/**
 *******************************************************************************
 * @file  hc32_ll_def.h
 * @brief This file contains LL common definitions: enumeration, macros and
  *       structures definitions.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_LL_DEF_H__
#define __HC32_LL_DEF_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <stddef.h>
#include <stdint.h>

/**
 * @addtogroup LL_Common
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup LL_Common_Global_Types LL Common Global Types
 * @{
 */

/**
 * @brief Single precision floating point number (4 byte)
 */
typedef float float32_t;

/**
 * @brief Double precision floating point number (8 byte)
 */
typedef double float64_t;

/**
 * @brief Function pointer type to void/void function
 */
typedef void (*func_ptr_t)(void);

/**
 * @brief Functional state
 */
typedef enum {
    DISABLE = 0U,
    ENABLE  = 1U,
} en_functional_state_t;

/**
 * @brief Flag status
 */
typedef enum {
    RESET = 0U,
    SET   = 1U,
} en_flag_status_t, en_int_status_t;
/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup LL_Common_Global_Macros LL Common Global Macros
 * @{
 */

/**
 * @defgroup Compiler_Macros Compiler Macros
 * @{
 */
#ifndef __UNUSED
#define __UNUSED                        __attribute__((unused))
#endif /* __UNUSED */

#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#ifndef __WEAKDEF
#define __WEAKDEF                   __attribute__((weak))
#endif /* __WEAKDEF */
#ifndef __ALIGN_BEGIN
#define __ALIGN_BEGIN               __attribute__((aligned(4)))
#endif /* __ALIGN_BEGIN */
#ifndef __NOINLINE
#define __NOINLINE                  __attribute__((noinline))
#endif /* __NOINLINE */
/* RAM functions are defined using the toolchain options.
Functions that are executed in RAM should reside in a separate source module.
Using the 'Options for File' dialog you can simply change the 'Code / Const'
area of a module to a memory space in physical RAM. */
#ifndef __RAM_FUNC
#define __RAM_FUNC
#endif /* __RAM_FUNC */
#ifndef __NO_INIT
#define __NO_INIT
#endif /* __NO_INIT */
#elif defined ( __GNUC__ ) && !defined (__CC_ARM) /*!< GNU Compiler */
#ifndef __WEAKDEF
#define __WEAKDEF                   __attribute__((weak))
#endif /* __WEAKDEF */
#ifndef __ALIGN_BEGIN
#define __ALIGN_BEGIN               __attribute__((aligned (4)))
#endif /* __ALIGN_BEGIN */
#ifndef __NOINLINE
#define __NOINLINE                  __attribute__((noinline))
#endif /* __NOINLINE */
#ifndef __RAM_FUNC
#define __RAM_FUNC                  __attribute__((long_call, section(".ramfunc")))
/* Usage: __RAM_FUNC void foo(void) */
#endif /* __RAM_FUNC */
#ifndef __NO_INIT
#define __NO_INIT                   __attribute__((section(".noinit")))
#endif /* __NO_INIT */
#elif defined (__ICCARM__)              /*!< IAR Compiler */
#ifndef __WEAKDEF
#define __WEAKDEF                   __weak
#endif /* __WEAKDEF */
#ifndef __ALIGN_BEGIN
#define __ALIGN_BEGIN               _Pragma("data_alignment=4")
#endif /* __ALIGN_BEGIN */
#ifndef __NOINLINE
#define __NOINLINE                  _Pragma("optimize = no_inline")
#endif /* __NOINLINE */
#ifndef __RAM_FUNC
#define __RAM_FUNC                  __ramfunc
#endif /* __RAM_FUNC */
#ifndef __NO_INIT
#define __NO_INIT                   __no_init
#endif /* __NO_INIT */
#elif defined (__CC_ARM)                /*!< ARM Compiler */
#ifndef __WEAKDEF
#define __WEAKDEF                   __attribute__((weak))
#endif /* __WEAKDEF */
#ifndef __ALIGN_BEGIN
#define __ALIGN_BEGIN               __align(4)
#endif /* __ALIGN_BEGIN */
#ifndef __NOINLINE
#define __NOINLINE                  __attribute__((noinline))
#endif /* __NOINLINE */
#ifndef __NO_INIT
#define __NO_INIT
#endif /* __NO_INIT */
/* RAM functions are defined using the toolchain options.
Functions that are executed in RAM should reside in a separate source module.
Using the 'Options for File' dialog you can simply change the 'Code / Const'
area of a module to a memory space in physical RAM. */
#ifndef __RAM_FUNC
#define __RAM_FUNC                  __attribute__((section("RAMCODE")))
#endif /* __RAM_FUNC */
#else
#error  "unsupported compiler!!"
#endif
/**
 * @}
 */

/**
 * @defgroup Extend_Macros Extend Macros
 * @{
 */
/* Decimal to BCD */
#define DEC2BCD(x)                      ((((x) / 10U) << 4U) + ((x) % 10U))

/* BCD to decimal */
#define BCD2DEC(x)                      ((((x) >> 4U) * 10U) + ((x) & 0x0FU))

/* Returns the dimension of an array */
#define ARRAY_SZ(x)                     ((sizeof(x)) / (sizeof((x)[0])))

/* Returns the minimum value out of two values */
#define LL_MIN(x, y)                    ((x) < (y) ? (x) : (y))

/* Returns the maximum value out of two values */
#define LL_MAX(x, y)                    ((x) > (y) ? (x) : (y))
/**
 * @}
 */

/**
 * @defgroup Check_Parameters_Validity Check Parameters Validity
 * @{
 */

/* Check Functional State */
#define IS_FUNCTIONAL_STATE(state)      (((state) == DISABLE) || ((state) == ENABLE))

/**
 * @defgroup Check_Address_Align_Validity Check Address Align Validity
 * @{
 */
#define IS_ADDR_ALIGN(addr, align)      (0UL == (((uint32_t)(addr)) & (((uint32_t)(align)) - 1UL)))
#define IS_ADDR_ALIGN_HALFWORD(addr)    (0UL == (((uint32_t)(addr)) & 0x1UL))
#define IS_ADDR_ALIGN_WORD(addr)        (0UL == (((uint32_t)(addr)) & 0x3UL))
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup Peripheral_Bit_Band Peripheral Bit Band
 * @{
 */
#define __PERIPH_BIT_BAND_BASE          (0x42000000UL)
#define __PERIPH_BASE                   (0x40000000UL)
#define __REG_OFS(regAddr)              ((regAddr) - __PERIPH_BASE)
#define __BIT_BAND_ADDR(regAddr, pos)   ((__REG_OFS(regAddr) << 5U) + ((uint32_t)(pos) << 2U) + __PERIPH_BIT_BAND_BASE)
#define PERIPH_BIT_BAND(regAddr, pos)   (*(__IO uint32_t *)__BIT_BAND_ADDR((regAddr), (pos)))
/**
 * @}
 */

/**
 * @defgroup Generic_Error_Codes Generic Error Codes
 * @{
 */
#define LL_OK                           (0)   /*!< No error */
#define LL_ERR                          (-1)  /*!< Non-specific error code */
#define LL_ERR_UNINIT                   (-2)  /*!< Module (or part of it) was not initialized properly */
#define LL_ERR_INVD_PARAM               (-3)  /*!< Provided parameter is not valid */
#define LL_ERR_INVD_MD                  (-4)  /*!< Operation not allowed in current mode */
#define LL_ERR_NOT_RDY                  (-5)  /*!< A requested final state is not reached */
#define LL_ERR_BUSY                     (-6)  /*!< A conflicting or requested operation is still in progress */
#define LL_ERR_ADDR_ALIGN               (-7)  /*!< Address alignment does not match */
#define LL_ERR_TIMEOUT                  (-8)  /*!< Time Out error occurred (e.g. I2C arbitration lost, Flash time-out, etc.) */
#define LL_ERR_BUF_EMPTY                (-9)  /*!< Circular buffer can not be read because the buffer is empty */
#define LL_ERR_BUF_FULL                 (-10) /*!< Circular buffer can not be written because the buffer is full */
/**
 * @}
 */

/**
 * @defgroup Chip_Module_Switch Chip Module Switch
 * @{
 */
#define DDL_ON                          (1U)
#define DDL_OFF                         (0U)
/**
 * @}
 */

/**
 * @defgroup Bit_Mask_Macros Bit Mask Macros
 * @{
 */
#define BIT_MASK_00                     (1UL << 0U)
#define BIT_MASK_01                     (1UL << 1U)
#define BIT_MASK_02                     (1UL << 2U)
#define BIT_MASK_03                     (1UL << 3U)
#define BIT_MASK_04                     (1UL << 4U)
#define BIT_MASK_05                     (1UL << 5U)
#define BIT_MASK_06                     (1UL << 6U)
#define BIT_MASK_07                     (1UL << 7U)
#define BIT_MASK_08                     (1UL << 8U)
#define BIT_MASK_09                     (1UL << 9U)
#define BIT_MASK_10                     (1UL << 10U)
#define BIT_MASK_11                     (1UL << 11U)
#define BIT_MASK_12                     (1UL << 12U)
#define BIT_MASK_13                     (1UL << 13U)
#define BIT_MASK_14                     (1UL << 14U)
#define BIT_MASK_15                     (1UL << 15U)
#define BIT_MASK_16                     (1UL << 16U)
#define BIT_MASK_17                     (1UL << 17U)
#define BIT_MASK_18                     (1UL << 18U)
#define BIT_MASK_19                     (1UL << 19U)
#define BIT_MASK_20                     (1UL << 20U)
#define BIT_MASK_21                     (1UL << 21U)
#define BIT_MASK_22                     (1UL << 22U)
#define BIT_MASK_23                     (1UL << 23U)
#define BIT_MASK_24                     (1UL << 24U)
#define BIT_MASK_25                     (1UL << 25U)
#define BIT_MASK_26                     (1UL << 26U)
#define BIT_MASK_27                     (1UL << 27U)
#define BIT_MASK_28                     (1UL << 28U)
#define BIT_MASK_29                     (1UL << 29U)
#define BIT_MASK_30                     (1UL << 30U)
#define BIT_MASK_31                     (1UL << 31U)
/**
 * @}
 */

/**
 * @defgroup Register_Macros Register Macros
 * @{
 */
#define RW_MEM8(addr)                   (*(volatile uint8_t *)(addr))
#define RW_MEM16(addr)                  (*(volatile uint16_t *)(addr))
#define RW_MEM32(addr)                  (*(volatile uint32_t *)(addr))

#define SET_REG_BIT(REG, BIT)           ((REG) |= (BIT))
#define SET_REG8_BIT(REG, BIT)          ((REG) |= ((uint8_t)(BIT)))
#define SET_REG16_BIT(REG, BIT)         ((REG) |= ((uint16_t)(BIT)))
#define SET_REG32_BIT(REG, BIT)         ((REG) |= ((uint32_t)(BIT)))

#define CLR_REG_BIT(REG, BIT)           ((REG) &= (~(BIT)))
#define CLR_REG8_BIT(REG, BIT)          ((REG) &= ((uint8_t)(~((uint8_t)(BIT)))))
#define CLR_REG16_BIT(REG, BIT)         ((REG) &= ((uint16_t)(~((uint16_t)(BIT)))))
#define CLR_REG32_BIT(REG, BIT)         ((REG) &= ((uint32_t)(~((uint32_t)(BIT)))))

#define READ_REG_BIT(REG, BIT)          ((REG) & (BIT))
#define READ_REG8_BIT(REG, BIT)         ((REG) & ((uint8_t)(BIT)))
#define READ_REG16_BIT(REG, BIT)        ((REG) & ((uint16_t)(BIT)))
#define READ_REG32_BIT(REG, BIT)        ((REG) & ((uint32_t)(BIT)))

#define CLR_REG(REG)                    ((REG) = (0U))
#define CLR_REG8(REG)                   ((REG) = ((uint8_t)(0U)))
#define CLR_REG16(REG)                  ((REG) = ((uint16_t)(0U)))
#define CLR_REG32(REG)                  ((REG) = ((uint32_t)(0UL)))

#define WRITE_REG(REG, VAL)             ((REG) = (VAL))
#define WRITE_REG8(REG, VAL)            ((REG) = ((uint8_t)(VAL)))
#define WRITE_REG16(REG, VAL)           ((REG) = ((uint16_t)(VAL)))
#define WRITE_REG32(REG, VAL)           ((REG) = ((uint32_t)(VAL)))

#define READ_REG(REG)                   (REG)
#define READ_REG8(REG)                  (REG)
#define READ_REG16(REG)                 (REG)
#define READ_REG32(REG)                 (REG)

#define MODIFY_REG(REGS, CLRMASK, SETMASK)    (WRITE_REG((REGS), (((READ_REG(REGS)) & (~(CLRMASK))) | ((SETMASK) & (CLRMASK)))))
#define MODIFY_REG8(REGS, CLRMASK, SETMASK)   (WRITE_REG8((REGS), (((READ_REG8((REGS))) & ((uint8_t)(~((uint8_t)(CLRMASK))))) | ((uint8_t)(SETMASK) & (uint8_t)(CLRMASK)))))
#define MODIFY_REG16(REGS, CLRMASK, SETMASK)  (WRITE_REG16((REGS), (((READ_REG16((REGS))) & ((uint16_t)(~((uint16_t)(CLRMASK))))) | ((uint16_t)(SETMASK) & (uint16_t)(CLRMASK)))))
#define MODIFY_REG32(REGS, CLRMASK, SETMASK)  (WRITE_REG32((REGS), (((READ_REG32((REGS))) & ((uint32_t)(~((uint32_t)(CLRMASK))))) | ((uint32_t)(SETMASK) & (uint32_t)(CLRMASK)))))
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_DEF_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
