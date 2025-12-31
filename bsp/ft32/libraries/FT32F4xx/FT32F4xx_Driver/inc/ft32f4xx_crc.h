/**
  ******************************************************************************
  * @file               ft32f4xx_crc.h
  * @author             FMD AE
  * @brief              This file contains all the functions prototypes for
  *               the CRC firmware library.
  * @version            V1.0.0
  * @date                   2025-03-25
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_CRC_H
#define __FT32F4XX_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

/*!< Includes ----------------------------------------------------------------*/
#include "ft32f4xx.h"


/** @addtogroup CRC
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup CRC_Exported_Constants I2S Exported Constants
  * @{
  */

/** @defgroup CRC_ReverseInputData
  * @{
  */
#define CRC_ReverseInputData_No             ((uint32_t)0x00000000) /*!< No reverse operation of Input Data */
#define CRC_ReverseInputData_8bits          CRC_CR_REV_IN_0        /*!< Reverse operation of Input Data on 8 bits */
#define CRC_ReverseInputData_16bits         CRC_CR_REV_IN_1        /*!< Reverse operation of Input Data on 16 bits */
#define CRC_ReverseInputData_32bits         CRC_CR_REV_IN          /*!< Reverse operation of Input Data on 32 bits */

#define IS_CRC_REVERSE_INPUT_DATA(DATA) (((DATA) == CRC_ReverseInputData_No)     || \
                                         ((DATA) == CRC_ReverseInputData_8bits)  || \
                                         ((DATA) == CRC_ReverseInputData_16bits) || \
                                         ((DATA) == CRC_ReverseInputData_32bits))

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */
/** @addtogroup CRC_Exported_Functions
  * @{
  */
/* Configuration of the CRC computation unit **********************************/
void CRC_DeInit(void);
void CRC_ResetDR(void);
void CRC_ReverseInputDataSelect(uint32_t CRC_ReverseInputData);
void CRC_ReverseOutputDataCmd(FunctionalState NewState);
void CRC_SetINITRegister(uint32_t CRC_InitValue);
void CRC_SetCRegister(uint32_t CRC_CRValue);

/* CRC computation ************************************************************/
uint32_t CRC_CalcCRC(uint32_t CRC_Data);
uint32_t CRC_CalcCRC16bits(uint16_t CRC_Data);
uint32_t CRC_CalcCRC8bits(uint8_t CRC_Data);
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength);
uint32_t CRC_GetCRC(void);

/* Independent register (IDR) access (write/read) *****************************/
void CRC_SetIDRegister(uint8_t CRC_IDValue);
uint8_t CRC_GetIDRegister(void);

/* Control register (CR) access (read) *****************************/
uint32_t CRC_GetCRegister(void);

/* Initial value register (INIT) access (read) *****************************/
uint32_t CRC_GetINITRegister(void);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __FT32F4XX_CRC_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
