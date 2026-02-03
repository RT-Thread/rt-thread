/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g4fr_qspi.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32g4fr_qspi.h"

/**
 * @brief  Control QSPI function switch.
 * @param cmd select enable or disable QSPI.
 */
void QSPI_Cmd(bool cmd)
{
    if (cmd != DISABLE)
    {
        QSPI->SLAVE_EN = QSPI_SLAVE_EN_SEN;
        QSPI->EN       = QSPI_EN_QEN;
    }
    else
    {
        QSPI->SLAVE_EN &= ~QSPI_SLAVE_EN_SEN;
        QSPI->EN &= ~QSPI_EN_QEN;
    }
}
/**
 * @brief  Control QSPI XIP function switch.
 * @param cmd select enable or disable QSPI XIP.
 */
void QSPI_XIP_Cmd(bool cmd)
{
    if (cmd != DISABLE)
    {
        QSPI->XIP_SLAVE_EN = QSPI_XIP_SLAVE_EN_SEN;
    }
    else
    {
        QSPI->XIP_SLAVE_EN &= ~QSPI_XIP_SLAVE_EN_SEN;
    }
}
/**
 * @brief  Deinitializes the QSPI peripheral registers to its default reset values.
 */
void QSPI_DeInit(void)
{
    RCC_EnableAHBPeriphReset(RCC_AHB_PERIPH_QSPI, ENABLE);
    RCC_EnableAHBPeriphReset(RCC_AHB_PERIPH_QSPI, DISABLE);
}
/**
 * @brief  Merge configuration from the buffer of QSPI para struct, then write it into related registers.
 * @param  QSPI_InitStruct pointer to buffer of QSPI para struct.
 */
void QspiInitConfig(QSPI_InitType* QSPI_InitStruct)
{
    uint32_t tmpregister = 0;

    /* Check the parameters */
    assert_param(IS_QSPI_SPI_FRF(QSPI_InitStruct->SPI_FRF));
    assert_param(IS_QSPI_CFS(QSPI_InitStruct->CFS));
    assert_param(IS_QSPI_SSTE(QSPI_InitStruct->SSTE));
    assert_param(IS_QSPI_TMOD(QSPI_InitStruct->TMOD));
    assert_param(IS_QSPI_SCPOL(QSPI_InitStruct->SCPOL));
    assert_param(IS_QSPI_SCPH(QSPI_InitStruct->SCPH));
    assert_param(IS_QSPI_FRF(QSPI_InitStruct->FRF));
    assert_param(IS_QSPI_DFS(QSPI_InitStruct->DFS));
    assert_param(IS_QSPI_MWMOD(QSPI_InitStruct->MWMOD));
    assert_param(IS_QSPI_MC_DIR(QSPI_InitStruct->MC_DIR));
    assert_param(IS_QSPI_MHS_EN(QSPI_InitStruct->MHS_EN));
    assert_param(IS_QSPI_SES(QSPI_InitStruct->SES));
    assert_param(IS_QSPI_SDCN(QSPI_InitStruct->SDCN));

    assert_param(IS_QSPI_ENH_CLK_STRETCH_EN(QSPI_InitStruct->ENHANCED_CLK_STRETCH_EN));
    assert_param(IS_QSPI_ENH_INST_DDR_EN(QSPI_InitStruct->ENHANCED_INST_DDR_EN));
    assert_param(IS_QSPI_ENH_SPI_DDR_EN(QSPI_InitStruct->ENHANCED_SPI_DDR_EN));
    assert_param(IS_QSPI_ENH_WAIT_CYCLES(QSPI_InitStruct->ENHANCED_WAIT_CYCLES));
    assert_param(IS_QSPI_ENH_INST_L(QSPI_InitStruct->ENHANCED_INST_L));
    assert_param(IS_QSPI_ENH_ADDR_LEN(QSPI_InitStruct->ENHANCED_ADDR_LEN));
    assert_param(IS_QSPI_ENH_TRANS_TYPE(QSPI_InitStruct->ENHANCED_TRANS_TYPE));

    assert_param(IS_QSPI_XIP_MBL(QSPI_InitStruct->XIP_MBL));
    assert_param(IS_QSPI_XIP_CT_EN(QSPI_InitStruct->XIP_CT_EN));
    assert_param(IS_QSPI_XIP_INST_EN(QSPI_InitStruct->XIP_INST_EN));
    assert_param(IS_QSPI_INST_DDR_EN(QSPI_InitStruct->XIP_INST_DDR_EN));
    assert_param(IS_QSPI_DDR_EN(QSPI_InitStruct->XIP_DDR_EN));
    assert_param(IS_QSPI_XIP_DFS_HC(QSPI_InitStruct->XIP_DFS_HC));
    assert_param(IS_QSPI_XIP_WAIT_CYCLES(QSPI_InitStruct->XIP_WAIT_CYCLES));
    assert_param(IS_QSPI_XIP_MD_BIT_EN(QSPI_InitStruct->XIP_MD_BITS_EN));
    assert_param(IS_QSPI_XIP_INST_L(QSPI_InitStruct->XIP_INST_L));
    assert_param(IS_QSPI_XIP_ADDR_LEN(QSPI_InitStruct->XIP_ADDR_LEN));
    assert_param(IS_QSPI_XIP_TRANS_TYPE(QSPI_InitStruct->XIP_TRANS_TYPE));
    assert_param(IS_QSPI_XIP_FRF(QSPI_InitStruct->XIP_FRF));

    assert_param(IS_QSPI_XIP_MODE(QSPI_InitStruct->XIP_MD_BITS));
    assert_param(IS_QSPI_XIP_INCR_TOC(QSPI_InitStruct->ITOC));
    assert_param(IS_QSPI_XIP_WRAP_TOC(QSPI_InitStruct->WTOC));
    assert_param(IS_QSPI_XIP_TOUT(QSPI_InitStruct->XTOUT));

    assert_param(IS_QSPI_NDF(QSPI_InitStruct->NDF));
    assert_param(IS_QSPI_CLK_DIV(QSPI_InitStruct->CLK_DIV));
    assert_param(IS_QSPI_TXFT(QSPI_InitStruct->TXFT));
    assert_param(IS_QSPI_RXFT(QSPI_InitStruct->RXFT));
    assert_param(IS_QSPI_TXFN(QSPI_InitStruct->TXFN));
    assert_param(IS_QSPI_RXFN(QSPI_InitStruct->RXFN));
    assert_param(IS_QSPI_DDR_TXDE(QSPI_InitStruct->TXDE));
            
    if((QSPI_InitStruct->SPI_FRF) == QSPI_CTRL0_SPI_FRF_STANDARD_FORMAT)
    {
        tmpregister = (uint32_t)(QSPI_InitStruct->SPI_FRF | QSPI_InitStruct->CFS | QSPI_InitStruct->SSTE | QSPI_InitStruct->TMOD 
                                                                | QSPI_InitStruct->SCPOL | QSPI_InitStruct->SCPH | QSPI_InitStruct->FRF | QSPI_InitStruct->DFS);
        QSPI->CTRL0 = tmpregister; 
            
        tmpregister = 0;
        tmpregister = (uint32_t)(QSPI_InitStruct->MWMOD | QSPI_InitStruct->MC_DIR | QSPI_InitStruct->MHS_EN);
        QSPI->MW_CTRL  = tmpregister;
    
        tmpregister = 0;
        tmpregister = (uint32_t)(QSPI_InitStruct->SES | QSPI_InitStruct->SDCN);
        QSPI->RS_DELAY  = tmpregister;
    }
    else if((QSPI_InitStruct->SPI_FRF == QSPI_CTRL0_SPI_FRF_DUAL_FORMAT) || (QSPI_InitStruct->SPI_FRF == QSPI_CTRL0_SPI_FRF_QUAD_FORMAT))
    {
        tmpregister = (uint32_t)(QSPI_InitStruct->SPI_FRF | QSPI_InitStruct->CFS | QSPI_InitStruct->SSTE | QSPI_InitStruct->TMOD 
                                                                | QSPI_InitStruct->SCPOL | QSPI_InitStruct->SCPH | QSPI_InitStruct->FRF | QSPI_InitStruct->DFS);
        QSPI->CTRL0 = tmpregister;
            
        tmpregister = 0;
        tmpregister = (uint32_t)(QSPI_InitStruct->MWMOD | QSPI_InitStruct->MC_DIR | QSPI_InitStruct->MHS_EN);
        QSPI->MW_CTRL  = tmpregister;

        tmpregister = 0;
        tmpregister = (uint32_t)(QSPI_InitStruct->SES | QSPI_InitStruct->SDCN);
        QSPI->RS_DELAY  = tmpregister;
            
        tmpregister = 0;
        tmpregister = (uint32_t)(QSPI_InitStruct->ENHANCED_CLK_STRETCH_EN | QSPI_InitStruct->ENHANCED_INST_DDR_EN
                                 | QSPI_InitStruct->ENHANCED_SPI_DDR_EN | QSPI_InitStruct->ENHANCED_WAIT_CYCLES | QSPI_InitStruct->ENHANCED_INST_L
                                 | QSPI_InitStruct->ENHANCED_ADDR_LEN | QSPI_InitStruct->ENHANCED_TRANS_TYPE);
        QSPI->ENH_CTRL0 = tmpregister;
            
        tmpregister = 0;
        tmpregister = (uint32_t)(QSPI_InitStruct->XIP_MBL | QSPI_InitStruct->XIP_CT_EN | QSPI_InitStruct->XIP_INST_EN | QSPI_InitStruct->XIP_INST_DDR_EN
                                                                | QSPI_InitStruct->XIP_DDR_EN | QSPI_InitStruct->XIP_DFS_HC | QSPI_InitStruct->XIP_WAIT_CYCLES | QSPI_InitStruct->XIP_MD_BITS_EN
                                                                | QSPI_InitStruct->XIP_INST_L | QSPI_InitStruct->XIP_ADDR_LEN | QSPI_InitStruct->XIP_TRANS_TYPE | QSPI_InitStruct->XIP_FRF);
        QSPI->XIP_CTRL = tmpregister;

        QSPI->XIP_MODE  = QSPI_InitStruct->XIP_MD_BITS;
        QSPI->XIP_INCR_TOC  = QSPI_InitStruct->ITOC;
        QSPI->XIP_WRAP_TOC  = QSPI_InitStruct->WTOC;
        QSPI->XIP_TOUT  = QSPI_InitStruct->XTOUT;
    }
    QSPI->CTRL1 = QSPI_InitStruct->NDF;
    QSPI->BAUD  = QSPI_InitStruct->CLK_DIV;
    QSPI->TXFT  = QSPI_InitStruct->TXFT;
    QSPI->RXFT  = QSPI_InitStruct->RXFT;
    QSPI->TXFN  = QSPI_InitStruct->TXFN;
    QSPI->RXFN  = QSPI_InitStruct->RXFN;
    QSPI->DDR_TXDE  = QSPI_InitStruct->TXDE;
}
/**
 * @brief  Configure single GPIO port as GPIO_Mode_AF_PP.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
static void QSPI_SingleGpioConfig(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStructure.Pin        = Pin;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);
}
/**
  * @brief  Remap QSPI AFIO group by selecting the pin of NSS.
  * @param qspi_nss_port_sel select the pin of NSS.
                        QSPI_NSS_PORTA_SEL:QSPI remap by PA4~PA7 and PC4~PC5.
                        QSPI_NSS_PORTC_SEL:QSPI remap by PC10~PC12 and PD0~PD2.
  * @param IO1_Input IO1 Configure as input or not.
  * @param IO3_Output IO3 Configure as output or not.
  */
void QSPI_GPIO(QSPI_NSS_PORT_SEL qspi_nss_port_sel, bool IO1_Input, bool IO3_Output)
{
    GPIO_InitType GPIO_InitStructure;

    switch (qspi_nss_port_sel)
    {
    case QSPI_NSS_PORTA_SEL:
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_AFIO, ENABLE);
        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_QSPI, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP3_QSPI, DISABLE); //clear two bits of qspi

        QSPI_SingleGpioConfig(GPIOA, GPIO_PIN_4); // NSS
        QSPI_SingleGpioConfig(GPIOA, GPIO_PIN_5); // SCK
        QSPI_SingleGpioConfig(GPIOA, GPIO_PIN_6); // IO0
        if (IO1_Input)
        {
            GPIO_InitStructure.Pin        = GPIO_PIN_7; // IO1
            GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_INPUT;
            GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);
        }
        else
        {
            QSPI_SingleGpioConfig(GPIOA, GPIO_PIN_7); // IO1
        }
        
        if (IO3_Output)
        {
            GPIO_InitStructure.Pin        = GPIO_PIN_4 | GPIO_PIN_5; // IO2 and IO3
            GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);

            GPIOC->PBSC |= GPIO_PIN_4 | GPIO_PIN_5;
        }
        else
        {
            QSPI_SingleGpioConfig(GPIOC, GPIO_PIN_4); // IO2
            QSPI_SingleGpioConfig(GPIOC, GPIO_PIN_5); // IO3
        }
        break;
    case QSPI_NSS_PORTC_SEL:
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_GPIOD | RCC_APB2_PERIPH_AFIO, ENABLE);

        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_QSPI, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP3_QSPI, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP_QSPI_XIP_EN, ENABLE);

        QSPI_SingleGpioConfig(GPIOC, GPIO_PIN_10); // NSS
        QSPI_SingleGpioConfig(GPIOC, GPIO_PIN_11); // SCK
        QSPI_SingleGpioConfig(GPIOC, GPIO_PIN_12); // IO0
        if (IO1_Input)
        {
            GPIO_InitStructure.Pin        = GPIO_PIN_0; // IO1
            GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_INPUT;
            GPIO_InitPeripheral(GPIOD, &GPIO_InitStructure);
        }
        else
        {
            QSPI_SingleGpioConfig(GPIOD, GPIO_PIN_0); // IO1
        }
        
        if (IO3_Output)
        {
            GPIO_InitStructure.Pin        = GPIO_PIN_1 | GPIO_PIN_2; // IO2 and IO3
            GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitPeripheral(GPIOD, &GPIO_InitStructure);

            GPIOD->PBSC |= GPIO_PIN_1 | GPIO_PIN_2;
        }
        else
        {
            QSPI_SingleGpioConfig(GPIOD, GPIO_PIN_1); // IO2
            QSPI_SingleGpioConfig(GPIOD, GPIO_PIN_2); // IO3
        }
        break;
    default:
        break;
    }
}

/**
  * @brief Configuration of QSPI DMA.
  * @param TxRx transmit or receive data.
               QSPI_DMA_CTRL_TX_DMA_EN:transmit data
  * @param TxDataLevel dma transmit data level.
  */
void QSPI_Tx_DMA_CTRL_Config(uint8_t Cmd,uint8_t TxDataLevel)
{
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    assert_param(IS_QSPI_DMATDL_CTRL(TxDataLevel));
    if (Cmd)
    {
        QSPI->DMATDL_CTRL = TxDataLevel;  
        QSPI->DMA_CTRL   |= QSPI_DMA_CTRL_TX_DMA_EN; 
    }
    else
    {
        QSPI->DMA_CTRL   &= ~QSPI_DMA_CTRL_TX_DMA_EN;
    }
}

/**
  * @brief Configuration of QSPI DMA.
  * @param TxRx transmit or receive data.
               QSPI_DMA_CTRL_RX_DMA_EN:receive data
  * @param RxDataLevel dma receive data level.
  */
void QSPI_Rx_DMA_CTRL_Config(uint8_t Cmd, uint8_t RxDataLevel)
{
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    assert_param(IS_QSPI_DMARDL_CTRL(RxDataLevel));
    
    if (Cmd)
    {
        QSPI->DMARDL_CTRL = RxDataLevel;
        QSPI->DMA_CTRL   |= QSPI_DMA_CTRL_RX_DMA_EN;
    }
    else
    {
        QSPI->DMA_CTRL   &= ~QSPI_DMA_CTRL_RX_DMA_EN;
    }
}
/**
 * @brief  Get the flag of interrupt status register.
 * @param FLAG flag of related interrupt register.
 */
uint16_t QSPI_GetITStatus(uint16_t FLAG)
{
    uint16_t tmp = 0;
    tmp          = QSPI->ISTS & FLAG;
    if (tmp)
        return 1;
    else
        return 0;
}
/**
 * @brief  Clear the flag of related interrupt register.
 * @param FLAG flag of related interrupt register.
 */
void QSPI_ClearITFLAG(uint16_t FLAG)
{
    if (FLAG == QSPI_ISTS_TXFOIS)
        (void)QSPI->TXFOI_CLR;
    else if (FLAG == QSPI_ISTS_RXFOIS)
        (void)QSPI->RXFOI_CLR;
    else if (FLAG == QSPI_ISTS_RXFUIS)
        (void)QSPI->RXFUI_CLR;
    else if (FLAG == QSPI_ISTS_MMCIS)
        (void)QSPI->MMC_CLR;
    else if (FLAG == QSPI_ISTS)
        (void)QSPI->ICLR;
    else
    {
    }
}
/**
 * @brief  Clear the flag of related interrupt register.
 * @param FLAG flag of XRXFOIC interrupt register.
 */
void QSPI_XIP_ClearITFLAG(uint16_t FLAG)
{
    if (FLAG == QSPI_XIP_RXFOI_CLR_XRXFOIC)
       (void)QSPI->XIP_RXFOI_CLR;
}
/**
 * @brief  Get QSPI status,busy or not.
 * @return 1:QSPI busy;0:QSPI idle.
 */
bool GetQspiBusyStatus(void)
{
    if ((QSPI->STS & 0x01) == 0x01)
        return 1;
    return 0;
}
/**
 * @brief  Check transmit fifo full or not.
 * @return 1: Transmit fifo full;0: Transmit fifo not full.
 */
bool GetQspiTxDataBusyStatus(void)
{
    if ((QSPI->STS & 0x02) == 0x00)
        return 1;
    return 0;
}
/**
 * @brief  Check transmit fifo empty or not.
 * @return 1: Transmit fifo empty;0: Transmit fifo not empty.
 */
bool GetQspiTxDataEmptyStatus(void)
{
    if ((QSPI->STS & 0x04) == 0x04)
        return 1;
    return 0;
}
/**
 * @brief  Check receive fifo have data or not.
 * @return 1:Receive fifo have data;0:Receive fifo empty.
 */
bool GetQspiRxHaveDataStatus(void)
{
    if ((QSPI->STS & 0x08) == 0x08)
        return 1;
    return 0;
}
/**
 * @brief  Check receive fifo full or not.
 * @return 1: Receive fifo full;0: Receive fifo not full.
 */
bool GetQspiRxDataFullStatus(void)
{
    if ((QSPI->STS & 0x10) == 0x10)
        return 1;
    return 0;
}

/**
 * @brief  Check data conflict error or not.
 * @return 1: Data conflict error;0: No data conflict error.
 */
bool GetQspiDataConflictErrorStatus(void)
{
    if ((QSPI->STS & 0x40) == 0x40)
        return 1;
    return 0;
}
/**
  * @brief Write one data direct to QSPI DAT0 register to send.
  * @param SendData: data to be send.
  */
void QspiSendWord(uint32_t SendData)
{
    QSPI->DAT0 = SendData;
}
/**
  * @brief Read one data from QSPI DAT0 register.
  * @return the value of QSPI DAT0 register.
  */
uint32_t QspiReadWord(void)
{
    return QSPI->DAT0;
}
/**
  * @brief Get Pointer of QSPI DAT0 register.
  * @return the pointer of QSPI DAT0 register.
  */
uint32_t QspiGetDataPointer(void)
{
    return (uint32_t)&QSPI->DAT0;
}
/**
  * @brief Read value from QSPI RXFN register which shows the number of the data from receive fifo.
  * @return the number of the data from receive fifo.
  */
uint32_t QspiReadRxFifoNum(void)
{
    return QSPI->RXFN;
}
/**
 * @brief  Read DAT0 register to clear fifo.
 */
void ClrFifo(void)
{
    uint32_t timeout = 0;

    while (GetQspiRxHaveDataStatus())
    {
        QspiReadWord();
        if(++timeout >= 200)
        {
            break;
        }
    }
}
/**
 * @brief  Get data from fifo.
 * @param pData pointer to buffer of getting fifo data.
 * @param Len length of getting fifo data.
 */
uint32_t GetFifoData(uint32_t* pData, uint32_t Len)
{
    uint32_t cnt;
    for (cnt = 0; cnt < Len; cnt++)
    {
        if (GetQspiRxHaveDataStatus())
        {
            *pData++ = QspiReadWord();
        }
        else
        {
            return QSPI_NULL;
        }
    }

    return QSPI_SUCCESS;
}
/**
 * @brief Send words out from source data buffer and get returned datas into destination data buffer.
 * @param pSrcData pointer to buffer of sending datas.
 * @param pDstData pointer to buffer of getting returned datas.
 * @param cnt number of sending datas.
 */
void QspiSendAndGetWords(uint32_t* pSrcData, uint32_t* pDstData, uint32_t cnt)
{
    uint32_t num = 0;
    uint32_t timeout = 0;
    
    while (num < cnt)
    {
        QspiSendWord(*(pSrcData++));
        num++;
    }
    while (!GetQspiRxHaveDataStatus())
    {
        if(++timeout >= QSPI_TIME_OUT_CNT)
        {
            break;
        }
    }
    timeout = 0;
    while (QSPI->RXFN < cnt)
    {
        if(++timeout >= QSPI_TIME_OUT_CNT)
        {
            break;
        }
    }
    num = 0;
    while (num < cnt)
    {
        *(pDstData++) = QspiReadWord();
        num++;
    }
}
/**
  * @brief  Send one word data and get returned words into destination data buffer.
  * @param WrData one word to be sent.
  * @param pRdData pointer to buffer of getting returned datas.
  * @param LastRd whether go on to get returned datas.
                        1:go on to get returned datas.
                        0:end to get returned datas.
  */
uint32_t QspiSendWordAndGetWords(uint32_t WrData, uint32_t* pRdData, uint8_t LastRd)
{
    uint32_t    timeout1 = 0;

    QspiSendWord(WrData);                   //trammit
    *pRdData = QspiReadWord();  
    if(LastRd != 0)
    {
        while(!GetQspiRxHaveDataStatus())   //wait for data
        {
            if(++timeout1 >= QSPI_TIME_OUT_CNT)
            {
                return QSPI_NULL;           //time out
            }
        }

        *pRdData = QspiReadWord();          //read data 
        return QSPI_SUCCESS;    
    }
    
    return QSPI_NULL;
}


