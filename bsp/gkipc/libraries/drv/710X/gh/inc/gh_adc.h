/*!
*******************************************************************************
**
** \file      gh_adc.h
**
** \brief     ADC.
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
#ifndef _GH_ADC_H
#define _GH_ADC_H

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

#define GH_ADC_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_ADC_DEBUG_PRINT_FUNCTION printk
#else
#define GH_ADC_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_ADC_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_ADC_AUX_ATOP                                    FIO_ADDRESS(ADC,0x90020A00) /* read/write */
#define REG_ADC_GPIO                                        FIO_ADDRESS(ADC,0x90020A04) /* read/write */
#define REG_ADC_CONTROL                                     FIO_ADDRESS(ADC,0xa000D000) /* read/write */
#define REG_ADC_READDATA                                    FIO_ADDRESS(ADC,0xa000D004) /* read */
#define REG_ADC_ENABLE                                      FIO_ADDRESS(ADC,0xa000D018) /* read/write */
#define REG_ADC_INTCONTROL                                  FIO_ADDRESS(ADC,0xa000D044) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* ADC_AUX_ATOP */
    U32 all;
    struct {
        U32 sar_pd                      : 1;
        U32 sar_maxnsel                 : 3;
        U32 sar_maxsel                  : 4;
        U32 sar_oneshot                 : 1;
        U32 sar_freerun                 : 1;
        U32 sar_refnsel                 : 2;
        U32 sar_refsel                  : 3;
        U32                             : 17;
    } bitc;
} GH_ADC_AUX_ATOP_S;

typedef union { /* ADC_GPIO */
    U32 all;
    struct {
        U32 sar_test                    : 4;
        U32 sar_key_pge                 : 4;
        U32                             : 24;
    } bitc;
} GH_ADC_GPIO_S;

typedef union { /* ADC_Control */
    U32 all;
    struct {
        U32 status                      : 1;
        U32 start                       : 1;
        U32                             : 1;
        U32 channel                     : 3;
        U32                             : 26;
    } bitc;
} GH_ADC_CONTROL_S;

typedef union { /* ADC_IntControl */
    U32 all;
    struct {
        U32 val_lo                      : 10;
        U32                             : 5;
        U32 val_hi                      : 10;
        U32                             : 5;
        U32 en_lo                       : 1;
        U32 en_hi                       : 1;
    } bitc;
} GH_ADC_INTCONTROL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register ADC_AUX_ATOP (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ADC_AUX_ATOP'. */
void GH_ADC_set_AUX_ATOP(U32 data);
/*! \brief Reads the register 'ADC_AUX_ATOP'. */
U32  GH_ADC_get_AUX_ATOP(void);
/*! \brief Writes the bit group 'sar_pd' of register 'ADC_AUX_ATOP'. */
void GH_ADC_set_AUX_ATOP_sar_pd(U8 data);
/*! \brief Reads the bit group 'sar_pd' of register 'ADC_AUX_ATOP'. */
U8   GH_ADC_get_AUX_ATOP_sar_pd(void);
/*! \brief Writes the bit group 'sar_maxnsel' of register 'ADC_AUX_ATOP'. */
void GH_ADC_set_AUX_ATOP_sar_maxnsel(U8 data);
/*! \brief Reads the bit group 'sar_maxnsel' of register 'ADC_AUX_ATOP'. */
U8   GH_ADC_get_AUX_ATOP_sar_maxnsel(void);
/*! \brief Writes the bit group 'sar_maxsel' of register 'ADC_AUX_ATOP'. */
void GH_ADC_set_AUX_ATOP_sar_maxsel(U8 data);
/*! \brief Reads the bit group 'sar_maxsel' of register 'ADC_AUX_ATOP'. */
U8   GH_ADC_get_AUX_ATOP_sar_maxsel(void);
/*! \brief Writes the bit group 'sar_oneshot' of register 'ADC_AUX_ATOP'. */
void GH_ADC_set_AUX_ATOP_sar_oneshot(U8 data);
/*! \brief Reads the bit group 'sar_oneshot' of register 'ADC_AUX_ATOP'. */
U8   GH_ADC_get_AUX_ATOP_sar_oneshot(void);
/*! \brief Writes the bit group 'sar_freerun' of register 'ADC_AUX_ATOP'. */
void GH_ADC_set_AUX_ATOP_sar_freerun(U8 data);
/*! \brief Reads the bit group 'sar_freerun' of register 'ADC_AUX_ATOP'. */
U8   GH_ADC_get_AUX_ATOP_sar_freerun(void);
/*! \brief Writes the bit group 'sar_refnsel' of register 'ADC_AUX_ATOP'. */
void GH_ADC_set_AUX_ATOP_sar_refnsel(U8 data);
/*! \brief Reads the bit group 'sar_refnsel' of register 'ADC_AUX_ATOP'. */
U8   GH_ADC_get_AUX_ATOP_sar_refnsel(void);
/*! \brief Writes the bit group 'sar_refsel' of register 'ADC_AUX_ATOP'. */
void GH_ADC_set_AUX_ATOP_sar_refsel(U8 data);
/*! \brief Reads the bit group 'sar_refsel' of register 'ADC_AUX_ATOP'. */
U8   GH_ADC_get_AUX_ATOP_sar_refsel(void);

/*----------------------------------------------------------------------------*/
/* register ADC_GPIO (read/write)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ADC_GPIO'. */
void GH_ADC_set_GPIO(U32 data);
/*! \brief Reads the register 'ADC_GPIO'. */
U32  GH_ADC_get_GPIO(void);
/*! \brief Writes the bit group 'sar_test' of register 'ADC_GPIO'. */
void GH_ADC_set_GPIO_sar_test(U8 data);
/*! \brief Reads the bit group 'sar_test' of register 'ADC_GPIO'. */
U8   GH_ADC_get_GPIO_sar_test(void);
/*! \brief Writes the bit group 'sar_key_pge' of register 'ADC_GPIO'. */
void GH_ADC_set_GPIO_sar_key_pge(U8 data);
/*! \brief Reads the bit group 'sar_key_pge' of register 'ADC_GPIO'. */
U8   GH_ADC_get_GPIO_sar_key_pge(void);

/*----------------------------------------------------------------------------*/
/* register ADC_Control (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ADC_Control'. */
void GH_ADC_set_Control(U32 data);
/*! \brief Reads the register 'ADC_Control'. */
U32  GH_ADC_get_Control(void);
/*! \brief Writes the bit group 'status' of register 'ADC_Control'. */
void GH_ADC_set_Control_status(U8 data);
/*! \brief Reads the bit group 'status' of register 'ADC_Control'. */
U8   GH_ADC_get_Control_status(void);
/*! \brief Writes the bit group 'start' of register 'ADC_Control'. */
void GH_ADC_set_Control_start(U8 data);
/*! \brief Reads the bit group 'start' of register 'ADC_Control'. */
U8   GH_ADC_get_Control_start(void);
/*! \brief Writes the bit group 'channel' of register 'ADC_Control'. */
void GH_ADC_set_Control_channel(U8 data);
/*! \brief Reads the bit group 'channel' of register 'ADC_Control'. */
U8   GH_ADC_get_Control_channel(void);

/*----------------------------------------------------------------------------*/
/* register ADC_ReadData (read)                                               */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'ADC_ReadData'. */
U32  GH_ADC_get_ReadData(U8 index);

/*----------------------------------------------------------------------------*/
/* register ADC_Enable (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ADC_Enable'. */
void GH_ADC_set_Enable(U32 data);
/*! \brief Reads the register 'ADC_Enable'. */
U32  GH_ADC_get_Enable(void);

/*----------------------------------------------------------------------------*/
/* register ADC_IntControl (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ADC_IntControl'. */
void GH_ADC_set_IntControl(U8 index, U32 data);
/*! \brief Reads the register 'ADC_IntControl'. */
U32  GH_ADC_get_IntControl(U8 index);
/*! \brief Writes the bit group 'val_lo' of register 'ADC_IntControl'. */
void GH_ADC_set_IntControl_val_lo(U8 index, U16 data);
/*! \brief Reads the bit group 'val_lo' of register 'ADC_IntControl'. */
U16  GH_ADC_get_IntControl_val_lo(U8 index);
/*! \brief Writes the bit group 'val_hi' of register 'ADC_IntControl'. */
void GH_ADC_set_IntControl_val_hi(U8 index, U16 data);
/*! \brief Reads the bit group 'val_hi' of register 'ADC_IntControl'. */
U16  GH_ADC_get_IntControl_val_hi(U8 index);
/*! \brief Writes the bit group 'en_lo' of register 'ADC_IntControl'. */
void GH_ADC_set_IntControl_en_lo(U8 index, U8 data);
/*! \brief Reads the bit group 'en_lo' of register 'ADC_IntControl'. */
U8   GH_ADC_get_IntControl_en_lo(U8 index);
/*! \brief Writes the bit group 'en_hi' of register 'ADC_IntControl'. */
void GH_ADC_set_IntControl_en_hi(U8 index, U8 data);
/*! \brief Reads the bit group 'en_hi' of register 'ADC_IntControl'. */
U8   GH_ADC_get_IntControl_en_hi(U8 index);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_ADC_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_adc.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_ADC_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

