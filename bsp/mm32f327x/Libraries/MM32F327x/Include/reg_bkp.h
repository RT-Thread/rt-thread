////////////////////////////////////////////////////////////////////////////////
/// @file     reg_bkp.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE SERIES OF
///           MM32 FIRMWARE LIBRARY.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion

#ifndef __REG_BKP_H
#define __REG_BKP_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif







////////////////////////////////////////////////////////////////////////////////
/// @brief BKP Base Address Definition
////////////////////////////////////////////////////////////////////////////////


#define BKP_BASE                        (APB1PERIPH_BASE + 0x2840)              ///< Base Address: 0x40002840




////////////////////////////////////////////////////////////////////////////////
/// @brief BKP Register Structure Definition
////////////////////////////////////////////////////////////////////////////////



#define BKP_NUMBER  20

typedef struct {
    __IO u32 RTCCR;                                                             ///< RTC clock calibration register,                offset: 0x00
    __IO u32 CR;                                                                ///< BKP control register,                          offset: 0x04
    __IO u32 CSR;                                                               ///< BKP control/status register,                   offset: 0x08
    __IO u32 RESERVED0;                                                         ///< Reserved,                                      offset: 0x0C
    __IO u32 DR1;                                                               ///< BKP data register 1,                           offset: 0x10
    __IO u32 DR2;                                                               ///< BKP data register 2,                           offset: 0x14
    __IO u32 DR3;                                                               ///< BKP data register 3,                           offset: 0x18
    __IO u32 DR4;                                                               ///< BKP data register 4,                           offset: 0x1C
    __IO u32 DR5;                                                               ///< BKP data register 5,                           offset: 0x20
    __IO u32 DR6;                                                               ///< BKP data register 6,                           offset: 0x24
    __IO u32 DR7;                                                               ///< BKP data register 7,                           offset: 0x28
    __IO u32 DR8;                                                               ///< BKP data register 8,                           offset: 0x2C
    __IO u32 DR9;                                                               ///< BKP data register 9,                           offset: 0x30
    __IO u32 DR10;                                                              ///< BKP data register 10                           offset: 0x34
    __IO u32 DR11;                                                              ///< BKP data register 11,                          offset: 0x38
    __IO u32 DR12;                                                              ///< BKP data register 12,                          offset: 0x3C
    __IO u32 DR13;                                                              ///< BKP data register 13,                          offset: 0x40
    __IO u32 DR14;                                                              ///< BKP data register 14,                          offset: 0x44
    __IO u32 DR15;                                                              ///< BKP data register 15,                          offset: 0x48
    __IO u32 DR16;                                                              ///< BKP data register 16,                          offset: 0x4C
    __IO u32 DR17;                                                              ///< BKP data register 17,                          offset: 0x50
    __IO u32 DR18;                                                              ///< BKP data register 18,                          offset: 0x54
    __IO u32 DR19;                                                              ///< BKP data register 19,                          offset: 0x58
    __IO u32 DR20;                                                              ///< BKP data register 20,                          offset: 0x5C
} BKP_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief BKP type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define BKP                          ((BKP_TypeDef*) BKP_BASE)



////////////////////////////////////////////////////////////////////////////////
/// @brief BKP_DRn Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define BKP_DR_DATA_Pos              (0)
#define BKP_DR_DATA                  (0xFFFFU << BKP_DR_DATA)                ///< Backup data

////////////////////////////////////////////////////////////////////////////////
/// @brief BKP_RTCCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define BKP_RTCCR_CAL_Pos           (0)
#define BKP_RTCCR_CAL               (0x7FU << BKP_RTCCR_CAL_Pos)            ///< Calibration value
#define BKP_RTCCR_CCO_Pos           (7)
#define BKP_RTCCR_CCO               (0x01U << BKP_RTCCR_CCO_Pos)            ///< Calibration Clock Output
#define BKP_RTCCR_ASOE_Pos          (8)
#define BKP_RTCCR_ASOE              (0x01U << BKP_RTCCR_ASOE_Pos)           ///< Alarm or Second Output Enable
#define BKP_RTCCR_ASOS_Pos          (9)
#define BKP_RTCCR_ASOS              (0x01U << BKP_RTCCR_ASOS_Pos)           ///< Alarm or Second Output Selection

////////////////////////////////////////////////////////////////////////////////
/// @brief BKP_CR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define BKP_CR_TPE_Pos              (0)
#define BKP_CR_TPE                  (0x01U << BKP_CR_TPE_Pos)               ///< TAMPER pin enable
#define BKP_CR_TPAL_Pos             (1)
#define BKP_CR_TPAL                 (0x01U << BKP_CR_TPAL_Pos)              ///< TAMPER pin active level

////////////////////////////////////////////////////////////////////////////////
/// @brief BKP_CSR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define BKP_CSR_CTE_Pos             (0)
#define BKP_CSR_CTE                 (0x01U << BKP_CSR_CTE_Pos)              ///< Clear Tamper event
#define BKP_CSR_CTI_Pos             (1)
#define BKP_CSR_CTI                 (0x01U << BKP_CSR_CTI_Pos)              ///< Clear Tamper Interrupt
#define BKP_CSR_TPIE_Pos            (2)
#define BKP_CSR_TPIE                (0x01U << BKP_CSR_TPIE_Pos)             ///< TAMPER Pin interrupt enable
#define BKP_CSR_TEF_Pos             (8)
#define BKP_CSR_TEF                 (0x01U << BKP_CSR_TEF_Pos)              ///< Tamper Event Flag
#define BKP_CSR_TIF_Pos             (9)
#define BKP_CSR_TIF                 (0x01U << BKP_CSR_TIF_Pos)              ///< Tamper Interrupt Flag





/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
