/**
  ******************************************************************************
  * @file    bl616_sdh.c
  * @version V1.2
  * @date
  * @brief   This file is the standard driver c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2018 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#include "bl616.h"
#include "string.h"
#include "bl616_sdh.h"

/** @addtogroup  BL616_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SDH
 *  @{
 */

/** @defgroup  SDH_Private_Macros
 *  @{
 */

/*@} end of group SDH_Private_Macros */

/** @defgroup  SDH_Private_Types
 *  @{
 */

/*@} end of group SDH_Private_Types */

/** @defgroup  SDH_Private_Variables
 *  @{
 */
static uint32_t bootDummy = 0;
static SDH_Handle_Cfg_Type *sdhHandle = NULL;

/*@} end of group SDH_Private_Variables */

/** @defgroup  SDH_Global_Variables
 *  @{
 */

/*@} end of group SDH_Global_Variables */

/** @defgroup  SDH_Private_Fun_Declaration
 *  @{
 */
static void SDH_IntHandler(IRQn_Type intPeriph, SDH_Handle_Cfg_Type *handle);

/*@} end of group SDH_Private_Fun_Declaration */

/** @defgroup  SDH_Private_Functions
 *  @{
 */

/*@} end of group SDH_Private_Functions */

/** @defgroup  SDH_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Enable SDH DMA
 *
 * @param  dmaMode: DMA mode select
 *
 * @return None
 *
*******************************************************************************/
void SDH_EnableDMA(SDH_DMA_Mode_Type dmaMode)
{
    uint16_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_SDH_DMA_MODE_TYPE(dmaMode));

    /* Select DMA type */
    tmpVal = BL_RD_REG16(SDH_BASE, SDH_SD_HOST_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SDH_DMA_SEL, dmaMode);
    BL_WR_REG16(SDH_BASE, SDH_SD_HOST_CTRL, tmpVal);

    tmpVal = BL_RD_REG16(SDH_BASE, SDH_SD_TRANSFER_MODE);
    tmpVal = BL_SET_REG_BIT(tmpVal, SDH_DMA_EN);
    BL_WR_REG16(SDH_BASE, SDH_SD_TRANSFER_MODE, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Disable SDH DMA
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void SDH_DisableDMA(void)
{
    uint16_t tmpVal;

    tmpVal = BL_RD_REG16(SDH_BASE, SDH_SD_TRANSFER_MODE);
    tmpVal = BL_CLR_REG_BIT(tmpVal, SDH_DMA_EN);
    BL_WR_REG16(SDH_BASE, SDH_SD_TRANSFER_MODE, tmpVal);
}
/****************************************************************************/ /**
 * @brief  SDH enable interrupt
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void SDH_ITConfig(uint32_t SDH_IT_FLAG, BL_Fun_Type NewState)
{
    if (NewState != DISABLE) {
        /* Enable the SDH interrupts */
        SDH_EnableIntSource(SDH_IT_FLAG);
    } else {
        /* Disable the SDH interrupts */
        SDH_DisableIntSource(SDH_IT_FLAG);
    }
}
/****************************************************************************/ /**
 * @brief  SDH enable interrupt
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void SDH_EnableStatus(void)
{
    uint32_t tmpVal;

    /* Disable all interrupts */
    SDH_DisableIntStatus(SDH_INT_ALL);

    tmpVal = (SDH_INT_CMD_TIMEOUT | SDH_INT_CMD_CRC_ERROR | SDH_INT_CMD_ENDBIT_ERROR |
              SDH_INT_CMD_INDEX_ERROR | SDH_INT_CMD_COMPLETED |
              SDH_INT_CARD_INSERT | SDH_INT_CARD_REMOVE |
              SDH_INT_DATA_COMPLETED | SDH_INT_DMA_COMPLETED |
              SDH_INT_BUFFER_WRITE_READY | SDH_INT_BUFFER_READ_READY |
              SDH_INT_DATA_TIMEOUT | SDH_INT_DATA_CRC_ERROR | SDH_INT_DATA_ENDBIT_ERROR |
              SDH_INT_AUTO_CMD12_ERROR | SDH_INT_DMA_ERROR | SDH_INT_BLK_GAP_EVENT |
              SDH_INT_RETUNE_EVENT | SDH_INT_TUNE_ERROR);

    SDH_EnableIntStatus(tmpVal);
}
/****************************************************************************/ /**
 * @brief  SDH enable interrupt
 *
 * @param  dataCfg: Transfer data config pointer
 *
 * @return SDH status
 *
*******************************************************************************/
SDH_Stat_Type SDH_ConfigDataTranfer(SDH_Data_Cfg_Type *dataCfg)
{
    uint16_t tmpVal;

    if (dataCfg != NULL) {
        /* For transfer boot continous, only need to set the CREQ bit */
        if (dataCfg->dataType == SDH_TRANS_DATA_BOOT_CONT) {
            tmpVal = BL_RD_REG16(SDH_BASE, SDH_SD_BLOCK_GAP_CTRL);
            /* Clear stop at block gap request */
            tmpVal = BL_CLR_REG_BIT(tmpVal, SDH_STOP_AT_BLOCK_GAP_REQ);
            /* Continous transfer data */
            tmpVal = BL_SET_REG_BIT(tmpVal, SDH_CONT_REQ);
            BL_WR_REG16(SDH_BASE, SDH_SD_BLOCK_GAP_CTRL, tmpVal);

            return SDH_STAT_SUCCESS;
        }

        tmpVal = BL_RD_REG16(SDH_BASE, SDH_SD_PRESENT_STATE_1);

        /* Check data inhibit flag */
        if (BL_IS_REG_BIT_SET(tmpVal, SDH_CMD_INHIBIT_DAT)) {
            return SDH_STAT_BUSY;
        }

        tmpVal = BL_RD_REG16(SDH_BASE, SDH_SD_TRANSFER_MODE);

        /* Check transfer block count */
        if ((dataCfg->blockCount > SDH_MAX_BLOCK_COUNT) || ((dataCfg->txData == NULL) && (dataCfg->rxData == NULL))) {
            return SDH_STAT_INVLAID_PARA;
        }

        if (dataCfg->rxData) {
            tmpVal = BL_SET_REG_BIT(tmpVal, SDH_TO_HOST_DIR);
        } else {
            tmpVal = BL_CLR_REG_BIT(tmpVal, SDH_TO_HOST_DIR);
        }

        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SDH_AUTO_CMD_EN, 0x00);

        /* auto command 23, auto send set block count cmd before multiple read/write */
        if (dataCfg->enableAutoCommand23) {
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SDH_AUTO_CMD_EN, 0x02);
            BL_WR_REG(SDH_BASE, SDH_SD_SYS_ADDR_LOW, dataCfg->blockCount);
        } else if (dataCfg->enableAutoCommand12) {
            /* auto command 12 */
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SDH_AUTO_CMD_EN, 0x01);
        }

        if (dataCfg->blockCount > 1U) {
            tmpVal = BL_SET_REG_BIT(tmpVal, SDH_MULTI_BLK_SEL);
        } else {
            tmpVal = BL_CLR_REG_BIT(tmpVal, SDH_MULTI_BLK_SEL);
        }

        /* Enable block count */
        tmpVal = BL_SET_REG_BIT(tmpVal, SDH_BLK_CNT_EN);

        BL_WR_REG16(SDH_BASE, SDH_SD_TRANSFER_MODE, tmpVal);

        /* if transfer boot data, leave the block count to SDH_SetMmcBootConfig function */
        if (dataCfg->dataType != SDH_TRANS_DATA_BOOT) {
            /* config data block size/block count */
            BL_WR_REG16(SDH_BASE, SDH_SD_BLOCK_SIZE, dataCfg->blockSize);
            BL_WR_REG16(SDH_BASE, SDH_SD_BLOCK_COUNT, dataCfg->blockCount);
        }
    } else {
        /* clear data flags */
        tmpVal = BL_RD_REG16(SDH_BASE, SDH_SD_TRANSFER_MODE);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SDH_AUTO_CMD_EN, 0x00);
        BL_WR_REG16(SDH_BASE, SDH_SD_TRANSFER_MODE, tmpVal);

        tmpVal = BL_RD_REG16(SDH_BASE, SDH_SD_PRESENT_STATE_1);

        /* Check data inhibit flag */
        if (BL_IS_REG_BIT_SET(tmpVal, SDH_CMD_INHIBIT_CMD)) {
            return SDH_STAT_BUSY;
        }
    }

    return SDH_STAT_SUCCESS;
}

/****************************************************************************/ /**
 * @brief  SDH enable interrupt
 *
 * @param  cmd: Transfer data config pointer
 *
 * @return SDH status
 *
*******************************************************************************/
SDH_Stat_Type SDH_GetCmdResp(SDH_CMD_Cfg_Type *cmd)
{
    if (cmd->respType != SDH_RESP_NONE) {
        cmd->response[0U] = BL_RD_REG(SDH_BASE, SDH_SD_RESP_0);
        cmd->response[1U] = BL_RD_REG(SDH_BASE, SDH_SD_RESP_2);
        cmd->response[2U] = BL_RD_REG(SDH_BASE, SDH_SD_RESP_4);
        cmd->response[3U] = BL_RD_REG(SDH_BASE, SDH_SD_RESP_6);
    }

    return SDH_STAT_SUCCESS;
}

/****************************************************************************/ /**
 * @brief  SDH read data port
 *
 * @param  dataCfg: Transfer data config pointer
 *
 * @return Read length
 *
*******************************************************************************/
uint32_t SDH_ReadDataPort(SDH_Data_Cfg_Type *dataCfg)
{
    uint32_t tmpVal;
    uint32_t totalLen, recvLen = 0;

    totalLen = (dataCfg->blockCount * dataCfg->blockSize);
    tmpVal = BL_RD_REG(SDH_BASE, SDH_SD_TRANSFER_MODE);

    if (!BL_IS_REG_BIT_SET(tmpVal, SDH_DMA_EN)) {
        do {
            dataCfg->rxData[dataCfg->rxDataLen++] = BL_RD_REG(SDH_BASE, SDH_SD_BUFFER_DATA_PORT_0);
            recvLen += 4;
        } while (recvLen < totalLen);
    }

    return recvLen;
}

/****************************************************************************/ /**
 * @brief  SDH read data port
 *
 * @param  dataCfg: Transfer data config pointer
 *
 * @return Read length
 *
*******************************************************************************/
SDH_Stat_Type SDH_ReadDataPortBlock(SDH_Data_Cfg_Type *dataCfg)
{
    uint32_t intStatus = 0U;
    SDH_Stat_Type error = SDH_STAT_SUCCESS;

    /* Make sure the buffer size is 4 byte aligned */
    if (dataCfg->blockSize % sizeof(uint32_t) != 0U) {
        dataCfg->blockSize += sizeof(uint32_t) - (dataCfg->blockSize % sizeof(uint32_t));
    }

    while (!(intStatus & (SDH_INT_BUFFER_READ_READY | SDH_INT_DATA_ERRORS | SDH_INT_TUNE_ERROR))) {
        intStatus = SDH_GetIntStatus();
    }

    /* during std tuning process, software do not need to read data, but wait BRR is enough */
    if ((dataCfg->dataType == SDH_TRANS_DATA_TUNING) && (intStatus & SDH_INT_BUFFER_READ_READY)) {
        SDH_ClearIntStatus(SDH_INT_BUFFER_READ_READY);
        return SDH_STAT_SUCCESS;
    } else if ((intStatus & SDH_INT_TUNE_ERROR) != 0U) {
        SDH_ClearIntStatus(SDH_INT_TUNE_ERROR);
        /* if tuning error occur ,return directly */
        error = SDH_STAT_TUNE_ERROR;
    } else if ((intStatus & SDH_INT_DATA_ERRORS) != 0U) {
        if (!(dataCfg->enableIgnoreError)) {
            error = SDH_STAT_RECV_DATA_FAIL;
        }

        /* clear data error flag */
        SDH_ClearIntStatus(SDH_INT_DATA_ERRORS);
    }

    if (error == SDH_STAT_SUCCESS) {
        SDH_ReadDataPort(dataCfg);
        /* clear buffer read ready */
        SDH_ClearIntStatus(SDH_INT_BUFFER_READ_READY);
        intStatus = 0U;
    }

    /* Clear data complete flag after the last read operation. */
    SDH_ClearIntStatus(SDH_INT_DATA_COMPLETED);

    return error;
}

/****************************************************************************/ /**
 * @brief  SDH write data port
 *
 * @param  dataCfg: Transfer data config pointer
 *
 * @return write length
 *
*******************************************************************************/
uint32_t SDH_WriteDataPort(SDH_Data_Cfg_Type *dataCfg)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(SDH_BASE, SDH_SD_TRANSFER_MODE);

    if (!BL_IS_REG_BIT_SET(tmpVal, SDH_DMA_EN)) {
        BL_WR_REG(SDH_BASE, SDH_SD_BUFFER_DATA_PORT_0, dataCfg->txData[dataCfg->txDataLen++]);
    }

    return 4;
}

/****************************************************************************/ /**
 * @brief  SDH write data port
 *
 * @param  dataCfg: Transfer data config pointer
 *
 * @return Write length
 *
*******************************************************************************/
SDH_Stat_Type SDH_WriteDataPortBlock(SDH_Data_Cfg_Type *dataCfg)
{
    uint32_t totalLen;
    uint32_t txLen = 0U, intStatus = 0U;
    SDH_Stat_Type error = SDH_STAT_SUCCESS;

    /* Make sure the buffer size is 4 byte aligned */
    if (dataCfg->blockSize % sizeof(uint32_t) != 0U) {
        dataCfg->blockSize += sizeof(uint32_t) - (dataCfg->blockSize % sizeof(uint32_t));
    }

    totalLen = (dataCfg->blockCount * dataCfg->blockSize);

    while ((error == SDH_STAT_SUCCESS) && (txLen < totalLen)) {
        while (!(intStatus & (SDH_INT_BUFFER_WRITE_READY | SDH_INT_DATA_ERRORS | SDH_INT_TUNE_ERROR))) {
            intStatus = SDH_GetIntStatus();
        }

        if ((intStatus & SDH_INT_TUNE_ERROR) != 0U) {
            SDH_ClearIntStatus(SDH_INT_TUNE_ERROR);
            /* if tuning error occur ,return directly */
            error = SDH_STAT_TUNE_ERROR;
        } else if ((intStatus & SDH_INT_DATA_ERRORS) != 0U) {
            if (!(dataCfg->enableIgnoreError)) {
                error = SDH_STAT_RECV_DATA_FAIL;
            }

            /* clear data error flag */
            SDH_ClearIntStatus(SDH_INT_DATA_ERRORS);
        }

        if (error == SDH_STAT_SUCCESS) {
            txLen += SDH_WriteDataPort(dataCfg);
            /* clear buffer read ready */
            SDH_ClearIntStatus(SDH_INT_BUFFER_WRITE_READY);
            intStatus = 0U;
        }
    }

    while (!(intStatus & (SDH_INT_DATA_COMPLETED | SDH_INT_DATA_ERRORS))) {
        intStatus = SDH_GetIntStatus();
    }

    if ((intStatus & SDH_INT_DATA_ERRORS) != 0U) {
        if (!(dataCfg->enableIgnoreError)) {
            error = SDH_STAT_RECV_DATA_FAIL;
        }

        /* clear data error flag */
        SDH_ClearIntStatus(SDH_INT_DATA_ERRORS);
    }

    SDH_ClearIntStatus(SDH_INT_DATA_COMPLETED);

    return error;
}

/****************************************************************************/ /**
 * @brief  SDH send command
 *
 * @param  cmd: command config pointer
 *
 * @return None
 *
*******************************************************************************/
void SDH_SendCommand(SDH_CMD_Cfg_Type *cmd)
{
    uint32_t tmpVal;
    uint32_t flag = cmd->flag;
    //uint32_t flag = 0;

    tmpVal = BL_RD_REG(SDH_BASE, SDH_SD_PRESENT_STATE_1);

    if (((tmpVal & SDH_PRESENT_FLAG_CMD_INHBIT) == 0U) && (cmd->type != SDH_CMD_EMPTY)) {
        /* Define the flag corresponding to each response type. */
        switch (cmd->respType) {
            case SDH_RESP_NONE:
                break;

            case SDH_RESP_R1: /* Response 1 */
            case SDH_RESP_R5: /* Response 5 */
            case SDH_RESP_R6: /* Response 6 */
            case SDH_RESP_R7: /* Response 7 */
                flag |= (SDH_TRANS_FLAG_RESP_48BITS | SDH_TRANS_FLAG_EN_CRC_CHECK | SDH_TRANS_FLAG_EN_INDEX_CHECK);
                break;

            case SDH_RESP_R1B: /* Response 1 with busy */
            case SDH_RESP_R5B: /* Response 5 with busy */
                flag |= (SDH_TRANS_FLAG_RESP_48BITS_WITH_BUSY | SDH_TRANS_FLAG_EN_CRC_CHECK | SDH_TRANS_FLAG_EN_INDEX_CHECK);
                break;

            case SDH_RESP_R2: /* Response 2 */
                flag |= (SDH_TRANS_FLAG_RESP_136BITS | SDH_TRANS_FLAG_EN_CRC_CHECK);
                break;

            case SDH_RESP_R3: /* Response 3 */
            case SDH_RESP_R4: /* Response 4 */
                flag |= (SDH_TRANS_FLAG_RESP_48BITS);
                break;

            default:
                break;
        }

        /* Config command index */
        tmpVal = flag >> 16;
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SDH_CMD_TYPE, cmd->type);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SDH_CMD_INDEX, cmd->index);

        /* Config command argument */
        BL_WR_REG(SDH_BASE, SDH_SD_ARG_LOW, cmd->argument);

        /* Config command index */
        BL_WR_REG16(SDH_BASE, SDH_SD_CMD, tmpVal);
    }

    /* FIXME:how to enable again */
    if (cmd->type == SDH_CMD_EMPTY) {
        SDH_DisableIntSource(SDH_INT_CMD_COMPLETED);
    }
}
/****************************************************************************/ /**
 * @brief  SDH wait command send done
 *
 * @param  cmd: Command config pointer
 *
 * @return Command deal status
 *
*******************************************************************************/
SDH_Stat_Type SDH_WaitCommandDone(SDH_CMD_Cfg_Type *cmd)
{
    uint32_t intStatus = 0U;
    SDH_Stat_Type stat = SDH_STAT_SUCCESS;

    /* Wait command complete or encounters error. */
    while (!(intStatus & (SDH_INT_CMD_COMPLETED | SDH_INT_CMD_ERRORS | SDH_INT_TUNE_ERROR))) {
        intStatus = SDH_GetIntStatus();
    }

    if ((intStatus & SDH_INT_TUNE_ERROR) != 0U) {
        stat = SDH_STAT_TUNE_ERROR;
    } else if ((intStatus & SDH_INT_CMD_ERRORS) != 0U) {
        stat = SDH_STAT_SEND_CMD_FAIL;
    }

    /* Receive response when command completes successfully. */
    if (stat == SDH_STAT_SUCCESS) {
        stat = SDH_GetCmdResp(cmd);
    }

    SDH_ClearIntStatus(SDH_INT_CMD_COMPLETED | SDH_INT_CMD_ERRORS | SDH_INT_TUNE_ERROR);

    return stat;
}

/****************************************************************************/ /**
 * @brief  SDH transfer data
 *
 * @param  dataCfg: Data config pointer
 * @param  enDMA: Whether enable DMA
 *
 * @return command deal status
 *
*******************************************************************************/
SDH_Stat_Type SDH_TransferDataBlocking(SDH_Data_Cfg_Type *dataCfg, uint8_t enDMA)
{
    SDH_Stat_Type stat = SDH_STAT_SUCCESS;
    uint32_t intStatus = 0U;

    if (enDMA) {
        /* Wait dataCfg complete or encounters error. */
        while (!(intStatus & (SDH_INT_DATA_COMPLETED | SDH_INT_DATA_ERRORS |
                              SDH_INT_DMA_ERROR | SDH_INT_TUNE_ERROR))) {
            intStatus = SDH_GetIntStatus();
        }

        if ((intStatus & SDH_INT_TUNE_ERROR) != 0U) {
            stat = SDH_STAT_TUNE_ERROR;
        } else if ((intStatus & (SDH_INT_DATA_ERRORS | SDH_INT_DMA_ERROR)) != 0U) {
            if ((!(dataCfg->enableIgnoreError)) || (intStatus & SDH_INT_DATA_TIMEOUT)) {
                stat = SDH_STAT_SEND_DATA_FAIL;
            }
        }

        /* load dummy data */
        if ((dataCfg->dataType == SDH_TRANS_DATA_BOOT_CONT) && (stat == SDH_STAT_SUCCESS)) {
            *(dataCfg->rxData) = bootDummy;
        }

        SDH_ClearIntStatus(SDH_INT_DATA_COMPLETED | SDH_INT_DATA_ERRORS |
                           SDH_INT_DMA_ERROR | SDH_INT_TUNE_ERROR);
    } else {
        if (dataCfg->rxData) {
            stat = SDH_ReadDataPortBlock(dataCfg);
        } else {
            stat = SDH_WriteDataPortBlock(dataCfg);
        }
    }

    return stat;
}

/****************************************************************************/ /**
 * @brief  SDH set clock
 *
 * @param  srcClock: Source clock frequency in Hz
 * @param  busClock: SDH clock frequency in Hz
 *
 * @return None
 *
*******************************************************************************/
void SDH_SetSdClock(uint32_t srcClock, uint32_t busClock)
{
    uint16_t tmpVal;
    uint16_t div = srcClock / busClock / 2;

    tmpVal = BL_RD_REG16(SDH_BASE, SDH_SD_CLOCK_CTRL);

    /* Disable internal clock*/
    tmpVal = BL_CLR_REG_BIT(tmpVal, SDH_INT_CLK_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, SDH_SD_CLK_EN);

    /* Set divdier */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SDH_SD_FREQ_SEL_LO, div & 0xff);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SDH_SD_FREQ_SEL_HI, (div >> 8) & 0x3);
    /* 0x1 = Programmable Clock Mode,0x0 = Divided Clock mode */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SDH_CLK_GEN_SEL, 0);

    /* Enable internal clock*/
    tmpVal = BL_SET_REG_BIT(tmpVal, SDH_INT_CLK_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal, SDH_SD_CLK_EN);

    BL_WR_REG16(SDH_BASE, SDH_SD_CLOCK_CTRL, tmpVal);

    /* Wait for clock stable */
    do {
        tmpVal = BL_RD_REG16(SDH_BASE, SDH_SD_CLOCK_CTRL);
    } while (!BL_IS_REG_BIT_SET(tmpVal, SDH_INT_CLK_STABLE));
}

/****************************************************************************/ /**
 * @brief  SDH disable clock
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void SDH_DisableSdClock(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(SDH_BASE, SDH_SD_CLOCK_CTRL);

    /* Disable internal clock*/
    tmpVal = BL_CLR_REG_BIT(tmpVal, SDH_INT_CLK_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, SDH_SD_CLK_EN);

    BL_WR_REG(SDH_BASE, SDH_SD_CLOCK_CTRL, tmpVal);
}
/****************************************************************************
 * @brief  SDH init function
 *
 * @param  cfg: SDH config pointer
 *
 * @return None
 *
*******************************************************************************/
void SDH_Powon(void)
{
    uint32_t tmpVal;
    tmpVal = BL_RD_REG16(SDH_BASE, SDH_SD_HOST_CTRL);
    tmpVal = BL_SET_REG_BIT(tmpVal, SDH_SD_BUS_POWER);
    BL_WR_REG16(SDH_BASE, SDH_SD_HOST_CTRL, tmpVal);
}
/****************************************************************************
 * @brief  SDH init function
 *
 * @param  cfg: SDH config pointer
 *
 * @return None
 *
*******************************************************************************/
void SDH_Ctrl_Init(const SDH_Cfg_Type *cfg)
{
    uint32_t tmpVal;

    SDH_SetSdClock(cfg->srcClock, cfg->busClock);
    SDH_DisableDMA();

    /* Set SDH config */
    tmpVal = BL_RD_REG16(SDH_BASE, SDH_SD_HOST_CTRL);

    if (cfg->dataWidth == SDH_DATA_BUS_WIDTH_8BITS) {
        tmpVal = BL_SET_REG_BIT(tmpVal, SDH_EX_DATA_WIDTH);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, SDH_EX_DATA_WIDTH);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SDH_DATA_WIDTH, cfg->dataWidth);
    }

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SDH_HI_SPEED_EN, cfg->highSpeed);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SDH_SD_BUS_VLT, cfg->volt);

    BL_WR_REG16(SDH_BASE, SDH_SD_HOST_CTRL, tmpVal);

    if (cfg->vlot18Enable) {
        tmpVal = BL_RD_REG16(SDH_BASE, SDH_HOST_CTRL_2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SDH_UHS_MODE_SEL, cfg->speed);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SDH_SDH_V18_EN, cfg->vlot18Enable);
        BL_WR_REG16(SDH_BASE, SDH_HOST_CTRL_2, tmpVal);
    }

    tmpVal = BL_RD_REG(SDH_BASE, SDH_TX_CFG_REG);
    tmpVal = BL_SET_REG_BIT(tmpVal, SDH_TX_INT_CLK_SEL);
    BL_WR_REG(SDH_BASE, SDH_TX_CFG_REG, tmpVal);

    SDH_EnableStatus();

#ifndef BFLB_USE_HAL_DRIVER
    /*!< use bflb irq */
    // Interrupt_Handler_Register(SDH_IRQn, SDH_MMC1_IRQHandler);
#endif
}

/****************************************************************************/ /**
 * @brief  SDH deinit function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void SDH_Deinit(void)
{
    SDH_DisableDMA();
}

/****************************************************************************/ /**
 * @brief  SDH reset function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void SDH_Reset(void)
{
    uint16_t tmpVal;

    tmpVal = BL_RD_REG16(SDH_BASE, SDH_SD_TIMEOUT_CTRL_SW_RESET);
    tmpVal = BL_SET_REG_BIT(tmpVal, SDH_SW_RST_ALL);
    BL_WR_REG16(SDH_BASE, SDH_SD_TIMEOUT_CTRL_SW_RESET, tmpVal);

    /* Wait for reset done */
    do {
        tmpVal = BL_RD_REG16(SDH_BASE, SDH_SD_TIMEOUT_CTRL_SW_RESET);
    } while (BL_IS_REG_BIT_SET(tmpVal, SDH_SW_RST_ALL));
}
/****************************************************************************/ /**
 * @brief  SDH set timeout function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void SDH_Set_Timeout(uint8_t tmo)
{
    uint16_t tmpVal;

    tmpVal = BL_RD_REG16(SDH_BASE, SDH_SD_TIMEOUT_CTRL_SW_RESET);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SDH_TIMEOUT_VALUE, tmo);
    BL_WR_REG16(SDH_BASE, SDH_SD_TIMEOUT_CTRL_SW_RESET, tmpVal);
}

/****************************************************************************/ /**
 * @brief  SDH get capability
 *
 * @param  capability: None
 *
 * @return None
 *
*******************************************************************************/
void SDH_GetCapability(SDH_Cap_Cfg_Type *capability)
{
    /* Get the capability  */
    capability->maxBlockLength = 512;
    capability->maxBlockCount = 65536;
    capability->flags = (SDH_CAP_SUPPORT_8BITS |
                         SDH_CAP_SUPPORT_ADMA2 |
                         SDH_CAP_SUPPORT_ADMA1 |
                         SDH_CAP_SUPPORT_HIGHSPEED |
                         SDH_CAP_SUPPORT_SDMA |
                         SDH_CAP_SUPPORT_SUS_RES |
                         SDH_CAP_SUPPORT_VLT33 |
                         SDH_CAP_SUPPORT_VLT18 |
                         SDH_CAP_SUPPORT_SBUS_64BITS |
                         SDH_CAP_SUPPORT_ASYNC_INT |
                         SDH_CAP_SUPPORT_DDR50 |
                         SDH_CAP_SUPPORT_SDR104 |
                         SDH_CAP_SUPPORT_SDR50 |
                         SDH_CAP_SUPPORT_DRV_TYPE_A |
                         SDH_CAP_SUPPORT_DRV_TYPE_C |
                         SDH_CAP_SUPPORT_DRV_TYPE_D |
                         SDH_CAP_SUPPORT_SDR50_TUNE);
}

/****************************************************************************/ /**
 * @brief  SDH create ADMA1 descriptor
 *
 * @param  adma1Entries: ADMA1 entries pointer
 * @param  maxEntries: ADMA1 entries size
 * @param  data: Data buffer to deal with
 * @param  dataLen: Data length
 * @param  flag: ADMA setting flag
 *
 * @return SDH deal status
 *
*******************************************************************************/
SDH_Stat_Type SDH_CreateADMA1Descriptor(uint32_t *adma1Entries, uint32_t maxEntries,
                                        const uint32_t *data, uint32_t dataLen, SDH_ADMA_Flag_Type flag)
{
    uint32_t miniEntries, startEntries = 0U;
    uint32_t i, dmaBufferLen = 0U;

    if (((uintptr_t)data % SDH_ADMA1_ADDRESS_ALIGN) != 0U) {
        return SDH_STAT_DMA_ADDR_NOT_ALIGN;
    }

    if (flag == SDH_ADMA_FLAG_MULTI_DESC) {
        return SDH_STAT_NOT_SUPPORT;
    }

    /* TODO:align */
    /* Make sure the buffer size is 4 byte aligned */
    if (dataLen % sizeof(uint32_t) != 0U) {
        /* make the data length as word-aligned */
        dataLen += sizeof(uint32_t) - (dataLen % sizeof(uint32_t));
    }

    /* Check if ADMA descriptor's number is enough. */
    if ((dataLen % SDH_ADMA1_DESCRIPTOR_MAX_LENGTH_PER_ENTRY) == 0U) {
        miniEntries = dataLen / SDH_ADMA1_DESCRIPTOR_MAX_LENGTH_PER_ENTRY;
    } else {
        miniEntries = ((dataLen / SDH_ADMA1_DESCRIPTOR_MAX_LENGTH_PER_ENTRY) + 1U);
    }

    /* ADMA1 needs two descriptors to finish a transfer */
    miniEntries <<= 1U;

    if (miniEntries + startEntries > maxEntries) {
        return SDH_STAT_OUTOF_RANGE;
    }

    for (i = startEntries; i < (miniEntries + startEntries); i += 2U) {
        if (dataLen > SDH_ADMA1_DESCRIPTOR_MAX_LENGTH_PER_ENTRY) {
            dmaBufferLen = SDH_ADMA1_DESCRIPTOR_MAX_LENGTH_PER_ENTRY;
        } else {
            dmaBufferLen = dataLen;
        }

        adma1Entries[i] = (dmaBufferLen << SDH_ADMA1_DESCRIPTOR_LENGTH_POS);
        adma1Entries[i] |= SDH_ADMA1_DESC_FLAG_SETLEN;
        adma1Entries[i + 1U] = (uintptr_t)(data);
        adma1Entries[i + 1U] |= SDH_ADMA1_DESC_FLAG_TRANSFER;
        data += (dmaBufferLen / sizeof(uint32_t));
        dataLen -= dmaBufferLen;
    }

    /* Set end of the descriptor */
    adma1Entries[i - 1U] |= SDH_ADMA1_DESC_FLAG_END;

    return SDH_STAT_SUCCESS;
}

/****************************************************************************/ /**
 * @brief  SDH create ADMA2 descriptor
 *
 * @param  adma2Entries: ADMA2 entries pointer
 * @param  maxEntries: ADMA2 entries size
 * @param  data: Data buffer to deal with
 * @param  dataLen: Data length
 * @param  flag: ADMA setting flag
 *
 * @return SDH deal status
 *
*******************************************************************************/
SDH_Stat_Type SDH_CreateADMA2Descriptor(SDH_ADMA2_Desc_Type *adma2Entries, uint32_t maxEntries,
                                        const uint32_t *data, uint32_t dataLen, SDH_ADMA_Flag_Type flag)
{
    uint32_t miniEntries, startEntries = 0U;
    uint32_t i, dmaBufferLen = 0U;

    if (((uintptr_t)data % SDH_ADMA2_ADDRESS_ALIGN) != 0U) {
        return SDH_STAT_DMA_ADDR_NOT_ALIGN;
    }

    /* TODO:align */
    /* Make sure the buffer size is 4 byte aligned */
    if (dataLen % sizeof(uint32_t) != 0U) {
        /* make the data length as word-aligned */
        dataLen += sizeof(uint32_t) - (dataLen % sizeof(uint32_t));
    }

    /* Check if ADMA descriptor's number is enough. */
    if ((dataLen % SDH_ADMA2_DESCRIPTOR_MAX_LENGTH_PER_ENTRY) == 0U) {
        miniEntries = dataLen / SDH_ADMA2_DESCRIPTOR_MAX_LENGTH_PER_ENTRY;
    } else {
        miniEntries = ((dataLen / SDH_ADMA2_DESCRIPTOR_MAX_LENGTH_PER_ENTRY) + 1U);
    }

    /* Calculate the start entry for multiple descriptor mode, ADMA engine is not stop, so update the descriptor
	data address and data size is enough */
    if (flag == SDH_ADMA_FLAG_MULTI_DESC) {
        for (i = 0U; i < maxEntries; i++) {
            if ((adma2Entries[i].attribute & SDH_ADMA2_DESC_FLAG_VALID) == 0U) {
                break;
            }
        }

        startEntries = i;
        /* Add one entry for dummy entry */
        miniEntries += 1U;
    }

    if (miniEntries + startEntries > maxEntries) {
        return SDH_STAT_OUTOF_RANGE;
    }

    for (i = startEntries; i < (miniEntries + startEntries); i++) {
        if (dataLen > SDH_ADMA2_DESCRIPTOR_MAX_LENGTH_PER_ENTRY) {
            dmaBufferLen = SDH_ADMA2_DESCRIPTOR_MAX_LENGTH_PER_ENTRY;
        } else {
            /* TODO:align */
            /* Adma don't support 0 data length transfer descriptor */
            dmaBufferLen = (dataLen == 0U ? sizeof(uint32_t) : dataLen);
        }

        /* Each descriptor for ADMA2 is 64-bit in length */
        adma2Entries[i].address = (dataLen == 0U) ? &bootDummy : data;
        adma2Entries[i].attribute = (dmaBufferLen << SDH_ADMA2_DESCRIPTOR_LENGTH_POS);
        adma2Entries[i].attribute |=
            (dataLen == 0U) ? 0U : (SDH_ADMA2_DESC_FLAG_TRANSFER);
        //          (dataLen == 0U) ? 0U : (SDH_ADMA2_DESC_FLAG_TRANSFER | SDH_ADMA2_DESC_FLAG_INT);
        /* TODO:align */
        data += (dmaBufferLen / sizeof(uint32_t));

        if (dataLen != 0U) {
            dataLen -= dmaBufferLen;
        }
    }

    /* add a dummy valid ADMA descriptor for multiple descriptor mode, this is useful when transfer boot data, the ADMA
	engine  will not stop at block gap */
    if (flag == SDH_ADMA_FLAG_MULTI_DESC) {
        //adma2Entries[startEntries + 1U].attribute |= SDH_ADMA2_DESC_FLAG_TRANSFER;
        adma2Entries[i - 1U].attribute |= SDH_ADMA2_DESC_FLAG_TRANSFER;
    } else {
        /* Set the end bit */
        adma2Entries[i - 1U].attribute |= SDH_ADMA2_DESC_FLAG_END;
    }

    return SDH_STAT_SUCCESS;
}

/****************************************************************************/ /**
 * @brief  SDH set DMA config
 *
 * @param  dmaCfg: DMA config pointer
 * @param  data: Data pointer for sending
 * @param  enAutoCmd23: Whether enable auto command 23
 *
 * @return DMA config deal status
 *
*******************************************************************************/
SDH_Stat_Type SDH_SetInternalDmaConfig(SDH_DMA_Cfg_Type *dmaCfg, const uint32_t *data, uint8_t enAutoCmd23)
{
    uint16_t tmpVal;

    if (dmaCfg->dmaMode == SDH_DMA_MODE_SIMPLE) {
        /* Check DMA data buffer address align or not */
        if (((uintptr_t)data % SDH_SDMA_LENGTH_ALIGN) != 0U) {
            return SDH_STAT_DMA_ADDR_NOT_ALIGN;
        }

        /* In simple DMA mode if use auto CMD23, address should load to ADMA addr,
		     and block count should load to DS_ADDR*/
        if (enAutoCmd23) {
            BL_WR_REG(SDH_BASE, SDH_SD_ADMA_SYS_ADDR_1, (uintptr_t)data);
        } else {
            BL_WR_REG(SDH_BASE, SDH_SD_SYS_ADDR_LOW, (uintptr_t)data);
        }
    } else {
        /* When use ADMA, disable simple DMA */
        BL_WR_REG(SDH_BASE, SDH_SD_SYS_ADDR_LOW, (uint32_t)0);
        BL_WR_REG(SDH_BASE, SDH_SD_ADMA_SYS_ADDR_1, (uintptr_t)(dmaCfg->admaEntries));
    }

    /* Select DMA mode and config the burst length */
    SDH_EnableDMA(dmaCfg->dmaMode);

    /* Set DMA burst size and FIFO threshold */
    tmpVal = BL_RD_REG16(SDH_BASE, SDH_SD_CLOCK_AND_BURST_SIZE_SETUP);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SDH_DMA_SIZE, dmaCfg->fifoThreshold);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SDH_BRST_SIZE, dmaCfg->burstSize);
    BL_WR_REG16(SDH_BASE, SDH_SD_CLOCK_AND_BURST_SIZE_SETUP, tmpVal);

    return SDH_STAT_SUCCESS;
}

/****************************************************************************/ /**
 * @brief  SDH create DMA entries according to DMA config
 *
 * @param  dmaCfg: DMA config pointer
 * @param  dataCfg: Data config pointer
 * @param  flag: ADMA create entries flag
 *
 * @return Create entries result
 *
*******************************************************************************/
SDH_Stat_Type SDH_CreateAdmaEntryConfig(SDH_DMA_Cfg_Type *dmaCfg, SDH_Data_Cfg_Type *dataCfg, SDH_ADMA_Flag_Type flag)
{
    SDH_Stat_Type stat = SDH_STAT_SUCCESS;

    /* TODO:align */
    uint32_t bootDummyOffset = (dataCfg->dataType == SDH_TRANS_DATA_BOOT_CONT ? sizeof(uint32_t) : 0);
    const uint32_t *data = (const uint32_t *)((dataCfg->rxData == NULL) ? dataCfg->txData : dataCfg->rxData);
    uint32_t dataLen = dataCfg->blockSize * dataCfg->blockCount;

    data += bootDummyOffset;
    dataLen -= bootDummyOffset;

    switch (dmaCfg->dmaMode) {
        case SDH_DMA_MODE_SIMPLE:
            stat = SDH_STAT_SUCCESS;
            break;

        case SDH_DMA_MODE_ADMA1:
            stat = SDH_CreateADMA1Descriptor(dmaCfg->admaEntries, dmaCfg->maxEntries, data, dataLen, flag);
            break;

        case SDH_DMA_MODE_ADMA2:
            stat = SDH_CreateADMA2Descriptor((SDH_ADMA2_Desc_Type *)dmaCfg->admaEntries, dmaCfg->maxEntries, data, dataLen, flag);
            break;

        default:
            return SDH_STAT_SEND_DATA_FAIL;
    }

    /* For internal dma, internal DMA configurations should not update the configurations when continous transfer the
	 * boot data, only the DMA descriptor need update */
    if ((stat == SDH_STAT_SUCCESS) && (dataCfg->dataType != SDH_TRANS_DATA_BOOT_CONT)) {
        stat = SDH_SetInternalDmaConfig(dmaCfg, data, dataCfg->enableAutoCommand23);
    }

    return stat;
}

/****************************************************************************/ /**
 * @brief  SDH transfer data in blocking way
 *
 * @param  dmaCfg: DMA config pointer
 * @param  transfer: Transfer config pointer
 *
 * @return Transfer deal status
 *
*******************************************************************************/
SDH_Stat_Type SDH_TransferBlocking(SDH_DMA_Cfg_Type *dmaCfg, SDH_Trans_Cfg_Type *transfer)
{
    SDH_Stat_Type stat = SDH_STAT_SUCCESS;
    SDH_CMD_Cfg_Type *cmdCfg = transfer->cmdCfg;
    SDH_Data_Cfg_Type *dataCfg = transfer->dataCfg;
    uint32_t intStatus;
    uint8_t enDMA = 1;
    uint8_t executeTuning = ((dataCfg == NULL) ? 0 : dataCfg->dataType == SDH_TRANS_DATA_TUNING);
    //volatile uint32_t tmp;
    /* Check re-tuning request */
    intStatus = SDH_GetIntStatus();

    if ((intStatus & SDH_INT_RETUNE_EVENT) != 0U) {
        SDH_ClearIntStatus(SDH_INT_RETUNE_EVENT);
        return SDH_STAT_RETUNE_REQ;
    }

    /* Update ADMA descriptor table according to different DMA mode(simple DMA, ADMA1, ADMA2).*/
    if ((dataCfg != NULL) && (dmaCfg != NULL) && (!executeTuning)) {
        stat = SDH_CreateAdmaEntryConfig(dmaCfg, dataCfg, (dataCfg->dataType & SDH_TRANS_DATA_BOOT) ? SDH_ADMA_FLAG_MULTI_DESC : SDH_ADMA_FLAG_SINGLE_DESC);
    }

    /* If the DMA desciptor configure fail or not needed , disable it */
    if ((stat != SDH_STAT_SUCCESS) || (dmaCfg == NULL)) {
        enDMA = 0;
        /* Disable DMA, using polling mode in this situation */
        SDH_DisableDMA();
    }

    /* Config the data transfer parameter */
    stat = SDH_ConfigDataTranfer(dataCfg);

    if (SDH_STAT_SUCCESS != stat) {
        return stat;
    }

    /* Send command first */
    if (dataCfg != NULL) {
        cmdCfg->flag = SDH_TRANS_FLAG_DATA_PRESENT;
    } else {
        cmdCfg->flag = 0;
    }

    SDH_SendCommand(cmdCfg);

    /* Wait command done */
    if ((dataCfg == NULL) || (dataCfg->dataType == SDH_TRANS_DATA_NORMAL)) {
        stat = SDH_WaitCommandDone(cmdCfg);
    }

    /*
	tmp = BL_RD_REG16(SDH_BASE,SDH_SD_ADMA_ERROR_STATUS);
	bflb_platform_printf("SDH_SD_ADMA_ERROR_STATUS->0x%x!\r\n",tmp);
	tmp = BL_RD_REG16(SDH_BASE,SDH_SD_AUTO_CMD12_ERROR_STATUS);
	*/

    /* Wait for transferring data finish */
    if ((dataCfg != NULL) && (stat == SDH_STAT_SUCCESS)) {
        stat = SDH_TransferDataBlocking(dataCfg, enDMA);
    }

    return stat;
}

/****************************************************************************/ /**
 * @brief  SDH transfer data in blocking way
 *
 * @param  handle: SDH handler
 * @param  dmaCfg: DMA config pointer
 * @param  transfer: Transfer config pointer
 *
 * @return Transfer deal status
 *
*******************************************************************************/
SDH_Stat_Type SDH_TransferNonBlocking(SDH_DMA_Cfg_Type *dmaCfg, SDH_Trans_Cfg_Type *transfer)
{
    SDH_Stat_Type stat = SDH_STAT_SUCCESS;
    SDH_CMD_Cfg_Type *cmdCfg = transfer->cmdCfg;
    SDH_Data_Cfg_Type *dataCfg = transfer->dataCfg;
    uint32_t intStatus;
    uint8_t executeTuning = ((dataCfg == NULL) ? 0 : dataCfg->dataType == SDH_TRANS_DATA_TUNING);

    /* Check re-tuning request */
    intStatus = SDH_GetIntStatus();

    if ((intStatus & SDH_INT_RETUNE_EVENT) != 0U) {
        SDH_ClearIntStatus(SDH_INT_RETUNE_EVENT);
        return SDH_STAT_RETUNE_REQ;
    }

    /* Update ADMA descriptor table according to different DMA mode(simple DMA, ADMA1, ADMA2).*/
    if ((dataCfg != NULL) && (dmaCfg != NULL) && (!executeTuning)) {
        stat = SDH_CreateAdmaEntryConfig(dmaCfg, dataCfg, (dataCfg->dataType & SDH_TRANS_DATA_BOOT) ? SDH_ADMA_FLAG_MULTI_DESC : SDH_ADMA_FLAG_SINGLE_DESC);
    }

    /* If the DMA desciptor configure fail or not needed , disable it */
    if (stat != SDH_STAT_SUCCESS) {
        /* Disable DMA, using polling mode in this situation */
        //SDH_DisableDMA();
        return stat;
    }

    /* Config the data transfer parameter */
    stat = SDH_ConfigDataTranfer(dataCfg);

    if (SDH_STAT_SUCCESS != stat) {
        return stat;
    }

    /* Send command first */
    if (dataCfg != NULL) {
        cmdCfg->flag |= SDH_TRANS_FLAG_DATA_PRESENT;
    }

#if 0
	SDH_SendCommand(cmdCfg);


	/* Wait command done */
	if((dataCfg == NULL) || (dataCfg->dataType == SDH_TRANS_DATA_NORMAL))
	{
		stat = SDH_WaitCommandDone(cmdCfg);
	}

#endif

    return SDH_STAT_SUCCESS;
}

/****************************************************************************/ /**
 * @brief  SDH install callback function for handler
 *
 * @param  handle: SDH handler
 * @param  callBack: SDH callBack function
 * @param  userData: User private data for SDH handler
 *
 * @return None
 *
*******************************************************************************/
void SDH_InstallHandleCallback(SDH_Handle_Cfg_Type *handle,
                               const SDH_Trans_Callback_Cfg_Type *callBack, void *userData)
{
    /* Zero the handle. */
    ARCH_MemSet(handle, 0, sizeof(SDH_Handle_Cfg_Type));

    /* Set the callback. */
    handle->callBack.SDH_CallBack_CardInserted = callBack->SDH_CallBack_CardInserted;
    handle->callBack.SDH_CallBack_CardRemoved = callBack->SDH_CallBack_CardRemoved;
    handle->callBack.SDH_CallBack_SdioInterrupt = callBack->SDH_CallBack_SdioInterrupt;
    handle->callBack.SDH_CallBack_BlockGap = callBack->SDH_CallBack_BlockGap;
    handle->callBack.SDH_CallBack_TransferFinished = callBack->SDH_CallBack_TransferFinished;
    handle->callBack.SDH_CMDCallBack_TransferFinished = callBack->SDH_CMDCallBack_TransferFinished;
    handle->callBack.SDH_CallBack_ReTuning = callBack->SDH_CallBack_ReTuning;
    handle->callBack.SDH_CallBack_Vendor = callBack->SDH_CallBack_ReTuning;
    handle->userData = userData;

    /* Save the handle in global variables  */
    sdhHandle = handle;
}

/****************************************************************************/ /**
 * @brief  SDH interrupt handle
 *
 * @param  intPeriph: Select the peripheral
 * @param  handle: SDH handler
 *
 * @return None
 *
*******************************************************************************/
static void SDH_IntHandler(IRQn_Type intPeriph, SDH_Handle_Cfg_Type *handle)
{
    uint32_t intFlag, intMask;

    intFlag = SDH_GetIntStatus();
    intMask = SDH_GetIntEnableStatus();
    intFlag &= intMask;

    if (NULL == handle) {
        SDH_ClearIntStatus(intFlag);
        return;
    }

    handle->intFlag = intFlag;

    /* Card insert interrupt */
    if (intFlag & SDH_INT_CARD_INSERT) {
        if (NULL != handle->callBack.SDH_CallBack_CardInserted) {
            handle->callBack.SDH_CallBack_CardInserted(handle->userData);
        }
    }

    /* Card remove interrupt */
    if (intFlag & SDH_INT_CARD_REMOVE) {
        if (NULL != handle->callBack.SDH_CallBack_CardRemoved) {
            handle->callBack.SDH_CallBack_CardRemoved(handle->userData);
        }
    }

    /* Command error interrupt */
    if (intFlag & (SDH_INT_CMD_ERRORS)) {
        if (NULL != handle->callBack.SDH_CMDCallBack_TransferFinished) {
            handle->callBack.SDH_CMDCallBack_TransferFinished(handle, SDH_STAT_SEND_CMD_FAIL, handle->userData);
        }
    }

    /* Command success interrupt */
    if (intFlag & SDH_INT_CMD_COMPLETED) {
        if (NULL != handle->callBack.SDH_CMDCallBack_TransferFinished &&
            NULL == handle->dataCfg) {
            /* Only deal with pure command, user need check response to make sure in SDH_CallBack_TransferFinished */
            handle->callBack.SDH_CMDCallBack_TransferFinished(handle, SDH_STAT_SUCCESS, handle->userData);
        }
    }

    /* Data error interrupt */
    if (intFlag & (SDH_INT_DATA_ERRORS | SDH_INT_DMA_ERROR)) {
        if (NULL != handle->callBack.SDH_CallBack_TransferFinished) {
            handle->callBack.SDH_CallBack_TransferFinished(handle, SDH_STAT_SEND_DATA_FAIL, handle->userData);
        }
    }

    /* Data success interrupt*/
    if (intFlag & SDH_INT_DATA_COMPLETED) {
        if (NULL != handle->callBack.SDH_CallBack_TransferFinished) {
            handle->callBack.SDH_CallBack_TransferFinished(handle, SDH_STAT_SUCCESS, handle->userData);
        }
    }

    /* Card interrupt */
    if (intFlag & SDH_INT_CARD) {
        if (handle->callBack.SDH_CallBack_SdioInterrupt) {
            handle->callBack.SDH_CallBack_SdioInterrupt(handle->userData);
        }
    }

    /* Buffer read ready interrupt*/
    if (intFlag & SDH_INT_BUFFER_READ_READY) {
        if (NULL != handle->callBack.SDH_CallBack_TransferFinished) {
            handle->callBack.SDH_CallBack_TransferFinished(handle, SDH_STAT_SUCCESS, handle->userData);
        } else {
            handle->dataCfg->rxDataLen += SDH_ReadDataPort(handle->dataCfg);
        }
    }

    /* Buffer write ready interrupt */
    if (intFlag & SDH_INT_BUFFER_WRITE_READY) {
        if (NULL != handle->callBack.SDH_CallBack_TransferFinished) {
            handle->dataCfg->txDataLen += SDH_WriteDataPort(handle->dataCfg);
        }
    }

    /* DMA success interrupt*/
    if (intFlag & SDH_INT_DMA_COMPLETED) {
        if (handle->dataCfg->dataType == SDH_TRANS_DATA_BOOT_CONT) {
            *(handle->dataCfg->rxData) = bootDummy;
        }
    }

    /* Block gap event interrupt */
    if (intFlag & SDH_INT_BLK_GAP_EVENT) {
        if (handle->callBack.SDH_CallBack_BlockGap) {
            handle->callBack.SDH_CallBack_BlockGap(handle->userData);
        }
    }

    /* Re-tuning event interrupt */
    if (intFlag & SDH_INT_RETUNE_EVENT) {
        if (handle->callBack.SDH_CallBack_ReTuning) {
            handle->callBack.SDH_CallBack_ReTuning(handle->userData);
        }
    }

    /* Vendor specified interrupt */
    if (intFlag & (SDH_INT_SPI_ERROR |
                   SDH_INT_AXI_RESP_ERROR |
                   SDH_INT_CPL_TIMEOUT_ERROR |
                   SDH_INT_CRC_STAT_ERROR)) {
        if (handle->callBack.SDH_CallBack_Vendor) {
            handle->callBack.SDH_CallBack_Vendor(handle->userData);
        }
    }

    SDH_ClearIntStatus(intFlag);
}

/****************************************************************************/ /**
 * @brief  SDH interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void SDH_MMC1_IRQHandler(void)
{
    SDH_IntHandler(SDH_IRQn, sdhHandle);
}

/*@} end of group SDH_Public_Functions */

/*@} end of group SDH */

/*@} end of group BL616_Peripheral_Driver */
