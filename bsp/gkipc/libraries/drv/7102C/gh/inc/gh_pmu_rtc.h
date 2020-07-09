/*!
*******************************************************************************
**
** \file      gh_pmu_rtc.h
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
#ifndef _GH_PMU_RTC_H
#define _GH_PMU_RTC_H

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

#define GH_PMU_RTC_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_PMU_RTC_DEBUG_PRINT_FUNCTION printk
#else
#define GH_PMU_RTC_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_PMU_RTC_ENABLE_DEBUG_PRINT
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
#define REG_PMU_RTC_SYS_CONFIG                              FIO_ADDRESS(PMU_RTC,0x90080000) /* read/write */
#define REG_PMU_RTC_P_SCALER_DIV0                           FIO_ADDRESS(PMU_RTC,0x90080004) /* read/write */
#define REG_PMU_RTC_P_SCALER_DIV1                           FIO_ADDRESS(PMU_RTC,0x90080008) /* read/write */
#define REG_PMU_RTC_P_SCALER_DIV2                           FIO_ADDRESS(PMU_RTC,0x9008000C) /* read/write */
#define REG_PMU_RTC_P_SCALER_DIV3                           FIO_ADDRESS(PMU_RTC,0x90080010) /* read/write */
#define REG_PMU_RTC_PRE_LOAD_HOUR                           FIO_ADDRESS(PMU_RTC,0x90080014) /* write */
#define REG_PMU_RTC_PRE_LOAD_MIN                            FIO_ADDRESS(PMU_RTC,0x90080018) /* write */
#define REG_PMU_RTC_PRE_LOAD_SEC                            FIO_ADDRESS(PMU_RTC,0x9008001C) /* write */
#define REG_PMU_RTC_IRQ_CLEAR                               FIO_ADDRESS(PMU_RTC,0x90080020) /* write */
#define REG_PMU_RTC_PRE_LOAD_DAY_L                          FIO_ADDRESS(PMU_RTC,0x90080024) /* write */
#define REG_PMU_RTC_PRE_LOAD_DAY_H                          FIO_ADDRESS(PMU_RTC,0x90080028) /* write */
#define REG_PMU_RTC_IRQ_STATUS                              FIO_ADDRESS(PMU_RTC,0x90080068) /* read */
#define REG_PMU_RTC_SEC_VALUE                               FIO_ADDRESS(PMU_RTC,0x9008006c) /* read */
#define REG_PMU_RTC_MIN_VALUE                               FIO_ADDRESS(PMU_RTC,0x90080070) /* read */
#define REG_PMU_RTC_HOUR_VALUE                              FIO_ADDRESS(PMU_RTC,0x90080074) /* read */
#define REG_PMU_RTC_DAY_L_VALUE                             FIO_ADDRESS(PMU_RTC,0x90080078) /* read */
#define REG_PMU_RTC_DAY_H_VALUE                             FIO_ADDRESS(PMU_RTC,0x9008007c) /* read */

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
} GH_PMU_RTC_SYS_CONFIG_S;

typedef union { /* PMU_RTC_IRQ_CLEAR */
    U8 all;
    struct {
        U8 clear                        : 1;
        U8                              : 7;
    } bitc;
} GH_PMU_RTC_IRQ_CLEAR_S;

typedef union { /* PMU_RTC_IRQ_STATUS */
    U32 all;
    struct {
        U32 gen                         : 1;
        U32                             : 31;
    } bitc;
} GH_PMU_RTC_IRQ_STATUS_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern U8                                      m_pmu_rtc_pre_load_hour;
extern U8                                      m_pmu_rtc_pre_load_min;
extern U8                                      m_pmu_rtc_pre_load_sec;
extern GH_PMU_RTC_IRQ_CLEAR_S                  m_pmu_rtc_irq_clear;
extern U8                                      m_pmu_rtc_pre_load_day_l;
extern U8                                      m_pmu_rtc_pre_load_day_h;

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_SYS_CONFIG (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_RTC_SYS_CONFIG'. */
void GH_PMU_RTC_set_SYS_CONFIG(U8 data);
/*! \brief Reads the register 'PMU_RTC_SYS_CONFIG'. */
U8   GH_PMU_RTC_get_SYS_CONFIG(void);
/*! \brief Writes the bit group 'Enable' of register 'PMU_RTC_SYS_CONFIG'. */
void GH_PMU_RTC_set_SYS_CONFIG_Enable(U8 data);
/*! \brief Reads the bit group 'Enable' of register 'PMU_RTC_SYS_CONFIG'. */
U8   GH_PMU_RTC_get_SYS_CONFIG_Enable(void);
/*! \brief Writes the bit group 'Stop' of register 'PMU_RTC_SYS_CONFIG'. */
void GH_PMU_RTC_set_SYS_CONFIG_Stop(U8 data);
/*! \brief Reads the bit group 'Stop' of register 'PMU_RTC_SYS_CONFIG'. */
U8   GH_PMU_RTC_get_SYS_CONFIG_Stop(void);
/*! \brief Writes the bit group 'Pause' of register 'PMU_RTC_SYS_CONFIG'. */
void GH_PMU_RTC_set_SYS_CONFIG_Pause(U8 data);
/*! \brief Reads the bit group 'Pause' of register 'PMU_RTC_SYS_CONFIG'. */
U8   GH_PMU_RTC_get_SYS_CONFIG_Pause(void);
/*! \brief Writes the bit group 'IRQ' of register 'PMU_RTC_SYS_CONFIG'. */
void GH_PMU_RTC_set_SYS_CONFIG_IRQ(U8 data);
/*! \brief Reads the bit group 'IRQ' of register 'PMU_RTC_SYS_CONFIG'. */
U8   GH_PMU_RTC_get_SYS_CONFIG_IRQ(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_RTC_set_SYS_CONFIG(U8 data)
{
    *(volatile U8 *)REG_PMU_RTC_SYS_CONFIG = data;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_SYS_CONFIG] <-- 0x%08x\n",
                        REG_PMU_RTC_SYS_CONFIG,data,data);
    #endif
}
GH_INLINE U8   GH_PMU_RTC_get_SYS_CONFIG(void)
{
    U8 value = (*(volatile U8 *)REG_PMU_RTC_SYS_CONFIG);

    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_RTC_get_SYS_CONFIG] --> 0x%08x\n",
                        REG_PMU_RTC_SYS_CONFIG,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_RTC_set_SYS_CONFIG_Enable(U8 data)
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
GH_INLINE U8   GH_PMU_RTC_get_SYS_CONFIG_Enable(void)
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
GH_INLINE void GH_PMU_RTC_set_SYS_CONFIG_Stop(U8 data)
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
GH_INLINE U8   GH_PMU_RTC_get_SYS_CONFIG_Stop(void)
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
GH_INLINE void GH_PMU_RTC_set_SYS_CONFIG_Pause(U8 data)
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
GH_INLINE U8   GH_PMU_RTC_get_SYS_CONFIG_Pause(void)
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
GH_INLINE void GH_PMU_RTC_set_SYS_CONFIG_IRQ(U8 data)
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
GH_INLINE U8   GH_PMU_RTC_get_SYS_CONFIG_IRQ(void)
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
/*! \brief Writes the register 'PMU_RTC_P_SCALER_DIV0'. */
void GH_PMU_RTC_set_P_SCALER_DIV0(U8 data);
/*! \brief Reads the register 'PMU_RTC_P_SCALER_DIV0'. */
U8   GH_PMU_RTC_get_P_SCALER_DIV0(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_RTC_set_P_SCALER_DIV0(U8 data)
{
    *(volatile U8 *)REG_PMU_RTC_P_SCALER_DIV0 = data;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_P_SCALER_DIV0] <-- 0x%08x\n",
                        REG_PMU_RTC_P_SCALER_DIV0,data,data);
    #endif
}
GH_INLINE U8   GH_PMU_RTC_get_P_SCALER_DIV0(void)
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
/*! \brief Writes the register 'PMU_RTC_P_SCALER_DIV1'. */
void GH_PMU_RTC_set_P_SCALER_DIV1(U8 data);
/*! \brief Reads the register 'PMU_RTC_P_SCALER_DIV1'. */
U8   GH_PMU_RTC_get_P_SCALER_DIV1(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_RTC_set_P_SCALER_DIV1(U8 data)
{
    *(volatile U8 *)REG_PMU_RTC_P_SCALER_DIV1 = data;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_P_SCALER_DIV1] <-- 0x%08x\n",
                        REG_PMU_RTC_P_SCALER_DIV1,data,data);
    #endif
}
GH_INLINE U8   GH_PMU_RTC_get_P_SCALER_DIV1(void)
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
/*! \brief Writes the register 'PMU_RTC_P_SCALER_DIV2'. */
void GH_PMU_RTC_set_P_SCALER_DIV2(U8 data);
/*! \brief Reads the register 'PMU_RTC_P_SCALER_DIV2'. */
U8   GH_PMU_RTC_get_P_SCALER_DIV2(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_RTC_set_P_SCALER_DIV2(U8 data)
{
    *(volatile U8 *)REG_PMU_RTC_P_SCALER_DIV2 = data;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_P_SCALER_DIV2] <-- 0x%08x\n",
                        REG_PMU_RTC_P_SCALER_DIV2,data,data);
    #endif
}
GH_INLINE U8   GH_PMU_RTC_get_P_SCALER_DIV2(void)
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
/*! \brief Writes the register 'PMU_RTC_P_SCALER_DIV3'. */
void GH_PMU_RTC_set_P_SCALER_DIV3(U8 data);
/*! \brief Reads the register 'PMU_RTC_P_SCALER_DIV3'. */
U8   GH_PMU_RTC_get_P_SCALER_DIV3(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_RTC_set_P_SCALER_DIV3(U8 data)
{
    *(volatile U8 *)REG_PMU_RTC_P_SCALER_DIV3 = data;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_P_SCALER_DIV3] <-- 0x%08x\n",
                        REG_PMU_RTC_P_SCALER_DIV3,data,data);
    #endif
}
GH_INLINE U8   GH_PMU_RTC_get_P_SCALER_DIV3(void)
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
/*! \brief Writes the register 'PMU_RTC_PRE_LOAD_HOUR'. */
void GH_PMU_RTC_set_PRE_LOAD_HOUR(U8 data);
/*! \brief Reads the mirror variable of the register 'PMU_RTC_PRE_LOAD_HOUR'. */
U8   GH_PMU_RTC_getm_PRE_LOAD_HOUR(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_PMU_RTC_set_PRE_LOAD_HOUR(U8 data)
{
    m_pmu_rtc_pre_load_hour = data;
    *(volatile U8 *)REG_PMU_RTC_PRE_LOAD_HOUR = data;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_PRE_LOAD_HOUR] <-- 0x%08x\n",
                        REG_PMU_RTC_PRE_LOAD_HOUR,data,data);
    #endif
}
GH_INLINE U8   GH_PMU_RTC_getm_PRE_LOAD_HOUR(void)
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
/*! \brief Writes the register 'PMU_RTC_PRE_LOAD_MIN'. */
void GH_PMU_RTC_set_PRE_LOAD_MIN(U8 data);
/*! \brief Reads the mirror variable of the register 'PMU_RTC_PRE_LOAD_MIN'. */
U8   GH_PMU_RTC_getm_PRE_LOAD_MIN(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_PMU_RTC_set_PRE_LOAD_MIN(U8 data)
{
    m_pmu_rtc_pre_load_min = data;
    *(volatile U8 *)REG_PMU_RTC_PRE_LOAD_MIN = data;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_PRE_LOAD_MIN] <-- 0x%08x\n",
                        REG_PMU_RTC_PRE_LOAD_MIN,data,data);
    #endif
}
GH_INLINE U8   GH_PMU_RTC_getm_PRE_LOAD_MIN(void)
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
/*! \brief Writes the register 'PMU_RTC_PRE_LOAD_SEC'. */
void GH_PMU_RTC_set_PRE_LOAD_SEC(U8 data);
/*! \brief Reads the mirror variable of the register 'PMU_RTC_PRE_LOAD_SEC'. */
U8   GH_PMU_RTC_getm_PRE_LOAD_SEC(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_PMU_RTC_set_PRE_LOAD_SEC(U8 data)
{
    m_pmu_rtc_pre_load_sec = data;
    *(volatile U8 *)REG_PMU_RTC_PRE_LOAD_SEC = data;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_PRE_LOAD_SEC] <-- 0x%08x\n",
                        REG_PMU_RTC_PRE_LOAD_SEC,data,data);
    #endif
}
GH_INLINE U8   GH_PMU_RTC_getm_PRE_LOAD_SEC(void)
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
/*! \brief Writes the register 'PMU_RTC_IRQ_CLEAR'. */
void GH_PMU_RTC_set_IRQ_CLEAR(U8 data);
/*! \brief Reads the mirror variable of the register 'PMU_RTC_IRQ_CLEAR'. */
U8   GH_PMU_RTC_getm_IRQ_CLEAR(void);
/*! \brief Writes the bit group 'Clear' of register 'PMU_RTC_IRQ_CLEAR'. */
void GH_PMU_RTC_set_IRQ_CLEAR_Clear(U8 data);
/*! \brief Reads the bit group 'Clear' from the mirror variable of register 'PMU_RTC_IRQ_CLEAR'. */
U8   GH_PMU_RTC_getm_IRQ_CLEAR_Clear(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_PMU_RTC_set_IRQ_CLEAR(U8 data)
{
    m_pmu_rtc_irq_clear.all = data;
    *(volatile U8 *)REG_PMU_RTC_IRQ_CLEAR = data;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_IRQ_CLEAR] <-- 0x%08x\n",
                        REG_PMU_RTC_IRQ_CLEAR,data,data);
    #endif
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
    *(volatile U8 *)REG_PMU_RTC_IRQ_CLEAR = m_pmu_rtc_irq_clear.all;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_IRQ_CLEAR_Clear] <-- 0x%08x\n",
                        REG_PMU_RTC_IRQ_CLEAR,m_pmu_rtc_irq_clear.all,m_pmu_rtc_irq_clear.all);
    #endif
}
GH_INLINE U8   GH_PMU_RTC_getm_IRQ_CLEAR_Clear(void)
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
/*! \brief Writes the register 'PMU_RTC_PRE_LOAD_DAY_L'. */
void GH_PMU_RTC_set_PRE_LOAD_DAY_L(U8 data);
/*! \brief Reads the mirror variable of the register 'PMU_RTC_PRE_LOAD_DAY_L'. */
U8   GH_PMU_RTC_getm_PRE_LOAD_DAY_L(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_PMU_RTC_set_PRE_LOAD_DAY_L(U8 data)
{
    m_pmu_rtc_pre_load_day_l = data;
    *(volatile U8 *)REG_PMU_RTC_PRE_LOAD_DAY_L = data;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_PRE_LOAD_DAY_L] <-- 0x%08x\n",
                        REG_PMU_RTC_PRE_LOAD_DAY_L,data,data);
    #endif
}
GH_INLINE U8   GH_PMU_RTC_getm_PRE_LOAD_DAY_L(void)
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
/*! \brief Writes the register 'PMU_RTC_PRE_LOAD_DAY_H'. */
void GH_PMU_RTC_set_PRE_LOAD_DAY_H(U8 data);
/*! \brief Reads the mirror variable of the register 'PMU_RTC_PRE_LOAD_DAY_H'. */
U8   GH_PMU_RTC_getm_PRE_LOAD_DAY_H(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_PMU_RTC_set_PRE_LOAD_DAY_H(U8 data)
{
    m_pmu_rtc_pre_load_day_h = data;
    *(volatile U8 *)REG_PMU_RTC_PRE_LOAD_DAY_H = data;
    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_RTC_set_PRE_LOAD_DAY_H] <-- 0x%08x\n",
                        REG_PMU_RTC_PRE_LOAD_DAY_H,data,data);
    #endif
}
GH_INLINE U8   GH_PMU_RTC_getm_PRE_LOAD_DAY_H(void)
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
/*! \brief Reads the register 'PMU_RTC_IRQ_STATUS'. */
U32  GH_PMU_RTC_get_IRQ_STATUS(void);
/*! \brief Reads the bit group 'Gen' of register 'PMU_RTC_IRQ_STATUS'. */
U8   GH_PMU_RTC_get_IRQ_STATUS_Gen(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_PMU_RTC_get_IRQ_STATUS(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_RTC_IRQ_STATUS);

    #if GH_PMU_RTC_ENABLE_DEBUG_PRINT
    GH_PMU_RTC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_RTC_get_IRQ_STATUS] --> 0x%08x\n",
                        REG_PMU_RTC_IRQ_STATUS,value);
    #endif
    return value;
}
GH_INLINE U8   GH_PMU_RTC_get_IRQ_STATUS_Gen(void)
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
/*! \brief Reads the register 'PMU_RTC_SEC_VALUE'. */
U32  GH_PMU_RTC_get_SEC_VALUE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_PMU_RTC_get_SEC_VALUE(void)
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
/*! \brief Reads the register 'PMU_RTC_MIN_VALUE'. */
U32  GH_PMU_RTC_get_MIN_VALUE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_PMU_RTC_get_MIN_VALUE(void)
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
/*! \brief Reads the register 'PMU_RTC_HOUR_VALUE'. */
U32  GH_PMU_RTC_get_HOUR_VALUE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_PMU_RTC_get_HOUR_VALUE(void)
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
/*! \brief Reads the register 'PMU_RTC_DAY_L_VALUE'. */
U32  GH_PMU_RTC_get_DAY_L_VALUE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_PMU_RTC_get_DAY_L_VALUE(void)
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
/*! \brief Reads the register 'PMU_RTC_DAY_H_VALUE'. */
U32  GH_PMU_RTC_get_DAY_H_VALUE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_PMU_RTC_get_DAY_H_VALUE(void)
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
/*! \brief Initialises the registers and mirror variables. */
void GH_PMU_RTC_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_PMU_RTC_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

