//
// Created by dev on 2/26/22.
//

#ifndef INC_1_QT_CREATOR_RENDERER_H
#define INC_1_QT_CREATOR_RENDERER_H

#include <QGraphicsScene>
#include "mesh3d.h"
#include "linalg.h"

typedef struct Renderer {
	QGraphicsScene *scene;
	int height;
	int width;
	Renderer() = default;
	Renderer(int width, int height, QObject &parent);

	void draw_object(Mesh3D const &mesh, Mat4x4 const& transformations) const;
} Renderer;

#endif //INC_1_QT_CREATOR_RENDERER_H
