/*!
    \file  gd32f450z_lcd_eval.h
    \brief definitions for GD32F450Z_EVAL's LCD
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-10-19, V1.0.0, firmware for GD32F450Z
*/

#ifndef GD32F450Z_LCD_EVAL_H
#define GD32F450Z_LCD_EVAL_H

#include "gd32f450z_eval.h"

#define LCD_CS_PIN                   GPIO_PIN_11
#define LCD_CS_GPIO_PORT             GPIOD
#define LCD_CS_GPIO_CLK              RCU_GPIOD

#define LCD_RS_PIN                   GPIO_PIN_3
#define LCD_RS_GPIO_PORT             GPIOE
#define LCD_RS_GPIO_CLK              RCU_GPIOE

#define LCD_SPI_SCK_PIN              GPIO_PIN_13
#define LCD_SPI_SCK_GPIO_PORT        GPIOG
#define LCD_SPI_SCK_GPIO_CLK         RCU_GPIOG

#define LCD_SPI_MOSI_PIN             GPIO_PIN_14
#define LCD_SPI_MOSI_GPIO_PORT       GPIOG
#define LCD_SPI_MOSI_GPIO_CLK        RCU_GPIOG

#define LCD_SPI                      SPI5
#define LCD_SPI_CLK                  RCU_SPI5

/* enable the LCD */
void lcd_enable(void);
/* disable the LCD */
void lcd_disable(void);
/* configure the LCD control line */
void lcd_ctrl_line_config(void);
/* set the LCD control line */
void lcd_ctrl_line_set(uint32_t gpiox, uint16_t gpiopin);
/* reset the LCD control line */
void lcd_ctrl_line_reset(uint32_t gpiox, uint16_t gpiopin);
/* configure the LCD SPI and it's GPIOs */
void lcd_spi_config(void);
/* write command to select LCD register */
void lcd_command_write(uint8_t lcd_register);
/* write data to select LCD register */
void lcd_data_write(uint8_t value);
/* configure the LCD based on the power on sequence */
void lcd_power_on(void);
void lcd_power_on3(void);
#endif /* GD32F450Z_LCD_EVAL_H */
