/******************************************************************************
**
** \file      gh_timer.c
**
** \brief     TIMER.
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
#include "gh_timer.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_TIMER_CNTNSTS_REAL                              FIO_ADDRESS(TIMER,0x7000B000) /* read/write */
#define REG_TIMER_RELOADN_REAL                              FIO_ADDRESS(TIMER,0x7000B004) /* read/write */
#define REG_TIMER_MATCH1_REAL                               FIO_ADDRESS(TIMER,0x7000B008) /* read/write */
#define REG_TIMER_MATCH2_REAL                               FIO_ADDRESS(TIMER,0x7000B00C) /* read/write */
#define REG_TIMER_CONTROL_REAL                              FIO_ADDRESS(TIMER,0x7000B030) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* TIMER_Control */
    U32 all;
    struct {
        U32 enable1                     : 1;
        U32 clksel1                     : 1;
        U32 of1                         : 1;
        U32                             : 1;
        U32 enable2                     : 1;
        U32 clksel2                     : 1;
        U32 of2                         : 1;
        U32                             : 1;
        U32 enable3                     : 1;
        U32 clksel3                     : 1;
        U32 of3                         : 1;
        U32                             : 21;
    } bitc;
} GH_TIMER_CONTROL_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register TIMER_CntnSts (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_TIMER_set_CntnSts(U8 index, U32 data)
{
    *(volatile U32 *)(REG_TIMER_CNTNSTS_REAL + index * FIO_MOFFSET(TIMER,0x00000010)) = data;
}
GH_INLINE U32  GH_TIMER_get_CntnSts(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_TIMER_CNTNSTS_REAL + index * FIO_MOFFSET(TIMER,0x00000010)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register TIMER_Reloadn (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_TIMER_set_Reloadn(U8 index, U32 data)
{
    *(volatile U32 *)(REG_TIMER_RELOADN_REAL + index * FIO_MOFFSET(TIMER,0x00000010)) = data;
}
GH_INLINE U32  GH_TIMER_get_Reloadn(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_TIMER_RELOADN_REAL + index * FIO_MOFFSET(TIMER,0x00000010)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register TIMER_Match1 (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_TIMER_set_Match1(U8 index, U32 data)
{
    *(volatile U32 *)(REG_TIMER_MATCH1_REAL + index * FIO_MOFFSET(TIMER,0x00000010)) = data;
}
GH_INLINE U32  GH_TIMER_get_Match1(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_TIMER_MATCH1_REAL + index * FIO_MOFFSET(TIMER,0x00000010)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register TIMER_Match2 (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_TIMER_set_Match2(U8 index, U32 data)
{
    *(volatile U32 *)(REG_TIMER_MATCH2_REAL + index * FIO_MOFFSET(TIMER,0x00000010)) = data;
}
GH_INLINE U32  GH_TIMER_get_Match2(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_TIMER_MATCH2_REAL + index * FIO_MOFFSET(TIMER,0x00000010)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register TIMER_Control (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_TIMER_set_Control(U32 data)
{
    GH_TIMER_CONTROL_REAL_S real;
    GH_TIMER_CONTROL_S dummy;
    dummy.all = data ;
    real.bitc.enable1 = dummy.bitc.enable1;
    real.bitc.clksel1 = dummy.bitc.clksel1;
    real.bitc.of1 = dummy.bitc.of1;
    real.bitc.enable2 = dummy.bitc.enable2;
    real.bitc.clksel2 = dummy.bitc.clksel2;
    real.bitc.of2 = dummy.bitc.of2;
    real.bitc.enable3 = dummy.bitc.enable3;
    real.bitc.clksel3 = dummy.bitc.clksel3;
    real.bitc.of3 = dummy.bitc.of3;
    *(volatile U32 *)REG_TIMER_CONTROL_REAL = real.all;
}
GH_INLINE U32  GH_TIMER_get_Control(void)
{
    GH_TIMER_CONTROL_REAL_S real;
    GH_TIMER_CONTROL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_TIMER_CONTROL_REAL);

    dummy.bitc.enable1 = real.bitc.enable1;
    dummy.bitc.clksel1 = real.bitc.clksel1;
    dummy.bitc.of1 = real.bitc.of1;
    dummy.bitc.enable2 = real.bitc.enable2;
    dummy.bitc.clksel2 = real.bitc.clksel2;
    dummy.bitc.of2 = real.bitc.of2;
    dummy.bitc.enable3 = real.bitc.enable3;
    dummy.bitc.clksel3 = real.bitc.clksel3;
    dummy.bitc.of3 = real.bitc.of3;
    return dummy.all;
}
GH_INLINE void GH_TIMER_set_Control_Enable1(U8 data)
{
    GH_TIMER_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL_REAL;
    d.bitc.enable1 = data;
    *(volatile U32 *)REG_TIMER_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_TIMER_get_Control_Enable1(void)
{
    GH_TIMER_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.enable1;
}
GH_INLINE void GH_TIMER_set_Control_ClkSel1(U8 data)
{
    GH_TIMER_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL_REAL;
    d.bitc.clksel1 = data;
    *(volatile U32 *)REG_TIMER_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_TIMER_get_Control_ClkSel1(void)
{
    GH_TIMER_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.clksel1;
}
GH_INLINE void GH_TIMER_set_Control_OF1(U8 data)
{
    GH_TIMER_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL_REAL;
    d.bitc.of1 = data;
    *(volatile U32 *)REG_TIMER_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_TIMER_get_Control_OF1(void)
{
    GH_TIMER_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.of1;
}
GH_INLINE void GH_TIMER_set_Control_Enable2(U8 data)
{
    GH_TIMER_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL_REAL;
    d.bitc.enable2 = data;
    *(volatile U32 *)REG_TIMER_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_TIMER_get_Control_Enable2(void)
{
    GH_TIMER_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.enable2;
}
GH_INLINE void GH_TIMER_set_Control_ClkSel2(U8 data)
{
    GH_TIMER_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL_REAL;
    d.bitc.clksel2 = data;
    *(volatile U32 *)REG_TIMER_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_TIMER_get_Control_ClkSel2(void)
{
    GH_TIMER_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.clksel2;
}
GH_INLINE void GH_TIMER_set_Control_OF2(U8 data)
{
    GH_TIMER_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL_REAL;
    d.bitc.of2 = data;
    *(volatile U32 *)REG_TIMER_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_TIMER_get_Control_OF2(void)
{
    GH_TIMER_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.of2;
}
GH_INLINE void GH_TIMER_set_Control_Enable3(U8 data)
{
    GH_TIMER_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL_REAL;
    d.bitc.enable3 = data;
    *(volatile U32 *)REG_TIMER_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_TIMER_get_Control_Enable3(void)
{
    GH_TIMER_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.enable3;
}
GH_INLINE void GH_TIMER_set_Control_ClkSel3(U8 data)
{
    GH_TIMER_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL_REAL;
    d.bitc.clksel3 = data;
    *(volatile U32 *)REG_TIMER_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_TIMER_get_Control_ClkSel3(void)
{
    GH_TIMER_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.clksel3;
}
GH_INLINE void GH_TIMER_set_Control_OF3(U8 data)
{
    GH_TIMER_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL_REAL;
    d.bitc.of3 = data;
    *(volatile U32 *)REG_TIMER_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_TIMER_get_Control_OF3(void)
{
    GH_TIMER_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.of3;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_TIMER_init(void)
{
    int i;

    for (i=0; i<3; i++)
    {
        GH_TIMER_set_CntnSts(i, (U32)0x00000000);
    }
    for (i=0; i<3; i++)
    {
        GH_TIMER_set_Reloadn(i, (U32)0x00000000);
    }
    for (i=0; i<3; i++)
    {
        GH_TIMER_set_Match1(i, (U32)0x00000000);
    }
    for (i=0; i<3; i++)
    {
        GH_TIMER_set_Match2(i, (U32)0x00000000);
    }
    GH_TIMER_set_Control((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

