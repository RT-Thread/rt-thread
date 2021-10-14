/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-14    spaceman   first version
 */

#include "lcd.h"

// __align(256) rt_uint32_t LTDC_Buf[XSIZE_PHYS * YSIZE_PHYS];

volatile void LCD_delay(volatile int time) //简单软件延时
{
    // volatile rt_uint32_t i;
    // while (time--)
    //     for (i = 500; i > 0; i--)
    //         ;
    rt_thread_mdelay(time);
}
void LTDC_Clock_Set(void) //设置LTDC时钟
{
    RCC->AHB1ENR |= 1 << 31;
    RCC->CR |= 1 << 28;
    RCC->PLLDCKCFGR = 0x1 << 16; //分频系数 0~3 --> 2,4,6,8
    RCC->PLLLCDCFGR = 6 << 6;    //倍频系数
}
void GPIO_RGB_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; //定义GPIO初始化结构体变量

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOE, ENABLE);

    //DE=PB4, PCLK=PB5, HSYNC=PB6, VSYNC=PB7
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //lcd_reset:PD6      LCD_Black_Light On Off  :PD8
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    // GPIO模拟SPI初始化液晶屏        SPI_SDA      SPI_DCLK     LCD_SPI_CS
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_9 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOB, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7, GPIO_AF_LTDC); //PB4~7复用为LTDC的同步信号线
    GPIO_PinAFConfig(GPIOE, GPIO_Pin_All, GPIO_AF_LTDC);                                      //GPIOE所有的IO全部复用为LTDC的数据线
}
static void LCD_Reset(void)
{
    //注意，现在科学发达，有的屏不用复位也行
    LCD_RST(0);
    LCD_delay(200);
    LCD_RST(1);
    LCD_delay(200);
}
void set_resolutionXX(LCD_FORM_TypeDef *LCD_FORM)
{
    rt_uint32_t aHorStart;
    rt_uint32_t aHorEnd;
    rt_uint32_t aVerStart;
    rt_uint32_t aVerEnd;

    aHorStart = LCD_FORM->blkHorEnd + 1;
    aHorEnd = aHorStart + LCD_FORM->aHorLen;
    aVerStart = LCD_FORM->blkVerEnd + 1;
    aVerEnd = aVerStart + LCD_FORM->aVerLen;

    LTDC->P_HOR = aHorEnd;                                             //总宽度
    LTDC->HSYNC = (LCD_FORM->sHsyncStart << 16) | LCD_FORM->sHsyncEnd; //水平同步信号起始和结束，位于背景色中间
    LTDC->A_HOR = (aHorStart << 16) | aHorEnd;                         //水平激活起始和结束
    LTDC->A_HOR_LEN = LCD_FORM->aHorLen;                               //水平激活域宽度
    LTDC->BLK_HOR = (0 << 16) | LCD_FORM->blkHorEnd;                   //背景开始和结束宽度0~激活地址
    LTDC->P_VER = aVerEnd;
    LTDC->VSYNC = (LCD_FORM->sVsyncStart << 16) | LCD_FORM->sVsyncEnd;
    LTDC->A_VER = (aVerStart << 16) | aVerEnd;
    LTDC->A_VER_LEN = LCD_FORM->aVerLen;
    LTDC->BLK_VER = (0 << 16) | LCD_FORM->blkVerEnd;
}

void Set_LCD_Timing_to_LTDC(rt_uint32_t LTDC_Buf1, rt_uint32_t LTDC_Buf2)
{
    LCD_FORM_TypeDef LCD_FORM;
    LTDC->OUT_EN = 0;
    LTDC->DP_ADDR0 = LTDC_Buf1; //第0层地址
    LTDC->DP_ADDR1 = LTDC_Buf2;//第一层地址
    LTDC->BLK_DATA = 0x0000;        //背景色

    LCD_FORM.sHsyncStart = 0x2; //水平激活起始
    LCD_FORM.sHsyncEnd = 0x3;   //水平激活结束
    LCD_FORM.aHorLen = 480 - 1; //水平分辨率
    LCD_FORM.blkHorEnd = 0xf;   //水平消隐

    LCD_FORM.sVsyncStart = 0x2; //垂直激活起始
    LCD_FORM.sVsyncEnd = 0x3;   //垂直激活结束
    LCD_FORM.aVerLen = 800 - 1; //垂直分辨率
    LCD_FORM.blkVerEnd = 0xF;   //垂直消隐

    set_resolutionXX(&LCD_FORM);

    LTDC->VI_FORMAT = 0;
    LTDC->POL_CTL = 0x8 + 3;
    LTDC->OUT_EN |= 0x107;
}
void LTDC_IRQHandler(void)
{
    LTDC->INTR_CLR = 2;
    LTDC->DP_SWT ^= 1; //连续显示两幅图片
    if (LTDC->DP_SWT != 0)
    {
        //        fun_test(SDRAM_RGB_ADD);
    }
    else
    {
        //        fun_test(SDRAM_RGB_ADD+SDRAM_RGB_OFFSET);
    }
    //    if(LTDC->INTR_STA & 2)
    //    {

    //    }
}

void LCD_WriteByteSPI(unsigned char byte)
{
    unsigned char n;

    for (n = 0; n < 8; n++)
    {
        if (byte & 0x80)
            SPI_SDA(1)
        else
            SPI_SDA(0)
        byte <<= 1;

        SPI_DCLK(0);
        SPI_DCLK(1);
    }
}
void SPI_WriteComm(rt_uint16_t CMD)
{
    LCD_SPI_CS(0);
    LCD_WriteByteSPI(0X20);
    LCD_WriteByteSPI(CMD >> 8);
    LCD_WriteByteSPI(0X00);
    LCD_WriteByteSPI(CMD);

    LCD_SPI_CS(1);
}
void SPI_WriteData(rt_uint16_t tem_data)
{
    LCD_SPI_CS(0);
    LCD_WriteByteSPI(0x40);
    LCD_WriteByteSPI(tem_data);
    LCD_SPI_CS(1);
}
void BlockWrite(unsigned int Xstart, unsigned int Xend, unsigned int Ystart, unsigned int Yend)
{
    SPI_WriteComm(0x2a00);
    SPI_WriteData(Xstart >> 8);
    SPI_WriteComm(0x2a01);
    SPI_WriteData(Xstart & 0xff);
    SPI_WriteComm(0x2a02);
    SPI_WriteData(Xend >> 8);
    SPI_WriteComm(0x2a03);
    SPI_WriteData(Xend & 0xff);

    SPI_WriteComm(0x2b00);
    SPI_WriteData(Ystart >> 8);
    SPI_WriteComm(0x2b01);
    SPI_WriteData(Ystart & 0xff);
    SPI_WriteComm(0x2b02);
    SPI_WriteData(Yend >> 8);
    SPI_WriteComm(0x2b03);
    SPI_WriteData(Yend & 0xff);

    SPI_WriteComm(0x2c00);
    //  for(Xstart=0;Xstart<1000;Xstart++)SPI_WriteData(0x55);
}
void Lcd_Initialize(void)
{
    LCD_SPI_CS(1);
    LCD_delay(20);
    LCD_SPI_CS(0);
    LCD_Reset();

    //ENABLE PAGE 1
    SPI_WriteComm(0xF000);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xF001);
    SPI_WriteData(0xAA);
    SPI_WriteComm(0xF002);
    SPI_WriteData(0x52);
    SPI_WriteComm(0xF003);
    SPI_WriteData(0x08);
    SPI_WriteComm(0xF004);
    SPI_WriteData(0x01);

    //GAMMA SETING  RED
    SPI_WriteComm(0xD100);
    SPI_WriteData(0x00);
    SPI_WriteComm(0xD101);
    SPI_WriteData(0x00);
    SPI_WriteComm(0xD102);
    SPI_WriteData(0x1b);
    SPI_WriteComm(0xD103);
    SPI_WriteData(0x44);
    SPI_WriteComm(0xD104);
    SPI_WriteData(0x62);
    SPI_WriteComm(0xD105);
    SPI_WriteData(0x00);
    SPI_WriteComm(0xD106);
    SPI_WriteData(0x7b);
    SPI_WriteComm(0xD107);
    SPI_WriteData(0xa1);
    SPI_WriteComm(0xD108);
    SPI_WriteData(0xc0);
    SPI_WriteComm(0xD109);
    SPI_WriteData(0xee);
    SPI_WriteComm(0xD10A);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD10B);
    SPI_WriteData(0x10);
    SPI_WriteComm(0xD10C);
    SPI_WriteData(0x2c);
    SPI_WriteComm(0xD10D);
    SPI_WriteData(0x43);
    SPI_WriteComm(0xD10E);
    SPI_WriteData(0x57);
    SPI_WriteComm(0xD10F);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD110);
    SPI_WriteData(0x68);
    SPI_WriteComm(0xD111);
    SPI_WriteData(0x78);
    SPI_WriteComm(0xD112);
    SPI_WriteData(0x87);
    SPI_WriteComm(0xD113);
    SPI_WriteData(0x94);
    SPI_WriteComm(0xD114);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD115);
    SPI_WriteData(0xa0);
    SPI_WriteComm(0xD116);
    SPI_WriteData(0xac);
    SPI_WriteComm(0xD117);
    SPI_WriteData(0xb6);
    SPI_WriteComm(0xD118);
    SPI_WriteData(0xc1);
    SPI_WriteComm(0xD119);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD11A);
    SPI_WriteData(0xcb);
    SPI_WriteComm(0xD11B);
    SPI_WriteData(0xcd);
    SPI_WriteComm(0xD11C);
    SPI_WriteData(0xd6);
    SPI_WriteComm(0xD11D);
    SPI_WriteData(0xdf);
    SPI_WriteComm(0xD11E);
    SPI_WriteData(0x95);
    SPI_WriteComm(0xD11F);
    SPI_WriteData(0xe8);
    SPI_WriteComm(0xD120);
    SPI_WriteData(0xf1);
    SPI_WriteComm(0xD121);
    SPI_WriteData(0xfa);
    SPI_WriteComm(0xD122);
    SPI_WriteData(0x02);
    SPI_WriteComm(0xD123);
    SPI_WriteData(0xaa);
    SPI_WriteComm(0xD124);
    SPI_WriteData(0x0b);
    SPI_WriteComm(0xD125);
    SPI_WriteData(0x13);
    SPI_WriteComm(0xD126);
    SPI_WriteData(0x1d);
    SPI_WriteComm(0xD127);
    SPI_WriteData(0x26);
    SPI_WriteComm(0xD128);
    SPI_WriteData(0xaa);
    SPI_WriteComm(0xD129);
    SPI_WriteData(0x30);
    SPI_WriteComm(0xD12A);
    SPI_WriteData(0x3c);
    SPI_WriteComm(0xD12B);
    SPI_WriteData(0x4A);
    SPI_WriteComm(0xD12C);
    SPI_WriteData(0x63);
    SPI_WriteComm(0xD12D);
    SPI_WriteData(0xea);
    SPI_WriteComm(0xD12E);
    SPI_WriteData(0x79);
    SPI_WriteComm(0xD12F);
    SPI_WriteData(0xa6);
    SPI_WriteComm(0xD130);
    SPI_WriteData(0xd0);
    SPI_WriteComm(0xD131);
    SPI_WriteData(0x20);
    SPI_WriteComm(0xD132);
    SPI_WriteData(0x0f);
    SPI_WriteComm(0xD133);
    SPI_WriteData(0x8e);
    SPI_WriteComm(0xD134);
    SPI_WriteData(0xff);
    //GAMMA SETING GREEN
    SPI_WriteComm(0xD200);
    SPI_WriteData(0x00);
    SPI_WriteComm(0xD201);
    SPI_WriteData(0x00);
    SPI_WriteComm(0xD202);
    SPI_WriteData(0x1b);
    SPI_WriteComm(0xD203);
    SPI_WriteData(0x44);
    SPI_WriteComm(0xD204);
    SPI_WriteData(0x62);
    SPI_WriteComm(0xD205);
    SPI_WriteData(0x00);
    SPI_WriteComm(0xD206);
    SPI_WriteData(0x7b);
    SPI_WriteComm(0xD207);
    SPI_WriteData(0xa1);
    SPI_WriteComm(0xD208);
    SPI_WriteData(0xc0);
    SPI_WriteComm(0xD209);
    SPI_WriteData(0xee);
    SPI_WriteComm(0xD20A);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD20B);
    SPI_WriteData(0x10);
    SPI_WriteComm(0xD20C);
    SPI_WriteData(0x2c);
    SPI_WriteComm(0xD20D);
    SPI_WriteData(0x43);
    SPI_WriteComm(0xD20E);
    SPI_WriteData(0x57);
    SPI_WriteComm(0xD20F);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD210);
    SPI_WriteData(0x68);
    SPI_WriteComm(0xD211);
    SPI_WriteData(0x78);
    SPI_WriteComm(0xD212);
    SPI_WriteData(0x87);
    SPI_WriteComm(0xD213);
    SPI_WriteData(0x94);
    SPI_WriteComm(0xD214);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD215);
    SPI_WriteData(0xa0);
    SPI_WriteComm(0xD216);
    SPI_WriteData(0xac);
    SPI_WriteComm(0xD217);
    SPI_WriteData(0xb6);
    SPI_WriteComm(0xD218);
    SPI_WriteData(0xc1);
    SPI_WriteComm(0xD219);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD21A);
    SPI_WriteData(0xcb);
    SPI_WriteComm(0xD21B);
    SPI_WriteData(0xcd);
    SPI_WriteComm(0xD21C);
    SPI_WriteData(0xd6);
    SPI_WriteComm(0xD21D);
    SPI_WriteData(0xdf);
    SPI_WriteComm(0xD21E);
    SPI_WriteData(0x95);
    SPI_WriteComm(0xD21F);
    SPI_WriteData(0xe8);
    SPI_WriteComm(0xD220);
    SPI_WriteData(0xf1);
    SPI_WriteComm(0xD221);
    SPI_WriteData(0xfa);
    SPI_WriteComm(0xD222);
    SPI_WriteData(0x02);
    SPI_WriteComm(0xD223);
    SPI_WriteData(0xaa);
    SPI_WriteComm(0xD224);
    SPI_WriteData(0x0b);
    SPI_WriteComm(0xD225);
    SPI_WriteData(0x13);
    SPI_WriteComm(0xD226);
    SPI_WriteData(0x1d);
    SPI_WriteComm(0xD227);
    SPI_WriteData(0x26);
    SPI_WriteComm(0xD228);
    SPI_WriteData(0xaa);
    SPI_WriteComm(0xD229);
    SPI_WriteData(0x30);
    SPI_WriteComm(0xD22A);
    SPI_WriteData(0x3c);
    SPI_WriteComm(0xD22B);
    SPI_WriteData(0x4a);
    SPI_WriteComm(0xD22C);
    SPI_WriteData(0x63);
    SPI_WriteComm(0xD22D);
    SPI_WriteData(0xea);
    SPI_WriteComm(0xD22E);
    SPI_WriteData(0x79);
    SPI_WriteComm(0xD22F);
    SPI_WriteData(0xa6);
    SPI_WriteComm(0xD230);
    SPI_WriteData(0xd0);
    SPI_WriteComm(0xD231);
    SPI_WriteData(0x20);
    SPI_WriteComm(0xD232);
    SPI_WriteData(0x0f);
    SPI_WriteComm(0xD233);
    SPI_WriteData(0x8e);
    SPI_WriteComm(0xD234);
    SPI_WriteData(0xff);

    //GAMMA SETING BLUE
    SPI_WriteComm(0xD300);
    SPI_WriteData(0x00);
    SPI_WriteComm(0xD301);
    SPI_WriteData(0x00);
    SPI_WriteComm(0xD302);
    SPI_WriteData(0x1b);
    SPI_WriteComm(0xD303);
    SPI_WriteData(0x44);
    SPI_WriteComm(0xD304);
    SPI_WriteData(0x62);
    SPI_WriteComm(0xD305);
    SPI_WriteData(0x00);
    SPI_WriteComm(0xD306);
    SPI_WriteData(0x7b);
    SPI_WriteComm(0xD307);
    SPI_WriteData(0xa1);
    SPI_WriteComm(0xD308);
    SPI_WriteData(0xc0);
    SPI_WriteComm(0xD309);
    SPI_WriteData(0xee);
    SPI_WriteComm(0xD30A);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD30B);
    SPI_WriteData(0x10);
    SPI_WriteComm(0xD30C);
    SPI_WriteData(0x2c);
    SPI_WriteComm(0xD30D);
    SPI_WriteData(0x43);
    SPI_WriteComm(0xD30E);
    SPI_WriteData(0x57);
    SPI_WriteComm(0xD30F);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD310);
    SPI_WriteData(0x68);
    SPI_WriteComm(0xD311);
    SPI_WriteData(0x78);
    SPI_WriteComm(0xD312);
    SPI_WriteData(0x87);
    SPI_WriteComm(0xD313);
    SPI_WriteData(0x94);
    SPI_WriteComm(0xD314);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD315);
    SPI_WriteData(0xa0);
    SPI_WriteComm(0xD316);
    SPI_WriteData(0xac);
    SPI_WriteComm(0xD317);
    SPI_WriteData(0xb6);
    SPI_WriteComm(0xD318);
    SPI_WriteData(0xc1);
    SPI_WriteComm(0xD319);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD31A);
    SPI_WriteData(0xcb);
    SPI_WriteComm(0xD31B);
    SPI_WriteData(0xcd);
    SPI_WriteComm(0xD31C);
    SPI_WriteData(0xd6);
    SPI_WriteComm(0xD31D);
    SPI_WriteData(0xdf);
    SPI_WriteComm(0xD31E);
    SPI_WriteData(0x95);
    SPI_WriteComm(0xD31F);
    SPI_WriteData(0xe8);
    SPI_WriteComm(0xD320);
    SPI_WriteData(0xf1);
    SPI_WriteComm(0xD321);
    SPI_WriteData(0xfa);
    SPI_WriteComm(0xD322);
    SPI_WriteData(0x02);
    SPI_WriteComm(0xD323);
    SPI_WriteData(0xaa);
    SPI_WriteComm(0xD324);
    SPI_WriteData(0x0b);
    SPI_WriteComm(0xD325);
    SPI_WriteData(0x13);
    SPI_WriteComm(0xD326);
    SPI_WriteData(0x1d);
    SPI_WriteComm(0xD327);
    SPI_WriteData(0x26);
    SPI_WriteComm(0xD328);
    SPI_WriteData(0xaa);
    SPI_WriteComm(0xD329);
    SPI_WriteData(0x30);
    SPI_WriteComm(0xD32A);
    SPI_WriteData(0x3c);
    SPI_WriteComm(0xD32B);
    SPI_WriteData(0x4A);
    SPI_WriteComm(0xD32C);
    SPI_WriteData(0x63);
    SPI_WriteComm(0xD32D);
    SPI_WriteData(0xea);
    SPI_WriteComm(0xD32E);
    SPI_WriteData(0x79);
    SPI_WriteComm(0xD32F);
    SPI_WriteData(0xa6);
    SPI_WriteComm(0xD330);
    SPI_WriteData(0xd0);
    SPI_WriteComm(0xD331);
    SPI_WriteData(0x20);
    SPI_WriteComm(0xD332);
    SPI_WriteData(0x0f);
    SPI_WriteComm(0xD333);
    SPI_WriteData(0x8e);
    SPI_WriteComm(0xD334);
    SPI_WriteData(0xff);

    //GAMMA SETING  RED
    SPI_WriteComm(0xD400);
    SPI_WriteData(0x00);
    SPI_WriteComm(0xD401);
    SPI_WriteData(0x00);
    SPI_WriteComm(0xD402);
    SPI_WriteData(0x1b);
    SPI_WriteComm(0xD403);
    SPI_WriteData(0x44);
    SPI_WriteComm(0xD404);
    SPI_WriteData(0x62);
    SPI_WriteComm(0xD405);
    SPI_WriteData(0x00);
    SPI_WriteComm(0xD406);
    SPI_WriteData(0x7b);
    SPI_WriteComm(0xD407);
    SPI_WriteData(0xa1);
    SPI_WriteComm(0xD408);
    SPI_WriteData(0xc0);
    SPI_WriteComm(0xD409);
    SPI_WriteData(0xee);
    SPI_WriteComm(0xD40A);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD40B);
    SPI_WriteData(0x10);
    SPI_WriteComm(0xD40C);
    SPI_WriteData(0x2c);
    SPI_WriteComm(0xD40D);
    SPI_WriteData(0x43);
    SPI_WriteComm(0xD40E);
    SPI_WriteData(0x57);
    SPI_WriteComm(0xD40F);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD410);
    SPI_WriteData(0x68);
    SPI_WriteComm(0xD411);
    SPI_WriteData(0x78);
    SPI_WriteComm(0xD412);
    SPI_WriteData(0x87);
    SPI_WriteComm(0xD413);
    SPI_WriteData(0x94);
    SPI_WriteComm(0xD414);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD415);
    SPI_WriteData(0xa0);
    SPI_WriteComm(0xD416);
    SPI_WriteData(0xac);
    SPI_WriteComm(0xD417);
    SPI_WriteData(0xb6);
    SPI_WriteComm(0xD418);
    SPI_WriteData(0xc1);
    SPI_WriteComm(0xD419);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD41A);
    SPI_WriteData(0xcb);
    SPI_WriteComm(0xD41B);
    SPI_WriteData(0xcd);
    SPI_WriteComm(0xD41C);
    SPI_WriteData(0xd6);
    SPI_WriteComm(0xD41D);
    SPI_WriteData(0xdf);
    SPI_WriteComm(0xD41E);
    SPI_WriteData(0x95);
    SPI_WriteComm(0xD41F);
    SPI_WriteData(0xe8);
    SPI_WriteComm(0xD420);
    SPI_WriteData(0xf1);
    SPI_WriteComm(0xD421);
    SPI_WriteData(0xfa);
    SPI_WriteComm(0xD422);
    SPI_WriteData(0x02);
    SPI_WriteComm(0xD423);
    SPI_WriteData(0xaa);
    SPI_WriteComm(0xD424);
    SPI_WriteData(0x0b);
    SPI_WriteComm(0xD425);
    SPI_WriteData(0x13);
    SPI_WriteComm(0xD426);
    SPI_WriteData(0x1d);
    SPI_WriteComm(0xD427);
    SPI_WriteData(0x26);
    SPI_WriteComm(0xD428);
    SPI_WriteData(0xaa);
    SPI_WriteComm(0xD429);
    SPI_WriteData(0x30);
    SPI_WriteComm(0xD42A);
    SPI_WriteData(0x3c);
    SPI_WriteComm(0xD42B);
    SPI_WriteData(0x4A);
    SPI_WriteComm(0xD42C);
    SPI_WriteData(0x63);
    SPI_WriteComm(0xD42D);
    SPI_WriteData(0xea);
    SPI_WriteComm(0xD42E);
    SPI_WriteData(0x79);
    SPI_WriteComm(0xD42F);
    SPI_WriteData(0xa6);
    SPI_WriteComm(0xD430);
    SPI_WriteData(0xd0);
    SPI_WriteComm(0xD431);
    SPI_WriteData(0x20);
    SPI_WriteComm(0xD432);
    SPI_WriteData(0x0f);
    SPI_WriteComm(0xD433);
    SPI_WriteData(0x8e);
    SPI_WriteComm(0xD434);
    SPI_WriteData(0xff);

    //GAMMA SETING GREEN
    SPI_WriteComm(0xD500);
    SPI_WriteData(0x00);
    SPI_WriteComm(0xD501);
    SPI_WriteData(0x00);
    SPI_WriteComm(0xD502);
    SPI_WriteData(0x1b);
    SPI_WriteComm(0xD503);
    SPI_WriteData(0x44);
    SPI_WriteComm(0xD504);
    SPI_WriteData(0x62);
    SPI_WriteComm(0xD505);
    SPI_WriteData(0x00);
    SPI_WriteComm(0xD506);
    SPI_WriteData(0x7b);
    SPI_WriteComm(0xD507);
    SPI_WriteData(0xa1);
    SPI_WriteComm(0xD508);
    SPI_WriteData(0xc0);
    SPI_WriteComm(0xD509);
    SPI_WriteData(0xee);
    SPI_WriteComm(0xD50A);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD50B);
    SPI_WriteData(0x10);
    SPI_WriteComm(0xD50C);
    SPI_WriteData(0x2c);
    SPI_WriteComm(0xD50D);
    SPI_WriteData(0x43);
    SPI_WriteComm(0xD50E);
    SPI_WriteData(0x57);
    SPI_WriteComm(0xD50F);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD510);
    SPI_WriteData(0x68);
    SPI_WriteComm(0xD511);
    SPI_WriteData(0x78);
    SPI_WriteComm(0xD512);
    SPI_WriteData(0x87);
    SPI_WriteComm(0xD513);
    SPI_WriteData(0x94);
    SPI_WriteComm(0xD514);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD515);
    SPI_WriteData(0xa0);
    SPI_WriteComm(0xD516);
    SPI_WriteData(0xac);
    SPI_WriteComm(0xD517);
    SPI_WriteData(0xb6);
    SPI_WriteComm(0xD518);
    SPI_WriteData(0xc1);
    SPI_WriteComm(0xD519);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD51A);
    SPI_WriteData(0xcb);
    SPI_WriteComm(0xD51B);
    SPI_WriteData(0xcd);
    SPI_WriteComm(0xD51C);
    SPI_WriteData(0xd6);
    SPI_WriteComm(0xD51D);
    SPI_WriteData(0xdf);
    SPI_WriteComm(0xD51E);
    SPI_WriteData(0x95);
    SPI_WriteComm(0xD51F);
    SPI_WriteData(0xe8);
    SPI_WriteComm(0xD520);
    SPI_WriteData(0xf1);
    SPI_WriteComm(0xD521);
    SPI_WriteData(0xfa);
    SPI_WriteComm(0xD522);
    SPI_WriteData(0x02);
    SPI_WriteComm(0xD523);
    SPI_WriteData(0xaa);
    SPI_WriteComm(0xD524);
    SPI_WriteData(0x0b);
    SPI_WriteComm(0xD525);
    SPI_WriteData(0x13);
    SPI_WriteComm(0xD526);
    SPI_WriteData(0x1d);
    SPI_WriteComm(0xD527);
    SPI_WriteData(0x26);
    SPI_WriteComm(0xD528);
    SPI_WriteData(0xaa);
    SPI_WriteComm(0xD529);
    SPI_WriteData(0x30);
    SPI_WriteComm(0xD52A);
    SPI_WriteData(0x3c);
    SPI_WriteComm(0xD52B);
    SPI_WriteData(0x4a);
    SPI_WriteComm(0xD52C);
    SPI_WriteData(0x63);
    SPI_WriteComm(0xD52D);
    SPI_WriteData(0xea);
    SPI_WriteComm(0xD52E);
    SPI_WriteData(0x79);
    SPI_WriteComm(0xD52F);
    SPI_WriteData(0xa6);
    SPI_WriteComm(0xD530);
    SPI_WriteData(0xd0);
    SPI_WriteComm(0xD531);
    SPI_WriteData(0x20);
    SPI_WriteComm(0xD532);
    SPI_WriteData(0x0f);
    SPI_WriteComm(0xD533);
    SPI_WriteData(0x8e);
    SPI_WriteComm(0xD534);
    SPI_WriteData(0xff);

    //GAMMA SETING BLUE
    SPI_WriteComm(0xD600);
    SPI_WriteData(0x00);
    SPI_WriteComm(0xD601);
    SPI_WriteData(0x00);
    SPI_WriteComm(0xD602);
    SPI_WriteData(0x1b);
    SPI_WriteComm(0xD603);
    SPI_WriteData(0x44);
    SPI_WriteComm(0xD604);
    SPI_WriteData(0x62);
    SPI_WriteComm(0xD605);
    SPI_WriteData(0x00);
    SPI_WriteComm(0xD606);
    SPI_WriteData(0x7b);
    SPI_WriteComm(0xD607);
    SPI_WriteData(0xa1);
    SPI_WriteComm(0xD608);
    SPI_WriteData(0xc0);
    SPI_WriteComm(0xD609);
    SPI_WriteData(0xee);
    SPI_WriteComm(0xD60A);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD60B);
    SPI_WriteData(0x10);
    SPI_WriteComm(0xD60C);
    SPI_WriteData(0x2c);
    SPI_WriteComm(0xD60D);
    SPI_WriteData(0x43);
    SPI_WriteComm(0xD60E);
    SPI_WriteData(0x57);
    SPI_WriteComm(0xD60F);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD610);
    SPI_WriteData(0x68);
    SPI_WriteComm(0xD611);
    SPI_WriteData(0x78);
    SPI_WriteComm(0xD612);
    SPI_WriteData(0x87);
    SPI_WriteComm(0xD613);
    SPI_WriteData(0x94);
    SPI_WriteComm(0xD614);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD615);
    SPI_WriteData(0xa0);
    SPI_WriteComm(0xD616);
    SPI_WriteData(0xac);
    SPI_WriteComm(0xD617);
    SPI_WriteData(0xb6);
    SPI_WriteComm(0xD618);
    SPI_WriteData(0xc1);
    SPI_WriteComm(0xD619);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xD61A);
    SPI_WriteData(0xcb);
    SPI_WriteComm(0xD61B);
    SPI_WriteData(0xcd);
    SPI_WriteComm(0xD61C);
    SPI_WriteData(0xd6);
    SPI_WriteComm(0xD61D);
    SPI_WriteData(0xdf);
    SPI_WriteComm(0xD61E);
    SPI_WriteData(0x95);
    SPI_WriteComm(0xD61F);
    SPI_WriteData(0xe8);
    SPI_WriteComm(0xD620);
    SPI_WriteData(0xf1);
    SPI_WriteComm(0xD621);
    SPI_WriteData(0xfa);
    SPI_WriteComm(0xD622);
    SPI_WriteData(0x02);
    SPI_WriteComm(0xD623);
    SPI_WriteData(0xaa);
    SPI_WriteComm(0xD624);
    SPI_WriteData(0x0b);
    SPI_WriteComm(0xD625);
    SPI_WriteData(0x13);
    SPI_WriteComm(0xD626);
    SPI_WriteData(0x1d);
    SPI_WriteComm(0xD627);
    SPI_WriteData(0x26);
    SPI_WriteComm(0xD628);
    SPI_WriteData(0xaa);
    SPI_WriteComm(0xD629);
    SPI_WriteData(0x30);
    SPI_WriteComm(0xD62A);
    SPI_WriteData(0x3c);
    SPI_WriteComm(0xD62B);
    SPI_WriteData(0x4A);
    SPI_WriteComm(0xD62C);
    SPI_WriteData(0x63);
    SPI_WriteComm(0xD62D);
    SPI_WriteData(0xea);
    SPI_WriteComm(0xD62E);
    SPI_WriteData(0x79);
    SPI_WriteComm(0xD62F);
    SPI_WriteData(0xa6);
    SPI_WriteComm(0xD630);
    SPI_WriteData(0xd0);
    SPI_WriteComm(0xD631);
    SPI_WriteData(0x20);
    SPI_WriteComm(0xD632);
    SPI_WriteData(0x0f);
    SPI_WriteComm(0xD633);
    SPI_WriteData(0x8e);
    SPI_WriteComm(0xD634);
    SPI_WriteData(0xff);

    //AVDD VOLTAGE SETTING
    SPI_WriteComm(0xB000);
    SPI_WriteData(0x05);
    SPI_WriteComm(0xB001);
    SPI_WriteData(0x05);
    SPI_WriteComm(0xB002);
    SPI_WriteData(0x05);
    //AVEE VOLTAGE SETTING
    SPI_WriteComm(0xB100);
    SPI_WriteData(0x05);
    SPI_WriteComm(0xB101);
    SPI_WriteData(0x05);
    SPI_WriteComm(0xB102);
    SPI_WriteData(0x05);

    //AVDD Boosting
    SPI_WriteComm(0xB600);
    SPI_WriteData(0x34);
    SPI_WriteComm(0xB601);
    SPI_WriteData(0x34);
    SPI_WriteComm(0xB603);
    SPI_WriteData(0x34);
    //AVEE Boosting
    SPI_WriteComm(0xB700);
    SPI_WriteData(0x24);
    SPI_WriteComm(0xB701);
    SPI_WriteData(0x24);
    SPI_WriteComm(0xB702);
    SPI_WriteData(0x24);
    //VCL Boosting
    SPI_WriteComm(0xB800);
    SPI_WriteData(0x24);
    SPI_WriteComm(0xB801);
    SPI_WriteData(0x24);
    SPI_WriteComm(0xB802);
    SPI_WriteData(0x24);
    //VGLX VOLTAGE SETTING
    SPI_WriteComm(0xBA00);
    SPI_WriteData(0x14);
    SPI_WriteComm(0xBA01);
    SPI_WriteData(0x14);
    SPI_WriteComm(0xBA02);
    SPI_WriteData(0x14);
    //VCL Boosting
    SPI_WriteComm(0xB900);
    SPI_WriteData(0x24);
    SPI_WriteComm(0xB901);
    SPI_WriteData(0x24);
    SPI_WriteComm(0xB902);
    SPI_WriteData(0x24);
    //Gamma Voltage
    SPI_WriteComm(0xBc00);
    SPI_WriteData(0x00);
    SPI_WriteComm(0xBc01);
    SPI_WriteData(0xa0); //vgmp=5.0
    SPI_WriteComm(0xBc02);
    SPI_WriteData(0x00);
    SPI_WriteComm(0xBd00);
    SPI_WriteData(0x00);
    SPI_WriteComm(0xBd01);
    SPI_WriteData(0xa0); //vgmn=5.0
    SPI_WriteComm(0xBd02);
    SPI_WriteData(0x00);
    //VCOM Setting
    SPI_WriteComm(0xBe01);
    SPI_WriteData(0x3d); //3
    //ENABLE PAGE 0
    SPI_WriteComm(0xF000);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xF001);
    SPI_WriteData(0xAA);
    SPI_WriteComm(0xF002);
    SPI_WriteData(0x52);
    SPI_WriteComm(0xF003);
    SPI_WriteData(0x08);
    SPI_WriteComm(0xF004);
    SPI_WriteData(0x00);
    //Vivid Color Function Control
    SPI_WriteComm(0xB400);
    SPI_WriteData(0x10);
    //Z-INVERSION
    SPI_WriteComm(0xBC00);
    SPI_WriteData(0x05);
    SPI_WriteComm(0xBC01);
    SPI_WriteData(0x05);
    SPI_WriteComm(0xBC02);
    SPI_WriteData(0x05);

    //*************** add on 20111021**********************//
    SPI_WriteComm(0xB700);
    SPI_WriteData(0x22); //GATE EQ CONTROL
    SPI_WriteComm(0xB701);
    SPI_WriteData(0x22); //GATE EQ CONTROL

    SPI_WriteComm(0xC80B);
    SPI_WriteData(0x2A); //DISPLAY TIMING CONTROL
    SPI_WriteComm(0xC80C);
    SPI_WriteData(0x2A); //DISPLAY TIMING CONTROL
    SPI_WriteComm(0xC80F);
    SPI_WriteData(0x2A); //DISPLAY TIMING CONTROL
    SPI_WriteComm(0xC810);
    SPI_WriteData(0x2A); //DISPLAY TIMING CONTROL
    //*************** add on 20111021**********************//
    //PWM_ENH_OE =1
    SPI_WriteComm(0xd000);
    SPI_WriteData(0x01);
    //DM_SEL =1
    SPI_WriteComm(0xb300);
    SPI_WriteData(0x10);
    //VBPDA=07h
    SPI_WriteComm(0xBd02);
    SPI_WriteData(0x07);
    //VBPDb=07h
    SPI_WriteComm(0xBe02);
    SPI_WriteData(0x07);
    //VBPDc=07h
    SPI_WriteComm(0xBf02);
    SPI_WriteData(0x07);
    //ENABLE PAGE 2
    SPI_WriteComm(0xF000);
    SPI_WriteData(0x55);
    SPI_WriteComm(0xF001);
    SPI_WriteData(0xAA);
    SPI_WriteComm(0xF002);
    SPI_WriteData(0x52);
    SPI_WriteComm(0xF003);
    SPI_WriteData(0x08);
    SPI_WriteComm(0xF004);
    SPI_WriteData(0x02);
    //SDREG0 =0
    SPI_WriteComm(0xc301);
    SPI_WriteData(0xa9);
    //DS=14
    SPI_WriteComm(0xfe01);
    SPI_WriteData(0x94);
    //OSC =60h
    SPI_WriteComm(0xf600);
    SPI_WriteData(0x60);
    //TE ON
    SPI_WriteComm(0x3500);
    SPI_WriteData(0x00);

    SPI_WriteComm(0x3600);
    SPI_WriteData(0x0048);
    SPI_WriteComm(0x1100);
    LCD_delay(120);

    SPI_WriteComm(0x2900);

    SPI_WriteComm(0x2c00);
    SPI_WriteComm(0x3c00);
}
void LCD_Initial(rt_uint32_t LTDC_Buf1, rt_uint32_t LTDC_Buf2) //LCD初始化函数
{
    GPIO_RGB_INIT(); //初始化液晶屏相关GPIO
    LCD_Reset();     //复位液晶屏

    LTDC_Clock_Set();
    Set_LCD_Timing_to_LTDC(LTDC_Buf1, LTDC_Buf2);
    Lcd_Initialize();
    Lcd_Light_ON; //打开背光
}



/**********************************************
函数名：Lcd矩形填充函数

入口参数：xStart x方向的起始点
          ySrart y方向的终止点
          xLong 要选定矩形的x方向长度
          yLong  要选定矩形的y方向长度
返回值：无
***********************************************/
// void Lcd_ColorBox(rt_uint16_t xStart, rt_uint16_t yStart, rt_uint16_t xLong, rt_uint16_t yLong, rt_uint32_t Color)
// {
//     rt_uint16_t i, j;
//     rt_uint32_t temp;
//     temp = YSIZE_PHYS * xStart;
//     for (i = 0; i < yLong; i++)
//     {
//         for (j = 0; j < xLong; j++)
//             LTDC_Buf[yStart + i + YSIZE_PHYS * j + temp] = Color;
//     }

//     //   rt_uint16_t i,j;
//     //   rt_uint32_t temp;
//     //   temp = XSIZE_PHYS*yStart;
//     //   for(i=0;i<yLong;i++)
//     //   {
//     //       for(j=0;j<xLong;j++)
//     //       LTDC_Buf[xStart+j+XSIZE_PHYS*i+temp]=Color;
//     //   }
// }

/******************************************
函数名：Lcd图像填充
功能：向Lcd指定位置填充图像
入口参数：
                    (x,y): 图片左上角起始坐标
                    (pic_H,pic_V): 图片的宽高
                     pic  指向存储图片数组的指针
LCD_Fill_Pic(400,100,320,480,(rt_uint32_t*)gImage_MM_T035);
******************************************/
// void LCD_Fill_Pic(rt_uint16_t x, rt_uint16_t y, rt_uint16_t pic_H, rt_uint16_t pic_V, rt_uint32_t *pic)
// {
//     rt_uint16_t i, j;
//     rt_uint32_t Xstart, k = 0;
//     Xstart = YSIZE_PHYS * x;
//     for (i = 0; i < pic_V; i++)
//     {
//         for (j = 0; j < pic_H; j++)
//             LTDC_Buf[Xstart + i + YSIZE_PHYS * j + y] = pic[k++];
//     }

//     //   rt_uint16_t i,j;
//     //   rt_uint32_t Ystart,k=0;
//     //   Ystart = YSIZE_PHYS*y;
//     //   for(i=0;i<pic_V;i++)
//     //   {
//     //       for(j=0;j<pic_H;j++)
//     //       LTDC_Buf[x+j+YSIZE_PHYS*i+Ystart]=pic[k++];
//     //   }
// }
//=============== 在x，y 坐标上打一个颜色为Color的点 ===============
// void DrawPixel(rt_uint16_t x, rt_uint16_t y, int Color)
// {
//     LTDC_Buf[y + YSIZE_PHYS * x] = Color;
//     //   LTDC_Buf[x+XSIZE_PHYS*y] = Color;
// }
/**********8*16字体 ASCII码 显示*************
(x,y): 显示字母的起始坐标
num:   要显示的字符:" "--->"~"
fColor 前景色
bColor 背景色
flag:  有背景色(1)无背景色(0)
*********************************************/
// void SPILCD_ShowChar(unsigned short x, unsigned short y, unsigned char num, unsigned int fColor, unsigned int bColor, unsigned char flag)
// {
//     unsigned char temp;
//     unsigned int pos, i, j;

//     num = num - ' '; //得到偏移后的值
//     i = num * 16;
//     for (pos = 0; pos < 16; pos++)
//     {
//         temp = nAsciiDot[i + pos]; //调通调用ASCII字体
//         for (j = 0; j < 8; j++)
//         {
//             if (temp & 0x80)
//                 DrawPixel(x + j, y, fColor);
//             else if (flag)
//                 DrawPixel(x + j, y, bColor); //如果背景色标志flag为1
//             temp <<= 1;
//         }
//         y++;
//     }
// }

/**********写一个16x16的汉字*****************
(x,y): 显示汉字的起始坐标
c[2]:  要显示的汉字
fColor 前景色
bColor 背景色
flag:  有背景色(1)无背景色(0)
*********************************************/
// void PutGB1616(unsigned short x, unsigned short y, unsigned char c[2], unsigned int fColor, unsigned int bColor, unsigned char flag)
// {
//     unsigned int i, j, k;
//     unsigned short m;
//     for (k = 0; k < 64; k++)
//     { //64标示自建汉字库中的个数，循环查询内码
//         if ((codeGB_16[k].Index[0] == c[0]) && (codeGB_16[k].Index[1] == c[1]))
//         {
//             for (i = 0; i < 32; i++)
//             {
//                 m = codeGB_16[k].Msk[i];
//                 for (j = 0; j < 8; j++)
//                 {
//                     if ((m & 0x80) == 0x80)
//                     {
//                         DrawPixel(x + j, y, fColor);
//                     }
//                     else
//                     {
//                         if (flag)
//                             DrawPixel(x + j, y, bColor);
//                     }
//                     m = m << 1;
//                 }
//                 if (i % 2)
//                 {
//                     y++;
//                     x = x - 8;
//                 }
//                 else
//                     x = x + 8;
//             }
//         }
//     }
// }
/**********显示一串字*****************
(x,y): 字符串的起始坐标
*s:    要显示的字符串指针
fColor 前景色
bColor 背景色
flag:  有背景色(1)无背景色(0)
*********************************************/
// void LCD_PutString(unsigned short x, unsigned short y, char *s, unsigned int fColor, unsigned int bColor, unsigned char flag)
// {
//     unsigned char l = 0;
//     while (*s)
//     {
//         if (*s < 0x80)
//         {
//             SPILCD_ShowChar(x + l * 8, y, *s, fColor, bColor, flag);
//             s++;
//             l++;
//         }
//         else
//         {
//             PutGB1616(x + l * 8, y, (unsigned char *)s, fColor, bColor, flag);
//             s += 2;
//             l += 2;
//         }
//     }
// }
