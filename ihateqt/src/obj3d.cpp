//
// Created by dev on 3/10/22.
//
#include <cstdio>
#include <cstring>
#include "inc/obj3d.h"
#include "inc/config.h"


errc init_obj3d(obj3d &self, int n_vertices, int n_lines)
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

	return self;
}

errc line_from_obj_string(const big_string &in, line &self)
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


errc appropriate_transformations(const obj3d &object, transformations &transforms)
{
	if (object.n_vertices == 0 || object.n_vertices == 1)
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

	transforms = {
			.translate = {
					.x = (double) SCREEN_WIDTH / 2,
					.y = (double) SCREEN_HEIGHT / 2,
					.z = 0,
					.type = transform_type::Translate },
			.rotate{ .x = 0, .y = 0, .z = 180, .type = transform_type::Rotate },
			.scale = { .x = required_scale, .y = required_scale, .z = required_scale, .type = transform_type::Scale },
	};
	return errc::ok;
}

errc find_object_center(obj3d &object, vec4 &center)
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

errc init_obj3d_from_string(obj3d &self, big_string& in)
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
	error = find_object_center(self, center);
	if (error == errc::ok)
		for (int i = 0; i < self.n_vertices; i++)
			self.vertices[i] = vec_sub(self.vertices[i], center);
	return error;
}

errc obj3d_from_file(obj3d &self, const big_string &path)
{

	FILE *file = fopen(path.buf, "r");
	if (file == nullptr)
		return errc::no_such_file_or_directory;

	obj3d object{};

	errc error = errc::ok;
	big_string buffer;
	small_string line_type;

	int n_vertices = 0;
	int n_lines = 0;

	while (not feof(file) and error == errc::ok)
	{
		fgets(buffer.buf, buffer.length, file);
		sscanf(buffer.buf, "%s", line_type);

		if (strcmp(line_type, "i") == 0)
			error = init_obj3d_from_string(object, buffer);
		else if (strcmp(line_type, "v") == 0)
		{
			vec4 read_result{};
			error = vec4_from_obj_string(buffer, read_result);
			object.vertices[n_vertices++] = read_result;
		}
		else if (strcmp(line_type, "l") == 0)
		{
			line read_result;
			error = line_from_obj_string(buffer, read_result);
			object.lines[n_lines++] = read_result;
		}
	}

	if (error == errc::ok)
		error = center_object_at_zero(object);

	if (error == errc::ok)
			self = object;
	else
		free_obj3d(object);
	fclose(file);
	return error;
}


errc obj3d_to_file(const obj3d &self, const big_string &path)
{
	errc ec = errc::ok;
	FILE *file = fopen(path.buf, "w");
	if (file == nullptr)
		return errc::bad_file_descriptor;

	fprintf(file, "i %d %d \n", self.n_vertices, self.n_lines);

	big_string buffer;
	for (int i = 0; i < self.n_vertices and ec == errc::ok; i++)
	{
		vec4 v = self.vertices[i];
		ec = vec4_to_obj_string(v, buffer);
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

