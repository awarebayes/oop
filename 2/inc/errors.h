//
// Created by dev on 4/16/22.
//

#ifndef LAB2_ERRORS_H
#define LAB2_ERRORS_H

class BaseError : public std::exception
{
public:
	explicit BaseError(
			const std::string &filename,
			const std::string &classname,
			const int line,
			const char *time,
			const std::string &info)
	{
		msg = "In: " + filename +
		      "\n inside: " + classname +
		      "\nat line: " + std::to_string(line) +
		      "\nat: " + time +
		      "\noccured: " + info;
	}

	[[nodiscard]] const char *what() const noexcept override
	{
		return msg.c_str();
	}

private:
	std::string msg{};
};

class AlreadyInSetError : public BaseError
{
public:
	AlreadyInSetError(
			const std::string &filename,
			const std::string &classname,
			const int line,
			const char *time,
			const std::string &info = "Element was already in set"
	) : BaseError(filename, classname, line, time, info)
	{
	}
};


class NotInSetError : public BaseError
{
public:
	NotInSetError(
			const std::string &filename,
			const std::string &classname,
			const int line,
			const char *time,
			const std::string &info = "Element was not in set"
	) : BaseError(filename, classname, line, time, info)
	{
	}
};


class IterationStoppedError : public BaseError
{
public:
	IterationStoppedError(
			const std::string &filename,
			const std::string &classname,
			const int line,
			const char *time,
			const std::string &info = "Element was not in set"
	) : BaseError(filename, classname, line, time, info)
	{
	}
};

#endif //LAB2_ERRORS_H
