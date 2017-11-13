/*
 * File      : drv_pmu.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-03-29     Urey         the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <stdint.h>

#include "board.h"
#include "drv_clock.h"
#include "drv_gpio.h"
#include "drv_ost.h"
#include "drv_rtc.h"

struct sleep_save_register
{
    unsigned int lcr;
    unsigned int opcr;
    unsigned int sleep_voice_enable;
    unsigned int ddr_training_space[20];
};

static struct sleep_save_register s_reg;


static void write_aic_register(unsigned int addr,unsigned char val)
{
    while(REG_ICDC_RGADW & (1 << 16));
    REG_ICDC_RGADW = (1 << 16) | (addr << 8) | val;
}


static void _delay_us(rt_uint32_t ns)
{
    volatile rt_uint16_t    delay;

    while(ns--)
    {
        delay = 200;
        while(delay--);
    }
}

static void _delay_ms(rt_uint32_t ms)
{
    volatile rt_uint16_t    delay;

    while(ms--)
    {
        _delay_us(1000);
    }
}

#if 0
static int jz_pm_do_sleep(void)
{
    unsigned int div;
    unsigned long opcr = REG_CPM_OPCR;
    unsigned long icmr0 = REG_INTC_IMCR(0);
    unsigned long icmr1 = REG_INTC_IMCR(1);
    unsigned long sleep_gpio_save[5*(GPIO_NR_PORTS)];
    unsigned long cpuflags;
    unsigned long msc0cdr = REG_CPM_MSC0CDR;
    void (*resume_addr)(void);
    unsigned int val;
    unsigned int gint_mask = REG_GINT_MASK;
    unsigned int level = rt_hw_interrupt_disable();
    unsigned int clkgr0 = REG_CPM_CLKGR0;
    /* set SLEEP mode */
    //CMSREG32(CPM_LCR, LCR_LPM_SLEEP, LCR_LPM_MASK);

    REG_CPM_CLKGR0 &= ~(1 << 11);
    write_aic_register(0x13, 0x10);
    write_aic_register(0xd, 0xb1);
    write_aic_register(0xe, 0xb5);

    *(volatile unsigned int *)0xb000003c |= (1 << 25) | (1 << 21) | (1 << 20);
    REG_CPM_CLKGR0 = 0x0fdefff7;

    /* Mask all interrupts */
    REG_INTC_IMCR(0) = 0xffffffff;
    REG_INTC_IMCR(1) = 0xffffffff;

    REG_GINT_MASK = 0;
    REG_GINT_MASK = 1 << 31;
    *((volatile unsigned int *)(0xb2000038)) = 1;
    /* OUTREG32(INTC_ICMCR(0), 0xffffffff); */
    /* /\* unmask rtc interrupts *\/ */
    /* OUTREG32(INTC_ICMCR(1), 0x1); */
    /* Sleep on-board modules */
    jzsoc_do_sleep(sleep_gpio_save);

    /* config_irq_wakeup(); */

    load_pm_firmware_new(SLEEP_TCSM_SPACE);
    sleep_param = (struct sleep_param *)SLEEP_TCSM_SPACE;

    sleep_param->post_resume_pc = (unsigned int)restore_goto;
    sleep_param->uart_id = 2;

    memcpy(&s_reg.ddr_training_space,(void*)0x80000000,sizeof(s_reg.ddr_training_space));
    s_reg.opcr = INREG32(CPM_OPCR);
    s_reg.lcr = INREG32(CPM_LCR);

        /*
     *   set OPCR.
     */
    val = s_reg.opcr;
#if 0
    val &= ~((1 << 25) | (1 << 22) | (0xfff << 8) | (1 << 7) | (1 << 6) | (1 << 4) | (1 << 3) | (1 << 2));
    val |= (1 << 31) | (1 << 30) | (1 << 25) | (1 << 23) | (0xfff << 8) | (1 << 4) | (1 << 3) | (1 << 2);
#else
    val &= ~((1 << 31)|(1 << 30)| (1 << 25) | (1 << 22) | (0xfff << 8) | (1 << 7) | (1 << 6) | (1 << 4) | (1 << 3) | (1 << 2));
    val |=  (1 << 25) | (1 << 23) | (0xfff << 8) | (1 << 3) | (1 << 2) | (1 << 4);
#endif
    REG_CPM_OPCR = val;
    *(volatile unsigned int *)0xb000003c &= ~(1 << 31);
    *(volatile unsigned int *)0xb000003c |= (1 << 20);

    val = s_reg.lcr;
    val &= ~3;
    //val |= 1;
    val |= 0xff << 8;   /* power stable time */
    REG_CPM_LCR = val;

//  *(volatile unsigned int *)0xb0000010 &= ~(1 << 8);
//  *(volatile unsigned int *)0xb0000014 &= ~(1 << 7);

    printf("clkgr = 0x%08x\n", *(volatile unsigned int *)0xb0000020);
    printf("opcr = 0x%08x\n", *(volatile unsigned int *)0xb0000024);
    printf("otg phy = 0x%08x\n", *(volatile unsigned int *)0xb0000048);
    printf("otg = 0x%08x\n", *(volatile unsigned int *)0xb0000050);
    mb();
    save_goto((unsigned int)sleep_param->pm_core_enter);
    mb();

    memcpy((void*)0x80000000,&s_reg.ddr_training_space,sizeof(s_reg.ddr_training_space));
    dma_cache_wback_inv(0x80000000,sizeof(s_reg.ddr_training_space));

    OUTREG32(CPM_LCR, s_reg.lcr);
    OUTREG32(CPM_OPCR, s_reg.opcr);

    spin_unlock_irqrestore(sr);

    REG_GINT_MASK = gint_mask;
    /* Restore interrupts */

    //*((volatile unsigned int *)(0xb2000008)) = 1;
    REG_CPM_CLKGR0 = clkgr0;

    *((volatile unsigned int *)(0xb2000034)) = 1;
    OUTREG32(INTC_ICMR(0), icmr0);
    OUTREG32(INTC_ICMR(1), icmr1);

    /* Resume on-board modules */
    jzsoc_do_resume(sleep_gpio_save);

    /* Restore Oscillator and Power Control Register */
    /* OUTREG32(CPM_OPCR, opcr); */
    return 0;
}
#endif
/*
 * Function: Keep power for CPU core when reset.
 * So that EPC, tcsm and so on can maintain it's status after reset-key pressed.
 */
int reset_keep_power(void)
{
    rtc_write_reg(RTC_BASE + RTC_PWRONCR, rtc_read_reg(RTC_BASE + RTC_PWRONCR) & ~(1 << 0));

    return 0;
}

int drv_pmu_get_keypwr(void)
{
    int level = 0;

#ifdef BOARD_CANNA_OVC
    level = gpio_get_value(DET_PWR_PORT,DET_PWR_PIN);
    do
    {
        _delay_ms(5);                                       //È¥¶¶
    }while(level != gpio_get_value(DET_PWR_PORT,DET_PWR_PIN));
#endif

    return level;
}

void drv_pmu_power_down(void)
{
#ifdef BOARD_CANNA_OVC
    rt_kprintf("SET STB down...\n");

    gpio_set_value(EXT_DEV_RST_PORT, EXT_DEV_RST_PIN, 0);
    gpio_direction_output(CTR_STB_PORT, CTR_STB_PIN, 0);
    _delay_ms(100);
    gpio_direction_output(CTR_LOCK_PORT, CTR_LOCK_PIN, 1);
    _delay_ms(100);

    rt_hw_led_off(LED_GREEN);
    rt_hw_led_off(LED_RED);
    rt_hw_led_off(LED_BLUE);
#endif
}

void drv_pmu_power_up(void)
{

}

int drv_pmu_init(void)
{
    volatile unsigned int lcr, opcr;

    /* init opcr and lcr for idle */
    lcr = cpm_inl(CPM_LCR);
    lcr &= ~(0x3);              /* LCR.SLEEP.DS=0'b0,LCR.LPM=1'b00*/
    lcr |= 0xff << 8;           /* power stable time */
    cpm_outl(lcr, CPM_LCR);

    opcr = cpm_inl(CPM_OPCR);
    opcr |= 0xff << 8;          /* EXCLK stable time */
    opcr &= ~(1 << 4);          /* EXCLK stable time */
    cpm_outl(opcr, CPM_OPCR);

    return 0;
}



