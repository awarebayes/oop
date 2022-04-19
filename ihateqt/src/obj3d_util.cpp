//
// Created by dev on 3/29/22.
//
#include "inc/obj3d.h"
#include "inc/config.h"
#include <cstring>

errc obj3d_flush_vertex(FILE *file, const int index, const obj3d object)
{
	return vec_flush(file, object.vertices[index]);
}

errc obj3d_flush_line(FILE *file, const int index, const obj3d object)
{
	return line_flush(file, object.lines[index]);
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

errc copy_lines(obj3d &dest, const obj3d &source)
{
	if (dest.n_lines != source.n_lines)
		return errc::invalid_argument;

	for (int i = 0; i < source.n_lines; i++)
		dest.lines[i] = source.lines[i];
	return errc::ok;
}

errc copy_vertices(obj3d &dest, const obj3d &source)
{
	if (dest.n_vertices != source.n_vertices)
		return errc::invalid_argument;

	for (int i = 0; i < source.n_vertices; i++)
		dest.vertices[i] = source.vertices[i];
	return errc::ok;
}

obj3d obj3d_default_cube()
{
	obj3d self{};
	init_obj3d(self, 8, 18);

	self.vertices[0] = { -210.0, -210.0, -210.0, 1.0 };
	self.vertices[1] = { -210.0, -210.0, 210.0, 1.0 };
	self.vertices[2] = { -210.0,  210.0, -210.0, 1.0 };
	self.vertices[3] = { -210.0,  210.0, 210.0, 1.0 };
	self.vertices[4] = {  210.0, -210.0, -210.0, 1.0 };
	self.vertices[5] = {  210.0, -210.0, 210.0, 1.0 };
	self.vertices[6] = {  210.0,  210.0, -210.0, 1.0 };
	self.vertices[7] = {  210.0,  210.0, 210.0, 1.0 };


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

	return self;
}
