/** ============================================================================
 *   \file  hw_usbOtg.h
 *
 *   \brief This file contains the offset of USB OTG registers
 *
 *  ============================================================================
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


//*****************************************************************************
//
// hw_usbOtg.h - Macros for use in accessing the USB registers.
//
//*****************************************************************************
#ifndef __HW_USBOTG_H__
#define __HW_USBOTG_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// The following are defines for the Univeral Serial Bus OTG register offsets.
//
//*****************************************************************************

//
//USB subsystem base address
//
#define USBSS_BASE					0x47400000
//
//USB0 base address
//
#define USB_0_OTGBASE				0x47401000
//
//USB1 base address
//
#define USB_1_OTGBASE				0x47401800

//
//USB subsystem register offsets
//
#define USBSS_SYSCONFIG                 (0x10)
#define USBSS_IRQ_EOI				0x20
#define USBSS_IRQ_STATUS_RAW		0x24
#define USBSS_IRQ_STATUS			0x28
#define USBSS_IRQ_ENABLE_SET		0x2C
#define USBSS_IRQ_ENABLE_CLR		0x30

//
//USB0 offset register offsets
//
#define USB_0_REVISION				0x00
#define USB_0_CTRL	            	0x14
#define USB_0_STAT	            	0x18
#define USB_0_IRQ_MERGED_STATUS		0x20
#define USB_0_IRQ_EOI				0x24
#define USB_0_IRQ_STATUS_RAW_0 		0x28
#define USB_0_IRQ_STATUS_RAW_1 		0x2C
#define USB_0_IRQ_STATUS_0     		0x30
#define USB_0_IRQ_STATUS_1     		0x34
#define USB_0_IRQ_ENABLE_SET_0 		0x38
#define USB_0_IRQ_ENABLE_SET_1 		0x3C
#define USB_0_IRQ_ENABLE_CLR_0 		0x40
#define USB_0_IRQ_ENABLE_CLR_1 		0x44

#define USB_0_TX_MODE				0x70
#define USB_0_RX_MODE				0x74

#define USB_0_GEN_RNDIS_SIZE_EP1	0x80
#define USB_0_GEN_RNDIS_SIZE_EP2	0x84
#define USB_0_GEN_RNDIS_SIZE_EP3	0x88
#define USB_0_GEN_RNDIS_SIZE_EP4	0x8C
#define USB_0_GEN_RNDIS_SIZE_EP5	0x90
#define USB_0_GEN_RNDIS_SIZE_EP6	0x94
#define USB_0_GEN_RNDIS_SIZE_EP7	0x98
#define USB_0_GEN_RNDIS_SIZE_EP8	0x9C
#define USB_0_GEN_RNDIS_SIZE_EP9	0xA0
#define USB_0_GEN_RNDIS_SIZE_EP10	0xA4
#define USB_0_GEN_RNDIS_SIZE_EP11	0xA8
#define USB_0_GEN_RNDIS_SIZE_EP12	0xAC
#define USB_0_GEN_RNDIS_SIZE_EP13	0xB0
#define USB_0_GEN_RNDIS_SIZE_EP14	0xB4
#define USB_0_GEN_RNDIS_SIZE_EP15	0xB8

#define USB_1_GEN_RNDIS_SIZE_EP1	0x880
#define USB_1_GEN_RNDIS_SIZE_EP2	0x884
#define USB_1_GEN_RNDIS_SIZE_EP3	0x888
#define USB_1_GEN_RNDIS_SIZE_EP4	0x88C
#define USB_1_GEN_RNDIS_SIZE_EP5	0x890
#define USB_1_GEN_RNDIS_SIZE_EP6	0x894
#define USB_1_GEN_RNDIS_SIZE_EP7	0x898
#define USB_1_GEN_RNDIS_SIZE_EP8	0x89C
#define USB_1_GEN_RNDIS_SIZE_EP9	0x8A0
#define USB_1_GEN_RNDIS_SIZE_EP10	0x8A4
#define USB_1_GEN_RNDIS_SIZE_EP11	0x8A8
#define USB_1_GEN_RNDIS_SIZE_EP12	0x8AC
#define USB_1_GEN_RNDIS_SIZE_EP13	0x8B0
#define USB_1_GEN_RNDIS_SIZE_EP14	0x8B4
#define USB_1_GEN_RNDIS_SIZE_EP15	0x8B8

#define USB_0_AUTO_REQ				0xD0 						
#define USB_0_SRP_FIX_TIME          0xD4
#define USB_0_TEARDOWN              0xD8
#define USB_0_THRESHOLD_XDMA_IDLE   0xDC
#define USB_0_PHY_UTMI              0xE0
#define USB_0_MGC_UTMI_LOOPBACK     0xE4
#define USB_0_MODE                  0xE8

#ifdef __cplusplus
}
#endif

#endif // __HW_USBOTG_H__

