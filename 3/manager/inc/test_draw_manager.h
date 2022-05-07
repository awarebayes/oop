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

class TestDrawManager : public BaseManager
{
public:
	explicit TestDrawManager(std::shared_ptr<Canvas> canvas_) : canvas(std::move(canvas_)) {};
	~TestDrawManager() override = default;
	TestDrawManager(const TestDrawManager &) = delete;
	void draw_scene();
	std::shared_ptr<Canvas> canvas;
};

class TestDrawManagerCreator
{
public:
	std::shared_ptr<TestDrawManager> get();
	static std::shared_ptr<TestDrawManager> get_test();
private:
	void create();
	std::shared_ptr<TestDrawManager> singleton;
};

#endif //INC_3_TEST_DRAW_MANAGER_H
