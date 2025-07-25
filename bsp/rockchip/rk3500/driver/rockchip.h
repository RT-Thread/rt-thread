/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#ifndef __ROCKCHIP_H__
#define __ROCKCHIP_H__

#include <rthw.h>

#define rk_clrsetreg(addr, clr, set)    HWREG32(addr) = (((clr) | (set)) << 16 | (set))
#define rk_clrreg(addr, clr)            HWREG32(addr) = ((clr) << 16)
#define rk_setreg(addr, set)            HWREG32(addr) = ((set) << 16 | (set))

#define HIWORD_UPDATE(val, mask, shift) ((val) << (shift) | (mask) << ((shift) + 16))

#endif /* __ROCKCHIP_H__ */
