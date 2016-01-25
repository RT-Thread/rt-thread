/**
  ******************************************************************************
  * @file    stm324x9i_eval_lcd.c
  * @author  MCD Application Team
  * @version V2.2.1
  * @date    07-October-2015
  * @brief   This file includes the driver for Liquid Crystal Display (LCD) module
  *          mounted on STM324x9I-EVAL evaluation board.
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

/* File Info: ------------------------------------------------------------------
                                   User NOTES
1. How To use this driver:
--------------------------
   - This driver is used to drive directly an LCD TFT using the LTDC controller.
   - This driver selects dynamically the mounted LCD, AMPIRE 640x480 LCD mounted 
     on MB1063 or AMPIRE 480x272 LCD mounted on MB1046 daughter board, 
     and uses the adequate timing and setting for the specified LCD using 
     device ID of the STMPE811 mounted on MB1046 daughter board.          

2. Driver description:
---------------------
  + Initialization steps:
     o Initialize the LCD using the BSP_LCD_Init() function.
     o Apply the Layer configuration using the BSP_LCD_LayerDefaultInit() function.    
     o Select the LCD layer to be used using the BSP_LCD_SelectLayer() function.
     o Enable the LCD display using the BSP_LCD_DisplayOn() function.

  + Options
     o Configure and enable the color keying functionality using the 
       BSP_LCD_SetColorKeying() function.
     o Modify in the fly the transparency and/or the frame buffer address
       using the following functions:
       - BSP_LCD_SetTransparency()
       - BSP_LCD_SetLayerAddress() 
  
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
#include "stm324x9i_eval_lcd.h"
#include "../../../Utilities/Fonts/fonts.h"
#include "../../../Utilities/Fonts/font24.c"
#include "../../../Utilities/Fonts/font20.c"
#include "../../../Utilities/Fonts/font16.c"
#include "../../../Utilities/Fonts/font12.c"
#include "../../../Utilities/Fonts/font8.c"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM324x9I_EVAL
  * @{
  */
    
/** @addtogroup STM324x9I_EVAL_LCD
  * @{
  */ 

/** @defgroup STM324x9I_EVAL_LCD_Private_TypesDefinitions
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM324x9I_EVAL_LCD_Private_Defines
  * @{
  */
#define POLY_X(Z)              ((int32_t)((Points + Z)->X))
#define POLY_Y(Z)              ((int32_t)((Points + Z)->Y))      
/**
  * @}
  */ 

/** @defgroup STM324x9I_EVAL_LCD_Private_Macros
  * @{
  */
#define ABS(X)  ((X) > 0 ? (X) : -(X))      
/**
  * @}
  */ 
    
/** @defgroup STM324x9I_EVAL_LCD_Private_Variables
  * @{
  */ 
static LTDC_HandleTypeDef  hltdc_eval;
static DMA2D_HandleTypeDef hdma2d_eval;
static uint32_t            PCLK_profile = LCD_MAX_PCLK;
    
/* Default LCD configuration with LCD Layer 1 */
static uint32_t            ActiveLayer = 0;
static LCD_DrawPropTypeDef DrawProp[MAX_LAYER_NUMBER];
/**
  * @}
  */ 

/** @defgroup STM324x9I_EVAL_LCD_Private_FunctionPrototypes
  * @{
  */ 
static void MspInit(void);
static void DrawChar(uint16_t Xpos, uint16_t Ypos, const uint8_t *c);
static void FillTriangle(uint16_t x1, uint16_t x2, uint16_t x3, uint16_t y1, uint16_t y2, uint16_t y3);
static void LL_FillBuffer(uint32_t LayerIndex, void *pDst, uint32_t xSize, uint32_t ySize, uint32_t OffLine, uint32_t ColorIndex);
static void LL_ConvertLineToARGB8888(void * pSrc, void *pDst, uint32_t xSize, uint32_t ColorMode);
/**
  * @}
  */ 

/** @defgroup STM324x9I_EVAL_LCD_Private_Functions
  * @{
  */
/**
  * @brief  Initializes the LCD.
  * @param  None
  * @retval LCD state
  */
uint8_t BSP_LCD_Init(void)
{    
  return (BSP_LCD_InitEx(LCD_MAX_PCLK));
}

/**
  * @brief  Initializes the LCD.
  * @param  PclkConfig : pixel clock profile
  * @retval LCD state
  */
uint8_t BSP_LCD_InitEx(uint32_t PclkConfig)
{    
  PCLK_profile = PclkConfig;
  
  /* Select the used LCD */
  /* The AMPIRE 480x272 does not contain an ID register then we check the availability 
     of AMPIRE 480x640 LCD using device ID of the STMPE811 mounted on MB1046 daughter board */ 
  if(stmpe811_ts_drv.ReadID(TS_I2C_ADDRESS) == STMPE811_ID)
  {
    /* The AMPIRE LCD 480x272 is selected */
    /* Timing Configuration */    
    hltdc_eval.Init.HorizontalSync = (AMPIRE480272_HSYNC - 1);
    hltdc_eval.Init.VerticalSync = (AMPIRE480272_VSYNC - 1);
    hltdc_eval.Init.AccumulatedHBP = (AMPIRE480272_HSYNC + AMPIRE480272_HBP - 1);
    hltdc_eval.Init.AccumulatedVBP = (AMPIRE480272_VSYNC + AMPIRE480272_VBP - 1);  
    hltdc_eval.Init.AccumulatedActiveH = (AMPIRE480272_HEIGHT + AMPIRE480272_VSYNC + AMPIRE480272_VBP - 1);
    hltdc_eval.Init.AccumulatedActiveW = (AMPIRE480272_WIDTH + AMPIRE480272_HSYNC + AMPIRE480272_HBP - 1);
    hltdc_eval.Init.TotalHeigh = (AMPIRE480272_HEIGHT + AMPIRE480272_VSYNC + AMPIRE480272_VBP + AMPIRE480272_VFP - 1);
    hltdc_eval.Init.TotalWidth = (AMPIRE480272_WIDTH + AMPIRE480272_HSYNC + AMPIRE480272_HBP + AMPIRE480272_HFP - 1);
  
    /* Initialize the LCD pixel width and pixel height */
    hltdc_eval.LayerCfg->ImageWidth  = AMPIRE480272_WIDTH;
    hltdc_eval.LayerCfg->ImageHeight = AMPIRE480272_HEIGHT;   
  }
  else
  {
    /* The LCD AMPIRE 640x480 is selected */
    /* Timing configuration */
    hltdc_eval.Init.HorizontalSync = (AMPIRE640480_HSYNC - 1);
    hltdc_eval.Init.VerticalSync = (AMPIRE640480_VSYNC - 1);
    hltdc_eval.Init.AccumulatedHBP = (AMPIRE640480_HSYNC + AMPIRE640480_HBP - 1);
    hltdc_eval.Init.AccumulatedVBP = (AMPIRE640480_VSYNC + AMPIRE640480_VBP - 1);  
    hltdc_eval.Init.AccumulatedActiveH = (AMPIRE640480_HEIGHT + AMPIRE640480_VSYNC + AMPIRE640480_VBP - 1);
    hltdc_eval.Init.AccumulatedActiveW = (AMPIRE640480_WIDTH + AMPIRE640480_HSYNC + AMPIRE640480_HBP - 1);
    hltdc_eval.Init.TotalHeigh = (AMPIRE640480_HEIGHT + AMPIRE640480_VSYNC + AMPIRE640480_VBP + AMPIRE640480_VFP - 1);
    hltdc_eval.Init.TotalWidth = (AMPIRE640480_WIDTH + AMPIRE640480_HSYNC + AMPIRE640480_HBP + AMPIRE640480_HFP - 1);
    
    /* Initialize the LCD pixel width and pixel height */
    hltdc_eval.LayerCfg->ImageWidth  = AMPIRE640480_WIDTH;
    hltdc_eval.LayerCfg->ImageHeight = AMPIRE640480_HEIGHT;
   }

  /* Background value */
  hltdc_eval.Init.Backcolor.Blue = 0;
  hltdc_eval.Init.Backcolor.Green = 0;
  hltdc_eval.Init.Backcolor.Red = 0;
  
  /* Polarity */
  hltdc_eval.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc_eval.Init.VSPolarity = LTDC_VSPOLARITY_AL; 
  hltdc_eval.Init.DEPolarity = LTDC_DEPOLARITY_AL;  
  hltdc_eval.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc_eval.Instance = LTDC;

  /* LCD clock configuration */
  BSP_LCD_ClockConfig(&hltdc_eval, &PCLK_profile);  
  
  MspInit();
  HAL_LTDC_Init(&hltdc_eval);
  
#if !defined(DATA_IN_ExtSDRAM)
  /* Initialize the SDRAM */
  BSP_SDRAM_Init();
#endif /* DATA_IN_ExtSDRAM */

  /* Initialize the font */
  BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
  
  return LCD_OK;
}

/**
  * @brief  Gets the LCD X size.
  * @param  None    
  * @retval Used LCD X size
  */
uint32_t BSP_LCD_GetXSize(void)
{
  return hltdc_eval.LayerCfg[ActiveLayer].ImageWidth;
}

/**
  * @brief  Gets the LCD Y size.
  * @param  None   
  * @retval Used LCD Y size
  */
uint32_t BSP_LCD_GetYSize(void)
{
  return hltdc_eval.LayerCfg[ActiveLayer].ImageHeight;
}

/**
  * @brief  Initializes the LCD layers.
  * @param  LayerIndex: Layer foreground or background
  * @param  FB_Address: Layer frame buffer
  * @retval None
  */
void BSP_LCD_LayerDefaultInit(uint16_t LayerIndex, uint32_t FB_Address)
{     
  LCD_LayerCfgTypeDef  Layercfg;

  /* Layer Init */
  Layercfg.WindowX0 = 0;
  Layercfg.WindowX1 = BSP_LCD_GetXSize();
  Layercfg.WindowY0 = 0;
  Layercfg.WindowY1 = BSP_LCD_GetYSize(); 
  Layercfg.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
  Layercfg.FBStartAdress = FB_Address;
  Layercfg.Alpha = 255;
  Layercfg.Alpha0 = 0;
  Layercfg.Backcolor.Blue = 0;
  Layercfg.Backcolor.Green = 0;
  Layercfg.Backcolor.Red = 0;
  Layercfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
  Layercfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
  Layercfg.ImageWidth = BSP_LCD_GetXSize();
  Layercfg.ImageHeight = BSP_LCD_GetYSize();
  
  HAL_LTDC_ConfigLayer(&hltdc_eval, &Layercfg, LayerIndex); 

  DrawProp[LayerIndex].BackColor = LCD_COLOR_WHITE;
  DrawProp[LayerIndex].pFont     = &Font24;
  DrawProp[LayerIndex].TextColor = LCD_COLOR_BLACK; 
}

/**
  * @brief  Selects the LCD Layer.
  * @param  LayerIndex: Layer foreground or background
  * @retval None
  */
void BSP_LCD_SelectLayer(uint32_t LayerIndex)
{
  ActiveLayer = LayerIndex;
} 

/**
  * @brief  Sets an LCD Layer visible
  * @param  LayerIndex: Visible Layer
  * @param  State: New state of the specified layer
  *          This parameter can be one of the following values:
  *            @arg  ENABLE
  *            @arg  DISABLE 
  * @retval None
  */
void BSP_LCD_SetLayerVisible(uint32_t LayerIndex, FunctionalState State)
{
  if(State == ENABLE)
  {
    __HAL_LTDC_LAYER_ENABLE(&hltdc_eval, LayerIndex);
  }
  else
  {
    __HAL_LTDC_LAYER_DISABLE(&hltdc_eval, LayerIndex);
  }
  __HAL_LTDC_RELOAD_CONFIG(&hltdc_eval);
} 

/**
  * @brief  Configures the transparency.
  * @param  LayerIndex: Layer foreground or background.
  * @param  Transparency: Transparency
  *           This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF 
  * @retval None
  */
void BSP_LCD_SetTransparency(uint32_t LayerIndex, uint8_t Transparency)
{    
  HAL_LTDC_SetAlpha(&hltdc_eval, Transparency, LayerIndex);
}

/**
  * @brief  Sets an LCD layer frame buffer address.
  * @param  LayerIndex: Layer foreground or background
  * @param  Address: New LCD frame buffer value      
  * @retval None
  */
void BSP_LCD_SetLayerAddress(uint32_t LayerIndex, uint32_t Address)
{
  HAL_LTDC_SetAddress(&hltdc_eval, Address, LayerIndex);
}

/**
  * @brief  Sets display window.
  * @param  LayerIndex: Layer index
  * @param  Xpos: LCD X position
  * @param  Ypos: LCD Y position
  * @param  Width: LCD window width
  * @param  Height: LCD window height  
  * @retval None
  */
void BSP_LCD_SetLayerWindow(uint16_t LayerIndex, uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  /* Reconfigure the layer size */
  HAL_LTDC_SetWindowSize(&hltdc_eval, Width, Height, LayerIndex);
  
  /* Reconfigure the layer position */
  HAL_LTDC_SetWindowPosition(&hltdc_eval, Xpos, Ypos, LayerIndex); 
}

/**
  * @brief  Configures and sets the color keying.
  * @param  LayerIndex: Layer foreground or background
  * @param  RGBValue: Color reference
  * @retval None
  */
void BSP_LCD_SetColorKeying(uint32_t LayerIndex, uint32_t RGBValue)
{  
  /* Configure and Enable the color Keying for LCD Layer */
  HAL_LTDC_ConfigColorKeying(&hltdc_eval, RGBValue, LayerIndex);
  HAL_LTDC_EnableColorKeying(&hltdc_eval, LayerIndex);
}

/**
  * @brief  Disables the color keying.
  * @param  LayerIndex: Layer foreground or background
  * @retval None
  */
void BSP_LCD_ResetColorKeying(uint32_t LayerIndex)
{   
  /* Disable the color Keying for LCD Layer */
  HAL_LTDC_DisableColorKeying(&hltdc_eval, LayerIndex);
}

/**
  * @brief  Sets the LCD text color.
  * @param  Color: Text color code ARGB(8-8-8-8)
  * @retval None
  */
void BSP_LCD_SetTextColor(uint32_t Color)
{
  DrawProp[ActiveLayer].TextColor = Color;
}

/**
  * @brief  Gets the LCD text color.
  * @param  None 
  * @retval Used text color.
  */
uint32_t BSP_LCD_GetTextColor(void)
{
  return DrawProp[ActiveLayer].TextColor;
}

/**
  * @brief  Sets the LCD background color.
  * @param  Color: Layer background color code ARGB(8-8-8-8)
  * @retval None
  */
void BSP_LCD_SetBackColor(uint32_t Color)
{
  DrawProp[ActiveLayer].BackColor = Color;
}

/**
  * @brief  Gets the LCD background color.
  * @param  None
  * @retval Used background color
  */
uint32_t BSP_LCD_GetBackColor(void)
{
  return DrawProp[ActiveLayer].BackColor;
}

/**
  * @brief  Sets the LCD text font.
  * @param  fonts: Layer font to be used
  * @retval None
  */
void BSP_LCD_SetFont(sFONT *fonts)
{
  DrawProp[ActiveLayer].pFont = fonts;
}

/**
  * @brief  Gets the LCD text font.
  * @param  None
  * @retval Used layer font
  */
sFONT *BSP_LCD_GetFont(void)
{
  return DrawProp[ActiveLayer].pFont;
}

/**
  * @brief  Reads an LCD pixel.
  * @param  Xpos: X position 
  * @param  Ypos: Y position 
  * @retval RGB pixel color
  */
uint32_t BSP_LCD_ReadPixel(uint16_t Xpos, uint16_t Ypos)
{
  uint32_t ret = 0;
  
  if(hltdc_eval.LayerCfg[ActiveLayer].PixelFormat == LTDC_PIXEL_FORMAT_ARGB8888)
  {
    /* Read data value from SDRAM memory */
    ret = *(__IO uint32_t*) (hltdc_eval.LayerCfg[ActiveLayer].FBStartAdress + (2*(Ypos*BSP_LCD_GetXSize() + Xpos)));
  }
  else if(hltdc_eval.LayerCfg[ActiveLayer].PixelFormat == LTDC_PIXEL_FORMAT_RGB888)
  {
    /* Read data value from SDRAM memory */
    ret = (*(__IO uint32_t*) (hltdc_eval.LayerCfg[ActiveLayer].FBStartAdress + (2*(Ypos*BSP_LCD_GetXSize() + Xpos))) & 0x00FFFFFF);
  }
  else if((hltdc_eval.LayerCfg[ActiveLayer].PixelFormat == LTDC_PIXEL_FORMAT_RGB565) || \
          (hltdc_eval.LayerCfg[ActiveLayer].PixelFormat == LTDC_PIXEL_FORMAT_ARGB4444) || \
          (hltdc_eval.LayerCfg[ActiveLayer].PixelFormat == LTDC_PIXEL_FORMAT_AL88))  
  {
    /* Read data value from SDRAM memory */
    ret = *(__IO uint16_t*) (hltdc_eval.LayerCfg[ActiveLayer].FBStartAdress + (2*(Ypos*BSP_LCD_GetXSize() + Xpos)));    
  }
  else
  {
    /* Read data value from SDRAM memory */
    ret = *(__IO uint8_t*) (hltdc_eval.LayerCfg[ActiveLayer].FBStartAdress + (2*(Ypos*BSP_LCD_GetXSize() + Xpos)));    
  }
  
  return ret;
}

/**
  * @brief  Clears the hole LCD.
  * @param  Color: Color of the background
  * @retval None
  */
void BSP_LCD_Clear(uint32_t Color)
{ 
  /* Clear the LCD */ 
  LL_FillBuffer(ActiveLayer, (uint32_t *)(hltdc_eval.LayerCfg[ActiveLayer].FBStartAdress), BSP_LCD_GetXSize(), BSP_LCD_GetYSize(), 0, Color);
}

/**
  * @brief  Clears the selected line.
  * @param  Line: Line to be cleared
  * @retval None
  */
void BSP_LCD_ClearStringLine(uint32_t Line)
{
  uint32_t color_backup = DrawProp[ActiveLayer].TextColor;
  DrawProp[ActiveLayer].TextColor = DrawProp[ActiveLayer].BackColor;
  
  /* Draw rectangle with background color */
  BSP_LCD_FillRect(0, (Line * DrawProp[ActiveLayer].pFont->Height), BSP_LCD_GetXSize(), DrawProp[ActiveLayer].pFont->Height);
  
  DrawProp[ActiveLayer].TextColor = color_backup;
  BSP_LCD_SetTextColor(DrawProp[ActiveLayer].TextColor);  
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
  DrawChar(Xpos, Ypos, &DrawProp[ActiveLayer].pFont->table[(Ascii-' ') *\
    DrawProp[ActiveLayer].pFont->Height * ((DrawProp[ActiveLayer].pFont->Width + 7) / 8)]);
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
void BSP_LCD_DisplayStringAt(uint16_t Xpos, uint16_t Ypos, uint8_t *Text, Text_AlignModeTypdef Mode)
{
  uint16_t refcolumn = 1, i = 0;
  uint32_t size = 0, xsize = 0; 
  uint8_t  *ptr = Text;
  
  /* Get the text size */
  while (*ptr++) size ++ ;
  
  /* Characters number per line */
  xsize = (BSP_LCD_GetXSize()/DrawProp[ActiveLayer].pFont->Width);
  
  switch (Mode)
  {
  case CENTER_MODE:
    {
      refcolumn = Xpos + ((xsize - size)* DrawProp[ActiveLayer].pFont->Width) / 2;
      break;
    }
  case LEFT_MODE:
    {
      refcolumn = Xpos;
      break;
    }
  case RIGHT_MODE:
    {
      refcolumn = - Xpos + ((xsize - size)*DrawProp[ActiveLayer].pFont->Width);
      break;
    }    
  default:
    {
      refcolumn = Xpos;
      break;
    }
  }
  
  /* Send the string character by character on LCD */
  while ((*Text != 0) & (((BSP_LCD_GetXSize() - (i*DrawProp[ActiveLayer].pFont->Width)) & 0xFFFF) >= DrawProp[ActiveLayer].pFont->Width))
  {
    /* Display one character on LCD */
    BSP_LCD_DisplayChar(refcolumn, Ypos, *Text);
    /* Decrement the column position by 16 */
    refcolumn += DrawProp[ActiveLayer].pFont->Width;
    /* Point on the next character */
    Text++;
    i++;
  }  
}

/**
  * @brief  Displays a maximum of 60 characters on the LCD.
  * @param  Line: Line where to display the character shape
  * @param  ptr: Pointer to string to display on LCD
  * @retval None
  */
void BSP_LCD_DisplayStringAtLine(uint16_t Line, uint8_t *ptr)
{  
  BSP_LCD_DisplayStringAt(0, LINE(Line), ptr, LEFT_MODE);
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
  uint32_t  Xaddress = 0;
  
  /* Get the line address */
  Xaddress = (hltdc_eval.LayerCfg[ActiveLayer].FBStartAdress) + 4*(BSP_LCD_GetXSize()*Ypos + Xpos);
  
  /* Write line */
  LL_FillBuffer(ActiveLayer, (uint32_t *)Xaddress, Length, 1, 0, DrawProp[ActiveLayer].TextColor);
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
  uint32_t  Xaddress = 0;
  
  /* Get the line address */
  Xaddress = (hltdc_eval.LayerCfg[ActiveLayer].FBStartAdress) + 4*(BSP_LCD_GetXSize()*Ypos + Xpos);
  
  /* Write line */
  LL_FillBuffer(ActiveLayer, (uint32_t *)Xaddress, 1, Length, (BSP_LCD_GetXSize() - 1), DrawProp[ActiveLayer].TextColor);
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
    BSP_LCD_DrawPixel(x, y, DrawProp[ActiveLayer].TextColor);   /* Draw the current pixel */
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
  int32_t   D;    /* Decision Variable */ 
  uint32_t  CurX; /* Current X Value */
  uint32_t  CurY; /* Current Y Value */ 
  
  D = 3 - (Radius << 1);
  CurX = 0;
  CurY = Radius;
  
  while (CurX <= CurY)
  {
    BSP_LCD_DrawPixel((Xpos + CurX), (Ypos - CurY), DrawProp[ActiveLayer].TextColor);
    
    BSP_LCD_DrawPixel((Xpos - CurX), (Ypos - CurY), DrawProp[ActiveLayer].TextColor);
    
    BSP_LCD_DrawPixel((Xpos + CurY), (Ypos - CurX), DrawProp[ActiveLayer].TextColor);
    
    BSP_LCD_DrawPixel((Xpos - CurY), (Ypos - CurX), DrawProp[ActiveLayer].TextColor);
    
    BSP_LCD_DrawPixel((Xpos + CurX), (Ypos + CurY), DrawProp[ActiveLayer].TextColor);
    
    BSP_LCD_DrawPixel((Xpos - CurX), (Ypos + CurY), DrawProp[ActiveLayer].TextColor);
    
    BSP_LCD_DrawPixel((Xpos + CurY), (Ypos + CurX), DrawProp[ActiveLayer].TextColor);
    
    BSP_LCD_DrawPixel((Xpos - CurY), (Ypos + CurX), DrawProp[ActiveLayer].TextColor);   
    
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
    BSP_LCD_DrawPixel((Xpos-(uint16_t)(x/K)), (Ypos+y), DrawProp[ActiveLayer].TextColor);
    BSP_LCD_DrawPixel((Xpos+(uint16_t)(x/K)), (Ypos+y), DrawProp[ActiveLayer].TextColor);
    BSP_LCD_DrawPixel((Xpos+(uint16_t)(x/K)), (Ypos-y), DrawProp[ActiveLayer].TextColor);
    BSP_LCD_DrawPixel((Xpos-(uint16_t)(x/K)), (Ypos-y), DrawProp[ActiveLayer].TextColor);      
    
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
  * @brief  Draws a bitmap picture loaded in the internal Flash (32 bpp).
  * @param  Xpos: Bmp X position in the LCD
  * @param  Ypos: Bmp Y position in the LCD
  * @param  pbmp: Pointer to Bmp picture address in the internal Flash
  * @retval None
  */
void BSP_LCD_DrawBitmap(uint32_t Xpos, uint32_t Ypos, uint8_t *pbmp)
{
  uint32_t index = 0, width = 0, height = 0, bit_pixel = 0;
  uint32_t Address;
  uint32_t InputColorMode = 0;
  
  /* Get bitmap data address offset */
  index = *(__IO uint16_t *) (pbmp + 10);
  index |= (*(__IO uint16_t *) (pbmp + 12)) << 16;
  
  /* Read bitmap width */
  width = *(uint16_t *) (pbmp + 18);
  width |= (*(uint16_t *) (pbmp + 20)) << 16;
  
  /* Read bitmap height */
  height = *(uint16_t *) (pbmp + 22);
  height |= (*(uint16_t *) (pbmp + 24)) << 16; 
  
  /* Read bit/pixel */
  bit_pixel = *(uint16_t *) (pbmp + 28);   
  
  /* Set the address */
  Address = hltdc_eval.LayerCfg[ActiveLayer].FBStartAdress + (((BSP_LCD_GetXSize()*Ypos) + Xpos)*(4));
  
  /* Get the layer pixel format */    
  if ((bit_pixel/8) == 4)
  {
    InputColorMode = CM_ARGB8888;
  }
  else if ((bit_pixel/8) == 2)
  {
    InputColorMode = CM_RGB565;   
  }
  else 
  {
    InputColorMode = CM_RGB888;
  }
  
  /* Bypass the bitmap header */
  pbmp += (index + (width * (height - 1) * (bit_pixel/8)));  
  
  /* Convert picture to ARGB8888 pixel format */
  for(index=0; index < height; index++)
  {
    /* Pixel format conversion */
    LL_ConvertLineToARGB8888((uint32_t *)pbmp, (uint32_t *)Address, width, InputColorMode);
    
    /* Increment the source and destination buffers */
    Address+=  (BSP_LCD_GetXSize()*4);
    pbmp -= width*(bit_pixel/8);
  } 
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
  uint32_t  Xaddress = 0;
  
  /* Set the text color */
  BSP_LCD_SetTextColor(DrawProp[ActiveLayer].TextColor);
  
  /* Get the rectangle start address */
  Xaddress = (hltdc_eval.LayerCfg[ActiveLayer].FBStartAdress) + 4*(BSP_LCD_GetXSize()*Ypos + Xpos);
  
  /* Fill the rectangle */
  LL_FillBuffer(ActiveLayer, (uint32_t *)Xaddress, Width, Height, (BSP_LCD_GetXSize() - Width), DrawProp[ActiveLayer].TextColor);
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
  int32_t  D;     /* Decision Variable */ 
  uint32_t  CurX; /* Current X Value */
  uint32_t  CurY; /* Current Y Value */ 
  
  D = 3 - (Radius << 1);
  
  CurX = 0;
  CurY = Radius;
  
  BSP_LCD_SetTextColor(DrawProp[ActiveLayer].TextColor);
  
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
  
  BSP_LCD_SetTextColor(DrawProp[ActiveLayer].TextColor);
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
  /* Display On */
  __HAL_LTDC_ENABLE(&hltdc_eval);
}

/**
  * @brief  Disables the display.
  * @param  None
  * @retval None
  */
void BSP_LCD_DisplayOff(void)
{
  /* Display Off */
  __HAL_LTDC_DISABLE(&hltdc_eval);
}

/*******************************************************************************
                       LTDC and DMA2D BSP Routines
*******************************************************************************/

/**
  * @brief  Initializes the LTDC MSP.
  * @param  None
  * @retval None
  */
static void MspInit(void)
{
  GPIO_InitTypeDef GPIO_Init_Structure;
  
  /* Enable the LTDC and DMA2D clocks */
  __LTDC_CLK_ENABLE();
  __DMA2D_CLK_ENABLE(); 
  
  /* Enable GPIOs clock */
  __GPIOI_CLK_ENABLE(); 
  __GPIOJ_CLK_ENABLE();
  __GPIOK_CLK_ENABLE();  

  /*** LTDC Pins configuration ***/
  /* GPIOI configuration */
  GPIO_Init_Structure.Pin       = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15; 
  GPIO_Init_Structure.Mode      = GPIO_MODE_AF_PP;
  GPIO_Init_Structure.Pull      = GPIO_NOPULL;
  GPIO_Init_Structure.Speed     = GPIO_SPEED_FAST;
  GPIO_Init_Structure.Alternate = GPIO_AF14_LTDC;  
  HAL_GPIO_Init(GPIOI, &GPIO_Init_Structure);

  /* GPIOJ configuration */  
  GPIO_Init_Structure.Pin       = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | \
                                  GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | \
                                  GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | \
                                  GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15; 
  GPIO_Init_Structure.Mode      = GPIO_MODE_AF_PP;
  GPIO_Init_Structure.Pull      = GPIO_NOPULL;
  GPIO_Init_Structure.Speed     = GPIO_SPEED_FAST;
  GPIO_Init_Structure.Alternate = GPIO_AF14_LTDC;  
  HAL_GPIO_Init(GPIOJ, &GPIO_Init_Structure);  

  /* GPIOK configuration */  
  GPIO_Init_Structure.Pin       = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | \
                                  GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7; 
  GPIO_Init_Structure.Mode      = GPIO_MODE_AF_PP;
  GPIO_Init_Structure.Pull      = GPIO_NOPULL;
  GPIO_Init_Structure.Speed     = GPIO_SPEED_FAST;
  GPIO_Init_Structure.Alternate = GPIO_AF14_LTDC;  
  HAL_GPIO_Init(GPIOK, &GPIO_Init_Structure);
}

/**
  * @brief  Clock Config.
  * @param  hltdc: LTDC handle
  * @note   This API is called by BSP_LCD_Init()
  *         Being __weak it can be overwritten by the application
  * @retval None
  */
__weak void BSP_LCD_ClockConfig(LTDC_HandleTypeDef *hltdc, void *Params)
{
  static RCC_PeriphCLKInitTypeDef  periph_clk_init_struct;

  if(stmpe811_ts_drv.ReadID(TS_I2C_ADDRESS) == STMPE811_ID)
  {
    /* AMPIRE480272 LCD clock configuration */
    /* PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz */
    /* PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAIN = 192 Mhz */
    /* PLLLCDCLK = PLLSAI_VCO Output/PLLSAIR = 192/5 = 38.4 Mhz */
    /* LTDC clock frequency = PLLLCDCLK / LTDC_PLLSAI_DIVR_4 = 38.4/4 = 9.6Mhz */
    periph_clk_init_struct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    periph_clk_init_struct.PLLSAI.PLLSAIN = 192;
    periph_clk_init_struct.PLLSAI.PLLSAIR = AMPIRE480272_FREQUENCY_DIVIDER;
    periph_clk_init_struct.PLLSAIDivR = RCC_PLLSAIDIVR_4;
    HAL_RCCEx_PeriphCLKConfig(&periph_clk_init_struct);
  }
  else
  {
    /* The programmed LTDC pixel clock depends on the vertical refresh rate of the panel 60Hz => 25.16MHz and
       the LCD/SDRAM bandwidth affected by the several access on the bus and the number of used layers.
    */
    if(*(uint32_t *)Params == LCD_MAX_PCLK)
    {
      /* In case of single layer the bandwidth is arround 160MBytesPerSec ==> theorical PCLK of 40MHz */
      /* AMPIRE640480 typical PCLK is 25.16 MHz so the PLLSAI is configured to provide this clock */ 
      /* AMPIRE640480 LCD clock configuration */
      /* PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz */
      /* PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAIN = 151 Mhz */
      /* PLLLCDCLK = PLLSAI_VCO Output/PLLSAIR = 151/3 = 50.3 Mhz */
      /* LTDC clock frequency = PLLLCDCLK / LTDC_PLLSAI_DIVR_2 = 50.3/2 = 25.16 Mhz */
      periph_clk_init_struct.PLLSAI.PLLSAIN = 151;
    }
    else
    {
      /* In case of double layers the bandwidth is arround 72MBytesPerSec => 18MHz (<25,16MHz) */
      /* so the PLLSAI is configured to provide this clock */
      /* AMPIRE640480 LCD clock configuration */
      /* PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz */
      /* PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAIN = 108 Mhz */
      /* PLLLCDCLK = PLLSAI_VCO Output/PLLSAIR = 108/3 = 36 Mhz */
      /* LTDC clock frequency = PLLLCDCLK / LTDC_PLLSAI_DIVR_2 = 36/2 = 18 Mhz */      
      periph_clk_init_struct.PLLSAI.PLLSAIN = 108;
    }
    periph_clk_init_struct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;    
    periph_clk_init_struct.PLLSAI.PLLSAIR = 3;    
    periph_clk_init_struct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
    HAL_RCCEx_PeriphCLKConfig(&periph_clk_init_struct);
  }
}
/*******************************************************************************
                            Static Functions
*******************************************************************************/

/**
  * @brief  Draws a pixel on LCD.
  * @param  Xpos: X position 
  * @param  Ypos: Y position
  * @param  RGB_Code: Pixel color in ARGB mode (8-8-8-8)  
  * @retval None
  */
void BSP_LCD_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint32_t RGB_Code)
{
  /* Write data value to all SDRAM memory */
  *(__IO uint32_t*) (hltdc_eval.LayerCfg[ActiveLayer].FBStartAdress + (4*(Ypos*BSP_LCD_GetXSize() + Xpos))) = RGB_Code;
}

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
  uint8_t  offset;
  uint8_t  *pchar;
  uint32_t line;
  
  height = DrawProp[ActiveLayer].pFont->Height;
  width  = DrawProp[ActiveLayer].pFont->Width;
  
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
        BSP_LCD_DrawPixel((Xpos + j), Ypos, DrawProp[ActiveLayer].TextColor);
      }
      else
      {
        BSP_LCD_DrawPixel((Xpos + j), Ypos, DrawProp[ActiveLayer].BackColor);
      } 
    }
    Ypos++;
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
  * @brief  Fills a buffer.
  * @param  LayerIndex: Layer index
  * @param  pDst: Pointer to destination buffer
  * @param  xSize: Buffer width
  * @param  ySize: Buffer height
  * @param  OffLine: Offset
  * @param  ColorIndex: Color index
  * @retval None
  */
static void LL_FillBuffer(uint32_t LayerIndex, void *pDst, uint32_t xSize, uint32_t ySize, uint32_t OffLine, uint32_t ColorIndex) 
{
  /* Register to memory mode with ARGB8888 as color Mode */ 
  hdma2d_eval.Init.Mode         = DMA2D_R2M;
  hdma2d_eval.Init.ColorMode    = DMA2D_ARGB8888;
  hdma2d_eval.Init.OutputOffset = OffLine;      
  
  hdma2d_eval.Instance = DMA2D;
  
  /* DMA2D Initialization */
  if(HAL_DMA2D_Init(&hdma2d_eval) == HAL_OK) 
  {
    if(HAL_DMA2D_ConfigLayer(&hdma2d_eval, LayerIndex) == HAL_OK) 
    {
      if (HAL_DMA2D_Start(&hdma2d_eval, ColorIndex, (uint32_t)pDst, xSize, ySize) == HAL_OK)
      {
        /* Polling For DMA transfer */  
        HAL_DMA2D_PollForTransfer(&hdma2d_eval, 10);
      }
    }
  } 
}

/**
  * @brief  Converts a line to an ARGB8888 pixel format.
  * @param  pSrc: Pointer to source buffer
  * @param  pDst: Output color
  * @param  xSize: Buffer width
  * @param  ColorMode: Input color mode   
  * @retval None
  */
static void LL_ConvertLineToARGB8888(void *pSrc, void *pDst, uint32_t xSize, uint32_t ColorMode)
{    
  /* Configure the DMA2D Mode, Color Mode and output offset */
  hdma2d_eval.Init.Mode         = DMA2D_M2M_PFC;
  hdma2d_eval.Init.ColorMode    = DMA2D_ARGB8888;
  hdma2d_eval.Init.OutputOffset = 0;     
  
  /* Foreground Configuration */
  hdma2d_eval.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d_eval.LayerCfg[1].InputAlpha = 0xFF;
  hdma2d_eval.LayerCfg[1].InputColorMode = ColorMode;
  hdma2d_eval.LayerCfg[1].InputOffset = 0;
  
  hdma2d_eval.Instance = DMA2D; 
  
  /* DMA2D Initialization */
  if(HAL_DMA2D_Init(&hdma2d_eval) == HAL_OK) 
  {
    if(HAL_DMA2D_ConfigLayer(&hdma2d_eval, 1) == HAL_OK) 
    {
      if (HAL_DMA2D_Start(&hdma2d_eval, (uint32_t)pSrc, (uint32_t)pDst, xSize, 1) == HAL_OK)
      {
        /* Polling For DMA transfer */  
        HAL_DMA2D_PollForTransfer(&hdma2d_eval, 10);
      }
    }
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
