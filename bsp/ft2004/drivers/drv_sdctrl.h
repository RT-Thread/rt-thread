/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-03-18     Carl      the first version
 */

#ifndef __DRV_SDCTRL_H__
#define __DRV_SDCTRL_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define SDCTR_CMD_IS_COMPLETE_FLG 0x1UL /* Command is  complete */
#define SDCTR_WRITE_IS_COMPLETE_FLG 0x2UL
#define SDCTR_READ_IS_COMPLETE_FLG 0x4UL
#define SDCTR_CMD_IS_ERROR_FLG 0x8UL
#define SDCTR_CMD_CRC_IS_ERROR_FLG 0x10UL     /* Command CRC error */
#define SDCTR_DMA_IS_ERROR_FLG 0x20UL         /*  */
#define SDCTR_CARD_REMOVE_FLG 0x40UL          /* Card remove */
#define SDCTR_CMD_TIMEOUT_FLG 0x70UL          /* command timeout */
#define SDCTR_CMD_RECEIVE_IS_ERROR_FLG 0x80UL /*  CMD receive is error  */

#ifndef SDCTR_BUFF_SIZE
#define SDCTR_BUFF_SIZE (512 * 128)
#endif

#ifndef SDCTR_ALIGN_LEN
#define SDCTR_ALIGN_LEN (32)
#endif

    void ft2004_mmcsd_change(void);
    rt_bool_t ft2004_card_status(void);
    rt_err_t ft2004_card_remove_check(rt_int32_t timeout, rt_uint32_t *status);
    void ft2004_sdctrl_reset(void);
#ifdef __cplusplus
}
#endif

#endif // !
