/*""FILE COMMENT""*******************************************************
* System Name	: I²C API for RX62Nxx
* File Name		: r_pdl_iic.h
* Version		: 1.02
* Contents		: I²C API header
* Customer		:
* Model			:
* Order			:
* CPU			: RX
* Compiler		: RXC
* OS			: Nothing
* Programmer	:
* Note			:
************************************************************************
* Copyright, 2011. Renesas Electronics Corporation
* and Renesas Solutions Corporation
************************************************************************
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FILE COMMENT END""**************************************************/

#ifndef R_PDL_IIC_H
#define R_PDL_IIC_H

#include "r_pdl_common_defs_RX62Nxx.h"

/* Function prototypes */
bool R_IIC_Create(
	uint8_t,
	uint32_t,
	uint32_t,
	uint16_t,
	uint16_t,
	uint16_t,
	uint32_t,
	uint32_t
);
bool R_IIC_Destroy(
	uint8_t
);
bool R_IIC_MasterSend(
	uint8_t,
	uint16_t,
	uint16_t,
	uint8_t *,
	uint16_t,
	void *,
	uint8_t
);
bool R_IIC_MasterReceive(
	uint8_t,
	uint16_t,
	uint16_t,
	uint8_t *,
	uint16_t,
	void *,
	uint8_t
);
bool R_IIC_MasterReceiveLast(
	uint8_t,
	uint8_t *
);
bool R_IIC_SlaveMonitor(
	uint8_t,
	uint16_t,
	uint8_t *,
	uint16_t,
	void *,
	uint8_t
);
bool R_IIC_SlaveSend(
	uint8_t,
	uint8_t *,
	uint16_t
);
bool R_IIC_Control(
	uint8_t,
	uint8_t
);
bool R_IIC_GetStatus(
	uint8_t,
	uint32_t *,
	uint16_t *,
	uint16_t *
);

/* Bus mode */
#define PDL_IIC_MODE_IIC				0x00000001ul
#define PDL_IIC_MODE_IIC_FMP			0x00000002ul
#define PDL_IIC_MODE_SMBUS				0x00000004ul

/* Internal reference clock */
#define PDL_IIC_INT_PCLK_DIV_1			0x00000008ul
#define PDL_IIC_INT_PCLK_DIV_2			0x00000010ul
#define PDL_IIC_INT_PCLK_DIV_4			0x00000020ul
#define PDL_IIC_INT_PCLK_DIV_8			0x00000040ul
#define PDL_IIC_INT_PCLK_DIV_16			0x00000080ul
#define PDL_IIC_INT_PCLK_DIV_32			0x00000100ul
#define PDL_IIC_INT_PCLK_DIV_64			0x00000200ul
#define PDL_IIC_INT_PCLK_DIV_128		0x00000400ul

/* Timeout detection */
#define PDL_IIC_TIMEOUT_DISABLE			0x00000800ul
#define PDL_IIC_TIMEOUT_LOW				0x00001000ul
#define PDL_IIC_TIMEOUT_HIGH			0x00002000ul
#define PDL_IIC_TIMEOUT_BOTH			0x00004000ul

/* Timeout mode */
#define PDL_IIC_TIMEOUT_LONG			0x00008000ul
#define PDL_IIC_TIMEOUT_SHORT			0x00010000ul

/* SDA output delay count */
#define PDL_IIC_SDA_DELAY_0				0x00020000ul
#define PDL_IIC_SDA_DELAY_1				0x00040000ul
#define PDL_IIC_SDA_DELAY_2				0x00080000ul
#define PDL_IIC_SDA_DELAY_3				0x00100000ul
#define PDL_IIC_SDA_DELAY_4				0x00200000ul
#define PDL_IIC_SDA_DELAY_5				0x00400000ul
#define PDL_IIC_SDA_DELAY_6				0x00800000ul
#define PDL_IIC_SDA_DELAY_7				0x01000000ul

/* SDA output delay clock source */
#define PDL_IIC_SDA_DELAY_DIV_1			0x02000000ul
#define PDL_IIC_SDA_DELAY_DIV_2			0x04000000ul

/* Noise filter control */
#define PDL_IIC_NF_DISABLE				0x08000000ul
#define PDL_IIC_NF_1					0x10000000ul
#define PDL_IIC_NF_2					0x20000000ul
#define PDL_IIC_NF_3					0x40000000ul
#define PDL_IIC_NF_4					0x80000000ul

/* NACK Transmission Arbitration Lost Detection control */
#define PDL_IIC_NTALD_DISABLE			0x00000001ul
#define PDL_IIC_NTALD_ENABLE			0x00000002ul

/* Slave Arbitration Lost Detection control */
#define PDL_IIC_SALD_DISABLE 			0x00000004ul
#define PDL_IIC_SALD_ENABLE				0x00000008ul

/* Slave address detection control */
#define PDL_IIC_SLAVE_0_DISABLE			0x00000010ul
#define PDL_IIC_SLAVE_0_ENABLE_7 		0x00000020ul
#define PDL_IIC_SLAVE_0_ENABLE_10		0x00000040ul
#define PDL_IIC_SLAVE_1_DISABLE			0x00000080ul
#define PDL_IIC_SLAVE_1_ENABLE_7		0x00000100ul
#define PDL_IIC_SLAVE_1_ENABLE_10		0x00000200ul
#define PDL_IIC_SLAVE_2_DISABLE			0x00000400ul
#define PDL_IIC_SLAVE_2_ENABLE_7		0x00000800ul
#define PDL_IIC_SLAVE_2_ENABLE_10		0x00001000ul
#define PDL_IIC_SLAVE_GCA_DISABLE 		0x00002000ul
#define PDL_IIC_SLAVE_GCA_ENABLE 		0x00004000ul

/* Device-ID detection control */
#define PDL_IIC_DEVICE_ID_DISABLE		0x00008000ul
#define PDL_IIC_DEVICE_ID_ENABLE		0x00010000ul

/* Host Address detection control */
#define PDL_IIC_HOST_ADDRESS_DISABLE	0x00020000ul
#define PDL_IIC_HOST_ADDRESS_ENABLE		0x00040000ul

/* Start / Repeated Start condition control */
#define PDL_IIC_START_ENABLE				0x0001u
#define PDL_IIC_START_DISABLE				0x0002u

/* Stop condition control */
#define PDL_IIC_STOP_ENABLE					0x0004u
#define PDL_IIC_STOP_DISABLE				0x0008u

/* Master DMAC / DTC trigger control */
#define PDL_IIC_DMAC_DTC_TRIGGER_DISABLE	0x0010u
#define PDL_IIC_DMAC_TRIGGER_ENABLE			0x0020u
#define PDL_IIC_DTC_TRIGGER_ENABLE			0x0040u

/* Slave DMAC / DTC trigger control */
#define PDL_IIC_RX_DMAC_DTC_TRIGGER_DISABLE	0x0080u
#define PDL_IIC_RX_DMAC_TRIGGER_ENABLE		0x0100u
#define PDL_IIC_RX_DTC_TRIGGER_ENABLE		0x0200u
#define PDL_IIC_TX_DMAC_DTC_TRIGGER_DISABLE	0x0400u
#define PDL_IIC_TX_DMAC_TRIGGER_ENABLE		0x0800u
#define PDL_IIC_TX_DTC_TRIGGER_ENABLE		0x1000u

/* Stop generation */
#define PDL_IIC_STOP		0x01u

/* NACK generation */
#define PDL_IIC_NACK		0x02u

/* Pin control */
#define PDL_IIC_SDA_LOW		0x04u
#define PDL_IIC_SDA_HI_Z	0x08u
#define PDL_IIC_SCL_LOW		0x10u
#define PDL_IIC_SCL_HI_Z	0x20u

/* Extra clock cycle generation */
#define PDL_IIC_CYCLE_SCL	0x40u

/* Reset control */
#define PDL_IIC_RESET		0x80u

#endif
/* End of file */
