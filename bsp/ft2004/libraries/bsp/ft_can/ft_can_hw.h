/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-27 13:52:47
 * @LastEditTime: 2021-04-27 13:52:47
 * @Description:  Description of file
 * @Modify History:
 * * * Ver   Who        Date         Changes
 * * ----- ------     --------    --------------------------------------
 */

#ifndef FT_CAN_HW_H
#define FT_CAN_HW_H

#include "ft_types.h"
#include "ft_io.h"
#include "ft_can.h"

/***ft CAN REGISTER offset*/
#define FCAN_CTRL_OFFSET 0x00          /* Global control register */
#define FCAN_INTR_OFFSET 0x04          /* Interrupt register */
#define FCAN_ARB_RATE_CTRL_OFFSET 0x08 /* Arbitration rate control register */
#define FCAN_DAT_RATE_CTRL_OFFSET 0x0C /* Data rate control register */
#define FCAN_ACC_ID0_OFFSET 0x10       /* Acceptance identifier0 register */
#define FCAN_ACC_ID1_OFFSET 0x14       /* Acceptance identifier1 register */
#define FCAN_ACC_ID2_OFFSET 0x18       /* Acceptance identifier2 register */
#define FCAN_ACC_ID3_OFFSET 0x1C       /* Acceptance identifier3 register */
#define FCAN_ACC_ID0_MASK_OFFSET 0x20  /* Acceptance identifier0 mask register */
#define FCAN_ACC_ID1_MASK_OFFSET 0x24  /* Acceptance identifier1 mask register */
#define FCAN_ACC_ID2_MASK_OFFSET 0x28  /* Acceptance identifier2 mask register */
#define FCAN_ACC_ID3_MASK_OFFSET 0x2C  /* Acceptance identifier3 mask register */
#define FCAN_XFER_STS_OFFSET 0x30      /* Transfer status register */
#define FCAN_ERR_CNT_OFFSET 0x34       /* Error counter register */
#define FCAN_FIFO_CNT_OFFSET 0x38      /* FIFO counter register */
#define FCAN_DMA_CTRL_OFFSET 0x3C      /* DMA request control register */
#define FCAN_TX_FIFO_OFFSET 0x100      /* TX FIFO shadow register */
#define FCAN_RX_FIFO_OFFSET 0x200      /* RX FIFO shadow register */

/*----------------------------------------------------------------------------*/
/* CAN register bit masks - FCAN_<REG>_<BIT>_MASK                            */
/*----------------------------------------------------------------------------*/

/* FCAN_CTRL mask */
#define FCAN_CTRL_XFER_MASK (0x1 << 0) /* RW */  /*Transfer enable*/
#define FCAN_CTRL_TXREQ_MASK (0x1 << 1) /* RW */ /*Transmit request*/
#define FCAN_CTRL_AIME_MASK (0x1 << 2) /* RW */  /*Acceptance identifier mask enable*/
#define FCAN_CTRL_RESET_MASK (0x1 << 6)

/* FCAN_INTR mask */
#define FCAN_INTR_STATUS_MASK (0xFF << 0) /* RO */ /*the interrupt status*/
#define FCAN_INTR_BOIS_MASK (0x1 << 0) /* RO */    /*Bus off interrupt status*/
#define FCAN_INTR_PWIS_MASK (0x1 << 1) /* RO */    /*Passive warning interrupt status*/
#define FCAN_INTR_PEIS_MASK (0x1 << 2) /* RO */    /*Passive error interrupt status*/
#define FCAN_INTR_RFIS_MASK (0x1 << 3) /* RO */    /*RX FIFO full interrupt status*/
#define FCAN_INTR_TFIS_MASK (0x1 << 4) /* RO */    /*TX FIFO empty interrupt status*/
#define FCAN_INTR_REIS_MASK (0x1 << 5) /* RO */    /*RX frame end interrupt status*/
#define FCAN_INTR_TEIS_MASK (0x1 << 6) /* RO */    /*TX frame end interrupt status*/
#define FCAN_INTR_EIS_MASK (0x1 << 7) /* RO */     /*Error interrupt status*/

#define FCAN_INTR_EN_MASK (0xFF << 8) /* RO */   /*the interrupt enable*/
#define FCAN_INTR_BOIE_MASK (0x1 << 8) /* RW */  /*Bus off interrupt enable*/
#define FCAN_INTR_PWIE_MASK (0x1 << 9) /* RW */  /*Passive warning interrupt enable*/
#define FCAN_INTR_PEIE_MASK (0x1 << 10) /* RW */ /*Passive error interrupt enable*/
#define FCAN_INTR_RFIE_MASK (0x1 << 11) /* RW */ /*RX FIFO full interrupt enable*/
#define FCAN_INTR_TFIE_MASK (0x1 << 12) /* RW */ /*TX FIFO empty interrupt enable*/
#define FCAN_INTR_REIE_MASK (0x1 << 13) /* RW */ /*RX frame end interrupt enable*/
#define FCAN_INTR_TEIE_MASK (0x1 << 14) /* RW */ /*TX frame end interrupt enable*/
#define FCAN_INTR_EIE_MASK (0x1 << 15) /* RW */  /*Error interrupt enable*/

#define FCAN_INTR_BOIC_MASK (0x1 << 16) /* WO */ /*Bus off interrupt clear*/
#define FCAN_INTR_PWIC_MASK (0x1 << 17) /* WO */ /*Passive warning interrupt clear*/
#define FCAN_INTR_PEIC_MASK (0x1 << 18) /* WO */ /*Passive error interrupt clear*/
#define FCAN_INTR_RFIC_MASK (0x1 << 19) /* WO */ /*RX FIFO full interrupt clear*/
#define FCAN_INTR_TFIC_MASK (0x1 << 20) /* WO */ /*TX FIFO empty interrupt clear*/
#define FCAN_INTR_REIC_MASK (0x1 << 21) /* WO */ /*RX frame end interrupt clear*/
#define FCAN_INTR_TEIC_MASK (0x1 << 22) /* WO */ /*TX frame end interrupt clear*/
#define FCAN_INTR_EIC_MASK (0x1 << 23) /* WO */  /*Error interrupt clear*/

/* FCAN_ACC_ID(0-3)_MASK mask */
#define FCAN_ACC_IDN_MASK 0x1FFFFFFF /* WO */ /*don’t care the matching */
/* FCAN_DAT_RATE_CTRL mask */

/* FCAN_ERR_CNT_OFFSET mask */
#define FCAN_ERR_CNT_RFN_MASK (0xFF << 0) /* RO */  /*Receive error counter*/
#define FCAN_ERR_CNT_TFN_MASK (0xFF << 16) /* RO */ /*Transmit error counter*/

/* FCAN_FIFO_CNT_OFFSET mask */
#define FCAN_FIFO_CNT_RFN_MASK (0xFF << 0) /* RO */  /*Receive FIFO valid data number*/
#define FCAN_FIFO_CNT_TFN_MASK (0xFF << 16) /* RO */ /*Transmit FIFO valid data number*/

#define FCAN_ERR_CNT_TFN_SHIFT 16  /* Tx Error Count shift */
#define FCAN_FIFO_CNT_TFN_SHIFT 16 /* Tx FIFO Count shift*/
#define FCAN_IDR_ID1_SHIFT 21      /* Standard Messg Identifier */
#define FCAN_IDR_ID2_SHIFT 1       /* Extended Message Identifier */
#define FCAN_IDR_SDLC_SHIFT 14
#define FCAN_IDR_EDLC_SHIFT 26
#define FCAN_ACC_IDN_SHIFT 18 /*Standard ACC ID shift*/

#define FCAN_IDR_ID2_MASK 0x0007FFFE  /* Extended message ident */
#define FCAN_IDR_ID1_MASK 0xFFE00000  /* Standard msg identifier */
#define FCAN_IDR_IDE_MASK 0x00080000  /* Identifier extension */
#define FCAN_IDR_SRR_MASK 0x00100000  /* Substitute remote TXreq */
#define FCAN_IDR_RTR_MASK 0x00000001  /* Extended frames remote TX request */
#define FCAN_IDR_DLC_MASK 0x0003C000  /* Standard msg dlc */
#define FCAN_IDR_PAD_MASK 0x00003FFF  /* Standard msg padding 1 */
#define FCAN_IDR_EDLC_MASK 0x3C000000 /* Extended msg dlc */

/* Can timming */
#define FCAN_TSEG1_MIN 1
#define FCAN_TSEG1_MAX 8
#define FCAN_TSEG2_MIN 1
#define FCAN_TSEG2_MAX 8
#define FCAN_SJW_MAX 4
#define FCAN_BRP_MIN 1
#define FCAN_BRP_MAX 512
#define FCAN_BRP_INC 1
#define FCAN_CALC_SYNC_SEG 1

/**
*
* This macro reads the given register.
*
* @param    BaseAddr is the base address of the device.
* @param    RegOffset is the register offset to be read.
*
* @return   The 32-bit value of the register
*
* @note     None.
*
*****************************************************************************/
#define FCan_ReadReg(BaseAddr, RegOffset) \
    Ft_in32((BaseAddr) + (u32)(RegOffset))

/****************************************************************************/
/**
*
* This macro writes the given register.
*
* @param    BaseAddr is the base address of the device.
* @param    RegOffset is the register offset to be written.
* @param    Data is the 32-bit value to write to the register.
*
* @return   None.
*
* @note     None.
*
*****************************************************************************/
#define FCan_WriteReg(BaseAddr, RegOffset, Data) \
    Ft_out32((BaseAddr) + (u32)(RegOffset), (u32)(Data))

#define FCan_SetBit(BaseAddr, RegOffset, Data) \
    Ft_setBit32((BaseAddr) + (u32)(RegOffset), (u32)(Data))

#define FCan_ClearBit(BaseAddr, RegOffset, Data) \
    Ft_clearBit32((BaseAddr) + (u32)(RegOffset), (u32)(Data))

void FCan_Reset(FCan_t *Can_p);

#endif // !
