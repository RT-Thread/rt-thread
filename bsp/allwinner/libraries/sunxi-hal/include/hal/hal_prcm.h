/*
*********************************************************************************************************
*                                                AR100 SYSTEM
*                                     AR100 Software System Develop Kits
*                                       clock control unit module
*
*                                    (c) Copyright 2012-2016, Sunny China
*                                             All Rights Reserved
*
* File    : prcm.h
* By      : Sunny
* Version : v1.0
* Date    : 2012-4-28
* Descript: clock control unit public header.
* Update  : date                auther      ver     notes
*           2012-4-28 14:48:38  Sunny       1.0     Create this file.
*********************************************************************************************************
*/

#ifndef __PRCM_H__
#define __PRCM_H__

#include <sunxi_hal_rtc.h>
#include <sunxi_hal_common.h>

/* the clock status of on-off */
typedef enum ccu_clk_onoff {
    CCU_CLK_OFF = 0x0,          /* clock off status */
    CCU_CLK_ON  = 0x1,          /* clock on status */
} ccu_clk_onff_e;

/* the clock status of reset */
typedef enum ccu_clk_reset {
    CCU_CLK_RESET   = 0x0,      /* reset valid status */
    CCU_CLK_NRESET  = 0x1,      /* reset invalid status */
} ccu_clk_reset_e;

/* command for call-back function of clock change */
typedef enum ccu_clk_cmd {
    CCU_CLK_CLKCHG_REQ = 0x0,   /* command for notify that clock will change */
    CCU_CLK_CLKCHG_DONE,        /* command for notify that clock change finish */
} ccu_clk_cmd_e;

/* command for call-back function of 24M hosc on-off */
typedef enum ccu_hosc_cmd {
    CCU_HOSC_ON_READY_NOTIFY = 0x0, /* command for notify that 24mhosc power-on already */
    CCU_HOSC_WILL_OFF_NOTIFY,       /* command for notify that 24mhosc will off */
} ccu_hosc_cmd_e;

/* the state of power-off gating */
typedef enum poweroff_gating_state {
    CCU_POWEROFF_GATING_INVALID = 0x0,
    CCU_POWEROFF_GATING_VALID   = 0x1,
} poweroff_gating_state_e;

/* source clocks ID */
typedef enum ccu_src_clk {
    CCU_SYS_CLK_NONE = 0x0, /* invalid source clock id */

    CCU_SYS_CLK_LOSC,   /* LOSC, 33/50/67:32768Hz, 73:16MHz/512=31250 */
    CCU_SYS_CLK_IOSC,   /* InternalOSC,  33/50/67:700KHZ, 73:16MHz */
    CCU_SYS_CLK_HOSC,   /* HOSC, 24MHZ clock */
    CCU_SYS_CLK_AXI,    /* AXI clock */
    CCU_SYS_CLK_16M,    /* 16M for the backdoor */

    CCU_SYS_CLK_PLL1,   /* PLL1 clock */
    CCU_SYS_CLK_PLL2,   /* PLL2 clock */
    CCU_SYS_CLK_PLL3,   /* PLL3 clock */
    CCU_SYS_CLK_PLL4,   /* PLL4 clock */
    CCU_SYS_CLK_PLL5,   /* PLL5 clock */
    CCU_SYS_CLK_PLL6,   /* PLL6 clock */
    CCU_SYS_CLK_PLL7,   /* PLL7 clock  */
    CCU_SYS_CLK_PLL8,   /* PLL8 clock */
    CCU_SYS_CLK_PLL9,   /* PLL9 clock */
    CCU_SYS_CLK_PLL10,  /* PLL10 clock */
    CCU_SYS_CLK_PLL11,  /* PLL10 clock */

    CCU_SYS_CLK_AUDIO0, /* AUDIO0 clock */
    CCU_SYS_CLK_AUDIO1, /* AUDIO1 clock */

    CCU_SYS_CLK_CPUS,   /* cpus clock */
    CCU_SYS_CLK_C0,     /* cluster0 clock */
    CCU_SYS_CLK_C1,     /* cluster1 clock */
    CCU_SYS_CLK_DDR0,   /* ddr0 clock */
    CCU_SYS_CLK_DDR1,   /* ddr1 clock */
    CCU_SYS_CLK_PERI0,  /* peri0 clock */
    CCU_SYS_CLK_PERI1,  /* peri1 clock */
    CCU_SYS_CLK_AXI0,   /* AXI0 clock */
    CCU_SYS_CLK_AXI1,   /* AXI0 clock */
    CCU_SYS_CLK_AHB0,   /* AHB0 clock */
    CCU_SYS_CLK_AHB1,   /* AHB1 clock */
    CCU_SYS_CLK_AHB2,   /* AHB2 clock */
    CCU_SYS_CLK_APB0,   /* APB0 clock */
    CCU_SYS_CLK_APB1,   /* APB1 clock */
    CCU_SYS_CLK_APB2,   /* APB2 clock */
    CCU_SYS_CLK_AHB3,   /* AHB3 clock */
    CCU_SYS_CLK_PSI,    /* PSI clock */
    CCU_SYS_CLK_AHBS,   /* AHBS clock */
    CCU_SYS_CLK_APBS1,  /* APBS1 clock */
    CCU_SYS_CLK_APBS2,  /* APBS2 clock */
} ccu_sys_clk_e;

/* module clocks ID */
typedef enum ccu_mod_clk {
    CCU_MOD_CLK_NONE,

    CCU_MOD_CLK_CPUS,
    CCU_MOD_CLK_AHB0,
    CCU_MOD_CLK_APB0,

    CCU_MOD_CLK_C0,
    CCU_MOD_CLK_C1,
    CCU_MOD_CLK_CPU0,
    CCU_MOD_CLK_CPU1,
    CCU_MOD_CLK_CPU2,
    CCU_MOD_CLK_CPU3,
    CCU_MOD_CLK_AHB1,
    CCU_MOD_CLK_AHB2,
    CCU_MOD_CLK_APB1,
    CCU_MOD_CLK_APB2,
    CCU_MOD_CLK_DMA,
    CCU_MOD_CLK_SDRAM,
    CCU_MOD_CLK_SPINLOCK,
    CCU_MOD_CLK_MSGBOX,
    CCU_MOD_CLK_MSGBOX0,
    CCU_MOD_CLK_MSGBOX1,
    CCU_MOD_CLK_MSGBOXR,
    CCU_MOD_CLK_AHB1_SS,
    CCU_MOD_CLK_AXI,
    CCU_MOD_CLK_AXI0,
    CCU_MOD_CLK_AXI1,
    CCU_MOD_CLK_R_DMA,
    CCU_MOD_CLK_R_DMA_MCLK,
    CCU_MOD_CLK_R_ONEWIRE_SP,
    CCU_MOD_CLK_R_CIR_SP,
    CCU_MOD_CLK_R_TH,
    CCU_MOD_CLK_R_ONEWIRE,
    CCU_MOD_CLK_R_UART,
    CCU_MOD_CLK_R_UART1,
    CCU_MOD_CLK_R_UART2,
    CCU_MOD_CLK_R_UART3,
    CCU_MOD_CLK_R_UART4,
    CCU_MOD_CLK_R_TIMER0_1,
    CCU_MOD_CLK_R_P2WI,
    CCU_MOD_CLK_R_RSB,
    CCU_MOD_CLK_R_TWI,
    CCU_MOD_CLK_R_TWI0,
    CCU_MOD_CLK_R_TWI1,
    CCU_MOD_CLK_R_TWI2,
    CCU_MOD_CLK_R_CIR,
    CCU_MOD_CLK_R_PIO,
    CCU_MOD_CLK_R_VM,
    CCU_MOD_CLK_R_THS,
    CCU_MOD_CLK_R_LRADC,
    CCU_MOD_CLK_R_CAN,

    CCU_MOD_CLK_R_LPSD,
    CCU_MOD_CLK_R_MAD,
    CCU_MOD_CLK_R_MAD_SRAM,
    CCU_MOD_CLK_R_MAD_CFG,

    CCU_MOD_CLK_R_AC_ADC,
    CCU_MOD_CLK_R_AC_DAC,
    CCU_MOD_CLK_R_AUDIO_CODEC,
    CCU_MOD_CLK_R_DMIC,
    CCU_MOD_CLK_R_I2S0,
    CCU_MOD_CLK_R_I2S0_ASRC,
    CCU_MOD_CLK_R_I2S1,

    CCU_MOD_CLK_VDD_SYS,
    CCU_MOD_CLK_CCI400,
    CCU_MOD_CLK_PSI,
    CCU_MOD_CLK_AHB3,
    CCU_MOD_CLK_AHBS,
    CCU_MOD_CLK_APBS1,
    CCU_MOD_CLK_APBS2,
    CCU_MOD_CLK_R_RTC,
    CCU_MOD_CLK_R_CPUSCFG,
    CCU_MOD_CLK_R_PRCM,
    CCU_MOD_CLK_R_WDG,
    CCU_MOD_CLK_R_TWD,
    CCU_MOD_CLK_R_PWM,
    CCU_MOD_CLK_R_SPI,
    CCU_MOD_CLK_R_INTC,
    CCU_MOD_CLK_CPU_APB,
} ccu_mod_clk_e;

/* the power control modules */
typedef enum power_control_module {
    /* cpux power controls */
    PWRCTL_C0CPUX,
    PWRCTL_C0CPU0,
    PWRCTL_C0CPU1,
    PWRCTL_C0CPU2,
    PWRCTL_C0CPU3,

    PWRCTL_C1CPUX,
    PWRCTL_C1CPU0,
    PWRCTL_C1CPU1,
    PWRCTL_C1CPU2,
    PWRCTL_C1CPU3,

    /* vdd-sys power controls */
    PWRCTL_VDD_CPUX_GPIO_PAD_HOLD,
    PWRCTL_VDD_CPUS,
    PWRCTL_VDD_AVCC_A,
    PWRCTL_VCC_PLL,
    PWRCTL_VCC_PLL_LOW_VOLT,

    /* gpu power control */
    PWRCTL_GPU,
    PWRCTL_SYS2VDD_USB3,
    PWRCTL_SYS2VDD_USB0,
} power_control_module_e;

/*
*********************************************************************************************************
*                                       INITIALIZE CCU
*
* Description:  initialize clock control unit.
*
* Arguments  :  none.
*
* Returns    :  OK if initialize ccu succeeded, others if failed.
*********************************************************************************************************
*/
s32 ccu_init(void);

/*
*********************************************************************************************************
*                                       EXIT CCU
*
* Description:  exit clock control unit.
*
* Arguments  :  none.
*
* Returns    :  OK if exit ccu succeeded, others if failed.
*********************************************************************************************************
*/
s32 ccu_exit(void);


void ccu_iosc_freq_update(void);
/*
*********************************************************************************************************
*                                      SET SOURCE FREQUENCY
*
* Description:  set the frequency of a specific source clock.
*
* Arguments  :  sclk : the source clock ID which we want to set frequency.
*               freq : the frequency which we want to set.
*
* Returns    :  OK if set source frequency succeeded, others if failed.
*********************************************************************************************************
*/
s32 ccu_set_sclk_freq(u32 sclk, u32 freq);

/*
*********************************************************************************************************
*                                     GET SOURCE FREQUENCY
*
* Description:  get the frequency of a specific source clock.
*
* Arguments  :  sclk : the source clock ID which we want to get frequency.
*
* Returns    :  frequency of the specific source clock.
*********************************************************************************************************
*/
u32 ccu_get_sclk_freq(u32 sclk);

s32 ccu_set_sclk_onoff(u32 sclk, s32 onoff);

/*
*********************************************************************************************************
*                                     REGISTER MODULE CB
*
* Description:  register call-back for module clock, when the source frequency
*               of the module clock changed, it will use this call-back to notify
*               module driver.
*
* Arguments  :  mclk    : the module clock ID which we want to register call-back.
*               pcb     : the call-back which we want to register.
*
* Returns    :  OK if register call-back succeeded, others if failed.
*********************************************************************************************************
*/
s32 ccu_reg_mclk_cb(u32 mclk, __pNotifier_t pcb);

/*
*********************************************************************************************************
*                                     UNREGISTER MODULE CB
*
* Description:  unregister call-back for module clock.
*
* Arguments  :  mclk    : the module clock ID which we want to unregister call-back.
*               pcb     : the call-back which we want to unregister.
*
* Returns    :  OK if unregister call-back succeeded, others if failed.
*********************************************************************************************************
*/
s32 ccu_unreg_mclk_cb(u32 mclk, __pNotifier_t pcb);

/*
*********************************************************************************************************
*                                    SET SOURCE OF MODULE CLOCK
*
* Description:  set the source of a specific module clock.
*
* Arguments  :  mclk    : the module clock ID which we want to set source.
*               sclk    : the source clock ID whick we want to set as source.
*
* Returns    :  OK if set source succeeded, others if failed.
*********************************************************************************************************
*/
s32 ccu_set_mclk_src(u32 mclk, u32 sclk);

/*
*********************************************************************************************************
*                                    GET SOURCE OF MODULE CLOCK
*
* Description:  get the source of a specific module clock.
*
* Arguments  :  mclk    : the module clock ID which we want to get source.
*
* Returns    :  the source clock ID of source clock.
*********************************************************************************************************
*/
s32 ccu_get_mclk_src(u32 mclk);

/*
*********************************************************************************************************
*                                    SET DIVIDER OF MODULE CLOCK
*
* Description:  set the divider of a specific module clock.
*
* Arguments  :  mclk    : the module clock ID which we want to set divider.
*               div     : the divider whick we want to set as source.
*
* Returns    :  OK if set divider succeeded, others if failed.
*********************************************************************************************************
*/
s32 ccu_set_mclk_div(u32 mclk, u32 div);

/*
*********************************************************************************************************
*                                    GET DIVIDER OF MODULE CLOCK
*
* Description:  get the divider of a specific module clock.
*
* Arguments  :  mclk    : the module clock ID which we want to get divider.
*
* Returns    :  the divider of the specific module clock.
*********************************************************************************************************
*/
s32 ccu_get_mclk_div(u32 mclk);

/*
*********************************************************************************************************
*                                    SET ON-OFF STATUS OF MODULE CLOCK
*
* Description:  set the on-off status of a specific module clock.
*
* Arguments  :  mclk    : the module clock ID which we want to set on-off status.
*               onoff   : the on-off status which we want to set, the detail please
*                         refer to the clock status of on-off.
*
* Returns    :  OK if set module clock on-off status succeeded, others if failed.
*********************************************************************************************************
*/
s32 ccu_set_mclk_onoff(u32 mclk, s32 onoff);

/*
*********************************************************************************************************
*                                    SET RESET STATUS OF MODULE CLOCK
*
* Description:  set the reset status of a specific module clock.
*
* Arguments  :  mclk    : the module clock ID which we want to set reset status.
*               reset   : the reset status which we want to set, the detail please
*                         refer to the clock status of reset.
*
* Returns    :  OK if set module clock reset status succeeded, others if failed.
*********************************************************************************************************
*/
s32 ccu_set_mclk_reset(u32 mclk, s32 reset);

/*
*********************************************************************************************************
*                                    SET POWER OFF STATUS OF HWMODULE
*
* Description:  set the power off gating status of a specific module.
*
* Arguments  :  module  : the module ID which we want to set power off gating status.
*               status  : the power off status which we want to set, the detail please
*                         refer to the status of power-off gating.
*
* Returns    :  OK if set module power off gating status succeeded, others if failed.
*********************************************************************************************************
*/
s32 ccu_set_poweroff_gating_state(s32 module, s32 state);

/*
*********************************************************************************************************
*                                           RESET MODULE
*
* Description:  reset a specific module.
*
* Arguments  :  module  : the module clock ID which we want to reset.
*
* Returns    :  OK if reset module succeeded, others if failed.
*********************************************************************************************************
*/
s32 ccu_reset_module(u32 mclk);

s32 ccu_24mhosc_disable(void);
s32 ccu_24mhosc_enable(void);
s32 ccu_24mhosc_reg_cb(__pNotifier_t pcb);
s32 is_hosc_lock(void);

static inline void save_state_flag(u32 value)
{
//  hal_writel(value, RTC_RECORD_REG);
}

extern u32 iosc_freq;
extern u32 losc_freq;
void osc_freq_init(void);
void osc_freq_filter(void);

#endif /* __PRCM_H__ */

