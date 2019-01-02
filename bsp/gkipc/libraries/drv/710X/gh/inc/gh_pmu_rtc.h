/*!
*******************************************************************************
**
** \file      gh_pmu_rtc.h
**
** \brief     PMU_RTC.
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
#ifndef _GH_PMU_RTC_H
#define _GH_PMU_RTC_H

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

#define GH_PMU_RTC_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_PMU_RTC_DEBUG_PRINT_FUNCTION printk
#else
#define GH_PMU_RTC_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_PMU_RTC_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_PMU_RTC_SYS_CONFIG                              FIO_ADDRESS(PMU_RTC,0x90080000) /* read/write */
#define REG_PMU_RTC_P_SCALER_DIV0                           FIO_ADDRESS(PMU_RTC,0x90080004) /* read/write */
#define REG_PMU_RTC_P_SCALER_DIV1                           FIO_ADDRESS(PMU_RTC,0x90080008) /* read/write */
#define REG_PMU_RTC_P_SCALER_DIV2                           FIO_ADDRESS(PMU_RTC,0x9008000C) /* read/write */
#define REG_PMU_RTC_P_SCALER_DIV3                           FIO_ADDRESS(PMU_RTC,0x90080010) /* read/write */
#define REG_PMU_RTC_PRE_LOAD_HOUR                           FIO_ADDRESS(PMU_RTC,0x90080014) /* write */
#define REG_PMU_RTC_PRE_LOAD_MIN                            FIO_ADDRESS(PMU_RTC,0x90080018) /* write */
#define REG_PMU_RTC_PRE_LOAD_SEC                            FIO_ADDRESS(PMU_RTC,0x9008001C) /* write */
#define REG_PMU_RTC_IRQ_CLEAR                               FIO_ADDRESS(PMU_RTC,0x90080020) /* write */
#define REG_PMU_RTC_PRE_LOAD_DAY_L                          FIO_ADDRESS(PMU_RTC,0x90080024) /* write */
#define REG_PMU_RTC_PRE_LOAD_DAY_H                          FIO_ADDRESS(PMU_RTC,0x90080028) /* write */
#define REG_PMU_RTC_IRQ_STATUS                              FIO_ADDRESS(PMU_RTC,0x90080068) /* read */
#define REG_PMU_RTC_SEC_VALUE                               FIO_ADDRESS(PMU_RTC,0x9008006c) /* read */
#define REG_PMU_RTC_MIN_VALUE                               FIO_ADDRESS(PMU_RTC,0x90080070) /* read */
#define REG_PMU_RTC_HOUR_VALUE                              FIO_ADDRESS(PMU_RTC,0x90080074) /* read */
#define REG_PMU_RTC_DAY_L_VALUE                             FIO_ADDRESS(PMU_RTC,0x90080078) /* read */
#define REG_PMU_RTC_DAY_H_VALUE                             FIO_ADDRESS(PMU_RTC,0x9008007c) /* read */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* PMU_RTC_SYS_CONFIG */
    U8 all;
    struct {
        U8 enable                       : 1;
        U8                              : 2;
        U8 stop                         : 1;
        U8 pause                        : 1;
        U8 irq                          : 1;
        U8                              : 2;
    } bitc;
} GH_PMU_RTC_SYS_CONFIG_S;

typedef union { /* PMU_RTC_IRQ_CLEAR */
    U8 all;
    struct {
        U8 clear                        : 1;
        U8                              : 7;
    } bitc;
} GH_PMU_RTC_IRQ_CLEAR_S;

typedef union { /* PMU_RTC_IRQ_STATUS */
    U32 all;
    struct {
        U32 gen                         : 1;
        U32                             : 31;
    } bitc;
} GH_PMU_RTC_IRQ_STATUS_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern U8                                      m_pmu_rtc_pre_load_hour;
extern U8                                      m_pmu_rtc_pre_load_min;
extern U8                                      m_pmu_rtc_pre_load_sec;
extern GH_PMU_RTC_IRQ_CLEAR_S                  m_pmu_rtc_irq_clear;
extern U8                                      m_pmu_rtc_pre_load_day_l;
extern U8                                      m_pmu_rtc_pre_load_day_h;

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_SYS_CONFIG (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_RTC_SYS_CONFIG'. */
void GH_PMU_RTC_set_SYS_CONFIG(U8 data);
/*! \brief Reads the register 'PMU_RTC_SYS_CONFIG'. */
U8   GH_PMU_RTC_get_SYS_CONFIG(void);
/*! \brief Writes the bit group 'Enable' of register 'PMU_RTC_SYS_CONFIG'. */
void GH_PMU_RTC_set_SYS_CONFIG_Enable(U8 data);
/*! \brief Reads the bit group 'Enable' of register 'PMU_RTC_SYS_CONFIG'. */
U8   GH_PMU_RTC_get_SYS_CONFIG_Enable(void);
/*! \brief Writes the bit group 'Stop' of register 'PMU_RTC_SYS_CONFIG'. */
void GH_PMU_RTC_set_SYS_CONFIG_Stop(U8 data);
/*! \brief Reads the bit group 'Stop' of register 'PMU_RTC_SYS_CONFIG'. */
U8   GH_PMU_RTC_get_SYS_CONFIG_Stop(void);
/*! \brief Writes the bit group 'Pause' of register 'PMU_RTC_SYS_CONFIG'. */
void GH_PMU_RTC_set_SYS_CONFIG_Pause(U8 data);
/*! \brief Reads the bit group 'Pause' of register 'PMU_RTC_SYS_CONFIG'. */
U8   GH_PMU_RTC_get_SYS_CONFIG_Pause(void);
/*! \brief Writes the bit group 'IRQ' of register 'PMU_RTC_SYS_CONFIG'. */
void GH_PMU_RTC_set_SYS_CONFIG_IRQ(U8 data);
/*! \brief Reads the bit group 'IRQ' of register 'PMU_RTC_SYS_CONFIG'. */
U8   GH_PMU_RTC_get_SYS_CONFIG_IRQ(void);

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_P_SCALER_DIV0 (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_RTC_P_SCALER_DIV0'. */
void GH_PMU_RTC_set_P_SCALER_DIV0(U8 data);
/*! \brief Reads the register 'PMU_RTC_P_SCALER_DIV0'. */
U8   GH_PMU_RTC_get_P_SCALER_DIV0(void);

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_P_SCALER_DIV1 (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_RTC_P_SCALER_DIV1'. */
void GH_PMU_RTC_set_P_SCALER_DIV1(U8 data);
/*! \brief Reads the register 'PMU_RTC_P_SCALER_DIV1'. */
U8   GH_PMU_RTC_get_P_SCALER_DIV1(void);

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_P_SCALER_DIV2 (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_RTC_P_SCALER_DIV2'. */
void GH_PMU_RTC_set_P_SCALER_DIV2(U8 data);
/*! \brief Reads the register 'PMU_RTC_P_SCALER_DIV2'. */
U8   GH_PMU_RTC_get_P_SCALER_DIV2(void);

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_P_SCALER_DIV3 (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_RTC_P_SCALER_DIV3'. */
void GH_PMU_RTC_set_P_SCALER_DIV3(U8 data);
/*! \brief Reads the register 'PMU_RTC_P_SCALER_DIV3'. */
U8   GH_PMU_RTC_get_P_SCALER_DIV3(void);

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_PRE_LOAD_HOUR (write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_RTC_PRE_LOAD_HOUR'. */
void GH_PMU_RTC_set_PRE_LOAD_HOUR(U8 data);
/*! \brief Reads the mirror variable of the register 'PMU_RTC_PRE_LOAD_HOUR'. */
U8   GH_PMU_RTC_getm_PRE_LOAD_HOUR(void);

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_PRE_LOAD_MIN (write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_RTC_PRE_LOAD_MIN'. */
void GH_PMU_RTC_set_PRE_LOAD_MIN(U8 data);
/*! \brief Reads the mirror variable of the register 'PMU_RTC_PRE_LOAD_MIN'. */
U8   GH_PMU_RTC_getm_PRE_LOAD_MIN(void);

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_PRE_LOAD_SEC (write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_RTC_PRE_LOAD_SEC'. */
void GH_PMU_RTC_set_PRE_LOAD_SEC(U8 data);
/*! \brief Reads the mirror variable of the register 'PMU_RTC_PRE_LOAD_SEC'. */
U8   GH_PMU_RTC_getm_PRE_LOAD_SEC(void);

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_IRQ_CLEAR (write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_RTC_IRQ_CLEAR'. */
void GH_PMU_RTC_set_IRQ_CLEAR(U8 data);
/*! \brief Reads the mirror variable of the register 'PMU_RTC_IRQ_CLEAR'. */
U8   GH_PMU_RTC_getm_IRQ_CLEAR(void);
/*! \brief Writes the bit group 'Clear' of register 'PMU_RTC_IRQ_CLEAR'. */
void GH_PMU_RTC_set_IRQ_CLEAR_Clear(U8 data);
/*! \brief Reads the bit group 'Clear' from the mirror variable of register 'PMU_RTC_IRQ_CLEAR'. */
U8   GH_PMU_RTC_getm_IRQ_CLEAR_Clear(void);

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_PRE_LOAD_DAY_L (write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_RTC_PRE_LOAD_DAY_L'. */
void GH_PMU_RTC_set_PRE_LOAD_DAY_L(U8 data);
/*! \brief Reads the mirror variable of the register 'PMU_RTC_PRE_LOAD_DAY_L'. */
U8   GH_PMU_RTC_getm_PRE_LOAD_DAY_L(void);

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_PRE_LOAD_DAY_H (write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PMU_RTC_PRE_LOAD_DAY_H'. */
void GH_PMU_RTC_set_PRE_LOAD_DAY_H(U8 data);
/*! \brief Reads the mirror variable of the register 'PMU_RTC_PRE_LOAD_DAY_H'. */
U8   GH_PMU_RTC_getm_PRE_LOAD_DAY_H(void);

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_IRQ_STATUS (read)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'PMU_RTC_IRQ_STATUS'. */
U32  GH_PMU_RTC_get_IRQ_STATUS(void);
/*! \brief Reads the bit group 'Gen' of register 'PMU_RTC_IRQ_STATUS'. */
U8   GH_PMU_RTC_get_IRQ_STATUS_Gen(void);

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_SEC_VALUE (read)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'PMU_RTC_SEC_VALUE'. */
U32  GH_PMU_RTC_get_SEC_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_MIN_VALUE (read)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'PMU_RTC_MIN_VALUE'. */
U32  GH_PMU_RTC_get_MIN_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_HOUR_VALUE (read)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'PMU_RTC_HOUR_VALUE'. */
U32  GH_PMU_RTC_get_HOUR_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_DAY_L_VALUE (read)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'PMU_RTC_DAY_L_VALUE'. */
U32  GH_PMU_RTC_get_DAY_L_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register PMU_RTC_DAY_H_VALUE (read)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'PMU_RTC_DAY_H_VALUE'. */
U32  GH_PMU_RTC_get_DAY_H_VALUE(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_PMU_RTC_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_pmu_rtc.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_PMU_RTC_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

