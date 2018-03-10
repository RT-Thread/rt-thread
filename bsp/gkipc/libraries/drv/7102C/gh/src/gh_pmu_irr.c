/******************************************************************************
**
** \file      gh_pmu_irr.c
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
#include "gh_pmu_irr.h"

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
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRR_set_Prog(U32 data)
{
    m_pmu_irr_prog.all = data;
    *(volatile U32 *)REG_PMU_IRR_PROG = data;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_Prog] <-- 0x%08x\n",
                        REG_PMU_IRR_PROG,data,data);
    #endif
}
U32  GH_PMU_IRR_getm_Prog(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_Prog] --> 0x%08x\n",
                        m_pmu_irr_prog.all);
    #endif
    return m_pmu_irr_prog.all;
}
void GH_PMU_IRR_set_Prog_RX(U8 data)
{
    m_pmu_irr_prog.bitc.rx = data;
    *(volatile U32 *)REG_PMU_IRR_PROG = m_pmu_irr_prog.all;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_Prog_RX] <-- 0x%08x\n",
                        REG_PMU_IRR_PROG,m_pmu_irr_prog.all,m_pmu_irr_prog.all);
    #endif
}
U8   GH_PMU_IRR_getm_Prog_RX(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_Prog_RX] --> 0x%08x\n",
                        m_pmu_irr_prog.bitc.rx);
    #endif
    return m_pmu_irr_prog.bitc.rx;
}
void GH_PMU_IRR_set_Prog_RISING_EDGE(U8 data)
{
    m_pmu_irr_prog.bitc.rising_edge = data;
    *(volatile U32 *)REG_PMU_IRR_PROG = m_pmu_irr_prog.all;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_Prog_RISING_EDGE] <-- 0x%08x\n",
                        REG_PMU_IRR_PROG,m_pmu_irr_prog.all,m_pmu_irr_prog.all);
    #endif
}
U8   GH_PMU_IRR_getm_Prog_RISING_EDGE(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_Prog_RISING_EDGE] --> 0x%08x\n",
                        m_pmu_irr_prog.bitc.rising_edge);
    #endif
    return m_pmu_irr_prog.bitc.rising_edge;
}
void GH_PMU_IRR_set_Prog_FALLING_EDGE(U8 data)
{
    m_pmu_irr_prog.bitc.falling_edge = data;
    *(volatile U32 *)REG_PMU_IRR_PROG = m_pmu_irr_prog.all;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_Prog_FALLING_EDGE] <-- 0x%08x\n",
                        REG_PMU_IRR_PROG,m_pmu_irr_prog.all,m_pmu_irr_prog.all);
    #endif
}
U8   GH_PMU_IRR_getm_Prog_FALLING_EDGE(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_Prog_FALLING_EDGE] --> 0x%08x\n",
                        m_pmu_irr_prog.bitc.falling_edge);
    #endif
    return m_pmu_irr_prog.bitc.falling_edge;
}
void GH_PMU_IRR_set_Prog_RESTARTS(U8 data)
{
    m_pmu_irr_prog.bitc.restarts = data;
    *(volatile U32 *)REG_PMU_IRR_PROG = m_pmu_irr_prog.all;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_Prog_RESTARTS] <-- 0x%08x\n",
                        REG_PMU_IRR_PROG,m_pmu_irr_prog.all,m_pmu_irr_prog.all);
    #endif
}
U8   GH_PMU_IRR_getm_Prog_RESTARTS(void)
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
void GH_PMU_IRR_set_PreScaler_l(U32 data)
{
    m_pmu_irr_prescaler_l.all = data;
    *(volatile U32 *)REG_PMU_IRR_PRESCALER_L = data;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_PreScaler_l] <-- 0x%08x\n",
                        REG_PMU_IRR_PRESCALER_L,data,data);
    #endif
}
U32  GH_PMU_IRR_getm_PreScaler_l(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_PreScaler_l] --> 0x%08x\n",
                        m_pmu_irr_prescaler_l.all);
    #endif
    return m_pmu_irr_prescaler_l.all;
}
void GH_PMU_IRR_set_PreScaler_l_VALUE(U8 data)
{
    m_pmu_irr_prescaler_l.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRR_PRESCALER_L = m_pmu_irr_prescaler_l.all;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_PreScaler_l_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRR_PRESCALER_L,m_pmu_irr_prescaler_l.all,m_pmu_irr_prescaler_l.all);
    #endif
}
U8   GH_PMU_IRR_getm_PreScaler_l_VALUE(void)
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
void GH_PMU_IRR_set_PreScaler_h(U32 data)
{
    m_pmu_irr_prescaler_h.all = data;
    *(volatile U32 *)REG_PMU_IRR_PRESCALER_H = data;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_PreScaler_h] <-- 0x%08x\n",
                        REG_PMU_IRR_PRESCALER_H,data,data);
    #endif
}
U32  GH_PMU_IRR_getm_PreScaler_h(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_PreScaler_h] --> 0x%08x\n",
                        m_pmu_irr_prescaler_h.all);
    #endif
    return m_pmu_irr_prescaler_h.all;
}
void GH_PMU_IRR_set_PreScaler_h_VALUE(U8 data)
{
    m_pmu_irr_prescaler_h.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRR_PRESCALER_H = m_pmu_irr_prescaler_h.all;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_PreScaler_h_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRR_PRESCALER_H,m_pmu_irr_prescaler_h.all,m_pmu_irr_prescaler_h.all);
    #endif
}
U8   GH_PMU_IRR_getm_PreScaler_h_VALUE(void)
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
U32  GH_PMU_IRR_get_Read(void)
{
    m_pmu_irr_read.all = *(volatile U32 *)REG_PMU_IRR_READ;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_IRR_get_Read] --> 0x%08x\n",
                        REG_PMU_IRR_READ,m_pmu_irr_read.all );
    #endif
    return m_pmu_irr_read.all;
}
U32  GH_PMU_IRR_getm_Read(void)
{
    return m_pmu_irr_read.all;
}
U8   GH_PMU_IRR_getm_Read_PULSE27(void)
{
    return m_pmu_irr_read.bitc.pulse27;
}
U8   GH_PMU_IRR_getm_Read_EDGE(void)
{
    return m_pmu_irr_read.bitc.edge;
}
U8   GH_PMU_IRR_getm_Read_VALID(void)
{
    return m_pmu_irr_read.bitc.valid;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRR_IrqMask_l (write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRR_set_IrqMask_l(U32 data)
{
    m_pmu_irr_irqmask_l.all = data;
    *(volatile U32 *)REG_PMU_IRR_IRQMASK_L = data;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_IrqMask_l] <-- 0x%08x\n",
                        REG_PMU_IRR_IRQMASK_L,data,data);
    #endif
}
U32  GH_PMU_IRR_getm_IrqMask_l(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_IrqMask_l] --> 0x%08x\n",
                        m_pmu_irr_irqmask_l.all);
    #endif
    return m_pmu_irr_irqmask_l.all;
}
void GH_PMU_IRR_set_IrqMask_l_VALUE(U8 data)
{
    m_pmu_irr_irqmask_l.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRR_IRQMASK_L = m_pmu_irr_irqmask_l.all;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_IrqMask_l_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRR_IRQMASK_L,m_pmu_irr_irqmask_l.all,m_pmu_irr_irqmask_l.all);
    #endif
}
U8   GH_PMU_IRR_getm_IrqMask_l_VALUE(void)
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
void GH_PMU_IRR_set_IrqMask_h(U32 data)
{
    m_pmu_irr_irqmask_h.all = data;
    *(volatile U32 *)REG_PMU_IRR_IRQMASK_H = data;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_IrqMask_h] <-- 0x%08x\n",
                        REG_PMU_IRR_IRQMASK_H,data,data);
    #endif
}
U32  GH_PMU_IRR_getm_IrqMask_h(void)
{
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRR_getm_IrqMask_h] --> 0x%08x\n",
                        m_pmu_irr_irqmask_h.all);
    #endif
    return m_pmu_irr_irqmask_h.all;
}
void GH_PMU_IRR_set_IrqMask_h_VALUE(U8 data)
{
    m_pmu_irr_irqmask_h.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRR_IRQMASK_H = m_pmu_irr_irqmask_h.all;
    #if GH_PMU_IRR_ENABLE_DEBUG_PRINT
    GH_PMU_IRR_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRR_set_IrqMask_h_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRR_IRQMASK_H,m_pmu_irr_irqmask_h.all,m_pmu_irr_irqmask_h.all);
    #endif
}
U8   GH_PMU_IRR_getm_IrqMask_h_VALUE(void)
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
void GH_PMU_IRR_init(void)
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

