/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-06     勤为本       first version
 */


// 硬件i2c接口的头文件

#ifndef __OPENLOONGSON_I2C_H
#define __OPENLOONGSON_I2C_H



// I2C的时钟频率
#define LS1C_I2C_CLOCK_DEFAULT              (100000)  // Hz. 默认频率
#define LS1C_I2C_CLOCK_MAX                  (400000)  // Hz, max 400 Kbits/sec


// I2C模块编号
typedef enum
{
    LS1C_I2C_0 = 0,
    LS1C_I2C_1,
    LS1C_I2C_2
}ls1c_i2c_t;


// I2C数据传输方向
typedef enum
{
    LS1C_I2C_DIRECTION_WRITE = 0,       // 主机向从机写信息
    LS1C_I2C_DIRECTION_READ,            // 主机向从机读信息
}ls1c_i2c_direction_t;


// 硬件I2C信息
typedef struct
{
    ls1c_i2c_t I2Cx;                    // i2c模块编号
    unsigned long clock;                // i2c时钟频率，单位hz
}ls1c_i2c_info_t;


// I2C应答
typedef enum
{
    LS1C_I2C_ACK = 0,                   // 收到应答
    LS1C_I2C_NACK = 1,                  // 没收到应答
}ls1c_i2c_ack_t;


// 函数返回值
typedef enum
{
    LS1C_I2C_RET_OK = 0,                // OK
    LS1C_I2C_RET_TIMEOUT,               // 超时
}ls1c_i2c_ret_t;



/*
 * 初始化指定i2c模块
 * @i2c_info_p 某个i2c模块的信息
 */
void i2c_init(ls1c_i2c_info_t *i2c_info_p);


/*
 * (再发送一个字节数据之后)接收从机发送的ACK信号
 * @i2c_info_p i2c模块信息
 * @ret LS1C_I2C_ACK or LS1C_I2C_NACK
 */
ls1c_i2c_ack_t i2c_receive_ack(ls1c_i2c_info_t *i2c_info_p);


/*
 * 接收数据
 * @i2c_info_p i2c模块信息
 * @buf 数据缓存
 * @len 待接收数据的长度
 */
ls1c_i2c_ret_t i2c_receive_data(ls1c_i2c_info_t *i2c_info_p, unsigned char *buf, int len);



/*
 * 发送START信号和地址
 * @i2c_info_p i2c模块信息
 * @slave_addr 从机地址
 * @direction 数据传输方向(读、写)
 */
ls1c_i2c_ret_t i2c_send_start_and_addr(ls1c_i2c_info_t *i2c_info_p, 
                                       unsigned char slave_addr,
                                       ls1c_i2c_direction_t direction);


/*
 * 发送数据
 * @i2c_info_p i2c模块信息
 * @data 待发送的数据
 * @len 待发送数据的长度
 */
ls1c_i2c_ret_t i2c_send_data(ls1c_i2c_info_t *i2c_info_p, unsigned char *data, int len);


/*
 * 发送STOP信号
 * @i2c_info_p i2c模块信息
 */
void i2c_send_stop(ls1c_i2c_info_t *i2c_info_p);



#endif

