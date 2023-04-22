/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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




/*
 * 获取指定SPI模块的基地址
 * @SPIx SPI模块的编号
 */
void *ls1c_spi_get_base(unsigned char SPIx)
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
 * @spi_base 基地址
 */
void ls1c_spi_print_all_regs_info(void *spi_base)
{
    printf("[%s] SPCR=0x%x, SPSR=0x%x, SPER=0x%x, SFC_PARAM=0x%x, SFC_SOFTCS=0x%x, SFC_TIMING=0x%x\r\n",
              __FUNCTION__,
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
unsigned int ls1c_spi_get_div(unsigned int max_speed_hz)
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
    printf("[%s] clk=%ld, max_speed_hz=%d, div_tmp=%d, bit=%d\r\n", 
              __FUNCTION__, clk, max_speed_hz, div_tmp, bit);
*/
    return div_tmp;
}


/*
 * 设置时钟
 * @spi_base 基地址
 * @max_hz 最大频率，单位hz
 */
void ls1c_spi_set_clock(void *spi_base, unsigned long max_hz)
{
    unsigned int div = 0;
    unsigned char val = 0;

    // 获取分频系数
    div = ls1c_spi_get_div(max_hz);

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
 * @spi_base 基地址
 * @cpol 时钟极性
 * @cpha 时钟相位
 */
void ls1c_spi_set_mode(void *spi_base, unsigned char cpol, unsigned char cpha)
{
    unsigned char val = 0;

    val = reg_read_8(spi_base + LS1C_SPI_SPCR_OFFSET);
    
    // 设置时钟极性--cpol
    val &= (~LS1C_SPI_SPCR_CPOL_MASK);                  // cpol清0
    val |= (cpol << LS1C_SPI_SPCR_CPOL_BIT);            // 写入新的cpol
    
    // 设置时钟相位--cpha
    val &= (~LS1C_SPI_SPCR_CPHA_MASK);                  // cpha清0
    val |= (cpha << LS1C_SPI_SPCR_CPHA_BIT);            // 写入新的cpha
    
    reg_write_8(val, spi_base + LS1C_SPI_SPCR_OFFSET);

    return ;
}


/*
 * 设置指定片选为指定状态
 * @spi_base 基地址
 * @cs 片选
 * @new_status 片选引脚的新状态，取值为0或1，即高电平或低电平
 */
void ls1c_spi_set_cs(void *spi_base, unsigned char cs, int new_status)
{
    unsigned char val = 0;

    val = reg_read_8(spi_base + LS1C_SPI_SFC_SOFTCS_OFFSET);
    val |= 0x01 << cs ; //对应的csen=1  
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
 * 等待收发完成
 * @spi_base 基地址
 */
void ls1c_spi_wait_txrx_done(void *spi_base)
{
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
 * @spi_base 基地址
 */
void ls1c_spi_clear(void *spi_base)
{
    unsigned char val = 0;

    // 清中断
    val = reg_read_8(spi_base + LS1C_SPI_SPSR_OFFSET);
    val |= LS1C_SPI_SPSR_SPIF_MASK;
    reg_write_8(val, spi_base + LS1C_SPI_SPSR_OFFSET);

    // 清溢出标志位(Write-Collision Clear)
    val = reg_read_8(spi_base + LS1C_SPI_SPSR_OFFSET);
    if (LS1C_SPI_SPSR_WCOL_MASK & val)
    {
        printf("[%s] clear register SPSR's wcol!\r\n", __FUNCTION__);       // 手册和linux源码中不一样，加个打印看看
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
 * @spi_base 基地址
 * @tx_ch 待发送的数据
 * @ret 收到的数据
 */
unsigned char ls1c_spi_txrx_byte(void *spi_base, unsigned char tx_ch)
{
    unsigned char rx_ch = 0;

    // 收发数据
    reg_write_8(tx_ch, spi_base + LS1C_SPI_TxFIFO_OFFSET);      // 开始发送
    ls1c_spi_wait_txrx_done(spi_base);                          // 等待收发完成
    rx_ch = reg_read_8(spi_base + LS1C_SPI_RxFIFO_OFFSET);      // 读取收到的数据
    ls1c_spi_clear(spi_base);                                   // 清中断和标志位

    return rx_ch;
}



