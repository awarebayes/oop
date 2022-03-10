//
// Created by dev on 3/6/22.
//
#include <sstream>
#include "../inc/transformations.h"
#include "../inc/linalg.h"

void TransformXYZ::mutate(Axis axis, double value)
{
	switch (axis)
	{
		case Axis::X:
			x = value;
			break;
		case Axis::Y:
			y = value;
			break;
		case Axis::Z:
			z = value;
			break;
	}
}

auto TransformXYZ::from_string(const std::string &in) -> cpp::result<TransformXYZ, errc>
{

	errc error = errc::ok;

	TransformXYZ self = { 0, 0, 0 };
	std::stringstream ss(in);

	std::string comment;
	std::string transform_type;

	ss >> comment >> transform_type >> self.x >> self.y >> self.z;

	if (ss.fail())
		error = errc::bad_from_string_read;

	auto maybe_transform_type = string_to_transform_type(transform_type);
	if (maybe_transform_type.has_error())
		error = maybe_transform_type.error();
	else
		self.type = maybe_transform_type.value();

	if (error != errc::ok)
		return cpp::fail(errc::bad_from_string_read);
	return self;
}

auto TransformXYZ::to_obj_string() const -> cpp::result<std::string, errc>
{
	auto maybe_type_string = transform_type_to_string(type);
	if (maybe_type_string.has_error())
		return cpp::fail(errc::bad_to_string);

	std::stringstream ss;
	ss << "## " << maybe_type_string.value() << " " << x << " " << y << " " << z << "\n";
	return ss.str();
}

auto transform_type_to_string(TransformType type) -> cpp::result<std::string, errc>
{
	std::string result;
	bool error = false;
	switch (type)
	{
		case (TransformType::Translate):
			result = "Translate";
			break;
		case (TransformType::Scale):
			result = "Scale";
			break;
		case (TransformType::Rotate):
			result = "Rotate";
			break;
		default:
			error = true;
			break;
	}

	if (error)
		return cpp::fail(errc::invalid_argument);
	else
		return result;
}

auto string_to_transform_type(const std::string &name) -> cpp::result<TransformType, errc>
{
	TransformType result = TransformType::Translate;
	errc error = errc::ok;
	if (name == "Translate")
		result = TransformType::Translate;
	else if (name == "Rotate")
		result = TransformType::Rotate;
	else if (name == "Scale")
		result = TransformType::Scale;
	else
		error = errc::invalid_argument;

	if (error != errc::ok)
		return cpp::fail(errc::invalid_argument);
	return result;
}

Mat4x4 Transformations::getMatrix() const
{
	Mat4x4 result = Mat4x4::identity();
	Mat4x4 scale_mat = scale_matrix(scale.x, scale.y, scale.z);
	Mat4x4 rotate_mat = rotation_matrix(rotate.x, rotate.y, rotate.z);
	Mat4x4 translation_mat = translation_matrix(translate.x, translate.y, translate.z);

	result = result * scale_mat;
	result = result * rotate_mat;
	result = result * translation_mat;
	return result;
}

void Transformations::mutate(const TransformMutation &mut)
{
	switch (mut.type)
	{
		case TransformType::Translate:
			translate.mutate(mut.axis, mut.argument);
			break;
		case TransformType::Rotate:
			rotate.mutate(mut.axis, mut.argument);
			break;
		case TransformType::Scale:
			scale.mutate(mut.axis, mut.argument);
			break;
	}
}

auto Transformations::to_obj_string() const -> cpp::result<std::string, errc>
{
	auto maybe_translate = translate.to_obj_string();
	auto maybe_rotate = rotate.to_obj_string();
	auto maybe_scale = scale.to_obj_string();

	if (maybe_rotate.has_error() || maybe_scale.has_error() || maybe_translate.has_error())
		return cpp::fail(errc::bad_to_string);

	std::stringstream ss;
	ss << maybe_translate.value() << maybe_rotate.value() << maybe_scale.value();

	return ss.str();
}

auto Transformations::read_partial(const std::string &in) -> cpp::result<void, errc>
{
	auto maybe_transformation = TransformXYZ::from_string(in);
	if (maybe_transformation.has_error())
		return cpp::fail(errc::bad_from_string_read);

	TransformXYZ transformation = maybe_transformation.value();
	if (transformation.type == TransformType::Translate)
		translate = transformation;
	else if (transformation.type == TransformType::Rotate)
		rotate = transformation;
	else if (transformation.type == TransformType::Scale)
		scale = transformation;
	return {};
}

