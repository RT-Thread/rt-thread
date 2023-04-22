////////////////////////////////////////////////////////////////////////////////
/// @file     hal_rcc.c
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE RCC FIRMWARE FUNCTIONS.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#define _HAL_RCC_C_

// Files includes
#include "mm32_reg.h"
#include "hal_rcc.h"



u8 tbPresc[] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup RCC_HAL
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup RCC_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  Resets the RCC clock configuration to default state.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_DeInit()
{
    SET_BIT(RCC->CR, RCC_CR_HSION);
    CLEAR_BIT(RCC->CFGR, RCC_CFGR_SW);
    CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_CSSON | RCC_CR_PLLON );
    CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL_DN | RCC_PLLCFGR_PLL_DP);
    CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);
    CLEAR_REG(RCC->CFGR);
    CLEAR_REG(RCC->CIR);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures the External High Speed oscillator (HSE).
/// @param  state: specifies the new state of HSE.
///         This parameter can be one of the following values:
/// @arg    RCC_HSE_OFF: HSE oscillator OFF
/// @arg    RCC_HSE_ON: HSE oscillator ON
/// @arg    RCC_HSE_Bypass: HSE oscillator bypassed with external clock
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_HSEConfig(RCCHSE_TypeDef state)
{
    RCC->CR &= ~(RCC_CR_HSEBYP | RCC_CR_HSEON);
    switch (state) {
        case RCC_HSE_Bypass:
            RCC->CR |= RCC_CR_HSEBYP;
            RCC->CR |= RCC_CR_HSEON;
            break;
        case RCC_HSE_ON:
            RCC->CR |= RCC_CR_HSEON;
            break;
        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the specified RCC flag is set or not.
/// @param  flag: specifies the flag to check.
///         This parameter can be one of the following values:
/// @arg    RCC_FLAG_HSIRDY: HSI oscillator clock ready
/// @arg    RCC_FLAG_HSERDY: HSE oscillator clock ready
/// @arg    RCC_FLAG_PLLRDY: PLL clock ready
/// @arg    RCC_FLAG_LSERDY: LSE oscillator clock ready
/// @arg    RCC_FLAG_LSIRDY: LSI oscillator clock ready
/// @arg    RCC_FLAG_PINRST: Pin reset
/// @arg    RCC_FLAG_PORRST: POR/PDR reset
/// @arg    RCC_FLAG_SFTRST: Software reset
/// @arg    RCC_FLAG_IWDGRST: Independent Watchdog reset
/// @arg    RCC_FLAG_WWDGRST: Window Watchdog reset
/// @arg    RCC_FLAG_LPWRRST: Low Power reset
/// @retval The new state of flag (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
FlagStatus RCC_GetFlagStatus(RCC_FLAG_TypeDef flag)
{
    return ((((flag >> 5) == CR_REG_INDEX) ? RCC->CR : (((flag >> 5) == BDCR_REG_INDEX) ? RCC->BDCR : RCC->CSR)) &
            (1 << (flag & 0x1F)))
           ? SET : RESET;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Waits for HSE start-up.
/// @param  None.
/// @retval An ErrorStatus enumuration value:
///         - SUCCESS: HSE oscillator is stable and ready to use
///         - ERROR: HSE oscillator not yet ready
////////////////////////////////////////////////////////////////////////////////
ErrorStatus RCC_WaitForHSEStartUp(void)
{
    u32 StartUpCounter = 0;

    FlagStatus HSEStatus;

    do {
        HSEStatus = RCC_GetFlagStatus(RCC_FLAG_HSERDY);
        StartUpCounter++;
    } while ((HSEStatus == RESET) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    return (ErrorStatus)(RCC_GetFlagStatus(RCC_FLAG_HSERDY) != RESET) ? SUCCESS : ERROR;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Waits for flag start-up.
/// @param  flag: specifies the flag to check.
///         This parameter can be one of the following values:
/// @arg    RCC_FLAG_HSIRDY: HSI oscillator clock ready
/// @arg    RCC_FLAG_HSERDY: HSE oscillator clock ready
/// @arg    RCC_FLAG_PLLRDY: PLL clock ready
/// @arg    RCC_FLAG_LSERDY: LSE oscillator clock ready
/// @arg    RCC_FLAG_LSIRDY: LSI oscillator clock ready
/// @arg    RCC_FLAG_PINRST: Pin reset
/// @arg    RCC_FLAG_PORRST: POR/PDR reset
/// @arg    RCC_FLAG_SFTRST: Software reset
/// @arg    RCC_FLAG_IWDGRST: Independent Watchdog reset
/// @arg    RCC_FLAG_WWDGRST: Window Watchdog reset
/// @retval An ErrorStatus enumuration value:
///         - SUCCESS: HSE oscillator is stable and ready to use
///         - ERROR: HSE oscillator not yet ready
////////////////////////////////////////////////////////////////////////////////
ErrorStatus RCC_WaitForFlagStartUp(RCC_FLAG_TypeDef flag)
{
    u32 StartUpCounter = 0;

    while (RCC_GetFlagStatus(flag) == RESET) {
        if (StartUpCounter++ > HSE_STARTUP_TIMEOUT) {
            return ERROR;
        }
    }
    return SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the Internal High Speed oscillator (HSI).
/// @param  state: new state of the HSI.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_HSICmd(FunctionalState state)
{
    MODIFY_REG(RCC->CR, RCC_CR_HSION, (state << RCC_CR_HSION_Pos));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures the system clock (SYSCLK).
/// @param  sys_clk_source: specifies the clock source used as system
///         clock. This parameter can be one of the following values:
/// @arg    RCC_HSI: specifies HSI as system clock
/// @arg    RCC_HSE: specifies HSE as system clock
/// @arg    RCC_PLL: specifies PLL as system clock
/// @arg    RCC_LSI: specifies LSI as system clock
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_SYSCLKConfig(SYSCLK_TypeDef sys_clk_source)
{
    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, (sys_clk_source << RCC_CFGR_SW_Pos));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures the PLL clock source and DM DN factor.
///         This function must be used only when the PLL is disabled.
/// @param  plldn: specifies the PLL multiplication factor.
///         This parameter can be RCC_PLLMul_x where x:[31:26]
/// @param  plldm: specifies the PLL Divsior factor.
///         This parameter can be RCC_Divsior_x where x:[22:20]
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_PLLDMDNConfig(u32 plldn, u32 plldm)
{
    MODIFY_REG(RCC->PLLCFGR, (RCC_PLLCFGR_PLL_DN | RCC_PLLCFGR_PLL_DP), ((plldn << RCC_PLLCFGR_PLL_DN_Pos) | (plldm << RCC_PLLCFGR_PLL_DP_Pos)));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the PLL.
///   The PLL can not be disabled if it is used as system clock.
/// @param  state: new state of the PLL.
///   This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_PLLCmd(FunctionalState state)
{
    MODIFY_REG(RCC->CR, RCC_CR_PLLON, (state << RCC_CR_PLLON_Pos));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures the PLL clock source and multiplication factor.
///         This function must be used only when the PLL is disabled.
/// @param  pll_src: specifies the PLL entry clock source.
///         This parameter can be one of the following values:
/// @arg    RCC_HSI_Div4: HSI oscillator clock divided
///         by 4 selected as PLL clock entry
/// @arg    RCC_HSE_Div1: HSE oscillator clock selected
///         as PLL clock entry
/// @arg    RCC_HSE_Div2: HSE oscillator clock divided
///         by 2 selected as PLL clock entry
/// @param  pll_mul: specifies the PLL multiplication factor.
///         This parameter can be RCC_PLLMul_x where x:[31:26][22:20]
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_PLLConfig(RCC_PLLSource_TypeDef pll_src, RCC_PLLMul_TypeDef pll_mul)
{
    const u8 DNDM_Item[] = {0x07, 0x03, 0x05, 0x01, 0x07, 0x01, 0x09, 0x01,  // Frclk*8/4 ; Frclk*6/2 ; Frclk*8/2 ; Frclk*10/2;
                            0x0B, 0x01, 0x0D, 0x01, 0x0F, 0x01, 0x11, 0x01,  // Frclk*12/2; Frclk*14/2; Frclk*16/2; Frclk*18/2;
                            0x13, 0x01, 0x15, 0x01, 0x17, 0x01, 0x19, 0x01,  // Frclk*20/2; Frclk*22/2; Frclk*24/2; Frclk*26/2;
                            0x1B, 0x01, 0x1D, 0x01, 0x1F, 0x01
                           };             // Frclk*28/2; Frclk*30/2;    // Frclk*32/2;
    MODIFY_REG(RCC->PLLCFGR, (RCC_PLLCFGR_PLLXTPRE | RCC_PLLCFGR_PLLSRC), pll_src);
    RCC_PLLDMDNConfig((u32)DNDM_Item[pll_mul >> 17], (u32)DNDM_Item[(pll_mul >> 17) + 1]);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures the USB clock (USBCLK).
/// @param  usb_clk_src: specifies the USB clock source.
///         This clock is derived from the PLL output.
///         This parameter can be one of the following values:
/// @arg    RCC_USBCLKSource_PLLCLK_Div1: PLL clock selected as USB clock source
/// @arg    RCC_USBCLKSource_PLLCLK_Div2: PLL clock divided by 2 selected as USB
///         clock source
/// @arg    RCC_USBCLKSource_PLLCLK_Div3: PLL clock divided by 3 selected as USB
///         clock source
/// @arg    RCC_USBCLKSource_PLLCLK_Div4: PLL clock divided by 4 selected as USB
///         clock source
/// @arg    RCC_USBCLKSource_PLLCLK_Div5: PLL clock divided by 5 selected as USB
///         clock source
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_USBCLKConfig(RCC_USBCLKSOURCE_TypeDef usb_clk_src)
{
    MODIFY_REG(RCC->CFGR, RCC_CFGR_USBPRE, (usb_clk_src << RCC_CFGR_USBPRE_Pos));
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the clock source used as system clock.
/// @param  None.
/// @retval The clock source used as system clock. The returned value can
///         be one of the following:
///         - 0x00: HSI/6 used as system clock
///         - 0x04: HSE used as system clock
///         - 0x08: PLL used as system clock
////////////////////////////////////////////////////////////////////////////////
u8 RCC_GetSYSCLKSource(void)
{
    return ((u8)READ_BIT(RCC->CFGR, RCC_CFGR_SWS));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures the AHB clock (hclk).
/// @param  sys_clk: defines the AHB clock divider. This clock is derived
///                    from the system clock (SYSCLK).
///         This parameter can be one of the following values:
/// @arg    RCC_SYSCLK_Div1: AHB clock = SYSCLK
/// @arg    RCC_SYSCLK_Div2: AHB clock = SYSCLK/2
/// @arg    RCC_SYSCLK_Div4: AHB clock = SYSCLK/4
/// @arg    RCC_SYSCLK_Div8: AHB clock = SYSCLK/8
/// @arg    RCC_SYSCLK_Div16: AHB clock = SYSCLK/16
/// @arg    RCC_SYSCLK_Div64: AHB clock = SYSCLK/64
/// @arg    RCC_SYSCLK_Div128: AHB clock = SYSCLK/128
/// @arg    RCC_SYSCLK_Div256: AHB clock = SYSCLK/256
/// @arg    RCC_SYSCLK_Div512: AHB clock = SYSCLK/512
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_HCLKConfig(RCC_AHB_CLK_TypeDef sys_clk)
{
    MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, sys_clk);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures the Low Speed APB clock (pclk1).
/// @param  hclk: defines the APB1 clock divider. This clock is derived from
///                  the AHB clock (hclk).
///         This parameter can be one of the following values:
/// @arg    RCC_HCLK_Div1: APB1 clock = hclk
/// @arg    RCC_HCLK_Div2: APB1 clock = hclk/2
/// @arg    RCC_HCLK_Div4: APB1 clock = hclk/4
/// @arg    RCC_HCLK_Div8: APB1 clock = hclk/8
/// @arg    RCC_HCLK_Div16: APB1 clock = hclk/16
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_PCLK1Config(RCC_APB1_APB2_CLK_TypeDef hclk)
{
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, hclk);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures the High Speed APB clock (pclk2).
/// @param  hclk: defines the APB2 clock divider. This clock is derived from
///                  the AHB clock (hclk).
///         This parameter can be one of the following values:
/// @arg    RCC_HCLK_Div1: APB2 clock = hclk
/// @arg    RCC_HCLK_Div2: APB2 clock = hclk/2
/// @arg    RCC_HCLK_Div4: APB2 clock = hclk/4
/// @arg    RCC_HCLK_Div8: APB2 clock = hclk/8
/// @arg    RCC_HCLK_Div16: APB2 clock = hclk/16
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_PCLK2Config(RCC_APB1_APB2_CLK_TypeDef hclk)
{
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, (hclk << 3));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures the ADC clock (ADCCLK).
/// @param  pclk2: defines the ADC clock divider. This clock is derived from
///                   the APB2 clock (pclk2).
///         This parameter can be one of the following values:
/// @arg    RCC_PCLK2_Div2: ADC clock = pclk2/2
/// @arg    RCC_PCLK2_Div4: ADC clock = pclk2/4
/// @arg    RCC_PCLK2_Div6: ADC clock = pclk2/6
/// @arg    RCC_PCLK2_Div8: ADC clock = pclk2/8
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_ADCCLKConfig(RCC_ADCCLKSOURCE_TypeDef pclk2)
{
    MODIFY_REG(RCC->CFGR, ADC_CFGR_PRE, pclk2);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures the External Low Speed oscillator (LSE).
/// @param  state: specifies the new state of the LSE.
///         This parameter can be one of the following values:
/// @arg    RCC_LSE_OFF: LSE oscillator OFF
/// @arg    RCC_LSE_ON: LSE oscillator ON
/// @arg    RCC_LSE_Bypass: LSE oscillator bypassed with external
///         clock
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_LSEConfig(RCC_LSE_TypeDef state)
{
    RCC->BDCR &= ~(RCC_BDCR_LSEBYP | RCC_BDCR_LSEON);

    switch (state) {
        case RCC_LSE_Bypass:
            RCC->BDCR |= RCC_BDCR_LSEBYP;
            RCC->BDCR |= RCC_BDCR_LSEON;
            break;
        case RCC_LSE_ON:
            RCC->BDCR |= RCC_BDCR_LSEON;
            break;
        default:
            break;
    }
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures the RTC clock (RTCCLK).
///         Once the RTC clock is selected it can be changed unless the
///         Backup domain is reset.
/// @param  rtc_clk_src: specifies the RTC clock source.
///         This parameter can be one of the following values:
/// @arg    RCC_RTCCLKSource_LSE: LSE selected as RTC clock
/// @arg    RCC_RTCCLKSource_LSI: LSI selected as RTC clock
/// @arg    RCC_RTCCLKSource_HSE_Div128: HSE clock divided by 128
///         selected as RTC clock
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_RTCCLKConfig(RCC_RTCCLKSOURCE_TypeDef rtc_clk_src)
{
    MODIFY_REG(RCC->BDCR, RCC_BDCR_RTCSEL, rtc_clk_src);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the RTC clock.
///         This function must be used only after the RTC clock was
///         selected using the RCC_RTCCLKConfig function.
/// @param  state: new state of the RTC clock.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_RTCCLKCmd(FunctionalState state)
{
    MODIFY_REG(RCC->BDCR, RCC_BDCR_RTCEN, (state << RCC_BDCR_RTCEN_Pos));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the Internal Low Speed oscillator (LSI).
///         LSI can not be disabled if the IWDG is running.
/// @param  state: new state of the LSI.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_LSICmd(FunctionalState state)
{
//    u32 j;
    MODIFY_REG(RCC->CSR, RCC_CSR_LSION | RCC_CSR_LSIOENLV, RCC_CSR_LSIOENLV | (state << RCC_CSR_LSION_Pos));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the clock frequency of different on chip clocks.
/// @param  None.
/// @retval sys_clk : System clock frequency
////////////////////////////////////////////////////////////////////////////////
u32 RCC_GetSysClockFreq(void)
{
    u32 result;
    u32 clock, mul, div;
    switch (RCC->CFGR & RCC_CFGR_SWS) {
        case RCC_CFGR_SWS_LSI:
            result = LSI_VALUE;
            break;

        case RCC_CFGR_SWS_HSE:
            result = HSE_VALUE;
            break;

        case RCC_CFGR_SWS_PLL:
            clock = READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC) ? (READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLXTPRE) ? (HSE_VALUE >> 1) : HSE_VALUE)
                    : HSI_VALUE_PLL_ON;
            mul = ((RCC->PLLCFGR & (u32)RCC_PLLCFGR_PLL_DN) >> RCC_PLLCFGR_PLL_DN_Pos) + 1;
            div = ((RCC->PLLCFGR & RCC_PLLCFGR_PLL_DP) >> RCC_PLLCFGR_PLL_DP_Pos) + 1;

            result = clock * mul / div;
            break;
        default:
            result =  HSI_VALUE;
            break;
    }
    return result;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the hclk frequency of different on chip clocks.
/// @param  None.
/// @retval hclk frequency
////////////////////////////////////////////////////////////////////////////////
u32 RCC_GetHCLKFreq(void)
{
    return (RCC_GetSysClockFreq() >> tbPresc[(RCC->CFGR & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos]);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the pclk1 frequency of different on chip clocks.
/// @param  None.
/// @retval pclk1 frequency
////////////////////////////////////////////////////////////////////////////////
u32 RCC_GetPCLK1Freq(void)
{
    return (RCC_GetHCLKFreq() >> tbPresc[(RCC->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos]);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the pclk2 frequency of different on chip clocks.
/// @param  None.
/// @retval pclk2 frequency
////////////////////////////////////////////////////////////////////////////////
u32 RCC_GetPCLK2Freq(void)
{
    return (RCC_GetHCLKFreq() >> tbPresc[(RCC->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos]);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the frequency of different on chip clocks.
/// @param  clk: pointer to a RCC_ClocksTypeDef structure which
///   will hold the clocks frequency.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_GetClocksFreq(RCC_ClocksTypeDef* clk)
{
    u8 tbADCPresc[] = {2, 4, 6, 8};

    clk->SYSCLK_Frequency = RCC_GetSysClockFreq();
    clk->HCLK_Frequency   = RCC_GetHCLKFreq();
    clk->PCLK1_Frequency  = RCC_GetPCLK1Freq();
    clk->PCLK2_Frequency  = RCC_GetPCLK2Freq();

    clk->ADCCLK_Frequency = clk->PCLK2_Frequency / tbADCPresc[(RCC->CFGR & ADC_CFGR_PRE) >> ADC_CFGR_PRE_Pos];

}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the AHB peripheral clock.
/// @param  ahb_periph: specifies the AHB peripheral to gates its clock.
///   This parameter can be any combination of the following values:
/// @param  state: new state of the specified peripheral clock.
///   This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_AHBPeriphClockCmd(u32 ahb_periph, FunctionalState state)
{
    (state) ? (RCC->AHBENR |= ahb_periph) : (RCC->AHBENR &= ~ahb_periph);
}
/// @param  state: new state of the specified peripheral clock.
///   This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_AHB2PeriphClockCmd(u32 ahb_periph, FunctionalState state)
{
    (state) ? (RCC->AHB2ENR |= ahb_periph) : (RCC->AHB2ENR &= ~ahb_periph);
}
/// @param  state: new state of the specified peripheral clock.
///   This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_AHB3PeriphClockCmd(u32 ahb_periph, FunctionalState state)
{
    (state) ? (RCC->AHB3ENR |= ahb_periph) : (RCC->AHB3ENR &= ~ahb_periph);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the High Speed APB (APB2) peripheral clock.
/// @param  apb2_periph: specifies the APB2 peripheral to gates its
///   clock.
///   This parameter can be any combination of the following values:
/// @param  state: new state of the specified peripheral clock.
///   This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_APB2PeriphClockCmd(u32 apb2_periph, FunctionalState state)
{
    (state) ? (RCC->APB2ENR |= apb2_periph) : (RCC->APB2ENR &= ~apb2_periph);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the Low Speed APB (APB1) peripheral clock.
/// @param  apb1_periph: specifies the APB1 peripheral to gates its
///   clock.
///   This parameter can be any combination of the following values:
/// @param  state: new state of the specified peripheral clock.
///   This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_APB1PeriphClockCmd(u32 apb1_periph, FunctionalState state)
{
    (state) ? (RCC->APB1ENR |= apb1_periph) : (RCC->APB1ENR &= ~apb1_periph);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Forces or releases High Speed APB (APB2) peripheral reset.
/// @param  apb2_periph: specifies the APB2 peripheral to reset.
///   This parameter can be any combination of the following values:
/// @param  state: new state of the specified peripheral reset.
///   This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_APB2PeriphResetCmd(u32 apb2_periph, FunctionalState state)
{
    (state) ? (RCC->APB2RSTR |= apb2_periph) : (RCC->APB2RSTR &= ~apb2_periph);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Forces or releases Low Speed APB (APB1) peripheral reset.
/// @param  apb1_periph: specifies the APB1 peripheral to reset.
///   This parameter can be any combination of the following values:
/// @param  state: new state of the specified peripheral clock.
///   This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_APB1PeriphResetCmd(u32 apb1_periph, FunctionalState state)
{
    (state) ? (RCC->APB1RSTR |= apb1_periph) : (RCC->APB1RSTR &= ~apb1_periph);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Forces or releases Low Speed AHB peripheral reset.
/// @param  ahb_periph: specifies the AHB peripheral to reset.
///   This parameter can be any combination of the following values:
/// @param  state: new state of the specified peripheral clock.
///   This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_AHBPeriphResetCmd(u32 ahb_periph, FunctionalState state)
{
    (state) ? (RCC->AHBRSTR |= ahb_periph) : (RCC->AHBRSTR &= ~ahb_periph);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Forces or releases Low Speed AHB2 peripheral reset.
/// @param  ahb_periph: specifies the AHB peripheral to reset.
///   This parameter can be any combination of the following values:
/// @param  state: new state of the specified peripheral clock.
///   This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_AHB2PeriphResetCmd(u32 ahb_periph, FunctionalState state)
{
    (state) ? (RCC->AHB2RSTR |= ahb_periph) : (RCC->AHB2RSTR &= ~ahb_periph);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Forces or releases Low Speed AHB2 peripheral reset.
/// @param  ahb_periph: specifies the AHB peripheral to reset.
///   This parameter can be any combination of the following values:
/// @param  state: new state of the specified peripheral clock.
///   This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_AHB3PeriphResetCmd(u32 ahb_periph, FunctionalState state)
{
    (state) ? (RCC->AHB3RSTR |= ahb_periph) : (RCC->AHB3RSTR &= ~ahb_periph);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Forces or releases the Backup domain reset.
/// @param  state: new state of the Backup domain reset.
///   This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_BackupResetCmd(FunctionalState state)
{
    MODIFY_REG(RCC->BDCR, RCC_BDCR_BDRST, (state << RCC_BDCR_BDRST_Pos));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the Clock Security System.
/// @param  state: new state of the Clock Security System..
///   This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_ClockSecuritySystemCmd(FunctionalState state)
{
    MODIFY_REG(RCC->CR, RCC_CR_CSSON, (state << RCC_CR_CSSON_Pos));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Selects the clock source to output on MCO pin.
/// @param  mco_src: specifies the clock source to output.
///   This parameter can be one of the following values:
/// @arg RCC_MCO_NoClock: No clock selected
/// @arg RCC_MCO_LSI: LSI oscillator clock selected
/// @arg RCC_MCO_LSE: LSE oscillator clock selected
/// @arg RCC_MCO_SYSCLK: System clock selected
/// @arg RCC_MCO_HSI: HSI oscillator clock selected
/// @arg RCC_MCO_HSE: HSE oscillator clock selected
/// @arg RCC_MCO_PLLCLK_Div2: PLL clock divided by 2 selected
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_MCOConfig(RCC_MCO_TypeDef mco_src)
{
    MODIFY_REG(RCC->CFGR, RCC_CFGR_MCO, mco_src);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Clears the RCC reset flags.
///   The reset flags are: RCC_FLAG_PINRST, RCC_FLAG_PORRST,
///   RCC_FLAG_SFTRST, RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST,
///   RCC_FLAG_LPWRRST
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_ClearFlag(void)
{
    SET_BIT(RCC->CSR, RCC_CSR_RMVF);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified RCC interrupts.
/// @param  it: specifies the RCC interrupt sources to be enabled or
/// disabled.
///   This parameter can be any combination of the following values:
/// @arg RCC_IT_LSIRDY: LSI ready interrupt
/// @arg RCC_IT_LSERDY: LSE ready interrupt
/// @arg RCC_IT_HSIRDY: HSI ready interrupt
/// @arg RCC_IT_HSERDY: HSE ready interrupt
/// @arg RCC_IT_PLLRDY: PLL ready interrupt
/// @param  state: new state of the specified RCC interrupts.
///   This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_ITConfig(RCC_IT_TypeDef it, FunctionalState state)
{
    (state) ? SET_BIT(RCC->CIR, it << RCC_CIR_LSIRDYIE_Pos) : CLEAR_BIT(RCC->CIR, it << RCC_CIR_LSIRDYIE_Pos);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the specified RCC interrupt has occurred or not.
/// @param  it: specifies the RCC interrupt source to check.
///   This parameter can be one of the following values:
/// @arg RCC_IT_LSIRDY: LSI ready interrupt
/// @arg RCC_IT_LSERDY: LSE ready interrupt
/// @arg RCC_IT_HSIRDY: HSI ready interrupt
/// @arg RCC_IT_HSERDY: HSE ready interrupt
/// @arg RCC_IT_PLLRDY: PLL ready interrupt
/// @arg RCC_IT_CSS: Clock Security System interrupt
/// @retval The new state of it (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
ITStatus RCC_GetITStatus(RCC_IT_TypeDef it)
{
    return (ITStatus)READ_BIT(RCC->CIR, (it << RCC_CIR_LSIRDYF_Pos));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Clears the RCC's interrupt pending bits.
/// @param  it: specifies the interrupt pending bit to clear.
///   This parameter can be any combination of the following values:
/// @arg RCC_IT_LSIRDY: LSI ready interrupt
/// @arg RCC_IT_LSERDY: LSE ready interrupt
/// @arg RCC_IT_HSIRDY: HSI ready interrupt
/// @arg RCC_IT_HSERDY: HSE ready interrupt
/// @arg RCC_IT_PLLRDY: PLL ready interrupt
/// @arg RCC_IT_CSS: Clock Security System interrupt
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_ClearITPendingBit(u8 it)
{
    SET_BIT(RCC->CIR, (it << RCC_CIR_LSIRDYC_Pos));
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Forces or releases Low Speed APB (APB1) peripheral reset.
/// @param  apb1_periph: specifies the APB1 peripheral to reset.
///   This parameter can be any combination of the following values:
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_APB1PeriphReset(u32 apb1_periph)
{
    RCC->APB1RSTR |= apb1_periph;
    RCC->APB1RSTR &= ~apb1_periph;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Forces or releases Low Speed APB (APB2) peripheral reset.
/// @param  apb2_periph: specifies the APB2 peripheral to reset.
///   This parameter can be any combination of the following values:
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_APB2PeriphReset(u32 apb2_periph)
{
    RCC->APB2RSTR |= apb2_periph;
    RCC->APB2RSTR &= ~apb2_periph;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Forces or releases High Speed AHB (AHB1) peripheral reset.
/// @param  ahb1_periph: specifies the AHB1 peripheral to reset.
///   This parameter can be any combination of the following values:
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_AHBPeriphReset(u32 ahb1_periph)
{
    RCC->AHBRSTR |= ahb1_periph;
    RCC->AHBRSTR &= ~ahb1_periph;
}
////////////////////////////////////////////////////////////////////////////////
//
//  New Function Interface
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief  Forces or releases Low Speed APB (APB1) peripheral reset.
/// @param  apb1_periph: specifies the APB1 peripheral to reset.
///   This parameter can be any combination of the following values:
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exRCC_APB1PeriphReset(u32 apb1_periph)
{
    RCC->APB1RSTR |= apb1_periph;
    RCC->APB1RSTR &= ~apb1_periph;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief
/// @param
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exRCC_BackupReset()
{
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Forces or releases High Speed APB (APB2) peripheral reset.
/// @param  apb2_periph: specifies the APB2 peripheral to reset.
///   This parameter can be any combination of the following values:
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exRCC_APB2PeriphReset(u32 apb2_periph)
{
    RCC->APB2RSTR |= apb2_periph;
    RCC->APB2RSTR &= ~apb2_periph;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Forces or releases High Speed AHB (AHB1) peripheral reset.
/// @param  ahb1_periph: specifies the AHB1 peripheral to reset.
///   This parameter can be any combination of the following values:
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exRCC_AHBPeriphReset(u32 ahb1_periph)
{
    RCC->AHBRSTR |= ahb1_periph;
    RCC->AHBRSTR &= ~ahb1_periph;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Disable systick
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exRCC_SystickDisable()
{
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enable systick
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exRCC_SystickEnable(u32 sys_tick_period)
{
    SysTick_Config(RCC_GetHCLKFreq() / 1000000 * sys_tick_period);
}

/*
(state) ? (RCC->AHBENR |= ahb_periph) : (RCC->AHBENR &= ~ahb_periph);
(state) ? (RCC->APB1ENR |= apb1_periph) : (RCC->APB1ENR &= ~apb1_periph);
(state) ? (RCC->APB2ENR |= apb2_periph) : (RCC->APB2ENR &= ~apb2_periph);
*/

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified ADC peripheral Clock.
/// @param  peripheral:select the ADC peripheral.
/// @param  state: new state of the ADC peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_ADC_ClockCmd(ADC_TypeDef* peripheral, FunctionalState state)
{
    switch (*(vu32*)&peripheral) {

        case ADC1_BASE:
            (state) ? (RCC->APB2ENR |= RCC_APB2ENR_ADC1) : (RCC->APB2ENR &= ~RCC_APB2ENR_ADC1);
            break;
        case ADC2_BASE:
            (state) ? (RCC->APB2ENR |= RCC_APB2ENR_ADC2) : (RCC->APB2ENR &= ~RCC_APB2ENR_ADC2);
            break;
        case ADC3_BASE:
            (state) ? (RCC->APB2ENR |= RCC_APB2ENR_ADC3) : (RCC->APB2ENR &= ~RCC_APB2ENR_ADC3);
            break;
        default:
            break;
    }

}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified BKP peripheral Clock.
/// @param  peripheral:select the BKP peripheral.
/// @param  state: new state of the BKP peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_BKP_ClockCmd(BKP_TypeDef* peripheral, FunctionalState state)
{
    if(BKP == peripheral) {
        (state) ? (RCC->APB1ENR |= RCC_APB1ENR_BKP) : (RCC->APB1ENR &= ~RCC_APB1ENR_BKP);
        (state) ? (RCC->APB1ENR |= RCC_APB1ENR_PWR) : (RCC->APB1ENR &= ~RCC_APB1ENR_PWR);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified CAN peripheral Clock.
/// @param  peripheral:select the CAN peripheral.
/// @param  state: new state of the CAN peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_CAN_ClockCmd(CAN_TypeDef* peripheral, FunctionalState state)
{
    if(CAN1 == peripheral) {
        (state) ? (RCC->APB1ENR |= RCC_APB1ENR_CAN) : (RCC->APB1ENR &= ~RCC_APB1ENR_CAN);
    }
}


////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified COMP peripheral Clock.
/// @param  peripheral:select the COMP peripheral.
/// @param  state: new state of the COMP peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_COMP_ClockCmd(COMP_TypeDef* peripheral, FunctionalState state)
{
    if(COMP == peripheral) {
        (state) ? (RCC->APB2ENR |= RCC_APB2ENR_COMP) : (RCC->APB2ENR &= ~RCC_APB2ENR_COMP);
    }
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified CRC peripheral Clock.
/// @param  peripheral:select the CRC peripheral.
/// @param  state: new state of the CRC peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_CRC_ClockCmd(CRC_TypeDef* peripheral, FunctionalState state)
{
    if(CRC == peripheral) {
        (state) ? (RCC->AHBENR |= RCC_AHBENR_CRC) : (RCC->AHBENR &= ~RCC_AHBENR_CRC);
    }
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified DAC peripheral Clock.
/// @param  peripheral:select the DAC peripheral.
/// @param  state: new state of the DAC peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_DAC_ClockCmd(DAC_TypeDef* peripheral, FunctionalState state)
{
    if(DAC == peripheral) {
        (state) ? (RCC->APB1ENR |= RCC_APB1ENR_DAC) : (RCC->APB1ENR &= ~RCC_APB1ENR_DAC);
    }
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified DMA peripheral Clock.
/// @param  peripheral:select the DMA peripheral.
/// @param  state: new state of the DMA peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_DMA_ClockCmd(DMA_TypeDef* peripheral, FunctionalState state)
{
    if(DMA1 == peripheral) {
        (state) ? (RCC->AHBENR |= RCC_AHBENR_DMA1) : (RCC->AHBENR &= ~RCC_AHBENR_DMA1);
    }
    if(DMA2 == peripheral) {
        (state) ? (RCC->AHBENR |= RCC_AHBENR_DMA2) : (RCC->AHBENR &= ~RCC_AHBENR_DMA2);
    }
}



////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified GPIO peripheral Clock.
/// @param  peripheral:select the GPIO peripheral.
/// @param  state: new state of the GPIO peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_GPIO_ClockCmd(GPIO_TypeDef* peripheral, FunctionalState state)
{
    switch (*(vu32*)&peripheral) {
        case (u32)GPIOA:
            (state) ? (RCC->AHBENR |= RCC_AHBENR_GPIOA) : (RCC->AHBENR &= ~RCC_AHBENR_GPIOA);
            break;
        case (u32)GPIOB:
            (state) ? (RCC->AHBENR |= RCC_AHBENR_GPIOB) : (RCC->AHBENR &= ~RCC_AHBENR_GPIOB);
            break;
        case (u32)GPIOC:
            (state) ? (RCC->AHBENR |= RCC_AHBENR_GPIOC) : (RCC->AHBENR &= ~RCC_AHBENR_GPIOC);
            break;
        case (u32)GPIOD:
            (state) ? (RCC->AHBENR |= RCC_AHBENR_GPIOD) : (RCC->AHBENR &= ~RCC_AHBENR_GPIOD);
            break;
        case (u32)GPIOE:
            (state) ? (RCC->AHBENR |= RCC_AHBENR_GPIOE) : (RCC->AHBENR &= ~RCC_AHBENR_GPIOE);
            break;
        case (u32)GPIOF:
            (state) ? (RCC->AHBENR |= RCC_AHBENR_GPIOF) : (RCC->AHBENR &= ~RCC_AHBENR_GPIOF);
            break;
        case (u32)GPIOG:
            (state) ? (RCC->AHBENR |= RCC_AHBENR_GPIOG) : (RCC->AHBENR &= ~RCC_AHBENR_GPIOG);
            break;
        case (u32)GPIOH:
            (state) ? (RCC->AHBENR |= RCC_AHBENR_GPIOH) : (RCC->AHBENR &= ~RCC_AHBENR_GPIOH);
            break;
        default:
            break;
    }
}


////////////////////////////////////////////////////////////////////////////////
/// @brief  Deinitializes the uart peripheral registers to their
///         default reset values.
/// @param  peripheral: Select the UART or the UART peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_UART_ClockCmd(UART_TypeDef* peripheral, FunctionalState state)
{
    if(UART2 == peripheral) {
        (state) ? (RCC->APB1ENR |= RCC_APB1ENR_UART2) : (RCC->APB1ENR &= ~RCC_APB1ENR_UART2);//exRCC_APB1PeriphReset(RCC_APB1ENR_UART2);
    }
    if(UART1 == peripheral) {
        (state) ? (RCC->APB2ENR |= RCC_APB2ENR_UART1) : (RCC->APB2ENR &= ~RCC_APB2ENR_UART1);//exRCC_APB2PeriphReset(RCC_APB2ENR_UART1);
    }
    if(UART3 == peripheral) {
        (state) ? (RCC->APB1ENR |= RCC_APB1ENR_UART3) : (RCC->APB1ENR &= ~RCC_APB1ENR_UART3);//exRCC_APB1PeriphReset(RCC_APB1ENR_UART3);
    }
    if(UART4 == peripheral) {
        (state) ? (RCC->APB1ENR |= RCC_APB1ENR_UART4) : (RCC->APB1ENR &= ~RCC_APB1ENR_UART4);//exRCC_APB1PeriphReset(RCC_APB1ENR_UART4);
    }
    if(UART5 == peripheral) {
        (state) ? (RCC->APB1ENR |= RCC_APB1ENR_UART5) : (RCC->APB1ENR &= ~RCC_APB1ENR_UART5);//exRCC_APB1PeriphReset(RCC_APB1ENR_UART5);
    }
    if(UART6 == peripheral) {
        (state) ? (RCC->APB2ENR |= RCC_APB2ENR_UART6) : (RCC->APB2ENR &= ~RCC_APB2ENR_UART6);//exRCC_APB2PeriphReset(RCC_APB2ENR_UART6);
    }
    if(UART7 == peripheral) {
        (state) ? (RCC->APB1ENR |= RCC_APB1ENR_UART7) : (RCC->APB1ENR &= ~RCC_APB1ENR_UART7);//exRCC_APB1PeriphReset(RCC_APB1ENR_UART7);
    }
    if(UART8 == peripheral) {
        (state) ? (RCC->APB1ENR |= RCC_APB1ENR_UART8) : (RCC->APB1ENR &= ~RCC_APB1ENR_UART8);//exRCC_APB1PeriphReset(RCC_APB1ENR_UART8);
    }
}
/// @}

/// @}

/// @}
