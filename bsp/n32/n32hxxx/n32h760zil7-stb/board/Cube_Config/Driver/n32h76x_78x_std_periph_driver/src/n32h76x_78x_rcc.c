/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_rcc.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "n32h76x_78x_rcc.h"
#include <math.h>

/** RCC Private Defines **/
#define __RCC_DELAY_US(usec)     do{                                       \
        uint32_t delay_end;                   \
        CPU_DELAY_INTI();                     \
        /* Delay*/                            \
        delay_end = DWT_CYCCNT + (usec * (600000000/1000000)); \
        while(DWT_CYCCNT < delay_end){};      \
        CPU_DELAY_DISABLE();                  \
    }while(0)


/** RCC Driving Functions Declaration **/
/**
  *\*\name RCC_Reset
  *\*\fun  Resets the RCC clock configuration to the default reset state.
  *\*\param  None
  *\*\return  None
  */
void RCC_DeInit(void)
{

    /* Set HSIEN bit */
    RCC->SRCCTRL1 |= (uint32_t)0x00000001U;

    /* Reset SCLKSW, MSIEN ,HSEBP, HSEEN bits */
    RCC->SRCCTRL1 &=  (uint32_t)0xFCFFFFABU;

    /* Reset M7HYPSEL,AXIHYPSEL*/
    RCC->SRCCTRL2 &= (uint32_t)0xFFFCFFFFU;

    /* Reset SYSBUSDIV1,  SYSBUSDIV2 */
    RCC->SYSBUSDIV1 = RCC_REG_BIT_MASK;
    RCC->SYSBUSDIV2 = RCC_REG_BIT_MASK;

    /* Reset PLL1CTRL1 */
    RCC->PLL1CTRL1 = (uint32_t)0x19030004U;

    /* Reset PLL2CTRL1 */
    RCC->PLL2CTRL1 &= (uint32_t)0x19030005U;

    /* Reset PLL3CTRL1 */
    RCC->PLL3CTRL1 &= (uint32_t)0x19030005U;

    /* Reset CFG2 register */
    RCC->CFG2 = 0x55ACCCCCU;

    /* Reset CFG3 register */
    RCC->CFG3 = 0x00000044U;

    /* Reset CFG4 register */
    RCC->CFG4 = 0xFFFFFDFEU;

    /* Reset CFG5 register */
    RCC->CFG5 = 0x02C10000U;

    /* Disable all interrupts and clear pending bits  */
    RCC->CLKINT1 = RCC_REG_BIT_MASK;
    RCC->CLKINT2 = RCC_REG_BIT_MASK;
    RCC->CLKINT3 = RCC_REG_BIT_MASK;
}

/**
*\*\name    RCC_ConfigHse.
*\*\fun     Configures the External High Speed oscillator (HSE).
*\*\param   RCC_HSE :
*\*\          - RCC_HSE_DISABLE    HSE oscillator OFF
*\*\          - RCC_HSE_ENABLE     HSE oscillator ON
*\*\          - RCC_HSE_BYPASS     HSE oscillator bypassed with external clock
*\*\return  none:
*\*\note    HSE can not be stopped if it is used directly or through the PLL as system clock
**/
void RCC_ConfigHse(uint32_t RCC_HSE)
{
    if(RCC_HSE == RCC_HSE_DISABLE)
    {
        /* Reset HSEEN bit */
        RCC->SRCCTRL1 &= (~(RCC_HSE_ENABLE | RCC_HSE_BYPASS));
    }
    else
    {
        /* Reset HSERDCNTEN bit */
        RCC->SRCCTRL1 &= (~RCC_HSE_RDCNTEN);

        if (RCC_HSE == RCC_HSE_BYPASS)
        {
            if((RCC->SRCCTRL1 & RCC_HSE_ENABLE) == RCC_HSE_ENABLE)
            {
                /* Reset HSEEN bit */
                RCC->SRCCTRL1 &= (~RCC_HSE_ENABLE);
            }

            /* Set HSEBP bits */
            RCC->SRCCTRL1 |= RCC_HSE_BYPASS;
        }

        /* Set HSEEN bit */
        RCC->SRCCTRL1 |= RCC_HSE_ENABLE;
        __RCC_DELAY_US(50);
        /* Set HSERDCNTEN bit */
        RCC->SRCCTRL1 |= (RCC_HSE_RDCNTEN);

    }
}

/**
*\*\name    RCC_WaitHseStable.
*\*\fun     Waits for HSE start-up.
*\*\param   none
*\*\return  ErrorStatus:
 *\*\         - SUCCESS    HSE oscillator is stable and ready to use
 *\*\         - ERROR      HSE oscillator not yet ready
**/
ErrorStatus RCC_WaitHseStable(void)
{
    __IO uint32_t counter_value = 0;
    uint32_t timeout_value;
    uint32_t status_value;
    RCC_ClocksTypeDef sysclk_value;
    ErrorStatus bitstatus;

    RCC_GetClocksFreqValue(&sysclk_value);
    timeout_value = (HSE_STARTUP_TIMEOUT / ((uint32_t)600000000 / sysclk_value.SysClkFreq));

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        status_value = (RCC->SRCCTRL1 & RCC_HSE_STABLE_FLAG);
        counter_value++;
    }
    while ((counter_value != timeout_value) && (status_value != RCC_HSE_STABLE_FLAG));

    if ((RCC->SRCCTRL1 & RCC_HSE_STABLE_FLAG) == RCC_HSE_STABLE_FLAG)
    {
        bitstatus = SUCCESS;
    }
    else
    {
        bitstatus = ERROR;
    }

    return bitstatus;
}

/**
*\*\name    RCC_EnableHsi.
*\*\fun     Enables the Internal High Speed oscillator (HSI).
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note   HSI can not be stopped if it is used directly or through the PLL as system clock.
**/
void RCC_EnableHsi(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        /* Set HSIEN bit */
        RCC->SRCCTRL1 |= RCC_HSI_ENABLE;
    }
    else
    {
        /* Reset HSIEN bit */
        RCC->SRCCTRL1 &= (~RCC_HSI_ENABLE);
    }
}

/**
*\*\name    RCC_WaitHsiStable.
*\*\fun     Waits for HSI start-up.
*\*\param   none
*\*\return  ErrorStatus:
 *\*\         - SUCCESS    HSI oscillator is stable and ready to use
 *\*\         - ERROR      HSI oscillator not yet ready
**/
ErrorStatus RCC_WaitHsiStable(void)
{
    __IO uint32_t counter_value = 0;
    uint32_t timeout_value;
    uint32_t status_value;
    RCC_ClocksTypeDef sysclk_value;
    ErrorStatus bitstatus;

    RCC_GetClocksFreqValue(&sysclk_value);
    timeout_value = (HSI_STARTUP_TIMEOUT / ((uint32_t)600000000 / sysclk_value.SysClkFreq));

    /* Wait till HSI is ready and if Time out is reached exit */
    do
    {
        status_value = (RCC->SRCCTRL1 & RCC_HSI_STABLE_FLAG);
        counter_value++;
    }
    while ((counter_value != timeout_value) && (status_value != RCC_HSI_STABLE_FLAG));

    if ((RCC->SRCCTRL1 & RCC_HSI_STABLE_FLAG) == RCC_HSI_STABLE_FLAG)
    {
        bitstatus = SUCCESS;
    }
    else
    {
        bitstatus = ERROR;
    }

    return bitstatus;
}

/**
*\*\name    RCC_EnableMsi.
*\*\fun     Enables the Internal High Speed oscillator (MSI).
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note   MSI can not be stopped if it is used directly or through the PLL as system clock.
**/
void RCC_EnableMsi(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        /* Set MSIEN bit */
        RCC->SRCCTRL1 |= RCC_MSI_ENABLE;
    }
    else
    {
        /* Reset MSIEN bit */
        RCC->SRCCTRL1 &= (~RCC_MSI_ENABLE);
    }
}

/**
*\*\name    RCC_WaitMsiStable.
*\*\fun     Waits for MSI start-up.
*\*\param   none
*\*\return  ErrorStatus:
 *\*\         - SUCCESS    MSI oscillator is stable and ready to use
 *\*\         - ERROR      MSI oscillator not yet ready
**/
ErrorStatus RCC_WaitMsiStable(void)
{
    __IO uint32_t counter_value = 0;
    uint32_t timeout_value;
    uint32_t status_value;
    RCC_ClocksTypeDef sysclk_value;
    ErrorStatus bitstatus;

    RCC_GetClocksFreqValue(&sysclk_value);
    timeout_value = (MSI_STARTUP_TIMEOUT / ((uint32_t)600000000 / sysclk_value.SysClkFreq));

    /* Wait till MSI is ready and if Time out is reached exit */
    do
    {
        status_value = (RCC->SRCCTRL1 & RCC_MSI_STABLE_FLAG);
        counter_value++;
    }
    while ((counter_value != timeout_value) && (status_value != RCC_MSI_STABLE_FLAG));

    if ((RCC->SRCCTRL1 & RCC_MSI_STABLE_FLAG) == RCC_MSI_STABLE_FLAG)
    {
        bitstatus = SUCCESS;
    }
    else
    {
        bitstatus = ERROR;
    }

    return bitstatus;
}

/**
*\*\name    RCC_ConfigLse.
*\*\fun     Configures the External High Speed oscillator (LSE).
*\*\param   RCC_LSE :
*\*\          - RCC_LSE_DISABLE    LSE oscillator OFF
*\*\          - RCC_LSE_ENABLE     LSE oscillator ON
*\*\          - RCC_LSE_BYPASS     LSE oscillator bypassed with external clock
*\*\return  none:
*\*\note BDCTRL is protected, you need to enable the PWR clock first,
*\*\     then configure PWR_SYSCTRL1.DBKP to 1 to change it.
**/
void RCC_ConfigLse(uint32_t RCC_LSE)
{

    if(RCC_LSE == RCC_LSE_DISABLE)
    {
        RCC->BDCTRL &= (~(RCC_LSE_ENABLE | RCC_LSERDY_ENABLE));

        while((RCC->BDCTRL & RCC_BDCTRL_LSERDF) == RCC_BDCTRL_LSERDF)
        {}

        __RCC_DELAY_US(10);
        RCC->BDCTRL &= (~(RCC_LSE_BYPASS | RCC_LSE_LSELDO));

    }
    else
    {
        if (RCC_LSE == RCC_LSE_BYPASS)
        {
            if((RCC->BDCTRL & RCC_LSE_ENABLE) == RCC_LSE_ENABLE)
            {
                RCC->BDCTRL &= (~RCC_LSE_ENABLE);
            }

            /* Set LSEBP bits */
            RCC->BDCTRL |= RCC_LSE_BYPASS;
        }
        else
        {
            /* Reset LSEBP bits */
            RCC->BDCTRL &= (~RCC_LSE_BYPASS);
        }

        /* Reset LSERDCNTEN bit */
        RCC->BDCTRL &= (~RCC_LSE_RDCNTEN);
        /* Set LSEEN bit */
        RCC->BDCTRL |= RCC_LSE_LSELDO;
        __RCC_DELAY_US(60);
        if (RCC_LSE == RCC_LSE_ENABLE)
        {
            /* Set da_lse_agcopt bits */
            AFEC->TRIMR7 |= 0x00400000;
        }
        /* Set LSEEN bit */
        RCC->BDCTRL |= (RCC_LSE_ENABLE | RCC_LSERDY_ENABLE);
        __RCC_DELAY_US(10);
        /* Set LSERDCNTEN bit */
        RCC->BDCTRL |= (RCC_LSE_RDCNTEN);
    }

}

/**
*\*\name    RCC_WaitLseStable.
*\*\fun     Waits for LSE start-up.
*\*\param   none
*\*\return  ErrorStatus:
 *\*\         - SUCCESS    LSE oscillator is stable and ready to use
 *\*\         - ERROR      LSE oscillator not yet ready
**/
ErrorStatus RCC_WaitLseStable(void)
{
    __IO uint32_t counter_value = 0;
    uint32_t timeout_value;
    uint32_t status_value;
    RCC_ClocksTypeDef sysclk_value;
    ErrorStatus bitstatus;

    RCC_GetClocksFreqValue(&sysclk_value);
    timeout_value = (LSE_STARTUP_TIMEOUT / ((uint32_t)600000000 / sysclk_value.SysClkFreq));

    /* Wait till LSE is ready and if Time out is reached exit */
    do
    {
        status_value = (RCC->BDCTRL & RCC_LSE_STABLE_FLAG);
        counter_value++;
    }
    while ((counter_value != timeout_value) && (status_value != RCC_LSE_STABLE_FLAG));

    if ((RCC->BDCTRL & RCC_LSE_STABLE_FLAG) == RCC_LSE_STABLE_FLAG)
    {
        bitstatus = SUCCESS;
    }
    else
    {
        bitstatus = ERROR;
    }

    return bitstatus;
}

/**
*\*\name    RCC_EnableLsi.
*\*\fun     Enables the Internal Low Speed oscillator (LSI).
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note BDCTRL is protected, you need to enable the PWR clock first,
*\*\     then configure PWR_SYSCTRL1.DBKP to 1 to change it.
**/
void RCC_EnableLsi(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        /* Set LSIEN bit */
        RCC->BDCTRL |= (RCC_LSI_ENABLE | RCC_LSIRDY_ENABLE);
    }
    else
    {
        /* Reset PLLEN bit */
        RCC->BDCTRL &= (~(RCC_LSI_ENABLE | RCC_LSIRDY_ENABLE));
    }

}

/**
*\*\name    RCC_WaitLsiStable.
*\*\fun     Waits for LSI start-up.
*\*\param   none
*\*\return  ErrorStatus:
 *\*\         - SUCCESS    LSI oscillator is stable and ready to use
 *\*\         - ERROR      LSI oscillator not yet ready
**/
ErrorStatus RCC_WaitLsiStable(void)
{
    __IO uint32_t counter_value = 0;
    uint32_t timeout_value;
    uint32_t status_value;
    RCC_ClocksTypeDef sysclk_value;
    ErrorStatus bitstatus;

    RCC_GetClocksFreqValue(&sysclk_value);
    timeout_value = (LSI_STARTUP_TIMEOUT / ((uint32_t)600000000 / sysclk_value.SysClkFreq));

    /* Wait till LSI is ready and if Time out is reached exit */
    do
    {
        status_value = (RCC->BDCTRL & RCC_LSI_STABLE_FLAG);
        counter_value++;
    }
    while ((counter_value != timeout_value) && (status_value != RCC_LSI_STABLE_FLAG));

    if ((RCC->BDCTRL & RCC_LSI_STABLE_FLAG) == RCC_LSI_STABLE_FLAG)
    {
        bitstatus = SUCCESS;
    }
    else
    {
        bitstatus = ERROR;
    }

    return bitstatus;
}

/**
*\*\name    RCC_EnableSecondaryLsi.
*\*\fun     Enables the Secondary Internal Low Speed oscillator (LSI).
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note BDCTRL is protected, you need to enable the PWR clock first,
*\*\     then configure PWR_SYSCTRL1.DBKP to 1 to change it.
**/
void RCC_EnableSecondaryLsi(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        /* Set LSIEN bit */
        RCC->BDCTRL |= RCC_SECLSI_ENABLE;
    }
    else
    {
        /* Reset PLLEN bit */
        RCC->BDCTRL &= (~RCC_SECLSI_ENABLE);
    }

}

/**
*\*\name    RCC_WaitSecondaryLsiStable.
*\*\fun     Waits for SECLSI start-up.
*\*\param   none
*\*\return  ErrorStatus:
 *\*\         - SUCCESS    SECLSI oscillator is stable and ready to use
 *\*\         - ERROR      SECLSI oscillator not yet ready
**/
ErrorStatus RCC_WaitSecondaryLsiStable(void)
{
    __IO uint32_t counter_value = 0;
    uint32_t timeout_value;
    uint32_t status_value;
    RCC_ClocksTypeDef sysclk_value;
    ErrorStatus bitstatus;

    RCC_GetClocksFreqValue(&sysclk_value);
    timeout_value = (SECLSI_STARTUP_TIMEOUT / ((uint32_t)600000000 / sysclk_value.SysClkFreq));

    /* Wait till SECLSI is ready and if Time out is reached exit */
    do
    {
        status_value = (RCC->BDCTRL & RCC_SECLSI_STABLE_FLAG);
        counter_value++;
    }
    while ((counter_value != timeout_value) && (status_value != RCC_SECLSI_STABLE_FLAG));

    if ((RCC->BDCTRL & RCC_SECLSI_STABLE_FLAG) == RCC_SECLSI_STABLE_FLAG)
    {
        bitstatus = SUCCESS;
    }
    else
    {
        bitstatus = ERROR;
    }

    return bitstatus;
}

/**
*\*\name    RCC_ConfigSysclk.
*\*\fun     Configures the system clock (SYSCLK).
*\*\param   sysclk_source(clock source used as system clock):
*\*\         - RCC_SYSCLK_SRC_HSI           HSI selected as system clock
*\*\         - RCC_SYSCLK_SRC_MSI           HSI selected as system clock
*\*\         - RCC_SYSCLK_SRC_HSE           HSE selected as system clock
*\*\         - RCC_SYSCLK_SRC_PLL1A         PLL1A selected as system clock
*\*\return  none
**/
void RCC_ConfigSysclk(uint32_t sysclk_source)
{
    uint32_t reg_value;

    reg_value = RCC->SRCCTRL1;
    /* Clear SCLKSW bits */
    reg_value &=  RCC_SYSCLK_SRC_MASK;
    /* Set SCLKSW bits */
    reg_value |=  sysclk_source;
    /* Store the new value */
    RCC->SRCCTRL1 = reg_value;

}

/**
*\*\name    RCC_GetSysclkSrc.
*\*\fun     Returns the clock source used as system clock.
*\*\param   none
*\*\return  (The clock source used as system clock):
*\*\         - RCC_SYSCLK_STS_HSI    HSI used as system clock
*\*\         - RCC_SYSCLK_STS_MSI    HSI used as system clock
*\*\         - RCC_SYSCLK_STS_HSE    HSE used as system clock
*\*\         - RCC_SYSCLK_STS_PLL1A  PLL1A used as system clock
**/
uint32_t RCC_GetSysclkSrc(void)
{
    return ((uint32_t)(RCC->SRCCTRL1 & RCC_SYSCLK_STS_MASK));
}


/**
*\*\name   RCC_ConfigHSIclkDivider .
*\*\fun    Obtained by dividing the HSI 64M clk.
*\*\param  CLK_divider
*\*\     - RCC_HSICLK_DIV1
*\*\     - RCC_HSICLK_DIV2
*\*\     - RCC_HSICLK_DIV4
*\*\     - RCC_HSICLK_DIV8
*\*\     - RCC_HSICLK_DIV16
*\*\     - RCC_HSICLK_DIV32
*\*\     - RCC_HSICLK_DIV64
*\*\     - RCC_HSICLK_DIV128
*\*\     - RCC_HSICLK_DIV256
*\*\     - RCC_HSICLK_DIV512
*\*\return none.
*\*\note All HSI are divided clocks except PLL clock sources
**/
void RCC_ConfigHSIclkDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->SYSBUSDIV1;
    /* Clear HSIDIV bits */
    reg_value &=  RCC_HSICLK_DIV_MASK;
    /* Set the HSIDIV bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->SYSBUSDIV1 = reg_value;
}

/**
*\*\name   RCC_ConfigMSIclkDivider .
*\*\fun    Obtained by dividing the MSI 64M clk.
*\*\param  CLK_divider
*\*\     - RCC_MSICLK_DIV1
*\*\     - RCC_MSICLK_DIV2
*\*\     - RCC_MSICLK_DIV4
*\*\     - RCC_MSICLK_DIV8
*\*\     - RCC_MSICLK_DIV16
*\*\     - RCC_MSICLK_DIV32
*\*\     - RCC_MSICLK_DIV64
*\*\     - RCC_MSICLK_DIV128
*\*\     - RCC_MSICLK_DIV256
*\*\     - RCC_MSICLK_DIV512
*\*\return none.
*\*\note All MSI are divided clocks except PLL clock sources
**/
void RCC_ConfigMSIclkDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->SYSBUSDIV1;
    /* Clear MSIDIV bits */
    reg_value &=  RCC_MSICLK_DIV_MASK;
    /* Set the MSIDIV bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->SYSBUSDIV1 = reg_value;
}

/**
*\*\name    RCC_ConfigM7Clk.
*\*\fun     Config the M7 clock source selection.
*\*\param   CLK_source:
*\*\       - RCC_M7HYPERCLK_SRC_PLL1A
*\*\       - RCC_M7HYPERCLK_SRC_PLL2A
*\*\return  none
*\*\note   none
**/
void RCC_ConfigM7Clk(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->SRCCTRL2;
    /* Clear M7HYPSEL bits */
    reg_value &=  RCC_M7HYPERCLK_SRC_MASK;
    /* Set the M7HYPSEL bits */
    reg_value |=  CLK_source;
    /* Store the new value */
    RCC->SRCCTRL2 = reg_value;

}

/**
*\*\name    RCC_ConfigAXIClk.
*\*\fun     Config the AXI clock source selection.
*\*\param   CLK_source:
*\*\       - RCC_AXIHYPERCLK_SRC_PLL1A
*\*\       - RCC_AXIHYPERCLK_SRC_PLL2A
*\*\return  none
*\*\note   none
**/
void RCC_ConfigAXIClk(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->SRCCTRL2;
    /* Clear AXIHYPSEL bits */
    reg_value &=  RCC_AXIHYPERCLK_SRC_MASK;
    /* Set the AXIHYPSEL bits */
    reg_value |=  CLK_source;
    /* Store the new value */
    RCC->SRCCTRL2 = reg_value;

}

/**
*\*\name    RCC_CalculatePLLParam.
*\*\fun     Configures the SHRTPLL clock source and multiplication factor.
*\*\param   fin(SHRTPLL input frequency):
*\*\         1000000 ~ 64000000 (Hz)
*\*\param   fout(SHRTPLL output frequency):
*\*\         75000000 ~ 1250000000 (Hz)
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  ErrorStatus:
*\*\         - SUCCESS
*\*\         - ERROR
*\*\note    fout = fin*(CLKF[25:0]/16384)/(CLKR[5:0] +1)
**/
ErrorStatus RCC_CalculatePLLParam(uint64_t fin, uint64_t fout, uint32_t* nr, uint32_t* nf, uint32_t* wb)
{
    ErrorStatus status;
    uint64_t err_t;
    uint32_t nr_t;
    uint32_t nf_all;
    uint32_t nf_int;
    uint64_t err = (uint64_t)0xFFFFFFFFU;

    /* get NR NF WB parameter */
    if ((fin > REF_MAX) || (fin < REF_MIN) || (fout > VCO_MAX) || (fout < VCO_MIN))
    {
        status = ERROR;
    }
    else
    {
        for ( nr_t = NR_MAX; nr_t >= NR_MIN; nr_t--)
        {
            nf_all = (uint32_t)floor(fout * nr_t * 256 / fin);
            nf_int = nf_all / 256;

            if ((nf_int > NF_MAX) || (nf_int < NF_MIN))
            {
                continue;
            }

            if((fin * nf_all / nr_t / 256) > fout)
            {
                err_t = ((fin * nf_all / nr_t / 256) - fout);
            }
            else
            {
                err_t = (fout - (fin * nf_all / nr_t / 256));
            }

            if (err_t <= err)
            {
                err = err_t;
                *nr = nr_t;
                *nf = nf_all;
            }
            else
            {
                /* In other cases, the cycle continues*/
            }
        }

        *wb = (uint32_t)floor((*nf / 2 / 256) - 1);

        if(*wb > 2047)
        {
            *wb = 2047;
        }

        *nr = *nr - 1;
        *nf = *nf * 64;
        status = SUCCESS;
    }

    return status;
}

/**
*\*\name    RCC_ConfigSHRPll.
*\*\fun     Configures the SHRPLL clock source and multiplication factor.
*\*\param   PLL_source(SHRPLL entry clock source):
*\*\             - RCC_PLL_SRC_HSI         HSI oscillator clock selected as SHRPLL clock entry
*\*\             - RCC_PLL_SRC_MSI         MSI oscillator clock selected as SHRPLL clock entry
*\*\             - RCC_PLL_SRC_HSE         HSE oscillator clock selected as SHRPLL clock entry
*\*\param   fin(SHRPLL input frequency):
*\*\         4000000 ~ 50000000 (Hz)
*\*\param   fout(SHRPLL output frequency):
*\*\         100000000 ~ 312500000 (Hz)
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  ErrorStatus:
 *\*\         - SUCCESS
 *\*\         - ERROR
*\*\note    fout = fin*(CLKF[25:0]/16384)/(CLKR[5:0] +1)/4
**/
ErrorStatus RCC_ConfigSHRPll(uint32_t PLL_source, uint64_t fin, uint64_t fout, FunctionalState Cmd)
{
    uint32_t temp_value1, temp_value2;
    ErrorStatus status;
    uint32_t nrtmp = 0;
    uint32_t nftmp = 0;
    uint32_t wbtmp = 0;

    if(Cmd == DISABLE)
    {
        /* Disable PLL */
        RCC->SHRPLLCTRL1 &= (~RCC_PLL_ENABLE);
        /* Enable PLL reset */
        RCC->SHRPLLCTRL1 |= RCC_PLL_RESET_ENABLE;

        while((RCC->SHRPLLCTRL1 & RCC_PLL_LOCK_FLAG) != RCC_REG_BIT_MASK)
        {}

        /* Disable power to analog circuitry in PLL */
        RCC->SHRPLLCTRL1 |= RCC_PLL_POWER_DOWN;
        /* Disable PLL module power */
        RCC->SHRPLLCTRL1  &= (~RCC_PLL_LDO_ENABLE);
        status = SUCCESS;
    }
    else
    {
        /* get NR NF WB parameter */
        fout = fout * 4;

        if(RCC_CalculatePLLParam(fin, fout, &nrtmp, &nftmp, &wbtmp) == SUCCESS)
        {
            /* get the register value */
            temp_value1 = RCC->SHRPLLCTRL1;
            temp_value2 = RCC->SHRPLLCTRL2;

            /* Clear BWAJ[11:0] bits */
            temp_value1 &= RCC_PLL_BWAJ_MASK;
            /* Clear CLKF[25:0] and CLKR[5:0] bits */
            temp_value2 &= RCC_PLL_CLKR_CLKF_MASK;

            /* Set BWAJ[11:0] bits */
            temp_value1 |= (uint32_t)(wbtmp & 0xFFF);
            /* Set CLKF[25:0] and CLKR[5:0]  bits */
            temp_value2 |= (uint32_t)((nrtmp << 26) | (nftmp & 0x3FFFFFF));

            /* Store the new value */
            RCC->SHRPLLCTRL1  = temp_value1;
            RCC->SHRPLLCTRL2  = temp_value2;

            /* Enable PLL module power */
            RCC->SHRPLLCTRL1 |= RCC_PLL_LDO_ENABLE;
            __RCC_DELAY_US(10);

            /* Enable power to analog circuitry in PLL */
            RCC->SHRPLLCTRL1 &= (~RCC_PLL_POWER_DOWN);

            /* Select Clock Source */
            temp_value1 = RCC->SHRPLLCTRL1;
            temp_value1 &= RCC_PLL_SRC_MASK;
            temp_value1 |= PLL_source;
            RCC->SHRPLLCTRL1 = temp_value1;
            __RCC_DELAY_US(10);

            /* Clear PLL reset */
            RCC->SHRPLLCTRL1 &= (~RCC_PLL_RESET_ENABLE);

            while((RCC->SHRPLLCTRL1 & RCC_PLL_LOCK_FLAG) != RCC_PLL_LOCK_FLAG)
            {}

            /* Enable PLL */
            RCC->SHRPLLCTRL1 |= RCC_PLL_ENABLE;
            status = SUCCESS;
        }
        else
        {
            status = ERROR;
        }

    }

    return status;
}

/**
*\*\name    RCC_ConfigPll1.
*\*\fun     Configures the PLL1 clock source and multiplication factor.
*\*\param   PLL_source(PLL1 entry clock source):
*\*\             - RCC_PLL_SRC_HSI         HSI oscillator clock selected as PLL1 clock entry
*\*\             - RCC_PLL_SRC_MSI         MSI oscillator clock selected as PLL1 clock entry
*\*\             - RCC_PLL_SRC_HSE         HSE oscillator clock selected as PLL1 clock entry
*\*\param   fin(PLL1 input frequency):
*\*\         1000000 ~ 64000000 (Hz)
*\*\param   fout(PLL1 output frequency):
*\*\         400000000 ~ 8000000000 (Hz)
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  ErrorStatus:
 *\*\         - SUCCESS
 *\*\         - ERROR
*\*\note    fout = fin*(CLKF[25:0]/16384)/(CLKR[5:0] +1)
**/
ErrorStatus RCC_ConfigPll1(uint32_t PLL_source, uint64_t fin, uint64_t fout, FunctionalState Cmd)
{
    uint32_t temp_value1, temp_value2;
    ErrorStatus status;
    uint32_t nrtmp = 0;
    uint32_t nftmp = 0;
    uint32_t wbtmp = 0;

    if(Cmd == DISABLE)
    {
        /* Disable PLL */
        RCC->PLL1CTRL1 &= (~RCC_PLL_ENABLE);
        /* Enable PLL reset */
        RCC->PLL1CTRL1 |= RCC_PLL_RESET_ENABLE;

        while((RCC->PLL1CTRL1 & RCC_PLL_LOCK_FLAG) != RCC_REG_BIT_MASK)
        {}

        /* Disable power to analog circuitry in PLL */
        RCC->PLL1CTRL1 |= RCC_PLL_POWER_DOWN;
        /* Disable PLL module power */
        RCC->PLL1CTRL1  &= (~RCC_PLL_LDO_ENABLE);
        status = SUCCESS;
    }
    else
    {
        /* get NR NF WB parameter */
        if(RCC_CalculatePLLParam(fin, fout, &nrtmp, &nftmp, &wbtmp) == SUCCESS)
        {
            /* get the register value */
            temp_value1 = RCC->PLL1CTRL1;
            temp_value2 = RCC->PLL1CTRL2;

            /* Clear BWAJ[11:0] bits */
            temp_value1 &= RCC_PLL_BWAJ_MASK;
            /* Clear CLKF[25:0] and CLKR[5:0] bits */
            temp_value2 &= RCC_PLL_CLKR_CLKF_MASK;

            /* Set BWAJ[11:0] bits */
            temp_value1 |= (uint32_t)(wbtmp & 0xFFF);
            /* Set CLKF[25:0] and CLKR[5:0]  bits */
            temp_value2 |= (uint32_t)((nrtmp << 26) | (nftmp & 0x3FFFFFF));

            /* Store the new value */
            RCC->PLL1CTRL1  = temp_value1;
            RCC->PLL1CTRL2  = temp_value2;

            /* Enable PLL module power */
            RCC->PLL1CTRL1 |= RCC_PLL_LDO_ENABLE;
            __RCC_DELAY_US(10);

            /* Enable power to analog circuitry in PLL */
            RCC->PLL1CTRL1 &= (~RCC_PLL_POWER_DOWN);

            /* Select Clock Source */
            temp_value1 = RCC->PLL1CTRL1;
            temp_value1 &= RCC_PLL_SRC_MASK;
            temp_value1 |= PLL_source;
            RCC->PLL1CTRL1 = temp_value1;
            __RCC_DELAY_US(10);

            /* Clear PLL reset */
            RCC->PLL1CTRL1 &= (~RCC_PLL_RESET_ENABLE);

            while((RCC->PLL1CTRL1 & RCC_PLL_LOCK_FLAG) != RCC_PLL_LOCK_FLAG)
            {}

            /* Enable PLL */
            RCC->PLL1CTRL1 |= RCC_PLL_ENABLE;
            status = SUCCESS;
        }
        else
        {
            status = ERROR;
        }

    }

    return status;
}

/**
*\*\name    RCC_ConfigPll2.
*\*\fun     Configures the PLL2 clock source and multiplication factor.
*\*\param   PLL_source(PLL2 entry clock source):
*\*\             - RCC_PLL_SRC_HSI         HSI oscillator clock selected as PLL2 clock entry
*\*\             - RCC_PLL_SRC_MSI         MSI oscillator clock selected as PLL2 clock entry
*\*\             - RCC_PLL_SRC_HSE         HSE oscillator clock selected as PLL2 clock entry
*\*\param   fin(PLL2 input frequency):
*\*\         1000000 ~ 64000000 (Hz)
*\*\param   fout(PLL2 output frequency):
*\*\         400000000 ~ 800000000 (Hz)
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  ErrorStatus:
 *\*\         - SUCCESS
 *\*\         - ERROR
*\*\note    fout = fin*(CLKF[25:0]/16384)/(CLKR[5:0] +1)
**/
ErrorStatus RCC_ConfigPll2(uint32_t PLL_source, uint64_t fin, uint64_t fout, FunctionalState Cmd)
{
    uint32_t temp_value1, temp_value2;
    ErrorStatus status;
    uint32_t nrtmp = 0;
    uint32_t nftmp = 0;
    uint32_t wbtmp = 0;

    if(Cmd == DISABLE)
    {
        /* Disable PLL */
        RCC->PLL2CTRL1 &= (~RCC_PLL_ENABLE);
        /* Enable PLL reset */
        RCC->PLL2CTRL1 |= RCC_PLL_RESET_ENABLE;

        while((RCC->PLL2CTRL1 & RCC_PLL_LOCK_FLAG) != RCC_REG_BIT_MASK)
        {}

        /* Disable power to analog circuitry in PLL */
        RCC->PLL2CTRL1 |= RCC_PLL_POWER_DOWN;
        /* Disable PLL module power */
        //RCC->PLL2CTRL1  &= (~RCC_PLL_LDO_ENABLE);
        RCC->PLL3CTRL1  &= (~RCC_PLL_LDO_ENABLE);
        status = SUCCESS;
    }
    else
    {
        /* get NR NF WB parameter */
        if(RCC_CalculatePLLParam(fin, fout, &nrtmp, &nftmp, &wbtmp) == SUCCESS)
        {
            /* get the register value */
            temp_value1 = RCC->PLL2CTRL1;
            temp_value2 = RCC->PLL2CTRL2;

            /* Clear BWAJ[11:0] bits */
            temp_value1 &= RCC_PLL_BWAJ_MASK;
            /* Clear CLKF[25:0] and CLKR[5:0] bits */
            temp_value2 &= RCC_PLL_CLKR_CLKF_MASK;

            /* Set BWAJ[11:0] bits */
            temp_value1 |= (uint32_t)(wbtmp & 0xFFF);
            /* Set CLKF[25:0] and CLKR[5:0]  bits */
            temp_value2 |= (uint32_t)((nrtmp << 26) | (nftmp & 0x3FFFFFF));

            /* Store the new value */
            RCC->PLL2CTRL1  = temp_value1;
            RCC->PLL2CTRL2  = temp_value2;

            /* Enable PLL module power */
            //RCC->PLL2CTRL1 |= RCC_PLL_LDO_ENABLE;
            RCC->PLL3CTRL1 |= RCC_PLL_LDO_ENABLE;
            __RCC_DELAY_US(10);

            /* Enable power to analog circuitry in PLL */
            RCC->PLL2CTRL1 &= (~RCC_PLL_POWER_DOWN);

            /* Select Clock Source */
            temp_value1 = RCC->PLL2CTRL1;
            temp_value1 &= RCC_PLL_SRC_MASK;
            temp_value1 |= PLL_source;
            RCC->PLL2CTRL1 = temp_value1;
            __RCC_DELAY_US(10);

            /* Clear PLL reset */
            RCC->PLL2CTRL1 &= (~RCC_PLL_RESET_ENABLE);

            while((RCC->PLL2CTRL1 & RCC_PLL_LOCK_FLAG) != RCC_PLL_LOCK_FLAG)
            {}

            /* Enable PLL */
            RCC->PLL2CTRL1 |= RCC_PLL_ENABLE;
            status = SUCCESS;
        }
        else
        {
            status = ERROR;
        }

    }

    return status;
}

/**
*\*\name    RCC_ConfigPll3.
*\*\fun     Configures the PLL3 clock source and multiplication factor.
*\*\param   PLL_source(PLL3 entry clock source):
*\*\             - RCC_PLL_SRC_HSI         HSI oscillator clock selected as PLL3 clock entry
*\*\             - RCC_PLL_SRC_MSI         MSI oscillator clock selected as PLL3 clock entry
*\*\             - RCC_PLL_SRC_HSE         HSE oscillator clock selected as PLL3 clock entry
*\*\param   fin(PLL3 input frequency):
*\*\         1000000 ~ 64000000 (Hz)
*\*\param   fout(PLL3 output frequency):
*\*\         400000000 ~ 800000000 (Hz)
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  ErrorStatus:
 *\*\         - SUCCESS
 *\*\         - ERROR
*\*\note    fout = fin*(CLKF[25:0]/16384)/(CLKR[5:0] +1)
**/
ErrorStatus RCC_ConfigPll3(uint32_t PLL_source, uint64_t fin, uint64_t fout, FunctionalState Cmd)
{
    uint32_t temp_value1, temp_value2;
    ErrorStatus status;
    uint32_t nrtmp = 0;
    uint32_t nftmp = 0;
    uint32_t wbtmp = 0;

    if(Cmd == DISABLE)
    {
        /* Disable PLL */
        RCC->PLL3CTRL1 &= (~RCC_PLL_ENABLE);
        /* Enable PLL reset */
        RCC->PLL3CTRL1 |= RCC_PLL_RESET_ENABLE;

        while((RCC->PLL3CTRL1 & RCC_PLL_LOCK_FLAG) != RCC_REG_BIT_MASK)
        {}

        /* Disable power to analog circuitry in PLL */
        RCC->PLL3CTRL1 |= RCC_PLL_POWER_DOWN;
        /* Disable PLL module power */
        //RCC->PLL3CTRL1  &= (~RCC_PLL_LDO_ENABLE);
        RCC->PLL2CTRL1  &= (~RCC_PLL_LDO_ENABLE);
        status = SUCCESS;
    }
    else
    {
        /* get NR NF WB parameter */
        if(RCC_CalculatePLLParam(fin, fout, &nrtmp, &nftmp, &wbtmp) == SUCCESS)
        {
            /* get the register value */
            temp_value1 = RCC->PLL3CTRL1;
            temp_value2 = RCC->PLL3CTRL2;

            /* Clear BWAJ[11:0] bits */
            temp_value1 &= RCC_PLL_BWAJ_MASK;
            /* Clear CLKF[25:0] and CLKR[5:0] bits */
            temp_value2 &= RCC_PLL_CLKR_CLKF_MASK;

            /* Set BWAJ[11:0] bits */
            temp_value1 |= (uint32_t)(wbtmp & 0xFFF);
            /* Set CLKF[25:0] and CLKR[5:0]  bits */
            temp_value2 |= (uint32_t)((nrtmp << 26) | (nftmp & 0x3FFFFFF));

            /* Store the new value */
            RCC->PLL3CTRL1  = temp_value1;
            RCC->PLL3CTRL2  = temp_value2;

            /* Enable PLL module power */
            //RCC->PLL3CTRL1 |= RCC_PLL_LDO_ENABLE;
            RCC->PLL2CTRL1 |= RCC_PLL_LDO_ENABLE;
            __RCC_DELAY_US(10);

            /* Enable power to analog circuitry in PLL */
            RCC->PLL3CTRL1 &= (~RCC_PLL_POWER_DOWN);

            /* Select Clock Source */
            temp_value1 = RCC->PLL3CTRL1;
            temp_value1 &= RCC_PLL_SRC_MASK;
            temp_value1 |= PLL_source;
            RCC->PLL3CTRL1 = temp_value1;
            __RCC_DELAY_US(10);

            /* Clear PLL reset */
            RCC->PLL3CTRL1 &= (~RCC_PLL_RESET_ENABLE);

            while((RCC->PLL3CTRL1 & RCC_PLL_LOCK_FLAG) != RCC_PLL_LOCK_FLAG)
            {}

            /* Enable PLL */
            RCC->PLL3CTRL1 |= RCC_PLL_ENABLE;
            status = SUCCESS;
        }
        else
        {
            status = ERROR;
        }

    }

    return status;
}

/**
*\*\name    RCC_ConfigSHRPll.
*\*\fun     Configures the SHRPLL clock source and multiplication factor.
*\*\param   PLL_source(SHRPLL entry clock source):
*\*\             - RCC_PLL_SRC_HSI         HSI oscillator clock selected as SHRPLL clock entry
*\*\             - RCC_PLL_SRC_MSI         MSI oscillator clock selected as SHRPLL clock entry
*\*\             - RCC_PLL_SRC_HSE         HSE oscillator clock selected as SHRPLL clock entry
*\*\param   nrtmp(SHRPLLCLKR parameter)
*\*\param   nftmp(SHRPLLCLKF parameter)
*\*\param   wbtmp(SHRPLLBWAJ parameter)
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  ErrorStatus:
 *\*\         - SUCCESS
 *\*\         - ERROR
*\*\note    Directly enter the nrtmp, nrtmp and wbtmp configuration parameters without spending a long time calculating the results
**/
ErrorStatus RCC_ConfigSHRPll_NoCalculate(uint32_t PLL_source, uint32_t nrtmp, uint32_t nftmp, uint32_t wbtmp, FunctionalState Cmd)
{
    uint32_t temp_value1, temp_value2;
    ErrorStatus status;

    if(Cmd == DISABLE)
    {
        /* Disable PLL */
        RCC->SHRPLLCTRL1 &= (~RCC_PLL_ENABLE);
        /* Enable PLL reset */
        RCC->SHRPLLCTRL1 |= RCC_PLL_RESET_ENABLE;

        while((RCC->SHRPLLCTRL1 & RCC_PLL_LOCK_FLAG) != RCC_REG_BIT_MASK)
        {}

        /* Disable power to analog circuitry in PLL */
        RCC->SHRPLLCTRL1 |= RCC_PLL_POWER_DOWN;
        /* Disable PLL module power */
        RCC->SHRPLLCTRL1  &= (~RCC_PLL_LDO_ENABLE);
        status = SUCCESS;
    }
    else
    {
        /* get NR NF WB parameter */
        /* get the register value */
        temp_value1 = RCC->SHRPLLCTRL1;
        temp_value2 = RCC->SHRPLLCTRL2;

        /* Clear BWAJ[11:0] bits */
        temp_value1 &= RCC_PLL_BWAJ_MASK;
        /* Clear CLKF[25:0] and CLKR[5:0] bits */
        temp_value2 &= RCC_PLL_CLKR_CLKF_MASK;

        /* Set BWAJ[11:0] bits */
        temp_value1 |= (uint32_t)(wbtmp & 0xFFF);
        /* Set CLKF[25:0] and CLKR[5:0]  bits */
        temp_value2 |= (uint32_t)((nrtmp << 26) | (nftmp & 0x3FFFFFF));

        /* Store the new value */
        RCC->SHRPLLCTRL1  = temp_value1;
        RCC->SHRPLLCTRL2  = temp_value2;

        /* Enable PLL module power */
        RCC->SHRPLLCTRL1 |= RCC_PLL_LDO_ENABLE;
        __RCC_DELAY_US(10);

        /* Enable power to analog circuitry in PLL */
        RCC->SHRPLLCTRL1 &= (~RCC_PLL_POWER_DOWN);

        /* Select Clock Source */
        temp_value1 = RCC->SHRPLLCTRL1;
        temp_value1 &= RCC_PLL_SRC_MASK;
        temp_value1 |= PLL_source;
        RCC->SHRPLLCTRL1 = temp_value1;
        __RCC_DELAY_US(10);

        /* Clear PLL reset */
        RCC->SHRPLLCTRL1 &= (~RCC_PLL_RESET_ENABLE);

        while((RCC->SHRPLLCTRL1 & RCC_PLL_LOCK_FLAG) != RCC_PLL_LOCK_FLAG)
        {}
            
        /* Enable PLL */
        RCC->SHRPLLCTRL1 |= RCC_PLL_ENABLE;
        status = SUCCESS;       
    }

    return status;
}

/**
*\*\name    RCC_ConfigPll1.
*\*\fun     Configures the PLL1 clock source and multiplication factor.
*\*\param   PLL_source(PLL1 entry clock source):
*\*\             - RCC_PLL_SRC_HSI         HSI oscillator clock selected as PLL1 clock entry
*\*\             - RCC_PLL_SRC_MSI         MSI oscillator clock selected as PLL1 clock entry
*\*\             - RCC_PLL_SRC_HSE         HSE oscillator clock selected as PLL1 clock entry
*\*\param   nrtmp(PLL1CLKR parameter)
*\*\param   nftmp(PLL1CLKF parameter)
*\*\param   wbtmp(PLL1BWAJ parameter)
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  ErrorStatus:
 *\*\         - SUCCESS
 *\*\         - ERROR
*\*\note    Directly enter the nrtmp, nrtmp and wbtmp configuration parameters without spending a long time calculating the results
**/
ErrorStatus RCC_ConfigPll1_NoCalculate(uint32_t PLL_source, uint32_t nrtmp, uint32_t nftmp, uint32_t wbtmp, FunctionalState Cmd)
{
    uint32_t temp_value1, temp_value2;
    ErrorStatus status;

    if(Cmd == DISABLE)
    {
        /* Disable PLL */
        RCC->PLL1CTRL1 &= (~RCC_PLL_ENABLE);
        /* Enable PLL reset */
        RCC->PLL1CTRL1 |= RCC_PLL_RESET_ENABLE;

        while((RCC->PLL1CTRL1 & RCC_PLL_LOCK_FLAG) != RCC_REG_BIT_MASK)
        {}

        /* Disable power to analog circuitry in PLL */
        RCC->PLL1CTRL1 |= RCC_PLL_POWER_DOWN;
        /* Disable PLL module power */
        RCC->PLL1CTRL1  &= (~RCC_PLL_LDO_ENABLE);
        status = SUCCESS;
    }
    else
    {
        /* get the register value */
        temp_value1 = RCC->PLL1CTRL1;
        temp_value2 = RCC->PLL1CTRL2;

        /* Clear BWAJ[11:0] bits */
        temp_value1 &= RCC_PLL_BWAJ_MASK;
        /* Clear CLKF[25:0] and CLKR[5:0] bits */
        temp_value2 &= RCC_PLL_CLKR_CLKF_MASK;

        /* Set BWAJ[11:0] bits */
        temp_value1 |= (uint32_t)(wbtmp & 0xFFF);
        /* Set CLKF[25:0] and CLKR[5:0]  bits */
        temp_value2 |= (uint32_t)((nrtmp << 26) | (nftmp & 0x3FFFFFF));

        /* Store the new value */
        RCC->PLL1CTRL1  = temp_value1;
        RCC->PLL1CTRL2  = temp_value2;

        /* Enable PLL module power */
        RCC->PLL1CTRL1 |= RCC_PLL_LDO_ENABLE;
        __RCC_DELAY_US(10);

        /* Enable power to analog circuitry in PLL */
        RCC->PLL1CTRL1 &= (~RCC_PLL_POWER_DOWN);

        /* Select Clock Source */
        temp_value1 = RCC->PLL1CTRL1;
        temp_value1 &= RCC_PLL_SRC_MASK;
        temp_value1 |= PLL_source;
        RCC->PLL1CTRL1 = temp_value1;
        __RCC_DELAY_US(10);

        /* Clear PLL reset */
        RCC->PLL1CTRL1 &= (~RCC_PLL_RESET_ENABLE);

        while((RCC->PLL1CTRL1 & RCC_PLL_LOCK_FLAG) != RCC_PLL_LOCK_FLAG)
        {}

        /* Enable PLL */
        RCC->PLL1CTRL1 |= RCC_PLL_ENABLE;
        status = SUCCESS;
       

    }

    return status;
}

/**
*\*\name    RCC_ConfigPll2.
*\*\fun     Configures the PLL2 clock source and multiplication factor.
*\*\param   PLL_source(PLL2 entry clock source):
*\*\             - RCC_PLL_SRC_HSI         HSI oscillator clock selected as PLL2 clock entry
*\*\             - RCC_PLL_SRC_MSI         MSI oscillator clock selected as PLL2 clock entry
*\*\             - RCC_PLL_SRC_HSE         HSE oscillator clock selected as PLL2 clock entry
*\*\param   nrtmp(PLL2CLKR parameter)
*\*\param   nftmp(PLL2CLKF parameter)
*\*\param   wbtmp(PLL2BWAJ parameter)
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  ErrorStatus:
 *\*\         - SUCCESS
 *\*\         - ERROR
*\*\note    Directly enter the nrtmp, nrtmp and wbtmp configuration parameters without spending a long time calculating the results
**/
ErrorStatus RCC_ConfigPll2_NoCalculate(uint32_t PLL_source, uint32_t nrtmp, uint32_t nftmp, uint32_t wbtmp, FunctionalState Cmd)
{
    uint32_t temp_value1, temp_value2;
    ErrorStatus status;

    if(Cmd == DISABLE)
    {
        /* Disable PLL */
        RCC->PLL2CTRL1 &= (~RCC_PLL_ENABLE);
        /* Enable PLL reset */
        RCC->PLL2CTRL1 |= RCC_PLL_RESET_ENABLE;

        while((RCC->PLL2CTRL1 & RCC_PLL_LOCK_FLAG) != RCC_REG_BIT_MASK)
        {}

        /* Disable power to analog circuitry in PLL */
        RCC->PLL2CTRL1 |= RCC_PLL_POWER_DOWN;
        /* Disable PLL module power */
        //RCC->PLL2CTRL1  &= (~RCC_PLL_LDO_ENABLE);
        RCC->PLL3CTRL1  &= (~RCC_PLL_LDO_ENABLE);
        status = SUCCESS;
    }
    else
    {
        /* get the register value */
        temp_value1 = RCC->PLL2CTRL1;
        temp_value2 = RCC->PLL2CTRL2;

        /* Clear BWAJ[11:0] bits */
        temp_value1 &= RCC_PLL_BWAJ_MASK;
        /* Clear CLKF[25:0] and CLKR[5:0] bits */
        temp_value2 &= RCC_PLL_CLKR_CLKF_MASK;

        /* Set BWAJ[11:0] bits */
        temp_value1 |= (uint32_t)(wbtmp & 0xFFF);
        /* Set CLKF[25:0] and CLKR[5:0]  bits */
        temp_value2 |= (uint32_t)((nrtmp << 26) | (nftmp & 0x3FFFFFF));

        /* Store the new value */
        RCC->PLL2CTRL1  = temp_value1;
        RCC->PLL2CTRL2  = temp_value2;

        /* Enable PLL module power */
        //RCC->PLL2CTRL1 |= RCC_PLL_LDO_ENABLE;
        RCC->PLL3CTRL1 |= RCC_PLL_LDO_ENABLE;
        __RCC_DELAY_US(10);

        /* Enable power to analog circuitry in PLL */
        RCC->PLL2CTRL1 &= (~RCC_PLL_POWER_DOWN);

        /* Select Clock Source */
        temp_value1 = RCC->PLL2CTRL1;
        temp_value1 &= RCC_PLL_SRC_MASK;
        temp_value1 |= PLL_source;
        RCC->PLL2CTRL1 = temp_value1;
        __RCC_DELAY_US(10);

        /* Clear PLL reset */
        RCC->PLL2CTRL1 &= (~RCC_PLL_RESET_ENABLE);

        while((RCC->PLL2CTRL1 & RCC_PLL_LOCK_FLAG) != RCC_PLL_LOCK_FLAG)
        {}

        /* Enable PLL */
        RCC->PLL2CTRL1 |= RCC_PLL_ENABLE;
        status = SUCCESS;
        
    }

    return status;
}

/**
*\*\name    RCC_ConfigPll3.
*\*\fun     Configures the PLL3 clock source and multiplication factor.
*\*\param   PLL_source(PLL3 entry clock source):
*\*\             - RCC_PLL_SRC_HSI         HSI oscillator clock selected as PLL3 clock entry
*\*\             - RCC_PLL_SRC_MSI         MSI oscillator clock selected as PLL3 clock entry
*\*\             - RCC_PLL_SRC_HSE         HSE oscillator clock selected as PLL3 clock entry
*\*\param   nrtmp(PLL3CLKR parameter)
*\*\param   nftmp(PLL3CLKF parameter)
*\*\param   wbtmp(PLL3BWAJ parameter)
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  ErrorStatus:
 *\*\         - SUCCESS
 *\*\         - ERROR
*\*\note    Directly enter the nrtmp, nrtmp and wbtmp configuration parameters without spending a long time calculating the results
**/
ErrorStatus RCC_ConfigPll3_NoCalculate(uint32_t PLL_source, uint32_t nrtmp, uint32_t nftmp, uint32_t wbtmp, FunctionalState Cmd)
{
    uint32_t temp_value1, temp_value2;
    ErrorStatus status;

    if(Cmd == DISABLE)
    {
        /* Disable PLL */
        RCC->PLL3CTRL1 &= (~RCC_PLL_ENABLE);
        /* Enable PLL reset */
        RCC->PLL3CTRL1 |= RCC_PLL_RESET_ENABLE;

        while((RCC->PLL3CTRL1 & RCC_PLL_LOCK_FLAG) != RCC_REG_BIT_MASK)
        {}

        /* Disable power to analog circuitry in PLL */
        RCC->PLL3CTRL1 |= RCC_PLL_POWER_DOWN;
        /* Disable PLL module power */
        //RCC->PLL3CTRL1  &= (~RCC_PLL_LDO_ENABLE);
        RCC->PLL2CTRL1  &= (~RCC_PLL_LDO_ENABLE);
        status = SUCCESS;
    }
    else
    {
        /* get the register value */
        temp_value1 = RCC->PLL3CTRL1;
        temp_value2 = RCC->PLL3CTRL2;

        /* Clear BWAJ[11:0] bits */
        temp_value1 &= RCC_PLL_BWAJ_MASK;
        /* Clear CLKF[25:0] and CLKR[5:0] bits */
        temp_value2 &= RCC_PLL_CLKR_CLKF_MASK;

        /* Set BWAJ[11:0] bits */
        temp_value1 |= (uint32_t)(wbtmp & 0xFFF);
        /* Set CLKF[25:0] and CLKR[5:0]  bits */
        temp_value2 |= (uint32_t)((nrtmp << 26) | (nftmp & 0x3FFFFFF));

        /* Store the new value */
        RCC->PLL3CTRL1  = temp_value1;
        RCC->PLL3CTRL2  = temp_value2;

        /* Enable PLL module power */
        //RCC->PLL3CTRL1 |= RCC_PLL_LDO_ENABLE;
        RCC->PLL2CTRL1 |= RCC_PLL_LDO_ENABLE;
        __RCC_DELAY_US(10);

        /* Enable power to analog circuitry in PLL */
        RCC->PLL3CTRL1 &= (~RCC_PLL_POWER_DOWN);

        /* Select Clock Source */
        temp_value1 = RCC->PLL3CTRL1;
        temp_value1 &= RCC_PLL_SRC_MASK;
        temp_value1 |= PLL_source;
        RCC->PLL3CTRL1 = temp_value1;
        __RCC_DELAY_US(10);

        /* Clear PLL reset */
        RCC->PLL3CTRL1 &= (~RCC_PLL_RESET_ENABLE);

        while((RCC->PLL3CTRL1 & RCC_PLL_LOCK_FLAG) != RCC_PLL_LOCK_FLAG)
        {}

        /* Enable PLL */
        RCC->PLL3CTRL1 |= RCC_PLL_ENABLE;
        status = SUCCESS;
       
    }

    return status;
}

/**
*\*\name   RCC_ConfigPLL1CDivider .
*\*\fun    Configure PLL1 prescaler value to PLL1C.
*\*\param  CLK_divider
*\*\     - RCC_PLLC_DIV1
*\*\     - RCC_PLLC_DIV2
*\*\     - RCC_PLLC_DIV3
*\*\     - RCC_PLLC_DIV4
*\*\     - RCC_PLLC_DIV5
*\*\     - RCC_PLLC_DIV6
*\*\     - RCC_PLLC_DIV7
*\*\     - RCC_PLLC_DIV8
*\*\     - RCC_PLLC_DIV9
*\*\     - RCC_PLLC_DIV10
*\*\     - RCC_PLLC_DIV11
*\*\     - RCC_PLLC_DIV12
*\*\     - RCC_PLLC_DIV13
*\*\     - RCC_PLLC_DIV14
*\*\     - RCC_PLLC_DIV15
*\*\     - RCC_PLLC_DIV16
*\*\     - RCC_PLLC_DIV17
*\*\     - RCC_PLLC_DIV18
*\*\     - RCC_PLLC_DIV19
*\*\     - RCC_PLLC_DIV20
*\*\     - RCC_PLLC_DIV21
*\*\     - RCC_PLLC_DIV22
*\*\     - RCC_PLLC_DIV23
*\*\     - RCC_PLLC_DIV24
*\*\     - RCC_PLLC_DIV25
*\*\     - RCC_PLLC_DIV26
*\*\     - RCC_PLLC_DIV27
*\*\     - RCC_PLLC_DIV28
*\*\     - RCC_PLLC_DIV29
*\*\     - RCC_PLLC_DIV30
*\*\     - RCC_PLLC_DIV31
*\*\     - RCC_PLLC_DIV32
*\*\     - RCC_PLLC_DIV33
*\*\     - RCC_PLLC_DIV34
*\*\     - RCC_PLLC_DIV35
*\*\     - RCC_PLLC_DIV36
*\*\     - RCC_PLLC_DIV37
*\*\     - RCC_PLLC_DIV38
*\*\     - RCC_PLLC_DIV39
*\*\     - RCC_PLLC_DIV40
*\*\     - RCC_PLLC_DIV41
*\*\     - RCC_PLLC_DIV42
*\*\     - RCC_PLLC_DIV43
*\*\     - RCC_PLLC_DIV44
*\*\     - RCC_PLLC_DIV45
*\*\     - RCC_PLLC_DIV46
*\*\     - RCC_PLLC_DIV47
*\*\     - RCC_PLLC_DIV48
*\*\     - RCC_PLLC_DIV49
*\*\     - RCC_PLLC_DIV50
*\*\     - RCC_PLLC_DIV51
*\*\     - RCC_PLLC_DIV52
*\*\     - RCC_PLLC_DIV53
*\*\     - RCC_PLLC_DIV54
*\*\     - RCC_PLLC_DIV55
*\*\     - RCC_PLLC_DIV56
*\*\     - RCC_PLLC_DIV57
*\*\     - RCC_PLLC_DIV58
*\*\     - RCC_PLLC_DIV59
*\*\     - RCC_PLLC_DIV60
*\*\     - RCC_PLLC_DIV61
*\*\     - RCC_PLLC_DIV62
*\*\     - RCC_PLLC_DIV63
*\*\return none.
**/
void RCC_ConfigPLL1CDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->PLL1DIV;
    /* Clear RCC_PLL1C_DIV bits */
    reg_value &=  RCC_PLLC_DIV_MASK;
    /* Set the DIV bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->PLL1DIV = reg_value;
}

/**
*\*\name   RCC_ConfigPLL1BDivider .
*\*\fun    Configure PLL1 divider value to PLL1B.
*\*\param  CLK_divider
*\*\     - RCC_PLLB_DIV1
*\*\     - RCC_PLLB_DIV2
*\*\     - RCC_PLLB_DIV3
*\*\     - RCC_PLLB_DIV4
*\*\     - RCC_PLLB_DIV5
*\*\     - RCC_PLLB_DIV6
*\*\     - RCC_PLLB_DIV7
*\*\     - RCC_PLLB_DIV8
*\*\     - RCC_PLLB_DIV9
*\*\     - RCC_PLLB_DIV10
*\*\     - RCC_PLLB_DIV11
*\*\     - RCC_PLLB_DIV12
*\*\     - RCC_PLLB_DIV13
*\*\     - RCC_PLLB_DIV14
*\*\     - RCC_PLLB_DIV15
*\*\     - RCC_PLLB_DIV16
*\*\     - RCC_PLLB_DIV17
*\*\     - RCC_PLLB_DIV18
*\*\     - RCC_PLLB_DIV19
*\*\     - RCC_PLLB_DIV20
*\*\     - RCC_PLLB_DIV21
*\*\     - RCC_PLLB_DIV22
*\*\     - RCC_PLLB_DIV23
*\*\     - RCC_PLLB_DIV24
*\*\     - RCC_PLLB_DIV25
*\*\     - RCC_PLLB_DIV26
*\*\     - RCC_PLLB_DIV27
*\*\     - RCC_PLLB_DIV28
*\*\     - RCC_PLLB_DIV29
*\*\     - RCC_PLLB_DIV30
*\*\     - RCC_PLLB_DIV31
*\*\     - RCC_PLLB_DIV32
*\*\     - RCC_PLLB_DIV33
*\*\     - RCC_PLLB_DIV34
*\*\     - RCC_PLLB_DIV35
*\*\     - RCC_PLLB_DIV36
*\*\     - RCC_PLLB_DIV37
*\*\     - RCC_PLLB_DIV38
*\*\     - RCC_PLLB_DIV39
*\*\     - RCC_PLLB_DIV40
*\*\     - RCC_PLLB_DIV41
*\*\     - RCC_PLLB_DIV42
*\*\     - RCC_PLLB_DIV43
*\*\     - RCC_PLLB_DIV44
*\*\     - RCC_PLLB_DIV45
*\*\     - RCC_PLLB_DIV46
*\*\     - RCC_PLLB_DIV47
*\*\     - RCC_PLLB_DIV48
*\*\     - RCC_PLLB_DIV49
*\*\     - RCC_PLLB_DIV50
*\*\     - RCC_PLLB_DIV51
*\*\     - RCC_PLLB_DIV52
*\*\     - RCC_PLLB_DIV53
*\*\     - RCC_PLLB_DIV54
*\*\     - RCC_PLLB_DIV55
*\*\     - RCC_PLLB_DIV56
*\*\     - RCC_PLLB_DIV57
*\*\     - RCC_PLLB_DIV58
*\*\     - RCC_PLLB_DIV59
*\*\     - RCC_PLLB_DIV60
*\*\     - RCC_PLLB_DIV61
*\*\     - RCC_PLLB_DIV62
*\*\     - RCC_PLLB_DIV63
*\*\return none.
**/
void RCC_ConfigPLL1BDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->PLL1DIV;
    /* Clear RCC_PLL1B_DIV bits */
    reg_value &=  RCC_PLLB_DIV_MASK;
    /* Set the DIV bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->PLL1DIV = reg_value;
}

/**
*\*\name   RCC_ConfigPLL1ADivider .
*\*\fun    Configure PLL1 divider value to PLL1A.
*\*\param  CLK_divider
*\*\     - RCC_PLLA_DIV1
*\*\     - RCC_PLLA_DIV2
*\*\     - RCC_PLLA_DIV3
*\*\     - RCC_PLLA_DIV4
*\*\     - RCC_PLLA_DIV5
*\*\     - RCC_PLLA_DIV6
*\*\     - RCC_PLLA_DIV7
*\*\     - RCC_PLLA_DIV8
*\*\     - RCC_PLLA_DIV9
*\*\     - RCC_PLLA_DIV10
*\*\     - RCC_PLLA_DIV11
*\*\     - RCC_PLLA_DIV12
*\*\     - RCC_PLLA_DIV13
*\*\     - RCC_PLLA_DIV14
*\*\     - RCC_PLLA_DIV15
*\*\     - RCC_PLLA_DIV16
*\*\     - RCC_PLLA_DIV17
*\*\     - RCC_PLLA_DIV18
*\*\     - RCC_PLLA_DIV19
*\*\     - RCC_PLLA_DIV20
*\*\     - RCC_PLLA_DIV21
*\*\     - RCC_PLLA_DIV22
*\*\     - RCC_PLLA_DIV23
*\*\     - RCC_PLLA_DIV24
*\*\     - RCC_PLLA_DIV25
*\*\     - RCC_PLLA_DIV26
*\*\     - RCC_PLLA_DIV27
*\*\     - RCC_PLLA_DIV28
*\*\     - RCC_PLLA_DIV29
*\*\     - RCC_PLLA_DIV30
*\*\     - RCC_PLLA_DIV31
*\*\     - RCC_PLLA_DIV32
*\*\     - RCC_PLLA_DIV33
*\*\     - RCC_PLLA_DIV34
*\*\     - RCC_PLLA_DIV35
*\*\     - RCC_PLLA_DIV36
*\*\     - RCC_PLLA_DIV37
*\*\     - RCC_PLLA_DIV38
*\*\     - RCC_PLLA_DIV39
*\*\     - RCC_PLLA_DIV40
*\*\     - RCC_PLLA_DIV41
*\*\     - RCC_PLLA_DIV42
*\*\     - RCC_PLLA_DIV43
*\*\     - RCC_PLLA_DIV44
*\*\     - RCC_PLLA_DIV45
*\*\     - RCC_PLLA_DIV46
*\*\     - RCC_PLLA_DIV47
*\*\     - RCC_PLLA_DIV48
*\*\     - RCC_PLLA_DIV49
*\*\     - RCC_PLLA_DIV50
*\*\     - RCC_PLLA_DIV51
*\*\     - RCC_PLLA_DIV52
*\*\     - RCC_PLLA_DIV53
*\*\     - RCC_PLLA_DIV54
*\*\     - RCC_PLLA_DIV55
*\*\     - RCC_PLLA_DIV56
*\*\     - RCC_PLLA_DIV57
*\*\     - RCC_PLLA_DIV58
*\*\     - RCC_PLLA_DIV59
*\*\     - RCC_PLLA_DIV60
*\*\     - RCC_PLLA_DIV61
*\*\     - RCC_PLLA_DIV62
*\*\     - RCC_PLLA_DIV63
*\*\return none.
**/
void RCC_ConfigPLL1ADivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->PLL1DIV;
    /* Clear RCC_PLL1A_DIV bits */
    reg_value &=  RCC_PLLA_DIV_MASK;
    /* Set the DIV bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->PLL1DIV = reg_value;
}

/**
*\*\name   RCC_ConfigPLL2CDivider .
*\*\fun    Configure PLL2 divider value to PLL2C.
*\*\param  CLK_divider
*\*\     - RCC_PLLC_DIV1
*\*\     - RCC_PLLC_DIV2
*\*\     - RCC_PLLC_DIV3
*\*\     - RCC_PLLC_DIV4
*\*\     - RCC_PLLC_DIV5
*\*\     - RCC_PLLC_DIV6
*\*\     - RCC_PLLC_DIV7
*\*\     - RCC_PLLC_DIV8
*\*\     - RCC_PLLC_DIV9
*\*\     - RCC_PLLC_DIV10
*\*\     - RCC_PLLC_DIV11
*\*\     - RCC_PLLC_DIV12
*\*\     - RCC_PLLC_DIV13
*\*\     - RCC_PLLC_DIV14
*\*\     - RCC_PLLC_DIV15
*\*\     - RCC_PLLC_DIV16
*\*\     - RCC_PLLC_DIV17
*\*\     - RCC_PLLC_DIV18
*\*\     - RCC_PLLC_DIV19
*\*\     - RCC_PLLC_DIV20
*\*\     - RCC_PLLC_DIV21
*\*\     - RCC_PLLC_DIV22
*\*\     - RCC_PLLC_DIV23
*\*\     - RCC_PLLC_DIV24
*\*\     - RCC_PLLC_DIV25
*\*\     - RCC_PLLC_DIV26
*\*\     - RCC_PLLC_DIV27
*\*\     - RCC_PLLC_DIV28
*\*\     - RCC_PLLC_DIV29
*\*\     - RCC_PLLC_DIV30
*\*\     - RCC_PLLC_DIV31
*\*\     - RCC_PLLC_DIV32
*\*\     - RCC_PLLC_DIV33
*\*\     - RCC_PLLC_DIV34
*\*\     - RCC_PLLC_DIV35
*\*\     - RCC_PLLC_DIV36
*\*\     - RCC_PLLC_DIV37
*\*\     - RCC_PLLC_DIV38
*\*\     - RCC_PLLC_DIV39
*\*\     - RCC_PLLC_DIV40
*\*\     - RCC_PLLC_DIV41
*\*\     - RCC_PLLC_DIV42
*\*\     - RCC_PLLC_DIV43
*\*\     - RCC_PLLC_DIV44
*\*\     - RCC_PLLC_DIV45
*\*\     - RCC_PLLC_DIV46
*\*\     - RCC_PLLC_DIV47
*\*\     - RCC_PLLC_DIV48
*\*\     - RCC_PLLC_DIV49
*\*\     - RCC_PLLC_DIV50
*\*\     - RCC_PLLC_DIV51
*\*\     - RCC_PLLC_DIV52
*\*\     - RCC_PLLC_DIV53
*\*\     - RCC_PLLC_DIV54
*\*\     - RCC_PLLC_DIV55
*\*\     - RCC_PLLC_DIV56
*\*\     - RCC_PLLC_DIV57
*\*\     - RCC_PLLC_DIV58
*\*\     - RCC_PLLC_DIV59
*\*\     - RCC_PLLC_DIV60
*\*\     - RCC_PLLC_DIV61
*\*\     - RCC_PLLC_DIV62
*\*\     - RCC_PLLC_DIV63
*\*\return none.
**/
void RCC_ConfigPLL2CDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->PLL2DIV;
    /* Clear RCC_PLL2C_DIV bits */
    reg_value &=  RCC_PLLC_DIV_MASK;
    /* Set the DIV bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->PLL2DIV = reg_value;
}

/**
*\*\name   RCC_ConfigPLL2BDivider .
*\*\fun    Configure PLL2 divider value to PLL2B.
*\*\param  CLK_divider
*\*\     - RCC_PLLB_DIV1
*\*\     - RCC_PLLB_DIV2
*\*\     - RCC_PLLB_DIV3
*\*\     - RCC_PLLB_DIV4
*\*\     - RCC_PLLB_DIV5
*\*\     - RCC_PLLB_DIV6
*\*\     - RCC_PLLB_DIV7
*\*\     - RCC_PLLB_DIV8
*\*\     - RCC_PLLB_DIV9
*\*\     - RCC_PLLB_DIV10
*\*\     - RCC_PLLB_DIV11
*\*\     - RCC_PLLB_DIV12
*\*\     - RCC_PLLB_DIV13
*\*\     - RCC_PLLB_DIV14
*\*\     - RCC_PLLB_DIV15
*\*\     - RCC_PLLB_DIV16
*\*\     - RCC_PLLB_DIV17
*\*\     - RCC_PLLB_DIV18
*\*\     - RCC_PLLB_DIV19
*\*\     - RCC_PLLB_DIV20
*\*\     - RCC_PLLB_DIV21
*\*\     - RCC_PLLB_DIV22
*\*\     - RCC_PLLB_DIV23
*\*\     - RCC_PLLB_DIV24
*\*\     - RCC_PLLB_DIV25
*\*\     - RCC_PLLB_DIV26
*\*\     - RCC_PLLB_DIV27
*\*\     - RCC_PLLB_DIV28
*\*\     - RCC_PLLB_DIV29
*\*\     - RCC_PLLB_DIV30
*\*\     - RCC_PLLB_DIV31
*\*\     - RCC_PLLB_DIV32
*\*\     - RCC_PLLB_DIV33
*\*\     - RCC_PLLB_DIV34
*\*\     - RCC_PLLB_DIV35
*\*\     - RCC_PLLB_DIV36
*\*\     - RCC_PLLB_DIV37
*\*\     - RCC_PLLB_DIV38
*\*\     - RCC_PLLB_DIV39
*\*\     - RCC_PLLB_DIV40
*\*\     - RCC_PLLB_DIV41
*\*\     - RCC_PLLB_DIV42
*\*\     - RCC_PLLB_DIV43
*\*\     - RCC_PLLB_DIV44
*\*\     - RCC_PLLB_DIV45
*\*\     - RCC_PLLB_DIV46
*\*\     - RCC_PLLB_DIV47
*\*\     - RCC_PLLB_DIV48
*\*\     - RCC_PLLB_DIV49
*\*\     - RCC_PLLB_DIV50
*\*\     - RCC_PLLB_DIV51
*\*\     - RCC_PLLB_DIV52
*\*\     - RCC_PLLB_DIV53
*\*\     - RCC_PLLB_DIV54
*\*\     - RCC_PLLB_DIV55
*\*\     - RCC_PLLB_DIV56
*\*\     - RCC_PLLB_DIV57
*\*\     - RCC_PLLB_DIV58
*\*\     - RCC_PLLB_DIV59
*\*\     - RCC_PLLB_DIV60
*\*\     - RCC_PLLB_DIV61
*\*\     - RCC_PLLB_DIV62
*\*\     - RCC_PLLB_DIV63
*\*\return none.
**/
void RCC_ConfigPLL2BDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->PLL2DIV;
    /* Clear RCC_PLL2B_DIV bits */
    reg_value &=  RCC_PLLB_DIV_MASK;
    /* Set the DIV bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->PLL2DIV = reg_value;
}

/**
*\*\name   RCC_ConfigPLL2ADivider .
*\*\fun    Configure PLL2 divider value to PLL2A.
*\*\param  CLK_divider
*\*\     - RCC_PLLA_DIV1
*\*\     - RCC_PLLA_DIV2
*\*\     - RCC_PLLA_DIV3
*\*\     - RCC_PLLA_DIV4
*\*\     - RCC_PLLA_DIV5
*\*\     - RCC_PLLA_DIV6
*\*\     - RCC_PLLA_DIV7
*\*\     - RCC_PLLA_DIV8
*\*\     - RCC_PLLA_DIV9
*\*\     - RCC_PLLA_DIV10
*\*\     - RCC_PLLA_DIV11
*\*\     - RCC_PLLA_DIV12
*\*\     - RCC_PLLA_DIV13
*\*\     - RCC_PLLA_DIV14
*\*\     - RCC_PLLA_DIV15
*\*\     - RCC_PLLA_DIV16
*\*\     - RCC_PLLA_DIV17
*\*\     - RCC_PLLA_DIV18
*\*\     - RCC_PLLA_DIV19
*\*\     - RCC_PLLA_DIV20
*\*\     - RCC_PLLA_DIV21
*\*\     - RCC_PLLA_DIV22
*\*\     - RCC_PLLA_DIV23
*\*\     - RCC_PLLA_DIV24
*\*\     - RCC_PLLA_DIV25
*\*\     - RCC_PLLA_DIV26
*\*\     - RCC_PLLA_DIV27
*\*\     - RCC_PLLA_DIV28
*\*\     - RCC_PLLA_DIV29
*\*\     - RCC_PLLA_DIV30
*\*\     - RCC_PLLA_DIV31
*\*\     - RCC_PLLA_DIV32
*\*\     - RCC_PLLA_DIV33
*\*\     - RCC_PLLA_DIV34
*\*\     - RCC_PLLA_DIV35
*\*\     - RCC_PLLA_DIV36
*\*\     - RCC_PLLA_DIV37
*\*\     - RCC_PLLA_DIV38
*\*\     - RCC_PLLA_DIV39
*\*\     - RCC_PLLA_DIV40
*\*\     - RCC_PLLA_DIV41
*\*\     - RCC_PLLA_DIV42
*\*\     - RCC_PLLA_DIV43
*\*\     - RCC_PLLA_DIV44
*\*\     - RCC_PLLA_DIV45
*\*\     - RCC_PLLA_DIV46
*\*\     - RCC_PLLA_DIV47
*\*\     - RCC_PLLA_DIV48
*\*\     - RCC_PLLA_DIV49
*\*\     - RCC_PLLA_DIV50
*\*\     - RCC_PLLA_DIV51
*\*\     - RCC_PLLA_DIV52
*\*\     - RCC_PLLA_DIV53
*\*\     - RCC_PLLA_DIV54
*\*\     - RCC_PLLA_DIV55
*\*\     - RCC_PLLA_DIV56
*\*\     - RCC_PLLA_DIV57
*\*\     - RCC_PLLA_DIV58
*\*\     - RCC_PLLA_DIV59
*\*\     - RCC_PLLA_DIV60
*\*\     - RCC_PLLA_DIV61
*\*\     - RCC_PLLA_DIV62
*\*\     - RCC_PLLA_DIV63
*\*\return none.
**/
void RCC_ConfigPLL2ADivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->PLL2DIV;
    /* Clear RCC_PLL2A_DIV bits */
    reg_value &=  RCC_PLLA_DIV_MASK;
    /* Set the DIV bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->PLL2DIV = reg_value;
}

/**
*\*\name   RCC_ConfigPLL3CDivider .
*\*\fun    Configure PLL3 divider value to PLL3C.
*\*\param  CLK_divider
*\*\     - RCC_PLLC_DIV1
*\*\     - RCC_PLLC_DIV2
*\*\     - RCC_PLLC_DIV3
*\*\     - RCC_PLLC_DIV4
*\*\     - RCC_PLLC_DIV5
*\*\     - RCC_PLLC_DIV6
*\*\     - RCC_PLLC_DIV7
*\*\     - RCC_PLLC_DIV8
*\*\     - RCC_PLLC_DIV9
*\*\     - RCC_PLLC_DIV10
*\*\     - RCC_PLLC_DIV11
*\*\     - RCC_PLLC_DIV12
*\*\     - RCC_PLLC_DIV13
*\*\     - RCC_PLLC_DIV14
*\*\     - RCC_PLLC_DIV15
*\*\     - RCC_PLLC_DIV16
*\*\     - RCC_PLLC_DIV17
*\*\     - RCC_PLLC_DIV18
*\*\     - RCC_PLLC_DIV19
*\*\     - RCC_PLLC_DIV20
*\*\     - RCC_PLLC_DIV21
*\*\     - RCC_PLLC_DIV22
*\*\     - RCC_PLLC_DIV23
*\*\     - RCC_PLLC_DIV24
*\*\     - RCC_PLLC_DIV25
*\*\     - RCC_PLLC_DIV26
*\*\     - RCC_PLLC_DIV27
*\*\     - RCC_PLLC_DIV28
*\*\     - RCC_PLLC_DIV29
*\*\     - RCC_PLLC_DIV30
*\*\     - RCC_PLLC_DIV31
*\*\     - RCC_PLLC_DIV32
*\*\     - RCC_PLLC_DIV33
*\*\     - RCC_PLLC_DIV34
*\*\     - RCC_PLLC_DIV35
*\*\     - RCC_PLLC_DIV36
*\*\     - RCC_PLLC_DIV37
*\*\     - RCC_PLLC_DIV38
*\*\     - RCC_PLLC_DIV39
*\*\     - RCC_PLLC_DIV40
*\*\     - RCC_PLLC_DIV41
*\*\     - RCC_PLLC_DIV42
*\*\     - RCC_PLLC_DIV43
*\*\     - RCC_PLLC_DIV44
*\*\     - RCC_PLLC_DIV45
*\*\     - RCC_PLLC_DIV46
*\*\     - RCC_PLLC_DIV47
*\*\     - RCC_PLLC_DIV48
*\*\     - RCC_PLLC_DIV49
*\*\     - RCC_PLLC_DIV50
*\*\     - RCC_PLLC_DIV51
*\*\     - RCC_PLLC_DIV52
*\*\     - RCC_PLLC_DIV53
*\*\     - RCC_PLLC_DIV54
*\*\     - RCC_PLLC_DIV55
*\*\     - RCC_PLLC_DIV56
*\*\     - RCC_PLLC_DIV57
*\*\     - RCC_PLLC_DIV58
*\*\     - RCC_PLLC_DIV59
*\*\     - RCC_PLLC_DIV60
*\*\     - RCC_PLLC_DIV61
*\*\     - RCC_PLLC_DIV62
*\*\     - RCC_PLLC_DIV63
*\*\return none.
**/
void RCC_ConfigPLL3CDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->PLL3DIV;
    /* Clear RCC_PLL3C_DIV bits */
    reg_value &=  RCC_PLLC_DIV_MASK;
    /* Set the DIV bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->PLL3DIV = reg_value;
}

/**
*\*\name   RCC_ConfigPLL3BDivider .
*\*\fun    Configure PLL3 divider value to PLL3B.
*\*\param  CLK_divider
*\*\     - RCC_PLLB_DIV1
*\*\     - RCC_PLLB_DIV2
*\*\     - RCC_PLLB_DIV3
*\*\     - RCC_PLLB_DIV4
*\*\     - RCC_PLLB_DIV5
*\*\     - RCC_PLLB_DIV6
*\*\     - RCC_PLLB_DIV7
*\*\     - RCC_PLLB_DIV8
*\*\     - RCC_PLLB_DIV9
*\*\     - RCC_PLLB_DIV10
*\*\     - RCC_PLLB_DIV11
*\*\     - RCC_PLLB_DIV12
*\*\     - RCC_PLLB_DIV13
*\*\     - RCC_PLLB_DIV14
*\*\     - RCC_PLLB_DIV15
*\*\     - RCC_PLLB_DIV16
*\*\     - RCC_PLLB_DIV17
*\*\     - RCC_PLLB_DIV18
*\*\     - RCC_PLLB_DIV19
*\*\     - RCC_PLLB_DIV20
*\*\     - RCC_PLLB_DIV21
*\*\     - RCC_PLLB_DIV22
*\*\     - RCC_PLLB_DIV23
*\*\     - RCC_PLLB_DIV24
*\*\     - RCC_PLLB_DIV25
*\*\     - RCC_PLLB_DIV26
*\*\     - RCC_PLLB_DIV27
*\*\     - RCC_PLLB_DIV28
*\*\     - RCC_PLLB_DIV29
*\*\     - RCC_PLLB_DIV30
*\*\     - RCC_PLLB_DIV31
*\*\     - RCC_PLLB_DIV32
*\*\     - RCC_PLLB_DIV33
*\*\     - RCC_PLLB_DIV34
*\*\     - RCC_PLLB_DIV35
*\*\     - RCC_PLLB_DIV36
*\*\     - RCC_PLLB_DIV37
*\*\     - RCC_PLLB_DIV38
*\*\     - RCC_PLLB_DIV39
*\*\     - RCC_PLLB_DIV40
*\*\     - RCC_PLLB_DIV41
*\*\     - RCC_PLLB_DIV42
*\*\     - RCC_PLLB_DIV43
*\*\     - RCC_PLLB_DIV44
*\*\     - RCC_PLLB_DIV45
*\*\     - RCC_PLLB_DIV46
*\*\     - RCC_PLLB_DIV47
*\*\     - RCC_PLLB_DIV48
*\*\     - RCC_PLLB_DIV49
*\*\     - RCC_PLLB_DIV50
*\*\     - RCC_PLLB_DIV51
*\*\     - RCC_PLLB_DIV52
*\*\     - RCC_PLLB_DIV53
*\*\     - RCC_PLLB_DIV54
*\*\     - RCC_PLLB_DIV55
*\*\     - RCC_PLLB_DIV56
*\*\     - RCC_PLLB_DIV57
*\*\     - RCC_PLLB_DIV58
*\*\     - RCC_PLLB_DIV59
*\*\     - RCC_PLLB_DIV60
*\*\     - RCC_PLLB_DIV61
*\*\     - RCC_PLLB_DIV62
*\*\     - RCC_PLLB_DIV63
*\*\return none.
**/
void RCC_ConfigPLL3BDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->PLL3DIV;
    /* Clear RCC_PLL3B_DIV bits */
    reg_value &=  RCC_PLLB_DIV_MASK;
    /* Set the DIV bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->PLL3DIV = reg_value;
}

/**
*\*\name   RCC_ConfigPLL3ADivider .
*\*\fun    Configure PLL3 divider value to PLL3A.
*\*\param  CLK_divider
*\*\     - RCC_PLLA_DIV1
*\*\     - RCC_PLLA_DIV2
*\*\     - RCC_PLLA_DIV3
*\*\     - RCC_PLLA_DIV4
*\*\     - RCC_PLLA_DIV5
*\*\     - RCC_PLLA_DIV6
*\*\     - RCC_PLLA_DIV7
*\*\     - RCC_PLLA_DIV8
*\*\     - RCC_PLLA_DIV9
*\*\     - RCC_PLLA_DIV10
*\*\     - RCC_PLLA_DIV11
*\*\     - RCC_PLLA_DIV12
*\*\     - RCC_PLLA_DIV13
*\*\     - RCC_PLLA_DIV14
*\*\     - RCC_PLLA_DIV15
*\*\     - RCC_PLLA_DIV16
*\*\     - RCC_PLLA_DIV17
*\*\     - RCC_PLLA_DIV18
*\*\     - RCC_PLLA_DIV19
*\*\     - RCC_PLLA_DIV20
*\*\     - RCC_PLLA_DIV21
*\*\     - RCC_PLLA_DIV22
*\*\     - RCC_PLLA_DIV23
*\*\     - RCC_PLLA_DIV24
*\*\     - RCC_PLLA_DIV25
*\*\     - RCC_PLLA_DIV26
*\*\     - RCC_PLLA_DIV27
*\*\     - RCC_PLLA_DIV28
*\*\     - RCC_PLLA_DIV29
*\*\     - RCC_PLLA_DIV30
*\*\     - RCC_PLLA_DIV31
*\*\     - RCC_PLLA_DIV32
*\*\     - RCC_PLLA_DIV33
*\*\     - RCC_PLLA_DIV34
*\*\     - RCC_PLLA_DIV35
*\*\     - RCC_PLLA_DIV36
*\*\     - RCC_PLLA_DIV37
*\*\     - RCC_PLLA_DIV38
*\*\     - RCC_PLLA_DIV39
*\*\     - RCC_PLLA_DIV40
*\*\     - RCC_PLLA_DIV41
*\*\     - RCC_PLLA_DIV42
*\*\     - RCC_PLLA_DIV43
*\*\     - RCC_PLLA_DIV44
*\*\     - RCC_PLLA_DIV45
*\*\     - RCC_PLLA_DIV46
*\*\     - RCC_PLLA_DIV47
*\*\     - RCC_PLLA_DIV48
*\*\     - RCC_PLLA_DIV49
*\*\     - RCC_PLLA_DIV50
*\*\     - RCC_PLLA_DIV51
*\*\     - RCC_PLLA_DIV52
*\*\     - RCC_PLLA_DIV53
*\*\     - RCC_PLLA_DIV54
*\*\     - RCC_PLLA_DIV55
*\*\     - RCC_PLLA_DIV56
*\*\     - RCC_PLLA_DIV57
*\*\     - RCC_PLLA_DIV58
*\*\     - RCC_PLLA_DIV59
*\*\     - RCC_PLLA_DIV60
*\*\     - RCC_PLLA_DIV61
*\*\     - RCC_PLLA_DIV62
*\*\     - RCC_PLLA_DIV63
*\*\return none.
**/
void RCC_ConfigPLL3ADivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->PLL3DIV;
    /* Clear RCC_PLL3A_DIV bits */
    reg_value &=  RCC_PLLA_DIV_MASK;
    /* Set the DIV bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->PLL3DIV = reg_value;
}

/**
*\*\name   RCC_ConfigAXIHyperDivider.
*\*\fun    Obtained by dividing the m7_hyp_div_clk.
*\*\param  CLK_divider
*\*\     - RCC_AXICLK_HYP_DIV1
*\*\     - RCC_AXICLK_HYP_DIV2
*\*\     - RCC_AXICLK_HYP_DIV4
*\*\     - RCC_AXICLK_HYP_DIV8
*\*\     - RCC_AXICLK_HYP_DIV16
*\*\     - RCC_AXICLK_HYP_DIV32
*\*\     - RCC_AXICLK_HYP_DIV64
*\*\     - RCC_AXICLK_HYP_DIV128
*\*\     - RCC_AXICLK_HYP_DIV256
*\*\     - RCC_AXICLK_HYP_DIV512
*\*\return none.
**/
void RCC_ConfigAXIHyperDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->SYSBUSDIV1;
    /* Clear AXIHYPDIV bits */
    reg_value &=  RCC_AXICLK_HYP_DIV_MASK;
    /* Set the AXIHYPDIV bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->SYSBUSDIV1 = reg_value;
}

/**
*\*\name   RCC_ConfigM7HyperDivider .
*\*\fun    Configure PLL2A divider value to m7_hyp_div_clk.
*\*\param  CLK_divider
*\*\     - RCC_M7CLK_HYP_DIV1
*\*\     - RCC_M7CLK_HYP_DIV2
*\*\     - RCC_M7CLK_HYP_DIV4
*\*\     - RCC_M7CLK_HYP_DIV8
*\*\     - RCC_M7CLK_HYP_DIV16
*\*\     - RCC_M7CLK_HYP_DIV32
*\*\     - RCC_M7CLK_HYP_DIV64
*\*\     - RCC_M7CLK_HYP_DIV128
*\*\     - RCC_M7CLK_HYP_DIV256
*\*\     - RCC_M7CLK_HYP_DIV512
*\*\return none.
**/
void RCC_ConfigM7HyperDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->SYSBUSDIV1;
    /* Clear M7HYPDIV bits */
    reg_value &=  RCC_M7CLK_HYP_DIV_MASK;
    /* Set the M7HYPDIV bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->SYSBUSDIV1 = reg_value;
}

/**
*\*\name   RCC_ConfigAXIclkDivider .
*\*\fun    Obtained by dividing the sys_div_clk.
*\*\param  CLK_divider
*\*\     - RCC_AXICLK_DIV1
*\*\     - RCC_AXICLK_DIV2
*\*\     - RCC_AXICLK_DIV4
*\*\     - RCC_AXICLK_DIV8
*\*\     - RCC_AXICLK_DIV16
*\*\     - RCC_AXICLK_DIV32
*\*\     - RCC_AXICLK_DIV64
*\*\     - RCC_AXICLK_DIV128
*\*\     - RCC_AXICLK_DIV256
*\*\     - RCC_AXICLK_DIV512
*\*\return none.
**/
void RCC_ConfigAXIclkDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->SYSBUSDIV1;
    /* Clear AXIDIV bits */
    reg_value &=  RCC_AXICLK_DIV_MASK;
    /* Set the AXIDIV bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->SYSBUSDIV1 = reg_value;
}

/**
*\*\name   RCC_ConfigSysbusDivider .
*\*\fun    Configure sys_div_clk divider value to sys_bus_div_clk.
*\*\param  CLK_divider
*\*\     - RCC_BUSCLK_DIV1
*\*\     - RCC_BUSCLK_DIV2
*\*\     - RCC_BUSCLK_DIV4
*\*\     - RCC_BUSCLK_DIV8
*\*\     - RCC_BUSCLK_DIV16
*\*\     - RCC_BUSCLK_DIV32
*\*\     - RCC_BUSCLK_DIV64
*\*\     - RCC_BUSCLK_DIV128
*\*\     - RCC_BUSCLK_DIV256
*\*\     - RCC_BUSCLK_DIV512
*\*\return none.
**/
void RCC_ConfigSysbusDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->SYSBUSDIV1;
    /* Clear BUSDIV bits */
    reg_value &=  RCC_BUSCLK_DIV_MASK;
    /* Set the BUSDIV bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->SYSBUSDIV1 = reg_value;
}

/**
*\*\name   RCC_ConfigSysclkDivider .
*\*\fun    Configure sys_clk divider value to sys_div_clk.
*\*\param  CLK_divider
*\*\     - RCC_SYSCLK_DIV1
*\*\     - RCC_SYSCLK_DIV2
*\*\     - RCC_SYSCLK_DIV4
*\*\     - RCC_SYSCLK_DIV8
*\*\     - RCC_SYSCLK_DIV16
*\*\     - RCC_SYSCLK_DIV32
*\*\     - RCC_SYSCLK_DIV64
*\*\     - RCC_SYSCLK_DIV128
*\*\     - RCC_SYSCLK_DIV256
*\*\     - RCC_SYSCLK_DIV512
*\*\return none.
**/
void RCC_ConfigSysclkDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->SYSBUSDIV1;
    /* Clear SCLKDIV bits */
    reg_value &=  RCC_SYSCLK_DIV_MASK;
    /* Set the SCLKDIV bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->SYSBUSDIV1 = reg_value;
}

/**
*\*\name   RCC_ConfigAPBclkDivider .
*\*\fun    Configure AHB1 clock divider value to APB1 clock.
*\*\param  APB1_divider
*\*\     - RCC_APB1CLK_DIV1
*\*\     - RCC_APB1CLK_DIV2
*\*\     - RCC_APB1CLK_DIV4
*\*\     - RCC_APB1CLK_DIV8
*\*\     - RCC_APB1CLK_DIV16
*\*\param  APB2_divider
*\*\     - RCC_APB2CLK_DIV1
*\*\     - RCC_APB2CLK_DIV2
*\*\     - RCC_APB2CLK_DIV4
*\*\     - RCC_APB2CLK_DIV8
*\*\     - RCC_APB2CLK_DIV16
*\*\param  APB5_divider
*\*\     - RCC_APB5CLK_DIV1
*\*\     - RCC_APB5CLK_DIV2
*\*\     - RCC_APB5CLK_DIV4
*\*\     - RCC_APB5CLK_DIV8
*\*\     - RCC_APB5CLK_DIV16
*\*\param  APB6_divider
*\*\     - RCC_APB6CLK_DIV1
*\*\     - RCC_APB6CLK_DIV2
*\*\     - RCC_APB6CLK_DIV4
*\*\     - RCC_APB6CLK_DIV8
*\*\     - RCC_APB6CLK_DIV16
*\*\return none.
**/
void RCC_ConfigAPBclkDivider(uint32_t APB1_divider, uint32_t APB2_divider, uint32_t APB5_divider, uint32_t APB6_divider)
{
    uint32_t reg_value;

    reg_value = RCC->SYSBUSDIV2;
    /* Clear APB1DIV bits */
    reg_value &=  RCC_APBCLK_DIV_MASK;
    /* Set the APB1DIV bits */
    reg_value |=  (APB1_divider | APB2_divider | APB5_divider | APB6_divider);
    /* Store the new value */
    RCC->SYSBUSDIV2 = reg_value;
}


/**
*\*\name    RCC_EnableAHB1PeriphReset1.
*\*\fun     AHB1 peripheral reset.
*\*\param   AHB_periph specifies the AHB peripheral to reset.
*\*\        - RCC_AHB1_PERIPHRST_SDMMC2
*\*\        - RCC_AHB1_PERIPHRST_SDHOST2
*\*\        - RCC_AHB1_PERIPHRST_USB2WRAP
*\*\        - RCC_AHB1_PERIPHRST_USB2POR
*\*\        - RCC_AHB1_PERIPHRST_USB2
*\*\        - RCC_AHB1_PERIPHRST_DMAMUX1
*\*\        - RCC_AHB1_PERIPHRST_ADC1
*\*\return none.
**/
void RCC_EnableAHB1PeriphReset1(uint32_t AHB_periph)
{
    RCC->AHB1RST1 |= AHB_periph;
    RCC->AHB1RST1 &= ~AHB_periph;
}

/**
*\*\name    RCC_EnableAHB1PeriphReset2.
*\*\fun     AHB1 peripheral reset.
*\*\param   AHB_periph specifies the AHB peripheral to reset.
*\*\        - RCC_AHB1_PERIPHRST_ETH2
*\*\return none.
**/
void RCC_EnableAHB1PeriphReset2(uint32_t AHB_periph)
{
    RCC->AHB1RST2 |= AHB_periph;
    RCC->AHB1RST2 &= ~AHB_periph;
}

/**
*\*\name    RCC_EnableAHB1PeriphReset3.
*\*\fun     AHB1 peripheral reset.
*\*\param   AHB_periph specifies the AHB peripheral to reset.
*\*\        - RCC_AHB1_PERIPHRST_ECCMAC
*\*\        - RCC_AHB1_PERIPHRST_DMA1
*\*\        - RCC_AHB1_PERIPHRST_DMA2
*\*\        - RCC_AHB1_PERIPHRST_DMA3
*\*\return none.
**/
void RCC_EnableAHB1PeriphReset3(uint32_t AHB_periph)
{
    RCC->AHB1RST3 |= AHB_periph;
    RCC->AHB1RST3 &= ~AHB_periph;
}

/**
*\*\name    RCC_EnableAHB1PeriphReset4.
*\*\fun     AHB1 peripheral reset.
*\*\param   AHB_periph specifies the AHB peripheral to reset.
*\*\        - RCC_AHB1_PERIPHRST_ADC2
*\*\        - RCC_AHB1_PERIPHRST_ADC3
*\*\return none.
**/
void RCC_EnableAHB1PeriphReset4(uint32_t AHB_periph)
{
    RCC->AHB1RST4 |= AHB_periph;
    RCC->AHB1RST4 &= ~AHB_periph;
}

/**
*\*\name    RCC_EnableAPB1PeriphReset1.
*\*\fun     APB1 peripheral reset.
*\*\param   APB_periph specifies the APB peripheral to reset.
*\*\        - RCC_APB1_PERIPHRST_BTIM1
*\*\        - RCC_APB1_PERIPHRST_BTIM2
*\*\        - RCC_APB1_PERIPHRST_BTIM3
*\*\        - RCC_APB1_PERIPHRST_BTIM4
*\*\        - RCC_APB1_PERIPHRST_GTIMB1
*\*\        - RCC_APB1_PERIPHRST_GTIMB2
*\*\        - RCC_APB1_PERIPHRST_GTIMB3
*\*\        - RCC_APB1_PERIPHRST_GTIMA4
*\*\return none.
**/
void RCC_EnableAPB1PeriphReset1(uint32_t APB_periph)
{
    RCC->APB1RST1 |= APB_periph;
    RCC->APB1RST1 &= ~APB_periph;
}

/**
*\*\name    RCC_EnableAPB1PeriphReset2.
*\*\fun     APB1 peripheral reset.
*\*\param   APB_periph specifies the APB peripheral to reset.
*\*\        - RCC_APB1_PERIPHRST_GTIMA5
*\*\        - RCC_APB1_PERIPHRST_GTIMA6
*\*\        - RCC_APB1_PERIPHRST_GTIMA7
*\*\        - RCC_APB1_PERIPHRST_SPI3
*\*\        - RCC_APB1_PERIPHRST_DAC12
*\*\        - RCC_APB1_PERIPHRST_WWDG2
*\*\return none.
**/
void RCC_EnableAPB1PeriphReset2(uint32_t APB_periph)
{
    RCC->APB1RST2 |= APB_periph;
    RCC->APB1RST2 &= ~APB_periph;
}

/**
*\*\name    RCC_EnableAPB1PeriphReset3.
*\*\fun     APB1 peripheral reset.
*\*\param   APB_periph specifies the APB peripheral to reset.
*\*\        - RCC_APB1_PERIPHRST_USART1
*\*\        - RCC_APB1_PERIPHRST_USART2
*\*\        - RCC_APB1_PERIPHRST_USART3
*\*\        - RCC_APB1_PERIPHRST_USART4
*\*\        - RCC_APB1_PERIPHRST_UART9
*\*\        - RCC_APB1_PERIPHRST_UART10
*\*\        - RCC_APB1_PERIPHRST_UART11
*\*\        - RCC_APB1_PERIPHRST_UART12
*\*\return none.
**/
void RCC_EnableAPB1PeriphReset3(uint32_t APB_periph)
{
    RCC->APB1RST3 |= APB_periph;
    RCC->APB1RST3 &= ~APB_periph;
}

/**
*\*\name    RCC_EnableAPB1PeriphReset4.
*\*\fun     APB1 peripheral reset.
*\*\param   APB_periph specifies the APB peripheral to reset.
*\*\        - RCC_APB1_PERIPHRST_I2S3
*\*\        - RCC_APB1_PERIPHRST_I2S4
*\*\        - RCC_APB1_PERIPHRST_I2C1
*\*\        - RCC_APB1_PERIPHRST_I2C2
*\*\        - RCC_APB1_PERIPHRST_I2C3
*\*\return none.
**/
void RCC_EnableAPB1PeriphReset4(uint32_t APB_periph)
{
    RCC->APB1RST4 |= APB_periph;
    RCC->APB1RST4 &= ~APB_periph;
}

/**
*\*\name    RCC_EnableAPB1PeriphReset5.
*\*\fun     APB1 peripheral reset.
*\*\param   APB_periph specifies the APB peripheral to reset.
*\*\        - RCC_APB1_PERIPHRST_FDCAN1
*\*\        - RCC_APB1_PERIPHRST_FDCAN2
*\*\        - RCC_APB1_PERIPHRST_FDCAN5
*\*\        - RCC_APB1_PERIPHRST_FDCAN6
*\*\        - RCC_APB1_PERIPHRST_CAHI
*\*\        - RCC_APB1_PERIPHRST_CAHD
*\*\return none.
**/
void RCC_EnableAPB1PeriphReset5(uint32_t APB_periph)
{
    RCC->APB1RST5 |= APB_periph;
    RCC->APB1RST5 &= ~APB_periph;
}

/**
*\*\name    RCC_EnableAHB2PeriphReset1.
*\*\fun     AHB2 peripheral reset.
*\*\param   AHB_periph specifies the AHB peripheral to reset.
*\*\        - RCC_AHB2_PERIPHRST_DAC56
*\*\        - RCC_AHB2_PERIPHRST_DAC34
*\*\        - RCC_AHB2_PERIPHRST_USB1WRAP
*\*\        - RCC_AHB2_PERIPHRST_USB1POR
*\*\        - RCC_AHB2_PERIPHRST_USB1
*\*\        - RCC_AHB2_PERIPHRST_ETH1
*\*\        - RCC_AHB2_PERIPHRST_ECCM2
*\*\        - RCC_AHB2_PERIPHRST_CORDIC
*\*\        - RCC_AHB2_PERIPHRST_SDPU
*\*\        - RCC_AHB2_PERIPHRST_FMAC
*\*\return none.
**/
void RCC_EnableAHB2PeriphReset1(uint32_t AHB_periph)
{
    RCC->AHB2RST1 |= AHB_periph;
    RCC->AHB2RST1 &= ~AHB_periph;
}

/**
*\*\name    RCC_EnableAPB2PeriphReset1.
*\*\fun     APB2 peripheral reset.
*\*\param   APB_periph specifies the APB peripheral to reset.
*\*\        - RCC_APB2_PERIPHRST_ATIM1
*\*\        - RCC_APB2_PERIPHRST_ATIM2
*\*\        - RCC_APB2_PERIPHRST_GTIMA1
*\*\        - RCC_APB2_PERIPHRST_GTIMA2
*\*\        - RCC_APB2_PERIPHRST_GTIMA3
*\*\        - RCC_APB2_PERIPHRST_SHRTIM1
*\*\        - RCC_APB2_PERIPHRST_SHRTIM2
*\*\return none.
**/
void RCC_EnableAPB2PeriphReset1(uint32_t APB_periph)
{
    RCC->APB2RST1 |= APB_periph;
    RCC->APB2RST1 &= ~APB_periph;
}

/**
*\*\name    RCC_EnableAPB2PeriphReset2.
*\*\fun     APB2 peripheral reset.
*\*\param   APB_periph specifies the APB peripheral to reset.
*\*\        - RCC_APB2_PERIPHRST_I2S1
*\*\        - RCC_APB2_PERIPHRST_I2S2
*\*\        - RCC_APB2_PERIPHRST_SPI1
*\*\        - RCC_APB2_PERIPHRST_SPI2
*\*\        - RCC_APB2_PERIPHRST_DSMU
*\*\        - RCC_APB2_PERIPHRST_I2C4
*\*\        - RCC_APB2_PERIPHRST_I2C5
*\*\        - RCC_APB2_PERIPHRST_I2C6
*\*\return none.
**/
void RCC_EnableAPB2PeriphReset2(uint32_t APB_periph)
{
    RCC->APB2RST2 |= APB_periph;
    RCC->APB2RST2 &= ~APB_periph;
}

/**
*\*\name    RCC_EnableAPB2PeriphReset3.
*\*\fun     APB2 peripheral reset.
*\*\param   APB_periph specifies the APB peripheral to reset.
*\*\        - RCC_APB2_PERIPHRST_USART5
*\*\        - RCC_APB2_PERIPHRST_USART6
*\*\        - RCC_APB2_PERIPHRST_USART7
*\*\        - RCC_APB2_PERIPHRST_USART8
*\*\        - RCC_APB2_PERIPHRST_UART13
*\*\        - RCC_APB2_PERIPHRST_UART14
*\*\        - RCC_APB2_PERIPHRST_UART15
*\*\return none.
**/
void RCC_EnableAPB2PeriphReset3(uint32_t APB_periph)
{
    RCC->APB2RST3 |= APB_periph;
    RCC->APB2RST3 &= ~APB_periph;
}

/**
*\*\name    RCC_EnableAPB2PeriphReset4.
*\*\fun     APB2 peripheral reset.
*\*\param   APB_periph specifies the APB peripheral to reset.
*\*\        - RCC_APB2_PERIPHRST_FDCAN3
*\*\        - RCC_APB2_PERIPHRST_FDCAN4
*\*\        - RCC_APB2_PERIPHRST_FDCAN7
*\*\        - RCC_APB2_PERIPHRST_FDCAN8
*\*\return none.
**/
void RCC_EnableAPB2PeriphReset4(uint32_t APB_periph)
{
    RCC->APB2RST4 |= APB_periph;
    RCC->APB2RST4 &= ~APB_periph;
}

/**
*\*\name    RCC_EnableAHB5PeriphReset1.
*\*\fun     AHB5 peripheral reset.
*\*\param   AHB_periph specifies the AHB peripheral to reset.
*\*\        - RCC_AHB5_PERIPHRST_GPIOA
*\*\        - RCC_AHB5_PERIPHRST_GPIOB
*\*\        - RCC_AHB5_PERIPHRST_GPIOC
*\*\        - RCC_AHB5_PERIPHRST_GPIOD
*\*\        - RCC_AHB5_PERIPHRST_GPIOE
*\*\        - RCC_AHB5_PERIPHRST_GPIOF
*\*\        - RCC_AHB5_PERIPHRST_GPIOG
*\*\        - RCC_AHB5_PERIPHRST_GPIOH
*\*\return none.
**/
void RCC_EnableAHB5PeriphReset1(uint32_t AHB_periph)
{
    RCC->AHB5RST1 |= AHB_periph;
    RCC->AHB5RST1 &= ~AHB_periph;
}

/**
*\*\name    RCC_EnableAHB5PeriphReset2.
*\*\fun     AHB5 peripheral reset.
*\*\param   AHB_periph specifies the AHB peripheral to reset.
*\*\        - RCC_AHB5_PERIPHRST_GPIOI
*\*\        - RCC_AHB5_PERIPHRST_GPIOJ
*\*\        - RCC_AHB5_PERIPHRST_GPIOK
*\*\        - RCC_AHB5_PERIPHRST_ECCM3
*\*\        - RCC_AHB5_PERIPHRST_PWR
*\*\        - RCC_AHB5_PERIPHRST_CRC
*\*\        - RCC_AHB5_PERIPHRST_SEMA4
*\*\        - RCC_AHB5_PERIPHRST_AFIO
*\*\return none.
**/
void RCC_EnableAHB5PeriphReset2(uint32_t AHB_periph)
{
    RCC->AHB5RST2 |= AHB_periph;
    RCC->AHB5RST2 &= ~AHB_periph;
}

/**
*\*\name    RCC_EnableAPB5PeriphReset1.
*\*\fun     APB5 peripheral reset.
*\*\param   APB_periph specifies the APB peripheral to reset.
*\*\        - RCC_APB5_PERIPHRST_ATIM3
*\*\        - RCC_APB5_PERIPHRST_ATIM4
*\*\        - RCC_APB5_PERIPHRST_SPI4
*\*\        - RCC_APB5_PERIPHRST_SPI5
*\*\        - RCC_APB5_PERIPHRST_SPI6
*\*\        - RCC_APB5_PERIPHRST_SPI7
*\*\return none.
**/
void RCC_EnableAPB5PeriphReset1(uint32_t APB_periph)
{
    RCC->APB5RST1 |= APB_periph;
    RCC->APB5RST1 &= ~APB_periph;
}

/**
*\*\name    RCC_EnableAPB5PeriphReset2.
*\*\fun     APB5 peripheral reset.
*\*\param   APB_periph specifies the APB peripheral to reset.
*\*\        - RCC_APB5_PERIPHRST_I2C7
*\*\        - RCC_APB5_PERIPHRST_I2C8
*\*\        - RCC_APB5_PERIPHRST_I2C9
*\*\        - RCC_APB5_PERIPHRST_I2C10
*\*\return none.
**/
void RCC_EnableAPB5PeriphReset2(uint32_t APB_periph)
{
    RCC->APB5RST2 |= APB_periph;
    RCC->APB5RST2 &= ~APB_periph;
}

/**
*\*\name    RCC_EnableAXIPeriphReset1.
*\*\fun     AXI/AHB6/APB6 peripheral reset.
*\*\param   AXI_periph specifies the AXI/AHB6/APB6 peripheral to reset.
*\*\        - RCC_AXI_PERIPHRST_JPEGD
*\*\        - RCC_AXI_PERIPHRST_JPEGE
*\*\        - RCC_AXI_PERIPHRST_DMAMUX2
*\*\        - RCC_AXI_PERIPHRST_MDMA
*\*\        - RCC_AXI_PERIPHRST_SDMMC1
*\*\        - RCC_AXI_PERIPHRST_SDHOST1
*\*\        - RCC_AXI_PERIPHRST_ECCM1
*\*\        - RCC_AXI_PERIPHRST_OTPC
*\*\return none.
**/
void RCC_EnableAXIPeriphReset1(uint32_t AXI_periph)
{
    RCC->AXIRST1 |= AXI_periph;
    RCC->AXIRST1 &= ~AXI_periph;
}

/**
*\*\name    RCC_EnableAXIPeriphReset2.
*\*\fun     AXI/AHB6/APB6 peripheral reset.
*\*\param   AXI_periph specifies the AXI/AHB6/APB6 peripheral to reset.
*\*\        - RCC_AXI_PERIPHRST_DSICFG
*\*\        - RCC_AXI_PERIPHRST_DSI
*\*\        - RCC_AXI_PERIPHRST_LCDC
*\*\        - RCC_AXI_PERIPHRST_DVP1
*\*\        - RCC_AXI_PERIPHRST_DVP2
*\*\        - RCC_AXI_PERIPHRST_WWDG1
*\*\return none.
**/
void RCC_EnableAXIPeriphReset2(uint32_t AXI_periph)
{
    RCC->AXIRST2 |= AXI_periph;
    RCC->AXIRST2 &= ~AXI_periph;
}

/**
*\*\name    RCC_EnableAXIPeriphReset3.
*\*\fun     AXI/AHB6/APB6 peripheral reset.
*\*\param   AXI_periph specifies the AXI/AHB6/APB6 peripheral to reset.
*\*\        - RCC_AXI_PERIPHRST_GPU
*\*\return none.
**/
void RCC_EnableAXIPeriphReset3(uint32_t AXI_periph)
{
    RCC->AXIRST3 |= AXI_periph;
    RCC->AXIRST3 &= ~AXI_periph;
}

/**
*\*\name    RCC_EnableAXIPeriphReset4.
*\*\fun     AXI/AHB6/APB6 peripheral reset.
*\*\param   AXI_periph specifies the AXI/AHB6/APB6 peripheral to reset.
*\*\        - RCC_AXI_PERIPHRST_XSPI1
*\*\        - RCC_AXI_PERIPHRST_XSPI2
*\*\        - RCC_AXI_PERIPHRST_FEMCCFG
*\*\        - RCC_AXI_PERIPHRST_FEMC
*\*\        - RCC_AXI_PERIPHRST_SDRAM
*\*\return none.
**/
void RCC_EnableAXIPeriphReset4(uint32_t AXI_periph)
{
    RCC->AXIRST4 |= AXI_periph;
    RCC->AXIRST4 &= ~AXI_periph;
}

/**
*\*\name    RCC_EnableAHB9PeriphReset1.
*\*\fun     AHB9 peripheral reset.
*\*\param   AHB_periph specifies the AHB9 peripheral to reset.
*\*\        - RCC_AHB9_PERIPHRST_ESC
*\*\return none.
**/
void RCC_EnableAHB9PeriphReset1(uint32_t AHB_periph)
{
    RCC->AHB9RST1 |= AHB_periph;
    RCC->AHB9RST1 &= ~AHB_periph;
}

/**
*\*\name    RCC_EnableRDPeriphReset1.
*\*\fun     Retention domain peripheral reset.
*\*\param   RD_periph specifies the Retention domain peripheral to reset.
*\*\        - RCC_RD_PERIPHRST_LPTIM1
*\*\        - RCC_RD_PERIPHRST_LPTIM2
*\*\        - RCC_RD_PERIPHRST_LPTIM3
*\*\        - RCC_RD_PERIPHRST_LPTIM4
*\*\        - RCC_RD_PERIPHRST_LPTIM5
*\*\        - RCC_RD_PERIPHRST_LPUART1
*\*\        - RCC_RD_PERIPHRST_LPUART2
*\*\return none.
**/
void RCC_EnableRDPeriphReset1(uint32_t RD_periph)
{
    RCC->RDRST1 |= RD_periph;
    RCC->RDRST1 &= ~RD_periph;
}

/**
*\*\name    RCC_EnableRDPeriphReset2.
*\*\fun     Retention domain peripheral reset.
*\*\param   RD_periph specifies the Retention domain peripheral to reset.
*\*\        - RCC_RD_PERIPHRST_COMP
*\*\return none.
**/
void RCC_EnableRDPeriphReset2(uint32_t RD_periph)
{
    RCC->RDRST2 |= RD_periph;
    RCC->RDRST2 &= ~RD_periph;
}

/**
*\*\name    RCC_EnableAHB1PeriphClk1.
*\*\fun     Enables the AHB1 peripheral clock.
*\*\param   AHB_periph (AHB peripheral to gates its clock):
*\*\     - RCC_AHB1_PERIPHEN_M7_SDMMC2
*\*\     - RCC_AHB1_PERIPHEN_M4_SDMMC2
*\*\     - RCC_AHB1_PERIPHEN_M7_SDMMC2LP
*\*\     - RCC_AHB1_PERIPHEN_M4_SDMMC2LP
*\*\     - RCC_AHB1_PERIPHEN_M7_USB2
*\*\     - RCC_AHB1_PERIPHEN_M4_USB2
*\*\     - RCC_AHB1_PERIPHEN_M7_USB2LP
*\*\     - RCC_AHB1_PERIPHEN_M4_USB2LP
*\*\     - RCC_AHB1_PERIPHEN_M7_DMAMUX1
*\*\     - RCC_AHB1_PERIPHEN_M4_DMAMUX1
*\*\     - RCC_AHB1_PERIPHEN_M7_DMAMUX1LP
*\*\     - RCC_AHB1_PERIPHEN_M4_DMAMUX1LP
*\*\     - RCC_AHB1_PERIPHEN_M7_ADC1PLL
*\*\     - RCC_AHB1_PERIPHEN_M4_ADC1PLL
*\*\     - RCC_AHB1_PERIPHEN_M7_ADC1PLLLP
*\*\     - RCC_AHB1_PERIPHEN_M4_ADC1PLLLP
*\*\     - RCC_AHB1_PERIPHEN_M7_ADC1SYS
*\*\     - RCC_AHB1_PERIPHEN_M4_ADC1SYS
*\*\     - RCC_AHB1_PERIPHEN_M7_ADC1SYSLP
*\*\     - RCC_AHB1_PERIPHEN_M4_ADC1SYSLP
*\*\     - RCC_AHB1_PERIPHEN_M7_ADC1BUS
*\*\     - RCC_AHB1_PERIPHEN_M4_ADC1BUS
*\*\     - RCC_AHB1_PERIPHEN_M7_ADC1BUSLP
*\*\     - RCC_AHB1_PERIPHEN_M4_ADC1BUSLP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAHB1PeriphClk1(uint32_t AHB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->AHB1EN1 |= AHB_periph;
    }
    else
    {
        RCC->AHB1EN1 &= ~AHB_periph;
    }
}

/**
*\*\name    RCC_EnableAHB1PeriphClk2.
*\*\fun     Enables the AHB1 peripheral clock.
*\*\param   AHB_periph (AHB peripheral to gates its clock):
*\*\     - RCC_AHB1_PERIPHEN_M7_ETH2TX
*\*\     - RCC_AHB1_PERIPHEN_M4_ETH2TX
*\*\     - RCC_AHB1_PERIPHEN_M7_ETH2TXLP
*\*\     - RCC_AHB1_PERIPHEN_M4_ETH2TXLP
*\*\     - RCC_AHB1_PERIPHEN_M7_ETH2RX
*\*\     - RCC_AHB1_PERIPHEN_M4_ETH2RX
*\*\     - RCC_AHB1_PERIPHEN_M7_ETH2RXLP
*\*\     - RCC_AHB1_PERIPHEN_M4_ETH2RXLP
*\*\     - RCC_AHB1_PERIPHEN_M7_ETH2MAC
*\*\     - RCC_AHB1_PERIPHEN_M4_ETH2MAC
*\*\     - RCC_AHB1_PERIPHEN_M7_ETH2MACLP
*\*\     - RCC_AHB1_PERIPHEN_M4_ETH2MACLP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAHB1PeriphClk2(uint32_t AHB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->AHB1EN2 |= AHB_periph;
    }
    else
    {
        RCC->AHB1EN2 &= ~AHB_periph;
    }
}

/**
*\*\name    RCC_EnableAHB1PeriphClk3.
*\*\fun     Enables the AHB1 peripheral clock.
*\*\param   AHB_periph (AHB peripheral to gates its clock):
*\*\     - RCC_AHB1_PERIPHEN_M7_ECCMAC
*\*\     - RCC_AHB1_PERIPHEN_M4_ECCMAC
*\*\     - RCC_AHB1_PERIPHEN_M7_ECCMACLP
*\*\     - RCC_AHB1_PERIPHEN_M4_ECCMACLP
*\*\     - RCC_AHB1_PERIPHEN_M7_DMA1
*\*\     - RCC_AHB1_PERIPHEN_M4_DMA1
*\*\     - RCC_AHB1_PERIPHEN_M7_DMA1LP
*\*\     - RCC_AHB1_PERIPHEN_M4_DMA1LP
*\*\     - RCC_AHB1_PERIPHEN_M7_DMA2
*\*\     - RCC_AHB1_PERIPHEN_M4_DMA2
*\*\     - RCC_AHB1_PERIPHEN_M7_DMA2LP
*\*\     - RCC_AHB1_PERIPHEN_M4_DMA2LP
*\*\     - RCC_AHB1_PERIPHEN_M7_DMA3
*\*\     - RCC_AHB1_PERIPHEN_M4_DMA3
*\*\     - RCC_AHB1_PERIPHEN_M7_DMA3LP
*\*\     - RCC_AHB1_PERIPHEN_M4_DMA3LP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAHB1PeriphClk3(uint32_t AHB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->AHB1EN3 |= AHB_periph;
    }
    else
    {
        RCC->AHB1EN3 &= ~AHB_periph;
    }
}

/**
*\*\name    RCC_EnableAHB1PeriphClk4.
*\*\fun     Enables the AHB1 peripheral clock.
*\*\param   AHB_periph (AHB peripheral to gates its clock):
*\*\     - RCC_AHB1_PERIPHEN_M7_ADC2PLL
*\*\     - RCC_AHB1_PERIPHEN_M4_ADC2PLL
*\*\     - RCC_AHB1_PERIPHEN_M7_ADC2PLLLP
*\*\     - RCC_AHB1_PERIPHEN_M4_ADC2PLLLP
*\*\     - RCC_AHB1_PERIPHEN_M7_ADC2SYS
*\*\     - RCC_AHB1_PERIPHEN_M4_ADC2SYS
*\*\     - RCC_AHB1_PERIPHEN_M7_ADC2SYSLP
*\*\     - RCC_AHB1_PERIPHEN_M4_ADC2SYSLP
*\*\     - RCC_AHB1_PERIPHEN_M7_ADC2BUS
*\*\     - RCC_AHB1_PERIPHEN_M4_ADC2BUS
*\*\     - RCC_AHB1_PERIPHEN_M7_ADC2BUSLP
*\*\     - RCC_AHB1_PERIPHEN_M4_ADC2BUSLP
*\*\     - RCC_AHB1_PERIPHEN_M7_ADC3PLL
*\*\     - RCC_AHB1_PERIPHEN_M4_ADC3PLL
*\*\     - RCC_AHB1_PERIPHEN_M7_ADC3PLLLP
*\*\     - RCC_AHB1_PERIPHEN_M4_ADC3PLLLP
*\*\     - RCC_AHB1_PERIPHEN_M7_ADC3SYS
*\*\     - RCC_AHB1_PERIPHEN_M4_ADC3SYS
*\*\     - RCC_AHB1_PERIPHEN_M7_ADC3SYSLP
*\*\     - RCC_AHB1_PERIPHEN_M4_ADC3SYSLP
*\*\     - RCC_AHB1_PERIPHEN_M7_ADC3BUS
*\*\     - RCC_AHB1_PERIPHEN_M4_ADC3BUS
*\*\     - RCC_AHB1_PERIPHEN_M7_ADC3BUSLP
*\*\     - RCC_AHB1_PERIPHEN_M4_ADC3BUSLP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAHB1PeriphClk4(uint32_t AHB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->AHB1EN4 |= AHB_periph;
    }
    else
    {
        RCC->AHB1EN4 &= ~AHB_periph;
    }
}

/**
*\*\name    RCC_EnableAPB1PeriphClk1.
*\*\fun     Enables the APB1 peripheral clock.
*\*\param   APB_periph (APB peripheral to gates its clock):
*\*\     - RCC_APB1_PERIPHEN_M7_BTIM1
*\*\     - RCC_APB1_PERIPHEN_M4_BTIM1
*\*\     - RCC_APB1_PERIPHEN_M7_BTIM1LP
*\*\     - RCC_APB1_PERIPHEN_M4_BTIM1LP
*\*\     - RCC_APB1_PERIPHEN_M7_BTIM2
*\*\     - RCC_APB1_PERIPHEN_M4_BTIM2
*\*\     - RCC_APB1_PERIPHEN_M7_BTIM2LP
*\*\     - RCC_APB1_PERIPHEN_M4_BTIM2LP
*\*\     - RCC_APB1_PERIPHEN_M7_BTIM3
*\*\     - RCC_APB1_PERIPHEN_M4_BTIM3
*\*\     - RCC_APB1_PERIPHEN_M7_BTIM3LP
*\*\     - RCC_APB1_PERIPHEN_M4_BTIM3LP
*\*\     - RCC_APB1_PERIPHEN_M7_BTIM4
*\*\     - RCC_APB1_PERIPHEN_M4_BTIM4
*\*\     - RCC_APB1_PERIPHEN_M7_BTIM4LP
*\*\     - RCC_APB1_PERIPHEN_M4_BTIM4LP
*\*\     - RCC_APB1_PERIPHEN_M7_GTIMB1
*\*\     - RCC_APB1_PERIPHEN_M4_GTIMB1
*\*\     - RCC_APB1_PERIPHEN_M7_GTIMB1LP
*\*\     - RCC_APB1_PERIPHEN_M4_GTIMB1LP
*\*\     - RCC_APB1_PERIPHEN_M7_GTIMB2
*\*\     - RCC_APB1_PERIPHEN_M4_GTIMB2
*\*\     - RCC_APB1_PERIPHEN_M7_GTIMB2LP
*\*\     - RCC_APB1_PERIPHEN_M4_GTIMB2LP
*\*\     - RCC_APB1_PERIPHEN_M7_GTIMB3
*\*\     - RCC_APB1_PERIPHEN_M4_GTIMB3
*\*\     - RCC_APB1_PERIPHEN_M7_GTIMB3LP
*\*\     - RCC_APB1_PERIPHEN_M4_GTIMB3LP
*\*\     - RCC_APB1_PERIPHEN_M7_GTIMA4
*\*\     - RCC_APB1_PERIPHEN_M4_GTIMA4
*\*\     - RCC_APB1_PERIPHEN_M7_GTIMA4LP
*\*\     - RCC_APB1_PERIPHEN_M4_GTIMA4LP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAPB1PeriphClk1(uint32_t APB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->APB1EN1 |= APB_periph;
    }
    else
    {
        RCC->APB1EN1 &= ~APB_periph;
    }
}

/**
*\*\name    RCC_EnableAPB1PeriphClk2.
*\*\fun     Enables the APB1 peripheral clock.
*\*\param   APB_periph (APB peripheral to gates its clock):
*\*\     - RCC_APB1_PERIPHEN_M7_GTIMA5
*\*\     - RCC_APB1_PERIPHEN_M4_GTIMA5
*\*\     - RCC_APB1_PERIPHEN_M7_GTIMA5LP
*\*\     - RCC_APB1_PERIPHEN_M4_GTIMA5LP
*\*\     - RCC_APB1_PERIPHEN_M7_GTIMA6
*\*\     - RCC_APB1_PERIPHEN_M4_GTIMA6
*\*\     - RCC_APB1_PERIPHEN_M7_GTIMA6LP
*\*\     - RCC_APB1_PERIPHEN_M4_GTIMA6LP
*\*\     - RCC_APB1_PERIPHEN_M7_GTIMA7
*\*\     - RCC_APB1_PERIPHEN_M4_GTIMA7
*\*\     - RCC_APB1_PERIPHEN_M7_GTIMA7LP
*\*\     - RCC_APB1_PERIPHEN_M4_GTIMA7LP
*\*\     - RCC_APB1_PERIPHEN_M7_SPI3
*\*\     - RCC_APB1_PERIPHEN_M4_SPI3
*\*\     - RCC_APB1_PERIPHEN_M7_SPI3LP
*\*\     - RCC_APB1_PERIPHEN_M4_SPI3LP
*\*\     - RCC_APB1_PERIPHEN_M7_DAC12
*\*\     - RCC_APB1_PERIPHEN_M4_DAC12
*\*\     - RCC_APB1_PERIPHEN_M7_DAC12LP
*\*\     - RCC_APB1_PERIPHEN_M4_DAC12LP
*\*\     - RCC_APB1_PERIPHEN_M7_WWDG2
*\*\     - RCC_APB1_PERIPHEN_M4_WWDG2
*\*\     - RCC_APB1_PERIPHEN_M7_WWDG2LP
*\*\     - RCC_APB1_PERIPHEN_M4_WWDG2LP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAPB1PeriphClk2(uint32_t APB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->APB1EN2 |= APB_periph;
    }
    else
    {
        RCC->APB1EN2 &= ~APB_periph;
    }
}

/**
*\*\name    RCC_EnableAPB1PeriphClk3.
*\*\fun     Enables the APB1 peripheral clock.
*\*\param   APB_periph (APB peripheral to gates its clock):
*\*\     - RCC_APB1_PERIPHEN_M7_USART1
*\*\     - RCC_APB1_PERIPHEN_M4_USART1
*\*\     - RCC_APB1_PERIPHEN_M7_USART1LP
*\*\     - RCC_APB1_PERIPHEN_M4_USART1LP
*\*\     - RCC_APB1_PERIPHEN_M7_USART2
*\*\     - RCC_APB1_PERIPHEN_M4_USART2
*\*\     - RCC_APB1_PERIPHEN_M7_USART2LP
*\*\     - RCC_APB1_PERIPHEN_M4_USART2LP
*\*\     - RCC_APB1_PERIPHEN_M7_USART3
*\*\     - RCC_APB1_PERIPHEN_M4_USART3
*\*\     - RCC_APB1_PERIPHEN_M7_USART3LP
*\*\     - RCC_APB1_PERIPHEN_M4_USART3LP
*\*\     - RCC_APB1_PERIPHEN_M7_USART4
*\*\     - RCC_APB1_PERIPHEN_M4_USART4
*\*\     - RCC_APB1_PERIPHEN_M7_USART4LP
*\*\     - RCC_APB1_PERIPHEN_M4_USART4LP
*\*\     - RCC_APB1_PERIPHEN_M7_UART9
*\*\     - RCC_APB1_PERIPHEN_M4_UART9
*\*\     - RCC_APB1_PERIPHEN_M7_UART9LP
*\*\     - RCC_APB1_PERIPHEN_M4_UART9LP
*\*\     - RCC_APB1_PERIPHEN_M7_UART10
*\*\     - RCC_APB1_PERIPHEN_M4_UART10
*\*\     - RCC_APB1_PERIPHEN_M7_UART10LP
*\*\     - RCC_APB1_PERIPHEN_M4_UART10LP
*\*\     - RCC_APB1_PERIPHEN_M7_UART11
*\*\     - RCC_APB1_PERIPHEN_M4_UART11
*\*\     - RCC_APB1_PERIPHEN_M7_UART11LP
*\*\     - RCC_APB1_PERIPHEN_M4_UART11LP
*\*\     - RCC_APB1_PERIPHEN_M7_UART12
*\*\     - RCC_APB1_PERIPHEN_M4_UART12
*\*\     - RCC_APB1_PERIPHEN_M7_UART12LP
*\*\     - RCC_APB1_PERIPHEN_M4_UART12LP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAPB1PeriphClk3(uint32_t APB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->APB1EN3 |= APB_periph;
    }
    else
    {
        RCC->APB1EN3 &= ~APB_periph;
    }
}

/**
*\*\name    RCC_EnableAPB1PeriphClk4.
*\*\fun     Enables the APB1 peripheral clock.
*\*\param   APB_periph (APB peripheral to gates its clock):
*\*\     - RCC_APB1_PERIPHEN_M7_I2S3
*\*\     - RCC_APB1_PERIPHEN_M4_I2S3
*\*\     - RCC_APB1_PERIPHEN_M7_I2S3LP
*\*\     - RCC_APB1_PERIPHEN_M4_I2S3LP
*\*\     - RCC_APB1_PERIPHEN_M7_I2S4
*\*\     - RCC_APB1_PERIPHEN_M4_I2S4
*\*\     - RCC_APB1_PERIPHEN_M7_I2S4LP
*\*\     - RCC_APB1_PERIPHEN_M4_I2S4LP
*\*\     - RCC_APB1_PERIPHEN_M7_I2C1
*\*\     - RCC_APB1_PERIPHEN_M4_I2C1
*\*\     - RCC_APB1_PERIPHEN_M7_I2C1LP
*\*\     - RCC_APB1_PERIPHEN_M4_I2C1LP
*\*\     - RCC_APB1_PERIPHEN_M7_I2C2
*\*\     - RCC_APB1_PERIPHEN_M4_I2C2
*\*\     - RCC_APB1_PERIPHEN_M7_I2C2LP
*\*\     - RCC_APB1_PERIPHEN_M4_I2C2LP
*\*\     - RCC_APB1_PERIPHEN_M7_I2C3
*\*\     - RCC_APB1_PERIPHEN_M4_I2C3
*\*\     - RCC_APB1_PERIPHEN_M7_I2C3LP
*\*\     - RCC_APB1_PERIPHEN_M4_I2C3LP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAPB1PeriphClk4(uint32_t APB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->APB1EN4 |= APB_periph;
    }
    else
    {
        RCC->APB1EN4 &= ~APB_periph;
    }
}

/**
*\*\name    RCC_EnableAPB1PeriphClk5.
*\*\fun     Enables the APB1 peripheral clock.
*\*\param   APB_periph (APB peripheral to gates its clock):
*\*\     - RCC_APB1_PERIPHEN_M7_FDCAN1
*\*\     - RCC_APB1_PERIPHEN_M4_FDCAN1
*\*\     - RCC_APB1_PERIPHEN_M7_FDCAN1LP
*\*\     - RCC_APB1_PERIPHEN_M4_FDCAN1LP
*\*\     - RCC_APB1_PERIPHEN_M7_FDCAN2
*\*\     - RCC_APB1_PERIPHEN_M4_FDCAN2
*\*\     - RCC_APB1_PERIPHEN_M7_FDCAN2LP
*\*\     - RCC_APB1_PERIPHEN_M4_FDCAN2LP
*\*\     - RCC_APB1_PERIPHEN_M7_FDCAN5
*\*\     - RCC_APB1_PERIPHEN_M4_FDCAN5
*\*\     - RCC_APB1_PERIPHEN_M7_FDCAN5LP
*\*\     - RCC_APB1_PERIPHEN_M4_FDCAN5LP
*\*\     - RCC_APB1_PERIPHEN_M7_FDCAN6
*\*\     - RCC_APB1_PERIPHEN_M4_FDCAN6
*\*\     - RCC_APB1_PERIPHEN_M7_FDCAN6LP
*\*\     - RCC_APB1_PERIPHEN_M4_FDCAN6LP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAPB1PeriphClk5(uint32_t APB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->APB1EN5 |= APB_periph;
    }
    else
    {
        RCC->APB1EN5 &= ~APB_periph;
    }
}

/**
*\*\name    RCC_EnableAHB2PeriphClk1.
*\*\fun     Enables the AHB2 peripheral clock.
*\*\param   AHB_periph (AHB peripheral to gates its clock):
*\*\     - RCC_AHB2_PERIPHEN_M7_USB1
*\*\     - RCC_AHB2_PERIPHEN_M4_USB1
*\*\     - RCC_AHB2_PERIPHEN_M7_USB1LP
*\*\     - RCC_AHB2_PERIPHEN_M4_USB1LP
*\*\     - RCC_AHB2_PERIPHEN_M7_ECCM2
*\*\     - RCC_AHB2_PERIPHEN_M4_ECCM2
*\*\     - RCC_AHB2_PERIPHEN_M7_ECCM2LP
*\*\     - RCC_AHB2_PERIPHEN_M4_ECCM2LP
*\*\     - RCC_AHB2_PERIPHEN_M7_CORDIC
*\*\     - RCC_AHB2_PERIPHEN_M4_CORDIC
*\*\     - RCC_AHB2_PERIPHEN_M7_CORDICLP
*\*\     - RCC_AHB2_PERIPHEN_M4_CORDICLP
*\*\     - RCC_AHB2_PERIPHEN_M7_SDPU
*\*\     - RCC_AHB2_PERIPHEN_M4_SDPU
*\*\     - RCC_AHB2_PERIPHEN_M7_SDPULP
*\*\     - RCC_AHB2_PERIPHEN_M4_SDPULP
*\*\     - RCC_AHB2_PERIPHEN_M7_FMAC
*\*\     - RCC_AHB2_PERIPHEN_M4_FMAC
*\*\     - RCC_AHB2_PERIPHEN_M7_FMACLP
*\*\     - RCC_AHB2_PERIPHEN_M4_FMACLP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAHB2PeriphClk1(uint32_t AHB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->AHB2EN1 |= AHB_periph;
    }
    else
    {
        RCC->AHB2EN1 &= ~AHB_periph;
    }
}

/**
*\*\name    RCC_EnableAHB2PeriphClk2.
*\*\fun     Enables the AHB2 peripheral clock.
*\*\param   AHB_periph (AHB peripheral to gates its clock):
*\*\     - RCC_AHB2_PERIPHEN_M7_DAC56
*\*\     - RCC_AHB2_PERIPHEN_M4_DAC56
*\*\     - RCC_AHB2_PERIPHEN_M7_DAC56LP
*\*\     - RCC_AHB2_PERIPHEN_M4_DAC56LP
*\*\     - RCC_AHB2_PERIPHEN_M7_DAC34
*\*\     - RCC_AHB2_PERIPHEN_M4_DAC34
*\*\     - RCC_AHB2_PERIPHEN_M7_DAC34LP
*\*\     - RCC_AHB2_PERIPHEN_M4_DAC34LP
*\*\     - RCC_AHB2_PERIPHEN_M7_ETH1TX
*\*\     - RCC_AHB2_PERIPHEN_M4_ETH1TX
*\*\     - RCC_AHB2_PERIPHEN_M7_ETH1TXLP
*\*\     - RCC_AHB2_PERIPHEN_M4_ETH1TXLP
*\*\     - RCC_AHB2_PERIPHEN_M7_ETH1RX
*\*\     - RCC_AHB2_PERIPHEN_M4_ETH1RX
*\*\     - RCC_AHB2_PERIPHEN_M7_ETH1RXLP
*\*\     - RCC_AHB2_PERIPHEN_M4_ETH1RXLP
*\*\     - RCC_AHB2_PERIPHEN_M7_ETH1MAC
*\*\     - RCC_AHB2_PERIPHEN_M4_ETH1MAC
*\*\     - RCC_AHB2_PERIPHEN_M7_ETH1MACLP
*\*\     - RCC_AHB2_PERIPHEN_M4_ETH1MACLP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAHB2PeriphClk2(uint32_t AHB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->AHB2EN2 |= AHB_periph;
    }
    else
    {
        RCC->AHB2EN2 &= ~AHB_periph;
    }
}

/**
*\*\name    RCC_EnableAPB2PeriphClk1.
*\*\fun     Enables the APB2 peripheral clock.
*\*\param   APB_periph (APB peripheral to gates its clock):
*\*\     - RCC_APB2_PERIPHEN_M7_ATIM1
*\*\     - RCC_APB2_PERIPHEN_M4_ATIM1
*\*\     - RCC_APB2_PERIPHEN_M7_ATIM1LP
*\*\     - RCC_APB2_PERIPHEN_M4_ATIM1LP
*\*\     - RCC_APB2_PERIPHEN_M7_ATIM2
*\*\     - RCC_APB2_PERIPHEN_M4_ATIM2
*\*\     - RCC_APB2_PERIPHEN_M7_ATIM2LP
*\*\     - RCC_APB2_PERIPHEN_M4_ATIM2LP
*\*\     - RCC_APB2_PERIPHEN_M7_GTIMA1
*\*\     - RCC_APB2_PERIPHEN_M4_GTIMA1
*\*\     - RCC_APB2_PERIPHEN_M7_GTIMA1LP
*\*\     - RCC_APB2_PERIPHEN_M4_GTIMA1LP
*\*\     - RCC_APB2_PERIPHEN_M7_GTIMA2
*\*\     - RCC_APB2_PERIPHEN_M4_GTIMA2
*\*\     - RCC_APB2_PERIPHEN_M7_GTIMA2LP
*\*\     - RCC_APB2_PERIPHEN_M4_GTIMA2LP
*\*\     - RCC_APB2_PERIPHEN_M7_GTIMA3
*\*\     - RCC_APB2_PERIPHEN_M4_GTIMA3
*\*\     - RCC_APB2_PERIPHEN_M7_GTIMA3LP
*\*\     - RCC_APB2_PERIPHEN_M4_GTIMA3LP
*\*\     - RCC_APB2_PERIPHEN_M7_SHRTIM1
*\*\     - RCC_APB2_PERIPHEN_M4_SHRTIM1
*\*\     - RCC_APB2_PERIPHEN_M7_SHRTIM1LP
*\*\     - RCC_APB2_PERIPHEN_M4_SHRTIM1LP
*\*\     - RCC_APB2_PERIPHEN_M7_SHRTIM2
*\*\     - RCC_APB2_PERIPHEN_M4_SHRTIM2
*\*\     - RCC_APB2_PERIPHEN_M7_SHRTIM2LP
*\*\     - RCC_APB2_PERIPHEN_M4_SHRTIM2LP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAPB2PeriphClk1(uint32_t APB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->APB2EN1 |= APB_periph;
    }
    else
    {
        RCC->APB2EN1 &= ~APB_periph;
    }
}

/**
*\*\name    RCC_EnableAPB2PeriphClk2.
*\*\fun     Enables the APB2 peripheral clock.
*\*\param   APB_periph (APB peripheral to gates its clock):
*\*\     - RCC_APB2_PERIPHEN_M7_I2S1
*\*\     - RCC_APB2_PERIPHEN_M4_I2S1
*\*\     - RCC_APB2_PERIPHEN_M7_I2S1LP
*\*\     - RCC_APB2_PERIPHEN_M4_I2S1LP
*\*\     - RCC_APB2_PERIPHEN_M7_I2S2
*\*\     - RCC_APB2_PERIPHEN_M4_I2S2
*\*\     - RCC_APB2_PERIPHEN_M7_I2S2LP
*\*\     - RCC_APB2_PERIPHEN_M4_I2S2LP
*\*\     - RCC_APB2_PERIPHEN_M7_SPI1
*\*\     - RCC_APB2_PERIPHEN_M4_SPI1
*\*\     - RCC_APB2_PERIPHEN_M7_SPI1LP
*\*\     - RCC_APB2_PERIPHEN_M4_SPI1LP
*\*\     - RCC_APB2_PERIPHEN_M7_SPI2
*\*\     - RCC_APB2_PERIPHEN_M4_SPI2
*\*\     - RCC_APB2_PERIPHEN_M7_SPI2LP
*\*\     - RCC_APB2_PERIPHEN_M4_SPI2LP
*\*\     - RCC_APB2_PERIPHEN_M7_DSMU
*\*\     - RCC_APB2_PERIPHEN_M4_DSMU
*\*\     - RCC_APB2_PERIPHEN_M7_DSMULP
*\*\     - RCC_APB2_PERIPHEN_M4_DSMULP
*\*\     - RCC_APB2_PERIPHEN_M7_I2C4
*\*\     - RCC_APB2_PERIPHEN_M4_I2C4
*\*\     - RCC_APB2_PERIPHEN_M7_I2C4LP
*\*\     - RCC_APB2_PERIPHEN_M4_I2C4LP
*\*\     - RCC_APB2_PERIPHEN_M7_I2C5
*\*\     - RCC_APB2_PERIPHEN_M4_I2C5
*\*\     - RCC_APB2_PERIPHEN_M7_I2C5LP
*\*\     - RCC_APB2_PERIPHEN_M4_I2C5LP
*\*\     - RCC_APB2_PERIPHEN_M7_I2C6
*\*\     - RCC_APB2_PERIPHEN_M4_I2C6
*\*\     - RCC_APB2_PERIPHEN_M7_I2C6LP
*\*\     - RCC_APB2_PERIPHEN_M4_I2C6LP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAPB2PeriphClk2(uint32_t APB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->APB2EN2 |= APB_periph;
    }
    else
    {
        RCC->APB2EN2 &= ~APB_periph;
    }
}

/**
*\*\name    RCC_EnableAPB2PeriphClk3.
*\*\fun     Enables the APB2 peripheral clock.
*\*\param   APB_periph (APB peripheral to gates its clock):
*\*\     - RCC_APB2_PERIPHEN_M7_USART5
*\*\     - RCC_APB2_PERIPHEN_M4_USART5
*\*\     - RCC_APB2_PERIPHEN_M7_USART5LP
*\*\     - RCC_APB2_PERIPHEN_M4_USART5LP
*\*\     - RCC_APB2_PERIPHEN_M7_USART6
*\*\     - RCC_APB2_PERIPHEN_M4_USART6
*\*\     - RCC_APB2_PERIPHEN_M7_USART6LP
*\*\     - RCC_APB2_PERIPHEN_M4_USART6LP
*\*\     - RCC_APB2_PERIPHEN_M7_USART7
*\*\     - RCC_APB2_PERIPHEN_M4_USART7
*\*\     - RCC_APB2_PERIPHEN_M7_USART7LP
*\*\     - RCC_APB2_PERIPHEN_M4_USART7LP
*\*\     - RCC_APB2_PERIPHEN_M7_USART8
*\*\     - RCC_APB2_PERIPHEN_M4_USART8
*\*\     - RCC_APB2_PERIPHEN_M7_USART8LP
*\*\     - RCC_APB2_PERIPHEN_M4_USART8LP
*\*\     - RCC_APB2_PERIPHEN_M7_UART13
*\*\     - RCC_APB2_PERIPHEN_M4_UART13
*\*\     - RCC_APB2_PERIPHEN_M7_UART13LP
*\*\     - RCC_APB2_PERIPHEN_M4_UART13LP
*\*\     - RCC_APB2_PERIPHEN_M7_UART14
*\*\     - RCC_APB2_PERIPHEN_M4_UART14
*\*\     - RCC_APB2_PERIPHEN_M7_UART14LP
*\*\     - RCC_APB2_PERIPHEN_M4_UART14LP
*\*\     - RCC_APB2_PERIPHEN_M7_UART15
*\*\     - RCC_APB2_PERIPHEN_M4_UART15
*\*\     - RCC_APB2_PERIPHEN_M7_UART15LP
*\*\     - RCC_APB2_PERIPHEN_M4_UART15LP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAPB2PeriphClk3(uint32_t APB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->APB2EN3 |= APB_periph;
    }
    else
    {
        RCC->APB2EN3 &= ~APB_periph;
    }
}

/**
*\*\name    RCC_EnableAPB2PeriphClk4.
*\*\fun     Enables the APB2 peripheral clock.
*\*\param   APB_periph (APB peripheral to gates its clock):
*\*\     - RCC_APB2_PERIPHEN_M7_FDCAN3
*\*\     - RCC_APB2_PERIPHEN_M4_FDCAN3
*\*\     - RCC_APB2_PERIPHEN_M7_FDCAN3LP
*\*\     - RCC_APB2_PERIPHEN_M4_FDCAN3LP
*\*\     - RCC_APB2_PERIPHEN_M7_FDCAN4
*\*\     - RCC_APB2_PERIPHEN_M4_FDCAN4
*\*\     - RCC_APB2_PERIPHEN_M7_FDCAN4LP
*\*\     - RCC_APB2_PERIPHEN_M4_FDCAN4LP
*\*\     - RCC_APB2_PERIPHEN_M7_FDCAN7
*\*\     - RCC_APB2_PERIPHEN_M4_FDCAN7
*\*\     - RCC_APB2_PERIPHEN_M7_FDCAN7LP
*\*\     - RCC_APB2_PERIPHEN_M4_FDCAN7LP
*\*\     - RCC_APB2_PERIPHEN_M7_FDCAN8
*\*\     - RCC_APB2_PERIPHEN_M4_FDCAN8
*\*\     - RCC_APB2_PERIPHEN_M7_FDCAN8LP
*\*\     - RCC_APB2_PERIPHEN_M4_FDCAN8LP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAPB2PeriphClk4(uint32_t APB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->APB2EN4 |= APB_periph;
    }
    else
    {
        RCC->APB2EN4 &= ~APB_periph;
    }
}

/**
*\*\name    RCC_EnableAHB5PeriphClk1.
*\*\fun     Enables the AHB5 peripheral clock.
*\*\param   AHB_periph (AHB peripheral to gates its clock):
*\*\     - RCC_AHB5_PERIPHEN_M7_GPIOA
*\*\     - RCC_AHB5_PERIPHEN_M4_GPIOA
*\*\     - RCC_AHB5_PERIPHEN_M7_GPIOALP
*\*\     - RCC_AHB5_PERIPHEN_M4_GPIOALP
*\*\     - RCC_AHB5_PERIPHEN_M7_GPIOB
*\*\     - RCC_AHB5_PERIPHEN_M4_GPIOB
*\*\     - RCC_AHB5_PERIPHEN_M7_GPIOBLP
*\*\     - RCC_AHB5_PERIPHEN_M4_GPIOBLP
*\*\     - RCC_AHB5_PERIPHEN_M7_GPIOC
*\*\     - RCC_AHB5_PERIPHEN_M4_GPIOC
*\*\     - RCC_AHB5_PERIPHEN_M7_GPIOCLP
*\*\     - RCC_AHB5_PERIPHEN_M4_GPIOCLP
*\*\     - RCC_AHB5_PERIPHEN_M7_GPIOD
*\*\     - RCC_AHB5_PERIPHEN_M4_GPIOD
*\*\     - RCC_AHB5_PERIPHEN_M7_GPIODLP
*\*\     - RCC_AHB5_PERIPHEN_M4_GPIODLP
*\*\     - RCC_AHB5_PERIPHEN_M7_GPIOE
*\*\     - RCC_AHB5_PERIPHEN_M4_GPIOE
*\*\     - RCC_AHB5_PERIPHEN_M7_GPIOELP
*\*\     - RCC_AHB5_PERIPHEN_M4_GPIOELP
*\*\     - RCC_AHB5_PERIPHEN_M7_GPIOF
*\*\     - RCC_AHB5_PERIPHEN_M4_GPIOF
*\*\     - RCC_AHB5_PERIPHEN_M7_GPIOFLP
*\*\     - RCC_AHB5_PERIPHEN_M4_GPIOFLP
*\*\     - RCC_AHB5_PERIPHEN_M7_GPIOG
*\*\     - RCC_AHB5_PERIPHEN_M4_GPIOG
*\*\     - RCC_AHB5_PERIPHEN_M7_GPIOGLP
*\*\     - RCC_AHB5_PERIPHEN_M4_GPIOGLP
*\*\     - RCC_AHB5_PERIPHEN_M7_GPIOH
*\*\     - RCC_AHB5_PERIPHEN_M4_GPIOH
*\*\     - RCC_AHB5_PERIPHEN_M7_GPIOHLP
*\*\     - RCC_AHB5_PERIPHEN_M4_GPIOHLP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAHB5PeriphClk1(uint32_t AHB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->AHB5EN1 |= AHB_periph;
    }
    else
    {
        RCC->AHB5EN1 &= ~AHB_periph;
    }
}

/**
*\*\name    RCC_EnableAHB5PeriphClk2.
*\*\fun     Enables the AHB5 peripheral clock.
*\*\param   AHB_periph (AHB peripheral to gates its clock):
*\*\     - RCC_AHB5_PERIPHEN_M7_GPIOI
*\*\     - RCC_AHB5_PERIPHEN_M4_GPIOI
*\*\     - RCC_AHB5_PERIPHEN_M7_GPIOILP
*\*\     - RCC_AHB5_PERIPHEN_M4_GPIOILP
*\*\     - RCC_AHB5_PERIPHEN_M7_GPIOJ
*\*\     - RCC_AHB5_PERIPHEN_M4_GPIOJ
*\*\     - RCC_AHB5_PERIPHEN_M7_GPIOJLP
*\*\     - RCC_AHB5_PERIPHEN_M4_GPIOJLP
*\*\     - RCC_AHB5_PERIPHEN_M7_GPIOK
*\*\     - RCC_AHB5_PERIPHEN_M4_GPIOK
*\*\     - RCC_AHB5_PERIPHEN_M7_GPIOKLP
*\*\     - RCC_AHB5_PERIPHEN_M4_GPIOKLP
*\*\     - RCC_AHB5_PERIPHEN_M7_ECCM3
*\*\     - RCC_AHB5_PERIPHEN_M4_ECCM3
*\*\     - RCC_AHB5_PERIPHEN_M7_ECCM3LP
*\*\     - RCC_AHB5_PERIPHEN_M4_ECCM3LP
*\*\     - RCC_AHB5_PERIPHEN_PWR
*\*\     - RCC_AHB5_PERIPHEN_PWRLP
*\*\     - RCC_AHB5_PERIPHEN_M7_CRC
*\*\     - RCC_AHB5_PERIPHEN_M4_CRC
*\*\     - RCC_AHB5_PERIPHEN_M7_CRCLP
*\*\     - RCC_AHB5_PERIPHEN_M4_CRCLP
*\*\     - RCC_AHB5_PERIPHEN_M7_SEMA4
*\*\     - RCC_AHB5_PERIPHEN_M4_SEMA4
*\*\     - RCC_AHB5_PERIPHEN_M7_SEMA4LP
*\*\     - RCC_AHB5_PERIPHEN_M4_SEMA4LP
*\*\     - RCC_AHB5_PERIPHEN_M7_AFIO
*\*\     - RCC_AHB5_PERIPHEN_M4_AFIO
*\*\     - RCC_AHB5_PERIPHEN_M7_AFIOLP
*\*\     - RCC_AHB5_PERIPHEN_M4_AFIOLP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAHB5PeriphClk2(uint32_t AHB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->AHB5EN2 |= AHB_periph;
    }
    else
    {
        RCC->AHB5EN2 &= ~AHB_periph;
    }
}

/**
*\*\name    RCC_EnableAPB5PeriphClk1.
*\*\fun     Enables the APB5 peripheral clock.
*\*\param   APB_periph (APB peripheral to gates its clock):
*\*\     - RCC_APB5_PERIPHEN_M7_ATIM3
*\*\     - RCC_APB5_PERIPHEN_M4_ATIM3
*\*\     - RCC_APB5_PERIPHEN_M7_ATIM3LP
*\*\     - RCC_APB5_PERIPHEN_M4_ATIM3LP
*\*\     - RCC_APB5_PERIPHEN_M7_ATIM4
*\*\     - RCC_APB5_PERIPHEN_M4_ATIM4
*\*\     - RCC_APB5_PERIPHEN_M7_ATIM4LP
*\*\     - RCC_APB5_PERIPHEN_M4_ATIM4LP
*\*\     - RCC_APB5_PERIPHEN_M7_AFEC
*\*\     - RCC_APB5_PERIPHEN_M4_AFEC
*\*\     - RCC_APB5_PERIPHEN_M7_AFECLP
*\*\     - RCC_APB5_PERIPHEN_M4_AFECLP
*\*\     - RCC_APB5_PERIPHEN_M7_SPI4
*\*\     - RCC_APB5_PERIPHEN_M4_SPI4
*\*\     - RCC_APB5_PERIPHEN_M7_SPI4LP
*\*\     - RCC_APB5_PERIPHEN_M4_SPI4LP
*\*\     - RCC_APB5_PERIPHEN_M7_SPI5
*\*\     - RCC_APB5_PERIPHEN_M4_SPI5
*\*\     - RCC_APB5_PERIPHEN_M7_SPI5LP
*\*\     - RCC_APB5_PERIPHEN_M4_SPI5LP
*\*\     - RCC_APB5_PERIPHEN_M7_SPI6
*\*\     - RCC_APB5_PERIPHEN_M4_SPI6
*\*\     - RCC_APB5_PERIPHEN_M7_SPI6LP
*\*\     - RCC_APB5_PERIPHEN_M4_SPI6LP
*\*\     - RCC_APB5_PERIPHEN_M7_SPI7
*\*\     - RCC_APB5_PERIPHEN_M4_SPI7
*\*\     - RCC_APB5_PERIPHEN_M7_SPI7LP
*\*\     - RCC_APB5_PERIPHEN_M4_SPI7LP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAPB5PeriphClk1(uint32_t APB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->APB5EN1 |= APB_periph;
    }
    else
    {
        RCC->APB5EN1 &= ~APB_periph;
    }
}

/**
*\*\name    RCC_EnableAPB5PeriphClk2.
*\*\fun     Enables the APB5 peripheral clock.
*\*\param   APB_periph (APB peripheral to gates its clock):
*\*\     - RCC_APB5_PERIPHEN_M7_I2C7
*\*\     - RCC_APB5_PERIPHEN_M4_I2C7
*\*\     - RCC_APB5_PERIPHEN_M7_I2C7LP
*\*\     - RCC_APB5_PERIPHEN_M4_I2C7LP
*\*\     - RCC_APB5_PERIPHEN_M7_I2C8
*\*\     - RCC_APB5_PERIPHEN_M4_I2C8
*\*\     - RCC_APB5_PERIPHEN_M7_I2C8LP
*\*\     - RCC_APB5_PERIPHEN_M4_I2C8LP
*\*\     - RCC_APB5_PERIPHEN_M7_I2C9
*\*\     - RCC_APB5_PERIPHEN_M4_I2C9
*\*\     - RCC_APB5_PERIPHEN_M7_I2C9LP
*\*\     - RCC_APB5_PERIPHEN_M4_I2C9LP
*\*\     - RCC_APB5_PERIPHEN_M7_I2C10
*\*\     - RCC_APB5_PERIPHEN_M4_I2C10
*\*\     - RCC_APB5_PERIPHEN_M7_I2C10LP
*\*\     - RCC_APB5_PERIPHEN_M4_I2C10LP
*\*\     - RCC_APB5_PERIPHEN_EXTI
*\*\     - RCC_APB5_PERIPHEN_EXTILP
*\*\     - RCC_APB5_PERIPHEN_M7_RTCPCLK
*\*\     - RCC_APB5_PERIPHEN_M4_RTCPCLK
*\*\     - RCC_APB5_PERIPHEN_M7_RTCPCLKLP
*\*\     - RCC_APB5_PERIPHEN_M4_RTCPCLKLP
*\*\     - RCC_APB5_PERIPHEN_IWDG1PCLK
*\*\     - RCC_APB5_PERIPHEN_IWDG1PCLKLP
*\*\     - RCC_APB5_PERIPHEN_IWDG2PCLK
*\*\     - RCC_APB5_PERIPHEN_IWDG2PCLKLP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAPB5PeriphClk2(uint32_t APB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->APB5EN2 |= APB_periph;
    }
    else
    {
        RCC->APB5EN2 &= ~APB_periph;
    }
}

/**
*\*\name    RCC_EnableAHB9PeriphClk1.
*\*\fun     Enables the AHB9 peripheral clock.
*\*\param   AHB_periph (AHB peripheral to gates its clock):
*\*\     - RCC_AHB9_PERIPHEN_M7_ESC
*\*\     - RCC_AHB9_PERIPHEN_M4_ESC
*\*\     - RCC_AHB9_PERIPHEN_M7_ESCLP
*\*\     - RCC_AHB9_PERIPHEN_M4_ESCLP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAHB9PeriphClk1(uint32_t AHB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->AHB9EN1 |= AHB_periph;
    }
    else
    {
        RCC->AHB9EN1 &= ~AHB_periph;
    }
}

/**
*\*\name    RCC_EnableRDPeriphClk1.
*\*\fun     Enables the Retention domain peripheral clock.
*\*\param   RD_periph (RD peripheral to gates its clock):
*\*\     - RCC_RD_PERIPHEN_M7_LPTIM1
*\*\     - RCC_RD_PERIPHEN_M4_LPTIM1
*\*\     - RCC_RD_PERIPHEN_M7_LPTIM1LP
*\*\     - RCC_RD_PERIPHEN_M4_LPTIM1LP
*\*\     - RCC_RD_PERIPHEN_M7_LPTIM2
*\*\     - RCC_RD_PERIPHEN_M4_LPTIM2
*\*\     - RCC_RD_PERIPHEN_M7_LPTIM2LP
*\*\     - RCC_RD_PERIPHEN_M4_LPTIM2LP
*\*\     - RCC_RD_PERIPHEN_M7_LPTIM3
*\*\     - RCC_RD_PERIPHEN_M4_LPTIM3
*\*\     - RCC_RD_PERIPHEN_M7_LPTIM3LP
*\*\     - RCC_RD_PERIPHEN_M4_LPTIM3LP
*\*\     - RCC_RD_PERIPHEN_M7_LPTIM4
*\*\     - RCC_RD_PERIPHEN_M4_LPTIM4
*\*\     - RCC_RD_PERIPHEN_M7_LPTIM4LP
*\*\     - RCC_RD_PERIPHEN_M4_LPTIM4LP
*\*\     - RCC_RD_PERIPHEN_M7_LPTIM5
*\*\     - RCC_RD_PERIPHEN_M4_LPTIM5
*\*\     - RCC_RD_PERIPHEN_M7_LPTIM5LP
*\*\     - RCC_RD_PERIPHEN_M4_LPTIM5LP
*\*\     - RCC_RD_PERIPHEN_M7_LPUART1
*\*\     - RCC_RD_PERIPHEN_M4_LPUART1
*\*\     - RCC_RD_PERIPHEN_M7_LPUART1LP
*\*\     - RCC_RD_PERIPHEN_M4_LPUART1LP
*\*\     - RCC_RD_PERIPHEN_M7_LPUART2
*\*\     - RCC_RD_PERIPHEN_M4_LPUART2
*\*\     - RCC_RD_PERIPHEN_M7_LPUART2LP
*\*\     - RCC_RD_PERIPHEN_M4_LPUART2LP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableRDPeriphClk1(uint32_t RD_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->RDEN1 |= RD_periph;
    }
    else
    {
        RCC->RDEN1 &= ~RD_periph;
    }
}

/**
*\*\name    RCC_EnableRDPeriphClk2.
*\*\fun     Enables the Retention domain peripheral clock.
*\*\param   RD_periph (RD peripheral to gates its clock):
*\*\     - RCC_RD_PERIPHEN_M7_COMP
*\*\     - RCC_RD_PERIPHEN_M4_COMP
*\*\     - RCC_RD_PERIPHEN_M7_COMPLP
*\*\     - RCC_RD_PERIPHEN_M4_COMPLP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableRDPeriphClk2(uint32_t RD_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->RDEN2 |= RD_periph;
    }
    else
    {
        RCC->RDEN2 &= ~RD_periph;
    }
}

/**
*\*\name    RCC_EnableAXIPeriphClk1.
*\*\fun     Enables the AXI peripheral clock.
*\*\param   AXI_periph (AXI peripheral to gates its clock):
*\*\     - RCC_AXI_PERIPHEN_M7_JPEGD
*\*\     - RCC_AXI_PERIPHEN_M4_JPEGD
*\*\     - RCC_AXI_PERIPHEN_M7_JPEGDLP
*\*\     - RCC_AXI_PERIPHEN_M4_JPEGDLP
*\*\     - RCC_AXI_PERIPHEN_M7_JPEGE
*\*\     - RCC_AXI_PERIPHEN_M4_JPEGE
*\*\     - RCC_AXI_PERIPHEN_M7_JPEGELP
*\*\     - RCC_AXI_PERIPHEN_M4_JPEGELP
*\*\     - RCC_AXI_PERIPHEN_M7_DMAMUX2
*\*\     - RCC_AXI_PERIPHEN_M4_DMAMUX2
*\*\     - RCC_AXI_PERIPHEN_M7_DMAMUX2LP
*\*\     - RCC_AXI_PERIPHEN_M4_DMAMUX2LP
*\*\     - RCC_AXI_PERIPHEN_M7_MDMA
*\*\     - RCC_AXI_PERIPHEN_M4_MDMA
*\*\     - RCC_AXI_PERIPHEN_M7_MDMALP
*\*\     - RCC_AXI_PERIPHEN_M4_MDMALP
*\*\     - RCC_AXI_PERIPHEN_M7_SDMMC1
*\*\     - RCC_AXI_PERIPHEN_M4_SDMMC1
*\*\     - RCC_AXI_PERIPHEN_M7_SDMMC1LP
*\*\     - RCC_AXI_PERIPHEN_M4_SDMMC1LP
*\*\     - RCC_AXI_PERIPHEN_M7_ECCM1
*\*\     - RCC_AXI_PERIPHEN_M4_ECCM1
*\*\     - RCC_AXI_PERIPHEN_M7_ECCM1LP
*\*\     - RCC_AXI_PERIPHEN_M4_ECCM1LP
*\*\     - RCC_AXI_PERIPHEN_M7_OTPC
*\*\     - RCC_AXI_PERIPHEN_M4_OTPC
*\*\     - RCC_AXI_PERIPHEN_M7_OTPCLP
*\*\     - RCC_AXI_PERIPHEN_M4_OTPCLP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAXIPeriphClk1(uint32_t AXI_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->AXIEN1 |= AXI_periph;
    }
    else
    {
        RCC->AXIEN1 &= ~AXI_periph;
    }
}

/**
*\*\name    RCC_EnableAXIPeriphClk2.
*\*\fun     Enables the AXI peripheral clock.
*\*\param   AXI_periph (AXI peripheral to gates its clock):
*\*\     - RCC_AXI_PERIPHEN_M7_DSI
*\*\     - RCC_AXI_PERIPHEN_M4_DSI
*\*\     - RCC_AXI_PERIPHEN_M7_DSILP
*\*\     - RCC_AXI_PERIPHEN_M4_DSILP
*\*\     - RCC_AXI_PERIPHEN_M7_LCDC
*\*\     - RCC_AXI_PERIPHEN_M4_LCDC
*\*\     - RCC_AXI_PERIPHEN_M7_LCDCLP
*\*\     - RCC_AXI_PERIPHEN_M4_LCDCLP
*\*\     - RCC_AXI_PERIPHEN_M7_LCDCAPB
*\*\     - RCC_AXI_PERIPHEN_M4_LCDCAPB
*\*\     - RCC_AXI_PERIPHEN_M7_LCDCAPBLP
*\*\     - RCC_AXI_PERIPHEN_M4_LCDCAPBLP
*\*\     - RCC_AXI_PERIPHEN_M7_DVP1
*\*\     - RCC_AXI_PERIPHEN_M4_DVP1
*\*\     - RCC_AXI_PERIPHEN_M7_DVP1LP
*\*\     - RCC_AXI_PERIPHEN_M4_DVP1LP
*\*\     - RCC_AXI_PERIPHEN_M7_DVP1APB
*\*\     - RCC_AXI_PERIPHEN_M4_DVP1APB
*\*\     - RCC_AXI_PERIPHEN_M7_DVP1APBLP
*\*\     - RCC_AXI_PERIPHEN_M4_DVP1APBLP
*\*\     - RCC_AXI_PERIPHEN_M7_DVP2
*\*\     - RCC_AXI_PERIPHEN_M4_DVP2
*\*\     - RCC_AXI_PERIPHEN_M7_DVP2LP
*\*\     - RCC_AXI_PERIPHEN_M4_DVP2LP
*\*\     - RCC_AXI_PERIPHEN_M7_DVP2APB
*\*\     - RCC_AXI_PERIPHEN_M4_DVP2APB
*\*\     - RCC_AXI_PERIPHEN_M7_DVP2APBLP
*\*\     - RCC_AXI_PERIPHEN_M4_DVP2APBLP
*\*\     - RCC_AXI_PERIPHEN_M7_WWDG1
*\*\     - RCC_AXI_PERIPHEN_M4_WWDG1
*\*\     - RCC_AXI_PERIPHEN_M7_WWDG1LP
*\*\     - RCC_AXI_PERIPHEN_M4_WWDG1LP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAXIPeriphClk2(uint32_t AXI_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->AXIEN2 |= AXI_periph;
    }
    else
    {
        RCC->AXIEN2 &= ~AXI_periph;
    }
}


/**
*\*\name    RCC_EnableAXIPeriphClk3.
*\*\fun     Enables the AXI peripheral clock.
*\*\param   AXI_periph (AXI peripheral to gates its clock):
*\*\     - RCC_AXI_PERIPHEN_M7_TASRAM2
*\*\     - RCC_AXI_PERIPHEN_M4_TASRAM2
*\*\     - RCC_AXI_PERIPHEN_M7_TASRAM2LP
*\*\     - RCC_AXI_PERIPHEN_M4_TASRAM2LP
*\*\     - RCC_AXI_PERIPHEN_M7_TASRAM3
*\*\     - RCC_AXI_PERIPHEN_M4_TASRAM3
*\*\     - RCC_AXI_PERIPHEN_M7_TASRAM3LP
*\*\     - RCC_AXI_PERIPHEN_M4_TASRAM3LP
*\*\     - RCC_AXI_PERIPHEN_M7_TCM
*\*\     - RCC_AXI_PERIPHEN_M4_TCM
*\*\     - RCC_AXI_PERIPHEN_M7_TCMLP
*\*\     - RCC_AXI_PERIPHEN_M4_TCMLP
*\*\     - RCC_AXI_PERIPHEN_M7_TCMAXI
*\*\     - RCC_AXI_PERIPHEN_M4_TCMAXI
*\*\     - RCC_AXI_PERIPHEN_M7_TCMAXILP
*\*\     - RCC_AXI_PERIPHEN_M4_TCMAXILP
*\*\     - RCC_AXI_PERIPHEN_M7_TCMAPB
*\*\     - RCC_AXI_PERIPHEN_M4_TCMAPB
*\*\     - RCC_AXI_PERIPHEN_M7_TCMAPBLP
*\*\     - RCC_AXI_PERIPHEN_M4_TCMAPBLP
*\*\     - RCC_AXI_PERIPHEN_M7_ASRAM1
*\*\     - RCC_AXI_PERIPHEN_M4_ASRAM1
*\*\     - RCC_AXI_PERIPHEN_M7_ASRAM1LP
*\*\     - RCC_AXI_PERIPHEN_M4_ASRAM1LP
*\*\     - RCC_AXI_PERIPHEN_M7_AXIROM
*\*\     - RCC_AXI_PERIPHEN_M4_AXIROM
*\*\     - RCC_AXI_PERIPHEN_M7_AXIROMLP
*\*\     - RCC_AXI_PERIPHEN_M4_AXIROMLP
*\*\     - RCC_AXI_PERIPHEN_M7_GPU
*\*\     - RCC_AXI_PERIPHEN_M4_GPU
*\*\     - RCC_AXI_PERIPHEN_M7_GPULP
*\*\     - RCC_AXI_PERIPHEN_M4_GPULP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAXIPeriphClk3(uint32_t AXI_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->AXIEN3 |= AXI_periph;
    }
    else
    {
        RCC->AXIEN3 &= ~AXI_periph;
    }
}

/**
*\*\name    RCC_EnableAXIPeriphClk4.
*\*\fun     Enables the AXI peripheral clock.
*\*\param   AXI_periph (AXI peripheral to gates its clock):
*\*\     - RCC_AXI_PERIPHEN_M7_XSPI1
*\*\     - RCC_AXI_PERIPHEN_M4_XSPI1
*\*\     - RCC_AXI_PERIPHEN_M7_XSPI1LP
*\*\     - RCC_AXI_PERIPHEN_M4_XSPI1LP
*\*\     - RCC_AXI_PERIPHEN_M7_XSPI2
*\*\     - RCC_AXI_PERIPHEN_M4_XSPI2
*\*\     - RCC_AXI_PERIPHEN_M7_XSPI2LP
*\*\     - RCC_AXI_PERIPHEN_M4_XSPI2LP
*\*\     - RCC_AXI_PERIPHEN_M7_FEMC
*\*\     - RCC_AXI_PERIPHEN_M4_FEMC
*\*\     - RCC_AXI_PERIPHEN_M7_FEMCLP
*\*\     - RCC_AXI_PERIPHEN_M4_FEMCLP
*\*\     - RCC_AXI_PERIPHEN_M7_SDRAM
*\*\     - RCC_AXI_PERIPHEN_M4_SDRAM
*\*\     - RCC_AXI_PERIPHEN_M7_SDRAMLP
*\*\     - RCC_AXI_PERIPHEN_M4_SDRAMLP
*\*\     - RCC_AXI_PERIPHEN_M7_DSIULPS
*\*\     - RCC_AXI_PERIPHEN_M4_DSIULPS
*\*\     - RCC_AXI_PERIPHEN_M7_DSIULPSLP
*\*\     - RCC_AXI_PERIPHEN_M4_DSIULPSLP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableAXIPeriphClk4(uint32_t AXI_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->AXIEN4 |= AXI_periph;
    }
    else
    {
        RCC->AXIEN4 &= ~AXI_periph;
    }
}

/**
*\*\name    RCC_ConfigETH2PtpClk.
*\*\fun     Config the Ethernet2 PTP clock.
*\*\param   CLK_source(Ethernet2 PTP clock source):
*\*\       - RCC_ETHPTPCLK_SRC_SYSBUSDIV
*\*\       - RCC_ETHPTPCLK_SRC_PERIPH
*\*\       - RCC_ETHPTPCLK_SRC_PLL2C
*\*\       - RCC_ETHPTPCLK_SRC_PLL3A
*\*\param   CLK_divider(Ethernet2 PTP clock source (sys_bus_div_clk) divider)
*\*\       - RCC_ETHPTPCLK_SYSBUSDIV1
*\*\       - RCC_ETHPTPCLK_SYSBUSDIV2
*\*\       - RCC_ETHPTPCLK_SYSBUSDIV4
*\*\       - RCC_ETHPTPCLK_SYSBUSDIV8
*\*\       - RCC_ETHPTPCLK_SYSBUSDIV16
*\*\       - RCC_ETHPTPCLK_SYSBUSDIV32
*\*\       - RCC_ETHPTPCLK_SYSBUSDIV64
*\*\       - RCC_ETHPTPCLK_SYSBUSDIV128
*\*\       - RCC_ETHPTPCLK_SYSBUSDIV256
*\*\       - RCC_ETHPTPCLK_SYSBUSDIV512
*\*\return  none
*\*\note  if select RCC_ETHPTPCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by ETH2SYSDIV[3:0]
**/
void RCC_ConfigETH2PtpClk(uint32_t CLK_source, uint32_t CLK_divider)
{
    uint32_t reg_value;
    uint32_t reg_value1;

    reg_value = RCC->AHB1SEL1;
    /* Clear ETH2PTPSEL[1:0] bits */
    reg_value &= RCC_ETHPTPCLK_SRC_MASK;
    /* Set ETH2PTPSEL[1:0] bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->AHB1SEL1 = reg_value;

    if(CLK_source == RCC_ETHPTPCLK_SRC_SYSBUSDIV)
    {
        reg_value1 = RCC->AHB1DIV1;
        /* Clear ETH2SYSDIV[3:0] bits */
        reg_value1 &=  RCC_ETHPTPCLK_SYSBUSDIV_MASK;
        /* Set the ETH2SYSDIV[3:0] bits */
        reg_value1 |=  CLK_divider;
        /* Store the new value */
        RCC->AHB1DIV1 = reg_value1;
    }

}

/**
*\*\name    RCC_ConfigETH1PtpClk.
*\*\fun     Config the Ethernet1 PTP clock.
*\*\param   CLK_source(Ethernet1 PTP clock source):
*\*\       - RCC_ETHPTPCLK_SRC_SYSBUSDIV
*\*\       - RCC_ETHPTPCLK_SRC_PERIPH
*\*\       - RCC_ETHPTPCLK_SRC_PLL2C
*\*\       - RCC_ETHPTPCLK_SRC_PLL3A
*\*\param   CLK_divider(Ethernet1 PTP clock source (sys_bus_div_clk) divider)
*\*\       - RCC_ETHPTPCLK_SYSBUSDIV1
*\*\       - RCC_ETHPTPCLK_SYSBUSDIV2
*\*\       - RCC_ETHPTPCLK_SYSBUSDIV4
*\*\       - RCC_ETHPTPCLK_SYSBUSDIV8
*\*\       - RCC_ETHPTPCLK_SYSBUSDIV16
*\*\       - RCC_ETHPTPCLK_SYSBUSDIV32
*\*\       - RCC_ETHPTPCLK_SYSBUSDIV64
*\*\       - RCC_ETHPTPCLK_SYSBUSDIV128
*\*\       - RCC_ETHPTPCLK_SYSBUSDIV256
*\*\       - RCC_ETHPTPCLK_SYSBUSDIV512
*\*\return  none
*\*\note  if select RCC_ETHPTPCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by ETH1SYSDIV[3:0]
**/
void RCC_ConfigETH1PtpClk(uint32_t CLK_source, uint32_t CLK_divider)
{
    uint32_t reg_value;
    uint32_t reg_value1;

    reg_value = RCC->AHB2SEL1;
    /* Clear ETH1PTPSEL[1:0] bits */
    reg_value &= RCC_ETHPTPCLK_SRC_MASK;
    /* Set ETH1PTPSEL[1:0] bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->AHB2SEL1 = reg_value;

    if(CLK_source == RCC_ETHPTPCLK_SRC_SYSBUSDIV)
    {
        reg_value1 = RCC->AHB2DIV1;
        /* Clear ETH1SYSDIV[3:0] bits */
        reg_value1 &=  RCC_ETHPTPCLK_SYSBUSDIV_MASK;
        /* Set the ETH1SYSDIV[3:0] bits */
        reg_value1 |=  CLK_divider;
        /* Store the new value */
        RCC->AHB2DIV1 = reg_value1;
    }

}

/**
*\*\name    RCC_ConfigETH1GMIITXClk.
*\*\fun     Configures ETH1 125 MHz GMII TX clock source.
*\*\param   CLK_source:
*\*\         - RCC_ETH1GMIITXCLK_SRC_PLL3A
*\*\         - RCC_ETH1GMIITXCLK_SRC_PLL2B
*\*\         - RCC_ETH1GMIITXCLK_SRC_IOM
*\*\         - RCC_ETH1GMIITXCLK_SRC_PLL1C
*\*\return  none
**/
void RCC_ConfigETH1GMIITXClk(uint32_t CLK_source)
{
    uint32_t temp_value;

    temp_value = RCC->AHB2SEL1;

    /* Clear ETH1GMIITXSEL[1:0] bits */
    temp_value &= RCC_ETH1GMIITXCLK_SRC_MASK;
    /* Set ETH1GMIITXSEL[1:0] bits according to CLK_source value*/
    temp_value |= CLK_source;

    /* Store the new value */
    RCC->AHB2SEL1 = temp_value;

}

/**
*\*\name    RCC_ConfigSDMMC2KerClk.
*\*\fun     Config the SDMMC2 kernel clock.
*\*\param   CLK_source(SDMMC2 kernel clock source):
*\*\       - RCC_SDMMC2KERCLK_SRC_SYSBUSDIV
*\*\       - RCC_SDMMC2KERCLK_SRC_PERIPH
*\*\       - RCC_SDMMC2KERCLK_SRC_PLL2A
*\*\       - RCC_SDMMC2KERCLK_SRC_PLL3A
*\*\       - RCC_SDMMC2KERCLK_SRC_PLL1B
*\*\param   CLK_divider(SDMMC2 kernel clock source (sys_bus_div_clk) divider)
*\*\       - RCC_SDMMC2KERCLK_SYSBUSDIV1
*\*\       - RCC_SDMMC2KERCLK_SYSBUSDIV2
*\*\       - RCC_SDMMC2KERCLK_SYSBUSDIV4
*\*\       - RCC_SDMMC2KERCLK_SYSBUSDIV8
*\*\       - RCC_SDMMC2KERCLK_SYSBUSDIV16
*\*\       - RCC_SDMMC2KERCLK_SYSBUSDIV32
*\*\       - RCC_SDMMC2KERCLK_SYSBUSDIV64
*\*\       - RCC_SDMMC2KERCLK_SYSBUSDIV128
*\*\       - RCC_SDMMC2KERCLK_SYSBUSDIV256
*\*\       - RCC_SDMMC2KERCLK_SYSBUSDIV512
*\*\return  none
*\*\note  if select RCC_SDMMC2KERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by SDMMC2SYSDIV[3:0]
**/
void RCC_ConfigSDMMC2KerClk(uint32_t CLK_source, uint32_t CLK_divider)
{
    uint32_t reg_value;
    uint32_t reg_value1;

    reg_value = RCC->AHB1SEL1;
    /* Clear SDMMC2KERSEL[2:0] bits */
    reg_value &= RCC_SDMMC2KERCLK_SRC_MASK;
    /* Set SDMMC2KERSEL[2:0] bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->AHB1SEL1 = reg_value;

    if(CLK_source == RCC_SDMMC2KERCLK_SRC_SYSBUSDIV)
    {
        reg_value1 = RCC->AHB1DIV1;
        /* Clear SDMMC2SYSDIV[3:0] bits */
        reg_value1 &=  RCC_SDMMC2KERCLK_SYSBUSDIV_MASK;
        /* Set the SDMMC2SYSDIV[3:0] bits */
        reg_value1 |=  CLK_divider;
        /* Store the new value */
        RCC->AHB1DIV1 = reg_value1;
    }

}

/**
*\*\name    RCC_ConfigSDMMC1KerClk.
*\*\fun     Config the SDMMC1 kernel clock.
*\*\param   CLK_source(SDMMC1 kernel clock source):
*\*\       - RCC_SDMMC1KERCLK_SRC_AXIDIV
*\*\       - RCC_SDMMC1KERCLK_SRC_PERIPH
*\*\       - RCC_SDMMC1KERCLK_SRC_PLL2A
*\*\       - RCC_SDMMC1KERCLK_SRC_PLL3A
*\*\       - RCC_SDMMC1KERCLK_SRC_PLL1B
*\*\param   CLK_divider(SDMMC1 kernel clock source (axi_bus_clk) divider)
*\*\       - RCC_SDMMC1KERCLK_AXIDIV1
*\*\       - RCC_SDMMC1KERCLK_AXIDIV2
*\*\       - RCC_SDMMC1KERCLK_AXIDIV4
*\*\       - RCC_SDMMC1KERCLK_AXIDIV8
*\*\       - RCC_SDMMC1KERCLK_AXIDIV16
*\*\       - RCC_SDMMC1KERCLK_AXIDIV32
*\*\       - RCC_SDMMC1KERCLK_AXIDIV64
*\*\       - RCC_SDMMC1KERCLK_AXIDIV128
*\*\       - RCC_SDMMC1KERCLK_AXIDIV256
*\*\       - RCC_SDMMC1KERCLK_AXIDIV512
*\*\return  none
*\*\note  if select RCC_SDMMC1KERCLK_SRC_AXIDIV then set the AXI clock divider by SDMMC1AXIDIV[3:0]
**/
void RCC_ConfigSDMMC1KerClk(uint32_t CLK_source, uint32_t CLK_divider)
{
    uint32_t reg_value;
    uint32_t reg_value1;

    reg_value = RCC->AXISEL1;
    /* Clear SDMMC1KERSEL[2:0] bits */
    reg_value &= RCC_SDMMC1KERCLK_SRC_MASK;
    /* Set SDMMC1KERSEL[2:0] bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->AXISEL1 = reg_value;

    if(CLK_source == RCC_SDMMC1KERCLK_SRC_AXIDIV)
    {
        reg_value1 = RCC->AXIDIV1;
        /* Clear SDMMC1AXIDIV[3:0] bits */
        reg_value1 &=  RCC_SDMMC1KERCLK_AXIDIV_MASK;
        /* Set the SDMMC1AXIDIV[3:0] bits */
        reg_value1 |=  CLK_divider;
        /* Store the new value */
        RCC->AXIDIV1 = reg_value1;
    }

}

/**
*\*\name    RCC_ConfigDSMUKerClk.
*\*\fun     Config the DSMU kernel clock.
*\*\param   CLK_source(DSMU kernel clock source):
*\*\       - RCC_DSMUKERCLK_SRC_APB2
*\*\       - RCC_DSMUKERCLK_SRC_SYSBUSDIV
*\*\param   CLK_divider(DSMU kernel clock source (sys_bus_div_clk) divider)
*\*\       - RCC_DSMUKERCLK_SYSBUSDIV1
*\*\       - RCC_DSMUKERCLK_SYSBUSDIV2
*\*\       - RCC_DSMUKERCLK_SYSBUSDIV4
*\*\       - RCC_DSMUKERCLK_SYSBUSDIV8
*\*\       - RCC_DSMUKERCLK_SYSBUSDIV16
*\*\return  none
*\*\note  if select RCC_DSMUKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB2DSMUDIV[2:0]
**/
void RCC_ConfigDSMUKerClk(uint32_t CLK_source, uint32_t CLK_divider)
{
    uint32_t reg_value;
    uint32_t reg_value1;

    reg_value = RCC->APB2SEL1;
    /* Clear DSMUKERSEL bits */
    reg_value &= RCC_DSMUKERCLK_SRC_MASK;
    /* Set DSMUKERSEL bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->APB2SEL1 = reg_value;

    if(CLK_source == RCC_DSMUKERCLK_SRC_SYSBUSDIV)
    {
        reg_value1 = RCC->APB2DIV1;
        /* Clear APB2DSMUDIV[2:0] bits */
        reg_value1 &=  RCC_DSMUKERCLK_SYSBUSDIV_MASK;
        /* Set the APB2DSMUDIV[2:0] bits */
        reg_value1 |=  CLK_divider;
        /* Store the new value */
        RCC->APB2DIV1 = reg_value1;
    }

}

/**
*\*\name    RCC_ConfigDSMUKerAClk.
*\*\fun     Config the DSMU kernel A clock.
*\*\param   CLK_source(DSMU kernel A clock source):
*\*\       - RCC_DSMUKERACLK_SRC_APB2
*\*\       - RCC_DSMUKERACLK_SRC_PLL1B
*\*\       - RCC_DSMUKERACLK_SRC_PLL2B
*\*\       - RCC_DSMUKERACLK_SRC_PLL3A
*\*\       - RCC_DSMUKERACLK_SRC_CKIN
*\*\       - RCC_DSMUKERACLK_SRC_PERIPH
*\*\param   CLK_pinsel(DSMU kernel A clock source CKIN pin select)
*\*\       - RCC_DSMUKERACLK_CKIN_I2S1
*\*\       - RCC_DSMUKERACLK_CKIN_I2S2
*\*\       - RCC_DSMUKERACLK_CKIN_I2S3
*\*\       - RCC_DSMUKERACLK_CKIN_I2S4
*\*\return  none
*\*\note  if select RCC_DSMUKERACLK_SRC_CKIN then set the I2S CKIN pin by I2SSEL[1:0]
**/
void RCC_ConfigDSMUKerAClk(uint32_t CLK_source, uint32_t CLK_pinsel)
{
    uint32_t reg_value;
    uint32_t reg_value1;

    reg_value = RCC->APB2SEL1;
    /* Clear DSMUKERASEL[2:0] bits */
    reg_value &= RCC_DSMUKERACLK_SRC_MASK;
    /* Set DSMUKERASEL[2:0] bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->APB2SEL1 = reg_value;

    if(CLK_source == RCC_DSMUKERACLK_SRC_CKIN)
    {
        reg_value1 = RCC->CFG3;
        /* Clear I2SSEL[1:0] bits */
        reg_value1 &=  RCC_DSMUKERACLK_CKIN_MASK;
        /* Set the I2SSEL[1:0] bits */
        reg_value1 |=  CLK_pinsel;
        /* Store the new value */
        RCC->CFG3 = reg_value1;
    }

}

/**
*\*\name    RCC_ConfigUSBRefClk.
*\*\fun     Config the USB1/2 reference clock divider from HSE.
*\*\param   CLK_divider(USB reference clock divider)
*\*\       - RCC_USBREFCLK_HSE_DIV1
*\*\       - RCC_USBREFCLK_HSE_DIV2
*\*\return  none
*\*\note   none
**/
void RCC_ConfigUSBRefClk(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->AHB2DIV1;
    /* Clear USBHSEDIV[3:0] bits */
    reg_value &=  RCC_USBREFCLK_HSE_DIV_MASK;
    /* Set the USBHSEDIV[3:0] bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->AHB2DIV1 = reg_value;

}

/**
*\*\name    RCC_ConfigAdc1PllClk.
*\*\fun     Configures the ADC PLL clock source.
*\*\param   CLK_source(ADC PLL clock source):
*\*\         - RCC_ADCPLLCLK_SRC_PLL2B
*\*\         - RCC_ADCPLLCLK_SRC_PLL1B
*\*\         - RCC_ADCPLLCLK_SRC_PLL3B
*\*\         - RCC_ADCPLLCLK_SRC_PLL3C
*\*\return  none
**/
void RCC_ConfigAdc1PllClk(uint32_t CLK_source)
{
    uint32_t temp_value;

    temp_value = RCC->AHB1SEL1;

    /* Clear ADC1PLLSEL[1:0] bits */
    temp_value &= RCC_ADC1PLLCLK_SRC_MASK;
    /* Set ADC1PLLSEL[1:0] bits according to CLK_source value*/
    temp_value |= CLK_source;

    /* Store the new value */
    RCC->AHB1SEL1 = temp_value;

}

/**
*\*\name    RCC_ConfigAdc1SysClk.
*\*\fun     Configures the prescaler from sys_bus_div_clk.
*\*\param   CLK_divider:
*\*\         - RCC_ADCSYSCLK_DIV1
*\*\         - RCC_ADCSYSCLK_DIV2
*\*\         - RCC_ADCSYSCLK_DIV3
*\*\         - RCC_ADCSYSCLK_DIV4
*\*\         - RCC_ADCSYSCLK_DIV5
*\*\         - RCC_ADCSYSCLK_DIV6
*\*\         - RCC_ADCSYSCLK_DIV7
*\*\         - RCC_ADCSYSCLK_DIV8
*\*\         - RCC_ADCSYSCLK_DIV9
*\*\         - RCC_ADCSYSCLK_DIV10
*\*\         - RCC_ADCSYSCLK_DIV11
*\*\         - RCC_ADCSYSCLK_DIV12
*\*\         - RCC_ADCSYSCLK_DIV13
*\*\         - RCC_ADCSYSCLK_DIV14
*\*\         - RCC_ADCSYSCLK_DIV15
*\*\         - RCC_ADCSYSCLK_DIV16
*\*\         - RCC_ADCSYSCLK_DIV17
*\*\         - RCC_ADCSYSCLK_DIV18
*\*\         - RCC_ADCSYSCLK_DIV19
*\*\         - RCC_ADCSYSCLK_DIV20
*\*\         - RCC_ADCSYSCLK_DIV21
*\*\         - RCC_ADCSYSCLK_DIV22
*\*\         - RCC_ADCSYSCLK_DIV23
*\*\         - RCC_ADCSYSCLK_DIV24
*\*\         - RCC_ADCSYSCLK_DIV25
*\*\         - RCC_ADCSYSCLK_DIV26
*\*\         - RCC_ADCSYSCLK_DIV27
*\*\         - RCC_ADCSYSCLK_DIV28
*\*\         - RCC_ADCSYSCLK_DIV29
*\*\         - RCC_ADCSYSCLK_DIV30
*\*\         - RCC_ADCSYSCLK_DIV31
*\*\         - RCC_ADCSYSCLK_DIV32
*\*\         - RCC_ADCSYSCLK_DIV33
*\*\         - RCC_ADCSYSCLK_DIV34
*\*\         - RCC_ADCSYSCLK_DIV35
*\*\         - RCC_ADCSYSCLK_DIV36
*\*\         - RCC_ADCSYSCLK_DIV37
*\*\         - RCC_ADCSYSCLK_DIV38
*\*\         - RCC_ADCSYSCLK_DIV39
*\*\         - RCC_ADCSYSCLK_DIV40
*\*\         - RCC_ADCSYSCLK_DIV41
*\*\         - RCC_ADCSYSCLK_DIV42
*\*\         - RCC_ADCSYSCLK_DIV43
*\*\         - RCC_ADCSYSCLK_DIV44
*\*\         - RCC_ADCSYSCLK_DIV45
*\*\         - RCC_ADCSYSCLK_DIV46
*\*\         - RCC_ADCSYSCLK_DIV47
*\*\         - RCC_ADCSYSCLK_DIV48
*\*\         - RCC_ADCSYSCLK_DIV49
*\*\         - RCC_ADCSYSCLK_DIV50
*\*\         - RCC_ADCSYSCLK_DIV51
*\*\         - RCC_ADCSYSCLK_DIV52
*\*\         - RCC_ADCSYSCLK_DIV53
*\*\         - RCC_ADCSYSCLK_DIV54
*\*\         - RCC_ADCSYSCLK_DIV55
*\*\         - RCC_ADCSYSCLK_DIV56
*\*\         - RCC_ADCSYSCLK_DIV57
*\*\         - RCC_ADCSYSCLK_DIV58
*\*\         - RCC_ADCSYSCLK_DIV59
*\*\         - RCC_ADCSYSCLK_DIV60
*\*\         - RCC_ADCSYSCLK_DIV61
*\*\         - RCC_ADCSYSCLK_DIV62
*\*\         - RCC_ADCSYSCLK_DIV63
*\*\return  none
**/
void RCC_ConfigAdc1SysClk(uint32_t CLK_divider)
{
    uint32_t temp_value;

    temp_value = RCC->AHB1DIV2;
    /* Clear ADC1SYSDIV[5:0] bits */
    temp_value &= RCC_ADC1SYSCLK_DIV_MASK;
    /* Set ADC1SYSDIV[5:0] bits according to CLK_divider value */
    temp_value |= CLK_divider;

    /* Store the new value */
    RCC->AHB1DIV2 = temp_value;
}

/**
*\*\name    RCC_ConfigAdc2PllClk.
*\*\fun     Configures the ADC PLL clock source.
*\*\param   CLK_source(ADC PLL clock source):
*\*\         - RCC_ADCPLLCLK_SRC_PLL2B
*\*\         - RCC_ADCPLLCLK_SRC_PLL1B
*\*\         - RCC_ADCPLLCLK_SRC_PLL3B
*\*\         - RCC_ADCPLLCLK_SRC_PLL3C
*\*\return  none
**/
void RCC_ConfigAdc2PllClk(uint32_t CLK_source)
{
    uint32_t temp_value;

    temp_value = RCC->AHB1SEL1;

    /* Clear ADC2PLLSEL[1:0] bits */
    temp_value &= RCC_ADC2PLLCLK_SRC_MASK;
    /* Set ADC2PLLSEL[1:0] bits according to CLK_source value*/
    temp_value |= (CLK_source << 4);

    /* Store the new value */
    RCC->AHB1SEL1 = temp_value;

}

/**
*\*\name    RCC_ConfigAdc2SysClk.
*\*\fun     Configures the ADCSYSCLK prescaler.
*\*\param   CLK_divider(ADCSYSCLK prescaler):
*\*\         - RCC_ADCSYSCLK_DIV1
*\*\         - RCC_ADCSYSCLK_DIV2
*\*\         - RCC_ADCSYSCLK_DIV3
*\*\         - RCC_ADCSYSCLK_DIV4
*\*\         - RCC_ADCSYSCLK_DIV5
*\*\         - RCC_ADCSYSCLK_DIV6
*\*\         - RCC_ADCSYSCLK_DIV7
*\*\         - RCC_ADCSYSCLK_DIV8
*\*\         - RCC_ADCSYSCLK_DIV9
*\*\         - RCC_ADCSYSCLK_DIV10
*\*\         - RCC_ADCSYSCLK_DIV11
*\*\         - RCC_ADCSYSCLK_DIV12
*\*\         - RCC_ADCSYSCLK_DIV13
*\*\         - RCC_ADCSYSCLK_DIV14
*\*\         - RCC_ADCSYSCLK_DIV15
*\*\         - RCC_ADCSYSCLK_DIV16
*\*\         - RCC_ADCSYSCLK_DIV17
*\*\         - RCC_ADCSYSCLK_DIV18
*\*\         - RCC_ADCSYSCLK_DIV19
*\*\         - RCC_ADCSYSCLK_DIV20
*\*\         - RCC_ADCSYSCLK_DIV21
*\*\         - RCC_ADCSYSCLK_DIV22
*\*\         - RCC_ADCSYSCLK_DIV23
*\*\         - RCC_ADCSYSCLK_DIV24
*\*\         - RCC_ADCSYSCLK_DIV25
*\*\         - RCC_ADCSYSCLK_DIV26
*\*\         - RCC_ADCSYSCLK_DIV27
*\*\         - RCC_ADCSYSCLK_DIV28
*\*\         - RCC_ADCSYSCLK_DIV29
*\*\         - RCC_ADCSYSCLK_DIV30
*\*\         - RCC_ADCSYSCLK_DIV31
*\*\         - RCC_ADCSYSCLK_DIV32
*\*\         - RCC_ADCSYSCLK_DIV33
*\*\         - RCC_ADCSYSCLK_DIV34
*\*\         - RCC_ADCSYSCLK_DIV35
*\*\         - RCC_ADCSYSCLK_DIV36
*\*\         - RCC_ADCSYSCLK_DIV37
*\*\         - RCC_ADCSYSCLK_DIV38
*\*\         - RCC_ADCSYSCLK_DIV39
*\*\         - RCC_ADCSYSCLK_DIV40
*\*\         - RCC_ADCSYSCLK_DIV41
*\*\         - RCC_ADCSYSCLK_DIV42
*\*\         - RCC_ADCSYSCLK_DIV43
*\*\         - RCC_ADCSYSCLK_DIV44
*\*\         - RCC_ADCSYSCLK_DIV45
*\*\         - RCC_ADCSYSCLK_DIV46
*\*\         - RCC_ADCSYSCLK_DIV47
*\*\         - RCC_ADCSYSCLK_DIV48
*\*\         - RCC_ADCSYSCLK_DIV49
*\*\         - RCC_ADCSYSCLK_DIV50
*\*\         - RCC_ADCSYSCLK_DIV51
*\*\         - RCC_ADCSYSCLK_DIV52
*\*\         - RCC_ADCSYSCLK_DIV53
*\*\         - RCC_ADCSYSCLK_DIV54
*\*\         - RCC_ADCSYSCLK_DIV55
*\*\         - RCC_ADCSYSCLK_DIV56
*\*\         - RCC_ADCSYSCLK_DIV57
*\*\         - RCC_ADCSYSCLK_DIV58
*\*\         - RCC_ADCSYSCLK_DIV59
*\*\         - RCC_ADCSYSCLK_DIV60
*\*\         - RCC_ADCSYSCLK_DIV61
*\*\         - RCC_ADCSYSCLK_DIV62
*\*\         - RCC_ADCSYSCLK_DIV63
*\*\return  none
**/
void RCC_ConfigAdc2SysClk(uint32_t CLK_divider)
{
    uint32_t temp_value;

    temp_value = RCC->AHB1DIV2;
    /* Clear ADC2SYSDIV[5:0] bits */
    temp_value &= RCC_ADC2SYSCLK_DIV_MASK;
    /* Set ADC2SYSDIV[5:0] bits according to CLK_divider value */
    temp_value |= (CLK_divider << 8);

    /* Store the new value */
    RCC->AHB1DIV2 = temp_value;
}

/**
*\*\name    RCC_ConfigAdc3PllClk.
*\*\fun     Configures the ADC PLL clock source.
*\*\param   CLK_source(ADC PLL clock source):
*\*\         - RCC_ADCPLLCLK_SRC_PLL2B
*\*\         - RCC_ADCPLLCLK_SRC_PLL1B
*\*\         - RCC_ADCPLLCLK_SRC_PLL3B
*\*\         - RCC_ADCPLLCLK_SRC_PLL3C
*\*\return  none
**/
void RCC_ConfigAdc3PllClk(uint32_t CLK_source)
{
    uint32_t temp_value;

    temp_value = RCC->AHB1SEL1;

    /* Clear ADC3PLLSEL[1:0] bits */
    temp_value &= RCC_ADC3PLLCLK_SRC_MASK;
    /* Set ADC3PLLSEL[1:0] bits according to CLK_source value*/
    temp_value |= (CLK_source << 8);

    /* Store the new value */
    RCC->AHB1SEL1 = temp_value;

}

/**
*\*\name    RCC_ConfigAdc3SysClk.
*\*\fun     Configures the ADCSYSCLK prescaler.
*\*\param   CLK_divider(ADCSYSCLK prescaler):
*\*\         - RCC_ADCSYSCLK_DIV1
*\*\         - RCC_ADCSYSCLK_DIV2
*\*\         - RCC_ADCSYSCLK_DIV3
*\*\         - RCC_ADCSYSCLK_DIV4
*\*\         - RCC_ADCSYSCLK_DIV5
*\*\         - RCC_ADCSYSCLK_DIV6
*\*\         - RCC_ADCSYSCLK_DIV7
*\*\         - RCC_ADCSYSCLK_DIV8
*\*\         - RCC_ADCSYSCLK_DIV9
*\*\         - RCC_ADCSYSCLK_DIV10
*\*\         - RCC_ADCSYSCLK_DIV11
*\*\         - RCC_ADCSYSCLK_DIV12
*\*\         - RCC_ADCSYSCLK_DIV13
*\*\         - RCC_ADCSYSCLK_DIV14
*\*\         - RCC_ADCSYSCLK_DIV15
*\*\         - RCC_ADCSYSCLK_DIV16
*\*\         - RCC_ADCSYSCLK_DIV17
*\*\         - RCC_ADCSYSCLK_DIV18
*\*\         - RCC_ADCSYSCLK_DIV19
*\*\         - RCC_ADCSYSCLK_DIV20
*\*\         - RCC_ADCSYSCLK_DIV21
*\*\         - RCC_ADCSYSCLK_DIV22
*\*\         - RCC_ADCSYSCLK_DIV23
*\*\         - RCC_ADCSYSCLK_DIV24
*\*\         - RCC_ADCSYSCLK_DIV25
*\*\         - RCC_ADCSYSCLK_DIV26
*\*\         - RCC_ADCSYSCLK_DIV27
*\*\         - RCC_ADCSYSCLK_DIV28
*\*\         - RCC_ADCSYSCLK_DIV29
*\*\         - RCC_ADCSYSCLK_DIV30
*\*\         - RCC_ADCSYSCLK_DIV31
*\*\         - RCC_ADCSYSCLK_DIV32
*\*\         - RCC_ADCSYSCLK_DIV33
*\*\         - RCC_ADCSYSCLK_DIV34
*\*\         - RCC_ADCSYSCLK_DIV35
*\*\         - RCC_ADCSYSCLK_DIV36
*\*\         - RCC_ADCSYSCLK_DIV37
*\*\         - RCC_ADCSYSCLK_DIV38
*\*\         - RCC_ADCSYSCLK_DIV39
*\*\         - RCC_ADCSYSCLK_DIV40
*\*\         - RCC_ADCSYSCLK_DIV41
*\*\         - RCC_ADCSYSCLK_DIV42
*\*\         - RCC_ADCSYSCLK_DIV43
*\*\         - RCC_ADCSYSCLK_DIV44
*\*\         - RCC_ADCSYSCLK_DIV45
*\*\         - RCC_ADCSYSCLK_DIV46
*\*\         - RCC_ADCSYSCLK_DIV47
*\*\         - RCC_ADCSYSCLK_DIV48
*\*\         - RCC_ADCSYSCLK_DIV49
*\*\         - RCC_ADCSYSCLK_DIV50
*\*\         - RCC_ADCSYSCLK_DIV51
*\*\         - RCC_ADCSYSCLK_DIV52
*\*\         - RCC_ADCSYSCLK_DIV53
*\*\         - RCC_ADCSYSCLK_DIV54
*\*\         - RCC_ADCSYSCLK_DIV55
*\*\         - RCC_ADCSYSCLK_DIV56
*\*\         - RCC_ADCSYSCLK_DIV57
*\*\         - RCC_ADCSYSCLK_DIV58
*\*\         - RCC_ADCSYSCLK_DIV59
*\*\         - RCC_ADCSYSCLK_DIV60
*\*\         - RCC_ADCSYSCLK_DIV61
*\*\         - RCC_ADCSYSCLK_DIV62
*\*\         - RCC_ADCSYSCLK_DIV63
*\*\return  none
**/
void RCC_ConfigAdc3SysClk(uint32_t CLK_divider)
{
    uint32_t temp_value;

    temp_value = RCC->AHB1DIV2;
    /* Clear ADC3SYSDIV[5:0] bits */
    temp_value &= RCC_ADC3SYSCLK_DIV_MASK;
    /* Set ADC3SYSDIV[5:0] bits according to CLK_divider value */
    temp_value |= (CLK_divider << 16);

    /* Store the new value */
    RCC->AHB1DIV2 = temp_value;
}


/**
*\*\name    RCC_ConfigBTIMKerClk.
*\*\fun     Config the BTIM1/2/3/4 kernel clock divider from ahb1.
*\*\param   CLK_divider
*\*\       - RCC_BTIMKERCLK_AHB1_DIV1
*\*\       - RCC_BTIMKERCLK_AHB1_DIV2
*\*\       - RCC_BTIMKERCLK_AHB1_DIV4
*\*\       - RCC_BTIMKERCLK_AHB1_DIV8
*\*\       - RCC_BTIMKERCLK_AHB1_DIV16
*\*\return  none
*\*\note   none
**/
void RCC_ConfigBTIMKerClk(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->APB1DIV1;
    /* Clear APB1BTIMDIV[2:0] bits */
    reg_value &=  RCC_BTIMKERCLK_AHB1_DIV_MASK;
    /* Set the APB1BTIMDIV[2:0] bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->APB1DIV1 = reg_value;
}

/**
*\*\name    RCC_ConfigGTIMA1_3_KerClk.
*\*\fun     Config the GTIMA1/2/3 kernel clock divider from ahb2.
*\*\param   CLK_divider
*\*\       - RCC_GTIMKERCLK_AHB2_DIV1
*\*\       - RCC_GTIMKERCLK_AHB2_DIV2
*\*\       - RCC_GTIMKERCLK_AHB2_DIV4
*\*\       - RCC_GTIMKERCLK_AHB2_DIV8
*\*\       - RCC_GTIMKERCLK_AHB2_DIV16
*\*\return  none
*\*\note   none
**/
void RCC_ConfigGTIMA1_3_KerClk(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->APB2DIV1;
    /* Clear APB2GTIMDIV[2:0] bits */
    reg_value &=  RCC_GTIMKERCLK_AHB2_DIV_MASK;
    /* Set the APB2GTIMDIV[2:0] bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->APB2DIV1 = reg_value;
}

/**
*\*\name    RCC_ConfigGTIMA4_7_KerClk.
*\*\fun     Config the GTIMA4/5/6/7 kernel clock divider from ahb1.
*\*\param   CLK_divider
*\*\       - RCC_GTIMKERCLK_AHB1_DIV1
*\*\       - RCC_GTIMKERCLK_AHB1_DIV2
*\*\       - RCC_GTIMKERCLK_AHB1_DIV4
*\*\       - RCC_GTIMKERCLK_AHB1_DIV8
*\*\       - RCC_GTIMKERCLK_AHB1_DIV16
*\*\return  none
*\*\note   none
**/
void RCC_ConfigGTIMA4_7_KerClk(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->APB1DIV1;
    /* Clear APB1GTIMDIV[2:0] bits */
    reg_value &=  RCC_GTIMKERCLK_AHB1_DIV_MASK;
    /* Set the APB1GTIMDIV[2:0] bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->APB1DIV1 = reg_value;
}

/**
*\*\name    RCC_ConfigGTIMB1_3_KerClk.
*\*\fun     Config the GTIMB1/2/3 kernel clock divider from ahb1.
*\*\param   CLK_divider
*\*\       - RCC_GTIMKERCLK_AHB1_DIV1
*\*\       - RCC_GTIMKERCLK_AHB1_DIV2
*\*\       - RCC_GTIMKERCLK_AHB1_DIV4
*\*\       - RCC_GTIMKERCLK_AHB1_DIV8
*\*\       - RCC_GTIMKERCLK_AHB1_DIV16
*\*\return  none
*\*\note   none
**/
void RCC_ConfigGTIMB1_3_KerClk(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->APB1DIV1;
    /* Clear APB1GTIMDIV[2:0] bits */
    reg_value &=  RCC_GTIMKERCLK_AHB1_DIV_MASK;
    /* Set the APB1GTIMDIV[2:0] bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->APB1DIV1 = reg_value;
}

/**
*\*\name    RCC_ConfigATIM1_2_KerClk.
*\*\fun     Config the ATIM1/2 kernel clock divider from ahb2.
*\*\param   CLK_divider
*\*\       - RCC_ATIMKERCLK_AHB2_DIV1
*\*\       - RCC_ATIMKERCLK_AHB2_DIV2
*\*\       - RCC_ATIMKERCLK_AHB2_DIV4
*\*\       - RCC_ATIMKERCLK_AHB2_DIV8
*\*\       - RCC_ATIMKERCLK_AHB2_DIV16
*\*\return  none
*\*\note   none
**/
void RCC_ConfigATIM1_2_KerClk(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->APB2DIV1;
    /* Clear APB2ATIMDIV[2:0] bits */
    reg_value &=  RCC_ATIMKERCLK_AHB2_DIV_MASK;
    /* Set the APB2ATIMDIV[2:0] bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->APB2DIV1 = reg_value;
}

/**
*\*\name    RCC_ConfigATIM3_4_KerClk.
*\*\fun     Config the ATIM3/4 kernel clock divider from ahb5.
*\*\param   CLK_divider
*\*\       - RCC_ATIMKERCLK_AHB5_DIV1
*\*\       - RCC_ATIMKERCLK_AHB5_DIV2
*\*\       - RCC_ATIMKERCLK_AHB5_DIV4
*\*\       - RCC_ATIMKERCLK_AHB5_DIV8
*\*\       - RCC_ATIMKERCLK_AHB5_DIV16
*\*\return  none
*\*\note   none
**/
void RCC_ConfigATIM3_4_KerClk(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->APB5DIV1;
    /* Clear APB5ATIMDIV[2:0] bits */
    reg_value &=  RCC_ATIMKERCLK_AHB5_DIV_MASK;
    /* Set the APB5ATIMDIV[2:0] bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->APB5DIV1 = reg_value;
}

/**
*\*\name    RCC_ConfigUSARTPClk.
*\*\fun     Config the USART1/2 PCLK divider from ahb1.
*\*\param   CLK_divider
*\*\       - RCC_USARTPCLK_AHB1_DIV1
*\*\       - RCC_USARTPCLK_AHB1_DIV2
*\*\       - RCC_USARTPCLK_AHB1_DIV4
*\*\       - RCC_USARTPCLK_AHB1_DIV8
*\*\       - RCC_USARTPCLK_AHB1_DIV16
*\*\return  none
*\*\note   none
**/
void RCC_ConfigUSARTPClk(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->APB1DIV1;
    /* Clear APB1USARTDIV[2:0] bits */
    reg_value &=  RCC_USARTPCLK_AHB1_DIV_MASK;
    /* Set the APB1USARTDIV[2:0] bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->APB1DIV1 = reg_value;
}

/**
*\*\name    RCC_ConfigI2S1KerClkSource.
*\*\fun     Config the I2S1 kernel clock source.
*\*\param   CLK_source(I2S kernel clock source):
*\*\       - RCC_I2SKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_I2SKERCLK_SRC_PLL3B
*\*\       - RCC_I2SKERCLK_SRC_HSI
*\*\       - RCC_I2SKERCLK_SRC_CLKIN
*\*\return  none
*\*\note  if select RCC_I2SKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB2I2SDIV[2:0]
**/
void RCC_ConfigI2S1KerClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->APB2SEL1;
    /* Clear I2S1KERSEL[1:0] bits */
    reg_value &= RCC_I2S1KERCLK_SRC_MASK;
    /* Set I2S1KERSEL[1:0] bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->APB2SEL1 = reg_value;

}

/**
*\*\name    RCC_ConfigI2S2KerClkSource.
*\*\fun     Config the I2S2 kernel clock source.
*\*\param   CLK_source(I2S kernel clock source):
*\*\       - RCC_I2SKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_I2SKERCLK_SRC_PLL3B
*\*\       - RCC_I2SKERCLK_SRC_HSI
*\*\       - RCC_I2SKERCLK_SRC_CLKIN
*\*\return  none
*\*\note  if select RCC_I2SKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB2I2SDIV[2:0]
**/
void RCC_ConfigI2S2KerClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->APB2SEL1;
    /* Clear I2S2KERSEL[1:0] bits */
    reg_value &= RCC_I2S2KERCLK_SRC_MASK;
    /* Set I2S2KERSEL[1:0] bits according to CLK_source value */
    reg_value |= (CLK_source << 2);
    /* Store the new value */
    RCC->APB2SEL1 = reg_value;

}

/**
*\*\name    RCC_ConfigI2S1_2_KerSysDivider.
*\*\fun     Config the I2S1/2 kernel clock source (sys_bus_div_clk) divider.
*\*\param   CLK_divider
*\*\       - RCC_I2SKERCLK_SYSBUSDIV1
*\*\       - RCC_I2SKERCLK_SYSBUSDIV2
*\*\       - RCC_I2SKERCLK_SYSBUSDIV4
*\*\       - RCC_I2SKERCLK_SYSBUSDIV8
*\*\       - RCC_I2SKERCLK_SYSBUSDIV16
*\*\return  none
*\*\note   none
**/
void RCC_ConfigI2S1_2_KerSysDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->APB2DIV1;
    /* Clear APB2I2SDIV[2:0] bits */
    reg_value &=  RCC_I2S1_2_KERCLK_SYSBUSDIV_MASK;
    /* Set the APB2I2SDIV[2:0] bits */
    reg_value |=  (CLK_divider << 8);
    /* Store the new value */
    RCC->APB2DIV1 = reg_value;
}

/**
*\*\name    RCC_ConfigI2S3KerClkSource.
*\*\fun     Config the I2S3 kernel clock source.
*\*\param   CLK_source(I2S kernel clock source):
*\*\       - RCC_I2SKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_I2SKERCLK_SRC_PLL3B
*\*\       - RCC_I2SKERCLK_SRC_HSI
*\*\       - RCC_I2SKERCLK_SRC_CLKIN
*\*\return  none
*\*\note  if select RCC_I2SKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB1I2SDIV[2:0]
**/
void RCC_ConfigI2S3KerClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->APB1SEL1;
    /* Clear I2S3KERSEL[1:0] bits */
    reg_value &= RCC_I2S3KERCLK_SRC_MASK;
    /* Set I2S3KERSEL[1:0] bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->APB1SEL1 = reg_value;

}

/**
*\*\name    RCC_ConfigI2S4KerClkSource.
*\*\fun     Config the I2S4 kernel clock source.
*\*\param   CLK_source(I2S kernel clock source):
*\*\       - RCC_I2SKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_I2SKERCLK_SRC_PLL3B
*\*\       - RCC_I2SKERCLK_SRC_HSI
*\*\       - RCC_I2SKERCLK_SRC_CLKIN
*\*\return  none
*\*\note  if select RCC_I2SKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB1I2SDIV[2:0]
**/
void RCC_ConfigI2S4KerClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->APB1SEL1;
    /* Clear I2S4KERSEL[1:0] bits */
    reg_value &= RCC_I2S4KERCLK_SRC_MASK;
    /* Set I2S4KERSEL[1:0] bits according to CLK_source value */
    reg_value |= (CLK_source << 2);
    /* Store the new value */
    RCC->APB1SEL1 = reg_value;

}

/**
*\*\name    RCC_ConfigI2S3_4_KerSysDivider.
*\*\fun     Config the I2S3/4 kernel clock source (sys_bus_div_clk) divider.
*\*\param   CLK_divider
*\*\       - RCC_I2SKERCLK_SYSBUSDIV1
*\*\       - RCC_I2SKERCLK_SYSBUSDIV2
*\*\       - RCC_I2SKERCLK_SYSBUSDIV4
*\*\       - RCC_I2SKERCLK_SYSBUSDIV8
*\*\       - RCC_I2SKERCLK_SYSBUSDIV16
*\*\return  none
*\*\note   none
**/
void RCC_ConfigI2S3_4_KerSysDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->APB1DIV1;
    /* Clear APB1I2SDIV[2:0] bits */
    reg_value &=  RCC_I2S3_4_KERCLK_SYSBUSDIV_MASK;
    /* Set the APB1I2SDIV[2:0] bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->APB1DIV1 = reg_value;
}



/**
*\*\name    RCC_ConfigI2C1KerClkSource.
*\*\fun     Config the I2C1 kernel clock source.
*\*\param   CLK_source(I2C kernel clock source):
*\*\       - RCC_I2CKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_I2CKERCLK_SRC_PLL3C
*\*\       - RCC_I2CKERCLK_SRC_HSI
*\*\       - RCC_I2CKERCLK_SRC_MSI
*\*\return  none
*\*\note  if select RCC_I2CKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB1I2CDIV[2:0]
**/
void RCC_ConfigI2C1KerClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->APB1SEL1;
    /* Clear I2C1KERSEL[2:0] bits */
    reg_value &= RCC_I2C1KERCLK_SRC_MASK;
    /* Set I2C1KERSEL[2:0] bits according to CLK_source value */
    reg_value |= (CLK_source << 8);
    /* Store the new value */
    RCC->APB1SEL1 = reg_value;

}

/**
*\*\name    RCC_ConfigI2C2KerClkSource.
*\*\fun     Config the I2C2 kernel clock source.
*\*\param   CLK_source(I2C kernel clock source):
*\*\       - RCC_I2CKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_I2CKERCLK_SRC_PLL3C
*\*\       - RCC_I2CKERCLK_SRC_HSI
*\*\       - RCC_I2CKERCLK_SRC_MSI
*\*\return  none
*\*\note  if select RCC_I2CKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB1I2CDIV[2:0]
**/
void RCC_ConfigI2C2KerClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->APB1SEL1;
    /* Clear I2C2KERSEL[2:0] bits */
    reg_value &= RCC_I2C2KERCLK_SRC_MASK;
    /* Set I2C2KERSEL[2:0] bits according to CLK_source value */
    reg_value |= (CLK_source << 4);
    /* Store the new value */
    RCC->APB1SEL1 = reg_value;

}

/**
*\*\name    RCC_ConfigI2C3KerClkSource.
*\*\fun     Config the I2C3 kernel clock source.
*\*\param   CLK_source(I2C kernel clock source):
*\*\       - RCC_I2CKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_I2CKERCLK_SRC_PLL3C
*\*\       - RCC_I2CKERCLK_SRC_HSI
*\*\       - RCC_I2CKERCLK_SRC_MSI
*\*\return  none
*\*\note  if select RCC_I2CKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB1I2CDIV[2:0]
**/
void RCC_ConfigI2C3KerClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->APB1SEL1;
    /* Clear I2C3KERSEL[2:0] bits */
    reg_value &= RCC_I2C3KERCLK_SRC_MASK;
    /* Set I2C3KERSEL[2:0] bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->APB1SEL1 = reg_value;

}

/**
*\*\name    RCC_ConfigI2C1_3_KerSysDivider.
*\*\fun     Config the I2C1/2/3 kernel clock source (sys_bus_div_clk) divider.
*\*\param   CLK_divider
*\*\       - RCC_I2CKERCLK_SYSBUSDIV1
*\*\       - RCC_I2CKERCLK_SYSBUSDIV2
*\*\       - RCC_I2CKERCLK_SYSBUSDIV4
*\*\       - RCC_I2CKERCLK_SYSBUSDIV8
*\*\       - RCC_I2CKERCLK_SYSBUSDIV16
*\*\return  none
*\*\note   none
**/
void RCC_ConfigI2C1_3_KerSysDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->APB1DIV1;
    /* Clear APB1I2CDIV[2:0] bits */
    reg_value &=  RCC_I2C1_3_KERCLK_SYSBUSDIV_MASK;
    /* Set the APB1I2CDIV[2:0] bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->APB1DIV1 = reg_value;
}

/**
*\*\name    RCC_ConfigI2C4KerClkSource.
*\*\fun     Config the I2C4 kernel clock source.
*\*\param   CLK_source(I2C kernel clock source):
*\*\       - RCC_I2CKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_I2CKERCLK_SRC_PLL3C
*\*\       - RCC_I2CKERCLK_SRC_HSI
*\*\       - RCC_I2CKERCLK_SRC_MSI
*\*\return  none
*\*\note  if select RCC_I2CKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB2I2CDIV[2:0]
**/
void RCC_ConfigI2C4KerClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->APB2SEL1;
    /* Clear I2C4KERSEL[2:0] bits */
    reg_value &= RCC_I2C4KERCLK_SRC_MASK;
    /* Set I2C4KERSEL[2:0] bits according to CLK_source value */
    reg_value |= (CLK_source >> 8);
    /* Store the new value */
    RCC->APB2SEL1 = reg_value;

}

/**
*\*\name    RCC_ConfigI2C5KerClkSource.
*\*\fun     Config the I2C5 kernel clock source.
*\*\param   CLK_source(I2C kernel clock source):
*\*\       - RCC_I2CKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_I2CKERCLK_SRC_PLL3C
*\*\       - RCC_I2CKERCLK_SRC_HSI
*\*\       - RCC_I2CKERCLK_SRC_MSI
*\*\return  none
*\*\note  if select RCC_I2CKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB2I2CDIV[2:0]
**/
void RCC_ConfigI2C5KerClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->APB2SEL1;
    /* Clear I2C5KERSEL[2:0] bits */
    reg_value &= RCC_I2C5KERCLK_SRC_MASK;
    /* Set I2C5KERSEL[2:0] bits according to CLK_source value */
    reg_value |= (CLK_source >> 12);
    /* Store the new value */
    RCC->APB2SEL1 = reg_value;

}

/**
*\*\name    RCC_ConfigI2C6KerClkSource.
*\*\fun     Config the I2C6 kernel clock source.
*\*\param   CLK_source(I2C kernel clock source):
*\*\       - RCC_I2CKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_I2CKERCLK_SRC_PLL3C
*\*\       - RCC_I2CKERCLK_SRC_HSI
*\*\       - RCC_I2CKERCLK_SRC_MSI
*\*\return  none
*\*\note  if select RCC_I2CKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB2I2CDIV[2:0]
**/
void RCC_ConfigI2C6KerClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->APB2SEL1;
    /* Clear I2C6KERSEL[2:0] bits */
    reg_value &= RCC_I2C6KERCLK_SRC_MASK;
    /* Set I2C6KERSEL[2:0] bits according to CLK_source value */
    reg_value |= (CLK_source >> 16);
    /* Store the new value */
    RCC->APB2SEL1 = reg_value;

}


/**
*\*\name    RCC_ConfigI2C4_6_KerSysDivider.
*\*\fun     Config the I2C4/5/6 kernel clock source (sys_bus_div_clk) divider.
*\*\param   CLK_divider
*\*\       - RCC_I2CKERCLK_SYSBUSDIV1
*\*\       - RCC_I2CKERCLK_SYSBUSDIV2
*\*\       - RCC_I2CKERCLK_SYSBUSDIV4
*\*\       - RCC_I2CKERCLK_SYSBUSDIV8
*\*\       - RCC_I2CKERCLK_SYSBUSDIV16
*\*\return  none
*\*\note   none
**/
void RCC_ConfigI2C4_6_KerSysDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->APB2DIV1;
    /* Clear APB2I2CDIV[2:0] bits */
    reg_value &=  RCC_I2C4_6_KERCLK_SYSBUSDIV_MASK;
    /* Set the APB2I2CDIV[2:0] bits */
    reg_value |=  (CLK_divider << 8);
    /* Store the new value */
    RCC->APB2DIV1 = reg_value;
}

/**
*\*\name    RCC_ConfigI2C7KerClkSource.
*\*\fun     Config the I2C7 kernel clock source.
*\*\param   CLK_source(I2C kernel clock source):
*\*\       - RCC_I2CKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_I2CKERCLK_SRC_PLL3C
*\*\       - RCC_I2CKERCLK_SRC_HSI
*\*\       - RCC_I2CKERCLK_SRC_MSI
*\*\return  none
*\*\note  if select RCC_I2CKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB5I2CDIV[2:0]
**/
void RCC_ConfigI2C7KerClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->APB5SEL1;
    /* Clear I2C7KERSEL[2:0] bits */
    reg_value &= RCC_I2C7KERCLK_SRC_MASK;
    /* Set I2C7KERSEL[2:0] bits according to CLK_source value */
    reg_value |= (CLK_source << 8);
    /* Store the new value */
    RCC->APB5SEL1 = reg_value;

}

/**
*\*\name    RCC_ConfigI2C8KerClkSource.
*\*\fun     Config the I2C8 kernel clock source.
*\*\param   CLK_source(I2C kernel clock source):
*\*\       - RCC_I2CKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_I2CKERCLK_SRC_PLL3C
*\*\       - RCC_I2CKERCLK_SRC_HSI
*\*\       - RCC_I2CKERCLK_SRC_MSI
*\*\return  none
*\*\note  if select RCC_I2CKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB5I2CDIV[2:0]
**/
void RCC_ConfigI2C8KerClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->APB5SEL1;
    /* Clear I2C8KERSEL[2:0] bits */
    reg_value &= RCC_I2C8KERCLK_SRC_MASK;
    /* Set I2C8KERSEL[2:0] bits according to CLK_source value */
    reg_value |= (CLK_source << 4);
    /* Store the new value */
    RCC->APB5SEL1 = reg_value;

}

/**
*\*\name    RCC_ConfigI2C9KerClkSource.
*\*\fun     Config the I2C9 kernel clock source.
*\*\param   CLK_source(I2C kernel clock source):
*\*\       - RCC_I2CKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_I2CKERCLK_SRC_PLL3C
*\*\       - RCC_I2CKERCLK_SRC_HSI
*\*\       - RCC_I2CKERCLK_SRC_MSI
*\*\return  none
*\*\note  if select RCC_I2CKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB5I2CDIV[2:0]
**/
void RCC_ConfigI2C9KerClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->APB5SEL1;
    /* Clear I2C9KERSEL[2:0] bits */
    reg_value &= RCC_I2C9KERCLK_SRC_MASK;
    /* Set I2C9KERSEL[2:0] bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->APB5SEL1 = reg_value;

}

/**
*\*\name    RCC_ConfigI2C10KerClkSource.
*\*\fun     Config the I2C10 kernel clock source.
*\*\param   CLK_source(I2C kernel clock source):
*\*\       - RCC_I2CKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_I2CKERCLK_SRC_PLL3C
*\*\       - RCC_I2CKERCLK_SRC_HSI
*\*\       - RCC_I2CKERCLK_SRC_MSI
*\*\return  none
*\*\note  if select RCC_I2CKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB5I2CDIV[2:0]
**/
void RCC_ConfigI2C10KerClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->APB5SEL1;
    /* Clear I2C10KERSEL[2:0] bits */
    reg_value &= RCC_I2C10KERCLK_SRC_MASK;
    /* Set I2C10KERSEL[2:0] bits according to CLK_source value */
    reg_value |= (CLK_source >> 4);
    /* Store the new value */
    RCC->APB5SEL1 = reg_value;

}


/**
*\*\name    RCC_ConfigI2C7_10_KerSysDivider.
*\*\fun     Config the I2C7/8/9/10 kernel clock source (sys_bus_div_clk) divider.
*\*\param   CLK_divider
*\*\       - RCC_I2CKERCLK_SYSBUSDIV1
*\*\       - RCC_I2CKERCLK_SYSBUSDIV2
*\*\       - RCC_I2CKERCLK_SYSBUSDIV4
*\*\       - RCC_I2CKERCLK_SYSBUSDIV8
*\*\       - RCC_I2CKERCLK_SYSBUSDIV16
*\*\return  none
*\*\note   none
**/
void RCC_ConfigI2C7_10_KerSysDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->APB5DIV1;
    /* Clear APB5I2CDIV[2:0] bits */
    reg_value &=  RCC_I2C7_10_KERCLK_SYSBUSDIV_MASK;
    /* Set the APB5I2CDIV[2:0] bits */
    reg_value |=  (CLK_divider << 24);
    /* Store the new value */
    RCC->APB5DIV1 = reg_value;
}

/**
*\*\name    RCC_ConfigFDCAN1KerClkSource.
*\*\fun     Config the FDCAN1 kernel clock source.
*\*\param   CLK_source(FDCAN kernel clock source):
*\*\       - RCC_FDCANKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_FDCANKERCLK_SRC_PLL1C
*\*\       - RCC_FDCANKERCLK_SRC_PLL2C
*\*\       - RCC_FDCANKERCLK_SRC_PLL3B
*\*\       - RCC_FDCANKERCLK_SRC_PERIPH
*\*\return  none
*\*\note  if select RCC_FDCANKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB1FDCANDIV[2:0]
**/
void RCC_ConfigFDCAN1KerClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->APB1SEL1;
    /* Clear FDCAN1KERSEL[2:0] bits */
    reg_value &= RCC_FDCAN1KERCLK_SRC_MASK;
    /* Set FDCAN1KERSEL[2:0] bits according to CLK_source value */
    reg_value |= (CLK_source << 8);
    /* Store the new value */
    RCC->APB1SEL1 = reg_value;

}

/**
*\*\name    RCC_ConfigFDCAN2KerClkSource.
*\*\fun     Config the FDCAN2 kernel clock source.
*\*\param   CLK_source(FDCAN kernel clock source):
*\*\       - RCC_FDCANKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_FDCANKERCLK_SRC_PLL1C
*\*\       - RCC_FDCANKERCLK_SRC_PLL2C
*\*\       - RCC_FDCANKERCLK_SRC_PLL3B
*\*\       - RCC_FDCANKERCLK_SRC_PERIPH
*\*\return  none
*\*\note  if select RCC_FDCANKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB1FDCANDIV[2:0]
**/
void RCC_ConfigFDCAN2KerClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->APB1SEL1;
    /* Clear FDCAN2KERSEL[2:0] bits */
    reg_value &= RCC_FDCAN2KERCLK_SRC_MASK;
    /* Set FDCAN2KERSEL[2:0] bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->APB1SEL1 = reg_value;

}

/**
*\*\name    RCC_ConfigFDCAN5KerClkSource.
*\*\fun     Config the FDCAN5 kernel clock source.
*\*\param   CLK_source(FDCAN kernel clock source):
*\*\       - RCC_FDCANKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_FDCANKERCLK_SRC_PLL1C
*\*\       - RCC_FDCANKERCLK_SRC_PLL2C
*\*\       - RCC_FDCANKERCLK_SRC_PLL3B
*\*\       - RCC_FDCANKERCLK_SRC_PERIPH
*\*\return  none
*\*\note  if select RCC_FDCANKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB1FDCANDIV[2:0]
**/
void RCC_ConfigFDCAN5KerClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->APB1SEL2;
    /* Clear FDCAN5KERSEL[2:0] bits */
    reg_value &= RCC_FDCAN5KERCLK_SRC_MASK;
    /* Set FDCAN5KERSEL[2:0] bits according to CLK_source value */
    reg_value |= (CLK_source << 20);
    /* Store the new value */
    RCC->APB1SEL2 = reg_value;

}

/**
*\*\name    RCC_ConfigFDCAN6KerClkSource.
*\*\fun     Config the FDCAN6 kernel clock source.
*\*\param   CLK_source(FDCAN kernel clock source):
*\*\       - RCC_FDCANKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_FDCANKERCLK_SRC_PLL1C
*\*\       - RCC_FDCANKERCLK_SRC_PLL2C
*\*\       - RCC_FDCANKERCLK_SRC_PLL3B
*\*\       - RCC_FDCANKERCLK_SRC_PERIPH
*\*\return  none
*\*\note  if select RCC_FDCANKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB1FDCANDIV[2:0]
**/
void RCC_ConfigFDCAN6KerClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->APB1SEL2;
    /* Clear FDCAN6KERSEL[2:0] bits */
    reg_value &= RCC_FDCAN6KERCLK_SRC_MASK;
    /* Set FDCAN6KERSEL[2:0] bits according to CLK_source value */
    reg_value |= (CLK_source << 12);
    /* Store the new value */
    RCC->APB1SEL2 = reg_value;

}

/**
*\*\name    RCC_ConfigFDCAN1_2_5_6_KerSysDivider.
*\*\fun     Config the FDCAN1/2/5/6 kernel clock source (sys_bus_div_clk) divider.
*\*\param   CLK_divider
*\*\       - RCC_FDCANKERCLK_SYSBUSDIV1
*\*\       - RCC_FDCANKERCLK_SYSBUSDIV2
*\*\       - RCC_FDCANKERCLK_SYSBUSDIV4
*\*\       - RCC_FDCANKERCLK_SYSBUSDIV8
*\*\       - RCC_FDCANKERCLK_SYSBUSDIV16
*\*\return  none
*\*\note   none
**/
void RCC_ConfigFDCAN1_2_5_6_KerSysDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->APB1DIV1;
    /* Clear APB1FDCANDIV[2:0] bits */
    reg_value &=  RCC_FDCAN1_2_5_6_KERCLK_SYSBUSDIV_MASK;
    /* Set the APB1FDCANDIV[2:0] bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->APB1DIV1 = reg_value;
}

/**
*\*\name    RCC_ConfigFDCAN3KerClkSource.
*\*\fun     Config the FDCAN3 kernel clock source.
*\*\param   CLK_source(FDCAN kernel clock source):
*\*\       - RCC_FDCANKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_FDCANKERCLK_SRC_PLL1C
*\*\       - RCC_FDCANKERCLK_SRC_PLL2C
*\*\       - RCC_FDCANKERCLK_SRC_PLL3B
*\*\       - RCC_FDCANKERCLK_SRC_PERIPH
*\*\return  none
*\*\note  if select RCC_FDCANKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB2FDCANDIV[2:0]
**/
void RCC_ConfigFDCAN3KerClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->APB2SEL2;
    /* Clear FDCAN3KERSEL[2:0] bits */
    reg_value &= RCC_FDCAN3KERCLK_SRC_MASK;
    /* Set FDCAN3KERSEL[2:0] bits according to CLK_source value */
    reg_value |= (CLK_source << 20);
    /* Store the new value */
    RCC->APB2SEL2 = reg_value;

}

/**
*\*\name    RCC_ConfigFDCAN4KerClkSource.
*\*\fun     Config the FDCAN4 kernel clock source.
*\*\param   CLK_source(FDCAN kernel clock source):
*\*\       - RCC_FDCANKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_FDCANKERCLK_SRC_PLL1C
*\*\       - RCC_FDCANKERCLK_SRC_PLL2C
*\*\       - RCC_FDCANKERCLK_SRC_PLL3B
*\*\       - RCC_FDCANKERCLK_SRC_PERIPH
*\*\return  none
*\*\note  if select RCC_FDCANKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB2FDCANDIV[2:0]
**/
void RCC_ConfigFDCAN4KerClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->APB2SEL2;
    /* Clear FDCAN4KERSEL[2:0] bits */
    reg_value &= RCC_FDCAN4KERCLK_SRC_MASK;
    /* Set FDCAN4KERSEL[2:0] bits according to CLK_source value */
    reg_value |= (CLK_source << 12);
    /* Store the new value */
    RCC->APB2SEL2 = reg_value;

}

/**
*\*\name    RCC_ConfigFDCAN7KerClkSource.
*\*\fun     Config the FDCAN7 kernel clock source.
*\*\param   CLK_source(FDCAN kernel clock source):
*\*\       - RCC_FDCANKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_FDCANKERCLK_SRC_PLL1C
*\*\       - RCC_FDCANKERCLK_SRC_PLL2C
*\*\       - RCC_FDCANKERCLK_SRC_PLL3B
*\*\       - RCC_FDCANKERCLK_SRC_PERIPH
*\*\return  none
*\*\note  if select RCC_FDCANKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB2FDCANDIV[2:0]
**/
void RCC_ConfigFDCAN7KerClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->APB2SEL2;
    /* Clear FDCAN7KERSEL[2:0] bits */
    reg_value &= RCC_FDCAN7KERCLK_SRC_MASK;
    /* Set FDCAN7KERSEL[2:0] bits according to CLK_source value */
    reg_value |= (CLK_source << 4);
    /* Store the new value */
    RCC->APB2SEL2 = reg_value;

}

/**
*\*\name    RCC_ConfigFDCAN8KerClkSource.
*\*\fun     Config the FDCAN8 kernel clock source.
*\*\param   CLK_source(FDCAN kernel clock source):
*\*\       - RCC_FDCANKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_FDCANKERCLK_SRC_PLL1C
*\*\       - RCC_FDCANKERCLK_SRC_PLL2C
*\*\       - RCC_FDCANKERCLK_SRC_PLL3B
*\*\       - RCC_FDCANKERCLK_SRC_PERIPH
*\*\return  none
*\*\note  if select RCC_FDCANKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by APB2FDCANDIV[2:0]
**/
void RCC_ConfigFDCAN8KerClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->APB2SEL2;
    /* Clear FDCAN8KERSEL[2:0] bits */
    reg_value &= RCC_FDCAN8KERCLK_SRC_MASK;
    /* Set FDCAN8KERSEL[2:0] bits according to CLK_source value */
    reg_value |= (CLK_source >> 4);
    /* Store the new value */
    RCC->APB2SEL2 = reg_value;

}

/**
*\*\name    RCC_ConfigFDCAN3_4_7_8_KerSysDivider.
*\*\fun     Config the FDCAN3/4/7/8 kernel clock source (sys_bus_div_clk) divider.
*\*\param   CLK_divider
*\*\       - RCC_FDCANKERCLK_SYSBUSDIV1
*\*\       - RCC_FDCANKERCLK_SYSBUSDIV2
*\*\       - RCC_FDCANKERCLK_SYSBUSDIV4
*\*\       - RCC_FDCANKERCLK_SYSBUSDIV8
*\*\       - RCC_FDCANKERCLK_SYSBUSDIV16
*\*\return  none
*\*\note   none
**/
void RCC_ConfigFDCAN3_4_7_8_KerSysDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->APB2DIV1;
    /* Clear APB2FDCANDIV[2:0] bits */
    reg_value &=  RCC_FDCAN3_4_7_8_KERCLK_SYSBUSDIV_MASK;
    /* Set the APB2FDCANDIV[2:0] bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->APB2DIV1 = reg_value;
}

/**
*\*\name    RCC_ConfigEXTISysDivider.
*\*\fun     Config the EXTI (sys_bus_div_clk) divider.
*\*\param   CLK_divider
*\*\       - RCC_EXTICLK_SYSBUSDIV1
*\*\       - RCC_EXTICLK_SYSBUSDIV2
*\*\       - RCC_EXTICLK_SYSBUSDIV4
*\*\       - RCC_EXTICLK_SYSBUSDIV8
*\*\       - RCC_EXTICLK_SYSBUSDIV16
*\*\return  none
*\*\note   none
**/
void RCC_ConfigEXTISysDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->APB5DIV1;
    /* Clear APB5EXTIDIV[2:0] bits */
    reg_value &=  RCC_EXTI_SYSBUSDIV_MASK;
    /* Set the APB5EXTIDIV[2:0] bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->APB5DIV1 = reg_value;
}

/**
*\*\name    RCC_ConfigRtcClk.
*\*\fun     Config the RTC clock.
*\*\param   CLK_source:
*\*\       - RCC_RTCCLK_SRC_LSE
*\*\       - RCC_RTCCLK_SRC_LSI
*\*\       - RCC_RTCCLK_SRC_HSEDIV
*\*\param   CLK_divider:
*\*\         - RCC_RTCCLK_HSEDIV1
*\*\         - RCC_RTCCLK_HSEDIV2
*\*\         - RCC_RTCCLK_HSEDIV3
*\*\         - RCC_RTCCLK_HSEDIV4
*\*\         - RCC_RTCCLK_HSEDIV5
*\*\         - RCC_RTCCLK_HSEDIV6
*\*\         - RCC_RTCCLK_HSEDIV7
*\*\         - RCC_RTCCLK_HSEDIV8
*\*\         - RCC_RTCCLK_HSEDIV9
*\*\         - RCC_RTCCLK_HSEDIV10
*\*\         - RCC_RTCCLK_HSEDIV11
*\*\         - RCC_RTCCLK_HSEDIV12
*\*\         - RCC_RTCCLK_HSEDIV13
*\*\         - RCC_RTCCLK_HSEDIV14
*\*\         - RCC_RTCCLK_HSEDIV15
*\*\         - RCC_RTCCLK_HSEDIV16
*\*\         - RCC_RTCCLK_HSEDIV17
*\*\         - RCC_RTCCLK_HSEDIV18
*\*\         - RCC_RTCCLK_HSEDIV19
*\*\         - RCC_RTCCLK_HSEDIV20
*\*\         - RCC_RTCCLK_HSEDIV21
*\*\         - RCC_RTCCLK_HSEDIV22
*\*\         - RCC_RTCCLK_HSEDIV23
*\*\         - RCC_RTCCLK_HSEDIV24
*\*\         - RCC_RTCCLK_HSEDIV25
*\*\         - RCC_RTCCLK_HSEDIV26
*\*\         - RCC_RTCCLK_HSEDIV27
*\*\         - RCC_RTCCLK_HSEDIV28
*\*\         - RCC_RTCCLK_HSEDIV29
*\*\         - RCC_RTCCLK_HSEDIV30
*\*\         - RCC_RTCCLK_HSEDIV31
*\*\         - RCC_RTCCLK_HSEDIV32
*\*\         - RCC_RTCCLK_HSEDIV33
*\*\         - RCC_RTCCLK_HSEDIV34
*\*\         - RCC_RTCCLK_HSEDIV35
*\*\         - RCC_RTCCLK_HSEDIV36
*\*\         - RCC_RTCCLK_HSEDIV37
*\*\         - RCC_RTCCLK_HSEDIV38
*\*\         - RCC_RTCCLK_HSEDIV39
*\*\         - RCC_RTCCLK_HSEDIV40
*\*\         - RCC_RTCCLK_HSEDIV41
*\*\         - RCC_RTCCLK_HSEDIV42
*\*\         - RCC_RTCCLK_HSEDIV43
*\*\         - RCC_RTCCLK_HSEDIV44
*\*\         - RCC_RTCCLK_HSEDIV45
*\*\         - RCC_RTCCLK_HSEDIV46
*\*\         - RCC_RTCCLK_HSEDIV47
*\*\         - RCC_RTCCLK_HSEDIV48
*\*\         - RCC_RTCCLK_HSEDIV49
*\*\         - RCC_RTCCLK_HSEDIV50
*\*\         - RCC_RTCCLK_HSEDIV51
*\*\         - RCC_RTCCLK_HSEDIV52
*\*\         - RCC_RTCCLK_HSEDIV53
*\*\         - RCC_RTCCLK_HSEDIV54
*\*\         - RCC_RTCCLK_HSEDIV55
*\*\         - RCC_RTCCLK_HSEDIV56
*\*\         - RCC_RTCCLK_HSEDIV57
*\*\         - RCC_RTCCLK_HSEDIV58
*\*\         - RCC_RTCCLK_HSEDIV59
*\*\         - RCC_RTCCLK_HSEDIV60
*\*\         - RCC_RTCCLK_HSEDIV61
*\*\         - RCC_RTCCLK_HSEDIV62
*\*\         - RCC_RTCCLK_HSEDIV63
*\*\return  none
*\*\note    if select RCC_RTCCLK_SRC_HSEDIV then set the HSE divider by RTCHSEDIV[5:0]
*\*\note    BDCTRL is protected, you need to enable the PWR clock first,
*\*\       then configure PWR_SYSCTRL1.DBKP to 1 to change it.
**/
void RCC_ConfigRtcClk(uint32_t CLK_source, uint32_t CLK_divider)
{
    uint32_t reg_value;
    uint32_t reg_value1;

    reg_value = RCC->BDCTRL;
    /* Clear RTCSEL[2:0] bits */
    reg_value &= RCC_RTCCLK_SRC_MASK;
    /* Set RTCSEL[2:0] bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->BDCTRL = reg_value;

    if(CLK_source == RCC_RTCCLK_SRC_HSEDIV)
    {
        reg_value1 = RCC->CFG5;
        /* Clear RTCHSEDIV[5:0] bits */
        reg_value1 &=  RCC_RTCCLK_HSEDIV_MASK;
        /* Set the RTCHSEDIV[5:0] bits */
        reg_value1 |=  CLK_divider;
        /* Store the new value */
        RCC->CFG5 = reg_value1;
    }

}

/**
*\*\name    RCC_EnableRtcClk.
*\*\fun     Enables the RTC clock.
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note    This function must be used only after the RTC clock was selected
*\*\        using the RCC_ConfigRtcClk function.
*\*\note    BDCTRL is protected, you need to enable the PWR clock first,
*\*\        then configure PWR_SYSCTRL1.DBKP to 1 to change it.
**/
void RCC_EnableRtcClk(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        RCC->BDCTRL |= RCC_RTC_ENABLE;
    }
    else
    {
        RCC->BDCTRL &= (~RCC_RTC_ENABLE);
    }
}

/**
*\*\name    RCC_EnableBackupReset.
*\*\fun     Reset Backup domain .
*\*\param   none
*\*\return  none.
*\*\note    BDCTRL is protected, you need to enable the PWR clock first,
*\*\        then configure PWR_SYSCTRL1.DBKP to 1 to change it.
**/
void RCC_EnableBackupReset(void)
{
    RCC->BDCTRL |= (RCC_BKUP_RESET);
    RCC->BDCTRL &= (~RCC_BKUP_RESET);
}

/**
*\*\name    RCC_EnableDCMUReset.
*\*\fun     Reset DCMU.
*\*\param   none
*\*\return  none.
**/
void RCC_EnableDCMUReset(void)
{
    RCC->CFG4 |= (RCC_DCMU_RESET);
    RCC->CFG4 &= (~RCC_DCMU_RESET);
}

/**
*\*\name    RCC_ConfigLPTIM1Clk.
*\*\fun     Config the LPTIM1 clock source.
*\*\param   CLK_source:
*\*\     - RCC_LPTIMCLK_SRC_APB5
*\*\     - RCC_LPTIMCLK_SRC_LSI
*\*\     - RCC_LPTIMCLK_SRC_LSE
*\*\     - RCC_LPTIMCLK_SRC_HSE
*\*\     - RCC_LPTIMCLK_SRC_HSI
*\*\     - RCC_LPTIMCLK_SRC_MSI
*\*\     - RCC_LPTIMCLK_SRC_COMP1
*\*\     - RCC_LPTIMCLK_SRC_COMP2
*\*\     - RCC_LPTIMCLK_SRC_COMP3
*\*\     - RCC_LPTIMCLK_SRC_COMP4
*\*\return  none
*\*\note  none
**/
void RCC_ConfigLPTIM1Clk(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->RDSEL1;
    /* Clear LPTIM1SEL[3:0] bits */
    reg_value &= RCC_LPTIM1CLK_SRC_MASK;
    /* Set LPTIM1SEL[3:0] bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->RDSEL1 = reg_value;

}

/**
*\*\name    RCC_EnableLPTIM1CompGate.
*\*\fun     Enable gate signal from COMPx to LPTIM1.
*\*\param   COMP_sel(select one COMPx) :
*\*\        -RCC_GATEEN_LPTIM1_COMP1
*\*\        -RCC_GATEEN_LPTIM1_COMP2
*\*\        -RCC_GATEEN_LPTIM1_COMP3
*\*\        -RCC_GATEEN_LPTIM1_COMP4
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note    If the LPTIM clock source is COMP, you need to enable this gate
**/
void RCC_EnableLPTIM1CompGate(uint32_t COMP_sel, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->RDCTRL1 |= COMP_sel;
    }
    else
    {
        RCC->RDCTRL1 &= ~COMP_sel;
    }

}

/**
*\*\name    RCC_ConfigLPTIM2Clk.
*\*\fun     Config the LPTIM2 clock source.
*\*\param   CLK_source:
*\*\     - RCC_LPTIMCLK_SRC_APB5
*\*\     - RCC_LPTIMCLK_SRC_LSI
*\*\     - RCC_LPTIMCLK_SRC_LSE
*\*\     - RCC_LPTIMCLK_SRC_HSE
*\*\     - RCC_LPTIMCLK_SRC_HSI
*\*\     - RCC_LPTIMCLK_SRC_MSI
*\*\     - RCC_LPTIMCLK_SRC_COMP1
*\*\     - RCC_LPTIMCLK_SRC_COMP2
*\*\     - RCC_LPTIMCLK_SRC_COMP3
*\*\     - RCC_LPTIMCLK_SRC_COMP4
*\*\return  none
*\*\note  none
**/
void RCC_ConfigLPTIM2Clk(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->RDSEL1;
    /* Clear LPTIM2SEL[3:0] bits */
    reg_value &= RCC_LPTIM2CLK_SRC_MASK;
    /* Set LPTIM2SEL[3:0] bits according to CLK_source value */
    reg_value |= (CLK_source >> 4);
    /* Store the new value */
    RCC->RDSEL1 = reg_value;

}

/**
*\*\name    RCC_EnableLPTIM2CompGate.
*\*\fun     Enable gate signal from COMPx to LPTIM2.
*\*\param   COMP_sel(select one COMPx) :
*\*\        -RCC_GATEEN_LPTIM2_COMP1
*\*\        -RCC_GATEEN_LPTIM2_COMP2
*\*\        -RCC_GATEEN_LPTIM2_COMP3
*\*\        -RCC_GATEEN_LPTIM2_COMP4
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note    If the LPTIM clock source is COMP, you need to enable this gate
**/
void RCC_EnableLPTIM2CompGate(uint32_t COMP_sel, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->RDCTRL1 |= COMP_sel;
    }
    else
    {
        RCC->RDCTRL1 &= ~COMP_sel;
    }

}

/**
*\*\name    RCC_ConfigLPTIM3Clk.
*\*\fun     Config the LPTIM3 clock source.
*\*\param   CLK_source:
*\*\     - RCC_LPTIMCLK_SRC_APB5
*\*\     - RCC_LPTIMCLK_SRC_LSI
*\*\     - RCC_LPTIMCLK_SRC_LSE
*\*\     - RCC_LPTIMCLK_SRC_HSE
*\*\     - RCC_LPTIMCLK_SRC_HSI
*\*\     - RCC_LPTIMCLK_SRC_MSI
*\*\     - RCC_LPTIMCLK_SRC_COMP1
*\*\     - RCC_LPTIMCLK_SRC_COMP2
*\*\     - RCC_LPTIMCLK_SRC_COMP3
*\*\     - RCC_LPTIMCLK_SRC_COMP4
*\*\return  none
*\*\note  none
**/
void RCC_ConfigLPTIM3Clk(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->RDSEL1;
    /* Clear LPTIM3SEL[3:0] bits */
    reg_value &= RCC_LPTIM3CLK_SRC_MASK;
    /* Set LPTIM3SEL[3:0] bits according to CLK_source value */
    reg_value |= (CLK_source >> 8);
    /* Store the new value */
    RCC->RDSEL1 = reg_value;

}

/**
*\*\name    RCC_EnableLPTIM3CompGate.
*\*\fun     Enable gate signal from COMPx to LPTIM3.
*\*\param   COMP_sel(select one COMPx) :
*\*\        -RCC_GATEEN_LPTIM3_COMP1
*\*\        -RCC_GATEEN_LPTIM3_COMP2
*\*\        -RCC_GATEEN_LPTIM3_COMP3
*\*\        -RCC_GATEEN_LPTIM3_COMP4
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note    If the LPTIM clock source is COMP, you need to enable this gate
**/
void RCC_EnableLPTIM3CompGate(uint32_t COMP_sel, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->RDCTRL2 |= COMP_sel;
    }
    else
    {
        RCC->RDCTRL2 &= ~COMP_sel;
    }

}

/**
*\*\name    RCC_ConfigLPTIM4Clk.
*\*\fun     Config the LPTIM4 clock source.
*\*\param   CLK_source:
*\*\     - RCC_LPTIMCLK_SRC_APB5
*\*\     - RCC_LPTIMCLK_SRC_LSI
*\*\     - RCC_LPTIMCLK_SRC_LSE
*\*\     - RCC_LPTIMCLK_SRC_HSE
*\*\     - RCC_LPTIMCLK_SRC_HSI
*\*\     - RCC_LPTIMCLK_SRC_MSI
*\*\     - RCC_LPTIMCLK_SRC_COMP1
*\*\     - RCC_LPTIMCLK_SRC_COMP2
*\*\     - RCC_LPTIMCLK_SRC_COMP3
*\*\     - RCC_LPTIMCLK_SRC_COMP4
*\*\return  none
*\*\note  none
**/
void RCC_ConfigLPTIM4Clk(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->RDSEL1;
    /* Clear LPTIM4SEL[3:0] bits */
    reg_value &= RCC_LPTIM4CLK_SRC_MASK;
    /* Set LPTIM4SEL[3:0] bits according to CLK_source value */
    reg_value |= (CLK_source >> 12);
    /* Store the new value */
    RCC->RDSEL1 = reg_value;

}

/**
*\*\name    RCC_EnableLPTIM4CompGate.
*\*\fun     Enable gate signal from COMPx to LPTIM4.
*\*\param   COMP_sel(select one COMPx) :
*\*\        -RCC_GATEEN_LPTIM4_COMP1
*\*\        -RCC_GATEEN_LPTIM4_COMP2
*\*\        -RCC_GATEEN_LPTIM4_COMP3
*\*\        -RCC_GATEEN_LPTIM4_COMP4
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note    If the LPTIM clock source is COMP, you need to enable this gate
**/
void RCC_EnableLPTIM4CompGate(uint32_t COMP_sel, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->RDCTRL2 |= COMP_sel;
    }
    else
    {
        RCC->RDCTRL2 &= ~COMP_sel;
    }

}

/**
*\*\name    RCC_ConfigLPTIM5Clk.
*\*\fun     Config the LPTIM5 clock source.
*\*\param   CLK_source:
*\*\     - RCC_LPTIMCLK_SRC_APB5
*\*\     - RCC_LPTIMCLK_SRC_LSI
*\*\     - RCC_LPTIMCLK_SRC_LSE
*\*\     - RCC_LPTIMCLK_SRC_HSE
*\*\     - RCC_LPTIMCLK_SRC_HSI
*\*\     - RCC_LPTIMCLK_SRC_MSI
*\*\     - RCC_LPTIMCLK_SRC_COMP1
*\*\     - RCC_LPTIMCLK_SRC_COMP2
*\*\     - RCC_LPTIMCLK_SRC_COMP3
*\*\     - RCC_LPTIMCLK_SRC_COMP4
*\*\return  none
*\*\note  none
**/
void RCC_ConfigLPTIM5Clk(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->RDSEL1;
    /* Clear LPTIM5SEL[3:0] bits */
    reg_value &= RCC_LPTIM5CLK_SRC_MASK;
    /* Set LPTIM5SEL[3:0] bits according to CLK_source value */
    reg_value |= (CLK_source >> 16);
    /* Store the new value */
    RCC->RDSEL1 = reg_value;

}

/**
*\*\name    RCC_EnableLPTIM5CompGate.
*\*\fun     Enable gate signal from COMPx to LPTIM5.
*\*\param   COMP_sel(select one COMPx) :
*\*\        -RCC_GATEEN_LPTIM5_COMP1
*\*\        -RCC_GATEEN_LPTIM5_COMP2
*\*\        -RCC_GATEEN_LPTIM5_COMP3
*\*\        -RCC_GATEEN_LPTIM5_COMP4
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note    If the LPTIM clock source is COMP, you need to enable this gate
**/
void RCC_EnableLPTIM5CompGate(uint32_t COMP_sel, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->RDCTRL3 |= COMP_sel;
    }
    else
    {
        RCC->RDCTRL3 &= ~COMP_sel;
    }

}

/**
*\*\name    RCC_ConfigLPUART1ClkSource.
*\*\fun     Config the LPUART1 kernel clock Source.
*\*\param   CLK_source:
*\*\       - RCC_LPUARTCLK_SRC_SYSBUSDIV
*\*\       - RCC_LPUARTCLK_SRC_HSI
*\*\       - RCC_LPUARTCLK_SRC_LSE
*\*\       - RCC_LPUARTCLK_SRC_HSE
*\*\       - RCC_LPUARTCLK_SRC_MSI
*\*\return  none
*\*\note  if select RCC_LPUARTCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by LPUARTDIV[2:0]
**/
void RCC_ConfigLPUART1ClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->RDSEL1;
    /* Clear LPUART1SEL[2:0] bits */
    reg_value &= RCC_LPUART1CLK_SRC_MASK;
    /* Set LPUART1SEL[2:0] bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->RDSEL1 = reg_value;
}

/**
*\*\name    RCC_ConfigLPUART2ClkSource.
*\*\fun     Config the LPUART2 kernel clock Source.
*\*\param   CLK_source:
*\*\       - RCC_LPUARTCLK_SRC_SYSBUSDIV
*\*\       - RCC_LPUARTCLK_SRC_HSI
*\*\       - RCC_LPUARTCLK_SRC_LSE
*\*\       - RCC_LPUARTCLK_SRC_HSE
*\*\       - RCC_LPUARTCLK_SRC_MSI
*\*\return  none
*\*\note  if select RCC_LPUARTCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by LPUARTDIV[2:0]
**/
void RCC_ConfigLPUART2ClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->RDSEL1;
    /* Clear LPUART2SEL[2:0] bits */
    reg_value &= RCC_LPUART2CLK_SRC_MASK;
    /* Set LPUART2SEL[2:0] bits according to CLK_source value */
    reg_value |= (CLK_source >> 4);
    /* Store the new value */
    RCC->RDSEL1 = reg_value;

}

/**
*\*\name    RCC_ConfigLPUART1_2_ClkDivider.
*\*\fun     Config the LPUART1/2 kernel clock system divider.
*\*\param   CLK_divider:
*\*\       - RCC_LPUARTCLK_SYSBUSDIV1
*\*\       - RCC_LPUARTCLK_SYSBUSDIV2
*\*\       - RCC_LPUARTCLK_SYSBUSDIV4
*\*\       - RCC_LPUARTCLK_SYSBUSDIV8
*\*\       - RCC_LPUARTCLK_SYSBUSDIV16
*\*\return  none
*\*\note  if select RCC_LPUARTCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by LPUARTDIV[2:0]
**/
void RCC_ConfigLPUART1_2_ClkDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->RDDIV1;
    /* Clear LPUARTDIV[2:0] bits */
    reg_value &=  RCC_LPUARTCLK_SYSBUSDIV_MASK;
    /* Set the LPUARTDIV[2:0] bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->RDDIV1 = reg_value;

}


/**
*\*\name    RCC_ConfigCOMPLsxClk.
*\*\fun     Config the COMP low speed clock source.
*\*\param   CLK_source:
*\*\     - RCC_COMPLSXCLK_SRC_LSI
*\*\     - RCC_COMPLSXCLK_SRC_LSE
*\*\return  none
*\*\note  none
**/
void RCC_ConfigCOMPLsxClk(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->RDSEL1;
    /* Clear COMPSEL bits */
    reg_value &= RCC_COMPLSXCLK_SRC_MASK;
    /* Set COMPSEL bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->RDSEL1 = reg_value;

}

/**
*\*\name    RCC_ConfigCOMPKerClk.
*\*\fun     Config the COMP kernel clock divider from sys_bus_div_clk.
*\*\param   CLK_divider
*\*\       - RCC_COMPKERCLK_SYSBUSDIV1
*\*\       - RCC_COMPKERCLK_SYSBUSDIV2
*\*\       - RCC_COMPKERCLK_SYSBUSDIV4
*\*\       - RCC_COMPKERCLK_SYSBUSDIV8
*\*\       - RCC_COMPKERCLK_SYSBUSDIV16
*\*\return  none
*\*\note   none
**/
void RCC_ConfigCOMPKerClk(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->RDDIV1;
    /* Clear COMPDIV[2:0] bits */
    reg_value &=  RCC_COMPKERCLK_SYSBUSDIV_MASK;
    /* Set the COMPDIV[2:0] bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->RDDIV1 = reg_value;
}

/**
*\*\name    RCC_ConfigFEMCM0Clk.
*\*\fun     Config the FEMC M0 clock.
*\*\param   CLK_source:
*\*\       - RCC_FEMCCLK_SRC_AXIDIV
*\*\       - RCC_FEMCCLK_SRC_PERIPH
*\*\       - RCC_FEMCCLK_SRC_PLL2C
*\*\       - RCC_FEMCCLK_SRC_PLL3B
*\*\       - RCC_FEMCCLK_SRC_PLL1B
*\*\param   CLK_divider:
*\*\       - RCC_FEMCCLK_AXIDIV1
*\*\       - RCC_FEMCCLK_AXIDIV2
*\*\       - RCC_FEMCCLK_AXIDIV3
*\*\       - RCC_FEMCCLK_AXIDIV4
*\*\       - RCC_FEMCCLK_AXIDIV5
*\*\       - RCC_FEMCCLK_AXIDIV6
*\*\       - RCC_FEMCCLK_AXIDIV7
*\*\       - RCC_FEMCCLK_AXIDIV8
*\*\       - RCC_FEMCCLK_AXIDIV9
*\*\       - RCC_FEMCCLK_AXIDIV10
*\*\       - RCC_FEMCCLK_AXIDIV11
*\*\       - RCC_FEMCCLK_AXIDIV12
*\*\       - RCC_FEMCCLK_AXIDIV13
*\*\       - RCC_FEMCCLK_AXIDIV14
*\*\       - RCC_FEMCCLK_AXIDIV15
*\*\return  none
*\*\note  if select RCC_FEMCCLK_SRC_AXIDIV then set the AXI clock divider by FEMCM0SYSDIV[3:0]
**/
void RCC_ConfigFEMCM0Clk(uint32_t CLK_source, uint32_t CLK_divider)
{
    uint32_t reg_value;
    uint32_t reg_value1;

    reg_value = RCC->AXISEL2;
    /* Clear FEMCM0SEL[2:0] bits */
    reg_value &= RCC_FEMCM0CLK_SRC_MASK;
    /* Set FEMCM0SEL[2:0] bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->AXISEL2 = reg_value;

    if(CLK_source == RCC_FEMCCLK_SRC_AXIDIV)
    {
        reg_value1 = RCC->AXIDIV2;
        /* Clear FEMCM0AXIDIV[3:0] bits */
        reg_value1 &=  RCC_FEMCM0CLK_AXIDIV_MASK;
        /* Set the FEMCM0AXIDIV[3:0] bits */
        reg_value1 |=  CLK_divider;
        /* Store the new value */
        RCC->AXIDIV2 = reg_value1;
    }

}

/**
*\*\name    RCC_ConfigFEMCM1Clk.
*\*\fun     Config the FEMC M1 clock.
*\*\param   CLK_source:
*\*\       - RCC_FEMCCLK_SRC_AXIDIV
*\*\       - RCC_FEMCCLK_SRC_PERIPH
*\*\       - RCC_FEMCCLK_SRC_PLL2C
*\*\       - RCC_FEMCCLK_SRC_PLL3B
*\*\       - RCC_FEMCCLK_SRC_PLL1B
*\*\param   CLK_divider:
*\*\       - RCC_FEMCCLK_AXIDIV1
*\*\       - RCC_FEMCCLK_AXIDIV2
*\*\       - RCC_FEMCCLK_AXIDIV3
*\*\       - RCC_FEMCCLK_AXIDIV4
*\*\       - RCC_FEMCCLK_AXIDIV5
*\*\       - RCC_FEMCCLK_AXIDIV6
*\*\       - RCC_FEMCCLK_AXIDIV7
*\*\       - RCC_FEMCCLK_AXIDIV8
*\*\       - RCC_FEMCCLK_AXIDIV9
*\*\       - RCC_FEMCCLK_AXIDIV10
*\*\       - RCC_FEMCCLK_AXIDIV11
*\*\       - RCC_FEMCCLK_AXIDIV12
*\*\       - RCC_FEMCCLK_AXIDIV13
*\*\       - RCC_FEMCCLK_AXIDIV14
*\*\       - RCC_FEMCCLK_AXIDIV15
*\*\return  none
*\*\note  if select RCC_FEMCCLK_SRC_AXIDIV then set the AXI clock divider by FEMCM1SYSDIV[3:0]
**/
void RCC_ConfigFEMCM1Clk(uint32_t CLK_source, uint32_t CLK_divider)
{
    uint32_t reg_value;
    uint32_t reg_value1;

    reg_value = RCC->AXISEL2;
    /* Clear FEMCM1SEL[2:0] bits */
    reg_value &= RCC_FEMCM1CLK_SRC_MASK;
    /* Set FEMCM1SEL[2:0] bits according to CLK_source value */
    reg_value |= (CLK_source << 4);
    /* Store the new value */
    RCC->AXISEL2 = reg_value;

    if(CLK_source == RCC_FEMCCLK_SRC_AXIDIV)
    {
        reg_value1 = RCC->AXIDIV2;
        /* Clear FEMCM1AXIDIV[3:0] bits */
        reg_value1 &=  RCC_FEMCM1CLK_AXIDIV_MASK;
        /* Set the FEMCM1AXIDIV[3:0] bits */
        reg_value1 |=  (CLK_divider << 4);
        /* Store the new value */
        RCC->AXIDIV2 = reg_value1;
    }

}

/**
*\*\name    RCC_ConfigDSIRefClk.
*\*\fun     Config the DSI reference clock divider from HSE.
*\*\param   CLK_divider:
*\*\       - RCC_DSIREFCLK_HSE_DIV1
*\*\       - RCC_DSIREFCLK_HSE_DIV2
*\*\return  none
*\*\note   none
**/
void RCC_ConfigDSIRefClk(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->CFG5;
    /* Clear DSIHSEDIV[3:0] bits */
    reg_value &=  RCC_DSIREFCLK_HSE_DIV_MASK;
    /* Set the DSIHSEDIV[3:0] bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->CFG5 = reg_value;

}

/**
*\*\name    RCC_ConfigDSIKerClk.
*\*\fun     Config the DSI kernel clock divider from HSE.
*\*\param   CLK_source:
*\*\       - RCC_DSIKERCLK_SRC_REF
*\*\       - RCC_DSIKERCLK_SRC_PLL3C
*\*\return  none
*\*\note   none
**/
void RCC_ConfigDSIKerClk(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->AXISEL1;
    /* Clear DSIKERSEL[1:0] bits */
    reg_value &=  RCC_DSIKERCLK_SRC_MASK;
    /* Set the DSIKERSEL[1:0] bits */
    reg_value |=  CLK_source;
    /* Store the new value */
    RCC->AXISEL1 = reg_value;

}

/**
*\*\name    RCC_ConfigDSIPpitxClk.
*\*\fun     Config the DSI PPI TXCLKESC clock.
*\*\param   CLK_source:
*\*\       - RCC_DSIPPICLK_SRC_REFDIV
*\*\       - RCC_DSIPPICLK_SRC_PLL2B
*\*\       - RCC_DSIPPICLK_SRC_PERIPH
*\*\       - RCC_DSIPPICLK_SRC_AXIDIV
*\*\param   CLK_divider:
*\*\       - RCC_DSIPPICLK_DIV1
*\*\       - RCC_DSIPPICLK_DIV2
*\*\       - RCC_DSIPPICLK_DIV4
*\*\       - RCC_DSIPPICLK_DIV8
*\*\       - RCC_DSIPPICLK_DIV16
*\*\       - RCC_DSIPPICLK_DIV32
*\*\       - RCC_DSIPPICLK_DIV64
*\*\       - RCC_DSIPPICLK_DIV128
*\*\       - RCC_DSIPPICLK_DIV256
*\*\       - RCC_DSIPPICLK_DIV512
*\*\return  none
*\*\note  if select RCC_DSIPPICLK_SRC_REFDIV then set the REF clock divider by DSIREFDIV[3:0],
*\*\      if select RCC_DSIPPICLK_SRC_AXIDIV then set the AXI clock divider by DSIAXIPPIDIV[3:0]
**/
void RCC_ConfigDSIPpitxClk(uint32_t CLK_source, uint32_t CLK_divider)
{
    uint32_t reg_value;
    uint32_t reg_value1;

    reg_value = RCC->AXISEL1;
    /* Clear DSIPPITXSEL[1:0] bits */
    reg_value &=  RCC_DSIPPICLK_SRC_MASK;
    /* Set DSIPPITXSEL[1:0] bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->AXISEL1 = reg_value;

    if(CLK_source == RCC_DSIPPICLK_SRC_REFDIV)
    {
        reg_value1 = RCC->AXIDIV1;
        /* Clear DSIREFDIV[3:0] bits */
        reg_value1 &=  RCC_DSIPPICLK_REFDIV_MASK;
        /* Set the DSIREFDIV[3:0] bits */
        reg_value1 |=  CLK_divider;
        /* Store the new value */
        RCC->AXIDIV1 = reg_value1;
    }
    else if(CLK_source == RCC_DSIPPICLK_SRC_AXIDIV)
    {
        reg_value1 = RCC->AXIDIV2;
        /* Clear DSIAXIPPIDIV[3:0] bits */
        reg_value1 &=  RCC_DSIPPICLK_AXIDIV_MASK;
        /* Set the DSIAXIPPIDIV[3:0] bits */
        reg_value1 |=  (CLK_divider << 4);
        /* Store the new value */
        RCC->AXIDIV2 = reg_value1;
    }
    else
    {
        /* no process */
    }

}

/**
*\*\name    RCC_ConfigDSIUlpsClk.
*\*\fun     Config the DSI ULPS TXCLKESC clock.
*\*\param   CLK_source:
*\*\       - RCC_DSIULPSCLK_SRC_REFDIV
*\*\       - RCC_DSIULPSCLK_SRC_PLL3C
*\*\param   CLK_divider:
*\*\       - RCC_DSIULPSCLK_REFDIV1
*\*\       - RCC_DSIULPSCLK_REFDIV2
*\*\       - RCC_DSIULPSCLK_REFDIV4
*\*\       - RCC_DSIULPSCLK_REFDIV8
*\*\       - RCC_DSIULPSCLK_REFDIV16
*\*\       - RCC_DSIULPSCLK_REFDIV32
*\*\       - RCC_DSIULPSCLK_REFDIV64
*\*\       - RCC_DSIULPSCLK_REFDIV128
*\*\       - RCC_DSIULPSCLK_REFDIV256
*\*\       - RCC_DSIULPSCLK_REFDIV512
*\*\return  none
*\*\note  if select RCC_DSIULPSCLK_SRC_REFDIV then set the REF clock divider by DSIREFULPSDIV[3:0]
**/
void RCC_ConfigDSIUlpsClk(uint32_t CLK_source, uint32_t CLK_divider)
{
    uint32_t reg_value;
    uint32_t reg_value1;

    reg_value = RCC->AXISEL1;
    /* Clear DSIULPSSEL[1:0] bits */
    reg_value &= RCC_DSIULPSCLK_SRC_MASK;
    /* Set DSIULPSSEL[1:0] bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->AXISEL1 = reg_value;

    if(CLK_source == RCC_DSIULPSCLK_SRC_REFDIV)
    {
        reg_value1 = RCC->AXIDIV2;
        /* Clear DSIREFULPSDIV[3:0] bits */
        reg_value1 &=  RCC_DSIULPSCLK_REFDIV_MASK;
        /* Set the DSIREFULPSDIV[3:0] bits */
        reg_value1 |=  CLK_divider;
        /* Store the new value */
        RCC->AXIDIV2 = reg_value1;
    }

}

/**
*\*\name    RCC_ConfigLCDCPixelClk.
*\*\fun     Config the LCDC pixel clock.
*\*\param   CLK_source:
*\*\       - RCC_LCDCPIXELCLK_SRC_AXIDIV
*\*\       - RCC_LCDCPIXELCLK_SRC_PERIPH
*\*\       - RCC_LCDCPIXELCLK_SRC_PLL2C
*\*\       - RCC_LCDCPIXELCLK_SRC_PLL3B
*\*\param   CLK_divider:
*\*\       - RCC_LCDCPIXELCLK_AXIDIV1
*\*\       - RCC_LCDCPIXELCLK_AXIDIV2
*\*\       - RCC_LCDCPIXELCLK_AXIDIV4
*\*\       - RCC_LCDCPIXELCLK_AXIDIV8
*\*\       - RCC_LCDCPIXELCLK_AXIDIV16
*\*\       - RCC_LCDCPIXELCLK_AXIDIV32
*\*\       - RCC_LCDCPIXELCLK_AXIDIV64
*\*\       - RCC_LCDCPIXELCLK_AXIDIV128
*\*\       - RCC_LCDCPIXELCLK_AXIDIV256
*\*\       - RCC_LCDCPIXELCLK_AXIDIV512
*\*\return  none
*\*\note  if select RCC_LCDCPIXELCLK_SRC_AXIDIV then set the AXI clock divider by LCDCAXIDIV[3:0]
**/
void RCC_ConfigLCDCPixelClk(uint32_t CLK_source, uint32_t CLK_divider)
{
    uint32_t reg_value;
    uint32_t reg_value1;

    reg_value = RCC->AXISEL1;
    /* Clear LCDCKERSEL[1:0] bits */
    reg_value &= RCC_LCDCPIXELCLK_SRC_MASK;
    /* Set LCDCKERSEL[1:0] bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->AXISEL1 = reg_value;

    if(CLK_source == RCC_LCDCPIXELCLK_SRC_AXIDIV)
    {
        reg_value1 = RCC->AXIDIV1;
        /* Clear LCDCAXIDIV[3:0] bits */
        reg_value1 &=  RCC_LCDCPIXELCLK_AXIDIV_MASK;
        /* Set the LCDCAXIDIV[3:0] bits */
        reg_value1 |=  CLK_divider;
        /* Store the new value */
        RCC->AXIDIV1 = reg_value1;
    }

}

/**
*\*\name    RCC_ConfigDVP1MClkSource.
*\*\fun     Config the DVP1 M clock source.
*\*\param   CLK_source:
*\*\       - RCC_DVPMCLK_SRC_AXIDIV
*\*\       - RCC_DVPMCLK_SRC_PERIPH
*\*\       - RCC_DVPMCLK_SRC_PLL2C
*\*\       - RCC_DVPMCLK_SRC_PLL3A
*\*\return  none
*\*\note  if select RCC_DVPMCLK_SRC_AXIDIV then set the AXI clock divider by DVPMAXIDIV[3:0]
**/
void RCC_ConfigDVP1MClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->AXISEL1;
    /* Clear DVP1MSEL[1:0] bits */
    reg_value &= RCC_DVP1MCLK_SRC_MASK;
    /* Set DVP1MSEL[1:0] bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->AXISEL1 = reg_value;

}

/**
*\*\name    RCC_ConfigDVP2MClkSource.
*\*\fun     Config the DVP2 M clock source.
*\*\param   CLK_source:
*\*\       - RCC_DVPMCLK_SRC_AXIDIV
*\*\       - RCC_DVPMCLK_SRC_PERIPH
*\*\       - RCC_DVPMCLK_SRC_PLL2C
*\*\       - RCC_DVPMCLK_SRC_PLL3A
*\*\return  none
*\*\note  if select RCC_DVPMCLK_SRC_AXIDIV then set the AXI clock divider by DVPMAXIDIV[3:0]
**/
void RCC_ConfigDVP2MClkSource(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->AXISEL1;
    /* Clear DVP2MSEL[1:0] bits */
    reg_value &= RCC_DVP2MCLK_SRC_MASK;
    /* Set DVP2MSEL[1:0] bits according to CLK_source value */
    reg_value |= (CLK_source >> 2);
    /* Store the new value */
    RCC->AXISEL1 = reg_value;

}

/**
*\*\name    RCC_ConfigDVP1_2_MClkDivider.
*\*\fun     Config the DVP1/2 M clock AXI divider.
*\*\param   CLK_divider:
*\*\       - RCC_DVPMCLK_AXIDIV1
*\*\       - RCC_DVPMCLK_AXIDIV2
*\*\       - RCC_DVPMCLK_AXIDIV4
*\*\       - RCC_DVPMCLK_AXIDIV8
*\*\       - RCC_DVPMCLK_AXIDIV16
*\*\       - RCC_DVPMCLK_AXIDIV32
*\*\       - RCC_DVPMCLK_AXIDIV64
*\*\       - RCC_DVPMCLK_AXIDIV128
*\*\       - RCC_DVPMCLK_AXIDIV256
*\*\       - RCC_DVPMCLK_AXIDIV512
*\*\return  none
**/
void RCC_ConfigDVP1_2_MClkDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->AXIDIV1;
    /* Clear DVPMAXIDIV[3:0] bits */
    reg_value &=  RCC_DVPMCLK_AXIDIV_MASK;
    /* Set the DVPMAXIDIV[3:0] bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->AXIDIV1 = reg_value;
}

/**
*\*\name    RCC_ConfigXSPI1SSIClk.
*\*\fun     Config the XSPI1 SSI clock.
*\*\param   CLK_source:
*\*\       - RCC_XSPISSICLK_SRC_AXI
*\*\       - RCC_XSPISSICLK_SRC_PLL3C
*\*\       - RCC_XSPISSICLK_SRC_PLL1B
*\*\       - RCC_XSPISSICLK_SRC_PLL2A
*\*\       - RCC_XSPISSICLK_SRC_PLL2C
*\*\return  none
**/
void RCC_ConfigXSPI1SSIClk(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->AXISEL1;
    /* Clear XSPI1SSISEL[2:0] bits */
    reg_value &= RCC_XSPI1SSICLK_SRC_MASK;
    /* Set XSPI1SSISEL[2:0] bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->AXISEL1 = reg_value;

}

/**
*\*\name    RCC_ConfigXSPI2SSIClk.
*\*\fun     Config the XSPI2 SSI clock.
*\*\param   CLK_source:
*\*\       - RCC_XSPISSICLK_SRC_AXI
*\*\       - RCC_XSPISSICLK_SRC_PLL3C
*\*\       - RCC_XSPISSICLK_SRC_PLL1B
*\*\       - RCC_XSPISSICLK_SRC_PLL2A
*\*\       - RCC_XSPISSICLK_SRC_PLL2C
*\*\return  none
**/
void RCC_ConfigXSPI2SSIClk(uint32_t CLK_source)
{
    uint32_t reg_value;

    reg_value = RCC->AXISEL1;
    /* Clear XSPI2SSISEL[2:0] bits */
    reg_value &= RCC_XSPI2SSICLK_SRC_MASK;
    /* Set XSPI2SSISEL[2:0] bits according to CLK_source value */
    reg_value |= (CLK_source >> 4);
    /* Store the new value */
    RCC->AXISEL1 = reg_value;

}

/**
*\*\name    RCC_ConfigSDRAMMemClk.
*\*\fun     Config the SDRAM memory clock.
*\*\param   CLK_source:
*\*\       - RCC_SDRAMMEMCLK_SRC_AXIDIV
*\*\       - RCC_SDRAMMEMCLK_SRC_PERIPH
*\*\       - RCC_SDRAMMEMCLK_SRC_PLL2A
*\*\       - RCC_SDRAMMEMCLK_SRC_PLL3A
*\*\       - RCC_SDRAMMEMCLK_SRC_PLL1B
*\*\param   CLK_divider:
*\*\       - RCC_SDRAMMEMCLK_AXIDIV1
*\*\       - RCC_SDRAMMEMCLK_AXIDIV2
*\*\       - RCC_SDRAMMEMCLK_AXIDIV4
*\*\       - RCC_SDRAMMEMCLK_AXIDIV8
*\*\       - RCC_SDRAMMEMCLK_AXIDIV16
*\*\       - RCC_SDRAMMEMCLK_AXIDIV32
*\*\       - RCC_SDRAMMEMCLK_AXIDIV64
*\*\       - RCC_SDRAMMEMCLK_AXIDIV128
*\*\       - RCC_SDRAMMEMCLK_AXIDIV256
*\*\       - RCC_SDRAMMEMCLK_AXIDIV512
*\*\return  none
*\*\note  if select RCC_SDRAMMEMCLK_SRC_AXIDIV then set the AXI clock divider by SDRAMMEMDIV[3:0]
**/
void RCC_ConfigSDRAMMemClk(uint32_t CLK_source, uint32_t CLK_divider)
{
    uint32_t reg_value;
    uint32_t reg_value1;

    reg_value = RCC->AXISEL2;
    /* Clear SDRAMMEMSEL[2:0] bits */
    reg_value &= RCC_SDRAMMEMCLK_SRC_MASK;
    /* Set SDRAMMEMSEL[2:0] bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->AXISEL2 = reg_value;

    if(CLK_source == RCC_SDRAMMEMCLK_SRC_AXIDIV)
    {
        reg_value1 = RCC->AXIDIV2;
        /* Clear SDRAMMEMDIV[3:0] bits */
        reg_value1 &=  RCC_SDRAMMEMCLK_AXIDIV_MASK;
        /* Set the SDRAMMEMDIV[3:0] bits */
        reg_value1 |=  CLK_divider;
        /* Store the new value */
        RCC->AXIDIV2 = reg_value1;
    }

}

/**
*\*\name    RCC_ConfigETHERCATKerClk.
*\*\fun     Config the ETHERCAT kernel clock.
*\*\param   CLK_source:
*\*\       - RCC_ESCKERCLK_SRC_SYSBUSDIV
*\*\       - RCC_ESCKERCLK_SRC_PLL2B
*\*\       - RCC_ESCKERCLK_SRC_PLL3A
*\*\       - RCC_ESCKERCLK_SRC_PLL3C
*\*\       - RCC_ESCKERCLK_SRC_PLL1B
*\*\param   CLK_divider:
*\*\       - RCC_ESCKERCLK_SYSBUSDIV1
*\*\       - RCC_ESCKERCLK_SYSBUSDIV2
*\*\       - RCC_ESCKERCLK_SYSBUSDIV4
*\*\       - RCC_ESCKERCLK_SYSBUSDIV8
*\*\       - RCC_ESCKERCLK_SYSBUSDIV16
*\*\       - RCC_ESCKERCLK_SYSBUSDIV32
*\*\       - RCC_ESCKERCLK_SYSBUSDIV64
*\*\       - RCC_ESCKERCLK_SYSBUSDIV128
*\*\       - RCC_ESCKERCLK_SYSBUSDIV256
*\*\       - RCC_ESCKERCLK_SYSBUSDIV512
*\*\return  none
*\*\note  if select RCC_ESCKERCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by ESCSYSDIV[3:0]
*\*\note  You need to make sure that the ETHERCAT kernel clock frequency is 100MHz
**/
void RCC_ConfigETHERCATKerClk(uint32_t CLK_source, uint32_t CLK_divider)
{
    uint32_t reg_value;
    uint32_t reg_value1;

    reg_value = RCC->AHB9SEL1;
    /* Clear ESCKERSEL[2:0] bits */
    reg_value &= RCC_ESCKERCLK_SRC_MASK;
    /* Set ESCKERSEL[2:0] bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->AHB9SEL1 = reg_value;

    if(CLK_source == RCC_ESCKERCLK_SRC_SYSBUSDIV)
    {
        reg_value1 = RCC->AHB9DIV1;
        /* Clear ESCSYSDIV[3:0] bits */
        reg_value1 &=  RCC_ESCKERCLK_SYSBUSDIV_MASK;
        /* Set the ESCSYSDIV[3:0] bits */
        reg_value1 |=  CLK_divider;
        /* Store the new value */
        RCC->AHB9DIV1 = reg_value1;
    }

}

/**
*\*\name    RCC_ConfigTRNGClk.
*\*\fun     Config the TRNG clock.
*\*\param   CLK_source:
*\*\       - RCC_TRNGCLK_SRC_SYSBUSDIV
*\*\       - RCC_TRNGCLK_SRC_HSI
*\*\param   CLK_divider:
*\*\       - RCC_TRNGCLK_SYSBUSDIV1
*\*\       - RCC_TRNGCLK_SYSBUSDIV2
*\*\       - RCC_TRNGCLK_SYSBUSDIV4
*\*\       - RCC_TRNGCLK_SYSBUSDIV8
*\*\       - RCC_TRNGCLK_SYSBUSDIV16
*\*\       - RCC_TRNGCLK_SYSBUSDIV32
*\*\       - RCC_TRNGCLK_SYSBUSDIV64
*\*\       - RCC_TRNGCLK_SYSBUSDIV128
*\*\       - RCC_TRNGCLK_SYSBUSDIV256
*\*\       - RCC_TRNGCLK_SYSBUSDIV512
*\*\return  none
*\*\note  if select RCC_TRNGCLK_SRC_SYSBUSDIV then set the (sys_bus_div_clk) divider by TRNGDIV[3:0]
**/
void RCC_ConfigTRNGClk(uint32_t CLK_source, uint32_t CLK_divider)
{
    uint32_t reg_value;
    uint32_t reg_value1;

    reg_value = RCC->CFG5;
    /* Clear TRNGSEL bits */
    reg_value &= RCC_TRNGCLK_SRC_MASK;
    /* Set TRNGSEL bits according to CLK_source value */
    reg_value |= CLK_source;
    /* Store the new value */
    RCC->CFG5 = reg_value;

    if(CLK_source == RCC_TRNGCLK_SRC_SYSBUSDIV)
    {
        reg_value1 = RCC->CFG5;
        /* Clear TRNGDIV[3:0] bits */
        reg_value1 &=  RCC_TRNGCLK_SYSBUSDIV_MASK;
        /* Set the TRNGDIV[3:0] bits */
        reg_value1 |=  CLK_divider;
        /* Store the new value */
        RCC->CFG5 = reg_value1;
    }

}

/**
*\*\name    RCC_EnableTRNGClk.
*\*\fun     Enables the TRNG clock.
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableTRNGClk(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        RCC->CFG5 |= RCC_TRNG_ENABLE;
    }
    else
    {
        RCC->CFG5 &= (~RCC_TRNG_ENABLE);
    }
}

/**
*\*\name    RCC_EnableCFG2PeriphClk1.
*\*\fun     Enables the CFG2 register peripheral clock.
*\*\param   CFG2_periph (CFG2 peripheral to gates its clock):
*\*\     - RCC_CFG2_PERIPHEN_M4_CAHI
*\*\     - RCC_CFG2_PERIPHEN_M4_CAHIPCLK
*\*\     - RCC_CFG2_PERIPHEN_M4_CAHD
*\*\     - RCC_CFG2_PERIPHEN_M4_CAHDPCLK
*\*\     - RCC_CFG2_PERIPHEN_M7_MMU
*\*\     - RCC_CFG2_PERIPHEN_M7_MMULP
*\*\     - RCC_CFG2_PERIPHEN_M4_MMU
*\*\     - RCC_CFG2_PERIPHEN_M4_MMULP
*\*\     - RCC_CFG2_PERIPHEN_M7_SRAMBKP
*\*\     - RCC_CFG2_PERIPHEN_M4_SRAMBKP
*\*\     - RCC_CFG2_PERIPHEN_M7_SRAMBKPLP
*\*\     - RCC_CFG2_PERIPHEN_M4_SRAMBKPLP
*\*\     - RCC_CFG2_PERIPHEN_M7_SRAM1
*\*\     - RCC_CFG2_PERIPHEN_M4_SRAM1
*\*\     - RCC_CFG2_PERIPHEN_M7_SRAM1LP
*\*\     - RCC_CFG2_PERIPHEN_M4_SRAM1LP
*\*\     - RCC_CFG2_PERIPHEN_M7_SRAM2
*\*\     - RCC_CFG2_PERIPHEN_M4_SRAM2
*\*\     - RCC_CFG2_PERIPHEN_M7_SRAM2LP
*\*\     - RCC_CFG2_PERIPHEN_M4_SRAM2LP
*\*\     - RCC_CFG2_PERIPHEN_M7_SRAM3
*\*\     - RCC_CFG2_PERIPHEN_M4_SRAM3
*\*\     - RCC_CFG2_PERIPHEN_M7_SRAM3LP
*\*\     - RCC_CFG2_PERIPHEN_M4_SRAM3LP
*\*\     - RCC_CFG2_PERIPHEN_M7_SRAM4
*\*\     - RCC_CFG2_PERIPHEN_M4_SRAM4
*\*\     - RCC_CFG2_PERIPHEN_M7_SRAM4LP
*\*\     - RCC_CFG2_PERIPHEN_M4_SRAM4LP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableCFG2PeriphClk1(uint32_t CFG2_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->CFG2 |= CFG2_periph;
    }
    else
    {
        RCC->CFG2 &= ~CFG2_periph;
    }
}


/**
*\*\name    RCC_EnableCFG4PeriphClk1.
*\*\fun     Enables the CFG4 register peripheral clock.
*\*\param   CFG4_periph (CFG4 peripheral to gates its clock):
*\*\     - RCC_CFG4_PERIPHEN_AHB1BUS
*\*\     - RCC_CFG4_PERIPHEN_AHB2BUS
*\*\     - RCC_CFG4_PERIPHEN_AHB5BUS
*\*\     - RCC_CFG4_PERIPHEN_AHB6BUS
*\*\     - RCC_CFG4_PERIPHEN_AXIBUS
*\*\     - RCC_CFG4_PERIPHEN_APB1BUS
*\*\     - RCC_CFG4_PERIPHEN_APB2BUS
*\*\     - RCC_CFG4_PERIPHEN_APB5BUS
*\*\     - RCC_CFG4_PERIPHEN_APB6BUS
*\*\     - RCC_CFG4_PERIPHEN_AHB9BUS
*\*\     - RCC_CFG4_PERIPHEN_M7AXIMATRIX_GPV
*\*\     - RCC_CFG4_PERIPHEN_M4AXIMATRIX_GPV
*\*\     - RCC_CFG4_PERIPHEN_HSICG
*\*\     - RCC_CFG4_PERIPHEN_HSIKERCG
*\*\     - RCC_CFG4_PERIPHEN_HSECG
*\*\     - RCC_CFG4_PERIPHEN_HSEKERCG
*\*\     - RCC_CFG4_PERIPHEN_MSICG
*\*\     - RCC_CFG4_PERIPHEN_MSIKERCG
*\*\     - RCC_CFG4_PERIPHEN_M7AXIMATRIX
*\*\     - RCC_CFG4_PERIPHEN_AXIGGPV
*\*\     - RCC_CFG4_PERIPHEN_M4AXIMATRIX
*\*\     - RCC_CFG4_PERIPHEN_M7DCMUCLK
*\*\     - RCC_CFG4_PERIPHEN_M4DCMUCLK
*\*\     - RCC_CFG4_PERIPHEN_AHBMATRIX1
*\*\     - RCC_CFG4_PERIPHEN_AHBMATRIX2
*\*\     - RCC_CFG4_PERIPHEN_AHBMATRIX3
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableCFG4PeriphClk1(uint32_t CFG4_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->CFG4 |= CFG4_periph;
    }
    else
    {
        RCC->CFG4 &= ~CFG4_periph;
    }
}

/**
*\*\name    RCC_EnableCFG5PeriphClk1.
*\*\fun     Enables the CFG5 register peripheral clock.
*\*\param   CFG5_periph (CFG5 peripheral to gates its clock):
*\*\     - RCC_CFG5_PERIPHEN_M7_SRAM5
*\*\     - RCC_CFG5_PERIPHEN_M4_SRAM5
*\*\     - RCC_CFG5_PERIPHEN_M7_SRAM5LP
*\*\     - RCC_CFG5_PERIPHEN_M4_SRAM5LP
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_EnableCFG5PeriphClk1(uint32_t CFG5_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->CFG5 |= CFG5_periph;
    }
    else
    {
        RCC->CFG5 &= ~CFG5_periph;
    }
}

/**
*\*\name    RCC_ConfigMco1.
*\*\fun     Configures the MCO1 clock source and divider.
*\*\param   CLK_source:
*\*\         - RCC_MCO1_SRC_LSI
*\*\         - RCC_MCO1_SRC_HSI
*\*\         - RCC_MCO1_SRC_MSI
*\*\         - RCC_MCO1_SRC_LSE
*\*\         - RCC_MCO1_SRC_HSE
*\*\         - RCC_MCO1_SRC_PLL3B
*\*\param   CLK_divider:
*\*\         - RCC_MCO1_DIV1
*\*\         - RCC_MCO1_DIV2
*\*\         - RCC_MCO1_DIV4
*\*\         - RCC_MCO1_DIV8
*\*\         - RCC_MCO1_DIV16
*\*\         - RCC_MCO1_DIV32
*\*\         - RCC_MCO1_DIV64
*\*\         - RCC_MCO1_DIV128
*\*\return  none
*\*\return  none
**/
void RCC_ConfigMco1(uint32_t CLK_source, uint32_t CLK_divider)
{
    uint32_t temp_value;

    temp_value = RCC->CFG3;
    /* Clear MCO1SEL[3:0] and MCO1DIV[3:0] bits */
    temp_value &= RCC_MCO1_SRC_MASK;
    temp_value &= RCC_MCO1_DIV_MASK;
    /* Set MCO1SEL[3:0] bits according to CLK_source value */
    temp_value |= CLK_source;
    /* Set MCO1DIV[3:0] bits according to CLK_divider value */
    temp_value |= CLK_divider;

    /* Store the new value */
    RCC->CFG3 = temp_value;
}

/**
*\*\name    RCC_ConfigMco2.
*\*\fun     Configures the MCO2 clock source and divider.
*\*\param   CLK_source:
*\*\         - RCC_MCO2_SRC_SYSCLK
*\*\         - RCC_MCO2_SRC_PLL1A
*\*\         - RCC_MCO2_SRC_PLL2A
*\*\         - RCC_MCO2_SRC_PLL3A
*\*\         - RCC_MCO2_SRC_SHRPLL
*\*\         - RCC_MCO2_SRC_LSE
*\*\param   CLK_divider:
*\*\         - RCC_MCO2_DIV1
*\*\         - RCC_MCO2_DIV2
*\*\         - RCC_MCO2_DIV4
*\*\         - RCC_MCO2_DIV8
*\*\         - RCC_MCO2_DIV16
*\*\         - RCC_MCO2_DIV32
*\*\         - RCC_MCO2_DIV64
*\*\         - RCC_MCO2_DIV128
*\*\return  none
**/
void RCC_ConfigMco2(uint32_t CLK_source, uint32_t CLK_divider)
{
    uint32_t temp_value;

    temp_value = RCC->CFG3;
    /* Clear MCO2SEL[3:0] and MCO2DIV[3:0] bits */
    temp_value &= RCC_MCO2_SRC_MASK;
    temp_value &= RCC_MCO2_DIV_MASK;
    /* Set MCO2SEL[3:0] bits according to CLK_source value */
    temp_value |= CLK_source;
    /* Set MCO2DIV[3:0] bits according to CLK_divider value */
    temp_value |= CLK_divider;

    /* Store the new value */
    RCC->CFG3 = temp_value;
}

/**
*\*\name    RCC_EnableFDCANStopRequest1.
*\*\fun     Sending a stop request to the FDCAN module when enabled.
*\*\param   FDCAN_sel(select FDCANx) :
*\*\        -RCC_STOPEN_FDCAN1
*\*\        -RCC_STOPEN_FDCAN2
*\*\        -RCC_STOPEN_FDCAN5
*\*\        -RCC_STOPEN_FDCAN6
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note    Hardware clears this bit after receiving a shutdown answer from the CAN module
**/
void RCC_EnableFDCANStopRequest1(uint32_t FDCAN_sel, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->APB1EN5 |= FDCAN_sel;
    }
    else
    {
        RCC->APB1EN5 &= ~FDCAN_sel;
    }

}

/**
*\*\name    RCC_GetFDCANStopAckFlag1
*\*\fun     Checks whether the specified FDCAN Stop Ack flag is set or not.
*\*\param   RCC_flag (The input   parameters must be the following values):
*\*\        -RCC_FLAG_STOPACK_FDCAN1
*\*\        -RCC_FLAG_STOPACK_FDCAN2
*\*\        -RCC_FLAG_STOPACK_FDCAN5
*\*\        -RCC_FLAG_STOPACK_FDCAN6
*\*\return  FlagStatus
*\*\          - SET
*\*\          - RESET
**/
FlagStatus RCC_GetFDCANStopAckFlag1(uint32_t RCC_flag)
{
    FlagStatus bitstatus;

    if ((RCC->APB1EN5 & RCC_flag) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
*\*\name    RCC_EnableFDCANStopRequest2.
*\*\fun     Sending a stop request to the FDCAN module when enabled.
*\*\param   FDCAN_sel(select FDCANx) :
*\*\        -RCC_STOPEN_FDCAN3
*\*\        -RCC_STOPEN_FDCAN4
*\*\        -RCC_STOPEN_FDCAN7
*\*\        -RCC_STOPEN_FDCAN8
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note    Hardware clears this bit after receiving a shutdown answer from the CAN module
**/
void RCC_EnableFDCANStopRequest2(uint32_t FDCAN_sel, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->APB2EN4 |= FDCAN_sel;
    }
    else
    {
        RCC->APB2EN4 &= ~FDCAN_sel;
    }

}

/**
*\*\name    RCC_GetFDCANStopAckFlag2
*\*\fun     Checks whether the specified FDCAN Stop Ack flag is set or not.
*\*\param   RCC_flag (The input   parameters must be the following values):
*\*\        -RCC_FLAG_STOPACK_FDCAN3
*\*\        -RCC_FLAG_STOPACK_FDCAN4
*\*\        -RCC_FLAG_STOPACK_FDCAN7
*\*\        -RCC_FLAG_STOPACK_FDCAN8
*\*\return  FlagStatus
*\*\          - SET
*\*\          - RESET
**/
FlagStatus RCC_GetFDCANStopAckFlag2(uint32_t RCC_flag)
{
    FlagStatus bitstatus;

    if ((RCC->APB2EN4 & RCC_flag) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}


/**
*\*\name    RCC_ConfigPeriphClk.
*\*\fun     Configures the Periph clock source.
*\*\param   CLK_source(Periph clock source):
*\*\         - RCC_PERIPHCLK_SRC_HSI
*\*\         - RCC_PERIPHCLK_SRC_MSI
*\*\         - RCC_PERIPHCLK_SRC_HSE
*\*\return  none
*\*\note  If the module clock source is selected as periph, then needs to config PERSW[1:0]
**/
void RCC_ConfigPeriphClk(uint32_t CLK_source)
{
    uint32_t temp_value;

    temp_value = RCC->CFG3;

    /* Clear PERSW[1:0] bits */
    temp_value &= RCC_PERIPHCLK_SRC_MASK;
    /* Set PERSW[1:0] bits according to CLK_source value*/
    temp_value |= CLK_source;

    /* Store the new value */
    RCC->CFG3 = temp_value;

}

/**
*\*\name    RCC_EnableModuleResetRequest.
*\*\fun     Configure whether to generate a reset request when the corresponding module event occurs.
*\*\param   Module_sel(select module) :
*\*\        -RCC_RSTEN_WWDG1
*\*\        -RCC_RSTEN_WWDG2
*\*\        -RCC_RSTEN_BOR
*\*\        -RCC_RSTEN_C1LP
*\*\        -RCC_RSTEN_C2LP
*\*\        -RCC_RSTEN_BKPEMC
*\*\        -RCC_RSTEN_RETEMC
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note BDCTRL is protected, you need to enable the PWR clock first,
*\*\     then configure PWR_SYSCTRL1.DBKP to 1 to change it.
**/
void RCC_EnableModuleResetRequest(uint32_t Module_sel, FunctionalState Cmd)
{
    if(Module_sel <= RCC_RSTEN_WWDG2)
    {
        if (Cmd != DISABLE)
        {
            RCC->CFG1 |= Module_sel;
        }
        else
        {
            RCC->CFG1 &= ~Module_sel;
        }
    }
    else
    {
        if (Cmd != DISABLE)
        {
            RCC->BDCTRL |= Module_sel;
        }
        else
        {
            RCC->BDCTRL &= ~Module_sel;
        }
    }


}

/**
*\*\name    RCC_ConfigInt1.
*\*\fun     Enables the specified RCC interrupts.
*\*\param   Interrupt(the RCC interrupt sources to be enabled):
*\*\         - RCC_INT_LSECSS
*\*\         - RCC_INT_BOR
*\*\         - RCC_INT_PLL1RD
*\*\         - RCC_INT_PLL2RD
*\*\         - RCC_INT_PLL3RD
*\*\         - RCC_INT_SHRPLLRD
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_ConfigInt1(uint32_t Interrupt, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->CLKINT1 |= (((uint32_t)Interrupt) << 1);
    }
    else
    {
        RCC->CLKINT1 &= (~(((uint32_t)Interrupt) << 1));
    }

}

/**
*\*\name    RCC_ConfigInt2.
*\*\fun     Enables the specified RCC interrupts.
*\*\param   Interrupt(the RCC interrupt sources to be enabled):
*\*\         - RCC_INT_HSERD
*\*\         - RCC_INT_HSIRD
*\*\         - RCC_INT_MSIRD
*\*\         - RCC_INT_LSERD
*\*\         - RCC_INT_LSIRD
*\*\         - RCC_INT_HSICALE
*\*\         - RCC_INT_MSICALE
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_ConfigInt2(uint32_t Interrupt, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->CLKINT2 |= (((uint32_t)Interrupt) << 1);
    }
    else
    {
        RCC->CLKINT2 &= (~(((uint32_t)Interrupt) << 1));
    }

}

/**
*\*\name    RCC_ConfigInt3.
*\*\fun     Enables the specified RCC interrupts.
*\*\param   Interrupt(the RCC interrupt sources to be enabled):
*\*\         - RCC_INT_PLL1LKF
*\*\         - RCC_INT_PLL2LKF
*\*\         - RCC_INT_PLL3LKF
*\*\         - RCC_INT_SHRPLLLKF
*\*\         - RCC_INT_LSIF
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RCC_ConfigInt3(uint32_t Interrupt, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->CLKINT3 |= (((uint32_t)Interrupt) << 1);
    }
    else
    {
        RCC->CLKINT3 &= (~(((uint32_t)Interrupt) << 1));
    }

}

/**
*\*\name    RCC_GetIntStatus1.
*\*\fun     Checks whether the specified RCC interrupt has occurred or not.
*\*\param   interrupt_flag(RCC interrupt source to check):
*\*\         - RCC_INT_LSECSS
*\*\         - RCC_INT_HSECSS
*\*\         - RCC_INT_BOR
*\*\         - RCC_INT_PLL1RD
*\*\         - RCC_INT_PLL2RD
*\*\         - RCC_INT_PLL3RD
*\*\         - RCC_INT_SHRPLLRD
*\*\return  The new state of interrupt_flag
*\*\         - SET
*\*\         - RESET
**/
INTStatus RCC_GetIntStatus1(uint32_t interrupt_flag)
{
    INTStatus bitstatus;

    /* Check the status of the specified RCC interrupt */
    if ((RCC->CLKINT1 & interrupt_flag) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
*\*\name    RCC_GetIntStatus2.
*\*\fun     Checks whether the specified RCC interrupt has occurred or not.
*\*\param   interrupt_flag(RCC interrupt source to check):
*\*\         - RCC_INT_HSERD
*\*\         - RCC_INT_HSIRD
*\*\         - RCC_INT_MSIRD
*\*\         - RCC_INT_LSERD
*\*\         - RCC_INT_LSIRD
*\*\         - RCC_INT_HSICALE
*\*\         - RCC_INT_MSICALE
*\*\return  The new state of interrupt_flag
*\*\         - SET
*\*\         - RESET
**/
INTStatus RCC_GetIntStatus2(uint32_t interrupt_flag)
{
    INTStatus bitstatus;

    /* Check the status of the specified RCC interrupt */
    if ((RCC->CLKINT2 & interrupt_flag) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
*\*\name    RCC_GetIntStatus3.
*\*\fun     Checks whether the specified RCC interrupt has occurred or not.
*\*\param   interrupt_flag(RCC interrupt source to check):
*\*\         - RCC_INT_PLL1LKF
*\*\         - RCC_INT_PLL2LKF
*\*\         - RCC_INT_PLL3LKF
*\*\         - RCC_INT_SHRPLLLKF
*\*\         - RCC_INT_LSIF
*\*\return  The new state of interrupt_flag
*\*\         - SET
*\*\         - RESET
**/
INTStatus RCC_GetIntStatus3(uint32_t interrupt_flag)
{
    INTStatus bitstatus;

    /* Check the status of the specified RCC interrupt */
    if ((RCC->CLKINT3 & interrupt_flag) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}


/**
*\*\name    RCC_ClrIntPendingBit1.
*\*\fun     Clears the RCC's interrupt pending bits.
*\*\param   interrupt_clear(interrupt pending bit to clear):
*\*\         - RCC_INT_LSECSS
*\*\         - RCC_INT_HSECSS
*\*\         - RCC_INT_BOR
*\*\         - RCC_INT_PLL1RD
*\*\         - RCC_INT_PLL2RD
*\*\         - RCC_INT_PLL3RD
*\*\         - RCC_INT_SHRPLLRD
*\*\return  none
**/
void RCC_ClrIntPendingBit1(uint32_t interrupt_clear)
{
    /* Software set this bit to clear INT flag. */
    RCC->CLKINT1 |= (((uint32_t)interrupt_clear) >> 1);;
}

/**
*\*\name    RCC_ClrIntPendingBit2.
*\*\fun     Clears the RCC's interrupt pending bits.
*\*\param   interrupt_clear(interrupt pending bit to clear):
*\*\         - RCC_INT_HSERD
*\*\         - RCC_INT_HSIRD
*\*\         - RCC_INT_MSIRD
*\*\         - RCC_INT_LSERD
*\*\         - RCC_INT_LSIRD
*\*\         - RCC_INT_HSICALE
*\*\         - RCC_INT_MSICALE
*\*\return  none
**/
void RCC_ClrIntPendingBit2(uint32_t interrupt_clear)
{
    /* Software set this bit to clear INT flag. */
    RCC->CLKINT2 |= (((uint32_t)interrupt_clear) >> 1);;
}

/**
*\*\name    RCC_ClrIntPendingBit3.
*\*\fun     Clears the RCC's interrupt pending bits.
*\*\param   interrupt_clear(interrupt pending bit to clear):
*\*\         - RCC_INT_PLL1LKF
*\*\         - RCC_INT_PLL2LKF
*\*\         - RCC_INT_PLL3LKF
*\*\         - RCC_INT_SHRPLLLKF
*\*\         - RCC_INT_LSIF
*\*\return  none
**/
void RCC_ClrIntPendingBit3(uint32_t interrupt_clear)
{
    /* Software set this bit to clear INT flag. */
    RCC->CLKINT3 |= (((uint32_t)interrupt_clear) >> 1);;
}

/**
*\*\name    RCC_GetFlagStatus.
*\*\fun     Checks whether the specified RCC flag is set or not.
*\*\param   RCC_flag:
*\*\          - RCC_FLAG_HSIRD        HSI clock ready
*\*\          - RCC_FLAG_HSERD        HSE clock ready
*\*\          - RCC_FLAG_MSIRD        MSI clock ready
*\*\          - RCC_FLAG_AFEHSIRD     AFE HSI clock ready
*\*\          - RCC_FLAG_AFEMSIRD     AFE MSI clock ready
*\*\          - RCC_FLAG_MSICALE      MSI calibration error status flag
*\*\          - RCC_FLAG_HSICALE      HSI calibration error status flag
*\*\          - RCC_FLAG_BOR          BOR status flag
*\*\          - RCC_FLAG_LSIRD        LSI clock ready
*\*\          - RCC_FLAG_LSERD        LSE clock ready
*\*\          - RCC_FLAG_LSECSS       LSE Clock Safety System flag
*\*\          - RCC_FLAG_LSISECRD     Secondary LSI clock ready
*\*\          - RCC_FLAG_RTCHSFSW     RTC HSE source fail status
*\*\          - RCC_FLAG_RTCLSFSW     RTC LSE source fail status
*\*\          - RCC_FLAG_LSIPF        LSI primary failure status
*\*\          - RCC_FLAG_AFELSIRD     AFE LSI clock ready
*\*\          - RCC_FLAG_AFELSERD     AFE LSE clock ready
*\*\          - RCC_FLAG_PINRST       PIN reset flag
*\*\          - RCC_FLAG_PORRST       POR/PDR reset flag
*\*\          - RCC_FLAG_CM7SFTRST    M7 Software reset flag
*\*\          - RCC_FLAG_CM4SFTRST    M4 Software reset flag
*\*\          - RCC_FLAG_IWDG2RST     IWDG2 reset flag
*\*\          - RCC_FLAG_IWDG1RST     IWDG1 reset flag
*\*\          - RCC_FLAG_WWDG2RST     WWDG2 reset flag
*\*\          - RCC_FLAG_WWDG1RST     WWDG1 reset flag
*\*\          - RCC_FLAG_MMURST       MMU reset flag
*\*\          - RCC_FLAG_BORRST       BOR reset flag
*\*\          - RCC_FLAG_BKPEMCRST    Backup EMC reset flag
*\*\          - RCC_FLAG_RETEMCRST    VDDDRET EMC reset flag
*\*\          - RCC_FLAG_C2LPRST      C2 Low-power reset flag
*\*\          - RCC_FLAG_C1LPRST      C1 Low-power reset flag
*\*\          - RCC_FLAG_SHRPLLG      SHRPLL clock gate flag
*\*\          - RCC_FLAG_PLL3G        PLL3 clock gate flag
*\*\          - RCC_FLAG_PLL2G        PLL2 clock gate flag
*\*\          - RCC_FLAG_PLL1G        PLL1 clock gate flag
*\*\          - RCC_FLAG_SHRPLLF      SHRPLL fail state flag
*\*\          - RCC_FLAG_PLL3F        PLL3 fail state flag
*\*\          - RCC_FLAG_PLL2F        PLL2 fail state flag
*\*\          - RCC_FLAG_PLL1F        PLL1 fail state flag
*\*\return  FlagStatus:
*\*\            - SET
*\*\            - RESET
**/
FlagStatus RCC_GetFlagStatus(uint8_t RCC_flag)
{
    uint32_t temp_value;
    uint32_t reg_value;
    FlagStatus bitstatus;

    /* Get the RCC register index */
    temp_value = (uint32_t)RCC_flag >> RCC_FLAG_OFFSET;

    switch(temp_value)
    {
        case 1: /* The flag to check is in SRCCTRL1 register */
            reg_value = RCC->SRCCTRL1;
            break;

        case 2: /* The flag to check is in SRCCTRL2 register */
            reg_value = RCC->SRCCTRL2;
            break;

        case 3:/* The flag to check is in BDCTRL register */
            reg_value = RCC->BDCTRL;
            break;

        case 4:/* The flag to check is in CTRLSTS register */
            reg_value = RCC->CTRLSTS;
            break;

        default:/* The flag to check is in PLLFD register */
            reg_value = RCC->PLLFD;
            break;
    }

    /* Get the flag position */
    temp_value = (uint32_t)RCC_flag & RCC_FLAG_MASK;

    if ((reg_value & ((uint32_t)1 << temp_value)) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
*\*\name    RCC_ClearResetFlag.
*\*\fun     Clears the RCC reset flags.
*\*\param   none
*\*\return  none
*\*\note  Clear the following flags:
*\*\          - RCC_FLAG_PINRST       PIN reset flag
*\*\          - RCC_FLAG_PORRST       POR/PDR reset flag
*\*\          - RCC_FLAG_CM7SFTRST    M7 Software reset flag
*\*\          - RCC_FLAG_CM4SFTRST    M4 Software reset flag
*\*\          - RCC_FLAG_IWDG2RST     IWDG2 reset flag
*\*\          - RCC_FLAG_IWDG1RST     IWDG1 reset flag
*\*\          - RCC_FLAG_WWDG2RST     WWDG2 reset flag
*\*\          - RCC_FLAG_WWDG1RST     WWDG1 reset flag
*\*\          - RCC_FLAG_MMURST       MMU reset flag
*\*\          - RCC_FLAG_BORRST       BOR reset flag
*\*\          - RCC_FLAG_BKPEMCRST    Backup EMC reset flag
*\*\          - RCC_FLAG_RETEMCRST    VDDDRET EMC reset flag
*\*\          - RCC_FLAG_C2LPRST      C2 Low-power reset flag
*\*\          - RCC_FLAG_C1LPRST      C1 Low-power reset flag
**/
void RCC_ClearResetFlag(void)
{
    /* Set RMRSTF bit to clear the reset flags */
    RCC->CTRLSTS |= RCC_REMOVE_RESET_FLAG;
    /* RMRSTF bit should be reset */
    RCC->CTRLSTS &= ~RCC_REMOVE_RESET_FLAG;
}

/**
 *\*\name   RCC_EnableCM4.
 *\*\fun    Enable CM4 core reset and startup.
 *\*\param  CM4_BaseAddr: the Vector Table location add offset address of CM4 core;
 *\*\return none
 */
void RCC_EnableCM4(uint32_t CM4_BaseAddr)
{
    /*Config CM4 vector address in MMU register*/
    *(uint32_t*)0x511050ac = CM4_BaseAddr;
    /*Enable CM7 reset CM4 Reset bit*/
    RCC->M4RSTREL |= RCC_RSTEN_M4REL  ;
}

/**
*\*\name    RCC_GetClocksFreq.
*\*\fun     Returns the frequencies of different on chip clocks.
*\*\param   RCC_Clocks:
*\*\        pointer to a RCC_ClocksTypeDef structure which will hold the clocks frequencies.
*\*\return  none
*\*\note   The result of this function could be not correct when using
*\*\        fractional value for HSE crystal.
**/
void RCC_GetClocksFreqValue(RCC_ClocksTypeDef* RCC_Clocks)
{
    uint32_t hsi_value, msi_value;
    uint32_t pll_value, temp_value, temp_value1, sysdiv_value, hyper_value;
    const uint8_t SysPresTable[16]    = {0, 1, 2, 2, 3, 3, 3, 4, 5, 6, 7, 8, 9, 9, 9, 9};
    const uint8_t ApbPresTable[8]    = {0, 0, 0, 0, 1, 2, 3, 4};



    temp_value = RCC->PLL1CTRL1 & RCC_PLL1CTRL1_PLL1SRC;

    if(temp_value == RCC_PLL_SRC_HSE)
    {
        pll_value = HSE_VALUE;
    }
    else if(temp_value == RCC_PLL_SRC_MSI)
    {
        pll_value = MSI_VALUE;
    }
    else
    {
        pll_value = HSI_VALUE;
    }

    temp_value = (((RCC->PLL1CTRL2 & RCC_PLL1CTRL2_PLL1CLKR) >> 26) + 1);
    temp_value1 = (RCC->PLL1CTRL2 & RCC_PLL1CTRL2_PLL1CLKF);
    pll_value = (uint32_t)((((uint64_t)pll_value * (uint64_t)temp_value1) >> 14) / temp_value);

    temp_value = (RCC->PLL1DIV & RCC_PLL1DIV_PLL1ADIV);

    if(temp_value > 0)
    {
        RCC_Clocks->PLL1AClkFreq = pll_value / temp_value;
    }

    temp_value = ((RCC->PLL1DIV & RCC_PLL1DIV_PLL1BDIV) >> 8);

    if(temp_value > 0)
    {
        RCC_Clocks->PLL1BClkFreq = pll_value / temp_value;
    }

    temp_value = ((RCC->PLL1DIV & RCC_PLL1DIV_PLL1CDIV) >> 16);

    if(temp_value > 0)
    {
        RCC_Clocks->PLL1CClkFreq = pll_value / temp_value;
    }

    temp_value = RCC->PLL2CTRL1 & RCC_PLL2CTRL1_PLL2SRC;

    if(temp_value == RCC_PLL_SRC_HSE)
    {
        pll_value = HSE_VALUE;
    }
    else if(temp_value == RCC_PLL_SRC_MSI)
    {
        pll_value = MSI_VALUE;
    }
    else
    {
        pll_value = HSI_VALUE;
    }

    temp_value = (((RCC->PLL2CTRL2 & RCC_PLL2CTRL2_PLL2CLKR) >> 26) + 1);
    temp_value1 = (RCC->PLL2CTRL2 & RCC_PLL2CTRL2_PLL2CLKF);
    pll_value = (uint32_t)((((uint64_t)pll_value * (uint64_t)temp_value1) >> 14) / temp_value);

    temp_value = (RCC->PLL2DIV & RCC_PLL2DIV_PLL2ADIV);

    if( temp_value > 0)
    {
        RCC_Clocks->PLL2AClkFreq = pll_value / temp_value;
    }

    temp_value = ((RCC->PLL2DIV & RCC_PLL2DIV_PLL2BDIV) >> 8);

    if(temp_value > 0)
    {
        RCC_Clocks->PLL2BClkFreq = pll_value / temp_value;
    }

    temp_value = ((RCC->PLL2DIV & RCC_PLL2DIV_PLL2CDIV) >> 16);

    if(temp_value > 0)
    {
        RCC_Clocks->PLL2CClkFreq = pll_value / temp_value;
    }

    temp_value = RCC->PLL3CTRL1 & RCC_PLL3CTRL1_PLL3SRC;

    if(temp_value == RCC_PLL_SRC_HSE)
    {
        pll_value = HSE_VALUE;
    }
    else if(temp_value == RCC_PLL_SRC_MSI)
    {
        pll_value = MSI_VALUE;
    }
    else
    {
        pll_value = HSI_VALUE;
    }

    temp_value = (((RCC->PLL3CTRL2 & RCC_PLL3CTRL2_PLL3CLKR) >> 26) + 1);
    temp_value1 = (RCC->PLL3CTRL2 & RCC_PLL3CTRL2_PLL3CLKF);
    pll_value = (uint32_t)((((uint64_t)pll_value * (uint64_t)temp_value1) >> 14) / temp_value);

    temp_value = (RCC->PLL3DIV & RCC_PLL3DIV_PLL3ADIV);

    if(temp_value > 0)
    {
        RCC_Clocks->PLL3AClkFreq = pll_value / temp_value;
    }

    temp_value = ((RCC->PLL3DIV & RCC_PLL3DIV_PLL3BDIV) >> 8);

    if(temp_value > 0)
    {
        RCC_Clocks->PLL3BClkFreq = pll_value / temp_value;
    }

    temp_value = ((RCC->PLL3DIV & RCC_PLL3DIV_PLL3CDIV) >> 16);

    if(temp_value > 0)
    {
        RCC_Clocks->PLL3CClkFreq = pll_value / temp_value;
    }

    hsi_value = HSI_VALUE >>  (SysPresTable[(RCC->SYSBUSDIV1 & RCC_SYSBUSDIV1_HSIDIV) >> 20]);
    msi_value = MSI_VALUE >>  (SysPresTable[(RCC->SYSBUSDIV1 & RCC_SYSBUSDIV1_MSIDIV) >> 4]);

    temp_value = RCC->SRCCTRL1 & RCC_SRCCTRL1_SCLKSTS;

    if(temp_value == RCC_SYSCLK_STS_HSE)
    {
        RCC_Clocks->SysClkFreq = HSE_VALUE;
    }
    else if(temp_value == RCC_SYSCLK_STS_MSI)
    {
        RCC_Clocks->SysClkFreq = msi_value;
    }
    else if(temp_value == RCC_SYSCLK_STS_PLL1A)
    {
        RCC_Clocks->SysClkFreq = RCC_Clocks->PLL1AClkFreq;
    }
    else
    {
        RCC_Clocks->SysClkFreq = hsi_value;
    }

    sysdiv_value = RCC_Clocks->SysClkFreq >> (SysPresTable[RCC->SYSBUSDIV1 & RCC_SYSBUSDIV1_SCLKDIV]);
    hyper_value = RCC_Clocks->PLL2AClkFreq >> (SysPresTable[(RCC->SYSBUSDIV1 & RCC_SYSBUSDIV1_M7HYPDIV) >> 16]);

    RCC_Clocks->SysBusDivClkFreq = sysdiv_value >> (SysPresTable[(RCC->SYSBUSDIV1 & RCC_SYSBUSDIV1_BUSDIV) >> 8]);
    RCC_Clocks->M4ClkFreq = RCC_Clocks->SysBusDivClkFreq;

    if((RCC->SRCCTRL2 & RCC_SRCCTRL2_M7HYPSEL) == RCC_M7HYPERCLK_SRC_PLL2A)
    {
        RCC_Clocks->M7ClkFreq = hyper_value;
    }
    else
    {
        RCC_Clocks->M7ClkFreq = sysdiv_value;
    }

    if((RCC->SRCCTRL2 & RCC_SRCCTRL2_AXIHYPSEL) == RCC_AXIHYPERCLK_SRC_PLL2A)
    {
        RCC_Clocks->AXIClkFreq = hyper_value >> (SysPresTable[(RCC->SYSBUSDIV1 & RCC_SYSBUSDIV1_AXIHYPDIV) >> 24]);
    }
    else
    {
        RCC_Clocks->AXIClkFreq = sysdiv_value >> (SysPresTable[(RCC->SYSBUSDIV1 & RCC_SYSBUSDIV1_AXIDIV) >> 12]);
    }

    RCC_Clocks->AHB1ClkFreq = RCC_Clocks->SysBusDivClkFreq;
    RCC_Clocks->AHB2ClkFreq = RCC_Clocks->SysBusDivClkFreq;
    RCC_Clocks->AHB5ClkFreq = RCC_Clocks->SysBusDivClkFreq;
    RCC_Clocks->AHB6ClkFreq = RCC_Clocks->AXIClkFreq;
    RCC_Clocks->AHB9ClkFreq = RCC_Clocks->SysBusDivClkFreq;

    RCC_Clocks->APB1ClkFreq = RCC_Clocks->AHB1ClkFreq >> (ApbPresTable[RCC->SYSBUSDIV2 & RCC_SYSBUSDIV2_APB1DIV]);
    RCC_Clocks->APB2ClkFreq = RCC_Clocks->AHB2ClkFreq >> (ApbPresTable[(RCC->SYSBUSDIV2 & RCC_SYSBUSDIV2_APB2DIV) >> 8]);
    RCC_Clocks->APB5ClkFreq = RCC_Clocks->AHB5ClkFreq >> (ApbPresTable[(RCC->SYSBUSDIV2 & RCC_SYSBUSDIV2_APB5DIV) >> 16]);
    RCC_Clocks->APB6ClkFreq = RCC_Clocks->AHB6ClkFreq >> (ApbPresTable[(RCC->SYSBUSDIV2 & RCC_SYSBUSDIV2_APB6DIV) >> 24]);

    temp_value = RCC->CFG3 & RCC_CFG3_PERSW;

    if(temp_value == RCC_PERIPHCLK_SRC_HSE)
    {
        RCC_Clocks->PeriphClkFreq = HSE_VALUE;
    }
    else if(temp_value == RCC_PERIPHCLK_SRC_MSI)
    {
        RCC_Clocks->PeriphClkFreq = msi_value;
    }
    else
    {
        RCC_Clocks->PeriphClkFreq = hsi_value;
    }

}

/**
*\*\name   RCC_SetSysClkToMode0.
*\*\fun    Configure the M7 clock is 600MHz,
*\*\       M4, AXI, AHB(1,2,5,6,9) clock is 300MHz,
*\*\       APB(1,2,5,6) clock is 150MHz.
*\*\param   none
*\*\return  none
*\*\note    M7 from PLL1A, AXI from PLL1A, M4 from PLL1A.
**/
void RCC_SetSysClkToMode0(void)
{
    uint32_t temp_value1, temp_value2;

    /* Configure sys_div_clk is sys_clk(PLL1A) = 600M = M7 clock*/
    RCC_ConfigSysclkDivider(RCC_SYSCLK_DIV1);
    /* Configure sys_bus_div_clk is sys_div_clk/2 = 300M = M4 clock = AHB1\2\5\9*/
    RCC_ConfigSysbusDivider(RCC_BUSCLK_DIV2);
    /* Configure AXI clock is sys_div_clk/2 = 300M = AHB6*/
    RCC_ConfigAXIclkDivider(RCC_AXICLK_DIV2);
    RCC_ConfigAXIHyperDivider(RCC_AXICLK_HYP_DIV2);

    __RCC_DELAY_US(1);
    /* Configure APB1 clock is AHB1/2 = 150M */
    /* Configure APB2 clock is AHB2/2 = 150M */
    /* Configure APB5 clock is AHB5/2 = 150M */
    /* Configure APB6 clock is AHB6/2 = 150M */
    RCC_ConfigAPBclkDivider(RCC_APB1CLK_DIV2, RCC_APB2CLK_DIV2, RCC_APB5CLK_DIV2, RCC_APB6CLK_DIV2);

    /* configure PLL1 source is HSI, frequency is 600M */
    //RCC_ConfigPll1(RCC_PLL_SRC_HSI,64000000,600000000,ENABLE);
    /* get the register value */
    temp_value1 = RCC->PLL1CTRL1;
    temp_value2 = RCC->PLL1CTRL2;

    /* Clear BWAJ[11:0] bits */
    temp_value1 &= RCC_PLL_BWAJ_MASK;
    /* Clear CLKF[25:0] and CLKR[5:0] bits */
    temp_value2 &= RCC_PLL_CLKR_CLKF_MASK;

    /* Set BWAJ[11:0] bits - 600M */
    temp_value1 |= 0x3U;
    /* Set CLKF[25:0] and CLKR[5:0]  bits */
    temp_value2 |= 0x25800U;

    /* Store the new value */
    RCC->PLL1CTRL1  = temp_value1;
    RCC->PLL1CTRL2  = temp_value2;

    /* Enable PLL module power */
    RCC->PLL1CTRL1 |= RCC_PLL_LDO_ENABLE;
    __RCC_DELAY_US(10);

    /* Enable power to analog circuitry in PLL */
    RCC->PLL1CTRL1 &= (~RCC_PLL_POWER_DOWN);

    /* Select Clock Source */
    temp_value1 = RCC->PLL1CTRL1;
    temp_value1 &= RCC_PLL_SRC_MASK;
    temp_value1 |= RCC_PLL_SRC_HSI;
    RCC->PLL1CTRL1 = temp_value1;
    __RCC_DELAY_US(10);

    /* Clear PLL reset */
    RCC->PLL1CTRL1 &= (~RCC_PLL_RESET_ENABLE);

    while((RCC->PLL1CTRL1 & RCC_PLL_LOCK_FLAG) != RCC_PLL_LOCK_FLAG)
    {}

    /* Enable PLL */
    RCC->PLL1CTRL1 |= RCC_PLL_ENABLE;
    /* configure PLL1 source is HSI, frequency is 600M end*/

    __RCC_DELAY_US(1);

    /* configure PLL1A is 600M */
    RCC_ConfigPLL1ADivider(RCC_PLLA_DIV1);//600M

    /* configure sys_clk source is PLL1A */
    RCC_ConfigSysclk(RCC_SYSCLK_SRC_PLL1A);

    /* Check if sys_clk source is PLL1A */
    while(RCC_GetSysclkSrc() != RCC_SYSCLK_STS_PLL1A)
    {}

}

/**
*\*\name   RCC_SetSysClkToMode1.
*\*\fun    Configure the M7 clock is 600MHz,
*\*\       M4, AXI, AHB(1,2,5,6,9) clock is 300MHz,
*\*\       APB(1,2,5,6) clock is 150MHz.
*\*\param   none
*\*\return  none
*\*\note    M7 from PLL2A, AXI from PLL2A, M4 from PLL1A.
**/
void RCC_SetSysClkToMode1(void)
{
    /* Configure sys_div_clk is sys_clk(PLL1A) = 600M = M7 clock*/
    RCC_ConfigSysclkDivider(RCC_SYSCLK_DIV1);
    /* Configure sys_bus_div_clk is sys_div_clk/2 = 300M = M4 clock = AHB1\2\5\9*/
    RCC_ConfigSysbusDivider(RCC_BUSCLK_DIV2);
    RCC_ConfigAXIclkDivider(RCC_AXICLK_DIV2);

    /* Configure m7_hyp_div_clk is PLL2A = 600M*/
    RCC_ConfigM7HyperDivider(RCC_M7CLK_HYP_DIV1);
    /* Configure AXI clock is m7_hyp_div_clk/2 = 300M = AHB6*/
    RCC_ConfigAXIHyperDivider(RCC_AXICLK_HYP_DIV2);

    __RCC_DELAY_US(1);
    /* Configure APB1 clock is AHB1/2 = 150M */
    /* Configure APB2 clock is AHB2/2 = 150M */
    /* Configure APB5 clock is AHB5/2 = 150M */
    /* Configure APB6 clock is AHB6/2 = 150M */
    RCC_ConfigAPBclkDivider(RCC_APB1CLK_DIV2, RCC_APB2CLK_DIV2, RCC_APB5CLK_DIV2, RCC_APB6CLK_DIV2);

    /* configure PLL1 source is HSI, frequency is 600M */
    RCC_ConfigPll1(RCC_PLL_SRC_HSI, 64000000, 600000000, ENABLE);
    __RCC_DELAY_US(1);

    /* configure PLL1A is 600M */
    RCC_ConfigPLL1ADivider(RCC_PLLA_DIV1);

    /* configure sys_clk source is PLL1A */
    RCC_ConfigSysclk(RCC_SYSCLK_SRC_PLL1A);

    /* Check if sys_clk source is PLL1A */
    while(RCC_GetSysclkSrc() != RCC_SYSCLK_STS_PLL1A)
    {}

    /* configure PLL2 source is HSI, frequency is 600M */
    RCC_ConfigPll2(RCC_PLL_SRC_HSI, 64000000, 600000000, ENABLE);
    __RCC_DELAY_US(1);

    /* configure PLL2A is 600M */
    RCC_ConfigPLL2ADivider(RCC_PLLA_DIV1);
    /* configure AXI clock source is PLL2A */
    RCC_ConfigAXIClk(RCC_AXIHYPERCLK_SRC_PLL2A);
    /* configure M7 clock source is PLL2A */
    RCC_ConfigM7Clk(RCC_M7HYPERCLK_SRC_PLL2A);

}

/**
*\*\name   RCC_SetSysClkToMode2.
*\*\fun    Configure the M7 clock is 600MHz,
*\*\       M4, AXI, AHB(1,2,5,6,9) clock is 300MHz,
*\*\       APB(1,2,5,6) clock is 150MHz.
*\*\param   none
*\*\return  none
*\*\note    M7 from PLL2A, AXI from PLL1A, M4 from PLL1A.
**/
void RCC_SetSysClkToMode2(void)
{
    /* Configure sys_div_clk is sys_clk(PLL1A) = 600M = M7 clock*/
    RCC_ConfigSysclkDivider(RCC_SYSCLK_DIV1);
    /* Configure sys_bus_div_clk is sys_div_clk/2 = 300M = M4 clock = AHB1\2\5\9*/
    RCC_ConfigSysbusDivider(RCC_BUSCLK_DIV2);
    /* Configure AXI clock is sys_div_clk/2 = 300M = AHB6*/
    RCC_ConfigAXIclkDivider(RCC_AXICLK_DIV2);
    RCC_ConfigAXIHyperDivider(RCC_AXICLK_HYP_DIV2);
    /* Configure m7_hyp_div_clk is PLL2A = 600M*/
    RCC_ConfigM7HyperDivider(RCC_M7CLK_HYP_DIV1);

    __RCC_DELAY_US(1);
    /* Configure APB1 clock is AHB1/2 = 150M */
    /* Configure APB2 clock is AHB2/2 = 150M */
    /* Configure APB5 clock is AHB5/2 = 150M */
    /* Configure APB6 clock is AHB6/2 = 150M */
    RCC_ConfigAPBclkDivider(RCC_APB1CLK_DIV2, RCC_APB2CLK_DIV2, RCC_APB5CLK_DIV2, RCC_APB6CLK_DIV2);

    /* configure PLL1 source is HSI, frequency is 600M */
    RCC_ConfigPll1(RCC_PLL_SRC_HSI, 64000000, 600000000, ENABLE);
    __RCC_DELAY_US(1);

    /* configure PLL1A is 600M */
    RCC_ConfigPLL1ADivider(RCC_PLLA_DIV1);

    /* configure sys_clk source is PLL1A */
    RCC_ConfigSysclk(RCC_SYSCLK_SRC_PLL1A);

    /* Check if sys_clk source is PLL1A */
    while(RCC_GetSysclkSrc() != RCC_SYSCLK_STS_PLL1A)
    {}

    /* configure PLL2 source is HSI, frequency is 600M */
    RCC_ConfigPll2(RCC_PLL_SRC_HSI, 64000000, 600000000, ENABLE);
    __RCC_DELAY_US(1);

    /* configure PLL2A is 600M */
    RCC_ConfigPLL2ADivider(RCC_PLLA_DIV1);
    /* configure M7 clock source is PLL2A */
    RCC_ConfigM7Clk(RCC_M7HYPERCLK_SRC_PLL2A);

}

/**
*\*\name    RCC_SetHsiCalibValue.
*\*\fun     Adjusts the HSI calibration value.
*\*\param   calibration_value(the calibration trimming value):
*\*\        This parameter must be a number between 0 and 0x1FF
*\*\return  none
**/
void RCC_SetHsiCalibValue(uint16_t calibration_value)
{
    uint32_t temp_value;

    temp_value = RCC->SRCCTRL3;
    /* Clear HSITRIM[8:0] bits */
    temp_value &= RCC_HSITRIM_MASK;
    /* Set the HSITRIM[8:0] bits according to calibration_value value */
    temp_value |= ((uint32_t)calibration_value & 0x1FFU);
    /* Store the new value */
    RCC->SRCCTRL3 = temp_value;
}


/**
*\*\name    RCC_SetMsiCalibValue.
*\*\fun     Adjusts the MSI calibration value.
*\*\param   calibration_value(the calibration trimming value):
*\*\        This parameter must be a number between 0 and 0x1F
*\*\return  none
**/
void RCC_SetMsiCalibValue(uint16_t calibration_value)
{
    uint32_t temp_value;

    temp_value = RCC->SRCCTRL2;
    /* Clear MSITRIM[8:0] bits */
    temp_value &= RCC_MSITRIM_MASK;
    /* Set the MSITRIM[8:0] bits according to calibration_value value */
    temp_value |= ((uint32_t)calibration_value & 0x1FU);
    /* Store the new value */
    RCC->SRCCTRL2 = temp_value;
}

/**
*\*\name    RCC_EnableHSEClockSecuritySystem.
*\*\fun     Enables the HSE Clock Security System.
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none.
**/
void RCC_EnableHSEClockSecuritySystem(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->SRCCTRL1 |= RCC_HSECSS_ENABLE;
    }
    else
    {
        RCC->SRCCTRL1 &= (~RCC_HSECSS_ENABLE);
    }
}

/**
*\*\name    RCC_SelectLSISourceControl.
*\*\fun     Selection of LSI clock source control.
*\*\param   CLK_source:
*\*\     - RCC_LSI_SRCCTRL_BY_HARDWARE
*\*\     - RCC_LSI_SRCCTRL_BY_SOFTWARE
*\*\return  none.
*\*\note  If RCC_LSI_SRCCTRL_BY_SOFTWARE is selected, the clock source is switched by enabling the LSICSSEN.
*\*\note BDCTRL is protected, you need to enable the PWR clock first,
*\*\     then configure PWR_SYSCTRL1.DBKP to 1 to change it.
**/
void RCC_SelectLSISourceControl(uint32_t CLK_source)
{
    if (CLK_source == RCC_LSI_SRCCTRL_BY_SOFTWARE)
    {
        RCC->BDCTRL |= CLK_source;
    }
    else
    {
        RCC->BDCTRL &= CLK_source;
    }
}

/**
*\*\name    RCC_EnableLSIClockSecuritySystem.
*\*\fun     Enables the LSI Clock Security System.
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none.
*\*\note BDCTRL is protected, you need to enable the PWR clock first,
*\*\     then configure PWR_SYSCTRL1.DBKP to 1 to change it.
**/
void RCC_EnableLSIClockSecuritySystem(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->BDCTRL |= RCC_LSICSS_ENABLE;
    }
    else
    {
        RCC->BDCTRL &= (~RCC_LSICSS_ENABLE);
    }
}

/**
*\*\name    RCC_EnableLSIClockSecuritySystem.
*\*\fun     Set by software to acknowledge the failure of LSI.
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none.
*\*\note BDCTRL is protected, you need to enable the PWR clock first,
*\*\     then configure PWR_SYSCTRL1.DBKP to 1 to change it.
**/
void RCC_EnableLSIFailAcknowledge(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->BDCTRL |= RCC_LSI_FAILACK_ENABLE;
    }
    else
    {
        RCC->BDCTRL &= (~RCC_LSI_FAILACK_ENABLE);
    }
}

/**
*\*\name    RCC_EnableLSECalibrationCount.
*\*\fun     LSE calibration count enable.
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none.
**/
void RCC_EnableLSECalibrationCount(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->LSEOS |= RCC_LSE_CALCNT_ENABLE;
    }
    else
    {
        RCC->LSEOS &= (~RCC_LSE_CALCNT_ENABLE);
    }
}

/**
*\*\name    RCC_GetLSECalibrationCount
*\*\fun     Get number of LSI clock counts in half cycle of LSE/128 clock.
*\*\param   none
*\*\return  Calibration Count
**/
uint8_t RCC_GetLSECalibrationCount(void)
{
    return (uint8_t)((RCC->LSEOS & RCC_LSE_CALCNT_MASK) >> 16);
}

/**
*\*\name    RCC_GetLSECSSFlag
*\*\fun     Checks whether the specified LSE CSS flag is set or not.
*\*\param   RCC_flag (The input parameters must be the following values):
*\*\        -RCC_FLAG_LSECSS_CALCNTRD
*\*\        -RCC_FLAG_LSECSS_OFFSET
*\*\return  FlagStatus
*\*\          - SET
*\*\          - RESET
**/
FlagStatus RCC_GetLSECSSFlag(uint32_t RCC_flag)
{
    FlagStatus bitstatus;

    if ((RCC->LSEOS & RCC_flag) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
*\*\name    RCC_EnableLSEOffsetDetection.
*\*\fun     Enable frequency offset detection in LSE clock.
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none.
**/
void RCC_EnableLSEOffsetDetection(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->LSEOS |= RCC_LSE_OFFSET_ENABLE;
    }
    else
    {
        RCC->LSEOS &= (~RCC_LSE_OFFSET_ENABLE);
    }
}

/**
*\*\name    RCC_SetLSEOffsetThreshold.
*\*\fun     Threshold value for detection of frequency offset greater than 10% in LSE clock.
*\*\param   threshold_value:
*\*\        This parameter must be a number between 0 and 0xFF
*\*\return  none
**/
void RCC_SetLSEOffsetThreshold(uint8_t threshold_value)
{
    uint32_t temp_value;

    temp_value = RCC->LSEOS;
    /* Clear LSEOSTHR[7:0] bits */
    temp_value &= RCC_LSEOSTHR_MASK;
    /* Set the LSEOSTHR[7:0] bits according to threshold_value */
    temp_value |= (uint32_t)threshold_value;
    /* Store the new value */
    RCC->LSEOS = temp_value;
}

/**
*\*\name    RCC_EnableHSECalibrationCount.
*\*\fun     HSE calibration count enable.
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none.
**/
void RCC_EnableHSECalibrationCount(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->HSECAL |= RCC_HSE_CALCNT_ENABLE;
    }
    else
    {
        RCC->HSECAL &= (~RCC_HSE_CALCNT_ENABLE);
    }
}

/**
*\*\name    RCC_GetHSECalibrationCount
*\*\fun     Get number of HSI clock counts in half cycle of HSE/128 clock.
*\*\param   none
*\*\return  Calibration Count
**/
uint16_t RCC_GetHSECalibrationCount(void)
{
    return (uint16_t)(RCC->HSECAL & RCC_HSE_CALCNT_MASK);
}

/**
*\*\name    RCC_GetHSECSSFlag
*\*\fun     Checks whether the specified HSE CSS flag is set or not.
*\*\param   RCC_flag (The input parameters must be the following values):
*\*\        -RCC_FLAG_HSECSS_CALCNTRD
*\*\        -RCC_FLAG_HSECSS_OFFSET
*\*\        -RCC_FLAG_HSECSS_MAXPD
*\*\        -RCC_FLAG_HSECSS_MINND
*\*\return  FlagStatus
*\*\          - SET
*\*\          - RESET
**/
FlagStatus RCC_GetHSECSSFlag(uint32_t RCC_flag)
{
    FlagStatus bitstatus;
    uint32_t reg_value;

    if(RCC_flag == RCC_FLAG_HSECSS_CALCNTRD)
    {
        reg_value = RCC->HSECAL;
    }
    else
    {
        reg_value = RCC->HSEOS;
    }

    if ((reg_value & RCC_flag) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
*\*\name    RCC_EnableHSECSSCheck.
*\*\fun     Enable different HSE CSS detection type .
*\*\param   Chk_type :
*\*\         - RCC_HSECSS_OFFSET    enable frequency offset detection
*\*\         - RCC_HSECSS_MAXPD     enable detection of positive deviation
*\*\         - RCC_HSECSS_MINND     enable detection of negative deviation
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none.
**/
void RCC_EnableHSECSSCheck(uint32_t Chk_type, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->HSEOS |= Chk_type;
    }
    else
    {
        RCC->HSEOS &= ~Chk_type;
    }

}

/**
*\*\name    RCC_SetHSEOffsetThreshold.
*\*\fun     Threshold value for detection of frequency offset greater than 5% in HSE clock.
*\*\param   threshold_value:
*\*\        This parameter must be a number between 0 and 0xFF
*\*\return  none
**/
void RCC_SetHSEOffsetThreshold(uint8_t threshold_value)
{
    uint32_t temp_value;

    temp_value = RCC->HSEOS;
    /* Clear HSEOSTHR[7:0] bits */
    temp_value &= RCC_HSEOSTHR_MASK;
    /* Set the HSEOSTHR[7:0] bits according to threshold_value */
    temp_value |= ((uint32_t)threshold_value << 8);
    /* Store the new value */
    RCC->HSEOS = temp_value;
}

/**
*\*\name    RCC_SetHSEPositiveDeviationMAXThreshold.
*\*\fun     Threshold value for detection of positive deviation in HSE clock at maximum frequency.
*\*\param   threshold_value:
*\*\        This parameter must be a number between 0 and 0xFF
*\*\return  none
**/
void RCC_SetHSEPositiveDeviationMAXThreshold(uint8_t threshold_value)
{
    uint32_t temp_value;

    temp_value = RCC->HSEOS;
    /* Clear HSEMAXPDTHR[7:0] bits */
    temp_value &= RCC_HSEMAXPDTHR_MASK;
    /* Set the HSEMAXPDTHR[7:0] bits according to threshold_value */
    temp_value |= ((uint32_t)threshold_value << 24);
    /* Store the new value */
    RCC->HSEOS = temp_value;
}

/**
*\*\name    RCC_SetHSENegativeDeviationMINThreshold.
*\*\fun     Threshold value for detection of negative deviation in HSE clock at minimum frequency.
*\*\param   threshold_value:
*\*\        This parameter must be a number between 0 and 0xFF
*\*\return  none
**/
void RCC_SetHSENegativeDeviationMINThreshold(uint8_t threshold_value)
{
    uint32_t temp_value;

    temp_value = RCC->HSEOS;
    /* Clear HSEMINNDTHR[7:0] bits */
    temp_value &= RCC_HSEMINNDTHR_MASK;
    /* Set the HSEMINNDTHR[7:0] bits according to threshold_value */
    temp_value |= ((uint32_t)threshold_value << 16);
    /* Store the new value */
    RCC->HSEOS = temp_value;
}


/**
*\*\name    RCC_SetLSICSSDelayValue.
*\*\fun     This delay represents the estimated time required for the primary
*\*\        LSI clock to be stable during chip power up.
*\*\param   delay_value:
*\*\        This parameter must be a number between 0 and 0xFFFFFFFF
*\*\return  none
**/
void RCC_SetLSICSSDelayValue(uint32_t delay_value)
{
    /* Store the new value */
    RCC->LSICSSDL = delay_value;
}

/**
*\*\name    RCC_SetLSEReadyDelayValue.
*\*\fun     Config counter delay of LSE clock ready signal.
*\*\param   delay_value:
*\*\        This parameter must be a number between 0 and 0xFFFFFFFF
*\*\return  none
**/
void RCC_SetLSEReadyDelayValue(uint32_t delay_value)
{
    /* Store the new value */
    RCC->LSERDDL = delay_value;
}

/**
*\*\name    RCC_SetMSIReadyDelayValue.
*\*\fun     Config counter delay of MSI clock ready signal.
*\*\param   delay_value:
*\*\        This parameter must be a number between 0 and 0xFFFFFFFF
*\*\return  none
**/
void RCC_SetMSIReadyDelayValue(uint32_t delay_value)
{
    /* Store the new value */
    RCC->MSIRDDL = delay_value;
}

/**
*\*\name    RCC_SetHSEReadyDelayValue.
*\*\fun     Config counter delay of HSE clock ready signal.
*\*\param   delay_value:
*\*\        This parameter must be a number between 0 and 0xFFFFFFFF
*\*\return  none
**/
void RCC_SetHSEReadyDelayValue(uint32_t delay_value)
{
    /* Store the new value */
    RCC->HSERDDL = delay_value;
}


/**
*\*\name    RCC_EnablePLLFailDetection.
*\*\fun     Enable different pll fail detection.
*\*\param   Chk_type :
*\*\         - RCC_FAIL_DETECT_EN_SHRPLL
*\*\         - RCC_FAIL_DETECT_EN_PLL3
*\*\         - RCC_FAIL_DETECT_EN_PLL2
*\*\         - RCC_FAIL_DETECT_EN_PLL1
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none.
**/
void RCC_EnablePLLFailDetection(uint32_t Chk_type, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->PLLFD |= Chk_type;
    }
    else
    {
        RCC->PLLFD &= ~Chk_type;
    }

}


/**
*\*\name    RCC_EnableLPTIM1Filter.
*\*\fun     Control signal to select filtered or non-filtered LPTIM1 comparator clock source.
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none.
**/
void RCC_EnableLPTIM1Filter(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->RDCTRL1 |= RCC_LPTIM1FILT_ENABLE;
    }
    else
    {
        RCC->RDCTRL1 &= (~RCC_LPTIM1FILT_ENABLE);
    }
}

/**
*\*\name    RCC_SelectLPTIM1FilterSource.
*\*\fun     Control signal to select the sample clock for the digital filter used at LPTIM1.
*\*\param   CLK_source:
*\*\     - RCC_LPTIM1_FILTCLK_SRC_APB5
*\*\     - RCC_LPTIM1_FILTCLK_SRC_MSI
*\*\return  none.
**/
void RCC_SelectLPTIM1FilterSource(uint32_t CLK_source)
{
    if (CLK_source == RCC_LPTIM1_FILTCLK_SRC_MSI)
    {
        RCC->RDCTRL1 |= CLK_source;
    }
    else
    {
        RCC->RDCTRL1 &= CLK_source;
    }
}

/**
*\*\name    RCC_ConfigLPTIM1FilterWidth.
*\*\fun     Config LPTIM1 counter value indicating minimum pulse width in terms of APB5 or MSI clock cycles.
*\*\param   width_value :
*\*\          - 0x00            Disable the digital filter.
*\*\          - 0x01 ~ 0x1F     The numbers of APB5 or MSI cycles.
*\*\return  none
**/
void RCC_ConfigLPTIM1FilterWidth(uint8_t width_value)
{
    uint32_t temp_value;

    temp_value = RCC->RDCTRL1;
    /* Clear LPTIM1FLTDFC[4:0] bits */
    temp_value &= I2C_LPTIM1FLTDFC_MASK;
    /* Set LPTIM1FLTDFC[4:0] bits according to width value */
    temp_value |= ((uint32_t)width_value & 0x1FU);
    /* Store the new value */
    RCC->RDCTRL1 = temp_value;
}

/**
*\*\name    RCC_EnableLPTIM2Filter.
*\*\fun     Control signal to select filtered or non-filtered LPTIM2 comparator clock source.
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none.
**/
void RCC_EnableLPTIM2Filter(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->RDCTRL1 |= RCC_LPTIM2FILT_ENABLE;
    }
    else
    {
        RCC->RDCTRL1 &= (~RCC_LPTIM2FILT_ENABLE);
    }
}

/**
*\*\name    RCC_SelectLPTIM2FilterSource.
*\*\fun     Control signal to select the sample clock for the digital filter used at LPTIM2.
*\*\param   CLK_source:
*\*\     - RCC_LPTIM2_FILTCLK_SRC_APB5
*\*\     - RCC_LPTIM2_FILTCLK_SRC_MSI
*\*\return  none.
**/
void RCC_SelectLPTIM2FilterSource(uint32_t CLK_source)
{
    if (CLK_source == RCC_LPTIM2_FILTCLK_SRC_MSI)
    {
        RCC->RDCTRL1 |= CLK_source;
    }
    else
    {
        RCC->RDCTRL1 &= CLK_source;
    }
}

/**
*\*\name    RCC_ConfigLPTIM2FilterWidth.
*\*\fun     Config LPTIM2 counter value indicating minimum pulse width in terms of APB5 or MSI clock cycles.
*\*\param   width_value :
*\*\          - 0x00            Disable the digital filter.
*\*\          - 0x01 ~ 0x1F     The numbers of APB5 or MSI cycles.
*\*\return  none
**/
void RCC_ConfigLPTIM2FilterWidth(uint8_t width_value)
{
    uint32_t temp_value;

    temp_value = RCC->RDCTRL1;
    /* Clear LPTIM2FLTDFC[4:0] bits */
    temp_value &= I2C_LPTIM2FLTDFC_MASK;
    /* Set LPTIM2FLTDFC[4:0] bits according to width value */
    temp_value |= (((uint32_t)width_value & 0x1FU) << 16);
    /* Store the new value */
    RCC->RDCTRL1 = temp_value;
}

/**
*\*\name    RCC_EnableLPTIM3Filter.
*\*\fun     Control signal to select filtered or non-filtered LPTIM3 comparator clock source.
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none.
**/
void RCC_EnableLPTIM3Filter(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->RDCTRL2 |= RCC_LPTIM3FILT_ENABLE;
    }
    else
    {
        RCC->RDCTRL2 &= (~RCC_LPTIM3FILT_ENABLE);
    }
}

/**
*\*\name    RCC_SelectLPTIM3FilterSource.
*\*\fun     Control signal to select the sample clock for the digital filter used at LPTIM3.
*\*\param   CLK_source:
*\*\     - RCC_LPTIM3_FILTCLK_SRC_APB5
*\*\     - RCC_LPTIM3_FILTCLK_SRC_MSI
*\*\return  none.
**/
void RCC_SelectLPTIM3FilterSource(uint32_t CLK_source)
{
    if (CLK_source == RCC_LPTIM3_FILTCLK_SRC_MSI)
    {
        RCC->RDCTRL2 |= CLK_source;
    }
    else
    {
        RCC->RDCTRL2 &= CLK_source;
    }
}

/**
*\*\name    RCC_ConfigLPTIM3FilterWidth.
*\*\fun     Config LPTIM3 counter value indicating minimum pulse width in terms of APB5 or MSI clock cycles.
*\*\param   width_value :
*\*\          - 0x00            Disable the digital filter.
*\*\          - 0x01 ~ 0x1F     The numbers of APB5 or MSI cycles.
*\*\return  none
**/
void RCC_ConfigLPTIM3FilterWidth(uint8_t width_value)
{
    uint32_t temp_value;

    temp_value = RCC->RDCTRL2;
    /* Clear LPTIM3FLTDFC[4:0] bits */
    temp_value &= I2C_LPTIM3FLTDFC_MASK;
    /* Set LPTIM3FLTDFC[4:0] bits according to width value */
    temp_value |= ((uint32_t)width_value & 0x1FU);
    /* Store the new value */
    RCC->RDCTRL2 = temp_value;
}

/**
*\*\name    RCC_EnableLPTIM4Filter.
*\*\fun     Control signal to select filtered or non-filtered LPTIM4 comparator clock source.
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none.
**/
void RCC_EnableLPTIM4Filter(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->RDCTRL2 |= RCC_LPTIM4FILT_ENABLE;
    }
    else
    {
        RCC->RDCTRL2 &= (~RCC_LPTIM4FILT_ENABLE);
    }
}

/**
*\*\name    RCC_SelectLPTIM4FilterSource.
*\*\fun     Control signal to select the sample clock for the digital filter used at LPTIM4.
*\*\param   CLK_source:
*\*\     - RCC_LPTIM4_FILTCLK_SRC_APB5
*\*\     - RCC_LPTIM4_FILTCLK_SRC_MSI
*\*\return  none.
**/
void RCC_SelectLPTIM4FilterSource(uint32_t CLK_source)
{
    if (CLK_source == RCC_LPTIM4_FILTCLK_SRC_MSI)
    {
        RCC->RDCTRL2 |= CLK_source;
    }
    else
    {
        RCC->RDCTRL2 &= CLK_source;
    }
}

/**
*\*\name    RCC_ConfigLPTIM4FilterWidth.
*\*\fun     Config LPTIM4 counter value indicating minimum pulse width in terms of APB5 or MSI clock cycles.
*\*\param   width_value :
*\*\          - 0x00            Disable the digital filter.
*\*\          - 0x01 ~ 0x1F     The numbers of APB5 or MSI cycles.
*\*\return  none
**/
void RCC_ConfigLPTIM4FilterWidth(uint8_t width_value)
{
    uint32_t temp_value;

    temp_value = RCC->RDCTRL2;
    /* Clear LPTIM4FLTDFC[4:0] bits */
    temp_value &= I2C_LPTIM4FLTDFC_MASK;
    /* Set LPTIM4FLTDFC[4:0] bits according to width value */
    temp_value |= (((uint32_t)width_value & 0x1FU) << 16);
    /* Store the new value */
    RCC->RDCTRL2 = temp_value;
}

/**
*\*\name    RCC_EnableLPTIM5Filter.
*\*\fun     Control signal to select filtered or non-filtered LPTIM5 comparator clock source.
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none.
**/
void RCC_EnableLPTIM5Filter(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->RDCTRL3 |= RCC_LPTIM5FILT_ENABLE;
    }
    else
    {
        RCC->RDCTRL3 &= (~RCC_LPTIM5FILT_ENABLE);
    }
}

/**
*\*\name    RCC_SelectLPTIM5FilterSource.
*\*\fun     Control signal to select the sample clock for the digital filter used at LPTIM5.
*\*\param   CLK_source:
*\*\     - RCC_LPTIM5_FILTCLK_SRC_APB5
*\*\     - RCC_LPTIM5_FILTCLK_SRC_MSI
*\*\return  none.
**/
void RCC_SelectLPTIM5FilterSource(uint32_t CLK_source)
{
    if (CLK_source == RCC_LPTIM5_FILTCLK_SRC_MSI)
    {
        RCC->RDCTRL3 |= CLK_source;
    }
    else
    {
        RCC->RDCTRL3 &= CLK_source;
    }
}

/**
*\*\name    RCC_ConfigLPTIM5FilterWidth.
*\*\fun     Config LPTIM5 counter value indicating minimum pulse width in terms of APB5 or MSI clock cycles.
*\*\param   width_value :
*\*\          - 0x00            Disable the digital filter.
*\*\          - 0x01 ~ 0x1F     The numbers of APB5 or MSI cycles.
*\*\return  none
**/
void RCC_ConfigLPTIM5FilterWidth(uint8_t width_value)
{
    uint32_t temp_value;

    temp_value = RCC->RDCTRL3;
    /* Clear LPTIM5FLTDFC[4:0] bits */
    temp_value &= I2C_LPTIM5FLTDFC_MASK;
    /* Set LPTIM5FLTDFC[4:0] bits according to width value */
    temp_value |= ((uint32_t)width_value & 0x1FU);
    /* Store the new value */
    RCC->RDCTRL3 = temp_value;
}

/**
*\*\name    RCC_SetWWDG1ResetDelayValue.
*\*\fun     Counter threshold used to delay the assertion of WWDG1 reset when WWDG1 reset request event occurs.
*\*\param   delay_value:
*\*\        This parameter must be a number between 0 and 0xF
*\*\return  none
**/
void RCC_SetWWDG1ResetDelayValue(uint8_t delay_value)
{
    uint32_t temp_value;

    temp_value = RCC->CFG1;
    /* Clear WWDG1RSTDLCNT[3:0] bits */
    temp_value &= RCC_WWDG1RSTDLCNT_MASK;
    /* Set the WWDG1RSTDLCNT[3:0] bits according to delay_value */
    temp_value |= (((uint32_t)delay_value & 0xFU) << 16);
    /* Store the new value */
    RCC->CFG1 = temp_value;
}

/**
*\*\name    RCC_SetWWDG2ResetDelayValue.
*\*\fun     Counter threshold used to delay the assertion of WWDG2 reset when WWDG2 reset request event occurs.
*\*\param   delay_value:
*\*\        This parameter must be a number between 0 and 0xF
*\*\return  none
**/
void RCC_SetWWDG2ResetDelayValue(uint8_t delay_value)
{
    uint32_t temp_value;

    temp_value = RCC->CFG1;
    /* Clear WWDG2RSTDLCNT[3:0] bits */
    temp_value &= RCC_WWDG2RSTDLCNT_MASK;
    /* Set the WWDG2RSTDLCNT[3:0] bits according to delay_value */
    temp_value |= (((uint32_t)delay_value & 0xFU) << 20);
    /* Store the new value */
    RCC->CFG1 = temp_value;
}

/**
*\*\name   RCC_ConfigM7TraceClkDivider .
*\*\fun    Configure M7 trace clock prescalar values.
*\*\param  CLK_divider
*\*\       - RCC_TRACECLK_DIV1
*\*\       - RCC_TRACECLK_DIV2
*\*\       - RCC_TRACECLK_DIV4
*\*\       - RCC_TRACECLK_DIV8
*\*\       - RCC_TRACECLK_DIV16
*\*\       - RCC_TRACECLK_DIV32
*\*\       - RCC_TRACECLK_DIV64
*\*\       - RCC_TRACECLK_DIV128
*\*\       - RCC_TRACECLK_DIV256
*\*\       - RCC_TRACECLK_DIV512
*\*\return none.
**/
void RCC_ConfigM7TraceClkDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->CFG1;
    /* Clear M7TRACEDIV bits */
    reg_value &=  RCC_M7TRACECLK_DIV_MASK;
    /* Set the M7TRACEDIV bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->CFG1 = reg_value;
}

/**
*\*\name   RCC_ConfigM4TraceClkDivider .
*\*\fun    Configure M4 trace clock prescalar values.
*\*\param  CLK_divider
*\*\       - RCC_TRACECLK_DIV1
*\*\       - RCC_TRACECLK_DIV2
*\*\       - RCC_TRACECLK_DIV4
*\*\       - RCC_TRACECLK_DIV8
*\*\       - RCC_TRACECLK_DIV16
*\*\       - RCC_TRACECLK_DIV32
*\*\       - RCC_TRACECLK_DIV64
*\*\       - RCC_TRACECLK_DIV128
*\*\       - RCC_TRACECLK_DIV256
*\*\       - RCC_TRACECLK_DIV512
*\*\return none.
**/
void RCC_ConfigM4TraceClkDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->CFG1;
    /* Clear M4TRACEDIV bits */
    reg_value &=  RCC_M4TRACECLK_DIV_MASK;
    /* Set the M4TRACEDIV bits */
    reg_value |=  (CLK_divider >> 4);
    /* Store the new value */
    RCC->CFG1 = reg_value;
}


/**
*\*\name   RCC_ConfigM7SystickClkDivider .
*\*\fun    Configure M7 systick prescalar values from fclk.
*\*\param  CLK_divider
*\*\       - RCC_STCLK_DIV1
*\*\       - RCC_STCLK_DIV2
*\*\       - RCC_STCLK_DIV4
*\*\       - RCC_STCLK_DIV8
*\*\       - RCC_STCLK_DIV16
*\*\       - RCC_STCLK_DIV32
*\*\       - RCC_STCLK_DIV64
*\*\       - RCC_STCLK_DIV128
*\*\       - RCC_STCLK_DIV256
*\*\       - RCC_STCLK_DIV512
*\*\return none.
**/
void RCC_ConfigM7SystickClkDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->CFG3;
    /* Clear M7STCLKDIV bits */
    reg_value &=  RCC_M7STCLK_DIV_MASK;
    /* Set the M7STCLKDIV bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->CFG3 = reg_value;
}

/**
*\*\name   RCC_ConfigM4SystickClkDivider .
*\*\fun    Configure M4 systick prescalar values from fclk.
*\*\param  CLK_divider
*\*\       - RCC_STCLK_DIV2
*\*\       - RCC_STCLK_DIV4
*\*\       - RCC_STCLK_DIV8
*\*\       - RCC_STCLK_DIV16
*\*\       - RCC_STCLK_DIV32
*\*\       - RCC_STCLK_DIV64
*\*\       - RCC_STCLK_DIV128
*\*\       - RCC_STCLK_DIV256
*\*\       - RCC_STCLK_DIV512
*\*\return none.
*\*\note DIV1 is not supported
**/
void RCC_ConfigM4SystickClkDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->CFG3;
    /* Clear M4STCLKDIV bits */
    reg_value &=  RCC_M4STCLK_DIV_MASK;
    /* Set the M4STCLKDIV bits */
    reg_value |=  (CLK_divider >> 4);
    /* Store the new value */
    RCC->CFG3 = reg_value;
}

/**
*\*\name    RCC_EnableDualCoreDebugClk.
*\*\fun     Dual core debug clock enable.
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none.
**/
void RCC_EnableDualCoreDebugClk(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->CFG5 |= RCC_DUALCORE_DBG_ENABLE;
    }
    else
    {
        RCC->CFG5 &= (~RCC_DUALCORE_DBG_ENABLE);
    }
}

/**
*\*\name   RCC_ConfigRTCHSIClkDivider .
*\*\fun    RTC HSI clock prescalar values.
*\*\param  CLK_divider
*\*\       - RCC_RTCCLK_HSIDIV1
*\*\       - RCC_RTCCLK_HSIDIV2
*\*\       - RCC_RTCCLK_HSIDIV4
*\*\       - RCC_RTCCLK_HSIDIV8
*\*\       - RCC_RTCCLK_HSIDIV16
*\*\       - RCC_RTCCLK_HSIDIV32
*\*\       - RCC_RTCCLK_HSIDIV64
*\*\       - RCC_RTCCLK_HSIDIV128
*\*\       - RCC_RTCCLK_HSIDIV256
*\*\       - RCC_RTCCLK_HSIDIV512
*\*\return none.
**/
void RCC_ConfigRTCHSIClkDivider(uint32_t CLK_divider)
{
    uint32_t reg_value;

    reg_value = RCC->CFG5;
    /* Clear RTCHSIDIV  bits */
    reg_value &=  RCC_RTCCLK_HSIDIV_MASK;
    /* Set the RTCHSIDIV  bits */
    reg_value |=  CLK_divider;
    /* Store the new value */
    RCC->CFG5 = reg_value;
}

/**
*\*\name    RCC_EnablePLLSoftwareLock.
*\*\fun     Enable this bit if hardware PLL lock fail.
*\*\param   lock_type :
*\*\         - RCC_SOFTLOCK_EN_SHRPLL
*\*\         - RCC_SOFTLOCK_EN_PLL3
*\*\         - RCC_SOFTLOCK_EN_PLL2
*\*\         - RCC_SOFTLOCK_EN_PLL1
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none.
**/
void RCC_EnablePLLSoftwareLock(uint32_t lock_type, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->PLLSFTLK |= lock_type;
    }
    else
    {
        RCC->PLLSFTLK &= ~lock_type;
    }

}

/**
*\*\name    RCC_EnableSHRTIMAFEReset.
*\*\fun     Used to assert POR reset to SHRTIM AFE.
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none.
**/
void RCC_EnableSHRTIMAFEReset(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->PLLSFTLK &= (~RCC_SHRTIMAFE_RESET_ENABLE);
    }
    else
    {
        RCC->PLLSFTLK |= RCC_SHRTIMAFE_RESET_ENABLE;
    }
}

/**
*\*\name    RCC_EnableSDRAMDelayChain.
*\*\fun     SDRAM Delay chain enable.
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none.
**/
void RCC_EnableSDRAMDelayChain(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->PLLSFTLK |= RCC_SDRAM_DELAY_ENABLE;
    }
    else
    {
        RCC->PLLSFTLK &= (~RCC_SDRAM_DELAY_ENABLE);
    }
}

/**
*\*\name   RCC_ConfigSDRAMDelay .
*\*\fun    Increase SDRAM clock latency.
*\*\param  CLK_delay
*\*\       - RCC_SDRAM_DELAY_0_2NS    Increase SDRAM clock latency by 0.2ns
*\*\       - RCC_SDRAM_DELAY_0_4NS    Increase SDRAM clock latency by 0.4ns
*\*\       - RCC_SDRAM_DELAY_0_6NS    Increase SDRAM clock latency by 0.6ns
*\*\       - RCC_SDRAM_DELAY_0_8NS    Increase SDRAM clock latency by 0.8ns
*\*\       - RCC_SDRAM_DELAY_1_0NS    Increase SDRAM clock latency by 1.0ns
*\*\       - RCC_SDRAM_DELAY_1_2NS    Increase SDRAM clock latency by 1.2ns
*\*\       - RCC_SDRAM_DELAY_1_4NS    Increase SDRAM clock latency by 1.4ns
*\*\       - RCC_SDRAM_DELAY_1_6NS    Increase SDRAM clock latency by 1.6ns
*\*\       - RCC_SDRAM_DELAY_1_8NS    Increase SDRAM clock latency by 1.8ns
*\*\       - RCC_SDRAM_DELAY_2_0NS    Increase SDRAM clock latency by 2.0ns
*\*\       - RCC_SDRAM_DELAY_2_2NS    Increase SDRAM clock latency by 2.2ns
*\*\       - RCC_SDRAM_DELAY_2_4NS    Increase SDRAM clock latency by 2.4ns
*\*\       - RCC_SDRAM_DELAY_2_6NS    Increase SDRAM clock latency by 2.6ns
*\*\       - RCC_SDRAM_DELAY_2_8NS    Increase SDRAM clock latency by 2.8ns
*\*\       - RCC_SDRAM_DELAY_3_0NS    Increase SDRAM clock latency by 3.0ns
*\*\       - RCC_SDRAM_DELAY_3_2NS    Increase SDRAM clock latency by 3.2ns
*\*\return none.
**/
void RCC_ConfigSDRAMDelay(uint32_t CLK_delay)
{
    uint32_t reg_value;

    reg_value = RCC->PLLSFTLK;
    /* Clear SDRAMDLSEL  bits */
    reg_value &=  RCC_SDRAM_DELAY_MASK;
    /* Set the SDRAMDLSEL  bits */
    reg_value |=  CLK_delay;
    /* Store the new value */
    RCC->PLLSFTLK = reg_value;
}

/**
*\*\name   RCC_ConfigHSEDriveStrength .
*\*\fun    Config HSE drive strength.
*\*\param  CLK_driver
*\*\       - 0x0 ~ 0x7 (min drive strength ~ max drive strength)
*\*\       - default value: 0x4
*\*\return none.
**/
void RCC_ConfigHSEDriveStrength(uint32_t CLK_driver)
{
    uint32_t reg_value;

    reg_value = AFEC->TRIMR1;
    /* Clear SDRAMDLSEL  bits */
    reg_value &=  0xFFF1FFFFU;
    /* Set the SDRAMDLSEL  bits */
    reg_value |=  (CLK_driver << 17U);
    /* Store the new value */
    AFEC->TRIMR1 = reg_value;
}

