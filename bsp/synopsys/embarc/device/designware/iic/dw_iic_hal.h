/* ------------------------------------------
 * Copyright (c) 2017, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

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
 *
 * \version 2017.03
 * \date 2014-06-30
 * \author Huaqi Fang(Huaqi.Fang@synopsys.com)
--------------------------------------------- */

/**
 * \file
 * \ingroup	DEVICE_DW_IIC
 * \brief	DesignWare IIC driver hardware description related header file
 * \details	detailed hardware related definitions of DesignWare IIC driver
 */

#ifndef _DEVICE_DW_IIC_HAL_H_
#define _DEVICE_DW_IIC_HAL_H_

#include "device/designware/iic/dw_iic_hal_cfg.h"

/** Enable Designware IIC */
#define DW_IIC_ENABLE			(1)
/** Disable Designware IIC */
#define DW_IIC_DISABLE			(0)

/** Stop Condition issue after this byte */
#define IC_DATA_CMD_STOP		(1 << 9)
/** Restart Condition issue after this byte */
#define IC_DATA_CMD_RESTART		(1 << 10)
/** No Restart or stop condition after this byte */
#define IC_DATA_CMD_NONE		(0)

/** Perform a write request */
#define IC_DATA_CMD_WRITE_REQ		(0)
/** Perform a read request */
#define IC_DATA_CMD_READ_REQ		(1 << 8)

/** Fields of IC_CON register */
/* DW_APB I2C IP Config Dependencies. */
#if DW_IIC_ALLOW_RESTART
#define IC_CON_RESTART_EN		(1 << 5)
#else
#define IC_CON_RESTART_EN		(0x00)
#endif

/* Master Addressing Mode Config */
#if DW_IIC_MST_10_BIT_ADDR_SUPPORT
#define MST_10_BIT_ADDR_MODE		(1 << 4)
#define IC_10BITADDR_MASTER		(1 << 12)
#else
#define MST_10_BIT_ADDR_MODE		(0x00)
#define IC_10BITADDR_MASTER		(0x00)
#endif

/* Slave Addressing Mode Config */
#if DW_IIC_SLV_10_BIT_ADDR_SUPPORT
#define SLV_10_BIT_ADDR_MODE		(1 << 3)
#else
#define SLV_10_BIT_ADDR_MODE		(0x00)
#endif

#if DW_IIC_SPECIAL_START_BYTE
#define IC_TAR_SPECIAL			(1 << 11)
#define IC_TAR_GC_OR_START		(1 << 10)
#else
#define IC_TAR_SPECIAL			(0x00)
#define IC_TAR_GC_OR_START		(0x00)
#endif

/** 7bit IIC address mask for target address register */
#define IC_TAR_7BIT_ADDR_MASK		(0x7F)
/** 7bit IIC address mask for slave address register */
#define IC_SAR_7BIT_ADDR_MASK		(0x7F)
/** 10bit IIC address mask for target address register */
#define IC_TAR_10BIT_ADDR_MASK		(0x3FF)
/** 10bit IIC address mask for slave address register */
#define IC_SAR_10BIT_ADDR_MASK		(0x3FF)

/** Speed modes of IC_CON */
#define IC_CON_SPEED_MASK		(0x6)
#define IC_CON_SPEED_STANDARD		(0x2)
#define IC_CON_SPEED_FAST		(0x4)
#define IC_CON_SPEED_HIGH		(0x6)
/** Working mode of IC_CON */
#define IC_CON_MST_SLV_MODE_MASK	(0x41)
#define IC_CON_ENA_MASTER_MODE		(0x41)
#define IC_CON_ENA_SLAVE_MODE		(0)

/* IIC interrupt control */
#define IC_INT_DISABLE_ALL		(0x0)
#define IC_INT_ENABLE_ALL		(0x7FF)
/* Interrupt Register Fields */
#define IC_INTR_STAT_GEN_CALL		(1 << 11)
#define IC_INTR_STAT_START_DET		(1 << 10)
#define IC_INTR_STAT_STOP_DET		(1 << 9)
#define IC_INTR_STAT_ACTIVITY		(1 << 8)
#define IC_INTR_STAT_RX_DONE		(1 << 7)
#define IC_INTR_STAT_TX_ABRT		(1 << 6)
#define IC_INTR_STAT_RD_REQ		(1 << 5)
#define IC_INTR_STAT_TX_EMPTY		(1 << 4)
#define IC_INTR_STAT_TX_OVER		(1 << 3)
#define IC_INTR_STAT_RX_FULL		(1 << 2)
#define IC_INTR_STAT_RX_OVER		(1 << 1)
#define IC_INTR_STAT_RX_UNDER		(1 << 0)

/* Interrupt enable mask as master */
#define IC_INT_MST_TX_ENABLE		(IC_INTR_STAT_TX_EMPTY|IC_INTR_STAT_TX_OVER|IC_INTR_STAT_TX_ABRT)
#define IC_INT_MST_RX_ENABLE		(IC_INTR_STAT_TX_EMPTY|IC_INTR_STAT_RX_FULL|IC_INTR_STAT_RX_OVER|IC_INTR_STAT_RX_UNDER|IC_INTR_STAT_TX_ABRT)

/* Interrupt enable mask as master */
#define IC_INT_SLV_COMMON_ENABLE	(IC_INTR_STAT_START_DET|IC_INTR_STAT_STOP_DET)
#define IC_INT_SLV_TX_ENABLE		(IC_INTR_STAT_RD_REQ|IC_INTR_STAT_TX_ABRT)
#define IC_INT_SLV_RX_ENABLE		(IC_INTR_STAT_RX_FULL|IC_INTR_STAT_RX_OVER|IC_INTR_STAT_RX_UNDER)

/* IC_ENABLE_STATUS Bits */
#define IC_ENABLE_STATUS_IC_EN		(1 << 0)
#define IC_ENABLE_STATUS_SLV_DIS	(1 << 1)
#define IC_ENABLE_STATUS_SLV_RX_LOST	(1 << 2)

/* IIC TX & RX threshold settings */
#define IIC_TX_THRESHOLD		(0)
#define IIC_RX_THRESHOLD		(0)

/* DW_APB IIC (DW_IC_STATUS) Status Register Fields. */
#define IC_STATUS_ACTIVITY		(0x01)
#define IC_STATUS_TFNF			(0x02) /* (1 << 1) */
#define IC_STATUS_TFE			(0x04) /* (1 << 2) */
#define IC_STATUS_RFNE			(0x08) /* (1 << 3) */
#define IC_STATUS_RFF			(0x10) /* (1 << 4) */
#define IC_STATUS_MASTER_ACT		(0x20) /* (1 << 5) */
#define IC_STATUS_SLAVE_ACT		(0x40) /* (1 << 6) */

/* IC_TX_ABRT_SOURCE Register Bit Fields */
#define IC_TX_ABRT_7B_ADDR_NOACK	(1 << 0)
#define IC_TX_ABRT_10ADDR1_NOACK	(1 << 1)
#define IC_TX_ABRT_10ADDR2_NOACK	(1 << 2)
#define IC_TX_ABRT_TXDATA_NOACK		(1 << 3)
#define IC_TX_ABRT_GCALL_NOACK		(1 << 4)
#define IC_TX_ABRT_GCALL_READ		(1 << 5)
#define IC_TX_ABRT_HS_ACKDET		(1 << 6)
#define IC_TX_ABRT_SBYTE_ACKDET		(1 << 7)
#define IC_TX_ABRT_HS_NORSTRT		(1 << 8)
#define IC_TX_ABRT_SBYTE_NORSTRT	(1 << 9)
#define IC_TX_ABRT_10B_RD_NORSTRT	(1 << 10)
#define IC_TX_ABRT_MASTER_DIS		(1 << 11)
#define IC_TX_ABRT_ARB_LOST		(1 << 12)
#define IC_TX_ABRT_SLVFLUSH_TXFIFO	(1 << 13)
#define IC_TX_ABRT_SLV_ARBLOST		(1 << 14)
#define IC_TX_ABRT_SLVRD_INTX		(1 << 15)

/* Combined bits for iic abort source as master */
#define IIC_MST_ABRT_ADDR_NOACK		(IC_TX_ABRT_7B_ADDR_NOACK|IC_TX_ABRT_10ADDR1_NOACK|IC_TX_ABRT_10ADDR1_NOACK)
#define IIC_MST_ABRT_LOST_BUS		(IC_TX_ABRT_ARB_LOST)
#define IIC_MST_ABRT_DATA_NOACK		(IC_TX_ABRT_TXDATA_NOACK)

/* Combined bits for iic abort source as slave */
#define IIC_SLV_ABRT_LOST_BUS		(IC_TX_ABRT_ARB_LOST|IC_TX_ABRT_SLV_ARBLOST)

/** @} */

#endif /* _DEVICE_DW_IIC_HAL_H_ */
