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
 * FilePath: fpcie.h
 * Date: 2022-08-10 14:55:11
 * LastEditTime: 2022-08-18 08:59:37
 * Description: This file is for detailed description of the device and driver.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe  2022/8/18   init commit
 */

#ifndef FPCIE_H
#define FPCIE_H

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/************************** Function Prototypes ******************************/

/***************************** Include Files *********************************/

#include "ftypes.h"
#include "fassert.h"
#include "fpcie_dma.h"
#include "fparameters.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __aarch64__
#define CONFIG_SYS_PCI_64BIT    1
#endif


#ifdef CONFIG_SYS_PCI_64BIT
typedef u64 pci_addr_t;
typedef u64 pci_size_t;
#else
typedef u32 pci_addr_t;
typedef u32 pci_size_t;
#endif

typedef boolean bool;
#define true TRUE
#define false FALSE


/* Access sizes for PCI reads and writes */
enum pci_size_t
{
    PCI_SIZE_8,
    PCI_SIZE_16,
    PCI_SIZE_32,
};


/***************** Macros (Inline Functions) Definitions *********************/

#define FPCIE_ERR_INVALID_PARAM FT_CODE_ERR(ErrModBsp, ErrPcie, 0x1u)
#define FPCIE_ERR_OUTOF_BUS FT_CODE_ERR(ErrModBsp, ErrPcie, 0x2u)
#define FPCIE_ERR_CONFIG_WRITE FT_CODE_ERR(ErrModBsp, ErrPcie, 0x3u)
#define FPCIE_ERR_TYPE0 FT_CODE_ERR(ErrModBsp, ErrPcie, 0x4u)
#define FPCIE_ERR_TIMEOUT FT_CODE_ERR(ErrModBsp, ErrPcie, 0x5u)
#define FPCIE_NEED_SKIP FT_CODE_ERR(ErrModBsp, ErrPcie, 0x6u)
#define FPCIE_NOT_FOUND FT_CODE_ERR(ErrModBsp, ErrPcie, 0x7u)


#define FPCIE_REGION_MEM        0x00000000  /* PCI memory space */
#define FPCIE_REGION_IO         0x00000001  /* PCI IO space */
#define PCI_REGION_PREFETCH     0x00000008  /* prefetchable PCI memory */


#define FPCIE_BAR_0 0
#define FPCIE_BAR_1 1
#define FPCIE_BAR_2 2
#define FPCIE_BAR_3 3
#define FPCIE_BAR_4 4
#define FPCIE_BAR_5 5

/*  PCI-E Unit controller selection */
#define FPCIE_PEU0_C0 0 /* pcie 0  0号控制器 */
#define FPCIE_PEU0_C1 1 /* pcie 0  1号控制器 */
#define FPCIE_PEU0_C2 2 /* pcie 0  2号控制器 */
#define FPCIE_PEU1_C0 3 /* pcie 1  0号控制器 */
#define FPCIE_PEU1_C1 4 /* pcie 1  1号控制器 */
#define FPCIE_PEU1_C2 5 /* pcie 1  2号控制器 */


#define FPCIE_REGION_EXIST_FLG 1

/** @name Callback identifiers
 *
 * These constants are used as parameters to FPcieMiscSetHandler()
 * @{
 */
#define FPCIE_HANDLER_DMASEND 1U
#define FPCIE_HANDLER_DMARECV 2U
#define FPCIE_HANDLER_DMASEND_ERROR 3U
#define FPCIE_HANDLER_DMARECV_ERROR 4U
/*@}*/

typedef void (*FPcieIrqCallBack)(void *args);

#if defined(__aarch64__)
typedef u64 FPcieAddr;
typedef u64 FPcieSize;
typedef u64 FPciePhysAddr;
#else
typedef u32 FPcieAddr;
typedef u32 FPcieSize;
typedef u32 FPciePhysAddr;
#endif


typedef struct
{
    u16 vender_id ;
    u16 device_id ;
    u32 bus_num ;
    u32 dev_num ;
    u32 fun_num ;
    u32 class_code ;
} FPcieSearchFunNode;


typedef struct
{
    void (*IntxCallBack)(void *args) ;
    void *args ;
    s32 bdf ;
} FPcieIntxFun;

struct FPcieRegion
{
    FPcieAddr bus_start;            /* Start on the bus */
    FPciePhysAddr phys_start;   /* Start in physical address space */
    FPcieSize size;             /* Size */
    unsigned long flags;        /* Resource flags */
    FPcieAddr bus_lower;
    u32 exist_flg;              /* exist flg */
};

typedef struct
{
    u16 vendor, device;
} FpcieId;

typedef struct
{
    u32 instance_id; /* Id of device*/
    u32 irq_num;     /* Irq number */
    uintptr_t ecam;  /* The Memory way */
    uintptr_t peu0_config_address;
    uintptr_t peu1_config_address;

    uintptr_t control_c0_address;       
    uintptr_t control_c1_address;       
    uintptr_t control_c2_address;
    uintptr_t control_c3_address;
    uintptr_t control_c4_address;
    uintptr_t control_c5_address;

#ifdef FPCI_INTX_EOI
    uintptr_t intx_peux_stat_address[FPCI_INTX_SATA_NUM] ;
    uintptr_t intx_control_eux_cx_address[FPCI_INTX_CONTROL_NUM] ;
#endif

    u32 io_base_addr;
    u32 io_size ;
    u32 npmem_base_addr;
    u32 npmem_size;
    u64 pmem_base_addr; /* Prefetchable memory */
    u64 pmem_size;

    u8 inta_irq_num ;
    u8 intb_irq_num ;
    u8 intc_irq_num ;
    u8 intd_irq_num ;
    u8 need_skip    ;

} FPcieConfig;

typedef struct
{
    u32 is_ready; /* Device is ininitialized and ready*/
    FPcieConfig config;

    struct FPcieRegion mem;
    struct FPcieRegion mem_prefetch;
    struct FPcieRegion mem_io;

    s32  bus_max; /* 当前最大bus num */

    FPcieIrqCallBack fpcie_dma_rx_cb;
    void *dma_rx_args;

    FPcieIrqCallBack fpcie_dma_tx_cb;
    void *dma_tx_args;

    FPcieIrqCallBack fpcie_dma_rx_error_cb;
    void *dma_rx_error_args;

    FPcieIrqCallBack fpcie_dma_tx_error_cb;
    void *dma_tx_error_args;

    FPcieIntxFun inta_fun[128];     //假设最高支持128个pcie 节点

    FPcieIntxFun intb_fun[128];

    FPcieIntxFun intc_fun[128];

    FPcieIntxFun intd_fun[128];

    s32 scaned_bdf_array[128];
    s32 scaned_bdf_count;

    u32 is_scaned; /* Device is ininitialized and ready*/

} FPcie;

FPcieConfig *FPcieLookupConfig(u32 instance_id);

FError FPcieCfgInitialize(FPcie *instance_p, FPcieConfig *config_p);

/* dma */
FError FPcieDmaDescSet(uintptr axi_addr,
                       uintptr pcie_addr,
                       u32 length,
                       struct FPcieDmaDescriptor *desc,
                       struct FPcieDmaDescriptor *next_desc);


void FPcieDmaRead(uintptr cintrol_address, struct FPcieDmaDescriptor *desc);

void FPcieDmaWrite(uintptr cintrol_address, struct FPcieDmaDescriptor *desc);

FError FPcieDmaPollDone(struct FPcieDmaDescriptor *desc, u32 wait_cnt);

/* Intx Interrupt */
void FPcieIntxIrqHandler(s32 vector, void *args) ;

FError FPcieIntxRegiterIrqHandler(FPcie *instance_p,
                                  u32 bdf,
                                  FPcieIntxFun *intx_fun_p) ;

void FPcieMiscIrqDisable(FPcie *instance_p, fsize_t peu_num) ;

struct FPcieBus
{
    s32 ChildN[32];
    u8  ChildCount;
} ;

typedef enum
{
    HEADER = 0,
    PCIE_CAP = 1,
    PCIE_ECAP = 2
} BITFIELD_REGISTER_TYPE;


const char *FPcieClassStr(u8 class);
void FPcieAutoRegionAlign(struct FPcieRegion *res, pci_size_t size);
int FPcieAutoRegionAllocate(struct FPcieRegion *res, pci_size_t size,
                            pci_addr_t *bar, bool supports_64bit);
void FPcieAutoSetupDevice(FPcie *instance_p, u32 bdf, int bars_num,
                          struct FPcieRegion *mem,
                          struct FPcieRegion *prefetch, struct FPcieRegion *io,
                          bool enum_only);
void FPcieAutoPrescanSetupBridge(FPcie *instance_p, u32 bdf, int sub_bus);
void FPcieAutoPostscanSetupBridge(FPcie *instance_p, u32 bdf, int sub_bus);
int FPcieHoseProbeBus(FPcie *instance_p, u32 bdf);
int FPcieAutoConfigDevice(FPcie *instance_p, u32 bdf);
FError FPcieBindBusDevices(FPcie *instance_p, u32 bus_num, u32 parent_bdf, struct FPcieBus *bus);
FError FPcieScanBus(FPcie *instance_p, u32 bus_num, u32 parent_bdf);


#ifdef __cplusplus
}
#endif

#endif // !
