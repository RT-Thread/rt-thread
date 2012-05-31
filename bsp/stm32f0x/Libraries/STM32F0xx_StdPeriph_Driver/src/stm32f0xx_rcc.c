/**
  ******************************************************************************
  * @file    stm32f0xx_rcc.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    23-March-2012
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Reset and clock control (RCC) peripheral:
  *           + Internal/external clocks, PLL, CSS and MCO configuration
  *           + System, AHB and APB busses clocks configuration
  *           + Peripheral clocks configuration
  *           + Interrupts and flags management
  *
 @verbatim

 ===============================================================================
                        ##### RCC specific features #####
 ===============================================================================
    [..] After reset the device is running from HSI (8 MHz) with Flash 0 WS, 
         all peripherals are off except internal SRAM, Flash and SWD.
         (#) There is no prescaler on High speed (AHB) and Low speed (APB) busses;
             all peripherals mapped on these busses are running at HSI speed.
         (#) The clock for all peripherals is switched off, except the SRAM and FLASH.
         (#) All GPIOs are in input floating state, except the SWD pins which
             are assigned to be used for debug purpose.
    [..] Once the device started from reset, the user application has to:
         (#) Configure the clock source to be used to drive the System clock
             (if the application needs higher frequency/performance)
         (#) Configure the System clock frequency and Flash settings
         (#) Configure the AHB and APB busses prescalers
         (#) Enable the clock for the peripheral(s) to be used
         (#) Configure the clock source(s) for peripherals which clocks are not
             derived from the System clock (ADC, CEC, I2C, USART, RTC and IWDG)

 @endverbatim
  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_rcc.h"

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup RCC 
  * @brief RCC driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* ---------------------- RCC registers mask -------------------------------- */
/* RCC Flag Mask */
#define FLAG_MASK                 ((uint8_t)0x1F)

/* CR register byte 2 (Bits[23:16]) base address */
#define CR_BYTE2_ADDRESS          ((uint32_t)0x40021002)

/* CFGR register byte 3 (Bits[31:23]) base address */
#define CFGR_BYTE3_ADDRESS        ((uint32_t)0x40021007)

/* CIR register byte 1 (Bits[15:8]) base address */
#define CIR_BYTE1_ADDRESS         ((uint32_t)0x40021009)

/* CIR register byte 2 (Bits[23:16]) base address */
#define CIR_BYTE2_ADDRESS         ((uint32_t)0x4002100A)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __I uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup RCC_Private_Functions
  * @{
  */

/** @defgroup RCC_Group1 Internal and external clocks, PLL, CSS and MCO configuration functions
 *  @brief   Internal and external clocks, PLL, CSS and MCO configuration functions 
 *
@verbatim
 ===============================================================================
 ##### Internal-external clocks, PLL, CSS and MCO configuration functions #####
 ===============================================================================
    [..] This section provides functions allowing to configure the internal/external clocks,
         PLL, CSS and MCO.
         (#) HSI (high-speed internal), 8 MHz factory-trimmed RC used directly 
             or through the PLL as System clock source.
             The HSI clock can be used also to clock the USART, I2C and CEC peripherals.
         (#) HSI14 (high-speed internal for ADC), 14 MHz factory-trimmed RC used to clock
             the ADC peripheral.
         (#) LSI (low-speed internal), 40 KHz low consumption RC used as IWDG and/or RTC
             clock source.
         (#) HSE (high-speed external), 4 to 32 MHz crystal oscillator used directly or
             through the PLL as System clock source. Can be used also as RTC clock source.
         (#) LSE (low-speed external), 32 KHz oscillator used as RTC clock source. 
             LSE can be used also to clock the USART and CEC peripherals.   
         (#) PLL (clocked by HSI or HSE), for System clock.
         (#) CSS (Clock security system), once enabled and if a HSE clock failure occurs 
             (HSE used directly or through PLL as System clock source), the System clock
             is automatically switched to HSI and an interrupt is generated if enabled. 
             The interrupt is linked to the Cortex-M0 NMI (Non-Maskable Interrupt) 
             exception vector.   
         (#) MCO (microcontroller clock output), used to output SYSCLK, HSI, HSI14, LSI,
             HSE, LSE or PLL (divided by 2) clock on PA8 pin.

@endverbatim
  * @{
  */

/**
  * @brief  Resets the RCC clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  * @note      HSI ON and used as system clock source 
  * @note      HSI14, HSE and PLL OFF
  * @note      AHB, APB prescaler set to 1.
  * @note      CSS and MCO OFF
  * @note      All interrupts disabled
  * @note   However, this function doesn't modify the configuration of the
  * @note      Peripheral clocks
  * @note      LSI, LSE and RTC clocks
  * @param  None
  * @retval None
  */
void RCC_DeInit(void)
{
  /* Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001;

  /* Reset SW[1:0], HPRE[3:0], PPRE[2:0], ADCPRE and MCOSEL[2:0] bits */
  RCC->CFGR &= (uint32_t)0xF8FFB80C;
  
  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* Reset PLLSRC, PLLXTPRE and PLLMUL[3:0] bits */
  RCC->CFGR &= (uint32_t)0xFFC0FFFF;

  /* Reset PREDIV1[3:0] bits */
  RCC->CFGR2 &= (uint32_t)0xFFFFFFF0;

  /* Reset USARTSW[1:0], I2CSW, CECSW and ADCSW bits */
  RCC->CFGR3 &= (uint32_t)0xFFFFFEAC;
  
  /* Reset HSI14 bit */
  RCC->CR2 &= (uint32_t)0xFFFFFFFE;

  /* Disable all interrupts */
  RCC->CIR = 0x00000000;
}

/**
  * @brief  Configures the External High Speed oscillator (HSE).
  * @note   After enabling the HSE (RCC_HSE_ON or RCC_HSE_Bypass), the application
  *           software should wait on HSERDY flag to be set indicating that HSE clock
  *           is stable and can be used to clock the PLL and/or system clock.
  *  @note    HSE state can not be changed if it is used directly or through the
  *           PLL as system clock. In this case, you have to select another source
  *           of the system clock then change the HSE state (ex. disable it).
  *  @note    The HSE is stopped by hardware when entering STOP and STANDBY modes.
  * @note   This function resets the CSSON bit, so if the Clock security system(CSS)
  *         was previously enabled you have to enable it again after calling this
  *         function.
  * @param RCC_HSE: specifies the new state of the HSE.
  *   This parameter can be one of the following values:
  *     @arg RCC_HSE_OFF: turn OFF the HSE oscillator, HSERDY flag goes low after
  *                       6 HSE oscillator clock cycles.
  *     @arg RCC_HSE_ON: turn ON the HSE oscillator
  *     @arg RCC_HSE_Bypass: HSE oscillator bypassed with external clock
  * @retval None
  */
void RCC_HSEConfig(uint8_t RCC_HSE)
{
  /* Check the parameters */
  assert_param(IS_RCC_HSE(RCC_HSE));

  /* Reset HSEON and HSEBYP bits before configuring the HSE ------------------*/
  *(__IO uint8_t *) CR_BYTE2_ADDRESS = RCC_HSE_OFF;

  /* Set the new HSE configuration -------------------------------------------*/
  *(__IO uint8_t *) CR_BYTE2_ADDRESS = RCC_HSE;

}

/**
  * @brief  Waits for HSE start-up.
  * @note   This function waits on HSERDY flag to be set and return SUCCESS if 
  *         this flag is set, otherwise returns ERROR if the timeout is reached 
  *         and this flag is not set. The timeout value is defined by the constant
  *         HSE_STARTUP_TIMEOUT in stm32f0xx.h file. You can tailor it depending
  *         on the HSE crystal used in your application.
  *         - The HSE is stopped by hardware when entering STOP and STANDBY modes.
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: HSE oscillator is stable and ready to use
  *          - ERROR: HSE oscillator not yet ready
  */
ErrorStatus RCC_WaitForHSEStartUp(void)
{
  __IO uint32_t StartUpCounter = 0;
  ErrorStatus status = ERROR;
  FlagStatus HSEStatus = RESET;
  
  /* Wait till HSE is ready and if timeout is reached exit */
  do
  {
    HSEStatus = RCC_GetFlagStatus(RCC_FLAG_HSERDY);
    StartUpCounter++;  
  } while((StartUpCounter != HSE_STARTUP_TIMEOUT) && (HSEStatus == RESET));
  
  if (RCC_GetFlagStatus(RCC_FLAG_HSERDY) != RESET)
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
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  *         Refer to the Application Note AN3300 for more details on how to  
  *         calibrate the HSI.
  * @param  HSICalibrationValue: specifies the HSI calibration trimming value.
  *         This parameter must be a number between 0 and 0x1F.
  * @retval None
  */
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_HSI_CALIBRATION_VALUE(HSICalibrationValue));
  
  tmpreg = RCC->CR;
  
  /* Clear HSITRIM[4:0] bits */
  tmpreg &= ~RCC_CR_HSITRIM;
  
  /* Set the HSITRIM[4:0] bits according to HSICalibrationValue value */
  tmpreg |= (uint32_t)HSICalibrationValue << 3;

  /* Store the new value */
  RCC->CR = tmpreg;
}

/**
  * @brief  Enables or disables the Internal High Speed oscillator (HSI).
  * @note     After enabling the HSI, the application software should wait on 
  *           HSIRDY flag to be set indicating that HSI clock is stable and can
  *           be used to clock the PLL and/or system clock.
  * @note     HSI can not be stopped if it is used directly or through the PLL
  *           as system clock. In this case, you have to select another source 
  *           of the system clock then stop the HSI.
  * @note     The HSI is stopped by hardware when entering STOP and STANDBY modes.
  * @param  NewState: new state of the HSI.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   When the HSI is stopped, HSIRDY flag goes low after 6 HSI oscillator
  *         clock cycles.
  * @retval None
  */
void RCC_HSICmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RCC->CR |= RCC_CR_HSION;
  }
  else
  {
    RCC->CR &= ~RCC_CR_HSION;
  }
}

/**
  * @brief  Adjusts the Internal High Speed oscillator for ADC (HSI14) 
  *         calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  *         Refer to the Application Note AN3300 for more details on how to  
  *         calibrate the HSI14.
  * @param  HSI14CalibrationValue: specifies the HSI14 calibration trimming value.
  *         This parameter must be a number between 0 and 0x1F.
  * @retval None
  */
void RCC_AdjustHSI14CalibrationValue(uint8_t HSI14CalibrationValue)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_HSI14_CALIBRATION_VALUE(HSI14CalibrationValue));
  
  tmpreg = RCC->CR2;
  
  /* Clear HSI14TRIM[4:0] bits */
  tmpreg &= ~RCC_CR2_HSI14TRIM;
  
  /* Set the HSITRIM14[4:0] bits according to HSI14CalibrationValue value */
  tmpreg |= (uint32_t)HSI14CalibrationValue << 3;

  /* Store the new value */
  RCC->CR2 = tmpreg;
}

/**
  * @brief  Enables or disables the Internal High Speed oscillator for ADC (HSI14).
  * @note     After enabling the HSI14, the application software should wait on 
  *           HSIRDY flag to be set indicating that HSI clock is stable and can
  *           be used to clock the ADC.
  * @note     The HSI14 is stopped by hardware when entering STOP and STANDBY modes.
  * @param  NewState: new state of the HSI14.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   When the HSI14 is stopped, HSI14RDY flag goes low after 6 HSI14 oscillator
  *         clock cycles.
  * @retval None
  */
void RCC_HSI14Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RCC->CR2 |= RCC_CR2_HSI14ON;
  }
  else
  {
    RCC->CR2 &= ~RCC_CR2_HSI14ON;
  }
}

/**
  * @brief  Enables or disables the Internal High Speed oscillator request from ADC.
  * @param  NewState: new state of the HSI14 ADC request.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_HSI14ADCRequestCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RCC->CR2 &= ~RCC_CR2_HSI14DIS;
  }
  else
  {
    RCC->CR2 |= RCC_CR2_HSI14DIS;
  }
}

/**
  * @brief  Configures the External Low Speed oscillator (LSE).
  * @note     As the LSE is in the Backup domain and write access is denied to this
  *           domain after reset, you have to enable write access using 
  *           PWR_BackupAccessCmd(ENABLE) function before to configure the LSE
  *           (to be done once after reset).
  * @note     After enabling the LSE (RCC_LSE_ON or RCC_LSE_Bypass), the application
  *           software should wait on LSERDY flag to be set indicating that LSE clock
  *           is stable and can be used to clock the RTC.
  * @param  RCC_LSE: specifies the new state of the LSE.
  *   This parameter can be one of the following values:
  *     @arg RCC_LSE_OFF: turn OFF the LSE oscillator, LSERDY flag goes low after
  *                       6 LSE oscillator clock cycles.
  *     @arg RCC_LSE_ON: turn ON the LSE oscillator
  *     @arg RCC_LSE_Bypass: LSE oscillator bypassed with external clock
  * @retval None
  */
void RCC_LSEConfig(uint32_t RCC_LSE)
{
  /* Check the parameters */
  assert_param(IS_RCC_LSE(RCC_LSE));

  /* Reset LSEON and LSEBYP bits before configuring the LSE ------------------*/
  /* Reset LSEON bit */
  RCC->BDCR &= ~(RCC_BDCR_LSEON);

  /* Reset LSEBYP bit */
  RCC->BDCR &= ~(RCC_BDCR_LSEBYP);

  /* Configure LSE */
  RCC->BDCR |= RCC_LSE;
}

/**
  * @brief  Configures the External Low Speed oscillator (LSE) drive capability.
  * @param  RCC_LSEDrive: specifies the new state of the LSE drive capability.
  *   This parameter can be one of the following values:
  *     @arg RCC_LSEDrive_Low: LSE oscillator low drive capability.
  *     @arg RCC_LSEDrive_MediumLow: LSE oscillator medium low drive capability.
  *     @arg RCC_LSEDrive_MediumHigh: LSE oscillator medium high drive capability.
  *     @arg RCC_LSEDrive_High: LSE oscillator high drive capability.
  * @retval None
  */
void RCC_LSEDriveConfig(uint32_t RCC_LSEDrive)
{
  /* Check the parameters */
  assert_param(IS_RCC_LSE_DRIVE(RCC_LSEDrive));
  
  /* Clear LSEDRV[1:0] bits */
  RCC->BDCR &= ~(RCC_BDCR_LSEDRV);

  /* Set the LSE Drive */
  RCC->BDCR |= RCC_LSEDrive;
}

/**
  * @brief  Enables or disables the Internal Low Speed oscillator (LSI).
  * @note     After enabling the LSI, the application software should wait on 
  *           LSIRDY flag to be set indicating that LSI clock is stable and can
  *           be used to clock the IWDG and/or the RTC.
  * @note     LSI can not be disabled if the IWDG is running.
  * @param  NewState: new state of the LSI.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   When the LSI is stopped, LSIRDY flag goes low after 6 LSI oscillator
  *         clock cycles.
  * @retval None
  */
void RCC_LSICmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RCC->CSR |= RCC_CSR_LSION;
  }
  else
  {
    RCC->CSR &= ~RCC_CSR_LSION;
  }
}

/**
  * @brief  Configures the PLL clock source and multiplication factor.
  * @note   This function must be used only when the PLL is disabled.
  *
  * @param  RCC_PLLSource: specifies the PLL entry clock source.
  *   This parameter can be one of the following values:
  *     @arg RCC_PLLSource_HSI_Div2: HSI oscillator clock selected as PLL clock source
  *     @arg RCC_PLLSource_PREDIV1: PREDIV1 clock selected as PLL clock entry
  * @note   The minimum input clock frequency for PLL is 2 MHz (when using HSE as
  *         PLL source).
  *
  * @param  RCC_PLLMul: specifies the PLL multiplication factor, which drive the PLLVCO clock
  *         This parameter can be RCC_PLLMul_x where x:[2,16] 
  *
  * @retval None
  */
void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul)
{
  /* Check the parameters */
  assert_param(IS_RCC_PLL_SOURCE(RCC_PLLSource));
  assert_param(IS_RCC_PLL_MUL(RCC_PLLMul));

  /* Clear PLL Source [16] and Multiplier [21:18] bits */
  RCC->CFGR &= ~(RCC_CFGR_PLLMULL | RCC_CFGR_PLLSRC);

  /* Set the PLL Source and Multiplier */
  RCC->CFGR |= (uint32_t)(RCC_PLLSource | RCC_PLLMul);
}

/**
  * @brief  Enables or disables the PLL.
  * @note   - After enabling the PLL, the application software should wait on 
  *           PLLRDY flag to be set indicating that PLL clock is stable and can
  *           be used as system clock source.
  *         - The PLL can not be disabled if it is used as system clock source
  *         - The PLL is disabled by hardware when entering STOP and STANDBY modes.
  * @param  NewState: new state of the PLL.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_PLLCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RCC->CR |= RCC_CR_PLLON;
  }
  else
  {
    RCC->CR &= ~RCC_CR_PLLON;
  }
}

/**
  * @brief  Configures the PREDIV1 division factor.
  * @note   This function must be used only when the PLL is disabled.
  * @param  RCC_PREDIV1_Div: specifies the PREDIV1 clock division factor.
  *         This parameter can be RCC_PREDIV1_Divx where x:[1,16]
  * @retval None
  */
void RCC_PREDIV1Config(uint32_t RCC_PREDIV1_Div)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_PREDIV1(RCC_PREDIV1_Div));

  tmpreg = RCC->CFGR2;
  /* Clear PREDIV1[3:0] bits */
  tmpreg &= ~(RCC_CFGR2_PREDIV1);
  /* Set the PREDIV1 division factor */
  tmpreg |= RCC_PREDIV1_Div;
  /* Store the new value */
  RCC->CFGR2 = tmpreg;
}

/**
  * @brief  Enables or disables the Clock Security System.
  * @note   If a failure is detected on the HSE oscillator clock, this oscillator
  *         is automatically disabled and an interrupt is generated to inform the
  *         software about the failure (Clock Security System Interrupt, CSSI),
  *         allowing the MCU to perform rescue operations. The CSSI is linked to 
  *         the Cortex-M0 NMI (Non-Maskable Interrupt) exception vector.
  * @param  NewState: new state of the Clock Security System.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_ClockSecuritySystemCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RCC->CR |= RCC_CR_CSSON;
  }
  else
  {
    RCC->CR &= ~RCC_CR_CSSON;
  }
}

/**
  * @brief  Selects the clock source to output on MCO pin (PA8).
  * @note   PA8 should be configured in alternate function mode.
  * @param  RCC_MCOSource: specifies the clock source to output.
  *   This parameter can be one of the following values:
  *     @arg RCC_MCOSource_NoClock: No clock selected.
  *     @arg RCC_MCOSource_HSI14: HSI14 oscillator clock selected.
  *     @arg RCC_MCOSource_LSI: LSI oscillator clock selected.
  *     @arg RCC_MCOSource_LSE: LSE oscillator clock selected.
  *     @arg RCC_MCOSource_SYSCLK: System clock selected.
  *     @arg RCC_MCOSource_HSI: HSI oscillator clock selected.
  *     @arg RCC_MCOSource_HSE: HSE oscillator clock selected.
  *     @arg RCC_MCOSource_PLLCLK_Div2: PLL clock divided by 2 selected.
  * @retval None
  */
void RCC_MCOConfig(uint8_t RCC_MCOSource)
{
  /* Check the parameters */
  assert_param(IS_RCC_MCO_SOURCE(RCC_MCOSource));
    
  /* Select MCO clock source and prescaler */
  *(__IO uint8_t *) CFGR_BYTE3_ADDRESS =  RCC_MCOSource;
}

/**
  * @}
  */

/** @defgroup RCC_Group2 System AHB and APB busses clocks configuration functions
 *  @brief   System, AHB and APB busses clocks configuration functions
 *
@verbatim
 ===============================================================================
     ##### System, AHB and APB busses clocks configuration functions #####
 ===============================================================================

    [..] This section provide functions allowing to configure the System, AHB and 
         APB busses clocks.
         (#) Several clock sources can be used to drive the System clock (SYSCLK): HSI,
             HSE and PLL.
             The AHB clock (HCLK) is derived from System clock through configurable prescaler
             and used to clock the CPU, memory and peripherals mapped on AHB bus (DMA and GPIO).
             and APB (PCLK) clocks are derived from AHB clock through 
             configurable prescalers and used to clock the peripherals mapped on these busses.
             You can use "RCC_GetClocksFreq()" function to retrieve the frequencies of these clocks.

         -@- All the peripheral clocks are derived from the System clock (SYSCLK) except:
             (+@) The ADC clock which is derived from HSI14 or APB (APB divided by a
                  programmable prescaler: 2 or 4).
             (+@) The CEC clock which is derived from LSE or HSI divided by 244.
             (+@) The I2C clock which is derived from HSI or system clock (SYSCLK).
             (+@) The USART clock which is derived from HSI, system clock (SYSCLK), APB or LSE.
             (+@) The RTC/LCD clock which is derived from the LSE, LSI or 2 MHz HSE_RTC (HSE
                  divided by a programmable prescaler).
                  The System clock (SYSCLK) frequency must be higher or equal to the RTC/LCD
                  clock frequency.
             (+@) IWDG clock which is always the LSI clock.
       
         (#) The maximum frequency of the SYSCLK, HCLK and PCLK is 48 MHz.
             Depending on the maximum frequency, the FLASH wait states (WS) should be 
             adapted accordingly:
        +--------------------------------------------- +
        |  Wait states  |   HCLK clock frequency (MHz) |
        |---------------|------------------------------|
        |0WS(1CPU cycle)|       0 < HCLK <= 24         |
        |---------------|------------------------------|
        |1WS(2CPU cycle)|       24 < HCLK <= 48        |
        +----------------------------------------------+

         (#) After reset, the System clock source is the HSI (8 MHz) with 0 WS and 
             prefetch is disabled.
  
    [..] It is recommended to use the following software sequences to tune the number
         of wait states needed to access the Flash memory with the CPU frequency (HCLK).
         (+) Increasing the CPU frequency
         (++) Program the Flash Prefetch buffer, using "FLASH_PrefetchBufferCmd(ENABLE)" 
              function
         (++) Check that Flash Prefetch buffer activation is taken into account by 
              reading FLASH_ACR using the FLASH_GetPrefetchBufferStatus() function
         (++) Program Flash WS to 1, using "FLASH_SetLatency(FLASH_Latency_1)" function
         (++) Check that the new number of WS is taken into account by reading FLASH_ACR
         (++) Modify the CPU clock source, using "RCC_SYSCLKConfig()" function
         (++) If needed, modify the CPU clock prescaler by using "RCC_HCLKConfig()" function
         (++) Check that the new CPU clock source is taken into account by reading 
              the clock source status, using "RCC_GetSYSCLKSource()" function 
         (+) Decreasing the CPU frequency
         (++) Modify the CPU clock source, using "RCC_SYSCLKConfig()" function
         (++) If needed, modify the CPU clock prescaler by using "RCC_HCLKConfig()" function
         (++) Check that the new CPU clock source is taken into account by reading 
              the clock source status, using "RCC_GetSYSCLKSource()" function
         (++) Program the new number of WS, using "FLASH_SetLatency()" function
         (++) Check that the new number of WS is taken into account by reading FLASH_ACR
         (++) Disable the Flash Prefetch buffer using "FLASH_PrefetchBufferCmd(DISABLE)" 
              function
         (++) Check that Flash Prefetch buffer deactivation is taken into account by reading FLASH_ACR
              using the FLASH_GetPrefetchBufferStatus() function.

@endverbatim
  * @{
  */

/**
  * @brief  Configures the system clock (SYSCLK).
  * @note    The HSI is used (enabled by hardware) as system clock source after
  *           startup from Reset, wake-up from STOP and STANDBY mode, or in case
  *           of failure of the HSE used directly or indirectly as system clock
  *           (if the Clock Security System CSS is enabled).
  * @note     A switch from one clock source to another occurs only if the target
  *           clock source is ready (clock stable after startup delay or PLL locked). 
  *           If a clock source which is not yet ready is selected, the switch will
  *           occur when the clock source will be ready. 
  *           You can use RCC_GetSYSCLKSource() function to know which clock is
  *           currently used as system clock source.  
  * @param  RCC_SYSCLKSource: specifies the clock source used as system clock source 
  *   This parameter can be one of the following values:
  *     @arg RCC_SYSCLKSource_HSI:    HSI selected as system clock source
  *     @arg RCC_SYSCLKSource_HSE:    HSE selected as system clock source
  *     @arg RCC_SYSCLKSource_PLLCLK: PLL selected as system clock source
  * @retval None
  */
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_SYSCLK_SOURCE(RCC_SYSCLKSource));
  
  tmpreg = RCC->CFGR;
  
  /* Clear SW[1:0] bits */
  tmpreg &= ~RCC_CFGR_SW;
  
  /* Set SW[1:0] bits according to RCC_SYSCLKSource value */
  tmpreg |= RCC_SYSCLKSource;
  
  /* Store the new value */
  RCC->CFGR = tmpreg;
}

/**
  * @brief  Returns the clock source used as system clock.
  * @param  None
  * @retval The clock source used as system clock. The returned value can be one 
  *         of the following values:
  *              - 0x00: HSI used as system clock
  *              - 0x04: HSE used as system clock  
  *              - 0x08: PLL used as system clock
  */
uint8_t RCC_GetSYSCLKSource(void)
{
  return ((uint8_t)(RCC->CFGR & RCC_CFGR_SWS));
}

/**
  * @brief  Configures the AHB clock (HCLK).
  * @param  RCC_SYSCLK: defines the AHB clock divider. This clock is derived from 
  *                     the system clock (SYSCLK).
  *   This parameter can be one of the following values:
  *     @arg RCC_SYSCLK_Div1:   AHB clock = SYSCLK
  *     @arg RCC_SYSCLK_Div2:   AHB clock = SYSCLK/2
  *     @arg RCC_SYSCLK_Div4:   AHB clock = SYSCLK/4
  *     @arg RCC_SYSCLK_Div8:   AHB clock = SYSCLK/8
  *     @arg RCC_SYSCLK_Div16:  AHB clock = SYSCLK/16
  *     @arg RCC_SYSCLK_Div64:  AHB clock = SYSCLK/64
  *     @arg RCC_SYSCLK_Div128: AHB clock = SYSCLK/128
  *     @arg RCC_SYSCLK_Div256: AHB clock = SYSCLK/256
  *     @arg RCC_SYSCLK_Div512: AHB clock = SYSCLK/512
  * @retval None
  */
void RCC_HCLKConfig(uint32_t RCC_SYSCLK)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_HCLK(RCC_SYSCLK));
  
  tmpreg = RCC->CFGR;
  
  /* Clear HPRE[3:0] bits */
  tmpreg &= ~RCC_CFGR_HPRE;
  
  /* Set HPRE[3:0] bits according to RCC_SYSCLK value */
  tmpreg |= RCC_SYSCLK;
  
  /* Store the new value */
  RCC->CFGR = tmpreg;
}

/**
  * @brief  Configures the APB clock (PCLK).
  * @param  RCC_HCLK: defines the APB clock divider. This clock is derived from 
  *         the AHB clock (HCLK).
  *   This parameter can be one of the following values:
  *     @arg RCC_HCLK_Div1: APB clock = HCLK
  *     @arg RCC_HCLK_Div2: APB clock = HCLK/2
  *     @arg RCC_HCLK_Div4: APB clock = HCLK/4
  *     @arg RCC_HCLK_Div8: APB clock = HCLK/8
  *     @arg RCC_HCLK_Div16: APB clock = HCLK/16
  * @retval None
  */
void RCC_PCLKConfig(uint32_t RCC_HCLK)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_PCLK(RCC_HCLK));
  
  tmpreg = RCC->CFGR;
  
  /* Clear PPRE[2:0] bits */
  tmpreg &= ~RCC_CFGR_PPRE;
  
  /* Set PPRE[2:0] bits according to RCC_HCLK value */
  tmpreg |= RCC_HCLK;
  
  /* Store the new value */
  RCC->CFGR = tmpreg;
}

/**
  * @brief  Configures the ADC clock (ADCCLK).
  * @param  RCC_ADCCLK: defines the ADC clock source. This clock is derived 
  *         from the HSI14 or APB clock (PCLK).
  *         This parameter can be one of the following values:
  *             @arg RCC_ADCCLK_HSI14: ADC clock = HSI14 (14MHz)
  *             @arg RCC_ADCCLK_PCLK_Div2: ADC clock = PCLK/2
  *             @arg RCC_ADCCLK_PCLK_Div4: ADC clock = PCLK/4  
  * @retval None
  */
void RCC_ADCCLKConfig(uint32_t RCC_ADCCLK)
{ 
  /* Check the parameters */
  assert_param(IS_RCC_ADCCLK(RCC_ADCCLK));

  /* Clear ADCPRE bit */
  RCC->CFGR &= ~RCC_CFGR_ADCPRE;
  /* Set ADCPRE bits according to RCC_PCLK value */
  RCC->CFGR |= RCC_ADCCLK & 0xFFFF;

  /* Clear ADCSW bit */
  RCC->CFGR3 &= ~RCC_CFGR3_ADCSW; 
  /* Set ADCSW bits according to RCC_ADCCLK value */
  RCC->CFGR3 |= RCC_ADCCLK >> 16;  
}

/**
  * @brief  Configures the CEC clock (CECCLK).
  * @param  RCC_CECCLK: defines the CEC clock source. This clock is derived 
  *         from the HSI or LSE clock.
  *         This parameter can be one of the following values:
  *             @arg RCC_CECCLK_HSI_Div244: CEC clock = HSI/244 (32768Hz)
  *             @arg RCC_CECCLK_LSE: CEC clock = LSE
  * @retval None
  */
void RCC_CECCLKConfig(uint32_t RCC_CECCLK)
{ 
  /* Check the parameters */
  assert_param(IS_RCC_CECCLK(RCC_CECCLK));

  /* Clear CECSW bit */
  RCC->CFGR3 &= ~RCC_CFGR3_CECSW;
  /* Set CECSW bits according to RCC_CECCLK value */
  RCC->CFGR3 |= RCC_CECCLK;
}

/**
  * @brief  Configures the I2C1 clock (I2C1CLK).
  * @param  RCC_I2CCLK: defines the I2C1 clock source. This clock is derived 
  *         from the HSI or System clock.
  *         This parameter can be one of the following values:
  *             @arg RCC_I2C1CLK_HSI: I2C1 clock = HSI
  *             @arg RCC_I2C1CLK_SYSCLK: I2C1 clock = System Clock
  * @retval None
  */
void RCC_I2CCLKConfig(uint32_t RCC_I2CCLK)
{ 
  /* Check the parameters */
  assert_param(IS_RCC_I2CCLK(RCC_I2CCLK));

  /* Clear I2CSW bit */
  RCC->CFGR3 &= ~RCC_CFGR3_I2C1SW;
  /* Set I2CSW bits according to RCC_I2CCLK value */
  RCC->CFGR3 |= RCC_I2CCLK;
}

/**
  * @brief  Configures the USART1 clock (USART1CLK).
  * @param  RCC_USARTCLK: defines the USART1 clock source. This clock is derived 
  *         from the HSI or System clock.
  *         This parameter can be one of the following values:
  *             @arg RCC_USART1CLK_PCLK: USART1 clock = APB Clock (PCLK)
  *             @arg RCC_USART1CLK_SYSCLK: USART1 clock = System Clock
  *             @arg RCC_USART1CLK_LSE: USART1 clock = LSE Clock
  *             @arg RCC_USART1CLK_HSI: USART1 clock = HSI Clock
  * @retval None
  */
void RCC_USARTCLKConfig(uint32_t RCC_USARTCLK)
{ 
  /* Check the parameters */
  assert_param(IS_RCC_USARTCLK(RCC_USARTCLK));

  /* Clear USARTSW[1:0] bit */
  RCC->CFGR3 &= ~RCC_CFGR3_USART1SW;
  /* Set USARTSW bits according to RCC_USARTCLK value */
  RCC->CFGR3 |= RCC_USARTCLK;
}

/**
  * @brief  Returns the frequencies of the System, AHB and APB busses clocks.
  * @note    The frequency returned by this function is not the real frequency
  *           in the chip. It is calculated based on the predefined constant and
  *           the source selected by RCC_SYSCLKConfig():
  *                                              
  * @note     If SYSCLK source is HSI, function returns constant HSI_VALUE(*)
  *                                              
  * @note     If SYSCLK source is HSE, function returns constant HSE_VALUE(**)
  *                          
  * @note     If SYSCLK source is PLL, function returns constant HSE_VALUE(**) 
  *             or HSI_VALUE(*) multiplied by the PLL factors.
  *         
  *         (*) HSI_VALUE is a constant defined in stm32f0xx.h file (default value
  *             8 MHz) but the real value may vary depending on the variations
  *             in voltage and temperature, refer to RCC_AdjustHSICalibrationValue().   
  *    
  *         (**) HSE_VALUE is a constant defined in stm32f0xx.h file (default value
  *              8 MHz), user has to ensure that HSE_VALUE is same as the real
  *              frequency of the crystal used. Otherwise, this function may
  *              return wrong result.
  *                
  *         - The result of this function could be not correct when using fractional
  *           value for HSE crystal.   
  *             
  * @param  RCC_Clocks: pointer to a RCC_ClocksTypeDef structure which will hold 
  *         the clocks frequencies. 
  *     
  * @note     This function can be used by the user application to compute the 
  *           baudrate for the communication peripherals or configure other parameters.
  * @note     Each time SYSCLK, HCLK and/or PCLK clock changes, this function
  *           must be called to update the structure's field. Otherwise, any
  *           configuration based on this function will be incorrect.
  *    
  * @retval None
  */
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks)
{
  uint32_t tmp = 0, pllmull = 0, pllsource = 0, prediv1factor = 0, presc = 0;

  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->CFGR & RCC_CFGR_SWS;
  
  switch (tmp)
  {
    case 0x00:  /* HSI used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
      break;
    case 0x04:  /* HSE used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSE_VALUE;
      break;
    case 0x08:  /* PLL used as system clock */
      /* Get PLL clock source and multiplication factor ----------------------*/
      pllmull = RCC->CFGR & RCC_CFGR_PLLMULL;
      pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;
      pllmull = ( pllmull >> 18) + 2;
      
      if (pllsource == 0x00)
      {
        /* HSI oscillator clock divided by 2 selected as PLL clock entry */
        RCC_Clocks->SYSCLK_Frequency = (HSI_VALUE >> 1) * pllmull;
      }
      else
      {
        prediv1factor = (RCC->CFGR2 & RCC_CFGR2_PREDIV1) + 1;
        /* HSE oscillator clock selected as PREDIV1 clock entry */
        RCC_Clocks->SYSCLK_Frequency = (HSE_VALUE / prediv1factor) * pllmull; 
      }      
      break;
    default: /* HSI used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
      break;
  }
  /* Compute HCLK, PCLK clocks frequencies -----------------------------------*/
  /* Get HCLK prescaler */
  tmp = RCC->CFGR & RCC_CFGR_HPRE;
  tmp = tmp >> 4;
  presc = APBAHBPrescTable[tmp]; 
  /* HCLK clock frequency */
  RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;

  /* Get PCLK prescaler */
  tmp = RCC->CFGR & RCC_CFGR_PPRE;
  tmp = tmp >> 8;
  presc = APBAHBPrescTable[tmp];
  /* PCLK clock frequency */
  RCC_Clocks->PCLK_Frequency = RCC_Clocks->HCLK_Frequency >> presc;

  /* ADCCLK clock frequency */
  if((RCC->CFGR3 & RCC_CFGR3_ADCSW) != RCC_CFGR3_ADCSW)
  {
    /* ADC Clock is HSI14 Osc. */
    RCC_Clocks->ADCCLK_Frequency = HSI14_VALUE;
  }
  else
  {
    if((RCC->CFGR & RCC_CFGR_ADCPRE) != RCC_CFGR_ADCPRE)
    {
      /* ADC Clock is derived from PCLK/2 */
      RCC_Clocks->ADCCLK_Frequency = RCC_Clocks->PCLK_Frequency >> 1;
    }
    else
    {
      /* ADC Clock is derived from PCLK/4 */
      RCC_Clocks->ADCCLK_Frequency = RCC_Clocks->PCLK_Frequency >> 2;
    }
    
  }

  /* CECCLK clock frequency */
  if((RCC->CFGR3 & RCC_CFGR3_CECSW) != RCC_CFGR3_CECSW)
  {
    /* CEC Clock is HSI/256 */
    RCC_Clocks->CECCLK_Frequency = HSI_VALUE / 244;
  }
  else
  {
    /* CECC Clock is LSE Osc. */
    RCC_Clocks->CECCLK_Frequency = LSE_VALUE;
  }

  /* I2C1CLK clock frequency */
  if((RCC->CFGR3 & RCC_CFGR3_I2C1SW) != RCC_CFGR3_I2C1SW)
  {
    /* I2C1 Clock is HSI Osc. */
    RCC_Clocks->I2C1CLK_Frequency = HSI_VALUE;
  }
  else
  {
    /* I2C1 Clock is System Clock */
    RCC_Clocks->I2C1CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
  }

  /* USART1CLK clock frequency */
  if((RCC->CFGR3 & RCC_CFGR3_USART1SW) == 0x0)
  {
    /* USART1 Clock is PCLK */
    RCC_Clocks->USART1CLK_Frequency = RCC_Clocks->PCLK_Frequency;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_USART1SW) == RCC_CFGR3_USART1SW_0)
  {
    /* USART1 Clock is System Clock */
    RCC_Clocks->USART1CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_USART1SW) == RCC_CFGR3_USART1SW_1)
  {
    /* USART1 Clock is LSE Osc. */
    RCC_Clocks->USART1CLK_Frequency = LSE_VALUE;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_USART1SW) == RCC_CFGR3_USART1SW)
  {
    /* USART1 Clock is HSI Osc. */
    RCC_Clocks->USART1CLK_Frequency = HSI_VALUE;
  }

}


/**
  * @}
  */

/** @defgroup RCC_Group3 Peripheral clocks configuration functions
 *  @brief   Peripheral clocks configuration functions 
 *
@verbatim
 ===============================================================================
             #####Peripheral clocks configuration functions #####
 ===============================================================================  

    [..] This section provide functions allowing to configure the Peripheral clocks. 
         (#) The RTC clock which is derived from the LSE, LSI or  HSE_Div32 (HSE
             divided by 32).
         (#) After restart from Reset or wakeup from STANDBY, all peripherals are off
             except internal SRAM, Flash and SWD. Before to start using a peripheral you
             have to enable its interface clock. You can do this using RCC_AHBPeriphClockCmd(),
             RCC_APB2PeriphClockCmd() and RCC_APB1PeriphClockCmd() functions.
         (#) To reset the peripherals configuration (to the default state after device reset)
             you can use RCC_AHBPeriphResetCmd(), RCC_APB2PeriphResetCmd() and 
             RCC_APB1PeriphResetCmd() functions.

@endverbatim
  * @{
  */

/**
  * @brief  Configures the RTC clock (RTCCLK).
  * @note     As the RTC clock configuration bits are in the Backup domain and write
  *           access is denied to this domain after reset, you have to enable write
  *           access using PWR_BackupAccessCmd(ENABLE) function before to configure
  *           the RTC clock source (to be done once after reset).    
  * @note     Once the RTC clock is configured it can't be changed unless the RTC
  *           is reset using RCC_BackupResetCmd function, or by a Power On Reset (POR)
  *             
  * @param  RCC_RTCCLKSource: specifies the RTC clock source.
  *   This parameter can be one of the following values:
  *     @arg RCC_RTCCLKSource_LSE: LSE selected as RTC clock
  *     @arg RCC_RTCCLKSource_LSI: LSI selected as RTC clock
  *     @arg RCC_RTCCLKSource_HSE_Div32: HSE divided by 32 selected as RTC clock
  *       
  * @note     If the LSE or LSI is used as RTC clock source, the RTC continues to
  *           work in STOP and STANDBY modes, and can be used as wakeup source.
  *           However, when the HSE clock is used as RTC clock source, the RTC
  *           cannot be used in STOP and STANDBY modes.
  *             
  * @note     The maximum input clock frequency for RTC is 2MHz (when using HSE as
  *           RTC clock source).
  *                          
  * @retval None
  */
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource)
{
  /* Check the parameters */
  assert_param(IS_RCC_RTCCLK_SOURCE(RCC_RTCCLKSource));
  
  /* Select the RTC clock source */
  RCC->BDCR |= RCC_RTCCLKSource;
}

/**
  * @brief  Enables or disables the RTC clock.
  * @note   This function must be used only after the RTC clock source was selected
  *         using the RCC_RTCCLKConfig function.
  * @param  NewState: new state of the RTC clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_RTCCLKCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RCC->BDCR |= RCC_BDCR_RTCEN;
  }
  else
  {
    RCC->BDCR &= ~RCC_BDCR_RTCEN;
  }
}

/**
  * @brief  Forces or releases the Backup domain reset.
  * @note   This function resets the RTC peripheral (including the backup registers)
  *         and the RTC clock source selection in RCC_BDCR register.
  * @param  NewState: new state of the Backup domain reset.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_BackupResetCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RCC->BDCR |= RCC_BDCR_BDRST;
  }
  else
  {
    RCC->BDCR &= ~RCC_BDCR_BDRST;
  }
}

/**
  * @brief  Enables or disables the AHB peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.    
  * @param  RCC_AHBPeriph: specifies the AHB peripheral to gates its clock.
  *         This parameter can be any combination of the following values:
  *             @arg RCC_AHBPeriph_GPIOA:         GPIOA clock
  *             @arg RCC_AHBPeriph_GPIOB:         GPIOB clock
  *             @arg RCC_AHBPeriph_GPIOC:         GPIOC clock
  *             @arg RCC_AHBPeriph_GPIOD:         GPIOD clock
  *             @arg RCC_AHBPeriph_GPIOF:         GPIOF clock
  *             @arg RCC_AHBPeriph_TS:            TS clock
  *             @arg RCC_AHBPeriph_CRC:           CRC clock
  *             @arg RCC_AHBPeriph_FLITF: (has effect only when the Flash memory is in power down mode)  
  *             @arg RCC_AHBPeriph_SRAM:          SRAM clock
  *             @arg RCC_AHBPeriph_DMA1:          DMA1 clock
  * @param  NewState: new state of the specified peripheral clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_AHB_PERIPH(RCC_AHBPeriph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RCC->AHBENR |= RCC_AHBPeriph;
  }
  else
  {
    RCC->AHBENR &= ~RCC_AHBPeriph;
  }
}

/**
  * @brief  Enables or disables the High Speed APB (APB2) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to gates its clock.
  *         This parameter can be any combination of the following values:
  *             @arg RCC_APB2Periph_SYSCFG:      SYSCFG clock
  *             @arg RCC_APB2Periph_ADC1:        ADC1 clock
  *             @arg RCC_APB2Periph_TIM1:        TIM1 clock
  *             @arg RCC_APB2Periph_SPI1:        SPI1 clock
  *             @arg RCC_APB2Periph_USART1:      USART1 clock
  *             @arg RCC_APB2Periph_TIM15:       TIM15 clock
  *             @arg RCC_APB2Periph_TIM16:       TIM16 clock
  *             @arg RCC_APB2Periph_TIM17:       TIM17 clock
  *             @arg RCC_APB2Periph_DBGMCU:      DBGMCU clock
  * @param  NewState: new state of the specified peripheral clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB2ENR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2ENR &= ~RCC_APB2Periph;
  }
}

/**
  * @brief  Enables or disables the Low Speed APB (APB1) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.
  * @param  RCC_APB1Periph: specifies the APB1 peripheral to gates its clock.
  *         This parameter can be any combination of the following values:
  *           @arg RCC_APB1Periph_TIM2:      TIM2 clock
  *           @arg RCC_APB1Periph_TIM3:      TIM3 clock
  *           @arg RCC_APB1Periph_TIM6:      TIM6 clock
  *           @arg RCC_APB1Periph_TIM14:     TIM14 clock
  *           @arg RCC_APB1Periph_WWDG:      WWDG clock
  *           @arg RCC_APB1Periph_SPI2:      SPI2 clock
  *           @arg RCC_APB1Periph_USART2:    USART2 clock
  *           @arg RCC_APB1Periph_I2C1:      I2C1 clock
  *           @arg RCC_APB1Periph_I2C2:      I2C2 clock
  *           @arg RCC_APB1Periph_PWR:       PWR clock
  *           @arg RCC_APB1Periph_DAC:       DAC clock
  *           @arg RCC_APB1Periph_CEC:       CEC clock                               
  * @param  NewState: new state of the specified peripheral clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB1ENR |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1ENR &= ~RCC_APB1Periph;
  }
}

/**
  * @brief  Forces or releases AHB peripheral reset.
  * @param  RCC_AHBPeriph: specifies the AHB peripheral to reset.
  *         This parameter can be any combination of the following values:
  *             @arg RCC_AHBPeriph_GPIOA:         GPIOA clock
  *             @arg RCC_AHBPeriph_GPIOB:         GPIOB clock
  *             @arg RCC_AHBPeriph_GPIOC:         GPIOC clock
  *             @arg RCC_AHBPeriph_GPIOD:         GPIOD clock
  *             @arg RCC_AHBPeriph_GPIOF:         GPIOF clock
  *             @arg RCC_AHBPeriph_TS:            TS clock
  * @param  NewState: new state of the specified peripheral reset.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_AHB_RST_PERIPH(RCC_AHBPeriph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->AHBRSTR |= RCC_AHBPeriph;
  }
  else
  {
    RCC->AHBRSTR &= ~RCC_AHBPeriph;
  }
}

/**
  * @brief  Forces or releases High Speed APB (APB2) peripheral reset.
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to reset.
  *         This parameter can be any combination of the following values:
  *             @arg RCC_APB2Periph_SYSCFG:      SYSCFG clock
  *             @arg RCC_APB2Periph_ADC1:        ADC1 clock
  *             @arg RCC_APB2Periph_TIM1:        TIM1 clock
  *             @arg RCC_APB2Periph_SPI1:        SPI1 clock
  *             @arg RCC_APB2Periph_USART1:      USART1 clock
  *             @arg RCC_APB2Periph_TIM15:       TIM15 clock
  *             @arg RCC_APB2Periph_TIM16:       TIM16 clock
  *             @arg RCC_APB2Periph_TIM17:       TIM17 clock
  *             @arg RCC_APB2Periph_DBGMCU:      DBGMCU clock
  * @param  NewState: new state of the specified peripheral reset.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB2RSTR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2RSTR &= ~RCC_APB2Periph;
  }
}

/**
  * @brief  Forces or releases Low Speed APB (APB1) peripheral reset.
  * @param  RCC_APB1Periph: specifies the APB1 peripheral to reset.
  *         This parameter can be any combination of the following values:
  *           @arg RCC_APB1Periph_TIM2:      TIM2 clock
  *           @arg RCC_APB1Periph_TIM3:      TIM3 clock
  *           @arg RCC_APB1Periph_TIM6:      TIM6 clock
  *           @arg RCC_APB1Periph_TIM14:     TIM14 clock
  *           @arg RCC_APB1Periph_WWDG:      WWDG clock
  *           @arg RCC_APB1Periph_SPI2:      SPI2 clock
  *           @arg RCC_APB1Periph_USART2:    USART2 clock
  *           @arg RCC_APB1Periph_I2C1:      I2C1 clock
  *           @arg RCC_APB1Periph_I2C2:      I2C2 clock
  *           @arg RCC_APB1Periph_PWR:       PWR clock
  *           @arg RCC_APB1Periph_DAC:       DAC clock
  *           @arg RCC_APB1Periph_CEC:       CEC clock
  * @param  NewState: new state of the specified peripheral clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB1RSTR |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1RSTR &= ~RCC_APB1Periph;
  }
}

/**
  * @}
  */

/** @defgroup RCC_Group4 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions 
 *
@verbatim
 ===============================================================================
             ##### Interrupts and flags management functions #####
 ===============================================================================
@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified RCC interrupts.
  * @note   The CSS interrupt doesn't have an enable bit; once the CSS is enabled
  *         and if the HSE clock fails, the CSS interrupt occurs and an NMI is
  *         automatically generated. The NMI will be executed indefinitely, and 
  *         since NMI has higher priority than any other IRQ (and main program)
  *         the application will be stacked in the NMI ISR unless the CSS interrupt
  *         pending bit is cleared.
  * @param  RCC_IT: specifies the RCC interrupt sources to be enabled or disabled.
  *         This parameter can be any combination of the following values:
  *              @arg RCC_IT_LSIRDY: LSI ready interrupt
  *              @arg RCC_IT_LSERDY: LSE ready interrupt
  *              @arg RCC_IT_HSIRDY: HSI ready interrupt
  *              @arg RCC_IT_HSERDY: HSE ready interrupt
  *              @arg RCC_IT_PLLRDY: PLL ready interrupt
  *              @arg RCC_IT_HSI14RDY: HSI14 ready interrupt
  * @param  NewState: new state of the specified RCC interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_IT(RCC_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Perform Byte access to RCC_CIR[13:8] bits to enable the selected interrupts */
    *(__IO uint8_t *) CIR_BYTE1_ADDRESS |= RCC_IT;
  }
  else
  {
    /* Perform Byte access to RCC_CIR[13:8] bits to disable the selected interrupts */
    *(__IO uint8_t *) CIR_BYTE1_ADDRESS &= (uint8_t)~RCC_IT;
  }
}

/**
  * @brief  Checks whether the specified RCC flag is set or not.
  * @param  RCC_FLAG: specifies the flag to check.
  *         This parameter can be one of the following values:
  *             @arg RCC_FLAG_HSIRDY: HSI oscillator clock ready  
  *             @arg RCC_FLAG_HSERDY: HSE oscillator clock ready
  *             @arg RCC_FLAG_PLLRDY: PLL clock ready
  *             @arg RCC_FLAG_LSERDY: LSE oscillator clock ready
  *             @arg RCC_FLAG_LSIRDY: LSI oscillator clock ready
  *             @arg RCC_FLAG_OBLRST: Option Byte Loader (OBL) reset 
  *             @arg RCC_FLAG_PINRST: Pin reset
  *             @arg RCC_FLAG_V18PWRRSTF:  V1.8 power domain reset  
  *             @arg RCC_FLAG_PORRST: POR/PDR reset
  *             @arg RCC_FLAG_SFTRST: Software reset
  *             @arg RCC_FLAG_IWDGRST: Independent Watchdog reset
  *             @arg RCC_FLAG_WWDGRST: Window Watchdog reset
  *             @arg RCC_FLAG_LPWRRST: Low Power reset
  *             @arg RCC_FLAG_HSI14RDY: HSI14 oscillator clock ready  
  * @retval The new state of RCC_FLAG (SET or RESET).
  */
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG)
{
  uint32_t tmp = 0;
  uint32_t statusreg = 0;
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_RCC_FLAG(RCC_FLAG));

  /* Get the RCC register index */
  tmp = RCC_FLAG >> 5;

  if (tmp == 0)               /* The flag to check is in CR register */
  {
    statusreg = RCC->CR;
  }
  else if (tmp == 1)          /* The flag to check is in BDCR register */
  {
    statusreg = RCC->BDCR;
  }
  else if (tmp == 2)          /* The flag to check is in CSR register */
  {
    statusreg = RCC->CSR;
  }
  else                        /* The flag to check is in CR2 register */
  {
    statusreg = RCC->CR2;
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
  *         The reset flags are: RCC_FLAG_OBLRST, RCC_FLAG_PINRST, RCC_FLAG_V18PWRRSTF,
  *         RCC_FLAG_PORRST, RCC_FLAG_SFTRST, RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST,
  *         RCC_FLAG_LPWRRST.
  * @param  None
  * @retval None
  */
void RCC_ClearFlag(void)
{
  /* Set RMVF bit to clear the reset flags */
  RCC->CSR |= RCC_CSR_RMVF;
}

/**
  * @brief  Checks whether the specified RCC interrupt has occurred or not.
  * @param  RCC_IT: specifies the RCC interrupt source to check.
  *         This parameter can be one of the following values:
  *             @arg RCC_IT_LSIRDY: LSI ready interrupt
  *             @arg RCC_IT_LSERDY: LSE ready interrupt
  *             @arg RCC_IT_HSIRDY: HSI ready interrupt
  *             @arg RCC_IT_HSERDY: HSE ready interrupt
  *             @arg RCC_IT_PLLRDY: PLL ready interrupt
  *             @arg RCC_IT_HSI14RDY: HSI14 ready interrupt 
  *             @arg RCC_IT_CSS: Clock Security System interrupt
  * @retval The new state of RCC_IT (SET or RESET).
  */
ITStatus RCC_GetITStatus(uint8_t RCC_IT)
{
  ITStatus bitstatus = RESET;
  
  /* Check the parameters */
  assert_param(IS_RCC_GET_IT(RCC_IT));
  
  /* Check the status of the specified RCC interrupt */
  if ((RCC->CIR & RCC_IT) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the RCC_IT status */
  return  bitstatus;
}

/**
  * @brief  Clears the RCC's interrupt pending bits.
  * @param  RCC_IT: specifies the interrupt pending bit to clear.
  *         This parameter can be any combination of the following values:
  *             @arg RCC_IT_LSIRDY: LSI ready interrupt
  *             @arg RCC_IT_LSERDY: LSE ready interrupt
  *             @arg RCC_IT_HSIRDY: HSI ready interrupt
  *             @arg RCC_IT_HSERDY: HSE ready interrupt
  *             @arg RCC_IT_PLLRDY: PLL ready interrupt
  *             @arg RCC_IT_HSI14RDY: HSI14 ready interrupt  
  *             @arg RCC_IT_CSS: Clock Security System interrupt
  * @retval None
  */
void RCC_ClearITPendingBit(uint8_t RCC_IT)
{
  /* Check the parameters */
  assert_param(IS_RCC_CLEAR_IT(RCC_IT));
  
  /* Perform Byte access to RCC_CIR[23:16] bits to clear the selected interrupt
     pending bits */
  *(__IO uint8_t *) CIR_BYTE2_ADDRESS = RCC_IT;
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

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
