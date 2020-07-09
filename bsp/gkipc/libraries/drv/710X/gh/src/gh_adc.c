/******************************************************************************
**
** \file      gh_adc.c
**
** \brief     ADC.
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
#include "gh_adc.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_ADC_AUX_ATOP_REAL                               FIO_ADDRESS(ADC,0x60020A00) /* read/write */
#define REG_ADC_GPIO_REAL                                   FIO_ADDRESS(ADC,0x60020A04) /* read/write */
#define REG_ADC_CONTROL_REAL                                FIO_ADDRESS(ADC,0x7000D000) /* read/write */
#define REG_ADC_READDATA_REAL                               FIO_ADDRESS(ADC,0x7000D004) /* read */
#define REG_ADC_ENABLE_REAL                                 FIO_ADDRESS(ADC,0x7000D018) /* read/write */
#define REG_ADC_INTCONTROL_REAL                             FIO_ADDRESS(ADC,0x7000D044) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* ADC_AUX_ATOP */
    U32 all;
    struct {
        U32 sar_pd                      : 1;
        U32 sar_maxnsel                 : 3;
        U32 sar_maxsel                  : 4;
        U32 sar_oneshot                 : 1;
        U32 sar_freerun                 : 1;
        U32 sar_refnsel                 : 2;
        U32 sar_refsel                  : 3;
        U32                             : 17;
    } bitc;
} GH_ADC_AUX_ATOP_REAL_S;

typedef union { /* ADC_GPIO */
    U32 all;
    struct {
        U32 sar_test                    : 4;
        U32 sar_key_pge                 : 4;
        U32                             : 24;
    } bitc;
} GH_ADC_GPIO_REAL_S;

typedef union { /* ADC_Control */
    U32 all;
    struct {
        U32 status                      : 1;
        U32 start                       : 1;
        U32                             : 1;
        U32 channel                     : 3;
        U32                             : 26;
    } bitc;
} GH_ADC_CONTROL_REAL_S;

typedef union { /* ADC_IntControl */
    U32 all;
    struct {
        U32 val_lo                      : 10;
        U32                             : 5;
        U32 val_hi                      : 10;
        U32                             : 5;
        U32 en_lo                       : 1;
        U32 en_hi                       : 1;
    } bitc;
} GH_ADC_INTCONTROL_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register ADC_AUX_ATOP (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ADC_set_AUX_ATOP(U32 data)
{
    GH_ADC_AUX_ATOP_REAL_S real;
    GH_ADC_AUX_ATOP_S dummy;
    dummy.all = data ;
    real.bitc.sar_pd = dummy.bitc.sar_pd;
    real.bitc.sar_maxnsel = dummy.bitc.sar_maxnsel;
    real.bitc.sar_maxsel = dummy.bitc.sar_maxsel;
    real.bitc.sar_oneshot = dummy.bitc.sar_oneshot;
    real.bitc.sar_freerun = dummy.bitc.sar_freerun;
    real.bitc.sar_refnsel = dummy.bitc.sar_refnsel;
    real.bitc.sar_refsel = dummy.bitc.sar_refsel;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REAL = real.all;
}
GH_INLINE U32  GH_ADC_get_AUX_ATOP(void)
{
    GH_ADC_AUX_ATOP_REAL_S real;
    GH_ADC_AUX_ATOP_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ADC_AUX_ATOP_REAL);

    dummy.bitc.sar_pd = real.bitc.sar_pd;
    dummy.bitc.sar_maxnsel = real.bitc.sar_maxnsel;
    dummy.bitc.sar_maxsel = real.bitc.sar_maxsel;
    dummy.bitc.sar_oneshot = real.bitc.sar_oneshot;
    dummy.bitc.sar_freerun = real.bitc.sar_freerun;
    dummy.bitc.sar_refnsel = real.bitc.sar_refnsel;
    dummy.bitc.sar_refsel = real.bitc.sar_refsel;
    return dummy.all;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_sar_pd(U8 data)
{
    GH_ADC_AUX_ATOP_REAL_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REAL;
    d.bitc.sar_pd = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REAL = d.all;
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_sar_pd(void)
{
    GH_ADC_AUX_ATOP_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sar_pd;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_sar_maxnsel(U8 data)
{
    GH_ADC_AUX_ATOP_REAL_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REAL;
    d.bitc.sar_maxnsel = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REAL = d.all;
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_sar_maxnsel(void)
{
    GH_ADC_AUX_ATOP_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sar_maxnsel;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_sar_maxsel(U8 data)
{
    GH_ADC_AUX_ATOP_REAL_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REAL;
    d.bitc.sar_maxsel = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REAL = d.all;
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_sar_maxsel(void)
{
    GH_ADC_AUX_ATOP_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sar_maxsel;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_sar_oneshot(U8 data)
{
    GH_ADC_AUX_ATOP_REAL_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REAL;
    d.bitc.sar_oneshot = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REAL = d.all;
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_sar_oneshot(void)
{
    GH_ADC_AUX_ATOP_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sar_oneshot;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_sar_freerun(U8 data)
{
    GH_ADC_AUX_ATOP_REAL_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REAL;
    d.bitc.sar_freerun = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REAL = d.all;
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_sar_freerun(void)
{
    GH_ADC_AUX_ATOP_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sar_freerun;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_sar_refnsel(U8 data)
{
    GH_ADC_AUX_ATOP_REAL_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REAL;
    d.bitc.sar_refnsel = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REAL = d.all;
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_sar_refnsel(void)
{
    GH_ADC_AUX_ATOP_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sar_refnsel;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_sar_refsel(U8 data)
{
    GH_ADC_AUX_ATOP_REAL_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REAL;
    d.bitc.sar_refsel = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REAL = d.all;
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_sar_refsel(void)
{
    GH_ADC_AUX_ATOP_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sar_refsel;
}

/*----------------------------------------------------------------------------*/
/* register ADC_GPIO (read/write)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ADC_set_GPIO(U32 data)
{
    GH_ADC_GPIO_REAL_S real;
    GH_ADC_GPIO_S dummy;
    dummy.all = data ;
    real.bitc.sar_test = dummy.bitc.sar_test;
    real.bitc.sar_key_pge = dummy.bitc.sar_key_pge;
    *(volatile U32 *)REG_ADC_GPIO_REAL = real.all;
}
GH_INLINE U32  GH_ADC_get_GPIO(void)
{
    GH_ADC_GPIO_REAL_S real;
    GH_ADC_GPIO_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ADC_GPIO_REAL);

    dummy.bitc.sar_test = real.bitc.sar_test;
    dummy.bitc.sar_key_pge = real.bitc.sar_key_pge;
    return dummy.all;
}
GH_INLINE void GH_ADC_set_GPIO_sar_test(U8 data)
{
    GH_ADC_GPIO_REAL_S d;
    d.all = *(volatile U32 *)REG_ADC_GPIO_REAL;
    d.bitc.sar_test = data;
    *(volatile U32 *)REG_ADC_GPIO_REAL = d.all;
}
GH_INLINE U8   GH_ADC_get_GPIO_sar_test(void)
{
    GH_ADC_GPIO_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_GPIO_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sar_test;
}
GH_INLINE void GH_ADC_set_GPIO_sar_key_pge(U8 data)
{
    GH_ADC_GPIO_REAL_S d;
    d.all = *(volatile U32 *)REG_ADC_GPIO_REAL;
    d.bitc.sar_key_pge = data;
    *(volatile U32 *)REG_ADC_GPIO_REAL = d.all;
}
GH_INLINE U8   GH_ADC_get_GPIO_sar_key_pge(void)
{
    GH_ADC_GPIO_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_GPIO_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sar_key_pge;
}

/*----------------------------------------------------------------------------*/
/* register ADC_Control (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ADC_set_Control(U32 data)
{
    GH_ADC_CONTROL_REAL_S real;
    GH_ADC_CONTROL_S dummy;
    dummy.all = data ;
    real.bitc.status = dummy.bitc.status;
    real.bitc.start = dummy.bitc.start;
    real.bitc.channel = dummy.bitc.channel;
    *(volatile U32 *)REG_ADC_CONTROL_REAL = real.all;
}
GH_INLINE U32  GH_ADC_get_Control(void)
{
    GH_ADC_CONTROL_REAL_S real;
    GH_ADC_CONTROL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ADC_CONTROL_REAL);

    dummy.bitc.status = real.bitc.status;
    dummy.bitc.start = real.bitc.start;
    dummy.bitc.channel = real.bitc.channel;
    return dummy.all;
}
GH_INLINE void GH_ADC_set_Control_status(U8 data)
{
    GH_ADC_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_ADC_CONTROL_REAL;
    d.bitc.status = data;
    *(volatile U32 *)REG_ADC_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_ADC_get_Control_status(void)
{
    GH_ADC_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.status;
}
GH_INLINE void GH_ADC_set_Control_start(U8 data)
{
    GH_ADC_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_ADC_CONTROL_REAL;
    d.bitc.start = data;
    *(volatile U32 *)REG_ADC_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_ADC_get_Control_start(void)
{
    GH_ADC_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.start;
}
GH_INLINE void GH_ADC_set_Control_channel(U8 data)
{
    GH_ADC_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_ADC_CONTROL_REAL;
    d.bitc.channel = data;
    *(volatile U32 *)REG_ADC_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_ADC_get_Control_channel(void)
{
    GH_ADC_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.channel;
}

/*----------------------------------------------------------------------------*/
/* register ADC_ReadData (read)                                               */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_ADC_get_ReadData(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_ADC_READDATA_REAL + index * FIO_MOFFSET(ADC,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register ADC_Enable (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ADC_set_Enable(U32 data)
{
    *(volatile U32 *)REG_ADC_ENABLE_REAL = data;
}
GH_INLINE U32  GH_ADC_get_Enable(void)
{
    U32 value = (*(volatile U32 *)REG_ADC_ENABLE_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register ADC_IntControl (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ADC_set_IntControl(U8 index, U32 data)
{
    GH_ADC_INTCONTROL_REAL_S real;
    GH_ADC_INTCONTROL_S dummy;
    dummy.all = data ;
    real.bitc.val_lo = dummy.bitc.val_lo;
    real.bitc.val_hi = dummy.bitc.val_hi;
    real.bitc.en_lo = dummy.bitc.en_lo;
    real.bitc.en_hi = dummy.bitc.en_hi;
    *(volatile U32 *)(REG_ADC_INTCONTROL_REAL + index * FIO_MOFFSET(ADC,0x00000004)) = real.all;
}
GH_INLINE U32  GH_ADC_get_IntControl(U8 index)
{
    GH_ADC_INTCONTROL_REAL_S real;
    GH_ADC_INTCONTROL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_ADC_INTCONTROL_REAL + index * FIO_MOFFSET(ADC,0x00000004)));

    dummy.bitc.val_lo = real.bitc.val_lo;
    dummy.bitc.val_hi = real.bitc.val_hi;
    dummy.bitc.en_lo = real.bitc.en_lo;
    dummy.bitc.en_hi = real.bitc.en_hi;
    return dummy.all;
}
GH_INLINE void GH_ADC_set_IntControl_val_lo(U8 index, U16 data)
{
    GH_ADC_INTCONTROL_REAL_S d;
    d.all = *(volatile U32 *)(REG_ADC_INTCONTROL_REAL + index * FIO_MOFFSET(ADC,0x00000004));
    d.bitc.val_lo = data;
    *(volatile U32 *)(REG_ADC_INTCONTROL_REAL + index * FIO_MOFFSET(ADC,0x00000004)) = d.all;
}
GH_INLINE U16  GH_ADC_get_IntControl_val_lo(U8 index)
{
    GH_ADC_INTCONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_ADC_INTCONTROL_REAL + index * FIO_MOFFSET(ADC,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.val_lo;
}
GH_INLINE void GH_ADC_set_IntControl_val_hi(U8 index, U16 data)
{
    GH_ADC_INTCONTROL_REAL_S d;
    d.all = *(volatile U32 *)(REG_ADC_INTCONTROL_REAL + index * FIO_MOFFSET(ADC,0x00000004));
    d.bitc.val_hi = data;
    *(volatile U32 *)(REG_ADC_INTCONTROL_REAL + index * FIO_MOFFSET(ADC,0x00000004)) = d.all;
}
GH_INLINE U16  GH_ADC_get_IntControl_val_hi(U8 index)
{
    GH_ADC_INTCONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_ADC_INTCONTROL_REAL + index * FIO_MOFFSET(ADC,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.val_hi;
}
GH_INLINE void GH_ADC_set_IntControl_en_lo(U8 index, U8 data)
{
    GH_ADC_INTCONTROL_REAL_S d;
    d.all = *(volatile U32 *)(REG_ADC_INTCONTROL_REAL + index * FIO_MOFFSET(ADC,0x00000004));
    d.bitc.en_lo = data;
    *(volatile U32 *)(REG_ADC_INTCONTROL_REAL + index * FIO_MOFFSET(ADC,0x00000004)) = d.all;
}
GH_INLINE U8   GH_ADC_get_IntControl_en_lo(U8 index)
{
    GH_ADC_INTCONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_ADC_INTCONTROL_REAL + index * FIO_MOFFSET(ADC,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.en_lo;
}
GH_INLINE void GH_ADC_set_IntControl_en_hi(U8 index, U8 data)
{
    GH_ADC_INTCONTROL_REAL_S d;
    d.all = *(volatile U32 *)(REG_ADC_INTCONTROL_REAL + index * FIO_MOFFSET(ADC,0x00000004));
    d.bitc.en_hi = data;
    *(volatile U32 *)(REG_ADC_INTCONTROL_REAL + index * FIO_MOFFSET(ADC,0x00000004)) = d.all;
}
GH_INLINE U8   GH_ADC_get_IntControl_en_hi(U8 index)
{
    GH_ADC_INTCONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_ADC_INTCONTROL_REAL + index * FIO_MOFFSET(ADC,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.en_hi;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ADC_init(void)
{
    int i;

    GH_ADC_set_AUX_ATOP((U32)0x00000000);
    GH_ADC_set_GPIO((U32)0x000000f0);
    GH_ADC_set_Control((U32)0x00000000);
    GH_ADC_set_Enable((U32)0x00000000);
    for (i=0; i<2; i++)
    {
        GH_ADC_set_IntControl(i, (U32)0x00000000);
    }
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

