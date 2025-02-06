#ifndef _DOXYGEN_EXAMPLE_MACRO_H_
#define _DOXYGEN_EXAMPLE_MACRO_H_

/**
 * @page page_howto_macro How to write doxygen documentation for macro.
 *
 * There are two typical types of macro definitions.
 *
 * - One is to define constant macros. For this type of macro, we
 *   recommend putting documentation after members. See `DOXYGEN_EXAMPLE_CONST_A`
 *   and `DOXYGEN_EXAMPLE_CONST_B` in
 *   <a href="https://github.com/RT-Thread/rt-thread/blob/master/documentation/0.doxygen/example/include/macro.h">documentation/0.doxygen/example/include/macro.h</a>
 *   for exmaple.
 *
 * - The other is to define macros with parameters. For this type of
 *   macro, we recommend using a method similar to documenting for
 *   functions, that is, writing comment block before the macro definition.
 *   More details please see @ref page_howto_function
 *   See `DOXYGEN_EXAMPLE_ABS` in
 *   <a href="https://github.com/RT-Thread/rt-thread/blob/master/documentation/0.doxygen/example/include/macro.h">documentation/0.doxygen/example/include/macro.h</a>
 *   for example.
 */

/**
 * @addtogroup group_doxygen_example
 */

/** @{ */

#define DOXYGEN_EXAMPLE_CONST_A 100 /**< Description of macro const A */
#define DOXYGEN_EXAMPLE_CONST_B 200 /**< Description of macro const B */

/**
 * @brief Computes the absolute value of its argument @a x.
 *
 * @param[in] x input value.
 *
 * @return absolute value of @a x.
 */
#define DOXYGEN_EXAMPLE_ABS(x) (((x)>0)?(x):-(x))

/** @} */

#endif
