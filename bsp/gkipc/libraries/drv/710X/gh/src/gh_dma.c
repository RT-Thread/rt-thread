/******************************************************************************
**
** \file      gh_dma.c
**
** \brief     DMA Engine Subsystem.
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
#include "gh_dma.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_DMA_CONTROL_REAL                                FIO_ADDRESS(DMA,0x60005300) /* read/write */
#define REG_DMA_SOURCE_ADDRESS_REAL                         FIO_ADDRESS(DMA,0x60005304) /* read/write */
#define REG_DMA_DESTINATION_ADDRESS_REAL                    FIO_ADDRESS(DMA,0x60005308) /* read/write */
#define REG_DMA_STATUS_REAL                                 FIO_ADDRESS(DMA,0x6000530C) /* read/write */
#define REG_DMA_DESCRIPTOR_ADDRESS_REAL                     FIO_ADDRESS(DMA,0x60005380) /* read/write */
#define REG_DMA_IR_REAL                                     FIO_ADDRESS(DMA,0x600053F0) /* read */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* DMA_Control */
    U32 all;
    struct {
        U32 count                       : 22;
        U32 ts                          : 2;
        U32 blk                         : 3;
        U32 ni                          : 1;
        U32 rm                          : 1;
        U32 wm                          : 1;
        U32 d                           : 1;
        U32 en                          : 1;
    } bitc;
} GH_DMA_CONTROL_REAL_S;

typedef union { /* DMA_Status */
    U32 all;
    struct {
        U32 count                       : 22;
        U32 dn                          : 1;
        U32 ae                          : 1;
        U32 rwe                         : 1;
        U32 be                          : 1;
        U32 me                          : 1;
        U32 od                          : 1;
        U32 dd                          : 1;
        U32 da                          : 1;
        U32 oe                          : 1;
        U32 dm                          : 1;
    } bitc;
} GH_DMA_STATUS_REAL_S;

typedef union { /* DMA_IR */
    U32 all;
    struct {
        U32 i0                          : 1;
        U32 i1                          : 1;
        U32 i2                          : 1;
        U32 i3                          : 1;
        U32                             : 28;
    } bitc;
} GH_DMA_IR_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register DMA_Control (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DMA_set_Control(U8 index, U32 data)
{
    GH_DMA_CONTROL_REAL_S real;
    GH_DMA_CONTROL_S dummy;
    dummy.all = data ;
    real.bitc.count = dummy.bitc.count;
    real.bitc.ts = dummy.bitc.ts;
    real.bitc.blk = dummy.bitc.blk;
    real.bitc.ni = dummy.bitc.ni;
    real.bitc.rm = dummy.bitc.rm;
    real.bitc.wm = dummy.bitc.wm;
    real.bitc.d = dummy.bitc.d;
    real.bitc.en = dummy.bitc.en;
    *(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = real.all;
}
GH_INLINE U32  GH_DMA_get_Control(U8 index)
{
    GH_DMA_CONTROL_REAL_S real;
    GH_DMA_CONTROL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    dummy.bitc.count = real.bitc.count;
    dummy.bitc.ts = real.bitc.ts;
    dummy.bitc.blk = real.bitc.blk;
    dummy.bitc.ni = real.bitc.ni;
    dummy.bitc.rm = real.bitc.rm;
    dummy.bitc.wm = real.bitc.wm;
    dummy.bitc.d = real.bitc.d;
    dummy.bitc.en = real.bitc.en;
    return dummy.all;
}
GH_INLINE void GH_DMA_set_Control_count(U8 index, U32 data)
{
    GH_DMA_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.count = data;
    *(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
}
GH_INLINE U32  GH_DMA_get_Control_count(U8 index)
{
    GH_DMA_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    return tmp_value.bitc.count;
}
GH_INLINE void GH_DMA_set_Control_ts(U8 index, U8 data)
{
    GH_DMA_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.ts = data;
    *(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
}
GH_INLINE U8   GH_DMA_get_Control_ts(U8 index)
{
    GH_DMA_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    return tmp_value.bitc.ts;
}
GH_INLINE void GH_DMA_set_Control_blk(U8 index, U8 data)
{
    GH_DMA_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.blk = data;
    *(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
}
GH_INLINE U8   GH_DMA_get_Control_blk(U8 index)
{
    GH_DMA_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    return tmp_value.bitc.blk;
}
GH_INLINE void GH_DMA_set_Control_ni(U8 index, U8 data)
{
    GH_DMA_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.ni = data;
    *(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
}
GH_INLINE U8   GH_DMA_get_Control_ni(U8 index)
{
    GH_DMA_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    return tmp_value.bitc.ni;
}
GH_INLINE void GH_DMA_set_Control_rm(U8 index, U8 data)
{
    GH_DMA_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.rm = data;
    *(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
}
GH_INLINE U8   GH_DMA_get_Control_rm(U8 index)
{
    GH_DMA_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    return tmp_value.bitc.rm;
}
GH_INLINE void GH_DMA_set_Control_wm(U8 index, U8 data)
{
    GH_DMA_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.wm = data;
    *(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
}
GH_INLINE U8   GH_DMA_get_Control_wm(U8 index)
{
    GH_DMA_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    return tmp_value.bitc.wm;
}
GH_INLINE void GH_DMA_set_Control_d(U8 index, U8 data)
{
    GH_DMA_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.d = data;
    *(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
}
GH_INLINE U8   GH_DMA_get_Control_d(U8 index)
{
    GH_DMA_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    return tmp_value.bitc.d;
}
GH_INLINE void GH_DMA_set_Control_en(U8 index, U8 data)
{
    GH_DMA_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.en = data;
    *(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
}
GH_INLINE U8   GH_DMA_get_Control_en(U8 index)
{
    GH_DMA_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_CONTROL_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    return tmp_value.bitc.en;
}

/*----------------------------------------------------------------------------*/
/* register DMA_Source_Address (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DMA_set_Source_Address(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DMA_SOURCE_ADDRESS_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = data;
}
GH_INLINE U32  GH_DMA_get_Source_Address(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DMA_SOURCE_ADDRESS_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DMA_Destination_Address (read/write)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DMA_set_Destination_Address(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DMA_DESTINATION_ADDRESS_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = data;
}
GH_INLINE U32  GH_DMA_get_Destination_Address(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DMA_DESTINATION_ADDRESS_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DMA_Status (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DMA_set_Status(U8 index, U32 data)
{
    GH_DMA_STATUS_REAL_S real;
    GH_DMA_STATUS_S dummy;
    dummy.all = data ;
    real.bitc.count = dummy.bitc.count;
    real.bitc.dn = dummy.bitc.dn;
    real.bitc.ae = dummy.bitc.ae;
    real.bitc.rwe = dummy.bitc.rwe;
    real.bitc.be = dummy.bitc.be;
    real.bitc.me = dummy.bitc.me;
    real.bitc.od = dummy.bitc.od;
    real.bitc.dd = dummy.bitc.dd;
    real.bitc.da = dummy.bitc.da;
    real.bitc.oe = dummy.bitc.oe;
    real.bitc.dm = dummy.bitc.dm;
    *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = real.all;
}
GH_INLINE U32  GH_DMA_get_Status(U8 index)
{
    GH_DMA_STATUS_REAL_S real;
    GH_DMA_STATUS_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    dummy.bitc.count = real.bitc.count;
    dummy.bitc.dn = real.bitc.dn;
    dummy.bitc.ae = real.bitc.ae;
    dummy.bitc.rwe = real.bitc.rwe;
    dummy.bitc.be = real.bitc.be;
    dummy.bitc.me = real.bitc.me;
    dummy.bitc.od = real.bitc.od;
    dummy.bitc.dd = real.bitc.dd;
    dummy.bitc.da = real.bitc.da;
    dummy.bitc.oe = real.bitc.oe;
    dummy.bitc.dm = real.bitc.dm;
    return dummy.all;
}
GH_INLINE void GH_DMA_set_Status_count(U8 index, U32 data)
{
    GH_DMA_STATUS_REAL_S d;
    d.all = *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.count = data;
    *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
}
GH_INLINE U32  GH_DMA_get_Status_count(U8 index)
{
    GH_DMA_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    return tmp_value.bitc.count;
}
GH_INLINE void GH_DMA_set_Status_dn(U8 index, U8 data)
{
    GH_DMA_STATUS_REAL_S d;
    d.all = *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.dn = data;
    *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
}
GH_INLINE U8   GH_DMA_get_Status_dn(U8 index)
{
    GH_DMA_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    return tmp_value.bitc.dn;
}
GH_INLINE void GH_DMA_set_Status_ae(U8 index, U8 data)
{
    GH_DMA_STATUS_REAL_S d;
    d.all = *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.ae = data;
    *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
}
GH_INLINE U8   GH_DMA_get_Status_ae(U8 index)
{
    GH_DMA_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    return tmp_value.bitc.ae;
}
GH_INLINE void GH_DMA_set_Status_rwe(U8 index, U8 data)
{
    GH_DMA_STATUS_REAL_S d;
    d.all = *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.rwe = data;
    *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
}
GH_INLINE U8   GH_DMA_get_Status_rwe(U8 index)
{
    GH_DMA_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    return tmp_value.bitc.rwe;
}
GH_INLINE void GH_DMA_set_Status_be(U8 index, U8 data)
{
    GH_DMA_STATUS_REAL_S d;
    d.all = *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.be = data;
    *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
}
GH_INLINE U8   GH_DMA_get_Status_be(U8 index)
{
    GH_DMA_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    return tmp_value.bitc.be;
}
GH_INLINE void GH_DMA_set_Status_me(U8 index, U8 data)
{
    GH_DMA_STATUS_REAL_S d;
    d.all = *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.me = data;
    *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
}
GH_INLINE U8   GH_DMA_get_Status_me(U8 index)
{
    GH_DMA_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    return tmp_value.bitc.me;
}
GH_INLINE void GH_DMA_set_Status_od(U8 index, U8 data)
{
    GH_DMA_STATUS_REAL_S d;
    d.all = *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.od = data;
    *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
}
GH_INLINE U8   GH_DMA_get_Status_od(U8 index)
{
    GH_DMA_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    return tmp_value.bitc.od;
}
GH_INLINE void GH_DMA_set_Status_dd(U8 index, U8 data)
{
    GH_DMA_STATUS_REAL_S d;
    d.all = *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.dd = data;
    *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
}
GH_INLINE U8   GH_DMA_get_Status_dd(U8 index)
{
    GH_DMA_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    return tmp_value.bitc.dd;
}
GH_INLINE void GH_DMA_set_Status_da(U8 index, U8 data)
{
    GH_DMA_STATUS_REAL_S d;
    d.all = *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.da = data;
    *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
}
GH_INLINE U8   GH_DMA_get_Status_da(U8 index)
{
    GH_DMA_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    return tmp_value.bitc.da;
}
GH_INLINE void GH_DMA_set_Status_oe(U8 index, U8 data)
{
    GH_DMA_STATUS_REAL_S d;
    d.all = *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.oe = data;
    *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
}
GH_INLINE U8   GH_DMA_get_Status_oe(U8 index)
{
    GH_DMA_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    return tmp_value.bitc.oe;
}
GH_INLINE void GH_DMA_set_Status_dm(U8 index, U8 data)
{
    GH_DMA_STATUS_REAL_S d;
    d.all = *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.dm = data;
    *(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
}
GH_INLINE U8   GH_DMA_get_Status_dm(U8 index)
{
    GH_DMA_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS_REAL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    return tmp_value.bitc.dm;
}

/*----------------------------------------------------------------------------*/
/* register DMA_Descriptor_Address (read/write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DMA_set_Descriptor_Address(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DMA_DESCRIPTOR_ADDRESS_REAL + index * FIO_MOFFSET(DMA,0x00000004)) = data;
}
GH_INLINE U32  GH_DMA_get_Descriptor_Address(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DMA_DESCRIPTOR_ADDRESS_REAL + index * FIO_MOFFSET(DMA,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DMA_IR (read)                                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DMA_get_IR(void)
{
    GH_DMA_IR_REAL_S real;
    GH_DMA_IR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DMA_IR_REAL);

    dummy.bitc.i0 = real.bitc.i0;
    dummy.bitc.i1 = real.bitc.i1;
    dummy.bitc.i2 = real.bitc.i2;
    dummy.bitc.i3 = real.bitc.i3;
    return dummy.all;
}
GH_INLINE U8   GH_DMA_get_IR_i0(void)
{
    GH_DMA_IR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DMA_IR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.i0;
}
GH_INLINE U8   GH_DMA_get_IR_i1(void)
{
    GH_DMA_IR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DMA_IR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.i1;
}
GH_INLINE U8   GH_DMA_get_IR_i2(void)
{
    GH_DMA_IR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DMA_IR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.i2;
}
GH_INLINE U8   GH_DMA_get_IR_i3(void)
{
    GH_DMA_IR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DMA_IR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.i3;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DMA_init(void)
{
    int i;

    for (i=0; i<4; i++)
    {
        GH_DMA_set_Control(i, (U32)0x38000000);
    }
    for (i=0; i<4; i++)
    {
        GH_DMA_set_Source_Address(i, (U32)0x00000000);
    }
    for (i=0; i<4; i++)
    {
        GH_DMA_set_Destination_Address(i, (U32)0x00000000);
    }
    for (i=0; i<4; i++)
    {
        GH_DMA_set_Status(i, (U32)0x00000000);
    }
    for (i=0; i<4; i++)
    {
        GH_DMA_set_Descriptor_Address(i, (U32)0x00000000);
    }
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

