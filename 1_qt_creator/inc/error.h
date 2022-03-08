//
// Created by dev on 3/7/22.
//

#ifndef INC_1_QT_CREATOR_ERROR_H
#define INC_1_QT_CREATOR_ERROR_H

#include <map>

enum class errc
{
	ok,
	io_error,
	no_such_file_or_directory,
	bad_file_descriptor,
	invalid_argument,
	invalid_vertex_string_in_file,
	invalid_index_string_in_file,
	index_mismatch,
	bad_render_call,
	bad_from_string_read,
	bad_to_string,
};

const std::map<errc, std::string> error_map = {
		{ errc::ok,                            "ok" },
		{ errc::io_error,                      "io_error" },
		{ errc::no_such_file_or_directory,     "no_such_file_or_directory" },
		{ errc::bad_file_descriptor,           "bad_file_descriptor" },
		{ errc::invalid_argument,              "invalid_argument" },
		{ errc::invalid_vertex_string_in_file, "invalid_vertex_string_in_file" },
		{ errc::invalid_index_string_in_file,  "invalid_index_string_in_file" },
		{ errc::bad_render_call,               "bad_render_call" },
		{ errc::index_mismatch,                "index_mismatch" },
		{ errc::bad_from_string_read,          "bad_from_string_read" },
};


#endif //INC_1_QT_CREATOR_ERROR_H
