/*!
    \file  gd32f303e_lcd_eval.h
    \brief LCD driver header file
*/

/*
    Copyright (C) 2017 GigaDevice

    2017-05-19, V1.0.0, demo for GD32F30x
*/

#ifndef GD32F303E_LCD_EVAL_H
#define GD32F303E_LCD_EVAL_H

#include "gd32f30x.h"

#define BANK0_LCD_D         ((uint32_t)0x65000000)    /*!< LCD data address */
#define BANK0_LCD_C         ((uint32_t)0x64000000)    /*!< LCD register address */

/* LCD registers */
#define R0                  0x00
#define R1                  0x01
#define R2                  0x02
#define R3                  0x03
#define R4                  0x04
#define R5                  0x05
#define R6                  0x06
#define R7                  0x07
#define R8                  0x08
#define R9                  0x09
#define R10                 0x0A
#define R11                 0x0B
#define R12                 0x0C
#define R13                 0x0D
#define R14                 0x0E
#define R15                 0x0F
#define R16                 0x10
#define R17                 0x11
#define R18                 0x12
#define R19                 0x13
#define R20                 0x14
#define R21                 0x15
#define R22                 0x16
#define R23                 0x17
#define R24                 0x18
#define R25                 0x19
#define R26                 0x1A
#define R27                 0x1B
#define R28                 0x1C
#define R29                 0x1D
#define R30                 0x1E
#define R31                 0x1F
#define R32                 0x20
#define R33                 0x21
#define R34                 0x22
#define R35                 0x23
#define R36                 0x24
#define R37                 0x25
#define R40                 0x28
#define R41                 0x29
#define R43                 0x2B
#define R45                 0x2D
#define R48                 0x30
#define R49                 0x31
#define R50                 0x32
#define R51                 0x33
#define R52                 0x34
#define R53                 0x35
#define R54                 0x36
#define R55                 0x37
#define R56                 0x38
#define R57                 0x39
#define R58                 0x3A
#define R59                 0x3B
#define R60                 0x3C
#define R61                 0x3D
#define R62                 0x3E
#define R63                 0x3F
#define R64                 0x40
#define R65                 0x41
#define R66                 0x42
#define R67                 0x43
#define R68                 0x44
#define R69                 0x45
#define R70                 0x46
#define R71                 0x47
#define R72                 0x48
#define R73                 0x49
#define R74                 0x4A
#define R75                 0x4B
#define R76                 0x4C
#define R77                 0x4D
#define R78                 0x4E
#define R79                 0x4F
#define R80                 0x50
#define R81                 0x51
#define R82                 0x52
#define R83                 0x53
#define R96                 0x60
#define R97                 0x61
#define R106                0x6A
#define R118                0x76
#define R128                0x80
#define R129                0x81
#define R130                0x82
#define R131                0x83
#define R132                0x84
#define R133                0x85
#define R134                0x86
#define R135                0x87
#define R136                0x88
#define R137                0x89
#define R139                0x8B
#define R140                0x8C
#define R141                0x8D
#define R143                0x8F
#define R144                0x90
#define R145                0x91
#define R146                0x92
#define R147                0x93
#define R148                0x94
#define R149                0x95
#define R150                0x96
#define R151                0x97
#define R152                0x98
#define R153                0x99
#define R154                0x9A
#define R157                0x9D
#define R192                0xC0
#define R193                0xC1
#define R229                0xE5

/* LCD color */
#define WHITE               0xFFFF
#define BLACK               0x0000
#define GREY                0xF7DE
#define BLUE                0x001F
#define BLUE2               0x051F
#define RED                 0xF800
#define MAGENTA             0xF81F
#define GREEN               0x07E0
#define CYAN                0x7FFF
#define YELLOW              0xFFE0

#define LINE0               0
#define LINE1               24
#define LINE2               48
#define LINE3               72
#define LINE4               96
#define LINE5               120
#define LINE6               144
#define LINE7               168
#define LINE8               192
#define LINE9               216

/* char format struct definitions */
typedef struct
{
    uint16_t font;              /*!< the type of font */
    uint16_t direction;         /*!< the direction of char */
    uint16_t char_color;        /*!< the color of char */
    uint16_t bk_color;          /*!< the color of backgroud */
}char_format_struct;

#define CHAR_FONT_8_16                    ((uint16_t)0x0000U) /*!< the font of char is 8X16 */
#define CHAR_FONT_16_24                   ((uint16_t)0x0001U) /*!< the font of char is 16X24 */

#define CHAR_DIRECTION_HORIZONTAL         ((uint16_t)0x0000U) /*!< character display direction is horizontal */
#define CHAR_DIRECTION_VERTICAL           ((uint16_t)0x0001U) /*!< character display direction is vertical */

/* lcd peripheral initialize */
void exmc_lcd_init(void);
/* initize the LCD */
void lcd_init(void);
/* write data to the selected LCD register */
void lcd_register_write(uint16_t register_id,uint16_t value);
/* read the value of LCD register */
uint16_t lcd_register_read(uint8_t register_id);
/* write command to LCD register */
void lcd_command_write (uint16_t value);
/* prepare to write to the LCD GRAM */
void lcd_gram_write_prepare(void);
/* write RGB code to the LCD GRAM register */
void lcd_gram_write(uint16_t rgb_code);
/* read data from GRAM */
uint16_t lcd_gram_read(void);
/* set the curson of LCD */
void lcd_cursor_set(uint16_t x,uint16_t y);
/* clear the LCD screen to the specified color */
void lcd_clear(uint16_t Color);
/* set the point according to the specified position and color */
void lcd_point_set(uint16_t x,uint16_t y,uint16_t point);
/* get the point according to the specified position */
uint16_t lcd_point_get(uint16_t x,uint16_t y);
/* set window area */
void lcd_windows_set(uint16_t start_x,uint16_t start_y,uint16_t end_x,uint16_t end_y);
/* draw a horizontal line on LCD screen */
void lcd_hline_draw(uint16_t x,uint16_t start_y,uint16_t end_y,uint16_t color,uint16_t width);
/* draw a rectangle according to the specified position and color */
void lcd_rectangle_draw(uint16_t start_x,uint16_t start_y,uint16_t end_x,uint16_t end_y,uint16_t point);
/* fill the specified color to a rectangle */
void lcd_rectangle_fill(uint16_t start_x,uint16_t start_y,uint16_t end_x,uint16_t end_y,uint16_t color);
/* draw a picture on LCD screen according to the specified position */
void lcd_picture_draw(uint16_t start_x,uint16_t start_y,uint16_t end_x,uint16_t end_y,uint16_t *pic);
/* display a char on LCD screen according to the specified position */
void lcd_char_display(uint16_t x,uint16_t y,uint8_t c,char_format_struct c_format);

#endif /* GD32F303E_LCD_EVAL_H */
