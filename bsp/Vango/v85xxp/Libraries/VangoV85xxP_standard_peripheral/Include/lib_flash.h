/**
  ******************************************************************************
  * @file    lib_flash.h 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   FLASH library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_FLASH_H
#define __LIB_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

#define FLASH_BLOCK_0             (0x00000001UL)
#define FLASH_BLOCK_1             (0x00000002UL)
#define FLASH_BLOCK_2             (0x00000004UL)
#define FLASH_BLOCK_3             (0x00000008UL)
#define FLASH_BLOCK_4             (0x00000010UL)
#define FLASH_BLOCK_5             (0x00000020UL)
#define FLASH_BLOCK_6             (0x00000040UL)
#define FLASH_BLOCK_7             (0x00000080UL)
#define FLASH_BLOCK_8             (0x00000100UL)
#define FLASH_BLOCK_9             (0x00000200UL)
#define FLASH_BLOCK_10            (0x00000400UL)
#define FLASH_BLOCK_11            (0x00000800UL)
#define FLASH_BLOCK_12            (0x00001000UL)
#define FLASH_BLOCK_13            (0x00002000UL)
#define FLASH_BLOCK_14            (0x00004000UL)
#define FLASH_BLOCK_15            (0x00008000UL)
#define FLASH_BLOCK_16            (0x00010000UL)
#define FLASH_BLOCK_17            (0x00020000UL)
#define FLASH_BLOCK_18            (0x00040000UL)
#define FLASH_BLOCK_19            (0x00080000UL)
#define FLASH_BLOCK_20            (0x00100000UL)
#define FLASH_BLOCK_21            (0x00200000UL)
#define FLASH_BLOCK_22            (0x00400000UL)
#define FLASH_BLOCK_23            (0x00800000UL)
#define FLASH_BLOCK_24            (0x01000000UL)
#define FLASH_BLOCK_25            (0x02000000UL)
#define FLASH_BLOCK_26            (0x04000000UL)
#define FLASH_BLOCK_27            (0x08000000UL)
#define FLASH_BLOCK_28            (0x10000000UL)
#define FLASH_BLOCK_29            (0x20000000UL)
#define FLASH_BLOCK_30            (0x40000000UL)
#define FLASH_BLOCK_31            (0x80000000UL)
#define FLASH_BLOCK_Msk           (0xFFFFFFFFUL)
#define FLASH_BLOCK_ALL           FLASH_BLOCK_Msk
#define IS_FLASH_RWBLOCK(__BLOCK__)  ((((__BLOCK__) & FLASH_BLOCK_Msk) != 0UL) &&\
                                      (((__BLOCK__) & ~FLASH_BLOCK_Msk) == 0UL))

#define IS_FLASH_BLOCK(__BLOCK__)         (((__BLOCK__) == FLASH_BLOCK_0)      ||\
                                           ((__BLOCK__) == FLASH_BLOCK_1)      ||\
                                           ((__BLOCK__) == FLASH_BLOCK_2)      ||\
                                           ((__BLOCK__) == FLASH_BLOCK_3)    ||\
                                           ((__BLOCK__) == FLASH_BLOCK_4)    ||\
                                           ((__BLOCK__) == FLASH_BLOCK_5)    ||\
                                           ((__BLOCK__) == FLASH_BLOCK_6)    ||\
                                           ((__BLOCK__) == FLASH_BLOCK_7)    ||\
                                           ((__BLOCK__) == FLASH_BLOCK_8)    ||\
                                           ((__BLOCK__) == FLASH_BLOCK_9)    ||\
                                           ((__BLOCK__) == FLASH_BLOCK_10)   ||\
                                           ((__BLOCK__) == FLASH_BLOCK_11)   ||\
                                           ((__BLOCK__) == FLASH_BLOCK_12)   ||\
                                           ((__BLOCK__) == FLASH_BLOCK_13)   ||\
                                           ((__BLOCK__) == FLASH_BLOCK_14)   ||\
                                           ((__BLOCK__) == FLASH_BLOCK_15)   ||\
                                           ((__BLOCK__) == FLASH_BLOCK_16)   ||\
                                           ((__BLOCK__) == FLASH_BLOCK_17)   ||\
                                           ((__BLOCK__) == FLASH_BLOCK_18)   ||\
                                           ((__BLOCK__) == FLASH_BLOCK_19)   ||\
                                           ((__BLOCK__) == FLASH_BLOCK_20)   ||\
                                           ((__BLOCK__) == FLASH_BLOCK_21)   ||\
                                           ((__BLOCK__) == FLASH_BLOCK_22)   ||\
                                           ((__BLOCK__) == FLASH_BLOCK_23)   ||\
                                           ((__BLOCK__) == FLASH_BLOCK_24)   ||\
                                           ((__BLOCK__) == FLASH_BLOCK_25)   ||\
                                           ((__BLOCK__) == FLASH_BLOCK_26)   ||\
                                           ((__BLOCK__) == FLASH_BLOCK_27)   ||\
                                           ((__BLOCK__) == FLASH_BLOCK_28)   ||\
                                           ((__BLOCK__) == FLASH_BLOCK_29)   ||\
                                           ((__BLOCK__) == FLASH_BLOCK_30)   ||\
                                           ((__BLOCK__) == FLASH_BLOCK_31))

#define FLASH_READ                    (0)
#define FLASH_WRITE                   (1)
#define IS_FLASH_OPERATION(__OPERATION__)    (((__OPERATION__) == FLASH_READ)  ||\
                                              ((__OPERATION__) == FLASH_WRITE))

/**************  Bits definition for FLASH_CTRL register     ******************/
#define FLASH_CTRL_CSMODE_DISABLE     (0x0U << FLASH_CTRL_CSMODE_Pos)          /*!< 0x00000000 */
#define FLASH_CTRL_CSMODE_ALWAYSON    (0x1U << FLASH_CTRL_CSMODE_Pos)          /*!< 0x00000001 */
#define FLASH_CTRL_CSMODE_TIM2OV      (0x2U << FLASH_CTRL_CSMODE_Pos)          /*!< 0x00000002 */
#define FLASH_CTRL_CSMODE_RTC         (0x3U << FLASH_CTRL_CSMODE_Pos)          /*!< 0x00000003 */

//CSMode
#define FLASH_CSMODE_DISABLE        FLASH_CTRL_CSMODE_DISABLE
#define FLASH_CSMODE_ALWAYSON       FLASH_CTRL_CSMODE_ALWAYSON
#define FLASH_CSMODE_TMR2OF         FLASH_CTRL_CSMODE_TIM2OV
#define FLASH_CSMODE_RTC            FLASH_CTRL_CSMODE_RTC
#define IS_FLASH_CSMODE(__CSMODE__)  (((__CSMODE__) == FLASH_CSMODE_DISABLE)  ||\
                                      ((__CSMODE__) == FLASH_CSMODE_ALWAYSON) ||\
                                      ((__CSMODE__) == FLASH_CSMODE_TMR2OF)   ||\
                                      ((__CSMODE__) == FLASH_CSMODE_RTC))

//INT
#define FLASH_INT_CS                FLASH_CTRL_CSINTEN
#define IS_FLASH_INT(__INT__)  ((__INT__) == FLASH_INT_CS)

//WriteStatus
#define FLASH_WSTA_BUSY         0
#define FLASH_WRITE_FINISH      1
#define FLASH_WSTA_FINISH       FLASH_WRITE_FINISH

#define IS_FLASH_ADDRESS(__ADDRESS__) ((__ADDRESS__) < 0x80000UL)

#define IS_FLASH_ADRRW(__ADDRW__)  (((__ADDRW__) < 0x80000UL) &&\
                                    (((__ADDRW__) & 0x3U) == 0U))

#define IS_FLASH_ADRRHW(__ADDRHW__)  (((__ADDRHW__) < 0x80000UL) &&\
                                      (((__ADDRHW__) & 0x1U) == 0U))

#define IS_FLASH_CHECKSUMADDR(__ADDRESS1__,__ADDRESS2__) (((__ADDRESS1__) < 0x80000) && ((__ADDRESS2__) < 0x80000) && ((__ADDRESS1__) < (__ADDRESS2__)))

/* Exported Functions ------------------------------------------------------- */

void FLASH_Init(uint32_t CSMode);
void FLASH_INTConfig(uint32_t IntMask, uint32_t NewState);
void FLASH_CycleInit(void);
void FLASH_SectorErase(uint32_t SectorAddr);
void FLASH_ChipErase(void);
void FLASH_ProgramWord(uint32_t Addr, uint32_t *WordBuffer, uint32_t Length);
void FLASH_ProgramHWord(uint32_t Addr, uint16_t *HWordBuffer, uint32_t Length);
void FLASH_ProgramByte(uint32_t Addr, uint8_t *ByteBuffer, uint32_t Length);
void FLASH_SetReadProtection(uint32_t Block);
void FLASH_WriteProtection(uint32_t Block, uint32_t NewState);
void FLASH_ICEProtection(uint32_t NewState);
uint8_t FLASH_GetProtectionStatus(uint32_t Block, uint32_t Operation);
uint32_t FLASH_GetAllProtectionStatus(uint32_t Operation);
void FLASH_SetCheckSumRange(uint32_t AddrStart, uint32_t AddrEnd);
void FLASH_SetCheckSumCompValue(uint32_t Checksum);
uint32_t FLASH_GetCheckSum(void);
uint8_t FLASH_GetINTStatus(uint32_t IntMask);
void FLASH_ClearINTStatus(uint32_t IntMask);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_FLASH_H */

/*********************************** END OF FILE ******************************/
