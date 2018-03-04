/*!
*******************************************************************************
**
** \file      gh_timer.h
**
** \brief     TIMER.
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
#ifndef _GH_TIMER_H
#define _GH_TIMER_H

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

#define GH_TIMER_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_TIMER_DEBUG_PRINT_FUNCTION printk
#else
#define GH_TIMER_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_TIMER_ENABLE_DEBUG_PRINT
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
#define REG_TIMER_T1CNTNSTS                                 FIO_ADDRESS(TIMER,0xA0000000) /* read/write */
#define REG_TIMER_T1MATCH1                                  FIO_ADDRESS(TIMER,0xA0000004) /* read/write */
#define REG_TIMER_T1MATCH2                                  FIO_ADDRESS(TIMER,0xA0000008) /* read/write */
#define REG_TIMER_CONTROL                                   FIO_ADDRESS(TIMER,0xA000000C) /* read/write */
#define REG_TIMER_T2CNTNSTS                                 FIO_ADDRESS(TIMER,0xA0000014) /* read/write */
#define REG_TIMER_T2MATCH1                                  FIO_ADDRESS(TIMER,0xA0000018) /* read/write */
#define REG_TIMER_T2MATCH2                                  FIO_ADDRESS(TIMER,0xA000001C) /* read/write */
#define REG_TIMER_T3CNTNSTS                                 FIO_ADDRESS(TIMER,0xA0000020) /* read/write */
#define REG_TIMER_T3MATCH1                                  FIO_ADDRESS(TIMER,0xA0000024) /* read/write */
#define REG_TIMER_T3MATCH2                                  FIO_ADDRESS(TIMER,0xA0000028) /* read/write */
#define REG_TIMER_T1RELOADN                                 FIO_ADDRESS(TIMER,0xA0000030) /* read/write */
#define REG_TIMER_T2RELOADN                                 FIO_ADDRESS(TIMER,0xA0000034) /* read/write */
#define REG_TIMER_T3RELOADN                                 FIO_ADDRESS(TIMER,0xA0000038) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* TIMER_Control */
    U32 all;
    struct {
        U32 clksel3                     : 1;
        U32 clksel2                     : 1;
        U32 clksel1                     : 1;
        U32                             : 1;
        U32 of3                         : 1;
        U32 of2                         : 1;
        U32 of1                         : 1;
        U32                             : 1;
        U32 enable3                     : 1;
        U32 enable2                     : 1;
        U32 enable1                     : 1;
        U32                             : 21;
    } bitc;
} GH_TIMER_CONTROL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register TIMER_T1CntnSts (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TIMER_T1CntnSts'. */
void GH_TIMER_set_T1CntnSts(U32 data);
/*! \brief Reads the register 'TIMER_T1CntnSts'. */
U32  GH_TIMER_get_T1CntnSts(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_TIMER_set_T1CntnSts(U32 data)
{
    *(volatile U32 *)REG_TIMER_T1CNTNSTS = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T1CntnSts] <-- 0x%08x\n",
                        REG_TIMER_T1CNTNSTS,data,data);
    #endif
}
GH_INLINE U32  GH_TIMER_get_T1CntnSts(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T1CNTNSTS);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T1CntnSts] --> 0x%08x\n",
                        REG_TIMER_T1CNTNSTS,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_T1Match1 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TIMER_T1Match1'. */
void GH_TIMER_set_T1Match1(U32 data);
/*! \brief Reads the register 'TIMER_T1Match1'. */
U32  GH_TIMER_get_T1Match1(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_TIMER_set_T1Match1(U32 data)
{
    *(volatile U32 *)REG_TIMER_T1MATCH1 = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T1Match1] <-- 0x%08x\n",
                        REG_TIMER_T1MATCH1,data,data);
    #endif
}
GH_INLINE U32  GH_TIMER_get_T1Match1(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T1MATCH1);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T1Match1] --> 0x%08x\n",
                        REG_TIMER_T1MATCH1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_T1Match2 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TIMER_T1Match2'. */
void GH_TIMER_set_T1Match2(U32 data);
/*! \brief Reads the register 'TIMER_T1Match2'. */
U32  GH_TIMER_get_T1Match2(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_TIMER_set_T1Match2(U32 data)
{
    *(volatile U32 *)REG_TIMER_T1MATCH2 = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T1Match2] <-- 0x%08x\n",
                        REG_TIMER_T1MATCH2,data,data);
    #endif
}
GH_INLINE U32  GH_TIMER_get_T1Match2(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T1MATCH2);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T1Match2] --> 0x%08x\n",
                        REG_TIMER_T1MATCH2,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_Control (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TIMER_Control'. */
void GH_TIMER_set_Control(U32 data);
/*! \brief Reads the register 'TIMER_Control'. */
U32  GH_TIMER_get_Control(void);
/*! \brief Writes the bit group 'ClkSel3' of register 'TIMER_Control'. */
void GH_TIMER_set_Control_ClkSel3(U8 data);
/*! \brief Reads the bit group 'ClkSel3' of register 'TIMER_Control'. */
U8   GH_TIMER_get_Control_ClkSel3(void);
/*! \brief Writes the bit group 'ClkSel2' of register 'TIMER_Control'. */
void GH_TIMER_set_Control_ClkSel2(U8 data);
/*! \brief Reads the bit group 'ClkSel2' of register 'TIMER_Control'. */
U8   GH_TIMER_get_Control_ClkSel2(void);
/*! \brief Writes the bit group 'ClkSel1' of register 'TIMER_Control'. */
void GH_TIMER_set_Control_ClkSel1(U8 data);
/*! \brief Reads the bit group 'ClkSel1' of register 'TIMER_Control'. */
U8   GH_TIMER_get_Control_ClkSel1(void);
/*! \brief Writes the bit group 'OF3' of register 'TIMER_Control'. */
void GH_TIMER_set_Control_OF3(U8 data);
/*! \brief Reads the bit group 'OF3' of register 'TIMER_Control'. */
U8   GH_TIMER_get_Control_OF3(void);
/*! \brief Writes the bit group 'OF2' of register 'TIMER_Control'. */
void GH_TIMER_set_Control_OF2(U8 data);
/*! \brief Reads the bit group 'OF2' of register 'TIMER_Control'. */
U8   GH_TIMER_get_Control_OF2(void);
/*! \brief Writes the bit group 'OF1' of register 'TIMER_Control'. */
void GH_TIMER_set_Control_OF1(U8 data);
/*! \brief Reads the bit group 'OF1' of register 'TIMER_Control'. */
U8   GH_TIMER_get_Control_OF1(void);
/*! \brief Writes the bit group 'Enable3' of register 'TIMER_Control'. */
void GH_TIMER_set_Control_Enable3(U8 data);
/*! \brief Reads the bit group 'Enable3' of register 'TIMER_Control'. */
U8   GH_TIMER_get_Control_Enable3(void);
/*! \brief Writes the bit group 'Enable2' of register 'TIMER_Control'. */
void GH_TIMER_set_Control_Enable2(U8 data);
/*! \brief Reads the bit group 'Enable2' of register 'TIMER_Control'. */
U8   GH_TIMER_get_Control_Enable2(void);
/*! \brief Writes the bit group 'Enable1' of register 'TIMER_Control'. */
void GH_TIMER_set_Control_Enable1(U8 data);
/*! \brief Reads the bit group 'Enable1' of register 'TIMER_Control'. */
U8   GH_TIMER_get_Control_Enable1(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_TIMER_set_Control(U32 data)
{
    *(volatile U32 *)REG_TIMER_CONTROL = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_Control] <-- 0x%08x\n",
                        REG_TIMER_CONTROL,data,data);
    #endif
}
GH_INLINE U32  GH_TIMER_get_Control(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_Control] --> 0x%08x\n",
                        REG_TIMER_CONTROL,value);
    #endif
    return value;
}
GH_INLINE void GH_TIMER_set_Control_ClkSel3(U8 data)
{
    GH_TIMER_CONTROL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL;
    d.bitc.clksel3 = data;
    *(volatile U32 *)REG_TIMER_CONTROL = d.all;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_Control_ClkSel3] <-- 0x%08x\n",
                        REG_TIMER_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_TIMER_get_Control_ClkSel3(void)
{
    GH_TIMER_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL);

    tmp_value.all = value;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_Control_ClkSel3] --> 0x%08x\n",
                        REG_TIMER_CONTROL,value);
    #endif
    return tmp_value.bitc.clksel3;
}
GH_INLINE void GH_TIMER_set_Control_ClkSel2(U8 data)
{
    GH_TIMER_CONTROL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL;
    d.bitc.clksel2 = data;
    *(volatile U32 *)REG_TIMER_CONTROL = d.all;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_Control_ClkSel2] <-- 0x%08x\n",
                        REG_TIMER_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_TIMER_get_Control_ClkSel2(void)
{
    GH_TIMER_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL);

    tmp_value.all = value;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_Control_ClkSel2] --> 0x%08x\n",
                        REG_TIMER_CONTROL,value);
    #endif
    return tmp_value.bitc.clksel2;
}
GH_INLINE void GH_TIMER_set_Control_ClkSel1(U8 data)
{
    GH_TIMER_CONTROL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL;
    d.bitc.clksel1 = data;
    *(volatile U32 *)REG_TIMER_CONTROL = d.all;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_Control_ClkSel1] <-- 0x%08x\n",
                        REG_TIMER_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_TIMER_get_Control_ClkSel1(void)
{
    GH_TIMER_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL);

    tmp_value.all = value;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_Control_ClkSel1] --> 0x%08x\n",
                        REG_TIMER_CONTROL,value);
    #endif
    return tmp_value.bitc.clksel1;
}
GH_INLINE void GH_TIMER_set_Control_OF3(U8 data)
{
    GH_TIMER_CONTROL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL;
    d.bitc.of3 = data;
    *(volatile U32 *)REG_TIMER_CONTROL = d.all;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_Control_OF3] <-- 0x%08x\n",
                        REG_TIMER_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_TIMER_get_Control_OF3(void)
{
    GH_TIMER_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL);

    tmp_value.all = value;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_Control_OF3] --> 0x%08x\n",
                        REG_TIMER_CONTROL,value);
    #endif
    return tmp_value.bitc.of3;
}
GH_INLINE void GH_TIMER_set_Control_OF2(U8 data)
{
    GH_TIMER_CONTROL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL;
    d.bitc.of2 = data;
    *(volatile U32 *)REG_TIMER_CONTROL = d.all;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_Control_OF2] <-- 0x%08x\n",
                        REG_TIMER_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_TIMER_get_Control_OF2(void)
{
    GH_TIMER_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL);

    tmp_value.all = value;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_Control_OF2] --> 0x%08x\n",
                        REG_TIMER_CONTROL,value);
    #endif
    return tmp_value.bitc.of2;
}
GH_INLINE void GH_TIMER_set_Control_OF1(U8 data)
{
    GH_TIMER_CONTROL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL;
    d.bitc.of1 = data;
    *(volatile U32 *)REG_TIMER_CONTROL = d.all;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_Control_OF1] <-- 0x%08x\n",
                        REG_TIMER_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_TIMER_get_Control_OF1(void)
{
    GH_TIMER_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL);

    tmp_value.all = value;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_Control_OF1] --> 0x%08x\n",
                        REG_TIMER_CONTROL,value);
    #endif
    return tmp_value.bitc.of1;
}
GH_INLINE void GH_TIMER_set_Control_Enable3(U8 data)
{
    GH_TIMER_CONTROL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL;
    d.bitc.enable3 = data;
    *(volatile U32 *)REG_TIMER_CONTROL = d.all;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_Control_Enable3] <-- 0x%08x\n",
                        REG_TIMER_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_TIMER_get_Control_Enable3(void)
{
    GH_TIMER_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL);

    tmp_value.all = value;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_Control_Enable3] --> 0x%08x\n",
                        REG_TIMER_CONTROL,value);
    #endif
    return tmp_value.bitc.enable3;
}
GH_INLINE void GH_TIMER_set_Control_Enable2(U8 data)
{
    GH_TIMER_CONTROL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL;
    d.bitc.enable2 = data;
    *(volatile U32 *)REG_TIMER_CONTROL = d.all;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_Control_Enable2] <-- 0x%08x\n",
                        REG_TIMER_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_TIMER_get_Control_Enable2(void)
{
    GH_TIMER_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL);

    tmp_value.all = value;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_Control_Enable2] --> 0x%08x\n",
                        REG_TIMER_CONTROL,value);
    #endif
    return tmp_value.bitc.enable2;
}
GH_INLINE void GH_TIMER_set_Control_Enable1(U8 data)
{
    GH_TIMER_CONTROL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL;
    d.bitc.enable1 = data;
    *(volatile U32 *)REG_TIMER_CONTROL = d.all;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_Control_Enable1] <-- 0x%08x\n",
                        REG_TIMER_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_TIMER_get_Control_Enable1(void)
{
    GH_TIMER_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL);

    tmp_value.all = value;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_Control_Enable1] --> 0x%08x\n",
                        REG_TIMER_CONTROL,value);
    #endif
    return tmp_value.bitc.enable1;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_T2CntnSts (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TIMER_T2CntnSts'. */
void GH_TIMER_set_T2CntnSts(U32 data);
/*! \brief Reads the register 'TIMER_T2CntnSts'. */
U32  GH_TIMER_get_T2CntnSts(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_TIMER_set_T2CntnSts(U32 data)
{
    *(volatile U32 *)REG_TIMER_T2CNTNSTS = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T2CntnSts] <-- 0x%08x\n",
                        REG_TIMER_T2CNTNSTS,data,data);
    #endif
}
GH_INLINE U32  GH_TIMER_get_T2CntnSts(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T2CNTNSTS);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T2CntnSts] --> 0x%08x\n",
                        REG_TIMER_T2CNTNSTS,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_T2Match1 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TIMER_T2Match1'. */
void GH_TIMER_set_T2Match1(U32 data);
/*! \brief Reads the register 'TIMER_T2Match1'. */
U32  GH_TIMER_get_T2Match1(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_TIMER_set_T2Match1(U32 data)
{
    *(volatile U32 *)REG_TIMER_T2MATCH1 = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T2Match1] <-- 0x%08x\n",
                        REG_TIMER_T2MATCH1,data,data);
    #endif
}
GH_INLINE U32  GH_TIMER_get_T2Match1(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T2MATCH1);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T2Match1] --> 0x%08x\n",
                        REG_TIMER_T2MATCH1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_T2Match2 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TIMER_T2Match2'. */
void GH_TIMER_set_T2Match2(U32 data);
/*! \brief Reads the register 'TIMER_T2Match2'. */
U32  GH_TIMER_get_T2Match2(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_TIMER_set_T2Match2(U32 data)
{
    *(volatile U32 *)REG_TIMER_T2MATCH2 = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T2Match2] <-- 0x%08x\n",
                        REG_TIMER_T2MATCH2,data,data);
    #endif
}
GH_INLINE U32  GH_TIMER_get_T2Match2(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T2MATCH2);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T2Match2] --> 0x%08x\n",
                        REG_TIMER_T2MATCH2,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_T3CntnSts (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TIMER_T3CntnSts'. */
void GH_TIMER_set_T3CntnSts(U32 data);
/*! \brief Reads the register 'TIMER_T3CntnSts'. */
U32  GH_TIMER_get_T3CntnSts(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_TIMER_set_T3CntnSts(U32 data)
{
    *(volatile U32 *)REG_TIMER_T3CNTNSTS = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T3CntnSts] <-- 0x%08x\n",
                        REG_TIMER_T3CNTNSTS,data,data);
    #endif
}
GH_INLINE U32  GH_TIMER_get_T3CntnSts(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T3CNTNSTS);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T3CntnSts] --> 0x%08x\n",
                        REG_TIMER_T3CNTNSTS,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_T3Match1 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TIMER_T3Match1'. */
void GH_TIMER_set_T3Match1(U32 data);
/*! \brief Reads the register 'TIMER_T3Match1'. */
U32  GH_TIMER_get_T3Match1(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_TIMER_set_T3Match1(U32 data)
{
    *(volatile U32 *)REG_TIMER_T3MATCH1 = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T3Match1] <-- 0x%08x\n",
                        REG_TIMER_T3MATCH1,data,data);
    #endif
}
GH_INLINE U32  GH_TIMER_get_T3Match1(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T3MATCH1);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T3Match1] --> 0x%08x\n",
                        REG_TIMER_T3MATCH1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_T3Match2 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TIMER_T3Match2'. */
void GH_TIMER_set_T3Match2(U32 data);
/*! \brief Reads the register 'TIMER_T3Match2'. */
U32  GH_TIMER_get_T3Match2(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_TIMER_set_T3Match2(U32 data)
{
    *(volatile U32 *)REG_TIMER_T3MATCH2 = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T3Match2] <-- 0x%08x\n",
                        REG_TIMER_T3MATCH2,data,data);
    #endif
}
GH_INLINE U32  GH_TIMER_get_T3Match2(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T3MATCH2);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T3Match2] --> 0x%08x\n",
                        REG_TIMER_T3MATCH2,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_T1Reloadn (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TIMER_T1Reloadn'. */
void GH_TIMER_set_T1Reloadn(U32 data);
/*! \brief Reads the register 'TIMER_T1Reloadn'. */
U32  GH_TIMER_get_T1Reloadn(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_TIMER_set_T1Reloadn(U32 data)
{
    *(volatile U32 *)REG_TIMER_T1RELOADN = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T1Reloadn] <-- 0x%08x\n",
                        REG_TIMER_T1RELOADN,data,data);
    #endif
}
GH_INLINE U32  GH_TIMER_get_T1Reloadn(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T1RELOADN);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T1Reloadn] --> 0x%08x\n",
                        REG_TIMER_T1RELOADN,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_T2Reloadn (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TIMER_T2Reloadn'. */
void GH_TIMER_set_T2Reloadn(U32 data);
/*! \brief Reads the register 'TIMER_T2Reloadn'. */
U32  GH_TIMER_get_T2Reloadn(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_TIMER_set_T2Reloadn(U32 data)
{
    *(volatile U32 *)REG_TIMER_T2RELOADN = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T2Reloadn] <-- 0x%08x\n",
                        REG_TIMER_T2RELOADN,data,data);
    #endif
}
GH_INLINE U32  GH_TIMER_get_T2Reloadn(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T2RELOADN);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T2Reloadn] --> 0x%08x\n",
                        REG_TIMER_T2RELOADN,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_T3Reloadn (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TIMER_T3Reloadn'. */
void GH_TIMER_set_T3Reloadn(U32 data);
/*! \brief Reads the register 'TIMER_T3Reloadn'. */
U32  GH_TIMER_get_T3Reloadn(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_TIMER_set_T3Reloadn(U32 data)
{
    *(volatile U32 *)REG_TIMER_T3RELOADN = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T3Reloadn] <-- 0x%08x\n",
                        REG_TIMER_T3RELOADN,data,data);
    #endif
}
GH_INLINE U32  GH_TIMER_get_T3Reloadn(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T3RELOADN);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T3Reloadn] --> 0x%08x\n",
                        REG_TIMER_T3RELOADN,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_TIMER_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_TIMER_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

