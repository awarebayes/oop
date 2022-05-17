//
// Created by dev on 5/17/22.
//

#ifndef INC_3_LOGIC_EXCEPTIONS_H
#define INC_3_LOGIC_EXCEPTIONS_H
#include "base_exception.h"

class LastCameraRemoveError : public BaseException {
public:
	explicit LastCameraRemoveError(const std::string &file, const int line, const std::string &msg) : BaseException(file, line, msg) {
		this->error_msg = "LastCameraRemoveError: " + this->error_msg;
	}
};

#endif //INC_3_LOGIC_EXCEPTIONS_H
