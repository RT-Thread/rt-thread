/*
 * File      : ls1c_spi.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-10-23     勤为本       first version
 */

// 硬件spi接口的头文件

#ifndef __OPENLOONGSON_SPI_H
#define __OPENLOONGSON_SPI_H


// SPI模块编号
typedef enum
{
    LS1C_SPI_0 = 0,
    LS1C_SPI_1,
}ls1c_spi_t;


// 片选
#define LS1C_SPI_INVALID_CS             (-1)
#define LS1C_SPI_CS_0                   (0)
#define LS1C_SPI_CS_1                   (1)
#define LS1C_SPI_CS_2                   (2)
#define LS1C_SPI_CS_3                   (3)

// 时钟极性和相位
#define SPI_CPOL_1                      (1)
#define SPI_CPOL_0                      (0)
#define SPI_CPHA_1                      (1)
#define SPI_CPHA_0                      (0)


// 硬件SPI信息
typedef struct
{
    ls1c_spi_t SPIx;                    // SPI模块编号
    unsigned long max_speed_hz;         // 最大通信速度，单位hz
    unsigned char cs;                   // 片选
    unsigned char cpol;                 // 时钟极性
    unsigned char cpha;                 // 时钟相位
}ls1c_spi_info_t;



/*
 * 初始化指定SPI模块
 * @spi_info_p SPI模块信息
 */
void spi_init(ls1c_spi_info_t *spi_info_p);


/*
 * 设置指定片选为指定状态
 * @spi_info_p SPI模块信息
 * @new_status 片选引脚的新状态，取值为0或1，即高电平或低电平
 */
void spi_set_cs(ls1c_spi_info_t *spi_info_p, int new_status);


/*
 * 通过指定SPI发送接收一个字节
 * 注意，在多任务的系统中，此函数需要互斥。
 * 即保证在和某个从设备收发某个字节的过程中，不能被切换到其它任务同时与另外的在同一个SPI总线上的从设备通信
 * 因为龙芯1c的每路SPI上可能接有不同的从设备，通信频率、模式等可能不同
 * @spi_info_p SPI接口
 * @tx_ch 待发送的数据
 * @ret 收到的数据
 */
unsigned char spi_txrx_byte(ls1c_spi_info_t *spi_info_p, unsigned char tx_ch);


/*
 * 打印指定SPI模块的所有寄存器的值
 * @spi_info_p SPI模块信息
 */
void spi_print_all_regs_info(ls1c_spi_info_t *spi_info_p);


#endif

