////////////////////////////////////////////////////////////////////////////////
/// @file     reg_pwr.h
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

#ifndef __REG_PWR_H
#define __REG_PWR_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif








////////////////////////////////////////////////////////////////////////////////
/// @brief PWR Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_BASE                        (APB1PERIPH_BASE + 0x7000)              ///< Base Address: 0x40007000





////////////////////////////////////////////////////////////////////////////////
/// @brief PWR Register Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    union {
        __IO u32 CR;                                                            ///< Control register,                             offset: 0x00
        __IO u32 CR1;
    };
    union {
        __IO u32 CSR;                                                               ///< Control Status register                        offset: 0x04
        __IO u32 CSR1;
    };
    __IO u32 CR2;                                                               ///< Control register  2                            offset: 0x08
    __IO u32 CR3;                                                               ///< Control register  3                            offset: 0x0C
    __IO u32 CR4;                                                               ///< Control register  4                            offset: 0x10
    __IO u32 CR5;                                                               ///< Control register  5                            offset: 0x14
    __IO u32 CR6;                                                               ///< Control register  6                            offset: 0x18
    __IO u32 SR;                                                                ///< Status  register                               offset: 0x1C
    __IO u32 SCR;                                                               ///< clear status register                          offset: 0x20
    __IO u32 CFGR;                                                              ///< Configuration register                         offset: 0x24
} PWR_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief PWR type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define PWR                             ((PWR_TypeDef*) PWR_BASE)



////////////////////////////////////////////////////////////////////////////////
/// @brief PWR_CR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_CR_LDPS_Pos                 (0)
#define PWR_CR_LDPS                     (0x01U  << PWR_CR_LDPS_Pos)             ///< Domain Write Protction

#define PWR_CR_PDDS_Pos                 (1)
#define PWR_CR_PDDS                     (0x01U  << PWR_CR_PDDS_Pos)             ///< Power Down Deepsleep
#define PWR_CR_CSBF_Pos                 (3)
#define PWR_CR_CSBF                     (0x01U  << PWR_CR_CSBF_Pos)             ///< Clear Standby Flag
#define PWR_CR_LPR_Pos                  (13)
#define PWR_CR_LPR                      (0x01U  << PWR_CR_LPR_Pos)              ///< Low power run
#define PWR_CR_VOS_Pos                  (14)
#define PWR_CR_VOS0                     (0x00U  << PWR_CR_VOS_Pos)              ///< Modulator Voltage Output Select 1.80V
#define PWR_CR_VOS1                     (0x01U  << PWR_CR_VOS_Pos)              ///< Modulator Voltage Output Select 1.70V
#define PWR_CR_VOS2                     (0x02U  << PWR_CR_VOS_Pos)              ///< Modulator Voltage Output Select 1.60V
#define PWR_CR_VOS3                     (0x03U  << PWR_CR_VOS_Pos)              ///< Modulator Voltage Output Select 1.55V

////////////////////////////////////////////////////////////////////////////////
/// @brief PWR_CSR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_CSR_SBF_Pos                 (1)
#define PWR_CSR_SBF                     (0x01U  << PWR_CSR_SBF_Pos)             ///< Standby Flag
#define PWR_CSR_VOSRDY_Pos              (14)
#define PWR_CSR_VOSRDY                  (0x01U  << PWR_CR_VOSRDY_Pos)           ///< Voltage Modulator Output Selection Ready
////////////////////////////////////////////////////////////////////////////////
/// @brief PWR_CR2 register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_CR2_EWUP1_Pos                (0)
#define PWR_CR2_EWUP1                    (0x01U << PWR_CR2_EWUP1_Pos)           ///< Enable WKUP1 wake-up pin
#define PWR_CR2_EWUP2_Pos                (1)
#define PWR_CR2_EWUP2                    (0x01U << PWR_CR2_EWUP2_Pos)           ///< Enable WKUP2 wake-up pin
#define PWR_CR2_EWUP3_Pos                (2)
#define PWR_CR2_EWUP3                    (0x01U << PWR_CR2_EWUP3_Pos)           ///< Enable WKUP3 wake-up pin
#define PWR_CR2_EWUP4_Pos                (3)
#define PWR_CR2_EWUP4                    (0x01U << PWR_CR2_EWUP4_Pos)           ///< Enable WKUP4 wake-up pin
#define PWR_CR2_EWUP5_Pos                (4)
#define PWR_CR2_EWUP5                    (0x01U << PWR_CR2_EWUP5_Pos)           ///< Enable WKUP5 wake-up pin
#define PWR_CR2_EWUP6_Pos                (5)
#define PWR_CR2_EWUP6                    (0x01U << PWR_CR2_EWUP6_Pos)           ///< Enable WKUP6 wake-up pin
#define PWR_CR2_ENWU_Pos                 (15)
#define PWR_CR2_ENWU                     (0x01U << PWR_CR2_ENWU_Pos)            ///< Enable wakeup module
////////////////////////////////////////////////////////////////////////////////
/// @brief PWR_CR3 register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_CR3_WP1_Pos                (0)
#define PWR_CR3_WP1                    (0x01U << PWR_CR3_WP1_Pos)               ///<  WKUP1 used for event polarity detection
#define PWR_CR3_WP2_Pos                (1)
#define PWR_CR3_WP2                    (0x01U << PWR_CR3_WP2_Pos)               ///<  WKUP2 used for event polarity detection
#define PWR_CR3_WP3_Pos                (2)
#define PWR_CR3_WP3                    (0x01U << PWR_CR3_WP3_Pos)               ///<  WKUP3 used for event polarity detection
#define PWR_CR3_WP4_Pos                (3)
#define PWR_CR3_WP4                    (0x01U << PWR_CR3_WP4_Pos)               ///<  WKUP4 used for event polarity detection
#define PWR_CR3_WP5_Pos                (4)
#define PWR_CR3_WP5                    (0x01U << PWR_CR3_WP5_Pos)               ///<  WKUP5 used for event polarity detection
#define PWR_CR3_WP6_Pos                (5)
#define PWR_CR3_WP6                    (0x01U << PWR_CR3_WP6_Pos)               ///<  WKUP6 used for event polarity detection
////////////////////////////////////////////////////////////////////////////////
/// @brief PWR_CR4 register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_CR4_FILTSEL0_Pos           (0)
#define PWR_CR4_FILTSEL0               (0x01U << PWR_CR4_FILTSEL0_Pos)          ///<  selection wake-up source
#define PWR_CR4_FILTE0_Pos             (2)
#define PWR_CR4_FILTE0                 (0x01U << PWR_CR4_FILTE0_Pos)            ///<  enable Filter 0
#define PWR_CR4_FILTF0_Pos             (4)
#define PWR_CR4_FILTF0                 (0x01U << PWR_CR4_FILTF0_Pos)            ///<  Whether the wake source passes through filter 0
#define PWR_CR4_FILTCNT0_Pos           (8)
#define PWR_CR4_FILTCNT0               (0xFFU << PWR_CR4_FILTCNT0_Pos)          ///<  Filter 0 counter
////////////////////////////////////////////////////////////////////////////////
/// @brief PWR_CR5 register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_CR5_FILTSEL1_Pos           (0)
#define PWR_CR5_FILTSEL1               (0x01U << PWR_CR5_FILTSEL1_Pos)          ///<  selection wake-up source
#define PWR_CR5_FILTE1_Pos             (2)
#define PWR_CR5_FILTE1                 (0x01U << PWR_CR5_FILTE1_Pos)            ///<  enable Filter 1
#define PWR_CR5_FILTF1_Pos             (4)
#define PWR_CR5_FILTF1                 (0x01U << PWR_CR5_FILTF1_Pos)            ///<  Whether the wake source passes through filter 1
#define PWR_CR5_FILTCNT1_Pos           (8)
#define PWR_CR5_FILTCNT1               (0xFFU << PWR_CR5_FILTCNT1_Pos)          ///<  Filter 1 counter
////////////////////////////////////////////////////////////////////////////////
/// @brief PWR_CR6 register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_CR6_STDBY_FS_W_Pos          (0)
#define PWR_CR6_STDBY_FS_W1             (0x00U << PWR_CR6_STDBY_FS_W_Pos)       ///<  1 LSI cycle wake
#define PWR_CR6_STDBY_FS_W2             (0x01U << PWR_CR6_STDBY_FS_W_Pos)       ///<  2 LSI cycle wake
#define PWR_CR6_STDBY_FS_W3             (0x02U << PWR_CR6_STDBY_FS_W_Pos)       ///<  3 LSI cycle wake
#define PWR_CR6_STDBY_FS_W4             (0x03U << PWR_CR6_STDBY_FS_W_Pos)       ///<  4 LSI cycle wake
#define PWR_CR6_STDBY_FS_W5             (0x04U << PWR_CR6_STDBY_FS_W_Pos)       ///<  5 LSI cycle wake
#define PWR_CR6_STDBY_FS_W6             (0x05U << PWR_CR6_STDBY_FS_W_Pos)       ///<  6 LSI cycle wake
#define PWR_CR6_STDBY_FS_W7             (0x06U << PWR_CR6_STDBY_FS_W_Pos)       ///<  7 LSI cycle wake
#define PWR_CR6_STDBY_FS_W8             (0x07U << PWR_CR6_STDBY_FS_W_Pos)       ///<  8 LSI cycle wake
////////////////////////////////////////////////////////////////////////////////
/// @brief PWR_SR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_SR_WUF1_Pos                (0)
#define PWR_SR_WUF1                    (0x01U << PWR_SR_WUF1_Pos)               ///<  wake-up flag 1
#define PWR_SR_WUF2_Pos                (1)
#define PWR_SR_WUF2                    (0x01U << PWR_SR_WUF2_Pos)               ///<  wake-up flag 2
#define PWR_SR_WUF3_Pos                (2)
#define PWR_SR_WUF3                    (0x01U << PWR_SR_WUF3_Pos)               ///<  wake-up flag 3
#define PWR_SR_WUF4_Pos                (3)
#define PWR_SR_WUF4                    (0x01U << PWR_SR_WUF4_Pos)               ///<  wake-up flag 4
#define PWR_SR_WUF5_Pos                (4)
#define PWR_SR_WUF5                    (0x01U << PWR_SR_WUF5_Pos)               ///<  wake-up flag 5
#define PWR_SR_WUF6_Pos                (5)
#define PWR_SR_WUF6                    (0x01U << PWR_SR_WUF6_Pos)               ///<  wake-up flag 6
////////////////////////////////////////////////////////////////////////////////
/// @brief PWR_SCR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_SCR_CWUF1_Pos              (0)
#define PWR_SCR_CWUF1                  (0x01U << PWR_SCR_CWUF1_Pos)             ///< clear wake-up flag 1 
#define PWR_SCR_CWUF2_Pos              (1)
#define PWR_SCR_CWUF2                  (0x01U << PWR_SCR_CWUF2_Pos)             ///< clear wake-up flag 2
#define PWR_SCR_CWUF3_Pos              (2)
#define PWR_SCR_CWUF3                  (0x01U << PWR_SCR_CWUF3_Pos)             ///< clear wake-up flag 3
#define PWR_SCR_CWUF4_Pos              (3)
#define PWR_SCR_CWUF4                  (0x01U << PWR_SCR_CWUF4_Pos)             ///< clear wake-up flag 4
#define PWR_SCR_CWUF5_Pos              (4)
#define PWR_SCR_CWUF5                  (0x01U << PWR_SCR_CWUF5_Pos)             ///< clear wake-up flag 5
#define PWR_SCR_CWUF6_Pos              (5)
#define PWR_SCR_CWUF6                  (0x01U << PWR_SCR_CWUF6_Pos)             ///< clear wake-up flag 6
////////////////////////////////////////////////////////////////////////////////
/// @brief PWR_CFGR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_CFGR_LSICALSEL_Pos         (0)
#define PWR_CFGR_LSICALSEL             (0x1FU << PWR_CFGR_LSICALSEL_Pos)        ///< Enable internal clock calibration 
#define PWR_CFGR_LSICAL_Pos            (5)
#define PWR_CFGR_LSICAL                (0x1FU << PWR_CFGR_LSICAL_Pos)           ///< Internal high-speed clock calibration

/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
