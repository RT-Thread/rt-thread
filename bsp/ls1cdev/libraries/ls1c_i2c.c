/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-06     勤为本       first version
 */

// 封装硬件i2c接口


#include "ls1c_public.h"
#include "ls1c_regs.h"
#include "ls1c_clock.h"
#include "ls1c_i2c.h"
#include "ls1c_delay.h"



/*
 * I2C各个寄存器相对基地址的偏移
 * 发送数据寄存器和接收数据寄存器的偏移是相同的
 * 命令寄存器和状态寄存器的偏移是相同的，不同的是命令寄存器只写，状态寄存器只读
 */
#define LS1C_I2C_PRER_LOW_OFFSET            (0)     // 分频锁存器低字节寄存器偏移
#define LS1C_I2C_PRER_HIGH_OFFSET           (1)     // 分频锁存器高字节寄存器偏移
#define LS1C_I2C_CONTROL_OFFSET             (2)     // 控制寄存器偏移
#define LS1C_I2C_DATA_OFFSET                (3)     // 发送数据寄存器和接收数据寄存器的偏移是相同的
#define LS1C_I2C_CMD_OFFSET                 (4)     // 命令寄存器偏移，只写
#define LS1C_I2C_STATUS_OFFSET              (4)     // 状态寄存器偏移，只读


// 控制寄存器的位域
#define LS1C_I2C_CONTROL_EN                 (0x80)  // i2c模块使能
#define LS1C_I2C_CONTROL_IEN                (0x40)  // 中断使能

// 命令寄存器的位域
#define LS1C_I2C_CMD_START                  (0x90)  // 产生START信号
#define LS1C_I2C_CMD_STOP                   (0x40)  // 产生STOP信号
#define LS1C_I2C_CMD_READ                   (0x20)  // 产生读信号，即产生ACK信号
#define LS1C_I2C_CMD_WRITE                  (0x10)  // 产生写信号
#define LS1C_I2C_CMD_READ_ACK               (0x20)  // 产生ACK信号，与读信号相同
#define LS1C_I2C_CMD_READ_NACK              (0x28)  // 产生NACK信号
#define LS1C_I2C_CMD_IACK                   (0x00)  // 产生中断应答信号

// 状态寄存器的位域
#define LS1C_I2C_STATUS_IF                  (0x01)  // 中断标志位
#define LS1C_I2C_STATUS_TIP                 (0x02)  // 指示传输的过程。1，正在传输；0，传输完成
#define LS1C_I2C_STATUS_ARBLOST             (0x20)  // I2C核失去I2C总线的控制权
#define LS1C_I2C_STATUS_BUSY                (0x40)  // I2C总线忙标志
#define LS1C_I2C_STATUS_NACK                (0x80)  // 应答位标志。1，没收到应答位；0，收到应答位


/*
 * 获取指定i2c模块的基地址
 * @I2Cx I2C模块的编号
 */
void *i2c_get_base(ls1c_i2c_t I2Cx)
{
    void *base = NULL;
    
    switch (I2Cx)
    {
        case LS1C_I2C_0:
            base = (void *)LS1C_I2C0_BASE;
            break;

        case LS1C_I2C_1:
            base = (void *)LS1C_I2C1_BASE;
            break;

        case LS1C_I2C_2:
            base = (void *)LS1C_I2C2_BASE;
            break;

        default:
            base = NULL;
            break;
    }

    return base;
}


/*
 * 向命令寄存器写命令
 * @i2c_info_p i2c模块信息
 * @cmd 命令
 */
void i2c_cmd(ls1c_i2c_info_t *i2c_info_p, unsigned char cmd)
{
    void *i2c_base = i2c_get_base(i2c_info_p->I2Cx);

    reg_write_8(cmd, i2c_base + LS1C_I2C_CMD_OFFSET);

    return ;
}


/*
 * 执行START命令，发送START信号
 * @i2c_info_p i2c模块信息
 */
void i2c_cmd_start(ls1c_i2c_info_t *i2c_info_p)
{
    i2c_cmd(i2c_info_p, LS1C_I2C_CMD_START);
    return ;
}


/*
 * 执行STOP命令，发送STOP信号
 * @i2c_info_p i2c模块信息
 */
void i2c_cmd_stop(ls1c_i2c_info_t *i2c_info_p)
{
    i2c_cmd(i2c_info_p, LS1C_I2C_CMD_STOP);
    return ;
}


/*
 * 执行写命令
 * @i2c_info_p i2c模块信息
 */
void i2c_cmd_write(ls1c_i2c_info_t *i2c_info_p)
{
    i2c_cmd(i2c_info_p, LS1C_I2C_CMD_WRITE);
    return ;
}


/*
 * 执行读ack命令，发送读ack信号
 * @i2c_info_p i2c模块信息
 */
void i2c_cmd_read_ack(ls1c_i2c_info_t *i2c_info_p)
{
    i2c_cmd(i2c_info_p, LS1C_I2C_CMD_READ_ACK);
    return ;
}


/*
 * 执行读nack命令,发送读nack信号
 * @i2c_info_p i2c模块信息
 */
void i2c_cmd_read_nack(ls1c_i2c_info_t *i2c_info_p)
{
    i2c_cmd(i2c_info_p, LS1C_I2C_CMD_READ_NACK);
    return ;
}


/*
 * 发送中断应答信号
 * @i2c_info_p i2c模块信息
 */
void i2c_cmd_iack(ls1c_i2c_info_t *i2c_info_p)
{
    i2c_cmd(i2c_info_p, LS1C_I2C_CMD_IACK);
    return ;
}


/*
 * 获取状态寄存器的值
 * @i2c_info_p i2c模块信息
 * @ret 状态寄存器的值
 */
unsigned char i2c_get_status(ls1c_i2c_info_t *i2c_info_p)
{
    void *i2c_base = i2c_get_base(i2c_info_p->I2Cx);

    return reg_read_8(i2c_base + LS1C_I2C_STATUS_OFFSET);
}


/*
 * Poll the i2c status register until the specified bit is set.
 * Returns 0 if timed out (100 msec).
 * @i2c_info_p i2c模块信息
 * @bit 寄存器的某一位
 * @ret true or false
 */
int i2c_poll_status(ls1c_i2c_info_t *i2c_info_p, unsigned long bit)
{
    int loop_cntr = 20000;

    do {
        delay_us(1);
    } while ((i2c_get_status(i2c_info_p) & bit) && (0 < --loop_cntr));

    return (0 < loop_cntr);
}


/*
 * 初始化指定i2c模块
 * @i2c_info_p 某个i2c模块的信息
 */
void i2c_init(ls1c_i2c_info_t *i2c_info_p)
{
    void *i2c_base = i2c_get_base(i2c_info_p->I2Cx);
    unsigned long i2c_clock = i2c_info_p->clock;
    unsigned char ctrl = reg_read_8(i2c_base + LS1C_I2C_CONTROL_OFFSET);
    unsigned long prescale = 0;

    /* make sure the device is disabled */
    ctrl = ctrl & ~(LS1C_I2C_CONTROL_EN | LS1C_I2C_CONTROL_IEN);
    reg_write_8(ctrl, i2c_base + LS1C_I2C_CONTROL_OFFSET);

    // 设置时钟
    i2c_clock = MIN(i2c_clock, LS1C_I2C_CLOCK_MAX);     // 限制在最大允许范围内
    prescale = clk_get_apb_rate();
    prescale = (prescale / (5 * i2c_clock)) - 1;
    reg_write_8(prescale & 0xff, i2c_base + LS1C_I2C_PRER_LOW_OFFSET);
    reg_write_8(prescale >> 8, i2c_base + LS1C_I2C_PRER_HIGH_OFFSET);
    
    // 使能
    i2c_cmd_iack(i2c_info_p);
    ctrl = ctrl | LS1C_I2C_CONTROL_EN;
    reg_write_8(ctrl, i2c_base + LS1C_I2C_CONTROL_OFFSET);

    return ;
}


/*
 * (再发送一个字节数据之后)接收从机发送的ACK信号
 * @i2c_info_p i2c模块信息
 * @ret LS1C_I2C_ACK or LS1C_I2C_NACK
 */
ls1c_i2c_ack_t i2c_receive_ack(ls1c_i2c_info_t *i2c_info_p)
{
    ls1c_i2c_ack_t ret = LS1C_I2C_NACK;
    
    if (LS1C_I2C_STATUS_NACK & i2c_get_status(i2c_info_p))
    {
        ret = LS1C_I2C_NACK;
    }
    else
    {
        ret = LS1C_I2C_ACK;
    }

    return ret;
}


/*
 * 接收数据
 * @i2c_info_p i2c模块信息
 * @buf 数据缓存
 * @len 待接收数据的长度
 */
ls1c_i2c_ret_t i2c_receive_data(ls1c_i2c_info_t *i2c_info_p, unsigned char *buf, int len)
{
    void *i2c_base = i2c_get_base(i2c_info_p->I2Cx);
    int i = 0;

    for (i=0; i<len; i++)
    {
        // 开始接收
        if (i != (len - 1))
            i2c_cmd_read_ack(i2c_info_p);
        else 
            i2c_cmd_read_nack(i2c_info_p);

        // 等待，直到接收完成
        if (!i2c_poll_status(i2c_info_p, LS1C_I2C_STATUS_TIP))
            return LS1C_I2C_RET_TIMEOUT;

        // 读取数据，并保存
        *buf++ = reg_read_8(i2c_base + LS1C_I2C_DATA_OFFSET);
    }

    return LS1C_I2C_RET_OK;
}


/*
 * 发送START信号和地址
 * @i2c_info_p i2c模块信息
 * @slave_addr 从机地址
 * @direction 数据传输方向(读、写)
 */
ls1c_i2c_ret_t i2c_send_start_and_addr(ls1c_i2c_info_t *i2c_info_p, 
                                       unsigned char slave_addr,
                                       ls1c_i2c_direction_t direction)
{
    void *i2c_base = i2c_get_base(i2c_info_p->I2Cx);
    unsigned char data = 0;
    
    // 等待i2c总线空闲
    if (!i2c_poll_status(i2c_info_p, LS1C_I2C_STATUS_BUSY))
        return LS1C_I2C_RET_TIMEOUT;

    // 填充地址到数据寄存器
    data = (slave_addr << 1) | ((LS1C_I2C_DIRECTION_READ == direction) ? 1 : 0);
    reg_write_8(data , i2c_base + LS1C_I2C_DATA_OFFSET);

    // 开始发送
    i2c_cmd_start(i2c_info_p);

    // 等待，直到发送完成
    if (!i2c_poll_status(i2c_info_p, LS1C_I2C_STATUS_TIP))
        return LS1C_I2C_RET_TIMEOUT;

    return LS1C_I2C_RET_OK;
}


/*
 * 发送数据
 * @i2c_info_p i2c模块信息
 * @data 待发送的数据
 * @len 待发送数据的长度
 */
ls1c_i2c_ret_t i2c_send_data(ls1c_i2c_info_t *i2c_info_p, unsigned char *data, int len)
{
    void *i2c_base = i2c_get_base(i2c_info_p->I2Cx);
    int i = 0;

    for (i=0; i<len; i++)
    {
        // 将一个字节数据写入数据寄存器
        reg_write_8(*data++, i2c_base + LS1C_I2C_DATA_OFFSET);

        // 开始发送
        reg_write_8(LS1C_I2C_CMD_WRITE, i2c_base + LS1C_I2C_CMD_OFFSET);

        // 等待，直到发送完成
        if (!i2c_poll_status(i2c_info_p, LS1C_I2C_STATUS_TIP))
            return LS1C_I2C_RET_TIMEOUT;

        // 读取应答信号
        if (LS1C_I2C_ACK != i2c_receive_ack(i2c_info_p))
            return len;
    }

    return LS1C_I2C_RET_OK;
}



/*
 * 发送STOP信号
 * @i2c_info_p i2c模块信息
 */
void i2c_send_stop(ls1c_i2c_info_t *i2c_info_p)
{
    i2c_cmd_stop(i2c_info_p);
    return ;
}


