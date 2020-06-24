/**
  ******************************************************************************
  * @file    stpmic.c
  * @author  MCD Application Team
  * @brief   This sample code provides hardware semaphore using HSEM for 
  *          synchronization and mutual exclusion between heterogeneous processors 
  *          and those not operating under a single, shared operating system.  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

#include <board.h>
#include <stpmic.h>
#include <string.h>
#include "drv_hard_i2c.h"

/* Definition of PMIC <=> stm32mp1 Signals */
#define PMIC_INTn_PIN               GPIO_PIN_0
#define PMIC_INTn_PORT              GPIOA
#define PMIC_INTn_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define PMIC_INTn_CLK_DISABLE()     __HAL_RCC_GPIOA_CLK_DISABLE()

#define BSP_PMIC_PWRCTRL_PIN_Assert()   HAL_GPIO_WritePin(PMIC_PWRCTRL_PORT, PMIC_PWRCTRL_PIN, GPIO_PIN_RESET);
#define BSP_PMIC_PWRCTRL_PIN_Pull()     HAL_GPIO_WritePin(PMIC_PWRCTRL_PORT, PMIC_PWRCTRL_PIN, GPIO_PIN_SET);

/**
  * @}
  */ 
  
 /** @defgroup STM32MP15XX_EVAL_STPMU_Private_Defines Private Defines
  * @{
  */ 
/* Private typedef -----------------------------------------------------------*/
typedef struct {
  PMIC_RegulId_TypeDef id;
  uint16_t *voltage_table;
  uint8_t  voltage_table_size;
  uint8_t  control_reg;
  uint8_t  low_power_reg;
  uint8_t  rank ;
  uint8_t  nvm_info ;
} regul_struct;

/* Private define ------------------------------------------------------------*/
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

/* Those define should reflect NVM_USER section
 * For ES Eval Configuration this is specified as
 * 	0xF7,
 0x92,
 0xC0,
 0x02,
 0xFA,
 0x30,
 0x00,
 0x33,
 * */
#define NVM_SECTOR3_REGISTER_0  0xF7
#define NVM_SECTOR3_REGISTER_1  0x92
#define NVM_SECTOR3_REGISTER_2  0xC0
#define NVM_SECTOR3_REGISTER_3  0x02
#define NVM_SECTOR3_REGISTER_4  0xFA
#define NVM_SECTOR3_REGISTER_5  0x30
#define NVM_SECTOR3_REGISTER_6  0x00
#define NVM_SECTOR3_REGISTER_7  0x33

/* nvm_vinok_hyst: VINOK hysteresis voltage
 00: 200mV
 01: 300mV
 10: 400mV
 11: 500mV
 *
 * nvm_vinok: VINOK threshold voltage
 00:  3.1v
 01:  3.3v
 10:  3.5v
 11:  4.5v
 Otp_ldo4_forced :
 0:  LDO4 ranks following OTP_RANK_LDO4<1:0>
 if VBUS_OTG or SWOUT is turn ON condition
 1:  LDO4 follows normal ranking procedure

 nvm_longkeypress:
 0:  Turn OFF on long key press inactive
 1:  Turn OFF on long key press active

 nvm_autoturnon:
 0:  PMIC doesnt start automatically on VIN rising
 1:  PMIC starts automatically on VIN rising

 nvm_cc_keepoff :
 0:  short circuit does not turn OFF PMIC
 1:  short circuit turn OFF PMIC and keep it OFF till CC_flag is reset

 *
 */
#define OTP_VINOK_HYST  	((NVM_SECTOR3_REGISTER_0 & 0xC0) >> 6) 	// nvm_vinok_hyst
#define OTP_VINOK		  	((NVM_SECTOR3_REGISTER_0 & 0x30) >> 4) 	// nvm_vinok
#define OTP_LDO4_FORCED     ((NVM_SECTOR3_REGISTER_0 & 0x08) >> 3) 	// Otp_ldo4_forced
#define OTP_LONGKEYPRESSED  ((NVM_SECTOR3_REGISTER_0 & 0x04) >> 2)	// nvm_longkeypress
#define OTP_AUTOTURNON  	((NVM_SECTOR3_REGISTER_0 & 0x02) >> 1)	// nvm_autoturnon
#define OTP_CC_KEEPOFF  	((NVM_SECTOR3_REGISTER_0 & 0x01))		// nvm_cc_keepoff

/*
 * nvm_rank_buck4:
 00: rank0
 01: rank1
 10: rank2
 11: rank3
 nvm_rank_buck3:
 00:  rank0
 01:  rank1
 10:  rank2
 11:  rank3
 nvm_rank_buck2:
 00:  rank0
 01:  rank1
 10:  rank2
 11:  rank3
 nvm_rank_buck1:
 00:  rank0
 01:  rank1
 10:  rank2
 11:  rank3
 *
 */
#define OTP_RANK_BUCK4  	((NVM_SECTOR3_REGISTER_1 & 0xC0) >> 6) 	// nvm_rank_buck4
#define OTP_RANK_BUCK3		((NVM_SECTOR3_REGISTER_1 & 0x30) >> 4) 	// nvm_rank_buck3
#define OTP_RANK_BUCK2     	((NVM_SECTOR3_REGISTER_1 & 0x0C) >> 2) 	// nvm_rank_buck2
#define OTP_RANK_BUCK1  	((NVM_SECTOR3_REGISTER_1 & 0x03))		// nvm_rank_buck1


/*
 * nvm_rank_ldo4:
 00: rank0
 01: rank1
 10: rank2
 11: rank3
 nvm_rank_ldo3:
 00:  rank0
 01:  rank1
 10:  rank2
 11:  rank3
 nvm_rank_ldo2:
 00:  rank0
 01:  rank1
 10:  rank2
 11:  rank3
 nvm_rank_ldo1:
 00:  rank0
 01:  rank1
 10:  rank2
 11:  rank3
 *
 */
#define OTP_RANK_LDO4  		((NVM_SECTOR3_REGISTER_2 & 0xC0) >> 6) 	// nvm_rank_ldo4
#define OTP_RANK_LDO3		((NVM_SECTOR3_REGISTER_2 & 0x30) >> 4) 	// nvm_rank_ldo3
#define OTP_RANK_LDO2     	((NVM_SECTOR3_REGISTER_2 & 0x0C) >> 2) 	// nvm_rank_ldo2
#define OTP_RANK_LDO1  		((NVM_SECTOR3_REGISTER_2 & 0x03))		// nvm_rank_ldo1

/*
 * nvm_clamp_output_buck: Clamp output value to 1.3V max
 0: output_buck4<5:0> not clamped
 1: output_buck4<5:0> to b011100(1.3V)

 nvm_bypass_mode_ldo3: LDO3 forced bypass mode
 0: LDO3 not in bypass mode
 1: LDO3 in bypass mode

 nvm_rank_vrefddr:
 00:  rank0
 01:  rank1
 10:  rank2
 11:  rank3

 nvm_rank_ldo6:
 00:  rank0
 01:  rank1
 10:  rank2
 11:  rank3

nvm_rank_ldo5:
 00:  rank0
 01:  rank1
 10:  rank2
 11:  rank3
 *
 */
#define OTP_CLAMP_OUTPUT_BUCK4  ((NVM_SECTOR3_REGISTER_3 & 0x80) >> 7) 	// nvm_clamp_output_buck4
#define OTP_BYPASS_MODE_LDO3  	((NVM_SECTOR3_REGISTER_3 & 0x40) >> 6) 	// nvm_bypass_mode_ldo3
#define OTP_RANK_VREFDDR		((NVM_SECTOR3_REGISTER_3 & 0x30) >> 4) 	// nvm_rank_vrefddr
#define OTP_RANK_LDO6     		((NVM_SECTOR3_REGISTER_3 & 0x0C) >> 2) 	// nvm_rank_ldo6
#define OTP_RANK_LDO5  			((NVM_SECTOR3_REGISTER_3 & 0x03))		// nvm_rank_ldo5

/*
 * nvm_output_buck4: Buck4 default output selection
 00:  1.15V
 01:  1.2V
 10:  1.8V
 11:  3.3V
 nvm_output_buck3: Buck3 default output selection
 00:  1.2V
 01:  1.8V
 10:  3.0V
 11:  3.3V
 nvm_output_buck2: Buck2 default output selection
 00:  1.1V
 01:  1.2V
 10:  1.35V
 11:  1.5V
 nvm_output_buck1: Buck1 default output selection
 00:  1.1V
 01:  1.15V
 10:  1.2V
 11:  1.25V
 *
 */
#define OTP_OUTPUT_BUCK4  		((NVM_SECTOR3_REGISTER_4 & 0xC0) >> 6) 	// nvm_output_buck4
#define OTP_OUTPUT_BUCK3		((NVM_SECTOR3_REGISTER_4 & 0x30) >> 4) 	// nvm_output_buck3
#define OTP_OUTPUT_BUCK2     	((NVM_SECTOR3_REGISTER_4 & 0x0C) >> 2) 	// nvm_output_buck2
#define OTP_OUTPUT_BUCK1  		((NVM_SECTOR3_REGISTER_4 & 0x03))		// nvm_output_buck1

/*
 * [7]	OTP_SWOFF_BY_BOOST_OVP:
 0 -> SWOUT will not turnoff bu boost OVP
 1 -> SWOUT will be turnoff by BOOST OVP

 [6]	reserved

 [5:4]	nvm_output_ldo3: LDO3 default output selection
 00:  1.8V
 01:  2.5V
 10:  3.3V
 11:  output_buck2<4:0>/2 (VTT termination for DDR3 x32, Analog divider implemented in Analog)

 [3:2]	nvm_output_ldo2: LDO2 default output selection
 00: 1.8V
 01: 2.5V
 10: 2.9V
 11: 3.3V

 [1:0]	nvm_output_ldo1: LDO1 default output selection
 00: 1.8V
 01: 2.5V
 10: 2.9V
 11: 3.3V

 *
 */
#define OTP_SWOFF_BY_BOOST_OVP  ((NVM_SECTOR3_REGISTER_5 & 0x80) >> 7) 	// OTP_SWOFF_BY_BOOST_OVP
#define OTP_OUTPUT_LDO3			((NVM_SECTOR3_REGISTER_5 & 0x30) >> 4) 	// nvm_output_ldo3
#define OTP_OUTPUT_LDO2     	((NVM_SECTOR3_REGISTER_5 & 0x0C) >> 2) 	// nvm_output_ldo2
#define OTP_OUTPUT_LDO1  		((NVM_SECTOR3_REGISTER_5 & 0x03))		// nvm_output_ldo1

/*
 * 	[7:4]	reserved
 *
 [3:2]	nvm_output_ldo6: LDO6 default output selection
 00:  1.0V
 01:  1.2V
 10:  1.8V
 11:  3.3V

 [1:0]	nvm_output_ldo5: LDO5 default output selection
 00:  1.8V
 01:  2.5V
 10:  2.9V
 11 :  3.3V
 *
 */

#define OTP_OUTPUT_LDO6     	((NVM_SECTOR3_REGISTER_6 & 0x0C) >> 2) 	// nvm_output_ldo6
#define OTP_OUTPUT_LDO5  		((NVM_SECTOR3_REGISTER_6 & 0x03))		// nvm_output_ldo5

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* I2C handler declaration */
I2C_HandleTypeDef I2cHandle;
extern I2C_HandleTypeDef hI2c4;

uint16_t buck1_voltage_table[] = {
  600,
  625,
  650,
  675,
  700,
  725,
  750,
  775,
  800,
  825,
  850,
  875,
  900,
  925,
  950,
  975,
  1000,
  1025,
  1050,
  1075,
  1100,
  1125,
  1150,
  1175,
  1200,
  1225,
  1250,
  1275,
  1300,
  1325,
  1350,
  1350,// 31  1,35stm32mp15xx_eval_stpmu1.c
};

uint16_t buck2_voltage_table[] = {
  1000, // 1
  1000, //
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1050, // 1,05
  1050, // 1,05
  1100, // 1,1
  1100, // 1,1
  1150, // 1,15
  1150, // 1,15
  1200, // 1,2
  1200, // 1,2
  1250, // 1,25
  1250, // 1,25
  1300, // 1,3
  1300, // 1,3
  1350, // 1,35
  1350, // 1,35
  1400, // 1,4
  1400, // 1,4
  1450, // 1,45
  1450, // 1,45
  1500, // 1,5
};

uint16_t buck3_voltage_table[] = {
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1100, // 1,1
  1100, // 1,1
  1100, // 1,1
  1100, // 1,1
  1200, // 1,2
  1200, // 1,2
  1200, // 1,2
  1200, // 1,2
  1300, // 1,3
  1300, // 1,3
  1300, // 1,3
  1300, // 1,3
  1400, // 1,4
  1400, // 1,4
  1400, // 1,4
  1400, // 1,4
  1500, // 1,5
  1600, // 1,6
  1700, // 1,7
  1800, // 1,8
  1900, // 1,9
  2000, // 2
  2100, // 2,1
  2200, // 2,2
  2300, // 2,3
  2400, // 2,4
  2500, // 2,5
  2600, // 2,6
  2700, // 2,7
  2800, // 2,8
  2900, // 2,9
  3000, // 3
  3100, // 3,1
  3200, // 3,2
  3300, // 3,3
  3400, // 3,4
};

uint16_t buck4_voltage_table[] = {
  600,
  625,
  650,
  675,
  700,
  725,
  750,
  775,
  800,
  825,
  850,
  875,
  900,
  925,
  950,
  975,
  1000,
  1025,
  1050,
  1075,
  1100,
  1125,
  1150,
  1175,
  1200,
  1225,
  1250,
  1275,
  1300,
  1300,
  1350,
  1350,// 31  1,35
  1400,// 32  1,40
  1400,// 33  1,40
  1450,// 34  1,45
  1450,// 35  1,45
  1500,// 36  1,5
  1600,// 37  1,6
  1700,// 38  1,7
  1800,// 39  1,8
  1900,// 40  1,9
  2000,// 41  2,0
  2100,// 42  2,1
  2200,// 43  2,2
  2300,// 44  2,3
  2400,// 45  2,4
  2500,// 46  2,5
  2600,// 47  2,6
  2700,// 48  2,7
  2800,// 49  2,8
  2900,// 50  2,9
  3000,// 51  3,0
  3100,// 52  3,1
  3200,// 53  3,2
  3300,// 54  3,3
  3400,// 55  3,4
  3500,// 56  3,5
  3600,// 57  3,6
  3700,// 58  3,7
  3800,// 59  3,8
  3900,// 60  3,9
};

uint16_t ldo1_voltage_table[] = {
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1800, // 1,8
  1900, // 1,9
  2000, // 2
  2100, // 2,1
  2200, // 2,2
  2300, // 2,3
  2400, // 2,4
  2500, // 2,5
  2600, // 2,6
  2700, // 2,7
  2800, // 2,8
  2900, // 2,9
  3000, // 3
  3100, // 3,1
  3200, // 3,2
  3300, // 3,3
};

uint16_t ldo2_voltage_table[] = {
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1800, // 1,8
  1900, // 1,9
  2000, // 2
  2100, // 2,1
  2200, // 2,2
  2300, // 2,3
  2400, // 2,4
  2500, // 2,5
  2600, // 2,6
  2700, // 2,7
  2800, // 2,8
  2900, // 2,9
  3000, // 3
  3100, // 3,1
  3200, // 3,2
  3300, // 3,3
};

uint16_t ldo3_voltage_table[] = {
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1800, // 1,8
  1900, // 1,9
  2000, // 2
  2100, // 2,1
  2200, // 2,2
  2300, // 2,3
  2400, // 2,4
  2500, // 2,5
  2600, // 2,6
  2700, // 2,7
  2800, // 2,8
  2900, // 2,9
  3000, // 3
  3100, // 3,1
  3200, // 3,2
  3300, // 3,3
  3300, // 3,3
  3300, // 3,3
  3300, // 3,3
  3300, // 3,3
  3300, // 3,3
  3300, // 3,3
  0xFFFF, // VREFDDR
};


uint16_t ldo5_voltage_table[] = {
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1800, // 1,8
  1900, // 1,9
  2000, // 2
  2100, // 2,1
  2200, // 2,2
  2300, // 2,3
  2400, // 2,4
  2500, // 2,5
  2600, // 2,6
  2700, // 2,7
  2800, // 2,8
  2900, // 2,9
  3000, // 3
  3100, // 3,1
  3200, // 3,2
  3300, // 3,3
  3400, // 3,4
  3500, // 3,5
  3600, // 3,6
  3700, // 3,7
  3800, // 3,8
  3900, // 3,9
};

uint16_t ldo6_voltage_table[] = {
  900, // 0,9
  1000, // 1,0
  1100, // 1,1
  1200, // 1,2
  1300, // 1,3
  1400, // 1,4
  1500, // 1,5
  1600, // 1,6
  1700, // 1,7
  1800, // 1,8
  1900, // 1,9
  2000, // 2
  2100, // 2,1
  2200, // 2,2
  2300, // 2,3
  2400, // 2,4
  2500, // 2,5
  2600, // 2,6
  2700, // 2,7
  2800, // 2,8
  2900, // 2,9
  3000, // 3
  3100, // 3,1
  3200, // 3,2
  3300, // 3,3
};


uint16_t ldo4_voltage_table[] = {
  3300, // 3,3
};

uint16_t vref_ddr_voltage_table[] = {
  3300, // 3,3
};

/*
  Table of Regulators in PMIC SoC
*/



regul_struct regulators_table[] = {
    {
      .id                 = STPMU1_BUCK1,
      .voltage_table      = buck1_voltage_table,
      .voltage_table_size = ARRAY_SIZE(buck1_voltage_table),
      .control_reg        = BUCK1_CONTROL_REG,
      .low_power_reg      = BUCK1_PWRCTRL_REG,
      .rank               = OTP_RANK_BUCK1,
    },
    {
      .id                 = STPMU1_BUCK2,
      .voltage_table      = buck2_voltage_table,
      .voltage_table_size = ARRAY_SIZE(buck2_voltage_table),
      .control_reg        = BUCK2_CONTROL_REG,
      .low_power_reg      = BUCK2_PWRCTRL_REG,
      .rank               = OTP_RANK_BUCK2,
    },
    {
      .id                 = STPMU1_BUCK3,
      .voltage_table      = buck3_voltage_table,
      .voltage_table_size = ARRAY_SIZE(buck3_voltage_table),
      .control_reg        = BUCK3_CONTROL_REG,
      .low_power_reg      = BUCK3_PWRCTRL_REG,
      .rank               = OTP_RANK_BUCK3,
    },
    {
      .id                 = STPMU1_BUCK4,
      .voltage_table      = buck4_voltage_table,
      .voltage_table_size = ARRAY_SIZE(buck4_voltage_table),
      .control_reg        = BUCK4_CONTROL_REG,
      .low_power_reg      = BUCK4_PWRCTRL_REG,
      .rank               = OTP_RANK_BUCK4,
    },
    {
      .id                 = STPMU1_LDO1,
      .voltage_table      = ldo1_voltage_table,
      .voltage_table_size = ARRAY_SIZE(ldo1_voltage_table),
      .control_reg        = LDO1_CONTROL_REG,
      .low_power_reg      = LDO1_PWRCTRL_REG,
      .rank               = OTP_RANK_LDO1,
    },
    {
      .id                 = STPMU1_LDO2,
      .voltage_table      = ldo2_voltage_table,
      .voltage_table_size = ARRAY_SIZE(ldo2_voltage_table),
      .control_reg        = LDO2_CONTROL_REG,
      .low_power_reg      = LDO2_PWRCTRL_REG,
      .rank               = OTP_RANK_LDO2,
    },

    {
      .id                 = STPMU1_LDO3,
      .voltage_table      = ldo3_voltage_table,
      .voltage_table_size = ARRAY_SIZE(ldo3_voltage_table),
      .control_reg        = LDO3_CONTROL_REG,
      .low_power_reg      = LDO3_PWRCTRL_REG,
      .rank               = OTP_RANK_LDO3,
    },
    {
      .id                 = STPMU1_LDO4,
      .voltage_table      = ldo4_voltage_table,
      .voltage_table_size = ARRAY_SIZE(ldo4_voltage_table),
      .control_reg        = LDO4_CONTROL_REG,
      .low_power_reg      = LDO4_PWRCTRL_REG,
      .rank               = OTP_RANK_LDO4,
    },
    {
      .id                 = STPMU1_LDO5,
      .voltage_table      = ldo5_voltage_table ,
      .voltage_table_size = ARRAY_SIZE(ldo5_voltage_table),
      .control_reg        = LDO5_CONTROL_REG,
      .low_power_reg      = LDO5_PWRCTRL_REG,
      .rank               = OTP_RANK_LDO5,
    },
    {
      .id                 = STPMU1_LDO6,
      .voltage_table      = ldo6_voltage_table ,
      .voltage_table_size = ARRAY_SIZE(ldo6_voltage_table),
      .control_reg        = LDO6_CONTROL_REG,
      .low_power_reg      = LDO6_PWRCTRL_REG,
      .rank               = OTP_RANK_LDO6,
    },
    {
      .id                 = STPMU1_VREFDDR,
      .voltage_table      = vref_ddr_voltage_table ,
      .voltage_table_size = ARRAY_SIZE(vref_ddr_voltage_table),
      .control_reg        = VREF_DDR_CONTROL_REG,
      .low_power_reg      = VREF_DDR_PWRCTRL_REG,
      .rank               = OTP_RANK_VREFDDR,
    },
};

#define MAX_REGUL  ARRAY_SIZE(regulators_table)

 
/* Private function prototypes -----------------------------------------------*/
void STPMU1_IrqHandler(void);
void STPMU1_INTn_Callback(PMIC_IRQn IRQn);
static void My_Error_Handler(void);
static regul_struct *STPMU1_Get_Regulator_Data(PMIC_RegulId_TypeDef id);
static uint8_t STPMU1_Voltage_Find_Index(PMIC_RegulId_TypeDef id, uint16_t milivolts);

/* Private functions ---------------------------------------------------------*/

static regul_struct *STPMU1_Get_Regulator_Data(PMIC_RegulId_TypeDef id)
{
    uint8_t i ;

    for (i = 0 ; i < MAX_REGUL ; i++ )
    {
        if (id == regulators_table[i].id)
            return &regulators_table[i];
    }
    /* id not found */
    My_Error_Handler();
    return NULL;
}

static uint8_t STPMU1_Voltage_Find_Index(PMIC_RegulId_TypeDef id, uint16_t milivolts)
{
    regul_struct *regul = STPMU1_Get_Regulator_Data(id);
    uint8_t i;
    for ( i = 0 ; i < regul->voltage_table_size ; i++)
    {
        if ( regul->voltage_table[i] == milivolts ) {
          //printf("idx:%d for %dmV\n\r", (int)i, (int)milivolts);
          return i;
        }
    }
    /* voltage not found */
    My_Error_Handler();
    return 0;
}

void STPMU1_Enable_Interrupt(PMIC_IRQn IRQn)
{
    uint8_t irq_reg , irq_reg_value ;

    if (IRQn >= IRQ_NR)
    return ;

    /* IRQ register is IRQ Number divided by 8 */
    irq_reg = IRQn >> 3 ;

    /* value to be set in IRQ register corresponds to BIT(7-N) where N is the Interrupt id modulo 8 */
    irq_reg_value = 1 << ( 7 - ( IRQn%8 ) );

    /* Clear previous event stored in latch */
    STPMU1_Register_Write(ITCLEARLATCH1_REG+irq_reg, irq_reg_value );

    /* Clear relevant mask to enable interrupt */
    STPMU1_Register_Write(ITCLEARMASK1_REG+irq_reg, irq_reg_value );

}

extern void STPMU1_Disable_Interrupt(PMIC_IRQn IRQn)
{
    uint8_t irq_reg , irq_reg_value ;

    if (IRQn >= IRQ_NR)
        return ;

    /* IRQ register is IRQ Number divided by 8 */
    irq_reg = IRQn >> 3 ;

    /* value to be set in IRQ register corresponds to BIT(7-N) where N is the Interrupt id modulo 8 */
    irq_reg_value = 1 << ( 7 - ( IRQn%8 ) );

    /* Clear previous event stored in latch */
    STPMU1_Register_Write(ITCLEARLATCH1_REG+irq_reg, irq_reg_value );

    /* Set relevant mask to disable interrupt */
    STPMU1_Register_Write(ITSETMASK1_REG+irq_reg, irq_reg_value );
}


void STPMU1_IrqHandler(void)
{
    uint8_t irq_reg,mask,latch_events,i;

    for (irq_reg = 0 ; irq_reg < STM32_PMIC_NUM_IRQ_REGS ; irq_reg++)
    {
        /* Get latch events & active mask from register */
        mask = STPMU1_Register_Read(ITMASK1_REG+irq_reg);
        latch_events = STPMU1_Register_Read(ITLATCH1_REG+irq_reg) & ~mask ;

        /* Go through all bits for each register */
        for (i = 0 ; i < 8 ; i++ )
        {
            if ( latch_events & ( 1 << i ) )
            {
                /* Callback with parameter computes as "PMIC Interrupt" enum */
                STPMU1_INTn_Callback( (PMIC_IRQn )(irq_reg*8 + (7-i)));
            }
        }
        /* Clear events in appropriate register for the event with mask set */
        STPMU1_Register_Write(ITCLEARLATCH1_REG+irq_reg, latch_events );
    }
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
static void My_Error_Handler(void)
{
    while(1)
    {    
        HAL_Delay(500);
    } 
}


void STPMU1_Sw_Reset(void)
{
    /* Write 1 in bit 0 of MAIN_CONTROL Register */
    STPMU1_Register_Update(MAIN_CONTROL_REG, SET , SOFTWARE_SWITCH_OFF_ENABLED );
}

void STPMU1_Regulator_Enable(PMIC_RegulId_TypeDef id)
{
    regul_struct *regul = STPMU1_Get_Regulator_Data(id);

    STPMU1_Register_Update(regul->control_reg,BIT(0),BIT(0));
}

void STPMU1_Regulator_Disable(PMIC_RegulId_TypeDef id)
{
    regul_struct *regul = STPMU1_Get_Regulator_Data(id);

    STPMU1_Register_Update(regul->control_reg,0,BIT(0));
}

uint8_t STPMU1_Is_Regulator_Enabled(PMIC_RegulId_TypeDef id)
{
    uint8_t val ;

    regul_struct *regul = STPMU1_Get_Regulator_Data(id);

    val = STPMU1_Register_Read(regul->control_reg);

    return (val&0x1);
}

void STPMU1_Regulator_Voltage_Set(PMIC_RegulId_TypeDef id,uint16_t milivolts)
{
    uint8_t voltage_index = STPMU1_Voltage_Find_Index(id,milivolts);
    regul_struct *regul = STPMU1_Get_Regulator_Data(id);
    STPMU1_Register_Update(regul->control_reg, voltage_index<<2 , 0xFC );
}

/* register direct access */
uint8_t STPMU1_Register_Read(uint8_t register_id)
{
    uint32_t status = RT_EOK;
    uint8_t Value = 0;

    status = BSP_I2C4_ReadReg(STPMU1_I2C_ADDRESS, (uint16_t)register_id, &Value, 1);

    /* Check the communication status */
    if(status != RT_EOK)
    {
        My_Error_Handler();
    }
    return Value;
}

void STPMU1_Register_Write(uint8_t register_id, uint8_t value)
{
    uint32_t status = RT_EOK;

    status = BSP_I2C4_WriteReg(STPMU1_I2C_ADDRESS, (uint16_t)register_id, &value, 1);

    /* Check the communication status */
    if(status != RT_EOK)
    {
        My_Error_Handler();
    }

    /* verify register content */
    if ((register_id!=WATCHDOG_CONTROL_REG) && (register_id<=0x40))
    {
        uint8_t readval = STPMU1_Register_Read(register_id);
        if (readval != value)
        {
            My_Error_Handler();
        }
    }
}

void STPMU1_Register_Update(uint8_t register_id, uint8_t value, uint8_t mask)
{
    uint8_t initial_value ;

    initial_value = STPMU1_Register_Read(register_id);

    /* Clear bits to update */
    initial_value &= ~mask;

    /* Update appropriate bits*/
    initial_value |= ( value & mask );

    /* Send new value on I2C Bus */
    STPMU1_Register_Write(register_id, initial_value);

    return ;
}

/*
 *
 * PMIC init
 *    pmic provides power supply on this board
 *    it is configured to turn off some power supply in standby mode
 *
 */
static uint32_t BSP_PMIC_MspInit(I2C_HandleTypeDef *hi2c)
{
    uint32_t  status = RT_EOK;
    GPIO_InitTypeDef  GPIO_InitStruct;

    /*##-1- Configure the I2C clock source, GPIO and Interrupt #*/
    BSP_I2C4_Init();

    /*##-2- Configure PMIC GPIOs Interface ########################################*/

    /* INTn - Interrupt Line - Active Low (Falling Edge) */
    PMIC_INTn_CLK_ENABLE();
    GPIO_InitStruct.Pin       = PMIC_INTn_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull      = GPIO_PULLUP; 
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = 0 ;
    HAL_GPIO_Init(PMIC_INTn_PORT, &GPIO_InitStruct);

    /* Enable and set INTn EXTI Interrupt  */
#if defined(CORE_CA7)
    IRQ_SetPriority(EXTI0_IRQn, 0);
    IRQ_Enable(EXTI0_IRQn);
#elif defined(CORE_CM4)
    HAL_NVIC_SetPriority(EXTI0_IRQn, 0x03, 0x00);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
#endif

    return status;
}

static uint32_t BSP_PMIC_MspDeInit(I2C_HandleTypeDef *hi2c)
{
    uint32_t  status = RT_EOK;
    /*##-1- Reset I2C Clock / Disable peripherals and GPIO Clocks###############*/
    status = BSP_I2C4_DeInit();

    /*##-2- Disable PMIC clk ###########################################*/
    PMIC_INTn_CLK_DISABLE();

    /*##-3- Disable the NVIC for PMIC ##########################################*/
#if defined(CORE_CA7)
    IRQ_Disable(EXTI0_IRQn);
#elif defined(CORE_CM4)
    HAL_NVIC_DisableIRQ(EXTI0_IRQn);
#endif
    HAL_GPIO_DeInit(PMIC_INTn_PORT,PMIC_INTn_PIN);

    return status;
}

uint32_t BSP_PMIC_Is_Device_Ready(void)
{
    int32_t  status = RT_EOK;

    /* Write the TxBuffer1 at @0, then read @0 when device ready */
    if (BSP_I2C4_IsReady(STPMU1_I2C_ADDRESS, 1) != RT_EOK)
    {
        status = -RT_EBUSY;
    }
    return status ;
}

/* Use Xls I2C COnfiguration Tools with I2C Clock config + output clocks requirement */
#define I2C_TIMING     0x10805E89

uint32_t BSP_PMIC_Init(void)
{
    int32_t status = RT_EOK;
    PMIC_IRQn irq;

    /*##-1- Configure the I2C peripheral ######################################*/
    BSP_PMIC_MspInit(&hI2c4);

    status = BSP_PMIC_Is_Device_Ready();
    if (status != RT_EOK )
    {
        return status;
    }

    if (STPMU1_Register_Read(VERSION_STATUS_REG) != 0x00)
    {
        status = -RT_EIO;
        return status;
    }

    STPMU1_Enable_Interrupt(IT_PONKEY_R);
    STPMU1_Enable_Interrupt(IT_PONKEY_F);
    /* enable all irqs  */
    for (irq = IT_SWOUT_R; irq < IRQ_NR; irq++) 
    {
        STPMU1_Enable_Interrupt(irq);
    }

    return RT_EOK;
}

uint32_t BSP_PMIC_DeInit(void)
{
    uint32_t  status = RT_EOK;
    if(HAL_I2C_GetState(&hI2c4) != HAL_I2C_STATE_RESET)
    {
        /* Deinit the I2C */
        BSP_PMIC_MspDeInit(&hI2c4);
    }
    return status;
}

/*
 *
 * following are configurations for this board
 * same configuration than linux
 *
 *  BSP_PMIC_InitRegulators set the regulators for boot
 *  BSP_PMIC_PrepareLpStop set the low power registers for LPSTOP mode
 *    should be called by user before entering is CSTOP
 *  BSP_PMIC_PrepareLpStop set the low power registers for STANDBY mode
 *    should be called by user before entering is STANDBY
 *
 *
 */
/* following are configurations */
uint32_t BSP_PMIC_InitRegulators(void)
{
    uint32_t  status = RT_EOK;

    STPMU1_Register_Write(MAIN_CONTROL_REG, 0x04);
    STPMU1_Register_Write(VIN_CONTROL_REG, 0xc0);
    STPMU1_Register_Write(USB_CONTROL_REG, 0x30);

    STPMU1_Register_Write(MASK_RESET_BUCK_REG, 0x04);
    STPMU1_Register_Write(MASK_RESET_LDO_REG, 0x00);
    STPMU1_Register_Write(MASK_RANK_BUCK_REG, 0x00);
    STPMU1_Register_Write(MASK_RANK_LDO_REG, 0x00);
    STPMU1_Register_Write(BUCK_PULL_DOWN_REG, 0x00);
    STPMU1_Register_Write(LDO14_PULL_DOWN_REG, 0x00);
    STPMU1_Register_Write(LDO56_PULL_DOWN_REG, 0x00);
    STPMU1_Register_Write(BUCK_ICC_TURNOFF_REG, 0x30);
    STPMU1_Register_Write(LDO_ICC_TURNOFF_REG, 0x3b);

    /* vddcore */
    STPMU1_Regulator_Voltage_Set(STPMU1_BUCK1, 1200);
    STPMU1_Regulator_Enable(STPMU1_BUCK1);

    /* vddddr */
    STPMU1_Regulator_Voltage_Set(STPMU1_BUCK2, 1350);
    STPMU1_Regulator_Enable(STPMU1_BUCK2);

    /* vdd */
    STPMU1_Regulator_Voltage_Set(STPMU1_BUCK3, 3300);
    STPMU1_Regulator_Enable(STPMU1_BUCK3);

    /* 3v3 */
    STPMU1_Regulator_Voltage_Set(STPMU1_BUCK4, 3300);
    STPMU1_Regulator_Enable(STPMU1_BUCK4);

    /* vdda */
    STPMU1_Regulator_Voltage_Set(STPMU1_LDO1, 2900);
    STPMU1_Regulator_Enable(STPMU1_LDO1);

    /* 2v8 */
    STPMU1_Regulator_Voltage_Set(STPMU1_LDO2, 2800);
    STPMU1_Regulator_Enable(STPMU1_LDO2);

    /* vtt_ddr  lod3 mode buck2/2 */
    STPMU1_Regulator_Voltage_Set(STPMU1_LDO3, 0xFFFF);
    STPMU1_Regulator_Enable(STPMU1_LDO3);

    /* vdd_usb */
    STPMU1_Regulator_Voltage_Set(STPMU1_LDO4, 3300);
    STPMU1_Regulator_Enable(STPMU1_LDO4);

    /* vdd_sd */
    STPMU1_Regulator_Voltage_Set(STPMU1_LDO5, 2900);
    STPMU1_Regulator_Enable(STPMU1_LDO5);

    /* 1v8 */
    STPMU1_Regulator_Voltage_Set(STPMU1_LDO6, 1800);
    STPMU1_Regulator_Enable(STPMU1_LDO6);

    STPMU1_Regulator_Enable(STPMU1_VREFDDR);

    return status;
}

uint32_t BSP_PMIC_SwitchOff(void)
{
    uint32_t  status = RT_EOK;

    STPMU1_Register_Write(MAIN_CONTROL_REG, 0x01);
    return status;
}

__weak void BSP_PMIC_INTn_Callback(PMIC_IRQn IRQn)
{
    switch (IRQn)
    {
    case IT_PONKEY_F:
        rt_kprintf("IT_PONKEY_F");
        break;

    case IT_PONKEY_R:
        rt_kprintf("IT_PONKEY_R");
        break;

    case IT_WAKEUP_F:
        rt_kprintf("IT_WAKEUP_F");
        break;

    case IT_WAKEUP_R:
        rt_kprintf("IT_WAKEUP_R");
        break;

    case IT_VBUS_OTG_F:
        rt_kprintf("IT_VBUS_OTG_F");
        break;

    case IT_SWOUT_F:
        rt_kprintf("IT_SWOUT_F");
        break;

    case IT_TWARN_R:
        rt_kprintf("IT_TWARN_R");
        break;

    case IT_TWARN_F:
        rt_kprintf("IT_TWARN_F");
        break;

    default:
        rt_kprintf("%d",IRQn);
        break;
    }
    rt_kprintf(" Interrupt received\n\r");
}

void STPMU1_INTn_Callback(PMIC_IRQn IRQn) 
{
    BSP_PMIC_INTn_Callback(IRQn);
}

void BSP_PMIC_INTn_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(PMIC_INTn_PIN);

    STPMU1_IrqHandler();
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hI2c4)
{
    while(1);
}
