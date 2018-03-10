/******************************************************************************
**
** \file      gh_gpio.c
**
** \brief     These GPIO pins can be configured as I/O pins for other hardware modules..
**
**            Copyright:   2012 - 2016 (C) GoKe Microelectronics
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      Do not modify this file as it is generated automatically.
**
******************************************************************************/
#ifndef SRC_INLINE
#include "gh_gpio.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_GPIO_IS_LOW_REAL                                FIO_ADDRESS(GPIO,0x70009000) /* read/write */
#define REG_GPIO_IS_HIGH_REAL                               FIO_ADDRESS(GPIO,0x70009004) /* read/write */
#define REG_GPIO_IBE_LOW_REAL                               FIO_ADDRESS(GPIO,0x70009008) /* read/write */
#define REG_GPIO_IBE_HIGH_REAL                              FIO_ADDRESS(GPIO,0x7000900C) /* read/write */
#define REG_GPIO_IEV_LOW_REAL                               FIO_ADDRESS(GPIO,0x70009010) /* read/write */
#define REG_GPIO_IEV_HIGH_REAL                              FIO_ADDRESS(GPIO,0x70009014) /* read/write */
#define REG_GPIO_IE_LOW_REAL                                FIO_ADDRESS(GPIO,0x70009018) /* read/write */
#define REG_GPIO_IE_HIGH_REAL                               FIO_ADDRESS(GPIO,0x7000901C) /* read/write */
#define REG_GPIO_IC_LOW_REAL                                FIO_ADDRESS(GPIO,0x70009020) /* write */
#define REG_GPIO_IC_HIGH_REAL                               FIO_ADDRESS(GPIO,0x70009024) /* write */
#define REG_GPIO_RIS_LOW_REAL                               FIO_ADDRESS(GPIO,0x70009028) /* read */
#define REG_GPIO_RIS_HIGH_REAL                              FIO_ADDRESS(GPIO,0x7000902C) /* read */
#define REG_GPIO_MIS_LOW_REAL                               FIO_ADDRESS(GPIO,0x70009030) /* read */
#define REG_GPIO_MIS_HIGH_REAL                              FIO_ADDRESS(GPIO,0x70009034) /* read */
#define REG_GPIO_INT_EN_REAL                                FIO_ADDRESS(GPIO,0x70009038) /* write */
#define REG_GPIO_PER_SEL_REAL                               FIO_ADDRESS(GPIO,0x7000903C) /* read/write */
#define REG_GPIO_DIN_LOW_REAL                               FIO_ADDRESS(GPIO,0x70009040) /* read */
#define REG_GPIO_DIN_HIGH_REAL                              FIO_ADDRESS(GPIO,0x70009044) /* read */
#define REG_GPIO_OUTPUT_CFG_REAL                            FIO_ADDRESS(GPIO,0x70009100) /* write */
#define REG_GPIO_INPUT_CFG_REAL                             FIO_ADDRESS(GPIO,0x70009200) /* write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* GPIO_INT_EN */
    U32 all;
    struct {
        U32 int_en                      : 1;
        U32                             : 31;
    } bitc;
} GH_GPIO_INT_EN_REAL_S;

typedef union { /* GPIO_PER_SEL */
    U32 all;
    struct {
        U32 enet_sel                    : 1;
        U32 i2s_sel                     : 1;
        U32                             : 30;
    } bitc;
} GH_GPIO_PER_SEL_REAL_S;

typedef union { /* GPIO_OUTPUT_CFG */
    U32 all;
    struct {
        U32 out_sel                     : 6;
        U32                             : 2;
        U32 oen_sel                     : 6;
        U32 out_invert                  : 1;
        U32 oen_invert                  : 1;
        U32                             : 16;
    } bitc;
} GH_GPIO_OUTPUT_CFG_REAL_S;

typedef union { /* GPIO_INPUT_CFG */
    U32 all;
    struct {
        U32 in_sel                      : 6;
        U32                             : 26;
    } bitc;
} GH_GPIO_INPUT_CFG_REAL_S;


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
GH_INLINE void GH_GPIO_set_IS_LOW(U32 data)
{
    *(volatile U32 *)REG_GPIO_IS_LOW_REAL = data;
}
GH_INLINE U32  GH_GPIO_get_IS_LOW(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IS_LOW_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_IS_HIGH (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_IS_HIGH(U32 data)
{
    *(volatile U32 *)REG_GPIO_IS_HIGH_REAL = data;
}
GH_INLINE U32  GH_GPIO_get_IS_HIGH(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IS_HIGH_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_IBE_LOW (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_IBE_LOW(U32 data)
{
    *(volatile U32 *)REG_GPIO_IBE_LOW_REAL = data;
}
GH_INLINE U32  GH_GPIO_get_IBE_LOW(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IBE_LOW_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_IBE_HIGH (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_IBE_HIGH(U32 data)
{
    *(volatile U32 *)REG_GPIO_IBE_HIGH_REAL = data;
}
GH_INLINE U32  GH_GPIO_get_IBE_HIGH(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IBE_HIGH_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_IEV_LOW (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_IEV_LOW(U32 data)
{
    *(volatile U32 *)REG_GPIO_IEV_LOW_REAL = data;
}
GH_INLINE U32  GH_GPIO_get_IEV_LOW(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IEV_LOW_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_IEV_HIGH (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_IEV_HIGH(U32 data)
{
    *(volatile U32 *)REG_GPIO_IEV_HIGH_REAL = data;
}
GH_INLINE U32  GH_GPIO_get_IEV_HIGH(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IEV_HIGH_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_IE_LOW (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_IE_LOW(U32 data)
{
    *(volatile U32 *)REG_GPIO_IE_LOW_REAL = data;
}
GH_INLINE U32  GH_GPIO_get_IE_LOW(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IE_LOW_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_IE_HIGH (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_IE_HIGH(U32 data)
{
    *(volatile U32 *)REG_GPIO_IE_HIGH_REAL = data;
}
GH_INLINE U32  GH_GPIO_get_IE_HIGH(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IE_HIGH_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_IC_LOW (write)                                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_IC_LOW(U32 data)
{
    m_gpio_ic_low = data;
    *(volatile U32 *)REG_GPIO_IC_LOW_REAL = data;
}
GH_INLINE U32  GH_GPIO_getm_IC_LOW(void)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_IC_LOW] --> 0x%08x\n",
                        m_gpio_ic_low);
    #endif
    return m_gpio_ic_low;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_IC_HIGH (write)                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_IC_HIGH(U32 data)
{
    m_gpio_ic_high = data;
    *(volatile U32 *)REG_GPIO_IC_HIGH_REAL = data;
}
GH_INLINE U32  GH_GPIO_getm_IC_HIGH(void)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_IC_HIGH] --> 0x%08x\n",
                        m_gpio_ic_high);
    #endif
    return m_gpio_ic_high;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_RIS_LOW (read)                                               */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_GPIO_get_RIS_LOW(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_RIS_LOW_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_RIS_HIGH (read)                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_GPIO_get_RIS_HIGH(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_RIS_HIGH_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_MIS_LOW (read)                                               */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_GPIO_get_MIS_LOW(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_MIS_LOW_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_MIS_HIGH (read)                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_GPIO_get_MIS_HIGH(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_MIS_HIGH_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_INT_EN (write)                                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_INT_EN(U32 data)
{
    m_gpio_int_en.all = data;
    GH_GPIO_INT_EN_REAL_S real;
    GH_GPIO_INT_EN_S dummy;
    dummy.all = data ;
    real.bitc.int_en = dummy.bitc.int_en;
    *(volatile U32 *)REG_GPIO_INT_EN_REAL = real.all;
}
GH_INLINE U32  GH_GPIO_getm_INT_EN(void)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_INT_EN] --> 0x%08x\n",
                        m_gpio_int_en.all);
    #endif
    return m_gpio_int_en.all;
}
GH_INLINE void GH_GPIO_set_INT_EN_int_en(U8 data)
{
    m_gpio_int_en.bitc.int_en = data;
    GH_GPIO_INT_EN_REAL_S real;
    real.bitc.int_en = m_gpio_int_en.bitc.int_en;
    *(volatile U32 *)REG_GPIO_INT_EN_REAL = real.all;
}
GH_INLINE U8   GH_GPIO_getm_INT_EN_int_en(void)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_INT_EN_int_en] --> 0x%08x\n",
                        m_gpio_int_en.bitc.int_en);
    #endif
    return m_gpio_int_en.bitc.int_en;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_PER_SEL (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_PER_SEL(U32 data)
{
    GH_GPIO_PER_SEL_REAL_S real;
    GH_GPIO_PER_SEL_S dummy;
    dummy.all = data ;
    real.bitc.enet_sel = dummy.bitc.enet_sel;
    real.bitc.i2s_sel = dummy.bitc.i2s_sel;
    *(volatile U32 *)REG_GPIO_PER_SEL_REAL = real.all;
}
GH_INLINE U32  GH_GPIO_get_PER_SEL(void)
{
    GH_GPIO_PER_SEL_REAL_S real;
    GH_GPIO_PER_SEL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_GPIO_PER_SEL_REAL);

    dummy.bitc.enet_sel = real.bitc.enet_sel;
    dummy.bitc.i2s_sel = real.bitc.i2s_sel;
    return dummy.all;
}
GH_INLINE void GH_GPIO_set_PER_SEL_enet_sel(U8 data)
{
    GH_GPIO_PER_SEL_REAL_S d;
    d.all = *(volatile U32 *)REG_GPIO_PER_SEL_REAL;
    d.bitc.enet_sel = data;
    *(volatile U32 *)REG_GPIO_PER_SEL_REAL = d.all;
}
GH_INLINE U8   GH_GPIO_get_PER_SEL_enet_sel(void)
{
    GH_GPIO_PER_SEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_GPIO_PER_SEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.enet_sel;
}
GH_INLINE void GH_GPIO_set_PER_SEL_i2s_sel(U8 data)
{
    GH_GPIO_PER_SEL_REAL_S d;
    d.all = *(volatile U32 *)REG_GPIO_PER_SEL_REAL;
    d.bitc.i2s_sel = data;
    *(volatile U32 *)REG_GPIO_PER_SEL_REAL = d.all;
}
GH_INLINE U8   GH_GPIO_get_PER_SEL_i2s_sel(void)
{
    GH_GPIO_PER_SEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_GPIO_PER_SEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.i2s_sel;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_DIN_LOW (read)                                               */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_GPIO_get_DIN_LOW(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_DIN_LOW_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_DIN_HIGH (read)                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_GPIO_get_DIN_HIGH(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_DIN_HIGH_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_OUTPUT_CFG (write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_OUTPUT_CFG(U8 index, U32 data)
{
    m_gpio_output_cfg[index].all = data;
    GH_GPIO_OUTPUT_CFG_REAL_S real;
    GH_GPIO_OUTPUT_CFG_S dummy;
    dummy.all = data ;
    real.bitc.out_sel = dummy.bitc.out_sel;
    real.bitc.oen_sel = dummy.bitc.oen_sel;
    real.bitc.out_invert = dummy.bitc.out_invert;
    real.bitc.oen_invert = dummy.bitc.oen_invert;
    *(volatile U32 *)(REG_GPIO_OUTPUT_CFG_REAL + index * FIO_MOFFSET(GPIO,0x4)) = real.all;
}
GH_INLINE U32  GH_GPIO_getm_OUTPUT_CFG(U8 index)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_OUTPUT_CFG] --> 0x%08x\n",
                        m_gpio_output_cfg[index].all);
    #endif
    return m_gpio_output_cfg[index].all;
}
GH_INLINE void GH_GPIO_set_OUTPUT_CFG_out_sel(U8 index, U8 data)
{
    m_gpio_output_cfg[index].bitc.out_sel = data;
    GH_GPIO_OUTPUT_CFG_REAL_S real;
    real.bitc.out_sel = m_gpio_output_cfg[index].bitc.out_sel;
    real.bitc.oen_sel = m_gpio_output_cfg[index].bitc.oen_sel;
    real.bitc.out_invert = m_gpio_output_cfg[index].bitc.out_invert;
    real.bitc.oen_invert = m_gpio_output_cfg[index].bitc.oen_invert;
    *(volatile U32 *)(REG_GPIO_OUTPUT_CFG_REAL + index * FIO_MOFFSET(GPIO,0x4)) = real.all;
}
GH_INLINE U8   GH_GPIO_getm_OUTPUT_CFG_out_sel(U8 index)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_OUTPUT_CFG_out_sel] --> 0x%08x\n",
                        m_gpio_output_cfg[index].bitc.out_sel);
    #endif
    return m_gpio_output_cfg[index].bitc.out_sel;
}
GH_INLINE void GH_GPIO_set_OUTPUT_CFG_oen_sel(U8 index, U8 data)
{
    m_gpio_output_cfg[index].bitc.oen_sel = data;
    GH_GPIO_OUTPUT_CFG_REAL_S real;
    real.bitc.out_sel = m_gpio_output_cfg[index].bitc.out_sel;
    real.bitc.oen_sel = m_gpio_output_cfg[index].bitc.oen_sel;
    real.bitc.out_invert = m_gpio_output_cfg[index].bitc.out_invert;
    real.bitc.oen_invert = m_gpio_output_cfg[index].bitc.oen_invert;
    *(volatile U32 *)(REG_GPIO_OUTPUT_CFG_REAL + index * FIO_MOFFSET(GPIO,0x4)) = real.all;
}
GH_INLINE U8   GH_GPIO_getm_OUTPUT_CFG_oen_sel(U8 index)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_OUTPUT_CFG_oen_sel] --> 0x%08x\n",
                        m_gpio_output_cfg[index].bitc.oen_sel);
    #endif
    return m_gpio_output_cfg[index].bitc.oen_sel;
}
GH_INLINE void GH_GPIO_set_OUTPUT_CFG_out_invert(U8 index, U8 data)
{
    m_gpio_output_cfg[index].bitc.out_invert = data;
    GH_GPIO_OUTPUT_CFG_REAL_S real;
    real.bitc.out_sel = m_gpio_output_cfg[index].bitc.out_sel;
    real.bitc.oen_sel = m_gpio_output_cfg[index].bitc.oen_sel;
    real.bitc.out_invert = m_gpio_output_cfg[index].bitc.out_invert;
    real.bitc.oen_invert = m_gpio_output_cfg[index].bitc.oen_invert;
    *(volatile U32 *)(REG_GPIO_OUTPUT_CFG_REAL + index * FIO_MOFFSET(GPIO,0x4)) = real.all;
}
GH_INLINE U8   GH_GPIO_getm_OUTPUT_CFG_out_invert(U8 index)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_OUTPUT_CFG_out_invert] --> 0x%08x\n",
                        m_gpio_output_cfg[index].bitc.out_invert);
    #endif
    return m_gpio_output_cfg[index].bitc.out_invert;
}
GH_INLINE void GH_GPIO_set_OUTPUT_CFG_oen_invert(U8 index, U8 data)
{
    m_gpio_output_cfg[index].bitc.oen_invert = data;
    GH_GPIO_OUTPUT_CFG_REAL_S real;
    real.bitc.out_sel = m_gpio_output_cfg[index].bitc.out_sel;
    real.bitc.oen_sel = m_gpio_output_cfg[index].bitc.oen_sel;
    real.bitc.out_invert = m_gpio_output_cfg[index].bitc.out_invert;
    real.bitc.oen_invert = m_gpio_output_cfg[index].bitc.oen_invert;
    *(volatile U32 *)(REG_GPIO_OUTPUT_CFG_REAL + index * FIO_MOFFSET(GPIO,0x4)) = real.all;
}
GH_INLINE U8   GH_GPIO_getm_OUTPUT_CFG_oen_invert(U8 index)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_OUTPUT_CFG_oen_invert] --> 0x%08x\n",
                        m_gpio_output_cfg[index].bitc.oen_invert);
    #endif
    return m_gpio_output_cfg[index].bitc.oen_invert;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_INPUT_CFG (write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_INPUT_CFG(U8 index, U32 data)
{
    m_gpio_input_cfg[index].all = data;
    GH_GPIO_INPUT_CFG_REAL_S real;
    GH_GPIO_INPUT_CFG_S dummy;
    dummy.all = data ;
    real.bitc.in_sel = dummy.bitc.in_sel;
    *(volatile U32 *)(REG_GPIO_INPUT_CFG_REAL + index * FIO_MOFFSET(GPIO,0x4)) = real.all;
}
GH_INLINE U32  GH_GPIO_getm_INPUT_CFG(U8 index)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_INPUT_CFG] --> 0x%08x\n",
                        m_gpio_input_cfg[index].all);
    #endif
    return m_gpio_input_cfg[index].all;
}
GH_INLINE void GH_GPIO_set_INPUT_CFG_in_sel(U8 index, U8 data)
{
    m_gpio_input_cfg[index].bitc.in_sel = data;
    GH_GPIO_INPUT_CFG_REAL_S real;
    real.bitc.in_sel = m_gpio_input_cfg[index].bitc.in_sel;
    *(volatile U32 *)(REG_GPIO_INPUT_CFG_REAL + index * FIO_MOFFSET(GPIO,0x4)) = real.all;
}
GH_INLINE U8   GH_GPIO_getm_INPUT_CFG_in_sel(U8 index)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_INPUT_CFG_in_sel] --> 0x%08x\n",
                        m_gpio_input_cfg[index].bitc.in_sel);
    #endif
    return m_gpio_input_cfg[index].bitc.in_sel;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_init(void)
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

