/***************************************************************************//**
* \file cy_lin.c
* \version 1.1
*
* \brief
* Provides an API declaration of the LIN driver
*
********************************************************************************
* \copyright
* Copyright 2020-2021, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "cy_device.h"
#if defined (CY_IP_MXLIN)
/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "cy_lin.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/


/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/


/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/


/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/


/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/
/**
 *****************************************************************************
 ** Cy_LIN_DeInit
 ** DeInitialization of a LIN module.
 ** This Function deinitializes the selected LIN channel.
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_DeInit( LIN_CH_Type* base )
{
    cy_en_lin_status_t status = CY_LIN_SUCCESS;

    /* Check if pointers are valid */
    if ( NULL == base )
    {
        return CY_LIN_BAD_PARAM;
    }

    /* Disable the LIN Channel and set the values to default. */
    LIN_CH_CTL0(base) = LIN_CH_CTL0_DEFAULT;

    /* Clear the data registers */
    LIN_CH_DATA0(base) = 0UL;
    LIN_CH_DATA0(base) = 0UL;

    /* Clear the PID filed */
    LIN_CH_PID_CHECKSUM(base) &= ~(LIN_CH_PID_CHECKSUM_PID_Msk);

    return status;
}

/**
 *****************************************************************************
 ** Cy_LIN_Init
 ** Initialization of a LIN module.
 ** This function initializes the LIN according the Options setup in the
 ** passed Config Struct. Several Checkings are done before that and an error
 ** is returned if invalid Modes are requested.
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_Init( LIN_CH_Type* base, const cy_stc_lin_config_t *pstcConfig)
{
    cy_en_lin_status_t status = CY_LIN_SUCCESS;

    /* Check if pointers are valid */
    if ( ( NULL == base  )     ||
         ( NULL == pstcConfig ) )
    {
        status = CY_LIN_BAD_PARAM;
    }
    else if (pstcConfig->masterMode &&
             ((LIN_MASTER_BREAK_FILED_LENGTH_MIN > pstcConfig->breakFieldLength) ||
              (LIN_BREAK_WAKEUP_LENGTH_BITS_MAX < pstcConfig->breakFieldLength)))
    {
        status = CY_LIN_BAD_PARAM;
    }
    else if (LIN_BREAK_WAKEUP_LENGTH_BITS_MAX < pstcConfig->breakFieldLength)
    {
        status = CY_LIN_BAD_PARAM;
    }
    else
    {
        LIN_CH_CTL0(base) =  (_VAL2FLD(LIN_CH_CTL0_STOP_BITS, pstcConfig->stopBit) | \
                              _VAL2FLD(LIN_CH_CTL0_AUTO_EN,  pstcConfig->linTransceiverAutoEnable) | \
                              _VAL2FLD(LIN_CH_CTL0_BREAK_DELIMITER_LENGTH, pstcConfig->breakDelimiterLength) | \
                              _VAL2FLD(LIN_CH_CTL0_BREAK_WAKEUP_LENGTH, (((uint32_t)pstcConfig->breakFieldLength) - 1U)) | \
                              _VAL2FLD(LIN_CH_CTL0_MODE, LIN_CH_CTL0_MODE_DEFAULT) | \
                              _VAL2FLD(LIN_CH_CTL0_BIT_ERROR_IGNORE, LIN_CH_CTL0_BIT_ERROR_IGNORE_DEFAULT) | \
                              _VAL2FLD(LIN_CH_CTL0_PARITY, LIN_CH_CTL0_PARITY_DEFAULT) | \
                              _VAL2FLD(LIN_CH_CTL0_PARITY_EN, LIN_CH_CTL0_PARITY_EN_DEFAULT) | \
                              _VAL2FLD(LIN_CH_CTL0_FILTER_EN, pstcConfig->filterEnable) | \
                              _VAL2FLD(LIN_CH_CTL0_ENABLED, 1U));

    }

    return status;
}

/**
 *****************************************************************************
 ** Cy_LIN_ReadData.
 ** Read response data.
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_ReadData( LIN_CH_Type* base, uint8_t  *data )
{
    cy_en_lin_status_t status = CY_LIN_SUCCESS;
    uint8_t cnt;
    uint8_t length;
    uint8_t data0[4];
    uint8_t data1[4];

    /* Check if pointers are valid */
    if( ( NULL == base )           ||
        ( NULL == data ))
    {
        status = CY_LIN_BAD_PARAM;
    }
    /* Check if the response is received successfully */
    else if( ( 0U == _FLD2VAL(LIN_CH_CMD_TX_RESPONSE, LIN_CH_CMD(base)))  &&
             ( 0u == _FLD2VAL(LIN_CH_STATUS_RX_BUSY, LIN_CH_STATUS(base))))
    {
        length = (uint8_t)(_FLD2VAL(LIN_CH_CTL1_DATA_NR, LIN_CH_CTL1(base)) + 1U);
        /* Copy the data in to u8Data array */
        data0[0] = (uint8_t)_FLD2VAL(LIN_CH_DATA0_DATA1, LIN_CH_DATA0(base));
        data0[1] = (uint8_t)_FLD2VAL(LIN_CH_DATA0_DATA2, LIN_CH_DATA0(base));
        data0[2] = (uint8_t)_FLD2VAL(LIN_CH_DATA0_DATA3, LIN_CH_DATA0(base));
        data0[3] = (uint8_t)_FLD2VAL(LIN_CH_DATA0_DATA4, LIN_CH_DATA0(base));
        data1[0] = (uint8_t)_FLD2VAL(LIN_CH_DATA1_DATA5, LIN_CH_DATA1(base));
        data1[1] = (uint8_t)_FLD2VAL(LIN_CH_DATA1_DATA6, LIN_CH_DATA1(base));
        data1[2] = (uint8_t)_FLD2VAL(LIN_CH_DATA1_DATA7, LIN_CH_DATA1(base));
        data1[3] = (uint8_t)_FLD2VAL(LIN_CH_DATA1_DATA8, LIN_CH_DATA1(base));
        for ( cnt = 0; cnt < length; cnt++ )
        {
            if( 4U > cnt )
            {
                data[cnt] = data0[cnt];
            }
            else
            {
                data[cnt] = data1[cnt - 4U];
            }
        }
    }
    else
    {
        status = CY_LIN_BUSY;
    }

    return status;
}

/**
 *****************************************************************************
 ** Cy_LIN_WriteData
 ** Write response data.
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_WriteData( LIN_CH_Type* base, const uint8_t *data,
                                  uint8_t dataLength )
{
    cy_en_lin_status_t status = CY_LIN_SUCCESS;
    uint8_t data0[4U] = { 0 };
    uint8_t data1[4U] = { 0 };
    uint8_t cnt;

    /* Check if NULL pointer */
    if( ( NULL == base ) ||
        ( NULL == data ) )
    {
        status = CY_LIN_BAD_PARAM;
    }
    /* Check if data length is valid */
    else if( LIN_DATA_LENGTH_MAX < dataLength )
    {
        status = CY_LIN_BAD_PARAM;
    }
    /* Check if the bus is free */
    else if( 0U == _FLD2VAL(LIN_CH_STATUS_TX_BUSY, LIN_CH_STATUS(base)) )
    {
        /* Write data in to the temp variables */
        for( cnt = 0U; cnt < dataLength; cnt++ )
        {
            if( 4u > cnt )
            {
                data0[cnt] = data[cnt];
            }
            else
            {
                data1[cnt - 4u] = data[cnt];
            }
        }
        /* Write data to HW FIFO */
        LIN_CH_DATA0(base) =   (_VAL2FLD(LIN_CH_DATA0_DATA1, data0[0]) | \
                                _VAL2FLD(LIN_CH_DATA0_DATA2, data0[1]) | \
                                _VAL2FLD(LIN_CH_DATA0_DATA3, data0[2]) | \
                                _VAL2FLD(LIN_CH_DATA0_DATA4, data0[3]));
        LIN_CH_DATA1(base) =   (_VAL2FLD(LIN_CH_DATA1_DATA5, data1[0]) | \
                                _VAL2FLD(LIN_CH_DATA1_DATA6, data1[1]) | \
                                _VAL2FLD(LIN_CH_DATA1_DATA7, data1[2]) | \
                                _VAL2FLD(LIN_CH_DATA1_DATA8, data1[3]));
    }
    else
    {
        status = CY_LIN_BUSY;
        /* A requested operation could not be completed */
    }

    return status;
}

/**
 *****************************************************************************
 ** Cy_LIN_Enable
 ** Enable LIN channel.
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_Enable(LIN_CH_Type* base)
{
    cy_en_lin_status_t ret = CY_LIN_SUCCESS;

    if (NULL == base)
    {
        ret = CY_LIN_BAD_PARAM;
    }
    else
    {
        LIN_CH_CTL0(base) |= _VAL2FLD(LIN_CH_CTL0_ENABLED, 1U);
    }

    return ret;
}

/**
 *****************************************************************************
 ** Cy_LIN_Disable
 ** Disable LIN channel.
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_Disable(LIN_CH_Type* base)
{
    cy_en_lin_status_t ret = CY_LIN_SUCCESS;

    if (NULL == base)
    {
        ret = CY_LIN_BAD_PARAM;
    }
    else
    {
        LIN_CH_CTL0(base) &= ~(LIN_CH_CTL0_ENABLED_Msk);
    }

    return ret;
}

/**
 *****************************************************************************
 **  Cy_LIN_SetBreakWakeupFieldLength
 **  Setup LIN break/wakeup field length.
 **  Normally this I/F is used for detection of the wakeup pulse.
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_SetBreakWakeupFieldLength(LIN_CH_Type* base, uint8_t length)
{
    cy_en_lin_status_t ret = CY_LIN_SUCCESS;

    if (NULL == base)
    {
        ret = CY_LIN_BAD_PARAM;
    }
    else if (LIN_BREAK_WAKEUP_LENGTH_BITS_MAX < length)
    {
        ret = CY_LIN_BAD_PARAM;
    }
    else
    {
        LIN_CH_CTL0(base) |= _VAL2FLD(LIN_CH_CTL0_BREAK_WAKEUP_LENGTH, (((uint32_t)length) - 1U));
    }

    return ret;
}

/**
 *****************************************************************************
 ** Cy_LIN_SetChecksumType
 ** Setup LIN checksum type setting
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_SetChecksumType(LIN_CH_Type* base, cy_en_lin_checksum_type_t type)
{
    cy_en_lin_status_t ret = CY_LIN_SUCCESS;

    if (NULL == base)
    {
        ret = CY_LIN_BAD_PARAM;
    }
    else
    {
        LIN_CH_CTL1(base) |= _VAL2FLD(LIN_CH_CTL1_CHECKSUM_ENHANCED, type);
    }
    return ret;
}

/**
 *****************************************************************************
 ** Cy_LIN_SetDataLength
 ** Setup LIN response field data length
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_SetDataLength(LIN_CH_Type* base, uint8_t length)
{
    cy_en_lin_status_t ret = CY_LIN_SUCCESS;

    if ((NULL == base) ||
        (length > LIN_DATA_LENGTH_MAX) ||
        (length < LIN_DATA_LENGTH_MIN))
    {
        ret = CY_LIN_BAD_PARAM;
    }
    else
    {
        LIN_CH_CTL1(base) |= _VAL2FLD(LIN_CH_CTL1_DATA_NR, (((uint32_t)length) - 1U));
    }
    return ret;
}

/**
 *****************************************************************************
 ** Cy_LIN_SetCmd
 ** Setup LIN operation command
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_SetCmd(LIN_CH_Type* base, uint32_t command)
{
    cy_en_lin_status_t ret = CY_LIN_SUCCESS;

    if (NULL == base)
    {
        ret = CY_LIN_BAD_PARAM;
    }
    /* The command cannot have both TX_HEADER and RX_HEADER master set's TX_HEADER and slave sets RX_HEADER.
       If the Command is a wakeup command then TX_HEADER, RX_HEADER, TX_RESPONSE and RX_RESPONSE are not valid.
    */
    else if (((command & (LIN_CH_CMD_TX_HEADER_Msk | LIN_CH_CMD_RX_HEADER_Msk))
                == (LIN_CH_CMD_TX_HEADER_Msk | LIN_CH_CMD_RX_HEADER_Msk))   ||
            (((command & LIN_CH_CMD_TX_WAKEUP_Msk) != 0UL) &&
             ((command & (LIN_CH_CMD_TX_HEADER_Msk |
                          LIN_CH_CMD_TX_RESPONSE_Msk |
                          LIN_CH_CMD_RX_HEADER_Msk |
                          LIN_CH_CMD_RX_RESPONSE_Msk)) != 0UL)))
    {
        ret = CY_LIN_BAD_PARAM;
    }
    /* If software has already set the command and it is not complete then the channel must be busy processing the command.
       before setting the command make sure that hardware has already set the bit to 0 for the above cases.
    */
    else if (((_FLD2VAL(LIN_CH_CMD_TX_HEADER, LIN_CH_CMD(base)) != 0UL) && (command & LIN_CH_CMD_RX_HEADER_Msk) != 0UL) ||
             ((_FLD2VAL(LIN_CH_CMD_RX_HEADER, LIN_CH_CMD(base)) != 0UL) && (command & LIN_CH_CMD_TX_HEADER_Msk) != 0UL) ||
             ((_FLD2VAL(LIN_CH_CMD_TX_WAKEUP, LIN_CH_CMD(base)) != 0UL) &&
                            ((command & (LIN_CH_CMD_TX_HEADER_Msk |
                                         LIN_CH_CMD_TX_RESPONSE_Msk |
                                         LIN_CH_CMD_RX_HEADER_Msk |
                                         LIN_CH_CMD_RX_RESPONSE_Msk)) != 0UL)))
    {
        ret = CY_LIN_BUSY;
    }
    else
    {
        LIN_CH_CMD(base) = command;
    }

    return ret;
}

/**
 *****************************************************************************
 ** Cy_LIN_SetHeader
 ** Setup LIN header for master tx header operation
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_SetHeader(LIN_CH_Type* base, uint8_t id)
{
    cy_en_lin_status_t ret = CY_LIN_SUCCESS;
    uint8_t tempPID;
    uint8_t parity_P1, parity_P0;

    if ((NULL == base) ||
        (LIN_ID_MAX < id))
    {
        ret = CY_LIN_BAD_PARAM;
    }
    else
    {
        /* Calculate the Parity bits P0 & P1
           Parity is calculated as per the formula given
             - P[1] = ! (ID[5] ^ ID[4] ^ ID[3] ^ ID[1])
             - P[0] = (ID[4] ^ ID[2] ^ ID[1] ^ ID[0])
        */
        parity_P0 = ((id) ^ (id>>1u) ^
                     (id>>2u) ^ (id>>4u)) & 0x01u;
        parity_P1 = (~((id>>1u) ^ (id>>3u) ^
                       (id>>4u) ^ (id>>5u))) & 0x01u;
        /* Assign the Parity bits and the header values in to the tempPID */
        tempPID = id | ((uint8_t) parity_P0<<6u) | ((uint8_t) parity_P1<<7u);
        /* Write the TempID value in to the TX_HEADER register */
        LIN_CH_PID_CHECKSUM(base) = _VAL2FLD(LIN_CH_PID_CHECKSUM_PID, tempPID);
    }

    return ret;
}

/**
 *****************************************************************************
 ** Cy_LIN_GetHeader
 ** Return received LIN header
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_GetHeader(LIN_CH_Type* base, uint8_t *id, uint8_t *parity)
{
    cy_en_lin_status_t ret = CY_LIN_SUCCESS;

    if ((NULL == base) ||
        (NULL == id)      ||
        (NULL == parity))
    {
        ret = CY_LIN_BAD_PARAM;
    }
    else
    {
        /* Store received ID and parity bits */
        uint8_t temp = (uint8_t)_FLD2VAL(LIN_CH_PID_CHECKSUM_PID, LIN_CH_PID_CHECKSUM(base));
        *parity = (temp >> 6u);
        *id = (temp & LIN_ID_MAX);
    }

    return ret;
}

/**
 *****************************************************************************
 ** Cy_LIN_SetInterruptMask
 ** Setup interrupt source to be accepted.
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_SetInterruptMask(LIN_CH_Type* base, uint32_t mask)
{
    cy_en_lin_status_t ret = CY_LIN_SUCCESS;

    if (NULL == base)
    {
        ret = CY_LIN_BAD_PARAM;
    }
    else
    {
        LIN_CH_INTR_MASK(base)  = mask;
    }

    return ret;
}

/**
 *****************************************************************************
 ** Cy_LIN_GetInterruptMask
 ** Return interrupt mask setting.
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_GetInterruptMask(LIN_CH_Type* base, uint32_t *mask)
{
    cy_en_lin_status_t ret = CY_LIN_SUCCESS;

    if ((NULL == base) ||
        (NULL == mask))
    {
        ret = CY_LIN_BAD_PARAM;
    }
    else
    {
        *mask = LIN_CH_INTR_MASK(base);
    }

    return ret;
}

/**
 *****************************************************************************
 ** Cy_LIN_GetInterruptMaskedStatus
 ** Return interrupt masked status.
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_GetInterruptMaskedStatus(LIN_CH_Type* base, uint32_t *status)
{
    cy_en_lin_status_t ret = CY_LIN_SUCCESS;

    if ((NULL == base) ||
        (NULL == status))
    {
        ret = CY_LIN_BAD_PARAM;
    }
    else
    {
        *status = LIN_CH_INTR_MASKED(base);
    }

    return ret;
}

/**
 *****************************************************************************
 ** Cy_LIN_GetInterruptStatus
 ** Return interrupt raw status.
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_GetInterruptStatus(LIN_CH_Type* base, uint32_t *status)
{

    cy_en_lin_status_t ret = CY_LIN_SUCCESS;

    if ((NULL == base) ||
        (NULL == status))
    {
        ret = CY_LIN_BAD_PARAM;
    }
    else
    {
        *status = LIN_CH_INTR(base) ;
    }

    return ret;
}

/**
 *****************************************************************************
 ** Cy_LIN_ClearInterrupt
 ** Clear interrupt status.
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_ClearInterrupt(LIN_CH_Type* base, uint32_t mask)
{
    cy_en_lin_status_t ret = CY_LIN_SUCCESS;

    if (NULL == base)
    {
        ret = CY_LIN_BAD_PARAM;
    }
    else
    {
        LIN_CH_INTR(base) = mask;
    }

    return ret;
}

/**
 *****************************************************************************
 ** Cy_LIN_GetStatus
 ** Return LIN module status
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_GetStatus(LIN_CH_Type* base, uint32_t *status)
{
    cy_en_lin_status_t ret = CY_LIN_SUCCESS;

    if ((NULL == base) ||
        (NULL == status))
    {
        ret = CY_LIN_BAD_PARAM;
    }
    else
    {
        *status = LIN_CH_STATUS(base);
    }

    return ret;
}

/**
 *****************************************************************************
 ** Cy_LIN_EnOut_Enable
 ** Enables LIN channel 'en' out
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_EnOut_Enable(LIN_CH_Type* base)
{
    if (NULL == base)
    {
        return CY_LIN_BAD_PARAM;
    }
    /* check if auto enabled is set or not */
    bool auto_enable = (_FLD2VAL(LIN_CH_CTL0_AUTO_EN, LIN_CH_CTL0(base)) != 0UL) ? true : false;
    if(!auto_enable)
    {
        /* Enable EN out  */
        LIN_CH_TX_RX_STATUS(base) |= _VAL2FLD(LIN_CH_TX_RX_STATUS_EN_OUT, 1U);
    }
    return CY_LIN_SUCCESS;
}

/**
 *****************************************************************************
 ** Cy_LIN_EnOut_Disable
 ** Disables LIN channel 'en' out
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_EnOut_Disable(LIN_CH_Type* base)
{
    if (NULL == base)
    {
        return CY_LIN_BAD_PARAM;
    }
    /* check if auto enabled is set or not */
    bool auto_enable = (_FLD2VAL(LIN_CH_CTL0_AUTO_EN, LIN_CH_CTL0(base)) != 0UL) ? true : false;
    if(!auto_enable)
    {
        /* Disable EN out  */
        LIN_CH_TX_RX_STATUS(base) &= ~LIN_CH_TX_RX_STATUS_EN_OUT_Msk;
    }
    return CY_LIN_SUCCESS;
}

/**
 *****************************************************************************
 ** Cy_LIN_TestMode_Enable
 ** Enables LIN Test mode
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_TestMode_Enable(LIN_Type* base, const cy_stc_lin_test_config_t* lin_test_config)
{
    if (NULL == base || NULL == lin_test_config)
    {
        return CY_LIN_BAD_PARAM;
    }
    CY_ASSERT_L3(CY_LIN_IS_TEST_CTL_CH_IDX_VALID(lin_test_config->chidx));
    /* Enable Test mode and set test configuration  */
    LIN_TEST_CTL(base) = (_VAL2FLD(LIN_TEST_CTL_CH_IDX, lin_test_config->chidx) |\
                          _VAL2FLD(LIN_TEST_CTL_MODE, lin_test_config->mode)    |\
                          _VAL2FLD(LIN_TEST_CTL_ENABLED, 1U));

    return CY_LIN_SUCCESS;
}

/**
 *****************************************************************************
 ** Cy_LIN_TestMode_Disable
 ** Disables LIN Test mode
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_TestMode_Disable(LIN_Type* base)
{
    if (NULL == base)
    {
        return CY_LIN_BAD_PARAM;
    }
    /* Disable Test mode  */
    LIN_TEST_CTL(base) &= ~LIN_TEST_CTL_ENABLED_Msk;
    return CY_LIN_SUCCESS;
}

/**
 *****************************************************************************
 ** Cy_LIN_ErrCtl_Enable
 ** Enables LIN Err Ctl in Test mode
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_ErrCtl_Enable(LIN_Type* base, cy_stc_lin_test_error_config_t* test_error_config)
{
    if (NULL == base)
    {
        return CY_LIN_BAD_PARAM;
    }

    /* LIN est Error CTL setting  */
    CY_ASSERT_L3(CY_LIN_IS_TEST_CTL_CH_IDX_VALID(test_error_config->chidx));

    LIN_ERROR_CTL(base) = (_VAL2FLD(LIN_ERROR_CTL_CH_IDX, test_error_config->chidx) |\
                           _VAL2FLD(LIN_ERROR_CTL_TX_SYNC_ERROR, test_error_config->txsync_error)             |\
                           _VAL2FLD(LIN_ERROR_CTL_TX_SYNC_STOP_ERROR, test_error_config->txsyncStop_error)    |\
                           _VAL2FLD(LIN_ERROR_CTL_TX_PARITY_ERROR, test_error_config->txParity_error)         |\
                           _VAL2FLD(LIN_ERROR_CTL_TX_PID_STOP_ERROR, test_error_config->txPIDStop_error)      |\
                           _VAL2FLD(LIN_ERROR_CTL_TX_DATA_STOP_ERROR, test_error_config->txDataStop_error)    |\
                           _VAL2FLD(LIN_ERROR_CTL_TX_CHECKSUM_ERROR, test_error_config->txChecksum_error)     |\
                           _VAL2FLD(LIN_ERROR_CTL_TX_CHECKSUM_STOP_ERROR, test_error_config->txChecksumStop_error) |\
                           _VAL2FLD(LIN_ERROR_CTL_ENABLED, 1U));

    return CY_LIN_SUCCESS;
}

/**
 *****************************************************************************
 ** Cy_LIN_ErrCtl_Disable
 ** Disables LIN Error Ctl in Test mode
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_ErrCtl_Disable(LIN_Type* base)
{
    if (NULL == base)
    {
        return CY_LIN_BAD_PARAM;
    }
    /* Disable Test Error Control mode  */
    LIN_ERROR_CTL(base) &= ~LIN_ERROR_CTL_ENABLED_Msk;
    return CY_LIN_SUCCESS;
}

#endif /* CY_IP_MXLIN */
/*****************************************************************************/
/* EOF (not truncated)                                                       */
/*****************************************************************************/
