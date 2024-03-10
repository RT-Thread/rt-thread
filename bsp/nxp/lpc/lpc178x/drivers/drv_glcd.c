/*************************************************************************
 *
*    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2008
 *
 *    File name   : drv_glcd.c
 *    Description : Graphical LCD driver
 *
 *    History :
 *    1. Date        : 6, March 2008
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *
 *    $Revision: 24636 $
 *
 *    @Modify: NXP MCU Application Team - NguyenCao
 *    @Date: 04. March. 2011
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//#include "ConstGlbPtrs.h"
//#include "Ex_sdram.h"
#include "drv_glcd.h"
#include "lpc177x_8x_clkpwr.h"
#include "lpc177x_8x_pinsel.h"

//#include "Cursor.h"
//#include "logo.h"

//#define MHZ

#define C_GLCD_CLK_PER_LINE     (C_GLCD_H_SIZE + C_GLCD_H_PULSE + C_GLCD_H_FRONT_PORCH + C_GLCD_H_BACK_PORCH)
#define C_GLCD_LINES_PER_FRAME  (C_GLCD_V_SIZE + C_GLCD_V_PULSE + C_GLCD_V_FRONT_PORCH + C_GLCD_V_BACK_PORCH)
#define C_GLCD_PIX_CLK          (C_GLCD_CLK_PER_LINE * C_GLCD_LINES_PER_FRAME)

//LPC_LCD_TypeDef   * const g_pLCD = ((LPC_LCD_TypeDef*) LPC_LCD_BASE);
//LPC_SC_TypeDef * const g_pSC = ((LPC_SC_TypeDef*) LPC_SC_BASE);

#define SDRAM_BASE          0xA0000000     /* CS0 */
#define SDRAM_BASE_ADDR     SDRAM_BASE

#define LCD_VRAM_BASE_ADDR  ((unsigned long)SDRAM_BASE_ADDR + 0x00000000)
#define LCD_CURSOR_BASE_ADDR    ((unsigned long)0x20088800)


static pFontType_t pCurrFont = NULL;
static LdcPixel_t TextColour;
static LdcPixel_t TextBackgndColour;

static unsigned long TextX_Pos = 0;
static unsigned long TextY_Pos = 0;

static unsigned long XL_Win = 0;
static unsigned long YU_Win = 0;
static unsigned long XR_Win = C_GLCD_H_SIZE-1;
static unsigned long YD_Win = C_GLCD_V_SIZE-1;

static unsigned long TabSize = TEXT_DEF_TAB_SIZE;

static unsigned long WindY_Size, WindX_Size;
static unsigned long CurrY_Size, CurrX_Size;
static unsigned long *pWind;
static unsigned long *pPix;

/*************************************************************************
 * Function Name: GLCD_Cursor_Cnfg
 * Parameters:
 *
 * Return: none
 *
 * Description: Configure the cursor
 *
 *************************************************************************/
void GLCD_Cursor_Cfg(int Cfg)
{
  LPC_LCD->CRSR_CFG = Cfg;
}
/*************************************************************************
 * Function Name: GLCD_Cursor_En
 * Parameters: cursor - Cursor Number
 *
 * Return: none
 *
 * Description: Enable Cursor
 *
 *************************************************************************/
void GLCD_Cursor_En(int cursor)
{
  LPC_LCD->CRSR_CTRL |= (cursor<<4);
  LPC_LCD->CRSR_CTRL |= 1;
}

/*************************************************************************
 * Function Name: GLCD_Cursor_Dis
 * Parameters: None
 *
 * Return: none
 *
 * Description: Disable Cursor
 *
 *************************************************************************/
void GLCD_Cursor_Dis(int cursor)
{
  LPC_LCD->CRSR_CTRL &= (1<<0);
}

/*************************************************************************
 * Function Name: GLCD_Move_Cursor
 * Parameters: x - cursor x position
 *             y - cursor y position
 *
 * Return: none
 *
 * Description: Moves cursor on position (x,y). Negativ values are posible.
 *
 *************************************************************************/
void GLCD_Move_Cursor(int x, int y)
{
  LPC_LCD->CRSR_CLIP = 0;
  LPC_LCD->CRSR_XY = 0;
  if(0 <= x)
  {//no clipping
    LPC_LCD->CRSR_XY |= (x & 0x3FF);
  }
  else
  {//clip x
    LPC_LCD->CRSR_CLIP |= -x;
  }

  if(0 <= y)
  {//no clipping

    LPC_LCD->CRSR_XY |= (y << 16);
  }
  else
  {//clip y
    LPC_LCD->CRSR_CLIP |= (-y << 8);
  }
}

/*************************************************************************
 * Function Name: GLCD_Copy_Cursor
 * Parameters: pCursor - pointer to cursor conts image
 *             cursor - cursor Number (0,1,2 or 3)
 *                      for 64x64(size 256) pix cursor always use 0
 *             size - cursor size in words
 * Return: none
 *
 * Description: Copy Cursor from const image to LCD RAM image
 *
 *************************************************************************/
void GLCD_Copy_Cursor (const unsigned long *pCursor, int cursor, int size)
{
    unsigned long i ;
    unsigned long * pDst = (unsigned long *)LCD_CURSOR_BASE_ADDR;

    pDst += cursor*64;

    for(i = 0; i < size ; i++)
//     *pDst++ = *pCursor++;
    {
        *pDst = *pCursor;
        pDst++;
        pCursor++;
    }
}
/*************************************************************************
 * Function Name: GLCD_Init
 * Parameters: const unsigned long *pPain, const unsigned long * pPallete
 *
 * Return: none
 *
 * Description: GLCD controller init
 *
 *************************************************************************/
void GLCD_Init (void* VRAMBase)
{
    // unsigned long i;
    // Assign pins
    LPC_IOCON->P2_9     = 0x06; // VD3,     R0
    LPC_IOCON->P2_6     = 0x07; // VD4,     R1
    LPC_IOCON->P2_7     = 0x07; // VD5,     R2
    LPC_IOCON->P4_28    = 0x05; // VD6,     R3
    LPC_IOCON->P4_29 = 0x05;    // VD7,     R4

    LPC_IOCON->P1_20    = 0x07; // VD10,    G0
    LPC_IOCON->P1_21    = 0x07; // VD11,    G1
    LPC_IOCON->P1_22    = 0x07; // VD12,    G2
    LPC_IOCON->P1_23    = 0x07; // VD13,    G3
    LPC_IOCON->P1_24    = 0x07; // VD14,    G4
    LPC_IOCON->P1_25    = 0x07; // VD15,    G5

    LPC_IOCON->P2_13    = 0x07; // VD19,    B0
    LPC_IOCON->P1_26 = 0x07;    // VD20,    B1
    LPC_IOCON->P1_27 = 0x07;    // VD21,    B2
    LPC_IOCON->P1_28 = 0x07;    // VD22,    B3
    LPC_IOCON->P1_29 = 0x07;    // VD23,    B4

    LPC_IOCON->P2_2 = 0x07; // DCLK
    LPC_IOCON->P2_0 = 0x07; // DSIP(power)
    LPC_IOCON->P2_5 = 0x07; // HSYNC
    LPC_IOCON->P2_3 = 0x07; // VSYNC
    LPC_IOCON->P2_4 = 0x07; // DataEn

//  LPC_IOCON->P5_4 = 0x00; // Backlight

    // >>> debug >>>

    // <<< debug <<<

    /*Back light enable*/
//  LPC_GPIO5->DIR = (1<<4);
//  LPC_GPIO5->SET= (5<<4);

    //Turn on LCD clock
    CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCLCD, ENABLE);

    // Disable cursor
    LPC_LCD->CRSR_CTRL &=~(1<<0);

    // disable GLCD controller
    LPC_LCD->CTRL = 0;
    // RGB888
    LPC_LCD->CTRL &= ~(0x07 <<1);
    LPC_LCD->CTRL |= (6<<1);

    // TFT panel
    LPC_LCD->CTRL |= (1<<5);
    // single panel
    LPC_LCD->CTRL &= ~(1<<7);
    // notmal output
    LPC_LCD->CTRL &= ~(1<<8);
    // little endian byte order
    LPC_LCD->CTRL &= ~(1<<9);
    // little endian pix order
    LPC_LCD->CTRL &= ~(1<<10);
    // disable power
    LPC_LCD->CTRL &= ~(1<<11);
    // init pixel clock
//  g_pSC->LCD_CFG = CLKPWR_GetCLK(CLKPWR_CLKTYPE_PER) / ((unsigned long)C_GLCD_PIX_CLK);
    LPC_SC->LCD_CFG = CLKPWR_GetCLK(CLKPWR_CLKTYPE_PER) / ((unsigned long)C_GLCD_PIX_CLK);
    // bypass inrenal clk divider
    LPC_LCD->POL |=(1<<26);
    // clock source for the LCD block is HCLK
    LPC_LCD->POL &= ~(1<<5);
    // LCDFP pin is active LOW and inactive HIGH
    LPC_LCD->POL |= (1<<11);
    // LCDLP pin is active LOW and inactive HIGH
    LPC_LCD->POL |= (1<<12);
    // data is driven out into the LCD on the falling edge
    LPC_LCD->POL &= ~(1<<13);
    // active high
    LPC_LCD->POL &= ~(1<<14);
    LPC_LCD->POL &= ~(0x3FF <<16);
    LPC_LCD->POL |= (C_GLCD_H_SIZE-1)<<16;

    // init Horizontal Timing
    LPC_LCD->TIMH = 0; //reset TIMH before set value
    LPC_LCD->TIMH |= (C_GLCD_H_BACK_PORCH - 1)<<24;
    LPC_LCD->TIMH |= (C_GLCD_H_FRONT_PORCH - 1)<<16;
    LPC_LCD->TIMH |= (C_GLCD_H_PULSE - 1)<<8;
    LPC_LCD->TIMH |= ((C_GLCD_H_SIZE/16) - 1)<<2;

    // init Vertical Timing
    LPC_LCD->TIMV = 0;  //reset TIMV value before setting
    LPC_LCD->TIMV |= (C_GLCD_V_BACK_PORCH)<<24;
    LPC_LCD->TIMV |= (C_GLCD_V_FRONT_PORCH)<<16;
    LPC_LCD->TIMV |= (C_GLCD_V_PULSE - 1)<<10;
    LPC_LCD->TIMV |= C_GLCD_V_SIZE - 1;
    // Frame Base Address doubleword aligned
    LPC_LCD->UPBASE = (unsigned long)VRAMBase & ~7UL ;
    LPC_LCD->LPBASE = (unsigned long)VRAMBase & ~7UL ;
}

/*************************************************************************
 * Function Name: GLCD_SetPallet
 * Parameters: const unsigned long * pPallete
 *
 * Return: none
 *
 * Description: GLCD init colour pallete
 *
 *************************************************************************/
void GLCD_SetPallet (const unsigned long * pPallete)
{
    unsigned long i;
    unsigned long * pDst = (unsigned long *)LPC_LCD->PAL;
    // //assert(pPallete);
    for (i = 0; i < 128; i++)
    {
    *pDst++ = *pPallete++;
    }
}

/*************************************************************************
 * Function Name: GLCD_Ctrl
 * Parameters: Bool bEna
 *
 * Return: none
 *
 * Description: GLCD enable disabe sequence
 *
 *************************************************************************/
void GLCD_Ctrl (Bool bEna)
{
    volatile unsigned long i;
  if (bEna)
  {
//    LCD_CTRL_bit.LcdEn = 1;
    LPC_LCD->CTRL |= (1<<0);
    for(i = C_GLCD_PWR_ENA_DIS_DLY; i; i--);
//    LCD_CTRL_bit.LcdPwr= 1;   // enable power
    LPC_LCD->CTRL |= (1<<11);
  }
  else
  {
//    LCD_CTRL_bit.LcdPwr= 0;   // disable power
    LPC_LCD->CTRL &= ~(1<<11);
    for(i = C_GLCD_PWR_ENA_DIS_DLY; i; i--);
//    LCD_CTRL_bit.LcdEn = 0;
    LPC_LCD->CTRL &= ~(1<<0);
  }
}

/*************************************************************************
 * Function Name: GLCD_SetFont
 * Parameters: pFontType_t pFont, LdcPixel_t Color
 *              LdcPixel_t BackgndColor
 *
 * Return: none
 *
 * Description: Set current font, font color and background color
 *
 *************************************************************************/
void GLCD_SetFont(pFontType_t pFont, LdcPixel_t Color, LdcPixel_t BackgndColor)
{
  pCurrFont = pFont;
  TextColour = Color;
  TextBackgndColour = BackgndColor;
}

/*************************************************************************
 * Function Name: GLCD_SetWindow
 * Parameters: unsigned long X_Left, unsigned long Y_Up,
 *             unsigned long X_Right, unsigned long Y_Down
 *
 * Return: none
 *
 * Description: Set draw window XY coordinate in pixels
 *
 *************************************************************************/
void GLCD_SetWindow(unsigned long X_Left, unsigned long Y_Up,
                    unsigned long X_Right, unsigned long Y_Down)
{
  // //assert(X_Right < C_GLCD_H_SIZE);
  // //assert(Y_Down < C_GLCD_V_SIZE);
  // //assert(X_Left < X_Right);
  //assert(Y_Up < Y_Down);
  XL_Win = X_Left;
  YU_Win = Y_Up;
  XR_Win = X_Right;
  YD_Win = Y_Down;
}

/*************************************************************************
 * Function Name: GLCD_TextSetPos
 * Parameters: unsigned long X_UpLeft, unsigned long Y_UpLeft,
 *             unsigned long X_DownLeft, unsigned long Y_DownLeft
 *
 * Return: none
 *
 * Description: Set text X,Y coordinate in characters
 *
 *************************************************************************/
void GLCD_TextSetPos(unsigned long X, unsigned long Y)
{
  TextX_Pos = X;
  TextY_Pos = Y;
}

/*************************************************************************
 * Function Name: GLCD_TextSetTabSize
 * Parameters: unsigned long Size
 *
 * Return: none
 *
 * Description: Set text tab size in characters
 *
 *************************************************************************/
void GLCD_TextSetTabSize(unsigned long Size)
{
  TabSize = Size;
}

/*************************************************************************
 * Function Name: LCD_SET_WINDOW
 * Parameters: int c
 *
 * Return: none
 *
 * Description: Put char function
 *
 *************************************************************************/
static
void LCD_SET_WINDOW (unsigned long X_Left, unsigned long X_Right,
                     unsigned long Y_Up, unsigned long Y_Down)
{
  pPix = pWind = ((unsigned long *)LCD_VRAM_BASE_ADDR) + X_Left + (Y_Up*C_GLCD_H_SIZE);
  WindX_Size = X_Right - X_Left;
  WindY_Size = Y_Down - Y_Up;
  CurrX_Size = CurrY_Size = 0;
}

/*************************************************************************
 * Function Name: LCD_SET_WINDOW
 * Parameters: int c
 *
 * Return: none
 *
 * Description: Put char function
 *
 *************************************************************************/
static
void LCD_WRITE_PIXEL (unsigned long Pixel)
{
  *pPix++ = Pixel;
  if (++CurrX_Size > WindX_Size)
  {
    CurrX_Size = 0;
    if(++CurrY_Size > WindY_Size)
    {
      CurrY_Size = 0;
    }
    pPix = pWind + CurrY_Size * C_GLCD_H_SIZE;
  }
}

/*************************************************************************
 * Function Name: GLCD_TextCalcWindow
 * Parameters: unsigned long * pXL, unsigned long * pXR,
 *             unsigned long * pYU, unsigned long * pYD,
 *             unsigned long * pH_Size, unsigned long * pV_Size
 *
 * Return: Bool
 *          FALSE - out of window coordinate aren't valid
 *          TRUE  - the returned coordinate are valid
 *
 * Description: Calculate character window
 *
 *************************************************************************/
static
Bool GLCD_TextCalcWindow (unsigned long * pXL, unsigned long * pXR,
                             unsigned long * pYU, unsigned long * pYD,
                             unsigned long * pH_Size, unsigned long * pV_Size)
{
  *pH_Size = pCurrFont->H_Size;
  *pV_Size = pCurrFont->V_Size;
  *pXL = XL_Win + (TextX_Pos*pCurrFont->H_Size);
  if(*pXL > XR_Win)
  {
    return(FALSE);
  }
  *pYU = YU_Win + (TextY_Pos*pCurrFont->V_Size);
  if(*pYU > YD_Win)
  {
    return(FALSE);
  }

  *pXR   = XL_Win + ((TextX_Pos+1)*pCurrFont->H_Size) - 1;
  if(*pXR > XR_Win)
  {
    *pH_Size -= *pXR - XR_Win;
    *pXR = XR_Win;
  }

  *pYD = YU_Win + ((TextY_Pos+1)*pCurrFont->V_Size) - 1;
  if(*pYD > YD_Win)
  {
    *pV_Size -= *pYD - YD_Win;
    *pYD = YD_Win;
  }

  return(TRUE);
}

/*************************************************************************
 * Function Name: putchar
 * Parameters: int c
 *
 * Return: none
 *
 * Description: Put char function
 *
 *************************************************************************/
int _putchar (int c)
{
uint8_t *pSrc;
unsigned long H_Line;
unsigned long xl,xr,yu,yd,Temp,V_Size, H_Size, SrcInc = 1;
unsigned long WhiteSpaceNumb;
unsigned long i, j, k;
  if(pCurrFont == NULL)
  {
    return(EOF);
  }
  H_Line = (pCurrFont->H_Size / 8) + ((pCurrFont->H_Size % 8)?1:0);
  switch(c)
  {
  case '\n':  // go to begin of next line (NewLine)
    ++TextY_Pos;
    break;
  case '\r':  // go to begin of this line (Carriage Return)
    // clear from current position to end of line
    while(GLCD_TextCalcWindow(&xl,&xr,&yu,&yd,&H_Size,&V_Size))
    {
      LCD_SET_WINDOW(xl,xr,yu,yd);
        for(i = 0; i < V_Size; ++i)
        {
          for(j = 0; j < H_Size; ++j)
          {
            LCD_WRITE_PIXEL(TextBackgndColour);
          }
        }
        ++TextX_Pos;
    }
    TextX_Pos = 0;
    break;
  case '\b': // go back one position (BackSpace)
    if(TextX_Pos)
    {
      --TextX_Pos;
      // del current position
        if(GLCD_TextCalcWindow(&xl,&xr,&yu,&yd,&H_Size,&V_Size))
        {
        LCD_SET_WINDOW(xl,xr,yu,yd);
            for(i = 0; i < V_Size; ++i)
            {
              for(j = 0; j < H_Size; ++j)
              {
                LCD_WRITE_PIXEL(TextBackgndColour);
              }
            }
        }
    }
    break;
  case '\t':  // go to next Horizontal Tab stop
    WhiteSpaceNumb = TabSize - (TextX_Pos%TabSize);
    for(k = 0; k < WhiteSpaceNumb; ++k)
    {
      LCD_SET_WINDOW(xl,xr,yu,yd);
        if(GLCD_TextCalcWindow(&xl,&xr,&yu,&yd,&H_Size,&V_Size))
        {
            for(i = 0; i < V_Size; ++i)
            {
              for(j = 0; j < H_Size; ++j)
              {
                LCD_WRITE_PIXEL(TextBackgndColour);
              }
            }
            ++TextX_Pos;
        }
        else
        {
            break;
        }
    }
    break;
  case '\f':  // go to top of page (Form Feed)
    // clear entire window
    H_Size = XR_Win - XL_Win;
    V_Size = YD_Win - YU_Win;
    // set character window X left, Y right
    LCD_SET_WINDOW(XL_Win,XR_Win,YU_Win,YD_Win);
    // Fill window with background font color
    for(i = 0; i <= V_Size; ++i)
    {
      for(j = 0; j <= H_Size; ++j)
      {
        LCD_WRITE_PIXEL(TextBackgndColour);
      }
    }

    TextX_Pos = TextY_Pos = 0;
    break;
  case '\a':  // signal an alert (BELl)
    TEXT_BEL1_FUNC();
    break;
  default:
    // Calculate the current character base address from stream
    // and the character position
    if((c <  pCurrFont->CharacterOffset) &&
         (c >= pCurrFont->CharactersNuber))
    {
        c = 0;
    }
    else
    {
        c -= pCurrFont->CharacterOffset;
    }
    pSrc = pCurrFont->pFontStream + (H_Line * pCurrFont->V_Size * c);
    // Calculate character window and fit it in the text window
    if(GLCD_TextCalcWindow(&xl,&xr,&yu,&yd,&H_Size,&V_Size))
    {
        // set character window X left, Y right
        LCD_SET_WINDOW(xl,xr,yu,yd);
        // Send char data
        for(i = 0; i < V_Size; ++i)
        {
        SrcInc = H_Line;
        for(j = 0; j < H_Size; ++j)
          {
            Temp = (*pSrc & (1UL << (j&0x7)))?TextColour:TextBackgndColour;
            LCD_WRITE_PIXEL(Temp);
            if((j&0x7) == 7)
            {
              ++pSrc;
            --SrcInc;
            }
          }
        // next line of character
          pSrc += SrcInc;
        }
    }
    ++TextX_Pos;
  }
  return(c);
}

/*************************************************************************
 * Function Name: GLCD_LoadPic
 * Parameters: unsigned long X_Left, unsigned long Y_Up, Bmp_t * pBmp
 *
 * Return: none
 *
 * Description: Load picture in VRAM memory area
 *
 *************************************************************************/
void GLCD_LoadPic (unsigned long X_Left, unsigned long Y_Up, Bmp_t * pBmp, unsigned long Mask)
{
unsigned long i, j;
unsigned long * pData = ((unsigned long *) LCD_VRAM_BASE_ADDR) + X_Left + (Y_Up * C_GLCD_H_SIZE);
unsigned long * pSrc = pBmp->pPicStream;
unsigned long X_LeftHold;
  for(i = 0; i < pBmp->V_Size; i++)
  {
    if(Y_Up++ >= C_GLCD_V_SIZE)
    {
      break;
    }
    for(j = 0; j < pBmp->H_Size; j++)
    {
      if(X_LeftHold++ >= C_GLCD_H_SIZE)
      {
        pSrc += pBmp->H_Size - j;
        break;
      }
      *(pData+j) = *pSrc++ ^ Mask;
    }
    X_LeftHold = X_Left;
    pData += C_GLCD_H_SIZE;
  }
}


