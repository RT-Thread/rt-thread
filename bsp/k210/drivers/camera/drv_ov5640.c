/* Copyright 2018 Canaan Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdio.h>
#include <unistd.h>
#include "drv_ov5640.h"
#include "ov5640cfg.h"
#include "ov5640af.h"
#include "dvp.h"

static void hal_delay(uint32_t delay)
{
    usleep(delay * 1000);
}

static void ov5640_wr_reg(uint16_t reg,uint8_t data)
{
    dvp_sccb_send_data(OV5640_ADDR, reg, data);
}

static uint8_t ov5640_rd_reg(uint16_t reg)
{
    return dvp_sccb_receive_data(OV5640_ADDR, reg);
}

uint8_t ov5640_init(void)
{
    uint16_t i = 0;
    uint16_t reg = 0;

    reg = ov5640_rd_reg(OV5640_CHIPIDH);
    reg <<= 8;
    reg |= ov5640_rd_reg(OV5640_CHIPIDL);
    if(reg != OV5640_ID)
    {
        printf("ID: %d \r\n", reg);
        return 1;
    }

    ov5640_wr_reg(0x3103,0X11); /*system clock from pad, bit[1]*/
    ov5640_wr_reg(0X3008,0X82);
    hal_delay(10);

    for(i = 0; i<sizeof(ov5640_init_reg_tbl) / 4; i++)
    {
        ov5640_wr_reg(ov5640_init_reg_tbl[i][0], ov5640_init_reg_tbl[i][1]);
    }

    hal_delay(50);
    /* Test for flash light*/
    ov5640_flash_lamp(1);
    hal_delay(50);
    ov5640_flash_lamp(0);

    return 0x00;
}

void ov5640_flash_lamp(uint8_t sw)
{
    ov5640_wr_reg(0x3016, 0X02);
    ov5640_wr_reg(0x301C, 0X02);
    if(sw)
        ov5640_wr_reg(0X3019, 0X02);
    else
        ov5640_wr_reg(0X3019, 0X00);
}

const static uint8_t OV5640_EXPOSURE_TBL[7][6]=
{
    0x10,0x08,0x10,0x08,0x20,0x10,//-3
    0x20,0x18,0x41,0x20,0x18,0x10,//-2
    0x30,0x28,0x61,0x30,0x28,0x10,//-1
    0x38,0x30,0x61,0x38,0x30,0x10,//0
    0x40,0x38,0x71,0x40,0x38,0x10,//+1
    0x50,0x48,0x90,0x50,0x48,0x20,//+2
    0x60,0x58,0xa0,0x60,0x58,0x20,//+3
};

//exposure: 0 - 6,
void OV5640_Exposure(uint8_t exposure)
{
        ov5640_wr_reg(0x3212,0x03); //start group 3
        ov5640_wr_reg(0x3a0f,OV5640_EXPOSURE_TBL[exposure][0]);
        ov5640_wr_reg(0x3a10,OV5640_EXPOSURE_TBL[exposure][1]);
        ov5640_wr_reg(0x3a1b,OV5640_EXPOSURE_TBL[exposure][2]);
        ov5640_wr_reg(0x3a1e,OV5640_EXPOSURE_TBL[exposure][3]);
        ov5640_wr_reg(0x3a11,OV5640_EXPOSURE_TBL[exposure][4]);
        ov5640_wr_reg(0x3a1f,OV5640_EXPOSURE_TBL[exposure][5]);
        ov5640_wr_reg(0x3212,0x13); //end group 3
        ov5640_wr_reg(0x3212,0xa3); //launch group 3
}

const static uint8_t OV5640_LIGHTMODE_TBL[5][7]=
{
    0x04,0X00,0X04,0X00,0X04,0X00,0X00,//Auto
    0x06,0X1C,0X04,0X00,0X04,0XF3,0X01,//Sunny
    0x05,0X48,0X04,0X00,0X07,0XCF,0X01,//Office
    0x06,0X48,0X04,0X00,0X04,0XD3,0X01,//Cloudy
    0x04,0X10,0X04,0X00,0X08,0X40,0X01,//Home
};

// light mode:
//      0: auto
//      1: sunny
//      2: office
//      3: cloudy
//      4: home
void OV5640_Light_Mode(uint8_t mode)
{
    uint8_t i;
    ov5640_wr_reg(0x3212,0x03); //start group 3
    for(i=0;i<7;i++)ov5640_wr_reg(0x3400+i,OV5640_LIGHTMODE_TBL[mode][i]);
    ov5640_wr_reg(0x3212,0x13); //end group 3
    ov5640_wr_reg(0x3212,0xa3); //launch group 3
}

const static uint8_t OV5640_SATURATION_TBL[7][6]=
{
    0X0C,0x30,0X3D,0X3E,0X3D,0X01,//-3
    0X10,0x3D,0X4D,0X4E,0X4D,0X01,//-2
    0X15,0x52,0X66,0X68,0X66,0X02,//-1
    0X1A,0x66,0X80,0X82,0X80,0X02,//+0
    0X1F,0x7A,0X9A,0X9C,0X9A,0X02,//+1
    0X24,0x8F,0XB3,0XB6,0XB3,0X03,//+2
    0X2B,0xAB,0XD6,0XDA,0XD6,0X04,//+3
};


// Color Saturation:
//   sat:  0 - 6
void OV5640_Color_Saturation(uint8_t sat)
{
    uint8_t i;
    ov5640_wr_reg(0x3212,0x03); //start group 3
    ov5640_wr_reg(0x5381,0x1c);
    ov5640_wr_reg(0x5382,0x5a);
    ov5640_wr_reg(0x5383,0x06);
    for(i=0;i<6;i++)  ov5640_wr_reg(0x5384+i,OV5640_SATURATION_TBL[sat][i]);
    ov5640_wr_reg(0x538b, 0x98);
    ov5640_wr_reg(0x538a, 0x01);
    ov5640_wr_reg(0x3212, 0x13); //end group 3
    ov5640_wr_reg(0x3212, 0xa3); //launch group 3
}

//Brightness
//     bright:  0 - 8
void OV5640_Brightness(uint8_t bright)
{
    uint8_t brtval;
    if(bright<4)brtval=4-bright;
    else brtval=bright-4;
    ov5640_wr_reg(0x3212,0x03); //start group 3
    ov5640_wr_reg(0x5587,brtval<<4);
    if(bright<4)ov5640_wr_reg(0x5588,0x09);
    else ov5640_wr_reg(0x5588,0x01);
    ov5640_wr_reg(0x3212,0x13); //end group 3
    ov5640_wr_reg(0x3212,0xa3); //launch group 3
}

//Contrast:
//     contrast:  0 - 6
void OV5640_Contrast(uint8_t contrast)
{
    uint8_t reg0val=0X00;
    uint8_t reg1val=0X20;
    switch(contrast)
    {
        case 0://-3
            reg1val=reg0val=0X14;
            break;
        case 1://-2
            reg1val=reg0val=0X18;
            break;
        case 2://-1
            reg1val=reg0val=0X1C;
            break;
        case 4://1
            reg0val=0X10;
            reg1val=0X24;
            break;
        case 5://2
            reg0val=0X18;
            reg1val=0X28;
            break;
        case 6://3
            reg0val=0X1C;
            reg1val=0X2C;
            break;
    }
    ov5640_wr_reg(0x3212,0x03); //start group 3
    ov5640_wr_reg(0x5585,reg0val);
    ov5640_wr_reg(0x5586,reg1val);
    ov5640_wr_reg(0x3212,0x13); //end group 3
    ov5640_wr_reg(0x3212,0xa3); //launch group 3
}
// Sharpness:
//    sharp: 0 - 33   (0: close , 33: auto , other: Sharpness)

void OV5640_Sharpness(uint8_t sharp)
{
    if(sharp<33)
    {
        ov5640_wr_reg(0x5308,0x65);
        ov5640_wr_reg(0x5302,sharp);
    }else   // auto
    {
        ov5640_wr_reg(0x5308,0x25);
        ov5640_wr_reg(0x5300,0x08);
        ov5640_wr_reg(0x5301,0x30);
        ov5640_wr_reg(0x5302,0x10);
        ov5640_wr_reg(0x5303,0x00);
        ov5640_wr_reg(0x5309,0x08);
        ov5640_wr_reg(0x530a,0x30);
        ov5640_wr_reg(0x530b,0x04);
        ov5640_wr_reg(0x530c,0x06);
    }

}

const static uint8_t OV5640_EFFECTS_TBL[7][3]=
{
        0X06,0x40,0X10, // normal
        0X1E,0xA0,0X40,
        0X1E,0x80,0XC0,
        0X1E,0x80,0X80,
        0X1E,0x40,0XA0,
        0X40,0x40,0X10,
        0X1E,0x60,0X60,
};

void OV5640_Special_Effects(uint8_t eft)
{
    ov5640_wr_reg(0x3212,0x03); //start group 3
    ov5640_wr_reg(0x5580,OV5640_EFFECTS_TBL[eft][0]);
    ov5640_wr_reg(0x5583,OV5640_EFFECTS_TBL[eft][1]);// sat U
    ov5640_wr_reg(0x5584,OV5640_EFFECTS_TBL[eft][2]);// sat V
    ov5640_wr_reg(0x5003,0x08);
    ov5640_wr_reg(0x3212,0x13); //end group 3
    ov5640_wr_reg(0x3212,0xa3); //launch group 3
}

uint8_t OV5640_Focus_Init(void)
{
    uint16_t i;
    uint16_t addr=0x8000;
    uint8_t state=0x8F;
    ov5640_wr_reg(0x3000, 0x20);    //reset
    for(i=0;i<sizeof(OV5640_AF_Config);i++)
    {
        ov5640_wr_reg(addr,OV5640_AF_Config[i]);
        addr++;
    }
    ov5640_wr_reg(0x3022,0x00);
    ov5640_wr_reg(0x3023,0x00);
    ov5640_wr_reg(0x3024,0x00);
    ov5640_wr_reg(0x3025,0x00);
    ov5640_wr_reg(0x3026,0x00);
    ov5640_wr_reg(0x3027,0x00);
    ov5640_wr_reg(0x3028,0x00);
    ov5640_wr_reg(0x3029,0x7f);
    ov5640_wr_reg(0x3000,0x00);
    i=0;
    do
    {
        state=ov5640_rd_reg(0x3029);
        hal_delay(5);
        i++;
        if(i>1000)return 1;
    }while(state!=0x70);
    return 0;
}

uint8_t OV5640_Auto_Focus(void)
{
    uint8_t temp=0;
    uint16_t retry=0;
    ov5640_wr_reg(0x3023,0x01);
    ov5640_wr_reg(0x3022,0x08);
    do
    {
        temp=ov5640_rd_reg(0x3023);
        retry++;
        if(retry>1000)return 2;
        hal_delay(5);
    } while(temp!=0x00);
    ov5640_wr_reg(0x3023,0x01);
    ov5640_wr_reg(0x3022,0x04);
    retry=0;
    do
    {
        temp=ov5640_rd_reg(0x3023);
        retry++;
        if(retry>1000)return 2;
        hal_delay(5);
    }while(temp!=0x00);
    return 0;
}
