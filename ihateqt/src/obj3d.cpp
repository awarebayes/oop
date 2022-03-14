//
// Created by dev on 3/10/22.
//
#include <cstdio>
#include <cstring>
#include "inc/obj3d.h"
#include "inc/config.h"


errc init_obj3d(obj3d &self, int n_vertices, int n_lines)
{
	self.n_vertices = n_vertices;
	self.n_lines = n_lines;

	self.vertices = (vec4 *)malloc(sizeof(vec4) * self.n_vertices);
	self.lines = (line *)malloc(sizeof(line) * self.n_lines);
}

errc free_obj3d(obj3d &self)
{
	free(self.vertices);
	free(self.lines);
	self.n_lines = 0;
	self.n_vertices = 0;
}

obj3d obj3d_default_cube()
{
	// todo
}

errc line_from_obj_string(const string512 &in, line &self)
{
	errc ec = errc::ok;
	string16 line_type = "";
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
	if (object.n_vertices == 0)
		return errc::invalid_argument;

	vec4 first = object.vertices[0];
	MinMax min_max_coords[3] = {{ first[0], first[1] },
								{ first[1], first[2] },
								{ first[2], first[2] }};
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

errc find_object_center(obj3d &object)
{
	if (object.n_vertices == 0)
		return errc::invalid_argument;

	vec4 &center = object.center;
	for (int i = 0; i < object.n_vertices; i++)
	{
		vec4 vertex = object.vertices[i];
		center[0] += vertex[0];
		center[1] += vertex[1];
		center[2] += vertex[2];
	}

	center[0] /= (double)object.n_vertices;
	center[1] /= (double)object.n_vertices;
	center[2] /= (double)object.n_vertices;
	return errc::ok;
}

errc init_obj3d_from_string(obj3d &self, string512& in)
{
	errc ec = errc::ok;
	int n_vertices = 0, n_lines = 0;
	string16 line_type;
	if (sscanf(in.buf, "%s %d %d", line_type, &n_vertices, &n_lines) != 3)
		ec = errc::bad_from_string_read;
	if (strcmp(line_type, "i") != 0)
		ec = errc::bad_from_string_read;
	if (ec == errc::ok)
		init_obj3d(self, n_vertices, n_lines);
	return ec;
}

errc obj3d_from_file(obj3d &self, const string512 &path)
{

	FILE *file = fopen(path.buf, "r");
	if (file == nullptr)
		return errc::no_such_file_or_directory;

	obj3d object{};

	errc error = errc::ok;
	bool found_transformations = false;
	string512 buffer;
	string16 line_type;


	while (not feof(file) and error == errc::ok)
	{
		fgets(buffer.buf, buffer.length, file);
		sscanf(buffer.buf, "%s", line_type);

		if (strcmp(line_type, "i") == 0)
		{
			error = init_obj3d_from_string(object, buffer);
		}

		else if (strcmp(line_type, "v") == 0)
		{
			vec4 read_result{};
			error = vec4::from_obj_string(buffer.buf, read_result);

		}
		else if (strcmp(line_type, "l") == 0)
		{
			line read_result;
			error = line_from_obj_string(buffer, read_result);
			object.lines[object.n_lines++] = read_result;
		}
	}

	find_object_center(object);

	if (error == errc::ok)
			self = object;
	fclose(file);
	return error;
}


errc obj3d_to_file(const obj3d &self, const string512 &path)
{
	errc ec = errc::ok;
	FILE *file = fopen(path.buf, "r");
	if (file == nullptr)
		return errc::bad_file_descriptor;

	string512 buffer;
	for (int i = 0; i < self.n_vertices; i++)
	{
		vec4 v = self.vertices[i];
		ec = vec4::to_obj_string(v, buffer);
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

