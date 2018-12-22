/******************************************************************************
**
** \file      gh_pmu_rtc.c
**
** \brief     PMU_RTC.
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
#include "gh_pmu_rtc.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
U8                                      m_pmu_rtc_pre_load_hour;
U8                                      m_pmu_rtc_pre_load_min;
U8                                      m_pmu_rtc_pre_load_sec;
GH_PMU_RTC_IRQ_CLEAR_S                  m_pmu_rtc_irq_clear;
U8                                      m_pmu_rtc_pre_load_day_l;
U8                                      m_pmu_rtc_pre_load_day_h;

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_SYS_CONFIG (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_PMU_RTC_set_SYS_CONFIG(U8 data)
{
    *(volatile U8 *)REG_PMU_RTC_SYS_CONFIG = data;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_SYS_CONFIG] <-- 0x%08x\n",
                        REG_PMU_RTC_SYS_CONFIG,data,data);
    #endif
}
U8   GH_PMU_RTC_get_SYS_CONFIG(void)
{
    U8 value = (*(volatile U8 *)REG_PMU_RTC_SYS_CONFIG);

    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_RTC_get_SYS_CONFIG] --> 0x%08x\n",
                        REG_PMU_RTC_SYS_CONFIG,value);
    #endif
    return value;
}
void GH_PMU_RTC_set_SYS_CONFIG_Enable(U8 data)
{
    GH_PMU_RTC_SYS_CONFIG_S d;
    d.all = *(volatile U8 *)REG_PMU_RTC_SYS_CONFIG;
    d.bitc.enable = data;
    *(volatile U8 *)REG_PMU_RTC_SYS_CONFIG = d.all;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_SYS_CONFIG_Enable] <-- 0x%08x\n",
                        REG_PMU_RTC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_PMU_RTC_get_SYS_CONFIG_Enable(void)
{
    GH_PMU_RTC_SYS_CONFIG_S tmp_value;
    U8 value = (*(volatile U8 *)REG_PMU_RTC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_RTC_get_SYS_CONFIG_Enable] --> 0x%08x\n",
                        REG_PMU_RTC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.enable;
}
void GH_PMU_RTC_set_SYS_CONFIG_Stop(U8 data)
{
    GH_PMU_RTC_SYS_CONFIG_S d;
    d.all = *(volatile U8 *)REG_PMU_RTC_SYS_CONFIG;
    d.bitc.stop = data;
    *(volatile U8 *)REG_PMU_RTC_SYS_CONFIG = d.all;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_SYS_CONFIG_Stop] <-- 0x%08x\n",
                        REG_PMU_RTC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_PMU_RTC_get_SYS_CONFIG_Stop(void)
{
    GH_PMU_RTC_SYS_CONFIG_S tmp_value;
    U8 value = (*(volatile U8 *)REG_PMU_RTC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_RTC_get_SYS_CONFIG_Stop] --> 0x%08x\n",
                        REG_PMU_RTC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.stop;
}
void GH_PMU_RTC_set_SYS_CONFIG_Pause(U8 data)
{
    GH_PMU_RTC_SYS_CONFIG_S d;
    d.all = *(volatile U8 *)REG_PMU_RTC_SYS_CONFIG;
    d.bitc.pause = data;
    *(volatile U8 *)REG_PMU_RTC_SYS_CONFIG = d.all;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_SYS_CONFIG_Pause] <-- 0x%08x\n",
                        REG_PMU_RTC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_PMU_RTC_get_SYS_CONFIG_Pause(void)
{
    GH_PMU_RTC_SYS_CONFIG_S tmp_value;
    U8 value = (*(volatile U8 *)REG_PMU_RTC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_RTC_get_SYS_CONFIG_Pause] --> 0x%08x\n",
                        REG_PMU_RTC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.pause;
}
void GH_PMU_RTC_set_SYS_CONFIG_IRQ(U8 data)
{
    GH_PMU_RTC_SYS_CONFIG_S d;
    d.all = *(volatile U8 *)REG_PMU_RTC_SYS_CONFIG;
    d.bitc.irq = data;
    *(volatile U8 *)REG_PMU_RTC_SYS_CONFIG = d.all;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_SYS_CONFIG_IRQ] <-- 0x%08x\n",
                        REG_PMU_RTC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_PMU_RTC_get_SYS_CONFIG_IRQ(void)
{
    GH_PMU_RTC_SYS_CONFIG_S tmp_value;
    U8 value = (*(volatile U8 *)REG_PMU_RTC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_RTC_get_SYS_CONFIG_IRQ] --> 0x%08x\n",
                        REG_PMU_RTC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.irq;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_P_SCALER_DIV0 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_PMU_RTC_set_P_SCALER_DIV0(U8 data)
{
    *(volatile U8 *)REG_PMU_RTC_P_SCALER_DIV0 = data;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_P_SCALER_DIV0] <-- 0x%08x\n",
                        REG_PMU_RTC_P_SCALER_DIV0,data,data);
    #endif
}
U8   GH_PMU_RTC_get_P_SCALER_DIV0(void)
{
    U8 value = (*(volatile U8 *)REG_PMU_RTC_P_SCALER_DIV0);

    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_RTC_get_P_SCALER_DIV0] --> 0x%08x\n",
                        REG_PMU_RTC_P_SCALER_DIV0,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_P_SCALER_DIV1 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_PMU_RTC_set_P_SCALER_DIV1(U8 data)
{
    *(volatile U8 *)REG_PMU_RTC_P_SCALER_DIV1 = data;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_P_SCALER_DIV1] <-- 0x%08x\n",
                        REG_PMU_RTC_P_SCALER_DIV1,data,data);
    #endif
}
U8   GH_PMU_RTC_get_P_SCALER_DIV1(void)
{
    U8 value = (*(volatile U8 *)REG_PMU_RTC_P_SCALER_DIV1);

    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_RTC_get_P_SCALER_DIV1] --> 0x%08x\n",
                        REG_PMU_RTC_P_SCALER_DIV1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_P_SCALER_DIV2 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_PMU_RTC_set_P_SCALER_DIV2(U8 data)
{
    *(volatile U8 *)REG_PMU_RTC_P_SCALER_DIV2 = data;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_P_SCALER_DIV2] <-- 0x%08x\n",
                        REG_PMU_RTC_P_SCALER_DIV2,data,data);
    #endif
}
U8   GH_PMU_RTC_get_P_SCALER_DIV2(void)
{
    U8 value = (*(volatile U8 *)REG_PMU_RTC_P_SCALER_DIV2);

    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_RTC_get_P_SCALER_DIV2] --> 0x%08x\n",
                        REG_PMU_RTC_P_SCALER_DIV2,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_P_SCALER_DIV3 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_PMU_RTC_set_P_SCALER_DIV3(U8 data)
{
    *(volatile U8 *)REG_PMU_RTC_P_SCALER_DIV3 = data;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_P_SCALER_DIV3] <-- 0x%08x\n",
                        REG_PMU_RTC_P_SCALER_DIV3,data,data);
    #endif
}
U8   GH_PMU_RTC_get_P_SCALER_DIV3(void)
{
    U8 value = (*(volatile U8 *)REG_PMU_RTC_P_SCALER_DIV3);

    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_RTC_get_P_SCALER_DIV3] --> 0x%08x\n",
                        REG_PMU_RTC_P_SCALER_DIV3,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_PRE_LOAD_HOUR (write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_RTC_set_PRE_LOAD_HOUR(U8 data)
{
    m_pmu_rtc_pre_load_hour = data;
    *(volatile U8 *)REG_PMU_RTC_PRE_LOAD_HOUR = data;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_PRE_LOAD_HOUR] <-- 0x%08x\n",
                        REG_PMU_RTC_PRE_LOAD_HOUR,data,data);
    #endif
}
U8   GH_PMU_RTC_getm_PRE_LOAD_HOUR(void)
{
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "[GH_PMU_RTC_getm_PRE_LOAD_HOUR] --> 0x%08x\n",
                        m_pmu_rtc_pre_load_hour);
    #endif
    return m_pmu_rtc_pre_load_hour;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_PRE_LOAD_MIN (write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_RTC_set_PRE_LOAD_MIN(U8 data)
{
    m_pmu_rtc_pre_load_min = data;
    *(volatile U8 *)REG_PMU_RTC_PRE_LOAD_MIN = data;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_PRE_LOAD_MIN] <-- 0x%08x\n",
                        REG_PMU_RTC_PRE_LOAD_MIN,data,data);
    #endif
}
U8   GH_PMU_RTC_getm_PRE_LOAD_MIN(void)
{
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "[GH_PMU_RTC_getm_PRE_LOAD_MIN] --> 0x%08x\n",
                        m_pmu_rtc_pre_load_min);
    #endif
    return m_pmu_rtc_pre_load_min;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_PRE_LOAD_SEC (write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_RTC_set_PRE_LOAD_SEC(U8 data)
{
    m_pmu_rtc_pre_load_sec = data;
    *(volatile U8 *)REG_PMU_RTC_PRE_LOAD_SEC = data;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_PRE_LOAD_SEC] <-- 0x%08x\n",
                        REG_PMU_RTC_PRE_LOAD_SEC,data,data);
    #endif
}
U8   GH_PMU_RTC_getm_PRE_LOAD_SEC(void)
{
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "[GH_PMU_RTC_getm_PRE_LOAD_SEC] --> 0x%08x\n",
                        m_pmu_rtc_pre_load_sec);
    #endif
    return m_pmu_rtc_pre_load_sec;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_IRQ_CLEAR (write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_RTC_set_IRQ_CLEAR(U8 data)
{
    m_pmu_rtc_irq_clear.all = data;
    *(volatile U8 *)REG_PMU_RTC_IRQ_CLEAR = data;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_IRQ_CLEAR] <-- 0x%08x\n",
                        REG_PMU_RTC_IRQ_CLEAR,data,data);
    #endif
}
U8   GH_PMU_RTC_getm_IRQ_CLEAR(void)
{
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "[GH_PMU_RTC_getm_IRQ_CLEAR] --> 0x%08x\n",
                        m_pmu_rtc_irq_clear.all);
    #endif
    return m_pmu_rtc_irq_clear.all;
}
void GH_PMU_RTC_set_IRQ_CLEAR_Clear(U8 data)
{
    m_pmu_rtc_irq_clear.bitc.clear = data;
    *(volatile U8 *)REG_PMU_RTC_IRQ_CLEAR = m_pmu_rtc_irq_clear.all;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_IRQ_CLEAR_Clear] <-- 0x%08x\n",
                        REG_PMU_RTC_IRQ_CLEAR,m_pmu_rtc_irq_clear.all,m_pmu_rtc_irq_clear.all);
    #endif
}
U8   GH_PMU_RTC_getm_IRQ_CLEAR_Clear(void)
{
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "[GH_PMU_RTC_getm_IRQ_CLEAR_Clear] --> 0x%08x\n",
                        m_pmu_rtc_irq_clear.bitc.clear);
    #endif
    return m_pmu_rtc_irq_clear.bitc.clear;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_PRE_LOAD_DAY_L (write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_RTC_set_PRE_LOAD_DAY_L(U8 data)
{
    m_pmu_rtc_pre_load_day_l = data;
    *(volatile U8 *)REG_PMU_RTC_PRE_LOAD_DAY_L = data;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_PRE_LOAD_DAY_L] <-- 0x%08x\n",
                        REG_PMU_RTC_PRE_LOAD_DAY_L,data,data);
    #endif
}
U8   GH_PMU_RTC_getm_PRE_LOAD_DAY_L(void)
{
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "[GH_PMU_RTC_getm_PRE_LOAD_DAY_L] --> 0x%08x\n",
                        m_pmu_rtc_pre_load_day_l);
    #endif
    return m_pmu_rtc_pre_load_day_l;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_PRE_LOAD_DAY_H (write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_PMU_RTC_set_PRE_LOAD_DAY_H(U8 data)
{
    m_pmu_rtc_pre_load_day_h = data;
    *(volatile U8 *)REG_PMU_RTC_PRE_LOAD_DAY_H = data;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_PRE_LOAD_DAY_H] <-- 0x%08x\n",
                        REG_PMU_RTC_PRE_LOAD_DAY_H,data,data);
    #endif
}
U8   GH_PMU_RTC_getm_PRE_LOAD_DAY_H(void)
{
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "[GH_PMU_RTC_getm_PRE_LOAD_DAY_H] --> 0x%08x\n",
                        m_pmu_rtc_pre_load_day_h);
    #endif
    return m_pmu_rtc_pre_load_day_h;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_IRQ_STATUS (read)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_PMU_RTC_get_IRQ_STATUS(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_RTC_IRQ_STATUS);

    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_RTC_get_IRQ_STATUS] --> 0x%08x\n",
                        REG_PMU_RTC_IRQ_STATUS,value);
    #endif
    return value;
}
U8   GH_PMU_RTC_get_IRQ_STATUS_Gen(void)
{
    GH_PMU_RTC_IRQ_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_RTC_IRQ_STATUS);

    tmp_value.all = value;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_RTC_get_IRQ_STATUS_Gen] --> 0x%08x\n",
                        REG_PMU_RTC_IRQ_STATUS,value);
    #endif
    return tmp_value.bitc.gen;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_SEC_VALUE (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_PMU_RTC_get_SEC_VALUE(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_RTC_SEC_VALUE);

    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_RTC_get_SEC_VALUE] --> 0x%08x\n",
                        REG_PMU_RTC_SEC_VALUE,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_MIN_VALUE (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_PMU_RTC_get_MIN_VALUE(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_RTC_MIN_VALUE);

    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_RTC_get_MIN_VALUE] --> 0x%08x\n",
                        REG_PMU_RTC_MIN_VALUE,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_HOUR_VALUE (read)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_PMU_RTC_get_HOUR_VALUE(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_RTC_HOUR_VALUE);

    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_RTC_get_HOUR_VALUE] --> 0x%08x\n",
                        REG_PMU_RTC_HOUR_VALUE,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_DAY_L_VALUE (read)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_PMU_RTC_get_DAY_L_VALUE(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_RTC_DAY_L_VALUE);

    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_RTC_get_DAY_L_VALUE] --> 0x%08x\n",
                        REG_PMU_RTC_DAY_L_VALUE,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_DAY_H_VALUE (read)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_PMU_RTC_get_DAY_H_VALUE(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_RTC_DAY_H_VALUE);

    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_RTC_get_DAY_H_VALUE] --> 0x%08x\n",
                        REG_PMU_RTC_DAY_H_VALUE,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_PMU_RTC_init(void)
{
    GH_PMU_RTC_set_SYS_CONFIG((U8)0x00000000);
    GH_PMU_RTC_set_IRQ_CLEAR((U8)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

