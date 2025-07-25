 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file       drv/io.h
 * @brief      Header File for register bits operation
 * @version    V1.0
 * @date       9. Oct 2020
 * @model      io
 ******************************************************************************/

#ifndef _DRV_IO_H_
#define _DRV_IO_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Bit field operate*/
#define REG64(addr)        (*(volatile uint64_t *)(addr))
#define REG32(addr)        (*(volatile uint32_t *)(addr))
#define REG16(addr)        (*(volatile uint16_t *)(addr))
#define REG8(addr)         (*(volatile uint8_t *)(addr))

/* Insert value to some field in reg, other field is set to 0(the field make macro) */
#define HAL_FMK(PER_REG_FIELD, val)                                         \
    (((val) << PER_REG_FIELD##_SHIFT) & PER_REG_FIELD##_MASK)

/* Get value of some field in reg(the field extract macro) */
#define HAL_FEXT(reg, PER_REG_FIELD)                                        \
    (((reg) & PER_REG_FIELD##_MASK) >> PER_REG_FIELD##_SHIFT)

/* Insert value to some field in reg, other field don't change(the field insert macro) */
#define HAL_FINS(reg, PER_REG_FIELD, val)                                   \
    ((reg) = ((reg) & ~PER_REG_FIELD##_MASK)                                \
             | HAL_FMK(PER_REG_FIELD, val))


/* Bit operate */
/* Set one value to 1, other bit don't change*/
#define HAL_BIT_SET(reg, bit) ((reg) = ((reg) | (1U << (bit))))

/* Set one value to 0, other bit don't change*/
#define HAL_BIT_CLR(reg, bit) ((reg) = ((reg) & (~(1U << (bit)))))

/* Get value of one bit(0/1) */
#define HAL_GET_BIT_VAL(reg, bit) (((reg)>> (bit)) & 1U)

/* Judge one bit is 1 or not */
#define HAL_IS_BIT_SET(reg, pos) (((reg) & (1U << (pos))) != 0x0U)

/* Judge one bit is 0 or not */
#define HAL_IS_BIT_CLR(reg, pos) (((reg) & (1U << (pos))) == 0x0U)

/* Set one value to bit, other bit don't change*/
#define HAL_BIT_INSR(reg, bit, val)                                       \
    ((reg) = (((reg) & (~(1U << (bit)))) | (((val) & 1U) << (bit))))


static inline uint8_t getreg8(volatile void *addr)
{
    return *(volatile uint8_t *)addr;
}

static inline void putreg8(uint8_t val, volatile void *addr)
{
    *(volatile uint8_t *)addr = val;
}

static inline uint16_t getreg16(volatile void *addr)
{
    return *(volatile uint16_t *)addr;
}

static inline void putreg16(uint16_t val, volatile void *addr)
{
    *(volatile uint16_t *)addr = val;
}

static inline uint32_t getreg32(volatile void *addr)
{
    return *(volatile uint32_t *)addr;
}

static inline void putreg32(uint32_t val, volatile void *addr)
{
    *(volatile uint32_t *)addr = val;
}

static inline uint64_t getreg64(volatile void *addr)
{
    return *(volatile uint64_t *)addr;
}

static inline void putreg64(uint32_t val, volatile void *addr)
{
    *(volatile uint64_t *)addr = val;
}

static inline uint32_t inl(void *addr)
{
    return *(volatile uint32_t *)addr;
}

static inline void outl(uint32_t val, void *addr)
{
    *(volatile uint32_t *)addr = val;
}

#ifdef __cplusplus
}
#endif

#endif /* _DRV_IO_H_ */
