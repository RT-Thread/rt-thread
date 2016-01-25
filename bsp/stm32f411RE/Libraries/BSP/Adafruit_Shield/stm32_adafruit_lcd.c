/**
  ******************************************************************************
  * @file    stm32_adafruit_lcd.c
  * @author  MCD Application Team
  * @version V2.0.1
  * @date    04-November-2015
  * @brief   This file includes the driver for Liquid Crystal Display (LCD) module
  *          mounted on the Adafruit 1.8" TFT LCD shield (reference ID 802), 
  *          that is used with the STM32 Nucleo board through SPI interface.     
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
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

/* File Info : -----------------------------------------------------------------
                                   User NOTES
1. How To use this driver:
--------------------------
   - The LCD st7735 component driver MUST be included with this driver.  

2. Driver description:
---------------------
  + Initialization steps:
     o Initialize the LCD using the BSP_LCD_Init() function.
  
  + Display on LCD
     o Clear the whole LCD using the BSP_LCD_Clear() function or only one specified 
       string line using the BSP_LCD_ClearStringLine() function.
     o Display a character on the specified line and column using the BSP_LCD_DisplayChar()
       function or a complete string line using the BSP_LCD_DisplayStringAtLine() function.
     o Display a string line on the specified position (x,y in pixel) and align mode
       using the BSP_LCD_DisplayStringAtLine() function.          
     o Draw and fill a basic shapes (dot, line, rectangle, circle, ellipse, ..) 
       on LCD using a set of functions.    
 
------------------------------------------------------------------------------*/
    
/* Includes ------------------------------------------------------------------*/
#include "stm32_adafruit_lcd.h"
#include "../../../Utilities/Fonts/fonts.h"
#include "../../../Utilities/Fonts/font24.c"
#include "../../../Utilities/Fonts/font20.c"
#include "../../../Utilities/Fonts/font16.c"
#include "../../../Utilities/Fonts/font12.c"
#include "../../../Utilities/Fonts/font8.c"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32_ADAFRUIT
  * @{
  */
    
/** @addtogroup STM32_ADAFRUIT_LCD
  * @{
  */ 

/** @defgroup STM32_ADAFRUIT_LCD_Private_TypesDefinitions
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup STM32_ADAFRUIT_LCD_Private_Defines
  * @{
  */
#define POLY_X(Z)             ((int32_t)((Points + (Z))->X))
#define POLY_Y(Z)             ((int32_t)((Points + (Z))->Y))
#define NULL                  (void *)0

#define MAX_HEIGHT_FONT         17
#define MAX_WIDTH_FONT          24
#define OFFSET_BITMAP           54
/**
  * @}
  */ 

/** @defgroup STM32_ADAFRUIT_LCD_Private_Macros
  * @{
  */
#define ABS(X) ((X) > 0 ? (X) : -(X)) 

/**
  * @}
  */ 
    
/** @defgroup STM32_ADAFRUIT_LCD_Private_Variables
  * @{
  */ 
LCD_DrawPropTypeDef DrawProp;

static LCD_DrvTypeDef  *lcd_drv; 

/* Max size of bitmap will based on a font24 (17x24) */
static uint8_t bitmap[MAX_HEIGHT_FONT*MAX_WIDTH_FONT*2+OFFSET_BITMAP] = {0};

/**
  * @}
  */ 

/** @defgroup STM32_ADAFRUIT_LCD_Private_FunctionPrototypes
  * @{
  */ 
static void DrawChar(uint16_t Xpos, uint16_t Ypos, const uint8_t *c);
static void FillTriangle(uint16_t x1, uint16_t x2, uint16_t x3, uint16_t y1, uint16_t y2, uint16_t y3);
static void SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
/**
  * @}
  */ 


/** @defgroup STM32_ADAFRUIT_LCD_Private_Functions
  * @{
  */
  
/**
  * @brief  Initializes the LCD.
  * @param  None
  * @retval LCD state
  */
uint8_t BSP_LCD_Init(void)
{ 
  uint8_t ret = LCD_ERROR;
  
  /* Default value for draw propriety */
  DrawProp.BackColor = 0xFFFF;
  DrawProp.pFont     = &Font24;
  DrawProp.TextColor = 0x0000;
  
  lcd_drv = &st7735_drv;
  
  /* LCD Init */   
  lcd_drv->Init();
  
  /* Clear the LCD screen */
  BSP_LCD_Clear(LCD_COLOR_WHITE);
  
  /* Initialize the font */
  BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
  
  ret = LCD_OK;
  
  return ret;
}

/**
  * @brief  Gets the LCD X size.
  * @param  None    
  * @retval Used LCD X size
  */
uint32_t BSP_LCD_GetXSize(void)
{
  return(lcd_drv->GetLcdPixelWidth());
}

/**
  * @brief  Gets the LCD Y size.
  * @param  None   
  * @retval Used LCD Y size
  */
uint32_t BSP_LCD_GetYSize(void)
{
  return(lcd_drv->GetLcdPixelHeight());
}

/**
  * @brief  Gets the LCD text color.
  * @param  None 
  * @retval Used text color.
  */
uint16_t BSP_LCD_GetTextColor(void)
{
  return DrawProp.TextColor;
}

/**
  * @brief  Gets the LCD background color.
  * @param  None
  * @retval Used background color
  */
uint16_t BSP_LCD_GetBackColor(void)
{
  return DrawProp.BackColor;
}

/**
  * @brief  Sets the LCD text color.
  * @param  Color: Text color code RGB(5-6-5)
  * @retval None
  */
void BSP_LCD_SetTextColor(uint16_t Color)
{
  DrawProp.TextColor = Color;
}

/**
  * @brief  Sets the LCD background color.
  * @param  Color: Background color code RGB(5-6-5)
  * @retval None
  */
void BSP_LCD_SetBackColor(uint16_t Color)
{
  DrawProp.BackColor = Color;
}

/**
  * @brief  Sets the LCD text font.
  * @param  fonts: Font to be used
  * @retval None
  */
void BSP_LCD_SetFont(sFONT *pFonts)
{
  DrawProp.pFont = pFonts;
}

/**
  * @brief  Gets the LCD text font.
  * @param  None
  * @retval Used font
  */
sFONT *BSP_LCD_GetFont(void)
{
  return DrawProp.pFont;
}

/**
  * @brief  Clears the hole LCD.
  * @param  Color: Color of the background
  * @retval None
  */
void BSP_LCD_Clear(uint16_t Color)
{ 
  uint32_t counter = 0;
  uint32_t color_backup = DrawProp.TextColor; 
  DrawProp.TextColor = Color;
  
  for(counter = 0; counter < BSP_LCD_GetYSize(); counter++)
  {
    BSP_LCD_DrawHLine(0, counter, BSP_LCD_GetXSize());
  }
  DrawProp.TextColor = color_backup; 
  BSP_LCD_SetTextColor(DrawProp.TextColor);
}

/**
  * @brief  Clears the selected line.
  * @param  Line: Line to be cleared
  *          This parameter can be one of the following values:
  *            @arg  0..9: if the Current fonts is Font16x24
  *            @arg  0..19: if the Current fonts is Font12x12 or Font8x12
  *            @arg  0..29: if the Current fonts is Font8x8
  * @retval None
  */
void BSP_LCD_ClearStringLine(uint16_t Line)
{ 
  uint32_t color_backup = DrawProp.TextColor; 
  DrawProp.TextColor = DrawProp.BackColor;;
    
  /* Draw a rectangle with background color */
  BSP_LCD_FillRect(0, (Line * DrawProp.pFont->Height), BSP_LCD_GetXSize(), DrawProp.pFont->Height);
  
  DrawProp.TextColor = color_backup;
  BSP_LCD_SetTextColor(DrawProp.TextColor);
}

/**
  * @brief  Displays one character.
  * @param  Xpos: Start column address
  * @param  Ypos: Line where to display the character shape.
  * @param  Ascii: Character ascii code
  *           This parameter must be a number between Min_Data = 0x20 and Max_Data = 0x7E 
  * @retval None
  */
void BSP_LCD_DisplayChar(uint16_t Xpos, uint16_t Ypos, uint8_t Ascii)
{
  DrawChar(Xpos, Ypos, &DrawProp.pFont->table[(Ascii-' ') *\
    DrawProp.pFont->Height * ((DrawProp.pFont->Width + 7) / 8)]);
}

/**
  * @brief  Displays characters on the LCD.
  * @param  Xpos: X position (in pixel)
  * @param  Ypos: Y position (in pixel)   
  * @param  Text: Pointer to string to display on LCD
  * @param  Mode: Display mode
  *          This parameter can be one of the following values:
  *            @arg  CENTER_MODE
  *            @arg  RIGHT_MODE
  *            @arg  LEFT_MODE   
  * @retval None
  */
void BSP_LCD_DisplayStringAt(uint16_t Xpos, uint16_t Ypos, uint8_t *Text, Line_ModeTypdef Mode)
{
  uint16_t refcolumn = 1, i = 0;
  uint32_t size = 0, xsize = 0; 
  uint8_t  *ptr = Text;
  
  /* Get the text size */
  while (*ptr++) size ++ ;
  
  /* Characters number per line */
  xsize = (BSP_LCD_GetXSize()/DrawProp.pFont->Width);
  
  switch (Mode)
  {
  case CENTER_MODE:
    {
      refcolumn = Xpos + ((xsize - size)* DrawProp.pFont->Width) / 2;
      break;
    }
  case LEFT_MODE:
    {
      refcolumn = Xpos;
      break;
    }
  case RIGHT_MODE:
    {
      refcolumn =  - Xpos + ((xsize - size)*DrawProp.pFont->Width);
      break;
    }    
  default:
    {
      refcolumn = Xpos;
      break;
    }
  }
  
  /* Send the string character by character on lCD */
  while ((*Text != 0) & (((BSP_LCD_GetXSize() - (i*DrawProp.pFont->Width)) & 0xFFFF) >= DrawProp.pFont->Width))
  {
    /* Display one character on LCD */
    BSP_LCD_DisplayChar(refcolumn, Ypos, *Text);
    /* Decrement the column position by 16 */
    refcolumn += DrawProp.pFont->Width;
    /* Point on the next character */
    Text++;
    i++;
  }
}

/**
  * @brief  Displays a character on the LCD.
  * @param  Line: Line where to display the character shape
  *          This parameter can be one of the following values:
  *            @arg  0..19: if the Current fonts is Font8
  *            @arg  0..12: if the Current fonts is Font12
  *            @arg  0...9: if the Current fonts is Font16
  *            @arg  0...7: if the Current fonts is Font20
  *            @arg  0...5: if the Current fonts is Font24
  * @param  ptr: Pointer to string to display on LCD
  * @retval None
  */
void BSP_LCD_DisplayStringAtLine(uint16_t Line, uint8_t *ptr)
{
  BSP_LCD_DisplayStringAt(0, LINE(Line), ptr, LEFT_MODE);
}

/**
  * @brief  Draws a pixel on LCD.
  * @param  Xpos: X position 
  * @param  Ypos: Y position
  * @param  RGB_Code: Pixel color in RGB mode (5-6-5)  
  * @retval None
  */
void BSP_LCD_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGB_Code)
{
  if(lcd_drv->WritePixel != NULL)
  {
    lcd_drv->WritePixel(Xpos, Ypos, RGB_Code);
  }
}
  
/**
  * @brief  Draws an horizontal line.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  Length: Line length
  * @retval None
  */
void BSP_LCD_DrawHLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
  uint32_t index = 0;
  
  if(lcd_drv->DrawHLine != NULL)
  {
    lcd_drv->DrawHLine(DrawProp.TextColor, Xpos, Ypos, Length);
  }
  else
  {
    for(index = 0; index < Length; index++)
    {
      BSP_LCD_DrawPixel((Xpos + index), Ypos, DrawProp.TextColor);
    }
  }
}

/**
  * @brief  Draws a vertical line.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  Length: Line length
  * @retval None
  */
void BSP_LCD_DrawVLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
  uint32_t index = 0;
  
  if(lcd_drv->DrawVLine != NULL)
  {
    lcd_drv->DrawVLine(DrawProp.TextColor, Xpos, Ypos, Length);
  }
  else
  {
    for(index = 0; index < Length; index++)
    {
      BSP_LCD_DrawPixel(Xpos, Ypos + index, DrawProp.TextColor);
    }
  }
}

/**
  * @brief  Draws an uni-line (between two points).
  * @param  x1: Point 1 X position
  * @param  y1: Point 1 Y position
  * @param  x2: Point 2 X position
  * @param  y2: Point 2 Y position
  * @retval None
  */
void BSP_LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0, 
  curpixel = 0;
  
  deltax = ABS(x2 - x1);        /* The difference between the x's */
  deltay = ABS(y2 - y1);        /* The difference between the y's */
  x = x1;                       /* Start x off at the first pixel */
  y = y1;                       /* Start y off at the first pixel */
  
  if (x2 >= x1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }
  
  if (y2 >= y1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }
  
  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    numadd = deltay;
    numpixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    numadd = deltax;
    numpixels = deltay;         /* There are more y-values than x-values */
  }
  
  for (curpixel = 0; curpixel <= numpixels; curpixel++)
  {
    BSP_LCD_DrawPixel(x, y, DrawProp.TextColor);  /* Draw the current pixel */
    num += numadd;                            /* Increase the numerator by the top of the fraction */
    if (num >= den)                           /* Check if numerator >= denominator */
    {
      num -= den;                             /* Calculate the new numerator value */
      x += xinc1;                             /* Change the x as appropriate */
      y += yinc1;                             /* Change the y as appropriate */
    }
    x += xinc2;                               /* Change the x as appropriate */
    y += yinc2;                               /* Change the y as appropriate */
  }
}

/**
  * @brief  Draws a rectangle.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  Width: Rectangle width  
  * @param  Height: Rectangle height
  * @retval None
  */
void BSP_LCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  /* Draw horizontal lines */
  BSP_LCD_DrawHLine(Xpos, Ypos, Width);
  BSP_LCD_DrawHLine(Xpos, (Ypos+ Height), Width);
  
  /* Draw vertical lines */
  BSP_LCD_DrawVLine(Xpos, Ypos, Height);
  BSP_LCD_DrawVLine((Xpos + Width), Ypos, Height);
}
                            
/**
  * @brief  Draws a circle.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  Radius: Circle radius
  * @retval None
  */
void BSP_LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  int32_t  D;       /* Decision Variable */ 
  uint32_t  CurX;   /* Current X Value */
  uint32_t  CurY;   /* Current Y Value */ 
  
  D = 3 - (Radius << 1);
  CurX = 0;
  CurY = Radius;
  
  while (CurX <= CurY)
  {
    BSP_LCD_DrawPixel((Xpos + CurX), (Ypos - CurY), DrawProp.TextColor);

    BSP_LCD_DrawPixel((Xpos - CurX), (Ypos - CurY), DrawProp.TextColor);

    BSP_LCD_DrawPixel((Xpos + CurY), (Ypos - CurX), DrawProp.TextColor);

    BSP_LCD_DrawPixel((Xpos - CurY), (Ypos - CurX), DrawProp.TextColor);

    BSP_LCD_DrawPixel((Xpos + CurX), (Ypos + CurY), DrawProp.TextColor);

    BSP_LCD_DrawPixel((Xpos - CurX), (Ypos + CurY), DrawProp.TextColor);

    BSP_LCD_DrawPixel((Xpos + CurY), (Ypos + CurX), DrawProp.TextColor);

    BSP_LCD_DrawPixel((Xpos - CurY), (Ypos + CurX), DrawProp.TextColor);   

    /* Initialize the font */
    BSP_LCD_SetFont(&LCD_DEFAULT_FONT);

    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  } 
}

/**
  * @brief  Draws an poly-line (between many points).
  * @param  Points: Pointer to the points array
  * @param  PointCount: Number of points
  * @retval None
  */
void BSP_LCD_DrawPolygon(pPoint Points, uint16_t PointCount)
{
  int16_t X = 0, Y = 0;

  if(PointCount < 2)
  {
    return;
  }

  BSP_LCD_DrawLine(Points->X, Points->Y, (Points+PointCount-1)->X, (Points+PointCount-1)->Y);
  
  while(--PointCount)
  {
    X = Points->X;
    Y = Points->Y;
    Points++;
    BSP_LCD_DrawLine(X, Y, Points->X, Points->Y);
  }
}

/**
  * @brief  Draws an ellipse on LCD.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  XRadius: Ellipse X radius
  * @param  YRadius: Ellipse Y radius
  * @retval None
  */
void BSP_LCD_DrawEllipse(int Xpos, int Ypos, int XRadius, int YRadius)
{
  int x = 0, y = -YRadius, err = 2-2*XRadius, e2;
  float K = 0, rad1 = 0, rad2 = 0;
  
  rad1 = XRadius;
  rad2 = YRadius;
  
  K = (float)(rad2/rad1);
  
  do {      
    BSP_LCD_DrawPixel((Xpos-(uint16_t)(x/K)), (Ypos+y), DrawProp.TextColor);
    BSP_LCD_DrawPixel((Xpos+(uint16_t)(x/K)), (Ypos+y), DrawProp.TextColor);
    BSP_LCD_DrawPixel((Xpos+(uint16_t)(x/K)), (Ypos-y), DrawProp.TextColor);
    BSP_LCD_DrawPixel((Xpos-(uint16_t)(x/K)), (Ypos-y), DrawProp.TextColor);      
    
    e2 = err;
    if (e2 <= x) {
      err += ++x*2+1;
      if (-y == x && e2 <= y) e2 = 0;
    }
    if (e2 > y) err += ++y*2+1;     
  }
  while (y <= 0);
}

/**
  * @brief  Draws a bitmap picture loaded in the STM32 MCU internal memory.
  * @param  Xpos: Bmp X position in the LCD
  * @param  Ypos: Bmp Y position in the LCD
  * @param  pBmp: Pointer to Bmp picture address
  * @retval None
  */
void BSP_LCD_DrawBitmap(uint16_t Xpos, uint16_t Ypos, uint8_t *pBmp)
{
  uint32_t height = 0, width  = 0;
  
  /* Read bitmap width */
  width = *(uint16_t *) (pBmp + 18);
  width |= (*(uint16_t *) (pBmp + 20)) << 16;
  
  /* Read bitmap height */
  height = *(uint16_t *) (pBmp + 22);
  height |= (*(uint16_t *) (pBmp + 24)) << 16; 
  
  /* Remap Ypos, st7735 works with inverted X in case of bitmap */
  /* X = 0, cursor is on Top corner */
  if(lcd_drv == &st7735_drv)
  {
    Ypos = BSP_LCD_GetYSize() - Ypos - height;
  }
  
  SetDisplayWindow(Xpos, Ypos, width, height);
  
  if(lcd_drv->DrawBitmap != NULL)
  {
    lcd_drv->DrawBitmap(Xpos, Ypos, pBmp);
  } 
  SetDisplayWindow(0, 0, BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
}

/**
  * @brief  Draws a full rectangle.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  Width: Rectangle width  
  * @param  Height: Rectangle height
  * @retval None
  */
void BSP_LCD_FillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  BSP_LCD_SetTextColor(DrawProp.TextColor);
  do
  {
    BSP_LCD_DrawHLine(Xpos, Ypos++, Width);    
  }
  while(Height--);
}

/**
  * @brief  Draws a full circle.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  Radius: Circle radius
  * @retval None
  */
void BSP_LCD_FillCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  int32_t  D;        /* Decision Variable */ 
  uint32_t  CurX;    /* Current X Value */
  uint32_t  CurY;    /* Current Y Value */ 
  
  D = 3 - (Radius << 1);

  CurX = 0;
  CurY = Radius;
  
  BSP_LCD_SetTextColor(DrawProp.TextColor);

  while (CurX <= CurY)
  {
    if(CurY > 0) 
    {
      BSP_LCD_DrawHLine(Xpos - CurY, Ypos + CurX, 2*CurY);
      BSP_LCD_DrawHLine(Xpos - CurY, Ypos - CurX, 2*CurY);
    }

    if(CurX > 0) 
    {
      BSP_LCD_DrawHLine(Xpos - CurX, Ypos - CurY, 2*CurX);
      BSP_LCD_DrawHLine(Xpos - CurX, Ypos + CurY, 2*CurX);
    }
    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }

  BSP_LCD_SetTextColor(DrawProp.TextColor);
  BSP_LCD_DrawCircle(Xpos, Ypos, Radius);
}

/**
  * @brief  Draws a full poly-line (between many points).
  * @param  Points: Pointer to the points array
  * @param  PointCount: Number of points
  * @retval None
  */
void BSP_LCD_FillPolygon(pPoint Points, uint16_t PointCount)
{
  int16_t X = 0, Y = 0, X2 = 0, Y2 = 0, X_center = 0, Y_center = 0, X_first = 0, Y_first = 0, pixelX = 0, pixelY = 0, counter = 0;
  uint16_t  IMAGE_LEFT = 0, IMAGE_RIGHT = 0, IMAGE_TOP = 0, IMAGE_BOTTOM = 0;  
  
  IMAGE_LEFT = IMAGE_RIGHT = Points->X;
  IMAGE_TOP= IMAGE_BOTTOM = Points->Y;
  
  for(counter = 1; counter < PointCount; counter++)
  {
    pixelX = POLY_X(counter);
    if(pixelX < IMAGE_LEFT)
    {
      IMAGE_LEFT = pixelX;
    }
    if(pixelX > IMAGE_RIGHT)
    {
      IMAGE_RIGHT = pixelX;
    }
    
    pixelY = POLY_Y(counter);
    if(pixelY < IMAGE_TOP)
    {
      IMAGE_TOP = pixelY;
    }
    if(pixelY > IMAGE_BOTTOM)
    {
      IMAGE_BOTTOM = pixelY;
    }
  }  
  
  if(PointCount < 2)
  {
    return;
  }
  
  X_center = (IMAGE_LEFT + IMAGE_RIGHT)/2;
  Y_center = (IMAGE_BOTTOM + IMAGE_TOP)/2;
  
  X_first = Points->X;
  Y_first = Points->Y;
  
  while(--PointCount)
  {
    X = Points->X;
    Y = Points->Y;
    Points++;
    X2 = Points->X;
    Y2 = Points->Y;    
    
    FillTriangle(X, X2, X_center, Y, Y2, Y_center);
    FillTriangle(X, X_center, X2, Y, Y_center, Y2);
    FillTriangle(X_center, X2, X, Y_center, Y2, Y);   
  }
  
  FillTriangle(X_first, X2, X_center, Y_first, Y2, Y_center);
  FillTriangle(X_first, X_center, X2, Y_first, Y_center, Y2);
  FillTriangle(X_center, X2, X_first, Y_center, Y2, Y_first);   
}

/**
  * @brief  Draws a full ellipse.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  XRadius: Ellipse X radius
  * @param  YRadius: Ellipse Y radius  
  * @retval None
  */
void BSP_LCD_FillEllipse(int Xpos, int Ypos, int XRadius, int YRadius)
{
  int x = 0, y = -YRadius, err = 2-2*XRadius, e2;
  float K = 0, rad1 = 0, rad2 = 0;
  
  rad1 = XRadius;
  rad2 = YRadius;
  
  K = (float)(rad2/rad1);    
  
  do 
  { 
    BSP_LCD_DrawHLine((Xpos-(uint16_t)(x/K)), (Ypos+y), (2*(uint16_t)(x/K) + 1));
    BSP_LCD_DrawHLine((Xpos-(uint16_t)(x/K)), (Ypos-y), (2*(uint16_t)(x/K) + 1));
    
    e2 = err;
    if (e2 <= x) 
    {
      err += ++x*2+1;
      if (-y == x && e2 <= y) e2 = 0;
    }
    if (e2 > y) err += ++y*2+1;
  }
  while (y <= 0);
}

/**
  * @brief  Enables the display.
  * @param  None
  * @retval None
  */
void BSP_LCD_DisplayOn(void)
{
  lcd_drv->DisplayOn();
}

/**
  * @brief  Disables the display.
  * @param  None
  * @retval None
  */
void BSP_LCD_DisplayOff(void)
{
  lcd_drv->DisplayOff();
}

/*******************************************************************************
                            Static Functions
*******************************************************************************/

/**
  * @brief  Draws a character on LCD.
  * @param  Xpos: Line where to display the character shape
  * @param  Ypos: Start column address
  * @param  pChar: Pointer to the character data
  * @retval None
  */
static void DrawChar(uint16_t Xpos, uint16_t Ypos, const uint8_t *pChar)
{
  uint32_t counterh = 0, counterw = 0, index = 0;
  uint16_t height = 0, width = 0;
  uint8_t offset = 0;
  uint8_t *pchar = NULL;
  uint32_t line = 0;
  
  height = DrawProp.pFont->Height;
  width  = DrawProp.pFont->Width;
  
  /* Fill bitmap header*/
  *(uint16_t *) (bitmap + 2) = (uint16_t)(height*width*2+OFFSET_BITMAP);
  *(uint16_t *) (bitmap + 4) = (uint16_t)((height*width*2+OFFSET_BITMAP)>>16);
  *(uint16_t *) (bitmap + 10) = OFFSET_BITMAP;
  *(uint16_t *) (bitmap + 18) = (uint16_t)(width);
  *(uint16_t *) (bitmap + 20) = (uint16_t)((width)>>16);
  *(uint16_t *) (bitmap + 22) = (uint16_t)(height);
  *(uint16_t *) (bitmap + 24) = (uint16_t)((height)>>16);
  
  offset =  8 *((width + 7)/8) - width ;
  
  for(counterh = 0; counterh < height; counterh++)
  {
    pchar = ((uint8_t *)pChar + (width + 7)/8 * counterh);
    
    if(((width + 7)/8) == 3)
    {
      line =  (pchar[0]<< 16) | (pchar[1]<< 8) | pchar[2];
    }
    
    if(((width + 7)/8) == 2)
    {
      line =  (pchar[0]<< 8) | pchar[1];
    }
    
    if(((width + 7)/8) == 1)
    {
      line =  pchar[0];
    }    
    
    for (counterw = 0; counterw < width; counterw++)
    {
      /* Image in the bitmap is written from the bottom to the top */
      /* Need to invert image in the bitmap */
      index = (((height-counterh-1)*width)+(counterw))*2+OFFSET_BITMAP;
      if(line & (1 << (width- counterw + offset- 1))) 
      {
        bitmap[index] = (uint8_t)DrawProp.TextColor;
        bitmap[index+1] = (uint8_t)(DrawProp.TextColor >> 8);
      }
      else
      {
        bitmap[index] = (uint8_t)DrawProp.BackColor;
        bitmap[index+1] = (uint8_t)(DrawProp.BackColor >> 8);
      } 
    }
  }
  
  BSP_LCD_DrawBitmap(Xpos, Ypos, bitmap);
}

/**
  * @brief  Fills a triangle (between 3 points).
  * @param  Points: Pointer to the points array
  * @param  x1: Point 1 X position
  * @param  y1: Point 1 Y position
  * @param  x2: Point 2 X position
  * @param  y2: Point 2 Y position
  * @param  x3: Point 3 X position
  * @param  y3: Point 3 Y position
  * @retval None
  */
static void FillTriangle(uint16_t x1, uint16_t x2, uint16_t x3, uint16_t y1, uint16_t y2, uint16_t y3)
{ 
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0, 
  curpixel = 0;
  
  deltax = ABS(x2 - x1);        /* The difference between the x's */
  deltay = ABS(y2 - y1);        /* The difference between the y's */
  x = x1;                       /* Start x off at the first pixel */
  y = y1;                       /* Start y off at the first pixel */
  
  if (x2 >= x1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }
  
  if (y2 >= y1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }
  
  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    numadd = deltay;
    numpixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    numadd = deltax;
    numpixels = deltay;         /* There are more y-values than x-values */
  }
  
  for (curpixel = 0; curpixel <= numpixels; curpixel++)
  {
    BSP_LCD_DrawLine(x, y, x3, y3);
    
    num += numadd;              /* Increase the numerator by the top of the fraction */
    if (num >= den)             /* Check if numerator >= denominator */
    {
      num -= den;               /* Calculate the new numerator value */
      x += xinc1;               /* Change the x as appropriate */
      y += yinc1;               /* Change the y as appropriate */
    }
    x += xinc2;                 /* Change the x as appropriate */
    y += yinc2;                 /* Change the y as appropriate */
  } 
}

/**
  * @brief  Sets display window.
  * @param  LayerIndex: layer index
  * @param  Xpos: LCD X position
  * @param  Ypos: LCD Y position
  * @param  Width: LCD window width
  * @param  Height: LCD window height  
  * @retval None
  */
static void SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  if(lcd_drv->SetDisplayWindow != NULL)
  {
    lcd_drv->SetDisplayWindow(Xpos, Ypos, Width, Height);
  }  
}

/**
  * @}
  */  
  
/**
  * @}
  */ 
  
/**
  * @}
  */     

/**
  * @}
  */  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
