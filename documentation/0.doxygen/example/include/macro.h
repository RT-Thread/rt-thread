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
 *   for code exmaple.
 *
 * - The other is to define macros with parameters. For this type of
 *   macro, we recommend using a method similar to documenting for
 *   functions, that is, writing comment block before the macro definition.
 *   More details please see @ref page_howto_function
 *   See `DOXYGEN_EXAMPLE_ABS` in
 *   <a href="https://github.com/RT-Thread/rt-thread/blob/master/documentation/0.doxygen/example/include/macro.h">documentation/0.doxygen/example/include/macro.h</a>
 *   for code example.
 *
 * We often categorize macros in our code. Similarly, when writing doxygen
 * comments for these categorized macros, we can also group them. See
 * `DOXYGEN_EXAMPLE_GROUP_A_X`/`DOXYGEN_EXAMPLE_GROUP_A_Y` and
 * `DOXYGEN_EXAMPLE_GROUP_B_X`/`DOXYGEN_EXAMPLE_GROUP_B_Y` in
 * <a href="https://github.com/RT-Thread/rt-thread/blob/master/documentation/0.doxygen/example/include/macro.h">documentation/0.doxygen/example/include/macro.h</a>
 * for code example.
 *
 * See @ref group_doxygen_example_macro for html output.
 */

 /**
 * @defgroup group_doxygen_example_macro Doxygen Example of Macro
 *
 * @ingroup group_doxygen_example
 *
 * @brief Doxygen Example of Macro.
 *
 * @{
 */

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

/**
 * @defgroup group_doxygen_example_macro_group_a Group A of Macros
 *
 * @brief Doxygen Example of Macros grouped in A.
 *
 * @{
 */
#define DOXYGEN_EXAMPLE_GROUP_A_X 0x0000 /**< Description of X in group A */
#define DOXYGEN_EXAMPLE_GROUP_A_Y 0x0001 /**< Description of Y in group A */
/** @} */

/**
 * @defgroup group_doxygen_example_macro_group_b Group B of Macros
 *
 * @brief Doxygen Example of Macros grouped in B
 *
 * @{
 */
#define DOXYGEN_EXAMPLE_GROUP_B_X 0x0000 /**< Description of X in group B */
#define DOXYGEN_EXAMPLE_GROUP_B_Y 0x0001 /**< Description of Y in group B */
/** @} */

/** @} */

#endif
