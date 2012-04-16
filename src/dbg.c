/**
 * Copyright (c) 2006 LxDE Developers, see the file AUTHORS for details.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <time.h>
#include <stdbool.h>
#include <stdarg.h>

#include "dbg.h"

int log_level = LOG_WARN;

void dbg(char const* fmt, ...)
{
	static struct timespec ta = {};
	struct timespec tb;
	va_list ap;

	clock_gettime(CLOCK_MONOTONIC, &tb);

	bool wrap = tb.tv_nsec < ta.tv_nsec ? true : false;
	fprintf(stderr, "%ld.%09ld (%ld.%09ld): ", tb.tv_sec, tb.tv_nsec,
			tb.tv_sec - ta.tv_sec - (wrap ? 1 : 0),
			tb.tv_nsec - ta.tv_nsec + (wrap ? 1000000000 : 0));

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	ta = tb;
}
