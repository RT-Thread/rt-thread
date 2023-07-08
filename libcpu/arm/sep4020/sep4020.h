/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef __SEP4020_H
#define __SEP4020_H

#include <rtthread.h>

/*Core definations*/
#define SVCMODE
#define Mode_USR    0x10
#define Mode_FIQ    0x11
#define Mode_IRQ    0x12
#define Mode_SVC    0x13
#define Mode_ABT    0x17
#define Mode_UND    0x1B
#define Mode_SYS    0x1F



/*
 *  各模块寄存器基值
 */

#define   ESRAM_BASE    0x04000000
#define   INTC_BASE     0x10000000
#define   PMU_BASE      0x10001000
#define   RTC_BASE      0x10002000
#define   WD_BASE       0x10002000
#define   TIMER_BASE    0x10003000
#define   PWM_BASE      0x10004000
#define   UART0_BASE    0X10005000
#define   UART1_BASE    0X10006000
#define   UART2_BASE    0X10007000
#define   UART3_BASE    0X10008000
#define   SSI_BASE      0X10009000
#define   I2S_BASE      0x1000A000
#define   MMC_BASE      0x1000B000
#define   SD_BASE       0x1000B000
#define   SMC0_BASE     0x1000C000
#define   SMC1_BASE     0x1000D000
#define   USBD_BASE     0x1000E000
#define   GPIO_BASE     0x1000F000
#define   EMI_BASE      0x11000000
#define   DMAC_BASE     0x11001000
#define   LCDC_BASE     0x11002000
#define   MAC_BASE      0x11003000
#define   AMBA_BASE     0x11005000


/*
 *  INTC模块
 *  基址: 0x10000000
 */

#define INTC_IER                  (INTC_BASE+0X000)       /* IRQ中断允许寄存器 */
#define INTC_IMR                  (INTC_BASE+0X008)       /* IRQ中断屏蔽寄存器 */
#define INTC_IFR                  (INTC_BASE+0X010)       /* IRQ软件强制中断寄存器 */
#define INTC_IRSR                 (INTC_BASE+0X018)       /* IRQ未处理中断状态寄存器 */
#define INTC_ISR                  (INTC_BASE+0X020)       /* IRQ中断状态寄存器 */
#define INTC_IMSR                 (INTC_BASE+0X028)       /* IRQ屏蔽中断状态寄存器 */
#define INTC_IFSR                 (INTC_BASE+0X030)       /* IRQ中断最终状态寄存器 */
#define INTC_FIER                 (INTC_BASE+0X0C0)       /* FIQ中断允许寄存器 */
#define INTC_FIMR                 (INTC_BASE+0X0C4)       /* FIQ中断屏蔽寄存器 */
#define INTC_FIFR                 (INTC_BASE+0X0C8)       /* FIQ软件强制中断寄存器 */
#define INTC_FIRSR                (INTC_BASE+0X0CC)       /* FIQ未处理中断状态寄存器 */
#define INTC_FISR                 (INTC_BASE+0X0D0)       /* FIQ中断状态寄存器 */
#define INTC_FIFSR                (INTC_BASE+0X0D4)       /* FIQ中断最终状态寄存器 */
#define INTC_IPLR                 (INTC_BASE+0X0D8)       /* IRQ中断优先级寄存器 */
#define INTC_ICR1                 (INTC_BASE+0X0DC)       /* IRQ内部中断优先级控制寄存器1 */
#define INTC_ICR2                 (INTC_BASE+0X0E0)       /* IRQ内部中断优先级控制寄存器2 */
#define INTC_EXICR1               (INTC_BASE+0X0E4)       /* IRQ外部中断优先级控制寄存器1 */
#define INTC_EXICR2               (INTC_BASE+0X0E8)       /* IRQ外部中断优先级控制寄存器2 */


/*
 *  PMU模块
 *  基址: 0x10001000
 */

#define PMU_PLTR                  (PMU_BASE+0X000)        /* PLL的稳定过渡时间 */
#define PMU_PMCR                  (PMU_BASE+0X004)        /* 系统主时钟PLL的控制寄存器 */
#define PMU_PUCR                  (PMU_BASE+0X008)        /* USB时钟PLL的控制寄存器 */
#define PMU_PCSR                  (PMU_BASE+0X00C)        /* 内部模块时钟源供给的控制寄存器 */
#define PMU_PDSLOW                (PMU_BASE+0X010)        /* SLOW状态下时钟的分频因子 */
#define PMU_PMDR                  (PMU_BASE+0X014)        /* 芯片工作模式寄存器 */
#define PMU_RCTR                  (PMU_BASE+0X018)        /* Reset控制寄存器 */
#define PMU_CLRWAKUP              (PMU_BASE+0X01C)        /* WakeUp清除寄存器 */


/*
 *  RTC模块
 *  基址: 0x10002000
 */

#define RTC_STA_YMD               (RTC_BASE+0X000)        /* 年, 月, 日计数寄存器 */
#define RTC_STA_HMS               (RTC_BASE+0X004)        /* 小时, 分钟, 秒寄存器 */
#define RTC_ALARM_ALL             (RTC_BASE+0X008)        /* 定时月, 日, 时, 分寄存器 */
#define RTC_CTR                   (RTC_BASE+0X00C)        /* 控制寄存器 */
#define RTC_INT_EN                (RTC_BASE+0X010)        /* 中断使能寄存器 */
#define RTC_INT_STS               (RTC_BASE+0X014)        /* 中断状态寄存器 */
#define RTC_SAMP                  (RTC_BASE+0X018)        /* 采样周期寄存器 */
#define RTC_WD_CNT                (RTC_BASE+0X01C)        /* Watch-Dog计数值寄存器 */
#define RTC_WD_SEV                (RTC_BASE+0X020)        /* Watch-Dog服务寄存器 */
#define RTC_CONFIG_CHECK          (RTC_BASE+0X024)        /* 配置时间确认寄存器 (在配置时间之前先写0xaaaaaaaa) */
#define RTC_KEY0                  (RTC_BASE+0X02C)        /* 密钥寄存器 */

/*
 *  TIMER模块
 *  基址: 0x10003000
 */

#define TIMER_T1LCR               (TIMER_BASE+0X000)      /* 通道1加载计数寄存器 */
#define TIMER_T1CCR               (TIMER_BASE+0X004)      /* 通道1当前计数值寄存器 */
#define TIMER_T1CR                (TIMER_BASE+0X008)      /* 通道1控制寄存器 */
#define TIMER_T1ISCR              (TIMER_BASE+0X00C)      /* 通道1中断状态清除寄存器 */
#define TIMER_T1IMSR              (TIMER_BASE+0X010)      /* 通道1中断屏蔽状态寄存器 */
#define TIMER_T2LCR               (TIMER_BASE+0X020)      /* 通道2加载计数寄存器 */
#define TIMER_T2CCR               (TIMER_BASE+0X024)      /* 通道2当前计数值寄存器 */
#define TIMER_T2CR                (TIMER_BASE+0X028)      /* 通道2控制寄存器 */
#define TIMER_T2ISCR              (TIMER_BASE+0X02C)      /* 通道2中断状态清除寄存器 */
#define TIMER_T2IMSR              (TIMER_BASE+0X030)      /* 通道2中断屏蔽状态寄存器 */
#define TIMER_T3LCR               (TIMER_BASE+0X040)      /* 通道3加载计数寄存器 */
#define TIMER_T3CCR               (TIMER_BASE+0X044)      /* 通道3当前计数值寄存器 */
#define TIMER_T3CR                (TIMER_BASE+0X048)      /* 通道3控制寄存器 */
#define TIMER_T3ISCR              (TIMER_BASE+0X04C)      /* 通道3中断状态清除寄存器 */
#define TIMER_T3IMSR              (TIMER_BASE+0X050)      /* 通道3中断屏蔽状态寄存器 */
#define TIMER_T3CAPR              (TIMER_BASE+0X054)      /* 通道3捕获寄存器 */
#define TIMER_T4LCR               (TIMER_BASE+0X060)      /* 通道4加载计数寄存器 */
#define TIMER_T4CCR               (TIMER_BASE+0X064)      /* 通道4当前计数值寄存器 */
#define TIMER_T4CR                (TIMER_BASE+0X068)      /* 通道4控制寄存器 */
#define TIMER_T4ISCR              (TIMER_BASE+0X06C)      /* 通道4中断状态清除寄存器 */
#define TIMER_T4IMSR              (TIMER_BASE+0X070)      /* 通道4中断屏蔽状态寄存器 */
#define TIMER_T4CAPR              (TIMER_BASE+0X074)      /* 通道4捕获寄存器 */
#define TIMER_T5LCR               (TIMER_BASE+0X080)      /* 通道5加载计数寄存器 */
#define TIMER_T5CCR               (TIMER_BASE+0X084)      /* 通道5当前计数值寄存器 */
#define TIMER_T5CR                (TIMER_BASE+0X088)      /* 通道5控制寄存器 */
#define TIMER_T5ISCR              (TIMER_BASE+0X08C)      /* 通道5中断状态清除寄存器 */
#define TIMER_T5IMSR              (TIMER_BASE+0X090)      /* 通道5中断屏蔽状态寄存器 */
#define TIMER_T5CAPR              (TIMER_BASE+0X094)      /* 通道5捕获寄存器 */
#define TIMER_T6LCR               (TIMER_BASE+0X0A0)      /* 通道6加载计数寄存器 */
#define TIMER_T6CCR               (TIMER_BASE+0X0A4)      /* 通道6当前计数值寄存器 */
#define TIMER_T6CR                (TIMER_BASE+0X0A8)      /* 通道6控制寄存器 */
#define TIMER_T6ISCR              (TIMER_BASE+0X0AC)      /* 通道6中断状态清除寄存器 */
#define TIMER_T6IMSR              (TIMER_BASE+0X0B0)      /* 通道6中断屏蔽状态寄存器 */
#define TIMER_T6CAPR              (TIMER_BASE+0X0B4)      /* 通道6捕获寄存器 */
#define TIMER_T7LCR               (TIMER_BASE+0X0C0)      /* 通道7加载计数寄存器 */
#define TIMER_T7CCR               (TIMER_BASE+0X0C4)      /* 通道7当前计数值寄存器 */
#define TIMER_T7CR                (TIMER_BASE+0X0C8)      /* 通道7控制寄存器 */
#define TIMER_T7ISCR              (TIMER_BASE+0X0CC)      /* 通道7中断状态清除寄存器 */
#define TIMER_T7IMSR              (TIMER_BASE+0X0D0)      /* 通道7中断屏蔽状态寄存器 */
#define TIMER_T8LCR               (TIMER_BASE+0X0E0)      /* 通道8加载计数寄存器 */
#define TIMER_T8CCR               (TIMER_BASE+0X0E4)      /* 通道8当前计数值寄存器 */
#define TIMER_T8CR                (TIMER_BASE+0X0E8)      /* 通道8控制寄存器 */
#define TIMER_T8ISCR              (TIMER_BASE+0X0EC)      /* 通道8中断状态清除寄存器 */
#define TIMER_T8IMSR              (TIMER_BASE+0X0F0)      /* 通道8中断屏蔽状态寄存器 */
#define TIMER_T9LCR               (TIMER_BASE+0X100)      /* 通道9加载计数寄存器 */
#define TIMER_T9CCR               (TIMER_BASE+0X104)      /* 通道9当前计数值寄存器 */
#define TIMER_T9CR                (TIMER_BASE+0X108)      /* 通道9控制寄存器 */
#define TIMER_T9ISCR              (TIMER_BASE+0X10C)      /* 通道9中断状态清除寄存器 */
#define TIMER_T9IMSR              (TIMER_BASE+0X110)      /* 通道9中断屏蔽状态寄存器 */
#define TIMER_T10LCR              (TIMER_BASE+0X120)      /* 通道10加载计数寄存器 */
#define TIMER_T10CCR              (TIMER_BASE+0X124)      /* 通道10当前计数值寄存器 */
#define TIMER_T10CR               (TIMER_BASE+0X128)      /* 通道10控制寄存器 */
#define TIMER_T10ISCR             (TIMER_BASE+0X12C)      /* 通道10中断状态清除寄存器 */
#define TIMER_T10IMSR             (TIMER_BASE+0X130)      /* 通道10中断屏蔽状态寄存器 */
#define TIMER_TIMSR               (TIMER_BASE+0X140)      /* TIMER中断屏蔽状态寄存器 */
#define TIMER_TISCR               (TIMER_BASE+0X144)      /* TIMER中断状态清除寄存器 */
#define TIMER_TISR                (TIMER_BASE+0X148)      /* TIMER中断状态寄存器 */



/*
 *  PWM模块
 *  基址: 0x10004000
 */

#define PWM0_CTRL                 (PWM_BASE+0X000)        /* PWM0控制寄存器 */
#define PWM0_DIV                  (PWM_BASE+0X004)        /* PWM0分频寄存器 */
#define PWM0_PERIOD               (PWM_BASE+0X008)        /* PWM0周期寄存器 */
#define PWM0_DATA                 (PWM_BASE+0X00C)        /* PWM0数据寄存器 */
#define PWM0_CNT                  (PWM_BASE+0X010)        /* PWM0计数寄存器 */
#define PWM0_STATUS               (PWM_BASE+0X014)        /* PWM0状态寄存器 */
#define PWM1_CTRL                 (PWM_BASE+0X020)        /* PWM1控制寄存器 */
#define PWM1_DIV                  (PWM_BASE+0X024)        /* PWM1分频寄存器 */
#define PWM1_PERIOD               (PWM_BASE+0X028)        /* PWM1周期寄存器 */
#define PWM1_DATA                 (PWM_BASE+0X02C)        /* PWM1数据寄存器 */
#define PWM1_CNT                  (PWM_BASE+0X030)        /* PWM1计数寄存器 */
#define PWM1_STATUS               (PWM_BASE+0X034)        /* PWM1状态寄存器 */
#define PWM2_CTRL                 (PWM_BASE+0X040)        /* PWM2控制寄存器 */
#define PWM2_DIV                  (PWM_BASE+0X044)        /* PWM2分频寄存器 */
#define PWM2_PERIOD               (PWM_BASE+0X048)        /* PWM2周期寄存器 */
#define PWM2_DATA                 (PWM_BASE+0X04C)        /* PWM2数据寄存器 */
#define PWM2_CNT                  (PWM_BASE+0X050)        /* PWM2计数寄存器 */
#define PWM2_STATUS               (PWM_BASE+0X054)        /* PWM2状态寄存器 */
#define PWM3_CTRL                 (PWM_BASE+0X060)        /* PWM3控制寄存器 */
#define PWM3_DIV                  (PWM_BASE+0X064)        /* PWM3分频寄存器 */
#define PWM3_PERIOD               (PWM_BASE+0X068)        /* PWM3周期寄存器 */
#define PWM3_DATA                 (PWM_BASE+0X06C)        /* PWM3数据寄存器 */
#define PWM3_CNT                  (PWM_BASE+0X070)        /* PWM3计数寄存器 */
#define PWM3_STATUS               (PWM_BASE+0X074)        /* PWM3状态寄存器 */
#define PWM_INTMASK               (PWM_BASE+0X080)        /* PWM中断屏蔽寄存器 */
#define PWM_INT                   (PWM_BASE+0X084)        /* PWM中断寄存器 */
#define PWM_ENABLE                (PWM_BASE+0X088)        /* PWM使能寄存器 */


/*
 *  UART0模块
 *  基址: 0x10005000
 */

#define UART0_DLBL                (UART0_BASE+0X000)      /* 波特率设置低八位寄存器 */
#define UART0_RXFIFO              (UART0_BASE+0X000)      /* 接收FIFO */
#define UART0_TXFIFO              (UART0_BASE+0X000)      /* 发送FIFO */
#define UART0_DLBH                (UART0_BASE+0X004)      /* 波特率设置高八位寄存器 */
#define UART0_IER                 (UART0_BASE+0X004)      /* 中断使能寄存器 */
#define UART0_IIR                 (UART0_BASE+0X008)      /* 中断识别寄存器 */
#define UART0_FCR                 (UART0_BASE+0X008)      /* FIFO控制寄存器 */
#define UART0_LCR                 (UART0_BASE+0X00C)      /* 行控制寄存器 */
#define UART0_MCR                 (UART0_BASE+0X010)      /* Modem控制寄存器 */
#define UART0_LSR                 (UART0_BASE+0X014)      /* 行状态寄存器 */
#define UART0_MSR                 (UART0_BASE+0X018)      /* Modem状态寄存器 */


/*
 *  UART1模块
 *  基址: 0x10006000
 */

#define UART1_DLBL                (UART1_BASE+0X000)      /* 波特率设置低八位寄存器 */
#define UART1_RXFIFO              (UART1_BASE+0X000)      /* 接收FIFO */
#define UART1_TXFIFO              (UART1_BASE+0X000)      /* 发送FIFO */
#define UART1_DLBH                (UART1_BASE+0X004)      /* 波特率设置高八位寄存器 */
#define UART1_IER                 (UART1_BASE+0X004)      /* 中断使能寄存器 */
#define UART1_IIR                 (UART1_BASE+0X008)      /* 中断识别寄存器 */
#define UART1_FCR                 (UART1_BASE+0X008)      /* FIFO控制寄存器 */
#define UART1_LCR                 (UART1_BASE+0X00C)      /* 行控制寄存器 */
#define UART1_MCR                 (UART1_BASE+0X010)      /* Modem控制寄存器 */
#define UART1_LSR                 (UART1_BASE+0X014)      /* 行状态寄存器 */
#define UART1_MSR                 (UART1_BASE+0X018)      /* Modem状态寄存器 */


/*
 *  UART2模块
 *  基址: 0x10007000
 */

#define UART2_DLBL                (UART2_BASE+0X000)      /* 波特率设置低八位寄存器 */
#define UART2_RXFIFO              (UART2_BASE+0X000)      /* 接收FIFO */
#define UART2_TXFIFO              (UART2_BASE+0X000)      /* 发送FIFO */
#define UART2_DLBH                (UART2_BASE+0X004)      /* 波特率设置高八位寄存器 */
#define UART2_IER                 (UART2_BASE+0X004)      /* 中断使能寄存器 */
#define UART2_IIR                 (UART2_BASE+0X008)      /* 中断识别寄存器 */
#define UART2_FCR                 (UART2_BASE+0X008)      /* FIFO控制寄存器 */
#define UART2_LCR                 (UART2_BASE+0X00C)      /* 行控制寄存器 */
#define UART2_MCR                 (UART2_BASE+0X010)      /* Modem控制寄存器 */
#define UART2_LSR                 (UART2_BASE+0X014)      /* 行状态寄存器 */
#define UART2_MSR                 (UART2_BASE+0X018)      /* Modem状态寄存器 */


/*
 *  UART3模块
 *  基址: 0x10008000
 */

#define UART3_DLBL                (UART3_BASE+0X000)      /* 波特率设置低八位寄存器 */
#define UART3_RXFIFO              (UART3_BASE+0X000)      /* 接收FIFO */
#define UART3_TXFIFO              (UART3_BASE+0X000)      /* 发送FIFO */
#define UART3_DLBH                (UART3_BASE+0X004)      /* 波特率设置高八位寄存器 */
#define UART3_IER                 (UART3_BASE+0X004)      /* 中断使能寄存器 */
#define UART3_IIR                 (UART3_BASE+0X008)      /* 中断识别寄存器 */
#define UART3_FCR                 (UART3_BASE+0X008)      /* FIFO控制寄存器 */
#define UART3_LCR                 (UART3_BASE+0X00C)      /* 行控制寄存器 */
#define UART3_MCR                 (UART3_BASE+0X010)      /* Modem控制寄存器 */
#define UART3_LSR                 (UART3_BASE+0X014)      /* 行状态寄存器 */
#define UART3_MSR                 (UART3_BASE+0X018)      /* Modem状态寄存器 */


/*
 *  SSI模块
 *  基址: 0x10009000
 */

#define SSI_CONTROL0              (SSI_BASE+0X000)        /* 控制寄存器0 */
#define SSI_CONTROL1              (SSI_BASE+0X004)        /* 控制寄存器1 */
#define SSI_SSIENR                (SSI_BASE+0X008)        /* SSI使能寄存器 */
#define SSI_MWCR                  (SSI_BASE+0X00C)        /* Microwire控制寄存器 */
#define SSI_SER                   (SSI_BASE+0X010)        /* 从设备使能寄存器 */
#define SSI_BAUDR                 (SSI_BASE+0X014)        /* 波特率设置寄存器 */
#define SSI_TXFTLR                (SSI_BASE+0X018)        /* 发送FIFO阈值寄存器 */
#define SSI_RXFTLR                (SSI_BASE+0X01C)        /* 接收FIFO阈值寄存器 */
#define SSI_TXFLR                 (SSI_BASE+0X020)        /* 发送FIFO状态寄存器 */
#define SSI_RXFLR                 (SSI_BASE+0X024)        /* 接收FIFO状态寄存器 */
#define SSI_SR                    (SSI_BASE+0X028)        /* 状态寄存器 */
#define SSI_IMR                   (SSI_BASE+0X02C)        /* 中断屏蔽寄存器 */
#define SSI_ISR                   (SSI_BASE+0X030)        /* 中断最终状态寄存器 */
#define SSI_RISR                  (SSI_BASE+0X034)        /* 中断原始状态寄存器 */
#define SSI_TXOICR                (SSI_BASE+0X038)        /* 发送FIFO上溢中断清除寄存器 */
#define SSI_RXOICR                (SSI_BASE+0X03C)        /* 接收FIFO上溢中断清除寄存器 */
#define SSI_RXUICR                (SSI_BASE+0X040)        /* 接收FIFO下溢中断清除寄存器 */
#define SSI_ICR                   (SSI_BASE+0X02C)        /* 中断清除寄存器 */
#define SSI_DMACR                 (SSI_BASE+0X04C)        /* DMA控制寄存器 */
#define SSI_DMATDLR               (SSI_BASE+0X050)        /* DMA发送状态寄存器 */
#define SSI_DMARDLR               (SSI_BASE+0X054)        /* DMA接收状态寄存器 */
#define SSI_DR                    (SSI_BASE+0X060)        /* 数据寄存器 */


/*
 *  I2S模块
 *  基址: 0x1000A000
 */

#define I2S_CTRL                  (I2S_BASE+0X000)        /* I2S控制寄存器 */
#define I2S_DATA                  (I2S_BASE+0X004)        /* I2S数据寄存器 */
#define I2S_INT                   (I2S_BASE+0X008)        /* I2S中断寄存器 */
#define I2S_STATUS                (I2S_BASE+0X00C)        /* I2S状态寄存器 */


/*
 *  SD模块
 *  基址: 0x1000B000
 */

#define SDC_CLOCK_CONTROL         (SD_BASE+0x00)          /* SDIO时钟控制寄存器 */
#define SDC_SOFTWARE_RESET        (SD_BASE+0X04)          /* SDIO软件复位寄存器 */
#define SDC_ARGUMENT              (SD_BASE+0X08)          /* SDIO命令参数寄存器 */
#define SDC_COMMAND               (SD_BASE+0X0C)          /* SDIO命令控制寄存器 */
#define SDC_BLOCK_SIZE            (SD_BASE+0X10)          /* SDIO数据块长度寄存器 */
#define SDC_BLOCK_COUNT           (SD_BASE+0X14)          /* SDIO数据块数目寄存器 */
#define SDC_TRANSFER_MODE         (SD_BASE+0X18)          /* SDIO传输模式选择寄存器 */
#define SDC_RESPONSE0             (SD_BASE+0X1c)          /* SDIO响应寄存器0 */
#define SDC_RESPONSE1             (SD_BASE+0X20)          /* SDIO响应寄存器1 */
#define SDC_RESPONSE2             (SD_BASE+0X24)          /* SDIO响应寄存器2 */
#define SDC_RESPONSE3             (SD_BASE+0X28)          /* SDIO响应寄存器3 */
#define SDC_READ_TIMEOUT_CONTROL  (SD_BASE+0X2c)          /* SDIO读超时控制寄存器 */
#define SDC_INTERRUPT_STATUS      (SD_BASE+0X30)          /* SDIO中断状态寄存器 */
#define SDC_INTERRUPT_STATUS_MASK (SD_BASE+0X34)          /* SDIO中断状态屏蔽寄存器 */
#define SDC_READ_BUFER_ACCESS     (SD_BASE+0X38)          /* SDIO接收FIFO */
#define SDC_WRITE_BUFER_ACCESS    (SD_BASE+0X3c)          /* SDIO发送FIFO */



/*
 *  SMC0模块
 *  基址: 0x1000C000
 */

#define SMC0_CTRL                 (SMC0_BASE+0X000)       /* SMC0控制寄存器 */
#define SMC0_INT                  (SMC0_BASE+0X004)       /* SMC0中断寄存器 */
#define SMC0_FD                   (SMC0_BASE+0X008)       /* SMC0基本单元时间寄存器 */
#define SMC0_CT                   (SMC0_BASE+0X00C)       /* SMC0字符传输时间寄存器 */
#define SMC0_BT                   (SMC0_BASE+0X010)       /* SMC0块传输时间寄存器 */



/*
 *  SMC1模块
 *  基址: 0x1000D000
 */

#define SMC1_CTRL                 (SMC1_BASE+0X000)       /* SMC1控制寄存器 */
#define SMC1_INT                  (SMC1_BASE+0X004)       /* SMC1中断寄存器 */
#define SMC1_FD                   (SMC1_BASE+0X008)       /* SMC1基本单元时间寄存器 */
#define SMC1_CT                   (SMC1_BASE+0X00C)       /* SMC1字符传输时间寄存器 */
#define SMC1_BT                   (SMC1_BASE+0X010)       /* SMC1块传输时间寄存器 */



/*
 *  USBD模块
 *  基址: 0x1000E000
 */

#define USBD_PROTOCOLINTR         (USBD_BASE+0X000)       /* USB协议中断寄存器 */
#define USBD_INTRMASK             (USBD_BASE+0X004)       /* USB中断屏蔽寄存器 */
#define USBD_INTRCTRL             (USBD_BASE+0X008)       /* USB中断类型控制寄存器 */
#define USBD_EPINFO               (USBD_BASE+0X00C)       /* USB活动端点状态寄存器 */
#define USBD_BCONFIGURATIONVALUE  (USBD_BASE+0X010)       /* SET_CCONFIGURATION记录 */
#define USBD_BMATTRIBUTES         (USBD_BASE+0X014)       /* 当前配置属性寄存器 */
#define USBD_DEVSPEED             (USBD_BASE+0X018)       /* 当前设备工作速度寄存器 */
#define USBD_FRAMENUMBER          (USBD_BASE+0X01C)       /* 记录当前SOF包内的帧号 */
#define USBD_EPTRANSACTIONS0      (USBD_BASE+0X020)       /* 记录下次要求的传输次数 */
#define USBD_EPTRANSACTIONS1      (USBD_BASE+0X024)       /* 记录下次要求的传输次数 */
#define USBD_APPIFUPDATE          (USBD_BASE+0X028)       /* 接口号快速更新寄存器 */
#define USBD_CFGINTERFACE0        (USBD_BASE+0X02C)       /* 记录接口的值 */
#define USBD_CFGINTERFACE1        (USBD_BASE+0X030)       /* 记录接口的值 */
#define USBD_CFGINTERFACE2        (USBD_BASE+0X034)       /* 记录接口的值 */
#define USBD_CFGINTERFACE3        (USBD_BASE+0X038)       /* 记录接口的值 */
#define USBD_CFGINTERFACE4        (USBD_BASE+0X03C)       /* 记录接口的值 */
#define USBD_CFGINTERFACE5        (USBD_BASE+0X040)       /* 记录接口的值 */
#define USBD_CFGINTERFACE6        (USBD_BASE+0X044)       /* 记录接口的值 */
#define USBD_CFGINTERFACE7        (USBD_BASE+0X048)       /* 记录接口的值 */
#define USBD_CFGINTERFACE8        (USBD_BASE+0X04C)       /* 记录接口的值 */
#define USBD_CFGINTERFACE9        (USBD_BASE+0X050)       /* 记录接口的值 */
#define USBD_CFGINTERFACE10       (USBD_BASE+0X054)       /* 记录接口的值 */
#define USBD_CFGINTERFACE11       (USBD_BASE+0X058)       /* 记录接口的值 */
#define USBD_CFGINTERFACE12       (USBD_BASE+0X05C)       /* 记录接口的值 */
#define USBD_CFGINTERFACE13       (USBD_BASE+0X060)       /* 记录接口的值 */
#define USBD_CFGINTERFACE14       (USBD_BASE+0X064)       /* 记录接口的值 */
#define USBD_CFGINTERFACE15       (USBD_BASE+0X068)       /* 记录接口的值 */
#define USBD_CFGINTERFACE16       (USBD_BASE+0X06C)       /* 记录接口的值 */
#define USBD_CFGINTERFACE17       (USBD_BASE+0X070)       /* 记录接口的值 */
#define USBD_CFGINTERFACE18       (USBD_BASE+0X074)       /* 记录接口的值 */
#define USBD_CFGINTERFACE19       (USBD_BASE+0X078)       /* 记录接口的值 */
#define USBD_CFGINTERFACE20       (USBD_BASE+0X07C)       /* 记录接口的值 */
#define USBD_CFGINTERFACE21       (USBD_BASE+0X080)       /* 记录接口的值 */
#define USBD_CFGINTERFACE22       (USBD_BASE+0X084)       /* 记录接口的值 */
#define USBD_CFGINTERFACE23       (USBD_BASE+0X088)       /* 记录接口的值 */
#define USBD_CFGINTERFACE24       (USBD_BASE+0X08C)       /* 记录接口的值 */
#define USBD_CFGINTERFACE25       (USBD_BASE+0X090)       /* 记录接口的值 */
#define USBD_CFGINTERFACE26       (USBD_BASE+0X094)       /* 记录接口的值 */
#define USBD_CFGINTERFACE27       (USBD_BASE+0X098)       /* 记录接口的值 */
#define USBD_CFGINTERFACE28       (USBD_BASE+0X09C)       /* 记录接口的值 */
#define USBD_CFGINTERFACE29       (USBD_BASE+0X0A0)       /* 记录接口的值 */
#define USBD_CFGINTERFACE30       (USBD_BASE+0X0A4)       /* 记录接口的值 */
#define USBD_CFGINTERFACE31       (USBD_BASE+0X0A8)       /* 记录接口的值 */
#define USBD_PKTPASSEDCTRL        (USBD_BASE+0X0AC)       /* 记录成功接收的包数 */
#define USBD_PKTDROPPEDCTRL       (USBD_BASE+0X0B0)       /* 记录丢失的包数 */
#define USBD_CRCERRCTRL           (USBD_BASE+0X0B4)       /* 记录CRC错误的包数 */
#define USBD_BITSTUFFERRCTRL      (USBD_BASE+0X0B8)       /* 记录位填充错误的包数 */
#define USBD_PIDERRCTRL           (USBD_BASE+0X0BC)       /* 记录PID错误的包数 */
#define USBD_FRAMINGERRCTL        (USBD_BASE+0X0C0)       /* 记录有SYNC和EOP的包数 */
#define USBD_TXPKTCTRL            (USBD_BASE+0X0C4)       /* 记录发送包的数量 */
#define USBD_STATCTRLOV           (USBD_BASE+0X0C8)       /* 记录统计寄存器溢出情况 */
#define USBD_TXLENGTH             (USBD_BASE+0X0CC)       /* 记录每次IN传输事务包长度 */
#define USBD_RXLENGTH             (USBD_BASE+0X0D0)       /* 记录OUT传输事务包长度 */
#define USBD_RESUME               (USBD_BASE+0X0D4)       /* USB唤醒寄存器 */
#define USBD_READFLAG             (USBD_BASE+0X0D8)       /* 读异步状态寄存器标志 */
#define USBD_RECEIVETYPE          (USBD_BASE+0X0DC)       /* 传输状态寄存器 */
#define USBD_APPLOCK              (USBD_BASE+0X0E0)       /* 锁信号寄存器 */
#define USBD_EP0OUTADDR           (USBD_BASE+0X100)       /* 端点0端点号和方向 */
#define USBD_EP0OUTBMATTR         (USBD_BASE+0X104)       /* 端点0类型寄存器 */
#define USBD_EP0OUTMAXPKTSIZE     (USBD_BASE+0X108)       /* 端点0最大包尺寸寄存器 */
#define USBD_EP0OUTIFNUM          (USBD_BASE+0X10C)       /* 端点0接口号寄存器 */
#define USBD_EP0OUTSTAT           (USBD_BASE+0X110)       /* 端点0状态寄存器 */
#define USBD_EP0OUTBMREQTYPE      (USBD_BASE+0X114)       /* 端点0 SETUP事务请求类 */
#define USBD_EP0OUTBREQUEST       (USBD_BASE+0X118)       /* 端点0 SETUP事务请求内容 */
#define USBD_EP0OUTWVALUE         (USBD_BASE+0X11C)       /* 端点0 SETUP事务请求值 */
#define USBD_EP0OUTWINDEX         (USBD_BASE+0X120)       /* 端点0 SETUP事务请求索引 */
#define USBD_EP0OUTWLENGTH        (USBD_BASE+0X120)       /* 端点0 SETUP事务请求长度 */
#define USBD_EP0OUTSYNCHFRAME     (USBD_BASE+0X128)       /* 端点0同步包帧号 */
#define USBD_EP1OUTADDR           (USBD_BASE+0X12C)       /* 端点1输出端点号和方向 */
#define USBD_EP1OUTBMATTR         (USBD_BASE+0X130)       /* 端点1输出类型寄存器 */
#define USBD_EP1OUTMAXPKTSIZE     (USBD_BASE+0X134)       /* 端点1输出最大包尺寸寄存器 */
#define USBD_EP1OUTIFNUM          (USBD_BASE+0X138)       /* 端点1输出接口号寄存器 */
#define USBD_EP1OUTSTAT           (USBD_BASE+0X13C)       /* 端点1输出状态寄存器 */
#define USBD_EP1OUTBMREQTYPE      (USBD_BASE+0X140)       /* 端点1输出SETUP事务请求类型 */
#define USBD_EP1OUTBREQUEST       (USBD_BASE+0X144)       /* 端点1输出SETUP事务请求内容 */
#define USBD_EP1OUTWVALUE         (USBD_BASE+0X148)       /* 端点1输出SETUP事务请求值 */
#define USBD_EP1OUTWINDX          (USBD_BASE+0X14C)       /* 端点1输出SETUP事务请求索引 */
#define USBD_EP1OUTWLENGH         (USBD_BASE+0X150)       /* 端点1输出SETUP事务请求域长度 */
#define USBD_EP1OUTSYNCHFRAME     (USBD_BASE+0X154)       /* 端点1输出同步包帧号 */
#define USBD_EP1INADDR            (USBD_BASE+0X158)       /* 端点1输入端点号和方向 */
#define USBD_EP1INBMATTR          (USBD_BASE+0X15C)       /* 端点1输入类型寄存器 */
#define USBD_EP1INMAXPKTSIZE      (USBD_BASE+0X160)       /* 端点1输入最大包尺寸寄存器 */
#define USBD_EP1INIFNUM           (USBD_BASE+0X164)       /* 端点1输入接口号寄存器 */
#define USBD_EP1INSTAT            (USBD_BASE+0X168)       /* 端点1输入状态寄存器 */
#define USBD_EP1INBMREQTYPE       (USBD_BASE+0X16C)       /* 端点1输入SETUP事务请求类型 */
#define USBD_EP1INBREQUEST        (USBD_BASE+0X170)       /* 端点1输入SETUP事务请求内容 */
#define USBD_EP1INWVALUE          (USBD_BASE+0X174)       /* 端点1输入SETUP事务请求值 */
#define USBD_EP1INWINDEX          (USBD_BASE+0X178)       /* 端点1输入SETUP事务请求索引 */
#define USBD_EP1INWLENGTH         (USBD_BASE+0X17C)       /* 端点1输入SETUP事务请求域长度 */
#define USBD_EP1INSYNCHFRAME      (USBD_BASE+0X180)       /* 端点1输入同步包帧号 */
#define USBD_EP2OUTADDR           (USBD_BASE+0X184)       /* 端点2输出端点号和方向 */
#define USBD_EP2OUTBMATTR         (USBD_BASE+0X188)       /* 端点2输出类型寄存器 */
#define USBD_EP2OUTMAXPKTSIZE     (USBD_BASE+0X18C)       /* 端点2输出最大包尺寸寄存器 */
#define USBD_EP2OUTIFNUM          (USBD_BASE+0X190)       /* 端点2输出接口号寄存器 */
#define USBD_EP2OUTSTAT           (USBD_BASE+0X194)       /* 端点2输出状态寄存器 */
#define USBD_EP2OUTBMREQTYPE      (USBD_BASE+0X198)       /* 端点2输出SETUP事务请求类型 */
#define USBD_EP2OUTBREQUEST       (USBD_BASE+0X19C)       /* 端点2输出SETUP事务请求内容 */
#define USBD_EP2OUTWVALUE         (USBD_BASE+0X1A0)       /* 端点2输出SETUP事务请求值 */
#define USBD_EP2OUTWINDEX         (USBD_BASE+0X1A4)       /* 端点2输出SETUP事务请求索引 */
#define USBD_EP2OUTWLENGTH        (USBD_BASE+0X1A8)       /* 端点2输出SETUP事务请求域长度 */
#define USBD_EP2OUTSYNCHFRAME     (USBD_BASE+0X1AC)       /* 端点2输出同步包帧号 */
#define USBD_EP2INADDR            (USBD_BASE+0X1B0)       /* 端点2输入端点号和方向 */
#define USBD_EP2INBMATTR          (USBD_BASE+0X1B4)       /* 端点2输入类型寄存器 */
#define USBD_EP2INMAXPKTSIZE      (USBD_BASE+0X1B8)       /* 端点2输入最大包尺寸寄存器 */
#define USBD_EP2INIFNUM           (USBD_BASE+0X1BC)       /* 端点2输入接口号寄存器 */
#define USBD_EP2INSTAT            (USBD_BASE+0X1C0)       /* 端点2输入状态寄存器 */
#define USBD_EP2INBMREQTYPE       (USBD_BASE+0X1C4)       /* 端点2输入SETUP事务请求类型 */
#define USBD_EP2INBREQUEST        (USBD_BASE+0X1C8)       /* 端点2输入SETUP事务请求内容 */
#define USBD_EP2INWVALUE          (USBD_BASE+0X1CC)       /* 端点2输入SETUP事务请求值 */
#define USBD_EP2INWINDEX          (USBD_BASE+0X1D0)       /* 端点2输入SETUP事务请求索引 */
#define USBD_EP2INWLENGTH         (USBD_BASE+0X1D4)       /* 端点2输入SETUP事务请求域长度 */
#define USBD_EP2INSYNCHFRAME      (USBD_BASE+0X1D8)       /* 端点2输入同步包帧号 */
#define USBD_RXFIFO               (USBD_BASE+0X200)       /* 接受FIFO */
#define USBD_TXFIFO               (USBD_BASE+0X300)       /* 发送FIFO */


/*
 *  GPIO模块
 *  基址: 0x1000F000
 */

#define GPIO_DBCLK_DIV            (GPIO_BASE+0X000)       /* 去毛刺采用时钟分频比配置寄存器 */
#define GPIO_PORTA_DIR            (GPIO_BASE+0X004)       /* A组端口输入输出方向配置寄存器 */
#define GPIO_PORTA_SEL            (GPIO_BASE+0X008)       /* A组端口通用用途选择配置寄存器 */
#define GPIO_PORTA_INCTL          (GPIO_BASE+0X00C)       /* A组端口通用用途输入时类型配置寄存器 */
#define GPIO_PORTA_INTRCTL        (GPIO_BASE+0X010)       /* A组端口中断触发类型配置寄存器 */
#define GPIO_PORTA_INTRCLR        (GPIO_BASE+0X014)       /* A组端口通用用途中断清除配置寄存器 */
#define GPIO_PORTA_DATA           (GPIO_BASE+0X018)       /* A组端口通用用途数据配置寄存器 */
#define GPIO_PORTB_DIR            (GPIO_BASE+0X01C)       /* B组端口输入输出方向配置寄存器 */
#define GPIO_PORTB_SEL            (GPIO_BASE+0X020)       /* B组端口通用用途选择配置寄存器 */
#define GPIO_PORTB_DATA           (GPIO_BASE+0X024)       /* B组端口通用用途数据配置寄存器 */
#define GPIO_PORTC_DIR            (GPIO_BASE+0X028)       /* C组端口输入输出方向配置寄存器 */
#define GPIO_PORTC_SEL            (GPIO_BASE+0X02C)       /* C组端口通用用途选择配置寄存器 */
#define GPIO_PORTC_DATA           (GPIO_BASE+0X030)       /* C组端口通用用途数据配置寄存器 */
#define GPIO_PORTD_DIR            (GPIO_BASE+0X034)       /* D组端口输入输出方向配置寄存器 */
#define GPIO_PORTD_SEL            (GPIO_BASE+0X038)       /* D组端口通用用途选择配置寄存器 */
#define GPIO_PORTD_SPECII         (GPIO_BASE+0X03C)       /* D组端口专用用途2选择配置寄存器 */
#define GPIO_PORTD_DATA           (GPIO_BASE+0X040)       /* D组端口通用用途数据配置寄存器 */
#define GPIO_PORTE_DIR            (GPIO_BASE+0X044)       /* E组端口输入输出方向配置寄存器 */
#define GPIO_PORTE_SEL            (GPIO_BASE+0X048)       /* E组端口通用用途选择配置寄存器 */
#define GPIO_PORTE_DATA           (GPIO_BASE+0X04C)       /* E组端口通用用途数据配置寄存器 */
#define GPIO_PORTF_DIR            (GPIO_BASE+0X050)       /* F组端口输入输出方向配置寄存器 */
#define GPIO_PORTF_SEL            (GPIO_BASE+0X054)       /* F组端口通用用途选择配置寄存器 */
#define GPIO_PORTF_INCTL          (GPIO_BASE+0X058)       /* F组端口通用用途输入时类型配置寄存器 */
#define GPIO_PORTF_INTRCTL        (GPIO_BASE+0X05C)       /* F组端口中断触发类型配置寄存器 */
#define GPIO_PORTF_INTRCLR        (GPIO_BASE+0X060)       /* F组端口通用用途中断清除配置寄存器 */
#define GPIO_PORTF_DATA           (GPIO_BASE+0X064)       /* F组端口通用用途数据配置寄存器 */
#define GPIO_PORTG_DIR            (GPIO_BASE+0X068)       /* G组端口输入输出方向配置寄存器 */
#define GPIO_PORTG_SEL            (GPIO_BASE+0X06C)       /* G组端口通用用途选择配置寄存器 */
#define GPIO_PORTG_DATA           (GPIO_BASE+0X070)       /* G组端口通用用途数据配置寄存器 */
#define GPIO_PORTH_DIR            (GPIO_BASE+0X07C)       /* H组端口输入输出方向配置寄存器 */
#define GPIO_PORTH_SEL            (GPIO_BASE+0X078)       /* H组端口通用用途选择配置寄存器 */
#define GPIO_PORTH_DATA           (GPIO_BASE+0X07C)       /* H组端口通用用途数据配置寄存器 */
#define GPIO_PORTI_DIR            (GPIO_BASE+0X080)       /* I组端口输入输出方向配置寄存器 */
#define GPIO_PORTI_SEL            (GPIO_BASE+0X084)       /* I组端口通用用途选择配置寄存器 */
#define GPIO_PORTI_DATA           (GPIO_BASE+0X088)       /* I组端口通用用途数据配置寄存器 */



/*
 *  EMI模块
 *  基址: 0x11000000
 */

#define EMI_CSACONF               (EMI_BASE+0X000)        /* CSA参数配置寄存器 */
#define EMI_CSBCONF               (EMI_BASE+0X004)        /* CSB参数配置寄存器 */
#define EMI_CSCCONF               (EMI_BASE+0X008)        /* CSC参数配置寄存器 */
#define EMI_CSDCONF               (EMI_BASE+0X00C)        /* CSD参数配置寄存器 */
#define EMI_CSECONF               (EMI_BASE+0X010)        /* CSE参数配置寄存器 */
#define EMI_CSFCONF               (EMI_BASE+0X014)        /* CSF参数配置寄存器 */
#define EMI_SDCONF1               (EMI_BASE+0X018)        /* SDRAM时序配置寄存器1 */
#define EMI_SDCONF2               (EMI_BASE+0X01C)        /* SDRAM时序配置寄存器2, SDRAM初始化用到的配置信息 */
#define EMI_REMAPCONF             (EMI_BASE+0X020)        /* 片选空间及地址映射REMAP配置寄存器 */
#define EMI_NAND_ADDR1            (EMI_BASE+0X100)        /* NAND FLASH的地址寄存器1 */
#define EMI_NAND_COM              (EMI_BASE+0X104)        /* NAND FLASH的控制字寄存器 */
#define EMI_NAND_STA              (EMI_BASE+0X10C)        /* NAND FLASH的状态寄存器 */
#define EMI_ERR_ADDR1             (EMI_BASE+0X110)        /* 读操作出错的地址寄存器1 */
#define EMI_ERR_ADDR2             (EMI_BASE+0X114)        /* 读操作出错的地址寄存器2 */
#define EMI_NAND_CONF1            (EMI_BASE+0X118)        /* NAND FLASH的配置器存器1 */
#define EMI_NAND_INTR             (EMI_BASE+0X11C)        /* NAND FLASH中断寄存器 */
#define EMI_NAND_ECC              (EMI_BASE+0X120)        /* ECC校验完成寄存器 */
#define EMI_NAND_IDLE             (EMI_BASE+0X124)        /* NAND FLASH空闲寄存器 */
#define EMI_NAND_CONF2            (EMI_BASE+0X128)        /* NAND FLASH的配置器存器2 */
#define EMI_NAND_ADDR2            (EMI_BASE+0X12C)        /* NAND FLASH的地址寄存器2 */
#define EMI_NAND_DATA             (EMI_BASE+0X200)        /* NAND FLASH的数据寄存器 */


/*
 *  DMAC模块
 *  基址: 0x11001000
 */

#define DMAC_INTSTATUS            (DMAC_BASE+0X020)       /* DAMC中断状态寄存器。 */
#define DMAC_INTTCSTATUS          (DMAC_BASE+0X050)       /* DMAC传输完成中断状态寄存器 */
#define DMAC_INTTCCLEAR           (DMAC_BASE+0X060)       /* DMAC传输完成中断状态清除寄存器 */
#define DMAC_INTERRORSTATUS       (DMAC_BASE+0X080)       /* DMAC传输错误中断状态寄存器 */
#define DMAC_INTINTERRCLR         (DMAC_BASE+0X090)       /* DMAC传输错误中断状态清除寄存器 */
#define DMAC_ENBLDCHNS            (DMAC_BASE+0X0B0)       /* DMAC通道使能状态寄存器 */
#define DMAC_C0SRCADDR            (DMAC_BASE+0X000)       /* DMAC道0源地址寄存器 */
#define DMAC_C0DESTADD            (DMAC_BASE+0X004)       /* DMAC道0目的地址寄存器 */
#define DMAC_C0CONTROL            (DMAC_BASE+0X00C)       /* DMAC道0控制寄存器 */
#define DMAC_C0CONFIGURATION      (DMAC_BASE+0X010)       /* DMAC道0配置寄存器 */
#define DMAC_C0DESCRIPTOR         (DMAC_BASE+0X01C)       /* DMAC道0链表地址寄存器 */
#define DMAC_C1SRCADDR            (DMAC_BASE+0X100)       /* DMAC道1源地址寄存器 */
#define DMAC_C1DESTADDR           (DMAC_BASE+0X104)       /* DMAC道1目的地址寄存器 */
#define DMAC_C1CONTROL            (DMAC_BASE+0X10C)       /* DMAC道1控制寄存器 */
#define DMAC_C1CONFIGURATION      (DMAC_BASE+0X110)       /* DMAC道1配置寄存器 */
#define DMAC_C1DESCRIPTOR         (DMAC_BASE+0X114)       /* DMAC道1链表地址寄存器 */
#define DMAC_C2SRCADDR            (DMAC_BASE+0X200)       /* DMAC道2源地址寄存器 */
#define DMAC_C2DESTADDR           (DMAC_BASE+0X204)       /* DMAC道2目的地址寄存器 */
#define DMAC_C2CONTROL            (DMAC_BASE+0X20C)       /* DMAC道2控制寄存器 */
#define DMAC_C2CONFIGURATION      (DMAC_BASE+0X210)       /* DMAC道2配置寄存器 */
#define DMAC_C2DESCRIPTOR         (DMAC_BASE+0X214)       /* DMAC道2链表地址寄存器 */
#define DMAC_C3SRCADDR            (DMAC_BASE+0X300)       /* DMAC道3源地址寄存器 */
#define DMAC_C3DESTADDR           (DMAC_BASE+0X304)       /* DMAC道3目的地址寄存器 */
#define DMAC_C3CONTROL            (DMAC_BASE+0X30C)       /* DMAC道3控制寄存器 */
#define DMAC_C3CONFIGURATION      (DMAC_BASE+0X310)       /* DMAC道3配置寄存器 */
#define DMAC_C3DESCRIPTOR         (DMAC_BASE+0X314)       /* DMAC道3链表地址寄存器 */
#define DMAC_C4SRCADDR            (DMAC_BASE+0X400)       /* DMAC道4源地址寄存器 */
#define DMAC_C4DESTADDR           (DMAC_BASE+0X404)       /* DMAC道4目的地址寄存器 */
#define DMAC_C4CONTROL            (DMAC_BASE+0X40C)       /* DMAC道4控制寄存器 */
#define DMAC_C4CONFIGURATION      (DMAC_BASE+0X410)       /* DMAC道4配置寄存器 */
#define DMAC_C4DESCRIPTOR         (DMAC_BASE+0X414)       /* DMAC道4链表地址寄存器 */
#define DMAC_C5SRCADDR            (DMAC_BASE+0X500)       /* DMAC道5源地址寄存器 */
#define DMAC_C5DESTADDR           (DMAC_BASE+0X504)       /* DMAC道5目的地址寄存器 */
#define DMAC_C5CONTROL            (DMAC_BASE+0X50C)       /* DMAC道5控制寄存器 */
#define DMAC_C5CONFIGURATION      (DMAC_BASE+0X510)       /* DMAC道5配置寄存器 */
#define DMAC_C5DESCRIPTOR         (DMAC_BASE+0X514)       /* DMAC道5链表地址寄存器 */


/*
 *  LCDC模块
 *  基址: 0x11002000
 */

#define LCDC_SSA                  (LCDC_BASE+0X000)       /* 屏幕起始地址寄存器 */
#define LCDC_SIZE                 (LCDC_BASE+0X004)       /* 屏幕尺寸寄存器 */
#define LCDC_PCR                  (LCDC_BASE+0X008)       /* 面板配置寄存器 */
#define LCDC_HCR                  (LCDC_BASE+0X00C)       /* 水平配置寄存器 */
#define LCDC_VCR                  (LCDC_BASE+0X010)       /* 垂直配置寄存器 */
#define LCDC_PWMR                 (LCDC_BASE+0X014)       /* PWM对比度控制寄存器 */
#define LCDC_LECR                 (LCDC_BASE+0X018)       /* 使能控制寄存器 */
#define LCDC_DMACR                (LCDC_BASE+0X01C)       /* DMA控制寄存器 */
#define LCDC_LCDISREN             (LCDC_BASE+0X020)       /* 中断使能寄存器 */
#define LCDC_LCDISR               (LCDC_BASE+0X024)       /* 中断状态寄存器 */
#define LCDC_LGPMR                (LCDC_BASE+0X040)       /* 灰度调色映射寄存器组 (16个32bit寄存器) */


/*
 *  MAC模块
 *  基址: 0x11003000
 */

#define MAC_CTRL                  (MAC_BASE+0X000)        /* MAC控制寄存器 */
#define MAC_INTSRC                (MAC_BASE+0X004)        /* MAC中断源寄存器 */
#define MAC_INTMASK               (MAC_BASE+0X008)        /* MAC中断屏蔽寄存器 */
#define MAC_IPGT                  (MAC_BASE+0X00C)        /* 连续帧间隔寄存器 */
#define MAC_IPGR1                 (MAC_BASE+0X010)        /* 等待窗口寄存器 */
#define MAC_IPGR2                 (MAC_BASE+0X014)        /* 等待窗口寄存器 */
#define MAC_PACKETLEN             (MAC_BASE+0X018)        /* 帧长度寄存器 */
#define MAC_COLLCONF              (MAC_BASE+0X01C)        /* 碰撞重发寄存器 */
#define MAC_TXBD_NUM              (MAC_BASE+0X020)        /* 发送描述符寄存器 */
#define MAC_FLOWCTRL              (MAC_BASE+0X024)        /* 流控寄存器 */
#define MAC_MII_CTRL              (MAC_BASE+0X028)        /* PHY控制寄存器 */
#define MAC_MII_CMD               (MAC_BASE+0X02C)        /* PHY命令寄存器 */
#define MAC_MII_ADDRESS           (MAC_BASE+0X030)        /* PHY地址寄存器 */
#define MAC_MII_TXDATA            (MAC_BASE+0X034)        /* PHY写数据寄存器 */
#define MAC_MII_RXDATA            (MAC_BASE+0X038)        /* PHY读数据寄存器 */
#define MAC_MII_STATUS            (MAC_BASE+0X03C)        /* PHY状态寄存器 */
#define MAC_ADDR0                 (MAC_BASE+0X040)        /* MAC地址寄存器 */
#define MAC_ADDR1                 (MAC_BASE+0X044)        /* MAC地址寄存器 */
#define MAC_HASH0                 (MAC_BASE+0X048)        /* MAC HASH寄存器 */
#define MAC_HASH1                 (MAC_BASE+0X04C)        /* MAC HASH寄存器 */
#define MAC_TXPAUSE               (MAC_BASE+0X050)        /* MAC控制帧寄存器 */
#define MAC_TX_BD                 (MAC_BASE+0X400)
#define MAC_RX_BD                 (MAC_BASE+0X600)


/*
 **************************************
 * Error Codes:
 *    IF SUCCESS RETURN 0, ELSE RETURN OTHER ERROR CODE,
 *    parameter error return (-33)/E_PAR,
 *    hardware error reture (-99)/E_HA
 **************************************
 */

#define    E_OK          0        /* Normal completion */
#define    E_SYS         (-5)     /* System error */
#define    E_NOMEM       (-10)    /* Insufficient memory */
#define    E_NOSPT       (-17)    /* Feature not supported */
#define    E_INOSPT      (-18)    /* Feature not supported by ITRON/FILE specification */
#define    E_RSFN        (-20)    /* Reserved function code number */
#define    E_RSATR       (-24)    /* Reserved attribute */
#define    E_PAR         (-33)    /* Parameter error */
#define    E_ID          (-35)    /* Invalid ID number */
#define    E_NOEXS       (-52)    /* Object does not exist */
#define    E_OBJ         (-63)    /* Invalid object state */
#define    E_MACV        (-65)    /* Memory access disabled or memory access violation */
#define    E_OACV        (-66)    /* Object access violation */
#define    E_CTX         (-69)    /* Context error */
#define    E_QOVR        (-73)    /* Queuing or nesting overflow */
#define    E_DLT         (-81)    /* Object being waited for was deleted */
#define    E_TMOUT       (-85)    /* Polling failure or timeout exceeded */
#define    E_RLWAI       (-86)    /* WAIT state was forcibly released */

#define    E_HA          (-99)    /* HARD WARE ERROR */


/*
 **************************************
 * PMU 模块时钟
 **************************************
 */

#define    CLK_SGPT      (1 << 16)
#define    CLK_SI2S      (1 << 15)
#define    CLK_SSMC      (1 << 14)
#define    CLK_SMAC      (1 << 13)
#define    CLK_SUSB      (1 << 12)
#define    CLK_SUART3    (1 << 11)
#define    CLK_SUART2    (1 << 10)
#define    CLK_SUART1    (1 << 9)
#define    CLK_SUART0    (1 << 8)
#define    CLK_SSSI      (1 << 7)
#define    CLK_SAC97     (1 << 6)
#define    CLK_SMMCSD    (1 << 5)
#define    CLK_SEMI      (1 << 4)
#define    CLK_SDMAC     (1 << 3)
#define    CLK_SPWM      (1 << 2)
#define    CLK_SLCDC     (1 << 1)
#define    CLK_SESRAM    (1)


/*Interrupt Sources*/


#define  INTSRC_RTC        31
#define  INTSRC_DMAC       30
#define  INTSRC_EMI        29
#define  INTSRC_MAC        28
#define  INTSRC_TIMER1     27
#define  INTSRC_TIMER2     26
#define  INTSRC_TIMER3     25
#define  INTSRC_UART0      24
#define  INTSRC_UART1      23
#define  INTSRC_UART2      22
#define  INTSRC_UART3      21
#define  INTSRC_PWM        20
#define  INTSRC_LCDC       19
#define  INTSRC_I2S        18
#define  INTSRC_SSI        17

#define  INTSRC_USB        15
#define  INTSRC_SMC0       14
#define  INTSRC_SMC1       13
#define  INTSRC_SDIO       12
#define  INTSRC_EXINT10    11
#define  INTSRC_EXINT9     10
#define  INTSRC_EXINT8     9
#define  INTSRC_EXINT7     8
#define  INTSRC_EXINT6     7
#define  INTSRC_EXINT5     6
#define  INTSRC_EXINT4     5
#define  INTSRC_EXINT3     4
#define  INTSRC_EXINT2     3
#define  INTSRC_EXINT1     2
#define  INTSRC_EXINT0     1
#define  INTSRC_NULL       0


/*Sereral useful macros*/
#define set_plevel(plevel)          *(RP)INTC_IPLR = plevel                      //设置普通中断的优先级门限，只有优先级大于此值的中断才能通过
#define set_int_force(intnum)       *(RP)INTC_IFR = (1 << intnum)                //置1后，软件强制该位对应的中断源发出中断信号
#define enable_irq(intnum)          *(RP)INTC_IER |= (1 << intnum)               //置1后，允许中断源的IRQ 中断信号
#define disable_irq( intnum)        *(RP)INTC_IER &= ~(1<< intnum)               //置0后，不允许中断源的IRQ 中断信号
#define mask_irq(intnum)            *(RP)INTC_IMR |= (1 << intnum)               //置1后，屏蔽对应的IRQ 中断信号
#define unmask_irq(intnum)          *(RP)INTC_IMR &= ~(1 << intnum)              //置0后，通过对应的IRQ 中断信号
#define mask_all_irq()              *(RP)INTC_IMR = 0xFFFFFFFF                   //屏蔽对应的IRQ 中断信号
#define unmask_all_irq()            *(RP)INTC_IMR = 0x00000000                   //通过对应的IRQ 中断信号
#define enable_all_irq()            *(RP)INTC_IER = 0XFFFFFFFF                   //允许中断源的IRQ 中断信号
#define disable_all_irq()           *(RP)INTC_IER = 0X00000000                   //不允许中断源的IRQ 中断信号
#define InitInt()                  do{mask_all_irq(); enable_all_irq();}while(0)

/*
 **************************************
 * 所有程序中用到的Typedef
 **************************************
 */

typedef    char                 S8;        /* signed 8-bit integer */
typedef    short                S16;       /* signed 16-bit integer */
typedef    long                 S32;       /* signed 32-bit integer */
typedef    unsigned char        U8;        /* unsigned 8-bit integer */
typedef    unsigned short       U16;       /* unsigned 16-bit integer */
typedef    unsigned long        U32;       /* unsigned 32-bit integer */

typedef    volatile U32 *       RP;
typedef    volatile U16 *       RP16;
typedef    volatile U8  *       RP8;

typedef    void                 *VP;       /* pointer to an unpredictable data type */
typedef    void                 (*FP)();   /* program start address */

#ifndef    _BOOL_TYPE_
#define    _BOOL_TYPE_
typedef    int                  BOOL;        /* Boolean value.  TRUE (1) or FALSE (0). */
#endif

typedef    int                  ER;         /* Error code.  A signed integer. */

/**
 * IO definitions
 *
 * define access restrictions to peripheral registers
 */

#define     __I     volatile const            /*!< defines 'read only' permissions      */
#define     __O     volatile                  /*!< defines 'write only' permissions     */
#define     __IO    volatile                  /*!< defines 'read / write' permissions   */
#define     __iomem volatile


/*Macros for debug*/

#define EOUT(fmt,...) \
    do \
    {   \
        rt_kprintf("EOUT:(%s:%i)  ",__FILE__,__LINE__); \
        rt_kprintf(fmt,##__VA_ARGS__); \
    }while(0)

#define RT_USING_DEBUG
#ifdef RT_USING_DEBUG
    #define DBOUT(fmt,...) \
    do \
    {   \
        rt_kprintf("DBOUT:(%s:%i)  ",__FILE__,__LINE__); \
        rt_kprintf(fmt,##__VA_ARGS__); \
    }while(0)
#else
    #define DBOUT(fmt,...) \
    do{}while(0)
#endif

#ifdef  RT_USING_DEBUG
    #define ASSERT(arg) \
    if((arg) == 0) \
    {       \
        while(1) \
        {         \
            rt_kprintf("have a assert failure\n"); \
        }                                        \
    }
#else
    #define ASSERT(arg) \
    do      \
    {        \
    }while(0)
#endif


#define write_reg(reg,value) \
    do \
    { \
        *(RP)(reg) = value; \
    }while(0)

#define read_reg(reg) (*(RP)reg)


struct rt_hw_register
{
    rt_uint32_t r0;
    rt_uint32_t r1;
    rt_uint32_t r2;
    rt_uint32_t r3;
    rt_uint32_t r4;
    rt_uint32_t r5;
    rt_uint32_t r6;
    rt_uint32_t r7;
    rt_uint32_t r8;
    rt_uint32_t r9;
    rt_uint32_t r10;
    rt_uint32_t fp;
    rt_uint32_t ip;
    rt_uint32_t sp;
    rt_uint32_t lr;
    rt_uint32_t pc;
    rt_uint32_t cpsr;
    rt_uint32_t ORIG_r0;
};


/*@}*/

#endif
