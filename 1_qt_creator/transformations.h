//
// Created by dev on 2/26/22.
//

#ifndef INC_1_QT_CREATOR_TRANSFORMATIONS_H
#define INC_1_QT_CREATOR_TRANSFORMATIONS_H

typedef struct TransformXYZ
{
	double x;
	double y;
	double z;
} TransformXYZ;

typedef struct Transformations
{
	TransformXYZ translate{};
	TransformXYZ rotate{};
	TransformXYZ scale{};
} Transformations;

#endif //INC_1_QT_CREATOR_TRANSFORMATIONS_H
