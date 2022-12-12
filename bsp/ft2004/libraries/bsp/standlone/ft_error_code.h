/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:30
 * @LastEditTime: 2021-05-24 10:12:07
 * @Description:  This files is for error code functions
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef _FT_ERROR_CODE_H
#define _FT_ERROR_CODE_H

#include "ft_status.h"
#include "ft_types.h"

typedef ft_base_t ft_error_t;

/* 系统错误码模块定义 */
typedef enum _ft_errcode_module_mask
{
    errModGeneral = 0,
    errModBsp,
    ERR_MODE_UART,
    errModeI2c,
    errModeGmac,
    errModeSdCtrl,
    errCan,
    errGicV3,
    errQspi,
    ERR_MODE_SD_MMC,
    ERR_MODE_SPI,

    errModMaxMask = 255,
} ft_errcode_module_mask_t;

/* BSP模块的错误子模块定义 */
typedef enum _ft_errcode_bsp_mask
{
    errBspGeneral = 0,
    errBspClk,
    errBspRtc,
    errPort,
    errBspModMaxMask = 255
} ft_errcode_bsp_mask_t;

#define FT_ERRCODE_SYS_MODULE_OFFSET 24
#define FT_ERRCODE_SUB_MODULE_OFFSET 16

#define FT_ERRCODE_SYS_MODULE_MASK (0xff << FT_ERRCODE_SYS_MODULE_OFFSET) /* bit 24 .. 31 */
#define FT_ERRCODE_SUB_MODULE_MASK (0xff << FT_ERRCODE_SUB_MODULE_OFFSET) /* bit 16 .. 23 */
#define FT_ERRCODE_TAIL_VALUE_MASK (0xffff)                               /* bit  1 .. 15 */

/* Offset error code */
#define FT_ERRCODE_OFFSET(code, offset, mask) \
    (((code) << offset) & mask)

/* Assembly error code */
#define FT_MAKE_ERRCODE(sys_mode, sub_mode, tail)                                              \
    ((FT_ERRCODE_OFFSET(sys_mode, FT_ERRCODE_SYS_MODULE_OFFSET, FT_ERRCODE_SYS_MODULE_MASK)) | \
     (FT_ERRCODE_OFFSET(sub_mode, FT_ERRCODE_SUB_MODULE_OFFSET, FT_ERRCODE_SUB_MODULE_MASK)) | \
     (tail & FT_ERRCODE_TAIL_VALUE_MASK))
#define FT_CODE_ERR FT_MAKE_ERRCODE

#define ERR_SUCCESS FT_MAKE_ERRCODE(errModGeneral, errBspGeneral, FST_SUCCESS) /* 成功 */
#define ERR_GENERAL FT_MAKE_ERRCODE(errModGeneral, errBspGeneral, FST_FAILURE) /* 一般错误 */

#endif
