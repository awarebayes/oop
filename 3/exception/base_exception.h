//
// Created by dev on 5/17/22.
//

#ifndef INC_3_BASE_EXCEPTION_H
#define INC_3_BASE_EXCEPTION_H

#include <exception>
#include <string>


class BaseException : public std::exception {
protected:
	std::string error_msg;

public:
	BaseException(const std::string &file, const int line, const std::string &err_msg = "No error message") {
		time_t curr_time = time(nullptr);
		auto local_time = localtime(&curr_time);
		this->error_msg =
				err_msg + "\nFile: " + file + "\nLine: " + std::to_string(line) + "\nTime: " + asctime(local_time);
	}

	[[nodiscard]] const char *what() const noexcept override {
		return this->error_msg.c_str();
	}
};

#endif //INC_3_BASE_EXCEPTION_H
