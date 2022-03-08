//
// Created by dev on 2/26/22.
//

#ifndef INC_1_QT_CREATOR_TRANSFORMATIONS_H
#define INC_1_QT_CREATOR_TRANSFORMATIONS_H

#include "linalg.h"
#include "result.h"
#include "error.h"
#include <string>

enum struct Axis
{
	X, Y, Z
};

enum struct TransformType
{
	Translate, Scale, Rotate
};

auto transform_type_to_string(TransformType type) -> cpp::result<std::string, errc>;

auto string_to_transform_type(const std::string &name) -> cpp::result<TransformType, errc>;

typedef struct TransformXYZ
{
	double x;
	double y;
	double z;
	TransformType type;

	void mutate(Axis axis, double value);

	static auto from_string(const std::string &in) -> cpp::result<TransformXYZ, errc>;

	[[nodiscard]] auto to_obj_string() const -> cpp::result<std::string, errc>;
} TransformXYZ;

typedef struct Transformations
{
	TransformXYZ translate{};
	TransformXYZ rotate{};
	TransformXYZ scale{};

	[[nodiscard]] Mat4x4 getMatrix() const;

	void mutate(TransformType type, Axis axis, double value);

	[[nodiscard]] auto to_obj_string() const -> cpp::result<std::string, errc>;

	auto read_partial(const std::string &in) -> cpp::result<void, errc>;
} Transformations;


#endif //INC_1_QT_CREATOR_TRANSFORMATIONS_H
