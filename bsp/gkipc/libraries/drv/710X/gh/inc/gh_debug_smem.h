/*!
*******************************************************************************
**
** \file      gh_debug_smem.h
**
** \brief     SMEM Debug Registers.
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
#ifndef _GH_DEBUG_SMEM_H
#define _GH_DEBUG_SMEM_H

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

#define GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION printk
#else
#define GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB0_START          FIO_ADDRESS(DEBUG_SMEM,0xa0100000) /* read/write */
#define REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB1_START          FIO_ADDRESS(DEBUG_SMEM,0xa0100400) /* read/write */
#define REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB2_START          FIO_ADDRESS(DEBUG_SMEM,0xa0100800) /* read/write */
#define REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB3_START          FIO_ADDRESS(DEBUG_SMEM,0xa0100C00) /* read/write */
#define REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB4_START          FIO_ADDRESS(DEBUG_SMEM,0xa0101000) /* read/write */
#define REG_DEBUG_SMEM_SYNC_COUNTER                         FIO_ADDRESS(DEBUG_SMEM,0xa0101000) /* read/write */
#define REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0                    FIO_ADDRESS(DEBUG_SMEM,0xa0104000) /* read/write */
#define REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1                    FIO_ADDRESS(DEBUG_SMEM,0xa0104400) /* read/write */
#define REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2                    FIO_ADDRESS(DEBUG_SMEM,0xa0104800) /* read/write */
#define REG_DEBUG_SMEM_DRAM_CHANNEL_SUB3                    FIO_ADDRESS(DEBUG_SMEM,0xa0104C00) /* read/write */
#define REG_DEBUG_SMEM_DRAM_CHANNEL_SUB4                    FIO_ADDRESS(DEBUG_SMEM,0xa0105000) /* read/write */
#define REG_DEBUG_SMEM_FMEM_REFRESH_VALUE                   FIO_ADDRESS(DEBUG_SMEM,0xa0108080) /* read/write */
#define REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE       FIO_ADDRESS(DEBUG_SMEM,0xa01080A0) /* read/write */
#define REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR                    FIO_ADDRESS(DEBUG_SMEM,0xa01080A4) /* read/write */
#define REG_DEBUG_SMEM_REQQ_REQUEST_QUEUE_STATUS            FIO_ADDRESS(DEBUG_SMEM,0xa0108100) /* read */
#define REG_DEBUG_SMEM_ONET_DMA_STATUS                      FIO_ADDRESS(DEBUG_SMEM,0xa0108104) /* read */
#define REG_DEBUG_SMEM_RMB_DMA_STATUS0                      FIO_ADDRESS(DEBUG_SMEM,0xa0108108) /* read */
#define REG_DEBUG_SMEM_RMB_DMA_STATUS1                      FIO_ADDRESS(DEBUG_SMEM,0xa010810C) /* read */
#define REG_DEBUG_SMEM_XFER_DRAM_TRANSFER_STATUS            FIO_ADDRESS(DEBUG_SMEM,0xa0108110) /* read */
#define REG_DEBUG_SMEM_SYNC_COUNTER_STATUS0                 FIO_ADDRESS(DEBUG_SMEM,0xa0108114) /* read */
#define REG_DEBUG_SMEM_SYNC_COUNTER_STATUS1                 FIO_ADDRESS(DEBUG_SMEM,0xa0108118) /* read */
#define REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS             FIO_ADDRESS(DEBUG_SMEM,0xa010811C) /* read */
#define REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS             FIO_ADDRESS(DEBUG_SMEM,0xa0108120) /* read */
#define REG_DEBUG_SMEM_ERROR_STATUS                         FIO_ADDRESS(DEBUG_SMEM,0xa0108140) /* read/clear */
#define REG_DEBUG_SMEM_ERROR_INFO                           FIO_ADDRESS(DEBUG_SMEM,0xa0108150) /* read/clear */
#define REG_DEBUG_SMEM_ERROR_MASK                           FIO_ADDRESS(DEBUG_SMEM,0xa0108160) /* read/write */
#define REG_DEBUG_SMEM_FMEM                                 FIO_ADDRESS(DEBUG_SMEM,0xa0200000) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* DEBUG_SMEM_sync_counter */
    U32 all;
    struct {
        U32 max                         : 8;
        U32 count                       : 8;
        U32                             : 8;
        U32 max_notchange               : 1;
        U32 value_notchange             : 1;
        U32                             : 6;
    } bitc;
} GH_DEBUG_SMEM_SYNC_COUNTER_S;

typedef union { /* DEBUG_SMEM_dram_channel_sub0 */
    U32 all;
    struct {
        U32 dpitch                      : 12;
        U32 drowmax                     : 13;
        U32 dpriority                   : 2;
        U32 dramdisable                 : 1;
        U32 nextdramdisable             : 1;
        U32                             : 3;
    } bitc;
} GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_S;

typedef union { /* DEBUG_SMEM_dram_channel_sub1 */
    U32 all;
    struct {
        U32 dcol                        : 14;
        U32                             : 2;
        U32 drow                        : 9;
        U32                             : 7;
    } bitc;
} GH_DEBUG_SMEM_DRAM_CHANNEL_SUB1_S;

typedef union { /* DEBUG_SMEM_dram_channel_sub2 */
    U32 all;
    struct {
        U32 dsrowcol                    : 14;
        U32 dscliprow                   : 10;
        U32 ddrepeatrow                 : 1;
        U32 dtileenable                 : 1;
        U32 dtilefield                  : 1;
        U32                             : 5;
    } bitc;
} GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_S;

typedef union { /* DEBUG_SMEM_RMB_2nd_lvl_clk_gating_disable */
    U32 all;
    struct {
        U32 en                          : 16;
        U32 asserted                    : 3;
        U32                             : 13;
    } bitc;
} GH_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_S;

typedef union { /* DEBUG_SMEM_DRAM_RMB_behavior */
    U32 all;
    struct {
        U32 dram_rmb                    : 1;
        U32 no_real_purpose             : 1;
        U32                             : 14;
        U32 load_data                   : 1;
        U32 no_write_requests           : 1;
        U32 best_left_alone             : 2;
        U32 write_requests              : 1;
        U32                             : 11;
    } bitc;
} GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_S;

typedef union { /* DEBUG_SMEM_SYNC_counter_status0 */
    U32 all;
    struct {
        U32 th0                         : 3;
        U32 th1                         : 3;
        U32 th2                         : 3;
        U32 th3                         : 3;
        U32                             : 20;
    } bitc;
} GH_DEBUG_SMEM_SYNC_COUNTER_STATUS0_S;

typedef union { /* DEBUG_SMEM_SYNC_counter_status1 */
    U32 all;
    struct {
        U32 th0                         : 3;
        U32 th1                         : 3;
        U32 th2                         : 3;
        U32 th3                         : 3;
        U32                             : 20;
    } bitc;
} GH_DEBUG_SMEM_SYNC_COUNTER_STATUS1_S;

typedef union { /* DEBUG_SMEM_SYNC_counter_IDSP_status */
    U32 all;
    struct {
        U32 id0                         : 3;
        U32 id1                         : 3;
        U32 id2                         : 3;
        U32 id3                         : 3;
        U32 id4                         : 3;
        U32 id5                         : 3;
        U32 id6                         : 3;
        U32                             : 11;
    } bitc;
} GH_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_S;

typedef union { /* DEBUG_SMEM_SYNC_counter_VOUT_status */
    U32 all;
    struct {
        U32 id0                         : 3;
        U32 id1                         : 3;
        U32 id2                         : 3;
        U32 id3                         : 3;
        U32 id4                         : 3;
        U32 id5                         : 3;
        U32                             : 14;
    } bitc;
} GH_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_S;

typedef union { /* DEBUG_SMEM_ERROR_status */
    U32 all;
    struct {
        U32 left_right                  : 1;
        U32 top_bottom                  : 1;
        U32 reached                     : 1;
        U32 srows                       : 1;
        U32 vflip                       : 1;
        U32 wider                       : 1;
        U32                             : 2;
        U32 transfers                   : 1;
        U32                             : 3;
        U32 idsp_sync                   : 1;
        U32 vout_sync                   : 1;
        U32                             : 18;
    } bitc;
} GH_DEBUG_SMEM_ERROR_STATUS_S;

typedef union { /* DEBUG_SMEM_ERROR_info */
    U32 all;
    struct {
        U32 first_error                 : 13;
        U32                             : 3;
        U32 id                          : 4;
        U32                             : 11;
        U32 valid                       : 1;
    } bitc;
} GH_DEBUG_SMEM_ERROR_INFO_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern GH_DEBUG_SMEM_ERROR_STATUS_S            m_debug_smem_error_status;
extern GH_DEBUG_SMEM_ERROR_INFO_S              m_debug_smem_error_info;

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_smem_channel_reg_sub0_start (read/write)               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DEBUG_SMEM_smem_channel_reg_sub0_start'. */
void GH_DEBUG_SMEM_set_smem_channel_reg_sub0_start(U16 index, U32 data);
/*! \brief Reads the register 'DEBUG_SMEM_smem_channel_reg_sub0_start'. */
U32  GH_DEBUG_SMEM_get_smem_channel_reg_sub0_start(U16 index);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_smem_channel_reg_sub1_start (read/write)               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DEBUG_SMEM_smem_channel_reg_sub1_start'. */
void GH_DEBUG_SMEM_set_smem_channel_reg_sub1_start(U16 index, U32 data);
/*! \brief Reads the register 'DEBUG_SMEM_smem_channel_reg_sub1_start'. */
U32  GH_DEBUG_SMEM_get_smem_channel_reg_sub1_start(U16 index);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_smem_channel_reg_sub2_start (read/write)               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DEBUG_SMEM_smem_channel_reg_sub2_start'. */
void GH_DEBUG_SMEM_set_smem_channel_reg_sub2_start(U16 index, U32 data);
/*! \brief Reads the register 'DEBUG_SMEM_smem_channel_reg_sub2_start'. */
U32  GH_DEBUG_SMEM_get_smem_channel_reg_sub2_start(U16 index);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_smem_channel_reg_sub3_start (read/write)               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DEBUG_SMEM_smem_channel_reg_sub3_start'. */
void GH_DEBUG_SMEM_set_smem_channel_reg_sub3_start(U16 index, U32 data);
/*! \brief Reads the register 'DEBUG_SMEM_smem_channel_reg_sub3_start'. */
U32  GH_DEBUG_SMEM_get_smem_channel_reg_sub3_start(U16 index);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_smem_channel_reg_sub4_start (read/write)               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DEBUG_SMEM_smem_channel_reg_sub4_start'. */
void GH_DEBUG_SMEM_set_smem_channel_reg_sub4_start(U16 index, U32 data);
/*! \brief Reads the register 'DEBUG_SMEM_smem_channel_reg_sub4_start'. */
U32  GH_DEBUG_SMEM_get_smem_channel_reg_sub4_start(U16 index);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_sync_counter (read/write)                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DEBUG_SMEM_sync_counter'. */
void GH_DEBUG_SMEM_set_sync_counter(U8 index, U32 data);
/*! \brief Reads the register 'DEBUG_SMEM_sync_counter'. */
U32  GH_DEBUG_SMEM_get_sync_counter(U8 index);
/*! \brief Writes the bit group 'max' of register 'DEBUG_SMEM_sync_counter'. */
void GH_DEBUG_SMEM_set_sync_counter_max(U8 index, U8 data);
/*! \brief Reads the bit group 'max' of register 'DEBUG_SMEM_sync_counter'. */
U8   GH_DEBUG_SMEM_get_sync_counter_max(U8 index);
/*! \brief Writes the bit group 'count' of register 'DEBUG_SMEM_sync_counter'. */
void GH_DEBUG_SMEM_set_sync_counter_count(U8 index, U8 data);
/*! \brief Reads the bit group 'count' of register 'DEBUG_SMEM_sync_counter'. */
U8   GH_DEBUG_SMEM_get_sync_counter_count(U8 index);
/*! \brief Writes the bit group 'max_notchange' of register 'DEBUG_SMEM_sync_counter'. */
void GH_DEBUG_SMEM_set_sync_counter_max_notchange(U8 index, U8 data);
/*! \brief Reads the bit group 'max_notchange' of register 'DEBUG_SMEM_sync_counter'. */
U8   GH_DEBUG_SMEM_get_sync_counter_max_notchange(U8 index);
/*! \brief Writes the bit group 'value_notchange' of register 'DEBUG_SMEM_sync_counter'. */
void GH_DEBUG_SMEM_set_sync_counter_value_notchange(U8 index, U8 data);
/*! \brief Reads the bit group 'value_notchange' of register 'DEBUG_SMEM_sync_counter'. */
U8   GH_DEBUG_SMEM_get_sync_counter_value_notchange(U8 index);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_dram_channel_sub0 (read/write)                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DEBUG_SMEM_dram_channel_sub0'. */
void GH_DEBUG_SMEM_set_dram_channel_sub0(U8 index, U32 data);
/*! \brief Reads the register 'DEBUG_SMEM_dram_channel_sub0'. */
U32  GH_DEBUG_SMEM_get_dram_channel_sub0(U8 index);
/*! \brief Writes the bit group 'dpitch' of register 'DEBUG_SMEM_dram_channel_sub0'. */
void GH_DEBUG_SMEM_set_dram_channel_sub0_dpitch(U8 index, U16 data);
/*! \brief Reads the bit group 'dpitch' of register 'DEBUG_SMEM_dram_channel_sub0'. */
U16  GH_DEBUG_SMEM_get_dram_channel_sub0_dpitch(U8 index);
/*! \brief Writes the bit group 'drowmax' of register 'DEBUG_SMEM_dram_channel_sub0'. */
void GH_DEBUG_SMEM_set_dram_channel_sub0_drowmax(U8 index, U16 data);
/*! \brief Reads the bit group 'drowmax' of register 'DEBUG_SMEM_dram_channel_sub0'. */
U16  GH_DEBUG_SMEM_get_dram_channel_sub0_drowmax(U8 index);
/*! \brief Writes the bit group 'dpriority' of register 'DEBUG_SMEM_dram_channel_sub0'. */
void GH_DEBUG_SMEM_set_dram_channel_sub0_dpriority(U8 index, U8 data);
/*! \brief Reads the bit group 'dpriority' of register 'DEBUG_SMEM_dram_channel_sub0'. */
U8   GH_DEBUG_SMEM_get_dram_channel_sub0_dpriority(U8 index);
/*! \brief Writes the bit group 'dramDisable' of register 'DEBUG_SMEM_dram_channel_sub0'. */
void GH_DEBUG_SMEM_set_dram_channel_sub0_dramDisable(U8 index, U8 data);
/*! \brief Reads the bit group 'dramDisable' of register 'DEBUG_SMEM_dram_channel_sub0'. */
U8   GH_DEBUG_SMEM_get_dram_channel_sub0_dramDisable(U8 index);
/*! \brief Writes the bit group 'nextDramDisable' of register 'DEBUG_SMEM_dram_channel_sub0'. */
void GH_DEBUG_SMEM_set_dram_channel_sub0_nextDramDisable(U8 index, U8 data);
/*! \brief Reads the bit group 'nextDramDisable' of register 'DEBUG_SMEM_dram_channel_sub0'. */
U8   GH_DEBUG_SMEM_get_dram_channel_sub0_nextDramDisable(U8 index);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_dram_channel_sub1 (read/write)                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DEBUG_SMEM_dram_channel_sub1'. */
void GH_DEBUG_SMEM_set_dram_channel_sub1(U8 index, U32 data);
/*! \brief Reads the register 'DEBUG_SMEM_dram_channel_sub1'. */
U32  GH_DEBUG_SMEM_get_dram_channel_sub1(U8 index);
/*! \brief Writes the bit group 'dcol' of register 'DEBUG_SMEM_dram_channel_sub1'. */
void GH_DEBUG_SMEM_set_dram_channel_sub1_dcol(U8 index, U16 data);
/*! \brief Reads the bit group 'dcol' of register 'DEBUG_SMEM_dram_channel_sub1'. */
U16  GH_DEBUG_SMEM_get_dram_channel_sub1_dcol(U8 index);
/*! \brief Writes the bit group 'drow' of register 'DEBUG_SMEM_dram_channel_sub1'. */
void GH_DEBUG_SMEM_set_dram_channel_sub1_drow(U8 index, U16 data);
/*! \brief Reads the bit group 'drow' of register 'DEBUG_SMEM_dram_channel_sub1'. */
U16  GH_DEBUG_SMEM_get_dram_channel_sub1_drow(U8 index);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_dram_channel_sub2 (read/write)                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DEBUG_SMEM_dram_channel_sub2'. */
void GH_DEBUG_SMEM_set_dram_channel_sub2(U8 index, U32 data);
/*! \brief Reads the register 'DEBUG_SMEM_dram_channel_sub2'. */
U32  GH_DEBUG_SMEM_get_dram_channel_sub2(U8 index);
/*! \brief Writes the bit group 'dsrowcol' of register 'DEBUG_SMEM_dram_channel_sub2'. */
void GH_DEBUG_SMEM_set_dram_channel_sub2_dsrowcol(U8 index, U16 data);
/*! \brief Reads the bit group 'dsrowcol' of register 'DEBUG_SMEM_dram_channel_sub2'. */
U16  GH_DEBUG_SMEM_get_dram_channel_sub2_dsrowcol(U8 index);
/*! \brief Writes the bit group 'dscliprow' of register 'DEBUG_SMEM_dram_channel_sub2'. */
void GH_DEBUG_SMEM_set_dram_channel_sub2_dscliprow(U8 index, U16 data);
/*! \brief Reads the bit group 'dscliprow' of register 'DEBUG_SMEM_dram_channel_sub2'. */
U16  GH_DEBUG_SMEM_get_dram_channel_sub2_dscliprow(U8 index);
/*! \brief Writes the bit group 'ddrepeatRow' of register 'DEBUG_SMEM_dram_channel_sub2'. */
void GH_DEBUG_SMEM_set_dram_channel_sub2_ddrepeatRow(U8 index, U8 data);
/*! \brief Reads the bit group 'ddrepeatRow' of register 'DEBUG_SMEM_dram_channel_sub2'. */
U8   GH_DEBUG_SMEM_get_dram_channel_sub2_ddrepeatRow(U8 index);
/*! \brief Writes the bit group 'dtileEnable' of register 'DEBUG_SMEM_dram_channel_sub2'. */
void GH_DEBUG_SMEM_set_dram_channel_sub2_dtileEnable(U8 index, U8 data);
/*! \brief Reads the bit group 'dtileEnable' of register 'DEBUG_SMEM_dram_channel_sub2'. */
U8   GH_DEBUG_SMEM_get_dram_channel_sub2_dtileEnable(U8 index);
/*! \brief Writes the bit group 'dtileField' of register 'DEBUG_SMEM_dram_channel_sub2'. */
void GH_DEBUG_SMEM_set_dram_channel_sub2_dtileField(U8 index, U8 data);
/*! \brief Reads the bit group 'dtileField' of register 'DEBUG_SMEM_dram_channel_sub2'. */
U8   GH_DEBUG_SMEM_get_dram_channel_sub2_dtileField(U8 index);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_dram_channel_sub3 (read/write)                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DEBUG_SMEM_dram_channel_sub3'. */
void GH_DEBUG_SMEM_set_dram_channel_sub3(U8 index, U32 data);
/*! \brief Reads the register 'DEBUG_SMEM_dram_channel_sub3'. */
U32  GH_DEBUG_SMEM_get_dram_channel_sub3(U8 index);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_dram_channel_sub4 (read/write)                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DEBUG_SMEM_dram_channel_sub4'. */
void GH_DEBUG_SMEM_set_dram_channel_sub4(U8 index, U32 data);
/*! \brief Reads the register 'DEBUG_SMEM_dram_channel_sub4'. */
U32  GH_DEBUG_SMEM_get_dram_channel_sub4(U8 index);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_FMEM_refresh_value (read/write)                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DEBUG_SMEM_FMEM_refresh_value'. */
void GH_DEBUG_SMEM_set_FMEM_refresh_value(U32 data);
/*! \brief Reads the register 'DEBUG_SMEM_FMEM_refresh_value'. */
U32  GH_DEBUG_SMEM_get_FMEM_refresh_value(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_RMB_2nd_lvl_clk_gating_disable (read/write)            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DEBUG_SMEM_RMB_2nd_lvl_clk_gating_disable'. */
void GH_DEBUG_SMEM_set_RMB_2nd_lvl_clk_gating_disable(U32 data);
/*! \brief Reads the register 'DEBUG_SMEM_RMB_2nd_lvl_clk_gating_disable'. */
U32  GH_DEBUG_SMEM_get_RMB_2nd_lvl_clk_gating_disable(void);
/*! \brief Writes the bit group 'en' of register 'DEBUG_SMEM_RMB_2nd_lvl_clk_gating_disable'. */
void GH_DEBUG_SMEM_set_RMB_2nd_lvl_clk_gating_disable_en(U16 data);
/*! \brief Reads the bit group 'en' of register 'DEBUG_SMEM_RMB_2nd_lvl_clk_gating_disable'. */
U16  GH_DEBUG_SMEM_get_RMB_2nd_lvl_clk_gating_disable_en(void);
/*! \brief Writes the bit group 'asserted' of register 'DEBUG_SMEM_RMB_2nd_lvl_clk_gating_disable'. */
void GH_DEBUG_SMEM_set_RMB_2nd_lvl_clk_gating_disable_asserted(U8 data);
/*! \brief Reads the bit group 'asserted' of register 'DEBUG_SMEM_RMB_2nd_lvl_clk_gating_disable'. */
U8   GH_DEBUG_SMEM_get_RMB_2nd_lvl_clk_gating_disable_asserted(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_DRAM_RMB_behavior (read/write)                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DEBUG_SMEM_DRAM_RMB_behavior'. */
void GH_DEBUG_SMEM_set_DRAM_RMB_behavior(U32 data);
/*! \brief Reads the register 'DEBUG_SMEM_DRAM_RMB_behavior'. */
U32  GH_DEBUG_SMEM_get_DRAM_RMB_behavior(void);
/*! \brief Writes the bit group 'DRAM_RMB' of register 'DEBUG_SMEM_DRAM_RMB_behavior'. */
void GH_DEBUG_SMEM_set_DRAM_RMB_behavior_DRAM_RMB(U8 data);
/*! \brief Reads the bit group 'DRAM_RMB' of register 'DEBUG_SMEM_DRAM_RMB_behavior'. */
U8   GH_DEBUG_SMEM_get_DRAM_RMB_behavior_DRAM_RMB(void);
/*! \brief Writes the bit group 'no_real_purpose' of register 'DEBUG_SMEM_DRAM_RMB_behavior'. */
void GH_DEBUG_SMEM_set_DRAM_RMB_behavior_no_real_purpose(U8 data);
/*! \brief Reads the bit group 'no_real_purpose' of register 'DEBUG_SMEM_DRAM_RMB_behavior'. */
U8   GH_DEBUG_SMEM_get_DRAM_RMB_behavior_no_real_purpose(void);
/*! \brief Writes the bit group 'load_data' of register 'DEBUG_SMEM_DRAM_RMB_behavior'. */
void GH_DEBUG_SMEM_set_DRAM_RMB_behavior_load_data(U8 data);
/*! \brief Reads the bit group 'load_data' of register 'DEBUG_SMEM_DRAM_RMB_behavior'. */
U8   GH_DEBUG_SMEM_get_DRAM_RMB_behavior_load_data(void);
/*! \brief Writes the bit group 'no_write_requests' of register 'DEBUG_SMEM_DRAM_RMB_behavior'. */
void GH_DEBUG_SMEM_set_DRAM_RMB_behavior_no_write_requests(U8 data);
/*! \brief Reads the bit group 'no_write_requests' of register 'DEBUG_SMEM_DRAM_RMB_behavior'. */
U8   GH_DEBUG_SMEM_get_DRAM_RMB_behavior_no_write_requests(void);
/*! \brief Writes the bit group 'best_left_alone' of register 'DEBUG_SMEM_DRAM_RMB_behavior'. */
void GH_DEBUG_SMEM_set_DRAM_RMB_behavior_best_left_alone(U8 data);
/*! \brief Reads the bit group 'best_left_alone' of register 'DEBUG_SMEM_DRAM_RMB_behavior'. */
U8   GH_DEBUG_SMEM_get_DRAM_RMB_behavior_best_left_alone(void);
/*! \brief Writes the bit group 'write_requests' of register 'DEBUG_SMEM_DRAM_RMB_behavior'. */
void GH_DEBUG_SMEM_set_DRAM_RMB_behavior_write_requests(U8 data);
/*! \brief Reads the bit group 'write_requests' of register 'DEBUG_SMEM_DRAM_RMB_behavior'. */
U8   GH_DEBUG_SMEM_get_DRAM_RMB_behavior_write_requests(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_REQQ_request_queue_status (read)                       */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_SMEM_REQQ_request_queue_status'. */
U32  GH_DEBUG_SMEM_get_REQQ_request_queue_status(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_ONET_dma_status (read)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_SMEM_ONET_dma_status'. */
U32  GH_DEBUG_SMEM_get_ONET_dma_status(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_RMB_dma_status0 (read)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_SMEM_RMB_dma_status0'. */
U32  GH_DEBUG_SMEM_get_RMB_dma_status0(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_RMB_dma_status1 (read)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_SMEM_RMB_dma_status1'. */
U32  GH_DEBUG_SMEM_get_RMB_dma_status1(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_XFER_dram_transfer_status (read)                       */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_SMEM_XFER_dram_transfer_status'. */
U32  GH_DEBUG_SMEM_get_XFER_dram_transfer_status(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_SYNC_counter_status0 (read)                            */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_SMEM_SYNC_counter_status0'. */
U32  GH_DEBUG_SMEM_get_SYNC_counter_status0(void);
/*! \brief Reads the bit group 'TH0' of register 'DEBUG_SMEM_SYNC_counter_status0'. */
U8   GH_DEBUG_SMEM_get_SYNC_counter_status0_TH0(void);
/*! \brief Reads the bit group 'TH1' of register 'DEBUG_SMEM_SYNC_counter_status0'. */
U8   GH_DEBUG_SMEM_get_SYNC_counter_status0_TH1(void);
/*! \brief Reads the bit group 'TH2' of register 'DEBUG_SMEM_SYNC_counter_status0'. */
U8   GH_DEBUG_SMEM_get_SYNC_counter_status0_TH2(void);
/*! \brief Reads the bit group 'TH3' of register 'DEBUG_SMEM_SYNC_counter_status0'. */
U8   GH_DEBUG_SMEM_get_SYNC_counter_status0_TH3(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_SYNC_counter_status1 (read)                            */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_SMEM_SYNC_counter_status1'. */
U32  GH_DEBUG_SMEM_get_SYNC_counter_status1(void);
/*! \brief Reads the bit group 'TH0' of register 'DEBUG_SMEM_SYNC_counter_status1'. */
U8   GH_DEBUG_SMEM_get_SYNC_counter_status1_TH0(void);
/*! \brief Reads the bit group 'TH1' of register 'DEBUG_SMEM_SYNC_counter_status1'. */
U8   GH_DEBUG_SMEM_get_SYNC_counter_status1_TH1(void);
/*! \brief Reads the bit group 'TH2' of register 'DEBUG_SMEM_SYNC_counter_status1'. */
U8   GH_DEBUG_SMEM_get_SYNC_counter_status1_TH2(void);
/*! \brief Reads the bit group 'TH3' of register 'DEBUG_SMEM_SYNC_counter_status1'. */
U8   GH_DEBUG_SMEM_get_SYNC_counter_status1_TH3(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_SYNC_counter_IDSP_status (read)                        */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_SMEM_SYNC_counter_IDSP_status'. */
U32  GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status(void);
/*! \brief Reads the bit group 'ID0' of register 'DEBUG_SMEM_SYNC_counter_IDSP_status'. */
U8   GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID0(void);
/*! \brief Reads the bit group 'ID1' of register 'DEBUG_SMEM_SYNC_counter_IDSP_status'. */
U8   GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID1(void);
/*! \brief Reads the bit group 'ID2' of register 'DEBUG_SMEM_SYNC_counter_IDSP_status'. */
U8   GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID2(void);
/*! \brief Reads the bit group 'ID3' of register 'DEBUG_SMEM_SYNC_counter_IDSP_status'. */
U8   GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID3(void);
/*! \brief Reads the bit group 'ID4' of register 'DEBUG_SMEM_SYNC_counter_IDSP_status'. */
U8   GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID4(void);
/*! \brief Reads the bit group 'ID5' of register 'DEBUG_SMEM_SYNC_counter_IDSP_status'. */
U8   GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID5(void);
/*! \brief Reads the bit group 'ID6' of register 'DEBUG_SMEM_SYNC_counter_IDSP_status'. */
U8   GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID6(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_SYNC_counter_VOUT_status (read)                        */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_SMEM_SYNC_counter_VOUT_status'. */
U32  GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status(void);
/*! \brief Reads the bit group 'ID0' of register 'DEBUG_SMEM_SYNC_counter_VOUT_status'. */
U8   GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID0(void);
/*! \brief Reads the bit group 'ID1' of register 'DEBUG_SMEM_SYNC_counter_VOUT_status'. */
U8   GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID1(void);
/*! \brief Reads the bit group 'ID2' of register 'DEBUG_SMEM_SYNC_counter_VOUT_status'. */
U8   GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID2(void);
/*! \brief Reads the bit group 'ID3' of register 'DEBUG_SMEM_SYNC_counter_VOUT_status'. */
U8   GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID3(void);
/*! \brief Reads the bit group 'ID4' of register 'DEBUG_SMEM_SYNC_counter_VOUT_status'. */
U8   GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID4(void);
/*! \brief Reads the bit group 'ID5' of register 'DEBUG_SMEM_SYNC_counter_VOUT_status'. */
U8   GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID5(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_ERROR_status (read/clear)                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DEBUG_SMEM_ERROR_status'. */
U32  GH_DEBUG_SMEM_get_ERROR_status(void);
/*! \brief Reads the mirror variable of the register 'DEBUG_SMEM_ERROR_status'. */
U32  GH_DEBUG_SMEM_getm_ERROR_status(void);
/*! \brief Reads the bit group 'left_right' from the mirror variable of register 'DEBUG_SMEM_ERROR_status'. */
U8   GH_DEBUG_SMEM_getm_ERROR_status_left_right(void);
/*! \brief Reads the bit group 'top_bottom' from the mirror variable of register 'DEBUG_SMEM_ERROR_status'. */
U8   GH_DEBUG_SMEM_getm_ERROR_status_top_bottom(void);
/*! \brief Reads the bit group 'reached' from the mirror variable of register 'DEBUG_SMEM_ERROR_status'. */
U8   GH_DEBUG_SMEM_getm_ERROR_status_reached(void);
/*! \brief Reads the bit group 'srows' from the mirror variable of register 'DEBUG_SMEM_ERROR_status'. */
U8   GH_DEBUG_SMEM_getm_ERROR_status_srows(void);
/*! \brief Reads the bit group 'vflip' from the mirror variable of register 'DEBUG_SMEM_ERROR_status'. */
U8   GH_DEBUG_SMEM_getm_ERROR_status_vflip(void);
/*! \brief Reads the bit group 'wider' from the mirror variable of register 'DEBUG_SMEM_ERROR_status'. */
U8   GH_DEBUG_SMEM_getm_ERROR_status_wider(void);
/*! \brief Reads the bit group 'transfers' from the mirror variable of register 'DEBUG_SMEM_ERROR_status'. */
U8   GH_DEBUG_SMEM_getm_ERROR_status_transfers(void);
/*! \brief Reads the bit group 'IDSP_sync' from the mirror variable of register 'DEBUG_SMEM_ERROR_status'. */
U8   GH_DEBUG_SMEM_getm_ERROR_status_IDSP_sync(void);
/*! \brief Reads the bit group 'VOUT_sync' from the mirror variable of register 'DEBUG_SMEM_ERROR_status'. */
U8   GH_DEBUG_SMEM_getm_ERROR_status_VOUT_sync(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_ERROR_info (read/clear)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DEBUG_SMEM_ERROR_info'. */
U32  GH_DEBUG_SMEM_get_ERROR_info(void);
/*! \brief Reads the mirror variable of the register 'DEBUG_SMEM_ERROR_info'. */
U32  GH_DEBUG_SMEM_getm_ERROR_info(void);
/*! \brief Reads the bit group 'first_error' from the mirror variable of register 'DEBUG_SMEM_ERROR_info'. */
U16  GH_DEBUG_SMEM_getm_ERROR_info_first_error(void);
/*! \brief Reads the bit group 'id' from the mirror variable of register 'DEBUG_SMEM_ERROR_info'. */
U8   GH_DEBUG_SMEM_getm_ERROR_info_id(void);
/*! \brief Reads the bit group 'valid' from the mirror variable of register 'DEBUG_SMEM_ERROR_info'. */
U8   GH_DEBUG_SMEM_getm_ERROR_info_valid(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_ERROR_mask (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DEBUG_SMEM_ERROR_mask'. */
void GH_DEBUG_SMEM_set_ERROR_mask(U32 data);
/*! \brief Reads the register 'DEBUG_SMEM_ERROR_mask'. */
U32  GH_DEBUG_SMEM_get_ERROR_mask(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_FMEM (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DEBUG_SMEM_FMEM'. */
void GH_DEBUG_SMEM_set_FMEM(U32 data);
/*! \brief Reads the register 'DEBUG_SMEM_FMEM'. */
U32  GH_DEBUG_SMEM_get_FMEM(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_DEBUG_SMEM_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_debug_smem.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_DEBUG_SMEM_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

