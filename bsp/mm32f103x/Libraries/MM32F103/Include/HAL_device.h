/**
******************************************************************************
* @file    HAL_device.h
* @author  AE Team
* @version V1.1.0
* @date    28/08/2019
* @brief   This file contains all the Device inc file for the library.
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
* <h2><center>&copy; COPYRIGHT 2019 MindMotion</center></h2>
*/

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __HAL_device_H
#define __HAL_device_H


#define MM32F103

#if defined(MM32F103)
#include "MM32F103.h"
#include "SYSTEM_MM32F103.h"
#else
#error "HAL_device.h: PART NUMBER undefined"
#endif
#endif /* __HAL_device_H */
/*-------------------------(C) COPYRIGHT 2019 MindMotion ----------------------*/

