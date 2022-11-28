/*
********************************************************************************
*                                    eMOD
*                   the Easy Portable/Player Develop Kits
*                               mod_duckweed sub-system
*                          (module name, e.g.mpeg4 decoder plug-in) module
*
*          (c) Copyright 2010-2012, Allwinner Microelectronic Co., Ltd.
*                              All Rights Reserved
*
* File   : webcam_linklist_manager.c
* Version: V1.0
* By     : Eric_wang
* Date   : 2010-1-4
* Description:
********************************************************************************
*/
#include "string.h"
#include "hal_mem.h"
#include "hal_log.h"
#include "webcam_linklist_manager.h"

//链表实现方式2
/*******************************************************************************
关于 链表实现方式2 的说明:
(1). 一个线程vdrv_task() 和一个中断处理程序webcam_irq_handle()会操作2个链表full2和free2
     因此需要做互斥。
(2). 考虑到ISR是不会被打断的，所以只需要对vdrv_task()操作涉及的函数做互斥处理就行了
    full2_insert( isr ), wt
    full2_delete( vdrv_task ), rd
    free2_insert( vdrv_task ), wt
    free2_delete( isr ), rd

    所以，只需要对full2_delete()和free2_insert()做互斥处理就行了。所谓互斥，也就是
    在处理前，把一些可能会被改变的变量记下来而已。
*******************************************************************************/
void Impl_initial_webcam_linklist_manager(__webcam_linklist_manager_t *thiz, WEBCAM_LINKLIST_TYPE type)
{
    //memset(pManager, 0, sizeof(__webcam_linklist_manager_t));
    thiz->list_type = type;
    thiz->wt = thiz->rd = 0;
    return;
}
__s32 Impl_webcam_linklist_manager_exit(__webcam_linklist_manager_t *thiz)
{
    memset(thiz, 0, sizeof(__webcam_linklist_manager_t));
    hal_log_info("%s %d %s thiz:%x!\n", __FILE__, __LINE__, __func__, thiz);
    hal_free(thiz);
    return 0;
}

/*******************************************************************************
Function name: full2_insert
Description:
    针对装满帧的数组做插入操作。
    isr调用
    修改wt
    rd由vdrv_task()修改
Parameters:
    1. idx:就是数组__webcam_frame_t webcam_frame[WEBCAM_BUFFER_NUM]的 frame_id
Return:

Time: 2010/7/12
*******************************************************************************/
__s32 Impl_webcam_linklist_manager_insert(__webcam_linklist_manager_t *thiz, __s32 frame_id)
{
    //__u32 cpu_sr;
    //__s32 full2_wt;
    //__s32 full2_rd;
    //__s32 uTmpRd;
    //__s32 uNextRd;
    __s32 uTmpWt = thiz->wt + 1;

    uTmpWt %= FRMID_CNT;
    if(thiz->rd == uTmpWt)
    {
        hal_log_info("fatal error, [%d] array full!\n", thiz->list_type);
    }

    thiz->frmid_array[thiz->wt] = frame_id;
    thiz->wt = uTmpWt;

    return EPDK_OK;
}
/*******************************************************************************
Function name: full2_delete
Description:
    取一个元素出来，
    vdrv_task()调用。可能会没有元素。
    修改rd,
    wt由ISR修改
Parameters:

Return:
    1.如果没有元素, 返回-1
    2.如果有，返回id号。
Time: 2010/7/12
*******************************************************************************/
__s32 Impl_webcam_linklist_manager_delete(__webcam_linklist_manager_t *thiz)
{
    __s32 frame_id;
    __s32 nTmpRd = thiz->rd;
    if(thiz->rd == thiz->wt)
    {
        return -1;
    }
    else
    {
        //__u32 cpu_sr;
        //__s32 full2_wt;
        //__s32 full2_rd;
        frame_id = thiz->frmid_array[nTmpRd++];
        nTmpRd %= FRMID_CNT;
        thiz->rd = nTmpRd;

        return frame_id;
    }
}
__webcam_linklist_manager_t* webcam_linklist_manager_init()
{
    __webcam_linklist_manager_t *p = (__webcam_linklist_manager_t*)hal_malloc(sizeof(__webcam_linklist_manager_t));
    printf("%s %d %s!\n", __FILE__, __LINE__, __func__);
    if(NULL == p)
    {
        hal_log_info("malloc __webcam_linklist_manager_t fail\n");
        return NULL;
    }
    memset(p, 0, sizeof(__webcam_linklist_manager_t));
    p->initial = Impl_initial_webcam_linklist_manager;
    p->insert_element = Impl_webcam_linklist_manager_insert;
    p->delete_element = Impl_webcam_linklist_manager_delete;
    p->exit = Impl_webcam_linklist_manager_exit;
    return p;
}

