/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-05-25 16:42:56
 * @Description:  This files is for gmac irq
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_gmac_hw.h"
#include "ft_gmac.h"
#include "ft_status.h"
#include "ft_assert.h"
#include "ft_io.h"

#include "ft_debug.h"
#define GMAC_INTR_DEBUG_TAG "GMAC_INTR"

#define GMAC_INTR_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(GMAC_INTR_DEBUG_TAG, format, ##__VA_ARGS__)
#define GMAC_INTR_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(GMAC_INTR_DEBUG_TAG, format, ##__VA_ARGS__)
#define GMAC_INTR_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(GMAC_INTR_DEBUG_TAG, format, ##__VA_ARGS__)

s32 FGmac_SetHandler(Ft_Gmac_t *Gmac, FGmac_IsrCallbackSelect_t SelectIndex, void *FuncPtr,
                     void *Args)
{
    Ft_assertNonvoid(Gmac != NULL);
    Ft_assertNonvoid(FuncPtr != NULL);
    Ft_assertNonvoid(Gmac->IsReady == FT_COMPONENT_IS_READLY);

    switch (SelectIndex)
    {
    case FT_GMAC_TX_COMPLETE_CB_ID:
        /* code */
        Gmac->SendHandler = FuncPtr;
        Gmac->SendArgs = Args;
        break;
    case FT_GMAC_RX_COMPLETE_CB_ID:
        Gmac->RecvHandler = FuncPtr;
        Gmac->RecvArgs = Args;
        break;
    case FT_GMAC_DMA_ERROR_CB_ID:
        Gmac->ErrorHandler = FuncPtr;
        Gmac->ErrorArgs = Args;
        break;
    case FT_GMAC_MAC_PHY_STATUS_CB_ID:
        Gmac->StatusHandler = FuncPtr;
        Gmac->StatusArgs = Args;
        break;
    default:
        return FST_FAILURE;
    }

    return FST_SUCCESS;
}


__STATIC_INLINE u32 FGmac_ErrorCheck(Ft_Gmac_t *Gmac)
{
    u32 RegValue = 0;
    u32 ErrIsr_RegValue = 0;
    u32 RetValue = 0;
    RegValue = Ft_in32(Gmac->Config.BaseAddress + DMA_STATUS_OFFSET);
    ErrIsr_RegValue = Ft_in32(Gmac->Config.BaseAddress + DMA_INTR_ENA_OFFSET);

    if (((RegValue & DMA_STATUS_TPS) == DMA_STATUS_TPS) && ((ErrIsr_RegValue & DMA_INTR_ENA_TSE) == DMA_INTR_ENA_TSE))
    {
        RetValue |= GMAC_ERROR_TRANSMIT_PROCESS_STOPPED;
    }

    if (((RegValue & DMA_STATUS_TU) == DMA_STATUS_TU) && ((ErrIsr_RegValue & DMA_INTR_ENA_TUE) == DMA_INTR_ENA_TUE))
    {
        RetValue |= GMAC_ERROR_TRANSMIT_UNAVAILABLE_STATUS;
    }

    if (((RegValue & DMA_STATUS_TJT) == DMA_STATUS_TJT) && ((ErrIsr_RegValue & DMA_INTR_ENA_THE) == DMA_INTR_ENA_THE))
    {
        RetValue |= GMAC_ERROR_TRANSMIT_JABBER_TIMEOUT;
    }

    if (((RegValue & DMA_STATUS_OVF) == DMA_STATUS_OVF) && ((ErrIsr_RegValue & DMA_INTR_ENA_OVE) == DMA_INTR_ENA_OVE))
    {
        RetValue |= GMAC_ERROR_RECEIVE_FIFO_OVERFLOW;
    }

    if (((RegValue & DMA_STATUS_UNF) == DMA_STATUS_UNF) && ((ErrIsr_RegValue & DMA_INTR_ENA_UNE) == DMA_INTR_ENA_UNE))
    {
        RetValue |= GMAC_ERROR_TRANSMIT_UNDERFLOW;
    }

    if (((RegValue & DMA_STATUS_RU) == DMA_STATUS_RU) && ((ErrIsr_RegValue & DMA_INTR_ENA_RUE) == DMA_INTR_ENA_RUE))
    {
        RetValue |= GMAC_ERROR_RECEIVE_BUFFER_UNAVAILABLE;
    }

    if (((RegValue & DMA_STATUS_RPS) == DMA_STATUS_RPS) && ((ErrIsr_RegValue & DMA_INTR_ENA_RSE) == DMA_INTR_ENA_RSE))
    {
        RetValue |= GMAC_ERROR_RECEIVE_PROCESS_STOPPED;
    }

    if (((RegValue & DMA_STATUS_RWT) == DMA_STATUS_RWT) && ((ErrIsr_RegValue & DMA_INTR_ENA_RWE) == DMA_INTR_ENA_RWE))
    {
        RetValue |= GMAC_ERROR_RECEIVE_WATCHDOG_TIMEOUT;
    }

    if (((RegValue & DMA_STATUS_ETI) == DMA_STATUS_ETI) && ((ErrIsr_RegValue & DMA_INTR_ENA_ETE) == DMA_INTR_ENA_ETE))
    {
        RetValue |= GMAC_ERROR_EARLY_TRANSMIT_INTERRUPT;
    }

    if (((RegValue & DMA_STATUS_FBI) == DMA_STATUS_FBI) && ((ErrIsr_RegValue & DMA_INTR_ENA_FBE) == DMA_INTR_ENA_FBE))
    {
        RetValue |= GMAC_ERROR_FATAL_BUS_ERROR;
    }

    if (0U == RetValue)
    {
        RetValue |= GMAC_ERROR_UNDEFINED;
    }
    Ft_printf("error RetValue %x \r\n", RetValue);
    return RetValue;
}


void FGmac_IntrHandler(void *Args)
{
    Ft_Gmac_t *Gmac;
    u32 RegValue;
    u32 MACRegValue;
    Ft_assertVoid(Args != NULL);
    Gmac = (Ft_Gmac_t *)Args;

    RegValue = Ft_in32(Gmac->Config.BaseAddress + DMA_STATUS_OFFSET);
    if ((RegValue)&DMA_STATUS_GLI)
    {
        MACRegValue = Ft_in32(Gmac->Config.BaseAddress + GMAC_MAC_MAC_PHY_STATUS);
        if (Gmac->StatusHandler)
        {
            Gmac->StatusHandler(Gmac->StatusArgs, MACRegValue);
        }
    }

    /* Frame received */
    if ((RegValue & (DMA_STATUS_RI)) != 0)
    {
        if (Gmac->RecvHandler)
        {
            Gmac->RecvHandler(Gmac->RecvArgs);
        }

        Ft_out32(Gmac->Config.BaseAddress + DMA_STATUS_OFFSET, DMA_STATUS_RI);
    }
    else if ((RegValue & DMA_STATUS_TI) == DMA_STATUS_TI)
    {
        Ft_printf("DMA_STATUS_TI %x \r\n", RegValue);
        Ft_printf("ti debug %x \r\n", Ft_in32(Gmac->Config.BaseAddress + GMAC_INTERNAL_MODULE_STATUS_OFFSET));

        Ft_out32(Gmac->Config.BaseAddress + DMA_STATUS_OFFSET, DMA_STATUS_TI);
    }

    Ft_out32(Gmac->Config.BaseAddress + DMA_STATUS_OFFSET, DMA_STATUS_NIS);

    /*  DMA Error */
    if ((Ft_in32(Gmac->Config.BaseAddress + DMA_STATUS_OFFSET) & DMA_STATUS_AIS) == DMA_STATUS_AIS)
    {
        if (Gmac->ErrorHandler)
            Gmac->ErrorHandler(Gmac->ErrorArgs, FGmac_ErrorCheck(Gmac));
        Ft_out32(Gmac->Config.BaseAddress + DMA_STATUS_OFFSET, Ft_in32(Gmac->Config.BaseAddress + DMA_STATUS_OFFSET));
    }
}
