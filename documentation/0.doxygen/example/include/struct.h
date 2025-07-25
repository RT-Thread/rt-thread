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
 * See `struct dogygen_example_struct` for example.
 *
 * If the structure member is too long (this often happens when the structure
 * member is a callback function), when the comment is written after the member,
 * it will make the code line too long. In this case, we can also put the comment
 * before the member. See `struct dogygen_example_struct_another` for example.
 *
 * Going a step further, for this kind of structure whose members are callback
 * functions, we can describe the members in style for functions, it is more
 * complicated and contains more content. It is useful when we want to describe
 * the parameters and return values ​​of the callback function in more detail.
 * See `struct dogygen_example_struct_another2` for example.
 *
 * See
 * <a href="https://github.com/RT-Thread/rt-thread/blob/master/documentation/0.doxygen/example/include/struct.h">documentation/0.doxygen/example/include/struct.h</a>
 * for code example.
 *
 * See @ref group_doxygen_example_struct for html output.
 */

/**
 * @defgroup group_doxygen_example_struct Doxygen Example of Structure
 *
 * @ingroup group_doxygen_example
 *
 * @brief Doxygen Example of Structure.
 *
 * @{
 */

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
    /** Some documentation for member 'm1'... */
    int (*m1)(int *param1, int param2, int param3, int param4);
    /** Some documentation for member 'm2'... */
    int (*m2)(int *param1, int param2, int param3, int param4);
};

/**
 * @brief Brief description this structure
 *
 * Detailed description starts here, one line or multiple lines.
 * Blah blah blah...
 *
 * @note This is a note for this structure, blah blah blah...
 */
struct dogygen_example_struct_another2
{
    /**
     * @brief Brief description of m1
     * @param param1 The first param.
     * @param param2 The second param.
     * @param param3 The third param.
     * @param param4 The fourth param.
     * @return the operation status, 0 on successful
     */
    int (*m1)(int *param1, int param2, int param3, int param4);
    /**
     * @brief Brief description of m2
     * @param param1 The first param.
     * @param param2 The second param.
     * @param param3 The third param.
     * @param param4 The fourth param.
     * @return the operation status, 0 on successful
     */
    int (*m2)(int *param1, int param2, int param3, int param4);
};

/** @} */

#endif /* _DOXYGEN_EXAMPLE_STRUCT_H_ */
