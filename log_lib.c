/******************************************************************************
 *
 *    log_lib.c
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

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "log_lib.h"

PRIVATE FILE *pFile = NULL;

PRIVATE int use_stdout = FALSE;

PUBLIC void log_lib_use_stdout(int b)
{
	use_stdout = b;
}

PUBLIC int log_lib_open(const char *pathname)
{
	if (use_stdout) {
		return (TRUE);
	}

	if (pFile != NULL) {
		log_lib_close();
	}

	pFile = fopen(pathname, "w+");

	return (pFile != NULL);
}

PUBLIC void log_lib_close(void)
{
	if (pFile != NULL) {
		fclose(pFile);
		pFile = NULL;	/* FIX (1.0, 2026): no use after close */
	}
}

#define DEBUG

PUBLIC void log_lib_print(const char *format, ...)
{
#ifdef DEBUG
	va_list ap;

	if (use_stdout) {
		va_start(ap, format);
		vprintf(format, ap);
		va_end(ap);

		fflush(stdout);

		return;
	}

	if (pFile != NULL) {

		va_start(ap, format);
		vfprintf(pFile, format, ap);
		va_end(ap);

		fflush(pFile);
	}
#endif
}

/*
PUBLIC void log_lib_dump(char *s)
{
	int i;
	int len;
	char c;

	len = strlen(s);

	printf("---\n");

	for (i = 0; i < len; i++) {

		c = *s++;

		printf("%d. %d %c\n", i, c, c);
	}

	printf("---\n");
}
*/

/*
PUBLIC void log_lib_nprint(char *s, int num)
{
	int i;

	for (i = 0; i < num; i++) {
		if (use_stdout) {
			putc((int) s++, stdout);
		}
		else {
			putc((int) s++, pFile);
		}
	}

	if (use_stdout) {
		putc(0, stdout);
	} else {
		putc(0, pFile);
	}
}
*/

PUBLIC void log_lib_error(const char *func_name, const char *format, ...)
{
	va_list ap;

	if (use_stdout) {

		printf("%s", func_name);

		va_start(ap, format);
		vprintf(format, ap);
		va_end(ap);

		fflush(stdout);

		return;
	}

	if (pFile != NULL) {

		fprintf(pFile, "%s", func_name);

		va_start(ap, format);
		vfprintf(pFile, format, ap);
		va_end(ap);

		fflush(pFile);
	}
}
