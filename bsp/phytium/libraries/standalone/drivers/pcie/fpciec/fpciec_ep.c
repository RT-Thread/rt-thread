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
 * FilePath: fpciec_ep.c
 * Created Date: 2023-08-02 09:38:21
 * Last Modified: 2023-08-11 15:05:12
 * Description:  This file is for pciec endpoint implementation
 * 
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 * 1.0     huanghe    2023/08/06        first release
 */
#include "fpciec.h"
#include "fpciec_hw.h"
#include <string.h>
#include <stdint.h>
#include "fassert.h"
#include "fdrivers_port.h"


#define FPCIEC_EP_DEBUG_TAG "FPCIEC_EP"
#define FPCIEC_EP_ERROR(format, ...) FT_DEBUG_PRINT_E(FPCIEC_EP_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIEC_EP_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FPCIEC_EP_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIEC_EP_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FPCIEC_EP_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIEC_EP_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FPCIEC_EP_DEBUG_TAG, format, ##__VA_ARGS__)


static int FPcieCFls64(uint64_t x)
{
    uint32_t h = x >> 32;

    if (h)
        return fls(h) + 32;
    return fls(x);
}

static u32 FPcieFindFirstZeroBit(const unsigned long *addr, u32 size)
{
    for (u32 idx = 0; idx < size; idx++)
    {
        if (!(*addr & (1UL << idx))) { // 检查当前位是否为零
            return idx;
        }
    }
    return size; // 所有位都是1，返回 size 表示未找到零位
}

/**
 * @name: FPcieCWriteEpHeader
 * @msg: Writes configuration data to an Endpoint's PCI configuration header.
 * @param {FPcieC *} instance_p - Pointer to the FPcieC instance.
 * @param {u32} fun_num - EP function number.
 * @param {FPcieCEpHeader *} header_p - Pointer to the EP header configuration.
 * @return {FError} - FT_SUCCESS if successful, error code otherwise.
 */
FError FPcieCWriteEpHeader(FPcieC *instance_p,u32 fun_num ,FPcieCEpHeader *header_p) 
{
    u16 reg;
    uintptr_t control_space = 0 ;
    FASSERT(instance_p != NULL);
    control_space = instance_p->config.control_space ;
    FASSERT(control_space != (uintptr_t)NULL) ;
    
    FPCIEC_HW_WRITEHW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num) + FPCIEC_STANDARD_CONFIG_VENDOR_ID_REG,header_p->vendor_id) ;
    FPCIEC_HW_WRITEHW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num) + FPCIEC_STANDARD_CONFIG_DEVICE_ID_REG,header_p->device_id) ;
    FPCIEC_HW_WRITEB(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num) + FPCIEC_STANDARD_CONFIG_REVISION_ID_REG,header_p->revid) ;
    FPCIEC_HW_WRITEB(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num) + FPCIEC_STANDARD_CONFIG_CLASS_PROG_REG,header_p->progif_code) ;
    
    FPCIEC_HW_WRITEHW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num) + FPCIEC_STANDARD_CONFIG_CLASS_DEVICE_REG,header_p->subclass_code | (header_p->baseclass_code<<8)) ;
    FPCIEC_HW_WRITEHW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num) + FPCIEC_STANDARD_CONFIG_SUBSYS_VENDOR_ID_REG,header_p->subsys_vendor_id ) ;
    FPCIEC_HW_WRITEHW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num) + FPCIEC_STANDARD_CONFIG_SUBSYS_DEVICE_ID_REG,header_p->subsys_id ) ;

    reg = FPCIEC_HW_READHW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num) + FPCIEC_STANDARD_CONFIG_INTERRUPT_PIN_REG) ;
    reg &= ~ FPCIEC_STANDARD_CONFIG_INTERRUPT_PIN_MASK;
    FPCIEC_HW_WRITEHW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num) + FPCIEC_STANDARD_CONFIG_INTERRUPT_PIN_REG,reg) ;

    reg = FPCIEC_HW_READHW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num) + FPCIEC_STANDARD_CONFIG_MSIX_CAP_REG) ;
    reg &= ~ FPCIEC_STANDARD_CONFIG_MSIX_CAP_MSIX_MASK ;
    FPCIEC_HW_WRITEHW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num) + FPCIEC_STANDARD_CONFIG_MSIX_CAP_REG,reg) ;
    return FT_SUCCESS;
}

/**
 * @name: FPcieCSetEpBar
 * @msg: Configures an Endpoint's Base Address Register (BAR).
 * @param {FPcieC *} instance_p - Pointer to the FPcieC instance.
 * @param {u32} fun_num - EP function number.
 * @param {FPcieCEpBar *} ep_bar - Pointer to the EP BAR configuration.
 * @return {FError} - FT_SUCCESS if successful, error code otherwise.
 */
FError FPcieCSetEpBar(FPcieC *instance_p,u32 fun_num ,FPcieCEpBar *ep_bar)
{
    FPcieCBarNo bar_no ; 
    u8 flags ;
    u32 setting ;
    u64 size ,sz_mask;
    u32 trsl_param ,atr_size , src_addr,src_addr_u,trsl_addr,trsl_addr_u ;
    uintptr_t control_space ;
    FASSERT(instance_p != NULL);
    control_space = instance_p->config.control_space ;
    FASSERT(control_space != (uintptr_t)NULL) ;
    FASSERT(ep_bar!= NULL) ;
    FASSERT(fun_num < 8 ) ;

    
    bar_no = ep_bar->bar_no ;
    flags  = ep_bar->flags ;
    
    if((bar_no & 1) && (flags&FPCIEC_STANDARD_CONFIG_BAR_MEM64))
    {
        return FPCIEC_ENDPOINT_BOUND_SELECT_OVERRANGE ;
    }
    
    FPCIEC_EP_DEBUG_I("set bar%d mapping address 0x%p size 0x%lx\n",
		bar_no, (ep_bar->phys_addr), ep_bar->size) ; 
    
    if(FPCIEC_EP_IO_TYPE & flags)
    {
        /* select io */
        setting = FPCIEC_STANDARD_CONFIG_BAR_IO  ;
        size = max_t(FPcieCSize,ep_bar->size,4) ;        
        size = 1 << FPcieCFls64(size - 1) ;
        sz_mask = ~(size - 1);
        setting |= sz_mask ;
        trsl_param = FPCIEC_STANDARD_CONFIG_WIN0_TRSL_IO;
    }
    else if(FPCIEC_EP_MEM_32_TYPE & flags)
    {
        FPCIEC_EP_DEBUG_I("FPCIEC_EP_MEM_32_TYPE is here \r\n") ;
        /*  select mem32 */
        setting = FPCIEC_STANDARD_CONFIG_BAR_MEM  ;
        size = max_t(FPcieCSize,ep_bar->size,16) ;  
        /* size 被舍入到最接近的2的幂次方 */
        size = 1 << FPcieCFls64(size - 1) ;
        sz_mask = ~(size - 1);
        setting |= sz_mask & 0xffffffff;
        trsl_param = FPCIEC_STANDARD_CONFIG_WIN0_TRSL_MASTER;
    }
    else
    {
        /*  select mem64 */
        setting = FPCIEC_STANDARD_CONFIG_BAR_MEM  ;
        size = max_t(FPcieCSize,ep_bar->size,16) ;       
        /* size 被舍入到最接近的2的幂次方 */
        size = 1 << FPcieCFls64(size - 1) ;
        sz_mask = ~(size - 1);
        setting |= sz_mask ;

        trsl_param = FPCIEC_STANDARD_CONFIG_WIN0_TRSL_MASTER;

        if(FPCIEC_EP_MEM_PREFETCH_TYPE & flags)
        {
            setting |= FPCIEC_STANDARD_CONFIG_BAR_MEMPREFET ;
        }
        
        if(FPCIEC_EP_MEM_64_TYPE & flags)
        {
            setting |= FPCIEC_STANDARD_CONFIG_BAR_MEM64 ;
            FPCIEC_HW_WRITEW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+FPCIEC_STANDARD_CONFIG_BAR((ep_bar->bar_no + 1)),UPPER_32_BITS(sz_mask)) ;
        }
    }
        

    /* write bar setting */
    FPCIEC_HW_WRITEW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+FPCIEC_STANDARD_CONFIG_BAR(ep_bar->bar_no),setting) ;
    

    FPCIEC_EP_DEBUG_I("set bar%d mapping address 0x%pa size 0x%llx 0x%x\n",
		bar_no, (ep_bar->phys_addr), size, LOWER_32_BITS(ep_bar->phys_addr));

    size = ALIGN(size, 4096);
	atr_size = FPcieCFls64(size - 1) - 1;
	src_addr = FPCIEC_STANDARD_CONFIG_WIN0_ATR_IMPL | FPCIEC_STANDARD_CONFIG_WIN0_ATR_SIZE_MASK(atr_size) ;// ((atr_size & ATR_SIZE_MASK) << ATR_SIZE_SHIFT);
	src_addr_u = 0;
	trsl_addr = (LOWER_32_BITS(ep_bar->phys_addr) & 0xfffff000);
	trsl_addr_u = UPPER_32_BITS(ep_bar->phys_addr);

    /* code */
    FPCIEC_HW_WRITEW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+ FPCIEC_STANDARD_CONFIG_WIN0_SRC_ADDR(bar_no),src_addr) ;
    FPCIEC_HW_WRITEW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+ FPCIEC_STANDARD_CONFIG_WIN0_SRC_ADDR_U(bar_no),src_addr_u) ;
    FPCIEC_HW_WRITEW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+ FPCIEC_STANDARD_CONFIG_WIN0_TRSL_ADDR(bar_no),trsl_addr) ;
    FPCIEC_HW_WRITEW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+ FPCIEC_STANDARD_CONFIG_WIN0_TRSL_ADDR_U(bar_no),trsl_addr_u) ;
    FPCIEC_HW_WRITEW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+ FPCIEC_STANDARD_CONFIG_WIN0_TRSL_PARAM(bar_no),trsl_param) ;
    return FT_SUCCESS ;
}

/**
 * @name: FPcieCClearEpBar
 * @msg: Clears an Endpoint's Base Address Register (BAR) configuration.
 * @param {FPcieC *} instance_p - Pointer to the FPcieC instance.
 * @param {u32} fun_num - EP function number.
 * @param {FPcieCBarNo} bar_no - BAR number to clear.
 * @return {FError} - FT_SUCCESS if successful, error code otherwise.
 */
FError FPcieCClearEpBar(FPcieC *instance_p,u32 fun_num ,FPcieCBarNo bar_no)
{

    uintptr_t control_space = 0 ;
    FASSERT(instance_p != NULL);
    control_space = instance_p->config.control_space ;
    FASSERT(control_space != (uintptr_t)NULL) ;

    /* write bar setting */
    FPCIEC_HW_WRITEHW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+FPCIEC_STANDARD_CONFIG_BAR(bar_no),0) ;
    FPCIEC_HW_WRITEHW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+FPCIEC_STANDARD_CONFIG_BAR((bar_no + 1)),0) ;
    
    FPCIEC_HW_WRITEW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+ FPCIEC_STANDARD_CONFIG_WIN0_SRC_ADDR(bar_no),0) ;
    FPCIEC_HW_WRITEW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+ FPCIEC_STANDARD_CONFIG_WIN0_SRC_ADDR_U(bar_no),0) ;
    FPCIEC_HW_WRITEW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+ FPCIEC_STANDARD_CONFIG_WIN0_TRSL_ADDR(bar_no),0) ;
    FPCIEC_HW_WRITEW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+ FPCIEC_STANDARD_CONFIG_WIN0_TRSL_ADDR_U(bar_no),0) ;
    FPCIEC_HW_WRITEW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+ FPCIEC_STANDARD_CONFIG_WIN0_TRSL_PARAM(bar_no),0) ;

    return FT_SUCCESS ;
}

/**
 * @brief Maps an EP address to an RC address for data transfer.
 *
 * This function sets up the necessary configurations to map an EP address to an RC address
 * for data transfer between EP and RC.
 *
 * @param instance_p A pointer to the FPcieC instance.
 * @param fun_num The function number for the EP.
 * @param ep_pci_addr The EP PCI address to be mapped.
 * @param rc_addr The RC address to map to.
 * @param size The size of the mapping.
 *
 * @return FT_SUCCESS if the mapping is successful, otherwise an error code.
 */
FError FPcieCMapEpAddr(FPcieC *instance_p,u32 fun_num ,uintptr_t ep_pci_addr , u64 rc_addr,FPcieCSize size )
{
    u64 size_target;
    u32 trsl_param ,atr_size , src_addr,src_addr_u,trsl_addr,trsl_addr_u ;
    u32 select_bounds ;
    uintptr_t control_space = 0 ;
    FASSERT(instance_p != NULL);
    control_space = instance_p->config.control_space ;
    FASSERT(control_space != (uintptr_t)NULL) ;
    
    select_bounds = FPcieFindFirstZeroBit(&instance_p->outbound_region_map,sizeof(instance_p->outbound_region_map)*8) ;
    FPCIEC_EP_DEBUG_I("select_bounds is %d\n",select_bounds) ;
    FPCIEC_EP_DEBUG_I("instance_p->config.outbound_max_num is %d\n",FPCIEC_MAX_OUTBOUND_NUM) ;
    if(select_bounds > FPCIEC_MAX_OUTBOUND_NUM)
    {
        return FPCIEC_ENDPOINT_BOUND_SELECT_OVERRANGE ;
    }

    size_target = ALIGN(size, 4096);
    atr_size = FPcieCFls64(size_target - 1) - 1;
    
    src_addr = FPCIEC_STANDARD_CONFIG_WIN0_ATR_IMPL | FPCIEC_STANDARD_CONFIG_WIN0_ATR_SIZE_MASK(atr_size) ;// ((atr_size & ATR_SIZE_MASK) << ATR_SIZE_SHIFT);
    src_addr |= LOWER_32_BITS(ep_pci_addr) & 0xfffff000;
	src_addr_u = UPPER_32_BITS(ep_pci_addr);
	trsl_addr = (LOWER_32_BITS(rc_addr) & 0xfffff000);
	trsl_addr_u = UPPER_32_BITS(rc_addr);
    trsl_param = FPCIEC_STANDARD_CONFIG_WIN0_TRSL_TR ;

    FPCIEC_HW_WRITEW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+ FPCIEC_STANDARD_CONFIG_SLAVE0_SRC_ADDR(select_bounds),src_addr) ;
    FPCIEC_HW_WRITEW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+ FPCIEC_STANDARD_CONFIG_SLAVE0_SRC_ADDR_U(select_bounds),src_addr_u) ;
    FPCIEC_HW_WRITEW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+ FPCIEC_STANDARD_CONFIG_SLAVE0_TRSL_ADDR(select_bounds),trsl_addr) ;
    FPCIEC_HW_WRITEW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+ FPCIEC_STANDARD_CONFIG_SLAVE0_TRSL_ADDR_U(select_bounds),trsl_addr_u) ;
    FPCIEC_HW_WRITEW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+ FPCIEC_STANDARD_CONFIG_SLAVE0_TRSL_PARAM(select_bounds),trsl_param) ;

    instance_p->outbound_region_map |= 1<<select_bounds ;
    instance_p->outbound_region_p[select_bounds] = ep_pci_addr ;
    return FT_SUCCESS ;
}

/**
 * @name: FPcieCUnmapEpAddr
 * @msg: Unmaps an address in the context of an EP function.
 * @param {FPcieC *} instance_p - Pointer to the FPcieC instance.
 * @param {u32} fun_num - EP function number.
 * @param {uintptr_t} addr - Address to unmap.
 * @return {FError} - FT_SUCCESS if successful, error code otherwise.
 */
FError FPcieCUnmapEpAddr(FPcieC *instance_p,u32 fun_num ,uintptr_t addr)
{
    u32 select_bounds ;
    uintptr_t control_space = 0 ;
    FASSERT(instance_p != NULL);
    control_space = instance_p->config.control_space ;
    FASSERT(control_space != (uintptr_t)NULL) ;

    for(select_bounds = 0; select_bounds < FPCIEC_MAX_OUTBOUND_NUM;select_bounds ++)
    {
       if(addr == instance_p->outbound_region_p[select_bounds])
       {
            break;
       }
    }

    FPCIEC_EP_DEBUG_I("set slave %d: unmapping address 0x%p\n", select_bounds, addr);
    FPCIEC_HW_WRITEW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+ FPCIEC_STANDARD_CONFIG_SLAVE0_SRC_ADDR(select_bounds),0) ;
    FPCIEC_HW_WRITEW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+ FPCIEC_STANDARD_CONFIG_SLAVE0_SRC_ADDR_U(select_bounds),0) ;
    FPCIEC_HW_WRITEW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+ FPCIEC_STANDARD_CONFIG_SLAVE0_TRSL_ADDR(select_bounds),0) ;
    FPCIEC_HW_WRITEW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+ FPCIEC_STANDARD_CONFIG_SLAVE0_TRSL_ADDR_U(select_bounds),0) ;
    FPCIEC_HW_WRITEW(control_space,FPCIEC_STANDARD_CONFIG_FUN_NUM_GET(fun_num)+ FPCIEC_STANDARD_CONFIG_SLAVE0_TRSL_PARAM(select_bounds),0) ;

    instance_p->outbound_region_p[select_bounds] = 0 ;
    instance_p->outbound_region_map &= ~(1<<select_bounds) ;
    return FT_SUCCESS ;
}

/**
 * @name: FPcieCEpPioInit
 * @msg: Initializes the PIO memory ranges for the endpoint.
 * @param {FPcieC *} instance_p - Pointer to the FPcieC instance.
 * @param {FPcieCEpPioMemRange *} mem_range - Pointer to the memory range structure.
 * @return {void}
 */
void FPcieCEpPioInit(FPcieC *instance_p,FPcieCEpPioMemRange * mem_range)
{
    uintptr_t config_space = 0 ;
    FASSERT(instance_p != NULL);
    config_space = instance_p->config.config_space ;
    FASSERT(config_space != (uintptr_t)NULL) ;

    FPCIEC_EP_DEBUG_I("************ config_space is %p ********************* \r\n",config_space); 
    FPCIEC_EP_DEBUG_I("test addr is %p \r\n",config_space+FPCIEC_HPB_CX_PREF_BASE_LIMIT_OFFSET(instance_p->config.config_index)) ;
    FPCIEC_HW_WRITEW(config_space,FPCIEC_HPB_CX_PREF_BASE_LIMIT_OFFSET(instance_p->config.config_index),FPCIEC_HPB_CX_PREF_BASE(mem_range->pref_start)|FPCIEC_HPB_CX_PREF_LIMIT(mem_range->pref_end)) ;
    FPCIEC_HW_WRITEW(config_space,FPCIEC_HPB_CX_PREF_BASE_LIMIT_UP32_OFFSET(instance_p->config.config_index),FPCIEC_HPB_CX_PREF_BASE_UP32(mem_range->pref_start)|FPCIEC_HPB_CX_PREF_LIMIT_UP32(mem_range->pref_end)) ;
    FPCIEC_HW_WRITEW(config_space,FPCIEC_HPB_CX_MEM_BASE_LIMIT_OFFSET(instance_p->config.config_index),FPCIEC_HPB_CX_MEM_BASE(mem_range->mem_start)|FPCIEC_HPB_CX_MEM_LIMIT(mem_range->mem_end)) ;
}
