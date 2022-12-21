/**************************************************************************//**
* @file     nu_sdh.c
* @brief    SDH driver source file
*
* SPDX-License-Identifier: Apache-2.0
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NuMicro.h"
#include <string.h>

/** @addtogroup Standard_Driver Standard Driver
@{
*/

/** @addtogroup SDH_Driver SDH Driver
@{
*/

/** @addtogroup SDH_EXPORTED_FUNCTIONS SDH Exported Functions
@{
*/

#define SDH_DBG
#if defined(SDH_DBG)
    extern int rt_kprintf(const char *fmt, ...);
    #define SDH_DBG_PRINT         rt_kprintf
    extern void rt_hw_us_delay(uint32_t us);
    #define DelayMicrosecond rt_hw_us_delay

#else
    #define SDH_DBG_PRINT(...)
    #define DelayMicrosecond SDH_Delay
#endif

/* Print out register information:  Name, Offset, Current value, Reset value, match flag. */
#define DUMP_REG(BASE, NAME, DEFAULT)          SDH_DBG_PRINT("| %-24s | 0x%04x | 0x%08x | 0x%08x | %-6s |\n", #NAME, (uint32_t)&BASE->NAME - (uint32_t)BASE,  BASE->NAME, DEFAULT, ((BASE->NAME != DEFAULT) ? " N ":" Y ") )

#define PACK_MMC_CMD(CMD, IDX, ARG, RESP)  ( CMD.cmdidx=IDX,  CMD.cmdarg=ARG, CMD.resp_type=RESP )

#if !defined(SDH_DBG)
static void SDH_Delay(uint32_t u32LoopTime)
{
    volatile uint32_t i = 0x2000 * u32LoopTime;
    for (; i > 0; i--);
}
#endif

void SDH_DumpReg(SDH_T *sdh)
{

    SDH_DBG_PRINT("========================================================================\n");
    SDH_DBG_PRINT("SDH_T(0x%08x): %d\n", sdh, sizeof(SDH_T));
    SDH_DBG_PRINT("========================================================================\n");
    SDH_DBG_PRINT("| %-24s | %-6s | %-10s | %-10s | %-6s |\n", "REG NAME", "OFFSET", "CURRENT", "DEFAULT", "MATCH?");
    SDH_DBG_PRINT("========================================================================\n");
    DUMP_REG(sdh, SDMASA, 0x0);
    DUMP_REG(sdh, BLOCKSIZE, 0x0);
    DUMP_REG(sdh, BLOCKCOUNT, 0x0);
    DUMP_REG(sdh, ARGUMENT, 0x0);
    DUMP_REG(sdh, XFER_MODE, 0x0);
    DUMP_REG(sdh, CMD, 0x0);
    DUMP_REG(sdh, RESP01, 0x0);
    DUMP_REG(sdh, RESP23, 0x0);
    DUMP_REG(sdh, RESP45, 0x0);
    DUMP_REG(sdh, RESP67, 0x0);
    DUMP_REG(sdh, BUF_DATA, 0x0);
    DUMP_REG(sdh, PSTATE, 0x0);
    DUMP_REG(sdh, HOST_CTRL1, 0x0);
    DUMP_REG(sdh, PWR_CTRL, 0x0);

    DUMP_REG(sdh, BGAP_CTRL, 0x0);
    DUMP_REG(sdh, WUP_CTRL, 0x0);
    DUMP_REG(sdh, CLK_CTRL, 0x0);
    DUMP_REG(sdh, TOUT_CTRL, 0x0);
    DUMP_REG(sdh, SW_RST, 0x0);
    DUMP_REG(sdh, NORMAL_INT_STAT, 0x0);
    DUMP_REG(sdh, ERROR_INT_STAT, 0x0);
    DUMP_REG(sdh, NORMAL_INT_STAT_EN, 0x0);
    DUMP_REG(sdh, ERROR_INT_STAT_EN, 0x0);
    DUMP_REG(sdh, NORMAL_INT_SIGNAL_EN, 0x0);

    DUMP_REG(sdh, ERROR_INT_SIGNAL_EN, 0x0);
    DUMP_REG(sdh, AUTO_CMD_STAT, 0x0);
    DUMP_REG(sdh, HOST_CTRL2, 0x0);
    DUMP_REG(sdh, CAPABILITIES1, 0x276EC898);
    DUMP_REG(sdh, CAPABILITIES2, 0x08008077);
    DUMP_REG(sdh, CURR_CAPABILITIES1, 0x0);
    DUMP_REG(sdh, CURR_CAPABILITIES2, 0x0);
    DUMP_REG(sdh, FORCE_AUTO_CMD_STAT, 0x0);
    DUMP_REG(sdh, FORCE_ERROR_INT_STAT, 0x0);
    DUMP_REG(sdh, ADMA_ERR_STAT, 0x0);
    DUMP_REG(sdh, ADMA_SA_LOW, 0x0);
    DUMP_REG(sdh, PRESET_INIT, 0x0);
    DUMP_REG(sdh, PRESET_DS, 0x0);
    DUMP_REG(sdh, PRESET_HS, 0x0);
    DUMP_REG(sdh, PRESET_SDR12, 0x0);
    DUMP_REG(sdh, PRESET_SDR25, 0x0);
    DUMP_REG(sdh, PRESET_SDR50, 0x0);
    DUMP_REG(sdh, PRESET_SDR104, 0x0);
    DUMP_REG(sdh, PRESET_DDR50, 0x0);
    DUMP_REG(sdh, PRESET_UHS2, 0x0);
    DUMP_REG(sdh, P_EMBEDDED_CNTRL, 0x0F6C);
    DUMP_REG(sdh, P_VENDOR_SPECIFIC_AREA, 0x0500);
    DUMP_REG(sdh, P_VENDOR2_SPECIFIC_AREA, 0x0180);
    DUMP_REG(sdh, SLOT_INTR_STATUS, 0x0000);
    DUMP_REG(sdh, HOST_CNTRL_VERS, 0x0005);
    DUMP_REG(sdh, EMBEDDED_CTRL, 0x00000000);
    DUMP_REG(sdh, MSHC_VER_ID, 0x3138302A);
    DUMP_REG(sdh, MSHC_VER_TYPE, 0x67612A2A);
    DUMP_REG(sdh, MSHC_CTRL, 0x01);
    DUMP_REG(sdh, MBIU_CTRL, 0x0F);
    DUMP_REG(sdh, EMMC_CTRL, 0x000C);
    DUMP_REG(sdh, BOOT_CTRL, 0x0000);

    DUMP_REG(sdh, AT_CTRL, 0x03000005);
    DUMP_REG(sdh, AT_STAT, 0x00000006);
    DUMP_REG(sdh, CQCAP,   0x000030C8);
    SDH_DBG_PRINT("========================================================================\n");
}

void SDH_Reset(SDH_T *sdh, uint8_t u8Mask)
{
    /* Wait max 100 ms */
    unsigned int timeout = 100;

    sdh->SW_RST |= u8Mask;
    while (sdh->SW_RST & u8Mask)
    {
        if (timeout == 0)
        {
            SDH_DBG_PRINT("SD Reset fail\n");
            return;
        }
        timeout--;
        DelayMicrosecond(1000);
    }
}

void SDH_SetPower(SDH_T *sdh, uint32_t u32OnOff)
{
    if (u32OnOff)
    {
        /* Power on VDD1 */
        sdh->S_PWR_CTRL.SD_BUS_PWR_VDD1 = 1;

        /* Set 3.3v for EMMC, SD and */
        sdh->S_PWR_CTRL.SD_BUS_VOL_VDD1 = 7;
    }
    else
    {
        /* Power off VDD1 */
        sdh->S_PWR_CTRL.SD_BUS_PWR_VDD1 = 0;

        /* Set 0v for EMMC, SD and */
        sdh->S_PWR_CTRL.SD_BUS_VOL_VDD1 = 0;
    }
}

uint32_t SDH_SetClock(SDH_T *sdh, uint32_t u32SrcFreqInHz, uint32_t u32ExceptedFreqInHz)
{
    uint32_t timeout;
    uint32_t div;

    if (u32ExceptedFreqInHz == 0)
        goto exit_SDH_SetClock;

    /* Wait max 20 ms */
    timeout = 200;
    while (sdh->PSTATE & 0x3)   //(SDH_CMD_INHIBIT | SDH_DATA_INHIBIT))
    {
        if (timeout == 0)
        {
            SDH_DBG_PRINT("Timeout to wait cmd & data inhibit\n");
            goto exit_SDH_SetClock;
        }
        timeout--;
        DelayMicrosecond(100);
    }
    /* Shutdown clocks. */
    sdh->CLK_CTRL = 0;
    DelayMicrosecond(1000);

    div = (u32SrcFreqInHz / 2) / u32ExceptedFreqInHz;
    if (div > 0)
    {
        while ((u32SrcFreqInHz / (2 * div)) > u32ExceptedFreqInHz)
        {
            div++;
        }
    }

    sdh->S_CLK_CTRL.FREQ_SEL = div & 0xff;
    sdh->S_CLK_CTRL.UPPER_FREQ_SEL = (div >> 8) & 0x3;

    sdh->S_CLK_CTRL.INTERNAL_CLK_EN = 1;

    /* Wait stable */
    /* Wait max 20 ms */
    timeout = 200;
    while (!sdh->S_CLK_CTRL.INTERNAL_CLK_STABLE)
    {
        if (timeout == 0)
        {
            SDH_DBG_PRINT("Timeout to wait CLK stable.\n");
            goto exit_SDH_SetClock;
        }
        timeout--;
        DelayMicrosecond(100);
    }

    /* Enable SD CLK */
    sdh->S_CLK_CTRL.SD_CLK_EN = 1;

    return (div == 0) ? u32SrcFreqInHz : u32SrcFreqInHz / (2 * div);

exit_SDH_SetClock:

    sdh->CLK_CTRL = 0;

    return 0;
}

#define SDH_CMD_MAX_TIMEOUT         3200
#define SDH_CMD_DEFAULT_TIMEOUT     100
#define SDH_MAX_DIV_SPEC_300        2046

int SD_GetBusStatus(SDH_T *sdh, uint32_t mask)
{
    volatile unsigned int time = 0;
    volatile unsigned int cmd_timeout = SDH_CMD_DEFAULT_TIMEOUT;

    while (sdh->PSTATE & mask)
    {
        if (time >= cmd_timeout)
        {
            if (2 * cmd_timeout <= SDH_CMD_MAX_TIMEOUT)
            {
                cmd_timeout += cmd_timeout;
            }
            else
            {
                return -1;
            }
        }
        DelayMicrosecond(1000);
        time++;
    }
    return 0;
}

int SDH_SetBusWidth(SDH_T *sdh, uint32_t u32BusWidth)
{
    switch (u32BusWidth)
    {
    case 1:
        sdh->S_HOST_CTRL1.DAT_XFER_WIDTH = 0;
        sdh->S_HOST_CTRL1.EXT_DAT_XFER = 0;
        break;
    case 4:
        sdh->S_HOST_CTRL1.DAT_XFER_WIDTH = 1;
        sdh->S_HOST_CTRL1.EXT_DAT_XFER = 0;
        break;
    case 8:
        sdh->S_HOST_CTRL1.DAT_XFER_WIDTH = 1;
        sdh->S_HOST_CTRL1.EXT_DAT_XFER = 1;
        break;
    }
    return 0;
}

/*@}*/ /* end of group SDH_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SDH_Driver */

/*@}*/ /* end of group Standard_Driver */

