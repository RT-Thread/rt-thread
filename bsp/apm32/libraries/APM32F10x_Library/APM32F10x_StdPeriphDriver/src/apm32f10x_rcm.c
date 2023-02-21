/*!
 * @file        apm32f10x_rcm.c
 *
 * @brief       This file provides all the RCM firmware functions
 *
 * @version     V1.0.4
 *
 * @date        2022-12-01
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#include "apm32f10x_rcm.h"

/** @addtogroup APM32F10x_StdPeriphDriver
  @{
*/

/** @addtogroup RCM_Driver RCM Driver
  * @brief RCM driver modules
  @{
*/

/** @defgroup RCM_Functions Functions
  @{
*/

/*!
 * @brief     Reset the clock configuration to the default state
 *
 * @param     None
 *
 * @retval    None
 */
void RCM_Reset(void)
{
    /* Open HSI clock */
    RCM->CTRL_B.HSIEN = BIT_SET;
    /* Configures HSI to system clock and Reset AHBPSC, APB1PSC, APB2PSC, ADCPSC and MCOSEL bits */
#if defined(APM32F10X_CL)
    RCM->CFG &= (uint32_t)0xF0FF0000;
#else
    RCM->CFG &= (uint32_t)0xF8FF0000;
#endif

    /* Reset HSEEN, CSSEN and PLLEN bits */
    RCM->CTRL &= (uint32_t)0xFEF6FFFF;
    /* Reset HSEBCFG bit */
    RCM->CTRL_B.HSEBCFG = BIT_RESET;
    /* Reset PLLSRCSEL, PLLHSEPSC, PLLMULCFG and USBDIV bits */
    RCM->CFG &= (uint32_t)0xFF00FFFF;

#if defined(APM32F10X_CL)
    /* Reset PLL2EN and PLL3EN bits */
    RCM->CTRL_B.PLL2EN = BIT_RESET;
    RCM->CTRL_B.PLL3EN = BIT_RESET;

    /* Disable all interrupts and clear pending bits  */
    RCM->INT = 0x00FF0000;

    /* Reset CFG2 register */
    RCM->CFG2 = 0x00000000;
#else
    /* Disable all interrupts and clear pending bits */
    RCM->INT = 0x009F0000;
#endif
}

/*!
 * @brief     Configures the HSE oscillator
 *
 * @param     state: state of the HSE
 *                   This parameter can be one of the following values:
 *                   @arg RCM_HSE_CLOSE:  Turn off the HSE oscillator
 *                   @arg RCM_HSE_OPEN:   Turn on the HSE oscillator
 *                   @arg RCM_HSE_BYPASS: HSE oscillator bypassed with external clock
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
 * @brief     Wait for HSE to be ready
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
 * @brief     Configures HSI trimming value
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
 * @brief     Enable the Internal Low Speed oscillator (LSI)
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
 * @brief     Disable the Internal Low Speed oscillator (LSI)
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
 * @brief     Configures the PLL clock source and multiplication factor
 *
 * @param     pllSelect: PLL entry clock source select
 *                       This parameter can be one of the following values:
 *                       For APM32F105xx and APM32F107xx devices:
 *                        @arg RCM_PLLSEL_HSI_DIV_2: HSI clock divided by 2 selected as PLL clock source
 *                        @arg RCM_PLLSEL_PREDIV1  : PLL prescaler 1 clock selected as PLL clock source
 *                       For other devices:
 *                        @arg RCM_PLLSEL_HSI_DIV_2: HSI clock divided by 2 selected as PLL clock source
 *                        @arg RCM_PLLSEL_HSE      : HSE clock selected as PLL clock source
 *                        @arg RCM_PLLSEL_HSE_DIV2 : HSE clock divided by 2 selected as PLL clock source
 *
 * @param     pllMf:     PLL multiplication factor
 *                       For APM32F105xx and APM32F107xx devices:
 *                        This parameter can be one of the following values:
 *                        @arg RCM_PLLMF_4  : PLL Multiplication Factor Configures to 4
 *                        @arg RCM_PLLMF_5  : PLL Multiplication Factor Configures to 5
 *                        @arg RCM_PLLMF_6  : PLL Multiplication Factor Configures to 6
 *                        @arg RCM_PLLMF_7  : PLL Multiplication Factor Configures to 7
 *                        @arg RCM_PLLMF_8  : PLL Multiplication Factor Configures to 8
 *                        @arg RCM_PLLMF_9  : PLL Multiplication Factor Configures to 9
 *                        @arg RCM_PLLMF_6_5: PLL Multiplication Factor Configures to 6.5
 *                       For other devices:
 *                        This parameter can be RCM_PLLMF_x where x can be a value from 2 to 16.
 *
 * @retval    None
 *
 * @note      PLL should be disabled while use this function.
 */
void RCM_ConfigPLL(RCM_PLLSEL_T pllSelect, RCM_PLLMF_T pllMf)
{
    RCM->CFG_B.PLL1MULCFG = pllMf;
    RCM->CFG_B.PLL1SRCSEL = pllSelect & 0x01;

#ifndef APM32F10X_CL
    RCM->CFG_B.PLLHSEPSC = (pllSelect >> 1) & 0x01;
#endif
}

/*!
 * @brief      Enable the PLL
 *
 * @param      None
 *
 * @retval     None
 */
void RCM_EnablePLL(void)
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
 * @note       When PLL is not used as system clock, it can be stopped.
 */
void RCM_DisablePLL(void)
{
    RCM->CTRL_B.PLL1EN = BIT_RESET;
}

#if defined(APM32F10X_CL)
/*!
 * @brief      Enable the PLL2
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
 * @brief      Enable the PLL3
 *
 * @param      None
 *
 * @retval     None
 */
void RCM_EnablePLL3(void)
{
    RCM->CTRL_B.PLL3EN = BIT_SET;
}

/*!
 * @brief      Disable the PLL3
 *
 * @param      None
 *
 * @retval     None
 */
void RCM_DisablePLL3(void)
{
    RCM->CTRL_B.PLL3EN = BIT_RESET;
}

/*!
 * @brief     Configures the PLL prescaler 1 factor.
 *
 * @param     pllPsc1Src: PLL prescaler 1 source select
 *                        This parameter can be one of the following values:
 *                        @arg RCM_PLLPSC1_SRC_HSE : HSE clock selected as PLL prescaler 1 clock source
 *                        @arg RCM_PLLPSC1_SRC_PLL2: PLL2 clock selected as PLL prescaler 1 clock source
 *
 * @param     pllPsc1: PLL prescaler 1 factor
 *                     This parameter can be RCM_PLLPSC1_DIV_x where x can be a value from 1 to 16.
 *
 * @retval    None
 *
 * @note      PLL should be disabled while use this function.
 */
void RCM_ConfigPLLPSC1(RCM_PLLPSC1_SRC_T pllPsc1Src,  RCM_PLLPSC1_DIV_T pllPsc1)
{
    RCM->CFG2_B.PLLPSC1SRC = pllPsc1Src;
    RCM->CFG2_B.PLLPSC1 = pllPsc1;
}

/*!
 * @brief     Configures the PLL prescaler 2 factor.
 *
 * @param     pllpsc2: PLL prescaler 2 factor
 *                     This parameter can be RCM_PLLPSC2_DIV_x where x can be a value from 1 to 16.
 *
 * @retval    None
 *
 * @note      PLL2 and PLL3 should be disabled while use this function.
 */
void RCM_ConfigPLLPSC2(RCM_PLLPSC2_DIV_T pllpsc2)
{
    RCM->CFG2_B.PLLPSC2 = pllpsc2;
}

/*!
 * @brief     Configures the PLL2 clock multiplication factor
 *
 * @param     pll2Mf:  PLL2 multiplication factor
 *                     This parameter can be RCM_PLL2MF_x where x can be a value from 8 to 14, and 16, 20.
 *
 * @retval    None
 *
 * @note      PLL2 should be disabled while use this function.
 */
void RCM_ConfigPLL2(RCM_PLL2MF_T pll2Mf)
{
    RCM->CFG2_B.PLL2MUL = pll2Mf;
}

/*!
 * @brief     Configures the PLL3 clock multiplication factor
 *
 * @param     pll3Mf:  PLL3 multiplication factor
 *                     This parameter can be RCM_PLL3MF_x where x can be a value from 8 to 14, and 16, 20.
 *
 * @retval    None
 *
 * @note      PLL3 should be disabled while use this function.
 */
void RCM_ConfigPLL3(RCM_PLL3MF_T pll3Mf)
{
    RCM->CFG2_B.PLL3MUL = pll3Mf;
}
#endif

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
 * @brief     Select the MCO pin clock output source
 *
 * @param     mcoClock: specifies the clock source to output
 *                      This parameter can be one of the following values:
 *                       @arg RCM_MCOCLK_NO_CLOCK     : No clock selected.
 *                       @arg RCM_MCOCLK_SYSCLK       : System clock selected.
 *                       @arg RCM_MCOCLK_HSI          : HSI oscillator clock selected.
 *                       @arg RCM_MCOCLK_HSE          : HSE oscillator clock selected.
 *                       @arg RCM_MCOCLK_PLLCLK_DIV_2 : PLL clock divided by 2 selected.
 *                      The following values is only for APM32F105xx or APM32F107xx:
 *                       @arg RCM_MCOCLK_PLL2CLK       : PLL2 clock selected.
 *                       @arg RCM_MCOCLK_PLL3CLK_DIV_2 : PLL3 clock divided by 2 selected.
 *                       @arg RCM_MCOCLK_OSCCLK        : OSC clock selected.
 *                       @arg RCM_MCOCLK_PLL3CLK       : PLL3 clock selected.
 *
 * @retval    None
 */
void RCM_ConfigMCO(RCM_MCOCLK_T mcoClock)
{
    RCM->CFG_B.MCOSEL = mcoClock;
}

/*!
 * @brief    Configures the system clock source
 *
 * @param    sysClkSelect: specifies the clock source used as system clock
 *                         This parameter can be one of the following values:
 *                         @arg RCM_SYSCLK_SEL_HSI: HSI is selected as system clock source
 *                         @arg RCM_SYSCLK_SEL_HSE: HSE is selected as system clock source
 *                         @arg RCM_SYSCLK_SEL_PLL: PLL is selected as system clock source
 *
 * @retval    None
 */
void RCM_ConfigSYSCLK(RCM_SYSCLK_SEL_T sysClkSelect)
{
    RCM->CFG_B.SCLKSEL = sysClkSelect;
}

/*!
 * @brief     Return the clock source which is used as system clock
 *
 * @param     None
 *
 * @retval    The clock source used as system clock
 */
RCM_SYSCLK_SEL_T RCM_ReadSYSCLKSource(void)
{
    return (RCM_SYSCLK_SEL_T)RCM->CFG_B.SCLKSELSTS;
}

/*!
 * @brief     Configures the AHB clock prescaler.
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
 * @brief     Configures the APB1 clock prescaler.
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
 * @brief     Configures the APB2 clock prescaler
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

#if defined(APM32F10X_CL)
/*!
 * @brief     Configures the I2S2 clock source.
 *
 * @param     i2s2ClkSelect: specifies the I2S2 clock source.
 *                           This parameter can be one of the following values:
 *                           @arg RCM_I2S2CLK_SYSCLK     : I2S2CLK = System clock
 *                           @arg RCM_I2S2CLK_DOUBLE_PLL3: I2S2CLK = Double PLL3 clock
 *
 * @retval    None
 *
 * @note      I2S2 clock source should be changed when I2S2 Clock is disabled.
 */
void RCM_ConfigI2S2CLK(RCM_I2S2CLK_T i2s2ClkSelect)
{
    RCM->CFG2_B.I2S2SRCSEL = i2s2ClkSelect;
}

/*!
 * @brief     Configures the I2S3 clock source.
 *
 * @param     i2s3ClkSelect: specifies the I2S3 clock source.
 *                           This parameter can be one of the following values:
 *                           @arg RCM_I2S3CLK_SYSCLK     : I2S3CLK = System clock
 *                           @arg RCM_I2S3CLK_DOUBLE_PLL3: I2S3CLK = Double PLL3 clock
 *
 * @retval    None
 *
 * @note      I2S3 clock source should be changed when I2S3 Clock is disabled.
 */
void RCM_ConfigI2S3CLK(RCM_I2S2CLK_T i2s3ClkSelect)
{
    RCM->CFG2_B.I2S3SRCSEL = i2s3ClkSelect;
}

/*!
 * @brief     Configures the OTG FS clock prescaler
 *
 * @param     OTGDiv: Specifies the OTG FS clock prescaler from the PLL clock.
 *                     This parameter can be one of the following values:
 *                     @arg RCM_OTGFS_DIV_1_5 : OTGFSCLK = PLL clock /1.5
 *                     @arg RCM_OTGFS_DIV_1   : OTGFSCLK = PLL clock
 *
 * @retval    None
 */
void RCM_ConfigOTGFSCLK(RCM_OTGFS_DIV_T OTGDiv)
{
    RCM->CFG_B.OTGFSPSC = OTGDiv;
}
#else
/*!
 * @brief     Configures the USB clock prescaler
 *
 * @param     USBDiv: Specifies the USB clock prescaler from the PLL clock.
 *                     This parameter can be one of the following values:
 *                     @arg RCM_USB_DIV_1_5 : USBCLK = PLL clock /1.5
 *                     @arg RCM_USB_DIV_1   : USBCLK = PLL clock
 *                     @arg RCM_USB_DIV_2   : USBCLK = PLL clock / 2
 *                     @arg RCM_USB_DIV_2_5 : USBCLK = PLL clock / 2.5 (Only for High-density devices for APM32F103xx)
 *
 * @retval    None
 */
void RCM_ConfigUSBCLK(RCM_USB_DIV_T USBDiv)
{
    RCM->CFG_B.USBDPSC = USBDiv;
}

/*!
 * @brief     Configures the FPU clock prescaler
 *
 * @param     FPUDiv: Specifies the FPU clock prescaler from the AHB clock.
 *                     This parameter can be one of the following values:
 *                     @arg RCM_FPU_DIV_1 : FPUCLK = HCLK
 *                     @arg RCM_FPU_DIV_2 : FPUCLK = HCLK /2
 *
 * @retval    None
 */
void RCM_ConfigFPUCLK(RCM_FPU_DIV_T FPUDiv)
{
    RCM->CFG_B.FPUPSC = FPUDiv;
}
#endif


/*!
 * @brief     Configures the ADC clock prescaler
 *
 * @param     ADCDiv : Specifies the ADC clock prescaler from the APB2 clock.
 *                     This parameter can be one of the following values:
 *                     @arg RCM_PCLK2_DIV_2: ADCCLK = PCLK2 / 2
 *                     @arg RCM_PCLK2_DIV_4: ADCCLK = PCLK2 / 4
 *                     @arg RCM_PCLK2_DIV_6: ADCCLK = PCLK2 / 6
 *                     @arg RCM_PCLK2_DIV_8: ADCCLK = PCLK2 / 8
 *
 * @retval    None
 */
void RCM_ConfigADCCLK(RCM_PCLK2_DIV_T ADCDiv)
{
    RCM->CFG_B.ADCPSC = ADCDiv;
}

/*!
 * @brief     Configures the RTC clock source
 *
 * @param     rtcClkSelect : specifies the RTC clock source.
 *                           This parameter can be one of the following values:
 *                           @arg RCM_RTCCLK_LSE        : RTCCLK = LSE clock
 *                           @arg RCM_RTCCLK_LSI        : RTCCLK = LSI clock
 *                           @arg RCM_RTCCLK_HSE_DIV_128: RTCCLK = HSE clock / 128
 *
 * @retval    None
 *
 * @note      Once the RTC clock is configured it can't be changed unless reset the Backup domain.
 */
void RCM_ConfigRTCCLK(RCM_RTCCLK_T rtcClkSelect)
{
    RCM->BDCTRL_B.RTCSRCSEL = rtcClkSelect;
}

/*!
 * @brief     Enable the RTC clock
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
 * @brief     Disable the RTC clock
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
 * @brief     Read the frequency of SYSCLK
 *
 * @param     None
 *
 * @retval    Return the frequency of SYSCLK
 */
uint32_t RCM_ReadSYSCLKFreq(void)
{
#ifdef APM32F10X_CL
    uint32_t sysClock, pllMull, pllSource, pll2Mull, pllPsc1, pllPsc2;
#else
    uint32_t sysClock, pllMull, pllSource;
#endif

    /* get sys clock */
    sysClock = RCM->CFG_B.SCLKSEL;

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
#ifdef APM32F10X_CL
            /* NOTE : PLL is the same as PLL1 */
            pllSource = RCM->CFG_B.PLL1SRCSEL;

            /* PLL entry clock source is HSE */
            if (pllSource)
            {
                /* PLLPSC1 prescaler factor */
                pllPsc1 = (RCM->CFG2_B.PLLPSC1 + 1);

                /* PLL entry clock source is PLL2 */
                if (RCM->CFG2_B.PLLPSC1SRC)
                {
                    pll2Mull = (RCM->CFG2_B.PLL2MUL != 15) ? (RCM->CFG2_B.PLL2MUL + 2) : 20;
                    pllPsc2 = RCM->CFG2_B.PLLPSC2 + 1;

                    pllSource = ((HSE_VALUE / pllPsc2) * pll2Mull) / pllPsc1;
                }
                /* PLL entry clock source is HSE */
                else
                {
                    pllSource = HSE_VALUE / pllPsc1;
                }
            }
            /* PLL entry clock source is HSI/2 */
            else
            {
                pllSource = HSI_VALUE >> 1;
            }

            pllMull = RCM->CFG_B.PLL1MULCFG;
            if (pllMull == 13)
            {
                /* For 6.5 multiplication factor */
                sysClock = pllSource * pllMull / 2;
            }
            else
            {
                sysClock = pllSource * (pllMull + 2);
            }
#else
            pllMull = RCM->CFG_B.PLL1MULCFG + 2;
            pllSource = RCM->CFG_B.PLL1SRCSEL;

            /* PLL entry clock source is HSE */
            if (pllSource == BIT_SET)
            {
                sysClock = HSE_VALUE * pllMull;

                /* HSE clock divided by 2 */
                if (pllSource == RCM->CFG_B.PLLHSEPSC)
                {
                    sysClock >>= 1;
                }
            }
            /* PLL entry clock source is HSI/2 */
            else
            {
                sysClock = (HSI_VALUE >> 1) * pllMull;
            }
#endif
            break;

        default:
            sysClock  = HSI_VALUE;
            break;
    }

    return sysClock;
}

/*!
 * @brief     Read the frequency of HCLK(AHB)
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
 * @brief     Read the frequency of PCLK1 And PCLK2
 *
 * @param     PCLK1 : Return the frequency of PCLK1
 *
 * @param     PCLK1 : Return the frequency of PCLK2
 *
 * @retval    None
 */
void RCM_ReadPCLKFreq(uint32_t* PCLK1, uint32_t* PCLK2)
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
 * @brief     Read the frequency of ADCCLK
 *
 * @param     None
 *
 * @retval    Return the frequency of ADCCLK
 */
uint32_t RCM_ReadADCCLKFreq(void)
{
    uint32_t adcClk, pclk2, divider;
    uint8_t ADCPrescTable[4] = {2, 4, 6, 8};

    RCM_ReadPCLKFreq(NULL, &pclk2);

    /* Get ADC CLK */
    divider = ADCPrescTable[RCM->CFG_B.ADCPSC];
    adcClk = pclk2 / divider;

    return adcClk;
}

/*!
 * @brief    Enable AHB peripheral clock.
 *
 * @param    AHBPeriph : Enable the specifies clock of AHB peripheral.
 *                       This parameter can be any combination of the following values:
 *                       @arg RCM_AHB_PERIPH_DMA1       : Enable DMA1 clock
 *                       @arg RCM_AHB_PERIPH_DMA2       : Enable DMA2 clock (Only for High-density devices for APM32F103xx)
 *                       @arg RCM_AHB_PERIPH_SRAM       : Enable SRAM clock
 *                       @arg RCM_AHB_PERIPH_FPU        : Enable FPU clock
 *                       @arg RCM_AHB_PERIPH_FMC        : Enable FMC clock
 *                       @arg RCM_AHB_PERIPH_QSPI       : Enable QSPI clock
 *                       @arg RCM_AHB_PERIPH_CRC        : Enable CRC clock
 *                       @arg RCM_AHB_PERIPH_EMMC       : Enable EMMC clock (Only for High-density devices for APM32F103xx)
 *                       @arg RCM_AHB_PERIPH_SDIO       : Enable SDIO clock (Only for High-density devices for APM32F103xx)
 *                       @arg RCM_AHB_PERIPH_OTG_FS     : Enable OTG FS clock (Only for APM32F105xx or APM32F107xx)
 *                       @arg RCM_AHB_PERIPH_ETH_MAC    : Enable Ethernet MAC clock (Only for APM32F105xx or APM32F107xx)
 *                       @arg RCM_AHB_PERIPH_ETH_MAC_TX : Enable Ethernet MAC TX clock (Only for APM32F105xx or APM32F107xx)
 *                       @arg RCM_AHB_PERIPH_ETH_MAC_RX : Enable Ethernet MAC RX clock (Only for APM32F105xx or APM32F107xx)
 *
 * @retval   None
 */
void RCM_EnableAHBPeriphClock(uint32_t AHBPeriph)
{
    RCM->AHBCLKEN |= AHBPeriph;
}

/*!
 * @brief    Disable AHB peripheral clock.
 *
 * @param    AHBPeriph : Enable the specifies clock of AHB peripheral.
 *                       This parameter can be any combination of the following values:
 *                       @arg RCM_AHB_PERIPH_DMA1       : Disable DMA1 clock
 *                       @arg RCM_AHB_PERIPH_DMA2       : Disable DMA2 clock (Only for High-density devices for APM32F103xx)
 *                       @arg RCM_AHB_PERIPH_SRAM       : Disable SRAM clock
 *                       @arg RCM_AHB_PERIPH_FPU        : Disable FPU clock
 *                       @arg RCM_AHB_PERIPH_FMC        : Disable FMC clock
 *                       @arg RCM_AHB_PERIPH_QSPI       : Disable QSPI clock
 *                       @arg RCM_AHB_PERIPH_CRC        : Disable CRC clock
 *                       @arg RCM_AHB_PERIPH_EMMC       : Disable EMMC clock (Only for High-density devices for APM32F103xx)
 *                       @arg RCM_AHB_PERIPH_SDIO       : Disable SDIO clock (Only for High-density devices for APM32F103xx)
 *                       @arg RCM_AHB_PERIPH_OTG_FS     : Disable OTG FS clock (Only for APM32F105xx or APM32F107xx)
 *                       @arg RCM_AHB_PERIPH_ETH_MAC    : Disable Ethernet MAC clock (Only for APM32F105xx or APM32F107xx)
 *                       @arg RCM_AHB_PERIPH_ETH_MAC_TX : Disable Ethernet MAC TX clock (Only for APM32F105xx or APM32F107xx)
 *                       @arg RCM_AHB_PERIPH_ETH_MAC_RX : Disable Ethernet MAC RX clock (Only for APM32F105xx or APM32F107xx)
 *
 * @retval   None
 */
void RCM_DisableAHBPeriphClock(uint32_t AHBPeriph)
{
    RCM->AHBCLKEN &= (uint32_t)~AHBPeriph;
}

/*!
 * @brief    Enable the High Speed APB (APB2) peripheral clock
 *
 * @param    APB2Periph : Enable specifies clock of the APB2 peripheral.
 *                        This parameter can be any combination of the following values:
 *                        @arg RCM_APB2_PERIPH_AFIO   : Enable AFIO clock
 *                        @arg RCM_APB2_PERIPH_GPIOA  : Enable GPIOA clock
 *                        @arg RCM_APB2_PERIPH_GPIOB  : Enable GPIOB clock
 *                        @arg RCM_APB2_PERIPH_GPIOC  : Enable GPIOC clock
 *                        @arg RCM_APB2_PERIPH_GPIOD  : Enable GPIOD clock
 *                        @arg RCM_APB2_PERIPH_GPIOE  : Enable GPIOE clock
 *                        @arg RCM_APB2_PERIPH_GPIOF  : Enable GPIOF clock (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB2_PERIPH_GPIOG  : Enable GPIOG clock (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB2_PERIPH_ADC1   : Enable ADC1 clock
 *                        @arg RCM_APB2_PERIPH_ADC2   : Enable ADC2 clock
 *                        @arg RCM_APB2_PERIPH_TMR1   : Enable TMR1 clock
 *                        @arg RCM_APB2_PERIPH_SPI1   : Enable SPI1 clock
 *                        @arg RCM_APB2_PERIPH_TMR8   : Enable TMR8 clock (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB2_PERIPH_USART1 : Enable USART1 clock
 *                        @arg RCM_APB2_PERIPH_ADC3   : Enable ADC3 clock (Only for High-density devices for APM32F103xx)
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
 *                        @arg RCM_APB2_PERIPH_AFIO   : Disable AFIO clock
 *                        @arg RCM_APB2_PERIPH_GPIOA  : Disable GPIOA clock
 *                        @arg RCM_APB2_PERIPH_GPIOB  : Disable GPIOB clock
 *                        @arg RCM_APB2_PERIPH_GPIOC  : Disable GPIOC clock
 *                        @arg RCM_APB2_PERIPH_GPIOD  : Disable GPIOD clock
 *                        @arg RCM_APB2_PERIPH_GPIOE  : Disable GPIOE clock
 *                        @arg RCM_APB2_PERIPH_GPIOF  : Disable GPIOF clock (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB2_PERIPH_GPIOG  : Disable GPIOG clock (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB2_PERIPH_ADC1   : Disable ADC1 clock
 *                        @arg RCM_APB2_PERIPH_ADC2   : Disable ADC2 clock
 *                        @arg RCM_APB2_PERIPH_TMR1   : Disable TMR1 clock
 *                        @arg RCM_APB2_PERIPH_SPI1   : Disable SPI1 clock
 *                        @arg RCM_APB2_PERIPH_TMR8   : Disable TMR8 clock (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB2_PERIPH_USART1 : Disable USART1 clock
 *                        @arg RCM_APB2_PERIPH_ADC3   : Disable ADC3 clock (Only for High-density devices for APM32F103xx)
 *
 * @retval   None
 */
void RCM_DisableAPB2PeriphClock(uint32_t APB2Periph)
{
    RCM->APB2CLKEN &= (uint32_t)~APB2Periph;
}

/*!
 * @brief    Enable the Low Speed APB (APB1) peripheral clock
 *
 * @param    APB1Periph : Enable specifies clock of the APB1 peripheral.
 *                        This parameter can be any combination of the following values:
 *                        @arg RCM_APB1_PERIPH_TMR2   : Enable TMR2 clock
 *                        @arg RCM_APB1_PERIPH_TMR3   : Enable TMR3 clock
 *                        @arg RCM_APB1_PERIPH_TMR4   : Enable TMR4 clock
 *                        @arg RCM_APB1_PERIPH_TMR5   : Enable TMR5 clock (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_TMR6   : Enable TMR6 clock (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_TMR7   : Enable TMR7 clock (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_WWDT   : Enable WWDT clock
 *                        @arg RCM_APB1_PERIPH_SPI2   : Enable SPI2 clock
 *                        @arg RCM_APB1_PERIPH_SPI3   : Enable SPI3 clock (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_USART2 : Enable USART2 clock
 *                        @arg RCM_APB1_PERIPH_USART3 : Enable USART3 clock
 *                        @arg RCM_APB1_PERIPH_UART4  : Enable UART4 clock (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_UART5  : Enable UART5 clock (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_I2C1   : Enable I2C1 clock
 *                        @arg RCM_APB1_PERIPH_I2C2   : Enable I2C2 clock
 *                        @arg RCM_APB1_PERIPH_USB    : Enable USB clock
 *                        @arg RCM_APB1_PERIPH_CAN1   : Enable CAN1 clock
 *                        @arg RCM_APB1_PERIPH_CAN2   : Enable CAN2 clock (only for APM32F103xC device)
 *                        @arg RCM_APB1_PERIPH_BAKR   : Enable BAKR clock
 *                        @arg RCM_APB1_PERIPH_PMU    : Enable PMU clock
 *                        @arg RCM_APB1_PERIPH_DAC    : Enable DAC clock (Only for High-density devices for APM32F103xx)
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
 *                        @arg RCM_APB1_PERIPH_TMR5   : Disable TMR5 clock (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_TMR6   : Disable TMR6 clock (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_TMR7   : Disable TMR7 clock (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_WWDT   : Disable WWDT clock
 *                        @arg RCM_APB1_PERIPH_SPI2   : Disable SPI2 clock
 *                        @arg RCM_APB1_PERIPH_SPI3   : Disable SPI3 clock (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_USART2 : Disable USART2 clock
 *                        @arg RCM_APB1_PERIPH_USART3 : Disable USART3 clock
 *                        @arg RCM_APB1_PERIPH_UART4  : Disable UART4 clock (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_UART5  : Disable UART5 clock (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_I2C1   : Disable I2C1 clock
 *                        @arg RCM_APB1_PERIPH_I2C2   : Disable I2C2 clock
 *                        @arg RCM_APB1_PERIPH_USB    : Disable USB clock
 *                        @arg RCM_APB1_PERIPH_CAN1   : Disable CAN1 clock
 *                        @arg RCM_APB1_PERIPH_CAN2   : Disable CAN2 clock (only for APM32F103xC device)
 *                        @arg RCM_APB1_PERIPH_BAKR   : Disable BAKR clock
 *                        @arg RCM_APB1_PERIPH_PMU    : Disable PMU clock
 *                        @arg RCM_APB1_PERIPH_DAC    : Disable DAC clock (Only for High-density devices for APM32F103xx)
 *
 * @retval   None
 */
void RCM_DisableAPB1PeriphClock(uint32_t APB1Periph)
{
    RCM->APB1CLKEN &= (uint32_t)~APB1Periph;
}

#if defined(APM32F10X_CL)
/*!
 * @brief    Enable AHB peripheral reset
 *
 * @param    AHBPeriph : Enable specifies AHB peripheral reset.
 *                       This parameter can be any combination of the following values:
 *                       @arg RCM_AHB_PERIPH_OTG_FS  : Enable OTG FS reset
 *                       @arg RCM_AHB_PERIPH_ETH_MAC : Enable ETH MAC reset *
 * @retval   None
 */
void RCM_EnableAHBPeriphReset(uint32_t AHBPeriph)
{
    RCM->AHBRST |= AHBPeriph;
}

/*!
 * @brief    Disable AHB peripheral reset
 *
 * @param    AHBPeriph : Disable specifies AHB peripheral reset.
 *                       This parameter can be any combination of the following values:
 *                       @arg RCM_AHB_PERIPH_OTG_FS  : Disable OTG FS reset
 *                       @arg RCM_AHB_PERIPH_ETH_MAC : Disable ETH MAC reset *
 * @retval   None
 */
void RCM_DisableAHBPeriphReset(uint32_t AHBPeriph)
{
    RCM->AHBRST &= (uint32_t)~AHBPeriph;
}
#endif

/*!
 * @brief    Enable High Speed APB (APB2) peripheral reset
 *
 * @param    APB2Periph : Enable specifies APB2 peripheral reset.
 *                        This parameter can be any combination of the following values:
 *                        @arg RCM_APB2_PERIPH_AFIO   : Enable AFIO reset
 *                        @arg RCM_APB2_PERIPH_GPIOA  : Enable GPIOA reset
 *                        @arg RCM_APB2_PERIPH_GPIOB  : Enable GPIOB reset
 *                        @arg RCM_APB2_PERIPH_GPIOC  : Enable GPIOC reset
 *                        @arg RCM_APB2_PERIPH_GPIOD  : Enable GPIOD reset
 *                        @arg RCM_APB2_PERIPH_GPIOE  : Enable GPIOE reset
 *                        @arg RCM_APB2_PERIPH_GPIOF  : Enable GPIOF reset (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB2_PERIPH_GPIOG  : Enable GPIOG reset (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB2_PERIPH_ADC1   : Enable ADC1 reset
 *                        @arg RCM_APB2_PERIPH_ADC2   : Enable ADC2 reset
 *                        @arg RCM_APB2_PERIPH_TMR1   : Enable TMR1 reset
 *                        @arg RCM_APB2_PERIPH_SPI1   : Enable SPI1 reset
 *                        @arg RCM_APB2_PERIPH_TMR8   : Enable TMR8 reset (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB2_PERIPH_USART1 : Enable USART1 reset
 *                        @arg RCM_APB2_PERIPH_ADC3   : Enable ADC3 reset (Only for High-density devices for APM32F103xx)
 *
 * @retval   None
 */
void RCM_EnableAPB2PeriphReset(uint32_t APB2Periph)
{
    RCM->APB2RST |= APB2Periph;
}

/*!
 * @brief    Disable High Speed APB (APB2) peripheral reset
 *
 * @param    APB2Periph : Disable specifies APB2 peripheral reset.
 *                        This parameter can be any combination of the following values:
 *                        @arg RCM_APB2_PERIPH_AFIO   : Disable AFIO reset
 *                        @arg RCM_APB2_PERIPH_GPIOA  : Disable GPIOA reset
 *                        @arg RCM_APB2_PERIPH_GPIOB  : Disable GPIOB reset
 *                        @arg RCM_APB2_PERIPH_GPIOC  : Disable GPIOC reset
 *                        @arg RCM_APB2_PERIPH_GPIOD  : Disable GPIOD reset
 *                        @arg RCM_APB2_PERIPH_GPIOE  : Disable GPIOE reset
 *                        @arg RCM_APB2_PERIPH_GPIOF  : Disable GPIOF reset (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB2_PERIPH_GPIOG  : Disable GPIOG reset (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB2_PERIPH_ADC1   : Disable ADC1 reset
 *                        @arg RCM_APB2_PERIPH_ADC2   : Disable ADC2 reset
 *                        @arg RCM_APB2_PERIPH_TMR1   : Disable TMR1 reset
 *                        @arg RCM_APB2_PERIPH_SPI1   : Disable SPI1 reset
 *                        @arg RCM_APB2_PERIPH_TMR8   : Disable TMR8 reset (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB2_PERIPH_USART1 : Disable USART1 reset
 *                        @arg RCM_APB2_PERIPH_ADC3   : Disable ADC3 reset (Only for High-density devices for APM32F103xx)
 *
 * @retval   None
 */
void RCM_DisableAPB2PeriphReset(uint32_t APB2Periph)
{
    RCM->APB2RST &= (uint32_t)~APB2Periph;
}

/*!
 * @brief    Enable Low Speed APB (APB1) peripheral reset
 *
 * @param    APB1Periph : Enable specifies APB1 peripheral reset.
 *                        This parameter can be any combination of the following values:
 *                        @arg RCM_APB1_PERIPH_TMR2   : Enable TMR2 reset
 *                        @arg RCM_APB1_PERIPH_TMR3   : Enable TMR3 reset
 *                        @arg RCM_APB1_PERIPH_TMR4   : Enable TMR4 reset
 *                        @arg RCM_APB1_PERIPH_TMR5   : Enable TMR5 reset (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_TMR6   : Enable TMR6 reset (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_TMR7   : Enable TMR7 reset (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_WWDT   : Enable WWDT reset
 *                        @arg RCM_APB1_PERIPH_SPI2   : Enable SPI2 reset
 *                        @arg RCM_APB1_PERIPH_SPI3   : Enable SPI3 reset (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_USART2 : Enable USART2 reset
 *                        @arg RCM_APB1_PERIPH_USART3 : Enable USART3 reset
 *                        @arg RCM_APB1_PERIPH_UART4  : Enable UART4 reset (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_UART5  : Enable UART5 reset (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_I2C1   : Enable I2C1 reset
 *                        @arg RCM_APB1_PERIPH_I2C2   : Enable I2C2 reset
 *                        @arg RCM_APB1_PERIPH_USB    : Enable USB reset
 *                        @arg RCM_APB1_PERIPH_CAN1   : Enable CAN1 reset
 *                        @arg RCM_APB1_PERIPH_CAN2   : Enable CAN2 reset (only for APM32F103xC device)
 *                        @arg RCM_APB1_PERIPH_BAKR   : Enable BAKR reset
 *                        @arg RCM_APB1_PERIPH_PMU    : Enable PMU reset
 *                        @arg RCM_APB1_PERIPH_DAC    : Enable DAC reset
 *
 * @retval   None
 */
void RCM_EnableAPB1PeriphReset(uint32_t APB1Periph)
{
    RCM->APB1RST |= APB1Periph;
}

/*!
 * @brief    Disable Low Speed APB (APB1) peripheral reset
 *
 * @param    APB1Periph : Disable specifies APB1 peripheral reset.
 *                        This parameter can be any combination of the following values:
 *                        @arg RCM_APB1_PERIPH_TMR2   : Disable TMR2 reset
 *                        @arg RCM_APB1_PERIPH_TMR3   : Disable TMR3 reset
 *                        @arg RCM_APB1_PERIPH_TMR4   : Disable TMR4 reset
 *                        @arg RCM_APB1_PERIPH_TMR5   : Disable TMR5 reset (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_TMR6   : Disable TMR6 reset (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_TMR7   : Disable TMR7 reset (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_WWDT   : Disable WWDT reset
 *                        @arg RCM_APB1_PERIPH_SPI2   : Disable SPI2 reset
 *                        @arg RCM_APB1_PERIPH_SPI3   : Disable SPI3 reset (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_USART2 : Disable USART2 reset
 *                        @arg RCM_APB1_PERIPH_USART3 : Disable USART3 reset
 *                        @arg RCM_APB1_PERIPH_UART4  : Disable UART4 reset (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_UART5  : Disable UART5 reset (Only for High-density devices for APM32F103xx)
 *                        @arg RCM_APB1_PERIPH_I2C1   : Disable I2C1 reset
 *                        @arg RCM_APB1_PERIPH_I2C2   : Disable I2C2 reset
 *                        @arg RCM_APB1_PERIPH_USB    : Disable USB reset
 *                        @arg RCM_APB1_PERIPH_CAN1   : Disable CAN1 reset
 *                        @arg RCM_APB1_PERIPH_CAN2   : Disable CAN2 reset (only for APM32F103xC device)
 *                        @arg RCM_APB1_PERIPH_BAKR   : Disable BAKR reset
 *                        @arg RCM_APB1_PERIPH_PMU    : Disable PMU reset
 *                        @arg RCM_APB1_PERIPH_DAC    : Disable DAC reset
 *
 * @retval   None
 */
void RCM_DisableAPB1PeriphReset(uint32_t APB1Periph)
{
    RCM->APB1RST &= (uint32_t)~APB1Periph;
}

/*!
 * @brief     Enable the Backup domain reset
 *
 * @param     None
 *
 * @retval    None
 *
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
 * @brief     Enable RCM interrupts
 *
 * @param     interrupt : Enable specifies RCM interrupt sources.
 *                        This parameter can be any combination of the following values:
 *                        @arg RCM_INT_LSIRDY : LSI ready interrupt
 *                        @arg RCM_INT_LSERDY : LSE ready interrupt
 *                        @arg RCM_INT_HSIRDY : HSI ready interrupt
 *                        @arg RCM_INT_HSERDY : HSE ready interrupt
 *                        @arg RCM_INT_PLLRDY : PLL ready interrupt
 *                        @arg RCM_INT_PLL2RDY: PLL2 ready interrupt
 *                        @arg RCM_INT_PLL3RDY: PLL3 ready interrupt
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
 *                        @arg RCM_INT_LSIRDY : LSI ready interrupt
 *                        @arg RCM_INT_LSERDY : LSE ready interrupt
 *                        @arg RCM_INT_HSIRDY : HSI ready interrupt
 *                        @arg RCM_INT_HSERDY : HSE ready interrupt
 *                        @arg RCM_INT_PLLRDY : PLL ready interrupt
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
 * @param     flag : Return specifies the flag status.
 *                   This parameter can be one of the following values:
 *                   @arg RCM_FLAG_HSIRDY  : HSI ready flag
 *                   @arg RCM_FLAG_HSERDY  : HSE ready flag
 *                   @arg RCM_FLAG_PLLRDY  : PLL ready flag
 *                   @arg RCM_FLAG_PLL2RDY : PLL2 ready flag (Only for APM32F105xx or APM32F107xx)
 *                   @arg RCM_FLAG_PLL3RDY : PLL3 ready flag (Only for APM32F105xx or APM32F107xx)
 *                   @arg RCM_FLAG_LSERDY  : LSE ready flag
 *                   @arg RCM_FLAG_LSIRDY  : LSI ready flag
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
 * @brief     Clear all the RCM reset flags
 *
 * @param     None
 *
 * @retval    None
 *
 * @note      The reset flags are:
 *            RCM_FLAG_PINRST, RCM_FLAG_PWRST, RCM_FLAG_SWRST
 *            RCM_FLAG_IWDTRST, RCM_FLAG_WWDTRST, RCM_FLAG_LPRRST
 */
void RCM_ClearStatusFlag(void)
{
    RCM->CSTS_B.RSTFLGCLR = BIT_SET;
}

/*!
 * @brief     Read the specified RCM interrupt Flag
 *
 * @param     flag ��Reads specifies RCM interrupt flag.
 *                   This parameter can be one of the following values:
 *                   @arg RCM_INT_LSIRDY : LSI ready interrupt flag
 *                   @arg RCM_INT_LSERDY : LSE ready interrupt flag
 *                   @arg RCM_INT_HSIRDY : HSI ready interrupt flag
 *                   @arg RCM_INT_HSERDY : HSE ready interrupt flag
 *                   @arg RCM_INT_PLLRDY : PLL ready interrupt flag
 *                   @arg RCM_INT_PLL2RDY: PLL2 ready interrupt flag
 *                   @arg RCM_INT_PLL3RDY: PLL3 ready interrupt flag
 *                   @arg RCM_INT_CSS    : Clock Security System interrupt flag
 *
 * @retval    The new state of intFlag (SET or RESET)
 */
uint8_t RCM_ReadIntFlag(RCM_INT_T flag)
{
    return (RCM->INT& flag) ? SET : RESET;
}

/*!
 * @brief     Clear the interrupt flag
 *
 * @param     flag : Clear specifies interrupt flag.
 *                   @arg RCM_INT_LSIRDY : Clear LSI ready interrupt flag
 *                   @arg RCM_INT_LSERDY : Clear LSE ready interrupt flag
 *                   @arg RCM_INT_HSIRDY : Clear HSI ready interrupt flag
 *                   @arg RCM_INT_HSERDY : Clear HSE ready interrupt flag
 *                   @arg RCM_INT_PLLRDY : Clear PLL ready interrupt flag
 *                   @arg RCM_INT_PLL2RDY: Clear PLL2 ready interrupt flag
 *                   @arg RCM_INT_PLL3RDY: Clear PLL3 ready interrupt flag
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
/**@} end of group APM32F10x_StdPeriphDriver */
