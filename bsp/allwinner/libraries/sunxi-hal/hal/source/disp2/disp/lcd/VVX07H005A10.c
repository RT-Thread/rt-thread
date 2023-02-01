/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include "VVX07H005A10.h"
#include "../disp_sys_intf.h"

static void LCD_power_on(u32 sel);
static void LCD_power_off(u32 sel);
static void LCD_bl_open(u32 sel);
static void LCD_bl_close(u32 sel);

static void LCD_panel_init(u32 sel);
static void LCD_panel_exit(u32 sel);
static __s32 LCD_user_defined_func(__u32 sel, __u32 para1, __u32 para2, __u32 para3);

// #define LCD_DEBUG
#ifdef LCD_DEBUG
#define DEBUG(fmt, args...) printf("[DEBUG] %s, %s, %d " fmt "\n", __FILE__, __func__, __LINE__, ## args)
#else
#define DEBUG(fmt, args...)
#endif

#define dsi_dcs_wr_0para sunxi_lcd_dsi_dcs_write_0para
#define dsi_dcs_wr_1para sunxi_lcd_dsi_dcs_write_1para
#define dsi_dcs_wr_2para sunxi_lcd_dsi_dcs_write_2para
#define dsi_dcs_wr_3para sunxi_lcd_dsi_dcs_write_3para
#define dsi_dcs_wr_4para sunxi_lcd_dsi_dcs_write_4para
#define dsi_dcs_wr_5para sunxi_lcd_dsi_dcs_write_5para
#define dsi_dcs_wr_6para sunxi_lcd_dsi_dcs_write_6para
#define dsi_dcs_wr_longpara sunxi_lcd_dsi_dcs_write
#define delayms sunxi_lcd_delay_ms

static void tft7201280_init(__u32 sel, __u32 mode, __u32 lane, __u32 format)
{
    //-----------------------Initial  Code--------------------------------------//
    //Page0
    dsi_dcs_wr_1para(sel,0xE0,0x00);

    //--- PASSWORD  ----//
    dsi_dcs_wr_1para(sel,0xE1,0x93);
    dsi_dcs_wr_1para(sel,0xE2,0x65);
    dsi_dcs_wr_1para(sel,0xE3,0xF8);
    dsi_dcs_wr_1para(sel,0x80,0x03);



    //--- Page1  ----//
    dsi_dcs_wr_1para(sel,0xE0,0x01);

    //Set VCOM
    dsi_dcs_wr_1para(sel,0x01,0x67);

    //Set Gamma Power, VGMP,VGMN,VGSP,VGSN
    dsi_dcs_wr_1para(sel,0x17,0x00);
    dsi_dcs_wr_1para(sel,0x18,0xBF);//4.5V, D7=4.8V
    dsi_dcs_wr_1para(sel,0x19,0x01);//0.0V
    dsi_dcs_wr_1para(sel,0x1A,0x00);
    dsi_dcs_wr_1para(sel,0x1B,0xBF);
    dsi_dcs_wr_1para(sel,0x1C,0x01);
    dsi_dcs_wr_1para(sel,0x0C,0x74);

    //Set Gate Power
    dsi_dcs_wr_1para(sel,0x1F,0x70);    //VGH_REG=16.2V
    dsi_dcs_wr_1para(sel,0x20,0x2D);    //VGL_REG=-12V
    dsi_dcs_wr_1para(sel,0x21,0x2D);    //VGL_REG2=-12V
    dsi_dcs_wr_1para(sel,0x22,0x7E);
    dsi_dcs_wr_1para(sel,0x0C,0x74);


    dsi_dcs_wr_1para(sel,0x35,0x28);    //SAP

    dsi_dcs_wr_1para(sel,0x37,0x19);    //SS=1,BGR=1

    //SET RGBCYC
    dsi_dcs_wr_1para(sel,0x38,0x05);    //JDT=101 zigzag inversion
    dsi_dcs_wr_1para(sel,0x39,0x00);
    dsi_dcs_wr_1para(sel,0x3A,0x01);
    dsi_dcs_wr_1para(sel,0x3C,0x7C);    //SET EQ3 for TE_H
    dsi_dcs_wr_1para(sel,0x3D,0xFF);    //SET CHGEN_ON, modify 20140806
    dsi_dcs_wr_1para(sel,0x3E,0xFF);    //SET CHGEN_OFF, modify 20140806
    dsi_dcs_wr_1para(sel,0x3F,0x7F);    //SET CHGEN_OFF2, modify 20140806


    //Set TCON
    dsi_dcs_wr_1para(sel,0x40,0x06);    //RSO=
    dsi_dcs_wr_1para(sel,0x41,0xA0);    //LN=640->1280 line
    dsi_dcs_wr_1para(sel,0x43,0x1E);    //VFP=30
    dsi_dcs_wr_1para(sel,0x44,0x0B);    //VBP=12
    dsi_dcs_wr_1para(sel,0x45,0x28);  //HBP=40

    //--- power voltage  ----//
    dsi_dcs_wr_1para(sel,0x55,0x01);
    dsi_dcs_wr_1para(sel,0x57,0xA9);
    //dsi_dcs_wr_1para(sel,0x58,0x0A);
    dsi_dcs_wr_1para(sel,0x59,0x0A);    //VCL = -2.5V
    dsi_dcs_wr_1para(sel,0x5A,0x2E);    //VGH = 16.2V
    dsi_dcs_wr_1para(sel,0x5B,0x1A);    //VGL = -12V
    dsi_dcs_wr_1para(sel,0x5C,0x15);    //pump clk


    //--- Gamma  ----//
    dsi_dcs_wr_1para(sel,0x5D,0x7F);
    dsi_dcs_wr_1para(sel,0x5E,0x64);
    dsi_dcs_wr_1para(sel,0x5F,0x53);
    dsi_dcs_wr_1para(sel,0x60,0x47);
    dsi_dcs_wr_1para(sel,0x61,0x43);
    dsi_dcs_wr_1para(sel,0x62,0x33);
    dsi_dcs_wr_1para(sel,0x63,0x37);
    dsi_dcs_wr_1para(sel,0x64,0x21);
    dsi_dcs_wr_1para(sel,0x65,0x39);
    dsi_dcs_wr_1para(sel,0x66,0x37);
    dsi_dcs_wr_1para(sel,0x67,0x34);
    dsi_dcs_wr_1para(sel,0x68,0x50);
    dsi_dcs_wr_1para(sel,0x69,0x3D);
    dsi_dcs_wr_1para(sel,0x6A,0x44);
    dsi_dcs_wr_1para(sel,0x6B,0x36);
    dsi_dcs_wr_1para(sel,0x6C,0x34);
    dsi_dcs_wr_1para(sel,0x6D,0x25);
    dsi_dcs_wr_1para(sel,0x6E,0x15);
    dsi_dcs_wr_1para(sel,0x6F,0x02);
    dsi_dcs_wr_1para(sel,0x70,0x7F);
    dsi_dcs_wr_1para(sel,0x71,0x64);
    dsi_dcs_wr_1para(sel,0x72,0x53);
    dsi_dcs_wr_1para(sel,0x73,0x47);
    dsi_dcs_wr_1para(sel,0x74,0x43);
    dsi_dcs_wr_1para(sel,0x75,0x33);
    dsi_dcs_wr_1para(sel,0x76,0x37);
    dsi_dcs_wr_1para(sel,0x77,0x21);
    dsi_dcs_wr_1para(sel,0x78,0x39);
    dsi_dcs_wr_1para(sel,0x79,0x37);
    dsi_dcs_wr_1para(sel,0x7A,0x34);
    dsi_dcs_wr_1para(sel,0x7B,0x50);
    dsi_dcs_wr_1para(sel,0x7C,0x3D);
    dsi_dcs_wr_1para(sel,0x7D,0x44);
    dsi_dcs_wr_1para(sel,0x7E,0x36);
    dsi_dcs_wr_1para(sel,0x7F,0x34);
    dsi_dcs_wr_1para(sel,0x80,0x25);
    dsi_dcs_wr_1para(sel,0x81,0x15);
    dsi_dcs_wr_1para(sel,0x82,0x02);


    //Page2, for GIP
    dsi_dcs_wr_1para(sel,0xE0,0x02);

    //GIP_L Pin mapping
    dsi_dcs_wr_1para(sel,0x00,0x52);//RESET_EVEN
    dsi_dcs_wr_1para(sel,0x01,0x55);//VSSG_EVEN
    dsi_dcs_wr_1para(sel,0x02,0x55);//VSSG_EVEN
    dsi_dcs_wr_1para(sel,0x03,0x50);//STV2_ODD
    dsi_dcs_wr_1para(sel,0x04,0x77);//VDD2_ODD
    dsi_dcs_wr_1para(sel,0x05,0x57);//VDD1_ODD
    dsi_dcs_wr_1para(sel,0x06,0x55);//x
    dsi_dcs_wr_1para(sel,0x07,0x4E);//CK11
    dsi_dcs_wr_1para(sel,0x08,0x4C);//CK9
    dsi_dcs_wr_1para(sel,0x09,0x5F);//x
    dsi_dcs_wr_1para(sel,0x0A,0x4A);//CK7
    dsi_dcs_wr_1para(sel,0x0B,0x48);//CK5
    dsi_dcs_wr_1para(sel,0x0C,0x55);//x
    dsi_dcs_wr_1para(sel,0x0D,0x46);//CK3
    dsi_dcs_wr_1para(sel,0x0E,0x44);//CK1
    dsi_dcs_wr_1para(sel,0x0F,0x40);//STV1_ODD
    dsi_dcs_wr_1para(sel,0x10,0x55);//x
    dsi_dcs_wr_1para(sel,0x11,0x55);//x
    dsi_dcs_wr_1para(sel,0x12,0x55);//x
    dsi_dcs_wr_1para(sel,0x13,0x55);//x
    dsi_dcs_wr_1para(sel,0x14,0x55);//x
    dsi_dcs_wr_1para(sel,0x15,0x55);//x

    //GIP_R Pin mapping
    dsi_dcs_wr_1para(sel,0x16,0x53);//RESET__EVEN
    dsi_dcs_wr_1para(sel,0x17,0x55);//VSSG_EVEN
    dsi_dcs_wr_1para(sel,0x18,0x55);//VSSG_EVEN
    dsi_dcs_wr_1para(sel,0x19,0x51);//STV2_EVEN
    dsi_dcs_wr_1para(sel,0x1A,0x77);//VDD2_EVEN
    dsi_dcs_wr_1para(sel,0x1B,0x57);//VDD1_EVEN
    dsi_dcs_wr_1para(sel,0x1C,0x55);//x
    dsi_dcs_wr_1para(sel,0x1D,0x4F);//CK12
    dsi_dcs_wr_1para(sel,0x1E,0x4D);//CK10
    dsi_dcs_wr_1para(sel,0x1F,0x5F);//x
    dsi_dcs_wr_1para(sel,0x20,0x4B);//CK8
    dsi_dcs_wr_1para(sel,0x21,0x49);//CK6
    dsi_dcs_wr_1para(sel,0x22,0x55);//x
    dsi_dcs_wr_1para(sel,0x23,0x47);//CK4
    dsi_dcs_wr_1para(sel,0x24,0x45);//CK2
    dsi_dcs_wr_1para(sel,0x25,0x41);//STV1_EVEN
    dsi_dcs_wr_1para(sel,0x26,0x55);//x
    dsi_dcs_wr_1para(sel,0x27,0x55);//x
    dsi_dcs_wr_1para(sel,0x28,0x55);//x
    dsi_dcs_wr_1para(sel,0x29,0x55);//x
    dsi_dcs_wr_1para(sel,0x2A,0x55);//x
    dsi_dcs_wr_1para(sel,0x2B,0x55);//x

    //GIP_L_GS Pin mapping
    dsi_dcs_wr_1para(sel,0x2C,0x13);//RESET_EVEN
    dsi_dcs_wr_1para(sel,0x2D,0x15);//VSSG_EVEN
    dsi_dcs_wr_1para(sel,0x2E,0x15);//VSSG_EVEN
    dsi_dcs_wr_1para(sel,0x2F,0x01);//STV2_ODD
    dsi_dcs_wr_1para(sel,0x30,0x37);//VDD2_ODD
    dsi_dcs_wr_1para(sel,0x31,0x17);//VDD1_ODD
    dsi_dcs_wr_1para(sel,0x32,0x15);//x
    dsi_dcs_wr_1para(sel,0x33,0x0D);//CK11
    dsi_dcs_wr_1para(sel,0x34,0x0F);//CK9
    dsi_dcs_wr_1para(sel,0x35,0x15);//x
    dsi_dcs_wr_1para(sel,0x36,0x05);//CK7
    dsi_dcs_wr_1para(sel,0x37,0x07);//CK5
    dsi_dcs_wr_1para(sel,0x38,0x15);//x
    dsi_dcs_wr_1para(sel,0x39,0x09);//CK3
    dsi_dcs_wr_1para(sel,0x3A,0x0B);//CK1
    dsi_dcs_wr_1para(sel,0x3B,0x11);//STV1_ODD
    dsi_dcs_wr_1para(sel,0x3C,0x15);//x
    dsi_dcs_wr_1para(sel,0x3D,0x15);//x
    dsi_dcs_wr_1para(sel,0x3E,0x15);//x
    dsi_dcs_wr_1para(sel,0x3F,0x15);//x
    dsi_dcs_wr_1para(sel,0x40,0x15);//x
    dsi_dcs_wr_1para(sel,0x41,0x15);//x

    //GIP_R_GS Pin mapping
    dsi_dcs_wr_1para(sel,0x42,0x12);//RESET__EVEN
    dsi_dcs_wr_1para(sel,0x43,0x15);//VSSG_EVEN
    dsi_dcs_wr_1para(sel,0x44,0x15);//VSSG_EVEN
    dsi_dcs_wr_1para(sel,0x45,0x00);//STV2_EVEN
    dsi_dcs_wr_1para(sel,0x46,0x37);//VDD2_EVEN
    dsi_dcs_wr_1para(sel,0x47,0x17);//VDD1_EVEN
    dsi_dcs_wr_1para(sel,0x48,0x15);//x
    dsi_dcs_wr_1para(sel,0x49,0x0C);//CK12
    dsi_dcs_wr_1para(sel,0x4A,0x0E);//CK10
    dsi_dcs_wr_1para(sel,0x4B,0x15);//x
    dsi_dcs_wr_1para(sel,0x4C,0x04);//CK8
    dsi_dcs_wr_1para(sel,0x4D,0x06);//CK6
    dsi_dcs_wr_1para(sel,0x4E,0x15);//x
    dsi_dcs_wr_1para(sel,0x4F,0x08);//CK4
    dsi_dcs_wr_1para(sel,0x50,0x0A);//CK2
    dsi_dcs_wr_1para(sel,0x51,0x10);//STV1_EVEN
    dsi_dcs_wr_1para(sel,0x52,0x15);//x
    dsi_dcs_wr_1para(sel,0x53,0x15);//x
    dsi_dcs_wr_1para(sel,0x54,0x15);//x
    dsi_dcs_wr_1para(sel,0x55,0x15);//x
    dsi_dcs_wr_1para(sel,0x56,0x15);//x
    dsi_dcs_wr_1para(sel,0x57,0x15);//x

    //GIP Timing
    dsi_dcs_wr_1para(sel,0x58,0x40);
    dsi_dcs_wr_1para(sel,0x5B,0x10);
    dsi_dcs_wr_1para(sel,0x5C,0x06);//STV_S0
    dsi_dcs_wr_1para(sel,0x5D,0x40);
    dsi_dcs_wr_1para(sel,0x5E,0x00);
    dsi_dcs_wr_1para(sel,0x5F,0x00);
    dsi_dcs_wr_1para(sel,0x60,0x40);//ETV_W
    dsi_dcs_wr_1para(sel,0x61,0x03);
    dsi_dcs_wr_1para(sel,0x62,0x04);
    dsi_dcs_wr_1para(sel,0x63,0x6C);//CKV_ON
    dsi_dcs_wr_1para(sel,0x64,0x6C);//CKV_OFF
    dsi_dcs_wr_1para(sel,0x65,0x75);
    dsi_dcs_wr_1para(sel,0x66,0x08);//ETV_S0
    dsi_dcs_wr_1para(sel,0x67,0xB4); //ckv_num/ckv_w
    dsi_dcs_wr_1para(sel,0x68,0x08); //CKV_S0
    dsi_dcs_wr_1para(sel,0x69,0x6C);//CKV_ON
    dsi_dcs_wr_1para(sel,0x6A,0x6C);//CKV_OFF
    dsi_dcs_wr_1para(sel,0x6B,0x0C); //dummy
    dsi_dcs_wr_1para(sel,0x6D,0x00);//GGND1
    dsi_dcs_wr_1para(sel,0x6E,0x00);//GGND2
    dsi_dcs_wr_1para(sel,0x6F,0x88);

    dsi_dcs_wr_1para(sel,0x75,0xBB);//FLM_EN
    dsi_dcs_wr_1para(sel,0x76,0x00);
    dsi_dcs_wr_1para(sel,0x77,0x05);
    dsi_dcs_wr_1para(sel,0x78,0x2A);//FLM_OFF

    //Page4
    dsi_dcs_wr_1para(sel,0xE0,0x04);
    dsi_dcs_wr_1para(sel,0x09,0x11);
    dsi_dcs_wr_1para(sel,0x0E,0x48);    //Source EQ option
    dsi_dcs_wr_1para(sel,0x2B,0x2B);
    dsi_dcs_wr_1para(sel,0x2D,0x03);//defult 0x01
    dsi_dcs_wr_1para(sel,0x2E,0x44);

    //Page5
    dsi_dcs_wr_1para(sel,0xE0,0x05);
    dsi_dcs_wr_1para(sel,0x12,0x72);//VCI GAS detect voltage

    //Page0
    dsi_dcs_wr_1para(sel,0xE0,0x00);
    dsi_dcs_wr_1para(sel,0xE6,0x02);//WD_Timer
    dsi_dcs_wr_1para(sel,0xE7,0x0C);//WD_Timer

    //SLP OUT
    dsi_dcs_wr_0para(sel,0x01);
    dsi_dcs_wr_0para(sel,0x11);   // SLPOUT
    delayms(120);


    //DISP ON
    dsi_dcs_wr_0para(sel,0x01);
    dsi_dcs_wr_0para(sel,0x29);   // DSPON
    delayms(5);

}

static void tft7201280_init_s(__u32 sel,__u32 mode,__u32 lane,__u32 format)
{
    __u8 tmp1[15]={0x6c,0x12,0x12,0x34,0x04,0x11,0xF1,0x80,0xE5,0x95,0x23,0x80,0xc0,0xd2,0x58};
    __u8 tmp2[12]={0x00,0xFF,0x01,0x5A,0x01,0x5A,0x01,0x5A,0x01,0x70,0x01,0x70};
    __u8 tmp3[37]={0x00,0x06,0x00,0x01,0x07,0x00,0x00,0x32,0x10,0x08,0x00,0x08,0x52,0x15,0x0E,0x05,0x0E,0x32,0x10,0x00,0x00,0x00,0x37,0x33,0x0C,0x0C,0x37,0x0C,0x0C,0x47,0x08,0x00,0x00,0x00,0x0A,0x00,0x01};
    __u8 tmp4[44]={0x1B,0x1B,0x1A,0x1A,0x06,0x07,0x02,0x03,0x04,0x05,0x00,0x01,0x20,0x21,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x19,0x18,0x24,0x19,0x18,0x25};
    __u8 tmp5[44]={0x1B,0x1B,0x1A,0x1A,0x01,0x00,0x05,0x04,0x03,0x02,0x07,0x06,0x25,0x24,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x19,0x18,0x18,0x19,0x21,0x18,0x18,0x20};
    __u8 tmp6[42]={0x00,0x06,0x17,0x0F,0x10,0x3f,0x2C,0x37,0x0A,0x0F,0x11,0x19,0x10,0x15,0x17,0x15,0x15,0x07,0x13,0x15,0x19,0x00,0x06,0x17,0x0F,0x10,0x3F,0x2C,0x37,0x0A,0x0F,0x11,0x19,0x10,0x15,0x17,0x15,0x15,0x07,0x13,0x15,0x19};
    __u8 tmp7[42]={0x00,0x16,0x1E,0x0E,0x0C,0x39,0x2E,0x3B,0x09,0x0D,0x0F,0x19,0x11,0x14,0x17,0x15,0x15,0x08,0x14,0x15,0x16,0x00,0x12,0x1B,0x0E,0x0C,0x39,0x26,0x2E,0x08,0x0E,0x0F,0x18,0x10,0x14,0x17,0x15,0x16,0x08,0x14,0x15,0x16};

    //-----------------------Initial  Code--------------------------------------//
    //password
    dsi_dcs_wr_3para(sel,0xB9,0xFF,0x83,0x94);
    delayms(1);

    //setting mipi 4-lane
    dsi_dcs_wr_2para(sel,0xBA,0x33,0x83);
    delayms(1);

    dsi_dcs_wr_longpara(sel,0xB1,tmp1,15);
    delayms(1);

    //set display
    dsi_dcs_wr_6para(sel,0xB2,0x00,0x64,0x10,0x07,0x32,0x1C);
    delayms(1);

    //setting CYC
    dsi_dcs_wr_longpara(sel,0xB4,tmp2,12);
    delayms(1);

    //set d3
    dsi_dcs_wr_longpara(sel,0xD3,tmp3,37);
    delayms(1);

    //setting SCAN RGB
    dsi_dcs_wr_1para(sel,0xCC,0x0B);
    delayms(1);

    //setting GIP
    dsi_dcs_wr_longpara(sel,0xD5,tmp4,44);
    delayms(1);

    //set D6
    dsi_dcs_wr_longpara(sel,0xD6,tmp5,44);
    delayms(1);

    //set VOCN option
    dsi_dcs_wr_4para(sel,0xC7,0x00,0xC0,0x00,0xC0);
    delayms(1);

    dsi_dcs_wr_1para(sel,0xC6,0x1D);

    //setting Gamma
    dsi_dcs_wr_longpara(sel,0xE0,tmp6,42);

    //dsi_dcs_wr_longpara(sel,0xE0,tmp7,42);
    delayms(10);

    //setting sleep out
    dsi_dcs_wr_0para(sel,0x11);
    delayms(20);

    dsi_dcs_wr_2para(sel,0xB6,0x32,0x32);

    //setting Display
    dsi_dcs_wr_0para(sel,0x29);   // DSPON
    delayms(10);

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
    LCD_OPEN_FUNC(sel, LCD_power_on, 15);   //open lcd power, and delay 10ms
    LCD_OPEN_FUNC(sel, LCD_panel_init, 30);   //open lcd power, than delay 50ms
    LCD_OPEN_FUNC(sel, sunxi_lcd_tcon_enable, 30);     //open lcd controller, and delay 50ms
    LCD_OPEN_FUNC(sel, LCD_bl_open, 0);     //open lcd backlight, and delay 0ms

    return 0;
}

static s32 LCD_close_flow(u32 sel)
{
    LCD_CLOSE_FUNC(sel, LCD_bl_close, 0);       //close lcd backlight, and delay 0ms
    LCD_CLOSE_FUNC(sel, sunxi_lcd_tcon_disable, 0);         //close lcd controller, and delay 0ms
    LCD_CLOSE_FUNC(sel, LCD_panel_exit, 20);   //open lcd power, than delay 20ms
    LCD_CLOSE_FUNC(sel, LCD_power_off, 50);   //close lcd power, and delay 50ms
    return 0;
}

static void LCD_power_on(u32 sel)
{
    sunxi_lcd_power_enable(sel, 0);//config lcd_power pin to open lcd power0
    sunxi_lcd_pin_cfg(sel, 1);
}

static void LCD_power_off(u32 sel)
{
    sunxi_lcd_pin_cfg(sel, 0);
    sunxi_lcd_power_disable(sel, 0);//config lcd_power pin to close lcd power0
    sunxi_lcd_dsi_clk_disable(sel);
}

static void LCD_bl_open(u32 sel)
{
    sunxi_lcd_pwm_enable(sel);
    sunxi_lcd_backlight_enable(sel);//config lcd_bl_en pin to open lcd backlight
}

static void LCD_bl_close(u32 sel)
{
    sunxi_lcd_backlight_disable(sel);//config lcd_bl_en pin to close lcd backlight
    sunxi_lcd_pwm_disable(sel);
}

static void LCD_panel_init(u32 sel)
{
#if 0
    // 有的屏需要初始化，在这里添加。比如hv屏可能需要spi或则iic初始化，
    // dsi屏，用LP_TX模式初始化
    struct disp_panel_para *panel_info = malloc(sizeof(struct disp_panel_para));

    bsp_disp_get_panel_info(sel, panel_info);
    sunxi_lcd_dsi_clk_enable(sel);
    tft7201280_init_s(sel, panel_info->lcd_dsi_if, panel_info->lcd_dsi_lane, panel_info->lcd_dsi_format);

    disp_sys_free(panel_info);
#else
    struct disp_panel_para *panel_info = malloc(sizeof(struct disp_panel_para));

    bsp_disp_get_panel_info(sel, panel_info);
    sunxi_lcd_dsi_clk_enable(sel);
    //tft7201280_init(sel, panel_info->lcd_dsi_if, panel_info->lcd_dsi_lane, panel_info->lcd_dsi_format);

    disp_sys_free(panel_info);
#endif
    return;
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

struct __lcd_panel VVX07H005A10_panel = {
    /* panel driver name, must mach the lcd_drv_name in sys_config.fex */
    .name = "VVX07H005A10",
    .func = {
         .cfg_panel_info = LCD_cfg_panel_info,
         .cfg_open_flow = LCD_open_flow,
         .cfg_close_flow = LCD_close_flow,
         .lcd_user_defined_func = LCD_user_defined_func,
         }
    ,
};
