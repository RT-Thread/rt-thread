/*
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-xx-xx     CDT          first version
 */

#ifndef __DRV_MCAN_H__
#define __DRV_MCAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "drv_can.h"

/* The arguments of RT command RT_CAN_CMD_SET_CANFD */
#define MCAN_FD_CLASSICAL                   0       /* CAN classical */
#define MCAN_FD_ISO_FD_NO_BRS               1       /* ISO CAN FD without BRS */
#define MCAN_FD_ISO_FD_BRS                  2       /* ISO CAN FD with BRS */
#define MCAN_FD_NON_ISO_FD_NO_BRS           3       /* non-ISO CAN FD without BRS */
#define MCAN_FD_NON_ISO_FD_BRS              4       /* non-ISO CAN FD with BRS */

#define MCAN_FD_ARG_MIN                     MCAN_FD_ISO_FD_NO_BRS
#define MCAN_FD_ARG_MAX                     MCAN_FD_NON_ISO_FD_BRS

#ifdef __cplusplus
}
#endif

#endif /*__DRV_MCAN_H__ */

/************************** end of file ******************/
