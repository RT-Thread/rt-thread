/*
* Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* o Redistributions of source code must retain the above copyright notice, this list
*   of conditions and the following disclaimer.
*
* o Redistributions in binary form must reproduce the above copyright notice, this
*   list of conditions and the following disclaimer in the documentation and/or
*   other materials provided with the distribution.
*
* o Neither the name of Freescale Semiconductor, Inc. nor the names of its
*   contributors may be used to endorse or promote products derived from this
*   software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "fsl_edma_hal.h"
#if FSL_FEATURE_SOC_EDMA_COUNT

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_Init
 * Description   : Initializes eDMA module to known state.
 *
 *END**************************************************************************/
void EDMA_HAL_Init(DMA_Type * base)
{
    uint32_t i;

    /* Clear the bit of CR register */
    DMA_BWR_CR_CLM(base, 0U);
    DMA_BWR_CR_CX(base, 0U);
    DMA_BWR_CR_ECX(base, 0U);
    DMA_BWR_CR_EDBG(base, 0U);
    DMA_BWR_CR_EMLM(base, 0U);
    DMA_BWR_CR_ERCA(base, 0U);
    /* If group count more than 1, need to set group priority. */
#if (FSL_FEATURE_EDMA_CHANNEL_GROUP_COUNT > 1)
    EDMA_HAL_SetGroupArbitrationMode(base,kEDMAGroupArbitrationFixedPriority);
    EDMA_HAL_SetGroupPriority(base,kEDMAGroup0PriorityHighGroup1PriorityLow);
#endif

    for (i = 0; i < FSL_FEATURE_EDMA_MODULE_CHANNEL; i++)
    {
        EDMA_HAL_HTCDClearReg(base, i);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_CancelTransfer
 * Description   : Cancels the remaining data transfer.
 *
 *END**************************************************************************/
void EDMA_HAL_CancelTransfer(DMA_Type * base)
{
    DMA_BWR_CR_CX(base, 1U);
    while (DMA_BRD_CR_CX(base))
    {}
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_ErrorCancelTransfer
 * Description   : Cancels the remaining data transfer and treat it as error.
 *
 *END**************************************************************************/
void EDMA_HAL_ErrorCancelTransfer(DMA_Type * base)
{
    DMA_BWR_CR_ECX(base, 1U);
    while (DMA_BRD_CR_ECX(base))
    {}
}

#if (FSL_FEATURE_EDMA_CHANNEL_GROUP_COUNT > 0x1U)
/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_SetGroupPriority
 * Description   : Configures the priority for group 0 and group 1.
 *
 *END**************************************************************************/
void EDMA_HAL_SetGroupPriority(DMA_Type * base, edma_group_priority_t groupPriority)
{

    if (groupPriority == kEDMAGroup0PriorityLowGroup1PriorityHigh)
    {
        DMA_BWR_CR_GRP0PRI(base, 0U);
        DMA_BWR_CR_GRP1PRI(base, 1U);
    }
    else
    {
        DMA_BWR_CR_GRP0PRI(base, 1U);
        DMA_BWR_CR_GRP1PRI(base, 0U);
    }

}
#endif
/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_SetErrorIntCmd
 * Description   : Enable/Disable error interrupt for channels.
 *
 *END**************************************************************************/
void EDMA_HAL_SetErrorIntCmd(DMA_Type * base, bool enable, edma_channel_indicator_t channel)
{

    if (enable)
    {
        DMA_WR_SEEI(base, channel);
    }
    else
    {
        DMA_WR_CEEI(base, channel);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_GetErrorStatus
 * Description   : Get EDMA error status.
 *
 *END**************************************************************************/
edma_error_status_all_t EDMA_HAL_GetErrorStatus(DMA_Type * base)
{
    uint32_t val = DMA_RD_ES(base);
    edma_error_status_all_t status;
    status.destinationBusError = (bool)(val & DMA_ES_DBE_MASK);
    status.sourceBusError = (bool)((val & DMA_ES_SBE_MASK) >> DMA_ES_SBE_SHIFT);
    status.scatterOrGatherConfigurationError = (bool)
        ((val & DMA_ES_SGE_MASK) >> DMA_ES_SGE_SHIFT);
    status.nbyteOrCiterConfigurationError = (bool)
        ((val & DMA_ES_NCE_MASK) >> DMA_ES_NCE_SHIFT);
    status.destinationOffsetError = (bool)((val & DMA_ES_DOE_MASK) >> DMA_ES_DOE_SHIFT);
    status.destinationAddressError = (bool)((val & DMA_ES_DAE_MASK) >> DMA_ES_DAE_SHIFT);
    status.sourceOffsetError = (bool)((val & DMA_ES_SOE_MASK) >> DMA_ES_SOE_SHIFT);
    status.sourceAddressError = (bool)((val & DMA_ES_SAE_MASK) >> DMA_ES_SAE_SHIFT);
    status.errorChannel = (uint8_t)((val & DMA_ES_ERRCHN_MASK) >> DMA_ES_ERRCHN_SHIFT);
    status.channelPriorityError = (bool)((val & DMA_ES_CPE_MASK) >> DMA_ES_CPE_SHIFT);
#if FSL_FEATURE_EDMA_CHANNEL_GROUP_COUNT > 1
    status.groupPriorityError = (bool)((val & DMA_ES_GPE_MASK) >> DMA_ES_GPE_SHIFT);
#endif
    status.transferCancelledError = (bool)((val & DMA_ES_ECX_MASK) >> DMA_ES_ECX_SHIFT);
    status.orOfAllError = (bool)((val & DMA_ES_VLD_MASK) >> DMA_ES_VLD_SHIFT);
    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_SetDmaRequestCmd
 * Description   : Enable/Disable dma request for channel or all channels.
 *
 *END**************************************************************************/
void EDMA_HAL_SetDmaRequestCmd(DMA_Type * base, edma_channel_indicator_t channel,bool enable)
{

    if (enable)
    {
        DMA_WR_SERQ(base, channel);
    }
    else
    {
        DMA_WR_CERQ(base, channel);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_HTCDClearReg
 * Description   : Set registers to 0 for hardware TCD of eDMA channel.
 *
 *END**************************************************************************/
void EDMA_HAL_HTCDClearReg(DMA_Type * base,uint32_t channel)
{
    DMA_WR_SADDR(base, channel, 0U);
    DMA_WR_SOFF(base, channel, 0U);
    DMA_WR_ATTR(base, channel, 0U);
    DMA_WR_NBYTES_MLNO(base, channel, 0U);
    DMA_WR_SLAST(base, channel, 0U);
    DMA_WR_DADDR(base, channel, 0U);
    DMA_WR_DOFF(base, channel, 0U);
    DMA_WR_CITER_ELINKNO(base, channel, 0U);
    DMA_WR_DLAST_SGA(base, channel, 0U);
    DMA_WR_CSR(base, channel, 0U);
    DMA_WR_BITER_ELINKNO(base, channel, 0U);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_HTCDSetAttribute
 * Description   : Configures the transfer attribute for eDMA channel.
 *
 *END**************************************************************************/
void EDMA_HAL_HTCDSetAttribute(
                DMA_Type * base, uint32_t channel,
                edma_modulo_t srcModulo, edma_modulo_t destModulo,
                edma_transfer_size_t srcTransferSize, edma_transfer_size_t destTransferSize)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);

    DMA_WR_ATTR(base, channel,
            DMA_ATTR_SMOD(srcModulo) | DMA_ATTR_DMOD(destModulo) |
            DMA_ATTR_SSIZE(srcTransferSize) | DMA_ATTR_DSIZE(destTransferSize));

}
/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_HTCDSetNbytes
 * Description   : Configures the nbytes for eDMA channel.
 *
 *END**************************************************************************/
void EDMA_HAL_HTCDSetNbytes(DMA_Type * base, uint32_t channel, uint32_t nbytes)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);

    if (DMA_BRD_CR_EMLM(base))
    {
        if (!(DMA_BRD_NBYTES_MLOFFNO_SMLOE(base, channel) ||
                                 DMA_BRD_NBYTES_MLOFFNO_DMLOE(base, channel)))
        {
            DMA_BWR_NBYTES_MLOFFNO_NBYTES(base, channel, nbytes);
        }
        else
        {
            DMA_BWR_NBYTES_MLOFFYES_NBYTES(base, channel, nbytes);
        }

    }
    else
    {
        DMA_WR_NBYTES_MLNO(base, channel, nbytes);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_HTCDGetNbytes
 * Description   : Get nbytes configuration data.
 *
 *END**************************************************************************/
uint32_t EDMA_HAL_HTCDGetNbytes(DMA_Type * base, uint32_t channel)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);

    if (DMA_BRD_CR_EMLM(base))
    {
        if (DMA_BRD_NBYTES_MLOFFYES_SMLOE(base, channel) ||
                DMA_BRD_NBYTES_MLOFFYES_DMLOE(base, channel))
        {
            return DMA_BRD_NBYTES_MLOFFYES_NBYTES(base, channel);
        }
        else
        {
            return DMA_BRD_NBYTES_MLOFFNO_NBYTES(base, channel);
        }
    }
    else
    {
        return DMA_RD_NBYTES_MLNO(base, channel);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_HTCDSetMinorLoopOffset
 * Description   : Configures the minorloop offset for the hardware TCD.
 *
 *END**************************************************************************/
void EDMA_HAL_HTCDSetMinorLoopOffset(
                DMA_Type * base, uint32_t channel, edma_minorloop_offset_config_t *config)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    if ((config->enableSrcMinorloop == true) || (config->enableDestMinorloop == true))
    {
        DMA_BWR_CR_EMLM(base, true);
        DMA_BWR_NBYTES_MLOFFYES_SMLOE(base, channel, config->enableSrcMinorloop);
        DMA_BWR_NBYTES_MLOFFYES_DMLOE(base, channel, config->enableDestMinorloop);
        DMA_BWR_NBYTES_MLOFFYES_MLOFF(base, channel, config->offset);
    }
}
/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_HTCDSetScatterGatherLink
 * Description   : Configures the memory address for the next transfer TCD
 * for the hardware TCD.
 *
 *END**************************************************************************/
void EDMA_HAL_HTCDSetScatterGatherLink(
                DMA_Type * base, uint32_t channel, edma_software_tcd_t *stcd)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    DMA_BWR_CSR_ESG(base, channel, true);
    DMA_WR_DLAST_SGA (base, channel, (uint32_t)stcd);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_HTCDSetChannelMinorLink
 * Description   : Set Channel minor link for hardware TCD.
 *
 *END**************************************************************************/
void EDMA_HAL_HTCDSetChannelMinorLink(
                DMA_Type * base, uint32_t channel, uint32_t linkChannel, bool enable)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);

    if (enable)
    {
        DMA_BWR_BITER_ELINKYES_ELINK(base, channel, enable);
        DMA_BWR_BITER_ELINKYES_LINKCH(base, channel, linkChannel);
        DMA_BWR_CITER_ELINKYES_ELINK(base, channel, enable);
        DMA_BWR_CITER_ELINKYES_LINKCH(base, channel, linkChannel);
    }
    else
    {
        DMA_BWR_BITER_ELINKNO_ELINK(base, channel, enable);
        DMA_BWR_CITER_ELINKNO_ELINK(base, channel, enable);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_HTCD_HTCDSetMajorCount
 * Description   : Sets the major iteration count according to minor loop
 * channel link setting.
 *
 *END**************************************************************************/
void EDMA_HAL_HTCDSetMajorCount(DMA_Type * base, uint32_t channel, uint32_t count)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);

    if (DMA_BRD_BITER_ELINKNO_ELINK(base, channel))
    {
        DMA_BWR_BITER_ELINKYES_BITER(base, channel, count);
        DMA_BWR_CITER_ELINKYES_CITER(base, channel, count);
    }
    else
    {
        DMA_BWR_BITER_ELINKNO_BITER(base, channel, count);
        DMA_BWR_CITER_ELINKNO_CITER(base, channel, count);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_HTCDGetBeginMajorCount
 * Description   : Gets the begin major iteration count according to minor loop
 * channel link setting.
 *
 *END**************************************************************************/
uint32_t EDMA_HAL_HTCDGetBeginMajorCount(DMA_Type * base, uint32_t channel)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);

    if (DMA_BRD_BITER_ELINKNO_ELINK(base, channel))
    {
        return DMA_BRD_BITER_ELINKYES_BITER(base, channel);
    }
    else
    {
        return DMA_BRD_BITER_ELINKNO_BITER(base, channel);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_HTCDGetCurrentMajorCount
 * Description   : Gets the current major iteration count according to minor
 * loop channel link setting.
 *
 *END**************************************************************************/
uint32_t EDMA_HAL_HTCDGetCurrentMajorCount(DMA_Type * base, uint32_t channel)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);

    if (DMA_BRD_BITER_ELINKNO_ELINK(base, channel))
    {
        return DMA_BRD_CITER_ELINKYES_CITER(base, channel);
    }
    else
    {
        return DMA_BRD_CITER_ELINKNO_CITER(base, channel);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_HTCDGetUnfinishedBytes
 * Description   : Get the bytes number of bytes haven't been transferred for
 * this hardware TCD.
 *
 *END**************************************************************************/
uint32_t EDMA_HAL_HTCDGetUnfinishedBytes(DMA_Type * base, uint32_t channel)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);

    uint32_t nbytes;

    nbytes = EDMA_HAL_HTCDGetNbytes(base, channel);

    if (DMA_BRD_BITER_ELINKNO_ELINK(base, channel))
    {
        return (DMA_BRD_CITER_ELINKYES_CITER(base, channel) * nbytes);

    }
    else
    {
        return (DMA_BRD_CITER_ELINKNO_CITER(base, channel) * nbytes);

    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_HTCDGetFinishedBytes
 * Description   : Get the bytes number of bytes already be transferred for this
 * hardware TCD.
 *
 *END**************************************************************************/
uint32_t EDMA_HAL_HTCDGetFinishedBytes(DMA_Type * base, uint32_t channel)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);

    uint32_t nbytes, begin_majorcount, current_majorcount;

    nbytes = EDMA_HAL_HTCDGetNbytes(base, channel);
    begin_majorcount = EDMA_HAL_HTCDGetBeginMajorCount(base,channel);
    current_majorcount = EDMA_HAL_HTCDGetCurrentMajorCount(base,channel);

    return ((begin_majorcount - current_majorcount) * nbytes);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_STCDSetAttribute
 * Description   : Configures the transfer attribute for software TCD.
 *
 *END**************************************************************************/
void EDMA_HAL_STCDSetAttribute(
                edma_software_tcd_t *stcd,
                edma_modulo_t srcModulo, edma_modulo_t destModulo,
                edma_transfer_size_t srcTransferSize, edma_transfer_size_t destTransferSize)
{
    assert(stcd);

    stcd->ATTR = DMA_ATTR_SMOD(srcModulo) | DMA_ATTR_DMOD(destModulo) |
                    DMA_ATTR_SSIZE(srcTransferSize) | DMA_ATTR_DSIZE(destTransferSize);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_STCDSetNbytes
 * Description   : Configures the nbytes for software TCD
 *
 *END**************************************************************************/
void EDMA_HAL_STCDSetNbytes(DMA_Type * base, edma_software_tcd_t *stcd, uint32_t nbytes)
{
    assert(stcd);

    if (DMA_BRD_CR_EMLM(base))
    {
        if (stcd->NBYTES | (DMA_NBYTES_MLOFFNO_SMLOE_MASK | DMA_NBYTES_MLOFFNO_DMLOE_MASK))
        {
            stcd->NBYTES = (stcd->NBYTES & ~DMA_NBYTES_MLOFFYES_NBYTES_MASK) |
                            DMA_NBYTES_MLOFFYES_NBYTES(nbytes);
        }
        else
        {
            stcd->NBYTES = (stcd->NBYTES & ~DMA_NBYTES_MLOFFNO_NBYTES_MASK) |
                             DMA_NBYTES_MLOFFNO_NBYTES(nbytes);
        }
    }
    else
    {
        stcd->NBYTES = (stcd->NBYTES & ~DMA_NBYTES_MLNO_NBYTES_MASK) |
                         DMA_NBYTES_MLNO_NBYTES(nbytes);
    }

}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_STCDSetMinorLoopOffset
 * Description   : Set minor loop offset for software TCD.
 *
 *END**************************************************************************/
void EDMA_HAL_STCDSetMinorLoopOffset(
                DMA_Type * base, edma_software_tcd_t *stcd, edma_minorloop_offset_config_t *config)
{
    assert(stcd);
    stcd->NBYTES = (stcd->NBYTES &
            ~(DMA_NBYTES_MLOFFYES_SMLOE_MASK | DMA_NBYTES_MLOFFYES_DMLOE_MASK)) |
            (((uint32_t)config->enableSrcMinorloop << DMA_NBYTES_MLOFFYES_SMLOE_SHIFT) |
            ((uint32_t)config->enableDestMinorloop << DMA_NBYTES_MLOFFYES_DMLOE_SHIFT));

    if ((config->enableSrcMinorloop == true) || (config->enableDestMinorloop == true))
    {
        DMA_BWR_CR_EMLM(base, true);
        stcd->NBYTES = (stcd->NBYTES & ~DMA_NBYTES_MLOFFYES_MLOFF_MASK) |
                                    DMA_NBYTES_MLOFFYES_MLOFF(config->offset);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_STCDSetScatterGatherLink
 * Description   : Set the next TCD pointer in scatter gather mode.
 *
 *END**************************************************************************/
void EDMA_HAL_STCDSetScatterGatherLink(
                edma_software_tcd_t *stcd, edma_software_tcd_t *nextStcd)
{
    assert(stcd);
    assert(nextStcd);
    EDMA_HAL_STCDSetScatterGatherCmd(stcd, true);
    stcd->DLAST_SGA = DMA_DLAST_SGA_DLASTSGA((uint32_t)nextStcd);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_STCDSetChannelMinorLink
 * Description   : Set minor link channel in software TCD.
 *
 *END**************************************************************************/
void EDMA_HAL_STCDSetChannelMinorLink(
                edma_software_tcd_t *stcd, uint32_t linkChannel, bool enable)
{
    assert(stcd);

    if (enable)
    {
        stcd->BITER = (stcd->BITER & ~DMA_BITER_ELINKYES_ELINK_MASK) |
                            ((uint32_t)enable << DMA_BITER_ELINKYES_ELINK_SHIFT);
        stcd->BITER = (stcd->BITER & ~DMA_BITER_ELINKYES_LINKCH_MASK) |
                            DMA_BITER_ELINKYES_LINKCH(linkChannel);
        stcd->CITER = (stcd->CITER & ~DMA_CITER_ELINKYES_ELINK_MASK) |
                            ((uint32_t)enable << DMA_CITER_ELINKYES_ELINK_SHIFT);
        stcd->CITER = (stcd->CITER & ~DMA_CITER_ELINKYES_LINKCH_MASK) |
                            DMA_CITER_ELINKYES_LINKCH(linkChannel);
    }
    else
    {
        stcd->BITER = (stcd->BITER & ~DMA_BITER_ELINKNO_ELINK_MASK) |
                            ((uint32_t)enable << DMA_BITER_ELINKNO_ELINK_SHIFT);
        stcd->CITER = (stcd->CITER & ~DMA_CITER_ELINKNO_ELINK_MASK) |
                            ((uint32_t)enable << DMA_CITER_ELINKNO_ELINK_SHIFT);
    }
}
/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_STCDSetMajorCount
 * Description   : Sets the major iteration count according to minor loop channel link setting.
 *
 *END**************************************************************************/
void EDMA_HAL_STCDSetMajorCount(edma_software_tcd_t *stcd, uint32_t count)
{
    assert(stcd);

    if (stcd->BITER & DMA_BITER_ELINKNO_ELINK_MASK)
    {
        stcd->BITER = (stcd->BITER & ~DMA_BITER_ELINKYES_BITER_MASK) |
                            DMA_BITER_ELINKYES_BITER(count);
        stcd->CITER = (stcd->CITER & ~DMA_CITER_ELINKYES_CITER_MASK) |
                            DMA_CITER_ELINKYES_CITER(count);
    }
    else
    {
        stcd->BITER = (stcd->BITER & ~DMA_BITER_ELINKNO_BITER_MASK) |
                            DMA_BITER_ELINKNO_BITER(count);
        stcd->CITER = (stcd->CITER & ~DMA_CITER_ELINKNO_CITER_MASK) |
                            DMA_CITER_ELINKNO_CITER(count);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_PushSTCDToHTCD
 * Description   : Copy the configuration data from the software TCD to hardware TCD.
 *
 *END**************************************************************************/
void EDMA_HAL_PushSTCDToHTCD(DMA_Type * base, uint32_t channel, edma_software_tcd_t *stcd)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    assert(stcd);

    DMA_WR_SADDR(base, channel, stcd->SADDR);
    DMA_WR_SOFF(base, channel, stcd->SOFF);
    DMA_WR_ATTR(base, channel, stcd->ATTR);
    DMA_WR_NBYTES_MLNO(base, channel, stcd->NBYTES);
    DMA_WR_SLAST(base, channel, stcd->SLAST);
    DMA_WR_DADDR(base, channel, stcd->DADDR);
    DMA_WR_DOFF(base, channel, stcd->DOFF);
    DMA_WR_CITER_ELINKYES(base, channel, stcd->CITER);
    DMA_WR_DLAST_SGA(base, channel, stcd->DLAST_SGA);
    DMA_WR_CSR(base, channel, stcd->CSR);
    DMA_WR_BITER_ELINKYES(base, channel, stcd->BITER);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_SetSTCDBasicTransfer
 * Description   : Set the basic transfer for software TCD.
 *
 *END**************************************************************************/
edma_status_t EDMA_HAL_STCDSetBasicTransfer(
            DMA_Type * base, edma_software_tcd_t *stcd, edma_transfer_config_t *config,
            bool enableInt, bool disableDmaRequest)
{
    assert(stcd);

    EDMA_HAL_STCDSetSrcAddr(stcd, config->srcAddr);
    EDMA_HAL_STCDSetDestAddr(stcd, config->destAddr);

    EDMA_HAL_STCDSetSrcOffset(stcd, config->srcOffset);
    EDMA_HAL_STCDSetDestOffset(stcd, config->destOffset);

    EDMA_HAL_STCDSetAttribute(stcd, config->srcModulo, config->destModulo,
            config->srcTransferSize, config->destTransferSize);

    EDMA_HAL_STCDSetSrcLastAdjust(stcd, config->srcLastAddrAdjust);
    EDMA_HAL_STCDSetDestLastAdjust(stcd, config->destLastAddrAdjust);
    EDMA_HAL_STCDSetNbytes(base, stcd, config->minorLoopCount);
    EDMA_HAL_STCDSetMajorCount(stcd, config->majorLoopCount);

    EDMA_HAL_STCDSetIntCmd(stcd, enableInt);
    EDMA_HAL_STCDSetDisableDmaRequestAfterTCDDoneCmd(stcd, disableDmaRequest);
    return kStatus_EDMA_Success;
}

#if (FSL_FEATURE_EDMA_ASYNCHRO_REQUEST_CHANNEL_COUNT > 0x0U)
/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_SetAsyncRequestInStopModeCmd
 * Description   : Enables/Disables an asynchronous request in stop mode.
 *
 *END**************************************************************************/
void EDMA_HAL_SetAsyncRequestInStopModeCmd(DMA_Type * base, uint32_t channel, bool enable)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);

    if(enable)
    {
        DMA_SET_EARS(base, 1U << channel);
    }
    else
    {
        DMA_CLR_EARS(base, 1U << channel);
    }
}
#endif
#endif
/*******************************************************************************
 * EOF
 ******************************************************************************/

