/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-03-29     Yi.Qiu
 * 2011-06-13     lgnq         modified for FM3 easy kit
 */
#ifndef __LCD_H__
#define __LCD_H__

#include <rtthread.h>
#include "mb9bf506r.h"

/********* LCD Hardward Interface *************
LCD_CS      PORT1.7
LCD_CD      PORT1.6
LCD_WR      PORT1.5
LCD_RD      PORT1.4
LCD_SCK     PORT1.3
LCD_MOSI    PORT1.2
LCD_C86     PORT1.1
LCD_PS      PORT1.0
LCD_DATA[0..7]      PORT5.[0..7]
***********************************************/
#define LCD_CS                  (1UL << 7)
#define LCD_CS_DDR              (FM3_GPIO->DDR1)
#define LCD_CS_PFR              (FM3_GPIO->PFR1)
#define LCD_CS_PDOR             (FM3_GPIO->PDOR1)

#define LCD_CD                  (1UL << 6)
#define LCD_CD_DDR              (FM3_GPIO->DDR1)
#define LCD_CD_PFR              (FM3_GPIO->PFR1)
#define LCD_CD_PDOR             (FM3_GPIO->PDOR1)

#define LCD_PS                  (1UL << 0)
#define LCD_PS_DDR              (FM3_GPIO->DDR1)
#define LCD_PS_PFR              (FM3_GPIO->PFR1)
#define LCD_PS_PDOR             (FM3_GPIO->PDOR1)

#define LCD_CLK                 (1UL << 6)
#define LCD_CLK_DDR             (FM3_GPIO->DDR5)
#define LCD_CLK_PFR             (FM3_GPIO->PFR5)
#define LCD_CLK_PDOR            (FM3_GPIO->PDOR5)

#define LCD_DATA                (1UL << 7)
#define LCD_DATA_DDR            (FM3_GPIO->DDR5)
#define LCD_DATA_PFR            (FM3_GPIO->PFR5)
#define LCD_DATA_PDOR           (FM3_GPIO->PDOR5)

/* LCD driver for ZYMG12864C3 */
#define LCD_WIDTH               128
#define LCD_HEIGHT              64

// Driver the LCD with Parallel or serial interface and the command/data control pin is gpio
#define LCD_CS_HIGH()           LCD_CS_PDOR  |=  LCD_CS
#define LCD_CS_LOW()            LCD_CS_PDOR  &= ~LCD_CS

#define LCD_CD_HIGH()           LCD_CD_PDOR |=  LCD_CD
#define LCD_CD_LOW()            LCD_CD_PDOR &= ~LCD_CD

#define LCD_PS_HIGH()           LCD_PS_PDOR |=  LCD_PS
#define LCD_PS_LOW()            LCD_PS_PDOR &= ~LCD_PS

#define LCD_CLK_HIGH()          LCD_CLK_PDOR |=  LCD_CLK
#define LCD_CLK_LOW()           LCD_CLK_PDOR &= ~LCD_CLK

#define LCD_DATA_HIGH()         LCD_DATA_PDOR |=  LCD_DATA
#define LCD_DATA_LOW()          LCD_DATA_PDOR &= ~LCD_DATA

// define the arrtibute of ZYMG12864(LCM)
#define GUI_LCM_XMAX            128     // defined the lcd's line-number is 128
#define GUI_LCM_YMAX            64      // defined the lcd's column-number is 64
#define GUI_LCM_PAGE            8       // defined the lcd's page-number is 8(GUI_LCM_YMAX/8)

/* set LCD command */
#define DISPLAY_ON              0xAF    // A0,RD,WR:010
#define DISPLAY_OFF             0xAE    // A0,RD,WR:010

#define SET_START_LINE_0        0x40    // A0,RD,WR:010; line0~line63
#define SET_PAGE_ADDR_0         0xB0    // A0,RD,WR:010; addr0~addr8
#define SET_COLH_ADDR_0         0x10    // A0,RD,WR:010;
#define SET_COLL_ADDR_0         0x00    // A0,RD,WR:010; addr0~addr131

#define READ_STATUS             0x-0    // A0,RD,WR:001; BUSY | ADC | ON/OFF |  RESET | 0 0 0 0
#define STATUS_BUSY             0x80
#define STATUS_ADC_REVERSE      0x40    // column address 131-n : SEG n, else column address n : SEG n
#define STATUS_DISPLAY_OFF      0x20
#define STATUS_RESET            0x80

#define WRITE_DATA              0x--    // A0,RD,WR:110
#define READ_DATE               0x--    // A0,RD,WR:101; spi mode is unavailable

#define SET_ADC_NORMAL          0xA0    // A0,RD,WR:010
#define SET_ADC_REVERSE         0xA1    // A0,RD,WR:010
#define DISPLAY_NORMAL          0xA6    // A0,RD,WR:010
#define DISPLAY_REVERSE         0xA7    // A0,RD,WR:010; reverse color
#define DISPLAY_ALL_ON          0xA5    // A0,RD,WR:010
#define DISPLAY_ALL_NORMAL      0xA4    // A0,RD,WR:010

/*************************************************************
*   bias:   1/65duty | 1/49duty | 1/33duty | 1/55duty | 1/53duty *
*   ---------------|----------|----------|----------|--------- *
*   A2:     1/9 bias | 1/8 bias | 1/6 bias | 1/8 bias | 1/8 bias *
*   A3:     1/7 bias | 1/6 bias | 1/5 bias | 1/6 bias | 1/6 bias *
**************************************************************/

#define SET_LCD_BIAS_7          0xA3    // A0,RD,WR:010
#define SET_LCD_BIAS_9          0xA2    // A0,RD,WR:010

#define RMW_MODE_ENABLE         0xE0    // A0,RD,WR:010; the column address locked when read command operating
#define RMW_MODE_END            0xEE    // A0,RD,WR:010; returns to the column address when RMW was entered.
#define RESET_LCD               0xE2    // A0,RD,WR:010


/**************************************************************************************
*   Com Scan Dir:   |   1/65duty        | 1/49duty      | 1/33duty      | 1/55duty      | 1/53duty      *
*   --------------|-------------|-------------|-------------|------------------------   *
*   C0:     Normal  |   COM0:COM63  |   COM0:COM47  |   COM0:COM31  |   COM0:COM53  |   COM0:COM51  *
*   C8:     Reverse |   COM63:COM0  |   COM47:COM0  |   COM31:COM0  |   COM53:COM0  |   COM51:COM0  *
***************************************************************************************/

#define COM_SCAN_DIR_NORMAL     0xC0    // A0,RD,WR:010
#define COM_SCAN_DIR_REVERSE    0xC8    // A0,RD,WR:010

// 0 0 1 0 1 | Booster On | Regulator On | Follower On
#define POWER_BOOSTER_ON        0x2C    // A0,RD,WR:010
#define POWER_REGULATOR_ON      0x2E    // A0,RD,WR:010
#define POWER_FOLLOWER_ON       0x2F    // A0,RD,WR:010

#define SET_RESISTOR_RATIO      0x20    // A0,RD,WR:010; 20~27:small~large

#define SET_ELECVOL_MODE        0x81    // A0,RD,WR:010; double byte command
#define SET_ELECVOL_REG         0x20    // A0,RD,WR:010; the electronic volume(64 voltage levels:00~3F) function is not used.

#define SLEEP_MODE_ENABLE       0xAC    // A0,RD,WR:010; double byte command, preceding command
#define SLEEP_MODE_DISABLE      0xAD    // A0,RD,WR:010; preceding command
#define SLEEP_MODE_DELIVER      0x00    // A0,RD,WR:010; following command

#define BOOST_RATIO_SET         0xF8    // A0,RD,WR:010; double byte command, preceding command
#define BOOST_RATIO_234         0x00    // A0,RD,WR:010; following command
#define BOOST_RATIO_5           0x01    // A0,RD,WR:010; following command
#define BOOST_RATIO_6           0x03    // A0,RD,WR:010; following command

#define COMMAND_NOP             0xE3    // A0,RD,WR:010
#define COMMAND_IC_TEST         0xFC    // A0,RD,WR:010; don't use

#define RT_DEVICE_CTRL_LCD_GET_WIDTH            0
#define RT_DEVICE_CTRL_LCD_GET_HEIGHT           1
#define RT_DEVICE_CTRL_LCD_GET_BPP              2
#define RT_DEVICE_CTRL_LCD_GET_FRAMEBUFFER      3
#define RT_DEVICE_CTRL_LCD_POWER_ON             4
#define RT_DEVICE_CTRL_LCD_POWER_OFF            5
#define RT_DEVICE_CTRL_LCD_CLEAR_SCR            6
#define RT_DEVICE_CTRL_LCD_FILL_ALL             7
#define RT_DEVICE_CTRL_LCD_UPDATE_POINT         8
#define RT_DEVICE_CTRL_LCD_DISPLAY_ON           9
#define RT_DEVICE_CTRL_LCD_DISPLAY_OFF          10
#define RT_DEVICE_CTRL_LCD_PUT_STRING           11

enum
{
    ADC_MSG,
    KEY_MSG,
    CPU_MSG,
    MAX_MSG,
};

struct lcd_msg
{
    rt_uint8_t  type;
    rt_uint16_t adc_value;
    rt_uint8_t  key;
    rt_uint16_t major;
    rt_uint16_t minor;
};

extern rt_uint32_t x;
extern rt_uint32_t y;

void rt_hw_lcd_init(void);

#endif
