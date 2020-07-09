/******************************************************************************
**
** \file      gh_sflash.c
**
** \brief     Serial Flash Interface.
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
#include "gh_sflash.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_SFLASH_DATA_REAL                                FIO_ADDRESS(SFLASH,0x60016000) /* read/write */
#define REG_SFLASH_COMMAND_REAL                             FIO_ADDRESS(SFLASH,0x60016004) /* read/write */
#define REG_SFLASH_CE_REAL                                  FIO_ADDRESS(SFLASH,0x60016008) /* read/write */
#define REG_SFLASH_SPEED_REAL                               FIO_ADDRESS(SFLASH,0x6001600C) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* SFLASH_Command */
    U32 all;
    struct {
        U32 code                        : 8;
        U32 sendcmd                     : 1;
        U32 adrnum                      : 3;
        U32 dummynum                    : 3;
        U32 rwn                         : 2;
        U32 cmdmode                     : 2;
        U32 adrmode                     : 2;
        U32 datamode                    : 2;
        U32 datanum                     : 5;
        U32 holdtime                    : 2;
        U32                             : 2;
    } bitc;
} GH_SFLASH_COMMAND_REAL_S;

typedef union { /* SFLASH_CE */
    U32 all;
    struct {
        U32 ce                          : 1;
        U32 wp                          : 1;
        U32 hold                        : 1;
        U32 cemode                      : 1;
        U32 wpmode                      : 1;
        U32 holdmode                    : 1;
        U32 chselect                    : 1;
        U32                             : 25;
    } bitc;
} GH_SFLASH_CE_REAL_S;

typedef union { /* SFLASH_Speed */
    U32 all;
    struct {
        U32 sf_sclk_sel                 : 3;
        U32                             : 29;
    } bitc;
} GH_SFLASH_SPEED_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register SFLASH_Data (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SFLASH_set_Data(U32 data)
{
    *(volatile U32 *)REG_SFLASH_DATA_REAL = data;
}
GH_INLINE U32  GH_SFLASH_get_Data(void)
{
    U32 value = (*(volatile U32 *)REG_SFLASH_DATA_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register SFLASH_Command (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SFLASH_set_Command(U32 data)
{
    GH_SFLASH_COMMAND_REAL_S real;
    GH_SFLASH_COMMAND_S dummy;
    dummy.all = data ;
    real.bitc.code = dummy.bitc.code;
    real.bitc.sendcmd = dummy.bitc.sendcmd;
    real.bitc.adrnum = dummy.bitc.adrnum;
    real.bitc.dummynum = dummy.bitc.dummynum;
    real.bitc.rwn = dummy.bitc.rwn;
    real.bitc.cmdmode = dummy.bitc.cmdmode;
    real.bitc.adrmode = dummy.bitc.adrmode;
    real.bitc.datamode = dummy.bitc.datamode;
    real.bitc.datanum = dummy.bitc.datanum;
    real.bitc.holdtime = dummy.bitc.holdtime;
    *(volatile U32 *)REG_SFLASH_COMMAND_REAL = real.all;
}
GH_INLINE U32  GH_SFLASH_get_Command(void)
{
    GH_SFLASH_COMMAND_REAL_S real;
    GH_SFLASH_COMMAND_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SFLASH_COMMAND_REAL);

    dummy.bitc.code = real.bitc.code;
    dummy.bitc.sendcmd = real.bitc.sendcmd;
    dummy.bitc.adrnum = real.bitc.adrnum;
    dummy.bitc.dummynum = real.bitc.dummynum;
    dummy.bitc.rwn = real.bitc.rwn;
    dummy.bitc.cmdmode = real.bitc.cmdmode;
    dummy.bitc.adrmode = real.bitc.adrmode;
    dummy.bitc.datamode = real.bitc.datamode;
    dummy.bitc.datanum = real.bitc.datanum;
    dummy.bitc.holdtime = real.bitc.holdtime;
    return dummy.all;
}
GH_INLINE void GH_SFLASH_set_Command_CODE(U8 data)
{
    GH_SFLASH_COMMAND_REAL_S d;
    d.all = *(volatile U32 *)REG_SFLASH_COMMAND_REAL;
    d.bitc.code = data;
    *(volatile U32 *)REG_SFLASH_COMMAND_REAL = d.all;
}
GH_INLINE U8   GH_SFLASH_get_Command_CODE(void)
{
    GH_SFLASH_COMMAND_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_COMMAND_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.code;
}
GH_INLINE void GH_SFLASH_set_Command_SENDCMD(U8 data)
{
    GH_SFLASH_COMMAND_REAL_S d;
    d.all = *(volatile U32 *)REG_SFLASH_COMMAND_REAL;
    d.bitc.sendcmd = data;
    *(volatile U32 *)REG_SFLASH_COMMAND_REAL = d.all;
}
GH_INLINE U8   GH_SFLASH_get_Command_SENDCMD(void)
{
    GH_SFLASH_COMMAND_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_COMMAND_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sendcmd;
}
GH_INLINE void GH_SFLASH_set_Command_ADRNUM(U8 data)
{
    GH_SFLASH_COMMAND_REAL_S d;
    d.all = *(volatile U32 *)REG_SFLASH_COMMAND_REAL;
    d.bitc.adrnum = data;
    *(volatile U32 *)REG_SFLASH_COMMAND_REAL = d.all;
}
GH_INLINE U8   GH_SFLASH_get_Command_ADRNUM(void)
{
    GH_SFLASH_COMMAND_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_COMMAND_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adrnum;
}
GH_INLINE void GH_SFLASH_set_Command_DUMMYNUM(U8 data)
{
    GH_SFLASH_COMMAND_REAL_S d;
    d.all = *(volatile U32 *)REG_SFLASH_COMMAND_REAL;
    d.bitc.dummynum = data;
    *(volatile U32 *)REG_SFLASH_COMMAND_REAL = d.all;
}
GH_INLINE U8   GH_SFLASH_get_Command_DUMMYNUM(void)
{
    GH_SFLASH_COMMAND_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_COMMAND_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dummynum;
}
GH_INLINE void GH_SFLASH_set_Command_RWN(U8 data)
{
    GH_SFLASH_COMMAND_REAL_S d;
    d.all = *(volatile U32 *)REG_SFLASH_COMMAND_REAL;
    d.bitc.rwn = data;
    *(volatile U32 *)REG_SFLASH_COMMAND_REAL = d.all;
}
GH_INLINE U8   GH_SFLASH_get_Command_RWN(void)
{
    GH_SFLASH_COMMAND_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_COMMAND_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rwn;
}
GH_INLINE void GH_SFLASH_set_Command_CMDMODE(U8 data)
{
    GH_SFLASH_COMMAND_REAL_S d;
    d.all = *(volatile U32 *)REG_SFLASH_COMMAND_REAL;
    d.bitc.cmdmode = data;
    *(volatile U32 *)REG_SFLASH_COMMAND_REAL = d.all;
}
GH_INLINE U8   GH_SFLASH_get_Command_CMDMODE(void)
{
    GH_SFLASH_COMMAND_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_COMMAND_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cmdmode;
}
GH_INLINE void GH_SFLASH_set_Command_ADRMODE(U8 data)
{
    GH_SFLASH_COMMAND_REAL_S d;
    d.all = *(volatile U32 *)REG_SFLASH_COMMAND_REAL;
    d.bitc.adrmode = data;
    *(volatile U32 *)REG_SFLASH_COMMAND_REAL = d.all;
}
GH_INLINE U8   GH_SFLASH_get_Command_ADRMODE(void)
{
    GH_SFLASH_COMMAND_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_COMMAND_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adrmode;
}
GH_INLINE void GH_SFLASH_set_Command_DATAMODE(U8 data)
{
    GH_SFLASH_COMMAND_REAL_S d;
    d.all = *(volatile U32 *)REG_SFLASH_COMMAND_REAL;
    d.bitc.datamode = data;
    *(volatile U32 *)REG_SFLASH_COMMAND_REAL = d.all;
}
GH_INLINE U8   GH_SFLASH_get_Command_DATAMODE(void)
{
    GH_SFLASH_COMMAND_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_COMMAND_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.datamode;
}
GH_INLINE void GH_SFLASH_set_Command_DATANUM(U8 data)
{
    GH_SFLASH_COMMAND_REAL_S d;
    d.all = *(volatile U32 *)REG_SFLASH_COMMAND_REAL;
    d.bitc.datanum = data;
    *(volatile U32 *)REG_SFLASH_COMMAND_REAL = d.all;
}
GH_INLINE U8   GH_SFLASH_get_Command_DATANUM(void)
{
    GH_SFLASH_COMMAND_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_COMMAND_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.datanum;
}
GH_INLINE void GH_SFLASH_set_Command_HOLDTIME(U8 data)
{
    GH_SFLASH_COMMAND_REAL_S d;
    d.all = *(volatile U32 *)REG_SFLASH_COMMAND_REAL;
    d.bitc.holdtime = data;
    *(volatile U32 *)REG_SFLASH_COMMAND_REAL = d.all;
}
GH_INLINE U8   GH_SFLASH_get_Command_HOLDTIME(void)
{
    GH_SFLASH_COMMAND_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_COMMAND_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.holdtime;
}

/*----------------------------------------------------------------------------*/
/* register SFLASH_CE (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SFLASH_set_CE(U32 data)
{
    GH_SFLASH_CE_REAL_S real;
    GH_SFLASH_CE_S dummy;
    dummy.all = data ;
    real.bitc.ce = dummy.bitc.ce;
    real.bitc.wp = dummy.bitc.wp;
    real.bitc.hold = dummy.bitc.hold;
    real.bitc.cemode = dummy.bitc.cemode;
    real.bitc.wpmode = dummy.bitc.wpmode;
    real.bitc.holdmode = dummy.bitc.holdmode;
    real.bitc.chselect = dummy.bitc.chselect;
    *(volatile U32 *)REG_SFLASH_CE_REAL = real.all;
}
GH_INLINE U32  GH_SFLASH_get_CE(void)
{
    GH_SFLASH_CE_REAL_S real;
    GH_SFLASH_CE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SFLASH_CE_REAL);

    dummy.bitc.ce = real.bitc.ce;
    dummy.bitc.wp = real.bitc.wp;
    dummy.bitc.hold = real.bitc.hold;
    dummy.bitc.cemode = real.bitc.cemode;
    dummy.bitc.wpmode = real.bitc.wpmode;
    dummy.bitc.holdmode = real.bitc.holdmode;
    dummy.bitc.chselect = real.bitc.chselect;
    return dummy.all;
}
GH_INLINE void GH_SFLASH_set_CE_CE(U8 data)
{
    GH_SFLASH_CE_REAL_S d;
    d.all = *(volatile U32 *)REG_SFLASH_CE_REAL;
    d.bitc.ce = data;
    *(volatile U32 *)REG_SFLASH_CE_REAL = d.all;
}
GH_INLINE U8   GH_SFLASH_get_CE_CE(void)
{
    GH_SFLASH_CE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_CE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ce;
}
GH_INLINE void GH_SFLASH_set_CE_WP(U8 data)
{
    GH_SFLASH_CE_REAL_S d;
    d.all = *(volatile U32 *)REG_SFLASH_CE_REAL;
    d.bitc.wp = data;
    *(volatile U32 *)REG_SFLASH_CE_REAL = d.all;
}
GH_INLINE U8   GH_SFLASH_get_CE_WP(void)
{
    GH_SFLASH_CE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_CE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.wp;
}
GH_INLINE void GH_SFLASH_set_CE_HOLD(U8 data)
{
    GH_SFLASH_CE_REAL_S d;
    d.all = *(volatile U32 *)REG_SFLASH_CE_REAL;
    d.bitc.hold = data;
    *(volatile U32 *)REG_SFLASH_CE_REAL = d.all;
}
GH_INLINE U8   GH_SFLASH_get_CE_HOLD(void)
{
    GH_SFLASH_CE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_CE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hold;
}
GH_INLINE void GH_SFLASH_set_CE_CEMODE(U8 data)
{
    GH_SFLASH_CE_REAL_S d;
    d.all = *(volatile U32 *)REG_SFLASH_CE_REAL;
    d.bitc.cemode = data;
    *(volatile U32 *)REG_SFLASH_CE_REAL = d.all;
}
GH_INLINE U8   GH_SFLASH_get_CE_CEMODE(void)
{
    GH_SFLASH_CE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_CE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cemode;
}
GH_INLINE void GH_SFLASH_set_CE_WPMODE(U8 data)
{
    GH_SFLASH_CE_REAL_S d;
    d.all = *(volatile U32 *)REG_SFLASH_CE_REAL;
    d.bitc.wpmode = data;
    *(volatile U32 *)REG_SFLASH_CE_REAL = d.all;
}
GH_INLINE U8   GH_SFLASH_get_CE_WPMODE(void)
{
    GH_SFLASH_CE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_CE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.wpmode;
}
GH_INLINE void GH_SFLASH_set_CE_HOLDMODE(U8 data)
{
    GH_SFLASH_CE_REAL_S d;
    d.all = *(volatile U32 *)REG_SFLASH_CE_REAL;
    d.bitc.holdmode = data;
    *(volatile U32 *)REG_SFLASH_CE_REAL = d.all;
}
GH_INLINE U8   GH_SFLASH_get_CE_HOLDMODE(void)
{
    GH_SFLASH_CE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_CE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.holdmode;
}
GH_INLINE void GH_SFLASH_set_CE_CHSELECT(U8 data)
{
    GH_SFLASH_CE_REAL_S d;
    d.all = *(volatile U32 *)REG_SFLASH_CE_REAL;
    d.bitc.chselect = data;
    *(volatile U32 *)REG_SFLASH_CE_REAL = d.all;
}
GH_INLINE U8   GH_SFLASH_get_CE_CHSELECT(void)
{
    GH_SFLASH_CE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_CE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.chselect;
}

/*----------------------------------------------------------------------------*/
/* register SFLASH_Speed (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SFLASH_set_Speed(U32 data)
{
    GH_SFLASH_SPEED_REAL_S real;
    GH_SFLASH_SPEED_S dummy;
    dummy.all = data ;
    real.bitc.sf_sclk_sel = dummy.bitc.sf_sclk_sel;
    *(volatile U32 *)REG_SFLASH_SPEED_REAL = real.all;
}
GH_INLINE U32  GH_SFLASH_get_Speed(void)
{
    GH_SFLASH_SPEED_REAL_S real;
    GH_SFLASH_SPEED_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SFLASH_SPEED_REAL);

    dummy.bitc.sf_sclk_sel = real.bitc.sf_sclk_sel;
    return dummy.all;
}
GH_INLINE void GH_SFLASH_set_Speed_SF_SCLK_SEL(U8 data)
{
    GH_SFLASH_SPEED_REAL_S d;
    d.all = *(volatile U32 *)REG_SFLASH_SPEED_REAL;
    d.bitc.sf_sclk_sel = data;
    *(volatile U32 *)REG_SFLASH_SPEED_REAL = d.all;
}
GH_INLINE U8   GH_SFLASH_get_Speed_SF_SCLK_SEL(void)
{
    GH_SFLASH_SPEED_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_SPEED_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sf_sclk_sel;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SFLASH_init(void)
{
    GH_SFLASH_set_Data((U32)0x00000000);
    GH_SFLASH_set_Command((U32)0x00000000);
    GH_SFLASH_set_CE((U32)0x00000000);
    GH_SFLASH_set_Speed((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

