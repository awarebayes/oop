//
// Created by dev on 3/29/22.
//
#include "inc/obj3d.h"
#include "inc/config.h"
#include <cstring>


// ok
errc line_from_obj_string(line &self, const big_string &in)
{
	errc ec = errc::ok;
	line temp_line;
	small_string line_type = "";
	if (sscanf(
			in.buf,
			"%s %d %d",
			line_type,
			&temp_line.first,
			&temp_line.second
	) != 3)
		ec = errc::bad_from_string_read;
	if (strcmp(line_type, "l") != 0)
		ec = errc::bad_from_string_read;

	if (ec == errc::ok)
		self = temp_line;
	return ec;
}

errc line_to_obj_string(big_string &out, const line &self)
{
	sprintf(out.buf, "l %d %d", self.first, self.second);
	return errc::ok;
}


struct MinMax
{
	double min;
	double max;
};

// ok
errc find_scale_to_fit_screen(double &out_scale, const obj3d &object)
{
	if (object.n_vertices < 2)
		return errc::invalid_argument;

	vec4 first = object.vertices[0];
	MinMax min_max_coords[3] = {{ first.components[0], first.components[1] },
	                            { first.components[1], first.components[2] },
	                            { first.components[2], first.components[2] }};
	for (int i = 0; i < object.n_vertices; i++)
	{
		vec4 point = object.vertices[i];
		for (int j = 0; j < 3; j++)
		{
			struct MinMax &mm = min_max_coords[j];
			mm.min = std::min(point.components[j], mm.min);
			mm.max = std::max(point.components[j], mm.max);
		}
	}

	double max_coordinate_difference = 0;
	for (auto &mm: min_max_coords)
	{
		double coordinate_difference = mm.max - mm.min;
		max_coordinate_difference = std::max(max_coordinate_difference, coordinate_difference);
	}

	int screen_dim = std::min(SCREEN_WIDTH, SCREEN_HEIGHT);
	double required_scale = screen_dim / max_coordinate_difference;

	required_scale *= 0.6; // чтобы не на весь экран было

	out_scale = required_scale;

	return errc::ok;
}

// ok
errc apply_scale_to_object(obj3d &object, const double scale)
{
	if (scale <= 0)
		return errc::invalid_argument;

	for (int i = 0; i < object.n_vertices; i++)
		object.vertices[i] = scale_vec(object.vertices[i], scale);

	return errc::ok;
}

// ok
errc scale_to_fit_screen(obj3d &object)
{
	double scale = 1.0;
	find_scale_to_fit_screen(scale, object);
	errc ec = apply_scale_to_object(object, scale);
	return ec;
}


// ok
errc find_mean(vec4 &center, const vec4 *vertices, const int n_vertices)
{
	if (n_vertices == 0)
		return errc::invalid_argument;

	center = { 0, 0, 0, 0 };

	for (int i = 0; i < n_vertices; i++)
	{
		vec4 vertex = vertices[i];
		center.components[0] += vertex.components[0];
		center.components[1] += vertex.components[1];
		center.components[2] += vertex.components[2];
	}

	center.components[0] /= (double) n_vertices;
	center.components[1] /= (double) n_vertices;
	center.components[2] /= (double) n_vertices;

	return errc::ok;
}

// ok
errc center_object_at_zero(obj3d &object)
{
	vec4 center{};
	errc error = errc::ok;
	error = find_mean(center, object.vertices, object.n_vertices);

	if (error == errc::ok)
		for (int i = 0; i < object.n_vertices; i++)
			object.vertices[i] = vec_sub(object.vertices[i], center);

	return error;
}

errc obj3d_read_vertex(obj3d &object, const int vertex_number, const big_string &str)
{
	vec4 read_result{};
	errc error = vec4_from_obj_string(read_result, str);
	if (error == errc::ok)
		object.vertices[vertex_number] = read_result;
	return error;
}

errc obj3d_read_line(obj3d &object, const int line_number, const big_string &str)
{
	line read_result{};
	errc error = line_from_obj_string(read_result, str);
	if (error == errc::ok)
		object.lines[line_number] = read_result;
	return error;
}


obj3d obj3d_default_cube()
{
	obj3d self{};
	init_obj3d(self, 8, 18);

	self.vertices[0] = { -1.0, -1.0, -1.0, 1.0 };
	self.vertices[1] = { -1.0, -1.0, 1.0, 1.0 };
	self.vertices[2] = { -1.0, 1.0, -1.0, 1.0 };
	self.vertices[3] = { -1.0, 1.0, 1.0, 1.0 };
	self.vertices[4] = { 1.0, -1.0, -1.0, 1.0 };
	self.vertices[5] = { 1.0, -1.0, 1.0, 1.0 };
	self.vertices[6] = { 1.0, 1.0, -1.0, 1.0 };
	self.vertices[7] = { 1.0, 1.0, 1.0, 1.0 };


	self.lines[0] = { 5, 1 };
	self.lines[1] = { 6, 0 };
	self.lines[2] = { 1, 0 };
	self.lines[3] = { 7, 3 };
	self.lines[4] = { 3, 2 };
	self.lines[5] = { 2, 0 };
	self.lines[6] = { 7, 6 };
	self.lines[7] = { 5, 4 };
	self.lines[8] = { 5, 0 };
	self.lines[9] = { 4, 0 };
	self.lines[10] = { 3, 1 };
	self.lines[11] = { 6, 2 };
	self.lines[12] = { 7, 2 };
	self.lines[13] = { 7, 5 };
	self.lines[14] = { 7, 1 };
	self.lines[15] = { 6, 4 };
	self.lines[16] = { 3, 0 };
	self.lines[17] = { 7, 4 };


	center_object_at_zero(self);
	scale_to_fit_screen(self);

	return self;
}


errc copy_lines(obj3d &dest, const obj3d &source)
{
	if (dest.n_lines != source.n_lines)
		return errc::invalid_argument;

	for (int i = 0; i < source.n_lines; i++)
		dest.lines[i] = source.lines[i];
	return errc::ok;
}
