//
// Created by dev on 22/05/2022.
//

#ifndef INC_3_CANVAS_SOLUTION_H
#define INC_3_CANVAS_SOLUTION_H

#include <memory>
#include "base_canvas.h"
#include "qt_canvas.h"

enum class CanvasType
{
	QtCanvas
};

class CanvasSolution
{
	static std::unique_ptr<Canvas> create(CanvasType type);
};



#endif //INC_3_CANVAS_SOLUTION_H
