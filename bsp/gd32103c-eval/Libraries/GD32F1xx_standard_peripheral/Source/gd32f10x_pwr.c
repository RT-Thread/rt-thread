/**
  ******************************************************************************
  * @brief   PWR functions of the firmware library.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x_pwr.h"
#include "gd32f10x_rcc.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @defgroup PWR
  * @brief PWR driver modules
  * @{
  */

/** @defgroup PWR_Private_Defines
  * @{
  */
/* Left shift SBF or WUF(PWR_STR) to SBFR or WUFR(PWR_CTLR) */
#define BIT_SHIFT           2

/**
  * @}
  */

/** @defgroup PWR_Private_Functions
  * @{
  */

/**
  * @brief  Reset the PWR peripheral registers.
  * @param  None
  * @retval None
  */
void PWR_DeInit(void)
{
    RCC_APB1PeriphReset_Enable(RCC_APB1PERIPH_PWRRST, ENABLE);
    RCC_APB1PeriphReset_Enable(RCC_APB1PERIPH_PWRRST, DISABLE);
}

/**
  * @brief  Enable or disable write access to the registers in Backup domain.
  * @note   After reset, any write access to the registers in Backup domain is disabled.
  *         This bit has to be set to enable write access to these registers.
  * @param  NewValue: New value of write access state to the registers in Backup domain.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_BackupAccess_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the Backup Domain Access */
        PWR->CTLR |= PWR_CTLR_BKPWE;
    } else {
        /* Disable the Backup Domain Access */
        PWR->CTLR &= ~((uint32_t)PWR_CTLR_BKPWE);
    }
}

/**
  * @brief  Enable or disable the LVD(Low Voltage Detector), and configure the voltage
  *         threshold detected by the LVD.
  * @note   The LVDE bit controls whether LVD is enabled or not, while the LVDT[2:0]
  *         bits select the LVDT from 2.2V to 2.9V.
  * @note   The LVD is stopped in Standby mode.
  * @param  PWR_LVDT: the LVD threshold.
  *   This parameter can be one of the following values:
  *     @arg PWR_LVDT_0
  *     @arg PWR_LVDT_1
  *     @arg PWR_LVDT_2
  *     @arg PWR_LVDT_3
  *     @arg PWR_LVDT_4
  *     @arg PWR_LVDT_5
  *     @arg PWR_LVDT_6
  *     @arg PWR_LVDT_7
  * @param  NewValue: New value of the LVD state.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_LVDConfig(uint32_t PWR_LVDT, TypeState NewValue)
{
    uint32_t temp = 0;

    temp = PWR->CTLR;

    /* Clear LVDT[7:5] bits */
    temp &= ~((uint32_t)PWR_CTLR_LVDT);

    /* Set LVDT[7:5] bits according to PWR_LVDT value */
    temp |= PWR_LVDT;

    /* Store the new value */
    PWR->CTLR = temp;

    /* Enable or disable the LVD */
    if (NewValue != DISABLE) {
        /* Enable the LVD */
        PWR->CTLR |= PWR_CTLR_LVDE;
    } else {
        /* Disable the LVD */
        PWR->CTLR &= ~((uint32_t)PWR_CTLR_LVDE);
    }
}

/**
  * @brief  Enable or disable the WakeUp Pin(PA0 pin) function.
  * @note   If WUPE is set before entering the power saving mode,
  *         a rising edge on the WKUP Pin wakes up the system from the power
  *         saving mode. As the WKUP pin is active high, it will setup
  *         an input pull down mode when this bit is high.
  * @param  NewValue: New value of the WKUP Pin state.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_WKUP_Pin_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the WKUP pin */
        PWR->STR |= PWR_STR_WUPE;
    } else {
        /* Disable the WKUP pin */
        PWR->STR &= ~PWR_STR_WUPE;
    }
}

/**
 *@verbatim

  [..] The GD32F10x series of devices provide three types of power saving modes.

  *** Sleep mode ***
  ==================
  [..] The Sleep mode is based on the SLEEPING mode of the Cortex-M3. In Sleep
       mode, only clock of Cortex-M3 is off.
    (+) Entry:
        (++) To enter the Sleep mode, it is only necessary to clear SLEEPDEEP bit
             in the Cortex-M3 System Control Register, and execute a WFI or WFE
             instruction.
        (++) The Sleep mode is entered using the PWR_SLEEPMode_Entry() function.
    (+) Wakeup:
        (++) Any interrupt for WFI or Any event for WFE.
    (+) Wakeup Latency:
        (++) None

  *** Deep-sleep mode ***
  =================
  [..] The Deep-sleep mode is based on the SLEEPDEEP mode of the Cortex-M3. In
       Deep-sleep mode, all clocks in the 1.2V domain are off, and all of HSI,
       HSE and PLL are disabled. The LDO can operate normally or in low
       power mode depending on the LDOLP bit in the PWR_CTLR register.
    (+) Entry:
        (++) Before entering the Deep-sleep mode, it is necessary to set the
             SLEEPDEEP bit in the Cortex-M3 System Control Register, and clear
             the SDBM bit in the PWR_CTLR register.
        (++) The Deep-sleep mode is entered using the PWR_DEEPSLEEPMode_Entry()
             function.
    (+) Wakeup:
        (++) Any interrupt or event from EXTI Lines.
    (+) Wakeup Latency:
        (++) HSI wakeup time; LDO wakeup time if LDO is in low power mode.

  *** Standby mode ***
  ====================
  [..] The Standby mode is based on the SLEEPDEEP mode of the Cortex-M3. In Standby
       mode, the whole 1.2V domain is power off, the LDO is shut down, and all of
       HSI, HSE and PLL are disabled. Besides, the contents of SRAM and
       registers(except Backup Registers) are lost in Standby mode.
    (+) Entry:
        (++) Before entering the Standby mode, it is necessary to set the
             SLEEPDEEP bit in the Cortex-M3 System Control Register, and set
             the SDBM bit in the PWR_CTLR register, and clear WUF bit in the
             PWR_STR register. .
        (++) The Standby mode is entered using the PWR_STDBYMode_Entry() function.
    (+) Wakeup:
        (++) NRST pin, WKUP pin rising edge, RTC alarm, IWDG reset.
    (+) Wakeup Latency:
        (++) Power on sequence
 *@endverbatim
 */
/**
  * @brief  Enter Sleep mode.
  * @note   By default, this function selects the Sleep-now entry mechanism (SLEEPONEXIT = 0).
  * @param  PWR_SLEEPENTRY: WFI or WFE instruction.
  *   This parameter can be one of the following values:
  *     @arg PWR_SLEEPENTRY_WFI: enter Sleep mode with WFI instruction
  *     @arg PWR_SLEEPENTRY_WFE: enter Sleep mode with WFE instruction
  * @retval None
  */
void PWR_SLEEPMode_Entry(uint8_t PWR_SLEEPENTRY)
{
    /* Clear SLEEPDEEP bit of Cortex-M3 System Control Register */
    SCB->SCR &= ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);

    /* Select WFI or WFE to enter Sleep mode */
    if (PWR_SLEEPENTRY == PWR_SLEEPENTRY_WFI) {
        __WFI();
    } else {
        __WFE();
    }
}

/**
  * @brief  Enter Deep-sleep mode.
  * @note   When exiting Deep-sleep mode, the HSI is selected as the system clock.
  * @note   An additional wakeup delay will be incurred if the LDO operates in
  *         low power mode.
  * @param  PWR_LDO: the LDO state in Deep-sleep mode.
  *   This parameter can be one of the following values:
  *     @arg PWR_LDO_ON: Deep-sleep mode with LDO ON
  *     @arg PWR_LDO_LOWPOWER: Deep-sleep mode with LDO in low power mode
  * @param  PWR_DEEPSLEEPENTRY: WFI or WFE instruction.
  *   This parameter can be one of the following values:
  *     @arg PWR_DEEPSLEEPENTRY_WFI: enter Deep-sleep mode with WFI instruction
  *     @arg PWR_DEEPSLEEPENTRY_WFE: enter Deep-sleep mode with WFE instruction
  * @retval None
  */
void PWR_DEEPSLEEPMode_Entry(uint32_t PWR_LDO, uint8_t PWR_DEEPSLEEPENTRY)
{
    uint32_t temp = 0;

    /* Select the LDO state in Deep-sleep mode */
    temp = PWR->CTLR;

    /* Clear SDBM and LDOLP bits, and select Deep-sleep mode */
    temp &= ~((uint32_t)(PWR_CTLR_SDBM | PWR_CTLR_LDOLP));

    /* Set LDOLP bit according to PWR_LDO value, and select the LDO's state */
    temp |= PWR_LDO;

    /* Store the new value */
    PWR->CTLR = temp;

    /* Set SLEEPDEEP bit of Cortex-M3 System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Select WFI or WFE to enter Deep-sleep mode */
    if (PWR_DEEPSLEEPENTRY == PWR_DEEPSLEEPENTRY_WFI) {
        __WFI();
    } else {
        __SEV();
        __WFE();
        __WFE();
    }
    /* Reset SLEEPDEEP bit of Cortex-M3 System Control Register */
    SCB->SCR &= ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
}

/**
  * @brief  Enter Standby mode.
  * @note   The Standby mode achieves the lowest power consumption, but spends
  *         longest time to wake up.
  * @note   When exiting from the Standby mode, a power-on reset occurs and the
  *         Cortex-M3 will execute instructions code from the 0x0000_0000 address.
  * @param  PWR_STDBYENTRY: WFI or WFE instruction.
  *   This parameter can be one of the following values:
  *     @arg PWR_STDBYENTRY_WFI: enter Standby mode with WFI instruction
  *     @arg PWR_STDBYENTRY_WFE: enter Standby mode with WFE instruction
  * @retval None
  */
void PWR_STDBYMode_Entry(uint8_t PWR_STDBYENTRY)
{
    /* Set SLEEPDEEP bit of Cortex-M3 System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Set SDBM bit, and select Standby mode */
    PWR->CTLR |= PWR_CTLR_SDBM;

    /* Reset Wakeup flag */
    PWR->CTLR |= PWR_CTLR_WUFR;

    /* Select WFI or WFE to enter Standby mode */
    if (PWR_STDBYENTRY == PWR_STDBYENTRY_WFI) {
        __WFI();
    } else {
        __WFE();
    }
}

/**
  * @brief  Get the bit flag of some PWR_STR registers.
  * @param  PWR_FLAG: the flag of PWR_STR registers.
  *   This parameter can be one of the following values:
  *     @arg PWR_FLAG_WKUP: WakeUp flag. This flag indicates that a wakeup
  *          event was received from the WKUP pin or from the RTC alarm,
  *          IWDG reset or NRST pin.
  *     @arg PWR_FLAG_STB: StandBy flag. This flag indicates that the
  *          system has been in Standby mode.
  *     @arg PWR_FLAG_LVDF: LVD State flag. This flag is valid only if LVD
  *          is enabled by the PWR_LVD_Config()function.
  * @retval The new value of PWR_FLAG (SET or RESET).
  */
TypeState PWR_GetBitState(uint32_t PWR_FLAG)
{
    /* Check and get the selected PWR flag */
    if ((PWR->STR & PWR_FLAG) != (uint32_t)RESET) {
        /* PWR_FLAG bit is SET */
        return SET;
    } else {
        /* PWR_FLAG bit is RESET */
        return RESET;
    }
}

/**
  * @brief  Clear the bit flag of some PWR_STR registers.
  * @param  PWR_FLAG: the flag of PWR_STR registers.
  *   This parameter can be one of the following values:
  *     @arg PWR_FLAG_WKUP: Wake_Up flag
  *     @arg PWR_FLAG_STB: StandBy flag
  * @retval None
  */
void PWR_ClearBitState(uint32_t PWR_FLAG)
{
    /* Clear the selected PWR flag */
    PWR->CTLR |=  PWR_FLAG << BIT_SHIFT;
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

