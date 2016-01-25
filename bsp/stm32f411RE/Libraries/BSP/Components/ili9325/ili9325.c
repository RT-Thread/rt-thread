/**
  ******************************************************************************
  * @file    ili9325.c
  * @author  MCD Application Team
  * @version V1.0.2
  * @date    02-December-2014
  * @brief   This file includes the LCD driver for ILI9325 LCD.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
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

/* Includes ------------------------------------------------------------------*/
#include "ili9325.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */ 
  
/** @addtogroup ili9325
  * @brief     This file provides a set of functions needed to drive the 
  *            ILI9325 LCD.
  * @{
  */

/** @defgroup ILI9325_Private_TypesDefinitions
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ILI9325_Private_Defines
  * @{
  */

/**
  * @}
  */ 
  
/** @defgroup ILI9325_Private_Macros
  * @{
  */
     
/**
  * @}
  */  

/** @defgroup ILI9325_Private_Variables
  * @{
  */ 
LCD_DrvTypeDef   ili9325_drv = 
{
  ili9325_Init,
  ili9325_ReadID,
  ili9325_DisplayOn,
  ili9325_DisplayOff,
  ili9325_SetCursor,
  ili9325_WritePixel,
  ili9325_ReadPixel,
  ili9325_SetDisplayWindow,
  ili9325_DrawHLine,
  ili9325_DrawVLine,
  ili9325_GetLcdPixelWidth,
  ili9325_GetLcdPixelHeight,
  ili9325_DrawBitmap,
  ili9325_DrawRGBImage,  
};

/**
  * @}
  */ 
  
/** @defgroup ILI9325_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */ 
  
/** @defgroup ILI9325_Private_Functions
  * @{
  */   

/**
  * @brief  Initialize the ILI9325 LCD Component.
  * @param  None
  * @retval None
  */
void ili9325_Init(void)
{  
  /* Initialize ILI9325 low level bus layer ----------------------------------*/
  LCD_IO_Init();
  
  /* Start Initial Sequence --------------------------------------------------*/
  ili9325_WriteReg(LCD_REG_0, 0x0001); /* Start internal OSC. */
  ili9325_WriteReg(LCD_REG_1, 0x0100); /* Set SS and SM bit */
  ili9325_WriteReg(LCD_REG_2, 0x0700); /* Set 1 line inversion */
  ili9325_WriteReg(LCD_REG_3, 0x1018); /* Set GRAM write direction and BGR=1. */
  ili9325_WriteReg(LCD_REG_4, 0x0000); /* Resize register */
  ili9325_WriteReg(LCD_REG_8, 0x0202); /* Set the back porch and front porch */
  ili9325_WriteReg(LCD_REG_9, 0x0000); /* Set non-display area refresh cycle ISC[3:0] */
  ili9325_WriteReg(LCD_REG_10, 0x0000); /* FMARK function */
  ili9325_WriteReg(LCD_REG_12, 0x0000); /* RGB interface setting */
  ili9325_WriteReg(LCD_REG_13, 0x0000); /* Frame marker Position */
  ili9325_WriteReg(LCD_REG_15, 0x0000); /* RGB interface polarity */
  
  /* Power On sequence -------------------------------------------------------*/
  ili9325_WriteReg(LCD_REG_16, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
  ili9325_WriteReg(LCD_REG_17, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
  ili9325_WriteReg(LCD_REG_18, 0x0000); /* VREG1OUT voltage */
  ili9325_WriteReg(LCD_REG_19, 0x0000); /* VDV[4:0] for VCOM amplitude */
  
  ili9325_WriteReg(LCD_REG_16, 0x17B0); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
  ili9325_WriteReg(LCD_REG_17, 0x0137); /* DC1[2:0], DC0[2:0], VC[2:0] */
  
  ili9325_WriteReg(LCD_REG_18, 0x0139); /* VREG1OUT voltage */
  
  ili9325_WriteReg(LCD_REG_19, 0x1d00); /* VDV[4:0] for VCOM amplitude */
  ili9325_WriteReg(LCD_REG_41, 0x0013); /* VCM[4:0] for VCOMH */
  
  ili9325_WriteReg(LCD_REG_32, 0x0000); /* GRAM horizontal Address */
  ili9325_WriteReg(LCD_REG_33, 0x0000); /* GRAM Vertical Address */
  
  /* Adjust the Gamma Curve (ILI9325) ----------------------------------------*/
  ili9325_WriteReg(LCD_REG_48, 0x0007);
  ili9325_WriteReg(LCD_REG_49, 0x0302);
  ili9325_WriteReg(LCD_REG_50, 0x0105);
  ili9325_WriteReg(LCD_REG_53, 0x0206);
  ili9325_WriteReg(LCD_REG_54, 0x0808);
  ili9325_WriteReg(LCD_REG_55, 0x0206);
  ili9325_WriteReg(LCD_REG_56, 0x0504);
  ili9325_WriteReg(LCD_REG_57, 0x0007);
  ili9325_WriteReg(LCD_REG_60, 0x0105);
  ili9325_WriteReg(LCD_REG_61, 0x0808);
  
  /* Set GRAM area -----------------------------------------------------------*/
  ili9325_WriteReg(LCD_REG_80, 0x0000); /* Horizontal GRAM Start Address */
  ili9325_WriteReg(LCD_REG_81, 0x00EF); /* Horizontal GRAM End Address */
  ili9325_WriteReg(LCD_REG_82, 0x0000); /* Vertical GRAM Start Address */
  ili9325_WriteReg(LCD_REG_83, 0x013F); /* Vertical GRAM End Address */
  
  ili9325_WriteReg(LCD_REG_96,  0xA700); /* Gate Scan Line(GS=1, scan direction is G320~G1) */
  ili9325_WriteReg(LCD_REG_97,  0x0001); /* NDL,VLE, REV */
  ili9325_WriteReg(LCD_REG_106, 0x0000); /* set scrolling line */
  
  /* Partial Display Control -------------------------------------------------*/
  ili9325_WriteReg(LCD_REG_128, 0x0000);
  ili9325_WriteReg(LCD_REG_129, 0x0000);
  ili9325_WriteReg(LCD_REG_130, 0x0000);
  ili9325_WriteReg(LCD_REG_131, 0x0000);
  ili9325_WriteReg(LCD_REG_132, 0x0000);
  ili9325_WriteReg(LCD_REG_133, 0x0000);
  
  /* Panel Control -----------------------------------------------------------*/
  ili9325_WriteReg(LCD_REG_144, 0x0010);
  ili9325_WriteReg(LCD_REG_146, 0x0000);
  ili9325_WriteReg(LCD_REG_147, 0x0003);
  ili9325_WriteReg(LCD_REG_149, 0x0110);
  ili9325_WriteReg(LCD_REG_151, 0x0000);
  ili9325_WriteReg(LCD_REG_152, 0x0000);
  
  /* set GRAM write direction and BGR = 1 */
  /* I/D=00 (Horizontal : increment, Vertical : decrement) */
  /* AM=1 (address is updated in vertical writing direction) */
  ili9325_WriteReg(LCD_REG_3, 0x1018);
  
  /* 262K color and display ON */ 
  ili9325_WriteReg(LCD_REG_7, 0x0173);    
  
  /* Set the Cursor */ 
  ili9325_SetCursor(0, 0);
  
  /* Prepare to write GRAM */
  LCD_IO_WriteReg(LCD_REG_34);
}

/**
  * @brief  Enables the Display.
  * @param  None
  * @retval None
  */
void ili9325_DisplayOn(void)
{
  /* Power On sequence -------------------------------------------------------*/
  ili9325_WriteReg(LCD_REG_16, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
  ili9325_WriteReg(LCD_REG_17, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
  ili9325_WriteReg(LCD_REG_18, 0x0000); /* VREG1OUT voltage */
  ili9325_WriteReg(LCD_REG_19, 0x0000); /* VDV[4:0] for VCOM amplitude*/

  ili9325_WriteReg(LCD_REG_16, 0x17B0); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
  ili9325_WriteReg(LCD_REG_17, 0x0137); /* DC1[2:0], DC0[2:0], VC[2:0] */

  ili9325_WriteReg(LCD_REG_18, 0x0139); /* VREG1OUT voltage */

  ili9325_WriteReg(LCD_REG_19, 0x1d00); /* VDV[4:0] for VCOM amplitude */
  ili9325_WriteReg(LCD_REG_41, 0x0013); /* VCM[4:0] for VCOMH */
 
  /* Display On */
  ili9325_WriteReg(LCD_REG_7, 0x0173); /* 262K color and display ON */
}

/**
  * @brief  Disables the Display.
  * @param  None
  * @retval None
  */
void ili9325_DisplayOff(void)
{
  /* Power Off sequence ------------------------------------------------------*/
  ili9325_WriteReg(LCD_REG_16, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
  ili9325_WriteReg(LCD_REG_17, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
  ili9325_WriteReg(LCD_REG_18, 0x0000); /* VREG1OUT voltage */
  ili9325_WriteReg(LCD_REG_19, 0x0000); /* VDV[4:0] for VCOM amplitude*/
  
  ili9325_WriteReg(LCD_REG_41, 0x0000); /* VCM[4:0] for VCOMH */
  
  /* Display Off */
  ili9325_WriteReg(LCD_REG_7, 0x0); 
}

/**
  * @brief  Get the LCD pixel Width.
  * @param  None
  * @retval The Lcd Pixel Width
  */
uint16_t ili9325_GetLcdPixelWidth(void)
{
 return (uint16_t)320;
}

/**
  * @brief  Get the LCD pixel Height.
  * @param  None
  * @retval The Lcd Pixel Height
  */
uint16_t ili9325_GetLcdPixelHeight(void)
{
 return (uint16_t)240;
}

/**
  * @brief  Get the ILI9325 ID.
  * @param  None
  * @retval The ILI9325 ID 
  */
uint16_t ili9325_ReadID(void)
{
  LCD_IO_Init(); 
  return (ili9325_ReadReg(0x00));
}

/**
  * @brief  Set Cursor position.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @retval None
  */
void ili9325_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
  ili9325_WriteReg(LCD_REG_32, Ypos);
  ili9325_WriteReg(LCD_REG_33, (ILI9325_LCD_PIXEL_WIDTH - 1 - Xpos));      
}

/**
  * @brief  Write pixel.   
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  RGB_Code: the RGB pixel color
  * @retval None
  */
void ili9325_WritePixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGB_Code)
{
  /* Set Cursor */
  ili9325_SetCursor(Xpos, Ypos);
  
  /* Prepare to write GRAM */
  LCD_IO_WriteReg(LCD_REG_34);

  /* Write 16-bit GRAM Reg */
  LCD_IO_WriteData(RGB_Code);
}

/**
  * @brief  Read pixel.
  * @param  None
  * @retval The RGB pixel color
  */
uint16_t ili9325_ReadPixel(uint16_t Xpos, uint16_t Ypos)
{
  /* Set Cursor */
  ili9325_SetCursor(Xpos, Ypos);
  
  /* Prepare to write GRAM */
  LCD_IO_WriteReg(LCD_REG_34);
  
  /* Dummy read */
  LCD_IO_ReadData();
  
  /* Read 16-bit Reg */
  return (LCD_IO_ReadData());
}

/**
  * @brief  Writes to the selected LCD register.
  * @param  LCD_Reg: Address of the selected register.
  * @param  LCD_RegValue: Value to write to the selected register.
  * @retval None
  */
void ili9325_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue)
{
  LCD_IO_WriteReg(LCD_Reg);
  
  /* Write 16-bit GRAM Reg */
  LCD_IO_WriteData(LCD_RegValue);
}

/**
  * @brief  Reads the selected LCD Register.
  * @param  LCD_Reg: address of the selected register.
  * @retval LCD Register Value.
  */
uint16_t ili9325_ReadReg(uint8_t LCD_Reg)
{
  /* Write 16-bit Index (then Read Reg) */
  LCD_IO_WriteReg(LCD_Reg);
  
  /* Read 16-bit Reg */
  return (LCD_IO_ReadData());
}

/**
  * @brief  Sets a display window
  * @param  Xpos:   specifies the X bottom left position.
  * @param  Ypos:   specifies the Y bottom left position.
  * @param  Height: display window height.
  * @param  Width:  display window width.
  * @retval None
  */
void ili9325_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  /* Horizontal GRAM Start Address */
  ili9325_WriteReg(LCD_REG_80, (Ypos));
  /* Horizontal GRAM End Address */
  ili9325_WriteReg(LCD_REG_81, (Ypos + Height - 1));
  
  /* Vertical GRAM Start Address */
  ili9325_WriteReg(LCD_REG_82, ILI9325_LCD_PIXEL_WIDTH - Xpos - Width);
  /* Vertical GRAM End Address */
  ili9325_WriteReg(LCD_REG_83, ILI9325_LCD_PIXEL_WIDTH - Xpos - 1);  
}

/**
  * @brief  Draw vertical line.
  * @param  RGB_Code: Specifies the RGB color   
  * @param  Xpos:     specifies the X position.
  * @param  Ypos:     specifies the Y position.
  * @param  Length:   specifies the Line length.  
  * @retval None
  */
void ili9325_DrawHLine(uint16_t RGB_Code, uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
  uint16_t i = 0;
  
  /* Set Cursor */
  ili9325_SetCursor(Xpos, Ypos); 
  
  /* Prepare to write GRAM */
  LCD_IO_WriteReg(LCD_REG_34);

  for(i = 0; i < Length; i++)
  {
    /* Write 16-bit GRAM Reg */
    LCD_IO_WriteData(RGB_Code);
  }  
}

/**
  * @brief  Draw vertical line.
  * @param  RGB_Code: Specifies the RGB color    
  * @param  Xpos:     specifies the X position.
  * @param  Ypos:     specifies the Y position.
  * @param  Length:   specifies the Line length.  
  * @retval None
  */
void ili9325_DrawVLine(uint16_t RGB_Code, uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
  uint16_t i = 0;

  /* set GRAM write direction and BGR = 1 */
  /* I/D=00 (Horizontal : increment, Vertical : decrement) */
  /* AM=1 (address is updated in vertical writing direction) */
  ili9325_WriteReg(LCD_REG_3, 0x1010);
  
  /* Set Cursor */
  ili9325_SetCursor(Xpos, Ypos);
  
  /* Prepare to write GRAM */
  LCD_IO_WriteReg(LCD_REG_34);

  for(i = 0; i < Length; i++)
  {
    /* Write 16-bit GRAM Reg */
    LCD_IO_WriteData(RGB_Code);
  }
  
  /* set GRAM write direction and BGR = 1 */
  /* I/D=00 (Horizontal : increment, Vertical : decrement) */
  /* AM=1 (address is updated in vertical writing direction) */
  ili9325_WriteReg(LCD_REG_3, 0x1018);  
}

/**
  * @brief  Displays a bitmap picture.
  * @param  BmpAddress: Bmp picture address.
  * @param  Xpos: Bmp X position in the LCD
  * @param  Ypos: Bmp Y position in the LCD    
  * @retval None
  */
void ili9325_DrawBitmap(uint16_t Xpos, uint16_t Ypos, uint8_t *pbmp)
{
  uint32_t index = 0, size = 0;
  /* Read bitmap size */
  size = *(volatile uint16_t *) (pbmp + 2);
  size |= (*(volatile uint16_t *) (pbmp + 4)) << 16;
  /* Get bitmap data address offset */
  index = *(volatile uint16_t *) (pbmp + 10);
  index |= (*(volatile uint16_t *) (pbmp + 12)) << 16;
  size = (size - index)/2;
  pbmp += index;
  /* Set GRAM write direction and BGR = 1 */
  /* I/D=00 (Horizontal : decrement, Vertical : decrement) */
  /* AM=1 (address is updated in vertical writing direction) */
  ili9325_WriteReg(LCD_REG_3, 0x1008);

  /* Set Cursor */
  ili9325_SetCursor(Xpos, Ypos);  
  
  /* Prepare to write GRAM */
  LCD_IO_WriteReg(LCD_REG_34);
 
  for(index = 0; index < size; index++)
  {
    /* Write 16-bit GRAM Reg */
    LCD_IO_WriteData(*(volatile uint16_t *)pbmp);
    pbmp += 2;
  }
 
  /* Set GRAM write direction and BGR = 1 */
  /* I/D = 01 (Horizontal : increment, Vertical : decrement) */
  /* AM = 1 (address is updated in vertical writing direction) */
  ili9325_WriteReg(LCD_REG_3, 0x1018);
}

/**
  * @brief  Displays picture.
  * @param  pdata: picture address.
  * @param  Xpos: Image X position in the LCD
  * @param  Ypos: Image Y position in the LCD
  * @param  Xsize: Image X size in the LCD
  * @param  Ysize: Image Y size in the LCD
  * @retval None
  */
void ili9325_DrawRGBImage(uint16_t Xpos, uint16_t Ypos, uint16_t Xsize, uint16_t Ysize, uint8_t *pdata)
{
  uint32_t index = 0, size = 0;

  size = (Xsize * Ysize);

  /* Set Cursor */
  ili9325_SetCursor(Xpos, Ypos);  
  
  /* Prepare to write GRAM */
  LCD_IO_WriteReg(LCD_REG_34);
 
  for(index = 0; index < size; index++)
  {
    /* Write 16-bit GRAM Reg */
    LCD_IO_WriteData(*(volatile uint16_t *)pdata);
    pdata += 2;
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
