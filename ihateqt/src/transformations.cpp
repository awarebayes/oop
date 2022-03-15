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

	result = mat_identity();
	result = mul_mat(result, scale_mat);
	result = mul_mat(result, rotation_mat);
	result = mul_mat(result, translation_mat);
	return errc::ok;
}

errc apply_transform(const vec4 *vertices, vec4 *transformed, const mat4x4 &matrix, int n_points)
{
	for (int i = 0; i < n_points; i++)
		transformed[i] = mul_vec(vertices[i], matrix);
	return errc::ok;
}

errc transform_xyz_from_string(transform_xyz &self, const big_string &in)
{
	errc error = errc::ok;

	transform_xyz temp_transform = { 0, 0, 0 };
	small_string comment = "";
	small_string type_str = "";
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

errc transform_xyz_to_obj_string(const transform_xyz &self, big_string &out)
{
	errc ec = errc::ok;
	small_string type_str = "";
	ec = get_string_for_transform_type(self.type, type_str);
	if (ec != errc::ok)
		return errc::bad_to_string;
	sprintf(out.buf, "## %s %lf %lf %lf", type_str, self.x, self.y, self.z);
	return ec;
}

errc get_string_for_transform_type(const transform_type type, small_string out)
{
	errc ec = errc::ok;
	switch (type)
	{
		case (transform_type::Translate):
			strcpy(out, "Translate");
			break;
		case (transform_type::Scale):
			strcpy(out, "Scale");
			break;
		case (transform_type::Rotate):
			strcpy(out, "Rotate");
			break;
		default:
			ec = errc::invalid_argument;
			break;
	}
	return ec;
}

errc get_transform_type_for_string(const small_string name, transform_type &out)
{
	errc ec = errc::ok;
	if (strcmp(name, "Translate") == 0)
		out = transform_type::Translate;
	else if (strcmp(name, "Rotate") == 0)
		out = transform_type::Rotate;
	else if (strcmp(name, "Scale") == 0)
		out = transform_type::Scale;
	else
		ec = errc::invalid_argument;
	return ec;
}

errc transforms_to_obj_string(const transformations &self, big_string &out)
{
	errc ec = errc::ok;
	big_string translate_str;
	big_string rotate_str;
	big_string scale_str;

	ec = transform_xyz_to_obj_string(self.translate, translate_str);
	if (ec == errc::ok)
		ec = transform_xyz_to_obj_string(self.rotate, rotate_str);
	if (ec == errc::ok)
		ec = transform_xyz_to_obj_string(self.scale, scale_str);

	if (ec == errc::ok)
	{
		sprintf(out.buf, "%s\n%s\n%s\n", translate_str.buf, rotate_str.buf, scale_str.buf);
	}

	return ec;
}

errc transforms_read_partial(transformations &self, const big_string &in)
{
	errc ec = errc::ok;
	transform_xyz loaded_transform;
	ec = transform_xyz_from_string(loaded_transform, in);

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

errc transforms_from_file(transformations &self, const big_string &path)
{
	bool transforms_found = false;
	errc ec = errc::ok;
	transformations transforms;
	FILE *in_file = fopen(path.buf, "r");

	if (in_file == nullptr)
		return errc::no_such_file_or_directory;

	big_string buffer;
	small_string line_type;


	while (not feof(in_file) and ec == errc::ok)
	{
		fgets(buffer.buf, buffer.length, in_file);
		sscanf(buffer.buf, "%s", line_type);

		if (strcmp(line_type, "##") == 0)
		{
			ec = transforms_read_partial(transforms, buffer);
			transforms_found = true;
		}
	}


	if (not transforms_found)
		ec = errc::transforms_not_found;
	if (ec == errc::ok)
		self = transforms;

	fclose(in_file);
	return ec;
}

errc transforms_to_file(const transformations &self, const big_string &path)
{
	errc ec = errc::ok;

	FILE *file = fopen(path.buf, "a");
	big_string buffer;
	if (file == nullptr)
		return errc::bad_file_descriptor;

	ec = transforms_to_obj_string(self, buffer);

	if (ec == errc::ok)
		fprintf(file, "%s", buffer.buf);
	fclose(file);
	return ec;
}
