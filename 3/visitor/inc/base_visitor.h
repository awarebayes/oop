//
// Created by dev on 5/3/22.
//

#ifndef INC_3_BASE_VISITOR_H
#define INC_3_BASE_VISITOR_H

class ICamera;
class SceneGroup;
class MeshModelReference;
class Scene;
class LightSource;

class Visitor
{
public:
	virtual void visit(ICamera &camera) = 0;
	virtual void visit(LightSource &light) = 0;
	virtual void visit(SceneGroup &group) = 0;
	virtual void visit(MeshModelReference &ref) = 0;
	virtual void visit(Scene &scene) = 0;
};

class Visitable
{
public:
	virtual void accept(Visitor &visitor) = 0;
};

#endif //INC_3_BASE_VISITOR_H
