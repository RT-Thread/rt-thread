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
 * FilePath: fpcie_hw.h
 * Date: 2022-08-10 14:55:11
 * LastEditTime: 2022-08-18 08:58:22
 * Description: This file is for pcie register definition.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe  2022/8/18   init commit
 */

#ifndef FPCIE_HW_H
#define FPCIE_HW_H

#include "ftypes.h"
#include "fio.h"
#include "ferror_code.h"

#ifdef __cplusplus
extern "C"
{
#endif

/***************************** Include Files *********************************/

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/* config register */
#define FPCIE_REG_MISC_INT_STATE_OFFSET 0x00000008U /* 杂散中断状态寄存器 */
#define FPCIE_REG_MISC_INT_ENALBE_OFFSET 0x0000000CU /* 杂散中断是能寄存器 */
#define FPCIE_REG_MSI_ENABLE_OFFSET 0x000000200U     /* MSI 中断使能寄存器 */
#define FPCIE_REG_MSI_UP32_ADDR_OFFSET 0x000000208U  /* 匹配 MSI 的高 32 位地址寄存器 */
#define FPCIE_REG_MSI_LOW32_ADDR_OFFSET 0x00000020CU /* 匹配 MSI 的低 32 位地址寄存器 */
#define FPCIE_REG_MSI_SPI_ENABLE_OFFSET 0x000000608U /*  MSI 转 SPI 的使能寄存器 */
#define FPCIE_REG_MSI_SPI_DATA_OFFSET 0x00000060CU   /* MSI 转 SPI 后的 ID 和数据信息寄存器 */
#define FPCIE_REG_EP_C0_PREF_BASE_LIMIT_OFFSET 0x000000A30U /* EP 模式下 PIO 请求译码到 C0 控制器 的可预取空间的 BASE 和 LIMIT 域  */
#define FPCIE_REG_EP_C0_PREF_BASE_LIMIT_UP32_OFFSET 0x000000A34U /* EP 模式下 PIO 请求译码到 C0 控制器的可预取空间的高 32 位 BASE 和 sLIMIT */
#define FPCIE_REG_EP_C0_MEM_BASE_LIMIT_OFFSET 0x000000A38U       /* EP 模式下 PIO 请求译码到 C1 控制器的存储空间的 BASE 和 LIMIT 域 */
#define FPCIE_REG_EP_C1_PREF_BASE_LIMIT_OFFSET 0x000000A40U
#define FPCIE_REG_EP_C1_PREF_BASE_LIMIT_UP32_OFFSET 0x000000A44U
#define FPCIE_REG_EP_C1_MEM_BASE_LIMIT_OFFSET 0x000000A48U
#define FPCIE_REG_EP_C2_PREF_BASE_LIMIT_OFFSET 0x000000A50U
#define FPCIE_REG_EP_C2_PREF_BASE_LIMIT_UP32_OFFSET 0x000000A54U
#define FPCIE_REG_EP_C2_MEM_BASE_LIMIT_OFFSET 0x000000A58U

/* Controler register */
#define FPCIE_REG_MSI_LOW_ADDRESS_OFFSET 0x94U     /* MSI 事务的写地址低 32 位 */
#define FPCIE_REG_MSI_HIGH_ADDRESS_OFFSET 0x98U    /* MSI 事务的写地址高 32 位 */
#define FPCIE_REG_MSI_DATA_OFFSET 0x9CU            /* MSI 事务携带的数据信息 */
#define FPCIE_REG_OUTBOUND_R0_PATR0_OFFSET 0x8000U /* 控制器输出方向上 region 0 的转换后地址低 32 位 */
#define FPCIE_REG_OUTBOUND_R0_PATR1_OFFSET 0x8004U /* 控制器输出方向上 region 0 的转换后地址高 32 位 */
#define FPCIE_REG_OUTBOUND_R0_PHDR0_OFFSET 0x8008U /* 控制器输出方向上 region 0 的转换描述符[31:0]位  */
#define FPCIE_REG_OUTBOUND_R0_PHDR1_OFFSET 0x800CU /* 控制器输出方向上 region 0 的转换描述符[63:31]位 */
#define FPCIE_REG_OUTBOUND_R0_PHDR2_OFFSET 0x8010U /* 控制器输出方向上 region 0 的转换描述符[95:64]位 */
#define FPCIE_REG_OUTBOUND_R0_ARBA0_OFFSET 0x8018U /* 控制器输出方向上 region 0 的转换前的地址低 32 位 */
#define FPCIE_REG_OUTBOUND_R0_ARBA1_OFFSET 0x801CU /* 控制器输出方向上 region 0 的转换前的地址高 32 位 */
#define FPCIE_REG_F0_B0_ATR_L_OFFSET 0x8840U       /* 控制器 FUNC 0 BAR 0 地址转换寄存器低 32 位 */
#define FPCIE_REG_F0_B0_ATR_H_OFFSET 0x8844U       /* 控制器 FUNC 0 BAR 0 地址转换寄存器高 32 位 */
#define FPCIE_REG_F0_B2_ATR_L_OFFSET 0x8850U       /* 控制器 FUNC 0 BAR 2 地址转换寄存器低 32 位 */
#define FPCIE_REG_F0_B2_ATR_H_OFFSET 0x8854U       /*  控制器 FUNC 0 BAR 2 地址转换寄存器高 32 位 */
#define FPCIE_REG_DMA_CH0_CTRL_OFFSET 0xC000U      /* DMA channel 0 的控制器寄存器 */
#define FPCIE_REG_DMA_CH0_SP_L_OFFSET 0xC004U      /* DMA channel 0 描述符存储的首地址低 32 位寄存器 */
#define FPCIE_REG_DMA_CH0_SP_H_OFFSET 0xC008U      /* DMA channel 0 描述符存储的首地址高 32 位寄存器 */
#define FPCIE_REG_DMA_CH1_CTRL_OFFSET 0xC014U      /* DMA channel 1 的控制器寄存器 */
#define FPCIE_REG_DMA_CH1_SP_L_OFFSET 0xC018U      /* DMA channel 1 描述符存储的首地址低 32 位寄存器 */
#define FPCIE_REG_DMA_CH1_SP_H_OFFSET 0xC01CU      /* DMA channel 1 描述符存储的首地址高 32 位寄存器 */
#define FPCIE_REG_DMA_INT_STATUS_OFFSET 0xC0A0U    /* DMA 中断状态寄存器 */
#define FPCIE_REG_DMA_INT_ENABLE_OFFSET 0xC0A4U    /* DMA 使能寄存器 */

/* REG_MISC_INT_STATE */
#define FPCIE_MISC_STATE_C0_DMA_INT_MASK 0x1U                   /* c0 dma 中断 */
#define FPCIE_MISC_STATE_C0_LOCAL_INT_MASK 0x2U                 /* c0 本地中断 */
#define FPCIE_MISC_STATE_C0_POWER_STATE_CHANGE_MASK 0x4U        /* c0 电源状态变化 */
#define FPCIE_MISC_STATE_C1_DMA_INT_MASK 0x100U                 /* c1 dma 中断 */
#define FPCIE_MISC_STATE_C1_LOCAL_INT_MASK 0x200U               /* c1 本地中断 */
#define FPCIE_MISC_STATE_C1_POWER_STATE_CHANGE_MASK 0x400U      /* c1 电源状态变化 */
#define FPCIE_MISC_STATE_C2_DMA_INT_MASK 0x1000U                /* c2 dma 中断 */
#define FPCIE_MISC_STATE_C2_LOCAL_INT_MASK 0x2000U              /* c2 本地中断 */
#define FPCIE_MISC_STATE_C2_POWER_STATE_CHANGE_MASK 0x4000U     /* c2 电源状态变化 */

/* REG_MISC_INT_ENALBE */
#define FPCIE_MISC_ENALBE_C0_MISC_INT_EN_MASK 0x1U              /* c0 杂散中断使能 */
#define FPCIE_MISC_ENALBE_C1_MISC_INT_EN_MASK 0x2U              /* c1 杂散中断使能 */
#define FPCIE_MISC_ENALBE_C2_MISC_INT_EN_MASK 0x4U              /* c2 杂散中断使能 */

/* REG_MSI_ENABLE */
#define FPCIE_MSI_EN_MASK 0x1U                                  /* MSI 中断使能 */

/* REG_MSI_UP32_ADDR */
#define FPCIE_MSI64_HI_ADDR_OFFSET 0xFFFFFFFFU                  /* MSI64 高位地址 */

/* REG_MSI_LOW32_ADDR */
#define FPCIE_MSI64_LO_ADDR_MASK 0xFFFF0000U                    /* MSI64 低位地址 */

/* REG_MSI_SPI_ENABLE */
#define FPCIE_MSI_DATA_MASK 0xFFFFU                             /* msi 中断的数据 */
#define FPCIE_MSI_DEVICE_ID_MASK 0xFFFF0000U                    /* msi 中断的设备 id */

/* REG_EP_C0_PREF_BASE_LIMIT */
#define FPCIE_C0_PREF_BASE_MASK 0xfff0U                         /* 可预取存储空间基址低位 */
#define FPCIE_C0_PREF_LIMIT_MASK 0xfff00000U                    /* 可预取存储空间上限低位 */

/* REG_EP_C0_PREF_BASE_LIMIT_UP32 */
#define FPCIE_C0_PREF_BASE_UP32_MASK 0xFFU                      /* 可预取存储空间基址高位 */
#define FPCIE_C0_PREF_LIMIT_UP32_MASK 0xFF00U                   /* 可预取存储空间上限高位 */

/* REG_EP_C1_PREF_BASE_LIMIT */
#define FPCIE_C1_PREF_BASE_MASK 0xfff0U                         /* 可预取存储空间基址低位 */
#define FPCIE_C1_PREF_LIMIT_MASK 0xfff00000U                    /* 可预取存储空间上限低位 */

/* REG_EP_C1_PREF_BASE_LIMIT_UP32 */
#define FPCIE_C1_PREF_BASE_UP32_MASK 0xFFU                      /* 可预取存储空间基址高位 */
#define FPCIE_C1_PREF_LIMIT_UP32_MASK 0xFF00U                   /* 可预取存储空间上限高位 */

/* Controler register */
/* REG_MSI_LOW_ADDRESS */
#define FPCIE_CTRL_MSI_LOW_ADDR_MASK 0xFFFFFFFCU                /* MSI 事务的写地址低位 */

/* REG_MSI_HIGH_ADDRESS */
#define FPCIE_CTRL_MSI_HIGH_ADDR_MASK 0xFFFFFFFFU               /* MSI 事务的写地址高 32 位 */

/* REG_MSI_DATA */
#define FPCIE_CTRL_MESSAGE_DATA_MASK 0xffffU                    /* MSI 事务携带的数据信息 */

/* REG_OUTBOUND_R0_PATR0 */
#define FPCIE_CTRL_OUTBOUND_R0_PATR0_R0_NUM_BITS_MASK 0x1fU     /* 配置可通过的 AXI 域地址，例如配置为 N，那么N+1 位地址可通过。 */
#define FPCIE_CTRL_OUTBOUND_R0_PATR0_ADDR_BITS_MASK 0xffffff00U /* 控制器输出方向 region 0 转换后的地址[31:8]位 */

/* REG_OUTBOUND_R0_PATR1 */
#define FPCIE_CTRL_OUTBOUND_R0_PATR1_ADDR_BITS_MASK 0xffffffffU /* 控制器输出方向 region 0 转换后的地址[63:32]位 */

/* REG_OUTBOUND_R0_PHDR0 */
#define FPCIE_CTRL_OUTBOUND_R0_PHDR0_DESCRIPTOR_MASK 0xffffffffU /* 控制器输出方向 region 0 的描述符[31:0]位 */

/* REG_OUTBOUND_R0_PHDR1 */
#define FPCIE_CTRL_OUTBOUND_R0_PHDR1_DESCRIPTOR_MASK 0xffffffffU /* 控制器输出方向 region 0 的描述符[63:32]位 */

/* REG_OUTBOUND_R0_PHDR2 */
#define FPCIE_CTRL_OUTBOUND_R0_PHDR2_DESCRIPTOR_MASK 0x1fffU     /* 控制器输出方向 region 0 的描述符[76:64]位 */

/* REG_OUTBOUND_R0_ARBA0 */
#define FPCIE_CTRL_OUTBOUND_R0_ARBA0_LOWER_MASK 0x3f             /* 配置AXI域匹配地址时的mask位，例如配置为M，那么 M+1 位地址在匹配时不做比较。 */
#define FPCIE_CTRL_OUTBOUND_R0_ARBA0_ADDR_MASK 0xFFFFFFF0U       /* 控制器输出方向 region 0 转换前的地址[31:8]位 */

/* REG_OUTBOUND_R0_ARBA1 */
#define FPCIE_CTRL_OUTBOUND_R0_ARBA1_ADDR_MASK 0xffffffffU       /* 控制器输出方向 region 0 转换前的地址[63:32]位 */

/* REG_F0_B0_ATR_L */
#define FPCIE_CTRL_F0_B0_ATR_L_ADDR_MASK 0xffffffffU             /* 控制器 FUNC 0 BAR 0 地址转换寄存器低 32 位 */

/* REG_F0_B0_ATR_H */
#define FPCIE_CTRL_F0_B0_ATR_H_ADDR_MASK 0xffffffffU            /* 控制器 FUNC 0 BAR 0 地址转换寄存器高 32 位 */

/* REG_F0_B2_ATR_L */
#define FPCIE_CTRL_F0_B2_ATR_L_ADDR_MASK 0xffffffffU            /* 控制器 FUNC 0 BAR 2 地址转换寄存器低 32 位 */

/* REG_F0_B2_ATR_H */
#define FPCIE_CTRL_F0_B2_ATR_H_ADDR_MASK 0xffffffffU            /* 控制器 FUNC 0 BAR 2 地址转换寄存器高 32 位 */

/* REG_DMA_CH0_CTRL */
#define FPCIE_CTRL_DMA_CH0_CTRL_GO_MASK 0x1U                    /* DMA channel 0 点火位，开始传输 */
#define FPCIE_CTRL_DMA_CH0_CTRL_OBNOTIB_MASK 0x2U               /* 配置 DMA channel 0 是读操作还是写操作 */

/* REG_DMA_CH0_SP_L */
#define FPCIE_CTRL_DMA_CH0_SP_L_START_MASK 0xFFFFFFFFU          /* 保存 channel 0 描述符的内存地址低 32 位 */

/* REG_DMA_CH0_SP_H */
#define FPCIE_CTRL_DMA_CH0_SP_H_START_MASK 0xFFFFFFFFU          /* 保存 channel 0 描述符的内存地址高 32 位 */

/* REG_DMA_CH1_CTRL */
#define FPCIE_CTRL_DMA_CH1_CTRL_GO_MASK 0x1U                    /* DMA channel 1 点火位，开始传输 */
#define FPCIE_CTRL_DMA_CH1_CTRL_OBNOTIB_MASK 0x2U               /* 配置 DMA channel 1 是读操作还是写操作 */

/* REG_DMA_CH1_SP_L */
#define FPCIE_CTRL_DMA_CH1_SP_L_START_MASK 0xFFFFFFFFU          /* 保存 channel 1 描述符的内存地址低 32 位 */

/* REG_DMA_CH1_SP_H */
#define FPCIE_CTRL_DMA_CH1_SP_H_START_MASK 0xFFFFFFFFU          /* 保存 channel 1 描述符的内存地址高 32 位 */

/* REG_DMA_INT_STATUS */
#define FPCIE_CTRL_DMA_INT_STATUS_CH0_DONE_MASK 0x1U            /* channel 0 传输完成中断 */
#define FPCIE_CTRL_DMA_INT_STATUS_CH1_DONE_MASK 0x2U            /* channel 1 传输完成中断 */
#define FPCIE_CTRL_DMA_INT_STATUS_CH0_ERR_MASK 0x10U            /* channel 0 传输出错中断 */
#define FPCIE_CTRL_DMA_INT_STATUS_CH1_ERR_MASK 0x20U            /* channel 1 传输出错中断 */
#define FPCIE_CTRL_DMA_INT_STATUS_ALL_MASK (FPCIE_CTRL_DMA_INT_STATUS_CH0_DONE_MASK | FPCIE_CTRL_DMA_INT_STATUS_CH1_DONE_MASK | FPCIE_CTRL_DMA_INT_STATUS_CH0_ERR_MASK | FPCIE_CTRL_DMA_INT_STATUS_CH1_ERR_MASK)

/* REG_DMA_INT_ENABLE */
#define FPCIE_CTRL_DMA_INT_ENABLE_CH0_DONE_MASK 0x1U            /*  使能 channel 0 传输完成后产生中断 */
#define FPCIE_CTRL_DMA_INT_ENABLE_CH1_DONE_MASK 0x2U            /*  使能 channel 1 传输完成后产生中断 */
#define FPCIE_CTRL_DMA_INT_ENABLE_CH0_ERR_MASK 0x10U            /*  使能 channel 0 传输出错后产生中断 */
#define FPCIE_CTRL_DMA_INT_ENABLE_CH1_ERR_MASK 0x20U            /*  使能 channel 1 传输出错后产生中断 */
#define FPCIE_CTRL_DMA_INT_ENABLE_ALL_MASK (FPCIE_CTRL_DMA_INT_ENABLE_CH0_DONE_MASK | FPCIE_CTRL_DMA_INT_ENABLE_CH1_DONE_MASK | FPCIE_CTRL_DMA_INT_ENABLE_CH0_ERR_MASK | FPCIE_CTRL_DMA_INT_ENABLE_CH1_ERR_MASK)

/** @name ECAM Address Register bitmaps and masks
 *
 * @{
 */
#define FPCIE_ECAM_MASK 0x0FFFFFFF     /**< Mask of all valid bits */
#define FPCIE_ECAM_BUS_MASK 0x0FF00000 /**< Bus Number Mask */
#define FPCIE_ECAM_DEV_MASK 0x000F8000 /**< Device Number Mask */
#define FPCIE_ECAM_FUN_MASK 0x00007000 /**< Function Number Mask */
#define FPCIE_ECAM_REG_MASK 0x00000FFC /**< Register Number Mask */
#define FPCIE_ECAM_BYT_MASK 0x00000003 /**< Byte Address Mask */

#define FPCIE_ECAM_BUS_SHIFT 20 /**< Bus Number Shift Value */
#define FPCIE_ECAM_DEV_SHIFT 15 /**< Device Number Shift Value */
#define FPCIE_ECAM_FUN_SHIFT 12 /**< Function Number Shift Value */
#define FPCIE_ECAM_REG_SHIFT 2  /**< Register Number Shift Value */
#define FPCIE_ECAM_BYT_SHIFT 0  /**< Byte Offset Shift Value */

#define FPCIE_BUS(d)        (((d) >> 16) & 0xff)
/*
 * Please note the difference in DEVFN usage in U-Boot vs Linux. U-Boot
 * uses DEVFN in bits 15-8 but Linux instead expects DEVFN in bits 7-0.
 * Please see the Linux header include/uapi/linux/pci.h for more details.
 * This is relevant for the following macros:
 * FPCIE_DEV, FPCIE_FUNC, FPCIE_DEVFN
 * The U-Boot macro FPCIE_DEV is equivalent to the Linux FPCIE_SLOT version with
 * the remark from above (input d in bits 15-8 instead of 7-0.
 */
#define FPCIE_DEV(d)        (((d) >> 11) & 0x1f)
#define FPCIE_FUNC(d)       (((d) >> 8) & 0x7)
#define FPCIE_DEVFN(d, f)       ((d) << 11 | (f) << 8)

#define FPCIE_MASK_BUS(bdf) ((bdf) & 0xffff)
#define FPCIE_ADD_BUS(bus, devfn)   (((bus) << 16) | (devfn))
#define FPCIE_BDF(b, d, f)  ((b) << 16 | FPCIE_DEVFN(d, f))
#define FPCIE_VENDEV(v, d)  (((v) << 16) | (d))
#define FPCIE_ANY_ID        (~0)

/**
*
* This macro reads the given register.
*
* @param    base_addr is the base address of the device.
* @param    reg_offset is the register offset to be read.
*
* @return   The 32-bit value of the register
*
* @note     None.
*
*****************************************************************************/
#define FPCIE_READREG(base_addr, reg_offset) \
    FtIn32((base_addr) + (u32)(reg_offset))

/****************************************************************************/
/**
*
* This macro writes the given register.
*
* @param    base_addr is the base address of the device.
* @param    reg_offset is the register offset to be written.
* @param    data is the 32-bit value to write to the register.
*
* @return   None.
*
* @note     None.
*
*****************************************************************************/
#define FPCIE_WRITEREG(base_addr, reg_offset, data) \
    FtOut32((base_addr) + (u32)(reg_offset), (u32)(data))

#define FPCIE_READREG_BYTE(base_addr, reg_offset) \
    FtIn8((base_addr) + (u32)(reg_offset))

#define FPCIE_WRITEREG_BYTE(base_addr, reg_offset, data) \
    FtOut8((base_addr) + (u32)(reg_offset), (u8)(data))


#define FPCIE_READREG_SHORT(base_addr, reg_offset) \
    FtIn16((base_addr) + (u32)(reg_offset))

#define FPCIE_WRITEREG_SHORT(base_addr, reg_offset, data) \
    FtOut16((base_addr) + (u32)(reg_offset), (u16)(data))


#define FPCIE_SETBIT(base_addr, reg_offset, data) \
    FtSetBit32((base_addr) + (u32)(reg_offset), (u32)(data))

#define FPCIE_CLEARBIT(base_addr, reg_offset, data) \
    FtClearBit32((base_addr) + (u32)(reg_offset), (u32)(data))


/************************** Function Prototypes ******************************/


void FPcieEcamReadConfig8bit(uintptr ecam_addr, s32 bdf, u32 offset, u8 *value_p);

void FPcieEcamReadConfig16bit(uintptr ecam_addr, s32 bdf, u32 offset, u16 *value_p);

void FPcieEcamReadConfig32bit(uintptr ecam_addr, s32 bdf, u32 offset, u32 *value_p);


void FPcieEcamWriteConfig8bit(uintptr ecam_addr, s32 bdf, u32 offset, u8 value);

void FPcieEcamWriteConfig16bit(uintptr ecam_addr, s32 bdf, u32 offset, u16 value);

void FPcieEcamWriteConfig32bit(uintptr ecam_addr, s32 bdf, u32 offset, u32 value);

FError FPcieSkipDevice(uintptr ecam_addr, s32 bdf);

#ifdef __cplusplus
}
#endif

#endif // !