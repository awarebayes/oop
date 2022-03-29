//
// Created by dev on 3/10/22.
//
#include <cstdio>
#include <cstring>
#include <QGraphicsScene>
#include "inc/obj3d.h"
#include "inc/config.h"
#include "inc/obj3d_util.h"


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
static errc init_read_obj3d_from_file(obj3d &out_object, const big_string &path)
{
	FILE *file = fopen(path.buf, "r");
	if (file == nullptr)
		return errc::no_such_file_or_directory;

	obj3d temp_object{};

	errc error = errc::ok;
	big_string buffer;
	small_string line_type;

	int n_vertices_read = 0;
	int n_lines_read = 0;

	bool break_flag = false;

	while (not break_flag and error == errc::ok)
	{
		fgets(buffer.buf, buffer.length, file);
		sscanf(buffer.buf, "%s", line_type);

		if (strcmp(line_type, "i") == 0)
			error = init_obj3d_from_string(temp_object, buffer);
		else if (strcmp(line_type, "v") == 0)
			error = obj3d_read_vertex(temp_object, n_vertices_read++, buffer);
		else if (strcmp(line_type, "l") == 0)
			error = obj3d_read_line(temp_object, n_lines_read++, buffer);
		else if (strcmp(line_type, "e") == 0)
			break_flag = true;
	}

	obj3d_move_if_ok(out_object, temp_object, error);
	fclose(file);

	return error;
}

// OK
errc obj3d_from_file(obj3d &dest, const big_string path)
{
	errc ec = errc::ok;
	obj3d temp_obj{};

	ec = init_read_obj3d_from_file(temp_obj, path);

	if (ec == errc::ok)
		ec = center_object_at_zero(temp_obj);
	if (ec == errc::ok)
		ec = scale_to_fit_screen(temp_obj);

	obj3d_move_if_ok(dest, temp_obj, ec);
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
	{
		big_string buffer;
		ec = vec4_to_obj_string(buffer, object.vertices[i]);
		fprintf(file, "%s\n", buffer.buf);
	}

	for (int i = 0; ec == errc::ok and i < object.n_lines; i++)
	{
		big_string buffer;
		ec = line_to_obj_string(buffer, object.lines[i]);
		fprintf(file, "%s\n", buffer.buf);
	}

	fprintf(file, "e\n");
	fclose(file);

	return ec;
}

// OK
static errc obj3d_apply_transform(obj3d &dest, const obj3d &source, const transformations &transforms)
{
	mat4x4 transform_mat{};
	transformations_to_matrix(transform_mat, transforms);
	apply_transform(dest.vertices, source.vertices, transform_mat, source.n_vertices);
	return errc::ok;
}

// OK
errc obj3d_apply_transform_then_copy(obj3d &dest, const obj3d &source, const transformations &transforms)
{
	errc ec = errc::ok;
	obj3d temp_dest{};

	init_obj3d_as(temp_dest, source);
	ec = copy_lines(temp_dest, source);
	if (ec == errc::ok)
		ec = obj3d_apply_transform(temp_dest, source, transforms);

	obj3d_move_if_ok(dest, temp_dest, ec);
	return ec;
}

// OK
errc obj3d_draw(QGraphicsScene *scene, const obj3d &object)
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
