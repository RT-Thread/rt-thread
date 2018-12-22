/******************************************************************************
**
** \file      gh_vo_i80.c
**
** \brief     VO I80 access function..
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      Do not modify this file as it is generated automatically.
**
******************************************************************************/
#include "gh_vo_i80.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register VO_I80_Data_Format (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_I80_set_Data_Format(U32 data)
{
    *(volatile U32 *)REG_VO_I80_DATA_FORMAT = data;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Data_Format] <-- 0x%08x\n",
                        REG_VO_I80_DATA_FORMAT,data,data);
    #endif
}
U32  GH_VO_I80_get_Data_Format(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_DATA_FORMAT);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Data_Format] --> 0x%08x\n",
                        REG_VO_I80_DATA_FORMAT,value);
    #endif
    return value;
}
void GH_VO_I80_set_Data_Format_data_width(U8 data)
{
    GH_VO_I80_DATA_FORMAT_S d;
    d.all = *(volatile U32 *)REG_VO_I80_DATA_FORMAT;
    d.bitc.data_width = data;
    *(volatile U32 *)REG_VO_I80_DATA_FORMAT = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Data_Format_data_width] <-- 0x%08x\n",
                        REG_VO_I80_DATA_FORMAT,d.all,d.all);
    #endif
}
U8   GH_VO_I80_get_Data_Format_data_width(void)
{
    GH_VO_I80_DATA_FORMAT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_DATA_FORMAT);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Data_Format_data_width] --> 0x%08x\n",
                        REG_VO_I80_DATA_FORMAT,value);
    #endif
    return tmp_value.bitc.data_width;
}
void GH_VO_I80_set_Data_Format_color_format(U8 data)
{
    GH_VO_I80_DATA_FORMAT_S d;
    d.all = *(volatile U32 *)REG_VO_I80_DATA_FORMAT;
    d.bitc.color_format = data;
    *(volatile U32 *)REG_VO_I80_DATA_FORMAT = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Data_Format_color_format] <-- 0x%08x\n",
                        REG_VO_I80_DATA_FORMAT,d.all,d.all);
    #endif
}
U8   GH_VO_I80_get_Data_Format_color_format(void)
{
    GH_VO_I80_DATA_FORMAT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_DATA_FORMAT);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Data_Format_color_format] --> 0x%08x\n",
                        REG_VO_I80_DATA_FORMAT,value);
    #endif
    return tmp_value.bitc.color_format;
}
void GH_VO_I80_set_Data_Format_data_transfer_format(U8 data)
{
    GH_VO_I80_DATA_FORMAT_S d;
    d.all = *(volatile U32 *)REG_VO_I80_DATA_FORMAT;
    d.bitc.data_transfer_format = data;
    *(volatile U32 *)REG_VO_I80_DATA_FORMAT = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Data_Format_data_transfer_format] <-- 0x%08x\n",
                        REG_VO_I80_DATA_FORMAT,d.all,d.all);
    #endif
}
U8   GH_VO_I80_get_Data_Format_data_transfer_format(void)
{
    GH_VO_I80_DATA_FORMAT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_DATA_FORMAT);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Data_Format_data_transfer_format] --> 0x%08x\n",
                        REG_VO_I80_DATA_FORMAT,value);
    #endif
    return tmp_value.bitc.data_transfer_format;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Pic_Resolution (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_I80_set_Pic_Resolution(U32 data)
{
    *(volatile U32 *)REG_VO_I80_PIC_RESOLUTION = data;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Pic_Resolution] <-- 0x%08x\n",
                        REG_VO_I80_PIC_RESOLUTION,data,data);
    #endif
}
U32  GH_VO_I80_get_Pic_Resolution(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_PIC_RESOLUTION);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Pic_Resolution] --> 0x%08x\n",
                        REG_VO_I80_PIC_RESOLUTION,value);
    #endif
    return value;
}
void GH_VO_I80_set_Pic_Resolution_width(U16 data)
{
    GH_VO_I80_PIC_RESOLUTION_S d;
    d.all = *(volatile U32 *)REG_VO_I80_PIC_RESOLUTION;
    d.bitc.width = data;
    *(volatile U32 *)REG_VO_I80_PIC_RESOLUTION = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Pic_Resolution_width] <-- 0x%08x\n",
                        REG_VO_I80_PIC_RESOLUTION,d.all,d.all);
    #endif
}
U16  GH_VO_I80_get_Pic_Resolution_width(void)
{
    GH_VO_I80_PIC_RESOLUTION_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_PIC_RESOLUTION);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Pic_Resolution_width] --> 0x%08x\n",
                        REG_VO_I80_PIC_RESOLUTION,value);
    #endif
    return tmp_value.bitc.width;
}
void GH_VO_I80_set_Pic_Resolution_height(U16 data)
{
    GH_VO_I80_PIC_RESOLUTION_S d;
    d.all = *(volatile U32 *)REG_VO_I80_PIC_RESOLUTION;
    d.bitc.height = data;
    *(volatile U32 *)REG_VO_I80_PIC_RESOLUTION = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Pic_Resolution_height] <-- 0x%08x\n",
                        REG_VO_I80_PIC_RESOLUTION,d.all,d.all);
    #endif
}
U16  GH_VO_I80_get_Pic_Resolution_height(void)
{
    GH_VO_I80_PIC_RESOLUTION_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_PIC_RESOLUTION);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Pic_Resolution_height] --> 0x%08x\n",
                        REG_VO_I80_PIC_RESOLUTION,value);
    #endif
    return tmp_value.bitc.height;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Pixel_RdWrcmd (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_I80_set_Pixel_RdWrcmd(U32 data)
{
    *(volatile U32 *)REG_VO_I80_PIXEL_RDWRCMD = data;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Pixel_RdWrcmd] <-- 0x%08x\n",
                        REG_VO_I80_PIXEL_RDWRCMD,data,data);
    #endif
}
U32  GH_VO_I80_get_Pixel_RdWrcmd(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_PIXEL_RDWRCMD);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Pixel_RdWrcmd] --> 0x%08x\n",
                        REG_VO_I80_PIXEL_RDWRCMD,value);
    #endif
    return value;
}
void GH_VO_I80_set_Pixel_RdWrcmd_pixel_wrcmd(U16 data)
{
    GH_VO_I80_PIXEL_RDWRCMD_S d;
    d.all = *(volatile U32 *)REG_VO_I80_PIXEL_RDWRCMD;
    d.bitc.pixel_wrcmd = data;
    *(volatile U32 *)REG_VO_I80_PIXEL_RDWRCMD = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Pixel_RdWrcmd_pixel_wrcmd] <-- 0x%08x\n",
                        REG_VO_I80_PIXEL_RDWRCMD,d.all,d.all);
    #endif
}
U16  GH_VO_I80_get_Pixel_RdWrcmd_pixel_wrcmd(void)
{
    GH_VO_I80_PIXEL_RDWRCMD_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_PIXEL_RDWRCMD);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Pixel_RdWrcmd_pixel_wrcmd] --> 0x%08x\n",
                        REG_VO_I80_PIXEL_RDWRCMD,value);
    #endif
    return tmp_value.bitc.pixel_wrcmd;
}
void GH_VO_I80_set_Pixel_RdWrcmd_pixel_rdcmd(U16 data)
{
    GH_VO_I80_PIXEL_RDWRCMD_S d;
    d.all = *(volatile U32 *)REG_VO_I80_PIXEL_RDWRCMD;
    d.bitc.pixel_rdcmd = data;
    *(volatile U32 *)REG_VO_I80_PIXEL_RDWRCMD = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Pixel_RdWrcmd_pixel_rdcmd] <-- 0x%08x\n",
                        REG_VO_I80_PIXEL_RDWRCMD,d.all,d.all);
    #endif
}
U16  GH_VO_I80_get_Pixel_RdWrcmd_pixel_rdcmd(void)
{
    GH_VO_I80_PIXEL_RDWRCMD_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_PIXEL_RDWRCMD);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Pixel_RdWrcmd_pixel_rdcmd] --> 0x%08x\n",
                        REG_VO_I80_PIXEL_RDWRCMD,value);
    #endif
    return tmp_value.bitc.pixel_rdcmd;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Cmd_Format (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_I80_set_Cmd_Format(U32 data)
{
    *(volatile U32 *)REG_VO_I80_CMD_FORMAT = data;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Cmd_Format] <-- 0x%08x\n",
                        REG_VO_I80_CMD_FORMAT,data,data);
    #endif
}
U32  GH_VO_I80_get_Cmd_Format(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_CMD_FORMAT);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Cmd_Format] --> 0x%08x\n",
                        REG_VO_I80_CMD_FORMAT,value);
    #endif
    return value;
}
void GH_VO_I80_set_Cmd_Format_cmd_width(U8 data)
{
    GH_VO_I80_CMD_FORMAT_S d;
    d.all = *(volatile U32 *)REG_VO_I80_CMD_FORMAT;
    d.bitc.cmd_width = data;
    *(volatile U32 *)REG_VO_I80_CMD_FORMAT = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Cmd_Format_cmd_width] <-- 0x%08x\n",
                        REG_VO_I80_CMD_FORMAT,d.all,d.all);
    #endif
}
U8   GH_VO_I80_get_Cmd_Format_cmd_width(void)
{
    GH_VO_I80_CMD_FORMAT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_CMD_FORMAT);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Cmd_Format_cmd_width] --> 0x%08x\n",
                        REG_VO_I80_CMD_FORMAT,value);
    #endif
    return tmp_value.bitc.cmd_width;
}
void GH_VO_I80_set_Cmd_Format_cmd_transfer_format(U8 data)
{
    GH_VO_I80_CMD_FORMAT_S d;
    d.all = *(volatile U32 *)REG_VO_I80_CMD_FORMAT;
    d.bitc.cmd_transfer_format = data;
    *(volatile U32 *)REG_VO_I80_CMD_FORMAT = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Cmd_Format_cmd_transfer_format] <-- 0x%08x\n",
                        REG_VO_I80_CMD_FORMAT,d.all,d.all);
    #endif
}
U8   GH_VO_I80_get_Cmd_Format_cmd_transfer_format(void)
{
    GH_VO_I80_CMD_FORMAT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_CMD_FORMAT);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Cmd_Format_cmd_transfer_format] --> 0x%08x\n",
                        REG_VO_I80_CMD_FORMAT,value);
    #endif
    return tmp_value.bitc.cmd_transfer_format;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Lcd_Rst_Para1 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_I80_set_Lcd_Rst_Para1(U32 data)
{
    *(volatile U32 *)REG_VO_I80_LCD_RST_PARA1 = data;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Lcd_Rst_Para1] <-- 0x%08x\n",
                        REG_VO_I80_LCD_RST_PARA1,data,data);
    #endif
}
U32  GH_VO_I80_get_Lcd_Rst_Para1(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_RST_PARA1);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_Rst_Para1] --> 0x%08x\n",
                        REG_VO_I80_LCD_RST_PARA1,value);
    #endif
    return value;
}
void GH_VO_I80_set_Lcd_Rst_Para1_lcdrst_first_hlevel(U16 data)
{
    GH_VO_I80_LCD_RST_PARA1_S d;
    d.all = *(volatile U32 *)REG_VO_I80_LCD_RST_PARA1;
    d.bitc.lcdrst_first_hlevel = data;
    *(volatile U32 *)REG_VO_I80_LCD_RST_PARA1 = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Lcd_Rst_Para1_lcdrst_first_hlevel] <-- 0x%08x\n",
                        REG_VO_I80_LCD_RST_PARA1,d.all,d.all);
    #endif
}
U16  GH_VO_I80_get_Lcd_Rst_Para1_lcdrst_first_hlevel(void)
{
    GH_VO_I80_LCD_RST_PARA1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_RST_PARA1);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_Rst_Para1_lcdrst_first_hlevel] --> 0x%08x\n",
                        REG_VO_I80_LCD_RST_PARA1,value);
    #endif
    return tmp_value.bitc.lcdrst_first_hlevel;
}
void GH_VO_I80_set_Lcd_Rst_Para1_lcdrst_en(U8 data)
{
    GH_VO_I80_LCD_RST_PARA1_S d;
    d.all = *(volatile U32 *)REG_VO_I80_LCD_RST_PARA1;
    d.bitc.lcdrst_en = data;
    *(volatile U32 *)REG_VO_I80_LCD_RST_PARA1 = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Lcd_Rst_Para1_lcdrst_en] <-- 0x%08x\n",
                        REG_VO_I80_LCD_RST_PARA1,d.all,d.all);
    #endif
}
U8   GH_VO_I80_get_Lcd_Rst_Para1_lcdrst_en(void)
{
    GH_VO_I80_LCD_RST_PARA1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_RST_PARA1);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_Rst_Para1_lcdrst_en] --> 0x%08x\n",
                        REG_VO_I80_LCD_RST_PARA1,value);
    #endif
    return tmp_value.bitc.lcdrst_en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Lcd_Rst_Para2 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_I80_set_Lcd_Rst_Para2(U32 data)
{
    *(volatile U32 *)REG_VO_I80_LCD_RST_PARA2 = data;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Lcd_Rst_Para2] <-- 0x%08x\n",
                        REG_VO_I80_LCD_RST_PARA2,data,data);
    #endif
}
U32  GH_VO_I80_get_Lcd_Rst_Para2(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_RST_PARA2);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_Rst_Para2] --> 0x%08x\n",
                        REG_VO_I80_LCD_RST_PARA2,value);
    #endif
    return value;
}
void GH_VO_I80_set_Lcd_Rst_Para2_lcdrst_level(U16 data)
{
    GH_VO_I80_LCD_RST_PARA2_S d;
    d.all = *(volatile U32 *)REG_VO_I80_LCD_RST_PARA2;
    d.bitc.lcdrst_level = data;
    *(volatile U32 *)REG_VO_I80_LCD_RST_PARA2 = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Lcd_Rst_Para2_lcdrst_level] <-- 0x%08x\n",
                        REG_VO_I80_LCD_RST_PARA2,d.all,d.all);
    #endif
}
U16  GH_VO_I80_get_Lcd_Rst_Para2_lcdrst_level(void)
{
    GH_VO_I80_LCD_RST_PARA2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_RST_PARA2);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_Rst_Para2_lcdrst_level] --> 0x%08x\n",
                        REG_VO_I80_LCD_RST_PARA2,value);
    #endif
    return tmp_value.bitc.lcdrst_level;
}
void GH_VO_I80_set_Lcd_Rst_Para2_lcdrst_hsetup(U16 data)
{
    GH_VO_I80_LCD_RST_PARA2_S d;
    d.all = *(volatile U32 *)REG_VO_I80_LCD_RST_PARA2;
    d.bitc.lcdrst_hsetup = data;
    *(volatile U32 *)REG_VO_I80_LCD_RST_PARA2 = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Lcd_Rst_Para2_lcdrst_hsetup] <-- 0x%08x\n",
                        REG_VO_I80_LCD_RST_PARA2,d.all,d.all);
    #endif
}
U16  GH_VO_I80_get_Lcd_Rst_Para2_lcdrst_hsetup(void)
{
    GH_VO_I80_LCD_RST_PARA2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_RST_PARA2);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_Rst_Para2_lcdrst_hsetup] --> 0x%08x\n",
                        REG_VO_I80_LCD_RST_PARA2,value);
    #endif
    return tmp_value.bitc.lcdrst_hsetup;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Delay_Para (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_I80_set_Delay_Para(U32 data)
{
    *(volatile U32 *)REG_VO_I80_DELAY_PARA = data;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Delay_Para] <-- 0x%08x\n",
                        REG_VO_I80_DELAY_PARA,data,data);
    #endif
}
U32  GH_VO_I80_get_Delay_Para(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_DELAY_PARA);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Delay_Para] --> 0x%08x\n",
                        REG_VO_I80_DELAY_PARA,value);
    #endif
    return value;
}
void GH_VO_I80_set_Delay_Para_delay_cmd(U16 data)
{
    GH_VO_I80_DELAY_PARA_S d;
    d.all = *(volatile U32 *)REG_VO_I80_DELAY_PARA;
    d.bitc.delay_cmd = data;
    *(volatile U32 *)REG_VO_I80_DELAY_PARA = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Delay_Para_delay_cmd] <-- 0x%08x\n",
                        REG_VO_I80_DELAY_PARA,d.all,d.all);
    #endif
}
U16  GH_VO_I80_get_Delay_Para_delay_cmd(void)
{
    GH_VO_I80_DELAY_PARA_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_DELAY_PARA);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Delay_Para_delay_cmd] --> 0x%08x\n",
                        REG_VO_I80_DELAY_PARA,value);
    #endif
    return tmp_value.bitc.delay_cmd;
}
void GH_VO_I80_set_Delay_Para_delay_time(U16 data)
{
    GH_VO_I80_DELAY_PARA_S d;
    d.all = *(volatile U32 *)REG_VO_I80_DELAY_PARA;
    d.bitc.delay_time = data;
    *(volatile U32 *)REG_VO_I80_DELAY_PARA = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Delay_Para_delay_time] <-- 0x%08x\n",
                        REG_VO_I80_DELAY_PARA,d.all,d.all);
    #endif
}
U16  GH_VO_I80_get_Delay_Para_delay_time(void)
{
    GH_VO_I80_DELAY_PARA_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_DELAY_PARA);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Delay_Para_delay_time] --> 0x%08x\n",
                        REG_VO_I80_DELAY_PARA,value);
    #endif
    return tmp_value.bitc.delay_time;
}
void GH_VO_I80_set_Delay_Para_delay_cmd_en(U8 data)
{
    GH_VO_I80_DELAY_PARA_S d;
    d.all = *(volatile U32 *)REG_VO_I80_DELAY_PARA;
    d.bitc.delay_cmd_en = data;
    *(volatile U32 *)REG_VO_I80_DELAY_PARA = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Delay_Para_delay_cmd_en] <-- 0x%08x\n",
                        REG_VO_I80_DELAY_PARA,d.all,d.all);
    #endif
}
U8   GH_VO_I80_get_Delay_Para_delay_cmd_en(void)
{
    GH_VO_I80_DELAY_PARA_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_DELAY_PARA);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Delay_Para_delay_cmd_en] --> 0x%08x\n",
                        REG_VO_I80_DELAY_PARA,value);
    #endif
    return tmp_value.bitc.delay_cmd_en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Twr_Timing (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_I80_set_Twr_Timing(U32 data)
{
    *(volatile U32 *)REG_VO_I80_TWR_TIMING = data;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Twr_Timing] <-- 0x%08x\n",
                        REG_VO_I80_TWR_TIMING,data,data);
    #endif
}
U32  GH_VO_I80_get_Twr_Timing(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_TWR_TIMING);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Twr_Timing] --> 0x%08x\n",
                        REG_VO_I80_TWR_TIMING,value);
    #endif
    return value;
}
void GH_VO_I80_set_Twr_Timing_twrl(U16 data)
{
    GH_VO_I80_TWR_TIMING_S d;
    d.all = *(volatile U32 *)REG_VO_I80_TWR_TIMING;
    d.bitc.twrl = data;
    *(volatile U32 *)REG_VO_I80_TWR_TIMING = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Twr_Timing_twrl] <-- 0x%08x\n",
                        REG_VO_I80_TWR_TIMING,d.all,d.all);
    #endif
}
U16  GH_VO_I80_get_Twr_Timing_twrl(void)
{
    GH_VO_I80_TWR_TIMING_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_TWR_TIMING);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Twr_Timing_twrl] --> 0x%08x\n",
                        REG_VO_I80_TWR_TIMING,value);
    #endif
    return tmp_value.bitc.twrl;
}
void GH_VO_I80_set_Twr_Timing_twrh(U16 data)
{
    GH_VO_I80_TWR_TIMING_S d;
    d.all = *(volatile U32 *)REG_VO_I80_TWR_TIMING;
    d.bitc.twrh = data;
    *(volatile U32 *)REG_VO_I80_TWR_TIMING = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Twr_Timing_twrh] <-- 0x%08x\n",
                        REG_VO_I80_TWR_TIMING,d.all,d.all);
    #endif
}
U16  GH_VO_I80_get_Twr_Timing_twrh(void)
{
    GH_VO_I80_TWR_TIMING_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_TWR_TIMING);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Twr_Timing_twrh] --> 0x%08x\n",
                        REG_VO_I80_TWR_TIMING,value);
    #endif
    return tmp_value.bitc.twrh;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Trd_Timing (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_I80_set_Trd_Timing(U32 data)
{
    *(volatile U32 *)REG_VO_I80_TRD_TIMING = data;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Trd_Timing] <-- 0x%08x\n",
                        REG_VO_I80_TRD_TIMING,data,data);
    #endif
}
U32  GH_VO_I80_get_Trd_Timing(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_TRD_TIMING);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Trd_Timing] --> 0x%08x\n",
                        REG_VO_I80_TRD_TIMING,value);
    #endif
    return value;
}
void GH_VO_I80_set_Trd_Timing_trdl(U16 data)
{
    GH_VO_I80_TRD_TIMING_S d;
    d.all = *(volatile U32 *)REG_VO_I80_TRD_TIMING;
    d.bitc.trdl = data;
    *(volatile U32 *)REG_VO_I80_TRD_TIMING = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Trd_Timing_trdl] <-- 0x%08x\n",
                        REG_VO_I80_TRD_TIMING,d.all,d.all);
    #endif
}
U16  GH_VO_I80_get_Trd_Timing_trdl(void)
{
    GH_VO_I80_TRD_TIMING_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_TRD_TIMING);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Trd_Timing_trdl] --> 0x%08x\n",
                        REG_VO_I80_TRD_TIMING,value);
    #endif
    return tmp_value.bitc.trdl;
}
void GH_VO_I80_set_Trd_Timing_trdh(U16 data)
{
    GH_VO_I80_TRD_TIMING_S d;
    d.all = *(volatile U32 *)REG_VO_I80_TRD_TIMING;
    d.bitc.trdh = data;
    *(volatile U32 *)REG_VO_I80_TRD_TIMING = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Trd_Timing_trdh] <-- 0x%08x\n",
                        REG_VO_I80_TRD_TIMING,d.all,d.all);
    #endif
}
U16  GH_VO_I80_get_Trd_Timing_trdh(void)
{
    GH_VO_I80_TRD_TIMING_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_TRD_TIMING);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Trd_Timing_trdh] --> 0x%08x\n",
                        REG_VO_I80_TRD_TIMING,value);
    #endif
    return tmp_value.bitc.trdh;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Tcs_Timing (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_I80_set_Tcs_Timing(U32 data)
{
    *(volatile U32 *)REG_VO_I80_TCS_TIMING = data;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Tcs_Timing] <-- 0x%08x\n",
                        REG_VO_I80_TCS_TIMING,data,data);
    #endif
}
U32  GH_VO_I80_get_Tcs_Timing(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_TCS_TIMING);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Tcs_Timing] --> 0x%08x\n",
                        REG_VO_I80_TCS_TIMING,value);
    #endif
    return value;
}
void GH_VO_I80_set_Tcs_Timing_tas(U8 data)
{
    GH_VO_I80_TCS_TIMING_S d;
    d.all = *(volatile U32 *)REG_VO_I80_TCS_TIMING;
    d.bitc.tas = data;
    *(volatile U32 *)REG_VO_I80_TCS_TIMING = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Tcs_Timing_tas] <-- 0x%08x\n",
                        REG_VO_I80_TCS_TIMING,d.all,d.all);
    #endif
}
U8   GH_VO_I80_get_Tcs_Timing_tas(void)
{
    GH_VO_I80_TCS_TIMING_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_TCS_TIMING);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Tcs_Timing_tas] --> 0x%08x\n",
                        REG_VO_I80_TCS_TIMING,value);
    #endif
    return tmp_value.bitc.tas;
}
void GH_VO_I80_set_Tcs_Timing_cs_ref(U8 data)
{
    GH_VO_I80_TCS_TIMING_S d;
    d.all = *(volatile U32 *)REG_VO_I80_TCS_TIMING;
    d.bitc.cs_ref = data;
    *(volatile U32 *)REG_VO_I80_TCS_TIMING = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Tcs_Timing_cs_ref] <-- 0x%08x\n",
                        REG_VO_I80_TCS_TIMING,d.all,d.all);
    #endif
}
U8   GH_VO_I80_get_Tcs_Timing_cs_ref(void)
{
    GH_VO_I80_TCS_TIMING_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_TCS_TIMING);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Tcs_Timing_cs_ref] --> 0x%08x\n",
                        REG_VO_I80_TCS_TIMING,value);
    #endif
    return tmp_value.bitc.cs_ref;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Polar_Ctrl (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_I80_set_Polar_Ctrl(U32 data)
{
    *(volatile U32 *)REG_VO_I80_POLAR_CTRL = data;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Polar_Ctrl] <-- 0x%08x\n",
                        REG_VO_I80_POLAR_CTRL,data,data);
    #endif
}
U32  GH_VO_I80_get_Polar_Ctrl(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_POLAR_CTRL);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Polar_Ctrl] --> 0x%08x\n",
                        REG_VO_I80_POLAR_CTRL,value);
    #endif
    return value;
}
void GH_VO_I80_set_Polar_Ctrl_wr_polar(U8 data)
{
    GH_VO_I80_POLAR_CTRL_S d;
    d.all = *(volatile U32 *)REG_VO_I80_POLAR_CTRL;
    d.bitc.wr_polar = data;
    *(volatile U32 *)REG_VO_I80_POLAR_CTRL = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Polar_Ctrl_wr_polar] <-- 0x%08x\n",
                        REG_VO_I80_POLAR_CTRL,d.all,d.all);
    #endif
}
U8   GH_VO_I80_get_Polar_Ctrl_wr_polar(void)
{
    GH_VO_I80_POLAR_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_POLAR_CTRL);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Polar_Ctrl_wr_polar] --> 0x%08x\n",
                        REG_VO_I80_POLAR_CTRL,value);
    #endif
    return tmp_value.bitc.wr_polar;
}
void GH_VO_I80_set_Polar_Ctrl_rd_polar(U8 data)
{
    GH_VO_I80_POLAR_CTRL_S d;
    d.all = *(volatile U32 *)REG_VO_I80_POLAR_CTRL;
    d.bitc.rd_polar = data;
    *(volatile U32 *)REG_VO_I80_POLAR_CTRL = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Polar_Ctrl_rd_polar] <-- 0x%08x\n",
                        REG_VO_I80_POLAR_CTRL,d.all,d.all);
    #endif
}
U8   GH_VO_I80_get_Polar_Ctrl_rd_polar(void)
{
    GH_VO_I80_POLAR_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_POLAR_CTRL);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Polar_Ctrl_rd_polar] --> 0x%08x\n",
                        REG_VO_I80_POLAR_CTRL,value);
    #endif
    return tmp_value.bitc.rd_polar;
}
void GH_VO_I80_set_Polar_Ctrl_lcdrst_polar(U8 data)
{
    GH_VO_I80_POLAR_CTRL_S d;
    d.all = *(volatile U32 *)REG_VO_I80_POLAR_CTRL;
    d.bitc.lcdrst_polar = data;
    *(volatile U32 *)REG_VO_I80_POLAR_CTRL = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Polar_Ctrl_lcdrst_polar] <-- 0x%08x\n",
                        REG_VO_I80_POLAR_CTRL,d.all,d.all);
    #endif
}
U8   GH_VO_I80_get_Polar_Ctrl_lcdrst_polar(void)
{
    GH_VO_I80_POLAR_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_POLAR_CTRL);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Polar_Ctrl_lcdrst_polar] --> 0x%08x\n",
                        REG_VO_I80_POLAR_CTRL,value);
    #endif
    return tmp_value.bitc.lcdrst_polar;
}
void GH_VO_I80_set_Polar_Ctrl_vsync_polar(U8 data)
{
    GH_VO_I80_POLAR_CTRL_S d;
    d.all = *(volatile U32 *)REG_VO_I80_POLAR_CTRL;
    d.bitc.vsync_polar = data;
    *(volatile U32 *)REG_VO_I80_POLAR_CTRL = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Polar_Ctrl_vsync_polar] <-- 0x%08x\n",
                        REG_VO_I80_POLAR_CTRL,d.all,d.all);
    #endif
}
U8   GH_VO_I80_get_Polar_Ctrl_vsync_polar(void)
{
    GH_VO_I80_POLAR_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_POLAR_CTRL);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Polar_Ctrl_vsync_polar] --> 0x%08x\n",
                        REG_VO_I80_POLAR_CTRL,value);
    #endif
    return tmp_value.bitc.vsync_polar;
}
void GH_VO_I80_set_Polar_Ctrl_cs_polar(U8 data)
{
    GH_VO_I80_POLAR_CTRL_S d;
    d.all = *(volatile U32 *)REG_VO_I80_POLAR_CTRL;
    d.bitc.cs_polar = data;
    *(volatile U32 *)REG_VO_I80_POLAR_CTRL = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Polar_Ctrl_cs_polar] <-- 0x%08x\n",
                        REG_VO_I80_POLAR_CTRL,d.all,d.all);
    #endif
}
U8   GH_VO_I80_get_Polar_Ctrl_cs_polar(void)
{
    GH_VO_I80_POLAR_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_POLAR_CTRL);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Polar_Ctrl_cs_polar] --> 0x%08x\n",
                        REG_VO_I80_POLAR_CTRL,value);
    #endif
    return tmp_value.bitc.cs_polar;
}
void GH_VO_I80_set_Polar_Ctrl_dc_polar(U8 data)
{
    GH_VO_I80_POLAR_CTRL_S d;
    d.all = *(volatile U32 *)REG_VO_I80_POLAR_CTRL;
    d.bitc.dc_polar = data;
    *(volatile U32 *)REG_VO_I80_POLAR_CTRL = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Polar_Ctrl_dc_polar] <-- 0x%08x\n",
                        REG_VO_I80_POLAR_CTRL,d.all,d.all);
    #endif
}
U8   GH_VO_I80_get_Polar_Ctrl_dc_polar(void)
{
    GH_VO_I80_POLAR_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_POLAR_CTRL);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Polar_Ctrl_dc_polar] --> 0x%08x\n",
                        REG_VO_I80_POLAR_CTRL,value);
    #endif
    return tmp_value.bitc.dc_polar;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Ctrl (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_I80_set_Ctrl(U32 data)
{
    *(volatile U32 *)REG_VO_I80_CTRL = data;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Ctrl] <-- 0x%08x\n",
                        REG_VO_I80_CTRL,data,data);
    #endif
}
U32  GH_VO_I80_get_Ctrl(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_CTRL);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Ctrl] --> 0x%08x\n",
                        REG_VO_I80_CTRL,value);
    #endif
    return value;
}
void GH_VO_I80_set_Ctrl_cfg_end(U8 data)
{
    GH_VO_I80_CTRL_S d;
    d.all = *(volatile U32 *)REG_VO_I80_CTRL;
    d.bitc.cfg_end = data;
    *(volatile U32 *)REG_VO_I80_CTRL = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Ctrl_cfg_end] <-- 0x%08x\n",
                        REG_VO_I80_CTRL,d.all,d.all);
    #endif
}
U8   GH_VO_I80_get_Ctrl_cfg_end(void)
{
    GH_VO_I80_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_CTRL);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Ctrl_cfg_end] --> 0x%08x\n",
                        REG_VO_I80_CTRL,value);
    #endif
    return tmp_value.bitc.cfg_end;
}
void GH_VO_I80_set_Ctrl_module_en(U8 data)
{
    GH_VO_I80_CTRL_S d;
    d.all = *(volatile U32 *)REG_VO_I80_CTRL;
    d.bitc.module_en = data;
    *(volatile U32 *)REG_VO_I80_CTRL = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Ctrl_module_en] <-- 0x%08x\n",
                        REG_VO_I80_CTRL,d.all,d.all);
    #endif
}
U8   GH_VO_I80_get_Ctrl_module_en(void)
{
    GH_VO_I80_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_CTRL);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Ctrl_module_en] --> 0x%08x\n",
                        REG_VO_I80_CTRL,value);
    #endif
    return tmp_value.bitc.module_en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Frame_Counter (read)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_VO_I80_get_Frame_Counter(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_FRAME_COUNTER);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Frame_Counter] --> 0x%08x\n",
                        REG_VO_I80_FRAME_COUNTER,value);
    #endif
    return value;
}
U16  GH_VO_I80_get_Frame_Counter_frame_cnt_out(void)
{
    GH_VO_I80_FRAME_COUNTER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_FRAME_COUNTER);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Frame_Counter_frame_cnt_out] --> 0x%08x\n",
                        REG_VO_I80_FRAME_COUNTER,value);
    #endif
    return tmp_value.bitc.frame_cnt_out;
}
U16  GH_VO_I80_get_Frame_Counter_frame_cnt_in(void)
{
    GH_VO_I80_FRAME_COUNTER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_FRAME_COUNTER);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Frame_Counter_frame_cnt_in] --> 0x%08x\n",
                        REG_VO_I80_FRAME_COUNTER,value);
    #endif
    return tmp_value.bitc.frame_cnt_in;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_I80_State (read)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_VO_I80_get_I80_State(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_I80_STATE);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_I80_State] --> 0x%08x\n",
                        REG_VO_I80_I80_STATE,value);
    #endif
    return value;
}
U8   GH_VO_I80_get_I80_State_cmd_err(void)
{
    GH_VO_I80_I80_STATE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_I80_STATE);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_I80_State_cmd_err] --> 0x%08x\n",
                        REG_VO_I80_I80_STATE,value);
    #endif
    return tmp_value.bitc.cmd_err;
}
U8   GH_VO_I80_get_I80_State_sram_overflow(void)
{
    GH_VO_I80_I80_STATE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_I80_STATE);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_I80_State_sram_overflow] --> 0x%08x\n",
                        REG_VO_I80_I80_STATE,value);
    #endif
    return tmp_value.bitc.sram_overflow;
}
U8   GH_VO_I80_get_I80_State_frame_head_err(void)
{
    GH_VO_I80_I80_STATE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_I80_STATE);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_I80_State_frame_head_err] --> 0x%08x\n",
                        REG_VO_I80_I80_STATE,value);
    #endif
    return tmp_value.bitc.frame_head_err;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Cmd_Sram_State (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_I80_set_Cmd_Sram_State(U32 data)
{
    *(volatile U32 *)REG_VO_I80_CMD_SRAM_STATE = data;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Cmd_Sram_State] <-- 0x%08x\n",
                        REG_VO_I80_CMD_SRAM_STATE,data,data);
    #endif
}
U32  GH_VO_I80_get_Cmd_Sram_State(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_CMD_SRAM_STATE);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Cmd_Sram_State] --> 0x%08x\n",
                        REG_VO_I80_CMD_SRAM_STATE,value);
    #endif
    return value;
}
void GH_VO_I80_set_Cmd_Sram_State_sram_state(U8 data)
{
    GH_VO_I80_CMD_SRAM_STATE_S d;
    d.all = *(volatile U32 *)REG_VO_I80_CMD_SRAM_STATE;
    d.bitc.sram_state = data;
    *(volatile U32 *)REG_VO_I80_CMD_SRAM_STATE = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Cmd_Sram_State_sram_state] <-- 0x%08x\n",
                        REG_VO_I80_CMD_SRAM_STATE,d.all,d.all);
    #endif
}
U8   GH_VO_I80_get_Cmd_Sram_State_sram_state(void)
{
    GH_VO_I80_CMD_SRAM_STATE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_CMD_SRAM_STATE);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Cmd_Sram_State_sram_state] --> 0x%08x\n",
                        REG_VO_I80_CMD_SRAM_STATE,value);
    #endif
    return tmp_value.bitc.sram_state;
}
void GH_VO_I80_set_Cmd_Sram_State_rd_para_num(U8 data)
{
    GH_VO_I80_CMD_SRAM_STATE_S d;
    d.all = *(volatile U32 *)REG_VO_I80_CMD_SRAM_STATE;
    d.bitc.rd_para_num = data;
    *(volatile U32 *)REG_VO_I80_CMD_SRAM_STATE = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Cmd_Sram_State_rd_para_num] <-- 0x%08x\n",
                        REG_VO_I80_CMD_SRAM_STATE,d.all,d.all);
    #endif
}
U8   GH_VO_I80_get_Cmd_Sram_State_rd_para_num(void)
{
    GH_VO_I80_CMD_SRAM_STATE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_CMD_SRAM_STATE);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Cmd_Sram_State_rd_para_num] --> 0x%08x\n",
                        REG_VO_I80_CMD_SRAM_STATE,value);
    #endif
    return tmp_value.bitc.rd_para_num;
}
void GH_VO_I80_set_Cmd_Sram_State_cmd_para_num(U8 data)
{
    GH_VO_I80_CMD_SRAM_STATE_S d;
    d.all = *(volatile U32 *)REG_VO_I80_CMD_SRAM_STATE;
    d.bitc.cmd_para_num = data;
    *(volatile U32 *)REG_VO_I80_CMD_SRAM_STATE = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Cmd_Sram_State_cmd_para_num] <-- 0x%08x\n",
                        REG_VO_I80_CMD_SRAM_STATE,d.all,d.all);
    #endif
}
U8   GH_VO_I80_get_Cmd_Sram_State_cmd_para_num(void)
{
    GH_VO_I80_CMD_SRAM_STATE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_CMD_SRAM_STATE);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Cmd_Sram_State_cmd_para_num] --> 0x%08x\n",
                        REG_VO_I80_CMD_SRAM_STATE,value);
    #endif
    return tmp_value.bitc.cmd_para_num;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Tcsref_Wt_Timing (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_I80_set_Tcsref_Wt_Timing(U32 data)
{
    *(volatile U32 *)REG_VO_I80_TCSREF_WT_TIMING = data;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Tcsref_Wt_Timing] <-- 0x%08x\n",
                        REG_VO_I80_TCSREF_WT_TIMING,data,data);
    #endif
}
U32  GH_VO_I80_get_Tcsref_Wt_Timing(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_TCSREF_WT_TIMING);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Tcsref_Wt_Timing] --> 0x%08x\n",
                        REG_VO_I80_TCSREF_WT_TIMING,value);
    #endif
    return value;
}
void GH_VO_I80_set_Tcsref_Wt_Timing_pwcsh_wt(U16 data)
{
    GH_VO_I80_TCSREF_WT_TIMING_S d;
    d.all = *(volatile U32 *)REG_VO_I80_TCSREF_WT_TIMING;
    d.bitc.pwcsh_wt = data;
    *(volatile U32 *)REG_VO_I80_TCSREF_WT_TIMING = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Tcsref_Wt_Timing_pwcsh_wt] <-- 0x%08x\n",
                        REG_VO_I80_TCSREF_WT_TIMING,d.all,d.all);
    #endif
}
U16  GH_VO_I80_get_Tcsref_Wt_Timing_pwcsh_wt(void)
{
    GH_VO_I80_TCSREF_WT_TIMING_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_TCSREF_WT_TIMING);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Tcsref_Wt_Timing_pwcsh_wt] --> 0x%08x\n",
                        REG_VO_I80_TCSREF_WT_TIMING,value);
    #endif
    return tmp_value.bitc.pwcsh_wt;
}
void GH_VO_I80_set_Tcsref_Wt_Timing_pwcsl_wt(U16 data)
{
    GH_VO_I80_TCSREF_WT_TIMING_S d;
    d.all = *(volatile U32 *)REG_VO_I80_TCSREF_WT_TIMING;
    d.bitc.pwcsl_wt = data;
    *(volatile U32 *)REG_VO_I80_TCSREF_WT_TIMING = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Tcsref_Wt_Timing_pwcsl_wt] <-- 0x%08x\n",
                        REG_VO_I80_TCSREF_WT_TIMING,d.all,d.all);
    #endif
}
U16  GH_VO_I80_get_Tcsref_Wt_Timing_pwcsl_wt(void)
{
    GH_VO_I80_TCSREF_WT_TIMING_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_TCSREF_WT_TIMING);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Tcsref_Wt_Timing_pwcsl_wt] --> 0x%08x\n",
                        REG_VO_I80_TCSREF_WT_TIMING,value);
    #endif
    return tmp_value.bitc.pwcsl_wt;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Tcsref_Rd_Timing (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_I80_set_Tcsref_Rd_Timing(U32 data)
{
    *(volatile U32 *)REG_VO_I80_TCSREF_RD_TIMING = data;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Tcsref_Rd_Timing] <-- 0x%08x\n",
                        REG_VO_I80_TCSREF_RD_TIMING,data,data);
    #endif
}
U32  GH_VO_I80_get_Tcsref_Rd_Timing(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_TCSREF_RD_TIMING);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Tcsref_Rd_Timing] --> 0x%08x\n",
                        REG_VO_I80_TCSREF_RD_TIMING,value);
    #endif
    return value;
}
void GH_VO_I80_set_Tcsref_Rd_Timing_pwcsh_rd(U16 data)
{
    GH_VO_I80_TCSREF_RD_TIMING_S d;
    d.all = *(volatile U32 *)REG_VO_I80_TCSREF_RD_TIMING;
    d.bitc.pwcsh_rd = data;
    *(volatile U32 *)REG_VO_I80_TCSREF_RD_TIMING = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Tcsref_Rd_Timing_pwcsh_rd] <-- 0x%08x\n",
                        REG_VO_I80_TCSREF_RD_TIMING,d.all,d.all);
    #endif
}
U16  GH_VO_I80_get_Tcsref_Rd_Timing_pwcsh_rd(void)
{
    GH_VO_I80_TCSREF_RD_TIMING_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_TCSREF_RD_TIMING);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Tcsref_Rd_Timing_pwcsh_rd] --> 0x%08x\n",
                        REG_VO_I80_TCSREF_RD_TIMING,value);
    #endif
    return tmp_value.bitc.pwcsh_rd;
}
void GH_VO_I80_set_Tcsref_Rd_Timing_pwcsl_rd(U16 data)
{
    GH_VO_I80_TCSREF_RD_TIMING_S d;
    d.all = *(volatile U32 *)REG_VO_I80_TCSREF_RD_TIMING;
    d.bitc.pwcsl_rd = data;
    *(volatile U32 *)REG_VO_I80_TCSREF_RD_TIMING = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Tcsref_Rd_Timing_pwcsl_rd] <-- 0x%08x\n",
                        REG_VO_I80_TCSREF_RD_TIMING,d.all,d.all);
    #endif
}
U16  GH_VO_I80_get_Tcsref_Rd_Timing_pwcsl_rd(void)
{
    GH_VO_I80_TCSREF_RD_TIMING_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_TCSREF_RD_TIMING);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Tcsref_Rd_Timing_pwcsl_rd] --> 0x%08x\n",
                        REG_VO_I80_TCSREF_RD_TIMING,value);
    #endif
    return tmp_value.bitc.pwcsl_rd;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Todh_Timing (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_I80_set_Todh_Timing(U32 data)
{
    *(volatile U32 *)REG_VO_I80_TODH_TIMING = data;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Todh_Timing] <-- 0x%08x\n",
                        REG_VO_I80_TODH_TIMING,data,data);
    #endif
}
U32  GH_VO_I80_get_Todh_Timing(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_TODH_TIMING);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Todh_Timing] --> 0x%08x\n",
                        REG_VO_I80_TODH_TIMING,value);
    #endif
    return value;
}
void GH_VO_I80_set_Todh_Timing_todh(U16 data)
{
    GH_VO_I80_TODH_TIMING_S d;
    d.all = *(volatile U32 *)REG_VO_I80_TODH_TIMING;
    d.bitc.todh = data;
    *(volatile U32 *)REG_VO_I80_TODH_TIMING = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Todh_Timing_todh] <-- 0x%08x\n",
                        REG_VO_I80_TODH_TIMING,d.all,d.all);
    #endif
}
U16  GH_VO_I80_get_Todh_Timing_todh(void)
{
    GH_VO_I80_TODH_TIMING_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_TODH_TIMING);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Todh_Timing_todh] --> 0x%08x\n",
                        REG_VO_I80_TODH_TIMING,value);
    #endif
    return tmp_value.bitc.todh;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Lcd_State (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_I80_set_Lcd_State(U32 data)
{
    *(volatile U32 *)REG_VO_I80_LCD_STATE = data;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Lcd_State] <-- 0x%08x\n",
                        REG_VO_I80_LCD_STATE,data,data);
    #endif
}
U32  GH_VO_I80_get_Lcd_State(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_STATE);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_State] --> 0x%08x\n",
                        REG_VO_I80_LCD_STATE,value);
    #endif
    return value;
}
void GH_VO_I80_set_Lcd_State_rdcmd_para_en(U8 data)
{
    GH_VO_I80_LCD_STATE_S d;
    d.all = *(volatile U32 *)REG_VO_I80_LCD_STATE;
    d.bitc.rdcmd_para_en = data;
    *(volatile U32 *)REG_VO_I80_LCD_STATE = d.all;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Lcd_State_rdcmd_para_en] <-- 0x%08x\n",
                        REG_VO_I80_LCD_STATE,d.all,d.all);
    #endif
}
U8   GH_VO_I80_get_Lcd_State_rdcmd_para_en(void)
{
    GH_VO_I80_LCD_STATE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_STATE);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_State_rdcmd_para_en] --> 0x%08x\n",
                        REG_VO_I80_LCD_STATE,value);
    #endif
    return tmp_value.bitc.rdcmd_para_en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Lcd_State0 (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_VO_I80_get_Lcd_State0(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_STATE0);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_State0] --> 0x%08x\n",
                        REG_VO_I80_LCD_STATE0,value);
    #endif
    return value;
}
U16  GH_VO_I80_get_Lcd_State0_lcd_para1(void)
{
    GH_VO_I80_LCD_STATE0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_STATE0);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_State0_lcd_para1] --> 0x%08x\n",
                        REG_VO_I80_LCD_STATE0,value);
    #endif
    return tmp_value.bitc.lcd_para1;
}
U16  GH_VO_I80_get_Lcd_State0_lcd_para0(void)
{
    GH_VO_I80_LCD_STATE0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_STATE0);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_State0_lcd_para0] --> 0x%08x\n",
                        REG_VO_I80_LCD_STATE0,value);
    #endif
    return tmp_value.bitc.lcd_para0;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Lcd_State1 (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_VO_I80_get_Lcd_State1(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_STATE1);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_State1] --> 0x%08x\n",
                        REG_VO_I80_LCD_STATE1,value);
    #endif
    return value;
}
U16  GH_VO_I80_get_Lcd_State1_lcd_para3(void)
{
    GH_VO_I80_LCD_STATE1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_STATE1);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_State1_lcd_para3] --> 0x%08x\n",
                        REG_VO_I80_LCD_STATE1,value);
    #endif
    return tmp_value.bitc.lcd_para3;
}
U16  GH_VO_I80_get_Lcd_State1_lcd_para2(void)
{
    GH_VO_I80_LCD_STATE1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_STATE1);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_State1_lcd_para2] --> 0x%08x\n",
                        REG_VO_I80_LCD_STATE1,value);
    #endif
    return tmp_value.bitc.lcd_para2;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Lcd_State2 (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_VO_I80_get_Lcd_State2(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_STATE2);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_State2] --> 0x%08x\n",
                        REG_VO_I80_LCD_STATE2,value);
    #endif
    return value;
}
U16  GH_VO_I80_get_Lcd_State2_lcd_para5(void)
{
    GH_VO_I80_LCD_STATE2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_STATE2);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_State2_lcd_para5] --> 0x%08x\n",
                        REG_VO_I80_LCD_STATE2,value);
    #endif
    return tmp_value.bitc.lcd_para5;
}
U16  GH_VO_I80_get_Lcd_State2_lcd_para4(void)
{
    GH_VO_I80_LCD_STATE2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_STATE2);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_State2_lcd_para4] --> 0x%08x\n",
                        REG_VO_I80_LCD_STATE2,value);
    #endif
    return tmp_value.bitc.lcd_para4;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Lcd_State3 (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_VO_I80_get_Lcd_State3(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_STATE3);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_State3] --> 0x%08x\n",
                        REG_VO_I80_LCD_STATE3,value);
    #endif
    return value;
}
U16  GH_VO_I80_get_Lcd_State3_lcd_para7(void)
{
    GH_VO_I80_LCD_STATE3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_STATE3);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_State3_lcd_para7] --> 0x%08x\n",
                        REG_VO_I80_LCD_STATE3,value);
    #endif
    return tmp_value.bitc.lcd_para7;
}
U16  GH_VO_I80_get_Lcd_State3_lcd_para6(void)
{
    GH_VO_I80_LCD_STATE3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_STATE3);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_State3_lcd_para6] --> 0x%08x\n",
                        REG_VO_I80_LCD_STATE3,value);
    #endif
    return tmp_value.bitc.lcd_para6;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Lcd_State4 (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_VO_I80_get_Lcd_State4(void)
{
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_STATE4);

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_State4] --> 0x%08x\n",
                        REG_VO_I80_LCD_STATE4,value);
    #endif
    return value;
}
U16  GH_VO_I80_get_Lcd_State4_lcd_para9(void)
{
    GH_VO_I80_LCD_STATE4_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_STATE4);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_State4_lcd_para9] --> 0x%08x\n",
                        REG_VO_I80_LCD_STATE4,value);
    #endif
    return tmp_value.bitc.lcd_para9;
}
U16  GH_VO_I80_get_Lcd_State4_lcd_para8(void)
{
    GH_VO_I80_LCD_STATE4_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_I80_LCD_STATE4);

    tmp_value.all = value;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Lcd_State4_lcd_para8] --> 0x%08x\n",
                        REG_VO_I80_LCD_STATE4,value);
    #endif
    return tmp_value.bitc.lcd_para8;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_I80_Sram_Cmdpara (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_I80_set_Sram_Cmdpara(U8 index, U32 data)
{
    *(volatile U32 *)(REG_VO_I80_SRAM_CMDPARA + index * FIO_MOFFSET(VO_I80,0x00000004)) = data;
    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_I80_set_Sram_Cmdpara] <-- 0x%08x\n",
                        (REG_VO_I80_SRAM_CMDPARA + index * FIO_MOFFSET(VO_I80,0x00000004)),data,data);
    #endif
}
U32  GH_VO_I80_get_Sram_Cmdpara(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VO_I80_SRAM_CMDPARA + index * FIO_MOFFSET(VO_I80,0x00000004)));

    #if GH_VO_I80_ENABLE_DEBUG_PRINT
    GH_VO_I80_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_I80_get_Sram_Cmdpara] --> 0x%08x\n",
                        (REG_VO_I80_SRAM_CMDPARA + index * FIO_MOFFSET(VO_I80,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_VO_I80_init(void)
{
    int i;

    GH_VO_I80_set_Data_Format((U32)0x00000000);
    GH_VO_I80_set_Pic_Resolution((U32)0x00f00140);
    GH_VO_I80_set_Pixel_RdWrcmd((U32)0x002e002c);
    GH_VO_I80_set_Cmd_Format((U32)0x00000000);
    GH_VO_I80_set_Lcd_Rst_Para1((U32)0x00000000);
    GH_VO_I80_set_Lcd_Rst_Para2((U32)0x04b003e8);
    GH_VO_I80_set_Delay_Para((U32)0x0000ffff);
    GH_VO_I80_set_Twr_Timing((U32)0x00030003);
    GH_VO_I80_set_Trd_Timing((U32)0x0014000a);
    GH_VO_I80_set_Tcs_Timing((U32)0x00000001);
    GH_VO_I80_set_Polar_Ctrl((U32)0x00000008);
    GH_VO_I80_set_Ctrl((U32)0x00000000);
    GH_VO_I80_set_Cmd_Sram_State((U32)0x00000000);
    GH_VO_I80_set_Tcsref_Wt_Timing((U32)0x00030003);
    GH_VO_I80_set_Tcsref_Rd_Timing((U32)0x000a0014);
    GH_VO_I80_set_Todh_Timing((U32)0x00000000);
    GH_VO_I80_set_Lcd_State((U32)0x00000000);
    GH_VO_I80_set_Sram_Cmdpara(0, (U32)0x00000000);
    for (i=1; i<128; i++)
    {
        GH_VO_I80_set_Sram_Cmdpara(i, (U32)0x00000000);
    }
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

