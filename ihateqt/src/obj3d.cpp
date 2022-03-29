//
// Created by dev on 3/10/22.
//
#include <cstdio>
#include <cstring>
#include <QGraphicsScene>
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


errc init_obj3d_as(obj3d &self, const obj3d &other)
{
	errc ec = errc::ok;
	self.n_vertices = other.n_vertices;
	self.n_lines = other.n_lines;

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
	self.vertices = nullptr;
	self.lines = nullptr;

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
static errc find_mean(vec4 &center, const vec4 *vertices, const int n_vertices)
{
	if (n_vertices == 0)
		return errc::invalid_argument;

	center = {0, 0, 0, 0};

	for (int i = 0; i < n_vertices; i++)
	{
		vec4 vertex = vertices[i];
		center.components[0] += vertex.components[0];
		center.components[1] += vertex.components[1];
		center.components[2] += vertex.components[2];
	}

	center.components[0] /= (double)n_vertices;
	center.components[1] /= (double)n_vertices;
	center.components[2] /= (double)n_vertices;

	return errc::ok;
}

// ok
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

// ok
errc obj3d_move_if_ok(obj3d &dest, obj3d &source, const errc ec)
{
	if (ec == errc::ok)
	{
		free_obj3d(dest);
		dest = source;
	}
	else
		free_obj3d(source);
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

// fixme
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

	bool break_flag = false;

	while (not break_flag)
	{
		fgets(buffer.buf, buffer.length, file);
		sscanf(buffer.buf, "%s", line_type);

		if (strcmp(line_type, "i") == 0)
			// maybe explicitly init
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
		else if (strcmp(line_type, "e") == 0)
			break_flag = true;
	}

	if (error == errc::ok)
	{
		free(out_object.lines);
		free(out_object.vertices);
		out_object.lines = temp_object.lines;
		out_object.vertices = temp_object.vertices;
	}
	fclose(file);

	return error;
}

// OK
errc obj3d_from_file(obj3d &dest, const big_string path)
{
	errc ec = errc::ok;
	obj3d temp_obj{};

	ec = read_obj3d_from_file(temp_obj, path);

	if (ec == errc::ok)
		ec = center_object_at_zero(temp_obj);
	if (ec == errc::ok)
		ec = scale_to_fit_screen(temp_obj);

	obj3d_move_if_ok(dest, temp_obj, ec);
	return ec;
}


// OK? Mabe add_line
errc obj3d_to_file(const obj3d &object, const big_string &path)
{
	errc ec = errc::ok;
	FILE *file = fopen(path.buf, "w");
	if (file == nullptr)
		return errc::bad_file_descriptor;

	fprintf(file, "i %d %d \n", object.n_vertices, object.n_lines);

	for (int i = 0; ec == errc::ok and i < object.n_vertices; i++)
	{
		big_string buffer;
		vec4 v = object.vertices[i];
		ec = vec4_to_obj_string(buffer, v);
		fprintf(file, "%s\n", buffer.buf);
	}

	for (int i = 0; ec == errc::ok and i < object.n_lines; i++)
	{
		big_string buffer;
		line l = object.lines[i];
		ec = line_to_obj_string(buffer, l);
		fprintf(file, "%s\n", buffer.buf);
	}

	fprintf(file, "e\n");
	fclose(file);

	return ec;
}

errc copy_lines(obj3d& dest, const obj3d& source)
{
	if (dest.n_lines != source.n_lines)
		return errc::invalid_argument;

	for (int i = 0; i < source.n_lines; i++)
		dest.lines[i] = source.lines[i];
	return errc::ok;
}

// OK, переход уровня абстракции
errc apply_transform_to_obj3d(obj3d &dest, const obj3d &source, const transformations &transforms)
{
	mat4x4 transform_mat{};
	transformations_to_matrix(transform_mat, transforms);
	errc ec = apply_transform(dest.vertices, source.vertices, transform_mat, source.n_vertices);
	return ec;
}

// OK
errc obj3d_apply_transform_then_copy(obj3d &dest, const obj3d &source, const transformations &transforms)
{
	errc ec = errc::ok;
	obj3d temp_dest{};

	init_obj3d_as(temp_dest, source);
	ec = copy_lines(temp_dest, source);
	if (ec == errc::ok)
		ec = apply_transform_to_obj3d(temp_dest, source, transforms);

	obj3d_move_if_ok(dest, temp_dest, ec);
	return ec;
}

// OK
errc draw_obj3d(QGraphicsScene *scene, const obj3d &object)
{
	if (object.n_vertices == 0 or object.n_lines == 0)
		return errc::bad_render_call;

	scene->clear();

	for (int i = 0; i < object.n_lines; i++)
	{
		line l = object.lines[i];
		vec4 point1 = object.vertices[l.first];
		vec4 point2 = object.vertices[l.second];
		scene->addLine(point1.components[0], point1.components[1],
		               point2.components[0], point2.components[1]);
	}
	return errc::ok;
}
