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
 * FilePath: fpcie_ecam.h
 * Created Date: 2023-08-01 08:43:09
 * Last Modified: 2023-11-01 09:36:20
 * Description:  This file is for
 *
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 */

#ifndef FPCIE_ECAM_H
#define FPCIE_ECAM_H

#include "ftypes.h"
#include "fassert.h"
#include "fparameters.h"
#include "fcompiler.h"

#include "fdrivers_port.h"

#ifdef __cplusplus
extern "C"
{
#endif


#define FPCIE_EXCEED_BUS FT_CODE_ERR(ErrModBsp, ErrPcie, 0x1u)
#define FPCIE_READCONFIG_ERROR  FT_CODE_ERR(ErrModBsp, ErrPcie, 0x2u)
#define FPCIE_CONFIG_REGION_ERROR FT_CODE_ERR(ErrModBsp, ErrPcie, 0x3u)
#define FPCIE_TYPE_NOT_FIT FT_CODE_ERR(ErrModBsp, ErrPcie, 0x4u)
#define FPCIE_DEVICE_NOT_FOUND FT_CODE_ERR(ErrModBsp, ErrPcie, 0x5u)
#define FPCIE_INTX_OVER_RANGE FT_CODE_ERR(ErrModBsp, ErrPcie, 0x6u)
#define FPCIE_NEED_SKIP FT_CODE_ERR(ErrModBsp, ErrPcie, 0x7u)


#ifdef FAARCH64_USE
#define CONFIG_SYS_PCI_64BIT 1
#endif

#ifdef CONFIG_SYS_PCI_64BIT
typedef u64 fpciaddr_t;
typedef u64 fpcisize_t;
#else
typedef u32 fpciaddr_t;
typedef u32 fpcisize_t;
#endif



#if defined(__aarch64__)
typedef u64 FPcieAddr;
typedef u64 FPcieSize;
typedef u64 FPciePhysAddr;
#else
typedef u32 FPcieAddr;
typedef u32 FPcieSize;
typedef u32 FPciePhysAddr;
#endif

#define FPCIE_REGION_MEM 0x00000000    /* PCI memory space */
#define FPCIE_REGION_IO 0x00000001     /* PCI IO space */
#define PCI_REGION_PREFETCH 0x00000008 /* prefetchable PCI memory */


#define FPCIE_REGION_EXIST_FLG 1

typedef int (*FPcieEcamNeedSkip)(void *instance_p, u8 bus, u8 device, u8 function) ;


struct FPcieRegion
{
    FPcieAddr bus_start;      /* Start on the bus */
    FPciePhysAddr phys_start; /* Start in physical address space */
    FPcieSize size;           /* Size */
    unsigned long flags;      /* Resource flags */
    FPcieAddr bus_lower;       /* Lower address */
    u32 exist_flg; /* exist flg */
};



/* Structure defining the PCIe interrupt callback function */
typedef struct
{
    void (*IntxCallBack)(void *args); /* Pointer to a callback function to be invoked on a PCIe interrupt event*/
    void *args;                       /* Arguments to be passed to the callback function*/
    u8 bus;                           /* PCIe bus number*/
    u8 device;                        /* PCIe device number*/
    u8 function;                      /* PCIe function number*/
} FPcieIntxFun;



/* Structure defining the PCIe ECAM (Enhanced Configuration Access Mechanism) configuration */
typedef struct
{
    u32 instance_id;                    /* ID of the device */
    uintptr_t ecam;                     /* Base address for the ECAM to access PCIe configuration space */
    u32 io_base_addr;                   /* IO base address */
    u32 io_size;                        /* IO size */
    u32 npmem_base_addr;                /* Non-prefetchable memory base address */
    u32 npmem_size;                     /* Non-prefetchable memory size */
    u64 pmem_base_addr;                 /* Prefetchable memory base address */
    u64 pmem_size;                      /* Prefetchable memory size */

    u8 inta_irq_num;                    /* IRQ number for INTA */
    u8 intb_irq_num;                    /* IRQ number for INTB */
    u8 intc_irq_num;                    /* IRQ number for INTC */
    u8 intd_irq_num;                    /* IRQ number for INTD */

    u32 max_bus_num;                    /* Maximum bus number */
    u32 max_dev_num;                    /* Maximum device number */
    u32 max_fun_num;                    /* Maximum function number */

    u32 feature;                        /* Feature flags, such as whether FPCI ECAM INTX requires EOI (End of Interrupt) */

#ifdef FPCI_ECAM_INTX_NEED_EOI
    uintptr_t control_intx_base[FPCI_ECAM_INTX_CONTROL_STATUS_REG_NUM]; /* Array of base addresses to control INTX */
    uintptr_t config_intx_base[FPCI_ECAM_INTX_CONFIG_ISTATUS_NUM];     /* Array of base addresses for INTX configuration */
#endif

} FPcieEcamConfig;


/* Structure defining the BDF (Bus Device Function) for PCIe scanning */
typedef struct
{
    u8 bus;                             /* PCIe bus number */
    u8 device;                          /* PCIe device number */
    u8 function;                        /* PCIe function number */
} FPcieScanBdf;



/* Main structure defining the PCIe ECAM properties */
typedef struct
{
    u32 is_ready;                       /* Flag indicating whether the device has been initialized and is ready */
    FPcieEcamConfig config;             /* Configuration data for PCIe ECAM */

    FPcieEcamNeedSkip need_skip_fun;    /* Data structure indicating functions that need to be skipped */

    struct FPcieRegion mem;             /* Memory region */
    struct FPcieRegion mem_prefetch;    /* Prefetchable memory region */
    struct FPcieRegion mem_io;          /* IO memory region */

    u32 bus_max;                        /* Maximum bus number currently in use */

    FPcieIntxFun inta_fun[FPCIE_MAX_SCAN_NUMBER]; /* Array of callback functions for INTA */
    s32 inta_num;                       /* Count of INTA callback functions */

    u32 is_scaned;                      /* Flag indicating whether the device has been scanned */
    u32 last_bus;                       /* Last scanned bus number */

    FPcieScanBdf scans_bdf[FPCIE_MAX_SCAN_NUMBER]; /* Array of scanned BDFs */
    u32 scans_bdf_count;                /* Count of scanned BDFs */
} FPcieEcam;



/* Ecam */
FError FPcieEcamCfgInitialize(FPcieEcam *instance_p, FPcieEcamConfig *config_p, FPcieEcamNeedSkip need_skip_fun) ;
FError FPcieEcamEnumerateBus(FPcieEcam *instance_p, u8 bus) ;
FError FPcieEcamReadConfigSpace(FPcieEcam *instance_p, u8 bus, u8 device, u8 function, u16 offset, u32 *data) ;
FError FPcieEcamWriteConfigSpace(FPcieEcam *instance_p, u8 bus, u8 device, u8 function, u16 offset, u32 data) ;
FPcieEcamConfig *FPcieEcamLookupConfig(u32 instance_id) ;

/* capability */
u32 FPcieEcamHasExtendCapability(FPcieEcam *instance_p, u8 bus, u8 device, u8 function, u16 capid) ;
u32 FPcieEcamHasCapability(FPcieEcam *instance_p, u8 bus, u8 device, u8 function, u8 capid) ;

/* intx */
FError FPcieEcamIntxRegister(FPcieEcam *instance_p, u8 bus, u8 device, u8 function, FPcieIntxFun *func_p) ;
void FPcieEcamIntxIrqHandler(s32 vector, void *args)  ;

/* debug */
void FPcieEcamInfoPrint(FPcieEcam *instance_p) ;
const char *FPcieEcamClassStr(u8 class) ;

#ifdef __cplusplus
}
#endif


#endif // !
