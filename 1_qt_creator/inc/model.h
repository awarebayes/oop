//
// Created by dev on 2/25/22.
//

#ifndef INC_1_QT_CREATOR_MODEL_H
#define INC_1_QT_CREATOR_MODEL_H

#include "mesh3d.h"
#include "transformations.h"
#include "observable.h"
#include "mainwindow.h"

struct Model
{
private:
	Observable<Mesh3D> current_object;
	Observable<Transformations> transform;

public:
	Mat4x4 get_transformation_matrix() const;
	void connect_view(MainWindow &view);

	const Mesh3D &get_current_object() const;
	void mutate_current_object(Mesh3D object);

	Transformations get_transformations();
	void mutate_transformations(Transformations transformations);

};

#endif //INC_1_QT_CREATOR_MODEL_H
