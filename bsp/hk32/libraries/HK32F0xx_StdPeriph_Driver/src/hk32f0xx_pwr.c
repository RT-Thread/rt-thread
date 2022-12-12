/**
  ******************************************************************************
  * @file    hk32f0xx_pwr.c
  * @version V1.0.1
  * @date    2019-08-15
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hk32f0xx_pwr.h"
#include "hk32f0xx_rcc.h"

/** @addtogroup HK32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup PWR
  * @brief PWR driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* ------------------ PWR registers bit mask ------------------------ */

/* CR register bit mask */
#define CR_DS_MASK               ((uint32_t)0xFFFFFFFC)
#define CR_PLS_MASK              ((uint32_t)0xFFFFFF1F)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup PWR_Private_Functions
  * @{
  */

/** @defgroup PWR_Group1 Backup Domain Access function
 *  @brief   Backup Domain Access function
 *
@verbatim
  ==============================================================================
                   ##### Backup Domain Access function #####
  ==============================================================================

    [..] After reset, the Backup Domain Registers (RCC BDCR Register, RTC registers
         and RTC backup registers) are protected against possible stray write accesses.
    [..] To enable access to Backup domain use the PWR_BackupAccessCmd(ENABLE) function.

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the PWR peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void PWR_DeInit(void)
{
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, DISABLE);
}

/**
  * @brief  Enables or disables access to the Backup domain registers.
  * @note   If the HSE divided by 32 is used as the RTC clock, the
  *         Backup Domain Access should be kept enabled.
  * @param  NewState: new state of the access to the Backup domain registers.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_BackupAccessCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the Backup Domain Access */
        PWR->CR |= PWR_CR_DBP;
    }
    else
    {
        /* Disable the Backup Domain Access */
        PWR->CR &= (uint32_t)~((uint32_t)PWR_CR_DBP);
    }
}

/**
  * @}
  */

/** @defgroup PWR_Group2 PVD configuration functions
 *  @brief   PVD configuration functions
 *
@verbatim
  ==============================================================================
                    ##### PVD configuration functions #####
  ==============================================================================
  [..]
  (+) The PVD is used to monitor the VDD power supply by comparing it to a threshold
      selected by the PVD Level (PLS[2:0] bits in the PWR_CR).
  (+) A PVDO flag is available to indicate if VDD/VDDA is higher or lower than the
      PVD threshold. This event is internally connected to the EXTI line16
      and can generate an interrupt if enabled through the EXTI registers.
  (+) The PVD is stopped in Standby mode.

@endverbatim
  * @{
  */

/**
  * @brief  Configures the voltage threshold detected by the Power Voltage Detector(PVD).
  * @param  PWR_PVDLevel: specifies the PVD detection level
  *          This parameter can be one of the following values:
  *             @arg PWR_PVDLevel_0
  *             @arg PWR_PVDLevel_1
  *             @arg PWR_PVDLevel_2
  *             @arg PWR_PVDLevel_3
  *             @arg PWR_PVDLevel_4
  *             @arg PWR_PVDLevel_5
  *             @arg PWR_PVDLevel_6
  *             @arg PWR_PVDLevel_7
  * @note   Refer to the electrical characteristics of your device datasheet for
  *         more details about the voltage threshold corresponding to each
  *         detection level.
  * @retval None
  */
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_PWR_PVD_LEVEL(PWR_PVDLevel));

    tmpreg = PWR->CR;

    /* Clear PLS[7:5] bits */
    tmpreg &= CR_PLS_MASK;

    /* Set PLS[7:5] bits according to PWR_PVDLevel value */
    tmpreg |= PWR_PVDLevel;

    /* Store the new value */
    PWR->CR = tmpreg;
}

/**
  * @brief  Enables or disables the Power Voltage Detector(PVD).
  * @param  NewState: new state of the PVD.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_PVDCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the PVD */
        PWR->CR |= PWR_CR_PVDE;
    }
    else
    {
        /* Disable the PVD */
        PWR->CR &= (uint32_t)~((uint32_t)PWR_CR_PVDE);
    }
}

/**
  * @}
  */

/** @defgroup PWR_Group3 WakeUp pins configuration functions
 *  @brief   WakeUp pins configuration functions
 *
@verbatim
  ==============================================================================
               ##### WakeUp pin configuration functions #####
  ==============================================================================

  (+) WakeUp pins are used to wakeup the system from Standby mode. These pins are
      forced in input pull down configuration and are active on rising edges.
  (+) There are eight WakeUp pins: WakeUp Pin 1 on PA.00 and WakeUp Pin 2 on PC.13.

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the WakeUp Pin functionality.
  * @param  PWR_WakeUpPin: specifies the WakeUpPin.
  *          This parameter can be one of the following values
  *             @arg PWR_WakeUpPin_1
  *             @arg PWR_WakeUpPin_2
  * @param  NewState: new state of the WakeUp Pin functionality.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_WakeUpPinCmd(uint32_t PWR_WakeUpPin, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_PWR_WAKEUP_PIN(PWR_WakeUpPin));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the EWUPx pin */
        PWR->CSR |= PWR_WakeUpPin;
    }
    else
    {
        /* Disable the EWUPx pin */
        PWR->CSR &= ~PWR_WakeUpPin;
    }
}

/**
  * @}
  */


/** @defgroup PWR_Group4 Low Power modes configuration functions
 *  @brief   Low Power modes configuration functions
 *
@verbatim
  ==============================================================================
              ##### Low Power modes configuration functions #####
  ==============================================================================

    [..] The devices feature three low-power modes:
    (+) Sleep mode: Cortex-M0 core stopped, peripherals kept running.
    (+) Stop mode: all clocks are stopped, regulator running, regulator in low power mode
    (+) Standby mode: VCORE domain powered off

  *** Sleep mode ***
  ==================
  [..]
    (+) Entry:
        (++) The Sleep mode is entered by executing the WFE() or WFI() instructions.
    (+) Exit:
        (++) Any peripheral interrupt acknowledged by the nested vectored interrupt
             controller (NVIC) can wake up the device from Sleep mode.

  *** Stop mode ***
  =================
  [..] In Stop mode, all clocks in the VCORE domain are stopped, the PLL, the HSI,
       the HSI14 and the HSE RC oscillators are disabled. Internal SRAM and register
       contents are preserved.
       The voltage regulator can be configured either in normal or low-power mode.

    (+) Entry:
        (++) The Stop mode is entered using the PWR_EnterSTOPMode(PWR_Regulator_LowPower,)
             function with regulator in LowPower or with Regulator ON.
    (+) Exit:
        (++) Any EXTI Line (Internal or External) configured in Interrupt/Event mode
             or any internal IPs (I2C, UASRT or CEC) wakeup event.

  *** Standby mode ***
  ====================
  [..] The Standby mode allows to achieve the lowest power consumption. It is based
       on the Cortex-M0 deepsleep mode, with the voltage regulator disabled.
       The VCORE domain is consequently powered off. The PLL, the HSI, the HSI14
       oscillator and the HSE oscillator are also switched off. SRAM and register
       contents are lost except for the Backup domain (RTC registers, RTC backup
       registers and Standby circuitry).

  [..] The voltage regulator is OFF.

    (+) Entry:
        (++) The Standby mode is entered using the PWR_EnterSTANDBYMode() function.
    (+) Exit:
        (++) WKUP pin rising edge, RTC alarm (Alarm A and Alarm B), RTC wakeup,
             tamper event, time-stamp event, external reset in NRST pin, IWDG reset.

  *** Auto-wakeup (AWU) from low-power mode ***
  =============================================
  [..] The MCU can be woken up from low-power mode by an RTC Alarm event, a tamper
       event, a time-stamp event, or a comparator event, without depending on an
       external interrupt (Auto-wakeup mode).

    (+) RTC auto-wakeup (AWU) from the Stop mode
        (++) To wake up from the Stop mode with an RTC alarm event, it is necessary to:
             (+++) Configure the EXTI Line 17 to be sensitive to rising edges (Interrupt
                   or Event modes) using the EXTI_Init() function.
             (+++) Enable the RTC Alarm Interrupt using the RTC_ITConfig() function
             (+++) Configure the RTC to generate the RTC alarm using the RTC_SetAlarm()
                   and RTC_AlarmCmd() functions.
        (++) To wake up from the Stop mode with an RTC Tamper or time stamp event, it
             is necessary to:
             (+++) Configure the EXTI Line 19 to be sensitive to rising edges (Interrupt
                   or Event modes) using the EXTI_Init() function.
             (+++) Enable the RTC Tamper or time stamp Interrupt using the RTC_ITConfig()
                   function.
             (+++) Configure the RTC to detect the tamper or time stamp event using the
                   RTC_TimeStampConfig(), RTC_TamperTriggerConfig() and RTC_TamperCmd()
                   functions.

    (+) RTC auto-wakeup (AWU) from the Standby mode
        (++) To wake up from the Standby mode with an RTC alarm event, it is necessary to:
             (+++) Enable the RTC Alarm Interrupt using the RTC_ITConfig() function.
             (+++) Configure the RTC to generate the RTC alarm using the RTC_SetAlarm()
                   and RTC_AlarmCmd() functions.
        (++) To wake up from the Standby mode with an RTC Tamper or time stamp event, it
             is necessary to:
             (+++) Enable the RTC Tamper or time stamp Interrupt using the RTC_ITConfig()
                   function.
             (+++) Configure the RTC to detect the tamper or time stamp event using the
                   RTC_TimeStampConfig(), RTC_TamperTriggerConfig() and RTC_TamperCmd()
                   functions.

    (+) Comparator auto-wakeup (AWU) from the Stop mode
        (++) To wake up from the Stop mode with an comparator 1 or comparator 2 wakeup
             event, it is necessary to:
             (+++) Configure the EXTI Line 21 for comparator 1 or EXTI Line 22 for comparator 2
                   to be sensitive to to the selected edges (falling, rising or falling
                   and rising) (Interrupt or Event modes) using the EXTI_Init() function.
             (+++) Configure the comparator to generate the event.

@endverbatim
  * @{
  */

/**
  * @brief  Enters Sleep mode.
  * @note   In Sleep mode, all I/O pins keep the same state as in Run mode.
  * @param  PWR_SLEEPEntry: specifies if SLEEP mode in entered with WFI or WFE instruction.
  *          This parameter can be one of the following values:
  *             @arg PWR_SLEEPEntry_WFI: enter SLEEP mode with WFI instruction
  *             @arg PWR_SLEEPEntry_WFE: enter SLEEP mode with WFE instruction
  * @retval None
  */
void PWR_EnterSleepMode(uint8_t PWR_SLEEPEntry)
{
    /* Check the parameters */
    assert_param(IS_PWR_SLEEP_ENTRY(PWR_SLEEPEntry));

    /* Clear SLEEPDEEP bit of Cortex-M0 System Control Register */
    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);

    /* Select SLEEP mode entry -------------------------------------------------*/
    if (PWR_SLEEPEntry == PWR_SLEEPEntry_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else
    {
        /* Request Wait For Event */
        __SEV();
        __WFE();
        __WFE();
    }
}

/**
  * @brief  Enters STOP mode.
  * @note   In Stop mode, all I/O pins keep the same state as in Run mode.
  * @note   When exiting Stop mode by issuing an interrupt or a wakeup event,
  *         the HSI RC oscillator is selected as system clock.
  * @note   When the voltage regulator operates in low power mode, an additional
  *         startup delay is incurred when waking up from Stop mode.
  *         By keeping the internal regulator ON during Stop mode, the consumption
  *         is higher although the startup time is reduced.
  * @param  PWR_Regulator: specifies the regulator state in STOP mode.
  *         This parameter can be one of the following values:
  *             @arg PWR_Regulator_ON: STOP mode with regulator ON
  *             @arg PWR_Regulator_LowPower: STOP mode with regulator in low power mode
  * @param  PWR_STOPEntry: specifies if STOP mode in entered with WFI or WFE instruction.
  *         This parameter can be one of the following values:
  *             @arg PWR_STOPEntry_WFI: enter STOP mode with WFI instruction
  *             @arg PWR_STOPEntry_WFE: enter STOP mode with WFE instruction
                @arg PWR_STOPEntry_SLEEPONEXIT: enter STOP mode with SLEEPONEXIT instruction
  * @retval None
  */
uint32_t nvic_iser0_bakup = 0;
uint32_t irq_systick_bakup = 0;

void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_PWR_REGULATOR(PWR_Regulator));
    assert_param(IS_PWR_STOP_ENTRY(PWR_STOPEntry));

    /* Select the regulator state in STOP mode ---------------------------------*/
    tmpreg = PWR->CR;
    /* Clear PDDS and LPDSR bits */
    tmpreg &= CR_DS_MASK;

    /* Set LPDSR bit according to PWR_Regulator value */
    tmpreg |= PWR_Regulator;

    nvic_iser0_bakup = NVIC->ISER[0]; // backup nvic setting
    NVIC->ICER[0] = NVIC->ISER[0] // diable all IRQ but the following
                    & ~((0x1 << 1) // PVD combined EXTI
                        | (0x1 << 2) // RTC combined EXTI
                        | (0x1 << 5) // EXTI0_1
                        | (0x1 << 6) // EXTI2_3
                        | (0x1 << 7) // EXTI4_15
                        // |(0x1<<12)
                        // ADC combined with EXTI
                        // |(0x1<<23)
                        // I2C1 combined with EXTI
                        // |(0x1<<24)
                        // I2C2 combined with EXTI
                        // |(0x1<<27) // USART1 combined with EXTI
                        // |(0x1<<28) // USART2 combined with EXTI
                        // |(0x1<<29) // USART3~8 combined with EXTI
                       );
    // 注意：上注释掉的 ADC/I2C/UART 的部分, 如果有使用到对应的 EXTI, 则应该去掉注释.
    irq_systick_bakup = SysTick->CTRL; // backup systicker setting
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk ; // Disable Systicker IRQ

    /* Store the new value */
    PWR->CR = tmpreg;

    /* Set SLEEPDEEP bit of Cortex-M0 System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Select STOP mode entry --------------------------------------------------*/
    if (PWR_STOPEntry == PWR_STOPEntry_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
        /* Reset SLEEPDEEP bit of Cortex System Control Register */
        SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
    }
    else if (PWR_STOPEntry == PWR_STOPEntry_WFE)
    {
        /* Request Wait For Event */
        __WFE();
        /* Reset SLEEPDEEP bit of Cortex System Control Register */
        SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
    }
    else
    {
        /* Set SLEEP on exit bit of Cortex-M0 System Control Register */
        SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
    }

    SysTick->CTRL = irq_systick_bakup; // restore Systicker setting
    NVIC->ISER[0] = nvic_iser0_bakup; // restore nvic setting
}

/**
  * @brief  Enters STANDBY mode.
  * @note   In Standby mode, all I/O pins are high impedance except for:
  *          - Reset pad (still available)
  *          - RTC_AF1 pin (PC13) if configured for Wakeup pin 2 (WKUP2), tamper,
  *             time-stamp, RTC Alarm out, or RTC clock calibration out.
  *          - WKUP pin 1 (PA0) if enabled.
  * @note The Wakeup flag (WUF) need to be cleared at application level before to call this function
  * @param  None
  * @retval None
  */
void PWR_EnterSTANDBYMode(void)
{
    /* Select STANDBY mode */
    PWR->CR |= PWR_CR_PDDS;

    /* Set SLEEPDEEP bit of Cortex-M0 System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Request Wait For Interrupt */
    __WFI();
}

/**
  * @}
  */

/** @defgroup PWR_Group5 Flags management functions
 *  @brief   Flags management functions
 *
@verbatim
  ==============================================================================
                       ##### Flags management functions #####
  ==============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Checks whether the specified PWR flag is set or not.
  * @param  PWR_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *             @arg PWR_FLAG_WU: Wake Up flag. This flag indicates that a wakeup
  *                  event was received from the WKUP pin or from the RTC alarm
  *                  (Alarm A or Alarm B), RTC Tamper event or RTC TimeStamp event.
  *             @arg PWR_FLAG_SB: StandBy flag. This flag indicates that the
  *                  system was resumed from StandBy mode.
  *             @arg PWR_FLAG_PVDO: PVD Output. This flag is valid only if PVD
  *                  is enabled by the PWR_PVDCmd() function.
  *             @arg PWR_FLAG_VREFINTRDY: Internal Voltage Reference Ready flag.
  *                  This flag indicates the state of the internal voltage
  *                  reference, VREFINT.
  * @retval The new state of PWR_FLAG (SET or RESET).
  */
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_PWR_GET_FLAG(PWR_FLAG));

    if ((PWR->CSR & PWR_FLAG) != (uint32_t)RESET)
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
  * @brief  Clears the PWR's pending flags.
  * @param  PWR_FLAG: specifies the flag to clear.
  *          This parameter can be one of the following values:
  *             @arg PWR_FLAG_WU: Wake Up flag
  *             @arg PWR_FLAG_SB: StandBy flag
  * @retval None
  */
void PWR_ClearFlag(uint32_t PWR_FLAG)
{
    /* Check the parameters */
    assert_param(IS_PWR_CLEAR_FLAG(PWR_FLAG));

    PWR->CR |=  PWR_FLAG << 2;
}
