//
// Created by dev on 5/6/22.
//

#ifndef INC_3_TEST_DRAW_MANAGER_H
#define INC_3_TEST_DRAW_MANAGER_H

#include <drawer/inc/base_canvas.h>
#include <memory>
#include <utility>
#include <visitor/inc/draw_visitor.h>
#include "base_manager.h"

class DrawManager : public BaseManager
{
private:
	std::shared_ptr<Canvas> canvas;
public:
	explicit DrawManager(std::shared_ptr<Canvas> canvas_) : canvas(std::move(canvas_)) {};
	~DrawManager() override = default;
	DrawManager(const TestDrawManager &) = delete;
	void draw_scene();
};

class DrawManagerCreator
{
public:
	std::shared_ptr<DrawManager> get();
	static std::shared_ptr<DrawManager> get_test();
private:
	void create();
	std::shared_ptr<DrawManager> singleton;
};

#endif //INC_3_TEST_DRAW_MANAGER_H
