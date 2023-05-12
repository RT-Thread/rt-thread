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
 * FilePath: fsdio_hw.h
 * Date: 2022-05-26 15:32:34
 * LastEditTime: 2022-05-26 15:32:35
 * Description:  This file is for SDIO register function definition
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2021/12/2    init
 * 1.1   zhugengyu  2022/5/26    modify according to tech manual.
 */

#ifndef FSDIO_HW_H
#define FSDIO_HW_H

/***************************** Include Files *********************************/

#include "fparameters.h"
#include "fio.h"
#include "ftypes.h"
#include "fassert.h"
#include "fkernel.h"

#ifdef __aarch64__
#include "faarch64.h"
#else
#include "fcp15.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions *****************************/

/** @name Register Map
 *
 * Register offsets from the base address of an SD device.
 * @{
 */
#define FSDIO_CNTRL_OFFSET          0x00U          /* the controller config reg */
#define FSDIO_PWREN_OFFSET          0x04U          /* the power enable reg */
#define FSDIO_CLKDIV_OFFSET         0x08U          /* the clock divider reg */
#define FSDIO_CLKENA_OFFSET         0x10U          /* the clock enable reg */
#define FSDIO_TMOUT_OFFSET          0x14U          /* the timeout reg */
#define FSDIO_CTYPE_OFFSET          0x18U          /* the card type reg */
#define FSDIO_BLK_SIZ_OFFSET        0x1CU          /* the block size reg */
#define FSDIO_BYT_CNT_OFFSET        0x20U          /* the byte count reg */
#define FSDIO_INT_MASK_OFFSET       0x24U          /* the interrupt mask reg */
#define FSDIO_CMD_ARG_OFFSET        0x28U          /* the command argument reg */
#define FSDIO_CMD_OFFSET            0x2CU          /* the command reg */
#define FSDIO_RESP0_OFFSET          0x30U          /* the response reg0 */
#define FSDIO_RESP1_OFFSET          0x34U          /* the response reg1 */
#define FSDIO_RESP2_OFFSET          0x38U          /* the response reg2 */
#define FSDIO_RESP3_OFFSET          0x3CU          /* the response reg3 */
#define FSDIO_MASKED_INTS_OFFSET    0x40U          /* the masked interrupt status reg */
#define FSDIO_RAW_INTS_OFFSET       0x44U          /* the raw interrupt status reg */
#define FSDIO_STATUS_OFFSET         0x48U          /* the status reg    */
#define FSDIO_FIFOTH_OFFSET         0x4CU          /* the FIFO threshold watermark reg */
#define FSDIO_CARD_DETECT_OFFSET    0x50U          /* the card detect reg */
#define FSDIO_CARD_WRTPRT_OFFSET    0x54U          /* the card write protect reg */
#define FSDIO_GPIO_OFFSET           0x58U          /* the ciu ready */
#define FSDIO_TRAN_CARD_CNT_OFFSET  0x5CU          /* the transferred CIU card byte count reg */
#define FSDIO_TRAN_FIFO_CNT_OFFSET  0x60U          /* the transferred host to FIFO byte count reg  */
#define FSDIO_DEBNCE_OFFSET         0x64U          /* the debounce count reg */
#define FSDIO_UID_OFFSET            0x68U          /* the user ID reg */
#define FSDIO_VID_OFFSET            0x6CU          /* the controller version ID reg */
#define FSDIO_HWCONF_OFFSET         0x70U          /* the hardware configuration reg */
#define FSDIO_UHS_REG_OFFSET        0x74U          /* the UHS-I reg */
#define FSDIO_CARD_RESET_OFFSET     0x78U          /* the card reset reg */
#define FSDIO_BUS_MODE_OFFSET       0x80U          /* the bus mode reg */
#define FSDIO_DESC_LIST_ADDRL_OFFSET 0x88U         /* the descriptor list low base address reg */
#define FSDIO_DESC_LIST_ADDRH_OFFSET 0x8CU         /* the descriptor list high base address reg */
#define FSDIO_DMAC_STATUS_OFFSET    0x90U          /* the internal DMAC status reg */
#define FSDIO_DMAC_INT_EN_OFFSET    0x94U          /* the internal DMAC interrupt enable reg */
#define FSDIO_CUR_DESC_ADDRL_OFFSET 0x98U          /* the current host descriptor low address reg */
#define FSDIO_CUR_DESC_ADDRH_OFFSET 0x9CU          /* the current host descriptor high address reg */
#define FSDIO_CUR_BUF_ADDRL_OFFSET  0xA0U          /* the current buffer low address reg */
#define FSDIO_CUR_BUF_ADDRH_OFFSET  0xA4U          /* the current buffer high address reg */
#define FSDIO_CARD_THRCTL_OFFSET    0x100U         /* the card threshold control reg */
#define FSDIO_UHS_REG_EXT_OFFSET    0x108U         /* the UHS register extension */
#define FSDIO_EMMC_DDR_REG_OFFSET   0x10CU         /* the EMMC DDR reg */
#define FSDIO_ENABLE_SHIFT_OFFSET   0x110U         /* the enable phase shift reg */
#define FSDIO_DATA_OFFSET           0x200U         /* the data FIFO access */

/** @name FSDIO_CNTRL_OFFSET x0 Register
 */
#define FSDIO_CNTRL_CONTROLLER_RESET BIT(0)             /* RW 复位控制器，除 DMA，FIFO */
#define FSDIO_CNTRL_FIFO_RESET BIT(1)                   /* RW 复位 FIFO, 1 有效 */
#define FSDIO_CNTRL_DMA_RESET BIT(2)                    /* RW 复位内部 DMA, 1 有效 */
#define FSDIO_CNTRL_INT_ENABLE BIT(4)                   /* RW 全局中断使能配置, 1 使能 */
#define FSDIO_CNTRL_DMA_ENABLE BIT(5)                   /* RW 外部 DMA 模式使能  */
#define FSDIO_CNTRL_READ_WAIT BIT(6)                    /* RW SDIO 读等待 1 有效 */
#define FSDIO_CNTRL_SEND_IRQ_RESPONSE BIT(7)            /* RW MMC 中断自动响应配置 1 有效 */
#define FSDIO_CNTRL_ABORT_READ_DATA BIT(8)              /* RW 读暂停异常清除 */
#define FSDIO_CNTRL_SEND_CCSD BIT(9)                    /* RW 发送CCD (NOT USED) */
#define FSDIO_CNTRL_SEND_AUTO_STOP_CCSD BIT(10)         /* RW 发送CCD，自动STOP (NOT USED) */
#define FSDIO_CNTRL_ENDIAN BIT(11)                      /* RW 0：小端，1：大端 */
#define FSDIO_CNTRL_CARD_VOLTAGE_A_MASK GENMASK(19, 16) /* RW A电压选择 */
#define FSDIO_CNTRL_CARD_VOLTAGE_B_MASK GENMASK(23, 20) /* RW B电压选择 */
#define FSDIO_CNTRL_ENABLE_OD_PULLUP BIT(24)            /* RW 外部开漏输出 */
#define FSDIO_CNTRL_USE_INTERNAL_DMAC BIT(25)           /* RW 使用内部DMA */

/** @name FSDIO_PWREN_OFFSET 0x4 Register
 */
#define FSDIO_PWREN_ENABLE BIT(0) /* RW 卡供电开关, 0：关；1：开*/

/** @name FSDIO_CLKDIV_OFFSET 0x8 Register
 */
/* CLK_SAMPLE 和 CLK_SAMPLE 必须小于 CLK_DIVIDER */
#define FSDIO_CLK_SAMPLE_SET(x)  SET_REG32_BITS((x), 23, 16)
#define FSDIO_CLK_DRV_SET(x)     SET_REG32_BITS((x), 15, 8)
#define FSDIO_CLK_DIVIDER_SET(x) SET_REG32_BITS((x), 7, 0) /* 分频系数 =  2 * bit[7:0] */
#define FSDIO_CLK_DIV(samp, drv, div) FSDIO_CLK_SAMPLE_SET(samp) | \
    FSDIO_CLK_DRV_SET(drv) | \
    FSDIO_CLK_DIVIDER_SET(div)

#define FSDIO_CLK_DIVDER_GET(div_reg)  GET_REG32_BITS((div_reg), 7, 0)

/** @name FSDIO_CLKENA_OFFSET Register
 */
#define FSDIO_CLKENA_CCLK_ENABLE    BIT(0)     /* RW 0：Clock disabled；1：Clock enabled */
#define FSDIO_CLKENA_CCLK_LOW_POWER BIT(16)    /* RW 0x0：非低功耗；0x1：低功耗 */

/** @name FSDIO_TMOUT_OFFSET Register
 */
#define FSDIO_MAX_DATA_TIMEOUT 0xffffff /* RW 读卡超时（以卡时钟为单位） */
#define FSDIO_MAX_RESP_TIMEOUT 0xff     /* RW 响应超时（以卡时钟为单位） */
#define FSDIO_TIMEOUT_DATA(data_timeout, resp_timeout) \
    ((GENMASK(31, 8) & ((data_timeout) << 8)) |        \
     (GENMASK(7, 0) & ((resp_timeout))))

/** @name FSDIO_CTYPE_OFFSET Register
 */
#define FSDIO_CARD0_WIDTH1_8BIT BIT(16) /* 1: 8-bit mode */
#define FSDIO_CARD0_WIDTH2_4BIT BIT(0)  /* 1: 4-bit mode */
#define FSDIO_CARD0_WIDTH2_1BIT 0x0U    /* 0: 1-bit mode */

/** @name FSDIO_INT_MASK_OFFSET Register
 *  @name FSDIO_MASKED_INTS_OFFSET Register
 *  @name FSDIO_RAW_INTS_OFFSET Register
 */
#define FSDIO_INT_CD_BIT BIT(0)       /* RW Card detect (CD) */
#define FSDIO_INT_RE_BIT BIT(1)       /* RW Response error (RE) */
#define FSDIO_INT_CMD_BIT BIT(2)      /* RW Command done (CD) */
#define FSDIO_INT_DTO_BIT BIT(3)      /* RW Data transfer over (DTO) */
#define FSDIO_INT_TXDR_BIT BIT(4)     /* RW Transmit FIFO data request (TXDR) */
#define FSDIO_INT_RXDR_BIT BIT(5)     /* RW Receive FIFO data request (RXDR) */
#define FSDIO_INT_RCRC_BIT BIT(6)     /* RW Response CRC error (RCRC) */
#define FSDIO_INT_DCRC_BIT BIT(7)     /* RW Data CRC error (DCRC) */
#define FSDIO_INT_RTO_BIT BIT(8)      /* RW Response timeout (RTO) */
#define FSDIO_INT_DRTO_BIT BIT(9)     /* RW Data read timeout (DRTO) */
#define FSDIO_INT_HTO_BIT BIT(10)     /* RW Data starvation-by-host timeout (HTO) */
#define FSDIO_INT_FRUN_BIT BIT(11)    /* RW FIFO underrun/overrun error (FRUN) */
#define FSDIO_INT_HLE_BIT BIT(12)     /* RW Hardware locked write error (HLE) */
#define FSDIO_INT_SBE_BCI_BIT BIT(13) /* RW Start-bit error (SBE) */
#define FSDIO_INT_ACD_BIT BIT(14)     /* RW Auto command done (ACD) */
#define FSDIO_INT_EBE_BIT BIT(15)     /* RW End-bit error (read)/Write no CRC (EBE) */
#define FSDIO_INT_SDIO_BIT BIT(16)    /* RW SDIO interrupt for card */

#define FSDIO_INT_ALL_BITS GENMASK(16, 0)
#define FSDIO_INTS_CMD_MASK (FSDIO_INT_RE_BIT | FSDIO_INT_CMD_BIT | FSDIO_INT_RCRC_BIT | \
                             FSDIO_INT_RTO_BIT | FSDIO_INT_HTO_BIT | FSDIO_INT_HLE_BIT)

#define FSDIO_INTS_DATA_MASK (FSDIO_INT_DTO_BIT | FSDIO_INT_DCRC_BIT | FSDIO_INT_DRTO_BIT | \
                              FSDIO_INT_SBE_BCI_BIT)

/** @name FSDIO_CMD_OFFSET Register
 */
#define FSDIO_CMD_START BIT(31)           /* 启动命令 */
#define FSDIO_CMD_USE_HOLD_REG BIT(29)    /* 0: 旁路HOLD寄存器，1: 使能HOLD寄存器 */
#define FSDIO_CMD_VOLT_SWITCH BIT(28)     /* 0: 无电压转换，1: 有电压转换 */
#define FSDIO_CMD_BOOT_MODE BIT(27)       /* 0: Mandatory boot, 1: Alternate boot */
#define FSDIO_CMD_DISABLE_BOOT BIT(26)    /* 中止boot进程 */
#define FSDIO_CMD_EXPECT_BOOT_ACK BIT(25) /* 1: Expect book ack */
#define FSDIO_CMD_ENABLE_BOOT BIT(24)     /* 1: 使能 boot for mandatory */
#define FSDIO_CMD_UPD_CLK BIT(21)         /* 1：不发送指令，仅更新时钟寄存器的值到卡时钟域内 */
#define FSDIO_CMD_CARD_NUM_SET(num)      SET_REG32_BITS((num), 20, 16)
#define FSDIO_CMD_INIT BIT(15)           /* 0：在发送指令前不发送初始化序列（80 个周期） 1: 发送 */
#define FSDIO_CMD_STOP_ABORT BIT(14)     /* 1：停止或中止命令，用于停止当前的数据传输 */
#define FSDIO_CMD_WAIT_PRVDATA_COMPLETE BIT(13)   /* 1：等待前面的数据传输完成后再发送指令 0: 立即发送命令 */
#define FSDIO_CMD_SEND_AUTO_STOP BIT(12) /* 1：在数据传送结束时发送停止命令 */
#define FSDIO_CMD_TRANSF_MODE_SET(mode) SET_REG32_BITS((mode), 12, 11)      /* 1: 流数据传输指令 */
#define FSDIO_CMD_DAT_WRITE BIT(10)         /* 0：读卡 1：写卡 */
#define FSDIO_CMD_DAT_EXP BIT(9)         /* 0：不等待数据传输, 1：等待数据传输 */
#define FSDIO_CMD_RESP_CRC BIT(8)        /* 1：检查响应 CRC */
#define FSDIO_CMD_RESP_LONG BIT(7)       /* 0：等待卡的短响应 1：等待卡的长响应 */
#define FSDIO_CMD_RESP_EXP BIT(6)        /* 1：等待卡的响应，0：命令不需要卡响应 */
#define FSDIO_CMD_INDX_SET(ind) SET_REG32_BITS((ind), 5, 0) /* 命令索引号 */

/** @name FSDIO_STATUS_OFFSET Register
 */
#define FSDIO_STATUS_FIFO_RX BIT(0)     /* RO, 达到 FIFO_RX 标记 */
#define FSDIO_STATUS_FIFO_TX BIT(1)     /* RO, 达到 FIFO_TX 标记 */
#define FSDIO_STATUS_FIFO_EMPTY BIT(2)  /* RO, FIFO empty */
#define FSDIO_STATUS_FIFO_FULL BIT(3)   /* RO, FIFO full */
#define FSDIO_STATUS_CMD_FSM_GET(reg_val)  GET_REG32_BITS((reg_val), 7, 4)
#define FSDIO_STATUS_DATA3_STATUS BIT(8) /* RO DATA[3] 卡在位检测，1：在位 */
#define FSDIO_STATUS_DATA_BUSY BIT(9)   /* RO 1: 卡 busy */
#define FSDIO_STATUS_DATA_STATE_MC_BUSY BIT(10)  /* RO DATA TX|RX FSM busy  */
#define FSDIO_STATUS_RESP_INDEX_GET(reg_val) GET_REG32_BITS((reg_val), 16, 11)
#define FSDIO_STATUS_FIFO_CNT_GET(reg_val)  GET_REG32_BITS((reg_val), 29, 17)  /* RO: FIFO 填充计数器 */
#define FSDIO_STATUS_DMA_ACK BIT(30)    /* RO DMA 确认 */
#define FSDIO_STATUS_DMA_REQ BIT(31)    /* RO DMA 请求 */

/** @name FSDIO_FIFOTH_OFFSET Register
 */
enum
{
    FSDIO_FIFOTH_DMA_TRANS_1 = 0b000,
    FSDIO_FIFOTH_DMA_TRANS_4 = 0b001,
    FSDIO_FIFOTH_DMA_TRANS_8 = 0b010,
    FSDIO_FIFOTH_DMA_TRANS_16 = 0b011,
    FSDIO_FIFOTH_DMA_TRANS_32 = 0b100,
    FSDIO_FIFOTH_DMA_TRANS_64 = 0b101,
    FSDIO_FIFOTH_DMA_TRANS_128 = 0b110,
    FSDIO_FIFOTH_DMA_TRANS_256 = 0b111
};

#define FSDIO_FIFOTH_DMA_TRANS_MASK GENMASK(30, 28) /* 多次传输的突发大小 */
#define FSDIO_FIFOTH_RX_WMARK_MASK GENMASK(27, 16)  /* 当接收数据给卡时FIFO的阈值 */
#define FSDIO_FIFOTH_TX_WMARK_MASK GENMASK(11, 0)   /* 当发送数据给卡时FIFO的阈值 */

#define FSDIO_RX_WMARK      0x7U
#define FSDIO_TX_WMARK      0x100U

/*
    trans_size: Burst size of multiple transaction;
    rx_wmark: FIFO threshold watermark level when receiving data to card.
    tx_wmark: FIFO threshold watermark level when transmitting data to card
*/
#define FSDIO_FIFOTH(trans_size, rx_wmark, tx_wmark)          \
    (((FSDIO_FIFOTH_DMA_TRANS_MASK) & ((trans_size) << 28)) | \
     ((FSDIO_FIFOTH_RX_WMARK_MASK) & ((rx_wmark) << 16)) |    \
     ((FSDIO_FIFOTH_TX_WMARK_MASK) & (tx_wmark)))

#define FSDIO_DMA_TRANS_SIZE_SET(x)     SET_REG32_BITS((x), 30, 28)
#define FSDIO_RX_MARK_SIZE_SET(x)       SET_REG32_BITS((x), 27, 16)
#define FSDIO_TX_MARK_SIZE_SET(x)       SET_REG32_BITS((x), 11, 0)

/** @name FSDIO_CARD_DETECT_OFFSET Register
 */
#define FSDIO_CARD_DETECTED BIT(0)  /* 1：卡不在位；0：卡在位 */

/** @name FSDIO_CARD_WRTPRT_OFFSET Register
 */
#define FSDIO_CARD_WRITE_PROTECTED BIT(0) /* 1：写保护；0：无写保护 */

/** @name FSDIO_GPIO_OFFSET Register
 */
#define FSDIO_CLK_READY BIT(0) /* CIU 时钟 ready */

/** @name FSDIO_UHS_REG_OFFSET Register
 */
#define FSDIO_UHS_REG_VOLT_180 BIT(0)      /* RW 外部调压器接口电压 0: 3.3v, 1: 1.8v */
#define FSDIO_UHS_REG_VOLT_330 0U
#define FSDIO_UHS_REG_DDR  BIT(16)     /* RW DDR 模式 */

/** @name FSDIO_CARD_RESET_OFFSET Register
 */
#define FSDIO_CARD_RESET_ENABLE BIT(0) /* RW 1：运行；0：复位 */

/** @name FSDIO_BUS_MODE_OFFSET Register
 */
#define FSDIO_BUS_MODE_SWR BIT(0) /* RW 软复位，复位idma内部寄存器 */
#define FSDIO_BUS_MODE_FB BIT(1)  /* RW 固定burst */
#define FSDIO_BUS_MODE_DE BIT(7)  /* RW idma使能 */
#define FSDIO_BUS_MODE_PBL_GET(reg_val)  GET_REG32_BITS((reg_val), 10, 8) /* burst LEN */

/** @name FSDIO_DMAC_STATUS_OFFSET Register
 */
#define FSDIO_DMAC_STATUS_TI BIT(0)  /* RW 发送中断。表示链表的数据发送完成 */
#define FSDIO_DMAC_STATUS_RI BIT(1)  /* RW 接收中断。表示链表的数据接收完成 */
#define FSDIO_DMAC_STATUS_FBE BIT(2) /* RW 致命总线错误中断 */
#define FSDIO_DMAC_STATUS_DU BIT(4)  /* RW 链表不可用中断 */
#define FSDIO_DMAC_STATUS_CES BIT(5) /* RW 卡错误汇总 */
#define FSDIO_DMAC_STATUS_NIS BIT(8) /* RW 正常中断汇总 */
#define FSDIO_DMAC_STATUS_AIS BIT(9) /* RW 异常中断汇总 */
#define FSDIO_DMAC_STATUS_EB_GET(reg_val) GET_REG32_BITS((reg_val), 12, 10)
#define FSDIO_DMAC_STATUS_ALL_BITS  GENMASK(9, 0)

#define FSDIO_DMAC_STATUS_EB_TX    0b001
#define FSDIO_DMAC_STATUS_EB_RX    0b010

/** @name FSDIO_DMAC_INT_EN_OFFSET Register
 */
#define FSDIO_DMAC_INT_ENA_TI BIT(0)            /* RW 发送完成中断使能 */
#define FSDIO_DMAC_INT_ENA_RI BIT(1)            /* RW 接收完成中断使能 */
#define FSDIO_DMAC_INT_ENA_FBE BIT(2)           /* RW 总线错误中断使能 */
#define FSDIO_DMAC_INT_ENA_DU BIT(4)            /* RW 描述符不可读中断使能 */
#define FSDIO_DMAC_INT_ENA_CES BIT(5)           /* RW 卡错误中断使能 */
#define FSDIO_DMAC_INT_ENA_NIS BIT(8)           /* RW 正常中断汇总使能 */
#define FSDIO_DMAC_INT_ENA_AIS BIT(9)           /* RW 异常中断汇总使能 */
#define FSDIO_DMAC_INT_ENA_ALL GENMASK(9, 0)

#define FSDIO_DMAC_INTS_MASK    (FSDIO_DMAC_INT_ENA_FBE | FSDIO_DMAC_INT_ENA_DU | \
                                 FSDIO_DMAC_INT_ENA_NIS | FSDIO_DMAC_INT_ENA_AIS)

/** @name FSDIO_CARD_THRCTL_OFFSET Register
 */
#define FSDIO_CARD_THRCTL_CARDRD BIT(0)   /* RW 读卡threshold使能 */
#define FSDIO_CARD_THRCTL_BUSY_CLR BIT(1) /* RW busy清中断 */
#define FSDIO_CARD_THRCTL_CARDWR BIT(2)   /* RO 写卡threshold使能 */
enum
{
    FSDIO_FIFO_DEPTH_8 = 23,
    FSDIO_FIFO_DEPTH_16 = 24,
    FSDIO_FIFO_DEPTH_32 = 25,
    FSDIO_FIFO_DEPTH_64 = 26,
    FSDIO_FIFO_DEPTH_128 = 27
};

#define FSDIO_CARD_THRCTL_THRESHOLD(n) BIT(n) /* 读卡 Threshold */

/** @name FSDIO_UHS_REG_EXT_OFFSET Register
 */
#define FSDIO_UHS_EXT_MMC_VOLT BIT(0)         /* RW 1.2V供电选择 */
#define FSDIO_UHS_EXT_CLK_ENA BIT(1)          /* RW 外部时钟，CIU时钟使能 */
#define FSDIO_UHS_CLK_DIV_MASK GENMASK(14, 8) /* RW 分频系数，ciu_f = clk_div_ctrl + 1, min=1*/
#define FSDIO_UHS_CLK_DIV(x) (FSDIO_UHS_CLK_DIV_MASK & ((x) << 8))
#define FSDIO_UHS_CLK_SAMP_MASK GENMASK(22, 16) /* RW 采样相位参数，相对于ciu时钟相位点 */
#define FSDIO_UHS_CLK_SAMP(x) (FSDIO_UHS_CLK_SAMP_MASK & ((x) << 16))
#define FSDIO_UHS_CLK_DRV_MASK GENMASK(30, 24) /* RW 输出相位参数，相对于ciu时钟相位点 */
#define FSDIO_UHS_CLK_DRV(x) (FSDIO_UHS_CLK_DRV_MASK & ((x) << 24))
#define FSDIO_UHS_EXT_CLK_MUX BIT(31)

/* FSDIO_UHS_REG_EXT_OFFSET 和 FSDIO_CLKDIV_OFFSET 两个寄存器配合完成卡时钟和驱动采样相位调整
    UHS_REG_EXT 配置一级分频，CLK_DIV 决定CARD工作时钟频率, DRV 和 SAMP 分别控制驱动相位和采样相位粗调
        分配系数 = bit [14 : 8] + 1
    CLKDIV 配置二级分频, DIVIDER , DRV 和 SAMP 分别控制驱动相位和采样相位精调
        分配系数 = bit [7: 0] * 2
*/
#define FSDIO_UHS_REG(drv_phase, samp_phase, clk_div) \
    (FSDIO_UHS_CLK_DRV(drv_phase) |                   \
     FSDIO_UHS_CLK_SAMP(samp_phase) |                 \
     FSDIO_UHS_CLK_DIV(clk_div))

#define FSDIO_UHS_CLK_DIV_SET(x)        SET_REG32_BITS((x), 14, 8)
#define FSDIO_UHS_CLK_DIV_GET(reg_val)  GET_REG32_BITS((reg_val), 14, 8)
#define FSDIO_UHS_CLK_SAMP_SET(x)       SET_REG32_BITS((x), 22, 16)
#define FSDIO_UHS_CLK_DRV_SET(x)        SET_REG32_BITS((x), 30, 24)

/** @name FSDIO_REG_EMMC_DDR_REG_OFFSET Register
 */
#define FSDIO_EMMC_DDR_CYCLE BIT(0) /* RW 1: start bit小于一个周期，0：start bit 为一个周期 */

#define FSDIO_TIMEOUT (50000) /* timeout for retries */
#define FSDIO_DELAY_US (5)
#define FSDIO_400_KHZ (400000UL)
#define FSDIO_25_MHZ (25000000UL)
#define FSDIO_MAX_FIFO_CNT (0x800U)

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FSDIO_READ_REG(addr, reg_off)           FtIn32((addr) + (u32)(reg_off))
#define FSDIO_WRITE_REG(addr, reg_off, reg_val) FtOut32((addr) + (u32)(reg_off), (u32)(reg_val))
#define FSDIO_CLR_BIT(addr, reg_off, bits)      FtClearBit32((addr) + (u32)(reg_off), bits)
#define FSDIO_SET_BIT(addr, reg_off, bits)      FtSetBit32((addr) + (u32)(reg_off), bits)

#define FSDIO_DATA_BARRIER()                    WMB()
/************************** Function Prototypes ******************************/
FError FSdioSendPrivateCmd(uintptr base_addr, u32 cmd, u32 arg);
FError FSdioResetCtrl(uintptr base_addr, u32 reset_bits);

/*****************************************************************************/
/**
 * @name: FSdioSetClock
 * @msg: Enable/Disable controller clock
 * @return {NONE}
 * @param {uintptr} base_addr, base address of SDIO controller
 * @param {boolean} enable, TRUE: enable clock
 */
static inline void FSdioSetClock(uintptr base_addr, boolean enable)
{
    u32 reg_val = FSDIO_READ_REG(base_addr, FSDIO_CLKENA_OFFSET);
    if (enable)
    {
        reg_val |= FSDIO_CLKENA_CCLK_ENABLE;
    }
    else
    {
        reg_val &= ~FSDIO_CLKENA_CCLK_ENABLE;
    }
    FSDIO_WRITE_REG(base_addr, FSDIO_CLKENA_OFFSET, reg_val);
}

static inline void FSdioSetPower(uintptr base_addr, boolean enable)
{
    u32 reg_val = FSDIO_READ_REG(base_addr, FSDIO_PWREN_OFFSET);
    if (enable)
    {
        reg_val |= FSDIO_PWREN_ENABLE;
    }
    else
    {
        reg_val &= ~FSDIO_PWREN_ENABLE;
    }
    FSDIO_WRITE_REG(base_addr, FSDIO_PWREN_OFFSET, reg_val);
}

static inline void FSdioSetExtClock(uintptr base_addr, boolean enable)
{
    u32 reg_val = FSDIO_READ_REG(base_addr, FSDIO_UHS_REG_EXT_OFFSET);
    if (enable)
    {
        reg_val |= FSDIO_UHS_EXT_CLK_ENA;
    }
    else
    {
        reg_val &= ~FSDIO_UHS_EXT_CLK_ENA;
    }
    FSDIO_WRITE_REG(base_addr, FSDIO_UHS_REG_EXT_OFFSET, reg_val);
}

static inline void FSdioSetVoltage1_8V(uintptr base_addr, boolean v1_8)
{
    u32 reg_val = FSDIO_READ_REG(base_addr, FSDIO_UHS_REG_OFFSET);
    if (v1_8)
    {
        reg_val |= FSDIO_UHS_REG_VOLT_180;
    }
    else
    {
        reg_val &= ~FSDIO_UHS_REG_VOLT_180;    /* 3.3v */
    }
    FSDIO_WRITE_REG(base_addr, FSDIO_UHS_REG_OFFSET, reg_val);
}

/**
 * @name: FSdioGetRawStatus
 * @msg: Get raw interrupt status of controller
 * @return {u32} raw interrupt status
 * @param {uintptr} base_addr, base address of SDIO controller
 */
static inline u32 FSdioGetRawStatus(uintptr base_addr)
{
    return FSDIO_READ_REG(base_addr, FSDIO_RAW_INTS_OFFSET);
}

/**
 * @name: FSdioClearRawStatus
 * @msg: Clear raw interrupt status of controller
 * @return {NONE}
 * @param {uintptr} base_addr, base address of SDIO controller
 */
static inline void FSdioClearRawStatus(uintptr base_addr)
{
    u32 reg_val = FSdioGetRawStatus(base_addr);
    FSDIO_WRITE_REG(base_addr, FSDIO_RAW_INTS_OFFSET, reg_val);
}

/**
 * @name: FSdioGetStatus
 * @msg: Get status of controller
 * @return {u32} controller status
 * @param {uintptr} base_addr, base address of SDIO controller
 */
static inline u32 FSdioGetStatus(uintptr base_addr)
{
    return FSDIO_READ_REG(base_addr, FSDIO_STATUS_OFFSET);
}

/**
 * @name: FSdioGetDMAStatus
 * @msg: Get interrupt status of DMA
 * @return {u32} DMA interrupt status
 * @param {uintptr} base_addr, base address of SDIO controller
 */
static inline u32 FSdioGetDMAStatus(uintptr base_addr)
{
    return FSDIO_READ_REG(base_addr, FSDIO_DMAC_STATUS_OFFSET);
}

/**
 * @name: FSdioClearDMAStatus
 * @msg: Clear interrupt status of DMA
 * @return {NONE}
 * @param {uintptr} base_addr, base address of SDIO controller
 */
static inline void FSdioClearDMAStatus(uintptr base_addr)
{
    u32 reg_val = FSdioGetDMAStatus(base_addr);
    FSDIO_WRITE_REG(base_addr, FSDIO_DMAC_STATUS_OFFSET, reg_val);
}

/**
 * @name: FSdioSetDescriptor
 * @msg: Set base address of DMA descriptors
 * @return {NONE}
 * @param {uintptr} base_addr, base address of SDIO controller
 * @param {uintptr} descriptor, base address of DMA descriptors
 */
static inline void FSdioSetDescriptor(uintptr base_addr, uintptr descriptor)
{
#ifdef __aarch64___
    FSDIO_WRITE_REG(base_addr, FSDIO_DESC_LIST_ADDRH_OFFSET, UPPER_32_BITS(descriptor));
    FSDIO_WRITE_REG(base_addr, FSDIO_DESC_LIST_ADDRL_OFFSET, LOWER_32_BITS(descriptor));
#else
    FSDIO_WRITE_REG(base_addr, FSDIO_DESC_LIST_ADDRH_OFFSET, 0x0U);
    FSDIO_WRITE_REG(base_addr, FSDIO_DESC_LIST_ADDRL_OFFSET, (u32)(descriptor));
#endif
}

/**
 * @name: FSdioSetTransBytes
 * @msg: Set number of bytes to transfer
 * @return {NONE}
 * @param {uintptr} base_addr, base address of SDIO controller
 * @param {u32} bytes, number of bytes to transfer
 */
static inline void FSdioSetTransBytes(uintptr base_addr, u32 bytes)
{
    FSDIO_WRITE_REG(base_addr, FSDIO_BYT_CNT_OFFSET, bytes);
}

/**
 * @name: FSdioSetBlockSize
 * @msg: Set size of blocks in card
 * @return {NONE}
 * @param {uintptr} base_addr, base address of SDIO controller
 * @param {u32} block_size, size of blocks in card
 */
static inline void FSdioSetBlockSize(uintptr base_addr, u32 block_size)
{
    FSDIO_WRITE_REG(base_addr, FSDIO_BLK_SIZ_OFFSET, block_size);
}

/**
 * @name: FSdioSetBusWidth
 * @msg: Set bus width of card
 * @return {NONE}
 * @param {uintptr} base_addr, base address of SDIO controller
 * @param {u32} width, bus width of card 1-bit, 4-bit, 8-bit
 */
static inline void FSdioSetBusWidth(uintptr base_addr, u32 width)
{
    u32 reg_val;

    switch (width)
    {
        case 1:
            reg_val = FSDIO_CARD0_WIDTH2_1BIT;
            break;
        case 4:
            reg_val = FSDIO_CARD0_WIDTH2_4BIT;
            break;
        case 8:
            reg_val = FSDIO_CARD0_WIDTH1_8BIT;
            break;
        default:
            FASSERT_MSG(0, "invalid bus width %d", width);
            break;
    }

    FSDIO_WRITE_REG(base_addr, FSDIO_CTYPE_OFFSET, reg_val);
}

/**
 * @name: FSdioGetBusWidth
 * @msg: Get bus width for card
 * @return {u32} current bus width setting
 * @param {uintptr} base_addr, base address of SDIO controller
 */
static inline u32 FSdioGetBusWidth(uintptr base_addr)
{
    u32 bus_width = 1;
    u32 reg_val = FSDIO_READ_REG(base_addr, FSDIO_CTYPE_OFFSET);

    if (FSDIO_CARD0_WIDTH2_4BIT & reg_val)
    {
        bus_width = 4;
    }
    else if (FSDIO_CARD0_WIDTH1_8BIT & reg_val)
    {
        bus_width = 8;
    }

    return bus_width;
}

/**
 * @name: FSdioResetIDMA
 * @msg: Reset for internal DMA
 * @return {NONE}
 * @param {uintptr} base_addr, base address of SDIO controller
 */
static inline void FSdioResetIDMA(uintptr base_addr)
{
    u32 reg_val = FSDIO_READ_REG(base_addr, FSDIO_BUS_MODE_OFFSET);
    reg_val |= FSDIO_BUS_MODE_SWR; /* 写1软复位idma，复位完成后硬件自动清0 */
    FSDIO_WRITE_REG(base_addr, FSDIO_BUS_MODE_OFFSET, reg_val);
}

/**
 * @name: FSdioSetDDRMode
 * @msg: Enable/Disable DDR mode
 * @return {*}
 * @param {uintptr} base_addr, base address of SDIO controller
 * @param {boolean} enable, TRUE: enable DDR mode
 */
static inline void FSdioSetDDRMode(uintptr base_addr, boolean enable)
{
    u32 uhs_val = FSDIO_READ_REG(base_addr, FSDIO_UHS_REG_OFFSET);
    u32 emmc_val = FSDIO_READ_REG(base_addr, FSDIO_EMMC_DDR_REG_OFFSET);
    if (enable)
    {
        uhs_val |= FSDIO_UHS_REG_DDR;
        emmc_val |= FSDIO_EMMC_DDR_CYCLE;
    }
    else
    {
        uhs_val &= ~FSDIO_UHS_REG_DDR;
        emmc_val &= ~FSDIO_EMMC_DDR_CYCLE;
    }
    FSDIO_WRITE_REG(base_addr, FSDIO_UHS_REG_OFFSET, uhs_val);
    FSDIO_WRITE_REG(base_addr, FSDIO_EMMC_DDR_REG_OFFSET, emmc_val);

    return;
}

/**
 * @name: FSdioCheckIfCardExists
 * @msg: Check if card inserted
 * @return {boolean} TRUE: inserted, FALSE: not-found
 * @param {uintptr} base_addr, base address of SDIO controller
 */
static inline boolean FSdioCheckIfCardExists(uintptr base_addr)
{
    return (FSDIO_READ_REG(base_addr, FSDIO_CARD_DETECT_OFFSET) & FSDIO_CARD_DETECTED) ?
           FALSE : TRUE;
}

#ifdef __cplusplus
}
#endif

#endif