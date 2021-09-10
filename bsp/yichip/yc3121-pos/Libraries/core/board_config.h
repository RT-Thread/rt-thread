/*
File Name    : board_config.h
Author       : Yichip
Version      : V1.0
Date         : 2020/07/17
Description  : board I/O config file.
*/

#ifndef __BOARD_CONFIG_H__
#define __BOARD_CONFIG_H__

#include "yc3121.h"
#include "yc_gpio.h"
#include "yc_exti.h"
#include "yc_spi.h"

//开发板选择
#define MPOS_BOARD_V2_1  0
#define EPOS_BOARD_V1_0  1
#define BOARD_VER  EPOS_BOARD_V1_0

//ADC管脚配置
#define ADC_IO_PORT  GPIOC
#define ADC2_IO_PIN  GPIO_Pin_7
#define ADC3_IO_PIN  GPIO_Pin_8

//外部中断管脚配置
#define EXTI_PORT  EXTI_Line0
#define EXTI_PIN   EXTI_PinSource14

#if (BOARD_VER == MPOS_BOARD_V2_1)
//DEBUG串口配置
#define UARTBAUD            921600
#define UART0_TX_PORT       GPIOA
#define UART0_TX_PIN        GPIO_Pin_1
#define UART0_RX_PORT       GPIOA
#define UART0_RX_PIN        GPIO_Pin_0

//串口1配置
#define UART1_TX_PORT       GPIOA
#define UART1_TX_PIN        GPIO_Pin_14
#define UART1_RX_PORT       GPIOA
#define UART1_RX_PIN        GPIO_Pin_15

//BEEP驱动IO
#define BEEP_PWM   0
#define BEEP_PORT  GPIOA
#define BEEP_PIN   GPIO_Pin_11

//IC卡在位检测IO
#define DET_PORT  GPIOC
#define DET_PIN   GPIO_Pin_12

//NFC IO
#define NFC_SPI	SPI1
#define NFC_12M_CLK_PORT  GPIOA
#define NFC_12M_CLK_PIN   GPIO_Pin_3

#define NFC_RST_PORT  GPIOA
#define NFC_RST_PIN   GPIO_Pin_4

#define NFC_SPI_MISO_PORT  GPIOB
#define NFC_SPI_MISO_PIN   GPIO_Pin_2

#define NFC_SPI_MOSI_PORT  GPIOB
#define NFC_SPI_MOSI_PIN   GPIO_Pin_1

#define NFC_SPI_SCL_PORT  GPIOB
#define NFC_SPI_SCL_PIN   GPIO_Pin_0

#define NFC_SPI_CS_PORT  GPIOB
#define NFC_SPI_CS_PIN   GPIO_Pin_6

//EEPROM写保护控制IO
#define IIC_WP2_PORT    GPIOB
#define IIC_WP2_PIN     GPIO_Pin_0
#define IIC_WP128_PORT  GPIOC
#define IIC_WP128_PIN   GPIO_Pin_10

//IIC驱动IO
#define IIC_SDA_PORT GPIOB
#define IIC_SDA_PIN  GPIO_Pin_2
#define IIC_SCL_PORT GPIOA
#define IIC_SCL_PIN  GPIO_Pin_11

//KEYBOARD配置
#define GPIO_GROUP_Line_1 GPIOC
#define Line_1 GPIO_Pin_7

#define GPIO_GROUP_Line_2 GPIOC
#define Line_2 GPIO_Pin_9

#define GPIO_GROUP_Line_3 GPIOC
#define Line_3 GPIO_Pin_8

#define GPIO_GROUP_Line_4 GPIOC
#define Line_4 GPIO_Pin_10

#define GPIO_GROUP_Line_5 GPIOC
#define Line_5 GPIO_Pin_11

//LCD屏幕驱动配置
#define LCD_SPI     SPI0
#define LCDSDA_PIN  GPIO_Pin_1
#define LCDSDA_PORT GPIOB
#define LCDSCL_PIN  GPIO_Pin_0
#define LCDSCL_PORT GPIOB
#define LCDCS_PIN   GPIO_Pin_6
#define LCDCS_PORT  GPIOC
#define LCDRST_PIN  GPIO_Pin_5
#define LCDRST_PORT GPIOA
#define LCDA0_PIN   GPIO_Pin_10
#define LCDA0_PORT  GPIOA
#define LCDBL_PIN   GPIO_Pin_2
#define LCDBL_PORT  GPIOA

#elif (BOARD_VER == EPOS_BOARD_V1_0)
//DEBUG串口配置
#define UARTBAUD            921600
#define UART0_TX_PORT       GPIOA
#define UART0_TX_PIN        GPIO_Pin_1
#define UART0_RX_PORT       GPIOA
#define UART0_RX_PIN        GPIO_Pin_0

//串口1配置
#define UART1_TX_PORT       GPIOA
#define UART1_TX_PIN        GPIO_Pin_14
#define UART1_RX_PORT       GPIOA
#define UART1_RX_PIN        GPIO_Pin_15

//BEEP驱动IO
#define BEEP_PWM   0
#define BEEP_PORT  GPIOC
#define BEEP_PIN   GPIO_Pin_1

//IC卡在位检测IO
#define DET_PORT  GPIOA
#define DET_PIN   GPIO_Pin_4

//NFC IO
#define NFC_SPI	SPI1
#define NFC_12M_CLK_PORT  GPIOC
#define NFC_12M_CLK_PIN   GPIO_Pin_10

#define NFC_RST_PORT  GPIOC
#define NFC_RST_PIN   GPIO_Pin_5

#define NFC_TVDD_PORT  GPIOC
#define NFC_TVDD_PIN   GPIO_Pin_4

#define NFC_SPI_MISO_PORT  GPIOC
#define NFC_SPI_MISO_PIN   GPIO_Pin_6

#define NFC_SPI_MOSI_PORT  GPIOC
#define NFC_SPI_MOSI_PIN   GPIO_Pin_7

#define NFC_SPI_SCL_PORT  GPIOC
#define NFC_SPI_SCL_PIN   GPIO_Pin_8

#define NFC_SPI_CS_PORT  GPIOC
#define NFC_SPI_CS_PIN   GPIO_Pin_9

//IIC驱动IO

//KEYBOARD配置
#define KEY_PORT_1    GPIOA
#define KEY_PIN_1     GPIO_Pin_9

#define KEY_PORT_2    GPIOA
#define KEY_PIN_2     GPIO_Pin_15

#define KEY_PORT_3    GPIOA
#define KEY_PIN_3     GPIO_Pin_14

#define KEY_PORT_4    GPIOA
#define KEY_PIN_4     GPIO_Pin_8

#define KEY_PORT_5    GPIOA
#define KEY_PIN_5     GPIO_Pin_7

#define KEY_PORT_6    GPIOA
#define KEY_PIN_6     GPIO_Pin_6

//TFT屏幕驱动配置
#define ST7789VTFTSPI       SPI1
#define ST7789_TFT_SDA_PIN  GPIO_Pin_7
#define ST7789_TFT_SDA_PORT GPIOC

#define ST7789_TFT_A0_PIN   GPIO_Pin_10
#define ST7789_TFT_A0_PORT  GPIOA

#define ST7789_TFT_SCL_PIN  GPIO_Pin_8
#define ST7789_TFT_SCL_PORT GPIOC

#define ST7789_TFT_RST_PIN  GPIO_Pin_11
#define ST7789_TFT_RST_PORT GPIOA

#define ST7789_TFT_CS_PIN   GPIO_Pin_5
#define ST7789_TFT_CS_PORT  GPIOA

#define ST7789_TFT_BL_PIN   GPIO_Pin_12
#define ST7789_TFT_BL_PORT  GPIOA
#define ST7789_TFT_BL_HIGH_LIGHT	1

/*QRdecode tft */
//tft camera io
#define QR_CAMERA_FREQ       24
#define QR_CAMERA_SDA        28
#define QR_CAMERA_SCL        29
#define QR_CAMERA_RST        32
#define QR_CAMERA_PD         31//power down
#define QR_CAMERA_MCLK       35
#define QR_CAMERA_PCLK       34
#define QR_CAMERA_DATA       30
#define QR_CAMERA_CS         42

//tft io
#define QR_TFT_RST             (11)                  /*rst pin*/
#define QR_TFT_CS              ( 5)                   /*cs pin*/
#define QR_TFT_CLK             (40)                  /*clk pin*/
#define QR_TFT_MOSI            (39)                  /*mosi pin*/
#define QR_TFT_A0              (10)                  /*a0 pin*/
#define QR_TFT_BL              (12 | (1 << 7))       /*bl pin*/
#define QR_TFT_START_COLUMN    ( (320 - 236) / 2 )   /*display center*/

//key io
#define QR_KEY_T_MATRIX        ( 0)                  /*key mode :0: T matrix key,1:matrix key*/
#define QR_KEY_LINE_NUM        ( 6)                  /*Value range 0~10*/
#define QR_KEY_COL_NUM         ( 0)                  /*Value range (T matrix key: 0)*/
#define QR_KEY_CANCEL_POSTION  ( (5 << 4) | 6 )      /*Exit key*/
#define QR_KEY_LINE_1          ( 9)                  /*GPIO pin*/
#define QR_KEY_LINE_2          (15)                  /*GPIO pin*/
#define QR_KEY_LINE_3          (14)                  /*GPIO pin*/
#define QR_KEY_LINE_4          ( 8)                  /*GPIO pin*/
#define QR_KEY_LINE_5          ( 7)                  /*GPIO pin*/
#define QR_KEY_LINE_6          ( 6)                  /*GPIO pin*/

/*QRdecode lcd */
//lcd io
#define QR_LCD_RST             (14)
#define QR_LCD_CS              (15)
#define QR_LCD_CLK             (10)
#define QR_LCD_MOSI            ( 3)
#define QR_LCD_A0              (11)
#define QR_LCD_BL              (39 | (1 << 7))
#define QR_LCD_SPI_BOUDSPEED   (0xFF)
#define QR_LCD_BLANK_LINE_NUM  ( 0)                   /*Value range 0~7*/
#define QR_LCD_COLUMN_NUM      (64)                   /*Value range 0~7*/
#define QR_LCD_START_COLUMN    ((128 - 64)/2)

//lcd camera io

#define QR_LCD_CAMERA_FREQ       (24)
#define QR_LCD_CAMERA_SDA        (17)
#define QR_LCD_CAMERA_SCL        (16)
#define QR_LCD_CAMERA_RST        (41)
#define QR_LCD_CAMERA_PD         ( 5)//power down
#define QR_LCD_CAMERA_MCLK       (40)
#define QR_LCD_CAMERA_PCLK       (38)
#define QR_LCD_CAMERA_DATA       ( 2)
#define QR_LCD_CAMERA_CS         (42)

/*touch*/
#define TP_Y_HIGH_PORT          GPIOA
#define TP_Y_HIGH_IO_PIN        GPIO_Pin_4
#define TP_Y_LOW_PORT           GPIOC
#define TP_Y_LOW_IO_PIN         GPIO_Pin_12
#define TP_X_HIGH_PORT          GPIOA
#define TP_X_HIGH_IO_PIN        GPIO_Pin_13
#define TP_X_LOW_PORT           GPIOC
#define TP_X_LOW_IO_PIN         GPIO_Pin_11

#endif

#endif
