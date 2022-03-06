//
// Created by dev on 3/6/22.
//

#ifndef INC_1_QT_CREATOR_CONTROLLER_H
#define INC_1_QT_CREATOR_CONTROLLER_H

#include "model.h"
#include "mainwindow.h"


struct Controller
{
private:
	struct Model &model_;
	MainWindow &view_;

public:
	Controller(Model &model, MainWindow &view);
	void mutate_transformations(TransformType type, Axis axis, double value);
	const Mesh3D &get_current_object() const;
	Mat4x4 get_transformation_matrix() const;
	void apply_appropriate_transformations();
	void load_object();
};

#endif //INC_1_QT_CREATOR_CONTROLLER_H
