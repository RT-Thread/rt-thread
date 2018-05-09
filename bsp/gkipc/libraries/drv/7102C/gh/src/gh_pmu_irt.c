/******************************************************************************
**
** \file      gh_pmu_irt.c
**
** \brief     Infrared Transmitter.
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
#include "gh_pmu_irt.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_PMU_IRT_READ_S                       m_pmu_irt_read;
GH_PMU_IRT_TRANSMIT0_0_S                m_pmu_irt_transmit0_0;
GH_PMU_IRT_TRANSMIT0_1_S                m_pmu_irt_transmit0_1;
GH_PMU_IRT_TRANSMIT0_2_S                m_pmu_irt_transmit0_2;
GH_PMU_IRT_TRANSMIT0_3_S                m_pmu_irt_transmit0_3;
GH_PMU_IRT_TRANSMIT1_0_S                m_pmu_irt_transmit1_0;
GH_PMU_IRT_TRANSMIT1_1_S                m_pmu_irt_transmit1_1;
GH_PMU_IRT_TRANSMIT1_2_S                m_pmu_irt_transmit1_2;
GH_PMU_IRT_TRANSMIT1_3_S                m_pmu_irt_transmit1_3;
GH_PMU_IRT_TRANSMIT2_0_S                m_pmu_irt_transmit2_0;
GH_PMU_IRT_TRANSMIT2_1_S                m_pmu_irt_transmit2_1;
GH_PMU_IRT_TRANSMIT2_2_S                m_pmu_irt_transmit2_2;
GH_PMU_IRT_TRANSMIT2_3_S                m_pmu_irt_transmit2_3;
GH_PMU_IRT_TRANSMIT3_0_S                m_pmu_irt_transmit3_0;
GH_PMU_IRT_TRANSMIT3_1_S                m_pmu_irt_transmit3_1;
GH_PMU_IRT_TRANSMIT3_2_S                m_pmu_irt_transmit3_2;
GH_PMU_IRT_TRANSMIT3_3_S                m_pmu_irt_transmit3_3;
GH_PMU_IRT_SENT_CLOCK_L_S               m_pmu_irt_sent_clock_l;
GH_PMU_IRT_SENT_CLOCK_H_S               m_pmu_irt_sent_clock_h;
GH_PMU_IRT_SHIFT_CLOCK_S                m_pmu_irt_shift_clock;
GH_PMU_IRT_SENT_CONF_S                  m_pmu_irt_sent_conf;
GH_PMU_IRT_COMPVALUE_S                  m_pmu_irt_compvalue;
GH_PMU_IRT_START_S                      m_pmu_irt_start;

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Read (read/clear)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
U32  GH_PMU_IRT_get_Read(void)
{
    m_pmu_irt_read.all = *(volatile U32 *)REG_PMU_IRT_READ;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_IRT_get_Read] --> 0x%08x\n",
                        REG_PMU_IRT_READ,m_pmu_irt_read.all );
    #endif
    return m_pmu_irt_read.all;
}
U32  GH_PMU_IRT_getm_Read(void)
{
    return m_pmu_irt_read.all;
}
U8   GH_PMU_IRT_getm_Read_IRR_PULSE01(void)
{
    return m_pmu_irt_read.bitc.irr_pulse01;
}
U8   GH_PMU_IRT_getm_Read_NO_USED(void)
{
    return m_pmu_irt_read.bitc.no_used;
}
U8   GH_PMU_IRT_getm_Read_IRT_TRANSMIT0(void)
{
    return m_pmu_irt_read.bitc.irt_transmit0;
}
U8   GH_PMU_IRT_getm_Read_IRT_TRANSMIT1(void)
{
    return m_pmu_irt_read.bitc.irt_transmit1;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit0_0 (write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRT_set_Transmit0_0(U32 data)
{
    m_pmu_irt_transmit0_0.all = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT0_0 = data;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit0_0] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT0_0,data,data);
    #endif
}
U32  GH_PMU_IRT_getm_Transmit0_0(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit0_0] --> 0x%08x\n",
                        m_pmu_irt_transmit0_0.all);
    #endif
    return m_pmu_irt_transmit0_0.all;
}
void GH_PMU_IRT_set_Transmit0_0_VALUE(U8 data)
{
    m_pmu_irt_transmit0_0.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT0_0 = m_pmu_irt_transmit0_0.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit0_0_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT0_0,m_pmu_irt_transmit0_0.all,m_pmu_irt_transmit0_0.all);
    #endif
}
U8   GH_PMU_IRT_getm_Transmit0_0_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit0_0_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit0_0.bitc.value);
    #endif
    return m_pmu_irt_transmit0_0.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit0_1 (write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRT_set_Transmit0_1(U32 data)
{
    m_pmu_irt_transmit0_1.all = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT0_1 = data;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit0_1] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT0_1,data,data);
    #endif
}
U32  GH_PMU_IRT_getm_Transmit0_1(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit0_1] --> 0x%08x\n",
                        m_pmu_irt_transmit0_1.all);
    #endif
    return m_pmu_irt_transmit0_1.all;
}
void GH_PMU_IRT_set_Transmit0_1_VALUE(U8 data)
{
    m_pmu_irt_transmit0_1.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT0_1 = m_pmu_irt_transmit0_1.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit0_1_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT0_1,m_pmu_irt_transmit0_1.all,m_pmu_irt_transmit0_1.all);
    #endif
}
U8   GH_PMU_IRT_getm_Transmit0_1_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit0_1_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit0_1.bitc.value);
    #endif
    return m_pmu_irt_transmit0_1.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit0_2 (write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRT_set_Transmit0_2(U32 data)
{
    m_pmu_irt_transmit0_2.all = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT0_2 = data;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit0_2] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT0_2,data,data);
    #endif
}
U32  GH_PMU_IRT_getm_Transmit0_2(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit0_2] --> 0x%08x\n",
                        m_pmu_irt_transmit0_2.all);
    #endif
    return m_pmu_irt_transmit0_2.all;
}
void GH_PMU_IRT_set_Transmit0_2_VALUE(U8 data)
{
    m_pmu_irt_transmit0_2.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT0_2 = m_pmu_irt_transmit0_2.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit0_2_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT0_2,m_pmu_irt_transmit0_2.all,m_pmu_irt_transmit0_2.all);
    #endif
}
U8   GH_PMU_IRT_getm_Transmit0_2_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit0_2_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit0_2.bitc.value);
    #endif
    return m_pmu_irt_transmit0_2.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit0_3 (write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRT_set_Transmit0_3(U32 data)
{
    m_pmu_irt_transmit0_3.all = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT0_3 = data;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit0_3] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT0_3,data,data);
    #endif
}
U32  GH_PMU_IRT_getm_Transmit0_3(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit0_3] --> 0x%08x\n",
                        m_pmu_irt_transmit0_3.all);
    #endif
    return m_pmu_irt_transmit0_3.all;
}
void GH_PMU_IRT_set_Transmit0_3_VALUE(U8 data)
{
    m_pmu_irt_transmit0_3.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT0_3 = m_pmu_irt_transmit0_3.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit0_3_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT0_3,m_pmu_irt_transmit0_3.all,m_pmu_irt_transmit0_3.all);
    #endif
}
U8   GH_PMU_IRT_getm_Transmit0_3_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit0_3_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit0_3.bitc.value);
    #endif
    return m_pmu_irt_transmit0_3.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit1_0 (write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRT_set_Transmit1_0(U32 data)
{
    m_pmu_irt_transmit1_0.all = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT1_0 = data;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit1_0] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT1_0,data,data);
    #endif
}
U32  GH_PMU_IRT_getm_Transmit1_0(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit1_0] --> 0x%08x\n",
                        m_pmu_irt_transmit1_0.all);
    #endif
    return m_pmu_irt_transmit1_0.all;
}
void GH_PMU_IRT_set_Transmit1_0_VALUE(U8 data)
{
    m_pmu_irt_transmit1_0.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT1_0 = m_pmu_irt_transmit1_0.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit1_0_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT1_0,m_pmu_irt_transmit1_0.all,m_pmu_irt_transmit1_0.all);
    #endif
}
U8   GH_PMU_IRT_getm_Transmit1_0_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit1_0_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit1_0.bitc.value);
    #endif
    return m_pmu_irt_transmit1_0.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit1_1 (write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRT_set_Transmit1_1(U32 data)
{
    m_pmu_irt_transmit1_1.all = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT1_1 = data;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit1_1] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT1_1,data,data);
    #endif
}
U32  GH_PMU_IRT_getm_Transmit1_1(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit1_1] --> 0x%08x\n",
                        m_pmu_irt_transmit1_1.all);
    #endif
    return m_pmu_irt_transmit1_1.all;
}
void GH_PMU_IRT_set_Transmit1_1_VALUE(U8 data)
{
    m_pmu_irt_transmit1_1.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT1_1 = m_pmu_irt_transmit1_1.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit1_1_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT1_1,m_pmu_irt_transmit1_1.all,m_pmu_irt_transmit1_1.all);
    #endif
}
U8   GH_PMU_IRT_getm_Transmit1_1_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit1_1_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit1_1.bitc.value);
    #endif
    return m_pmu_irt_transmit1_1.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit1_2 (write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRT_set_Transmit1_2(U32 data)
{
    m_pmu_irt_transmit1_2.all = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT1_2 = data;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit1_2] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT1_2,data,data);
    #endif
}
U32  GH_PMU_IRT_getm_Transmit1_2(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit1_2] --> 0x%08x\n",
                        m_pmu_irt_transmit1_2.all);
    #endif
    return m_pmu_irt_transmit1_2.all;
}
void GH_PMU_IRT_set_Transmit1_2_VALUE(U8 data)
{
    m_pmu_irt_transmit1_2.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT1_2 = m_pmu_irt_transmit1_2.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit1_2_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT1_2,m_pmu_irt_transmit1_2.all,m_pmu_irt_transmit1_2.all);
    #endif
}
U8   GH_PMU_IRT_getm_Transmit1_2_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit1_2_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit1_2.bitc.value);
    #endif
    return m_pmu_irt_transmit1_2.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit1_3 (write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRT_set_Transmit1_3(U32 data)
{
    m_pmu_irt_transmit1_3.all = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT1_3 = data;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit1_3] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT1_3,data,data);
    #endif
}
U32  GH_PMU_IRT_getm_Transmit1_3(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit1_3] --> 0x%08x\n",
                        m_pmu_irt_transmit1_3.all);
    #endif
    return m_pmu_irt_transmit1_3.all;
}
void GH_PMU_IRT_set_Transmit1_3_VALUE(U8 data)
{
    m_pmu_irt_transmit1_3.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT1_3 = m_pmu_irt_transmit1_3.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit1_3_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT1_3,m_pmu_irt_transmit1_3.all,m_pmu_irt_transmit1_3.all);
    #endif
}
U8   GH_PMU_IRT_getm_Transmit1_3_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit1_3_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit1_3.bitc.value);
    #endif
    return m_pmu_irt_transmit1_3.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit2_0 (write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRT_set_Transmit2_0(U32 data)
{
    m_pmu_irt_transmit2_0.all = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT2_0 = data;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit2_0] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT2_0,data,data);
    #endif
}
U32  GH_PMU_IRT_getm_Transmit2_0(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit2_0] --> 0x%08x\n",
                        m_pmu_irt_transmit2_0.all);
    #endif
    return m_pmu_irt_transmit2_0.all;
}
void GH_PMU_IRT_set_Transmit2_0_VALUE(U8 data)
{
    m_pmu_irt_transmit2_0.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT2_0 = m_pmu_irt_transmit2_0.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit2_0_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT2_0,m_pmu_irt_transmit2_0.all,m_pmu_irt_transmit2_0.all);
    #endif
}
U8   GH_PMU_IRT_getm_Transmit2_0_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit2_0_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit2_0.bitc.value);
    #endif
    return m_pmu_irt_transmit2_0.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit2_1 (write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRT_set_Transmit2_1(U32 data)
{
    m_pmu_irt_transmit2_1.all = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT2_1 = data;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit2_1] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT2_1,data,data);
    #endif
}
U32  GH_PMU_IRT_getm_Transmit2_1(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit2_1] --> 0x%08x\n",
                        m_pmu_irt_transmit2_1.all);
    #endif
    return m_pmu_irt_transmit2_1.all;
}
void GH_PMU_IRT_set_Transmit2_1_VALUE(U8 data)
{
    m_pmu_irt_transmit2_1.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT2_1 = m_pmu_irt_transmit2_1.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit2_1_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT2_1,m_pmu_irt_transmit2_1.all,m_pmu_irt_transmit2_1.all);
    #endif
}
U8   GH_PMU_IRT_getm_Transmit2_1_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit2_1_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit2_1.bitc.value);
    #endif
    return m_pmu_irt_transmit2_1.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit2_2 (write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRT_set_Transmit2_2(U32 data)
{
    m_pmu_irt_transmit2_2.all = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT2_2 = data;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit2_2] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT2_2,data,data);
    #endif
}
U32  GH_PMU_IRT_getm_Transmit2_2(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit2_2] --> 0x%08x\n",
                        m_pmu_irt_transmit2_2.all);
    #endif
    return m_pmu_irt_transmit2_2.all;
}
void GH_PMU_IRT_set_Transmit2_2_VALUE(U8 data)
{
    m_pmu_irt_transmit2_2.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT2_2 = m_pmu_irt_transmit2_2.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit2_2_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT2_2,m_pmu_irt_transmit2_2.all,m_pmu_irt_transmit2_2.all);
    #endif
}
U8   GH_PMU_IRT_getm_Transmit2_2_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit2_2_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit2_2.bitc.value);
    #endif
    return m_pmu_irt_transmit2_2.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit2_3 (write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRT_set_Transmit2_3(U32 data)
{
    m_pmu_irt_transmit2_3.all = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT2_3 = data;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit2_3] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT2_3,data,data);
    #endif
}
U32  GH_PMU_IRT_getm_Transmit2_3(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit2_3] --> 0x%08x\n",
                        m_pmu_irt_transmit2_3.all);
    #endif
    return m_pmu_irt_transmit2_3.all;
}
void GH_PMU_IRT_set_Transmit2_3_VALUE(U8 data)
{
    m_pmu_irt_transmit2_3.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT2_3 = m_pmu_irt_transmit2_3.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit2_3_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT2_3,m_pmu_irt_transmit2_3.all,m_pmu_irt_transmit2_3.all);
    #endif
}
U8   GH_PMU_IRT_getm_Transmit2_3_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit2_3_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit2_3.bitc.value);
    #endif
    return m_pmu_irt_transmit2_3.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit3_0 (write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRT_set_Transmit3_0(U32 data)
{
    m_pmu_irt_transmit3_0.all = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT3_0 = data;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit3_0] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT3_0,data,data);
    #endif
}
U32  GH_PMU_IRT_getm_Transmit3_0(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit3_0] --> 0x%08x\n",
                        m_pmu_irt_transmit3_0.all);
    #endif
    return m_pmu_irt_transmit3_0.all;
}
void GH_PMU_IRT_set_Transmit3_0_VALUE(U8 data)
{
    m_pmu_irt_transmit3_0.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT3_0 = m_pmu_irt_transmit3_0.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit3_0_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT3_0,m_pmu_irt_transmit3_0.all,m_pmu_irt_transmit3_0.all);
    #endif
}
U8   GH_PMU_IRT_getm_Transmit3_0_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit3_0_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit3_0.bitc.value);
    #endif
    return m_pmu_irt_transmit3_0.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit3_1 (write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRT_set_Transmit3_1(U32 data)
{
    m_pmu_irt_transmit3_1.all = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT3_1 = data;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit3_1] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT3_1,data,data);
    #endif
}
U32  GH_PMU_IRT_getm_Transmit3_1(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit3_1] --> 0x%08x\n",
                        m_pmu_irt_transmit3_1.all);
    #endif
    return m_pmu_irt_transmit3_1.all;
}
void GH_PMU_IRT_set_Transmit3_1_VALUE(U8 data)
{
    m_pmu_irt_transmit3_1.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT3_1 = m_pmu_irt_transmit3_1.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit3_1_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT3_1,m_pmu_irt_transmit3_1.all,m_pmu_irt_transmit3_1.all);
    #endif
}
U8   GH_PMU_IRT_getm_Transmit3_1_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit3_1_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit3_1.bitc.value);
    #endif
    return m_pmu_irt_transmit3_1.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit3_2 (write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRT_set_Transmit3_2(U32 data)
{
    m_pmu_irt_transmit3_2.all = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT3_2 = data;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit3_2] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT3_2,data,data);
    #endif
}
U32  GH_PMU_IRT_getm_Transmit3_2(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit3_2] --> 0x%08x\n",
                        m_pmu_irt_transmit3_2.all);
    #endif
    return m_pmu_irt_transmit3_2.all;
}
void GH_PMU_IRT_set_Transmit3_2_VALUE(U8 data)
{
    m_pmu_irt_transmit3_2.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT3_2 = m_pmu_irt_transmit3_2.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit3_2_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT3_2,m_pmu_irt_transmit3_2.all,m_pmu_irt_transmit3_2.all);
    #endif
}
U8   GH_PMU_IRT_getm_Transmit3_2_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit3_2_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit3_2.bitc.value);
    #endif
    return m_pmu_irt_transmit3_2.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit3_3 (write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRT_set_Transmit3_3(U32 data)
{
    m_pmu_irt_transmit3_3.all = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT3_3 = data;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit3_3] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT3_3,data,data);
    #endif
}
U32  GH_PMU_IRT_getm_Transmit3_3(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit3_3] --> 0x%08x\n",
                        m_pmu_irt_transmit3_3.all);
    #endif
    return m_pmu_irt_transmit3_3.all;
}
void GH_PMU_IRT_set_Transmit3_3_VALUE(U8 data)
{
    m_pmu_irt_transmit3_3.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT3_3 = m_pmu_irt_transmit3_3.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Transmit3_3_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRT_TRANSMIT3_3,m_pmu_irt_transmit3_3.all,m_pmu_irt_transmit3_3.all);
    #endif
}
U8   GH_PMU_IRT_getm_Transmit3_3_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit3_3_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit3_3.bitc.value);
    #endif
    return m_pmu_irt_transmit3_3.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Sent_Clock_l (write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRT_set_Sent_Clock_l(U32 data)
{
    m_pmu_irt_sent_clock_l.all = data;
    *(volatile U32 *)REG_PMU_IRT_SENT_CLOCK_L = data;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Sent_Clock_l] <-- 0x%08x\n",
                        REG_PMU_IRT_SENT_CLOCK_L,data,data);
    #endif
}
U32  GH_PMU_IRT_getm_Sent_Clock_l(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Sent_Clock_l] --> 0x%08x\n",
                        m_pmu_irt_sent_clock_l.all);
    #endif
    return m_pmu_irt_sent_clock_l.all;
}
void GH_PMU_IRT_set_Sent_Clock_l_VALUE(U8 data)
{
    m_pmu_irt_sent_clock_l.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRT_SENT_CLOCK_L = m_pmu_irt_sent_clock_l.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Sent_Clock_l_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRT_SENT_CLOCK_L,m_pmu_irt_sent_clock_l.all,m_pmu_irt_sent_clock_l.all);
    #endif
}
U8   GH_PMU_IRT_getm_Sent_Clock_l_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Sent_Clock_l_VALUE] --> 0x%08x\n",
                        m_pmu_irt_sent_clock_l.bitc.value);
    #endif
    return m_pmu_irt_sent_clock_l.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Sent_Clock_h (write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRT_set_Sent_Clock_h(U32 data)
{
    m_pmu_irt_sent_clock_h.all = data;
    *(volatile U32 *)REG_PMU_IRT_SENT_CLOCK_H = data;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Sent_Clock_h] <-- 0x%08x\n",
                        REG_PMU_IRT_SENT_CLOCK_H,data,data);
    #endif
}
U32  GH_PMU_IRT_getm_Sent_Clock_h(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Sent_Clock_h] --> 0x%08x\n",
                        m_pmu_irt_sent_clock_h.all);
    #endif
    return m_pmu_irt_sent_clock_h.all;
}
void GH_PMU_IRT_set_Sent_Clock_h_VALUE(U8 data)
{
    m_pmu_irt_sent_clock_h.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRT_SENT_CLOCK_H = m_pmu_irt_sent_clock_h.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Sent_Clock_h_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRT_SENT_CLOCK_H,m_pmu_irt_sent_clock_h.all,m_pmu_irt_sent_clock_h.all);
    #endif
}
U8   GH_PMU_IRT_getm_Sent_Clock_h_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Sent_Clock_h_VALUE] --> 0x%08x\n",
                        m_pmu_irt_sent_clock_h.bitc.value);
    #endif
    return m_pmu_irt_sent_clock_h.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Shift_Clock (write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRT_set_Shift_Clock(U32 data)
{
    m_pmu_irt_shift_clock.all = data;
    *(volatile U32 *)REG_PMU_IRT_SHIFT_CLOCK = data;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Shift_Clock] <-- 0x%08x\n",
                        REG_PMU_IRT_SHIFT_CLOCK,data,data);
    #endif
}
U32  GH_PMU_IRT_getm_Shift_Clock(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Shift_Clock] --> 0x%08x\n",
                        m_pmu_irt_shift_clock.all);
    #endif
    return m_pmu_irt_shift_clock.all;
}
void GH_PMU_IRT_set_Shift_Clock_VALUE(U8 data)
{
    m_pmu_irt_shift_clock.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRT_SHIFT_CLOCK = m_pmu_irt_shift_clock.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Shift_Clock_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRT_SHIFT_CLOCK,m_pmu_irt_shift_clock.all,m_pmu_irt_shift_clock.all);
    #endif
}
U8   GH_PMU_IRT_getm_Shift_Clock_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Shift_Clock_VALUE] --> 0x%08x\n",
                        m_pmu_irt_shift_clock.bitc.value);
    #endif
    return m_pmu_irt_shift_clock.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Sent_Conf (write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRT_set_Sent_Conf(U32 data)
{
    m_pmu_irt_sent_conf.all = data;
    *(volatile U32 *)REG_PMU_IRT_SENT_CONF = data;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Sent_Conf] <-- 0x%08x\n",
                        REG_PMU_IRT_SENT_CONF,data,data);
    #endif
}
U32  GH_PMU_IRT_getm_Sent_Conf(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Sent_Conf] --> 0x%08x\n",
                        m_pmu_irt_sent_conf.all);
    #endif
    return m_pmu_irt_sent_conf.all;
}
void GH_PMU_IRT_set_Sent_Conf_EN_TX_IRQ(U8 data)
{
    m_pmu_irt_sent_conf.bitc.en_tx_irq = data;
    *(volatile U32 *)REG_PMU_IRT_SENT_CONF = m_pmu_irt_sent_conf.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Sent_Conf_EN_TX_IRQ] <-- 0x%08x\n",
                        REG_PMU_IRT_SENT_CONF,m_pmu_irt_sent_conf.all,m_pmu_irt_sent_conf.all);
    #endif
}
U8   GH_PMU_IRT_getm_Sent_Conf_EN_TX_IRQ(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Sent_Conf_EN_TX_IRQ] --> 0x%08x\n",
                        m_pmu_irt_sent_conf.bitc.en_tx_irq);
    #endif
    return m_pmu_irt_sent_conf.bitc.en_tx_irq;
}
void GH_PMU_IRT_set_Sent_Conf_MODE(U8 data)
{
    m_pmu_irt_sent_conf.bitc.mode = data;
    *(volatile U32 *)REG_PMU_IRT_SENT_CONF = m_pmu_irt_sent_conf.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Sent_Conf_MODE] <-- 0x%08x\n",
                        REG_PMU_IRT_SENT_CONF,m_pmu_irt_sent_conf.all,m_pmu_irt_sent_conf.all);
    #endif
}
U8   GH_PMU_IRT_getm_Sent_Conf_MODE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Sent_Conf_MODE] --> 0x%08x\n",
                        m_pmu_irt_sent_conf.bitc.mode);
    #endif
    return m_pmu_irt_sent_conf.bitc.mode;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Compvalue (write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRT_set_Compvalue(U32 data)
{
    m_pmu_irt_compvalue.all = data;
    *(volatile U32 *)REG_PMU_IRT_COMPVALUE = data;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Compvalue] <-- 0x%08x\n",
                        REG_PMU_IRT_COMPVALUE,data,data);
    #endif
}
U32  GH_PMU_IRT_getm_Compvalue(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Compvalue] --> 0x%08x\n",
                        m_pmu_irt_compvalue.all);
    #endif
    return m_pmu_irt_compvalue.all;
}
void GH_PMU_IRT_set_Compvalue_VALUE(U8 data)
{
    m_pmu_irt_compvalue.bitc.value = data;
    *(volatile U32 *)REG_PMU_IRT_COMPVALUE = m_pmu_irt_compvalue.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Compvalue_VALUE] <-- 0x%08x\n",
                        REG_PMU_IRT_COMPVALUE,m_pmu_irt_compvalue.all,m_pmu_irt_compvalue.all);
    #endif
}
U8   GH_PMU_IRT_getm_Compvalue_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Compvalue_VALUE] --> 0x%08x\n",
                        m_pmu_irt_compvalue.bitc.value);
    #endif
    return m_pmu_irt_compvalue.bitc.value;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Start (write)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_IRT_set_Start(U32 data)
{
    m_pmu_irt_start.all = data;
    *(volatile U32 *)REG_PMU_IRT_START = data;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Start] <-- 0x%08x\n",
                        REG_PMU_IRT_START,data,data);
    #endif
}
U32  GH_PMU_IRT_getm_Start(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Start] --> 0x%08x\n",
                        m_pmu_irt_start.all);
    #endif
    return m_pmu_irt_start.all;
}
void GH_PMU_IRT_set_Start_START_TX(U8 data)
{
    m_pmu_irt_start.bitc.start_tx = data;
    *(volatile U32 *)REG_PMU_IRT_START = m_pmu_irt_start.all;
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_IRT_set_Start_START_TX] <-- 0x%08x\n",
                        REG_PMU_IRT_START,m_pmu_irt_start.all,m_pmu_irt_start.all);
    #endif
}
U8   GH_PMU_IRT_getm_Start_START_TX(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Start_START_TX] --> 0x%08x\n",
                        m_pmu_irt_start.bitc.start_tx);
    #endif
    return m_pmu_irt_start.bitc.start_tx;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_PMU_IRT_init(void)
{
    GH_PMU_IRT_set_Transmit0_0((U32)0x00000000);
    GH_PMU_IRT_set_Transmit0_1((U32)0x00000000);
    GH_PMU_IRT_set_Transmit0_2((U32)0x00000000);
    GH_PMU_IRT_set_Transmit0_3((U32)0x00000000);
    GH_PMU_IRT_set_Transmit1_0((U32)0x00000000);
    GH_PMU_IRT_set_Transmit1_1((U32)0x00000000);
    GH_PMU_IRT_set_Transmit1_2((U32)0x00000000);
    GH_PMU_IRT_set_Transmit1_3((U32)0x00000000);
    GH_PMU_IRT_set_Transmit2_0((U32)0x00000000);
    GH_PMU_IRT_set_Transmit2_1((U32)0x00000000);
    GH_PMU_IRT_set_Transmit2_2((U32)0x00000000);
    GH_PMU_IRT_set_Transmit2_3((U32)0x00000000);
    GH_PMU_IRT_set_Transmit3_0((U32)0x00000000);
    GH_PMU_IRT_set_Transmit3_1((U32)0x00000000);
    GH_PMU_IRT_set_Transmit3_2((U32)0x00000000);
    GH_PMU_IRT_set_Transmit3_3((U32)0x00000000);
    GH_PMU_IRT_set_Sent_Clock_l((U32)0x00000000);
    GH_PMU_IRT_set_Sent_Clock_h((U32)0x00000000);
    GH_PMU_IRT_set_Shift_Clock((U32)0x00000000);
    GH_PMU_IRT_set_Sent_Conf((U32)0x00000000);
    GH_PMU_IRT_set_Compvalue((U32)0x00000000);
    GH_PMU_IRT_set_Start((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
    GH_PMU_IRT_get_Read();
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

