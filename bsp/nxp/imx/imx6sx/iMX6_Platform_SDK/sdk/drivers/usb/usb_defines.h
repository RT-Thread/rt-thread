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

/*
 * @file		USB_DEFINES.h
 * @brief:		Bit defines for USB data structures
 *
 */

#ifndef _USB_DEFINES_H
#define _USB_DEFINES_H

/********************************************************************/

/*
 * Bit definitions for USB data structures.
 */
#define USB_QH_LINK_PTR_TYP_ITD		0x00000000
#define USB_QH_LINK_PTR_TYP_QH		0x00000002
#define USB_QH_LINK_PTR_TYP_SITD	0x00000004
#define USB_QH_LINK_PTR_TYP_FSTN	0x00000006
#define USB_QH_LINK_PTR_T			0x00000001

#define USB_QH_EP_CHAR_RL(x)	    (((x)&0x7)<<29)
#define USB_QH_EP_CHAR_C		    0x10000000
#define USB_QH_EP_CHAR_MAX_PACKET(x)   (((x)&0x7FF)<<16)
#define USB_QH_EP_CHAR_H		    0x00008000
#define USB_QH_EP_CHAR_DTC		    0x00004000
#define USB_QH_EP_CHAR_EPS_FULL   	0x00000000
#define USB_QH_EP_CHAR_EPS_LOW   	0x00001000
#define USB_QH_EP_CHAR_EPS_HIGH   	0x00002000
#define USB_QH_EP_CHAR_EP(x)   		(((x)&0xF)<<8)
#define USB_QH_EP_CHAR_I		    0x00000080
#define USB_QH_EP_CHAR_DEV_ADDR(x)  (((x)&0x7F)<<0)

#define USB_QH_EP_CAP_MULT_ONE   	0x40000000
#define USB_QH_EP_CAP_MULT_TWO   	0x80000000
#define USB_QH_EP_CAP_MULT_THREE  	0xC0000000
#define USB_QH_EP_CAP_PORT_NUM(x)  	(((x)&0x7F)<<23)
#define USB_QH_EP_CAP_HUB_ADDR(x)  	(((x)&0x7F)<<16)
#define USB_QH_EP_CAP_UFRAME_CMASK(x)	(((x)&0xFF)<<8)
#define USB_QH_EP_CAP_UFRAME_SMASK(x)	(((x)&0xFF)<<0)

#define USB_QTD_NEXT_QTD_T   		0x00000001

#define USB_QTD_ALT_QTD_NAK_CNT(x)		(((x)&0xF)<<1)
#define USB_QTD_ALT_QTD_T   		0x00000001

#define USB_QTD_TOKEN_DT	   		0x80000000
#define USB_QTD_TOKEN_TRANS_SIZE(x)	(((x)&0x7FFF)<<16)
#define USB_QTD_TOKEN_IOC			0x00008000
#define USB_QTD_TOKEN_C_PAGE(x)		(((x)&0x7)<<12)
#define USB_QTD_TOKEN_CERR(x)		(((x)&0x3)<<10)
#define USB_QTD_TOKEN_PID_OUT		0x00000000
#define USB_QTD_TOKEN_PID_IN		0x00000100
#define USB_QTD_TOKEN_PID_SETUP		0x00000200
#define USB_QTD_TOKEN_STAT_ACTIVE	0x00000080
#define USB_QTD_TOKEN_STAT_HALTED	0x00000040
#define USB_QTD_TOKEN_STAT_DBE		0x00000020
#define USB_QTD_TOKEN_STAT_BABBLE	0x00000010
#define USB_QTD_TOKEN_STAT_XACT_ERR	0x00000008
#define USB_QTD_TOKEN_STAT_MISS_UFRAME	0x00000004
#define USB_QTD_TOKEN_STAT_SPLITXSTATE	0x00000002
#define USB_QTD_TOKEN_STAT_PING		0x00000001

#define USB_QTD_BUF_PTR(x)			(((x)&0xFFFFF)<<12)
#define USB_QTD_BUF0_OFFSET(x)		(((x)&0xFFF)<<0)

#define USB_QTD_BUF1_C_PROG_MASK(x)	(((x)&0xFF)<<0)

#define USB_QTD_BUF2_S_BYTES(x)		(((x)&0x1FF)<<3)
#define USB_QTD_BUF2_FRAME_TAG(x)	(((x)&0x7)<<0)

#define USB_ITD_LINK_PTR_TYP_ITD	0x00000000
#define USB_ITD_LINK_PTR_TYP_QH		0x00000002
#define USB_ITD_LINK_PTR_TYP_SITD	0x00000004
#define USB_ITD_LINK_PTR_TYP_FSTN	0x00000006
#define USB_ITD_LINK_PTR_T			0x00000001

#define USB_ITD_TRANS_STAT_ACTIVE	0x80000000
#define USB_ITD_TRANS_STAT_DBE		0x40000000
#define USB_ITD_TRANS_STAT_BABBLE	0x20000000
#define USB_ITD_TRANS_STAT_XACT_ERR	0x10000000
#define USB_ITD_TRANS_LEN(x)		(((x)&0xFFF)<<16)
#define USB_ITD_TRANS_IOC			0x00008000
#define USB_ITD_TRANS_PG(x)			(((x)&0x7)<<12)
#define USB_ITD_TRANS_OFFSET(x)		(((x)&0xFFF)<<0)

#define USB_ITD_BUF_PTR(x)			(((x)&0xFFFFF)<<12)
#define USB_ITD_BUF0_EP(x)			(((x)&0xF)<<8)
#define USB_ITD_BUF0_DEV_ADDR(x)		(((x)&0x7F)<<0)

#define USB_ITD_BUF1_IO				0x00000800
#define USB_ITD_BUF1_MAX_PACKET(x)  (((x)&0x7FF)<<0)

#define USB_ITD_BUF2_MULT(x)		(((x)&0x3)<<0)

#define USB_EP_QH_EP_CHAR_MULT(x)		(((x)&0x3)<<30)
#define USB_EP_QH_EP_CHAR_MULT_NORM 	0x00000000
#define USB_EP_QH_EP_CHAR_MULT_ONE 		0x40000000
#define USB_EP_QH_EP_CHAR_MULT_TWO 		0x80000000
#define USB_EP_QH_EP_CHAR_MULT_THREE 	0xC0000000
#define USB_EP_QH_EP_CHAR_ZLT		    0x20000000
#define USB_EP_QH_EP_CHAR_MAX_PACKET(x)	(((x)&0x7FF)<<16)
#define USB_EP_QH_EP_CHAR_IOS		    0x00008000

#define USB_DTD_NEXT_DTD_T   			0x00000001

#define USB_DTD_TOKEN_TOTAL_BYTES(x)	(((x)&0x7FFF)<<16)
#define USB_DTD_TOKEN_IOC				0x00008000
#define USB_DTD_TOKEN_MULTO(x)			(((x)&0x3)<<10)
#define USB_DTD_TOKEN_MULTO_ONE			0x00000100
#define USB_DTD_TOKEN_MULTO_TWO			0x00000200
#define USB_DTD_TOKEN_MULTO_THREE		0x00000300
#define USB_DTD_TOKEN_STAT_ACTIVE		0x00000080
#define USB_DTD_TOKEN_STAT_HALTED		0x00000040
#define USB_DTD_TOKEN_STAT_DBE			0x00000020
#define USB_DTD_TOKEN_STAT_XACT_ERR		0x00000008

#define USB_DTD_BUF_PTR(x)				(((x)&0xFFFFF)<<12)
#define USB_DTD_BUF0_OFFSET(x)			(((x)&0xFFF)<<0)

#define USB_DTD_BUF1_FRAME_NUM(x)		(((x)&0x7FF)<<0)

#endif /* USB_DEFINES_H */
