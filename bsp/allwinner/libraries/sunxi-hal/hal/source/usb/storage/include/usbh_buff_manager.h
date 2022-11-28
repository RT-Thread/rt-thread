/*
********************************************************************************************************************
*                                              usb_host
*
*                              (c) Copyright 2007-2009, holi.China
*                                       All Rights Reserved
*
* File Name     : msc_buff_manager.h
*
* Author        : javen
*
* Version       : 2.0
*
* Date          : 2009.08.19
*
* Description   :
*
* History       :
*     v1.0  holi  2008.11.22 - 读写速度快, 但是只支持单个lun
*     v2.0  javen 2009.08.19 - 支持多个lun 和 多种类型的设备
********************************************************************************************************************
*/
#ifndef _USBH_BUFF_MANAGER_H_
#define _USBH_BUFF_MANAGER_H_

typedef void       *__hdle;

/* usb host 临时 buffer */
typedef struct tag_usbh_temp_buff
{
    unsigned int num;            /* buffer在整个buffer管理里面的号码     */

    unsigned int dev_id;         /* 设备id, 确定设备身份的唯一标识       */
    unsigned int start_lba;      /* 起始扇区                             */
    unsigned int end_lba;        /* 结束扇区, 最后一个有效扇区           */
    unsigned int sector_size;    /* 扇区大小                             */

    unsigned int used_time;      /* 被文件系统使用的次数                 */

    void *buff;         /* 存放从设备读取的数据                 */
    unsigned int buff_len;       /* buffer的大小                         */

    unsigned int is_valid;       /* 这个buff的内容是否有效               */
    unsigned int is_busy;        /* 防止buff正在接收device数据，但是
                           又被usbh_buff_manager设置为无效      */
} usbh_temp_buff_t;


#define  USBH_TEMP_BUFFER_MAX_NUM    8              //buffer的个数, 先分4个，不够用再加
#define  USBH_TEMP_BUFFER_MAX_LEN    (32 * 1024)    //32k, 必须是k的倍数, 因为要palloc

typedef struct tag_usbh_buff_manager
{
    unsigned int temp_buff_len;    /* 临时buff的大小, 它决定了usbh_temp_buff_t里buff_len的大小 */
    unsigned int temp_buff_nr;     /* 临时buff的个数 */

    usbh_temp_buff_t buff_array[USBH_TEMP_BUFFER_MAX_NUM];
} usbh_buff_manager_t;


//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
int usbh_msc_special_read(void *pBuffer,
                          unsigned int blk,
                          unsigned int n,
                          __hdle hDev,
                          unsigned int dev_id,
                          unsigned int secter_size,
                          void *blk_read_entry);

int usbh_msc_special_write(void *pBuffer,
                           unsigned int blk,
                           unsigned int n,
                           __hdle hDev,
                           unsigned int dev_id,
                           unsigned int secter_size,
                           void *blk_write_entry);

int set_usbh_temp_buff_invalid_by_dev(unsigned int dev_id);
int set_all_usbh_temp_buff_invalid(void);

int init_usbh_buff_manager(void);
int exit_usbh_buff_manager(void);

#endif





