/******************************************************************************
**
** \file      gh_pmu_rtc.c
**
** \brief     PMU_RTC.
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
#include "gh_pmu_rtc.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_PMU_RTC_SYS_CONFIG_REAL                         FIO_ADDRESS(PMU_RTC,0x60080000) /* read/write */
#define REG_PMU_RTC_P_SCALER_DIV0_REAL                      FIO_ADDRESS(PMU_RTC,0x60080004) /* read/write */
#define REG_PMU_RTC_P_SCALER_DIV1_REAL                      FIO_ADDRESS(PMU_RTC,0x60080008) /* read/write */
#define REG_PMU_RTC_P_SCALER_DIV2_REAL                      FIO_ADDRESS(PMU_RTC,0x6008000C) /* read/write */
#define REG_PMU_RTC_P_SCALER_DIV3_REAL                      FIO_ADDRESS(PMU_RTC,0x60080010) /* read/write */
#define REG_PMU_RTC_PRE_LOAD_HOUR_REAL                      FIO_ADDRESS(PMU_RTC,0x60080014) /* write */
#define REG_PMU_RTC_PRE_LOAD_MIN_REAL                       FIO_ADDRESS(PMU_RTC,0x60080018) /* write */
#define REG_PMU_RTC_PRE_LOAD_SEC_REAL                       FIO_ADDRESS(PMU_RTC,0x6008001C) /* write */
#define REG_PMU_RTC_IRQ_CLEAR_REAL                          FIO_ADDRESS(PMU_RTC,0x60080020) /* write */
#define REG_PMU_RTC_PRE_LOAD_DAY_L_REAL                     FIO_ADDRESS(PMU_RTC,0x60080024) /* write */
#define REG_PMU_RTC_PRE_LOAD_DAY_H_REAL                     FIO_ADDRESS(PMU_RTC,0x60080028) /* write */
#define REG_PMU_RTC_IRQ_STATUS_REAL                         FIO_ADDRESS(PMU_RTC,0x60080068) /* read */
#define REG_PMU_RTC_SEC_VALUE_REAL                          FIO_ADDRESS(PMU_RTC,0x6008006c) /* read */
#define REG_PMU_RTC_MIN_VALUE_REAL                          FIO_ADDRESS(PMU_RTC,0x60080070) /* read */
#define REG_PMU_RTC_HOUR_VALUE_REAL                         FIO_ADDRESS(PMU_RTC,0x60080074) /* read */
#define REG_PMU_RTC_DAY_L_VALUE_REAL                        FIO_ADDRESS(PMU_RTC,0x60080078) /* read */
#define REG_PMU_RTC_DAY_H_VALUE_REAL                        FIO_ADDRESS(PMU_RTC,0x6008007c) /* read */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* PMU_RTC_SYS_CONFIG */
    U8 all;
    struct {
        U8 enable                       : 1;
        U8                              : 2;
        U8 stop                         : 1;
        U8 pause                        : 1;
        U8 irq                          : 1;
        U8                              : 2;
    } bitc;
} GH_PMU_RTC_SYS_CONFIG_REAL_S;

typedef union { /* PMU_RTC_IRQ_CLEAR */
    U8 all;
    struct {
        U8 clear                        : 1;
        U8                              : 7;
    } bitc;
} GH_PMU_RTC_IRQ_CLEAR_REAL_S;

typedef union { /* PMU_RTC_IRQ_STATUS */
    U32 all;
    struct {
        U32 gen                         : 1;
        U32                             : 31;
    } bitc;
} GH_PMU_RTC_IRQ_STATUS_REAL_S;


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
GH_INLINE void GH_PMU_RTC_set_SYS_CONFIG(U8 data)
{
    GH_PMU_RTC_SYS_CONFIG_REAL_S real;
    GH_PMU_RTC_SYS_CONFIG_S dummy;
    dummy.all = data ;
    real.bitc.enable = dummy.bitc.enable;
    real.bitc.stop = dummy.bitc.stop;
    real.bitc.pause = dummy.bitc.pause;
    real.bitc.irq = dummy.bitc.irq;
    *(volatile U8 *)REG_PMU_RTC_SYS_CONFIG_REAL = real.all;
}
GH_INLINE U8   GH_PMU_RTC_get_SYS_CONFIG(void)
{
    GH_PMU_RTC_SYS_CONFIG_REAL_S real;
    GH_PMU_RTC_SYS_CONFIG_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_PMU_RTC_SYS_CONFIG_REAL);

    dummy.bitc.enable = real.bitc.enable;
    dummy.bitc.stop = real.bitc.stop;
    dummy.bitc.pause = real.bitc.pause;
    dummy.bitc.irq = real.bitc.irq;
    return dummy.all;
}
GH_INLINE void GH_PMU_RTC_set_SYS_CONFIG_Enable(U8 data)
{
    GH_PMU_RTC_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U8 *)REG_PMU_RTC_SYS_CONFIG_REAL;
    d.bitc.enable = data;
    *(volatile U8 *)REG_PMU_RTC_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_PMU_RTC_get_SYS_CONFIG_Enable(void)
{
    GH_PMU_RTC_SYS_CONFIG_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_PMU_RTC_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.enable;
}
GH_INLINE void GH_PMU_RTC_set_SYS_CONFIG_Stop(U8 data)
{
    GH_PMU_RTC_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U8 *)REG_PMU_RTC_SYS_CONFIG_REAL;
    d.bitc.stop = data;
    *(volatile U8 *)REG_PMU_RTC_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_PMU_RTC_get_SYS_CONFIG_Stop(void)
{
    GH_PMU_RTC_SYS_CONFIG_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_PMU_RTC_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.stop;
}
GH_INLINE void GH_PMU_RTC_set_SYS_CONFIG_Pause(U8 data)
{
    GH_PMU_RTC_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U8 *)REG_PMU_RTC_SYS_CONFIG_REAL;
    d.bitc.pause = data;
    *(volatile U8 *)REG_PMU_RTC_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_PMU_RTC_get_SYS_CONFIG_Pause(void)
{
    GH_PMU_RTC_SYS_CONFIG_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_PMU_RTC_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pause;
}
GH_INLINE void GH_PMU_RTC_set_SYS_CONFIG_IRQ(U8 data)
{
    GH_PMU_RTC_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U8 *)REG_PMU_RTC_SYS_CONFIG_REAL;
    d.bitc.irq = data;
    *(volatile U8 *)REG_PMU_RTC_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_PMU_RTC_get_SYS_CONFIG_IRQ(void)
{
    GH_PMU_RTC_SYS_CONFIG_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_PMU_RTC_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.irq;
}

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_P_SCALER_DIV0 (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_RTC_set_P_SCALER_DIV0(U8 data)
{
    *(volatile U8 *)REG_PMU_RTC_P_SCALER_DIV0_REAL = data;
}
GH_INLINE U8   GH_PMU_RTC_get_P_SCALER_DIV0(void)
{
    U8 value = (*(volatile U8 *)REG_PMU_RTC_P_SCALER_DIV0_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_P_SCALER_DIV1 (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_RTC_set_P_SCALER_DIV1(U8 data)
{
    *(volatile U8 *)REG_PMU_RTC_P_SCALER_DIV1_REAL = data;
}
GH_INLINE U8   GH_PMU_RTC_get_P_SCALER_DIV1(void)
{
    U8 value = (*(volatile U8 *)REG_PMU_RTC_P_SCALER_DIV1_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_P_SCALER_DIV2 (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_RTC_set_P_SCALER_DIV2(U8 data)
{
    *(volatile U8 *)REG_PMU_RTC_P_SCALER_DIV2_REAL = data;
}
GH_INLINE U8   GH_PMU_RTC_get_P_SCALER_DIV2(void)
{
    U8 value = (*(volatile U8 *)REG_PMU_RTC_P_SCALER_DIV2_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_P_SCALER_DIV3 (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_RTC_set_P_SCALER_DIV3(U8 data)
{
    *(volatile U8 *)REG_PMU_RTC_P_SCALER_DIV3_REAL = data;
}
GH_INLINE U8   GH_PMU_RTC_get_P_SCALER_DIV3(void)
{
    U8 value = (*(volatile U8 *)REG_PMU_RTC_P_SCALER_DIV3_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_PRE_LOAD_HOUR (write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_RTC_set_PRE_LOAD_HOUR(U8 data)
{
    m_pmu_rtc_pre_load_hour = data;
    *(volatile U8 *)REG_PMU_RTC_PRE_LOAD_HOUR_REAL = data;
}
GH_INLINE U8   GH_PMU_RTC_getm_PRE_LOAD_HOUR(void)
{
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "[GH_PMU_RTC_getm_PRE_LOAD_HOUR] --> 0x%08x\n",
                        m_pmu_rtc_pre_load_hour);
    #endif
    return m_pmu_rtc_pre_load_hour;
}

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_PRE_LOAD_MIN (write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_RTC_set_PRE_LOAD_MIN(U8 data)
{
    m_pmu_rtc_pre_load_min = data;
    *(volatile U8 *)REG_PMU_RTC_PRE_LOAD_MIN_REAL = data;
}
GH_INLINE U8   GH_PMU_RTC_getm_PRE_LOAD_MIN(void)
{
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "[GH_PMU_RTC_getm_PRE_LOAD_MIN] --> 0x%08x\n",
                        m_pmu_rtc_pre_load_min);
    #endif
    return m_pmu_rtc_pre_load_min;
}

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_PRE_LOAD_SEC (write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_RTC_set_PRE_LOAD_SEC(U8 data)
{
    m_pmu_rtc_pre_load_sec = data;
    *(volatile U8 *)REG_PMU_RTC_PRE_LOAD_SEC_REAL = data;
}
GH_INLINE U8   GH_PMU_RTC_getm_PRE_LOAD_SEC(void)
{
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "[GH_PMU_RTC_getm_PRE_LOAD_SEC] --> 0x%08x\n",
                        m_pmu_rtc_pre_load_sec);
    #endif
    return m_pmu_rtc_pre_load_sec;
}

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_IRQ_CLEAR (write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_RTC_set_IRQ_CLEAR(U8 data)
{
    m_pmu_rtc_irq_clear.all = data;
    GH_PMU_RTC_IRQ_CLEAR_REAL_S real;
    GH_PMU_RTC_IRQ_CLEAR_S dummy;
    dummy.all = data ;
    real.bitc.clear = dummy.bitc.clear;
    *(volatile U8 *)REG_PMU_RTC_IRQ_CLEAR_REAL = real.all;
}
GH_INLINE U8   GH_PMU_RTC_getm_IRQ_CLEAR(void)
{
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "[GH_PMU_RTC_getm_IRQ_CLEAR] --> 0x%08x\n",
                        m_pmu_rtc_irq_clear.all);
    #endif
    return m_pmu_rtc_irq_clear.all;
}
GH_INLINE void GH_PMU_RTC_set_IRQ_CLEAR_Clear(U8 data)
{
    m_pmu_rtc_irq_clear.bitc.clear = data;
    GH_PMU_RTC_IRQ_CLEAR_REAL_S real;
    real.bitc.clear = m_pmu_rtc_irq_clear.bitc.clear;
    *(volatile U8 *)REG_PMU_RTC_IRQ_CLEAR_REAL = real.all;
}
GH_INLINE U8   GH_PMU_RTC_getm_IRQ_CLEAR_Clear(void)
{
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "[GH_PMU_RTC_getm_IRQ_CLEAR_Clear] --> 0x%08x\n",
                        m_pmu_rtc_irq_clear.bitc.clear);
    #endif
    return m_pmu_rtc_irq_clear.bitc.clear;
}

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_PRE_LOAD_DAY_L (write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_RTC_set_PRE_LOAD_DAY_L(U8 data)
{
    m_pmu_rtc_pre_load_day_l = data;
    *(volatile U8 *)REG_PMU_RTC_PRE_LOAD_DAY_L_REAL = data;
}
GH_INLINE U8   GH_PMU_RTC_getm_PRE_LOAD_DAY_L(void)
{
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "[GH_PMU_RTC_getm_PRE_LOAD_DAY_L] --> 0x%08x\n",
                        m_pmu_rtc_pre_load_day_l);
    #endif
    return m_pmu_rtc_pre_load_day_l;
}

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_PRE_LOAD_DAY_H (write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_RTC_set_PRE_LOAD_DAY_H(U8 data)
{
    m_pmu_rtc_pre_load_day_h = data;
    *(volatile U8 *)REG_PMU_RTC_PRE_LOAD_DAY_H_REAL = data;
}
GH_INLINE U8   GH_PMU_RTC_getm_PRE_LOAD_DAY_H(void)
{
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "[GH_PMU_RTC_getm_PRE_LOAD_DAY_H] --> 0x%08x\n",
                        m_pmu_rtc_pre_load_day_h);
    #endif
    return m_pmu_rtc_pre_load_day_h;
}

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_IRQ_STATUS (read)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_PMU_RTC_get_IRQ_STATUS(void)
{
    GH_PMU_RTC_IRQ_STATUS_REAL_S real;
    GH_PMU_RTC_IRQ_STATUS_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_PMU_RTC_IRQ_STATUS_REAL);

    dummy.bitc.gen = real.bitc.gen;
    return dummy.all;
}
GH_INLINE U8   GH_PMU_RTC_get_IRQ_STATUS_Gen(void)
{
    GH_PMU_RTC_IRQ_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_RTC_IRQ_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gen;
}

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_SEC_VALUE (read)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_PMU_RTC_get_SEC_VALUE(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_RTC_SEC_VALUE_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_MIN_VALUE (read)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_PMU_RTC_get_MIN_VALUE(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_RTC_MIN_VALUE_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_HOUR_VALUE (read)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_PMU_RTC_get_HOUR_VALUE(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_RTC_HOUR_VALUE_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_DAY_L_VALUE (read)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_PMU_RTC_get_DAY_L_VALUE(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_RTC_DAY_L_VALUE_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_DAY_H_VALUE (read)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_PMU_RTC_get_DAY_H_VALUE(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_RTC_DAY_H_VALUE_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_RTC_init(void)
{
    GH_PMU_RTC_set_SYS_CONFIG((U8)0x00000000);
    GH_PMU_RTC_set_IRQ_CLEAR((U8)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

