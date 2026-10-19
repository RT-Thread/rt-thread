/*
 * ATOMIC_VAR_INIT was removed from <stdatomic.h> in C17. Newer Xtensa
 * toolchains (GCC 15+) default to a mode where the macro is gone, while
 * the vendored ESP-IDF still uses it in driver/spi_common.c. Provide the
 * historical expansion so both GCC 12 (CI) and GCC 15 (local) build.
 */
#ifndef ATOMIC_VAR_INIT
#define ATOMIC_VAR_INIT(value) (value)
#endif
