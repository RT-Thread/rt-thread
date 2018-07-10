/*!
*******************************************************************************
**
** \file      gh_pmu_irr.h
**
** \brief     Infrared Receiver.
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
#if GH_INLINE_LEVEL < 2
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
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_PMU_IRR_set_Prog(U32 data)
{
    m_pmu_irr_prog.all = data;
    *(volatile U32 *)REG_PMU_IRR_PROG = data;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_Prog] <-- 0x%08x\n",
                        REG_PMU_IRR_PROG,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_IRR_getm_Prog(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_Prog] --> 0x%08x\n",
                        m_pmu_irr_prog.all);
    #endif
    return m_pmu_irr_prog.all;
}
GH_INLINE void GH_PMU_IRR_set_Prog_RX(U8 data)
{
    m_pmu_irr_prog.bitc.rx = data;
    *(volatile U32 *)REG_PMU_IRR_PROG = m_pmu_irr_prog.all;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_Prog_RX] <-- 0x%08x\n",
                        REG_PMU_IRR_PROG,m_pmu_irr_prog.all,m_pmu_irr_prog.all);
    #endif
}
GH_INLINE U8   GH_PMU_IRR_getm_Prog_RX(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_Prog_RX] --> 0x%08x\n",
                        m_pmu_irr_prog.bitc.rx);
    #endif
    return m_pmu_irr_prog.bitc.rx;
}
GH_INLINE void GH_PMU_IRR_set_Prog_RISING_EDGE(U8 data)
{
    m_pmu_irr_prog.bitc.rising_edge = data;
    *(volatile U32 *)REG_PMU_IRR_PROG = m_pmu_irr_prog.all;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_Prog_RISING_EDGE] <-- 0x%08x\n",
                        REG_PMU_IRR_PROG,m_pmu_irr_prog.all,m_pmu_irr_prog.all);
    #endif
}
GH_INLINE U8   GH_PMU_IRR_getm_Prog_RISING_EDGE(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_Prog_RISING_EDGE] --> 0x%08x\n",
                        m_pmu_irr_prog.bitc.rising_edge);
    #endif
    return m_pmu_irr_prog.bitc.rising_edge;
}
GH_INLINE void GH_PMU_IRR_set_Prog_FALLING_EDGE(U8 data)
{
    m_pmu_irr_prog.bitc.falling_edge = data;
    *(volatile U32 *)REG_PMU_IRR_PROG = m_pmu_irr_prog.all;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_Prog_FALLING_EDGE] <-- 0x%08x\n",
                        REG_PMU_IRR_PROG,m_pmu_irr_prog.all,m_pmu_irr_prog.all);
    #endif
}
GH_INLINE U8   GH_PMU_IRR_getm_Prog_FALLING_EDGE(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_Prog_FALLING_EDGE] --> 0x%08x\n",
                        m_pmu_irr_prog.bitc.falling_edge);
    #endif
    return m_pmu_irr_prog.bitc.falling_edge;
}
GH_INLINE void GH_PMU_IRR_set_Prog_RESTARTS(U8 data)
{
    m_pmu_irr_prog.bitc.restarts = data;
    *(volatile U32 *)REG_PMU_IRR_PROG = m_pmu_irr_prog.all;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_Prog_RESTARTS] <-- 0x%08x\n",
                        REG_PMU_IRR_PROG,m_pmu_irr_prog.all,m_pmu_irr_prog.all);
    #endif
}
GH_INLINE U8   GH_PMU_IRR_getm_Prog_RESTARTS(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_Prog_RESTARTS] --> 0x%08x\n",
                        m_pmu_irr_prog.bitc.restarts);
    #endif
    return m_pmu_irr_prog.bitc.restarts;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRR_PreScaler_l (write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'PMU_IRR_PreScaler_l'. */
void GH_PMU_IRR_set_PreScaler_l(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRR_PreScaler_l'. */
U32  GH_PMU_IRR_getm_PreScaler_l(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRR_PreScaler_l'. */
void GH_PMU_IRR_set_PreScaler_l_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRR_PreScaler_l'. */
U8   GH_PMU_IRR_getm_PreScaler_l_VALUE(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_PMU_IRR_set_PreScaler_l(U32 data)
{
    m_pmu_irr_prescaler_l.all = data;
    *(volatile U32 *)REG_PMU_IRR_PRESCALER_L = data;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_PreScaler_l] <-- 0x%08x\n",
                        REG_PMU_IRR_PRESCALER_L,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_IRR_getm_PreScaler_l(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_PreScaler_l] --> 0x%08x\n",
                        m_pmu_irr_prescaler_l.all);
    #endif
    return m_pmu_irr_prescaler_l.all;
}
GH_INLINE void GH_PMU_IRR_set_PreScaler_l_VALUE(U8 data)
{
    m_pmu_irr_prescaler_l.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRR_PRESCALER_L = m_pmu_irr_prescaler_l.all;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_PreScaler_l_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRR_PRESCALER_L,m_pmu_irr_prescaler_l.all,m_pmu_irr_prescaler_l.all);
    #endif
}
GH_INLINE U8   GH_PMU_IRR_getm_PreScaler_l_VALUE(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_PreScaler_l_VALUE] --> 0x%08x\n",
                        m_pmu_irr_prescaler_l.bitc.value);
    #endif
    return m_pmu_irr_prescaler_l.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRR_PreScaler_h (write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'PMU_IRR_PreScaler_h'. */
void GH_PMU_IRR_set_PreScaler_h(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRR_PreScaler_h'. */
U32  GH_PMU_IRR_getm_PreScaler_h(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRR_PreScaler_h'. */
void GH_PMU_IRR_set_PreScaler_h_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRR_PreScaler_h'. */
U8   GH_PMU_IRR_getm_PreScaler_h_VALUE(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_PMU_IRR_set_PreScaler_h(U32 data)
{
    m_pmu_irr_prescaler_h.all = data;
    *(volatile U32 *)REG_PMU_IRR_PRESCALER_H = data;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_PreScaler_h] <-- 0x%08x\n",
                        REG_PMU_IRR_PRESCALER_H,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_IRR_getm_PreScaler_h(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_PreScaler_h] --> 0x%08x\n",
                        m_pmu_irr_prescaler_h.all);
    #endif
    return m_pmu_irr_prescaler_h.all;
}
GH_INLINE void GH_PMU_IRR_set_PreScaler_h_VALUE(U8 data)
{
    m_pmu_irr_prescaler_h.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRR_PRESCALER_H = m_pmu_irr_prescaler_h.all;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_PreScaler_h_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRR_PRESCALER_H,m_pmu_irr_prescaler_h.all,m_pmu_irr_prescaler_h.all);
    #endif
}
GH_INLINE U8   GH_PMU_IRR_getm_PreScaler_h_VALUE(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_PreScaler_h_VALUE] --> 0x%08x\n",
                        m_pmu_irr_prescaler_h.bitc.value);
    #endif
    return m_pmu_irr_prescaler_h.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRR_Read (read/clear)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
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
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE U32  GH_PMU_IRR_get_Read(void)
{
    m_pmu_irr_read.all = *(volatile U32 *)REG_PMU_IRR_READ;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_IRR_get_Read] --> 0x%08x\n",
                        REG_PMU_IRR_READ,m_pmu_irr_read.all );
    #endif
    return m_pmu_irr_read.all;
}
GH_INLINE U32  GH_PMU_IRR_getm_Read(void)
{
    return m_pmu_irr_read.all;
}
GH_INLINE U8   GH_PMU_IRR_getm_Read_PULSE27(void)
{
    return m_pmu_irr_read.bitc.pulse27;
}
GH_INLINE U8   GH_PMU_IRR_getm_Read_EDGE(void)
{
    return m_pmu_irr_read.bitc.edge;
}
GH_INLINE U8   GH_PMU_IRR_getm_Read_VALID(void)
{
    return m_pmu_irr_read.bitc.valid;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRR_IrqMask_l (write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'PMU_IRR_IrqMask_l'. */
void GH_PMU_IRR_set_IrqMask_l(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRR_IrqMask_l'. */
U32  GH_PMU_IRR_getm_IrqMask_l(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRR_IrqMask_l'. */
void GH_PMU_IRR_set_IrqMask_l_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRR_IrqMask_l'. */
U8   GH_PMU_IRR_getm_IrqMask_l_VALUE(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_PMU_IRR_set_IrqMask_l(U32 data)
{
    m_pmu_irr_irqmask_l.all = data;
    *(volatile U32 *)REG_PMU_IRR_IRQMASK_L = data;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_IrqMask_l] <-- 0x%08x\n",
                        REG_PMU_IRR_IRQMASK_L,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_IRR_getm_IrqMask_l(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_IrqMask_l] --> 0x%08x\n",
                        m_pmu_irr_irqmask_l.all);
    #endif
    return m_pmu_irr_irqmask_l.all;
}
GH_INLINE void GH_PMU_IRR_set_IrqMask_l_VALUE(U8 data)
{
    m_pmu_irr_irqmask_l.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRR_IRQMASK_L = m_pmu_irr_irqmask_l.all;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_IrqMask_l_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRR_IRQMASK_L,m_pmu_irr_irqmask_l.all,m_pmu_irr_irqmask_l.all);
    #endif
}
GH_INLINE U8   GH_PMU_IRR_getm_IrqMask_l_VALUE(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_IrqMask_l_VALUE] --> 0x%08x\n",
                        m_pmu_irr_irqmask_l.bitc.value);
    #endif
    return m_pmu_irr_irqmask_l.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRR_IrqMask_h (write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'PMU_IRR_IrqMask_h'. */
void GH_PMU_IRR_set_IrqMask_h(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRR_IrqMask_h'. */
U32  GH_PMU_IRR_getm_IrqMask_h(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRR_IrqMask_h'. */
void GH_PMU_IRR_set_IrqMask_h_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRR_IrqMask_h'. */
U8   GH_PMU_IRR_getm_IrqMask_h_VALUE(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_PMU_IRR_set_IrqMask_h(U32 data)
{
    m_pmu_irr_irqmask_h.all = data;
    *(volatile U32 *)REG_PMU_IRR_IRQMASK_H = data;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_IrqMask_h] <-- 0x%08x\n",
                        REG_PMU_IRR_IRQMASK_H,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_IRR_getm_IrqMask_h(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_IrqMask_h] --> 0x%08x\n",
                        m_pmu_irr_irqmask_h.all);
    #endif
    return m_pmu_irr_irqmask_h.all;
}
GH_INLINE void GH_PMU_IRR_set_IrqMask_h_VALUE(U8 data)
{
    m_pmu_irr_irqmask_h.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRR_IRQMASK_H = m_pmu_irr_irqmask_h.all;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_IrqMask_h_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRR_IRQMASK_H,m_pmu_irr_irqmask_h.all,m_pmu_irr_irqmask_h.all);
    #endif
}
GH_INLINE U8   GH_PMU_IRR_getm_IrqMask_h_VALUE(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_IrqMask_h_VALUE] --> 0x%08x\n",
                        m_pmu_irr_irqmask_h.bitc.value);
    #endif
    return m_pmu_irr_irqmask_h.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_PMU_IRR_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_PMU_IRR_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

