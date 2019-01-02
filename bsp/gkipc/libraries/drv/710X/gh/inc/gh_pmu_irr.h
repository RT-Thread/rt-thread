/*!
*******************************************************************************
**
** \file      gh_pmu_irr.h
**
** \brief     Infrared Receiver.
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
#ifndef _GH_PMU_IRR_H
#define _GH_PMU_IRR_H

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

#define GH_PMU_IRR_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_PMU_IRR_DEBUG_PRINT_FUNCTION printk
#else
#define GH_PMU_IRR_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_PMU_IRR_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_PMU_IRR_PROG                                    FIO_ADDRESS(PMU_IRR,0x90082000) /* write */
#define REG_PMU_IRR_PRESCALER_L                             FIO_ADDRESS(PMU_IRR,0x90082004) /* write */
#define REG_PMU_IRR_PRESCALER_H                             FIO_ADDRESS(PMU_IRR,0x90082008) /* write */
#define REG_PMU_IRR_READ                                    FIO_ADDRESS(PMU_IRR,0x9008200C) /* read/clear */
#define REG_PMU_IRR_IRQMASK_L                               FIO_ADDRESS(PMU_IRR,0x90082014) /* write */
#define REG_PMU_IRR_IRQMASK_H                               FIO_ADDRESS(PMU_IRR,0x90082018) /* write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* PMU_IRR_Prog */
    U32 all;
    struct {
        U32 rx                          : 1;
        U32 rising_edge                 : 1;
        U32 falling_edge                : 1;
        U32 restarts                    : 1;
        U32                             : 28;
    } bitc;
} GH_PMU_IRR_PROG_S;

typedef union { /* PMU_IRR_PreScaler_l */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRR_PRESCALER_L_S;

typedef union { /* PMU_IRR_PreScaler_h */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRR_PRESCALER_H_S;

typedef union { /* PMU_IRR_Read */
    U32 all;
    struct {
        U32 pulse27                     : 6;
        U32 edge                        : 1;
        U32 valid                       : 1;
        U32                             : 24;
    } bitc;
} GH_PMU_IRR_READ_S;

typedef union { /* PMU_IRR_IrqMask_l */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRR_IRQMASK_L_S;

typedef union { /* PMU_IRR_IrqMask_h */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRR_IRQMASK_H_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern GH_PMU_IRR_PROG_S                       m_pmu_irr_prog;
extern GH_PMU_IRR_PRESCALER_L_S                m_pmu_irr_prescaler_l;
extern GH_PMU_IRR_PRESCALER_H_S                m_pmu_irr_prescaler_h;
extern GH_PMU_IRR_READ_S                       m_pmu_irr_read;
extern GH_PMU_IRR_IRQMASK_L_S                  m_pmu_irr_irqmask_l;
extern GH_PMU_IRR_IRQMASK_H_S                  m_pmu_irr_irqmask_h;

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register PMU_IRR_Prog (write)                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRR_Prog'. */
void GH_PMU_IRR_set_Prog(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRR_Prog'. */
U32  GH_PMU_IRR_getm_Prog(void);
/*! \brief Writes the bit group 'RX' of register 'PMU_IRR_Prog'. */
void GH_PMU_IRR_set_Prog_RX(U8 data);
/*! \brief Reads the bit group 'RX' from the mirror variable of register 'PMU_IRR_Prog'. */
U8   GH_PMU_IRR_getm_Prog_RX(void);
/*! \brief Writes the bit group 'RISING_EDGE' of register 'PMU_IRR_Prog'. */
void GH_PMU_IRR_set_Prog_RISING_EDGE(U8 data);
/*! \brief Reads the bit group 'RISING_EDGE' from the mirror variable of register 'PMU_IRR_Prog'. */
U8   GH_PMU_IRR_getm_Prog_RISING_EDGE(void);
/*! \brief Writes the bit group 'FALLING_EDGE' of register 'PMU_IRR_Prog'. */
void GH_PMU_IRR_set_Prog_FALLING_EDGE(U8 data);
/*! \brief Reads the bit group 'FALLING_EDGE' from the mirror variable of register 'PMU_IRR_Prog'. */
U8   GH_PMU_IRR_getm_Prog_FALLING_EDGE(void);
/*! \brief Writes the bit group 'RESTARTS' of register 'PMU_IRR_Prog'. */
void GH_PMU_IRR_set_Prog_RESTARTS(U8 data);
/*! \brief Reads the bit group 'RESTARTS' from the mirror variable of register 'PMU_IRR_Prog'. */
U8   GH_PMU_IRR_getm_Prog_RESTARTS(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRR_PreScaler_l (write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRR_PreScaler_l'. */
void GH_PMU_IRR_set_PreScaler_l(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRR_PreScaler_l'. */
U32  GH_PMU_IRR_getm_PreScaler_l(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRR_PreScaler_l'. */
void GH_PMU_IRR_set_PreScaler_l_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRR_PreScaler_l'. */
U8   GH_PMU_IRR_getm_PreScaler_l_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRR_PreScaler_h (write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRR_PreScaler_h'. */
void GH_PMU_IRR_set_PreScaler_h(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRR_PreScaler_h'. */
U32  GH_PMU_IRR_getm_PreScaler_h(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRR_PreScaler_h'. */
void GH_PMU_IRR_set_PreScaler_h_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRR_PreScaler_h'. */
U8   GH_PMU_IRR_getm_PreScaler_h_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRR_Read (read/clear)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRR_Read'. */
U32  GH_PMU_IRR_get_Read(void);
/*! \brief Reads the mirror variable of the register 'PMU_IRR_Read'. */
U32  GH_PMU_IRR_getm_Read(void);
/*! \brief Reads the bit group 'PULSE27' from the mirror variable of register 'PMU_IRR_Read'. */
U8   GH_PMU_IRR_getm_Read_PULSE27(void);
/*! \brief Reads the bit group 'EDGE' from the mirror variable of register 'PMU_IRR_Read'. */
U8   GH_PMU_IRR_getm_Read_EDGE(void);
/*! \brief Reads the bit group 'VALID' from the mirror variable of register 'PMU_IRR_Read'. */
U8   GH_PMU_IRR_getm_Read_VALID(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRR_IrqMask_l (write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRR_IrqMask_l'. */
void GH_PMU_IRR_set_IrqMask_l(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRR_IrqMask_l'. */
U32  GH_PMU_IRR_getm_IrqMask_l(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRR_IrqMask_l'. */
void GH_PMU_IRR_set_IrqMask_l_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRR_IrqMask_l'. */
U8   GH_PMU_IRR_getm_IrqMask_l_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRR_IrqMask_h (write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRR_IrqMask_h'. */
void GH_PMU_IRR_set_IrqMask_h(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRR_IrqMask_h'. */
U32  GH_PMU_IRR_getm_IrqMask_h(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRR_IrqMask_h'. */
void GH_PMU_IRR_set_IrqMask_h_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRR_IrqMask_h'. */
U8   GH_PMU_IRR_getm_IrqMask_h_VALUE(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_PMU_IRR_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_pmu_irr.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_PMU_IRR_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

