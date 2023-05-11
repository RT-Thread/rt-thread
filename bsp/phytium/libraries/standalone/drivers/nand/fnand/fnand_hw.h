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
 * FilePath: fnand_hw.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:56:40
 * Description:  This file contains macros that can be used to access the device.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/05/10    first release
 */


#ifndef FNAND_HW_H
#define FNAND_HW_H


#include "fkernel.h"
#include "ftypes.h"
#include "fio.h"
#include "fkernel.h"


#ifdef __cplusplus
extern "C"
{
#endif


#define FNAND_CTRL0_OFFSET 0x00000000U
#define FNAND_CTRL1_OFFSET 0x00000004U
#define FNAND_MADDR0_OFFSET 0x00000008U
#define FNAND_MADDR1_OFFSET 0x0000000CU
/* ASY */
#define FNAND_ASY_TIMING0_OFFSET 0x00000010U
#define FNAND_ASY_TIMING1_OFFSET 0x00000014U
#define FNAND_ASY_TIMING2_OFFSET 0x00000018U
#define FNAND_ASY_TIMING3_OFFSET 0x0000001CU
#define FNAND_ASY_TIMING4_OFFSET 0x00000020U
#define FNAND_ASY_TIMING5_OFFSET 0x00000024U
/* SYN */
#define FNAND_SYN_TIMING6_OFFSET 0x00000028U
#define FNAND_SYN_TIMING7_OFFSET 0x0000002CU
#define FNAND_SYN_TIMING8_OFFSET 0x00000030U
#define FNAND_SYN_TIMING9_OFFSET 0x00000034U
#define FNAND_SYN_TIMING10_OFFSET 0x00000038U
#define FNAND_SYN_TIMING11_OFFSET 0x0000003CU
#define FNAND_SYN_TIMING12_OFFSET 0x00000040U
/* TOG */
#define FNAND_TOG_TIMING13_OFFSET 0x00000044U
#define FNAND_TOG_TIMING14_OFFSET 0x00000048U
#define FNAND_TOG_TIMING15_OFFSET 0x0000004CU
#define FNAND_TOG_TIMING16_OFFSET 0x00000050U
#define FNAND_TOG_TIMING17_OFFSET 0x00000054U
#define FNAND_TOG_TIMING18_OFFSET 0x00000058U

#define FNAND_FIFORSTA_OFFSET 0x0000005CU
#define FNAND_INTERVAL_OFFSET 0x00000060U
#define FNAND_CMDINTERVAL_OFFSET 0x00000064U
#define FNAND_FIFO_TIMEOUT_OFFSET 0x00000068U
#define FNAND_FIFO_LEVEL0_FULL_OFFSET 0x0000006CU
#define FNAND_FIFO_LEVEL1_EMPTY_OFFSET 0x00000070U
#define FNAND_WP_OFFSET 0x00000074U
#define FNAND_FIFO_FREE_OFFSET 0x00000078U
#define FNAND_STATE_OFFSET 0x0000007CU
#define FNAND_INTRMASK_OFFSET 0x00000080U
#define FNAND_INTR_OFFSET 0x00000084U
#define FNAND_ERROR_CLEAR_OFFSET 0x0000008CU
#define FNAND_ERROR_LOCATION_OFFSET 0x000000B8U

/* FNAND_CTRL0_OFFSET */
#define FNAND_CTRL0_EN_MASK BIT(0)
#define FNAND_CTRL0_WIDTH_MASK BIT(1)                            /* DQ width, only for ONFI async mode. 0: 8bits, 1: 16bits*/
#define FNAND_CTRL0_INTER_MODE(x) (min((x), (0x3UL)) << 2)         /* Nand Flash interface mode. 00: ONFI Async; 01: ONFI Sync; 10: Toggle Async*/
#define FNAND_CTRL0_ECC_EN_MASK BIT(4)                           /* Nand Flash hardware ECC enable */
#define FNAND_CTRL0_ECC_CORRECT_MAKE(x) (min((x), (0x7UL)) << 5) /* Nand Flash ECC strength. 3'h2: 2bits; 3'h4: 4bits */
#define FNAND_CTRL0_SPARE_SIZE_EN_MASK BIT(8)                    /* Data with spare  */
#define FNAND_CTRL0_SPARE_SIZE_MASK GENMASK(31, 9)               /* Spare size */

/* FNAND_CTRL1_OFFSET */
// #define FNAND_CTRL1_SAMPL_PHASE_MASK GENMASK(15,0)   /* when onfi synchronization or toggle mode, the cycle of receive data sampling phase */
#define FNAND_CTRL1_SAMPL_PHASE_MAKE(x) (min((x), GENMASK(15, 0))) /* when onfi synchronization or toggle mode, the cycle of receive data sampling phase */
#define FNAND_CTRL1_ECC_DATA_FIRST_EN_MASK BIT(16)                 /* ECC data is read first and then the corresponding data is read */
#define FNAND_CTRL1_RB_SHARE_EN_MASK BIT(17)                       /* The R/B signal sharing function of four devices is enabled. Write 1 is enabled */
#define FNAND_CTRL1_ECC_BYPASS_MASK BIT(18)                        /* When the received ECC encoded address data is 13'hff, the ECC verification function is bypass. 1 indicates that the function is enabled */

/* FNAND_MADDR0_OFFSET */
#define FNAND_MADDR0_DT_LOW_ADDR_MASK GENMASK(31, 0) /* The lower 32 bits of the descriptor table header address in memory storage */

/* FNAND_MADDR1_OFFSET */
#define FNAND_MADDR1_DT_HIGH_8BITADDR_MASK GENMASK(7, 0)   /* The high 8 bits of the first address of the descriptor table stored in memory */
#define FNAND_MADDR1_DMA_EN_MASK BIT(8)                    /* DMA transfer enable bit. This bit is 1 for the controller to start DMA transfers */
#define FNAND_MADDR1_DMA_READ_LENGTH_MASK GENMASK(23, 16)  /* Sets the length to which dma reads data */
#define FNAND_MADDR1_DMA_WRITE_LENGTH_MASK GENMASK(31, 24) /* Sets the length to which dma writes data */

/* FNAND_ASY_TIMING0_OFFSET */
#define FNAND_ASY_TIMING0_TCLS_TWP_MASK GENMASK(31, 16) /* tCL-tWP */
#define FNAND_ASY_TIMING0_TCLS_TCS_MASK GENMASK(15, 0)  /* tCS-tCLS */

/* FNAND_ASY_TIMING1_OFFSET */
#define FNAND_ASY_TIMING1_TWH_MASK GENMASK(31, 16) /* tWH */
#define FNAND_ASY_TIMING1_TWP_MASK GENMASK(15, 0)  /* tWP */

/* FNAND_ASY_TIMING2_OFFSET */
#define FNAND_ASY_TIMING2_TCLH_TWH_MASK GENMASK(31, 16) /* tCLH-tWH */
#define FNAND_ASY_TIMING2_TCH_TCLH_MASK GENMASK(15, 0)  /* tCH-tCLH */

/* FNAND_ASY_TIMING3_OFFSET */
#define FNAND_ASY_TIMING3_TCH_TWH_MASK GENMASK(31, 16) /* tCH-tWH */
#define FNAND_ASY_TIMING3_TDQ_EN_MASK GENMASK(15, 0)

/* FNAND_ASY_TIMING4_OFFSET */
#define FNAND_ASY_TIMING4_TREH_MASK GENMASK(31, 16) /* TREH */
#define FNAND_ASY_TIMING4_TWHR_MASK GENMASK(15, 0)  /* TWHR */

/* FNAND_ASY_TIMING5_OFFSET */
#define FNAND_ASY_TIMING5_TADL_MASK GENMASK(31, 16)
#define FNAND_ASY_TIMING5_TRC_MASK GENMASK(15, 0)

/* FNAND_SYN_TIMING6_OFFSET */
#define FNAND_SYN_TIMING6_TCALS_TCH_MASK GENMASK(31, 16)
#define FNAND_SYN_TIMING6_TRC_MASK GENMASK(15, 0)

/* FNAND_SYN_TIMING7_OFFSET */
#define FNAND_SYN_TIMING7_TDQ_EN_MASK GENMASK(31, 16)
#define FNAND_SYN_TIMING7_TCK_MASK GENMASK(15, 0)

/* FNAND_SYN_TIMING8_OFFSET */
#define FNAND_SYN_TIMING8_TCK_MASK GENMASK(31, 16)
#define FNAND_SYN_TIMING8_TCAD_TCK_MASK GENMASK(15, 0)

/* FNAND_SYN_TIMING9_OFFSET */
#define FNAND_SYN_TIMING9_TCCS_MASK GENMASK(31, 16)
#define FNAND_SYN_TIMING9_TWHR_MASK GENMASK(15, 0)

/* FNAND_SYN_TIMING10_OFFSET */
#define FNAND_SYN_TIMING10_TCK_MASK GENMASK(31, 16)
#define FNAND_SYN_TIMING10_MTCK_MASK GENMASK(15, 0)

/* FNAND_SYN_TIMING11_OFFSET */
#define FNAND_SYN_TIMING11_TCK_TCALS_MASK GENMASK(15, 0)

/* FNAND_SYN_TIMING12_OFFSET */
#define FNAND_SYN_TIMING12_TCKWR_MASK GENMASK(31, 16)
#define FNAND_SYN_TIMING12_TWRCK_MASK GENMASK(15, 0)

/* FNAND_TOG_TIMING13_OFFSET */
#define FNAND_TOG_TIMING13_TWRPST_MASK GENMASK(31, 16)
#define FNAND_TOG_TIMING13_TWPRE_MASK GENMASK(15, 0)

/* FNAND_TOG_TIMING14_OFFSET */
#define FNAND_TOG_TIMING14_TCLS_TWP_MASK GENMASK(31, 16)
#define FNAND_TOG_TIMING14_TCS_TCLS_MASK GENMASK(15, 0)

/* FNAND_TOG_TIMING15_OFFSET */
#define FNAND_TOG_TIMING15_TWHR_MASK GENMASK(31, 16)
#define FNAND_TOG_TIMING15_TADL_MASK GENMASK(15, 0)

/* FNAND_TOG_TIMING16_OFFSET */
#define FNAND_TOG_TIMING16_TCLH_TWH_MASK GENMASK(31, 16)
#define FNAND_TOG_TIMING16_TCH_TCLH_MASK GENMASK(15, 0)

/* FNAND_TOG_TIMING17_OFFSET */
#define FNAND_TOG_TIMING17_TRPST_MASK GENMASK(31, 16)
#define FNAND_TOG_TIMING17_TRPRE_MASK GENMASK(15, 0)

/* FNAND_TOG_TIMING18_OFFSET */
#define FNAND_TOG_TIMING18_TRPSTH_MASK GENMASK(31, 16)
#define FNAND_TOG_TIMING18_DSC_MASK GENMASK(15, 0)

/* FNAND_FIFORSTA_OFFSET */
#define FNAND_FIFORSTA_FIFO_FULL_MASK BIT(11)
#define FNAND_FIFORSTA_FIFO_EMPTY_MASK BIT(10)
#define FNAND_FIFORSTA_FIFO_COUNT_MASK GENMASK(9, 0)

/* FNAND_INTERVAL_OFFSET */
// #define FNAND_INTERVAL_TIME_MASK GENMASK(15,0) /* The interval between commands, addresses, and data. The timeout increases by 2ns for every 1 increase in the write value */
#define FNAND_INTERVAL_TIME_MAKE(x) (min((x), (0xFFUL)))

/* FNAND_CMDINTERVAL_OFFSET */
#define FNAND_CMDINTERVAL_MASK GENMASK(31, 0) /* The interval between requests. The timeout increases by 2ns for every 1 increase in the write value */

/* FNAND_FIFO_TIMEOUT_OFFSET */
#define FNAND_FIFO_TIMEOUT_MASK GENMASK(31, 0) /* FIFO timeout counter, the timeout time increases by 2ns for each increment of the value written */

/* FNAND_FIFO_LEVEL0_FULL_OFFSET */
#define FNAND_FIFO_LEVEL0_FULL_THRESHOLD_MASK GENMASK(3, 0)

/* FNAND_FIFO_LEVEL1_EMPTY_OFFSET */
#define FNAND_FIFO_LEVEL1_EMPTY_THRESHOLD_MASK GENMASK(3, 0)

/* FNAND_WP_OFFSET */
#define FNAND_WP_EN_MASK BIT(0)

/* FNAND_FIFO_FREE_OFFSET */
#define FNAND_FIFO_FREE_MASK BIT(0)

/* FNAND_STATE_OFFSET */
#define FNAND_STATE_BUSY_OFFSET BIT(0)         /* nandflash控制器忙 */
#define FNAND_STATE_DMA_BUSY_OFFSET BIT(1)     /* dma控制器忙 */
#define FNAND_STATE_DMA_PGFINISH_OFFSET BIT(2) /* dma数据操作完成 */
#define FNAND_STATE_DMA_FINISH_OFFSET BIT(3)   /* dma完成 */
#define FNAND_STATE_FIFO_EMP_OFFSET BIT(4)
#define FNAND_STATE_FIFO_FULL_OFFSET BIT(5)
#define FNAND_STATE_FIFO_TIMEOUT_OFFSET BIT(6)
#define FNAND_STATE_CS_OFFSET GENMASK(10, 7)
#define FNAND_STATE_CMD_PGFINISH_OFFSET BIT(11) /* nand接口命令操作完成 */
#define FNAND_STATE_PG_PGFINISH_OFFSET BIT(12)  /* nand接口数据操作完成 */
#define FNAND_STATE_RE_OFFSET BIT(13)           /* re_n门控状态 */
#define FNAND_STATE_DQS_OFFSET BIT(14)          /* dqs门控状态 */
#define FNAND_STATE_RB_OFFSET BIT(15)           /* RB_N接口的状态 */
#define FNAND_STATE_ECC_BUSY_OFFSET BIT(16)
#define FNAND_STATE_ECC_FINISH_OFFSET BIT(17)
#define FNAND_STATE_ECC_RIGHT_OFFSET BIT(18)
#define FNAND_STATE_ECC_ERR_OFFSET BIT(19)      /* ECC 校验有错 */
#define FNAND_STATE_ECC_ERROVER_OFFSET BIT(20) /* 错误超过可校验范围  */
#define FNAND_STATE_AXI_DSP_ERR_OFFSET BIT(21) /* 描述符错误 */
#define FNAND_STATE_AXI_RD_ERR_OFFSET BIT(22)
#define FNAND_STATE_AXI_WR_ERR_OFFSET BIT(23)
#define FNAND_STATE_RB_N_OFFSET GENMASK(27, 24)
#define FNAND_STATE_PROT_ERR_OFFSET BIT(28)
#define FNAND_STATE_ECCBYPASS_STA_OFFSET BIT(29)
#define FNAND_STATE_ALL_BIT GENMASK(29, 0)

/* FNAND_INTRMASK_OFFSET */
#define FNAND_INTRMASK_ALL_INT_MASK GENMASK(17, 0)
#define FNAND_INTRMASK_BUSY_MASK BIT(0)         /* nandflash控制器忙状态中断屏蔽位 */
#define FNAND_INTRMASK_DMA_BUSY_MASK BIT(1)     /* dma控制器忙状态中断屏蔽位 */
#define FNAND_INTRMASK_DMA_PGFINISH_MASK BIT(2) /* dma页操作完成中断屏蔽位 */
#define FNAND_INTRMASK_DMA_FINISH_MASK BIT(3)   /* dma操作完成中断完成中断屏蔽位 */
#define FNAND_INTRMASK_FIFO_EMP_MASK BIT(4)     /* fifo为空中断屏蔽位 */
#define FNAND_INTRMASK_FIFO_FULL_MASK BIT(5)    /* fifo为满中断屏蔽位 */
#define FNAND_INTRMASK_FIFO_TIMEOUT_MASK BIT(6) /* fifo超时中断屏蔽位 */
#define FNAND_INTRMASK_CMD_FINISH_MASK BIT(7)   /* nand接口命令完成中断屏蔽位 */
#define FNAND_INTRMASK_PGFINISH_MASK BIT(8)     /* nand接口页操作完成中断屏蔽位 */
#define FNAND_INTRMASK_RE_MASK BIT(9)           /* re_n门控打开中断屏蔽位 */
#define FNAND_INTRMASK_DQS_MASK BIT(10)         /* dqs门控打开中断屏蔽位 */
#define FNAND_INTRMASK_RB_MASK BIT(11)          /* rb_n信号busy中断屏蔽位 */
#define FNAND_INTRMASK_ECC_FINISH_MASK BIT(12)  /* ecc完成中断屏蔽位 */
#define FNAND_INTRMASK_ECC_ERR_MASK BIT(13)     /* ecc 中断屏蔽位 */

/* FNAND_INTR_OFFSET */
#define FNAND_INTR_ALL_INT_MASK GENMASK(17, 0)
#define FNAND_INTR_BUSY_MASK BIT(0)         /* nandflash控制器忙状态中断状态位 */
#define FNAND_INTR_DMA_BUSY_MASK BIT(1)     /* dma控制器忙状态中断状态位 */
#define FNAND_INTR_DMA_PGFINISH_MASK BIT(2) /* dma页操作完成中断状态位 */
#define FNAND_INTR_DMA_FINISH_MASK BIT(3)   /* dma操作完成中断完成中断状态位 */
#define FNAND_INTR_FIFO_EMP_MASK BIT(4)     /* fifo为空中断状态位 */
#define FNAND_INTR_FIFO_FULL_MASK BIT(5)    /* fifo为满中断状态位 */
#define FNAND_INTR_FIFO_TIMEOUT_MASK BIT(6) /* fifo超时中断状态位 */
#define FNAND_INTR_CMD_FINISH_MASK BIT(7)   /* nand接口命令完成中断状态位 */
#define FNAND_INTR_PGFINISH_MASK BIT(8)     /* nand接口页操作完成中断状态位 */
#define FNAND_INTR_RE_MASK BIT(9)           /* re_n门控打开中断状态位 */
#define FNAND_INTR_DQS_MASK BIT(10)         /* dqs门控打开中断状态位 */
#define FNAND_INTR_RB_MASK BIT(11)          /* rb_n信号busy中断状态位 */
#define FNAND_INTR_ECC_FINISH_MASK BIT(12)  /* ecc完成中断状态蔽位 */
#define FNAND_INTR_ECC_ERR_MASK BIT(13)     /* ecc正确中断状态蔽位 */

/* FNAND_ERROR_CLEAR_OFFSET */
#define FNAND_ERROR_CLEAR_DSP_ERR_CLR_MASK BIT(0)
#define FNAND_ERROR_CLEAR_AXI_RD_ERR_CLR_MASK BIT(1)
#define FNAND_ERROR_CLEAR_AXI_WR_ERR_CLR_MASK BIT(2)
#define FNAND_ERROR_CLEAR_ECC_ERR_CLR_MASK BIT(3)
#define FNAND_ERROR_ALL_CLEAR GENMASK(3, 0)

#define FNAND_SELETED_MAX_NUMBER 4



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
#define FNAND_READREG(base_addr, reg_offset) \
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
#define FNAND_WRITEREG(base_addr, reg_offset, data) \
    FtOut32((base_addr) + (u32)(reg_offset), (u32)(data))

#define FNAND_SETBIT(base_addr, reg_offset, data) \
    FtSetBit32((base_addr) + (u32)(reg_offset), (u32)(data))

#define FNAND_CLEARBIT(base_addr, reg_offset, data) \
    FtClearBit32((base_addr) + (u32)(reg_offset), (u32)(data))

#ifdef __cplusplus
}
#endif

#endif // !
