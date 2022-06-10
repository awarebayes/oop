//
// Created by dev on 30/03/2022.
//
#include "inc/mishalib.h"

errc get_big_line(big_string &buffer, FILE *file)
{
	if (file == nullptr or buffer.length == 0)
		return errc::invalid_argument;
	fgets(buffer.buf, buffer.length, file);
	return errc::ok;
}

errc get_big_line_type(small_string  &line_type, const big_string &buffer)
{
	sscanf(buffer.buf, "%s", line_type);
	return errc::ok;
}