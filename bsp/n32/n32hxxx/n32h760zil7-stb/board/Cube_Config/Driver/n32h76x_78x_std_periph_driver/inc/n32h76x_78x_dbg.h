/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_dbg.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H76x_78x_DBG_H__
#define __N32H76x_78x_DBG_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

#include "n32h76x_78x.h"


#define DBG_FLASH_SIZE_MASK       ((uint32_t)0x000000C0U)
#define DBG_REV_NUM_MASK          ((uint32_t)0xFF000000U)
#define DBG_DEV_NUM_MASK          ((uint32_t)0x00FFF000U)

#define REGISTER_OFFSET_POS       ((uint8_t)0x18U)
#define REGISTER_OFFSET_MASK      ((uint32_t)0xFF000000U)
#define REGISTER_DBG_CTRL_OFFSET  ((uint32_t)0x04000000U)
#define REGISTER_M7_APB1_OFFSET   ((uint32_t)0x08000000U)
#define REGISTER_M7_APB2_OFFSET   ((uint32_t)0x10000000U)
#define REGISTER_M7_APB5_OFFSET   ((uint32_t)0x18000000U)
#define REGISTER_M7_APB6_OFFSET   ((uint32_t)0x20000000U)



#define DBG_TRGIO_INPUT_DIRECTION  ((uint32_t)0x00000000U)
#define DBG_TRGIO_OUTPUT_DIRECTION (DBG_CTRL_TRACE_IOEN)

#define DBG_M7SLEEP               (DBG_CTRL_M7SLEEP | REGISTER_DBG_CTRL_OFFSET)
#define DBG_M7STOP                (DBG_CTRL_M7STOP  | REGISTER_DBG_CTRL_OFFSET)
#define DBG_M7STANDBY             (DBG_CTRL_M7STBY  | REGISTER_DBG_CTRL_OFFSET)
#define DBG_M4SLEEP               (DBG_CTRL_M4SLEEP | REGISTER_DBG_CTRL_OFFSET)
#define DBG_M4STOP                (DBG_CTRL_M4STOP  | REGISTER_DBG_CTRL_OFFSET)
#define DBG_M4STANDBY             (DBG_CTRL_M4STBY  | REGISTER_DBG_CTRL_OFFSET)

#define DBG_WWDG1_STOP            (DBG_M7APB6FZ_WWDG1_STOP | REGISTER_M7_APB6_OFFSET )

#define DBG_ATIM3_STOP            (DBG_M7APB5FZ_ATIM3_STOP  | REGISTER_M7_APB5_OFFSET)
#define DBG_ATIM4_STOP            (DBG_M7APB5FZ_ATIM4_STOP  | REGISTER_M7_APB5_OFFSET)
#define DBG_I2C7SMBUS_TIMEOUT     (DBG_M7APB5FZ_I2C7_STOP   | REGISTER_M7_APB5_OFFSET)
#define DBG_I2C8SMBUS_TIMEOUT     (DBG_M7APB5FZ_I2C8_STOP   | REGISTER_M7_APB5_OFFSET)
#define DBG_I2C9SMBUS_TIMEOUT     (DBG_M7APB5FZ_I2C9_STOP   | REGISTER_M7_APB5_OFFSET)
#define DBG_I2C10SMBUS_TIMEOUT    (DBG_M7APB5FZ_I2C10_STOP  | REGISTER_M7_APB5_OFFSET)
#define DBG_IWDG1_STOP            (DBG_M7APB5FZ_IWDG1_STOP  | REGISTER_M7_APB5_OFFSET)
#define DBG_IWDG2_STOP            (DBG_M7APB5FZ_IWDG2_STOP  | REGISTER_M7_APB5_OFFSET)
#define DBG_LPTIM1_STOP           (DBG_M7APB5FZ_LPTIM1_STOP | REGISTER_M7_APB5_OFFSET)
#define DBG_LPTIM2_STOP           (DBG_M7APB5FZ_LPTIM2_STOP | REGISTER_M7_APB5_OFFSET)
#define DBG_LPTIM3_STOP           (DBG_M7APB5FZ_LPTIM3_STOP | REGISTER_M7_APB5_OFFSET)
#define DBG_LPTIM4_STOP           (DBG_M7APB5FZ_LPTIM4_STOP | REGISTER_M7_APB5_OFFSET)
#define DBG_LPTIM5_STOP           (DBG_M7APB5FZ_LPTIM5_STOP | REGISTER_M7_APB5_OFFSET)
#define DBG_RTC_STOP              (DBG_M7APB5FZ_RTC_STOP    | REGISTER_M7_APB5_OFFSET)

#define DBG_CANFD3_STOP           (DBG_M7APB2FZ_CANFD3_STOP  | REGISTER_M7_APB2_OFFSET)
#define DBG_CANFD4_STOP           (DBG_M7APB2FZ_CANFD4_STOP  | REGISTER_M7_APB2_OFFSET)
#define DBG_CANFD7_STOP           (DBG_M7APB2FZ_CANFD7_STOP  | REGISTER_M7_APB2_OFFSET)
#define DBG_CANFD8_STOP           (DBG_M7APB2FZ_CANFD8_STOP  | REGISTER_M7_APB2_OFFSET)
#define DBG_I2C4SMBUS_TIMEOUT     (DBG_M7APB2FZ_I2C4_STOP    | REGISTER_M7_APB2_OFFSET)
#define DBG_I2C5SMBUS_TIMEOUT     (DBG_M7APB2FZ_I2C5_STOP    | REGISTER_M7_APB2_OFFSET)
#define DBG_I2C6SMBUS_TIMEOUT     (DBG_M7APB2FZ_I2C6_STOP    | REGISTER_M7_APB2_OFFSET)
#define DBG_ATIM1_STOP            (DBG_M7APB2FZ_ATIM1_STOP   | REGISTER_M7_APB2_OFFSET)
#define DBG_ATIM2_STOP            (DBG_M7APB2FZ_ATIM2_STOP   | REGISTER_M7_APB2_OFFSET)
#define DBG_GTIMA1_STOP           (DBG_M7APB2FZ_GTIMA1_STOP  | REGISTER_M7_APB2_OFFSET)
#define DBG_GTIMA2_STOP           (DBG_M7APB2FZ_GTIMA2_STOP  | REGISTER_M7_APB2_OFFSET)
#define DBG_GTIMA3_STOP           (DBG_M7APB2FZ_GTIMA3_STOP  | REGISTER_M7_APB2_OFFSET)
#define DBG_SHRTIM1_STOP          (DBG_M7APB2FZ_SHRTIM1_STOP | REGISTER_M7_APB2_OFFSET)
#define DBG_SHRTIM2_STOP          (DBG_M7APB2FZ_SHRTIM2_STOP | REGISTER_M7_APB2_OFFSET)

#define DBG_BTIM1_STOP            (DBG_M7APB1FZ_BTIM1_STOP  | REGISTER_M7_APB1_OFFSET)
#define DBG_BTIM2_STOP            (DBG_M7APB1FZ_BTIM2_STOP  | REGISTER_M7_APB1_OFFSET)
#define DBG_BTIM3_STOP            (DBG_M7APB1FZ_BTIM3_STOP  | REGISTER_M7_APB1_OFFSET)
#define DBG_BTIM4_STOP            (DBG_M7APB1FZ_BTIM4_STOP  | REGISTER_M7_APB1_OFFSET)
#define DBG_GTIMA4_STOP           (DBG_M7APB1FZ_GTIMA4_STOP | REGISTER_M7_APB1_OFFSET)
#define DBG_GTIMA5_STOP           (DBG_M7APB1FZ_GTIMA5_STOP | REGISTER_M7_APB1_OFFSET)
#define DBG_GTIMA6_STOP           (DBG_M7APB1FZ_GTIMA6_STOP | REGISTER_M7_APB1_OFFSET)
#define DBG_GTIMA7_STOP           (DBG_M7APB1FZ_GTIMA7_STOP | REGISTER_M7_APB1_OFFSET)
#define DBG_GTIMB1_STOP           (DBG_M7APB1FZ_GTIMB1_STOP | REGISTER_M7_APB1_OFFSET)
#define DBG_GTIMB2_STOP           (DBG_M7APB1FZ_GTIMB2_STOP | REGISTER_M7_APB1_OFFSET)
#define DBG_GTIMB3_STOP           (DBG_M7APB1FZ_GTIMB3_STOP | REGISTER_M7_APB1_OFFSET)
#define DBG_I2C1SMBUS_TIMEOUT     (DBG_M7APB1FZ_I2C1_STOP   | REGISTER_M7_APB1_OFFSET)
#define DBG_I2C2SMBUS_TIMEOUT     (DBG_M7APB1FZ_I2C2_STOP   | REGISTER_M7_APB1_OFFSET)
#define DBG_I2C3SMBUS_TIMEOUT     (DBG_M7APB1FZ_I2C3_STOP   | REGISTER_M7_APB1_OFFSET)
#define DBG_WWDG2_STOP            (DBG_M7APB1FZ_WWDG2_STOP  | REGISTER_M7_APB1_OFFSET)
#define DBG_CANFD1_STOP           (DBG_M7APB1FZ_CANFD1_STOP | REGISTER_M7_APB1_OFFSET)
#define DBG_CANFD2_STOP           (DBG_M7APB1FZ_CANFD2_STOP | REGISTER_M7_APB1_OFFSET)
#define DBG_CANFD5_STOP           (DBG_M7APB1FZ_CANFD5_STOP | REGISTER_M7_APB1_OFFSET)
#define DBG_CANFD6_STOP           (DBG_M7APB1FZ_CANFD6_STOP | REGISTER_M7_APB1_OFFSET)



uint32_t DBG_GetRevNum(void);
uint32_t DBG_GetDevNum(void);

void DBG_SetExternalTriggerPinDirection(uint32_t PinDirection);
void DBG_M7ConfigPeriph(uint32_t DBG_Periph, FunctionalState Cmd);
void DBG_M4ConfigPeriph(uint32_t DBG_Periph, FunctionalState Cmd);

uint32_t DBG_GetFlashSize(void);


#ifdef __cplusplus
}
#endif

#endif /* __N32H76x_78x_DBG_H__ */


