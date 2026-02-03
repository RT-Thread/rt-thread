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
 * @file n32h76x_78x_vrefbuf.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H76X_78X_VREFBUF_H__
#define __N32H76X_78X_VREFBUF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h76x_78x.h"

/** VREFBUF Register list**/
#define VREFBUF_STS_REG_ADDR                     ((uint32_t)AFEC_BASE + 0x34U)
#define VREFBUF_CTRL1_REG_ADDR                   ((uint32_t)AFEC_BASE + 0x48U)
#define VREFBUF_CTRL2_REG_ADDR                   ((uint32_t)AFEC_BASE + 0xDCU)
#define VREFBUF_TRIM1_REG_ADDR                   ((uint32_t)AFEC_BASE + 0x28U)
#define VREFBUF_TRIM2_REG_ADDR                   ((uint32_t)AFEC_BASE + 0xE8U)

#define VREFBUF_EN_CTRL                          ((uint32_t)AFEC_BASE + 0x3CU)  

/** VREFBUF_Exported_Constants **/
#define VREFBUF_EN_MASK                           (VREFBUF_CTRL1_EN)
#define VREFBUF_HIM_EN_MASK                       (VREFBUF_CTRL1_HIM)

#define VREFBUF_VOLTAGE_SCALE_MASK                (VREFBUF_CTRL2_VLSEL)
#define VREFBUF_VOLTAGE_SCALE_2_5V                ((uint32_t)0x00000000U)
#define VREFBUF_VOLTAGE_SCALE_2_048V              (VREFBUF_CTRL2_VLSEL_0)
#define VREFBUF_VOLTAGE_SCALE_1_8V                (VREFBUF_CTRL2_VLSEL_1)
#define VREFBUF_VOLTAGE_SCALE_1_5V                (VREFBUF_CTRL2_VLSEL_1 | VREFBUF_CTRL2_VLSEL_0)

#define VREFBUF_READY_MASK                        (VREFBUF_STS_RDY)

/** VREFBUF_Trimming_Constants **/
#define VREFBUF_TRIMING_2_5V_POS                  ((uint8_t)16U)
#define VREFBUF_TRIMING_2_5V_MASK                 (VREFBUF_TRIM1_2_5V_MASK)
#define VREFBUF_TRIMING_2_0V_POS                  ((uint8_t)22U)
#define VREFBUF_TRIMING_2_0V_MASK                 (VREFBUF_TRIM1_2_048V_MASK)
#define VREFBUF_TRIMING_1_8V_POS                  ((uint8_t)0U)
#define VREFBUF_TRIMING_1_8V_MASK                 (VREFBUF_TRIM1_1_8V_MASK)
#define VREFBUF_TRIMING_1_5V_POS                  ((uint8_t)8U)
#define VREFBUF_TRIMING_1_5V_MASK                 (VREFBUF_TRIM1_1_5V_MASK)
/** VREFBUF_Exported_Functions **/

void VREFBUF_Enable(FunctionalState Cmd);
void VREFBUF_EnableHIM(FunctionalState Cmd);
void VREFBUF_SetVoltageScale(uint32_t Scale);
uint32_t VREFBUF_GetVoltageScale(void);
FlagStatus VREFBUF_IsVREFReady(void);


void VREFBUF_SetTrimming(uint32_t Value);

#ifdef __cplusplus
}
#endif

#endif /*__N32H76X_78X_VREFBUF_H__ */


