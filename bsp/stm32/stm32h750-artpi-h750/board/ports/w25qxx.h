/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-15     whj4674672   first version
 */

#ifndef __W25QXX_H
#define __W25QXX_H

#include "board.h"
/*----------------------------------------------------------------------------*/
#define W25Q80 0xEF13
#define W25Q16 0xEF14
#define W25Q32 0xEF15
#define W25Q64 0xEF16
#define W25Q128 0xEF17
#define W25Q256 0xEF18

#define W25X_WriteEnable 0x06
#define W25X_VolatileSRWriteEnable 0x50
#define W25X_WriteDisable 0x04

#define W25X_ReleasePowerDownID 0xAB
#define W25X_ManufacturerDeviceID 0x90
#define W25X_JedecID 0x9F
#define W25X_ReadUniqueID 0x4B      //SPI
#define W25X_SetReadParameters 0xC0 //QPI

#define W25X_ReadData 0x03 //SPI
#define W25X_FastRead 0x0B
#define W25X_BurstReadWithWrap 0x0C //QPI
#define W25X_FastReadQuadIO 0xEB    //QPI

#define W25X_PageProgram 0x02
#define W25X_SectorErase 0x20  //4KB
#define W25X_BlockErase32 0x52 //32KB
#define W25X_BlockErase64 0xD8 //64KB
#define W25X_ChipErase 0xC7    //0x60

#define W25X_ReadStatusReg1 0x05
#define W25X_ReadStatusReg2 0x35
#define W25X_ReadStatusReg3 0x15
#define W25X_WriteStatusReg1 0x01 // Reg1 Reg2
#define W25X_WriteStatusReg2 0x01 //0x31
#define W25X_WriteStatusReg3 0x01 //0x11

#define W25X_ReadSFDPReg 0x5A      //SPI
#define W25X_EraseSecurityReg 0x44 //SPI
#define W25X_ProgSecurityReg 0x42  //SPI
#define W25X_ReadSecurityReg 0x48  //SPI

#define W25X_GlobalBlockLock 0x7E
#define W25X_GlobalBlockUnlock 0x98
#define W25X_ReadBlockLock 0x3D
#define W25X_IndividualBlockLock 0x36
#define W25X_IndividualBlockUnlock 0x39

#define W25X_EraseProgramSuspend 0x75
#define W25X_EraseProgramResume 0x7A

#define W25X_PowerDown 0xB9

#define W25X_EnterQPIMode 0x38 //SPI
#define W25X_EnableReset 0x66
#define W25X_ResetDevice 0x99
#define W25X_ExitQPIMode 0xFF //QPI

/*----------------------------------------------------------------------------*/
extern uint16_t w25qxx_mid;
/*----------------------------------------------------------------------------*/
void W25QXX_Init(void);
void W25QXX_ExitQPIMode(void);
void W25QXX_EnterQPIMode(void);
uint8_t W25QXX_ReadSR(uint8_t srx);
void W25QXX_WriteSR(uint8_t srx, uint8_t dat);
void W25QXX_WriteEnable(uint8_t en);

uint16_t W25QXX_MftrDeviceID(void);
uint8_t W25QXX_UniqueID(void);

void W25QXX_Write_NoCheck(uint8_t *pbuf, uint32_t addr, uint16_t size);
void W25QXX_Read(uint8_t *pbuf, uint32_t addr, uint16_t size);
void W25QXX_PageProgram(uint8_t *pbuf, uint32_t addr, uint16_t size);
void W25QXX_Write(uint8_t *pbuf, uint32_t addr, uint16_t size);
void W25QXX_ChipErase(void);
void W25QXX_SectorErase(uint32_t addr);
void W25QXX_WaitBusy(void);
void W25QXX_Reset(void);

void W25Q_Memory_Mapped_Enable(void);
void MX_QUADSPI_Init(void);
#endif

