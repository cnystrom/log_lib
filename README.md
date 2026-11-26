# log_lib: tiny logging to a file or stdout

Version 1.1 (2026). Split from NewIO 0.12, https://github.com/cnystrom/newio

## Versions

- **1.0:** original code as published in NewIO 0.12 (tag `v1.0`).
- **1.1:** this release, with the fixes listed below. See `CHANGES.md`.

log_lib is NewIO's logger, renamed. It writes `printf`-style messages to a
log file, or to stdout when asked, and flushes after every message.

**Original name:** this library was `nio_log` in NewIO (`nio_log.c`,
`nio_log.h`, functions `nio_log_*`). The files and functions are now
`log_lib`. `log_lib.h` keeps the old `nio_log_*` names as macros, so code
written for NewIO builds unchanged once it includes `log_lib.h`. Define
`LOG_LIB_NO_NIO_COMPAT` before the include to turn the old names off.

## API

From `log_lib.h`:

| Function (old NewIO name) | What it does |
|---|---|
| `void log_lib_use_stdout(int b)` (`nio_log_use_stdout`) | `TRUE` sends all output to stdout; `log_lib_open()` then does nothing. |
| `int log_lib_open(const char *pathname)` (`nio_log_open`) | Opens (truncates) the log file. Returns `TRUE` on success. |
| `void log_lib_close(void)` (`nio_log_close`) | Closes the log file. Later messages are dropped until the next open. |
| `void log_lib_print(const char *format, ...)` (`nio_log_print`) | Writes a formatted message. |
| `void log_lib_error(const char *func_name, const char *format, ...)` (`nio_log_error`) | Writes `func_name` followed by a formatted message. |
| `void log_lib_dump(char *s)` (`nio_log_dump`) | Declared, but its body is commented out in NewIO 0.12, so do not call it. |

If nothing is open and stdout is off, messages are dropped.
`nio_types.h` (copied unchanged from NewIO) supplies `PUBLIC`, `PRIVATE`,
`TRUE`, `FALSE` and the small integer types. `log_lib_version.h` defines
`LOG_LIB_VERSION` ("1.1") and `LOG_LIB_ORIGIN`.

## Dependencies

None. Only the C library.

## Build

```sh
make            # builds log_lib.a
make test       # builds and runs test_log_lib
make CC=clang test
make clean
```

## License

LGPL 2.1 or later, the same as NewIO. See `LICENSE` (GNU LGPL 2.1). `COPYING`
holds the GNU GPL 2, as in NewIO. Copyright Chris Nystrom; see the header of
each file for its years.

## Origin

Split from NewIO 0.12, https://github.com/cnystrom/newio (tag `newio-0.12`,
commit `ce54c5b`), directory `common/nio_log/`. The library code is Chris
Nystrom's original, copied unchanged except for the lines listed under
"Changes from NewIO" below.

Contact: Chris Nystrom <cnystrom@gmail.com>

## Changes from NewIO

- Renamed `nio_log.c` to `log_lib.c` and `nio_log.h` to `log_lib.h`, and
  replaced `nio_log` with `log_lib` in them: `log_lib.h` lines 3 and 35-41,
  `log_lib.c` lines 3, 32, 38, 43, 50, 58, 68, 95, 117 and 138 (95 and 117 are
  inside commented-out code). `Makefile` lines 6 and 13 likewise.
- `log_lib.h:33`: `#include "../nio_types.h"` became `#include "nio_types.h"`
  (a copy of NewIO's `common/nio_types.h` is included).
- `log_lib.h:43-51`: added the `nio_log_*` compatibility macros.
- `log_lib.c:144` and `:157`: `printf(func_name)` and
  `fprintf(pFile, func_name)` became `printf("%s", func_name)` and
  `fprintf(pFile, "%s", func_name)`. clang warned (`-Wformat-security`): a
  `%` in a function name would have been read as a format.
- `log_lib.c:62`: bug fix, see "Fixed in 1.1".
- Removed two old personal contact lines (a web-log URL and a chat handle) from the file headers, at Chris's request (2026). The rest of each header and the authorship are unchanged, so header-area line numbers are 2 lower than in NewIO.
- `Makefile:28`: `-I..` became `-I.`.
- Added `log_lib_version.h`, `test_log_lib.c`, a `make test` target at the
  end of the `Makefile`, this README, `LICENSE` and `COPYING`.

## Fixed in 1.1

- **`log_lib_close()` didn't reset its file pointer** (`log_lib.c:62`). A
  print or a second close after `log_lib_close()` used the closed `FILE`.
  It now sets the pointer to `NULL`, so later messages are dropped until the
  next `log_lib_open()`. Tested in `test_log_lib.c`.

## Known issues

Kept as in NewIO 0.12:

- `log_lib.h` has no include guard. Including it twice is harmless.
