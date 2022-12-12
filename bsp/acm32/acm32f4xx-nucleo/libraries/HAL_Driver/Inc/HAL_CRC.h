/*
  ******************************************************************************
  * @file    HAL_CRC.h
  * @version V1.0.0
  * @date    2021
  * @brief   Header file of CRC HAL module.
  ******************************************************************************
*/
#ifndef __HAL_CRC_H__
#define __HAL_CRC_H__
#include  "ACM32Fxx_HAL.h"

/** @defgroup CRC POLY Reverse
  * @{
  */ 
 #define CRC_POLY_REV_EN                    (0x00000400U)    /*!< Poly Reverse Enable */
 #define CRC_POLY_REV_DIS                   (0x00000000U)    /*!< Poly Reverse Disable */
/**
  * @}
  */

/** @defgroup CRC OUTXOR Reverse
  * @{
  */ 
 #define CRC_OUTXOR_REV_EN                   (0x00000200U)    /*!< OUTXOR Reverse Enable */
 #define CRC_OUTXOR_REV_DIS                  (0x00000000U)    /*!< OUTXOR Reverse Disable */
/**
  * @}
  */
 
/** @defgroup CRC INIT Reverse
  * @{
  */ 
 #define CRC_INIT_REV_EN                     (0x00000100U)    /*!< INIT Reverse Enable */
 #define CRC_INIT_REV_DIS                    (0x00000000U)    /*!< INIT Reverse Disable */
/**
  * @}
  */
  
/** @defgroup CRC RSLT Reverse
  * @{
  */ 
 #define CRC_RSLT_REV_EN                     (0x00000080U)    /*!< RSLT Reverse Enable */
 #define CRC_RSLT_REV_DIS                    (0x00000000U)    /*!< RSLT Reverse Disable */
/**
  * @}
  */

/** @defgroup CRC DATA Reverse
  * @{
  */ 
 #define CRC_DATA_REV_DISABLE                (0x00000000U)    /*!< DATA Reverse Disable */
 #define CRC_DATA_REV_BY_BYTE                (0x00000020U)    /*!< DATA Reverse By Byte */
 #define CRC_DATA_REV_BY_HALFWORD            (0x00000040U)    /*!< DATA Reverse By HalfWord */
 #define CRC_DATA_REV_BY_WORD                (0x00000060U)    /*!< DATA Reverse By Word */
/**
  * @}
  */

/** @defgroup CRC Poly Len
  * @{
  */ 
 #define CRC_POLTY_LEN_32                    (0x00000000U)    /*!< POLY len = 32bit */
 #define CRC_POLTY_LEN_16                    (0x00000008U)    /*!< POLY len = 16bit */
 #define CRC_POLTY_LEN_8                     (0x00000010U)    /*!< POLY len = 8bit  */
 #define CRC_POLTY_LEN_7                     (0x00000018U)    /*!< POLY len = 7bit  */
/**
  * @}
  */

/** @defgroup CRC Data Len
  * @{
  */ 
 #define CRC_DATA_LEN_1B                    (0x00000000U)    /*!< DATA len = 1 Byte */
 #define CRC_DATA_LEN_2B                    (0x00000002U)    /*!< DATA len = 2 Byte */
 #define CRC_DATA_LEN_3B                    (0x00000004U)    /*!< DATA len = 3 Byte */
 #define CRC_DATA_LEN_4B                    (0x00000006U)    /*!< DATA len = 4 Byte */
/**
  * @}
  */

/** @defgroup CRC RST
  * @{
  */ 
 #define CRC_RST_EN                          (0x00000001U)    /*!< RST CRC_DATA To CRC_INIT */
 #define CRC_RST_DIS                         (0x00000000U)    /*!< RST CRC_DATA To CRC_INIT */

/**
  * @}
  */
  
/*
 * @brief CRC Init Structure definition
 */
typedef struct
{
    uint32_t PolyRev;                  /*!< Specifies if the Poly is reversed in CRC
                                            This parameter can be a value of @ref CRC POLY Reverse. */
    uint32_t OutxorRev;                /*!< Specifies if the Outxor is reversed in CRC
                                            This parameter can be a value of @ref CRC OUTXOR Reverse. */
    uint32_t InitRev;                  /*!< Specifies if the Init is reversed in CRC
                                            This parameter can be a value of @ref CRC INIT Reverse. */
    uint32_t RsltRev;                  /*!< Specifies if the Result is reversed in CRC
                                            This parameter can be a value of @ref CRC RSLT Reverse. */
    uint32_t DataRev;                  /*!< Specifies if the Data is reversed in CRC
                                            This parameter can be a value of @ref CRC DATA Reverse. */
    uint32_t PolyLen;                  /*!< Specifies the Poly Len in CRC
                                            This parameter can be a value of @ref CRC Poly Len. */
    uint32_t DataLen;                  /*!< Specifies the Data Len in CRC
                                            This parameter can be a value of @ref CRC Data Len. */
    uint32_t RST;                      /*!< Specifies if CRC is reset
                                            This parameter can be a value of @ref CRC RST. */
	
    uint32_t InitData;                 /*!< This member configures the InitData. */
	
    uint32_t OutXorData;               /*!< This member configures the OutXorData. */
	
    uint32_t PolyData;                 /*!< This member configures the PolyData. */
	
    uint32_t FData;                    /*!< This member configures the FData. */
	
}CRC_InitTypeDef;

/*
 * @brief  UART handle Structure definition
 */
typedef struct
{
    CRC_TypeDef           *Instance;                /*!< CRC registers base address  */

    CRC_InitTypeDef        Init;                    /*!< CRC calculate parameters  */
	
    uint8_t* CRC_Data_Buff;                         /*!< CRC databuff base address */
	
    uint32_t CRC_Data_Len;                          /*!< amount of CRC data to be calculated */
    
}CRC_HandleTypeDef;  
  
 
/*********************************************************************************
* Function    : HAL_CRC_Calculate
* Description : Calculate the crc calue of input data.
* Input       : hcrc: CRC handle.
* Output      : CRC value
* Author      : cl                        Data : 2021 
**********************************************************************************/
uint32_t HAL_CRC_Calculate(CRC_HandleTypeDef *hcrc);  


#endif




