/******************************************************************************
 *
 *    log_lib.h
 *
 *    Copyright (C) 2005-2007  Chris Nystrom
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU Lessor General Public License as published
 *    by the Free Software Foundation; either version 2.1 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but without any warranty whatsoever.
 *
 *    For more license information see:
 *
 *      http://www.gnu.org/copyleft/lessor.html
 *
 *    Contact Author at:
 *
 *    Chris Nystrom
 *
 *    E-Mail: cnystrom@newio.org
 *
 *    Soli Deo Gloria
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "nio_types.h"

	PUBLIC void log_lib_use_stdout(int b);
	PUBLIC int log_lib_open(const char *pathname);
	PUBLIC void log_lib_close(void);
	PUBLIC void log_lib_print(const char *format, ...);
	PUBLIC void log_lib_error(const char *func_name,
				  const char *format, ...);
	PUBLIC void log_lib_dump(char *s);

/* log_lib was called nio_log in NewIO. These keep the old names working. */
#ifndef LOG_LIB_NO_NIO_COMPAT
#define nio_log_use_stdout	log_lib_use_stdout
#define nio_log_open		log_lib_open
#define nio_log_close		log_lib_close
#define nio_log_print		log_lib_print
#define nio_log_error		log_lib_error
#define nio_log_dump		log_lib_dump
#endif

#ifdef __cplusplus
}
#endif
