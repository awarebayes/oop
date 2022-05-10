//
// Created by dev on 5/8/22.
//

#ifndef INC_3_SCENE_META_H
#define INC_3_SCENE_META_H

#include <string>
#include <map>
#include <set>

class SceneMeta
{
private:
	int n_cameras{};
	int active_camera{};
	int selected_object_id;
	std::map<int, std::string> object_map{};
	std::set<int> camera_ids;
public:
	void add_object(int object_id, const std::string& meta);
	void remove_object(int object_id);
	void set_camera(int camera);
	void add_camera(int camera);
	std::map<int, std::string> &get_objects();
	std::set<int> &get_cameras();
	int get_selected();
};


#endif //INC_3_SCENE_META_H
