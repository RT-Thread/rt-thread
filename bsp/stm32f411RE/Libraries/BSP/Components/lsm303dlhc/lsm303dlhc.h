/**
  ******************************************************************************
  * @file    lsm303dlhc.h
  * @author  MCD Application Team
  * @version V2.0.0
  * @date    24-June-2015
  * @brief   This file contains all the functions prototypes for the lsm303dlhc.c driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LSM303DLHC_H
#define __LSM303DLHC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "../Common/accelero.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */ 
   
/** @addtogroup LSM303DLHC
  * @{
  */
  
/** @defgroup LSM303DLHC_Exported_Types
  * @{
  */

/**
  * @}
  */
 
/******************************************************************************/
/*************************** START REGISTER MAPPING  **************************/
/******************************************************************************/
/* Exported constant IO ------------------------------------------------------*/
#define ACC_I2C_ADDRESS                      0x32
#define MAG_I2C_ADDRESS                      0x3C

/* Acceleration Registers */
#define LSM303DLHC_WHO_AM_I_ADDR             0x0F  /* device identification register */
#define LSM303DLHC_CTRL_REG1_A               0x20  /* Control register 1 acceleration */
#define LSM303DLHC_CTRL_REG2_A               0x21  /* Control register 2 acceleration */
#define LSM303DLHC_CTRL_REG3_A               0x22  /* Control register 3 acceleration */
#define LSM303DLHC_CTRL_REG4_A               0x23  /* Control register 4 acceleration */
#define LSM303DLHC_CTRL_REG5_A               0x24  /* Control register 5 acceleration */
#define LSM303DLHC_CTRL_REG6_A               0x25  /* Control register 6 acceleration */
#define LSM303DLHC_REFERENCE_A               0x26  /* Reference register acceleration */
#define LSM303DLHC_STATUS_REG_A              0x27  /* Status register acceleration */
#define LSM303DLHC_OUT_X_L_A                 0x28  /* Output Register X acceleration */
#define LSM303DLHC_OUT_X_H_A                 0x29  /* Output Register X acceleration */
#define LSM303DLHC_OUT_Y_L_A                 0x2A  /* Output Register Y acceleration */
#define LSM303DLHC_OUT_Y_H_A                 0x2B  /* Output Register Y acceleration */
#define LSM303DLHC_OUT_Z_L_A                 0x2C  /* Output Register Z acceleration */
#define LSM303DLHC_OUT_Z_H_A                 0x2D  /* Output Register Z acceleration */ 
#define LSM303DLHC_FIFO_CTRL_REG_A           0x2E  /* Fifo control Register acceleration */
#define LSM303DLHC_FIFO_SRC_REG_A            0x2F  /* Fifo src Register acceleration */

#define LSM303DLHC_INT1_CFG_A                0x30  /* Interrupt 1 configuration Register acceleration */
#define LSM303DLHC_INT1_SOURCE_A             0x31  /* Interrupt 1 source Register acceleration */
#define LSM303DLHC_INT1_THS_A                0x32  /* Interrupt 1 Threshold register acceleration */
#define LSM303DLHC_INT1_DURATION_A           0x33  /* Interrupt 1 DURATION register acceleration */

#define LSM303DLHC_INT2_CFG_A                0x34  /* Interrupt 2 configuration Register acceleration */
#define LSM303DLHC_INT2_SOURCE_A             0x35  /* Interrupt 2 source Register acceleration */
#define LSM303DLHC_INT2_THS_A                0x36  /* Interrupt 2 Threshold register acceleration */
#define LSM303DLHC_INT2_DURATION_A           0x37  /* Interrupt 2 DURATION register acceleration */

#define LSM303DLHC_CLICK_CFG_A               0x38  /* Click configuration Register acceleration */
#define LSM303DLHC_CLICK_SOURCE_A            0x39  /* Click 2 source Register acceleration */
#define LSM303DLHC_CLICK_THS_A               0x3A  /* Click 2 Threshold register acceleration */

#define LSM303DLHC_TIME_LIMIT_A              0x3B  /* Time Limit Register acceleration */
#define LSM303DLHC_TIME_LATENCY_A            0x3C  /* Time Latency Register acceleration */
#define LSM303DLHC_TIME_WINDOW_A             0x3D  /* Time window register acceleration */

/* Magnetic field Registers */
#define LSM303DLHC_CRA_REG_M                 0x00  /* Control register A magnetic field */
#define LSM303DLHC_CRB_REG_M                 0x01  /* Control register B magnetic field */
#define LSM303DLHC_MR_REG_M                  0x02  /* Control register MR magnetic field */
#define LSM303DLHC_OUT_X_H_M                 0x03  /* Output Register X magnetic field */
#define LSM303DLHC_OUT_X_L_M                 0x04  /* Output Register X magnetic field */
#define LSM303DLHC_OUT_Z_H_M                 0x05  /* Output Register Z magnetic field */
#define LSM303DLHC_OUT_Z_L_M                 0x06  /* Output Register Z magnetic field */ 
#define LSM303DLHC_OUT_Y_H_M                 0x07  /* Output Register Y magnetic field */
#define LSM303DLHC_OUT_Y_L_M                 0x08  /* Output Register Y magnetic field */

#define LSM303DLHC_SR_REG_M                  0x09  /* Status Register magnetic field */
#define LSM303DLHC_IRA_REG_M                 0x0A  /* IRA Register magnetic field */
#define LSM303DLHC_IRB_REG_M                 0x0B  /* IRB Register magnetic field */
#define LSM303DLHC_IRC_REG_M                 0x0C  /* IRC Register magnetic field */

#define LSM303DLHC_TEMP_OUT_H_M              0x31  /* Temperature Register magnetic field */
#define LSM303DLHC_TEMP_OUT_L_M              0x32  /* Temperature Register magnetic field */

/******************************************************************************/
/**************************** END REGISTER MAPPING  ***************************/
/******************************************************************************/

#define I_AM_LMS303DLHC                   ((uint8_t)0x33)

/** @defgroup Acc_Power_Mode_selection
  * @{
  */
#define LSM303DLHC_NORMAL_MODE            ((uint8_t)0x00)
#define LSM303DLHC_LOWPOWER_MODE          ((uint8_t)0x08)
/**
  * @}
  */

/** @defgroup Acc_OutPut_DataRate_Selection
  * @{
  */
#define LSM303DLHC_ODR_1_HZ                ((uint8_t)0x10)  /*!< Output Data Rate = 1 Hz */
#define LSM303DLHC_ODR_10_HZ               ((uint8_t)0x20)  /*!< Output Data Rate = 10 Hz */
#define LSM303DLHC_ODR_25_HZ               ((uint8_t)0x30)  /*!< Output Data Rate = 25 Hz */
#define LSM303DLHC_ODR_50_HZ               ((uint8_t)0x40)  /*!< Output Data Rate = 50 Hz */
#define LSM303DLHC_ODR_100_HZ              ((uint8_t)0x50)  /*!< Output Data Rate = 100 Hz */
#define LSM303DLHC_ODR_200_HZ              ((uint8_t)0x60)  /*!< Output Data Rate = 200 Hz */
#define LSM303DLHC_ODR_400_HZ              ((uint8_t)0x70)  /*!< Output Data Rate = 400 Hz */
#define LSM303DLHC_ODR_1620_HZ_LP          ((uint8_t)0x80)  /*!< Output Data Rate = 1620 Hz only in Low Power Mode */
#define LSM303DLHC_ODR_1344_HZ             ((uint8_t)0x90)  /*!< Output Data Rate = 1344 Hz in Normal mode and 5376 Hz in Low Power Mode */
/**
  * @}
  */

/** @defgroup Acc_Axes_Selection
  * @{
  */
#define LSM303DLHC_X_ENABLE                ((uint8_t)0x01)
#define LSM303DLHC_Y_ENABLE                ((uint8_t)0x02)
#define LSM303DLHC_Z_ENABLE                ((uint8_t)0x04)
#define LSM303DLHC_AXES_ENABLE             ((uint8_t)0x07)
#define LSM303DLHC_AXES_DISABLE            ((uint8_t)0x00)
/**
  * @}
  */

/** @defgroup Acc_High_Resolution
  * @{
  */
#define LSM303DLHC_HR_ENABLE               ((uint8_t)0x08)
#define LSM303DLHC_HR_DISABLE              ((uint8_t)0x00)
/**
  * @}
  */

/** @defgroup Acc_Full_Scale_Selection
  * @{
  */
#define LSM303DLHC_FULLSCALE_2G            ((uint8_t)0x00)  /*!< ±2 g */
#define LSM303DLHC_FULLSCALE_4G            ((uint8_t)0x10)  /*!< ±4 g */
#define LSM303DLHC_FULLSCALE_8G            ((uint8_t)0x20)  /*!< ±8 g */
#define LSM303DLHC_FULLSCALE_16G           ((uint8_t)0x30)  /*!< ±16 g */
/**
  * @}
  */

/** @defgroup Acc_Full_Scale_Selection
  * @{
  */
#define LSM303DLHC_ACC_SENSITIVITY_2G     ((uint8_t)1)  /*!< accelerometer sensitivity with 2 g full scale [mg/LSB] */
#define LSM303DLHC_ACC_SENSITIVITY_4G     ((uint8_t)2)  /*!< accelerometer sensitivity with 4 g full scale [mg/LSB] */
#define LSM303DLHC_ACC_SENSITIVITY_8G     ((uint8_t)4)  /*!< accelerometer sensitivity with 8 g full scale [mg/LSB] */
#define LSM303DLHC_ACC_SENSITIVITY_16G    ((uint8_t)12) /*!< accelerometer sensitivity with 12 g full scale [mg/LSB] */
/**
  * @}
  */

/** @defgroup Acc_Block_Data_Update
  * @{
  */  
#define LSM303DLHC_BlockUpdate_Continous   ((uint8_t)0x00) /*!< Continuos Update */
#define LSM303DLHC_BlockUpdate_Single      ((uint8_t)0x80) /*!< Single Update: output registers not updated until MSB and LSB reading */
/**
  * @}
  */
  
/** @defgroup Acc_Endian_Data_selection
  * @{
  */  
#define LSM303DLHC_BLE_LSB                 ((uint8_t)0x00) /*!< Little Endian: data LSB @ lower address */
#define LSM303DLHC_BLE_MSB                 ((uint8_t)0x40) /*!< Big Endian: data MSB @ lower address */
/**
  * @}
  */
  
/** @defgroup Acc_Boot_Mode_selection
  * @{
  */
#define LSM303DLHC_BOOT_NORMALMODE         ((uint8_t)0x00)
#define LSM303DLHC_BOOT_REBOOTMEMORY       ((uint8_t)0x80)
/**
  * @}
  */  
 
/** @defgroup Acc_High_Pass_Filter_Mode
  * @{
  */   
#define LSM303DLHC_HPM_NORMAL_MODE_RES     ((uint8_t)0x00)
#define LSM303DLHC_HPM_REF_SIGNAL          ((uint8_t)0x40)
#define LSM303DLHC_HPM_NORMAL_MODE         ((uint8_t)0x80)
#define LSM303DLHC_HPM_AUTORESET_INT       ((uint8_t)0xC0)
/**
  * @}
  */

/** @defgroup Acc_High_Pass_CUT OFF_Frequency
  * @{
  */   
#define LSM303DLHC_HPFCF_8                 ((uint8_t)0x00)
#define LSM303DLHC_HPFCF_16                ((uint8_t)0x10)
#define LSM303DLHC_HPFCF_32                ((uint8_t)0x20)
#define LSM303DLHC_HPFCF_64                ((uint8_t)0x30)
/**
  * @}
  */
    
/** @defgroup Acc_High_Pass_Filter_status
  * @{
  */   
#define LSM303DLHC_HIGHPASSFILTER_DISABLE  ((uint8_t)0x00)
#define LSM303DLHC_HIGHPASSFILTER_ENABLE   ((uint8_t)0x08)
/**
  * @}
  */
  
/** @defgroup Acc_High_Pass_Filter_Click_status
  * @{
  */   
#define LSM303DLHC_HPF_CLICK_DISABLE       ((uint8_t)0x00)
#define LSM303DLHC_HPF_CLICK_ENABLE        ((uint8_t)0x04)
/**
  * @}
  */

/** @defgroup Acc_High_Pass_Filter_AOI1_status
  * @{
  */   
#define LSM303DLHC_HPF_AOI1_DISABLE        ((uint8_t)0x00)
#define LSM303DLHC_HPF_AOI1_ENABLE	       ((uint8_t)0x01)
/**
  * @}
  */
  
/** @defgroup Acc_High_Pass_Filter_AOI2_status
  * @{
  */   
#define LSM303DLHC_HPF_AOI2_DISABLE        ((uint8_t)0x00)
#define LSM303DLHC_HPF_AOI2_ENABLE         ((uint8_t)0x02)
/**
  * @}
  */ 

/** @defgroup Acc_Interrupt1_Configuration_definition
  * @{
  */
#define LSM303DLHC_IT1_CLICK               ((uint8_t)0x80)
#define LSM303DLHC_IT1_AOI1                ((uint8_t)0x40)
#define LSM303DLHC_IT1_AOI2                ((uint8_t)0x20)
#define LSM303DLHC_IT1_DRY1                ((uint8_t)0x10)
#define LSM303DLHC_IT1_DRY2                ((uint8_t)0x08)
#define LSM303DLHC_IT1_WTM                 ((uint8_t)0x04)
#define LSM303DLHC_IT1_OVERRUN             ((uint8_t)0x02)
/**
  * @}
  */  
 
/** @defgroup Acc_Interrupt2_Configuration_definition
  * @{
  */
#define LSM303DLHC_IT2_CLICK               ((uint8_t)0x80)
#define LSM303DLHC_IT2_INT1                ((uint8_t)0x40)
#define LSM303DLHC_IT2_INT2                ((uint8_t)0x20)
#define LSM303DLHC_IT2_BOOT                ((uint8_t)0x10)
#define LSM303DLHC_IT2_ACT                 ((uint8_t)0x08)
#define LSM303DLHC_IT2_HLACTIVE            ((uint8_t)0x02)
/**
  * @}
  */ 

/** @defgroup Acc_INT_Combination_Status
  * @{
  */   
#define LSM303DLHC_OR_COMBINATION          ((uint8_t)0x00)  /*!< OR combination of enabled IRQs */
#define LSM303DLHC_AND_COMBINATION         ((uint8_t)0x80)  /*!< AND combination of enabled IRQs */
#define LSM303DLHC_MOV_RECOGNITION         ((uint8_t)0x40)  /*!< 6D movement recognition */
#define LSM303DLHC_POS_RECOGNITION         ((uint8_t)0xC0)  /*!< 6D position recognition */
/**
  * @}
  */

/** @defgroup Acc_INT_Axes
  * @{
  */   
#define LSM303DLHC_Z_HIGH                  ((uint8_t)0x20)  /*!< Z High enabled IRQs */
#define LSM303DLHC_Z_LOW                   ((uint8_t)0x10)  /*!< Z low enabled IRQs */
#define LSM303DLHC_Y_HIGH                  ((uint8_t)0x08)  /*!< Y High enabled IRQs */
#define LSM303DLHC_Y_LOW                   ((uint8_t)0x04)  /*!< Y low enabled IRQs */
#define LSM303DLHC_X_HIGH                  ((uint8_t)0x02)  /*!< X High enabled IRQs */
#define LSM303DLHC_X_LOW                   ((uint8_t)0x01)  /*!< X low enabled IRQs */
/**
  * @}
  */
      
/** @defgroup Acc_INT_Click
* @{
*/   
#define LSM303DLHC_Z_DOUBLE_CLICK          ((uint8_t)0x20)  /*!< Z double click IRQs */
#define LSM303DLHC_Z_SINGLE_CLICK          ((uint8_t)0x10)  /*!< Z single click IRQs */
#define LSM303DLHC_Y_DOUBLE_CLICK          ((uint8_t)0x08)  /*!< Y double click IRQs */
#define LSM303DLHC_Y_SINGLE_CLICK          ((uint8_t)0x04)  /*!< Y single click IRQs */
#define LSM303DLHC_X_DOUBLE_CLICK          ((uint8_t)0x02)  /*!< X double click IRQs */
#define LSM303DLHC_X_SINGLE_CLICK          ((uint8_t)0x01)  /*!< X single click IRQs */
/**
* @}
*/
  
/** @defgroup Acc_INT1_Interrupt_status
  * @{
  */   
#define LSM303DLHC_INT1INTERRUPT_DISABLE   ((uint8_t)0x00)
#define LSM303DLHC_INT1INTERRUPT_ENABLE    ((uint8_t)0x80)
/**
  * @}
  */

/** @defgroup Acc_INT1_Interrupt_ActiveEdge
  * @{
  */   
#define LSM303DLHC_INT1INTERRUPT_LOW_EDGE  ((uint8_t)0x20)
#define LSM303DLHC_INT1INTERRUPT_HIGH_EDGE ((uint8_t)0x00)
/**
  * @}
  */

/** @defgroup Mag_Data_Rate
  * @{
  */ 
#define LSM303DLHC_ODR_0_75_HZ              ((uint8_t) 0x00)  /*!< Output Data Rate = 0.75 Hz */
#define LSM303DLHC_ODR_1_5_HZ               ((uint8_t) 0x04)  /*!< Output Data Rate = 1.5 Hz */
#define LSM303DLHC_ODR_3_0_HZ               ((uint8_t) 0x08)  /*!< Output Data Rate = 3 Hz */
#define LSM303DLHC_ODR_7_5_HZ               ((uint8_t) 0x0C)  /*!< Output Data Rate = 7.5 Hz */
#define LSM303DLHC_ODR_15_HZ                ((uint8_t) 0x10)  /*!< Output Data Rate = 15 Hz */
#define LSM303DLHC_ODR_30_HZ                ((uint8_t) 0x14)  /*!< Output Data Rate = 30 Hz */
#define LSM303DLHC_ODR_75_HZ                ((uint8_t) 0x18)  /*!< Output Data Rate = 75 Hz */
#define LSM303DLHC_ODR_220_HZ               ((uint8_t) 0x1C)  /*!< Output Data Rate = 220 Hz */
/**
  * @}
  */
 
/** @defgroup Mag_Full_Scale
  * @{
  */ 
#define  LSM303DLHC_FS_1_3_GA               ((uint8_t) 0x20)  /*!< Full scale = ±1.3 Gauss */
#define  LSM303DLHC_FS_1_9_GA               ((uint8_t) 0x40)  /*!< Full scale = ±1.9 Gauss */
#define  LSM303DLHC_FS_2_5_GA               ((uint8_t) 0x60)  /*!< Full scale = ±2.5 Gauss */
#define  LSM303DLHC_FS_4_0_GA               ((uint8_t) 0x80)  /*!< Full scale = ±4.0 Gauss */
#define  LSM303DLHC_FS_4_7_GA               ((uint8_t) 0xA0)  /*!< Full scale = ±4.7 Gauss */
#define  LSM303DLHC_FS_5_6_GA               ((uint8_t) 0xC0)  /*!< Full scale = ±5.6 Gauss */
#define  LSM303DLHC_FS_8_1_GA               ((uint8_t) 0xE0)  /*!< Full scale = ±8.1 Gauss */
/**
  * @}
  */ 
 
/**
 * @defgroup Magnetometer_Sensitivity
 * @{
 */
#define LSM303DLHC_M_SENSITIVITY_XY_1_3Ga     1100  /*!< magnetometer X Y axes sensitivity for 1.3 Ga full scale [LSB/Ga] */
#define LSM303DLHC_M_SENSITIVITY_XY_1_9Ga     855   /*!< magnetometer X Y axes sensitivity for 1.9 Ga full scale [LSB/Ga] */
#define LSM303DLHC_M_SENSITIVITY_XY_2_5Ga     670   /*!< magnetometer X Y axes sensitivity for 2.5 Ga full scale [LSB/Ga] */
#define LSM303DLHC_M_SENSITIVITY_XY_4Ga       450   /*!< magnetometer X Y axes sensitivity for 4 Ga full scale [LSB/Ga] */
#define LSM303DLHC_M_SENSITIVITY_XY_4_7Ga     400   /*!< magnetometer X Y axes sensitivity for 4.7 Ga full scale [LSB/Ga] */
#define LSM303DLHC_M_SENSITIVITY_XY_5_6Ga     330   /*!< magnetometer X Y axes sensitivity for 5.6 Ga full scale [LSB/Ga] */
#define LSM303DLHC_M_SENSITIVITY_XY_8_1Ga     230   /*!< magnetometer X Y axes sensitivity for 8.1 Ga full scale [LSB/Ga] */
#define LSM303DLHC_M_SENSITIVITY_Z_1_3Ga      980   /*!< magnetometer Z axis sensitivity for 1.3 Ga full scale [LSB/Ga] */
#define LSM303DLHC_M_SENSITIVITY_Z_1_9Ga      760   /*!< magnetometer Z axis sensitivity for 1.9 Ga full scale [LSB/Ga] */
#define LSM303DLHC_M_SENSITIVITY_Z_2_5Ga      600   /*!< magnetometer Z axis sensitivity for 2.5 Ga full scale [LSB/Ga] */
#define LSM303DLHC_M_SENSITIVITY_Z_4Ga        400   /*!< magnetometer Z axis sensitivity for 4 Ga full scale [LSB/Ga] */
#define LSM303DLHC_M_SENSITIVITY_Z_4_7Ga      355   /*!< magnetometer Z axis sensitivity for 4.7 Ga full scale [LSB/Ga] */
#define LSM303DLHC_M_SENSITIVITY_Z_5_6Ga      295   /*!< magnetometer Z axis sensitivity for 5.6 Ga full scale [LSB/Ga] */
#define LSM303DLHC_M_SENSITIVITY_Z_8_1Ga      205   /*!< magnetometer Z axis sensitivity for 8.1 Ga full scale [LSB/Ga] */
/**
 * @}
 */

/** @defgroup Mag_Working_Mode
  * @{
  */ 
#define LSM303DLHC_CONTINUOS_CONVERSION      ((uint8_t) 0x00)   /*!< Continuous-Conversion Mode */
#define LSM303DLHC_SINGLE_CONVERSION         ((uint8_t) 0x01)   /*!< Single-Conversion Mode */
#define LSM303DLHC_SLEEP                     ((uint8_t) 0x02)   /*!< Sleep Mode */                       
/**
  * @}
  */

/** @defgroup Mag_Temperature_Sensor
  * @{
  */ 
#define LSM303DLHC_TEMPSENSOR_ENABLE         ((uint8_t) 0x80)   /*!< Temp sensor Enable */
#define LSM303DLHC_TEMPSENSOR_DISABLE        ((uint8_t) 0x00)   /*!< Temp sensor Disable */
/**
  * @}
  */
  
/** @defgroup LSM303DLHC_Exported_Functions
  * @{
  */
/* ACC functions */
void    LSM303DLHC_AccInit(uint16_t InitStruct);
void    LSM303DLHC_AccDeInit(void);
uint8_t LSM303DLHC_AccReadID(void);
void    LSM303DLHC_AccRebootCmd(void);
void    LSM303DLHC_AccFilterConfig(uint8_t FilterStruct);
void    LSM303DLHC_AccFilterCmd(uint8_t HighPassFilterState);
void    LSM303DLHC_AccReadXYZ(int16_t* pData);
void    LSM303DLHC_AccFilterClickCmd(uint8_t HighPassFilterClickState);
void    LSM303DLHC_AccIT1Enable(uint8_t LSM303DLHC_IT);
void    LSM303DLHC_AccIT1Disable(uint8_t LSM303DLHC_IT);
void    LSM303DLHC_AccIT2Enable(uint8_t LSM303DLHC_IT);
void    LSM303DLHC_AccIT2Disable(uint8_t LSM303DLHC_IT);
void    LSM303DLHC_AccINT1InterruptEnable(uint8_t ITCombination, uint8_t ITAxes);
void    LSM303DLHC_AccINT1InterruptDisable(uint8_t ITCombination, uint8_t ITAxes);
void    LSM303DLHC_AccINT2InterruptEnable(uint8_t ITCombination, uint8_t ITAxes);
void    LSM303DLHC_AccINT2InterruptDisable(uint8_t ITCombination, uint8_t ITAxes);
void    LSM303DLHC_AccClickITEnable(uint8_t ITClick);
void    LSM303DLHC_AccClickITDisable(uint8_t ITClick);
void    LSM303DLHC_AccZClickITConfig(void);

/* COMPASS / ACCELERO IO functions */
void    COMPASSACCELERO_IO_Init(void);
void    COMPASSACCELERO_IO_ITConfig(void);
void    COMPASSACCELERO_IO_Write(uint16_t DeviceAddr, uint8_t RegisterAddr, uint8_t Value);
uint8_t COMPASSACCELERO_IO_Read(uint16_t DeviceAddr, uint8_t RegisterAddr);

/* ACC driver structure */
extern ACCELERO_DrvTypeDef Lsm303dlhcDrv;

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

#endif /* __LSM303DLHC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/ 
