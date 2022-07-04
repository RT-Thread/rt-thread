/**************************************************************************//**
 * @file     sdh.c
 * @version  V1.00
 * @brief    M2354 SDH driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NuMicro.h"

#if defined (__ICCARM__)
    #pragma diag_suppress=Pm073, Pm143        /* Misra C 2004 rule 14.7 */
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SDH_Driver SDH Driver
  @{
*/

/** @addtogroup SDH_EXPORTED_FUNCTIONS SDH Exported Functions
  @{
*/

#define SDH_BLOCK_SIZE   512UL

/* #define DEBUG_PRINTF printf */
#define DEBUG_PRINTF(...)

/** @cond HIDDEN_SYMBOLS */

/* global variables */
/* For response R3 (such as ACMD41, CRC-7 is invalid; but SD controller will still */
/* calculate CRC-7 and get an error result, software should ignore this error and clear SDISR [CRC_IF] flag */
/* _sd_uR3_CMD is the flag for it. 1 means software should ignore CRC-7 error */
uint8_t g_u8R3Flag = 0UL;
uint8_t volatile g_u8SDDataReadyFlag = (uint8_t)FALSE;

static uint32_t _SDH_uR7_CMD = 0UL;
static uint32_t _SDH_ReferenceClock;

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment = 4
    static uint8_t _SDH_ucSDHCBuffer[512];
#else
    static __attribute__((aligned)) uint8_t _SDH_ucSDHCBuffer[512];
#endif

/* Declare these functions here to avoid MISRA C 2004 rule 8.1 error */
void SDH_CheckRB(SDH_T *sdh);
uint32_t SDH_SDCommand(SDH_T *sdh, uint32_t u32Cmd, uint32_t u32Arg);
uint32_t SDH_SDCmdAndRsp(SDH_T *sdh, uint32_t u32Cmd, uint32_t u32Arg, uint32_t u32TickCount);
uint32_t SDH_Swap32(uint32_t u32Val);
uint32_t SDH_SDCmdAndRsp2(SDH_T *sdh, uint32_t u32Cmd, uint32_t u32Arg, uint32_t pu32R2ptr[]);
uint32_t SDH_SDCmdAndRspDataIn(SDH_T *sdh, uint32_t u32Cmd, uint32_t u32Arg);
void SDH_Set_clock(SDH_T *sdh, uint32_t u32SDClockKhz);
uint32_t SDH_CardDetection(SDH_T *sdh);
uint32_t SDH_Init(SDH_T *sdh);
uint32_t SDH_SwitchToHighSpeed(SDH_T *sdh, SDH_INFO_T *pSD);
uint32_t SDH_SelectCardType(SDH_T *sdh);
void SDH_Get_SD_info(SDH_T *sdh);

SDH_INFO_T SD0;

void SDH_CheckRB(SDH_T *sdh)
{
    while (1)
    {
        sdh->CTL |= SDH_CTL_CLK8OEN_Msk;
        while (sdh->CTL & SDH_CTL_CLK8OEN_Msk) {}
        if (sdh->INTSTS & SDH_INTSTS_DAT0STS_Msk)
        {
            break;
        }
    }
}


uint32_t SDH_SDCommand(SDH_T *sdh, uint32_t u32Cmd, uint32_t u32Arg)
{
    SDH_INFO_T *pSD;
    volatile uint32_t u32Status = Successful;

    /* M2354 is only support SDH0 */
    pSD = &SD0;

    sdh->CMDARG = u32Arg;
    sdh->CTL = (sdh->CTL & (~SDH_CTL_CMDCODE_Msk)) | (u32Cmd << 8) | (SDH_CTL_COEN_Msk);

    while (sdh->CTL & SDH_CTL_COEN_Msk)
    {
        if (pSD->IsCardInsert == (uint32_t)FALSE)
        {
            u32Status = SDH_NO_SD_CARD;
        }
    }
    return u32Status;
}


uint32_t SDH_SDCmdAndRsp(SDH_T *sdh, uint32_t u32Cmd, uint32_t u32Arg, uint32_t u32TickCount)
{
    SDH_INFO_T *pSD;

    /* M2354 is only support SDH0 */
    pSD = &SD0;

    sdh->CMDARG = u32Arg;
    sdh->CTL = (sdh->CTL & (~SDH_CTL_CMDCODE_Msk)) | (u32Cmd << 8) | (SDH_CTL_COEN_Msk | SDH_CTL_RIEN_Msk);

    if (u32TickCount > 0UL)
    {
        while (sdh->CTL & SDH_CTL_RIEN_Msk)
        {
            if (u32TickCount-- == 0UL)
            {
                sdh->CTL |= SDH_CTL_CTLRST_Msk; /* reset SD engine */
                return 2UL;
            }
            if (pSD->IsCardInsert == (uint8_t)FALSE)
            {
                return SDH_NO_SD_CARD;
            }
        }
    }
    else
    {
        while (sdh->CTL & SDH_CTL_RIEN_Msk)
        {
            if (pSD->IsCardInsert == (uint8_t)FALSE)
            {
                return SDH_NO_SD_CARD;
            }
        }
    }

    if (_SDH_uR7_CMD)
    {
        if ((sdh->RESP1 & 0xffUL) != 0x55UL)
        {
            if ((sdh->RESP0 & 0xfUL) != 0x01UL)
            {
                _SDH_uR7_CMD = 0UL;
                return SDH_CMD8_ERROR;
            }
        }
    }

    if (!g_u8R3Flag)
    {
        if (sdh->INTSTS & SDH_INTSTS_CRC7_Msk)     /* check CRC7 */
        {
            return Successful;
        }
        else
        {
            return SDH_CRC7_ERROR;
        }
    }
    else     /* ignore CRC error for R3 case */
    {
        g_u8R3Flag = 0UL;
        sdh->INTSTS = SDH_INTSTS_CRCIF_Msk;
        return Successful;
    }
}


uint32_t SDH_Swap32(uint32_t u32Val)
{
    uint32_t u32Buf;

    u32Buf = u32Val;
    u32Val <<= 24;
    u32Val |= (u32Buf << 8) & 0xff0000UL;
    u32Val |= (u32Buf >> 8) & 0xff00UL;
    u32Val |= (u32Buf >> 24) & 0xffUL;
    return u32Val;
}

/* Get 16 bytes CID or CSD */
uint32_t SDH_SDCmdAndRsp2(SDH_T *sdh, uint32_t u32Cmd, uint32_t u32Arg, uint32_t pu32R2ptr[])
{
    uint32_t i;
    uint32_t au32TmpBuf[5];
    SDH_INFO_T *pSD;

    /* M2354 is only support SDH0 */
    pSD = &SD0;

    sdh->CMDARG = u32Arg;
    sdh->CTL = (sdh->CTL & (~SDH_CTL_CMDCODE_Msk)) | (u32Cmd << 8) | (SDH_CTL_COEN_Msk | SDH_CTL_R2EN_Msk);

    while (sdh->CTL & SDH_CTL_R2EN_Msk)
    {
        if (pSD->IsCardInsert == (uint8_t)FALSE)
        {
            return SDH_NO_SD_CARD;
        }
    }

    if (sdh->INTSTS & SDH_INTSTS_CRC7_Msk)
    {
        for (i = 0UL; i < 5UL; i++)
        {
            au32TmpBuf[i] = SDH_Swap32(sdh->FB[i]);
        }
        for (i = 0UL; i < 4UL; i++)
        {
            pu32R2ptr[i] = ((au32TmpBuf[i] & 0x00ffffffUL) << 8) | ((au32TmpBuf[i + 1UL] & 0xff000000UL) >> 24);
        }
        return Successful;
    }
    else
    {
        return SDH_CRC7_ERROR;
    }
}


uint32_t SDH_SDCmdAndRspDataIn(SDH_T *sdh, uint32_t u32Cmd, uint32_t u32Arg)
{
    SDH_INFO_T *pSD;

    /* M2354 is only support SDH0 */
    pSD = &SD0;

    sdh->CMDARG = u32Arg;
    sdh->CTL = (sdh->CTL & (~SDH_CTL_CMDCODE_Msk)) | ((uint32_t)u32Cmd << 8) |
               (SDH_CTL_COEN_Msk | SDH_CTL_RIEN_Msk | SDH_CTL_DIEN_Msk);

    while (sdh->CTL & SDH_CTL_RIEN_Msk)
    {
        if (pSD->IsCardInsert == (uint32_t)FALSE)
        {
            return SDH_NO_SD_CARD;
        }
    }

    while (sdh->CTL & SDH_CTL_DIEN_Msk)
    {
        if (pSD->IsCardInsert == (uint32_t)FALSE)
        {
            return SDH_NO_SD_CARD;
        }
    }

    if (!(sdh->INTSTS & SDH_INTSTS_CRC7_Msk))      /* check CRC7 */
    {
        return SDH_CRC7_ERROR;
    }

    if (!(sdh->INTSTS & SDH_INTSTS_CRC16_Msk))     /* check CRC16 */
    {
        return SDH_CRC16_ERROR;
    }

    return Successful;
}

/* there are 8 bits for divider0, maximum is 256 */
#define SDH_CLK_DIV0_MAX     256UL

void SDH_Set_clock(SDH_T *sdh, uint32_t u32SDClockKhz)
{
    (void)sdh;
    if (!(__PC() & (1UL << 28)))
    {
        uint32_t u32Rate, u32Div1;
        static uint32_t u32SDClkSrc = 0UL;

        SYS_UnlockReg();
        /* M2354 is only support SDH0 */
        u32SDClkSrc = (CLK->CLKSEL0 & CLK_CLKSEL0_SDH0SEL_Msk);
        if (u32SDClkSrc == CLK_CLKSEL0_SDH0SEL_HXT)
        {
            _SDH_ReferenceClock = (CLK_GetHXTFreq() / 1000UL);
        }
        else if (u32SDClkSrc == CLK_CLKSEL0_SDH0SEL_HIRC)
        {
            _SDH_ReferenceClock = (__HIRC / 1000UL);
        }
        else if (u32SDClkSrc == CLK_CLKSEL0_SDH0SEL_PLL)
        {
            _SDH_ReferenceClock = (CLK_GetPLLClockFreq() / 1000UL);
        }
        else if (u32SDClkSrc == CLK_CLKSEL0_SDH0SEL_HCLK)
        {
            _SDH_ReferenceClock = (CLK_GetHCLKFreq() / 1000UL);
        }

        if (u32SDClockKhz >= 50000UL)
        {
            u32SDClockKhz = 50000UL;
        }
        u32Rate = _SDH_ReferenceClock / u32SDClockKhz;

        /* choose slower clock if system clock cannot divisible by wanted clock */
        if (_SDH_ReferenceClock % u32SDClockKhz != 0UL)
        {
            u32Rate++;
        }

        if (u32Rate >= SDH_CLK_DIV0_MAX)
        {
            u32Rate = SDH_CLK_DIV0_MAX;
        }

        /* --- calculate the second divider CLKDIV0[SDHOST_N] */
        if (u32Rate == 0UL)
        {
            u32Div1 = 0UL;
        }
        else
        {
            u32Div1 = ((u32Rate - 1UL) & 0xFFUL);
        }

        /* --- setup register */
        /* M2354 is only support SDH0 */
        CLK->CLKDIV0 &= ~CLK_CLKDIV0_SDH0DIV_Msk;
        CLK->CLKDIV0 |= (u32Div1 << CLK_CLKDIV0_SDH0DIV_Pos);
    }
}

uint32_t SDH_CardDetection(SDH_T *sdh)
{
    uint32_t i, u32Status = (uint32_t)TRUE;
    SDH_INFO_T *pSD;

    /* M2354 is only support SDH0 */
    pSD = &SD0;

    if (sdh->INTEN & SDH_INTEN_CDSRC_Msk)  /* Card detect pin from GPIO */
    {
        if (sdh->INTSTS & SDH_INTSTS_CDSTS_Msk)  /* Card remove */
        {
            pSD->IsCardInsert = (uint8_t)FALSE;
            u32Status = (uint32_t)FALSE;
        }
        else
        {
            pSD->IsCardInsert = (uint8_t)TRUE;
        }
    }
    else if (!(sdh->INTEN & SDH_INTEN_CDSRC_Msk))
    {
        sdh->CTL |= SDH_CTL_CLKKEEP_Msk;
        for (i = 0UL; i < 5000UL; i++) {}

        if (sdh->INTSTS & SDH_INTSTS_CDSTS_Msk) /* Card insert */
        {
            pSD->IsCardInsert = (uint8_t)TRUE;
        }
        else
        {
            pSD->IsCardInsert = (uint8_t)FALSE;
            u32Status = (uint32_t)FALSE;
        }

        sdh->CTL &= ~SDH_CTL_CLKKEEP_Msk;
    }

    return u32Status;
}


/* Initial */
uint32_t SDH_Init(SDH_T *sdh)
{
    uint32_t volatile i, u32Status;
    uint32_t u32Resp;
    uint32_t au32CIDBuffer[4];
    uint32_t volatile u32CmdTimeOut;
    SDH_INFO_T *pSD;

    /* M2354 is only support SDH0 */
    pSD = &SD0;

    /* set the clock to 300KHz */
    SDH_Set_clock(sdh, 300UL);

    /* power ON 74 clock */
    sdh->CTL |= SDH_CTL_CLK74OEN_Msk;

    while (sdh->CTL & SDH_CTL_CLK74OEN_Msk)
    {
        if (pSD->IsCardInsert == (uint8_t)FALSE)
        {
            return SDH_NO_SD_CARD;
        }
    }

    SDH_SDCommand(sdh, 0UL, 0UL);        /* reset all cards */
    for (i = 0x1000UL; i > 0UL; i--) {}

    /* initial SDHC */
    _SDH_uR7_CMD = 1UL;
    u32CmdTimeOut = 0xFFFFFUL;

    i = SDH_SDCmdAndRsp(sdh, 8UL, 0x00000155UL, u32CmdTimeOut);
    if (i == Successful)
    {
        /* SD 2.0 */
        SDH_SDCmdAndRsp(sdh, 55UL, 0x00UL, u32CmdTimeOut);
        g_u8R3Flag = 1UL;
        SDH_SDCmdAndRsp(sdh, 41UL, 0x40ff8000UL, u32CmdTimeOut); /* 2.7v-3.6v */
        u32Resp = sdh->RESP0;

        while (!(u32Resp & 0x00800000UL))        /* check if card is ready */
        {
            SDH_SDCmdAndRsp(sdh, 55UL, 0x00UL, u32CmdTimeOut);
            g_u8R3Flag = 1UL;
            SDH_SDCmdAndRsp(sdh, 41UL, 0x40ff8000UL, u32CmdTimeOut); /* 3.0v-3.4v */
            u32Resp = sdh->RESP0;
        }
        if (u32Resp & 0x00400000UL)
        {
            pSD->CardType = SDH_TYPE_SD_HIGH;
        }
        else
        {
            pSD->CardType = SDH_TYPE_SD_LOW;
        }
    }
    else
    {
        /* SD 1.1 */
        SDH_SDCommand(sdh, 0UL, 0UL);        /* reset all cards */
        for (i = 0x100UL; i > 0UL; i--) {}

        i = SDH_SDCmdAndRsp(sdh, 55UL, 0x00UL, u32CmdTimeOut);
        if (i == 2UL)     /* MMC memory */
        {
            SDH_SDCommand(sdh, 0UL, 0UL);        /* reset */
            for (i = 0x100UL; i > 0UL; i--) {}

            g_u8R3Flag = 1UL;

            if (SDH_SDCmdAndRsp(sdh, 1UL, 0x40ff8000UL, u32CmdTimeOut) != 2UL)    /* eMMC memory */
            {
                u32Resp = sdh->RESP0;
                while (!(u32Resp & 0x00800000UL))        /* check if card is ready */
                {
                    g_u8R3Flag = 1UL;

                    SDH_SDCmdAndRsp(sdh, 1UL, 0x40ff8000UL, u32CmdTimeOut);      /* high voltage */
                    u32Resp = sdh->RESP0;
                }

                if (u32Resp & 0x00400000UL)
                {
                    pSD->CardType = SDH_TYPE_EMMC;
                }
                else
                {
                    pSD->CardType = SDH_TYPE_MMC;
                }
            }
            else
            {
                pSD->CardType = SDH_TYPE_UNKNOWN;
                return SDH_ERR_DEVICE;
            }
        }
        else if (i == 0UL)     /* SD Memory */
        {
            g_u8R3Flag = 1UL;
            SDH_SDCmdAndRsp(sdh, 41UL, 0x00ff8000UL, u32CmdTimeOut); /* 3.0v-3.4v */
            u32Resp = sdh->RESP0;
            while (!(u32Resp & 0x00800000UL))        /* check if card is ready */
            {
                SDH_SDCmdAndRsp(sdh, 55UL, 0x00UL, u32CmdTimeOut);
                g_u8R3Flag = 1UL;
                SDH_SDCmdAndRsp(sdh, 41UL, 0x00ff8000UL, u32CmdTimeOut); /* 3.0v-3.4v */
                u32Resp = sdh->RESP0;
            }
            pSD->CardType = SDH_TYPE_SD_LOW;
        }
        else
        {
            pSD->CardType = SDH_TYPE_UNKNOWN;
            return SDH_INIT_ERROR;
        }
    }

    /* CMD2, CMD3 */
    if (pSD->CardType != SDH_TYPE_UNKNOWN)
    {
        SDH_SDCmdAndRsp2(sdh, 2UL, 0x00UL, au32CIDBuffer);
        if ((pSD->CardType == SDH_TYPE_MMC) || (pSD->CardType == SDH_TYPE_EMMC))
        {
            if ((u32Status = SDH_SDCmdAndRsp(sdh, 3UL, 0x10000UL, 0UL)) != Successful)        /* set RCA */
            {
                return u32Status;
            }
            pSD->RCA = 0x10000UL;
        }
        else
        {
            if ((u32Status = SDH_SDCmdAndRsp(sdh, 3UL, 0x00UL, 0UL)) != Successful)       /* get RCA */
            {
                return u32Status;
            }
            else
            {
                pSD->RCA = (sdh->RESP0 << 8) & 0xffff0000UL;
            }
        }
    }

    return Successful;
}


uint32_t SDH_SwitchToHighSpeed(SDH_T *sdh, SDH_INFO_T *pSD)
{
    uint32_t volatile u32Status = 0UL;
    uint16_t u16CurrentComsumption, u16BusyStatus0;

    (void)pSD;
    sdh->DMASA = (uint32_t)_SDH_ucSDHCBuffer;    /* set DMA transfer starting address */
    sdh->BLEN = 63UL;    /* 512 bit */

    if ((u32Status = SDH_SDCmdAndRspDataIn(sdh, 6UL, 0x00ffff01UL)) != Successful)
    {
        return Fail;
    }

    u16CurrentComsumption = (uint16_t)(_SDH_ucSDHCBuffer[0] << 8);
    u16CurrentComsumption |= (uint16_t)_SDH_ucSDHCBuffer[1];
    if (!u16CurrentComsumption)
    {
        return Fail;
    }

    u16BusyStatus0 = (uint16_t)(_SDH_ucSDHCBuffer[28] << 8);
    u16BusyStatus0 |= (uint16_t)_SDH_ucSDHCBuffer[29];

    if (!u16BusyStatus0)   /* function ready */
    {
        sdh->DMASA = (uint32_t)_SDH_ucSDHCBuffer;        /* set DMA transfer starting address */
        sdh->BLEN = 63UL;    /* 512 bit */

        if ((u32Status = SDH_SDCmdAndRspDataIn(sdh, 6UL, 0x80ffff01UL)) != Successful)
        {
            return Fail;
        }

        /* function change timing: 8 clocks */
        sdh->CTL |= SDH_CTL_CLK8OEN_Msk;
        while (sdh->CTL & SDH_CTL_CLK8OEN_Msk) {}

        u16CurrentComsumption = (uint16_t)(_SDH_ucSDHCBuffer[0] << 8);
        u16CurrentComsumption |= (uint16_t)_SDH_ucSDHCBuffer[1];
        if (!u16CurrentComsumption)
        {
            return Fail;
        }

        return Successful;
    }
    else
    {
        return Fail;
    }
}


uint32_t SDH_SelectCardType(SDH_T *sdh)
{
    uint32_t volatile u32Status = 0UL;
    uint32_t u32Param;
    SDH_INFO_T *pSD;

    /* M2354 is only support SDH0 */
    pSD = &SD0;

    if ((u32Status = SDH_SDCmdAndRsp(sdh, 7UL, pSD->RCA, 0UL)) != Successful)
    {
        return u32Status;
    }

    SDH_CheckRB(sdh);

    /* if SD card set 4bit */
    if (pSD->CardType == SDH_TYPE_SD_HIGH)
    {
        sdh->DMASA = (uint32_t)_SDH_ucSDHCBuffer;    /* set DMA transfer starting address */
        sdh->BLEN = 0x07UL;  /* 64 bit */

        if ((u32Status = SDH_SDCmdAndRsp(sdh, 55UL, pSD->RCA, 0UL)) != Successful)
        {
            return u32Status;
        }

        sdh->DMACTL |= 0x2;
        while (sdh->DMACTL & 0x2) {}

        if ((u32Status = SDH_SDCmdAndRspDataIn(sdh, 51UL, 0x00UL)) != Successful)
        {
            return u32Status;
        }

        if ((_SDH_ucSDHCBuffer[0] & 0xfUL) == 0xfUL)
        {
            u32Status = SDH_SwitchToHighSpeed(sdh, pSD);
            if (u32Status == Successful)
            {
                /* divider */
                SDH_Set_clock(sdh, SDHC_FREQ);
            }
        }

        if ((u32Status = SDH_SDCmdAndRsp(sdh, 55UL, pSD->RCA, 0UL)) != Successful)
        {
            return u32Status;
        }
        if ((u32Status = SDH_SDCmdAndRsp(sdh, 6UL, 0x02UL, 0UL)) != Successful)   /* set bus width */
        {
            return u32Status;
        }

        sdh->CTL |= SDH_CTL_DBW_Msk;
    }
    else if (pSD->CardType == SDH_TYPE_SD_LOW)
    {
        sdh->DMASA = (uint32_t) _SDH_ucSDHCBuffer; /* set DMA transfer starting address */
        sdh->BLEN = 0x07UL;  /* 64 bit */

        if ((u32Status = SDH_SDCmdAndRsp(sdh, 55UL, pSD->RCA, 0UL)) != Successful)
        {
            return u32Status;
        }
        if ((u32Status = SDH_SDCmdAndRspDataIn(sdh, 51UL, 0x00UL)) != Successful)
        {
            return u32Status;
        }

        /* set data bus width. ACMD6 for SD card, SDCR_DBW for host. */
        if ((u32Status = SDH_SDCmdAndRsp(sdh, 55UL, pSD->RCA, 0UL)) != Successful)
        {
            return u32Status;
        }

        if ((u32Status = SDH_SDCmdAndRsp(sdh, 6UL, 0x02UL, 0UL)) != Successful)   /* set bus width */
        {
            return u32Status;
        }

        sdh->CTL |= SDH_CTL_DBW_Msk;
    }
    else if ((pSD->CardType == SDH_TYPE_MMC) || (pSD->CardType == SDH_TYPE_EMMC))
    {

        if (pSD->CardType == SDH_TYPE_MMC)
        {
            sdh->CTL &= ~SDH_CTL_DBW_Msk;
        }

        /* --- sent CMD6 to MMC card to set bus width to 4 bits mode */
        /* set CMD6 argument Access field to 3, Index to 183, Value to 1 (4-bit mode) */
        u32Param = (3UL << 24) | (183UL << 16) | (1UL << 8);
        if ((u32Status = SDH_SDCmdAndRsp(sdh, 6UL, u32Param, 0UL)) != Successful)
        {
            return u32Status;
        }
        SDH_CheckRB(sdh);

        sdh->CTL |= SDH_CTL_DBW_Msk; /* set bus width to 4-bit mode for SD host controller */
    }

    if ((u32Status = SDH_SDCmdAndRsp(sdh, 16UL, SDH_BLOCK_SIZE, 0UL)) != Successful) /* set block length */
    {
        return u32Status;
    }
    sdh->BLEN = SDH_BLOCK_SIZE - 1UL;           /* set the block size */

    SDH_SDCommand(sdh, 7UL, 0UL);
    sdh->CTL |= SDH_CTL_CLK8OEN_Msk;
    while (sdh->CTL & SDH_CTL_CLK8OEN_Msk) {}

    sdh->INTEN |= SDH_INTEN_BLKDIEN_Msk;

    return Successful;
}

void SDH_Get_SD_info(SDH_T *sdh)
{
    uint32_t u32RLen, u32CSize, u32Mult, u32Size;
    uint32_t au32Buffer[4];
    SDH_INFO_T *pSD;

    /* M2354 is only support SDH0 */
    pSD = &SD0;

    SDH_SDCmdAndRsp2(sdh, 9UL, pSD->RCA, au32Buffer);

    if ((pSD->CardType == SDH_TYPE_MMC) || (pSD->CardType == SDH_TYPE_EMMC))
    {
        /* for MMC/eMMC card */
        if ((au32Buffer[0] & 0xc0000000UL) == 0xc0000000UL)
        {
            /* CSD_STRUCTURE [127:126] is 3 */
            /* CSD version depend on EXT_CSD register in eMMC v4.4 for card size > 2GB */
            SDH_SDCmdAndRsp(sdh, 7UL, pSD->RCA, 0UL);

            sdh->DMASA = (uint32_t)_SDH_ucSDHCBuffer;  /* set DMA transfer starting address */
            sdh->BLEN = 511UL;  /* read 512 bytes for EXT_CSD */

            if (SDH_SDCmdAndRspDataIn(sdh, 8UL, 0x00UL) != Successful)
            {
                return;
            }

            SDH_SDCommand(sdh, 7UL, 0UL);
            sdh->CTL |= SDH_CTL_CLK8OEN_Msk;
            while (sdh->CTL & SDH_CTL_CLK8OEN_Msk) {}

            pSD->totalSectorN = (uint32_t)_SDH_ucSDHCBuffer[215] << 24;
            pSD->totalSectorN |= (uint32_t)_SDH_ucSDHCBuffer[214] << 16;
            pSD->totalSectorN |= (uint32_t)_SDH_ucSDHCBuffer[213] << 8;
            pSD->totalSectorN |= (uint32_t)_SDH_ucSDHCBuffer[212];
            pSD->diskSize = pSD->totalSectorN / 2UL;
        }
        else
        {
            /* CSD version v1.0/1.1/1.2 in eMMC v4.4 spec for card size <= 2GB */
            u32RLen = (au32Buffer[1] & 0x000f0000UL) >> 16;
            u32CSize = ((au32Buffer[1] & 0x000003ffUL) << 2) | ((au32Buffer[2] & 0xc0000000UL) >> 30);
            u32Mult = (au32Buffer[2] & 0x00038000UL) >> 15;
            u32Size = (u32CSize + 1UL) * (1UL << (u32Mult + 2UL)) * (1UL << u32RLen);

            pSD->diskSize = u32Size / 1024UL;
            pSD->totalSectorN = u32Size / 512UL;
        }
    }
    else
    {
        if (au32Buffer[0] & 0xc0000000UL)
        {
            u32CSize = ((au32Buffer[1] & 0x0000003fUL) << 16) | ((au32Buffer[2] & 0xffff0000UL) >> 16);
            u32Size = (u32CSize + 1UL) * 512UL;  /* Kbytes */

            pSD->diskSize = u32Size;
            pSD->totalSectorN = u32Size << 1;
        }
        else
        {
            u32RLen = (au32Buffer[1] & 0x000f0000UL) >> 16;
            u32CSize = ((au32Buffer[1] & 0x000003ffUL) << 2) | ((au32Buffer[2] & 0xc0000000UL) >> 30);
            u32Mult = (au32Buffer[2] & 0x00038000UL) >> 15;
            u32Size = (u32CSize + 1UL) * (1UL << (u32Mult + 2UL)) * (1UL << u32RLen);

            pSD->diskSize = u32Size / 1024UL;
            pSD->totalSectorN = u32Size / 512UL;
        }
    }
    pSD->sectorSize = (int)512UL;
}

/** @endcond HIDDEN_SYMBOLS */


/**
 *  @brief  This function use to reset SD function and select card detection source and pin.
 *
 *  @param[in]  sdh    The pointer of the specified SDH module.
 *  @param[in]  u32CardDetSrc   Select card detection pin from GPIO or DAT3 pin. ( \ref CardDetect_From_GPIO / \ref CardDetect_From_DAT3)
 *
 *  @return None
 */
void SDH_Open(SDH_T *sdh, uint32_t u32CardDetSrc)
{
    /* enable DMAC */
    sdh->DMACTL = SDH_DMACTL_DMARST_Msk;
    while (sdh->DMACTL & SDH_DMACTL_DMARST_Msk) {}

    sdh->DMACTL = SDH_DMACTL_DMAEN_Msk;

    /* Reset FMI */
    sdh->GCTL = SDH_GCTL_GCTLRST_Msk | SDH_GCTL_SDEN_Msk;        /* Start reset FMI controller. */
    while (sdh->GCTL & SDH_GCTL_GCTLRST_Msk) {}

    memset(&SD0, 0, sizeof(SDH_INFO_T));

    /* enable SD */
    sdh->GCTL = SDH_GCTL_SDEN_Msk;

    if (u32CardDetSrc & CardDetect_From_DAT3)
    {
        sdh->INTEN &= ~SDH_INTEN_CDSRC_Msk;
    }
    else
    {
        sdh->INTEN |= SDH_INTEN_CDSRC_Msk;
    }
    sdh->INTEN |= SDH_INTEN_CDIEN_Msk;

    sdh->CTL |= SDH_CTL_CTLRST_Msk;     /* SD software reset */
    while (sdh->CTL & SDH_CTL_CTLRST_Msk) {}

}

/**
 *  @brief  This function use to initial SD card.
 *
 *  @param[in]    sdh    The pointer of the specified SDH module.
 *
 *  @return None
 *
 *  @details This function is used to initial SD card.
 *           SD initial state needs 400KHz clock output, driver will use HIRC for SD initial clock source.
 *           And then switch back to the user's setting.
 */
uint32_t SDH_Probe(SDH_T *sdh)
{
    uint32_t u32Val;

    /* Disable FMI/SD host interrupt */
    sdh->GINTEN = 0UL;

    sdh->CTL &= ~SDH_CTL_SDNWR_Msk;
    sdh->CTL |=  0x09UL << SDH_CTL_SDNWR_Pos;         /* set SDNWR = 9 */
    sdh->CTL &= ~SDH_CTL_BLKCNT_Msk;
    sdh->CTL |=  0x01UL << SDH_CTL_BLKCNT_Pos;           /* set BLKCNT = 1 */
    sdh->CTL &= ~SDH_CTL_DBW_Msk;               /* SD 1-bit data bus */

    if (!(SDH_CardDetection(sdh)))
    {
        return SDH_NO_SD_CARD;
    }

    if ((u32Val = SDH_Init(sdh)) != 0UL)
    {
        return u32Val;
    }

    /* divider */
    if (SD0.CardType == SDH_TYPE_MMC)
    {
        SDH_Set_clock(sdh, MMC_FREQ);
    }
    else
    {
        SDH_Set_clock(sdh, SD_FREQ);
    }
    SDH_Get_SD_info(sdh);

    if ((u32Val = SDH_SelectCardType(sdh)) != 0UL)
    {
        return u32Val;
    }

    return 0UL;
}

/**
 *  @brief  This function use to read data from SD card.
 *
 *  @param[in]     sdh           The pointer of the specified SDH module.
 *  @param[out]    pu8BufAddr    The buffer to receive the data from SD card.
 *  @param[in]     u32StartSec   The start read sector address.
 *  @param[in]     u32SecCount   The the read sector number of data
 *
 *  @return None
 */
uint32_t SDH_Read(SDH_T *sdh, uint8_t *pu8BufAddr, uint32_t u32StartSec, uint32_t u32SecCount)
{
    uint32_t volatile u32IsSendCmd = (uint32_t)FALSE;
    uint32_t volatile u32Reg;
    uint32_t volatile u32Loop, u32Status;
    uint32_t u32BlkSize = SDH_BLOCK_SIZE;

    SDH_INFO_T *pSD;

    /* M2354 is only support SDH0 */
    pSD = &SD0;

    /* --- check input parameters */
    if (u32SecCount == 0UL)
    {
        return SDH_SELECT_ERROR;
    }

    if ((u32Status = SDH_SDCmdAndRsp(sdh, 7UL, pSD->RCA, 0UL)) != Successful)
    {
        return u32Status;
    }
    SDH_CheckRB(sdh);

    sdh->BLEN = u32BlkSize - 1UL;       /* the actual byte count is equal to (SDBLEN+1) */

    if ((pSD->CardType == SDH_TYPE_SD_HIGH) || (pSD->CardType == SDH_TYPE_EMMC))
    {
        sdh->CMDARG = u32StartSec;
    }
    else
    {
        sdh->CMDARG = u32StartSec * u32BlkSize;
    }

    sdh->DMASA = (uint32_t)pu8BufAddr;

    u32Loop = u32SecCount / 255UL;
    while (u32Loop > 0UL)
    {
        g_u8SDDataReadyFlag = (uint8_t)FALSE;
        u32Reg = sdh->CTL & ~SDH_CTL_CMDCODE_Msk;
        u32Reg = u32Reg | 0xff0000UL;   /* set BLK_CNT to 255 */
        if (u32IsSendCmd == (uint32_t)FALSE)
        {
            sdh->CTL = u32Reg | (18UL << 8) | (SDH_CTL_COEN_Msk | SDH_CTL_RIEN_Msk | SDH_CTL_DIEN_Msk);
            u32IsSendCmd = (uint32_t)TRUE;
        }
        else
        {
            sdh->CTL = u32Reg | SDH_CTL_DIEN_Msk;
        }

        while (!g_u8SDDataReadyFlag)
        {
            if (g_u8SDDataReadyFlag)
            {
                break;
            }
            if (pSD->IsCardInsert == (uint8_t)FALSE)
            {
                return SDH_NO_SD_CARD;
            }
        }

        if (!(sdh->INTSTS & SDH_INTSTS_CRC7_Msk))    /* check CRC7 */
        {
            return SDH_CRC7_ERROR;
        }

        if (!(sdh->INTSTS & SDH_INTSTS_CRC16_Msk))   /* check CRC16 */
        {
            return SDH_CRC16_ERROR;
        }
        u32Loop--;
    }

    u32Loop = u32SecCount % 255UL;
    if (u32Loop != 0UL)
    {
        uint32_t u32RegTmp;
        g_u8SDDataReadyFlag = (uint8_t)FALSE;
        u32Reg = sdh->CTL & (~SDH_CTL_CMDCODE_Msk);
        u32Reg = u32Reg & (~SDH_CTL_BLKCNT_Msk);
        u32RegTmp = (u32Loop << 16);
        u32Reg |= u32RegTmp;    /* setup SDCR_BLKCNT */

        if (u32IsSendCmd == (uint32_t)FALSE)
        {
            sdh->CTL = u32Reg | (18UL << 8) | (SDH_CTL_COEN_Msk | SDH_CTL_RIEN_Msk | SDH_CTL_DIEN_Msk);
            u32IsSendCmd = (uint32_t)TRUE;
        }
        else
        {
            sdh->CTL = u32Reg | SDH_CTL_DIEN_Msk;
        }

        while (!g_u8SDDataReadyFlag)
        {
            if (pSD->IsCardInsert == (uint8_t)FALSE)
            {
                return SDH_NO_SD_CARD;
            }
        }

        if (!(sdh->INTSTS & SDH_INTSTS_CRC7_Msk))    /* check CRC7 */
        {
            return SDH_CRC7_ERROR;
        }

        if (!(sdh->INTSTS & SDH_INTSTS_CRC16_Msk))    /* check CRC16 */
        {
            return SDH_CRC16_ERROR;
        }
    }

    if (SDH_SDCmdAndRsp(sdh, 12UL, 0UL, 0UL))    /* stop command */
    {
        return SDH_CRC7_ERROR;
    }
    SDH_CheckRB(sdh);

    SDH_SDCommand(sdh, 7UL, 0UL);
    sdh->CTL |= SDH_CTL_CLK8OEN_Msk;
    while (sdh->CTL & SDH_CTL_CLK8OEN_Msk) {}

    return Successful;
}

/**
 *  @brief  This function use to write data to SD card.
 *
 *  @param[in]    sdh           The pointer of the specified SDH module.
 *  @param[in]    pu8BufAddr    The buffer to send the data to SD card.
 *  @param[in]    u32StartSec   The start write sector address.
 *  @param[in]    u32SecCount   The the write sector number of data.
 *
 *  @return   \ref SDH_SELECT_ERROR : u32SecCount is zero. \n
 *            \ref SDH_NO_SD_CARD : SD card be removed. \n
 *            \ref SDH_CRC_ERROR : CRC error happen. \n
 *            \ref SDH_CRC7_ERROR : CRC7 error happen. \n
 *            \ref Successful : Write data to SD card success.
 */
uint32_t SDH_Write(SDH_T *sdh, uint8_t *pu8BufAddr, uint32_t u32StartSec, uint32_t u32SecCount)
{
    uint32_t volatile u32IsSendCmd = (uint32_t)FALSE;
    uint32_t volatile u32Reg;
    uint32_t volatile u32Loop, u32Status;

    SDH_INFO_T *pSD;

    /* M2354 is only support SDH0 */
    pSD = &SD0;

    /* --- check input parameters */
    if (u32SecCount == 0UL)
    {
        return SDH_SELECT_ERROR;
    }

    if ((u32Status = SDH_SDCmdAndRsp(sdh, 7UL, pSD->RCA, 0UL)) != Successful)
    {
        return u32Status;
    }

    SDH_CheckRB(sdh);

    /* According to SD Spec v2.0, the write CMD block size MUST be 512, and the start address MUST be 512*n. */
    sdh->BLEN = SDH_BLOCK_SIZE - 1UL;           /* set the block size */

    if ((pSD->CardType == SDH_TYPE_SD_HIGH) || (pSD->CardType == SDH_TYPE_EMMC))
    {
        sdh->CMDARG = u32StartSec;
    }
    else
    {
        sdh->CMDARG = u32StartSec * SDH_BLOCK_SIZE;  /* set start address for SD CMD */
    }

    sdh->DMASA = (uint32_t)pu8BufAddr;
    u32Loop = u32SecCount / 255UL;   /* the maximum block count is 0xFF=255 for register SDCR[BLK_CNT] */
    while (u32Loop > 0UL)
    {
        g_u8SDDataReadyFlag = (uint8_t)FALSE;
        u32Reg = sdh->CTL & 0xff00c080UL;
        u32Reg = u32Reg | 0xff0000UL;   /* set BLK_CNT to 0xFF=255 */
        if (!u32IsSendCmd)
        {
            sdh->CTL = u32Reg | (25UL << 8) | (SDH_CTL_COEN_Msk | SDH_CTL_RIEN_Msk | SDH_CTL_DOEN_Msk);
            u32IsSendCmd = (uint32_t)TRUE;
        }
        else
        {
            sdh->CTL = u32Reg | SDH_CTL_DOEN_Msk;
        }

        while (!g_u8SDDataReadyFlag)
        {
            if (pSD->IsCardInsert == (uint8_t)FALSE)
            {
                return SDH_NO_SD_CARD;
            }
        }

        if ((sdh->INTSTS & SDH_INTSTS_CRCIF_Msk) != 0UL)     /* check CRC */
        {
            sdh->INTSTS = SDH_INTSTS_CRCIF_Msk;
            return SDH_CRC_ERROR;
        }
        u32Loop--;
    }

    u32Loop = u32SecCount % 255UL;
    if (u32Loop != 0UL)
    {
        uint32_t u32RegTmp;
        g_u8SDDataReadyFlag = (uint8_t)FALSE;
        u32RegTmp = (u32Loop << 16);
        u32Reg = (sdh->CTL & 0xff00c080UL) | u32RegTmp;
        if (!u32IsSendCmd)
        {
            sdh->CTL = u32Reg | (25UL << 8) | (SDH_CTL_COEN_Msk | SDH_CTL_RIEN_Msk | SDH_CTL_DOEN_Msk);
            u32IsSendCmd = (uint32_t)TRUE;
        }
        else
        {
            sdh->CTL = u32Reg | SDH_CTL_DOEN_Msk;
        }

        while (!g_u8SDDataReadyFlag)
        {
            if (pSD->IsCardInsert == (uint8_t)FALSE)
            {
                return SDH_NO_SD_CARD;
            }
        }

        if ((sdh->INTSTS & SDH_INTSTS_CRCIF_Msk) != 0UL)     /* check CRC */
        {
            sdh->INTSTS = SDH_INTSTS_CRCIF_Msk;
            return SDH_CRC_ERROR;
        }
    }
    sdh->INTSTS = SDH_INTSTS_CRCIF_Msk;

    if (SDH_SDCmdAndRsp(sdh, 12UL, 0UL, 0UL))      /* stop command */
    {
        return SDH_CRC7_ERROR;
    }
    SDH_CheckRB(sdh);

    SDH_SDCommand(sdh, 7UL, 0UL);
    sdh->CTL |= SDH_CTL_CLK8OEN_Msk;
    while (sdh->CTL & SDH_CTL_CLK8OEN_Msk) {}

    return Successful;
}


/**@}*/ /* end of group SDH_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group SDH_Driver */

/**@}*/ /* end of group Standard_Driver */

