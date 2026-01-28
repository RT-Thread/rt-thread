/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32l40x_rcc.c
 * @author Nations
 * @version v1.2.0
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "n32l40x_rcc.h"

/** @addtogroup n32l40x_StdPeriph_Driver
 * @{
 */

/** @addtogroup RCC
 * @brief RCC driver modules
 * @{
 */

/** @addtogroup RCC_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @addtogroup RCC_Private_Defines
 * @{
 */

/* ------------ RCC registers bit address in the alias region ----------- */
#define RCC_OFFSET (RCC_BASE - PERIPH_BASE)

/* --- CTRL Register ---*/

/* Alias word address of HSIEN bit */
#define CTRL_OFFSET   (RCC_OFFSET + 0x00)
#define HSIEN_BITN    0x00
#define CTRL_HSIEN_BB (PERIPH_BB_BASE + (CTRL_OFFSET * 32) + (HSIEN_BITN * 4))

/* Alias word address of PLLEN bit */
#define PLLEN_BITN    0x18
#define CTRL_PLLEN_BB (PERIPH_BB_BASE + (CTRL_OFFSET * 32) + (PLLEN_BITN * 4))

/* Alias word address of CLKSSEN bit */
#define CLKSSEN_BITN    0x13
#define CTRL_CLKSSEN_BB (PERIPH_BB_BASE + (CTRL_OFFSET * 32) + (CLKSSEN_BITN * 4))

/* --- CFG Register ---*/

/* Alias word address of USBPRES bit */
#define CFG_OFFSET (RCC_OFFSET + 0x04)

#define USBPRES_BITN   0x16
#define CFG_USBPRES_BB (PERIPH_BB_BASE + (CFG_OFFSET * 32) + (USBPRES_BITN * 4))

#define USBPRE_Bit1Number   0x17
#define CFGR_USBPRE_BB_BIT1 (PERIPH_BB_BASE + (CFG_OFFSET * 32) + (USBPRE_Bit1Number * 4))

/* --- CLKINT Register ---*/

#define CLKINT_OFFSET (RCC_OFFSET + 0x08)

/* Alias word address of LSIRDIF bit */
#define LSIRDIF_BITN   0x00
#define CLKINT_LSIRDIF_BB (PERIPH_BB_BASE + (CLKINT_OFFSET * 32) + (LSIRDIF_BITN * 4))

/* --- LDCTRL Register ---*/

/* Alias word address of LSECLKSSEN bit */
#define LSECLKSSEN_BITN    0x03
#define LDCTRL_LSECLKSSEN_BB (PERIPH_BB_BASE + (LDCTRL_OFFSET * 32) + (LSECLKSSEN_BITN * 4))

/* Alias word address of RTCEN bit */
#define LDCTRL_OFFSET   (RCC_OFFSET + 0x20)
#define RTCEN_BITN       0x0F
#define LDCTRL_RTCEN_BB (PERIPH_BB_BASE + (LDCTRL_OFFSET * 32) + (RTCEN_BITN * 4))

/* Alias word address of LDSFTRST bit */
#define LDSFTRST_BITN      0x10
#define LDCTRL_LDSFTRST_BB (PERIPH_BB_BASE + (LDCTRL_OFFSET * 32) + (LDSFTRST_BITN * 4))

/* --- CTRLSTS Register ---*/

/* Alias word address of LSIEN bit */
#define CTRLSTS_OFFSET   (RCC_OFFSET + 0x24)
#define LSIEN_BITNUMBER  0x00
#define CTRLSTS_LSIEN_BB (PERIPH_BB_BASE + (CTRLSTS_OFFSET * 32) + (LSIEN_BITNUMBER * 4))

/* Alias word address of MSIEN bit */
#define MSIEN_BITNUMBER  0x02
#define CTRLSTS_MSIEN_BB (PERIPH_BB_BASE + (CTRLSTS_OFFSET * 32) + (MSIEN_BITNUMBER * 4))

/* ---------------------- RCC registers bit mask ------------------------ */

/* CTRL register bit mask */
#define CTRL_HSEBP_RESET  ((uint32_t)0xFFFBFFFF)
#define CTRL_HSEBP_SET    ((uint32_t)0x00040000)
#define CTRL_HSEEN_RESET  ((uint32_t)0xFFFEFFFF)
#define CTRL_HSEEN_SET    ((uint32_t)0x00010000)
#define CTRL_HSITRIM_MASK ((uint32_t)0xFFFFFF83)
#define CTRL_HSIEN_RESET  ((uint32_t)0xFFFFFFFE)
#define CTRL_HSIEN_SET    ((uint32_t)0x00000001)

/* CTRLSTS register bit mask */
#define CTRLSTS_MSITRIM_MASK   ((uint32_t)0xFF807FFF)
#define CTRLSTS_MSIEN_RESET    ((uint32_t)0xFFFFFFFB)
#define CTRLSTS_MSIEN_SET      ((uint32_t)0x00000004)

#define CTRLSTS_MSIRANGE_MASK  ((uint32_t)0xFFFFFF8F)
#define CTRLSTS_MSIRANGE_RESET ((uint32_t)0x00000060) /* 4MHz */

/* CFG register bit mask */
#define CFG_PLL_MASK ((uint32_t)0xF7C0FFFF)

#define CFG_PLLMULFCT_MASK      ((uint32_t)0x083C0000)
#define CFG_PLLSRC_MASK         ((uint32_t)0x00010000)
#define CFG_PLLHSEPRES_MASK     ((uint32_t)0x00020000)
#define CFG_SCLKSTS_MASK        ((uint32_t)0x0000000C)
#define CFG_SCLKSW_MASK         ((uint32_t)0xFFFFFFFC)
#define CFG_AHBPRES_RESET_MASK  ((uint32_t)0xFFFFFF0F)
#define CFG_AHBPRES_SET_MASK    ((uint32_t)0x000000F0)
#define CFG_APB1PRES_RESET_MASK ((uint32_t)0xFFFFF8FF)
#define CFG_APB1PRES_SET_MASK   ((uint32_t)0x00000700)
#define CFG_APB2PRES_RESET_MASK ((uint32_t)0xFFFFC7FF)
#define CFG_APB2PRES_SET_MASK   ((uint32_t)0x00003800)

/* CFG2 register bit mask */
#define CFG2_TIM18CLKSEL_SET_MASK   ((uint32_t)0x20000000)
#define CFG2_TIM18CLKSEL_RESET_MASK ((uint32_t)0xDFFFFFFF)
#define CFG2_RNGCPRES_SET_MASK      ((uint32_t)0x1F000000)
#define CFG2_RNGCPRES_RESET_MASK    ((uint32_t)0xE0FFFFFF)
#define CFG2_ETHCLKSEL_SET_MASK     ((uint32_t)0x00100000)
#define CFG2_ETHCLKSEL_RESET_MASK   ((uint32_t)0xFFEFFFFF)
#define CFG2_ADC1MSEL_SET_MASK      ((uint32_t)0x00020000)
#define CFG2_ADC1MSEL_RESET_MASK    ((uint32_t)0xFFFDFFFF)
#define CFG2_ADC1MPRES_SET_MASK     ((uint32_t)0x0001F000)
#define CFG2_ADC1MPRES_RESET_MASK   ((uint32_t)0xFFFE0FFF)
#define CFG2_ADCPLLPRES_SET_MASK    ((uint32_t)0x000001F0)
#define CFG2_ADCPLLPRES_RESET_MASK  ((uint32_t)0xFFFFFE0F)
#define CFG2_ADCHPRES_SET_MASK      ((uint32_t)0x0000000F)
#define CFG2_ADCHPRES_RESET_MASK    ((uint32_t)0xFFFFFFF0)

/* CFG3 register bit mask */
#define CFGR3_TRNG1MSEL_SET_MASK    ((uint32_t)0x00020000)
#define CFGR3_TRNG1MSEL_RESET_MASK  ((uint32_t)0xFFFDFFFF)
#define CFGR3_TRNG1MPRES_SET_MASK   ((uint32_t)0x0000F800)
#define CFGR3_TRNG1MPRES_RESET_MASK ((uint32_t)0xFFFF07FF)

/* CTRLSTS register bit mask */
#define CSR_RMRSTF_SET ((uint32_t)0x01000000)
#define CSR_RMVF_Reset ((uint32_t)0xfeffffff)

/* RCC Flag Mask */
#define FLAG_MASK ((uint8_t)0x1F)

/* CLKINT register(Bits[31:0]) base address */
#define CLKINT_ADDR ((uint32_t)0x40021008)

/* LDCTRL register base address */
#define LDCTRL_ADDR (PERIPH_BASE + LDCTRL_OFFSET)

/* RDCTRL register bit mask */
#define RDCTRL_LPTIMCLKSEL_MASK      ((uint32_t)0x00000007)
#define RDCTRL_LPUARTCLKSEL_MASK     ((uint32_t)0x00000018)

/* PLLHSIPRE register bit mask */
#define PLLHSIPRE_PLLHSI_PRE_MASK    ((uint32_t)0x00000001)
#define PLLHSIPRE_PLLSRCDIV_MASK     ((uint32_t)0x00000002)

#define LSE_TRIMR_ADDR               ((uint32_t)0x40001808)

#define LSE_GM_MASK_VALUE            (0x1FF)
#define LSE_GM_MAX_VALUE             (0x1FF)
#define LSE_GM_DEFAULT_VALUE         (0x1FF)

/**
 * @}
 */

/** @addtogroup RCC_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup RCC_Private_Variables
 * @{
 */

static const uint8_t s_ApbAhbPresTable[16]     = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};
static const uint8_t s_AdcHclkPresTable[16]    = {1, 2, 4, 6, 8, 10, 12, 16, 32, 32, 32, 32, 32, 32, 32, 32};
static const uint16_t s_AdcPllClkPresTable[16] = {1, 2, 4, 6, 8, 10, 12, 16, 32, 64, 128, 256, 256, 256, 256, 256};
static const uint32_t s_msiClockTable[7]       = {MSI_VALUE_L0, MSI_VALUE_L1, MSI_VALUE_L2, MSI_VALUE_L3,
                                                  MSI_VALUE_L4, MSI_VALUE_L5, MSI_VALUE_L6};

/**
 * @}
 */

/** @addtogroup RCC_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @addtogroup RCC_Private_Functions
 * @{
 */

/**
 * @brief  Resets the RCC clock configuration to the default reset state.
 */
void RCC_DeInit(void)
{
    /* Set MSIEN bit */
    RCC->CTRLSTS |= (uint32_t)0x00000004;

    /* Reset SW, HPRE, PPRE1, PPRE2 and MCO bits */
    RCC->CFG &= (uint32_t)0xF8FFC000;

    /* Reset HSIEN, HSEEN, CLKSSEN and PLLEN bits */
    RCC->CTRL &= (uint32_t)0xFEF6FFFE;

    /* Reset HSEBYP bit */
    RCC->CTRL &= (uint32_t)0xFFFBFFFF;

    /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRES bits */
    RCC->CFG &= (uint32_t)0xF700FFFF;

    /* Reset CFG2 register */
    RCC->CFG2 = 0x00007000;

    /* Reset CFG3 register */
    RCC->CFG3 = 0x00003800;

    /* Reset RDCTRL register */
    RCC->RDCTRL = 0x00000000;

    /* Reset PLLHSIPRE register */
    RCC->PLLHSIPRE = 0x00000000;

    /* Disable all interrupts and clear pending bits  */
    RCC->CLKINT = 0x04BF8000;
}

/**
 * @brief  Configures the External High Speed oscillator (HSE).
 * @note   HSE can not be stopped if it is used directly or through the PLL as system clock.
 * @param RCC_HSE specifies the new state of the HSE.
 *   This parameter can be one of the following values:
 *     @arg RCC_HSE_DISABLE HSE oscillator OFF
 *     @arg RCC_HSE_ENABLE HSE oscillator ON
 *     @arg RCC_HSE_BYPASS HSE oscillator bypassed with external clock
 */
void RCC_ConfigHse(uint32_t RCC_HSE)
{
    /* Check the parameters */
    assert_param(IS_RCC_HSE(RCC_HSE));
    /* Reset HSEON and HSEBYP bits before configuring the HSE ------------------*/
    /* Reset HSEON bit */
    RCC->CTRL &= CTRL_HSEEN_RESET;
    /* Reset HSEBYP bit */
    RCC->CTRL &= CTRL_HSEBP_RESET;
    /* Configure HSE (RCC_HSE_DISABLE is already covered by the code section above) */
    switch (RCC_HSE)
    {
        case RCC_HSE_ENABLE:
            /* Set HSEEN bit */
            RCC->CTRL |= CTRL_HSEEN_SET;
            break;

        case RCC_HSE_BYPASS:
            /* Set HSEBYP and HSEEN bits */
            RCC->CTRL |= CTRL_HSEBP_SET | CTRL_HSEEN_SET;
            break;

        default:
            break;
    }
}

/**
 * @brief  Waits for HSE start-up.
 * @return An ErrorStatus enumuration value:
 * - SUCCESS: HSE oscillator is stable and ready to use
 * - ERROR: HSE oscillator not yet ready
 */
ErrorStatus RCC_WaitHseStable(void)
{
    __IO uint32_t StartUpCounter = 0;
    ErrorStatus status           = ERROR;
    FlagStatus HSEStatus         = RESET;

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC_GetFlagStatus(RCC_CTRL_FLAG_HSERDF);
        StartUpCounter++;
    } while ((StartUpCounter != HSE_STARTUP_TIMEOUT) && (HSEStatus == RESET));

    if (RCC_GetFlagStatus(RCC_CTRL_FLAG_HSERDF) != RESET)
    {
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }
    return (status);
}

/**
 * @brief  Configures the Internal High Speed oscillator (HSI).
 * @note   HSI can not be stopped if it is used directly or through the PLL as system clock.
 * @param RCC_HSI specifies the new state of the HSI.
 *   This parameter can be one of the following values:
 *     @arg RCC_HSI_DISABLE HSI oscillator OFF
 *     @arg RCC_HSI_ENABLE HSI oscillator ON
 */
void RCC_ConfigHsi(uint32_t RCC_HSI)
{
    /* Check the parameters */
    assert_param(IS_RCC_HSI(RCC_HSI));
    /* Reset HSIEN bit */
    RCC->CTRL &= CTRL_HSIEN_RESET;
    /* Configure HSI */
    switch (RCC_HSI)
    {
        case RCC_HSI_ENABLE:
            /* Set HSIEN bit */
            RCC->CTRL |= CTRL_HSIEN_SET;
            break;

        default:
            break;
    }
}

/**
 * @brief  Waits for HSI start-up.
 * @return An ErrorStatus enumuration value:
 * - SUCCESS: HSI oscillator is stable and ready to use
 * - ERROR: HSI oscillator not yet ready
 */
ErrorStatus RCC_WaitHsiStable(void)
{
    __IO uint32_t StartUpCounter = 0;
    ErrorStatus status           = ERROR;
    FlagStatus HSIStatus         = RESET;

    /* Wait till HSI is ready and if Time out is reached exit */
    do
    {
        HSIStatus = RCC_GetFlagStatus(RCC_CTRL_FLAG_HSIRDF);
        StartUpCounter++;
    } while ((StartUpCounter != HSI_STARTUP_TIMEOUT) && (HSIStatus == RESET));

    if (RCC_GetFlagStatus(RCC_CTRL_FLAG_HSIRDF) != RESET)
    {
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }
    return (status);
}

/**
 * @brief  Adjusts the Internal High Speed oscillator (HSI) calibration value.
 * @param HSICalibrationValue specifies the calibration trimming value.
 *   This parameter must be a number between 0 and 0x1F.
 */
void RCC_SetHsiCalibValue(uint8_t HSICalibrationValue)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_RCC_CALIB_VALUE(HSICalibrationValue));
    tmpregister = RCC->CTRL;
    /* Clear HSITRIM[4:0] bits */
    tmpregister &= CTRL_HSITRIM_MASK;
    /* Set the HSITRIM[4:0] bits according to HSICalibrationValue value */
    tmpregister |= (uint32_t)HSICalibrationValue << 2;
    /* Store the new value */
    RCC->CTRL = tmpregister;
}

/**
 * @brief  Enables or disables the Internal High Speed oscillator (HSI).
 * @note   HSI can not be stopped if it is used directly or through the PLL as system clock.
 * @param Cmd new state of the HSI. This parameter can be: ENABLE or DISABLE.
 */
void RCC_EnableHsi(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    *(__IO uint32_t*)CTRL_HSIEN_BB = (uint32_t)Cmd;
}

/**
 * @brief  Configures the Multi Speed oscillator (MSI).
 * @param RCC_MSI specifies the new state of the MSI.
 *   This parameter can be one of the following values:
 *     @arg RCC_MSI_DISABLE MSI oscillator OFF
 *     @arg RCC_MSI_ENABLE MSI oscillator ON
 * @param RCC_MSI_Range specifies the clock of the MSI.
 *   This parameter can be one of the following values:
 *     @arg RCC_MSI_RANGE_100K 100KHz
 *     @arg RCC_MSI_RANGE_200K 200KHz
 *     @arg RCC_MSI_RANGE_400K 400KHz
 *     @arg RCC_MSI_RANGE_800K 800KHz
 *     @arg RCC_MSI_RANGE_1M   1MHz
 *     @arg RCC_MSI_RANGE_2M   2MHz
 *     @arg RCC_MSI_RANGE_4M   4MHz
 */
void RCC_ConfigMsi(uint32_t RCC_MSI, uint32_t RCC_MSI_Range)
{
    /* Check the parameters */
    assert_param(IS_RCC_MSI(RCC_MSI));
    assert_param(IS_RCC_MSI_RANGE(RCC_MSI_Range));
    /* Set MSIRANGE[2:0] bit */
    RCC->CTRLSTS &= CTRLSTS_MSIRANGE_MASK;
    RCC->CTRLSTS |= RCC_MSI_Range;
    /* Configure MSI */
    switch (RCC_MSI)
    {
        case RCC_MSI_ENABLE:
            /* Set MSIEN bit */
            RCC->CTRLSTS |= CTRLSTS_MSIEN_SET;
            break;
        case RCC_MSI_DISABLE:
            /* Reset MSIEN bit */
            RCC->CTRLSTS &= CTRLSTS_MSIEN_RESET;
            break;
        default:
            break;
    }
}

/**
 * @brief  Waits for MSI start-up.
 * @return An ErrorStatus enumuration value:
 * - SUCCESS: MSI oscillator is stable and ready to use
 * - ERROR: MSI oscillator not yet ready
 */
ErrorStatus RCC_WaitMsiStable(void)
{
    __IO uint32_t StartUpCounter = 0;
    ErrorStatus status           = ERROR;
    FlagStatus MSIStatus         = RESET;

    /* Wait till MSI is ready and if Time out is reached exit */
    do
    {
        MSIStatus = RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_MSIRD);
        StartUpCounter++;
    } while ((StartUpCounter != MSI_STARTUP_TIMEOUT) && (MSIStatus == RESET));

    if (RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_MSIRD) != RESET)
    {
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }
    return (status);
}

/**
 * @brief  Adjusts the Multi Speed oscillator (MSI) calibration value.
 * @param MSICalibrationValue specifies the calibration trimming value.
 *   This parameter must be a number between 0 and 0xFF.
 */
void RCC_SetMsiCalibValue(uint8_t MSICalibrationValue)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    //assert_param(IS_RCC_MSICALIB_VALUE(MSICalibrationValue));
    tmpregister = RCC->CTRLSTS;
    /* Clear MSITRIM[7:0] bits */
    tmpregister &= CTRLSTS_MSITRIM_MASK;
    /* Set the MSITRIM[7:0] bits according to MSICalibrationValue value */
    tmpregister |= (uint32_t)MSICalibrationValue << 15;
    /* Store the new value */
    RCC->CTRLSTS = tmpregister;
}

/**
 * @brief  Enables or disables the Multi Speed oscillator (MSI).
 * @param Cmd new state of the MSI. This parameter can be: ENABLE or DISABLE.
 */
void RCC_EnableMsi(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    *(__IO uint32_t*)CTRLSTS_MSIEN_BB = (uint32_t)Cmd;
}

/**
 * @brief  Configures the PLL clock source and multiplication factor.
 * @note   This function must be used only when the PLL is disabled.
 * @param RCC_PLLSource specifies the PLL entry clock source.
 *   this parameter can be one of the following values:
 *     @arg RCC_PLL_HSI_PRE_DIV1 HSI oscillator clock selected as PLL clock entry
 *     @arg RCC_PLL_HSI_PRE_DIV2 HSI oscillator clock divided by 2 selected as PLL clock entry
 *     @arg RCC_PLL_SRC_HSE_DIV1 HSE oscillator clock selected as PLL clock entry
 *     @arg RCC_PLL_SRC_HSE_DIV2 HSE oscillator clock divided by 2 selected as PLL clock entry
 * @param RCC_PLLMul specifies the PLL multiplication factor.
 *    this parameter can be RCC_PLLMul_x where x:[2,32]
 * @param RCC_PLLDIVCLK specifies the PLL divider feedback clock source.
 *   this parameter can be one of the following values:
 *     @arg RCC_PLLDIVCLK_DISABLE PLLSource clock selected as PLL clock entry
 *     @arg RCC_PLLDIVCLK_ENABLE  PLLSource clock divided by 2 selected as PLL clock entry
 */
void RCC_ConfigPll(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul, uint32_t RCC_PLLDIVCLK)
{
    uint32_t tmpregister = 0;
    uint32_t pllhsipreregister = 0;

    /* Check the parameters */
    assert_param(IS_RCC_PLL_SRC(RCC_PLLSource));
    assert_param(IS_RCC_PLL_MUL(RCC_PLLMul));
    assert_param(IS_RCC_PLL_DIVCLK(RCC_PLLDIVCLK));

    tmpregister = RCC->CFG;
    pllhsipreregister = RCC->PLLHSIPRE;
    /* Clear PLLSRC, PLLXTPRE and PLLMUL[4:0] bits */
    tmpregister &= CFG_PLL_MASK;
    /* Clear PLLHSIPRE, PLLSRCDIV bits */
    pllhsipreregister &= (~(PLLHSIPRE_PLLHSI_PRE_MASK | PLLHSIPRE_PLLSRCDIV_MASK));
    /* Set the PLL configuration bits */
    if ((RCC_PLLSource == RCC_PLL_HSI_PRE_DIV1) || (RCC_PLLSource == RCC_PLL_HSI_PRE_DIV2))
    {
        tmpregister       |= RCC_PLLMul;
        pllhsipreregister |= RCC_PLLSource | RCC_PLLDIVCLK;
    }
    /* (RCC_PLLSource == RCC_PLL_SRC_HSE_DIV1) || (RCC_PLLSource == RCC_PLL_SRC_HSE_DIV2) */
    else
    {
        tmpregister       |= RCC_PLLSource | RCC_PLLMul;
        pllhsipreregister |= RCC_PLLDIVCLK;
    }
    /* Store the new value */
    RCC->CFG       = tmpregister;
    RCC->PLLHSIPRE = pllhsipreregister;
}

/**
 * @brief  Enables or disables the PLL.
 * @note   The PLL can not be disabled if it is used as system clock.
 * @param Cmd new state of the PLL. This parameter can be: ENABLE or DISABLE.
 */
void RCC_EnablePll(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    *(__IO uint32_t*)CTRL_PLLEN_BB = (uint32_t)Cmd;
}

/**
 * @brief  Configures the system clock (SYSCLK).
 * @param RCC_SYSCLKSource specifies the clock source used as system clock.
 *   This parameter can be one of the following values:
 *     @arg RCC_SYSCLK_SRC_MSI    HSI selected as system clock
 *     @arg RCC_SYSCLK_SRC_HSI    HSI selected as system clock
 *     @arg RCC_SYSCLK_SRC_HSE    HSE selected as system clock
 *     @arg RCC_SYSCLK_SRC_PLLCLK PLL selected as system clock
 */
void RCC_ConfigSysclk(uint32_t RCC_SYSCLKSource)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_RCC_SYSCLK_SRC(RCC_SYSCLKSource));
    tmpregister = RCC->CFG;
    /* Clear SW[1:0] bits */
    tmpregister &= CFG_SCLKSW_MASK;
    /* Set SW[1:0] bits according to RCC_SYSCLKSource value */
    tmpregister |= RCC_SYSCLKSource;
    /* Store the new value */
    RCC->CFG = tmpregister;
}

/**
 * @brief  Returns the clock source used as system clock.
 * @return The clock source used as system clock. The returned value can
 *   be one of the following:
 *     - 0x00: MSI used as system clock
 *     - 0x04: HSI used as system clock
 *     - 0x08: HSE used as system clock
 *     - 0x0C: PLL used as system clock
 */
uint8_t RCC_GetSysclkSrc(void)
{
    return ((uint8_t)(RCC->CFG & CFG_SCLKSTS_MASK));
}

/**
 * @brief  Configures the AHB clock (HCLK).
 * @param RCC_SYSCLK defines the AHB clock divider. This clock is derived from
 *   the system clock (SYSCLK).
 *   This parameter can be one of the following values:
 *     @arg RCC_SYSCLK_DIV1 AHB clock = SYSCLK
 *     @arg RCC_SYSCLK_DIV2 AHB clock = SYSCLK/2
 *     @arg RCC_SYSCLK_DIV4 AHB clock = SYSCLK/4
 *     @arg RCC_SYSCLK_DIV8 AHB clock = SYSCLK/8
 *     @arg RCC_SYSCLK_DIV16 AHB clock = SYSCLK/16
 *     @arg RCC_SYSCLK_DIV64 AHB clock = SYSCLK/64
 *     @arg RCC_SYSCLK_DIV128 AHB clock = SYSCLK/128
 *     @arg RCC_SYSCLK_DIV256 AHB clock = SYSCLK/256
 *     @arg RCC_SYSCLK_DIV512 AHB clock = SYSCLK/512
 */
void RCC_ConfigHclk(uint32_t RCC_SYSCLK)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_RCC_SYSCLK_DIV(RCC_SYSCLK));
    tmpregister = RCC->CFG;
    /* Clear HPRE[3:0] bits */
    tmpregister &= CFG_AHBPRES_RESET_MASK;
    /* Set HPRE[3:0] bits according to RCC_SYSCLK value */
    tmpregister |= RCC_SYSCLK;
    /* Store the new value */
    RCC->CFG = tmpregister;
}

/**
 * @brief  Configures the Low Speed APB clock (PCLK1).
 * @param RCC_HCLK defines the APB1 clock divider. This clock is derived from
 *   the AHB clock (HCLK).
 *   This parameter can be one of the following values:
 *     @arg RCC_HCLK_DIV1 APB1 clock = HCLK
 *     @arg RCC_HCLK_DIV2 APB1 clock = HCLK/2
 *     @arg RCC_HCLK_DIV4 APB1 clock = HCLK/4
 *     @arg RCC_HCLK_DIV8 APB1 clock = HCLK/8
 *     @arg RCC_HCLK_DIV16 APB1 clock = HCLK/16
 */
void RCC_ConfigPclk1(uint32_t RCC_HCLK)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_RCC_HCLK_DIV(RCC_HCLK));
    tmpregister = RCC->CFG;
    /* Clear PPRE1[2:0] bits */
    tmpregister &= CFG_APB1PRES_RESET_MASK;
    /* Set PPRE1[2:0] bits according to RCC_HCLK value */
    tmpregister |= RCC_HCLK;
    /* Store the new value */
    RCC->CFG = tmpregister;
}

/**
 * @brief  Configures the High Speed APB clock (PCLK2).
 * @param RCC_HCLK defines the APB2 clock divider. This clock is derived from
 *   the AHB clock (HCLK).
 *   This parameter can be one of the following values:
 *     @arg RCC_HCLK_DIV1 APB2 clock = HCLK
 *     @arg RCC_HCLK_DIV2 APB2 clock = HCLK/2
 *     @arg RCC_HCLK_DIV4 APB2 clock = HCLK/4
 *     @arg RCC_HCLK_DIV8 APB2 clock = HCLK/8
 *     @arg RCC_HCLK_DIV16 APB2 clock = HCLK/16
 */
void RCC_ConfigPclk2(uint32_t RCC_HCLK)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_RCC_HCLK_DIV(RCC_HCLK));
    tmpregister = RCC->CFG;
    /* Clear PPRE2[2:0] bits */
    tmpregister &= CFG_APB2PRES_RESET_MASK;
    /* Set PPRE2[2:0] bits according to RCC_HCLK value */
    tmpregister |= RCC_HCLK << 3;
    /* Store the new value */
    RCC->CFG = tmpregister;
}

/**
 * @brief  Enables or disables the specified RCC interrupts.
 * @param RccInt specifies the RCC interrupt sources to be enabled or disabled.
 *
 *   this parameter can be any combination of the following values
 *     @arg RCC_INT_LSIRDIF LSI ready interrupt
 *     @arg RCC_INT_LSERDIF LSE ready interrupt
 *     @arg RCC_INT_HSIRDIF HSI ready interrupt
 *     @arg RCC_INT_HSERDIF HSE ready interrupt
 *     @arg RCC_INT_PLLRDIF PLL ready interrupt
 *     @arg RCC_INT_BORIF   BOR interrupt
 *     @arg RCC_INT_MSIRDIF MSI ready interrupt
 *
 * @param Cmd new state of the specified RCC interrupts.
 *   This parameter can be: ENABLE or DISABLE.
 */
void RCC_ConfigInt(uint8_t RccInt, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_RCC_INT(RccInt));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Perform Byte access to RCC_CLKINT bits to enable the selected interrupts */
        *(__IO uint32_t*)CLKINT_ADDR |= (((uint32_t)RccInt) << 8);
    }
    else
    {
        /* Perform Byte access to RCC_CLKINT bits to disable the selected interrupts */
        *(__IO uint32_t*)CLKINT_ADDR &= (~(((uint32_t)RccInt) << 8));
    }
}

/**
 * @brief  Configures the USB clock (USBCLK).
 * @param RCC_USBCLKSource specifies the USB clock source. This clock is
 *   derived from the PLL output.
 *   This parameter can be one of the following values:
 *     @arg RCC_USBCLK_SRC_PLLCLK_DIV1_5 PLL clock divided by 1,5 selected as USB clock source
 *     @arg RCC_USBCLK_SRC_PLLCLK_DIV1   PLL clock divided by 1 selected as USB clock source
 *     @arg RCC_USBCLK_SRC_PLLCLK_DIV2   PLL clock divided by 2 selected as USB clock source
 *     @arg RCC_USBCLK_SRC_PLLCLK_DIV3   PLL clock divided by 3 selected as USB clock source
 */
void RCC_ConfigUsbClk(uint32_t RCC_USBCLKSource)
{
    /* Check the parameters */
    assert_param(IS_RCC_USBCLK_SRC(RCC_USBCLKSource));

    *(__IO uint32_t*)CFG_USBPRES_BB      = RCC_USBCLKSource;
    *(__IO uint32_t*)CFGR_USBPRE_BB_BIT1 = RCC_USBCLKSource >> 1;
}

/**
 * @brief  Configures the TIM1/8 clock (TIM1/8CLK).
 * @param RCC_TIM18CLKSource specifies the TIM1/8 clock source.
 *   This parameter can be one of the following values:
 *     @arg RCC_TIM18CLK_SRC_TIM18CLK
 *     @arg RCC_TIM18CLK_SRC_SYSCLK
 */
void RCC_ConfigTim18Clk(uint32_t RCC_TIM18CLKSource)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_RCC_TIM18CLKSRC(RCC_TIM18CLKSource));

    tmpregister = RCC->CFG2;
    /* Clear TIMCLK_SEL bits */
    tmpregister &= CFG2_TIM18CLKSEL_RESET_MASK;
    /* Set TIMCLK_SEL bits according to RCC_TIM18CLKSource value */
    tmpregister |= RCC_TIM18CLKSource;

    /* Store the new value */
    RCC->CFG2 = tmpregister;
}

/**
 * @brief  Configures the RNGCCLK prescaler.
 * @param RCC_RNGCCLKPrescaler specifies the RNGCCLK prescaler.
 *   This parameter can be one of the following values:
 *     @arg RCC_RNGCCLK_SYSCLK_DIV1 RNGCPRE[24:28] = 00000, SYSCLK Divided By 1
 *     @arg RCC_RNGCCLK_SYSCLK_DIV2 RNGCPRE[24:28] = 00001, SYSCLK Divided By 2
 *     @arg RCC_RNGCCLK_SYSCLK_DIV3 RNGCPRE[24:28] = 00002, SYSCLK Divided By 3
 *               ...
 *     @arg RCC_RNGCCLK_SYSCLK_DIV31 RNGCPRE[24:28] = 11110, SYSCLK Divided By 31
 *     @arg RCC_RNGCCLK_SYSCLK_DIV32 RNGCPRE[24:28] = 11111, SYSCLK Divided By 32
 */
void RCC_ConfigRngcClk(uint32_t RCC_RNGCCLKPrescaler)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_RCC_RNGCCLKPRE(RCC_RNGCCLKPrescaler));

    tmpregister = RCC->CFG2;
    /* Clear RNGCPRE[3:0] bits */
    tmpregister &= CFG2_RNGCPRES_RESET_MASK;
    /* Set RNGCPRE[3:0] bits according to RCC_RNGCCLKPrescaler value */
    tmpregister |= RCC_RNGCCLKPrescaler;

    /* Store the new value */
    RCC->CFG2 = tmpregister;
}

/**
 * @brief  Configures the ADCx 1M clock (ADC1MCLK).
 * @param RCC_ADC1MCLKSource specifies the ADC1M clock source.
 *   This parameter can be on of the following values:
 *     @arg RCC_ADC1MCLK_SRC_HSI
 *     @arg RCC_ADC1MCLK_SRC_HSE
 *
 * @param RCC_ADC1MPrescaler specifies the ADC1M clock prescaler.
 *   This parameter can be on of the following values:
 *     @arg RCC_ADC1MCLK_DIV1 ADC1M clock = RCC_ADC1MCLKSource_xxx/1
 *     @arg RCC_ADC1MCLK_DIV2 ADC1M clock = RCC_ADC1MCLKSource_xxx/2
 *     @arg RCC_ADC1MCLK_DIV3 ADC1M clock = RCC_ADC1MCLKSource_xxx/3
 *               ...
 *     @arg RCC_ADC1MCLK_DIV31 ADC1M clock = RCC_ADC1MCLKSource_xxx/31
 *     @arg RCC_ADC1MCLK_DIV32 ADC1M clock = RCC_ADC1MCLKSource_xxx/32
 */
void RCC_ConfigAdc1mClk(uint32_t RCC_ADC1MCLKSource, uint32_t RCC_ADC1MPrescaler)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_RCC_ADC1MCLKSRC(RCC_ADC1MCLKSource));
    assert_param(IS_RCC_ADC1MCLKPRE(RCC_ADC1MPrescaler));

    tmpregister = RCC->CFG2;
    /* Clear ADC1MSEL and ADC1MPRE[4:0] bits */
    tmpregister &= CFG2_ADC1MSEL_RESET_MASK;
    tmpregister &= CFG2_ADC1MPRES_RESET_MASK;
    /* Set ADC1MSEL bits according to RCC_ADC1MCLKSource value */
    tmpregister |= RCC_ADC1MCLKSource;
    /* Set ADC1MPRE[4:0] bits according to RCC_ADC1MPrescaler value */
    tmpregister |= RCC_ADC1MPrescaler;

    /* Store the new value */
    RCC->CFG2 = tmpregister;
}

/**
 * @brief  Configures the ADCPLLCLK prescaler, and enable/disable ADCPLLCLK.
 * @param RCC_ADCPLLCLKPrescaler specifies the ADCPLLCLK prescaler.
 *   This parameter can be on of the following values:
 *     @arg RCC_ADCPLLCLK_DIV1 ADCPLLCLKPRES[4:0] = 10000, Pll Clock Divided By 1
 *     @arg RCC_ADCPLLCLK_DIV2 ADCPLLCLKPRES[4:0] = 10001, Pll Clock Divided By 2
 *     @arg RCC_ADCPLLCLK_DIV4 ADCPLLCLKPRES[4:0] = 10010, Pll Clock Divided By 4
 *     @arg RCC_ADCPLLCLK_DIV6 ADCPLLCLKPRES[4:0] = 10011, Pll Clock Divided By 6
 *     @arg RCC_ADCPLLCLK_DIV8 ADCPLLCLKPRES[4:0] = 10100, Pll Clock Divided By 8
 *     @arg RCC_ADCPLLCLK_DIV10 ADCPLLCLKPRES[4:0] = 10101, Pll Clock Divided By 10
 *     @arg RCC_ADCPLLCLK_DIV12 ADCPLLCLKPRES[4:0] = 10110, Pll Clock Divided By 12
 *     @arg RCC_ADCPLLCLK_DIV16 ADCPLLCLKPRES[4:0] = 10111, Pll Clock Divided By 16
 *     @arg RCC_ADCPLLCLK_DIV32 ADCPLLCLKPRES[4:0] = 11000, Pll Clock Divided By 32
 *     @arg RCC_ADCPLLCLK_DIV64 ADCPLLCLKPRES[4:0] = 11001, Pll Clock Divided By 64
 *     @arg RCC_ADCPLLCLK_DIV128 ADCPLLCLKPRES[4:0] = 11010, Pll Clock Divided By 128
 *     @arg RCC_ADCPLLCLK_DIV256 ADCPLLCLKPRES[4:0] = 11011, Pll Clock Divided By 256
 *     @arg RCC_ADCPLLCLK_DIV256 ADCPLLCLKPRES[4:0] = others, Pll Clock Divided By 256
 *
 * @param Cmd specifies the ADCPLLCLK enable/disable selection.
 *   This parameter can be on of the following values:
 *     @arg ENABLE enable ADCPLLCLK
 *     @arg DISABLE disable ADCPLLCLK ADCPLLCLKPRES[4:0] = 0xxxx, ADC Pll Clock Disable
 */
void RCC_ConfigAdcPllClk(uint32_t RCC_ADCPLLCLKPrescaler, FunctionalState Cmd)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_RCC_ADCPLLCLKPRE(RCC_ADCPLLCLKPrescaler));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    tmpregister = RCC->CFG2;
    /* Clear ADCPLLPRES[4:0] bits */
    tmpregister &= CFG2_ADCPLLPRES_RESET_MASK;

    if (Cmd != DISABLE)
    {
        tmpregister |= RCC_ADCPLLCLKPrescaler;
    }
    else
    {
        tmpregister |= RCC_ADCPLLCLKPrescaler;
        tmpregister &= RCC_ADCPLLCLK_DISABLE;
    }

    /* Store the new value */
    RCC->CFG2 = tmpregister;
}

/**
 * @brief  Configures the ADCHCLK prescaler.
 * @param RCC_ADCHCLKPrescaler specifies the ADCHCLK prescaler.
 *   This parameter can be on of the following values:
 *     @arg RCC_ADCHCLK_DIV1 ADCHCLKPRE[3:0] = 0000, HCLK Clock Divided By 1
 *     @arg RCC_ADCHCLK_DIV2 ADCHCLKPRE[3:0] = 0001, HCLK Clock Divided By 2
 *     @arg RCC_ADCHCLK_DIV4 ADCHCLKPRE[3:0] = 0010, HCLK Clock Divided By 4
 *     @arg RCC_ADCHCLK_DIV6 ADCHCLKPRE[3:0] = 0011, HCLK Clock Divided By 6
 *     @arg RCC_ADCHCLK_DIV8 ADCHCLKPRE[3:0] = 0100, HCLK Clock Divided By 8
 *     @arg RCC_ADCHCLK_DIV10 ADCHCLKPRE[3:0] = 0101, HCLK Clock Divided By 10
 *     @arg RCC_ADCHCLK_DIV12 ADCHCLKPRE[3:0] = 0110, HCLK Clock Divided By 12
 *     @arg RCC_ADCHCLK_DIV16 ADCHCLKPRE[3:0] = 0111, HCLK Clock Divided By 16
 *     @arg RCC_ADCHCLK_DIV32 ADCHCLKPRE[3:0] = 1000, HCLK Clock Divided By 32
 *     @arg RCC_ADCHCLK_DIV_OTHERS ADCHCLKPRE[3:0] = others, HCLK Clock Divided By 32
 */
void RCC_ConfigAdcHclk(uint32_t RCC_ADCHCLKPrescaler)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_RCC_ADCHCLKPRE(RCC_ADCHCLKPrescaler));

    tmpregister = RCC->CFG2;
    /* Clear ADCHPRE[3:0] bits */
    tmpregister &= CFG2_ADCHPRES_RESET_MASK;
    /* Set ADCHPRE[3:0] bits according to RCC_ADCHCLKPrescaler value */
    tmpregister |= RCC_ADCHCLKPrescaler;

    /* Store the new value */
    RCC->CFG2 = tmpregister;
}

/**
 * @brief  Configures the TRNG 1M clock (TRNG1MCLK).
 * @param RCC_TRNG1MCLKSource specifies the TRNG1M clock source.
 *   This parameter can be on of the following values:
 *     @arg RCC_TRNG1MCLK_SRC_HSI
 *     @arg RCC_TRNG1MCLK_SRC_HSE
 *
 * @param RCC_TRNG1MPrescaler specifies the TRNG1M prescaler.
 *   This parameter can be on of the following values:
 *     @arg RCC_TRNG1MCLK_DIV2 TRNG1M clock = RCC_TRNG1MCLK_SRC_HSE/2
 *     @arg RCC_TRNG1MCLK_DIV4 TRNG1M clock = RCC_TRNG1MCLKSource_xxx/4
 *     @arg RCC_TRNG1MCLK_DIV6 TRNG1M clock = RCC_TRNG1MCLKSource_xxx/6
 *               ...
 *     @arg RCC_TRNG1MCLK_DIV60 TRNG1M clock = RCC_TRNG1MCLKSource_xxx/60
 *     @arg RCC_TRNG1MCLK_DIV62 TRNG1M clock = RCC_TRNG1MCLKSource_xxx/62
 */
void RCC_ConfigTrng1mClk(uint32_t RCC_TRNG1MCLKSource, uint32_t RCC_TRNG1MPrescaler)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_RCC_TRNG1MCLK_SRC(RCC_TRNG1MCLKSource));
    assert_param(IS_RCC_TRNG1MCLKPRE(RCC_TRNG1MPrescaler));

    tmpregister = RCC->CFG3;
    /* Clear TRNG1MSEL and TRNG1MPRE[4:0] bits */
    tmpregister &= CFGR3_TRNG1MSEL_RESET_MASK;
    tmpregister &= CFGR3_TRNG1MPRES_RESET_MASK;
    /* Set TRNG1MSEL bits according to RCC_TRNG1MCLKSource value */
    tmpregister |= RCC_TRNG1MCLKSource;
    /* Set TRNG1MPRE[4:0] bits according to RCC_TRNG1MPrescaler value */
    tmpregister |= RCC_TRNG1MPrescaler;

    /* Store the new value */
    RCC->CFG3 = tmpregister;
}

/**
 * @brief  Enable/disable TRNG clock (TRNGCLK).
 * @param Cmd specifies the TRNGCLK enable/disable selection.
 *   This parameter can be on of the following values:
 *     @arg ENABLE enable TRNGCLK
 *     @arg DISABLE disable TRNGCLK
 */
void RCC_EnableTrng1mClk(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        RCC->CFG3 |= RCC_TRNG1MCLK_ENABLE;
    }
    else
    {
        RCC->CFG3 &= RCC_TRNG1MCLK_DISABLE;
    }
}

/**
 * @brief  Configures the UCDR clock.
 * @param RCC_UCDR300MSource specifies the UCDR clock source.
 *   This parameter can be on of the following values:
 *     @arg RCC_UCDR300M_SRC_OSC300M
 *     @arg RCC_UCDR300M_SRC_PLLVCO
 *
 * @param Cmd enable/disable selection.
 *   This parameter can be on of the following values:
 *     @arg ENABLE enable UCDR
 *     @arg DISABLE disable UCDR
 */
void RCC_ConfigUCDRClk(uint32_t RCC_UCDR300MSource, FunctionalState Cmd)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_RCC_UCDR300M_SRC(RCC_UCDR300MSource));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    tmpregister = RCC->CFG3;
    /* Clear UCDR300MSEL bits */
    tmpregister &= RCC_UCDR300MSource_MASK;
    /* Set UCDR300MSEL bits */
    tmpregister |= RCC_UCDR300MSource;

    /* Store the new value */
    RCC->CFG3 = tmpregister;

    if (Cmd != DISABLE)
    {
        RCC->CFG3 |= RCC_UCDR_ENABLE;
    }
    else
    {
        RCC->CFG3 &= RCC_UCDR_DISABLE;
    }
}

/**
 * @brief  Configures the USB Crystal Mode.
 * @param RCC_USBXTALESSMode specifies the USB Crystal Mode.
 *   This parameter can be one of the following values:
 *     @arg RCC_USBXTALESS_MODE     USB work in crystal mode
 *     @arg RCC_USBXTALESS_LESSMODE USB work in crystalless mode
 */
void RCC_ConfigUSBXTALESSMode(uint32_t RCC_USBXTALESSMode)
{
    /* Check the parameters */
    assert_param(IS_RCC_USBXTALESS_MODE(RCC_USBXTALESSMode));

    /* Clear the USB Crystal Mode bit */
    RCC->CFG3 &= RCC_USBXTALESSMode_MASK;

    /* Select the USB Crystal Mode */
    RCC->CFG3 |= RCC_USBXTALESSMode;
}

/**
 * @brief  Enables or disables the RET peripheral clock.
 * @param RCC_RETPeriph specifies the RET peripheral to gates its clock.
 *
 *   this parameter can be any combination of the following values:
 *     @arg RCC_RET_PERIPH_LPTIM
 *     @arg RCC_RET_PERIPH_LPUART
 *     @arg RCC_RET_PERIPH_LCD
 *
 * @param Cmd new state of the specified peripheral clock.
 *   This parameter can be: ENABLE or DISABLE.
 */
void RCC_EnableRETPeriphClk(uint32_t RCC_RETPeriph, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_RCC_RET_PERIPH(RCC_RETPeriph));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        RCC->RDCTRL |= RCC_RETPeriph;
    }
    else
    {
        RCC->RDCTRL &= ~RCC_RETPeriph;
    }
}

/**
 * @brief Forces or releases RET peripheral reset.
 * @param RCC_RETPeriph specifies the RET peripheral to reset.
 *   This parameter can be any combination of the following values:
 *     @arg   RCC_RET_PERIPH_LPTIM.
 *            RCC_RET_PERIPH_LPUART.
 *            RCC_RET_PERIPH_LCD.
 * @param Cmd new state of the specified peripheral reset. This parameter can be ENABLE or DISABLE.
 */
void RCC_EnableRETPeriphReset(uint32_t RCC_RETPeriph, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_RCC_RET_PERIPH(RCC_RETPeriph));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        RCC->RDCTRL |= (RCC_RETPeriph << 4);
    }
    else
    {
        RCC->RDCTRL &= ~(RCC_RETPeriph << 4);
    }
}

/**
 * @brief  Configures the LPTIM clock (LPTIMCLK).
 * @param RCC_LPTIMCLKSource specifies the LPTIM clock source.
 *   This parameter can be one of the following values:
 *     @arg RCC_LPTIMCLK_SRC_APB1  APB1 clock selected as LPTIM clock
 *     @arg RCC_LPTIMCLK_SRC_LSI   LSI selected as LPTIM clock
 *     @arg RCC_LPTIMCLK_SRC_HSI   HSI selected as LPTIM clock
 *     @arg RCC_LPTIMCLK_SRC_LSE   LSE selected as LPTIM clock
 *     @arg RCC_LPTIMCLK_SRC_COMP1 COMP1 output selected as LPTIM clock
 *     @arg RCC_LPTIMCLK_SRC_COMP2 COMP2 output selected as LPTIM clock
 * @note When switching from comparator1/2 to other clock sources,
 *       it is suggested to disable comparators first.
 */
void RCC_ConfigLPTIMClk(uint32_t RCC_LPTIMCLKSource)
{
    /* Check the parameters */
    assert_param(IS_RCC_LPTIM_CLK(RCC_LPTIMCLKSource));
    //PWR DBP set 1
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
    PWR->CTRL1 |=  0x100;
    /* Clear the LPTIM clock source */
    RCC->RDCTRL &= RCC_LPTIMCLK_SRC_MASK;

    /* Select the LPTIM clock source */
    RCC->RDCTRL |= RCC_LPTIMCLKSource;
}

/**
 * @brief  Returns the clock source used as LPTIM clock (LPTIMCLK).
 * @return The clock source used as system clock. The returned value can
 *   be one of the following:
 *     - RCC_LPTIMCLK_SRC_APB1  APB1 clock selected as LPTIM clock
 *     - RCC_LPTIMCLK_SRC_LSI   LSI selected as LPTIM clock
 *     - RCC_LPTIMCLK_SRC_HSI   HSI selected as LPTIM clock
 *     - RCC_LPTIMCLK_SRC_LSE   LSE selected as LPTIM clock
 *     - RCC_LPTIMCLK_SRC_COMP1 COMP1 output selected as LPTIM clock
 *     - RCC_LPTIMCLK_SRC_COMP2 COMP2 output selected as LPTIM clock
 */
uint32_t RCC_GetLPTIMClkSrc(void)
{
    return ((uint32_t)(RCC->RDCTRL & RDCTRL_LPTIMCLKSEL_MASK));
}

/**
 * @brief  Configures the LPUART clock (LPUARTCLK).
 * @param RCC_LPUARTCLKSource specifies the LPUART clock source.
 *   This parameter can be one of the following values:
 *     @arg RCC_LPUARTCLK_SRC_APB1   APB1 clock selected as LPTIM clock
 *     @arg RCC_LPUARTCLK_SRC_SYSCLK SYSCLK selected as LPTIM clock
 *     @arg RCC_LPUARTCLK_SRC_HSI    HSI selected as LPTIM clock
 *     @arg RCC_LPUARTCLK_SRC_LSE    LSE selected as LPTIM clock
 */
void RCC_ConfigLPUARTClk(uint32_t RCC_LPUARTCLKSource)
{
    /* Check the parameters */
    assert_param(IS_RCC_LPUART_CLK(RCC_LPUARTCLKSource));

    /* Clear the LPUART clock source */
    RCC->RDCTRL &= RCC_LPUARTCLK_SRC_MASK;

    /* Select the LPTIM clock source */
    RCC->RDCTRL |= RCC_LPUARTCLKSource;
}

/**
 * @brief  Returns the clock source used as LPUART clock.
 * @return The clock source used as system clock. The returned value can
 *   be one of the following:
 *     - RCC_RDCTRL_LPUARTSEL_APB1:   APB1 used as LPUART clock
 *     - RCC_RDCTRL_LPUARTSEL_SYSCLK: SYSCLK used as LPUART clock
 *     - RCC_RDCTRL_LPUARTSEL_HSI:    HSI used as LPUART clock
 *     - RCC_RDCTRL_LPUARTSEL_LSE:    LSE used as LPUART clock
 */
uint32_t RCC_GetLPUARTClkSrc(void)
{
    return ((uint32_t)(RCC->RDCTRL & RDCTRL_LPUARTCLKSEL_MASK));
}

/**
 * @brief  Enables or disables the specified SRAM1/2 parity error interrupts.
 * @param SramErrorInt specifies the SRAM1/2 interrupt sources to be enabled or disabled.
 *
 *   this parameter can be any combination of the following values
 *     @arg SRAM1_PARITYERROR_INT SRAM1 parity interrupt
 *     @arg SRAM2_PARITYERROR_INT SRAM2 parity interrupt
 *
 * @param Cmd new state of the specified SRAM1/2 parity error interrupts.
 *   This parameter can be: ENABLE or DISABLE.
 */
void RCC_ConfigSRAMParityErrorInt(uint32_t SramErrorInt, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_RCC_SRAMERRORINT(SramErrorInt));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Set ERR1EN/ERR2EN bit to enable the selected parity error interrupts */
        RCC->SRAM_CTRLSTS |= SramErrorInt;
    }
    else
    {
        /* Clear ERR1EN/ERR2EN bit to disable the selected parity error interrupts */
        RCC->SRAM_CTRLSTS &= (~SramErrorInt);
    }
}

/**
 * @brief  Enables or disables the specified SRAM1/2 parity error reset.
 * @param SramErrorReset specifies the SRAM1/2 parity error reset to be enabled or disabled.
 *
 *   this parameter can be any combination of the following values
 *     @arg SRAM1_PARITYERROR_RESET SRAM1 parity error reset
 *     @arg SRAM2_PARITYERROR_RESET SRAM2 parity error reset
 *
 * @param Cmd new state of the specified SRAM1/2 parity error reset.
 *   This parameter can be: ENABLE or DISABLE.
 */
void RCC_ConfigSRAMParityErrorRESET(uint32_t SramErrorReset, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_RCC_SRAMERRORRESET(SramErrorReset));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Set ERR1EN/ERR2EN bit to enable SRAM1/2 parity error reset */
        RCC->SRAM_CTRLSTS |= SramErrorReset;
    }
    else
    {
        /* Clear ERR1EN/ERR2EN bit to disable SRAM1/2 parity error reset */
        RCC->SRAM_CTRLSTS &= (~SramErrorReset);
    }
}

/**
 * @brief Clears the specified SRAM1/2 parity error flag.
 * @param SramErrorReset specifies the SRAM1/2 parity error flag.
 *
 *   this parameter can be any combination of the following values
 *     @arg SRAM1_PARITYERROR_FLAG SRAM1 parity error flag
 *     @arg SRAM2_PARITYERROR_FLAG SRAM2 parity error flag
 */
void RCC_ClrSRAMParityErrorFlag(uint32_t SramErrorflag)
{
    /* Check the parameters */
    assert_param(IS_RCC_SRAMERRORFLAG(SramErrorflag));
    RCC->SRAM_CTRLSTS |= SramErrorflag;
}

/**
 * @brief  Configures the External Low Speed oscillator (LSE) Xtal bias.
 * @param LSE_Trim specifies LSE Driver Trim Level.
 *        Trim value rang 0x0~0x1FF
 */
void LSE_XtalConfig(uint16_t LSE_Trim)
{
    uint32_t tmpregister = 0;
    tmpregister = *(__IO uint32_t*)LSE_TRIMR_ADDR;
    //clear lse trim[8:0]
    tmpregister &= (~(LSE_GM_MASK_VALUE));
    (LSE_Trim>LSE_GM_MAX_VALUE) ? (LSE_Trim=LSE_GM_DEFAULT_VALUE):(LSE_Trim&=LSE_GM_MASK_VALUE);
    tmpregister |= LSE_Trim;
    *(__IO uint32_t*)LSE_TRIMR_ADDR = tmpregister;
}

/**
 * @brief  Configures the External Low Speed oscillator (LSE).
 * @param RCC_LSE specifies the new state of the LSE.
 *   This parameter can be one of the following values:
 *     @arg RCC_LSE_DISABLE LSE oscillator OFF
 *     @arg RCC_LSE_ENABLE LSE oscillator ON
 *     @arg RCC_LSE_BYPASS LSE oscillator bypassed with external clock
 * @param LSE_Trim specifies LSE Driver Trim Level.
 *        Trim value rang 0x00~0x1FF
 */
void RCC_ConfigLse(uint8_t RCC_LSE,uint16_t LSE_Trim)
{
    //PWR DBP set 1
    /* Enable PWR Clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
    PWR->CTRL1 |=  0x100;
    /* Check the parameters */
    assert_param(IS_RCC_LSE(RCC_LSE));
    /* Reset LSEEN LSEBYP and LSECLKSSEN bits before configuring the LSE ------------------*/
    *(__IO uint32_t*)LDCTRL_ADDR &= (~(RCC_LDCTRL_LSEEN | RCC_LDCTRL_LSEBP | RCC_LDCTRL_LSECLKSSEN));
    /* Configure LSE (RCC_LSE_DISABLE is already covered by the code section above) */
    switch (RCC_LSE)
    {
    case RCC_LSE_ENABLE:
        /* Set LSEON bit */
        *(__IO uint32_t*)LDCTRL_ADDR |= RCC_LSE_ENABLE;
        LSE_XtalConfig(LSE_Trim);
        break;
    case RCC_LSE_BYPASS:
        /* Set LSEBYP and LSEON bits */
        *(__IO uint32_t*)LDCTRL_ADDR |= (RCC_LSE_BYPASS | RCC_LSE_ENABLE);
        break;

    default:
        break;
    }
}

/**
 * @brief  Enables or disables the Internal Low Speed oscillator (LSI).
 * @note   LSI can not be disabled if the IWDG is running.
 * @param Cmd new state of the LSI. This parameter can be: ENABLE or DISABLE.
 */
void RCC_EnableLsi(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    *(__IO uint32_t*)CTRLSTS_LSIEN_BB = (uint32_t)Cmd;
}

/**
 * @brief  Configures the RTC clock (RTCCLK).
 * @note   Once the RTC clock is selected it can't be changed unless the LowPower domain is reset.
 * @param RCC_RTCCLKSource specifies the RTC clock source.
 *   This parameter can be one of the following values:
 *     @arg RCC_RTCCLK_SRC_NONE:      No clock selected as RTC clock
 *     @arg RCC_RTCCLK_SRC_LSE:       LSE selected as RTC clock
 *     @arg RCC_RTCCLK_SRC_LSI:       LSI selected as RTC clock
 *     @arg RCC_RTCCLK_SRC_HSE_DIV32: HSE clock divided by 32 selected as RTC clock
 */
void RCC_ConfigRtcClk(uint32_t RCC_RTCCLKSource)
{
    /* Check the parameters */
    assert_param(IS_RCC_RTCCLK_SRC(RCC_RTCCLKSource));

    /* Clear the RTC clock source */
    RCC->LDCTRL &= (~RCC_LDCTRL_RTCSEL);

    /* Select the RTC clock source */
    RCC->LDCTRL |= RCC_RTCCLKSource;
}

/**
 * @brief  Returns the clock source used as RTC clock (RTCCLK).
 * @return The clock source used as system clock. The returned value can
 *   be one of the following:
 *     - RCC_RTCCLK_SRC_NONE:      No clock used as RTC clock (RTCCLK)
 *     - RCC_RTCCLK_SRC_LSE:       LSE used as RTC clock (RTCCLK)
 *     - RCC_RTCCLK_SRC_LSI:       LSI used as RTC clock (RTCCLK)
 *     - RCC_RTCCLK_SRC_HSE_DIV32: HSE clock divided by 32 used as RTC clock (RTCCLK)
 */
uint32_t RCC_GetRTCClkSrc(void)
{
    return ((uint32_t)(RCC->LDCTRL & RCC_LDCTRL_RTCSEL));
}

/**
 * @brief  Enables or disables the RTC clock.
 * @note   This function must be used only after the RTC clock was selected using the RCC_ConfigRtcClk function.
 * @param Cmd new state of the RTC clock. This parameter can be: ENABLE or DISABLE.
 */
void RCC_EnableRtcClk(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    *(__IO uint32_t*)LDCTRL_RTCEN_BB = (uint32_t)Cmd;
}

/**
 * @brief  Configures the LSX clock (for TSC).
 * @note   Once the LSX clock is selected it can't be changed unless the LowPower domain is reset.
 * @param RCC_RTCCLKSource specifies the RTC clock source.
 *   This parameter can be one of the following values:
 *     @arg RCC_LSXCLK_SRC_LSI LSI selected as RTC clock
 *     @arg RCC_LSXCLK_SRC_LSE LSE selected as RTC clock
 */
void RCC_ConfigLSXClk(uint32_t RCC_LSXCLKSource)
{
    /* Check the parameters */
    assert_param(IS_RCC_LSXCLK_SRC(RCC_LSXCLKSource));

    /* Clear the LSX clock source */
    RCC->LDCTRL &= (~RCC_LDCTRL_LSXSEL);

    /* Select the LSX clock source */
    RCC->LDCTRL |= RCC_LSXCLKSource;
}

/**
 * @brief  Returns the clock source used as LSX clock (for TSC).
 * @return The clock source used as system clock. The returned value can
 *   be one of the following:
 *     - RCC_LSXCLK_SRC_LSI: LSI used as LSX clock (for TSC)
 *     - RCC_LSXCLK_SRC_LSE: LSE used as LSX clock (for TSC)
 */
uint32_t RCC_GetLSXClkSrc(void)
{
    return ((uint32_t)(RCC->LDCTRL & RCC_LDCTRL_LSXSEL));
}

/**
 * @brief  Returns the frequencies of different on chip clocks.
 * @param RCC_Clocks pointer to a RCC_ClocksType structure which will hold
 *         the clocks frequencies.
 * @note   The result of this function could be not correct when using
 *         fractional value for HSE crystal.
 */
void RCC_GetClocksFreqValue(RCC_ClocksType* RCC_Clocks)
{
    uint32_t tmp = 0, pllclk = 0, pllmull = 0, pllsource = 0, presc = 0;
    uint8_t msi_clk = 0;

    /* Get PLL clock source and multiplication factor ----------------------*/
    pllmull   = RCC->CFG & CFG_PLLMULFCT_MASK;
    pllsource = RCC->CFG & CFG_PLLSRC_MASK;
    /* Get MSI clock --------------------------------------------------------*/
    msi_clk = (uint8_t) ((RCC->CTRLSTS & RCC_CTRLSTS_MSIRANGE)>>4);

    if ((pllmull & RCC_CFG_PLLMULFCT_4) == 0)
    {
        pllmull = (pllmull >> 18) + 2; // PLLMUL[4]=0
    }
    else
    {
        pllmull = ((pllmull >> 18) - 496) + 1; // PLLMUL[4]=1
    }

    if (pllsource == 0x00)
    {
        /* HSI selected as PLL clock entry */
        if ((RCC->PLLHSIPRE & PLLHSIPRE_PLLHSI_PRE_MASK) != (uint32_t)RESET)
        { /* HSI oscillator clock divided by 2 */
            pllclk = (HSI_VALUE >> 1) * pllmull;
        }
        else
        {
            pllclk = HSI_VALUE * pllmull;
        }

    }
    else
    {
        /* HSE selected as PLL clock entry */
        if ((RCC->CFG & CFG_PLLHSEPRES_MASK) != (uint32_t)RESET)
        { /* HSE oscillator clock divided by 2 */
            pllclk = (HSE_VALUE >> 1) * pllmull;
        }
        else
        {
            pllclk = HSE_VALUE * pllmull;
        }
    }

    /* PLL Div clock */
    if ((RCC->PLLHSIPRE & PLLHSIPRE_PLLSRCDIV_MASK) != (uint32_t)RESET)
    { /* PLL clock divided by 2 */
        pllclk = (pllclk >> 1);
    }

    /* Get SYSCLK source -------------------------------------------------------*/
    tmp = RCC->CFG & CFG_SCLKSTS_MASK;

    switch (tmp)
    {
    case 0x00: /* MSI used as system clock */
        RCC_Clocks->SysclkFreq = s_msiClockTable[msi_clk];
        break;
    case 0x04: /* HSI used as system clock */
        RCC_Clocks->SysclkFreq = HSI_VALUE;
        break;
    case 0x08: /* HSE used as system clock */
        RCC_Clocks->SysclkFreq = HSE_VALUE;
        break;
    case 0x0C: /* PLL used as system clock */
        RCC_Clocks->SysclkFreq = pllclk;
        break;

    default:
        RCC_Clocks->SysclkFreq = s_msiClockTable[msi_clk];
        break;
    }

    /* Compute HCLK, PCLK1, PCLK2 and ADCCLK clocks frequencies ----------------*/
    /* Get HCLK prescaler */
    tmp   = RCC->CFG & CFG_AHBPRES_SET_MASK;
    tmp   = tmp >> 4;
    presc = s_ApbAhbPresTable[tmp];
    /* HCLK clock frequency */
    RCC_Clocks->HclkFreq = RCC_Clocks->SysclkFreq >> presc;
    /* Get PCLK1 prescaler */
    tmp   = RCC->CFG & CFG_APB1PRES_SET_MASK;
    tmp   = tmp >> 8;
    presc = s_ApbAhbPresTable[tmp];
    /* PCLK1 clock frequency */
    RCC_Clocks->Pclk1Freq = RCC_Clocks->HclkFreq >> presc;
    /* Get PCLK2 prescaler */
    tmp   = RCC->CFG & CFG_APB2PRES_SET_MASK;
    tmp   = tmp >> 11;
    presc = s_ApbAhbPresTable[tmp];
    /* PCLK2 clock frequency */
    RCC_Clocks->Pclk2Freq = RCC_Clocks->HclkFreq >> presc;

    /* Get ADCHCLK prescaler */
    tmp   = RCC->CFG2 & CFG2_ADCHPRES_SET_MASK;
    presc = s_AdcHclkPresTable[tmp];
    /* ADCHCLK clock frequency */
    RCC_Clocks->AdcHclkFreq = RCC_Clocks->HclkFreq / presc;
    /* Get ADCPLLCLK prescaler */
    tmp   = RCC->CFG2 & CFG2_ADCPLLPRES_SET_MASK;
    tmp   = tmp >> 4;
    presc = s_AdcPllClkPresTable[(tmp & 0xF)]; // ignore BIT5
    /* ADCPLLCLK clock frequency */
    RCC_Clocks->AdcPllClkFreq = pllclk / presc;
}

/**
 * @brief  Enables or disables the AHB peripheral clock.
 * @param RCC_AHBPeriph specifies the AHB peripheral to gates its clock.
 *
 *   this parameter can be any combination of the following values:
 *     @arg RCC_AHB_PERIPH_DMA
 *     @arg RCC_AHB_PERIPH_SRAM
 *     @arg RCC_AHB_PERIPH_FLITF
 *     @arg RCC_AHB_PERIPH_CRC
 *     @arg RCC_AHB_PERIPH_RNGC
 *     @arg RCC_AHB_PERIPH_SAC
 *     @arg RCC_AHB_PERIPH_ADC
 *
 * @note SRAM and FLITF clock can be disabled only during sleep mode.
 * @param Cmd new state of the specified peripheral clock.
 *   This parameter can be: ENABLE or DISABLE.
 */
void RCC_EnableAHBPeriphClk(uint32_t RCC_AHBPeriph, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_RCC_AHB_PERIPH(RCC_AHBPeriph));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        RCC->AHBPCLKEN |= RCC_AHBPeriph;
    }
    else
    {
        RCC->AHBPCLKEN &= ~RCC_AHBPeriph;
    }
}

/**
 * @brief  Enables or disables the High Speed APB (APB2) peripheral clock.
 * @param RCC_APB2Periph specifies the APB2 peripheral to gates its clock.
 *   This parameter can be any combination of the following values:
 *     @arg RCC_APB2_PERIPH_AFIO, RCC_APB2_PERIPH_GPIOA, RCC_APB2_PERIPH_GPIOB,
 *          RCC_APB2_PERIPH_GPIOC, RCC_APB2_PERIPH_GPIOD, RCC_APB2_PERIPH_TIM1,
 *          RCC_APB2_PERIPH_SPI1, RCC_APB2_PERIPH_TIM8, RCC_APB2_PERIPH_USART1,
 *          RCC_APB2_PERIPH_UART4, RCC_APB2_PERIPH_UART5, RCC_APB2_PERIPH_SPI2
 * @param Cmd new state of the specified peripheral clock.
 *   This parameter can be: ENABLE or DISABLE.
 */
void RCC_EnableAPB2PeriphClk(uint32_t RCC_APB2Periph, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        RCC->APB2PCLKEN |= RCC_APB2Periph;
    }
    else
    {
        RCC->APB2PCLKEN &= ~RCC_APB2Periph;
    }
}

/**
 * @brief  Enables or disables the Low Speed APB (APB1) peripheral clock.
 * @param RCC_APB1Periph specifies the APB1 peripheral to gates its clock.
 *   This parameter can be any combination of the following values:
 *     @arg RCC_APB1_PERIPH_TIM2, RCC_APB1_PERIPH_TIM3, RCC_APB1_PERIPH_TIM4,
 *          RCC_APB1_PERIPH_TIM5, RCC_APB1_PERIPH_TIM6, RCC_APB1_PERIPH_TIM7,
 *          RCC_APB1_PERIPH_COMP, RCC_APB1_PERIPH_COMP_FILT, RCC_APB1_PERIPH_AFEC,
 *          RCC_APB1_PERIPH_TIM9, RCC_APB1_PERIPH_TSC, RCC_APB1_PERIPH_WWDG,
 *          RCC_APB1_PERIPH_USART2, RCC_APB1_PERIPH_USART3, RCC_APB1_PERIPH_I2C1,
 *          RCC_APB1_PERIPH_I2C2, RCC_APB1_PERIPH_USB, RCC_APB1_PERIPH_CAN,
 *          RCC_APB1_PERIPH_PWR, RCC_APB1_PERIPH_DAC, RCC_APB1_PERIPH_OPAMP
 *
 * @param Cmd new state of the specified peripheral clock.
 *   This parameter can be: ENABLE or DISABLE.
 */
void RCC_EnableAPB1PeriphClk(uint32_t RCC_APB1Periph, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        RCC->APB1PCLKEN |= RCC_APB1Periph;
    }
    else
    {
        RCC->APB1PCLKEN &= ~RCC_APB1Periph;
    }
}

/**
 * @brief Forces or releases AHB peripheral reset.
 * @param RCC_AHBPeriph specifies the AHB peripheral to reset.
 *   This parameter can be any combination of the following values:
 *     @arg   RCC_AHB_PERIPH_ADC.
 *            RCC_AHB_PERIPH_SAC.
 *            RCC_AHB_PERIPH_RNGC.
 * @param Cmd new state of the specified peripheral reset. This parameter can be ENABLE or DISABLE.
 */
void RCC_EnableAHBPeriphReset(uint32_t RCC_AHBPeriph, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_RCC_AHB_PERIPH(RCC_AHBPeriph));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        RCC->AHBPRST |= RCC_AHBPeriph;
    }
    else
    {
        RCC->AHBPRST &= ~RCC_AHBPeriph;
    }
}

/**
 * @brief  Forces or releases High Speed APB (APB2) peripheral reset.
 * @param RCC_APB2Periph specifies the APB2 peripheral to reset.
 *   This parameter can be any combination of the following values:
 *     @arg RCC_APB2_PERIPH_AFIO, RCC_APB2_PERIPH_GPIOA, RCC_APB2_PERIPH_GPIOB,
 *          RCC_APB2_PERIPH_GPIOC, RCC_APB2_PERIPH_GPIOD, RCC_APB2_PERIPH_TIM1,
 *          RCC_APB2_PERIPH_SPI1, RCC_APB2_PERIPH_TIM8, RCC_APB2_PERIPH_USART1,
 *          RCC_APB2_PERIPH_UART4, RCC_APB2_PERIPH_UART5, RCC_APB2_PERIPH_SPI2
 * @param Cmd new state of the specified peripheral reset.
 *   This parameter can be: ENABLE or DISABLE.
 */
void RCC_EnableAPB2PeriphReset(uint32_t RCC_APB2Periph, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        RCC->APB2PRST |= RCC_APB2Periph;
    }
    else
    {
        RCC->APB2PRST &= ~RCC_APB2Periph;
    }
}

/**
 * @brief  Forces or releases Low Speed APB (APB1) peripheral reset.
 * @param RCC_APB1Periph specifies the APB1 peripheral to reset.
 *   This parameter can be any combination of the following values:
 *     @arg RCC_APB1_PERIPH_TIM2, RCC_APB1_PERIPH_TIM3, RCC_APB1_PERIPH_TIM4,
 *          RCC_APB1_PERIPH_TIM5, RCC_APB1_PERIPH_TIM6, RCC_APB1_PERIPH_TIM7,
 *          RCC_APB1_PERIPH_COMP, RCC_APB1_PERIPH_COMP_FILT, RCC_APB1_PERIPH_AFEC,
 *          RCC_APB1_PERIPH_TIM9, RCC_APB1_PERIPH_TSC, RCC_APB1_PERIPH_WWDG,
 *          RCC_APB1_PERIPH_USART2, RCC_APB1_PERIPH_USART3, RCC_APB1_PERIPH_I2C1,
 *          RCC_APB1_PERIPH_I2C2, RCC_APB1_PERIPH_USB, RCC_APB1_PERIPH_CAN,
 *          RCC_APB1_PERIPH_PWR, RCC_APB1_PERIPH_DAC, RCC_APB1_PERIPH_OPAMP
 * @param Cmd new state of the specified peripheral clock.
 *   This parameter can be: ENABLE or DISABLE.
 */
void RCC_EnableAPB1PeriphReset(uint32_t RCC_APB1Periph, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        RCC->APB1PRST |= RCC_APB1Periph;
    }
    else
    {
        RCC->APB1PRST &= ~RCC_APB1Periph;
    }
}

/**
 * @brief  Forces or releases the LowPower domain reset.
 * @param Cmd new state of the Backup domain reset.
 *   This parameter can be: ENABLE or DISABLE.
 */
void RCC_EnableLowPowerReset(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    *(__IO uint32_t*)LDCTRL_LDSFTRST_BB = (uint32_t)Cmd;
}

/**
 * @brief  Enables or disables the Clock Security System.
 * @param Cmd new state of the Clock Security System..
 *   This parameter can be: ENABLE or DISABLE.
 */
void RCC_EnableClockSecuritySystem(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    *(__IO uint32_t*)CTRL_CLKSSEN_BB = (uint32_t)Cmd;
}

/**
 * @brief  Enables or disables the LSE Clock Security System.
 * @param Cmd new state of the LSE Clock Security System..
 *   This parameter can be: ENABLE or DISABLE.
 */
void RCC_EnableLSEClockSecuritySystem(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    *(__IO uint32_t*)LDCTRL_LSECLKSSEN_BB = (uint32_t)Cmd;
}

/**
 * @brief  Get LSE Clock Security System failure status.
 * @return LSE Clock Security System failure status (SET or RESET).
 */
FlagStatus RCC_GetLSEClockSecuritySystemStatus(void)
{
    FlagStatus bitstatus = RESET;
    /* Check the status of LSE Clock Security System */
    if ((RCC->LDCTRL & RCC_LDCTRL_LSECLKSSF) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    /* Return LSE Clock Security System status */
    return bitstatus;
}

/**
 * @brief  Configures the MCO PLL clock prescaler.
 * @param RCC_MCOPLLCLKPrescaler specifies the MCO PLL clock prescaler.
 *   This parameter can be on of the following values:
 *     @arg RCC_MCO_CLK_NUM0  MCOPRE[3:0] = 0000, PLL Clock Divided By 1,  Duty cycle = clock source
 *     @arg RCC_MCO_CLK_NUM1  MCOPRE[3:0] = 0001, PLL Clock Divided By 2,  Duty cycle = 1/((MCOPRE[3:0]+1)*2)
 *     @arg RCC_MCO_CLK_NUM2  MCOPRE[3:0] = 0010, PLL Clock Divided By 3,  Duty cycle = 1/((MCOPRE[3:0]+1)*2)
 *     @arg RCC_MCO_CLK_NUM3  MCOPRE[3:0] = 0011, PLL Clock Divided By 4,  Duty cycle = 1/((MCOPRE[3:0]+1)*2)
 *     @arg RCC_MCO_CLK_NUM4  MCOPRE[3:0] = 0100, PLL Clock Divided By 5,  Duty cycle = 1/((MCOPRE[3:0]+1)*2)
 *     @arg RCC_MCO_CLK_NUM5  MCOPRE[3:0] = 0101, PLL Clock Divided By 6,  Duty cycle = 1/((MCOPRE[3:0]+1)*2)
 *     @arg RCC_MCO_CLK_NUM6  MCOPRE[3:0] = 0110, PLL Clock Divided By 7,  Duty cycle = 1/((MCOPRE[3:0]+1)*2)
 *     @arg RCC_MCO_CLK_NUM7  MCOPRE[3:0] = 0111, PLL Clock Divided By 8,  Duty cycle = 1/((MCOPRE[3:0]+1)*2)
 *     @arg RCC_MCO_CLK_NUM8  MCOPRE[3:0] = 1000, PLL Clock Divided By 2,  Duty cycle = 50%
 *     @arg RCC_MCO_CLK_NUM9  MCOPRE[3:0] = 1001, PLL Clock Divided By 4,  Duty cycle = 50%
 *     @arg RCC_MCO_CLK_NUM10 MCOPRE[3:0] = 1010, PLL Clock Divided By 6,  Duty cycle = 50%
 *     @arg RCC_MCO_CLK_NUM11 MCOPRE[3:0] = 1011, PLL Clock Divided By 8,  Duty cycle = 50%
 *     @arg RCC_MCO_CLK_NUM12 MCOPRE[3:0] = 1100, PLL Clock Divided By 10, Duty cycle = 50%
 *     @arg RCC_MCO_CLK_NUM13 MCOPRE[3:0] = 1101, PLL Clock Divided By 12, Duty cycle = 50%
 *     @arg RCC_MCO_CLK_NUM14 MCOPRE[3:0] = 1110, PLL Clock Divided By 14, Duty cycle = 50%
 *     @arg RCC_MCO_CLK_NUM15 MCOPRE[3:0] = 1111, PLL Clock Divided By 16, Duty cycle = 50%
 */
void RCC_ConfigMcoClkPre(uint32_t RCC_MCOCLKPrescaler)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_RCC_MCOCLKPRE(RCC_MCOCLKPrescaler));

    tmpregister = RCC->CFG;
    /* Clear MCOPRE[3:0] bits */
    tmpregister &= ((uint32_t)0x0FFFFFFF);
    /* Set MCOPRE[3:0] bits according to RCC_ADCHCLKPrescaler value */
    tmpregister |= RCC_MCOCLKPrescaler;

    /* Store the new value */
    RCC->CFG = tmpregister;
}

/**
 * @brief  Selects the clock source to output on MCO pin.
 * @param RCC_MCO specifies the clock source to output.
 *
 *   this parameter can be one of the following values:
 *     @arg RCC_MCO_NOCLK No clock selected
 *     @arg RCC_MCO_LSI LSI oscillator clock selected
 *     @arg RCC_MCO_LSE LSE oscillator clock selected
 *     @arg RCC_MCO_MSI MSI oscillator clock selected
 *     @arg RCC_MCO_SYSCLK System clock selected
 *     @arg RCC_MCO_HSI HSI oscillator clock selected
 *     @arg RCC_MCO_HSE HSE oscillator clock selected
 *     @arg RCC_MCO_PLLCLK PLL clock selected
 *
 */
void RCC_ConfigMco(uint8_t RCC_MCO)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_RCC_MCO(RCC_MCO));

    tmpregister = RCC->CFG;
    /* Clear MCO[2:0] bits */
    tmpregister &= ((uint32_t)0xF8FFFFFF);
    /* Set MCO[2:0] bits according to RCC_MCO value */
    tmpregister |= ((uint32_t)(RCC_MCO << 24));

    /* Store the new value */
    RCC->CFG = tmpregister;
}

/**
 * @brief  Checks whether the specified RCC flag is set or not.
 * @param RCC_FLAG specifies the flag to check.
 *
 *   this parameter can be one of the following values:
 *     @arg RCC_CTRL_FLAG_HSIRDF        HSI oscillator clock ready
 *     @arg RCC_CTRL_FLAG_HSERDF        HSE oscillator clock ready
 *     @arg RCC_CTRL_FLAG_PLLRDF        PLL clock ready
 *     @arg RCC_LDCTRL_FLAG_LSERD       LSE oscillator clock ready
 *     @arg RCC_LDCTRL_FLAG_LSECLKSSF   LSE Clock Security System failure status
 *     @arg RCC_LDCTRL_FLAG_BORRSTF     BOR reset flag
 *     @arg RCC_LDCTRL_FLAG_LDEMCRSTF   LowPower EMC reset flag
 *     @arg RCC_CTRLSTS_FLAG_LSIRD      LSI oscillator clock ready
 *     @arg RCC_CTRLSTS_FLAG_MSIRD      MSI oscillator clock ready
 *     @arg RCC_CTRLSTS_FLAG_RAMRSTF    RAM reset flag
 *     @arg RCC_CTRLSTS_FLAG_MMURSTF    MMU reset flag
 *     @arg RCC_CTRLSTS_FLAG_PINRSTF    Pin reset
 *     @arg RCC_CTRLSTS_FLAG_PORRSTF    POR reset
 *     @arg RCC_CTRLSTS_FLAG_SFTRSTF    Software reset
 *     @arg RCC_CTRLSTS_FLAG_IWDGRSTF   Independent Watchdog reset
 *     @arg RCC_CTRLSTS_FLAG_WWDGRSTF   Window Watchdog reset
 *     @arg RCC_CTRLSTS_FLAG_LPWRRSTF   Low Power reset
 *
 * @return The new state of RCC_FLAG (SET or RESET).
 */
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG)
{
    uint32_t tmp         = 0;
    uint32_t statusreg   = 0;
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_RCC_FLAG(RCC_FLAG));

    /* Get the RCC register index */
    tmp = RCC_FLAG >> 5;
    if (tmp == 1) /* The flag to check is in CTRL register */
    {
        statusreg = RCC->CTRL;
    }
    else if (tmp == 2) /* The flag to check is in BDCTRL register */
    {
        statusreg = RCC->LDCTRL;
    }
    else /* The flag to check is in CTRLSTS register */
    {
        statusreg = RCC->CTRLSTS;
    }

    /* Get the flag position */
    tmp = RCC_FLAG & FLAG_MASK;
    if ((statusreg & ((uint32_t)1 << tmp)) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    /* Return the flag status */
    return bitstatus;
}

/**
 * @brief  Clears the RCC reset flags.
 * @note   The reset flags are: RCC_FLAG_LPEMCRST, RCC_FLAG_BORRST, RCC_FLAG_RAMRST, RCC_FLAG_MMURST,
 *                              RCC_FLAG_PINRST, RCC_FLAG_PORRST,RCC_FLAG_SFTRST, RCC_FLAG_IWDGRST,
 *                              RCC_FLAG_WWDGRST, RCC_FLAG_LPWRRST
 */
void RCC_ClrFlag(void)
{
    /* Set RMVF bit to clear the reset flags */
    RCC->CTRLSTS |= CSR_RMRSTF_SET;
    /* RMVF bit should be reset */
    RCC->CTRLSTS &= CSR_RMVF_Reset;
}

/**
 * @brief  Checks whether the specified RCC interrupt has occurred or not.
 * @param RccInt specifies the RCC interrupt source to check.
 *
 *   this parameter can be one of the following values:
 *     @arg RCC_INT_LSIRDIF LSI ready interrupt
 *     @arg RCC_INT_LSERDIF LSE ready interrupt
 *     @arg RCC_INT_HSIRDIF HSI ready interrupt
 *     @arg RCC_INT_HSERDIF HSE ready interrupt
 *     @arg RCC_INT_PLLRDIF PLL ready interrupt
 *     @arg RCC_INT_BORIF interrupt
 *     @arg RCC_INT_MSIRDIF MSI ready interrupt
 *     @arg RCC_INT_CLKSSIF Clock Security System interrupt
 *
 * @return The new state of RccInt (SET or RESET).
 */
INTStatus RCC_GetIntStatus(uint8_t RccInt)
{
    INTStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_RCC_GET_INT(RccInt));

    /* Check the status of the specified RCC interrupt */
    if ((RCC->CLKINT & RccInt) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    /* Return the RccInt status */
    return bitstatus;
}

/**
 * @brief  Clears the RCC's interrupt pending bits.
 * @param RccInt specifies the interrupt pending bit to clear.
 *
 *   this parameter can be any combination of the
 *   following values:
 *     @arg RCC_CLR_MSIRDIF Clear MSI ready interrupt flag
 *     @arg RCC_CLR_LSIRDIF Clear LSI ready interrupt flag
 *     @arg RCC_CLR_LSERDIF Clear LSE ready interrupt flag
 *     @arg RCC_CLR_HSIRDIF Clear HSI ready interrupt flag
 *     @arg RCC_CLR_HSERDIF Clear HSE ready interrupt flag
 *     @arg RCC_CLR_PLLRDIF Clear PLL ready interrupt flag
 *     @arg RCC_CLR_BORIF   Clear BOR interrupt flag
 *     @arg RCC_CLR_CLKSSIF Clear Clock Security System interrupt flag
 */
void RCC_ClrIntPendingBit(uint32_t RccClrInt)
{
    /* Check the parameters */
    assert_param(IS_RCC_CLR_INTF(RccClrInt));
   /* Software set this bit to clear INT flag. */
    RCC->CLKINT |= RccClrInt;
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
