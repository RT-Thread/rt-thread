//*****************************************************************************
//
// hw_usb.h - Macros for use in accessing the USB registers.
//
// Copyright (c) 2007-2010 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of Hercules Development Kit software.
//
//******************************************************************************

#ifndef __HW_USB_H__
#define __HW_USB_H__

/** @brief Base address of memmory mapped Registers                 		  */
#define USBD_0_BASE			0xFCF78A00u
#define USB0_BASE			USBD_0_BASE

typedef volatile struct {
	uint16 rev;			/* Revision 					  		  	  */
	
	/** Endpoint registers	***************************************************/
	uint16 epnum;			/* Endpoint selection 			  		  */
	uint16 data;			/* Data 						  		  */
	uint16 ctrl;			/* Control 						  		  */
	uint16 stat_flag;		/* Status 						  		  */
	uint16 rxf_stat;		/* RX FIFO Status 				  		  */
	uint16 syscon1;			/* System configuration 1 		  		  */
	uint16 syscon2;			/* System configuration 2 		  		  */
	uint16 dev_stat;		/* Device status 				  		  */
	uint16 sof;				/* Start of frame 				  		  */
	uint16 irq_en;			/* Interrupt enable 			  		  */
	uint16 dma_irqen;		/* DMA Interrupt enable 		  		  */
	uint16 irqsrc;			/* Interrupt source 			  		  */
	uint16 epn_stat;		/* Non-ISO EP interrupt enable 	  		  */
	uint16 dman_stat;		/* Non-ISO DMA interrupt enable   		  */
	uint16 _rsvd1[1];		/* Reserved for reg holes				  */
	
	/** DMA Configuration	***************************************************/
	uint16 rxdma_cfg; 		/* DMA Rx channels configuration 	      */
	uint16 txdma_cfg; 		/* DMA Tx channels configuration 	  	  */
	uint16 data_dma; 		/* DMA FIFO data				  	  	  */
	uint16 txdma0; 			/* Transmit DMA control 0		  	  	  */
	uint16 txdma1; 			/* Transmit DMA control 1		  	  	  */
	uint16 txdma2; 			/* Transmit DMA control 2		  	  	  */
	uint16 _rsvd2[2];		/* Reserved for reg holes				  */
	
	uint16 dman_rxdma0; 	/* Receive DMA control 0		  		  */
	uint16 dman_rxdma1;		/* Receive DMA control 1		  		  */
	uint16 dman_rxdma2;		/* Receive DMA control 2		  		  */
	uint16 _rsvd3[5];		/* Reserved 							  */

	/** Endpoint Configuration	***********************************************/
	uint16 ep0; 			/* Endpoint 0 Configuration 	  		  */

	uint16 epn_rx[15];		/* RX EP configurations... 				  */
	uint16 _rsvd4[1];		/* Reserved for reg holes 				  */
	
	uint16 epn_tx[15];		/* TX EP configurations...				  */
} usbdRegs;

/******************************************************************************\
* Register Bit Masks 
* (USBD_<Instance ID=0>_<Register Name>_<Bit Field Name> <Mask Value>
\******************************************************************************/

/* Endpoint selection *********************************************************/
#define USBD_EP_NUM_SETUP_SEL    				(0x0040u)
#define USBD_EP_NUM_EP_SEL       				(0x0020u)
#define USBD_EP_NUM_EP_DIR       				(0x0010u)
#define USBD_EP_NUM_EP_NUM_MASK     			(0x000Fu)

/* Data ***********************************************************************/
#define USBD_DATA_DATA          				(0xFFFFu)

/* Control ********************************************************************/
#define USBD_CTRL_CLR_HALT      				(0x0080u)
#define USBD_CTRL_SET_HALT      				(0x0040u)
#define USBD_CTRL_SET_FIFO_EN   				(0x0004u)
#define USBD_CTRL_CLR_EP        				(0x0002u)
#define USBD_CTRL_RESET_EP      				(0x0001u)

/* Status *********************************************************************/
#define USBD_STAT_FLG_NO_RXPACKET 				(0x8000u)
#define USBD_STAT_FLG_MISS_IN   				(0x4000u)
#define USBD_STAT_FLG_DATA_FLUSH 				(0x2000u)
#define USBD_STAT_FLG_ISO_ERR   				(0x1000u)
#define USBD_STAT_FLG_ISO_FIFO_EMPTY 			(0x0200u)
#define USBD_STAT_FLG_ISO_FIFO_FULL 			(0x0100u)
#define USBD_STAT_FLG_EP_HALTED 				(0x0040u)
#define USBD_STAT_FLG_STALL     				(0x0020u)
#define USBD_STAT_FLG_NAK       				(0x0010u)
#define USBD_STAT_FLG_ACK       				(0x0008u)
#define USBD_STAT_FLG_FIFO_EN   				(0x0004u)
#define USBD_STAT_FLG_NON_ISO_FIFO_EMPTY 		(0x0002u)
#define USBD_STAT_FLG_NON_ISO_FIFO_FULL 		(0x0001u)

/* RX FIFO Status 					 */
#define USBD_RXFSTAT_RXF_COUNT  				(0x03FFu)

/* System configuration 1 *****************************************************/
#define USBD_SYSCON1_CFG_LOCK   				(0x0100u)
#define USBD_SYSCON1_DATA_ENDIAN 				(0x0080u)
#define USBD_SYSCON1_DMA_ENDIAN 				(0x0040u)
#define USBD_SYSCON1_NAK_EN     				(0x0010u)
#define USBD_SYSCON1_AUTODEC_DIS 				(0x0008u)
#define USBD_SYSCON1_SELF_PWR   				(0x0004u)
#define USBD_SYSCON1_SOFF_DIS   				(0x0002u)
#define USBD_SYSCON1_PULLUP_EN  				(0x0001u)

/* System configuration 2 *****************************************************/
#define USBD_SYSCON2_RMT_WKP    				(0x0040u)
#define USBD_SYSCON2_STALL_CMD  				(0x0020u)
#define USBD_SYSCON2_DEV_CFG    				(0x0008u)
#define USBD_SYSCON2_CLR_CFG    				(0x0004u)

/* Device status **************************************************************/
#define USBD_DEVSTAT_B_HNP_ENABLE 				(0x0200u)
#define USBD_DEVSTAT_A_HNP_SUPPORT 				(0x0100u)
#define USBD_DEVSTAT_A_ALT_HNP_SUPPORT 			(0x0080u)
#define USBD_DEVSTAT_R_WK_OK    				(0x0040u)
#define USBD_DEVSTAT_USB_RESET  				(0x0020u)
#define USBD_DEVSTAT_SUS        				(0x0010u)
#define USBD_DEVSTAT_CFG        				(0x0008u)
#define USBD_DEVSTAT_ADD        				(0x0004u)
#define USBD_DEVSTAT_DEF        				(0x0002u)
#define USBD_DEVSTAT_ATT        				(0x0001u)


/* Start of frame *************************************************************/
#define USBD_SOF_FT_LOCK        				(0x1000u)
#define USBD_SOF_TS_OK          				(0x0800u)
#define USBD_SOF_TS            					(0x07FFu)

/* Interrupt enable ***********************************************************/
#define USBD_IRQ_EN_SOF_IE      				(0x0080u)
#define USBD_IRQ_EN_EPN_RX_IE   				(0x0020u)
#define USBD_IRQ_EN_EPN_TX_IE   				(0x0010u)
#define USBD_IRQ_EN_DS_CHG_IE   				(0x0008u)
#define USBD_IRQ_EN_EP0_IE      				(0x0001u)

/* DMA Interrupt enable *******************************************************/
#define USBD_DMA_IRQ_EN_TX2_DONE_IE 			(0x0400u)
#define USBD_DMA_IRQ_EN_RX2_CNT_IE 				(0x0200u)
#define USBD_DMA_IRQ_EN_RX2_EOT_IE 				(0x0100u)
#define USBD_DMA_IRQ_EN_TX1_DONE_IE 			(0x0040u)
#define USBD_DMA_IRQ_EN_RX1_CNT_IE 				(0x0020u)
#define USBD_DMA_IRQ_EN_RX1_EOT_IE 				(0x0010u)
#define USBD_DMA_IRQ_EN_TX0_DONE_IE 			(0x0004u)
#define USBD_DMA_IRQ_EN_RX0_CNT_IE 				(0x0002u)
#define USBD_DMA_IRQ_EN_RX0_EOT_IE 				(0x0001u)

/* Interrupt source ***********************************************************/
#define USBD_IRQ_SRC_TXN_DONE   				(0x0400u)
#define USBD_IRQ_SRC_RXN_CNT    				(0x0200u)
#define USBD_IRQ_SRC_RXN_EOT    				(0x0100u)
#define USBD_IRQ_SRC_SOF        				(0x0080u)
#define USBD_IRQ_SRC_EPN_RX     				(0x0020u)
#define USBD_IRQ_SRC_EPN_TX    					(0x0010u)
#define USBD_IRQ_SRC_DS_CHG     				(0x0008u)
#define USBD_IRQ_SRC_SETUP      				(0x0004u)
#define USBD_IRQ_SRC_EP0_RX     				(0x0002u)
#define USBD_IRQ_SRC_EP0_TX     				(0x0001u)

/* Non-ISO endpoint interrupt enable ******************************************/
#define USBD_EPN_STAT_RX_IT_SRC 				(0x0F00u)
#define USBD_EPN_STAT_TX_IT_SRC 				(0x000Fu)

/* Non-ISO DMA interrupt enable ***********************************************/
#define USBD_DMAN_STAT_RX_SB    				(0x1000u)
#define USBD_DMAN_STAT_RX_IT_SRC 				(0x0F00u)
#define USBD_DMAN_STAT_TX_IT_SRC 				(0x000Fu)

/* DMA Receive channels configuration *****************************************/
#define USBD_RXDMA_CFG_RX_REQ   				(0x1000u)
#define USBD_RXDMA_CFG_RXDMA2_EP 				(0x0F00u)
#define USBD_RXDMA_CFG_RXDMA1_EP 				(0x00F0u)
#define USBD_RXDMA_CFG_RXDMA0_EP 				(0x000Fu)

/* DMA Transmit channels configuration ****************************************/
#define USBD_TXDMA_CFG_TX_REQ   				(0x1000u)
#define USBD_TXDMA_CFG_TXDMA2_EP 				(0x0F00u)
#define USBD_TXDMA_CFG_TXDMA1_EP 				(0x00F0u)
#define USBD_TXDMA_CFG_TXDMA0_EP 				(0x000Fu)

/* DMA FIFO data **************************************************************/
#define USBD_DATA_DMA_DATA_DMA  				(0xFFFFu)

/* Transmit DMA control 0 *****************************************************/
#define USBD_TXDMA0_TX0_EOT     				(0x8000u)
#define USBD_TXDMA0_TX0_START   				(0x4000u)
#define USBD_TXDMA0_TX0_TSC     				(0x03FFu)

/* Transmit DMA control 1 *****************************************************/
#define USBD_TXDMA1_TX1_EOT    					(0x8000u)
#define USBD_TXDMA1_TX1_START   				(0x4000u)
#define USBD_TXDMA1_TX1_TSC     				(0x03FFu)
#define USBD_TXDMA1_TX1_TSC_SHIFT    			(0x0000u)

/* Transmit DMA control 2 *****************************************************/
#define USBD_TXDMA2_TX2_EOT     				(0x8000u)
#define USBD_TXDMA2_TX2_START   				(0x4000u)
#define USBD_TXDMA2_TX2_TSC     				(0x03FFu)

/* Receive DMA control 0 ******************************************************/
#define USBD_RXDMA0_RX0_STOP    				(0x8000u)
#define USBD_RXDMA0_RX0_TC      				(0x00FFu)

/* Receive DMA control 1 ******************************************************/
#define USBD_RXDMA1_RX10_STOP   				(0x8000u)
#define USBD_RXDMA1_RX1_TC      				(0x00FFu)

/* Receive DMA control 2 ******************************************************/
#define USBD_RXDMA2_RX2_STOP    				(0x8000u)
#define USBD_RXDMA2_RX2_TC      				(0x00FFu)

/* Endpoint 0 Configuration ***************************************************/
#define USBD_EP0_SIZE           				(0x3000u)
#define USBD_EP0_PTR            				(0x07FFu)

/* Receive endpoint configurations... *****************************************/
#define USBD_RX_EP_VALID        				(0x8000u)
#define USBD_RX_EP_SIZEDB       				(0x4000u)
#define USBD_RX_EP_SIZE         				(0x3000u)
#define USBD_RX_EP_ISO          				(0x0800u)
#define USBD_RX_EP_PTR          				(0x07FFu)

/* Transmit endpoint configurations... ****************************************/
#define USBD_TX_EP_VALID        				(0x8000u)
#define USBD_TX_EP_SIZEDB       				(0x4000u)
#define USBD_TX_EP_SIZE         				(0x3000u)
#define USBD_TX_EP_ISO          				(0x0800u)
#define USBD_TX_EP_PTR          				(0x07FFu)

#define USBD_MAX_EP0_PTR						(0xFFu)
#define USBD_EP_RX_MAX							(15u)
#define USBD_EP_TX_MAX							(15u)

/** @brief Macro for setting a bit/s in a register (read, modify & write)	  */
#define USBD_REG_BIT_SET(reg,bit) ((reg) |= ((uint16)(bit)))
/** @brief Macro for clearing a bit/s in a register (read, modify & write)	  */
#define USBD_REG_BIT_CLR(reg,bit) ((reg) &= ((uint16)~((uint16)bit)))
/** @brief Macro for setting a bit/s in a register (write)	  				  */
#define USBD_REG_SET_ONE(reg,value) ((reg) = ((uint16)value))

#endif // __HW_USB_H__
