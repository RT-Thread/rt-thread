/**************************************************************************//**
* @file     i2s.c
* @brief    N9H30 I2S driver source file
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
#include "nu_i2s.h"

/** @addtogroup N9H30_Device_Driver N9H30 Device Driver
  @{
*/

/** @addtogroup N9H30_I2S_Driver I2S Driver
  @{
*/

/** @addtogroup N9H30_I2S_EXPORTED_CONSTANTS I2S Exported Constants
  @{
*/

/// @cond HIDDEN_SYMBOLS

typedef uint32_t (AU_CB_FUNC_T)(uint32_t);

static AU_CB_FUNC_T *g_fnPlayCallBack;
static AU_CB_FUNC_T *g_fnRecCallBack;
static uint8_t i2sOpened = 0;

/// @endcond /* HIDDEN_SYMBOLS */

/*@}*/ /* end of group N9H30_I2S_EXPORTED_CONSTANTS */

/** @addtogroup N9H30_I2S_EXPORTED_FUNCTIONS I2S Exported Functions
  @{
*/

/// @cond HIDDEN_SYMBOLS
/**
  * @brief Start to play
  * @param None
  * @return None
  */
static void i2sStartPlay(void)
{
    /* start playing */
    //sysprintf("IIS start playing...\n");

    outpw(REG_ACTL_PSR, 0x1);
    outpw(REG_ACTL_RESET, inpw(REG_ACTL_RESET) | (1 << 5));
}

/**
  * @brief Stop to play
  * @param None
  * @return None
  */
static void i2sStopPlay(void)
{
    //sysprintf("IIS stop playing\n");

    /* stop playing */
    outpw(REG_ACTL_RESET, inpw(REG_ACTL_RESET) & ~(1 << 5));
}

/**
  * @brief Start to record
  * @param None
  * @return None
  */
static void i2sStartRecord(void)
{
    /* start recording */
    //sysprintf("IIS start recording...\n");

    outpw(REG_ACTL_RSR, 0x1);
    outpw(REG_ACTL_RESET, inpw(REG_ACTL_RESET) | (1 << 6));
}

/**
  * @brief Stop to record
  * @param None
  * @return None
  */
static void i2sStopRecord(void)
{
    //sysprintf("I2S stop recording\n");

    /* stop recording */
    outpw(REG_ACTL_RESET, inpw(REG_ACTL_RESET) & ~(1 << 6));
}

/**
  * @brief Delay function
  * @param None
  * @return None
  */
static void Delay(int nCnt)
{
    int volatile loop;
    for (loop = 0; loop < nCnt * 10; loop++);
}

/**
  * @brief Interrupt service routine for i2s
  * @param None
  * @return None
  */
static void i2sISR(void)
{
    uint8_t u8SN;

    if (inpw(REG_ACTL_CON) & (1 << 10))
    {
        outpw(REG_ACTL_CON, inpw(REG_ACTL_CON) | (1 << 10)); //Clear TX INT

        if (inpw(REG_ACTL_PSR) & (1 << 4))
        {
            outpw(REG_ACTL_PSR, (1 << 4));
            //sysprintf("\ndebug:DMA_COUNTER_IRQ occur");
        }

        if (inpw(REG_ACTL_PSR) & (1 << 3))
        {
            outpw(REG_ACTL_PSR, (1 << 3));
            //sysprintf("\ndebug:DMA_DATA_ZERO_IRQ occur");
        }

        if (inpw(REG_ACTL_PSR) & 0x1)
        {
            outpw(REG_ACTL_PSR, 0x1);
            u8SN = (inpw(REG_ACTL_PSR) >> 5) & 0x7;
            g_fnPlayCallBack(u8SN);
        }
    }

    if (inpw(REG_ACTL_CON) & (1 << 11))
    {
        outpw(REG_ACTL_CON, inpw(REG_ACTL_CON) | (1 << 11)); //Clear RX INT

        if (inpw(REG_ACTL_RSR) & 0x1)
        {
            outpw(REG_ACTL_RSR, 0x1);
            u8SN = (inpw(REG_ACTL_RSR) >> 5) & 0x7;
            g_fnRecCallBack(u8SN);
        }
    }
}
/// @endcond /* HIDDEN_SYMBOLS */

/**
  * @brief Open i2s interface
  * @return open status
  * @retval I2S_ERR_BUSY error.
  * @retval 0 success.
  */
int32_t i2sOpen(void)
{
    if (i2sOpened)
        return I2S_ERR_BUSY;

    /* reset audio interface */
    outpw(REG_ACTL_RESET, inpw(REG_ACTL_RESET) | (1 << 16));
    Delay(100);
    outpw(REG_ACTL_RESET, inpw(REG_ACTL_RESET) & ~(1 << 16));
    Delay(100);

    /* reset IIS interface */
    outpw(REG_ACTL_RESET, inpw(REG_ACTL_RESET) | 0x1);
    Delay(100);
    outpw(REG_ACTL_RESET, inpw(REG_ACTL_RESET) & ~0x1);
    Delay(100);

    outpw(REG_ACTL_CON, inpw(REG_ACTL_CON) | (1 << 21) | (1 << 20));

    i2sOpened = 1;

    return 0;
}

/**
  * @brief Close i2s interface
  * @return None
  */
void i2sClose(void)
{
    // reset some variables
    i2sOpened = 0;
    g_fnPlayCallBack = NULL;
    g_fnRecCallBack = NULL;

    // reset i2s interface
    outpw(REG_SYS_AHBIPRST, inpw(REG_SYS_AHBIPRST) | (1 << 8));
    outpw(REG_SYS_AHBIPRST, inpw(REG_SYS_AHBIPRST) & ~(1 << 8));
}

/**
  * @brief Initialize i2s interface and setup interrupt
  * @return None
  */
void i2sInit(void)
{
    // enable i2s engine clock
    outpw(REG_CLK_HCLKEN, inpw(REG_CLK_HCLKEN) | (1 << 24));

    // enable interrupt and set ISR
    sysSetInterruptType(ACTL_IRQn, HIGH_LEVEL_SENSITIVE);
    sysInstallISR(IRQ_LEVEL_1, ACTL_IRQn, (PVOID)i2sISR);
    sysEnableInterrupt(ACTL_IRQn);
    sysSetLocalInterrupt(ENABLE_IRQ);
}

/**
  * @brief IO control for i2s interface
  * @param[in] cmd Command for io control, value could be
  *                                     - \ref I2S_SET_PLAY
  *                                     - \ref I2S_SET_RECORD
  *                                     - \ref I2S_SELECT_BLOCK
  *                                     - \ref I2S_SELECT_BIT
  *                                     - \ref I2S_SET_PLAY_DMA_INT_SEL
  *                                     - \ref I2S_SET_REC_DMA_INT_SEL
  *                                     - \ref I2S_SET_ZEROCROSS
  *                                     - \ref I2S_SET_DMACOUNTER
  *                                     - \ref I2S_SET_CHANNEL
  *                                     - \ref I2S_SET_MODE
  *                                     - \ref I2S_SET_SPLITDATA
  *                                     - \ref I2S_SET_DMA_ADDRESS
  *                                     - \ref I2S_SET_DMA_LENGTH
  *                                     - \ref I2S_GET_DMA_CUR_ADDRESS
  *                                     - \ref I2S_SET_I2S_FORMAT
  *                                     - \ref I2S_SET_I2S_CALLBACKFUN
  *                                     - \ref I2S_SET_PCMSLOT
  * @param[in] arg0 argument 0 for io control
  * @param[in] arg1 argument 1 for io control
  * @retval I2S_ERR_IO Command error.
  * @retval 0 success.
  */
int32_t i2sIoctl(uint32_t cmd, uint32_t arg0, uint32_t arg1)
{
    uint32_t *buf;
    AU_CB_FUNC_T *ptr;

    switch (cmd)
    {
    // #define I2S_START_PLAY  0
    // #define I2S_STOP_PLAY   1
    case I2S_SET_PLAY:
        if (arg0 == I2S_START_PLAY)
            i2sStartPlay();
        else
            i2sStopPlay();
        break;
    // #define I2S_START_REC  0
    // #define I2S_STOP_REC   1
    case I2S_SET_RECORD:
        if (arg0 == I2S_START_REC)
            i2sStartRecord();
        else
            i2sStopRecord();
        break;
    // #define I2S_BLOCK_I2S  0
    // #define I2S_BLOCK_PCM   1
    case I2S_SELECT_BLOCK:
        if (arg0 == I2S_BLOCK_I2S)
            outpw(REG_ACTL_CON, (inpw(REG_ACTL_CON) & ~0x3) | 0x1);
        else
            outpw(REG_ACTL_CON, (inpw(REG_ACTL_CON) & ~0x3) | 0x2);
        break;
    // #define I2S_BIT_WIDTH_8  0
    // #define I2S_BIT_WIDTH_16 1
    // #define I2S_BIT_WIDTH_24 2
    case I2S_SELECT_BIT:
        outpw(REG_ACTL_CON, (inpw(REG_ACTL_CON) & ~0x300) | (arg0 << 8));
        break;
    // #define I2S_DMA_INT_END         0
    // #define I2S_DMA_INT_HALF        1
    // #define I2S_DMA_INT_QUARTER     2
    // #define I2S_DMA_INT_EIGTH       3
    case I2S_SET_PLAY_DMA_INT_SEL:
        outpw(REG_ACTL_CON, (inpw(REG_ACTL_CON) & ~0x3000) | (arg0 << 12));
        break;

    case I2S_SET_REC_DMA_INT_SEL:
        outpw(REG_ACTL_CON, (inpw(REG_ACTL_CON) & ~0xc000) | (arg0 << 14));
        break;

    case I2S_SET_ZEROCROSS:
        if (arg0 == I2S_ENABLE)
            outpw(REG_ACTL_RESET, inpw(REG_ACTL_RESET) | 0x8);
        else
            outpw(REG_ACTL_RESET, inpw(REG_ACTL_RESET) & ~0x8);
        break;

    case I2S_SET_DMACOUNTER:
        if (arg0 == I2S_ENABLE)
            outpw(REG_ACTL_RESET, inpw(REG_ACTL_RESET) | 0x10);
        else
            outpw(REG_ACTL_RESET, inpw(REG_ACTL_RESET) & ~0x10);
        break;
    // #define I2S_CHANNEL_I2S_ONE         2
    // #define I2S_CHANNEL_I2S_TWO         3
    // #define I2S_CHANNEL_PCM_TWO         3
    // #define I2S_CHANNEL_PCM_TWO_SLOT1   0
    // #define I2S_CHANNEL_PCM_TWO_SLOT0   1
    // #define I2S_CHANNEL_PCM_ONE_SLOT0   2
    case I2S_SET_CHANNEL:
        if (arg0 == I2S_PLAY)
            outpw(REG_ACTL_RESET, inpw(REG_ACTL_RESET) & ~(0x3 << 12) | (arg1 << 12));
        else
            outpw(REG_ACTL_RESET, inpw(REG_ACTL_RESET) & ~(0x3 << 14) | (arg1 << 14));
        break;
    // #define I2S_MODE_MASTER  0
    // #define I2S_MODE_SLAVE  1
    case I2S_SET_MODE:
        if (arg0 == I2S_MODE_MASTER)
            outpw(REG_ACTL_I2SCON, inpw(REG_ACTL_I2SCON) & ~(0x1 << 20));
        else
            outpw(REG_ACTL_I2SCON, inpw(REG_ACTL_I2SCON) | (0x1 << 20));
        break;

    case I2S_SET_SPLITDATA:
        if (arg0 == I2S_ENABLE)
            outpw(REG_ACTL_RESET, inpw(REG_ACTL_RESET) | (0x1 << 20));
        else
            outpw(REG_ACTL_RESET, inpw(REG_ACTL_RESET) & ~(0x1 << 20));
        break;

    case I2S_SET_DMA_ADDRESS:
        if (arg0 == I2S_PLAY)
            outpw(REG_ACTL_PDESB, arg1 | 0x80000000);
        else if (arg0 == I2S_REC)
            outpw(REG_ACTL_RDESB, arg1 | 0x80000000);
        else if (arg0 == PCM_PLAY)
            outpw(REG_ACTL_PDESB2, arg1 | 0x80000000);
        else
            outpw(REG_ACTL_RDESB2, arg1 | 0x80000000);
        break;

    case I2S_SET_DMA_LENGTH:
        if (arg0 == I2S_PLAY)
            outpw(REG_ACTL_PDES_LENGTH, arg1);
        else
            outpw(REG_ACTL_RDES_LENGTH, arg1);
        break;

    case I2S_GET_DMA_CUR_ADDRESS:
        buf = (uint32_t *)arg0;
        if (arg0 == I2S_PLAY)
            *buf = inpw(REG_ACTL_PDESC);
        else
            *buf = inpw(REG_ACTL_RDESC);
        break;

    // #define I2S_FORMAT_I2S  0
    // #define I2S_FORMAT_MSB  1
    case I2S_SET_I2S_FORMAT:
        if (arg0 == I2S_FORMAT_I2S)
            outpw(REG_ACTL_I2SCON, inpw(REG_ACTL_I2SCON) & ~ 0x8);
        else
            outpw(REG_ACTL_I2SCON, inpw(REG_ACTL_I2SCON) | 0x8);
        break;

    case I2S_SET_I2S_CALLBACKFUN:
        ptr = (AU_CB_FUNC_T *)arg1;
        if (arg0 == I2S_PLAY)
            g_fnPlayCallBack = ptr;
        else
            g_fnRecCallBack = ptr;
        break;
    // #define PCM_SLOT1_IN        0
    // #define PCM_SLOT1_OUT       1
    // #define PCM_SLOT2_IN        2
    // #define PCM_SLOT2_OUT       3
    case I2S_SET_PCMSLOT:
        if (arg0 == PCM_SLOT1_IN)
            outpw(REG_ACTL_PCMS1ST, (inpw(REG_ACTL_PCMS1ST) & ~0x3ff) | (arg1 & 0x3ff));
        else if (arg0 == PCM_SLOT1_OUT)
            outpw(REG_ACTL_PCMS1ST, (inpw(REG_ACTL_PCMS1ST) & ~0x3ff0000) | ((arg1 & 0x3ff) << 16));
        else if (arg0 == PCM_SLOT2_IN)
            outpw(REG_ACTL_PCMS2ST, (inpw(REG_ACTL_PCMS2ST) & ~0x3ff) | (arg1 & 0x3ff));
        else
            outpw(REG_ACTL_PCMS2ST, (inpw(REG_ACTL_PCMS2ST) & ~0x3ff0000) | ((arg1 & 0x3ff) << 16));
        break;

    case I2S_SET_PCM_FS_PERIOD:
        outpw(REG_ACTL_PCMCON, (inpw(REG_ACTL_PCMCON) & ~0x03FF0000 | (((arg0 - 1) & 0x3ff) << 16)));
        break;

    default:
        return I2S_ERR_IO;
    }
    return 0;
}

/**
  * @brief Configure sampling rate for audio
  * @param[in] u32SourceClockRate source speed to i2s interface
  * @param[in] u32SampleRate sampling rate
  * @param[in] u32DataBit data width
  * @param[in] u32Channel channel number
  * @return None
  */
void i2sSetSampleRate(uint32_t u32SourceClockRate, uint32_t u32SampleRate, uint32_t u32DataBit, uint32_t u32Channel)
{
    uint32_t u32BCLKDiv;
    uint32_t u32MCLK, u32MCLKDiv;

    u32MCLK = (u32SampleRate * 256);
    u32MCLKDiv = u32SourceClockRate / u32MCLK;
    outpw(REG_ACTL_I2SCON, (inpw(REG_ACTL_I2SCON) & ~0x000F0000) | (u32MCLKDiv - 1) << 16);

    u32BCLKDiv = u32MCLK / (u32SampleRate * u32DataBit * u32Channel);
    u32BCLKDiv = u32BCLKDiv / 2 - 1;
    outpw(REG_ACTL_I2SCON, (inpw(REG_ACTL_I2SCON) & ~0xF0) | u32BCLKDiv << 5);
}

/**
  * @brief Configure MCLK frequency (master mode)
  * @param[in] u32SourceClockRate source clock rate
  * @param[in] u32SampleRate sampling rate
  * @return None
  */
void i2sSetMCLKFrequency(uint32_t u32SourceClockRate, uint32_t u32SampleRate)
{
    uint32_t u32MCLK, u32MCLKDiv;

    u32MCLK = (u32SampleRate * 256);
    u32MCLKDiv = u32SourceClockRate / u32MCLK;
    outpw(REG_ACTL_I2SCON, (inpw(REG_ACTL_I2SCON) & ~0x000F0000) | (u32MCLKDiv - 1) << 16);
}

/**
  * @brief Configure PCM BCLK frequency (master mode)
  * @param[in] u32SourceClockRate source clock rate
  * @param[in] u32Rate target rate
  * @return None
  */
void i2sSetPCMBCLKFrequency(uint32_t u32SourceClockRate, uint32_t u32Rate)
{
    uint32_t u32BCLKDiv;

    u32BCLKDiv = (u32SourceClockRate / (2 * u32Rate)) - 1;
    outpw(REG_ACTL_PCMCON, (inpw(REG_ACTL_PCMCON) & ~0x0000FF00) | (u32BCLKDiv << 8));
}


/*@}*/ /* end of group N9H30_I2S_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group N9H30_I2S_Driver */

/*@}*/ /* end of group N9H30_Device_Driver */

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/

