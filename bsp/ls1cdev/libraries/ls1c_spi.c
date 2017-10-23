/*
 * File      : ls1c_spi.c
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

// 硬件spi接口源文件


#include <string.h>
#include "ls1c_public.h"
#include "ls1c_regs.h"
#include "ls1c_clock.h"
#include "ls1c_spi.h"


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
inline void *spi_get_base(ls1c_spi_t SPIx)
{
    void *base = NULL;

    switch (SPIx)
    {
        case LS1C_SPI_0:
            base = (void *)LS1C_SPI0_BASE;
            break;

        case LS1C_SPI_1:
            base = (void *)LS1C_SPI1_BASE;
            break;

        default:
            base = NULL;
            break;
    }

    return base;
}


/*
 * 打印指定SPI模块的所有寄存器的值
 * @spi_info_p SPI模块信息
 */
void spi_print_all_regs_info(ls1c_spi_info_t *spi_info_p)
{
    void *spi_base = spi_get_base(spi_info_p->SPIx);

    rt_kprintf("[%s] SPI%d's info:\r\n\
              SPCR=0x%x, SPSR=0x%x, SPER=0x%x, SFC_PARAM=0x%x, SFC_SOFTCS=0x%x, SFC_TIMING=0x%x\r\n",
              __FUNCTION__, spi_info_p->SPIx,
              reg_read_8(spi_base + LS1C_SPI_SPCR_OFFSET),
              reg_read_8(spi_base + LS1C_SPI_SPSR_OFFSET),
              reg_read_8(spi_base + LS1C_SPI_SPER_OFFSET),
              reg_read_8(spi_base + LS1C_SPI_SFC_PARAM_OFFSET),
              reg_read_8(spi_base + LS1C_SPI_SFC_SOFTCS_OFFSET),
              reg_read_8(spi_base + LS1C_SPI_SFC_TIMING_OFFSET));

    return ;
}


/*
 * 根据SPI时钟频率计算分频系数
 * @max_speed_hz SPI最大通信速度
 * @ret 分频系数
 */
unsigned int spi_get_div(unsigned int max_speed_hz)
{
    unsigned long clk = 0;
    unsigned int div = 0;
    unsigned int div_tmp = 0;
    unsigned int bit = 0;

    clk = clk_get_apb_rate();
    div = DIV_ROUND_UP(clk, max_speed_hz);

    if (div < 2)
        div = 2;

    if (div > 4096)
        div = 4096;

    bit = ls1c_fls(div) - 1;
    switch (1 << bit)
    {
        case 16:
            div_tmp = 2;
            if (div > (1 << bit))
            {
                div_tmp++;
            }
            break;

        case 32:
            div_tmp = 3;
            if (div > (1 << bit))
            {
                div_tmp += 2;
            }
            break;

        case 8:
            div_tmp = 4;
            if (div > (1 << bit))
            {
                div_tmp -= 2;
            }
            break;

        default:
            div_tmp = bit - 1;
            if (div > (1 << bit))
            {
                div_tmp++;
            }
            break;
    }
/*    
    rt_kprintf("[%s] clk=%ld, max_speed_hz=%d, div_tmp=%d, bit=%d\r\n", 
              __FUNCTION__, clk, max_speed_hz, div_tmp, bit);
*/
    return div_tmp;
}


/*
 * 设置时钟
 * @spi_info_p SPI模块信息
 */
void spi_set_clock(ls1c_spi_info_t *spi_info_p)
{
    void *spi_base = spi_get_base(spi_info_p->SPIx);
    unsigned int div = 0;
    unsigned char val = 0;

    // 获取分频系数
    div = spi_get_div(spi_info_p->max_speed_hz);

    // 设置spr
    val = reg_read_8(spi_base + LS1C_SPI_SPCR_OFFSET);
    val &= (~LS1C_SPI_SPCR_SPR_MASK);                       // spr清零
    val |= (div & LS1C_SPI_SPCR_SPR_MASK);                  // 设置新的spr
    reg_write_8(val, spi_base + LS1C_SPI_SPCR_OFFSET);

    // 设置spre
    val = reg_read_8(spi_base + LS1C_SPI_SPER_OFFSET);
    val &= (~LS1C_SPI_SPER_SPRE_MASK);                      // spre清零
    val |= ((div >> 2) & LS1C_SPI_SPER_SPRE_MASK);        // 设置新的spre
    reg_write_8(val, spi_base + LS1C_SPI_SPER_OFFSET);

    return ;
}


/*
 * 设置通信模式(时钟极性和相位)
 * @spi_info_p SPI模块信息
 */
void spi_set_mode(ls1c_spi_info_t *spi_info_p)
{
    void *spi_base = spi_get_base(spi_info_p->SPIx);
    unsigned char val = 0;

    val = reg_read_8(spi_base + LS1C_SPI_SPCR_OFFSET);
    
    // 设置时钟极性--cpol
    val &= (~LS1C_SPI_SPCR_CPOL_MASK);                      // cpol清0
    val |= (spi_info_p->cpol << LS1C_SPI_SPCR_CPOL_BIT);    // 写入新的cpol
    
    // 设置时钟相位--cpha
    val &= (~LS1C_SPI_SPCR_CPHA_MASK);                      // cpha清0
    val |= (spi_info_p->cpha << LS1C_SPI_SPCR_CPHA_BIT);    // 写入新的cpha
    
    reg_write_8(val, spi_base + LS1C_SPI_SPCR_OFFSET);

    return ;
}


/*
 * 设置指定片选为指定状态
 * @spi_info_p SPI模块信息
 * @new_status 片选引脚的新状态，取值为0或1，即高电平或低电平
 */
void spi_set_cs(ls1c_spi_info_t *spi_info_p, int new_status)
{
    void *spi_base = spi_get_base(spi_info_p->SPIx);
    unsigned char cs = spi_info_p->cs;
    unsigned char val = 0;

    val = 0xf0 | (0x01 << cs);          // 全部csn=1，指定的csen=1
    if (new_status)         // cs = 1
    {
        val |= (0x10 << cs);            // 指定csn=1
    }
    else                    // cs = 0
    {
        val &= ~(0x10 << cs);           // 指定csn=0
    }
    reg_write_8(val, spi_base + LS1C_SPI_SFC_SOFTCS_OFFSET);

    return ;
}


/*
 * 初始化指定SPI模块
 * @spi_info_p SPI模块信息
 */
void spi_init(ls1c_spi_info_t *spi_info_p)
{
    void *spi_base = spi_get_base(spi_info_p->SPIx);
    unsigned char val = 0;

    // 使能SPI控制器，master模式，关闭中断
    reg_write_8(0x53, spi_base + LS1C_SPI_SPCR_OFFSET);

    // 清空状态寄存器
    reg_write_8(0xc0, spi_base + LS1C_SPI_SPSR_OFFSET);

    // 1字节产生中断，采样(读)与发送(写)时机同时
    reg_write_8(0x03, spi_base + LS1C_SPI_SPER_OFFSET);

    // 关闭SPI flash
    val = reg_read_8(spi_base + LS1C_SPI_SFC_PARAM_OFFSET);
    val &= 0xfe;
    reg_write_8(val, spi_base + LS1C_SPI_SFC_PARAM_OFFSET);

    // spi flash时序控制寄存器
    reg_write_8(0x05, spi_base + LS1C_SPI_SFC_TIMING_OFFSET);

    // 设置时钟
    spi_set_clock(spi_info_p);

    // 设置通信模式(时钟极性和相位)
    spi_set_mode(spi_info_p);

    // 打印寄存器信息(用于调试)
//    spi_print_all_regs_info(spi_info_p);

    return ;
}


/*
 * 等待收发完成
 */
inline void spi_wait_txrx_done(ls1c_spi_info_t *spi_info_p)
{
    void *spi_base = spi_get_base(spi_info_p->SPIx);
    int timeout = LS1C_SPI_TX_TIMEOUT;

    while (timeout--)
    {
        if (LS1C_SPI_SPSR_SPIF_MASK & reg_read_8(spi_base + LS1C_SPI_SPSR_OFFSET))
            break;
    }
    
    return ;
}


/*
 * 清中断和标志位
 */
inline void spi_clear(ls1c_spi_info_t *spi_info_p)
{
    void *spi_base = spi_get_base(spi_info_p->SPIx);
    unsigned char val = 0;

    // 清中断
    val = reg_read_8(spi_base + LS1C_SPI_SPSR_OFFSET);
    val |= LS1C_SPI_SPSR_SPIF_MASK;
    reg_write_8(val, spi_base + LS1C_SPI_SPSR_OFFSET);

    // 清溢出标志位(Write-Collision Clear)
    val = reg_read_8(spi_base + LS1C_SPI_SPSR_OFFSET);
    if (LS1C_SPI_SPSR_WCOL_MASK & val)
    {
        rt_kprintf("[%s] clear register SPSR's wcol!\r\n");       // 手册和linux源码中不一样，加个打印看看
        reg_write_8(val & ~LS1C_SPI_SPSR_WCOL_MASK, spi_base + LS1C_SPI_SPSR_OFFSET);   // 写0，linux源码中是写0
//        reg_write_8(val | LS1C_SPI_SPSR_WCOL_MASK, spi_base + LS1C_SPI_SPSR_OFFSET);  // 写1，按照1c手册，应该写1
    }

    return ;
}



/*
 * 通过指定SPI发送接收一个字节
 * 注意，在多任务的系统中，此函数需要互斥。
 * 即保证在和某个从设备收发某个字节的过程中，不能被切换到其它任务同时与另外的在同一个SPI总线上的从设备通信
 * 因为龙芯1c的每路SPI上可能接有不同的从设备，通信频率、模式等可能不同
 * @spi_info_p SPI接口
 * @tx_ch 待发送的数据
 * @ret 收到的数据
 */
unsigned char spi_txrx_byte(ls1c_spi_info_t *spi_info_p, unsigned char tx_ch)
{
    void *spi_base = spi_get_base(spi_info_p->SPIx);
    unsigned char rx_ch = 0;

    // 收发数据
    reg_write_8(tx_ch, spi_base + LS1C_SPI_TxFIFO_OFFSET);      // 开始发送
    spi_wait_txrx_done(spi_info_p);                             // 等待收发完成
    rx_ch = reg_read_8(spi_base + LS1C_SPI_RxFIFO_OFFSET);      // 读取收到的数据
    spi_clear(spi_info_p);                                      // 清中断和标志位

    return rx_ch;
}



