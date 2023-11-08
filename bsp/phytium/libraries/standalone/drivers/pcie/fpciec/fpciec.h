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
 * FilePath: fpcie.h
 * Created Date: 2023-08-01 22:10:24
 * Last Modified: 2023-08-11 15:05:24
 * Description:  This file is for fpciec struct and application interface
 * 
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 * 1.0     huanghe    2023/08/06        first release
 */

#ifndef FPCIE_H
#define FPCIE_H

#include "ftypes.h"
#include "fdrivers_port.h"
#include "ferror_code.h"
#include "fparameters.h"
#include "fcompiler.h"

#ifdef __cplusplus
extern "C"
{
#endif


#if defined(FAARCH64_USE)
    typedef u64 FPcieCAddr;
    typedef u64 FPcieCSize;
    typedef u64 FPcieCPhysAddr;
#else
typedef u32 FPcieCAddr;
typedef u32 FPcieCSize;
typedef u32 FPcieCPhysAddr;
#endif




#define FPCIEC_ENDPOINT_BOUND_SELECT_OVERRANGE FT_CODE_ERR(ErrModBsp, ErrPcie, 0x2u)
#define FPCIEC_MISC_IRQ_OUTRANGE FT_CODE_ERR(ErrModBsp, ErrPcie, 0x3u)


/* msic type */
#define FPCIEC_MISC_TYPE_DMA0_END 0
#define FPCIEC_MISC_TYPE_DMA1_END 1
#define FPCIEC_MISC_TYPE_DMA2_END 2
#define FPCIEC_MISC_TYPE_DMA3_END 3
#define FPCIEC_MISC_TYPE_DMA4_END 4
#define FPCIEC_MISC_TYPE_DMA5_END 5
#define FPCIEC_MISC_TYPE_DMA6_END 6
#define FPCIEC_MISC_TYPE_DMA7_END 7

#define FPCIEC_MISC_TYPE_DMA0_ERROR (0 + 8)
#define FPCIEC_MISC_TYPE_DMA1_ERROR (1 + 8)
#define FPCIEC_MISC_TYPE_DMA2_ERROR (2 + 8)
#define FPCIEC_MISC_TYPE_DMA3_ERROR (3 + 8)
#define FPCIEC_MISC_TYPE_DMA4_ERROR (4 + 8)
#define FPCIEC_MISC_TYPE_DMA5_ERROR (5 + 8)
#define FPCIEC_MISC_TYPE_DMA6_ERROR (6 + 8)
#define FPCIEC_MISC_TYPE_DMA7_ERROR (7 + 8)

/* mem type */
#define FPCIEC_EP_MEM_32_TYPE        (1<<1) 
#define FPCIEC_EP_MEM_PREFETCH_TYPE  (1<<2)
#define FPCIEC_EP_IO_TYPE            (1<<3)
#define FPCIEC_EP_MEM_64_TYPE        (1<<4)

/* DMA */
#define FPCIEC_DMA_TYPE_READ  0
#define FPCIEC_DMA_TYPE_WRITE 1

/* A typedef for a callback function which takes a misc type and some arguments */
    typedef void (*FPcieCMiscIrqCallBack)(u32 misc_type,void *args);

/* Enumeration of possible PCIe interrupts */
typedef enum
{
    FPCIE_INTERRUPT_UNKNOWN ,
    FPCIE_INTERRUPT_INTA,
    FPCIE_INTERRUPT_INTB,
    FPCIE_INTERRUPT_INTC,
    FPCIE_INTERRUPT_INTD,
} FPcieCIntxNum;

typedef boolean bool;

/* Enumeration for Base Address Register (BAR) numbers in PCIe */
typedef enum
{
    FPCIE_NO_BAR = -1,
    FPCIE_BAR_0 = 0,
    FPCIE_BAR_1,
    FPCIE_BAR_2,
    FPCIE_BAR_3,
    FPCIE_BAR_4,
    FPCIE_BAR_5,
} FPcieCBarNo;

/* Structure defining a BAR in PCIe End Point */
typedef struct
{
    uintptr_t phys_addr;           /* Physical address of the BAR */
    uintptr_t virt_addr;           /* Virtual address of the BAR */
    FPcieCSize size;             /* Size of the BAR */
    FPcieCBarNo bar_no;            /* BAR number */
    u8 flags;                      /* Flags indicating type of memory (1 for 32bit mem, 2 for prefetch mem) */
} FPcieCEpBar;

/* Structure defining the header of a PCIe End Point */
typedef struct
{
    u16 vendor_id;
    u16 device_id;
    u8  revid;                     /* Revision ID */
    u8  progif_code;               /* Programming Interface Code */
    u8  subclass_code;             /* Subclass Code */
    u8  baseclass_code;            /* Base Class Code */
    u8  cache_line_size;           /* Cache Line Size */
    u16 subsys_vendor_id;          /* Subsystem Vendor ID */
    u16 subsys_id;                 /* Subsystem ID */
    FPcieCIntxNum interrupt_pin;   /* Interrupt Pin being used */
} FPcieCEpHeader;

/* Structure defining configuration of the PCIe device */
typedef struct
{
    u32 instance_id;               /* ID of the device */

    uintptr_t config_index;
    uintptr_t config_space;        /* Base address for the config space (hbp base) */
    uintptr_t control_space;       /* Base address for the control (control base) */

    uintptr_t dma_engine_base;     /* Base address for DMA engine */
    u32 dma_max_num;               /* Maximum number for DMA */

    u32 misc_irq_num;              /* Number of miscellaneous interrupts */
} FPcieCConfig;

/* Structure defining PCIe EndPoint memory ranges */
typedef struct 
{
    uintptr_t pref_start;          /* Start address of prefetch memory */
    uintptr_t pref_end;            /* End address of prefetch memory */
    uintptr_t mem_start;           /* Start address of regular memory */
    uintptr_t mem_end;             /* End address of regular memory */
} FPcieCEpPioMemRange;


/* Main structure defining the PCIe configuration */
typedef struct
{
    u32 is_ready;                  /* Flag indicating if the device is initialized and ready */
    FPcieCConfig config;           /* Configuration of the device */

    /* Miscellaneous interrupt */
    FPcieCMiscIrqCallBack misc_irq; /* Callback for DMA engine interrupts */
    void *args;                    /* Arguments to be passed to the callback */

    /* Set map */
    uintptr_t outbound_region_p[FPCIEC_MAX_OUTBOUND_NUM]; /* Outbound region pointers */
    unsigned long outbound_region_map;                    /* Map of the outbound region */

} FPcieC;

/* init */
FError FPcieCCfgInitialize(FPcieC *instance_p, FPcieCConfig *config_p) ;
FPcieCConfig *FPcieCLookupConfig(u32 instance_id) ;

/* endpoint */
void FPcieCEpPioInit(FPcieC *instance_p,FPcieCEpPioMemRange * mem_range) ;
FError FPcieCUnmapEpAddr(FPcieC *instance_p,u32 fun_num ,uintptr_t addr) ;
FError FPcieCMapEpAddr(FPcieC *instance_p,u32 fun_num ,uintptr_t addr , u64 pci_addr,FPcieCSize size ) ;
FError FPcieCClearEpBar(FPcieC *instance_p,u32 fun_num ,FPcieCBarNo bar_no) ;
FError FPcieCSetEpBar(FPcieC *instance_p,u32 fun_num ,FPcieCEpBar *ep_bar) ;
FError FPcieCWriteEpHeader(FPcieC *instance_p,u32 fun_num ,FPcieCEpHeader *header_p)  ;


/* dma */
u32 FPcieCDmaStatusGet(FPcieC *instance_p,u32 channel_index) ;
FError FPcieCDmaStart(FPcieC *instance_p,u32 channel_index) ;
FError FPcieCDmaDirectConfig(FPcieC *instance_p,u32 channel_index,uintptr_t src_addr,uintptr_t dest_addr,u32 length,u32 direct) ;


/* misc */
void FPcieCMiscIrqInit(FPcieC *instance_p) ;
FError FPcieCMiscIrqRegister(FPcieC *instance_p,FPcieCMiscIrqCallBack misc_irq,void *args) ;
void FPcieCMiscIrq(s32 vector, void *args) ;
FError FPcieCMiscIrqConfig(FPcieC *instance_p,u32 irq_type,bool set) ;


#ifdef __cplusplus
}
#endif

#endif // !
