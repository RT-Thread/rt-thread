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

struct rtgui_list_node
{
    struct rtgui_list_node *next;
};
typedef struct rtgui_list_node rtgui_list_t;

rt_inline void rtgui_list_init(rtgui_list_t *l)
{
    l->next = (struct rtgui_list_node *)0;
}

rt_inline void rtgui_list_append(rtgui_list_t *l, rtgui_list_t *n)
{
    struct rtgui_list_node *node;

    node = l;
    while (node->next) node = node->next;

    /* append the node to the tail */
    node->next = n;
    n->next = (struct rtgui_list_node *) 0;
}

rt_inline void rtgui_list_insert(rtgui_list_t *l, rtgui_list_t *n)
{
    n->next = l->next;
    l->next = n;
}

rt_inline rtgui_list_t *rtgui_list_remove(rtgui_list_t *l, rtgui_list_t *n)
{
    /* remove slist head */
    struct rtgui_list_node *node = l;
    while (node->next && node->next != n) node = node->next;

    /* remove node */
    if (node->next != (rtgui_list_t *)0) node->next = node->next->next;

    return l;
}

#define rtgui_list_entry(node, type, member)    \
    ((type *)((char*)(node)-(unsigned long)(&((type *)0)->member)))

#define rtgui_list_foreach(node, list)  \
    for ((node) = (list)->next; (node) != RT_NULL; (node) = (node)->next)

#endif
