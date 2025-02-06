#ifndef _DOXYGEN_EXAMPLE_STRUCT_H_
#define _DOXYGEN_EXAMPLE_STRUCT_H_

/**
 * @page page_howto_struct How to write doxygen documentation for structure.
 *
 * We recommend the following approach:
 *
 * A comment block before the structure definition is recommended to
 * describe the general information of the structure type. In the
 * comment block, a `@brief` is required, other commands (such as `@note`)
 * are optional.
 *
 * If you feel that the description of `@brief` is not enough, you
 * can add a detailed description part, which is also optional.
 *
 * Put member comments inside the structure definition and after every member.
 *
 * See
 * <a href="https://github.com/RT-Thread/rt-thread/blob/master/documentation/0.doxygen/example/include/struct.h">documentation/0.doxygen/example/include/struct.h</a>
 * for example.
 */

/**
 * @addtogroup group_doxygen_example
 */

/** @{ */

/**
 * @brief Brief description this structure
 *
 * Detailed description starts here, one line or multiple lines.
 * Blah blah blah...
 *
 * @note This is a note for this structure, blah blah blah...
 */
struct dogygen_example_struct
{
    int m1; /**< Some documentation for member 'm1'...
             * Multiple lines ... Note the "multi-line" here refers
             * to the code. Whether it is displayed in multiple lines
             * on the specific HTML page depends on the browser rendering.
             *
             * @note We can also embed note for member 'm1'...
             */
    int m2; /**< Some documentation for member 'm2'... */
    int m3; /**< Some documentation for member 'm3'... */
    int m4; /**< Some documentation for member 'm4'... */
    int m5; /**< Some documentation for member 'm5'... */
};

/**
 * @brief Brief description this structure
 *
 * Detailed description starts here, one line or multiple lines.
 * Blah blah blah...
 *
 * @note This is a note for this structure, blah blah blah...
 */
struct dogygen_example_struct_another
{
    int m1; /**< Some documentation for member 'm1'...
             * Multiple lines ... Note the "multi-line" here refers
             * to the code. Whether it is displayed in multiple lines
             * on the specific HTML page depends on the browser rendering.
             *
             * @note We can also embed note for member 'm1'...
             */
    int m2; /**< Some documentation for member 'm2'... */
    int m3; /**< Some documentation for member 'm3'... */
    int m4; /**< Some documentation for member 'm4'... */
    int m5; /**< Some documentation for member 'm5'... */
};

/** @} */

#endif /* _DOXYGEN_EXAMPLE_STRUCT_H_ */
