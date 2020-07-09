/******************************************************************************
**
** \file      gh_pmu_irr.c
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
#ifndef SRC_INLINE
#include "gh_pmu_irr.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_PMU_IRR_PROG_REAL                               FIO_ADDRESS(PMU_IRR,0x60082000) /* write */
#define REG_PMU_IRR_PRESCALER_L_REAL                        FIO_ADDRESS(PMU_IRR,0x60082004) /* write */
#define REG_PMU_IRR_PRESCALER_H_REAL                        FIO_ADDRESS(PMU_IRR,0x60082008) /* write */
#define REG_PMU_IRR_READ_REAL                               FIO_ADDRESS(PMU_IRR,0x6008200C) /* read/clear */
#define REG_PMU_IRR_IRQMASK_L_REAL                          FIO_ADDRESS(PMU_IRR,0x60082014) /* write */
#define REG_PMU_IRR_IRQMASK_H_REAL                          FIO_ADDRESS(PMU_IRR,0x60082018) /* write */

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
} GH_PMU_IRR_PROG_REAL_S;

typedef union { /* PMU_IRR_PreScaler_l */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRR_PRESCALER_L_REAL_S;

typedef union { /* PMU_IRR_PreScaler_h */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRR_PRESCALER_H_REAL_S;

typedef union { /* PMU_IRR_Read */
    U32 all;
    struct {
        U32 pulse27                     : 6;
        U32 edge                        : 1;
        U32 valid                       : 1;
        U32                             : 24;
    } bitc;
} GH_PMU_IRR_READ_REAL_S;

typedef union { /* PMU_IRR_IrqMask_l */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRR_IRQMASK_L_REAL_S;

typedef union { /* PMU_IRR_IrqMask_h */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRR_IRQMASK_H_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_PMU_IRR_PROG_S                       m_pmu_irr_prog;
GH_PMU_IRR_PRESCALER_L_S                m_pmu_irr_prescaler_l;
GH_PMU_IRR_PRESCALER_H_S                m_pmu_irr_prescaler_h;
GH_PMU_IRR_READ_S                       m_pmu_irr_read;
GH_PMU_IRR_IRQMASK_L_S                  m_pmu_irr_irqmask_l;
GH_PMU_IRR_IRQMASK_H_S                  m_pmu_irr_irqmask_h;

/*----------------------------------------------------------------------------*/
/* register PMU_IRR_Prog (write)                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRR_set_Prog(U32 data)
{
    m_pmu_irr_prog.all = data;
    GH_PMU_IRR_PROG_REAL_S real;
    GH_PMU_IRR_PROG_S dummy;
    dummy.all = data ;
    real.bitc.rx = dummy.bitc.rx;
    real.bitc.rising_edge = dummy.bitc.rising_edge;
    real.bitc.falling_edge = dummy.bitc.falling_edge;
    real.bitc.restarts = dummy.bitc.restarts;
    *(volatile U32 *)REG_PMU_IRR_PROG_REAL = real.all;
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
    GH_PMU_IRR_PROG_REAL_S real;
    real.bitc.rx = m_pmu_irr_prog.bitc.rx;
    real.bitc.rising_edge = m_pmu_irr_prog.bitc.rising_edge;
    real.bitc.falling_edge = m_pmu_irr_prog.bitc.falling_edge;
    real.bitc.restarts = m_pmu_irr_prog.bitc.restarts;
    *(volatile U32 *)REG_PMU_IRR_PROG_REAL = real.all;
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
    GH_PMU_IRR_PROG_REAL_S real;
    real.bitc.rx = m_pmu_irr_prog.bitc.rx;
    real.bitc.rising_edge = m_pmu_irr_prog.bitc.rising_edge;
    real.bitc.falling_edge = m_pmu_irr_prog.bitc.falling_edge;
    real.bitc.restarts = m_pmu_irr_prog.bitc.restarts;
    *(volatile U32 *)REG_PMU_IRR_PROG_REAL = real.all;
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
    GH_PMU_IRR_PROG_REAL_S real;
    real.bitc.rx = m_pmu_irr_prog.bitc.rx;
    real.bitc.rising_edge = m_pmu_irr_prog.bitc.rising_edge;
    real.bitc.falling_edge = m_pmu_irr_prog.bitc.falling_edge;
    real.bitc.restarts = m_pmu_irr_prog.bitc.restarts;
    *(volatile U32 *)REG_PMU_IRR_PROG_REAL = real.all;
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
    GH_PMU_IRR_PROG_REAL_S real;
    real.bitc.rx = m_pmu_irr_prog.bitc.rx;
    real.bitc.rising_edge = m_pmu_irr_prog.bitc.rising_edge;
    real.bitc.falling_edge = m_pmu_irr_prog.bitc.falling_edge;
    real.bitc.restarts = m_pmu_irr_prog.bitc.restarts;
    *(volatile U32 *)REG_PMU_IRR_PROG_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRR_getm_Prog_RESTARTS(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_Prog_RESTARTS] --> 0x%08x\n",
                        m_pmu_irr_prog.bitc.restarts);
    #endif
    return m_pmu_irr_prog.bitc.restarts;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRR_PreScaler_l (write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRR_set_PreScaler_l(U32 data)
{
    m_pmu_irr_prescaler_l.all = data;
    GH_PMU_IRR_PRESCALER_L_REAL_S real;
    GH_PMU_IRR_PRESCALER_L_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRR_PRESCALER_L_REAL = real.all;
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
    GH_PMU_IRR_PRESCALER_L_REAL_S real;
    real.bitc.value = m_pmu_irr_prescaler_l.bitc.value;
    *(volatile U32 *)REG_PMU_IRR_PRESCALER_L_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRR_getm_PreScaler_l_VALUE(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_PreScaler_l_VALUE] --> 0x%08x\n",
                        m_pmu_irr_prescaler_l.bitc.value);
    #endif
    return m_pmu_irr_prescaler_l.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRR_PreScaler_h (write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRR_set_PreScaler_h(U32 data)
{
    m_pmu_irr_prescaler_h.all = data;
    GH_PMU_IRR_PRESCALER_H_REAL_S real;
    GH_PMU_IRR_PRESCALER_H_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRR_PRESCALER_H_REAL = real.all;
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
    GH_PMU_IRR_PRESCALER_H_REAL_S real;
    real.bitc.value = m_pmu_irr_prescaler_h.bitc.value;
    *(volatile U32 *)REG_PMU_IRR_PRESCALER_H_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRR_getm_PreScaler_h_VALUE(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_PreScaler_h_VALUE] --> 0x%08x\n",
                        m_pmu_irr_prescaler_h.bitc.value);
    #endif
    return m_pmu_irr_prescaler_h.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRR_Read (read/clear)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_PMU_IRR_get_Read(void)
{
    GH_PMU_IRR_READ_REAL_S real;
    GH_PMU_IRR_READ_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_PMU_IRR_READ_REAL);

    dummy.bitc.pulse27 = real.bitc.pulse27;
    dummy.bitc.edge = real.bitc.edge;
    dummy.bitc.valid = real.bitc.valid;
    m_pmu_irr_read.all = dummy.all;
    return dummy.all;
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

/*----------------------------------------------------------------------------*/
/* register PMU_IRR_IrqMask_l (write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRR_set_IrqMask_l(U32 data)
{
    m_pmu_irr_irqmask_l.all = data;
    GH_PMU_IRR_IRQMASK_L_REAL_S real;
    GH_PMU_IRR_IRQMASK_L_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRR_IRQMASK_L_REAL = real.all;
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
    GH_PMU_IRR_IRQMASK_L_REAL_S real;
    real.bitc.value = m_pmu_irr_irqmask_l.bitc.value;
    *(volatile U32 *)REG_PMU_IRR_IRQMASK_L_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRR_getm_IrqMask_l_VALUE(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_IrqMask_l_VALUE] --> 0x%08x\n",
                        m_pmu_irr_irqmask_l.bitc.value);
    #endif
    return m_pmu_irr_irqmask_l.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRR_IrqMask_h (write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRR_set_IrqMask_h(U32 data)
{
    m_pmu_irr_irqmask_h.all = data;
    GH_PMU_IRR_IRQMASK_H_REAL_S real;
    GH_PMU_IRR_IRQMASK_H_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRR_IRQMASK_H_REAL = real.all;
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
    GH_PMU_IRR_IRQMASK_H_REAL_S real;
    real.bitc.value = m_pmu_irr_irqmask_h.bitc.value;
    *(volatile U32 *)REG_PMU_IRR_IRQMASK_H_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRR_getm_IrqMask_h_VALUE(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_IrqMask_h_VALUE] --> 0x%08x\n",
                        m_pmu_irr_irqmask_h.bitc.value);
    #endif
    return m_pmu_irr_irqmask_h.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRR_init(void)
{
    GH_PMU_IRR_set_Prog((U32)0x00000000);
    GH_PMU_IRR_set_PreScaler_l((U32)0x00000000);
    GH_PMU_IRR_set_PreScaler_h((U32)0x00000000);
    GH_PMU_IRR_set_IrqMask_l((U32)0x00000000);
    GH_PMU_IRR_set_IrqMask_h((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
    GH_PMU_IRR_get_Read();
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

