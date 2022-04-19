//
// Created by dev on 3/10/22.
//
#include <cstdio>
#include <cstring>
#include "inc/obj3d.h"
#include "inc/obj3d_util.h"
#include "inc/mishalib.h"


errc init_obj3d(obj3d &self, const int n_vertices, const int n_lines)
{
	errc ec = errc::ok;
	self.n_vertices = n_vertices;
	self.n_lines = n_lines;

	self.vertices = (vec4 *) malloc(sizeof(vec4) * self.n_vertices);
	self.lines = (line *) malloc(sizeof(line) * self.n_lines);
	if (self.vertices == nullptr or self.lines == nullptr)
		ec = errc::bad_malloc;

	return ec;
}


errc init_obj3d_as(obj3d &self, const obj3d &other)
{
	errc ec = errc::ok;
	self.n_vertices = other.n_vertices;
	self.n_lines = other.n_lines;

	self.vertices = (vec4 *) malloc(sizeof(vec4) * self.n_vertices);
	self.lines = (line *) malloc(sizeof(line) * self.n_lines);
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
	self.n_lines = 0;
	self.n_vertices = 0;

	return errc::ok;
}

// ok
errc init_obj3d_from_string(obj3d &self, const big_string &in)
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
errc obj3d_from_file(obj3d &out_object, const big_string path)
{
	FILE *file = fopen(path.buf, "r");
	if (file == nullptr)
		return errc::no_such_file_or_directory;

	obj3d temp_object{};

	errc ec = errc::ok;
	big_string buffer;
	small_string line_type;

	int n_vertices_read = 0;
	int n_lines_read = 0;

	bool break_flag = false;

	while (not break_flag and ec == errc::ok)
	{
		get_big_line(buffer, file);
		get_big_line_type(line_type, buffer);

		if (strcmp(line_type, "i") == 0)
			ec = init_obj3d_from_string(temp_object, buffer);
		else if (strcmp(line_type, "v") == 0)
			ec = obj3d_read_vertex(temp_object, n_vertices_read++, buffer);
		else if (strcmp(line_type, "l") == 0)
			ec = obj3d_read_line(temp_object, n_lines_read++, buffer);
		else if (strcmp(line_type, "e") == 0)
			break_flag = true;
	}


	if (ec == errc::ok)
	{
		free_obj3d(out_object);
		out_object = temp_object;
	}
	else
		free_obj3d(temp_object);

	fclose(file);

	return ec;
}


errc obj3d_to_file(const obj3d &object, const big_string &path)
{
	errc ec = errc::ok;
	FILE *file = fopen(path.buf, "w");
	if (file == nullptr)
		return errc::bad_file_descriptor;

	fprintf(file, "i %d %d \n", object.n_vertices, object.n_lines);

	for (int i = 0; ec == errc::ok and i < object.n_vertices; i++)
		ec = obj3d_flush_vertex(file, i, object);

	for (int i = 0; ec == errc::ok and i < object.n_lines; i++)
		ec = obj3d_flush_line(file, i, object);

	fprintf(file, "e\n");
	fclose(file);

	return ec;
}

// OK
errc obj3d_apply_transform(obj3d &dest, const transformations &transforms)
{
	mat4x4 transform_mat{};
	transformations_to_matrix(transform_mat, transforms);
	apply_transform(dest.vertices, transform_mat, dest.n_vertices);
	return errc::ok;
}

// OK
errc obj3d_copy(obj3d &dest, const obj3d &source)
{
	errc ec = errc::ok;
	obj3d temp_dest{};

	ec = init_obj3d_as(temp_dest, source);
	if (ec == errc::ok)
	{
		free_obj3d(dest);
		dest = temp_dest;
		copy_lines(dest, source);
		copy_vertices(dest, source);
	}

	return ec;
}

errc obj3d_get_points(vec4 &p1, vec4 &p2, const obj3d &object, const line line_map)
{
	int index1 = line_map.first;
	int index2 = line_map.second;
	p1 = object.vertices[index1];
	p2 = object.vertices[index2];
	return errc::ok;
}

// ok
errc obj3d_draw_line(domain_scene &scene, const obj3d &object, const int line_num)
{
	line line_map = object.lines[line_num];
	vec4 p1 = {};
	vec4 p2 = {};
	obj3d_get_points(p1, p2, object, line_map);
	draw_line(scene, p1, p2);
	return errc::ok;
}

// OK
errc obj3d_draw(domain_scene scene, const obj3d &object)
{
	scene->clear();
	for (int i = 0; i < object.n_lines; i++)
		obj3d_draw_line(scene, object, i);

	return errc::ok;
}
