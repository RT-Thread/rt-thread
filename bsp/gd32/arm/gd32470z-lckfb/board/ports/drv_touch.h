/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-05-23     godmial      Refactor to conform to RT-Thread coding style.
 */

#ifndef __TOUCH_H__
#define __TOUCH_H__

#include "stdio.h"
#include "string.h"
#include "gd32f4xx.h"


#define SCL_RCU    RCU_GPIOB
#define SCL_PORT   GPIOB
#define SCL_PIN    GPIO_PIN_6
#define SCL_ON     gpio_bit_set(SCL_PORT, SCL_PIN)
#define SCL_OFF    gpio_bit_reset(SCL_PORT, SCL_PIN)
#define SCL_TOGGLE gpio_bit_toggle(SCL_PORT, SCL_PIN)

#define SDA_RCU    RCU_GPIOB
#define SDA_PORT   GPIOB
#define SDA_PIN    GPIO_PIN_7
#define SDA_ON     gpio_bit_set(SDA_PORT, SDA_PIN)
#define SDA_OFF    gpio_bit_reset(SDA_PORT, SDA_PIN)
#define SDA_TOGGLE gpio_bit_toggle(SDA_PORT, SDA_PIN)

/* IO direction settings */
#define CT_SDA_IN()  gpio_mode_set(SCL_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, SDA_PIN);  //{GPIOF->MODER&=~(3<<(2*11));GPIOF->MODER|=0<<2*11;}	//PF11输入模式
#define CT_SDA_OUT() gpio_mode_set(SCL_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, SDA_PIN); //{GPIOF->MODER&=~(3<<(2*11));GPIOF->MODER|=1<<2*11;} 	//PF11输出模式
/* IO operations */
#define CT_IIC_SCL                                            // PBout(0) 	//SCL
#define CT_IIC_SDA(val) ((val) == 1 ? SDA_ON : SDA_OFF)       // PFout(11) //SDA
#define CT_READ_SDA     gpio_input_bit_get(SDA_PORT, SDA_PIN) // PFin(11)  //输入SDA
/* Reset and interrupt pin definitions */
#define RST_RCU    RCU_GPIOD
#define RST_PORT   GPIOD
#define RST_PIN    GPIO_PIN_12
#define RST_ON     gpio_bit_set(RST_PORT, RST_PIN);
#define RST_OFF    gpio_bit_reset(RST_PORT, RST_PIN);
#define RST_TOGGLE gpio_bit_toggle(RST_PORT, RST_PIN);

#define INT_RCU    RCU_GPIOD
#define INT_PORT   GPIOD
#define INT_PIN    GPIO_PIN_11
#define INT_ON     gpio_bit_set(INT_PORT, INT_PIN);
#define INT_OFF    gpio_bit_reset(INT_PORT, INT_PIN);
#define INT_TOGGLE gpio_bit_toggle(INT_PORT, INT_PIN);

/* I2C command definitions */
#define FT_CMD_WR 0X70 /**< FT5206 write command */
#define FT_CMD_RD 0X71 /**< FT5206 read command */
/* FT5206 register definitions */
#define FT_DEVIDE_MODE       0x00 /**< Mode control register */
#define FT_REG_NUM_FINGER    0x02 /**< Touch status register */
#define FT_TP1_REG           0x03 /**< Touch point 1 data */
#define FT_TP2_REG           0x09 /**< Touch point 2 data */
#define FT_TP3_REG           0x0F /**< Touch point 3 data */
#define FT_TP4_REG           0x15 /**< Touch point 4 data */
#define FT_TP5_REG           0x1B /**< Touch point 5 data */
#define FT_ID_G_LIB_VERSION  0xA1 /**< Firmware version */
#define FT_ID_G_MODE         0xA4 /**< Interrupt mode control */
#define FT_ID_G_THGROUP      0x80 /**< Touch sensitivity */
#define FT_ID_G_PERIODACTIVE 0x88 /**< Active period register */

#define TP_PRES_DOWN 0x80         /**< Touch pressed flag */
#define TP_CATH_PRES 0x40         /**< Key press detected flag */
#define CT_MAX_TOUCH 5            /**< Maximum number of supported touch points */
/**
 * @brief Touch point device structure.
 */
typedef struct
{
    uint16_t x[CT_MAX_TOUCH]; /**< X coordinates of touch points */
    uint16_t y[CT_MAX_TOUCH]; /**< Y coordinates of touch points */
    uint8_t  sta;             /**< Touch status flag */
    float    xfac;            /**< X axis scaling factor */
    float    yfac;            /**< Y axis scaling factor */
    short    xoff;            /**< X axis offset */
    short    yoff;            /**< Y axis offset */
    uint8_t  touchtype;       /**< Touch type flag */
} _m_tp_dev;

extern _m_tp_dev tp_dev;

/**
 * @brief Initialize I2C GPIO lines.
 */
void CT_IIC_Init(void);

/**
 * @brief Generate I2C start condition.
 */
void CT_IIC_Start(void);

/**
 * @brief Generate I2C stop condition.
 */
void CT_IIC_Stop(void);

/**
 * @brief Send a byte over I2C.
 *
 * @param txd Byte to send.
 */
void CT_IIC_Send_Byte(uint8_t txd);

/**
 * @brief Read a byte over I2C.
 *
 * @param ack 1 to send ACK after read, 0 for NACK.
 *
 * @return The received byte.
 */
uint8_t CT_IIC_Read_Byte(unsigned char ack);

/**
 * @brief Wait for I2C ACK.
 *
 * @return 0 on success, non-zero on timeout.
 */
uint8_t CT_IIC_Wait_Ack(void);

/**
 * @brief Generate I2C ACK.
 */
void CT_IIC_Ack(void);

/**
 * @brief Generate I2C NACK.
 */
void CT_IIC_NAck(void);

/**
 * @brief Write data to FT5206 register.
 *
 * @param reg Register address.
 * @param buf Pointer to data.
 * @param len Number of bytes to write.
 *
 * @return 0 if success, non-zero otherwise.
 */
uint8_t FT5206_WR_Reg(uint16_t reg, uint8_t *buf, uint8_t len);

/**
 * @brief Read data from FT5206 register.
 *
 * @param reg Register address.
 * @param buf Buffer to store data.
 * @param len Number of bytes to read.
 */
void FT5206_RD_Reg(uint16_t reg, uint8_t *buf, uint8_t len);

/**
 * @brief Initialize the FT5206 touch controller.
 *
 * @return 0 if successful.
 */
uint8_t FT5206_Init(void);

/**
 * @brief Poll the FT5206 for touch input.
 *
 * @param mode Scan mode.
 *
 * @return 1 if touch detected, 0 otherwise.
 */
uint8_t FT5206_Scan(uint8_t mode);

/**
 * @brief Wait until touch contact leaves specified area.
 *
 * @param contact Touch point index.
 * @param sx Start X coordinate.
 * @param sy Start Y coordinate.
 * @param ex End X coordinate.
 * @param ey End Y coordinate.
 */
void letgo_scan(uint16_t contact, uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey);


#endif
