/******************************************************************************
**
** \file      gh_gpio.c
**
** \brief     These GPIO pins can be configured as I/O pins for other hardware modules..
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
#include "gh_gpio.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
U32                                     m_gpio_ic_low;
U32                                     m_gpio_ic_high;
GH_GPIO_INT_EN_S                        m_gpio_int_en;
GH_GPIO_OUTPUT_CFG_S                    m_gpio_output_cfg[64];
GH_GPIO_INPUT_CFG_S                     m_gpio_input_cfg[64];

/*----------------------------------------------------------------------------*/
/* register GPIO_IS_LOW (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_GPIO_set_IS_LOW(U32 data)
{
    *(volatile U32 *)REG_GPIO_IS_LOW = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_IS_LOW] <-- 0x%08x\n",
                        REG_GPIO_IS_LOW,data,data);
    #endif
}
U32  GH_GPIO_get_IS_LOW(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IS_LOW);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_IS_LOW] --> 0x%08x\n",
                        REG_GPIO_IS_LOW,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_IS_HIGH (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_GPIO_set_IS_HIGH(U32 data)
{
    *(volatile U32 *)REG_GPIO_IS_HIGH = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_IS_HIGH] <-- 0x%08x\n",
                        REG_GPIO_IS_HIGH,data,data);
    #endif
}
U32  GH_GPIO_get_IS_HIGH(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IS_HIGH);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_IS_HIGH] --> 0x%08x\n",
                        REG_GPIO_IS_HIGH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_IBE_LOW (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_GPIO_set_IBE_LOW(U32 data)
{
    *(volatile U32 *)REG_GPIO_IBE_LOW = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_IBE_LOW] <-- 0x%08x\n",
                        REG_GPIO_IBE_LOW,data,data);
    #endif
}
U32  GH_GPIO_get_IBE_LOW(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IBE_LOW);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_IBE_LOW] --> 0x%08x\n",
                        REG_GPIO_IBE_LOW,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_IBE_HIGH (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_GPIO_set_IBE_HIGH(U32 data)
{
    *(volatile U32 *)REG_GPIO_IBE_HIGH = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_IBE_HIGH] <-- 0x%08x\n",
                        REG_GPIO_IBE_HIGH,data,data);
    #endif
}
U32  GH_GPIO_get_IBE_HIGH(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IBE_HIGH);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_IBE_HIGH] --> 0x%08x\n",
                        REG_GPIO_IBE_HIGH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_IEV_LOW (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_GPIO_set_IEV_LOW(U32 data)
{
    *(volatile U32 *)REG_GPIO_IEV_LOW = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_IEV_LOW] <-- 0x%08x\n",
                        REG_GPIO_IEV_LOW,data,data);
    #endif
}
U32  GH_GPIO_get_IEV_LOW(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IEV_LOW);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_IEV_LOW] --> 0x%08x\n",
                        REG_GPIO_IEV_LOW,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_IEV_HIGH (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_GPIO_set_IEV_HIGH(U32 data)
{
    *(volatile U32 *)REG_GPIO_IEV_HIGH = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_IEV_HIGH] <-- 0x%08x\n",
                        REG_GPIO_IEV_HIGH,data,data);
    #endif
}
U32  GH_GPIO_get_IEV_HIGH(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IEV_HIGH);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_IEV_HIGH] --> 0x%08x\n",
                        REG_GPIO_IEV_HIGH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_IE_LOW (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_GPIO_set_IE_LOW(U32 data)
{
    *(volatile U32 *)REG_GPIO_IE_LOW = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_IE_LOW] <-- 0x%08x\n",
                        REG_GPIO_IE_LOW,data,data);
    #endif
}
U32  GH_GPIO_get_IE_LOW(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IE_LOW);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_IE_LOW] --> 0x%08x\n",
                        REG_GPIO_IE_LOW,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_IE_HIGH (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_GPIO_set_IE_HIGH(U32 data)
{
    *(volatile U32 *)REG_GPIO_IE_HIGH = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_IE_HIGH] <-- 0x%08x\n",
                        REG_GPIO_IE_HIGH,data,data);
    #endif
}
U32  GH_GPIO_get_IE_HIGH(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IE_HIGH);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_IE_HIGH] --> 0x%08x\n",
                        REG_GPIO_IE_HIGH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_IC_LOW (write)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_GPIO_set_IC_LOW(U32 data)
{
    m_gpio_ic_low = data;
    *(volatile U32 *)REG_GPIO_IC_LOW = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_IC_LOW] <-- 0x%08x\n",
                        REG_GPIO_IC_LOW,data,data);
    #endif
}
U32  GH_GPIO_getm_IC_LOW(void)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_IC_LOW] --> 0x%08x\n",
                        m_gpio_ic_low);
    #endif
    return m_gpio_ic_low;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register GPIO_IC_HIGH (write)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_GPIO_set_IC_HIGH(U32 data)
{
    m_gpio_ic_high = data;
    *(volatile U32 *)REG_GPIO_IC_HIGH = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_IC_HIGH] <-- 0x%08x\n",
                        REG_GPIO_IC_HIGH,data,data);
    #endif
}
U32  GH_GPIO_getm_IC_HIGH(void)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_IC_HIGH] --> 0x%08x\n",
                        m_gpio_ic_high);
    #endif
    return m_gpio_ic_high;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register GPIO_RIS_LOW (read)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_GPIO_get_RIS_LOW(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_RIS_LOW);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_RIS_LOW] --> 0x%08x\n",
                        REG_GPIO_RIS_LOW,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_RIS_HIGH (read)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_GPIO_get_RIS_HIGH(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_RIS_HIGH);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_RIS_HIGH] --> 0x%08x\n",
                        REG_GPIO_RIS_HIGH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_MIS_LOW (read)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_GPIO_get_MIS_LOW(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_MIS_LOW);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_MIS_LOW] --> 0x%08x\n",
                        REG_GPIO_MIS_LOW,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_MIS_HIGH (read)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_GPIO_get_MIS_HIGH(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_MIS_HIGH);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_MIS_HIGH] --> 0x%08x\n",
                        REG_GPIO_MIS_HIGH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_INT_EN (write)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_GPIO_set_INT_EN(U32 data)
{
    m_gpio_int_en.all = data;
    *(volatile U32 *)REG_GPIO_INT_EN = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_INT_EN] <-- 0x%08x\n",
                        REG_GPIO_INT_EN,data,data);
    #endif
}
U32  GH_GPIO_getm_INT_EN(void)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_INT_EN] --> 0x%08x\n",
                        m_gpio_int_en.all);
    #endif
    return m_gpio_int_en.all;
}
void GH_GPIO_set_INT_EN_int_en(U8 data)
{
    m_gpio_int_en.bitc.int_en = data;
    *(volatile U32 *)REG_GPIO_INT_EN = m_gpio_int_en.all;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_INT_EN_int_en] <-- 0x%08x\n",
                        REG_GPIO_INT_EN,m_gpio_int_en.all,m_gpio_int_en.all);
    #endif
}
U8   GH_GPIO_getm_INT_EN_int_en(void)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_INT_EN_int_en] --> 0x%08x\n",
                        m_gpio_int_en.bitc.int_en);
    #endif
    return m_gpio_int_en.bitc.int_en;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register GPIO_PER_SEL (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_GPIO_set_PER_SEL(U32 data)
{
    *(volatile U32 *)REG_GPIO_PER_SEL = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_PER_SEL] <-- 0x%08x\n",
                        REG_GPIO_PER_SEL,data,data);
    #endif
}
U32  GH_GPIO_get_PER_SEL(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_PER_SEL);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_PER_SEL] --> 0x%08x\n",
                        REG_GPIO_PER_SEL,value);
    #endif
    return value;
}
void GH_GPIO_set_PER_SEL_enet_sel(U8 data)
{
    GH_GPIO_PER_SEL_S d;
    d.all = *(volatile U32 *)REG_GPIO_PER_SEL;
    d.bitc.enet_sel = data;
    *(volatile U32 *)REG_GPIO_PER_SEL = d.all;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_PER_SEL_enet_sel] <-- 0x%08x\n",
                        REG_GPIO_PER_SEL,d.all,d.all);
    #endif
}
U8   GH_GPIO_get_PER_SEL_enet_sel(void)
{
    GH_GPIO_PER_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_GPIO_PER_SEL);

    tmp_value.all = value;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_PER_SEL_enet_sel] --> 0x%08x\n",
                        REG_GPIO_PER_SEL,value);
    #endif
    return tmp_value.bitc.enet_sel;
}
void GH_GPIO_set_PER_SEL_i2s_sel(U8 data)
{
    GH_GPIO_PER_SEL_S d;
    d.all = *(volatile U32 *)REG_GPIO_PER_SEL;
    d.bitc.i2s_sel = data;
    *(volatile U32 *)REG_GPIO_PER_SEL = d.all;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_PER_SEL_i2s_sel] <-- 0x%08x\n",
                        REG_GPIO_PER_SEL,d.all,d.all);
    #endif
}
U8   GH_GPIO_get_PER_SEL_i2s_sel(void)
{
    GH_GPIO_PER_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_GPIO_PER_SEL);

    tmp_value.all = value;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_PER_SEL_i2s_sel] --> 0x%08x\n",
                        REG_GPIO_PER_SEL,value);
    #endif
    return tmp_value.bitc.i2s_sel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_DIN_LOW (read)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_GPIO_get_DIN_LOW(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_DIN_LOW);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_DIN_LOW] --> 0x%08x\n",
                        REG_GPIO_DIN_LOW,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_DIN_HIGH (read)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_GPIO_get_DIN_HIGH(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_DIN_HIGH);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_DIN_HIGH] --> 0x%08x\n",
                        REG_GPIO_DIN_HIGH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_OUTPUT_CFG (write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_GPIO_set_OUTPUT_CFG(U8 index, U32 data)
{
    m_gpio_output_cfg[index].all = data;
    *(volatile U32 *)(REG_GPIO_OUTPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)) = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_OUTPUT_CFG] <-- 0x%08x\n",
                        (REG_GPIO_OUTPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)),data,data);
    #endif
}
U32  GH_GPIO_getm_OUTPUT_CFG(U8 index)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_OUTPUT_CFG] --> 0x%08x\n",
                        m_gpio_output_cfg[index].all);
    #endif
    return m_gpio_output_cfg[index].all;
}
void GH_GPIO_set_OUTPUT_CFG_out_sel(U8 index, U8 data)
{
    m_gpio_output_cfg[index].bitc.out_sel = data;
    *(volatile U32 *)(REG_GPIO_OUTPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)) = m_gpio_output_cfg[index].all;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_OUTPUT_CFG_out_sel] <-- 0x%08x\n",
                        (REG_GPIO_OUTPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)),m_gpio_output_cfg[index].all,m_gpio_output_cfg[index].all);
    #endif
}
U8   GH_GPIO_getm_OUTPUT_CFG_out_sel(U8 index)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_OUTPUT_CFG_out_sel] --> 0x%08x\n",
                        m_gpio_output_cfg[index].bitc.out_sel);
    #endif
    return m_gpio_output_cfg[index].bitc.out_sel;
}
void GH_GPIO_set_OUTPUT_CFG_oen_sel(U8 index, U8 data)
{
    m_gpio_output_cfg[index].bitc.oen_sel = data;
    *(volatile U32 *)(REG_GPIO_OUTPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)) = m_gpio_output_cfg[index].all;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_OUTPUT_CFG_oen_sel] <-- 0x%08x\n",
                        (REG_GPIO_OUTPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)),m_gpio_output_cfg[index].all,m_gpio_output_cfg[index].all);
    #endif
}
U8   GH_GPIO_getm_OUTPUT_CFG_oen_sel(U8 index)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_OUTPUT_CFG_oen_sel] --> 0x%08x\n",
                        m_gpio_output_cfg[index].bitc.oen_sel);
    #endif
    return m_gpio_output_cfg[index].bitc.oen_sel;
}
void GH_GPIO_set_OUTPUT_CFG_out_invert(U8 index, U8 data)
{
    m_gpio_output_cfg[index].bitc.out_invert = data;
    *(volatile U32 *)(REG_GPIO_OUTPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)) = m_gpio_output_cfg[index].all;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_OUTPUT_CFG_out_invert] <-- 0x%08x\n",
                        (REG_GPIO_OUTPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)),m_gpio_output_cfg[index].all,m_gpio_output_cfg[index].all);
    #endif
}
U8   GH_GPIO_getm_OUTPUT_CFG_out_invert(U8 index)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_OUTPUT_CFG_out_invert] --> 0x%08x\n",
                        m_gpio_output_cfg[index].bitc.out_invert);
    #endif
    return m_gpio_output_cfg[index].bitc.out_invert;
}
void GH_GPIO_set_OUTPUT_CFG_oen_invert(U8 index, U8 data)
{
    m_gpio_output_cfg[index].bitc.oen_invert = data;
    *(volatile U32 *)(REG_GPIO_OUTPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)) = m_gpio_output_cfg[index].all;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_OUTPUT_CFG_oen_invert] <-- 0x%08x\n",
                        (REG_GPIO_OUTPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)),m_gpio_output_cfg[index].all,m_gpio_output_cfg[index].all);
    #endif
}
U8   GH_GPIO_getm_OUTPUT_CFG_oen_invert(U8 index)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_OUTPUT_CFG_oen_invert] --> 0x%08x\n",
                        m_gpio_output_cfg[index].bitc.oen_invert);
    #endif
    return m_gpio_output_cfg[index].bitc.oen_invert;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register GPIO_INPUT_CFG (write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_GPIO_set_INPUT_CFG(U8 index, U32 data)
{
    m_gpio_input_cfg[index].all = data;
    *(volatile U32 *)(REG_GPIO_INPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)) = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_INPUT_CFG] <-- 0x%08x\n",
                        (REG_GPIO_INPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)),data,data);
    #endif
}
U32  GH_GPIO_getm_INPUT_CFG(U8 index)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_INPUT_CFG] --> 0x%08x\n",
                        m_gpio_input_cfg[index].all);
    #endif
    return m_gpio_input_cfg[index].all;
}
void GH_GPIO_set_INPUT_CFG_in_sel(U8 index, U8 data)
{
    m_gpio_input_cfg[index].bitc.in_sel = data;
    *(volatile U32 *)(REG_GPIO_INPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)) = m_gpio_input_cfg[index].all;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_INPUT_CFG_in_sel] <-- 0x%08x\n",
                        (REG_GPIO_INPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)),m_gpio_input_cfg[index].all,m_gpio_input_cfg[index].all);
    #endif
}
U8   GH_GPIO_getm_INPUT_CFG_in_sel(U8 index)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_INPUT_CFG_in_sel] --> 0x%08x\n",
                        m_gpio_input_cfg[index].bitc.in_sel);
    #endif
    return m_gpio_input_cfg[index].bitc.in_sel;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_GPIO_init(void)
{
    int i;

    GH_GPIO_set_INT_EN((U32)0x00000000);
    GH_GPIO_set_PER_SEL((U32)0x00000000);
    GH_GPIO_set_OUTPUT_CFG(0, (U32)0x00000002);
    for (i=1; i<64; i++)
    {
        GH_GPIO_set_OUTPUT_CFG(i, (U32)0x00000100);
    }
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

