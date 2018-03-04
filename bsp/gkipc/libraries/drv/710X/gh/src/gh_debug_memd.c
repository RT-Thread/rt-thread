/******************************************************************************
**
** \file      gh_debug_memd.c
**
** \brief     MEMD Debug Registers.
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
#include "gh_debug_memd.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_REAL             FIO_ADDRESS(DEBUG_MEMD,0x70150000) /* read/write */
#define REG_DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR_REAL           FIO_ADDRESS(DEBUG_MEMD,0x70150004) /* write */
#define REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR_REAL           FIO_ADDRESS(DEBUG_MEMD,0x70150008) /* read/write */
#define REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL            FIO_ADDRESS(DEBUG_MEMD,0x7015000C) /* read/write */
#define REG_DEBUG_MEMD_MEMD_CR_TS_T0_ADDR_REAL              FIO_ADDRESS(DEBUG_MEMD,0x70150010) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_TS_T1_ADDR_REAL              FIO_ADDRESS(DEBUG_MEMD,0x70150014) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_TS_T2_ADDR_REAL              FIO_ADDRESS(DEBUG_MEMD,0x70150018) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_TS_T3_ADDR_REAL              FIO_ADDRESS(DEBUG_MEMD,0x7015001C) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_IS_ADDR_REAL                 FIO_ADDRESS(DEBUG_MEMD,0x70150020) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR_REAL                FIO_ADDRESS(DEBUG_MEMD,0x70150024) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_PC_T0_ADDR_REAL              FIO_ADDRESS(DEBUG_MEMD,0x70150028) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_PC_T1_ADDR_REAL              FIO_ADDRESS(DEBUG_MEMD,0x7015002C) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_PC_T2_ADDR_REAL              FIO_ADDRESS(DEBUG_MEMD,0x70150030) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_PC_T3_ADDR_REAL              FIO_ADDRESS(DEBUG_MEMD,0x70150034) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_PC_D_ADDR_REAL               FIO_ADDRESS(DEBUG_MEMD,0x70150038) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_OP_D_ADDR_REAL               FIO_ADDRESS(DEBUG_MEMD,0x7015003C) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_STALL_ADDR_REAL              FIO_ADDRESS(DEBUG_MEMD,0x70150040) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_DMAQ0_ADDR_REAL              FIO_ADDRESS(DEBUG_MEMD,0x70150044) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_DMAQ1_ADDR_REAL              FIO_ADDRESS(DEBUG_MEMD,0x70150048) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_DMAQ2_ADDR_REAL              FIO_ADDRESS(DEBUG_MEMD,0x7015004C) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_CMDQ0_ADDR_REAL              FIO_ADDRESS(DEBUG_MEMD,0x70150050) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_ME_ADDR_REAL                 FIO_ADDRESS(DEBUG_MEMD,0x70150060) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_MD_ADDR_REAL                 FIO_ADDRESS(DEBUG_MEMD,0x70150064) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_RF_ADDR_REAL                 FIO_ADDRESS(DEBUG_MEMD,0x70150800) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* DEBUG_MEMD_MEMD_CR_TRESET_ADDR */
    U32 all;
    struct {
        U32 reset                       : 4;
        U32 suspend                     : 4;
        U32                             : 23;
        U32 orc_reset                   : 1;
    } bitc;
} GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_REAL_S;

typedef union { /* DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR */
    U32 all;
    struct {
        U32 icache                      : 1;
        U32                             : 31;
    } bitc;
} GH_DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR_REAL_S;

typedef union { /* DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR */
    U32 all;
    struct {
        U32 reset                       : 32;
    } bitc;
} GH_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR_REAL_S;

typedef union { /* DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR */
    U32 all;
    struct {
        U32 mctf                        : 1;
        U32 me                          : 1;
        U32 md                          : 1;
        U32                             : 1;
        U32 mctf_hw                     : 1;
        U32 me_hw                       : 1;
        U32 md_hw                       : 1;
        U32                             : 25;
    } bitc;
} GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL_S;

typedef union { /* DEBUG_MEMD_MEMD_CR_LRU_ADDR */
    U32 all;
    struct {
        U32 entry0                      : 4;
        U32 entry1                      : 4;
        U32 entry2                      : 4;
        U32 entry3                      : 4;
        U32                             : 16;
    } bitc;
} GH_DEBUG_MEMD_MEMD_CR_LRU_ADDR_REAL_S;

typedef union { /* DEBUG_MEMD_MEMD_CR_PC_D_ADDR */
    U32 all;
    struct {
        U32 pc_d                        : 20;
        U32                             : 11;
        U32 vld_d                       : 1;
    } bitc;
} GH_DEBUG_MEMD_MEMD_CR_PC_D_ADDR_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR_S   m_debug_memd_memd_cr_ic_invld_addr;

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_TRESET_ADDR (read/write)                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR(U32 data)
{
    GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_REAL_S real;
    GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_S dummy;
    dummy.all = data ;
    real.bitc.reset = dummy.bitc.reset;
    real.bitc.suspend = dummy.bitc.suspend;
    real.bitc.orc_reset = dummy.bitc.orc_reset;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR(void)
{
    GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_REAL_S real;
    GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_REAL);

    dummy.bitc.reset = real.bitc.reset;
    dummy.bitc.suspend = real.bitc.suspend;
    dummy.bitc.orc_reset = real.bitc.orc_reset;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR_reset(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_REAL;
    d.bitc.reset = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR_reset(void)
{
    GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reset;
}
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR_suspend(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_REAL;
    d.bitc.suspend = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR_suspend(void)
{
    GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.suspend;
}
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR_ORC_reset(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_REAL;
    d.bitc.orc_reset = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR_ORC_reset(void)
{
    GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.orc_reset;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR (write)                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_IC_INVLD_ADDR(U32 data)
{
    m_debug_memd_memd_cr_ic_invld_addr.all = data;
    GH_DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR_REAL_S real;
    GH_DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR_S dummy;
    dummy.all = data ;
    real.bitc.icache = dummy.bitc.icache;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_MEMD_getm_MEMD_CR_IC_INVLD_ADDR(void)
{
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "[GH_DEBUG_MEMD_getm_MEMD_CR_IC_INVLD_ADDR] --> 0x%08x\n",
                        m_debug_memd_memd_cr_ic_invld_addr.all);
    #endif
    return m_debug_memd_memd_cr_ic_invld_addr.all;
}
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_IC_INVLD_ADDR_icache(U8 data)
{
    m_debug_memd_memd_cr_ic_invld_addr.bitc.icache = data;
    GH_DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR_REAL_S real;
    real.bitc.icache = m_debug_memd_memd_cr_ic_invld_addr.bitc.icache;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR_REAL = real.all;
}
GH_INLINE U8   GH_DEBUG_MEMD_getm_MEMD_CR_IC_INVLD_ADDR_icache(void)
{
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "[GH_DEBUG_MEMD_getm_MEMD_CR_IC_INVLD_ADDR_icache] --> 0x%08x\n",
                        m_debug_memd_memd_cr_ic_invld_addr.bitc.icache);
    #endif
    return m_debug_memd_memd_cr_ic_invld_addr.bitc.icache;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR (read/write)                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_RESET_PC_ADDR(U32 data)
{
    GH_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR_REAL_S real;
    GH_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR_S dummy;
    dummy.all = data ;
    real.bitc.reset = dummy.bitc.reset;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_RESET_PC_ADDR(void)
{
    GH_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR_REAL_S real;
    GH_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR_REAL);

    dummy.bitc.reset = real.bitc.reset;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_RESET_PC_ADDR_reset(U32 data)
{
    GH_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR_REAL;
    d.bitc.reset = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR_REAL = d.all;
}
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_RESET_PC_ADDR_reset(void)
{
    GH_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reset;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR (read/write)                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR(U32 data)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL_S real;
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S dummy;
    dummy.all = data ;
    real.bitc.mctf = dummy.bitc.mctf;
    real.bitc.me = dummy.bitc.me;
    real.bitc.md = dummy.bitc.md;
    real.bitc.mctf_hw = dummy.bitc.mctf_hw;
    real.bitc.me_hw = dummy.bitc.me_hw;
    real.bitc.md_hw = dummy.bitc.md_hw;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR(void)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL_S real;
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL);

    dummy.bitc.mctf = real.bitc.mctf;
    dummy.bitc.me = real.bitc.me;
    dummy.bitc.md = real.bitc.md;
    dummy.bitc.mctf_hw = real.bitc.mctf_hw;
    dummy.bitc.me_hw = real.bitc.me_hw;
    dummy.bitc.md_hw = real.bitc.md_hw;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MCTF(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL;
    d.bitc.mctf = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MCTF(void)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mctf;
}
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_ME(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL;
    d.bitc.me = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_ME(void)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.me;
}
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MD(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL;
    d.bitc.md = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MD(void)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.md;
}
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MCTF_HW(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL;
    d.bitc.mctf_hw = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MCTF_HW(void)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mctf_hw;
}
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_ME_HW(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL;
    d.bitc.me_hw = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_ME_HW(void)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.me_hw;
}
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MD_HW(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL;
    d.bitc.md_hw = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MD_HW(void)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.md_hw;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_TS_T0_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_TS_T0_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TS_T0_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_TS_T1_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_TS_T1_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TS_T1_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_TS_T2_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_TS_T2_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TS_T2_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_TS_T3_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_TS_T3_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TS_T3_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_IS_ADDR (read)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_IS_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_IS_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_LRU_ADDR (read)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR(void)
{
    GH_DEBUG_MEMD_MEMD_CR_LRU_ADDR_REAL_S real;
    GH_DEBUG_MEMD_MEMD_CR_LRU_ADDR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR_REAL);

    dummy.bitc.entry0 = real.bitc.entry0;
    dummy.bitc.entry1 = real.bitc.entry1;
    dummy.bitc.entry2 = real.bitc.entry2;
    dummy.bitc.entry3 = real.bitc.entry3;
    return dummy.all;
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry0(void)
{
    GH_DEBUG_MEMD_MEMD_CR_LRU_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.entry0;
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry1(void)
{
    GH_DEBUG_MEMD_MEMD_CR_LRU_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.entry1;
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry2(void)
{
    GH_DEBUG_MEMD_MEMD_CR_LRU_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.entry2;
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry3(void)
{
    GH_DEBUG_MEMD_MEMD_CR_LRU_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.entry3;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_PC_T0_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_T0_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_PC_T0_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_PC_T1_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_T1_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_PC_T1_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_PC_T2_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_T2_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_PC_T2_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_PC_T3_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_T3_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_PC_T3_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_PC_D_ADDR (read)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_D_ADDR(void)
{
    GH_DEBUG_MEMD_MEMD_CR_PC_D_ADDR_REAL_S real;
    GH_DEBUG_MEMD_MEMD_CR_PC_D_ADDR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_PC_D_ADDR_REAL);

    dummy.bitc.pc_d = real.bitc.pc_d;
    dummy.bitc.vld_d = real.bitc.vld_d;
    return dummy.all;
}
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_D_ADDR_pc_d(void)
{
    GH_DEBUG_MEMD_MEMD_CR_PC_D_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_PC_D_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pc_d;
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_PC_D_ADDR_vld_d(void)
{
    GH_DEBUG_MEMD_MEMD_CR_PC_D_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_PC_D_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vld_d;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_OP_D_ADDR (read)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_OP_D_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_OP_D_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_STALL_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_STALL_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_STALL_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_DMAQ0_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_DMAQ0_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_DMAQ0_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_DMAQ1_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_DMAQ1_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_DMAQ1_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_DMAQ2_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_DMAQ2_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_DMAQ2_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_CMDQ0_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_CMDQ0_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CMDQ0_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_ME_ADDR (read)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_ME_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_ME_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_MD_ADDR (read)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_MD_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_MD_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_RF_ADDR (read/write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_RF_ADDR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_RF_ADDR_REAL = data;
}
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_RF_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_RF_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_MEMD_init(void)
{
    GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR((U32)0x00000000);
    GH_DEBUG_MEMD_set_MEMD_CR_IC_INVLD_ADDR((U32)0x00000000);
    GH_DEBUG_MEMD_set_MEMD_CR_RESET_PC_ADDR((U32)0x00000000);
    GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR((U32)0x00000000);
    GH_DEBUG_MEMD_set_MEMD_CR_RF_ADDR((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

