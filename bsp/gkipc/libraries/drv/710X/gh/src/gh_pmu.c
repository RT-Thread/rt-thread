/******************************************************************************
**
** \file      gh_pmu.c
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
#ifndef SRC_INLINE
#include "gh_pmu.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_PMU_SYS_REG_CFG0_REAL                           FIO_ADDRESS(PMU,0x6008A000) /* read/write */
#define REG_PMU_SYS_REG_CFG1_REAL                           FIO_ADDRESS(PMU,0x6008A004) /* read/write */
#define REG_PMU_SYS_REG_CFG3_REAL                           FIO_ADDRESS(PMU,0x6008A00C) /* read/write */
#define REG_PMU_SYS_REG_CFG7_REAL                           FIO_ADDRESS(PMU,0x6008A01C) /* read/write */
#define REG_PMU_SYS_REG_CFG8_REAL                           FIO_ADDRESS(PMU,0x6008A020) /* read/write */
#define REG_PMU_SYS_REG_CFG9_REAL                           FIO_ADDRESS(PMU,0x6008A024) /* read/write */
#define REG_PMU_SYS_REG_CFG10_REAL                          FIO_ADDRESS(PMU,0x6008A028) /* read/write */
#define REG_PMU_SYS_REG_CFG11_REAL                          FIO_ADDRESS(PMU,0x6008A02C) /* read/write */
#define REG_PMU_SYS_REG_CFG16_REAL                          FIO_ADDRESS(PMU,0x6008A040) /* read/write */
#define REG_PMU_SYS_REG_CFG17_REAL                          FIO_ADDRESS(PMU,0x6008A044) /* read/write */
#define REG_PMU_SYS_REG_CFG18_REAL                          FIO_ADDRESS(PMU,0x6008A048) /* read/write */
#define REG_PMU_IRQ_EN_MASK_REAL                            FIO_ADDRESS(PMU,0x6008DC00) /* read/write */
#define REG_PMU_IRQ_CLR_RTC_REAL                            FIO_ADDRESS(PMU,0x6008DC20) /* read/write */
#define REG_PMU_IRQ_CLR_IRR_REAL                            FIO_ADDRESS(PMU,0x6008DC24) /* read/write */
#define REG_PMU_IRQ_CLR_FPC_REAL                            FIO_ADDRESS(PMU,0x6008DC28) /* read/write */
#define REG_PMU_IRQ_CLR_GPIO_REAL                           FIO_ADDRESS(PMU,0x6008DC2C) /* read/write */
#define REG_PMU_IRQ_CLR_CEC_REAL                            FIO_ADDRESS(PMU,0x6008DC30) /* read/write */
#define REG_PMU_IRQ_CLR_ADC_REAL                            FIO_ADDRESS(PMU,0x6008DC34) /* read/write */
#define REG_PMU_IRQ_CLR_IRT_REAL                            FIO_ADDRESS(PMU,0x6008DC38) /* read/write */
#define REG_PMU_IRQ_STATUS_REAL                             FIO_ADDRESS(PMU,0x6008DC40) /* read/write */
#define REG_PMU_C51_LOADCODE_ADDR_REAL                      FIO_ADDRESS(PMU,0x600C0000) /* read/write */

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
} GH_PMU_SYS_REG_CFG0_REAL_S;

typedef union { /* PMU_SYS_REG_CFG1 */
    U32 all;
    struct {
        U32                             : 4;
        U32 gpio4                       : 1;
        U32                             : 2;
        U32 gpio7                       : 1;
        U32                             : 24;
    } bitc;
} GH_PMU_SYS_REG_CFG1_REAL_S;

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
} GH_PMU_SYS_REG_CFG3_REAL_S;

typedef union { /* PMU_SYS_REG_CFG7 */
    U32 all;
    struct {
        U32 power_down                  : 1;
        U32                             : 31;
    } bitc;
} GH_PMU_SYS_REG_CFG7_REAL_S;

typedef union { /* PMU_SYS_REG_CFG8 */
    U32 all;
    struct {
        U32 wd_low_value                : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_SYS_REG_CFG8_REAL_S;

typedef union { /* PMU_SYS_REG_CFG9 */
    U32 all;
    struct {
        U32 wd_high_value               : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_SYS_REG_CFG9_REAL_S;

typedef union { /* PMU_SYS_REG_CFG10 */
    U32 all;
    struct {
        U32 wd_update                   : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_SYS_REG_CFG10_REAL_S;

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
} GH_PMU_SYS_REG_CFG11_REAL_S;

typedef union { /* PMU_SYS_REG_CFG16 */
    U32 all;
    struct {
        U32 xclk_iopad                  : 1;
        U32 rtc_iopad                   : 1;
        U32                             : 30;
    } bitc;
} GH_PMU_SYS_REG_CFG16_REAL_S;

typedef union { /* PMU_SYS_REG_CFG17 */
    U32 all;
    struct {
        U32 rtc_clk_sel                 : 1;
        U32 rtc_cnt_reset               : 1;
        U32                             : 30;
    } bitc;
} GH_PMU_SYS_REG_CFG17_REAL_S;

typedef union { /* PMU_SYS_REG_CFG18 */
    U32 all;
    struct {
        U32 e                           : 2;
        U32 sr                          : 1;
        U32 smt                         : 1;
        U32 p                           : 2;
        U32                             : 26;
    } bitc;
} GH_PMU_SYS_REG_CFG18_REAL_S;

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
} GH_PMU_IRQ_EN_MASK_REAL_S;

typedef union { /* PMU_IRQ_CLR_RTC */
    U32 all;
    struct {
        U32 irqclr                      : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRQ_CLR_RTC_REAL_S;

typedef union { /* PMU_IRQ_CLR_IRR */
    U32 all;
    struct {
        U32 irqclr                      : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRQ_CLR_IRR_REAL_S;

typedef union { /* PMU_IRQ_CLR_FPC */
    U32 all;
    struct {
        U32 irqclr                      : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRQ_CLR_FPC_REAL_S;

typedef union { /* PMU_IRQ_CLR_GPIO */
    U32 all;
    struct {
        U32 irqclr                      : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRQ_CLR_GPIO_REAL_S;

typedef union { /* PMU_IRQ_CLR_CEC */
    U32 all;
    struct {
        U32 irqclr                      : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRQ_CLR_CEC_REAL_S;

typedef union { /* PMU_IRQ_CLR_ADC */
    U32 all;
    struct {
        U32 irqclr                      : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRQ_CLR_ADC_REAL_S;

typedef union { /* PMU_IRQ_CLR_IRT */
    U32 all;
    struct {
        U32 irqclr                      : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRQ_CLR_IRT_REAL_S;

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
} GH_PMU_IRQ_STATUS_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG0 (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_set_SYS_REG_CFG0(U32 data)
{
    GH_PMU_SYS_REG_CFG0_REAL_S real;
    GH_PMU_SYS_REG_CFG0_S dummy;
    dummy.all = data ;
    real.bitc.pmu_en = dummy.bitc.pmu_en;
    real.bitc.sys_reset = dummy.bitc.sys_reset;
    real.bitc.sw_reset = dummy.bitc.sw_reset;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG0_REAL = real.all;
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG0(void)
{
    GH_PMU_SYS_REG_CFG0_REAL_S real;
    GH_PMU_SYS_REG_CFG0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_PMU_SYS_REG_CFG0_REAL);

    dummy.bitc.pmu_en = real.bitc.pmu_en;
    dummy.bitc.sys_reset = real.bitc.sys_reset;
    dummy.bitc.sw_reset = real.bitc.sw_reset;
    return dummy.all;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG0_PMU_EN(U8 data)
{
    GH_PMU_SYS_REG_CFG0_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG0_REAL;
    d.bitc.pmu_en = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG0_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG0_PMU_EN(void)
{
    GH_PMU_SYS_REG_CFG0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pmu_en;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG0_SYS_RESET(U8 data)
{
    GH_PMU_SYS_REG_CFG0_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG0_REAL;
    d.bitc.sys_reset = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG0_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG0_SYS_RESET(void)
{
    GH_PMU_SYS_REG_CFG0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sys_reset;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG0_SW_RESET(U8 data)
{
    GH_PMU_SYS_REG_CFG0_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG0_REAL;
    d.bitc.sw_reset = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG0_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG0_SW_RESET(void)
{
    GH_PMU_SYS_REG_CFG0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sw_reset;
}

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG1 (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_set_SYS_REG_CFG1(U32 data)
{
    GH_PMU_SYS_REG_CFG1_REAL_S real;
    GH_PMU_SYS_REG_CFG1_S dummy;
    dummy.all = data ;
    real.bitc.gpio4 = dummy.bitc.gpio4;
    real.bitc.gpio7 = dummy.bitc.gpio7;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG1_REAL = real.all;
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG1(void)
{
    GH_PMU_SYS_REG_CFG1_REAL_S real;
    GH_PMU_SYS_REG_CFG1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_PMU_SYS_REG_CFG1_REAL);

    dummy.bitc.gpio4 = real.bitc.gpio4;
    dummy.bitc.gpio7 = real.bitc.gpio7;
    return dummy.all;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG1_GPIO4(U8 data)
{
    GH_PMU_SYS_REG_CFG1_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG1_REAL;
    d.bitc.gpio4 = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG1_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG1_GPIO4(void)
{
    GH_PMU_SYS_REG_CFG1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gpio4;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG1_GPIO7(U8 data)
{
    GH_PMU_SYS_REG_CFG1_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG1_REAL;
    d.bitc.gpio7 = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG1_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG1_GPIO7(void)
{
    GH_PMU_SYS_REG_CFG1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gpio7;
}

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG3 (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_set_SYS_REG_CFG3(U32 data)
{
    GH_PMU_SYS_REG_CFG3_REAL_S real;
    GH_PMU_SYS_REG_CFG3_S dummy;
    dummy.all = data ;
    real.bitc.cec_en = dummy.bitc.cec_en;
    real.bitc.pt6964_key_in = dummy.bitc.pt6964_key_in;
    real.bitc.ct1642_key_in = dummy.bitc.ct1642_key_in;
    real.bitc.pwr_wakeup = dummy.bitc.pwr_wakeup;
    real.bitc.ir_in = dummy.bitc.ir_in;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG3_REAL = real.all;
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG3(void)
{
    GH_PMU_SYS_REG_CFG3_REAL_S real;
    GH_PMU_SYS_REG_CFG3_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_PMU_SYS_REG_CFG3_REAL);

    dummy.bitc.cec_en = real.bitc.cec_en;
    dummy.bitc.pt6964_key_in = real.bitc.pt6964_key_in;
    dummy.bitc.ct1642_key_in = real.bitc.ct1642_key_in;
    dummy.bitc.pwr_wakeup = real.bitc.pwr_wakeup;
    dummy.bitc.ir_in = real.bitc.ir_in;
    return dummy.all;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG3_CEC_EN(U8 data)
{
    GH_PMU_SYS_REG_CFG3_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG3_REAL;
    d.bitc.cec_en = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG3_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG3_CEC_EN(void)
{
    GH_PMU_SYS_REG_CFG3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cec_en;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG3_PT6964_KEY_IN(U8 data)
{
    GH_PMU_SYS_REG_CFG3_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG3_REAL;
    d.bitc.pt6964_key_in = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG3_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG3_PT6964_KEY_IN(void)
{
    GH_PMU_SYS_REG_CFG3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pt6964_key_in;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG3_CT1642_KEY_IN(U8 data)
{
    GH_PMU_SYS_REG_CFG3_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG3_REAL;
    d.bitc.ct1642_key_in = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG3_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG3_CT1642_KEY_IN(void)
{
    GH_PMU_SYS_REG_CFG3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ct1642_key_in;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG3_PWR_WAKEUP(U8 data)
{
    GH_PMU_SYS_REG_CFG3_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG3_REAL;
    d.bitc.pwr_wakeup = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG3_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG3_PWR_WAKEUP(void)
{
    GH_PMU_SYS_REG_CFG3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pwr_wakeup;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG3_IR_IN(U8 data)
{
    GH_PMU_SYS_REG_CFG3_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG3_REAL;
    d.bitc.ir_in = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG3_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG3_IR_IN(void)
{
    GH_PMU_SYS_REG_CFG3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ir_in;
}

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG7 (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_set_SYS_REG_CFG7(U32 data)
{
    GH_PMU_SYS_REG_CFG7_REAL_S real;
    GH_PMU_SYS_REG_CFG7_S dummy;
    dummy.all = data ;
    real.bitc.power_down = dummy.bitc.power_down;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG7_REAL = real.all;
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG7(void)
{
    GH_PMU_SYS_REG_CFG7_REAL_S real;
    GH_PMU_SYS_REG_CFG7_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_PMU_SYS_REG_CFG7_REAL);

    dummy.bitc.power_down = real.bitc.power_down;
    return dummy.all;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG7_POWER_DOWN(U8 data)
{
    GH_PMU_SYS_REG_CFG7_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG7_REAL;
    d.bitc.power_down = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG7_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG7_POWER_DOWN(void)
{
    GH_PMU_SYS_REG_CFG7_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG7_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.power_down;
}

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG8 (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_set_SYS_REG_CFG8(U32 data)
{
    GH_PMU_SYS_REG_CFG8_REAL_S real;
    GH_PMU_SYS_REG_CFG8_S dummy;
    dummy.all = data ;
    real.bitc.wd_low_value = dummy.bitc.wd_low_value;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG8_REAL = real.all;
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG8(void)
{
    GH_PMU_SYS_REG_CFG8_REAL_S real;
    GH_PMU_SYS_REG_CFG8_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_PMU_SYS_REG_CFG8_REAL);

    dummy.bitc.wd_low_value = real.bitc.wd_low_value;
    return dummy.all;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG8_WD_LOW_VALUE(U8 data)
{
    GH_PMU_SYS_REG_CFG8_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG8_REAL;
    d.bitc.wd_low_value = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG8_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG8_WD_LOW_VALUE(void)
{
    GH_PMU_SYS_REG_CFG8_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG8_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.wd_low_value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG9 (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_set_SYS_REG_CFG9(U32 data)
{
    GH_PMU_SYS_REG_CFG9_REAL_S real;
    GH_PMU_SYS_REG_CFG9_S dummy;
    dummy.all = data ;
    real.bitc.wd_high_value = dummy.bitc.wd_high_value;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG9_REAL = real.all;
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG9(void)
{
    GH_PMU_SYS_REG_CFG9_REAL_S real;
    GH_PMU_SYS_REG_CFG9_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_PMU_SYS_REG_CFG9_REAL);

    dummy.bitc.wd_high_value = real.bitc.wd_high_value;
    return dummy.all;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG9_WD_HIGH_VALUE(U8 data)
{
    GH_PMU_SYS_REG_CFG9_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG9_REAL;
    d.bitc.wd_high_value = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG9_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG9_WD_HIGH_VALUE(void)
{
    GH_PMU_SYS_REG_CFG9_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG9_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.wd_high_value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG10 (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_set_SYS_REG_CFG10(U32 data)
{
    GH_PMU_SYS_REG_CFG10_REAL_S real;
    GH_PMU_SYS_REG_CFG10_S dummy;
    dummy.all = data ;
    real.bitc.wd_update = dummy.bitc.wd_update;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG10_REAL = real.all;
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG10(void)
{
    GH_PMU_SYS_REG_CFG10_REAL_S real;
    GH_PMU_SYS_REG_CFG10_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_PMU_SYS_REG_CFG10_REAL);

    dummy.bitc.wd_update = real.bitc.wd_update;
    return dummy.all;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG10_WD_UPDATE(U8 data)
{
    GH_PMU_SYS_REG_CFG10_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG10_REAL;
    d.bitc.wd_update = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG10_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG10_WD_UPDATE(void)
{
    GH_PMU_SYS_REG_CFG10_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG10_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.wd_update;
}

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG11 (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_set_SYS_REG_CFG11(U32 data)
{
    GH_PMU_SYS_REG_CFG11_REAL_S real;
    GH_PMU_SYS_REG_CFG11_S dummy;
    dummy.all = data ;
    real.bitc.m51reset_dis = dummy.bitc.m51reset_dis;
    real.bitc.m51clk_en = dummy.bitc.m51clk_en;
    real.bitc.dlcode_en = dummy.bitc.dlcode_en;
    real.bitc.dlcode_to_m51 = dummy.bitc.dlcode_to_m51;
    real.bitc.m51_handle = dummy.bitc.m51_handle;
    real.bitc.cpu_handle = dummy.bitc.cpu_handle;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG11_REAL = real.all;
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG11(void)
{
    GH_PMU_SYS_REG_CFG11_REAL_S real;
    GH_PMU_SYS_REG_CFG11_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_PMU_SYS_REG_CFG11_REAL);

    dummy.bitc.m51reset_dis = real.bitc.m51reset_dis;
    dummy.bitc.m51clk_en = real.bitc.m51clk_en;
    dummy.bitc.dlcode_en = real.bitc.dlcode_en;
    dummy.bitc.dlcode_to_m51 = real.bitc.dlcode_to_m51;
    dummy.bitc.m51_handle = real.bitc.m51_handle;
    dummy.bitc.cpu_handle = real.bitc.cpu_handle;
    return dummy.all;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG11_M51RESET_DIS(U8 data)
{
    GH_PMU_SYS_REG_CFG11_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG11_REAL;
    d.bitc.m51reset_dis = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG11_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG11_M51RESET_DIS(void)
{
    GH_PMU_SYS_REG_CFG11_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG11_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.m51reset_dis;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG11_M51CLK_EN(U8 data)
{
    GH_PMU_SYS_REG_CFG11_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG11_REAL;
    d.bitc.m51clk_en = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG11_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG11_M51CLK_EN(void)
{
    GH_PMU_SYS_REG_CFG11_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG11_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.m51clk_en;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG11_DLCODE_EN(U8 data)
{
    GH_PMU_SYS_REG_CFG11_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG11_REAL;
    d.bitc.dlcode_en = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG11_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG11_DLCODE_EN(void)
{
    GH_PMU_SYS_REG_CFG11_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG11_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dlcode_en;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG11_DLCODE_TO_M51(U8 data)
{
    GH_PMU_SYS_REG_CFG11_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG11_REAL;
    d.bitc.dlcode_to_m51 = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG11_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG11_DLCODE_TO_M51(void)
{
    GH_PMU_SYS_REG_CFG11_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG11_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dlcode_to_m51;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG11_M51_HANDLE(U8 data)
{
    GH_PMU_SYS_REG_CFG11_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG11_REAL;
    d.bitc.m51_handle = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG11_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG11_M51_HANDLE(void)
{
    GH_PMU_SYS_REG_CFG11_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG11_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.m51_handle;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG11_CPU_HANDLE(U8 data)
{
    GH_PMU_SYS_REG_CFG11_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG11_REAL;
    d.bitc.cpu_handle = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG11_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG11_CPU_HANDLE(void)
{
    GH_PMU_SYS_REG_CFG11_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG11_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cpu_handle;
}

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG16 (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_set_SYS_REG_CFG16(U32 data)
{
    GH_PMU_SYS_REG_CFG16_REAL_S real;
    GH_PMU_SYS_REG_CFG16_S dummy;
    dummy.all = data ;
    real.bitc.xclk_iopad = dummy.bitc.xclk_iopad;
    real.bitc.rtc_iopad = dummy.bitc.rtc_iopad;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG16_REAL = real.all;
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG16(void)
{
    GH_PMU_SYS_REG_CFG16_REAL_S real;
    GH_PMU_SYS_REG_CFG16_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_PMU_SYS_REG_CFG16_REAL);

    dummy.bitc.xclk_iopad = real.bitc.xclk_iopad;
    dummy.bitc.rtc_iopad = real.bitc.rtc_iopad;
    return dummy.all;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG16_XCLK_IOPAD(U8 data)
{
    GH_PMU_SYS_REG_CFG16_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG16_REAL;
    d.bitc.xclk_iopad = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG16_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG16_XCLK_IOPAD(void)
{
    GH_PMU_SYS_REG_CFG16_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG16_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.xclk_iopad;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG16_RTC_IOPAD(U8 data)
{
    GH_PMU_SYS_REG_CFG16_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG16_REAL;
    d.bitc.rtc_iopad = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG16_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG16_RTC_IOPAD(void)
{
    GH_PMU_SYS_REG_CFG16_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG16_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rtc_iopad;
}

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG17 (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_set_SYS_REG_CFG17(U32 data)
{
    GH_PMU_SYS_REG_CFG17_REAL_S real;
    GH_PMU_SYS_REG_CFG17_S dummy;
    dummy.all = data ;
    real.bitc.rtc_clk_sel = dummy.bitc.rtc_clk_sel;
    real.bitc.rtc_cnt_reset = dummy.bitc.rtc_cnt_reset;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG17_REAL = real.all;
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG17(void)
{
    GH_PMU_SYS_REG_CFG17_REAL_S real;
    GH_PMU_SYS_REG_CFG17_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_PMU_SYS_REG_CFG17_REAL);

    dummy.bitc.rtc_clk_sel = real.bitc.rtc_clk_sel;
    dummy.bitc.rtc_cnt_reset = real.bitc.rtc_cnt_reset;
    return dummy.all;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG17_RTC_CLK_SEL(U8 data)
{
    GH_PMU_SYS_REG_CFG17_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG17_REAL;
    d.bitc.rtc_clk_sel = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG17_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG17_RTC_CLK_SEL(void)
{
    GH_PMU_SYS_REG_CFG17_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG17_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rtc_clk_sel;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG17_RTC_CNT_RESET(U8 data)
{
    GH_PMU_SYS_REG_CFG17_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_SYS_REG_CFG17_REAL;
    d.bitc.rtc_cnt_reset = data;
    *(volatile U32 *)REG_PMU_SYS_REG_CFG17_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG17_RTC_CNT_RESET(void)
{
    GH_PMU_SYS_REG_CFG17_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_SYS_REG_CFG17_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rtc_cnt_reset;
}

/*----------------------------------------------------------------------------*/
/* register PMU_SYS_REG_CFG18 (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_set_SYS_REG_CFG18(U8 index, U32 data)
{
    GH_PMU_SYS_REG_CFG18_REAL_S real;
    GH_PMU_SYS_REG_CFG18_S dummy;
    dummy.all = data ;
    real.bitc.e = dummy.bitc.e;
    real.bitc.sr = dummy.bitc.sr;
    real.bitc.smt = dummy.bitc.smt;
    real.bitc.p = dummy.bitc.p;
    *(volatile U32 *)(REG_PMU_SYS_REG_CFG18_REAL + index * FIO_MOFFSET(PMU,4)) = real.all;
}
GH_INLINE U32  GH_PMU_get_SYS_REG_CFG18(U8 index)
{
    GH_PMU_SYS_REG_CFG18_REAL_S real;
    GH_PMU_SYS_REG_CFG18_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_PMU_SYS_REG_CFG18_REAL + index * FIO_MOFFSET(PMU,4)));

    dummy.bitc.e = real.bitc.e;
    dummy.bitc.sr = real.bitc.sr;
    dummy.bitc.smt = real.bitc.smt;
    dummy.bitc.p = real.bitc.p;
    return dummy.all;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG18_E(U8 index, U8 data)
{
    GH_PMU_SYS_REG_CFG18_REAL_S d;
    d.all = *(volatile U32 *)(REG_PMU_SYS_REG_CFG18_REAL + index * FIO_MOFFSET(PMU,4));
    d.bitc.e = data;
    *(volatile U32 *)(REG_PMU_SYS_REG_CFG18_REAL + index * FIO_MOFFSET(PMU,4)) = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG18_E(U8 index)
{
    GH_PMU_SYS_REG_CFG18_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PMU_SYS_REG_CFG18_REAL + index * FIO_MOFFSET(PMU,4)));

    tmp_value.all = value;
    return tmp_value.bitc.e;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG18_SR(U8 index, U8 data)
{
    GH_PMU_SYS_REG_CFG18_REAL_S d;
    d.all = *(volatile U32 *)(REG_PMU_SYS_REG_CFG18_REAL + index * FIO_MOFFSET(PMU,4));
    d.bitc.sr = data;
    *(volatile U32 *)(REG_PMU_SYS_REG_CFG18_REAL + index * FIO_MOFFSET(PMU,4)) = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG18_SR(U8 index)
{
    GH_PMU_SYS_REG_CFG18_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PMU_SYS_REG_CFG18_REAL + index * FIO_MOFFSET(PMU,4)));

    tmp_value.all = value;
    return tmp_value.bitc.sr;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG18_SMT(U8 index, U8 data)
{
    GH_PMU_SYS_REG_CFG18_REAL_S d;
    d.all = *(volatile U32 *)(REG_PMU_SYS_REG_CFG18_REAL + index * FIO_MOFFSET(PMU,4));
    d.bitc.smt = data;
    *(volatile U32 *)(REG_PMU_SYS_REG_CFG18_REAL + index * FIO_MOFFSET(PMU,4)) = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG18_SMT(U8 index)
{
    GH_PMU_SYS_REG_CFG18_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PMU_SYS_REG_CFG18_REAL + index * FIO_MOFFSET(PMU,4)));

    tmp_value.all = value;
    return tmp_value.bitc.smt;
}
GH_INLINE void GH_PMU_set_SYS_REG_CFG18_P(U8 index, U8 data)
{
    GH_PMU_SYS_REG_CFG18_REAL_S d;
    d.all = *(volatile U32 *)(REG_PMU_SYS_REG_CFG18_REAL + index * FIO_MOFFSET(PMU,4));
    d.bitc.p = data;
    *(volatile U32 *)(REG_PMU_SYS_REG_CFG18_REAL + index * FIO_MOFFSET(PMU,4)) = d.all;
}
GH_INLINE U8   GH_PMU_get_SYS_REG_CFG18_P(U8 index)
{
    GH_PMU_SYS_REG_CFG18_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PMU_SYS_REG_CFG18_REAL + index * FIO_MOFFSET(PMU,4)));

    tmp_value.all = value;
    return tmp_value.bitc.p;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_EN_MASK (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_set_IRQ_EN_MASK(U32 data)
{
    GH_PMU_IRQ_EN_MASK_REAL_S real;
    GH_PMU_IRQ_EN_MASK_S dummy;
    dummy.all = data ;
    real.bitc.rtc_en = dummy.bitc.rtc_en;
    real.bitc.irr_en = dummy.bitc.irr_en;
    real.bitc.fpc_en = dummy.bitc.fpc_en;
    real.bitc.gpio_en = dummy.bitc.gpio_en;
    real.bitc.cec_en = dummy.bitc.cec_en;
    real.bitc.adc_en = dummy.bitc.adc_en;
    real.bitc.irt_en = dummy.bitc.irt_en;
    *(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL = real.all;
}
GH_INLINE U32  GH_PMU_get_IRQ_EN_MASK(void)
{
    GH_PMU_IRQ_EN_MASK_REAL_S real;
    GH_PMU_IRQ_EN_MASK_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL);

    dummy.bitc.rtc_en = real.bitc.rtc_en;
    dummy.bitc.irr_en = real.bitc.irr_en;
    dummy.bitc.fpc_en = real.bitc.fpc_en;
    dummy.bitc.gpio_en = real.bitc.gpio_en;
    dummy.bitc.cec_en = real.bitc.cec_en;
    dummy.bitc.adc_en = real.bitc.adc_en;
    dummy.bitc.irt_en = real.bitc.irt_en;
    return dummy.all;
}
GH_INLINE void GH_PMU_set_IRQ_EN_MASK_RTC_EN(U8 data)
{
    GH_PMU_IRQ_EN_MASK_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL;
    d.bitc.rtc_en = data;
    *(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_IRQ_EN_MASK_RTC_EN(void)
{
    GH_PMU_IRQ_EN_MASK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rtc_en;
}
GH_INLINE void GH_PMU_set_IRQ_EN_MASK_IRR_EN(U8 data)
{
    GH_PMU_IRQ_EN_MASK_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL;
    d.bitc.irr_en = data;
    *(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_IRQ_EN_MASK_IRR_EN(void)
{
    GH_PMU_IRQ_EN_MASK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.irr_en;
}
GH_INLINE void GH_PMU_set_IRQ_EN_MASK_FPC_EN(U8 data)
{
    GH_PMU_IRQ_EN_MASK_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL;
    d.bitc.fpc_en = data;
    *(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_IRQ_EN_MASK_FPC_EN(void)
{
    GH_PMU_IRQ_EN_MASK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fpc_en;
}
GH_INLINE void GH_PMU_set_IRQ_EN_MASK_GPIO_EN(U8 data)
{
    GH_PMU_IRQ_EN_MASK_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL;
    d.bitc.gpio_en = data;
    *(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_IRQ_EN_MASK_GPIO_EN(void)
{
    GH_PMU_IRQ_EN_MASK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gpio_en;
}
GH_INLINE void GH_PMU_set_IRQ_EN_MASK_CEC_EN(U8 data)
{
    GH_PMU_IRQ_EN_MASK_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL;
    d.bitc.cec_en = data;
    *(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_IRQ_EN_MASK_CEC_EN(void)
{
    GH_PMU_IRQ_EN_MASK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cec_en;
}
GH_INLINE void GH_PMU_set_IRQ_EN_MASK_ADC_EN(U8 data)
{
    GH_PMU_IRQ_EN_MASK_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL;
    d.bitc.adc_en = data;
    *(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_IRQ_EN_MASK_ADC_EN(void)
{
    GH_PMU_IRQ_EN_MASK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adc_en;
}
GH_INLINE void GH_PMU_set_IRQ_EN_MASK_IRT_EN(U8 data)
{
    GH_PMU_IRQ_EN_MASK_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL;
    d.bitc.irt_en = data;
    *(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_IRQ_EN_MASK_IRT_EN(void)
{
    GH_PMU_IRQ_EN_MASK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_EN_MASK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.irt_en;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_CLR_RTC (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_set_IRQ_CLR_RTC(U32 data)
{
    GH_PMU_IRQ_CLR_RTC_REAL_S real;
    GH_PMU_IRQ_CLR_RTC_S dummy;
    dummy.all = data ;
    real.bitc.irqclr = dummy.bitc.irqclr;
    *(volatile U32 *)REG_PMU_IRQ_CLR_RTC_REAL = real.all;
}
GH_INLINE U32  GH_PMU_get_IRQ_CLR_RTC(void)
{
    GH_PMU_IRQ_CLR_RTC_REAL_S real;
    GH_PMU_IRQ_CLR_RTC_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_PMU_IRQ_CLR_RTC_REAL);

    dummy.bitc.irqclr = real.bitc.irqclr;
    return dummy.all;
}
GH_INLINE void GH_PMU_set_IRQ_CLR_RTC_IRQCLR(U8 data)
{
    GH_PMU_IRQ_CLR_RTC_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_CLR_RTC_REAL;
    d.bitc.irqclr = data;
    *(volatile U32 *)REG_PMU_IRQ_CLR_RTC_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_IRQ_CLR_RTC_IRQCLR(void)
{
    GH_PMU_IRQ_CLR_RTC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_CLR_RTC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.irqclr;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_CLR_IRR (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_set_IRQ_CLR_IRR(U32 data)
{
    GH_PMU_IRQ_CLR_IRR_REAL_S real;
    GH_PMU_IRQ_CLR_IRR_S dummy;
    dummy.all = data ;
    real.bitc.irqclr = dummy.bitc.irqclr;
    *(volatile U32 *)REG_PMU_IRQ_CLR_IRR_REAL = real.all;
}
GH_INLINE U32  GH_PMU_get_IRQ_CLR_IRR(void)
{
    GH_PMU_IRQ_CLR_IRR_REAL_S real;
    GH_PMU_IRQ_CLR_IRR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_PMU_IRQ_CLR_IRR_REAL);

    dummy.bitc.irqclr = real.bitc.irqclr;
    return dummy.all;
}
GH_INLINE void GH_PMU_set_IRQ_CLR_IRR_IRQCLR(U8 data)
{
    GH_PMU_IRQ_CLR_IRR_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_CLR_IRR_REAL;
    d.bitc.irqclr = data;
    *(volatile U32 *)REG_PMU_IRQ_CLR_IRR_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_IRQ_CLR_IRR_IRQCLR(void)
{
    GH_PMU_IRQ_CLR_IRR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_CLR_IRR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.irqclr;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_CLR_FPC (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_set_IRQ_CLR_FPC(U32 data)
{
    GH_PMU_IRQ_CLR_FPC_REAL_S real;
    GH_PMU_IRQ_CLR_FPC_S dummy;
    dummy.all = data ;
    real.bitc.irqclr = dummy.bitc.irqclr;
    *(volatile U32 *)REG_PMU_IRQ_CLR_FPC_REAL = real.all;
}
GH_INLINE U32  GH_PMU_get_IRQ_CLR_FPC(void)
{
    GH_PMU_IRQ_CLR_FPC_REAL_S real;
    GH_PMU_IRQ_CLR_FPC_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_PMU_IRQ_CLR_FPC_REAL);

    dummy.bitc.irqclr = real.bitc.irqclr;
    return dummy.all;
}
GH_INLINE void GH_PMU_set_IRQ_CLR_FPC_IRQCLR(U8 data)
{
    GH_PMU_IRQ_CLR_FPC_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_CLR_FPC_REAL;
    d.bitc.irqclr = data;
    *(volatile U32 *)REG_PMU_IRQ_CLR_FPC_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_IRQ_CLR_FPC_IRQCLR(void)
{
    GH_PMU_IRQ_CLR_FPC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_CLR_FPC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.irqclr;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_CLR_GPIO (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_set_IRQ_CLR_GPIO(U32 data)
{
    GH_PMU_IRQ_CLR_GPIO_REAL_S real;
    GH_PMU_IRQ_CLR_GPIO_S dummy;
    dummy.all = data ;
    real.bitc.irqclr = dummy.bitc.irqclr;
    *(volatile U32 *)REG_PMU_IRQ_CLR_GPIO_REAL = real.all;
}
GH_INLINE U32  GH_PMU_get_IRQ_CLR_GPIO(void)
{
    GH_PMU_IRQ_CLR_GPIO_REAL_S real;
    GH_PMU_IRQ_CLR_GPIO_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_PMU_IRQ_CLR_GPIO_REAL);

    dummy.bitc.irqclr = real.bitc.irqclr;
    return dummy.all;
}
GH_INLINE void GH_PMU_set_IRQ_CLR_GPIO_IRQCLR(U8 data)
{
    GH_PMU_IRQ_CLR_GPIO_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_CLR_GPIO_REAL;
    d.bitc.irqclr = data;
    *(volatile U32 *)REG_PMU_IRQ_CLR_GPIO_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_IRQ_CLR_GPIO_IRQCLR(void)
{
    GH_PMU_IRQ_CLR_GPIO_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_CLR_GPIO_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.irqclr;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_CLR_CEC (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_set_IRQ_CLR_CEC(U32 data)
{
    GH_PMU_IRQ_CLR_CEC_REAL_S real;
    GH_PMU_IRQ_CLR_CEC_S dummy;
    dummy.all = data ;
    real.bitc.irqclr = dummy.bitc.irqclr;
    *(volatile U32 *)REG_PMU_IRQ_CLR_CEC_REAL = real.all;
}
GH_INLINE U32  GH_PMU_get_IRQ_CLR_CEC(void)
{
    GH_PMU_IRQ_CLR_CEC_REAL_S real;
    GH_PMU_IRQ_CLR_CEC_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_PMU_IRQ_CLR_CEC_REAL);

    dummy.bitc.irqclr = real.bitc.irqclr;
    return dummy.all;
}
GH_INLINE void GH_PMU_set_IRQ_CLR_CEC_IRQCLR(U8 data)
{
    GH_PMU_IRQ_CLR_CEC_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_CLR_CEC_REAL;
    d.bitc.irqclr = data;
    *(volatile U32 *)REG_PMU_IRQ_CLR_CEC_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_IRQ_CLR_CEC_IRQCLR(void)
{
    GH_PMU_IRQ_CLR_CEC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_CLR_CEC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.irqclr;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_CLR_ADC (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_set_IRQ_CLR_ADC(U32 data)
{
    GH_PMU_IRQ_CLR_ADC_REAL_S real;
    GH_PMU_IRQ_CLR_ADC_S dummy;
    dummy.all = data ;
    real.bitc.irqclr = dummy.bitc.irqclr;
    *(volatile U32 *)REG_PMU_IRQ_CLR_ADC_REAL = real.all;
}
GH_INLINE U32  GH_PMU_get_IRQ_CLR_ADC(void)
{
    GH_PMU_IRQ_CLR_ADC_REAL_S real;
    GH_PMU_IRQ_CLR_ADC_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_PMU_IRQ_CLR_ADC_REAL);

    dummy.bitc.irqclr = real.bitc.irqclr;
    return dummy.all;
}
GH_INLINE void GH_PMU_set_IRQ_CLR_ADC_IRQCLR(U8 data)
{
    GH_PMU_IRQ_CLR_ADC_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_CLR_ADC_REAL;
    d.bitc.irqclr = data;
    *(volatile U32 *)REG_PMU_IRQ_CLR_ADC_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_IRQ_CLR_ADC_IRQCLR(void)
{
    GH_PMU_IRQ_CLR_ADC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_CLR_ADC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.irqclr;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_CLR_IRT (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_set_IRQ_CLR_IRT(U32 data)
{
    GH_PMU_IRQ_CLR_IRT_REAL_S real;
    GH_PMU_IRQ_CLR_IRT_S dummy;
    dummy.all = data ;
    real.bitc.irqclr = dummy.bitc.irqclr;
    *(volatile U32 *)REG_PMU_IRQ_CLR_IRT_REAL = real.all;
}
GH_INLINE U32  GH_PMU_get_IRQ_CLR_IRT(void)
{
    GH_PMU_IRQ_CLR_IRT_REAL_S real;
    GH_PMU_IRQ_CLR_IRT_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_PMU_IRQ_CLR_IRT_REAL);

    dummy.bitc.irqclr = real.bitc.irqclr;
    return dummy.all;
}
GH_INLINE void GH_PMU_set_IRQ_CLR_IRT_IRQCLR(U8 data)
{
    GH_PMU_IRQ_CLR_IRT_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_CLR_IRT_REAL;
    d.bitc.irqclr = data;
    *(volatile U32 *)REG_PMU_IRQ_CLR_IRT_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_IRQ_CLR_IRT_IRQCLR(void)
{
    GH_PMU_IRQ_CLR_IRT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_CLR_IRT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.irqclr;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRQ_STATUS (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_set_IRQ_STATUS(U32 data)
{
    GH_PMU_IRQ_STATUS_REAL_S real;
    GH_PMU_IRQ_STATUS_S dummy;
    dummy.all = data ;
    real.bitc.rtc_irq = dummy.bitc.rtc_irq;
    real.bitc.irr_irq = dummy.bitc.irr_irq;
    real.bitc.fpc_irq = dummy.bitc.fpc_irq;
    real.bitc.gpio_irq = dummy.bitc.gpio_irq;
    real.bitc.cec_irq = dummy.bitc.cec_irq;
    real.bitc.adc_irq = dummy.bitc.adc_irq;
    real.bitc.irt_irq = dummy.bitc.irt_irq;
    *(volatile U32 *)REG_PMU_IRQ_STATUS_REAL = real.all;
}
GH_INLINE U32  GH_PMU_get_IRQ_STATUS(void)
{
    GH_PMU_IRQ_STATUS_REAL_S real;
    GH_PMU_IRQ_STATUS_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_PMU_IRQ_STATUS_REAL);

    dummy.bitc.rtc_irq = real.bitc.rtc_irq;
    dummy.bitc.irr_irq = real.bitc.irr_irq;
    dummy.bitc.fpc_irq = real.bitc.fpc_irq;
    dummy.bitc.gpio_irq = real.bitc.gpio_irq;
    dummy.bitc.cec_irq = real.bitc.cec_irq;
    dummy.bitc.adc_irq = real.bitc.adc_irq;
    dummy.bitc.irt_irq = real.bitc.irt_irq;
    return dummy.all;
}
GH_INLINE void GH_PMU_set_IRQ_STATUS_RTC_IRQ(U8 data)
{
    GH_PMU_IRQ_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_STATUS_REAL;
    d.bitc.rtc_irq = data;
    *(volatile U32 *)REG_PMU_IRQ_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_IRQ_STATUS_RTC_IRQ(void)
{
    GH_PMU_IRQ_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rtc_irq;
}
GH_INLINE void GH_PMU_set_IRQ_STATUS_IRR_IRQ(U8 data)
{
    GH_PMU_IRQ_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_STATUS_REAL;
    d.bitc.irr_irq = data;
    *(volatile U32 *)REG_PMU_IRQ_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_IRQ_STATUS_IRR_IRQ(void)
{
    GH_PMU_IRQ_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.irr_irq;
}
GH_INLINE void GH_PMU_set_IRQ_STATUS_FPC_IRQ(U8 data)
{
    GH_PMU_IRQ_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_STATUS_REAL;
    d.bitc.fpc_irq = data;
    *(volatile U32 *)REG_PMU_IRQ_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_IRQ_STATUS_FPC_IRQ(void)
{
    GH_PMU_IRQ_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fpc_irq;
}
GH_INLINE void GH_PMU_set_IRQ_STATUS_GPIO_IRQ(U8 data)
{
    GH_PMU_IRQ_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_STATUS_REAL;
    d.bitc.gpio_irq = data;
    *(volatile U32 *)REG_PMU_IRQ_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_IRQ_STATUS_GPIO_IRQ(void)
{
    GH_PMU_IRQ_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gpio_irq;
}
GH_INLINE void GH_PMU_set_IRQ_STATUS_CEC_IRQ(U8 data)
{
    GH_PMU_IRQ_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_STATUS_REAL;
    d.bitc.cec_irq = data;
    *(volatile U32 *)REG_PMU_IRQ_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_IRQ_STATUS_CEC_IRQ(void)
{
    GH_PMU_IRQ_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cec_irq;
}
GH_INLINE void GH_PMU_set_IRQ_STATUS_ADC_IRQ(U8 data)
{
    GH_PMU_IRQ_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_STATUS_REAL;
    d.bitc.adc_irq = data;
    *(volatile U32 *)REG_PMU_IRQ_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_IRQ_STATUS_ADC_IRQ(void)
{
    GH_PMU_IRQ_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adc_irq;
}
GH_INLINE void GH_PMU_set_IRQ_STATUS_IRT_IRQ(U8 data)
{
    GH_PMU_IRQ_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_PMU_IRQ_STATUS_REAL;
    d.bitc.irt_irq = data;
    *(volatile U32 *)REG_PMU_IRQ_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_PMU_get_IRQ_STATUS_IRT_IRQ(void)
{
    GH_PMU_IRQ_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PMU_IRQ_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.irt_irq;
}

/*----------------------------------------------------------------------------*/
/* register PMU_C51_LOADCODE_ADDR (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_set_C51_LOADCODE_ADDR(U16 index, U32 data)
{
    *(volatile U32 *)(REG_PMU_C51_LOADCODE_ADDR_REAL + index * FIO_MOFFSET(PMU,4)) = data;
}
GH_INLINE U32  GH_PMU_get_C51_LOADCODE_ADDR(U16 index)
{
    U32 value = (*(volatile U32 *)(REG_PMU_C51_LOADCODE_ADDR_REAL + index * FIO_MOFFSET(PMU,4)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_init(void)
{
    GH_PMU_set_SYS_REG_CFG8((U32)0x00000000);
    GH_PMU_set_SYS_REG_CFG9((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

