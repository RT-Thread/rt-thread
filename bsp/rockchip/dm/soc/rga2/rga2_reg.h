/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#ifndef __ROCKCHIP_RGA2_REG_H__
#define __ROCKCHIP_RGA2_REG_H__

#define RGA2_SYS_CTRL                   0x000
#define RGA2_STATUS1                    0x00c
#define RGA2_INT                        0x010
#define RGA2_STATUS2                    0x01c
#define RGA2_VERSION_NUM                0x028
#define RGA2_CMD_REG_BASE               0x100

#define RGA2_MODE_CTRL                  0x00
#define RGA2_SRC_INFO                   0x04
#define RGA2_SRC_BASE0                  0x08
#define RGA2_SRC_VIR_INFO               0x18
#define RGA2_SRC_ACT_INFO               0x1c
#define RGA2_SRC_X_FACTOR               0x20
#define RGA2_SRC_Y_FACTOR               0x24
#define RGA2_SRC_BG_COLOR               0x28
#define RGA2_DST_INFO                   0x38
#define RGA2_DST_BASE0                  0x3c
#define RGA2_DST_VIR_INFO               0x48
#define RGA2_DST_ACT_INFO               0x4c

#define RGA2_SYS_AUTO_RESET             (1U << 5)
#define RGA2_SYS_AUTO_CLOCK             (1U << 2)
#define RGA2_SYS_START                  (1U << 0)
#define RGA2_SYS_SOFT_RESET             ((1U << 4) | (1U << 3))
#define RGA2_SYS_RESET_PROTECT          (1U << 6)

#define RGA2_INT_ALL_DONE_ENABLE        (1U << 10)
#define RGA2_INT_MMU_ERROR_ENABLE       (1U << 9)
#define RGA2_INT_BUS_ERROR_ENABLE       (1U << 8)
#define RGA2_INT_ALL_DONE_CLEAR         (1U << 6)
#define RGA2_INT_MMU_ERROR_CLEAR        (1U << 5)
#define RGA2_INT_BUS_ERROR_CLEAR        (1U << 4)
#define RGA2_INT_CURRENT_DONE_CLEAR     (1U << 7)
#define RGA2_INT_ALL_DONE               (1U << 2)
#define RGA2_INT_MMU_ERROR              (1U << 1)
#define RGA2_INT_BUS_ERROR              (1U << 0)
#define RGA2_INT_SCALE_ERROR_ENABLE     (1U << 18)
#define RGA2_INT_SCALE_ERROR_CLEAR      (1U << 19)
#define RGA2_INT_SCALE_ERROR            (1U << 17)

#define RGA2_INT_ERROR_MASK             (RGA2_INT_MMU_ERROR | \
                                         RGA2_INT_BUS_ERROR | \
                                         RGA2_INT_SCALE_ERROR)
#define RGA2_INT_ENABLE_MASK            (RGA2_INT_ALL_DONE_ENABLE | \
                                         RGA2_INT_MMU_ERROR_ENABLE | \
                                         RGA2_INT_BUS_ERROR_ENABLE | \
                                         RGA2_INT_SCALE_ERROR_ENABLE)
#define RGA2_INT_CLEAR_MASK             (RGA2_INT_ALL_DONE_CLEAR | \
                                         RGA2_INT_CURRENT_DONE_CLEAR | \
                                         RGA2_INT_MMU_ERROR_CLEAR | \
                                         RGA2_INT_BUS_ERROR_CLEAR | \
                                         RGA2_INT_SCALE_ERROR_CLEAR)

#endif /* __ROCKCHIP_RGA2_REG_H__ */
