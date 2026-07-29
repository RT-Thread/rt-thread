/**
  ******************************************************************************
  * @file    lib_flash.h 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
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

//CSMode
#define FLASH_CSMODE_DISABLE        FLASH_CTRL_CSMODE_DISABLE
#define FLASH_CSMODE_ALWAYSON       FLASH_CTRL_CSMODE_ALWAYSON
#define FLASH_CSMODE_TIM2OF         FLASH_CTRL_CSMODE_TIM2OV
#define FLASH_CSMODE_RTC            FLASH_CTRL_CSMODE_RTC
#define IS_FLASH_CSMODE(__CSMODE__)  (((__CSMODE__) == FLASH_CSMODE_DISABLE)  ||\
                                      ((__CSMODE__) == FLASH_CSMODE_ALWAYSON) ||\
                                      ((__CSMODE__) == FLASH_CSMODE_TIM2OF)   ||\
                                      ((__CSMODE__) == FLASH_CSMODE_RTC))

//INT
#define FLASH_INT_CS                FLASH_CTRL_CSINTEN
#define IS_FLASH_INT(__INT__)  ((__INT__) == FLASH_INT_CS)

//WriteStatus
#define FLASH_WSTA_BUSY         0
#define FLASH_WRITE_FINISH      1
#define FLASH_WSTA_FINISH       FLASH_WRITE_FINISH

#define IS_FLASH_ADDRESS(__ADDRESS__) ((__ADDRESS__) < 0x40000UL)

#define IS_FLASH_ADRRW(__ADDRW__)  (((__ADDRW__) < 0x40000UL) &&\
                                    (((__ADDRW__) & 0x3U) == 0U))

#define IS_FLASH_ADRRHW(__ADDRHW__)  (((__ADDRHW__) < 0x40000UL) &&\
                                      (((__ADDRHW__) & 0x1U) == 0U))

#define IS_FLASH_CHECKSUMADDR(__ADDRESS1__,__ADDRESS2__) (((__ADDRESS1__) < 0x40000) && ((__ADDRESS2__) < 0x40000) && ((__ADDRESS1__) < (__ADDRESS2__)))

/* Exported Functions ------------------------------------------------------- */

void FLASH_Init(uint32_t CSMode);
void FLASH_INTConfig(uint32_t IntMask, uint32_t NewState);
void FLASH_CycleInit(void);
void FLASH_SectorErase(uint32_t SectorAddr);
void FLASH_ProgramWord(uint32_t Addr, uint32_t *WordBuffer, uint32_t Length);
void FLASH_ProgramHWord(uint32_t Addr, uint16_t *HWordBuffer, uint32_t Length);
void FLASH_ProgramByte(uint32_t Addr, uint8_t *ByteBuffer, uint32_t Length);
uint32_t FLASH_GetWriteStatus(void);
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
