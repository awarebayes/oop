//
// Created by dev on 5/1/22.
//

#ifndef INC_3_CAMERA_H
#define INC_3_CAMERA_H
#include "scene_object.h"

class Camera : public InvisibleObject
{
private:
	Vector<3> position;
	Vector<3> look_direction;

	Matrix<4> viewport();

public:
	std::unique_ptr<Transformation> look_at_object(VisibleObject &object) const;
	void change_look_direction(float x, float y, float z);
	void change_position(float x, float y, float z);
	[[nodiscard]] Matrix<4> get_matrix() const;
	void accept(Visitor& v) override;
};

#endif //INC_3_CAMERA_H
