/*!
*******************************************************************************
**
** \file      gh_pmu_irt.h
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
#ifndef _GH_PMU_IRT_H
#define _GH_PMU_IRT_H

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

#define GH_PMU_IRT_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_PMU_IRT_DEBUG_PRINT_FUNCTION printk
#else
#define GH_PMU_IRT_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_PMU_IRT_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_PMU_IRT_READ                                    FIO_ADDRESS(PMU_IRT,0x90082010) /* read/clear */
#define REG_PMU_IRT_TRANSMIT0_0                             FIO_ADDRESS(PMU_IRT,0x90082020) /* write */
#define REG_PMU_IRT_TRANSMIT0_1                             FIO_ADDRESS(PMU_IRT,0x90082024) /* write */
#define REG_PMU_IRT_TRANSMIT0_2                             FIO_ADDRESS(PMU_IRT,0x90082028) /* write */
#define REG_PMU_IRT_TRANSMIT0_3                             FIO_ADDRESS(PMU_IRT,0x9008202C) /* write */
#define REG_PMU_IRT_TRANSMIT1_0                             FIO_ADDRESS(PMU_IRT,0x90082030) /* write */
#define REG_PMU_IRT_TRANSMIT1_1                             FIO_ADDRESS(PMU_IRT,0x90082034) /* write */
#define REG_PMU_IRT_TRANSMIT1_2                             FIO_ADDRESS(PMU_IRT,0x90082038) /* write */
#define REG_PMU_IRT_TRANSMIT1_3                             FIO_ADDRESS(PMU_IRT,0x9008203C) /* write */
#define REG_PMU_IRT_TRANSMIT2_0                             FIO_ADDRESS(PMU_IRT,0x90082040) /* write */
#define REG_PMU_IRT_TRANSMIT2_1                             FIO_ADDRESS(PMU_IRT,0x90082044) /* write */
#define REG_PMU_IRT_TRANSMIT2_2                             FIO_ADDRESS(PMU_IRT,0x90082048) /* write */
#define REG_PMU_IRT_TRANSMIT2_3                             FIO_ADDRESS(PMU_IRT,0x9008204C) /* write */
#define REG_PMU_IRT_TRANSMIT3_0                             FIO_ADDRESS(PMU_IRT,0x90082050) /* write */
#define REG_PMU_IRT_TRANSMIT3_1                             FIO_ADDRESS(PMU_IRT,0x90082054) /* write */
#define REG_PMU_IRT_TRANSMIT3_2                             FIO_ADDRESS(PMU_IRT,0x90082058) /* write */
#define REG_PMU_IRT_TRANSMIT3_3                             FIO_ADDRESS(PMU_IRT,0x9008205C) /* write */
#define REG_PMU_IRT_SENT_CLOCK_L                            FIO_ADDRESS(PMU_IRT,0x90082060) /* write */
#define REG_PMU_IRT_SENT_CLOCK_H                            FIO_ADDRESS(PMU_IRT,0x90082064) /* write */
#define REG_PMU_IRT_SHIFT_CLOCK                             FIO_ADDRESS(PMU_IRT,0x90082068) /* write */
#define REG_PMU_IRT_SENT_CONF                               FIO_ADDRESS(PMU_IRT,0x9008206C) /* write */
#define REG_PMU_IRT_COMPVALUE                               FIO_ADDRESS(PMU_IRT,0x90082070) /* write */
#define REG_PMU_IRT_START                                   FIO_ADDRESS(PMU_IRT,0x90082074) /* write */

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
} GH_PMU_IRT_READ_S;

typedef union { /* PMU_IRT_Transmit0_0 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT0_0_S;

typedef union { /* PMU_IRT_Transmit0_1 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT0_1_S;

typedef union { /* PMU_IRT_Transmit0_2 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT0_2_S;

typedef union { /* PMU_IRT_Transmit0_3 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT0_3_S;

typedef union { /* PMU_IRT_Transmit1_0 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT1_0_S;

typedef union { /* PMU_IRT_Transmit1_1 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT1_1_S;

typedef union { /* PMU_IRT_Transmit1_2 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT1_2_S;

typedef union { /* PMU_IRT_Transmit1_3 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT1_3_S;

typedef union { /* PMU_IRT_Transmit2_0 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT2_0_S;

typedef union { /* PMU_IRT_Transmit2_1 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT2_1_S;

typedef union { /* PMU_IRT_Transmit2_2 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT2_2_S;

typedef union { /* PMU_IRT_Transmit2_3 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT2_3_S;

typedef union { /* PMU_IRT_Transmit3_0 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT3_0_S;

typedef union { /* PMU_IRT_Transmit3_1 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT3_1_S;

typedef union { /* PMU_IRT_Transmit3_2 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT3_2_S;

typedef union { /* PMU_IRT_Transmit3_3 */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_TRANSMIT3_3_S;

typedef union { /* PMU_IRT_Sent_Clock_l */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_SENT_CLOCK_L_S;

typedef union { /* PMU_IRT_Sent_Clock_h */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_SENT_CLOCK_H_S;

typedef union { /* PMU_IRT_Shift_Clock */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_SHIFT_CLOCK_S;

typedef union { /* PMU_IRT_Sent_Conf */
    U32 all;
    struct {
        U32 en_tx_irq                   : 1;
        U32 mode                        : 1;
        U32                             : 30;
    } bitc;
} GH_PMU_IRT_SENT_CONF_S;

typedef union { /* PMU_IRT_Compvalue */
    U32 all;
    struct {
        U32 value                       : 8;
        U32                             : 24;
    } bitc;
} GH_PMU_IRT_COMPVALUE_S;

typedef union { /* PMU_IRT_Start */
    U32 all;
    struct {
        U32 start_tx                    : 1;
        U32                             : 31;
    } bitc;
} GH_PMU_IRT_START_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern GH_PMU_IRT_READ_S                       m_pmu_irt_read;
extern GH_PMU_IRT_TRANSMIT0_0_S                m_pmu_irt_transmit0_0;
extern GH_PMU_IRT_TRANSMIT0_1_S                m_pmu_irt_transmit0_1;
extern GH_PMU_IRT_TRANSMIT0_2_S                m_pmu_irt_transmit0_2;
extern GH_PMU_IRT_TRANSMIT0_3_S                m_pmu_irt_transmit0_3;
extern GH_PMU_IRT_TRANSMIT1_0_S                m_pmu_irt_transmit1_0;
extern GH_PMU_IRT_TRANSMIT1_1_S                m_pmu_irt_transmit1_1;
extern GH_PMU_IRT_TRANSMIT1_2_S                m_pmu_irt_transmit1_2;
extern GH_PMU_IRT_TRANSMIT1_3_S                m_pmu_irt_transmit1_3;
extern GH_PMU_IRT_TRANSMIT2_0_S                m_pmu_irt_transmit2_0;
extern GH_PMU_IRT_TRANSMIT2_1_S                m_pmu_irt_transmit2_1;
extern GH_PMU_IRT_TRANSMIT2_2_S                m_pmu_irt_transmit2_2;
extern GH_PMU_IRT_TRANSMIT2_3_S                m_pmu_irt_transmit2_3;
extern GH_PMU_IRT_TRANSMIT3_0_S                m_pmu_irt_transmit3_0;
extern GH_PMU_IRT_TRANSMIT3_1_S                m_pmu_irt_transmit3_1;
extern GH_PMU_IRT_TRANSMIT3_2_S                m_pmu_irt_transmit3_2;
extern GH_PMU_IRT_TRANSMIT3_3_S                m_pmu_irt_transmit3_3;
extern GH_PMU_IRT_SENT_CLOCK_L_S               m_pmu_irt_sent_clock_l;
extern GH_PMU_IRT_SENT_CLOCK_H_S               m_pmu_irt_sent_clock_h;
extern GH_PMU_IRT_SHIFT_CLOCK_S                m_pmu_irt_shift_clock;
extern GH_PMU_IRT_SENT_CONF_S                  m_pmu_irt_sent_conf;
extern GH_PMU_IRT_COMPVALUE_S                  m_pmu_irt_compvalue;
extern GH_PMU_IRT_START_S                      m_pmu_irt_start;

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Read (read/clear)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Read'. */
U32  GH_PMU_IRT_get_Read(void);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Read'. */
U32  GH_PMU_IRT_getm_Read(void);
/*! \brief Reads the bit group 'IRR_PULSE01' from the mirror variable of register 'PMU_IRT_Read'. */
U8   GH_PMU_IRT_getm_Read_IRR_PULSE01(void);
/*! \brief Reads the bit group 'NO_USED' from the mirror variable of register 'PMU_IRT_Read'. */
U8   GH_PMU_IRT_getm_Read_NO_USED(void);
/*! \brief Reads the bit group 'IRT_TRANSMIT0' from the mirror variable of register 'PMU_IRT_Read'. */
U8   GH_PMU_IRT_getm_Read_IRT_TRANSMIT0(void);
/*! \brief Reads the bit group 'IRT_TRANSMIT1' from the mirror variable of register 'PMU_IRT_Read'. */
U8   GH_PMU_IRT_getm_Read_IRT_TRANSMIT1(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit0_0 (write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Transmit0_0'. */
void GH_PMU_IRT_set_Transmit0_0(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Transmit0_0'. */
U32  GH_PMU_IRT_getm_Transmit0_0(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRT_Transmit0_0'. */
void GH_PMU_IRT_set_Transmit0_0_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRT_Transmit0_0'. */
U8   GH_PMU_IRT_getm_Transmit0_0_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit0_1 (write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Transmit0_1'. */
void GH_PMU_IRT_set_Transmit0_1(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Transmit0_1'. */
U32  GH_PMU_IRT_getm_Transmit0_1(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRT_Transmit0_1'. */
void GH_PMU_IRT_set_Transmit0_1_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRT_Transmit0_1'. */
U8   GH_PMU_IRT_getm_Transmit0_1_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit0_2 (write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Transmit0_2'. */
void GH_PMU_IRT_set_Transmit0_2(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Transmit0_2'. */
U32  GH_PMU_IRT_getm_Transmit0_2(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRT_Transmit0_2'. */
void GH_PMU_IRT_set_Transmit0_2_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRT_Transmit0_2'. */
U8   GH_PMU_IRT_getm_Transmit0_2_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit0_3 (write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Transmit0_3'. */
void GH_PMU_IRT_set_Transmit0_3(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Transmit0_3'. */
U32  GH_PMU_IRT_getm_Transmit0_3(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRT_Transmit0_3'. */
void GH_PMU_IRT_set_Transmit0_3_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRT_Transmit0_3'. */
U8   GH_PMU_IRT_getm_Transmit0_3_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit1_0 (write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Transmit1_0'. */
void GH_PMU_IRT_set_Transmit1_0(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Transmit1_0'. */
U32  GH_PMU_IRT_getm_Transmit1_0(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRT_Transmit1_0'. */
void GH_PMU_IRT_set_Transmit1_0_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRT_Transmit1_0'. */
U8   GH_PMU_IRT_getm_Transmit1_0_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit1_1 (write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Transmit1_1'. */
void GH_PMU_IRT_set_Transmit1_1(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Transmit1_1'. */
U32  GH_PMU_IRT_getm_Transmit1_1(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRT_Transmit1_1'. */
void GH_PMU_IRT_set_Transmit1_1_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRT_Transmit1_1'. */
U8   GH_PMU_IRT_getm_Transmit1_1_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit1_2 (write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Transmit1_2'. */
void GH_PMU_IRT_set_Transmit1_2(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Transmit1_2'. */
U32  GH_PMU_IRT_getm_Transmit1_2(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRT_Transmit1_2'. */
void GH_PMU_IRT_set_Transmit1_2_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRT_Transmit1_2'. */
U8   GH_PMU_IRT_getm_Transmit1_2_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit1_3 (write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Transmit1_3'. */
void GH_PMU_IRT_set_Transmit1_3(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Transmit1_3'. */
U32  GH_PMU_IRT_getm_Transmit1_3(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRT_Transmit1_3'. */
void GH_PMU_IRT_set_Transmit1_3_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRT_Transmit1_3'. */
U8   GH_PMU_IRT_getm_Transmit1_3_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit2_0 (write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Transmit2_0'. */
void GH_PMU_IRT_set_Transmit2_0(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Transmit2_0'. */
U32  GH_PMU_IRT_getm_Transmit2_0(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRT_Transmit2_0'. */
void GH_PMU_IRT_set_Transmit2_0_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRT_Transmit2_0'. */
U8   GH_PMU_IRT_getm_Transmit2_0_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit2_1 (write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Transmit2_1'. */
void GH_PMU_IRT_set_Transmit2_1(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Transmit2_1'. */
U32  GH_PMU_IRT_getm_Transmit2_1(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRT_Transmit2_1'. */
void GH_PMU_IRT_set_Transmit2_1_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRT_Transmit2_1'. */
U8   GH_PMU_IRT_getm_Transmit2_1_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit2_2 (write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Transmit2_2'. */
void GH_PMU_IRT_set_Transmit2_2(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Transmit2_2'. */
U32  GH_PMU_IRT_getm_Transmit2_2(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRT_Transmit2_2'. */
void GH_PMU_IRT_set_Transmit2_2_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRT_Transmit2_2'. */
U8   GH_PMU_IRT_getm_Transmit2_2_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit2_3 (write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Transmit2_3'. */
void GH_PMU_IRT_set_Transmit2_3(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Transmit2_3'. */
U32  GH_PMU_IRT_getm_Transmit2_3(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRT_Transmit2_3'. */
void GH_PMU_IRT_set_Transmit2_3_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRT_Transmit2_3'. */
U8   GH_PMU_IRT_getm_Transmit2_3_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit3_0 (write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Transmit3_0'. */
void GH_PMU_IRT_set_Transmit3_0(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Transmit3_0'. */
U32  GH_PMU_IRT_getm_Transmit3_0(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRT_Transmit3_0'. */
void GH_PMU_IRT_set_Transmit3_0_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRT_Transmit3_0'. */
U8   GH_PMU_IRT_getm_Transmit3_0_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit3_1 (write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Transmit3_1'. */
void GH_PMU_IRT_set_Transmit3_1(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Transmit3_1'. */
U32  GH_PMU_IRT_getm_Transmit3_1(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRT_Transmit3_1'. */
void GH_PMU_IRT_set_Transmit3_1_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRT_Transmit3_1'. */
U8   GH_PMU_IRT_getm_Transmit3_1_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit3_2 (write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Transmit3_2'. */
void GH_PMU_IRT_set_Transmit3_2(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Transmit3_2'. */
U32  GH_PMU_IRT_getm_Transmit3_2(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRT_Transmit3_2'. */
void GH_PMU_IRT_set_Transmit3_2_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRT_Transmit3_2'. */
U8   GH_PMU_IRT_getm_Transmit3_2_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Transmit3_3 (write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Transmit3_3'. */
void GH_PMU_IRT_set_Transmit3_3(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Transmit3_3'. */
U32  GH_PMU_IRT_getm_Transmit3_3(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRT_Transmit3_3'. */
void GH_PMU_IRT_set_Transmit3_3_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRT_Transmit3_3'. */
U8   GH_PMU_IRT_getm_Transmit3_3_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Sent_Clock_l (write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Sent_Clock_l'. */
void GH_PMU_IRT_set_Sent_Clock_l(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Sent_Clock_l'. */
U32  GH_PMU_IRT_getm_Sent_Clock_l(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRT_Sent_Clock_l'. */
void GH_PMU_IRT_set_Sent_Clock_l_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRT_Sent_Clock_l'. */
U8   GH_PMU_IRT_getm_Sent_Clock_l_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Sent_Clock_h (write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Sent_Clock_h'. */
void GH_PMU_IRT_set_Sent_Clock_h(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Sent_Clock_h'. */
U32  GH_PMU_IRT_getm_Sent_Clock_h(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRT_Sent_Clock_h'. */
void GH_PMU_IRT_set_Sent_Clock_h_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRT_Sent_Clock_h'. */
U8   GH_PMU_IRT_getm_Sent_Clock_h_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Shift_Clock (write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Shift_Clock'. */
void GH_PMU_IRT_set_Shift_Clock(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Shift_Clock'. */
U32  GH_PMU_IRT_getm_Shift_Clock(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRT_Shift_Clock'. */
void GH_PMU_IRT_set_Shift_Clock_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRT_Shift_Clock'. */
U8   GH_PMU_IRT_getm_Shift_Clock_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Sent_Conf (write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Sent_Conf'. */
void GH_PMU_IRT_set_Sent_Conf(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Sent_Conf'. */
U32  GH_PMU_IRT_getm_Sent_Conf(void);
/*! \brief Writes the bit group 'EN_TX_IRQ' of register 'PMU_IRT_Sent_Conf'. */
void GH_PMU_IRT_set_Sent_Conf_EN_TX_IRQ(U8 data);
/*! \brief Reads the bit group 'EN_TX_IRQ' from the mirror variable of register 'PMU_IRT_Sent_Conf'. */
U8   GH_PMU_IRT_getm_Sent_Conf_EN_TX_IRQ(void);
/*! \brief Writes the bit group 'MODE' of register 'PMU_IRT_Sent_Conf'. */
void GH_PMU_IRT_set_Sent_Conf_MODE(U8 data);
/*! \brief Reads the bit group 'MODE' from the mirror variable of register 'PMU_IRT_Sent_Conf'. */
U8   GH_PMU_IRT_getm_Sent_Conf_MODE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Compvalue (write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Compvalue'. */
void GH_PMU_IRT_set_Compvalue(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Compvalue'. */
U32  GH_PMU_IRT_getm_Compvalue(void);
/*! \brief Writes the bit group 'VALUE' of register 'PMU_IRT_Compvalue'. */
void GH_PMU_IRT_set_Compvalue_VALUE(U8 data);
/*! \brief Reads the bit group 'VALUE' from the mirror variable of register 'PMU_IRT_Compvalue'. */
U8   GH_PMU_IRT_getm_Compvalue_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_IRT_Start (write)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_IRT_Start'. */
void GH_PMU_IRT_set_Start(U32 data);
/*! \brief Reads the mirror variable of the register 'PMU_IRT_Start'. */
U32  GH_PMU_IRT_getm_Start(void);
/*! \brief Writes the bit group 'START_TX' of register 'PMU_IRT_Start'. */
void GH_PMU_IRT_set_Start_START_TX(U8 data);
/*! \brief Reads the bit group 'START_TX' from the mirror variable of register 'PMU_IRT_Start'. */
U8   GH_PMU_IRT_getm_Start_START_TX(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_PMU_IRT_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_pmu_irt.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_PMU_IRT_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

