/*!
*******************************************************************************
**
** \file      gh_pmu.h
**
** \brief     Power Management Unit.
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
        U32                             : 30;
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

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG1 (read/write)                                     */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG3 (read/write)                                     */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG7 (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_SYS_REG_CFG7'. */
void GH_PMU_set_SYS_REG_CFG7(U32 data);
/*! \brief Reads the register 'PMU_SYS_REG_CFG7'. */
U32  GH_PMU_get_SYS_REG_CFG7(void);
/*! \brief Writes the bit group 'POWER_DOWN' of register 'PMU_SYS_REG_CFG7'. */
void GH_PMU_set_SYS_REG_CFG7_POWER_DOWN(U8 data);
/*! \brief Reads the bit group 'POWER_DOWN' of register 'PMU_SYS_REG_CFG7'. */
U8   GH_PMU_get_SYS_REG_CFG7_POWER_DOWN(void);

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG8 (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_SYS_REG_CFG8'. */
void GH_PMU_set_SYS_REG_CFG8(U32 data);
/*! \brief Reads the register 'PMU_SYS_REG_CFG8'. */
U32  GH_PMU_get_SYS_REG_CFG8(void);
/*! \brief Writes the bit group 'WD_LOW_VALUE' of register 'PMU_SYS_REG_CFG8'. */
void GH_PMU_set_SYS_REG_CFG8_WD_LOW_VALUE(U8 data);
/*! \brief Reads the bit group 'WD_LOW_VALUE' of register 'PMU_SYS_REG_CFG8'. */
U8   GH_PMU_get_SYS_REG_CFG8_WD_LOW_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG9 (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_SYS_REG_CFG9'. */
void GH_PMU_set_SYS_REG_CFG9(U32 data);
/*! \brief Reads the register 'PMU_SYS_REG_CFG9'. */
U32  GH_PMU_get_SYS_REG_CFG9(void);
/*! \brief Writes the bit group 'WD_HIGH_VALUE' of register 'PMU_SYS_REG_CFG9'. */
void GH_PMU_set_SYS_REG_CFG9_WD_HIGH_VALUE(U8 data);
/*! \brief Reads the bit group 'WD_HIGH_VALUE' of register 'PMU_SYS_REG_CFG9'. */
U8   GH_PMU_get_SYS_REG_CFG9_WD_HIGH_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG10 (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_SYS_REG_CFG10'. */
void GH_PMU_set_SYS_REG_CFG10(U32 data);
/*! \brief Reads the register 'PMU_SYS_REG_CFG10'. */
U32  GH_PMU_get_SYS_REG_CFG10(void);
/*! \brief Writes the bit group 'WD_UPDATE' of register 'PMU_SYS_REG_CFG10'. */
void GH_PMU_set_SYS_REG_CFG10_WD_UPDATE(U8 data);
/*! \brief Reads the bit group 'WD_UPDATE' of register 'PMU_SYS_REG_CFG10'. */
U8   GH_PMU_get_SYS_REG_CFG10_WD_UPDATE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG11 (read/write)                                    */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG16 (read/write)                                    */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG17 (read/write)                                    */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG18 (read/write)                                    */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_EN_MASK (read/write)                                      */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_CLR_RTC (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRQ_CLR_RTC'. */
void GH_PMU_set_IRQ_CLR_RTC(U32 data);
/*! \brief Reads the register 'PMU_IRQ_CLR_RTC'. */
U32  GH_PMU_get_IRQ_CLR_RTC(void);
/*! \brief Writes the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_RTC'. */
void GH_PMU_set_IRQ_CLR_RTC_IRQCLR(U8 data);
/*! \brief Reads the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_RTC'. */
U8   GH_PMU_get_IRQ_CLR_RTC_IRQCLR(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_CLR_IRR (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRQ_CLR_IRR'. */
void GH_PMU_set_IRQ_CLR_IRR(U32 data);
/*! \brief Reads the register 'PMU_IRQ_CLR_IRR'. */
U32  GH_PMU_get_IRQ_CLR_IRR(void);
/*! \brief Writes the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_IRR'. */
void GH_PMU_set_IRQ_CLR_IRR_IRQCLR(U8 data);
/*! \brief Reads the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_IRR'. */
U8   GH_PMU_get_IRQ_CLR_IRR_IRQCLR(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_CLR_FPC (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRQ_CLR_FPC'. */
void GH_PMU_set_IRQ_CLR_FPC(U32 data);
/*! \brief Reads the register 'PMU_IRQ_CLR_FPC'. */
U32  GH_PMU_get_IRQ_CLR_FPC(void);
/*! \brief Writes the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_FPC'. */
void GH_PMU_set_IRQ_CLR_FPC_IRQCLR(U8 data);
/*! \brief Reads the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_FPC'. */
U8   GH_PMU_get_IRQ_CLR_FPC_IRQCLR(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_CLR_GPIO (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRQ_CLR_GPIO'. */
void GH_PMU_set_IRQ_CLR_GPIO(U32 data);
/*! \brief Reads the register 'PMU_IRQ_CLR_GPIO'. */
U32  GH_PMU_get_IRQ_CLR_GPIO(void);
/*! \brief Writes the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_GPIO'. */
void GH_PMU_set_IRQ_CLR_GPIO_IRQCLR(U8 data);
/*! \brief Reads the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_GPIO'. */
U8   GH_PMU_get_IRQ_CLR_GPIO_IRQCLR(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_CLR_CEC (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRQ_CLR_CEC'. */
void GH_PMU_set_IRQ_CLR_CEC(U32 data);
/*! \brief Reads the register 'PMU_IRQ_CLR_CEC'. */
U32  GH_PMU_get_IRQ_CLR_CEC(void);
/*! \brief Writes the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_CEC'. */
void GH_PMU_set_IRQ_CLR_CEC_IRQCLR(U8 data);
/*! \brief Reads the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_CEC'. */
U8   GH_PMU_get_IRQ_CLR_CEC_IRQCLR(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_CLR_ADC (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRQ_CLR_ADC'. */
void GH_PMU_set_IRQ_CLR_ADC(U32 data);
/*! \brief Reads the register 'PMU_IRQ_CLR_ADC'. */
U32  GH_PMU_get_IRQ_CLR_ADC(void);
/*! \brief Writes the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_ADC'. */
void GH_PMU_set_IRQ_CLR_ADC_IRQCLR(U8 data);
/*! \brief Reads the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_ADC'. */
U8   GH_PMU_get_IRQ_CLR_ADC_IRQCLR(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_CLR_IRT (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRQ_CLR_IRT'. */
void GH_PMU_set_IRQ_CLR_IRT(U32 data);
/*! \brief Reads the register 'PMU_IRQ_CLR_IRT'. */
U32  GH_PMU_get_IRQ_CLR_IRT(void);
/*! \brief Writes the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_IRT'. */
void GH_PMU_set_IRQ_CLR_IRT_IRQCLR(U8 data);
/*! \brief Reads the bit group 'IRQCLR' of register 'PMU_IRQ_CLR_IRT'. */
U8   GH_PMU_get_IRQ_CLR_IRT_IRQCLR(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_STATUS (read/write)                                       */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register PMU_C51_LOADCODE_ADDR (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_C51_LOADCODE_ADDR'. */
void GH_PMU_set_C51_LOADCODE_ADDR(U16 index, U32 data);
/*! \brief Reads the register 'PMU_C51_LOADCODE_ADDR'. */
U32  GH_PMU_get_C51_LOADCODE_ADDR(U16 index);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_PMU_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_pmu.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_PMU_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

