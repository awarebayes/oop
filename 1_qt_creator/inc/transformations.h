//
// Created by dev on 2/26/22.
//

#ifndef INC_1_QT_CREATOR_TRANSFORMATIONS_H
#define INC_1_QT_CREATOR_TRANSFORMATIONS_H

#include "linalg.h"

enum struct Axis {
	X, Y, Z
};


enum struct TransformType{
	Translate, Scale, Rotate
};

typedef struct TransformXYZ
{
	double x;
	double y;
	double z;
	void mutate(Axis axis, double value);
} TransformXYZ;

typedef struct Transformations
{
	TransformXYZ translate{};
	TransformXYZ rotate{};
	TransformXYZ scale{};
	[[nodiscard]] Mat4x4 getMatrix() const;

	void mutate(TransformType type, Axis axis, double value);
} Transformations;


#endif //INC_1_QT_CREATOR_TRANSFORMATIONS_H
