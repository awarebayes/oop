//
// Created by dev on 5/7/22.
//

#include <command/inc/scene_command.h>
#include <manager/inc/test_draw_manager.h>

void RenderSceneCommand::exec()
{
	auto draw_manager = TestDrawManagerCreator().get();
	draw_manager->draw_scene();
}

