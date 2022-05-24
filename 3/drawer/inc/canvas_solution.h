//
// Created by dev on 22/05/2022.
//

#ifndef INC_3_CANVAS_SOLUTION_H
#define INC_3_CANVAS_SOLUTION_H

#include <memory>
#include "base_canvas.h"
#include "qt_canvas.h"
#include "canvas_factory.h"

enum class CanvasType
{
	QtCanvas
};

class CanvasSolution
{
public:

	template<typename... Args>
	static std::unique_ptr<ICanvas> create(CanvasType type, Args &&... args)
	{
		std::unique_ptr<CanvasFactory> canvas_factory = nullptr;
		if (type == CanvasType::QtCanvas)
			canvas_factory = std::make_unique<QtCanvasFactory>(std::forward<Args>(args)...);
		return canvas_factory->create();
	}
};


#endif //INC_3_CANVAS_SOLUTION_H
