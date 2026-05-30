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
 * @file n32h76x_78x_eccmon.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H76x_78x_ECCMON_H__
#define __N32H76x_78x_ECCMON_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

#include "n32h76x_78x.h"
#include "n32h76x_78x_rcc.h"


/** ECCMON Init Structure definition **/
typedef struct
{
    uint32_t MemType; /*Specifies ECCMON monit memory ,can |(or) operation */
    uint32_t CaptureSelect;/*Specifies ECC error event capture selection*/
    uint32_t ErrFlagOut;/*Specifies which error flag out  to FLAG_En_OT port,as system fault events*/																		 
} ECCMON_InitType;

typedef struct
{
    ECCMON_TypeDef * MonitorUnit;/*ECCMON1P1,ECCMON1P2.......ECCMON3*/
    uint32_t MonitorIndex;/*min:0,max:5*/
}ECCMON_MonitorType;
#define  ECCMON_GROUP_REG_ADDR_GAP      (0x05UL)   //5 registers
#define  AXI_SRAM1_BASE_ADDR            ((uint32_t)0x24000000)
#define  AXI_SRAM2_BASE_ADDR            ((uint32_t)0x24020000)
#define  AXI_SRAM3_BASE_ADDR            ((uint32_t)0x240A0000)
#define  AHB_SRAM1_BASE_ADDR            ((uint32_t)0x30000000)
#define  AHB_SRAM2_BASE_ADDR            ((uint32_t)0x30020000)
#define  AHB_SRAM3_BASE_ADDR            ((uint32_t)0x30040000)
#define  AHB_SRAM4_BASE_ADDR            ((uint32_t)0x30048000)
#define  AHB_SRAM5_BANK1_BASE_ADDR      ((uint32_t)0x30050000)
#define  AHB_SRAM5_BANK2_BASE_ADDR      ((uint32_t)0x30054000)
#define  ITCM_BASE_ADDR                 ((uint32_t)0x00000000)
#define  DTCM_BASE_ADDR                 ((uint32_t)0x20000000)
#define  BACKUP_SRAM_BASE_ADDR          ((uint32_t)0x38000000)
/** ECCMON Memory Type  definition **/
#define  ECCMON_NONE_SRAM               ((uint32_t)0x0000)
#define  ECCMON_AXI_SRAM1               ((uint32_t)0x0001)      //corresponding ECCMON1P1,n=1
#define  ECCMON_AXI_SRAM2               ((uint32_t)0x0002)      //corresponding ECCMON1P2,n=0
#define  ECCMON_AXI_SRAM3               ((uint32_t)0x0004)      //corresponding ECCMON1P2,n=1
#define  ECCMON_ITCM                    ((uint32_t)0x0008)      //corresponding ECCMON1P3,n=0
#define  ECCMON_D0TCM                   ((uint32_t)0x0010)      //corresponding ECCMON1P4,n=0
#define  ECCMON_D1TCM                   ((uint32_t)0x0020)      //corresponding ECCMON1P4,n=1
#define  ECCMON_AHB_SRAM1               ((uint32_t)0x0040)      //corresponding ECCMON2,n=0
#define  ECCMON_AHB_SRAM2               ((uint32_t)0x0080)      //corresponding ECCMON2,n=1
#define  ECCMON_AHB_SRAM3               ((uint32_t)0x0100)      //corresponding ECCMON2,n=2
#define  ECCMON_AHB_SRAM4               ((uint32_t)0x0200)      //corresponding ECCMON2,n=3
#define  ECCMON_AHB_SRAM5_BANK1         ((uint32_t)0x0400)      //corresponding ECCMON2,n=4
#define  ECCMON_AHB_SRAM5_BANK2         ((uint32_t)0x0800)      //corresponding ECCMON2,n=5
#define  ECCMON_BACKUP_SRAM             ((uint32_t)0x1000)      //corresponding ECCMON3,n=0
/**ECCMON Error Flag Out Type definiton**/
#define  ECCMON_NO_ERROR_FLAG_OUT       ((uint32_t)0x00u)
#define  ECCMON_1BIT_ERROR_FLAG_OUT     ((uint32_t)0x01u)
#define  ECCMON_2BIT_ERROR_FLAG_OUT     ((uint32_t)0x02u)
#define  ECCMON_1_2BIT_ERROR_FLAG_OUT   ((uint32_t)0x03u)
/**ECCMON Capture Selection**/
#define  ECCMON_CAPTURE_1_2BIT_ERROR    ((uint32_t)0x00u)
#define  ECCMON_CAPTURE_1BIT_ERROR      ((uint32_t)ECCMON_EINJ_ECSEL1_0)
#define  ECCMON_CAPTURE_2BIT_ERROR      ((uint32_t)ECCMON_EINJ_ECSEL1_1)
#define  ECCMON_CAPTURE_NONE_ERROR      ((uint32_t)ECCMON_EINJ_ECSEL1_0|ECCMON_EINJ_ECSEL1_1)


/**ECCMON interrupt Type definiton**/
#define  ECCMON_1BIT_ERROR_INT          ((uint32_t)0x01u)
#define  ECCMON_2BIT_ERROR_INT          ((uint32_t)0x02u)
#define  ECCMON_1_2BIT_ERROR_INT        ((uint32_t)0x03u)

/**ECCMON Interrupt  definiton**/
#define  ECCMON_FLAG_E1DCIFW            (ECCMON_INTF1_E1DCIFW)
#define  ECCMON_FLAG_E2DCIFW            (ECCMON_INTF1_E2DCIFW)
#define  ECCMON_FLAG_E1DCIFR            (ECCMON_INTF1_E1DCIFR)
#define  ECCMON_FLAG_E2DCIFR            (ECCMON_INTF1_E2DCIFR)

#define  ECCMON_INT_E1DCIFW             (ECCMON_INTF1_E1DCIFW)
#define  ECCMON_INT_E2DCIFW             (ECCMON_INTF1_E2DCIFW)
#define  ECCMON_INT_E1DCIFR             (ECCMON_INTF1_E1DCIFR)
#define  ECCMON_INT_E2DCIFR             (ECCMON_INTF1_E2DCIFR)
/**ECCMON error context flag define */
#define  ECCMON_ERR_CONTEXT_FLAG_E2EAD  (ECCMON_FEADR1_E2EAD)
#define  ECCMON_ERR_CONTEXT_FLAG_E1EAD  (ECCMON_FEADR1_E1EAD)

/**ECCMON Inject type**/ 
#define  ECCMON_NO_INJECT               ((uint32_t)0x00u)
#define  ECCMON_INJECT_1BIT             (ECCMON_EINJ_ERICTR1_0)
#define  ECCMON_INJECT_2BIT             (ECCMON_EINJ_ERICTR1_0|ECCMON_EINJ_ERICTR1_1)
#define  ECCMON_INJECT_MASK             (ECCMON_EINJ_ERICTR1_0|ECCMON_EINJ_ERICTR1_1)

void ECCMON_StructInit(ECCMON_InitType *ECCMON_InitStruct);
void ECCMON_Init(ECCMON_InitType *ECCMON_InitStruct);
void ECCMON_ConfigInt(uint32_t ECCMON_MemType, uint32_t ECCMON_IntType);
void ECCMON_InjectError(uint32_t ECCMON_MemType, uint32_t ECCMON_InjectType);
void ECCMON_SetBypassTempRegister(uint32_t ECCMON_MemType, FunctionalState Cmd);
void ECCMON_SetWriteOn2Bit(uint32_t ECCMON_MemType, FunctionalState Cmd);
void ECCMON_Enable(uint32_t ECCMON_MemType,FunctionalState Cmd);
void ECCMON_EnableClk(void);
uint32_t ECCMON_GetFailAddress(uint32_t ECCMON_MemType);
uint32_t ECCMON_GetFailDataLow(uint32_t ECCMON_MemType);
uint32_t ECCMON_GetFailDataHigh(uint32_t ECCMON_MemType);
uint32_t ECCMON_GetFailErrorCode(uint32_t ECCMON_MemType);
FlagStatus ECCMON_GetErrorContextFlagStatus(uint32_t ECCMON_MemType, uint32_t ECCMON_ERR_CONTEXT_FLAG);
void ECCMON_ClrErrorContextFlag(uint32_t ECCMON_MemType, uint32_t ECCMON_ERR_CONTEXT_FLAG);

FlagStatus ECCMON_GetFlagStatus(uint32_t ECCMON_MemType, uint32_t ECCMON_FLAG);
void ECCMON_ClrFlag(uint32_t ECCMON_MemType, uint32_t ECCMON_FLAG);
INTStatus ECCMON_GetIntStatus(uint32_t ECCMON_MemType, uint32_t ECCMON_INT);
#ifdef __cplusplus
}
#endif

#endif /* __n32h76x_78x_CRC_H__ */


