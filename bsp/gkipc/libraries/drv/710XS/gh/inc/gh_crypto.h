/*!
*******************************************************************************
**
** \file      gh_crypto.h
**
** \brief     Cryptography Engine.
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      Do not modify this file as it is generated automatically.
**
******************************************************************************/
#ifndef _GH_CRYPTO_H
#define _GH_CRYPTO_H

#ifdef __LINUX__
#include "reg4linux.h"
#else
#define FIO_ADDRESS(block,address) (address)
#define FIO_MOFFSET(block,moffset) (moffset)
#endif

#ifndef __LINUX__
#include "gtypes.h" /* global type definitions */
#include "gh_lib_cfg.h" /* configuration */
#endif

#define GH_CRYPTO_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_CRYPTO_DEBUG_PRINT_FUNCTION printk
#else
#define GH_CRYPTO_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_CRYPTO_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/* check configuration */
#ifndef GH_INLINE_LEVEL
  #error "GH_INLINE_LEVEL is not defined!"
#endif
#if GH_INLINE_LEVEL > 2
  #error "GH_INLINE_LEVEL must be set 0, 1 or 2!"
#endif
#ifndef GH_INLINE
  #error "GH_INLINE is not defined!"
#endif

/* disable inlining for debugging */
#ifdef DEBUG
  #undef GH_INLINE_LEVEL
  #define GH_INLINE_LEVEL 0
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_CRYPTO_DES_KEY                                  FIO_ADDRESS(CRYPTO,0x90005008) /* read/write */
#define REG_CRYPTO_DES_INPUT                                FIO_ADDRESS(CRYPTO,0x90005010) /* read/write */
#define REG_CRYPTO_DES_OPCODE                               FIO_ADDRESS(CRYPTO,0x90005004) /* read/write */
#define REG_CRYPTO_DES_OUTPUT_RDY                           FIO_ADDRESS(CRYPTO,0x90005018) /* read */
#define REG_CRYPTO_DES_OUTPUT                               FIO_ADDRESS(CRYPTO,0x9000501C) /* read */
#define REG_CRYPTO_DES_INTERRUPT                            FIO_ADDRESS(CRYPTO,0x90005000) /* read/write */
#define REG_CRYPTO_AES_128_KEY                              FIO_ADDRESS(CRYPTO,0x90005068) /* read/write */
#define REG_CRYPTO_AES_192_KEY                              FIO_ADDRESS(CRYPTO,0x90005050) /* read/write */
#define REG_CRYPTO_AES_256_KEY                              FIO_ADDRESS(CRYPTO,0x90005030) /* read/write */
#define REG_CRYPTO_AES_INPUT                                FIO_ADDRESS(CRYPTO,0x90005078) /* read/write */
#define REG_CRYPTO_AES_OPCODE                               FIO_ADDRESS(CRYPTO,0x9000502c) /* read/write */
#define REG_CRYPTO_AES_OUTPUT_RDY                           FIO_ADDRESS(CRYPTO,0x90005088) /* read */
#define REG_CRYPTO_AES_OUTPUT                               FIO_ADDRESS(CRYPTO,0x9000508C) /* read */
#define REG_CRYPTO_AES_INTERRUPT                            FIO_ADDRESS(CRYPTO,0x90005028) /* read/write */
#define REG_CRYPTO_EFUSE_BOOT_SW_DIS                        FIO_ADDRESS(CRYPTO,0x90005024) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* CRYPTO_DES_Opcode */
    U32 all;
    struct {
        U32 mode                        : 1;
        U32                             : 31;
    } bitc;
} GH_CRYPTO_DES_OPCODE_S;

typedef union { /* CRYPTO_DES_Output_Rdy */
    U32 all;
    struct {
        U32 rdy                         : 1;
        U32                             : 31;
    } bitc;
} GH_CRYPTO_DES_OUTPUT_RDY_S;

typedef union { /* CRYPTO_DES_Interrupt */
    U32 all;
    struct {
        U32 en                          : 1;
        U32                             : 31;
    } bitc;
} GH_CRYPTO_DES_INTERRUPT_S;

typedef union { /* CRYPTO_AES_Opcode */
    U32 all;
    struct {
        U32 mode                        : 1;
        U32                             : 31;
    } bitc;
} GH_CRYPTO_AES_OPCODE_S;

typedef union { /* CRYPTO_AES_Output_Rdy */
    U32 all;
    struct {
        U32 rdy                         : 1;
        U32                             : 31;
    } bitc;
} GH_CRYPTO_AES_OUTPUT_RDY_S;

typedef union { /* CRYPTO_AES_Interrupt */
    U32 all;
    struct {
        U32 en                          : 1;
        U32                             : 31;
    } bitc;
} GH_CRYPTO_AES_INTERRUPT_S;

typedef union { /* CRYPTO_EFUSE_BOOT_SW_DIS */
    U32 all;
    struct {
        U32 efuse_boot_dis              : 1;
        U32 efuse_boot_sw               : 1;
        U32                             : 30;
    } bitc;
} GH_CRYPTO_EFUSE_BOOT_SW_DIS_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Key (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'CRYPTO_DES_Key'. */
void GH_CRYPTO_set_DES_Key(U8 index, U32 data);
/*! \brief Reads the register 'CRYPTO_DES_Key'. */
U32  GH_CRYPTO_get_DES_Key(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_CRYPTO_set_DES_Key(U8 index, U32 data)
{
    *(volatile U32 *)(REG_CRYPTO_DES_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)) = data;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_DES_Key] <-- 0x%08x\n",
                        (REG_CRYPTO_DES_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)),data,data);
    #endif
}
GH_INLINE U32  GH_CRYPTO_get_DES_Key(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_DES_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_DES_Key] --> 0x%08x\n",
                        (REG_CRYPTO_DES_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Input (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'CRYPTO_DES_Input'. */
void GH_CRYPTO_set_DES_Input(U8 index, U32 data);
/*! \brief Reads the register 'CRYPTO_DES_Input'. */
U32  GH_CRYPTO_get_DES_Input(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_CRYPTO_set_DES_Input(U8 index, U32 data)
{
    *(volatile U32 *)(REG_CRYPTO_DES_INPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)) = data;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_DES_Input] <-- 0x%08x\n",
                        (REG_CRYPTO_DES_INPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)),data,data);
    #endif
}
GH_INLINE U32  GH_CRYPTO_get_DES_Input(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_DES_INPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_DES_Input] --> 0x%08x\n",
                        (REG_CRYPTO_DES_INPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Opcode (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'CRYPTO_DES_Opcode'. */
void GH_CRYPTO_set_DES_Opcode(U32 data);
/*! \brief Reads the register 'CRYPTO_DES_Opcode'. */
U32  GH_CRYPTO_get_DES_Opcode(void);
/*! \brief Writes the bit group 'mode' of register 'CRYPTO_DES_Opcode'. */
void GH_CRYPTO_set_DES_Opcode_mode(U8 data);
/*! \brief Reads the bit group 'mode' of register 'CRYPTO_DES_Opcode'. */
U8   GH_CRYPTO_get_DES_Opcode_mode(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_CRYPTO_set_DES_Opcode(U32 data)
{
    *(volatile U32 *)REG_CRYPTO_DES_OPCODE = data;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_DES_Opcode] <-- 0x%08x\n",
                        REG_CRYPTO_DES_OPCODE,data,data);
    #endif
}
GH_INLINE U32  GH_CRYPTO_get_DES_Opcode(void)
{
    U32 value = (*(volatile U32 *)REG_CRYPTO_DES_OPCODE);

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_DES_Opcode] --> 0x%08x\n",
                        REG_CRYPTO_DES_OPCODE,value);
    #endif
    return value;
}
GH_INLINE void GH_CRYPTO_set_DES_Opcode_mode(U8 data)
{
    GH_CRYPTO_DES_OPCODE_S d;
    d.all = *(volatile U32 *)REG_CRYPTO_DES_OPCODE;
    d.bitc.mode = data;
    *(volatile U32 *)REG_CRYPTO_DES_OPCODE = d.all;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_DES_Opcode_mode] <-- 0x%08x\n",
                        REG_CRYPTO_DES_OPCODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_CRYPTO_get_DES_Opcode_mode(void)
{
    GH_CRYPTO_DES_OPCODE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_DES_OPCODE);

    tmp_value.all = value;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_DES_Opcode_mode] --> 0x%08x\n",
                        REG_CRYPTO_DES_OPCODE,value);
    #endif
    return tmp_value.bitc.mode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Output_Rdy (read)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'CRYPTO_DES_Output_Rdy'. */
U32  GH_CRYPTO_get_DES_Output_Rdy(void);
/*! \brief Reads the bit group 'Rdy' of register 'CRYPTO_DES_Output_Rdy'. */
U8   GH_CRYPTO_get_DES_Output_Rdy_Rdy(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_CRYPTO_get_DES_Output_Rdy(void)
{
    U32 value = (*(volatile U32 *)REG_CRYPTO_DES_OUTPUT_RDY);

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_DES_Output_Rdy] --> 0x%08x\n",
                        REG_CRYPTO_DES_OUTPUT_RDY,value);
    #endif
    return value;
}
GH_INLINE U8   GH_CRYPTO_get_DES_Output_Rdy_Rdy(void)
{
    GH_CRYPTO_DES_OUTPUT_RDY_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_DES_OUTPUT_RDY);

    tmp_value.all = value;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_DES_Output_Rdy_Rdy] --> 0x%08x\n",
                        REG_CRYPTO_DES_OUTPUT_RDY,value);
    #endif
    return tmp_value.bitc.rdy;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Output (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'CRYPTO_DES_Output'. */
U32  GH_CRYPTO_get_DES_Output(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_CRYPTO_get_DES_Output(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_DES_OUTPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_DES_Output] --> 0x%08x\n",
                        (REG_CRYPTO_DES_OUTPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Interrupt (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'CRYPTO_DES_Interrupt'. */
void GH_CRYPTO_set_DES_Interrupt(U32 data);
/*! \brief Reads the register 'CRYPTO_DES_Interrupt'. */
U32  GH_CRYPTO_get_DES_Interrupt(void);
/*! \brief Writes the bit group 'En' of register 'CRYPTO_DES_Interrupt'. */
void GH_CRYPTO_set_DES_Interrupt_En(U8 data);
/*! \brief Reads the bit group 'En' of register 'CRYPTO_DES_Interrupt'. */
U8   GH_CRYPTO_get_DES_Interrupt_En(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_CRYPTO_set_DES_Interrupt(U32 data)
{
    *(volatile U32 *)REG_CRYPTO_DES_INTERRUPT = data;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_DES_Interrupt] <-- 0x%08x\n",
                        REG_CRYPTO_DES_INTERRUPT,data,data);
    #endif
}
GH_INLINE U32  GH_CRYPTO_get_DES_Interrupt(void)
{
    U32 value = (*(volatile U32 *)REG_CRYPTO_DES_INTERRUPT);

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_DES_Interrupt] --> 0x%08x\n",
                        REG_CRYPTO_DES_INTERRUPT,value);
    #endif
    return value;
}
GH_INLINE void GH_CRYPTO_set_DES_Interrupt_En(U8 data)
{
    GH_CRYPTO_DES_INTERRUPT_S d;
    d.all = *(volatile U32 *)REG_CRYPTO_DES_INTERRUPT;
    d.bitc.en = data;
    *(volatile U32 *)REG_CRYPTO_DES_INTERRUPT = d.all;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_DES_Interrupt_En] <-- 0x%08x\n",
                        REG_CRYPTO_DES_INTERRUPT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_CRYPTO_get_DES_Interrupt_En(void)
{
    GH_CRYPTO_DES_INTERRUPT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_DES_INTERRUPT);

    tmp_value.all = value;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_DES_Interrupt_En] --> 0x%08x\n",
                        REG_CRYPTO_DES_INTERRUPT,value);
    #endif
    return tmp_value.bitc.en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_128_Key (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'CRYPTO_AES_128_Key'. */
void GH_CRYPTO_set_AES_128_Key(U8 index, U32 data);
/*! \brief Reads the register 'CRYPTO_AES_128_Key'. */
U32  GH_CRYPTO_get_AES_128_Key(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_CRYPTO_set_AES_128_Key(U8 index, U32 data)
{
    *(volatile U32 *)(REG_CRYPTO_AES_128_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)) = data;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_AES_128_Key] <-- 0x%08x\n",
                        (REG_CRYPTO_AES_128_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)),data,data);
    #endif
}
GH_INLINE U32  GH_CRYPTO_get_AES_128_Key(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_AES_128_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_AES_128_Key] --> 0x%08x\n",
                        (REG_CRYPTO_AES_128_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_192_Key (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'CRYPTO_AES_192_Key'. */
void GH_CRYPTO_set_AES_192_Key(U8 index, U32 data);
/*! \brief Reads the register 'CRYPTO_AES_192_Key'. */
U32  GH_CRYPTO_get_AES_192_Key(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_CRYPTO_set_AES_192_Key(U8 index, U32 data)
{
    *(volatile U32 *)(REG_CRYPTO_AES_192_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)) = data;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_AES_192_Key] <-- 0x%08x\n",
                        (REG_CRYPTO_AES_192_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)),data,data);
    #endif
}
GH_INLINE U32  GH_CRYPTO_get_AES_192_Key(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_AES_192_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_AES_192_Key] --> 0x%08x\n",
                        (REG_CRYPTO_AES_192_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_256_Key (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'CRYPTO_AES_256_Key'. */
void GH_CRYPTO_set_AES_256_Key(U8 index, U32 data);
/*! \brief Reads the register 'CRYPTO_AES_256_Key'. */
U32  GH_CRYPTO_get_AES_256_Key(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_CRYPTO_set_AES_256_Key(U8 index, U32 data)
{
    *(volatile U32 *)(REG_CRYPTO_AES_256_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)) = data;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_AES_256_Key] <-- 0x%08x\n",
                        (REG_CRYPTO_AES_256_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)),data,data);
    #endif
}
GH_INLINE U32  GH_CRYPTO_get_AES_256_Key(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_AES_256_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_AES_256_Key] --> 0x%08x\n",
                        (REG_CRYPTO_AES_256_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_Input (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'CRYPTO_AES_Input'. */
void GH_CRYPTO_set_AES_Input(U8 index, U32 data);
/*! \brief Reads the register 'CRYPTO_AES_Input'. */
U32  GH_CRYPTO_get_AES_Input(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_CRYPTO_set_AES_Input(U8 index, U32 data)
{
    *(volatile U32 *)(REG_CRYPTO_AES_INPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)) = data;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_AES_Input] <-- 0x%08x\n",
                        (REG_CRYPTO_AES_INPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)),data,data);
    #endif
}
GH_INLINE U32  GH_CRYPTO_get_AES_Input(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_AES_INPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_AES_Input] --> 0x%08x\n",
                        (REG_CRYPTO_AES_INPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_Opcode (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'CRYPTO_AES_Opcode'. */
void GH_CRYPTO_set_AES_Opcode(U32 data);
/*! \brief Reads the register 'CRYPTO_AES_Opcode'. */
U32  GH_CRYPTO_get_AES_Opcode(void);
/*! \brief Writes the bit group 'mode' of register 'CRYPTO_AES_Opcode'. */
void GH_CRYPTO_set_AES_Opcode_mode(U8 data);
/*! \brief Reads the bit group 'mode' of register 'CRYPTO_AES_Opcode'. */
U8   GH_CRYPTO_get_AES_Opcode_mode(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_CRYPTO_set_AES_Opcode(U32 data)
{
    *(volatile U32 *)REG_CRYPTO_AES_OPCODE = data;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_AES_Opcode] <-- 0x%08x\n",
                        REG_CRYPTO_AES_OPCODE,data,data);
    #endif
}
GH_INLINE U32  GH_CRYPTO_get_AES_Opcode(void)
{
    U32 value = (*(volatile U32 *)REG_CRYPTO_AES_OPCODE);

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_AES_Opcode] --> 0x%08x\n",
                        REG_CRYPTO_AES_OPCODE,value);
    #endif
    return value;
}
GH_INLINE void GH_CRYPTO_set_AES_Opcode_mode(U8 data)
{
    GH_CRYPTO_AES_OPCODE_S d;
    d.all = *(volatile U32 *)REG_CRYPTO_AES_OPCODE;
    d.bitc.mode = data;
    *(volatile U32 *)REG_CRYPTO_AES_OPCODE = d.all;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_AES_Opcode_mode] <-- 0x%08x\n",
                        REG_CRYPTO_AES_OPCODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_CRYPTO_get_AES_Opcode_mode(void)
{
    GH_CRYPTO_AES_OPCODE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_AES_OPCODE);

    tmp_value.all = value;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_AES_Opcode_mode] --> 0x%08x\n",
                        REG_CRYPTO_AES_OPCODE,value);
    #endif
    return tmp_value.bitc.mode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_Output_Rdy (read)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'CRYPTO_AES_Output_Rdy'. */
U32  GH_CRYPTO_get_AES_Output_Rdy(void);
/*! \brief Reads the bit group 'Rdy' of register 'CRYPTO_AES_Output_Rdy'. */
U8   GH_CRYPTO_get_AES_Output_Rdy_Rdy(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_CRYPTO_get_AES_Output_Rdy(void)
{
    U32 value = (*(volatile U32 *)REG_CRYPTO_AES_OUTPUT_RDY);

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_AES_Output_Rdy] --> 0x%08x\n",
                        REG_CRYPTO_AES_OUTPUT_RDY,value);
    #endif
    return value;
}
GH_INLINE U8   GH_CRYPTO_get_AES_Output_Rdy_Rdy(void)
{
    GH_CRYPTO_AES_OUTPUT_RDY_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_AES_OUTPUT_RDY);

    tmp_value.all = value;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_AES_Output_Rdy_Rdy] --> 0x%08x\n",
                        REG_CRYPTO_AES_OUTPUT_RDY,value);
    #endif
    return tmp_value.bitc.rdy;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_Output (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'CRYPTO_AES_Output'. */
U32  GH_CRYPTO_get_AES_Output(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_CRYPTO_get_AES_Output(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_AES_OUTPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_AES_Output] --> 0x%08x\n",
                        (REG_CRYPTO_AES_OUTPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_Interrupt (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'CRYPTO_AES_Interrupt'. */
void GH_CRYPTO_set_AES_Interrupt(U32 data);
/*! \brief Reads the register 'CRYPTO_AES_Interrupt'. */
U32  GH_CRYPTO_get_AES_Interrupt(void);
/*! \brief Writes the bit group 'En' of register 'CRYPTO_AES_Interrupt'. */
void GH_CRYPTO_set_AES_Interrupt_En(U8 data);
/*! \brief Reads the bit group 'En' of register 'CRYPTO_AES_Interrupt'. */
U8   GH_CRYPTO_get_AES_Interrupt_En(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_CRYPTO_set_AES_Interrupt(U32 data)
{
    *(volatile U32 *)REG_CRYPTO_AES_INTERRUPT = data;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_AES_Interrupt] <-- 0x%08x\n",
                        REG_CRYPTO_AES_INTERRUPT,data,data);
    #endif
}
GH_INLINE U32  GH_CRYPTO_get_AES_Interrupt(void)
{
    U32 value = (*(volatile U32 *)REG_CRYPTO_AES_INTERRUPT);

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_AES_Interrupt] --> 0x%08x\n",
                        REG_CRYPTO_AES_INTERRUPT,value);
    #endif
    return value;
}
GH_INLINE void GH_CRYPTO_set_AES_Interrupt_En(U8 data)
{
    GH_CRYPTO_AES_INTERRUPT_S d;
    d.all = *(volatile U32 *)REG_CRYPTO_AES_INTERRUPT;
    d.bitc.en = data;
    *(volatile U32 *)REG_CRYPTO_AES_INTERRUPT = d.all;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_AES_Interrupt_En] <-- 0x%08x\n",
                        REG_CRYPTO_AES_INTERRUPT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_CRYPTO_get_AES_Interrupt_En(void)
{
    GH_CRYPTO_AES_INTERRUPT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_AES_INTERRUPT);

    tmp_value.all = value;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_AES_Interrupt_En] --> 0x%08x\n",
                        REG_CRYPTO_AES_INTERRUPT,value);
    #endif
    return tmp_value.bitc.en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_EFUSE_BOOT_SW_DIS (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'CRYPTO_EFUSE_BOOT_SW_DIS'. */
void GH_CRYPTO_set_EFUSE_BOOT_SW_DIS(U32 data);
/*! \brief Reads the register 'CRYPTO_EFUSE_BOOT_SW_DIS'. */
U32  GH_CRYPTO_get_EFUSE_BOOT_SW_DIS(void);
/*! \brief Writes the bit group 'Efuse_boot_dis' of register 'CRYPTO_EFUSE_BOOT_SW_DIS'. */
void GH_CRYPTO_set_EFUSE_BOOT_SW_DIS_Efuse_boot_dis(U8 data);
/*! \brief Reads the bit group 'Efuse_boot_dis' of register 'CRYPTO_EFUSE_BOOT_SW_DIS'. */
U8   GH_CRYPTO_get_EFUSE_BOOT_SW_DIS_Efuse_boot_dis(void);
/*! \brief Writes the bit group 'Efuse_boot_sw' of register 'CRYPTO_EFUSE_BOOT_SW_DIS'. */
void GH_CRYPTO_set_EFUSE_BOOT_SW_DIS_Efuse_boot_sw(U8 data);
/*! \brief Reads the bit group 'Efuse_boot_sw' of register 'CRYPTO_EFUSE_BOOT_SW_DIS'. */
U8   GH_CRYPTO_get_EFUSE_BOOT_SW_DIS_Efuse_boot_sw(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_CRYPTO_set_EFUSE_BOOT_SW_DIS(U32 data)
{
    *(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS = data;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_EFUSE_BOOT_SW_DIS] <-- 0x%08x\n",
                        REG_CRYPTO_EFUSE_BOOT_SW_DIS,data,data);
    #endif
}
GH_INLINE U32  GH_CRYPTO_get_EFUSE_BOOT_SW_DIS(void)
{
    U32 value = (*(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS);

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_EFUSE_BOOT_SW_DIS] --> 0x%08x\n",
                        REG_CRYPTO_EFUSE_BOOT_SW_DIS,value);
    #endif
    return value;
}
GH_INLINE void GH_CRYPTO_set_EFUSE_BOOT_SW_DIS_Efuse_boot_dis(U8 data)
{
    GH_CRYPTO_EFUSE_BOOT_SW_DIS_S d;
    d.all = *(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS;
    d.bitc.efuse_boot_dis = data;
    *(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS = d.all;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_EFUSE_BOOT_SW_DIS_Efuse_boot_dis] <-- 0x%08x\n",
                        REG_CRYPTO_EFUSE_BOOT_SW_DIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_CRYPTO_get_EFUSE_BOOT_SW_DIS_Efuse_boot_dis(void)
{
    GH_CRYPTO_EFUSE_BOOT_SW_DIS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS);

    tmp_value.all = value;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_EFUSE_BOOT_SW_DIS_Efuse_boot_dis] --> 0x%08x\n",
                        REG_CRYPTO_EFUSE_BOOT_SW_DIS,value);
    #endif
    return tmp_value.bitc.efuse_boot_dis;
}
GH_INLINE void GH_CRYPTO_set_EFUSE_BOOT_SW_DIS_Efuse_boot_sw(U8 data)
{
    GH_CRYPTO_EFUSE_BOOT_SW_DIS_S d;
    d.all = *(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS;
    d.bitc.efuse_boot_sw = data;
    *(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS = d.all;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_EFUSE_BOOT_SW_DIS_Efuse_boot_sw] <-- 0x%08x\n",
                        REG_CRYPTO_EFUSE_BOOT_SW_DIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_CRYPTO_get_EFUSE_BOOT_SW_DIS_Efuse_boot_sw(void)
{
    GH_CRYPTO_EFUSE_BOOT_SW_DIS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS);

    tmp_value.all = value;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_EFUSE_BOOT_SW_DIS_Efuse_boot_sw] --> 0x%08x\n",
                        REG_CRYPTO_EFUSE_BOOT_SW_DIS,value);
    #endif
    return tmp_value.bitc.efuse_boot_sw;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_CRYPTO_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_CRYPTO_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

