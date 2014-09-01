/**********************************************************************
* $Id$      lpc_clkpwr.c            2011-06-02
*//**
* @file     lpc_clkpwr.c
* @brief    Contains all functions support for Clock and Power Control
*           firmware library on LPC
* @version  1.0
* @date     02. June. 2011
* @author   NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup CLKPWR
 * @{
 */
#ifdef __BUILD_WITH_EXAMPLE__
#include "lpc_libcfg.h"
#else
#include "lpc_libcfg_default.h"
#endif /* __BUILD_WITH_EXAMPLE__ */
#ifdef _CLKPWR
 
/* Includes ------------------------------------------------------------------- */
#include "lpc_clkpwr.h"

uint32_t USBFrequency = 0;


/* Public Functions ----------------------------------------------------------- */
/** @addtogroup CLKPWR_Public_Functions
 * @{
 */

/*********************************************************************//**
 * @brief       Set value of each Peripheral Clock Selection
 * @param[in]   ClkType clock type that will be divided, should be:
 *              - CLKPWR_CLKTYPE_CPU        : CPU clock
 *              - CLKPWR_CLKTYPE_PER        : Peripheral clock
 *              - CLKPWR_CLKTYPE_EMC        : EMC clock
 *              - CLKPWR_CLKTYPE_USB        : USB clock
 * @param[in]   DivVal  Value of divider. This value should be set as follows:
 *                  - CPU clock: DivVal must be in range: 0..31
 *                  - Peripheral clock: DivVal must be in range: 0..31
 *                  - EMC clock: DivVal must be:
 *                          + 0: The EMC uses the same clock as the CPU
 *                          + 1: The EMC uses a clock at half the rate of the CPU
 *                  - USB clock: DivVal must be:
 *                          + 0: the divider is turned off, no clock will
 *                               be provided to the USB subsystem
 *                          + 4: PLL0 output is divided by 4. PLL0 output must be 192MHz
 *                          + 6: PLL0 output is divided by 6. PLL0 output must be 288MHz
 * @return none
 * Note: Pls assign right DivVal, this function will not check if it is illegal.
 **********************************************************************/
void CLKPWR_SetCLKDiv (uint8_t ClkType, uint8_t DivVal)
{
    uint32_t tmp;
    switch(ClkType)
    {
    case CLKPWR_CLKTYPE_CPU:
        tmp =   LPC_SC->CCLKSEL & ~(0x1F);
        tmp |=  DivVal & 0x1F;
        LPC_SC->CCLKSEL = tmp;
        SystemCoreClockUpdate(); //Update clock
        break;
    case CLKPWR_CLKTYPE_PER:
        tmp =   LPC_SC->PCLKSEL & ~(0x1F);
        tmp |=  DivVal & 0x1F;
        LPC_SC->PCLKSEL = tmp;
        SystemCoreClockUpdate(); //Update clock
        break;
    case CLKPWR_CLKTYPE_EMC:
        tmp =   LPC_SC->EMCCLKSEL & ~(0x01);
        tmp |=  DivVal & 0x01;
        LPC_SC->EMCCLKSEL = tmp;
        SystemCoreClockUpdate(); //Update clock
        break;
    case CLKPWR_CLKTYPE_USB:
        tmp =   LPC_SC->USBCLKSEL & ~(0x1F);
        tmp |=  DivVal & 0x1F;
        LPC_SC->USBCLKSEL |= DivVal & 0x1F;
        SystemCoreClockUpdate(); //Update clock
        break;
    default:
        while(1);//Error Loop;
    }
}

/*********************************************************************//**
 * @brief       Get current clock value
 * @param[in]   ClkType clock type that will be divided, should be:
 *              - CLKPWR_CLKTYPE_CPU        : CPU clock
 *              - CLKPWR_CLKTYPE_PER        : Peripheral clock
 *              - CLKPWR_CLKTYPE_EMC        : EMC clock
 *              - CLKPWR_CLKTYPE_USB        : USB clock
 **********************************************************************/
uint32_t CLKPWR_GetCLK (uint8_t ClkType)
{
    switch(ClkType)
    {
        case CLKPWR_CLKTYPE_CPU:
            return SystemCoreClock;

        case CLKPWR_CLKTYPE_PER:
            return PeripheralClock;

        case CLKPWR_CLKTYPE_EMC:
            return EMCClock;

        case CLKPWR_CLKTYPE_USB:
            return USBClock;

        default:
            while(1);//error loop
    }
}

/*********************************************************************//**
 * @brief       Configure power supply for each peripheral according to NewState
 * @param[in]   PPType  Type of peripheral used to enable power,
 *              should be one of the following:
 *              -  CLKPWR_PCONP_PCLCD       : LCD
 *              -  CLKPWR_PCONP_PCTIM0      : Timer 0
 *              -  CLKPWR_PCONP_PCTIM1      : Timer 1
 *              -  CLKPWR_PCONP_PCUART0     : UART 0
 *              -  CLKPWR_PCONP_PCUART1     : UART 1
 *              -  CLKPWR_PCONP_PCPWM0      : PWM 0
 *              -  CLKPWR_PCONP_PCPWM1      : PWM 1
 *              -  CLKPWR_PCONP_PCI2C0      : I2C 0
 *              -  CLKPWR_PCONP_PCUART4     : UART4
 *              -  CLKPWR_PCONP_PCLCD       : LCD
 *              -  CLKPWR_PCONP_PCTIM0      : Timer 0
 *              -  CLKPWR_PCONP_PCRTC       : RTC
 *              -  CLKPWR_PCONP_PCSSP1      : SSP 1
 *              -  CLKPWR_PCONP_PCEMC       : EMC
 *              -  CLKPWR_PCONP_PCADC       : ADC
 *              -  CLKPWR_PCONP_PCAN1       : CAN 1
 *              -  CLKPWR_PCONP_PCAN2       : CAN 2
 *              -  CLKPWR_PCONP_PCGPIO      : GPIO
 *              -  CLKPWR_PCONP_PCMC        : MCPWM
 *              -  CLKPWR_PCONP_PCQEI       : QEI
 *              -  CLKPWR_PCONP_PCI2C1      : I2C 1
 *              -  CLKPWR_PCONP_PCSSP2      : SSP 2
 *              -  CLKPWR_PCONP_PCSSP0      : SSP 0
 *              -  CLKPWR_PCONP_PCTIM2      : Timer 2
 *              -  CLKPWR_PCONP_PCTIM3      : Timer 3
 *              -  CLKPWR_PCONP_PCUART2     : UART 2
 *              -  CLKPWR_PCONP_PCUART3     : UART 3
 *              -  CLKPWR_PCONP_PCI2C2      : I2C 2
 *              -  CLKPWR_PCONP_PCI2S       : I2S
 *              -  CLKPWR_PCONP_PCSDC       : SDC
 *              -  CLKPWR_PCONP_PCGPDMA     : GPDMA
 *              -  CLKPWR_PCONP_PCENET      : Ethernet
 *              -  CLKPWR_PCONP_PCUSB       : USB
 *
 * @param[in]   NewState    New state of Peripheral Power, should be:
 *              - ENABLE    : Enable power for this peripheral
 *              - DISABLE   : Disable power for this peripheral
 *
 * @return none
 **********************************************************************/
void CLKPWR_ConfigPPWR (uint32_t PPType, FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        LPC_SC->PCONP |= PPType;
    }
    else if (NewState == DISABLE)
    {
        LPC_SC->PCONP &= ~PPType;
    }
}

#if 0
// nxp21346
/*********************************************************************//**
 * @brief       Configure hardware reset for each peripheral according to NewState
 * @param[in]   PPType  Type of peripheral used to enable power,
 *              should be one of the following:
 *              -  CLKPWR_RSTCON0_LCD       : LCD
 *              -  CLKPWR_RSTCON0_TIM0      : Timer 0
                -  CLKPWR_RSTCON0_TIM1      : Timer 1
                -  CLKPWR_RSTCON0_UART0     : UART 0
                -  CLKPWR_RSTCON0_UART1     : UART 1
                -  CLKPWR_RSTCON0_PWM0      : PWM 0
                -  CLKPWR_RSTCON0_PWM1      : PWM 1
                -  CLKPWR_RSTCON0_I2C0      : I2C 0
                -  CLKPWR_RSTCON0_UART4     : UART 4
                -  CLKPWR_RSTCON0_RTC       : RTC
                -  CLKPWR_RSTCON0_SSP1      : SSP 1
                -  CLKPWR_RSTCON0_EMC       : EMC
                -  CLKPWR_RSTCON0_ADC       : ADC
                -  CLKPWR_RSTCON0_CAN1      : CAN 1
                -  CLKPWR_RSTCON0_CAN2      : CAN 2
                -  CLKPWR_RSTCON0_GPIO      : GPIO
                -  CLKPWR_RSTCON0_MCPWM     : MCPWM
                -  CLKPWR_RSTCON0_QEI       : QEI
                -  CLKPWR_RSTCON0_I2C1      : I2C 1
                -  CLKPWR_RSTCON0_SSP2      : SSP 2
                -  CLKPWR_RSTCON0_SSP0      : SSP 0
                -  CLKPWR_RSTCON0_TIM2      : Timer 2
                -  CLKPWR_RSTCON0_TIM3      : Timer 3
                -  CLKPWR_RSTCON0_UART2     : UART 2
                -  CLKPWR_RSTCON0_UART3     : UART 3
                -  CLKPWR_RSTCON0_I2C2      : I2C 2
                -  CLKPWR_RSTCON0_I2S       : I2S
                -  CLKPWR_RSTCON0_SDC       : SDC
                -  CLKPWR_RSTCON0_GPDMA     : GPDMA
                -  CLKPWR_RSTCON0_ENET      : Ethernet
                -  CLKPWR_RSTCON0_USB       : USB
 *
 * @param[in]   NewState    New state of Peripheral Power, should be:
 *              - ENABLE    : Enable power for this peripheral
 *              - DISABLE   : Disable power for this peripheral
 *
 * @return none
 **********************************************************************/
void CLKPWR_ConfigReset(uint8_t PType, FunctionalState NewState)
{
    if(PType < 32)
    {
        if(NewState == ENABLE)
            LPC_SC->RSTCON0 |=(1<<PType);
        else
            LPC_SC->RSTCON0 &=~(1<<PType);
    }
    else
    {
        if(NewState == ENABLE)
            LPC_SC->RSTCON1 |= (1<<(PType - 31));
        else
            LPC_SC->RSTCON1 &= ~(1<<(PType - 31));
    }
}
// nxp21346
#endif

/*********************************************************************//**
 * @brief       Enter Sleep mode with co-operated instruction by the Cortex-M3.
 * @param[in]   None
 * @return      None
 **********************************************************************/
void CLKPWR_Sleep(void)
{
    LPC_SC->PCON = 0x00;
    /* Sleep Mode*/
    __WFI();
}


/*********************************************************************//**
 * @brief       Enter Deep Sleep mode with co-operated instruction by the Cortex-M3.
 * @param[in]   None
 * @return      None
 **********************************************************************/
void CLKPWR_DeepSleep(void)
{
    /* Deep-Sleep Mode, set SLEEPDEEP bit */
    SCB->SCR = 0x4;
    LPC_SC->PCON = 0x00;
    /* Deep Sleep Mode*/
    __WFI();
}


/*********************************************************************//**
 * @brief       Enter Power Down mode with co-operated instruction by the Cortex-M3.
 * @param[in]   None
 * @return      None
 **********************************************************************/
void CLKPWR_PowerDown(void)
{
    /* Deep-Sleep Mode, set SLEEPDEEP bit */
    SCB->SCR = 0x4;
    LPC_SC->PCON = 0x01;
    /* Power Down Mode*/
    __WFI();
}


/*********************************************************************//**
 * @brief       Enter Deep Power Down mode with co-operated instruction by the Cortex-M3.
 * @param[in]   None
 * @return      None
 **********************************************************************/
void CLKPWR_DeepPowerDown(void)
{
    /* Deep-Sleep Mode, set SLEEPDEEP bit */
    SCB->SCR = 0x4;
    LPC_SC->PCON = 0x03;
    /* Deep Power Down Mode*/
    __WFI();
}

/**
 * @}
 */
 
#endif /*_CLKPWR*/

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
