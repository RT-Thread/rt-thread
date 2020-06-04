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
 * @file n32g45x_qspi.c
 * @author Nations Solution Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32g45x_qspi.h"

/**
 * @brief  Merge configuration from the buffer of QSPI para struct, then write it into related registers.
 * @param  QSPI_InitStruct pointer to buffer of QSPI para struct.
 */
void QspiConfigInit(QSPI_InitType* QSPI_InitStruct)
{
    uint32_t tmpregister = 0;

    if ((QSPI_InitStruct->SPI_FRF) == QSPI_CTRL0_SPI_FRF_STANDARD_FORMAT)
    {
        tmpregister |= (uint32_t)(QSPI_InitStruct->SPI_FRF | QSPI_InitStruct->TMOD | QSPI_InitStruct->SCPOL
                                  | QSPI_InitStruct->SCPH | QSPI_InitStruct->DFS);
        QSPI->CTRL0 = tmpregister;
        QSPI->CTRL1 = QSPI_InitStruct->NDF;
        QSPI->BAUD  = QSPI_InitStruct->CLK_DIV;
        QSPI->TXFT  = QSPI_InitStruct->TXFT;
        QSPI->RXFT  = QSPI_InitStruct->RXFT;
    }
    else if ((QSPI_InitStruct->SPI_FRF) == QSPI_CTRL0_SPI_FRF_DUAL_FORMAT)
    {
        tmpregister |= (uint32_t)(QSPI_InitStruct->SPI_FRF | QSPI_InitStruct->TMOD | QSPI_InitStruct->SCPOL
                                  | QSPI_InitStruct->SCPH | QSPI_InitStruct->DFS | QSPI_InitStruct->CFS);
        QSPI->CTRL0 = tmpregister;
        if ((QSPI_InitStruct->TMOD) == QSPI_CTRL0_TMOD_TX_ONLY)
        {
            QSPI_InitStruct->ENHANCED_WAIT_CYCLES = 0;
        }
        tmpregister = 0;
        tmpregister |=
            (uint32_t)(QSPI_InitStruct->ENHANCED_CLK_STRETCH_EN | QSPI_InitStruct->ENHANCED_ADDR_LEN
                       | QSPI_InitStruct->ENHANCED_INST_L | QSPI_InitStruct->ENHANCED_WAIT_CYCLES | QSPI_InitStruct->TRANS_TYPE);
        QSPI->ENH_CTRL0 = tmpregister;
        QSPI->BAUD     = QSPI_InitStruct->CLK_DIV;
        QSPI->TXFT     = QSPI_InitStruct->TXFT;
        QSPI->RXFT     = QSPI_InitStruct->RXFT;
        if ((QSPI_InitStruct->TMOD) == QSPI_CTRL0_TMOD_TX_ONLY)
        {
            QSPI->CTRL1 = 0;
        }
        else
        {
            QSPI->CTRL1 = QSPI_InitStruct->NDF;
        }
    }
    else if ((QSPI_InitStruct->SPI_FRF) == QSPI_CTRL0_SPI_FRF_QUAD_FORMAT)
    {
        tmpregister |= (uint32_t)(QSPI_InitStruct->SPI_FRF | QSPI_InitStruct->TMOD | QSPI_InitStruct->SCPOL
                                  | QSPI_InitStruct->SCPH | QSPI_InitStruct->DFS | QSPI_InitStruct->CFS);
        QSPI->CTRL0 = tmpregister;
        if ((QSPI_InitStruct->TMOD) == QSPI_CTRL0_TMOD_TX_ONLY)
        {
            QSPI_InitStruct->ENHANCED_WAIT_CYCLES = 0;
        }
        tmpregister = 0;
        tmpregister |=
            (uint32_t)(QSPI_InitStruct->ENHANCED_CLK_STRETCH_EN | QSPI_InitStruct->ENHANCED_ADDR_LEN
                       | QSPI_InitStruct->ENHANCED_INST_L | QSPI_InitStruct->ENHANCED_WAIT_CYCLES | QSPI_InitStruct->TRANS_TYPE);
        QSPI->ENH_CTRL0 = tmpregister;
        QSPI->BAUD     = QSPI_InitStruct->CLK_DIV;
        QSPI->TXFT     = QSPI_InitStruct->TXFT;
        QSPI->RXFT     = QSPI_InitStruct->RXFT;
        if ((QSPI_InitStruct->TMOD) == QSPI_CTRL0_TMOD_TX_ONLY)
        {
            QSPI->CTRL1 = 0;
        }
        else
        {
            QSPI->CTRL1 = QSPI_InitStruct->NDF;
        }
    }
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
                        QSPI_NSS_PORTF_SEL:QSPI remap by PF0~PF5.
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
        QSPI_SingleGpioConfig(GPIOC, GPIO_PIN_4); // IO2
        if (IO3_Output)
        {
            GPIO_InitStructure.Pin        = GPIO_PIN_5; // IO3
            GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);
        }
        else
        {
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
        QSPI_SingleGpioConfig(GPIOD, GPIO_PIN_1); // IO2
        if (IO3_Output)
        {
            GPIO_InitStructure.Pin        = GPIO_PIN_2; // IO3
            GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitPeripheral(GPIOD, &GPIO_InitStructure);
        }
        else
        {
            QSPI_SingleGpioConfig(GPIOD, GPIO_PIN_2); // IO3
        }
        break;
    case QSPI_NSS_PORTF_SEL:
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOF | RCC_APB2_PERIPH_AFIO, ENABLE);
        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_QSPI, ENABLE);
		GPIO_ConfigPinRemap(GPIO_RMP1_QSPI, ENABLE);

        QSPI_SingleGpioConfig(GPIOF, GPIO_PIN_0); // NSS
        QSPI_SingleGpioConfig(GPIOF, GPIO_PIN_1); // SCK
        QSPI_SingleGpioConfig(GPIOF, GPIO_PIN_2); // IO0
        if (IO1_Input)
        {
            GPIO_InitStructure.Pin        = GPIO_PIN_3; // IO1
            GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_INPUT;
            GPIO_InitPeripheral(GPIOF, &GPIO_InitStructure);
        }
        else
        {
            QSPI_SingleGpioConfig(GPIOF, GPIO_PIN_3); // IO1
        }
        QSPI_SingleGpioConfig(GPIOF, GPIO_PIN_4); // IO2
        if (IO3_Output)
        {
            GPIO_InitStructure.Pin        = GPIO_PIN_5; // IO3
            GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitPeripheral(GPIOF, &GPIO_InitStructure);
        }
        else
        {
            QSPI_SingleGpioConfig(GPIOF, GPIO_PIN_5); // IO3
        }
        break;
    default:
        break;
    }
}
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
 * @brief  Configuration of QSPI interrupt.
 */
void QSPI_NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitStructure.NVIC_IRQChannel                   = QSPI_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
/**
  * @brief  Configuration of QSPI DMA.
  * @param PeripheraAddr start address of periphera.
  * @param MemoryAddr start address of memory.
  * @param Len size of buffer.
  * @param TxRx transmit or receive data.
                        DMA_TX:transmit data
                        DMA_TX:receive data
  */
void QSPI_DMA_Config(uint32_t PeripheraAddr, uint32_t MemoryAddr, uint16_t Len, uint8_t TxRx)
{
    DMA_InitType DMA_InitStructure;
    DMA_ChannelType* DMAyChx;
    uint32_t Direction;
    uint8_t QSPI_DMAReq;
    uint8_t QSPI_DMADL;

    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA2, ENABLE);

    if (TxRx == DMA_TX) // DMA send enable
    {
        DMAyChx     = DMA2_CH7;
        Direction   = DMA_DIR_PERIPH_DST;
        QSPI_DMADL  = 0x01;
        QSPI_DMAReq = QSPI_DMAReq_TxEN;
        DMA_RequestRemap(DMA2_REMAP_QSPI_TX, DMA2, DMAyChx, ENABLE);
    }
    else if (TxRx == DMA_RX) // DMA receive enable
    {
        DMAyChx     = DMA2_CH8;
        Direction   = DMA_DIR_PERIPH_SRC;
        QSPI_DMADL  = 0x01;
        QSPI_DMAReq = QSPI_DMAReq_RxEN;
        DMA_RequestRemap(DMA2_REMAP_QSPI_RX, DMA2, DMAyChx, ENABLE);
    }

    DMA_DeInit(DMAyChx);
    DMA_InitStructure.PeriphAddr = PeripheraAddr; // Peripheral data address
    DMA_InitStructure.MemAddr    = MemoryAddr;    // memory address
    DMA_InitStructure.Direction  = Direction;     //
    DMA_InitStructure.BufSize    = Len;
    DMA_InitStructure.PeriphInc = DMA_PERIPH_INC_DISABLE;         // Peripheral address not increment
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;        // DMA memory auto increment
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_WORD; // Peripheral data In word
    DMA_InitStructure.MemDataSize    = 0x800;                     //	memory data In word
    DMA_InitStructure.CircularMode   = DMA_MODE_NORMAL;
    DMA_InitStructure.Priority       = DMA_PRIORITY_HIGH; // DMA channel High Priority
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;   // not memory-to-memory mode
    DMA_Init(DMAyChx, &DMA_InitStructure);                //

    if (TxRx == DMA_TX)
    {
        QSPI->DMA_CTRL   = 0x00;
        QSPI->DMATDL_CTRL = QSPI_DMADL;  // 1
        QSPI->DMA_CTRL   = QSPI_DMAReq; ////QSPI_DMAReq_TxEN
    }
    else if (TxRx == DMA_RX)
    {
        QSPI->DMA_CTRL   = 0x00;
        QSPI->DMARDL_CTRL = QSPI_DMADL;
        QSPI->DMA_CTRL   = QSPI_DMAReq;
    }

    DMA_EnableChannel(DMAyChx, ENABLE); // Enable DMA
}
/**
  * @brief  Select format of QSPI.
  * @param qspi_format_sel Select format of QSPI.
                        STANDARD_SPI_FORMAT_SEL:Standard spi
                        DUAL_SPI_FORMAT_SEL:Dual spi
                        QUAD_SPI_FORMAT_SEL:Quad spi
                        XIP_SPI_FORMAT_SEL: Memory mapping mode
  * @param data_dir The direction of transferring data.
                        TX_AND_RX:Transmit and receive data.
                        RX_ONLY:Receive data only.
                        TX_ONLY:Transmit data only.
  * @param count Number of data frames. It is valid only in RX_ONLY mode of DUAL_SPI_FORMAT_SEL or QUAD_SPI_FORMAT_SEL.
  */
void QspiInit(QSPI_FORMAT_SEL qspi_format_sel, QSPI_DATA_DIR data_dir, uint16_t count)
{
    QSPI_InitType QSPI_InitStruct;

    switch (qspi_format_sel)
    {
    case STANDARD_SPI_FORMAT_SEL:
        ////QSPI_GPIO(QSPI_NSS_PORTA_SEL,1,1);
        QSPI_GPIO(QSPI_AFIO_PORT_SEL, 0, 0);

        QSPI_DeInit();
        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_QSPI, ENABLE);
        QSPI_InitStruct.SPI_FRF  = QSPI_CTRL0_SPI_FRF_STANDARD_FORMAT;
        QSPI_InitStruct.TMOD     = QSPI_CTRL0_TMOD_TX_AND_RX;
        QSPI_InitStruct.SSTE    = 0;
        QSPI_InitStruct.SCPOL = QSPI_CTRL0_SCPOL_LOW;
        QSPI_InitStruct.SCPH = QSPI_CTRL0_SCPH_FIRST_EDGE;
        QSPI_InitStruct.DFS   = QSPI_CTRL0_DFS_8_BIT;
        QSPI_InitStruct.CLK_DIV  = CLOCK_DIVIDER;
        QSPI_InitStruct.TXFT     = TX_COUNT_EN;
        QSPI_InitStruct.NDF = CTRL1_NDF_CNT; // not affect by count in  standard spi mode

        QspiConfigInit(&QSPI_InitStruct);
        QSPI_Cmd(ENABLE);

        if (QSPI_AFIO_PORT_SEL == QSPI_NSS_PORTA_SEL)
        {
            GPIOC->PBSC = GPIO_PIN_5; // HOLD ON when select QSPI_NSS_PORTA_SEL
        }
        else if (QSPI_AFIO_PORT_SEL == QSPI_NSS_PORTC_SEL)
        {
            GPIOD->PBSC = GPIO_PIN_2; // HOLD ON when select QSPI_NSS_PORTC_SEL
        }
        else if (QSPI_AFIO_PORT_SEL == QSPI_NSS_PORTF_SEL)
        {
            GPIOF->PBSC = GPIO_PIN_5; // HOLD ON when select QSPI_NSS_PORTF_SEL
        }
        else
        {
        }
        break;
    case DUAL_SPI_FORMAT_SEL:
        QSPI_GPIO(QSPI_AFIO_PORT_SEL, 0, 0);

        QSPI_DeInit();
        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_QSPI, ENABLE);

		GPIO_ConfigPinRemap(GPIO_RMP_QSPI_XIP_EN, DISABLE);
        QSPI_InitStruct.SPI_FRF = QSPI_CTRL0_SPI_FRF_DUAL_FORMAT;
        if (data_dir == TX_AND_RX)
            QSPI_InitStruct.TMOD = QSPI_CTRL0_TMOD_TX_AND_RX;
        else if (data_dir == TX_ONLY)
            QSPI_InitStruct.TMOD = QSPI_CTRL0_TMOD_TX_ONLY;
        else if (data_dir == RX_ONLY)
            QSPI_InitStruct.TMOD = QSPI_CTRL0_TMOD_RX_ONLY;
        QSPI_InitStruct.SSTE                  = 0;
        QSPI_InitStruct.SCPOL               = QSPI_CTRL0_SCPOL_LOW;
        QSPI_InitStruct.SCPH               = QSPI_CTRL0_SCPH_FIRST_EDGE;
        QSPI_InitStruct.DFS                 = QSPI_CTRL0_DFS_8_BIT;
        QSPI_InitStruct.CLK_DIV                = CLOCK_DIVIDER;
        QSPI_InitStruct.TXFT                   = TX_COUNT_EN;
        QSPI_InitStruct.NDF                 = count; // only be valid in Rx mode
        QSPI_InitStruct.ENHANCED_CLK_STRETCH_EN = QSPI_ENH_CTRL0_CLK_STRETCH_EN;
        QSPI_InitStruct.ENHANCED_WAIT_CYCLES      = ENSPI_WAIT_2CYCLES;
        QSPI_InitStruct.ENHANCED_ADDR_LEN      = ENSPI_ADDR_24BIT;
        QSPI_InitStruct.ENHANCED_INST_L        = QSPI_ENH_CTRL0_INST_L_8_LINE;
        if (SRAM_CFG_EN == 1)
            QSPI_InitStruct.TRANS_TYPE = QSPI_ENH_CTRL0_TRANS_TYPE_ALL_BY_FRF;
        else
            QSPI_InitStruct.TRANS_TYPE = QSPI_ENH_CTRL0_TRANS_TYPE_STANDARD;

        QspiConfigInit(&QSPI_InitStruct);
        QSPI_Cmd(ENABLE);
        if (QSPI_AFIO_PORT_SEL == QSPI_NSS_PORTA_SEL)
        {
            GPIOC->PBSC = GPIO_PIN_5; // HOLD ON when select QSPI_NSS_PORTA_SEL
        }
        else if (QSPI_AFIO_PORT_SEL == QSPI_NSS_PORTC_SEL)
        {
            GPIOD->PBSC = GPIO_PIN_2; // HOLD ON when select QSPI_NSS_PORTC_SEL
        }
        else if (QSPI_AFIO_PORT_SEL == QSPI_NSS_PORTF_SEL)
        {
            GPIOF->PBSC = GPIO_PIN_5; // HOLD ON when select QSPI_NSS_PORTF_SEL
        }
        else
        {
        }
        break;
    case QUAD_SPI_FORMAT_SEL:
        QSPI_GPIO(QSPI_AFIO_PORT_SEL, 0, 0);

        QSPI_DeInit();
        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_QSPI, ENABLE);

		GPIO_ConfigPinRemap(GPIO_RMP_QSPI_XIP_EN, DISABLE);
        QSPI_InitStruct.SPI_FRF = QSPI_CTRL0_SPI_FRF_QUAD_FORMAT;
        if (data_dir == TX_AND_RX)
            QSPI_InitStruct.TMOD = QSPI_CTRL0_TMOD_TX_AND_RX;
        else if (data_dir == TX_ONLY)
            QSPI_InitStruct.TMOD = QSPI_CTRL0_TMOD_TX_ONLY;
        else if (data_dir == RX_ONLY)
            QSPI_InitStruct.TMOD = QSPI_CTRL0_TMOD_RX_ONLY;
        QSPI_InitStruct.SSTE                  = 0;
        QSPI_InitStruct.SCPOL               = QSPI_CTRL0_SCPOL_LOW;
        QSPI_InitStruct.SCPH               = QSPI_CTRL0_SCPH_FIRST_EDGE;
        QSPI_InitStruct.DFS                 = QSPI_CTRL0_DFS_8_BIT;
        QSPI_InitStruct.CLK_DIV                = CLOCK_DIVIDER;
        QSPI_InitStruct.TXFT                   = TX_COUNT_EN;
        QSPI_InitStruct.NDF                 = count; // only be valid in Rx mode
        QSPI_InitStruct.ENHANCED_CLK_STRETCH_EN = QSPI_ENH_CTRL0_CLK_STRETCH_EN;
        QSPI_InitStruct.ENHANCED_WAIT_CYCLES      = ENSPI_WAIT_2CYCLES;
        QSPI_InitStruct.ENHANCED_ADDR_LEN      = ENSPI_ADDR_24BIT;
        QSPI_InitStruct.ENHANCED_INST_L        = QSPI_ENH_CTRL0_INST_L_8_LINE;
        if (SRAM_CFG_EN == 1)
            QSPI_InitStruct.TRANS_TYPE = QSPI_ENH_CTRL0_TRANS_TYPE_ALL_BY_FRF;
        else
            QSPI_InitStruct.TRANS_TYPE = QSPI_ENH_CTRL0_TRANS_TYPE_STANDARD;
        QspiConfigInit(&QSPI_InitStruct);
        QSPI_Cmd(ENABLE);
        break;
    case XIP_SPI_FORMAT_SEL:
        QSPI_GPIO(QSPI_NSS_PORTA_SEL, 0, 0);

        QSPI_DeInit();
        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_QSPI, ENABLE);

        QSPI->SLAVE_EN     = 0;
        QSPI->EN           = 0;
        QSPI->XIP_SLAVE_EN = 0;

        QSPI->XIP_INCR_TOC = 0x6B; // ITOC
        QSPI->XIP_WRAP_TOC = 0x6B; // WTOC

        if (data_dir == RX_ONLY)
        {
            if (XIP_PREFETCH_EN)
                QSPI->ENH_CTRL0 = 0x20180218;
            else
                QSPI->ENH_CTRL0 = 0x180218;

            QSPI->XIP_CTRL = 0x450462;
        }
        else
        {
            QSPI->XIP_CTRL = 0x451462;
            QSPI->XIP_MODE = 0x11aa;
        }
        QSPI->CTRL1 = 16; //
        QSPI->BAUD  = 0x08;
        QSPI->CTRL0 = 0x800807;

        QSPI->SLAVE_EN     = 1;
        QSPI->EN           = 1;
        QSPI->XIP_SLAVE_EN = XIP_SLAVE_EN_SEN;

		GPIO_ConfigPinRemap(GPIO_RMP_QSPI_XIP_EN, ENABLE);
        break;
    default:
        break;
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
 * @brief  Get the flag of interrupt status register.
 * @param FLAG Flag of related interrupt register.
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
 * @param FLAG Flag of related interrupt register.
 */
void QSPI_ClearITFLAG(uint16_t FLAG)
{
    volatile uint16_t tmp = 0;

    if (FLAG == QSPI_ISTS_TXFOIS)
        tmp = QSPI->TXFOI_CLR;
    if (FLAG == QSPI_ISTS_RXFOIS)
        tmp = QSPI->RXFOI_CLR;
    if (FLAG == QSPI_ISTS_RXFUIS)
        tmp = QSPI->RXFUI_CLR;
    if (FLAG == QSPI_ISTS_MMCIS)
        tmp = QSPI->MMC_CLR;
    if (FLAG == QSPI_ISTS_ICRS)
        tmp = QSPI->ICLR;
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
 * @brief  Check transmit error or not.
 * @return 1: Transmit error;0: No transmit error.
 */
bool GetQspiTransmitErrorStatus(void)
{
    if ((QSPI->STS & 0x20) == 0x20)
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
		if(++timeout >= 200)
		{
			break;
		}
	}
	timeout = 0;
    while (QSPI->RXFN < cnt)
    {
		if(++timeout >= 200)
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
    uint32_t sr = QSPI_NULL;
	uint32_t timeout1 = 0,timeout2 =0;

    QspiSendWord(WrData);
    *pRdData   = QspiReadWord();
    sr         = QSPI_SUCCESS;
    if (LastRd != 0)
    {
        do
        {
            while (GetQspiRxHaveDataStatus())
            {
                *pRdData = QspiReadWord();
                sr       = QSPI_SUCCESS;
				if(++timeout2 >= 200)
				{
					break;
				}
            }
			if(++timeout1 >= 200)
			{
				break;
			}
        } while (GetQspiBusyStatus());
    }

    return sr;
}
/**
 * @brief  Read DAT0 register to clear fifo.
 */
void ClrFifo(void)
{
    uint32_t data;
		uint32_t timeout = 0;

    while (GetQspiRxHaveDataStatus())
    {
			data = QspiReadWord();
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

