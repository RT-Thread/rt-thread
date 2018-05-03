/*!
*******************************************************************************
**
** \file      gh_pwm.h
**
** \brief     Pulse Width Modulator.
**
**            Copyright:   2012 - 2016 (C) GoKe Microelectronics
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      Do not modify this file as it is generated automatically.
**
******************************************************************************/
#ifndef _GH_PWM_H
#define _GH_PWM_H

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

#define GH_PWM_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_PWM_DEBUG_PRINT_FUNCTION printk
#else
#define GH_PWM_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_PWM_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* PWM_Control */
    U32 all;
    struct {
        U32 xon                         : 16;
        U32 xoff                        : 16;
    } bitc;
} GH_PWM_CONTROL_S;

typedef union { /* PWM_Enable */
    U32 all;
    struct {
        U32 enb                         : 1;
        U32                             : 31;
    } bitc;
} GH_PWM_ENABLE_S;

typedef union { /* PWM_Mode */
    U32 all;
    struct {
        U32 divider                     : 10;
        U32 mode                        : 1;
        U32                             : 21;
    } bitc;
} GH_PWM_MODE_S;

typedef union { /* PWM_Control1 */
    U32 all;
    struct {
        U32 xon                         : 16;
        U32 xoff                        : 16;
    } bitc;
} GH_PWM_CONTROL1_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register PWM_Control (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PWM_Control'. */
void GH_PWM_set_Control(U8 index, U32 data);
/*! \brief Reads the register 'PWM_Control'. */
U32  GH_PWM_get_Control(U8 index);
/*! \brief Writes the bit group 'xoff' of register 'PWM_Control'. */
void GH_PWM_set_Control_xoff(U8 index, U16 data);
/*! \brief Reads the bit group 'xoff' of register 'PWM_Control'. */
U16  GH_PWM_get_Control_xoff(U8 index);
/*! \brief Writes the bit group 'xon' of register 'PWM_Control'. */
void GH_PWM_set_Control_xon(U8 index, U16 data);
/*! \brief Reads the bit group 'xon' of register 'PWM_Control'. */
U16  GH_PWM_get_Control_xon(U8 index);

/*----------------------------------------------------------------------------*/
/* register PWM_Enable (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PWM_Enable'. */
void GH_PWM_set_Enable(U8 index, U32 data);
/*! \brief Reads the register 'PWM_Enable'. */
U32  GH_PWM_get_Enable(U8 index);
/*! \brief Writes the bit group 'enb' of register 'PWM_Enable'. */
void GH_PWM_set_Enable_enb(U8 index, U8 data);
/*! \brief Reads the bit group 'enb' of register 'PWM_Enable'. */
U8   GH_PWM_get_Enable_enb(U8 index);

/*----------------------------------------------------------------------------*/
/* register PWM_Mode (read/write)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PWM_Mode'. */
void GH_PWM_set_Mode(U8 index, U32 data);
/*! \brief Reads the register 'PWM_Mode'. */
U32  GH_PWM_get_Mode(U8 index);
/*! \brief Writes the bit group 'mode' of register 'PWM_Mode'. */
void GH_PWM_set_Mode_mode(U8 index, U8 data);
/*! \brief Reads the bit group 'mode' of register 'PWM_Mode'. */
U8   GH_PWM_get_Mode_mode(U8 index);
/*! \brief Writes the bit group 'divider' of register 'PWM_Mode'. */
void GH_PWM_set_Mode_divider(U8 index, U16 data);
/*! \brief Reads the bit group 'divider' of register 'PWM_Mode'. */
U16  GH_PWM_get_Mode_divider(U8 index);

/*----------------------------------------------------------------------------*/
/* register PWM_Control1 (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PWM_Control1'. */
void GH_PWM_set_Control1(U8 index, U32 data);
/*! \brief Reads the register 'PWM_Control1'. */
U32  GH_PWM_get_Control1(U8 index);
/*! \brief Writes the bit group 'xoff' of register 'PWM_Control1'. */
void GH_PWM_set_Control1_xoff(U8 index, U16 data);
/*! \brief Reads the bit group 'xoff' of register 'PWM_Control1'. */
U16  GH_PWM_get_Control1_xoff(U8 index);
/*! \brief Writes the bit group 'xon' of register 'PWM_Control1'. */
void GH_PWM_set_Control1_xon(U8 index, U16 data);
/*! \brief Reads the bit group 'xon' of register 'PWM_Control1'. */
U16  GH_PWM_get_Control1_xon(U8 index);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_PWM_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_pwm.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_PWM_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

