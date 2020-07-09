/******************************************************************************
**
** \file      gh_efuse.c
**
** \brief     EFUSE controller.
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
#include "gh_efuse.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_EFUSE_KEY_REAL                                  FIO_ADDRESS(EFUSE,0x6000B000) /* read */
#define REG_EFUSE_DATA_REAL                                 FIO_ADDRESS(EFUSE,0x6000B010) /* read */
#define REG_EFUSE_USER_DATA_REAL                            FIO_ADDRESS(EFUSE,0x6000B014) /* read */
#define REG_EFUSE_CTRL_REAL                                 FIO_ADDRESS(EFUSE,0x6000B100) /* read/write */
#define REG_EFUSE_BOOT_REAL                                 FIO_ADDRESS(EFUSE,0x6000B104) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* EFUSE_Data */
    U32 all;
    struct {
        U32 boot_mode_sel               : 1;
        U32 engine_sel                  : 1;
        U32 user_data                   : 30;
    } bitc;
} GH_EFUSE_DATA_REAL_S;

typedef union { /* EFUSE_CTRL */
    U32 all;
    struct {
        U32 wr_progen_high_cnt          : 9;
        U32 wr_progen_low_cnt           : 6;
        U32 wr_addr_setup_cnt           : 4;
        U32 rd_addr_setup_cnt           : 3;
        U32 rd_prchg_setup_cnt          : 2;
        U32 rd_prchg_hold_cnt           : 2;
        U32 rd_sense_hold_cnt           : 3;
        U32 wait_rd_addr_update_cnt     : 3;
    } bitc;
} GH_EFUSE_CTRL_REAL_S;

typedef union { /* EFUSE_BOOT */
    U32 all;
    struct {
        U32 en                          : 1;
        U32 rd_ok                       : 1;
        U32                             : 30;
    } bitc;
} GH_EFUSE_BOOT_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register EFUSE_KEY (read)                                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_EFUSE_get_KEY(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_EFUSE_KEY_REAL + index * FIO_MOFFSET(EFUSE,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register EFUSE_Data (read)                                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_EFUSE_get_Data(U8 index)
{
    GH_EFUSE_DATA_REAL_S real;
    GH_EFUSE_DATA_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_EFUSE_DATA_REAL + index * FIO_MOFFSET(EFUSE,0x00000004)));

    dummy.bitc.boot_mode_sel = real.bitc.boot_mode_sel;
    dummy.bitc.engine_sel = real.bitc.engine_sel;
    dummy.bitc.user_data = real.bitc.user_data;
    return dummy.all;
}
GH_INLINE U8   GH_EFUSE_get_Data_boot_mode_sel(U8 index)
{
    GH_EFUSE_DATA_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_EFUSE_DATA_REAL + index * FIO_MOFFSET(EFUSE,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.boot_mode_sel;
}
GH_INLINE U8   GH_EFUSE_get_Data_engine_sel(U8 index)
{
    GH_EFUSE_DATA_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_EFUSE_DATA_REAL + index * FIO_MOFFSET(EFUSE,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.engine_sel;
}
GH_INLINE U32  GH_EFUSE_get_Data_User_Data(U8 index)
{
    GH_EFUSE_DATA_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_EFUSE_DATA_REAL + index * FIO_MOFFSET(EFUSE,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.user_data;
}

/*----------------------------------------------------------------------------*/
/* register EFUSE_User_Data (read)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_EFUSE_get_User_Data(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_EFUSE_USER_DATA_REAL + index * FIO_MOFFSET(EFUSE,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register EFUSE_CTRL (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EFUSE_set_CTRL(U32 data)
{
    GH_EFUSE_CTRL_REAL_S real;
    GH_EFUSE_CTRL_S dummy;
    dummy.all = data ;
    real.bitc.wr_progen_high_cnt = dummy.bitc.wr_progen_high_cnt;
    real.bitc.wr_progen_low_cnt = dummy.bitc.wr_progen_low_cnt;
    real.bitc.wr_addr_setup_cnt = dummy.bitc.wr_addr_setup_cnt;
    real.bitc.rd_addr_setup_cnt = dummy.bitc.rd_addr_setup_cnt;
    real.bitc.rd_prchg_setup_cnt = dummy.bitc.rd_prchg_setup_cnt;
    real.bitc.rd_prchg_hold_cnt = dummy.bitc.rd_prchg_hold_cnt;
    real.bitc.rd_sense_hold_cnt = dummy.bitc.rd_sense_hold_cnt;
    real.bitc.wait_rd_addr_update_cnt = dummy.bitc.wait_rd_addr_update_cnt;
    *(volatile U32 *)REG_EFUSE_CTRL_REAL = real.all;
}
GH_INLINE U32  GH_EFUSE_get_CTRL(void)
{
    GH_EFUSE_CTRL_REAL_S real;
    GH_EFUSE_CTRL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_EFUSE_CTRL_REAL);

    dummy.bitc.wr_progen_high_cnt = real.bitc.wr_progen_high_cnt;
    dummy.bitc.wr_progen_low_cnt = real.bitc.wr_progen_low_cnt;
    dummy.bitc.wr_addr_setup_cnt = real.bitc.wr_addr_setup_cnt;
    dummy.bitc.rd_addr_setup_cnt = real.bitc.rd_addr_setup_cnt;
    dummy.bitc.rd_prchg_setup_cnt = real.bitc.rd_prchg_setup_cnt;
    dummy.bitc.rd_prchg_hold_cnt = real.bitc.rd_prchg_hold_cnt;
    dummy.bitc.rd_sense_hold_cnt = real.bitc.rd_sense_hold_cnt;
    dummy.bitc.wait_rd_addr_update_cnt = real.bitc.wait_rd_addr_update_cnt;
    return dummy.all;
}
GH_INLINE void GH_EFUSE_set_CTRL_wr_progen_high_cnt(U16 data)
{
    GH_EFUSE_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_EFUSE_CTRL_REAL;
    d.bitc.wr_progen_high_cnt = data;
    *(volatile U32 *)REG_EFUSE_CTRL_REAL = d.all;
}
GH_INLINE U16  GH_EFUSE_get_CTRL_wr_progen_high_cnt(void)
{
    GH_EFUSE_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EFUSE_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.wr_progen_high_cnt;
}
GH_INLINE void GH_EFUSE_set_CTRL_wr_progen_low_cnt(U8 data)
{
    GH_EFUSE_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_EFUSE_CTRL_REAL;
    d.bitc.wr_progen_low_cnt = data;
    *(volatile U32 *)REG_EFUSE_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_EFUSE_get_CTRL_wr_progen_low_cnt(void)
{
    GH_EFUSE_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EFUSE_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.wr_progen_low_cnt;
}
GH_INLINE void GH_EFUSE_set_CTRL_wr_addr_setup_cnt(U8 data)
{
    GH_EFUSE_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_EFUSE_CTRL_REAL;
    d.bitc.wr_addr_setup_cnt = data;
    *(volatile U32 *)REG_EFUSE_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_EFUSE_get_CTRL_wr_addr_setup_cnt(void)
{
    GH_EFUSE_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EFUSE_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.wr_addr_setup_cnt;
}
GH_INLINE void GH_EFUSE_set_CTRL_rd_addr_setup_cnt(U8 data)
{
    GH_EFUSE_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_EFUSE_CTRL_REAL;
    d.bitc.rd_addr_setup_cnt = data;
    *(volatile U32 *)REG_EFUSE_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_EFUSE_get_CTRL_rd_addr_setup_cnt(void)
{
    GH_EFUSE_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EFUSE_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rd_addr_setup_cnt;
}
GH_INLINE void GH_EFUSE_set_CTRL_rd_prchg_setup_cnt(U8 data)
{
    GH_EFUSE_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_EFUSE_CTRL_REAL;
    d.bitc.rd_prchg_setup_cnt = data;
    *(volatile U32 *)REG_EFUSE_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_EFUSE_get_CTRL_rd_prchg_setup_cnt(void)
{
    GH_EFUSE_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EFUSE_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rd_prchg_setup_cnt;
}
GH_INLINE void GH_EFUSE_set_CTRL_rd_prchg_hold_cnt(U8 data)
{
    GH_EFUSE_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_EFUSE_CTRL_REAL;
    d.bitc.rd_prchg_hold_cnt = data;
    *(volatile U32 *)REG_EFUSE_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_EFUSE_get_CTRL_rd_prchg_hold_cnt(void)
{
    GH_EFUSE_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EFUSE_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rd_prchg_hold_cnt;
}
GH_INLINE void GH_EFUSE_set_CTRL_rd_sense_hold_cnt(U8 data)
{
    GH_EFUSE_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_EFUSE_CTRL_REAL;
    d.bitc.rd_sense_hold_cnt = data;
    *(volatile U32 *)REG_EFUSE_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_EFUSE_get_CTRL_rd_sense_hold_cnt(void)
{
    GH_EFUSE_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EFUSE_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rd_sense_hold_cnt;
}
GH_INLINE void GH_EFUSE_set_CTRL_Wait_rd_addr_update_cnt(U8 data)
{
    GH_EFUSE_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_EFUSE_CTRL_REAL;
    d.bitc.wait_rd_addr_update_cnt = data;
    *(volatile U32 *)REG_EFUSE_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_EFUSE_get_CTRL_Wait_rd_addr_update_cnt(void)
{
    GH_EFUSE_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EFUSE_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.wait_rd_addr_update_cnt;
}

/*----------------------------------------------------------------------------*/
/* register EFUSE_BOOT (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EFUSE_set_BOOT(U32 data)
{
    GH_EFUSE_BOOT_REAL_S real;
    GH_EFUSE_BOOT_S dummy;
    dummy.all = data ;
    real.bitc.en = dummy.bitc.en;
    real.bitc.rd_ok = dummy.bitc.rd_ok;
    *(volatile U32 *)REG_EFUSE_BOOT_REAL = real.all;
}
GH_INLINE U32  GH_EFUSE_get_BOOT(void)
{
    GH_EFUSE_BOOT_REAL_S real;
    GH_EFUSE_BOOT_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_EFUSE_BOOT_REAL);

    dummy.bitc.en = real.bitc.en;
    dummy.bitc.rd_ok = real.bitc.rd_ok;
    return dummy.all;
}
GH_INLINE void GH_EFUSE_set_BOOT_EN(U8 data)
{
    GH_EFUSE_BOOT_REAL_S d;
    d.all = *(volatile U32 *)REG_EFUSE_BOOT_REAL;
    d.bitc.en = data;
    *(volatile U32 *)REG_EFUSE_BOOT_REAL = d.all;
}
GH_INLINE U8   GH_EFUSE_get_BOOT_EN(void)
{
    GH_EFUSE_BOOT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EFUSE_BOOT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en;
}
GH_INLINE void GH_EFUSE_set_BOOT_RD_OK(U8 data)
{
    GH_EFUSE_BOOT_REAL_S d;
    d.all = *(volatile U32 *)REG_EFUSE_BOOT_REAL;
    d.bitc.rd_ok = data;
    *(volatile U32 *)REG_EFUSE_BOOT_REAL = d.all;
}
GH_INLINE U8   GH_EFUSE_get_BOOT_RD_OK(void)
{
    GH_EFUSE_BOOT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EFUSE_BOOT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rd_ok;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EFUSE_init(void)
{
    GH_EFUSE_set_CTRL((U32)0x4551c119);
    GH_EFUSE_set_BOOT((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

