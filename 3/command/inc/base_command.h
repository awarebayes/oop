//
// Created by dev on 5/7/22.
//

#ifndef INC_3_BASE_COMMAND_H
#define INC_3_BASE_COMMAND_H

class Command
{
public:
	Command() = default;
	virtual ~Command() = default;
	virtual void exec() = 0;
};

#endif //INC_3_BASE_COMMAND_H
