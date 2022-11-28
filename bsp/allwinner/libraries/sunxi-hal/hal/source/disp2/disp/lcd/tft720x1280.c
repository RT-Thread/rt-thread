/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include "tft720x1280.h"

static void LCD_power_on(u32 sel);
static void LCD_power_off(u32 sel);
static void LCD_bl_open(u32 sel);
static void LCD_bl_close(u32 sel);

static void LCD_panel_init(u32 sel);
static void LCD_panel_exit(u32 sel);

#define dsi_dcs_wr_0para sunxi_lcd_dsi_dcs_write_0para
#define dsi_dcs_wr_1para sunxi_lcd_dsi_dcs_write_1para
#define dsi_dcs_wr_2para sunxi_lcd_dsi_dcs_write_2para
#define dsi_dcs_wr_3para sunxi_lcd_dsi_dcs_write_3para
#define dsi_dcs_wr_4para sunxi_lcd_dsi_dcs_write_4para
#define dsi_dcs_wr_5para sunxi_lcd_dsi_dcs_write_5para
#define delayms sunxi_lcd_delay_ms

static void tft7201280_init(__u32 sel, __u32 mode, __u32 lane, __u32 format)
{
    __u8 const mipi_dcs_pixel_format[2][4] = {
        {0x70, 0x60, 0x60, 0x50}, {0x07, 0x06, 0x05, 0x07}
    };

    dsi_dcs_wr_2para(sel, 0xb9, 0x01, 0x00);
    dsi_dcs_wr_2para(sel, 0xb7, 0x02, 0x03);
    dsi_dcs_wr_2para(sel, 0xb8, 0x10, 0x00);

    dsi_dcs_wr_1para(sel, 0xff, 0xee);
    dsi_dcs_wr_1para(sel, 0x26, 0x08);

    delayms(20);        /* Wait more than 1ms */

    dsi_dcs_wr_1para(sel, 0x26, 0x00);

    dsi_dcs_wr_1para(sel, 0xff, 0x00);

    delayms(70);        /* Wait more than 10ms */

    dsi_dcs_wr_1para(sel, 0xba, lane - 1);  /* MIPI lane number */

    if (mode == 1)
        /* Setting 0x08 for MIPI command mode */
        dsi_dcs_wr_1para(sel, 0xc2, 0x08);
    else
        /* Setting 0x03 for MIPI video mode */
        dsi_dcs_wr_1para(sel, 0xc2, 0x03);

    dsi_dcs_wr_1para(sel, DSI_DCS_SET_TEAR_ON, 0x00); /* tear effect */

    dsi_dcs_wr_1para(sel, 0xFF, 0x01);  /* CMD page select */
    dsi_dcs_wr_1para(sel, 0xFB, 0x01);  /* RELOAD CMD1 */
    dsi_dcs_wr_1para(sel, 0x00, 0x4A);
    dsi_dcs_wr_1para(sel, 0x01, 0x33);
    dsi_dcs_wr_1para(sel, 0x02, 0x53);
    dsi_dcs_wr_1para(sel, 0x03, 0x55);
    dsi_dcs_wr_1para(sel, 0x04, 0x55);
    dsi_dcs_wr_1para(sel, 0x05, 0x33);
    dsi_dcs_wr_1para(sel, 0x06, 0x22);
    dsi_dcs_wr_1para(sel, 0x08, 0x56);
    dsi_dcs_wr_1para(sel, 0x09, 0x8F);
    dsi_dcs_wr_1para(sel, 0x36, 0x73);
    dsi_dcs_wr_1para(sel, 0x0B, 0x9F);
    dsi_dcs_wr_1para(sel, 0x0C, 0x9F);
    dsi_dcs_wr_1para(sel, 0x0D, 0x2F);
    dsi_dcs_wr_1para(sel, 0x0E, 0x24);
    /* VCOM DC,no need to issue for OTP LCM */
    dsi_dcs_wr_1para(sel, 0x11, 0x83);
    dsi_dcs_wr_1para(sel, 0x12, 0x03);
    dsi_dcs_wr_1para(sel, 0x71, 0x2C);
    dsi_dcs_wr_1para(sel, 0x6F, 0x03);
    dsi_dcs_wr_1para(sel, 0x0F, 0x0A);

    dsi_dcs_wr_1para(sel, 0xFF, 0x05);  /* CMD page select */
    dsi_dcs_wr_1para(sel, 0xFB, 0x01);  /* RELOAD CMD1 */
    dsi_dcs_wr_1para(sel, 0x01, 0x00);
    dsi_dcs_wr_1para(sel, 0x02, 0x82);
    dsi_dcs_wr_1para(sel, 0x03, 0x82);
    dsi_dcs_wr_1para(sel, 0x04, 0x82);
    dsi_dcs_wr_1para(sel, 0x05, 0x30);
    dsi_dcs_wr_1para(sel, 0x06, 0x33);
    dsi_dcs_wr_1para(sel, 0x07, 0x01);
    dsi_dcs_wr_1para(sel, 0x08, 0x00);
    dsi_dcs_wr_1para(sel, 0x09, 0x46);
    dsi_dcs_wr_1para(sel, 0x0A, 0x46);
    dsi_dcs_wr_1para(sel, 0x0D, 0x0B);
    dsi_dcs_wr_1para(sel, 0x0E, 0x1D);
    dsi_dcs_wr_1para(sel, 0x0F, 0x08);
    dsi_dcs_wr_1para(sel, 0x10, 0x53);
    dsi_dcs_wr_1para(sel, 0x11, 0x00);
    dsi_dcs_wr_1para(sel, 0x12, 0x00);
    dsi_dcs_wr_1para(sel, 0x14, 0x01);
    dsi_dcs_wr_1para(sel, 0x15, 0x00);
    dsi_dcs_wr_1para(sel, 0x16, 0x05);
    dsi_dcs_wr_1para(sel, 0x17, 0x00);
    dsi_dcs_wr_1para(sel, 0x19, 0x7F);
    dsi_dcs_wr_1para(sel, 0x1A, 0xFF);
    dsi_dcs_wr_1para(sel, 0x1B, 0x0F);
    dsi_dcs_wr_1para(sel, 0x1C, 0x00);
    dsi_dcs_wr_1para(sel, 0x1D, 0x00);
    dsi_dcs_wr_1para(sel, 0x1E, 0x00);
    dsi_dcs_wr_1para(sel, 0x1F, 0x07);
    dsi_dcs_wr_1para(sel, 0x20, 0x00);
    dsi_dcs_wr_1para(sel, 0x21, 0x00);
    dsi_dcs_wr_1para(sel, 0x22, 0x55);
    dsi_dcs_wr_1para(sel, 0x23, 0x4D);
    dsi_dcs_wr_1para(sel, 0x2D, 0x02);
    dsi_dcs_wr_1para(sel, 0x28, 0x01);
    dsi_dcs_wr_1para(sel, 0x2F, 0x02);
    dsi_dcs_wr_1para(sel, 0x83, 0x01);
    dsi_dcs_wr_1para(sel, 0x9E, 0x58);
    dsi_dcs_wr_1para(sel, 0x9F, 0x6A);
    dsi_dcs_wr_1para(sel, 0xA0, 0x01);
    dsi_dcs_wr_1para(sel, 0xA2, 0x10);
    dsi_dcs_wr_1para(sel, 0xBB, 0x0A);
    dsi_dcs_wr_1para(sel, 0xBC, 0x0A);
    dsi_dcs_wr_1para(sel, 0x32, 0x08);
    dsi_dcs_wr_1para(sel, 0x33, 0xB8);
    dsi_dcs_wr_1para(sel, 0x36, 0x01);
    dsi_dcs_wr_1para(sel, 0x37, 0x00);
    dsi_dcs_wr_1para(sel, 0x43, 0x00);
    dsi_dcs_wr_1para(sel, 0x4B, 0x21);
    dsi_dcs_wr_1para(sel, 0x4C, 0x03);
    dsi_dcs_wr_1para(sel, 0x50, 0x21);
    dsi_dcs_wr_1para(sel, 0x51, 0x03);
    dsi_dcs_wr_1para(sel, 0x58, 0x21);
    dsi_dcs_wr_1para(sel, 0x59, 0x03);
    dsi_dcs_wr_1para(sel, 0x5D, 0x21);
    dsi_dcs_wr_1para(sel, 0x5E, 0x03);
    dsi_dcs_wr_1para(sel, 0x6C, 0x00);
    dsi_dcs_wr_1para(sel, 0x6D, 0x00);

    /* Lcd_Gamma_Setting();//AUO 4.66''+NT35590 GAMMA2.2 */

    dsi_dcs_wr_1para(sel, 0xFF, 0x01);

    dsi_dcs_wr_1para(sel, 0xFB, 0x01);

    dsi_dcs_wr_1para(sel, 0xFF, 0x02);

    dsi_dcs_wr_1para(sel, 0xFB, 0x01);

    dsi_dcs_wr_1para(sel, 0xFF, 0x04);

    dsi_dcs_wr_1para(sel, 0xFB, 0x01);

    dsi_dcs_wr_1para(sel, 0xFF, 0x00);

    dsi_dcs_wr_0para(sel, 0x11);    /* Sleep out */
    delayms(700);       /* Wait more than 100ms */

    dsi_dcs_wr_1para(sel, 0xFF, 0xEE);

    dsi_dcs_wr_1para(sel, 0x12, 0x50);

    dsi_dcs_wr_1para(sel, 0x13, 0x02);

    dsi_dcs_wr_1para(sel, 0x6A, 0x60);

    dsi_dcs_wr_1para(sel, 0xFF, 0x00);

/* dsi_dcs_wr_1para(sel,0x36,0xb0);        //dlp */
/* dsi_dcs_wr_1para(sel,0xc2,0x08);//Setting 0x08 for MIPI command mode */
/* dsi_dcs_wr_4para(sel,0x2a,0x00,0x00,0x02,0xcf); //dlp */
/* dsi_dcs_wr_4para(sel,0x2b,0x00,0x00,0x04,0xff); //dlp */
/* dsi_dcs_wr_4para(sel,0x30,0x00,0x00,0x01,0xff); //dlp */
    dsi_dcs_wr_5para(sel, 0x3b, 0x23, 0x05, 0x05, 0x0c, 0x20);

    dsi_dcs_wr_1para(sel, 0x3a, mipi_dcs_pixel_format[mode][format]);

    dsi_dcs_wr_0para(sel, 0x29);    /* Display on */
    delayms(300);       /* Wait more than 40ms */

/* dsi_trnd(0); */

/* AUO Initial Code 2012.06.28 */
/* Setting for Gamma+ R */
    dsi_dcs_wr_1para(sel, 0xFB, 0x01);
    dsi_dcs_wr_1para(sel, 0xFF, 0x01);  /* Enter CMD2,Page0 */
    dsi_dcs_wr_1para(sel, 0xFB, 0x01);

    dsi_dcs_wr_1para(sel, 0x75, 0x00);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x76, 0x7D);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x77, 0x00);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x78, 0x8A);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x79, 0x00);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x7A, 0x9C);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x7B, 0x00);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x7C, 0xB1);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x7D, 0x00);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x7E, 0xBF);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x7F, 0x00);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x80, 0xCF);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x81, 0x00);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x82, 0xDD);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x83, 0x00);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x84, 0xE8);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x85, 0x00);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x86, 0xF2);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x87, 0x01);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x88, 0x1F);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x89, 0x01);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x8A, 0x41);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x8B, 0x01);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x8C, 0x78);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x8D, 0x01);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x8E, 0xA5);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x8F, 0x01);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x90, 0xEE);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x91, 0x02);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x92, 0x29);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x93, 0x02);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x94, 0x2A);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x95, 0x02);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x96, 0x5D);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x97, 0x02);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x98, 0x93);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x99, 0x02);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x9A, 0xB8);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x9B, 0x02);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x9C, 0xE7);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x9D, 0x03);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x9E, 0x07);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0x9F, 0x03);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0xA0, 0x37);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0xA2, 0x03);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0xA3, 0x46);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0xA4, 0x03);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0xA5, 0x56);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0xA6, 0x03);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0xA7, 0x66);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0xA9, 0x03);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0xAA, 0x7A);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0xAB, 0x03);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0xAC, 0x93);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0xAD, 0x03);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0xAE, 0xA3);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0xAF, 0x03);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0xB0, 0xB4);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0xB1, 0x03);  /* Gamma+ R */
    dsi_dcs_wr_1para(sel, 0xB2, 0xCB);  /* Gamma+ R */

    /* Setting for Gamma- R */

    dsi_dcs_wr_1para(sel, 0xB3, 0x00);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xB4, 0x7D);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xB5, 0x00);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xB6, 0x8A);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xB7, 0x00);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xB8, 0x9C);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xB9, 0x00);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xBA, 0xB1);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xBB, 0x00);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xBC, 0xBF);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xBD, 0x00);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xBE, 0xCF);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xBF, 0x00);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xC0, 0xDD);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xC1, 0x00);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xC2, 0xE8);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xC3, 0x00);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xC4, 0xF2);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xC5, 0x01);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xC6, 0x1F);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xC7, 0x01);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xC8, 0x41);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xC9, 0x01);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xCA, 0x78);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xCB, 0x01);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xCC, 0xA5);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xCD, 0x01);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xCE, 0xEE);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xCF, 0x02);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xD0, 0x29);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xD1, 0x02);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xD2, 0x2A);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xD3, 0x02);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xD4, 0x5D);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xD5, 0x02);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xD6, 0x93);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xD7, 0x02);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xD8, 0xB8);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xD9, 0x02);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xDA, 0xE7);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xDB, 0x03);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xDC, 0x07);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xDD, 0x03);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xDE, 0x37);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xDF, 0x03);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xE0, 0x46);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xE1, 0x03);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xE2, 0x56);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xE3, 0x03);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xE4, 0x66);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xE5, 0x03);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xE6, 0x7A);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xE7, 0x03);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xE8, 0x93);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xE9, 0x03);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xEA, 0xA3);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xEB, 0x03);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xEC, 0xB4);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xED, 0x03);  /* Gamma- R */
    dsi_dcs_wr_1para(sel, 0xEE, 0xCB);  /* Gamma- R */

    /* Setting for Gamma+ G */

    dsi_dcs_wr_1para(sel, 0xEF, 0x00);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0xF0, 0xED);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0xF1, 0x00);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0xF2, 0xF3);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0xF3, 0x00);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0xF4, 0xFE);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0xF5, 0x01);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0xF6, 0x09);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0xF7, 0x01);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0xF8, 0x13);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0xF9, 0x01);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0xFA, 0x1D);  /* Gamma+ G */

    dsi_dcs_wr_1para(sel, 0xFF, 0x02);  /* Enter CMD */
    dsi_dcs_wr_1para(sel, 0xFB, 0x01);

    dsi_dcs_wr_1para(sel, 0x00, 0x01);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x01, 0x26);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x02, 0x01);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x03, 0x2F);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x04, 0x01);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x05, 0x37);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x06, 0x01);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x07, 0x56);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x08, 0x01);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x09, 0x70);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x0A, 0x01);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x0B, 0x9D);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x0C, 0x01);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x0D, 0xC2);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x0E, 0x01);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x0F, 0xFF);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x10, 0x02);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x11, 0x31);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x12, 0x02);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x13, 0x32);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x14, 0x02);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x15, 0x60);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x16, 0x02);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x17, 0x94);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x18, 0x02);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x19, 0xB5);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x1A, 0x02);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x1B, 0xE3);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x1C, 0x03);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x1D, 0x03);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x1E, 0x03);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x1F, 0x2D);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x20, 0x03);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x21, 0x3A);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x22, 0x03);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x23, 0x48);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x24, 0x03);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x25, 0x57);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x26, 0x03);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x27, 0x68);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x28, 0x03);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x29, 0x7B);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x2A, 0x03);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x2B, 0x90);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x2D, 0x03);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x2F, 0xA0);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x30, 0x03);  /* Gamma+ G */
    dsi_dcs_wr_1para(sel, 0x31, 0xCB);  /* Gamma+ G */

    /* Setting for Gamma- G */

    dsi_dcs_wr_1para(sel, 0x32, 0x00);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x33, 0xED);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x34, 0x00);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x35, 0xF3);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x36, 0x00);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x37, 0xFE);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x38, 0x01);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x39, 0x09);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x3A, 0x01);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x3B, 0x13);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x3D, 0x01);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x3F, 0x1D);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x40, 0x01);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x41, 0x26);  /* Gamma- G 2 */
    dsi_dcs_wr_1para(sel, 0x42, 0x01);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x43, 0x2F);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x44, 0x01);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x45, 0x37);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x46, 0x01);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x47, 0x56);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x48, 0x01);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x49, 0x70);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x4A, 0x01);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x4B, 0x9D);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x4C, 0x01);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x4D, 0xC2);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x4E, 0x01);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x4F, 0xFF);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x50, 0x02);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x51, 0x31);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x52, 0x02);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x53, 0x32);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x54, 0x02);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x55, 0x60);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x56, 0x02);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x58, 0x94);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x59, 0x02);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x5A, 0xB5);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x5B, 0x02);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x5C, 0xE3);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x5D, 0x03);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x5E, 0x03);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x5F, 0x03);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x60, 0x2D);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x61, 0x03);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x62, 0x3A);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x63, 0x03);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x64, 0x48);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x65, 0x03);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x66, 0x57);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x67, 0x03);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x68, 0x68);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x69, 0x03);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x6A, 0x7B);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x6B, 0x03);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x6C, 0x90);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x6D, 0x03);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x6E, 0xA0);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x6F, 0x03);  /* Gamma- G */
    dsi_dcs_wr_1para(sel, 0x70, 0xCB);  /* Gamma- G */

    /* Setting for Gamma+ B */

    dsi_dcs_wr_1para(sel, 0x71, 0x00);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x72, 0x19);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x73, 0x00);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x74, 0x36);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x75, 0x00);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x76, 0x55);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x77, 0x00);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x78, 0x70);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x79, 0x00);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x7A, 0x83);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x7B, 0x00);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x7C, 0x99);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x7D, 0x00);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x7E, 0xA8);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x7F, 0x00);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x80, 0xB7);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x81, 0x00);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x82, 0xC5);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x83, 0x00);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x84, 0xF7);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x85, 0x01);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x86, 0x1E);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x87, 0x01);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x88, 0x60);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x89, 0x01);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x8A, 0x95);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x8B, 0x01);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x8C, 0xE1);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x8D, 0x02);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x8E, 0x20);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x8F, 0x02);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x90, 0x23);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x91, 0x02);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x92, 0x59);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x93, 0x02);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x94, 0x94);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x95, 0x02);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x96, 0xB4);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x97, 0x02);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x98, 0xE1);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x99, 0x03);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x9A, 0x01);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x9B, 0x03);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x9C, 0x28);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x9D, 0x03);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x9E, 0x30);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0x9F, 0x03);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0xA0, 0x37);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0xA2, 0x03);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0xA3, 0x3B);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0xA4, 0x03);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0xA5, 0x40);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0xA6, 0x03);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0xA7, 0x50);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0xA9, 0x03);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0xAA, 0x6D);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0xAB, 0x03);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0xAC, 0x80);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0xAD, 0x03);  /* Gamma+ B */
    dsi_dcs_wr_1para(sel, 0xAE, 0xCB);  /* Gamma+ B */

    /* Setting for Gamma- B */

    dsi_dcs_wr_1para(sel, 0xAF, 0x00);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xB0, 0x19);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xB1, 0x00);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xB2, 0x36);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xB3, 0x00);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xB4, 0x55);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xB5, 0x00);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xB6, 0x70);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xB7, 0x00);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xB8, 0x83);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xB9, 0x00);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xBA, 0x99);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xBB, 0x00);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xBC, 0xA8);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xBD, 0x00);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xBE, 0xB7);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xBF, 0x00);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xC0, 0xC5);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xC1, 0x00);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xC2, 0xF7);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xC3, 0x01);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xC4, 0x1E);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xC5, 0x01);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xC6, 0x60);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xC7, 0x01);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xC8, 0x95);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xC9, 0x01);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xCA, 0xE1);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xCB, 0x02);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xCC, 0x20);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xCD, 0x02);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xCE, 0x23);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xCF, 0x02);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xD0, 0x59);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xD1, 0x02);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xD2, 0x94);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xD3, 0x02);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xD4, 0xB4);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xD5, 0x02);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xD6, 0xE1);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xD7, 0x03);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xD8, 0x01);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xD9, 0x03);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xDA, 0x28);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xDB, 0x03);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xDC, 0x30);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xDD, 0x03);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xDE, 0x37);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xDF, 0x03);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xE0, 0x3B);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xE1, 0x03);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xE2, 0x40);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xE3, 0x03);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xE4, 0x50);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xE5, 0x03);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xE6, 0x6D);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xE7, 0x03);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xE8, 0x80);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xE9, 0x03);  /* Gamma- B */
    dsi_dcs_wr_1para(sel, 0xEA, 0xCB);  /* Gamma- B */
}

static void LCD_cfg_panel_info(struct panel_extend_para *info)
{
    u32 i = 0, j = 0;
    u32 items;
    u8 lcd_gamma_tbl[][2] = {
        /* {input value, corrected value} */
        {0, 0},
        {15, 15},
        {30, 30},
        {45, 45},
        {60, 60},
        {75, 75},
        {90, 90},
        {105, 105},
        {120, 120},
        {135, 135},
        {150, 150},
        {165, 165},
        {180, 180},
        {195, 195},
        {210, 210},
        {225, 225},
        {240, 240},
        {255, 255},
    };

    u32 lcd_cmap_tbl[2][3][4] = {
        {
         {LCD_CMAP_G0, LCD_CMAP_B1, LCD_CMAP_G2, LCD_CMAP_B3},
         {LCD_CMAP_B0, LCD_CMAP_R1, LCD_CMAP_B2, LCD_CMAP_R3},
         {LCD_CMAP_R0, LCD_CMAP_G1, LCD_CMAP_R2, LCD_CMAP_G3},
         },
        {
         {LCD_CMAP_B3, LCD_CMAP_G2, LCD_CMAP_B1, LCD_CMAP_G0},
         {LCD_CMAP_R3, LCD_CMAP_B2, LCD_CMAP_R1, LCD_CMAP_B0},
         {LCD_CMAP_G3, LCD_CMAP_R2, LCD_CMAP_G1, LCD_CMAP_R0},
         },
    };

    items = sizeof(lcd_gamma_tbl) / 2;
    for (i = 0; i < items - 1; i++) {
        u32 num = lcd_gamma_tbl[i + 1][0] - lcd_gamma_tbl[i][0];

        for (j = 0; j < num; j++) {
            u32 value = 0;

            value =
                lcd_gamma_tbl[i][1] +
                ((lcd_gamma_tbl[i + 1][1] -
                  lcd_gamma_tbl[i][1]) * j) / num;
            info->lcd_gamma_tbl[lcd_gamma_tbl[i][0] + j] =
                (value << 16) + (value << 8) + value;
        }
    }
    info->lcd_gamma_tbl[255] =
        (lcd_gamma_tbl[items - 1][1] << 16) +
        (lcd_gamma_tbl[items - 1][1] << 8) + lcd_gamma_tbl[items - 1][1];

    memcpy(info->lcd_cmap_tbl, lcd_cmap_tbl, sizeof(lcd_cmap_tbl));

}

static s32 LCD_open_flow(u32 sel)
{
    /* open lcd power, and delay 50ms */
    LCD_OPEN_FUNC(sel, LCD_power_on, 100);
    /* open lcd power, than delay 200ms */
    LCD_OPEN_FUNC(sel, LCD_panel_init, 500);
    /* open lcd controller, and delay 100ms */
    LCD_OPEN_FUNC(sel, sunxi_lcd_tcon_enable, 50);
    /* open lcd backlight, and delay 0ms */
    LCD_OPEN_FUNC(sel, LCD_bl_open, 0);

    return 0;
}

static s32 LCD_close_flow(u32 sel)
{
    /* close lcd backlight, and delay 0ms */
    LCD_CLOSE_FUNC(sel, LCD_bl_close, 0);
    /* close lcd controller, and delay 0ms */
    LCD_CLOSE_FUNC(sel, sunxi_lcd_tcon_disable, 0);
    /* open lcd power, than delay 200ms */
    LCD_CLOSE_FUNC(sel, LCD_panel_exit, 10);
    /* close lcd power, and delay 500ms */
    LCD_CLOSE_FUNC(sel, LCD_power_off, 100);

    return 0;
}

static void LCD_power_on(u32 sel)
{
    /* config lcd_power pin to open lcd power */
    sunxi_lcd_power_enable(sel, 0);
    sunxi_lcd_pin_cfg(sel, 1);
}

static void LCD_power_off(u32 sel)
{
    sunxi_lcd_pin_cfg(sel, 0);
    /* config lcd_power pin to open lcd power */
    sunxi_lcd_power_disable(sel, 0);
    sunxi_lcd_dsi_clk_disable(sel);
}

static void LCD_bl_open(u32 sel)
{
    /* config lcd_bl_en pin to open lcd backlight */
    sunxi_lcd_backlight_enable(sel);
    sunxi_lcd_pwm_enable(sel);
}

static void LCD_bl_close(u32 sel)
{
    /* config lcd_bl_en pin to close lcd backlight */
    sunxi_lcd_backlight_disable(sel);
}

static void LCD_panel_init(u32 sel)
{
    struct disp_panel_para *panel_info =
        kmalloc(sizeof(struct disp_panel_para), GFP_KERNEL | __GFP_ZERO);

    bsp_disp_get_panel_info(sel, panel_info);

    sunxi_lcd_dsi_clk_enable(sel);
    tft7201280_init(sel, panel_info->lcd_dsi_if, panel_info->lcd_dsi_lane,
            panel_info->lcd_dsi_format);

    disp_sys_free(panel_info);
}

static void LCD_panel_exit(u32 sel)
{
    sunxi_lcd_dsi_dcs_write_0para(sel, DSI_DCS_SET_DISPLAY_OFF);
    sunxi_lcd_delay_ms(50);
    sunxi_lcd_dsi_dcs_write_0para(sel, DSI_DCS_ENTER_SLEEP_MODE);
    sunxi_lcd_delay_ms(20);
}

/* sel: 0:lcd0; 1:lcd1 */
static s32 LCD_user_defined_func(u32 sel, u32 para1, u32 para2, u32 para3)
{
    return 0;
}

struct __lcd_panel tft720x1280_panel = {
    /* panel driver name, must mach the lcd_drv_name in sys_config.fex */
    .name = "tft720x1280",
    .func = {
         .cfg_panel_info = LCD_cfg_panel_info,
         .cfg_open_flow = LCD_open_flow,
         .cfg_close_flow = LCD_close_flow,
         .lcd_user_defined_func = LCD_user_defined_func,
         }
    ,
};
