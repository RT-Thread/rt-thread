/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-15     whj4674672   first version
 */

#include "w25qxx.h"

/*----------------------------------------------------------------------------*/
#define W25QXX_MODE_SPI 0
#define W25QXX_MODE_QPI 1

#define QE_MASK 0x02
#define BUSY_MASK 0x01
/*----------------------------------------------------------------------------*/
uint8_t w25qxx_mode = W25QXX_MODE_SPI;
uint8_t w25qxx_uid[8];
uint8_t w25qxx_buf[4096];
uint16_t w25qxx_mid = W25Q128;

/*----------------------------------------------------------------------------*/
QSPI_HandleTypeDef hqspi;

void MX_QUADSPI_Init(void)
{
    hqspi.Instance            = QUADSPI;
    hqspi.Init.ClockPrescaler = 1;
    hqspi.Init.FifoThreshold  = 4;
    hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
    hqspi.Init.FlashSize      = POSITION_VAL(0X1000000)-1;
    hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_5_CYCLE;
    hqspi.Init.ClockMode      = QSPI_CLOCK_MODE_0;
    hqspi.Init.FlashID        = QSPI_FLASH_ID_1;
    hqspi.Init.DualFlash      = QSPI_DUALFLASH_DISABLE;
    if (HAL_QSPI_Init(&hqspi) != HAL_OK)
    {

    }
}

void W25QXX_Init(void)
{
    MX_QUADSPI_Init();

    W25QXX_ExitQPIMode();
    W25QXX_Reset();
    W25QXX_EnterQPIMode();
}

void W25QXX_ExitQPIMode(void)
{
    QSPI_CommandTypeDef cmd;

    cmd.InstructionMode = QSPI_INSTRUCTION_4_LINES;
    cmd.Instruction = W25X_ExitQPIMode;

    cmd.AddressMode = QSPI_ADDRESS_NONE;
    cmd.AddressSize = QSPI_ADDRESS_24_BITS;
    cmd.Address = 0x00;

    cmd.DataMode = QSPI_DATA_NONE;
    cmd.NbData = 0;

    cmd.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    cmd.AlternateBytesSize = 0;
    cmd.AlternateBytes = 0x00;

    cmd.DummyCycles = 0;

    cmd.DdrMode = QSPI_DDR_MODE_DISABLE;
    cmd.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    cmd.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    HAL_QSPI_Command(&hqspi, &cmd, 100);

    w25qxx_mode = W25QXX_MODE_SPI;
}

void W25QXX_EnterQPIMode(void)
{
    uint8_t dat;

    QSPI_CommandTypeDef cmd;

    dat = W25QXX_ReadSR(2);
    if ((dat & QE_MASK) == 0x00)
    {
        W25QXX_WriteEnable(1);
        dat |= QE_MASK;
        W25QXX_WriteSR(2, dat);
    }

    cmd.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    cmd.Instruction = W25X_EnterQPIMode;

    cmd.AddressMode = QSPI_ADDRESS_NONE;
    cmd.AddressSize = QSPI_ADDRESS_24_BITS;
    cmd.Address = 0x00;

    cmd.DataMode = QSPI_DATA_NONE;
    cmd.NbData = 0;

    cmd.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    cmd.AlternateBytesSize = 0;
    cmd.AlternateBytes = 0x00;

    cmd.DummyCycles = 0;

    cmd.DdrMode = QSPI_DDR_MODE_DISABLE;
    cmd.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    cmd.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    HAL_QSPI_Command(&hqspi, &cmd, 100);

    w25qxx_mode = W25QXX_MODE_QPI;

    cmd.InstructionMode = QSPI_INSTRUCTION_4_LINES;
    cmd.Instruction = W25X_SetReadParameters;
    cmd.DataMode = QSPI_DATA_4_LINES;
    cmd.NbData = 1;
    dat = 0x03 << 4;

    W25QXX_WriteEnable(1);
    if (HAL_QSPI_Command(&hqspi, &cmd, 100) == HAL_OK)
    {
        HAL_QSPI_Transmit(&hqspi, &dat, 100);
    }
}

uint8_t W25QXX_ReadSR(uint8_t srx)
{
    uint8_t dat = 0;

    QSPI_CommandTypeDef cmd;

    if (w25qxx_mode)
    {
        cmd.InstructionMode = QSPI_INSTRUCTION_4_LINES;
        cmd.DataMode = QSPI_DATA_4_LINES;
    }
    else
    {
        cmd.InstructionMode = QSPI_INSTRUCTION_1_LINE;
        cmd.DataMode = QSPI_DATA_1_LINE;
    }

    cmd.AddressMode = QSPI_ADDRESS_NONE;
    cmd.AddressSize = QSPI_ADDRESS_24_BITS;
    cmd.Address = 0x00;

    cmd.NbData = 1;

    cmd.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    cmd.AlternateBytesSize = 0;
    cmd.AlternateBytes = 0x00;

    cmd.DummyCycles = 0;

    cmd.DdrMode = QSPI_DDR_MODE_DISABLE;
    cmd.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    cmd.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    switch (srx)
    {
    case 1:
        cmd.Instruction = W25X_ReadStatusReg1;
        break;
    case 2:
        cmd.Instruction = W25X_ReadStatusReg2;
        break;
    case 3:
        cmd.Instruction = W25X_ReadStatusReg3;
        break;
    default:
        cmd.Instruction = W25X_ReadStatusReg1;
        break;
    }
    if (HAL_QSPI_Command(&hqspi, &cmd, 100) == HAL_OK)
    {
        HAL_QSPI_Receive(&hqspi, &dat, 100);
    }

    return dat;
}

void W25QXX_WriteSR(uint8_t srx, uint8_t dat)
{
    QSPI_CommandTypeDef cmd;

    if (w25qxx_mode)
    {
        cmd.InstructionMode = QSPI_INSTRUCTION_4_LINES;
        cmd.DataMode = QSPI_DATA_4_LINES;
    }
    else
    {
        cmd.InstructionMode = QSPI_INSTRUCTION_1_LINE;
        cmd.DataMode = QSPI_DATA_1_LINE;
    }

    cmd.AddressMode = QSPI_ADDRESS_NONE;
    cmd.AddressSize = QSPI_ADDRESS_24_BITS;
    cmd.Address = 0x00;

    cmd.NbData = 1;

    cmd.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    cmd.AlternateBytesSize = 0;
    cmd.AlternateBytes = 0x00;

    cmd.DummyCycles = 0;

    cmd.DdrMode = QSPI_DDR_MODE_DISABLE;
    cmd.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    cmd.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    switch (srx)
    {
    case 1:
        cmd.Instruction = W25X_WriteStatusReg1;
        break;
    case 2:
        cmd.Instruction = W25X_WriteStatusReg2;
        break;
    case 3:
        cmd.Instruction = W25X_WriteStatusReg3;
        break;
    default:
        cmd.Instruction = W25X_WriteStatusReg1;
        break;
    }
    if (HAL_QSPI_Command(&hqspi, &cmd, 100) == HAL_OK)
    {
        HAL_QSPI_Transmit(&hqspi, &dat, 100);
    }
}

void W25QXX_WriteEnable(uint8_t en)
{
    QSPI_CommandTypeDef cmd;

    if (w25qxx_mode)
    {
        cmd.InstructionMode = QSPI_INSTRUCTION_4_LINES;
    }
    else
    {
        cmd.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    }

    if (en)
    {
        cmd.Instruction = W25X_WriteEnable;
    }
    else
    {
        cmd.Instruction = W25X_WriteDisable;
    }

    cmd.AddressMode = QSPI_ADDRESS_NONE;
    cmd.AddressSize = QSPI_ADDRESS_24_BITS;
    cmd.Address = 0x00;

    cmd.DataMode = QSPI_DATA_NONE;
    cmd.NbData = 0;

    cmd.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    cmd.AlternateBytesSize = 0;
    cmd.AlternateBytes = 0x00;

    cmd.DummyCycles = 0;

    cmd.DdrMode = QSPI_DDR_MODE_DISABLE;
    cmd.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    cmd.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    HAL_QSPI_Command(&hqspi, &cmd, 100);
}

uint16_t W25QXX_MftrDeviceID(void)
{
    uint8_t pData[2];
    uint16_t MftrID = 0xEEEE;

    QSPI_CommandTypeDef cmd;

    if (w25qxx_mode == W25QXX_MODE_QPI)
    {
        cmd.InstructionMode = QSPI_INSTRUCTION_4_LINES;
        cmd.AddressMode = QSPI_ADDRESS_4_LINES;
        cmd.DataMode = QSPI_DATA_4_LINES;
    }
    else
    {
        cmd.InstructionMode = QSPI_INSTRUCTION_1_LINE;
        cmd.AddressMode = QSPI_ADDRESS_1_LINE;
        cmd.DataMode = QSPI_DATA_1_LINE;
    }

    cmd.Instruction = W25X_ManufacturerDeviceID;

    cmd.AddressSize = QSPI_ADDRESS_24_BITS;
    cmd.Address = 0x00;

    cmd.NbData = 2;

    cmd.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    cmd.AlternateBytesSize = 0;
    cmd.AlternateBytes = 0x00;

    cmd.DummyCycles = 0;

    cmd.DdrMode = QSPI_DDR_MODE_DISABLE;
    cmd.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    cmd.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(&hqspi, &cmd, 100) != HAL_OK)
    {
        return MftrID;
    }
    if (HAL_QSPI_Receive(&hqspi, pData, 100) != HAL_OK)
    {
        return MftrID;
    }
    MftrID = (pData[0] << 8) | pData[1];

    return MftrID;
}

uint8_t W25QXX_UniqueID(void)
{
    QSPI_CommandTypeDef cmd;

    if (w25qxx_mode)
    {
        return 1;
    }

    cmd.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    cmd.Instruction = W25X_ReadUniqueID;

    cmd.AddressMode = QSPI_ADDRESS_NONE;
    cmd.AddressSize = QSPI_ADDRESS_24_BITS;
    cmd.Address = 0x00;

    cmd.DataMode = QSPI_DATA_1_LINE;
    cmd.NbData = 8;

    cmd.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    cmd.AlternateBytesSize = 0;
    cmd.AlternateBytes = 0x00;

    cmd.DummyCycles = 32 - 1;

    cmd.DdrMode = QSPI_DDR_MODE_DISABLE;
    cmd.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    cmd.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(&hqspi, &cmd, 100) != HAL_OK)
    {
        return 1;
    }
    if (HAL_QSPI_Receive(&hqspi, w25qxx_uid, 100) != HAL_OK)
    {
        return 1;
    }

    return 0;
}

void W25QXX_Read(uint8_t *pbuf, uint32_t addr, uint16_t size)
{
    QSPI_CommandTypeDef cmd;

    if (w25qxx_mode)
    {
        cmd.InstructionMode = QSPI_INSTRUCTION_4_LINES;
        cmd.AddressMode = QSPI_ADDRESS_4_LINES;
        cmd.DataMode = QSPI_DATA_4_LINES;
    }
    else
    {
        cmd.InstructionMode = QSPI_INSTRUCTION_1_LINE;
        cmd.AddressMode = QSPI_ADDRESS_1_LINE;
        cmd.DataMode = QSPI_DATA_1_LINE;
    }
    cmd.Instruction = W25X_FastRead;

    cmd.AddressSize = QSPI_ADDRESS_24_BITS;
    cmd.Address = addr;

    cmd.NbData = size;

    cmd.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    cmd.AlternateBytesSize = 0;
    cmd.AlternateBytes = 0x00;

    cmd.DummyCycles = 8;

    cmd.DdrMode = QSPI_DDR_MODE_DISABLE;
    cmd.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    cmd.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(&hqspi, &cmd, 100) != HAL_OK)
    {
        return;
    }
    HAL_QSPI_Receive(&hqspi, pbuf, 1000);
}

void W25QXX_PageProgram(uint8_t *pbuf, uint32_t addr, uint16_t size)
{
    QSPI_CommandTypeDef cmd;

    if (size > 256)
        return;

    if (w25qxx_mode)
    {
        cmd.InstructionMode = QSPI_INSTRUCTION_4_LINES;
        cmd.AddressMode = QSPI_ADDRESS_4_LINES;
        cmd.DataMode = QSPI_DATA_4_LINES;
    }
    else
    {
        cmd.InstructionMode = QSPI_INSTRUCTION_1_LINE;
        cmd.AddressMode = QSPI_ADDRESS_1_LINE;
        cmd.DataMode = QSPI_DATA_1_LINE;
    }
    cmd.Instruction = W25X_PageProgram;

    cmd.AddressSize = QSPI_ADDRESS_24_BITS;
    cmd.Address = addr;

    cmd.NbData = size;

    cmd.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    cmd.AlternateBytesSize = 0;
    cmd.AlternateBytes = 0x00;

    cmd.DummyCycles = 0;

    cmd.DdrMode = QSPI_DDR_MODE_DISABLE;
    cmd.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    cmd.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    W25QXX_WriteEnable(1);
    if (HAL_QSPI_Command(&hqspi, &cmd, 100) != HAL_OK)
    {
        return;
    }
    if (HAL_QSPI_Transmit(&hqspi, pbuf, 100) != HAL_OK)
    {
        return;
    }
    W25QXX_WaitBusy();
}

void W25QXX_Write_NoCheck(uint8_t *pbuf, uint32_t addr, uint16_t size)
{
    uint32_t page_rem;
    page_rem = 256 - addr % 256;
    if (size <= page_rem)
    {
        page_rem = size;
    }
    while (1)
    {
        W25QXX_PageProgram(pbuf, addr, page_rem);
        if (size == page_rem)
        {
            break;
        }
        else
        {
            pbuf += page_rem;
            addr += page_rem;

            size -= page_rem;
            if (size > 256)
            {
                page_rem = 256;
            }
            else
            {
                page_rem = size;
            }
        }
    }
}

void W25QXX_Write(uint8_t *pbuf, uint32_t addr, uint16_t size)
{
    uint32_t sec_pos;
    uint32_t sec_off;
    uint32_t sec_rem;
    uint32_t i;
    uint8_t *W25QXX_BUF;

    W25QXX_BUF = w25qxx_buf;
    sec_pos = addr / 4096;
    sec_off = addr % 4096;
    sec_rem = 4096 - sec_off;

    if (size <= sec_rem)
    {
        sec_rem = size;
    }
    while (1)
    {
        W25QXX_Read(W25QXX_BUF, sec_pos * 4096, 4096);
        for (i = 0; i < sec_rem; i++)
        {
            if (W25QXX_BUF[sec_off + i] != 0xFF)
                break;
        }
        if (i < sec_rem)
        {
            W25QXX_SectorErase(sec_pos);
            for (i = 0; i < sec_rem; i++)
            {
                W25QXX_BUF[sec_off + i] = pbuf[i];
            }
            W25QXX_Write_NoCheck(W25QXX_BUF, sec_pos * 4096, 4096);
        }
        else
        {
            W25QXX_Write_NoCheck(pbuf, addr, sec_rem);
        }
        if (size == sec_rem)
        {
            break;
        }
        else
        {
            sec_pos++;
            sec_off = 0;

            pbuf += sec_rem;
            addr += sec_rem;
            size -= sec_rem;
            if (size > 4096)
            {
                sec_rem = 4096;
            }
            else
            {
                sec_rem = size;
            }
        }
    }
}

void W25QXX_ChipErase(void)
{
    QSPI_CommandTypeDef cmd;

    if (w25qxx_mode)
    {
        cmd.InstructionMode = QSPI_INSTRUCTION_4_LINES;
    }
    else
    {
        cmd.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    }
    cmd.Instruction = W25X_ChipErase;

    cmd.AddressMode = QSPI_ADDRESS_NONE;
    cmd.AddressSize = QSPI_ADDRESS_24_BITS;
    cmd.Address = 0x00;

    cmd.DataMode = QSPI_DATA_NONE;
    cmd.NbData = 0;

    cmd.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    cmd.AlternateBytesSize = 0;
    cmd.AlternateBytes = 0x00;

    cmd.DummyCycles = 0;

    cmd.DdrMode = QSPI_DDR_MODE_DISABLE;
    cmd.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    cmd.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    W25QXX_WriteEnable(1);
    W25QXX_WaitBusy();
    HAL_QSPI_Command(&hqspi, &cmd, 100);
    W25QXX_WaitBusy();
}

void W25QXX_SectorErase(uint32_t addr)
{
    QSPI_CommandTypeDef cmd;

    if (w25qxx_mode)
    {
        cmd.InstructionMode = QSPI_INSTRUCTION_4_LINES;
        cmd.AddressMode = QSPI_ADDRESS_4_LINES;
    }
    else
    {
        cmd.InstructionMode = QSPI_INSTRUCTION_1_LINE;
        cmd.AddressMode = QSPI_ADDRESS_1_LINE;
    }
    cmd.Instruction = W25X_SectorErase;

    cmd.AddressSize = QSPI_ADDRESS_24_BITS;
    cmd.Address = addr;

    cmd.DataMode = QSPI_DATA_NONE;
    cmd.NbData = 0;

    cmd.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    cmd.AlternateBytesSize = 0;
    cmd.AlternateBytes = 0x00;

    cmd.DummyCycles = 0;

    cmd.DdrMode = QSPI_DDR_MODE_DISABLE;
    cmd.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    cmd.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    W25QXX_WriteEnable(1);
    W25QXX_WaitBusy();
    HAL_QSPI_Command(&hqspi, &cmd, 100);
    W25QXX_WaitBusy();
}

void W25QXX_WaitBusy(void)
{
    while ((W25QXX_ReadSR(1) & BUSY_MASK) == BUSY_MASK)
        ;
}

void W25QXX_Reset(void)
{
    QSPI_CommandTypeDef cmd;

    if (w25qxx_mode)
    {
        cmd.InstructionMode = QSPI_INSTRUCTION_4_LINES;
    }
    else
    {
        cmd.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    }
    cmd.Instruction = W25X_EnableReset;

    cmd.AddressMode = QSPI_ADDRESS_NONE;
    cmd.AddressSize = QSPI_ADDRESS_24_BITS;
    cmd.Address = 0;

    cmd.DataMode = QSPI_DATA_NONE;
    cmd.NbData = 0;

    cmd.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    cmd.AlternateBytesSize = 0;
    cmd.AlternateBytes = 0x00;

    cmd.DummyCycles = 0;

    cmd.DdrMode = QSPI_DDR_MODE_DISABLE;
    cmd.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    cmd.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    W25QXX_WaitBusy();
    if (HAL_QSPI_Command(&hqspi, &cmd, 100) == HAL_OK)
    {
        cmd.Instruction = W25X_ResetDevice;
        HAL_QSPI_Command(&hqspi, &cmd, 100);
    }
}

void W25Q_Memory_Mapped_Enable(void)
{
  QSPI_CommandTypeDef s_command;
  QSPI_MemoryMappedTypeDef s_mem_mapped_cfg;
 
  /* Configure the command for the read instruction */
  s_command.InstructionMode = QSPI_INSTRUCTION_4_LINES;
  s_command.Instruction = W25X_FastReadQuadIO;
  s_command.AddressMode = QSPI_ADDRESS_4_LINES;
  s_command.AddressSize = QSPI_ADDRESS_24_BITS;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_4_LINES;
  s_command.DummyCycles = 8;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
 
  /* Configure the memory mapped mode */
  s_mem_mapped_cfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE;
  s_mem_mapped_cfg.TimeOutPeriod = 0;
 
  if (HAL_QSPI_MemoryMapped(&hqspi, &s_command, &s_mem_mapped_cfg) != HAL_OK)
  {

  }
}

