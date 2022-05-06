//
// Created by dev on 5/3/22.
//

#ifndef INC_3_BASE_VISITOR_H
#define INC_3_BASE_VISITOR_H

class Camera;
class VisibleGroup;
class VisibleObject;
class Scene;
class MeshModel;

class Visitor
{
public:
	virtual void visit(Camera &camera) = 0;
	virtual void visit(VisibleGroup &group) = 0;
	virtual void visit(MeshModel &model) = 0;
	virtual void visit(VisibleObject &object) = 0;
	virtual void visit(Scene &scene) = 0;
};

class Visitable
{
public:
	virtual void accept(Visitor &visitor) = 0;
};

#endif //INC_3_BASE_VISITOR_H
