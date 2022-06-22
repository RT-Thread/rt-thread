/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <rtthread.h>

#include <system_LPC177x_8x.h>
#include "LPC177x_8x.h"
#include "sdram.h"

//LPC_EMC_TypeDef   * const g_pEMC = ((LPC_EMC_TypeDef*) LPC_EMC_BASE);
//LPC_IOCON_TypeDef * const LPC_IOCON = ((LPC_IOCON_TypeDef*) LPC_IOCON_BASE);
#define SDRAM_BASE               0xA0000000    /* CS0 */
#define EMC_NS2CLK(ns, nsPerClk)    ((ns + nsPerClk - 1) / nsPerClk)

static void delayMs(int a,int b)
{
    volatile unsigned int i;
    for(i=0;i<10000;i++);
}

/*****************************************************************************
** Function name:       delayMs
**
** Descriptions:        Start the timer delay in milo seconds
**                      until elapsed
**
** parameters:          timer number, Delay value in milo second
**
** Returned value:      None
**
*****************************************************************************/
//void delayMs(uint8_t timer_num, uint32_t delayInMs)
//{
//  if ( timer_num == 0 )
//  {
//  LPC_TIM0->TCR = 0x02;       /* reset timer */
//  LPC_TIM0->PR  = 0x00;       /* set prescaler to zero */
//  LPC_TIM0->MR0 = delayInMs * (PeripheralClock / 1000 - 1);
//  LPC_TIM0->IR  = 0xff;       /* reset all interrrupts */
//  LPC_TIM0->MCR = 0x04;       /* stop timer on match */
//  LPC_TIM0->TCR = 0x01;       /* start timer */
//
//  /* wait until delay time has elapsed */
//  while (LPC_TIM0->TCR & 0x01);
//  }
//  else if ( timer_num == 1 )
//  {
//  LPC_TIM1->TCR = 0x02;       /* reset timer */
//  LPC_TIM1->PR  = 0x00;       /* set prescaler to zero */
//  LPC_TIM1->MR0 = delayInMs * (PeripheralClock / 1000 - 1);
//  LPC_TIM1->IR  = 0xff;       /* reset all interrrupts */
//  LPC_TIM1->MCR = 0x04;       /* stop timer on match */
//  LPC_TIM1->TCR = 0x01;       /* start timer */
//
//  /* wait until delay time has elapsed */
//  while (LPC_TIM1->TCR & 0x01);
//  }
//  else if ( timer_num == 2 )
//  {
//  LPC_TIM2->TCR = 0x02;       /* reset timer */
//  LPC_TIM2->PR  = 0x00;       /* set prescaler to zero */
//  LPC_TIM2->MR0 = delayInMs * (PeripheralClock / 1000 - 1);
//  LPC_TIM2->IR  = 0xff;       /* reset all interrrupts */
//  LPC_TIM2->MCR = 0x04;       /* stop timer on match */
//  LPC_TIM2->TCR = 0x01;       /* start timer */
//
//  /* wait until delay time has elapsed */
//  while (LPC_TIM2->TCR & 0x01);
//  }
//  else if ( timer_num == 3 )
//  {
//  LPC_TIM3->TCR = 0x02;       /* reset timer */
//  LPC_TIM3->PR  = 0x00;       /* set prescaler to zero */
//  LPC_TIM3->MR0 = delayInMs * (PeripheralClock / 1000 - 1);
//  LPC_TIM3->IR  = 0xff;       /* reset all interrrupts */
//  LPC_TIM3->MCR = 0x04;       /* stop timer on match */
//  LPC_TIM3->TCR = 0x01;       /* start timer */
//
//  /* wait until delay time has elapsed */
//  while (LPC_TIM3->TCR & 0x01);
//  }
//  return;
//}

static void EMC_GPIO_Init (void)
{
  LPC_IOCON->P3_0 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D0 @ P3.0 */
  LPC_IOCON->P3_1 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D1 @ P3.1 */
  LPC_IOCON->P3_2 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D2 @ P3.2 */
  LPC_IOCON->P3_3 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D3 @ P3.3 */

  LPC_IOCON->P3_4 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D4 @ P3.4 */
  LPC_IOCON->P3_5 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D5 @ P3.5 */
  LPC_IOCON->P3_6 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D6 @ P3.6 */
  LPC_IOCON->P3_7 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D7 @ P3.7 */

  LPC_IOCON->P3_8 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D8 @ P3.8 */
  LPC_IOCON->P3_9 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D9 @ P3.9 */
  LPC_IOCON->P3_10 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D10 @ P3.10 */
  LPC_IOCON->P3_11 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D11 @ P3.11 */

  LPC_IOCON->P3_12 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D12 @ P3.12 */
  LPC_IOCON->P3_13 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D13 @ P3.13 */
  LPC_IOCON->P3_14 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D14 @ P3.14 */
  LPC_IOCON->P3_15 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D15 @ P3.15 */

  LPC_IOCON->P3_16 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D16 @ P3.16 */
  LPC_IOCON->P3_17 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D17 @ P3.17 */
  LPC_IOCON->P3_18 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D18 @ P3.18 */
  LPC_IOCON->P3_19 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D19 @ P3.19 */

  LPC_IOCON->P3_20 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D20 @ P3.20 */
  LPC_IOCON->P3_21 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D21 @ P3.21 */
  LPC_IOCON->P3_22 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D22 @ P3.22 */
  LPC_IOCON->P3_23 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D23 @ P3.23 */

  LPC_IOCON->P3_24 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D24 @ P3.24 */
  LPC_IOCON->P3_25 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D25 @ P3.25 */
  LPC_IOCON->P3_26 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D26 @ P3.26 */
  LPC_IOCON->P3_27 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D27 @ P3.27 */

  LPC_IOCON->P3_28 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D28 @ P3.28 */
  LPC_IOCON->P3_29 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D29 @ P3.29 */
  LPC_IOCON->P3_30 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D30 @ P3.30 */
  LPC_IOCON->P3_31 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* D31 @ P3.31 */

  LPC_IOCON->P4_0 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A0 @ P4.0 */
  LPC_IOCON->P4_1 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A1 @ P4.1 */
  LPC_IOCON->P4_2 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A2 @ P4.2 */
  LPC_IOCON->P4_3 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A3 @ P4.3 */

  LPC_IOCON->P4_4 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A4 @ P4.4 */
  LPC_IOCON->P4_5 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A5 @ P4.5 */
  LPC_IOCON->P4_6 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A6 @ P4.6 */
  LPC_IOCON->P4_7 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A7 @ P4.7 */

  LPC_IOCON->P4_8 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A8 @ P4.8 */
  LPC_IOCON->P4_9 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A9 @ P4.9 */
  LPC_IOCON->P4_10 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A10 @ P4.10 */
  LPC_IOCON->P4_11 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A11 @ P4.11 */

  LPC_IOCON->P4_12 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A12 @ P4.12 */
  LPC_IOCON->P4_13 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A13 @ P4.13 */
  LPC_IOCON->P4_14 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A14 @ P4.14 */
  LPC_IOCON->P4_15 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A15 @ P4.15 */

  LPC_IOCON->P4_16 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A16 @ P4.16 */
  LPC_IOCON->P4_17 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A17 @ P4.17 */
  LPC_IOCON->P4_18 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A18 @ P4.18 */
  LPC_IOCON->P4_19 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A19 @ P4.19 */

  LPC_IOCON->P4_20 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A20 @ P4.20 */
  LPC_IOCON->P4_21 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A21 @ P4.21 */
  LPC_IOCON->P4_22 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A22 @ P4.22 */
  LPC_IOCON->P4_23 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* A23 @ P4.23 */

  LPC_IOCON->P4_25 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* WEN @ P4.25 */

#if 1
  LPC_IOCON->P4_24 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* OEN @ P4.24 */

  LPC_IOCON->P4_26 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* BLSN[0] @ P4.26 */
  LPC_IOCON->P4_27 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* BLSN[1] @ P4.27 */

  LPC_IOCON->P4_28 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* BLSN[2] @ P4.28 */
  LPC_IOCON->P4_29 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* BLSN[3] @ P4.29 */
  LPC_IOCON->P4_30 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* CSN[0] @ P4.30 */
  LPC_IOCON->P4_31 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* CSN[1] @ P4.31 */

  LPC_IOCON->P2_14 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* CSN[2] @ P2.14 */
  LPC_IOCON->P2_15 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* CSN[3] @ P2.15 */
#endif

#if 1
  LPC_IOCON->P2_16 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* CASN @ P2.16 */
  LPC_IOCON->P2_17 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* RASN @ P2.17 */
  LPC_IOCON->P2_18 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* CLK[0] @ P2.18 */
  LPC_IOCON->P2_19 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* CLK[1] @ P2.19 */

  LPC_IOCON->P2_20 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* DYCSN[0] @ P2.20 */
  LPC_IOCON->P2_21 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* DYCSN[1] @ P2.21 */
  LPC_IOCON->P2_22 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* DYCSN[2] @ P2.22 */
  LPC_IOCON->P2_23 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* DYCSN[3] @ P2.23 */

  LPC_IOCON->P2_24 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* CKE[0] @ P2.24 */

//  LPC_IOCON->P2_25 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* CKE[1] @ P2.25 */
  LPC_IOCON->P2_26 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* CKE[2] @ P2.26 */
  LPC_IOCON->P2_27 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* CKE[3] @ P2.27 */

  LPC_IOCON->P2_28 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* DQM[0] @ P2.28 */
  LPC_IOCON->P2_29 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* DQM[1] @ P2.29 */
  LPC_IOCON->P2_30 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* DQM[2] @ P2.30 */
  LPC_IOCON->P2_31 = (1<<0 | 0<<3 | 0<<5 | 1<<9); /* DQM[3] @ P2.31 */
#endif
}

void SDRAM_Init (void)
{
    uint32_t i, dwtemp = dwtemp;
    uint16_t wtemp = wtemp;
    uint32_t mhz, nsPerClk;
    /* Enable External Memory Controller power/clock */
    LPC_SC->PCONP      |= 0x00000800;
    LPC_SC->EMCDLYCTL   = 0x00001010;
    LPC_EMC->Control = 0x00000001;
    LPC_EMC->Config  = 0x00000000;

    EMC_GPIO_Init();

    mhz = SystemCoreClock / 1000000;
    if (LPC_SC->EMCCLKSEL)
        mhz >>= 1;
    nsPerClk = 1000 / mhz;
    LPC_EMC->DynamicRP         = EMC_NS2CLK(20, nsPerClk); /* 20ns,  */
    LPC_EMC->DynamicRAS        = /*EMC_NS2CLK(42, nsPerClk);*/ 15; /* 42ns to 100K ns,  */
    LPC_EMC->DynamicSREX       = 1 - 1; /* tSRE, 1clk, */
    LPC_EMC->DynamicAPR        = 2 - 1; /* Not found!!! Estimated as 2clk, */
    LPC_EMC->DynamicDAL        = EMC_NS2CLK(20, nsPerClk) + 2; /* tDAL = tRP + tDPL = 20ns + 2clk  */
    LPC_EMC->DynamicWR         = 2 - 1; /* 2CLK,  */
    LPC_EMC->DynamicRC         = EMC_NS2CLK(63, nsPerClk); /* H57V2562GTR-75C tRC=63ns(min)*/
    LPC_EMC->DynamicRFC        = EMC_NS2CLK(63, nsPerClk); /* H57V2562GTR-75C tRFC=tRC */
    LPC_EMC->DynamicXSR        = 0x0000000F; /* exit self-refresh to active, 不知道，设为最久  */
    LPC_EMC->DynamicRRD        = EMC_NS2CLK(63, nsPerClk); /* 3clk, tRRD=15ns(min) */
    LPC_EMC->DynamicMRD        = 2 - 1; /* 2clk, tMRD=2clk(min) */

//    LPC_EMC->DynamicRP         = 0x00000002; /* 3clk=24ns,  */
//    LPC_EMC->DynamicRAS        = 0x00000005; /* 6clk=48ns,  */
//    LPC_EMC->DynamicSREX       = 0x00000001; /* 2clk, */
//    LPC_EMC->DynamicAPR        = 0x00000001; /* 2clk, */
//    LPC_EMC->DynamicDAL        = 0x00000005; /* 6clk,  */
//    LPC_EMC->DynamicWR         = 0x00000001; /* 2CLK,  */
//    LPC_EMC->DynamicRC         = 0x00000008; /* 9clk, H57V2562GTR-75C tRC=63ns(min)*/
//    LPC_EMC->DynamicRFC        = 0x00000008; /* 9clk, H57V2562GTR-75C tRFC=63ns(min) */
//    LPC_EMC->DynamicXSR        = 0x00000007; /* 8clk,  */
//    LPC_EMC->DynamicRRD        = 0x00000002; /* 3clk, tRRD=15ns(min) */
//    LPC_EMC->DynamicMRD        = 0x00000001; /* 2clk, tMRD=2clk(min) */

    LPC_EMC->DynamicReadConfig = 0x00000001; /* Command delayed strategy, using EMCCLKDELAY */
    /* H57V2562GTR-75C: tCL=3CLK, tRCD=20ns(min), 3 CLK=24ns */
    LPC_EMC->DynamicRasCas0    = 0x00000303; /* 3 RAS, 3 CAS latency */

    /* For Manley lpc1778 SDRAM: H57V2562GTR-75C, 256Mb, 16Mx16, 4 banks, row=13, column=9 */
#ifdef SDRAM_CONFIG_16BIT
    LPC_EMC->DynamicConfig0    = 0x680; /* 256Mb, 16Mx16, 4 banks, row=13, column=9, RBC */
#elif defined SDRAM_CONFIG_32BIT
    LPC_EMC->DynamicConfig0 = 0x4680; /* 256Mb, 16Mx16, 4 banks, row=13, column=9, RBC */
#endif
    delayMs(0, 100);

    LPC_EMC->DynamicControl    = 0x00000183; /* Issue NOP command */
    delayMs(0, 200);                              /* wait 200ms */

    LPC_EMC->DynamicControl    = 0x00000103; /* Issue PALL command */

    LPC_EMC->DynamicRefresh    = 0x00000002; /* ( n * 16 ) -> 32 clock cycles */
    for(i = 0; i < 0x80; i++);                /* wait 128 AHB clock cycles */
    /* 64ms/8192=7.8125us, nx16x8.33ns<7.8125us, n<58.6*/
    wtemp = 64000000 / (1 << 13);
    wtemp -= 16;
    wtemp >>= 4;
    wtemp = wtemp * mhz / 1000;
    LPC_EMC->DynamicRefresh    = wtemp;

    LPC_EMC->DynamicControl    = 0x00000083; /* Issue MODE command */

#ifdef SDRAM_CONFIG_16BIT

    wtemp = *((volatile uint16_t *)(SDRAM_BASE | (0x33<<12))); /* 8 burst, 3 CAS latency */
#elif defined SDRAM_CONFIG_32BIT
    dwtemp = *((volatile uint32_t *)(SDRAM_BASE | (0x32<<13))); /* 4 burst, 3 CAS latency */
#endif

    LPC_EMC->DynamicControl    = 0x00000000; /* Issue NORMAL command */

    LPC_EMC->DynamicConfig0 |= 0x80000; /* enable buffer */
    delayMs(0, 1);

}


