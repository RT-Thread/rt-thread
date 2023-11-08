/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
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
 * FilePath: fpciec_hw.h
 * Created Date: 2023-08-02 09:52:01
 * Last Modified: 2023-08-06 09:53:10
 * Description:  This file is for pciec hardware registers offset
 * 
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 * 1.0     huanghe    2023/08/06        first release
 */

#ifndef FPCIEC_HW_H
#define FPCIEC_HW_H

#include "ftypes.h"
#include "fkernel.h"
#include "fio.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* Bridge internal Registers */
/* Control and Status Registers */

#define FPCIEC_STANDARD_CONFIG_VENDOR_ID_REG 0x98        /* Vendor ID */
#define FPCIEC_STANDARD_CONFIG_DEVICE_ID_REG 0x9a        /* Device ID */
#define FPCIEC_STANDARD_CONFIG_REVISION_ID_REG 0x9c      /* Revision ID */

#define FPCIEC_STANDARD_CONFIG_CLASS_PROG_REG			0x9d /* Class code */
#define FPCIEC_STANDARD_CONFIG_CLASS_DEVICE_REG		0x9e     /*  */
#define FPCIEC_STANDARD_CONFIG_SUBSYS_VENDOR_ID_REG		0xa0  /* Sub-system vendor ID */
#define FPCIEC_STANDARD_CONFIG_SUBSYS_DEVICE_ID_REG		0xa2  /*  Sub-system device ID */
#define FPCIEC_STANDARD_CONFIG_INTERRUPT_PIN_REG		0xa8 /* PCIe PCI Interrupt Settings */
#define FPCIEC_STANDARD_CONFIG_MSIX_CAP_REG			0xaa /* PCIe MSI-X Settings */

#define FPCIEC_STANDARD_CONFIG_BAR01                 0xe4

#define FPCIEC_IMASK_LOCAL_REG                       0x180   /* Local Processor Interrupt Mask */
#define FPCIEC_ISTATUS_LOCAL_REG                     0x184   /* Local Processor Interrupt Status */
#define FPCIEC_IMASK_HOST_REG                        0x188   /* Host Processor Interrupt Mask */
#define FPCIEC_ISTATUS_HOST_REG                      0x18c   /* Host Processor Interrupt Status */



#define FPCIEC_STANDARD_CONFIG_BAR(bar_num)          (FPCIEC_STANDARD_CONFIG_BAR01 + (bar_num <<2))    
/* Outbound */
#define FPCIEC_STANDARD_CONFIG_WIN0                         0x600 
#define FPCIEC_STANDARD_CONFIG_WIN0_SRC_ADDR(table)         (FPCIEC_STANDARD_CONFIG_WIN0+0x20 *table )
#define FPCIEC_STANDARD_CONFIG_WIN0_SRC_ADDR_U(table)         (FPCIEC_STANDARD_CONFIG_WIN0+0x20 * table + 0x4 )
#define FPCIEC_STANDARD_CONFIG_WIN0_TRSL_ADDR(table)         (FPCIEC_STANDARD_CONFIG_WIN0+0x20 * table + 0x8 )
#define FPCIEC_STANDARD_CONFIG_WIN0_TRSL_ADDR_U(table)         (FPCIEC_STANDARD_CONFIG_WIN0+0x20 * table + 0xc )
#define FPCIEC_STANDARD_CONFIG_WIN0_TRSL_PARAM(table)         (FPCIEC_STANDARD_CONFIG_WIN0+0x20 * table + 0x10 )
/*  */
#define FPCIEC_STANDARD_CONFIG_SLAVE0                        0x800
#define FPCIEC_STANDARD_CONFIG_SLAVE0_SRC_ADDR(table)         (FPCIEC_STANDARD_CONFIG_SLAVE0+0x20 *table )
#define FPCIEC_STANDARD_CONFIG_SLAVE0_SRC_ADDR_U(table)         (FPCIEC_STANDARD_CONFIG_SLAVE0+0x20 * table + 0x4 )
#define FPCIEC_STANDARD_CONFIG_SLAVE0_TRSL_ADDR(table)         (FPCIEC_STANDARD_CONFIG_SLAVE0+0x20 * table + 0x8 )
#define FPCIEC_STANDARD_CONFIG_SLAVE0_TRSL_ADDR_U(table)         (FPCIEC_STANDARD_CONFIG_SLAVE0+0x20 * table + 0xc )
#define FPCIEC_STANDARD_CONFIG_SLAVE0_TRSL_PARAM(table)         (FPCIEC_STANDARD_CONFIG_SLAVE0+0x20 * table + 0x10 )

/* only for endpoint mode */
#define FPCIEC_STANDARD_CONFIG_IMASK_HOST            0x188
#define FPCIEC_STANDARD_CONFIG_ISTATUS_HOST          0x18c


/* FPCIEC_STANDARD_CONFIG_INTERRUPT_PIN_REG */
#define FPCIEC_STANDARD_CONFIG_INTERRUPT_PIN_MASK    0x7 /* Bit [2:0]: Interrupt Pin */

/* FPCIEC_STANDARD_CONFIG_MSIX_CAP_REG */
#define FPCIEC_STANDARD_CONFIG_MSIX_CAP_MSIX_MASK    (1 << 15)

#define FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num) (u32)(((fun_num) << 14) & GENMASK(16, 14))

/* FPCIEC_STANDARD_CONFIG_BAR */
#define FPCIEC_STANDARD_CONFIG_BAR_IO            (1<<0)
#define FPCIEC_STANDARD_CONFIG_BAR_MEM           (0<<0)
#define FPCIEC_STANDARD_CONFIG_BAR_MEM64         (1<<2)
#define FPCIEC_STANDARD_CONFIG_BAR_MEMPREFET     (1<<3)                                


/* FPCIEC_STANDARD_CONFIG_WIN0 */
#define FPCIEC_STANDARD_CONFIG_WIN0_TRSL_IO           (1<<0) | (2 << 16)
#define FPCIEC_STANDARD_CONFIG_WIN0_TRSL_TR           (0<<0)
#define FPCIEC_STANDARD_CONFIG_WIN0_TRSL_MASTER       (1<<2)
#define FPCIEC_STANDARD_CONFIG_WIN0_ATR_SIZE_MASK(x)  (((x)<<1) & 0x7e )
#define FPCIEC_STANDARD_CONFIG_WIN0_ATR_IMPL          (1 << 0)  


/* FPCIEC_STANDARD_CONFIG_IMASK_HOST */

#define FPCIEC_STANDARD_CONFIG_IMASK_INTA            (1<<24)
#define FPCIEC_STANDARD_CONFIG_IMASK_INTB            (1<<25)
#define FPCIEC_STANDARD_CONFIG_IMASK_INTC            (1<<26)
#define FPCIEC_STANDARD_CONFIG_IMASK_INTd            (1<<27)

/* HPB */
#define	FPCIEC_HPB_C0_PREF_BASE_LIMIT	0xa40
#define	FPCIEC_HPB_C0_PREF_BASE_LIMIT_UP32	0xa44
#define FPCIEC_HPB_C0_MEM_BASE_LIMIT     0xa48


/* FPCIEC_HPB_C0_PREF_BASE_LIMIT */
#define FPCIEC_HPB_CX_PREF_BASE_LIMIT_OFFSET(control_num)   (FPCIEC_HPB_C0_PREF_BASE_LIMIT + (control_num) * 0x10)
#define FPCIEC_HPB_CX_PREF_LIMIT(address)  (u32)(((LOWER_32_BITS(address) >> 20) & 0xfff)  << 20)
#define FPCIEC_HPB_CX_PREF_BASE(address)  (u32)(((LOWER_32_BITS(address)>>20) & 0xfff)  << 4)


/* FPCIEC_HPB_C0_PREF_BASE_LIMIT_UP32 */
#define FPCIEC_HPB_CX_PREF_BASE_LIMIT_UP32_OFFSET(control_num)   (FPCIEC_HPB_C0_PREF_BASE_LIMIT_UP32 + (control_num) * 0x10)
#define FPCIEC_HPB_CX_PREF_LIMIT_UP32(address)   (u32)((UPPER_32_BITS(address) & 0xff) << 8)
#define FPCIEC_HPB_CX_PREF_BASE_UP32(address)   (u32)((UPPER_32_BITS(address) & 0xff) << 0)

/* FPCIEC_HPB_C0_MEM_BASE_LIMIT */
#define FPCIEC_HPB_CX_MEM_BASE_LIMIT_OFFSET(control_num)    (FPCIEC_HPB_C0_MEM_BASE_LIMIT + (control_num) * 0x10)
#define FPCIEC_HPB_CX_MEM_LIMIT(address)  (u32)(((address>>20) & 0xfff)  << 20)
#define FPCIEC_HPB_CX_MEM_BASE(address)  (u32)(((address>>20) & 0xfff)  << 4)


/* FPCIEC_IMASK_LOCAL_REG */
#define FPCIEC_IMASK_LOCAL_DMAX_END(x)   (x&0xff)
#define FPCIEC_IMASK_LOCAL_DMAX_ERROR(x)   ((x<<16)&0xff00)
/* FPCIEC_ISTATUS_LOCAL_REG */
#define FPCIEC_ISTATUS_LOCAL_DMAX_END(x)   (x&0xff)
#define FPCIEC_ISTATUS_LOCAL_DMAX_ERROR(x)   ((x<<16)&0xff00)

/* FPCIEC_IMASK_HOST_REG */
#define FPCIEC_IMASK_HOST_DMAX_END(x)   (x&0xff)
#define FPCIEC_IMASK_HOST_DMAX_ERROR(x)   ((x<<16)&0xff00)
/* FPCIEC_ISTATUS_HOST_REG */
#define FPCIEC_ISTATUS_HOST_DMAX_END(x)   (x&0xff)
#define FPCIEC_ISTATUS_HOST_DMAX_ERROR(x)   ((x<<16)&0xff00)



#define FPCIEC_HW_WRITEW(mem,offset,value) FtOut32((uintptr)(mem + offset),value) 
#define FPCIEC_HW_WRITEHW(mem,offset,value) FtOut16((uintptr)(mem + offset),value) 
#define FPCIEC_HW_WRITEB(mem,offset,value) FtOut8((uintptr)(mem + offset),value) 

#define FPCIEC_HW_READW(mem,offset) FtIn32((uintptr)(mem + offset))
#define FPCIEC_HW_READHW(mem,offset) FtIn16((uintptr)(mem + offset)) 
#define FPCIEC_HW_READB(mem,offset) FtIn8((uintptr)(mem + offset)) 

#ifdef __cplusplus
}
#endif

#endif
