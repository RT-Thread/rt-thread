/**
  ******************************************************************************
  * @file    stm32h7rsxx_hal.h
  * @author  MCD Application Team
  * @brief   This file contains all the functions prototypes for the HAL
  *          module driver.
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7RSxx_HAL_H
#define STM32H7RSxx_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_hal_conf.h"

/** @addtogroup STM32H7RSxx_HAL_Driver
  * @{
  */

/** @addtogroup HAL
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup HAL_TICK_FREQ Tick Frequency
  * @{
  */
/**
  * @brief  HAL Tick frequency
  */
typedef enum
{
  HAL_TICK_FREQ_10HZ         = 100U,
  HAL_TICK_FREQ_100HZ        = 10U,
  HAL_TICK_FREQ_1KHZ         = 1U,
  HAL_TICK_FREQ_DEFAULT      = HAL_TICK_FREQ_1KHZ
} HAL_TickFreqTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup REV_ID device revision ID
  * @{
  */
#define REV_ID_A 0x1003U  /*!< STM32H7Rx/Sx rev.A */
/**
  * @}
  */

/** @defgroup HAL_Exported_Constants HAL Exported Constants
  * @{
  */
/**
  * @brief STM32H7RSxx HAL Driver version number
  */
#define STM32H7RSXX_HAL_VERSION_MAIN   (0x01U) /*!< [31:24] main version */
#define STM32H7RSXX_HAL_VERSION_SUB1   (0x00U) /*!< [23:16] sub1 version */
#define STM32H7RSXX_HAL_VERSION_SUB2   (0x00U) /*!< [15:8]  sub2 version */
#define STM32H7RSXX_HAL_VERSION_RC     (0x00U) /*!< [7:0]  release candidate */
#define STM32H7RSXX_HAL_VERSION        ((STM32H7RSXX_HAL_VERSION_MAIN  << 24U)\
                                        |(STM32H7RSXX_HAL_VERSION_SUB1 << 16U)\
                                        |(STM32H7RSXX_HAL_VERSION_SUB2 << 8U )\
                                        |(STM32H7RSXX_HAL_VERSION_RC))
/**
  * @}
  */

/** @defgroup SBS_Exported_Constants SBS Exported Constants
  * @{
  */

/** @defgroup SBS_HDPL_Value HDPL Value
  * @{
  */
#define SBS_HDPL_VALUE_0               0x000000B4U               /*!< Hide protection level 0 */
#define SBS_HDPL_VALUE_1               0x00000051U               /*!< Hide protection level 1 */
#define SBS_HDPL_VALUE_2               0x0000008AU               /*!< Hide protection level 2 */
#define SBS_HDPL_VALUE_3               0x0000006FU               /*!< Hide protection level 3 */
/**
  * @}
  */

/** @defgroup SBS_Timer_Break_Inputs Timer Break Inputs
  * @{
  */
#define SBS_TIMER_BREAK_LOCK_PVD       SBS_BKLOCKR_PVD_BL        /*!< PVD break lock */
#define SBS_TIMER_BREAK_LOCK_FLASH     SBS_BKLOCKR_FLASHECC_BL   /*!< FLASH ECC error break lock */
#define SBS_TIMER_BREAK_LOCK_CORE      SBS_BKLOCKR_CM7LCKUP_BL   /*!< Cortex-M7 lockup break lock */
#define SBS_TIMER_BREAK_LOCK_BKPRAM    SBS_BKLOCKR_BKRAMECC_BL   /*!< Backup RAM ECC error break lock */
#define SBS_TIMER_BREAK_LOCK_DTCM      SBS_BKLOCKR_DTCMECC_BL    /*!< DTCM ECC error break lock */
#define SBS_TIMER_BREAK_LOCK_ITCM      SBS_BKLOCKR_ITCMECC_BL    /*!< ITCM ECC error break lock */
#define SBS_TIMER_BREAK_LOCK_AXISRAM3  SBS_BKLOCKR_ARAM3ECC_BL   /*!< AXISRAM3 ECC error break lock */
#define SBS_TIMER_BREAK_LOCK_AXISRAM1  SBS_BKLOCKR_ARAM1ECC_BL   /*!< AXISRAM1 ECC error break lock */
/**
  * @}
  */

/** @defgroup SBS_FPU_Interrupts FPU Interrupts
  * @{
  */
#define SBS_IT_FPU_IOC                 SBS_FPUIMR_FPU_IE_0       /*!< Floating Point Unit Invalid operation Interrupt */
#define SBS_IT_FPU_DZC                 SBS_FPUIMR_FPU_IE_1       /*!< Floating Point Unit Divide-by-zero Interrupt */
#define SBS_IT_FPU_UFC                 SBS_FPUIMR_FPU_IE_2       /*!< Floating Point Unit Underflow Interrupt */
#define SBS_IT_FPU_OFC                 SBS_FPUIMR_FPU_IE_3       /*!< Floating Point Unit Overflow Interrupt */
#define SBS_IT_FPU_IDC                 SBS_FPUIMR_FPU_IE_4       /*!< Floating Point Unit Input denormal Interrupt */
#define SBS_IT_FPU_IXC                 SBS_FPUIMR_FPU_IE_5       /*!< Floating Point Unit Inexact Interrupt */
/**
  * @}
  */

/** @defgroup SBS_Compensation_Cell_Selection Compensation Cell Selection
  * @{
  */
#define SBS_IO_ANALOG_CELL             SBS_CCCSR_COMP_EN         /*!< Compensation cell for the I/O analog switches */
#define SBS_IO_XSPI1_CELL              SBS_CCCSR_XSPI1_COMP_EN   /*!< Compensation cell for the I/O of the XSPI1 */
#define SBS_IO_XSPI2_CELL              SBS_CCCSR_XSPI2_COMP_EN   /*!< Compensation cell for the I/O of the XSPI2 */
/**
  * @}
  */

/** @defgroup SBS_Compensation_Cell_Ready_Selection Compensation Cell Ready Selection
  * @{
  */
#define SBS_IO_ANALOG_CELL_READY       SBS_CCCSR_COMP_RDY        /*!< Ready flag of compensation cell for the I/O analog switches */
#define SBS_IO_XSPI1_CELL_READY        SBS_CCCSR_XSPI1_COMP_RDY  /*!< Ready flag of compensation cell for the I/O of the XSPI1 */
#define SBS_IO_XSPI2_CELL_READY        SBS_CCCSR_XSPI2_COMP_RDY  /*!< Ready flag of compensation cell for the I/O of the XSPI2 */
/**
  * @}
  */

/** @defgroup SBS_IO_Compensation_Code_Config IO Compensation Code config
  * @{
  */
#define SBS_IO_CELL_CODE               0UL                       /*!< Code from the cell */
#define SBS_IO_REGISTER_CODE           1UL                       /*!< Code from the values in the cell code register */
/**
  * @}
  */

/** @defgroup SBS_IO_HSLV_Selection IO High Speed at Low Voltage Selection
  * @{
  */
#define SBS_IO_ANALOG_HSLV             SBS_CCCSR_IOHSLV          /*!< High speed at low voltage for the I/O analog switches */
#define SBS_IO_XSPI1_HSLV              SBS_CCCSR_XSPI1_IOHSLV    /*!< High speed at low voltage for the I/O of the XSPI1 */
#define SBS_IO_XSPI2_HSLV              SBS_CCCSR_XSPI2_IOHSLV    /*!< High speed at low voltage for the I/O of the XSPI2 */
/**
  * @}
  */

/** @defgroup SBS_Ethernet_PHY_Config Ethernet PHY config
  * @{
  */
#define SBS_ETHERNET_PHY_GMII_OR_MII    0U                       /*!< GMII or MII */
#define SBS_ETHERNET_PHY_RMII           SBS_PMCR_ETH_PHYSEL_2    /*!< RMII */
/**
  * @}
  */

/** @defgroup SBS_ECC_AXISRAM_WS_Config ECC AXISRAMs Wait State when ECC=0 config
  * @{
  */
#define SBS_AXISRAM_WS_0               0U                         /*!< 0 Wait state */
#define SBS_AXISRAM_WS_1               SBS_PMCR_AXISRAM_WS        /*!< 1 Wait state */
/**
  * @}
  */

/** @defgroup SBS_EXTI_Port EXTI Port configuration
  * @{
  */
#define SBS_EXTI_PIN_PORTA             0x00UL                     /*!< Port A pin input of EXTI event detection */
#define SBS_EXTI_PIN_PORTB             0x01UL                     /*!< Port B pin input of EXTI event detection */
#define SBS_EXTI_PIN_PORTC             0x02UL                     /*!< Port C pin input of EXTI event detection */
#define SBS_EXTI_PIN_PORTD             0x03UL                     /*!< Port D pin input of EXTI event detection */
#define SBS_EXTI_PIN_PORTE             0x04UL                     /*!< Port E pin input of EXTI event detection */
#define SBS_EXTI_PIN_PORTF             0x05UL                     /*!< Port F pin input of EXTI event detection */
#define SBS_EXTI_PIN_PORTG             0x06UL                     /*!< Port G pin input of EXTI event detection */
#define SBS_EXTI_PIN_PORTH             0x07UL                     /*!< Port H pin input of EXTI event detection */
#define SBS_EXTI_PIN_PORTM             0x0CUL                     /*!< Port M pin input of EXTI event detection */
#define SBS_EXTI_PIN_PORTN             0x0DUL                     /*!< Port N pin input of EXTI event detection */
#define SBS_EXTI_PIN_PORTO             0x0EUL                     /*!< Port O pin input of EXTI event detection */
#define SBS_EXTI_PIN_PORTP             0x0FUL                     /*!< Port P pin input of EXTI event detection */
/**
  * @}
  */

/** @defgroup AXIM_Exported_Constants AXIM Exported Constants
  * @{
  */

/** @defgroup AXIM_ASIB_READ_ISSUING_CAP AXIM ASIBs Read Issuing Capability
  * @{
  */
#define AXIM_ASIB_READ_ISS_NORMAL       0U                         /*!< Normal issuing capability */
#define AXIM_ASIB_READ_ISS_FORCE_TO_1   AXIM_ASIB_FNMOD_READ_ISS   /*!< Force issuing capability to 1 */
/**
  * @}
  */

/** @defgroup AXIM_ASIB_WRITE_ISSUING_CAP AXIM ASIBs Write Issuing Capability
  * @{
  */
#define AXIM_ASIB_WRITE_ISS_NORMAL      0U                          /*!< Normal issuing capability */
#define AXIM_ASIB_WRITE_ISS_FORCE_TO_1  AXIM_ASIB_FNMOD_WRITE_ISS   /*!< Force issuing capability to 1 */
/**
  * @}
  */

/** @defgroup AXIM_AMIB_READ_ISSUING_CAP AXIM AMIBs Read Issuing Capability
  * @{
  */
#define AXIM_AMIB_READ_ISS_NORMAL       0U                         /*!< Normal issuing capability */
#define AXIM_AMIB_READ_ISS_FORCE_TO_1   AXIM_AMIB_FNMOD_READ_ISS   /*!< Force issuing capability to 1 */
/**
  * @}
  */

/** @defgroup AXIM_AMIB_WRITE_ISSUING_CAP AXIM AMIBs Write Issuing Capability
  * @{
  */
#define AXIM_AMIB_WRITE_ISS_NORMAL      0U                          /*!< Normal issuing capability */
#define AXIM_AMIB_WRITE_ISS_FORCE_TO_1  AXIM_AMIB_FNMOD_WRITE_ISS   /*!< Force issuing capability to 1 */
/**
  * @}
  */

/** @defgroup AXIM_AMIB_READ_ISSUING_BM_CAP AXIM AMIBs Read Issuing Bus Matrix Capability
  * @{
  */
#define AXIM_AMIB_READ_ISS_BM_NORMAL       0U                         /*!< Normal issuing capability */
#define AXIM_AMIB_READ_ISS_BM_FORCE_TO_1   AXIM_AMIB_FNMOD_READ_ISS   /*!< Force issuing capability to 1 */
/**
  * @}
  */

/** @defgroup AXIM_AMIB_WRITE_ISSUING_BM_CAP AXIM AMIBs Write Issuing Bus Matrix Capability
  * @{
  */
#define AXIM_AMIB_WRITE_ISS_BM_NORMAL      0U                          /*!< Normal issuing capability */
#define AXIM_AMIB_WRITE_ISS_BM_FORCE_TO_1  AXIM_AMIB_FNMOD_WRITE_ISS   /*!< Force issuing capability to 1 */
/**
  * @}
  */
/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup DBGMCU_Exported_Macros DBGMCU Exported Macros
  * @{
  */

/** @brief  Freeze/Unfreeze Peripherals in Debug mode
  */
#define __HAL_DBGMCU_FREEZE_GPDMA0()         SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_0)
#define __HAL_DBGMCU_UNFREEZE_GPDMA0()       CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_0)

#define __HAL_DBGMCU_FREEZE_GPDMA1()         SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_1)
#define __HAL_DBGMCU_UNFREEZE_GPDMA1()       CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_1)

#define __HAL_DBGMCU_FREEZE_GPDMA2()         SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_2)
#define __HAL_DBGMCU_UNFREEZE_GPDMA2()       CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_2)

#define __HAL_DBGMCU_FREEZE_GPDMA3()         SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_3)
#define __HAL_DBGMCU_UNFREEZE_GPDMA3()       CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_3)

#define __HAL_DBGMCU_FREEZE_GPDMA4()         SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_4)
#define __HAL_DBGMCU_UNFREEZE_GPDMA4()       CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_4)

#define __HAL_DBGMCU_FREEZE_GPDMA5()         SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_5)
#define __HAL_DBGMCU_UNFREEZE_GPDMA5()       CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_5)

#define __HAL_DBGMCU_FREEZE_GPDMA6()         SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_6)
#define __HAL_DBGMCU_UNFREEZE_GPDMA6()       CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_6)

#define __HAL_DBGMCU_FREEZE_GPDMA7()         SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_7)
#define __HAL_DBGMCU_UNFREEZE_GPDMA7()       CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_7)

#define __HAL_DBGMCU_FREEZE_GPDMA8()         SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_8)
#define __HAL_DBGMCU_UNFREEZE_GPDMA8()       CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_8)

#define __HAL_DBGMCU_FREEZE_GPDMA9()         SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_9)
#define __HAL_DBGMCU_UNFREEZE_GPDMA9()       CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_9)

#define __HAL_DBGMCU_FREEZE_GPDMA10()        SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_10)
#define __HAL_DBGMCU_UNFREEZE_GPDMA10()      CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_10)

#define __HAL_DBGMCU_FREEZE_GPDMA11()        SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_11)
#define __HAL_DBGMCU_UNFREEZE_GPDMA11()      CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_11)

#define __HAL_DBGMCU_FREEZE_GPDMA12()        SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_12)
#define __HAL_DBGMCU_UNFREEZE_GPDMA12()      CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_12)

#define __HAL_DBGMCU_FREEZE_GPDMA13()        SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_13)
#define __HAL_DBGMCU_UNFREEZE_GPDMA13()      CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_13)

#define __HAL_DBGMCU_FREEZE_GPDMA14()        SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_14)
#define __HAL_DBGMCU_UNFREEZE_GPDMA14()      CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_14)

#define __HAL_DBGMCU_FREEZE_GPDMA15()        SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_15)
#define __HAL_DBGMCU_UNFREEZE_GPDMA15()      CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_GPDMA_15)

#define __HAL_DBGMCU_FREEZE_HPDMA0()         SET_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_0)
#define __HAL_DBGMCU_UNFREEZE_HPDMA0()       CLEAR_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_0)

#define __HAL_DBGMCU_FREEZE_HPDMA1()         SET_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_1)
#define __HAL_DBGMCU_UNFREEZE_HPDMA1()       CLEAR_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_1)

#define __HAL_DBGMCU_FREEZE_HPDMA2()         SET_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_2)
#define __HAL_DBGMCU_UNFREEZE_HPDMA2()       CLEAR_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_2)

#define __HAL_DBGMCU_FREEZE_HPDMA3()         SET_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_3)
#define __HAL_DBGMCU_UNFREEZE_HPDMA3()       CLEAR_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_3)

#define __HAL_DBGMCU_FREEZE_HPDMA4()         SET_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_4)
#define __HAL_DBGMCU_UNFREEZE_HPDMA4()       CLEAR_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_4)

#define __HAL_DBGMCU_FREEZE_HPDMA5()         SET_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_5)
#define __HAL_DBGMCU_UNFREEZE_HPDMA5()       CLEAR_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_5)

#define __HAL_DBGMCU_FREEZE_HPDMA6()         SET_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_6)
#define __HAL_DBGMCU_UNFREEZE_HPDMA6()       CLEAR_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_6)

#define __HAL_DBGMCU_FREEZE_HPDMA7()         SET_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_7)
#define __HAL_DBGMCU_UNFREEZE_HPDMA7()       CLEAR_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_7)

#define __HAL_DBGMCU_FREEZE_HPDMA8()         SET_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_8)
#define __HAL_DBGMCU_UNFREEZE_HPDMA8()       CLEAR_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_8)

#define __HAL_DBGMCU_FREEZE_HPDMA9()         SET_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_9)
#define __HAL_DBGMCU_UNFREEZE_HPDMA9()       CLEAR_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_9)

#define __HAL_DBGMCU_FREEZE_HPDMA10()        SET_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_10)
#define __HAL_DBGMCU_UNFREEZE_HPDMA10()      CLEAR_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_10)

#define __HAL_DBGMCU_FREEZE_HPDMA11()        SET_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_11)
#define __HAL_DBGMCU_UNFREEZE_HPDMA11()      CLEAR_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_11)

#define __HAL_DBGMCU_FREEZE_HPDMA12()        SET_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_12)
#define __HAL_DBGMCU_UNFREEZE_HPDMA12()      CLEAR_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_12)

#define __HAL_DBGMCU_FREEZE_HPDMA13()        SET_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_13)
#define __HAL_DBGMCU_UNFREEZE_HPDMA13()      CLEAR_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_13)

#define __HAL_DBGMCU_FREEZE_HPDMA14()        SET_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_14)
#define __HAL_DBGMCU_UNFREEZE_HPDMA14()      CLEAR_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_14)

#define __HAL_DBGMCU_FREEZE_HPDMA15()        SET_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_15)
#define __HAL_DBGMCU_UNFREEZE_HPDMA15()      CLEAR_BIT(DBGMCU->AHB5FZR, DBGMCU_AHB5FZR_HPDMA_15)

#define __HAL_DBGMCU_FREEZE_I2C1()           SET_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_I2C1)
#define __HAL_DBGMCU_UNFREEZE_I2C1()         CLEAR_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_I2C1)

#define __HAL_DBGMCU_FREEZE_I2C2()           SET_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_I2C2)
#define __HAL_DBGMCU_UNFREEZE_I2C2()         CLEAR_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_I2C2)

#define __HAL_DBGMCU_FREEZE_I2C3()           SET_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_I2C3)
#define __HAL_DBGMCU_UNFREEZE_I2C3()         CLEAR_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_I2C3)

#define __HAL_DBGMCU_FREEZE_TIM2()           SET_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_TIM2)
#define __HAL_DBGMCU_UNFREEZE_TIM2()         CLEAR_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_TIM2)

#define __HAL_DBGMCU_FREEZE_TIM3()           SET_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_TIM3)
#define __HAL_DBGMCU_UNFREEZE_TIM3()         CLEAR_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_TIM3)

#define __HAL_DBGMCU_FREEZE_TIM4()           SET_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_TIM4)
#define __HAL_DBGMCU_UNFREEZE_TIM4()         CLEAR_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_TIM4)

#define __HAL_DBGMCU_FREEZE_TIM5()           SET_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_TIM5)
#define __HAL_DBGMCU_UNFREEZE_TIM5()         CLEAR_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_TIM5)

#define __HAL_DBGMCU_FREEZE_TIM6()           SET_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_TIM6)
#define __HAL_DBGMCU_UNFREEZE_TIM6()         CLEAR_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_TIM6)

#define __HAL_DBGMCU_FREEZE_TIM7()           SET_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_TIM7)
#define __HAL_DBGMCU_UNFREEZE_TIM7()         CLEAR_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_TIM7)

#define __HAL_DBGMCU_FREEZE_TIM9()           SET_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_TIM9)
#define __HAL_DBGMCU_UNFREEZE_TIM9()         CLEAR_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_TIM9)

#define __HAL_DBGMCU_FREEZE_TIM12()          SET_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_TIM12)
#define __HAL_DBGMCU_UNFREEZE_TIM12()        CLEAR_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_TIM12)

#define __HAL_DBGMCU_FREEZE_TIM13()          SET_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_TIM13)
#define __HAL_DBGMCU_UNFREEZE_TIM13()        CLEAR_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_TIM13)

#define __HAL_DBGMCU_FREEZE_TIM14()          SET_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_TIM14)
#define __HAL_DBGMCU_UNFREEZE_TIM14()        CLEAR_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_TIM14)

#define __HAL_DBGMCU_FREEZE_TIM1()           SET_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_TIM1)
#define __HAL_DBGMCU_UNFREEZE_TIM1()         CLEAR_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_TIM1)

#define __HAL_DBGMCU_FREEZE_TIM15()          SET_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_TIM15)
#define __HAL_DBGMCU_UNFREEZE_TIM15()        CLEAR_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_TIM15)

#define __HAL_DBGMCU_FREEZE_TIM16()          SET_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_TIM16)
#define __HAL_DBGMCU_UNFREEZE_TIM16()        CLEAR_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_TIM16)

#define __HAL_DBGMCU_FREEZE_TIM17()          SET_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_TIM17)
#define __HAL_DBGMCU_UNFREEZE_TIM17()        CLEAR_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_TIM17)

#define __HAL_DBGMCU_FREEZE_LPTIM1()         SET_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_LPTIM1)
#define __HAL_DBGMCU_UNFREEZE_LPTIM1()       CLEAR_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_LPTIM1)

#define __HAL_DBGMCU_FREEZE_LPTIM2()         SET_BIT(DBGMCU->APB4FZR, DBGMCU_APB4FZR_LPTIM2)
#define __HAL_DBGMCU_UNFREEZE_LPTIM2()       CLEAR_BIT(DBGMCU->APB4FZR, DBGMCU_APB4FZR_LPTIM2)

#define __HAL_DBGMCU_FREEZE_LPTIM3()         SET_BIT(DBGMCU->APB4FZR, DBGMCU_APB4FZR_LPTIM3)
#define __HAL_DBGMCU_UNFREEZE_LPTIM3()       CLEAR_BIT(DBGMCU->APB4FZR, DBGMCU_APB4FZR_LPTIM3)

#define __HAL_DBGMCU_FREEZE_LPTIM4()         SET_BIT(DBGMCU->APB4FZR, DBGMCU_APB4FZR_LPTIM4)
#define __HAL_DBGMCU_UNFREEZE_LPTIM4()       CLEAR_BIT(DBGMCU->APB4FZR, DBGMCU_APB4FZR_LPTIM4)

#define __HAL_DBGMCU_FREEZE_LPTIM5()         SET_BIT(DBGMCU->APB4FZR, DBGMCU_APB4FZR_LPTIM5)
#define __HAL_DBGMCU_UNFREEZE_LPTIM5()       CLEAR_BIT(DBGMCU->APB4FZR, DBGMCU_APB4FZR_LPTIM5)

#define __HAL_DBGMCU_FREEZE_IWDG()           SET_BIT(DBGMCU->APB4FZR, DBGMCU_APB4FZR_IWDG)
#define __HAL_DBGMCU_UNFREEZE_IWDG()         CLEAR_BIT(DBGMCU->APB4FZR, DBGMCU_APB4FZR_IWDG)

#define __HAL_DBGMCU_FREEZE_PWM1()           SET_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_PWM1)
#define __HAL_DBGMCU_UNFREEZE_PWM1()         CLEAR_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_PWM1)

#define __HAL_DBGMCU_FREEZE_RTC()            SET_BIT(DBGMCU->APB4FZR, DBGMCU_APB4FZR_RTC)
#define __HAL_DBGMCU_UNFREEZE_RTC()          CLEAR_BIT(DBGMCU->APB4FZR, DBGMCU_APB4FZR_RTC)

#define __HAL_DBGMCU_FREEZE_WWDG()           SET_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_WWDG)
#define __HAL_DBGMCU_UNFREEZE_WWDG()         CLEAR_BIT(DBGMCU->APB1FZR, DBGMCU_APB1FZR_WWDG)

/**
  * @}
  */

/** @defgroup SBS_Exported_Macros SBS Exported Macros
  * @{
  */

/** @brief  Floating Point Unit interrupt enable/disable macros
  * @param __INTERRUPT__  This parameter can be a value of @ref SBS_FPU_Interrupts
  */
#define __HAL_SBS_FPU_INTERRUPT_ENABLE(__INTERRUPT__)    do { \
                                                              assert_param(IS_SBS_FPU_INTERRUPT((__INTERRUPT__))); \
                                                              SET_BIT(SBS->FPUIMR, (__INTERRUPT__)); \
                                                            } while(0)

#define __HAL_SBS_FPU_INTERRUPT_DISABLE(__INTERRUPT__)   do { \
                                                              assert_param(IS_SBS_FPU_INTERRUPT((__INTERRUPT__))); \
                                                              CLEAR_BIT(SBS->FPUIMR, (__INTERRUPT__)); \
                                                            } while(0)

/** @brief  Check SBS Memories Erase Status Flags.
  * @retval The state of memory erase.
  */
#define __HAL_SBS_GET_MEMORIES_ERASE_STATUS()            ((SBS->MESR) & (SBS_MESR_MEF))

/**
  * @}
  */


/* Private macros ------------------------------------------------------------*/
/** @defgroup VREFBUF_VoltageScale VREFBUF Voltage Scale
  * @{
  */
#define VREFBUF_VOLTAGE_SCALE0   VREFBUF_CSR_VRS_OUT1   /*!< Voltage reference scale 0 (VREF_OUT1) */
#define VREFBUF_VOLTAGE_SCALE1   VREFBUF_CSR_VRS_OUT2   /*!< Voltage reference scale 1 (VREF_OUT2) */
#define VREFBUF_VOLTAGE_SCALE2   VREFBUF_CSR_VRS_OUT3   /*!< Voltage reference scale 2 (VREF_OUT3) */
#define VREFBUF_VOLTAGE_SCALE3   VREFBUF_CSR_VRS_OUT4   /*!< Voltage reference scale 3 (VREF_OUT4) */


#define IS_VREFBUF_VOLTAGE_SCALE(__SCALE__)  (((__SCALE__) == VREFBUF_VOLTAGE_SCALE0) || \
                                              ((__SCALE__) == VREFBUF_VOLTAGE_SCALE1) || \
                                              ((__SCALE__) == VREFBUF_VOLTAGE_SCALE2) || \
                                              ((__SCALE__) == VREFBUF_VOLTAGE_SCALE3))


/**
  * @}
  */

/** @defgroup VREFBUF_HighImpedance VREFBUF High Impedance
  * @{
  */
#define VREFBUF_HIGH_IMPEDANCE_DISABLE  ((uint32_t)0x00000000) /*!< VREF_plus pin is internally connected to Voltage reference buffer output */
#define VREFBUF_HIGH_IMPEDANCE_ENABLE   VREFBUF_CSR_HIZ        /*!< VREF_plus pin is high impedance */

#define IS_VREFBUF_HIGH_IMPEDANCE(__VALUE__)  (((__VALUE__) == VREFBUF_HIGH_IMPEDANCE_DISABLE) || \
                                               ((__VALUE__) == VREFBUF_HIGH_IMPEDANCE_ENABLE))

#define IS_VREFBUF_TRIMMING(__VALUE__)        ((__VALUE__) <= VREFBUF_CCR_TRIM)

/**
  * @}
  */

/** @addtogroup SBS_Private_Macros
  * @{
  */
#define IS_SBS_FPU_INTERRUPT(__INTERRUPT__)      ((((__INTERRUPT__) & SBS_IT_FPU_IOC) == SBS_IT_FPU_IOC) || \
                                                  (((__INTERRUPT__) & SBS_IT_FPU_DZC) == SBS_IT_FPU_DZC) || \
                                                  (((__INTERRUPT__) & SBS_IT_FPU_UFC) == SBS_IT_FPU_UFC) || \
                                                  (((__INTERRUPT__) & SBS_IT_FPU_OFC) == SBS_IT_FPU_OFC) || \
                                                  (((__INTERRUPT__) & SBS_IT_FPU_IDC) == SBS_IT_FPU_IDC) || \
                                                  (((__INTERRUPT__) & SBS_IT_FPU_IXC) == SBS_IT_FPU_IXC))

#define IS_SBS_HDPL(__LEVEL__)                   (((__LEVEL__) == SBS_HDPL_VALUE_0) || \
                                                  ((__LEVEL__) == SBS_HDPL_VALUE_1) || \
                                                  ((__LEVEL__) == SBS_HDPL_VALUE_2) || \
                                                  ((__LEVEL__) == SBS_HDPL_VALUE_3))

#define IS_SBS_COMPENSATION_CELL(__CELL__)       (((__CELL__) == SBS_IO_ANALOG_CELL) || \
                                                  ((__CELL__) == SBS_IO_XSPI1_CELL)  || \
                                                  ((__CELL__) == SBS_IO_XSPI2_CELL))

#define IS_SBS_COMPENSATION_CELL_READY(__CELL__) (((__CELL__) == SBS_IO_ANALOG_CELL_READY) || \
                                                  ((__CELL__) == SBS_IO_XSPI1_CELL_READY)  || \
                                                  ((__CELL__) == SBS_IO_XSPI2_CELL_READY))

#define IS_SBS_IOHSLV(__HSLV__)                  (((__HSLV__) == SBS_IO_ANALOG_HSLV) || \
                                                  ((__HSLV__) == SBS_IO_XSPI1_HSLV)  || \
                                                  ((__HSLV__) == SBS_IO_XSPI2_HSLV))

#define IS_SBS_EXTI_INPUT(__INPUT__)             ((__INPUT__) < 16U)

#define IS_SBS_EXTI_PIN(__PIN__)                 (((__PIN__) == SBS_EXTI_PIN_PORTA) || \
                                                  ((__PIN__) == SBS_EXTI_PIN_PORTB) || \
                                                  ((__PIN__) == SBS_EXTI_PIN_PORTC) || \
                                                  ((__PIN__) == SBS_EXTI_PIN_PORTD) || \
                                                  ((__PIN__) == SBS_EXTI_PIN_PORTE) || \
                                                  ((__PIN__) == SBS_EXTI_PIN_PORTF) || \
                                                  ((__PIN__) == SBS_EXTI_PIN_PORTG) || \
                                                  ((__PIN__) == SBS_EXTI_PIN_PORTH) || \
                                                  ((__PIN__) == SBS_EXTI_PIN_PORTM) || \
                                                  ((__PIN__) == SBS_EXTI_PIN_PORTN) || \
                                                  ((__PIN__) == SBS_EXTI_PIN_PORTO) || \
                                                  ((__PIN__) == SBS_EXTI_PIN_PORTP))
/**
  * @}
  */

/** @addtogroup AXIM_Private_Macros
  * @{
  */
#define IS_AXIM_ASIB_READ_ISS(__ISS__)          (((__ISS__) == AXIM_ASIB_READ_ISS_NORMAL) || \
                                                 ((__ISS__) == AXIM_ASIB_READ_ISS_FORCE_TO_1))

#define IS_AXIM_ASIB_WRITE_ISS(__ISS__)         (((__ISS__) == AXIM_ASIB_WRITE_ISS_NORMAL) || \
                                                 ((__ISS__) == AXIM_ASIB_WRITE_ISS_FORCE_TO_1))

#define IS_AXIM_QOS(__QOS__)                    ((__QOS__) <= AXIM_ASIB_READQOS_AR_QOS)

#define IS_AXIM_AMIB_READ_ISS(__ISS__)          (((__ISS__) == AXIM_AMIB_READ_ISS_NORMAL) || \
                                                 ((__ISS__) == AXIM_AMIB_READ_ISS_FORCE_TO_1))

#define IS_AXIM_AMIB_WRITE_ISS(__ISS__)         (((__ISS__) == AXIM_AMIB_WRITE_ISS_NORMAL) || \
                                                 ((__ISS__) == AXIM_AMIB_WRITE_ISS_FORCE_TO_1))

#define IS_AXIM_AMIB_READ_ISS_BM(__ISS__)       (((__ISS__) == AXIM_AMIB_READ_ISS_NORMAL) || \
                                                 ((__ISS__) == AXIM_AMIB_READ_ISS_FORCE_TO_1))

#define IS_AXIM_AMIB_WRITE_ISS_BM(__ISS__)      (((__ISS__) == AXIM_AMIB_WRITE_ISS_BM_NORMAL) || \
                                                 ((__ISS__) == AXIM_AMIB_WRITE_ISS_BM_FORCE_TO_1))

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @addtogroup HAL_Exported_Variables
  * @{
  */
extern __IO uint32_t        uwTick;
extern uint32_t             uwTickPrio;
extern HAL_TickFreqTypeDef  uwTickFreq;
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup HAL_Exported_Functions
  * @{
  */

/** @addtogroup HAL_Exported_Functions_Group1
  * @{
  */

/* Initialization and de-initialization functions  ****************************/
HAL_StatusTypeDef    HAL_Init(void);
HAL_StatusTypeDef    HAL_DeInit(void);
void                 HAL_MspInit(void);
void                 HAL_MspDeInit(void);
HAL_StatusTypeDef    HAL_InitTick(uint32_t TickPriority);

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group2
  * @{
  */

/* Peripheral Control functions  **********************************************/
void                 HAL_IncTick(void);
void                 HAL_Delay(uint32_t Delay);
uint32_t             HAL_GetTick(void);
uint32_t             HAL_GetTickPrio(void);
HAL_StatusTypeDef    HAL_SetTickFreq(HAL_TickFreqTypeDef Freq);
HAL_TickFreqTypeDef  HAL_GetTickFreq(void);
void                 HAL_SuspendTick(void);
void                 HAL_ResumeTick(void);
uint32_t             HAL_GetHalVersion(void);
uint32_t             HAL_GetREVID(void);
uint32_t             HAL_GetDEVID(void);
uint32_t             HAL_GetUIDw0(void);
uint32_t             HAL_GetUIDw1(void);
uint32_t             HAL_GetUIDw2(void);

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group3
  * @{
  */

/* DBGMCU Peripheral Control functions  ***************************************/
void                 HAL_DBGMCU_EnableDBGSleepMode(void);
void                 HAL_DBGMCU_DisableDBGSleepMode(void);
void                 HAL_DBGMCU_EnableDBGStopMode(void);
void                 HAL_DBGMCU_DisableDBGStopMode(void);
void                 HAL_DBGMCU_EnableDBGStandbyMode(void);
void                 HAL_DBGMCU_DisableDBGStandbyMode(void);

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group4
  * @{
  */

/* SBS Control functions  *****************************************************/
uint32_t             HAL_SBS_GetBootAddress(void);

void                 HAL_SBS_IncrementHDPLValue(void);
uint32_t             HAL_SBS_GetHDPLValue(void);

void                 HAL_SBS_OpenAccessPort(void);
void                 HAL_SBS_OpenDebug(void);
HAL_StatusTypeDef    HAL_SBS_ConfigDebugLevel(uint32_t Level);
uint32_t             HAL_SBS_GetDebugLevel(void);
void                 HAL_SBS_UnlockDebugConfig(void);
void                 HAL_SBS_LockDebugConfig(void);

void                 HAL_SBS_ConfigRSSCommand(uint32_t Cmd);
uint32_t             HAL_SBS_GetRSSCommand(void);

void                 HAL_SBS_EnableIOAnalogBooster(void);
void                 HAL_SBS_DisableIOAnalogBooster(void);
void                 HAL_SBS_EnableIOAnalogSwitchVdd(void);
void                 HAL_SBS_DisableIOAnalogSwitchVdd(void);
void                 HAL_SBS_ConfigEthernetPHY(uint32_t Config);
void                 HAL_SBS_ConfigAXISRAMWaitState(uint32_t Config);

void                 HAL_SBS_EnableCompensationCell(uint32_t Selection);
void                 HAL_SBS_DisableCompensationCell(uint32_t Selection);
uint32_t             HAL_SBS_GetCompensationCellReadyStatus(uint32_t Selection);
void                 HAL_SBS_ConfigCompensationCell(uint32_t Selection, uint32_t Code, uint32_t NmosValue,
                                                    uint32_t PmosValue);
HAL_StatusTypeDef    HAL_SBS_GetCompensationCell(uint32_t Selection, uint32_t *pCode, uint32_t *pNmosValue,
                                                 uint32_t *pPmosValue);

void                 HAL_SBS_EnableIOSpeedOptimize(uint32_t Selection);
void                 HAL_SBS_DisableIOSpeedOptimize(uint32_t Selection);

void                 HAL_SBS_ConfigTimerBreakInput(uint32_t Input);
uint32_t             HAL_SBS_GetTimerBreakInputConfig(void);

void                 HAL_SBS_EXTIConfig(uint32_t Exti, uint32_t Port);
uint32_t             HAL_SBS_GetEXTIConfig(uint32_t Exti);
/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group5
  * @{
  */

/* VREFBUF Control functions  *************************************************/
void                 HAL_VREFBUF_VoltageScalingConfig(uint32_t VoltageScaling);
void                 HAL_VREFBUF_HighImpedanceConfig(uint32_t Mode);
void                 HAL_VREFBUF_TrimmingConfig(uint32_t TrimmingValue);
HAL_StatusTypeDef    HAL_VREFBUF_Enable(void);
void                 HAL_VREFBUF_Disable(void);


/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group6
  * @{
  */

/* AXIM Configuration functions  *************************************************/
void                 HAL_AXIM_ASIB_EnablePacking(AXIM_ASIB_TypeDef *AsibInstance);
void                 HAL_AXIM_ASIB_DisablePacking(AXIM_ASIB_TypeDef *AsibInstance);
void                 HAL_AXIM_ASIB_IssuingConfig(AXIM_ASIB_TypeDef *AsibInstance, uint32_t ReadIssuing,
                                                 uint32_t WriteIssuing);
void                 HAL_AXIM_ASIB_ReadQoSConfig(AXIM_ASIB_TypeDef *AsibInstance, uint32_t QosPriority);
void                 HAL_AXIM_ASIB_WriteQoSConfig(AXIM_ASIB_TypeDef *AsibInstance, uint32_t QosPriority);


void                 HAL_AXIM_AMIB_EnablePacking(AXIM_AMIB_TypeDef *AmibInstance);
void                 HAL_AXIM_AMIB_DisablePacking(AXIM_AMIB_TypeDef *AmibInstance);
void                 HAL_AXIM_AMIB_IssuingConfig(AXIM_AMIB_TypeDef *AmibInstance, uint32_t ReadIssuing,
                                                 uint32_t WriteIssuing);
void                 HAL_AXIM_AMIB_IssuingConfigBusMatrix(AXIM_AMIB_TypeDef *AmibInstance, uint32_t ReadIssuing,
                                                          uint32_t WriteIssuing);
void                 HAL_AXIM_AMIB_EnableLongBurst(AXIM_AMIB_TypeDef *AmibInstance);
void                 HAL_AXIM_AMIB_DisableLongBurst(AXIM_AMIB_TypeDef *AmibInstance);
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

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7RSxx_HAL_H */
