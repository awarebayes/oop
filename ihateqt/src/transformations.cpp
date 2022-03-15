//
// Created by dev on 3/10/22.
//

#include "inc/transformations.h"
#include <cmath>
#include <cstring>

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

errc apply_transform(const vec4 *vertices, vec4 *transformed, const mat4x4 &matrix, int n_points)
{
	for (int i = 0; i < n_points; i++)
		transformed[i] = vertices[i] * matrix;
	return errc::ok;
}

errc transform_xyz_from_string(transform_xyz &self, const string512 &in)
{
	errc error = errc::ok;

	transform_xyz temp_transform = { 0, 0, 0 };
	string16 comment = "";
	string16 type_str = "";
	if (sscanf(
			in.buf,
			"%s %s %lf %lf %lf",
			comment,
			type_str,
			&temp_transform.x,
			&temp_transform.y,
			&temp_transform.z)
			!= 5)
	{
		error = errc::bad_from_string_read;
	}

	if (get_transform_type_for_string(type_str, temp_transform.type) != errc::ok)
		error = errc::bad_from_string_read;

	if (error == errc::ok)
		self = temp_transform;
	return error;
}

errc transform_xyz_to_obj_string(const transform_xyz &self, string512 &out)
{
	errc ec = errc::ok;
	string16 type_str = "";
	ec = get_string_for_transform_type(self.type, type_str);
	if (ec != errc::ok)
		return errc::bad_to_string;

	ss << "## " << type_str << " " << self.x << " " << self.y << " " << self.z << "\n";
	printf("## %s %lf %lf %lf", );
	out = ss.str();
	return ec;
}

errc get_string_for_transform_type(const transform_type type, string512 &out)
{
	errc ec = errc::ok;
	switch (type)
	{
		case (transform_type::Translate):
			strcpy(out.buf, "Translate");
			break;
		case (transform_type::Scale):
			strcpy(out.buf, "Scale");
			break;
		case (transform_type::Rotate):
			strcpy(out.buf, "Rotate");
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

errc transforms_to_obj_string(const transformations &self, std::string &out)
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

errc transforms_read_partial(transformations &self, const std::string &in)
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

errc transforms_from_file(transformations &self, const std::string &path)
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

errc transforms_to_file(const transformations &self, const std::string &path)
{
	errc ec = errc::ok;
	std::ofstream file;
	std::string buffer;
	file.open(path.c_str(), std::ios::app);
	if (not file.is_open())
		return errc::bad_file_descriptor;

	ec = transforms_to_obj_string(self, buffer);

	if (ec == errc::ok)
		file << buffer;

	file.close();
	return ec;
}
