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
 * FilePath: fnand.c
 * Date: 2022-05-10 14:53:42
 * LastEditTime: 2022-05-10 08:56:27
 * Description:  This file is for  functions in this file are the minimum required functions
 * for this driver. 
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/05/10    first release
 */
#include "fnand.h"
#include "fnand_hw.h"
#include <stdio.h>
#include <string.h>
#include "fnand_id.h"
#include "fnand_common_cmd.h"
#include "fdebug.h"
#define FNAND_DEBUG_TAG "FNAND"
#define FNAND_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FNAND_DEBUG_TAG, format, ##__VA_ARGS__)
#define FNAND_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FNAND_DEBUG_TAG, format, ##__VA_ARGS__)
#define FNAND_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FNAND_DEBUG_TAG, format, ##__VA_ARGS__)

extern void FNandHwInit(uintptr_t base_address, FNandInterMode inter_mode);
extern void FNandHwReset(uintptr_t base_address);
extern void FNandEnable(uintptr_t base_address);
extern FError FNandToggleInit(FNand *instance_p, u32 chip_addr);
extern FError FNandOnfiInit(FNand *instance_p, u32 chip_addr);
extern FError FNandTimingInterfaceUpdate(FNand *instance_p, u32 chip_addr);
extern void FNandIsrEnable(FNand *instance_p, u32 int_mask);


/**
 * @name: FNandScan
 * @msg:  Nand scanning
 * @note:
 * @param {FNand} *instance_p is the pointer to the FNand instance.
 * @return {FT_SUCCESS} Scan nand is ok
 */
FError FNandScan(FNand *instance_p)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    return FNandDetect(instance_p);

}

u32 FNandCheckBusy(FNand *instance_p)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FNandConfig *config_p;
    config_p = &instance_p->config;

    return FNAND_READREG(config_p->base_address, FNAND_STATE_OFFSET) & FNAND_STATE_BUSY_OFFSET;
}


FError FNandSendCmd(FNand *instance_p, struct FNandDmaDescriptor *descriptor_p, FNandOperationType isr_type)
{
    FNandConfig *config_p;
    u32 timeout_cnt = 0;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(isr_type < FNAND_TYPE_NUM);

    config_p = &instance_p->config;

    FNandHwReset(config_p->base_address);

    if (0 != FNandCheckBusy(instance_p))
    {
        FNAND_DEBUG_E("Nand is busy");
        return FNAND_IS_BUSY;
    }

    /* write dma addr to register */
    FNAND_WRITEREG(config_p->base_address, FNAND_MADDR0_OFFSET, ((uintptr)descriptor_p) & FNAND_MADDR0_DT_LOW_ADDR_MASK);

#ifdef __aarch64__
    /* 将高位地址填入寄存器 */
    FNAND_CLEARBIT(config_p->base_address, FNAND_MADDR1_OFFSET, FNAND_MADDR1_DT_HIGH_8BITADDR_MASK);
    FNAND_SETBIT(config_p->base_address, FNAND_MADDR1_OFFSET, ((uintptr)descriptor_p >> 32) & FNAND_MADDR1_DT_HIGH_8BITADDR_MASK);
#else
    FNAND_CLEARBIT(config_p->base_address, FNAND_MADDR1_OFFSET, FNAND_MADDR1_DT_HIGH_8BITADDR_MASK);
#endif
    /* 中断模式操作 */
    if (instance_p->work_mode == FNAND_WORK_MODE_ISR)
    {
        if (isr_type == FNAND_CMD_TYPE)
        {
            FNandIsrEnable(instance_p, FNAND_INTRMASK_CMD_FINISH_MASK);
        }
        else if (isr_type == FNAND_WRITE_PAGE_TYPE)
        {
            FNandIsrEnable(instance_p, FNAND_INTRMASK_PGFINISH_MASK);
        }
        else if (isr_type == FNAND_READ_PAGE_TYPE)
        {
            FNandIsrEnable(instance_p, FNAND_INTRMASK_DMA_PGFINISH_MASK);
        }
        else if (isr_type == FNAND_WAIT_ECC_TYPE)
        {
            FNandIsrEnable(instance_p, FNAND_INTRMASK_ECC_FINISH_MASK);
        }
    }

    FNAND_SETBIT(config_p->base_address, FNAND_MADDR1_OFFSET, FNAND_MADDR1_DMA_EN_MASK);

    if (instance_p->work_mode == FNAND_WORK_MODE_ISR && (instance_p->wait_irq_fun_p != NULL))
    {
        if (instance_p->wait_irq_fun_p)
        {
            if (instance_p->wait_irq_fun_p(instance_p->wait_args) != FT_SUCCESS)
            {
                FNAND_DEBUG_E("wait_irq_fun_p is failed");
                return FNAND_ERR_IRQ_OP_FAILED;
            }
        }
        else
        {
            FNAND_DEBUG_E("The member wait_irq_fun_p of instance_p is null");
            FNAND_WRITEREG(config_p->base_address, FNAND_INTRMASK_OFFSET, FNAND_INTRMASK_ALL_INT_MASK);
            return FNAND_ERR_IRQ_LACK_OF_CALLBACK;
        }

        return  FT_SUCCESS ;
    }
    else
    {
        if (isr_type == FNAND_CMD_TYPE)
        {
            while (0 == (FNAND_READREG(config_p->base_address, FNAND_STATE_OFFSET) & FNAND_STATE_CMD_PGFINISH_OFFSET))
            {
                if (timeout_cnt++ >= 0xffffff)
                {
                    FNAND_DEBUG_E("FNAND_CMD_TYPE is sending timeout");
                    return FNAND_OP_TIMEOUT;
                }
            }
        }
        else if (isr_type == FNAND_WRITE_PAGE_TYPE)
        {
            while (0 == (FNAND_READREG(config_p->base_address, FNAND_STATE_OFFSET) & FNAND_STATE_PG_PGFINISH_OFFSET))
            {
                if (timeout_cnt++ >= 0xffffff)
                {
                    FNAND_DEBUG_E("FNAND_CMD_TYPE is sending timeout");
                    return FNAND_OP_TIMEOUT;
                }
            }
        }
        else if (isr_type == FNAND_READ_PAGE_TYPE)
        {
            while (0 == (FNAND_READREG(config_p->base_address, FNAND_STATE_OFFSET) & FNAND_STATE_DMA_PGFINISH_OFFSET))
            {
                if (timeout_cnt++ >= 0xffffff)
                {
                    FNAND_DEBUG_E("FNAND_CMD_TYPE is sending timeout");
                    return FNAND_OP_TIMEOUT;
                }
            }
        }
        else if (isr_type == FNAND_WAIT_ECC_TYPE)
        {
            while (0 == (FNAND_READREG(config_p->base_address, FNAND_STATE_OFFSET) & FNAND_STATE_ECC_FINISH_OFFSET))
            {
                if (timeout_cnt++ >= 0xffffff)
                {
                    FNAND_DEBUG_E("FNAND_CMD_TYPE is sending timeout");
                    return FNAND_OP_TIMEOUT;
                }
            }
        }
    }

    return FT_SUCCESS;
}


/**
 * @name:  FNandOperationWaitIrqRegister
 * @msg:   When nand is sent in interrupt mode, the action that waits while the operation completes
 * @note:
 * @param {FNand} *instance_p is the pointer to the FNand instance.
 * @param {FNandOperationWaitIrqCallback} wait_irq_fun_p , When the user adds this function, return FT_SUCCESS reports success, otherwise failure
 * @param {void} *wait_args
 * @return {*}
 */
void FNandOperationWaitIrqRegister(FNand *instance_p, FNandOperationWaitIrqCallback wait_irq_fun_p, void *wait_args)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);

    instance_p->wait_irq_fun_p = wait_irq_fun_p;
    instance_p->wait_args = wait_args;
}



/**
 * @name: FNandCfgInitialize
 * @msg:  Initialize the NAND controller
 * @param {FNand} *instance_p is the pointer to the FNand instance.
 * @param {FNandConfig} * points to the FNand device configuration structure.
 * @return {FError} FT_SUCCESS if successful
 * @note:
 */
FError FNandCfgInitialize(FNand *instance_p,
                          FNandConfig *config_p)
{
    u32 i;
    FError ret;
    /* Assert arguments */
    FASSERT(instance_p != NULL);
    FASSERT(config_p != NULL);

    /* Clear instance memory and make copy of configuration */
    memset(instance_p, 0, sizeof(FNand));
    instance_p->config = *config_p;
    instance_p->is_ready = FT_COMPONENT_IS_READY;

    /* lsd config */
    FNAND_CLEARBIT(FLSD_CONFIG_BASE, 0xc0, 1);

    instance_p->work_mode = FNAND_WORK_MODE_ISR ; /* 默认采用中断模式 */
    for (i = 0; i < FNAND_CONNECT_MAX_NUM; i++)
    {
        instance_p->inter_mode[i] = FNAND_ASYN_SDR; /* 初始化阶段以异步模式启动 */
        instance_p->timing_mode[i] = FNAND_TIMING_MODE0 ;
        /*  初始化时序配置 */
        ret  = FNandTimingInterfaceUpdate(instance_p, i);
        if (ret != FT_SUCCESS)
        {
            FNAND_DEBUG_E("%s, FNandTimingInterfaceUpdate is error", __func__);
            return ret;
        }
    }

    FNandHwInit(instance_p->config.base_address, instance_p->inter_mode[0]);
    FNandHwReset(instance_p->config.base_address);

    /* init ecc strength */
    FNAND_CLEARBIT(instance_p->config.base_address, FNAND_CTRL0_OFFSET, FNAND_CTRL0_ECC_CORRECT_MAKE(7UL)); /*  clear all ecc_correct  */
    if (instance_p->config.ecc_strength == 0x8)
    {
        FNAND_SETBIT(instance_p->config.base_address, FNAND_CTRL0_OFFSET, FNAND_CTRL0_ECC_CORRECT_MAKE(7UL));
    }
    else if (instance_p->config.ecc_strength == 0x4)
    {
        FNAND_SETBIT(instance_p->config.base_address, FNAND_CTRL0_OFFSET, FNAND_CTRL0_ECC_CORRECT_MAKE(3UL));
    }
    else if (instance_p->config.ecc_strength == 0x2)
    {
        FNAND_SETBIT(instance_p->config.base_address, FNAND_CTRL0_OFFSET, FNAND_CTRL0_ECC_CORRECT_MAKE(1UL));
    }
    else
    {
        FNAND_SETBIT(instance_p->config.base_address, FNAND_CTRL0_OFFSET, FNAND_CTRL0_ECC_CORRECT_MAKE(0UL));
    }

    FNandEnable(instance_p->config.base_address);

    /* init bbm */
    FNandInitBbtDesc(instance_p);
    return (FT_SUCCESS);
}


/**
 * @name: FNandWritePage
 * @msg:  Write operations one page at a time, including writing page data and spare data
 * @note:
 * @param {FNand} *instance_p is the pointer to the FNand instance.
 * @param {u32} page_addr is the address to which the page needs to be written
 * @param {u8} *buffer is page writes a pointer to the buffer
 * @param {u32} page_copy_offset is the offset of the page writing , Buffer write data to 0 + page_copy_offset
 * @param {u32} length is page data write length
 * @param {u8} *oob_buffer is the data buffer pointer needs to be written to the spare space
 * @param {u32} oob_copy_offset  is the offset of the spare space writing , Buffer write data to page length + oob_copy_offset
 * @param {u32} oob_length is the length to be written to the spare space
 * @param {u32} chip_addr chip address
 * @return {FError} FT_SUCCESS ,write page is successful
 */
FError FNandWritePage(FNand *instance_p, u32 page_addr, u8 *buffer, u32 page_copy_offset, u32 length, u8 *oob_buffer, u32 oob_copy_offset, u32 oob_length, u32 chip_addr)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(chip_addr < FNAND_CONNECT_MAX_NUM);
    FASSERT(instance_p->write_hw_ecc_p);

    FNandOpData op_data =
    {
        .page_addr = page_addr,
        .page_buf = NULL,            /* page 数据缓存空间 */
        .page_offset = 0,            /* 从offset开始拷贝页数据 */
        .page_length = 0, /* 从offset开始拷贝页数据的长度 */
        .obb_required = 0,                /* obb 是否读取的标志位,1 需要操作oob 区域 */
        .oob_buf = NULL,         /* obb 数据缓存空间 */
        .oob_offset = 0,             /* 从offset开始拷贝页数据 */
        .oob_length = 0,               /* 从offset开始拷贝页数据的长度 */
        .chip_addr = chip_addr,                   /* 芯片地址 */
    };

    if (buffer && (length > 0))
    {
        op_data.page_buf = buffer;
        op_data.page_length = length;
        op_data.page_offset = page_copy_offset;
    }

    if (oob_buffer && (oob_length > 0))
    {
        op_data.obb_required = 1;
        op_data.oob_buf = oob_buffer;
        op_data.oob_length = oob_length;
        op_data.oob_offset = oob_copy_offset;
    }

    return instance_p->write_hw_ecc_p(instance_p, &op_data);
}

/**
 * @name: FNandWritePage
 * @msg:  Write operations one page at a time, including writing page data and spare data ,without hw ecc
 * @note:
 * @param {FNand} *instance_p is the pointer to the FNand instance.
 * @param {u32} page_addr is the address to which the page needs to be written
 * @param {u8} *buffer is page writes a pointer to the buffer
 * @param {u32} page_copy_offset is the offset of the page writing , Buffer write data to 0 + page_copy_offset
 * @param {u32} length is page data write length
 * @param {u8} *oob_buffer is the data buffer pointer needs to be written to the spare space
 * @param {u32} oob_copy_offset  is the offset of the spare space writing , Buffer write data to page length + oob_copy_offset
 * @param {u32} oob_length is the length to be written to the spare space
 * @param {u32} chip_addr chip address
 * @return {FError} FT_SUCCESS ,write page is successful
 */
FError FNandWritePageRaw(FNand *instance_p, u32 page_addr, u8 *buffer, u32 page_copy_offset, u32 length, u8 *oob_buffer, u32 oob_copy_offset, u32 oob_length, u32 chip_addr)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(chip_addr < FNAND_CONNECT_MAX_NUM);
    FASSERT(instance_p->write_hw_ecc_p);

    FNandOpData op_data =
    {
        .page_addr = page_addr,
        .page_buf = NULL,            /* page 数据缓存空间 */
        .page_offset = 0,            /* 从offset开始拷贝页数据 */
        .page_length = 0, /* 从offset开始拷贝页数据的长度 */
        .obb_required = 0,                /* obb 是否读取的标志位,1 需要操作oob 区域 */
        .oob_buf = NULL,         /* obb 数据缓存空间 */
        .oob_offset = 0,             /* 从offset开始拷贝页数据 */
        .oob_length = 0,               /* 从offset开始拷贝页数据的长度 */
        .chip_addr = chip_addr,                   /* 芯片地址 */
    };

    if (buffer && (length > 0))
    {
        op_data.page_buf = buffer;
        op_data.page_length = length;
        op_data.page_offset = page_copy_offset;
    }

    if (oob_buffer && (oob_length > 0))
    {
        op_data.obb_required = 1;
        op_data.oob_buf = oob_buffer;
        op_data.oob_length = oob_length;
        op_data.oob_offset = oob_copy_offset;
    }

    return instance_p->write_p(instance_p, &op_data);
}

/**
 * @name: FNandReadPage
 * @msg:  Read operations one page at a time, including reading page data and spare space data
 * @note:
 * @param {FNand} *instance_p is the pointer to the FNand instance.
 * @param {u32} page_addr is the address to which the page needs to be readed
 * @param {u8} *buffer is the buffer used by the user to read page data
 * @param {u32} page_copy_offset  is the offset of the page reading , Buffer read data from 0 + page_copy_offset of per page
 * @param {u32} length is page data read length
 * @param {u8} *oob_buffer is buffer that read data from the spare space
 * @param {u32} oob_copy_offset is the offset of the spare space reading , Buffer reads data from page length + oob_copy_offset
 * @param {u32} oob_length  is the length to be written to the spare space
 * @param {u32} chip_addr chip address
 * @return {FError} FT_SUCCESS is read  successful
 */
FError FNandReadPage(FNand *instance_p, u32 page_addr, u8 *buffer, u32 page_copy_offset, u32 length, u8 *oob_buffer, u32 oob_copy_offset, u32 oob_length, u32 chip_addr)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(chip_addr < FNAND_CONNECT_MAX_NUM);
    FASSERT(instance_p->read_hw_ecc_p);

    FNandOpData op_data =
    {
        .page_addr = page_addr,
        .page_buf = NULL,            /* page 数据缓存空间 */
        .page_offset = 0,            /* 从offset开始拷贝页数据 */
        .page_length = 0,            /* 从offset开始拷贝页数据的长度 */
        .obb_required = 0,           /* obb 是否读取的标志位,1 需要操作oob 区域 */
        .oob_buf = NULL,             /* obb 数据缓存空间 */
        .oob_offset = 0,             /* 从offset开始拷贝页数据 */
        .oob_length = 0,             /* 从offset开始拷贝页数据的长度 */
        .chip_addr = chip_addr,      /* 芯片地址 */
    };

    /* clear buffer */
    if (buffer && (length > 0))
    {
        op_data.page_buf = buffer;
        op_data.page_length = length;
        op_data.page_offset = page_copy_offset;
    }

    if (oob_buffer && (oob_length > 0))
    {
        op_data.obb_required = 1;
        op_data.oob_buf = oob_buffer;
        op_data.oob_length = oob_length;
        op_data.oob_offset = oob_copy_offset;
    }

    return instance_p->read_hw_ecc_p(instance_p, &op_data);
}

FError FNandReadPageRaw(FNand *instance_p, u32 page_addr, u8 *buffer, u32 page_copy_offset, u32 length, u8 *oob_buffer, u32 oob_copy_offset, u32 oob_length, u32 chip_addr)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(chip_addr < FNAND_CONNECT_MAX_NUM);
    FASSERT(instance_p->read_hw_ecc_p);

    FNandOpData op_data =
    {
        .page_addr = page_addr,
        .page_buf = NULL,            /* page 数据缓存空间 */
        .page_offset = 0,            /* 从offset开始拷贝页数据 */
        .page_length = 0,            /* 从offset开始拷贝页数据的长度 */
        .obb_required = 0,           /* obb 是否读取的标志位,1 需要操作oob 区域 */
        .oob_buf = NULL,             /* obb 数据缓存空间 */
        .oob_offset = 0,             /* 从offset开始拷贝页数据 */
        .oob_length = 0,             /* 从offset开始拷贝页数据的长度 */
        .chip_addr = chip_addr,      /* 芯片地址 */
    };

    /* clear buffer */
    if (buffer && (length > 0))
    {
        op_data.page_buf = buffer;
        op_data.page_length = length;
        op_data.page_offset = page_copy_offset;
    }

    if (oob_buffer && (oob_length > 0))
    {
        op_data.obb_required = 1;
        op_data.oob_buf = oob_buffer;
        op_data.oob_length = oob_length;
        op_data.oob_offset = oob_copy_offset;
    }

    return instance_p->read_p(instance_p, &op_data);
}

/**
 * @name: FNandEraseBlock
 * @msg:  erase block data
 * @note: 擦除之后增加read status 命令进行检查。（70h）
 * @param {FNand} *instance_p is the pointer to the FNand instance.
 * @param {u32} block   is block number
 * @param {u32} chip_addr is chip address
 * @return {FError} FT_SUCCESS is erase is successful
 */
FError FNandEraseBlock(FNand *instance_p, u32 block, u32 chip_addr)
{
    u32 page_address;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(chip_addr < FNAND_CONNECT_MAX_NUM);
    page_address = block * instance_p->nand_geometry[chip_addr].pages_per_block;
    return instance_p->erase_p(instance_p, page_address, chip_addr);
}



/**
 * @name: FNandReadPageOOb
 * @msg:  Read spare space fo per page
 * @note:
 * @param {FNand} *instance_p is the instance pointer
 * @param {u32} page_addr is the Row Address of the spare space needs to be read
 * @param {u8} *oob_buffer is the buffer used by the user to read spare space data
 * @param {u32} oob_copy_offset is the offset of the spare space reading , Buffer reads data from page length + page_copy_offset
 * @param {u32} oob_length is the length of data retrieved from spare space
 * @param {u32} chip_addr is chip address
 * @return {FError} FT_SUCCESS is read  successful
 */
FError FNandReadPageOOb(FNand *instance_p, u32 page_addr, u8 *oob_buffer, u32 oob_copy_offset, u32 oob_length, u32 chip_addr)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(chip_addr < FNAND_CONNECT_MAX_NUM);

    FNandOpData op_data =
    {
        .page_addr = page_addr,
        .page_buf = NULL,            /* page 数据缓存空间 */
        .page_offset = 0,            /* 从offset开始拷贝页数据 */
        .page_length = 0, /* 从offset开始拷贝页数据的长度 */
        .obb_required = 1,                /* obb 是否读取的标志位,1 需要操作oob 区域 */
        .oob_buf = oob_buffer,         /* obb 数据缓存空间 */
        .oob_offset = oob_copy_offset,             /* 从offset开始拷贝页数据 */
        .oob_length = oob_length,               /* 从offset开始拷贝页数据的长度 */
        .chip_addr = chip_addr,                   /* 芯片地址 */
    };

    return instance_p->read_oob_p(instance_p, &op_data);
}

/**
 * @name: FNandWritePageOOb
 * @msg:  write data to the spare space
 * @note:
 * @param {FNand} *instance_p is the instance pointer
 * @param {u32} page_addr  is the Row Address of the spare space needs to be write
 * @param {u8} *oob_buffer is buffer that writes data to the spare space
 * @param {u32} page_copy_offset is the offset of the spare space writing , Buffer write data to page length + page_copy_offset
 * @param {u32} oob_length is the length to be written to the spare space
 * @param {u32} chip_addr is chip address
 * @return {FError} FT_SUCCESS is write  successful
 */
FError FNandWritePageOOb(FNand *instance_p, u32 page_addr, u8 *oob_buffer, u32 page_copy_offset, u32 oob_length, u32 chip_addr)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(chip_addr < FNAND_CONNECT_MAX_NUM);

    FNandOpData op_data =
    {
        .page_addr = page_addr,
        .page_buf = NULL,            /* page 数据缓存空间 */
        .page_offset = 0,            /* 从offset开始拷贝页数据 */
        .page_length = 0, /* 从offset开始拷贝页数据的长度 */
        .obb_required = 1,                /* obb 是否读取的标志位,1 需要操作oob 区域 */
        .oob_buf = oob_buffer,         /* obb 数据缓存空间 */
        .oob_offset = page_copy_offset,             /* 从offset开始拷贝页数据 */
        .oob_length = oob_length,               /* 从offset开始拷贝页数据的长度 */
        .chip_addr = chip_addr,                   /* 芯片地址 */
    };

    return instance_p->write_oob_p(instance_p, &op_data);
}
