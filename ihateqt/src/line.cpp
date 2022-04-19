//
// Created by dev on 04/04/2022.
//
#include "inc/line.h"
#include <cstring>


// ok
errc line_from_obj_string(line &self, const big_string &in)
{
	errc ec = errc::ok;
	line temp_line;
	small_string line_type = "";
	if (sscanf(
			in.buf,
			"%s %d %d",
			line_type,
			&temp_line.first,
			&temp_line.second
	) != 3)
		ec = errc::bad_from_string_read;
	if (strcmp(line_type, "l") != 0)
		ec = errc::bad_from_string_read;

	if (ec == errc::ok)
		self = temp_line;
	return ec;
}

errc line_to_obj_string(big_string &out, const line &self)
{
	sprintf(out.buf, "l %d %d", self.first, self.second);
	return errc::ok;
}

errc line_flush(FILE *file, line &l)
{
	big_string buffer;
	errc ec = line_to_obj_string(buffer, l);
	if (ec == errc::ok)
		fprintf(file, "%s\n", buffer.buf);
	return ec;
}

errc scene_draw_line(domain_scene scene, vec4 point1, vec4 point2)
{
	double x1 = point1.components[0];
	double y1 = point1.components[1];
	double x2 = point2.components[0];
	double y2 = point2.components[1];
	scene_draw_line(scene, x1, y1, x2, y2);
	return errc::ok;
}
