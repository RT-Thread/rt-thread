/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-05-25 16:42:13
 * @Description:  This files is for gmac description
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_gmac_desc.h"
#include "ft_gmac_hw.h"
#include "ft_parameters.h"

#include "ft_io.h"
#include "ft_status.h"
#include "ft_assert.h"
#include "ft_cache.h"
#include "ft_debug.h"
#include <string.h>

#define GMAC_DESC_DEBUG_TAG "GMAC_DESC"

#define GMAC_DESC_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(GMAC_DESC_DEBUG_TAG, format, ##__VA_ARGS__)
#define GMAC_DESC_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(GMAC_DESC_DEBUG_TAG, format, ##__VA_ARGS__)
#define GMAC_DESC_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(GMAC_DESC_DEBUG_TAG, format, ##__VA_ARGS__)

void FGmac_ResumeTransmission(Ft_Gmac_t *Gmac)
{
    /* When Tx Buffer unavailable flag is set: clear it and resume transmission */
    if ((Ft_in32(Gmac->Config.BaseAddress + DMA_STATUS_OFFSET) & DMA_STATUS_TU) == DMA_STATUS_TU)
    {
        /* Clear TBUS GMAC DMA flag */
        Ft_out32(Gmac->Config.BaseAddress + DMA_STATUS_OFFSET, DMA_STATUS_TU);

        /* Resume DMA transmission*/
        Ft_out32(Gmac->Config.BaseAddress + DMA_XMT_POLL_DEMAND_OFFSET, 0xff);
    }
}

void FGmac_SetTransmitUnderflow(Ft_Gmac_t *Gmac)
{
    /* When Tx Buffer unavailable flag is set: clear it and resume transmission */
    if ((Ft_in32(Gmac->Config.BaseAddress + DMA_STATUS_OFFSET) & DMA_STATUS_UNF) == DMA_STATUS_UNF)
    {
        /* Clear TBUS GMAC DMA flag */
        Ft_out32(Gmac->Config.BaseAddress + DMA_STATUS_OFFSET, DMA_STATUS_UNF);

        /* Resume DMA transmission*/
        Ft_out32(Gmac->Config.BaseAddress + DMA_XMT_POLL_DEMAND_OFFSET, 0xff);
    }
}

s32 FGmac_DMATxDescChainInit(Ft_Gmac_t *Gmac, FGmac_DmaDesc_t *DMATxDescTab, u8 *TxBuff, u32 TxBuffCount)
{
    u32 i;
    FGmac_DmaDesc_t *TxDesc;
    Ft_assertNonvoid(Gmac != NULL);
    Ft_assertNonvoid(Gmac->IsReady == FT_COMPONENT_IS_READLY);

    /* Make Each DmaTx  descriptor with initialized value*/
    for (i = 0; i < TxBuffCount; i++)
    {
        TxDesc = DMATxDescTab + i;
        TxDesc->Control = DMA_TDES1_SECOND_ADDRESS_CHAINED;
        TxDesc->Buffer1Addr = (u32)(&TxBuff[i * GMAC_MAX_PACKET_SIZE]);

        /* Initialize the next descriptor with the Next Descriptor Polling Enable */
        if (i < (TxBuffCount - 1))
        {
            /* Set next descriptor address register with next descriptor base address */
            TxDesc->Buffer2NextDescAddr = (u32)(DMATxDescTab + i + 1);
            Ft_printf(" Buffer2NextDescAddr %x \r\n", TxDesc->Buffer2NextDescAddr);
        }
        else
        {
            /* For last descriptor, set next descriptor address register equal to the first descriptor base address */
            TxDesc->Buffer2NextDescAddr = (u32)DMATxDescTab;
            Ft_printf(" Buffer2NextDescAddr %x \r\n", TxDesc->Buffer2NextDescAddr);
        }
    }
    Ft_printf("DMATxDescTab addr is %x", DMATxDescTab);

    return FST_SUCCESS;
}

s32 FGmac_DmaTxDescRingInit(Ft_Gmac_t *Gmac, FGmac_DmaDesc_t *DMATxDescTab, u8 *TxBuff, u32 DescBufPerLength, u32 TxBuffCount)
{
    u32 i;
    FGmac_DmaDesc_t *TxDesc;
    Ft_assertNonvoid(Gmac != NULL);
    Ft_assertNonvoid(Gmac->IsReady == FT_COMPONENT_IS_READLY);

    memset(&Gmac->TxDescRingData, 0, sizeof(Gmac->TxDescRingData));
    Gmac->TxDescRingData.DescMaxNumber = TxBuffCount;
    memset(DMATxDescTab, 0, sizeof(FGmac_DmaDesc_t) * TxBuffCount);
    DMATxDescTab[TxBuffCount - 1].Control |= DMA_TDES1_END_RING;
    for (i = 0; i < TxBuffCount; i++)
    {
        TxDesc = DMATxDescTab + i;
        FCache_cpuDcacheInvalidate(&TxBuff[i * DescBufPerLength], DescBufPerLength);
        TxDesc->Buffer1Addr = (u32)(&TxBuff[i * DescBufPerLength]);
    }
    Ft_out32(Gmac->Config.BaseAddress + DMA_TX_BASE_ADDR_OFFSET, (u32)DMATxDescTab);
    return FST_SUCCESS;
}

s32 FGmac_TransmitframeRingPoll(Ft_Gmac_t *Gmac, uint32_t FrameLength)
{
    u32 Size = 0U;
    u32 i = 0U;
    u32 BufCount = 0U;
    FGmac_DmaDesc_t *TxDesc;

    if (0U == FrameLength)
    {
        return FST_SUCCESS;
    }

    if (FrameLength > GMAC_MAX_PACKET_SIZE)
    {
        BufCount = FrameLength / GMAC_MAX_PACKET_SIZE;
        if (FrameLength % GMAC_MAX_PACKET_SIZE)
        {
            BufCount++;
        }
    }
    else
    {
        BufCount = 1U;
    }

    if (BufCount == 1U)
    {

        TxDesc = &Gmac->TxDesc[Gmac->TxDescRingData.DescIndex];
        /* Set LAST and FIRST segment */
        TxDesc->Control |= (DMA_TDES1_FIRST_SEGMENT | DMA_TDES1_LAST_SEGMENT);

        /* Set frame size */
        TxDesc->Control &= ~(DMA_TDES1_BUFFER1_SIZE_MASK);
        TxDesc->Control |= (FrameLength & DMA_TDES1_BUFFER1_SIZE_MASK);
        /* Set Own bit of the Tx descriptor Status: gives the buffer back to ETHERNET DMA */
        TxDesc->Status |= (DMA_TDES0_OWN);
        GMAC_INC_DESC(Gmac->TxDescRingData.DescIndex, Gmac->TxDescRingData.DescMaxNumber);
    }
    else
    {
        for (i = 0U; i < BufCount; i++)
        {
            TxDesc = &Gmac->TxDesc[Gmac->TxDescRingData.DescIndex];
            /* Clear FIRST and LAST segment bits */
            TxDesc->Control &= ~(DMA_TDES1_FIRST_SEGMENT | DMA_TDES1_LAST_SEGMENT);

            if (i == 0U)
            {
                /* Setting the first segment bit */
                TxDesc->Control |= DMA_TDES1_FIRST_SEGMENT;
            }

            /* Program size */
            TxDesc->Control &= ~(DMA_TDES1_BUFFER1_SIZE_MASK);
            TxDesc->Control |= (GMAC_MAX_PACKET_SIZE & DMA_TDES1_BUFFER1_SIZE_MASK);

            if (i == (BufCount - 1U))
            {
                /* Setting the last segment bit */
                TxDesc->Control |= (DMA_TDES1_LAST_SEGMENT);
                Size = FrameLength - (BufCount - 1U) * GMAC_MAX_PACKET_SIZE;
                TxDesc->Control &= ~(DMA_TDES1_BUFFER1_SIZE_MASK);
                TxDesc->Control |= (Size & DMA_TDES1_BUFFER1_SIZE_MASK);
            }

            /* Set Own bit of the Tx descriptor Status: gives the buffer back to ETHERNET DMA */
            TxDesc->Status |= (DMA_TDES0_OWN);

            GMAC_INC_DESC(Gmac->TxDescRingData.DescIndex, Gmac->TxDescRingData.DescMaxNumber);
        }
    }

    FGmac_ResumeTransmission(Gmac);

    return FST_SUCCESS;
}

s32 FGmac_DMARxDescChainInit(Ft_Gmac_t *Gmac, FGmac_DmaDesc_t *DMARxDescTab, u8 *RxBuff, u32 RxBuffCount)
{
    u32 i;
    FGmac_DmaDesc_t *RxDesc;
    Ft_assertNonvoid(Gmac != NULL);
    Ft_assertNonvoid(Gmac->IsReady == FT_COMPONENT_IS_READLY);

    for (i = 0; i < RxBuffCount; i++)
    {
        RxDesc = DMARxDescTab + i;
        /* Set Own bit of the Rx descriptor Status */
        RxDesc->Status = DMA_RDES0_OWN;

        /* Set Buffer1 size and Second Address Chained bit */
        RxDesc->Control = DMA_RDES1_BUFFER1_SIZE_MASK & (u32)(GMAC_MAX_PACKET_SIZE);
        RxDesc->Control |= DMA_RDES1_SECOND_ADDRESS_CHAINED;
        /* Set Buffer1 address pointer */
        RxDesc->Buffer1Addr = (u32)(&RxBuff[i * GMAC_MAX_PACKET_SIZE]);

        /* Initialize the next descriptor with the Next Descriptor Polling Enable */
        if (i < (RxBuffCount - 1))
        {
            /* Set next descriptor address register with next descriptor base address */
            RxDesc->Buffer2NextDescAddr = (u32)(DMARxDescTab + i + 1);
        }
        else
        {
            /* For last descriptor, set next descriptor address register equal to the first descriptor base address */
            RxDesc->Buffer2NextDescAddr = (u32)(DMARxDescTab);
        }

        // Ft_printf("rx Buffer2NextDescAddr %x \r\n", RxDesc->Buffer2NextDescAddr);
    }
    Ft_out32(Gmac->Config.BaseAddress + DMA_RCV_BASE_ADDR_OFFSET, (u32)DMARxDescTab);
    return FST_SUCCESS;
}

s32 FGmac_DmaRxDescRingInit(Ft_Gmac_t *Gmac, FGmac_DmaDesc_t *DMARxDescTab, u8 *RxBuff, u32 DescBufPerLength, u32 RxBuffCount)
{
    u32 i;
    FGmac_DmaDesc_t *RxDesc;
    Ft_assertNonvoid(Gmac != NULL);
    Ft_assertNonvoid(Gmac->IsReady == FT_COMPONENT_IS_READLY);

    memset(&Gmac->RxDescRingData, 0, sizeof(Gmac->RxDescRingData));
    Gmac->RxDescRingData.DescMaxNumber = RxBuffCount;
    memset(DMARxDescTab, 0, sizeof(FGmac_DmaDesc_t) * RxBuffCount);

    for (i = 0; i < RxBuffCount; i++)
    {
        RxDesc = DMARxDescTab + i;
        /* Set Own bit of the Rx descriptor Status */
        RxDesc->Status = DMA_RDES0_OWN;
        /* Set Buffer1 size and Second Address Chained bit */
        RxDesc->Control = DMA_RDES1_BUFFER1_SIZE_MASK & (u32)(DescBufPerLength);
        /* Set Buffer1 address pointer */
        FCache_cpuDcacheInvalidate(&RxBuff[i * DescBufPerLength], DescBufPerLength);
        RxDesc->Buffer1Addr = (u32)(&RxBuff[i * DescBufPerLength]);

        if (i == (RxBuffCount - 1))
        {
            RxDesc->Control |= DMA_RDES1_END_RING;
        }
    }

    Ft_out32(Gmac->Config.BaseAddress + DMA_RCV_BASE_ADDR_OFFSET, (u32)DMARxDescTab);

    return FST_SUCCESS;
}

void FGmac_ResumeTransmissionReception(Ft_Gmac_t *Gmac)
{
    /* When Rx Buffer unavailable flag is set: clear it and resume transmission */
    if ((Ft_in32(Gmac->Config.BaseAddress + DMA_STATUS_OFFSET) & DMA_STATUS_RU) == DMA_STATUS_RU)
    {
        /* Clear RBUS GMAC DMA flag */
        Ft_out32(Gmac->Config.BaseAddress + DMA_STATUS_OFFSET, DMA_STATUS_RU);

        /* Resume DMA transmission*/
        Ft_out32(Gmac->Config.BaseAddress + DMA_RCV_POLL_DEMAND_OFFSET, 0xff);
    }
}

s32 FGmac_RingGetReceivedFrame_IT(Ft_Gmac_t *Gmac)
{
    u32 DescriptorsCounter = 0U;
    FGmac_DmaDesc_t *RxDesc;
    RxDesc = &Gmac->RxDesc[Gmac->RxDescRingData.DescIndex];

    while (((RxDesc->Status & DMA_RDES0_OWN) == 0) && DescriptorsCounter < Gmac->RxDescRingData.DescMaxNumber)
    {
        DescriptorsCounter++;

        /* Check if first segment in frame */
        if ((RxDesc->Status & (DMA_RDES0_FIRST_DESCRIPTOR | DMA_RDES0_LAST_DESCRIPTOR)) == (u32)DMA_RDES0_FIRST_DESCRIPTOR)
        {
            // GMAC_DESC_DEBUG_I("find first frame");
            Gmac->RxDescRingData.DescBufIndex = Gmac->RxDescRingData.DescIndex;
            /* Point to next descriptor */
            GMAC_INC_DESC(Gmac->RxDescRingData.DescIndex, Gmac->RxDescRingData.DescMaxNumber);
            RxDesc = &Gmac->RxDesc[Gmac->RxDescRingData.DescIndex];
        } /* Check if intermediate segment */
        else if ((RxDesc->Status & (DMA_RDES0_FIRST_DESCRIPTOR | DMA_RDES0_LAST_DESCRIPTOR)) == 0)
        {
            // GMAC_DESC_DEBUG_I("find invaild frame");
            /* Point to next descriptor */
            GMAC_INC_DESC(Gmac->RxDescRingData.DescIndex, Gmac->RxDescRingData.DescMaxNumber);
            RxDesc = &Gmac->RxDesc[Gmac->RxDescRingData.DescIndex];
        } /* Should be last segment */
        else
        {
            Gmac->RxDescRingData.DescBufIndex = Gmac->RxDescRingData.DescIndex;
            GMAC_INC_DESC(Gmac->RxDescRingData.DescIndex, Gmac->RxDescRingData.DescMaxNumber);
            return FST_SUCCESS;
        }
    }
    return FST_FAILURE;
}

s32 FGmac_GetReceivedFrame(Ft_Gmac_t *Gmac)
{
    u32 FrameLength = 0U;
    /* Check if segment is not owned by DMA */
    if ((Gmac->RxDesc->Status & DMA_RDES0_OWN) == 0)
    {
        if ((Gmac->RxDesc->Status & DMA_RDES0_LAST_DESCRIPTOR) != 0)
        {
            /* increment segment count */
            Gmac->DMARxFrameInfos.SegCount++;

            /*  Check if last segment is first segment: one segment contains the frame   */
            if (1U == Gmac->DMARxFrameInfos.SegCount)
            {
                (Gmac->DMARxFrameInfos).FSRxDesc = Gmac->RxDesc;
            }

            Gmac->DMARxFrameInfos.LSRxDesc = Gmac->RxDesc;

            /* Get the Frame Length of the received packet: substruct 4 bytes of the CRC */
            FrameLength = (((Gmac->RxDesc)->Status & DMA_RDES0_FRAME_LEN_MASK) >> 16U) - 4U;
            Gmac->DMARxFrameInfos.length = FrameLength;

            /* Get the address of the buffer start address */
            Gmac->DMARxFrameInfos.buffer = ((Gmac->DMARxFrameInfos).FSRxDesc)->Buffer1Addr;
            /* point to next descriptor */
            Gmac->RxDesc = (FGmac_DmaDesc_t *)((Gmac->RxDesc)->Buffer2NextDescAddr);

            return FST_SUCCESS;
        }
        /* Check if first segment */
        else if ((Gmac->RxDesc->Status & DMA_RDES0_FIRST_DESCRIPTOR) == (u32)DMA_RDES0_FIRST_DESCRIPTOR)
        {
            (Gmac->DMARxFrameInfos).FSRxDesc = Gmac->RxDesc;
            (Gmac->DMARxFrameInfos).LSRxDesc = NULL;
            (Gmac->DMARxFrameInfos).SegCount = 1U;
            /* Point to next descriptor */
            Gmac->RxDesc = (FGmac_DmaDesc_t *)(Gmac->RxDesc->Buffer2NextDescAddr);
        } /* Check if intermediate segment */
        else
        {
            (Gmac->DMARxFrameInfos).SegCount++;
            /* Point to next descriptor */
            Gmac->RxDesc = (FGmac_DmaDesc_t *)(Gmac->RxDesc->Buffer2NextDescAddr);
        }
    }

    return FST_FAILURE;
}
