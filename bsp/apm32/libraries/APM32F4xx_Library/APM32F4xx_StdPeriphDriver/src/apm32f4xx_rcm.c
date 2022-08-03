/*!
 * @file        apm32f4xx_rcm.c
 *
 * @brief       This file provides all the RCM firmware functions
 *
 * @version     V1.0.2
 *
 * @date        2022-06-23
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#include "apm32f4xx_rcm.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @defgroup RCM_Driver
  * @brief RCM driver modules
  @{
*/

/** @defgroup RCM_Functions
  @{
*/

/*!
 * @brief     Resets the clock configuration to the default state
 *
 * @param     None
 *
 * @retval    None
 */
void RCM_Reset(void)
{
    /* Open HSI clock */
    RCM->CTRL_B.HSIEN = BIT_SET;
    /* Clear CFG register */
    RCM->CFG = (uint32_t)0x00000000;
    /* Reset HSEON, CSSON, PLLON, PLLI2S bits */
    RCM->CTRL &= (uint32_t)0xEAF6FFFF;

    /* Reset PLL1CFG register */
    RCM->PLL1CFG = 0x24003010;
    /* Reset PLL2CFG register */
    RCM->PLL2CFG = 0x20003000;

    /* Reset HSEBCFG bit */
    RCM->CTRL_B.HSEBCFG = BIT_RESET;

    /* Disable all interrupts and clear pending bits */
    RCM->INT = 0x00000000;
}

/*!
 * @brief     Configs the HSE oscillator
 *
 * @param     state: state of the HSE
 *                   This parameter can be one of the following values:
 *                   @arg RCM_HSE_CLOSE  : Turn off the HSE oscillator
 *                   @arg RCM_HSE_OPEN   : Turn on the HSE oscillator
 *                   @arg RCM_HSE_BYPASS : HSE oscillator bypassed with external clock
 *
 * @retval    None
 *
 * @note      When HSE is not used directly or through the PLL as system clock, it can be stopped.
 */
void RCM_ConfigHSE(RCM_HSE_T state)
{
    /* Reset HSEEN bit */
    RCM->CTRL_B.HSEEN = BIT_RESET;

    /* Reset HSEBCFG bit */
    RCM->CTRL_B.HSEBCFG = BIT_RESET;

    if (state == RCM_HSE_OPEN)
    {
        RCM->CTRL_B.HSEEN = BIT_SET;
    }
    else if (state == RCM_HSE_BYPASS)
    {
        RCM->CTRL_B.HSEBCFG = BIT_SET;
        RCM->CTRL_B.HSEEN = BIT_SET;
    }
}

/*!
 * @brief     Waits for HSE to be ready
 *
 * @param     None
 *
 * @retval    SUCCESS: HSE oscillator is ready
 *            ERROR  : HSE oscillator is not ready
 */

uint8_t RCM_WaitHSEReady(void)
{
    __IO uint32_t cnt;

    for (cnt = 0; cnt < HSE_STARTUP_TIMEOUT; cnt++)
    {
        if (RCM->CTRL_B.HSERDYFLG == BIT_SET)
        {
            return SUCCESS;
        }
    }

    return ERROR;
}

/*!
 * @brief     Config HSI trimming value
 *
 * @param     HSITrim: HSI trimming value
 *                     This parameter must be a number between 0 and 0x1F.
 *
 * @retval    None
 */
void RCM_ConfigHSITrim(uint8_t HSITrim)
{
    RCM->CTRL_B.HSITRIM = HSITrim;
}

/*!
 * @brief     Enable the HSI
 *
 * @param     None
 *
 * @retval    None
 */
void RCM_EnableHSI(void)
{
    RCM->CTRL_B.HSIEN = BIT_SET;
}

/*!
 * @brief     Disable the HSI
 *
 * @param     None
 *
 * @retval    None
 *
 * @note      When HSI is not used directly or through the PLL as system clock, it can be stopped.
 */

void RCM_DisableHSI(void)
{
    RCM->CTRL_B.HSIEN = BIT_RESET;
}

/*!
 * @brief     Configures the External Low Speed oscillator (LSE)
 *
 * @param     state : Specifies the new state of the LSE
 *                    This parameter can be one of the following values:
 *                    @arg RCM_LSE_CLOSE  : Close the LSE
 *                    @arg RCM_LSE_OPEN   : Open the LSE
 *                    @arg RCM_LSE_BYPASS : LSE bypass
 *
 * @retval    None
 */
void RCM_ConfigLSE(RCM_LSE_T state)
{
    RCM->BDCTRL_B.LSEEN = BIT_RESET;
    RCM->BDCTRL_B.LSEBCFG = BIT_RESET;

    if (state == RCM_LSE_OPEN)
    {
        RCM->BDCTRL_B.LSEEN = BIT_SET;
    }
    else if (state == RCM_LSE_BYPASS)
    {
        RCM->BDCTRL_B.LSEBCFG = BIT_SET;
        RCM->BDCTRL_B.LSEEN = BIT_SET;
    }
}

/*!
 * @brief     Enables the Internal Low Speed oscillator (LSI)
 *
 * @param     None
 *
 * @retval    None
 */
void RCM_EnableLSI(void)
{
    RCM->CSTS_B.LSIEN = BIT_SET;
}

/*!
 * @brief     Disables the Internal Low Speed oscillator (LSI)
 *
 * @param     None
 *
 * @retval    None
 */
void RCM_DisableLSI(void)
{
    RCM->CSTS_B.LSIEN = BIT_RESET;
}

/*!
 * @brief     Configures the main PLL clock source, multiplication and division factors
 *
 * @param     pllSelect: PLL entry clock source select
 *                       This parameter can be one of the following values:
 *                       @arg RCM_PLLSEL_HSI: HSI oscillator clock selected as PLL clock entry
 *                       @arg RCM_PLLSEL_HSE: HSE oscillator clock selected as PLL clock entry
 *
 * @param     inputDiv: specifies the Division factor for PLL VCO input clock
 *                      This parameter must be a number between 0 and 63
 *
 * @param     vcoMul: specifies the Multiplication factor for PLL VCO output clock
 *                    This parameter must be a number between 50 and 432
 *
 * @param     sysDiv: specifies the Division factor for main system clock (SYSCLK)
 *                    This parameter can be one of the following values:
 *                    @arg RCM_PLL_SYS_DIV_2 : system clock Division factor is 2
 *                    @arg RCM_PLL_SYS_DIV_4 : system clock Division factor is 4
 *                    @arg RCM_PLL_SYS_DIV_6 : system clock Division factor is 6
 *                    @arg RCM_PLL_SYS_DIV_8 : system clock Division factor is 8
 *
 * @param     appDiv: specifies the Division factor for OTG FS, SDIO and RNG clocks
 *                    This parameter must be a number between 4 and 15
 *
 * @retval    None
 */
void RCM_ConfigPLL1(uint32_t pllSelect, uint32_t inputDiv, uint32_t vcoMul,
                    RCM_PLL_SYS_DIV_T sysDiv, uint32_t appDiv)
{
    RCM->PLL1CFG_B.PLL1CLKS = pllSelect;
    RCM->PLL1CFG_B.PLLB = inputDiv;
    RCM->PLL1CFG_B.PLL1A = vcoMul;
    RCM->PLL1CFG_B.PLL1C = sysDiv;
    RCM->PLL1CFG_B.PLLD = appDiv;
}

/*!
 * @brief      Enables the PLL1
 *
 * @param      None
 *
 * @retval     None
 */
void RCM_EnablePLL1(void)
{
    RCM->CTRL_B.PLL1EN = BIT_SET;
}

/*!
 * @brief      Disable the PLL
 *
 * @param      None
 *
 * @retval     None
 *
 * @note       When PLL1 is not used as system clock, it can be stopped.
 */
void RCM_DisablePLL1(void)
{
    RCM->CTRL_B.PLL1EN = BIT_RESET;
}

/*!
 * @brief     Configures the RCM_PLL2CFG register
 *
 * @param     i2sVcoMul: specifies the multiplication factor for PLLI2S VCO output clock
 *                       This parameter must be a number between 50 and 432
 *
 * @param     i2sDiv: specifies the division factor for I2S clock
 *                    This parameter must be a number between 2 and 7
 *
 * @retval    None
 */
void RCM_ConfigPLL2(uint32_t i2sVcoMul, uint32_t i2sDiv)
{
    RCM->PLL2CFG_B.PLL2A = i2sVcoMul;
    RCM->PLL2CFG_B.PLL2C = i2sDiv;
}

/*!
 * @brief      Enables the PLL2
 *
 * @param      None
 *
 * @retval     None
 */
void RCM_EnablePLL2(void)
{
    RCM->CTRL_B.PLL2EN = BIT_SET;
}

/*!
 * @brief      Disable the PLL2
 *
 * @param      None
 *
 * @retval     None
 */
void RCM_DisablePLL2(void)
{
    RCM->CTRL_B.PLL2EN = BIT_RESET;
}

/*!
 * @brief     Enable the Clock Security System
 *
 * @param     None
 *
 * @retval    None
 */
void RCM_EnableCSS(void)
{
    RCM->CTRL_B.CSSEN = BIT_SET;
}

/*!
 * @brief     Disable the Clock Security System
 *
 * @param     None
 *
 * @retval    None
 */
void RCM_DisableCSS(void)
{
    RCM->CTRL_B.CSSEN = BIT_RESET;
}

/*!
 * @brief     Selects the clock source to output on MCO1 pin
 *
 * @param     mco1Div: specifies the clock source to output
 *                     This parameter can be one of the following values:
 *                     @arg RCM_MCO1_SEL_HSICLK : HSI clock selected as MCO1 source
 *                     @arg RCM_MCO1_SEL_LSECLK : LSE clock selected as MCO1 source
 *                     @arg RCM_MCO1_SEL_HSECLK : HSE clock selected as MCO1 source
 *                     @arg RCM_MCO1_SEL_PLLCLK : main PLL clock selected as MCO1 source
 *
 * @param     mco1Div: specifies the MCO1 prescaler
 *                     This parameter can be one of the following values:
 *                     @arg RCM_MCO1_DIV_1 : no division applied to MCO1 clock
 *                     @arg RCM_MCO1_DIV_2 : division by 2 applied to MCO1 clock
 *                     @arg RCM_MCO1_DIV_3 : division by 3 applied to MCO1 clock
 *                     @arg RCM_MCO1_DIV_4 : division by 4 applied to MCO1 clock
 *                     @arg RCM_MCO1_DIV_5 : division by 5 applied to MCO1 clock
 *
 * @retval    None
 */
void RCM_ConfigMCO1(RCM_MCO1_SEL_T mco1Select, RCM_MCO1_DIV_T mco1Div)
{
    RCM->CFG_B.MCO1SEL = mco1Select;
    RCM->CFG_B.MCO1PRE = mco1Div;
}

/*!
 * @brief     Selects the clock source to output on MCO2 pin
 *
 * @param     mco2Select: specifies the clock source to output
 *                        This parameter can be one of the following values:
 *                        @arg RCM_MCO2_SEL_SYSCLK  : SYS clock selected as MCO2 source
 *                        @arg RCM_MCO2_SEL_PLL2CLK : PLL2 clock selected as MCO2 source
 *                        @arg RCM_MCO2_SEL_HSECLK  : HSE clock selected as MCO2 source
 *                        @arg RCM_MCO2_SEL_PLLCLK  : PLL clock selected as MCO2 source
 *
 * @param     mco2Div: specifies the MCO2 prescaler
 *                     This parameter can be one of the following values:
 *                     @arg RCM_MCO2_DIV_1 : no division applied to MCO2 clock
 *                     @arg RCM_MCO2_DIV_2 : division by 2 applied to MCO2 clock
 *                     @arg RCM_MCO2_DIV_3 : division by 3 applied to MCO2 clock
 *                     @arg RCM_MCO2_DIV_4 : division by 4 applied to MCO2 clock
 *                     @arg RCM_MCO2_DIV_5 : division by 5 applied to MCO2 clock
 *
 * @retval    None
 */
void RCM_ConfigMCO2(RCM_MCO2_SEL_T mco2Select, RCM_MCO2_DIV_T mco2Div)
{
    RCM->CFG_B.MCO2SEL = mco2Select;
    RCM->CFG_B.MCO2PRE = mco2Div;
}

/*!
 * @brief    Configures the system clock source
 *
 * @param    sysClkSelect: specifies the clock source used as system clock
 *                         This parameter can be one of the following values:
 *                         @arg RCM_SYSCLK_SEL_HSI : HSI is selected as system clock source
 *                         @arg RCM_SYSCLK_SEL_HSE : HSE is selected as system clock source
 *                         @arg RCM_SYSCLK_SEL_PLL : PLL is selected as system clock source
 *
 * @retva    None
 */
void RCM_ConfigSYSCLK(RCM_SYSCLK_SEL_T sysClkSelect)
{
    RCM->CFG_B.SCLKSEL = sysClkSelect;
}

/*!
 * @brief     Returns the clock source which is used as system clock
 *
 * @param     None
 *
 * @retval    The clock source used as system clock
 */
RCM_SYSCLK_SEL_T RCM_ReadSYSCLKSource(void)
{
    return (RCM_SYSCLK_SEL_T)RCM->CFG_B.SCLKSWSTS;
}

/*!
 * @brief     Configs the AHB clock prescaler.
 *
 * @param     AHBDiv : Specifies the AHB clock prescaler from the system clock.
 *                     This parameter can be one of the following values:
 *                     @arg RCM_AHB_DIV_1   : HCLK = SYSCLK
 *                     @arg RCM_AHB_DIV_2   : HCLK = SYSCLK / 2
 *                     @arg RCM_AHB_DIV_4   : HCLK = SYSCLK / 4
 *                     @arg RCM_AHB_DIV_8   : HCLK = SYSCLK / 8
 *                     @arg RCM_AHB_DIV_16  : HCLK = SYSCLK / 16
 *                     @arg RCM_AHB_DIV_64  : HCLK = SYSCLK / 64
 *                     @arg RCM_AHB_DIV_128 : HCLK = SYSCLK / 128
 *                     @arg RCM_AHB_DIV_256 : HCLK = SYSCLK / 256
 *                     @arg RCM_AHB_DIV_512 : HCLK = SYSCLK / 512
 *
 * @retval    None
 */
void RCM_ConfigAHB(RCM_AHB_DIV_T AHBDiv)
{
    RCM->CFG_B.AHBPSC = AHBDiv;
}

/*!
 * @brief     Configs the APB1 clock prescaler.
 *
 * @param     APB1Div: Specifies the APB1 clock prescaler from the AHB clock.
 *                     This parameter can be one of the following values:
 *                     @arg RCM_APB_DIV_1  : PCLK1 = HCLK
 *                     @arg RCM_APB_DIV_2  : PCLK1 = HCLK / 2
 *                     @arg RCM_APB_DIV_4  : PCLK1 = HCLK / 4
 *                     @arg RCM_APB_DIV_8  : PCLK1 = HCLK / 8
 *                     @arg RCM_APB_DIV_16 : PCLK1 = HCLK / 16
 *
 * @retval    None
 */
void RCM_ConfigAPB1(RCM_APB_DIV_T APB1Div)
{
    RCM->CFG_B.APB1PSC = APB1Div;
}

/*!
 * @brief     Configs the APB2 clock prescaler
 *
 * @param     APB2Div: Specifies the APB2 clock prescaler from the AHB clock.
 *                     This parameter can be one of the following values:
 *                     @arg RCM_APB_DIV_1  : PCLK2 = HCLK
 *                     @arg RCM_APB_DIV_2  : PCLK2 = HCLK / 2
 *                     @arg RCM_APB_DIV_4  : PCLK2 = HCLK / 4
 *                     @arg RCM_APB_DIV_8  : PCLK2 = HCLK / 8
 *                     @arg RCM_APB_DIV_16 : PCLK2 = HCLK / 16
 *
 * @retval    None
 */
void RCM_ConfigAPB2(RCM_APB_DIV_T APB2Div)
{
    RCM->CFG_B.APB2PSC = APB2Div;
}

/*!
 * @brief     Configs the SDRAM clock prescaler
 *
 * @param     SDRAMDiv: Specifies the SDRAM clock prescaler from the DMC clock.
 *                     This parameter can be one of the following values:
 *                     @arg RCM_SDRAM_DIV_1 : SDRAM clock = DMC clock
 *                     @arg RCM_SDRAM_DIV_2 : SDRAM clock = DMC clock / 2
 *                     @arg RCM_SDRAM_DIV_4 : SDRAM clock = DMC clock / 4
 *
 * @retval    None
 */
void RCM_ConfigSDRAM(RCM_SDRAM_DIV_T SDRAMDiv)
{
    RCM->CFG_B.SDRAMPSC = SDRAMDiv;
}

/*!
 * @brief     Reads the frequency of SYSCLK
 *
 * @param     None
 *
 * @retval    Return the frequency of SYSCLK
 */
uint32_t RCM_ReadSYSCLKFreq(void)
{
    uint32_t sysClock, pllMull, pllSource, pllvco;

    /* get sys clock */
    sysClock = RCM->CFG_B.SCLKSWSTS;

    switch (sysClock)
    {
    /* sys clock is HSI */
    case RCM_SYSCLK_SEL_HSI:
        sysClock = HSI_VALUE;
        break;

    /* sys clock is HSE */
    case RCM_SYSCLK_SEL_HSE:
        sysClock = HSE_VALUE;
        break;

    /* sys clock is PLL */
    case RCM_SYSCLK_SEL_PLL:
        pllMull = RCM->PLL1CFG_B.PLLB;
        pllSource = RCM->PLL1CFG_B.PLL1CLKS;

        /* PLL entry clock source is HSE */
        if (pllSource == BIT_SET)
        {
            /* HSE used as PLL clock source */
            pllvco = (HSE_VALUE / pllMull) * (RCM->PLL1CFG_B.PLL1A);
        }
        else
        {
            /* HSI used as PLL clock source */
            pllvco = (HSI_VALUE / pllMull) * (RCM->PLL1CFG_B.PLL1A);
        }

        sysClock = pllvco / ((RCM->PLL1CFG_B.PLL1C + 1) * 2);
        break;

    default:
        sysClock  = HSI_VALUE;
        break;
    }

    return sysClock;
}

/*!
 * @brief     Reads the frequency of HCLK(AHB)
 *
 * @param     None
 *
 * @retval    Return the frequency of HCLK
 */
uint32_t RCM_ReadHCLKFreq(void)
{
    uint32_t divider;
    uint32_t sysClk, hclk;
    uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

    sysClk = RCM_ReadSYSCLKFreq();
    divider = AHBPrescTable[RCM->CFG_B.AHBPSC];
    hclk = sysClk >> divider;

    return hclk;
}

/*!
 * @brief     Reads the frequency of PCLK1 And PCLK2
 *
 * @param     PCLK1 : Return the frequency of PCLK1
 *
 * @param     PCLK1 : Return the frequency of PCLK2
 *
 * @retval    None
 */
void RCM_ReadPCLKFreq(uint32_t *PCLK1, uint32_t *PCLK2)
{
    uint32_t hclk, divider;
    uint8_t APBPrescTable[8] = {0, 0, 0, 0, 1, 2, 3, 4};

    hclk = RCM_ReadHCLKFreq();

    if (PCLK1)
    {
        divider = APBPrescTable[RCM->CFG_B.APB1PSC];
        *PCLK1 = hclk >> divider;
    }

    if (PCLK2)
    {
        divider = APBPrescTable[RCM->CFG_B.APB2PSC];
        *PCLK2 = hclk >> divider;
    }
}

/*!
 * @brief     Configures the RTC clock source
 *
 * @param     rtcClkSelect : specifies the RTC clock source.
 *                           This parameter can be one of the following values:
 *                           @arg RCM_RTCCLK_LSE        : RTCCLK = LSE clock
 *                           @arg RCM_RTCCLK_LSI        : RTCCLK = LSI clock
 *                           @arg RCM_RTCCLK_HSE_DIVX   : X:[2:31]
 *
 * @retval    None
 */
void RCM_ConfigRTCCLK(RCM_RTCCLK_T rtcClkSelect)
{
    if (rtcClkSelect <= 1)
    {
        RCM->BDCTRL_B.RTCSRCSEL = (rtcClkSelect + 1);
    }

    else
    {
        RCM->BDCTRL_B.RTCSRCSEL = 3;
        RCM->CFG_B.RTCPSC = rtcClkSelect;
    }
}

/*!
 * @brief     Enables the RTC clock
 *
 * @param     None
 *
 * @retval    None
 */
void RCM_EnableRTCCLK(void)
{
    RCM->BDCTRL_B.RTCCLKEN = BIT_SET;
}

/*!
 * @brief     Disables the RTC clock
 *
 * @param     None
 *
 * @retval    None
 */
void RCM_DisableRTCCLK(void)
{
    RCM->BDCTRL_B.RTCCLKEN = BIT_RESET;
}
/*!
 * @brief     Enable the Backup domain reset
 *
 * @param     None
 *
 * @retval    None
 *
 * @note
 */
void RCM_EnableBackupReset(void)
{
    RCM->BDCTRL_B.BDRST = BIT_SET;
}

/*!
 * @brief     Disable the Backup domain reset
 *
 * @param     None
 *
 * @retval    None
 */
void RCM_DisableBackupReset(void)
{
    RCM->BDCTRL_B.BDRST = BIT_RESET;
}

/*!
 * @brief     Configures the I2S clock source (I2SCLK)
 *
 * @param     i2sClkSource: specifies the I2S clock source
 *                          This parameter can be one of the following values:
 *                          @arg RCM_I2S_CLK_PLLI2S : PLLI2S is selected as I2S clock source
 *                          @arg RCM_I2S_CLK_EXT    : EXT is selected as I2S clock source
 *
 * @retval    None
 */
void RCM_ConfigI2SCLK(RCM_I2S_CLK_T i2sClkSource)
{
    RCM->CFG_B.I2SSEL = i2sClkSource;
}

/*!
 * @brief    Enables AHB1 peripheral clock
 *
 * @param    AHB1Periph : Enable the specifies clock of AHB peripheral
 *                       This parameter can be any combination of the following values:
 *                       @arg RCM_AHB1_PERIPH_GPIOA       : Enable GPIOA clock
 *                       @arg RCM_AHB1_PERIPH_GPIOB       : Enable GPIOB clock
 *                       @arg RCM_AHB1_PERIPH_GPIOC       : Enable GPIOC clock
 *                       @arg RCM_AHB1_PERIPH_GPIOD       : Enable GPIOD clock
 *                       @arg RCM_AHB1_PERIPH_GPIOE       : Enable GPIOE clock
 *                       @arg RCM_AHB1_PERIPH_GPIOF       : Enable GPIOF clock
 *                       @arg RCM_AHB1_PERIPH_GPIOG       : Enable GPIOG clock
 *                       @arg RCM_AHB1_PERIPH_GPIOI       : Enable GPIOI clock
 *                       @arg RCM_AHB1_PERIPH_CRC         : Enable CRC clock
 *                       @arg RCM_AHB1_PERIPH_BKPSRAM     : Enable BKPSRAM interface clock
 *                       @arg RCM_AHB1_PERIPH_CCMDATARAMEN: Enable CCM data RAM interface clock
 *                       @arg RCM_AHB1_PERIPH_DMA1        : Enable DMA1 clock
 *                       @arg RCM_AHB1_PERIPH_DMA2        : Enable DMA2 clock
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC     : Enable Ethernet MAC clock
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC_Tx  : Enable Ethernet Transmission clock
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC_Rx  : Enable Ethernet Reception clock
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC_PTP : Enable Ethernet PTP clock
 *                       @arg RCM_AHB1_PERIPH_OTG_HS      : Enable USB OTG HS clock
 *                       @arg RCM_AHB1_PERIPH_OTG_HS_ULPI : Enable USB OTG HS ULPI clock
 *
 * @retval    None
 */
void RCM_EnableAHB1PeriphClock(uint32_t AHB1Periph)
{
    RCM->AHB1CLKEN |= AHB1Periph;
}

/*!
 * @brief    Disable AHB1 peripheral clock
 *
 * @param    AHB1Periph : Disable the specifies clock of AHB1 peripheral
 *                       This parameter can be any combination of the following values:
 *                       @arg RCM_AHB1_PERIPH_GPIOA       : Disable GPIOA clock
 *                       @arg RCM_AHB1_PERIPH_GPIOB       : Disable GPIOB clock
 *                       @arg RCM_AHB1_PERIPH_GPIOC       : Disable GPIOC clock
 *                       @arg RCM_AHB1_PERIPH_GPIOD       : Disable GPIOD clock
 *                       @arg RCM_AHB1_PERIPH_GPIOE       : Disable GPIOE clock
 *                       @arg RCM_AHB1_PERIPH_GPIOF       : Disable GPIOF clock
 *                       @arg RCM_AHB1_PERIPH_GPIOG       : Disable GPIOG clock
 *                       @arg RCM_AHB1_PERIPH_GPIOI       : Disable GPIOI clock
 *                       @arg RCM_AHB1_PERIPH_CRC         : Disable CRC clock
 *                       @arg RCM_AHB1_PERIPH_BKPSRAM     : Disable BKPSRAM interface clock
 *                       @arg RCM_AHB1_PERIPH_CCMDATARAMEN: Disable CCM data RAM interface clock
 *                       @arg RCM_AHB1_PERIPH_DMA1        : Disable DMA1 clock
 *                       @arg RCM_AHB1_PERIPH_DMA2        : Disable DMA2 clock
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC     : Disable Ethernet MAC clock
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC_Tx  : Disable Ethernet Transmission clock
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC_Rx  : Disable Ethernet Reception clock
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC_PTP : Disable Ethernet PTP clock
 *                       @arg RCM_AHB1_PERIPH_OTG_HS      : Disable USB OTG HS clock
 *                       @arg RCM_AHB1_PERIPH_OTG_HS_ULPI : Disable USB OTG HS ULPI clock
 *
 * @retval    None
 */
void RCM_DisableAHB1PeriphClock(uint32_t AHB1Periph)
{
    RCM->AHB1CLKEN &= (uint32_t)~AHB1Periph;
}

/*!
 * @brief    Enables AHB2 peripheral clock
 *
 * @param    AHB2Periph : Enable the specifies clock of AHB2 peripheral
 *                       This parameter can be any combination of the following values:
 *                       @arg RCM_AHB2_PERIPH_DCI       : Enable DCI clock
 *                       @arg RCM_AHB2_PERIPH_FPU       : Enable FPU clock
 *                       @arg RCM_AHB2_PERIPH_BN        : Enable BN clock
 *                       @arg RCM_AHB2_PERIPH_SM        : Enable SM clock
 *                       @arg RCM_AHB2_PERIPH_CRYP      : Enable CRYP clock
 *                       @arg RCM_AHB2_PERIPH_HASH      : Enable HASH clock
 *                       @arg RCM_AHB2_PERIPH_RNG       : Enable RNG clock
 *                       @arg RCM_AHB2_PERIPH_OTG_FS    : Enable OTG FS clock
 *
 * @retval    None
 */
void RCM_EnableAHB2PeriphClock(uint32_t AHB2Periph)
{
    RCM->AHB2CLKEN |= AHB2Periph;
}

/*!
 * @brief    Disable AHB2 peripheral clock
 *
 * @param    AHB2Periph : Disable the specifies clock of AHB2 peripheral
 *                       This parameter can be any combination of the following values:
 *                       @arg RCM_AHB2_PERIPH_DCI       : Disable DCI clock
 *                       @arg RCM_AHB2_PERIPH_FPU       : Disable FPU clock
 *                       @arg RCM_AHB2_PERIPH_BN        : Disable BN clock
 *                       @arg RCM_AHB2_PERIPH_SM        : Disable SM clock
 *                       @arg RCM_AHB2_PERIPH_CRYP      : Disable CRYP clock
 *                       @arg RCM_AHB2_PERIPH_HASH      : Disable HASH clock
 *                       @arg RCM_AHB2_PERIPH_RNG       : Disable RNG clock
 *                       @arg RCM_AHB2_PERIPH_OTG_FS    : Disable OTG FS clock
 *
 * @retval    None
 */
void RCM_DisableAHB2PeriphClock(uint32_t AHB2Periph)
{
    RCM->AHB2CLKEN &= (uint32_t)~AHB2Periph;
}

/*!
 * @brief    Enable the Low Speed APB (APB1) peripheral clock
 *
 * @param    APB1Periph : Enable specifies clock of the APB1 peripheral.
 *                        This parameter can be any combination of the following values:
 *                        @arg RCM_APB1_PERIPH_TMR2   : Enable TMR2 clock
 *                        @arg RCM_APB1_PERIPH_TMR3   : Enable TMR3 clock
 *                        @arg RCM_APB1_PERIPH_TMR4   : Enable TMR4 clock
 *                        @arg RCM_APB1_PERIPH_TMR5   : Enable TMR5 clock
 *                        @arg RCM_APB1_PERIPH_TMR6   : Enable TMR6 clock
 *                        @arg RCM_APB1_PERIPH_TMR7   : Enable TMR7 clock
 *                        @arg RCM_APB1_PERIPH_TMR12  : Enable TMR12 clock
 *                        @arg RCM_APB1_PERIPH_TMR13  : Enable TMR13 clock
 *                        @arg RCM_APB1_PERIPH_TMR14  : Enable TMR14 clock
 *                        @arg RCM_APB1_PERIPH_WWDT   : Enable WWDT clock
 *                        @arg RCM_APB1_PERIPH_SPI2   : Enable SPI2 clock
 *                        @arg RCM_APB1_PERIPH_SPI3   : Enable SPI3 clock
 *                        @arg RCM_APB1_PERIPH_USART2 : Enable USART2 clock
 *                        @arg RCM_APB1_PERIPH_USART3 : Enable USART3 clock
 *                        @arg RCM_APB1_PERIPH_UART4  : Enable UART4 clock
 *                        @arg RCM_APB1_PERIPH_UART5  : Enable UART5 clock
 *                        @arg RCM_APB1_PERIPH_I2C1   : Enable I2C1 clock
 *                        @arg RCM_APB1_PERIPH_I2C2   : Enable I2C2 clock
 *                        @arg RCM_APB1_PERIPH_I2C3   : Enable I2C3 clock
 *                        @arg RCM_APB1_PERIPH_FMPI2C1: Enable FMPI2C1 clock
 *                        @arg RCM_APB1_PERIPH_CAN1   : Enable CAN1 clock
 *                        @arg RCM_APB1_PERIPH_CAN2   : Enable CAN2 clock
 *                        @arg RCM_APB1_PERIPH_PMU    : Enable PMU clock
 *                        @arg RCM_APB1_PERIPH_DAC    : Enable DAC clock
 *                        @arg RCM_APB1_PERIPH_UART7  : Enable UART7 clock
 *                        @arg RCM_APB1_PERIPH_UART8  : Enable UART8 clock
 *
 * @retval   None
 */
void RCM_EnableAPB1PeriphClock(uint32_t APB1Periph)
{
    RCM->APB1CLKEN |= APB1Periph;
}

/*!
 * @brief    Disable the Low Speed APB (APB1) peripheral clock
 *
 * @param    APB1Periph : Disable specifies clock of the APB1 peripheral.
 *                        This parameter can be any combination of the following values:
 *                        @arg RCM_APB1_PERIPH_TMR2   : Disable TMR2 clock
 *                        @arg RCM_APB1_PERIPH_TMR3   : Disable TMR3 clock
 *                        @arg RCM_APB1_PERIPH_TMR4   : Disable TMR4 clock
 *                        @arg RCM_APB1_PERIPH_TMR5   : Disable TMR5 clock
 *                        @arg RCM_APB1_PERIPH_TMR6   : Disable TMR6 clock
 *                        @arg RCM_APB1_PERIPH_TMR7   : Disable TMR7 clock
 *                        @arg RCM_APB1_PERIPH_TMR12  : Disable TMR12 clock
 *                        @arg RCM_APB1_PERIPH_TMR13  : Disable TMR13 clock
 *                        @arg RCM_APB1_PERIPH_TMR14  : Disable TMR14 clock
 *                        @arg RCM_APB1_PERIPH_WWDT   : Disable WWDT clock
 *                        @arg RCM_APB1_PERIPH_SPI2   : Disable SPI2 clock
 *                        @arg RCM_APB1_PERIPH_SPI3   : Disable SPI3 clock
 *                        @arg RCM_APB1_PERIPH_USART2 : Disable USART2 clock
 *                        @arg RCM_APB1_PERIPH_USART3 : Disable USART3 clock
 *                        @arg RCM_APB1_PERIPH_UART4  : Disable UART4 clock
 *                        @arg RCM_APB1_PERIPH_UART5  : Disable UART5 clock
 *                        @arg RCM_APB1_PERIPH_I2C1   : Disable I2C1 clock
 *                        @arg RCM_APB1_PERIPH_I2C2   : Disable I2C2 clock
 *                        @arg RCM_APB1_PERIPH_I2C3   : Disable I2C3 clock
 *                        @arg RCM_APB1_PERIPH_FMPI2C1: Disable FMPI2C1 clock
 *                        @arg RCM_APB1_PERIPH_CAN1   : Disable CAN1 clock
 *                        @arg RCM_APB1_PERIPH_CAN2   : Disable CAN2 clock
 *                        @arg RCM_APB1_PERIPH_PMU    : Disable PMU clock
 *                        @arg RCM_APB1_PERIPH_DAC    : Disable DAC clock
 *                        @arg RCM_APB1_PERIPH_UART7  : Disable UART7 clock
 *                        @arg RCM_APB1_PERIPH_UART8  : Disable UART8 clock
 *
 * @retval   None
 */
void RCM_DisableAPB1PeriphClock(uint32_t APB1Periph)
{
    RCM->APB1CLKEN &= (uint32_t)~APB1Periph;
}

/*!
 * @brief    Enable the High Speed APB (APB2) peripheral clock
 *
 * @param    APB2Periph : Enable specifies clock of the APB2 peripheral.
 *                        This parameter can be any combination of the following values:
 *                        @arg RCM_APB2_PERIPH_TMR1   : TMR1 clock
 *                        @arg RCM_APB2_PERIPH_TMR8   : TMR8 clock
 *                        @arg RCM_APB2_PERIPH_USART1 : USART1 clock
 *                        @arg RCM_APB2_PERIPH_USART6 : USART6 clock
 *                        @arg RCM_APB2_PERIPH_ADC1   : ADC1 clock
 *                        @arg RCM_APB2_PERIPH_ADC2   : ADC2 clock
 *                        @arg RCM_APB2_PERIPH_ADC3   : ADC3 clock
 *                        @arg RCM_APB2_PERIPH_SDIO   : SDIO clock
 *                        @arg RCM_APB2_PERIPH_SPI1   : SPI1 clock
 *                        @arg RCM_APB2_PERIPH_SPI4   : SPI4 clock
 *                        @arg RCM_APB2_PERIPH_SYSCFG : SYSCFG clock
 *                        @arg RCM_APB2_PERIPH_TMR9   : TMR9 clock
 *                        @arg RCM_APB2_PERIPH_TMR10  : TMR10 clock
 *                        @arg RCM_APB2_PERIPH_TMR11  : TMR11 clock
 *                        @arg RCM_APB2_PERIPH_SPI5   : SPI5 clock
 *                        @arg RCM_APB2_PERIPH_SPI6   : SPI6 clock
 *
 * @retval   None
 */
void RCM_EnableAPB2PeriphClock(uint32_t APB2Periph)
{
    RCM->APB2CLKEN |= APB2Periph;
}

/*!
 * @brief    Disable the High Speed APB (APB2) peripheral clock
 *
 * @param    APB2Periph : Disable specifies clock of the APB2 peripheral.
 *                        This parameter can be any combination of the following values:
 *                        @arg RCM_APB2_PERIPH_TMR1   : TMR1 clock
 *                        @arg RCM_APB2_PERIPH_TMR8   : TMR8 clock
 *                        @arg RCM_APB2_PERIPH_USART1 : USART1 clock
 *                        @arg RCM_APB2_PERIPH_USART6 : USART6 clock
 *                        @arg RCM_APB2_PERIPH_ADC1   : ADC1 clock
 *                        @arg RCM_APB2_PERIPH_ADC2   : ADC2 clock
 *                        @arg RCM_APB2_PERIPH_ADC3   : ADC3 clock
 *                        @arg RCM_APB2_PERIPH_SDIO   : SDIO clock
 *                        @arg RCM_APB2_PERIPH_SPI1   : SPI1 clock
 *                        @arg RCM_APB2_PERIPH_SPI4   : SPI4 clock
 *                        @arg RCM_APB2_PERIPH_SYSCFG : SYSCFG clock
 *                        @arg RCM_APB2_PERIPH_TMR9   : TMR9 clock
 *                        @arg RCM_APB2_PERIPH_TMR10  : TMR10 clock
 *                        @arg RCM_APB2_PERIPH_TMR11  : TMR11 clock
 *                        @arg RCM_APB2_PERIPH_SPI5   : SPI5 clock
 *                        @arg RCM_APB2_PERIPH_SPI6   : SPI6 clock
 *
 * @retval   None
 */
void RCM_DisableAPB2PeriphClock(uint32_t APB2Periph)
{
    RCM->APB2CLKEN &= (uint32_t)~APB2Periph;
}

/*!
 * @brief    Enables AHB1 peripheral reset
 *
 * @param    AHB1Periph : Enable the specifies reset of AHB peripheral
 *                       This parameter can be any combination of the following values:
 *                       @arg RCM_AHB1_PERIPH_GPIOA       : Enable GPIOA reset
 *                       @arg RCM_AHB1_PERIPH_GPIOB       : Enable GPIOB reset
 *                       @arg RCM_AHB1_PERIPH_GPIOC       : Enable GPIOC reset
 *                       @arg RCM_AHB1_PERIPH_GPIOD       : Enable GPIOD reset
 *                       @arg RCM_AHB1_PERIPH_GPIOE       : Enable GPIOE reset
 *                       @arg RCM_AHB1_PERIPH_GPIOF       : Enable GPIOF reset
 *                       @arg RCM_AHB1_PERIPH_GPIOG       : Enable GPIOG reset
 *                       @arg RCM_AHB1_PERIPH_GPIOI       : Enable GPIOI reset
 *                       @arg RCM_AHB1_PERIPH_CRC         : Enable CRC reset
 *                       @arg RCM_AHB1_PERIPH_BKPSRAM     : Enable BKPSRAM interface reset
 *                       @arg RCM_AHB1_PERIPH_CCMDATARAMEN: Enable CCM data RAM interface reset
 *                       @arg RCM_AHB1_PERIPH_DMA1        : Enable DMA1 reset
 *                       @arg RCM_AHB1_PERIPH_DMA2        : Enable DMA2 reset
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC     : Enable Ethernet MAC reset
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC_Tx  : Enable Ethernet Transmission reset
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC_Rx  : Enable Ethernet Reception reset
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC_PTP : Enable Ethernet PTP reset
 *                       @arg RCM_AHB1_PERIPH_OTG_HS      : Enable USB OTG HS reset
 *                       @arg RCM_AHB1_PERIPH_OTG_HS_ULPI : Enable USB OTG HS ULPI clock
 *
 * @retval    None
 */
void RCM_EnableAHB1PeriphReset(uint32_t AHB1Periph)
{
    RCM->AHB1RST |= AHB1Periph;
}

/*!
 * @brief    Disable AHB1 peripheral reset
 *
 * @param    AHB1Periph : Disable the specifies reset of AHB1 peripheral
 *                       This parameter can be any combination of the following values:
 *                       @arg RCM_AHB1_PERIPH_GPIOA       : Disable GPIOA reset
 *                       @arg RCM_AHB1_PERIPH_GPIOB       : Disable GPIOB reset
 *                       @arg RCM_AHB1_PERIPH_GPIOC       : Disable GPIOC reset
 *                       @arg RCM_AHB1_PERIPH_GPIOD       : Disable GPIOD reset
 *                       @arg RCM_AHB1_PERIPH_GPIOE       : Disable GPIOE reset
 *                       @arg RCM_AHB1_PERIPH_GPIOF       : Disable GPIOF reset
 *                       @arg RCM_AHB1_PERIPH_GPIOG       : Disable GPIOG reset
 *                       @arg RCM_AHB1_PERIPH_GPIOI       : Disable GPIOI reset
 *                       @arg RCM_AHB1_PERIPH_CRC         : Disable CRC reset
 *                       @arg RCM_AHB1_PERIPH_BKPSRAM     : Disable BKPSRAM interface reset
 *                       @arg RCM_AHB1_PERIPH_CCMDATARAMEN: Disable CCM data RAM interface reset
 *                       @arg RCM_AHB1_PERIPH_DMA1        : Disable DMA1 reset
 *                       @arg RCM_AHB1_PERIPH_DMA2        : Disable DMA2 reset
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC     : Disable Ethernet MAC reset
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC_Tx  : Disable Ethernet Transmission reset
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC_Rx  : Disable Ethernet Reception reset
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC_PTP : Disable Ethernet PTP reset
 *                       @arg RCM_AHB1_PERIPH_OTG_HS      : Disable USB OTG HS reset
 *                       @arg RCM_AHB1_PERIPH_OTG_HS_ULPI : Disable USB OTG HS ULPI reset
 *
 * @retval    None
 */
void RCM_DisableAHB1PeriphReset(uint32_t AHB1Periph)
{
    RCM->AHB1RST &= (uint32_t)~AHB1Periph;
}

/*!
 * @brief    Enables AHB2 peripheral reset
 *
 * @param    AHB2Periph : Enable the specifies reset of AHB2 peripheral
 *                       This parameter can be any combination of the following values:
 *                       @arg RCM_AHB2_PERIPH_DCI       : Enable DCI reset
 *                       @arg RCM_AHB2_PERIPH_FPU       : Enable FPU reset
 *                       @arg RCM_AHB2_PERIPH_BN        : Enable BN reset
 *                       @arg RCM_AHB2_PERIPH_SM        : Enable SM reset
 *                       @arg RCM_AHB2_PERIPH_CRYP      : Enable CRYP reset
 *                       @arg RCM_AHB2_PERIPH_HASH      : Enable HASH reset
 *                       @arg RCM_AHB2_PERIPH_RNG       : Enable RNG reset
 *                       @arg RCM_AHB2_PERIPH_OTG_FS    : Enable OTG FS reset
 *
 * @retval    None
 */
void RCM_EnableAHB2PeriphReset(uint32_t AHB2Periph)
{
    RCM->AHB2RST |= AHB2Periph;
}

/*!
 * @brief    Disable AHB2 peripheral reset
 *
 * @param    AHB2Periph : Disable the specifies reset of AHB2 peripheral
 *                       This parameter can be any combination of the following values:
 *                       @arg RCM_AHB2_PERIPH_DCI       : Disable DCI reset
 *                       @arg RCM_AHB2_PERIPH_FPU       : Disable FPU reset
 *                       @arg RCM_AHB2_PERIPH_BN        : Disable BN reset
 *                       @arg RCM_AHB2_PERIPH_SM        : Disable SM reset
 *                       @arg RCM_AHB2_PERIPH_CRYP      : Disable CRYP reset
 *                       @arg RCM_AHB2_PERIPH_HASH      : Disable HASH reset
 *                       @arg RCM_AHB2_PERIPH_RNG       : Disable RNG reset
 *                       @arg RCM_AHB2_PERIPH_OTG_FS    : Disable OTG FS reset
 *
 * @retval    None
 */
void RCM_DisableAHB2PeriphReset(uint32_t AHB2Periph)
{
    RCM->AHB2RST &= (uint32_t)~AHB2Periph;
}

/*!
 * @brief    Enable the Low Speed APB (APB1) peripheral reset
 *
 * @param    APB1Periph : Enable specifies reset of the APB1 peripheral.
 *                        This parameter can be any combination of the following values:
 *                        @arg RCM_APB1_PERIPH_TMR2   : Enable TMR2 reset
 *                        @arg RCM_APB1_PERIPH_TMR3   : Enable TMR3 reset
 *                        @arg RCM_APB1_PERIPH_TMR4   : Enable TMR4 reset
 *                        @arg RCM_APB1_PERIPH_TMR5   : Enable TMR5 reset
 *                        @arg RCM_APB1_PERIPH_TMR6   : Enable TMR6 reset
 *                        @arg RCM_APB1_PERIPH_TMR7   : Enable TMR7 reset
 *                        @arg RCM_APB1_PERIPH_TMR12  : Enable TMR12 reset
 *                        @arg RCM_APB1_PERIPH_TMR13  : Enable TMR13 reset
 *                        @arg RCM_APB1_PERIPH_TMR14  : Enable TMR14 reset
 *                        @arg RCM_APB1_PERIPH_WWDT   : Enable WWDT reset
 *                        @arg RCM_APB1_PERIPH_SPI2   : Enable SPI2 reset
 *                        @arg RCM_APB1_PERIPH_SPI3   : Enable SPI3 reset
 *                        @arg RCM_APB1_PERIPH_USART2 : Enable USART2 reset
 *                        @arg RCM_APB1_PERIPH_USART3 : Enable USART3 reset
 *                        @arg RCM_APB1_PERIPH_UART4  : Enable UART4 reset
 *                        @arg RCM_APB1_PERIPH_UART5  : Enable UART5 reset
 *                        @arg RCM_APB1_PERIPH_I2C1   : Enable I2C1 reset
 *                        @arg RCM_APB1_PERIPH_I2C2   : Enable I2C2 reset
 *                        @arg RCM_APB1_PERIPH_I2C3   : Enable I2C3 reset
 *                        @arg RCM_APB1_PERIPH_FMPI2C1: Enable FMPI2C1 reset
 *                        @arg RCM_APB1_PERIPH_CAN1   : Enable CAN1 reset
 *                        @arg RCM_APB1_PERIPH_CAN2   : Enable CAN2 reset
 *                        @arg RCM_APB1_PERIPH_PMU    : Enable PMU reset
 *                        @arg RCM_APB1_PERIPH_DAC    : Enable DAC reset
 *                        @arg RCM_APB1_PERIPH_UART7  : Enable UART7 reset
 *                        @arg RCM_APB1_PERIPH_UART8  : Enable UART8 reset
 *
 * @retval   None
 */
void RCM_EnableAPB1PeriphReset(uint32_t APB1Periph)
{
    RCM->APB1RST |= APB1Periph;
}

/*!
 * @brief    Disable the Low Speed APB (APB1) peripheral reset
 *
 * @param    APB1Periph : Disable specifies reset of the APB1 peripheral.
 *                        This parameter can be any combination of the following values:
 *                        @arg RCM_APB1_PERIPH_TMR2   : Disable TMR2 reset
 *                        @arg RCM_APB1_PERIPH_TMR3   : Disable TMR3 reset
 *                        @arg RCM_APB1_PERIPH_TMR4   : Disable TMR4 reset
 *                        @arg RCM_APB1_PERIPH_TMR5   : Disable TMR5 reset
 *                        @arg RCM_APB1_PERIPH_TMR6   : Disable TMR6 reset
 *                        @arg RCM_APB1_PERIPH_TMR7   : Disable TMR7 reset
 *                        @arg RCM_APB1_PERIPH_TMR12  : Disable TMR12 reset
 *                        @arg RCM_APB1_PERIPH_TMR13  : Disable TMR13 reset
 *                        @arg RCM_APB1_PERIPH_TMR14  : Disable TMR14 reset
 *                        @arg RCM_APB1_PERIPH_WWDT   : Disable WWDT reset
 *                        @arg RCM_APB1_PERIPH_SPI2   : Disable SPI2 reset
 *                        @arg RCM_APB1_PERIPH_SPI3   : Disable SPI3 reset
 *                        @arg RCM_APB1_PERIPH_USART2 : Disable USART2 reset
 *                        @arg RCM_APB1_PERIPH_USART3 : Disable USART3 reset
 *                        @arg RCM_APB1_PERIPH_UART4  : Disable UART4 reset
 *                        @arg RCM_APB1_PERIPH_UART5  : Disable UART5 reset
 *                        @arg RCM_APB1_PERIPH_I2C1   : Disable I2C1 reset
 *                        @arg RCM_APB1_PERIPH_I2C2   : Disable I2C2 reset
 *                        @arg RCM_APB1_PERIPH_I2C3   : Disable I2C3 reset
 *                        @arg RCM_APB1_PERIPH_FMPI2C1: Disable FMPI2C1 reset
 *                        @arg RCM_APB1_PERIPH_CAN1   : Disable CAN1 reset
 *                        @arg RCM_APB1_PERIPH_CAN2   : Disable CAN2 reset
 *                        @arg RCM_APB1_PERIPH_PMU    : Disable PMU reset
 *                        @arg RCM_APB1_PERIPH_DAC    : Disable DAC reset
 *                        @arg RCM_APB1_PERIPH_UART7  : Disable UART7 reset
 *                        @arg RCM_APB1_PERIPH_UART8  : Disable UART8 reset
 *
 * @retval   None
 */
void RCM_DisableAPB1PeriphReset(uint32_t APB1Periph)
{
    RCM->APB1RST &= (uint32_t)~APB1Periph;
}

/*!
 * @brief    Enable the High Speed APB (APB2) peripheral reset
 *
 * @param    APB2Periph : Enable specifies reset of the APB2 peripheral.
 *                        This parameter can be any combination of the following values:
 *                        @arg RCM_APB2_PERIPH_TMR1   : TMR1 reset
 *                        @arg RCM_APB2_PERIPH_TMR8   : TMR8 reset
 *                        @arg RCM_APB2_PERIPH_USART1 : USART1 reset
 *                        @arg RCM_APB2_PERIPH_USART6 : USART6 reset
 *                        @arg RCM_APB2_PERIPH_ADC    : All of ADC reset
 *                        @arg RCM_APB2_PERIPH_SDIO   : SDIO reset
 *                        @arg RCM_APB2_PERIPH_SPI1   : SPI1 reset
 *                        @arg RCM_APB2_PERIPH_SPI4   : SPI4 reset
 *                        @arg RCM_APB2_PERIPH_SYSCFG : SYSCFG reset
 *                        @arg RCM_APB2_PERIPH_TMR9   : TMR9 reset
 *                        @arg RCM_APB2_PERIPH_TMR10  : TMR10 reset
 *                        @arg RCM_APB2_PERIPH_TMR11  : TMR11 reset
 *                        @arg RCM_APB2_PERIPH_SPI5   : SPI5 reset
 *                        @arg RCM_APB2_PERIPH_SPI6   : SPI6 reset
 *
 * @retval   None
 */
void RCM_EnableAPB2PeriphReset(uint32_t APB2Periph)
{
    RCM->APB2RST |= APB2Periph;
}

/*!
 * @brief    Disable the High Speed APB (APB2) peripheral reset
 *
 * @param    APB2Periph : Disable specifies reset of the APB2 peripheral.
 *                        This parameter can be any combination of the following values:
 *                        @arg RCM_APB2_PERIPH_TMR1   : TMR1 reset
 *                        @arg RCM_APB2_PERIPH_TMR8   : TMR8 reset
 *                        @arg RCM_APB2_PERIPH_USART1 : USART1 reset
 *                        @arg RCM_APB2_PERIPH_USART6 : USART6 reset
 *                        @arg RCM_APB2_PERIPH_ADC1   : ADC1 reset
 *                        @arg RCM_APB2_PERIPH_ADC2   : ADC2 reset
 *                        @arg RCM_APB2_PERIPH_ADC3   : ADC3 reset
 *                        @arg RCM_APB2_PERIPH_SDIO   : SDIO reset
 *                        @arg RCM_APB2_PERIPH_SPI1   : SPI1 reset
 *                        @arg RCM_APB2_PERIPH_SPI4   : SPI4 reset
 *                        @arg RCM_APB2_PERIPH_SYSCFG : SYSCFG reset
 *                        @arg RCM_APB2_PERIPH_TMR9   : TMR9 reset
 *                        @arg RCM_APB2_PERIPH_TMR10  : TMR10 reset
 *                        @arg RCM_APB2_PERIPH_TMR11  : TMR11 reset
 *                        @arg RCM_APB2_PERIPH_SPI5   : SPI5 reset
 *                        @arg RCM_APB2_PERIPH_SPI6   : SPI6 reset
 *
 * @retval   None
 */
void RCM_DisableAPB2PeriphReset(uint32_t APB2Periph)
{
    RCM->APB2RST &= (uint32_t)~APB2Periph;
}

/*!
 * @brief    Enables AHB1 peripheral clock during Low Power (Sleep) mode
 *
 * @param    AHB1Periph : Enable the specifies clock of AHB peripheral
 *                       This parameter can be any combination of the following values:
 *                       @arg RCM_AHB1_PERIPH_GPIOA       : Enable GPIOA clock
 *                       @arg RCM_AHB1_PERIPH_GPIOB       : Enable GPIOB clock
 *                       @arg RCM_AHB1_PERIPH_GPIOC       : Enable GPIOC clock
 *                       @arg RCM_AHB1_PERIPH_GPIOD       : Enable GPIOD clock
 *                       @arg RCM_AHB1_PERIPH_GPIOE       : Enable GPIOE clock
 *                       @arg RCM_AHB1_PERIPH_GPIOF       : Enable GPIOF clock
 *                       @arg RCM_AHB1_PERIPH_GPIOG       : Enable GPIOG clock
 *                       @arg RCM_AHB1_PERIPH_GPIOI       : Enable GPIOI clock
 *                       @arg RCM_AHB1_PERIPH_CRC         : Enable CRC clock
 *                       @arg RCM_AHB1_PERIPH_BKPSRAM     : Enable BKPSRAM interface clock
 *                       @arg RCM_AHB1_PERIPH_CCMDATARAMEN: Enable CCM data RAM interface clock
 *                       @arg RCM_AHB1_PERIPH_DMA1        : Enable DMA1 clock
 *                       @arg RCM_AHB1_PERIPH_DMA2        : Enable DMA2 clock
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC     : Enable Ethernet MAC clock
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC_Tx  : Enable Ethernet Transmission clock
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC_Rx  : Enable Ethernet Reception clock
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC_PTP : Enable Ethernet PTP clock
 *                       @arg RCM_AHB1_PERIPH_OTG_HS      : Enable USB OTG HS clock
 *                       @arg RCM_AHB1_PERIPH_OTG_HS_ULPI : Enable USB OTG HS ULPI clock
 *
 * @retval    None
 */
void RCM_EnableAHB1PeriphClockLPMode(uint32_t AHB1Periph)
{
    RCM->LPAHB1CLKEN |= AHB1Periph;
}

/*!
 * @brief    Disable AHB1 peripheral clock during Low Power (Sleep) mode
 *
 * @param    AHB1Periph : Disable the specifies clock of AHB1 peripheral
 *                       This parameter can be any combination of the following values:
 *                       @arg RCM_AHB1_PERIPH_GPIOA       : Disable GPIOA clock
 *                       @arg RCM_AHB1_PERIPH_GPIOB       : Disable GPIOB clock
 *                       @arg RCM_AHB1_PERIPH_GPIOC       : Disable GPIOC clock
 *                       @arg RCM_AHB1_PERIPH_GPIOD       : Disable GPIOD clock
 *                       @arg RCM_AHB1_PERIPH_GPIOE       : Disable GPIOE clock
 *                       @arg RCM_AHB1_PERIPH_GPIOF       : Disable GPIOF clock
 *                       @arg RCM_AHB1_PERIPH_GPIOG       : Disable GPIOG clock
 *                       @arg RCM_AHB1_PERIPH_GPIOI       : Disable GPIOI clock
 *                       @arg RCM_AHB1_PERIPH_CRC         : Disable CRC clock
 *                       @arg RCM_AHB1_PERIPH_BKPSRAM     : Disable BKPSRAM interface clock
 *                       @arg RCM_AHB1_PERIPH_CCMDATARAMEN: Disable CCM data RAM interface clock
 *                       @arg RCM_AHB1_PERIPH_DMA1        : Disable DMA1 clock
 *                       @arg RCM_AHB1_PERIPH_DMA2        : Disable DMA2 clock
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC     : Disable Ethernet MAC clock
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC_Tx  : Disable Ethernet Transmission clock
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC_Rx  : Disable Ethernet Reception clock
 *                       @arg RCM_AHB1_PERIPH_ETH_MAC_PTP : Disable Ethernet PTP clock
 *                       @arg RCM_AHB1_PERIPH_OTG_HS      : Disable USB OTG HS clock
 *                       @arg RCM_AHB1_PERIPH_OTG_HS_ULPI : Disable USB OTG HS ULPI clock
 *
 * @retval    None
 */
void RCM_DisableAHB1PeriphClockLPMode(uint32_t AHB1Periph)
{
    RCM->LPAHB1CLKEN &= (uint32_t)~AHB1Periph;
}

/*!
 * @brief    Enables AHB2 peripheral clock during Low Power (Sleep) mode
 *
 * @param    AHB2Periph : Enable the specifies clock of AHB2 peripheral
 *                       This parameter can be any combination of the following values:
 *                       @arg RCM_AHB2_PERIPH_DCI       : Enable DCI clock
 *                       @arg RCM_AHB2_PERIPH_FPU       : Enable FPU clock
 *                       @arg RCM_AHB2_PERIPH_BN        : Enable BN clock
 *                       @arg RCM_AHB2_PERIPH_SM        : Enable SM clock
 *                       @arg RCM_AHB2_PERIPH_CRYP      : Enable CRYP clock
 *                       @arg RCM_AHB2_PERIPH_HASH      : Enable HASH clock
 *                       @arg RCM_AHB2_PERIPH_RNG       : Enable RNG clock
 *                       @arg RCM_AHB2_PERIPH_OTG_FS    : Enable OTG FS clock
 *
 * @retval    None
 */
void RCM_EnableAHB2PeriphClockLPMode(uint32_t AHB2Periph)
{
    RCM->LPAHB2CLKEN |= AHB2Periph;
}

/*!
 * @brief    Disable AHB2 peripheral clock during Low Power (Sleep) mode
 *
 * @param    AHB2Periph : Disable the specifies clock of AHB2 peripheral
 *                       This parameter can be any combination of the following values:
 *                       @arg RCM_AHB2_PERIPH_DCI       : Disable DCI clock
 *                       @arg RCM_AHB2_PERIPH_FPU       : Disable FPU clock
 *                       @arg RCM_AHB2_PERIPH_BN        : Disable BN clock
 *                       @arg RCM_AHB2_PERIPH_SM        : Disable SM clock
 *                       @arg RCM_AHB2_PERIPH_CRYP      : Disable CRYP clock
 *                       @arg RCM_AHB2_PERIPH_HASH      : Disable HASH clock
 *                       @arg RCM_AHB2_PERIPH_RNG       : Disable RNG clock
 *                       @arg RCM_AHB2_PERIPH_OTG_FS    : Disable OTG FS clock
 *
 * @retval    None
 */
void RCM_DisableAHB2PeriphClockLPMode(uint32_t AHB2Periph)
{
    RCM->LPAHB2CLKEN &= (uint32_t)~AHB2Periph;
}

/*!
 * @brief    Enable the Low Speed APB (APB1) peripheral clock during Low Power (Sleep) mode
 *
 * @param    APB1Periph : Enable specifies clock of the APB1 peripheral.
 *                        This parameter can be any combination of the following values:
 *                        @arg RCM_APB1_PERIPH_TMR2   : Enable TMR2 clock
 *                        @arg RCM_APB1_PERIPH_TMR3   : Enable TMR3 clock
 *                        @arg RCM_APB1_PERIPH_TMR4   : Enable TMR4 clock
 *                        @arg RCM_APB1_PERIPH_TMR5   : Enable TMR5 clock
 *                        @arg RCM_APB1_PERIPH_TMR6   : Enable TMR6 clock
 *                        @arg RCM_APB1_PERIPH_TMR7   : Enable TMR7 clock
 *                        @arg RCM_APB1_PERIPH_TMR12  : Enable TMR12 clock
 *                        @arg RCM_APB1_PERIPH_TMR13  : Enable TMR13 clock
 *                        @arg RCM_APB1_PERIPH_TMR14  : Enable TMR14 clock
 *                        @arg RCM_APB1_PERIPH_WWDT   : Enable WWDT clock
 *                        @arg RCM_APB1_PERIPH_SPI2   : Enable SPI2 clock
 *                        @arg RCM_APB1_PERIPH_SPI3   : Enable SPI3 clock
 *                        @arg RCM_APB1_PERIPH_USART2 : Enable USART2 clock
 *                        @arg RCM_APB1_PERIPH_USART3 : Enable USART3 clock
 *                        @arg RCM_APB1_PERIPH_UART4  : Enable UART4 clock
 *                        @arg RCM_APB1_PERIPH_UART5  : Enable UART5 clock
 *                        @arg RCM_APB1_PERIPH_I2C1   : Enable I2C1 clock
 *                        @arg RCM_APB1_PERIPH_I2C2   : Enable I2C2 clock
 *                        @arg RCM_APB1_PERIPH_I2C3   : Enable I2C3 clock
 *                        @arg RCM_APB1_PERIPH_FMPI2C1: Enable FMPI2C1 clock
 *                        @arg RCM_APB1_PERIPH_CAN1   : Enable CAN1 clock
 *                        @arg RCM_APB1_PERIPH_CAN2   : Enable CAN2 clock
 *                        @arg RCM_APB1_PERIPH_PMU    : Enable PMU clock
 *                        @arg RCM_APB1_PERIPH_DAC    : Enable DAC clock
 *                        @arg RCM_APB1_PERIPH_UART7  : Enable UART7 clock
 *                        @arg RCM_APB1_PERIPH_UART8  : Enable UART8 clock
 *
 * @retval   None
 */
void RCM_EnableAPB1PeriphClockLPMode(uint32_t APB1Periph)
{
    RCM->LPAPB1CLKEN |= APB1Periph;
}

/*!
 * @brief    Disable the Low Speed APB (APB1) peripheral clock during Low Power (Sleep) mode
 *
 * @param    APB1Periph : Disable specifies clock of the APB1 peripheral.
 *                        This parameter can be any combination of the following values:
 *                        @arg RCM_APB1_PERIPH_TMR2   : Disable TMR2 clock
 *                        @arg RCM_APB1_PERIPH_TMR3   : Disable TMR3 clock
 *                        @arg RCM_APB1_PERIPH_TMR4   : Disable TMR4 clock
 *                        @arg RCM_APB1_PERIPH_TMR5   : Disable TMR5 clock
 *                        @arg RCM_APB1_PERIPH_TMR6   : Disable TMR6 clock
 *                        @arg RCM_APB1_PERIPH_TMR7   : Disable TMR7 clock
 *                        @arg RCM_APB1_PERIPH_TMR12  : Disable TMR12 clock
 *                        @arg RCM_APB1_PERIPH_TMR13  : Disable TMR13 clock
 *                        @arg RCM_APB1_PERIPH_TMR14  : Disable TMR14 clock
 *                        @arg RCM_APB1_PERIPH_WWDT   : Disable WWDT clock
 *                        @arg RCM_APB1_PERIPH_SPI2   : Disable SPI2 clock
 *                        @arg RCM_APB1_PERIPH_SPI3   : Disable SPI3 clock
 *                        @arg RCM_APB1_PERIPH_USART2 : Disable USART2 clock
 *                        @arg RCM_APB1_PERIPH_USART3 : Disable USART3 clock
 *                        @arg RCM_APB1_PERIPH_UART4  : Disable UART4 clock
 *                        @arg RCM_APB1_PERIPH_UART5  : Disable UART5 clock
 *                        @arg RCM_APB1_PERIPH_I2C1   : Disable I2C1 clock
 *                        @arg RCM_APB1_PERIPH_I2C2   : Disable I2C2 clock
 *                        @arg RCM_APB1_PERIPH_I2C3   : Disable I2C3 clock
 *                        @arg RCM_APB1_PERIPH_FMPI2C1: Disable FMPI2C1 clock
 *                        @arg RCM_APB1_PERIPH_CAN1   : Disable CAN1 clock
 *                        @arg RCM_APB1_PERIPH_CAN2   : Disable CAN2 clock
 *                        @arg RCM_APB1_PERIPH_PMU    : Disable PMU clock
 *                        @arg RCM_APB1_PERIPH_DAC    : Disable DAC clock
 *                        @arg RCM_APB1_PERIPH_UART7  : Disable UART7 clock
 *                        @arg RCM_APB1_PERIPH_UART8  : Disable UART8 clock
 *
 * @retval   None
 */
void RCM_DisableAPB1PeriphClockLPMode(uint32_t APB1Periph)
{
    RCM->LPAPB1CLKEN &= (uint32_t)~APB1Periph;
}

/*!
 * @brief    Enable the High Speed APB (APB2) peripheral clock during Low Power (Sleep) mode
 *
 * @param    APB2Periph : Enable specifies clock of the APB2 peripheral.
 *                        This parameter can be any combination of the following values:
 *                        @arg RCM_APB2_PERIPH_TMR1   : TMR1 clock
 *                        @arg RCM_APB2_PERIPH_TMR8   : TMR8 clock
 *                        @arg RCM_APB2_PERIPH_USART1 : USART1 clock
 *                        @arg RCM_APB2_PERIPH_USART6 : USART6 clock
 *                        @arg RCM_APB2_PERIPH_ADC1   : ADC1 clock
 *                        @arg RCM_APB2_PERIPH_ADC2   : ADC2 clock
 *                        @arg RCM_APB2_PERIPH_ADC3   : ADC3 clock
 *                        @arg RCM_APB2_PERIPH_SDIO   : SDIO clock
 *                        @arg RCM_APB2_PERIPH_SPI1   : SPI1 clock
 *                        @arg RCM_APB2_PERIPH_SPI4   : SPI4 clock
 *                        @arg RCM_APB2_PERIPH_SYSCFG : SYSCFG clock
 *                        @arg RCM_APB2_PERIPH_TMR9   : TMR9 clock
 *                        @arg RCM_APB2_PERIPH_TMR10  : TMR10 clock
 *                        @arg RCM_APB2_PERIPH_TMR11  : TMR11 clock
 *                        @arg RCM_APB2_PERIPH_SPI5   : SPI5 clock
 *                        @arg RCM_APB2_PERIPH_SPI6   : SPI6 clock
 *
 * @retval   None
 */
void RCM_EnableAPB2PeriphClockLPMode(uint32_t APB2Periph)
{
    RCM->LPAPB2CLKEN |= APB2Periph;
}

/*!
 * @brief    Disable the High Speed APB (APB2) peripheral clock during Low Power (Sleep) mode
 *
 * @param    APB2Periph : Disable specifies clock of the APB2 peripheral.
 *                        This parameter can be any combination of the following values:
 *                        @arg RCM_APB2_PERIPH_TMR1   : TMR1 clock
 *                        @arg RCM_APB2_PERIPH_TMR8   : TMR8 clock
 *                        @arg RCM_APB2_PERIPH_USART1 : USART1 clock
 *                        @arg RCM_APB2_PERIPH_USART6 : USART6 clock
 *                        @arg RCM_APB2_PERIPH_ADC1   : ADC1 clock
 *                        @arg RCM_APB2_PERIPH_ADC2   : ADC2 clock
 *                        @arg RCM_APB2_PERIPH_ADC3   : ADC3 clock
 *                        @arg RCM_APB2_PERIPH_SDIO   : SDIO clock
 *                        @arg RCM_APB2_PERIPH_SPI1   : SPI1 clock
 *                        @arg RCM_APB2_PERIPH_SPI4   : SPI4 clock
 *                        @arg RCM_APB2_PERIPH_SYSCFG : SYSCFG clock
 *                        @arg RCM_APB2_PERIPH_TMR9   : TMR9 clock
 *                        @arg RCM_APB2_PERIPH_TMR10  : TMR10 clock
 *                        @arg RCM_APB2_PERIPH_TMR11  : TMR11 clock
 *                        @arg RCM_APB2_PERIPH_SPI5   : SPI5 clock
 *                        @arg RCM_APB2_PERIPH_SPI6   : SPI6 clock
 *
 * @retval   None
 */
void RCM_DisableAPB2PeriphClockLPMode(uint32_t APB2Periph)
{
    RCM->LPAPB2CLKEN &= (uint32_t)~APB2Periph;
}

/*!
 * @brief     Enable RCM interrupts
 *
 * @param     interrupt : Enable specifies RCM interrupt sources.
 *                        This parameter can be any combination of the following values:
 *                        @arg RCM_INT_LSIRDY  : LSI ready interrupt
 *                        @arg RCM_INT_LSERDY  : LSE ready interrupt
 *                        @arg RCM_INT_HSIRDY  : HSI ready interrupt
 *                        @arg RCM_INT_HSERDY  : HSE ready interrupt
 *                        @arg RCM_INT_PLL1RDY : PLL1 ready interrupt
 *                        @arg RCM_INT_PLL2RDY : PLL2 ready interrupt
 *
 * @retval    None
 */
void RCM_EnableInterrupt(uint32_t interrupt)
{
    uint32_t temp;

    temp = interrupt << 8;

    RCM->INT |= temp;
}

/*!
 * @brief     Disable RCM interrupts
 *
 * @param     interrupt : Disable specifies RCM interrupt sources.
 *                        This parameter can be any combination of the following values:
 *                        @arg RCM_INT_LSIRDY  : LSI ready interrupt
 *                        @arg RCM_INT_LSERDY  : LSE ready interrupt
 *                        @arg RCM_INT_HSIRDY  : HSI ready interrupt
 *                        @arg RCM_INT_HSERDY  : HSE ready interrupt
 *                        @arg RCM_INT_PLL1RDY : PLL1 ready interrupt
 *                        @arg RCM_INT_PLL2RDY : PLL2 ready interrupt
 *
 * @retval    None
 */
void RCM_DisableInterrupt(uint32_t interrupt)
{
    uint32_t temp;

    temp = interrupt << 8;

    RCM->INT &= (uint32_t)~temp;
}

/*!
 * @brief     Read the specified RCM flag status
 *
 * @param     flag : Returns specifies the flag status.
 *                   This parameter can be one of the following values:
 *                   @arg RCM_FLAG_HSIRDY  : HSI ready flag
 *                   @arg RCM_FLAG_HSERDY  : HSE ready flag
 *                   @arg RCM_FLAG_PLL1RDY : PLL1 ready flag
 *                   @arg RCM_FLAG_PLL2RDY : PLL2 ready flag
 *                   @arg RCM_FLAG_LSERDY  : LSE ready flag
 *                   @arg RCM_FLAG_LSIRDY  : LSI ready flag
 *                   @arg RCM_FLAG_BORRST  : POR/PDR or BOR reset
 *                   @arg RCM_FLAG_PINRST  : NRST PIN Reset Occur Flag
 *                   @arg RCM_FLAG_PORRST  : POR/PDR Reset Occur Flag
 *                   @arg RCM_FLAG_SWRST   : Software Reset Occur Flag
 *                   @arg RCM_FLAG_IWDTRST : Independent Watchdog Reset Occur Flag
 *                   @arg RCM_FLAG_WWDTRST : Window Watchdog Reset Occur Flag
 *                   @arg RCM_FLAG_LPRRST  : Low Power Reset Occur Flag
 *
 * @retval    The new state of flag (SET or RESET)
 */
uint8_t RCM_ReadStatusFlag(RCM_FLAG_T flag)
{
    uint32_t reg, bit;

    bit = (uint32_t)(1 << (flag & 0xff));

    reg = (flag >> 8) & 0xff;

    switch (reg)
    {
    case 0:
        reg = RCM->CTRL;
        break;

    case 1:
        reg = RCM->BDCTRL;
        break;

    case 2:
        reg = RCM->CSTS;
        break;

    default:
        break;
    }

    if (reg & bit)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief     Clears all the RCM reset flags
 *
 * @param     None
 *
 * @retval    None
 *
 * @note      The reset flags are:
 *            RCM_FLAG_BORRST, RCM_FLAG_PINRST, RCM_FLAG_PWRST, RCM_FLAG_SWRST
 *            RCM_FLAG_IWDTRST, RCM_FLAG_WWDTRST, RCM_FLAG_LPRRST
 */
void RCM_ClearStatusFlag(void)
{
    RCM->CSTS_B.RSTFLGCLR = BIT_SET;
}

/*!
 * @brief     Reads the specified RCM interrupt Flag
 *
 * @param     flag : Reads specifies RCM interrupt flag.
 *                   This parameter can be one of the following values:
 *                   @arg RCM_INT_LSIRDY : LSI ready interrupt flag
 *                   @arg RCM_INT_LSERDY : LSE ready interrupt flag
 *                   @arg RCM_INT_HSIRDY : HSI ready interrupt flag
 *                   @arg RCM_INT_HSERDY : HSE ready interrupt flag
 *                   @arg RCM_INT_PLL1RDY: PLL1 ready interrupt flag
 *                   @arg RCM_INT_PLL2RDY: PLL2 ready interrupt flag
 *                   @arg RCM_INT_CSS    : Clock Security System interrupt flag
 *
 * @retval    The new state of intFlag (SET or RESET)
 */
uint8_t RCM_ReadIntFlag(RCM_INT_T flag)
{
    return (RCM->INT &flag) ? SET : RESET;
}

/*!
 * @brief     Clears the interrupt flag
 *
 * @param     flag : Clears specifies interrupt flag.
 *                   @arg RCM_INT_LSIRDY : Clear LSI ready interrupt flag
 *                   @arg RCM_INT_LSERDY : Clear LSE ready interrupt flag
 *                   @arg RCM_INT_HSIRDY : Clear HSI ready interrupt flag
 *                   @arg RCM_INT_HSERDY : Clear HSE ready interrupt flag
 *                   @arg RCM_INT_PLL1RDY: Clear PLL1 ready interrupt flag
 *                   @arg RCM_INT_PLL2RDY: Clear PLL2 ready interrupt flag
 *                   @arg RCM_INT_CSS    : Clear Clock Security System interrupt flag
 *
 * @retval    None
 */
void RCM_ClearIntFlag(uint32_t flag)
{
    uint32_t temp;

    temp = flag << 16;
    RCM->INT |= temp;
}

/**@} end of group RCM_Functions */
/**@} end of group RCM_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
