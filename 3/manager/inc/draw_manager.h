//
// Created by dev on 5/6/22.
//

#ifndef INC_3_DRAW_MANAGER_H
#define INC_3_DRAW_MANAGER_H

#include <scene/inc/canvas.h>
#include <memory>
#include <visitor/inc/draw_visitor.h>
#include "base_manager.h"

class DrawManager : public BaseManager
{
public:
	DrawManager() = default;
	~DrawManager() override = default;
	DrawManager(const DrawManager &) = delete;
	void draw_scene();
private:
	std::shared_ptr<Canvas> canvas;
};

#endif //INC_3_DRAW_MANAGER_H
