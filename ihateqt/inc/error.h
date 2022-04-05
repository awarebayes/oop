#ifndef __ERROR_H__
#define __ERROR_H__

#include <map>
#include <string>

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
	bad_command,
	invalid_transformations,
	transforms_not_found,
	bad_malloc,
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
		{ errc::bad_to_string,                 "bad_to_string" },
		{ errc::bad_command,                   "bad_domain_command" },
		{ errc::invalid_transformations,       "invalid_transformations" },
		{ errc::transforms_not_found,          "transforms_not_found" },
		{ errc::bad_malloc,                    "bad_malloc" },
};

#endif
