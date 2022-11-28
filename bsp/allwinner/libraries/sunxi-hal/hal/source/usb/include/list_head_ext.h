/*===============================================================================================*
*                                                                                                *
* MMMMMMMM  MMMMMMM    MMMMMMM  MMMMMMMM    MMMMMMMM       MM      MM    MMMMMMMMMMMMM           *
*    MMM      MMM        MMM      MMM          MM      MM        . MM        MMM        MM       *
*    MMM      MMM        MMM      MMM          MM      MM          MM        MMM        MM.      *
*    MMM      MMM        MMM      MMM          MM    . MM          MM        MMM        MMMM     *
*    MMM      MMM        MMM      MMM          MM      MMMM                  MMM        MM       *
*    MMMMMMMMMMMM        MMM      MMM          MM          MMMM              MMMMMMMMMMM         *
*    MMM      MMM        MMM      MMM          MM              MMMM          MMM          .      *
*    MMM      MMM        MMM      MMM          MM                . MM        MMM          MM     *
*    MMM      MMM        MMM      MMM          .     MM            MMMM      MMM          MMMM   *
*    MMM      MMM        MM        MM                MM            MM.       MMM          MM     *
*    MMM      MMM  .     MM        MM.               MMMM          MM        MMM          MM     *
* MMMMMMMM  MMMMMMM  MM.                MMMMM         MM      MMMM        MMMMMMMMMMMMM.         *
*                                                                                                *
*================================================================================================
*
*                                              usb host module
*
*                              Copyright(C), 2006-2008, SoftWinners Co., Ltd.
*                                                  All Rights Reserved
*
* File Name :
*
* Author : GLHuang(HoLiGun)
*
* Version : 1.0
*
* Date : 2008.06.12
*
* Description :
*           对list_head的extention
* History :
*================================================================================================
*/
#ifndef __LIST_HEAD_UTILS_H__
#define __LIST_HEAD_UTILS_H__
#include "usb_list.h"

//从list_header_input中删除某个node
//return :  0   //表示找到了改node，且成功删除了
//对list的操作有critical保护
//int list_head_ext_remov_node_from_list(void *node_data, struct usb_list_head *list_header_input);

//遍历的init，先申明两个变量。
#define list_head_ext_for_each_entry_init()     \
    struct usb_list_head * list_head_ext_start_ = NULL;     \
    struct usb_list_head *  list_head_ext_now_ = NULL ;

//遍历的主体,当前的为list_head_ext_now_
#define list_head_ext_for_each_entry_process( p_start_list_head)        \
    for(list_head_ext_start_ = (p_start_list_head),list_head_ext_now_ = (p_start_list_head)->next;\
        list_head_ext_now_ != list_head_ext_start_ ;\
        list_head_ext_now_ = list_head_ext_now_->next)

/* 遍历list, 看是否存在值为data的node */
int32_t list_node_exist(void *data, struct usb_list_head *list_head);
int32_t list_del_node_by_data(void *data, struct usb_list_head  *list);
int32_t list_destroy_whole_list(struct usb_list_head  *list);
int list_head_ext_remov_node_from_list(void *node_data, struct usb_list_head *list_header_input);


#endif





