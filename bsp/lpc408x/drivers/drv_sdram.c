/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-05-19     Bernard      The first version for LPC40xx
 */

#include <rtthread.h>

#ifdef BSP_USING_SDRAM
#include "drv_sdram.h"

#include <lpc_emc.h>
#include <lpc_timer.h>

static void  sdram_gpio_config(void)
{
    LPC_IOCON->P3_0 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* D0 @ P3.0 */
    LPC_IOCON->P3_1 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* D1 @ P3.1 */
    LPC_IOCON->P3_2 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* D2 @ P3.2 */
    LPC_IOCON->P3_3 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* D3 @ P3.3 */

    LPC_IOCON->P3_4 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* D4 @ P3.4 */
    LPC_IOCON->P3_5 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* D5 @ P3.5 */
    LPC_IOCON->P3_6 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* D6 @ P3.6 */
    LPC_IOCON->P3_7 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* D7 @ P3.7 */

    LPC_IOCON->P3_8 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* D8 @ P3.8 */
    LPC_IOCON->P3_9 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* D9 @ P3.9 */
    LPC_IOCON->P3_10 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* D10 @ P3.10 */
    LPC_IOCON->P3_11 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* D11 @ P3.11 */

    LPC_IOCON->P3_12 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* D12 @ P3.12 */
    LPC_IOCON->P3_13 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* D13 @ P3.13 */
    LPC_IOCON->P3_14 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* D14 @ P3.14 */
    LPC_IOCON->P3_15 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* D15 @ P3.15 */


    LPC_IOCON->P4_0 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* A0 @ P4.0 */
    LPC_IOCON->P4_1 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* A1 @ P4.1 */
    LPC_IOCON->P4_2 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* A2 @ P4.2 */
    LPC_IOCON->P4_3 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* A3 @ P4.3 */

    LPC_IOCON->P4_4 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* A4 @ P4.4 */
    LPC_IOCON->P4_5 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* A5 @ P4.5 */
    LPC_IOCON->P4_6 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* A6 @ P4.6 */
    LPC_IOCON->P4_7 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* A7 @ P4.7 */

    LPC_IOCON->P4_8 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* A8 @ P4.8 */
    LPC_IOCON->P4_9 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* A9 @ P4.9 */
    LPC_IOCON->P4_10 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* A10 @ P4.10 */
    LPC_IOCON->P4_11 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* A11 @ P4.11 */

    LPC_IOCON->P4_12 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* A12 @ P4.12 */
    LPC_IOCON->P4_13 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* A13 @ P4.13 */
    LPC_IOCON->P4_14 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* A14 @ P4.14 */

    LPC_IOCON->P4_25 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* WEN @ P4.25 */

    LPC_IOCON->P2_16 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* CASN @ P2.16 */
    LPC_IOCON->P2_17 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* RASN @ P2.17 */
    LPC_IOCON->P2_18 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* CLK[0] @ P2.18 */
    LPC_IOCON->P2_19 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* CLK[1] @ P2.19 */

    LPC_IOCON->P2_20 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* DYCSN[0] @ P2.20 */
    LPC_IOCON->P2_24 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* CKE[0] @ P2.24 */

    LPC_IOCON->P2_28 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* DQM[0] @ P2.28 */
    LPC_IOCON->P2_29 = (1 << 0 | 0 << 3 | 0 << 5 | 1 << 9); /* DQM[1] @ P2.29 */
}

void rt_hw_sdram_init(void)
{
    volatile uint32_t i;
    volatile uint32_t dwtemp;
    uint16_t wtemp = wtemp;
    TIM_TIMERCFG_Type TIM_ConfigStruct;

    TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
    TIM_ConfigStruct.PrescaleValue  = 1;

    /* Set configuration for Tim_config and Tim_MatchConfig */
    TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &TIM_ConfigStruct);

    LPC_SC->PCONP      |= 0x00000800;
    LPC_SC->EMCDLYCTL   = 0x00001010;
    LPC_EMC->Control = 0x00000001;
    LPC_EMC->Config  = 0x00000000;

    sdram_gpio_config();

    LPC_EMC->DynamicRP         = EMC_NS2CLK(20);        /* 20ns  */
    LPC_EMC->DynamicRAS        =  15;                   /* EMC_NS2CLK(42, nsPerClk),42ns to 100K ns  */
    LPC_EMC->DynamicSREX       = 1 - 1;                 /* tSRE, 1clk */
    LPC_EMC->DynamicAPR        = 2 - 1;                 /* Not found!!! Estimated as 2clk */
    LPC_EMC->DynamicDAL        = EMC_NS2CLK(20) + 2;    /* tDAL = tRP + tDPL = 20ns + 2clk  */
    LPC_EMC->DynamicWR         = 2 - 1;                 /* 2CLK */
    LPC_EMC->DynamicRC         = EMC_NS2CLK(63);        /* H57V2562GTR-75C tRC=63ns(min)*/
    LPC_EMC->DynamicRFC        = EMC_NS2CLK(63);        /* H57V2562GTR-75C tRFC=tRC */
    LPC_EMC->DynamicXSR        = 0x0000000F;            /* exit self-refresh to active */
    LPC_EMC->DynamicRRD        = EMC_NS2CLK(63);        /* 3clk, tRRD=15ns(min) */
    LPC_EMC->DynamicMRD        = 2 - 1;                 /* 2clk, tMRD=2clk(min) */

    LPC_EMC->DynamicReadConfig = 0x00000001;            /* Command delayed strategy, using EMCCLKDELAY */
    /* H57V2562GTR-75C: tCL=3CLK, tRCD=20ns(min), 3 CLK=24ns */
    LPC_EMC->DynamicRasCas0    = 0x303;

    /* For Manley lpc1778 SDRAM: H57V2562GTR-75C, 256Mb, 16Mx16, 4 banks, row=13, column=9 */
#ifdef SDRAM_CONFIG_16BIT
    LPC_EMC->DynamicConfig0    = 0x680;                 /* 256Mb, 16Mx16, 4 banks, row=13, column=9, RBC */
#elif defined SDRAM_CONFIG_32BIT
    LPC_EMC->DynamicConfig0 = 0x4680;                   /* 256Mb, 16Mx16, 4 banks, row=13, column=9, RBC */
#endif
    TIM_Waitms(100);

    LPC_EMC->DynamicControl    = 0x00000183;            /* Issue NOP command */
    TIM_Waitms(200);                                    /* wait 200ms */

    LPC_EMC->DynamicControl    = 0x00000103;            /* Issue PALL command */

    LPC_EMC->DynamicRefresh    = 0x00000002;            /* ( n * 16 ) -> 32 clock cycles */
    for (i = 0; i < 0x80; i++);                         /* wait 128 AHB clock cycles */

    LPC_EMC->DynamicRefresh    = EMC_SDRAM_REFRESH(64);

    LPC_EMC->DynamicControl    = 0x00000083;            /* Issue MODE command */

#ifdef SDRAM_CONFIG_16BIT
    wtemp = *((volatile uint16_t *)(EXT_SDRAM_BEGIN | (0x33 << 12)));   /* 8 burst, 3 CAS latency */
#elif defined SDRAM_CONFIG_32BIT
    dwtemp = *((volatile uint32_t *)(SDRAM_BASE | (0x32 << 13)));       /* 4 burst, 3 CAS latency */
#endif

    LPC_EMC->DynamicControl    = 0x00000000;                            /* Issue NORMAL command */

    LPC_EMC->DynamicConfig0 |= 0x80000;                                 /* enable buffer */
    TIM_Waitms(1);

    TIM_DeInit(LPC_TIM0);
}

#endif /* BSP_USING_SDRAM */
