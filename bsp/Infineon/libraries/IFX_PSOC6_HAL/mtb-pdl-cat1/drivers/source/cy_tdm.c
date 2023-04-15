/***************************************************************************//**
* \file cy_tdm.c
* \version 1.0
*
* Provides an API implementation of the audio dac driver.
*
********************************************************************************
* \copyright
* Copyright 2021, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "cy_device.h"

#if defined (CY_IP_MXTDM)

#include "cy_tdm.h"
#include <stdlib.h>

#if defined(__cplusplus)
extern "C" {

#endif /* __cplusplus */


cy_en_tdm_status_t Cy_AudioTDM_TX_Init( TDM_TX_STRUCT_Type * base, cy_stc_tdm_config_tx_t const * config);
void Cy_AudioTDM_TX_DeInit( TDM_TX_STRUCT_Type * base);

cy_en_tdm_status_t Cy_AudioTDM_RX_Init( TDM_RX_STRUCT_Type * base, cy_stc_tdm_config_rx_t const * config);
void Cy_AudioTDM_RX_DeInit( TDM_RX_STRUCT_Type * base);

/**
* \addtogroup group_tdm_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_AudioTDM_Init
****************************************************************************//**
*
* Initializes the TDM module in accordance with a configuration structure.
*
* \pre If the TDM module is initialized previously, the \ref Cy_AudioTDM_DeInit()
* must be called before calling this function.
*
* \param base The pointer to the TDM instance address.
*
* \param config The pointer to a configuration structure.
*
* \return error / status code. See \ref cy_en_tdm_status_t.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_Init
*
*******************************************************************************/
cy_en_tdm_status_t Cy_AudioTDM_Init( TDM_STRUCT_Type * base, cy_stc_tdm_config_t const * config)
{
    cy_en_tdm_status_t ret = CY_TDM_BAD_PARAM;

    if((NULL != base) && (NULL != config))
    {
       if(config->tx_config->enable)
       {
           ret = Cy_AudioTDM_TX_Init(&(base->TDM_TX_STRUCT),(config->tx_config));
           if(ret == CY_TDM_BAD_PARAM)
           {
               return(ret);
           }
       }
       if(config->rx_config->enable)
       {
            ret = Cy_AudioTDM_RX_Init(&(base->TDM_RX_STRUCT),(config->rx_config));
       }
    }
    return (ret);
}

/** \} group_tdm_functions */

/**************************************************************************/
/* Function Name: Cy_AudioTDM_TX_Init                                     */
/**************************************************************************/
/*
* Initializes the TDM Transmitter module in accordance with a configuration structure.
*
* \pre If the TDM TX module is initialized previously, the \ref Cy_AudioTX_Tx_DeInit()
* must be called before calling this function.
*
* \param base The pointer to the TDM->TX instance address.
*
* \param config The pointer to a configuration structure.
*
* \return error / status code. See \ref cy_en_tdm_status_t.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_Init
*
****************************************************************************/
cy_en_tdm_status_t Cy_AudioTDM_TX_Init( TDM_TX_STRUCT_Type * base, cy_stc_tdm_config_tx_t const * config)
{
    cy_en_tdm_status_t          ret     = CY_TDM_SUCCESS;
    uint16_t clockDiv = config->clkDiv -1U;
    uint8_t channelNum = config->channelNum - 1U;
    uint8_t channelSIZE = config->channelSize - 1U;
    CY_ASSERT_L2(base);
    CY_ASSERT_L2(config);
    CY_ASSERT_L2(CY_TDM_IS_CLK_DIV_VALID(clockDiv));
    CY_ASSERT_L2(CY_TDM_IS_CHANNELS_VALID(channelNum));
    CY_ASSERT_L2(CY_TDM_IS_CHANNEL_SIZE_VALID(channelSIZE));
    CY_ASSERT_L2(CY_I2S_TDM_IS_INPUT_SIGNAL_MODE_VALID(config->signalInput));

    /* Channel Default */
    if((bool)(TDM_STRUCT_TX_CTL(base) & TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_CTL_ENABLED_Msk))
    {
        ret = CY_TDM_BAD_PARAM;
        return(ret);
    }

    /* The TX interface setting */
    TDM_STRUCT_TX_IF_CTL(base) =
        _VAL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_CLOCK_DIV,         clockDiv)               |
        _VAL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_CLOCK_SEL,         config->clkSel)         |
        _VAL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_SCK_POLARITY,     config->sckPolarity)     |
        _VAL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_FSYNC_POLARITY, config->fsyncPolarity)     |
        _VAL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_FSYNC_FORMAT,     config->fsyncFormat)     |
        _VAL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_CH_NR,             channelNum)             |
        _VAL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_CH_SIZE,         channelSIZE)              |
        _BOOL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_I2S_MODE,         config->i2sMode);

    if(!((bool)(config->masterMode)))
    {
        TDM_STRUCT_TX_ROUTE_CTL(base) = _VAL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_ROUTE_CTL_MODE, config->signalInput);
    }

    /* Chanel Enable */
    TDM_STRUCT_TX_CH_CTL(base) = config->chEn;
    /* The FIFO setting */
    TDM_STRUCT_TX_FIFO_CTL(base) = _VAL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_CTL_TRIGGER_LEVEL,config->fifoTriggerLevel);
    /* The TC Interface setting */
    TDM_STRUCT_TX_CTL(base) =
        _VAL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_CTL_WORD_SIZE,    config->wordSize) |
        _VAL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_CTL_FORMAT,     config->format)     |
        _VAL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_CTL_MS, config->masterMode);

    return (ret);
}

/**************************************************************************/
/* Function Name: Cy_AudioTDM_RX_Init                                     */
/**************************************************************************/
cy_en_tdm_status_t Cy_AudioTDM_RX_Init( TDM_RX_STRUCT_Type * base, cy_stc_tdm_config_rx_t const * config)
{
    cy_en_tdm_status_t ret = CY_TDM_SUCCESS;
    uint16_t clockDiv   = config->clkDiv - 1U;
    uint8_t channelSIZE = config->channelSize - 1U;
    uint8_t channelNum  = config->channelNum - 1U;
    CY_ASSERT_L2(base);
    CY_ASSERT_L2(config);
    CY_ASSERT_L2(CY_TDM_IS_CLK_DIV_VALID(clockDiv));
    CY_ASSERT_L2(CY_TDM_IS_CHANNELS_VALID(channelNum));
    CY_ASSERT_L2(CY_TDM_IS_CHANNEL_SIZE_VALID(channelSIZE));
    CY_ASSERT_L2(CY_I2S_TDM_IS_INPUT_SIGNAL_MODE_VALID(config->signalInput));

    /* The RX interface setting */
    TDM_STRUCT_RX_IF_CTL(base) =
        _VAL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_CLOCK_DIV,         clockDiv)             |
        _VAL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_CLOCK_SEL,         config->clkSel)       |
        _VAL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_SCK_POLARITY,     config->sckPolarity)   |
        _VAL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_FSYNC_POLARITY, config->fsyncPolarity)   |
        _VAL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_LATE_SAMPLE,     config->lateSample)     |
        _VAL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_FSYNC_FORMAT,     config->fsyncFormat)   |
        _VAL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_CH_NR,             channelNum)           |
        _VAL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_CH_SIZE,         channelSIZE)            |
        _BOOL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_I2S_MODE,         config->i2sMode);

    if(!((bool)(config->masterMode)))
    {
        TDM_STRUCT_RX_ROUTE_CTL(base) = _VAL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_ROUTE_CTL_MODE, config->signalInput);
    }

    /* Chanel Enable */
    TDM_STRUCT_RX_CH_CTL(base) = config->chEn;
    /* The FIFO setting */
    TDM_STRUCT_RX_FIFO_CTL(base) = _VAL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_FIFO_CTL_TRIGGER_LEVEL,config->fifoTriggerLevel);
    /* The TC Interface setting */
    TDM_STRUCT_RX_CTL(base) =
        _VAL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_CTL_WORD_SIZE,            config->wordSize)   |
        _VAL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_CTL_WORD_SIGN_EXTEND,    config->signExtend) |
        _VAL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_CTL_FORMAT,             config->format)     |
        _VAL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_CTL_MS, config->masterMode);

    return (ret);
}

/**
* \addtogroup group_tdm_functions
* \{
*/


/*******************************************************************************
* Function Name: Cy_AudioTDM_DeInit
****************************************************************************//**
* Deinitialize the TDM block.
*
* \param base base
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_DeInit
*******************************************************************************/
void Cy_AudioTDM_DeInit( TDM_STRUCT_Type * base)
{
    Cy_AudioTDM_TX_DeInit(&(base->TDM_TX_STRUCT));
    Cy_AudioTDM_RX_DeInit(&(base->TDM_RX_STRUCT));
}

/** \} group_tdm_functions */

/**************************************************************************/
/* Function Name: Cy_AudioTDM_TX_DeInit                                   */
/**************************************************************************/
void Cy_AudioTDM_TX_DeInit( TDM_TX_STRUCT_Type * base)
{
    TDM_STRUCT_TX_INTR_TX_MASK(base)    = 0UL;
    TDM_STRUCT_TX_FIFO_CTL(base)        = 0UL;
    TDM_STRUCT_TX_IF_CTL(base)            = CY_TDM_TX_IF_CTL_DEFAULT;
    TDM_STRUCT_TX_CTL(base)                = CY_TDM_TX_CTL_DEFAULT;
}

/**************************************************************************/
/* Function Name: Cy_AudioTDM_RX_DeInit                                   */
/**************************************************************************/
void Cy_AudioTDM_RX_DeInit( TDM_RX_STRUCT_Type * base)
{
    TDM_STRUCT_RX_INTR_RX_MASK(base)    = 0UL;
    TDM_STRUCT_RX_FIFO_CTL(base)        = 0UL;
    TDM_STRUCT_RX_IF_CTL(base)            = CY_TDM_RX_IF_CTL_DEFAULT;
    TDM_STRUCT_RX_CTL(base)                = CY_TDM_RX_CTL_DEFAULT;
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */


#endif /* CY_IP_MXTDM */
/******************************************************************************/
/* [] END OF FILE */
/******************************************************************************/
