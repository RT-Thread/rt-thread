/******************************************************************************
**
** \file      gh_vo_dac.c
**
** \brief     VDAC Registers.
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
#include "gh_vo_dac.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_VO_DAC_EN_IDAC_X_REAL                           FIO_ADDRESS(VO_DAC,0x60022680) /* read/write */
#define REG_VO_DAC_MODE_SD_REAL                             FIO_ADDRESS(VO_DAC,0x60022681) /* read/write */
#define REG_VO_DAC_IDAC_IHALF_SD_REAL                       FIO_ADDRESS(VO_DAC,0x60022682) /* read/write */
#define REG_VO_DAC_GCR_LEVEL_REAL                           FIO_ADDRESS(VO_DAC,0x60022684) /* read/write */
#define REG_VO_DAC_IDA_IQUART_SD_REAL                       FIO_ADDRESS(VO_DAC,0x60022685) /* read/write */
#define REG_VO_DAC_GCR_IDAC_GAINX_REAL                      FIO_ADDRESS(VO_DAC,0x60022686) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* VO_DAC_EN_IDAC_X */
    U8 all;
    struct {
        U8 enable                       : 1;
        U8                              : 7;
    } bitc;
} GH_VO_DAC_EN_IDAC_X_REAL_S;

typedef union { /* VO_DAC_MODE_SD */
    U8 all;
    struct {
        U8 mode                         : 1;
        U8                              : 7;
    } bitc;
} GH_VO_DAC_MODE_SD_REAL_S;

typedef union { /* VO_DAC_IDAC_IHALF_SD */
    U8 all;
    struct {
        U8 half                         : 1;
        U8                              : 7;
    } bitc;
} GH_VO_DAC_IDAC_IHALF_SD_REAL_S;

typedef union { /* VO_DAC_GCR_LEVEL */
    U8 all;
    struct {
        U8 level                        : 2;
        U8                              : 6;
    } bitc;
} GH_VO_DAC_GCR_LEVEL_REAL_S;

typedef union { /* VO_DAC_IDA_IQUART_SD */
    U8 all;
    struct {
        U8 quart                        : 1;
        U8                              : 7;
    } bitc;
} GH_VO_DAC_IDA_IQUART_SD_REAL_S;

typedef union { /* VO_DAC_GCR_IDAC_GAINX */
    U8 all;
    struct {
        U8 gain                         : 7;
        U8                              : 1;
    } bitc;
} GH_VO_DAC_GCR_IDAC_GAINX_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register VO_DAC_EN_IDAC_X (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DAC_set_EN_IDAC_X(U8 data)
{
    GH_VO_DAC_EN_IDAC_X_REAL_S real;
    GH_VO_DAC_EN_IDAC_X_S dummy;
    dummy.all = data ;
    real.bitc.enable = dummy.bitc.enable;
    *(volatile U8 *)REG_VO_DAC_EN_IDAC_X_REAL = real.all;
}
GH_INLINE U8   GH_VO_DAC_get_EN_IDAC_X(void)
{
    GH_VO_DAC_EN_IDAC_X_REAL_S real;
    GH_VO_DAC_EN_IDAC_X_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DAC_EN_IDAC_X_REAL);

    dummy.bitc.enable = real.bitc.enable;
    return dummy.all;
}
GH_INLINE void GH_VO_DAC_set_EN_IDAC_X_enable(U8 data)
{
    GH_VO_DAC_EN_IDAC_X_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DAC_EN_IDAC_X_REAL;
    d.bitc.enable = data;
    *(volatile U8 *)REG_VO_DAC_EN_IDAC_X_REAL = d.all;
}
GH_INLINE U8   GH_VO_DAC_get_EN_IDAC_X_enable(void)
{
    GH_VO_DAC_EN_IDAC_X_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DAC_EN_IDAC_X_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.enable;
}

/*----------------------------------------------------------------------------*/
/* register VO_DAC_MODE_SD (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DAC_set_MODE_SD(U8 data)
{
    GH_VO_DAC_MODE_SD_REAL_S real;
    GH_VO_DAC_MODE_SD_S dummy;
    dummy.all = data ;
    real.bitc.mode = dummy.bitc.mode;
    *(volatile U8 *)REG_VO_DAC_MODE_SD_REAL = real.all;
}
GH_INLINE U8   GH_VO_DAC_get_MODE_SD(void)
{
    GH_VO_DAC_MODE_SD_REAL_S real;
    GH_VO_DAC_MODE_SD_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DAC_MODE_SD_REAL);

    dummy.bitc.mode = real.bitc.mode;
    return dummy.all;
}
GH_INLINE void GH_VO_DAC_set_MODE_SD_mode(U8 data)
{
    GH_VO_DAC_MODE_SD_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DAC_MODE_SD_REAL;
    d.bitc.mode = data;
    *(volatile U8 *)REG_VO_DAC_MODE_SD_REAL = d.all;
}
GH_INLINE U8   GH_VO_DAC_get_MODE_SD_mode(void)
{
    GH_VO_DAC_MODE_SD_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DAC_MODE_SD_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mode;
}

/*----------------------------------------------------------------------------*/
/* register VO_DAC_IDAC_IHALF_SD (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DAC_set_IDAC_IHALF_SD(U8 data)
{
    GH_VO_DAC_IDAC_IHALF_SD_REAL_S real;
    GH_VO_DAC_IDAC_IHALF_SD_S dummy;
    dummy.all = data ;
    real.bitc.half = dummy.bitc.half;
    *(volatile U8 *)REG_VO_DAC_IDAC_IHALF_SD_REAL = real.all;
}
GH_INLINE U8   GH_VO_DAC_get_IDAC_IHALF_SD(void)
{
    GH_VO_DAC_IDAC_IHALF_SD_REAL_S real;
    GH_VO_DAC_IDAC_IHALF_SD_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DAC_IDAC_IHALF_SD_REAL);

    dummy.bitc.half = real.bitc.half;
    return dummy.all;
}
GH_INLINE void GH_VO_DAC_set_IDAC_IHALF_SD_half(U8 data)
{
    GH_VO_DAC_IDAC_IHALF_SD_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DAC_IDAC_IHALF_SD_REAL;
    d.bitc.half = data;
    *(volatile U8 *)REG_VO_DAC_IDAC_IHALF_SD_REAL = d.all;
}
GH_INLINE U8   GH_VO_DAC_get_IDAC_IHALF_SD_half(void)
{
    GH_VO_DAC_IDAC_IHALF_SD_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DAC_IDAC_IHALF_SD_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.half;
}

/*----------------------------------------------------------------------------*/
/* register VO_DAC_GCR_LEVEL (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DAC_set_GCR_LEVEL(U8 data)
{
    GH_VO_DAC_GCR_LEVEL_REAL_S real;
    GH_VO_DAC_GCR_LEVEL_S dummy;
    dummy.all = data ;
    real.bitc.level = dummy.bitc.level;
    *(volatile U8 *)REG_VO_DAC_GCR_LEVEL_REAL = real.all;
}
GH_INLINE U8   GH_VO_DAC_get_GCR_LEVEL(void)
{
    GH_VO_DAC_GCR_LEVEL_REAL_S real;
    GH_VO_DAC_GCR_LEVEL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DAC_GCR_LEVEL_REAL);

    dummy.bitc.level = real.bitc.level;
    return dummy.all;
}
GH_INLINE void GH_VO_DAC_set_GCR_LEVEL_level(U8 data)
{
    GH_VO_DAC_GCR_LEVEL_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DAC_GCR_LEVEL_REAL;
    d.bitc.level = data;
    *(volatile U8 *)REG_VO_DAC_GCR_LEVEL_REAL = d.all;
}
GH_INLINE U8   GH_VO_DAC_get_GCR_LEVEL_level(void)
{
    GH_VO_DAC_GCR_LEVEL_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DAC_GCR_LEVEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.level;
}

/*----------------------------------------------------------------------------*/
/* register VO_DAC_IDA_IQUART_SD (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DAC_set_IDA_IQUART_SD(U8 data)
{
    GH_VO_DAC_IDA_IQUART_SD_REAL_S real;
    GH_VO_DAC_IDA_IQUART_SD_S dummy;
    dummy.all = data ;
    real.bitc.quart = dummy.bitc.quart;
    *(volatile U8 *)REG_VO_DAC_IDA_IQUART_SD_REAL = real.all;
}
GH_INLINE U8   GH_VO_DAC_get_IDA_IQUART_SD(void)
{
    GH_VO_DAC_IDA_IQUART_SD_REAL_S real;
    GH_VO_DAC_IDA_IQUART_SD_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DAC_IDA_IQUART_SD_REAL);

    dummy.bitc.quart = real.bitc.quart;
    return dummy.all;
}
GH_INLINE void GH_VO_DAC_set_IDA_IQUART_SD_quart(U8 data)
{
    GH_VO_DAC_IDA_IQUART_SD_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DAC_IDA_IQUART_SD_REAL;
    d.bitc.quart = data;
    *(volatile U8 *)REG_VO_DAC_IDA_IQUART_SD_REAL = d.all;
}
GH_INLINE U8   GH_VO_DAC_get_IDA_IQUART_SD_quart(void)
{
    GH_VO_DAC_IDA_IQUART_SD_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DAC_IDA_IQUART_SD_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.quart;
}

/*----------------------------------------------------------------------------*/
/* register VO_DAC_GCR_IDAC_GAINX (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DAC_set_GCR_IDAC_GAINX(U8 data)
{
    GH_VO_DAC_GCR_IDAC_GAINX_REAL_S real;
    GH_VO_DAC_GCR_IDAC_GAINX_S dummy;
    dummy.all = data ;
    real.bitc.gain = dummy.bitc.gain;
    *(volatile U8 *)REG_VO_DAC_GCR_IDAC_GAINX_REAL = real.all;
}
GH_INLINE U8   GH_VO_DAC_get_GCR_IDAC_GAINX(void)
{
    GH_VO_DAC_GCR_IDAC_GAINX_REAL_S real;
    GH_VO_DAC_GCR_IDAC_GAINX_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DAC_GCR_IDAC_GAINX_REAL);

    dummy.bitc.gain = real.bitc.gain;
    return dummy.all;
}
GH_INLINE void GH_VO_DAC_set_GCR_IDAC_GAINX_gain(U8 data)
{
    GH_VO_DAC_GCR_IDAC_GAINX_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DAC_GCR_IDAC_GAINX_REAL;
    d.bitc.gain = data;
    *(volatile U8 *)REG_VO_DAC_GCR_IDAC_GAINX_REAL = d.all;
}
GH_INLINE U8   GH_VO_DAC_get_GCR_IDAC_GAINX_gain(void)
{
    GH_VO_DAC_GCR_IDAC_GAINX_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DAC_GCR_IDAC_GAINX_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gain;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DAC_init(void)
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

