/**************************************************************************//**
 * @file     SDH.c
 * @version  V1.00
 * @brief    M480 SDH driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SDH_Driver SDH Driver
  @{
*/


/** @addtogroup SDH_EXPORTED_FUNCTIONS SDH Exported Functions
  @{
*/
#define SDH_BLOCK_SIZE   512ul

/** @cond HIDDEN_SYMBOLS */

/* global variables */
/* For response R3 (such as ACMD41, CRC-7 is invalid; but SD controller will still */
/* calculate CRC-7 and get an error result, software should ignore this error and clear SDISR [CRC_IF] flag */
/* _sd_uR3_CMD is the flag for it. 1 means software should ignore CRC-7 error */

static uint32_t _SDH0_ReferenceClock, _SDH1_ReferenceClock;

#ifdef __ICCARM__
#pragma data_alignment = 4
static uint8_t _SDH0_ucSDHCBuffer[512];
static uint8_t _SDH1_ucSDHCBuffer[512];
#else
static uint8_t _SDH0_ucSDHCBuffer[512] __attribute__((aligned(4)));
static uint8_t _SDH1_ucSDHCBuffer[512] __attribute__((aligned(4)));
#endif

SDH_INFO_T SD0, SD1;

void SDH_CheckRB(SDH_T *sdh)
{
    while(1)
    {
        sdh->CTL |= SDH_CTL_CLK8OEN_Msk;
        while ((sdh->CTL & SDH_CTL_CLK8OEN_Msk) == SDH_CTL_CLK8OEN_Msk)
        {
        }
        if ((sdh->INTSTS & SDH_INTSTS_DAT0STS_Msk) == SDH_INTSTS_DAT0STS_Msk)
        {
            break;
        }
    }
}


uint32_t SDH_SDCommand(SDH_T *sdh, uint32_t ucCmd, uint32_t uArg)
{
    volatile uint32_t buf, val = 0ul;
    SDH_INFO_T *pSD;

    if (sdh == SDH0)
    {
        pSD = &SD0;
    }
    else
    {
        pSD = &SD1;
    }

    sdh->CMDARG = uArg;
    buf = (sdh->CTL&(~SDH_CTL_CMDCODE_Msk))|(ucCmd << 8ul)|(SDH_CTL_COEN_Msk);
    sdh->CTL = buf;

    while ((sdh->CTL & SDH_CTL_COEN_Msk) == SDH_CTL_COEN_Msk)
    {
        if (pSD->IsCardInsert == 0ul)
        {
            val = SDH_NO_SD_CARD;
        }
    }
    return val;
}


uint32_t SDH_SDCmdAndRsp(SDH_T *sdh, uint32_t ucCmd, uint32_t uArg, uint32_t ntickCount)
{
    volatile uint32_t buf;
    SDH_INFO_T *pSD;

    if (sdh == SDH0)
    {
        pSD = &SD0;
    }
    else
    {
        pSD = &SD1;
    }

    sdh->CMDARG = uArg;
    buf = (sdh->CTL & (~SDH_CTL_CMDCODE_Msk)) | (ucCmd << 8ul) | (SDH_CTL_COEN_Msk | SDH_CTL_RIEN_Msk);
    sdh->CTL = buf;

    if (ntickCount > 0ul)
    {
        while ((sdh->CTL & SDH_CTL_RIEN_Msk) == SDH_CTL_RIEN_Msk)
        {
            if(ntickCount-- == 0ul)
            {
                sdh->CTL |= SDH_CTL_CTLRST_Msk; /* reset SD engine */
                return 2ul;
            }
            if (pSD->IsCardInsert == FALSE)
            {
                return SDH_NO_SD_CARD;
            }
        }
    }
    else
    {
        while ((sdh->CTL & SDH_CTL_RIEN_Msk) == SDH_CTL_RIEN_Msk)
        {
            if (pSD->IsCardInsert == FALSE)
            {
                return SDH_NO_SD_CARD;
            }
        }
    }

    if (pSD->R7Flag)
    {
        uint32_t tmp0 = 0ul, tmp1= 0ul;
        tmp1 = sdh->RESP1 & 0xfful;
        tmp0 = sdh->RESP0 & 0xful;
        if ((tmp1 != 0x55ul) && (tmp0 != 0x01ul))
        {
            pSD->R7Flag = 0ul;
            return SDH_CMD8_ERROR;
        }
    }

    if (!pSD->R3Flag)
    {
        if ((sdh->INTSTS & SDH_INTSTS_CRC7_Msk) == SDH_INTSTS_CRC7_Msk)     /* check CRC7 */
        {
            return Successful;
        }
        else
        {
            return SDH_CRC7_ERROR;
        }
    }
    else
    {
        /* ignore CRC error for R3 case */
        pSD->R3Flag = 0ul;
        sdh->INTSTS = SDH_INTSTS_CRCIF_Msk;
        return Successful;
    }
}


uint32_t SDH_Swap32(uint32_t val)
{
    uint32_t buf;

    buf = val;
    val <<= 24;
    val |= (buf<<8) & 0xff0000ul;
    val |= (buf>>8) & 0xff00ul;
    val |= (buf>>24)& 0xfful;
    return val;
}

/* Get 16 bytes CID or CSD */
uint32_t SDH_SDCmdAndRsp2(SDH_T *sdh, uint32_t ucCmd, uint32_t uArg, uint32_t puR2ptr[])
{
    uint32_t i, buf;
    uint32_t tmpBuf[5];
    SDH_INFO_T *pSD;

    if (sdh == SDH0)
    {
        pSD = &SD0;
    }
    else
    {
        pSD = &SD1;
    }

    sdh->CMDARG = uArg;
    buf = (sdh->CTL&(~SDH_CTL_CMDCODE_Msk))|(ucCmd << 8)|(SDH_CTL_COEN_Msk | SDH_CTL_R2EN_Msk);
    sdh->CTL = buf;

    while ((sdh->CTL & SDH_CTL_R2EN_Msk) == SDH_CTL_R2EN_Msk)
    {
        if (pSD->IsCardInsert == FALSE)
        {
            return SDH_NO_SD_CARD;
        }
    }

    if ((sdh->INTSTS & SDH_INTSTS_CRC7_Msk) == SDH_INTSTS_CRC7_Msk)
    {
        for (i=0ul; i<5ul; i++)
        {
            tmpBuf[i] = SDH_Swap32(sdh->FB[i]);
        }
        for (i=0ul; i<4ul; i++)
        {
            puR2ptr[i] = ((tmpBuf[i] & 0x00fffffful)<<8) | ((tmpBuf[i+1ul] & 0xff000000ul)>>24);
        }
    }
    else
    {
        return SDH_CRC7_ERROR;
    }
    return Successful;
}


uint32_t SDH_SDCmdAndRspDataIn(SDH_T *sdh, uint32_t ucCmd, uint32_t uArg)
{
    volatile uint32_t buf;
    SDH_INFO_T *pSD;

    if (sdh == SDH0)
    {
        pSD = &SD0;
    }
    else
    {
        pSD = &SD1;
    }

    sdh->CMDARG = uArg;
    buf = (sdh->CTL & (~SDH_CTL_CMDCODE_Msk))|(ucCmd << 8ul)|
          (SDH_CTL_COEN_Msk | SDH_CTL_RIEN_Msk | SDH_CTL_DIEN_Msk);

    sdh->CTL = buf;

    while ((sdh->CTL & SDH_CTL_RIEN_Msk) == SDH_CTL_RIEN_Msk)
    {
        if (pSD->IsCardInsert == FALSE)
        {
            return SDH_NO_SD_CARD;
        }
    }

    while ((sdh->CTL & SDH_CTL_DIEN_Msk) == SDH_CTL_DIEN_Msk)
    {
        if (pSD->IsCardInsert == FALSE)
        {
            return SDH_NO_SD_CARD;
        }
    }

    if ((sdh->INTSTS & SDH_INTSTS_CRC7_Msk) != SDH_INTSTS_CRC7_Msk)
    {
        /* check CRC7 */
        return SDH_CRC7_ERROR;
    }

    if ((sdh->INTSTS & SDH_INTSTS_CRC16_Msk) != SDH_INTSTS_CRC16_Msk)
    {
        /* check CRC16 */
        return SDH_CRC16_ERROR;
    }
    return 0ul;
}

/* there are 8 bits for divider0, maximum is 256 */
#define SDH_CLK_DIV0_MAX     256ul

void SDH_Set_clock(SDH_T *sdh, uint32_t sd_clock_khz)
{
    uint32_t rate, div1;
    static uint32_t u32SD_ClkSrc = 0ul, u32SD_PwrCtl = 0ul;

    SYS_UnlockReg();

    /* initial state, clock source use HIRC */
    if (sd_clock_khz <= 400ul)
    {
        u32SD_PwrCtl = CLK->PWRCTL;
        if ((u32SD_PwrCtl & CLK_PWRCTL_HIRCEN_Msk) != 0x4ul)
        {
            CLK->PWRCTL |= CLK_PWRCTL_HIRCEN_Msk;
        }

        if (sdh == SDH0)
        {
            u32SD_ClkSrc = (CLK->CLKSEL0 & CLK_CLKSEL0_SDH0SEL_Msk);
            CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_SDH0SEL_Msk) | CLK_CLKSEL0_SDH0SEL_HIRC;
            _SDH0_ReferenceClock = (__HIRC / 1000ul);
        }
        else
        {
            u32SD_ClkSrc = (CLK->CLKSEL0 & CLK_CLKSEL0_SDH1SEL_Msk);
            CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_SDH1SEL_Msk) | CLK_CLKSEL0_SDH1SEL_HIRC;
            _SDH1_ReferenceClock = (__HIRC / 1000ul);
        }
    }
    /* transfer state, clock source use sys_init() */
    else
    {
        CLK->PWRCTL = u32SD_PwrCtl;
        if (sdh == SDH0)
        {
            CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_SDH0SEL_Msk) | u32SD_ClkSrc;
            if(u32SD_ClkSrc == CLK_CLKSEL0_SDH0SEL_HXT)
            {
                _SDH0_ReferenceClock = (CLK_GetHXTFreq() / 1000ul);
            }
            else if(u32SD_ClkSrc == CLK_CLKSEL0_SDH0SEL_HIRC)
            {
                _SDH0_ReferenceClock = (__HIRC / 1000ul);
            }
            else if(u32SD_ClkSrc == CLK_CLKSEL0_SDH0SEL_PLL)
            {
                _SDH0_ReferenceClock = (CLK_GetPLLClockFreq() / 1000ul);
            }
            else if(u32SD_ClkSrc == CLK_CLKSEL0_SDH0SEL_HCLK)
            {
                _SDH0_ReferenceClock = (CLK_GetHCLKFreq() / 1000ul);
            }
        }
        else
        {
            CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_SDH1SEL_Msk) | u32SD_ClkSrc;
            if(u32SD_ClkSrc == CLK_CLKSEL0_SDH1SEL_HXT)
            {
                _SDH1_ReferenceClock = (CLK_GetHXTFreq() / 1000ul);
            }
            else if(u32SD_ClkSrc == CLK_CLKSEL0_SDH1SEL_HIRC)
            {
                _SDH1_ReferenceClock = (__HIRC / 1000ul);
            }
            else if(u32SD_ClkSrc == CLK_CLKSEL0_SDH1SEL_PLL)
            {
                _SDH1_ReferenceClock = (CLK_GetPLLClockFreq() / 1000ul);
            }
            else if(u32SD_ClkSrc == CLK_CLKSEL0_SDH1SEL_HCLK)
            {
                _SDH1_ReferenceClock = (CLK_GetHCLKFreq() / 1000ul);
            }
        }

        if(sd_clock_khz >= 50000ul)
        {
            sd_clock_khz = 50000ul;
        }
    }
    if (sdh == SDH0)
    {
        rate = _SDH0_ReferenceClock / sd_clock_khz;

        /* choose slower clock if system clock cannot divisible by wanted clock */
        if ((_SDH0_ReferenceClock % sd_clock_khz) != 0ul)
        {
            rate++;
        }
    }
    else
    {
        rate = _SDH1_ReferenceClock / sd_clock_khz;

        /* choose slower clock if system clock cannot divisible by wanted clock */
        if ((_SDH1_ReferenceClock % sd_clock_khz) != 0ul)
        {
            rate++;
        }
    }

    if(rate >= SDH_CLK_DIV0_MAX)
    {
        rate = SDH_CLK_DIV0_MAX;
    }

    /*--- calculate the second divider CLKDIV0[SDHOST_N]*/
    div1 = (rate - 1ul) & 0xFFul;

    /*--- setup register */
    if (sdh == SDH0)
    {
        CLK->CLKDIV0 &= ~CLK_CLKDIV0_SDH0DIV_Msk;
        CLK->CLKDIV0 |= (div1 << CLK_CLKDIV0_SDH0DIV_Pos);
    }
    else
    {
        CLK->CLKDIV3 &= ~CLK_CLKDIV3_SDH1DIV_Msk;
        CLK->CLKDIV3 |= (div1 << CLK_CLKDIV3_SDH1DIV_Pos);
    }
    return;
}

uint32_t SDH_CardDetection(SDH_T *sdh)
{
    uint32_t i, val = TRUE;
    SDH_INFO_T *pSD;

    if (sdh == SDH0)
    {
        pSD = &SD0;
    }
    else
    {
        pSD = &SD1;
    }


    if ((sdh->INTEN & SDH_INTEN_CDSRC_Msk) == SDH_INTEN_CDSRC_Msk)   /* Card detect pin from GPIO */
    {
        if ((sdh->INTSTS & SDH_INTSTS_CDSTS_Msk) == SDH_INTSTS_CDSTS_Msk)   /* Card remove */
        {
            pSD->IsCardInsert = (uint8_t)FALSE;
            val = FALSE;
        }
        else
        {
            pSD->IsCardInsert = (uint8_t)TRUE;
        }
    }
    else if ((sdh->INTEN & SDH_INTEN_CDSRC_Msk) != SDH_INTEN_CDSRC_Msk)
    {
        sdh->CTL |= SDH_CTL_CLKKEEP_Msk;
        for(i= 0ul; i < 5000ul; i++)
        {
        }

        if ((sdh->INTSTS & SDH_INTSTS_CDSTS_Msk) == SDH_INTSTS_CDSTS_Msk)   /* Card insert */
        {
            pSD->IsCardInsert = (uint8_t)TRUE;
        }
        else
        {
            pSD->IsCardInsert = (uint8_t)FALSE;
            val = FALSE;
        }

        sdh->CTL &= ~SDH_CTL_CLKKEEP_Msk;
    }

    return val;
}

uint32_t SDH_Init(SDH_T *sdh)
{
    uint32_t volatile i, status;
    uint32_t resp;
    uint32_t CIDBuffer[4];
    uint32_t volatile u32CmdTimeOut;
    SDH_INFO_T *pSD;

    if (sdh == SDH0)
    {
        pSD = &SD0;
    }
    else
    {
        pSD = &SD1;
    }

    /* set the clock to 300KHz */
    SDH_Set_clock(sdh, 300ul);

    /* power ON 74 clock */
    sdh->CTL |= SDH_CTL_CLK74OEN_Msk;

    while ((sdh->CTL & SDH_CTL_CLK74OEN_Msk) == SDH_CTL_CLK74OEN_Msk)
    {
        if (pSD->IsCardInsert == FALSE)
        {
            return SDH_NO_SD_CARD;
        }
    }

    SDH_SDCommand(sdh, 0ul, 0ul);        /* reset all cards */
    for (i=0x1000ul; i>0ul; i--)
    {
    }

    /* initial SDHC */
    pSD->R7Flag = 1ul;
    u32CmdTimeOut = 0xFFFFFul;

    i = SDH_SDCmdAndRsp(sdh, 8ul, 0x00000155ul, u32CmdTimeOut);
    if (i == Successful)
    {
        /* SD 2.0 */
        SDH_SDCmdAndRsp(sdh, 55ul, 0x00ul, u32CmdTimeOut);
        pSD->R3Flag = 1ul;
        SDH_SDCmdAndRsp(sdh, 41ul, 0x40ff8000ul, u32CmdTimeOut); /* 2.7v-3.6v */
        resp = sdh->RESP0;

        while ((resp & 0x00800000ul) != 0x00800000ul)        /* check if card is ready */
        {
            SDH_SDCmdAndRsp(sdh, 55ul, 0x00ul, u32CmdTimeOut);
            pSD->R3Flag = 1ul;
            SDH_SDCmdAndRsp(sdh, 41ul, 0x40ff8000ul, u32CmdTimeOut); /* 3.0v-3.4v */
            resp = sdh->RESP0;
        }
        if ((resp & 0x00400000ul) == 0x00400000ul)
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
        SDH_SDCommand(sdh, 0ul, 0ul);        /* reset all cards */
        for (i=0x100ul; i>0ul; i--)
        {
        }

        i = SDH_SDCmdAndRsp(sdh, 55ul, 0x00ul, u32CmdTimeOut);
        if (i == 2ul)     /* MMC memory */
        {

            SDH_SDCommand(sdh, 0ul, 0ul);        /* reset */
            for (i=0x100ul; i>0ul; i--)
            {
            }

            pSD->R3Flag = 1ul;

            if (SDH_SDCmdAndRsp(sdh, 1ul, 0x40ff8000ul, u32CmdTimeOut) != 2ul)    /* eMMC memory */
            {
                resp = sdh->RESP0;
                while ((resp & 0x00800000ul) != 0x00800000ul)
                {
                    /* check if card is ready */
                    pSD->R3Flag = 1ul;

                    SDH_SDCmdAndRsp(sdh, 1ul, 0x40ff8000ul, u32CmdTimeOut);      /* high voltage */
                    resp = sdh->RESP0;
                }

                if ((resp & 0x00400000ul) == 0x00400000ul)
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
        else if (i == 0ul)     /* SD Memory */
        {
            pSD->R3Flag = 1ul;
            SDH_SDCmdAndRsp(sdh, 41ul, 0x00ff8000ul, u32CmdTimeOut); /* 3.0v-3.4v */
            resp = sdh->RESP0;
            while ((resp & 0x00800000ul) != 0x00800000ul)        /* check if card is ready */
            {
                SDH_SDCmdAndRsp(sdh, 55ul, 0x00ul, u32CmdTimeOut);
                pSD->R3Flag = 1ul;
                SDH_SDCmdAndRsp(sdh, 41ul, 0x00ff8000ul, u32CmdTimeOut); /* 3.0v-3.4v */
                resp = sdh->RESP0;
            }
            pSD->CardType = SDH_TYPE_SD_LOW;
        }
        else
        {
            pSD->CardType = SDH_TYPE_UNKNOWN;
            return SDH_INIT_ERROR;
        }
    }

    if (pSD->CardType != SDH_TYPE_UNKNOWN)
    {
        SDH_SDCmdAndRsp2(sdh, 2ul, 0x00ul, CIDBuffer);
        if ((pSD->CardType == SDH_TYPE_MMC) || (pSD->CardType == SDH_TYPE_EMMC))
        {
            if ((status = SDH_SDCmdAndRsp(sdh, 3ul, 0x10000ul, 0ul)) != Successful)     /* set RCA */
            {
                return status;
            }
            pSD->RCA = 0x10000ul;
        }
        else
        {
            if ((status = SDH_SDCmdAndRsp(sdh, 3ul, 0x00ul, 0ul)) != Successful)       /* get RCA */
            {
                return status;
            }
            else
            {
                pSD->RCA = (sdh->RESP0 << 8) & 0xffff0000;
            }
        }
    }
    return Successful;
}


uint32_t SDH_SwitchToHighSpeed(SDH_T *sdh, SDH_INFO_T *pSD)
{
    uint32_t volatile status=0ul;
    uint16_t current_comsumption, busy_status0;

    sdh->DMASA = (uint32_t)pSD->dmabuf;
    sdh->BLEN = 63ul;

    if ((status = SDH_SDCmdAndRspDataIn(sdh, 6ul, 0x00ffff01ul)) != Successful)
    {
        return Fail;
    }

    current_comsumption = (uint16_t)(*pSD->dmabuf) << 8;
    current_comsumption |= (uint16_t)(*(pSD->dmabuf + 1));
    if (!current_comsumption)
    {
        return Fail;
    }

    busy_status0 = (uint16_t)(*(pSD->dmabuf + 28)) << 8;
    busy_status0 |= (uint16_t)(*(pSD->dmabuf + 29));

    if (!busy_status0)   /* function ready */
    {
        sdh->DMASA = (uint32_t)pSD->dmabuf;
        sdh->BLEN = 63ul;    /* 512 bit */

        if ((status = SDH_SDCmdAndRspDataIn(sdh, 6ul, 0x80ffff01ul)) != Successful)
        {
            return Fail;
        }

        /* function change timing: 8 clocks */
        sdh->CTL |= SDH_CTL_CLK8OEN_Msk;
        while ((sdh->CTL & SDH_CTL_CLK8OEN_Msk) == SDH_CTL_CLK8OEN_Msk)
        {
        }

        current_comsumption = (uint16_t)(*pSD->dmabuf) << 8;
        current_comsumption |= (uint16_t)(*(pSD->dmabuf + 1));
        if (!current_comsumption)
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
    uint32_t volatile status=0ul;
    uint32_t param;
    SDH_INFO_T *pSD;

    if (sdh == SDH0)
    {
        pSD = &SD0;
    }
    else
    {
        pSD = &SD1;
    }

    if ((status = SDH_SDCmdAndRsp(sdh, 7ul, pSD->RCA, 0ul)) != Successful)
    {
        return status;
    }

    SDH_CheckRB(sdh);

    /* if SD card set 4bit */
    if (pSD->CardType == SDH_TYPE_SD_HIGH)
    {
        sdh->DMASA = (uint32_t)pSD->dmabuf;
        sdh->BLEN = 0x07ul;  /* 64 bit */
        sdh->DMACTL |= SDH_DMACTL_DMARST_Msk;
        while ((sdh->DMACTL & SDH_DMACTL_DMARST_Msk) == 0x2);

        if ((status = SDH_SDCmdAndRsp(sdh, 55ul, pSD->RCA, 0ul)) != Successful)
        {
            return status;
        }
        if ((status = SDH_SDCmdAndRspDataIn(sdh, 51ul, 0x00ul)) != Successful)
        {
            return status;
        }

        if ((*pSD->dmabuf & 0xful) == 0x2ul)
        {
            status = SDH_SwitchToHighSpeed(sdh, pSD);
            if (status == Successful)
            {
                /* divider */
                SDH_Set_clock(sdh, SDHC_FREQ);
            }
        }

        if ((status = SDH_SDCmdAndRsp(sdh, 55ul, pSD->RCA, 0ul)) != Successful)
        {
            return status;
        }
        if ((status = SDH_SDCmdAndRsp(sdh, 6ul, 0x02ul, 0ul)) != Successful)   /* set bus width */
        {
            return status;
        }

        sdh->CTL |= SDH_CTL_DBW_Msk;
    }
    else if (pSD->CardType == SDH_TYPE_SD_LOW)
    {
        sdh->DMASA = (uint32_t)pSD->dmabuf;;
        sdh->BLEN = 0x07ul;

        if ((status = SDH_SDCmdAndRsp(sdh, 55ul, pSD->RCA, 0ul)) != Successful)
        {
            return status;
        }
        if ((status = SDH_SDCmdAndRspDataIn(sdh, 51ul, 0x00ul)) != Successful)
        {
            return status;
        }

        /* set data bus width. ACMD6 for SD card, SDCR_DBW for host. */
        if ((status = SDH_SDCmdAndRsp(sdh, 55ul, pSD->RCA, 0ul)) != Successful)
        {
            return status;
        }

        if ((status = SDH_SDCmdAndRsp(sdh, 6ul, 0x02ul, 0ul)) != Successful)
        {
            return status;
        }

        sdh->CTL |= SDH_CTL_DBW_Msk;
    }
    else if ((pSD->CardType == SDH_TYPE_MMC) ||(pSD->CardType == SDH_TYPE_EMMC))
    {

        if(pSD->CardType == SDH_TYPE_MMC)
        {
            sdh->CTL &= ~SDH_CTL_DBW_Msk;
        }

        /*--- sent CMD6 to MMC card to set bus width to 4 bits mode */
        /* set CMD6 argument Access field to 3, Index to 183, Value to 1 (4-bit mode) */
        param = (3ul << 24) | (183ul << 16) | (1ul << 8);
        if ((status = SDH_SDCmdAndRsp(sdh, 6ul, param, 0ul)) != Successful)
        {
            return status;
        }
        SDH_CheckRB(sdh);

        sdh->CTL |= SDH_CTL_DBW_Msk; /* set bus width to 4-bit mode for SD host controller */

    }

    if ((status = SDH_SDCmdAndRsp(sdh, 16ul, SDH_BLOCK_SIZE, 0ul)) != Successful)
    {
        return status;
    }
    sdh->BLEN = SDH_BLOCK_SIZE - 1ul;

    SDH_SDCommand(sdh, 7ul, 0ul);
    sdh->CTL |= SDH_CTL_CLK8OEN_Msk;
    while ((sdh->CTL & SDH_CTL_CLK8OEN_Msk) == SDH_CTL_CLK8OEN_Msk)
    {
    }

    sdh->INTEN |= SDH_INTEN_BLKDIEN_Msk;

    return Successful;
}

void SDH_Get_SD_info(SDH_T *sdh)
{
    unsigned int R_LEN, C_Size, MULT, size;
    uint32_t Buffer[4];
    //unsigned char *ptr;
    SDH_INFO_T *pSD;

    if (sdh == SDH0)
    {
        pSD = &SD0;
    }
    else
    {
        pSD = &SD1;
    }

    SDH_SDCmdAndRsp2(sdh, 9ul, pSD->RCA, Buffer);

    if ((pSD->CardType == SDH_TYPE_MMC) || (pSD->CardType == SDH_TYPE_EMMC))
    {
        /* for MMC/eMMC card */
        if ((Buffer[0] & 0xc0000000) == 0xc0000000)
        {
            /* CSD_STRUCTURE [127:126] is 3 */
            /* CSD version depend on EXT_CSD register in eMMC v4.4 for card size > 2GB */
            SDH_SDCmdAndRsp(sdh, 7ul, pSD->RCA, 0ul);

            //ptr = (uint8_t *)((uint32_t)_SDH_ucSDHCBuffer );
            sdh->DMASA = (uint32_t)pSD->dmabuf;;
            sdh->BLEN = 511ul;  /* read 512 bytes for EXT_CSD */

            if (SDH_SDCmdAndRspDataIn(sdh, 8ul, 0x00ul) == Successful)
            {
                SDH_SDCommand(sdh, 7ul, 0ul);
                sdh->CTL |= SDH_CTL_CLK8OEN_Msk;
                while ((sdh->CTL & SDH_CTL_CLK8OEN_Msk) == SDH_CTL_CLK8OEN_Msk)
                {
                }

                pSD->totalSectorN = (uint32_t)(*(pSD->dmabuf+215))<<24;
                pSD->totalSectorN |= (uint32_t)(*(pSD->dmabuf+214))<<16;
                pSD->totalSectorN |= (uint32_t)(*(pSD->dmabuf+213))<<8;
                pSD->totalSectorN |= (uint32_t)(*(pSD->dmabuf+212));
                pSD->diskSize = pSD->totalSectorN / 2ul;
            }
        }
        else
        {
            /* CSD version v1.0/1.1/1.2 in eMMC v4.4 spec for card size <= 2GB */
            R_LEN = (Buffer[1] & 0x000f0000ul) >> 16;
            C_Size = ((Buffer[1] & 0x000003fful) << 2) | ((Buffer[2] & 0xc0000000ul) >> 30);
            MULT = (Buffer[2] & 0x00038000ul) >> 15;
            size = (C_Size+1ul) * (1ul<<(MULT+2ul)) * (1ul<<R_LEN);

            pSD->diskSize = size / 1024ul;
            pSD->totalSectorN = size / 512ul;
        }
    }
    else
    {
        if ((Buffer[0] & 0xc0000000) != 0x0ul)
        {
            C_Size = ((Buffer[1] & 0x0000003ful) << 16) | ((Buffer[2] & 0xffff0000ul) >> 16);
            size = (C_Size+1ul) * 512ul;    /* Kbytes */

            pSD->diskSize = size;
            pSD->totalSectorN = size << 1;
        }
        else
        {
            R_LEN = (Buffer[1] & 0x000f0000ul) >> 16;
            C_Size = ((Buffer[1] & 0x000003fful) << 2) | ((Buffer[2] & 0xc0000000ul) >> 30);
            MULT = (Buffer[2] & 0x00038000ul) >> 15;
            size = (C_Size+1ul) * (1ul<<(MULT+2ul)) * (1ul<<R_LEN);

            pSD->diskSize = size / 1024ul;
            pSD->totalSectorN = size / 512ul;
        }
    }
    pSD->sectorSize = (int)512;
}

/** @endcond HIDDEN_SYMBOLS */


/**
 *  @brief  This function use to reset SD function and select card detection source and pin.
 *
 *  @param[in]  sdh    Select SDH0 or SDH1.
 *  @param[in]  u32CardDetSrc   Select card detection pin from GPIO or DAT3 pin. ( \ref CardDetect_From_GPIO / \ref CardDetect_From_DAT3)
 *
 *  @return None
 */
void SDH_Open(SDH_T *sdh, uint32_t u32CardDetSrc)
{
    sdh->DMACTL = SDH_DMACTL_DMARST_Msk;
    while ((sdh->DMACTL & SDH_DMACTL_DMARST_Msk) == SDH_DMACTL_DMARST_Msk)
    {
    }

    sdh->DMACTL = SDH_DMACTL_DMAEN_Msk;

    sdh->GCTL = SDH_GCTL_GCTLRST_Msk | SDH_GCTL_SDEN_Msk;
    while ((sdh->GCTL & SDH_GCTL_GCTLRST_Msk) == SDH_GCTL_GCTLRST_Msk)
    {
    }

    if (sdh == SDH0)
    {
        NVIC_EnableIRQ(SDH0_IRQn);
        memset(&SD0, 0, sizeof(SDH_INFO_T));
        SD0.dmabuf = _SDH0_ucSDHCBuffer;
    }
    else if (sdh == SDH1)
    {
        NVIC_EnableIRQ(SDH1_IRQn);
        memset(&SD1, 0, sizeof(SDH_INFO_T));
        SD1.dmabuf = _SDH1_ucSDHCBuffer;
    }
    else
    {
    }

    sdh->GCTL = SDH_GCTL_SDEN_Msk;

    if ((u32CardDetSrc & CardDetect_From_DAT3) == CardDetect_From_DAT3)
    {
        sdh->INTEN &= ~SDH_INTEN_CDSRC_Msk;
    }
    else
    {
        sdh->INTEN |= SDH_INTEN_CDSRC_Msk;
    }
    sdh->INTEN |= SDH_INTEN_CDIEN_Msk;

    sdh->CTL |= SDH_CTL_CTLRST_Msk;
    while ((sdh->CTL & SDH_CTL_CTLRST_Msk) == SDH_CTL_CTLRST_Msk)
    {
    }
}

/**
 *  @brief  This function use to initial SD card.
 *
 *  @param[in]    sdh    Select SDH0 or SDH1.
 *
 *  @return None
 *
 *  @details This function is used to initial SD card.
 *           SD initial state needs 400KHz clock output, driver will use HIRC for SD initial clock source.
 *           And then switch back to the user's setting.
 */
uint32_t SDH_Probe(SDH_T *sdh)
{
    uint32_t val;

    sdh->GINTEN = 0ul;
    sdh->CTL &= ~SDH_CTL_SDNWR_Msk;
    sdh->CTL |=  0x09ul << SDH_CTL_SDNWR_Pos;   /* set SDNWR = 9 */
    sdh->CTL &= ~SDH_CTL_BLKCNT_Msk;
    sdh->CTL |=  0x01ul << SDH_CTL_BLKCNT_Pos;  /* set BLKCNT = 1 */
    sdh->CTL &= ~SDH_CTL_DBW_Msk;               /* SD 1-bit data bus */

    if(!(SDH_CardDetection(sdh)))
    {
        return SDH_NO_SD_CARD;
    }

    if ((val = SDH_Init(sdh)) != 0ul)
    {
        return val;
    }

    /* divider */
    if ((SD0.CardType == SDH_TYPE_MMC) || (SD1.CardType == SDH_TYPE_MMC))
    {
        SDH_Set_clock(sdh, MMC_FREQ);
    }
    else
    {
        SDH_Set_clock(sdh, SD_FREQ);
    }
    SDH_Get_SD_info(sdh);

    if ((val = SDH_SelectCardType(sdh)) != 0ul)
    {
        return val;
    }

    return 0ul;
}

/**
 *  @brief  This function use to read data from SD card.
 *
 *  @param[in]     sdh           Select SDH0 or SDH1.
 *  @param[out]    pu8BufAddr    The buffer to receive the data from SD card.
 *  @param[in]     u32StartSec   The start read sector address.
 *  @param[in]     u32SecCount   The the read sector number of data
 *
 *  @return None
 */
uint32_t SDH_Read(SDH_T *sdh, uint8_t *pu8BufAddr, uint32_t u32StartSec, uint32_t u32SecCount)
{
    uint32_t volatile bIsSendCmd = FALSE, buf;
    uint32_t volatile reg;
    uint32_t volatile i, loop, status;
    uint32_t blksize = SDH_BLOCK_SIZE;

    SDH_INFO_T *pSD;
    if (sdh == SDH0)
    {
        pSD = &SD0;
    }
    else
    {
        pSD = &SD1;
    }

    if (u32SecCount == 0ul)
    {
        return SDH_SELECT_ERROR;
    }

    if ((status = SDH_SDCmdAndRsp(sdh, 7ul, pSD->RCA, 0ul)) != Successful)
    {
        return status;
    }
    SDH_CheckRB(sdh);

    sdh->BLEN = blksize - 1ul;       /* the actual byte count is equal to (SDBLEN+1) */

    if ( (pSD->CardType == SDH_TYPE_SD_HIGH) || (pSD->CardType == SDH_TYPE_EMMC) )
    {
        sdh->CMDARG = u32StartSec;
    }
    else
    {
        sdh->CMDARG = u32StartSec * blksize;
    }

    sdh->DMASA = (uint32_t)pu8BufAddr;

    loop = u32SecCount / 255ul;
    for (i=0ul; i<loop; i++)
    {
        pSD->DataReadyFlag = (uint8_t)FALSE;
        reg = sdh->CTL & ~SDH_CTL_CMDCODE_Msk;
        reg = reg | 0xff0000ul;   /* set BLK_CNT to 255 */
        if (bIsSendCmd == FALSE)
        {
            sdh->CTL = reg|(18ul << 8)|(SDH_CTL_COEN_Msk | SDH_CTL_RIEN_Msk | SDH_CTL_DIEN_Msk);
            bIsSendCmd = TRUE;
        }
        else
        {
            sdh->CTL = reg | SDH_CTL_DIEN_Msk;
        }

        while(!pSD->DataReadyFlag)
        {
            if(pSD->DataReadyFlag)
            {
                break;
            }
            if (pSD->IsCardInsert == FALSE)
            {
                return SDH_NO_SD_CARD;
            }
        }

        if ((sdh->INTSTS & SDH_INTSTS_CRC7_Msk) != SDH_INTSTS_CRC7_Msk)      /* check CRC7 */
        {
            return SDH_CRC7_ERROR;
        }

        if ((sdh->INTSTS & SDH_INTSTS_CRC16_Msk) != SDH_INTSTS_CRC16_Msk)     /* check CRC16 */
        {
            return SDH_CRC16_ERROR;
        }
    }

    loop = u32SecCount % 255ul;
    if (loop != 0ul)
    {
        pSD->DataReadyFlag = (uint8_t)FALSE;
        reg = sdh->CTL & (~SDH_CTL_CMDCODE_Msk);
        reg = reg & (~SDH_CTL_BLKCNT_Msk);
        reg |= (loop << 16);    /* setup SDCR_BLKCNT */

        if (bIsSendCmd == FALSE)
        {
            sdh->CTL = reg|(18ul << 8)|(SDH_CTL_COEN_Msk | SDH_CTL_RIEN_Msk | SDH_CTL_DIEN_Msk);
            bIsSendCmd = TRUE;
        }
        else
        {
            sdh->CTL = reg | SDH_CTL_DIEN_Msk;
        }

        while(!pSD->DataReadyFlag)
        {
            if (pSD->IsCardInsert == FALSE)
            {
                return SDH_NO_SD_CARD;
            }
        }

        if ((sdh->INTSTS & SDH_INTSTS_CRC7_Msk) != SDH_INTSTS_CRC7_Msk)      /* check CRC7 */
        {
            return SDH_CRC7_ERROR;
        }

        if ((sdh->INTSTS & SDH_INTSTS_CRC16_Msk) != SDH_INTSTS_CRC16_Msk)     /* check CRC16 */
        {
            return SDH_CRC16_ERROR;
        }
    }

    if (SDH_SDCmdAndRsp(sdh, 12ul, 0ul, 0ul))      /* stop command */
    {
        return SDH_CRC7_ERROR;
    }
    SDH_CheckRB(sdh);

    SDH_SDCommand(sdh, 7ul, 0ul);
    sdh->CTL |= SDH_CTL_CLK8OEN_Msk;
    while ((sdh->CTL & SDH_CTL_CLK8OEN_Msk) == SDH_CTL_CLK8OEN_Msk)
    {
    }

    return Successful;
}


/**
 *  @brief  This function use to write data to SD card.
 *
 *  @param[in]    sdh           Select SDH0 or SDH1.
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
    uint32_t volatile bIsSendCmd = FALSE;
    uint32_t volatile reg;
    uint32_t volatile i, loop, status;

    SDH_INFO_T *pSD;

    if (sdh == SDH0)
    {
        pSD = &SD0;
    }
    else
    {
        pSD = &SD1;
    }

    if (u32SecCount == 0ul)
    {
        return SDH_SELECT_ERROR;
    }

    if ((status = SDH_SDCmdAndRsp(sdh, 7ul, pSD->RCA, 0ul)) != Successful)
    {
        return status;
    }

    SDH_CheckRB(sdh);

    /* According to SD Spec v2.0, the write CMD block size MUST be 512, and the start address MUST be 512*n. */
    sdh->BLEN = SDH_BLOCK_SIZE - 1ul;

    if ((pSD->CardType == SDH_TYPE_SD_HIGH) || (pSD->CardType == SDH_TYPE_EMMC))
    {
        sdh->CMDARG = u32StartSec;
    }
    else
    {
        sdh->CMDARG = u32StartSec * SDH_BLOCK_SIZE;  /* set start address for SD CMD */
    }

    sdh->DMASA = (uint32_t)pu8BufAddr;
    loop = u32SecCount / 255ul;   /* the maximum block count is 0xFF=255 for register SDCR[BLK_CNT] */
    for (i=0ul; i<loop; i++)
    {
        pSD->DataReadyFlag = (uint8_t)FALSE;
        reg = sdh->CTL & 0xff00c080;
        reg = reg | 0xff0000ul;   /* set BLK_CNT to 0xFF=255 */
        if (!bIsSendCmd)
        {
            sdh->CTL = reg|(25ul << 8)|(SDH_CTL_COEN_Msk | SDH_CTL_RIEN_Msk | SDH_CTL_DOEN_Msk);
            bIsSendCmd = TRUE;
        }
        else
        {
            sdh->CTL = reg | SDH_CTL_DOEN_Msk;
        }

        while(!pSD->DataReadyFlag)
        {
            if (pSD->IsCardInsert == FALSE)
            {
                return SDH_NO_SD_CARD;
            }
        }

        if ((sdh->INTSTS & SDH_INTSTS_CRCIF_Msk) != 0ul)
        {
            sdh->INTSTS = SDH_INTSTS_CRCIF_Msk;
            return SDH_CRC_ERROR;
        }
    }

    loop = u32SecCount % 255ul;
    if (loop != 0ul)
    {
        pSD->DataReadyFlag = (uint8_t)FALSE;
        reg = (sdh->CTL & 0xff00c080) | (loop << 16);
        if (!bIsSendCmd)
        {
            sdh->CTL = reg|(25ul << 8)|(SDH_CTL_COEN_Msk | SDH_CTL_RIEN_Msk | SDH_CTL_DOEN_Msk);
            bIsSendCmd = TRUE;
        }
        else
        {
            sdh->CTL = reg | SDH_CTL_DOEN_Msk;
        }

        while(!pSD->DataReadyFlag)
        {
            if (pSD->IsCardInsert == FALSE)
            {
                return SDH_NO_SD_CARD;
            }
        }

        if ((sdh->INTSTS & SDH_INTSTS_CRCIF_Msk) != 0ul)
        {
            sdh->INTSTS = SDH_INTSTS_CRCIF_Msk;
            return SDH_CRC_ERROR;
        }
    }
    sdh->INTSTS = SDH_INTSTS_CRCIF_Msk;

    if (SDH_SDCmdAndRsp(sdh, 12ul, 0ul, 0ul))      /* stop command */
    {
        return SDH_CRC7_ERROR;
    }
    SDH_CheckRB(sdh);

    SDH_SDCommand(sdh, 7ul, 0ul);
    sdh->CTL |= SDH_CTL_CLK8OEN_Msk;
    while ((sdh->CTL & SDH_CTL_CLK8OEN_Msk) == SDH_CTL_CLK8OEN_Msk)
    {
    }

    return Successful;
}

/*@}*/ /* end of group SDH_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SDH_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/








