/**
  ******************************************************************************
  * @file    stm32mp15xx__stpmic1.h
  * @author  MCD Application Team
  * @brief   stpmu driver functions used for ST internal validation
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics. 
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the 
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  *
  ******************************************************************************
  */

#ifndef __STPMIC_H__
#define __STPMIC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp1xx_hal.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  STPMU1_BUCK1=1,
  STPMU1_BUCK2,
  STPMU1_BUCK3,
  STPMU1_BUCK4,
  STPMU1_LDO1,
  STPMU1_LDO2,
  STPMU1_LDO3,
  STPMU1_LDO4,
  STPMU1_LDO5,
  STPMU1_LDO6,
  STPMU1_VREFDDR,
}PMIC_RegulId_TypeDef;

/* IRQ definitions */
typedef enum {

/* Interrupt Register 1 (0x50 for latch) */
IT_SWOUT_R,
IT_SWOUT_F,
IT_VBUS_OTG_R,
IT_VBUS_OTG_F,
IT_WAKEUP_R,
IT_WAKEUP_F,
IT_PONKEY_R,
IT_PONKEY_F,

/* Interrupt Register 2 (0x51 for latch) */
IT_OVP_BOOST,
IT_OCP_BOOST,
IT_OCP_SWOUT,
IT_OCP_OTG,
IT_CURLIM_BUCK4,
IT_CURLIM_BUCK3,
IT_CURLIM_BUCK2,
IT_CURLIM_BUCK1,

/* Interrupt Register 3 (0x52 for latch) */
IT_SHORT_SWOUT,
IT_SHORT_SWOTG,
IT_CURLIM_LDO6,
IT_CURLIM_LDO5,
IT_CURLIM_LDO4,
IT_CURLIM_LDO3,
IT_CURLIM_LDO2,
IT_CURLIM_LDO1,

/* Interrupt Register 3 (0x52 for latch) */
IT_SWIN_R,
IT_SWIN_F,
IT_RESERVED_1,
IT_RESERVED_2,
IT_VINLOW_R,
IT_VINLOW_F,
IT_TWARN_R,
IT_TWARN_F,

IRQ_NR,
} PMIC_IRQn;

/**
  * @}
  */ 

/** @defgroup STM32MP15XX_EVAL_STPMU_Exported_Constants Exported Constants
  * @{
  */ 

/* Exported constants --------------------------------------------------------*/
#define BIT(_x)  (1<<(_x))
#define STM32_PMIC_NUM_IRQ_REGS       4

#define TURN_ON_REG                 0x1
#define TURN_OFF_REG                0x2
#define ICC_LDO_TURN_OFF_REG        0x3
#define ICC_BUCK_TURN_OFF_REG       0x4
#define RESET_STATUS_REG            0x5
#define VERSION_STATUS_REG          0x6
#define MAIN_CONTROL_REG            0x10
#define PADS_PULL_REG               0x11
#define BUCK_PULL_DOWN_REG          0x12
#define LDO14_PULL_DOWN_REG         0x13
#define LDO56_PULL_DOWN_REG         0x14
#define VIN_CONTROL_REG             0x15
#define PONKEY_TIMER_REG            0x16
#define MASK_RANK_BUCK_REG          0x17
#define MASK_RESET_BUCK_REG         0x18
#define MASK_RANK_LDO_REG           0x19
#define MASK_RESET_LDO_REG          0x1A
#define WATCHDOG_CONTROL_REG        0x1B
#define WATCHDOG_TIMER_REG          0x1C
#define BUCK_ICC_TURNOFF_REG        0x1D
#define LDO_ICC_TURNOFF_REG         0x1E
#define BUCK_APM_CONTROL_REG        0x1F
#define BUCK1_CONTROL_REG           0x20
#define BUCK2_CONTROL_REG           0x21
#define BUCK3_CONTROL_REG           0x22
#define BUCK4_CONTROL_REG           0x23
#define VREF_DDR_CONTROL_REG        0x24
#define LDO1_CONTROL_REG            0x25
#define LDO2_CONTROL_REG            0x26
#define LDO3_CONTROL_REG            0x27
#define LDO4_CONTROL_REG            0x28
#define LDO5_CONTROL_REG            0x29
#define LDO6_CONTROL_REG            0x2A
#define BUCK1_PWRCTRL_REG           0x30
#define BUCK2_PWRCTRL_REG           0x31
#define BUCK3_PWRCTRL_REG           0x32
#define BUCK4_PWRCTRL_REG           0x33
#define VREF_DDR_PWRCTRL_REG        0x34
#define LDO1_PWRCTRL_REG            0x35
#define LDO2_PWRCTRL_REG            0x36
#define LDO3_PWRCTRL_REG            0x37
#define LDO4_PWRCTRL_REG            0x38
#define LDO5_PWRCTRL_REG            0x39
#define LDO6_PWRCTRL_REG            0x3A
#define FREQUENCY_SPREADING_REG     0x3B
#define USB_CONTROL_REG             0x40
#define ITLATCH1_REG                0x50
#define ITLATCH2_REG                0x51
#define ITLATCH3_REG                0x52
#define ITLATCH4_REG                0x53
#define ITSETLATCH1_REG             0x60
#define ITSETLATCH2_REG             0x61
#define ITSETLATCH3_REG             0x62
#define ITSETLATCH4_REG             0x63
#define ITCLEARLATCH1_REG           0x70
#define ITCLEARLATCH2_REG           0x71
#define ITCLEARLATCH3_REG           0x72
#define ITCLEARLATCH4_REG           0x73
#define ITMASK1_REG                 0x80
#define ITMASK2_REG                 0x81
#define ITMASK3_REG                 0x82
#define ITMASK4_REG                 0x83
#define ITSETMASK1_REG              0x90
#define ITSETMASK2_REG              0x91
#define ITSETMASK3_REG              0x92
#define ITSETMASK4_REG              0x93
#define ITCLEARMASK1_REG            0xA0
#define ITCLEARMASK2_REG            0xA1
#define ITCLEARMASK3_REG            0xA2
#define ITCLEARMASK4_REG            0xA3
#define ITSOURCE1_REG               0xB0
#define ITSOURCE2_REG               0xB1
#define ITSOURCE3_REG               0xB2
#define ITSOURCE4_REG               0xB3
#define LDO_VOLTAGE_MASK            0x7C
#define BUCK_VOLTAGE_MASK           0xFC
#define LDO_BUCK_VOLTAGE_SHIFT      2

#define LDO_ENABLE_MASK             0x01
#define BUCK_ENABLE_MASK            0x01
#define BUCK_HPLP_ENABLE_MASK       0x02
#define LDO_HPLP_ENABLE_MASK        0x02
#define LDO_BUCK_HPLP_SHIFT         1

#define LDO_BUCK_RANK_MASK          0x01
#define LDO_BUCK_RESET_MASK         0x01
#define LDO_BUCK_PULL_DOWN_MASK     0x03


/* Main PMIC Control Register 
 * MAIN_CONTROL_REG
 * Address : 0x10
 * */
#define ICC_EVENT_ENABLED           BIT(4)
#define PWRCTRL_POLARITY_HIGH       BIT(3)
#define PWRCTRL_PIN_VALID           BIT(2)
#define RESTART_REQUEST_ENABLED     BIT(1)
#define SOFTWARE_SWITCH_OFF_ENABLED BIT(0)

/* Main PMIC PADS Control Register 
 * PADS_PULL_REG
 * Address : 0x11
 * */
#define WAKEUP_DETECTOR_DISABLED    BIT(4)
#define PWRCTRL_PD_ACTIVE           BIT(3)
#define PWRCTRL_PU_ACTIVE           BIT(2)
#define WAKEUP_PD_ACTIVE            BIT(1)
#define PONKEY_PU_ACTIVE            BIT(0)


/* Main PMIC VINLOW Control Register 
 * VIN_CONTROL_REGC DMSC
 * Address : 0x15
 * */
#define SWIN_DETECTOR_ENABLED       BIT(7)
#define SWOUT_DETECTOR_ENABLED      BIT(6)
#define VINLOW_HYST_MASK            0x3
#define VINLOW_HYST_SHIFT           4
#define VINLOW_THRESHOLD_MASK       0x7
#define VINLOW_THRESHOLD_SHIFT      1
#define VINLOW_ENABLED              0x01
#define VINLOW_CTRL_REG_MASK        0xFF


/* USB Control Register 
 * Address : 0x40
 * */
#define BOOST_OVP_DISABLED          BIT(7)
#define VBUS_OTG_DETECTION_DISABLED BIT(6)
// Discharge not implemented
#define OCP_LIMIT_HIGH              BIT(3)
#define SWIN_SWOUT_ENABLED          BIT(2)
#define USBSW_OTG_SWITCH_ENABLED    BIT(1)


/* IRQ masks */
/* Interrupt Mask for Register 1 (0x50 for latch) */
#define IT_SWOUT_R_MASK             BIT(7)
#define IT_SWOUT_F_MASK             BIT(6)
#define IT_VBUS_OTG_R_MASK          BIT(5)
#define IT_VBUS_OTG_F_MASK          BIT(4)
#define IT_WAKEUP_R_MASK            BIT(3)
#define IT_WAKEUP_F_MASK            BIT(2)
#define IT_PONKEY_R_MASK            BIT(1)
#define IT_PONKEY_F_MASK            BIT(0)

/* Interrupt Mask for Register 2 (0x51 for latch) */
#define IT_OVP_BOOST_MASK           BIT(7)
#define IT_OCP_BOOST_MASK           BIT(6)
#define IT_OCP_SWOUT_MASK           BIT(5)
#define IT_OCP_OTG_MASK             BIT(4)
#define IT_CURLIM_BUCK4_MASK        BIT(3)
#define IT_CURLIM_BUCK3_MASK        BIT(2)
#define IT_CURLIM_BUCK2_MASK        BIT(1)
#define IT_CURLIM_BUCK1_MASK        BIT(0)

/* Interrupt Mask for Register 3 (0x52 for latch) */
#define IT_SHORT_SWOUT_MASK         BIT(7)
#define IT_SHORT_SWOTG_MASK         BIT(6)
#define IT_CURLIM_LDO6_MASK         BIT(5)
#define IT_CURLIM_LDO5_MASK         BIT(4)
#define IT_CURLIM_LDO4_MASK         BIT(3)
#define IT_CURLIM_LDO3_MASK         BIT(2)
#define IT_CURLIM_LDO2_MASK         BIT(1)
#define IT_CURLIM_LDO1_MASK         BIT(0)

/* Interrupt Mask for Register 4 (0x53 for latch) */
#define IT_SWIN_R_MASK              BIT(7)
#define IT_SWIN_F_MASK              BIT(6)
/*  Reserved 1 */
/*  Reserved 2 */
#define IT_VINLOW_R_MASK            BIT(3)
#define IT_VINLOW_F_MASK            BIT(2)
#define IT_TWARN_R_MASK             BIT(1)
#define IT_TWARN_F_MASK             BIT(0)

#define PMIC_VERSION_ID             0x10

#define NVM_SECTOR3_REGISTER_7      0x33
//#define STPMU1_I2C_ADDRESS          ((NVM_SECTOR3_REGISTER_7 & 0x7F) << 1 )

/**
  * @}
  */ 
  
/** @defgroup STM32MP15XX_EVAL_STPMU_Exported_Functions Exported Functions
  * @{
  */

/* Exported functions --------------------------------------------------------*/
uint8_t STPMU1_Register_Read(uint8_t register_id);
void STPMU1_Register_Write(uint8_t register_id, uint8_t value);
void STPMU1_Register_Update(uint8_t register_id, uint8_t value, uint8_t mask);
void STPMU1_Enable_Interrupt(PMIC_IRQn IRQn);
void STPMU1_Disable_Interrupt(PMIC_IRQn IRQn);
void STPMU1_Regulator_Enable(PMIC_RegulId_TypeDef id);
void STPMU1_Regulator_Disable(PMIC_RegulId_TypeDef id);
uint8_t STPMU1_Is_Regulator_Enabled(PMIC_RegulId_TypeDef id);
void STPMU1_Regulator_Voltage_Set(PMIC_RegulId_TypeDef id,uint16_t milivolts);
uint32_t BSP_PMIC_Init(void);
uint32_t BSP_PMIC_DeInit(void);
uint32_t BSP_PMIC_Is_Device_Ready(void);
uint32_t BSP_PMIC_InitRegulators (void);
__weak void BSP_PMIC_INTn_Callback(PMIC_IRQn IRQn);


#ifdef __cplusplus
}
#endif

#endif
