//
// Created by dev on 5/7/22.
//

#ifndef INC_3_MODEL_REF_H
#define INC_3_MODEL_REF_H

#include <utility>

#include "object/inc/scene_object.h"

class MeshModelReference : public VisibleObject
{
private:
	std::shared_ptr<MeshModel> reference;
	std::shared_ptr<Transformation> proxy_transform = std::make_shared<Transformation>();
public:
	explicit MeshModelReference(std::shared_ptr<MeshModel>  ref) : reference(std::move(ref)) {};
	~MeshModelReference() override = default;
	bool is_reference() override {return true;};
	std::shared_ptr<MeshModel> deref() {return reference;};
	std::shared_ptr<Transformation> get_transform() override {return proxy_transform;};
	virtual void set_transform(std::shared_ptr<Transformation> transform_) {proxy_transform = std::move(transform_);};
	void accept(Visitor& v) override { v.visit(*this); };
};


#endif //INC_3_MODEL_REF_H
