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
#ifndef __DRIVER_WEBCAM_H__
#define __DRIVER_WEBCAM_H__
#include "typedef.h"
#include "fb.h"

#define WEBCAM_BUFFER_NUM   6
#define WEBCAM_MODE_NUM     8

typedef struct JPEG_FRAME_INFO_
{
    void* jpegData;
    __u32 jpegData_len;

    __s32 pic_width;
    __s32 pic_height;
    __u32 format;
    __u8* y_buf;
    __u8* c_buf;

}_jpeg_frame_info;

typedef enum tag_BUF_SCRAB_MODE_WEBCAM
{
    WEBCAM0_FULL  = 0 ,       //WEBCAM0 on one buffer
    WEBCAM1_FULL  = 1 ,       //WEBCAM1 on one buffer

    WEBCAM_01_LR  = 2 ,       //WEBCAM0(L) and WEBCAM1(R) with same size and format parallel on one buffer
    WEBCAM_10_LR  = 3 ,       //WEBCAM1(L) and WEBCAM0(R) with same size and format parallel on one buffer

    WEBCAM_01_UD  = 4 ,       //WEBCAM0(L) and WEBCAM1(R) with same size and format sequential on one buffer
    WEBCAM_10_UD  = 5 ,       //WEBCAM1(L) and WEBCAM0(R) with same size and format sequential on one buffer

    WEBCAM0_TDM_2CH_2X1 = 6 ,     //WEBCAM0 TDM CH0/1 with same size and format
    WEBCAM0_TDM_4CH_2X2 = 7 ,     //WEBCAM0 TDM CH0/1 + CH2/3 with same size and format

    WEBCAM_SC_NA = 0xff,
}__buf_scrab_mode_webcam_t;

typedef struct tag_WEBCAM_MODE
{

    __pixel_yuvfmt_t    color_format; //__pixel_yuvfmt_t
    __u32               component_seq;//__yuv_seq_t + __bayer_seq_t
    __u32               store_mode;   //__yuv_mod_t + __bayer_store_mode_t
    __rectsz_t          size;
    __u32               frame_rate;    //Hz, x1000
    __u32               frame_period;  //us
    __cs_mode_t             color_space;
//=========add for WEBCAM0+WEBCAM1 ===============
    __buf_scrab_mode_webcam_t  webcam_buf_scrab_mode;
//========================

}__webcam_mode_t;

typedef struct tag_WEBCAM_MODE_ALL
{
    __u32             number;
    __webcam_mode_t      webcam_mode[WEBCAM_MODE_NUM];
}__webcam_mode_all_t;


typedef enum  __DRV_WEBCAM_CMD_SET
{
    DRV_WEBCAM_CMD_NONE = 0,
    DRV_WEBCAM_CMD_INIT,                        //ret = EPDK_OK/EPDK_FAIL
    DRV_WEBCAM_CMD_EXIT,                        //ret = EPDK_OK/EPDK_FAIL
    DRV_WEBCAM_CMD_SET_MODE,                    //pbuffer = __csi_mode_t*, ret = EPDK_OK/EPDK_FAIL
    DRV_WEBCAM_CMD_GET_MODE,                    //pbuffer = __csi_mode_t*, ret = EPDK_OK/EPDK_FAIL
    DRV_WEBCAM_CMD_GET_MODE_ALL,                //pbuffer = __csi_mode_total_t *
    DRV_WEBCAM_CMD_CAPTURE_ON,                  //ret = EPDK_OK/EPDK_FAIL
    DRV_WEBCAM_CMD_CAPTURE_OFF,                 //ret = EPDK_OK/EPDK_FAIL
    DRV_WEBCAM_CMD_REQUEST_FRAME,               //pbuffer= (__csi_frame_t**), ret = EPDK_OK/EPDK_FAIL
    DRV_WEBCAM_CMD_RELEASE_FRAME,               //aux = frame_id, ret = EPDK_OK/EPDK_FAIL
    DRV_WEBCAM_CMD_SET_PTS,                     //**absence**//aux = pts(__u32)
    DRV_WEBCAM_CMD_GET_PTS,                     //**absence**//ret=pts(__u32)
    DRV_WEBCAM_CMD_SET_PTS_MODE,                //**absence**//设置PTS的获取方式，aux = 0:CSI自己算PTS; 1:通过回调函数得到PTS; 2.不需要PTS
    DRV_WEBCAM_CMD_INSTALL_CALLBACK_GET_PTS,    //**absence**//注册回调函数,得到PTS。该callback的原型为CB_GetPTS,参数*arg是__s64*的指针,表示PTS，单位us. *pbuffer = callback
    DRV_WEBCAM_CMD_SET_FRAME_QUEUE,             //设置frame queue.必须在capture_on之前设置。因为capture off会清掉. pbuffer = __csi_frame_queue_t*,主要是设置buffer和frame_id，其他的参数还是由csidrv决定.
    DRV_WEBCAM_CMD_SET_COLOR_EFFECT,            //**absence**//aux = color effet
    DRV_WEBCAM_CMD_GET_COLOR_EFFECT,            //**absence**//ret = color effet
    DRV_WEBCAM_CMD_SET_AWB,                     //**absence**//aux = awb
    DRV_WEBCAM_CMD_GET_AWB,                     //**absence**//ret = awb
    DRV_WEBCAM_CMD_SET_AE,                      //**absence**//aux = ae
    DRV_WEBCAM_CMD_GET_AE,                      //**absence**//ret = ae
    DRV_WEBCAM_CMD_SET_BRIGHT,                  //**absence**//aux = bright
    DRV_WEBCAM_CMD_GET_BRIGHT,                  //**absence**//ret = bright
    DRV_WEBCAM_CMD_SET_CONTRAST,                //**absence**//aux = contrast
    DRV_WEBCAM_CMD_GET_CONTRAST,                //**absence**//ret = contrast
    DRV_WEBCAM_CMD_SET_BAND,                    //**absence**//aux = band
    DRV_WEBCAM_CMD_GET_BAND,                    //**absence**//ret = band//add 2011-8-3 13:13:13
    DRV_WEBCAM_CMD_GET_PROGRSSV_INFO,           //**absence**//ret = b_progr
    DRV_WEBCAM_CMD_SET_MASTER_PORT = DRV_WEBCAM_CMD_GET_PROGRSSV_INFO,//**absence**
    DRV_WEBCAM_CMD_GET_MASTER_PORT,             //**absence**

    DRV_WENCAM_CMD_SET_TRANSPORT_CB,
    DRV_WENCAM_CMD_GET_IRQ_CB,
    DRV_WENCAM_CMD_WEBCAM_INSERT,
    DRV_WENCAM_CMD_WEBCAM_MOVED,

    DRV_WEBCAM_CMD_,


}__drv_WEBCAM_cmd_set_t;


typedef struct tag_WEBCAM_FRAME
{
    __s32               frame_id;

    __bool              bProgressiveSrc;    // Indicating the source is progressive or not
    __bool              bTopFieldFirst;     // VPO should check this flag when bProgressiveSrc is FALSE
    __u16               eAspectRatio;       //the source picture aspect ratio
    __rect_t            src_rect;           // source valid size, 宏块对齐的图像大小, 一般就是frame buffer了
    __rect_t            dst_rect;           // source display size,真实图像的位置大小
    __u32               addr[3];            // data buffer address

    __u16               color_format; //same with __webcam_mode_t
    __u32               component_seq;//same with __webcam_mode_t
    __u32               store_mode;   //same with __webcam_mode_t
    __u16               frame_rate;   //same with __webcam_mode_t

    __s64               uPts;         //us
    __s32               bPtsValid;
}__webcam_frame_t;

typedef struct tag_WEBCAM_FRAME_QUEUE
{
    __s32               num;    //有效的帧个数，num <= WEBCAM_BUFFER_NUM
    __webcam_frame_t    webcam_frame_array[WEBCAM_BUFFER_NUM];
} __webcam_frame_queue_t;




typedef enum __DRV_WEBCAM_STATUS
{
    WEBCAM_STATUS_NONE          = 0,
    WEBCAM_STATUS_CAPTURE_ON,
    WEBCAM_STATUS_CAPTURE_OFF

}__drv_webcam_status_t;




typedef __s32   (* transport_cb_t )(__u32 addr0, __u32 addr1, __u32 addr2);
typedef __s32   (* uvc_irq_t)(__u32* addr0, __u32* addr1, __u32* addr2 );









#endif  // __DRIVER_WEBCAM_H__
