/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-08 13:45:05
 * @LastEditTime: 2021-04-15 15:12:03
 * @Description:  This files is for 
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef _FT_SDMMC_COMMON_H_
#define _FT_SDMMC_COMMON_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "ft_types.h"
#include "ft_debug.h"
#include "ft_error_code.h"
#include "ft_sdmmc.h"

#define SDMMC_GO_IDLE_DELAY_MS              20
#define SDMMC_IO_SEND_OP_COND_DELAY_MS      10

/* These delay values are mostly useful for cases when CD pin is not used, and
 * the card is removed. In this case, SDMMC peripheral may not always return
 * CMD_DONE / DATA_DONE interrupts after signaling the error. These timeouts work
 * as a safety net in such cases.
 */
#define SDMMC_DEFAULT_CMD_TIMEOUT_MS  1000   // Max timeout of ordinary commands
#define SDMMC_WRITE_CMD_TIMEOUT_MS    5000   // Max timeout of write commands

/* Maximum retry/error count for SEND_OP_COND (CMD1).
 * These are somewhat arbitrary, values originate from OpenBSD driver.
 */
#define SDMMC_SEND_OP_COND_MAX_RETRIES  100
#define SDMMC_SEND_OP_COND_MAX_ERRORS   3

/* Functions to send individual commands */
ft_error_t Sdmmc_SendCmd(Sdmmc_Card_t* card, Sdmmc_Cmd_t* cmd);
ft_error_t Sdmmc_SendAppCmd(Sdmmc_Card_t* card, Sdmmc_Cmd_t* cmd);
ft_error_t Sdmmc_SendCmdGoIdleState(Sdmmc_Card_t* card);
ft_error_t Sdmmc_SendCmdSendIfCond(Sdmmc_Card_t* card, u32 ocr);
ft_error_t Sdmmc_SendCmdSendOpCond(Sdmmc_Card_t* card, u32 ocr, u32 *ocrp);
ft_error_t Sdmmc_SendCmdReadOCR(Sdmmc_Card_t *card, u32 *ocrp);
ft_error_t Sdmmc_SendCmdSendCID(Sdmmc_Card_t *card, Sdmmc_CID_t *out_cid);
ft_error_t Sdmmc_SendCmdAllSendCID(Sdmmc_Card_t* card, Sdmmc_Resp_t* out_raw_cid);
ft_error_t Sdmmc_SendCmdSetRelativeAddr(Sdmmc_Card_t* card, u16* out_rca);
ft_error_t Sdmmc_SendCmdSetBlkLen(Sdmmc_Card_t* card, Sdmmc_CSD_t* csd);
ft_error_t Sdmmc_SendCmdSwitchFunc(Sdmmc_Card_t* card,
        u32 mode, u32 group, u32 function,
        Sdmmc_SwitchFuncRsp_t* resp);
ft_error_t Sdmmc_SendCmdSendCSD(Sdmmc_Card_t* card, Sdmmc_CSD_t* out_csd);
ft_error_t Sdmmc_SendCmdSelectCard(Sdmmc_Card_t* card, u32 rca);
ft_error_t Sdmmc_SendCmdSendSCR(Sdmmc_Card_t* card, Sdmmc_SCR_t *out_scr);
ft_error_t Sdmmc_SendCmdSwitch(Sdmmc_Card_t *card);
ft_error_t Sdmmc_SendCmdSetBusWidth(Sdmmc_Card_t* card, int width);
ft_error_t Sdmmc_SendCmdSendStatus(Sdmmc_Card_t* card, u32* out_status);
ft_error_t Sdmmc_SendCmdCrcOnOff(Sdmmc_Card_t* card, bool_t crc_enable);

/* Higher level functions */
ft_error_t Sdmmc_EnableHsMode(Sdmmc_Card_t* card);
ft_error_t Sdmmc_EnableHsModeAndCheck(Sdmmc_Card_t* card);
ft_error_t Sdmmc_WriteSectorsDMA(Sdmmc_Card_t* card, const void* src,
        size_t start_block, size_t block_count);
ft_error_t Sdmmc_ReadSectorsDMA(Sdmmc_Card_t* card, void* dst,
        size_t start_block, size_t block_count);

/* SD specific */
ft_error_t Sdmmc_CheckSCR(Sdmmc_Card_t* card);
ft_error_t Sdmmc_DecodeCID(Sdmmc_Resp_t resp, Sdmmc_CID_t* out_cid);
ft_error_t Sdmmc_DecodeCSD(Sdmmc_Resp_t response, Sdmmc_CSD_t* out_csd);
ft_error_t Sdmmc_DecodeSCR(u32 *raw_scr, Sdmmc_SCR_t* out_scr);

/* MMC specific */
ft_error_t Sdmmc_MMCSendExtCSDData(Sdmmc_Card_t* card, void *out_data, size_t datalen);
ft_error_t Sdmmc_MMCSwitch(Sdmmc_Card_t* card, u8 set, u8 index, u8 value);
ft_error_t Sdmmc_MMCDecodeCID(int mmcVer, Sdmmc_Resp_t resp, Sdmmc_CID_t* out_cid);
ft_error_t Sdmmc_MMCDecodeCSD(Sdmmc_Resp_t response, Sdmmc_CSD_t* out_csd);
ft_error_t Sdmmc_MMCEnableHsMode(Sdmmc_Card_t* card);

/* Parts of card initialization flow */
ft_error_t Sdmmc_InitSdIfCond(Sdmmc_Card_t* card);
ft_error_t Sdmmc_InitSelectCard(Sdmmc_Card_t* card);
ft_error_t Sdmmc_InitCSD(Sdmmc_Card_t* card);
ft_error_t Sdmmc_InitCID(Sdmmc_Card_t* card);
ft_error_t Sdmmc_InitRCA(Sdmmc_Card_t* card);
ft_error_t Sdmmc_InitMMCDecodeCID(Sdmmc_Card_t* card);
ft_error_t Sdmmc_InitOCR(Sdmmc_Card_t* card);
ft_error_t Sdmmc_InitSpiCrc(Sdmmc_Card_t* card);
//ft_error_t sdmmc_init_io(Sdmmc_Card_t* card);
ft_error_t Sdmmc_InitSdBlkLen(Sdmmc_Card_t* card);
ft_error_t Sdmmc_InitSdSCR(Sdmmc_Card_t* card);
ft_error_t Sdmmc_InitSwitchHs(Sdmmc_Card_t *card);
ft_error_t Sdmmc_InitSdWaitDataReady(Sdmmc_Card_t* card);
ft_error_t Sdmmc_InitMMCReadExtCSD(Sdmmc_Card_t* card);
ft_error_t Sdmmc_InitMMCReadCID(Sdmmc_Card_t* card);
ft_error_t Sdmmc_InitHostBusWidth(Sdmmc_Card_t* card);
ft_error_t Sdmmc_InitSdBusWidth(Sdmmc_Card_t* card);
//ft_error_t sdmmc_init_io_bus_width(Sdmmc_Card_t* card);
ft_error_t Sdmmc_InitMMCBusWidth(Sdmmc_Card_t* card);
ft_error_t Sdmmc_InitCardHsMode(Sdmmc_Card_t* card);
ft_error_t Sdmmc_InitHostFreq(Sdmmc_Card_t* card);
ft_error_t Sdmmc_InitMMCCheckCSD(Sdmmc_Card_t* card);

/* Various helper functions */
static inline bool_t Sdmmc_IsHostSpi(const Sdmmc_Card_t* card)
{
    return (card->host.flags & SDMMC_HOST_FLAG_SPI) != 0;
}

static inline u32 Sdmmc_GetHostOCR(float voltage)
{
    // TODO: report exact voltage to the card
    // For now tell that the host has 2.8-3.6V voltage range
    (void) voltage;
    return SD_OCR_VOL_MASK;
}

void Sdmmc_FilpByteOrder(u32* response, size_t size);

ft_error_t Sdmmc_FixHostFlags(Sdmmc_Card_t* card);

/* define debug log function */
//#define FT_SDMMC_DEBUG_ENABLED
#define FT_SDMMC_DEBUG_TAG "FT_SDMMC"
#define FT_SDMMC_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FT_SDMMC_DEBUG_TAG, format, ##__VA_ARGS__)
#ifdef FT_SDMMC_DEBUG_ENABLED
#define FT_SDMMC_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FT_SDMMC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FT_SDMMC_DEBUG_D(format, ...) FT_DEBUG_PRINT_D(FT_SDMMC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FT_SDMMC_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FT_SDMMC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FT_SDMMC_DEBUG_V(format, ...) FT_DEBUG_PRINT_V(FT_SDMMC_DEBUG_TAG, format, ##__VA_ARGS__)
#else
#define FT_SDMMC_DEBUG_I(format, ...) 
#define FT_SDMMC_DEBUG_D(format, ...) 
#define FT_SDMMC_DEBUG_W(format, ...) 
#define FT_SDMMC_DEBUG_V(format, ...) 
#endif

/* define SD MMC error code */
typedef enum
{
    ERR_SUB_MODE_SDMMC_GENERAL = 0
}FT_SDMMC_ERR_SUB_MODE;


#define ERR_SDMMC_NO_MEM              FT_CODE_ERR(ERR_MODE_SD_MMC, ERR_SUB_MODE_SDMMC_GENERAL, 0x1)   /*!< Out of memory */
#define ERR_SDMMC_INVALID_ARG         FT_CODE_ERR(ERR_MODE_SD_MMC, ERR_SUB_MODE_SDMMC_GENERAL, 0x2)    
#define ERR_SDMMC_INVALID_STATE       FT_CODE_ERR(ERR_MODE_SD_MMC, ERR_SUB_MODE_SDMMC_GENERAL, 0x3)    /*!< Invalid state */
#define ERR_SDMMC_INVALID_SIZE        FT_CODE_ERR(ERR_MODE_SD_MMC, ERR_SUB_MODE_SDMMC_GENERAL, 0x4)    /*!< Invalid size */
#define ERR_SDMMC_NOT_FOUND           FT_CODE_ERR(ERR_MODE_SD_MMC, ERR_SUB_MODE_SDMMC_GENERAL, 0x5)    /*!< Requested resource not found */
#define ERR_SDMMC_NOT_SUPPORTED       FT_CODE_ERR(ERR_MODE_SD_MMC, ERR_SUB_MODE_SDMMC_GENERAL, 0x6)    /*!< Operation or feature not supported */
#define ERR_SDMMC_TIMEOUT             FT_CODE_ERR(ERR_MODE_SD_MMC, ERR_SUB_MODE_SDMMC_GENERAL, 0x7)    /*!< Operation timed out */
#define ERR_SDMMC_INVALID_RESPONSE    FT_CODE_ERR(ERR_MODE_SD_MMC, ERR_SUB_MODE_SDMMC_GENERAL, 0x8)    /*!< Received response was invalid */
#define ERR_SDMMC_INVALID_CRC         FT_CODE_ERR(ERR_MODE_SD_MMC, ERR_SUB_MODE_SDMMC_GENERAL, 0x9)    /*!< CRC or checksum was invalid */
#define ERR_SDMMC_INVALID_VERSION     FT_CODE_ERR(ERR_MODE_SD_MMC, ERR_SUB_MODE_SDMMC_GENERAL, 0xa)    /*!< Version was invalid */
#define ERR_SDMMC_INVALID_MAC         FT_CODE_ERR(ERR_MODE_SD_MMC, ERR_SUB_MODE_SDMMC_GENERAL, 0xb)    /*!< MAC address was invalid */
#define ERR_SDMMC_CARD_NOFOUND        FT_CODE_ERR(ERR_MODE_SD_MMC, ERR_SUB_MODE_SDMMC_GENERAL, 0x10)    /*!< SDMMC card not found */

#define ERR_SDMMC_WIFI_BASE           FT_CODE_ERR(ERR_MODE_SD_MMC, ERR_SUB_MODE_SDMMC_GENERAL, 0xc)  /*!< Starting number of WiFi error codes */
#define ERR_SDMMC_MESH_BASE           FT_CODE_ERR(ERR_MODE_SD_MMC, ERR_SUB_MODE_SDMMC_GENERAL, 0xd)  /*!< Starting number of MESH error codes */
#define ERR_SDMMC_FLASH_BASE          FT_CODE_ERR(ERR_MODE_SD_MMC, ERR_SUB_MODE_SDMMC_GENERAL, 0xe)  /*!< Starting number of flash error codes */
#define ERR_SDMMC_NOTYET_INIT         FT_CODE_ERR(ERR_MODE_SD_MMC, ERR_SUB_MODE_SDMMC_GENERAL, 0xf)  /*!< Starting number of flash error codes */

#define ERR_SDMMC_OK                  ERR_SUCCESS


#ifdef __cplusplus
}
#endif

#endif