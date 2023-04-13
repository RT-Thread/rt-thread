/****************************************************************************//**
 * @file     nu_sdh.h
 * @brief    SDH driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_SDH_H__
#define __NU_SDH_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SDH_Driver SDH Driver
  @{
*/

/** @addtogroup SDH_EXPORTED_CONSTANTS SDH Exported Constants
  @{
*/

#define  SDH_POWER_ON            0x01
#define  SDH_POWER_180           0x0A
#define  SDH_POWER_300           0x0C
#define  SDH_POWER_330           0x0E

#define  SDH_RESET_ALL           0x01
#define  SDH_RESET_CMD           0x02
#define  SDH_RESET_DATA          0x04

#define  SDH_CMD_RESP_MASK       0x03
#define  SDH_CMD_CRC             0x08
#define  SDH_CMD_INDEX           0x10
#define  SDH_CMD_DATA            0x20
#define  SDH_CMD_ABORTCMD        0xC0

#define  SDH_CMD_RESP_NONE       0x00
#define  SDH_CMD_RESP_LONG       0x01
#define  SDH_CMD_RESP_SHORT      0x02
#define  SDH_CMD_RESP_SHORT_BUSY 0x03


/* MMC command */
#define MMC_CMD_STOP_TRANSMISSION       12

/* MMC response */
#define MMC_RSP_PRESENT (1 << 0)
#define MMC_RSP_136     (1 << 1)        /* 136 bit response */
#define MMC_RSP_CRC     (1 << 2)        /* expect valid crc */
#define MMC_RSP_BUSY    (1 << 3)        /* card may send busy */
#define MMC_RSP_OPCODE  (1 << 4)        /* response contains opcode */

#define MMC_RSP_NONE    (0)
#define MMC_RSP_R1  (MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#define MMC_RSP_R1b (MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE|MMC_RSP_BUSY)
#define MMC_RSP_R2  (MMC_RSP_PRESENT|MMC_RSP_136|MMC_RSP_CRC)
#define MMC_RSP_R3  (MMC_RSP_PRESENT)
#define MMC_RSP_R4  (MMC_RSP_PRESENT)
#define MMC_RSP_R5  (MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#define MMC_RSP_R6  (MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#define MMC_RSP_R7  (MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)

#define MMC_DATA_READ       1
#define MMC_DATA_WRITE      2

#define SDH_BLOCK_SIZE   512ul

struct mmc_cmd
{
    unsigned short cmdidx;
    unsigned int   resp_type;
    unsigned int   cmdarg;
    unsigned int   response[4];
};

struct mmc_data
{
    union
    {
        char *dest;
        const char *src; /* src buffers don't get written to */
    };
    unsigned int flags;
    unsigned int blocks;
    unsigned int blocksize;
};

#define SDH_ISCARDINSERTED(SDH)   (SDH->S_PSTATE.CARD_INSERTED && SDH->S_PSTATE.CARD_STABLE)


/*@}*/ /* end of group SDH_EXPORTED_CONSTANTS */

/** @addtogroup SDH_EXPORTED_FUNCTIONS SDH Exported Functions
  @{
*/

void SDH_DumpReg(SDH_T *sdh);
void SDH_Reset(SDH_T *sdh, uint8_t u8Mask);
int SDH_SetBusWidth(SDH_T *sdh, uint32_t u32BusWidth);
uint32_t SDH_SetClock(SDH_T *sdh, uint32_t u32SrcFreqInHz, uint32_t u32ExceptedFreqInHz);
int SD_GetBusStatus(SDH_T *sdh, uint32_t cmdidx);
void SDH_SetPower(SDH_T *sdh, uint32_t u32OnOff);

/*@}*/ /* end of group SDH_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SDH_Driver */

/*@}*/ /* end of group Standard_Driver */
#ifdef __cplusplus
}
#endif

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif


