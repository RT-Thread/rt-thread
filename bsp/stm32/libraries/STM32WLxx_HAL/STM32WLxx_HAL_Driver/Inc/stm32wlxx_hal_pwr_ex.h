/**
  ******************************************************************************
  * @file    stm32wlxx_hal_pwr_ex.h
  * @author  MCD Application Team
  * @brief   Header file of PWR HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WLxx_HAL_PWR_EX_H
#define STM32WLxx_HAL_PWR_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx_hal_def.h"

/** @addtogroup STM32WLxx_HAL_Driver
  * @{
  */

/** @defgroup PWREx PWREx
  * @brief PWR Extended HAL module driver
  * @{
  */


/* Exported types ------------------------------------------------------------*/

/** @defgroup PWREx_Exported_Types PWR Extended Exported Types
  * @{
  */

/**
  * @brief  PWR PVM configuration structure definition
  */
typedef struct
{
  uint32_t PVMType;   /*!< PVMType: Specifies which voltage is monitored and against which threshold.
                           This parameter can be a value of @ref PWREx_PVM_Type.
                           @arg @ref PWR_PVM_3 Peripheral Voltage Monitoring 3 enable: VDDA versus 1.62 V.
                           */
  uint32_t Mode;      /*!< Mode: Specifies the operating mode for the selected pins.
                           This parameter can be a value of @ref PWREx_PVM_Mode. */
} PWR_PVMTypeDef;

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup PWREx_Private_Constants PWR Extended Private Constants
  * @{
  */
#define PWR_WUP_POLARITY_SHIFT                  0x05   /*!< Internal constant used to retrieve wakeup pin polarity */

/** @defgroup PWR_FLAG_REG PWR flag register
  * @{
  */
#define PWR_FLAG_REG_SR1         (0x20UL)   /* Bitfield to indicate PWR flag located in register PWR_SR1 */
#define PWR_FLAG_REG_SR2         (0x40UL)   /* Bitfield to indicate PWR flag located in register PWR_SR2 */
#define PWR_FLAG_REG_EXTSCR      (0x60UL)   /* Bitfield to indicate PWR flag located in register PWR_EXTSCR */
#define PWR_FLAG_REG_MASK_POS    (5UL)      /* Bitfield mask position to indicate PWR flag location in PWR register */
#define PWR_FLAG_REG_MASK        (PWR_FLAG_REG_SR1 | PWR_FLAG_REG_SR2 | PWR_FLAG_REG_EXTSCR)   /* Bitfield mask to indicate PWR flag location in PWR register */
#define PWR_FLAG_EXTSCR_CLR_POS  (16UL)     /* Bitfield for register PWR_EXTSCR clearable bits positions: position of bitfield in flag literals */
#if defined(DUAL_CORE)
#define PWR_FLAG_EXTSCR_CLR_MASK ((PWR_EXTSCR_C1CSSF_Pos | PWR_EXTSCR_C2CSSF_Pos) << PWR_FLAG_EXTSCR_CLR_POS)  /* Bitfield for register PWR_EXTSCR clearable bits positions: mask of bitfield in flag literals */
#else
#define PWR_FLAG_EXTSCR_CLR_MASK ((PWR_EXTSCR_C1CSSF_Pos) << PWR_FLAG_EXTSCR_CLR_POS)  /* Bitfield for register PWR_EXTSCR clearable bits positions: mask of bitfield in flag literals */
#endif
/**
  * @}
  */

/** @defgroup PWR_PVM_Mode_Mask PWR PVM Mode Mask
  * @{
  */
/* Note: On STM32WL series, power PVD event is not available on EXTI lines     */
/*       (only interruption is available through EXTI line 16).               */
#define PVM_MODE_IT                         (0x00010000UL)  /*!< Mask for interruption yielded by PVM threshold crossing */
#define PVM_RISING_EDGE                     (0x00000001UL)  /*!< Mask for rising edge set as PVM trigger */
#define PVM_FALLING_EDGE                    (0x00000002UL)  /*!< Mask for falling edge set as PVM trigger */
#define PVM_RISING_FALLING_EDGE             (0x00000003UL)  /*!< Mask for rising and falling edges set as PVM trigger */

/**
  * @}
  */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup PWREx_Exported_Constants  PWR Extended Exported Constants
  * @{
  */

/** @defgroup PWREx_WakeUp_Pins  PWR wake-up pins
  * @{
  */
#define PWR_WAKEUP_PIN1_HIGH                PWR_CR3_EWUP1  /*!< Wakeup pin 1 (with high level polarity) */
#define PWR_WAKEUP_PIN2_HIGH                PWR_CR3_EWUP2  /*!< Wakeup pin 2 (with high level polarity) */
#define PWR_WAKEUP_PIN3_HIGH                PWR_CR3_EWUP3  /*!< Wakeup pin 3 (with high level polarity) */

#define PWR_WAKEUP_PIN1_LOW                 ((PWR_CR4_WP1<<PWR_WUP_POLARITY_SHIFT) | PWR_CR3_EWUP1) /*!< Wakeup pin 1 (with low level polarity) */
#define PWR_WAKEUP_PIN2_LOW                 ((PWR_CR4_WP2<<PWR_WUP_POLARITY_SHIFT) | PWR_CR3_EWUP2) /*!< Wakeup pin 2 (with low level polarity) */
#define PWR_WAKEUP_PIN3_LOW                 ((PWR_CR4_WP3<<PWR_WUP_POLARITY_SHIFT) | PWR_CR3_EWUP3) /*!< Wakeup pin 3 (with low level polarity) */
/**
  * @}
  */

/* Literals kept for legacy purpose */
#define PWR_WAKEUP_PIN1                     PWR_CR3_EWUP1  /*!< Wakeup pin 1 (with high level polarity) */
#define PWR_WAKEUP_PIN2                     PWR_CR3_EWUP2  /*!< Wakeup pin 2 (with high level polarity) */
#define PWR_WAKEUP_PIN3                     PWR_CR3_EWUP3  /*!< Wakeup pin 3 (with high level polarity) */

/** @defgroup PWREx_PVM_Type Peripheral Voltage Monitoring type
  * @{
  */
#define PWR_PVM_3                           PWR_CR2_PVME3  /*!< Peripheral Voltage Monitoring 3 enable: VDDA versus 1.62 V */
/**
  * @}
  */

/** @defgroup PWREx_PVM_Mode  PWR PVM interrupt and event mode
  * @{
  */
/* Note: On STM32WL series, power PVM event is not available on EXTI lines     */
/*       (only interruption is available through EXTI line 34).               */
#define PWR_PVM_MODE_NORMAL                 (0x00000000UL)                              /*!< basic mode is used */

#define PWR_PVM_MODE_IT_RISING              (PVM_MODE_IT | PVM_RISING_EDGE)             /*!< External Interrupt Mode with Rising edge trigger detection */
#define PWR_PVM_MODE_IT_FALLING             (PVM_MODE_IT | PVM_FALLING_EDGE)            /*!< External Interrupt Mode with Falling edge trigger detection */
#define PWR_PVM_MODE_IT_RISING_FALLING      (PVM_MODE_IT | PVM_RISING_FALLING_EDGE)     /*!< External Interrupt Mode with Rising/Falling edge trigger detection */
/**
  * @}
  */

/** @defgroup PWREx_Flash_PowerDown  Flash Power Down modes
  * @{
  */
#define PWR_FLASHPD_LPRUN                   PWR_CR1_FPDR     /*!< Enable Flash power down in low power run mode */
#define PWR_FLASHPD_LPSLEEP                 PWR_CR1_FPDS     /*!< Enable Flash power down in low power sleep mode */
/**
  * @}
  */

/** @defgroup PWREx_Regulator_Voltage_Scale  PWR Regulator voltage scale
  * @{
  */
#define PWR_REGULATOR_VOLTAGE_SCALE1        PWR_CR1_VOS_0     /*!< Regulator voltage output range 1 mode, typical output voltage at 1.2 V, system frequency up to 64 MHz */
#define PWR_REGULATOR_VOLTAGE_SCALE2        PWR_CR1_VOS_1     /*!< Regulator voltage output range 2 mode, typical output voltage at 1.0 V, system frequency up to 16 MHz */
/**
  * @}
  */

/** @defgroup PWREx_VBAT_Battery_Charging_Selection PWR battery charging resistor selection
  * @{
  */
#define PWR_BATTERY_CHARGING_RESISTOR_5     (0x00000000UL)         /*!< VBAT charging through a 5 kOhms resistor   */
#define PWR_BATTERY_CHARGING_RESISTOR_1_5   PWR_CR4_VBRS           /*!< VBAT charging through a 1.5 kOhms resistor */
/**
  * @}
  */

/** @defgroup PWREx_VBAT_Battery_Charging PWR battery charging
  * @{
  */
#define PWR_BATTERY_CHARGING_DISABLE        (0x00000000UL)
#define PWR_BATTERY_CHARGING_ENABLE         PWR_CR4_VBE
/**
  * @}
  */

/** @defgroup PWREx_GPIO_Bit_Number GPIO bit number for I/O setting in standby/shutdown mode
  * @{
  */
#define PWR_GPIO_BIT_0                      PWR_PUCRB_PB0    /*!< GPIO port I/O pin 0  */
#define PWR_GPIO_BIT_1                      PWR_PUCRB_PB1    /*!< GPIO port I/O pin 1  */
#define PWR_GPIO_BIT_2                      PWR_PUCRB_PB2    /*!< GPIO port I/O pin 2  */
#define PWR_GPIO_BIT_3                      PWR_PUCRB_PB3    /*!< GPIO port I/O pin 3  */
#define PWR_GPIO_BIT_4                      PWR_PUCRB_PB4    /*!< GPIO port I/O pin 4  */
#define PWR_GPIO_BIT_5                      PWR_PUCRB_PB5    /*!< GPIO port I/O pin 5  */
#define PWR_GPIO_BIT_6                      PWR_PUCRB_PB6    /*!< GPIO port I/O pin 6  */
#define PWR_GPIO_BIT_7                      PWR_PUCRB_PB7    /*!< GPIO port I/O pin 7  */
#define PWR_GPIO_BIT_8                      PWR_PUCRB_PB8    /*!< GPIO port I/O pin 8  */
#define PWR_GPIO_BIT_9                      PWR_PUCRB_PB9    /*!< GPIO port I/O pin 9  */
#define PWR_GPIO_BIT_10                     PWR_PUCRB_PB10   /*!< GPIO port I/O pin 10 */
#define PWR_GPIO_BIT_11                     PWR_PUCRB_PB11   /*!< GPIO port I/O pin 11 */
#define PWR_GPIO_BIT_12                     PWR_PUCRB_PB12   /*!< GPIO port I/O pin 12 */
#define PWR_GPIO_BIT_13                     PWR_PUCRB_PB13   /*!< GPIO port I/O pin 14 */
#define PWR_GPIO_BIT_14                     PWR_PDCRB_PB14   /*!< GPIO port I/O pin 14 */
#define PWR_GPIO_BIT_15                     PWR_PUCRB_PB15   /*!< GPIO port I/O pin 15 */
/**
  * @}
  */

/** @defgroup PWREx_GPIO GPIO port
  * @{
  */
#define PWR_GPIO_A                          (0x00000000UL)      /*!< GPIO port A */
#define PWR_GPIO_B                          (0x00000001UL)      /*!< GPIO port B */
#define PWR_GPIO_C                          (0x00000002UL)      /*!< GPIO port C */
#define PWR_GPIO_H                          (0x00000007UL)      /*!< GPIO port H */
/**
  * @}
  */

/** @defgroup PWR_EC_EOL_OPERATING_MODES Monitoring of supply voltage for radio operating level (radio End Of Life)
  * @{
  */
#define PWR_RADIO_EOL_DISABLE               (0x00000000UL)    /*!< Monitoring of supply voltage for radio operating level (radio End Of Life) disable */
#define PWR_RADIO_EOL_ENABLE                (PWR_CR5_RFEOLEN) /*!< Monitoring of supply voltage for radio operating level (radio End Of Life) enable */
/**
  * @}
  */

/** @defgroup PWR_EC_SMPS_OPERATING_MODES SMPS Step down converter operating modes
  * @{
  */
#define PWR_SMPS_BYPASS                     (0x00000000UL)    /*!< SMPS step down in bypass mode  */
#define PWR_SMPS_STEP_DOWN                  (PWR_CR5_SMPSEN)  /*!< SMPS step down in step down mode if system low power mode is run, LP run or stop0. If system low power mode is stop1, stop2, standby, shutdown, then SMPS is forced in mode open to preserve energy stored in decoupling capacitor as long as possible. Note: In case of a board without SMPS coil mounted, SMPS should not be activated. */
/**
  * @}
  */

/** @defgroup PWR_EC_RADIO_BUSY_POLARITY Radio busy signal polarity
  * @{
  */
#define PWR_RADIO_BUSY_POLARITY_RISING      (0x00000000UL)     /*!< Radio busy signal polarity to rising edge (detection on high level). */
#define PWR_RADIO_BUSY_POLARITY_FALLING     (PWR_CR4_WRFBUSYP) /*!< Radio busy signal polarity to falling edge (detection on low level). */
/**
  * @}
  */

/** @defgroup PWR_EC_RADIO_BUSY_TRIGGER Radio busy trigger
  * @{
  */
#define PWR_RADIO_BUSY_TRIGGER_NONE         (0x00000000UL)     /*!< Radio busy trigger action: no wake-up from low-power mode and no interruption sent to the selected CPU. */
#define PWR_RADIO_BUSY_TRIGGER_WU_IT        (PWR_CR3_EWRFBUSY) /*!< Radio busy trigger action: wake-up from low-power mode Standby and interruption sent to the selected CPU. */
/**
  * @}
  */

/** @defgroup PWR_EC_RADIO_IRQ_TRIGGER Radio IRQ trigger
  * @{
  */
#define PWR_RADIO_IRQ_TRIGGER_NONE          (0x00000000UL)     /*!< Radio IRQ trigger action: no wake-up from low-power mode and no interruption sent to the selected CPU. */
#define PWR_RADIO_IRQ_TRIGGER_WU_IT         (PWR_CR3_EWRFIRQ)  /*!< Radio IRQ trigger action: wake-up from low-power mode Standby and interruption sent to the selected CPU. */
/**
  * @}
  */

/** @defgroup PWREx_Flag  PWR Status Flags
  *        Elements values convention: 0000 0000 0XXY YYYYb
  *           - Y YYYY  : Flag position in the XX register (5 bits)
  *           - XX  : Status register (2 bits)
  *                 - 01: SR1 register
  *                 - 10: SR2 register
  *                 - 11: EXTSCR register
  * @{
  */
/*--------------------------------SR1-------------------------------*/
#define PWR_FLAG_WUF1                       (PWR_FLAG_REG_SR1 | PWR_SR1_WUF1_Pos)        /*!< Wakeup event on wakeup pin 1 */
#define PWR_FLAG_WUF2                       (PWR_FLAG_REG_SR1 | PWR_SR1_WUF2_Pos)        /*!< Wakeup event on wakeup pin 2 */
#define PWR_FLAG_WUF3                       (PWR_FLAG_REG_SR1 | PWR_SR1_WUF3_Pos)        /*!< Wakeup event on wakeup pin 3 */
#define PWR_FLAG_WU                         (PWR_FLAG_REG_SR1 | PWR_SR1_WUF)             /*!< Encompass wakeup event on all wakeup pins */
#define PWR_FLAG_WPVD                       (PWR_FLAG_REG_SR1 | PWR_SR1_WPVDF_Pos)       /*!< Wakeup PVD flag */
#define PWR_FLAG_HOLDC2I                    (PWR_FLAG_REG_SR1 | PWR_SR1_C2HF_Pos)        /*!< CPU2 on-Hold Interrupt Flag */
#define PWR_FLAG_WUFI                       (PWR_FLAG_REG_SR1 | PWR_SR1_WUFI_Pos)        /*!< Wakeup on internal wakeup line */
#define PWR_FLAG_WRFBUSY                    (PWR_FLAG_REG_SR1 | PWR_SR1_WRFBUSYF_Pos)    /*!< Wakeup radio busy flag (triggered status: wake-up event or interruption occurred at least once. Can be cleared by software) */
/*--------------------------------SR2-------------------------------*/
#define PWR_FLAG_LDORDY                     (PWR_FLAG_REG_SR2 | PWR_SR2_LDORDY_Pos)      /*!< Main LDO ready flag */
#define PWR_FLAG_SMPSRDY                    (PWR_FLAG_REG_SR2 | PWR_SR2_SMPSRDY_Pos)     /*!< SMPS ready Flag */
#define PWR_FLAG_REGLPS                     (PWR_FLAG_REG_SR2 | PWR_SR2_REGLPS_Pos)      /*!< Low-power regulator started and ready flag */
#define PWR_FLAG_REGLPF                     (PWR_FLAG_REG_SR2 | PWR_SR2_REGLPF_Pos)      /*!< Low-power regulator (main regulator or low-power regulator used) flag */
#define PWR_FLAG_REGMRS                     (PWR_FLAG_REG_SR2 | PWR_SR2_REGMRS_Pos)      /*!< Main regulator supply from LDO or SMPS or directly from VDD */
#define PWR_FLAG_FLASHRDY                   (PWR_FLAG_REG_SR2 | PWR_SR2_FLASHRDY_Pos)    /*!< Flash ready flag */
#define PWR_FLAG_VOSF                       (PWR_FLAG_REG_SR2 | PWR_SR2_VOSF_Pos)        /*!< Voltage scaling flag */
#define PWR_FLAG_PVDO                       (PWR_FLAG_REG_SR2 | PWR_SR2_PVDO_Pos)        /*!< Power Voltage Detector output flag */
#define PWR_FLAG_PVMO3                      (PWR_FLAG_REG_SR2 | PWR_SR2_PVMO3_Pos)       /*!< Power Voltage Monitoring 3 output flag */
#define PWR_FLAG_RFEOL                      (PWR_FLAG_REG_SR2 | PWR_SR2_RFEOLF_Pos)      /*!< Power Voltage Monitoring Radio end of life flag */
#define PWR_FLAG_RFBUSYS                    (PWR_FLAG_REG_SR2 | PWR_SR2_RFBUSYS_Pos)     /*!< Radio busy signal flag (current status) */
#define PWR_FLAG_RFBUSYMS                   (PWR_FLAG_REG_SR2 | PWR_SR2_RFBUSYMS_Pos)    /*!< Radio busy masked signal flag (current status) */
#define PWR_FLAG_C2BOOTS                    (PWR_FLAG_REG_SR2 | PWR_SR2_C2BOOTS_Pos)     /*!< CPU2 boot request source information flag */
/*------------------------------EXTSCR------------------------------*/
#define PWR_FLAG_SB                         (PWR_FLAG_REG_EXTSCR | PWR_EXTSCR_C1SBF_Pos | (PWR_EXTSCR_C1CSSF_Pos << PWR_FLAG_EXTSCR_CLR_POS))    /*!< System Standby flag for CPU1 */
#define PWR_FLAG_STOP2                      (PWR_FLAG_REG_EXTSCR | PWR_EXTSCR_C1STOP2F_Pos | (PWR_EXTSCR_C1CSSF_Pos << PWR_FLAG_EXTSCR_CLR_POS)) /*!< System Stop 2 flag for CPU1 */
#define PWR_FLAG_STOP                       (PWR_FLAG_REG_EXTSCR | PWR_EXTSCR_C1STOPF_Pos | (PWR_EXTSCR_C1CSSF_Pos << PWR_FLAG_EXTSCR_CLR_POS))  /*!< System Stop 0 or Stop 1 flag for CPU1 */
#if defined(DUAL_CORE)
#define PWR_FLAG_C2SB                       (PWR_FLAG_REG_EXTSCR | PWR_EXTSCR_C2SBF_Pos | (PWR_EXTSCR_C2CSSF_Pos << PWR_FLAG_EXTSCR_CLR_POS))    /*!< System Standby flag for CPU2 */
#define PWR_FLAG_C2STOP2                    (PWR_FLAG_REG_EXTSCR | PWR_EXTSCR_C2STOP2F_Pos | (PWR_EXTSCR_C2CSSF_Pos << PWR_FLAG_EXTSCR_CLR_POS)) /*!< System Stop 2 flag for CPU2 */
#define PWR_FLAG_C2STOP                     (PWR_FLAG_REG_EXTSCR | PWR_EXTSCR_C2STOPF_Pos | (PWR_EXTSCR_C2CSSF_Pos << PWR_FLAG_EXTSCR_CLR_POS))  /*!< System Stop 0 or Stop 1 flag for CPU2 */
#endif

#define PWR_FLAG_LPMODES                    (PWR_FLAG_SB)                       /*!< System flag encompassing all low-powers flags (Stop0, 1, 2 and Standby) for CPU1, used when clearing flags */
#if defined(DUAL_CORE)
#define PWR_FLAG_C2LPMODES                  (PWR_FLAG_C2SB)                     /*!< System flag encompassing all low-powers flags (Stop0, 1, 2 and Standby) for CPU2, used when clearing flags */
#endif

#define PWR_FLAG_C1DEEPSLEEP                (PWR_EXTSCR_C1DS_Pos | PWR_FLAG_REG_EXTSCR)     /*!< CPU1 DeepSleep Flag */
#if defined(DUAL_CORE)
#define PWR_FLAG_C2DEEPSLEEP                (PWR_EXTSCR_C2DS_Pos | PWR_FLAG_REG_EXTSCR)     /*!< CPU2 DeepSleep Flag */
#endif
/**
  * @}
  */

/** @defgroup PWREx_Core_Select PWREx Core definition
  * @{
  */
#define PWR_CORE_CPU1                       (0x00000000UL)
#if defined(DUAL_CORE)
#define PWR_CORE_CPU2                       (0x00000001UL)
#endif
/**
  * @}
  */

/** @defgroup PWREx_PVM_EXTI_LINE PWR PVM external interrupts lines
  * @{
  */
#define PWR_EXTI_LINE_PVM3                  (LL_EXTI_LINE_34)  /*!< External interrupt line 34 connected to PVM3 */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup PWREx_Exported_Macros PWR Extended Exported Macros
 * @{
 */

/**
  * @brief Enable the PVM3 Extended Interrupt line.
  * @retval None
  */
#if defined(CORE_CM0PLUS)
#define __HAL_PWR_PVM3_EXTI_ENABLE_IT()     LL_C2_EXTI_EnableIT_32_63(PWR_EXTI_LINE_PVM3)
#else
#define __HAL_PWR_PVM3_EXTI_ENABLE_IT()     LL_EXTI_EnableIT_32_63(PWR_EXTI_LINE_PVM3)
#endif

/**
  * @brief Disable the PVM3 Extended Interrupt line.
  * @retval None
  */
#if defined(CORE_CM0PLUS)
#define __HAL_PWR_PVM3_EXTI_DISABLE_IT()    LL_C2_EXTI_DisableIT_32_63(PWR_EXTI_LINE_PVM3)
#else
#define __HAL_PWR_PVM3_EXTI_DISABLE_IT()    LL_EXTI_DisableIT_32_63(PWR_EXTI_LINE_PVM3)
#endif

/**
  * @brief Enable the PVM3 Event line.
  * @retval None
  */
#if defined(CORE_CM0PLUS)
#define __HAL_PWR_PVM3_EXTI_ENABLE_EVENT()  LL_C2_EXTI_EnableEvent_32_63(PWR_EXTI_LINE_PVM3)
#else
#define __HAL_PWR_PVM3_EXTI_ENABLE_EVENT()  LL_EXTI_EnableEvent_32_63(PWR_EXTI_LINE_PVM3)
#endif

/**
  * @brief Disable the PVM3 Event line.
  * @retval None
  */
#if defined(CORE_CM0PLUS)
#define __HAL_PWR_PVM3_EXTI_DISABLE_EVENT()   LL_C2_EXTI_DisableEvent_32_63(PWR_EXTI_LINE_PVM3)
#else
#define __HAL_PWR_PVM3_EXTI_DISABLE_EVENT()   LL_EXTI_DisableEvent_32_63(PWR_EXTI_LINE_PVM3)
#endif

/**
  * @brief Enable the PVM3 Extended Interrupt Rising Trigger.
  * @note  PVM3 flag polarity is inverted compared to EXTI line, therefore
  *        EXTI rising and falling logic edges are inverted versus PVM3 voltage edges.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_ENABLE_RISING_EDGE()   LL_EXTI_EnableFallingTrig_32_63(PWR_EXTI_LINE_PVM3)

/**
  * @brief Disable the PVM3 Extended Interrupt Rising Trigger.
  * @note  PVM3 flag polarity is inverted compared to EXTI line, therefore
  *        EXTI rising and falling logic edges are inverted versus PVM3 voltage edges.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_DISABLE_RISING_EDGE()  LL_EXTI_DisableFallingTrig_32_63(PWR_EXTI_LINE_PVM3)

/**
  * @brief Enable the PVM3 Extended Interrupt Falling Trigger.
  * @note  PVM3 flag polarity is inverted compared to EXTI line, therefore
  *        EXTI rising and falling logic edges are inverted versus PVM3 voltage edges.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_ENABLE_FALLING_EDGE()   LL_EXTI_EnableRisingTrig_32_63(PWR_EXTI_LINE_PVM3)


/**
  * @brief Disable the PVM3 Extended Interrupt Falling Trigger.
  * @note  PVM3 flag polarity is inverted compared to EXTI line, therefore
  *        EXTI rising and falling logic edges are inverted versus PVM3 voltage edges.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_DISABLE_FALLING_EDGE()  LL_EXTI_DisableRisingTrig_32_63(PWR_EXTI_LINE_PVM3)

/**
  * @brief  PVM3 EXTI line configuration: set rising & falling edge trigger.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_ENABLE_RISING_FALLING_EDGE()  \
  do {                                                    \
    __HAL_PWR_PVM3_EXTI_ENABLE_RISING_EDGE();             \
    __HAL_PWR_PVM3_EXTI_ENABLE_FALLING_EDGE();            \
  } while(0)

/**
  * @brief Disable the PVM3 Extended Interrupt Rising & Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_DISABLE_RISING_FALLING_EDGE()  \
  do {                                                     \
    __HAL_PWR_PVM3_EXTI_DISABLE_RISING_EDGE();             \
    __HAL_PWR_PVM3_EXTI_DISABLE_FALLING_EDGE();            \
  } while(0)

/**
  * @brief  Generate a Software interrupt on selected EXTI line.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_GENERATE_SWIT() LL_EXTI_GenerateSWI_32_63(PWR_EXTI_LINE_PVM3)

/**
  * @brief Check whether the specified PVM3 EXTI interrupt flag is set or not.
  * @retval EXTI PVM3 Line Status.
  */
#define __HAL_PWR_PVM3_EXTI_GET_FLAG()      LL_EXTI_ReadFlag_32_63(PWR_EXTI_LINE_PVM3)

/**
  * @brief Clear the PVM3 EXTI flag.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_CLEAR_FLAG()    LL_EXTI_ClearFlag_32_63(PWR_EXTI_LINE_PVM3)


/**
  * @brief Configure the main internal regulator output voltage.
  * @param __REGULATOR__ specifies the regulator output voltage to achieve
  *         a tradeoff between performance and power consumption.
  *          This parameter can be one of the following values:
  *            @arg @ref PWR_REGULATOR_VOLTAGE_SCALE1  Regulator voltage output range 1 mode,
  *                                                typical output voltage at 1.2 V,
  *                                                system frequency up to 64 MHz.
  *            @arg @ref PWR_REGULATOR_VOLTAGE_SCALE2  Regulator voltage output range 2 mode,
  *                                                typical output voltage at 1.0 V,
  *                                                system frequency up to 16 MHz.
  * @note  This macro is similar to HAL_PWREx_ControlVoltageScaling() API but doesn't check
  *        whether or not VOSF flag is cleared when moving from range 2 to range 1. User
  *        may resort to __HAL_PWR_GET_FLAG() macro to check VOSF bit resetting.
  * @retval None
  */
#define __HAL_PWR_VOLTAGESCALING_CONFIG(__REGULATOR__) do {                                                     \
                                                            __IO uint32_t tmpreg;                               \
                                                            MODIFY_REG(PWR->CR1, PWR_CR1_VOS, (__REGULATOR__)); \
                                                            /* Delay after an RCC peripheral clock enabling */  \
                                                            tmpreg = READ_BIT(PWR->CR1, PWR_CR1_VOS);           \
                                                            UNUSED(tmpreg);                                     \
                                                          } while(0)

/**
  * @}
  */

/* Private macros --------------------------------------------------------*/
/** @addtogroup  PWREx_Private_Macros   PWR Extended Private Macros
  * @{
  */

#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WAKEUP_PIN1_HIGH) || \
                                ((PIN) == PWR_WAKEUP_PIN2_HIGH) || \
                                ((PIN) == PWR_WAKEUP_PIN3_HIGH) || \
                                ((PIN) == PWR_WAKEUP_PIN1_LOW) || \
                                ((PIN) == PWR_WAKEUP_PIN2_LOW) || \
                                ((PIN) == PWR_WAKEUP_PIN3_LOW))

#define IS_PWR_PVM_TYPE(__TYPE__) (((__TYPE__) == PWR_PVM_3))

#define IS_PWR_PVM_MODE(__MODE__) (((__MODE__) == PWR_PVM_MODE_NORMAL)              ||\
                                   ((__MODE__) == PWR_PVM_MODE_IT_RISING)           ||\
                                   ((__MODE__) == PWR_PVM_MODE_IT_FALLING)          ||\
                                   ((__MODE__) == PWR_PVM_MODE_IT_RISING_FALLING))

#define IS_PWR_FLASH_POWERDOWN(__MODE__)    ((((__MODE__) & (PWR_FLASHPD_LPRUN | PWR_FLASHPD_LPSLEEP)) != 0x00UL) && \
                                             (((__MODE__) & ~(PWR_FLASHPD_LPRUN | PWR_FLASHPD_LPSLEEP)) == 0x00UL))

#define IS_PWR_VOLTAGE_SCALING_RANGE(__RANGE__) (((__RANGE__) == PWR_REGULATOR_VOLTAGE_SCALE1) || \
                                                 ((__RANGE__) == PWR_REGULATOR_VOLTAGE_SCALE2))

#define IS_PWR_BATTERY_RESISTOR_SELECT(__RESISTOR__) (((__RESISTOR__) == PWR_BATTERY_CHARGING_RESISTOR_5) ||\
                                                      ((__RESISTOR__) == PWR_BATTERY_CHARGING_RESISTOR_1_5))

#define IS_PWR_BATTERY_CHARGING(__CHARGING__) (((__CHARGING__) == PWR_BATTERY_CHARGING_DISABLE) ||\
                                               ((__CHARGING__) == PWR_BATTERY_CHARGING_ENABLE))

#define IS_PWR_GPIO_BIT_NUMBER(__BIT_NUMBER__) (((__BIT_NUMBER__) & GPIO_PIN_MASK) != (uint32_t)0x00)

#define IS_PWR_GPIO(__GPIO__) (((__GPIO__) == PWR_GPIO_A) ||\
                               ((__GPIO__) == PWR_GPIO_B) ||\
                               ((__GPIO__) == PWR_GPIO_C) ||\
                               ((__GPIO__) == PWR_GPIO_H))

#define IS_PWR_SMPS_MODE(__SMPS_MODE__) (((__SMPS_MODE__) == PWR_SMPS_BYPASS)    ||\
                                         ((__SMPS_MODE__) == PWR_SMPS_STEP_DOWN))

#define IS_RADIO_BUSY_POLARITY(__RADIO_BUSY_POLARITY__) (((__RADIO_BUSY_POLARITY__) == PWR_RADIO_BUSY_POLARITY_RISING)  ||\
                                                         ((__RADIO_BUSY_POLARITY__) == PWR_RADIO_BUSY_POLARITY_FALLING))

#define IS_PWR_RADIO_BUSY_TRIGGER(__RADIO_BUSY_TRIGGER__) (((__RADIO_BUSY_TRIGGER__) == PWR_RADIO_BUSY_TRIGGER_NONE)  ||\
                                                           ((__RADIO_BUSY_TRIGGER__) == PWR_RADIO_BUSY_TRIGGER_WU_IT))

#define IS_RADIO_IRQ_TRIGGER(__RADIO_IRQ_TRIGGER__) (((__RADIO_IRQ_TRIGGER__) == PWR_RADIO_IRQ_TRIGGER_NONE)  ||\
                                                     ((__RADIO_IRQ_TRIGGER__) == PWR_RADIO_IRQ_TRIGGER_WU_IT))

#if defined(DUAL_CORE)
#define IS_PWR_CORE(__CPU__)  (((__CPU__) == PWR_CORE_CPU1) || ((__CPU__) == PWR_CORE_CPU2))
#else
#define IS_PWR_CORE(__CPU__)  (((__CPU__) == PWR_CORE_CPU1))
#endif

#if defined(DUAL_CORE)
#define IS_PWR_CORE_HOLD_RELEASE(__CPU__)  ((__CPU__) == PWR_CORE_CPU2)
#endif

/**
  * @}
  */


/** @addtogroup PWREx_Exported_Functions PWR Extended Exported Functions
  * @{
  */

/** @addtogroup PWREx_Exported_Functions_Group1 Extended Peripheral Control functions
  * @{
  */


/* Peripheral Control functions  **********************************************/
uint32_t          HAL_PWREx_GetVoltageRange(void);
HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling);

void              HAL_PWREx_EnableBatteryCharging(uint32_t ResistorSelection);
void              HAL_PWREx_DisableBatteryCharging(void);

void              HAL_PWREx_EnableInternalWakeUpLine(void);
void              HAL_PWREx_DisableInternalWakeUpLine(void);

void              HAL_PWREx_SetRadioBusyPolarity(uint32_t RadioBusyPolarity);
void              HAL_PWREx_SetRadioBusyTrigger(uint32_t RadioBusyTrigger);
void              HAL_PWREx_SetRadioIRQTrigger(uint32_t RadioIRQTrigger);

void              HAL_PWREx_EnableHOLDC2IT(void);
void              HAL_PWREx_DisableHOLDC2IT(void);

void              HAL_PWREx_HoldCore(uint32_t CPU);
void              HAL_PWREx_ReleaseCore(uint32_t CPU);

#ifdef CORE_CM0PLUS
void              HAL_PWREx_EnableWakeUp_ILAC(void);
void              HAL_PWREx_DisableWakeUp_ILAC(void);
uint32_t          HAL_PWREx_IsEnabledWakeUp_ILAC(void);
#endif

HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber);
void              HAL_PWREx_EnablePullUpPullDownConfig(void);
void              HAL_PWREx_DisablePullUpPullDownConfig(void);

void              HAL_PWREx_EnableSRAMRetention(void);
void              HAL_PWREx_DisableSRAMRetention(void);

void              HAL_PWREx_EnableFlashPowerDown(uint32_t PowerMode);
void              HAL_PWREx_DisableFlashPowerDown(uint32_t PowerMode);

void              HAL_PWREx_EnableWPVD(void);
void              HAL_PWREx_DisableWPVD(void);
void              HAL_PWREx_EnableBORPVD_ULP(void);
void              HAL_PWREx_DisableBORPVD_ULP(void);

void              HAL_PWREx_EnablePVM3(void);
void              HAL_PWREx_DisablePVM3(void);

HAL_StatusTypeDef HAL_PWREx_ConfigPVM(PWR_PVMTypeDef *sConfigPVM);

void              HAL_PWREx_SetRadioEOL(uint32_t RadioEOL);
void              HAL_PWREx_SMPS_SetMode(uint32_t OperatingMode);
uint32_t          HAL_PWREx_SMPS_GetEffectiveMode(void);

/* Low Power modes configuration functions ************************************/
void              HAL_PWREx_EnableLowPowerRunMode(void);
HAL_StatusTypeDef HAL_PWREx_DisableLowPowerRunMode(void);

void              HAL_PWREx_EnterSTOP0Mode(uint8_t STOPEntry);
void              HAL_PWREx_EnterSTOP1Mode(uint8_t STOPEntry);
void              HAL_PWREx_EnterSTOP2Mode(uint8_t STOPEntry);
void              HAL_PWREx_EnterSHUTDOWNMode(void);

void              HAL_PWREx_PVD_PVM_IRQHandler(void);

void              HAL_PWREx_PVM3Callback(void);

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

#ifdef __cplusplus
}
#endif


#endif /* STM32WLxx_HAL_PWR_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
