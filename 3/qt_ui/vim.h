//
// Created by dev on 5/8/22.
//

#ifndef INC_3_VIM_H
#define INC_3_VIM_H

#include <functional>
#include <utility>
#include "logic.h"
using callback_t = std::function<void(const std::string& msg)>;

enum class VimStateEnum
{
	None,
	Normal,
	Object,
	Camera,
};

class VimState
{
public:
	virtual void handle_key(int key) = 0;
};

class VimStateNormal : public VimState
{
public:
	void handle_key(int key) override {};
};

class VimStateObject : public VimState
{
private:
	std::shared_ptr<Logic> logic;
	int selected_object = -1; // fixme
public:
	explicit VimStateObject(std::shared_ptr<Logic> logic_, callback_t callback);
	callback_t update_callback;
	void handle_key(int key) override;
	void handle_find(int key);
	void start_find();
	void reset_find_fail();
	void reset_find_success();
};

class VimStateCamera : public VimState
{
private:
	std::shared_ptr<Logic> logic;
	callback_t update_callback;
public:
	explicit VimStateCamera(std::shared_ptr<Logic> logic_, callback_t callback);
	void handle_key(int key) override {};
};

class Vim
{
private:
	VimStateEnum state_enum = VimStateEnum::Normal;
	std::unique_ptr<VimState> state = std::make_unique<VimStateNormal>();
	std::shared_ptr<Logic> logic;
	std::function<void(const std::string& msg)> update_callback;

	void go_to_normal();
	void go_to_object();
	void go_to_camera();
	void handle_key_in_normal(int key);

public:
	explicit Vim(callback_t update_status_);
	void handle_key(int key);

};

#endif //INC_3_VIM_H
