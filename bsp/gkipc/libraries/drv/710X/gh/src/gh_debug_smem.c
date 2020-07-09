/******************************************************************************
**
** \file      gh_debug_smem.c
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
#ifndef SRC_INLINE
#include "gh_debug_smem.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB0_START_REAL     FIO_ADDRESS(DEBUG_SMEM,0x70100000) /* read/write */
#define REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB1_START_REAL     FIO_ADDRESS(DEBUG_SMEM,0x70100400) /* read/write */
#define REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB2_START_REAL     FIO_ADDRESS(DEBUG_SMEM,0x70100800) /* read/write */
#define REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB3_START_REAL     FIO_ADDRESS(DEBUG_SMEM,0x70100C00) /* read/write */
#define REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB4_START_REAL     FIO_ADDRESS(DEBUG_SMEM,0x70101000) /* read/write */
#define REG_DEBUG_SMEM_SYNC_COUNTER_REAL                    FIO_ADDRESS(DEBUG_SMEM,0x70101000) /* read/write */
#define REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL               FIO_ADDRESS(DEBUG_SMEM,0x70104000) /* read/write */
#define REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1_REAL               FIO_ADDRESS(DEBUG_SMEM,0x70104400) /* read/write */
#define REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL               FIO_ADDRESS(DEBUG_SMEM,0x70104800) /* read/write */
#define REG_DEBUG_SMEM_DRAM_CHANNEL_SUB3_REAL               FIO_ADDRESS(DEBUG_SMEM,0x70104C00) /* read/write */
#define REG_DEBUG_SMEM_DRAM_CHANNEL_SUB4_REAL               FIO_ADDRESS(DEBUG_SMEM,0x70105000) /* read/write */
#define REG_DEBUG_SMEM_FMEM_REFRESH_VALUE_REAL              FIO_ADDRESS(DEBUG_SMEM,0x70108080) /* read/write */
#define REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_REAL  FIO_ADDRESS(DEBUG_SMEM,0x701080A0) /* read/write */
#define REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL               FIO_ADDRESS(DEBUG_SMEM,0x701080A4) /* read/write */
#define REG_DEBUG_SMEM_REQQ_REQUEST_QUEUE_STATUS_REAL       FIO_ADDRESS(DEBUG_SMEM,0x70108100) /* read */
#define REG_DEBUG_SMEM_ONET_DMA_STATUS_REAL                 FIO_ADDRESS(DEBUG_SMEM,0x70108104) /* read */
#define REG_DEBUG_SMEM_RMB_DMA_STATUS0_REAL                 FIO_ADDRESS(DEBUG_SMEM,0x70108108) /* read */
#define REG_DEBUG_SMEM_RMB_DMA_STATUS1_REAL                 FIO_ADDRESS(DEBUG_SMEM,0x7010810C) /* read */
#define REG_DEBUG_SMEM_XFER_DRAM_TRANSFER_STATUS_REAL       FIO_ADDRESS(DEBUG_SMEM,0x70108110) /* read */
#define REG_DEBUG_SMEM_SYNC_COUNTER_STATUS0_REAL            FIO_ADDRESS(DEBUG_SMEM,0x70108114) /* read */
#define REG_DEBUG_SMEM_SYNC_COUNTER_STATUS1_REAL            FIO_ADDRESS(DEBUG_SMEM,0x70108118) /* read */
#define REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_REAL        FIO_ADDRESS(DEBUG_SMEM,0x7010811C) /* read */
#define REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_REAL        FIO_ADDRESS(DEBUG_SMEM,0x70108120) /* read */
#define REG_DEBUG_SMEM_ERROR_STATUS_REAL                    FIO_ADDRESS(DEBUG_SMEM,0x70108140) /* read/clear */
#define REG_DEBUG_SMEM_ERROR_INFO_REAL                      FIO_ADDRESS(DEBUG_SMEM,0x70108150) /* read/clear */
#define REG_DEBUG_SMEM_ERROR_MASK_REAL                      FIO_ADDRESS(DEBUG_SMEM,0x70108160) /* read/write */
#define REG_DEBUG_SMEM_FMEM_REAL                            FIO_ADDRESS(DEBUG_SMEM,0x70200000) /* read/write */

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
} GH_DEBUG_SMEM_SYNC_COUNTER_REAL_S;

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
} GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL_S;

typedef union { /* DEBUG_SMEM_dram_channel_sub1 */
    U32 all;
    struct {
        U32 dcol                        : 14;
        U32                             : 2;
        U32 drow                        : 9;
        U32                             : 7;
    } bitc;
} GH_DEBUG_SMEM_DRAM_CHANNEL_SUB1_REAL_S;

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
} GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL_S;

typedef union { /* DEBUG_SMEM_RMB_2nd_lvl_clk_gating_disable */
    U32 all;
    struct {
        U32 en                          : 16;
        U32 asserted                    : 3;
        U32                             : 13;
    } bitc;
} GH_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_REAL_S;

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
} GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL_S;

typedef union { /* DEBUG_SMEM_SYNC_counter_status0 */
    U32 all;
    struct {
        U32 th0                         : 3;
        U32 th1                         : 3;
        U32 th2                         : 3;
        U32 th3                         : 3;
        U32                             : 20;
    } bitc;
} GH_DEBUG_SMEM_SYNC_COUNTER_STATUS0_REAL_S;

typedef union { /* DEBUG_SMEM_SYNC_counter_status1 */
    U32 all;
    struct {
        U32 th0                         : 3;
        U32 th1                         : 3;
        U32 th2                         : 3;
        U32 th3                         : 3;
        U32                             : 20;
    } bitc;
} GH_DEBUG_SMEM_SYNC_COUNTER_STATUS1_REAL_S;

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
} GH_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_REAL_S;

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
} GH_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_REAL_S;

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
} GH_DEBUG_SMEM_ERROR_STATUS_REAL_S;

typedef union { /* DEBUG_SMEM_ERROR_info */
    U32 all;
    struct {
        U32 first_error                 : 13;
        U32                             : 3;
        U32 id                          : 4;
        U32                             : 11;
        U32 valid                       : 1;
    } bitc;
} GH_DEBUG_SMEM_ERROR_INFO_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_DEBUG_SMEM_ERROR_STATUS_S            m_debug_smem_error_status;
GH_DEBUG_SMEM_ERROR_INFO_S              m_debug_smem_error_info;

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_smem_channel_reg_sub0_start (read/write)               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_SMEM_set_smem_channel_reg_sub0_start(U16 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB0_START_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = data;
}
GH_INLINE U32  GH_DEBUG_SMEM_get_smem_channel_reg_sub0_start(U16 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB0_START_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_smem_channel_reg_sub1_start (read/write)               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_SMEM_set_smem_channel_reg_sub1_start(U16 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB1_START_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = data;
}
GH_INLINE U32  GH_DEBUG_SMEM_get_smem_channel_reg_sub1_start(U16 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB1_START_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_smem_channel_reg_sub2_start (read/write)               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_SMEM_set_smem_channel_reg_sub2_start(U16 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB2_START_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = data;
}
GH_INLINE U32  GH_DEBUG_SMEM_get_smem_channel_reg_sub2_start(U16 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB2_START_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_smem_channel_reg_sub3_start (read/write)               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_SMEM_set_smem_channel_reg_sub3_start(U16 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB3_START_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = data;
}
GH_INLINE U32  GH_DEBUG_SMEM_get_smem_channel_reg_sub3_start(U16 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB3_START_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_smem_channel_reg_sub4_start (read/write)               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_SMEM_set_smem_channel_reg_sub4_start(U16 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB4_START_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = data;
}
GH_INLINE U32  GH_DEBUG_SMEM_get_smem_channel_reg_sub4_start(U16 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB4_START_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_sync_counter (read/write)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_SMEM_set_sync_counter(U8 index, U32 data)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_REAL_S real;
    GH_DEBUG_SMEM_SYNC_COUNTER_S dummy;
    dummy.all = data ;
    real.bitc.max = dummy.bitc.max;
    real.bitc.count = dummy.bitc.count;
    real.bitc.max_notchange = dummy.bitc.max_notchange;
    real.bitc.value_notchange = dummy.bitc.value_notchange;
    *(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = real.all;
}
GH_INLINE U32  GH_DEBUG_SMEM_get_sync_counter(U8 index)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_REAL_S real;
    GH_DEBUG_SMEM_SYNC_COUNTER_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    dummy.bitc.max = real.bitc.max;
    dummy.bitc.count = real.bitc.count;
    dummy.bitc.max_notchange = real.bitc.max_notchange;
    dummy.bitc.value_notchange = real.bitc.value_notchange;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_SMEM_set_sync_counter_max(U8 index, U8 data)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_REAL_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.max = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_sync_counter_max(U8 index)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.max;
}
GH_INLINE void GH_DEBUG_SMEM_set_sync_counter_count(U8 index, U8 data)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_REAL_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.count = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_sync_counter_count(U8 index)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.count;
}
GH_INLINE void GH_DEBUG_SMEM_set_sync_counter_max_notchange(U8 index, U8 data)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_REAL_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.max_notchange = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_sync_counter_max_notchange(U8 index)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.max_notchange;
}
GH_INLINE void GH_DEBUG_SMEM_set_sync_counter_value_notchange(U8 index, U8 data)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_REAL_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.value_notchange = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_sync_counter_value_notchange(U8 index)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.value_notchange;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_dram_channel_sub0 (read/write)                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_SMEM_set_dram_channel_sub0(U8 index, U32 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL_S real;
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_S dummy;
    dummy.all = data ;
    real.bitc.dpitch = dummy.bitc.dpitch;
    real.bitc.drowmax = dummy.bitc.drowmax;
    real.bitc.dpriority = dummy.bitc.dpriority;
    real.bitc.dramdisable = dummy.bitc.dramdisable;
    real.bitc.nextdramdisable = dummy.bitc.nextdramdisable;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = real.all;
}
GH_INLINE U32  GH_DEBUG_SMEM_get_dram_channel_sub0(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL_S real;
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    dummy.bitc.dpitch = real.bitc.dpitch;
    dummy.bitc.drowmax = real.bitc.drowmax;
    dummy.bitc.dpriority = real.bitc.dpriority;
    dummy.bitc.dramdisable = real.bitc.dramdisable;
    dummy.bitc.nextdramdisable = real.bitc.nextdramdisable;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_SMEM_set_dram_channel_sub0_dpitch(U8 index, U16 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.dpitch = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
}
GH_INLINE U16  GH_DEBUG_SMEM_get_dram_channel_sub0_dpitch(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.dpitch;
}
GH_INLINE void GH_DEBUG_SMEM_set_dram_channel_sub0_drowmax(U8 index, U16 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.drowmax = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
}
GH_INLINE U16  GH_DEBUG_SMEM_get_dram_channel_sub0_drowmax(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.drowmax;
}
GH_INLINE void GH_DEBUG_SMEM_set_dram_channel_sub0_dpriority(U8 index, U8 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.dpriority = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_dram_channel_sub0_dpriority(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.dpriority;
}
GH_INLINE void GH_DEBUG_SMEM_set_dram_channel_sub0_dramDisable(U8 index, U8 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.dramdisable = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_dram_channel_sub0_dramDisable(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.dramdisable;
}
GH_INLINE void GH_DEBUG_SMEM_set_dram_channel_sub0_nextDramDisable(U8 index, U8 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.nextdramdisable = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_dram_channel_sub0_nextDramDisable(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.nextdramdisable;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_dram_channel_sub1 (read/write)                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_SMEM_set_dram_channel_sub1(U8 index, U32 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB1_REAL_S real;
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB1_S dummy;
    dummy.all = data ;
    real.bitc.dcol = dummy.bitc.dcol;
    real.bitc.drow = dummy.bitc.drow;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = real.all;
}
GH_INLINE U32  GH_DEBUG_SMEM_get_dram_channel_sub1(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB1_REAL_S real;
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    dummy.bitc.dcol = real.bitc.dcol;
    dummy.bitc.drow = real.bitc.drow;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_SMEM_set_dram_channel_sub1_dcol(U8 index, U16 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB1_REAL_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.dcol = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
}
GH_INLINE U16  GH_DEBUG_SMEM_get_dram_channel_sub1_dcol(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.dcol;
}
GH_INLINE void GH_DEBUG_SMEM_set_dram_channel_sub1_drow(U8 index, U16 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB1_REAL_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.drow = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
}
GH_INLINE U16  GH_DEBUG_SMEM_get_dram_channel_sub1_drow(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.drow;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_dram_channel_sub2 (read/write)                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_SMEM_set_dram_channel_sub2(U8 index, U32 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL_S real;
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_S dummy;
    dummy.all = data ;
    real.bitc.dsrowcol = dummy.bitc.dsrowcol;
    real.bitc.dscliprow = dummy.bitc.dscliprow;
    real.bitc.ddrepeatrow = dummy.bitc.ddrepeatrow;
    real.bitc.dtileenable = dummy.bitc.dtileenable;
    real.bitc.dtilefield = dummy.bitc.dtilefield;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = real.all;
}
GH_INLINE U32  GH_DEBUG_SMEM_get_dram_channel_sub2(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL_S real;
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    dummy.bitc.dsrowcol = real.bitc.dsrowcol;
    dummy.bitc.dscliprow = real.bitc.dscliprow;
    dummy.bitc.ddrepeatrow = real.bitc.ddrepeatrow;
    dummy.bitc.dtileenable = real.bitc.dtileenable;
    dummy.bitc.dtilefield = real.bitc.dtilefield;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_SMEM_set_dram_channel_sub2_dsrowcol(U8 index, U16 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.dsrowcol = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
}
GH_INLINE U16  GH_DEBUG_SMEM_get_dram_channel_sub2_dsrowcol(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.dsrowcol;
}
GH_INLINE void GH_DEBUG_SMEM_set_dram_channel_sub2_dscliprow(U8 index, U16 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.dscliprow = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
}
GH_INLINE U16  GH_DEBUG_SMEM_get_dram_channel_sub2_dscliprow(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.dscliprow;
}
GH_INLINE void GH_DEBUG_SMEM_set_dram_channel_sub2_ddrepeatRow(U8 index, U8 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.ddrepeatrow = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_dram_channel_sub2_ddrepeatRow(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.ddrepeatrow;
}
GH_INLINE void GH_DEBUG_SMEM_set_dram_channel_sub2_dtileEnable(U8 index, U8 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.dtileenable = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_dram_channel_sub2_dtileEnable(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.dtileenable;
}
GH_INLINE void GH_DEBUG_SMEM_set_dram_channel_sub2_dtileField(U8 index, U8 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.dtilefield = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_dram_channel_sub2_dtileField(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    return tmp_value.bitc.dtilefield;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_dram_channel_sub3 (read/write)                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_SMEM_set_dram_channel_sub3(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB3_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = data;
}
GH_INLINE U32  GH_DEBUG_SMEM_get_dram_channel_sub3(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB3_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_dram_channel_sub4 (read/write)                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_SMEM_set_dram_channel_sub4(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB4_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = data;
}
GH_INLINE U32  GH_DEBUG_SMEM_get_dram_channel_sub4(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB4_REAL + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_FMEM_refresh_value (read/write)                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_SMEM_set_FMEM_refresh_value(U32 data)
{
    *(volatile U32 *)REG_DEBUG_SMEM_FMEM_REFRESH_VALUE_REAL = data;
}
GH_INLINE U32  GH_DEBUG_SMEM_get_FMEM_refresh_value(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_FMEM_REFRESH_VALUE_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_RMB_2nd_lvl_clk_gating_disable (read/write)            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_SMEM_set_RMB_2nd_lvl_clk_gating_disable(U32 data)
{
    GH_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_REAL_S real;
    GH_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_S dummy;
    dummy.all = data ;
    real.bitc.en = dummy.bitc.en;
    real.bitc.asserted = dummy.bitc.asserted;
    *(volatile U32 *)REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_SMEM_get_RMB_2nd_lvl_clk_gating_disable(void)
{
    GH_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_REAL_S real;
    GH_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_REAL);

    dummy.bitc.en = real.bitc.en;
    dummy.bitc.asserted = real.bitc.asserted;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_SMEM_set_RMB_2nd_lvl_clk_gating_disable_en(U16 data)
{
    GH_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_REAL;
    d.bitc.en = data;
    *(volatile U32 *)REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_SMEM_get_RMB_2nd_lvl_clk_gating_disable_en(void)
{
    GH_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en;
}
GH_INLINE void GH_DEBUG_SMEM_set_RMB_2nd_lvl_clk_gating_disable_asserted(U8 data)
{
    GH_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_REAL;
    d.bitc.asserted = data;
    *(volatile U32 *)REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_RMB_2nd_lvl_clk_gating_disable_asserted(void)
{
    GH_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.asserted;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_DRAM_RMB_behavior (read/write)                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_SMEM_set_DRAM_RMB_behavior(U32 data)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL_S real;
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_S dummy;
    dummy.all = data ;
    real.bitc.dram_rmb = dummy.bitc.dram_rmb;
    real.bitc.no_real_purpose = dummy.bitc.no_real_purpose;
    real.bitc.load_data = dummy.bitc.load_data;
    real.bitc.no_write_requests = dummy.bitc.no_write_requests;
    real.bitc.best_left_alone = dummy.bitc.best_left_alone;
    real.bitc.write_requests = dummy.bitc.write_requests;
    *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_SMEM_get_DRAM_RMB_behavior(void)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL_S real;
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL);

    dummy.bitc.dram_rmb = real.bitc.dram_rmb;
    dummy.bitc.no_real_purpose = real.bitc.no_real_purpose;
    dummy.bitc.load_data = real.bitc.load_data;
    dummy.bitc.no_write_requests = real.bitc.no_write_requests;
    dummy.bitc.best_left_alone = real.bitc.best_left_alone;
    dummy.bitc.write_requests = real.bitc.write_requests;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_SMEM_set_DRAM_RMB_behavior_DRAM_RMB(U8 data)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL;
    d.bitc.dram_rmb = data;
    *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_DRAM_RMB_behavior_DRAM_RMB(void)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dram_rmb;
}
GH_INLINE void GH_DEBUG_SMEM_set_DRAM_RMB_behavior_no_real_purpose(U8 data)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL;
    d.bitc.no_real_purpose = data;
    *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_DRAM_RMB_behavior_no_real_purpose(void)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.no_real_purpose;
}
GH_INLINE void GH_DEBUG_SMEM_set_DRAM_RMB_behavior_load_data(U8 data)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL;
    d.bitc.load_data = data;
    *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_DRAM_RMB_behavior_load_data(void)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.load_data;
}
GH_INLINE void GH_DEBUG_SMEM_set_DRAM_RMB_behavior_no_write_requests(U8 data)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL;
    d.bitc.no_write_requests = data;
    *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_DRAM_RMB_behavior_no_write_requests(void)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.no_write_requests;
}
GH_INLINE void GH_DEBUG_SMEM_set_DRAM_RMB_behavior_best_left_alone(U8 data)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL;
    d.bitc.best_left_alone = data;
    *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_DRAM_RMB_behavior_best_left_alone(void)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.best_left_alone;
}
GH_INLINE void GH_DEBUG_SMEM_set_DRAM_RMB_behavior_write_requests(U8 data)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL;
    d.bitc.write_requests = data;
    *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_DRAM_RMB_behavior_write_requests(void)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.write_requests;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_REQQ_request_queue_status (read)                       */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_SMEM_get_REQQ_request_queue_status(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_REQQ_REQUEST_QUEUE_STATUS_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_ONET_dma_status (read)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_SMEM_get_ONET_dma_status(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_ONET_DMA_STATUS_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_RMB_dma_status0 (read)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_SMEM_get_RMB_dma_status0(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_RMB_DMA_STATUS0_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_RMB_dma_status1 (read)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_SMEM_get_RMB_dma_status1(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_RMB_DMA_STATUS1_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_XFER_dram_transfer_status (read)                       */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_SMEM_get_XFER_dram_transfer_status(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_XFER_DRAM_TRANSFER_STATUS_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_SYNC_counter_status0 (read)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_SMEM_get_SYNC_counter_status0(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_STATUS0_REAL_S real;
    GH_DEBUG_SMEM_SYNC_COUNTER_STATUS0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_STATUS0_REAL);

    dummy.bitc.th0 = real.bitc.th0;
    dummy.bitc.th1 = real.bitc.th1;
    dummy.bitc.th2 = real.bitc.th2;
    dummy.bitc.th3 = real.bitc.th3;
    return dummy.all;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_SYNC_counter_status0_TH0(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_STATUS0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_STATUS0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.th0;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_SYNC_counter_status0_TH1(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_STATUS0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_STATUS0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.th1;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_SYNC_counter_status0_TH2(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_STATUS0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_STATUS0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.th2;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_SYNC_counter_status0_TH3(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_STATUS0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_STATUS0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.th3;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_SYNC_counter_status1 (read)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_SMEM_get_SYNC_counter_status1(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_STATUS1_REAL_S real;
    GH_DEBUG_SMEM_SYNC_COUNTER_STATUS1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_STATUS1_REAL);

    dummy.bitc.th0 = real.bitc.th0;
    dummy.bitc.th1 = real.bitc.th1;
    dummy.bitc.th2 = real.bitc.th2;
    dummy.bitc.th3 = real.bitc.th3;
    return dummy.all;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_SYNC_counter_status1_TH0(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_STATUS1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_STATUS1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.th0;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_SYNC_counter_status1_TH1(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_STATUS1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_STATUS1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.th1;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_SYNC_counter_status1_TH2(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_STATUS1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_STATUS1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.th2;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_SYNC_counter_status1_TH3(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_STATUS1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_STATUS1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.th3;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_SYNC_counter_IDSP_status (read)                        */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_REAL_S real;
    GH_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_REAL);

    dummy.bitc.id0 = real.bitc.id0;
    dummy.bitc.id1 = real.bitc.id1;
    dummy.bitc.id2 = real.bitc.id2;
    dummy.bitc.id3 = real.bitc.id3;
    dummy.bitc.id4 = real.bitc.id4;
    dummy.bitc.id5 = real.bitc.id5;
    dummy.bitc.id6 = real.bitc.id6;
    return dummy.all;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID0(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.id0;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID1(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.id1;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID2(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.id2;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID3(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.id3;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID4(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.id4;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID5(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.id5;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID6(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.id6;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_SYNC_counter_VOUT_status (read)                        */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_REAL_S real;
    GH_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_REAL);

    dummy.bitc.id0 = real.bitc.id0;
    dummy.bitc.id1 = real.bitc.id1;
    dummy.bitc.id2 = real.bitc.id2;
    dummy.bitc.id3 = real.bitc.id3;
    dummy.bitc.id4 = real.bitc.id4;
    dummy.bitc.id5 = real.bitc.id5;
    return dummy.all;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID0(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.id0;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID1(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.id1;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID2(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.id2;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID3(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.id3;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID4(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.id4;
}
GH_INLINE U8   GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID5(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.id5;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_ERROR_status (read/clear)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_SMEM_get_ERROR_status(void)
{
    GH_DEBUG_SMEM_ERROR_STATUS_REAL_S real;
    GH_DEBUG_SMEM_ERROR_STATUS_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_SMEM_ERROR_STATUS_REAL);

    dummy.bitc.left_right = real.bitc.left_right;
    dummy.bitc.top_bottom = real.bitc.top_bottom;
    dummy.bitc.reached = real.bitc.reached;
    dummy.bitc.srows = real.bitc.srows;
    dummy.bitc.vflip = real.bitc.vflip;
    dummy.bitc.wider = real.bitc.wider;
    dummy.bitc.transfers = real.bitc.transfers;
    dummy.bitc.idsp_sync = real.bitc.idsp_sync;
    dummy.bitc.vout_sync = real.bitc.vout_sync;
    m_debug_smem_error_status.all = dummy.all;
    return dummy.all;
}
GH_INLINE U32  GH_DEBUG_SMEM_getm_ERROR_status(void)
{
    return m_debug_smem_error_status.all;
}
GH_INLINE U8   GH_DEBUG_SMEM_getm_ERROR_status_left_right(void)
{
    return m_debug_smem_error_status.bitc.left_right;
}
GH_INLINE U8   GH_DEBUG_SMEM_getm_ERROR_status_top_bottom(void)
{
    return m_debug_smem_error_status.bitc.top_bottom;
}
GH_INLINE U8   GH_DEBUG_SMEM_getm_ERROR_status_reached(void)
{
    return m_debug_smem_error_status.bitc.reached;
}
GH_INLINE U8   GH_DEBUG_SMEM_getm_ERROR_status_srows(void)
{
    return m_debug_smem_error_status.bitc.srows;
}
GH_INLINE U8   GH_DEBUG_SMEM_getm_ERROR_status_vflip(void)
{
    return m_debug_smem_error_status.bitc.vflip;
}
GH_INLINE U8   GH_DEBUG_SMEM_getm_ERROR_status_wider(void)
{
    return m_debug_smem_error_status.bitc.wider;
}
GH_INLINE U8   GH_DEBUG_SMEM_getm_ERROR_status_transfers(void)
{
    return m_debug_smem_error_status.bitc.transfers;
}
GH_INLINE U8   GH_DEBUG_SMEM_getm_ERROR_status_IDSP_sync(void)
{
    return m_debug_smem_error_status.bitc.idsp_sync;
}
GH_INLINE U8   GH_DEBUG_SMEM_getm_ERROR_status_VOUT_sync(void)
{
    return m_debug_smem_error_status.bitc.vout_sync;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_ERROR_info (read/clear)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_SMEM_get_ERROR_info(void)
{
    GH_DEBUG_SMEM_ERROR_INFO_REAL_S real;
    GH_DEBUG_SMEM_ERROR_INFO_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_SMEM_ERROR_INFO_REAL);

    dummy.bitc.first_error = real.bitc.first_error;
    dummy.bitc.id = real.bitc.id;
    dummy.bitc.valid = real.bitc.valid;
    m_debug_smem_error_info.all = dummy.all;
    return dummy.all;
}
GH_INLINE U32  GH_DEBUG_SMEM_getm_ERROR_info(void)
{
    return m_debug_smem_error_info.all;
}
GH_INLINE U16  GH_DEBUG_SMEM_getm_ERROR_info_first_error(void)
{
    return m_debug_smem_error_info.bitc.first_error;
}
GH_INLINE U8   GH_DEBUG_SMEM_getm_ERROR_info_id(void)
{
    return m_debug_smem_error_info.bitc.id;
}
GH_INLINE U8   GH_DEBUG_SMEM_getm_ERROR_info_valid(void)
{
    return m_debug_smem_error_info.bitc.valid;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_ERROR_mask (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_SMEM_set_ERROR_mask(U32 data)
{
    *(volatile U32 *)REG_DEBUG_SMEM_ERROR_MASK_REAL = data;
}
GH_INLINE U32  GH_DEBUG_SMEM_get_ERROR_mask(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_ERROR_MASK_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_FMEM (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_SMEM_set_FMEM(U32 data)
{
    *(volatile U32 *)REG_DEBUG_SMEM_FMEM_REAL = data;
}
GH_INLINE U32  GH_DEBUG_SMEM_get_FMEM(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_FMEM_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_SMEM_init(void)
{
    int i;

    for (i=0; i<256; i++)
    {
        GH_DEBUG_SMEM_set_smem_channel_reg_sub0_start(i, (U32)0x00000000);
    }
    for (i=0; i<256; i++)
    {
        GH_DEBUG_SMEM_set_smem_channel_reg_sub1_start(i, (U32)0x00000000);
    }
    for (i=0; i<256; i++)
    {
        GH_DEBUG_SMEM_set_smem_channel_reg_sub2_start(i, (U32)0x00000000);
    }
    for (i=0; i<256; i++)
    {
        GH_DEBUG_SMEM_set_smem_channel_reg_sub3_start(i, (U32)0x00000000);
    }
    for (i=0; i<256; i++)
    {
        GH_DEBUG_SMEM_set_smem_channel_reg_sub4_start(i, (U32)0x00000000);
    }
    for (i=0; i<32; i++)
    {
        GH_DEBUG_SMEM_set_sync_counter(i, (U32)0x00000000);
    }
    for (i=0; i<128; i++)
    {
        GH_DEBUG_SMEM_set_dram_channel_sub0(i, (U32)0x00000000);
    }
    for (i=0; i<128; i++)
    {
        GH_DEBUG_SMEM_set_dram_channel_sub1(i, (U32)0x00000000);
    }
    for (i=0; i<128; i++)
    {
        GH_DEBUG_SMEM_set_dram_channel_sub2(i, (U32)0x00000000);
    }
    for (i=0; i<128; i++)
    {
        GH_DEBUG_SMEM_set_dram_channel_sub3(i, (U32)0x00000000);
    }
    for (i=0; i<128; i++)
    {
        GH_DEBUG_SMEM_set_dram_channel_sub4(i, (U32)0x00000000);
    }
    GH_DEBUG_SMEM_set_FMEM_refresh_value((U32)0x00000000);
    GH_DEBUG_SMEM_set_RMB_2nd_lvl_clk_gating_disable((U32)0x00000000);
    GH_DEBUG_SMEM_set_DRAM_RMB_behavior((U32)0x00000000);
    GH_DEBUG_SMEM_set_ERROR_mask((U32)0x00000000);
    GH_DEBUG_SMEM_set_FMEM((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
    GH_DEBUG_SMEM_get_ERROR_status();
    GH_DEBUG_SMEM_get_ERROR_info();
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

