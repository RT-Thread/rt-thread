/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-08 16:57:05
 * @LastEditTime: 2021-04-16 13:38:21
 * @Description:  This files is for free-rtos sdmmc porting
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include <assert.h>
#include <string.h>
#include "ft_assert.h"
#include "ft_parameters.h"
#include "ft_sdctrl.h"
#include "ft_sdmmc.h"
#include "ft_sdmmc_common.h"
#include "ft_sdmmc_cmd.h"
#include "diskio_sdmmc.h"

#define SDCTR_BUFF_SIZE (512 * 2)
#define SDCTR_ALIGN_MASK 0x1f
static u8 g_DMABuf[SDCTR_BUFF_SIZE] __attribute__((aligned(SDCTR_ALIGN_MASK + 1)));

typedef struct
{
    FtsdCtrl_t *pSdmmcReg;
    Sdmmc_Host_t *pSdmmcHost;
    Sdmmc_Card_t *pSdmmcCard;
    bool_t isReady;
} FSdmmc_Ctrl;

FSdmmc_Ctrl *FSdmmc_GetSdmmcCtrl();
ft_error_t FSdmmc_InitHost();
ft_error_t FSdmmc_SetBusWidth(int slot, size_t width);
size_t FSdmmc_GetSlotWidth(int slot);
ft_error_t FSdmmc_SetBusDdrMode(int slot, bool_t ddr_enabled);
ft_error_t FSdmmc_SetCardClk(int slot, u32 freq_khz);
ft_error_t FSdmmc_DoTransaction(int slot, Sdmmc_Cmd_t *cmdinfo);
ft_error_t FSdmmc_DeInit(void);
ft_error_t FSdmmc_IoIntEnable(int slot);
ft_error_t FSdmmc_IoIntWait(int slot, u32 timeout_ticks);

#define SDMMC_SLOT_NO_CD GPIO_NUM_NC ///< indicates that card detect line is not used
#define SDMMC_SLOT_NO_WP GPIO_NUM_NC ///< indicates that write protect line is not used
#define SDMMC_SLOT_WIDTH_DEFAULT 0   ///< use the default width for the slot (8 for slot 0, 4 for slot 1)

static FSdmmc_Ctrl g_SdmmcCtrl = {
    .pSdmmcReg = NULL,
    .pSdmmcHost = NULL,
    .pSdmmcCard = NULL,
    .isReady = FALSE};

static FtsdCtrl_t *FSdmmc_GetHWCtrl()
{
    if (NULL == g_SdmmcCtrl.pSdmmcReg)
    {
        g_SdmmcCtrl.pSdmmcReg = Sdmmc_HeapMalloc(sizeof(FtsdCtrl_t));
        Ft_assertNoneReturn(g_SdmmcCtrl.pSdmmcReg);
    }

    return g_SdmmcCtrl.pSdmmcReg;
}

static Sdmmc_Host_t *FSdmmc_GetHostCtrl()
{
    if (NULL == g_SdmmcCtrl.pSdmmcHost)
    {
        g_SdmmcCtrl.pSdmmcHost = Sdmmc_HeapMalloc(sizeof(Sdmmc_Host_t));
        Ft_assertNoneReturn(g_SdmmcCtrl.pSdmmcHost);

        g_SdmmcCtrl.pSdmmcHost->flags = SDMMC_HOST_FLAG_1BIT;
        g_SdmmcCtrl.pSdmmcHost->flags &= ~SDMMC_HOST_FLAG_DDR;
        g_SdmmcCtrl.pSdmmcHost->slot = FATFS_HOST_SLOT_0;
        g_SdmmcCtrl.pSdmmcHost->max_freq_khz = SDMMC_FREQ_PROBING;
        g_SdmmcCtrl.pSdmmcHost->io_voltage = 3.3f;
        g_SdmmcCtrl.pSdmmcHost->init = &FSdmmc_InitHost;
        g_SdmmcCtrl.pSdmmcHost->set_bus_width = &FSdmmc_SetBusWidth;
        g_SdmmcCtrl.pSdmmcHost->get_bus_width = &FSdmmc_GetSlotWidth;
        g_SdmmcCtrl.pSdmmcHost->set_bus_ddr_mode = &FSdmmc_SetBusDdrMode;
        g_SdmmcCtrl.pSdmmcHost->set_card_clk = &FSdmmc_SetCardClk;
        g_SdmmcCtrl.pSdmmcHost->do_transaction = &FSdmmc_DoTransaction;
        g_SdmmcCtrl.pSdmmcHost->deinit = &FSdmmc_DeInit;
        g_SdmmcCtrl.pSdmmcHost->io_int_enable = FSdmmc_IoIntEnable;
        g_SdmmcCtrl.pSdmmcHost->io_int_wait = FSdmmc_IoIntWait;
        g_SdmmcCtrl.pSdmmcHost->command_timeout_ms = 0;
    }

    return g_SdmmcCtrl.pSdmmcHost;
}

static Sdmmc_Card_t *FSdmmc_GetCardCtrl()
{
    if (NULL == g_SdmmcCtrl.pSdmmcCard)
    {
        g_SdmmcCtrl.pSdmmcCard = Sdmmc_HeapMalloc(sizeof(Sdmmc_Card_t));
        Ft_assertNoneReturn(g_SdmmcCtrl.pSdmmcCard);
    }

    return g_SdmmcCtrl.pSdmmcCard;
}

bool_t FSdmmc_IsSdmmcReady()
{
    return g_SdmmcCtrl.isReady;
}

static void FSdmmc_SetSdmmcReady(bool_t status)
{
    g_SdmmcCtrl.isReady = status;
}

/******************SD MMC for FreeRTOS*************************/
ft_error_t FSdmmc_InitHost()
{
    FtsdCtrl_t *pRegCtrl = FSdmmc_GetHWCtrl();
    ft_error_t ret = ERR_SDMMC_OK;

    pRegCtrl->config = *(FSdCtrl_Config_t *)FSdCtrl_LookupConfig(0);
    FSdCtrl_Reset(pRegCtrl, (pFtsdCtrl_delayTimer_t)Sdmmc_Delay);
    FATFS_ERROR_HANDLE_RET(ret, FsdCtrl_Init(pRegCtrl), "init host");

    FSdCtrl_ClkFreqSetup(pRegCtrl, SDMMC_FREQ_PROBING);

    return ret;
}

ft_error_t FSdmmc_InitCard()
{
    return Sdmmc_CardInit(FSdmmc_GetHostCtrl(), FSdmmc_GetCardCtrl());
}

bool_t FSdmmc_CardExist()
{
    return FSdCtrl_CardDetect(FSdmmc_GetHWCtrl());
}

ft_error_t FSdmmc_SetBusWidth(int slot, size_t width)
{
    ft_error_t ret = ERR_SDMMC_OK;

    return ret;
}

size_t FSdmmc_GetSlotWidth(int slot)
{
    return 1;
}

ft_error_t FSdmmc_SetBusDdrMode(int slot, bool_t ddr_enabled)
{
    ft_error_t ret = ERR_SDMMC_OK;

    return ret;
}

ft_error_t FSdmmc_SetCardClk(int slot, u32 freq_khz)
{
    ft_error_t ret = ERR_SDMMC_OK;
    FSdCtrl_ClkFreqSetup(FSdmmc_GetHWCtrl(), SDMMC_FREQ_DEFAULT);
    return ret;
}

static u32 FSdmmc_resp2CmdType(u32 cmdFlag)
{
    u32 cmdType = FTSDCTRL_CMD_RES_SHORT;

    switch (cmdFlag)
    {
    case SCT_RESP_NONE:
        cmdType = FTSDCTRL_CMD_RES_NONE;
        break;
    case SCT_RESP_LONG:
        cmdType = FTSDCTRL_CMD_RES_LONG;
        break;
    case SCT_RESP_SHORT:
        cmdType = FTSDCTRL_CMD_RES_SHORT;
        break;
    default:
        Ft_assertNoneReturn(0);
        break;
    }

    return cmdType;
}

static ft_error_t FSdmmc_transferByDMA(FtsdCtrl_t *pRegCtrl, Sdmmc_Cmd_t *cmdInfo)
{
    u32 cmdType;
    u32 *pBuf;
    u32 ret = ERR_SDMMC_OK;

    Ft_assertNoneReturn((NULL != pRegCtrl) && (NULL != cmdInfo));

    /* get respones type from command info */
    Sdmmc_TraceHeapAlloc("BEF-CMD-TYPE");
    cmdType = FSdmmc_resp2CmdType(cmdInfo->cmd_resp_type);
    pBuf = cmdInfo->data;

    if (cmdInfo->flags & SCF_CMD_READ)
    {
        //FT_FATFS_DEBUG_I("read cmd");

        /* read mode */
        if ((cmdInfo->flags & SCF_CMD_ADTC) && (512 > cmdInfo->blklen))
        {
            Sdmmc_TraceHeapAlloc("BEF-DO-ACMD");
            FSdCtrl_DoACmd(pRegCtrl, cmdInfo->opcode, cmdType, cmdInfo->arg);
            Sdmmc_Delay(10);
        }

        Sdmmc_TraceHeapAlloc("BEF-READ-DATA");
        FSdCtrl_ReadData(pRegCtrl, (UINTPTR)cmdInfo->data, cmdInfo->arg, 1);
        Sdmmc_TraceHeapAlloc("AFT-READ-DATA");
        //Ft_printf("0x%p %x\r\n", &cmdInfo->error, cmdInfo->error);
        cmdInfo->error = FSdCtrl_WaitCmdEnd(pRegCtrl, (pFtsdCtrl_delayTimer_t)Sdmmc_Delay, cmdType, (u32 *)cmdInfo->response);
        Sdmmc_TraceHeapAlloc("AFT-READ-WAIT");

        ret = FSdCtrl_WaitReadDataEnd(pRegCtrl, (pFtsdCtrl_delayTimer_t)Sdmmc_Delay, 1);
        Sdmmc_TraceHeapAlloc("AFT-READ-WAIT-END");
    }
    else
    {
        /* write mode */
        //FT_FATFS_DEBUG_I("write cmd");

        FSdCtrl_WriteData(pRegCtrl, (UINTPTR)cmdInfo->data, cmdInfo->arg, 1);
        cmdInfo->error = FSdCtrl_WaitCmdEnd(pRegCtrl, (pFtsdCtrl_delayTimer_t)Sdmmc_Delay, cmdType, (u32 *)cmdInfo->response);

        ret = FSdCtrl_WaitWriteDataEnd(pRegCtrl, (pFtsdCtrl_delayTimer_t)Sdmmc_Delay, 1);
    }

    return ret;
}

static ft_error_t FSdmmc_doCommand(FtsdCtrl_t *pRegCtrl, Sdmmc_Cmd_t *cmdInfo)
{
    u32 cmdType;
    u32 *pBuf;
    u32 ret = ERR_SDMMC_OK;

    Ft_assertNoneReturn((NULL != pRegCtrl) && (NULL != cmdInfo));

    cmdType = FSdmmc_resp2CmdType(cmdInfo->cmd_resp_type);
    Sdmmc_Delay(10);

    //FT_FATFS_DEBUG_I("do cmd: type: %d, resp: 0x%x", cmdType, cmdInfo->response);
    FSdCtrl_DoCmd(pRegCtrl, cmdInfo->opcode, cmdType, cmdInfo->arg);
    cmdInfo->error = FSdCtrl_WaitCmdEnd(pRegCtrl, (pFtsdCtrl_delayTimer_t)Sdmmc_Delay, cmdType, (u32 *)cmdInfo->response);
    ret = cmdInfo->error;

    return ret;
}

static ft_error_t FSdmmc_sendCommand(FtsdCtrl_t *pRegCtrl, Sdmmc_Cmd_t *cmdInfo)
{
    ft_error_t ret = ERR_SDMMC_OK;

    Ft_assertNoneReturn((NULL != pRegCtrl) && (NULL != cmdInfo));

    /* read one block */
    if (NULL != cmdInfo->data)
    {
        //FT_FATFS_DEBUG_I("CMD %d ,data transfer", cmdInfo->opcode);
        Sdmmc_TraceHeapAlloc("BEF-DMA");
        ret = FSdmmc_transferByDMA(pRegCtrl, cmdInfo);
    }
    else
    {
        //FT_FATFS_DEBUG_I("CMD %d ,cmd transfer", cmdInfo->opcode);
        Sdmmc_TraceHeapAlloc("BEF-DO-CMD");
        ret = FSdmmc_doCommand(pRegCtrl, cmdInfo);
    }

    Sdmmc_TraceHeapAlloc("AFT-DO-CMD");
    return ret;
}

static bool_t FSdmmc_cmdNeedsAutoStop(const Sdmmc_Cmd_t *cmd)
{
    /* SDMMC host needs an "auto stop" flag for the following commands: */
    return cmd->datalen > 0 &&
           (cmd->opcode == MMC_WRITE_BLOCK_MULTIPLE ||
            cmd->opcode == MMC_READ_BLOCK_MULTIPLE ||
            cmd->opcode == MMC_WRITE_DAT_UNTIL_STOP ||
            cmd->opcode == MMC_READ_DAT_UNTIL_STOP);
}

static void FSdmmc_dumpCmdInfo(Sdmmc_Cmd_t *cmdInfo)
{
    Ft_assertNoneReturn(NULL != cmdInfo);
    return;
}

static void FSdmmc_dumpCardInfo(Sdmmc_Card_t *pCard)
{
    Ft_assertNoneReturn(NULL != pCard);

    // FT_FATFS_DEBUG_I("HOST:0x%x 0x%x, RCA:0x%x, Freq: %d, MEM: %d, SPI: %d, SDIO: %d, MMC: %d, BUS Width: %d. DDR: %d",
    //                 pCard->host, FSdmmc_GetSdmmcCtrl(), pCard->rca, pCard->max_freq_khz,
    //                 pCard->is_mem, Sdmmc_IsHostSpi(pCard), pCard->is_sdio, pCard->is_mmc,
    //                 pCard->log_bus_width, pCard->is_ddr);

    return;
}

ft_error_t FSdmmc_DoTransaction(int slot, Sdmmc_Cmd_t *cmdInfo)
{
    ft_error_t ret = ERR_SDMMC_OK;
    FtsdCtrl_t *pRegCtrl = FSdmmc_GetHWCtrl();
    size_t inputBufSize;
    u8 *pDataBuf = cmdInfo->data;

    Sdmmc_TraceHeapAlloc("BEF-DUMP");
    FSdmmc_dumpCmdInfo(cmdInfo);

    /* use DMA buf to transfer data */
    if ((NULL != cmdInfo->data))
    {
        Ft_assertNoneReturn(cmdInfo->datalen <= SDCTR_BUFF_SIZE);
        memset(g_DMABuf, 0, sizeof(g_DMABuf));
        memcpy(g_DMABuf, cmdInfo->data, cmdInfo->datalen);
        cmdInfo->data = g_DMABuf; /* use dma buffer to read and write data */
    }

    ret = FSdmmc_sendCommand(pRegCtrl, cmdInfo);

    if ((NULL != cmdInfo->data) && (ERR_SDMMC_OK == ret))
    {
        /* copy back data from DMA buf to the original data buf */
        //dump_hex(g_DMABuf, 512, "DMA buf");
        memcpy(pDataBuf, g_DMABuf, cmdInfo->datalen);
    }

    if (FSdmmc_cmdNeedsAutoStop(cmdInfo))
    {
        Ft_assertNoneReturn(0);
    }

    return ret;
}

ft_error_t FSdmmc_DeInit(void)
{
    ft_error_t ret = ERR_SDMMC_OK;

    FSdmmc_SetSdmmcReady(FALSE);

    return ret;
}

ft_error_t FSdmmc_IoIntEnable(int slot)
{
    ft_error_t ret = ERR_SDMMC_OK;

    return ret;
}

ft_error_t FSdmmc_IoIntWait(int slot, u32 timeout_ticks)
{
    ft_error_t ret = ERR_SDMMC_OK;

    return ret;
}

ft_error_t FSdmmc_InitSd()
{
    ft_error_t ret = ERR_SDMMC_OK;

    if (FSdmmc_IsSdmmcReady())
    {
        FT_SDMMC_DEBUG_E("try to re-init");
        return ret;
    }

    FATFS_ERROR_HANDLE_RET(ret, FSdmmc_InitHost(), "init host");
    FATFS_ERROR_HANDLE_RET(ret, FSdmmc_InitCard(), "init card");

    if (FSdmmc_CardExist())
    {
        FSdmmc_SetSdmmcReady(TRUE);
    }
    else
    {
        ret = ERR_SDMMC_CARD_NOFOUND;
    }

    return ret;
}

ft_error_t FSdmmc_ReadSector(u32 startSector, u32 numSector, void *pBuf)
{
    ft_error_t ret = ERR_SDMMC_OK;
    //FT_FATFS_DEBUG_I("before get ctrl");
    Sdmmc_Card_t *pCard = FSdmmc_GetCardCtrl();

    //FT_FATFS_DEBUG_I("before check ready");
    if (!FSdmmc_IsSdmmcReady())
    {
        return ERR_SDMMC_NOTYET_INIT;
    }

    FATFS_ERROR_HANDLE_RET(ret, Sdmmc_ReadSectors(pCard, pBuf, startSector, numSector), "read sector");
    return ret;
}

ft_error_t FSdmmc_WriteSector(u32 startSector, u32 numSector, void *pBuf)
{
    ft_error_t ret = ERR_SDMMC_OK;
    //FT_FATFS_DEBUG_I("before get ctrl");
    Sdmmc_Card_t *pCard = FSdmmc_GetCardCtrl();

    //FT_FATFS_DEBUG_I("before check ready");
    if (!FSdmmc_IsSdmmcReady())
    {
        return ERR_SDMMC_NOTYET_INIT;
    }

    FATFS_ERROR_HANDLE_RET(ret, Sdmmc_WriteSectors(pCard, pBuf, startSector, numSector), "write sector");
    //FT_FATFS_DEBUG_I("sector write finished! ret %x", ret);
    return ret;
}