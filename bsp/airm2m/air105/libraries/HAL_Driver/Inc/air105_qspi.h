/*
 * Copyright (c) 2022 OpenLuat & AirM2M
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#ifndef AIRMCU_FLASH
#define AIRMCU_FLASH

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "air105.h"


/* Size of the flash */
#define X25Q_PAGE_SIZE                      0x100

// Identification Operations
/***Command Definitions***/

// Program Operations
#define PAGE_PROG_CMD                       0x02
#define QUAD_INPUT_PAGE_PROG_CMD            0x32


// Erase Operations
#define SECTOR_ERASE_CMD                    0x20
#define CHIP_ERASE_CMD                      0xC7

#define PROG_ERASE_RESUME_CMD               0x7A
#define PROG_ERASE_SUSPEND_CMD              0x75

#define SET_BURST_WITH_WRAP                 0x77
#define RELEASE_FROM_DEEP_POWER_DOWN        0xAB
#define DEEP_POWER_DOWN                     0xB9

/***End Cmd***/


#define QSPI_DEVICE_PARA_SAMPLE_DLY_Pos       15
#define QSPI_DEVICE_PARA_SAMPLE_PHA_Pos       14
#define QSPI_DEVICE_PARA_PROTOCOL_Pos         8
#define QSPI_DEVICE_PARA_DUMMY_CYCLE_Pos      4


#define ROM_QSPI_Init                        (*((void (*)(QSPI_InitTypeDef *))(*(uint32_t *)0x8010)))
#define ROM_QSPI_ReadID                      (*((uint32_t (*)(QSPI_CommandTypeDef *))(*(uint32_t *)0x8014)))
#define ROM_QSPI_WriteParam                  (*((uint8_t (*)(QSPI_CommandTypeDef *, uint16_t))(*(uint32_t *)0x8018)))
#define ROM_QSPI_EraseSector                 (*((uint8_t (*)(QSPI_CommandTypeDef *, uint32_t))(*(uint32_t *)0x801C)))
#define ROM_QSPI_ProgramPage                 (*((uint8_t (*)(QSPI_CommandTypeDef *, DMA_TypeDef *, uint32_t, uint32_t, uint8_t *))(*(uint32_t *)0x8024)))
#define ROM_QSPI_ReleaseDeepPowerDown        (*((uint8_t (*)(QSPI_CommandTypeDef *))(*(uint32_t *)0x802C)))
#define ROM_QSPI_StatusReg                   (*((uint16_t (*)(QSPI_CommandTypeDef *))(*(uint32_t *)0x8034)))


typedef enum
{
    QSPI_BUSMODE_111 = 0x00,    //CMD-ADDR-DATA = 1-1-1
    QSPI_BUSMODE_114 = 0x01,    //CMD-ADDR-DATA = 1-1-4
    QSPI_BUSMODE_144 = 0x02,    //CMD-ADDR-DATA = 1-4-4
    QSPI_BUSMODE_444 = 0x03,    //CMD-ADDR-DATA = 4-4-4
}QSPI_BusModeTypeDef;


typedef enum
{
    QSPI_CMDFORMAT_CMD8                         = 0x00,
    QSPI_CMDFORMAT_CMD8_RREG8                   = 0x01,
    QSPI_CMDFORMAT_CMD8_RREG16                  = 0x02,
    QSPI_CMDFORMAT_CMD8_RREG24                  = 0x03,
    QSPI_CMDFORMAT_CMD8_DMY24_WREG8             = 0x04,
    QSPI_CMDFORMAT_CMD8_ADDR24_RREG8            = 0x05,
    QSPI_CMDFORMAT_CMD8_ADDR24_RREG16           = 0x06,
    QSPI_CMDFORMAT_CMD8_WREG8                   = 0x07,
    QSPI_CMDFORMAT_CMD8_WREG16                  = 0x08,
    QSPI_CMDFORMAT_CMD8_ADDR24                  = 0x09,
    QSPI_CMDFORMAT_CMD8_ADDR24_RDAT             = 0x0A,
    QSPI_CMDFORMAT_CMD8_ADDR24_DMY_RDAT         = 0x0B,
    QSPI_CMDFORMAT_CMD8_ADDR24_M8_DMY_RDAT      = 0x0C,
    QSPI_CMDFORMAT_CMD8_ADDR24_PDAT             = 0x0D
}QSPI_CmdFormatTypeDef;


typedef enum
{
    QSPI_PROTOCOL_CLPL      = 0x00,
    QSPI_PROTOCOL_CHPH      = 0x03
}QSPI_ProtocolTypedef;

typedef enum
{
    QSPI_FREQSEL_HCLK_DIV2  = 0x01,
    QSPI_FREQSEL_HCLK_DIV3  = 0x02,
    QSPI_FREQSEL_HCLK_DIV4  = 0x03
}QSPI_FreqSelTypeDef;

typedef struct
{
    //Device Para
    uint8_t SampleDly;                      //Default:0
    uint8_t SamplePha;                      //Default:0
    uint8_t ProToCol;                       //Defualt: QSPI_PROTOCOL_CLPL
    uint8_t DummyCycles;                    //Include M7:0  Defualt: 6
    uint8_t FreqSel;                        //Defualt: QSPI_FREQSEL_HCLK_DIV4

    //Setting Cache
    uint8_t Cache_Cmd_ReleaseDeepInstruction;           //Defualt: 0xAB
    uint8_t Cache_Cmd_DeepInstruction;                  //Defualt: 0xB9
    uint8_t Cache_Cmd_ReadBusMode;                      //Defualt: QSPI_BUSMODE_144
    uint8_t Cache_Cmd_ReadFormat;                       //Defualt: QSPI_CMDFORMAT_CMD8_ADDR24_DMY_RDAT
    uint8_t Cache_Cmd_ReadInstruction;                  //Defualt: 0xEB

}QSPI_InitTypeDef;

typedef struct
{
    uint8_t Instruction;
    uint32_t BusMode;
    uint32_t CmdFormat;

}QSPI_CommandTypeDef;


void QSPI_Init(QSPI_InitTypeDef *mhqspi);
void QSPI_SetLatency(uint32_t u32UsClk);

uint8_t FLASH_EraseSector(uint32_t sectorAddress);
uint8_t FLASH_ProgramPage(uint32_t addr, uint32_t size, uint8_t *buffer);


#ifdef __cplusplus
}
#endif

#endif

