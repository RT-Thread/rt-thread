/**
  ******************************************************************************
  * @file               ft32f4xx_qspi.c
  * @author             FMD AE
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of the Serial peripheral interface (QSPI):
  *                 + Initialization and Configuration
  *                 + Data transfers functions
  *                 + DMA transfers management
  *                 + XIP transfer management
  *                 + XIP transfer management
  *                 + Interrupts and flags management
  * @version            V1.0.0
  * @data                   2025-03-06
    ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_qspi.h"
#include "ft32f4xx_rcc.h"

/* QSPI registers Masks */
#define CTRLR0_CLEAR_MASK      ((uint32_t)0x00c04fc0)
#define SPI_CTRLR0_CLEAR_MASK  ((uint32_t)0x0c03033f)
/**
  * @brief  Deinitializes the QSPI peripheral registers to their default
  *         reset values.
  */
void QSPI_DeInit(void)
{

    /* Enable QSPI reset state */
    RCC_AHB3PeriphResetCmd(RCC_AHB3Periph_QSPI, ENABLE);
    /* Release QSPI from reset state */
    RCC_AHB3PeriphResetCmd(RCC_AHB3Periph_QSPI, DISABLE);
}

/**
  * @brief  Fills each QSPI_InitStruct member with its default value.
  * @param  QSPI_InitStruct: pointer to a QSPI_InitTypeDef structure which will be initialized.
  * @retval None
  */
void QSPI_StructInit(QSPI_InitTypeDef *QSPI_InitStruct)
{
    /*--------------- Reset QSPI init structure parameters values -----------------*/
    /* Initialize the QSPI_Protocol member */
    QSPI_InitStruct->QSPI_Protocol = QSPI_PROTOCOL_SPI;
    /* Initialize the QSPI_Direction member */
    QSPI_InitStruct->QSPI_Direction = QSPI_DIRECTION_Tx_ONLY;
    /* Initialize the QSPI_SSTE member */
    QSPI_InitStruct->QSPI_SSTE = QSPI_SSTE_TOGGLE_DIS;
    /* Initialize the QSPI_DataSize member */
    QSPI_InitStruct->QSPI_DataSize = QSPI_DATASIZE_8B;
    /* Initialize the QSPI_SCPOL member */
    QSPI_InitStruct->QSPI_SCPOL = QSPI_SCPOL_LOW;
    /* Initialize the QSPI_SCPHA member */
    QSPI_InitStruct->QSPI_SCPHA = QSPI_SCPHA_1EDGE;
    /* Initialize the QSPI_SER member */
    QSPI_InitStruct->QSPI_SER = QSPI_NCS0;
    /* Initialize the QSPI_Chio select min time member */
    QSPI_InitStruct->QSPI_CS_MIN_HIGH = 0;
    /*Initialize the DataMode member*/
    QSPI_InitStruct->QSPI_DataMode = QSPI_STANDARD;

}


/**
  * @brief  Initializes the QSPI peripheral according to the specified
  *         parameters in the QSPI_InitStruct.
  * @param  QSPI_InitStruct: pointer to a QSPI_InitTypeDef structure that
  *         contains the configuration information for the specified QSPI peripheral.
  *         Br: specifies the baundrate. Br can be the value between 0x0~0x7FFF.
  * @retval None
  */
void QSPI_Init(QSPI_InitTypeDef *QSPI_InitStruct, uint16_t Br)
{
    uint32_t tmpreg = 0;

    /* Check the QSPI parameters */
    assert_param(IS_QSPI_PROPTOCOL(QSPI_InitStruct->QSPI_Protocol));
    assert_param(IS_QSPI_DIRECTION_MODE(QSPI_InitStruct->QSPI_Direction));
    assert_param(IS_QSPI_SSTE(QSPI_InitStruct->QSPI_SSTE));
    assert_param(IS_QSPI_DATA_SIZE(QSPI_InitStruct->QSPI_DataSize));
    assert_param(IS_QSPI_SCPOL(QSPI_InitStruct->QSPI_SCPOL));
    assert_param(IS_QSPI_SCPHA(QSPI_InitStruct->QSPI_SCPHA));
    assert_param(IS_QSPI_SER_SEL(QSPI_InitStruct->QSPI_SER));
    assert_param(IS_QSPI_DATA_MODE(QSPI_InitStruct->QSPI_DataMode));

    /*---------------------------- QSPI CTRLR0 Configuration ------------------------*/
    /* Get the QSPI CTRLR0 value */
    tmpreg = QSPI->CTRLR0;
    /* Clear CLK_LOOP_EN,SPI_FRF,SSTE,SRL,TMOD,SCPOL,SCPHA,FRF,DFS bits */
    tmpreg &= ~CTRLR0_CLEAR_MASK;
    /* Configure QSPI: Protocol,Direction,SSTE,DataSize,SCPOL,SCPHA,SER,SRL*/
    /* Set SPI_FRF bits according to QSPI_Protocol value,select SPI/SSP/MICROWIRE proptocol */
    /* Set TMOD bit according to QSPI_Direction values,include txrx tx rx*/
    /* Set SSTE bit according to QSPI_SSTE value */
    /* Set SCPOL bit according to QSPI_SCPOL value */
    /* Set SCPHA bit according to QSPI_SCPHA value */

    /* Set DataSize according to QSPI_DataSize value,DataSize value must >= 'h11*/
    tmpreg  = (uint32_t)((uint32_t)QSPI_InitStruct->QSPI_DataSize);
    tmpreg |= (uint32_t)((uint32_t)QSPI_InitStruct->QSPI_Protocol | QSPI_InitStruct->QSPI_Direction |
                         QSPI_InitStruct->QSPI_SSTE     | QSPI_InitStruct->QSPI_SCPOL     |
                         QSPI_InitStruct->QSPI_SCPHA    | QSPI_InitStruct->QSPI_SER       |
                         QSPI_InitStruct->QSPI_DataMode);
    /* Write to QSPI CTRLR0 */
    QSPI->CTRLR0 = tmpreg;

    /*-------------------------QSPI SER Configuration -----------------------*/
    /* Get the QSPI SER value */
    tmpreg = QSPI->SER;
    /* Clear SER[1:0] bits */
    tmpreg &= (uint32_t)~QSPI_SER_SER;
    /* Configure QSPI: NCSx select */
    tmpreg |= (uint32_t)(QSPI_InitStruct->QSPI_SER);
    /* Write to QSPI SER */
    QSPI->SER = tmpreg;

    /*---------------------------- QSPI BAUDR Configuration --------------------*/
    /* Clear SCKDV[14:0] */
    QSPI->BAUDR = 0;
    QSPI->BAUDR = Br << 1;

    /*---------------------------- QSPI SPI_CTRLR1 Configuration ------------------------*/
    /* Get the QSPI SPI_CTRLR1 value */
    tmpreg = QSPI->SPI_CTRLR1;
    /* Clear CS_MIN_HIGH bit */
    tmpreg &= ~0xf0000;
    /* Configure CS_MIN_HIGH bit */
    tmpreg |= (uint32_t)((uint32_t)QSPI_InitStruct->QSPI_CS_MIN_HIGH) ;
    /* Write to QSPI SPI_CTRLR1 */
    QSPI->SPI_CTRLR1 = tmpreg << 16;
}

/**
  * @brief  Initializes the QSPI peripheral according to the specified
  *         parameters in the QSPI_CommandStruct.
  * @param  QSPI_CommandStruct: pointer to a QSPI_CommandTypeDef structure that
  *         contains the configuration information for the specified QSPI peripheral.
  * @retval None
  */

/**
  * @brief  Enables or disables the Testing Mode for QSPI.
  * @retval None
  */

void QSPI_TestMode_Enable(FunctionalState NewState)
{

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Enable test mode */
        QSPI->CTRLR0 |= QSPI_TESTING_MODE ;
    }
    else
    {
        /* Disable test mode*/
        QSPI->CTRLR0 &=  ~QSPI_TESTING_MODE ;
    }
}

/**
  * @brief  Config MicroWire Mode for QSPI.
  * @param  MHS: specifies the MICROWIRE handshake enable or disable.
  *          This parameter can be any combination of the following values:
  *            @arg QSPI_MICROHAND_DIS: handshake disable;
  *            @arg QSPI_MICROHAND_EN:  handshake enable;
  *         MDD: specifies the MICROWIRE transfer direction.
  *          This parameter can be any combination of the following values:
  *            @arg QSPI_MICRODIR_Rx: receive data;
  *            @arg QSPI_MICRODIR_Tx: transmit data;
  *         MWMOD: specifies the MICROWIRE transfer mode.
  *          This parameter can be any combination of the following values:
  *            @arg QSPI_MICROTRANS_NSEQ: nosequence transfer;
  *            @arg QSPI_MICROTRANS_SEQ:  sequence trnsfer;
  *         FrameSize: specifies the control frame size.
  *          This parameter can be any combination of the following values:
  *            @arg QSPI_CFS_1B: cfs 1 bit;
  *            @arg QSPI_CFS_2B: cfs 2 bit;
  *                        ......   ......
  *            @arg QSPI_CFS_15B: cfs 15 bit;
  *            @arg QSPI_CFS_16B: cfs 16 bit;

  * @retval None
  */

void QSPI_MicroWireMode_Config(uint32_t MHS, uint32_t MDD, uint32_t MWMOD, uint32_t FrameSize, FunctionalState NewState)
{

    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Get the QSPI MWCR value */
        tmpreg = QSPI->MWCR;
        /* Clear the MWMOD,MDD,MHS*/
        tmpreg &= ~0x7;
        /* Set the MWMOD,MDD,MHS*/
        tmpreg |= MHS | MDD | MWMOD;
        /* Write the QSPI MWCR register*/
        QSPI->MWCR = tmpreg ;

        /* Get the QSPI CTRLR0 value */
        tmpreg = QSPI->CTRLR0 ;
        /* Clear the CFS,FRF value */
        tmpreg &= ~(0xf << 16 | QSPI_CTRLR0_FRF);
        /*Set the CFS,FRF bits */
        tmpreg |= (FrameSize | QSPI_PROTOCOL_MICROWIRE);
        /* Write the CFS,FRF bits in CTRLR0 */
        QSPI->CTRLR0 |= tmpreg ;
    }
    else
    {
        /* Disable the MICROWIRE mode for the selected QSPI peripheral */
        QSPI->CTRLR0 &= ~QSPI_CTRLR0_FRF ;
    }
}

/**
  * @brief  Enables or disables the specified QSPI peripheral.
  * @param  NewState: new state of the QSPI peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void QSPI_EnCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected QSPI peripheral */
        QSPI->SSIENR |= QSPI_SSIENR_SSIC_EN;
    }
    else
    {
        /* Disable the selected QSPI peripheral */
        QSPI->SSIENR &= ~QSPI_SSIENR_SSIC_EN;
    }
}

/**
  * @brief  Enables or disables the TI Mode.
  *
  * @note   This function can be called only after the QSPI_Init() function has
  *         been called.
  *
  * @param  NewState: new state of the selected QSPI TI communication mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void QSPI_TIModeCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the TI mode for the selected QSPI peripheral */
        QSPI->CTRLR0 &= (uint32_t)~((uint32_t)QSPI_CTRLR0_FRF);
        QSPI->CTRLR0 |= (QSPI_CTRLR0_FRF & 1 << 6);
    }
    else
    {
        /* Disable the TI mode for the selected QSPI peripheral */
        QSPI->CTRLR0 &= (uint32_t)~((uint32_t)QSPI_CTRLR0_FRF);
    }
}
/**
  * @brief  Configures the data size for the selected QSPI.
  * @param  QSPI_DataSize: specifies the QSPI data size.
  *         For the QSPI peripheral this parameter can be one of the following values:
  *            @arg QSPI_DATASIZE_4B: Set data size to 4 bits
  *            @arg QSPI_DATASIZE_5B: Set data size to 5 bits
  *            @arg QSPI_DATASIZE_6B: Set data size to 6 bits
  *                             ......              ......
  *            @arg QSPI_DATASIZE_30B: Set data size to 30 bits
  *            @arg QSPI_DATASIZE_31B: Set data size to 31 bits
  *            @arg QSPI_DATASIZE_32B: Set data size to 32 bits
  * @retval None
  */
void QSPI_DataSizeConfig(uint16_t QSPI_DataSize)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_QSPI_DATA_SIZE(QSPI_DataSize));
    if (QSPI_DataSize >= 3)
    {
        /* Read the CTRLR0 register */
        tmpreg = QSPI->CTRLR0;
        /* Clear DFD[4:0] bits */
        tmpreg &= ~0x1f;
        /* Set new DS[3:0] bits value */
        tmpreg = QSPI_DataSize | tmpreg;
        QSPI->CTRLR0 = tmpreg;
    }
    else
    {
        // printf("ERROR ! QSPI DATA SIZE CAN NOT BE LESS THAN 4BITS!!! \n");
    }
}

/**
  * @brief  Configures the number of data frames.
  * @param  QSPI_NDF: specifies the NDF value.
  * @retval None
  */
void QSPI_DataNumberConfig(uint32_t QSPI_NDF)
{
    /* Check the parameters */
    assert_param(IS_QSPI_DATANUMBER(QSPI_NDF));

    /* Set new NDF bits value */
    QSPI->CTRLR1 = QSPI_NDF ;
}
/**
  * @brief  Configures the FIFO reception threshold for the selected QSPI.
  * @param  QSPI_RxFIFOThreshold: specifies the FIFO reception threshold.
  * @retval None
  */
void QSPI_RxFIFOThresholdConfig(uint16_t QSPI_RxFIFOThreshold)
{
    /* Check the parameters */
    assert_param(IS_QSPI_RX_FIFO_THRESHOLD(QSPI_RxFIFOThreshold));

    /* Clear RFT bit */
    QSPI->RXFTLR &= ~QSPI_RXFTLR_RFT;

    /* Set new RFT bit value */
    QSPI->RXFTLR |= QSPI_RxFIFOThreshold;
}

/**
  * @brief  Configures the FIFO transmition threshold for the selected QSPI.
  * @param  QSPI_TxFIFOThreshold: specifies the FIFO transmition threshold.
  * @param  QSPI_TxFIFOStart: specifies the FIFO transfer start interrupt level.
  * @retval None
  */
void QSPI_TxFIFOThresholdConfig(uint16_t QSPI_TxFIFOStart, uint16_t QSPI_TxFIFOThreshold)
{
    /* Check the parameters */
    assert_param(IS_QSPI_TX_FIFO_THRESHOLD(QSPI_TxFIFOThreshold));
    assert_param(IS_QSPI_TX_FIFO_STARTLEVEL(QSPI_TxFIFOStart));

    /* Clear TXFTHR TFT bit */
    QSPI->TXFTLR &= ~(QSPI_TXFTLR_TFT | QSPI_TXFTLR_TXFTHR);

    /* Set new TXFTHR TFT bit value */
    QSPI->TXFTLR |= (QSPI_TxFIFOStart << 16 | QSPI_TxFIFOThreshold);
}

/**
  * @brief  Enables or disables the slave select toggle mode.
  * @note   This bits only can be set when SCPH = 0.
  * @param  NewState: new state of the NSS pulse management mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void QSPI_SSTEModeCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the NSS pulse management mode */
        QSPI->CTRLR0 |= QSPI_CTRLR0_SSTE;
    }
    else
    {
        /* Disable the NSS pulse management mode */
        QSPI->CTRLR0 &= ~QSPI_CTRLR0_SSTE;
    }
}

/**
  * @}
  */
/**
  * @brief  Transmits a Data through the QSPI peripheral.
  * @param  Data: Data to be transmitted.
  * @retval None
  */
void QSPI_SendData(uint32_t Data)
{

    QSPI->DR[0] = (uint32_t)Data;
}

/**
  * @brief  Returns the most recent received data by the QSPI peripheral.
  * @retval The value of the received data.
  */
uint32_t QSPI_ReceiveData(void)
{
    uint32_t qspixbase = 0x00;

    qspixbase = (uint32_t)QSPI;
    qspixbase += 0x60;

    return *(__IO uint32_t *) qspixbase;
}

/**
  * @brief  Config the QSPI SPI frame format.
  * @param  LINE: specifies the QSPI line numbers.
  *          This parameter can be any combination of the following values:
  *            @arg QSPI_STANDARD: single line;
  *            @arg QSPI_DUAL:     dual line;
  *            @arg QSPI_QUAD:     quad line.
  * @retval None
  */
void QSPI_LineCfg(uint32_t LINE)
{
    /* Check the parameters */
    assert_param(IS_QSPI_DATA_MODE(LINE));

    /* Clear the SPI_FRF bits*/
    QSPI->CTRLR0 &= ~QSPI_CTRLR0_SPI_FRF ;
    /* Set the SPI_FRF bits*/
    QSPI->CTRLR0 |= LINE;
}

/**
  * @brief  Config the QSPI transfer mode.
  * @param  TRANS: specifies the QSPI transfer mode.
  *          This parameter can be any combination of the following values:
  *            @arg QSPI_DIRECTION_Tx_AND_Rx:   txrx mode;
  *            @arg QSPI_DIRECTION_Tx_ONLY:     tx only mode;
  *            @arg QSPI_DIRECTION_Rx_ONLY:     rx only mode;
  *            @arg QSPI_DIRECTION_EEPROM_READ: eeprom read mode.
  * @retval None
  */

void QSPI_TransMode(uint32_t TRANS)
{
    /* Check the parameters */
    assert_param(IS_QSPI_DIRECTION_MODE(TRANS));

    /* Clear the TMOD bits*/
    QSPI->CTRLR0 &= ~QSPI_CTRLR0_TMOD ;
    /* Set the TMOD bits*/
    QSPI->CTRLR0 |= TRANS ;
}

/**
  * @brief  Config QSPI waitcycles.
  * @param  NUMBER: specifies the QSPI number of waitcycles.
  *          This parameter can be less than 0x1f:
  * @retval None
  */
void QSPI_WaitCyclesConfig(uint32_t NUMBER)
{

    /* Check the parameters */
    assert_param(IS_QSPI_WAITCYCLES(NUMBER));

    /* Clear the WAIT_CYCLES bits*/
    QSPI->SPI_CTRLR0 &= ~QSPI_SPI_CTRLR0_WAIT_CYCLES;
    /* Set the WAIT_CYCLES bits*/
    QSPI->SPI_CTRLR0 |= NUMBER << 11 ;

}

/**
  * @brief  Config QSPI waitcycles.
  * @param  TRANSTYPE: specifies the number of instruction and addr phase lane.
  *          This parameter can be any combination of the following values:
  *          @arg QSPI_TRANSTYPE_STAND :  both instruction and addr work in standard mode
  *          @arg QSPI_TRANSTYPE_MIX   :  instruction works in standard,addr works in the SPI mode selected in the SPI_FRF filed
  *          @arg QSPI_TRANSTYPE_FRF   :  both instruction and addr work in the SPI mode selected in the SPI_FRF filed
  * @retval None
  */
void QSPI_TransTypeConfig(uint32_t TRANSTYPE)
{

    /* Check the parameters */
    assert_param(IS_QSPI_TRANSTYPE(TRANSTYPE));

    /* Clear the TRANS_TYPE bits*/
    QSPI->SPI_CTRLR0 &= ~QSPI_SPI_CTRLR0_TRANS_TYPE;
    /* Set the TRANS_TYPE bits*/
    QSPI->SPI_CTRLR0 |= TRANSTYPE ;

}

/**
  * @}
  */
/**
  * @brief  Enables or disables the QSPI DMA interface.
  * @param  QSPI_MAReq: specifies the QSPI DMA transfer request to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg QSPI_DMAReq_Tx: Tx buffer DMA transfer request
  *            @arg QSPI_DMAReq_Rx: Rx buffer DMA transfer request
  * @param  NewState: new state of the selected QSPI DMA transfer request.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void QSPI_DMACmd(uint32_t QSPI_DMAReq, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_QSPI_DMA_REQ(QSPI_DMAReq));

    if (NewState != DISABLE)
    {
        /* Enable the selected QSPI DMA requests */
        QSPI->DMACR |= QSPI_DMAReq;
    }
    else
    {
        /* Disable the selected QSPI DMA requests */
        QSPI->DMACR &= (uint32_t)~QSPI_DMAReq;
    }
}

/**
  * @brief  Config the DMA Tx data level.
  * @param  QSPI_DMATxDLevel: specifies the QSPI DMA Tx data level.
  *          This parameter can be less than 0xF.
  * @retval None
  */

void QSPI_DMA_Tx_DATALEVELCmd(uint32_t QSPI_DMATxDLevel)
{
    /* Check the parameters */
    assert_param(IS_QSPI_DMA_TX_DATA_LEVEL(QSPI_DMATxDLevel));

    /* Config the QSPI DMA Txdata level */
    QSPI->DMATDLR = QSPI_DMATxDLevel;

}

/**
  * @brief  Config the DMA Rx data level.
  * @param  QSPI_DMARxDLevel: specifies the QSPI DMA Rx data level.
  *          This parameter can be less than 0xF.
  * @retval None
  */

void QSPI_DMA_Rx_DATALEVELCmd(uint32_t QSPI_DMARxDLevel)
{
    /* Check the parameters */
    assert_param(IS_QSPI_DMA_RX_DATA_LEVEL(QSPI_DMARxDLevel));

    /* Config the QSPI DMA Rxdata level */
    QSPI->DMARDLR = QSPI_DMARxDLevel;

}


/**
  * @}
  */

/**
  * @brief  Enables or disables the QSPI XIP instruction phase.
  * @param  NewState: new state of the selected QSPI instruction phase.
  *          This parameter can be: ENABLE or DISABLE.
  *          INST_L specifies the QSPI instruction phase length.
  *          This parameter can be one of the following values:
  *          QSPI_INSTRUCTION_0B: instruction 0 bits.
  *          QSPI_INSTRUCTION_4B: instruction 4 bits.
  *          QSPI_INSTRUCTION_8B: instruction 8 bits.
  *          QSPI_INSTRUCTION_16B: instruction 16 bits.
  * @note   Write SPI_CTRLR0 register must clear SSIENR bit.
  *         Normal mode instruction enable: INST_L != 0.
  *         XIP mode enable: (INST_L != 0) && (XIP_INST_EN == 1)
  * @retval None
  */
void QSPI_XIP_INSTCmd(uint32_t INSTRUCTION_L, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_QSPI_XIP_INST(QSPI_INSTCfg));

    if (NewState != DISABLE)
    {
        /* Clear the INST_L*/
        QSPI->SPI_CTRLR0 &= ~QSPI_SPI_CTRLR0_INST_L ;
        /* Config instruction length and enable*/
        QSPI->SPI_CTRLR0 |= INSTRUCTION_L | QSPI_SPI_CTRLR0_XIP_INST_EN;

    }
    else
    {
        /* Clear INST_L and XIP_INST_EN bits*/
        QSPI->SPI_CTRLR0 &= ~(QSPI_SPI_CTRLR0_INST_L | QSPI_SPI_CTRLR0_XIP_INST_EN);
    }
}


/**
  * @brief  Config the QSPI XIP instruction opcode.
  * @param  QSPI_XIP_INSTCfg: specifies the QSPI XIP mode instruction .
  *          This parameter can be less than 0xFFFF.
  * @retval None
  */

void QSPI_XIP_INST_Config(uint32_t QSPI_XIP_INSTCfg)
{
    /* Set mode bit phase*/
    QSPI->XIP_INCR_INST = QSPI_XIP_INSTCfg ;
}

/**
  * @brief  Enables or disables the QSPI ADDR phase.
  * @note   Write SPI_CTRLR0 register must clear SSIENR bit.
  *         ADDR_L specifies the QSPI addr phase length.
  *         This parameter can be one of the following values:
  *         QSPI_ADDRESS_0B: addr length 0 bits.
  *         QSPI_ADDRESS_4B: addr length 4 bits.
  *                    ......           ......
  *         QSPI_ADDRESS_56B: addr length 56 bits.
  *         QSPI_ADDRESS_60B: addr length 60 bits.
  * @retval None
  */
void QSPI_ADDRCfg(uint32_t ADDR_L)
{
    /* Check the parameters */
    assert_param(IS_QSPI_ADDRESSSIZE(ADDR_L));

    /* Clear ADDR_L bits*/
    QSPI->SPI_CTRLR0 &= ~QSPI_SPI_CTRLR0_ADDR_L;
    /* Config ADDR_L bits*/
    QSPI->SPI_CTRLR0 |= ADDR_L;
}

/**
  * @brief  Enables or disables the QSPI XIP mode bits .
  * @param  NewState: new state of the QSPI mode bits phase.
  *          This parameter can be: ENABLE or DISABLE.
  *         MODEBITS: specifies the QSPI XIP mode bits .
  *          This parameter can be less than 0xFFFF.
  *         MD_SIZE: specifies the QSPI mode bits length.
  *          This parameter can be one of the following values:
  *           QSPI_MODEBITS_2B:   modebits length equal to 2 bits.
  *           QSPI_MODEBITS_4B:   modebits length equal to 4 bits.
  *           QSPI_MODEBITS_8B:   modebits length equal to 8 bits.
  *           QSPI_MODEBITS_16B:  modebits length equal to 16 bits.
  * @retval None
  */

void QSPI_XIP_ModeBitsCmd(uint32_t MODEBITS, uint32_t MD_SIZE, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_QSPI_MODEBITSSIZE(MD_SIZE));
    assert_param(IS_QSPI_XIP_MODEBITS(MODEBITS));

    if (NewState != DISABLE)
    {
        /* Clear XIP_MBL bits*/
        QSPI->SPI_CTRLR0 &= ~QSPI_SPI_CTRLR0_XIP_MBL ;
        /* Set XIP_MD_BIT_EN , XIP_MBL bits*/
        QSPI->SPI_CTRLR0 |= QSPI_SPI_CTRLR0_XIP_MD_BIT_EN | MD_SIZE;
        /* Config XIP mode bits*/
        QSPI->XIP_MODE_BITS = MODEBITS;
    }
    else
    {
        /* Clear XIP_MD_BIT_EN bit*/
        QSPI->SPI_CTRLR0 &= ~QSPI_SPI_CTRLR0_XIP_MD_BIT_EN ;
    }
}


/**
  * @brief  Enables or disables the QSPI data/addr phase ddr mode .
  * @param  NewState: new state of the QSPI data/addr phase ddr mode.
  *          This parameter can be: ENABLE or DISABLE.
  *         Ddr_TXD: specifies the DDR mode driveing edge of transmit data.
  *          This parameter can be less than 0xFF.
  * @retval None
  */

void QSPI_Ddrcmd(uint32_t Ddr_TXD, FunctionalState NewState)
{

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_QSPI_DDR_DRIVE_EDGE(Ddr_TXD));
    if (NewState != DISABLE)
    {
        /* Set the SPI_DDR_EN bit*/
        QSPI->SPI_CTRLR0 |= QSPI_SPI_CTRLR0_SPI_DDR_EN ;
        /* Set the TDE bit*/
        QSPI->DDR_DRIVE_EDGE = Ddr_TXD ;
    }
    else
    {
        /* Clear the SPI_DDR_EN bit*/
        QSPI->SPI_CTRLR0 &= ~QSPI_SPI_CTRLR0_SPI_DDR_EN ;
        /* Clear the TDE bit*/
        QSPI->DDR_DRIVE_EDGE = 0 ;
    }

}

/**
  * @brief  Enables or disables the QSPI instruction phase ddr mode .
  * @param  NewState: new state of the QSPI instruction phase ddr mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */

void QSPI_InstDdrcmd(FunctionalState NewState)
{

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Set the INST_DDR_EN bit*/
        QSPI->SPI_CTRLR0 |= QSPI_SPI_CTRLR0_INST_DDR_EN ;
    }
    else
    {
        /* Clear the INST_DDR_EN bit*/
        QSPI->SPI_CTRLR0 &= ~QSPI_SPI_CTRLR0_INST_DDR_EN ;
    }

}

/**
  * @brief  Enables or disables the QSPI XIP continous transfer .
  * @param  NewState: new state of the QSPI XIP continous transfer.
  *          This parameter can be: ENABLE or DISABLE.
  *         TIMOUT: specifies the XIP time out value in terms of hclk.
  *         This parameter can be less than 0xFF.
  * @retval None
  */

void QSPI_XIP_ContinuousCmd(uint32_t TIMOUT, FunctionalState NewState)
{

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_QSPI_XIP_TIMOUT(TIMOUT));

    if (NewState != DISABLE)
    {
        /* Set the SSIC_XIP_CONT_XFER_EN bit*/
        QSPI->SPI_CTRLR0 |= QSPI_SPI_CTRLR0_SSIC_XIP_CONT_XFER_EN;
        /* Set the XIP_CNT_TIME_OUT */
        QSPI->XIP_CNT_TIME_OUT = TIMOUT ;
    }
    else
    {
        /* Clear the SSIC_XIP_CONT_XFER_EN bit*/
        QSPI->SPI_CTRLR0 &= ~QSPI_SPI_CTRLR0_SSIC_XIP_CONT_XFER_EN;
    }
}


/**
  * @brief  Enables or disables the QSPI XIP DFS Fix .
  * @param  NewState: new state of the QSPI XIP DFS fix.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */

void QSPI_XIP_DFSHCCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Set the XIP_DFS_HC bit*/
        QSPI->SPI_CTRLR0 |= QSPI_SPI_CTRLR0_XIP_DFS_HC;
    }
    else
    {
        /* Clear the XIP_DFS_HC bit*/
        QSPI->SPI_CTRLR0 &= ~QSPI_SPI_CTRLR0_XIP_DFS_HC;
    }

}
/**
  * @brief  Enables or disables the QSPI CLK_LOOP_BACK MODE .
  * @param  NewState: new state of the QSPI clk loop back mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */

void QSPI_CLK_LOOPCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Set the CLK_LOOP_EN bit*/
        QSPI->CTRLR0 |= QSPI_CTRLR0_CLK_LOOP_EN;
    }
    else
    {
        /* Clear the CLK_LOOP_EN bit*/
        QSPI->CTRLR0 &= ~QSPI_CTRLR0_CLK_LOOP_EN;
    }

}
/**
  * @brief  Config the rx sample delay mode .
  * @param  SE:specifies the receive data sample edge
  *          This parameter can be one of the following value:
  *          @arg QSPI_SAMPLE_NEGEDGE: sample negedge;
  *          @arg QSPI_SAMPLE_POSEDGE: sample posgedge;
  *         RSD:specifies the receive data sample delay.
  *          This parameter can be less than 0xFF .
  * @retval None
  */
void QSPI_RX_SAMPLEDLYConfig(uint32_t SE, uint32_t RSD)
{

    /* Check the parameters */
    assert_param(IS_QSPI_SAMPLE_DLY_EDGE(SE));
    assert_param(IS_QSPI_SAMPLE_DLY(RSD));

    /* Clear SE and RSD bits*/
    QSPI->RX_SAMPLE_DELAY = 0;
    /* Set SE and RSD bits*/
    QSPI->RX_SAMPLE_DELAY = (SE | RSD) ;
}


/**
  * @brief  Enables or disables the QSPI read data strobe mode.
  * @param  RXDS_VL_EN :specifies enable or disable variable latency mode.
  *          This parameter can be one of the following value:
  *          @arg QSPI_VARIABLE_LATEN_DIS: disable variable latency mode;
  *          @arg QSPI_VARIABLE_LATEN_EN: enable variable latency mode;
  * @param  NewState: new state of the QSPI read data strobe mod.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void QSPI_RXDSConfig(uint32_t RXDS_VL_EN, FunctionalState NewState)
{

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_QSPI_VL_EN(RXDS_VL_EN));

    if (NewState != DISABLE)
    {
        /* Clear the RXDS_VL_EN,SPI_RXDS_EN bit*/
        QSPI->SPI_CTRLR0 &= ~(QSPI_SPI_CTRLR0_SPI_RXDS_EN | QSPI_SPI_CTRLR0_RXDS_VL_EN);
        /* Set the RXDS_VL_EN,SPI_RXDS_EN bit*/
        QSPI->SPI_CTRLR0 |= QSPI_SPI_CTRLR0_SPI_RXDS_EN | RXDS_VL_EN ;
    }
    else
    {
        /* Clear the SPI_RXDS_EN bit*/
        QSPI->SPI_CTRLR0 &= ~QSPI_SPI_CTRLR0_SPI_RXDS_EN ;
    }
}

/**
  * @brief  Enables or disables the clk stretch mode .
  * @param  NewState: new state of clk stretch mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */

void QSPI_CLK_StretchCmd(FunctionalState NewState)
{

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the CLK STRECTH */
        QSPI->SPI_CTRLR0 |= QSPI_SPI_CTRLR0_CLK_STRETCH_EN;
    }
    else
    {
        /* Disable the CLK STRECTH */
        QSPI->SPI_CTRLR0 &= ~QSPI_SPI_CTRLR0_CLK_STRETCH_EN;
    }
}
/**
  * @brief  Enables or disables the specified QSPI interrupts.
  * @param  QSPI_IT: specifies the QSPI interrupt source to be enabled or disabled.
  *          This parameter can be one of the following values:
  *            @arg QSPI_IT_TXEIM: Tx buffer empty interrupt mask
  *            @arg QSPI_IT_TXOIM: Tx buffer overflow interrupt mask
  *            @arg QSPI_IT_RXUIM: Rx buffer underflow interrupt mask
  *            @arg QSPI_IT_RXOIM: Rx buffer overflow interrupt mask
  *            @arg QSPI_IT_RXFIM: Rx buffer full interrupt mask
  *            @arg QSPI_IT_TXUIM: Tx buffer underflow interrupt mask
  * @param  NewState: new state of the specified QSPI interrupt.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void QSPI_ITConfig(uint32_t QSPI_IT, FunctionalState NewState)
{
    uint16_t itmask = 0 ;

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_QSPI_CONFIG_IT(QSPI_IT));

    /* Clear all the interrupt enable*/
    QSPI->IMR = 0 ;

    /* Set the IT mask */
    itmask = QSPI_IT;

    if (NewState != DISABLE)
    {
        /* Enable the selected QSPI interrupt */
        QSPI->IMR |= itmask;
    }
    else
    {
        /* Disable the selected QSPI interrupt */
        QSPI->IMR &= (uint16_t)~itmask;
    }
}

/**
  * @brief  Returns the current QSPI FIFO status,busy status.
  * @retval The status .
  *          - QSPI_STATE_BUSY: when QSPI is working
  *          - QSPI_STATE_TFNF: Tx buffer not full.
  *          - QSPI_STATE_TFE:  Tx buffer empty.
  *          - QSPI_STATE_RFNE: Rx buffer not empty.
  *          - QSPI_STATE_RFF:  Rx buffer full.
  */
uint32_t QSPI_GetStatus(uint16_t QSPI_SR_FLAG)
{
    /* Get the QSPI status */
    return (uint16_t)((QSPI->SR & QSPI_SR_FLAG));
}

/**
  * @brief  Returns the FIFO Interrupt status after mask.
  * @retval The Reception FIFO filling state.
  *          - QSPI_FLAG_TXEIS: Tx FIFO is empty
  *          - QSPI_FLAG_TXOIS: Tx FIFO is overflow.
  *          - QSPI_FLAG_RXUIS: Rx FIFO is underflow.
  *          - QSPI_FLAG_RXOIS: Rx FIFO is overflow.
  *          - QSPI_FLAG_RXFIS: Rx FIFO is full.
  *          - QSPI_FLAG_TXUIS: Tx FIFO is underflow.
  */
uint32_t QSPI_GetAfterMaskInterruptStatus(uint16_t QSPI_ISR_FLAG)
{
    /* Get the QSPI interrupt status */
    return (uint32_t)((QSPI->ISR & QSPI_ISR_FLAG));
}

/**
  * @brief  Returns the FIFO Interrupt status before mask.
  * @retval The Reception FIFO filling state.
  *          - QSPI_FLAG_TXEIR: Tx FIFO is empty
  *          - QSPI_FLAG_TXOIR: Tx FIFO is overflow.
  *          - QSPI_FLAG_RXUIR: Rx FIFO is underflow.
  *          - QSPI_FLAG_RXOIR: Rx FIFO is overflow.
  *          - QSPI_FLAG_RXFIR: Rx FIFO is full.
  *          - QSPI_FLAG_TXUIR: Tx FIFO is underflow.
  */
uint32_t QSPI_GetBeforeMaskInterruptStatusuint16_t (uint16_t QSPI_RISR_FLAG)
{
    /* Get the QSPI interrupt status */
    return (uint32_t)((QSPI->RISR & QSPI_RISR_FLAG));
}




/**
  * @brief  Clears the QSPI TxFIFO Error flag.
  * @retval None
  */
void QSPI_ClearTxFIFOErrorInterrupt(void)
{
    uint32_t data;

    /* Read TXEICR register to Clear the Tx FIFO overflow/underflow interrupt */
    data = QSPI->TXEICR;
}

/**
  * @brief  Clears the QSPI RxFIFO overflow interrupt.
  * @retval None
  */
void QSPI_ClearRxFIFOOverflowInterrupt(void)
{
    uint32_t data;

    /* Read RXOICR register to Clear the Rx FIFO overflow interrupt */
    data = QSPI->RXOICR;
}

/**
  * @brief  Clears the QSPI RxFIFO underflow interrupt.
  * @retval None
  */
void QSPI_ClearRxFIFOUnderflowInterrupt(void)
{
    uint32_t data;

    /* Read RXUICR register to Clear the Rx FIFO underflow interrupt */
    data = QSPI->RXUICR;
}

/**
  * @brief  Clears the QSPI Tx overflow/underflow,Rx overflow/underflow interrupt.
  * @retval None
  */
void QSPI_ClearFIFOFlowInterrupt(void)
{
    uint32_t data;

    /* Read ICR register to Clear the FIFO flow interrupt */
    data = QSPI->ICR;
}



/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
