//
// Created by dev on 3/10/22.
//

#include "inc/transformations.h"
#include <cmath>
#include <vector>
#include <sstream>
#include <fstream>


bool transform_xyz_is_valid(const transform_xyz &self)
{
	if (std::isnan(self.x) || std::isnan(self.y) || std::isnan(self.z))
		return false;
	if (std::isinf(self.x) || std::isinf(self.y) || std::isinf(self.z))
		return false;
	if (self.type != transform_type::Translate && self.type != transform_type::Rotate && self.type != transform_type::Scale)
		return false;
	return true;
}

bool transformations_valid(const transformations &self)
{
	bool res = true;
	res &= transform_xyz_is_valid(self.translate);
	res &= transform_xyz_is_valid(self.rotate);
	res &= transform_xyz_is_valid(self.scale);
	return res;
}

errc transform_xyz_to_matrix(const transform_xyz &self, mat4x4 &result)
{
	if (not transform_xyz_is_valid(self))
		return errc::invalid_transformations;
	errc ec = errc::ok;
	switch (self.type)
	{
		case transform_type::Translate:
			result = translation_matrix(self.x, self.y, self.z);
			break;

		case transform_type::Rotate:
			result = rotation_matrix(self.x, self.y, self.z);
			break;

		case transform_type::Scale:
			result = scale_matrix(self.x, self.y, self.z);
			break;
		default:
			ec = errc::invalid_transformations;
			break;
	}
	return ec;
}

errc transformations_to_matrix(const transformations &self, mat4x4 &result)
{
	if (not transformations_valid(self))
		return errc::invalid_transformations;

	mat4x4 translation_mat = {.mat={0}};
	mat4x4 rotation_mat = {.mat={0}};
	mat4x4 scale_mat = {.mat={0}};

	transform_xyz_to_matrix(self.translate, translation_mat);
	transform_xyz_to_matrix(self.rotate, rotation_mat);
	transform_xyz_to_matrix(self.scale, scale_mat);

	result = mat4x4::identity();
	result = result * scale_mat;
	result = result * rotation_mat;
	result = result * translation_mat;
	return errc::ok;
}

std::vector<vec4> apply_transform(const std::vector<vec4> &vertices, const mat4x4 &matrix)
{
	std::vector<vec4> transformed;
	transformed.reserve(vertices.size());

	for (const auto &vertex: vertices)
	{
		vec4 result = vertex * matrix;
		transformed.push_back(result);
	}

	return std::move(transformed);
}

errc transform_xyz::from_string(transform_xyz &self, const std::string &in)
{
	errc error = errc::ok;

	transform_xyz temp_transform = { 0, 0, 0 };
	std::stringstream ss(in);
	std::string comment;
	std::string type_str;
	ss >> comment >> type_str >> temp_transform.x >> temp_transform.y >> temp_transform.z;

	if (ss.fail())
		error = errc::bad_from_string_read;
	error = get_transform_type_for_string(type_str, temp_transform.type);

	if (error != errc::ok)
		error = errc::bad_from_string_read;
	else
		self = temp_transform;
	return error;
}

errc transform_xyz::to_obj_string(const transform_xyz &self, std::string &out)
{
	errc ec = errc::ok;
	std::string type_str;
	ec = get_string_for_transform_type(self.type, type_str);
	if (ec != errc::ok)
		return errc::bad_to_string;

	std::stringstream ss;
	ss << "## " << type_str << " " << self.x << " " << self.y << " " << self.z << "\n";
	out = ss.str();
	return ec;
}

errc get_string_for_transform_type(const transform_type type, std::string &out)
{
	errc ec = errc::ok;
	switch (type)
	{
		case (transform_type::Translate):
			out = "Translate";
			break;
		case (transform_type::Scale):
			out = "Scale";
			break;
		case (transform_type::Rotate):
			out = "Rotate";
			break;
		default:
			ec = errc::invalid_argument;
			break;
	}
	return ec;
}

errc get_transform_type_for_string(const std::string &name, transform_type &out)
{
	errc ec = errc::ok;
	if (name == "Translate")
		out = transform_type::Translate;
	else if (name == "Rotate")
		out = transform_type::Rotate;
	else if (name == "Scale")
		out = transform_type::Scale;
	else
		ec = errc::invalid_argument;
	return ec;
}

errc transformations::to_obj_string(const transformations &self, std::string &out)
{
	errc ec = errc::ok;
	std::string translate_str;
	std::string rotate_str;
	std::string scale_str;

	ec = transform_xyz::to_obj_string(self.translate, translate_str);
	if (ec == errc::ok)
		ec = transform_xyz::to_obj_string(self.rotate, rotate_str);
	if (ec == errc::ok)
		ec = transform_xyz::to_obj_string(self.scale, scale_str);

	if (ec == errc::ok)
	{
		std::stringstream ss;
		ss << translate_str << rotate_str << scale_str;
		out = ss.str();
	}

	return ec;
}

errc transformations::read_partial(transformations &self, const std::string &in)
{
	errc ec = errc::ok;
	transform_xyz loaded_transform;
	ec = transform_xyz::from_string(loaded_transform, in);

	if (ec == errc::ok)
	{
		if (loaded_transform.type == transform_type::Translate)
			self.translate = loaded_transform;
		else if (loaded_transform.type == transform_type::Rotate)
			self.rotate = loaded_transform;
		else if (loaded_transform.type == transform_type::Scale)
			self.scale = loaded_transform;
	}
	return ec;
}

errc transformations::from_file(transformations &self, const std::string &path)
{
	bool transforms_found = false;
	errc ec = errc::ok;
	std::stringstream ss;
	std::ifstream in_file(path.c_str());
	transformations transforms;

	if (in_file.fail())
		return errc::no_such_file_or_directory;

	std::string line;
	std::string prefix;
	while (std::getline(in_file, line) and ec == errc::ok)
	{
		ss.clear();
		ss.str(line);
		prefix.clear();

		ss >> prefix;
		if (prefix == "##")
		{
			ec = transformations::read_partial(transforms, line);
			transforms_found = true;
		}
	}

	if (not transforms_found)
		ec = errc::transforms_not_found;
	if (ec == errc::ok)
		self = transforms;
	return ec;
}

errc transformations::to_file(const transformations &self, const std::string &path)
{
	errc ec = errc::ok;
	std::ofstream file;
	std::string buffer;
	file.open(path.c_str(), std::ios::app);
	if (not file.is_open())
		return errc::bad_file_descriptor;

	ec = transformations::to_obj_string(self, buffer);

	if (ec == errc::ok)
		file << buffer;

	file.close();
	return ec;
}
