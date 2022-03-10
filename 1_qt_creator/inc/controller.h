//
// Created by dev on 3/6/22.
//

#ifndef INC_1_QT_CREATOR_CONTROLLER_H
#define INC_1_QT_CREATOR_CONTROLLER_H

#include "model.h"

enum class ControllerCommandType
{
	load_object,
	load_default_cube,
	save_object,
	mutate_transformations,
	exit,
	default_view,
};


union ControllerCommandArgs{
	TransformMutation transform_mutation;
};

struct ControllerCommand
{
	ControllerCommandArgs args;
	ControllerCommandType type;
};

struct Controller
{
private:
	struct Model &model_;

public:
	explicit Controller(Model &model);

	void mutate_transformations(const TransformMutation &mut) const;

	[[nodiscard]] const Mesh3D &get_current_object() const;

	[[nodiscard]] const Transformations &get_transformations() const;

	void set_appropriate_transformations();

	void load_object();

	void load_default_cube();

	void save_object();

	static void show_error_dialog(errc code);
};

void entry_point(Controller &controller, const struct ControllerCommand &command);

#endif //INC_1_QT_CREATOR_CONTROLLER_H
