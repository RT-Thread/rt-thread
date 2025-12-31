/**
  ******************************************************************************
  * @file               ft32f4xx_dma.c
  * @author             FMD AE
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of the Direct Memory Access controller (DMA):
  *                 + Initialization and Configuration
  *                 + Data Counter
  *                 + Interrupts and flags management
  *                 + Software Request
  * @version            V1.0.0
  * @data                   2025-04-15
    ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_dma.h"
#include "ft32f4xx_rcc.h"
/** @defgroup DMA
  * @brief DMA driver modules
  * @{
  */


/**
  * @brief  Initialize the DMA according to the specified
  *         parameters in the DMA_InitTypeDef and initialize the associated handle.
  * @param  DMAy_Channelx Where y can be 1 or 2 to select the DMA and x can be 0 to 7
  *                       for DMAy to select the DMA Channel.
  * @retval None
  */
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* Init)
{
    uint32_t tmp_high = 0;
    uint32_t tmp_low  = 0;

    /* Check the parameters */
    assert_param(IS_DMA_ALL_INSTANCE(DMAy_Channelx));
    assert_param(IS_DMA_SRC_DST_MASTER_SEL(Init->SrcDstMasterSel));
    assert_param(IS_DMA_TRANS_TYPE_FLOW_CTL(Init->TransferTypeFlowCtl));
    assert_param(IS_DMA_SRC_BURST_TRANS_LENGTH(Init->SrcBurstTransferLength));
    assert_param(IS_DMA_DST_BURST_TRANS_LENGTH(Init->DstBurstTransferLength));
    assert_param(IS_DMA_SRC_ADDR_MODE(Init->SrcAddrMode));
    assert_param(IS_DMA_DST_ADDR_MODE(Init->DstAddrMode));
    assert_param(IS_DMA_SRC_TRANS_WIDTH(Init->SrcTransferWidth));
    assert_param(IS_DMA_DST_TRANS_WIDTH(Init->DstTransferWidth));
    assert_param(IS_DMA_DST_HW_IF(Init->DstHardwareInterface));
    assert_param(IS_DMA_SRC_HW_IF(Init->SrcHardwareInterface));
    assert_param(IS_FUNCTIONAL_STATE(Init->FIFOMode));
    assert_param(IS_FUNCTIONAL_STATE(Init->FlowCtlMode));
    assert_param(IS_FUNCTIONAL_STATE(Init->ReloadDst));
    assert_param(IS_FUNCTIONAL_STATE(Init->ReloadSrc));
    assert_param(IS_DMA_SRC_HS_IF_POL(Init->SrcHsIfPol));
    assert_param(IS_DMA_DST_HS_IF_POL(Init->DstHsIfPol));
    assert_param(IS_DMA_SRC_HS_SEL(Init->SrcHsSel));
    assert_param(IS_DMA_DST_HS_SEL(Init->DstHsSel));
    assert_param(IS_DMA_CHANNEL_POLARITY(Init->Polarity));
    assert_param(IS_DMA_DST_HANDSHAKE_INTERFACE_SEL(Init->DstHsIfPeriphSel));
    assert_param(IS_DMA_SRC_HANDSHAKE_INTERFACE_SEL(Init->SrcHsIfPeriphSel));


    /* Calculate the base address and channel index of the DMA */
    DMA_BaseAddressAndChannelIndex DMA = CalBaseAddressAndChannelIndex(DMAy_Channelx);

    /* Config DMA source address */
    DMAy_Channelx->SAR = (uint64_t)Init->SrcAddress;

    /* Config DMA destination address */
    DMAy_Channelx->DAR = (uint64_t)Init->DstAddress;


    //tmp_high = (uint32_t)(DMAy_Channelx->CTL >> 32U);
    //tmp_low  = (uint32_t)(DMAy_Channelx->CTL);

    /* Prepare the DMA Channel configuration */
    tmp_high = (uint32_t)Init->BlockTransSize << 13U;

    tmp_low  = ((uint32_t)Init->SrcDstMasterSel        | Init->TransferTypeFlowCtl    |
                Init->SrcBurstTransferLength | Init->DstBurstTransferLength |
                Init->SrcAddrMode            | Init->DstAddrMode            |
                Init->SrcTransferWidth       | Init->DstTransferWidth) ;

    /* Write to DMA Channel CTL register */
    DMAy_Channelx->CTL = (((uint64_t)tmp_high << 32UL) | (uint64_t)tmp_low);


    //tmp_high = (uint32_t)(DMAy_Channelx->CFG >> 32U);
    //tmp_low  = (uint32_t)(DMAy_Channelx->CFG);
    tmp_high = 0;
    tmp_low  = 0;

    /* Prepare the DMA Channel configuration */
    tmp_high |= ((uint32_t)(Init->DstHardwareInterface << 11U) |
                 (Init->SrcHardwareInterface << 7U));

    if (Init->FIFOMode == ENABLE)
    {
        tmp_high |= (uint32_t)(DMA_CFG_FIFO_MODE >> 32U);
    }

    if (Init->FlowCtlMode == ENABLE)
    {
        tmp_high |= (uint32_t)(DMA_CFG_FCMODE >> 32U);
    }

    tmp_low |= ((uint32_t)(Init->MaxBurstLength << 20U) |
                (Init->SrcHsIfPol     << 19U) |
                (Init->DstHsIfPol     << 18U) |
                (Init->SrcHsSel       << 11U) |
                (Init->DstHsSel       << 10U) |
                (Init->Polarity       << 5U));

    if (Init->ReloadDst == ENABLE)
    {
        tmp_low |= (uint32_t)DMA_CFG_RELOAD_DST;
    }

    if (Init->ReloadSrc == ENABLE)
    {
        tmp_low |= (uint32_t)DMA_CFG_RELOAD_SRC;
    }

    /* Write to DMA Channel CFG register */
    DMAy_Channelx->CFG = (((uint64_t)tmp_high << 32UL) | (uint64_t)tmp_low);


    /* Select peripheral request for the handshake interface */
    DMA.BaseAddress->CHSEL |= (uint64_t)((Init->DstHsIfPeriphSel << (Init->DstHardwareInterface * 3UL)) |
                                         (Init->SrcHsIfPeriphSel << (Init->SrcHardwareInterface * 3UL)));
}


/**
  * @brief  Fills each DMA_StructInit member with its default value.
  * @param  DMA_StructInit: pointer to a DMA_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct)
{
    /*-------------- Reset DMA init structure parameters values ------------------*/
    /* Initialize the DMA source address */
    DMA_InitStruct->SrcAddress = 0U;

    /* Initialize the DMA destination address */
    DMA_InitStruct->DstAddress = 0U;

    /* Initialize the DMA block transfer size */
    DMA_InitStruct->BlockTransSize = 0U;

    /* Initialize the DMA source/destination master select */
    DMA_InitStruct->SrcDstMasterSel = DMA_SRCMASTER1_DSTMASTER1;

    /* Initialize the DMA transfer type and flow control */
    DMA_InitStruct->TransferTypeFlowCtl = DMA_TRANSFERTYPE_FLOWCTL_M2M_DMA;

    /* Initialize the DMA source burst transaction length */
    DMA_InitStruct->SrcBurstTransferLength = DMA_SRC_BURSTTRANSFERLENGTH_1;

    /* Initialize the DMA destination burst transaction length */
    DMA_InitStruct->DstBurstTransferLength = DMA_DST_BURSTTRANSFERLENGTH_1;

    /* Initialize the DMA source address increment */
    DMA_InitStruct->SrcAddrMode = DMA_SRC_ADDRMODE_INC;

    /* Initialize the DMA destination address increment */
    DMA_InitStruct->DstAddrMode = DMA_DST_ADDRMODE_INC;

    /* Initialize the DMA srouce transfer width */
    DMA_InitStruct->SrcTransferWidth = DMA_SRC_TRANSFERWIDTH_8BITS;

    /* Initialize the DMA destination transfer width */
    DMA_InitStruct->DstTransferWidth = DMA_DST_TRANSFERWIDTH_8BITS;


    /* Initialize the DMA destination hardware interface */
    DMA_InitStruct->DstHardwareInterface = DMA_DST_HARDWARE_INTERFACE_0;

    /* Initialize the DMA source hardware interface */
    DMA_InitStruct->SrcHardwareInterface = DMA_SRC_HARDWARE_INTERFACE_0;

    /* Initialize the DMA FIFO mode */
    DMA_InitStruct->FIFOMode = DISABLE;

    /* Initialize the DMA flow control mode */
    DMA_InitStruct->FlowCtlMode = DISABLE;

    /* Initialize the DMA automatic destination reload */
    DMA_InitStruct->ReloadDst = DISABLE;

    /* Initialize the DMA automatic source reload */
    DMA_InitStruct->ReloadSrc = DISABLE;

    /* Initialize the DMA maximum AMBA burst length */
    DMA_InitStruct->MaxBurstLength = 0U;

    /* Initialize the DMA source handshaking interface polarity */
    DMA_InitStruct->SrcHsIfPol = DMA_SRCHSIFPOL_HIGH;

    /* Initialize the DMA destination handshaking interface polarity */
    DMA_InitStruct->DstHsIfPol = DMA_DSTHSIFPOL_HIGH;

    /* Initialize the DMA source software or handware handshaking */
    DMA_InitStruct->SrcHsSel = DMA_SRCHSSEL_HARDWARE;

    /* Initialize the DMA destination software or handware handshaking */
    DMA_InitStruct->DstHsSel = DMA_DSTHSSEL_HARDWARE;

    /* Initialize the DMA channel polarity */
    DMA_InitStruct->Polarity = DMA_CH_POLARITY_0;

    /* Initialize the destination peripheral request */
    DMA_InitStruct->DstHsIfPeriphSel = DMA_DST_HANDSHAKE_INTERFACE_SEL_0;

    /* Initialize the source peripheral request */
    DMA_InitStruct->SrcHsIfPeriphSel = DMA_SRC_HANDSHAKE_INTERFACE_SEL_0;

}


/**
  * @brief  DeInitialize the DMA peripheral.
  * @param  DMAy_Channelx Where y can be 1 or 2 to select the DMA and x can be 0 to 7
  *                       for DMAy to select the DMA Channel.
  * @retval None
  */
void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_INSTANCE(DMAy_Channelx));


    /* Calculate the base address and channel index of the DMA */
    DMA_BaseAddressAndChannelIndex DMA = CalBaseAddressAndChannelIndex(DMAy_Channelx);


    if (DMA.BaseAddress == DMA1)
    {
        /* Enable DMA1 reset state */
        RCC_AHB1PeriphResetCmd(RCC_AHB1PeriphRst_DMA1, ENABLE);

        /* Release DMA1 from reset state */
        RCC_AHB1PeriphResetCmd(RCC_AHB1PeriphRst_DMA1, DISABLE);
    }
    else if (DMA.BaseAddress == DMA2)
    {
        /* Enable DMA2 reset state */
        RCC_AHB1PeriphResetCmd(RCC_AHB1PeriphRst_DMA2, ENABLE);

        /* Release DMA2 from reset state */
        RCC_AHB1PeriphResetCmd(RCC_AHB1PeriphRst_DMA2, DISABLE);
    }

}


/**
  * @brief  Return the DMA base address and channel index depending on DMAy_Channelx.
  * @param  DMAy_Channelx  Where y can be 1 or 2 to select the DMA and x can be 0 to 7
  *                        for DMAy to select the DMA Channel.
  * @retval DMA base address and channel index.
  */
DMA_BaseAddressAndChannelIndex CalBaseAddressAndChannelIndex(DMA_Channel_TypeDef* DMAy_Channelx)
{
    DMA_BaseAddressAndChannelIndex DMA;

    /* Compute the channel index */
    if ((uint32_t)(DMAy_Channelx) < (uint32_t)(DMA2_Channel0))
    {
        /* DMA1 */
        DMA.ChannelIndex = (((uint32_t)DMAy_Channelx - (uint32_t)DMA1_Channel0) / ((uint32_t)DMA1_Channel2 - (uint32_t)DMA1_Channel1));
        DMA.BaseAddress = DMA1;
    }
    else
    {
        /* DMA2 */
        DMA.ChannelIndex = (((uint32_t)DMAy_Channelx - (uint32_t)DMA2_Channel0) / ((uint32_t)DMA2_Channel2 - (uint32_t)DMA2_Channel1));
        DMA.BaseAddress = DMA2;
    }

    return DMA;
}


/**
  * @brief  Enables or disables the specified DMAy Channelx.
  * @param  DMAy_Channelx Where y can be 1 or 2 to select the DMA and x can be 0 to 7
  *                       for DMAy to select the DMA Channel.
  * @param  NewState      New state of the DMAy Channelx.
  *                       This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_INSTANCE(DMAy_Channelx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Calculate the base address and channel index of the DMA */
    DMA_BaseAddressAndChannelIndex DMA = CalBaseAddressAndChannelIndex(DMAy_Channelx);

    if (NewState != DISABLE)
    {
        /* Enable the Peripheral */
        DMA_ENABLE(DMA.BaseAddress);
        /* Enable the DMA Channel */
        DMA_Channel_Cmd(DMAy_Channelx, ENABLE);
    }
    else
    {
        /* Disable the DMA Channel */
        DMA_Channel_Cmd(DMAy_Channelx, DISABLE);
        /* Disable the Peripheral */
        DMA_DISABLE(DMA.BaseAddress);
    }

}


/**
  * @brief  Returns the number of data units transferred by the current DMAy Channelx.
  * @param  DMAy_Channelx Where y can be 1 or 2 to select the DMA and x can be 0 to 7
  *                       for DMAy to select the DMA Channel.
  * @retval The number of data units transferred by the current DMAy Channelx.
  */
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_INSTANCE(DMAy_Channelx));

    /* Return the number of remaining data units for DMAy Channelx */
    return ((uint16_t)((DMAy_Channelx->CTL) >> 45U));
}


/**
  * @brief  Enable the specified DMA Channel interrupts.
  * @param  DMAy_Channelx Where y can be 1 or 2 to select the DMA and x can be 0 to 7
  *                       for DMAy to select the DMA Channel.
  * @param  DMA_IT specifies the DMA interrupt sources to be enabled or disabled.
  *                This parameter can be any combination of the following values:
  *                @arg DMA_IT_TFR    Transfer complete interrupt mask
  *                @arg DMA_IT_BLOCK  Block transfer complete interrupt mask
  *                @arg DMA_IT_SRC    Source transfer complete interrupt mask
  *                @arg DMA_IT_DST    Destination transfer complete interrupt mask
  *                @arg DMA_IT_ERR    Transfer error interrupt mask
  * @retval None
  */
void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, uint8_t DMA_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_INSTANCE(DMAy_Channelx));
    assert_param(IS_DMA_IT(DMA_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));


    /* Calculate the base address and channel index of the DMA */
    DMA_BaseAddressAndChannelIndex DMA = CalBaseAddressAndChannelIndex(DMAy_Channelx);

    /* Config channel interrupt mask */
    const uint32_t ch_mask = (1U << (DMA.ChannelIndex));
    const uint32_t ch_en_mask = (0x100U << (DMA.ChannelIndex));

    /* Config channelx transfer complete interrupt */
    if ((DMA_IT & DMA_IT_TFR) != 0U)
    {
        (NewState) ? (DMA.BaseAddress->MASKTFR |= (ch_en_mask | ch_mask))
        : (DMA.BaseAddress->MASKTFR &= (ch_en_mask | (~ch_mask)));
    }

    /* Config channelx block transfer complete interrupt */
    if ((DMA_IT & DMA_IT_BLOCK) != 0U)
    {
        (NewState) ? (DMA.BaseAddress->MASKBLOCK |= (ch_en_mask | ch_mask))
        : (DMA.BaseAddress->MASKBLOCK &= (ch_en_mask | (~ch_mask)));
    }

    /* Config channelx source transfer complete interrupt */
    if ((DMA_IT & DMA_IT_SRC) != 0U)
    {
        (NewState) ? (DMA.BaseAddress->MASKSRCTRAN |= (ch_en_mask | ch_mask))
        : (DMA.BaseAddress->MASKSRCTRAN &= (ch_en_mask | (~ch_mask)));
    }

    /* Config channelx destination transfer complete interrupt */
    if ((DMA_IT & DMA_IT_DST) != 0U)
    {
        (NewState) ? (DMA.BaseAddress->MASKDSTTRAN |= (ch_en_mask | ch_mask))
        : (DMA.BaseAddress->MASKDSTTRAN &= (ch_en_mask | (~ch_mask)));
    }

    /* Config channelx transfer error interrupt */
    if ((DMA_IT & DMA_IT_ERR) != 0U)
    {
        (NewState) ? (DMA.BaseAddress->MASKERR |= (ch_en_mask | ch_mask))
        : (DMA.BaseAddress->MASKERR &= (ch_en_mask | (~ch_mask)));
    }

    /* Config global interrupt */
    const uint8_t int_en_bit = 0x01;  //CTL[0]
    if (NewState == ENABLE)
    {
        /* Enable global interrupt */
        DMAy_Channelx->CTL |= (uint64_t)int_en_bit;
    }
    else
    {
        // Check all interrupts are disabled.
        if (!(DMA.BaseAddress->MASKTFR     & ch_mask) &&
                !(DMA.BaseAddress->MASKBLOCK   & ch_mask) &&
                !(DMA.BaseAddress->MASKSRCTRAN & ch_mask) &&
                !(DMA.BaseAddress->MASKDSTTRAN & ch_mask) &&
                !(DMA.BaseAddress->MASKERR     & ch_mask))
        {
            /* Disable global interrupt */
            DMAy_Channelx->CTL &= ~(uint64_t)int_en_bit;
        }
    }
}


/**
  * @brief  Clears the DMA interrupt flags.
  * @param  DMAy_Channelx Where y can be 1 or 2 to select the DMA and x can be 0 to 7
  *                       for DMAy to select the DMA Channel.
  * @param  DMA_IT  specifies DMA interrupt flag to clear.
  *                 This parameter can be one of the following values:
  *                 @arg DMA_IT_TFR    Transfer complete flag.
  *                 @arg DMA_IT_BLOCK  Block transfer complete flag.
  *                 @arg DMA_IT_SRC    Source transfer complete flag.
  *                 @arg DMA_IT_DST    Destination transfer complete flag.
  *                 @arg DMA_IT_ERR    Transfer error flag.
  * @retval None
  */
void DMA_ClearFlagStatus(DMA_Channel_TypeDef* DMAy_Channelx, uint8_t DMA_IT)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_INSTANCE(DMAy_Channelx));
    assert_param(IS_DMA_IT(DMA_IT));


    /* Calculate the base address and channel index of the DMA */
    DMA_BaseAddressAndChannelIndex DMA = CalBaseAddressAndChannelIndex(DMAy_Channelx);

    /* Config channel mask */
    const uint32_t ch_mask = (1U << (DMA.ChannelIndex));

    /* Clear channelx transfer complete interrupt */
    if ((DMA_IT & DMA_IT_TFR) != 0U)
    {
        DMA.BaseAddress->CLEARTFR = ch_mask;
    }
    /* Clear channelx block transfer complete interrupt */
    if ((DMA_IT & DMA_IT_BLOCK) != 0U)
    {
        DMA.BaseAddress->CLEARBLOCK = ch_mask;
    }
    /* Clear channelx source transfer complete interrupt */
    if ((DMA_IT & DMA_IT_SRC) != 0U)
    {
        DMA.BaseAddress->CLEARSRCTRAN = ch_mask;
    }
    /* Clear channelx destination transfer complete interrupt */
    if ((DMA_IT & DMA_IT_DST) != 0U)
    {
        DMA.BaseAddress->CLEARDSTTRAN = ch_mask;
    }
    /* Clear channelx transfer error interrupt */
    if ((DMA_IT & DMA_IT_ERR) != 0U)
    {
        DMA.BaseAddress->CLEARERR = ch_mask;
    }
}


/**
  * @brief  Checks whether the specified DMAy Channelx interrupt has occurred or not.
  * @param  DMAy_Channelx Where y can be 1 or 2 to select the DMA and x can be 0 to 7
  *                       for DMAy to select the DMA Channel.
  * @param  DMA_IT  specifies the DMA interrupt source to check
  *                 This parameter can be one of the following values:
  *                 @arg DMA_IT_TFR    Transfer complete interrupt.
  *                 @arg DMA_IT_BLOCK  Block transfer complete interrupt.
  *                 @arg DMA_IT_SRC    Source transfer complete interrupt.
  *                 @arg DMA_IT_DST    Destination transfer complete interrupt.
  *                 @arg DMA_IT_ERR    Transfer error interrupt.
  * @retval The new state of DMA_IT (SET or RESET).
  */
ITStatus DMA_GetITStatus(DMA_Channel_TypeDef* DMAy_Channelx, uint8_t DMA_IT)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_INSTANCE(DMAy_Channelx));
    assert_param(IS_DMA_IT(DMA_IT));

    ITStatus bitstatus = RESET;
    uint32_t tmpreg = 0;

    /* Calculate the base address and channel index of the DMA */
    DMA_BaseAddressAndChannelIndex DMA = CalBaseAddressAndChannelIndex(DMAy_Channelx);

    /* Config channel mask */
    const uint32_t ch_mask = (1U << (DMA.ChannelIndex));

    /* Get DMA IT Status register value */
    /* Get channelx transfer complete interrupt status */
    if ((DMA_IT & DMA_IT_TFR) != 0U)
    {
        tmpreg = DMA.BaseAddress->STATUSTFR;
    }

    /* Get channelx block transfer complete interrupt status */
    if ((DMA_IT & DMA_IT_BLOCK) != 0U)
    {
        tmpreg = DMA.BaseAddress->STATUSBLOCK;
    }

    /* Get channelx source transfer complete interrupt status */
    if ((DMA_IT & DMA_IT_SRC) != 0U)
    {
        tmpreg = DMA.BaseAddress->STATUSSRCTRAN;
    }

    /* Get channelx destination transfer complete interrupt status */
    if ((DMA_IT & DMA_IT_DST) != 0U)
    {
        tmpreg = DMA.BaseAddress->STATUSDSTTRAN;
    }

    /* Get channelx transfer error interrupt status */
    if ((DMA_IT & DMA_IT_ERR) != 0U)
    {
        tmpreg = DMA.BaseAddress->STATUSERR;
    }

    /* Check the status of the specified DMAy interrupt */
    if ((tmpreg & ch_mask) != (uint32_t)RESET)
    {
        /* DMA_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* DMA_IT is reset */
        bitstatus = RESET;
    }
    /* Return the DMA_IT status */
    return  bitstatus;
}


/**
  * @brief  Checks whether the specified DMAy Channelx flag has occurred or not.
  * @param  DMAy_Channelx Where y can be 1 or 2 to select the DMA and x can be 0 to 7
  *                       for DMAy to select the DMA Channel.
  * @param  DMA_FLAG  specifies the DMA flag to check
  *                   This parameter can be one of the following values:
  *                   @arg DMA_IT_TFR    Transfer complete flag.
  *                   @arg DMA_IT_BLOCK  Block transfer complete flag.
  *                   @arg DMA_IT_SRC    Source transfer complete flag.
  *                   @arg DMA_IT_DST    Destination transfer complete flag.
  *                   @arg DMA_IT_ERR    Transfer error flag.
  * @retval The new state of DMA_FLAG (SET or RESET).
  */
FlagStatus DMA_GetFlagStatus(DMA_Channel_TypeDef* DMAy_Channelx, uint8_t DMA_FLAG)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_INSTANCE(DMAy_Channelx));
    assert_param(IS_DMA_FLAG(DMA_FLAG));

    FlagStatus bitstatus = RESET;
    uint32_t tmpreg = 0;

    /* Calculate the base address and channel index of the DMA */
    DMA_BaseAddressAndChannelIndex DMA = CalBaseAddressAndChannelIndex(DMAy_Channelx);

    /* Config channel mask */
    const uint32_t ch_mask = (1U << (DMA.ChannelIndex));

    /* Get DMA IT Status register value */
    /* Get channelx transfer complete interrupt status */
    if ((DMA_FLAG & DMA_FLAG_TFR) != 0U)
    {
        tmpreg = DMA.BaseAddress->RAWTFR;
    }

    /* Get channelx block transfer complete interrupt status */
    if ((DMA_FLAG & DMA_FLAG_BLOCK) != 0U)
    {
        tmpreg = DMA.BaseAddress->RAWBLOCK;
    }

    /* Get channelx source transfer complete interrupt status */
    if ((DMA_FLAG & DMA_FLAG_SRC) != 0U)
    {
        tmpreg = DMA.BaseAddress->RAWSRCTRAN;
    }

    /* Get channelx destination transfer complete interrupt status */
    if ((DMA_FLAG & DMA_FLAG_DST) != 0U)
    {
        tmpreg = DMA.BaseAddress->RAWDSTTRAN;
    }

    /* Get channelx transfer error interrupt status */
    if ((DMA_FLAG & DMA_FLAG_ERR) != 0U)
    {
        tmpreg = DMA.BaseAddress->RAWERR;
    }

    /* Check the status of the specified DMAy interrupt */
    if ((tmpreg & ch_mask) != (uint32_t)RESET)
    {
        /* DMA_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* DMA_FLAG is reset */
        bitstatus = RESET;
    }
    /* Return the DMA_FLAG status */
    return  bitstatus;
}


/**
  * @brief  Enable or disable the specified DMA Channel.
  * @param  DMAy_Channelx Where y can be 1 or 2 to select the DMA and x can be 0 to 7
  *                       for DMAy to select the DMA Channel.
  * @param  NewState  new state of the specified DMA Channel.
  *                   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DMA_Channel_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_INSTANCE(DMAy_Channelx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));


    /* Calculate the base address and channel index of the DMA */
    DMA_BaseAddressAndChannelIndex DMA = CalBaseAddressAndChannelIndex(DMAy_Channelx);

    /* Config channel mask */
    const uint32_t ch_mask    = (1U     << (DMA.ChannelIndex));
    const uint32_t ch_en_mask = (0x100U << (DMA.ChannelIndex));

    if (NewState != DISABLE)
    {
        DMA.BaseAddress->CHEN |= (ch_en_mask | ch_mask);
        DMA.BaseAddress->CHEN &= ~ch_en_mask;
    }
    else
    {
        DMA.BaseAddress->CHEN |= ch_en_mask;
        DMA.BaseAddress->CHEN &= ~ch_mask;
        DMA.BaseAddress->CHEN &= ~ch_en_mask;
    }
}


/**
  * @brief  Sets software request.
  * @param  DMAy_Channelx Where y can be 1 or 2 to select the DMA and x can be 0 to 7
  *                       for DMAy to select the DMA Channel.
  * @param  SoftwareRequest  The specified software request.
  *                          This parameter can be one of the following values:
  *                          DMA_SW_REQUEST_SRC      DMA source software transaction request
  *                          DMA_SW_REQUEST_DST      DMA destination software transaction request
  *                          DMA_SW_REQUEST_SRC_SGL  DMA source single transaction request
  *                          DMA_SW_REQUEST_DST_SGL  DMA destination single transaction request
  *                          DMA_SW_REQUEST_SRC_LST  DMA source last transaction request
  *                          DMA_SW_REQUEST_DST_LST  DMA destination last transaction request
  * @retval None
  */
void DMA_SoftWare_Request(DMA_Channel_TypeDef* DMAy_Channelx, DMA_SoftwareRequestTypeDef SoftwareRequest)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_INSTANCE(DMAy_Channelx));
    assert_param(IS_DMA_SOFTWARE_REQUEST(SoftwareRequest));


    /* Calculate the base address and channel index of the DMA */
    DMA_BaseAddressAndChannelIndex DMA = CalBaseAddressAndChannelIndex(DMAy_Channelx);

    /* Config channel mask */
    const uint32_t ch_mask    = (1U     << (DMA.ChannelIndex));
    const uint32_t ch_en_mask = (0x100U << (DMA.ChannelIndex));

    /* Config the source software transaction request */
    if (SoftwareRequest == DMA_SW_REQUEST_SRC)
    {
        DMA.BaseAddress->REQSRC |= (ch_en_mask | ch_mask);
    }

    /* Config the destination software transaction request */
    if (SoftwareRequest == DMA_SW_REQUEST_DST)
    {
        DMA.BaseAddress->REQDST |= (ch_en_mask | ch_mask);
    }

    /* Config the source single transaction request */
    if (SoftwareRequest == DMA_SW_REQUEST_SRC_SGL)
    {
        DMA.BaseAddress->SGLRQSRC |= (ch_en_mask | ch_mask);
    }

    /* Config the destination single transaction request */
    if (SoftwareRequest == DMA_SW_REQUEST_DST_SGL)
    {
        DMA.BaseAddress->SGLRQDST |= (ch_en_mask | ch_mask);
    }

    /* Config the source last transaction request */
    if (SoftwareRequest == DMA_SW_REQUEST_SRC_LST)
    {
        DMA.BaseAddress->LSTSRC |= (ch_en_mask | ch_mask);
    }

    /* Config the destination last transaction request */
    if (SoftwareRequest == DMA_SW_REQUEST_DST_LST)
    {
        DMA.BaseAddress->LSTDST |= (ch_en_mask | ch_mask);
    }
}


/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
