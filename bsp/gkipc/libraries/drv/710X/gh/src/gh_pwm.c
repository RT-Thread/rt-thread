/******************************************************************************
**
** \file      gh_pwm.c
**
** \brief     Pulse Width Modulator.
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
#include "gh_pwm.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_PWM_CONTROL_REAL                                FIO_ADDRESS(PWM,0x70010000) /* read/write */
#define REG_PWM_ENABLE_REAL                                 FIO_ADDRESS(PWM,0x70010004) /* read/write */
#define REG_PWM_MODE_REAL                                   FIO_ADDRESS(PWM,0x70010008) /* read/write */
#define REG_PWM_CONTROL1_REAL                               FIO_ADDRESS(PWM,0x7001000C) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* PWM_Control */
    U32 all;
    struct {
        U32 xoff                        : 16;
        U32 xon                         : 16;
    } bitc;
} GH_PWM_CONTROL_REAL_S;

typedef union { /* PWM_Enable */
    U32 all;
    struct {
        U32 enb                         : 1;
        U32                             : 31;
    } bitc;
} GH_PWM_ENABLE_REAL_S;

typedef union { /* PWM_Mode */
    U32 all;
    struct {
        U32 mode                        : 1;
        U32 divider                     : 10;
        U32                             : 21;
    } bitc;
} GH_PWM_MODE_REAL_S;

typedef union { /* PWM_Control1 */
    U32 all;
    struct {
        U32 xoff                        : 16;
        U32 xon                         : 16;
    } bitc;
} GH_PWM_CONTROL1_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register PWM_Control (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PWM_set_Control(U8 index, U32 data)
{
    GH_PWM_CONTROL_REAL_S real;
    GH_PWM_CONTROL_S dummy;
    dummy.all = data ;
    real.bitc.xoff = dummy.bitc.xoff;
    real.bitc.xon = dummy.bitc.xon;
    *(volatile U32 *)(REG_PWM_CONTROL_REAL + index * FIO_MOFFSET(PWM,0x00001000)) = real.all;
}
GH_INLINE U32  GH_PWM_get_Control(U8 index)
{
    GH_PWM_CONTROL_REAL_S real;
    GH_PWM_CONTROL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_PWM_CONTROL_REAL + index * FIO_MOFFSET(PWM,0x00001000)));

    dummy.bitc.xoff = real.bitc.xoff;
    dummy.bitc.xon = real.bitc.xon;
    return dummy.all;
}
GH_INLINE void GH_PWM_set_Control_xoff(U8 index, U16 data)
{
    GH_PWM_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)(REG_PWM_CONTROL_REAL + index * FIO_MOFFSET(PWM,0x00001000));
    d.bitc.xoff = data;
    *(volatile U32 *)(REG_PWM_CONTROL_REAL + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
}
GH_INLINE U16  GH_PWM_get_Control_xoff(U8 index)
{
    GH_PWM_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PWM_CONTROL_REAL + index * FIO_MOFFSET(PWM,0x00001000)));

    tmp_value.all = value;
    return tmp_value.bitc.xoff;
}
GH_INLINE void GH_PWM_set_Control_xon(U8 index, U16 data)
{
    GH_PWM_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)(REG_PWM_CONTROL_REAL + index * FIO_MOFFSET(PWM,0x00001000));
    d.bitc.xon = data;
    *(volatile U32 *)(REG_PWM_CONTROL_REAL + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
}
GH_INLINE U16  GH_PWM_get_Control_xon(U8 index)
{
    GH_PWM_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PWM_CONTROL_REAL + index * FIO_MOFFSET(PWM,0x00001000)));

    tmp_value.all = value;
    return tmp_value.bitc.xon;
}

/*----------------------------------------------------------------------------*/
/* register PWM_Enable (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PWM_set_Enable(U8 index, U32 data)
{
    GH_PWM_ENABLE_REAL_S real;
    GH_PWM_ENABLE_S dummy;
    dummy.all = data ;
    real.bitc.enb = dummy.bitc.enb;
    *(volatile U32 *)(REG_PWM_ENABLE_REAL + index * FIO_MOFFSET(PWM,0x00001000)) = real.all;
}
GH_INLINE U32  GH_PWM_get_Enable(U8 index)
{
    GH_PWM_ENABLE_REAL_S real;
    GH_PWM_ENABLE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_PWM_ENABLE_REAL + index * FIO_MOFFSET(PWM,0x00001000)));

    dummy.bitc.enb = real.bitc.enb;
    return dummy.all;
}
GH_INLINE void GH_PWM_set_Enable_enb(U8 index, U8 data)
{
    GH_PWM_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)(REG_PWM_ENABLE_REAL + index * FIO_MOFFSET(PWM,0x00001000));
    d.bitc.enb = data;
    *(volatile U32 *)(REG_PWM_ENABLE_REAL + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
}
GH_INLINE U8   GH_PWM_get_Enable_enb(U8 index)
{
    GH_PWM_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PWM_ENABLE_REAL + index * FIO_MOFFSET(PWM,0x00001000)));

    tmp_value.all = value;
    return tmp_value.bitc.enb;
}

/*----------------------------------------------------------------------------*/
/* register PWM_Mode (read/write)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PWM_set_Mode(U8 index, U32 data)
{
    GH_PWM_MODE_REAL_S d;

    d.all = *(volatile U32 *)(REG_PWM_MODE_REAL + index * FIO_MOFFSET(PWM,0x00001000));
    d.bitc.mode= data;
    *(volatile U32 *)(REG_PWM_MODE_REAL + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
}

GH_INLINE U32  GH_PWM_get_Mode(U8 index)
{
    GH_PWM_MODE_REAL_S real;
    GH_PWM_MODE_S dummy;
    dummy.all =  0;
    real.all = (*(volatile U32 *)(REG_PWM_MODE_REAL + index * FIO_MOFFSET(PWM,0x00001000)));

    dummy.bitc.mode = real.bitc.mode;
    dummy.bitc.divider = real.bitc.divider;
    return dummy.bitc.mode;
}

GH_INLINE void GH_PWM_set_Mode_mode(U8 index, U8 data)
{
    GH_PWM_MODE_REAL_S d;
    d.all = *(volatile U32 *)(REG_PWM_MODE_REAL + index * FIO_MOFFSET(PWM,0x00001000));
    d.bitc.mode = data;
    *(volatile U32 *)(REG_PWM_MODE_REAL + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
}
GH_INLINE U8   GH_PWM_get_Mode_mode(U8 index)
{
    GH_PWM_MODE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PWM_MODE_REAL + index * FIO_MOFFSET(PWM,0x00001000)));

    tmp_value.all = value;
    return tmp_value.bitc.mode;
}
GH_INLINE void GH_PWM_set_Mode_divider(U8 index, U16 data)
{
    GH_PWM_MODE_REAL_S d;
    d.all = *(volatile U32 *)(REG_PWM_MODE_REAL + index * FIO_MOFFSET(PWM,0x00001000));
    d.bitc.divider = data;
    *(volatile U32 *)(REG_PWM_MODE_REAL + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
}
GH_INLINE U16  GH_PWM_get_Mode_divider(U8 index)
{
    GH_PWM_MODE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PWM_MODE_REAL + index * FIO_MOFFSET(PWM,0x00001000)));

    tmp_value.all = value;
    return tmp_value.bitc.divider;
}

/*----------------------------------------------------------------------------*/
/* register PWM_Control1 (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PWM_set_Control1(U8 index, U32 data)
{
    GH_PWM_CONTROL1_REAL_S real;
    GH_PWM_CONTROL1_S dummy;
    dummy.all = data ;
    real.bitc.xoff = dummy.bitc.xoff;
    real.bitc.xon = dummy.bitc.xon;
    *(volatile U32 *)(REG_PWM_CONTROL1_REAL + index * FIO_MOFFSET(PWM,0x00001000)) = real.all;
}
GH_INLINE U32  GH_PWM_get_Control1(U8 index)
{
    GH_PWM_CONTROL1_REAL_S real;
    GH_PWM_CONTROL1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_PWM_CONTROL1_REAL + index * FIO_MOFFSET(PWM,0x00001000)));

    dummy.bitc.xoff = real.bitc.xoff;
    dummy.bitc.xon = real.bitc.xon;
    return dummy.all;
}
GH_INLINE void GH_PWM_set_Control1_xoff(U8 index, U16 data)
{
    GH_PWM_CONTROL1_REAL_S d;
    d.all = *(volatile U32 *)(REG_PWM_CONTROL1_REAL + index * FIO_MOFFSET(PWM,0x00001000));
    d.bitc.xoff = data;
    *(volatile U32 *)(REG_PWM_CONTROL1_REAL + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
}
GH_INLINE U16  GH_PWM_get_Control1_xoff(U8 index)
{
    GH_PWM_CONTROL1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PWM_CONTROL1_REAL + index * FIO_MOFFSET(PWM,0x00001000)));

    tmp_value.all = value;
    return tmp_value.bitc.xoff;
}
GH_INLINE void GH_PWM_set_Control1_xon(U8 index, U16 data)
{
    GH_PWM_CONTROL1_REAL_S d;
    d.all = *(volatile U32 *)(REG_PWM_CONTROL1_REAL + index * FIO_MOFFSET(PWM,0x00001000));
    d.bitc.xon = data;
    *(volatile U32 *)(REG_PWM_CONTROL1_REAL + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
}
GH_INLINE U16  GH_PWM_get_Control1_xon(U8 index)
{
    GH_PWM_CONTROL1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PWM_CONTROL1_REAL + index * FIO_MOFFSET(PWM,0x00001000)));

    tmp_value.all = value;
    return tmp_value.bitc.xon;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PWM_init(void)
{
    int i;

    for (i=0; i<4; i++)
    {
        GH_PWM_set_Control(i, (U32)0x00000000);
    }
    for (i=0; i<4; i++)
    {
        GH_PWM_set_Enable(i, (U32)0x00000000);
    }
    for (i=0; i<4; i++)
    {
        GH_PWM_set_Mode(i, (U32)0x00000000);
    }
    for (i=0; i<4; i++)
    {
        GH_PWM_set_Control1(i, (U32)0x00000000);
    }
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

