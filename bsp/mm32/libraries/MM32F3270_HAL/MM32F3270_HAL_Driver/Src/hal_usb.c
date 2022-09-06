/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hal_usb.h"


void USB_SetBufDespTableAddr(USB_Type * USBx, uint32_t addr)
{
    USBx->BDTPAGE01 = USB_BDTPAGE01_BDTBA(addr >> 9u);
    USBx->BDTPAGE02 = USB_BDTPAGE02_BDTBA(addr >> 16u);
    USBx->BDTPAGE03 = USB_BDTPAGE03_BDTBA(addr >> 24u);
}

void USB_InitDevice(USB_Type * USBx, USB_Device_Init_Type *init)
{
    if ( (uintptr_t)(init->BufDespTable_Addr) % 512u != 0u)
    {
        return;
    }
    USB_SetDeviceAddr(USBx, 0x00u);
    USB_SetBufDespTableAddr(USBx, init->BufDespTable_Addr);
    USB_Enable(USBx, true);
}

void USB_EnableInterrupts(USB_Type * USBx, uint32_t interrupts, bool enable)
{
    if(enable)
    {
        USBx->INTENB |=  interrupts;
    }
    else
    {
        USBx->INTENB &= ~interrupts;
    }
}

uint32_t USB_GetEnabledInterrupts(USB_Type * USBx)
{
    return USBx->INTENB;
}

uint32_t USB_GetInterruptStatus(USB_Type * USBx)
{
    uint32_t stat  = USBx->INTSTAT;
    uint32_t enb   = USBx->INTENB;
    return stat & enb;
}

void USB_ClearInterruptStatus(USB_Type * USBx, uint32_t interrupts)
{
    uint32_t enb  = USBx->INTENB;
    USBx->INTSTAT = interrupts & enb;
}

void USB_EnableErrInterrupts(USB_Type * USBx, uint32_t interrupts, bool enable)
{
    if(enable)
    {
        USBx->ERRENB |=  interrupts;
    }
    else
    {
        USBx->ERRENB &= ~interrupts;
    }
}


uint32_t USB_GetEnabledErrInterrupts(USB_Type * USBx)
{
    return USBx->ERRENB;
}

uint32_t USB_GetErrInterruptStatus(USB_Type * USBx)
{
    uint32_t stat = USBx->ERRSTAT;
    uint32_t enb  = USBx->ERRENB;
    USBx->ERRSTAT = stat & ~enb;
    return stat & enb;
}

void USB_ClearErrInterruptStatus(USB_Type * USBx, uint32_t interrupts)
{
    uint32_t enb  = USBx->ERRENB;
    USBx->ERRSTAT = interrupts & enb;
}

uint32_t USB_GetBufDespIndex(USB_Type * USBx)
{
    return (USBx->STAT)>>2;
}

void USB_Enable(USB_Type * USBx, bool enable)
{
    if(enable)
    {
        USBx->CTL |=  USB_CTL_USBEN_MASK;
    }
    else
    {
        USBx->CTL &= ~USB_CTL_USBEN_MASK;
    }
}

void USB_EnableOddEvenReset(USB_Type * USBx, bool enable)
{
    if(enable)
    {
        USBx->CTL |=  USB_CTL_ODDRST_MASK;
    }
    else
    {
        USBx->CTL &= ~USB_CTL_ODDRST_MASK;
    }
}

void USB_EnableResumeSignal(USB_Type * USBx, bool enable)
{
    if(enable)
    {
        USBx->CTL |=  USB_CTL_RESUME_MASK;
    }
    else
    {
        USBx->CTL &= ~USB_CTL_RESUME_MASK;
    }
}

void USB_EnableSuspend(USB_Type * USBx, bool enable)
{
    if(true == enable)
    {
        USBx->CTL |=  USB_CTL_TXDSUSPENDTOKENBUSY_MASK;
    }
    else
    {
        USBx->CTL &= ~USB_CTL_TXDSUSPENDTOKENBUSY_MASK;
    }

}


void USB_SetDeviceAddr(USB_Type * USBx, uint8_t addr)
{
    USBx->ADDR = ( (USBx->ADDR & ~USB_ADDR_ADDR_MASK)
                               | (addr & USB_ADDR_ADDR_MASK) )
                               ;
}

uint8_t USB_GetDeviceAddr(USB_Type * USBx)
{
    return USBx->ADDR & USB_ADDR_ADDR_MASK;
}

uint32_t USB_GetBufDespTableAddr(USB_Type * USBx)
{
    return (uint32_t)
        ( ( (USBx->BDTPAGE01 >> USB_BDTPAGE01_BDTBA_SHIFT) << 9u )
        | ( (USBx->BDTPAGE02 >> USB_BDTPAGE02_BDTBA_SHIFT) << 16u)
        | ( (USBx->BDTPAGE03 >> USB_BDTPAGE03_BDTBA_SHIFT) << 24u)
        );
}

uint32_t USB_GetFrameNumber(USB_Type * USBx)
{
    return (USBx->FRMNUML) | (USBx->FRMNUML << 7u);
}

USB_BufDesp_Type * USB_GetBufDesp(USB_Type * USBx)
{
    USB_BufDespTable_Type *bdt = (USB_BufDespTable_Type *)USB_GetBufDespTableAddr(USBx);
    return &bdt->Index[USBx->STAT >> 2];
}

USB_TokenPid_Type USB_BufDesp_GetTokenPid(USB_BufDesp_Type * bd)
{
    return (USB_TokenPid_Type)bd->TOK_PID;
}

uint32_t USB_BufDesp_GetPacketAddr(USB_BufDesp_Type * bd)
{
    return bd->ADDR;
}

uint32_t USB_BufDesp_GetPacketSize(USB_BufDesp_Type * bd)
{
    return bd->BC;
}

void USB_BufDesp_Reset(USB_BufDesp_Type * bd)
{
    bd->BDT_STALL = 0u;
    bd->NINC      = 0u;
    bd->KEEP      = 0u;
    bd->DTS       = 1u;
}

uint32_t USB_GetEndPointIndex(USB_Type * USBx)
{
    return (USBx->STAT & USB_STAT_ENDP_MASK) >> USB_STAT_ENDP_SHIFT;
}

USB_Direction_Type USB_GetXferDirection(USB_Type * USBx)
{
    return (USB_Direction_Type)( (USBx->STAT & USB_STAT_TX_MASK) >> USB_STAT_TX_SHIFT);
}

USB_BufDesp_OddEven_Type USB_GetBufDespOddEven(USB_Type * USBx)
{
    return (USB_BufDesp_OddEven_Type)( (USBx->STAT & USB_STAT_ODD_MASK) >> USB_STAT_ODD_SHIFT );
}

bool USB_BufDesp_Xfer(USB_BufDesp_Type * bd, uint32_t data_n, uint8_t * buffer, uint32_t len)
{
    if (1u == bd->OWN)
    {
        return false;
    }
    bd->ADDR = (uint32_t)buffer;
    bd->DATA = data_n;
    bd->BC   = len;
    bd->OWN  = 1u;
    return true;
}

bool USB_BufDesp_IsBusy(USB_BufDesp_Type * bd)
{
    if (1u == bd->OWN)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void USB_EnableEndPoint(USB_Type * USBx, uint32_t index, USB_EndPointMode_Type mode, bool enable)
{
    if (false == enable)
    {
        USBx->EPCTL[index] = 0u;
        USB_BufDespTable_Type * bdt = (USB_BufDespTable_Type * )USB_GetBufDespTableAddr(USBx);
        bdt->Table[index][0u][0u].HEAD = 0u;
        bdt->Table[index][0u][1u].HEAD = 0u;
        bdt->Table[index][1u][0u].HEAD = 0u;
        bdt->Table[index][1u][1u].HEAD = 0u;
        return;
    }
    if      (USB_EndPointMode_Control == mode)
    {
        USBx->EPCTL[index] |= USB_EPCTL_EPCTLDISEPRXENEPTXEN(3) | USB_EPCTL_EPHSHK_MASK;
    }
    else if (USB_EndPointMode_Bulk == mode)
    {
        USBx->EPCTL[index] |= USB_EPCTL_EPCTLDISEPRXENEPTXEN(7u) | USB_EPCTL_EPHSHK_MASK;
    }
    else if (USB_EndPointMode_Interrupt == mode)
    {
        USBx->EPCTL[index] |= USB_EPCTL_EPCTLDISEPRXENEPTXEN(7u) | USB_EPCTL_EPHSHK_MASK;
    }
    else if (USB_EndPointMode_Isochronous == mode)
    {
        USBx->EPCTL[index] |= USB_EPCTL_EPCTLDISEPRXENEPTXEN(7u);
    }
}

void USB_EnableEndPointStall(USB_Type * USBx, uint32_t index, bool enable)
{
    USB_BufDespTable_Type * bdt = (USB_BufDespTable_Type * )USB_GetBufDespTableAddr(USBx);
    for (uint32_t i = 0; i < USB_BDT_EP_NUM; i++)
    {
        if (true == enable)
        {
            USBx->EPCTL[i] |= USB_EPCTL_EPSTALL_MASK;
            bdt->Table[i][USB_BufDesp_OddEven_Odd ][USB_Direction_IN ].BDT_STALL = 1u;
            bdt->Table[i][USB_BufDesp_OddEven_Odd ][USB_Direction_OUT].BDT_STALL = 1u;
            bdt->Table[i][USB_BufDesp_OddEven_Even][USB_Direction_IN ].BDT_STALL = 1u;
            bdt->Table[i][USB_BufDesp_OddEven_Even][USB_Direction_OUT].BDT_STALL = 1u;
        }
        else
        {
            USBx->EPCTL[i] &= ~USB_EPCTL_EPSTALL_MASK;
            bdt->Table[i][USB_BufDesp_OddEven_Odd ][USB_Direction_IN ].BDT_STALL = 0u;
            bdt->Table[i][USB_BufDesp_OddEven_Odd ][USB_Direction_IN ].OWN       = 0u;
            bdt->Table[i][USB_BufDesp_OddEven_Odd ][USB_Direction_OUT].BDT_STALL = 0u;
            bdt->Table[i][USB_BufDesp_OddEven_Odd ][USB_Direction_OUT].OWN       = 0u;
            bdt->Table[i][USB_BufDesp_OddEven_Even][USB_Direction_IN ].BDT_STALL = 0u;
            bdt->Table[i][USB_BufDesp_OddEven_Even][USB_Direction_IN ].OWN       = 0u;
            bdt->Table[i][USB_BufDesp_OddEven_Even][USB_Direction_OUT].BDT_STALL = 0u;
            bdt->Table[i][USB_BufDesp_OddEven_Even][USB_Direction_OUT].OWN       = 0u;
        }
    }
}

uint32_t USB_GetEnabledEndPointStall(USB_Type * USBx)
{
    uint32_t status = 0u;
    for(uint32_t i = 0u; i < USB_BDT_EP_NUM; i++)
    {
        if (0 != (USBx->EPCTL[i] & USB_EPCTL_EPSTALL_MASK) )
        {
            status |= 1u << i;
        }
    }
    return status;
}

/* EOF. */

