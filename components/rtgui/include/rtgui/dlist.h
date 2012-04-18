/*
 * File      : dlist.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-16     Bernard      the first version
 * 2006-09-07     Bernard      move the kservice APIs to rtthread.h
 * 2007-06-27     Bernard      fix the rt_list_remove bug
 * 2012-02-25     Grissiom     move to rtgui/include/rtgui and some misc changes
 */

#ifndef __RTGUI_DLIST_H__
#define __RTGUI_DLIST_H__

/* This file is copied from kservice.h in RTT kernel. There are some differences:
 *     1, naming. Use rtgui_dlist_ prefix instead of rt_list.
 *     2, add rtgui_dlist_foreach for convenience.
 *     3, move the definition of list node into this file.
 *
 * Please keep both of the files synchronized when fixing bugs.
 */

#ifdef __cplusplus
extern "C" {
#endif

struct rtgui_dlist_node
{
	struct rtgui_dlist_node *next;	/* point to next node. */
	struct rtgui_dlist_node *prev;	/* point to prev node. */
};

/**
 * @brief initialize a list
 *
 * @param l list to be initialized
 */
rt_inline void rtgui_dlist_init(struct rtgui_dlist_node *l)
{
	l->next = l->prev = l;
}

/**
 * @brief insert a node after a list
 *
 * @param l list to insert it
 * @param n new node to be inserted
 */
rt_inline void rtgui_dlist_insert_after(struct rtgui_dlist_node *l, struct rtgui_dlist_node *n)
{
	l->next->prev = n;
	n->next = l->next;

	l->next = n;
	n->prev = l;
}

/**
 * @brief insert a node before a list
 *
 * @param n new node to be inserted
 * @param l list to insert it
 */
rt_inline void rtgui_dlist_insert_before(struct rtgui_dlist_node *l, struct rtgui_dlist_node *n)
{
	l->prev->next = n;
	n->prev = l->prev;

	l->prev = n;
	n->next = l;
}

/**
 * @brief remove node from list.
 * @param n the node to remove from the list.
 */
rt_inline void rtgui_dlist_remove(struct rtgui_dlist_node *n)
{
	n->next->prev = n->prev;
	n->prev->next = n->next;

	rtgui_dlist_init(n);
}

/**
 * @brief tests whether a list is empty
 * @param l the list to test.
 */
rt_inline int rtgui_dlist_isempty(const struct rtgui_dlist_node *l)
{
	return l->next == l;
}

/**
 * @brief get the struct for this entry
 * @param node the entry point
 * @param type the type of structure
 * @param member the name of list in structure
 */
#define rtgui_dlist_entry(node, type, member) \
    ((type *)((char *)(node) - (unsigned long)(&((type *)0)->member)))

/* the direction can only be next or prev. If you want to iterate the list in
 * normal order, use next. If you want to iterate the list with reverse order,
 * use prev.*/
#define rtgui_dlist_foreach(node, list, direction)	\
	for ((node) = (list)->direction; (node) != list; (node) = (node)->direction)

#ifdef __cplusplus
}
#endif

#endif
