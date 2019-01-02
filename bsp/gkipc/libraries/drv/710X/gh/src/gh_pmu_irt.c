/******************************************************************************
**
** \file      gh_pmu_irt.c
**
** \brief     Infrared Transmitter.
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
#include "gh_pmu_irt.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_PMU_IRT_READ_REAL                               FIO_ADDRESS(PMU_IRT,0x60082010) /* read/clear */
#define REG_PMU_IRT_TRANSMIT0_0_REAL                        FIO_ADDRESS(PMU_IRT,0x60082020) /* write */
#define REG_PMU_IRT_TRANSMIT0_1_REAL                        FIO_ADDRESS(PMU_IRT,0x60082024) /* write */
#define REG_PMU_IRT_TRANSMIT0_2_REAL                        FIO_ADDRESS(PMU_IRT,0x60082028) /* write */
#define REG_PMU_IRT_TRANSMIT0_3_REAL                        FIO_ADDRESS(PMU_IRT,0x6008202C) /* write */
#define REG_PMU_IRT_TRANSMIT1_0_REAL                        FIO_ADDRESS(PMU_IRT,0x60082030) /* write */
#define REG_PMU_IRT_TRANSMIT1_1_REAL                        FIO_ADDRESS(PMU_IRT,0x60082034) /* write */
#define REG_PMU_IRT_TRANSMIT1_2_REAL                        FIO_ADDRESS(PMU_IRT,0x60082038) /* write */
#define REG_PMU_IRT_TRANSMIT1_3_REAL                        FIO_ADDRESS(PMU_IRT,0x6008203C) /* write */
#define REG_PMU_IRT_TRANSMIT2_0_REAL                        FIO_ADDRESS(PMU_IRT,0x60082040) /* write */
#define REG_PMU_IRT_TRANSMIT2_1_REAL                        FIO_ADDRESS(PMU_IRT,0x60082044) /* write */
#define REG_PMU_IRT_TRANSMIT2_2_REAL                        FIO_ADDRESS(PMU_IRT,0x60082048) /* write */
#define REG_PMU_IRT_TRANSMIT2_3_REAL                        FIO_ADDRESS(PMU_IRT,0x6008204C) /* write */
#define REG_PMU_IRT_TRANSMIT3_0_REAL                        FIO_ADDRESS(PMU_IRT,0x60082050) /* write */
#define REG_PMU_IRT_TRANSMIT3_1_REAL                        FIO_ADDRESS(PMU_IRT,0x60082054) /* write */
#define REG_PMU_IRT_TRANSMIT3_2_REAL                        FIO_ADDRESS(PMU_IRT,0x60082058) /* write */
#define REG_PMU_IRT_TRANSMIT3_3_REAL                        FIO_ADDRESS(PMU_IRT,0x6008205C) /* write */
#define REG_PMU_IRT_SENT_CLOCK_L_REAL                       FIO_ADDRESS(PMU_IRT,0x60082060) /* write */
#define REG_PMU_IRT_SENT_CLOCK_H_REAL                       FIO_ADDRESS(PMU_IRT,0x60082064) /* write */
#define REG_PMU_IRT_SHIFT_CLOCK_REAL                        FIO_ADDRESS(PMU_IRT,0x60082068) /* write */
#define REG_PMU_IRT_SENT_CONF_REAL                          FIO_ADDRESS(PMU_IRT,0x6008206C) /* write */
#define REG_PMU_IRT_COMPVALUE_REAL                          FIO_ADDRESS(PMU_IRT,0x60082070) /* write */
#define REG_PMU_IRT_START_REAL                              FIO_ADDRESS(PMU_IRT,0x60082074) /* write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* PMU_IRT_Read */
    U32 all;
    struct {
        U32 irr_pulse01                 : 2;
        U32 no_used                     : 4;
        U32 irt_transmit0               : 1;
        U32 irt_transmit1               : 1;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_READ_REAL_S;

typedef union { /* PMU_IRT_Transmit0_0 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT0_0_REAL_S;

typedef union { /* PMU_IRT_Transmit0_1 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT0_1_REAL_S;

typedef union { /* PMU_IRT_Transmit0_2 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT0_2_REAL_S;

typedef union { /* PMU_IRT_Transmit0_3 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT0_3_REAL_S;

typedef union { /* PMU_IRT_Transmit1_0 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT1_0_REAL_S;

typedef union { /* PMU_IRT_Transmit1_1 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT1_1_REAL_S;

typedef union { /* PMU_IRT_Transmit1_2 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT1_2_REAL_S;

typedef union { /* PMU_IRT_Transmit1_3 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT1_3_REAL_S;

typedef union { /* PMU_IRT_Transmit2_0 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT2_0_REAL_S;

typedef union { /* PMU_IRT_Transmit2_1 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT2_1_REAL_S;

typedef union { /* PMU_IRT_Transmit2_2 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT2_2_REAL_S;

typedef union { /* PMU_IRT_Transmit2_3 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT2_3_REAL_S;

typedef union { /* PMU_IRT_Transmit3_0 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT3_0_REAL_S;

typedef union { /* PMU_IRT_Transmit3_1 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT3_1_REAL_S;

typedef union { /* PMU_IRT_Transmit3_2 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT3_2_REAL_S;

typedef union { /* PMU_IRT_Transmit3_3 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT3_3_REAL_S;

typedef union { /* PMU_IRT_Sent_Clock_l */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_SENT_CLOCK_L_REAL_S;

typedef union { /* PMU_IRT_Sent_Clock_h */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_SENT_CLOCK_H_REAL_S;

typedef union { /* PMU_IRT_Shift_Clock */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_SHIFT_CLOCK_REAL_S;

typedef union { /* PMU_IRT_Sent_Conf */
    U32 all;
    struct {
        U32 en_tx_irq                   : 1;
        U32 mode                        : 1;
        U32                             : 30;
    } bitc;
} GH_PMU_IRT_SENT_CONF_REAL_S;

typedef union { /* PMU_IRT_Compvalue */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_COMPVALUE_REAL_S;

typedef union { /* PMU_IRT_Start */
    U32 all;
    struct {
        U32 start_tx                    : 1;
        U32                             : 31;
    } bitc;
} GH_PMU_IRT_START_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_PMU_IRT_READ_S                       m_pmu_irt_read;
GH_PMU_IRT_TRANSMIT0_0_S                m_pmu_irt_transmit0_0;
GH_PMU_IRT_TRANSMIT0_1_S                m_pmu_irt_transmit0_1;
GH_PMU_IRT_TRANSMIT0_2_S                m_pmu_irt_transmit0_2;
GH_PMU_IRT_TRANSMIT0_3_S                m_pmu_irt_transmit0_3;
GH_PMU_IRT_TRANSMIT1_0_S                m_pmu_irt_transmit1_0;
GH_PMU_IRT_TRANSMIT1_1_S                m_pmu_irt_transmit1_1;
GH_PMU_IRT_TRANSMIT1_2_S                m_pmu_irt_transmit1_2;
GH_PMU_IRT_TRANSMIT1_3_S                m_pmu_irt_transmit1_3;
GH_PMU_IRT_TRANSMIT2_0_S                m_pmu_irt_transmit2_0;
GH_PMU_IRT_TRANSMIT2_1_S                m_pmu_irt_transmit2_1;
GH_PMU_IRT_TRANSMIT2_2_S                m_pmu_irt_transmit2_2;
GH_PMU_IRT_TRANSMIT2_3_S                m_pmu_irt_transmit2_3;
GH_PMU_IRT_TRANSMIT3_0_S                m_pmu_irt_transmit3_0;
GH_PMU_IRT_TRANSMIT3_1_S                m_pmu_irt_transmit3_1;
GH_PMU_IRT_TRANSMIT3_2_S                m_pmu_irt_transmit3_2;
GH_PMU_IRT_TRANSMIT3_3_S                m_pmu_irt_transmit3_3;
GH_PMU_IRT_SENT_CLOCK_L_S               m_pmu_irt_sent_clock_l;
GH_PMU_IRT_SENT_CLOCK_H_S               m_pmu_irt_sent_clock_h;
GH_PMU_IRT_SHIFT_CLOCK_S                m_pmu_irt_shift_clock;
GH_PMU_IRT_SENT_CONF_S                  m_pmu_irt_sent_conf;
GH_PMU_IRT_COMPVALUE_S                  m_pmu_irt_compvalue;
GH_PMU_IRT_START_S                      m_pmu_irt_start;

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Read (read/clear)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_PMU_IRT_get_Read(void)
{
    GH_PMU_IRT_READ_REAL_S real;
    GH_PMU_IRT_READ_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_PMU_IRT_READ_REAL);

    dummy.bitc.irr_pulse01 = real.bitc.irr_pulse01;
    dummy.bitc.no_used = real.bitc.no_used;
    dummy.bitc.irt_transmit0 = real.bitc.irt_transmit0;
    dummy.bitc.irt_transmit1 = real.bitc.irt_transmit1;
    m_pmu_irt_read.all = dummy.all;
    return dummy.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Read(void)
{
    return m_pmu_irt_read.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Read_IRR_PULSE01(void)
{
    return m_pmu_irt_read.bitc.irr_pulse01;
}
GH_INLINE U8   GH_PMU_IRT_getm_Read_NO_USED(void)
{
    return m_pmu_irt_read.bitc.no_used;
}
GH_INLINE U8   GH_PMU_IRT_getm_Read_IRT_TRANSMIT0(void)
{
    return m_pmu_irt_read.bitc.irt_transmit0;
}
GH_INLINE U8   GH_PMU_IRT_getm_Read_IRT_TRANSMIT1(void)
{
    return m_pmu_irt_read.bitc.irt_transmit1;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit0_0 (write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_set_Transmit0_0(U32 data)
{
    m_pmu_irt_transmit0_0.all = data;
    GH_PMU_IRT_TRANSMIT0_0_REAL_S real;
    GH_PMU_IRT_TRANSMIT0_0_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT0_0_REAL = real.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Transmit0_0(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit0_0] --> 0x%08x\n",
                        m_pmu_irt_transmit0_0.all);
    #endif
    return m_pmu_irt_transmit0_0.all;
}
GH_INLINE void GH_PMU_IRT_set_Transmit0_0_VALUE(U8 data)
{
    m_pmu_irt_transmit0_0.bitc.value = data;
    GH_PMU_IRT_TRANSMIT0_0_REAL_S real;
    real.bitc.value = m_pmu_irt_transmit0_0.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT0_0_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Transmit0_0_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit0_0_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit0_0.bitc.value);
    #endif
    return m_pmu_irt_transmit0_0.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit0_1 (write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_set_Transmit0_1(U32 data)
{
    m_pmu_irt_transmit0_1.all = data;
    GH_PMU_IRT_TRANSMIT0_1_REAL_S real;
    GH_PMU_IRT_TRANSMIT0_1_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT0_1_REAL = real.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Transmit0_1(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit0_1] --> 0x%08x\n",
                        m_pmu_irt_transmit0_1.all);
    #endif
    return m_pmu_irt_transmit0_1.all;
}
GH_INLINE void GH_PMU_IRT_set_Transmit0_1_VALUE(U8 data)
{
    m_pmu_irt_transmit0_1.bitc.value = data;
    GH_PMU_IRT_TRANSMIT0_1_REAL_S real;
    real.bitc.value = m_pmu_irt_transmit0_1.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT0_1_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Transmit0_1_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit0_1_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit0_1.bitc.value);
    #endif
    return m_pmu_irt_transmit0_1.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit0_2 (write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_set_Transmit0_2(U32 data)
{
    m_pmu_irt_transmit0_2.all = data;
    GH_PMU_IRT_TRANSMIT0_2_REAL_S real;
    GH_PMU_IRT_TRANSMIT0_2_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT0_2_REAL = real.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Transmit0_2(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit0_2] --> 0x%08x\n",
                        m_pmu_irt_transmit0_2.all);
    #endif
    return m_pmu_irt_transmit0_2.all;
}
GH_INLINE void GH_PMU_IRT_set_Transmit0_2_VALUE(U8 data)
{
    m_pmu_irt_transmit0_2.bitc.value = data;
    GH_PMU_IRT_TRANSMIT0_2_REAL_S real;
    real.bitc.value = m_pmu_irt_transmit0_2.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT0_2_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Transmit0_2_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit0_2_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit0_2.bitc.value);
    #endif
    return m_pmu_irt_transmit0_2.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit0_3 (write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_set_Transmit0_3(U32 data)
{
    m_pmu_irt_transmit0_3.all = data;
    GH_PMU_IRT_TRANSMIT0_3_REAL_S real;
    GH_PMU_IRT_TRANSMIT0_3_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT0_3_REAL = real.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Transmit0_3(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit0_3] --> 0x%08x\n",
                        m_pmu_irt_transmit0_3.all);
    #endif
    return m_pmu_irt_transmit0_3.all;
}
GH_INLINE void GH_PMU_IRT_set_Transmit0_3_VALUE(U8 data)
{
    m_pmu_irt_transmit0_3.bitc.value = data;
    GH_PMU_IRT_TRANSMIT0_3_REAL_S real;
    real.bitc.value = m_pmu_irt_transmit0_3.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT0_3_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Transmit0_3_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit0_3_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit0_3.bitc.value);
    #endif
    return m_pmu_irt_transmit0_3.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit1_0 (write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_set_Transmit1_0(U32 data)
{
    m_pmu_irt_transmit1_0.all = data;
    GH_PMU_IRT_TRANSMIT1_0_REAL_S real;
    GH_PMU_IRT_TRANSMIT1_0_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT1_0_REAL = real.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Transmit1_0(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit1_0] --> 0x%08x\n",
                        m_pmu_irt_transmit1_0.all);
    #endif
    return m_pmu_irt_transmit1_0.all;
}
GH_INLINE void GH_PMU_IRT_set_Transmit1_0_VALUE(U8 data)
{
    m_pmu_irt_transmit1_0.bitc.value = data;
    GH_PMU_IRT_TRANSMIT1_0_REAL_S real;
    real.bitc.value = m_pmu_irt_transmit1_0.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT1_0_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Transmit1_0_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit1_0_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit1_0.bitc.value);
    #endif
    return m_pmu_irt_transmit1_0.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit1_1 (write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_set_Transmit1_1(U32 data)
{
    m_pmu_irt_transmit1_1.all = data;
    GH_PMU_IRT_TRANSMIT1_1_REAL_S real;
    GH_PMU_IRT_TRANSMIT1_1_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT1_1_REAL = real.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Transmit1_1(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit1_1] --> 0x%08x\n",
                        m_pmu_irt_transmit1_1.all);
    #endif
    return m_pmu_irt_transmit1_1.all;
}
GH_INLINE void GH_PMU_IRT_set_Transmit1_1_VALUE(U8 data)
{
    m_pmu_irt_transmit1_1.bitc.value = data;
    GH_PMU_IRT_TRANSMIT1_1_REAL_S real;
    real.bitc.value = m_pmu_irt_transmit1_1.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT1_1_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Transmit1_1_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit1_1_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit1_1.bitc.value);
    #endif
    return m_pmu_irt_transmit1_1.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit1_2 (write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_set_Transmit1_2(U32 data)
{
    m_pmu_irt_transmit1_2.all = data;
    GH_PMU_IRT_TRANSMIT1_2_REAL_S real;
    GH_PMU_IRT_TRANSMIT1_2_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT1_2_REAL = real.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Transmit1_2(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit1_2] --> 0x%08x\n",
                        m_pmu_irt_transmit1_2.all);
    #endif
    return m_pmu_irt_transmit1_2.all;
}
GH_INLINE void GH_PMU_IRT_set_Transmit1_2_VALUE(U8 data)
{
    m_pmu_irt_transmit1_2.bitc.value = data;
    GH_PMU_IRT_TRANSMIT1_2_REAL_S real;
    real.bitc.value = m_pmu_irt_transmit1_2.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT1_2_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Transmit1_2_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit1_2_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit1_2.bitc.value);
    #endif
    return m_pmu_irt_transmit1_2.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit1_3 (write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_set_Transmit1_3(U32 data)
{
    m_pmu_irt_transmit1_3.all = data;
    GH_PMU_IRT_TRANSMIT1_3_REAL_S real;
    GH_PMU_IRT_TRANSMIT1_3_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT1_3_REAL = real.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Transmit1_3(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit1_3] --> 0x%08x\n",
                        m_pmu_irt_transmit1_3.all);
    #endif
    return m_pmu_irt_transmit1_3.all;
}
GH_INLINE void GH_PMU_IRT_set_Transmit1_3_VALUE(U8 data)
{
    m_pmu_irt_transmit1_3.bitc.value = data;
    GH_PMU_IRT_TRANSMIT1_3_REAL_S real;
    real.bitc.value = m_pmu_irt_transmit1_3.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT1_3_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Transmit1_3_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit1_3_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit1_3.bitc.value);
    #endif
    return m_pmu_irt_transmit1_3.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit2_0 (write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_set_Transmit2_0(U32 data)
{
    m_pmu_irt_transmit2_0.all = data;
    GH_PMU_IRT_TRANSMIT2_0_REAL_S real;
    GH_PMU_IRT_TRANSMIT2_0_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT2_0_REAL = real.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Transmit2_0(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit2_0] --> 0x%08x\n",
                        m_pmu_irt_transmit2_0.all);
    #endif
    return m_pmu_irt_transmit2_0.all;
}
GH_INLINE void GH_PMU_IRT_set_Transmit2_0_VALUE(U8 data)
{
    m_pmu_irt_transmit2_0.bitc.value = data;
    GH_PMU_IRT_TRANSMIT2_0_REAL_S real;
    real.bitc.value = m_pmu_irt_transmit2_0.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT2_0_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Transmit2_0_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit2_0_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit2_0.bitc.value);
    #endif
    return m_pmu_irt_transmit2_0.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit2_1 (write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_set_Transmit2_1(U32 data)
{
    m_pmu_irt_transmit2_1.all = data;
    GH_PMU_IRT_TRANSMIT2_1_REAL_S real;
    GH_PMU_IRT_TRANSMIT2_1_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT2_1_REAL = real.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Transmit2_1(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit2_1] --> 0x%08x\n",
                        m_pmu_irt_transmit2_1.all);
    #endif
    return m_pmu_irt_transmit2_1.all;
}
GH_INLINE void GH_PMU_IRT_set_Transmit2_1_VALUE(U8 data)
{
    m_pmu_irt_transmit2_1.bitc.value = data;
    GH_PMU_IRT_TRANSMIT2_1_REAL_S real;
    real.bitc.value = m_pmu_irt_transmit2_1.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT2_1_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Transmit2_1_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit2_1_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit2_1.bitc.value);
    #endif
    return m_pmu_irt_transmit2_1.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit2_2 (write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_set_Transmit2_2(U32 data)
{
    m_pmu_irt_transmit2_2.all = data;
    GH_PMU_IRT_TRANSMIT2_2_REAL_S real;
    GH_PMU_IRT_TRANSMIT2_2_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT2_2_REAL = real.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Transmit2_2(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit2_2] --> 0x%08x\n",
                        m_pmu_irt_transmit2_2.all);
    #endif
    return m_pmu_irt_transmit2_2.all;
}
GH_INLINE void GH_PMU_IRT_set_Transmit2_2_VALUE(U8 data)
{
    m_pmu_irt_transmit2_2.bitc.value = data;
    GH_PMU_IRT_TRANSMIT2_2_REAL_S real;
    real.bitc.value = m_pmu_irt_transmit2_2.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT2_2_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Transmit2_2_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit2_2_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit2_2.bitc.value);
    #endif
    return m_pmu_irt_transmit2_2.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit2_3 (write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_set_Transmit2_3(U32 data)
{
    m_pmu_irt_transmit2_3.all = data;
    GH_PMU_IRT_TRANSMIT2_3_REAL_S real;
    GH_PMU_IRT_TRANSMIT2_3_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT2_3_REAL = real.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Transmit2_3(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit2_3] --> 0x%08x\n",
                        m_pmu_irt_transmit2_3.all);
    #endif
    return m_pmu_irt_transmit2_3.all;
}
GH_INLINE void GH_PMU_IRT_set_Transmit2_3_VALUE(U8 data)
{
    m_pmu_irt_transmit2_3.bitc.value = data;
    GH_PMU_IRT_TRANSMIT2_3_REAL_S real;
    real.bitc.value = m_pmu_irt_transmit2_3.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT2_3_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Transmit2_3_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit2_3_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit2_3.bitc.value);
    #endif
    return m_pmu_irt_transmit2_3.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit3_0 (write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_set_Transmit3_0(U32 data)
{
    m_pmu_irt_transmit3_0.all = data;
    GH_PMU_IRT_TRANSMIT3_0_REAL_S real;
    GH_PMU_IRT_TRANSMIT3_0_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT3_0_REAL = real.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Transmit3_0(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit3_0] --> 0x%08x\n",
                        m_pmu_irt_transmit3_0.all);
    #endif
    return m_pmu_irt_transmit3_0.all;
}
GH_INLINE void GH_PMU_IRT_set_Transmit3_0_VALUE(U8 data)
{
    m_pmu_irt_transmit3_0.bitc.value = data;
    GH_PMU_IRT_TRANSMIT3_0_REAL_S real;
    real.bitc.value = m_pmu_irt_transmit3_0.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT3_0_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Transmit3_0_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit3_0_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit3_0.bitc.value);
    #endif
    return m_pmu_irt_transmit3_0.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit3_1 (write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_set_Transmit3_1(U32 data)
{
    m_pmu_irt_transmit3_1.all = data;
    GH_PMU_IRT_TRANSMIT3_1_REAL_S real;
    GH_PMU_IRT_TRANSMIT3_1_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT3_1_REAL = real.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Transmit3_1(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit3_1] --> 0x%08x\n",
                        m_pmu_irt_transmit3_1.all);
    #endif
    return m_pmu_irt_transmit3_1.all;
}
GH_INLINE void GH_PMU_IRT_set_Transmit3_1_VALUE(U8 data)
{
    m_pmu_irt_transmit3_1.bitc.value = data;
    GH_PMU_IRT_TRANSMIT3_1_REAL_S real;
    real.bitc.value = m_pmu_irt_transmit3_1.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT3_1_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Transmit3_1_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit3_1_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit3_1.bitc.value);
    #endif
    return m_pmu_irt_transmit3_1.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit3_2 (write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_set_Transmit3_2(U32 data)
{
    m_pmu_irt_transmit3_2.all = data;
    GH_PMU_IRT_TRANSMIT3_2_REAL_S real;
    GH_PMU_IRT_TRANSMIT3_2_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT3_2_REAL = real.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Transmit3_2(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit3_2] --> 0x%08x\n",
                        m_pmu_irt_transmit3_2.all);
    #endif
    return m_pmu_irt_transmit3_2.all;
}
GH_INLINE void GH_PMU_IRT_set_Transmit3_2_VALUE(U8 data)
{
    m_pmu_irt_transmit3_2.bitc.value = data;
    GH_PMU_IRT_TRANSMIT3_2_REAL_S real;
    real.bitc.value = m_pmu_irt_transmit3_2.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT3_2_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Transmit3_2_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit3_2_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit3_2.bitc.value);
    #endif
    return m_pmu_irt_transmit3_2.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit3_3 (write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_set_Transmit3_3(U32 data)
{
    m_pmu_irt_transmit3_3.all = data;
    GH_PMU_IRT_TRANSMIT3_3_REAL_S real;
    GH_PMU_IRT_TRANSMIT3_3_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT3_3_REAL = real.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Transmit3_3(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit3_3] --> 0x%08x\n",
                        m_pmu_irt_transmit3_3.all);
    #endif
    return m_pmu_irt_transmit3_3.all;
}
GH_INLINE void GH_PMU_IRT_set_Transmit3_3_VALUE(U8 data)
{
    m_pmu_irt_transmit3_3.bitc.value = data;
    GH_PMU_IRT_TRANSMIT3_3_REAL_S real;
    real.bitc.value = m_pmu_irt_transmit3_3.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_TRANSMIT3_3_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Transmit3_3_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Transmit3_3_VALUE] --> 0x%08x\n",
                        m_pmu_irt_transmit3_3.bitc.value);
    #endif
    return m_pmu_irt_transmit3_3.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Sent_Clock_l (write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_set_Sent_Clock_l(U32 data)
{
    m_pmu_irt_sent_clock_l.all = data;
    GH_PMU_IRT_SENT_CLOCK_L_REAL_S real;
    GH_PMU_IRT_SENT_CLOCK_L_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_SENT_CLOCK_L_REAL = real.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Sent_Clock_l(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Sent_Clock_l] --> 0x%08x\n",
                        m_pmu_irt_sent_clock_l.all);
    #endif
    return m_pmu_irt_sent_clock_l.all;
}
GH_INLINE void GH_PMU_IRT_set_Sent_Clock_l_VALUE(U8 data)
{
    m_pmu_irt_sent_clock_l.bitc.value = data;
    GH_PMU_IRT_SENT_CLOCK_L_REAL_S real;
    real.bitc.value = m_pmu_irt_sent_clock_l.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_SENT_CLOCK_L_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Sent_Clock_l_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Sent_Clock_l_VALUE] --> 0x%08x\n",
                        m_pmu_irt_sent_clock_l.bitc.value);
    #endif
    return m_pmu_irt_sent_clock_l.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Sent_Clock_h (write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_set_Sent_Clock_h(U32 data)
{
    m_pmu_irt_sent_clock_h.all = data;
    GH_PMU_IRT_SENT_CLOCK_H_REAL_S real;
    GH_PMU_IRT_SENT_CLOCK_H_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_SENT_CLOCK_H_REAL = real.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Sent_Clock_h(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Sent_Clock_h] --> 0x%08x\n",
                        m_pmu_irt_sent_clock_h.all);
    #endif
    return m_pmu_irt_sent_clock_h.all;
}
GH_INLINE void GH_PMU_IRT_set_Sent_Clock_h_VALUE(U8 data)
{
    m_pmu_irt_sent_clock_h.bitc.value = data;
    GH_PMU_IRT_SENT_CLOCK_H_REAL_S real;
    real.bitc.value = m_pmu_irt_sent_clock_h.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_SENT_CLOCK_H_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Sent_Clock_h_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Sent_Clock_h_VALUE] --> 0x%08x\n",
                        m_pmu_irt_sent_clock_h.bitc.value);
    #endif
    return m_pmu_irt_sent_clock_h.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Shift_Clock (write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_set_Shift_Clock(U32 data)
{
    m_pmu_irt_shift_clock.all = data;
    GH_PMU_IRT_SHIFT_CLOCK_REAL_S real;
    GH_PMU_IRT_SHIFT_CLOCK_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_SHIFT_CLOCK_REAL = real.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Shift_Clock(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Shift_Clock] --> 0x%08x\n",
                        m_pmu_irt_shift_clock.all);
    #endif
    return m_pmu_irt_shift_clock.all;
}
GH_INLINE void GH_PMU_IRT_set_Shift_Clock_VALUE(U8 data)
{
    m_pmu_irt_shift_clock.bitc.value = data;
    GH_PMU_IRT_SHIFT_CLOCK_REAL_S real;
    real.bitc.value = m_pmu_irt_shift_clock.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_SHIFT_CLOCK_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Shift_Clock_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Shift_Clock_VALUE] --> 0x%08x\n",
                        m_pmu_irt_shift_clock.bitc.value);
    #endif
    return m_pmu_irt_shift_clock.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Sent_Conf (write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_set_Sent_Conf(U32 data)
{
    m_pmu_irt_sent_conf.all = data;
    GH_PMU_IRT_SENT_CONF_REAL_S real;
    GH_PMU_IRT_SENT_CONF_S dummy;
    dummy.all = data ;
    real.bitc.en_tx_irq = dummy.bitc.en_tx_irq;
    real.bitc.mode = dummy.bitc.mode;
    *(volatile U32 *)REG_PMU_IRT_SENT_CONF_REAL = real.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Sent_Conf(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Sent_Conf] --> 0x%08x\n",
                        m_pmu_irt_sent_conf.all);
    #endif
    return m_pmu_irt_sent_conf.all;
}
GH_INLINE void GH_PMU_IRT_set_Sent_Conf_EN_TX_IRQ(U8 data)
{
    m_pmu_irt_sent_conf.bitc.en_tx_irq = data;
    GH_PMU_IRT_SENT_CONF_REAL_S real;
    real.bitc.en_tx_irq = m_pmu_irt_sent_conf.bitc.en_tx_irq;
    real.bitc.mode = m_pmu_irt_sent_conf.bitc.mode;
    *(volatile U32 *)REG_PMU_IRT_SENT_CONF_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Sent_Conf_EN_TX_IRQ(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Sent_Conf_EN_TX_IRQ] --> 0x%08x\n",
                        m_pmu_irt_sent_conf.bitc.en_tx_irq);
    #endif
    return m_pmu_irt_sent_conf.bitc.en_tx_irq;
}
GH_INLINE void GH_PMU_IRT_set_Sent_Conf_MODE(U8 data)
{
    m_pmu_irt_sent_conf.bitc.mode = data;
    GH_PMU_IRT_SENT_CONF_REAL_S real;
    real.bitc.en_tx_irq = m_pmu_irt_sent_conf.bitc.en_tx_irq;
    real.bitc.mode = m_pmu_irt_sent_conf.bitc.mode;
    *(volatile U32 *)REG_PMU_IRT_SENT_CONF_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Sent_Conf_MODE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Sent_Conf_MODE] --> 0x%08x\n",
                        m_pmu_irt_sent_conf.bitc.mode);
    #endif
    return m_pmu_irt_sent_conf.bitc.mode;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Compvalue (write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_set_Compvalue(U32 data)
{
    m_pmu_irt_compvalue.all = data;
    GH_PMU_IRT_COMPVALUE_REAL_S real;
    GH_PMU_IRT_COMPVALUE_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_COMPVALUE_REAL = real.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Compvalue(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Compvalue] --> 0x%08x\n",
                        m_pmu_irt_compvalue.all);
    #endif
    return m_pmu_irt_compvalue.all;
}
GH_INLINE void GH_PMU_IRT_set_Compvalue_VALUE(U8 data)
{
    m_pmu_irt_compvalue.bitc.value = data;
    GH_PMU_IRT_COMPVALUE_REAL_S real;
    real.bitc.value = m_pmu_irt_compvalue.bitc.value;
    *(volatile U32 *)REG_PMU_IRT_COMPVALUE_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Compvalue_VALUE(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Compvalue_VALUE] --> 0x%08x\n",
                        m_pmu_irt_compvalue.bitc.value);
    #endif
    return m_pmu_irt_compvalue.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Start (write)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_set_Start(U32 data)
{
    m_pmu_irt_start.all = data;
    GH_PMU_IRT_START_REAL_S real;
    GH_PMU_IRT_START_S dummy;
    dummy.all = data ;
    real.bitc.start_tx = dummy.bitc.start_tx;
    *(volatile U32 *)REG_PMU_IRT_START_REAL = real.all;
}
GH_INLINE U32  GH_PMU_IRT_getm_Start(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Start] --> 0x%08x\n",
                        m_pmu_irt_start.all);
    #endif
    return m_pmu_irt_start.all;
}
GH_INLINE void GH_PMU_IRT_set_Start_START_TX(U8 data)
{
    m_pmu_irt_start.bitc.start_tx = data;
    GH_PMU_IRT_START_REAL_S real;
    real.bitc.start_tx = m_pmu_irt_start.bitc.start_tx;
    *(volatile U32 *)REG_PMU_IRT_START_REAL = real.all;
}
GH_INLINE U8   GH_PMU_IRT_getm_Start_START_TX(void)
{
    #if GH_PMU_IRT_ENABLE_DEBUG_PRINT
    GH_PMU_IRT_DEBUG_PRINT_FUNCTION( "[GH_PMU_IRT_getm_Start_START_TX] --> 0x%08x\n",
                        m_pmu_irt_start.bitc.start_tx);
    #endif
    return m_pmu_irt_start.bitc.start_tx;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_PMU_IRT_init(void)
{
    GH_PMU_IRT_set_Transmit0_0((U32)0x00000000);
    GH_PMU_IRT_set_Transmit0_1((U32)0x00000000);
    GH_PMU_IRT_set_Transmit0_2((U32)0x00000000);
    GH_PMU_IRT_set_Transmit0_3((U32)0x00000000);
    GH_PMU_IRT_set_Transmit1_0((U32)0x00000000);
    GH_PMU_IRT_set_Transmit1_1((U32)0x00000000);
    GH_PMU_IRT_set_Transmit1_2((U32)0x00000000);
    GH_PMU_IRT_set_Transmit1_3((U32)0x00000000);
    GH_PMU_IRT_set_Transmit2_0((U32)0x00000000);
    GH_PMU_IRT_set_Transmit2_1((U32)0x00000000);
    GH_PMU_IRT_set_Transmit2_2((U32)0x00000000);
    GH_PMU_IRT_set_Transmit2_3((U32)0x00000000);
    GH_PMU_IRT_set_Transmit3_0((U32)0x00000000);
    GH_PMU_IRT_set_Transmit3_1((U32)0x00000000);
    GH_PMU_IRT_set_Transmit3_2((U32)0x00000000);
    GH_PMU_IRT_set_Transmit3_3((U32)0x00000000);
    GH_PMU_IRT_set_Sent_Clock_l((U32)0x00000000);
    GH_PMU_IRT_set_Sent_Clock_h((U32)0x00000000);
    GH_PMU_IRT_set_Shift_Clock((U32)0x00000000);
    GH_PMU_IRT_set_Sent_Conf((U32)0x00000000);
    GH_PMU_IRT_set_Compvalue((U32)0x00000000);
    GH_PMU_IRT_set_Start((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
    GH_PMU_IRT_get_Read();
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

