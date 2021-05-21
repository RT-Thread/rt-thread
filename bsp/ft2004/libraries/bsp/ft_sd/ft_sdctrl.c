/*
 * @ : Copyright (c) 2020 Phytium Information Technology(TianJin), Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-03-31 14:59:20
 * @LastEditTime: 2021-04-15 13:57:52
 * @Description:  This files is for implemenation of sd ctrl
 * 
 * @Modify History: * * Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_parameters.h"
#include "ft_assert.h"
#include "ft_io.h"
#include "ft_sdctrl.h"
#include "ft_sdctrl_hw.h"
#include "ft_debug.h"
#include "ft_printf.h"
#include "ft_trace.h"
#include "ft_cache.h"
#define FT_SD_CTRL_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FT_SD_CTRL_DEBUG_TAG, format, ##__VA_ARGS__)
#define FT_SD_CTRL_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FT_SD_CTRL_DEBUG_TAG, format, ##__VA_ARGS__)
#define FT_SD_CTRL_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FT_SD_CTRL_DEBUG_TAG, format, ##__VA_ARGS__)

/**
 *  @Description: setup sd ctrl clk freq
 *  @Date: 2021-04-01 09:28:28
 *  @Param: 
 *  @return {*}
 *  @param {FT_INOUT FtsdCtrl_t} *pFtsdCtrl
 *  @param {FT_IN u32} sdClk, clk from SD
 */
void FSdCtrl_ClkFreqSetup(FT_INOUT FtsdCtrl_t *pFtsdCtrl, FT_IN u32 sdClk)
{
    FSdCtrl_Config_t *pConfig;
    u32 clkDiv;
    u32 inputClk;
    u32 tmpSdFreq;
    u32 workSpeed;

    Ft_assertVoid(FT_NULL != pFtsdCtrl);
    pConfig = &pFtsdCtrl->config;
    inputClk = pConfig->inputClockHz;

    /* sd work speed is limit to 25MHz */
    workSpeed = (sdClk < SD_CLK_FREQ_25MHZ) ? sdClk : SD_CLK_FREQ_25MHZ;

    /* if sd clk freq is valid and is two times greater than io input clk */
    if ((SD_CLK_FREQ_400KHZ < workSpeed) && (inputClk > (2 * workSpeed)))
    {
        clkDiv = (u32)(inputClk / (2 * workSpeed)) - 1;

        /* calculte sd freq one more time base on divsor */
        tmpSdFreq = (u32)inputClk / (2 * (clkDiv + 1));

        /* if calculated sd freq is greater than the real val  */
        if (tmpSdFreq > workSpeed)
        {
            clkDiv += 1;
        }
    }
    else
    {
        clkDiv = SD_FRRQ_DIV_DEFAULT;
    }

    Ft_out32(pConfig->baseAddress + CLOCK_DIV_REG_OFFSET, clkDiv);

    return;
}

/**
 * @name: FsdCtrl_Init
 * @msg: init sd ctrl
 * @in param: 
 * @inout param: 
 * @out param: 
 * @return {*}
 * @param {FT_INOUT FtsdCtrl_t} *pFtsdCtrl
 */
ft_error_t FsdCtrl_Init(FT_INOUT FtsdCtrl_t *pFtsdCtrl)
{
    FSdCtrl_Config_t *pConfig;
    Ft_assertNonvoid(FT_NULL != pFtsdCtrl);
    pConfig = &pFtsdCtrl->config;

    /* Disable card detection */
    Ft_out32(pConfig->baseAddress + SD_SEN_REG_OFFSET, 0);

    /* Disable all interrupts */
    Ft_out32(pConfig->baseAddress + NORMAL_INT_EN_REG_OFFSET, 0);
    Ft_out32(pConfig->baseAddress + ERROR_INT_EN_REG_OFFSET, 0);
    Ft_out32(pConfig->baseAddress + BD_ISR_EN_REG_OFFSET, 0);
    // Ft_out32(pConfig->baseAddress + NORMAL_INT_EN_REG_OFFSET, NORMAL_INT_EN_ECCRCE);

    /* Clear status register */
    Ft_out32(pConfig->baseAddress + NORMAL_INT_STATUS_REG, 0);
    Ft_out32(pConfig->baseAddress + ERROR_INT_STATUS_REG, 0);
    Ft_out32(pConfig->baseAddress + BD_ISR_REG, 0);

    /* Set default ctrl register  */
    Ft_out32(pConfig->baseAddress + CONTROLL_SETTING_REG_OFFSET, 0x0f00);

    /* Set default drive and sampling register */
    Ft_out32(pConfig->baseAddress + SD_DRV_REG_OFFSET, 0);
    Ft_out32(pConfig->baseAddress + SD_SAMP_REG_OFFSET, 0);

    /* Configure to default cmd data timeout */
    Ft_out32(pConfig->baseAddress + TIMEOUT_CMD_REG_OFFSET, 0xFFFFFFFF);
    //FSdCtrl_ClkFreqSetup(pFtsdCtrl, 1);

    Ft_out32(pConfig->baseAddress + CLOCK_DIV_REG_OFFSET, SD_FRRQ_DIV_DEFAULT);
    Ft_out32(pConfig->baseAddress + SD_SAMP_REG_OFFSET, SD_SAMP_DEFAULT);

    pFtsdCtrl->isReady = FT_COMPONENT_IS_READLY;

    return FTSDC_SUCCESS;
}

/**
 * @name: FSdCtrl_CardDetect
 * @msg: 
 * @in param {FtsdCtrl_t} *pFtsdCtrl
 * @inout param: 
 * @out param: 
 * @return {*}
 */
bool_t FSdCtrl_CardDetect(FT_INOUT FtsdCtrl_t *pFtsdCtrl)
{
    FSdCtrl_Config_t *pConfig;
    u32 status;

    Ft_assertBool(FT_NULL != pFtsdCtrl);
    pConfig = &pFtsdCtrl->config;
    status = Ft_in32(pConfig->baseAddress + STATUS_REG);

    /* check card-detection signal */
    if (((status)&STATUS_REG_CDSL) == STATUS_REG_CDSL)
    {
        pConfig->cardDetect = 0;
    }
    else
    {
        pConfig->cardDetect = 1;
    }

    return pConfig->cardDetect;
}

/**
 * @name: 
 * @msg: 
 * @in param: 
 * @inout param: 
 * @out param: 
 * @return {*}
 * @param {FT_INOUT FtsdCtrl_t} *pFtsdCtrl
 */
void FSdCtrl_ResetDma(FT_INOUT FtsdCtrl_t *pFtsdCtrl)
{
    FSdCtrl_Config_t *pConfig;
    Ft_assertVoid(FT_NULL != pFtsdCtrl);
    pConfig = &pFtsdCtrl->config;

    Ft_setBit32((UINTPTR)(pConfig->baseAddress + SOFTWARE_RESET_REG_OFFSET), SOFTWARE_RESET_BDRST);
    Ft_clearBit32((UINTPTR)(pConfig->baseAddress + SOFTWARE_RESET_REG_OFFSET), SOFTWARE_RESET_BDRST);
}

/**
 * @name: 
 * @msg: 
 * @in param: 
 * @inout param: 
 * @out param: 
 * @return {*}
 * @param {FT_INFtsdCtrl_t} *pFtsdCtrl
 * @param {FT_INu32} cmdIndex
 * @param {FT_INu32} rspType
 */
u32 FSdCtrl_PrepareCmdRaw(FT_IN u32 cmdIndex, FT_IN u32 rspType)
{
    u32 rawCmd = 0;

    rawCmd |= CMD_SETTING_CMDI(cmdIndex);

    switch (rspType)
    {
    case FTSDCTRL_CMD_RES_NONE:
        rawCmd |= CMD_SETTING_RTS(0);
        break;
    case FTSDCTRL_CMD_RES_LONG:
        rawCmd |= CMD_SETTING_RTS(1);
        break;
    case FTSDCTRL_CMD_RES_SHORT:
        rawCmd |= CMD_SETTING_RTS(2);
        break;
    default:
        rawCmd |= CMD_SETTING_RTS(0);
        break;
    }

    return rawCmd;
}

/**
 *  Description: sd ctrl write data
 *  Date: 2021-03-31 11:12:09
 *  Param: 
 *  return {*}
 *  param {FT_INOUT FtsdCtrl_t} *pFtsdCtrl
 *  param {FT_IN UINTPTR} dataAddr, src addr
 *  param {FT_IN UINTPTR} cardAddr, dst addr
 *  param {FT_IN u32} blkNum,  num of blks to write
 */
void FSdCtrl_WriteData(FT_INOUT FtsdCtrl_t *pFtsdCtrl, FT_IN UINTPTR dataAddr,
                       FT_IN UINTPTR cardAddr, FT_IN u32 blkNum)
{

    FSdCtrl_Config_t *pConfig;
    Ft_assertVoid(FT_NULL != pFtsdCtrl);
    pConfig = &pFtsdCtrl->config;

    /* write 1 to clear data status register and command status register */
    Ft_out32(pConfig->baseAddress + BD_ISR_REG, BD_ISR_REG_TRS);
    Ft_out32(pConfig->baseAddress + NORMAL_INT_STATUS_REG, NORMAL_INT_STATUS_CC);

    /* set DMA BD  */
    Ft_setBit32((UINTPTR)(pConfig->baseAddress + SOFTWARE_RESET_REG_OFFSET), SOFTWARE_RESET_BDRST);
    Ft_clearBit32((UINTPTR)(pConfig->baseAddress + SOFTWARE_RESET_REG_OFFSET), SOFTWARE_RESET_BDRST);

    /* set transfer lenth */
    Ft_out32(pConfig->baseAddress + BLK_CNT_REG, blkNum);

    /* set DMA discriptor data low address,data high address,card low address,card high address*/
    Ft_out32(pConfig->baseAddress + DAT_IN_M_TX_BD, dataAddr);
    Ft_out32(pConfig->baseAddress + DAT_IN_M_TX_BD, 0);
    Ft_out32(pConfig->baseAddress + DAT_IN_M_TX_BD, cardAddr);
    Ft_out32(pConfig->baseAddress + DAT_IN_M_TX_BD, 0);
}

/**
 * @name: 
 * @msg: 
 * @in param: 
 * @inout param: 
 * @out param: 
 * @return {*}
 */
void FSdCtrl_ReadData(FT_INOUT FtsdCtrl_t *pFtsdCtrl,
                      FT_IN UINTPTR dataAddr,
                      FT_IN UINTPTR cardAddr,
                      FT_IN u32 blkNum)
{
    FSdCtrl_Config_t *pConfig;
    Ft_assertVoid(FT_NULL != pFtsdCtrl);
    pConfig = &pFtsdCtrl->config;

    /* clear data status register and command status register */
    Ft_out32(pConfig->baseAddress + BD_ISR_REG, BD_ISR_EN_ETRS);
    Ft_out32(pConfig->baseAddress + NORMAL_INT_STATUS_REG, NORMAL_INT_EN_ECC);

    /* set DMA BD  */
    Ft_setBit32((UINTPTR)(pConfig->baseAddress + SOFTWARE_RESET_REG_OFFSET), SOFTWARE_RESET_BDRST);
    Ft_clearBit32((UINTPTR)(pConfig->baseAddress + SOFTWARE_RESET_REG_OFFSET), SOFTWARE_RESET_BDRST);

    /* set transfer lenth */
    Ft_out32(pConfig->baseAddress + BLK_CNT_REG, blkNum);

    /* set DMA discriptor data low address,data high address,card low address,card high address*/

    Ft_out32(pConfig->baseAddress + DAT_IN_M_RX_BD, dataAddr);
    Ft_out32(pConfig->baseAddress + DAT_IN_M_RX_BD, 0);
    Ft_out32(pConfig->baseAddress + DAT_IN_M_RX_BD, cardAddr);
    Ft_out32(pConfig->baseAddress + DAT_IN_M_RX_BD, 0);
}

/**
 *  Description: send ctrl cmd
 *  Date: 2021-03-31 10:51:33
 *  Param: 
 *  return {*}
 *  param {FT_INOUT FtsdCtrl_t} *pFtsdCtrl
 *  param {FT_IN pFtsdCtrl_delayTimer_t} pDelayTimer_fun
 *  param {FT_IN u32} cmd
 *  param {FT_IN u32} respType
 *  param {FT_IN u32} arg
 */
static ft_error_t FsdCtrl_privateSendCmd(FT_INOUT FtsdCtrl_t *pFtsdCtrl, FT_IN pFtsdCtrl_delayTimer_t pDelayTimer_fun, FT_IN u32 cmd, FT_IN u32 respType, FT_IN u32 arg)
{
    u32 temp;
    u32 sd_cmd;
    u32 sd_arg;
    FSdCtrl_Config_t *pConfig;
    Ft_assertNonvoid(FT_NULL != pFtsdCtrl);
    pConfig = &pFtsdCtrl->config;

    /* enable cmd finished irq */
    Ft_out32(pConfig->baseAddress + NORMAL_INT_STATUS_REG, NORMAL_INT_EN_ECC);
    Ft_out32(pConfig->baseAddress + NORMAL_INT_STATUS_REG, 0);

    Ft_out32(pConfig->baseAddress + ERROR_INT_STATUS_REG, BD_ISR_EN_ETRS);
    Ft_out32(pConfig->baseAddress + ERROR_INT_STATUS_REG, 0);

    /* prepare cmd msg, along with arg */
    sd_cmd = FSdCtrl_PrepareCmdRaw(cmd, respType);
    sd_arg = arg;

    /* send cmd and arg */
    Ft_out32(pConfig->baseAddress + CMD_SETTING_REG_OFFSET, sd_cmd);
    Ft_out32(pConfig->baseAddress + ARGUMENT_REG_OFFSET, sd_arg);

    if (pConfig->workMode & FTSDCTRL_CMD_IRQ_MASK)
    {
        if (pFtsdCtrl->cmdWaitCallback)
        {
            /* if irq is enabled and call back registered, enter call back procedure */
            return pFtsdCtrl->cmdWaitCallback(pFtsdCtrl);
        }
        else
        {
            return FTSDC_INVALID_PARAM;
        }
    }
    else
    {
        temp = Ft_in32(pConfig->baseAddress + NORMAL_INT_STATUS_REG);
        /* polling wait for cmd-finished response */
        while (NORMAL_INT_STATUS_CC != (temp & NORMAL_INT_STATUS_CC))
        {
            temp = Ft_in32(pConfig->baseAddress + NORMAL_INT_STATUS_REG);
            pDelayTimer_fun(1);
        }
    }

    return FTSDC_SUCCESS;
}

/**
 *  Description: wait data write procedure to end
 *  Date: 2021-03-31 11:28:41
 *  Param: 
 *  return {*}
 */
ft_error_t FSdCtrl_WaitWriteDataEnd(FT_INOUT FtsdCtrl_t *pFtsdCtrl,
                                    FT_IN pFtsdCtrl_delayTimer_t pDelayTimer_fun,
                                    FT_IN u32 blkNum)
{
    u32 status;
    u32 statusMask;
    ft_error_t ret;
    s32 timeout = 1000;
    FSdCtrl_Config_t *pConfig;

    Ft_assertNonvoid(FT_NULL != pFtsdCtrl);
    pConfig = &pFtsdCtrl->config;

    if (pConfig->workMode & FTSDCTRL_DATA_WRITE_IRQ_MASK)
    {
        /* enter irq mode */
        if (NULL == pFtsdCtrl->writeWaitCallback)
        {
            return FTSDC_INVALID_PARAM;
        }

        ret = pFtsdCtrl->writeWaitCallback(pFtsdCtrl);
        if (FTSDC_SUCCESS != ret)
        {
            return FTSDC_EILSEQ;
        }
    }
    else
    {
        /* wait for DMA-error or DMA-finished status */
        statusMask = BD_ISR_REG_DAIS | BD_ISR_REG_TRS;
        do
        {
            status = (Ft_in32(pConfig->baseAddress + BD_ISR_REG) & statusMask);
            pDelayTimer_fun(1);
            timeout--;
        } while ((!status) && timeout);

        if (status & BD_ISR_REG_DAIS)
        {
            if (status & (BD_ISR_REG_TRE | BD_ISR_REG_NRCRC | BD_ISR_REG_CMDE))
            {
                return FTSDC_EILSEQ;
            }
            else if (!timeout)
            {
                return FTSDC_TIMEOUT;
            }
        }
    }

    /* multi block needs MMC_STOP_TRANSMISSION to stop process*/
    if (blkNum > 1)
    {
        return FsdCtrl_privateSendCmd(pFtsdCtrl, pDelayTimer_fun, 12, CMD_SETTING_RTS(2), 0);
    }

    return FTSDC_SUCCESS;
}

/**
 *  Description: wait for read data procedure end
 *  Date: 2021-03-31 11:25:25
 *  Param: 
 *  return {*}
 */
ft_error_t FSdCtrl_WaitReadDataEnd(FT_INOUT FtsdCtrl_t *pFtsdCtrl,
                                   FT_IN pFtsdCtrl_delayTimer_t pDelayTimer_fun,
                                   FT_IN u32 blkNum)
{
    u32 status;
    u32 statusMask;
    ft_error_t ret;
    s32 timeout = 1000;
    FSdCtrl_Config_t *pConfig;

    Ft_assertNonvoid(FT_NULL != pFtsdCtrl);
    pConfig = &pFtsdCtrl->config;

    if (pConfig->workMode & FTSDCTRL_DATA_READ_IRQ_MASK)
    {
        if (pFtsdCtrl->readWaitCallback)
        {
            ret = pFtsdCtrl->readWaitCallback(pFtsdCtrl);
            if (FTSDC_SUCCESS != ret)
            {
                return FTSDC_EILSEQ;
            }
        }
        else
        {
            return FTSDC_INVALID_PARAM;
        }
    }
    else
    {
        /* wait for DMA-error or Read-finish status */
        statusMask = BD_ISR_REG_DAIS | BD_ISR_REG_RESPE;
        do
        {
            status = (Ft_in32(pConfig->baseAddress + BD_ISR_REG) & statusMask);
            pDelayTimer_fun(1);
            timeout--;
        } while ((!status) && timeout);

        if (status & BD_ISR_REG_DAIS)
        {
            /* error handle */
            if (status & (BD_ISR_REG_TRE | BD_ISR_REG_NRCRC | BD_ISR_REG_CMDE))
            {
                return FTSDC_EILSEQ;
            }
            else if (!timeout)
            {
                return FTSDC_TIMEOUT;
            }
        }
    }

    // /* multi block needs MMC_STOP_TRANSMISSION to stop process*/
    if (blkNum > 1)
    {
        return FsdCtrl_privateSendCmd(pFtsdCtrl, pDelayTimer_fun, 12, CMD_SETTING_RTS(2), 0);
    }

    return FTSDC_SUCCESS;
}

/**
 *  Description: wait for cmd response
 *  Date: 2021-03-31 11:18:57
 *  Param: 
 *  return {*}
 */
ft_error_t FSdCtrl_WaitCmdEnd(FT_OUT FtsdCtrl_t *pFtsdCtrl,
                              FT_IN pFtsdCtrl_delayTimer_t pDelayTimer_fun,
                              FT_IN u32 rspType,
                              FT_OUT u32 *cmdRsp)
{
    u32 status;
    u32 statusMask;
    s32 timeout = 1000;
    const FSdCtrl_Config_t *pConfig;
    ft_error_t result = FST_SUCCESS;

    Ft_assertNonvoid(FT_NULL != pFtsdCtrl);
    pConfig = &pFtsdCtrl->config;

    if (pConfig->workMode & FTSDCTRL_CMD_IRQ_MASK)
    {
        if (pFtsdCtrl->cmdWaitCallback)
        {
            result = pFtsdCtrl->cmdWaitCallback(pFtsdCtrl);
        }
        else
        {
            return FTSDC_INVALID_PARAM;
        }
        status = Ft_in32(pConfig->baseAddress + NORMAL_INT_STATUS_REG);
    }
    else
    {
        /* wait for cmd-error or cmd-finish respones */
        statusMask = NORMAL_INT_STATUS_EI | NORMAL_INT_STATUS_CC;

        do
        {
            status = (Ft_in32(pConfig->baseAddress + NORMAL_INT_STATUS_REG) & statusMask);
            pDelayTimer_fun(1);
            timeout--;

        } while ((!status) && timeout);
    }

    if (status & NORMAL_INT_STATUS_EI)
    {
        /* error handle */
        status = Ft_in32(pConfig->baseAddress + ERROR_INT_STATUS_REG);

        if (!timeout)
        {
            return FTSDC_TIMEOUT;
        }
        else if ((status & NORMAL_INT_EN_ECCRCE))
        {
            return FTSDC_EILSEQ;
        }
    }

    if (rspType != FTSDCTRL_CMD_RES_NONE)
    {
        /* get cmd respones */
        if (rspType == FTSDCTRL_CMD_RES_LONG)
        {
            cmdRsp[0] = Ft_in32(pConfig->baseAddress + CMD_RESP_1);
            cmdRsp[1] = Ft_in32(pConfig->baseAddress + CMD_RESP_2);
            cmdRsp[2] = Ft_in32(pConfig->baseAddress + CMD_RESP_3);
            cmdRsp[3] = Ft_in32(pConfig->baseAddress + CMD_RESP_4);
        }
        else
        {
            cmdRsp[0] = Ft_in32(pConfig->baseAddress + CMD_RESP_1);
            cmdRsp[1] = 0;
            cmdRsp[2] = 0;
            cmdRsp[3] = 0;
        }
    }

    return result;
}

/**
 * @name: 
 * @msg: 
 * @in param: 
 * @inout param: 
 * @out param: 
 * @return {*}
 */
void FSdCtrl_DoCmd(FT_INOUT FtsdCtrl_t *pFtsdCtrl,
                   FT_IN u32 cmdIndex,
                   FT_IN u32 rspType,
                   u32 arg)
{
    u32 cmd;

    FSdCtrl_Config_t *pConfig;
    Ft_assertVoid(FT_NULL != pFtsdCtrl);
    pConfig = &pFtsdCtrl->config;

    /* clear normal interrupt status */
    Ft_out32(pConfig->baseAddress + NORMAL_INT_STATUS_REG, NORMAL_INT_STATUS_EI);

    /* set command*/
    cmd = FSdCtrl_PrepareCmdRaw(cmdIndex, rspType);
    Ft_out32(pConfig->baseAddress + CMD_SETTING_REG_OFFSET, cmd);

    if (cmdIndex == 41)
    {
        arg = 0x40ff8000;
    }

    Ft_out32(pConfig->baseAddress + ARGUMENT_REG_OFFSET, arg);
}

/**
 * @name: 
 * @msg: 
 * @in param: 
 * @inout param: 
 * @out param: 
 * @return {*}
 */
void FSdCtrl_DoACmd(FT_INOUT FtsdCtrl_t *pFtsdCtrl,
                    FT_IN u32 cmdIndex,
                    FT_IN u32 rspType,
                    u32 arg)
{
    u32 cmd;

    FSdCtrl_Config_t *pConfig;
    Ft_assertVoid(FT_NULL != pFtsdCtrl);
    pConfig = &pFtsdCtrl->config;

    /* clear normal interrupt status */
    Ft_out32(pConfig->baseAddress + NORMAL_INT_STATUS_REG, NORMAL_INT_EN_ECC);
    /* set command*/
    cmd = FSdCtrl_PrepareCmdRaw(cmdIndex, rspType);
    cmd |= CMD_SETTING_TRTY(2);
    Ft_out32(pConfig->baseAddress + CMD_SETTING_REG_OFFSET, cmd);
}

/**
 * @name: 
 * @msg: 
 * @in param: 
 * @inout param: 
 * @out param: 
 * @return {*}
 * @param {FT_INOUT FtsdCtrl_t} *pFtsdCtrl
 * @param {FT_IN pFtsdCtrl_irqWaitCallback_t} callBack
 */
void FSdCtrl_WriteWaitRegister(FT_INOUT FtsdCtrl_t *pFtsdCtrl, FT_IN pFtsdCtrl_irqWaitCallback_t callBack)
{
    Ft_assertVoid(FT_NULL != pFtsdCtrl);
    pFtsdCtrl->writeWaitCallback = callBack;
}

/**
 * @name: 
 * @msg: 
 * @in param: 
 * @inout param: 
 * @out param: 
 * @return {*}
 * @param {FT_INOUT FtsdCtrl_t} *pFtsdCtrl
 * @param {FT_IN pFtsdCtrl_irqWaitCallback_t} callBack
 */
void FSdCtrl_ReadWaitRegister(FT_INOUT FtsdCtrl_t *pFtsdCtrl, FT_IN pFtsdCtrl_irqWaitCallback_t callBack)
{
    Ft_assertVoid(FT_NULL != pFtsdCtrl);
    pFtsdCtrl->readWaitCallback = callBack;
}

/**
 * @name: 
 * @msg: 
 * @in param: 
 * @inout param: 
 * @out param: 
 * @return {*}
 * @param {FT_INOUT FtsdCtrl_t} *pFtsdCtrl
 * @param {FT_IN pFtsdCtrl_irqWaitCallback_t} callBack
 */
void FSdCtrl_CmdWaitRegister(FT_INOUT FtsdCtrl_t *pFtsdCtrl, FT_IN pFtsdCtrl_irqWaitCallback_t callBack)
{
    Ft_assertVoid(FT_NULL != pFtsdCtrl);
    pFtsdCtrl->cmdWaitCallback = callBack;
}

/**
 * @name: 
 * @msg: 
 * @in param: 
 * @inout param: 
 * @out param: 
 * @return {*}
 * @param {FT_INOUT FtsdCtrl_t} *pFtsdCtrl
 */
u32 FSdCtrl_GetNormalIrqStatus(FT_INOUT FtsdCtrl_t *pFtsdCtrl)
{
    Ft_assertNonvoid(FT_NULL != pFtsdCtrl);
    FSdCtrl_Config_t *pConfig;
    pConfig = &pFtsdCtrl->config;
    // rt_kprintf("FSdCtrl_GetNormalIrqStatus is in \r\n");
    return Ft_in32(pConfig->baseAddress + NORMAL_INT_STATUS_REG);
}

/**
 * @name: 
 * @msg: 
 * @in param: 
 * @inout param: 
 * @out param: 
 * @return {*}
 * @param {FT_INOUT FtsdCtrl_t} *pFtsdCtrl
 */
u32 FSdCtrl_GetDataIrqStatus(FT_INOUT FtsdCtrl_t *pFtsdCtrl)
{
    Ft_assertNonvoid(FT_NULL != pFtsdCtrl);
    FSdCtrl_Config_t *pConfig;
    pConfig = &pFtsdCtrl->config;

    return Ft_in32(pConfig->baseAddress + BD_ISR_REG);
}

/**
 * @name: 
 * @msg: 
 * @in param: 
 * @inout param: 
 * @out param: 
 * @return {*}
 * @param {FT_INOUT FtsdCtrl_t} *pFtsdCtrl
 */
u32 FSdCtrl_GetErrorIrqStatus(FT_INOUT FtsdCtrl_t *pFtsdCtrl)
{
    Ft_assertNonvoid(FT_NULL != pFtsdCtrl);
    FSdCtrl_Config_t *pConfig;
    pConfig = &pFtsdCtrl->config;

    return Ft_in32(pConfig->baseAddress + ERROR_INT_STATUS_REG);
}