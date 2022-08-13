/***********************************************************************************************//**
 * \file cy_utils.h
 *
 * \brief
 * Basic utility macros and functions.
 *
 ***************************************************************************************************
 * \copyright
 * Copyright 2018-2021 Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation
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
 **************************************************************************************************/

/**
 * \addtogroup group_utils Utilities
 * \ingroup group_abstraction
 * \{
 * Basic utility macros and functions.
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

/** Simple macro to suppress the unused parameter warning by casting to void. */
#define CY_UNUSED_PARAMETER(x) ( (void)(x) )

/** Halt the processor in the debug state
 */
static inline void CY_HALT(void)
{
    __asm("    bkpt    1");
}


#ifdef CY_ASSERT
#undef CY_ASSERT
#endif // ifdef(CY_ASSERT)

/** Utility macro when neither NDEBUG or CY_NO_ASSERT is not declared to check a condition and, if
   false, trigger a breakpoint */
#if defined(NDEBUG) || defined(CY_NO_ASSERT)
    #define CY_ASSERT(x)    do {                \
                            } while(false)
#else
    #define CY_ASSERT(x)    do {                \
                                if(!(x))        \
                                {               \
                                    CY_HALT();  \
                                }               \
                            } while(false)
#endif // defined(NDEBUG)


/*******************************************************************************
*  Data manipulation defines
*******************************************************************************/

/** Get the lower 8 bits of a 16-bit value. */
#define CY_LO8(x)               ((uint8_t) ((x) & 0xFFU))
/** Get the upper 8 bits of a 16-bit value. */
#define CY_HI8(x)               ((uint8_t) ((uint16_t)(x) >> 8U))

/** Get the lower 16 bits of a 32-bit value. */
#define CY_LO16(x)              ((uint16_t) ((x) & 0xFFFFU))
/** Get the upper 16 bits of a 32-bit value. */
#define CY_HI16(x)              ((uint16_t) ((uint32_t)(x) >> 16U))

/** Swap the byte ordering of a 16-bit value */
#define CY_SWAP_ENDIAN16(x)     ((uint16_t)(((x) << 8U) | (((x) >> 8U) & 0x00FFU)))

/** Swap the byte ordering of a 32-bit value */
#define CY_SWAP_ENDIAN32(x)     \
    ((uint32_t)((((x) >> 24U) & 0x000000FFU) | (((x) & 0x00FF0000U) >> 8U) | \
                (((x) & 0x0000FF00U) << 8U) | ((x) << 24U)))

/** Swap the byte ordering of a 64-bit value */
#define CY_SWAP_ENDIAN64(x)     ((uint64_t) (((uint64_t) CY_SWAP_ENDIAN32((uint32_t)(x)) << 32U) | \
                                CY_SWAP_ENDIAN32((uint32_t)((x) >> 32U))))


/*******************************************************************************
*   Memory model definitions
*******************************************************************************/
#if defined(__ARMCC_VERSION)
/** To create cross compiler compatible code, use the CY_NOINIT, CY_SECTION, CY_UNUSED, CY_ALIGN
 * attributes at the first place of declaration/definition.
 * For example: CY_NOINIT uint32_t noinitVar;
 */
    #if (__ARMCC_VERSION >= 6010050)
        #define CY_NOINIT           __attribute__ ((section(".noinit")))
    #else
        #define CY_NOINIT           __attribute__ ((section(".noinit"), zero_init))
    #endif // (__ARMCC_VERSION >= 6010050)
    #define CY_SECTION(name)    __attribute__ ((section(name)))
    #define CY_UNUSED           __attribute__ ((unused))
    #define CY_NOINLINE         __attribute__ ((noinline))
// Specifies the minimum alignment (in bytes) for variables of the specified type.
    #define CY_ALIGN(align)     __ALIGNED(align)
    #define CY_RAMFUNC_BEGIN    __attribute__ ((section(".cy_ramfunc")))
    #define CY_RAMFUNC_END
#elif defined (__GNUC__)
    #if defined (__clang__)
        #define CY_NOINIT           __attribute__ ((section("__DATA, __noinit")))
        #define CY_SECTION(name)    __attribute__ ((section("__DATA, "name)))
        #define CY_RAMFUNC_BEGIN    __attribute__ ((section("__DATA, .cy_ramfunc")))
        #define CY_RAMFUNC_END
    #else
        #define CY_NOINIT           __attribute__ ((section(".noinit")))
        #define CY_SECTION(name)    __attribute__ ((section(name)))
        #define CY_RAMFUNC_BEGIN    __attribute__ ((section(".cy_ramfunc")))
        #define CY_RAMFUNC_END
    #endif

    #define CY_UNUSED           __attribute__ ((unused))
    #define CY_NOINLINE         __attribute__ ((noinline))
    #define CY_ALIGN(align)     __ALIGNED(align)
#elif defined (__ICCARM__)
    #define CY_PRAGMA(x)        _Pragma(#x)
    #define CY_NOINIT           __no_init
    #define CY_SECTION(name)    CY_PRAGMA(location = name)
    #define CY_UNUSED
    #define CY_NOINLINE         CY_PRAGMA(optimize = no_inline)
    #define CY_RAMFUNC_BEGIN    CY_PRAGMA(diag_suppress = Ta023) __ramfunc
    #define CY_RAMFUNC_END      CY_PRAGMA(diag_default = Ta023)
    #if (__VER__ < 8010001)
        #define CY_ALIGN(align) CY_PRAGMA(data_alignment = align)
    #else
        #define CY_ALIGN(align) __ALIGNED(align)
    #endif // (__VER__ < 8010001)
#else // if defined(__ARMCC_VERSION)
    #error "An unsupported toolchain"
#endif // (__ARMCC_VERSION)


/***************************************************************************************************
 * Macro Name: CY_GET_REG8(addr)
 ***********************************************************************************************//**
 *
 * Reads the 8-bit value from the specified address. This function can't be
 * used to access the Core register, otherwise a fault occurs.
 *
 * \param addr  The register address.
 *
 * \return The read value.
 *
 **************************************************************************************************/
#define CY_GET_REG8(addr)           (*((const volatile uint8_t *)(addr)))


/***************************************************************************************************
 * Macro Name: CY_SET_REG8(addr, value)
 ***********************************************************************************************//**
 *
 * Writes an 8-bit value to the specified address. This function can't be
 * used to access the Core register, otherwise a fault occurs.
 *
 * \param addr  The register address.
 *
 * \param value The value to write.
 *
 **************************************************************************************************/
#define CY_SET_REG8(addr, value)    (*((volatile uint8_t *)(addr)) = (uint8_t)(value))


/***************************************************************************************************
 * Macro Name: CY_GET_REG16(addr)
 ***********************************************************************************************//**
 *
 * Reads the 16-bit value from the specified address.
 *
 * \param addr  The register address.
 *
 * \return The read value.
 *
 **************************************************************************************************/
#define CY_GET_REG16(addr)          (*((const volatile uint16_t *)(addr)))


/***************************************************************************************************
 * Macro Name: CY_SET_REG16(addr, value)
 ***********************************************************************************************//**
 *
 * Writes the 16-bit value to the specified address.
 *
 * \param addr  The register address.
 *
 * \param value The value to write.
 *
 **************************************************************************************************/
#define CY_SET_REG16(addr, value)   (*((volatile uint16_t *)(addr)) = (uint16_t)(value))


/***************************************************************************************************
 * Macro Name: CY_GET_REG24(addr)
 ***********************************************************************************************//**
 *
 * Reads the 24-bit value from the specified address.
 *
 * \param addr  The register address.
 *
 * \return The read value.
 *
 **************************************************************************************************/
#define CY_GET_REG24(addr)  (((uint32_t) (*((const volatile uint8_t *)(addr)))) | \
                            (((uint32_t) (*((const volatile uint8_t *)(addr) + 1))) << 8U) | \
                            (((uint32_t) (*((const volatile uint8_t *)(addr) + 2))) << 16U))


/***************************************************************************************************
 * Macro Name: CY_SET_REG24(addr, value)
 ***********************************************************************************************//**
 *
 * Writes the 24-bit value to the specified address.
 *
 * \param addr  The register address.
 *
 * \param value The value to write.
 *
 **************************************************************************************************/
#define CY_SET_REG24(addr, value) \
    do  \
    {   \
        (*((volatile uint8_t *) (addr))) = (uint8_t)(value);                \
        (*((volatile uint8_t *) (addr) + 1)) = (uint8_t)((value) >> 8U);    \
        (*((volatile uint8_t *) (addr) + 2)) = (uint8_t)((value) >> 16U);   \
    }   \
    while(0)


/***************************************************************************************************
 * Macro Name: CY_GET_REG32(addr)
 ***********************************************************************************************//**
 *
 * Reads the 32-bit value from the specified register. The address is the little
 * endian order (LSB in lowest address).
 *
 * \param addr  The register address.
 *
 * \return The read value.
 *
 **************************************************************************************************/
#define CY_GET_REG32(addr)          (*((const volatile uint32_t *)(addr)))


/***************************************************************************************************
 * Macro Name: CY_SET_REG32(addr, value)
 ***********************************************************************************************//**
 *
 * Writes the 32-bit value to the specified register. The address is the little
 * endian order (LSB in lowest address).
 *
 * \param addr  The register address.
 *
 * \param value The value to write.
 *
 **************************************************************************************************/
#define CY_SET_REG32(addr, value)   (*((volatile uint32_t *)(addr)) = (uint32_t)(value))


/***************************************************************************************************
 * Macro Name: _CLR_SET_FLD32U
 ***********************************************************************************************//**
 *
 *  The macro for setting a register with a name field and value for providing
 *  get-clear-modify-write operations.
 *  Returns a resulting value to be assigned to the register.
 *
 **************************************************************************************************/
#define _CLR_SET_FLD32U(reg, field, value) \
    (((reg) & ((uint32_t)(~(field ## _Msk)))) | (_VAL2FLD(field, value)))


/***************************************************************************************************
 * Macro Name: CY_REG32_CLR_SET
 ***********************************************************************************************//**
 *
 *  Uses _CLR_SET_FLD32U macro for providing get-clear-modify-write
 *  operations with a name field and value and writes a resulting value
 *  to the 32-bit register.
 *
 **************************************************************************************************/
#define CY_REG32_CLR_SET(reg, field, value) ((reg) = _CLR_SET_FLD32U((reg), field, (value)))


/***************************************************************************************************
 * Macro Name: _CLR_SET_FLD16U
 ***********************************************************************************************//**
 *
 *  The macro for setting a 16-bit register with a name field and value for providing
 *  get-clear-modify-write operations.
 *  Returns a resulting value to be assigned to the 16-bit register.
 *
 **************************************************************************************************/
#define _CLR_SET_FLD16U(reg, field, value) \
    ((uint16_t)(((reg) & ((uint16_t)(~(field ## _Msk)))) | ((uint16_t)_VAL2FLD(field, value))))


/***************************************************************************************************
 * Macro Name: CY_REG16_CLR_SET
 ***********************************************************************************************//**
 *
 *  Uses _CLR_SET_FLD16U macro for providing get-clear-modify-write
 *  operations with a name field and value and writes a resulting value
 *  to the 16-bit register.
 *
 **************************************************************************************************/
#define CY_REG16_CLR_SET(reg, field, value) ((reg) = _CLR_SET_FLD16U((reg), field, (value)))


/***************************************************************************************************
 * Macro Name: _CLR_SET_FLD8U
 ***********************************************************************************************//**
 *
 *  The macro for setting a 8-bit register with a name field and value for providing
 *  get-clear-modify-write operations.
 *  Returns a resulting value to be assigned to the 8-bit register.
 *
 **************************************************************************************************/
#define _CLR_SET_FLD8U(reg, field, value) \
    ((uint8_t)(((reg) & ((uint8_t)(~(field ## _Msk)))) | ((uint8_t)_VAL2FLD(field, value))))


/***************************************************************************************************
 * Macro Name: CY_REG8_CLR_SET
 ***********************************************************************************************//**
 *
 *  Uses _CLR_SET_FLD8U macro for providing get-clear-modify-write
 *  operations with a name field and value and writes a resulting value
 *  to the 8-bit register.
 *
 **************************************************************************************************/
#define CY_REG8_CLR_SET(reg, field, value) ((reg) = _CLR_SET_FLD8U((reg), field, (value)))


/***************************************************************************************************
 * Macro Name: _BOOL2FLD
 ***********************************************************************************************//**
 *
 *  Returns a field mask if the value is not false.
 *  Returns 0, if the value is false.
 *
 **************************************************************************************************/
#define _BOOL2FLD(field, value) (((value) != false) ? (field ## _Msk) : 0UL)


/***************************************************************************************************
 * Macro Name: _FLD2BOOL
 ***********************************************************************************************//**
 *
 *  Returns true, if the value includes the field mask.
 *  Returns false, if the value doesn't include the field mask.
 *
 **************************************************************************************************/
#define _FLD2BOOL(field, value) (((value) & (field ## _Msk)) != 0UL)


/***************************************************************************************************
 * Macro Name: CY_SYSLIB_DIV_ROUND
 ***********************************************************************************************//**
 *
 *  Calculates a / b with rounding to the nearest integer,
 *  a and b must have the same sign.
 *
 **************************************************************************************************/
#define CY_SYSLIB_DIV_ROUND(a, b) (((a) + ((b) / 2U)) / (b))


/***************************************************************************************************
 * Macro Name: CY_SYSLIB_DIV_ROUNDUP
 ***********************************************************************************************//**
 *
 *  Calculates a / b with rounding up if remainder != 0,
 *  both a and b must be positive.
 *
 **************************************************************************************************/
#define CY_SYSLIB_DIV_ROUNDUP(a, b) ((((a) - 1U) / (b)) + 1U)

/*******************************************************************************
*  Provides the macros for MISRA violation documentation in Coverity tool.
*******************************************************************************/

/** \cond INTERNAL */

#ifdef CY_COVERITY_2012_CHECK // Check MISRA-C:2012 with Coverity tool
#define CY_COVERITY_PRAGMA_STR(a) #a

#define CY_MISRA_DEVIATE_LINE(MISRA, MESSAGE) \
_Pragma(CY_COVERITY_PRAGMA_STR(coverity compliance deviate MISRA MESSAGE))

#define CY_MISRA_FP_LINE(MISRA, MESSAGE) \
_Pragma(CY_COVERITY_PRAGMA_STR(coverity compliance fp MISRA MESSAGE))

#define CY_MISRA_DEVIATE_BLOCK_START(MISRA, COUNT, MESSAGE) \
_Pragma(CY_COVERITY_PRAGMA_STR(coverity compliance block (deviate:COUNT MISRA MESSAGE)))

#define CY_MISRA_FP_BLOCK_START(MISRA, COUNT, MESSAGE) \
_Pragma(CY_COVERITY_PRAGMA_STR(coverity compliance block (fp:COUNT MISRA MESSAGE)))

#define CY_MISRA_BLOCK_END(MISRA) \
_Pragma(CY_COVERITY_PRAGMA_STR(coverity compliance end_block MISRA))

#else // General usage

#define CY_MISRA_DEVIATE_LINE(MISRA, MESSAGE) do{}while(false)
#define CY_MISRA_FP_LINE(MISRA, MESSAGE) do{}while(false)
#define CY_MISRA_DEVIATE_BLOCK_START(MISRA, COUNT, MESSAGE)
#define CY_MISRA_FP_BLOCK_START(MISRA, COUNT, MESSAGE)
#define CY_MISRA_BLOCK_END(MISRA)

#endif // CY_COVERITY_2012_CHECK

/** \endcond */

#ifdef __cplusplus
}
#endif

/** \} group_utils */
