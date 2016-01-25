/**
  ******************************************************************************
  * @file    gyro.h
  * @author  MCD Application Team
  * @version V4.0.1
  * @date    21-July-2015
  * @brief   This header file contains the functions prototypes for the gyroscope driver.
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
#ifndef __GYRO_H
#define __GYRO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @addtogroup BSP
  * @{
  */

/** @addtogroup Components
  * @{
  */
    
/** @addtogroup GYRO
  * @{
  */

/** @defgroup GYRO_Exported_Types
  * @{
  */

/** @defgroup GYRO_Driver_structure  Gyroscope Driver structure
  * @{
  */
typedef struct
{  
  void       (*Init)(uint16_t);
  void       (*DeInit)(void); 
  uint8_t    (*ReadID)(void);
  void       (*Reset)(void);
  void       (*LowPower)(uint16_t);   
  void       (*ConfigIT)(uint16_t); 
  void       (*EnableIT)(uint8_t);
  void       (*DisableIT)(uint8_t);  
  uint8_t    (*ITStatus)(uint16_t, uint16_t);   
  void       (*ClearIT)(uint16_t, uint16_t); 
  void       (*FilterConfig)(uint8_t);  
  void       (*FilterCmd)(uint8_t);  
  void       (*GetXYZ)(float *);
}GYRO_DrvTypeDef;
/**
  * @}
  */

/** @defgroup GYRO_Config_structure  Gyroscope Configuration structure
  * @{
  */

typedef struct
{
  uint8_t Power_Mode;                         /* Power-down/Sleep/Normal Mode */
  uint8_t Output_DataRate;                    /* OUT data rate */
  uint8_t Axes_Enable;                        /* Axes enable */
  uint8_t Band_Width;                         /* Bandwidth selection */
  uint8_t BlockData_Update;                   /* Block Data Update */
  uint8_t Endianness;                         /* Endian Data selection */
  uint8_t Full_Scale;                         /* Full Scale selection */
}GYRO_InitTypeDef;

/* GYRO High Pass Filter struct */
typedef struct
{
  uint8_t HighPassFilter_Mode_Selection;      /* Internal filter mode */
  uint8_t HighPassFilter_CutOff_Frequency;    /* High pass filter cut-off frequency */
}GYRO_FilterConfigTypeDef;

/*GYRO Interrupt struct */
typedef struct
{
  uint8_t Latch_Request;                      /* Latch interrupt request into CLICK_SRC register */
  uint8_t Interrupt_Axes;                     /* X, Y, Z Axes Interrupts */ 
  uint8_t Interrupt_ActiveEdge;               /* Interrupt Active edge */
}GYRO_InterruptConfigTypeDef;  

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

#endif /* __GYRO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
