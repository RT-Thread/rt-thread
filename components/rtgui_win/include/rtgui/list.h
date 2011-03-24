/*
 * File      : list.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-16     Bernard      first version
 */
#ifndef __RTGUI_LIST_H__
#define __RTGUI_LIST_H__

#include <rtgui/rtgui.h>

typedef struct rtgui_list_node rtgui_list_t;/* (template),注意与CCList的区别 */

struct rtgui_list_node
{
	rtgui_list_t* next;
};
rt_inline void rtgui_list_init(rtgui_list_t *l)
{
	l->next = (rtgui_list_t *)0;
}

rt_inline void rtgui_list_append(rtgui_list_t *l, rtgui_list_t *n)
{
	rtgui_list_t* node;

	node = l;
	while(node->next) node = node->next;

	/* append the node to the tail */
	node->next = n;
	n->next = (rtgui_list_t*) 0;
}

rt_inline void list_insert(rtgui_list_t *l, rtgui_list_t *n)
{
	n->next = l->next;
	l->next = n;
}

rt_inline rtgui_list_t* rtgui_list_remove(rtgui_list_t *l, rtgui_list_t *n)
{
	/* remove slist head */
	rtgui_list_t* node = l;
	while(node->next && node->next != n) node = node->next;

	/* remove node */
	if(node->next != (rtgui_list_t *)0) node->next = node->next->next;

	return l;
}

#define rtgui_list_entry(node, type, member)	\
	((type *)((char*)(node)-(unsigned long)(&((type *)0)->member)))

#define rtgui_list_foreach(node, list)	\
	for((node) = (list)->next; (node) != RT_NULL; (node) = (node)->next)

#endif
