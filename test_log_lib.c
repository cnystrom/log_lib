/* test_log_lib.c - exercises log_lib (2026). Run with `make test`. */

#include <stdio.h>
#include <string.h>
#include "log_lib.h"
#include "log_lib_version.h"

static int n_pass, n_fail;
#define CHECK(c) do { if (c) { n_pass++; printf("  ok   %s\n", #c); } \
	else { n_fail++; printf("  FAIL %s  (%s:%d)\n", #c, __FILE__, __LINE__); } } while (0)
#define DONE(name) do { printf("%s: %d passed, %d failed\n", name, n_pass, n_fail); \
	return n_fail ? 1 : 0; } while (0)

#define LOG_FILE "test_log_lib.log"

int main(void)
{
	char line[128];
	FILE *f;
	int n = 0;

	printf("log_lib %s (%s)\n", LOG_LIB_VERSION, LOG_LIB_ORIGIN);

	/* to a file */
	CHECK(log_lib_open(LOG_FILE) == TRUE);
	log_lib_print("print %d %s\n", 42, "abc");
	log_lib_error("func():", " error %d\n", 7);
	nio_log_print("old name %s\n", "works");	/* NewIO compat name */
	log_lib_close();

	f = fopen(LOG_FILE, "r");
	CHECK(f != NULL);
	if (f != NULL) {
		while (fgets(line, sizeof(line), f) != NULL) {
			n++;
			if (n == 1)
				CHECK(strcmp(line, "print 42 abc\n") == 0);
			if (n == 2)
				CHECK(strcmp(line, "func(): error 7\n") == 0);
			if (n == 3)
				CHECK(strcmp(line, "old name works\n") == 0);
		}
		fclose(f);
	}
	CHECK(n == 3);
	remove(LOG_FILE);

	/* 1.1 fix: printing or closing again after log_lib_close() used the
	 * closed FILE. Now it is dropped, and a new open works. */
	log_lib_print("dropped after close\n");
	log_lib_close();
	CHECK(log_lib_open(LOG_FILE) == TRUE);
	log_lib_print("kept\n");
	log_lib_close();
	f = fopen(LOG_FILE, "r");
	CHECK(f != NULL && fgets(line, sizeof(line), f) != NULL
	      && strcmp(line, "kept\n") == 0
	      && fgets(line, sizeof(line), f) == NULL);
	if (f != NULL)
		fclose(f);
	remove(LOG_FILE);

	/* to stdout */
	log_lib_use_stdout(TRUE);
	CHECK(log_lib_open("ignored-when-stdout") == TRUE);
	log_lib_print("  (stdout) print %d\n", 1);
	log_lib_error("  (stdout) func():", " error %d\n", 2);

	DONE("log_lib");
}
