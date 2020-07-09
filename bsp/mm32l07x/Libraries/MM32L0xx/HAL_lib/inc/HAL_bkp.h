/**
******************************************************************************
* @file  HAL_bkp.h
* @author  AE Team
* @version  V2.0.0
* @date  22/08/2017
* @brief  This file contains all the functions prototypes for the BKP firmware 
*         library.
******************************************************************************
* @copy
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MindMotion SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2017 MindMotion</center></h2>
*/ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_BKP_H
#define __HAL_BKP_H

/* Includes ------------------------------------------------------------------*/
#include "HAL_device.h"

/** @addtogroup StdPeriph_Driver
* @{
*/


#define BKP_DR1                          ((uint16_t)0x0050)
#define BKP_DR2                          ((uint16_t)0x0054)
#define BKP_DR3                          ((uint16_t)0x0058)
#define BKP_DR4                          ((uint16_t)0x005C)
#define BKP_DR5                          ((uint16_t)0x0060)
#define BKP_DR6                          ((uint16_t)0x0064)
#define BKP_DR7                          ((uint16_t)0x0068)
#define BKP_DR8                          ((uint16_t)0x006C)
#define BKP_DR9                          ((uint16_t)0x0070)
#define BKP_DR10                         ((uint16_t)0x0074)

#define IS_BKP_DR(DR) (((DR) == BKP_DR1)  || ((DR) == BKP_DR2)  || ((DR) == BKP_DR3)  || \
((DR) == BKP_DR4)  || ((DR) == BKP_DR5)  || ((DR) == BKP_DR6)  || \
  ((DR) == BKP_DR7)  || ((DR) == BKP_DR8)  || ((DR) == BKP_DR9)  || \
    ((DR) == BKP_DR10))

#define IS_BKP_CALIBRATION_VALUE(VALUE) ((VALUE) <= 0x7F)
/**
* @}
*/

/**
* @}
*/

/** @defgroup BKP_Exported_Macros
* @{
*/

/**
* @}
*/

/** @defgroup BKP_Exported_Functions
* @{
*/


void BKP_WriteBackupRegister(uint16_t BKP_DR, uint16_t Data);
uint16_t BKP_ReadBackupRegister(uint16_t BKP_DR);

#endif /* __HAL_BKP_H */
/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*-------------------------(C) COPYRIGHT 2017 MindMotion ----------------------*/
