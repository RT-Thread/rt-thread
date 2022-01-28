/*
 * Copyright (c) 2021, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-16     Dystopia     the first version
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#include <c6x.h>
#include <cslr_cgem.h>
#include <cslr_device.h>
#include <cslr_bootcfg.h>
#include <cslr_tmr.h>
#include <csl_tmr.h>

/* DSP core clock speed in Hz */
#define DSP_CORE_SPEED_HZ   1000000000

extern CSL_CgemRegs * gp_cgem_regs;
extern CSL_BootcfgRegs * gp_bootcfg_regs;

/*----------------------Timer plus registers definition----------------*/
typedef struct {
    volatile unsigned int PID12;
    volatile unsigned int EMUMGT_CLKSPD;
    volatile unsigned int GPINT_EN;
    volatile unsigned int GPDIR_DAT;
    volatile unsigned int CNTLO;
    volatile unsigned int CNTHI;
    volatile unsigned int PRDLO;
    volatile unsigned int PRDHI;
    volatile unsigned int TCR;
    volatile unsigned int TGCR;
    volatile unsigned int WDTCR;
    volatile unsigned int TLGC;
    volatile unsigned int TLMR;
    volatile unsigned int RELLO;
    volatile unsigned int RELHI;
    volatile unsigned int CAPLO;
    volatile unsigned int CAPHI;
    volatile unsigned int INTCTL_STAT;
    volatile unsigned char  RSVD0[24];
    volatile unsigned int TIMERLO_COMPARE_REG[8];
    volatile unsigned char  RSVD1[32];
} CSL_TmrPlusRegs;

#define TMR_TCR_READRSTMODE_HI_SHIFT   (26)
#define TMR_TCR_CAPEVTMODE_LO_SHIFT    (12)
#define TMR_TCR_CAPMODE_LO_SHIFT       (11)
#define TMR_TCR_READRSTMODE_LO_SHIFT   (10)

#define TMR_TCR_READRSTMODE_HI_MASK    (1<<26)
#define TMR_TCR_CAPEVTMODE_LO_MASK     (3<<12)
#define TMR_TCR_CAPMODE_LO_MASK        (1<<11)
#define TMR_TCR_READRSTMODE_LO_MASK    (1<<10)

#define TMR_TGCR_PLUSEN_SHIFT          4
#define TMR_TGCR_PLUSEN_MASK           (1<<4)

#define TMR_INTCTLSTAT_EN_ALL_CLR_ALL  0x000F000F

#define CSL_TMR_WDTCR_WDKEY_CMD1       (0x0000A5C6u)
#define CSL_TMR_WDTCR_WDKEY_CMD2       (0x0000DA7Eu)

#define CSL_TMR_ENAMODE_CONT_RELOAD    3

extern CSL_TmrPlusRegs * gp_timer0_regs;
extern CSL_TmrPlusRegs * gp_timer1_regs;
extern CSL_TmrPlusRegs * gp_timer2_regs;
extern CSL_TmrPlusRegs * gp_timer3_regs;
extern CSL_TmrPlusRegs * gp_timer4_regs;
extern CSL_TmrPlusRegs * gp_timer5_regs;
extern CSL_TmrPlusRegs * gp_timer6_regs;
extern CSL_TmrPlusRegs * gp_timer7_regs;
extern CSL_TmrPlusRegs * gp_timer8_regs;
extern CSL_TmrPlusRegs * gp_timer_regs[];

typedef enum
{
    TIMER_ONE_SHOT_PULSE = 0,     /*generate one shot pulse with timer*/
    TIMER_PERIODIC_PULSE,         /*generate periodic pulse with timer*/
    TIMER_PERIODIC_CLOCK,         /*generate periodic clock with timer*/
    /*generate periodic square wave with period reload feature, the difference
    between wave and clock is the duty cycle of clock is always 50%*/
    TIMER_PERIODIC_WAVE,
    TIMER_WATCH_DOG               /*configure timer as watch dog*/
}TTimerMode;

typedef struct  {
    int timer_num;                /*select one timer*/
    TTimerMode timerMode;         /*select function of the timer*/
    unsigned long long period;    /*in the unit of DSP core clock/6*/
    unsigned long long reload_period;     /*the reload value of period*/
    int pulseWidth;               /*pulse width between 0~3*/
}Timer64_Config;

/* Reset a 64-bit timer */
extern void reset_timer(int timer_num);

/* Initailize a 64-bit timer */
extern void timer64_init(Timer64_Config * tmrCfg);

extern void keystone_cpu_init(void);

#endif /* __COMMON_H__ */
