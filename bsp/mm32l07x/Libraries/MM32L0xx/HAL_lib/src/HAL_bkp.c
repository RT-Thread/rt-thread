/**
******************************************************************************
* @file  HAL_bkp.c
* @author  AE Team
* @version  V2.0.0
* @date  22/08/2017
* @brief  This file provides all the BKP firmware functions.
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

/* Includes ------------------------------------------------------------------*/
#include "HAL_bkp.h"

/** @addtogroup StdPeriph_Driver
* @{
*/

/** @defgroup BKP 
* @brief BKP driver modules
* @{
*/

/**
* @brief  Writes user data to the specified Data Backup Register.
* @param BKP_DR: specifies the Data Backup Register.
*   This parameter can be BKP_DRx where x:[1, 42]
* @param Data: data to write
* @retval : None
*/
void BKP_WriteBackupRegister(uint16_t BKP_DR, uint16_t Data)
{
  /* Check the parameters */
  assert_param(IS_BKP_DR(BKP_DR));
  *(__IO uint16_t *) (BKP_BASE + BKP_DR) = Data;
}

/**
* @brief  Reads data from the specified Data Backup Register.
* @param BKP_DR: specifies the Data Backup Register.
*   This parameter can be BKP_DRx where x:[1, 42]
* @retval : The content of the specified Data Backup Register
*/
uint16_t BKP_ReadBackupRegister(uint16_t BKP_DR)
{
  /* Check the parameters */
  assert_param(IS_BKP_DR(BKP_DR));
  return (*(__IO uint16_t *) (BKP_BASE + BKP_DR));
}

/*-------------------------(C) COPYRIGHT 2017 MindMotion ----------------------*/
