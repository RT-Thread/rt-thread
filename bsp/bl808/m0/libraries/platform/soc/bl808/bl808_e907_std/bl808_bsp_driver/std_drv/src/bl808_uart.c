/**
  ******************************************************************************
  * @file    bl808_uart.c
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

#include "bl808_uart.h"
#include "bl808_glb.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  UART
 *  @{
 */

/** @defgroup  UART_Private_Macros
 *  @{
 */
#define UART_TX_TIMEOUT_COUNT (320 * 1000)

/*@} end of group UART_Private_Macros */

/** @defgroup  UART_Private_Types
 *  @{
 */

/*@} end of group UART_Private_Types */

/** @defgroup  UART_Private_Variables
 *  @{
 */
static const uint32_t uartAddr[UART_ID_MAX] = { UART0_BASE, UART1_BASE, UART2_BASE, UART3_BASE };
#if (defined BOOTROM) || (!defined BFLB_USE_HAL_DRIVER)
static intCallback_Type *uartIntCbfArra[UART_ID_MAX][UART_INT_ALL] = {
    { NULL }
};
#endif

/*@} end of group UART_Private_Variables */

/** @defgroup  UART_Global_Variables
 *  @{
 */

/*@} end of group UART_Global_Variables */

/** @defgroup  UART_Private_Fun_Declaration
 *  @{
 */
#if (defined BOOTROM) || (!defined BFLB_USE_HAL_DRIVER)
static void UART_IntHandler(UART_ID_Type uartId);
#endif

/*@} end of group UART_Private_Fun_Declaration */

/** @defgroup  UART_Private_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  UART interrupt common handler function
 *
 * @param  uartId: UART ID type
 *
 * @return None
 *
*******************************************************************************/
#if (defined BOOTROM) || (!defined BFLB_USE_HAL_DRIVER)
static void UART_IntHandler(UART_ID_Type uartId)
{
    uint32_t tmpVal = 0;
    uint32_t maskVal = 0;
    uint32_t UARTx = uartAddr[uartId];

    tmpVal = BL_RD_REG(UARTx, UART_INT_STS);
    maskVal = BL_RD_REG(UARTx, UART_INT_MASK);

    /* Length of uart tx data transfer arrived interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_UTX_END_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_UTX_END_MASK)) {
        BL_WR_REG(UARTx, UART_INT_CLEAR, 1 << UART_CR_UTX_END_CLR_POS);

        if (uartIntCbfArra[uartId][UART_INT_TX_END] != NULL) {
            uartIntCbfArra[uartId][UART_INT_TX_END]();
        }
    }

    /* Length of uart rx data transfer arrived interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_END_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_END_MASK)) {
        BL_WR_REG(UARTx, UART_INT_CLEAR, 1 << UART_CR_URX_END_CLR_POS);

        if (uartIntCbfArra[uartId][UART_INT_RX_END] != NULL) {
            uartIntCbfArra[uartId][UART_INT_RX_END]();
        }
    }

    /* Tx fifo ready interrupt,auto-cleared when data is pushed */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_UTX_FRDY_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_UTX_FRDY_MASK)) {
        if (uartIntCbfArra[uartId][UART_INT_TX_FIFO_REQ] != NULL) {
            uartIntCbfArra[uartId][UART_INT_TX_FIFO_REQ]();
        }
    }

    /* Rx fifo ready interrupt,auto-cleared when data is popped */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_FRDY_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_FRDY_MASK)) {
        if (uartIntCbfArra[uartId][UART_INT_RX_FIFO_REQ] != NULL) {
            uartIntCbfArra[uartId][UART_INT_RX_FIFO_REQ]();
        }
    }

    /* Rx time-out interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_RTO_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_RTO_MASK)) {
        BL_WR_REG(UARTx, UART_INT_CLEAR, 1 << UART_CR_URX_RTO_CLR_POS);

        if (uartIntCbfArra[uartId][UART_INT_RTO] != NULL) {
            uartIntCbfArra[uartId][UART_INT_RTO]();
        }
    }

    /* Rx parity check error interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_PCE_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_PCE_MASK)) {
        BL_WR_REG(UARTx, UART_INT_CLEAR, 1 << UART_CR_URX_PCE_CLR_POS);

        if (uartIntCbfArra[uartId][UART_INT_PCE] != NULL) {
            uartIntCbfArra[uartId][UART_INT_PCE]();
        }
    }

    /* Tx fifo overflow/underflow error interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_UTX_FER_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_UTX_FER_MASK)) {
        if (uartIntCbfArra[uartId][UART_INT_TX_FER] != NULL) {
            uartIntCbfArra[uartId][UART_INT_TX_FER]();
        }
    }

    /* Rx fifo overflow/underflow error interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_FER_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_FER_MASK)) {
        if (uartIntCbfArra[uartId][UART_INT_RX_FER] != NULL) {
            uartIntCbfArra[uartId][UART_INT_RX_FER]();
        }
    }

    /* Rx lin mode sync field error interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_LSE_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_LSE_MASK)) {
        BL_WR_REG(UARTx, UART_INT_CLEAR, 1 << UART_CR_URX_LSE_CLR_POS);

        if (uartIntCbfArra[uartId][UART_INT_LSE] != NULL) {
            uartIntCbfArra[uartId][UART_INT_LSE]();
        }
    }

    /* Rx byte count reached interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_BCR_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_BCR_MASK)) {
        BL_WR_REG(UARTx, UART_INT_CLEAR, 1 << UART_CR_URX_BCR_CLR_POS);

        if (uartIntCbfArra[uartId][UART_INT_BCR] != NULL) {
            uartIntCbfArra[uartId][UART_INT_BCR]();
        }
    }

    /* Rx auto baud rate detection finish interrupt using start bit */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_ADS_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_ADS_MASK)) {
        BL_WR_REG(UARTx, UART_INT_CLEAR, 1 << UART_CR_URX_ADS_CLR_POS);

        if (uartIntCbfArra[uartId][UART_INT_STARTBIT] != NULL) {
            uartIntCbfArra[uartId][UART_INT_STARTBIT]();
        }
    }

    /* Rx auto baud rate detection finish interrupt using codeword 0x55 */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_AD5_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_AD5_MASK)) {
        BL_WR_REG(UARTx, UART_INT_CLEAR, 1 << UART_CR_URX_AD5_CLR_POS);

        if (uartIntCbfArra[uartId][UART_INT_0X55] != NULL) {
            uartIntCbfArra[uartId][UART_INT_0X55]();
        }
    }
}
#endif

/*@} end of group UART_Private_Functions */

/** @defgroup  UART_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  UART set baud rate function
 *
 * @param  uartId: UART ID type
 * @param  baudRate: baudRate need to set
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type UART_SetBaudRate(UART_ID_Type uartId, uint32_t baudRate)
{
    uint32_t uartClk= 0;
    uint32_t fraction = 0;
    uint32_t baudRateDivisor = 0;
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Get uart clk */
    if (uartId == UART0_ID || uartId == UART1_ID || uartId == UART2_ID) {
        uartClk = Clock_Peripheral_Clock_Get(BL_PERIPHERAL_CLOCK_UART0);
    } else if (uartId == UART0_MM_ID) {
        uartClk = Clock_Peripheral_Clock_Get(BL_PERIPHERAL_CLOCK_UART3);
    } else {
        return ERROR;
    }

    /* Cal the baud rate divisor */
    fraction = uartClk * 10 / baudRate % 10;
    baudRateDivisor = uartClk / baudRate;

    if (fraction >= 5) {
        ++baudRateDivisor;
    }

    /* Set the baud rate register value */
    BL_WR_REG(UARTx, UART_BIT_PRD, ((baudRateDivisor - 1) << 0x10) | ((baudRateDivisor - 1) & 0xFFFF));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART initialization function
 *
 * @param  uartId: UART ID type
 * @param  uartCfg: UART configuration structure pointer
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_Init(UART_ID_Type uartId, UART_CFG_Type *uartCfg)
{
    uint32_t tmpValTxCfg = 0;
    uint32_t tmpValRxCfg = 0;
    uint32_t fraction = 0;
    uint32_t baudRateDivisor = 0;
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));
    CHECK_PARAM(IS_UART_PARITY_TYPE(uartCfg->parity));
    CHECK_PARAM(IS_UART_DATABITS_TYPE(uartCfg->dataBits));
    CHECK_PARAM(IS_UART_STOPBITS_TYPE(uartCfg->stopBits));
    CHECK_PARAM(IS_UART_BYTEBITINVERSE_TYPE(uartCfg->byteBitInverse));

    /* Disable clock gate when use UART2 */
    if(uartId == UART2_ID){
        GLB_PER_Clock_UnGate(GLB_AHB_CLOCK_UART2);
    }

    /* Cal the baud rate divisor */
    fraction = uartCfg->uartClk * 10 / uartCfg->baudRate % 10;
    baudRateDivisor = uartCfg->uartClk / uartCfg->baudRate;

    if (fraction >= 5) {
        ++baudRateDivisor;
    }

    /* Set the baud rate register value */
    BL_WR_REG(UARTx, UART_BIT_PRD, ((baudRateDivisor - 1) << 0x10) | ((baudRateDivisor - 1) & 0xFFFF));

    /* Configure parity type */
    tmpValTxCfg = BL_RD_REG(UARTx, UART_UTX_CONFIG);
    tmpValRxCfg = BL_RD_REG(UARTx, UART_URX_CONFIG);

    switch (uartCfg->parity) {
        case UART_PARITY_NONE:
            tmpValTxCfg = BL_CLR_REG_BIT(tmpValTxCfg, UART_CR_UTX_PRT_EN);
            tmpValRxCfg = BL_CLR_REG_BIT(tmpValRxCfg, UART_CR_URX_PRT_EN);
            break;

        case UART_PARITY_ODD:
            tmpValTxCfg = BL_SET_REG_BIT(tmpValTxCfg, UART_CR_UTX_PRT_EN);
            tmpValTxCfg = BL_SET_REG_BIT(tmpValTxCfg, UART_CR_UTX_PRT_SEL);
            tmpValRxCfg = BL_SET_REG_BIT(tmpValRxCfg, UART_CR_URX_PRT_EN);
            tmpValRxCfg = BL_SET_REG_BIT(tmpValRxCfg, UART_CR_URX_PRT_SEL);
            break;

        case UART_PARITY_EVEN:
            tmpValTxCfg = BL_SET_REG_BIT(tmpValTxCfg, UART_CR_UTX_PRT_EN);
            tmpValTxCfg = BL_CLR_REG_BIT(tmpValTxCfg, UART_CR_UTX_PRT_SEL);
            tmpValRxCfg = BL_SET_REG_BIT(tmpValRxCfg, UART_CR_URX_PRT_EN);
            tmpValRxCfg = BL_CLR_REG_BIT(tmpValRxCfg, UART_CR_URX_PRT_SEL);
            break;

        default:
            break;
    }

    /* Configure data bits */
    tmpValTxCfg = BL_SET_REG_BITS_VAL(tmpValTxCfg, UART_CR_UTX_BIT_CNT_D, (uartCfg->dataBits + 4));
    tmpValRxCfg = BL_SET_REG_BITS_VAL(tmpValRxCfg, UART_CR_URX_BIT_CNT_D, (uartCfg->dataBits + 4));

    /* Configure tx stop bits */
    tmpValTxCfg = BL_SET_REG_BITS_VAL(tmpValTxCfg, UART_CR_UTX_BIT_CNT_P, uartCfg->stopBits);

    /* Configure tx cts flow control function */
    tmpValTxCfg = BL_SET_REG_BITS_VAL(tmpValTxCfg, UART_CR_UTX_CTS_EN, uartCfg->ctsFlowControl);

    /* Configure rx input de-glitch function */
    tmpValRxCfg = BL_SET_REG_BITS_VAL(tmpValRxCfg, UART_CR_URX_DEG_EN, uartCfg->rxDeglitch);

    /* Configure tx lin mode function */
    tmpValTxCfg = BL_SET_REG_BITS_VAL(tmpValTxCfg, UART_CR_UTX_LIN_EN, uartCfg->txLinMode);

    /* Configure rx lin mode function */
    tmpValRxCfg = BL_SET_REG_BITS_VAL(tmpValRxCfg, UART_CR_URX_LIN_EN, uartCfg->rxLinMode);

    /* Set tx break bit count for lin protocol */
    tmpValTxCfg = BL_SET_REG_BITS_VAL(tmpValTxCfg, UART_CR_UTX_BIT_CNT_B, uartCfg->txBreakBitCnt);

    /* Write back */
    BL_WR_REG(UARTx, UART_UTX_CONFIG, tmpValTxCfg);
    BL_WR_REG(UARTx, UART_URX_CONFIG, tmpValRxCfg);

    /* Configure LSB-first or MSB-first */
    tmpValTxCfg = BL_RD_REG(UARTx, UART_DATA_CONFIG);

    if (UART_MSB_FIRST == uartCfg->byteBitInverse) {
        tmpValTxCfg = BL_SET_REG_BIT(tmpValTxCfg, UART_CR_UART_BIT_INV);
    } else {
        tmpValTxCfg = BL_CLR_REG_BIT(tmpValTxCfg, UART_CR_UART_BIT_INV);
    }

    BL_WR_REG(UARTx, UART_DATA_CONFIG, tmpValTxCfg);

    tmpValTxCfg = BL_RD_REG(UARTx, UART_SW_MODE);
    /* Configure rx rts output SW control mode */
    tmpValTxCfg = BL_SET_REG_BITS_VAL(tmpValTxCfg, UART_CR_URX_RTS_SW_MODE, uartCfg->rtsSoftwareControl);
    /* Configure tx output SW control mode */
    tmpValTxCfg = BL_SET_REG_BITS_VAL(tmpValTxCfg, UART_CR_UTX_TXD_SW_MODE, uartCfg->txSoftwareControl);
    BL_WR_REG(UARTx, UART_SW_MODE, tmpValTxCfg);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(UART0_IRQn, UART0_IRQHandler);
    Interrupt_Handler_Register(UART1_IRQn, UART1_IRQHandler);
    Interrupt_Handler_Register(UART2_IRQn, UART2_IRQHandler);
    Interrupt_Handler_Register(UART3_IRQn, UART3_IRQHandler);
#endif
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART set default value of all registers function
 *
 * @param  uartId: UART ID type
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_DeInit(UART_ID_Type uartId)
{
    switch(uartId){
        case UART0_ID:
            GLB_AHB_MCU_Software_Reset(GLB_AHB_MCU_SW_UART0);
            break;
        case UART1_ID:
            GLB_AHB_MCU_Software_Reset(GLB_AHB_MCU_SW_UART1);
            break;
        case UART2_ID:
            GLB_AHB_MCU_Software_Reset(GLB_AHB_MCU_SW_UART2);
            break;
        case UART0_MM_ID:
            GLB_AHB_DSP_Software_Reset(GLB_AHB_DSP_SW_SWRST_UART0);
            break;
        default:
            break;
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART configure fifo function
 *
 * @param  uartId: UART ID type
 * @param  fifoCfg: FIFO configuration structure pointer
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_FifoConfig(UART_ID_Type uartId, UART_FifoCfg_Type *fifoCfg)
{
    uint32_t tmpVal = 0;
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Deal with uart fifo configure register */
    tmpVal = BL_RD_REG(UARTx, UART_FIFO_CONFIG_1);
    /* Configure dma tx fifo threshold */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, UART_TX_FIFO_TH, fifoCfg->txFifoDmaThreshold);
    /* Configure dma rx fifo threshold */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, UART_RX_FIFO_TH, fifoCfg->rxFifoDmaThreshold);
    /* Write back */
    BL_WR_REG(UARTx, UART_FIFO_CONFIG_1, tmpVal);

    /* Enable or disable uart fifo dma function */
    tmpVal = BL_RD_REG(UARTx, UART_FIFO_CONFIG_0);

    if (ENABLE == fifoCfg->txFifoDmaEnable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, UART_DMA_TX_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, UART_DMA_TX_EN);
    }

    if (ENABLE == fifoCfg->rxFifoDmaEnable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, UART_DMA_RX_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, UART_DMA_RX_EN);
    }

    BL_WR_REG(UARTx, UART_FIFO_CONFIG_0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART configure infra function
 *
 * @param  uartId: UART ID type
 * @param  irCfg: IR configuration structure pointer
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_IrConfig(UART_ID_Type uartId, UART_IrCfg_Type *irCfg)
{
    uint32_t tmpVal = 0;
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Configure tx ir mode */
    tmpVal = BL_RD_REG(UARTx, UART_UTX_CONFIG);

    if (ENABLE == irCfg->txIrEnable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, UART_CR_UTX_IR_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, UART_CR_UTX_IR_EN);
    }

    if (ENABLE == irCfg->txIrInverse) {
        tmpVal = BL_SET_REG_BIT(tmpVal, UART_CR_UTX_IR_INV);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, UART_CR_UTX_IR_INV);
    }

    BL_WR_REG(UARTx, UART_UTX_CONFIG, tmpVal);

    /* Configure rx ir mode */
    tmpVal = BL_RD_REG(UARTx, UART_URX_CONFIG);

    if (ENABLE == irCfg->rxIrEnable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, UART_CR_URX_IR_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, UART_CR_URX_IR_EN);
    }

    if (ENABLE == irCfg->rxIrInverse) {
        tmpVal = BL_SET_REG_BIT(tmpVal, UART_CR_URX_IR_INV);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, UART_CR_URX_IR_INV);
    }

    BL_WR_REG(UARTx, UART_URX_CONFIG, tmpVal);

    /* Configure tx ir pulse start and stop position */
    BL_WR_REG(UARTx, UART_UTX_IR_POSITION, irCfg->txIrPulseStop << 0x10 | irCfg->txIrPulseStart);

    /* Configure rx ir pulse start position */
    BL_WR_REG(UARTx, UART_URX_IR_POSITION, irCfg->rxIrPulseStart);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Enable UART
 *
 * @param  uartId: UART ID type
 * @param  direct: UART direction type
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_Enable(UART_ID_Type uartId, UART_Direction_Type direct)
{
    uint32_t tmpVal = 0;
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));
    CHECK_PARAM(IS_UART_DIRECTION_TYPE(direct));

    if (direct == UART_TX || direct == UART_TXRX) {
        /* Enable UART tx unit */
        tmpVal = BL_RD_REG(UARTx, UART_UTX_CONFIG);
        BL_WR_REG(UARTx, UART_UTX_CONFIG, BL_SET_REG_BIT(tmpVal, UART_CR_UTX_EN));
    }

    if (direct == UART_RX || direct == UART_TXRX) {
        /* Enable UART rx unit */
        tmpVal = BL_RD_REG(UARTx, UART_URX_CONFIG);
        BL_WR_REG(UARTx, UART_URX_CONFIG, BL_SET_REG_BIT(tmpVal, UART_CR_URX_EN));
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Disable UART
 *
 * @param  uartId: UART ID type
 * @param  direct: UART direction type
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_Disable(UART_ID_Type uartId, UART_Direction_Type direct)
{
    uint32_t tmpVal = 0;
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));
    CHECK_PARAM(IS_UART_DIRECTION_TYPE(direct));

    if (direct == UART_TX || direct == UART_TXRX) {
        /* Disable UART tx unit */
        tmpVal = BL_RD_REG(UARTx, UART_UTX_CONFIG);
        BL_WR_REG(UARTx, UART_UTX_CONFIG, BL_CLR_REG_BIT(tmpVal, UART_CR_UTX_EN));
    }

    if (direct == UART_RX || direct == UART_TXRX) {
        /* Disable UART rx unit */
        tmpVal = BL_RD_REG(UARTx, UART_URX_CONFIG);
        BL_WR_REG(UARTx, UART_URX_CONFIG, BL_CLR_REG_BIT(tmpVal, UART_CR_URX_EN));
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART set length of tx data transfer,tx end interrupt will assert when this length is
 *         reached
 *
 * @param  uartId: UART ID type
 * @param  length: Length of data (unit:character/byte)
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_SetTxDataLength(UART_ID_Type uartId, uint16_t length)
{
    uint32_t tmpVal = 0;
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Set length */
    tmpVal = BL_RD_REG(UARTx, UART_UTX_CONFIG);
    BL_WR_REG(UARTx, UART_UTX_CONFIG, BL_SET_REG_BITS_VAL(tmpVal, UART_CR_UTX_LEN, length - 1));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART set length of rx data transfer,rx end interrupt will assert when this length is
 *         reached
 *
 * @param  uartId: UART ID type
 * @param  length: Length of data (unit:character/byte)
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_SetRxDataLength(UART_ID_Type uartId, uint16_t length)
{
    uint32_t tmpVal = 0;
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Set length */
    tmpVal = BL_RD_REG(UARTx, UART_URX_CONFIG);
    BL_WR_REG(UARTx, UART_URX_CONFIG, BL_SET_REG_BITS_VAL(tmpVal, UART_CR_URX_LEN, length - 1));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART set rx time-out value for triggering RTO interrupt
 *
 * @param  uartId: UART ID type
 * @param  time: Time-out value (unit:bit time)
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_SetRxTimeoutValue(UART_ID_Type uartId, uint8_t time)
{
    uint32_t UARTx = uartAddr[uartId];
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Set time-out value */
    tmpVal = BL_RD_REG(UARTx, UART_URX_RTO_TIMER);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, UART_CR_URX_RTO_VALUE, time - 1);
    BL_WR_REG(UARTx, UART_URX_RTO_TIMER, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART set byte count value for bcr interrupt
 *
 * @param  uartId: UART ID type
 * @param  count: Byte count
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_SetRxByteCount(UART_ID_Type uartId, uint16_t count)
{
    uint32_t UARTx = uartAddr[uartId];
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Set count value */
    tmpVal = BL_RD_REG(UARTx, UART_URX_BCR_INT_CFG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, UART_CR_URX_BCR_VALUE, count);
    BL_WR_REG(UARTx, UART_URX_BCR_INT_CFG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART set de-glitch function cycle count value
 *
 * @param  uartId: UART ID type
 * @param  deglitchCnt: De-glitch function cycle count
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_SetDeglitchCount(UART_ID_Type uartId, uint8_t deglitchCnt)
{
    uint32_t UARTx = uartAddr[uartId];
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Set count value */
    tmpVal = BL_RD_REG(UARTx, UART_URX_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, UART_CR_URX_DEG_CNT, deglitchCnt);
    BL_WR_REG(UARTx, UART_URX_CONFIG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART set tx and rx baudrate according to auto baudrate detection value
 *
 * @param  uartId: UART ID type
 * @param  autoBaudDet: Choose detection value using codeword 0x55 or start bit
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_ApplyAbrResult(UART_ID_Type uartId, UART_AutoBaudDetection_Type autoBaudDet)
{
    uint32_t UARTx = uartAddr[uartId];
    uint16_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Get detection value */
    tmpVal = UART_GetAutoBaudCount(uartId, autoBaudDet);

    /* Set tx baudrate */
    BL_WR_REG(UARTx, UART_BIT_PRD, tmpVal << 0x10 | tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART set rx rts output software control value
 *
 * @param  uartId: UART ID type
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_SetRtsValue(UART_ID_Type uartId)
{
    uint32_t UARTx = uartAddr[uartId];
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Rts set 1*/
    tmpVal = BL_RD_REG(UARTx, UART_SW_MODE);
    BL_WR_REG(UARTx, UART_SW_MODE, BL_SET_REG_BIT(tmpVal, UART_CR_URX_RTS_SW_VAL));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART clear rx rts output software control value
 *
 * @param  uartId: UART ID type
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_ClrRtsValue(UART_ID_Type uartId)
{
    uint32_t UARTx = uartAddr[uartId];
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Rts clear 0 */
    tmpVal = BL_RD_REG(UARTx, UART_SW_MODE);
    BL_WR_REG(UARTx, UART_SW_MODE, BL_CLR_REG_BIT(tmpVal, UART_CR_URX_RTS_SW_VAL));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART set tx output software control value
 *
 * @param  uartId: UART ID type
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_SetTxValue(UART_ID_Type uartId)
{
    uint32_t UARTx = uartAddr[uartId];
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Tx set 1*/
    tmpVal = BL_RD_REG(UARTx, UART_SW_MODE);
    BL_WR_REG(UARTx, UART_SW_MODE, BL_SET_REG_BIT(tmpVal, UART_CR_UTX_TXD_SW_VAL));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART clear tx output software control value
 *
 * @param  uartId: UART ID type
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_ClrTxValue(UART_ID_Type uartId)
{
    uint32_t UARTx = uartAddr[uartId];
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Rts clear 0 */
    tmpVal = BL_RD_REG(UARTx, UART_SW_MODE);
    BL_WR_REG(UARTx, UART_SW_MODE, BL_CLR_REG_BIT(tmpVal, UART_CR_UTX_TXD_SW_VAL));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART configure tx free run mode function
 *
 * @param  uartId: UART ID type
 * @param  txFreeRun: Enable or disable tx free run mode
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_TxFreeRun(UART_ID_Type uartId, BL_Fun_Type txFreeRun)
{
    uint32_t tmpVal = 0;
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Enable or disable tx free run mode */
    tmpVal = BL_RD_REG(UARTx, UART_UTX_CONFIG);

    if (ENABLE == txFreeRun) {
        BL_WR_REG(UARTx, UART_UTX_CONFIG, BL_SET_REG_BIT(tmpVal, UART_CR_UTX_FRM_EN));
    } else {
        BL_WR_REG(UARTx, UART_UTX_CONFIG, BL_CLR_REG_BIT(tmpVal, UART_CR_UTX_FRM_EN));
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART configure auto baud rate detection function
 *
 * @param  uartId: UART ID type
 * @param  autoBaud: Enable or disable auto function
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_AutoBaudDetection(UART_ID_Type uartId, BL_Fun_Type autoBaud)
{
    uint32_t tmpVal = 0;
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Enable or disable auto baud rate detection function */
    tmpVal = BL_RD_REG(UARTx, UART_URX_CONFIG);

    if (ENABLE == autoBaud) {
        BL_WR_REG(UARTx, UART_URX_CONFIG, BL_SET_REG_BIT(tmpVal, UART_CR_URX_ABR_EN));
    } else {
        BL_WR_REG(UARTx, UART_URX_CONFIG, BL_CLR_REG_BIT(tmpVal, UART_CR_URX_ABR_EN));
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART auto baud rate detection pulse width allowable error for using codeword 0x55
 *
 * @param  uartId: UART ID type
 * @param  allowableError: Pulse width allowable error
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_SetAllowableError0X55(UART_ID_Type uartId, uint8_t allowableError)
{
    uint32_t tmpVal = 0;
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameter */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    tmpVal = BL_RD_REG(UARTx, UART_URX_ABR_PW_TOL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, UART_CR_URX_ABR_PW_TOL, allowableError);
    BL_WR_REG(UARTx, UART_URX_ABR_PW_TOL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART get bit width of auto baud rate detection for using codeword 0x55
 *
 * @param  uartId: UART ID type
 * @param  width: Buffer to save bit width, length:8
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_GetBitWidth0X55(UART_ID_Type uartId, uint16_t *width)
{
    uint32_t i;
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameter */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    for (i = 0; i < 4; i++) {
        width[2 * i] = (uint16_t)BL_RD_WORD(UARTx + UART_URX_ABR_PRD_B01_OFFSET + 4 * i);
        width[2 * i + 1] = (uint16_t)(BL_RD_WORD(UARTx + UART_URX_ABR_PRD_B01_OFFSET + 4 * i) >> 16);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART set RS-485 trans ceiver mode
 *
 * @param  uartId: UART ID type
 * @param  enable: Enable or disable RS-485 mode
 * @param  polarity: Set DE polarity, active-low or active-high
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_SetRS485(UART_ID_Type uartId, BL_Fun_Type enable, UART_RS485Polarity_Type polarity)
{
    uint32_t tmpVal;
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameter */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    tmpVal = BL_RD_REG(UARTx, UART_UTX_RS485_CFG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, UART_CR_UTX_RS485_EN, enable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, UART_CR_UTX_RS485_POL, polarity);
    BL_WR_REG(UARTx, UART_UTX_RS485_CFG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART tx fifo clear
 *
 * @param  uartId: UART ID type
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_TxFifoClear(UART_ID_Type uartId)
{
    uint32_t tmpVal = 0;
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameter */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Clear tx fifo */
    tmpVal = BL_RD_REG(UARTx, UART_FIFO_CONFIG_0);
    BL_WR_REG(UARTx, UART_FIFO_CONFIG_0, BL_SET_REG_BIT(tmpVal, UART_TX_FIFO_CLR));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART rx fifo clear
 *
 * @param  uartId: UART ID type
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_RxFifoClear(UART_ID_Type uartId)
{
    uint32_t tmpVal = 0;
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameter */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Clear rx fifo */
    tmpVal = BL_RD_REG(UARTx, UART_FIFO_CONFIG_0);
    BL_WR_REG(UARTx, UART_FIFO_CONFIG_0, BL_SET_REG_BIT(tmpVal, UART_RX_FIFO_CLR));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART mask or unmask certain or all interrupt
 *
 * @param  uartId: UART ID type
 * @param  intType: UART interrupt type
 * @param  intMask: UART interrupt mask value( MASK:disbale interrupt,UNMASK:enable interrupt )
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_IntMask(UART_ID_Type uartId, UART_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal;
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));
    CHECK_PARAM(IS_UART_INT_TYPE(intType));
    CHECK_PARAM(IS_BL_MASK_TYPE(intMask));

    tmpVal = BL_RD_REG(UARTx, UART_INT_MASK);

    /* Mask or unmask certain or all interrupt */
    if (UART_INT_ALL == intType) {
        if (MASK == intMask) {
            tmpVal |= 0xfff;
        } else {
            tmpVal &= 0;
        }
    } else {
        if (MASK == intMask) {
            tmpVal |= 1 << intType;
        } else {
            tmpVal &= ~(1 << intType);
        }
    }

    /* Write back */
    BL_WR_REG(UARTx, UART_INT_MASK, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART clear certain or all interrupt
 *
 * @param  uartId: UART ID type
 * @param  intType: UART interrupt type
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_IntClear(UART_ID_Type uartId, UART_INT_Type intType)
{
    uint32_t tmpVal;
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));
    CHECK_PARAM(IS_UART_INT_TYPE(intType));

    tmpVal = BL_RD_REG(UARTx, UART_INT_CLEAR);

    /* Clear certain or all interrupt */
    if (UART_INT_ALL == intType) {
        tmpVal |= 0xfff;
    } else {
        tmpVal |= 1 << intType;
    }

    /* Write back */
    BL_WR_REG(UARTx, UART_INT_CLEAR, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Install uart interrupt callback function
 *
 * @param  uartId: UART ID type
 * @param  intType: UART interrupt type
 * @param  cbFun: Pointer to interrupt callback function. The type should be void (*fn)(void)
 *
 * @return SUCCESS
 *
*******************************************************************************/
#if (defined BOOTROM) || (!defined BFLB_USE_HAL_DRIVER)
BL_Err_Type UART_Int_Callback_Install(UART_ID_Type uartId, UART_INT_Type intType, intCallback_Type *cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));
    CHECK_PARAM(IS_UART_INT_TYPE(intType));

    uartIntCbfArra[uartId][intType] = cbFun;

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  UART send data to tx fifo
 *
 * @param  uartId: UART ID type
 * @param  data: The data to be send
 * @param  len: The length of the send buffer
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_SendData(UART_ID_Type uartId, uint8_t *data, uint32_t len)
{
    uint32_t txLen = 0;
    uint32_t UARTx = uartAddr[uartId];
    uint32_t timeoutCnt = UART_TX_TIMEOUT_COUNT;

    /* Check the parameter */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Send data */
    while (txLen < len) {
        if (UART_GetTxFifoCount(uartId) > 0) {
            BL_WR_BYTE(UARTx + UART_FIFO_WDATA_OFFSET, data[txLen++]);
            timeoutCnt = UART_TX_TIMEOUT_COUNT;
        } else {
            timeoutCnt--;

            if (timeoutCnt == 0) {
                return TIMEOUT;
            }
        }
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART send data to tx fifo in block mode
 *
 * @param  uartId: UART ID type
 * @param  data: The data to be send
 * @param  len: The length of the send buffer
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_SendDataBlock(UART_ID_Type uartId, uint8_t *data, uint32_t len)
{
    uint32_t txLen = 0;
    uint32_t UARTx = uartAddr[uartId];
    uint32_t timeoutCnt = UART_TX_TIMEOUT_COUNT;

    /* Check the parameter */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Send data */
    while (txLen < len) {
        if (UART_GetTxFifoCount(uartId) > 0) {
            BL_WR_BYTE(UARTx + UART_FIFO_WDATA_OFFSET, data[txLen++]);
            timeoutCnt = UART_TX_TIMEOUT_COUNT;
        } else {
            timeoutCnt--;

            if (timeoutCnt == 0) {
                return TIMEOUT;
            }
        }
    }

    timeoutCnt = UART_TX_TIMEOUT_COUNT;

    while (UART_GetTxBusBusyStatus(uartId) == SET) {
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  UART receive data from rx fifo
 *
 * @param  uartId: UART ID type
 * @param  data: The receive data buffer
 * @param  maxLen: The max length of the buffer
 *
 * @return The length of the received buffer
 *
*******************************************************************************/
uint32_t UART_ReceiveData(UART_ID_Type uartId, uint8_t *data, uint32_t maxLen)
{
    uint32_t rxLen = 0;
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameter */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Receive data */
    while (rxLen < maxLen && UART_GetRxFifoCount(uartId) > 0) {
        data[rxLen++] = BL_RD_BYTE(UARTx + UART_FIFO_RDATA_OFFSET);
    }

    return rxLen;
}

/****************************************************************************/ /**
 * @brief  UART get auto baud count value
 *
 * @param  uartId: UART ID type
 * @param  autoBaudDet: Detection using codeword 0x55 or start bit
 *
 * @return Bit period of auto baudrate detection
 *
*******************************************************************************/
uint16_t UART_GetAutoBaudCount(UART_ID_Type uartId, UART_AutoBaudDetection_Type autoBaudDet)
{
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameter */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));
    CHECK_PARAM(IS_UART_AUTOBAUDDETECTION_TYPE(autoBaudDet));

    /* Select 0x55 or start bit detection value */
    if (UART_AUTOBAUD_0X55 == autoBaudDet) {
        return BL_RD_REG(UARTx, UART_STS_URX_ABR_PRD) >> 0x10 & 0xffff;
    } else {
        return BL_RD_REG(UARTx, UART_STS_URX_ABR_PRD) & 0xffff;
    }
}

/****************************************************************************/ /**
 * @brief  UART get rx current byte count value
 *
 * @param  uartId: UART ID type
 *
 * @return Rx byte count value
 *
*******************************************************************************/
uint16_t UART_GetRxByteCount(UART_ID_Type uartId)
{
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameter */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    return BL_GET_REG_BITS_VAL(BL_RD_REG(UARTx, UART_URX_BCR_INT_CFG), UART_STS_URX_BCR_COUNT);
}

/****************************************************************************/ /**
 * @brief  UART get tx fifo unoccupied count value
 *
 * @param  uartId: UART ID type
 *
 * @return Tx fifo unoccupied count value
 *
*******************************************************************************/
uint8_t UART_GetTxFifoCount(UART_ID_Type uartId)
{
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameter */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    return BL_GET_REG_BITS_VAL(BL_RD_REG(UARTx, UART_FIFO_CONFIG_1), UART_TX_FIFO_CNT);
}

/****************************************************************************/ /**
 * @brief  UART get rx fifo occupied count value
 *
 * @param  uartId: UART ID type
 *
 * @return Rx fifo occupied count value
 *
*******************************************************************************/
uint8_t UART_GetRxFifoCount(UART_ID_Type uartId)
{
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameter */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    return BL_GET_REG_BITS_VAL(BL_RD_REG(UARTx, UART_FIFO_CONFIG_1), UART_RX_FIFO_CNT);
}

/****************************************************************************/ /**
 * @brief  Get uart interrupt status
 *
 * @param  uartId: UART ID type
 * @param  intType: UART interrupt type
 *
 * @return Status of interrupt
 *
*******************************************************************************/
BL_Sts_Type UART_GetIntStatus(UART_ID_Type uartId, UART_INT_Type intType)
{
    uint32_t tmpVal;
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));
    CHECK_PARAM(IS_UART_INT_TYPE(intType));

    /* Get certain or all interrupt status */
    tmpVal = BL_RD_REG(UARTx, UART_INT_STS);

    if (UART_INT_ALL == intType) {
        if ((tmpVal & 0xfff) != 0) {
            return SET;
        } else {
            return RESET;
        }
    } else {
        if ((tmpVal & (1U << intType)) != 0) {
            return SET;
        } else {
            return RESET;
        }
    }
}

/****************************************************************************/ /**
 * @brief  Get indicator of uart tx bus busy
 *
 * @param  uartId: UART ID type
 *
 * @return Status of tx bus
 *
*******************************************************************************/
BL_Sts_Type UART_GetTxBusBusyStatus(UART_ID_Type uartId)
{
    uint32_t tmpVal;
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Get tx bus busy status */
    tmpVal = BL_RD_REG(UARTx, UART_STATUS);

    if (BL_IS_REG_BIT_SET(tmpVal, UART_STS_UTX_BUS_BUSY)) {
        return SET;
    } else {
        return RESET;
    }
}

/****************************************************************************/ /**
 * @brief  Get indicator of uart rx bus busy
 *
 * @param  uartId: UART ID type
 *
 * @return Status of rx bus
 *
*******************************************************************************/
BL_Sts_Type UART_GetRxBusBusyStatus(UART_ID_Type uartId)
{
    uint32_t tmpVal;
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Get rx bus busy status */
    tmpVal = BL_RD_REG(UARTx, UART_STATUS);

    if (BL_IS_REG_BIT_SET(tmpVal, UART_STS_URX_BUS_BUSY)) {
        return SET;
    } else {
        return RESET;
    }
}

/****************************************************************************/ /**
 * @brief  Get tx/rx fifo overflow or underflow status
 *
 * @param  uartId: UART ID type
 * @param  overflow: Select tx/rx overflow or underflow
 *
 * @return Status of tx/rx fifo
 *
*******************************************************************************/
BL_Sts_Type UART_GetOverflowStatus(UART_ID_Type uartId, UART_Overflow_Type overflow)
{
    uint32_t tmpVal;
    uint32_t UARTx = uartAddr[uartId];

    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));
    CHECK_PARAM(IS_UART_OVERFLOW_TYPE(overflow));

    /* Get tx/rx fifo overflow or underflow status */
    tmpVal = BL_RD_REG(UARTx, UART_FIFO_CONFIG_0);

    if ((tmpVal & (1U << (overflow + 4))) != 0) {
        return SET;
    } else {
        return RESET;
    }
}

/****************************************************************************/ /**
 * @brief  UART0 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#if (defined BOOTROM) || (!defined BFLB_USE_HAL_DRIVER)
void UART0_IRQHandler(void)
{
    UART_IntHandler(UART0_ID);
}
#endif

/****************************************************************************/ /**
 * @brief  UART1 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#if (defined BOOTROM) || (!defined BFLB_USE_HAL_DRIVER)
void UART1_IRQHandler(void)
{
    UART_IntHandler(UART1_ID);
}
#endif

/****************************************************************************/ /**
 * @brief  UART2 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void UART2_IRQHandler(void)
{
    UART_IntHandler(UART2_ID);
}
#endif

/****************************************************************************/ /**
 * @brief  UART3 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void UART3_IRQHandler(void)
{
    UART_IntHandler(UART0_MM_ID);
}
#endif

/*@} end of group UART_Public_Functions */

/*@} end of group UART */

/*@} end of group BL808_Peripheral_Driver */
