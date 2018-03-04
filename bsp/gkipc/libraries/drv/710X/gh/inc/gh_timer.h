/*!
*******************************************************************************
**
** \file      gh_timer.h
**
** \brief     TIMER.
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

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_TIMER_CNTNSTS                                   FIO_ADDRESS(TIMER,0xa000B000) /* read/write */
#define REG_TIMER_RELOADN                                   FIO_ADDRESS(TIMER,0xa000B004) /* read/write */
#define REG_TIMER_MATCH1                                    FIO_ADDRESS(TIMER,0xa000B008) /* read/write */
#define REG_TIMER_MATCH2                                    FIO_ADDRESS(TIMER,0xa000B00C) /* read/write */
#define REG_TIMER_CONTROL                                   FIO_ADDRESS(TIMER,0xa000B030) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* TIMER_Control */
    U32 all;
    struct {
        U32 enable1                     : 1;
        U32 clksel1                     : 1;
        U32 of1                         : 1;
        U32                             : 1;
        U32 enable2                     : 1;
        U32 clksel2                     : 1;
        U32 of2                         : 1;
        U32                             : 1;
        U32 enable3                     : 1;
        U32 clksel3                     : 1;
        U32 of3                         : 1;
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
/* register TIMER_CntnSts (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'TIMER_CntnSts'. */
void GH_TIMER_set_CntnSts(U8 index, U32 data);
/*! \brief Reads the register 'TIMER_CntnSts'. */
U32  GH_TIMER_get_CntnSts(U8 index);

/*----------------------------------------------------------------------------*/
/* register TIMER_Reloadn (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'TIMER_Reloadn'. */
void GH_TIMER_set_Reloadn(U8 index, U32 data);
/*! \brief Reads the register 'TIMER_Reloadn'. */
U32  GH_TIMER_get_Reloadn(U8 index);

/*----------------------------------------------------------------------------*/
/* register TIMER_Match1 (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'TIMER_Match1'. */
void GH_TIMER_set_Match1(U8 index, U32 data);
/*! \brief Reads the register 'TIMER_Match1'. */
U32  GH_TIMER_get_Match1(U8 index);

/*----------------------------------------------------------------------------*/
/* register TIMER_Match2 (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'TIMER_Match2'. */
void GH_TIMER_set_Match2(U8 index, U32 data);
/*! \brief Reads the register 'TIMER_Match2'. */
U32  GH_TIMER_get_Match2(U8 index);

/*----------------------------------------------------------------------------*/
/* register TIMER_Control (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'TIMER_Control'. */
void GH_TIMER_set_Control(U32 data);
/*! \brief Reads the register 'TIMER_Control'. */
U32  GH_TIMER_get_Control(void);
/*! \brief Writes the bit group 'Enable1' of register 'TIMER_Control'. */
void GH_TIMER_set_Control_Enable1(U8 data);
/*! \brief Reads the bit group 'Enable1' of register 'TIMER_Control'. */
U8   GH_TIMER_get_Control_Enable1(void);
/*! \brief Writes the bit group 'ClkSel1' of register 'TIMER_Control'. */
void GH_TIMER_set_Control_ClkSel1(U8 data);
/*! \brief Reads the bit group 'ClkSel1' of register 'TIMER_Control'. */
U8   GH_TIMER_get_Control_ClkSel1(void);
/*! \brief Writes the bit group 'OF1' of register 'TIMER_Control'. */
void GH_TIMER_set_Control_OF1(U8 data);
/*! \brief Reads the bit group 'OF1' of register 'TIMER_Control'. */
U8   GH_TIMER_get_Control_OF1(void);
/*! \brief Writes the bit group 'Enable2' of register 'TIMER_Control'. */
void GH_TIMER_set_Control_Enable2(U8 data);
/*! \brief Reads the bit group 'Enable2' of register 'TIMER_Control'. */
U8   GH_TIMER_get_Control_Enable2(void);
/*! \brief Writes the bit group 'ClkSel2' of register 'TIMER_Control'. */
void GH_TIMER_set_Control_ClkSel2(U8 data);
/*! \brief Reads the bit group 'ClkSel2' of register 'TIMER_Control'. */
U8   GH_TIMER_get_Control_ClkSel2(void);
/*! \brief Writes the bit group 'OF2' of register 'TIMER_Control'. */
void GH_TIMER_set_Control_OF2(U8 data);
/*! \brief Reads the bit group 'OF2' of register 'TIMER_Control'. */
U8   GH_TIMER_get_Control_OF2(void);
/*! \brief Writes the bit group 'Enable3' of register 'TIMER_Control'. */
void GH_TIMER_set_Control_Enable3(U8 data);
/*! \brief Reads the bit group 'Enable3' of register 'TIMER_Control'. */
U8   GH_TIMER_get_Control_Enable3(void);
/*! \brief Writes the bit group 'ClkSel3' of register 'TIMER_Control'. */
void GH_TIMER_set_Control_ClkSel3(U8 data);
/*! \brief Reads the bit group 'ClkSel3' of register 'TIMER_Control'. */
U8   GH_TIMER_get_Control_ClkSel3(void);
/*! \brief Writes the bit group 'OF3' of register 'TIMER_Control'. */
void GH_TIMER_set_Control_OF3(U8 data);
/*! \brief Reads the bit group 'OF3' of register 'TIMER_Control'. */
U8   GH_TIMER_get_Control_OF3(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_TIMER_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_timer.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_TIMER_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

