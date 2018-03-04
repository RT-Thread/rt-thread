/*!
*******************************************************************************
**
** \file      gh_pmu.h
**
** \brief     Power Management Unit.
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
#ifndef _GH_PMU_H
#define _GH_PMU_H

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

#define GH_PMU_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_PMU_DEBUG_PRINT_FUNCTION printk
#else
#define GH_PMU_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_PMU_ENABLE_DEBUG_PRINT
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
#define REG_PMU_SYS_REG_CFG0                                FIO_ADDRESS(PMU,0x9008A000) /* read/write */
#define REG_PMU_SYS_REG_CFG1                                FIO_ADDRESS(PMU,0x9008A004) /* read/write */
#define REG_PMU_SYS_REG_CFG3                                FIO_ADDRESS(PMU,0x9008A00C) /* read/write */
#define REG_PMU_SYS_REG_CFG7                                FIO_ADDRESS(PMU,0x9008A01C) /* read/write */
#define REG_PMU_SYS_REG_CFG8                                FIO_ADDRESS(PMU,0x9008A020) /* read/write */
#define REG_PMU_SYS_REG_CFG9                                FIO_ADDRESS(PMU,0x9008A024) /* read/write */
#define REG_PMU_SYS_REG_CFG10                               FIO_ADDRESS(PMU,0x9008A028) /* read/write */
#define REG_PMU_SYS_REG_CFG11                               FIO_ADDRESS(PMU,0x9008A02C) /* read/write */
#define REG_PMU_SYS_REG_CFG12                               FIO_ADDRESS(PMU,0x9008A030) /* read/write */
#define REG_PMU_SYS_REG_CFG13                               FIO_ADDRESS(PMU,0x9008A034) /* read/write */
#define REG_PMU_SYS_REG_CFG14                               FIO_ADDRESS(PMU,0x9008A038) /* read/write */
#define REG_PMU_SYS_REG_CFG16                               FIO_ADDRESS(PMU,0x9008A040) /* read/write */
#define REG_PMU_SYS_REG_CFG17                               FIO_ADDRESS(PMU,0x9008A044) /* read/write */
#define REG_PMU_SYS_REG_CFG18                               FIO_ADDRESS(PMU,0x9008A048) /* read/write */
#define REG_PMU_IRQ_EN_MASK                                 FIO_ADDRESS(PMU,0x9008DC00) /* read/write */
#define REG_PMU_IRQ_CLR_RTC                                 FIO_ADDRESS(PMU,0x9008DC20) /* read/write */
#define REG_PMU_IRQ_CLR_IRR                                 FIO_ADDRESS(PMU,0x9008DC24) /* read/write */
#define REG_PMU_IRQ_CLR_FPC                                 FIO_ADDRESS(PMU,0x9008DC28) /* read/write */
#define REG_PMU_IRQ_CLR_GPIO                                FIO_ADDRESS(PMU,0x9008DC2C) /* read/write */
#define REG_PMU_IRQ_CLR_CEC                                 FIO_ADDRESS(PMU,0x9008DC30) /* read/write */
#define REG_PMU_IRQ_CLR_ADC                                 FIO_ADDRESS(PMU,0x9008DC34) /* read/write */
#define REG_PMU_IRQ_CLR_IRT                                 FIO_ADDRESS(PMU,0x9008DC38) /* read/write */
#define REG_PMU_IRQ_STATUS                                  FIO_ADDRESS(PMU,0x9008DC40) /* read/write */
#define REG_PMU_C51_LOADCODE_ADDR                           FIO_ADDRESS(PMU,0x900C0000) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* PMU_SYS_REG_CFG0 */
    U32 all;
    struct {
        U32 pmu_en                      : 1;
        U32                             : 3;
        U32 sys_reset                   : 1;
        U32 sw_reset                    : 1;
        U32                             : 26;
    } bitc;
} GH_PMU_SYS_REG_CFG0_S;

typedef union { /* PMU_SYS_REG_CFG1 */
    U32 all;
    struct {
        U32                             : 4;
        U32 gpio4                       : 1;
        U32                             : 2;
        U32 gpio7                       : 1;
        U32                             : 24;
    } bitc;
} GH_PMU_SYS_REG_CFG1_S;

typedef union { /* PMU_SYS_REG_CFG3 */
    U32 all;
    struct {
        U32 cec_en                      : 1;
        U32                             : 2;
        U32 pt6964_key_in               : 1;
        U32 ct1642_key_in               : 1;
        U32                             : 1;
        U32 pwr_wakeup                  : 1;
        U32 ir_in                       : 1;
        U32                             : 24;
    } bitc;
} GH_PMU_SYS_REG_CFG3_S;

typedef union { /* PMU_SYS_REG_CFG7 */
    U32 all;
    struct {
        U32 power_down                  : 1;
        U32                             : 31;
    } bitc;
} GH_PMU_SYS_REG_CFG7_S;

typedef union { /* PMU_SYS_REG_CFG8 */
    U32 all;
    struct {
        U32 wd_low_value                : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_SYS_REG_CFG8_S;

typedef union { /* PMU_SYS_REG_CFG9 */
    U32 all;
    struct {
        U32 wd_high_value               : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_SYS_REG_CFG9_S;

typedef union { /* PMU_SYS_REG_CFG10 */
    U32 all;
    struct {
        U32 wd_update                   : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_SYS_REG_CFG10_S;

typedef union { /* PMU_SYS_REG_CFG11 */
    U32 all;
    struct {
        U32 m51reset_dis                : 1;
        U32 m51clk_en                   : 1;
        U32                             : 2;
        U32 dlcode_en                   : 1;
        U32 dlcode_to_m51               : 1;
        U32 m51_handle                  : 1;
        U32 cpu_handle                  : 1;
        U32                             : 24;
    } bitc;
} GH_PMU_SYS_REG_CFG11_S;

typedef union { /* PMU_SYS_REG_CFG12 */
    U32 all;
    struct {
        U32 div0_low                    : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_SYS_REG_CFG12_S;

typedef union { /* PMU_SYS_REG_CFG13 */
    U32 all;
    struct {
        U32 div1_low                    : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_SYS_REG_CFG13_S;

typedef union { /* PMU_SYS_REG_CFG14 */
    U32 all;
    struct {
        U32 div0_high                   : 4;
        U32 div1_high                   : 4;
        U32                             : 24;
    } bitc;
} GH_PMU_SYS_REG_CFG14_S;

typedef union { /* PMU_SYS_REG_CFG16 */
    U32 all;
    struct {
        U32 xclk_iopad                  : 1;
        U32 rtc_iopad                   : 1;
        U32                             : 30;
    } bitc;
} GH_PMU_SYS_REG_CFG16_S;

typedef union { /* PMU_SYS_REG_CFG17 */
    U32 all;
    struct {
        U32 rtc_clk_sel                 : 1;
        U32 rtc_cnt_reset               : 1;
        U32 pmu_clk_sel                 : 1;
        U32                             : 29;
    } bitc;
} GH_PMU_SYS_REG_CFG17_S;

typedef union { /* PMU_SYS_REG_CFG18 */
    U32 all;
    struct {
        U32 e                           : 2;
        U32 sr                          : 1;
        U32 smt                         : 1;
        U32 p                           : 2;
        U32                             : 26;
    } bitc;
} GH_PMU_SYS_REG_CFG18_S;

typedef union { /* PMU_IRQ_EN_MASK */
    U32 all;
    struct {
        U32 rtc_en                      : 1;
        U32 irr_en                      : 1;
        U32 fpc_en                      : 1;
        U32 gpio_en                     : 1;
        U32 cec_en                      : 1;
        U32 adc_en                      : 1;
        U32 irt_en                      : 1;
        U32                             : 25;
    } bitc;
} GH_PMU_IRQ_EN_MASK_S;

typedef union { /* PMU_IRQ_CLR_RTC */
    U32 all;
    struct {
        U32 irqclr                      : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRQ_CLR_RTC_S;

typedef union { /* PMU_IRQ_CLR_IRR */
    U32 all;
    struct {
        U32 irqclr                      : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRQ_CLR_IRR_S;

typedef union { /* PMU_IRQ_CLR_FPC */
    U32 all;
    struct {
        U32 irqclr                      : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRQ_CLR_FPC_S;

typedef union { /* PMU_IRQ_CLR_GPIO */
    U32 all;
    struct {
        U32 irqclr                      : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRQ_CLR_GPIO_S;

typedef union { /* PMU_IRQ_CLR_CEC */
    U32 all;
    struct {
        U32 irqclr                      : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRQ_CLR_CEC_S;

typedef union { /* PMU_IRQ_CLR_ADC */
    U32 all;
    struct {
        U32 irqclr                      : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRQ_CLR_ADC_S;

typedef union { /* PMU_IRQ_CLR_IRT */
    U32 all;
    struct {
        U32 irqclr                      : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRQ_CLR_IRT_S;

typedef union { /* PMU_IRQ_STATUS */
    U32 all;
    struct {
        U32 rtc_irq                     : 1;
        U32 irr_irq                     : 1;
        U32 fpc_irq                     : 1;
        U32 gpio_irq                    : 1;
        U32 cec_irq                     : 1;
        U32 adc_irq                     : 1;
        U32 irt_irq                     : 1;
        U32                             : 25;
    } bitc;
} GH_PMU_IRQ_STATUS_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG0 (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_SYS_REG_CFG0'. */
void GH_PMU_set_SYS_REG_CFG0(U32 data);
/*! \brief Reads the register 'PMU_SYS_REG_CFG0'. */
U32  GH_PMU_get_SYS_REG_CFG0(void);
/*! \brief Writes the bit group 'PMU_EN' of register 'PMU_SYS_REG_CFG0'. */
void GH_PMU_set_SYS_REG_CFG0_PMU_EN(U8 data);
/*! \brief Reads the bit group 'PMU_EN' of register 'PMU_SYS_REG_CFG0'. */
U8   GH_PMU_get_SYS_REG_CFG0_PMU_EN(void);
/*! \brief Writes the bit group 'SYS_RESET' of register 'PMU_SYS_REG_CFG0'. */
void GH_PMU_set_SYS_REG_CFG0_SYS_RESET(U8 data);
/*! \brief Reads the bit group 'SYS_RESET' of register 'PMU_SYS_REG_CFG0'. */
U8   GH_PMU_get_SYS_REG_CFG0_SYS_RESET(void);
/*! \brief Writes the bit group 'SW_RESET' of register 'PMU_SYS_REG_CFG0'. */
void GH_PMU_set_SYS_REG_CFG0_SW_RESET(U8 data);
/*! \brief Reads the bit group 'SW_RESET' of register 'PMU_SYS_REG_CFG0'. */
U8   GH_PMU_get_SYS_REG_CFG0_SW_RESET(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_SYS_REG_CFG0(U32 data)
{
    *(volatile U32 *)REG_PMU_SYS_REG_CFG0 = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG0] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG0,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG0(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG0);

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG0] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG0,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG0_PMU_EN(U8 data)
{
    GH_PMU_SYS_REG_CFG0_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG0;
    d.bitc.pmu_en = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG0 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG0_PMU_EN] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG0_PMU_EN(void)
{
    GH_PMU_SYS_REG_CFG0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG0);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG0_PMU_EN] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG0,value);
    #endif
    return tmp_value.bitc.pmu_en;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG0_SYS_RESET(U8 data)
{
    GH_PMU_SYS_REG_CFG0_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG0;
    d.bitc.sys_reset = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG0 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG0_SYS_RESET] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG0_SYS_RESET(void)
{
    GH_PMU_SYS_REG_CFG0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG0);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG0_SYS_RESET] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG0,value);
    #endif
    return tmp_value.bitc.sys_reset;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG0_SW_RESET(U8 data)
{
    GH_PMU_SYS_REG_CFG0_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG0;
    d.bitc.sw_reset = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG0 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG0_SW_RESET] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG0_SW_RESET(void)
{
    GH_PMU_SYS_REG_CFG0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG0);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG0_SW_RESET] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG0,value);
    #endif
    return tmp_value.bitc.sw_reset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG1 (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_SYS_REG_CFG1'. */
void GH_PMU_set_SYS_REG_CFG1(U32 data);
/*! \brief Reads the register 'PMU_SYS_REG_CFG1'. */
U32  GH_PMU_get_SYS_REG_CFG1(void);
/*! \brief Writes the bit group 'GPIO4' of register 'PMU_SYS_REG_CFG1'. */
void GH_PMU_set_SYS_REG_CFG1_GPIO4(U8 data);
/*! \brief Reads the bit group 'GPIO4' of register 'PMU_SYS_REG_CFG1'. */
U8   GH_PMU_get_SYS_REG_CFG1_GPIO4(void);
/*! \brief Writes the bit group 'GPIO7' of register 'PMU_SYS_REG_CFG1'. */
void GH_PMU_set_SYS_REG_CFG1_GPIO7(U8 data);
/*! \brief Reads the bit group 'GPIO7' of register 'PMU_SYS_REG_CFG1'. */
U8   GH_PMU_get_SYS_REG_CFG1_GPIO7(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_SYS_REG_CFG1(U32 data)
{
    *(volatile U32 *)REG_PMU_SYS_REG_CFG1 = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG1] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG1,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG1(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG1);

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG1] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG1,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG1_GPIO4(U8 data)
{
    GH_PMU_SYS_REG_CFG1_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG1;
    d.bitc.gpio4 = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG1 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG1_GPIO4] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG1_GPIO4(void)
{
    GH_PMU_SYS_REG_CFG1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG1);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG1_GPIO4] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG1,value);
    #endif
    return tmp_value.bitc.gpio4;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG1_GPIO7(U8 data)
{
    GH_PMU_SYS_REG_CFG1_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG1;
    d.bitc.gpio7 = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG1 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG1_GPIO7] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG1_GPIO7(void)
{
    GH_PMU_SYS_REG_CFG1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG1);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG1_GPIO7] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG1,value);
    #endif
    return tmp_value.bitc.gpio7;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG3 (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_SYS_REG_CFG3'. */
void GH_PMU_set_SYS_REG_CFG3(U32 data);
/*! \brief Reads the register 'PMU_SYS_REG_CFG3'. */
U32  GH_PMU_get_SYS_REG_CFG3(void);
/*! \brief Writes the bit group 'CEC_EN' of register 'PMU_SYS_REG_CFG3'. */
void GH_PMU_set_SYS_REG_CFG3_CEC_EN(U8 data);
/*! \brief Reads the bit group 'CEC_EN' of register 'PMU_SYS_REG_CFG3'. */
U8   GH_PMU_get_SYS_REG_CFG3_CEC_EN(void);
/*! \brief Writes the bit group 'PT6964_KEY_IN' of register 'PMU_SYS_REG_CFG3'. */
void GH_PMU_set_SYS_REG_CFG3_PT6964_KEY_IN(U8 data);
/*! \brief Reads the bit group 'PT6964_KEY_IN' of register 'PMU_SYS_REG_CFG3'. */
U8   GH_PMU_get_SYS_REG_CFG3_PT6964_KEY_IN(void);
/*! \brief Writes the bit group 'CT1642_KEY_IN' of register 'PMU_SYS_REG_CFG3'. */
void GH_PMU_set_SYS_REG_CFG3_CT1642_KEY_IN(U8 data);
/*! \brief Reads the bit group 'CT1642_KEY_IN' of register 'PMU_SYS_REG_CFG3'. */
U8   GH_PMU_get_SYS_REG_CFG3_CT1642_KEY_IN(void);
/*! \brief Writes the bit group 'PWR_WAKEUP' of register 'PMU_SYS_REG_CFG3'. */
void GH_PMU_set_SYS_REG_CFG3_PWR_WAKEUP(U8 data);
/*! \brief Reads the bit group 'PWR_WAKEUP' of register 'PMU_SYS_REG_CFG3'. */
U8   GH_PMU_get_SYS_REG_CFG3_PWR_WAKEUP(void);
/*! \brief Writes the bit group 'IR_IN' of register 'PMU_SYS_REG_CFG3'. */
void GH_PMU_set_SYS_REG_CFG3_IR_IN(U8 data);
/*! \brief Reads the bit group 'IR_IN' of register 'PMU_SYS_REG_CFG3'. */
U8   GH_PMU_get_SYS_REG_CFG3_IR_IN(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_SYS_REG_CFG3(U32 data)
{
    *(volatile U32 *)REG_PMU_SYS_REG_CFG3 = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG3] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG3,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG3(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG3);

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG3] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG3,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG3_CEC_EN(U8 data)
{
    GH_PMU_SYS_REG_CFG3_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG3;
    d.bitc.cec_en = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG3 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG3_CEC_EN] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG3_CEC_EN(void)
{
    GH_PMU_SYS_REG_CFG3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG3);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG3_CEC_EN] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG3,value);
    #endif
    return tmp_value.bitc.cec_en;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG3_PT6964_KEY_IN(U8 data)
{
    GH_PMU_SYS_REG_CFG3_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG3;
    d.bitc.pt6964_key_in = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG3 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG3_PT6964_KEY_IN] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG3_PT6964_KEY_IN(void)
{
    GH_PMU_SYS_REG_CFG3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG3);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG3_PT6964_KEY_IN] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG3,value);
    #endif
    return tmp_value.bitc.pt6964_key_in;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG3_CT1642_KEY_IN(U8 data)
{
    GH_PMU_SYS_REG_CFG3_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG3;
    d.bitc.ct1642_key_in = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG3 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG3_CT1642_KEY_IN] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG3_CT1642_KEY_IN(void)
{
    GH_PMU_SYS_REG_CFG3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG3);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG3_CT1642_KEY_IN] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG3,value);
    #endif
    return tmp_value.bitc.ct1642_key_in;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG3_PWR_WAKEUP(U8 data)
{
    GH_PMU_SYS_REG_CFG3_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG3;
    d.bitc.pwr_wakeup = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG3 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG3_PWR_WAKEUP] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG3_PWR_WAKEUP(void)
{
    GH_PMU_SYS_REG_CFG3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG3);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG3_PWR_WAKEUP] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG3,value);
    #endif
    return tmp_value.bitc.pwr_wakeup;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG3_IR_IN(U8 data)
{
    GH_PMU_SYS_REG_CFG3_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG3;
    d.bitc.ir_in = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG3 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG3_IR_IN] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG3_IR_IN(void)
{
    GH_PMU_SYS_REG_CFG3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG3);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG3_IR_IN] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG3,value);
    #endif
    return tmp_value.bitc.ir_in;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG7 (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_SYS_REG_CFG7'. */
void GH_PMU_set_SYS_REG_CFG7(U32 data);
/*! \brief Reads the register 'PMU_SYS_REG_CFG7'. */
U32  GH_PMU_get_SYS_REG_CFG7(void);
/*! \brief Writes the bit group 'POWER_DOWN' of register 'PMU_SYS_REG_CFG7'. */
void GH_PMU_set_SYS_REG_CFG7_POWER_DOWN(U8 data);
/*! \brief Reads the bit group 'POWER_DOWN' of register 'PMU_SYS_REG_CFG7'. */
U8   GH_PMU_get_SYS_REG_CFG7_POWER_DOWN(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_SYS_REG_CFG7(U32 data)
{
    *(volatile U32 *)REG_PMU_SYS_REG_CFG7 = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG7] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG7,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG7(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG7);

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG7] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG7,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG7_POWER_DOWN(U8 data)
{
    GH_PMU_SYS_REG_CFG7_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG7;
    d.bitc.power_down = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG7 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG7_POWER_DOWN] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG7,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG7_POWER_DOWN(void)
{
    GH_PMU_SYS_REG_CFG7_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG7);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG7_POWER_DOWN] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG7,value);
    #endif
    return tmp_value.bitc.power_down;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG8 (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_SYS_REG_CFG8'. */
void GH_PMU_set_SYS_REG_CFG8(U32 data);
/*! \brief Reads the register 'PMU_SYS_REG_CFG8'. */
U32  GH_PMU_get_SYS_REG_CFG8(void);
/*! \brief Writes the bit group 'WD_LOW_VALUE' of register 'PMU_SYS_REG_CFG8'. */
void GH_PMU_set_SYS_REG_CFG8_WD_LOW_VALUE(U8 data);
/*! \brief Reads the bit group 'WD_LOW_VALUE' of register 'PMU_SYS_REG_CFG8'. */
U8   GH_PMU_get_SYS_REG_CFG8_WD_LOW_VALUE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_SYS_REG_CFG8(U32 data)
{
    *(volatile U32 *)REG_PMU_SYS_REG_CFG8 = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG8] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG8,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG8(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG8);

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG8] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG8,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG8_WD_LOW_VALUE(U8 data)
{
    GH_PMU_SYS_REG_CFG8_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG8;
    d.bitc.wd_low_value = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG8 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG8_WD_LOW_VALUE] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG8,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG8_WD_LOW_VALUE(void)
{
    GH_PMU_SYS_REG_CFG8_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG8);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG8_WD_LOW_VALUE] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG8,value);
    #endif
    return tmp_value.bitc.wd_low_value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG9 (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_SYS_REG_CFG9'. */
void GH_PMU_set_SYS_REG_CFG9(U32 data);
/*! \brief Reads the register 'PMU_SYS_REG_CFG9'. */
U32  GH_PMU_get_SYS_REG_CFG9(void);
/*! \brief Writes the bit group 'WD_HIGH_VALUE' of register 'PMU_SYS_REG_CFG9'. */
void GH_PMU_set_SYS_REG_CFG9_WD_HIGH_VALUE(U8 data);
/*! \brief Reads the bit group 'WD_HIGH_VALUE' of register 'PMU_SYS_REG_CFG9'. */
U8   GH_PMU_get_SYS_REG_CFG9_WD_HIGH_VALUE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_SYS_REG_CFG9(U32 data)
{
    *(volatile U32 *)REG_PMU_SYS_REG_CFG9 = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG9] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG9,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG9(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG9);

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG9] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG9,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG9_WD_HIGH_VALUE(U8 data)
{
    GH_PMU_SYS_REG_CFG9_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG9;
    d.bitc.wd_high_value = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG9 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG9_WD_HIGH_VALUE] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG9,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG9_WD_HIGH_VALUE(void)
{
    GH_PMU_SYS_REG_CFG9_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG9);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG9_WD_HIGH_VALUE] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG9,value);
    #endif
    return tmp_value.bitc.wd_high_value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG10 (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_SYS_REG_CFG10'. */
void GH_PMU_set_SYS_REG_CFG10(U32 data);
/*! \brief Reads the register 'PMU_SYS_REG_CFG10'. */
U32  GH_PMU_get_SYS_REG_CFG10(void);
/*! \brief Writes the bit group 'WD_UPDATE' of register 'PMU_SYS_REG_CFG10'. */
void GH_PMU_set_SYS_REG_CFG10_WD_UPDATE(U8 data);
/*! \brief Reads the bit group 'WD_UPDATE' of register 'PMU_SYS_REG_CFG10'. */
U8   GH_PMU_get_SYS_REG_CFG10_WD_UPDATE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_SYS_REG_CFG10(U32 data)
{
    *(volatile U32 *)REG_PMU_SYS_REG_CFG10 = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG10] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG10,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG10(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG10);

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG10] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG10,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG10_WD_UPDATE(U8 data)
{
    GH_PMU_SYS_REG_CFG10_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG10;
    d.bitc.wd_update = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG10 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG10_WD_UPDATE] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG10,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG10_WD_UPDATE(void)
{
    GH_PMU_SYS_REG_CFG10_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG10);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG10_WD_UPDATE] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG10,value);
    #endif
    return tmp_value.bitc.wd_update;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG11 (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_SYS_REG_CFG11'. */
void GH_PMU_set_SYS_REG_CFG11(U32 data);
/*! \brief Reads the register 'PMU_SYS_REG_CFG11'. */
U32  GH_PMU_get_SYS_REG_CFG11(void);
/*! \brief Writes the bit group 'M51RESET_DIS' of register 'PMU_SYS_REG_CFG11'. */
void GH_PMU_set_SYS_REG_CFG11_M51RESET_DIS(U8 data);
/*! \brief Reads the bit group 'M51RESET_DIS' of register 'PMU_SYS_REG_CFG11'. */
U8   GH_PMU_get_SYS_REG_CFG11_M51RESET_DIS(void);
/*! \brief Writes the bit group 'M51CLK_EN' of register 'PMU_SYS_REG_CFG11'. */
void GH_PMU_set_SYS_REG_CFG11_M51CLK_EN(U8 data);
/*! \brief Reads the bit group 'M51CLK_EN' of register 'PMU_SYS_REG_CFG11'. */
U8   GH_PMU_get_SYS_REG_CFG11_M51CLK_EN(void);
/*! \brief Writes the bit group 'DLCODE_EN' of register 'PMU_SYS_REG_CFG11'. */
void GH_PMU_set_SYS_REG_CFG11_DLCODE_EN(U8 data);
/*! \brief Reads the bit group 'DLCODE_EN' of register 'PMU_SYS_REG_CFG11'. */
U8   GH_PMU_get_SYS_REG_CFG11_DLCODE_EN(void);
/*! \brief Writes the bit group 'DLCODE_TO_M51' of register 'PMU_SYS_REG_CFG11'. */
void GH_PMU_set_SYS_REG_CFG11_DLCODE_TO_M51(U8 data);
/*! \brief Reads the bit group 'DLCODE_TO_M51' of register 'PMU_SYS_REG_CFG11'. */
U8   GH_PMU_get_SYS_REG_CFG11_DLCODE_TO_M51(void);
/*! \brief Writes the bit group 'M51_HANDLE' of register 'PMU_SYS_REG_CFG11'. */
void GH_PMU_set_SYS_REG_CFG11_M51_HANDLE(U8 data);
/*! \brief Reads the bit group 'M51_HANDLE' of register 'PMU_SYS_REG_CFG11'. */
U8   GH_PMU_get_SYS_REG_CFG11_M51_HANDLE(void);
/*! \brief Writes the bit group 'CPU_HANDLE' of register 'PMU_SYS_REG_CFG11'. */
void GH_PMU_set_SYS_REG_CFG11_CPU_HANDLE(U8 data);
/*! \brief Reads the bit group 'CPU_HANDLE' of register 'PMU_SYS_REG_CFG11'. */
U8   GH_PMU_get_SYS_REG_CFG11_CPU_HANDLE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_SYS_REG_CFG11(U32 data)
{
    *(volatile U32 *)REG_PMU_SYS_REG_CFG11 = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG11] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG11,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG11(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG11);

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG11] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG11,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG11_M51RESET_DIS(U8 data)
{
    GH_PMU_SYS_REG_CFG11_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG11;
    d.bitc.m51reset_dis = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG11 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG11_M51RESET_DIS] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG11_M51RESET_DIS(void)
{
    GH_PMU_SYS_REG_CFG11_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG11);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG11_M51RESET_DIS] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG11,value);
    #endif
    return tmp_value.bitc.m51reset_dis;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG11_M51CLK_EN(U8 data)
{
    GH_PMU_SYS_REG_CFG11_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG11;
    d.bitc.m51clk_en = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG11 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG11_M51CLK_EN] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG11_M51CLK_EN(void)
{
    GH_PMU_SYS_REG_CFG11_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG11);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG11_M51CLK_EN] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG11,value);
    #endif
    return tmp_value.bitc.m51clk_en;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG11_DLCODE_EN(U8 data)
{
    GH_PMU_SYS_REG_CFG11_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG11;
    d.bitc.dlcode_en = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG11 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG11_DLCODE_EN] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG11_DLCODE_EN(void)
{
    GH_PMU_SYS_REG_CFG11_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG11);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG11_DLCODE_EN] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG11,value);
    #endif
    return tmp_value.bitc.dlcode_en;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG11_DLCODE_TO_M51(U8 data)
{
    GH_PMU_SYS_REG_CFG11_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG11;
    d.bitc.dlcode_to_m51 = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG11 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG11_DLCODE_TO_M51] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG11_DLCODE_TO_M51(void)
{
    GH_PMU_SYS_REG_CFG11_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG11);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG11_DLCODE_TO_M51] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG11,value);
    #endif
    return tmp_value.bitc.dlcode_to_m51;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG11_M51_HANDLE(U8 data)
{
    GH_PMU_SYS_REG_CFG11_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG11;
    d.bitc.m51_handle = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG11 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG11_M51_HANDLE] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG11_M51_HANDLE(void)
{
    GH_PMU_SYS_REG_CFG11_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG11);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG11_M51_HANDLE] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG11,value);
    #endif
    return tmp_value.bitc.m51_handle;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG11_CPU_HANDLE(U8 data)
{
    GH_PMU_SYS_REG_CFG11_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG11;
    d.bitc.cpu_handle = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG11 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG11_CPU_HANDLE] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG11_CPU_HANDLE(void)
{
    GH_PMU_SYS_REG_CFG11_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG11);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG11_CPU_HANDLE] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG11,value);
    #endif
    return tmp_value.bitc.cpu_handle;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG12 (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_SYS_REG_CFG12'. */
void GH_PMU_set_SYS_REG_CFG12(U32 data);
/*! \brief Reads the register 'PMU_SYS_REG_CFG12'. */
U32  GH_PMU_get_SYS_REG_CFG12(void);
/*! \brief Writes the bit group 'DIV0_LOW' of register 'PMU_SYS_REG_CFG12'. */
void GH_PMU_set_SYS_REG_CFG12_DIV0_LOW(U8 data);
/*! \brief Reads the bit group 'DIV0_LOW' of register 'PMU_SYS_REG_CFG12'. */
U8   GH_PMU_get_SYS_REG_CFG12_DIV0_LOW(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_SYS_REG_CFG12(U32 data)
{
    *(volatile U32 *)REG_PMU_SYS_REG_CFG12 = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG12] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG12,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG12(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG12);

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG12] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG12,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG12_DIV0_LOW(U8 data)
{
    GH_PMU_SYS_REG_CFG12_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG12;
    d.bitc.div0_low = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG12 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG12_DIV0_LOW] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG12,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG12_DIV0_LOW(void)
{
    GH_PMU_SYS_REG_CFG12_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG12);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG12_DIV0_LOW] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG12,value);
    #endif
    return tmp_value.bitc.div0_low;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG13 (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_SYS_REG_CFG13'. */
void GH_PMU_set_SYS_REG_CFG13(U32 data);
/*! \brief Reads the register 'PMU_SYS_REG_CFG13'. */
U32  GH_PMU_get_SYS_REG_CFG13(void);
/*! \brief Writes the bit group 'DIV1_LOW' of register 'PMU_SYS_REG_CFG13'. */
void GH_PMU_set_SYS_REG_CFG13_DIV1_LOW(U8 data);
/*! \brief Reads the bit group 'DIV1_LOW' of register 'PMU_SYS_REG_CFG13'. */
U8   GH_PMU_get_SYS_REG_CFG13_DIV1_LOW(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_SYS_REG_CFG13(U32 data)
{
    *(volatile U32 *)REG_PMU_SYS_REG_CFG13 = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG13] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG13,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG13(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG13);

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG13] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG13,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG13_DIV1_LOW(U8 data)
{
    GH_PMU_SYS_REG_CFG13_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG13;
    d.bitc.div1_low = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG13 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG13_DIV1_LOW] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG13,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG13_DIV1_LOW(void)
{
    GH_PMU_SYS_REG_CFG13_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG13);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG13_DIV1_LOW] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG13,value);
    #endif
    return tmp_value.bitc.div1_low;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG14 (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_SYS_REG_CFG14'. */
void GH_PMU_set_SYS_REG_CFG14(U32 data);
/*! \brief Reads the register 'PMU_SYS_REG_CFG14'. */
U32  GH_PMU_get_SYS_REG_CFG14(void);
/*! \brief Writes the bit group 'DIV0_HIGH' of register 'PMU_SYS_REG_CFG14'. */
void GH_PMU_set_SYS_REG_CFG14_DIV0_HIGH(U8 data);
/*! \brief Reads the bit group 'DIV0_HIGH' of register 'PMU_SYS_REG_CFG14'. */
U8   GH_PMU_get_SYS_REG_CFG14_DIV0_HIGH(void);
/*! \brief Writes the bit group 'DIV1_HIGH' of register 'PMU_SYS_REG_CFG14'. */
void GH_PMU_set_SYS_REG_CFG14_DIV1_HIGH(U8 data);
/*! \brief Reads the bit group 'DIV1_HIGH' of register 'PMU_SYS_REG_CFG14'. */
U8   GH_PMU_get_SYS_REG_CFG14_DIV1_HIGH(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_SYS_REG_CFG14(U32 data)
{
    *(volatile U32 *)REG_PMU_SYS_REG_CFG14 = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG14] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG14,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG14(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG14);

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG14] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG14,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG14_DIV0_HIGH(U8 data)
{
    GH_PMU_SYS_REG_CFG14_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG14;
    d.bitc.div0_high = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG14 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG14_DIV0_HIGH] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG14,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG14_DIV0_HIGH(void)
{
    GH_PMU_SYS_REG_CFG14_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG14);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG14_DIV0_HIGH] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG14,value);
    #endif
    return tmp_value.bitc.div0_high;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG14_DIV1_HIGH(U8 data)
{
    GH_PMU_SYS_REG_CFG14_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG14;
    d.bitc.div1_high = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG14 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG14_DIV1_HIGH] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG14,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG14_DIV1_HIGH(void)
{
    GH_PMU_SYS_REG_CFG14_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG14);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG14_DIV1_HIGH] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG14,value);
    #endif
    return tmp_value.bitc.div1_high;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG16 (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_SYS_REG_CFG16'. */
void GH_PMU_set_SYS_REG_CFG16(U32 data);
/*! \brief Reads the register 'PMU_SYS_REG_CFG16'. */
U32  GH_PMU_get_SYS_REG_CFG16(void);
/*! \brief Writes the bit group 'XCLK_IOPAD' of register 'PMU_SYS_REG_CFG16'. */
void GH_PMU_set_SYS_REG_CFG16_XCLK_IOPAD(U8 data);
/*! \brief Reads the bit group 'XCLK_IOPAD' of register 'PMU_SYS_REG_CFG16'. */
U8   GH_PMU_get_SYS_REG_CFG16_XCLK_IOPAD(void);
/*! \brief Writes the bit group 'RTC_IOPAD' of register 'PMU_SYS_REG_CFG16'. */
void GH_PMU_set_SYS_REG_CFG16_RTC_IOPAD(U8 data);
/*! \brief Reads the bit group 'RTC_IOPAD' of register 'PMU_SYS_REG_CFG16'. */
U8   GH_PMU_get_SYS_REG_CFG16_RTC_IOPAD(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_SYS_REG_CFG16(U32 data)
{
    *(volatile U32 *)REG_PMU_SYS_REG_CFG16 = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG16] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG16,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG16(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG16);

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG16] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG16,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG16_XCLK_IOPAD(U8 data)
{
    GH_PMU_SYS_REG_CFG16_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG16;
    d.bitc.xclk_iopad = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG16 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG16_XCLK_IOPAD] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG16,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG16_XCLK_IOPAD(void)
{
    GH_PMU_SYS_REG_CFG16_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG16);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG16_XCLK_IOPAD] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG16,value);
    #endif
    return tmp_value.bitc.xclk_iopad;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG16_RTC_IOPAD(U8 data)
{
    GH_PMU_SYS_REG_CFG16_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG16;
    d.bitc.rtc_iopad = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG16 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG16_RTC_IOPAD] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG16,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG16_RTC_IOPAD(void)
{
    GH_PMU_SYS_REG_CFG16_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG16);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG16_RTC_IOPAD] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG16,value);
    #endif
    return tmp_value.bitc.rtc_iopad;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG17 (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_SYS_REG_CFG17'. */
void GH_PMU_set_SYS_REG_CFG17(U32 data);
/*! \brief Reads the register 'PMU_SYS_REG_CFG17'. */
U32  GH_PMU_get_SYS_REG_CFG17(void);
/*! \brief Writes the bit group 'RTC_CLK_SEL' of register 'PMU_SYS_REG_CFG17'. */
void GH_PMU_set_SYS_REG_CFG17_RTC_CLK_SEL(U8 data);
/*! \brief Reads the bit group 'RTC_CLK_SEL' of register 'PMU_SYS_REG_CFG17'. */
U8   GH_PMU_get_SYS_REG_CFG17_RTC_CLK_SEL(void);
/*! \brief Writes the bit group 'RTC_CNT_RESET' of register 'PMU_SYS_REG_CFG17'. */
void GH_PMU_set_SYS_REG_CFG17_RTC_CNT_RESET(U8 data);
/*! \brief Reads the bit group 'RTC_CNT_RESET' of register 'PMU_SYS_REG_CFG17'. */
U8   GH_PMU_get_SYS_REG_CFG17_RTC_CNT_RESET(void);
/*! \brief Writes the bit group 'PMU_CLK_SEL' of register 'PMU_SYS_REG_CFG17'. */
void GH_PMU_set_SYS_REG_CFG17_PMU_CLK_SEL(U8 data);
/*! \brief Reads the bit group 'PMU_CLK_SEL' of register 'PMU_SYS_REG_CFG17'. */
U8   GH_PMU_get_SYS_REG_CFG17_PMU_CLK_SEL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_SYS_REG_CFG17(U32 data)
{
    *(volatile U32 *)REG_PMU_SYS_REG_CFG17 = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG17] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG17,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG17(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG17);

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG17] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG17,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG17_RTC_CLK_SEL(U8 data)
{
    GH_PMU_SYS_REG_CFG17_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG17;
    d.bitc.rtc_clk_sel = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG17 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG17_RTC_CLK_SEL] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG17,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG17_RTC_CLK_SEL(void)
{
    GH_PMU_SYS_REG_CFG17_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG17);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG17_RTC_CLK_SEL] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG17,value);
    #endif
    return tmp_value.bitc.rtc_clk_sel;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG17_RTC_CNT_RESET(U8 data)
{
    GH_PMU_SYS_REG_CFG17_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG17;
    d.bitc.rtc_cnt_reset = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG17 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG17_RTC_CNT_RESET] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG17,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG17_RTC_CNT_RESET(void)
{
    GH_PMU_SYS_REG_CFG17_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG17);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG17_RTC_CNT_RESET] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG17,value);
    #endif
    return tmp_value.bitc.rtc_cnt_reset;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG17_PMU_CLK_SEL(U8 data)
{
    GH_PMU_SYS_REG_CFG17_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG17;
    d.bitc.pmu_clk_sel = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG17 = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG17_PMU_CLK_SEL] <-- 0x%08x\n",
                        REG_PMU_SYS_REG_CFG17,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG17_PMU_CLK_SEL(void)
{
    GH_PMU_SYS_REG_CFG17_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG17);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG17_PMU_CLK_SEL] --> 0x%08x\n",
                        REG_PMU_SYS_REG_CFG17,value);
    #endif
    return tmp_value.bitc.pmu_clk_sel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG18 (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_SYS_REG_CFG18'. */
void GH_PMU_set_SYS_REG_CFG18(U8 index, U32 data);
/*! \brief Reads the register 'PMU_SYS_REG_CFG18'. */
U32  GH_PMU_get_SYS_REG_CFG18(U8 index);
/*! \brief Writes the bit group 'E' of register 'PMU_SYS_REG_CFG18'. */
void GH_PMU_set_SYS_REG_CFG18_E(U8 index, U8 data);
/*! \brief Reads the bit group 'E' of register 'PMU_SYS_REG_CFG18'. */
U8   GH_PMU_get_SYS_REG_CFG18_E(U8 index);
/*! \brief Writes the bit group 'SR' of register 'PMU_SYS_REG_CFG18'. */
void GH_PMU_set_SYS_REG_CFG18_SR(U8 index, U8 data);
/*! \brief Reads the bit group 'SR' of register 'PMU_SYS_REG_CFG18'. */
U8   GH_PMU_get_SYS_REG_CFG18_SR(U8 index);
/*! \brief Writes the bit group 'SMT' of register 'PMU_SYS_REG_CFG18'. */
void GH_PMU_set_SYS_REG_CFG18_SMT(U8 index, U8 data);
/*! \brief Reads the bit group 'SMT' of register 'PMU_SYS_REG_CFG18'. */
U8   GH_PMU_get_SYS_REG_CFG18_SMT(U8 index);
/*! \brief Writes the bit group 'P' of register 'PMU_SYS_REG_CFG18'. */
void GH_PMU_set_SYS_REG_CFG18_P(U8 index, U8 data);
/*! \brief Reads the bit group 'P' of register 'PMU_SYS_REG_CFG18'. */
U8   GH_PMU_get_SYS_REG_CFG18_P(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_SYS_REG_CFG18(U8 index, U32 data)
{
    *(volatile U32 *)(REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4)) = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG18] <-- 0x%08x\n",
                        (REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4)),data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG18(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4)));

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG18] --> 0x%08x\n",
                        (REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4)),value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG18_E(U8 index, U8 data)
{
    GH_PMU_SYS_REG_CFG18_S d;
    d.all = *(volatile U32 *)(REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4));
    d.bitc.e = data;
    *(volatile U32 *)(REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4)) = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG18_E] <-- 0x%08x\n",
                        (REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG18_E(U8 index)
{
    GH_PMU_SYS_REG_CFG18_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4)));

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG18_E] --> 0x%08x\n",
                        (REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4)),value);
    #endif
    return tmp_value.bitc.e;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG18_SR(U8 index, U8 data)
{
    GH_PMU_SYS_REG_CFG18_S d;
    d.all = *(volatile U32 *)(REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4));
    d.bitc.sr = data;
    *(volatile U32 *)(REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4)) = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG18_SR] <-- 0x%08x\n",
                        (REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG18_SR(U8 index)
{
    GH_PMU_SYS_REG_CFG18_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4)));

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG18_SR] --> 0x%08x\n",
                        (REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4)),value);
    #endif
    return tmp_value.bitc.sr;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG18_SMT(U8 index, U8 data)
{
    GH_PMU_SYS_REG_CFG18_S d;
    d.all = *(volatile U32 *)(REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4));
    d.bitc.smt = data;
    *(volatile U32 *)(REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4)) = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG18_SMT] <-- 0x%08x\n",
                        (REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG18_SMT(U8 index)
{
    GH_PMU_SYS_REG_CFG18_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4)));

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG18_SMT] --> 0x%08x\n",
                        (REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4)),value);
    #endif
    return tmp_value.bitc.smt;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG18_P(U8 index, U8 data)
{
    GH_PMU_SYS_REG_CFG18_S d;
    d.all = *(volatile U32 *)(REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4));
    d.bitc.p = data;
    *(volatile U32 *)(REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4)) = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_SYS_REG_CFG18_P] <-- 0x%08x\n",
                        (REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG18_P(U8 index)
{
    GH_PMU_SYS_REG_CFG18_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4)));

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_SYS_REG_CFG18_P] --> 0x%08x\n",
                        (REG_PMU_SYS_REG_CFG18 + index * FIO_MOFFSET(PMU,4)),value);
    #endif
    return tmp_value.bitc.p;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_EN_MASK (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_IRQ_EN_MASK'. */
void GH_PMU_set_IRQ_EN_MASK(U32 data);
/*! \brief Reads the register 'PMU_IRQ_EN_MASK'. */
U32  GH_PMU_get_IRQ_EN_MASK(void);
/*! \brief Writes the bit group 'RTC_EN' of register 'PMU_IRQ_EN_MASK'. */
void GH_PMU_set_IRQ_EN_MASK_RTC_EN(U8 data);
/*! \brief Reads the bit group 'RTC_EN' of register 'PMU_IRQ_EN_MASK'. */
U8   GH_PMU_get_IRQ_EN_MASK_RTC_EN(void);
/*! \brief Writes the bit group 'IRR_EN' of register 'PMU_IRQ_EN_MASK'. */
void GH_PMU_set_IRQ_EN_MASK_IRR_EN(U8 data);
/*! \brief Reads the bit group 'IRR_EN' of register 'PMU_IRQ_EN_MASK'. */
U8   GH_PMU_get_IRQ_EN_MASK_IRR_EN(void);
/*! \brief Writes the bit group 'FPC_EN' of register 'PMU_IRQ_EN_MASK'. */
void GH_PMU_set_IRQ_EN_MASK_FPC_EN(U8 data);
/*! \brief Reads the bit group 'FPC_EN' of register 'PMU_IRQ_EN_MASK'. */
U8   GH_PMU_get_IRQ_EN_MASK_FPC_EN(void);
/*! \brief Writes the bit group 'GPIO_EN' of register 'PMU_IRQ_EN_MASK'. */
void GH_PMU_set_IRQ_EN_MASK_GPIO_EN(U8 data);
/*! \brief Reads the bit group 'GPIO_EN' of register 'PMU_IRQ_EN_MASK'. */
U8   GH_PMU_get_IRQ_EN_MASK_GPIO_EN(void);
/*! \brief Writes the bit group 'CEC_EN' of register 'PMU_IRQ_EN_MASK'. */
void GH_PMU_set_IRQ_EN_MASK_CEC_EN(U8 data);
/*! \brief Reads the bit group 'CEC_EN' of register 'PMU_IRQ_EN_MASK'. */
U8   GH_PMU_get_IRQ_EN_MASK_CEC_EN(void);
/*! \brief Writes the bit group 'ADC_EN' of register 'PMU_IRQ_EN_MASK'. */
void GH_PMU_set_IRQ_EN_MASK_ADC_EN(U8 data);
/*! \brief Reads the bit group 'ADC_EN' of register 'PMU_IRQ_EN_MASK'. */
U8   GH_PMU_get_IRQ_EN_MASK_ADC_EN(void);
/*! \brief Writes the bit group 'IRT_EN' of register 'PMU_IRQ_EN_MASK'. */
void GH_PMU_set_IRQ_EN_MASK_IRT_EN(U8 data);
/*! \brief Reads the bit group 'IRT_EN' of register 'PMU_IRQ_EN_MASK'. */
U8   GH_PMU_get_IRQ_EN_MASK_IRT_EN(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_IRQ_EN_MASK(U32 data)
{
    *(volatile U32 *)REG_PMU_IRQ_EN_MASK = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_EN_MASK] <-- 0x%08x\n",
                        REG_PMU_IRQ_EN_MASK,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_IRQ_EN_MASK(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_EN_MASK);

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_EN_MASK] --> 0x%08x\n",
                        REG_PMU_IRQ_EN_MASK,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_IRQ_EN_MASK_RTC_EN(U8 data)
{
    GH_PMU_IRQ_EN_MASK_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_EN_MASK;
    d.bitc.rtc_en = data;
    *(volatile U32 *)REG_PMU_IRQ_EN_MASK = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_EN_MASK_RTC_EN] <-- 0x%08x\n",
                        REG_PMU_IRQ_EN_MASK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_IRQ_EN_MASK_RTC_EN(void)
{
    GH_PMU_IRQ_EN_MASK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_EN_MASK);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_EN_MASK_RTC_EN] --> 0x%08x\n",
                        REG_PMU_IRQ_EN_MASK,value);
    #endif
    return tmp_value.bitc.rtc_en;
}
GH_INLINE void GH_PMU_set_IRQ_EN_MASK_IRR_EN(U8 data)
{
    GH_PMU_IRQ_EN_MASK_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_EN_MASK;
    d.bitc.irr_en = data;
    *(volatile U32 *)REG_PMU_IRQ_EN_MASK = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_EN_MASK_IRR_EN] <-- 0x%08x\n",
                        REG_PMU_IRQ_EN_MASK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_IRQ_EN_MASK_IRR_EN(void)
{
    GH_PMU_IRQ_EN_MASK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_EN_MASK);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_EN_MASK_IRR_EN] --> 0x%08x\n",
                        REG_PMU_IRQ_EN_MASK,value);
    #endif
    return tmp_value.bitc.irr_en;
}
GH_INLINE void GH_PMU_set_IRQ_EN_MASK_FPC_EN(U8 data)
{
    GH_PMU_IRQ_EN_MASK_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_EN_MASK;
    d.bitc.fpc_en = data;
    *(volatile U32 *)REG_PMU_IRQ_EN_MASK = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_EN_MASK_FPC_EN] <-- 0x%08x\n",
                        REG_PMU_IRQ_EN_MASK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_IRQ_EN_MASK_FPC_EN(void)
{
    GH_PMU_IRQ_EN_MASK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_EN_MASK);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_EN_MASK_FPC_EN] --> 0x%08x\n",
                        REG_PMU_IRQ_EN_MASK,value);
    #endif
    return tmp_value.bitc.fpc_en;
}
GH_INLINE void GH_PMU_set_IRQ_EN_MASK_GPIO_EN(U8 data)
{
    GH_PMU_IRQ_EN_MASK_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_EN_MASK;
    d.bitc.gpio_en = data;
    *(volatile U32 *)REG_PMU_IRQ_EN_MASK = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_EN_MASK_GPIO_EN] <-- 0x%08x\n",
                        REG_PMU_IRQ_EN_MASK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_IRQ_EN_MASK_GPIO_EN(void)
{
    GH_PMU_IRQ_EN_MASK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_EN_MASK);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_EN_MASK_GPIO_EN] --> 0x%08x\n",
                        REG_PMU_IRQ_EN_MASK,value);
    #endif
    return tmp_value.bitc.gpio_en;
}
GH_INLINE void GH_PMU_set_IRQ_EN_MASK_CEC_EN(U8 data)
{
    GH_PMU_IRQ_EN_MASK_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_EN_MASK;
    d.bitc.cec_en = data;
    *(volatile U32 *)REG_PMU_IRQ_EN_MASK = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_EN_MASK_CEC_EN] <-- 0x%08x\n",
                        REG_PMU_IRQ_EN_MASK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_IRQ_EN_MASK_CEC_EN(void)
{
    GH_PMU_IRQ_EN_MASK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_EN_MASK);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_EN_MASK_CEC_EN] --> 0x%08x\n",
                        REG_PMU_IRQ_EN_MASK,value);
    #endif
    return tmp_value.bitc.cec_en;
}
GH_INLINE void GH_PMU_set_IRQ_EN_MASK_ADC_EN(U8 data)
{
    GH_PMU_IRQ_EN_MASK_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_EN_MASK;
    d.bitc.adc_en = data;
    *(volatile U32 *)REG_PMU_IRQ_EN_MASK = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_EN_MASK_ADC_EN] <-- 0x%08x\n",
                        REG_PMU_IRQ_EN_MASK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_IRQ_EN_MASK_ADC_EN(void)
{
    GH_PMU_IRQ_EN_MASK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_EN_MASK);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_EN_MASK_ADC_EN] --> 0x%08x\n",
                        REG_PMU_IRQ_EN_MASK,value);
    #endif
    return tmp_value.bitc.adc_en;
}
GH_INLINE void GH_PMU_set_IRQ_EN_MASK_IRT_EN(U8 data)
{
    GH_PMU_IRQ_EN_MASK_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_EN_MASK;
    d.bitc.irt_en = data;
    *(volatile U32 *)REG_PMU_IRQ_EN_MASK = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_EN_MASK_IRT_EN] <-- 0x%08x\n",
                        REG_PMU_IRQ_EN_MASK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_IRQ_EN_MASK_IRT_EN(void)
{
    GH_PMU_IRQ_EN_MASK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_EN_MASK);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_EN_MASK_IRT_EN] --> 0x%08x\n",
                        REG_PMU_IRQ_EN_MASK,value);
    #endif
    return tmp_value.bitc.irt_en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_CLR_RTC (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_IRQ_CLR_RTC'. */
void GH_PMU_set_IRQ_CLR_RTC(U32 data);
/*! \brief Reads the register 'PMU_IRQ_CLR_RTC'. */
U32  GH_PMU_get_IRQ_CLR_RTC(void);
/*! \brief Writes the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_RTC'. */
void GH_PMU_set_IRQ_CLR_RTC_IRQCLR(U8 data);
/*! \brief Reads the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_RTC'. */
U8   GH_PMU_get_IRQ_CLR_RTC_IRQCLR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_IRQ_CLR_RTC(U32 data)
{
    *(volatile U32 *)REG_PMU_IRQ_CLR_RTC = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_CLR_RTC] <-- 0x%08x\n",
                        REG_PMU_IRQ_CLR_RTC,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_IRQ_CLR_RTC(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_CLR_RTC);

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_CLR_RTC] --> 0x%08x\n",
                        REG_PMU_IRQ_CLR_RTC,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_IRQ_CLR_RTC_IRQCLR(U8 data)
{
    GH_PMU_IRQ_CLR_RTC_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_CLR_RTC;
    d.bitc.irqclr = data;
    *(volatile U32 *)REG_PMU_IRQ_CLR_RTC = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_CLR_RTC_IRQCLR] <-- 0x%08x\n",
                        REG_PMU_IRQ_CLR_RTC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_IRQ_CLR_RTC_IRQCLR(void)
{
    GH_PMU_IRQ_CLR_RTC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_CLR_RTC);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_CLR_RTC_IRQCLR] --> 0x%08x\n",
                        REG_PMU_IRQ_CLR_RTC,value);
    #endif
    return tmp_value.bitc.irqclr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_CLR_IRR (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_IRQ_CLR_IRR'. */
void GH_PMU_set_IRQ_CLR_IRR(U32 data);
/*! \brief Reads the register 'PMU_IRQ_CLR_IRR'. */
U32  GH_PMU_get_IRQ_CLR_IRR(void);
/*! \brief Writes the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_IRR'. */
void GH_PMU_set_IRQ_CLR_IRR_IRQCLR(U8 data);
/*! \brief Reads the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_IRR'. */
U8   GH_PMU_get_IRQ_CLR_IRR_IRQCLR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_IRQ_CLR_IRR(U32 data)
{
    *(volatile U32 *)REG_PMU_IRQ_CLR_IRR = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_CLR_IRR] <-- 0x%08x\n",
                        REG_PMU_IRQ_CLR_IRR,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_IRQ_CLR_IRR(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_CLR_IRR);

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_CLR_IRR] --> 0x%08x\n",
                        REG_PMU_IRQ_CLR_IRR,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_IRQ_CLR_IRR_IRQCLR(U8 data)
{
    GH_PMU_IRQ_CLR_IRR_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_CLR_IRR;
    d.bitc.irqclr = data;
    *(volatile U32 *)REG_PMU_IRQ_CLR_IRR = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_CLR_IRR_IRQCLR] <-- 0x%08x\n",
                        REG_PMU_IRQ_CLR_IRR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_IRQ_CLR_IRR_IRQCLR(void)
{
    GH_PMU_IRQ_CLR_IRR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_CLR_IRR);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_CLR_IRR_IRQCLR] --> 0x%08x\n",
                        REG_PMU_IRQ_CLR_IRR,value);
    #endif
    return tmp_value.bitc.irqclr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_CLR_FPC (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_IRQ_CLR_FPC'. */
void GH_PMU_set_IRQ_CLR_FPC(U32 data);
/*! \brief Reads the register 'PMU_IRQ_CLR_FPC'. */
U32  GH_PMU_get_IRQ_CLR_FPC(void);
/*! \brief Writes the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_FPC'. */
void GH_PMU_set_IRQ_CLR_FPC_IRQCLR(U8 data);
/*! \brief Reads the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_FPC'. */
U8   GH_PMU_get_IRQ_CLR_FPC_IRQCLR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_IRQ_CLR_FPC(U32 data)
{
    *(volatile U32 *)REG_PMU_IRQ_CLR_FPC = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_CLR_FPC] <-- 0x%08x\n",
                        REG_PMU_IRQ_CLR_FPC,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_IRQ_CLR_FPC(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_CLR_FPC);

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_CLR_FPC] --> 0x%08x\n",
                        REG_PMU_IRQ_CLR_FPC,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_IRQ_CLR_FPC_IRQCLR(U8 data)
{
    GH_PMU_IRQ_CLR_FPC_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_CLR_FPC;
    d.bitc.irqclr = data;
    *(volatile U32 *)REG_PMU_IRQ_CLR_FPC = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_CLR_FPC_IRQCLR] <-- 0x%08x\n",
                        REG_PMU_IRQ_CLR_FPC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_IRQ_CLR_FPC_IRQCLR(void)
{
    GH_PMU_IRQ_CLR_FPC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_CLR_FPC);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_CLR_FPC_IRQCLR] --> 0x%08x\n",
                        REG_PMU_IRQ_CLR_FPC,value);
    #endif
    return tmp_value.bitc.irqclr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_CLR_GPIO (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_IRQ_CLR_GPIO'. */
void GH_PMU_set_IRQ_CLR_GPIO(U32 data);
/*! \brief Reads the register 'PMU_IRQ_CLR_GPIO'. */
U32  GH_PMU_get_IRQ_CLR_GPIO(void);
/*! \brief Writes the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_GPIO'. */
void GH_PMU_set_IRQ_CLR_GPIO_IRQCLR(U8 data);
/*! \brief Reads the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_GPIO'. */
U8   GH_PMU_get_IRQ_CLR_GPIO_IRQCLR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_IRQ_CLR_GPIO(U32 data)
{
    *(volatile U32 *)REG_PMU_IRQ_CLR_GPIO = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_CLR_GPIO] <-- 0x%08x\n",
                        REG_PMU_IRQ_CLR_GPIO,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_IRQ_CLR_GPIO(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_CLR_GPIO);

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_CLR_GPIO] --> 0x%08x\n",
                        REG_PMU_IRQ_CLR_GPIO,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_IRQ_CLR_GPIO_IRQCLR(U8 data)
{
    GH_PMU_IRQ_CLR_GPIO_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_CLR_GPIO;
    d.bitc.irqclr = data;
    *(volatile U32 *)REG_PMU_IRQ_CLR_GPIO = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_CLR_GPIO_IRQCLR] <-- 0x%08x\n",
                        REG_PMU_IRQ_CLR_GPIO,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_IRQ_CLR_GPIO_IRQCLR(void)
{
    GH_PMU_IRQ_CLR_GPIO_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_CLR_GPIO);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_CLR_GPIO_IRQCLR] --> 0x%08x\n",
                        REG_PMU_IRQ_CLR_GPIO,value);
    #endif
    return tmp_value.bitc.irqclr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_CLR_CEC (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_IRQ_CLR_CEC'. */
void GH_PMU_set_IRQ_CLR_CEC(U32 data);
/*! \brief Reads the register 'PMU_IRQ_CLR_CEC'. */
U32  GH_PMU_get_IRQ_CLR_CEC(void);
/*! \brief Writes the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_CEC'. */
void GH_PMU_set_IRQ_CLR_CEC_IRQCLR(U8 data);
/*! \brief Reads the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_CEC'. */
U8   GH_PMU_get_IRQ_CLR_CEC_IRQCLR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_IRQ_CLR_CEC(U32 data)
{
    *(volatile U32 *)REG_PMU_IRQ_CLR_CEC = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_CLR_CEC] <-- 0x%08x\n",
                        REG_PMU_IRQ_CLR_CEC,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_IRQ_CLR_CEC(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_CLR_CEC);

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_CLR_CEC] --> 0x%08x\n",
                        REG_PMU_IRQ_CLR_CEC,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_IRQ_CLR_CEC_IRQCLR(U8 data)
{
    GH_PMU_IRQ_CLR_CEC_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_CLR_CEC;
    d.bitc.irqclr = data;
    *(volatile U32 *)REG_PMU_IRQ_CLR_CEC = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_CLR_CEC_IRQCLR] <-- 0x%08x\n",
                        REG_PMU_IRQ_CLR_CEC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_IRQ_CLR_CEC_IRQCLR(void)
{
    GH_PMU_IRQ_CLR_CEC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_CLR_CEC);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_CLR_CEC_IRQCLR] --> 0x%08x\n",
                        REG_PMU_IRQ_CLR_CEC,value);
    #endif
    return tmp_value.bitc.irqclr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_CLR_ADC (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_IRQ_CLR_ADC'. */
void GH_PMU_set_IRQ_CLR_ADC(U32 data);
/*! \brief Reads the register 'PMU_IRQ_CLR_ADC'. */
U32  GH_PMU_get_IRQ_CLR_ADC(void);
/*! \brief Writes the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_ADC'. */
void GH_PMU_set_IRQ_CLR_ADC_IRQCLR(U8 data);
/*! \brief Reads the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_ADC'. */
U8   GH_PMU_get_IRQ_CLR_ADC_IRQCLR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_IRQ_CLR_ADC(U32 data)
{
    *(volatile U32 *)REG_PMU_IRQ_CLR_ADC = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_CLR_ADC] <-- 0x%08x\n",
                        REG_PMU_IRQ_CLR_ADC,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_IRQ_CLR_ADC(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_CLR_ADC);

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_CLR_ADC] --> 0x%08x\n",
                        REG_PMU_IRQ_CLR_ADC,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_IRQ_CLR_ADC_IRQCLR(U8 data)
{
    GH_PMU_IRQ_CLR_ADC_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_CLR_ADC;
    d.bitc.irqclr = data;
    *(volatile U32 *)REG_PMU_IRQ_CLR_ADC = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_CLR_ADC_IRQCLR] <-- 0x%08x\n",
                        REG_PMU_IRQ_CLR_ADC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_IRQ_CLR_ADC_IRQCLR(void)
{
    GH_PMU_IRQ_CLR_ADC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_CLR_ADC);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_CLR_ADC_IRQCLR] --> 0x%08x\n",
                        REG_PMU_IRQ_CLR_ADC,value);
    #endif
    return tmp_value.bitc.irqclr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_CLR_IRT (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_IRQ_CLR_IRT'. */
void GH_PMU_set_IRQ_CLR_IRT(U32 data);
/*! \brief Reads the register 'PMU_IRQ_CLR_IRT'. */
U32  GH_PMU_get_IRQ_CLR_IRT(void);
/*! \brief Writes the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_IRT'. */
void GH_PMU_set_IRQ_CLR_IRT_IRQCLR(U8 data);
/*! \brief Reads the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_IRT'. */
U8   GH_PMU_get_IRQ_CLR_IRT_IRQCLR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_IRQ_CLR_IRT(U32 data)
{
    *(volatile U32 *)REG_PMU_IRQ_CLR_IRT = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_CLR_IRT] <-- 0x%08x\n",
                        REG_PMU_IRQ_CLR_IRT,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_IRQ_CLR_IRT(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_CLR_IRT);

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_CLR_IRT] --> 0x%08x\n",
                        REG_PMU_IRQ_CLR_IRT,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_IRQ_CLR_IRT_IRQCLR(U8 data)
{
    GH_PMU_IRQ_CLR_IRT_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_CLR_IRT;
    d.bitc.irqclr = data;
    *(volatile U32 *)REG_PMU_IRQ_CLR_IRT = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_CLR_IRT_IRQCLR] <-- 0x%08x\n",
                        REG_PMU_IRQ_CLR_IRT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_IRQ_CLR_IRT_IRQCLR(void)
{
    GH_PMU_IRQ_CLR_IRT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_CLR_IRT);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_CLR_IRT_IRQCLR] --> 0x%08x\n",
                        REG_PMU_IRQ_CLR_IRT,value);
    #endif
    return tmp_value.bitc.irqclr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_STATUS (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_IRQ_STATUS'. */
void GH_PMU_set_IRQ_STATUS(U32 data);
/*! \brief Reads the register 'PMU_IRQ_STATUS'. */
U32  GH_PMU_get_IRQ_STATUS(void);
/*! \brief Writes the bit group 'RTC_IRQ' of register 'PMU_IRQ_STATUS'. */
void GH_PMU_set_IRQ_STATUS_RTC_IRQ(U8 data);
/*! \brief Reads the bit group 'RTC_IRQ' of register 'PMU_IRQ_STATUS'. */
U8   GH_PMU_get_IRQ_STATUS_RTC_IRQ(void);
/*! \brief Writes the bit group 'IRR_IRQ' of register 'PMU_IRQ_STATUS'. */
void GH_PMU_set_IRQ_STATUS_IRR_IRQ(U8 data);
/*! \brief Reads the bit group 'IRR_IRQ' of register 'PMU_IRQ_STATUS'. */
U8   GH_PMU_get_IRQ_STATUS_IRR_IRQ(void);
/*! \brief Writes the bit group 'FPC_IRQ' of register 'PMU_IRQ_STATUS'. */
void GH_PMU_set_IRQ_STATUS_FPC_IRQ(U8 data);
/*! \brief Reads the bit group 'FPC_IRQ' of register 'PMU_IRQ_STATUS'. */
U8   GH_PMU_get_IRQ_STATUS_FPC_IRQ(void);
/*! \brief Writes the bit group 'GPIO_IRQ' of register 'PMU_IRQ_STATUS'. */
void GH_PMU_set_IRQ_STATUS_GPIO_IRQ(U8 data);
/*! \brief Reads the bit group 'GPIO_IRQ' of register 'PMU_IRQ_STATUS'. */
U8   GH_PMU_get_IRQ_STATUS_GPIO_IRQ(void);
/*! \brief Writes the bit group 'CEC_IRQ' of register 'PMU_IRQ_STATUS'. */
void GH_PMU_set_IRQ_STATUS_CEC_IRQ(U8 data);
/*! \brief Reads the bit group 'CEC_IRQ' of register 'PMU_IRQ_STATUS'. */
U8   GH_PMU_get_IRQ_STATUS_CEC_IRQ(void);
/*! \brief Writes the bit group 'ADC_IRQ' of register 'PMU_IRQ_STATUS'. */
void GH_PMU_set_IRQ_STATUS_ADC_IRQ(U8 data);
/*! \brief Reads the bit group 'ADC_IRQ' of register 'PMU_IRQ_STATUS'. */
U8   GH_PMU_get_IRQ_STATUS_ADC_IRQ(void);
/*! \brief Writes the bit group 'IRT_IRQ' of register 'PMU_IRQ_STATUS'. */
void GH_PMU_set_IRQ_STATUS_IRT_IRQ(U8 data);
/*! \brief Reads the bit group 'IRT_IRQ' of register 'PMU_IRQ_STATUS'. */
U8   GH_PMU_get_IRQ_STATUS_IRT_IRQ(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_IRQ_STATUS(U32 data)
{
    *(volatile U32 *)REG_PMU_IRQ_STATUS = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_STATUS] <-- 0x%08x\n",
                        REG_PMU_IRQ_STATUS,data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_IRQ_STATUS(void)
{
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_STATUS);

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_STATUS] --> 0x%08x\n",
                        REG_PMU_IRQ_STATUS,value);
    #endif
    return value;
}
GH_INLINE void GH_PMU_set_IRQ_STATUS_RTC_IRQ(U8 data)
{
    GH_PMU_IRQ_STATUS_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_STATUS;
    d.bitc.rtc_irq = data;
    *(volatile U32 *)REG_PMU_IRQ_STATUS = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_STATUS_RTC_IRQ] <-- 0x%08x\n",
                        REG_PMU_IRQ_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_IRQ_STATUS_RTC_IRQ(void)
{
    GH_PMU_IRQ_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_STATUS);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_STATUS_RTC_IRQ] --> 0x%08x\n",
                        REG_PMU_IRQ_STATUS,value);
    #endif
    return tmp_value.bitc.rtc_irq;
}
GH_INLINE void GH_PMU_set_IRQ_STATUS_IRR_IRQ(U8 data)
{
    GH_PMU_IRQ_STATUS_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_STATUS;
    d.bitc.irr_irq = data;
    *(volatile U32 *)REG_PMU_IRQ_STATUS = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_STATUS_IRR_IRQ] <-- 0x%08x\n",
                        REG_PMU_IRQ_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_IRQ_STATUS_IRR_IRQ(void)
{
    GH_PMU_IRQ_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_STATUS);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_STATUS_IRR_IRQ] --> 0x%08x\n",
                        REG_PMU_IRQ_STATUS,value);
    #endif
    return tmp_value.bitc.irr_irq;
}
GH_INLINE void GH_PMU_set_IRQ_STATUS_FPC_IRQ(U8 data)
{
    GH_PMU_IRQ_STATUS_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_STATUS;
    d.bitc.fpc_irq = data;
    *(volatile U32 *)REG_PMU_IRQ_STATUS = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_STATUS_FPC_IRQ] <-- 0x%08x\n",
                        REG_PMU_IRQ_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_IRQ_STATUS_FPC_IRQ(void)
{
    GH_PMU_IRQ_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_STATUS);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_STATUS_FPC_IRQ] --> 0x%08x\n",
                        REG_PMU_IRQ_STATUS,value);
    #endif
    return tmp_value.bitc.fpc_irq;
}
GH_INLINE void GH_PMU_set_IRQ_STATUS_GPIO_IRQ(U8 data)
{
    GH_PMU_IRQ_STATUS_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_STATUS;
    d.bitc.gpio_irq = data;
    *(volatile U32 *)REG_PMU_IRQ_STATUS = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_STATUS_GPIO_IRQ] <-- 0x%08x\n",
                        REG_PMU_IRQ_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_IRQ_STATUS_GPIO_IRQ(void)
{
    GH_PMU_IRQ_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_STATUS);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_STATUS_GPIO_IRQ] --> 0x%08x\n",
                        REG_PMU_IRQ_STATUS,value);
    #endif
    return tmp_value.bitc.gpio_irq;
}
GH_INLINE void GH_PMU_set_IRQ_STATUS_CEC_IRQ(U8 data)
{
    GH_PMU_IRQ_STATUS_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_STATUS;
    d.bitc.cec_irq = data;
    *(volatile U32 *)REG_PMU_IRQ_STATUS = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_STATUS_CEC_IRQ] <-- 0x%08x\n",
                        REG_PMU_IRQ_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_IRQ_STATUS_CEC_IRQ(void)
{
    GH_PMU_IRQ_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_STATUS);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_STATUS_CEC_IRQ] --> 0x%08x\n",
                        REG_PMU_IRQ_STATUS,value);
    #endif
    return tmp_value.bitc.cec_irq;
}
GH_INLINE void GH_PMU_set_IRQ_STATUS_ADC_IRQ(U8 data)
{
    GH_PMU_IRQ_STATUS_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_STATUS;
    d.bitc.adc_irq = data;
    *(volatile U32 *)REG_PMU_IRQ_STATUS = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_STATUS_ADC_IRQ] <-- 0x%08x\n",
                        REG_PMU_IRQ_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_IRQ_STATUS_ADC_IRQ(void)
{
    GH_PMU_IRQ_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_STATUS);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_STATUS_ADC_IRQ] --> 0x%08x\n",
                        REG_PMU_IRQ_STATUS,value);
    #endif
    return tmp_value.bitc.adc_irq;
}
GH_INLINE void GH_PMU_set_IRQ_STATUS_IRT_IRQ(U8 data)
{
    GH_PMU_IRQ_STATUS_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_STATUS;
    d.bitc.irt_irq = data;
    *(volatile U32 *)REG_PMU_IRQ_STATUS = d.all;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_IRQ_STATUS_IRT_IRQ] <-- 0x%08x\n",
                        REG_PMU_IRQ_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PMU_get_IRQ_STATUS_IRT_IRQ(void)
{
    GH_PMU_IRQ_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_STATUS);

    tmp_value.all = value;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_IRQ_STATUS_IRT_IRQ] --> 0x%08x\n",
                        REG_PMU_IRQ_STATUS,value);
    #endif
    return tmp_value.bitc.irt_irq;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PMU_C51_LOADCODE_ADDR (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PMU_C51_LOADCODE_ADDR'. */
void GH_PMU_set_C51_LOADCODE_ADDR(U16 index, U32 data);
/*! \brief Reads the register 'PMU_C51_LOADCODE_ADDR'. */
U32  GH_PMU_get_C51_LOADCODE_ADDR(U16 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PMU_set_C51_LOADCODE_ADDR(U16 index, U32 data)
{
    *(volatile U32 *)(REG_PMU_C51_LOADCODE_ADDR + index * FIO_MOFFSET(PMU,4)) = data;
    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PMU_set_C51_LOADCODE_ADDR] <-- 0x%08x\n",
                        (REG_PMU_C51_LOADCODE_ADDR + index * FIO_MOFFSET(PMU,4)),data,data);
    #endif
}
GH_INLINE U32  GH_PMU_get_C51_LOADCODE_ADDR(U16 index)
{
    U32 value = (*(volatile U32 *)(REG_PMU_C51_LOADCODE_ADDR + index * FIO_MOFFSET(PMU,4)));

    #if GH_PMU_ENABLE_DEBUG_PRINT
    GH_PMU_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PMU_get_C51_LOADCODE_ADDR] --> 0x%08x\n",
                        (REG_PMU_C51_LOADCODE_ADDR + index * FIO_MOFFSET(PMU,4)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_PMU_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_PMU_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

