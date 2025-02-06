#ifndef _DOXYGEN_EXAMPLE_ENUM_H_
#define _DOXYGEN_EXAMPLE_ENUM_H_

/**
 * @page page_howto_enum How to write doxygen documentation for enumeration.
 *
 * A comment block before the enumeration definition is recommended to
 * describe the general information of the enumeration type. In the
 * comment block, a `@brief` is required, other commands (such as `@note`)
 * are optional.
 *
 * To describe the values of the enumeration, document is recommended
 * to be put after each value.
 *
 * See
 * <a href="https://github.com/RT-Thread/rt-thread/blob/master/documentation/0.doxygen/example/include/enum.h">documentation/0.doxygen/example/include/enum.h</a>
 * for example.
 */

/**
 * @addtogroup group_doxygen_example
 */

/** @{ */

/**
 * @brief Brief description of this enumeration
 */
enum doxygen_example_enum
{
    V1, /**< description for value 1 */
    V2, /**< description for value 2 */
};

/** @} */

#endif /* _DOXYGEN_EXAMPLE_ENUM_H_ */
