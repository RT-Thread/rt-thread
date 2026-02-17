/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_i2c.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "n32h76x_78x_i2c.h"
#include "n32h76x_78x_rcc.h"

/**
*\*\name    I2C_DeInit.
*\*\fun     Deinitializes the I2Cx peripheral registers to their default reset values.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\return  None
**/
void I2C_DeInit(I2C_Module* I2Cx)
{
    if (I2Cx == I2C1)
    {
        /* Enable I2C1 reset state */
        RCC_EnableAPB1PeriphReset4(RCC_APB1_PERIPHRST_I2C1);
    }
    else if (I2Cx == I2C2)
    {
        /* Enable I2C2 reset state */
        RCC_EnableAPB1PeriphReset4(RCC_APB1_PERIPHRST_I2C2);
    }
    else if (I2Cx == I2C3)
    {
        /* Enable I2C3 reset state */
        RCC_EnableAPB1PeriphReset4(RCC_APB1_PERIPHRST_I2C3);
    }
    else if (I2Cx == I2C4)
    {
        /* Enable I2C4 reset state */
        RCC_EnableAPB2PeriphReset2(RCC_APB2_PERIPHRST_I2C4);
    }
    else if (I2Cx == I2C5)
    {
        /* Enable I2C5 reset state */
        RCC_EnableAPB2PeriphReset2(RCC_APB2_PERIPHRST_I2C5);
    }
    else if (I2Cx == I2C6)
    {
        /* Enable I2C6 reset state */
        RCC_EnableAPB2PeriphReset2(RCC_APB2_PERIPHRST_I2C6);;
    }
    else if (I2Cx == I2C7)
    {
        /* Enable I2C7 reset state */
        RCC_EnableAPB5PeriphReset2(RCC_APB5_PERIPHRST_I2C7);
    }
    else if (I2Cx == I2C8)
    {
        /* Enable I2C8 reset state */
        RCC_EnableAPB5PeriphReset2(RCC_APB5_PERIPHRST_I2C8);
    }
    else if (I2Cx == I2C9)
    {
        /* Enable I2C9 reset state */
        RCC_EnableAPB5PeriphReset2(RCC_APB5_PERIPHRST_I2C9);
    }
    else
    {
        /* Enable I2C10 reset state */
        RCC_EnableAPB5PeriphReset2(RCC_APB5_PERIPHRST_I2C10);
    }

}



/**
*\*\name    I2C_Init.
*\*\fun     Initializes the I2C peripheral according to the specified parameters in the I2C_InitStruct.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   I2C_InitStruct (The input parameters must be the following values):
*\*\          - Timing
*\*\          - HSTiming
*\*\          - OwnAddress1:
*\*\            - between 0 to 0x3FF
*\*\          - AddressingMode(only for Address1):
*\*\            - I2C_ADDRESSINGMODE_7BIT
*\*\            - I2C_ADDRESSINGMODE_10BIT
*\*\          - DualAddressMode:
*\*\            - I2C_DUALADDRESS_DISABLE
*\*\            - I2C_DUALADDRESS_ENABLE
*\*\          - OwnAddress2:
*\*\            - between 0 to 0xFF
*\*\          - OwnAddress2Masks:
*\*\            - I2C_ADDRESS2MASK_NONE         AD2[7:1] are compared.
*\*\            - I2C_ADDRESS2MASK_1            AD2[1] dont care. Only AD2[7:2] are compared.
*\*\            - I2C_ADDRESS2MASK_2_1          AD2[2:1] dont care. Only AD2[7:3] are compared.
*\*\            - I2C_ADDRESS2MASK_3_1          AD2[3:1] dont care. Only AD2[7:4] are compared.
*\*\            - I2C_ADDRESS2MASK_4_1          AD2[4:1] dont care. Only AD2[7:5] are compared.
*\*\            - I2C_ADDRESS2MASK_5_1          AD2[5:1] dont care. Only AD2[7:6] are compared.
*\*\            - I2C_ADDRESS2MASK_6_1          AD2[6:1] dont care. Only AD2[7] is compared.
*\*\            - I2C_ADDRESS2MASK_7_1          AD2[7:1] dont care. No comparison is done.
*\*\          - GeneralCallMode:
*\*\            - I2C_GENERALCALL_DISABLE
*\*\            - I2C_GENERALCALL_ENABLE
*\*\          - NoStretchMode:
*\*\            - I2C_NOSTRCH_DISABLE
*\*\            - I2C_NOSTRCH_ENABLE
*\*\return  Status
**/
void I2C_Init(I2C_Module* I2Cx, I2C_InitType* I2C_InitStruct)
{
    uint32_t temp_value;

    /* Disable the selected I2C peripheral */
    I2C_Enable(I2Cx, DISABLE);

    /*---------------------------- I2Cx BUSTIM Configuration ------------------*/
    /* Configure I2Cx: Frequency range */
    I2Cx->BUSTIM = I2C_InitStruct->Timing & TIMING_CLEAR_MASK;
    I2Cx->HSBUSTM = I2C_InitStruct->HSTiming & TIMING_CLEAR_MASK;

    /*---------------------------- I2Cx ADR1 Configuration ---------------------*/
    /* Disable Own Address1 before set the Own Address1 configuration */
    I2Cx->ADR1 &= (~I2C_ADR1_AD1EN);

    /* Configure I2Cx: Own Address1 and ack own address1 mode */
    if (I2C_InitStruct->AddressingMode == I2C_ADDRESSINGMODE_7BIT)
    {
        I2Cx->ADR1 = (I2C_ADR1_AD1EN | I2C_InitStruct->OwnAddress1);
    }
    else /* I2C_ADDRESSINGMODE_10BIT */
    {
        I2Cx->ADR1 = (I2C_ADR1_AD1EN | I2C_ADR1_AD1MODE | I2C_InitStruct->OwnAddress1);
    }

    /*---------------------------- I2Cx CTRL2 Configuration ----------------------*/
    /* Configure I2Cx: Addressing Master mode */
    if (I2C_InitStruct->AddressingMode == I2C_ADDRESSINGMODE_10BIT)
    {
        I2Cx->CTRL2 |= (I2C_CTRL2_ADR10);
    }

    /*---------------------------- I2Cx ADR2 Configuration ---------------------*/
    /* Disable Own Address2 before set the Own Address2 configuration */
    I2Cx->ADR2 &= (~I2C_DUALADDRESS_ENABLE);
    /* Configure I2Cx: Dual mode and Own Address2 */
    I2Cx->ADR2 = (I2C_InitStruct->DualAddressMode | I2C_InitStruct->OwnAddress2 | I2C_InitStruct->OwnAddress2Masks);

    /*---------------------------- I2Cx CTRL1 Configuration ----------------------*/
    temp_value = I2Cx->CTRL1;
    temp_value &= CTRL1_CLEAR_MASK;
    /* Configure I2Cx: Generalcall and NoStretch mode */
    temp_value |= (I2C_InitStruct->GeneralCallMode | I2C_InitStruct->NoStretchMode);
    I2Cx->CTRL1 = temp_value;

    /*--------------------------------------------------------------------------------*/
    /* Enable the selected I2C peripheral */
    I2C_Enable(I2Cx, ENABLE);

}

/**
*\*\name    I2C_Initializes_Structure.
*\*\fun     Fills each I2C_InitStruct member with its default value.
*\*\param   (The input parameters must be the following values):
*\*\          - Timing
*\*\          - HSTiming
*\*\          - OwnAddress1
*\*\          - AddressingMode
*\*\          - DualAddressMode
*\*\          - OwnAddress2
*\*\          - OwnAddress2Masks
*\*\          - GeneralCallMode
*\*\          - NoStretchMode
*\*\return  none
**/
void I2C_InitStruct(I2C_InitType* I2C_StructInit)
{
    /*Reset I2C init structure parameters values */
    I2C_StructInit->Timing           = 0x50012526;
    I2C_StructInit->HSTiming         = 0x0;
    I2C_StructInit->OwnAddress1      = 0x0;
    I2C_StructInit->AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
    I2C_StructInit->DualAddressMode  = I2C_DUALADDRESS_DISABLE;
    I2C_StructInit->OwnAddress2      = 0x0;
    I2C_StructInit->OwnAddress2Masks = I2C_ADDRESS2MASK_NONE;
    I2C_StructInit->GeneralCallMode  = I2C_GENERALCALL_DISABLE;
    I2C_StructInit->NoStretchMode    = I2C_NOSTRCH_DISABLE;

}

/**
*\*\name    I2C_Enable.
*\*\fun     Enables or disables the specified I2C peripheral.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_Enable(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C peripheral */
        I2Cx->CTRL1 |= CTRL1_SPEN_SET;
    }
    else
    {
        /* Disable the selected I2C peripheral */
        I2Cx->CTRL1 &= CTRL1_SPEN_RESET;
    }
}

/**
*\*\name    I2C_ConfigSendAddress.
*\*\fun     Configure slave address and transfer direction in master mode.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   address (The input parameters must be the following values)
*\*\        - 0 to 0x3FF
*\*\param   mode (The input parameters must be the following values):
*\*\          - I2C_DIRECTION_SEND    Transmitter mode
*\*\          - I2C_DIRECTION_RECV    Receiver mode
*\*\return  none
**/
void I2C_ConfigSendAddress(I2C_Module* I2Cx, uint32_t address, uint32_t direction)
{
    uint32_t temp_value;

    temp_value = I2Cx->CTRL2;
    temp_value &= I2C_SADR_RWN_MASK;
    /* Test on the direction to set/reset the read/write bit */
    temp_value |= ((address & I2C_SADR_MASK) | direction);

    I2Cx->CTRL2 = temp_value;
}

/**
*\*\name    I2C_Enable10bitAddressHeader.
*\*\fun     10-bit address header executes complete sequence in master receive mode.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_Enable10bitAddressHeader(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Generate a START condition */
        I2Cx->CTRL2 |= CTRL2_HDR10_ENABLE;
    }
    else
    {
        /* Disable the START condition generation */
        I2Cx->CTRL2 &= CTRL2_HDR10_DISABLE;
    }
}

/**
*\*\name    I2C_EnableAutomaticEnd.
*\*\fun     Enable I2C automatic end mode in master mode.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableAutomaticEnd(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Generate a START condition */
        I2Cx->CTRL2 |= CTRL2_AUTO_STOP;
    }
    else
    {
        /* Disable the START condition generation */
        I2Cx->CTRL2 &= CTRL2_SOFTWARE_STOP;
    }
}

/**
*\*\name    I2C_EnableReload.
*\*\fun     Enable I2C reload mode.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableReload(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Generate a START condition */
        I2Cx->CTRL2 |= CTRL2_REFILL_ENABLE;
    }
    else
    {
        /* Disable the START condition generation */
        I2Cx->CTRL2 &= CTRL2_REFILL_DISABLE;
    }
}


/**
*\*\name    I2C_GenerateStart.
*\*\fun     Generates I2Cx communication START condition.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_GenerateStart(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Generate a START condition */
        I2Cx->CTRL2 |= CTRL2_START_ENABLE;
    }
    else
    {
        /* Disable the START condition generation */
        I2Cx->CTRL2 &= CTRL2_START_DISABLE;
    }
}

/**
*\*\name    I2C_GenerateStop.
*\*\fun     Generates I2Cx communication STOP condition.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_GenerateStop(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Generate a STOP condition */
        I2Cx->CTRL2 |= CTRL2_STOP_ENABLE;
    }
    else
    {
        /* Disable the STOP condition generation */
        I2Cx->CTRL2 &= CTRL2_STOP_DISABLE;
    }
}


/**
*\*\name    I2C_ConfigAck.
*\*\fun     Enables or disables the specified I2C acknowledge feature.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_ConfigAck(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the acknowledgement */
        I2Cx->CTRL2 &= CTRL2_ACK;
    }
    else
    {
        /* Disable the acknowledgement */
        I2Cx->CTRL2 |= CTRL2_NACK;
    }
}


/**
*\*\name    I2C_ConfigOwnAddr2.
*\*\fun     Configures the specified I2C own address2.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Address
*\*\          - 7bit I2C own address2
*\*\return  none
**/
void I2C_ConfigOwnAddr2(I2C_Module* I2Cx, uint8_t Address)
{
    uint32_t tmpregister;

    /* Get the old register value */
    tmpregister = I2Cx->ADR2;

    /* Reset I2Cx Own address2 bit [7:1] */
    tmpregister &= ADR2_AD2_RESET;

    /* Set I2Cx Own address2 */
    tmpregister |= (uint16_t)((uint16_t)Address & ADR2_AD2_SET);

    /* Store the new register value */
    I2Cx->ADR2 = tmpregister;
}


/**
*\*\name    I2C_EnableDualAddr.
*\*\fun     Enables or disables the specified I2C dual addressing mode.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableDualAddr(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable dual addressing mode */
        I2Cx->ADR2 |= ADR2_ENABLE;
    }
    else
    {
        /* Disable dual addressing mode */
        I2Cx->ADR2 &= ADR2_DISABLE;
    }
}


/**
*\*\name    I2C_EnableGeneralCall.
*\*\fun     Enables or disables the specified I2C general call feature.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableGeneralCall(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable generall call */
        I2Cx->CTRL1 |= CTRL1_GENC_SET;
    }
    else
    {
        /* Disable generall call */
        I2Cx->CTRL1 &= CTRL1_GENC_RESET;
    }
}

/**
*\*\name    I2C_EnableSlaveByteControl.
*\*\fun     Enables or disables slave byte control.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableSlaveByteControl(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable slave byte control */
        I2Cx->CTRL1 |= CTRL1_SBCTL_SET;
    }
    else
    {
        /* Disable slave byte control */
        I2Cx->CTRL1 &= CTRL1_SBCTL_RESET;
    }
}

/**
*\*\name    I2C_EnableSMBusAlert.
*\*\fun     Enables or disables SMBus alert.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableSMBusAlert(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable slave byte control */
        I2Cx->CTRL1 |= CTRL1_ALRTEN_SET;
    }
    else
    {
        /* Disable slave byte control */
        I2Cx->CTRL1 &= CTRL1_ALRTEN_RESET;
    }
}

/**
*\*\name    I2C_EnableSMBusDefaultAddr.
*\*\fun     Enables or disables SMBus device default address.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableSMBusDefaultAddr(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable slave byte control */
        I2Cx->CTRL1 |= CTRL1_SMBD_SET;
    }
    else
    {
        /* Disable slave byte control */
        I2Cx->CTRL1 &= CTRL1_SMBD_RESET;
    }
}

/**
*\*\name    I2C_EnableSMBusHostAddr.
*\*\fun     Enables or disables SMBus host address.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableSMBusHostAddr(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable slave byte control */
        I2Cx->CTRL1 |= CTRL1_SMBH_SET;
    }
    else
    {
        /* Disable slave byte control */
        I2Cx->CTRL1 &= CTRL1_SMBH_RESET;
    }
}

/**
*\*\name    I2C_SendData.
*\*\fun     Sends a data byte through the I2Cx peripheral.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Data
*\*\return  none
**/
void I2C_SendData(I2C_Module* I2Cx, uint8_t Data)
{
    /* Write in the DAT register the data to be sent */
    I2Cx->WDR = Data;
}

/**
*\*\name    I2C_RecvData.
*\*\fun     Returns the most recent received data by the I2Cx peripheral.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\return  The value of the received data
**/
uint8_t I2C_RecvData(I2C_Module* I2Cx)
{
    /* Return the data in the DAT register */
    return (uint8_t)I2Cx->RDR;
}


/**
*\*\name    I2C_SendCRC.
*\*\fun        Enables or disables the specified I2C CRC transfer.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_SendCRC(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C CRC transmission */
        I2Cx->CTRL2 |= CTRL2_CRCBYTE_ENABLE;
    }
    else
    {
        /* Disable the selected I2C CRC transmission */
        I2Cx->CTRL2 &= CTRL2_CRCBYTE_DISABLE;
    }
}

/**
*\*\name    I2C_EnableCRC.
*\*\fun        Enables or disables the CRC value calculation of the transferred bytes.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableCRC(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C PEC calculation */
        I2Cx->CTRL1 |= CTRL1_CRCEN_SET;
    }
    else
    {
        /* Disable the selected I2C PEC calculation */
        I2Cx->CTRL1 &= CTRL1_CRCEN_RESET;
    }
}



/**
*\*\name    I2C_EnableQuickCommand.
*\*\fun        Enables or disables Quick Command(For Master or Slave mode).
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableQuickCommand(I2C_Module* I2Cx, FunctionalState Cmd)
{

    if( Cmd == DISABLE)
    {
        I2Cx->QCMD &= QCMD_DISABLE;
    }
    else
    {
        I2Cx->QCMD |= QCMD_ENABLE;
    }
}

/**
*\*\name    I2C_ConfigQuickCommandAddr.
*\*\fun     Configures SMB Quick command address(For Slave mode only).
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Address
*\*\          - 7bit own address
*\*\return  none
**/
void I2C_ConfigQuickCommandAddr(I2C_Module* I2Cx, uint8_t Address)
{
    uint32_t tmpregister;

    /* Get the old register value */
    tmpregister = I2Cx->QCMD;

    /* Reset address bit [6:1] */
    tmpregister &= QCMDAD_MASK;

    /* Set address */
    tmpregister |= Address;

    /* Store the new register value */
    I2Cx->QCMD = tmpregister;
}

/**
*\*\name    I2C_EnableTXFIFO.
*\*\fun        Enables or disables the TX FIFO.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableTXFIFO(I2C_Module* I2Cx, FunctionalState Cmd)
{

    if( Cmd == DISABLE)
    {
        I2Cx->FIFOCSR &= TFE_DISABLE;
    }
    else
    {
        I2Cx->FIFOCSR |= TFE_ENABLE;
    }
}

/**
*\*\name    I2C_EnableRXFIFO.
*\*\fun        Enables or disables the RX FIFO.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableRXFIFO(I2C_Module* I2Cx, FunctionalState Cmd)
{

    if( Cmd == DISABLE)
    {
        I2Cx->FIFOCSR &= RFE_DISABLE;
    }
    else
    {
        I2Cx->FIFOCSR |= RFE_ENABLE;
    }
}

/**
*\*\name    I2C_EnableTXDMA.
*\*\fun        Enables or disables the TX DMA request.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableTXDMA(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if( Cmd == DISABLE)
    {
        I2Cx->CTRL1 &= CTRL1_DMAWREN_TRANSMISSION_RESET;
    }
    else
    {
        I2Cx->CTRL1 |= CTRL1_DMAWREN_TRANSMISSION_SET;
    }
}

/**
*\*\name    I2C_EnableRXDMA.
*\*\fun        Enables or disables the RX DMA request.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableRXDMA(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if( Cmd == DISABLE)
    {
        I2Cx->CTRL1 &= CTRL1_DMARDEN_RECEPTION_RESET;
    }
    else
    {
        I2Cx->CTRL1 |= CTRL1_DMARDEN_RECEPTION_SET;
    }
}


/**
*\*\name    I2C_SetTransferByteNumber.
*\*\fun     Set the number of data bytes that will be transferred of I2C peripheral.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Number_Of_bytes:
*\*\          - 0 ~ 255
*\*\return  none
*\*\note    The number of bytes is greater than or equal to 2.
**/
void I2C_SetTransferByteNumber(I2C_Module* I2Cx, uint8_t Number_Of_bytes)
{
    uint32_t temp_value;

    temp_value = I2Cx->CTRL2;
    temp_value &= (BYTENUM_Mask);
    temp_value |= ((uint32_t)Number_Of_bytes << 16);
    I2Cx->CTRL2 = temp_value;

}


/**
*\*\name    I2C_SetTXFIFO_ILEVEL.
*\*\fun     Config TX FIFO empty level.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   TX_ILEVEL:
*\*\          - 0 ~ 15
*\*\return  none
**/
void I2C_SetTXFIFO_ILEVEL(I2C_Module* I2Cx, uint8_t TX_ILEVEL)
{
    uint32_t temp_value;

    /* Config TX FIFO emptly level */
    temp_value = I2Cx->FIFOCSR;
    temp_value &= (FIFO_TX_ILEVEL_Mask);
    temp_value |= (((uint32_t)TX_ILEVEL & 0xF) << 24);
    I2Cx->FIFOCSR = temp_value;
}

/**
*\*\name    I2C_SetRXFIFO_ILEVEL.
*\*\fun     Config RX FIFO level to generate interrupt.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   RX_ILEVEL:
*\*\          - 0 ~ 15
*\*\return  none
**/
void I2C_SetRXFIFO_ILEVEL(I2C_Module* I2Cx, uint8_t RX_ILEVEL)
{
    uint32_t temp_value;

    /* Config RX FIFO emptly level */
    temp_value = I2Cx->FIFOCSR;
    temp_value &= (FIFO_RX_ILEVEL_Mask);
    temp_value |= (((uint32_t)RX_ILEVEL & 0xF) << 16);
    I2Cx->FIFOCSR = temp_value;
}

/**
*\*\name    I2C_GetTXFIFO_FLEVEL.
*\*\fun     Returns TX FIFO data number.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\return  FIFO data.
**/
uint8_t I2C_GetTXFIFO_FLEVEL(I2C_Module* I2Cx)
{
    uint32_t tmpregister;

    /* Return the data in the FIFODAT register */
    tmpregister = ((I2Cx->FIFOCSR & FIFO_TX_FLEVEL_Mask) >> 8);

    return (uint8_t)tmpregister;
}

/**
*\*\name    I2C_GetRXFIFO_FLEVEL.
*\*\fun     Returns RX FIFO data number.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\return  FIFO data.
**/
uint8_t I2C_GetRXFIFO_FLEVEL(I2C_Module* I2Cx)
{
    uint32_t tmpregister;

    /* Return the data in the FIFODAT register */
    tmpregister = (I2Cx->FIFOCSR & FIFO_RX_FLEVEL_Mask);

    return (uint8_t)tmpregister;
}

/**
*\*\name    I2C_EnableSCLTimeoutDetection.
*\*\fun        Enable or disable clk timeout.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableSCLTimeoutDetection(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if( Cmd == DISABLE)
    {
        I2Cx->TMOUTR &= ~TMOUTEN_ENABLE;
    }
    else
    {
        I2Cx->TMOUTR |= TMOUTEN_ENABLE;
    }
}

/**
*\*\name    I2C_EnableExtenClkTimeout.
*\*\fun        Enable or disable extended clk timeout.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableExtenClkTimeout(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if( Cmd == DISABLE)
    {
        I2Cx->TMOUTR &= ~TMEXTEN_ENABLE;
    }
    else
    {
        I2Cx->TMOUTR |= TMEXTEN_ENABLE;
    }
}

/**
*\*\name    I2C_SetBusTimeoutA.
*\*\fun     Configure bus timeout A.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   bus_timeout
*\*\          - 0x0 ~ 0xFFF
*\*\return  none
**/
void I2C_SetBusTimeoutA(I2C_Module* I2Cx, uint32_t bus_timeout)
{
    uint32_t temp_value;

    temp_value = I2Cx->TMOUTR;
    temp_value &= I2C_TMOUTA_MASK;
    temp_value |= (bus_timeout & 0xFFFU);
    I2Cx->TMOUTR = temp_value;
}

/**
*\*\name    I2C_SetBusTimeoutB.
*\*\fun     Configure bus timeout B.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   bus_timeout
*\*\          - 0x0 ~ 0xFFF
*\*\return  none
**/
void I2C_SetBusTimeoutB(I2C_Module* I2Cx, uint32_t bus_timeout)
{
    uint32_t temp_value;

    temp_value = I2Cx->TMOUTR;
    temp_value &= I2C_TMOUTB_MASK;
    temp_value |= ((bus_timeout << 16) & 0xFFF0000U);
    I2Cx->TMOUTR = temp_value;
}

/**
*\*\name    I2C_ConfigIdleClockTimeout.
*\*\fun     Configure idle clock timeout detection.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   bus_timeout
*\*\          - I2C_TMOUTA_DETECT_SCL_LOW
*\*\          - I2C_TMOUTA_DETECT_BUS_IDLE
*\*\return  none
**/
void I2C_ConfigIdleClockTimeout(I2C_Module* I2Cx, uint32_t bus_timeout)
{
    uint32_t temp_value;

    temp_value = I2Cx->TMOUTR;
    temp_value &= (~I2C_TMOUTA_DETECT_BUS_IDLE);
    temp_value |= bus_timeout;
    I2Cx->TMOUTR = temp_value;
}

/**
*\*\name    I2C_EnableAnalogFilter.
*\*\fun        Enables or disables Analog Filter.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableAnalogFilter(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if( Cmd == DISABLE)
    {
        I2Cx->CTRL1 |= CTRL1_AF_SET;
    }
    else
    {
        I2Cx->CTRL1 &= CTRL1_AF_RESET;
    }
}
/**
*\*\name    I2C_Enable_SDA_Analog_Filter.
*\*\fun        Enables or disables SDA Analog Filter.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableSDAAnalogFilter(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if( Cmd == DISABLE)
    {
        I2Cx->GFLTRCTRL |= SDAAFENN_ENABLE;

    }
    else
    {
        I2Cx->GFLTRCTRL &= SDAAFENN_DISABLE ;
    }
}

/**
*\*\name    I2C_EnableSCLAnalogFilter.
*\*\fun        Enables or disables SCL Analog Filter.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableSCLAnalogFilter(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if( Cmd == DISABLE)
    {
        I2Cx->GFLTRCTRL |= SCLAFENN_ENABLE;
    }
    else
    {

        I2Cx->GFLTRCTRL &= SCLAFENN_DISABLE ;
    }
}


/**
*\*\name    I2C_SetSCLAnalogFilterWidth.
*\*\fun     SCL analog filter width selection.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   width :
*\*\        - I2C_ANALOG_FILTER_WIDTH_5NS
*\*\        - I2C_ANALOG_FILTER_WIDTH_15NS
*\*\        - I2C_ANALOG_FILTER_WIDTH_25NS
*\*\        - I2C_ANALOG_FILTER_WIDTH_35NS
*\*\return  none
**/
void I2C_SetSCLAnalogFilterWidth(I2C_Module* I2Cx, uint32_t width)
{
    uint32_t temp_value;

    temp_value = I2Cx->GFLTRCTRL;
    /* Clear SCLAFW[1:0] bits */
    temp_value &= I2C_SCLAFW_MASK;
    /* Set SCLAFW[1:0] bits according to width value */
    temp_value |= (width << 4);
    /* Store the new value */
    I2Cx->GFLTRCTRL = temp_value;

}


/**
*\*\name    I2C_SetSDAAnalogFilterWidth.
*\*\fun     SDA analog filter width selection.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   width :
*\*\        - I2C_ANALOG_FILTER_WIDTH_5NS
*\*\        - I2C_ANALOG_FILTER_WIDTH_15NS
*\*\        - I2C_ANALOG_FILTER_WIDTH_25NS
*\*\        - I2C_ANALOG_FILTER_WIDTH_35NS
*\*\return  none
**/
void I2C_SetSDAAnalogFilterWidth(I2C_Module* I2Cx, uint32_t width)
{
    uint32_t temp_value;

    temp_value = I2Cx->GFLTRCTRL;
    /* Clear SDAAFW[1:0] bits */
    temp_value &= I2C_SDAAFW_MASK;
    /* Set SDAAFW[1:0] bits according to width value */
    temp_value |= width;
    /* Store the new value */
    I2Cx->GFLTRCTRL = temp_value;

}


/**
*\*\name    I2C_SetDigitalFilterWidth.
*\*\fun     SCL digital filter width selection.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   width :
*\*\          - 0x00            Disable the digital filter.
*\*\          - 0x001 ~ 0x3FF   The numbers which filters spikes with a length of up to DF10{DFX,DF} *tI2CCLK.
                                                                Details pls check I2C user manual.
*\*\return  none
**/
void I2C_SetDigitalFilterWidth(I2C_Module* I2Cx, uint32_t width)
{
    uint32_t temp_value;

    temp_value = I2Cx->CTRL1;
    /* Clear DFX[29:24] bits and DF[11:8] bits */
    temp_value &= (CTRL1_DF10_RESET);

    /* Set DFX[29:24] bits and DF[11:8] bits according to width value */
    temp_value |= (((width & 0xF) << 8) | ((width & 0x3F0) << 20));
    /* Store the new value */
    I2Cx->CTRL1 = temp_value;

}

/**
*\*\name    I2C_ClrFlag.
*\*\fun     Clears the I2Cx's pending flags.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   I2C_FLAG :
*\*\          - I2C_FLAG_ADR        Address matched(Slave mode)
*\*\          - I2C_FLAG_NAKF       NACK flag received
*\*\          - I2C_FLAG_STOPF      STOP detection flag
*\*\          - I2C_FLAG_BSER       BUS Error flag
*\*\          - I2C_FLAG_ABLO          Arbitration lost flag
*\*\          - I2C_FLAG_OVF          Overrun/Underrun flag(Slave mode)
*\*\          - I2C_FLAG_CRCERR     CRC Error flag in reception
*\*\          - I2C_FLAG_TMOUT      Timeout or tLOW detection flag
*\*\          - I2C_FLAG_ALRT       SMBUS alert flag
*\*\return  none
**/
void I2C_ClrFlag(I2C_Module* I2Cx, uint32_t I2C_FLAG)
{
    /* Clear the selected I2C flag */
    I2Cx->INTCLR |= I2C_FLAG;
}


/**
*\*\name    I2C_ConfigInt.
*\*\fun     Enables or disables the specified I2C interrupts.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   I2C_IT :
*\*\          - I2C_INT_WDR           TX interrupt enable
*\*\          - I2C_INT_RDR           RX interrupt enable
*\*\          - I2C_INT_ADR           Address match interrupt enable
*\*\          - I2C_INT_NACK          Not acknowledge received Interrupt enable
*\*\          - I2C_INT_STOP          Stop detection interrupt enable
*\*\          - I2C_INT_TFC           Transfer complete interrupt enable
*\*\          - I2C_INT_ERR           Error interrupt enable
*\*\          - I2C_INT_RXFIFO        FIFO RX interrupt enable
*\*\          - I2C_INT_TXFIFO        FIFO TX interrupt enable
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2C_ConfigInt(I2C_Module* I2Cx, uint32_t I2C_IT, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C interrupts */
        I2Cx->CTRL1 |= I2C_IT;
    }
    else
    {
        /* Disable the selected I2C interrupts */
        I2Cx->CTRL1 &= (uint32_t)~I2C_IT;
    }
}

/**
*\*\name    I2C_GetCRC.
*\*\fun     Get the PEC value for the specified I2C.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\return  The PEC value
**/
uint8_t I2C_GetCRC(I2C_Module* I2Cx)
{
    /* Return the selected I2C PEC value */
    return (uint8_t)(I2Cx->CRCR);
}

/**
*\*\name    I2C_GetReceiveAddress.
*\*\fun     Get the received address value for the specified I2C.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\return  The received address value
**/
uint8_t I2C_GetReceiveAddress(I2C_Module* I2Cx)
{
    /* Return the selected I2C PEC value */
    return (uint8_t)((I2Cx->STSINT & STSINT_ADRRCV_MASK) >> 17);
}

/**
*\*\name    I2C_GetFlag.
*\*\fun     Checks whether the specified I2C flag is set or not.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\          - I2C5
*\*\          - I2C6
*\*\          - I2C7
*\*\          - I2C8
*\*\          - I2C9
*\*\          - I2C10
*\*\param   I2C_FLAG :
*\*\          - I2C_FLAG_WRE        Write data register empty
*\*\          - I2C_FLAG_WRAVL      Write availabe
*\*\          - I2C_FLAG_RDAVL      Receive data availabe
*\*\          - I2C_FLAG_ADR        Address matched(Slave mode)
*\*\          - I2C_FLAG_NAKF       NACK flag received
*\*\          - I2C_FLAG_STOPF      STOP detection flag
*\*\          - I2C_FLAG_TFC        Transfer Complete(Master mode)
*\*\          - I2C_FLAG_TFCR       Transfer Complete Refill
*\*\          - I2C_FLAG_BSER       BUS Error flag
*\*\          - I2C_FLAG_ABLO       Arbitration lost flag
*\*\          - I2C_FLAG_OVF        Overrun/Underrun flag(Slave mode)
*\*\          - I2C_FLAG_CRCERR     CRC Error flag in reception
*\*\          - I2C_FLAG_TMOUT      Timeout or tLOW detection flag
*\*\          - I2C_FLAG_ALRT       SMBUS alert flag
*\*\          - I2C_FLAG_QADR       Quick command address matched
*\*\          - I2C_FLAG_BUSY       BUS busy flag
*\*\          - I2C_FLAG_DIR        Transfer direction
*\*\          - I2C_FLAG_FRXNE      Receive FIFO not empty flag
*\*\          - I2C_FLAG_FTXIS      Transmit FIFO empty flag
*\*\return  SET or RESET
*\*\note    none.
**/
FlagStatus I2C_GetFlag(I2C_Module* I2Cx, uint32_t I2C_FLAG)
{
    FlagStatus bitstatus;

    if ((I2Cx->STSINT & I2C_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}




