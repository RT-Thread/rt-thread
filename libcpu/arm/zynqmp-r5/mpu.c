/******************************************************************************
* Copyright (c) 2014 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
* @file mpu.c
*
* This file contains initial configuration of the MPU.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- ---------------------------------------------------
* 5.00 	pkp  02/20/14 First release
* 5.04	pkp  12/18/15 Updated MPU initialization as per the proper address map
* 6.00  pkp  06/27/16 moving the Init_MPU code to .boot section since it is a
*                     part of processor boot process
* 6.2   mus  01/27/17 Updated to support IAR compiler
* 7.1   mus  09/11/19 Added warning message if DDR size is not in power of 2.
*                     Fix for CR#1038577.
* 7.2   asa  04/08/20 Fix warning in the function Init_MPU.
* </pre>
*
* @note
*
* None.
*
******************************************************************************/
/***************************** Include Files *********************************/
#include <rtthread.h>
#include "zynqmp-r5.h"
#include "xreg_cortexr5.h"
#include "xpseudo_asm_gcc.h"

/***************** Macros (Inline Functions) Definitions *********************/

/**************************** Type Definitions *******************************/
typedef rt_int32_t s32;
typedef rt_uint64_t u64;
typedef rt_uint32_t u32;
/************************** Constant Definitions *****************************/

/************************** Variable Definitions *****************************/

static const struct {
	u64 size;
	unsigned int encoding;
}region_size[] = {
	{ 0x20, REGION_32B },
	{ 0x40, REGION_64B },
	{ 0x80, REGION_128B },
	{ 0x100, REGION_256B },
	{ 0x200, REGION_512B },
	{ 0x400, REGION_1K },
	{ 0x800, REGION_2K },
	{ 0x1000, REGION_4K },
	{ 0x2000, REGION_8K },
	{ 0x4000, REGION_16K },
	{ 0x8000, REGION_32K },
	{ 0x10000, REGION_64K },
	{ 0x20000, REGION_128K },
	{ 0x40000, REGION_256K },
	{ 0x80000, REGION_512K },
	{ 0x100000, REGION_1M },
	{ 0x200000, REGION_2M },
	{ 0x400000, REGION_4M },
	{ 0x800000, REGION_8M },
	{ 0x1000000, REGION_16M },
	{ 0x2000000, REGION_32M },
	{ 0x4000000, REGION_64M },
	{ 0x8000000, REGION_128M },
	{ 0x10000000, REGION_256M },
	{ 0x20000000, REGION_512M },
	{ 0x40000000, REGION_1G },
	{ 0x80000000, REGION_2G },
	{ 0x100000000, REGION_4G },
};

/************************** Function Prototypes ******************************/
#if defined (__GNUC__)
void Init_MPU(void) __attribute__((__section__(".boot")));
static void Xil_SetAttribute(u32 addr, u32 reg_size,s32 reg_num, u32 attrib) __attribute__((__section__(".boot")));
static void Xil_DisableMPURegions(void) __attribute__((__section__(".boot")));
#elif defined (__ICCARM__)
#pragma default_function_attributes = @ ".boot"
void Init_MPU(void);
static void Xil_SetAttribute(u32 addr, u32 reg_size,s32 reg_num, u32 attrib);
static void Xil_DisableMPURegions(void);
#endif
/*****************************************************************************
*
* Initialize MPU for a given address map and Enabled the background Region in
* MPU with default memory attributes for rest of address range for Cortex R5
* processor.
*
* @param	None.
*
* @return	None.
*
*
******************************************************************************/

void Init_MPU(void)
{
	u32 Addr;
	u32 RegSize = 0U;
	u32 Attrib;
	u32 RegNum = 0, i, Offset = 0;
	u64 size;

	Xil_DisableMPURegions();

	Addr = 0x00000000U;
#ifdef	XPAR_PSU_R5_DDR_0_S_AXI_BASEADDR
	/* If the DDR is present, configure region as per DDR size */
	size = (XPAR_PSU_R5_DDR_0_S_AXI_HIGHADDR - XPAR_PSU_R5_DDR_0_S_AXI_BASEADDR) + 1;
	if (size < 0x80000000) {
		/* Lookup the size.  */
		for (i = 0; i < sizeof region_size / sizeof region_size[0]; i++) {
			if (size <= region_size[i].size) {
				RegSize = region_size[i].encoding;

				/* Check if DDR size is in power of 2*/
				if ( XPAR_PSU_R5_DDR_0_S_AXI_BASEADDR == 0x100000)
					Offset = XPAR_PSU_R5_DDR_0_S_AXI_BASEADDR;
				if (region_size[i].size > (size + Offset + 1)) {
					rt_kprintf ("WARNING: DDR size mapped to Cortexr5 processor is not \
								in power of 2. As processor allocates MPU regions size \
								in power of 2, address range %llx to %x has been \
								incorrectly mapped as normal memory \n", \
								region_size[i].size - 1, ((u32)XPAR_PSU_R5_DDR_0_S_AXI_HIGHADDR + 1));
				}
				break;
			}
		}
	} else {
		/* if the DDR size is > 2GB, truncate it to 2GB */
		RegSize = REGION_2G;
	}
#else
	/* For DDRless system, configure region for TCM */
	RegSize = REGION_256K;
#endif
	Attrib = NORM_NSHARED_WB_WA | PRIV_RW_USER_RW;
	Xil_SetAttribute(Addr,RegSize,RegNum, Attrib);
	RegNum++;

	/*
	 * 1G of strongly ordered memory from 0x80000000 to 0xBFFFFFFF for PL.
	 * 512 MB - LPD-PL interface
	 * 256 MB - FPD-PL (HPM0) interface
	 * 256 MB - FPD-PL (HPM1) interface
	 */
	Addr = 0x80000000;
	RegSize = REGION_1G;
	Attrib = STRONG_ORDERD_SHARED | PRIV_RW_USER_RW   ;
	Xil_SetAttribute(Addr,RegSize,RegNum, Attrib);
	RegNum++;

	/* 512M of device memory from 0xC0000000 to 0xDFFFFFFF for QSPI */
	Addr = 0xC0000000U;
	RegSize = REGION_512M;
	Attrib = DEVICE_NONSHARED | PRIV_RW_USER_RW   ;
	Xil_SetAttribute(Addr,RegSize,RegNum, Attrib);
	RegNum++;

	/* 256M of device memory from 0xE0000000 to 0xEFFFFFFF for PCIe Low */
	Addr = 0xE0000000U;
	RegSize = REGION_256M;
	Attrib = DEVICE_NONSHARED | PRIV_RW_USER_RW   ;
	Xil_SetAttribute(Addr,RegSize,RegNum, Attrib);
	RegNum++;

	/* 16M of device memory from 0xF8000000 to 0xF8FFFFFF for STM_CORESIGHT */
	Addr = 0xF8000000U;
	RegSize = REGION_16M;
	Attrib = DEVICE_NONSHARED | PRIV_RW_USER_RW   ;
	Xil_SetAttribute(Addr,RegSize,RegNum, Attrib);
	RegNum++;

	/* 1M of device memory from 0xF9000000 to 0xF90FFFFF for RPU_A53_GIC */
	Addr = 0xF9000000U;
	RegSize = REGION_1M;
	Attrib = DEVICE_NONSHARED | PRIV_RW_USER_RW   ;
	Xil_SetAttribute(Addr,RegSize,RegNum, Attrib);
	RegNum++;

	/* 16M of device memory from 0xFD000000 to 0xFDFFFFFF for FPS slaves */
	Addr = 0xFD000000U;
	RegSize = REGION_16M;
	Attrib = DEVICE_NONSHARED | PRIV_RW_USER_RW   ;
	Xil_SetAttribute(Addr,RegSize,RegNum, Attrib);
	RegNum++;

	/* 16M of device memory from 0xFE000000 to 0xFEFFFFFF for Upper LPS slaves */
	Addr = 0xFE000000U;
	RegSize = REGION_16M;
	Attrib = DEVICE_NONSHARED | PRIV_RW_USER_RW   ;
	Xil_SetAttribute(Addr,RegSize,RegNum, Attrib);
	RegNum++;

	/*
	 * 16M of device memory from 0xFF000000 to 0xFFFFFFFF for Lower LPS slaves,
	 * CSU, PMU, TCM, OCM
	 */
	Addr = 0xFF000000U;
	RegSize = REGION_16M;
	Attrib = DEVICE_NONSHARED | PRIV_RW_USER_RW   ;
	Xil_SetAttribute(Addr,RegSize,RegNum, Attrib);
	RegNum++;

	/* 256K of OCM RAM from 0xFFFC0000 to 0xFFFFFFFF marked as normal memory */
	Addr = 0xFFFC0000U;
	RegSize = REGION_256K;
	Attrib = NORM_NSHARED_WB_WA| PRIV_RW_USER_RW  ;
	Xil_SetAttribute(Addr,RegSize,RegNum, Attrib);

	/* A total of 10 MPU regions are allocated with another 6 being free for users */

}

/*****************************************************************************
*
* Set the memory attributes for a section of memory with starting address addr
* of the region size defined by reg_size having attributes attrib of region number
* reg_num
*
* @param	addr is the address for which attributes are to be set.
* @param	attrib specifies the attributes for that memory region.
* @param	reg_size specifies the size for that memory region.
* @param	reg_num specifies the number for that memory region.
* @return	None.
*
*
******************************************************************************/
static void Xil_SetAttribute(u32 addr, u32 reg_size,s32 reg_num, u32 attrib)
{
	u32 Local_reg_size = reg_size;

	Local_reg_size = Local_reg_size<<1U;
	Local_reg_size |= REGION_EN;
	dsb();
	mtcp(XREG_CP15_MPU_MEMORY_REG_NUMBER,reg_num);
	isb();
	mtcp(XREG_CP15_MPU_REG_BASEADDR,addr); 		/* Set base address of a region */
	mtcp(XREG_CP15_MPU_REG_ACCESS_CTRL,attrib); 	/* Set the control attribute */
	mtcp(XREG_CP15_MPU_REG_SIZE_EN,Local_reg_size);	/* set the region size and enable it*/
	dsb();
	isb();						/* synchronize context on this processor */
}


/*****************************************************************************
*
* Disable all the MPU regions if any of them is enabled
*
* @param	None.
*
* @return	None.
*
*
******************************************************************************/
static void Xil_DisableMPURegions(void)
{
	u32 Temp = 0U;
	u32 Index = 0U;
	for (Index = 0; Index <= 15; Index++) {
		mtcp(XREG_CP15_MPU_MEMORY_REG_NUMBER,Index);
#if defined (__GNUC__)
		Temp = mfcp(XREG_CP15_MPU_REG_SIZE_EN);
#elif defined (__ICCARM__)
		mfcp(XREG_CP15_MPU_REG_SIZE_EN,Temp);
#endif
		Temp &= (~REGION_EN);
		dsb();
		mtcp(XREG_CP15_MPU_REG_SIZE_EN,Temp);
		dsb();
		isb();
	}

}

#if defined (__ICCARM__)
#pragma default_function_attributes =
#endif
