/** @file if_gspi.h
 *  @brief This file contains MSU registers definition
 * 
 *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2006
 */
/********************************************************
Change log:
	09/26/05: Add Doxygen format comments
	
********************************************************/

#ifndef __GSPIREG_H_
#define __GSPIREG_H_

#include "..\wlan\include.h"	 //changed by dennis
/* GSPI Registers Offset. All the resgisters are at DWORD boundary */
#define DEVICEID_CTRL_REG		0x00
#define CHIPREV_REG			0x02

#define IO_READBASE_REG			0x04
#define IO_WRITEBASE_REG		0x08
#define IO_RDWRPORT_REG			0x0C

#define CMD_READBASE_REG		0x10
#define CMD_WRITEBASE_REG		0x14
#define CMD_RDWRPORT_REG		0x18

#define DATA_READBASE_REG		0x1C
#define DATA_WRITEBASE_REG		0x20
#define DATA_RDWRPORT_REG		0x24

#define SCRATCH_1_REG			0x28
#define SCRATCH_2_REG			0x2C
#define SCRATCH_3_REG			0x30
#define SCRATCH_4_REG			0x34

#define TX_FRAME_SEQ_NUM_REG		0x38
#define TX_FRAME_STATUS_REG		0x3C

#define HOST_INT_CTRL_REG		0x40

#define CARD_INT_CAUSE_REG		0x44
#define CARD_INT_STATUS_REG		0x48
#define CARD_INT_EVENT_MASK_REG		0x4C
#define CARD_INT_STATUS_MASK_REG	0x50
#define CARD_INT_RESET_SELECT_REG	0x54

#define HOST_INT_CAUSE_REG		0x58
#define HOST_INT_STATUS_REG		0x5C
#define HOST_INT_EVENT_MASK_REG		0x60
#define HOST_INT_STATUS_MASK_REG	0x64
#define HOST_INT_RESET_SELECT_REG	0x68

#define DELAY_READ_REG			0x6C
#define SPU_BUS_MODE_REG		0x70
#define BUS_MODE_16_NO_DELAY		0x02

/* Bit definition for CARD_INT_CAUSE (Card Interrupt Cause) */
#define CIC_TxDnLdOvr			B_BIT_0
#define CIC_RxUpLdOvr			B_BIT_1
#define CIC_CmdDnLdOvr			B_BIT_2
#define CIC_HostEvent			B_BIT_3
#define CIC_CmdUpLdOvr			B_BIT_4
#define CIC_PwrDown			B_BIT_5

/* Bit definition for HOST_INT_STATUS (Host Interrupt Status) */
#define GHIS_TxDnLdRdy			B_BIT_0
#define GHIS_RxUpLdRdy			B_BIT_1
#define GHIS_CmdDnLdRdy			B_BIT_2
#define GHIS_CardEvent			B_BIT_3
#define GHIS_CmdUpLdRdy			B_BIT_4
#define GHIS_IOWrFifoOvrflow		B_BIT_5
#define GHIS_IORdFifoUndrflow		B_BIT_6
#define GHIS_DATAWrFifoOvrflow		B_BIT_7
#define GHIS_DATARdFifoUndrflow		B_BIT_8
#define GHIS_CMDWrFifoOvrflow		B_BIT_9
#define GHIS_CMDRdFifoUndrflow		B_BIT_10
/* Bit definition for HOST_INT_STATUS_MASK_REG (Host Interrupt Status Mask) */
#define HISM_TxDnLdRdy			B_BIT_0
#define HISM_RxUpLdRdy			B_BIT_1
#define HISM_CmdDnLdRdy			B_BIT_2
#define HISM_CardEvent			B_BIT_3
#define HISM_CmdUpLdRdy			B_BIT_4
#define HISM_IOWrFifoOvrflow		B_BIT_5
#define HISM_IORdFifoUndrflow		B_BIT_6
#define HISM_DATAWrFifoOvrflow		B_BIT_7
#define HISM_DATARdFifoUndrflow		B_BIT_8
#define HISM_CMDWrFifoOvrflow		B_BIT_9
#define HISM_CMDRdFifoUndrflow		B_BIT_10

/* Bit definition for HOST_INT_CTRL_REG (Host Interrupt Control) */
#define HIC_WakeUp			B_BIT_0
#define HIC_WlanRdy			B_BIT_1
#define HIC_TxDnldAuto			B_BIT_5
#define HIC_RxUpldAuto			B_BIT_6
#define HIC_CmdDnldAuto			B_BIT_7
#define HIC_CmdUpldAuto			B_BIT_8

/* Bit definition for SPU_BUS_MODE_REG (SPU Bus mode register)*/
#define SBM_DataFormat_2		B_BIT_2

/* Value to check once the firmware is downloaded */
#define FIRMWARE_DNLD_OK 		0x88888888

/* Value to write to indicate end of firmware dnld */
#define FIRMWARE_DNLD_END 		0x0000
#define FIRMWARE_DNLD_PCKCNT		64


#endif /* __GSPIREG_H_ */
