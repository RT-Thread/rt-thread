/*
** ###################################################################
**     Processors:          MCIMX6Y2CVM05
**                          MCIMX6Y2CVM08
**                          MCIMX6Y2DVM05
**                          MCIMX6Y2DVM09
**
**     Compilers:           Keil ARM C/C++ Compiler
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    IMX6ULLRM, Rev. 1, Feb. 2017
**     Version:             rev. 3.0, 2017-02-28
**     Build:               b170410
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2017 NXP
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of the copyright holder nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2015-12-18)
**         Initial version.
**     - rev. 2.0 (2016-08-02)
**         Rev.B Header GA
**     - rev. 3.0 (2017-02-28)
**         Rev.1 Header GA
**
** ###################################################################
*/

/*!
 * @file MCIMX6Y2
 * @version 3.0
 * @date 2017-02-28
 * @brief Device specific configuration file for MCIMX6Y2 (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "fsl_device_registers.h"

/* Transaction Drivers Handler Declaration */
extern void CAN1_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void CAN2_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void ECSPI1_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void ECSPI2_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void ECSPI3_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void ECSPI4_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void ENET1_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void ENET1_Driver1588IRQHandler (uint32_t giccIar, void *userParam);
extern void ENET2_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void ENET2_Driver1588IRQHandler (uint32_t giccIar, void *userParam);
extern void I2C1_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void I2C2_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void I2C3_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void I2C4_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void I2S1_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void I2S2_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void I2S3_Tx_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void I2S3_Rx_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void UART1_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void UART2_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void UART3_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void UART4_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void UART5_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void UART6_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void UART7_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void UART8_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void USDHC1_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void USDHC2_DriverIRQHandler (uint32_t giccIar, void *userParam);
extern void SDMA_DriverIRQHandler (uint32_t giccIar, void *userParam);

#if defined(__IAR_SYSTEMS_ICC__)
#pragma weak CAN1_DriverIRQHandler=defaultIrqHandler
#pragma weak CAN2_DriverIRQHandler=defaultIrqHandler
#pragma weak ECSPI1_DriverIRQHandler=defaultIrqHandler
#pragma weak ECSPI2_DriverIRQHandler=defaultIrqHandler
#pragma weak ECSPI3_DriverIRQHandler=defaultIrqHandler
#pragma weak ECSPI4_DriverIRQHandler=defaultIrqHandler
#pragma weak ENET1_DriverIRQHandler=defaultIrqHandler
#pragma weak ENET2_DriverIRQHandler=defaultIrqHandler
#pragma weak ENET1_Driver1588IRQHandler=defaultIrqHandler
#pragma weak ENET2_Driver1588IRQHandler=defaultIrqHandler
#pragma weak I2C1_DriverIRQHandler=defaultIrqHandler
#pragma weak I2C2_DriverIRQHandler=defaultIrqHandler
#pragma weak I2C3_DriverIRQHandler=defaultIrqHandler
#pragma weak I2C4_DriverIRQHandler=defaultIrqHandler
#pragma weak I2S1_DriverIRQHandler=defaultIrqHandler
#pragma weak I2S2_DriverIRQHandler=defaultIrqHandler
#pragma weak I2S3_Tx_DriverIRQHandler=defaultIrqHandler
#pragma weak I2S3_Rx_DriverIRQHandler=defaultIrqHandler
#pragma weak UART1_DriverIRQHandler=defaultIrqHandler
#pragma weak UART2_DriverIRQHandler=defaultIrqHandler
#pragma weak UART3_DriverIRQHandler=defaultIrqHandler
#pragma weak UART4_DriverIRQHandler=defaultIrqHandler
#pragma weak UART5_DriverIRQHandler=defaultIrqHandler
#pragma weak UART6_DriverIRQHandler=defaultIrqHandler
#pragma weak UART7_DriverIRQHandler=defaultIrqHandler
#pragma weak UART8_DriverIRQHandler=defaultIrqHandler
#pragma weak USDHC1_DriverIRQHandler=defaultIrqHandler
#pragma weak USDHC2_DriverIRQHandler=defaultIrqHandler
#pragma weak SDMA_DriverIRQHandler=defaultIrqHandler
#elif defined(__GNUC__)
void CAN1_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void CAN2_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void ECSPI1_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void ECSPI2_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void ECSPI3_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void ECSPI4_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void ENET1_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void ENET2_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void ENET1_Driver1588IRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void ENET2_Driver1588IRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void I2C1_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void I2C2_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void I2C3_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void I2C4_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void I2S1_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void I2S2_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void I2S3_Tx_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void I2S3_Rx_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void UART1_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void UART2_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void UART3_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void UART4_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void UART5_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void UART6_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void UART7_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void UART8_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void USDHC1_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void USDHC2_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
void SDMA_DriverIRQHandler() __attribute__((weak, alias("defaultIrqHandler")));
#else
  #error Not supported compiler type
#endif

extern uint32_t __VECTOR_TABLE[];

/* Local irq table and nesting level value */
static sys_irq_handle_t irqTable[NUMBER_OF_INT_VECTORS];
static uint32_t irqNesting;

/* Local IRQ functions */
static void defaultIrqHandler (uint32_t giccIar, void *userParam) {
  while(1) {
  }
}

/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

void SystemInit (void) {
  uint32_t sctlr;
  uint32_t actlr;
#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
  uint32_t cpacr;
  uint32_t fpexc;
#endif

  L1C_InvalidateInstructionCacheAll();
  L1C_InvalidateDataCacheAll();

  actlr = __get_ACTLR();
  actlr = (actlr | ACTLR_SMP_Msk);       /* Change to SMP mode before enable DCache */
  __set_ACTLR(actlr);

  sctlr = __get_SCTLR();
  sctlr = (sctlr & ~(SCTLR_V_Msk       | /* Use low vector */
                     SCTLR_A_Msk       | /* Disable alignment fault checking */
                     SCTLR_M_Msk))       /* Disable MMU */
                 |  (SCTLR_I_Msk       | /* Enable ICache */
                     SCTLR_Z_Msk       | /* Enable Prediction */
                     SCTLR_CP15BEN_Msk | /* Enable CP15 barrier operations */
                     SCTLR_C_Msk);       /* Enable DCache */
  __set_SCTLR(sctlr);

  /* Set vector base address */
  GIC_Init();
  __set_VBAR((uint32_t)__VECTOR_TABLE);

#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
  cpacr = __get_CPACR();
  /* Enable NEON and FPU */
  cpacr = (cpacr & ~(CPACR_ASEDIS_Msk | CPACR_D32DIS_Msk))
         |  (3UL << CPACR_cp10_Pos) | (3UL << CPACR_cp11_Pos);
  __set_CPACR(cpacr);

  fpexc = __get_FPEXC();
  fpexc |= 0x40000000UL;  /* Enable NEON and FPU */
  __set_FPEXC(fpexc);
#endif /* ((__FPU_PRESENT == 1) && (__FPU_USED == 1)) */
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {
  /* i.MX6ULL systemCoreClockUpdate */
  uint32_t PLL1SWClock;
  uint32_t PLL2MainClock;
  if (CCM->CCSR & CCM_CCSR_PLL1_SW_CLK_SEL_MASK)
  {
    if (CCM->CCSR & CCM_CCSR_STEP_SEL_MASK)
    {
        /* Get SYS PLL clock*/
        if (CCM_ANALOG->PLL_SYS & CCM_ANALOG_PLL_SYS_DIV_SELECT_MASK)
        {
          PLL2MainClock = (24000000UL * 22UL + (uint64_t)(24000000UL) * (uint64_t)(CCM_ANALOG->PLL_SYS_NUM) / (uint64_t)(CCM_ANALOG->PLL_SYS_DENOM));
        }
        else
        {
          PLL2MainClock = (24000000UL * 20UL + (uint64_t)(24000000UL) * (uint64_t)(CCM_ANALOG->PLL_SYS_NUM) / (uint64_t)(CCM_ANALOG->PLL_SYS_DENOM));
        }

        if (CCM->CCSR & CCM_CCSR_SECONDARY_CLK_SEL_MASK)
        {
            /* PLL2 ---> Secondary_clk ---> Step Clock ---> CPU Clock */
            PLL1SWClock = PLL2MainClock;
        }
        else
        {
            /* PLL2 PFD2 ---> Secondary_clk ---> Step Clock ---> CPU Clock */
            PLL1SWClock = ((uint64_t)PLL2MainClock * 18) / ((CCM_ANALOG->PFD_528 & CCM_ANALOG_PFD_528_PFD2_FRAC_MASK) >> CCM_ANALOG_PFD_528_PFD2_FRAC_SHIFT);
        }
    }
    else
    {
      /* Osc_clk (24M) ---> Step Clock ---> CPU Clock */
      PLL1SWClock = 24000000UL;
    }
  }
  else
  {
    /* ARM PLL ---> CPU Clock */
    PLL1SWClock = 24000000UL;
    PLL1SWClock = ( PLL1SWClock * (CCM_ANALOG->PLL_ARM & CCM_ANALOG_PLL_ARM_DIV_SELECT_MASK) >> CCM_ANALOG_PLL_ARM_DIV_SELECT_SHIFT) >> 1UL;
   }

  SystemCoreClock = PLL1SWClock / (((CCM->CACRR & CCM_CACRR_ARM_PODF_MASK) >> CCM_CACRR_ARM_PODF_SHIFT) + 1UL);
}

/* ----------------------------------------------------------------------------
   -- SystemInitIrqTable()
   ---------------------------------------------------------------------------- */

void SystemInitIrqTable (void) {
  uint32_t i;

  /* First set all handler to default */
  for (i = 0; i < NUMBER_OF_INT_VECTORS; i++) {
    SystemInstallIrqHandler((IRQn_Type)i, defaultIrqHandler, NULL);
  }

  /* Then set transaction drivers handler */
  /* FlexCAN transaction drivers handler */
  SystemInstallIrqHandler(CAN1_IRQn, CAN1_DriverIRQHandler, NULL);
  SystemInstallIrqHandler(CAN2_IRQn, CAN2_DriverIRQHandler, NULL);
  /* ECSPI transaction drivers handler */
  SystemInstallIrqHandler(eCSPI1_IRQn, ECSPI1_DriverIRQHandler, NULL);
  SystemInstallIrqHandler(eCSPI2_IRQn, ECSPI2_DriverIRQHandler, NULL);
  SystemInstallIrqHandler(eCSPI3_IRQn, ECSPI3_DriverIRQHandler, NULL);
  SystemInstallIrqHandler(eCSPI4_IRQn, ECSPI4_DriverIRQHandler, NULL);
  /* ENET transaction drivers handler */
  SystemInstallIrqHandler(ENET1_IRQn, ENET1_DriverIRQHandler, NULL);
  SystemInstallIrqHandler(ENET1_1588_IRQn, ENET1_Driver1588IRQHandler, NULL);
  SystemInstallIrqHandler(ENET2_IRQn, ENET2_DriverIRQHandler, NULL);
  SystemInstallIrqHandler(ENET2_1588_IRQn, ENET2_Driver1588IRQHandler, NULL);
  /* I2C transaction drivers handler */
  SystemInstallIrqHandler(I2C1_IRQn, I2C1_DriverIRQHandler, NULL);
  SystemInstallIrqHandler(I2C2_IRQn, I2C2_DriverIRQHandler, NULL);
  SystemInstallIrqHandler(I2C3_IRQn, I2C3_DriverIRQHandler, NULL);
  SystemInstallIrqHandler(I2C4_IRQn, I2C4_DriverIRQHandler, NULL);
  /* I2S transaction drivers handler */
  SystemInstallIrqHandler(SAI1_IRQn, I2S1_DriverIRQHandler, NULL);
  SystemInstallIrqHandler(SAI2_IRQn, I2S2_DriverIRQHandler, NULL);
  SystemInstallIrqHandler(SAI3_TX_IRQn, I2S3_Tx_DriverIRQHandler, NULL);
  SystemInstallIrqHandler(SAI3_RX_IRQn, I2S3_Rx_DriverIRQHandler, NULL);
  /* UART transaction drivers handler */
  SystemInstallIrqHandler(UART1_IRQn, UART1_DriverIRQHandler, NULL);
  SystemInstallIrqHandler(UART2_IRQn, UART2_DriverIRQHandler, NULL);
  SystemInstallIrqHandler(UART3_IRQn, UART3_DriverIRQHandler, NULL);
  SystemInstallIrqHandler(UART4_IRQn, UART4_DriverIRQHandler, NULL);
  SystemInstallIrqHandler(UART5_IRQn, UART5_DriverIRQHandler, NULL);
  SystemInstallIrqHandler(UART6_IRQn, UART6_DriverIRQHandler, NULL);
  SystemInstallIrqHandler(UART7_IRQn, UART7_DriverIRQHandler, NULL);
  SystemInstallIrqHandler(UART8_IRQn, UART8_DriverIRQHandler, NULL);
  /* USDHC transaction drivers handler */
  SystemInstallIrqHandler(USDHC1_IRQn, USDHC1_DriverIRQHandler, NULL);
  SystemInstallIrqHandler(USDHC2_IRQn, USDHC2_DriverIRQHandler, NULL);
  /* SDMA transaction driver handler */
  SystemInstallIrqHandler(SDMA_IRQn, SDMA_DriverIRQHandler, NULL);
}

/* ----------------------------------------------------------------------------
   -- SystemInstallIrqHandler()
   ---------------------------------------------------------------------------- */

void SystemInstallIrqHandler(IRQn_Type irq, system_irq_handler_t handler, void *userParam) {
  irqTable[irq].irqHandler = handler;
  irqTable[irq].userParam = userParam;
}

/* ----------------------------------------------------------------------------
   -- SystemIrqHandler()
   ---------------------------------------------------------------------------- */

#if defined(__IAR_SYSTEMS_ICC__)
#pragma weak SystemIrqHandler
void SystemIrqHandler(uint32_t giccIar) {
#elif defined(__GNUC__)
__attribute__((weak)) void SystemIrqHandler(uint32_t giccIar) {
#else
  #error Not supported compiler type
#endif
  uint32_t intNum = giccIar & 0x3FFUL;

  /* Spurious interrupt ID or Wrong interrupt number */
  if ((intNum == 1023) || (intNum >= NUMBER_OF_INT_VECTORS))
  {
    return;
  }

  irqNesting++;

  __enable_irq();      /* Support nesting interrupt */

  /* Now call the real irq handler for intNum */
  irqTable[intNum].irqHandler(giccIar, irqTable[intNum].userParam);

  __disable_irq();

  irqNesting--;
}

uint32_t SystemGetIRQNestingLevel(void)
{
  return irqNesting;
}

/* Leverage GPT1 to provide Systick */
void SystemSetupSystick(uint32_t tickRateHz, void *tickHandler, uint32_t intPriority)
{
    uint32_t clockFreq;
    uint32_t spllTmp;

    /* Install IRQ handler for GPT1 */
    SystemInstallIrqHandler(GPT1_IRQn, (system_irq_handler_t)(uint32_t)tickHandler, NULL);

    /* Enable Systick all the time */
    CCM->CCGR1 |= CCM_CCGR1_CG10_MASK | CCM_CCGR1_CG11_MASK;

    GPT1->CR = GPT_CR_SWR_MASK;
    /* Wait reset finished. */
    while (GPT1->CR == GPT_CR_SWR_MASK)
    {
    }
    /* Use peripheral clock source IPG */
    GPT1->CR = GPT_CR_WAITEN_MASK | GPT_CR_STOPEN_MASK | GPT_CR_DOZEEN_MASK |
               GPT_CR_DBGEN_MASK | GPT_CR_ENMOD_MASK | GPT_CR_CLKSRC(1UL);
    /* Set clock divider to 1 */
    GPT1->PR = 0;

    /* Get IPG clock*/
    /* Periph_clk2_clk ---> Periph_clk */
    if (CCM->CBCDR & CCM_CBCDR_PERIPH_CLK_SEL_MASK)
    {
        switch (CCM->CBCMR & CCM_CBCMR_PERIPH_CLK2_SEL_MASK)
        {
            /* Pll3_sw_clk ---> Periph_clk2_clk ---> Periph_clk */
            case CCM_CBCMR_PERIPH_CLK2_SEL(0U):
                clockFreq = (24000000UL * ((CCM_ANALOG->PLL_USB1 & CCM_ANALOG_PLL_USB1_DIV_SELECT_MASK) ? 22U : 20U));
                break;

            /* Osc_clk ---> Periph_clk2_clk ---> Periph_clk */
            case CCM_CBCMR_PERIPH_CLK2_SEL(1U):
                clockFreq = 24000000UL;
                break;

            case CCM_CBCMR_PERIPH_CLK2_SEL(2U):
            case CCM_CBCMR_PERIPH_CLK2_SEL(3U):
            default:
                clockFreq = 0U;
                break;
        }

        clockFreq /= (((CCM->CBCDR & CCM_CBCDR_PERIPH_CLK2_PODF_MASK) >> CCM_CBCDR_PERIPH_CLK2_PODF_SHIFT) + 1U);
    }
    /* Pll2_main_clk ---> Periph_clk */
    else
    {
        /* Get SYS PLL clock*/
        if (CCM_ANALOG->PLL_SYS & CCM_ANALOG_PLL_SYS_DIV_SELECT_MASK)
        {
          spllTmp = (24000000UL * 22UL + (uint64_t)(24000000UL) * (uint64_t)(CCM_ANALOG->PLL_SYS_NUM) / (uint64_t)(CCM_ANALOG->PLL_SYS_DENOM));
        }
        else
        {
          spllTmp = (24000000UL * 20UL + (uint64_t)(24000000UL) * (uint64_t)(CCM_ANALOG->PLL_SYS_NUM) / (uint64_t)(CCM_ANALOG->PLL_SYS_DENOM));
        }

        switch (CCM->CBCMR & CCM_CBCMR_PRE_PERIPH_CLK_SEL_MASK)
        {
            /* PLL2 ---> Pll2_main_clk ---> Periph_clk */
            case CCM_CBCMR_PRE_PERIPH_CLK_SEL(0U):
                clockFreq = spllTmp;
                break;

            /* PLL2 PFD2 ---> Pll2_main_clk ---> Periph_clk */
            case CCM_CBCMR_PRE_PERIPH_CLK_SEL(1U):
                clockFreq = ((uint64_t)spllTmp * 18) / ((CCM_ANALOG->PFD_528 & CCM_ANALOG_PFD_528_PFD2_FRAC_MASK) >> CCM_ANALOG_PFD_528_PFD2_FRAC_SHIFT);
                break;

            /* PLL2 PFD0 ---> Pll2_main_clk ---> Periph_clk */
            case CCM_CBCMR_PRE_PERIPH_CLK_SEL(2U):
                clockFreq = ((uint64_t)spllTmp * 18) / ((CCM_ANALOG->PFD_528 & CCM_ANALOG_PFD_528_PFD0_FRAC_MASK) >> CCM_ANALOG_PFD_528_PFD0_FRAC_SHIFT);
                break;

            /* PLL2 PFD2 divided(/2) ---> Pll2_main_clk ---> Periph_clk */
            case CCM_CBCMR_PRE_PERIPH_CLK_SEL(3U):
                clockFreq = ((((uint64_t)spllTmp * 18) / ((CCM_ANALOG->PFD_528 & CCM_ANALOG_PFD_528_PFD2_FRAC_MASK) >> CCM_ANALOG_PFD_528_PFD2_FRAC_SHIFT)) >> 1U);
                break;

            default:
                clockFreq = 0U;
                break;
        }
    }
    clockFreq /= (((CCM->CBCDR & CCM_CBCDR_AHB_PODF_MASK) >> CCM_CBCDR_AHB_PODF_SHIFT) + 1U);
    clockFreq /= (((CCM->CBCDR & CCM_CBCDR_IPG_PODF_MASK) >> CCM_CBCDR_IPG_PODF_SHIFT) + 1U);

    /* Set timeout value and enable interrupt */
    GPT1->OCR[0] = clockFreq / tickRateHz - 1UL;
    GPT1->IR = GPT_IR_OF1IE_MASK;

    /* Set interrupt priority */
    GIC_SetPriority(GPT1_IRQn, intPriority);
    /* Enable IRQ */
    GIC_EnableIRQ(GPT1_IRQn);

    /* Start GPT counter */
    GPT1->CR |= GPT_CR_EN_MASK;
}

void SystemClearSystickFlag(void)
{
    GPT1->SR = GPT_SR_OF1_MASK;
}
