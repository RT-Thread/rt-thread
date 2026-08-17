/**
 * \addtogroup PLA_BSP_SYSTEM
 * \{
 * \addtogroup BSP_DEFINITIONS SDK Platform Definitions
 *
 * \brief Platform definitions
 *
 * \{
 */

/**
 ****************************************************************************************
 *
 * @file sdk_defs.h
 *
 * @brief Central include header file with platform definitions.
 *
 * Copyright (c) 2023 Renesas Electronics. All rights reserved.
 *
 * This software ("Software") is owned by Renesas Electronics.
 *
 * By using this Software you agree that Renesas Electronics retains all
 * intellectual property and proprietary rights in and to this Software and any
 * use, reproduction, disclosure or distribution of the Software without express
 * written permission or a license agreement from Renesas Electronics is
 * strictly prohibited. This Software is solely for use on or in conjunction
 * with Renesas Electronics products.
 *
 * EXCEPT AS OTHERWISE PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, THE
 * SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. EXCEPT AS OTHERWISE
 * PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, IN NO EVENT SHALL
 * RENESAS ELECTRONICS BE LIABLE FOR ANY DIRECT, SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THE SOFTWARE.
 *
 ****************************************************************************************
 */

#ifndef __SDK_DEFS_H__
 #define __SDK_DEFS_H__

 #if !dg_configPTIM_APP
  #include "bsp_api.h"
  #include "config/bsp_definitions.h"
  #include "config/bsp_sflash_map_ra6w1.h"
  #include "config/bsp_defaults.h"
 #endif
 #include <stddef.h>
 #include <stdbool.h>
 #include <stdio.h>

 #ifdef __cplusplus
extern "C" {
 #endif

 #ifdef __GNUC__
  #define GCC_VERSION    (__GNUC__ * 10000       \
                          + __GNUC_MINOR__ * 100 \
                          + __GNUC_PATCHLEVEL__)

/* assert gcc version is at least 4.9.3 */
  #if GCC_VERSION < 40903
   #error "Please use gcc version 4.9.3 or newer!"
  #endif
 #endif

 #include "bsp_api.h"

 #ifndef BSP_DEVICE_REVISION
  #error "BSP_DEVICE_REVISION is not defined"
 #endif
 #ifndef DEVICE_REV_A
  #error "DEVICE_REV_A is not defined"
 #endif
 #ifndef DEVICE_REV_B
  #error "DEVICE_REV_B is not defined"
 #endif

 #include "R7SA6W1CE.h"

 #if  (DEVICE_FAMILY != DA1640X)
  #error "Unknown device type -- check the value of dg_configDEVICE"
 #endif                                /* DEVICE_FAMILY */

/************************
 * Memory map
 ************************/

/**
 * \brief Remapped device base address.
 */
 #if (DEVICE_FAMILY == DA1640X)
  #define MEMORY_REMAPPED_BASE    0x00000000UL
  #define MEMORY_REMAPPED_END     0x08000000UL
 #endif                                /* DEVICE_FAMILY */

/**
 * \brief Remapped device memory size.
 */
 #define MEMORY_REMAPPED_SIZE     (MEMORY_REMAPPED_END - MEMORY_REMAPPED_BASE)

/**
 * \brief ROM base address.
 */
 #if (DEVICE_FAMILY == DA1640X)
  #define MEMORY_ROM_BASE         0xF020000UL
  #define MEMORY_ROM_END          (MEMORY_ROM_BASE + 0x40000UL)
 #endif                                /* DEVICE_FAMILY */

/**
 * \brief ROM memory size.
 */
 #define MEMORY_ROM_SIZE          (MEMORY_ROM_END - MEMORY_ROM_BASE)

/**
 * \brief OTP memory base address.
 */
 #if (DEVICE_FAMILY == DA1640X)
  #define MEMORY_OTP_BASE         0x400F2000UL
  #define MEMORY_OTP_END          0x400F2800UL
 #endif                                /* DEVICE_FAMILY */

/**
 * \brief OTP memory size.
 */
 #define MEMORY_OTP_SIZE          (MEMORY_OTP_END - MEMORY_OTP_BASE)

/**
 * \brief SYSTEM RAM base address.
 */
 #if (DEVICE_FAMILY == DA1640X)
  #define MEMORY_SYSRAM_BASE      0x20000000UL
  #define MEMORY_SYSRAM_END       (MEMORY_SYSRAM_BASE + 0xc0000UL)
 #endif                                /* DEVICE_FAMILY */

/**
 * \brief SYSTEM RAM size.
 */
 #define MEMORY_SYSRAM_SIZE       (MEMORY_SYSRAM_END - MEMORY_SYSRAM_BASE)

/**
 * \brief CACHE RAM base address.
 */
 #if (DEVICE_FAMILY == DA1640X)
  #define MEMORY_CACHERAM_BASE    0x18A00000UL
  #define MEMORY_CACHERAM_END     0x18A10000UL
 #endif                                /* DEVICE_FAMILY */

/**
 * \brief CACHE RAM size.
 */
 #define MEMORY_CACHERAM_SIZE     (MEMORY_CACHERAM_END - MEMORY_CACHERAM_BASE)

/**
 * \brief QSPI Flash base address.
 */
 #if (DEVICE_FAMILY == DA1640X)

/*
 * OQSPI AHB-C(ode) bus (cached). Accesses through this bus
 * are restricted according to CACHE_FLASH_REG.
 */
  #define MEMORY_OQSPIC_BASE              (0x0A000000) // before (0x19000000UL)
  #define MEMORY_OQSPIC_END               (0x0DFFFFFF) // before (0x1D000000UL)

  #define MEMORY_OQSPIC_SIZE              (MEMORY_OQSPIC_END - MEMORY_OQSPIC_BASE)

/*
 * OQSPI AHB-S(ystem) bus (Not cached). Accesses through this bus
 * are not affected by CACHE_FLASH_REG.
 */
  #define MEMORY_OQSPIC_S_BASE            (0x2A000000) // before (0x3A000000UL)
  #define MEMORY_OQSPIC_S_END             (0x2DFFFFFF) // before (0x3E000000UL)

/*
 * QSPI AHB-C(ode) bus (cached). Accesses through this bus
 * are restricted according to CACHE_FLASH_REG.
 */
  #define  MEMORY_QSPIF_BASE              (0x24000000UL)
  #define  MEMORY_QSPIF_END               (MEMORY_QSPIF_BASE + 0x4000000UL)

/*
 * QSPI Data
 */
  #define MEMORY_QSPID_BASE               (0x24000000UL)
  #define MEMORY_QSPID_END                (0x28000000UL)
  #define MEMORY_QSPID_SIZE               (MEMORY_QSPID_END - MEMORY_QSPID_BASE)

/*
 * DCACHE controller
 */
  #define MEMORY_DCACHE_BASE              (0x21014000UL)
  #define MEMORY_DCACHE_SIZE              (0x2000UL)
  #define MEMORY_DCACHE_END               (MEMORY_DCACHE_BASE + MEMORY_DCACHE_SIZE)

 #endif                                /* DEVICE_FAMILY */

/**
 * \brief QSPI Flash memory size.
 */
 #define MEMORY_QSPIF_SIZE                (MEMORY_QSPIF_END - MEMORY_QSPIF_BASE)

/**
 * \brief The Sector Size of the OQSPI and QSPI flash memories
 */
 #define FLASH_SECTOR_SIZE                (0x1000)

/**
 * \brief The base address for accessing the Flash memory connected to OQSPI
 *
 * The base address is used in oqspi_automode. Automode is using a single zero-based address region
 * for accessing the Flash devices connected to OQSPI and QSPI controllers (OQSPIC and QSPIC).
 * The defined address sub-regions are:
 *    Address region 1: starting at OQSPI_MEM1_VIRTUAL_BASE_ADDR
 * When Flash address is in region 1 then the device connected to OQSPIC is accessed.
 * The maximum region size handled by each QSPI controller in automode is 128MBytes.
 * The default value of each region size is 0x8000000, allowing 128MBytes region
 * for each controller.
 */
 #ifndef OQSPI_MEM1_VIRTUAL_BASE_ADDR
  #define OQSPI_MEM1_VIRTUAL_BASE_ADDR    (0x00000000)
 #endif

/**
 * \brief Address is in OQSPI_MEM1 virtual memory region
 */
 #define IS_OQSPI_MEM1_VIRTUAL_ADDRESS(_a)    WITHIN_RANGE((_a), OQSPI_MEM1_VIRTUAL_BASE_ADDR, \
                                                           (OQSPI_MEM1_VIRTUAL_BASE_ADDR + MEMORY_OQSPIC_SIZE))

/**
 * \brief The base address for accessing the Flash memory connected to QSPIC
 *
 * The base address is used in qspi_automode.
 */
 #ifndef QSPI_MEM1_VIRTUAL_BASE_ADDR
  #define QSPI_MEM1_VIRTUAL_BASE_ADDR    (OQSPI_MEM1_VIRTUAL_BASE_ADDR + MEMORY_OQSPIC_SIZE)
 #endif

/**
 * \brief OTP User Data Encryption Keys memory base address
 */
 #define WITHIN_RANGE(_a, _s, _e)    (((uint32_t) (_a) >= (uint32_t) (_s)) && ((uint32_t) (_a) < (uint32_t) (_e)))

/**
 * \brief Address is in the remapped memory region
 */
 #define IS_REMAPPED_ADDRESS(_a)     WITHIN_RANGE((_a), MEMORY_REMAPPED_BASE, MEMORY_REMAPPED_END)

/**
 * \brief Address is in the ROM region
 */
 #define IS_ROM_ADDRESS(_a)          WITHIN_RANGE((_a), MEMORY_ROM_BASE, MEMORY_ROM_END)

/**
 * \brief Address is in the SYSTEM RAM region
 */
 #define IS_SYSRAM_ADDRESS(_a)       WITHIN_RANGE((_a), MEMORY_SYSRAM_BASE, MEMORY_SYSRAM_END)

/**
 * \brief Address is in the CACHE RAM region
 */
 #define IS_CACHERAM_ADDRESS(_a)     WITHIN_RANGE((_a), MEMORY_CACHERAM_BASE, MEMORY_CACHERAM_END)

/**
 * \brief Address is in the QSPI Flash memory region
 */
 #define IS_QSPIF_ADDRESS(_a)        WITHIN_RANGE((_a), MEMORY_OQSPIC_BASE, MEMORY_OQSPIC_S_END)

 #if (DEVICE_FAMILY == DA1640X)

/**
 * \brief Address is in the QSPI AHB-S(ystem) memory region
 */
  #define IS_QSPIF_S_ADDRESS(_a)     WITHIN_RANGE((_a), MEMORY_QSPIF_BASE, MEMORY_QSPIF_END)
 #endif                                /* DEVICE_FAMILY */

 #if (DEVICE_FAMILY == DA1640X)

/**
 * \brief Address is in the OQSPI Flash memory region
 */
  #define IS_OQSPIC_ADDRESS(_a)      WITHIN_RANGE((_a), MEMORY_OQSPIC_BASE, MEMORY_OQSPIC_END)

/**
 * \brief Address is in the OQSPI AHB-S(ystem) memory region
 */
  #define IS_OQSPIC_S_ADDRESS(_a)    WITHIN_RANGE((_a), MEMORY_OQSPIC_S_BASE, MEMORY_OQSPIC_S_END)

 #endif                                /* DEVICE_FAMILY */

/**
 * \brief Zero-initialized data retained memory attribute
 */

// TIN_HACK_WIFI
 #define __RETAINED
 #define __RETAINED_1

/**
 * \brief Initialized data retained memory attribute
 */
 #define __RETAINED_RW            __attribute__((section("retention_mem_init")))

/**
 * \brief Uninitialized data retained memory attribute. Used for variables that should
 * not be initialized during startup.
 */
 #define __RETAINED_UNINIT        __attribute__((section("retention_mem_uninit")))

/**
 * \brief Constant data retained memory attribute
 */
 #define __RETAINED_CONST_INIT    __attribute__((section("retention_mem_const")))

/**
 * \brief Text retained memory attribute
 */
 #if ((dg_configCODE_LOCATION == NON_VOLATILE_IS_FLASH) && (dg_configEXEC_MODE == MODE_IS_CACHED))
  #define __RETAINED_CODE         __attribute__((section(".ram_code_from_flash"))) __attribute__((noinline)) \
    __attribute__((optimize("no-tree-switch-conversion")))
  #define __MTB_CODE              __attribute__((section("mtb_text_retained"))) __attribute__((noinline)) __attribute__((             \
                                                                                                                            optimize( \
                                                                                                                                "no-tree-switch-conversion")))
 #else
  #define __RETAINED_CODE
  #define __MTB_CODE              __attribute__((section("mtb_text_retained")))
 #endif

/**
 * \brief Attribute to silence warnings about unused parameters/variables/function
 */
 #define __UNUSED                 __attribute__((unused))

/**
 * \brief Attribute to tell the compiler to consider a symbol as externally visible (for LTO)
 */
 #define __LTO_EXT                __attribute__((externally_visible))

 #if dg_configUSE_HW_SYS

// Forward declaration
__RETAINED_CODE void hw_sys_assert_trigger_gpio(void);

 #else
  #define hw_sys_assert_trigger_gpio()
 #endif

/**
 * \brief Assert as warning macro
 *
 * \note Active only while in development mode
 */
 #if (DEVICE_FAMILY == DA1640X)
  #define ASSERT_WARNING(a)                                                 \
    {                                                                       \
        if (!(a)) {                                                         \
            if (dg_configIMAGE_SETUP == DEVELOPMENT_MODE) {                 \
                printf(" >> ASSERT_WARNING %s:%d \n", __func__, __LINE__);} \
        }                                                                   \
    }

/**
 * \brief Assert as error macro
 *
 */
  #define ASSERT_ERROR(a)                                                \
    {                                                                    \
        if (dg_configIMAGE_SETUP == DEVELOPMENT_MODE) {                  \
            if (!(a)) {                                                  \
                printf(" >> ASSERT_ERROR %s:%d \n", __func__, __LINE__); \
            }                                                            \
        }                                                                \
        else {                                                           \
            if (!(a)) {                                                  \
                __ASM volatile ("cpsid i" : : : "memory");               \
                __BKPT(2);                                               \
            }                                                            \
        }                                                                \
    }

/**
 * \brief Assert as warning macro when the system is still uninitialized
 *
 * \note Active only while in development mode. The SW cursor is not activated.
 */
  #define ASSERT_WARNING_UNINIT(a)                                                 \
    {                                                                              \
        if (!(a)) {                                                                \
            if (dg_configIMAGE_SETUP == DEVELOPMENT_MODE) {                        \
                printf(" >> ASSERT_WARNING_UNINIT %s:%d \n", __func__, __LINE__);} \
        }                                                                          \
    }

/**
 * \brief Assert as error macro when the system is still uninitialized
 *
 * \note The SW cursor is not activated.
 */
  #define ASSERT_ERROR_UNINIT(a)                                                \
    {                                                                           \
        if (dg_configIMAGE_SETUP == DEVELOPMENT_MODE) {                         \
            if (!(a)) {                                                         \
                printf(" >> ASSERT_ERROR_UNINIT %s:%d \n", __func__, __LINE__); \
            }                                                                   \
        }                                                                       \
        else {                                                                  \
            if (!(a)) {                                                         \
                __disable_irq();                                                \
                __BKPT(2);                                                      \
            }                                                                   \
        }                                                                       \
    }
 #endif                                /* DEVICE_FAMILY */

/**
 * \brief Macro to disable all interrupts
 *
 * This macro must always be used with GLOBAL_INT_RESTORE(). E.g.
 *
 * \code{.c}
 * GLOBAL_INT_DISABLE();
 *  ... code to be executed with interrupts disabled ...
 * GLOBAL_INT_RESTORE();
 * \endcode
 *
 * \sa GLOBAL_INT_RESTORE
 */
 #define GLOBAL_INT_DISABLE()                     \
    do {                                          \
        unsigned int __l_irq_rest;                \
        __ASM volatile ("mrs   %0, primask  \n\t" \
                        "mov   r1, $1     \n\t"   \
                        "msr   primask, r1  \n\t" \
                        : "=r" (__l_irq_rest)     \
                        :                         \
                        : "r1"                    \
                        );                        \
        /*DBG_CONFIGURE_HIGH(CMN_TIMING_DEBUG, CMNDBG_CRITICAL_SECTION);*/

/**
 * \brief Macro to restore all interrupts
 *
 * This macro must always be used after GLOBAL_INT_DISABLE(). E.g.
 *
 * \code{.c}
 * GLOBAL_INT_DISABLE();
 *  ... code to be executed with interrupts disabled ...
 * GLOBAL_INT_RESTORE();
 * \endcode
 *
 * \sa GLOBAL_INT_DISABLE
 */
 #define GLOBAL_INT_RESTORE()                                             \
    if (__l_irq_rest == 0) {                                              \
        /*DBG_CONFIGURE_LOW(CMN_TIMING_DEBUG, CMNDBG_CRITICAL_SECTION);*/ \
    }                                                                     \
    __ASM volatile ("msr   primask, %0  \n\t"                             \
                    :                                                     \
                    : "r" (__l_irq_rest)                                  \
                    :                                                     \
                    );                                                    \
}                                                                         \
    while (0)

 #define containingoffset(address, type, field)    ((type *) ((uint8 *) (address) - (size_t) (&((type *) 0)->field)))

/**
 * \brief Macro the minimum of two values
 *
 * \param[in] a         First value
 * \param[in] b         Second value
 */
 #ifndef MIN
  #define MIN(a, b)                                (((a) < (b)) ? (a) : (b))
 #endif

/**
 * \brief Macro the maximum of two values
 *
 * \param[in] a         First value
 * \param[in] b         Second value
 */
 #define MAX(a, b)                                 (((a) > (b)) ? (a) : (b))

/**
 * \brief Macro to swap the bytes of a 16-bit variable
 *
 * \param[in] a         The 16-bit variable
 */
 #if defined(__GNUC__)
  #define SWAP16(a)                                __builtin_bswap16(a)
 #else
  #define SWAP16(a)                                ((a << 8) | (a >> 8))
 #endif

/**
 * \brief Macro to swap the bytes of a 32-bit variable
 *
 * \param[in] a         The 32-bit variable
 */
 #if defined(__GNUC__)
  #define SWAP32(a)                                __builtin_bswap32(a)
 #else
  #define SWAP32(a)                                ((a >> 24 & 0xff) | (a >> 8 & 0xff00) | (a << 8 & 0xff0000) | \
                                                    (a << 24 & 0xff000000))
 #endif

 #if defined(__GNUC__)
  #define DEPRECATED    __attribute__((deprecated))
 #else
  #pragma message "Deprecated macro must be implemented for this compiler"
  #define DEPRECATED
 #endif

 #if defined(__GNUC__)
  #define DEPRECATED_MSG(msg)    __attribute__((deprecated(msg)))
 #else
  #pragma message "Deprecated macro must be implemented for this compiler"
  #define DEPRECATED_MSG(msg)
 #endif

/* The following exist in ROM code */
void __aeabi_memcpy(void * dest, const void * src, size_t n);
void __aeabi_memmove(void * dest, const void * src, size_t n);
void __aeabi_memset(void * dest, size_t n, int c);

/**
 * \brief Optimized memcpy
 */
 #define OPT_MEMCPY     __aeabi_memcpy

/**
 * \brief Optimized memmove
 */
 #define OPT_MEMMOVE    __aeabi_memmove

/**
 * \brief Optimized memset
 */
 #define OPT_MEMSET(s, c, n)    __aeabi_memset(s, n, c)

/**
 * \brief Access register field mask.
 *
 * Returns a register field mask (aimed to be used with local variables).
 * e.g.
 * \code
 * uint16_t tmp;
 *
 * tmp = CRG_TOP->SYS_STAT_REG;
 *
 * if (tmp & REG_MSK(CRG_TOP, SYS_STAT_REG, XTAL16_TRIM_READY)) {
 * ...
 * \endcode
 */
 #define REG_MSK(base, reg, field) \
    (base ## _ ## reg ## _ ## field ## _Msk)

/**
 * \brief Access register field position.
 *
 * Returns a register field position (aimed to be used with local variables).
 */
 #define REG_POS(base, reg, field) \
    (base ## _ ## reg ## _ ## field ## _Pos)

/**
 * \brief Access register field value.
 *
 * Returns a register field value (aimed to be used with local variables).
 * e.g.
 * \code
 * uint16_t tmp;
 * int counter;
 * tmp = CRG_TOP->TRIM_CTRL_REG;
 * counter = REG_GET_FIELD(CRG_TOP, TRIM_CTRL_REG, XTAL_COUNT_N, tmp);
 * ...
 * \endcode
 */
 #define REG_GET_FIELD(base, reg, field, var)            \
    ((var & (base ## _ ## reg ## _ ## field ## _Msk)) >> \
     (base ## _ ## reg ## _ ## field ## _Pos))

/**
 * \brief Set register field value.
 *
 * Sets a register field value (aimed to be used with local variables).
 * e.g.
 * \code
 * uint16_t tmp;
 *
 * tmp = CRG_TOP->TRIM_CTRL_REG;
 * REG_SET_FIELD(CRG_TOP, TRIM_CTRL_REG, XTAL_COUNT_N, tmp, 10);
 * REG_SET_FIELD(CRG_TOP, TRIM_CTRL_REG, XTAL_TRIM_SELECT, tmp, 2);
 * CRG_TOP->TRIM_CTRL_REG = tmp;
 * ...
 * \endcode
 */
 #define REG_SET_FIELD(base, reg, field, var, val)                \
    var = ((var & ~((base ## _ ## reg ## _ ## field ## _Msk))) |  \
           (((val) << (base ## _ ## reg ## _ ## field ## _Pos)) & \
            (base ## _ ## reg ## _ ## field ## _Msk)))

/**
 * \brief Set memory field value.
 *
 * Sets a memory field value using a mask (aimed to be used with local variables).
 * e.g.
 * \code
 * uint32_t tmp = *(volatile uint32_t *)0x50000000;
 *
 * RAW_SET_FIELD(tmp, 0x1UL, 1);
 * ...
 * \endcode
 */
 #define RAW_SET_FIELD(mem, mask, val) \
    mem = ((mem & ~((mask))) | (((val) << (__builtin_ctz(mask))) & (mask)))

/**
 * \brief Clear register field value.
 *
 * Clears a register field value (aimed to be used with local variables).
 * e.g.
 * \code
 * uint16_t tmp;
 *
 * tmp = CRG_TOP->TRIM_CTRL_REG;
 * REG_CLR_FIELD(CRG_TOP, TRIM_CTRL_REG, XTAL_COUNT_N, tmp);
 * REG_CLR_FIELD(CRG_TOP, TRIM_CTRL_REG, XTAL_TRIM_SELECT, tmp);
 * CRG_TOP->TRIM_CTRL_REG = tmp;
 * ...
 * \endcode
 */
 #define REG_CLR_FIELD(base, reg, field, var) \
    var &= ~(base ## _ ## reg ## _ ## field ## _Msk)

/**
 * \brief Get the address of a register value by index (provided a register interval)
 *
 * \note The register interval should be an exact multiple of the register's base size. For example,
 * if the register size is 32-bit, then the interval should be 0x4, 0x8, etc. Otherwise, the result
 * will be undefined. The interval value must be in bytes. The index value (0,1,2...) is multiplied by
 * the interval value (in bytes) to find the actual offset of the register.
 *
 * Returns a register address value by index
 */
 #define REG_GET_ADDR_INDEXED(base, reg, interval, index) \
    ((&base->reg) + (((intptr_t) index) * ((interval) / sizeof(base->reg))))

/**
 * \brief Return the value of a register field by index (provided a register interval).
 *
 * e.g.
 * \code
 * uint16_t val;
 * uint16_t index = 2
 *
 * val = REG_GETF_INDEXED(FTDF, FTDF_LONG_ADDR_0_0_REG, REG_EXP_SA_L, 0x10, index)
 *
 * ...
 * \endcode
 *
 * \note The register interval should be an exact multiple of the register's base size. For example,
 * if the register size is 32-bit, then the interval should be 0x4, 0x8, etc. Otherwise, the result
 * will be undefined. The interval value must be in bytes. The index value (0,1,2...) is multiplied by
 * the interval value (in bytes) to find the actual offset of the register.
 *
 */
 #define REG_GETF_INDEXED(base, reg, field, interval, index) \
    (((*REG_GET_ADDR_INDEXED(base, reg, interval, index)) &  \
      (base ## _ ## reg ## _ ## field ## _Msk)) >> (base ## _ ## reg ## _ ## field ## _Pos))

/**
 * \brief Return the value of a register field.
 *
 * e.g.
 * \code
 * uint32_t val;
 *
 * val = REG_GETF(CRG_TOP, TRIM_CTRL_REG, XTAL_COUNT_N);
 * ...
 * \endcode
 */
 #define REG_GETF(base, reg, field) \
    (((base->reg) & (base ## _ ## reg ## _ ## field ## _Msk)) >> (base ## _ ## reg ## _ ## field ## _Pos))

/**
 * \brief Return the value of a memory field using a mask.
 *
 * e.g.
 * \code
 * uint32_t val;
 *
 * val = RAW_GETF(0x50000000, 0x1UL);
 * ...
 * \endcode
 */
 #define RAW_GETF(addr, mask) \
    ((*(volatile uint32_t *) (addr) & (mask)) >> (__builtin_ctz(mask)))

/**
 * \brief Set the value of a register field.
 *
 * e.g.
 * \code
 *
 * REG_SETF(CRG_TOP, TRIM_CTRL_REG, XTAL_COUNT_N, new_value);
 * ...
 * \endcode
 */
 #define REG_SETF(base, reg, field, new_val)                               \
    base->reg = ((base->reg & ~(base ## _ ## reg ## _ ## field ## _Msk)) | \
                 ((base ## _ ## reg ## _ ## field ## _Msk) &((new_val) << (base ## _ ## reg ## _ ## field ## _Pos))))

/**
 * \brief Set the value of a memory field.
 *
 * e.g.
 * \code
 *
 * RAW_SETF(0x50000000, 0x1UL, 1);
 * ...
 * \endcode
 */
 #define RAW_SETF(addr, mask, val)                                                 \
    (*(volatile uint32_t *) (addr)) = ((*(volatile uint32_t *) (addr) & ~(mask)) | \
                                       ((mask) & ((val) << __builtin_ctz(mask))))

/**
 * \brief Set a bit of a register.
 *
 * e.g.
 * \code
 *
 * REG_SET_BIT(CRG_TOP, CLK_TMR_REG, TMR1_ENABLE);
 * ...
 * \endcode
 */
 #define REG_SET_BIT(base, reg, field)                                \
    do {                                                              \
        base->reg |= (1 << (base ## _ ## reg ## _ ## field ## _Pos)); \
    } while (0)

/**
 * \brief Clear a bit of a register.
 *
 * e.g.
 * \code
 *
 * REG_CLR_BIT(CRG_TOP, CLK_TMR_REG, TMR1_ENABLE);
 * ...
 * \endcode
 */
 #define REG_CLR_BIT(base, reg, field)                          \
    do {                                                        \
        base->reg &= ~(base ## _ ## reg ## _ ## field ## _Msk); \
    } while (0)

/**
 * \brief Sets register bits, indicated by the mask, to a value.
 *
 * e.g.
 * \code
 * REG_SET_MASKED(RFCU_POWER, RF_CNTRL_TIMER_5_REG, 0xFF00, 0x1818);
 * \endcode
 */
 #define REG_SET_MASKED(base, reg, mask, value)                 \
    do {                                                        \
        base->reg = (base->reg & ~(mask)) | ((value) & (mask)); \
    } while (0)

/**
 * \brief Sets memory bits, indicated by the mask, to a value.
 *
 * e.g.
 * \code
 * RAW_SET_MASKED(0x50000000, 0xFF00, 0x1818);
 * \endcode
 */
 #define RAW_SET_MASKED(addr, mask, value)                                                                  \
    do {                                                                                                    \
        (*(volatile uint32_t *) (addr)) = ((*(volatile uint32_t *) (addr)) & ~(mask)) | ((value) & (mask)); \
    } while (0)

/**
 * \brief Sets 16-bit wide register bits, indicated by the field, to a value v.
 */
 #define BITS16(base, reg, field, v)                                        \
    ((uint16) (((uint16) (v) << (base ## _ ## reg ## _ ## field ## _Pos)) & \
               (base ## _ ## reg ## _ ## field ## _Msk)))

/**
 * \brief Sets 32-bit wide register bits, indicated by the field, to a value v.
 */
 #define BITS32(base, reg, field, v)                                        \
    ((uint32) (((uint32) (v) << (base ## _ ## reg ## _ ## field ## _Pos)) & \
               (base ## _ ## reg ## _ ## field ## _Msk)))

/**
 * \brief Reads 16-bit wide register bits, indicated by the field, to a variable v.
 */
 #define GETBITS16(base, reg, v, field)                                      \
    ((uint16) (((uint16) (v)) & (base ## _ ## reg ## _ ## field ## _Msk)) >> \
     (base ## _ ## reg ## _ ## field ## _Pos))

/**
 * \brief Reads 32-bit wide register bits, indicated by the field, to a variable v.
 */
 #define GETBITS32(base, reg, v, field)                                      \
    ((uint32) (((uint32) (v)) & (base ## _ ## reg ## _ ## field ## _Msk)) >> \
     (base ## _ ## reg ## _ ## field ## _Pos))

/**
 * \brief Macro to enable the debugger
 *
 */
 #define ENABLE_DEBUGGER                                     \
    do {                                                     \
        REG_SET_BIT(CRG_TOP, SYS_CTRL_REG, DEBUGGER_ENABLE); \
    } while (0)

/**
 * \brief Macro to disable the debugger
 *
 */
 #define DISABLE_DEBUGGER                                    \
    do {                                                     \
        REG_CLR_BIT(CRG_TOP, SYS_CTRL_REG, DEBUGGER_ENABLE); \
    } while (0)

extern void pll_off(void);

/**
 * \brief Macro to cause a software reset
 *
 */
 #define SWRESET                                       \
    do {                                               \
        REG_SETF(CRG_TOP, PMU_CTRL_REG, PHY_SLEEP, 1); \
        REG_SETF(CRG_TOP, PMU_CTRL_REG, MAC_SLEEP, 1); \
        pll_off();                                     \
        REG_SET_BIT(CRG_TOP, SYS_CTRL_REG, SW_RESET);  \
    } while (0)

/**
 * \brief Macro to cause a POR reset. it reset the DCORE
 *
 */
 #define PORRESET                                           \
    do {                                                    \
        if (bsp_is_chip_revision_a())                       \
        {                                                   \
            RTC->LDO_ENABLE_REG_b.LDO_EN_BOOST_PWR_OFF = 1; \
        }                                                   \
        RTC->DCDC_CNTL_OFF_REG = 0;                         \
        RTC->DCDC_CNTL_OFF_REG = 0x03;                      \
    } while (0)

 #define BIT0     0x00000001
 #define BIT1     0x00000002
 #define BIT2     0x00000004
 #define BIT3     0x00000008
 #define BIT4     0x00000010
 #define BIT5     0x00000020
 #define BIT6     0x00000040
 #define BIT7     0x00000080

 #define BIT8     0x00000100
 #define BIT9     0x00000200
 #define BIT10    0x00000400
 #define BIT11    0x00000800
 #define BIT12    0x00001000
 #define BIT13    0x00002000
 #define BIT14    0x00004000
 #define BIT15    0x00008000

 #define BIT16    0x00010000
 #define BIT17    0x00020000
 #define BIT18    0x00040000
 #define BIT19    0x00080000
 #define BIT20    0x00100000
 #define BIT21    0x00200000
 #define BIT22    0x00400000
 #define BIT23    0x00800000

 #define BIT24    0x01000000
 #define BIT25    0x02000000
 #define BIT26    0x04000000
 #define BIT27    0x08000000
 #define BIT28    0x10000000
 #define BIT29    0x20000000
 #define BIT30    0x40000000
 #define BIT31    0x80000000

typedef unsigned char      uint8;      // 8 bits
typedef char               int8;       // 8 bits
typedef unsigned short     uint16;     // 16 bits
typedef short              int16;      // 16 bits
typedef unsigned long      uint32;     // 32 bits
typedef long               int32;      // 32 bits
typedef unsigned long long uint64;     // 64 bits
typedef long long          int64;      // 64 bits

/* See also "Data Types" on pag. 21 of the (Doulos) Cortex-M0 / SoC 1.0 training documentation. */
typedef unsigned char  BYTE;           // 8 bits = Byte
typedef unsigned short HWORD;          // 16 bits = Halfword
typedef unsigned long  WORD;           // 32 bits = Word
typedef long long      DWORD;          // 64 bits = Doubleword

////////////////////////////////////////////////////////////////////

typedef signed char    CHAR;
typedef unsigned char  UCHAR;
typedef signed short   SHORT;
typedef unsigned short USHORT;
typedef signed int     INT;
typedef unsigned int   UINT;
typedef signed long    LONG;
typedef unsigned long  ULONG;

typedef void VOID;

typedef char               INT8;
typedef unsigned char      UINT8;
typedef short              INT16;
typedef unsigned short     UINT16;
typedef int                INT32;
typedef unsigned int       UINT32;
typedef long long          INT64;
typedef unsigned long long UINT64;

typedef void * HANDLE;

typedef unsigned int  OPTION;
typedef unsigned long UNSIGNED;
typedef long          SIGNED;

typedef unsigned long long u64;
typedef unsigned int       u32;
typedef unsigned short     u16;
typedef unsigned char      u8;

typedef signed char s8;
typedef signed int  s32;

/******************************************************************************
 *
 *  Macro
 *
 ******************************************************************************/

 #ifndef NX_PORT_H
  #define TRUE     (1)
  #define FALSE    (0)
 #else
  #define TRUE     pdTRUE
  #define FALSE    pdFALSE
 #endif

 #define MBYTE     (1024UL * 1024UL)
 #define KBYTE     (1024UL)

 #define MHz       (1000UL * 1000UL)
 #define KHz       (1000UL)

 #ifndef RA6W1_UNUSED_ARG
  #define RA6W1_UNUSED_ARG(x)    (void) x
 #endif                                // RA6W1_UNUSED_ARG

/******************************************************************************
 *
 *  Callback
 *
 ******************************************************************************/

typedef     VOID (* USR_CALLBACK)(VOID *);

////////////////////////////////////////////////////////////////////

 #if dg_configAUTOTEST_ENABLE
  #define autotest_printf(fmt, arg ...)    printf(fmt, ## arg);
 #endif

 #ifdef __cplusplus
}
 #endif

#endif                                 /* __SDK_DEFS_H__ */

/**
 * \}
 * \}
 */
