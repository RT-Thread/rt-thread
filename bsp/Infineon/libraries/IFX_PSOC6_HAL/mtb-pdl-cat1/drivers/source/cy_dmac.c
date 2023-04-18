/***************************************************************************//**
* \file cy_dmac.c
* \version 1.30.1
*
* \brief
* The source code file for the DMAC driver.
*
********************************************************************************
* \copyright
* Copyright 2018-2022 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include "cy_device.h"

#if defined (CY_IP_M4CPUSS_DMAC) || defined (CY_IP_MXAHBDMAC) || defined (CY_IP_M7CPUSS_DMAC)


#include "cy_dmac.h"

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 11.3', 8, \
'The cast to another type is made intentionally. \
These structures are subset of the main structure cy_stc_dmac_descriptor_t. \
This will provide better code readability with the type of data transfer used');

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 10.8', 2, \
'Value extracted from _VAL2FLD macro will not exceed enum range.');

/*******************************************************************************
* Function Name: Cy_DMAC_Descriptor_Init
****************************************************************************//**
*
* Initializes the descriptor structure in SRAM from a pre-initialized
* configuration structure.
* This function initializes only the descriptor and not the channel.
*
* \param descriptor
* The descriptor structure instance.
*
* \param config
* This is a configuration structure that has all initialization information for
* the descriptor.
*
* \return
* The status /ref cy_en_dmac_status_t.
*
* \funcusage
* \snippet dmac/snippet/main.c snippet_Cy_DMAC_Enable
*
*******************************************************************************/
cy_en_dmac_status_t Cy_DMAC_Descriptor_Init(cy_stc_dmac_descriptor_t * descriptor, const cy_stc_dmac_descriptor_config_t * config)
{
    cy_en_dmac_status_t ret = CY_DMAC_BAD_PARAM;

    if ((NULL != descriptor) && (NULL != config))
    {
        CY_ASSERT_L3(CY_DMAC_IS_RETRIGGER_VALID(config->retrigger));
        CY_ASSERT_L3(CY_DMAC_IS_TRIG_TYPE_VALID(config->interruptType));
        CY_ASSERT_L3(CY_DMAC_IS_TRIG_TYPE_VALID(config->triggerOutType));
        CY_ASSERT_L3(CY_DMAC_IS_TRIG_TYPE_VALID(config->triggerInType));
        CY_ASSERT_L3(CY_DMAC_IS_XFER_SIZE_VALID(config->srcTransferSize));
        CY_ASSERT_L3(CY_DMAC_IS_XFER_SIZE_VALID(config->dstTransferSize));
        CY_ASSERT_L3(CY_DMAC_IS_CHANNEL_STATE_VALID(config->channelState));
        CY_ASSERT_L3(CY_DMAC_IS_DATA_SIZE_VALID(config->dataSize));
        CY_ASSERT_L3(CY_DMAC_IS_TYPE_VALID(config->descriptorType));

        descriptor->ctl =
            _VAL2FLD(DMAC_CH_V2_DESCR_CTL_WAIT_FOR_DEACT, config->retrigger) |
            _VAL2FLD(DMAC_CH_V2_DESCR_CTL_INTR_TYPE, config->interruptType) |
            _VAL2FLD(DMAC_CH_V2_DESCR_CTL_TR_OUT_TYPE, config->triggerOutType) |
            _VAL2FLD(DMAC_CH_V2_DESCR_CTL_TR_IN_TYPE, config->triggerInType) |
           _BOOL2FLD(DMAC_CH_V2_DESCR_CTL_DATA_PREFETCH, config->dataPrefetch) |
            _VAL2FLD(DMAC_CH_V2_DESCR_CTL_SRC_TRANSFER_SIZE, config->srcTransferSize) |
            _VAL2FLD(DMAC_CH_V2_DESCR_CTL_DST_TRANSFER_SIZE, config->dstTransferSize) |
            _VAL2FLD(DMAC_CH_V2_DESCR_CTL_CH_DISABLE, config->channelState) |
            _VAL2FLD(DMAC_CH_V2_DESCR_CTL_DATA_SIZE, config->dataSize) |
            _VAL2FLD(DMAC_CH_V2_DESCR_CTL_DESCR_TYPE, config->descriptorType);

        descriptor->src = (uint32_t)config->srcAddress;

        if(CY_DMAC_SCATTER_TRANSFER != config->descriptorType)
        {
            Cy_DMAC_Descriptor_SetDstAddress(descriptor, config->dstAddress);
        }

        if(CY_DMAC_SINGLE_TRANSFER != config->descriptorType)
        {
            Cy_DMAC_Descriptor_SetXloopDataCount(descriptor, config->xCount);
        }

        Cy_DMAC_Descriptor_SetNextDescriptor(descriptor, config->nextDescriptor);

        if((CY_DMAC_1D_TRANSFER == config->descriptorType) ||
           (CY_DMAC_2D_TRANSFER == config->descriptorType))
        {
            CY_ASSERT_L2(CY_DMAC_IS_LOOP_INCR_VALID(config->srcXincrement));
            CY_ASSERT_L2(CY_DMAC_IS_LOOP_INCR_VALID(config->dstXincrement));

            descriptor->xIncr = _VAL2FLD(DMAC_CH_V2_DESCR_X_INCR_SRC_X, config->srcXincrement) |
                                _VAL2FLD(DMAC_CH_V2_DESCR_X_INCR_DST_X, config->dstXincrement);
        }

        if(CY_DMAC_2D_TRANSFER == config->descriptorType)
        {
            Cy_DMAC_Descriptor_SetYloopDataCount(descriptor, config->yCount);

            CY_ASSERT_L2(CY_DMAC_IS_LOOP_INCR_VALID(config->srcYincrement));
            CY_ASSERT_L2(CY_DMAC_IS_LOOP_INCR_VALID(config->dstYincrement));

            descriptor->yIncr = _VAL2FLD(DMAC_CH_V2_DESCR_Y_INCR_SRC_Y, config->srcYincrement) |
                                _VAL2FLD(DMAC_CH_V2_DESCR_Y_INCR_DST_Y, config->dstYincrement);
        }

        ret = CY_DMAC_SUCCESS;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_DMAC_Descriptor_DeInit
****************************************************************************//**
*
* Clears the content of the specified descriptor.
*
* \param descriptor
* The descriptor structure instance.
*
* \funcusage
* \snippet dmac/snippet/main.c snippet_Cy_DMAC_Descriptor_Deinit
*
*******************************************************************************/
void Cy_DMAC_Descriptor_DeInit(cy_stc_dmac_descriptor_t * descriptor)
{
    descriptor->ctl = 0UL;
    descriptor->src = 0UL;
    descriptor->dst = 0UL;
    descriptor->xSize = 0UL;
    descriptor->xIncr = 0UL;
    descriptor->ySize = 0UL;
    descriptor->yIncr = 0UL;
    descriptor->nextPtr = 0UL;
}


/*******************************************************************************
* Function Name: Cy_DMAC_Channel_Init
****************************************************************************//**
*
* Initializes the DMAC channel with a descriptor and other parameters.
*
* \param base
* The pointer to the hardware DMAC block.
*
* \param channel
* A channel number.
*
* \param config
* The structure that has the initialization information for the
* channel.
*
* \return
* The status /ref cy_en_dmac_status_t.
*
* \funcusage
* \snippet dmac/snippet/main.c snippet_Cy_DMAC_Enable
*
*******************************************************************************/
cy_en_dmac_status_t Cy_DMAC_Channel_Init(DMAC_Type * base, uint32_t channel, cy_stc_dmac_channel_config_t const * config)
{
    cy_en_dmac_status_t ret = CY_DMAC_BAD_PARAM;

    if ((NULL != base) && (CY_DMAC_IS_CH_NR_VALID(channel)) && (NULL != config) && (NULL != config->descriptor))
    {
        CY_ASSERT_L2(CY_DMAC_IS_PRIORITY_VALID(config->priority));

        /* Set the current descriptor */
        DMAC_CH_CURR(base, channel) = (uint32_t)config->descriptor;

        /* Set the channel configuration */
        DMAC_CH_CTL(base, channel) = _VAL2FLD(DMAC_CH_V2_CTL_PRIO,    config->priority) |
                                    _BOOL2FLD(DMAC_CH_V2_CTL_ENABLED, config->enable)   |
                                    _BOOL2FLD(DMAC_CH_V2_CTL_B,       config->bufferable);
        ret = CY_DMAC_SUCCESS;
    }

    return (ret);
}


/*******************************************************************************
* Function Name: Cy_DMAC_Channel_DeInit
****************************************************************************//**
*
* Clears the content of registers corresponding to the channel.
*
* \param base
* The pointer to the hardware DMAC block.
*
* \param channel
* A channel number.
*
* \funcusage
* \snippet dmac/snippet/main.c snippet_Cy_DMAC_Disable
*
*******************************************************************************/
void Cy_DMAC_Channel_DeInit(DMAC_Type * base, uint32_t channel)
{
    CY_ASSERT_L1(CY_DMAC_IS_CH_NR_VALID(channel));

    DMAC_CH_CTL(base, channel) = 0UL;
    DMAC_CH_CURR(base, channel) = 0UL;
    DMAC_CH_INTR_MASK(base, channel) = 0UL;
}


/*******************************************************************************
* Function Name: Cy_DMAC_Descriptor_GetXloopDataCount
****************************************************************************//**
*
* Returns the number of data elements for the X loop of the specified
* descriptor (for all descriptor types except single transfer).
*
* Based on the descriptor type, the offset of the address for the xCount
* register may vary:
* For the scatter transfer descriptors type, this register is at offset 0x8.
* For all the rest supported descriptor types, this register is at offset 0xc.
*
* \param descriptor
* The descriptor structure instance.
*
* \return
* The number of data elements to transfer in the X loop.
* For scatter transfer descriptors the X loop count unit is
*  an [address, data] pair (two words, or 8 bytes).
* For memory copy descriptors X loop count unit is one byte.
* For all the rest descriptors (except single transfer) the X loop count unit
*  is specified by the data transfer size /ref cy_en_dmac_data_size_t.
*
* \funcusage
* \snippet dmac/snippet/main.c snippet_Cy_DMAC_Descriptor_GetterFunctions
*
*******************************************************************************/
uint32_t Cy_DMAC_Descriptor_GetXloopDataCount(cy_stc_dmac_descriptor_t const * descriptor)
{
    uint32_t retVal = 0UL;
    cy_en_dmac_descriptor_type_t locDescriptorType = Cy_DMAC_Descriptor_GetDescriptorType(descriptor);

    CY_ASSERT_L1(CY_DMAC_SINGLE_TRANSFER != locDescriptorType);

    if (CY_DMAC_SCATTER_TRANSFER == locDescriptorType)
    {
        /* Convert the data count from the machine range (0-65535) into the user's range (1-32768). */
        retVal = (_FLD2VAL(DMAC_CH_V2_DESCR_X_SIZE_X_COUNT, ((cy_stc_dmac_dscr_scatter_t const*)descriptor)->xSize) + 1UL) / 2UL;
    }
    else
    {
        /* Convert the data count from the machine range (0-65535) into the user's range (1-65536). */
        retVal = _FLD2VAL(DMAC_CH_V2_DESCR_X_SIZE_X_COUNT, descriptor->xSize) + 1UL;
    }

    return (retVal);
}


/*******************************************************************************
* Function Name: Cy_DMAC_Descriptor_SetXloopDataCount
****************************************************************************//**
*
* Sets the number of data elements to transfer in the X loop
* for the specified descriptor (for all descriptor types except single transfer).
*
* Based on the descriptor type, the offset of the address for the xCount
* register may vary:
* For the scatter transfer descriptors type, this register is at offset 0x8.
* For all the rest of the supported descriptor types, this register is at offset 0xc.
*
* \param descriptor
* The descriptor structure instance.
*
* \param xCount
* The number of data elements to transfer in the X loop.
* For scatter transfer descriptors the valid range is 1...32768.
* For all the rest of the descriptors (except single transfer), the valid range is 1...65536.
*
* \funcusage
* \snippet dmac/snippet/main.c snippet_Cy_DMAC_Descriptor_SetterFunctions
*
*******************************************************************************/
void Cy_DMAC_Descriptor_SetXloopDataCount(cy_stc_dmac_descriptor_t * descriptor, uint32_t xCount)
{
    cy_en_dmac_descriptor_type_t locDescriptorType = Cy_DMAC_Descriptor_GetDescriptorType(descriptor);

    CY_ASSERT_L1(CY_DMAC_SINGLE_TRANSFER != locDescriptorType);

    if (CY_DMAC_SCATTER_TRANSFER == locDescriptorType)
    {
        CY_ASSERT_L2(CY_DMAC_IS_SCATTER_COUNT_VALID(xCount));
        /* Convert the data count from the user's range (1-32768) into the machine range (0-65535). */
        ((cy_stc_dmac_dscr_scatter_t*)descriptor)->xSize = _VAL2FLD(DMAC_CH_V2_DESCR_X_SIZE_X_COUNT, (xCount * 2UL) - 1UL);
    }
    else
    {
        CY_ASSERT_L2(CY_DMAC_IS_LOOP_COUNT_VALID(xCount));
        /* Convert the data count from the user's range (1-65536) into the machine range (0-65535). */
        descriptor->xSize = _VAL2FLD(DMAC_CH_V2_DESCR_X_SIZE_X_COUNT, xCount - 1UL);
    }
}


/*******************************************************************************
* Function Name: Cy_DMAC_Descriptor_SetNextDescriptor
****************************************************************************//**
*
* Sets a Next Descriptor parameter for the specified descriptor.
*
* Based on the descriptor type, the offset of the address for the next descriptor
* register may vary:
* For the single and scatter transfer descriptors, this register is at offset 0x0c.
* For the memory copy descriptor type, this register is at offset 0x10.
* For the 1D-transfer descriptor type, this register is at offset 0x14.
* For the 2D-transfer descriptor type, this register is at offset 0x1c.
*
* \param descriptor
* The descriptor structure instance.
*
* \param nextDescriptor
* The pointer to the next descriptor.
* For CAT1C devices this pointer needs to point to 32 byte aligned structure.
*
* \funcusage
* \snippet dmac/snippet/main.c snippet_Cy_DMAC_Descriptor_SetterFunctions
*
*******************************************************************************/
void Cy_DMAC_Descriptor_SetNextDescriptor(cy_stc_dmac_descriptor_t * descriptor, cy_stc_dmac_descriptor_t const * nextDescriptor)
{
    CY_ASSERT_L1(NULL != descriptor);

    switch((cy_en_dmac_descriptor_type_t)_FLD2VAL(DMAC_CH_V2_DESCR_CTL_DESCR_TYPE, descriptor->ctl))
    {
        case CY_DMAC_SINGLE_TRANSFER:
        case CY_DMAC_SCATTER_TRANSFER:
            /* The next pointer is on the same offset for single and scatter descriptors */
            ((cy_stc_dmac_dscr_single_t*)descriptor)->nextPtr = (uint32_t)nextDescriptor;
            break;

        case CY_DMAC_MEMORY_COPY:
            ((cy_stc_dmac_dscr_memcpy_t*)descriptor)->nextPtr = (uint32_t)nextDescriptor;
            break;

        case CY_DMAC_1D_TRANSFER:
            ((cy_stc_dmac_dscr_1d_t*)descriptor)->nextPtr = (uint32_t)nextDescriptor;
            break;

        case CY_DMAC_2D_TRANSFER:
            ((cy_stc_dmac_dscr_2d_t*)descriptor)->nextPtr = (uint32_t)nextDescriptor;
            break;

        default:
            /* Unsupported type of descriptor */
            break;
    }
}


/*******************************************************************************
* Function Name: Cy_DMAC_Descriptor_GetNextDescriptor
****************************************************************************//**
*
* Returns a next descriptor address of the specified descriptor.
*
* Based on the descriptor type, the offset of the address for the next descriptor
* register may vary:
* For the single and scatter transfer descriptors, this register is at offset 0x0c.
* For the memory copy descriptor type, this register is at offset 0x10.
* For the 1D-transfer descriptor type, this register is at offset 0x14.
* For the 2D-transfer descriptor type, this register is at offset 0x1c.
*
* \param descriptor
* The descriptor structure instance.
*
* \return
* The pointer to the next descriptor.
*
* \funcusage
* \snippet dmac/snippet/main.c snippet_Cy_DMAC_Descriptor_GetterFunctions
*
*******************************************************************************/
cy_stc_dmac_descriptor_t * Cy_DMAC_Descriptor_GetNextDescriptor(cy_stc_dmac_descriptor_t const * descriptor)
{
    uint32_t retVal = 0UL;

    switch((cy_en_dmac_descriptor_type_t)_FLD2VAL(DMAC_CH_V2_DESCR_CTL_DESCR_TYPE, descriptor->ctl))
    {
        case CY_DMAC_SINGLE_TRANSFER:
        case CY_DMAC_SCATTER_TRANSFER:
            /* The next pointer is on the same offset for single and scatter descriptors */
            retVal = ((cy_stc_dmac_dscr_single_t const*)descriptor)->nextPtr;
            break;

        case CY_DMAC_MEMORY_COPY:
            retVal = ((cy_stc_dmac_dscr_memcpy_t const*)descriptor)->nextPtr;
            break;

        case CY_DMAC_1D_TRANSFER:
            retVal = ((cy_stc_dmac_dscr_1d_t const*)descriptor)->nextPtr;
            break;

        case CY_DMAC_2D_TRANSFER:
            retVal = ((cy_stc_dmac_dscr_2d_t const*)descriptor)->nextPtr;
            break;

        default:
            /* An unsupported type of the descriptor */
            break;
    }

    return ((cy_stc_dmac_descriptor_t*)retVal);
}


/*******************************************************************************
* Function Name: Cy_DMAC_Descriptor_SetDescriptorType
****************************************************************************//**
*
* Sets the descriptor's type for the specified descriptor.
* Moves the next descriptor pointer and X data count values into the proper
* offset in accordance to the actual descriptor type.
*
* During the descriptor's type change, carefully set up the settings starting
* from dstAddress and all the rest below in the \ref cy_stc_dmac_descriptor_config_t
* structure. This is because the content of the descriptor registers might be
* lost/overridden by other descriptor settings due to the
* different registers structure for different descriptor types.
*
* \param descriptor
* The descriptor structure instance.
*
* \param descriptorType
* The descriptor type \ref cy_en_dmac_descriptor_type_t.
*
* \funcusage
* \snippet dmac/snippet/main.c snippet_Cy_DMAC_Descriptor_SetterFunctions
*
*******************************************************************************/
void Cy_DMAC_Descriptor_SetDescriptorType(cy_stc_dmac_descriptor_t * descriptor, cy_en_dmac_descriptor_type_t descriptorType)
{
    CY_ASSERT_L3(CY_DMAC_IS_TYPE_VALID(descriptorType));

    if (descriptorType != Cy_DMAC_Descriptor_GetDescriptorType(descriptor)) /* Do not perform if the type is not changed */
    {
        /* Store the current nextDescriptor pointer. */
        cy_stc_dmac_descriptor_t const *locNextDescriptor = Cy_DMAC_Descriptor_GetNextDescriptor(descriptor);
        /* Store the current X data counter. */
        uint32_t locXcount = Cy_DMAC_Descriptor_GetXloopDataCount(descriptor);
        /* Change the descriptor type. */
        CY_REG32_CLR_SET(descriptor->ctl, DMAC_CH_V2_DESCR_CTL_DESCR_TYPE, descriptorType);
        /* Restore the current X data counter. */
        Cy_DMAC_Descriptor_SetXloopDataCount(descriptor, locXcount);
        /* Restore the nextDescriptor pointer into the proper place. */
        Cy_DMAC_Descriptor_SetNextDescriptor(descriptor, locNextDescriptor);
    }
}

CY_MISRA_BLOCK_END('MISRA C-2012 Rule 11.3');
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 10.8');

#endif /* CY_IP_M4CPUSS_DMAC, CY_IP_MXAHBDMAC */

/* [] END OF FILE */
