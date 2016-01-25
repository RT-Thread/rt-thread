/**
  ******************************************************************************
  * @file    stm32446e_eval_lcd.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    14-August-2015
  * @brief   This file includes the driver for Liquid Crystal Display (LCD) module
  *          mounted on STM32446E-EVAL evaluation board.
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
   - This driver is used to drive indirectly an LCD TFT.
   - This driver supports the ILI9325 LCD mounted on MB785 daughter board 
   - The ILI9325 component driver MUST be included with this driver.  

2. Driver description:
---------------------
  + Initialization steps:
     o Initialize the LCD using the BSP_LCD_Init() function.
  
  + Display on LCD
     o Clear the hole LCD using BSP_LCD_Clear() function or only one specified string
       line using the BSP_LCD_ClearStringLine() function.
     o Display a character on the specified line and column using the BSP_LCD_DisplayChar()
       function or a complete string line using the BSP_LCD_DisplayStringAtLine() function.
     o Display a string line on the specified position (x,y in pixel) and align mode
       using the BSP_LCD_DisplayStringAtLine() function.          
     o Draw and fill a basic shapes (dot, line, rectangle, circle, ellipse, .. bitmap) 
       on LCD using the available set of functions.     
 
------------------------------------------------------------------------------*/
    
/* Includes ------------------------------------------------------------------*/
#include "stm32446e_eval_lcd.h"  
#include "../../../Utilities/Fonts/fonts.h"
#include "../../../Utilities/Fonts/font24.c"
#include "../../../Utilities/Fonts/font20.c"
#include "../../../Utilities/Fonts/font16.c"
#include "../../../Utilities/Fonts/font12.c"
#include "../../../Utilities/Fonts/font8.c"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32446E_EVAL
  * @{
  */
    
/** @defgroup STM32446E_EVAL_LCD STM32446E-EVAL LCD
  * @{
  */ 

/** @defgroup STM32446E_EVAL_LCD_Private_TypesDefinitions STM32446E Eval Lcd Private TypesDef
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM32446E_EVAL_LCD_Private_Defines STM32446E Eval Lcd Private Defines
  * @{
  */
#define POLY_X(Z)              ((int32_t)((Points + Z)->X))
#define POLY_Y(Z)              ((int32_t)((Points + Z)->Y))      
/**
  * @}
  */ 

/** @defgroup STM32446E_EVAL_LCD_Private_Macros STM32446E Eval Lcd Private Macros
  * @{
  */
#define ABS(X)  ((X) > 0 ? (X) : -(X))      
/**
  * @}
  */ 
    
/** @defgroup STM32446E_EVAL_LCD_Private_Variables STM32446E Eval Lcd Private Variables
  * @{
  */ 
LCD_DrawPropTypeDef DrawProp;
static LCD_DrvTypeDef  *LcdDrv; 
/**
  * @}
  */ 

/** @defgroup STM32446E_EVAL_LCD_Private_FunctionPrototypes STM32446E Eval Lcd Private Prototypes
  * @{
  */ 
static void DrawChar(uint16_t Xpos, uint16_t Ypos, const uint8_t *c);
static void SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
static void FillTriangle(uint16_t x1, uint16_t x2, uint16_t x3, uint16_t y1, uint16_t y2, uint16_t y3);
/**
  * @}
  */ 

/** @defgroup STM32446E_EVAL_LCD_Private_Functions STM32446E Eval Lcd Private Functions
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
  
  if(ili9325_drv.ReadID() == ILI9325_ID)
  {
    LcdDrv = &ili9325_drv;

    /* LCD Init */   
    LcdDrv->Init();
    
    /* Initialize the font */
    BSP_LCD_SetFont(&LCD_DEFAULT_FONT);

    ret = LCD_OK;
  }
  
  return ret;
}

/**
  * @brief  DeInitializes the LCD.
  * @param  None
  * @retval LCD state
  */
uint8_t BSP_LCD_DeInit(void)
{ 
  /* Actually LcdDrv does not provide a DeInit function */
  return LCD_OK;
}

/**
  * @brief  Gets the LCD X size.
  * @param  None    
  * @retval Used LCD X size
  */
uint32_t BSP_LCD_GetXSize(void)
{
  return(LcdDrv->GetLcdPixelWidth());
}

/**
  * @brief  Gets the LCD Y size.
  * @param  None   
  * @retval Used LCD Y size
  */
uint32_t BSP_LCD_GetYSize(void)
{
  return(LcdDrv->GetLcdPixelHeight());
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
void BSP_LCD_SetFont(sFONT *fonts)
{
  DrawProp.pFont = fonts;
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
  uint32_t y_size = 0;
  uint32_t color_backup = DrawProp.TextColor; 

  DrawProp.TextColor = Color;
  y_size =  BSP_LCD_GetYSize();
  
  for(counter = 0; counter < y_size; counter++)
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
  
  /* Check that the Start column is located in the screen */
  if ((refcolumn < 1) || (refcolumn >= 0x8000))
  {
    refcolumn = 1;
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
  *            @arg  0..9: if the Current fonts is Font16x24  
  *            @arg  0..19: if the Current fonts is Font12x12 or Font8x12
  *            @arg  0..29: if the Current fonts is Font8x8
  * @param  ptr: Pointer to string to display on LCD
  * @retval None
  */
void BSP_LCD_DisplayStringAtLine(uint16_t Line, uint8_t *ptr)
{
  BSP_LCD_DisplayStringAt(0, LINE(Line), ptr, LEFT_MODE);
}

/**
  * @brief  Reads an LCD pixel.
  * @param  Xpos: X position 
  * @param  Ypos: Y position 
  * @retval RGB pixel color
  */
uint16_t BSP_LCD_ReadPixel(uint16_t Xpos, uint16_t Ypos)
{
  uint16_t ret = 0;
  
  if(LcdDrv->ReadPixel != NULL)
  {
    ret = LcdDrv->ReadPixel(Xpos, Ypos);
  }
    
  return ret;
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
  if(LcdDrv->WritePixel != NULL)
  {
    LcdDrv->WritePixel(Xpos, Ypos, RGB_Code);
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
  
  if(LcdDrv->DrawHLine != NULL)
  {
    LcdDrv->DrawHLine(DrawProp.TextColor, Xpos, Ypos, Length);
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
  
  if(LcdDrv->DrawVLine != NULL)
  {
    LcdDrv->DrawVLine(DrawProp.TextColor, Xpos, Ypos, Length);
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
  int32_t  decision;       /* Decision Variable */ 
  uint32_t  current_x;   /* Current X Value */
  uint32_t  current_y;   /* Current Y Value */ 
  
  decision = 3 - (Radius << 1);
  current_x = 0;
  current_y = Radius;
  
  while (current_x <= current_y)
  {
    BSP_LCD_DrawPixel((Xpos + current_x), (Ypos - current_y), DrawProp.TextColor);

    BSP_LCD_DrawPixel((Xpos - current_x), (Ypos - current_y), DrawProp.TextColor);

    BSP_LCD_DrawPixel((Xpos + current_y), (Ypos - current_x), DrawProp.TextColor);

    BSP_LCD_DrawPixel((Xpos - current_y), (Ypos - current_x), DrawProp.TextColor);

    BSP_LCD_DrawPixel((Xpos + current_x), (Ypos + current_y), DrawProp.TextColor);

    BSP_LCD_DrawPixel((Xpos - current_x), (Ypos + current_y), DrawProp.TextColor);

    BSP_LCD_DrawPixel((Xpos + current_y), (Ypos + current_x), DrawProp.TextColor);

    BSP_LCD_DrawPixel((Xpos - current_y), (Ypos + current_x), DrawProp.TextColor);   

    /* Initialize the font */
    BSP_LCD_SetFont(&LCD_DEFAULT_FONT);

    if (decision < 0)
    { 
      decision += (current_x << 2) + 6;
    }
    else
    {
      decision += ((current_x - current_y) << 2) + 10;
      current_y--;
    }
    current_x++;
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
  int16_t x = 0, y = 0;

  if(PointCount < 2)
  {
    return;
  }

  BSP_LCD_DrawLine(Points->X, Points->Y, (Points+PointCount-1)->X, (Points+PointCount-1)->Y);
  
  while(--PointCount)
  {
    x = Points->X;
    y = Points->Y;
    Points++;
    BSP_LCD_DrawLine(x, y, Points->X, Points->Y);
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
  float k = 0, rad1 = 0, rad2 = 0;
  
  rad1 = XRadius;
  rad2 = YRadius;
  
  k = (float)(rad2/rad1);
  
  do {      
    BSP_LCD_DrawPixel((Xpos-(uint16_t)(x/k)), (Ypos+y), DrawProp.TextColor);
    BSP_LCD_DrawPixel((Xpos+(uint16_t)(x/k)), (Ypos+y), DrawProp.TextColor);
    BSP_LCD_DrawPixel((Xpos+(uint16_t)(x/k)), (Ypos-y), DrawProp.TextColor);
    BSP_LCD_DrawPixel((Xpos-(uint16_t)(x/k)), (Ypos-y), DrawProp.TextColor);      
    
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
  * @brief  Draws a bitmap picture (16 bpp).
  * @param  Xpos: Bmp X position in the LCD
  * @param  Ypos: Bmp Y position in the LCD
  * @param  pbmp: Pointer to Bmp picture address.
  * @retval None
  */
void BSP_LCD_DrawBitmap(uint16_t Xpos, uint16_t Ypos, uint8_t *pbmp)
{
  uint32_t height = 0;
  uint32_t width  = 0;
  
  
  /* Read bitmap width */
  width = *(uint16_t *) (pbmp + 18);
  width |= (*(uint16_t *) (pbmp + 20)) << 16;
  
  /* Read bitmap height */
  height = *(uint16_t *) (pbmp + 22);
  height |= (*(uint16_t *) (pbmp + 24)) << 16; 
  
  SetDisplayWindow(Xpos, Ypos, width, height);
  
  if(LcdDrv->DrawBitmap != NULL)
  {
    LcdDrv->DrawBitmap(Xpos, Ypos, pbmp);
  } 
  SetDisplayWindow(0, 0, BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
}

/**
  * @brief  Draws RGB Image (16 bpp).
  * @param  Xpos:  X position in the LCD
  * @param  Ypos:  Y position in the LCD
  * @param  Xsize: X size in the LCD
  * @param  Ysize: Y size in the LCD
  * @param  pdata: Pointer to the RGB Image address.
  * @retval None
  */
void BSP_LCD_DrawRGBImage(uint16_t Xpos, uint16_t Ypos, uint16_t Xsize, uint16_t Ysize, uint8_t *pdata)
{
  
  SetDisplayWindow(Xpos, Ypos, Xsize, Ysize);
  
  if(LcdDrv->DrawRGBImage != NULL)
  {
    LcdDrv->DrawRGBImage(Xpos, Ypos, Xsize, Ysize, pdata);
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
  int32_t  decision;        /* Decision Variable */ 
  uint32_t  current_x;    /* Current X Value */
  uint32_t  current_y;    /* Current Y Value */ 
  
  decision = 3 - (Radius << 1);

  current_x = 0;
  current_y = Radius;
  
  BSP_LCD_SetTextColor(DrawProp.TextColor);

  while (current_x <= current_y)
  {
    if(current_y > 0) 
    {
      BSP_LCD_DrawHLine(Xpos - current_y, Ypos + current_x, 2*current_y);
      BSP_LCD_DrawHLine(Xpos - current_y, Ypos - current_x, 2*current_y);
    }

    if(current_x > 0) 
    {
      BSP_LCD_DrawHLine(Xpos - current_x, Ypos - current_y, 2*current_x);
      BSP_LCD_DrawHLine(Xpos - current_x, Ypos + current_y, 2*current_x);
    }
    if (decision < 0)
    { 
      decision += (current_x << 2) + 6;
    }
    else
    {
      decision += ((current_x - current_y) << 2) + 10;
      current_y--;
    }
    current_x++;
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
  float k = 0, rad1 = 0, rad2 = 0;
  
  rad1 = XRadius;
  rad2 = YRadius;
  
  k = (float)(rad2/rad1);    
  
  do 
  { 
    BSP_LCD_DrawHLine((Xpos-(uint16_t)(x/k)), (Ypos+y), (2*(uint16_t)(x/k) + 1));
    BSP_LCD_DrawHLine((Xpos-(uint16_t)(x/k)), (Ypos-y), (2*(uint16_t)(x/k) + 1));
    
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
  LcdDrv->DisplayOn();
}

/**
  * @brief  Disables the display.
  * @param  None
  * @retval None
  */
void BSP_LCD_DisplayOff(void)
{
  LcdDrv->DisplayOff();
}

/******************************************************************************
                            Static Functions
*******************************************************************************/

/**
  * @brief  Draws a character on LCD.
  * @param  Xpos: Line where to display the character shape
  * @param  Ypos: Start column address
  * @param  c: Pointer to the character data
  * @retval None
  */
static void DrawChar(uint16_t Xpos, uint16_t Ypos, const uint8_t *c)
{
  uint32_t i = 0, j = 0;
  uint16_t height, width;
  uint8_t offset;
  uint8_t *pchar;
  uint32_t line;
  
  height = DrawProp.pFont->Height;
  width  = DrawProp.pFont->Width;
  
  offset =  8 *((width + 7)/8) -  width ;
  
  for(i = 0; i < height; i++)
  {
    pchar = ((uint8_t *)c + (width + 7)/8 * i);
    
    switch(((width + 7)/8))
    {
    case 1:
      line =  pchar[0];
      break;    

    case 2:
      line =  (pchar[0]<< 8) | pchar[1];
      break;
      
    case 3:
    default:
      line =  (pchar[0]<< 16) | (pchar[1]<< 8) | pchar[2];
      break;
    }  
    
    for (j = 0; j < width; j++)
    {
      if(line & (1 << (width- j + offset- 1))) 
      {
        BSP_LCD_DrawPixel((Xpos + j), Ypos, DrawProp.TextColor);
      }
      else
      {
        BSP_LCD_DrawPixel((Xpos + j), Ypos, DrawProp.BackColor);
      } 
    }
    Ypos++;
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
  if(LcdDrv->SetDisplayWindow != NULL)
  {
    LcdDrv->SetDisplayWindow(Xpos, Ypos, Width, Height);
  }  
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
