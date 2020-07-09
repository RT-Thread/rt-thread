/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-10-23     勤为本       first version
 */

// 硬件spi接口的头文件

#ifndef __OPENLOONGSON_SPI_H
#define __OPENLOONGSON_SPI_H


// SPI模块编号
#define LS1C_SPI_0                      (0)
#define LS1C_SPI_1                      (1)

// 片选
#define LS1C_SPI_CS_0                   (0)
#define LS1C_SPI_CS_1                   (1)
#define LS1C_SPI_CS_2                   (2)
#define LS1C_SPI_CS_3                   (3)

// 时钟极性和相位
#define SPI_CPOL_1                      (1)
#define SPI_CPOL_0                      (0)
#define SPI_CPHA_1                      (1)
#define SPI_CPHA_0                      (0)


// 寄存器偏移
#define LS1C_SPI_SPCR_OFFSET                (0)     // 控制寄存器
#define LS1C_SPI_SPSR_OFFSET                (1)     // 状态寄存器
#define LS1C_SPI_TxFIFO_OFFSET              (2)     // 发送的数据寄存器，与接收数据寄存器的偏移相同
#define LS1C_SPI_RxFIFO_OFFSET              (2)     // 接收的数据寄存器，与发送数据寄存器的偏移相同
#define LS1C_SPI_SPER_OFFSET                (3)     // 外部寄存器
#define LS1C_SPI_SFC_PARAM_OFFSET           (4)     // 参数控制寄存器
#define LS1C_SPI_SFC_SOFTCS_OFFSET          (5)     // 片选控制寄存器
#define LS1C_SPI_SFC_TIMING_OFFSET          (6)     // 时序控制寄存器

// 寄存器SPCR中的位域
#define LS1C_SPI_SPCR_SPIE_BIT              (7)
#define LS1C_SPI_SPCR_SPIE_MASK             (0x01 << LS1C_SPI_SPCR_SPIE_BIT)
#define LS1C_SPI_SPCR_SPE_BIT               (6)
#define LS1C_SPI_SPCR_SPE_MASK              (0x01 << LS1C_SPI_SPCR_SPE_BIT)
#define LS1C_SPI_SPCR_CPOL_BIT              (3)
#define LS1C_SPI_SPCR_CPOL_MASK             (0x01 << LS1C_SPI_SPCR_CPOL_BIT)
#define LS1C_SPI_SPCR_CPHA_BIT              (2)
#define LS1C_SPI_SPCR_CPHA_MASK             (0x01 << LS1C_SPI_SPCR_CPHA_BIT)
#define LS1C_SPI_SPCR_SPR_BIT               (0)
#define LS1C_SPI_SPCR_SPR_MASK              (0x03 << LS1C_SPI_SPCR_SPR_BIT)

// 寄存器SPSR中的位域
#define LS1C_SPI_SPSR_SPIF_BIT              (7)
#define LS1C_SPI_SPSR_SPIF_MASK             (0x01 << LS1C_SPI_SPSR_SPIF_BIT)
#define LS1C_SPI_SPSR_WCOL_BIT              (6)
#define LS1C_SPI_SPSR_WCOL_MASK             (0x01 << LS1C_SPI_SPSR_WCOL_BIT)

// 寄存器SPER中的位域
#define LS1C_SPI_SPER_SPRE_BIT              (0)
#define LS1C_SPI_SPER_SPRE_MASK             (0x3 << LS1C_SPI_SPER_SPRE_BIT)

// 寄存器SFC_SOFTCS的位域
#define LS1C_SPI_SFC_SOFTCS_CSN_BIT         (4)
#define LS1C_SPI_SFC_SOFTCS_CSN_MASK        (0x0f << LS1C_SPI_SFC_SOFTCS_CSN_BIT)
#define LS1C_SPI_SFC_SOFTCS_CSEN_BIT        (0)
#define LS1C_SPI_SFC_SOFTCS_CSEN_MASK       (0x0f << LS1C_SPI_SFC_SOFTCS_CSEN_BIT)

// 发送超时的门限值
#define LS1C_SPI_TX_TIMEOUT                 (20000)



/*
 * 获取指定SPI模块的基地址
 * @SPIx SPI模块的编号
 */
void *ls1c_spi_get_base(unsigned char SPIx);


/*
 * 设置时钟
 * @spi_base 基地址
 * @max_hz 最大频率，单位hz
 */
void ls1c_spi_set_clock(void *spi_base, unsigned long max_hz);


/*
 * 设置通信模式(时钟极性和相位)
 * @spi_base 基地址
 * @cpol 时钟极性
 * @cpha 时钟相位
 */
void ls1c_spi_set_mode(void *spi_base, unsigned char cpol, unsigned char cpha);


/*
 * 设置指定片选为指定状态
 * @spi_base 基地址
 * @cs 片选
 * @new_status 片选引脚的新状态，取值为0或1，即高电平或低电平
 */
void ls1c_spi_set_cs(void *spi_base, unsigned char cs, int new_status);


/*
 * 通过指定SPI发送接收一个字节
 * 注意，在多任务的系统中，此函数需要互斥。
 * 即保证在和某个从设备收发某个字节的过程中，不能被切换到其它任务同时与另外的在同一个SPI总线上的从设备通信
 * 因为龙芯1c的每路SPI上可能接有不同的从设备，通信频率、模式等可能不同
 * @spi_base 基地址
 * @tx_ch 待发送的数据
 * @ret 收到的数据
 */
unsigned char ls1c_spi_txrx_byte(void *spi_base, unsigned char tx_ch);


/*
 * 打印指定SPI模块的所有寄存器的值
 * @spi_base 基地址
 */
void ls1c_spi_print_all_regs_info(void *spi_base);




#endif

