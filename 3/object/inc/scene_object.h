//
// Created by dev on 5/1/22.
//

#ifndef INC_3_SCENE_OBJECT_H
#define INC_3_SCENE_OBJECT_H
#include <utility>

#include "math/inc/transformation.h"
#include "visitor/inc/base_visitor.h"

class SceneObject : public Visitable
{
private:
	std::shared_ptr<Transformation> transform = std::make_shared<Transformation>();
public:
	SceneObject() = default;
	virtual bool is_visible() = 0;
	virtual bool is_mesh() = 0;
	virtual bool is_grouped() = 0;
	virtual bool is_reference() = 0;
	virtual ~SceneObject() = default;
	void accept(Visitor& v) override = 0;
	virtual std::shared_ptr<Transformation> get_transform() {return transform;};
	virtual void set_transform(std::shared_ptr<Transformation> transform_) {transform = std::move(transform_);};
};

class VisibleObject : public SceneObject
{
public:
	VisibleObject() = default;
	bool is_visible() override {return true;};
	bool is_mesh() override {return false;};
	bool is_grouped() override {return false;};
	bool is_reference() override {return false;};
	~VisibleObject() override = default;
	void accept(Visitor& v) override = 0;

};

class InvisibleObject : public SceneObject
{
public:
	InvisibleObject() = default;
	bool is_visible() override {return false;};
	bool is_mesh() override {return false;};
	bool is_grouped() override {return false;};
	bool is_reference() override {return false;};
	~InvisibleObject() override = default;
	void accept(Visitor& v) override = 0;
};

#endif //INC_3_SCENE_OBJECT_H
