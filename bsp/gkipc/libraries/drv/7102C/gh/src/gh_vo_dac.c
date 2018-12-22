/******************************************************************************
**
** \file      gh_vo_dac.c
**
** \brief     VDAC Registers.
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
#include "gh_vo_dac.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register VO_DAC_EN_IDAC_X (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DAC_set_EN_IDAC_X(U8 data)
{
    *(volatile U8 *)REG_VO_DAC_EN_IDAC_X = data;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_EN_IDAC_X] <-- 0x%08x\n",
                        REG_VO_DAC_EN_IDAC_X,data,data);
    #endif
}
U8   GH_VO_DAC_get_EN_IDAC_X(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DAC_EN_IDAC_X);

    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_EN_IDAC_X] --> 0x%08x\n",
                        REG_VO_DAC_EN_IDAC_X,value);
    #endif
    return value;
}
void GH_VO_DAC_set_EN_IDAC_X_enable(U8 data)
{
    GH_VO_DAC_EN_IDAC_X_S d;
    d.all = *(volatile U8 *)REG_VO_DAC_EN_IDAC_X;
    d.bitc.enable = data;
    *(volatile U8 *)REG_VO_DAC_EN_IDAC_X = d.all;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_EN_IDAC_X_enable] <-- 0x%08x\n",
                        REG_VO_DAC_EN_IDAC_X,d.all,d.all);
    #endif
}
U8   GH_VO_DAC_get_EN_IDAC_X_enable(void)
{
    GH_VO_DAC_EN_IDAC_X_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DAC_EN_IDAC_X);

    tmp_value.all = value;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_EN_IDAC_X_enable] --> 0x%08x\n",
                        REG_VO_DAC_EN_IDAC_X,value);
    #endif
    return tmp_value.bitc.enable;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DAC_MODE_SD (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DAC_set_MODE_SD(U8 data)
{
    *(volatile U8 *)REG_VO_DAC_MODE_SD = data;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_MODE_SD] <-- 0x%08x\n",
                        REG_VO_DAC_MODE_SD,data,data);
    #endif
}
U8   GH_VO_DAC_get_MODE_SD(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DAC_MODE_SD);

    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_MODE_SD] --> 0x%08x\n",
                        REG_VO_DAC_MODE_SD,value);
    #endif
    return value;
}
void GH_VO_DAC_set_MODE_SD_mode(U8 data)
{
    GH_VO_DAC_MODE_SD_S d;
    d.all = *(volatile U8 *)REG_VO_DAC_MODE_SD;
    d.bitc.mode = data;
    *(volatile U8 *)REG_VO_DAC_MODE_SD = d.all;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_MODE_SD_mode] <-- 0x%08x\n",
                        REG_VO_DAC_MODE_SD,d.all,d.all);
    #endif
}
U8   GH_VO_DAC_get_MODE_SD_mode(void)
{
    GH_VO_DAC_MODE_SD_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DAC_MODE_SD);

    tmp_value.all = value;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_MODE_SD_mode] --> 0x%08x\n",
                        REG_VO_DAC_MODE_SD,value);
    #endif
    return tmp_value.bitc.mode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DAC_IDAC_IHALF_SD (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DAC_set_IDAC_IHALF_SD(U8 data)
{
    *(volatile U8 *)REG_VO_DAC_IDAC_IHALF_SD = data;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_IDAC_IHALF_SD] <-- 0x%08x\n",
                        REG_VO_DAC_IDAC_IHALF_SD,data,data);
    #endif
}
U8   GH_VO_DAC_get_IDAC_IHALF_SD(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DAC_IDAC_IHALF_SD);

    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_IDAC_IHALF_SD] --> 0x%08x\n",
                        REG_VO_DAC_IDAC_IHALF_SD,value);
    #endif
    return value;
}
void GH_VO_DAC_set_IDAC_IHALF_SD_half(U8 data)
{
    GH_VO_DAC_IDAC_IHALF_SD_S d;
    d.all = *(volatile U8 *)REG_VO_DAC_IDAC_IHALF_SD;
    d.bitc.half = data;
    *(volatile U8 *)REG_VO_DAC_IDAC_IHALF_SD = d.all;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_IDAC_IHALF_SD_half] <-- 0x%08x\n",
                        REG_VO_DAC_IDAC_IHALF_SD,d.all,d.all);
    #endif
}
U8   GH_VO_DAC_get_IDAC_IHALF_SD_half(void)
{
    GH_VO_DAC_IDAC_IHALF_SD_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DAC_IDAC_IHALF_SD);

    tmp_value.all = value;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_IDAC_IHALF_SD_half] --> 0x%08x\n",
                        REG_VO_DAC_IDAC_IHALF_SD,value);
    #endif
    return tmp_value.bitc.half;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DAC_GCR_LEVEL (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DAC_set_GCR_LEVEL(U8 data)
{
    *(volatile U8 *)REG_VO_DAC_GCR_LEVEL = data;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_GCR_LEVEL] <-- 0x%08x\n",
                        REG_VO_DAC_GCR_LEVEL,data,data);
    #endif
}
U8   GH_VO_DAC_get_GCR_LEVEL(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DAC_GCR_LEVEL);

    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_GCR_LEVEL] --> 0x%08x\n",
                        REG_VO_DAC_GCR_LEVEL,value);
    #endif
    return value;
}
void GH_VO_DAC_set_GCR_LEVEL_level(U8 data)
{
    GH_VO_DAC_GCR_LEVEL_S d;
    d.all = *(volatile U8 *)REG_VO_DAC_GCR_LEVEL;
    d.bitc.level = data;
    *(volatile U8 *)REG_VO_DAC_GCR_LEVEL = d.all;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_GCR_LEVEL_level] <-- 0x%08x\n",
                        REG_VO_DAC_GCR_LEVEL,d.all,d.all);
    #endif
}
U8   GH_VO_DAC_get_GCR_LEVEL_level(void)
{
    GH_VO_DAC_GCR_LEVEL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DAC_GCR_LEVEL);

    tmp_value.all = value;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_GCR_LEVEL_level] --> 0x%08x\n",
                        REG_VO_DAC_GCR_LEVEL,value);
    #endif
    return tmp_value.bitc.level;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DAC_IDA_IQUART_SD (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DAC_set_IDA_IQUART_SD(U8 data)
{
    *(volatile U8 *)REG_VO_DAC_IDA_IQUART_SD = data;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_IDA_IQUART_SD] <-- 0x%08x\n",
                        REG_VO_DAC_IDA_IQUART_SD,data,data);
    #endif
}
U8   GH_VO_DAC_get_IDA_IQUART_SD(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DAC_IDA_IQUART_SD);

    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_IDA_IQUART_SD] --> 0x%08x\n",
                        REG_VO_DAC_IDA_IQUART_SD,value);
    #endif
    return value;
}
void GH_VO_DAC_set_IDA_IQUART_SD_quart(U8 data)
{
    GH_VO_DAC_IDA_IQUART_SD_S d;
    d.all = *(volatile U8 *)REG_VO_DAC_IDA_IQUART_SD;
    d.bitc.quart = data;
    *(volatile U8 *)REG_VO_DAC_IDA_IQUART_SD = d.all;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_IDA_IQUART_SD_quart] <-- 0x%08x\n",
                        REG_VO_DAC_IDA_IQUART_SD,d.all,d.all);
    #endif
}
U8   GH_VO_DAC_get_IDA_IQUART_SD_quart(void)
{
    GH_VO_DAC_IDA_IQUART_SD_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DAC_IDA_IQUART_SD);

    tmp_value.all = value;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_IDA_IQUART_SD_quart] --> 0x%08x\n",
                        REG_VO_DAC_IDA_IQUART_SD,value);
    #endif
    return tmp_value.bitc.quart;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DAC_GCR_IDAC_GAINX (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DAC_set_GCR_IDAC_GAINX(U8 data)
{
    *(volatile U8 *)REG_VO_DAC_GCR_IDAC_GAINX = data;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_GCR_IDAC_GAINX] <-- 0x%08x\n",
                        REG_VO_DAC_GCR_IDAC_GAINX,data,data);
    #endif
}
U8   GH_VO_DAC_get_GCR_IDAC_GAINX(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DAC_GCR_IDAC_GAINX);

    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_GCR_IDAC_GAINX] --> 0x%08x\n",
                        REG_VO_DAC_GCR_IDAC_GAINX,value);
    #endif
    return value;
}
void GH_VO_DAC_set_GCR_IDAC_GAINX_gain(U8 data)
{
    GH_VO_DAC_GCR_IDAC_GAINX_S d;
    d.all = *(volatile U8 *)REG_VO_DAC_GCR_IDAC_GAINX;
    d.bitc.gain = data;
    *(volatile U8 *)REG_VO_DAC_GCR_IDAC_GAINX = d.all;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_GCR_IDAC_GAINX_gain] <-- 0x%08x\n",
                        REG_VO_DAC_GCR_IDAC_GAINX,d.all,d.all);
    #endif
}
U8   GH_VO_DAC_get_GCR_IDAC_GAINX_gain(void)
{
    GH_VO_DAC_GCR_IDAC_GAINX_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DAC_GCR_IDAC_GAINX);

    tmp_value.all = value;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_GCR_IDAC_GAINX_gain] --> 0x%08x\n",
                        REG_VO_DAC_GCR_IDAC_GAINX,value);
    #endif
    return tmp_value.bitc.gain;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_VO_DAC_init(void)
{
    GH_VO_DAC_set_EN_IDAC_X((U8)0x00000001);
    GH_VO_DAC_set_MODE_SD((U8)0x00000000);
    GH_VO_DAC_set_IDAC_IHALF_SD((U8)0x00000000);
    GH_VO_DAC_set_GCR_LEVEL((U8)0x00000000);
    GH_VO_DAC_set_IDA_IQUART_SD((U8)0x00000000);
    GH_VO_DAC_set_GCR_IDAC_GAINX((U8)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

