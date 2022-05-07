//
// Created by dev on 5/7/22.
//

#ifndef INC_3_DRAW_MANAGER_H
#define INC_3_DRAW_MANAGER_H

class DrawManager : public BaseManager
{
private:
	std::shared_ptr<Canvas> canvas;
public:
	DrawManager() = default;
	~DrawManager() override = default;
	DrawManager(const DrawManager &) = delete;
	void draw_scene();
	void set_canvas(std::shared_ptr<Canvas> &canvas_);
};

class DrawManagerCreator
{
public:
	std::shared_ptr<DrawManager> get();
private:
	void create();
	std::shared_ptr<DrawManager> singleton;
};

#endif //INC_3_DRAW_MANAGER_H
