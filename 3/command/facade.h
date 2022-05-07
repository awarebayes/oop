//
// Created by dev on 5/7/22.
//

#ifndef INC_3_FACADE_H
#define INC_3_FACADE_H

class RendererFacade
{
public:
	void exec(const std::shared_ptr<Command> &command) {command->exec();};
};

#endif //INC_3_FACADE_H
