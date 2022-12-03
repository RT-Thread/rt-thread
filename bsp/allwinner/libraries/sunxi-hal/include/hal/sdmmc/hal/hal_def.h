/*
 * Copyright (C) 2017 ALLWINNERTECH TECHNOLOGY CO., LTD. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *    3. Neither the name of ALLWINNERTECH TECHNOLOGY CO., LTD. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _DRIVER_CHIP_HAL_DEF_H_
#define _DRIVER_CHIP_HAL_DEF_H_

#include "chip.h"
#include "../sys/compiler.h"
//#include "kernel/os/os_common.h"
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
    #define   __I     volatile             /*!< Defines 'read only' permissions                 */
#else
    #define   __I     volatile const       /*!< Defines 'read only' permissions                 */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */


/*
 * Bitwise operation
 */
#define HAL_BIT(pos)                        (1U << (pos))

#define HAL_SET_BIT(reg, mask)              ((reg) |= (mask))
#define HAL_CLR_BIT(reg, mask)              ((reg) &= ~(mask))
#define HAL_GET_BIT(reg, mask)              ((reg) & (mask))
#define HAL_GET_BIT_VAL(reg, shift, vmask)  (((reg) >> (shift)) & (vmask))

#define HAL_MODIFY_REG(reg, clr_mask, set_mask) \
    ((reg) = (((reg) & (~(clr_mask))) | (set_mask)))

/*
 * Macros for accessing LSBs of a 32-bit register (little endian only)
 */
#define HAL_REG_32BIT(reg_addr)  (*((__IO uint32_t *)(reg_addr)))
#define HAL_REG_16BIT(reg_addr)  (*((__IO uint16_t *)(reg_addr)))
#define HAL_REG_8BIT(reg_addr)   (*((__IO uint8_t  *)(reg_addr)))

/* Macro for counting the element number of an array */
#define HAL_ARRAY_SIZE(a)   (sizeof((a)) / sizeof((a)[0]))

/* Wait forever timeout value */
#define HAL_WAIT_FOREVER    OS_WAIT_FOREVER

#define HAL_SIZE_T      (unsigned long)
#define HAL_PT_TO_U(v)      (HAL_SIZE_T(v))

/*use to prinf and sscanf function to avoid compiler error*/
#define HAL_PR_SZ_L(v)      (HAL_SIZE_T(v))
#define HAL_PR_SZ(v)        ((unsigned int)(v))
#define HAL_PR_SZ_P(v)      ((unsigned int *)(v))


#define HAL_WMB()       {dsb(0xf);}

/**
 * @brief HAL Status value
 */
typedef enum
{
    HAL_OK      = 0,    /* success */
    HAL_ERROR   = -1,   /* general error */
    HAL_BUSY    = -2,   /* device or resource busy */
    HAL_TIMEOUT = -3,   /* wait timeout */
    HAL_INVALID = -4    /* invalid argument */
} HAL_Status;

#ifdef __cplusplus
}
#endif

#endif /* _DRIVER_CHIP_HAL_DEF_H_ */
