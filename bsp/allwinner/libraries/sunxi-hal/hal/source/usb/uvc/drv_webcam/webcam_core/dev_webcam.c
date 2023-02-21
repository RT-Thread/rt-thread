/*
*********************************************************************************************************
*                                                    MELIS
*                                    the Easy Portable/Player Develop Kits
*                                                 WEBCAM Driver
*
*                                    (c) Copyright 2012-2016, Kingvan.Tong China
*                                             All Rights Reserved
*
* File    : drv_webcam.h
* By      : Kingvan
* Version : v1.0
* Date    : 2012-9-27
* Descript:
* Update  : date                auther         ver     notes
*           2012-9-27 11:09:13  Kingvan.Tong   2.0     build the file.
*********************************************************************************************************
*/

#include "dev_webcam_i.h"
#include "webcam_dev_i.h"
#include "hal_log.h"
#include "hal_mem.h"
#include "typedef.h"
#include "string.h"

__webcam_dev_t     *pWebcamDevNode = NULL;

static __u32    first_flag=0;
static __u32    pts=0;
static __u32    valid_mode_idx=0;
static __s32   lost_frame_num = 0;

__s32 translate_frame_id_to_index(__s32 frame_id)
{
    //__s32 index;
    return (frame_id & 0x0F);
}

static __s32  webcam_irq_handle(__u32* addr0, __u32* addr1, __u32* addr2 )
{
    __s32 frame_id;//index切切不要用全局变量

    hal_log_info("webcam irq\n");
    if(first_flag==0)
    {
        first_flag=1;
        hal_log_info("webcam first irq\n");
        frame_id = pWebcamDevNode->free2->delete_element(pWebcamDevNode->free2);
        if (frame_id != -1)
        {//在free中请求buffer成功

            __s32 index = translate_frame_id_to_index(frame_id);

            if( addr0 != NULL ) *addr0 = pWebcamDevNode->webcam_frame[index].addr[0];
            if( addr1 != NULL ) *addr1 = pWebcamDevNode->webcam_frame[index].addr[1];
            if( addr2 != NULL ) *addr2 = pWebcamDevNode->webcam_frame[index].addr[2];

            pWebcamDevNode->frame_id_last_b = frame_id;

        }
        else
        {
            hal_log_err("webcam no buffer!\n");
        }

        goto done;
    }

    if (pWebcamDevNode->pts_flag==0)
    {
        pWebcamDevNode->pts += (__s64)(webcam_mode.frame_period);
    }
    else if(pWebcamDevNode->pts_flag == 1)
    {
        if(pWebcamDevNode->CB_GetPts)
        {
            pWebcamDevNode->CB_GetPts((void*)&pWebcamDevNode->pts);
            if((__u32)(pWebcamDevNode->pts)-pts>webcam_mode_all.webcam_mode[valid_mode_idx].frame_period*(1.2))
            {
                hal_log_err("frame period not match, delta = %d\n",(__u32)(pWebcamDevNode->pts)-pts);
            }
            pts = (__u32)(pWebcamDevNode->pts);
        }
        else
        {
//            //hal_log_err("CB_GetPts callback is not set!\n");
            pWebcamDevNode->pts = 0;
        }
    }
    else
    {
        pWebcamDevNode->pts = 0;
    }

    hal_log_info("pWebcamDevNode->pts_flag=%d pWebcamDevNode->pts=%d\n",pWebcamDevNode->pts_flag,(pWebcamDevNode->pts&0xffffffff));
    frame_id = pWebcamDevNode->free2->delete_element(pWebcamDevNode->free2);
    hal_log_info("frame_id=%x\n",frame_id);
    if (frame_id != -1)//在free中请求buffer成功
    {
        __s32 nTmpIndex = translate_frame_id_to_index(frame_id);

        if( addr0 != NULL ) *addr0 = pWebcamDevNode->webcam_frame[nTmpIndex].addr[0];
        if( addr1 != NULL ) *addr1 = pWebcamDevNode->webcam_frame[nTmpIndex].addr[1];
        if( addr2 != NULL ) *addr2 = pWebcamDevNode->webcam_frame[nTmpIndex].addr[2];

        nTmpIndex = translate_frame_id_to_index(pWebcamDevNode->frame_id_last);
        pWebcamDevNode->webcam_frame[nTmpIndex].uPts = pWebcamDevNode->pts;//

        pWebcamDevNode->full2->insert_element(pWebcamDevNode->full2, pWebcamDevNode->frame_id_last);
        pWebcamDevNode->frame_id_last = pWebcamDevNode->frame_id_last_b;
        pWebcamDevNode->frame_id_last_b = frame_id;
    }
    else
    {
        hal_log_info("****webcam lost frame[%d] ****\n", lost_frame_num++);
    }

done:

    return EPDK_OK;
}

__s32 webcam_check_mode_valid(void)
{
    __u32 i;
    for (i=0;i<webcam_mode_all.number;i++)
    {
        hal_log_err("mode%d:%dx%d@%d#color_fmt=%d buf_scmode=%d\n",i, webcam_mode_all.webcam_mode[i].size.width, webcam_mode_all.webcam_mode[i].size.height, webcam_mode_all.webcam_mode[i].frame_rate, (__u32)webcam_mode_all.webcam_mode[i].color_format, webcam_mode_all.webcam_mode[i].webcam_buf_scrab_mode);
        if ((webcam_mode_all.webcam_mode[i].color_format == webcam_mode.color_format)&&
            (webcam_mode_all.webcam_mode[i].color_space == webcam_mode.color_space)&&
            (webcam_mode_all.webcam_mode[i].component_seq == webcam_mode.component_seq)&&
            (webcam_mode_all.webcam_mode[i].frame_rate == webcam_mode.frame_rate)&&
            (webcam_mode_all.webcam_mode[i].frame_period == webcam_mode.frame_period)&&
            (webcam_mode_all.webcam_mode[i].store_mode == webcam_mode.store_mode)&&
            (webcam_mode_all.webcam_mode[i].size.width == webcam_mode.size.width)&&
            (webcam_mode_all.webcam_mode[i].size.height   == webcam_mode.size.height)&&
            (webcam_mode_all.webcam_mode[i].webcam_buf_scrab_mode    == webcam_mode.webcam_buf_scrab_mode) )  {
            hal_log_err("webcam_check_mode_valid:%d\n",i);
            //webcam_dev_set_mode(i); //设置模式
            valid_mode_idx = i;
            return EPDK_OK;
        }
    }
    return EPDK_FAIL;
}

static void WEBCAM_OpLock(void)
{
    __u8  err;

    hal_sem_wait(pWebcamDevNode->webcam_lock);
}

static void WEBCAM_OpUnlock(void)
{
    hal_sem_post(pWebcamDevNode->webcam_lock);
}

__hdle DEV_WEBCAM_Open(void * open_arg, __u32 mode)
{
    hal_log_err("DEV_WEBCAM_Open\n");
    return (__hdle)&(pWebcamDevNode);
}

__s32 DEV_WEBCAM_Close(__hdle hwebcam)
{
    hal_log_err("DEV_WEBCAM_Close\n");

    return EPDK_OK;
}

__u32 DEV_WEBCAM_Read(void *pdata, __u32 size, __u32 n, __hdle hPower)
{
    return 0;
}

__u32 DEV_WEBCAM_Write(const void *pdata, __u32 size, __u32 n, __hdle hPower)
{
    return size * n;
}

__s32 DEV_WEBCAM_Ioctrl(__hdle hWebcam, __u32 cmd, __s32 aux, void *pbuffer)
{
    __s32                ret;
    __s32 i;

    ret = EPDK_FAIL;

    WEBCAM_OpLock();

    switch(cmd)
    {
        case DRV_WEBCAM_CMD_INIT:
        {
            hal_log_err("webcam buffer number = %d\n", WEBCAM_BUFFER_NUM);
            for (i=0; i<WEBCAM_BUFFER_NUM; i++) {
                pWebcamDevNode->p_webcam_frame[i] = &pWebcamDevNode->webcam_frame[i];\
            }

            webcam_dev_init();
            hal_log_err("DRV_WEBCAM_CMD_INIT\n");
            ret = EPDK_OK;
            break;
        }
        case DRV_WEBCAM_CMD_EXIT:
        {
            webcam_dev_exit();

            hal_log_err("DRV_WEBCAM_CMD_EXIT\n");
            ret = EPDK_OK;
            break;
        }
        case DRV_WEBCAM_CMD_SET_MODE:
        {
            __webcam_mode_t *p=pbuffer;
            webcam_mode = *p;

            hal_log_err("DRV_WEBCAM_CMD_SET_MODE\n");
            ret = EPDK_OK;
            break;
        }
        case DRV_WEBCAM_CMD_GET_MODE:
        {
            __webcam_mode_t *p=pbuffer;
            *p = webcam_mode;

            hal_log_err("DRV_WEBCAM_CMD_GET_MODE\n");
            ret = EPDK_OK;
            break;
        }
        case DRV_WEBCAM_CMD_GET_MODE_ALL:
        {
            __webcam_mode_all_t *p = pbuffer;
            *p = webcam_mode_all;

            hal_log_err("DRV_WEBCAM_CMD_GET_MODE_ALL\n");
            ret = EPDK_OK;
            break;
        }
        case DRV_WEBCAM_CMD_SET_FRAME_QUEUE:
        {
            __webcam_frame_queue_t *pFrameQueue = (__webcam_frame_queue_t*)pbuffer;

            hal_log_err("DRV_WEBCAM_CMD_SET_FRAME_QUEUE\n");
            if (pFrameQueue->num != WEBCAM_BUFFER_NUM)
            {
                hal_log_err("careful! num[%d] != WEBCAM_BUFFER_NUM[%d]\n", pFrameQueue->num, WEBCAM_BUFFER_NUM);
                //return EPDK_FAIL;
            }
            else
            {
                hal_log_err("webcam_frame_num[%d]\n", pFrameQueue->num);
            }

            if (pFrameQueue->num > WEBCAM_BUFFER_NUM)
            {
                hal_log_err("fatal error, num[%d] > WEBCAM_BUFFER_NUM[%d]\n", pFrameQueue->num, WEBCAM_BUFFER_NUM);
                return EPDK_FAIL;
            }

            pWebcamDevNode->webcam_frame_num = pFrameQueue->num;
            for (i=0; i<pFrameQueue->num; i++)   //现在num就等于WEBCAM_BUFFER_NUM，为下一步修改做准备
            {
                //WEBCAM_BUFFER_NUM
                memcpy(&pWebcamDevNode->webcam_frame[i], &pFrameQueue->webcam_frame_array[i], sizeof(__webcam_frame_t));
            }
            ret = EPDK_OK;
            break;
        }
        case DRV_WEBCAM_CMD_CAPTURE_ON:
        {
            __s32 frame_id;
            __s32 index;//index切切不要用全局变量

            if (webcam_check_mode_valid() != EPDK_OK)
            {
                hal_log_err("webcam mode invalid!\n");
                break;
            }
            else
            {
                webcam_dev_set_mode(valid_mode_idx); //设置模式
            }

            pWebcamDevNode->pts = 0;
            pWebcamDevNode->full2->initial(pWebcamDevNode->full2, WEBCAM_LISTTYPE_FULL);
            pWebcamDevNode->free2->initial(pWebcamDevNode->free2, WEBCAM_LISTTYPE_FREE);
            for (i=0; i<pWebcamDevNode->webcam_frame_num; i++)
            {
                pWebcamDevNode->webcam_frame[i].bProgressiveSrc   = 1;//bProgressiveSrc;
                pWebcamDevNode->webcam_frame[i].bTopFieldFirst    = 0;//bTopFieldFirst;
                pWebcamDevNode->webcam_frame[i].eAspectRatio      = 1000;//eAspectRatio;
                pWebcamDevNode->webcam_frame[i].color_format      = webcam_mode.color_format;
                pWebcamDevNode->webcam_frame[i].src_rect.width    = pWebcamDevNode->webcam_frame[i].dst_rect.width = webcam_mode.size.width;
                pWebcamDevNode->webcam_frame[i].src_rect.height   = pWebcamDevNode->webcam_frame[i].dst_rect.height = webcam_mode.size.height;
                pWebcamDevNode->webcam_frame[i].frame_rate        = webcam_mode.frame_rate;
                pWebcamDevNode->webcam_frame[i].uPts              = pWebcamDevNode->pts;
                pWebcamDevNode->webcam_frame[i].bPtsValid         = 1;
                pWebcamDevNode->webcam_frame[i].component_seq     = webcam_mode.component_seq;;
                pWebcamDevNode->webcam_frame[i].store_mode        = webcam_mode.store_mode;;

                if(EPDK_OK != pWebcamDevNode->free2->insert_element(pWebcamDevNode->free2, pWebcamDevNode->webcam_frame[i].frame_id))
                {
                    hal_log_err("impossible free2_insert fail,check code!\n");
                }
            }
            pWebcamDevNode->webcam_mode_last = webcam_mode;
            first_flag=0;

            if( pWebcamDevNode->tran_cb != NULL )
            {
                hal_log_info("DRV_WEBCAM_CMD_CAPTURE_ON: have cb\n");
                frame_id = pWebcamDevNode->free2->delete_element(pWebcamDevNode->free2);
                if (frame_id != -1)
                {//在free中请求buffer成功
                    index = translate_frame_id_to_index(frame_id);
                    pWebcamDevNode->tran_cb(pWebcamDevNode->webcam_frame[index].addr[0], (__u32)NULL, (__u32)NULL);
                    pWebcamDevNode->frame_id_last = frame_id;
                    pWebcamDevNode->capture = CAPTURE_ON_AND_CALLBACK;
                }
                else
                {
                    hal_log_info("ERROR:webcam no buffer! ???? \n");
                }
            }
            else
            {
                hal_log_info("DRV_WEBCAM_CMD_CAPTURE_ON: haven't cb\n");
                pWebcamDevNode->capture = CAPTURE_ON;
            }
          //WEBCAM_capture_video_start();
            hal_log_err("DRV_WEBCAM_CMD_CAPTURE_ON\n");
            ret = EPDK_OK;
            break;
        }

        case DRV_WEBCAM_CMD_CAPTURE_OFF:
        {
            if (pWebcamDevNode->tran_cb != NULL)
            {
                pWebcamDevNode->tran_cb((__u32)NULL, (__u32)NULL, (__u32)NULL);
            }

            pWebcamDevNode->capture     = CAPTURE_NONE;
            pWebcamDevNode->used_addr0  = (__u32)NULL;
            pWebcamDevNode->used_addr1  = (__u32)NULL;
            //WEBCAM_capture_video_stop();//关中断发生器
            first_flag=0;
            lost_frame_num=0;

            hal_log_info("DRV_WEBCAM_CMD_CAPTURE_OFF pWebcamDevNode->tran_cb=%x\n",pWebcamDevNode->tran_cb);
            ret = EPDK_OK;

            //清掉webcam_frame数组，即full2, free2数组，也可以不清. 为简单起见,这里不清数组.
            //initial_webcam_linklist_manager(&full2, WEBCAM_LISTTYPE_FULL);
            //initial_webcam_linklist_manager(&free2, WEBCAM_LISTTYPE_FREE);
            pWebcamDevNode->full2->initial(pWebcamDevNode->full2, WEBCAM_LISTTYPE_FULL);
            pWebcamDevNode->free2->initial(pWebcamDevNode->free2, WEBCAM_LISTTYPE_FREE);
            break;
        }
        case DRV_WEBCAM_CMD_SET_PTS:
        {
            pWebcamDevNode->pts = aux;
            hal_log_err("DRV_WEBCAM_CMD_SET_PTS\n");
           ret = EPDK_OK;
            break;
        }
        case DRV_WEBCAM_CMD_GET_PTS:
        {
            ret = pWebcamDevNode->pts;
            hal_log_err("DRV_WEBCAM_CMD_GET_PTS\n");
            //ret = EPDK_OK;
            break;
        }
        case DRV_WEBCAM_CMD_REQUEST_FRAME:
        {
            __s32 index;
            __s32 frame_id;//index切切不要用全局变量

            frame_id = pWebcamDevNode->full2->delete_element(pWebcamDevNode->full2);
            if (frame_id != -1){
                __webcam_frame_t **pp = (__webcam_frame_t ** )pbuffer;
                index = translate_frame_id_to_index(frame_id);
                *pp = pWebcamDevNode->p_webcam_frame[index];

                ret = EPDK_OK;
            }

            break;
        }
        case DRV_WEBCAM_CMD_RELEASE_FRAME:
        {
            //linklist_insert(&webcam_free, aux);
            //free2_insert(aux);
            pWebcamDevNode->free2->insert_element(pWebcamDevNode->free2, aux);
            //hal_log_err("DRV_WEBCAM_CMD_RELEASE_FRAME\n");
            ret = EPDK_OK;
            break;
        }
        case DRV_WEBCAM_CMD_SET_PTS_MODE:
        {
            pWebcamDevNode->pts_flag = aux;
            ret = EPDK_OK;
            break;
        }
        case DRV_WEBCAM_CMD_INSTALL_CALLBACK_GET_PTS:
        {
            pWebcamDevNode->CB_GetPts = (__pCBK_t)pbuffer;
            ret = EPDK_OK;
            break;
        }
        case DRV_WEBCAM_CMD_SET_COLOR_EFFECT:
        {
            ret = EPDK_FAIL;
            hal_log_err("DRV_WEBCAM_CMD_SET_COLOR_EFFECT %d\n",aux);
            break;
        }
        case DRV_WEBCAM_CMD_GET_COLOR_EFFECT:
        {
            ret = EPDK_FAIL;
            hal_log_err("DRV_WEBCAM_CMD_GET_COLOR_EFFECT\n");
            break;
        }
        case DRV_WEBCAM_CMD_SET_AWB:
        {
            ret = EPDK_FAIL;
            hal_log_err("DRV_WEBCAM_CMD_SET_AWB %d\n",aux);
            break;
        }
        case DRV_WEBCAM_CMD_GET_AWB:
        {
            ret = EPDK_FAIL;
            hal_log_err("DRV_WEBCAM_CMD_GET_AWB\n");
            break;
        }
        case DRV_WEBCAM_CMD_SET_AE:
        {
            ret = EPDK_FAIL;
            hal_log_err("DRV_WEBCAM_CMD_SET_AE %d\n",aux);
            break;
        }
        case DRV_WEBCAM_CMD_GET_AE:
        {
            ret = EPDK_FAIL;
            hal_log_err("DRV_WEBCAM_CMD_GET_AE\n");
            break;
        }
        case DRV_WEBCAM_CMD_SET_BRIGHT:
        {
            ret = EPDK_FAIL;
            hal_log_err("DRV_WEBCAM_CMD_SET_BRIGHT %d\n",aux);
            break;
        }
        case DRV_WEBCAM_CMD_GET_BRIGHT:
        {
            ret = EPDK_FAIL;
            hal_log_err("DRV_WEBCAM_CMD_GET_BRIGHT\n");
            break;
        }
        case DRV_WEBCAM_CMD_SET_CONTRAST:
        {
            ret = EPDK_FAIL;
            hal_log_err("DRV_WEBCAM_CMD_SET_CONTRAST %d\n",aux);
            break;
        }
        case DRV_WEBCAM_CMD_GET_CONTRAST:
        {
            ret = EPDK_FAIL;
            hal_log_err("DRV_WEBCAM_CMD_GET_CONTRAST\n");
            break;
        }
        case DRV_WEBCAM_CMD_SET_BAND:
        {
            ret = EPDK_FAIL;
            hal_log_err("DRV_WEBCAM_CMD_SET_BAND %d\n",aux);
            break;
        }
        case DRV_WEBCAM_CMD_GET_BAND:
        {
            ret = EPDK_FAIL;
            hal_log_err("DRV_WEBCAM_CMD_GET_BAND\n");
            break;
        }
        case DRV_WEBCAM_CMD_GET_PROGRSSV_INFO:
        {
            ret = 1;//bProgressiveSrc;
            //hal_log_err("DRV_WEBCAM_CMD_GET_PROGRSSV_INFO[%d]\n",bProgressiveSrc);
            break;
        }
        case DRV_WENCAM_CMD_SET_TRANSPORT_CB:
        {
            hal_log_info("DRV_WENCAM_CMD_SET_TRANSPORT_CB[%X]\n", pbuffer);
            pWebcamDevNode->tran_cb = (transport_cb_t)pbuffer;
            ret = EPDK_OK;
            hal_log_err("DRV_WENCAM_CMD_SET_TRANSPORT_CB[%X]\n",pbuffer);
            break;
        }
        case DRV_WENCAM_CMD_GET_IRQ_CB:
        {
            uvc_irq_t *cb = (uvc_irq_t *)pbuffer;

            //hal_log_info("DRV_WENCAM_CMD_GET_IRQ_CB, %x\n", pWebcamDevNode->irq_cb);
            ret = EPDK_OK;
            *cb = pWebcamDevNode->irq_cb;
            hal_log_err("DRV_WENCAM_CMD_GET_IRQ_CB[%X]\n",pbuffer);
            break;

        }
        case DRV_WENCAM_CMD_WEBCAM_INSERT:
        {
            __s32 frame_id;
            __s32 index;

            if(pWebcamDevNode->capture == CAPTURE_ON && pWebcamDevNode->tran_cb != NULL)
            {
                //hal_log_info("DRV_WENCAM_CMD_WEBCAM_INSERT 1\n");
                frame_id = pWebcamDevNode->free2->delete_element(pWebcamDevNode->free2);
                if (frame_id != -1)
                {//在free中请求buffer成功
                    index = translate_frame_id_to_index(frame_id);
                    pWebcamDevNode->tran_cb(pWebcamDevNode->webcam_frame[index].addr[0], (__u32)NULL, (__u32)NULL);
                    pWebcamDevNode->frame_id_last = frame_id;
                    pWebcamDevNode->capture = CAPTURE_ON_AND_CALLBACK;
                }
                else
                {
                    hal_log_info("ERROR:webcam no buffer! ???? \n");
                }
            }
            else if(pWebcamDevNode->capture == CAPTURE_REMOVE && pWebcamDevNode->tran_cb != NULL &&
                    pWebcamDevNode->used_addr0 != (__u32)NULL)
            {
                hal_log_info("DRV_WENCAM_CMD_WEBCAM_INSERT 2\n");
                pWebcamDevNode->tran_cb(pWebcamDevNode->used_addr0, (__u32)NULL, (__u32)NULL);
                pWebcamDevNode->capture = CAPTURE_ON_AND_CALLBACK;
            }
            hal_log_err("DRV_WENCAM_CMD_WEBCAM_INSERT\n");
            ret = EPDK_OK;
            break;
        }
        case DRV_WENCAM_CMD_WEBCAM_MOVED:
        {
            //hal_log_info("DRV_WENCAM_CMD_WEBCAM_MOVED, (%x,%x)\n", aux, pbuffer);
            pWebcamDevNode->capture = CAPTURE_REMOVE;
            pWebcamDevNode->used_addr0 = (__u32)aux;
            pWebcamDevNode->used_addr1 = (__u32)pbuffer;
            hal_log_err("DRV_WENCAM_CMD_WEBCAM_MOVED\n");
            ret = EPDK_OK;
            break;
        }
        default:
        {
            hal_log_err("Unkonwn Command...\n");
            ret=EPDK_FAIL;
            break;
        }
    }

    WEBCAM_OpUnlock();

    return ret;
}

__s32 WEBCAM_DEV_NODE_Init_Part1(void)
{
    __u8    err;
    if(pWebcamDevNode)
    {
        hal_log_err("webcam device node resource has been requested already!\n");
        return EPDK_OK;
    }
    pWebcamDevNode = (__webcam_dev_t*)hal_malloc(sizeof(__webcam_dev_t));
    if(!pWebcamDevNode)
    {
        hal_log_info("request memory for webcam device handle failed!\n");
        return EPDK_FAIL;
    }
    memset(pWebcamDevNode, 0, sizeof(__webcam_dev_t));

    pWebcamDevNode->irq_cb  = webcam_irq_handle;
    pWebcamDevNode->tran_cb = NULL;

    pWebcamDevNode->webcam_lock = hal_sem_create(1);
    if(NULL == pWebcamDevNode->webcam_lock)
    {
        hal_log_info("create semaphore webcam_lock fail\n");
        goto __err0;
    }
    pWebcamDevNode->full2 = webcam_linklist_manager_init();
    pWebcamDevNode->free2 = webcam_linklist_manager_init();
    if(NULL==pWebcamDevNode->full2 || NULL==pWebcamDevNode->free2)
    {
        hal_log_info("create webcam linklist manager fail\n");
        goto __err1;
    }
    pWebcamDevNode->full2->initial(pWebcamDevNode->full2, WEBCAM_LISTTYPE_FULL);
    pWebcamDevNode->free2->initial(pWebcamDevNode->free2, WEBCAM_LISTTYPE_FREE);
    return EPDK_OK;
__err1:
    if(pWebcamDevNode->full2)
    {
        pWebcamDevNode->full2->exit(pWebcamDevNode->full2);
        pWebcamDevNode->full2 = NULL;
    }
    if(pWebcamDevNode->free2)
    {
        pWebcamDevNode->free2->exit(pWebcamDevNode->free2);
        pWebcamDevNode->free2 = NULL;
    }
    hal_sem_delete(pWebcamDevNode->webcam_lock);
    pWebcamDevNode->webcam_lock = NULL;
__err0:
    hal_log_info("%s %d %s pWebcamDevNode:%x!\n", __FILE__, __LINE__, __func__, pWebcamDevNode);
    hal_free(pWebcamDevNode);
    pWebcamDevNode = NULL;
    return EPDK_FAIL;
}
//__s32 WEBCAM_DEV_NODE_Init_Part2(void)
//{
//    return EPDK_OK;
//}

__s32 WEBCAM_DEV_NODE_Exit(void)
{
    __u8    err;

    if(NULL == pWebcamDevNode)
    {
        hal_log_err("webcam dev node already exit!\n");
        return EPDK_OK;
    }
    if(pWebcamDevNode->full2)
    {
        pWebcamDevNode->full2->exit(pWebcamDevNode->full2);
        pWebcamDevNode->full2 = NULL;
    }
    if(pWebcamDevNode->free2)
    {
        pWebcamDevNode->free2->exit(pWebcamDevNode->free2);
        pWebcamDevNode->free2 = NULL;
    }
    if(pWebcamDevNode->webcam_lock)
    {
        hal_sem_delete(pWebcamDevNode->webcam_lock);
        pWebcamDevNode->webcam_lock = NULL;
    }

    hal_log_info("%s %d %s pWebcamDevNode:%x!\n", __FILE__, __LINE__, __func__, pWebcamDevNode);
    hal_free(pWebcamDevNode);
    pWebcamDevNode = NULL;
    return EPDK_OK;
}







