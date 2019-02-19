/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#ifndef __REGOPR_H__
#define __REGOPR_H__

#include <stdint.h>
#include "asmopr.h"
#include <rthw.h>

/* Insert several NOPs and prevent optimization */
#define __INSNOPS   _ARM_NOP();_ARM_NOP();_ARM_NOP()

/*
 * M(mask)--get/set valid bit
 * G(get)/S(set)--get/set
 * WA(wait all)--Waiting for the specified bit of the mask (all bits are not specified)
 * W1(wait one)--Wait for any bit in the valid bit
 * WZ(wait zero)--Waiting for 0
 */
#define REG32___G___(reg)                               HWREG32(reg)
#define REG32_M_G___(reg, mask)                         (HWREG32(reg) & (mask))
#define REG32_M_S___(reg, mask, val)                    HWREG32(reg) = (HWREG32(reg) & ~(mask)) | ((uint32_t)(val) & (mask))
#define REG32___S___(reg, val)                          HWREG32(reg) = (uint32_t)(val)
#define REG32_____WA(reg, val)                          while ((HWREG32(reg)) != (val))
#define REG32_____WZ(reg)                               while ((HWREG32(reg)) != 0)
#define REG32_M___WA(reg, mask, val)                    while ((HWREG32(reg) & (mask)) != (val))
#define REG32_M___WZ(reg, mask)                         while ((HWREG32(reg) & (mask)) != 0)
#define REG32_M_S_WA(reg, mask, val)                    do {REG32_M_S___(reg, mask, val); __INSNOPS; REG32_M___WA(reg, mask, val);} while (0)
#define REG32_M_S_WZ(reg, mask, val)                    do {REG32_M_S___(reg, mask, val); __INSNOPS; REG32_M___WZ(reg, mask);} while (0)
#define REG32_M___W1(reg, mask)				            while(!(HWREG32(reg) & (mask))){}
#define REG32_M_S_W1(reg, mask, val)                    do {REG32_M_S___(reg, mask, val); __INSNOPS; REG32_M___W1(reg, mask, val);} while (0)

#define REG16___G___(reg)                               HWREG16(reg)
#define REG16_M_G___(reg, mask)                         (HWREG16(reg) & (mask))
#define REG16_M_S___(reg, mask, val)                    HWREG16(reg) = (HWREG16(reg) & ~(mask)) | ((uint32_t)(val) & (mask))
#define REG16___S___(reg, val)                          HWREG16(reg) = (uint16_t)(val)
#define REG16_____WA(reg, val)                          while ((HWREG16(reg)) != (val))
#define REG16_____WZ(reg)                               while ((HWREG16(reg)) != 0)
#define REG16_M___WA(reg, mask, val)                    while ((HWREG16(reg) & (mask)) != (val))
#define REG16_M___WZ(reg, mask)                         while ((HWREG16(reg) & (mask)) != 0)
#define REG16_M_S_WA(reg, mask, val)                    do {REG16_M_S___(reg, mask, val); __INSNOPS; REG16_M___WA(reg, mask, val);} while (0)
#define REG16_M_S_WZ(reg, mask, val)                    do {REG16_M_S___(reg, mask, val); __INSNOPS; REG16_M___WZ(reg, mask);} while (0)
#define REG16_M___W1(reg, mask)				            while (!(HWREG16(reg) & (mask))){}
#define REG16_M_S_W1(reg, mask, val)                    do {REG16_M_S___(reg, mask, val); __INSNOPS; REG16_M___W1(reg, mask, val);} while (0)

#define REG08___G___(reg)                               HWREG8(reg)
#define REG08_M_G___(reg, mask)                         (HWREG8(reg) & (mask))
#define REG08_M_S___(reg, mask, val)                    HWREG8(reg) = (HWREG8(reg) & ~(mask)) | ((uint32_t)(val) & (mask))
#define REG08___S___(reg, val)                          HWREG8(reg) = (uint8_t)(val)
#define REG08_____WA(reg, val)                          while ((HWREG8(reg)) != (val))
#define REG08_____WZ(reg)                               while ((HWREG8(reg)) != 0)
#define REG08_M___WA(reg, mask, val)                    while ((HWREG8(reg) & (mask)) != (val))
#define REG08_M___WZ(reg, mask)                         while ((HWREG8(reg) & (mask)) != 0)
#define REG08_M_S_WA(reg, mask, val)                    do {REG08_M_S___(reg, mask, val); __INSNOPS; REG08_M___WA(reg, mask, val);} while (0)
#define REG08_M_S_WZ(reg, mask, val)                    do {REG08_M_S___(reg, mask, val); __INSNOPS; REG08_M___WZ(reg, mask);} while (0)
#define REG08_M___W1(reg, mask)				            while (!(HWREG16(reg) & (mask))){}
#define REG08_M_S_W1(reg, mask, val)                    do {REG08_M_S___(reg, mask, val); __INSNOPS; REG08_M___W1(reg, mask, val);} while (0)

#endif
