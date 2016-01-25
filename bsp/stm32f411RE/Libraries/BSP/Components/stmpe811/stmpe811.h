/**
  ******************************************************************************
  * @file    stmpe811.h
  * @author  MCD Application Team
  * @version V2.0.0
  * @date    15-December-2014
  * @brief   This file contains all the functions prototypes for the
  *          stmpe811.c IO expander driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
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
#ifndef __STMPE811_H
#define __STMPE811_H

#ifdef __cplusplus
 extern "C" {
#endif   
   
/* Includes ------------------------------------------------------------------*/
#include "../Common/ts.h"
#include "../Common/io.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */
    
/** @defgroup STMPE811
  * @{
  */    

/** @defgroup STMPE811_Exported_Types
  * @{
  */ 
/**
  * @}
  */ 
   
/** @defgroup STMPE811_Exported_Constants
  * @{
  */ 

/* Chip IDs */   
#define STMPE811_ID                     0x0811
    
/* Identification registers & System Control */ 
#define STMPE811_REG_CHP_ID_LSB         0x00
#define STMPE811_REG_CHP_ID_MSB         0x01
#define STMPE811_REG_ID_VER             0x02

/* Global interrupt Enable bit */ 
#define STMPE811_GIT_EN                 0x01   

/* IO expander functionalities */        
#define STMPE811_ADC_FCT                0x01
#define STMPE811_TS_FCT                 0x02
#define STMPE811_IO_FCT                 0x04
#define STMPE811_TEMPSENS_FCT           0x08

/* Global Interrupts definitions */ 
#define STMPE811_GIT_IO                 0x80  /* IO interrupt                   */
#define STMPE811_GIT_ADC                0x40  /* ADC interrupt                  */
#define STMPE811_GIT_TEMP               0x20  /* Not implemented                */
#define STMPE811_GIT_FE                 0x10  /* FIFO empty interrupt           */
#define STMPE811_GIT_FF                 0x08  /* FIFO full interrupt            */
#define STMPE811_GIT_FOV                0x04  /* FIFO overflowed interrupt      */
#define STMPE811_GIT_FTH                0x02  /* FIFO above threshold interrupt */
#define STMPE811_GIT_TOUCH              0x01  /* Touch is detected interrupt    */      
#define STMPE811_ALL_GIT                0x1F  /* All global interrupts          */
#define STMPE811_TS_IT                  (STMPE811_GIT_TOUCH | STMPE811_GIT_FTH |  STMPE811_GIT_FOV | STMPE811_GIT_FF | STMPE811_GIT_FE) /* Touch screen interrupts */
    
/* General Control Registers */ 
#define STMPE811_REG_SYS_CTRL1          0x03
#define STMPE811_REG_SYS_CTRL2          0x04
#define STMPE811_REG_SPI_CFG            0x08 

/* Interrupt system Registers */ 
#define STMPE811_REG_INT_CTRL           0x09
#define STMPE811_REG_INT_EN             0x0A
#define STMPE811_REG_INT_STA            0x0B
#define STMPE811_REG_IO_INT_EN          0x0C
#define STMPE811_REG_IO_INT_STA         0x0D

/* IO Registers */ 
#define STMPE811_REG_IO_SET_PIN         0x10
#define STMPE811_REG_IO_CLR_PIN         0x11
#define STMPE811_REG_IO_MP_STA          0x12
#define STMPE811_REG_IO_DIR             0x13
#define STMPE811_REG_IO_ED              0x14
#define STMPE811_REG_IO_RE              0x15
#define STMPE811_REG_IO_FE              0x16
#define STMPE811_REG_IO_AF              0x17

/* ADC Registers */ 
#define STMPE811_REG_ADC_INT_EN         0x0E
#define STMPE811_REG_ADC_INT_STA        0x0F
#define STMPE811_REG_ADC_CTRL1          0x20
#define STMPE811_REG_ADC_CTRL2          0x21
#define STMPE811_REG_ADC_CAPT           0x22
#define STMPE811_REG_ADC_DATA_CH0       0x30 
#define STMPE811_REG_ADC_DATA_CH1       0x32 
#define STMPE811_REG_ADC_DATA_CH2       0x34 
#define STMPE811_REG_ADC_DATA_CH3       0x36 
#define STMPE811_REG_ADC_DATA_CH4       0x38 
#define STMPE811_REG_ADC_DATA_CH5       0x3A 
#define STMPE811_REG_ADC_DATA_CH6       0x3B 
#define STMPE811_REG_ADC_DATA_CH7       0x3C 

/* Touch Screen Registers */ 
#define STMPE811_REG_TSC_CTRL           0x40
#define STMPE811_REG_TSC_CFG            0x41
#define STMPE811_REG_WDM_TR_X           0x42 
#define STMPE811_REG_WDM_TR_Y           0x44
#define STMPE811_REG_WDM_BL_X           0x46
#define STMPE811_REG_WDM_BL_Y           0x48
#define STMPE811_REG_FIFO_TH            0x4A
#define STMPE811_REG_FIFO_STA           0x4B
#define STMPE811_REG_FIFO_SIZE          0x4C
#define STMPE811_REG_TSC_DATA_X         0x4D 
#define STMPE811_REG_TSC_DATA_Y         0x4F
#define STMPE811_REG_TSC_DATA_Z         0x51
#define STMPE811_REG_TSC_DATA_XYZ       0x52 
#define STMPE811_REG_TSC_FRACT_XYZ      0x56
#define STMPE811_REG_TSC_DATA_INC       0x57
#define STMPE811_REG_TSC_DATA_NON_INC   0xD7
#define STMPE811_REG_TSC_I_DRIVE        0x58
#define STMPE811_REG_TSC_SHIELD         0x59

/* Touch Screen Pins definition */ 
#define STMPE811_TOUCH_YD               STMPE811_PIN_7 
#define STMPE811_TOUCH_XD               STMPE811_PIN_6
#define STMPE811_TOUCH_YU               STMPE811_PIN_5
#define STMPE811_TOUCH_XU               STMPE811_PIN_4
#define STMPE811_TOUCH_IO_ALL           (uint32_t)(STMPE811_TOUCH_YD | STMPE811_TOUCH_XD | STMPE811_TOUCH_YU | STMPE811_TOUCH_XU)

/* IO Pins definition */ 
#define STMPE811_PIN_0                  0x01
#define STMPE811_PIN_1                  0x02
#define STMPE811_PIN_2                  0x04
#define STMPE811_PIN_3                  0x08
#define STMPE811_PIN_4                  0x10
#define STMPE811_PIN_5                  0x20
#define STMPE811_PIN_6                  0x40
#define STMPE811_PIN_7                  0x80
#define STMPE811_PIN_ALL                0xFF

/* IO Pins directions */ 
#define STMPE811_DIRECTION_IN           0x00
#define STMPE811_DIRECTION_OUT          0x01

/* IO IT types */   
#define STMPE811_TYPE_LEVEL             0x00
#define STMPE811_TYPE_EDGE              0x02

/* IO IT polarity */   
#define STMPE811_POLARITY_LOW           0x00
#define STMPE811_POLARITY_HIGH          0x04

/* IO Pin IT edge modes */
#define STMPE811_EDGE_FALLING           0x01
#define STMPE811_EDGE_RISING            0x02

/* TS registers masks */
#define STMPE811_TS_CTRL_ENABLE         0x01  
#define STMPE811_TS_CTRL_STATUS         0x80
/**
  * @}
  */ 
   
/** @defgroup STMPE811_Exported_Macros
  * @{
  */ 
/**
  * @}
  */ 
   
/** @defgroup STMPE811_Exported_Functions
  * @{
  */

/** 
  * @brief STMPE811 Control functions
  */
void     stmpe811_Init(uint16_t DeviceAddr);
void     stmpe811_Reset(uint16_t DeviceAddr);
uint16_t stmpe811_ReadID(uint16_t DeviceAddr);
void     stmpe811_EnableGlobalIT(uint16_t DeviceAddr);
void     stmpe811_DisableGlobalIT(uint16_t DeviceAddr);
void     stmpe811_EnableITSource(uint16_t DeviceAddr, uint8_t Source);
void     stmpe811_DisableITSource(uint16_t DeviceAddr, uint8_t Source);
void     stmpe811_SetITPolarity(uint16_t DeviceAddr, uint8_t Polarity);
void     stmpe811_SetITType(uint16_t DeviceAddr, uint8_t Type);
uint8_t  stmpe811_GlobalITStatus(uint16_t DeviceAddr, uint8_t Source);
uint8_t  stmpe811_ReadGITStatus(uint16_t DeviceAddr, uint8_t Source);
void     stmpe811_ClearGlobalIT(uint16_t DeviceAddr, uint8_t Source);

/** 
  * @brief STMPE811 IO functionalities functions
  */
void     stmpe811_IO_Start(uint16_t DeviceAddr, uint32_t IO_Pin);
uint8_t  stmpe811_IO_Config(uint16_t DeviceAddr, uint32_t IO_Pin, IO_ModeTypedef IO_Mode);
void     stmpe811_IO_InitPin(uint16_t DeviceAddr, uint32_t IO_Pin, uint8_t Direction);
void     stmpe811_IO_EnableAF(uint16_t DeviceAddr, uint32_t IO_Pin);
void     stmpe811_IO_DisableAF(uint16_t DeviceAddr, uint32_t IO_Pin);
void     stmpe811_IO_SetEdgeMode(uint16_t DeviceAddr, uint32_t IO_Pin, uint8_t Edge);
void     stmpe811_IO_WritePin(uint16_t DeviceAddr, uint32_t IO_Pin, uint8_t PinState);
uint32_t stmpe811_IO_ReadPin(uint16_t DeviceAddr, uint32_t IO_Pin);
void     stmpe811_IO_EnableIT(uint16_t DeviceAddr);
void     stmpe811_IO_DisableIT(uint16_t DeviceAddr);
void     stmpe811_IO_EnablePinIT(uint16_t DeviceAddr, uint32_t IO_Pin);
void     stmpe811_IO_DisablePinIT(uint16_t DeviceAddr, uint32_t IO_Pin);
uint32_t stmpe811_IO_ITStatus(uint16_t DeviceAddr, uint32_t IO_Pin);
void     stmpe811_IO_ClearIT(uint16_t DeviceAddr, uint32_t IO_Pin);

/** 
  * @brief STMPE811 Touch screen functionalities functions
  */
void     stmpe811_TS_Start(uint16_t DeviceAddr);
uint8_t  stmpe811_TS_DetectTouch(uint16_t DeviceAddr);
void     stmpe811_TS_GetXY(uint16_t DeviceAddr, uint16_t *X, uint16_t *Y);
void     stmpe811_TS_EnableIT(uint16_t DeviceAddr);
void     stmpe811_TS_DisableIT(uint16_t DeviceAddr);
uint8_t  stmpe811_TS_ITStatus (uint16_t DeviceAddr);
void     stmpe811_TS_ClearIT (uint16_t DeviceAddr);

void     IOE_Init(void);
void     IOE_ITConfig (void);
void     IOE_Delay(uint32_t delay);
void     IOE_Write(uint8_t addr, uint8_t reg, uint8_t value);
uint8_t  IOE_Read(uint8_t addr, uint8_t reg);
uint16_t IOE_ReadMultiple(uint8_t addr, uint8_t reg, uint8_t *buffer, uint16_t length);

/* Touch screen driver structure */
extern TS_DrvTypeDef stmpe811_ts_drv;

/* IO driver structure */
extern IO_DrvTypeDef stmpe811_io_drv;

#ifdef __cplusplus
}
#endif
#endif /* __STMPE811_H */

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
