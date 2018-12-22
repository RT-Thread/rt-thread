/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
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

/*!
 * @file usbh_drv.c
 * @brief USB host driver.
 *
 */
#include "sdk.h"
#include "usb/usb.h"

extern void usbEnableVbus(usb_module_t * port);
extern void usbDisableVbus(usb_module_t * port);

/*!
 * Initialize the USB for host operation. This initialization sets
 * up the USB host to detect a device connection.
 *
 * Parameters:
 * @param port      USB module to initialize
 */

int usbh_init(usb_module_t * port)
{
    uint32_t core = (uint32_t)port->controllerID;
    /*!
     *  Start clocks and PLL
     */

    if (usbEnableClocks(port) == -1) {
        return -1;
    };

    /*!
     *  Enable and initialize transceiver interface for controller
     */

    if (usbEnableTransceiver(port) == -1) {
        return -1;
    }

    if (port->phyType == Ulpi) {
        HW_USBC_PORTSC1_WR(core, (HW_USBC_PORTSC1_RD(core) & (~(BF_USBC_UH1_PORTSC1_PTS_1(3) | BF_USBC_UH1_PORTSC1_PTS_2(1)))) | (BF_USBC_UH1_PORTSC1_PTS_1(2)));
    } else if (port->phyType == Utmi) {
        HW_USBC_PORTSC1_WR(core, HW_USBC_PORTSC1_RD(core) & (~(BF_USBC_UH1_PORTSC1_PTS_1(3) | BF_USBC_UH1_PORTSC1_PTS_2(1))));
    } else if (port->phyType == Serial) {
        HW_USBC_PORTSC1_WR(core, ((HW_USBC_PORTSC1_RD(core)) | (BF_USBC_UH1_PORTSC1_PTS_1(3))) & (~BF_USBC_UH1_PORTSC1_PTS_2(1)));
    } else {
        /* Invalid PHY type */
        return (-1);
    }

    //! Reset controller after switching PHY's
    HW_USBC_USBCMD_WR(core, HW_USBC_USBCMD_RD(core) | BM_USBC_UH1_USBCMD_RST);

    //! wait for reset to complete
    while (HW_USBC_USBCMD_RD(core) & BM_USBC_UH1_USBCMD_RST);

    //! set controller to host mode
    HW_USBC_USBMODE_WR(core, USB_USBMODE_CM_HOST);

    //! Set Asynchronous schedule park mode to 3
    //! to allow up to 3 successive transactions same queue.
    //! set interrupt interval to 0 for immediate interrupt
    HW_USBC_USBCMD_WR(core, BF_USBC_UH1_USBCMD_ASP(3) | BF_USBC_UH1_USBCMD_ITC(0));

#ifdef USB_USE_INT
    /* setup interrupt */
    usb_init_host_interrupts(port->moduleBaseAddress);
#endif

    //! start the controller
    //! the controller will start running but the schedules are not yet enabled.
    HW_USBC_USBCMD_WR(core, HW_USBC_USBCMD_RD(core) | BM_USBC_UH1_USBCMD_RS);

    //! Enable port power.
    //! Port power must be set for port to detect a device connection
    HW_USBC_PORTSC1_WR(core, HW_USBC_PORTSC1_RD(core) | BM_USBC_UH1_PORTSC1_PP);

    //! Enable Vbus power when Vbus power is controlled by GPIO
    //! On some board hardware, Vbus is not controlled by PortPower
    usbEnableVbus(port);

    return 0;
}

/*!
 * Initialize the periodic schedule. This function creates an empty
 * frame list for the periodic schedule, points the periodic base
 * address to the empty frame list, and enables the periodic schedule.
 *
 * @param port              USB module to initialize
 * @param frame_list_size   size of the frame list for the periodic schedule
 * @param frame_list        pointer to the start of the allocated frame list
 */
uint32_t usbh_periodic_schedule_init(struct usb_module * port, uint32_t frame_list_size,
                                     uint32_t * frame_list)
{
    uint32_t core = (uint32_t)port->controllerID;
    int i;
    uint32_t periodic_base;

    //! Initialize the USBCMD register for the desired frame list size

    //! Clear all FS bits before we start
    HW_USBC_USBCMD_WR(core, HW_USBC_USBCMD_RD(core) & (~(BM_USBC_UH1_USBCMD_FS_1 | BM_USBC_UH1_USBCMD_FS_2)));

    //! Set the new size
    switch (frame_list_size) {
    case 1024:
    	HW_USBC_USBCMD_WR(core, HW_USBC_USBCMD_RD(core) | USB_USBCMD_FS_1024);
        break;
    case 512:
    	HW_USBC_USBCMD_WR(core, HW_USBC_USBCMD_RD(core) | USB_USBCMD_FS_512);
        break;
    case 256:
    	HW_USBC_USBCMD_WR(core, HW_USBC_USBCMD_RD(core) | USB_USBCMD_FS_256);
        break;
    case 128:
    	HW_USBC_USBCMD_WR(core, HW_USBC_USBCMD_RD(core) | USB_USBCMD_FS_128);
        break;
    case 64:
    	HW_USBC_USBCMD_WR(core, HW_USBC_USBCMD_RD(core) | USB_USBCMD_FS_64);
        break;
    case 32:
    	HW_USBC_USBCMD_WR(core, HW_USBC_USBCMD_RD(core) | USB_USBCMD_FS_32);
        break;
    case 16:
    	HW_USBC_USBCMD_WR(core, HW_USBC_USBCMD_RD(core) | USB_USBCMD_FS_16);
        break;
    case 8:
    	HW_USBC_USBCMD_WR(core, HW_USBC_USBCMD_RD(core) | USB_USBCMD_FS_8);
        break;
    default:
        // Invalid frame list size
        return (-1);
        break;
    }

    /*!
     * The USB specification requires the frame list to be aligned on an 8Kbyte boundary.
     */

    //! Check if allocated frame list memory is aligned
    if ((int)frame_list % (1024 * 4) != 0) {
        printf("Frame list not aligned on 4K boundary");
        return (-1);
    }

    /*!
     * Fill the frame list with link pointers marked invalid
     * since we don't have any traffic to send yet.
     */
    periodic_base = (uint32_t) frame_list;

    for (i = 0; i < (frame_list_size); i++)
        *(frame_list++) = 1;

    //! Initialize the Periodic base address register
    HW_USBC_PERIODICLISTBASE_WR(core, periodic_base);

    //! Enable the periodic schedule
    HW_USBC_USBCMD_WR(core, HW_USBC_USBCMD_RD(core) | BM_USBC_UH1_USBCMD_PSE);

    //! Wait for periodic schedule to become enabled
    while(!(HW_USBC_USBSTS_RD(core) & BM_USBC_UH1_USBSTS_PS));

#ifdef DEBUG_PRINT
    printf("Periodic schedule is enabled.\n");
#endif

    return periodic_base;
}

/*!
 * Issue a USB reset to the specified port.
 *
 * @param port      USB module to send reset
 */
void usbh_bus_reset(struct usb_module *port)
{
    uint32_t core = (uint32_t)port->controllerID;

    //! Set Port Reset
    HW_USBC_PORTSC1_WR(core, HW_USBC_PORTSC1_RD(core) | BM_USBC_UH1_PORTSC1_PR);

    //! Wait for reset to finish
    while(HW_USBC_PORTSC1_RD(core) & BM_USBC_UH1_PORTSC1_PR);
}

/*!
 * Enable the asynchronous schedule\n
 * This function enables the Asynchronous schedule.\n
 * The application code must create descriptors and queue heads and\n
 * set the Asynchronous list address before calling this function.
 */
void usbh_enable_asynchronous_schedule(usb_module_t * port)
{
    uint32_t core = (uint32_t)port->controllerID;

    // Enable the Asynchronous schedule
    HW_USBC_USBCMD_WR(core, HW_USBC_USBCMD_RD(core) | BM_USBC_UH1_USBCMD_ASE);

    // Wait for asynchronous schedule to enable
    while(!(HW_USBC_USBSTS_RD(core) & BM_USBC_UH1_USBSTS_AS));
}

/*!
 * Disable the asynchronous schedule.
 *
 * @param port  USB module
 */
void usbh_disable_asynchronous_schedule(struct usb_module *port)
{
    uint32_t core = (uint32_t)port->controllerID;

    //! Disable the asynchronous schedule
    HW_USBC_USBCMD_WR(core, HW_USBC_USBCMD_RD(core) & (~BM_USBC_UH1_USBCMD_ASE));

    //! Wait for asynchronous enable bit to clear
    while(HW_USBC_USBCMD_RD(core) & BM_USBC_UH1_USBCMD_ASE);
}

/*!
* Disable the periodic lists.
*
* @param port  USB module
*/
void usbh_disable_Periodic_list(struct usb_module *port)
{
    uint32_t core = (uint32_t)port->controllerID;

    //! Disable the periodic schedule
    HW_USBC_USBCMD_WR(core, HW_USBC_USBCMD_RD(core) &(~BM_USBC_UH1_USBCMD_PSE));

    //! Wait for periodic schedule enable bit to clear
    while(HW_USBC_USBCMD_RD(core) & BM_USBC_UH1_USBCMD_PSE);
}

/*!
 * Initialize the qTD.
 * This function initializes a transfer descriptor.
 * the next qTD and alternate next qTD pointers are initialized with the terminate bit set.
 *
 * @param transferSize   number of bytes to be transferred
 * @param ioc            interrupt on complete flag
 * @param pid            PID code for the transfer
 * @param bufferPointer  pointer to the data buffer
 */
usbhTransferDescriptor_t *usbh_qtd_init(uint32_t transferSize, uint32_t ioc, uint32_t pid,
                                        uint32_t * bufferPointer)
{
    uint32_t token;
    uint32_t bufferOffset;      // offset in first 4K buffer
    int remainingSize;          // remaining number of byte to allocate

    usbhTransferDescriptor_t *usbhQtd;

    uint32_t memoryPointer;
    int i;

    /*!
     * Allocate memory for the transfer descriptor
     */
    memoryPointer = (uint32_t)malloc(sizeof(usbhTransferDescriptor_t) + 63); // over-allocate to accommodate 64-byte alignment
    if (memoryPointer == 0) {
        return NULL;            // No memory available
    }

    /*!
     * Allign qTD on a 64 byte boundary.
     */
    if ((memoryPointer % 64) != 0) {
        usbhQtd = (usbhTransferDescriptor_t *) ((memoryPointer / 64 + 1) * 64); // first 64-byte boundary within allocated memory
    } else
        usbhQtd = (usbhTransferDescriptor_t *) memoryPointer;

    usbhQtd->mallocPointer = memoryPointer; // keep track of allocated memory

    //! Set terminate bit on all pointers
    usbhQtd->nextQtd = 0xDEAD0001;
    usbhQtd->alternateNextQtd = 0x1;

    //! Set the PID for the for the transaction
    switch (pid) {
    case SETUP_PID:
        token = USB_QTD_TOKEN_PID_SETUP;
        break;
    case OUT_PID:
        token = (USB_QTD_TOKEN_DT | USB_QTD_TOKEN_PID_OUT);
        break;
    case IN_PID:
        token = (USB_QTD_TOKEN_DT | USB_QTD_TOKEN_PID_IN);
        break;
    default:
#ifdef DEBUG_PRINT
        printf("ERR!! Invalid PID\n");
#endif
        return NULL;
        break;
    }

    if (ioc)
        token |= USB_QTD_TOKEN_IOC; // Set interrupt on completion.
    // Note: Short packets will always interrupt!

    usbhQtd->qtdToken = (token | USB_QTD_TOKEN_TRANS_SIZE(transferSize)
                         | USB_QTD_TOKEN_CERR(0x3)
                         | USB_QTD_TOKEN_STAT_ACTIVE);

    //! Allocate first buffer.
    //! First qtd buffer holds data up to first 4K address boundary)
    usbhQtd->qtdBuffer[0] = (uint32_t) bufferPointer;
    bufferOffset = (uint32_t) bufferPointer % 4096;
    remainingSize = (int)(transferSize - (4096 - bufferOffset));

    //! Assign remaining buffers.
    //! All remaining buffers start at a 4K boundary

    for (i = 1; i < 5; i++) {
        if (remainingSize > 0)  // allocate next 4K
        {
            usbhQtd->qtdBuffer[i] = (uint32_t) bufferPointer + ((4096 * i) - bufferOffset);
            remainingSize -= 4096;
        } else
            usbhQtd->qtdBuffer[i] = 0;
    }
    if (remainingSize > 0) {
        free((void *)(usbhQtd->mallocPointer));
        usbhQtd = NULL;         // Error. transfer size exceeds maximum available size.
    }
    return usbhQtd;
}

/*!
 * Initialize the QH.
 * This function assumes the QH is the only one in the horizontal list so
 * the horizontal link pointer points to the queue head. This function
 * doesn't initialize the qTD pointer either. This must be done later. 
 *
 * Parameters:
 * @param max_packet maximum packet length for the endpoint
 * @param head       used to mark the QH as the first in the linked list (not used for interrupt QHs)
 * @param eps        end point speed
 * @param epnum      end point number
 * @param dev_addr   device address
 * @param smask      interrupt schedule mask (only used for periodic schedule QHs)
 */

usbhQueueHead_t *usbh_qh_init(uint32_t max_packet, uint32_t head, uint32_t eps, uint32_t epnum,
                              uint32_t dev_addr, uint32_t smask)
{
    uint32_t token;
    uint32_t memoryPointer;
    usbhQueueHead_t *queueHead;
    int i;

    /*!
     * Allocate memory for the queue head.
     * - Over-allocate to accommodate 64-byte alignment
     */
    memoryPointer = (uint32_t) malloc(sizeof(usbhQueueHead_t) + 63);
    if (memoryPointer == 0) {
        return NULL;            // No memory available
    }

    /*!
     * - Align QH on a 64 byte boundary.
     */
    if ((memoryPointer % 64) != 0) {
        queueHead = (usbhQueueHead_t *) ((memoryPointer / 64 + 1) * 64);    // first 64-byte boundary within allocated memory
    } else
        queueHead = (usbhQueueHead_t *) memoryPointer;

    queueHead->mallocPointer = memoryPointer;

    //! - Loop the queue head pointer back to itself and set type
    queueHead->queueHeadLinkPointer = (((uint32_t) queueHead)
                                       | USB_QH_LINK_PTR_TYP_QH);

    //! - Set endpoint speed
    switch (eps) {
    case EPS_FULL:
        token = USB_QH_EP_CHAR_EPS_FULL;
        break;
    case EPS_LOW:
        token = USB_QH_EP_CHAR_EPS_LOW;
        break;
    case EPS_HIGH:
        token = USB_QH_EP_CHAR_EPS_HIGH;
        break;
    default:
#ifdef DEBUG_PRINT
        printf("ERR!! Invalid EPS\n");
#endif
        return NULL;
    }

    //! Set endpoint characteristics
    if (head)
        token |= USB_QH_EP_CHAR_H;

    queueHead->endpointCharacteristics = (token | USB_QH_EP_CHAR_MAX_PACKET(max_packet)
                                          | USB_QH_EP_CHAR_DTC | USB_QH_EP_CHAR_EP(epnum)
                                          | USB_QH_EP_CHAR_DEV_ADDR(dev_addr));

    /* - set interrupt to occur every 8ms */
    queueHead->endpointCapabilities = (USB_QH_EP_CAP_MULT_ONE | USB_QH_EP_CAP_UFRAME_SMASK(smask));

    queueHead->currentQtd = 0;
    queueHead->nextQtd = 1;     //! - set terminate bit on Next qtd pointer
    queueHead->alternateNextQtd = 1;    //! - set terminate bit on alternate next qtd pointer
    queueHead->qtdToken = 0;

    for (i = 0; i < 5; i++)     //! - Clear buffer pointers (for debug purposes)
    {
        queueHead->qtdBuffer[i] = 0;
    }
    return queueHead;
}
