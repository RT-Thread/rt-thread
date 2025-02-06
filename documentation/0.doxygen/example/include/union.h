#ifndef _DOXYGEN_EXAMPLE_UNION_H_
#define _DOXYGEN_EXAMPLE_UNION_H_

/**
 * @page page_howto_union How to write doxygen documentation for union.
 *
 * A comment block before the union definition is recommended to
 * describe the general information of the union type. In the
 * comment block, a `@brief` is required, other commands (such as `@note`)
 * are optional.
 *
 * To describe the values of the union, document is recommended
 * to be put after each value.
 *
 * See
 * <a href="https://github.com/RT-Thread/rt-thread/blob/master/documentation/0.doxygen/example/include/union.h">documentation/0.doxygen/example/include/union.h</a>
 * for example.
 */

/**
 * @addtogroup group_doxygen_example
 */

/** @{ */

/**
 * @brief Brief description of this union
 */
union doxygen_example_union
{
    int    v1; /**< description for v1 */
    double v2; /**< description for v2 */
};

/** @} */

#endif /* _DOXYGEN_EXAMPLE_UNION_H_ */
