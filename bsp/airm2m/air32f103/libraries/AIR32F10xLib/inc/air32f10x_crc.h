/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AIR32F10x_CRC_H
#define __AIR32F10x_CRC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "air32f10x.h"

/** @addtogroup air32f10x_StdPeriph_Driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
#define CRC_32_BYTE_NUM         ((uint32_t)0xC0)
#define CRC_16_BYTE_NUM         ((uint32_t)0x40)
#define XOR_OUT_SEL_SET         ((uint32_t)0x20)
#define REV_OUT_SEL_SET         ((uint32_t)0x10)
#define REV_IN_SEL_SET          ((uint32_t)0x04)
#define TYPE_SEL_SET            ((uint32_t)0x02)
#define POLY_SEL_SET            ((uint32_t)0x01)

#define CRC_INIT_VALUE_0        ((uint32_t)0)
#define CRC16_INIT_VALUE_FF     ((uint32_t)0xffff)
#define CRC32_INIT_VALUE_FF     ((uint32_t)0xffffffff)

typedef enum
{
    CRC_16_IBM = 0x01,
    CRC_16_MAXIM = 0x02,
    CRC_16_USB   = 0x03,
    CRC_16_MODBUS= 0x04,
    CRC_16_CCITT = 0x05,
    CRC_16_CCITT_FALSE = 0x06,
    CRC_16_X25    = 0x07,
    CRC_16_XMODEM = 0x08,
    CRC_32        = 0x09,
    CRC_32_MPEG_2 = 0x0A
}CRC_Param_TypeDef;

typedef enum
{
    CRC_Poly_16_1021 = 0x01,
    CRC_Poly_16_8005 = 0x02,
    CRC_Poly_32_04C11DB7 = 0x03
}CRC_Poly_TypeDef;


void CRC_ResetDR(void);
uint32_t CRC_CalcCRC(uint32_t Data);
uint32_t CRC_CalcBlockCRC(uint32_t Type,uint32_t pBuffer[], uint32_t BufferLength);
uint32_t CRC_GetCRC(void);
void CRC_SetIDRegister(uint8_t IDValue);
uint8_t CRC_GetIDRegister(void);

#ifdef __cplusplus
}
#endif

#endif /* __AIR32F10x_CRC_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

