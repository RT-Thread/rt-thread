/****************************************************************************
 *
 * File Name
 *  ota.c
 * Author
 *  wangk
 * Date
 *  2020/02/28
 * Descriptions:
 * OTA远程升级接口实现
 *
 ******************************************************************************/
/*----------------------------------------------------------------------------*
**                             Dependencies                                   *
**----------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <rtthread.h>
#include <rthw.h>
#include <fal.h>
//#include <ymodem.h>

//#include "ota.h"

/**---------------------------------------------------------------------------*
 **                            Debugging Flag                                 *
 **---------------------------------------------------------------------------*/

/**---------------------------------------------------------------------------*
**                             Compiler Flag                                  *
**----------------------------------------------------------------------------*/
#ifdef __cplusplus
extern   "C"
{
#endif

/*----------------------------------------------------------------------------*
**                             Mcaro Definitions                              *
**----------------------------------------------------------------------------*/
#define DEFAULT_DOWNLOAD_PART "download"

/*----------------------------------------------------------------------------*
**                             Data Structures                                *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Local Vars                                     *
**----------------------------------------------------------------------------*/
static char* recv_partition = DEFAULT_DOWNLOAD_PART;
static size_t update_file_total_size, update_file_cur_size;
static const struct fal_partition * dl_part = RT_NULL;

/*----------------------------------------------------------------------------*
**                             Local Function                                 *
**----------------------------------------------------------------------------*/
/*************************************************
* Function: ymodem_on_begin
* Description: ymodem通信开始回调函数
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
static enum rym_code ymodem_on_begin(struct rym_ctx *ctx, rt_uint8_t *buf, rt_size_t len)
{
    char *file_name, *file_size;

    /* calculate and store file size */
    file_name = (char *)&buf[0];
    file_size = (char *)&buf[rt_strlen(file_name) + 1];
    update_file_total_size = atol(file_size);
    rt_kprintf("Ymodem file_size:%d\n", update_file_total_size);

    update_file_cur_size = 0;

    /* Get download partition information and erase download partition data */
    if ((dl_part = fal_partition_find(recv_partition)) == RT_NULL)
    {
        rt_kprintf("Firmware download failed! Partition (%s) find error!", recv_partition);
        return RYM_CODE_CAN;
    }

    if (update_file_total_size > dl_part->len)
    {
        rt_kprintf("Firmware is too large! File size (%d), '%s' partition size (%d)", update_file_total_size, recv_partition, dl_part->len);
        return RYM_CODE_CAN;
    }

    rt_kprintf("Start erase. Size (%d)", update_file_total_size);

    /* erase DL section */
    if (fal_partition_erase(dl_part, 0, update_file_total_size) < 0)
    {
        rt_kprintf("Firmware download failed! Partition (%s) erase error!", dl_part->name);
        return RYM_CODE_CAN;
    }

    return RYM_CODE_ACK;
}

/*************************************************
* Function: ymodem_on_data
* Description: ymodem数据收取回调函数
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
static enum rym_code ymodem_on_data(struct rym_ctx *ctx, rt_uint8_t *buf, rt_size_t len)
{
    /* write data of application to DL partition  */
    if (fal_partition_write(dl_part, update_file_cur_size, buf, len) < 0)
    {
        rt_kprintf("Firmware download failed! Partition (%s) write data error!", dl_part->name);
        return RYM_CODE_CAN;
    }

    update_file_cur_size += len;

    return RYM_CODE_ACK;
}

/*----------------------------------------------------------------------------*
**                             Public Function                                *
**----------------------------------------------------------------------------*/
/*************************************************
* Function: OTA_Download
* Description: 执行OTA远程固件下载(阻塞)
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
bool OTA_Download(rt_device_t ptDevice)
{
    struct rym_ctx rctx;
	bool ret = false;

    recv_partition = DEFAULT_DOWNLOAD_PART;
    rt_kprintf("Default save firmware on download partition.\n");

    rt_kprintf("Warning: Ymodem has started! This operator will not recovery.\n");
    rt_kprintf("Please select the ota firmware file and use Ymodem to send.\n");

    if (!rym_recv_on_device(&rctx, ptDevice, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                            ymodem_on_begin, ymodem_on_data, NULL, 10))
    {
        rt_kprintf("Download firmware to flash success.\n");

		ret = true;
    }
    else
    {
        rt_kprintf("Update firmware fail.\n");
    }

    return ret;
}

/*************************************************
* Function: OTA_Reboot
* Description: 重启升级
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
void OTA_Reboot(void)
{
	rt_kprintf("System now will restart...\r\n");
	
	/* Reset the device, Start new firmware */
    rt_hw_cpu_reset();
}

/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif
// End of ota.c
