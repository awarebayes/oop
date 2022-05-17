//
// Created by dev on 5/1/22.
//

#ifndef INC_3_SCENE_OBJECT_H
#define INC_3_SCENE_OBJECT_H
#include <utility>
#include <vector>
#include <map>

#include "math/inc/transformation.h"
#include "visitor/inc/base_visitor.h"

class ISceneObject;

using ObjectMap = std::map<int, std::shared_ptr<ISceneObject>>;
using Iterator = ObjectMap::iterator;
using ConstIterator = ObjectMap::const_iterator;

class ISceneObject : public Visitable
{
private:
	std::shared_ptr<Transformation> transform = std::make_shared<Transformation>();
public:
	ISceneObject() = default;
	virtual ~ISceneObject() = default;

	virtual bool is_visible() { return false; };
	virtual bool is_grouped() {return false;};

	// visitor
	void accept(Visitor& v) override = 0;

	// transform
	virtual std::shared_ptr<Transformation> get_transform() {return transform;};
	virtual void set_transform(std::shared_ptr<Transformation> transform_) {transform = std::move(transform_);};

	// composite
	virtual int add_object(const std::shared_ptr<ISceneObject>& object) { return false; };
	virtual bool remove_object(const Iterator &iter) { return false; };
};

class VisibleObject : public ISceneObject
{
public:
	VisibleObject() = default;
	bool is_visible() override {return true;};
	~VisibleObject() override = default;

};

class InvisibleObject : public ISceneObject
{
public:
	InvisibleObject() = default;
	~InvisibleObject() override = default;
};

#endif //INC_3_SCENE_OBJECT_H
