/**************************************************************************//**
 * @file     fmi.c
 * @brief    N9H30 FMI eMMC driver source file
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "N9H30.h"
#include "nu_sys.h"
#include "nu_fmi.h"

/** @addtogroup N9H30_Device_Driver N9H30 Device Driver
  @{
*/

/** @addtogroup N9H30_FMI_Driver FMI Driver
  @{
*/


/** @addtogroup N9H30_FMI_EXPORTED_FUNCTIONS FMI Exported Functions
  @{
*/
/// @cond HIDDEN_SYMBOLS

#define FMI_BLOCK_SIZE   512

// global variables
// For response R3 (such as ACMD41, CRC-7 is invalid; but FMI controller will still
// calculate CRC-7 and get an error result, software should ignore this error and clear INTSTS [CRC_IF] flag
// _fmi_uR3_CMD is the flag for it. 1 means software should ignore CRC-7 error
unsigned int _fmi_uR3_CMD = 0;
unsigned int _fmi_uR7_CMD = 0;
unsigned char volatile _fmi_eMMCDataReady = FALSE;

unsigned char *_fmi_peMMCBuffer;
unsigned int gFMIReferenceClock;

#ifdef __ICCARM__
    #pragma data_alignment = 4096
    unsigned char _fmi_uceMMCBuffer[512];
#else
    unsigned char _fmi_uceMMCBuffer[512] __attribute__((aligned(4096)));
#endif

int emmc_ok = 0;

unsigned char peMMC_offset = 0;

EMMC_INFO_T eMMC;

void eMMC_CheckRB()
{
    while (1)
    {
        outpw(REG_FMI_EMMCCTL, inpw(REG_FMI_EMMCCTL) | FMI_EMMCCTL_CLK8OEN_Msk);
        while (inpw(REG_FMI_EMMCCTL) & FMI_EMMCCTL_CLK8OEN_Msk);
        if (inpw(REG_FMI_EMMCINTSTS) & FMI_EMMCINTSTS_DAT0STS_Msk)
            break;
    }
}


int eMMC_Command(EMMC_INFO_T *pSD, unsigned char ucCmd, unsigned int uArg)
{
    volatile int buf;

    outpw(REG_FMI_EMMCCMD, uArg);
    buf = (inpw(REG_FMI_EMMCCTL) & (~FMI_EMMCCTL_CMDCODE_Msk)) | (ucCmd << 8) | (FMI_EMMCCTL_COEN_Msk);
    outpw(REG_FMI_EMMCCTL, buf);

    while (inpw(REG_FMI_EMMCCTL) & FMI_EMMCCTL_COEN_Msk)
    {
        if (pSD->IsCardInsert == FALSE)
            return EMMC_NO_CARD;
    }
    return 0;
}


int eMMC_CmdAndRsp(EMMC_INFO_T *pSD, unsigned char ucCmd, unsigned int uArg, int ntickCount)
{
    volatile int buf;

    outpw(REG_FMI_EMMCCMD, uArg);
    buf = (inpw(REG_FMI_EMMCCTL) & (~FMI_EMMCCTL_CMDCODE_Msk)) | (ucCmd << 8) | (FMI_EMMCCTL_COEN_Msk | FMI_EMMCCTL_RIEN_Msk);
    outpw(REG_FMI_EMMCCTL, buf);

    if (ntickCount > 0)
    {
        while (inpw(REG_FMI_EMMCCTL) & FMI_EMMCCTL_RIEN_Msk)
        {
            if (ntickCount-- == 0)
            {
                outpw(REG_FMI_EMMCCTL, inpw(REG_FMI_EMMCCTL) | FMI_EMMCCTL_CTLRST_Msk); // reset SD engine
                return 2;
            }
            if (pSD->IsCardInsert == FALSE)
                return EMMC_NO_CARD;
        }
    }
    else
    {
        while (inpw(REG_FMI_EMMCCTL) & FMI_EMMCCTL_RIEN_Msk)
        {
            if (pSD->IsCardInsert == FALSE)
                return EMMC_NO_CARD;
        }
    }

    if (_fmi_uR7_CMD)
    {
        if (((inpw(REG_FMI_EMMCRESP1) & 0xff) != 0x55) && ((inpw(REG_FMI_EMMCRESP0) & 0xf) != 0x01))
        {
            _fmi_uR7_CMD = 0;
            return EMMC_CMD8_ERROR;
        }
    }

    if (!_fmi_uR3_CMD)
    {
        if (inpw(REG_FMI_EMMCINTSTS) & FMI_EMMCINTSTS_CRC7_Msk)     // check CRC7
            return 0;
        else
            return EMMC_CRC7_ERROR;
    }
    else     // ignore CRC error for R3 case
    {
        _fmi_uR3_CMD = 0;
        outpw(REG_FMI_EMMCINTSTS, FMI_EMMCINTSTS_CRCIF_Msk);
        return 0;
    }
}

int eMMC_Swap32(int val)
{
    int buf;

    buf = val;
    val <<= 24;
    val |= (buf << 8) & 0xff0000;
    val |= (buf >> 8) & 0xff00;
    val |= (buf >> 24) & 0xff;
    return val;
}

// Get 16 bytes CID or CSD
int eMMC_CmdAndRsp2(EMMC_INFO_T *pSD, unsigned char ucCmd, unsigned int uArg, unsigned int *puR2ptr)
{
    unsigned int i, buf;
    unsigned int tmpBuf[5];

    outpw(REG_FMI_EMMCCMD, uArg);
    buf = (inpw(REG_FMI_EMMCCTL) & (~FMI_EMMCCTL_CMDCODE_Msk)) | (ucCmd << 8) | (FMI_EMMCCTL_COEN_Msk | FMI_EMMCCTL_R2EN_Msk);
    outpw(REG_FMI_EMMCCTL, buf);

    while (inpw(REG_FMI_EMMCCTL) & FMI_EMMCCTL_R2EN_Msk)
    {
        if (pSD->IsCardInsert == FALSE)
            return EMMC_NO_CARD;
    }

    if (inpw(REG_FMI_EMMCINTSTS) & FMI_EMMCINTSTS_CRC7_Msk)
    {
        for (i = 0; i < 5; i++)
            tmpBuf[i] = eMMC_Swap32(*(int *)(FMI_BA + i * 4));
        for (i = 0; i < 4; i++)
            *puR2ptr++ = ((tmpBuf[i] & 0x00ffffff) << 8) | ((tmpBuf[i + 1] & 0xff000000) >> 24);
        return 0;
    }
    else
        return EMMC_CRC7_ERROR;
}


int eMMC_CmdAndRspDataIn(EMMC_INFO_T *pSD, unsigned char ucCmd, unsigned int uArg)
{
    volatile int buf;

    outpw(REG_FMI_EMMCCMD, uArg);
    buf = (inpw(REG_FMI_EMMCCTL) & (~FMI_EMMCCTL_CMDCODE_Msk)) | (ucCmd << 8) | (FMI_EMMCCTL_COEN_Msk | FMI_EMMCCTL_RIEN_Msk | FMI_EMMCCTL_DIEN_Msk);
    outpw(REG_FMI_EMMCCTL, buf);

    while (inpw(REG_FMI_EMMCCTL) & FMI_EMMCCTL_RIEN_Msk)
    {
        if (pSD->IsCardInsert == FALSE)
            return EMMC_NO_CARD;
    }

    while (inpw(REG_FMI_EMMCCTL) & FMI_EMMCCTL_DIEN_Msk)
    {
        if (pSD->IsCardInsert == FALSE)
            return EMMC_NO_CARD;
    }

    if (!(inpw(REG_FMI_EMMCINTSTS) & FMI_EMMCINTSTS_CRC7_Msk))      // check CRC7
    {
        return EMMC_CRC7_ERROR;
    }

    if (!(inpw(REG_FMI_EMMCINTSTS) & FMI_EMMCINTSTS_CRC16_Msk))     // check CRC16
    {
        return EMMC_CRC16_ERROR;
    }
    return 0;
}

// there are 3 bits for divider N0, maximum is 8
#define EMMC_CLK_DIV0_MAX     8
// there are 8 bits for divider N1, maximum is 256
#define EMMC_CLK_DIV1_MAX     256

void eMMC_Set_clock(unsigned int clock_khz)
{
    UINT32 rate, div0, div1, i;

    //--- calculate the rate that 2 divider have to divide
    // _fmi_uFMIReferenceClock is the input clock with unit KHz like as APLL/UPLL and
    if (clock_khz > gFMIReferenceClock)
    {
        //sysprintf("ERROR: wrong eMMC clock %dKHz since it is faster than input clock %dKHz !\n", clock_khz, gFMIReferenceClock);
        return;
    }
    rate = gFMIReferenceClock / clock_khz;
    // choose slower clock if system clock cannot divisible by wanted clock
    if (gFMIReferenceClock % clock_khz != 0)
        rate++;

    if (rate > (EMMC_CLK_DIV0_MAX * EMMC_CLK_DIV1_MAX))   // the maximum divider for EMMC_CLK is (EMMC_CLK_DIV0_MAX * EMMC_CLK_DIV1_MAX)
    {
        //sysprintf("ERROR: wrong SD clock %dKHz since it is slower than input clock %dKHz/%d !\n", clock_khz, gFMIReferenceClock, EMMC_CLK_DIV0_MAX * EMMC_CLK_DIV1_MAX);
        return;
    }

    //--- choose a suitable value for first divider
    for (div0 = EMMC_CLK_DIV0_MAX; div0 > 0; div0--)    // choose the maximum value if can exact division
    {
        if (rate % div0 == 0)
            break;
    }
    if (div0 == 0)   // cannot exact division
    {
        // if rate <= EMMC_CLK_DIV1_MAX, set div0 to 1 since div1 can exactly divide input clock
        div0 = (rate <= EMMC_CLK_DIV1_MAX) ? 1 : EMMC_CLK_DIV0_MAX;
    }

    //--- calculate the second divider
    div1 = rate / div0;
    div1 &= 0xFF;

    //sysprintf("Set_clock(): wanted clock=%d, rate=%d, div0=%d, div1=%d\n", clock_khz, rate, div0, div1);

    //--- setup register
    outpw(REG_CLK_DIVCTL3, (inpw(REG_CLK_DIVCTL3) & ~0x18) | (0x3 << 3));
    outpw(REG_CLK_DIVCTL3, (inpw(REG_CLK_DIVCTL3) & ~0x7) | (div0 - 1));
    outpw(REG_CLK_DIVCTL3, (inpw(REG_CLK_DIVCTL3) & ~0xff00) | ((div1 - 1) << 8));
    for (i = 0; i < 1000; i++); // waiting for clock become stable
    return;
}

// Initial
int eMMC_Init(EMMC_INFO_T *pSD)
{
    int volatile i, status;
    unsigned int resp;
    unsigned int CIDBuffer[4];
    unsigned int volatile u32CmdTimeOut;

    // set the clock to 300KHz
    eMMC_Set_clock(300);

    // power ON 74 clock
    outpw(REG_FMI_EMMCCTL, inpw(REG_FMI_EMMCCTL) | FMI_EMMCCTL_CLK74OEN_Msk);

    while (inpw(REG_FMI_EMMCCTL) & FMI_EMMCCTL_CLK74OEN_Msk);

    eMMC_Command(pSD, 0, 0);        // reset all cards
    for (i = 0x1000; i > 0; i--);

    // initial SDHC
    _fmi_uR7_CMD = 1;
    u32CmdTimeOut = 5000;

    i = eMMC_CmdAndRsp(pSD, 8, 0x00000155, u32CmdTimeOut);
    if (i == 0)
    {
        // SD 2.0
        eMMC_CmdAndRsp(pSD, 55, 0x00, u32CmdTimeOut);
        _fmi_uR3_CMD = 1;
        eMMC_CmdAndRsp(pSD, 41, 0x40ff8000, u32CmdTimeOut); // 2.7v-3.6v
        resp = inpw(REG_FMI_EMMCRESP0);

        while (!(resp & 0x00800000))        // check if card is ready
        {
            eMMC_CmdAndRsp(pSD, 55, 0x00, u32CmdTimeOut);
            _fmi_uR3_CMD = 1;
            eMMC_CmdAndRsp(pSD, 41, 0x40ff8000, u32CmdTimeOut); // 3.0v-3.4v
            resp = inpw(REG_FMI_EMMCRESP0);
        }
        if (resp & 0x00400000)
            pSD->CardType = EMMC_TYPE_SD_HIGH;
        else
            pSD->CardType = EMMC_TYPE_SD_LOW;
    }
    else
    {
        // SD 1.1
        eMMC_Command(pSD, 0, 0);        // reset all cards
        for (i = 0x100; i > 0; i--);

        i = eMMC_CmdAndRsp(pSD, 55, 0x00, u32CmdTimeOut);
        if (i == 2)     // MMC memory
        {

            eMMC_Command(pSD, 0, 0);        // reset
            for (i = 0x100; i > 0; i--);

            _fmi_uR3_CMD = 1;

            if (eMMC_CmdAndRsp(pSD, 1, 0x40ff8000, u32CmdTimeOut) != 2)    // eMMC memory
            {
                resp = inpw(REG_FMI_EMMCRESP0);
                while (!(resp & 0x00800000))        // check if card is ready
                {
                    _fmi_uR3_CMD = 1;

                    eMMC_CmdAndRsp(pSD, 1, 0x40ff8000, u32CmdTimeOut);      // high voltage
                    resp = inpw(REG_FMI_EMMCRESP0);
                }

                if (resp & 0x00400000)
                    pSD->CardType = EMMC_TYPE_EMMC;
                else
                    pSD->CardType = EMMC_TYPE_MMC;
            }
            else
            {
                pSD->CardType = EMMC_TYPE_UNKNOWN;
                return EMMC_ERR_DEVICE;
            }
        }
        else if (i == 0)     // SD Memory
        {
            _fmi_uR3_CMD = 1;
            eMMC_CmdAndRsp(pSD, 41, 0x00ff8000, u32CmdTimeOut); // 3.0v-3.4v
            resp = inpw(REG_FMI_EMMCRESP0);
            while (!(resp & 0x00800000))        // check if card is ready
            {
                eMMC_CmdAndRsp(pSD, 55, 0x00, u32CmdTimeOut);
                _fmi_uR3_CMD = 1;
                eMMC_CmdAndRsp(pSD, 41, 0x00ff8000, u32CmdTimeOut); // 3.0v-3.4v
                resp = inpw(REG_FMI_EMMCRESP0);
            }
            pSD->CardType = EMMC_TYPE_SD_LOW;
        }
        else
        {
            pSD->CardType = EMMC_TYPE_UNKNOWN;
            return EMMC_INIT_ERROR;
        }
    }

    // CMD2, CMD3
    if (pSD->CardType != EMMC_TYPE_UNKNOWN)
    {
        eMMC_CmdAndRsp2(pSD, 2, 0x00, CIDBuffer);
        if ((pSD->CardType == EMMC_TYPE_MMC) || (pSD->CardType == EMMC_TYPE_EMMC))
        {
            if ((status = eMMC_CmdAndRsp(pSD, 3, 0x10000, 0)) != 0)        // set RCA
                return status;
            pSD->RCA = 0x10000;
        }
        else
        {
            if ((status = eMMC_CmdAndRsp(pSD, 3, 0x00, 0)) != 0)       // get RCA
                return status;
            else
                pSD->RCA = (inpw(REG_FMI_EMMCRESP0) << 8) & 0xffff0000;
        }
    }

#if 0
    if (pSD->CardType == EMMC_TYPE_SD_HIGH)
        sysprintf("This is high capacity SD memory card\n");
    if (pSD->CardType == EMMC_TYPE_SD_LOW)
        sysprintf("This is standard capacity SD memory card\n");
    if (pSD->CardType == EMMC_TYPE_EMMC)
        sysprintf("This is eMMC memory card\n");
#endif
    return 0;
}


int eMMC_SwitchToHighSpeed(EMMC_INFO_T *pSD)
{
    int volatile status = 0;
    unsigned short current_comsumption, busy_status0;

    outpw(REG_FMI_DMASA, (unsigned int)_fmi_peMMCBuffer);    // set DMA transfer starting address
    outpw(REG_FMI_EMMCBLEN, 63);    // 512 bit

    if ((status = eMMC_CmdAndRspDataIn(pSD, 6, 0x00ffff01)) != 0)
        return 1;

    current_comsumption = _fmi_peMMCBuffer[0] << 8 | _fmi_peMMCBuffer[1];
    if (!current_comsumption)
        return 1;

    busy_status0 = _fmi_peMMCBuffer[28] << 8 | _fmi_peMMCBuffer[29];

    if (!busy_status0)   // function ready
    {
        outpw(REG_FMI_DMASA, (unsigned int)_fmi_peMMCBuffer);        // set DMA transfer starting address
        outpw(REG_FMI_EMMCBLEN, 63);    // 512 bit

        if ((status = eMMC_CmdAndRspDataIn(pSD, 6, 0x80ffff01)) != 0)
            return 1;

        // function change timing: 8 clocks
        outpw(REG_FMI_EMMCCTL, inpw(REG_FMI_EMMCCTL) | FMI_EMMCCTL_CLK8OEN_Msk);
        while (inpw(REG_FMI_EMMCCTL) & FMI_EMMCCTL_CLK8OEN_Msk);

        current_comsumption = _fmi_peMMCBuffer[0] << 8 | _fmi_peMMCBuffer[1];
        if (!current_comsumption)
            return 1;

        return 0;
    }
    else
        return 1;
}


int eMMC_SelectCardType(EMMC_INFO_T *pSD)
{
    int volatile status = 0;
    //unsigned int arg;

    if ((status = eMMC_CmdAndRsp(pSD, 7, pSD->RCA, 0)) != 0)
        return status;

    eMMC_CheckRB();

    // if SD card set 4bit
    if (pSD->CardType == EMMC_TYPE_SD_HIGH)
    {
        _fmi_peMMCBuffer = (unsigned char *)((unsigned int)_fmi_uceMMCBuffer);
        outpw(REG_FMI_DMASA, (unsigned int)_fmi_peMMCBuffer);    // set DMA transfer starting address
        outpw(REG_FMI_EMMCBLEN, 0x07);  // 64 bit

        if ((status = eMMC_CmdAndRsp(pSD, 55, pSD->RCA, 0)) != 0)
            return status;
        if ((status = eMMC_CmdAndRspDataIn(pSD, 51, 0x00)) != 0)
            return status;

        if ((_fmi_uceMMCBuffer[0] & 0xf) == 0x2)
        {
            status = eMMC_SwitchToHighSpeed(pSD);
            if (status == 0)
            {
                /* divider */
                eMMC_Set_clock(SDHC_FREQ);
            }
        }

        if ((status = eMMC_CmdAndRsp(pSD, 55, pSD->RCA, 0)) != 0)
            return status;
        if ((status = eMMC_CmdAndRsp(pSD, 6, 0x02, 0)) != 0)   // set bus width
            return status;

        outpw(REG_FMI_EMMCCTL, inpw(REG_FMI_EMMCCTL) | FMI_EMMCCTL_DBW_Msk);
    }
    else if (pSD->CardType == EMMC_TYPE_SD_LOW)
    {
        _fmi_peMMCBuffer = (unsigned char *)((unsigned int)_fmi_uceMMCBuffer);
        outpw(REG_FMI_DMASA, (unsigned int) _fmi_peMMCBuffer); // set DMA transfer starting address
        outpw(REG_FMI_EMMCBLEN, 0x07);  // 64 bit

        if ((status = eMMC_CmdAndRsp(pSD, 55, pSD->RCA, 0)) != 0)
            return status;
        if ((status = eMMC_CmdAndRspDataIn(pSD, 51, 0x00)) != 0)
            return status;

        // set data bus width. ACMD6 for SD card, SDCR_DBW for host.
        if ((status = eMMC_CmdAndRsp(pSD, 55, pSD->RCA, 0)) != 0)
            return status;

        if ((status = eMMC_CmdAndRsp(pSD, 6, 0x02, 0)) != 0)   // set bus width
            return status;

        outpw(REG_FMI_EMMCCTL, inpw(REG_FMI_EMMCCTL) | FMI_EMMCCTL_DBW_Msk);
    }
    else if (pSD->CardType == EMMC_TYPE_MMC)
    {

        outpw(REG_FMI_EMMCCTL, inpw(REG_FMI_EMMCCTL) & ~FMI_EMMCCTL_DBW_Msk);

    }
    else if (pSD->CardType == EMMC_TYPE_EMMC)
    {

        //--- sent CMD6 to MMC card to set bus width to 4 bits mode, skymedi only support 1-bit
        // set CMD6 argument Access field to 3, Index to 183, Value to 1 (4-bit mode)
//         arg = (3 << 24) | (183 << 16) | (1 << 8);
//         if ((status = eMMC_CmdAndRsp(pSD, 6, arg, 0)) != 0)
//             return status;
//         eMMC_CheckRB();

//         outpw(REG_FMI_EMMCCTL, inpw(REG_FMI_EMMCCTL)| FMI_EMMCCTL_DBW_Msk);
        outpw(REG_FMI_EMMCCTL, inpw(REG_FMI_EMMCCTL) & ~FMI_EMMCCTL_DBW_Msk);
    }

    if ((status = eMMC_CmdAndRsp(pSD, 16, FMI_BLOCK_SIZE, 0)) != 0) // set block length
        return status;
    outpw(REG_FMI_EMMCBLEN, FMI_BLOCK_SIZE - 1);           // set the block size

    eMMC_Command(pSD, 7, 0);
    outpw(REG_FMI_EMMCCTL, inpw(REG_FMI_EMMCCTL) | FMI_EMMCCTL_CLK8OEN_Msk);
    while (inpw(REG_FMI_EMMCCTL) & FMI_EMMCCTL_CLK8OEN_Msk);

    outpw(REG_FMI_EMMCINTEN, inpw(REG_FMI_EMMCINTEN) | FMI_EMMCINTEN_BLKDIEN_Msk);

    return 0;
}

void eMMC_Get_info(EMMC_INFO_T *pSD)
{
    unsigned int R_LEN, C_Size, MULT, size;
    unsigned int Buffer[4];
    unsigned char *ptr;

    eMMC_CmdAndRsp2(pSD, 9, pSD->RCA, Buffer);

    if ((pSD->CardType == EMMC_TYPE_MMC) || (pSD->CardType == EMMC_TYPE_EMMC))
    {
        // for MMC/eMMC card
        if ((Buffer[0] & 0xc0000000) == 0xc0000000)
        {
            // CSD_STRUCTURE [127:126] is 3
            // CSD version depend on EXT_CSD register in eMMC v4.4 for card size > 2GB
            eMMC_CmdAndRsp(pSD, 7, pSD->RCA, 0);

            ptr = (unsigned char *)((unsigned int)_fmi_uceMMCBuffer);
            outpw(REG_FMI_DMASA, (unsigned int)ptr);  // set DMA transfer starting address
            outpw(REG_FMI_EMMCBLEN, 511);  // read 512 bytes for EXT_CSD

            if (eMMC_CmdAndRspDataIn(pSD, 8, 0x00) != 0)
                return;

            eMMC_Command(pSD, 7, 0);
            outpw(REG_FMI_EMMCCTL, inpw(REG_FMI_EMMCCTL) | FMI_EMMCCTL_CLK8OEN_Msk);
            while (inpw(REG_FMI_EMMCCTL) & FMI_EMMCCTL_CLK8OEN_Msk);

            pSD->totalSectorN = (*(unsigned int *)(ptr + 212));
            pSD->diskSize = pSD->totalSectorN / 2;
        }
        else
        {
            // CSD version v1.0/1.1/1.2 in eMMC v4.4 spec for card size <= 2GB
            R_LEN = (Buffer[1] & 0x000f0000) >> 16;
            C_Size = ((Buffer[1] & 0x000003ff) << 2) | ((Buffer[2] & 0xc0000000) >> 30);
            MULT = (Buffer[2] & 0x00038000) >> 15;
            size = (C_Size + 1) * (1 << (MULT + 2)) * (1 << R_LEN);

            pSD->diskSize = size / 1024;
            pSD->totalSectorN = size / 512;
        }
    }
    else
    {
        if (Buffer[0] & 0xc0000000)
        {
            C_Size = ((Buffer[1] & 0x0000003f) << 16) | ((Buffer[2] & 0xffff0000) >> 16);
            size = (C_Size + 1) * 512;  // Kbytes

            pSD->diskSize = size;
            pSD->totalSectorN = size << 1;
        }
        else
        {
            R_LEN = (Buffer[1] & 0x000f0000) >> 16;
            C_Size = ((Buffer[1] & 0x000003ff) << 2) | ((Buffer[2] & 0xc0000000) >> 30);
            MULT = (Buffer[2] & 0x00038000) >> 15;
            size = (C_Size + 1) * (1 << (MULT + 2)) * (1 << R_LEN);

            pSD->diskSize = size / 1024;
            pSD->totalSectorN = size / 512;
        }
    }
    pSD->sectorSize = 512;
    //sysprintf("The size is %d KB\n", pSD->diskSize);
}

/// @endcond HIDDEN_SYMBOLS

/**
 *  @brief  This function use to tell FMI eMMC engine clock.
 *
 *  @param[in]  u32Clock   Set current eMMC engine clock
 *
 *  @return None
 */
void FMI_SetReferenceClock(unsigned int u32Clock)
{
    gFMIReferenceClock = u32Clock;  // kHz
}

/**
 *  @brief  This function use to reset FMI eMMC function.
 *
 *  @return None
 */
void eMMC_Open(void)
{
    // enable DMAC
    outpw(REG_FMI_DMACTL, FMI_DMACTL_DMARST_Msk);
    while (inpw(REG_FMI_DMACTL) & FMI_DMACTL_DMARST_Msk);

    outpw(REG_FMI_DMACTL, FMI_DMACTL_DMAEN_Msk);

    //Reset Global
    outpw(REG_FMI_CTL, FMI_CTL_CTLRST_Msk);
    while (inpw(REG_FMI_CTL) & FMI_CTL_CTLRST_Msk);

    // enable eMMC
    outpw(REG_FMI_CTL, FMI_CTL_EMMCEN_Msk);

    outpw(REG_FMI_EMMCCTL, inpw(REG_FMI_EMMCCTL) | FMI_EMMCCTL_CTLRST_Msk);
    while (inpw(REG_FMI_EMMCCTL) & FMI_EMMCCTL_CTLRST_Msk);

    memset(&eMMC, 0, sizeof(EMMC_INFO_T));
    eMMC.IsCardInsert = 1;
}

/**
 *  @brief  This function use to initial eMMC card.
 *
 *  @return None
 */
void eMMC_Probe(void)
{
    // Disable FMI interrupt
    outpw(REG_FMI_INTEN, 0);

    outpw(REG_FMI_EMMCCTL, inpw(REG_FMI_EMMCCTL) & ~(FMI_EMMCCTL_SDNWR_Msk | FMI_EMMCCTL_BLKCNT_Msk | FMI_EMMCCTL_DBW_Msk));
    outpw(REG_FMI_EMMCCTL, inpw(REG_FMI_EMMCCTL) | (0x09 << FMI_EMMCCTL_SDNWR_Pos) | (0x01 << FMI_EMMCCTL_BLKCNT_Pos));

    if (eMMC_Init(&eMMC) < 0)
        return;

    /* divider */
    if ((eMMC.CardType == EMMC_TYPE_MMC) || (eMMC.CardType == EMMC_TYPE_EMMC))
        eMMC_Set_clock(MMC_FREQ);
    else
        eMMC_Set_clock(SD_FREQ);

    eMMC_Get_info(&eMMC);

    if (eMMC_SelectCardType(&eMMC))
        return;

    emmc_ok = 1;
}

/**
 *  @brief  This function use to read data from eMMC card.
 *
 *  @param[out]    pu8BufAddr    The buffer to receive the data from eMMC card.
 *  @param[in]     u32StartSec   The start read sector address.
 *  @param[in]     u32SecCount   The the read sector number of data
 *
 *  @return None
 */
unsigned int eMMC_Read(unsigned char *pu8BufAddr, unsigned int u32StartSec, unsigned int u32SecCount)
{
    char volatile bIsSendCmd = FALSE;
    unsigned int volatile reg;
    int volatile i, loop, status;
    unsigned int blksize = FMI_BLOCK_SIZE;

    EMMC_INFO_T *pSD;
    pSD = &eMMC;

    //--- check input parameters
    if (u32SecCount == 0)
        return EMMC_SELECT_ERROR;

    if ((status = eMMC_CmdAndRsp(pSD, 7, pSD->RCA, 0)) != 0)
        return status;
    eMMC_CheckRB();

    outpw(REG_FMI_EMMCBLEN, blksize - 1);       // the actual byte count is equal to (BLEN+1)

    if ((pSD->CardType == EMMC_TYPE_SD_HIGH) || (pSD->CardType == EMMC_TYPE_EMMC))
        outpw(REG_FMI_EMMCCMD, u32StartSec);
    else
        outpw(REG_FMI_EMMCCMD, u32StartSec * blksize);

    outpw(REG_FMI_DMASA, (unsigned int)pu8BufAddr);

    loop = u32SecCount / 255;
    for (i = 0; i < loop; i++)
    {
        _fmi_eMMCDataReady = FALSE;

        reg = inpw(REG_FMI_EMMCCTL) & ~FMI_EMMCCTL_CMDCODE_Msk;
        reg = reg | 0xff0000;
        if (bIsSendCmd == FALSE)
        {
            outpw(REG_FMI_EMMCCTL, reg | (18 << 8) | (FMI_EMMCCTL_COEN_Msk | FMI_EMMCCTL_RIEN_Msk | FMI_EMMCCTL_DIEN_Msk));
            bIsSendCmd = TRUE;
        }
        else
            outpw(REG_FMI_EMMCCTL, reg | FMI_EMMCCTL_DIEN_Msk);

        while (!_fmi_eMMCDataReady)
        {
//             if ((inpw(REG_FMI_EMMCINTSTS) & FMI_EMMCINTSTS_BLKDIF_Msk) && (!(inpw(REG_FMI_EMMCCTL) & FMI_EMMCCTL_DIEN_Msk))) {
//                 outpw(REG_FMI_EMMCINTSTS, FMI_EMMCINTSTS_BLKDIF_Msk);
//                 break;
//             }
            if (pSD->IsCardInsert == FALSE)
                return EMMC_NO_CARD;
        }

        if (!(inpw(REG_FMI_EMMCINTSTS) & FMI_EMMCINTSTS_CRC7_Msk))      // check CRC7
        {
            return EMMC_CRC7_ERROR;
        }

        if (!(inpw(REG_FMI_EMMCINTSTS) & FMI_EMMCINTSTS_CRC16_Msk))     // check CRC16
        {
            return EMMC_CRC16_ERROR;
        }
    }

    loop = u32SecCount % 255;
    if (loop != 0)
    {
        _fmi_eMMCDataReady = FALSE;

        reg = inpw(REG_FMI_EMMCCTL) & (~FMI_EMMCCTL_CMDCODE_Msk);
        reg = reg & (~FMI_EMMCCTL_BLKCNT_Msk);
        reg |= (loop << 16);

        if (bIsSendCmd == FALSE)
        {
            outpw(REG_FMI_EMMCCTL, reg | (18 << 8) | (FMI_EMMCCTL_COEN_Msk | FMI_EMMCCTL_RIEN_Msk | FMI_EMMCCTL_DIEN_Msk));
            bIsSendCmd = TRUE;
        }
        else
            outpw(REG_FMI_EMMCCTL, reg | FMI_EMMCCTL_DIEN_Msk);

        while (!_fmi_eMMCDataReady)
        {
//             if ((inpw(REG_FMI_EMMCINTSTS) & FMI_EMMCINTSTS_BLKDIF_Msk) && (!(inpw(REG_FMI_EMMCCTL) & FMI_EMMCCTL_DIEN_Msk))) {
//                 outpw(REG_FMI_EMMCINTSTS, FMI_EMMCINTSTS_BLKDIF_Msk);
//                 break;
//             }
            if (pSD->IsCardInsert == FALSE)
                return EMMC_NO_CARD;
        }

        if (!(inpw(REG_FMI_EMMCINTSTS) & FMI_EMMCINTSTS_CRC7_Msk))      // check CRC7
        {
            return EMMC_CRC7_ERROR;
        }

        if (!(inpw(REG_FMI_EMMCINTSTS) & FMI_EMMCINTSTS_CRC16_Msk))     // check CRC16
        {
            return EMMC_CRC16_ERROR;
        }
    }

    if (eMMC_CmdAndRsp(pSD, 12, 0, 0))      // stop command
    {
        //sysprintf("stop command fail !!\n");
        return EMMC_CRC7_ERROR;
    }
    eMMC_CheckRB();

    eMMC_Command(pSD, 7, 0);
    outpw(REG_FMI_EMMCCTL, inpw(REG_FMI_EMMCCTL) | FMI_EMMCCTL_CLK8OEN_Msk);
    while (inpw(REG_FMI_EMMCCTL) & FMI_EMMCCTL_CLK8OEN_Msk);

    return 0;
}


/**
 *  @brief  This function use to write data to eMMC card.
 *
 *  @param[in]    pu8BufAddr    The buffer to send the data to SD card.
 *  @param[in]    u32StartSec   The start write sector address.
 *  @param[in]    u32SecCount   The the write sector number of data.
 *
 *  @return   - \ref EMMC_SELECT_ERROR  u32SecCount is zero.
 *            - \ref EMMC_NO_CARD  SD card be removed.
 *            - \ref EMMC_CRC_ERROR  CRC error happen.
 *            - \ref EMMC_CRC7_ERROR  CRC7 error happen.
 *            - \ref Successful  Write data to eMMC card success.
 */
unsigned int eMMC_Write(unsigned char *pu8BufAddr, unsigned int u32StartSec, unsigned int u32SecCount)
{
    char volatile bIsSendCmd = FALSE;
    unsigned int volatile reg;
    int volatile i, loop, status;

    EMMC_INFO_T *pSD;
    pSD = &eMMC;

    //--- check input parameters
    if (u32SecCount == 0)
        return EMMC_SELECT_ERROR;

    if ((status = eMMC_CmdAndRsp(pSD, 7, pSD->RCA, 0)) != 0)
        return status;

    eMMC_CheckRB();

    // According to SD Spec v2.0/ eMMC v4.4, the write CMD block size MUST be 512, and the start address MUST be 512*n.
    outpw(REG_FMI_EMMCBLEN, FMI_BLOCK_SIZE - 1);           // set the block size

    if ((pSD->CardType == EMMC_TYPE_SD_HIGH) || (pSD->CardType == EMMC_TYPE_EMMC))
        outpw(REG_FMI_EMMCCMD, u32StartSec);
    else
        outpw(REG_FMI_EMMCCMD, u32StartSec * FMI_BLOCK_SIZE);  // set start address for CMD

    outpw(REG_FMI_DMASA, (unsigned int)pu8BufAddr);
    loop = u32SecCount / 255;   // the maximum block count is 0xFF=255
    for (i = 0; i < loop; i++)
    {
        _fmi_eMMCDataReady = FALSE;

        reg = inpw(REG_FMI_EMMCCTL) & 0xff00c080;
        reg = reg | 0xff0000;
        if (!bIsSendCmd)
        {
            outpw(REG_FMI_EMMCCTL, reg | (25 << 8) | (FMI_EMMCCTL_COEN_Msk | FMI_EMMCCTL_RIEN_Msk | FMI_EMMCCTL_DOEN_Msk));
            bIsSendCmd = TRUE;
        }
        else
            outpw(REG_FMI_EMMCCTL, reg | FMI_EMMCCTL_DOEN_Msk);

        while (!_fmi_eMMCDataReady)
        {
//             if ((inpw(REG_FMI_EMMCINTSTS) & FMI_EMMCINTSTS_BLKDIF_Msk) && (!(inpw(REG_FMI_EMMCCTL) & FMI_EMMCCTL_DOEN_Msk))) {
//                 outpw(REG_FMI_EMMCINTSTS, FMI_EMMCINTSTS_BLKDIF_Msk);
//                 break;
//             }
            if (pSD->IsCardInsert == FALSE)
                return EMMC_NO_CARD;
        }

        if ((inpw(REG_FMI_EMMCINTSTS) & FMI_EMMCINTSTS_CRCIF_Msk) != 0)     // check CRC
        {
            outpw(REG_FMI_EMMCINTSTS, FMI_EMMCINTSTS_CRCIF_Msk);
            return EMMC_CRC_ERROR;
        }
    }

    loop = u32SecCount % 255;
    if (loop != 0)
    {
        _fmi_eMMCDataReady = FALSE;

        reg = (inpw(REG_FMI_EMMCCTL) & 0xff00c080) | (loop << 16);
        if (!bIsSendCmd)
        {
            outpw(REG_FMI_EMMCCTL, reg | (25 << 8) | (FMI_EMMCCTL_COEN_Msk | FMI_EMMCCTL_RIEN_Msk | FMI_EMMCCTL_DOEN_Msk));
            bIsSendCmd = TRUE;
        }
        else
            outpw(REG_FMI_EMMCCTL, reg | FMI_EMMCCTL_DOEN_Msk);

        while (!_fmi_eMMCDataReady)
        {
//             if ((inpw(REG_FMI_EMMCINTSTS) & FMI_EMMCINTSTS_BLKDIF_Msk) && (!(inpw(REG_FMI_EMMCCTL) & FMI_EMMCCTL_DOEN_Msk))) {
//                 outpw(REG_FMI_EMMCINTSTS, FMI_EMMCINTSTS_BLKDIF_Msk);
//                 break;
//             }
            if (pSD->IsCardInsert == FALSE)
                return EMMC_NO_CARD;
        }

        if ((inpw(REG_FMI_EMMCINTSTS) & FMI_EMMCINTSTS_CRCIF_Msk) != 0)     // check CRC
        {
            outpw(REG_FMI_EMMCINTSTS, FMI_EMMCINTSTS_CRCIF_Msk);
            return EMMC_CRC_ERROR;
        }
    }
    outpw(REG_FMI_EMMCINTSTS, FMI_EMMCINTSTS_CRCIF_Msk);

    if (eMMC_CmdAndRsp(pSD, 12, 0, 0))      // stop command
    {
        return EMMC_CRC7_ERROR;
    }
    eMMC_CheckRB();

    eMMC_Command(pSD, 7, 0);
    outpw(REG_FMI_EMMCCTL, inpw(REG_FMI_EMMCCTL) | FMI_EMMCCTL_CLK8OEN_Msk);
    while (inpw(REG_FMI_EMMCCTL) & FMI_EMMCCTL_CLK8OEN_Msk);

    return 0;
}


/*@}*/ /* end of group N9H30_FMI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group N9H30_FMI_Driver */

/*@}*/ /* end of group N9H30_Device_Driver */

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/


