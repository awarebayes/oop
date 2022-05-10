//
// Created by dev on 5/8/22.
//

#ifndef INC_3_INTERACTOR_H
#define INC_3_INTERACTOR_H

#include <functional>
#include <utility>
#include "logic.h"

using callback_t = std::function<void(const std::string& msg)>;

enum class SelectedObjectType
{
	None,
	VisibleObject,
	Camera,
};


class Interactor
{
private:
	std::shared_ptr<Logic> logic;
	std::function<void(const std::string& msg)> update_callback;
	SelectedObjectType selected_type = SelectedObjectType::Camera;
	int selected_id = 0;
	void handle_key_with_vision_object(int key);
	void handle_key_with_camera_object(int key);
	void handle_command_select(std::stringstream& command);
	void handle_command_load(std::stringstream& command);
	void handle_command_create(std::stringstream& command);
	void help();

public:
	explicit Interactor(callback_t update_status_);
	void handle_key(int key);
	void handle_command(const std::string& command);

};

#endif //INC_3_INTERACTOR_H
