//
// Created by dev on 5/17/22.
//

#ifndef INC_3_LOADER_EXCEPTIONS_H
#define INC_3_LOADER_EXCEPTIONS_H
#include "base_exception.h"

class FileError : public BaseException {
public:
	explicit FileError(const std::string &file, const int line, const std::string &msg) : BaseException(file, line, msg) {
		this->error_msg = "FileError: " + this->error_msg;
	}
};

class NoBuilderError : public BaseException {
public:
	explicit NoBuilderError(const std::string &file, const int line, const std::string &msg) : BaseException(file, line, msg) {
		this->error_msg = "Loader called with no builder: " + this->error_msg;
	}
};

#endif //INC_3_LOADER_EXCEPTIONS_H
