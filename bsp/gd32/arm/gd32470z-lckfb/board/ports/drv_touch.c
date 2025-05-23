/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-05-23     godmial      Refactor to conform to RT-Thread coding style.
 */

#include <board.h>
#include <rthw.h>
#include <rtthread.h>
#include "drv_touch.h"
#include "drv_lcd.h"

#define DRV_DEBUG
#define LOG_TAG "drv.touch"
#include <drv_log.h>

_m_tp_dev tp_dev;

const uint16_t FT5206_TPX_TBL[5] = {FT_TP1_REG, FT_TP2_REG, FT_TP3_REG, FT_TP4_REG, FT_TP5_REG};
uint8_t        g_gt_tnum         = 5; /**< Default number of supported touch points (5-point touch) */


/**
 * @brief Delay for a specified number of microseconds.
 *
 * @note This function uses the SysTick timer to implement microsecond delay by polling.
 *
 * @param _nus Number of microseconds to delay.
 */
void delay_us(uint32_t _nus)
{
    uint8_t  fac_us = 0;
    uint32_t ticks;
    uint32_t t_old, t_now, t_cnt = 0;
    uint32_t reload = SysTick->LOAD;

    fac_us = SystemCoreClock / 1000000;
    ticks  = _nus * fac_us - fac_us * 7 / 20;
    t_old  = SysTick->VAL;

    while (1)
    {
        t_now = SysTick->VAL;

        if (t_now < t_old)
        {
            t_cnt += t_old - t_now;
        }
        else
        {
            t_cnt += t_old + (reload - t_now);
        }

        if (t_cnt >= ticks)
        {
            break;
        }

        t_old = t_now;
    };
}


/**
 * @brief Delay function wrapper for touch operations.
 *
 * @param us Number of microseconds to delay.
 */
void touch_delay_1us(uint16_t us)
{
    delay_us(us);
}

/**
 * @brief Delay to control I2C speed.
 *
 * @note Used between I2C signal toggles to ensure proper timing.
 */
void CT_Delay(void)
{
    touch_delay_1us(2);
}

/**
 * @brief Initialize the I2C interface for the capacitive touch chip.
 *
 * @note Configures GPIO ports for SCL and SDA lines as outputs with pull-up resistors.
 */
void CT_IIC_Init(void)
{
    /* enable the led clock */
    rcu_periph_clock_enable(SCL_RCU);
    /* configure led GPIO port */
    gpio_mode_set(SCL_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, SCL_PIN);
    gpio_output_options_set(SCL_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SCL_PIN);

    rcu_periph_clock_enable(SDA_RCU);
    gpio_mode_set(SDA_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, SDA_PIN);
    gpio_output_options_set(SDA_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SDA_PIN);
}

/**
 * @brief Generate I2C start condition.
 *
 * @note Starts communication by pulling SDA low while SCL is high.
 */
void CT_IIC_Start(void)
{
    CT_SDA_OUT();
    SDA_ON;
    SCL_ON;
    touch_delay_1us(30);
    SDA_OFF;
    CT_Delay();
    SCL_OFF;
}

/**
 * @brief Generate I2C stop condition.
 *
 * @note Ends communication by pulling SDA high while SCL is high.
 */
void CT_IIC_Stop(void)
{
    CT_SDA_OUT();
    SCL_ON;
    touch_delay_1us(30);
    SDA_OFF;
    CT_Delay();
    SDA_ON;
}

/**
 * @brief Wait for I2C ACK signal.
 *
 * @return 0 if ACK received successfully, 1 if timeout occurred.
 *
 * @warning If ACK is not received within 250 iterations, a stop condition is generated.
 */
uint8_t CT_IIC_Wait_Ack(void)
{
    uint8_t ucErrTime = 0;
    CT_SDA_IN();
    SDA_ON;
    SCL_ON;
    CT_Delay();
    while (CT_READ_SDA)
    {
        ucErrTime++;
        if (ucErrTime > 250)
        {
            CT_IIC_Stop();
            return 1;
        }
        CT_Delay();
    }
    SCL_OFF;
    return 0;
}

/**
 * @brief Generate I2C ACK signal.
 *
 * @note This is used to acknowledge receipt of a byte in I2C communication.
 */
void CT_IIC_Ack(void)
{
    SCL_OFF;
    CT_SDA_OUT();
    CT_Delay();
    SDA_OFF;
    CT_Delay();
    SCL_ON;
    CT_Delay();
    SCL_OFF;
}

/**
 * @brief Generate I2C NACK signal.
 *
 * @note This is used to indicate the end of reading in I2C communication.
 */
void CT_IIC_NAck(void)
{
    SCL_OFF;
    CT_SDA_OUT();
    CT_Delay();
    SDA_ON;
    CT_Delay();
    SCL_ON;
    CT_Delay();
    SCL_OFF;
}


/**
 * @brief Send a byte over I2C.
 *
 * @param txd Byte to send.
 *
 * @note Sends 8 bits starting from the MSB over the SDA line.
 */
void CT_IIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
    CT_SDA_OUT();
    SCL_OFF;
    CT_Delay();
    for (t = 0; t < 8; t++)
    {
        if ((txd & 0x80) >> 7)
        {
            gpio_bit_set(SDA_PORT, SDA_PIN);
        }
        else
        {
            gpio_bit_reset(SDA_PORT, SDA_PIN);
        }

        txd <<= 1;
        SCL_ON;
        CT_Delay();
        SCL_OFF;
        CT_Delay();
    }
}

/**
 * @brief Read a byte over I2C.
 *
 * @param ack If 1, send ACK after receiving; if 0, send NACK.
 *
 * @return The received byte.
 */
uint8_t CT_IIC_Read_Byte(unsigned char ack)
{
    volatile uint8_t i, receive = 0;
    CT_SDA_IN();
    touch_delay_1us(30);
    for (i = 0; i < 8; i++)
    {
        SCL_OFF;
        CT_Delay();
        SCL_ON;
        receive <<= 1;

        if (CT_READ_SDA)
            receive++;
    }

    if (!ack)
        CT_IIC_NAck();
    else
        CT_IIC_Ack();
    return receive;
}

/**
 * @brief Write data to FT5206 register.
 *
 * @param reg Register address.
 * @param buf Pointer to data buffer.
 * @param len Length of data to write.
 *
 * @return 0 if successful, non-zero if any write fails.
 */
uint8_t FT5206_WR_Reg(uint16_t reg, uint8_t *buf, uint8_t len)
{
    uint8_t i;
    uint8_t ret = 0;
    CT_IIC_Start();
    CT_IIC_Send_Byte(FT_CMD_WR);
    CT_IIC_Wait_Ack();
    CT_IIC_Send_Byte(reg & 0XFF);
    CT_IIC_Wait_Ack();
    for (i = 0; i < len; i++)
    {
        CT_IIC_Send_Byte(buf[i]);
        ret = CT_IIC_Wait_Ack();
        if (ret)
            break;
    }
    CT_IIC_Stop();
    return ret;
}

/**
 * @brief Read data from FT5206 register.
 *
 * @param reg Register address.
 * @param buf Pointer to buffer to store read data.
 * @param len Number of bytes to read.
 */
void FT5206_RD_Reg(uint16_t reg, uint8_t *buf, uint8_t len)
{
    uint8_t i;
    CT_IIC_Start();
    CT_IIC_Send_Byte(FT_CMD_WR);
    CT_IIC_Wait_Ack();
    CT_IIC_Send_Byte(reg & 0XFF);
    CT_IIC_Wait_Ack();
    CT_IIC_Start();
    CT_IIC_Send_Byte(FT_CMD_RD);
    CT_IIC_Wait_Ack();
    for (i = 0; i < len; i++)
    {
        buf[i] = CT_IIC_Read_Byte(i == (len - 1) ? 0 : 1);
    }
    CT_IIC_Stop();
}

/**
 * @brief Initialize the FT5206 touch screen controller.
 *
 * @note Initializes I2C, sets operational modes and touch sensitivity.
 *
 * @return 0 if initialization is successful.
 */
uint8_t FT5206_Init(void)
{
    uint8_t temp[5];
    /* enable the led clock */
    rcu_periph_clock_enable(INT_RCU);
    /* configure led GPIO port */
    gpio_mode_set(INT_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE, INT_PIN);


    CT_IIC_Init();

    FT5206_WR_Reg(FT_DEVIDE_MODE, temp, 1);
    FT5206_WR_Reg(FT_ID_G_MODE, temp, 1);
    temp[0] = 22;
    FT5206_WR_Reg(FT_ID_G_THGROUP, temp, 1);
    temp[0] = 12;
    FT5206_WR_Reg(FT_ID_G_PERIODACTIVE, temp, 1);

    FT5206_RD_Reg(FT_ID_G_LIB_VERSION, &temp[0], 2);
    printf("CTP ID:%x\r\n", ((uint16_t)temp[0] << 8) + temp[1]);
    return 0;
}

/**
 * @brief Scan the touch screen using polling.
 *
 * @param mode 0 for normal scan mode.
 *
 * @return 1 if a touch is detected, 0 otherwise.
 */
uint8_t FT5206_Scan(uint8_t mode)
{
    uint8_t        buf[4];
    uint8_t        i   = 0;
    uint8_t        res = 0;
    uint8_t        temp;
    uint16_t       tempsta;
    static uint8_t t = 0;
    t++;
    if ((t % 10) == 0 || t < 10)
    {
        FT5206_RD_Reg(FT_REG_NUM_FINGER, &mode, 1);
        if ((mode & 0XF) && ((mode & 0XF) <= g_gt_tnum))
        {
            temp                    = 0XFF << (mode & 0XF);
            tempsta                 = tp_dev.sta;
            tp_dev.sta              = (~temp) | TP_PRES_DOWN | TP_CATH_PRES;
            tp_dev.x[g_gt_tnum - 1] = tp_dev.x[0];
            tp_dev.y[g_gt_tnum - 1] = tp_dev.y[0];

            for (i = 0; i < g_gt_tnum; i++)
            {
                if (tp_dev.sta & (1 << i))
                {
                    FT5206_RD_Reg(FT5206_TPX_TBL[i], buf, 4);
                    if (tp_dev.touchtype & 0X01)
                    {
                        tp_dev.y[i] = ((uint16_t)(buf[0] & 0X0F) << 8) + buf[1];
                        tp_dev.x[i] = ((uint16_t)(buf[2] & 0X0F) << 8) + buf[3];
                    }
                    else
                    {
                        tp_dev.x[i] = (((uint16_t)(buf[0] & 0X0F) << 8) + buf[1]);
                        tp_dev.y[i] = ((uint16_t)(buf[2] & 0X0F) << 8) + buf[3];
                    }
                }
            }
            res = 1;
            if (tp_dev.x[0] > ACTIVE_WIDTH || tp_dev.y[0] > ACTIVE_HEIGHT)
            {
                if ((mode & 0XF) > 1)
                {
                    tp_dev.x[0] = tp_dev.x[1];
                    tp_dev.y[0] = tp_dev.y[1];
                    t           = 0;
                }
                else
                {
                    tp_dev.x[0] = tp_dev.x[g_gt_tnum - 1];
                    tp_dev.y[0] = tp_dev.y[g_gt_tnum - 1];
                    mode        = 0X80;
                    tp_dev.sta  = tempsta;
                }
            }
            else
                t = 0;
        }
    }

    if ((mode & 0X1F) == 0)
    {
        if (tp_dev.sta & TP_PRES_DOWN)
        {
            tp_dev.sta &= ~TP_PRES_DOWN;
        }
        else
        {
            tp_dev.x[0]  = 0xffff;
            tp_dev.y[0]  = 0xffff;
            tp_dev.sta  &= 0XE0;
        }
    }

    if (t > 240)
        t = 10;
    return res;
}

/**
 * @brief Detect touch release by monitoring a specific touch point.
 *
 * @param contact Index of touch contact to check.
 * @param sx Start X coordinate.
 * @param sy Start Y coordinate.
 * @param ex End X coordinate.
 * @param ey End Y coordinate.
 *
 * @note Returns when the touch point leaves the specified rectangle.
 */
void letgo_scan(uint16_t contact, uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey)
{
    while (FT5206_Scan(0))
    {
        if (tp_dev.x[contact] <= sx || tp_dev.x[contact] >= ex)
        {
            return;
        }

        if (tp_dev.y[contact] <= sy && tp_dev.y[contact] >= ey)
        {
            return;
        }
    }
}

/**
 * @brief Example application to test the touch screen functionality.
 *
 * @return Always returns 0.
 *
 * @warning This function runs an infinite loop and is intended for manual test only.
 */
int touch_test(void)
{
    int touch_state = 0;
    FT5206_Init();

    while (1)
    {
        touch_state = FT5206_Scan(0);

        if (touch_state == 1)
        {
            rt_kprintf("touch\r\n");
        }
        rt_thread_mdelay(10);
    }
}
MSH_CMD_EXPORT(touch_test, touch test)
