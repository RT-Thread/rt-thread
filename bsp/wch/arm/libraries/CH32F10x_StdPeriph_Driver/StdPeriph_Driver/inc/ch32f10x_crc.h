/***************COPYRIGHT(C)  2019 WCH. A11 rights reserved*********************
* File Name          : ch32f10x_crc.h
* Author             : WCH
* Version            : V1.0.0
* Date               : 2019/10/15
* Description        : This file contains all the functions prototypes for the 
*                      CRC firmware library.
*******************************************************************************/ 
#ifndef __CH32F10x_CRC_H
#define __CH32F10x_CRC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "ch32f10x.h"

	 
void CRC_ResetDR(void);
uint32_t CRC_CalcCRC(uint32_t Data);
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength);
uint32_t CRC_GetCRC(void);
void CRC_SetIDRegister(uint8_t IDValue);
uint8_t CRC_GetIDRegister(void);

#ifdef __cplusplus
}
#endif

#endif /* __CH32F10x_CRC_H */





