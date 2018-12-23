/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
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
 * o Neither the name of the copyright holder nor the names of its
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

#ifndef __USB_EHCI_H__
#define __USB_EHCI_H__

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Device QH */
#define USB_DEVICE_EHCI_QH_POINTER_MASK (0xFFFFFFC0U)
#define USB_DEVICE_EHCI_QH_MULT_MASK (0xC0000000U)
#define USB_DEVICE_EHCI_QH_ZLT_MASK (0x20000000U)
#define USB_DEVICE_EHCI_QH_MAX_PACKET_SIZE_MASK (0x07FF0000U)
#define USB_DEVICE_EHCI_QH_MAX_PACKET_SIZE (0x00000800U)
#define USB_DEVICE_EHCI_QH_IOS_MASK (0x00008000U)

/* Device DTD */
#define USB_DEVICE_ECHI_DTD_POINTER_MASK (0xFFFFFFE0U)
#define USB_DEVICE_ECHI_DTD_TERMINATE_MASK (0x00000001U)
#define USB_DEVICE_ECHI_DTD_PAGE_MASK (0xFFFFF000U)
#define USB_DEVICE_ECHI_DTD_PAGE_OFFSET_MASK (0x00000FFFU)
#define USB_DEVICE_ECHI_DTD_PAGE_BLOCK (0x00001000U)
#define USB_DEVICE_ECHI_DTD_TOTAL_BYTES_MASK (0x7FFF0000U)
#define USB_DEVICE_ECHI_DTD_TOTAL_BYTES (0x00004000U)
#define USB_DEVICE_ECHI_DTD_IOC_MASK (0x00008000U)
#define USB_DEVICE_ECHI_DTD_MULTIO_MASK (0x00000C00U)
#define USB_DEVICE_ECHI_DTD_STATUS_MASK (0x000000FFU)
#define USB_DEVICE_EHCI_DTD_STATUS_ERROR_MASK (0x00000068U)
#define USB_DEVICE_ECHI_DTD_STATUS_ACTIVE (0x00000080U)
#define USB_DEVICE_ECHI_DTD_STATUS_HALTED (0x00000040U)
#define USB_DEVICE_ECHI_DTD_STATUS_DATA_BUFFER_ERROR (0x00000020U)
#define USB_DEVICE_ECHI_DTD_STATUS_TRANSACTION_ERROR (0x00000008U)

typedef struct _usb_device_ehci_qh_struct
{
    union
    {
        volatile uint32_t capabilttiesCharacteristics;
        struct
        {
            volatile uint32_t reserved1 : 15;
            volatile uint32_t ios : 1;
            volatile uint32_t maxPacketSize : 11;
            volatile uint32_t reserved2 : 2;
            volatile uint32_t zlt : 1;
            volatile uint32_t mult : 2;
        } capabilttiesCharacteristicsBitmap;
    } capabilttiesCharacteristicsUnion;
    volatile uint32_t currentDtdPointer;
    volatile uint32_t nextDtdPointer;
    union
    {
        volatile uint32_t dtdToken;
        struct
        {
            volatile uint32_t status : 8;
            volatile uint32_t reserved1 : 2;
            volatile uint32_t multiplierOverride : 2;
            volatile uint32_t reserved2 : 3;
            volatile uint32_t ioc : 1;
            volatile uint32_t totalBytes : 15;
            volatile uint32_t reserved3 : 1;
        } dtdTokenBitmap;
    } dtdTokenUnion;
    volatile uint32_t bufferPointerPage[5];
    volatile uint32_t reserved1;
    uint32_t setupBuffer[2];
    uint32_t setupBufferBack[2];
    union
    {
        uint32_t endpointStatus;
        struct
        {
            uint32_t isOpened : 1;
            uint32_t : 31;
        } endpointStatusBitmap;
    } endpointStatusUnion;
    uint32_t reserved2;
} usb_device_ehci_qh_struct_t;

typedef struct _usb_device_ehci_dtd_struct
{
    volatile uint32_t nextDtdPointer;
    union
    {
        volatile uint32_t dtdToken;
        struct
        {
            volatile uint32_t status : 8;
            volatile uint32_t reserved1 : 2;
            volatile uint32_t multiplierOverride : 2;
            volatile uint32_t reserved2 : 3;
            volatile uint32_t ioc : 1;
            volatile uint32_t totalBytes : 15;
            volatile uint32_t reserved3 : 1;
        } dtdTokenBitmap;
    } dtdTokenUnion;
    volatile uint32_t bufferPointerPage[5];
    union
    {
        volatile uint32_t reserved;
        struct
        {
            uint32_t originalBufferOffest : 12;
            uint32_t originalBufferLength : 19;
            uint32_t dtdInvalid : 1;
        } originalBufferInfo;
    } reservedUnion;
} usb_device_ehci_dtd_struct_t;

#endif /* __USB_EHCI_H__ */
