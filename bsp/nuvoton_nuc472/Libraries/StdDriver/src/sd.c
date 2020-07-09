/**************************************************************************//**
 * @file     SD.c
 * @version  V1.00
 * $Revision: 16 $
 * $Date: 15/11/26 10:45a $
 * @brief    NUC472/NUC442 SD driver source file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NUC472_442.h"

/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_SD_Driver SD Driver
  @{
*/


/** @addtogroup NUC472_442_SD_EXPORTED_FUNCTIONS SD Exported Functions
  @{
*/
#define SD_BLOCK_SIZE   512

/// @cond HIDDEN_SYMBOLS

// global variables
// For response R3 (such as ACMD41, CRC-7 is invalid; but SD controller will still
// calculate CRC-7 and get an error result, software should ignore this error and clear SDISR [CRC_IF] flag
// _sd_uR3_CMD is the flag for it. 1 means software should ignore CRC-7 error
uint32_t _sd_uR3_CMD=0;
uint32_t _sd_uR7_CMD=0;
uint8_t volatile _sd_SDDataReady = FALSE;

uint8_t *_sd_pSDHCBuffer;
uint32_t _sd_ReferenceClock;

#if defined (__CC_ARM)
__align(4096) uint8_t _sd_ucSDHCBuffer[512];
#elif defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma data_alignment = 4096
uint8_t _sd_ucSDHCBuffer[512];
#elif defined(__GNUC__)
__attribute__((aligned(4096)))
uint8_t _sd_ucSDHCBuffer[512];
#endif


int sd0_ok = 0;
int sd1_ok = 0;

uint8_t pSD0_offset = 0;
uint8_t pSD1_offset = 0;

DISK_DATA_T SD_DiskInfo0;
DISK_DATA_T SD_DiskInfo1;

SD_INFO_T SD0;
SD_INFO_T SD1;

void SD_CheckRB()
{
    while(1) {
        SD->CTL |= SDH_CTL_CLK8OEN_Msk;
        while(SD->CTL & SDH_CTL_CLK8OEN_Msk);
        if (SD->INTSTS & SDH_INTSTS_DAT0STS_Msk)
            break;
    }
}


int SD_SDCommand(SD_INFO_T *pSD, uint8_t ucCmd, uint32_t uArg)
{
    volatile int buf;

    SD->CMDARG = uArg;
    buf = (SD->CTL&(~SDH_CTL_CMDCODE_Msk))|(ucCmd << 8)|(SDH_CTL_COEN_Msk);
    SD->CTL = buf;

    while(SD->CTL & SDH_CTL_COEN_Msk) {
        if (pSD->IsCardInsert == FALSE)
            return SD_NO_SD_CARD;
    }
    return Successful;
}


int SD_SDCmdAndRsp(SD_INFO_T *pSD, uint8_t ucCmd, uint32_t uArg, int ntickCount)
{
    volatile int buf;

    SD->CMDARG = uArg;
    buf = (SD->CTL&(~SDH_CTL_CMDCODE_Msk))|(ucCmd << 8)|(SDH_CTL_COEN_Msk | SDH_CTL_RIEN_Msk);
    SD->CTL = buf;

    if (ntickCount > 0) {
        while(SD->CTL & SDH_CTL_RIEN_Msk) {
            if(ntickCount-- == 0) {
                SD->CTL |= SDH_CTL_CTLRST_Msk; // reset SD engine
                return 2;
            }
            if (pSD->IsCardInsert == FALSE)
                return SD_NO_SD_CARD;
        }
    } else {
        while(SD->CTL & SDH_CTL_RIEN_Msk) {
            if (pSD->IsCardInsert == FALSE)
                return SD_NO_SD_CARD;
        }
    }

    if (_sd_uR7_CMD) {
        if (((SD->RESP1 & 0xff) != 0x55) && ((SD->RESP0 & 0xf) != 0x01)) {
            _sd_uR7_CMD = 0;
            return SD_CMD8_ERROR;
        }
    }

    if (!_sd_uR3_CMD) {
        if (SD->INTSTS & SDH_INTSTS_CRC7_Msk)     // check CRC7
            return Successful;
        else {
            return SD_CRC7_ERROR;
        }
    } else { // ignore CRC error for R3 case
        _sd_uR3_CMD = 0;
        SD->INTSTS = SDH_INTSTS_CRCIF_Msk;
        return Successful;
    }
}


int SD_Swap32(int val)
{
#if 1
    int buf;

    buf = val;
    val <<= 24;
    val |= (buf<<8)&0xff0000;
    val |= (buf>>8)&0xff00;
    val |= (buf>>24)&0xff;
    return val;

#else
    return ((val<<24) | ((val<<8)&0xff0000) | ((val>>8)&0xff00) | (val>>24));
#endif
}

// Get 16 bytes CID or CSD
int SD_SDCmdAndRsp2(SD_INFO_T *pSD, uint8_t ucCmd, uint32_t uArg, uint32_t *puR2ptr)
{
    unsigned int i, buf;
    unsigned int tmpBuf[5];

    SD->CMDARG = uArg;
    buf = (SD->CTL&(~SDH_CTL_CMDCODE_Msk))|(ucCmd << 8)|(SDH_CTL_COEN_Msk | SDH_CTL_R2EN_Msk);
    SD->CTL = buf;

    while(SD->CTL & SDH_CTL_R2EN_Msk) {
        if (pSD->IsCardInsert == FALSE)
            return SD_NO_SD_CARD;
    }

    if (SD->INTSTS & SDH_INTSTS_CRC7_Msk) {
        for (i=0; i<5; i++) {
            tmpBuf[i] = SD_Swap32(*(int*)(SD_BASE+i*4));
        }
        for (i=0; i<4; i++)
            *puR2ptr++ = ((tmpBuf[i] & 0x00ffffff)<<8) | ((tmpBuf[i+1] & 0xff000000)>>24);
        return Successful;
    } else
        return SD_CRC7_ERROR;
}


int SD_SDCmdAndRspDataIn(SD_INFO_T *pSD, uint8_t ucCmd, uint32_t uArg)
{
    volatile int buf;

    SD->CMDARG = uArg;
    buf = (SD->CTL&(~SDH_CTL_CMDCODE_Msk))|(ucCmd << 8)|
          (SDH_CTL_COEN_Msk | SDH_CTL_RIEN_Msk | SDH_CTL_DIEN_Msk);

    SD->CTL = buf;

    while (SD->CTL & SDH_CTL_RIEN_Msk) {
        if (pSD->IsCardInsert == FALSE)
            return SD_NO_SD_CARD;
    }

    while (SD->CTL & SDH_CTL_DIEN_Msk) {
        if (pSD->IsCardInsert == FALSE)
            return SD_NO_SD_CARD;
    }

    if (!(SD->INTSTS & SDH_INTSTS_CRC7_Msk)) {    // check CRC7
        return SD_CRC7_ERROR;
    }

    if (!(SD->INTSTS & SDH_INTSTS_CRC16_Msk)) {   // check CRC16
        return SD_CRC16_ERROR;
    }
    return Successful;
}

// there are 8 bits for divider0, maximum is 256
#define SD_CLK_DIV0_MAX     256

void SD_Set_clock(uint32_t sd_clock_khz)
{
    uint32_t rate, div1, i;
    uint32_t u32SD_ClkSrc;

    if(sd_clock_khz >= 24000) {
        sd_clock_khz = 24000;
    }

    u32SD_ClkSrc = (CLK->CLKSEL0 & CLK_CLKSEL0_SDHSEL_Msk);

    if(u32SD_ClkSrc == CLK_CLKSEL0_SDHSEL_HXT)
        _sd_ReferenceClock = (CLK_GetHXTFreq() / 1000);
    else if(u32SD_ClkSrc == CLK_CLKSEL0_SDHSEL_HIRC)
        _sd_ReferenceClock = (__HIRC / 1000);
    else if(u32SD_ClkSrc == CLK_CLKSEL0_SDHSEL_PLL)
        _sd_ReferenceClock = (CLK_GetPLLClockFreq() / 1000);
    else if(u32SD_ClkSrc == CLK_CLKSEL0_SDHSEL_HCLK)
        _sd_ReferenceClock = (CLK_GetHCLKFreq() / 1000);

    rate = _sd_ReferenceClock / sd_clock_khz;

    // choose slower clock if system clock cannot divisible by wanted clock
    if (_sd_ReferenceClock % sd_clock_khz != 0)
        rate++;

    if(rate >= SD_CLK_DIV0_MAX) {
        rate = SD_CLK_DIV0_MAX;
    }

    //--- calculate the second divider CLKDIV0[SDHOST_N]
    div1 = ((rate -1) & 0xFF);

    //--- setup register
    CLK->CLKDIV0 &= ~CLK_CLKDIV0_SDHDIV_Msk;
    CLK->CLKDIV0 |= (div1 << CLK_CLKDIV0_SDHDIV_Pos);

    for(i=0; i<1000; i++);  // waiting for clock become stable
    return;
}

void SD_CardSelect(int cardSel)
{
    if(cardSel == 0) {
        SD->CTL |= (SD->CTL & ~SDH_CTL_SDPORT_Msk);
    } else if(cardSel == 1) {
        SD->CTL |= ((SD->CTL & ~SDH_CTL_SDPORT_Msk) | (1 << SDH_CTL_SDPORT_Pos));
    }
}

uint32_t SD_CardDetection(uint32_t u32CardNum)
{
    uint32_t i;

    if (u32CardNum == SD_PORT0) {
        if(SD->INTEN & SDH_INTEN_CDSRC0_Msk) { // Card detect pin from GPIO
            if(SD->INTSTS & SDH_INTSTS_CDSTS0_Msk) { // Card remove
                SD0.IsCardInsert = FALSE;
                return FALSE;
            } else
                SD0.IsCardInsert = TRUE;
        } else if(!(SD->INTEN & SDH_INTEN_CDSRC0_Msk)) {
            SD->CTL |= SDH_CTL_CLKKEEP0_Msk;
            for(i= 0; i < 5000; i++);

            if(SD->INTSTS & SDH_INTSTS_CDSTS0_Msk) // Card insert
                SD0.IsCardInsert = TRUE;
            else {
                SD0.IsCardInsert = FALSE;
                return FALSE;
            }

            SD->CTL &= ~SDH_CTL_CLKKEEP0_Msk;
        }

    } else if (u32CardNum == SD_PORT1) {
        if(SD->INTEN & SDH_INTEN_CDSRC1_Msk) { // Card detect pin from GPIO
            if(SD->INTSTS & SDH_INTSTS_CDSTS1_Msk) { // Card remove
                SD1.IsCardInsert = FALSE;
                return FALSE;
            } else
                SD1.IsCardInsert = TRUE;
        } else if(!(SD->INTEN & SDH_INTEN_CDSRC1_Msk)) {
            SD->CTL |= SDH_CTL_CLKKEEP1_Msk;
            for(i= 0; i < 5000; i++);

            if(SD->INTSTS & SDH_INTSTS_CDSTS1_Msk) // Card insert
                SD1.IsCardInsert = TRUE;
            else {
                SD1.IsCardInsert = FALSE;
                return FALSE;
            }

            SD->CTL &= ~SDH_CTL_CLKKEEP1_Msk;
        }

    }

    return TRUE;
}


// Initial
int SD_Init(SD_INFO_T *pSD)
{
    int volatile i, status;
    unsigned int resp;
    unsigned int CIDBuffer[4];
    unsigned int volatile u32CmdTimeOut;

    // set the clock to 200KHz
    //SD_Set_clock(200);
    SD_Set_clock(100);

    // power ON 74 clock
    SD->CTL |= SDH_CTL_CLK74OEN_Msk;

    while(SD->CTL & SDH_CTL_CLK74OEN_Msk) {
        if (pSD->IsCardInsert == FALSE)
            return SD_NO_SD_CARD;
    }

    SD_SDCommand(pSD, 0, 0);        // reset all cards
    for (i=0x1000; i>0; i--);

    // initial SDHC
    _sd_uR7_CMD = 1;
    //u32CmdTimeOut = 5000;
    u32CmdTimeOut = 0xFFFFF;
    //u32CmdTimeOut = 0;

    i = SD_SDCmdAndRsp(pSD, 8, 0x00000155, u32CmdTimeOut);
    if (i == Successful) {
        // SD 2.0
        SD_SDCmdAndRsp(pSD, 55, 0x00, u32CmdTimeOut);
        _sd_uR3_CMD = 1;
        SD_SDCmdAndRsp(pSD, 41, 0x40ff8000, u32CmdTimeOut); // 2.7v-3.6v
        resp = SD->RESP0;

        while (!(resp & 0x00800000)) {      // check if card is ready
            SD_SDCmdAndRsp(pSD, 55, 0x00, u32CmdTimeOut);
            _sd_uR3_CMD = 1;
            SD_SDCmdAndRsp(pSD, 41, 0x40ff8000, u32CmdTimeOut); // 3.0v-3.4v
            resp = SD->RESP0;
        }
        if (resp & 0x00400000)
            pSD->CardType = SD_TYPE_SD_HIGH;
        else
            pSD->CardType = SD_TYPE_SD_LOW;
    } else {
        // SD 1.1
        SD_SDCommand(pSD, 0, 0);        // reset all cards
        for (i=0x100; i>0; i--);

        i = SD_SDCmdAndRsp(pSD, 55, 0x00, u32CmdTimeOut);
        if (i == 2) {   // MMC memory

            SD_SDCommand(pSD, 0, 0);        // reset
            for (i=0x100; i>0; i--);

            _sd_uR3_CMD = 1;

            if (SD_SDCmdAndRsp(pSD, 1, 0x40ff8000, u32CmdTimeOut) != 2) {  // eMMC memory
                resp = SD->RESP0;
                while (!(resp & 0x00800000)) {      // check if card is ready
                    _sd_uR3_CMD = 1;

                    SD_SDCmdAndRsp(pSD, 1, 0x40ff8000, u32CmdTimeOut);      // high voltage
                    resp = SD->RESP0;
                }

                if(resp & 0x00400000)
                    pSD->CardType = SD_TYPE_EMMC;
                else
                    pSD->CardType = SD_TYPE_MMC;
            } else {
                pSD->CardType = SD_TYPE_UNKNOWN;
                return SD_ERR_DEVICE;
            }
        } else if (i == 0) { // SD Memory
            _sd_uR3_CMD = 1;
            SD_SDCmdAndRsp(pSD, 41, 0x00ff8000, u32CmdTimeOut); // 3.0v-3.4v
            resp = SD->RESP0;
            while (!(resp & 0x00800000)) {      // check if card is ready
                SD_SDCmdAndRsp(pSD, 55, 0x00,u32CmdTimeOut);
                _sd_uR3_CMD = 1;
                SD_SDCmdAndRsp(pSD, 41, 0x00ff8000, u32CmdTimeOut); // 3.0v-3.4v
                resp = SD->RESP0;
            }
            pSD->CardType = SD_TYPE_SD_LOW;
        } else {
            pSD->CardType = SD_TYPE_UNKNOWN;
            return SD_INIT_ERROR;
        }
    }

    // CMD2, CMD3
    if (pSD->CardType != SD_TYPE_UNKNOWN) {
        SD_SDCmdAndRsp2(pSD, 2, 0x00, CIDBuffer);
        if ((pSD->CardType == SD_TYPE_MMC) || (pSD->CardType == SD_TYPE_EMMC)) {
            if ((status = SD_SDCmdAndRsp(pSD, 3, 0x10000, 0)) != Successful)        // set RCA
                return status;
            pSD->RCA = 0x10000;
        } else {
            if ((status = SD_SDCmdAndRsp(pSD, 3, 0x00, 0)) != Successful)       // get RCA
                return status;
            else
                pSD->RCA = (SD->RESP0 << 8) & 0xffff0000;
        }
    }

    return Successful;
}


int SD_SwitchToHighSpeed(SD_INFO_T *pSD)
{
    int volatile status=0;
    uint16_t current_comsumption, busy_status0;

    SD->DMASA = (uint32_t)_sd_pSDHCBuffer;    // set DMA transfer starting address
    SD->BLEN = 63;    // 512 bit

    if ((status = SD_SDCmdAndRspDataIn(pSD, 6, 0x00ffff01)) != Successful)
        return Fail;

    current_comsumption = _sd_pSDHCBuffer[0]<<8 | _sd_pSDHCBuffer[1];
    if (!current_comsumption)
        return Fail;

    busy_status0 = _sd_pSDHCBuffer[28]<<8 | _sd_pSDHCBuffer[29];

    if (!busy_status0) { // function ready
        SD->DMASA = (uint32_t)_sd_pSDHCBuffer;        // set DMA transfer starting address
        SD->BLEN = 63;    // 512 bit

        if ((status = SD_SDCmdAndRspDataIn(pSD, 6, 0x80ffff01)) != Successful)
            return Fail;

        // function change timing: 8 clocks
        SD->CTL |= SDH_CTL_CLK8OEN_Msk;
        while(SD->CTL & SDH_CTL_CLK8OEN_Msk);

        current_comsumption = _sd_pSDHCBuffer[0]<<8 | _sd_pSDHCBuffer[1];
        if (!current_comsumption)
            return Fail;

        return Successful;
    } else
        return Fail;
}


int SD_SelectCardType(SD_INFO_T *pSD)
{
    int volatile status=0;
    unsigned int arg;

    if ((status = SD_SDCmdAndRsp(pSD, 7, pSD->RCA, 0)) != Successful)
        return status;

    SD_CheckRB();

    // if SD card set 4bit
    if (pSD->CardType == SD_TYPE_SD_HIGH) {
        _sd_pSDHCBuffer = (uint8_t *)((uint32_t)_sd_ucSDHCBuffer);
        SD->DMASA = (uint32_t)_sd_pSDHCBuffer;    // set DMA transfer starting address
        SD->BLEN = 0x07;  // 64 bit

        if ((status = SD_SDCmdAndRsp(pSD, 55, pSD->RCA, 0)) != Successful)
            return status;
        if ((status = SD_SDCmdAndRspDataIn(pSD, 51, 0x00)) != Successful)
            return status;

        if ((_sd_ucSDHCBuffer[0] & 0xf) == 0x2) {
            status = SD_SwitchToHighSpeed(pSD);
            if (status == Successful) {
                /* divider */
                SD_Set_clock(SDHC_FREQ);
            }
        }

        if ((status = SD_SDCmdAndRsp(pSD, 55, pSD->RCA, 0)) != Successful)
            return status;
        if ((status = SD_SDCmdAndRsp(pSD, 6, 0x02, 0)) != Successful)   // set bus width
            return status;

        SD->CTL |= SDH_CTL_DBW_Msk;
    } else if (pSD->CardType == SD_TYPE_SD_LOW) {
        _sd_pSDHCBuffer = (uint8_t *)((uint32_t)_sd_ucSDHCBuffer);
        SD->DMASA = (uint32_t) _sd_pSDHCBuffer; // set DMA transfer starting address
        SD->BLEN = 0x07;  // 64 bit

        if ((status = SD_SDCmdAndRsp(pSD, 55, pSD->RCA, 0)) != Successful)
            return status;
        if ((status = SD_SDCmdAndRspDataIn(pSD, 51, 0x00)) != Successful)
            return status;

        // set data bus width. ACMD6 for SD card, SDCR_DBW for host.
        if ((status = SD_SDCmdAndRsp(pSD, 55, pSD->RCA, 0)) != Successful)
            return status;

        if ((status = SD_SDCmdAndRsp(pSD, 6, 0x02, 0)) != Successful)   // set bus width
            return status;

        SD->CTL |= SDH_CTL_DBW_Msk;
    } else if ((pSD->CardType == SD_TYPE_MMC) ||(pSD->CardType == SD_TYPE_EMMC)) {

        if(pSD->CardType == SD_TYPE_MMC)
            SD->CTL &= ~SDH_CTL_DBW_Msk;

        //--- sent CMD6 to MMC card to set bus width to 4 bits mode
        // set CMD6 argument Access field to 3, Index to 183, Value to 1 (4-bit mode)
        arg = (3 << 24) | (183 << 16) | (1 << 8);
        if ((status = SD_SDCmdAndRsp(pSD, 6, arg, 0)) != Successful)
            return status;
        SD_CheckRB();

        SD->CTL |= SDH_CTL_DBW_Msk;; // set bus width to 4-bit mode for SD host controller

    }

    if ((status = SD_SDCmdAndRsp(pSD, 16, SD_BLOCK_SIZE, 0)) != Successful) // set block length
        return status;
    SD->BLEN = SD_BLOCK_SIZE - 1;           // set the block size

    SD_SDCommand(pSD, 7, 0);
    SD->CTL |= SDH_CTL_CLK8OEN_Msk;
    while(SD->CTL & SDH_CTL_CLK8OEN_Msk);

#ifdef _SD_USE_INT_
    SD->INTEN |= SDH_INTEN_BLKDIEN_Msk;
#endif  //_SD_USE_INT_

    return Successful;
}

void SD_Get_SD_info(SD_INFO_T *pSD, DISK_DATA_T *_info)
{
    unsigned int R_LEN, C_Size, MULT, size;
    unsigned int Buffer[4];
    unsigned char *ptr;

    SD_SDCmdAndRsp2(pSD, 9, pSD->RCA, Buffer);

    if ((pSD->CardType == SD_TYPE_MMC) || (pSD->CardType == SD_TYPE_EMMC)) {
        // for MMC/eMMC card
        if ((Buffer[0] & 0xc0000000) == 0xc0000000) {
            // CSD_STRUCTURE [127:126] is 3
            // CSD version depend on EXT_CSD register in eMMC v4.4 for card size > 2GB
            SD_SDCmdAndRsp(pSD, 7, pSD->RCA, 0);

            ptr = (uint8_t *)((uint32_t)_sd_ucSDHCBuffer );
            SD->DMASA = (uint32_t)ptr;  // set DMA transfer starting address
            SD->BLEN = 511;  // read 512 bytes for EXT_CSD

            if (SD_SDCmdAndRspDataIn(pSD, 8, 0x00) != Successful)
                return;

            SD_SDCommand(pSD, 7, 0);
            SD->CTL |= SDH_CTL_CLK8OEN_Msk;
            while(SD->CTL & SDH_CTL_CLK8OEN_Msk);

            _info->totalSectorN = (*(uint32_t *)(ptr+212));
            _info->diskSize = _info->totalSectorN / 2;
        } else {
            // CSD version v1.0/1.1/1.2 in eMMC v4.4 spec for card size <= 2GB
            R_LEN = (Buffer[1] & 0x000f0000) >> 16;
            C_Size = ((Buffer[1] & 0x000003ff) << 2) | ((Buffer[2] & 0xc0000000) >> 30);
            MULT = (Buffer[2] & 0x00038000) >> 15;
            size = (C_Size+1) * (1<<(MULT+2)) * (1<<R_LEN);

            _info->diskSize = size / 1024;
            _info->totalSectorN = size / 512;
        }
    } else {
        if (Buffer[0] & 0xc0000000) {
            C_Size = ((Buffer[1] & 0x0000003f) << 16) | ((Buffer[2] & 0xffff0000) >> 16);
            size = (C_Size+1) * 512;    // Kbytes

            _info->diskSize = size;
            _info->totalSectorN = size << 1;
        } else {
            R_LEN = (Buffer[1] & 0x000f0000) >> 16;
            C_Size = ((Buffer[1] & 0x000003ff) << 2) | ((Buffer[2] & 0xc0000000) >> 30);
            MULT = (Buffer[2] & 0x00038000) >> 15;
            size = (C_Size+1) * (1<<(MULT+2)) * (1<<R_LEN);

            _info->diskSize = size / 1024;
            _info->totalSectorN = size / 512;
        }
    }

    _info->sectorSize = 512;
}

int SD_ChipErase(SD_INFO_T *pSD, DISK_DATA_T *_info)
{
    int status=0;

    status = SD_SDCmdAndRsp(pSD, 32, 512, 6000);
    if (status < 0) {
        return status;
    }
    status = SD_SDCmdAndRsp(pSD, 33, _info->totalSectorN*512, 6000);
    if (status < 0) {
        return status;
    }
    status = SD_SDCmdAndRsp(pSD, 38, 0, 6000);
    if (status < 0) {
        return status;
    }
    SD_CheckRB();

    return 0;
}

/// @endcond HIDDEN_SYMBOLS


/**
 *  @brief  This function use to reset SD function and select card detection source and pin.
 *
 *  @param[in]  u32CardDetSrc   Select card detection source from SD0 or SD1. ( \ref SD_PORT0 / \ref SD_PORT1) \n
 *                          And also select card detection pin from GPIO or DAT3 pin. ( \ref CardDetect_From_GPIO / \ref CardDetect_From_DAT3)
 *
 *  @return None
 */
void SD_Open(uint32_t u32CardDetSrc)
{
    // Enable SD Card Host Controller operation.
    //CLK->AHBCLK |= CLK_AHBCLK_SDHCKEN_Msk;

    // enable DMAC
    SD->DMACTL = SDH_DMACTL_DMARST_Msk;
    while(SD->DMACTL & SDH_DMACTL_DMARST_Msk);

    SD->DMACTL = SDH_DMACTL_DMAEN_Msk;

    //Reset FMI
    SD->GCTL = SDH_GCTL_GCTLRST_Msk;        // Start reset FMI controller.
    while(SD->GCTL & SDH_GCTL_GCTLRST_Msk);


//#ifdef _SD_USE_INT_
//    NVIC_EnableIRQ(SD_IRQn);
//#endif  //_SD_USE_INT_

    // enable SD
    SD->GCTL = SDH_GCTL_SDEN_Msk;

    if(u32CardDetSrc & SD_PORT0) {
        SD->CTL |= (SD->CTL & ~SDH_CTL_SDPORT_Msk);

        if(u32CardDetSrc & CardDetect_From_DAT3) {
            SD->INTEN &= ~SDH_INTEN_CDSRC0_Msk;
        } else {
            SD->INTEN |= SDH_INTEN_CDSRC0_Msk;
        }
    } else if(u32CardDetSrc & SD_PORT1) {
        SD->CTL |= ((SD->CTL & ~SDH_CTL_SDPORT_Msk) | (1 << SDH_CTL_SDPORT_Pos));

        if(u32CardDetSrc & CardDetect_From_DAT3) {
            SD->INTEN &= ~SDH_INTEN_CDSRC1_Msk;
        } else {
            SD->INTEN |= SDH_INTEN_CDSRC1_Msk;
        }
    }

    SD->CTL |= SDH_CTL_CTLRST_Msk;     // SD software reset
    while(SD->CTL & SDH_CTL_CTLRST_Msk);

    SD->CTL &= ~((0xFF) | (SDH_CTL_CLKKEEP1_Msk));    // disable SD clock output

    if(u32CardDetSrc & SD_PORT0) {
        memset(&SD0, 0, sizeof(SD_INFO_T));
    } else if(u32CardDetSrc & SD_PORT1) {
        memset(&SD1, 0, sizeof(SD_INFO_T));
    }

}

/**
 *  @brief  This function use to initial SD card.
 *
 *  @param[in]  u32CardNum  Select initial SD0 or SD1. ( \ref SD_PORT0 / \ref SD_PORT1)
 *
 *  @return None
 */
void SD_Probe(uint32_t u32CardNum)
{
    // Disable FMI/SD host interrupt
    SD->GINTEN = 0;

    SD->CTL &= ~SDH_CTL_SDNWR_Msk;
    SD->CTL |=  0x09 << SDH_CTL_SDNWR_Pos;         // set SDNWR = 9
    SD->CTL &= ~SDH_CTL_BLKCNT_Msk;
    SD->CTL |=  0x01 << SDH_CTL_BLKCNT_Pos;           // set BLKCNT = 1
    SD->CTL &= ~SDH_CTL_DBW_Msk;               // SD 1-bit data bus

    if(!(SD_CardDetection(u32CardNum)))
        return;

    if (u32CardNum == SD_PORT0) {
        if (SD_Init(&SD0) < 0)
            return;

        /* divider */
        if (SD0.CardType == SD_TYPE_MMC)
            SD_Set_clock(20000);
        else
            SD_Set_clock(SD_FREQ);

        SD_Get_SD_info(&SD0, &SD_DiskInfo0);

        if (SD_SelectCardType(&SD0))
            return;

        sd0_ok = 1;
    } else if (u32CardNum == SD_PORT1) {
        if (SD_Init(&SD1) < 0)
            return;

        /* divider */
        if (SD1.CardType == SD_TYPE_MMC)
            SD_Set_clock(20000);
        else
            SD_Set_clock(SD_FREQ);

        SD_Get_SD_info(&SD1, &SD_DiskInfo1);

        if (SD_SelectCardType(&SD1))
            return;

        sd1_ok = 1;
    }


}

/**
 *  @brief  This function use to read data from SD card.
 *
 *  @param[in]     u32CardNum    Select card: SD0 or SD1. ( \ref SD_PORT0 / \ref SD_PORT1)
 *  @param[out]    pu8BufAddr    The buffer to receive the data from SD card.
 *  @param[in]     u32StartSec   The start read sector address.
 *  @param[in]     u32SecCount   The the read sector number of data
 *
 *  @return None
 */
uint32_t SD_Read(uint32_t u32CardNum, uint8_t *pu8BufAddr, uint32_t u32StartSec, uint32_t u32SecCount)
{
    char volatile bIsSendCmd = FALSE, buf;
    unsigned int volatile reg;
    int volatile i, loop, status;
    uint32_t blksize = SD_BLOCK_SIZE;

    SD_INFO_T *pSD;

    if(u32CardNum == SD_PORT0)
        pSD = &SD0;
    else
        pSD = &SD1;

    //--- check input parameters
    if (u32SecCount == 0) {
        return SD_SELECT_ERROR;
    }

    if ((status = SD_SDCmdAndRsp(pSD, 7, pSD->RCA, 0)) != Successful)
        return status;
    SD_CheckRB();

    SD->BLEN = blksize - 1;       // the actual byte count is equal to (SDBLEN+1)

    if ( (pSD->CardType == SD_TYPE_SD_HIGH) || (pSD->CardType == SD_TYPE_EMMC) )
        SD->CMDARG = u32StartSec;
    else
        SD->CMDARG = u32StartSec * blksize;

    SD->DMASA = (uint32_t)pu8BufAddr;

    loop = u32SecCount / 255;
    for (i=0; i<loop; i++) {
#ifdef _SD_USE_INT_
        _sd_SDDataReady = FALSE;
#endif  //_SD_USE_INT_

        reg = SD->CTL & ~SDH_CTL_CMDCODE_Msk;
        reg = reg | 0xff0000;   // set BLK_CNT to 255
        if (bIsSendCmd == FALSE) {
            SD->CTL = reg|(18<<8)|(SDH_CTL_COEN_Msk | SDH_CTL_RIEN_Msk | SDH_CTL_DIEN_Msk);
            bIsSendCmd = TRUE;
        } else
            SD->CTL = reg | SDH_CTL_DIEN_Msk;

#ifdef _SD_USE_INT_
        while(!_sd_SDDataReady)
#else
        while(1)
#endif  //_SD_USE_INT_
        {
            if(_sd_SDDataReady) break;

#ifndef _SD_USE_INT_
            if ((SD->INTSTS & SDH_INTSTS_BLKDIF_Msk) && (!(SD->CTL & SDH_CTL_DIEN_Msk))) {
                SD->INTSTS = SDH_INTSTS_BLKDIF_Msk;
                break;
            }
#endif
            if (pSD->IsCardInsert == FALSE)
                return SD_NO_SD_CARD;
        }

        if (!(SD->INTSTS & SDH_INTSTS_CRC7_Msk)) {    // check CRC7
            //printf("sdioSD_Read_in_blksize(): response error!\n");
            return SD_CRC7_ERROR;
        }

        if (!(SD->INTSTS & SDH_INTSTS_CRC16_Msk)) {   // check CRC16
            //printf("sdioSD_Read_in_blksize() :read data error!\n");
            return SD_CRC16_ERROR;
        }
    }

    loop = u32SecCount % 255;
    if (loop != 0) {
#ifdef _SD_USE_INT_
        _sd_SDDataReady = FALSE;
#endif  //_SD_USE_INT_

        reg = SD->CTL & (~SDH_CTL_CMDCODE_Msk);
        reg = reg & (~SDH_CTL_BLKCNT_Msk);
        reg |= (loop << 16);    // setup SDCR_BLKCNT

        if (bIsSendCmd == FALSE) {
            SD->CTL = reg|(18<<8)|(SDH_CTL_COEN_Msk | SDH_CTL_RIEN_Msk | SDH_CTL_DIEN_Msk);
            bIsSendCmd = TRUE;
        } else
            SD->CTL = reg | SDH_CTL_DIEN_Msk;

#ifdef _SD_USE_INT_
        while(!_sd_SDDataReady)
#else
        while(1)
#endif  //_SD_USE_INT_
        {

#ifndef _SD_USE_INT_
            if ((SD->INTSTS & SDH_INTSTS_BLKDIF_Msk) && (!(SD->CTL & SDH_CTL_DIEN_Msk))) {
                SD->INTSTS = SDH_INTSTS_BLKDIF_Msk;
                break;
            }
#endif

            if (pSD->IsCardInsert == FALSE)
                return SD_NO_SD_CARD;
        }

        if (!(SD->INTSTS & SDH_INTSTS_CRC7_Msk)) {    // check CRC7
            //printf("sdioSD_Read_in_blksize(): response error!\n");
            return SD_CRC7_ERROR;
        }

        if (!(SD->INTSTS & SDH_INTSTS_CRC16_Msk)) {   // check CRC16
            //printf("sdioSD_Read_in_blksize(): read data error!\n");
            return SD_CRC16_ERROR;
        }
    }

    if (SD_SDCmdAndRsp(pSD, 12, 0, 0)) {    // stop command
        //printf("stop command fail !!\n");
        return SD_CRC7_ERROR;
    }
    SD_CheckRB();

    SD_SDCommand(pSD, 7, 0);
    SD->CTL |= SDH_CTL_CLK8OEN_Msk;
    while(SD->CTL & SDH_CTL_CLK8OEN_Msk);

    return Successful;
}


/**
 *  @brief  This function use to write data to SD card.
 *
 *  @param[in]    u32CardNum  Select card: SD0 or SD1. ( \ref SD_PORT0 / \ref SD_PORT1)
 *  @param[in]    pu8BufAddr    The buffer to send the data to SD card.
 *  @param[in]    u32StartSec   The start write sector address.
 *  @param[in]    u32SecCount   The the write sector number of data.
 *
 *  @return   \ref SD_SELECT_ERROR : u32SecCount is zero. \n
 *            \ref SD_NO_SD_CARD : SD card be removed. \n
 *            \ref SD_CRC_ERROR : CRC error happen. \n
 *            \ref SD_CRC7_ERROR : CRC7 error happen. \n
 *            \ref Successful : Write data to SD card success.
 */
uint32_t SD_Write(uint32_t u32CardNum, uint8_t *pu8BufAddr, uint32_t u32StartSec, uint32_t u32SecCount)
{
    char volatile bIsSendCmd = FALSE;
    unsigned int volatile reg;
    int volatile i, loop, status;

    SD_INFO_T *pSD;

    if(u32CardNum == SD_PORT0)
        pSD = &SD0;
    else
        pSD = &SD1;


    //--- check input parameters
    if (u32SecCount == 0) {
        return SD_SELECT_ERROR;
    }

    if ((status = SD_SDCmdAndRsp(pSD, 7, pSD->RCA, 0)) != Successful)
        return status;

    SD_CheckRB();

    // According to SD Spec v2.0, the write CMD block size MUST be 512, and the start address MUST be 512*n.
    SD->BLEN = SD_BLOCK_SIZE - 1;           // set the block size

    if ((pSD->CardType == SD_TYPE_SD_HIGH) || (pSD->CardType == SD_TYPE_EMMC))
        SD->CMDARG = u32StartSec;
    else
        SD->CMDARG = u32StartSec * SD_BLOCK_SIZE;  // set start address for SD CMD

    SD->DMASA = (uint32_t)pu8BufAddr;
    loop = u32SecCount / 255;   // the maximum block count is 0xFF=255 for register SDCR[BLK_CNT]
    for (i=0; i<loop; i++) {
#ifdef _SD_USE_INT_
        _sd_SDDataReady = FALSE;
#endif  //_SD_USE_INT_

        reg = SD->CTL & 0xff00c080;
        reg = reg | 0xff0000;   // set BLK_CNT to 0xFF=255
        if (!bIsSendCmd) {
            SD->CTL = reg|(25<<8)|(SDH_CTL_COEN_Msk | SDH_CTL_RIEN_Msk | SDH_CTL_DOEN_Msk);
            bIsSendCmd = TRUE;
        } else
            SD->CTL = reg | SDH_CTL_DOEN_Msk;

#ifdef _SD_USE_INT_
        while(!_sd_SDDataReady)
#else
        while(1)
#endif  //_SD_USE_INT_
        {
#ifndef _SD_USE_INT_
            if ((SD->INTSTS & SDH_INTSTS_BLKDIF_Msk) && (!(SD->CTL & SDH_CTL_DOEN_Msk))) {
                SD->INTSTS = SDH_INTSTS_BLKDIF_Msk;
                break;
            }
#endif
            if (pSD->IsCardInsert == FALSE)
                return SD_NO_SD_CARD;
        }

        if ((SD->INTSTS & SDH_INTSTS_CRCIF_Msk) != 0) {   // check CRC
            SD->INTSTS = SDH_INTSTS_CRCIF_Msk;
            return SD_CRC_ERROR;
        }
    }

    loop = u32SecCount % 255;
    if (loop != 0) {
#ifdef _SD_USE_INT_
        _sd_SDDataReady = FALSE;
#endif  //_SD_USE_INT_

        reg = (SD->CTL & 0xff00c080) | (loop << 16);
        if (!bIsSendCmd) {
            SD->CTL = reg|(25<<8)|(SDH_CTL_COEN_Msk | SDH_CTL_RIEN_Msk | SDH_CTL_DOEN_Msk);
            bIsSendCmd = TRUE;
        } else
            SD->CTL = reg | SDH_CTL_DOEN_Msk;

#ifdef _SD_USE_INT_
        while(!_sd_SDDataReady)
#else
        while(1)
#endif  //_SD_USE_INT_
        {
#ifndef _SD_USE_INT_
            if ((SD->INTSTS & SDH_INTSTS_BLKDIF_Msk) && (!(SD->CTL & SDH_CTL_DOEN_Msk))) {
                SD->INTSTS = SDH_INTSTS_BLKDIF_Msk;
                break;
            }
#endif
            if (pSD->IsCardInsert == FALSE)
                return SD_NO_SD_CARD;
        }

        if ((SD->INTSTS & SDH_INTSTS_CRCIF_Msk) != 0) {   // check CRC
            SD->INTSTS = SDH_INTSTS_CRCIF_Msk;
            return SD_CRC_ERROR;
        }
    }
    SD->INTSTS = SDH_INTSTS_CRCIF_Msk;

    if (SD_SDCmdAndRsp(pSD, 12, 0, 0)) {    // stop command
        return SD_CRC7_ERROR;
    }
    SD_CheckRB();

    SD_SDCommand(pSD, 7, 0);
    SD->CTL |= SDH_CTL_CLK8OEN_Msk;
    while(SD->CTL & SDH_CTL_CLK8OEN_Msk);

    return Successful;
}


/*@}*/ /* end of group NUC472_442_SD_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_SD_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/








