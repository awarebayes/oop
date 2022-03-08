//
// Created by dev on 2/26/22.
//

#ifndef INC_1_QT_CREATOR_RENDERER_H
#define INC_1_QT_CREATOR_RENDERER_H

#include <QGraphicsScene>
#include "mesh3d.h"
#include "linalg.h"
#include "result.h"
#include "error.h"

typedef struct Renderer
{
	std::shared_ptr<QGraphicsScene> scene;

	Renderer(int width, int height, QObject &parent);

	~Renderer();

	auto draw_object(Mesh3D const &mesh, Transformations const &transformations) const -> cpp::result<void, errc>;
} Renderer;

#endif //INC_1_QT_CREATOR_RENDERER_H
