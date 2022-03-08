//
// Created by dev on 2/25/22.
//

#ifndef INC_1_QT_CREATOR_MODEL_H
#define INC_1_QT_CREATOR_MODEL_H

#include "mesh3d.h"
#include "transformations.h"
#include "observable.h"

struct Model
{
	Observable<Mesh3D> current_object;
	Observable<Transformations> transform;

	[[nodiscard]] const Mesh3D &get_current_object() const;

	void mutate_current_object(const Mesh3D &object);

	[[nodiscard]] const Transformations &get_transformations() const;

	void mutate_transformations(const Transformations &transformations);
};

#endif //INC_1_QT_CREATOR_MODEL_H
