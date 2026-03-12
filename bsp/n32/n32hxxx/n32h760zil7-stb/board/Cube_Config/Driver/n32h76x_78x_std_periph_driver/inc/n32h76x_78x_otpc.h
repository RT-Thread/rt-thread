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
 * @file n32h76x_78x_otpc.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#ifndef __N32H76X_78X_OTPC_H__
#define __N32H76X_78X_OTPC_H__

#include "n32h76x_78x.h"

#ifdef __cplusplus
extern "C" {
#endif
    
/** OTPC status**/
typedef enum
{
    OTPC_UNCOMPLETE = 1,
    OTPC_ERR_TIMEOUT,
    OTPC_COMPLETE,
}OTPC_STS;

/** OTPC reload data structure definition **/
typedef struct
{
    uint32_t NRST_IWDG_OTPValue;    /* Corresponding to the value of SYS_CFG_CRST_SWDG_OTP in OTP */
    uint32_t BOR_OTPValue;          /* Corresponding to the value of BOR in OTP */
    uint32_t SEC_JTAG_OTPValue;     /* Corresponding to the value of SEC_JTAG in OTP */
    FlagStatus L2MODE;              /* Chip L2 mode*/
    FlagStatus L1MODE;              /* Chip L2 mode*/
    FlagStatus L0MODE;              /* Chip L2 mode*/
    FlagStatus ROOTMODE;            /* Chip ROOT mode*/
    FlagStatus INITMODE;            /* Chip INIT mode*/
    uint32_t TCM_SIZE_OTPValue;     /* Corresponding to the value of TCM_SIZE in OTP */
} OTPC_DBGReloadValue;    
    

/** OTPC Keys **/
#define OTPC_KEY1               ((uint32_t)0x45670123U)
#define OTPC_KEY2               ((uint32_t)0xCDEF89ABU)    

/** OTPC Operation **/
#define OTPC_CMD_WRITE          (OTPC_CTRL_PRMD)
#define OTPC_CMD_READ           (~OTPC_CTRL_PRMD)
#define OTPC_CMD_LOCK           (OTPC_CTRL_LOCK)   

/** OTPC us Counter Mask**/   
#define OTPC_USC_MASK           (OTPC_USC_VAL)    
    
/** OTPC Flags **/    
#define OTPC_FLAG_BE                                      ((uint32_t)OTPC_STS_BE  )         /* Bit[6] */
#define OTPC_FLAG_OORE                                    ((uint32_t)OTPC_STS_OORE)         /* Bit[5] */
#define OTPC_FLAG_RDPE                                    ((uint32_t)OTPC_STS_RDPE)         /* Bit[4] */
#define OTPC_FLAG_WRPE                                    ((uint32_t)OTPC_STS_WRPE)         /* Bit[3] */
#define OTPC_FLAG_PGE                                     ((uint32_t)OTPC_STS_PGE )         /* Bit[2] */
#define OTPC_FLAG_KEYE                                    ((uint32_t)OTPC_STS_KEYE)         /* Bit[1] */
#define OTPC_FLAG_BUSY                                    ((uint32_t)OTPC_STS_BUSY)         /* Bit[0] */
#define OTPC_ERROR_STS     (OTPC_FLAG_BE | OTPC_FLAG_OORE | OTPC_FLAG_RDPE | OTPC_FLAG_WRPE | OTPC_FLAG_PGE)
#define OTPC_ALLERROR_STS  (OTPC_FLAG_BE | OTPC_FLAG_OORE | OTPC_FLAG_RDPE | OTPC_FLAG_WRPE | OTPC_FLAG_PGE | OTPC_FLAG_KEYE)

/** OTPC Interrupt **/    
#define OTPC_INT_BE                                      ((uint32_t)OTPC_CTRL_BEEN)         /* Bit[6] */
#define OTPC_INT_OORE                                    ((uint32_t)OTPC_CTRL_OOREEN)         /* Bit[5] */
#define OTPC_INT_RDPE                                    ((uint32_t)OTPC_CTRL_RDPEEN)         /* Bit[4] */
#define OTPC_INT_WRPE                                    ((uint32_t)OTPC_CTRL_WRPEEN)         /* Bit[3] */
#define OTPC_INT_PGE                                     ((uint32_t)OTPC_CTRL_PGEEN)         /* Bit[2] */

/** User config register Offset Address **/
#define OTPC_VARIOUS_REG_MASK           ((uint32_t)0x0000FFFFU)
#define OTPC_SEC_JTAG_REG               ((uint32_t)0x00000020U)
#define OTPC_SEC_MODE_REG               ((uint32_t)0x00000028U)
#define OTPC_RDP2_REG                   ((uint32_t)0x00000030U)
#define OTPC_BTM_REG                    ((uint32_t)0x00000038U)
#define OTPC_BOR_REG                    ((uint32_t)0x0000003CU)
#define OTPC_IWDG_REG                   ((uint32_t)0x00000040U)
#define OTPC_TCM_SIZE_REG               ((uint32_t)0x00000044U)
#define OTPC_JTAG_KEY_REG               ((uint32_t)0x00000050U)
#define OTPC_REK_UNIT1_REG              ((uint32_t)0x00000054U)
#define OTPC_REK_UNIT2_REG              ((uint32_t)0x00000058U)
#define OTPC_REK_UNIT3_REG              ((uint32_t)0x0000005CU)
#define OTPC_REK_UNIT4_REG              ((uint32_t)0x00000060U)
#define OTPC_IDK_UNIT1_REG              ((uint32_t)0x00000064U)
#define OTPC_IDK_UNIT2_REG              ((uint32_t)0x00000068U)
#define OTPC_IDK_UNIT3_REG              ((uint32_t)0x0000006CU)
#define OTPC_IDK_UNIT4_REG              ((uint32_t)0x00000070U)
#define OTPC_UMUU_BASE_REG              ((uint32_t)0x00000074U)

/** OTPC CRLD1 register bit offset define **/
#define OTPC_CRLD1_NRIWDG_OFFSET               (REG_BIT16_OFFSET)  /* NRST IWDG OTP Value */
#define OTPC_CRLD1_BOR_OFFSET                  (REG_BIT12_OFFSET)  /* BOR OTP Value */

#define OTPC_TIME_OUT                  ((uint32_t)0xffffffffU)  /* timeout */

/* OTPC User unuse memory */
#define OTPC_UNUSE_STARTADDRESS        ((uint32_t)0x00000500U)  /* OTPC User unuse memory start address */
#define OTPC_UNUSE_PAGESIZE            ((uint32_t)0x00000020U)  /* OTPC User unuse memory page size */

/** OTPC Function **/
void OTPC_Unlock(void);
void OTPC_Lock(void);
FlagStatus OTPC_GetLockStatus(void);
void OTPC_SetUsCount(uint32_t us_count);
FlagStatus OTPC_GetFlagStatus(uint32_t optc_flag);
void OTPC_ClearFlag(uint32_t optc_flag);
FlagStatus OTPC_CheckError(void);
OTPC_STS OTPC_WaitForLastOperation(void);
void OTPC_ConfigInterrupt(uint32_t otpc_int, FunctionalState cmd);
void OTPC_WriteEnable(void);
void OTPC_ReadEnable(void);
void OTPC_SetAddr(uint32_t addr);
void OTPC_SetWriteData(uint32_t data);
OTPC_STS OTPC_ProgramWord(uint32_t addr, uint32_t data);
OTPC_STS OTPC_ReadWord(uint32_t addr, uint32_t *data);
uint32_t OTPC_GetUserCfgVaildNum(uint32_t ConfigUser);
FlagStatus OTPC_CheckUserMemoryUnused(uint32_t addr);
void OTPC_GetReload(OTPC_DBGReloadValue* DBGReloadValue);


#ifdef __cplusplus
}
#endif

#endif /* __N32H76X_78X_OTPC_H__ */
