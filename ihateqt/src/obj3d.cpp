//
// Created by dev on 3/10/22.
//
#include <cstdio>
#include <cstring>
#include "inc/obj3d.h"
#include "inc/config.h"


errc init_obj3d(obj3d &self, const int n_vertices, const int n_lines)
{
	errc ec = errc::ok;
	self.n_vertices = n_vertices;
	self.n_lines = n_lines;

	self.vertices = (vec4 *)malloc(sizeof(vec4) * self.n_vertices);
	self.lines = (line *)malloc(sizeof(line) * self.n_lines);
	if (self.vertices == nullptr or self.lines == nullptr)
		ec = errc::bad_malloc;

	return ec;
}

errc free_obj3d(obj3d &self)
{
	free(self.vertices);
	free(self.lines);

	return errc::ok;
}

obj3d obj3d_default_cube()
{
	obj3d self{};
	init_obj3d(self, 8, 18);

	self.vertices[0] = {-1.0, -1.0, -1.0, 1.0};
	self.vertices[1] = {-1.0, -1.0, 1.0, 1.0};
	self.vertices[2] = {-1.0, 1.0, -1.0, 1.0};
	self.vertices[3] = {-1.0, 1.0, 1.0, 1.0};
	self.vertices[4] = {1.0, -1.0, -1.0, 1.0};
	self.vertices[5] = {1.0, -1.0, 1.0, 1.0};
	self.vertices[6] = {1.0, 1.0, -1.0, 1.0};
	self.vertices[7] = {1.0, 1.0, 1.0, 1.0};


	self.lines[0] = {5, 1};
	self.lines[1] = {6, 0};
	self.lines[2] = {1, 0};
	self.lines[3] = {7, 3};
	self.lines[4] = {3, 2};
	self.lines[5] = {2, 0};
	self.lines[6] = {7, 6};
	self.lines[7] = {5, 4};
	self.lines[8] = {5, 0};
	self.lines[9] = {4, 0};
	self.lines[10] = {3, 1};
	self.lines[11] = {6, 2};
	self.lines[12] = {7, 2};
	self.lines[13] = {7, 5};
	self.lines[14] = {7, 1};
	self.lines[15] = {6, 4};
	self.lines[16] = {3, 0};
	self.lines[17] = {7, 4};


	center_object_at_zero(self);
	scale_to_fit_screen(self);

	return self;
}

errc line_from_obj_string(line &self, const big_string &in)
{
	errc ec = errc::ok;
	small_string line_type = "";
	if (sscanf(
			in.buf,
			"%s %d %d",
			line_type,
			&self.first,
			&self.second
			) != 3)
		ec = errc::bad_from_string_read;
	if (strcmp(line_type, "l") != 0)
		ec = errc::bad_from_string_read;

	return ec;
}

struct MinMax
{
	double min;
	double max;
};

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
	for (auto & mm : min_max_coords)
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

errc apply_scale_to_object(obj3d &object, const double scale)
{
	if (scale == 0)
		return errc::invalid_argument;

	for (int i = 0; i < object.n_vertices; i++)
		object.vertices[i] = scale_vec(object.vertices[i], scale);

	return errc::ok;
}


errc scale_to_fit_screen(obj3d &object)
{
	double scale = 1.0;
	find_scale_to_fit_screen(scale, object);
	errc ec = apply_scale_to_object(object, scale);
	return ec;
}

static errc find_object_center(vec4 &center, const obj3d &object)
{
	if (object.n_vertices == 0)
		return errc::invalid_argument;

	center = {0, 0, 0, 0};

	for (int i = 0; i < object.n_vertices; i++)
	{
		vec4 vertex = object.vertices[i];
		center.components[0] += vertex.components[0];
		center.components[1] += vertex.components[1];
		center.components[2] += vertex.components[2];
	}

	center.components[0] /= (double)object.n_vertices;
	center.components[1] /= (double)object.n_vertices;
	center.components[2] /= (double)object.n_vertices;

	return errc::ok;
}

errc init_obj3d_from_string(obj3d &self, const big_string& in)
{
	errc ec = errc::ok;
	int n_vertices = 0, n_lines = 0;
	small_string line_type;
	if (sscanf(in.buf, "%s %d %d", line_type, &n_vertices, &n_lines) != 3)
		ec = errc::bad_from_string_read;
	if (strcmp(line_type, "i") != 0)
		ec = errc::bad_from_string_read;
	if (ec == errc::ok)
		init_obj3d(self, n_vertices, n_lines);

	return ec;
}

errc center_object_at_zero(obj3d &self)
{
	vec4 center{};
	errc error = errc::ok;
	error = find_object_center(center, self);
	if (error == errc::ok)
		for (int i = 0; i < self.n_vertices; i++)
			self.vertices[i] = vec_sub(self.vertices[i], center);

	return error;
}

static errc read_obj3d_from_file(obj3d &out_object, const big_string &path)
{

	FILE *file = fopen(path.buf, "r");
	if (file == nullptr)
		return errc::no_such_file_or_directory;

	obj3d temp_object{};

	errc error = errc::ok;
	big_string buffer;
	small_string line_type;

	int n_vertices = 0;
	int n_lines = 0;

	while (error == errc::ok and not feof(file))
	{
		fgets(buffer.buf, buffer.length, file);
		sscanf(buffer.buf, "%s", line_type);

		if (strcmp(line_type, "i") == 0)
			error = init_obj3d_from_string(temp_object, buffer);
		else if (strcmp(line_type, "v") == 0)
		{
			vec4 read_result{};
			error = vec4_from_obj_string(read_result, buffer);
			temp_object.vertices[n_vertices++] = read_result;
		}
		else if (strcmp(line_type, "l") == 0)
		{
			line read_result;
			error = line_from_obj_string(read_result, buffer);
			temp_object.lines[n_lines++] = read_result;
		}
	}

	if (error == errc::ok)
		out_object = temp_object;
	else
		free_obj3d(temp_object);
	fclose(file);

	return error;
}

errc obj3d_from_file(obj3d &out_obj, const big_string path)
{
	errc ec = errc::ok;
	obj3d temp_obj{};

	ec = read_obj3d_from_file(temp_obj, path);
	if (ec == errc::ok)
		ec = scale_to_fit_screen(temp_obj);

	if (ec == errc::ok)
		out_obj = temp_obj;
	else
		free_obj3d(temp_obj);
	return ec;
}


errc obj3d_to_file(const obj3d &self, const big_string &path)
{
	errc ec = errc::ok;
	FILE *file = fopen(path.buf, "w");
	if (file == nullptr)
		return errc::bad_file_descriptor;

	fprintf(file, "i %d %d \n", self.n_vertices, self.n_lines);

	big_string buffer;
	for (int i = 0; ec == errc::ok and i < self.n_vertices; i++)
	{
		vec4 v = self.vertices[i];
		ec = vec4_to_obj_string(buffer, v);
		fprintf(file, "%s\n", buffer.buf);
	}

	for (int i = 0; i < self.n_lines; i++)
	{
		line l = self.lines[i];
		fprintf(file, "l %d %d\n", l.first, l.second);
	}

	fclose(file);

	return ec;
}


errc copy_transformed_vertices(vec4 *dest, const transformations &transforms, const obj3d &object)
{
	errc ec = errc::ok;
	mat4x4 transform_mat;
	ec = transformations_to_matrix(transform_mat, transforms);
	if (ec == errc::ok)
		ec = apply_transform(object.vertices, dest, transform_mat, object.n_vertices);
	return ec;
}
