/**
 * @page page_howto_function How to write doxygen documentation for function.
 *
 * Function comments can be placed in the header file (before the
 * function declaration) OR in the source file (before the function
 * definition).
 *
 * The advantage of placing it in the header file is that we generally
 * think that the header file is the place to declare the API, but the
 * problem is that when a module has many API extern functions, if the
 * comments are placed in the header file, the header file will be very
 * long. You can imagine that for a module with many APIs and many
 * comments, the header file will be full of large green comments, and
 * the function declaration part is mixed in the middle and difficult
 * to distinguish. And if you want to fully understand which extern
 * functions this module exports, you need to scroll a long file for a
 * long time to get a general idea. Especially for RTT, see `include/rtthread.h`
 * as an example.
 *
 * Putting the comment in the source file can avoid the above problems.
 * For developers, it is also convenient to read the comments together with
 * the code implementation. The disadvantage is that it would be different
 * from the function side, from other types, such as structures, i.e. the API
 * comments of functions need to be read in the source file instead of directly
 * in the header file.
 *
 * Comprehensive consideration can be combined with the actual situation.
 * For example, if there are too many API functions in a header file, it is
 * recommended to put the function comments in the source file.
 *
 * So, it is **strongly recommended** to put comments in the source file when
 * writing new functions or annotating functions.
 *
 * To documenting for functions, a comment block before the function
 * declaraion/definition is recommended to describe the general information
 * of the function. In the comment block, a `@brief` is required, a `@return`
 * is also required no matter if the function return values or not. `@param` is
 * required if any, and if it is provided, direction [in]/[out]/[in,out] should
 * be provide together. Other commands (such as `@note`) are optional.
 *
 * If you feel that the description of `@brief` is not enough, you
 * can add a detailed description part, which is also optional.
 *
 * See
 * <a href="https://github.com/RT-Thread/rt-thread/blob/master/documentation/0.doxygen/example/src/function.c">documentation/0.doxygen/example/src/function.c</a>
 * for example.
 *
 * <a href="https://github.com/RT-Thread/rt-thread/blob/master/documentation/0.doxygen/example/src/function.h">documentation/0.doxygen/example/src/function.h</a> is an example of the header file where we just declare the API without doxygen documentation.
 */

/**
 * @addtogroup group_doxygen_example
 */

/** @{ */

/**
 * @brief Brief description for the function
 *
 * Detailed description starts here, one line or multiple lines.
 * Blah blah blah...
 *
 * @param[in] a Description of param a
 *
 * @param[in] b Description of param b
 *
 * @return void
 *
 * @note This is a note for this structure, blah blah blah...
 */
void doxygen_example_func_foo(int a, int b)
{
    return;
}

/**
 * @brief Brief description for the function
 *
 * Detailed description starts here, one line or multiple lines.
 * Blah blah blah...
 *
 * @param[in] a Description of param a
 *
 * @param[out] b Description of param b
 *
 * @return the return value, 0 for success, -1 for failure
 *
 * @note This is a note for this structure, blah blah blah...
 */
int doxygen_example_func_bar(int a, int* b)
{
    return 0;
}

/** @} */
