/*!
    \file    gd32f303e_lcd_eval.c
    \brief   LCD driver functions

    \version 2021-03-23, V2.0.0, demo for GD32F30x
*/

/*
    Copyright (c) 2021, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "gd32f30x.h"
#include "gd32f303e_lcd_eval.h"
#include "lcd_font.h"

#define LCD_ILI9320       0x9320
#define LCD_ILI9325       0x9325

#define ABS(X)  ((X) > 0 ? (X) : -(X))

uint16_t device_code;

/*!
    \brief      lcd peripheral initialize
    \param[in]  none 
    \param[out] none
    \retval     none
*/
void exmc_lcd_init(void)
{
    exmc_norsram_parameter_struct lcd_init_struct;
    exmc_norsram_timing_parameter_struct lcd_timing_init_struct;

    /* EXMC clock enable */
    rcu_periph_clock_enable(RCU_EXMC);

    /* GPIO clock enable */
    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_GPIOE);
    rcu_periph_clock_enable(RCU_GPIOG);

    /* configure EXMC_D[0~15]*/
    /* PD14(EXMC_D0), PD15(EXMC_D1),PD0(EXMC_D2), PD1(EXMC_D3), PD8(EXMC_D13), PD9(EXMC_D14), PD10(EXMC_D15) */
    gpio_init(GPIOD, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0 | GPIO_PIN_1| GPIO_PIN_8 | GPIO_PIN_9 |
                                                         GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15);

    /* PE7(EXMC_D4), PE8(EXMC_D5), PE9(EXMC_D6), PE10(EXMC_D7), PE11(EXMC_D8), PE12(EXMC_D9), 
       PE13(EXMC_D10), PE14(EXMC_D11), PE15(EXMC_D12) */
    gpio_init(GPIOE, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | 
                                                         GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | 
                                                         GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);

    /* configure PE2(EXMC_A23) */ 
    gpio_init(GPIOE, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);
    
    /* configure NOE and NWE */
    gpio_init(GPIOD, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_4 | GPIO_PIN_5);

    /* configure EXMC NE1 */
    gpio_init(GPIOG, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);

    lcd_timing_init_struct.asyn_access_mode = EXMC_ACCESS_MODE_A;
    lcd_timing_init_struct.syn_data_latency = EXMC_DATALAT_2_CLK;
    lcd_timing_init_struct.syn_clk_division = EXMC_SYN_CLOCK_RATIO_DISABLE;
    lcd_timing_init_struct.bus_latency = 2;
    lcd_timing_init_struct.asyn_data_setuptime = 18;
    lcd_timing_init_struct.asyn_address_holdtime = 3;
    lcd_timing_init_struct.asyn_address_setuptime = 8;

    lcd_init_struct.norsram_region = EXMC_BANK0_NORSRAM_REGION1;
    lcd_init_struct.write_mode = EXMC_ASYN_WRITE;
    lcd_init_struct.extended_mode = DISABLE;
    lcd_init_struct.asyn_wait = DISABLE;
    lcd_init_struct.nwait_signal = DISABLE;
    lcd_init_struct.memory_write = ENABLE;
    lcd_init_struct.nwait_config = EXMC_NWAIT_CONFIG_BEFORE;
    lcd_init_struct.wrap_burst_mode = DISABLE;
    lcd_init_struct.nwait_polarity = EXMC_NWAIT_POLARITY_LOW;
    lcd_init_struct.burst_mode = DISABLE;
    lcd_init_struct.databus_width = EXMC_NOR_DATABUS_WIDTH_16B;
    lcd_init_struct.memory_type = EXMC_MEMORY_TYPE_SRAM;
    lcd_init_struct.address_data_mux = DISABLE;
    lcd_init_struct.read_write_timing = &lcd_timing_init_struct;
    lcd_init_struct.write_timing = &lcd_timing_init_struct;

    exmc_norsram_init(&lcd_init_struct);

    exmc_norsram_enable(EXMC_BANK0_NORSRAM_REGION1);
}


/*!
    \brief      write data to the selected LCD register
    \param[in]  register_id: the selected register id
    \param[in]  value: the register value to be written
    \param[out] none
    \retval     none
*/

void lcd_register_write(uint16_t register_id,uint16_t value)
{
    *(__IO uint16_t *) (BANK0_LCD_C)= register_id;
    *(__IO uint16_t *) (BANK0_LCD_D)= value;
}

/*!
    \brief      read the value of LCD register
    \param[in]  register_id: the register id
    \param[out] none
    \retval     the register value
*/
uint16_t lcd_register_read(uint8_t register_id)
{
    uint16_t data;
    *(__IO uint16_t *) (BANK0_LCD_C)= register_id;
    data = *(__IO uint16_t *) (BANK0_LCD_D); 
    return  data;
}

/*!
    \brief      write command to LCD register
    \param[in]  value: the register value to be written
    \param[out] none
    \retval     none
*/
void lcd_command_write(uint16_t value)
{
    /* write 16-bit index, then write reg */
    *(__IO uint16_t *) (BANK0_LCD_C) = value;
}

/*!
    \brief      prepare to write to the LCD GRAM register(R22h)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lcd_gram_write_prepare(void)
{
    *(__IO uint16_t *) (BANK0_LCD_C) = 0x0022;
}

/*!
    \brief      write RGB code to the LCD GRAM register
    \param[in]  rgb_code: the pixel color in RGB mode (5-6-5)
    \param[out] none
    \retval     none
*/
void lcd_gram_write(uint16_t rgb_code)
{
    /* write 16-bit GRAM register */
    *(__IO uint16_t *) (BANK0_LCD_D) = rgb_code;
}

/*!
    \brief      read data from GRAM
    \param[in]  none
    \param[out] none
    \retval     GRAM value
*/
uint16_t lcd_gram_read(void)
{
  uint16_t data;
    
  /* write GRAM register (R22h) */
  *(__IO uint16_t *) (BANK0_LCD_C) = 0x0022;
  /* dummy read (invalid data) */
  data = *(__IO uint16_t *) (BANK0_LCD_D);

  data = *(__IO uint16_t *) (BANK0_LCD_D); 
  return data;
}

/*!
    \brief      initialize the LCD
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lcd_init(void)
{
    __IO uint16_t i;

    /* read the LCD controller device code */
    device_code = lcd_register_read(0x0000);

    if(0x8989 == device_code){             // SSD1289
        lcd_register_write(0x0000,0x0001);
        lcd_register_write(0x0003,0xA8A4);
        lcd_register_write(0x000C,0x0000);
        lcd_register_write(0x000D,0x080C);
        lcd_register_write(0x000E,0x2B00);
        lcd_register_write(0x001E,0x00B0);
        lcd_register_write(0x0001,0x2B3F);
        lcd_register_write(0x0002,0x0600);
        lcd_register_write(0x0010,0x0000);
        lcd_register_write(0x0011,0x6070);
        lcd_register_write(0x0005,0x0000);
        lcd_register_write(0x0006,0x0000);
        lcd_register_write(0x0016,0xEF1C);
        lcd_register_write(0x0017,0x0003);
        lcd_register_write(0x0007,0x0233);
        lcd_register_write(0x000B,0x0000);
        lcd_register_write(0x000F,0x0000);
        lcd_register_write(0x0041,0x0000);
        lcd_register_write(0x0042,0x0000);
        lcd_register_write(0x0048,0x0000);
        lcd_register_write(0x0049,0x013F);
        lcd_register_write(0x004A,0x0000);
        lcd_register_write(0x004B,0x0000);
        lcd_register_write(0x0044,0xEF00);
        lcd_register_write(0x0045,0x0000);
        lcd_register_write(0x0046,0x013F);
        lcd_register_write(0x0030,0x0707);
        lcd_register_write(0x0031,0x0204);
        lcd_register_write(0x0032,0x0204);
        lcd_register_write(0x0033,0x0502);
        lcd_register_write(0x0034,0x0507);
        lcd_register_write(0x0035,0x0204);
        lcd_register_write(0x0036,0x0204);
        lcd_register_write(0x0037,0x0502);
        lcd_register_write(0x003A,0x0302);
        lcd_register_write(0x003B,0x0302);
        lcd_register_write(0x0023,0x0000);
        lcd_register_write(0x0024,0x0000);
        lcd_register_write(0x0025,0x8000);
        lcd_register_write(0x004e,0);
        lcd_register_write(0x004f,0);
    }else if((0x9320 == device_code) || (0x9300 == device_code)){    //ILI9320
        lcd_register_write(0x01,0x0100);         //driver output control
        lcd_register_write(0x02,0x0700);         //lcd driver waveform control
        lcd_register_write(0x03,0x1020);         //entry mode set

        lcd_register_write(0x04,0x0000);         //resizing control
        lcd_register_write(0x08,0x0202);         //display control 2
        lcd_register_write(0x09,0x0000);         //display control 3
        lcd_register_write(0x0a,0x0000);         //frame cycle control
        lcd_register_write(0x0c,(1<<0));         //extern display interface control 1
        lcd_register_write(0x0d,0x0000);         //frame maker position
        lcd_register_write(0x0f,0x0000);         //extern display interface control 2

        for(i=50000;i>0;i--);
        lcd_register_write(0x07,0x0101);         //display control
        for(i=50000;i>0;i--);

        lcd_register_write(0x10,(1<<12)|(0<<8)|(1<<7)|(1<<6)|(0<<4));        //power control 1
        lcd_register_write(0x11,0x0007);                                     //power control 2
        lcd_register_write(0x12,(1<<8)|(1<<4)|(0<<0));                       //power control 3
        lcd_register_write(0x13,0x0b00);                                     //power control 4
        lcd_register_write(0x29,0x0000);                                     //power control 7
        lcd_register_write(0x2b,(1<<14)|(1<<4));
        lcd_register_write(0x50,0);              //set x start
        lcd_register_write(0x51,239);            //set x end
        lcd_register_write(0x52,0);              //set y start
        lcd_register_write(0x53,319);            //set y end

        lcd_register_write(0x60,0x2700);         //driver output control
        lcd_register_write(0x61,0x0001);         //driver output control
        lcd_register_write(0x6a,0x0000);         //vertical srcoll control

        lcd_register_write(0x80,0x0000);         //display position? partial display 1
        lcd_register_write(0x81,0x0000);         //ram address start? partial display 1
        lcd_register_write(0x82,0x0000);         //ram address end-partial display 1
        lcd_register_write(0x83,0x0000);         //display position? partial display 2
        lcd_register_write(0x84,0x0000);         //ram address start? partial display 2
        lcd_register_write(0x85,0x0000);         //ram address end? partial display 2

        lcd_register_write(0x90,(0<<7)|(16<<0)); //frame cycle control
        lcd_register_write(0x92,0x0000);         //panel interface control 2
        lcd_register_write(0x93,0x0001);         //panel interface control 3
        lcd_register_write(0x95,0x0110);         //frame cycle control
        lcd_register_write(0x97,(0<<8));
        lcd_register_write(0x98,0x0000);         //frame cycle control
        for(i=50000;i>0;i--);
        lcd_register_write(0x07,0x0173);
        for(i=50000;i>0;i--);

    }else{
        return;
    }
    
    for(i=50000;i>0;i--);
}

/*!
    \brief      set the cursor of LCD
    \param[in]  x: the row-coordinate
    \param[in]  y: the column-coordinate
    \param[out] none
    \retval     none
*/
void lcd_cursor_set(uint16_t x,uint16_t y)
{
    if(0x8989 == device_code){             // SSD1289
        lcd_register_write(0x004e, x);
        lcd_register_write(0x004f, y);
    }else if((0x9320 == device_code) || (0x9300 == device_code)){    //ILI9320
        lcd_register_write(0x20, x);
        lcd_register_write(0x21, y);
    }
}

/*!
    \brief      clear the LCD screen to the specified color
    \param[in]  color: specified screen color
    \param[out] none
    \retval     none
*/
void lcd_clear(uint16_t color)
{
    uint32_t index=0;
    if(0x8989 == device_code){             // SSD1289
        lcd_cursor_set(0,0);
        /* prepare to write GRAM */
        lcd_gram_write_prepare();
        for(index=0; index<LCD_PIXEL_WIDTH*LCD_PIXEL_HEIGHT; index++){
            *(__IO uint16_t *) (BANK0_LCD_D) = color;
        }
    }else if((0x9320 == device_code) || (0x9300 == device_code)){    //ILI9320
        lcd_register_write(0x20, 0);
        lcd_register_write(0x21, 0);
        lcd_command_write(0x22);
        for(index=0; index<LCD_PIXEL_WIDTH*LCD_PIXEL_HEIGHT; index++){
            *(__IO uint16_t *) (BANK0_LCD_D) = color;
        }
    }
}

/*!
    \brief      set the point according to the specified position and color
    \param[in]  x: the row-coordinate
    \param[in]  y: the column-coordinate
    \param[in]  point: specified color of the point
    \param[out] none
    \retval     none
*/
void lcd_point_set(uint16_t x,uint16_t y,uint16_t point)
{
    if ((x > LCD_PIXEL_HEIGHT)||(y > LCD_PIXEL_WIDTH)){
        return;
    }
    if(0x8989 == device_code){             // SSD1289
        lcd_cursor_set(x,y);
        lcd_gram_write_prepare();
        lcd_gram_write(point);
    }else if((0x9320 == device_code) || (0x9300 == device_code)){    //ILI9320
        lcd_register_write(0x20, x);
        lcd_register_write(0x21, y);
        lcd_register_write(0x22, point);
    }
}

/*!
    \brief      get point GRAM according to the specified position
    \param[in]  x: the row-coordinate
    \param[in]  y: the column-coordinate
    \param[out] none
    \retval     GRAM value of point 
*/
uint16_t lcd_point_get(uint16_t x,uint16_t y)
{
    uint16_t data;
    
    if ((x > LCD_PIXEL_HEIGHT)||(y > LCD_PIXEL_WIDTH)){
        return 0;
    }
    
    lcd_cursor_set(x,y);
    data = lcd_gram_read();

    return  data;
}

/*!
    \brief      set window area
    \param[in]  start_x: the start position of row-coordinate
    \param[in]  start_y: the start position of column-coordinate
    \param[in]  end_x: the end position of row-coordinate
    \param[in]  end_y: the end position of column-coordinate
    \param[out] none
    \retval     none
*/
void lcd_windows_set(uint16_t start_x,uint16_t start_y,uint16_t end_x,uint16_t end_y)
{
    if(0x8989 == device_code){             // SSD1289
        lcd_register_write(0x0044, start_x + (end_x<<8));
        lcd_register_write(0x0045, start_y);
        lcd_register_write(0x0046, end_y);
        
        lcd_cursor_set(start_x, start_y);
        lcd_gram_write_prepare();
    }else if((0x9320 == device_code) || (0x9300 == device_code)){    //ILI9320
        lcd_register_write(0x0050, start_x);
        lcd_register_write(0x0052, start_y);
        lcd_register_write(0x0051, end_x);
        lcd_register_write(0x0053, end_y);

        lcd_cursor_set(start_x, start_y);
        lcd_gram_write_prepare();
    }
}

/*!
    \brief      draw a horizontal line on LCD screen
    \param[in]  x: the row-coordinate
    \param[in]  start_y: the start column-coordinate
    \param[in]  end_y: the end column-coordinate
    \param[in]  color: specified color of the point
    \param[in]  width: line width
    \param[out] none
    \retval     none
*/

void lcd_hline_draw(uint16_t x,uint16_t start_y,uint16_t end_y,uint16_t color,uint16_t width)
{
    uint16_t i, y;

    for (i = 0; i < width; i++) {
        uint16_t sx = x + i;

        for (y = start_y; y < end_y; y++) {
            lcd_point_set(sx, y, color);
        }
    }
}

/*!
    \brief      draw a vertical line on LCD screen
    \param[in]  start_x: the start column-coordinate
    \param[in]  end_x: the end column-coordinate
    \param[in]  y: the row-coordinate
    \param[in]  color: specified color of the point
    \param[in]  width: line width
    \param[out] none
    \retval     none
*/

void lcd_vline_draw(uint16_t start_x,uint16_t end_x,uint16_t y,uint16_t color,uint16_t width)
{
    uint16_t i, x;

    for (i = 0; i < width; i++) {
        uint16_t sy = y + i;

        for (x = start_x; x < end_x; x++) {
            lcd_point_set(x, sy, color);
        }
    }
}

/*!
    \brief      draw a rectangle according to the specified position and color
    \param[in]  start_x: the start position of row-coordinate
    \param[in]  start_y: the start position of column-coordinate
    \param[in]  end_x: the end position of row-coordinate
    \param[in]  end_y: the end position of column-coordinate
    \param[in]  point: specified color of the point
    \param[out] none
    \retval     none
*/
void lcd_rectangle_draw(uint16_t start_x,uint16_t start_y,uint16_t end_x,uint16_t end_y,uint16_t point)
{
    uint16_t x,y;
    x=start_x;
    y=start_y;
    /* draw four lines */
    for(x=start_x;x<end_x;x++){
        /* draw a point */
        lcd_point_set(x,y,point);
    }
    for(y=start_y;y<end_y;y++){
        lcd_point_set(x,y,point);
    }
    for(x=end_x;x>start_x;x--){
        lcd_point_set(x,y,point);
    }
    for(y=end_y;y>start_y;y--){
        lcd_point_set(x,y,point);
    }
}

/*!
    \brief      fill the specified color to a rectangle
    \param[in]  start_x: the start position of row-coordinate
    \param[in]  start_y: the start position of column-coordinate
    \param[in]  end_x: the end position of row-coordinate
    \param[in]  end_y: the end position of column-coordinate
    \param[in]  color: specified color
    \param[out] none
    \retval     none
*/
void lcd_rectangle_fill(uint16_t start_x,uint16_t start_y,uint16_t end_x,uint16_t end_y,uint16_t color)
{
    uint16_t x, y;
    x = start_x;
    y = start_y;

    for (x = start_x; x < end_x; x++) {
        for (y = start_y; y < end_y; y++) {
            lcd_point_set(x, y, color);
        }
    }
}

/*!
    \brief      draw a picture on LCD screen according to the specified position
    \param[in]  start_x: the start position of row-coordinate
    \param[in]  start_y: the start position of column-coordinate
    \param[in]  end_x: the end position of row-coordinate
    \param[in]  end_y: the end position of column-coordinate
    \param[in]  pic: the picture pointer
    \param[out] none
    \retval     none
*/
void lcd_picture_draw(uint16_t start_x,uint16_t start_y,uint16_t end_x,uint16_t end_y,uint16_t *pic)
{
    uint32_t i, total;
    uint16_t *picturepointer = pic;
    uint16_t x,y;

    x = start_x;
    y = start_y;

    total = (end_x - start_x + 1) * (end_y - start_y + 1);
    
    for(i = 0; i < total; i ++){
        /* set point according to the specified position and color */
        lcd_point_set(x,y,*picturepointer++);
        x++;
        if(x > end_x){
            y++;
            x = start_x;
        }
    }
}

/*!
    \brief      display a char on LCD screen according to the specified position
    \param[in]  x: the start position of row-coordinate
    \param[in]  y: the start position of column-coordinate
    \param[in]  c: the char
    \param[in]  char_color: the color of char
    \param[in]  c_format: the structure of char format
                  font: CHAR_FONT_8_16 or CHAR_FONT_16_24
                  direction: CHAR_DIRECTION_HORIZONTAL or CHAR_DIRECTION_VERTICAL
                  char_color: the color of char
                  bk_color: the color of background
    \param[out] none
    \retval     none
*/
void lcd_char_display(uint16_t x,uint16_t y,uint8_t c,char_format_struct c_format)
{
    uint16_t i = 0, j = 0;
    uint8_t temp_char = 0;
    uint16_t temp_char_16 = 0;
    
    if(CHAR_FONT_8_16 == c_format.font){ /* 8x16 ASCII */
        for (i = 0; i < 16; i++) {
            temp_char = ascii_8x16[((c - 0x20) * 16) + i];
            if(CHAR_DIRECTION_HORIZONTAL == c_format.direction){
                for (j = 0; j < 8; j++) {
                    if (((temp_char >> (7 - j)) & 0x01) == 0x01) {
                        /* set point of char */
                        lcd_point_set(x - i, y + j, c_format.char_color);
                    } else {
                        /* set point of background */
                        lcd_point_set(x - i, y + j, c_format.bk_color);
                    }
                }
            }else{
                for (j = 0; j < 8; j++) {
                    if (((temp_char >> (7 - j)) & 0x01) == 0x01) {
                        /* set point of char */
                        lcd_point_set(x + j, y + i, c_format.char_color);
                    } else {
                        /* set point of background */
                        lcd_point_set(x + j, y + i, c_format.bk_color);
                    }
                }
            }
        }
    }else if(CHAR_FONT_16_24 == c_format.font){ /* 16x24 ASCII */
        for (i = 0; i < 24; i++) {
            temp_char_16 = ASCII_Table_16x24[((c - 0x20) * 24) + i];
            if(CHAR_DIRECTION_HORIZONTAL == c_format.direction){
                for (j = 0; j < 16; j++) {
                    if (((temp_char_16 >> j) & 0x01) == 0x01) {
                        /* set point of char */
                        lcd_point_set(x - i, y + j, c_format.char_color);
                    } else {
                        /* set point of background */
                        lcd_point_set(x - i, y + j, c_format.bk_color);
                    }
                }
            }else{
                for (j = 0; j < 16; j++) {
                    if (((temp_char_16 >> j) & 0x01) == 0x01) {
                        /* set point of char */
                        lcd_point_set(x + j, y + i, c_format.char_color);
                    } else {
                        /* set point of background */
                        lcd_point_set(x + j, y + i, c_format.bk_color);
                    }
                }
            }
        }
    }
}
