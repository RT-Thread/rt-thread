/******************************************************************************
**
** \file      gh_i2c.c
**
** \brief     I2C Interface..
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
#include "gh_i2c.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_I2C_ENABLE_REAL                                 FIO_ADDRESS(I2C,0x70003000) /* read/write */
#define REG_I2C_CONTROL_REAL                                FIO_ADDRESS(I2C,0x70003004) /* read/write */
#define REG_I2C_DATA_REAL                                   FIO_ADDRESS(I2C,0x70003008) /* read/write */
#define REG_I2C_STATUS_REAL                                 FIO_ADDRESS(I2C,0x7000300C) /* read */
#define REG_I2C_PRESCALEL_REAL                              FIO_ADDRESS(I2C,0x70003010) /* read/write */
#define REG_I2C_PRESCALEH_REAL                              FIO_ADDRESS(I2C,0x70003014) /* read/write */
#define REG_I2C_FMCONTROL_REAL                              FIO_ADDRESS(I2C,0x70003018) /* read/write */
#define REG_I2C_FMDATA_REAL                                 FIO_ADDRESS(I2C,0x7000301C) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* I2C_ENABLE */
    U32 all;
    struct {
        U32 en                          : 1;
        U32                             : 31;
    } bitc;
} GH_I2C_ENABLE_REAL_S;

typedef union { /* I2C_CONTROL */
    U32 all;
    struct {
        U32 ack                         : 1;
        U32 intflag                     : 1;
        U32 start                       : 1;
        U32 stop                        : 1;
        U32                             : 28;
    } bitc;
} GH_I2C_CONTROL_REAL_S;

typedef union { /* I2C_DATA */
    U32 all;
    struct {
        U32 data                        : 8;
        U32                             : 24;
    } bitc;
} GH_I2C_DATA_REAL_S;

typedef union { /* I2C_STATUS */
    U32 all;
    struct {
        U32 mode                        : 1;
        U32                             : 31;
    } bitc;
} GH_I2C_STATUS_REAL_S;

typedef union { /* I2C_PRESCALEL */
    U32 all;
    struct {
        U32 scale                       : 8;
        U32                             : 24;
    } bitc;
} GH_I2C_PRESCALEL_REAL_S;

typedef union { /* I2C_PRESCALEH */
    U32 all;
    struct {
        U32 scale                       : 8;
        U32                             : 24;
    } bitc;
} GH_I2C_PRESCALEH_REAL_S;

typedef union { /* I2C_FMCONTROL */
    U32 all;
    struct {
        U32                             : 1;
        U32 is                          : 1;
        U32 start                       : 1;
        U32 stop                        : 1;
        U32                             : 28;
    } bitc;
} GH_I2C_FMCONTROL_REAL_S;

typedef union { /* I2C_FMDATA */
    U32 all;
    struct {
        U32 data                        : 8;
        U32                             : 24;
    } bitc;
} GH_I2C_FMDATA_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register I2C_ENABLE (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2C_set_ENABLE(U8 index, U32 data)
{
    GH_I2C_ENABLE_REAL_S real;
    GH_I2C_ENABLE_S dummy;
    dummy.all = data ;
    real.bitc.en = dummy.bitc.en;
    *(volatile U32 *)(REG_I2C_ENABLE_REAL + index * FIO_MOFFSET(I2C,0x00004000)) = real.all;
}
GH_INLINE U32  GH_I2C_get_ENABLE(U8 index)
{
    GH_I2C_ENABLE_REAL_S real;
    GH_I2C_ENABLE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_I2C_ENABLE_REAL + index * FIO_MOFFSET(I2C,0x00004000)));

    dummy.bitc.en = real.bitc.en;
    return dummy.all;
}
GH_INLINE void GH_I2C_set_ENABLE_en(U8 index, U8 data)
{
    GH_I2C_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)(REG_I2C_ENABLE_REAL + index * FIO_MOFFSET(I2C,0x00004000));
    d.bitc.en = data;
    *(volatile U32 *)(REG_I2C_ENABLE_REAL + index * FIO_MOFFSET(I2C,0x00004000)) = d.all;
}
GH_INLINE U8   GH_I2C_get_ENABLE_en(U8 index)
{
    GH_I2C_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_ENABLE_REAL + index * FIO_MOFFSET(I2C,0x00004000)));

    tmp_value.all = value;
    return tmp_value.bitc.en;
}

/*----------------------------------------------------------------------------*/
/* register I2C_CONTROL (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2C_set_CONTROL(U8 index, U32 data)
{
    GH_I2C_CONTROL_REAL_S real;
    GH_I2C_CONTROL_S dummy;
    dummy.all = data ;
    real.bitc.ack = dummy.bitc.ack;
    real.bitc.intflag = dummy.bitc.intflag;
    real.bitc.start = dummy.bitc.start;
    real.bitc.stop = dummy.bitc.stop;
    *(volatile U32 *)(REG_I2C_CONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000)) = real.all;
}
GH_INLINE U32  GH_I2C_get_CONTROL(U8 index)
{
    GH_I2C_CONTROL_REAL_S real;
    GH_I2C_CONTROL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_I2C_CONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000)));

    dummy.bitc.ack = real.bitc.ack;
    dummy.bitc.intflag = real.bitc.intflag;
    dummy.bitc.start = real.bitc.start;
    dummy.bitc.stop = real.bitc.stop;
    return dummy.all;
}
GH_INLINE void GH_I2C_set_CONTROL_ack(U8 index, U8 data)
{
    GH_I2C_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)(REG_I2C_CONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000));
    d.bitc.ack = data;
    *(volatile U32 *)(REG_I2C_CONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000)) = d.all;
}
GH_INLINE U8   GH_I2C_get_CONTROL_ack(U8 index)
{
    GH_I2C_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_CONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000)));

    tmp_value.all = value;
    return tmp_value.bitc.ack;
}
GH_INLINE void GH_I2C_set_CONTROL_IntFlag(U8 index, U8 data)
{
    GH_I2C_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)(REG_I2C_CONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000));
    d.bitc.intflag = data;
    *(volatile U32 *)(REG_I2C_CONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000)) = d.all;
}
GH_INLINE U8   GH_I2C_get_CONTROL_IntFlag(U8 index)
{
    GH_I2C_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_CONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000)));

    tmp_value.all = value;
    return tmp_value.bitc.intflag;
}
GH_INLINE void GH_I2C_set_CONTROL_start(U8 index, U8 data)
{
    GH_I2C_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)(REG_I2C_CONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000));
    d.bitc.start = data;
    *(volatile U32 *)(REG_I2C_CONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000)) = d.all;
}
GH_INLINE U8   GH_I2C_get_CONTROL_start(U8 index)
{
    GH_I2C_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_CONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000)));

    tmp_value.all = value;
    return tmp_value.bitc.start;
}
GH_INLINE void GH_I2C_set_CONTROL_stop(U8 index, U8 data)
{
    GH_I2C_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)(REG_I2C_CONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000));
    d.bitc.stop = data;
    *(volatile U32 *)(REG_I2C_CONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000)) = d.all;
}
GH_INLINE U8   GH_I2C_get_CONTROL_stop(U8 index)
{
    GH_I2C_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_CONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000)));

    tmp_value.all = value;
    return tmp_value.bitc.stop;
}

/*----------------------------------------------------------------------------*/
/* register I2C_DATA (read/write)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2C_set_DATA(U8 index, U32 data)
{
    GH_I2C_DATA_REAL_S real;
    GH_I2C_DATA_S dummy;
    dummy.all = data ;
    real.bitc.data = dummy.bitc.data;
    *(volatile U32 *)(REG_I2C_DATA_REAL + index * FIO_MOFFSET(I2C,0x00004000)) = real.all;
}
GH_INLINE U32  GH_I2C_get_DATA(U8 index)
{
    GH_I2C_DATA_REAL_S real;
    GH_I2C_DATA_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_I2C_DATA_REAL + index * FIO_MOFFSET(I2C,0x00004000)));

    dummy.bitc.data = real.bitc.data;
    return dummy.all;
}
GH_INLINE void GH_I2C_set_DATA_Data(U8 index, U8 data)
{
    GH_I2C_DATA_REAL_S d;
    d.all = *(volatile U32 *)(REG_I2C_DATA_REAL + index * FIO_MOFFSET(I2C,0x00004000));
    d.bitc.data = data;
    *(volatile U32 *)(REG_I2C_DATA_REAL + index * FIO_MOFFSET(I2C,0x00004000)) = d.all;
}
GH_INLINE U8   GH_I2C_get_DATA_Data(U8 index)
{
    GH_I2C_DATA_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_DATA_REAL + index * FIO_MOFFSET(I2C,0x00004000)));

    tmp_value.all = value;
    return tmp_value.bitc.data;
}

/*----------------------------------------------------------------------------*/
/* register I2C_STATUS (read)                                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_I2C_get_STATUS(U8 index)
{
    GH_I2C_STATUS_REAL_S real;
    GH_I2C_STATUS_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_I2C_STATUS_REAL + index * FIO_MOFFSET(I2C,0x00004000)));

    dummy.bitc.mode = real.bitc.mode;
    return dummy.all;
}
GH_INLINE U8   GH_I2C_get_STATUS_mode(U8 index)
{
    GH_I2C_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_STATUS_REAL + index * FIO_MOFFSET(I2C,0x00004000)));

    tmp_value.all = value;
    return tmp_value.bitc.mode;
}

/*----------------------------------------------------------------------------*/
/* register I2C_PRESCALEL (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2C_set_PRESCALEL(U8 index, U32 data)
{
    GH_I2C_PRESCALEL_REAL_S real;
    GH_I2C_PRESCALEL_S dummy;
    dummy.all = data ;
    real.bitc.scale = dummy.bitc.scale;
    *(volatile U32 *)(REG_I2C_PRESCALEL_REAL + index * FIO_MOFFSET(I2C,0x00004000)) = real.all;
}
GH_INLINE U32  GH_I2C_get_PRESCALEL(U8 index)
{
    GH_I2C_PRESCALEL_REAL_S real;
    GH_I2C_PRESCALEL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_I2C_PRESCALEL_REAL + index * FIO_MOFFSET(I2C,0x00004000)));

    dummy.bitc.scale = real.bitc.scale;
    return dummy.all;
}
GH_INLINE void GH_I2C_set_PRESCALEL_scale(U8 index, U8 data)
{
    GH_I2C_PRESCALEL_REAL_S d;
    d.all = *(volatile U32 *)(REG_I2C_PRESCALEL_REAL + index * FIO_MOFFSET(I2C,0x00004000));
    d.bitc.scale = data;
    *(volatile U32 *)(REG_I2C_PRESCALEL_REAL + index * FIO_MOFFSET(I2C,0x00004000)) = d.all;
}
GH_INLINE U8   GH_I2C_get_PRESCALEL_scale(U8 index)
{
    GH_I2C_PRESCALEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_PRESCALEL_REAL + index * FIO_MOFFSET(I2C,0x00004000)));

    tmp_value.all = value;
    return tmp_value.bitc.scale;
}

/*----------------------------------------------------------------------------*/
/* register I2C_PRESCALEH (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2C_set_PRESCALEH(U8 index, U32 data)
{
    GH_I2C_PRESCALEH_REAL_S real;
    GH_I2C_PRESCALEH_S dummy;
    dummy.all = data ;
    real.bitc.scale = dummy.bitc.scale;
    *(volatile U32 *)(REG_I2C_PRESCALEH_REAL + index * FIO_MOFFSET(I2C,0x00004000)) = real.all;
}
GH_INLINE U32  GH_I2C_get_PRESCALEH(U8 index)
{
    GH_I2C_PRESCALEH_REAL_S real;
    GH_I2C_PRESCALEH_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_I2C_PRESCALEH_REAL + index * FIO_MOFFSET(I2C,0x00004000)));

    dummy.bitc.scale = real.bitc.scale;
    return dummy.all;
}
GH_INLINE void GH_I2C_set_PRESCALEH_scale(U8 index, U8 data)
{
    GH_I2C_PRESCALEH_REAL_S d;
    d.all = *(volatile U32 *)(REG_I2C_PRESCALEH_REAL + index * FIO_MOFFSET(I2C,0x00004000));
    d.bitc.scale = data;
    *(volatile U32 *)(REG_I2C_PRESCALEH_REAL + index * FIO_MOFFSET(I2C,0x00004000)) = d.all;
}
GH_INLINE U8   GH_I2C_get_PRESCALEH_scale(U8 index)
{
    GH_I2C_PRESCALEH_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_PRESCALEH_REAL + index * FIO_MOFFSET(I2C,0x00004000)));

    tmp_value.all = value;
    return tmp_value.bitc.scale;
}

/*----------------------------------------------------------------------------*/
/* register I2C_FMCONTROL (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2C_set_FMCONTROL(U8 index, U32 data)
{
    GH_I2C_FMCONTROL_REAL_S real;
    GH_I2C_FMCONTROL_S dummy;
    dummy.all = data ;
    real.bitc.is = dummy.bitc.is;
    real.bitc.start = dummy.bitc.start;
    real.bitc.stop = dummy.bitc.stop;
    *(volatile U32 *)(REG_I2C_FMCONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000)) = real.all;
}
GH_INLINE U32  GH_I2C_get_FMCONTROL(U8 index)
{
    GH_I2C_FMCONTROL_REAL_S real;
    GH_I2C_FMCONTROL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_I2C_FMCONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000)));

    dummy.bitc.is = real.bitc.is;
    dummy.bitc.start = real.bitc.start;
    dummy.bitc.stop = real.bitc.stop;
    return dummy.all;
}
GH_INLINE void GH_I2C_set_FMCONTROL_is(U8 index, U8 data)
{
    GH_I2C_FMCONTROL_REAL_S d;
    d.all = *(volatile U32 *)(REG_I2C_FMCONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000));
    d.bitc.is = data;
    *(volatile U32 *)(REG_I2C_FMCONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000)) = d.all;
}
GH_INLINE U8   GH_I2C_get_FMCONTROL_is(U8 index)
{
    GH_I2C_FMCONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_FMCONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000)));

    tmp_value.all = value;
    return tmp_value.bitc.is;
}
GH_INLINE void GH_I2C_set_FMCONTROL_start(U8 index, U8 data)
{
    GH_I2C_FMCONTROL_REAL_S d;
    d.all = *(volatile U32 *)(REG_I2C_FMCONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000));
    d.bitc.start = data;
    *(volatile U32 *)(REG_I2C_FMCONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000)) = d.all;
}
GH_INLINE U8   GH_I2C_get_FMCONTROL_start(U8 index)
{
    GH_I2C_FMCONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_FMCONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000)));

    tmp_value.all = value;
    return tmp_value.bitc.start;
}
GH_INLINE void GH_I2C_set_FMCONTROL_stop(U8 index, U8 data)
{
    GH_I2C_FMCONTROL_REAL_S d;
    d.all = *(volatile U32 *)(REG_I2C_FMCONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000));
    d.bitc.stop = data;
    *(volatile U32 *)(REG_I2C_FMCONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000)) = d.all;
}
GH_INLINE U8   GH_I2C_get_FMCONTROL_stop(U8 index)
{
    GH_I2C_FMCONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_FMCONTROL_REAL + index * FIO_MOFFSET(I2C,0x00004000)));

    tmp_value.all = value;
    return tmp_value.bitc.stop;
}

/*----------------------------------------------------------------------------*/
/* register I2C_FMDATA (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2C_set_FMDATA(U8 index, U32 data)
{
    GH_I2C_FMDATA_REAL_S real;
    GH_I2C_FMDATA_S dummy;
    dummy.all = data ;
    real.bitc.data = dummy.bitc.data;
    *(volatile U32 *)(REG_I2C_FMDATA_REAL + index * FIO_MOFFSET(I2C,0x00004000)) = real.all;
}
GH_INLINE U32  GH_I2C_get_FMDATA(U8 index)
{
    GH_I2C_FMDATA_REAL_S real;
    GH_I2C_FMDATA_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_I2C_FMDATA_REAL + index * FIO_MOFFSET(I2C,0x00004000)));

    dummy.bitc.data = real.bitc.data;
    return dummy.all;
}
GH_INLINE void GH_I2C_set_FMDATA_Data(U8 index, U8 data)
{
    GH_I2C_FMDATA_REAL_S d;
    d.all = *(volatile U32 *)(REG_I2C_FMDATA_REAL + index * FIO_MOFFSET(I2C,0x00004000));
    d.bitc.data = data;
    *(volatile U32 *)(REG_I2C_FMDATA_REAL + index * FIO_MOFFSET(I2C,0x00004000)) = d.all;
}
GH_INLINE U8   GH_I2C_get_FMDATA_Data(U8 index)
{
    GH_I2C_FMDATA_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_FMDATA_REAL + index * FIO_MOFFSET(I2C,0x00004000)));

    tmp_value.all = value;
    return tmp_value.bitc.data;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2C_init(void)
{
    int i;

    for (i=0; i<2; i++)
    {
        GH_I2C_set_ENABLE(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_I2C_set_CONTROL(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_I2C_set_DATA(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_I2C_set_PRESCALEL(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_I2C_set_PRESCALEH(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_I2C_set_FMCONTROL(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_I2C_set_FMDATA(i, (U32)0x00000000);
    }
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

