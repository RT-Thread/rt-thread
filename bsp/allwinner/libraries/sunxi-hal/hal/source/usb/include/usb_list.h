/*
*******************************************************************************
*                                              usb host module
*
*                             Copyright(C), 2006-2008, SoftWinners Co., Ltd.
*                                                  All Rights Reserved
*
* File Name :
*
* Author : GLHuang(HoLiGun)
*
* Version : 1.0
*
* Date : 2008.05.xx
*
* Description :
*
* History :
*注意*:别忘记修改list 的头指针，我犯过这个错误。
********************************************************************************************************************
*/



#ifndef _USB_LIST_H_
#define _USB_LIST_H_

#include <log.h>
#include <hal_osal.h>
//#include "usb_host_config.h"


//#define   USE_USB_LIST_BUFF   0x01        //使用usb_list的buff机制

struct usb_list_head
{
    struct usb_list_head *next;
    struct usb_list_head *prev;
    void *data;
};

#define __USB_LIST_HEAD_INIT(name) { &(name), &(name) ,NULL}

//创建并初始化
#define USB_LIST_HEAD(name) \
    struct usb_list_head name = __USB_LIST_HEAD_INIT(name)

//只初始化
#define USB_INIT_LIST_HEAD(ptr) do { \
        (ptr)->next = (ptr); (ptr)->prev = (ptr); \
        (ptr)->data = NULL;\
    } while (0)

/* 获得list中每个node的内容
 *
 * list_head  :  链表头
 * list_next  :  下一个node
 * data       :  node的内容
 */
#define usb_list_for_each_entry(list_head, list_next, data) \
    for((list_next) = (list_head)->next, (data) = list_next->data; \
        (list_next) != (list_head);       \
        (list_next) = (list_head)->next, (data) = list_next->data)

//=========================================================

//用这个的前提：prev,next必须是存在的，否则崩溃。
static inline void __usb_list_add(struct usb_list_head *node,
                                  struct usb_list_head *prev,
                                  struct usb_list_head *next)
{
    node->next = next;
    node->prev = prev;
    prev->next = node;
    next->prev = node;
}

//将node添加到head的后面
static inline void usb_list_add(struct usb_list_head *node, struct usb_list_head *head)
{
    __usb_list_add(node, head, head->next);
}

//将node添加到head的最后面，既其前面
static inline void usb_list_add_tail(struct usb_list_head *node, struct usb_list_head *head)
{
    __usb_list_add(node, head->prev, head);
}

//=========================================================

//内部函数，删除prev,next之间的
static inline void __usb_list_del(struct usb_list_head *prev, struct usb_list_head *next)
{
    next->prev = prev;
    prev->next = next;
}

//从list中删除entry
static inline void usb_list_del(struct usb_list_head *entry)
{
    __usb_list_del(entry->prev, entry->next);
    //entry->next = LIST_POISON1;
    //entry->prev = LIST_POISON2;
    entry->next = entry;
    entry->prev = entry;
}

//比list_del多清除了指向data的
static inline void usb_list_del_init(struct usb_list_head *entry)
{
    __usb_list_del(entry->prev, entry->next);
    USB_INIT_LIST_HEAD(entry);
}

//判断是否为空
static inline int usb_list_empty(const struct usb_list_head *head)
{
    return head->next == head;
}

//-------------------------------------------------------------------
//
//
//-------------------------------------------------------------------
__s32 ListMemoryInit(void);
__s32 ListMemoryExit(void);
void *ListMemoryMalloc(__u32 size, u8 *file_name, u32 line_nr);
void ListMemoryFree(void *addr, u8 *file_name, u32 line_nr);


/* list_head结构的分配和init */
static struct usb_list_head *_list_head_malloc_init(void)
{
    struct usb_list_head *list = NULL;
    //先从buff中分配
    //list = ListMemoryMalloc(sizeof(struct usb_list_head), USB_MEM_FILE_TRIGGER, USB_MEM_LINE_TRIGGER);
    list = hal_malloc(sizeof(struct usb_list_head));

    if (list == NULL)
    {
        __err("PANIC : _list_head_malloc_init() : no mem\n");
        return NULL;
    }

    USB_INIT_LIST_HEAD(list);
    return list;
}

/* list_head结构的释放 */
static void _usb_list_head_free(struct usb_list_head *list)
{
    if (list == NULL)
    {
        __err("PANIC : _list_head_free() : try to free NULL\n");
        return ;
    }

    //ListMemoryFree((void *)list, USB_MEM_FILE_TRIGGER, USB_MEM_LINE_TRIGGER);
    hal_free((void *)list);
    return ;
}

/*
********************************************************************************
*                     list_head_malloc_and_add
*
* Description:
*     创建list_head并将data挂载到list_head，同时添加到目标list
* 与list_head_malloc_and_add()配对使用
*
* Arguments:
*     data  : input. 需要加入队列的数据
*     head  : input. 队列的头
* Return value:
*     返回 head->data
* note:
*     void
*********************************************************************************
*/
static inline void list_head_malloc_and_add(void *data, struct usb_list_head *head)
{
    __u32 lock = 0;
    struct usb_list_head *list = _list_head_malloc_init();

    if (list == NULL)
    {
        __err("ERR: _list_head_malloc_init failed\n");
        return;
    }

    //USB_OS_ENTER_CRITICAL(lock);
    list->data = data;
    usb_list_add_tail(list, head);
    //USB_OS_EXIT_CRITICAL(lock);
    return;
}

/*
********************************************************************************
*                     list_head_unlink_and_del
*
* Description:
*     从list中删除head这个node ,且free这个node的内存, 返回这个node的内容
* 与list_head_malloc_and_add()配对使用
*
* Arguments:
*     head  : input. 即将被删除的node
* Return value:
*     返回 head->data
* note:
*     void
*********************************************************************************
*/
static inline void *list_head_unlink_and_del(struct usb_list_head *head)
{
    void *ret = NULL;
    __u32 lock = 0;

    if (head == NULL)
    {
        __err("PANIC : list_head_unlink_and_del() : try to free NULL\n");
        return NULL ;
    }

    //--1--unlink from list
    //USB_OS_ENTER_CRITICAL(lock);
    usb_list_del(head);
    ret = head->data;
    //USB_OS_EXIT_CRITICAL(lock);
    _usb_list_head_free(head);
    return ret;
}

#endif


