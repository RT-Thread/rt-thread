/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
/*****************************************************************************
 *  Include Section
 *  add all #include here
 *****************************************************************************/
#include "board_info.h"
#include <rtdevice.h>
#include <string.h>
/*****************************************************************************
 * Define section
 * add all #define here
 *****************************************************************************/
struct fh_board_info_list_node {
	struct fh_board_info obj;
	rt_list_t list;
};

#define CHECK_TEST_LIST_EMPTY		\
		if(rt_list_isempty(&board_info_head.list)) \
		rt_kprintf("board info is null...please register first..\n")

/****************************************************************************
 * ADT section
 *  add definition of user defined Data Type that only be used in this file  here
 ***************************************************************************/

#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = rt_list_entry((head)->next, typeof(*pos), member),	\
		n = rt_list_entry(pos->member.next, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = n, n = rt_list_entry(n->member.next, typeof(*n), member))

#define PARA_ERROR			(-1)
#define PROBE_FUNC_MISS		(-2)

/******************************************************************************
 * Function prototype section
 * add prototypes for all functions called by this file,execepting those
 * declared in header file
 *****************************************************************************/

//static void fh81_soc_free_all_test(void);
//static void fh81_soc_print_all_test(void);
//static void fh81_soc_auto_test_all(void);
//static void fh81_soc_test_help(void);
/*****************************************************************************
 * Global variables section - Exported
 * add declaration of global variables that will be exported here
 * e.g.
 *  int8_t foo;
 ****************************************************************************/

/*****************************************************************************

 *  static fun;
 *****************************************************************************/
static struct fh_board_info_list_node board_info_head;



/*****************************************************************************
 * Global variables section - Local
 * define global variables(will be refered only in this file) here,
 * static keyword should be used to limit scope of local variable to this file
 * e.g.
 *  static uint8_t ufoo;
 *****************************************************************************/


 /* function body */
/*****************************************************************************
 * Description:
 *      add funtion description here
 * Parameters:
 *      description for each argument, new argument starts at new line
 * Return:
 *      what does this function returned?
 *****************************************************************************/

int fh_board_info_init(void) {

	memset(&board_info_head, 0x0, sizeof(struct fh_board_info_list_node));
	rt_list_init(&board_info_head.list);
	board_info_head.obj.name = "NO INFO";
	return 0;
}

void fh_free_all_info(void) {
	rt_list_t *p_list;
	struct fh_board_info_list_node *info_node;
	struct fh_board_info_list_node *_info_node;
	p_list = &board_info_head.list;

	CHECK_TEST_LIST_EMPTY;

	list_for_each_entry_safe(info_node, _info_node, p_list, list)
	{

		if (info_node->obj.ops->exit) {
			info_node->obj.ops->exit(info_node->obj.data);
		}
		rt_kprintf("soc free list name:(%s)\n", info_node->obj.name);
		rt_free(info_node);
	}
	fh_board_info_init();
}

void fh_print_all_board_info(void) {
	rt_list_t *p_list;

	struct fh_board_info_list_node *info_node;
	struct fh_board_info_list_node *_info_node;
	p_list = &board_info_head.list;

	CHECK_TEST_LIST_EMPTY;

	list_for_each_entry_safe(info_node, _info_node, p_list, list)
	{
		rt_kprintf("%s\n", info_node->obj.name);
	}
}

/*****************************************************************************
 * Description:
 *      add funtion description here
 * Parameters:
 *      description for each argument, new argument starts at new line
 * Return:
 *      what does this function returned?
 *****************************************************************************/

//register the platform info such as base add,isr no..
//caution:do not free the name and data because of here not copy
struct fh_board_info *fh_board_info_register(char *info_name, void *data) {
	rt_list_t *p_list;
	struct fh_board_info_list_node *new_node;
	struct fh_board_info_list_node *info_node;
	struct fh_board_info_list_node *_info_node;
	p_list = &board_info_head.list;

	if (RT_NULL == info_name || RT_NULL == data) {
		rt_kprintf("info name or info data is NULL!\n");
		return RT_NULL;
	}

	//check if the func is already in the test list....
#if(0)
	list_for_each_entry_safe(info_node, _info_node, p_list, list) {
		if (!memcmp(info_node->obj.name, info_name, strlen(info_name))) {
			rt_kprintf("info_name(%s) is already registered\n", info_name);
			return RT_NULL;
		}
	}
#endif

	new_node = (struct fh_board_info_list_node *) rt_malloc(
			sizeof(struct fh_board_info_list_node));
	if (!new_node) {
		rt_kprintf("malloc new_list_node failed~\n");
		return RT_NULL;
	}

	new_node->obj.name = info_name;
	new_node->obj.data = data;
	//here insert "before" and test is "after" will make the list like a fifo...
	rt_list_insert_before(&board_info_head.list, &new_node->list);
	return &new_node->obj;
}

//back the platform info
static void *fh_get_board_info_data(char *info_name) {

	rt_list_t *p_list;
	struct fh_board_info_list_node *info_node;
	struct fh_board_info_list_node *_info_node;
	p_list = &board_info_head.list;

	//check info name
	if (RT_NULL == info_name) {
		rt_kprintf("info name is NULL!\n");
		return RT_NULL;
	}

	CHECK_TEST_LIST_EMPTY;

	list_for_each_entry_safe(info_node, _info_node, p_list, list)
	{
		if (!strcmp(info_node->obj.name, info_name)) {
			return info_node->obj.data;
		}
	}

	rt_kprintf("Can't find the board info name:%s\n", info_name);
}

int fh_board_driver_register(char *info_name, struct fh_board_ops *ops) {

	rt_list_t *p_list;
	struct fh_board_info_list_node *new_node;
	struct fh_board_info_list_node *info_node;
	struct fh_board_info_list_node *_info_node;
	p_list = &board_info_head.list;

	if (RT_NULL == info_name || RT_NULL == ops) {
		rt_kprintf("info name or ops func is NULL!\n");
		return PARA_ERROR;
	}

	list_for_each_entry_safe(info_node, _info_node, p_list, list)
	{
		if (!strcmp(info_node->obj.name, info_name)) {

			info_node->obj.ops = ops;
			if (info_node->obj.ops->probe) {
				info_node->obj.ops->probe(info_node->obj.data);
			}

			//return info_node->obj.data;
		}
	}

	//rt_kprintf("Can't find the board info name:%s\n",info_name);

	return 0;
}
