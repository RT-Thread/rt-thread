/*************************************************************************
 *
*    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2008
 *
 *    File name   : drv_glcd.h
 *    Description : Graphical LCD driver include file
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
#include "lpc_types.h"

#ifndef __GLCD_DRV_H
#define __GLCD_DRV_H

#ifndef EOF
#define EOF (-1)
#endif

typedef unsigned long U32;
typedef unsigned char U8;
typedef unsigned long Boolean;
/**
 * @brief A struct for Bitmap on LCD screen
 */
typedef struct _Bmp_t
{
  U32  H_Size;
  U32  V_Size;
  U32  BitsPP;
  U32  BytesPP;
  U32 *pPalette;
  U32 *pPicStream;
  U8 *pPicDesc;
} Bmp_t, *pBmp_t;

/**
 * @brief A struct for Font Type on LCD screen
 */

typedef struct _FontType_t
{
  U32 H_Size;
  U32 V_Size;
  U32 CharacterOffset;
  U32 CharactersNuber;
  U8 *pFontStream;
  U8 *pFontDesc;
} FontType_t, *pFontType_t;

typedef U32 LdcPixel_t, *pLdcPixel_t;

#define C_GLCD_REFRESH_FREQ     (60HZ)
#define C_GLCD_H_SIZE           480
#define C_GLCD_H_PULSE          2   //
#define C_GLCD_H_FRONT_PORCH    5   //
#define C_GLCD_H_BACK_PORCH     40  //
#define C_GLCD_V_SIZE           272
#define C_GLCD_V_PULSE          2
#define C_GLCD_V_FRONT_PORCH    8
#define C_GLCD_V_BACK_PORCH     8

#define C_GLCD_PWR_ENA_DIS_DLY  10000
#define C_GLCD_ENA_DIS_DLY      10000

//Cursor 64x64 pixels
#define CURSOR_H_SIZE 64
#define CURSOR_V_SIZE 64
//
#define CIRCLE_R  18


#define CRSR_PIX_32     0
#define CRSR_PIX_64     1
#define CRSR_ASYNC      0
#define CRSR_FRAME_SYNC 2

#define TEXT_DEF_TAB_SIZE 5

#define TEXT_BEL1_FUNC()

void GLCD_Init (void* VRAMBase);
void GLCD_SetPallet (const U32 * pPallete);
void GLCD_Ctrl (Bool bEna);
void GLCD_Cursor_Cfg(int Cfg);
void GLCD_Cursor_En(int cursor);
void GLCD_Cursor_Dis(int cursor);
void GLCD_Move_Cursor(int x, int y);
void GLCD_Copy_Cursor (const U32 *pCursor, int cursor, int size);
void GLCD_SetFont(pFontType_t pFont, LdcPixel_t Color, LdcPixel_t BackgndColor);
void GLCD_SetWindow(U32 X_Left, U32 Y_Up,
                    U32 X_Right, U32 Y_Down);
void GLCD_TextSetPos(U32 X, U32 Y);
void GLCD_TextSetTabSize(U32 Size);
static void LCD_SET_WINDOW (U32 X_Left, U32 X_Right,
                            U32 Y_Up, U32 Y_Down);
static void LCD_WRITE_PIXEL (U32 Pixel);
static Bool GLCD_TextCalcWindow (U32 * pXL, U32 * pXR,
                                    U32 * pYU, U32 * pYD,
                                    U32 * pH_Size, U32 * pV_Size);
void GLCD_LoadPic (U32 X_Left, U32 Y_Up, Bmp_t * pBmp, U32 Mask);
int _putchar (int c);


#endif // __GLCD_DRV_H
