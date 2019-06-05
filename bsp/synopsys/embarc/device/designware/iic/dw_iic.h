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
 * \brief	designware iic driver header file
 * \ingroup	DEVICE_DW_IIC
 */

#ifndef _DW_IIC_H_
#define _DW_IIC_H_

#include "device/device_hal/inc/dev_iic.h"

#include "inc/arc/arc_exception.h"


/**
 * If this header file is included,
 * will indicate that this designware iic device
 * is used
 */
#define DEVICE_USE_DESIGNWARE_IIC

/**
 * \defgroup	DEVICE_DW_IIC_INFO	DesignWare IIC Related Information
 * \ingroup	DEVICE_DW_IIC
 * \brief	Defines some macros of DesignWare IIC need.
 * \details	macros like, iic number
 * @{
 */
#define DW_IIC_MASTER_SUPPORTED		(0x1)	/*!< Support Designware IIC Master Mode */
#define DW_IIC_SLAVE_SUPPORTED		(0x2)	/*!< Support Designware IIC Slave Mode */
/*!< Support Designware IIC Both Master and Slave Mode */
#define DW_IIC_BOTH_SUPPORTED		(DW_IIC_MASTER_SUPPORTED|DW_IIC_SLAVE_SUPPORTED)
/** @} */

/**
 * \defgroup	DEVICE_DW_IIC_REGSTRUCT		DesignWare IIC Register Structure
 * \ingroup	DEVICE_DW_IIC
 * \brief	contains definitions of DesignWare IIC register structure.
 * \details	detailed description of DesignWare IIC register information
 * @{
 */
/**
 * \brief	DesignWare IIC register structure
 * \details	Detailed struct description of DesignWare IIC
 *	block register information, implementation of dev_iic_info::iic_regs
 */
typedef volatile struct dw_iic_reg {
	uint32_t IC_CON;		/*!< (0x00) : IIC control */
	uint32_t IC_TAR;		/*!< (0x04) : IIC target address */
	uint32_t IC_SAR;		/*!< (0x08) : IIC slave address */
	uint32_t IC_HS_MADDR;		/*!< (0x0c) : IIC HS Master Mode Code address */
	uint32_t IC_DATA_CMD;		/*!< (0x10) : IIC Rx/Tx Data Buffer and Command */
	uint32_t IC_SS_SCL_HCNT;	/*!< (0x14) : Standard Speed IIC clock SCL High Count */
	uint32_t IC_SS_SCL_LCNT;	/*!< (0x18) : Standard Speed IIC clock SCL Low Count */
	uint32_t IC_FS_SCL_HCNT;	/*!< (0x1c) : Fast Speed IIC clock SCL Low Count */
	uint32_t IC_FS_SCL_LCNT;	/*!< (0x20) : Fast Speed IIC clock SCL Low Count */
	uint32_t IC_HS_SCL_HCNT;	/*!< (0x24) : High Speed IIC clock SCL Low Count */
	uint32_t IC_HS_SCL_LCNT;	/*!< (0x28) : High Speed IIC clock SCL Low Count */
	uint32_t IC_INTR_STAT;		/*!< (0x2c) : IIC Interrupt Status */
	uint32_t IC_INTR_MASK;		/*!< (0x30) : IIC Interrupt Mask */
	uint32_t IC_RAW_INTR_STAT;	/*!< (0x34) : IIC Raw Interrupt Status */
	uint32_t IC_RX_TL;		/*!< (0x38) : IIC Receive FIFO Threshold */
	uint32_t IC_TX_TL;		/*!< (0x3c) : IIC Transmit FIFO Threshold */
	uint32_t IC_CLR_INTR;		/*!< (0x40) : Clear combined and Individual Interrupts */
	uint32_t IC_CLR_RX_UNDER;	/*!< (0x44) : Clear RX_UNDER Interrupt */
	uint32_t IC_CLR_RX_OVER;	/*!< (0x48) : Clear RX_OVER Interrupt */
	uint32_t IC_CLR_TX_OVER;	/*!< (0x4c) : Clear TX_OVER Interrupt */
	uint32_t IC_CLR_RD_REQ;		/*!< (0x50) : Clear RQ_REQ Interrupt */
	uint32_t IC_CLR_TX_ABRT;	/*!< (0x54) : Clear TX_ABRT Interrupt */
	uint32_t IC_CLR_RX_DONE;	/*!< (0x58) : Clear RX_DONE Interrupt */
	uint32_t IC_CLR_ACTIVITY;	/*!< (0x5c) : Clear ACTIVITY Interrupt */
	uint32_t IC_CLR_STOP_DET;	/*!< (0x60) : Clear STOP_DET Interrupt */
	uint32_t IC_CLR_START_DET;	/*!< (0x64) : Clear START_DET Interrupt */
	uint32_t IC_CLR_GEN_CALL;	/*!< (0x68) : Clear GEN_CALL Interrupt */
	uint32_t IC_ENABLE;		/*!< (0x6c) : IIC Enable */
	uint32_t IC_STATUS;		/*!< (0x70) : IIC Status */
	uint32_t IC_TXFLR;		/*!< (0x74) : Transmit FIFO Level Register */
	uint32_t IC_RXFLR;		/*!< (0x78) : Receive FIFO Level Register */
	uint32_t IC_SDA_HOLD;		/*!< (0x7c) : SDA Hold Time Length Reg */
	uint32_t IC_TX_ABRT_SOURCE;	/*!< (0x80) : IIC Transmit Abort Status Reg */
	uint32_t IC_SLV_DATA_NACK_ONLY;	/*!< (0x84) : Generate SLV_DATA_NACK Register */
	uint32_t IC_DMA_CR;		/*!< (0x88) : DMA Control Register */
	uint32_t IC_DMA_TDLR;		/*!< (0x8c) : DMA Transmit Data Level */
	uint32_t IC_DMA_RDLR;		/*!< (0x90) : DMA Receive Data Level */
	uint32_t IC_SDA_SETUP;		/*!< (0x94) : SDA Setup Register */
	uint32_t IC_ACK_GENERAL_CALL;	/*!< (0x98) : ACK General Call Register */
	uint32_t IC_ENABLE_STATUS;	/*!< (0x9c) : Enable Status Register */
	uint32_t IC_FS_SPKLEN;		/*!< (0xa0) : ISS and FS spike suppression limit */
	uint32_t IC_HS_SPKLEN;		/*!< (0xa4) : HS spike suppression limit */
	uint32_t RESERVED[19];		/*!< (0xa8) : Reserved */
	uint32_t IC_COMP_PARAM_1;	/*!< (0xf4) : Component Parameter Register */
	uint32_t IC_COMP_VERSION;	/*!< (0xf8) : Component Version ID Reg */
	uint32_t IC_COMP_TYPE;		/*!< (0xfc) : Component Type Reg */
} DW_IIC_REG, *DW_IIC_REG_PTR;
/** @} */

/** Spike Suppression Limit Configurations */
typedef struct dw_iic_spklen {
	uint32_t fs_spklen;	/*!< value for IC_FS_SPKLEN, Tsp for fast mode is 50ns */
	uint32_t hs_spklen;	/*!< value for IC_HS_SPKLEN, Tsp for high-speed mode is 10ns */
} DW_IIC_SPKLEN, *DW_IIC_SPKLEN_PTR;

/** IIC Clock SCL High and Low Count Configurations for Different Speed */
typedef struct dw_iic_scl_cnt {
	uint32_t ss_scl_hcnt;	/*!< value for IC_SS_SCL_HCNT */
	uint32_t ss_scl_lcnt;	/*!< value for IC_SS_SCL_LCNT */
	uint32_t fs_scl_hcnt;	/*!< value for IC_FS_SCL_HCNT */
	uint32_t fs_scl_lcnt;	/*!< value for IC_FS_SCL_LCNT */
	uint32_t hs_scl_hcnt;	/*!< value for IC_HS_SCL_HCNT */
	uint32_t hs_scl_lcnt;	/*!< value for IC_HS_SCL_LCNT */
} DW_IIC_SCL_CNT, *DW_IIC_SCL_CNT_PTR;

#define DW_IIC_GINT_DISABLED		(0)		/*!< designware interrupt disabled for control iic irq/fiq */
#define DW_IIC_GINT_ENABLE		(1<<0)		/*!< designware interrupt enabled for control iic irq/fiq */
#define DW_IIC_TXINT_ENABLE		(1<<1)		/*!< designware interrupt enabled for control transmit process */
#define DW_IIC_RXINT_ENABLE		(1<<2)		/*!< designware interrupt enabled for control transmit process */

typedef struct dw_iic_buffer {
	DEV_BUFFER *buf;
	uint32_t ofs;
	uint32_t len;
} DW_IIC_BUFFER, *DW_IIC_BUFFER_PTR;

/**
 * \brief	DesignWare IIC control structure definition
 * \details	implement of dev_iic_info::iic_ctrl
 */
typedef struct dw_iic_ctrl {
	DW_IIC_REG *dw_iic_regs;	/*!< iic device registers */
	/* Variables which should be set during object implementation */
	uint32_t support_modes;		/*!< supported iic modes */
	uint32_t tx_fifo_len;		/*!< transmit fifo length */
	uint32_t rx_fifo_len;		/*!< receive fifo length */
	uint32_t iic_master_code;	/*!< value for IC_HS_MADDR */
	uint32_t retry_cnt;		/*!< retry count for TX or RX */
	uint32_t intno;			/*!< iic interrupt vector number */
	INT_HANDLER dw_iic_int_handler;	/*!< iic interrupt handler */
	DW_IIC_SPKLEN iic_spklen;	/*!< iic spike suppression length settings */
	DW_IIC_SCL_CNT iic_scl_cnt;	/*!< iic scl count settings */
	/* Variables which always change during iic operation */
	uint32_t int_status;		/*!< iic interrupt status */
	uint32_t iic_tx_over;		/*!< iic tx overflow count */
	uint32_t iic_rx_over;		/*!< iic rx overflow count */
	DW_IIC_BUFFER dw_iic_rxbuf;	/*!< iic read buffer for receive data */
} DW_IIC_CTRL, *DW_IIC_CTRL_PTR;

/*!< One possible value for \ref dw_iic_ctrl::retry_cnt */
#define DW_IIC_MAX_RETRY_COUNT		(100000)

#if DW_IIC_USE_IC_CLK_MHZ == 100 /*!< 100MHz */
/*!< One possible value for \ref dw_iic_ctrl::iic_spklen */
static const DW_IIC_SPKLEN dw_iic_spklen_const = {5, 1};

/*!< One possible value for \ref dw_iic_ctrl::iic_spklen */
#if DW_IIC_USE_HS_BUS_LOADING_100PF
static const DW_IIC_SCL_CNT dw_iic_sclcnt_const = {0x0190, 0x01d6, 0x003c, 0x0082, 0x6, 0x10};
#else
static const DW_IIC_SCL_CNT dw_iic_sclcnt_const = {0x0190, 0x01d6, 0x003c, 0x0082, 0xc, 0x20};
#endif

#elif DW_IIC_USE_IC_CLK_MHZ == 50 /* 50MHz */
/*!< One possible value for \ref dw_iic_ctrl::iic_spklen */
static const DW_IIC_SPKLEN dw_iic_spklen_const = {5, 1};

/*!< One possible value for \ref dw_iic_ctrl::iic_spklen */
#if DW_IIC_USE_HS_BUS_LOADING_100PF
static const DW_IIC_SCL_CNT dw_iic_sclcnt_const = {0x00c8, 0x00eb, 0x001e, 0x0041, 0x6, 0x8};
#else
static const DW_IIC_SCL_CNT dw_iic_sclcnt_const = {0x00c8, 0x00eb, 0x001e, 0x0041, 0x6, 0x10};
#endif

#else /* Default 100MHz */
/*!< One possible value for \ref dw_iic_ctrl::iic_spklen */
static const DW_IIC_SPKLEN dw_iic_spklen_const = {5, 1};

/*!< One possible value for \ref dw_iic_ctrl::iic_spklen */
#if DW_IIC_USE_HS_BUS_LOADING_100PF
static const DW_IIC_SCL_CNT dw_iic_sclcnt_const = {0x0190, 0x01d6, 0x003c, 0x0082, 0x6, 0x10};
#else
static const DW_IIC_SCL_CNT dw_iic_sclcnt_const = {0x0190, 0x01d6, 0x003c, 0x0082, 0xc, 0x20};
#endif

#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup	DEVICE_DW_IIC_FUNCDLR	DesignWare IIC Function Declaration
 * \ingroup	DEVICE_DW_IIC
 * \brief	Contains declarations of designware iic functions.
 * \details	This are only used in iic object implementation source file
 * @{
 */
extern int32_t dw_iic_open (DEV_IIC *iic_obj, uint32_t mode, uint32_t param);
extern int32_t dw_iic_close (DEV_IIC *iic_obj);
extern int32_t dw_iic_control (DEV_IIC *iic_obj, uint32_t ctrl_cmd, void *param);
extern int32_t dw_iic_write (DEV_IIC *iic_obj, const void *data, uint32_t len);
extern int32_t dw_iic_read (DEV_IIC *iic_obj, void *data, uint32_t len);
extern void dw_iic_isr(DEV_IIC *iic_obj, void *ptr);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* _DW_IIC_H_ */
