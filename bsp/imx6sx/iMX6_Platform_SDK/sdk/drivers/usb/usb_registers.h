/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
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
#ifndef __USB_CORE_REGISTERS__
#define __USB_CORE_REGISTERS__

#include "sdk.h"
#include "registers/regsusbcore.h"
#include "registers/regsusbnoncore.h"

/*!
 * @file usb_registers.h
 * @brief USB controller registers and bit definitions.
 *
 */


/*
 * Register access macros
 */
#if defined(CHIP_MX6DQ) || defined(CHIP_MX6SDL)
#define USB_OTG		0
#define USB_UH1		1
#define USB_UH2		2
#define USB_UH3		3
#define USB_CORE_BM(n, reg, fld)		((n) == USB_OTG ? BM_USBC_UOG_##reg##_##fld : \
 						(n) == USB_UH1 ? BM_USBC_UH1_##reg##_##fld: \
 						(n) == USB_UH2 ? BM_USBC_UH2_##reg##_##fld: \
 						BM_USBC_UH3_##reg##_##fld)
#define USB_CORE_BP(n, reg, fld)		((n) == USB_OTG ? BP_USBC_UOG_##reg##_##fld : \
 						(n) == USB_UH1 ? BP_USBC_UH1_##reg##_##fld: \
 						(n) == USB_UH2 ? BP_USBC_UH2_##reg##_##fld: \
 						BP_USBC_UH3_##reg##_##fld)
#define USB_CORE_REGISTER_RD(n, reg)		((n) == USB_OTG ? HW_USBC_UOG_##reg##_RD() : \
 						(n) == USB_UH1 ? HW_USBC_UH1_##reg##_RD(): \
 						(n) == USB_UH2 ? HW_USBC_UH2_##reg##_RD(): \
 						HW_USBC_UH3_##reg##_RD())
#define USB_CORE_REGISTER_WR(n, reg, v)		((n) == USB_OTG ? HW_USBC_UOG_##reg##_WR((v)) : \
						(n) == USB_UH1 ? HW_USBC_UH1_##reg##_WR((v)): \
						(n) == USB_UH2 ? HW_USBC_UH2_##reg##_WR((v)): \
						HW_USBC_UH3_##reg##_WR((v)))
#define USB_DEV_REGISTER_RD(n, reg)		HW_USBC_UOG_##reg##_RD()
#define USB_DEV_REGISTER_WR(n, reg, v)		HW_USBC_UOG_##reg##_WR((v))
#endif

#if defined(CHIP_MX6SL)
#define USB_OTG1	4
#define USB_OTG2	5
#define USB_UH1		6
#define USB_CORE_BM(n, reg, fld)		((n) == USB_OTG1 ? BM_USBC_UOG1_##reg##_##fld : \
 						(n) == USB_OTG2 ? BM_USBC_UOG2_##reg##_##fld: \
 						BM_USBC_UH1_##reg##_##fld)
#define USB_CORE_BP(n, reg, fld)		((n) == USB_OTG1 ? BP_USBC_UOG1_##reg##_##fld : \
 						(n) == USB_OTG2 ? BP_USBC_UOG2_##reg##_##fld: \
 						BP_USBC_UH1_##reg##_##fld)
#define USB_CORE_REGISTER_RD(n, reg)		((n) == USB_OTG1 ? HW_USBC_UOG1_##reg##_RD() : \
 						(n) == USB_OTG2 ? HW_USBC_UOG2_##reg##_RD(): \
 						HW_USBC_UH1_##reg##_RD())
#define USB_CORE_REGISTER_WR(n, reg, v)		(n) == USB_OTG1 ? HW_USBC_UOG1_##reg##_WR((v)) : \
						(n) == USB_OTG2 ? HW_USBC_UOG2_##reg##_WR((v)): \
						HW_USBC_UH1_##reg##_WR((v))
#define USB_DEV_REGISTER_RD(n, reg)		((n) == USB_OTG1 ? HW_USBC_UOG1_##reg##_RD() : \
 						HW_USBC_UOG2_##reg##_RD())
#define USB_DEV_REGISTER_WR(n, reg, v)		(n) == USB_OTG1 ? HW_USBC_UOG1_##reg##_WR((v)) : \
						HW_USBC_UOG2_##reg##_WR((v))
#endif

#define HW_USBC_ID_RD(n)			USB_CORE_REGISTER_RD(n, ID )
#define HW_USBC_HWGENERAL_RD(n)			USB_CORE_REGISTER_RD(n, HWGENERAL )
#define HW_USBC_HWHOST_RD(n)			USB_CORE_REGISTER_RD(n, HWHOST    )
#define HW_USBC_HWDEVICE_RD(n)			USB_CORE_REGISTER_RD(n, HWDEVICE  )
#define HW_USBC_HWTXBUF_RD(n)			USB_CORE_REGISTER_RD(n, HWTXBUF   )
#define HW_USBC_HWRXBUF_RD(n)			USB_CORE_REGISTER_RD(n, HWRXBUF   )
#define HW_USBC_GPTIMER0LD_RD(n)		USB_CORE_REGISTER_RD(n, GPTIMER0LD )
#define HW_USBC_GPTIMER0CTRL_RD(n)		USB_CORE_REGISTER_RD(n, GPTIMER0CTRL)
#define HW_USBC_GPTIMER1LD_RD(n)		USB_CORE_REGISTER_RD(n, GPTIMER1LD )
#define HW_USBC_GPTIMER1CTRL_RD(n)		USB_CORE_REGISTER_RD(n, GPTIMER1CTRL)
#define HW_USBC_SBUSCFG_RD(n)			USB_CORE_REGISTER_RD(n, SBUSCFG )
#define HW_USBC_CAPLENGTH_RD(n)			USB_CORE_REGISTER_RD(n, CAPLENGTH)
#define HW_USBC_HCIVERSION_RD(n)		USB_CORE_REGISTER_RD(n, HCIVERSION )
#define HW_USBC_HCSPARAMS_RD(n)			USB_CORE_REGISTER_RD(n, HCSPARAMS)
#define HW_USBC_HCCPARAMS_RD(n)			USB_CORE_REGISTER_RD(n, HCCPARAMS)
#define HW_USBC_DCIVERSION_RD(n)		USB_CORE_REGISTER_RD(n, DCIVERSION )
#define HW_USBC_DCCPARAMS_RD(n)			USB_CORE_REGISTER_RD(n, DCCPARAMS)
#define HW_USBC_USBCMD_RD(n)			USB_CORE_REGISTER_RD(n, USBCMD )
#define HW_USBC_USBSTS_RD(n)			USB_CORE_REGISTER_RD(n, USBSTS )
#define HW_USBC_USBINTR_RD(n)			USB_CORE_REGISTER_RD(n, USBINTR)
#define HW_USBC_FRINDEX_RD(n)			USB_CORE_REGISTER_RD(n, FRINDEX)
#define HW_USBC_PERIODICLISTBASE_RD(n) 		USB_CORE_REGISTER_RD(n, PERIODICLISTBASE)
#define HW_USBC_DEVICEADDR_RD(n)		USB_DEV_REGISTER_RD(n, DEVICEADDR)
#define HW_USBC_ASYNCLISTADDR_RD(n)		USB_CORE_REGISTER_RD(n, ASYNCLISTADDR)
#define HW_USBC_ENDPTLISTADDR_RD(n)		USB_CORE_REGISTER_RD(n, ENDPTLISTADDR)
#define HW_USBC_BURSTSIZE_RD(n)			USB_CORE_REGISTER_RD(n, BURSTSIZE)
#define HW_USBC_TXFILLTUNING_RD(n)		USB_CORE_REGISTER_RD(n, TXFILLTUNING )
#define HW_USBC_ENDPTNAK_RD(n)			USB_CORE_REGISTER_RD(n, ENDPTNAK )
#define HW_USBC_ENDPTNAKEN_RD(n)		USB_CORE_REGISTER_RD(n, ENDPTNAKEN )
#define HW_USBC_CONFIGFLAG_RD(n)		USB_CORE_REGISTER_RD(n, CONFIGFLAG )
#define HW_USBC_PORTSC1_RD(n)			USB_CORE_REGISTER_RD(n, PORTSC1 )
#define HW_USBC_OTGSC_RD(n)			USB_CORE_REGISTER_RD(n, OTGSC )
#define HW_USBC_USBMODE_RD(n)			USB_CORE_REGISTER_RD(n, USBMODE )
#define HW_USBC_ENDPTSETUPSTAT_RD(n)		USB_DEV_REGISTER_RD(n, ENDPTSETUPSTAT )
#define HW_USBC_ENDPTPRIME_RD(n)		USB_DEV_REGISTER_RD(n, ENDPTPRIME )
#define HW_USBC_ENDPTFLUSH_RD(n)		USB_DEV_REGISTER_RD(n, ENDPTFLUSH )
#define HW_USBC_ENDPTSTAT_RD(n)			USB_DEV_REGISTER_RD(n, ENDPTSTAT )
#define HW_USBC_ENDPTCOMPLETE_RD(n)		USB_DEV_REGISTER_RD(n, ENDPTCOMPLETE )
#define HW_USBC_ENDPTCTRL0_RD(n)		USB_DEV_REGISTER_RD(n, ENDPTCTRL0 )
#define HW_USBC_ENDPTCTRL1_RD(n)		USB_DEV_REGISTER_RD(n, ENDPTCTRL1 )
#define HW_USBC_ENDPTCTRL2_RD(n)		USB_DEV_REGISTER_RD(n, ENDPTCTRL2 )
#define HW_USBC_ENDPTCTRL3_RD(n)		USB_DEV_REGISTER_RD(n, ENDPTCTRL3 )
#define HW_USBC_ENDPTCTRL4_RD(n)		USB_DEV_REGISTER_RD(n, ENDPTCTRL4 )
#define HW_USBC_ENDPTCTRL5_RD(n)		USB_DEV_REGISTER_RD(n, ENDPTCTRL5 )
#define HW_USBC_ENDPTCTRL6_RD(n)		USB_DEV_REGISTER_RD(n, ENDPTCTRL6 )
#define HW_USBC_ENDPTCTRL7_RD(n)		USB_DEV_REGISTER_RD(n, ENDPTCTRL7 )

#define HW_USBC_GPTIMER0LD_WR(n, v)		USB_CORE_REGISTER_WR(n, GPTIMER0LD, v)
#define HW_USBC_GPTIMER0CTRL_WR(n, v)		USB_CORE_REGISTER_WR(n, GPTIMER0CTRL, v)
#define HW_USBC_GPTIMER1LD_WR(n, v)		USB_CORE_REGISTER_WR(n, GPTIMER1LD, v)
#define HW_USBC_GPTIMER1CTRL_WR(n, v)		USB_CORE_REGISTER_WR(n, GPTIMER1CTRL, v)
#define HW_USBC_SBUSCFG_WR(n, v)		USB_CORE_REGISTER_WR(n, SBUSCFG, v)
#define HW_USBC_USBCMD_WR(n, v)			USB_CORE_REGISTER_WR(n, USBCMD, v)
#define HW_USBC_USBSTS_WR(n, v)			USB_CORE_REGISTER_WR(n, USBSTS, v)
#define HW_USBC_USBINTR_WR(n, v)		USB_CORE_REGISTER_WR(n, USBINTR, v)
#define HW_USBC_FRINDEX_WR(n, v)		USB_CORE_REGISTER_WR(n, FRINDEX, v)
#define HW_USBC_PERIODICLISTBASE_WR(n, v) 	USB_CORE_REGISTER_WR(n, PERIODICLISTBASE, v)
#define HW_USBC_DEVICEADDR_WR(n, v)		USB_DEV_REGISTER_WR(n, DEVICEADDR, v)
#define HW_USBC_ASYNCLISTADDR_WR(n, v)		USB_CORE_REGISTER_WR(n, ASYNCLISTADDR, v)
#define HW_USBC_ENDPTLISTADDR_WR(n, v)		USB_CORE_REGISTER_WR(n, ENDPTLISTADDR, v)
#define HW_USBC_BURSTSIZE_WR(n, v)		USB_CORE_REGISTER_WR(n, BURSTSIZE, v)
#define HW_USBC_TXFILLTUNING_WR(n, v)		USB_CORE_REGISTER_WR(n, TXFILLTUNING, v)
#define HW_USBC_ENDPTNAK_WR(n, v)		USB_CORE_REGISTER_WR(n, ENDPTNAK, v)
#define HW_USBC_ENDPTNAKEN_WR(n, v)		USB_CORE_REGISTER_WR(n, ENDPTNAKEN, v)
#define HW_USBC_CONFIGFLAG_WR(n, v)		USB_CORE_REGISTER_WR(n, CONFIGFLAG, v)
#define HW_USBC_PORTSC1_WR(n, v)		USB_CORE_REGISTER_WR(n, PORTSC1, v)
#define HW_USBC_OTGSC_WR(n, v)			USB_CORE_REGISTER_WR(n, OTGSC, v)
#define HW_USBC_USBMODE_WR(n, v)		USB_CORE_REGISTER_WR(n, USBMODE, v )
#define HW_USBC_ENDPTSETUPSTAT_WR(n, v)		USB_DEV_REGISTER_WR(n, ENDPTSETUPSTAT, v)
#define HW_USBC_ENDPTPRIME_WR(n, v)		USB_DEV_REGISTER_WR(n, ENDPTPRIME, v)
#define HW_USBC_ENDPTFLUSH_WR(n, v)		USB_DEV_REGISTER_WR(n, ENDPTFLUSH, v)
#define HW_USBC_ENDPTCOMPLETE_WR(n, v)		USB_DEV_REGISTER_WR(n, ENDPTCOMPLETE, v)
#define HW_USBC_ENDPTCTRL0_WR(n, v)		USB_DEV_REGISTER_WR(n, ENDPTCTRL0, v)
#define HW_USBC_ENDPTCTRL1_WR(n, v)		USB_DEV_REGISTER_WR(n, ENDPTCTRL1, v)
#define HW_USBC_ENDPTCTRL2_WR(n, v)		USB_DEV_REGISTER_WR(n, ENDPTCTRL2, v)
#define HW_USBC_ENDPTCTRL3_WR(n, v)		USB_DEV_REGISTER_WR(n, ENDPTCTRL3, v)
#define HW_USBC_ENDPTCTRL4_WR(n, v)		USB_DEV_REGISTER_WR(n, ENDPTCTRL4, v)
#define HW_USBC_ENDPTCTRL5_WR(n, v)		USB_DEV_REGISTER_WR(n, ENDPTCTRL5, v)
#define HW_USBC_ENDPTCTRL6_WR(n, v)		USB_DEV_REGISTER_WR(n, ENDPTCTRL6, v)
#define HW_USBC_ENDPTCTRL7_WR(n, v)		USB_DEV_REGISTER_WR(n, ENDPTCTRL7, v)


/*
 * Regiseter field value definitions
 */
#define USB_USBCMD_FS_1024               (0)
#define USB_USBCMD_FS_512                (0x4)
#define USB_USBCMD_FS_256                (0x8)
#define USB_USBCMD_FS_128                (0xC)
#define USB_USBCMD_FS_64                 (0x8000)
#define USB_USBCMD_FS_32                 (0x8004)
#define USB_USBCMD_FS_16                 (0x8008)
#define USB_USBCMD_FS_8                  (0x800C)
#define USB_USBCMD_FS_MASK               (0x0000800C)

#define USB_USBMODE_CM_IDLE              (0)
#define USB_USBMODE_CM_DEVICE            (0x2)
#define USB_USBMODE_CM_HOST              (0x3)

/*
 * Reserved the Endpoint registers, since mx6dq/mx6sdl and mx6sl can not shared the 
 * same macros defined in their register header file.
 */
#define USB_ENDPTSETUPSTAT_ENDPTSETUPSTAT(x) (((x)&0xFF)<<0)

#define USB_ENDPTPRIME_PERB(x)           (((x)&0x3F)<<0)
#define USB_ENDPTPRIME_PETB(x)           (((x)&0x3F)<<0x10)

#define USB_ENDPTFLUSH_FERB(x)           (((x)&0x3F)<<0)
#define USB_ENDPTFLUSH_FETB(x)           (((x)&0x3F)<<0x10)

#define USB_ENDPTSTATUS_ERBR(x)          (((x)&0xFF)<<0)
#define USB_ENDPTSTATUS_ETBR(x)          (((x)&0xFF)<<0x10)

#define USB_ENDPTCOMPLETE_ERCE0          (0x1)
#define USB_ENDPTCOMPLETE_ERCE1          (0x2)
#define USB_ENDPTCOMPLETE_ERCE2          (0x4)
#define USB_ENDPTCOMPLETE_ERCE3          (0x8)
#define USB_ENDPTCOMPLETE_ETCE0          (0x10000)
#define USB_ENDPTCOMPLETE_ETCE1          (0x20000)
#define USB_ENDPTCOMPLETE_ETCE2          (0x40000)
#define USB_ENDPTCOMPLETE_ETCE3          (0x80000)
#define USB_ENDPTCOMPLETE_ERCE(x)        (((x)&0x3F)<<0)
#define USB_ENDPTCOMPLETE_ETCE(x)        (((x)&0x3F)<<0x10)

#define USB_ENDPTCTRL0_RXS               (0x1)
#define USB_ENDPTCTRL0_RXT(x)            (((x)&0x3)<<0x2)
#define USB_ENDPTCTRL0_RXE               (0x80)
#define USB_ENDPTCTRL0_TXS               (0x10000)
#define USB_ENDPTCTRL0_TXT(x)            (((x)&0x3)<<0x12)
#define USB_ENDPTCTRL0_TXE               (0x800000)

#define USB_ENDPTCTRL_RXS                (0x1)
#define USB_ENDPTCTRL_RXD                (0x2)
#define USB_ENDPTCTRL_RXT(x)             (((x)&0x3)<<0x2)
#define USB_ENDPTCTRL_RXT_CONTROL        (0)
#define USB_ENDPTCTRL_RXT_ISO            (0x4)
#define USB_ENDPTCTRL_RXT_BULK           (0x8)
#define USB_ENDPTCTRL_RXT_INT            (0xC)
#define USB_ENDPTCTRL_RXI                (0x20)
#define USB_ENDPTCTRL_RXR                (0x40)
#define USB_ENDPTCTRL_RXE                (0x80)
#define USB_ENDPTCTRL_TXS                (0x10000)
#define USB_ENDPTCTRL_TXD                (0x20000)
#define USB_ENDPTCTRL_TXT(x)             (((x)&0x3)<<0x12)
#define USB_ENDPTCTRL_TXT_CONTROL        (0)
#define USB_ENDPTCTRL_TXT_ISO            (0x40000)
#define USB_ENDPTCTRL_TXT_BULK           (0x80000)
#define USB_ENDPTCTRL_TXT_INT            (0xC0000)
#define USB_ENDPTCTRL_TXI                (0x200000)
#define USB_ENDPTCTRL_TXR                (0x400000)
#define USB_ENDPTCTRL_TXE                (0x800000)

#endif 
