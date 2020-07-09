/*!
*******************************************************************************
**
** \file      gh_efuse.h
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
#ifndef _GH_EFUSE_H
#define _GH_EFUSE_H

#ifdef __LINUX__
#include "reg4linux.h"
#else
#define FIO_ADDRESS(block,address) (address)
#define FIO_MOFFSET(block,moffset) (moffset)
#endif

#ifndef __LINUX__
#include "gtypes.h" /* global type definitions */
#include "gh_lib_cfg.h" /* configuration */
#endif

#define GH_EFUSE_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_EFUSE_DEBUG_PRINT_FUNCTION printk
#else
#define GH_EFUSE_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_EFUSE_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_EFUSE_KEY                                       FIO_ADDRESS(EFUSE,0x9000B000) /* read */
#define REG_EFUSE_DATA                                      FIO_ADDRESS(EFUSE,0x9000B010) /* read */
#define REG_EFUSE_USER_DATA                                 FIO_ADDRESS(EFUSE,0x9000B014) /* read */
#define REG_EFUSE_CTRL                                      FIO_ADDRESS(EFUSE,0x9000B100) /* read/write */
#define REG_EFUSE_BOOT                                      FIO_ADDRESS(EFUSE,0x9000B104) /* read/write */

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
} GH_EFUSE_DATA_S;

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
} GH_EFUSE_CTRL_S;

typedef union { /* EFUSE_BOOT */
    U32 all;
    struct {
        U32 en                          : 1;
        U32 rd_ok                       : 1;
        U32                             : 30;
    } bitc;
} GH_EFUSE_BOOT_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register EFUSE_KEY (read)                                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'EFUSE_KEY'. */
U32  GH_EFUSE_get_KEY(U8 index);

/*----------------------------------------------------------------------------*/
/* register EFUSE_Data (read)                                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'EFUSE_Data'. */
U32  GH_EFUSE_get_Data(U8 index);
/*! \brief Reads the bit group 'boot_mode_sel' of register 'EFUSE_Data'. */
U8   GH_EFUSE_get_Data_boot_mode_sel(U8 index);
/*! \brief Reads the bit group 'engine_sel' of register 'EFUSE_Data'. */
U8   GH_EFUSE_get_Data_engine_sel(U8 index);
/*! \brief Reads the bit group 'User_Data' of register 'EFUSE_Data'. */
U32  GH_EFUSE_get_Data_User_Data(U8 index);

/*----------------------------------------------------------------------------*/
/* register EFUSE_User_Data (read)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'EFUSE_User_Data'. */
U32  GH_EFUSE_get_User_Data(U8 index);

/*----------------------------------------------------------------------------*/
/* register EFUSE_CTRL (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'EFUSE_CTRL'. */
void GH_EFUSE_set_CTRL(U32 data);
/*! \brief Reads the register 'EFUSE_CTRL'. */
U32  GH_EFUSE_get_CTRL(void);
/*! \brief Writes the bit group 'wr_progen_high_cnt' of register 'EFUSE_CTRL'. */
void GH_EFUSE_set_CTRL_wr_progen_high_cnt(U16 data);
/*! \brief Reads the bit group 'wr_progen_high_cnt' of register 'EFUSE_CTRL'. */
U16  GH_EFUSE_get_CTRL_wr_progen_high_cnt(void);
/*! \brief Writes the bit group 'wr_progen_low_cnt' of register 'EFUSE_CTRL'. */
void GH_EFUSE_set_CTRL_wr_progen_low_cnt(U8 data);
/*! \brief Reads the bit group 'wr_progen_low_cnt' of register 'EFUSE_CTRL'. */
U8   GH_EFUSE_get_CTRL_wr_progen_low_cnt(void);
/*! \brief Writes the bit group 'wr_addr_setup_cnt' of register 'EFUSE_CTRL'. */
void GH_EFUSE_set_CTRL_wr_addr_setup_cnt(U8 data);
/*! \brief Reads the bit group 'wr_addr_setup_cnt' of register 'EFUSE_CTRL'. */
U8   GH_EFUSE_get_CTRL_wr_addr_setup_cnt(void);
/*! \brief Writes the bit group 'rd_addr_setup_cnt' of register 'EFUSE_CTRL'. */
void GH_EFUSE_set_CTRL_rd_addr_setup_cnt(U8 data);
/*! \brief Reads the bit group 'rd_addr_setup_cnt' of register 'EFUSE_CTRL'. */
U8   GH_EFUSE_get_CTRL_rd_addr_setup_cnt(void);
/*! \brief Writes the bit group 'rd_prchg_setup_cnt' of register 'EFUSE_CTRL'. */
void GH_EFUSE_set_CTRL_rd_prchg_setup_cnt(U8 data);
/*! \brief Reads the bit group 'rd_prchg_setup_cnt' of register 'EFUSE_CTRL'. */
U8   GH_EFUSE_get_CTRL_rd_prchg_setup_cnt(void);
/*! \brief Writes the bit group 'rd_prchg_hold_cnt' of register 'EFUSE_CTRL'. */
void GH_EFUSE_set_CTRL_rd_prchg_hold_cnt(U8 data);
/*! \brief Reads the bit group 'rd_prchg_hold_cnt' of register 'EFUSE_CTRL'. */
U8   GH_EFUSE_get_CTRL_rd_prchg_hold_cnt(void);
/*! \brief Writes the bit group 'rd_sense_hold_cnt' of register 'EFUSE_CTRL'. */
void GH_EFUSE_set_CTRL_rd_sense_hold_cnt(U8 data);
/*! \brief Reads the bit group 'rd_sense_hold_cnt' of register 'EFUSE_CTRL'. */
U8   GH_EFUSE_get_CTRL_rd_sense_hold_cnt(void);
/*! \brief Writes the bit group 'Wait_rd_addr_update_cnt' of register 'EFUSE_CTRL'. */
void GH_EFUSE_set_CTRL_Wait_rd_addr_update_cnt(U8 data);
/*! \brief Reads the bit group 'Wait_rd_addr_update_cnt' of register 'EFUSE_CTRL'. */
U8   GH_EFUSE_get_CTRL_Wait_rd_addr_update_cnt(void);

/*----------------------------------------------------------------------------*/
/* register EFUSE_BOOT (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'EFUSE_BOOT'. */
void GH_EFUSE_set_BOOT(U32 data);
/*! \brief Reads the register 'EFUSE_BOOT'. */
U32  GH_EFUSE_get_BOOT(void);
/*! \brief Writes the bit group 'EN' of register 'EFUSE_BOOT'. */
void GH_EFUSE_set_BOOT_EN(U8 data);
/*! \brief Reads the bit group 'EN' of register 'EFUSE_BOOT'. */
U8   GH_EFUSE_get_BOOT_EN(void);
/*! \brief Writes the bit group 'RD_OK' of register 'EFUSE_BOOT'. */
void GH_EFUSE_set_BOOT_RD_OK(U8 data);
/*! \brief Reads the bit group 'RD_OK' of register 'EFUSE_BOOT'. */
U8   GH_EFUSE_get_BOOT_RD_OK(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_EFUSE_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_efuse.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_EFUSE_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

