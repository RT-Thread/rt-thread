/**************************************************************************//**
* @file     2d.h
* @brief    N9H30 2DGE driver header file
*
* @note
* SPDX-License-Identifier: Apache-2.0
* Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#ifndef __NU_2D_H__
#define __NU_2D_H__

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup N9H30_Device_Driver N9H30 Device Driver
  @{
*/

/** @addtogroup N9H30_GE2D_Driver GE2D Driver
  @{
*/

/** @addtogroup N9H30_GE2D_EXPORTED_CONSTANTS GE2D Exported Constants
  @{
*/

/// @cond HIDDEN_SYMBOLS
typedef struct
{
    uint32_t    PatternA;
    uint32_t    PatternB;
} MONOPATTERN;

#define COLOR_KEY 0xFF000000
/// @endcond HIDDEN_SYMBOLS

///////////////////////////////////////////////////////////////////////////////
// Definition of ROP2
///////////////////////////////////////////////////////////////////////////////
#define    BLACKNESS       0x00  /*!< rop code: 0 */
#define    DSTINVERT       0x55  /*!< rop code: Dn  */
#define    MERGECOPY       0xC0  /*!< rop code: PSa  */
#define    MERGEPAINT      0xBB  /*!< rop code: DSno  */
#define    NOTSRCCOPY      0x33  /*!< rop code: Sn  */
#define    NOTSRCERASE     0x11  /*!< rop code: DSon  */
#define    PATCOPY         0xF0  /*!< rop code: P  */
#define    PATINVERT       0x5A  /*!< rop code: DPx  */
#define    PATPAINT        0xFB  /*!< rop code: DPSnoo  */
#define    SRCAND          0x88  /*!< rop code: DSa  */
#define    SRCCOPY         0xCC  /*!< rop code: S  */
#define    SRCERASE        0x44  /*!< rop code: SDna  */
#define    SRCINVERT       0x66  /*!< rop code: DSx  */
#define    SRCPAINT        0xEE  /*!< rop code: DSo  */
#define    WHITENESS       0xFF  /*!< rop code: 1  */

///////////////////////////////////////////////////////////////////////////////
// Definition of Pen Styles
///////////////////////////////////////////////////////////////////////////////
#define PS_SOLID        0xffff     /*!< pan style: solid */ //1111111111111111 (1111111111111111)
#define PS_DASH         0xcccc     /*!< pan style: dash */ //1100110011001100 (1111000011110000)
#define PS_DOT          0xaaaa     /*!< pan style: dot */ //1010101010101010 (1100110011001100)
#define PS_DASHDOT      0xe4e4     /*!< pan style: dash and dot */ //1110010011100100 (1111110000110000)
#define PS_DASHDOTDOT   0xeaea     /*!< pan style: dash and two dots  */ //1110101011101010 (1111110011001100)
#define PS_NULL         0x0000     /*!< pan style: null */ //0000000000000000 (0000000000000000)

///////////////////////////////////////////////////////////////////////////////
// Definition of Brush Styles
//
// HS_HORIZONTAL:   00000000     HS_BDIAGONAL:  00000001
//                  00000000                    00000010
//                  00000000                    00000100
//                  00000000                    00001000
//                  11111111                    00010000
//                  00000000                    00100000
//                  00000000                    01000000
//                  00000000                    10000000
//
// HS_VERTICAL:     00001000     HS_CROSS:      00001000
//                  00001000                    00001000
//                  00001000                    00001000
//                  00001000                    00001000
//                  00001000                    11111111
//                  00001000                    00001000
//                  00001000                    00001000
//                  00001000                    00001000
//
// HS_FDIAGONAL:    10000000     HS_DIAGCROSS:  10000001
//                  01000000                    01000010
//                  00100000                    00100100
//                  00010000                    00011000
//                  00001000                    00011000
//                  00000100                    00100100
//                  00000010                    01000010
//                  00000001                    10000001
///////////////////////////////////////////////////////////////////////////////
#define HS_HORIZONTAL   0   /*!< brush style: horizontal */
#define HS_VERTICAL     1   /*!< brush style: vertical */
#define HS_FDIAGONAL    2   /*!< brush style: fdiagonal */
#define HS_BDIAGONAL    3   /*!< brush style: bdiagonal */
#define HS_CROSS        4   /*!< brush style: cross */
#define HS_DIAGCROSS    5   /*!< brush style: diagcross */

#define MODE_OPAQUE             0                   /*!< opaque mode */
#define MODE_TRANSPARENT        1                   /*!< transparent mode */
#define MODE_SRC_TRANSPARENT    MODE_TRANSPARENT    /*!< source transparent mode */
#define MODE_DEST_TRANSPARENT   2                   /*!< destination transparent mode */

#define MODE_INSIDE_CLIP    0   /*!< clip inside */
#define MODE_OUTSIDE_CLIP   1   /*!< clip outside */

#define TYPE_MONO           0   /*!< mono */
#define TYPE_COLOR          1   /*!< color */

#define GE_BPP_8    0x00000000  /*!< 8bpp display */
#define GE_BPP_16   0x00000010  /*!< 16bpp display */
#define GE_BPP_32   0x00000020  /*!< 32bpp display */

#define RGB332 1    /*!< 8bpp display */
#define RGB565 2    /*!< 16bpp display */
#define RGB888 3    /*!< 24bpp display */

#define F8x8            0   /*!< 8x8 font support */
#define F8x16           1   /*!< 8x16 font support */

/*@}*/ /* end of group N9H30_GE2D_EXPORTED_CONSTANTS */

/** @addtogroup N9H30_GE2D_EXPORTED_FUNCTIONS GE2D Exported Functions
  @{
*/

void ge2dClearScreen(int color);
void ge2dSetWriteMask(int mask);
void ge2dSetSourceOriginStarting(void *ptr);
void ge2dSetDestinationOriginStarting(void *ptr);
void ge2dInit(int bpp, int width, int height, void *destination);
void ge2dReset(void);
void ge2dResetFIFO(void);
void ge2dBitblt_SetDrawMode(int opt, int ckey, int mask);
int ge2dBitblt_SetAlphaMode(int opt, int ks, int kd);
void ge2dBitblt_ScreenToScreen(int srcx, int srcy, int destx, int desty, int width, int height);
void ge2dBitblt_ScreenToScreenRop(int srcx, int srcy, int destx, int desty, int width, int height, int rop);
void ge2dBitblt_SourceToDestination(int srcx, int srcy, int destx, int desty, int width, int height, int srcpitch, int destpitch);
void ge2dClip_SetClip(int x1, int y1, int x2, int y2);
void ge2dClip_SetClipMode(int opt);
void ge2dDrawFrame(int x1, int y1, int x2, int y2, int color, int opt);
void ge2dLine_DrawSolidLine(int x1, int y1, int x2, int y2, int color);
void ge2dLine_DrawSolidLine_RGB565(int x1, int y1, int x2, int y2, int color);
void ge2dLine_DrawStyledLine(int x1, int y1, int x2, int y2, int style, int fgcolor, int bkcolor, int draw_mode);
void ge2dLine_DrawStyledLine_RGB565(int x1, int y1, int x2, int y2, int style, int fgcolor, int bkcolor, int draw_mode);
void ge2dFill_Solid(int dx, int dy, int width, int height, int color);
void ge2dFill_Solid_RGB565(int dx, int dy, int width, int height, int color);
void ge2dFill_SolidBackground(int dx, int dy, int width, int height, int color);
void ge2dFill_ColorPattern(int dx, int dy, int width, int height);
void ge2dFill_MonoPattern(int dx, int dy, int width, int height, int opt);
void ge2dFill_ColorPatternROP(int sx, int sy, int width, int height, int rop);
void ge2dFill_MonoPatternROP(int sx, int sy, int width, int height, int rop, int opt);
void ge2dFill_TileBlt(int srcx, int srcy, int destx, int desty, int width, int height, int x_count, int y_count);
void ge2dHostBlt_Write(int x, int y, int width, int height, void *buf);
void ge2dHostBlt_Read(int x, int y, int width, int height, void *buf);
void ge2dHostBlt_Sprite(int x, int y, int width, int height, void *buf);
void ge2dRotation(int srcx, int srcy, int destx, int desty, int width, int height, int ctl);
void ge2dSpriteBlt_Screen(int destx, int desty, int sprite_width, int sprite_height, void *buf);
void ge2dSpriteBltx_Screen(int x, int y, int sprite_sx, int sprite_sy, int width, int height, int sprite_width, int sprite_height, void *buf);
void ge2dSpriteBlt_ScreenRop(int x, int y, int sprite_width, int sprite_height, void *buf, int rop);
void ge2dSpriteBltx_ScreenRop(int x, int y, int sprite_sx, int sprite_sy, int width, int height, int sprite_width, int sprite_height, void *buf, int rop);
void ge2dColorExpansionBlt(int x, int y, int width, int height, int fore_color, int back_color, int opt, void *buf);
void ge2dHostColorExpansionBlt(int x, int y, int width, int height, int fore_color, int back_color, int opt, void *buf);
void ge2dInitMonoPattern(int opt, int fore_color, int back_color);
void ge2dInitMonoInputPattern(uint32_t PatternA, uint32_t PatternB, int fore_color, int back_color);
void ge2dInitColorPattern(int patformat, void *patdata);
void ge2dFont_PutChar(int x, int y, char asc_code, int fore_color, int back_color, int draw_mode, int font_id);
void ge2dFont_PutString(int x, int y, char *str, int fore_color, int back_color, int draw_mode, int font_id);

/*@}*/ /* end of group N9H30_GE2D_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group N9H30_GE2D_Driver */

/*@}*/ /* end of group N9H30_Device_Driver */


#ifdef __cplusplus
}
#endif

#endif //__NU_2D_H__

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
