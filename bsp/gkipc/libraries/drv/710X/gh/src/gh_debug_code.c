/******************************************************************************
**
** \file      gh_debug_code.c
**
** \brief     CODE Debug Registers.
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
#include "gh_debug_code.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_DEBUG_CODE_CODE_CR_TRESET_ADDR_REAL             FIO_ADDRESS(DEBUG_CODE,0x70160000) /* read/write */
#define REG_DEBUG_CODE_CODE_CR_IC_INVLD_ADDR_REAL           FIO_ADDRESS(DEBUG_CODE,0x70160004) /* write */
#define REG_DEBUG_CODE_CODE_CR_RESET_PC_ADDR_REAL           FIO_ADDRESS(DEBUG_CODE,0x70160008) /* read/write */
#define REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL                 FIO_ADDRESS(DEBUG_CODE,0x70160010) /* read */
#define REG_DEBUG_CODE_CODE_CR_PC_T0_ADDR_REAL              FIO_ADDRESS(DEBUG_CODE,0x70160020) /* read */
#define REG_DEBUG_CODE_CODE_CR_PC_T1_ADDR_REAL              FIO_ADDRESS(DEBUG_CODE,0x70160024) /* read */
#define REG_DEBUG_CODE_CODE_CR_PC_T2_ADDR_REAL              FIO_ADDRESS(DEBUG_CODE,0x70160028) /* read */
#define REG_DEBUG_CODE_CODE_CR_PC_T3_ADDR_REAL              FIO_ADDRESS(DEBUG_CODE,0x7016002C) /* read */
#define REG_DEBUG_CODE_CODE_CR_STALL_ADDR_REAL              FIO_ADDRESS(DEBUG_CODE,0x70160038) /* read */
#define REG_DEBUG_CODE_CODE_CR_RF_ADDR_REAL                 FIO_ADDRESS(DEBUG_CODE,0x70160200) /* read */
#define REG_DEBUG_CODE_CODE_CR_DC_ADDR_REAL                 FIO_ADDRESS(DEBUG_CODE,0x70164000) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* DEBUG_CODE_CODE_CR_IC_INVLD_ADDR */
    U32 all;
    struct {
        U32 invalid_icache              : 1;
        U32                             : 31;
    } bitc;
} GH_DEBUG_CODE_CODE_CR_IC_INVLD_ADDR_REAL_S;

typedef union { /* DEBUG_CODE_CODE_CR_TS_ADDR */
    U32 all;
    struct {
        U32 ts_t0_run                   : 1;
        U32 ts_t0_restmr                : 1;
        U32 ts_t0_dmab4                 : 1;
        U32 ts_t0_codeb4                : 1;
        U32 ts_t0_sendb4                : 1;
        U32 ts_t0_recb4                 : 1;
        U32                             : 2;
        U32 ts_t1_run                   : 1;
        U32 ts_t1_restmr                : 1;
        U32 ts_t1_dmab4                 : 1;
        U32 ts_t1_codeb4                : 1;
        U32 ts_t1_sendb4                : 1;
        U32 ts_t1_recb4                 : 1;
        U32                             : 2;
        U32 ts_t2_run                   : 1;
        U32 ts_t2_restmr                : 1;
        U32 ts_t2_dmab4                 : 1;
        U32 ts_t2_codeb4                : 1;
        U32 ts_t2_sendb4                : 1;
        U32 ts_t2_recb4                 : 1;
        U32                             : 2;
        U32 ts_t3_run                   : 1;
        U32 ts_t3_restmr                : 1;
        U32 ts_t3_dmab4                 : 1;
        U32 ts_t3_codeb4                : 1;
        U32 ts_t3_sendb4                : 1;
        U32 ts_t3_recb4                 : 1;
        U32                             : 2;
    } bitc;
} GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_DEBUG_CODE_CODE_CR_IC_INVLD_ADDR_S   m_debug_code_code_cr_ic_invld_addr;

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_TRESET_ADDR (read/write)                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_CODE_set_CODE_CR_TRESET_ADDR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TRESET_ADDR_REAL = data;
}
GH_INLINE U32  GH_DEBUG_CODE_get_CODE_CR_TRESET_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TRESET_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_IC_INVLD_ADDR (write)                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_CODE_set_CODE_CR_IC_INVLD_ADDR(U32 data)
{
    m_debug_code_code_cr_ic_invld_addr.all = data;
    GH_DEBUG_CODE_CODE_CR_IC_INVLD_ADDR_REAL_S real;
    GH_DEBUG_CODE_CODE_CR_IC_INVLD_ADDR_S dummy;
    dummy.all = data ;
    real.bitc.invalid_icache = dummy.bitc.invalid_icache;
    *(volatile U32 *)REG_DEBUG_CODE_CODE_CR_IC_INVLD_ADDR_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_CODE_getm_CODE_CR_IC_INVLD_ADDR(void)
{
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "[GH_DEBUG_CODE_getm_CODE_CR_IC_INVLD_ADDR] --> 0x%08x\n",
                        m_debug_code_code_cr_ic_invld_addr.all);
    #endif
    return m_debug_code_code_cr_ic_invld_addr.all;
}
GH_INLINE void GH_DEBUG_CODE_set_CODE_CR_IC_INVLD_ADDR_invalid_icache(U8 data)
{
    m_debug_code_code_cr_ic_invld_addr.bitc.invalid_icache = data;
    GH_DEBUG_CODE_CODE_CR_IC_INVLD_ADDR_REAL_S real;
    real.bitc.invalid_icache = m_debug_code_code_cr_ic_invld_addr.bitc.invalid_icache;
    *(volatile U32 *)REG_DEBUG_CODE_CODE_CR_IC_INVLD_ADDR_REAL = real.all;
}
GH_INLINE U8   GH_DEBUG_CODE_getm_CODE_CR_IC_INVLD_ADDR_invalid_icache(void)
{
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "[GH_DEBUG_CODE_getm_CODE_CR_IC_INVLD_ADDR_invalid_icache] --> 0x%08x\n",
                        m_debug_code_code_cr_ic_invld_addr.bitc.invalid_icache);
    #endif
    return m_debug_code_code_cr_ic_invld_addr.bitc.invalid_icache;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_RESET_PC_ADDR (read/write)                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_CODE_set_CODE_CR_RESET_PC_ADDR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_CODE_CODE_CR_RESET_PC_ADDR_REAL = data;
}
GH_INLINE U32  GH_DEBUG_CODE_get_CODE_CR_RESET_PC_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_RESET_PC_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_TS_ADDR (read)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_CODE_get_CODE_CR_TS_ADDR(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S real;
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    dummy.bitc.ts_t0_run = real.bitc.ts_t0_run;
    dummy.bitc.ts_t0_restmr = real.bitc.ts_t0_restmr;
    dummy.bitc.ts_t0_dmab4 = real.bitc.ts_t0_dmab4;
    dummy.bitc.ts_t0_codeb4 = real.bitc.ts_t0_codeb4;
    dummy.bitc.ts_t0_sendb4 = real.bitc.ts_t0_sendb4;
    dummy.bitc.ts_t0_recb4 = real.bitc.ts_t0_recb4;
    dummy.bitc.ts_t1_run = real.bitc.ts_t1_run;
    dummy.bitc.ts_t1_restmr = real.bitc.ts_t1_restmr;
    dummy.bitc.ts_t1_dmab4 = real.bitc.ts_t1_dmab4;
    dummy.bitc.ts_t1_codeb4 = real.bitc.ts_t1_codeb4;
    dummy.bitc.ts_t1_sendb4 = real.bitc.ts_t1_sendb4;
    dummy.bitc.ts_t1_recb4 = real.bitc.ts_t1_recb4;
    dummy.bitc.ts_t2_run = real.bitc.ts_t2_run;
    dummy.bitc.ts_t2_restmr = real.bitc.ts_t2_restmr;
    dummy.bitc.ts_t2_dmab4 = real.bitc.ts_t2_dmab4;
    dummy.bitc.ts_t2_codeb4 = real.bitc.ts_t2_codeb4;
    dummy.bitc.ts_t2_sendb4 = real.bitc.ts_t2_sendb4;
    dummy.bitc.ts_t2_recb4 = real.bitc.ts_t2_recb4;
    dummy.bitc.ts_t3_run = real.bitc.ts_t3_run;
    dummy.bitc.ts_t3_restmr = real.bitc.ts_t3_restmr;
    dummy.bitc.ts_t3_dmab4 = real.bitc.ts_t3_dmab4;
    dummy.bitc.ts_t3_codeb4 = real.bitc.ts_t3_codeb4;
    dummy.bitc.ts_t3_sendb4 = real.bitc.ts_t3_sendb4;
    dummy.bitc.ts_t3_recb4 = real.bitc.ts_t3_recb4;
    return dummy.all;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_run(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t0_run;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_restmr(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t0_restmr;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_dmab4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t0_dmab4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_codeb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t0_codeb4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_sendb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t0_sendb4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_recb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t0_recb4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_run(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t1_run;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_restmr(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t1_restmr;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_dmab4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t1_dmab4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_codeb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t1_codeb4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_sendb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t1_sendb4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_recb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t1_recb4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_run(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t2_run;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_restmr(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t2_restmr;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_dmab4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t2_dmab4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_codeb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t2_codeb4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_sendb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t2_sendb4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_recb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t2_recb4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_run(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t3_run;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_restmr(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t3_restmr;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_dmab4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t3_dmab4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_codeb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t3_codeb4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_sendb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t3_sendb4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_recb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts_t3_recb4;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_PC_T0_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_CODE_get_CODE_CR_PC_T0_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_PC_T0_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_PC_T1_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_CODE_get_CODE_CR_PC_T1_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_PC_T1_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_PC_T2_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_CODE_get_CODE_CR_PC_T2_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_PC_T2_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_PC_T3_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_CODE_get_CODE_CR_PC_T3_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_PC_T3_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_STALL_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_CODE_get_CODE_CR_STALL_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_STALL_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_RF_ADDR (read)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_CODE_get_CODE_CR_RF_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_RF_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_DC_ADDR (read/write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_CODE_set_CODE_CR_DC_ADDR(U16 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_CODE_CODE_CR_DC_ADDR_REAL + index * FIO_MOFFSET(DEBUG_CODE,0x00000004)) = data;
}
GH_INLINE U32  GH_DEBUG_CODE_get_CODE_CR_DC_ADDR(U16 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_CODE_CODE_CR_DC_ADDR_REAL + index * FIO_MOFFSET(DEBUG_CODE,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_CODE_init(void)
{
    int i;

    GH_DEBUG_CODE_set_CODE_CR_TRESET_ADDR((U32)0x00000000);
    GH_DEBUG_CODE_set_CODE_CR_IC_INVLD_ADDR((U32)0x00000000);
    GH_DEBUG_CODE_set_CODE_CR_RESET_PC_ADDR((U32)0x00000000);
    for (i=0; i<4096; i++)
    {
        GH_DEBUG_CODE_set_CODE_CR_DC_ADDR(i, (U32)0x00000000);
    }
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

