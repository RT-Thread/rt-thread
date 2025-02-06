#ifndef _DOXYGEN_EXAMPLE_TYPEDEF_H_
#define _DOXYGEN_EXAMPLE_TYPEDEF_H_

/**
 * @page page_howto_typedef How to write doxygen documentation for typedef.
 *
 * It is recommended to use separate typedef statements rather
 * than a combination. That is:
 *
 * Recommended:
 *
 * ```c
 * struct S { ... };
 * typedef struct S S_t;
 * ```
 *
 * Not recommended:
 *
 * ```c
 * typedef struct S { ... } S_t;
 * ```
 *
 * The reason is we found that the former is more readable, and when we
 * write comment block with `@typedef`, the latter may
 * cause unexpceted behaviour for doxygen (as of version 1.9.1).
 *
 * See
 * <a href="https://github.com/RT-Thread/rt-thread/blob/master/documentation/0.doxygen/example/include/typedef.h">documentation/0.doxygen/example/include/typedef.h</a>
 * for example.
 */

#include "struct.h"
#include "enum.h"

/**
 * @addtogroup group_doxygen_example
 */

/** @{ */

/**
 * @typedef dogygen_example_struct_t
 * Alias of `struct dogygen_example_struct`.
 *
 * @typedef dogygen_example_struct_another_t
 * Alias of `struct dogygen_example_struct_another`.
 */
typedef struct dogygen_example_struct dogygen_example_struct_t;
typedef struct dogygen_example_struct_another dogygen_example_struct_another_t;

/**
 * @typedef doxygen_example_enum
 * Alias of `enum doxygen_example_enum`.
 */
typedef enum doxygen_example_enum doxygen_example_enum_t;

/** @} */

#endif /* _DOXYGEN_EXAMPLE_TYPEDEF_H_ */
