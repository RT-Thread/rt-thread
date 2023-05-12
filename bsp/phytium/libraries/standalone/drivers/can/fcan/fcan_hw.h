/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fcan_hw.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:29:05
 * Description:  This files is for the can register related definition
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/5/26  first release
 * 1.1   zhangyan      2022/12/7  improve functions
 */


#ifndef FCAN_HW_H
#define FCAN_HW_H

#include "fparameters.h"
#include "ftypes.h"
#include "fio.h"
#include "sdkconfig.h"

#ifdef __cplusplus
extern "C"
{
#endif

/***ft CAN REGISTER offset*/
#define FCAN_CTRL_OFFSET            0x00 /* Global control register */
#define FCAN_INTR_OFFSET            0x04 /* Interrupt register */
#define FCAN_ARB_RATE_CTRL_OFFSET   0x08 /* Arbitration rate control register */
#define FCAN_DAT_RATE_CTRL_OFFSET   0x0C /* Data rate control register */
#define FCAN_ACC_ID0_OFFSET         0x10 /* Acceptance identifier0 register */
#define FCAN_ACC_ID1_OFFSET         0x14 /* Acceptance identifier1 register */
#define FCAN_ACC_ID2_OFFSET         0x18 /* Acceptance identifier2 register */
#define FCAN_ACC_ID3_OFFSET         0x1C /* Acceptance identifier3 register */
#define FCAN_ACC_ID0_MASK_OFFSET    0x20 /* Acceptance identifier0 mask register */
#define FCAN_ACC_ID1_MASK_OFFSET    0x24 /* Acceptance identifier1 mask register */
#define FCAN_ACC_ID2_MASK_OFFSET    0x28 /* Acceptance identifier2 mask register */
#define FCAN_ACC_ID3_MASK_OFFSET    0x2C /* Acceptance identifier3 mask register */
#define FCAN_XFER_STS_OFFSET        0x30 /* Transfer status register */
#define FCAN_ERR_CNT_OFFSET         0x34 /* Error counter register */
#define FCAN_FIFO_CNT_OFFSET        0x38 /* FIFO counter register */
#define FCAN_DMA_CTRL_OFFSET        0x3C /* DMA request control register */
#define FCAN_XFER_EN_OFFSET         0x40 /* Transfer enable register */
#define FCAN_FRM_INFO_OFFSET        0x48 /* Frame valid number register */
#define FCAN_TX_FIFO_OFFSET         0x100/* TX FIFO shadow register */
#define FCAN_RX_FIFO_OFFSET         0x200/* RX FIFO shadow register */

/*----------------------------------------------------------------------------*/
/* CAN register bit masks - FCAN_<REG>_<BIT>_MASK                            */
/*----------------------------------------------------------------------------*/

/* FCAN_CTRL mask */
#define FCAN_CTRL_XFER_MASK     BIT(0)   /*Transfer enable*/
#define FCAN_CTRL_TXREQ_MASK    BIT(1)   /*Transmit request*/
#define FCAN_CTRL_AIME_MASK     BIT(2)   /*Acceptance identifier mask enable*/
#define FCAN_CTRL_RST_MASK      BIT(7)   /* Soft rest 1:reset and auto clear */
#define FCAN_CTRL_RFEIDF_MASK   BIT(8)   /* whether generates frame recv completion interrupt when filtering frames */
#define FCAN_CTRL_IRFEDT_MASK   BIT(9)   /* whether generates frame recv completion interrupt when sending frame */
#define FCAN_CTRL_IOF_MASK      BIT(10)  /* send overload frame */
#define FCAN_CTRL_FDCRC_MASK    BIT(11)  /* Stuff count, crc mode */

/* FCAN_INTR mask */
#define FCAN_INTR_BOIS_MASK     BIT(0)  /* Bus off interrupt status*/
#define FCAN_INTR_PWIS_MASK     BIT(1)  /* Passive warning interrupt status*/
#define FCAN_INTR_PEIS_MASK     BIT(2)  /* Passive error interrupt status*/
#define FCAN_INTR_RFIS_MASK     BIT(3)  /* RX FIFO full interrupt status*/
#define FCAN_INTR_TFIS_MASK     BIT(4)  /* TX FIFO empty interrupt status*/
#define FCAN_INTR_REIS_MASK     BIT(5)  /* RX frame end interrupt status*/
#define FCAN_INTR_TEIS_MASK     BIT(6)  /* TX frame end interrupt status*/
#define FCAN_INTR_EIS_MASK      BIT(7)  /* Error interrupt status*/
#define FCAN_INTR_BOIE_MASK     BIT(8)  /* Bus off interrupt enable*/
#define FCAN_INTR_PWIE_MASK     BIT(9)  /* Passive warning interrupt enable*/
#define FCAN_INTR_PEIE_MASK     BIT(10) /* Passive error interrupt enable*/
#define FCAN_INTR_RFIE_MASK     BIT(11) /* RX FIFO full interrupt enable*/
#define FCAN_INTR_TFIE_MASK     BIT(12) /* TX FIFO empty interrupt enable*/
#define FCAN_INTR_REIE_MASK     BIT(13) /* RX frame end interrupt enable*/
#define FCAN_INTR_TEIE_MASK     BIT(14) /* TX frame end interrupt enable*/
#define FCAN_INTR_EIE_MASK      BIT(15) /* Error interrupt enable*/
#define FCAN_INTR_BOIC_MASK     BIT(16) /* Bus off interrupt clear*/
#define FCAN_INTR_PWIC_MASK     BIT(17) /* Passive warning interrupt clear*/
#define FCAN_INTR_PEIC_MASK     BIT(18) /* Passive error interrupt clear*/
#define FCAN_INTR_RFIC_MASK     BIT(19) /* RX FIFO full interrupt clear*/
#define FCAN_INTR_TFIC_MASK     BIT(20) /* TX FIFO empty interrupt clear*/
#define FCAN_INTR_REIC_MASK     BIT(21) /* RX frame end interrupt clear*/
#define FCAN_INTR_TEIC_MASK     BIT(22) /* TX frame end interrupt clear*/
#define FCAN_INTR_EIC_MASK      BIT(23) /* Error interrupt clear*/
#define FCAN_INTR_BORIS_MASK    BIT(24)
#define FCAN_INTR_PWRIS_MASK    BIT(25)
#define FCAN_INTR_PERIS_MASK    BIT(26)
#define FCAN_INTR_RFRIS_MASK    BIT(27)
#define FCAN_INTR_TFRIS_MASK    BIT(28)
#define FCAN_INTR_RERIS_MASK    BIT(29)
#define FCAN_INTR_TERIS_MASK    BIT(30)
#define FCAN_INTR_ERIS_MASK     BIT(31)

/* FCAN_DAT_RATE_CTRL mask */

/* FCAN_ACC_ID(0-3)_MASK mask */
#define FCAN_ACC_IDN_MASK           GENMASK(28, 0)/*don’t care the matching */

#define FCAN_ACC_ID_REG_NUM         4

/* FCAN_XFER_STS mask */
#define FCAN_XFER_STS_XFERS_GET(x)     GET_REG32_BITS((x), 10, 10)
#define FCAN_XFER_STS_RS_GET(x)        GET_REG32_BITS((x), 9, 9)
#define FCAN_XFER_STS_TS_GET(x)        GET_REG32_BITS((x), 8, 8)
#define FCAN_XFER_STS_FIES_GET(x)      GET_REG32_BITS((x), 7, 3)
#define FCAN_XFER_STS_FRAS_GET(x)      GET_REG32_BITS((x), 2, 0)

/* FCAN_ERR_CNT_OFFSET mask */
#define FCAN_ERR_CNT_RFN_MASK       GENMASK(8, 0)    /*Receive error counter*/
#define FCAN_ERR_CNT_RFN_GET(x)     GET_REG32_BITS((x), 8, 0)
#define FCAN_ERR_CNT_RFN_SET(x)     SET_REG32_BITS((x), 8, 0)

#define FCAN_ERR_CNT_TFN_MASK       GENMASK(24, 16)    /*Transmit error counter*/
#define FCAN_ERR_CNT_TFN_GET(x)     GET_REG32_BITS((x), 24, 16)
#define FCAN_ERR_CNT_TFN_SET(x)     SET_REG32_BITS((x), 24, 16)

/* FCAN_FIFO_CNT_OFFSET mask */
#define FCAN_FIFO_CNT_RFN_MASK       GENMASK(6, 0)    /*Receive FIFO valid data number*/
#define FCAN_FIFO_CNT_RFN_GET(x)     GET_REG32_BITS((x), 6, 0)
#define FCAN_FIFO_CNT_RFN_SET(x)     SET_REG32_BITS((x), 6, 0)

#define FCAN_FIFO_CNT_TFN_MASK       GENMASK(6, 0)    /*Transmit FIFO valid data number*/
#define FCAN_FIFO_CNT_TFN_GET(x)     GET_REG32_BITS((x), 22, 16)
#define FCAN_FIFO_CNT_TFN_SET(x)     SET_REG32_BITS((x), 22, 16)

#define FCAN_IDR_ID1_SHIFT          21 /* Standard Message Identifier */
#define FCAN_IDR_SDLC_SHIFT         14
#define FCANFD_IDR_EDLC_SHIFT       24
#define FCAN_IDR_EDLC_SHIFT         26
#define FCAN_ACC_IDN_SHIFT          18 /*Standard ACC ID shift*/
#define FCANFD_IDR_GET_EDLC_SHIFT   12
#define FCANFD_IDR1_SDLC_SHIFT      11

/* can */
#define FCAN_IDR_ID2_GET(x)   GET_REG32_BITS((x), 18, 1)  /* Get extended message ident */
#define FCAN_IDR_ID2_SET(x)   SET_REG32_BITS((x), 18, 1)  /* Set extended message ident */
#define FCAN_IDR_ID1_GET(x)   GET_REG32_BITS((x), 31, 21)  /* Get standard msg identifier */
#define FCAN_IDR_ID1_SET(x)   SET_REG32_BITS((x), 31, 21)  /* Set standard msg identifier */
#define FCAN_IDR_IDE_MASK   BIT(19)     /* Identifier extension */
#define FCAN_IDR_SRR_MASK   BIT(20)  /* Substitute remote TXreq */
#define FCAN_IDR_RTR_MASK   BIT(0)  /* Extended frames remote TX request */
#define FCAN_IDR_PAD_MASK   GENMASK(13, 0)  /* Standard msg padding 1 */
#define FCAN_IDR_DLC_GET(x)   GET_REG32_BITS((x), 17, 14)  /* Standard msg dlc */
#define FCAN_IDR_EDLC_GET(x)  GET_REG32_BITS((x), 29, 26)  /* Extended msg dlc */

/* canfd */
#define FTCANFD_ID1_FDL_MASK    BIT(18)     /* CANFD Standard FDF */
#define FTCANFD_ID1_BRS_MASK    BIT(16)     /* CANFD Standard BRS */
#define FTCANFD_ID1_ESI_MASK    BIT(15)     /* CANFD Standard ESI */
#define FTCANFD_ID1_SDLC_GET(x)   GET_REG32_BITS((x),14, 11)  /* CANFD Standard msg dlc */
#define FTCANFD_IDR_PAD_MASK    GENMASK(10, 0)  /* CANFD Standard msg padding 1 */

#define FTCANFD_ID2_FDL_MASK    BIT(31)  /* CANFD Extended FDF */
#define FTCANFD_ID2_BRS_MASK    BIT(29)  /* CANFD Extended BRS */
#define FTCANFD_ID2_ESI_MASK    BIT(28)  /* CANFD Extended ESI */
#define FTCANFD_ID2_EDLC_GET(x)    GET_REG32_BITS((x), 27, 24)  /* CANFD Extended msg dlc */

#define FTCAN_INTR_EN (FTCAN_INTR_TEIE_MASK | FTCAN_INTR_REIE_MASK | FTCAN_INTR_RFIE_MASK)

/* Can timming */
#if defined(CONFIG_TARGET_F2000_4) || defined(CONFIG_TARGET_D2000)

    #define FCAN_ARB_TSEG1_MIN  1
    #define FCAN_ARB_TSEG1_MAX  16
    #define FCAN_ARB_TSEG2_MIN  1
    #define FCAN_ARB_TSEG2_MAX  8
    #define FCAN_ARB_SJW_MAX    4
    #define FCAN_ARB_BRP_MIN    1
    #define FCAN_ARB_BRP_MAX    512
    #define FCAN_ARB_BRP_INC    1

    #define FCAN_DATA_TSEG1_MIN 1
    #define FCAN_DATA_TSEG1_MAX 16
    #define FCAN_DATA_TSEG2_MIN 1
    #define FCAN_DATA_TSEG2_MAX 8
    #define FCAN_DATA_SJW_MAX   4
    #define FCAN_DATA_BRP_MIN   1
    #define FCAN_DATA_BRP_MAX   512
    #define FCAN_DATA_BRP_INC   1

#elif defined(CONFIG_TARGET_E2000) || defined(TARDIGRADE)

    #define FCAN_ARB_TSEG1_MIN  1
    #define FCAN_ARB_TSEG1_MAX  16
    #define FCAN_ARB_TSEG2_MIN  1
    #define FCAN_ARB_TSEG2_MAX  8
    #define FCAN_ARB_SJW_MAX    4
    #define FCAN_ARB_BRP_MIN    1
    #define FCAN_ARB_BRP_MAX    8192
    #define FCAN_ARB_BRP_INC    1

    #define FCAN_DATA_TSEG1_MIN 1
    #define FCAN_DATA_TSEG1_MAX 16
    #define FCAN_DATA_TSEG2_MIN 1
    #define FCAN_DATA_TSEG2_MAX 8
    #define FCAN_DATA_SJW_MAX   4
    #define FCAN_DATA_BRP_MIN   1
    #define FCAN_DATA_BRP_MAX   8192
    #define FCAN_DATA_BRP_INC   1

#endif


#define FCAN_FIFO_DEPTH     64

/**
* This macro reads the given register.
* @param    base_addr is the base address of the device.
* @param    reg_offset is the register offset to be read.
* @return   The 32-bit value of the register
* @note     None.
*****************************************************************************/
#define FCAN_READ_REG32(addr, reg_offset) FtIn32((addr) + (u32)(reg_offset))

/****************************************************************************/
/**
* This macro writes the given register.
* @param    base_addr is the base address of the device.
* @param    reg_offset is the register offset to be written.
* @param    data is the 32-bit value to write to the register.
* @return   None.
* @note     None.
*****************************************************************************/
#define FCAN_WRITE_REG32(addr, reg_offset, reg_value) FtOut32((addr) + (u32)reg_offset, (u32)reg_value)

#define FCAN_SETBIT(base_addr, reg_offset, data)      FtSetBit32((base_addr) + (u32)(reg_offset), (u32)(data))

#define FCAN_CLEARBIT(base_addr, reg_offset, data)     FtClearBit32((base_addr) + (u32)(reg_offset), (u32)(data))

#define FCAN_TX_FIFO_FULL(instance_p) (FCAN_FIFO_DEPTH == FCAN_FIFO_CNT_TFN_GET(FCAN_READ_REG32(instance_p->config.base_address, FCAN_FIFO_CNT_OFFSET)))

#define FCAN_RX_FIFO_EMPTY(instance_p) (0 == FCAN_FIFO_CNT_RFN_GET(FCAN_READ_REG32(instance_p->config.base_address, FCAN_FIFO_CNT_OFFSET)))


void FCanDump(uintptr base_addr);

#ifdef __cplusplus
}
#endif

#endif // !
