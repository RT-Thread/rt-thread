#ifndef _DOXYGEN_EXAMPLE_GROUPS_H_
#define _DOXYGEN_EXAMPLE_GROUPS_H_

/**
 * @page page_howto_groups How to use groups in doxygen documentation.
 *
 * Doxygen has three mechanisms to group things together. For RT-Thread
 * API documentation, we use 'topics' to create new page for each group.
 * On HTML browser, the topics pages are shown under the "Modules" in the
 * treeview on the left.
 *
 * To define a group, we use `@defgroup` command. The group name should be
 * prefixed with a "group_", and the group name should be unique. We can
 * define a group anywhere, not necessarily in the same file as the members
 * of the group. Generally, we define a group in a header file.
 *
 * To make an entity (structure, function etc. or another group) a member of
 * a speicific group, we can use `@ingroup` command and put the `@ingroup`
 * command inside its documentation block.
 *
 * To avoid putting `@ingroup` commands in the documentation for each member
 * you can use `@addtogroup` and group members together by the open marker
 * `@{` before the group and the closing marker `@}` after the group.
 *
 * See
 * <a href="https://github.com/RT-Thread/rt-thread/blob/master/documentation/0.doxygen/example/include/groups.h">documentation/0.doxygen/example/include/groups.h</a>
 * for example.
 *
 * More information can be found in the Doxygen manual:
 * <a href="https://www.doxygen.nl/manual/grouping.html">Grouping</a>.
 */

/**
 * @defgroup group_doxygen_example_sub Sub Group of Doxygen Example
 *
 * All members of this group will be displayed in one HTML page.
 *
 * @ingroup group_doxygen_example
 *
 * @brief Define a sub group of Doxygen Example.
 */

/**
 * @brief Brief description of this enumeration
 *
 * We use `@ingroup` to add this enum to the group_doxygen_example_sub separately.
 *
 * @ingroup group_doxygen_example_sub
 */
enum doxygen_example_enum_2
{
    V1, /**< description for value 1 */
    V2, /**< description for value 2 */
};

// This entity is not a member of any group.
#define DOXYGEN_EXAMPLE_CONST_E 300 /**< Description of macro const D */

/**
 * @addtogroup group_doxygen_example_sub
 */

/** @{ */

/*
 * DOXYGEN_EXAMPLE_CONST_C & DOXYGEN_EXAMPLE_CONST_D are close together, so
 * we can use `@addtogroup`, `@{` and `@}` to group them together.
 */
#define DOXYGEN_EXAMPLE_CONST_C 100 /**< Description of macro const C */
#define DOXYGEN_EXAMPLE_CONST_D 200 /**< Description of macro const D */

/** @} */

#endif /* _DOXYGEN_EXAMPLE_GROUPS_H_ */
