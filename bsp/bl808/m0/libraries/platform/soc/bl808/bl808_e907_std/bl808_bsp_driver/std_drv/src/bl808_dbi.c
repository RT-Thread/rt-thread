/**
  ******************************************************************************
  * @file    bl808_dbi.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
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

#include "bl808_dbi.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DBI
 *  @{
 */

/** @defgroup  DBI_Private_Macros
 *  @{
 */

/*@} end of group DBI_Private_Macros */

/** @defgroup  DBI_Private_Types
 *  @{
 */

/*@} end of group DBI_Private_Types */

/** @defgroup  DBI_Private_Variables
 *  @{
 */

/**
 *  @brief DBI interrupt callback function address array
 */
#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type *DBIIntCbfArra[DBI_INT_ALL] = {
    NULL
};
#endif

/*@} end of group DBI_Private_Variables */

/** @defgroup  DBI_Global_Variables
 *  @{
 */

/*@} end of group DBI_Global_Variables */

/** @defgroup  DBI_Private_Fun_Declaration
 *  @{
 */

/*@} end of group DBI_Private_Fun_Declaration */

/** @defgroup  DBI_Private_Functions
 *  @{
 */

/*@} end of group DBI_Private_Functions */

/** @defgroup  DBI_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  DBI interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void DBI_IRQHandler(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DBI_BASE, DBI_INT_STS);

    /* DBI transfer end interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, DBI_END_INT) && !BL_IS_REG_BIT_SET(tmpVal, DBI_CR_DBI_END_MASK)) {
        BL_WR_REG(DBI_BASE, DBI_INT_STS, BL_SET_REG_BIT(tmpVal, DBI_CR_DBI_END_CLR));

        if (DBIIntCbfArra[DBI_INT_END] != NULL) {
            DBIIntCbfArra[DBI_INT_END]();
        }
    }

    /* DBI tx fifo ready interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, DBI_TXF_INT) && !BL_IS_REG_BIT_SET(tmpVal, DBI_CR_DBI_TXF_MASK)) {
        if (DBIIntCbfArra[DBI_INT_TX_FIFO_REQ] != NULL) {
            DBIIntCbfArra[DBI_INT_TX_FIFO_REQ]();
        }
    }

    /* DBI tx fifo ready interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, DBI_FER_INT) && !BL_IS_REG_BIT_SET(tmpVal, DBI_CR_DBI_FER_MASK)) {
        if (DBIIntCbfArra[DBI_INT_FIFO_ERR] != NULL) {
            DBIIntCbfArra[DBI_INT_FIFO_ERR]();
        }
    }
}
#endif

/****************************************************************************/ /**
 * @brief  DBI init
 *
 * @param  dbiCfg: DBI configuration
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type DBI_Init(DBI_CFG_Type *dbiCfg)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DBI_MODE_TYPE(dbiCfg->mode));
    CHECK_PARAM(IS_DBI_PIXEL_FORMAT_TYPE(dbiCfg->pixelFormat));
    CHECK_PARAM(IS_DBI_FIFO_FORMAT_TYPE(dbiCfg->fifoFormat));
    CHECK_PARAM(IS_DBI_SCL_CLK_PHASE_TYPE(dbiCfg->clkPhase));
    CHECK_PARAM(IS_DBI_SCL_CLK_POLARITY_TYPE(dbiCfg->clkPolarity));

    tmpVal = BL_RD_REG(DBI_BASE, DBI_CONFIG);

    /* Select DBI type B or C */
    if (dbiCfg->mode == DBI_TYPE_B) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DBI_CR_DBI_SEL);
    } else if (dbiCfg->mode == DBI_TYPE_C_3_WIRE) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DBI_CR_DBI_SEL);
        tmpVal = BL_SET_REG_BIT(tmpVal, DBI_CR_DBI_TC_3W_MODE);
    } else {
        tmpVal = BL_SET_REG_BIT(tmpVal, DBI_CR_DBI_SEL);
        tmpVal = BL_CLR_REG_BIT(tmpVal, DBI_CR_DBI_TC_3W_MODE);
    }

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_CONT_EN, dbiCfg->continueEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_DMY_EN, dbiCfg->dummyEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_DMY_CNT, dbiCfg->dummyCnt);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_SCL_PH, dbiCfg->clkPhase);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_SCL_POL, dbiCfg->clkPolarity);

    BL_WR_REG(DBI_BASE, DBI_CONFIG, tmpVal);

    /* Set data period */
    DBI_SetPeriod(&(dbiCfg->period));

    /* Set pixel format */
    tmpVal = BL_RD_REG(DBI_BASE, DBI_PIX_CNT);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_PIX_FORMAT, dbiCfg->pixelFormat);
    BL_WR_REG(DBI_BASE, DBI_PIX_CNT, tmpVal);

    /* Set fifo format */
    tmpVal = BL_RD_REG(DBI_BASE, DBI_FIFO_CONFIG_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_FIFO_FORMAT, dbiCfg->fifoFormat);
    BL_WR_REG(DBI_BASE, DBI_FIFO_CONFIG_0, tmpVal);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(DBI_IRQn, DBI_IRQHandler);
#endif

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  DBI command and data configuration
 *
 * @param  cdCfg: Pointer of DBI CD configure type
 *
 * @return None
 *
*******************************************************************************/
void DBI_CDConfig(DBI_CD_CFG_Type *cdCfg)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DBI_DATA_TYPE(cdCfg->dataType));
    CHECK_PARAM(IS_DBI_DATA_DIRECTION_TYPE(cdCfg->dataDir));

    /* Set command and data comfiguration */
    tmpVal = BL_RD_REG(DBI_BASE, DBI_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_CMD_EN, cdCfg->commandEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_CMD, cdCfg->command);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_DAT_EN, cdCfg->dataEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_DAT_TP, cdCfg->dataType);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_DAT_WR, cdCfg->dataDir);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_DAT_BC, cdCfg->dataCnt);
    BL_WR_REG(DBI_BASE, DBI_CONFIG, tmpVal);
    BL_WR_REG(DBI_BASE, DBI_WDATA, cdCfg->data);
}

/****************************************************************************/ /**
 * @brief  DBI enable
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void DBI_Enable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DBI_BASE, DBI_CONFIG);
    BL_WR_REG(DBI_BASE, DBI_CONFIG, BL_SET_REG_BIT(tmpVal, DBI_CR_DBI_EN));
}

/****************************************************************************/ /**
 * @brief  DBI disable
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void DBI_Disable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DBI_BASE, DBI_CONFIG);
    BL_WR_REG(DBI_BASE, DBI_CONFIG, BL_CLR_REG_BIT(tmpVal, DBI_CR_DBI_EN));
}

/****************************************************************************/ /**
 * @brief  DBI enable
 *
 * @param  period: DBI period configuration
 *
 * @return None
 *
*******************************************************************************/
void DBI_SetPeriod(DBI_Period_CFG_Type *period)
{
    uint32_t tmpVal;

    /* Set data period */
    tmpVal = BL_RD_REG(DBI_BASE, DBI_PRD);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_PRD_S, period->startLen);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_PRD_D_PH_0, period->dataPhase0Len);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_PRD_D_PH_1, period->dataPhase1Len);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_PRD_I, period->intervalLen);

    BL_WR_REG(DBI_BASE, DBI_PRD, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DBI set Command
 *
 * @param  Command:  start Command (frist byte)
 * @return None
 *
*******************************************************************************/
void DBI_SetCommand(uint8_t Command )
{
    uint32_t tmpVal;

    /* Set command */
    tmpVal = BL_RD_REG(DBI_BASE, DBI_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_CMD, Command);
    BL_WR_REG(DBI_BASE, DBI_CONFIG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DBI set Command and Data enable signal
 *
 * @param  CommandEn:  DISABLE:No command phase, ENABLE:Command will be sent
 * @param  dataEn:     DISABLE:No data phase,    ENABLE:data will be sent
 * @return None
 *
*******************************************************************************/
void DBI_SetPhaseState(BL_Fun_Type commandEn, BL_Fun_Type dataEn)
{
    uint32_t tmpVal;

    /* Set command */
    tmpVal = BL_RD_REG(DBI_BASE, DBI_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_CMD_EN, commandEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_DAT_EN, dataEn);
    BL_WR_REG(DBI_BASE, DBI_CONFIG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DBI set Data type and count, Automatically change data phase settings
 *
 * @param  datatype:  Data type select
 * @param  dataCount: count of data (Not the size of the data)
 *                    normal data: max 4
 * @return None
 *
*******************************************************************************/
void DBI_SetDataTypeAndCount(DBI_Data_Type dataType, uint32_t dataCount)
{
    uint32_t tmpVal, tmpVal2;

    /* Set dbi config */
    tmpVal = BL_RD_REG(DBI_BASE, DBI_CONFIG);
    /* Set data type */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_DAT_TP, dataType);

    if(!dataCount){
        /* No data phase */
        tmpVal = BL_CLR_REG_BIT(tmpVal, DBI_CR_DBI_DAT_EN);
    }else{
        /* data will be sent */
        tmpVal = BL_SET_REG_BIT(tmpVal, DBI_CR_DBI_DAT_EN);

        if(dataType == DBI_DATA_NORMAL){
            if(dataCount > 4){
                dataCount = 4;
            }
            /* data byte count of normal-data */
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_DAT_BC, dataCount-1);
        }else{
            /* pixel count of pixel-data */
            tmpVal2 = BL_RD_REG(DBI_BASE, DBI_PIX_CNT);
            tmpVal2 = BL_SET_REG_BITS_VAL(tmpVal2, DBI_CR_DBI_PIX_CNT, dataCount-1);
            BL_WR_REG(DBI_BASE, DBI_PIX_CNT, tmpVal2);
        }
    }
    BL_WR_REG(DBI_BASE, DBI_CONFIG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DBI set normal data direction (It only works in normal data)
 *
 * @param  dataDir:  write or read
 * @return None
 *
*******************************************************************************/
void DBI_SetNormalDataDir(DBI_Data_Direction_Type dataDir)
{
    uint32_t tmpVal;
    /* Set dbi config */
    tmpVal = BL_RD_REG(DBI_BASE, DBI_CONFIG);
    /* set normal data direction */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_DAT_WR, dataDir);
    BL_WR_REG(DBI_BASE, DBI_CONFIG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DBI Read Norml-Data from rdata-register
 *
 * @param  dataSize:  size of data (max 4-byte)
 * @param  dataBuff:  buff of data
 * @return None
 *
*******************************************************************************/
void DBI_ReadNormlData(uint8_t dataSize, uint8_t *dataBuff)
{
    if(dataSize > 4){
        dataSize = 4;
    }

    /* get receive data from registers*/
    uint32_t para_data = 0;
    para_data = BL_RD_REG(DBI_BASE, DBI_RDATA);

    /* copy to buff */
    memcpy(dataBuff, &para_data, dataSize);
}

/****************************************************************************/ /**
 * @brief  DBI Write Norml-Data to rdata-register
 *
 * @param  dataSize:  size of data (max 4-byte)
 * @param  dataBuff:  buff of data
 * @return None
 *
*******************************************************************************/
void DBI_WriteNormlData(uint8_t dataSize, uint8_t *dataBuff)
{
    uint32_t para_data = 0;

    if(dataSize > 4){
        dataSize = 4;
    }

    for(uint8_t i=0; i<dataSize; i++){
        ((uint8_t *)(&para_data))[dataSize-i-1] = dataBuff[i];
    }

    BL_WR_REG(DBI_BASE, DBI_WDATA, para_data);
}

/****************************************************************************/ /**
 * @brief  DBI Wirte Data to FIFO.
 *    You should have configured Data byte count(normal or pixel) before,
 *    And the transfer has been started.
 *    note : The sum of data Count must be for the configured Count(normal or pixel),
 *           Before the next transmission, you should wait for send done.
 *
 * @param  wordCount: the WordsCount of data (Not data count)
 * @param  pixelBuff: buff of data
 * @return None
 *
*******************************************************************************/
void DBI_WirteData2FIFO(uint32_t wordCount, uint32_t *dataBuff)
{
    for(uint32_t i = 0; i < wordCount; ){
        if (DBI_GetTxFifoCount() > 0) {
            BL_WR_REG(DBI_BASE, DBI_FIFO_WDATA, dataBuff[i++]);
        }
    }
}

/****************************************************************************/ /**
 * @brief  DBI Calculate the WordCount of data in different pixel formats
 *          You should have configured the FIFO-format before
 * @param  PixelCount: pixel count
 * @return Words Count
 *
*******************************************************************************/
uint32_t DBI_GetWordCountOfPixelData(int32_t PixelCount)
{
    uint32_t wordCount;
    /* get pixel-formats of fifo*/
    DBI_FIFO_Format_Type fifoFormat = BL_GET_REG_BITS_VAL(BL_RD_REG(DBI_BASE, DBI_FIFO_CONFIG_0), DBI_FIFO_FORMAT);

    if(fifoFormat == DBI_FIFO_888_NBGR || fifoFormat == DBI_FIFO_888_NRGB){
        wordCount = PixelCount;
    }else if(fifoFormat == DBI_FIFO_565_BGRBGR || fifoFormat == DBI_FIFO_565_RGBRGB){
        wordCount = (PixelCount + 1) >> 1;
    }else{
        wordCount = (PixelCount * 3 + 3) >> 2;
    }
    return wordCount;
}

/****************************************************************************/ /**
 * @brief  DBI send Command and write normal-data function
 *
 * @param  command: Command to send (if command phase enable)
 * @param  dataSize: write size of NormalData (write max 4)
 * @param  dataBuff: buff of NormalData
 * @return None
 *
*******************************************************************************/
void DBI_SendCmdWithNormalData(uint8_t command, uint8_t dataSize, uint8_t *dataBuff)
{
    /* disable transfer */
    DBI_Disable();

    /* clear fifo and interrupt */
    DBI_IntClear();

    /* set command */
    DBI_SetCommand(command);

    /* set data direction */
    DBI_SetNormalDataDir(DBI_DATA_WRITE);

    /* Data type select, and set data count */
    DBI_SetDataTypeAndCount(DBI_DATA_NORMAL, dataSize);

    /* Fill the data into the register */
    DBI_WriteNormlData(dataSize, dataBuff);

    /* enable transfer */
    DBI_Enable();

    /* Wait transfer end */
    while (DBI_GetIntStatus(DBI_INT_END) != SET) {
    }

    /* clear interrupt */
    DBI_IntClear();
}

/****************************************************************************/ /**
 * @brief  DBI send Command and read normal-data function
 *
 * @param  command: Command to send (if command phase enable)
 * @param  dataSize: read size of NormalData (read max 4 )
 * @param  dataBuff: buff of NormalData
 * @return None
 *
*******************************************************************************/
void DBI_SendCmdAndReadNormalData(uint8_t command, uint8_t dataSize, uint8_t *dataBuff)
{
    /* disable transfer */
    DBI_Disable();

    /* clear interrupt */
    DBI_IntClear();

    /* set command */
    DBI_SetCommand(command);

    /* set data direction */
    DBI_SetNormalDataDir(DBI_DATA_READ);

    /* Data type select, and set data count */
    DBI_SetDataTypeAndCount(DBI_DATA_NORMAL, dataSize);

    /* enable transfer */
    DBI_Enable();

    /* Wait transfer end */
    while (DBI_GetIntStatus(DBI_INT_END) != SET) {
    }

    /* get data */
    DBI_ReadNormlData(dataSize, dataBuff);

    /* clear interrupt */
    DBI_IntClear();
}

/****************************************************************************/ /**
 * @brief  DBI send Command and write pixel-data function
 *
 * @param  command: Command to send (if command phase enable)
 * @param  dataSize: write size of Pixel-Data
 * @param  dataBuff: buff of Pixel-Data
 * @return None
 *
*******************************************************************************/
void DBI_SendCmdWithPixelData(uint8_t command, int32_t PixelCount, uint32_t *pixelBuff)
{
    /* disable transfer */
    DBI_Disable();

    /* clear fifo and interrupt */
    DBI_TxFifoClear();
    DBI_IntClear();

    /* set command */
    DBI_SetCommand(command);

    /* set data direction */
    DBI_SetNormalDataDir(DBI_DATA_WRITE);

    /* Data type select, and set data count */
    DBI_SetDataTypeAndCount(DBI_DATA_PIXEL, PixelCount);

    /* enable transfer */
    DBI_Enable();

    /* get words count */
    uint32_t wordsCount = DBI_GetWordCountOfPixelData(PixelCount);
    /* send data */
    DBI_WirteData2FIFO(wordsCount, pixelBuff);

    /* Wait transfer end */
    while (DBI_GetIntStatus(DBI_INT_END) != SET) {
    }

    /* clear interrupt */
    DBI_IntClear();
}

/****************************************************************************/ /**
 * @brief  Clear tx fifo,overflow/underflow flag and fifo error interrupt will be cleared
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void DBI_TxFifoClear(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DBI_BASE, DBI_FIFO_CONFIG_0);
    tmpVal = BL_SET_REG_BIT(tmpVal, DBI_TX_FIFO_CLR);
    BL_WR_REG(DBI_BASE, DBI_FIFO_CONFIG_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Enable or disable signal of dma interface
 *
 * @param  dmaEn: Enable or disable
 *
 * @return None
 *
*******************************************************************************/
void DBI_SetDMA(BL_Fun_Type dmaEn)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DBI_BASE, DBI_FIFO_CONFIG_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_DMA_TX_EN, dmaEn);
    BL_WR_REG(DBI_BASE, DBI_FIFO_CONFIG_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Set tx fifo threshold
 *
 * @param  threshold: Threshold value
 *
 * @return None
 *
*******************************************************************************/
void DBI_SetTxFifoThreshold(uint8_t threshold)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DBI_BASE, DBI_FIFO_CONFIG_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_TX_FIFO_TH, threshold);
    BL_WR_REG(DBI_BASE, DBI_FIFO_CONFIG_1, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Get tx fifo count value
 *
 * @param  None
 *
 * @return Count value
 *
*******************************************************************************/
uint8_t DBI_GetTxFifoCount(void)
{
    return BL_GET_REG_BITS_VAL(BL_RD_REG(DBI_BASE, DBI_FIFO_CONFIG_1), DBI_TX_FIFO_CNT);
}

/****************************************************************************/ /**
 * @brief  Get interrupt status
 *
 * @param  intType: DBI interrupt type
 *
 * @return Status of interrupt
 *
*******************************************************************************/
BL_Sts_Type DBI_GetIntStatus(DBI_INT_Type intType)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DBI_BASE, DBI_INT_STS);

    if ((tmpVal >> intType & 1) == 1) {
        return SET;
    } else {
        return RESET;
    }
}

/****************************************************************************/ /**
 * @brief  Get tx fifo overflow/underflow status
 *
 * @param  overflow: Select overflow or underflow
 *
 * @return Status of tx fifo
 *
*******************************************************************************/
BL_Sts_Type DBI_GetOverflowStatus(DBI_Overflow_Type overflow)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DBI_OVERFLOW_TYPE(overflow));

    tmpVal = BL_RD_REG(DBI_BASE, DBI_FIFO_CONFIG_0);

    if (overflow == DBI_TX_OVERFLOW) {
        if (BL_IS_REG_BIT_SET(tmpVal, DBI_TX_FIFO_OVERFLOW)) {
            return SET;
        } else {
            return RESET;
        }
    } else {
        if (BL_IS_REG_BIT_SET(tmpVal, DBI_TX_FIFO_UNDERFLOW)) {
            return SET;
        } else {
            return RESET;
        }
    }
}

/****************************************************************************/ /**
 * @brief  Get DBI bus busy status
 *
 * @param  None
 *
 * @return Status of DBI bus
 *
*******************************************************************************/
BL_Sts_Type DBI_GetBusBusyStatus(void)
{
    if (BL_IS_REG_BIT_SET(BL_RD_REG(DBI_BASE, DBI_BUS_BUSY), DBI_STS_DBI_BUS_BUSY)) {
        return SET;
    } else {
        return RESET;
    }
}

/****************************************************************************/ /**
 * @brief  Mask/Unmask the DBI interrupt
 *
 * @param  intType: DBI interrupt type
 * @param  intMask: Mask/Unmask
 *
 * @return None
 *
*******************************************************************************/
void DBI_IntMask(DBI_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DBI_INT_TYPE(intType));

    tmpVal = BL_RD_REG(DBI_BASE, DBI_INT_STS);

    switch (intType) {
        case DBI_INT_END:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_END_MASK, intMask);
            break;

        case DBI_INT_TX_FIFO_REQ:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_TXF_MASK, intMask);
            break;

        case DBI_INT_FIFO_ERR:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_FER_MASK, intMask);
            break;

        case DBI_INT_ALL:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_END_MASK, intMask);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_TXF_MASK, intMask);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DBI_CR_DBI_FER_MASK, intMask);
            break;

        default:
            break;
    }

    BL_WR_REG(DBI_BASE, DBI_INT_STS, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Clear DBI interrupt
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void DBI_IntClear(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DBI_BASE, DBI_INT_STS);
    BL_WR_REG(DBI_BASE, DBI_INT_STS, BL_SET_REG_BIT(tmpVal, DBI_CR_DBI_END_CLR));
}

/****************************************************************************/ /**
 * @brief  Install DBI interrupt callback function
 *
 * @param  intType: DBI interrupt type
 * @param  cbFun: Pointer to interrupt callback function. The type should be void (*fn)(void)
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void DBI_Int_Callback_Install(DBI_INT_Type intType, intCallback_Type *cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_DBI_INT_TYPE(intType));

    DBIIntCbfArra[intType] = cbFun;
}
#endif

/*@} end of group DBI_Public_Functions */

/*@} end of group DBI */

/*@} end of group BL808_Peripheral_Driver */
