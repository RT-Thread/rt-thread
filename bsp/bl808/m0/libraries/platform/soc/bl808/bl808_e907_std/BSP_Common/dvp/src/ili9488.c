/**
  ******************************************************************************
  * @file    ili9488.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#include "ili9488.h"

/** @addtogroup  ILI9488_Driver
 *  @{
 */

/** @addtogroup  ILI9488
 *  @{
 */

/** @defgroup  ILI9488_Private_Macros
 *  @{
 */
#define DBI_DMA_USE                      DMA2_ID

/*@} end of group ILI9488_Private_Macros */

/** @defgroup  ILI9488_Private_Types
 *  @{
 */

/*@} end of group ILI9488_Private_Types */

/** @defgroup  ILI9488_Private_Variables
 *  @{
 */

/*@} end of group ILI9488_Private_Variables */

/** @defgroup  ILI9488_Global_Variables
 *  @{
 */

/*@} end of group ILI9488_Global_Variables */

/** @defgroup  ILI9488_Private_Fun_Declaration
 *  @{
 */

/*@} end of group ILI9488_Private_Fun_Declaration */

/** @defgroup  ILI9488_Private_Functions
 *  @{
 */

/*@} end of group ILI9488_Private_Functions */

/** @defgroup  ILI9488_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  SPI LCD init
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void LCD_Init(void)
{
    /* Reset */
    //DBI_ILI9488_RESET_HIGH;
    //ARCH_Delay_MS(1);
    //DBI_ILI9488_RESET_LOW;
    //ARCH_Delay_MS(10);
    //DBI_ILI9488_RESET_HIGH;
    //ARCH_Delay_MS(120);
    
    /* PGAMCTRL (Positive Gamma Control) */
    DBI_SendCommand(0xE0);
    DBI_SendData(0x00,1);
    DBI_SendData(0x07,1);
    DBI_SendData(0x0F,1);
    DBI_SendData(0x0D,1);
    DBI_SendData(0x1B,1);
    DBI_SendData(0x0A,1);
    DBI_SendData(0x3C,1);
    DBI_SendData(0x78,1);
    DBI_SendData(0x4A,1);
    DBI_SendData(0x07,1);
    DBI_SendData(0x0E,1);
    DBI_SendData(0x09,1);
    DBI_SendData(0x1B,1);
    DBI_SendData(0x1E,1);
    DBI_SendData(0x0F,1);
    
    /* NGAMCTRL (Negative Gamma Control) */
    DBI_SendCommand(0xE1);
    DBI_SendData(0x00,1);
    DBI_SendData(0x22,1);
    DBI_SendData(0x24,1);
    DBI_SendData(0x06,1);
    DBI_SendData(0x12,1);
    DBI_SendData(0x07,1);
    DBI_SendData(0x36,1);
    DBI_SendData(0x47,1);
    DBI_SendData(0x47,1);
    DBI_SendData(0x06,1);
    DBI_SendData(0x0A,1);
    DBI_SendData(0x07,1);
    DBI_SendData(0x30,1);
    DBI_SendData(0x37,1);
    DBI_SendData(0x0F,1);
    
    /* Power Control 1 */
    DBI_SendCommand(0xC0);
    DBI_SendData(0x10,1);
    DBI_SendData(0x10,1);
    
    /* Power Control 2 */
    DBI_SendCommand(0xC1);
    DBI_SendData(0x41,1);
    
    /* VCOM Control */
    DBI_SendCommand(0xC5);
    DBI_SendData(0x00,1);
    DBI_SendData(0x2c,1);
    DBI_SendData(0x80,1);
    
    /* Memory Access Control */
    DBI_SendCommand(0x36);
    DBI_SendData(0x08,1);
    
    /* Interface Pixel Format */
    DBI_SendCommand(0x3A);
    DBI_SendData(0x66,1);//RGB666
    //DBI_SendData(0x55,1);//RGB565
    
    /* Interface Mode Control */
    DBI_SendCommand(0xB0);
    DBI_SendData(0x00,1);
    
    /* Frame rate 70Hz */
    DBI_SendCommand(0xB1);
    DBI_SendData(0xB0,1);
    
    /* Display Inversion Control */
    DBI_SendCommand(0xB4);
    DBI_SendData(0x02,1);
    
    /* Display Function Control */
    DBI_SendCommand(0xB6);
    DBI_SendData(0x02,1);
    DBI_SendData(0x22,1);
    
    /* Set Image Function */
    DBI_SendCommand(0xE9);
    DBI_SendData(0x00,1);
    
    /* Adjust Control 3 */
    DBI_SendCommand(0xF7);
    DBI_SendData(0xA9,1);
    DBI_SendData(0x51,1);
    DBI_SendData(0x2C,1);
    DBI_SendData(0x82,1);
    
    /* Sleep Out */
    DBI_SendCommand(0x11);
    
    ARCH_Delay_MS(120);
    
    /* Display On */
    DBI_SendCommand(0x29);
}

/****************************************************************************//**
 * @brief  SPI LCD DPI init
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void LCD_DPI_Init(void)
{
    /* Reset */
    //DBI_ILI9488_RESET_HIGH;
    //ARCH_Delay_MS(1);
    //DBI_ILI9488_RESET_LOW;
    //ARCH_Delay_MS(10);
    //DBI_ILI9488_RESET_HIGH;
    //ARCH_Delay_MS(120);
    
    /* PGAMCTRL (Positive Gamma Control) */
    DBI_SendCommand(0xe0);
    DBI_SendData(0x00,1);
    DBI_SendData(0x07,1);
    DBI_SendData(0x0f,1);
    DBI_SendData(0x07,1);
    DBI_SendData(0x15,1);
    DBI_SendData(0x09,1);
    DBI_SendData(0x3c,1);
    DBI_SendData(0x99,1);
    DBI_SendData(0x4b,1);
    DBI_SendData(0x09,1);
    DBI_SendData(0x10,1);
    DBI_SendData(0x0d,1);
    DBI_SendData(0x1c,1);
    DBI_SendData(0x1e,1);
    DBI_SendData(0x0f,1);
    
    /* NGAMCTRL (Negative Gamma Control) */
    DBI_SendCommand(0xe1);
    DBI_SendData(0x00,1);
    DBI_SendData(0x20,1);
    DBI_SendData(0x23,1);
    DBI_SendData(0x02,1);
    DBI_SendData(0x0f,1);
    DBI_SendData(0x06,1);
    DBI_SendData(0x34,1);
    DBI_SendData(0x45,1);
    DBI_SendData(0x43,1);
    DBI_SendData(0x04,1);
    DBI_SendData(0x0a,1);
    DBI_SendData(0x08,1);
    DBI_SendData(0x30,1);
    DBI_SendData(0x37,1);
    DBI_SendData(0x0f,1);
    
    /* Power Control 1 */
    DBI_SendCommand(0xc0);
    DBI_SendData(0x10,1);
    DBI_SendData(0x10,1);
    
    /* Power Control 2 */
    DBI_SendCommand(0xc1);
    DBI_SendData(0x41,1);
    
    /* VCOM Control */
    DBI_SendCommand(0xc5);
    DBI_SendData(0x00,1);
    DBI_SendData(0x20,1);
    DBI_SendData(0xd0,1);
    
    /* Memory Access Control */
    DBI_SendCommand(0x36);
    DBI_SendData(0x08,1);
    //DBI_SendData(0x68,1);
    
    /* Interface Pixel Format */
    DBI_SendCommand(0x3a);
    DBI_SendData(0x50,1);
    
    /* Interface Mode Control */
    DBI_SendCommand(0xb0);
    DBI_SendData(0x00,1);
    
    /* Frame rate 60Hz */
    DBI_SendCommand(0xb1);
    DBI_SendData(0xa0,1);
    DBI_SendData(0x11,1);
    
    /* Display Inversion Control */
    DBI_SendCommand(0xb4);
    DBI_SendData(0x02,1);
    
    /* Display Function Control */
    DBI_SendCommand(0xb6);
    DBI_SendData(0xb0,1);
    DBI_SendData(0x02,1);
    
    DBI_SendCommand(0xbe);
    DBI_SendData(0x00,1);
    DBI_SendData(0x04,1);
    
    /* Set Image Function */
    DBI_SendCommand(0xe9);
    DBI_SendData(0x00,1);
    
    /* Adjust Control 3 */
    DBI_SendCommand(0xf7);
    DBI_SendData(0xa9,1);
    DBI_SendData(0x51,1);
    DBI_SendData(0x2c,1);
    DBI_SendData(0x82,1);
    
    /* Sleep Out */
    DBI_SendCommand(0x11);
    
    ARCH_Delay_MS(120);
    
    /* Display On */
    DBI_SendCommand(0x29);
}

/****************************************************************************//**
 * @brief  LCD set address
 *
 * @param  x1: Coordinate x start
 * @param  y1: Coordinate y start
 * @param  x2: Coordinate x end
 * @param  y2: Coordinate y end
 *
 * @return None
 *
*******************************************************************************/
void LCD_Set_Addr(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{ 
   DBI_SendCommand(0x2A);
   DBI_SendData((x1<<16)+x2,4);
   DBI_SendCommand(0x2B);
   DBI_SendData((y1<<16)+y2,4);
   DBI_SendCommand(0x2C);
}


/****************************************************************************//**
 * @brief  LCD clear display
 *
 * @param  color: Color to fill
 *
 * @return None
 *
*******************************************************************************/
void LCD_Clear(uint32_t color)
{
    LCD_Set_Addr(0,0,LCD_W-1,LCD_H-1);
    DBI_SendSinglePixel(color,LCD_W*LCD_H);
}


/****************************************************************************//**
 * @brief  LCD clear display with DMA
 *
 * @param  sourceAddr: Source address of data
 *
 * @return None
 *
*******************************************************************************/
void LCD_DMA_Clear(uint32_t sourceAddr)
{
    uint32_t i;
    
    DMA_Channel_Cfg_Type dmaChCfg = {
        .srcDmaAddr = sourceAddr,
        .destDmaAddr = DBI_BASE+DBI_FIFO_WDATA_OFFSET,
        .transfLength = 3200,
        .dir = DMA_TRNS_M2P,
        .ch = DMA_CH0,
        .srcTransfWidth = DMA_TRNS_WIDTH_32BITS,
        .dstTransfWidth = DMA_TRNS_WIDTH_32BITS,
        .srcBurstSize = DMA_BURST_SIZE_1,
        .dstBurstSize = DMA_BURST_SIZE_1,
        .dstAddMode = DISABLE,
        .dstMinMode = DISABLE,
        .fixCnt = 0,
        .srcAddrInc = 0,
        .destAddrInc = 0,
        .srcPeriph = DMA_REQ_NONE,
        .dstPeriph = DMA_REQ_DBI_TX,
    };
    
    LCD_Set_Addr(0,0,LCD_W-1,LCD_H-1);
    DBI_SetPixel(3200);
    DBI_SetTxFifoThreshold(4);
    DBI_SetDMA(ENABLE);
    
    DBI_IntClear();
    
    for(i=0;i<LCD_W*LCD_H/3200;i++){
        DMA_Channel_Init(DBI_DMA_USE,&dmaChCfg);
        DMA_Enable(DBI_DMA_USE);
        DMA_Channel_Enable(DBI_DMA_USE,DMA_CH0);
        DBI_Enable();
        while(DBI_GetIntStatus(DBI_INT_END) != SET){}
        DBI_Disable();
        DMA_Channel_Disable(DBI_DMA_USE,DMA_CH0);
        DMA_Disable(DBI_DMA_USE);
        DBI_IntClear();
    }
    DBI_SetDMA(DISABLE);
}


/****************************************************************************//**
 * @brief  LCD draw a point
 *
 * @param  x: Coordinate x
 * @param  y: Coordinate y
 * @param  color: Color of the point
 *
 * @return None
 *
*******************************************************************************/
void LCD_DrawPoint(uint16_t x,uint16_t y,uint32_t color)
{
    LCD_Set_Addr(x,y,x,y);
    DBI_SendSinglePixel(color,1);
}


/****************************************************************************//**
 * @brief  LCD draw line
 *
 * @param  x1: Coordinate x start
 * @param  y1: Coordinate y start
 * @param  x2: Coordinate x end
 * @param  y2: Coordinate y end
 * @param  color: Color of the line
 *
 * @return None
 *
*******************************************************************************/
void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint32_t color)
{
    int xVariation,yVariation,temp;
    int absX,absY,i;
    xVariation = x2-x1;
    yVariation = y2-y1;
    absX = ABS32(xVariation);
    absY = ABS32(yVariation);
    
    if(absX > absY){
        for(i=0;i<absX+1;i++){
            temp = yVariation*100/absX*i/100;
            if(xVariation>0){
                LCD_DrawPoint(x1+i,y1+temp,color);
            }else{
                LCD_DrawPoint(x1-i,y1+temp,color);
            }
        }
    }
    else{
        for(i=0;i<absY+1;i++){
            temp = xVariation*100/absY*i/100;
            if(yVariation>0){
                LCD_DrawPoint(x1+temp,y1+i,color);
            }else{
                LCD_DrawPoint(x1+temp,y1-i,color);
            }
        }
    }
}


/****************************************************************************//**
 * @brief  LCD draw rectangle
 *
 * @param  x1: Coordinate x start
 * @param  y1: Coordinate y start
 * @param  x2: Coordinate x end
 * @param  y2: Coordinate y end
 * @param  color: Color of the rectangle
 *
 * @return None
 *
*******************************************************************************/
void LCD_DrawRectangle(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint32_t color)
{
    LCD_DrawLine(x1,y1,x2,y1,color);
    LCD_DrawLine(x2,y1,x2,y2,color);
    LCD_DrawLine(x2,y2,x1,y2,color);
    LCD_DrawLine(x1,y2,x1,y1,color);
}


/****************************************************************************//**
 * @brief  LCD draw circle
 *
 * @param  x: Center coordinate x
 * @param  y: Center coordinate y
 * @param  r: Radius
 * @param  color: Color of the circle
 *
 * @return None
 *
*******************************************************************************/
void LCD_DrawCircle(uint16_t x,uint16_t y,uint16_t r,uint32_t color)
{
    int a = 0,b;
    int di;
    b = r;
    di = 3-(r<<1);
    while(a <= b)
    {
        LCD_DrawPoint(x-b,y-a,color);
        LCD_DrawPoint(x+b,y-a,color);
        LCD_DrawPoint(x-a,y+b,color);
        LCD_DrawPoint(x-b,y-a,color);
        LCD_DrawPoint(x-a,y-b,color);
        LCD_DrawPoint(x+b,y+a,color);
        LCD_DrawPoint(x+a,y-b,color);
        LCD_DrawPoint(x+a,y+b,color);
        LCD_DrawPoint(x-b,y+a,color);
        a++;
        if(di<0){
            di += 4*a+6;
        }else{
            di += 10+4*(a-b);
            b--;
        }
        LCD_DrawPoint(x+a,y+b,color);
    }
}


/****************************************************************************//**
 * @brief  LCD fill the area with color
 *
 * @param  x1: Coordinate x start
 * @param  y1: Coordinate y start
 * @param  x2: Coordinate x end
 * @param  y2: Coordinate y end
 * @param  color: Color to fill
 *
 * @return None
 *
*******************************************************************************/
void LCD_DrawArea(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint32_t color)
{
    LCD_Set_Addr(x1,y1,x2,y2);
    DBI_SendSinglePixel(color,ABS16((x2-x1+1)*(y2-y1+1)));
}


/****************************************************************************//**
 * @brief  LCD draw picture
 *
 * @param  x1: Coordinate x start
 * @param  y1: Coordinate y start
 * @param  x2: Coordinate x end
 * @param  y2: Coordinate y end
 * @param  picture: Color array of the picture
 *
 * @return None
 *
*******************************************************************************/
void LCD_DrawPicture(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint32_t* picture)
{
    LCD_Set_Addr(x1,y1,x2,y2);
    DBI_SendVariousPixel(picture,ABS16((x2-x1+1)*(y2-y1+1)));
}


/****************************************************************************//**
 * @brief  LCD draw picture with DMA
 *
 * @param  x1: Coordinate x start
 * @param  y1: Coordinate y start
 * @param  x2: Coordinate x end
 * @param  y2: Coordinate y end
 * @param  picture: Color array of the picture
 *
 * @return None
 *
*******************************************************************************/
void LCD_DMA_DrawPicture(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint32_t* picture)
{
    uint32_t i=0;
    uint32_t tmpVal = (x2+1-x1)*(y2+1-y1)/3200;
    
    DMA_Channel_Cfg_Type dmaChCfg = {
        .srcDmaAddr = (uint32_t)(uintptr_t)picture,
        .destDmaAddr = DBI_BASE+DBI_FIFO_WDATA_OFFSET,
        .transfLength = 3200,
        .dir = DMA_TRNS_M2P,
        .ch = DMA_CH0,
        .srcTransfWidth = DMA_TRNS_WIDTH_32BITS,
        .dstTransfWidth = DMA_TRNS_WIDTH_32BITS,
        .srcBurstSize = DMA_BURST_SIZE_1,
        .dstBurstSize = DMA_BURST_SIZE_1,
        .dstAddMode = DISABLE,
        .dstMinMode = DISABLE,
        .fixCnt = 0,
        .srcAddrInc = 1,
        .destAddrInc = 0,
        .srcPeriph = DMA_REQ_NONE,
        .dstPeriph = DMA_REQ_DBI_TX,
    };
    
    LCD_Set_Addr(x1,y1,x2,y2);
    DBI_SetTxFifoThreshold(4);
    DBI_SetDMA(ENABLE);
    DBI_IntClear();
    
    for(i=0;i<tmpVal;i++){
        DBI_SetPixel(3200);
        dmaChCfg.srcDmaAddr = (uint32_t)(uintptr_t)picture+3200*4*i;
        dmaChCfg.transfLength = 3200;
        DMA_Channel_Init(DBI_DMA_USE,&dmaChCfg);
        DMA_Enable(DBI_DMA_USE);
        DMA_Channel_Enable(DBI_DMA_USE,DMA_CH0);
        DBI_Enable();
        while(DBI_GetIntStatus(DBI_INT_END) != SET){
        }
        DBI_Disable();
        DMA_Channel_Disable(DBI_DMA_USE,DMA_CH0);
        DMA_Disable(DBI_DMA_USE);
        DBI_IntClear();
    }
    
    tmpVal = (x2+1-x1)*(y2+1-y1)%3200;
    if(tmpVal){
        DBI_SetPixel(tmpVal);
        dmaChCfg.srcDmaAddr = (uint32_t)(uintptr_t)picture+3200*4*i;
        dmaChCfg.transfLength = tmpVal;
        DMA_Channel_Init(DBI_DMA_USE,&dmaChCfg);
        DMA_Enable(DBI_DMA_USE);
        DMA_Channel_Enable(DBI_DMA_USE,DMA_CH0);
        DBI_Enable();
        while(DBI_GetIntStatus(DBI_INT_END) != SET){
        }
        DBI_Disable();
        DMA_Channel_Disable(DBI_DMA_USE,DMA_CH0);
        DMA_Disable(DBI_DMA_USE);
        DBI_IntClear();
    }
    
    DBI_SetDMA(DISABLE);
}


/****************************************************************************//**
 * @brief  LCD draw a 32*32 chinese character in lattice mode
 *
 * @param  x: Coordinate x
 * @param  y: Coordinate y
 * @param  character: Array of the character
 * @param  bColor: Color of the background
 * @param  cColor: Color of the character
 *
 * @return None
 *
*******************************************************************************/
void LCD_DrawChinese(uint16_t x,uint16_t y,uint8_t* character,uint32_t bColor,uint32_t cColor)
{
    uint8_t i,j;
    LCD_Set_Addr(x,y,x+31,y+31);
    for(j=0;j<128;j++)
    {
        for(i=0;i<8;i++)
        {
            if((*character&(1<<i)) != 0)
            {
                DBI_SendSinglePixel(cColor,1);
            } 
            else
            {
                DBI_SendSinglePixel(bColor,1);
            }
        }
        character++;
     }
}


/*@} end of group ILI9488_Public_Functions */

/*@} end of group ILI9488 */

/*@} end of group ILI9488_Driver */
