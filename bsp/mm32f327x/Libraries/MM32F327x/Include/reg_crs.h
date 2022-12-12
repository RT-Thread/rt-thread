////////////////////////////////////////////////////////////////////////////////
/// @file     reg_crs.h
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

#ifndef __REG_CRS_H
#define __REG_CRS_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif








////////////////////////////////////////////////////////////////////////////////
/// @brief CRS Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define CRS_BASE                        (APB1PERIPH_BASE + 0x6C00)              ///< Base Address: 0x40006C00



////////////////////////////////////////////////////////////////////////////////
/// @brief CRS Register Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 CR;                                                                ///< Control Register                    offset: 0x00
    __IO u32 CFGR;                                                              ///< Configuration Register              offset: 0x04
    __IO u32 ISR;                                                               ///< Interrupt and Status Register       offset: 0x08
    __IO u32 ICR;                                                               ///< Interrupt Flag Clear Register       offset: 0x0C
} CRS_TypeDef;



////////////////////////////////////////////////////////////////////////////////
/// @brief CRS type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define CRS                         ((CRS_TypeDef*) CRS_BASE)



////////////////////////////////////////////////////////////////////////////////
/// @brief CRS_CR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CRS_CR_OKIE_Pos             (0)
#define CRS_CR_OKIE                 (0x01U << CRS_CR_OKIE_Pos)              ///< SYNC event OK interrupt enable
#define CRS_CR_WARNIE_Pos           (1)
#define CRS_CR_WARNIE               (0x01U << CRS_CR_WARNIE_Pos)            ///< SYNC warning interrupt enable
#define CRS_CR_ERRIE_Pos            (2)
#define CRS_CR_ERRIE                (0x01U << CRS_CR_ERRIE_Pos)             ///< Synchronization or trimming error interrupt enable
#define CRS_CR_EXPTIE_Pos           (3)
#define CRS_CR_EXPTIE               (0x01U << CRS_CR_EXPTIE_Pos)            ///< Expected SYNC interrupt enable
#define CRS_CR_CNTEN_Pos            (5)
#define CRS_CR_CNTEN                (0x01U << CRS_CR_CNTEN_Pos)             ///< Frequency error counter enable
#define CRS_CR_AUTOTRIMEN_Pos       (6)
#define CRS_CR_AUTOTRIMEN           (0x01U << CRS_CR_AUTOTRIMEN_Pos)        ///< Automatic trimming enable
#define CRS_CR_SWSYNC_Pos           (7)
#define CRS_CR_SWSYNC               (0x01U << CRS_CR_SWSYNC_Pos)            ///< Generate software SYNC event
#define CRS_CR_TRIM_Pos             (8)
#define CRS_CR_TRIM                 (0x3FFU << CRS_CR_TRIM_Pos)              ///< HSI 48 oscillator smooth trimming

////////////////////////////////////////////////////////////////////////////////
/// @brief CRS_CFGR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CRS_CFGR_RELOAD_Pos         (0)
#define CRS_CFGR_RELOAD             (0xFFFFU << CRS_CFGR_RELOAD_Pos)        ///< Counter reload value
#define CRS_CFGR_FELIM_Pos          (16)
#define CRS_CFGR_FELIM              (0xFFU << CRS_CFGR_FELIM_Pos)           ///< Frequency error limit
#define CRS_CFGR_DIV_Pos            (24)
#define CRS_CFGR_DIV                (0x07U << CRS_CFGR_DIV_Pos)             ///< SYNC divider
#define CRS_CFGR_SRC_Pos            (28)
#define CRS_CFGR_SRC                (0x03U << CRS_CFGR_SRC_Pos)             ///< SYNC signal source selection
#define CRS_CFGR_SRC_MCO            (0x00U << CRS_CFGR_SRC_Pos)
#define CRS_CFGR_SRC_USBSOF         (0x02U << CRS_CFGR_SRC_Pos)
#define CRS_CFGR_POL_Pos            (31)
#define CRS_CFGR_POL                (0x01U << CRS_CFGR_POL_Pos)             ///< SYNC polarity selection

////////////////////////////////////////////////////////////////////////////////
/// @brief CRS_ISR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CRS_ISR_OKIF_Pos            (0)
#define CRS_ISR_OKIF                (0x01U << CRS_ISR_OKIF_Pos)             ///< SYNC event OK flag
#define CRS_ISR_WARNIF_Pos          (1)
#define CRS_ISR_WARNIF              (0x01U << CRS_ISR_WARNIF_Pos)           ///< SYNC warning flag
#define CRS_ISR_ERRIF_Pos           (2)
#define CRS_ISR_ERRIF               (0x01U << CRS_ISR_ERRIF_Pos)            ///< Error flag
#define CRS_ISR_EXPTIF_Pos          (3)
#define CRS_ISR_EXPTIF              (0x01U << CRS_ISR_EXPTIF_Pos)           ///< Expected SYNC flag
#define CRS_ISR_ERR_Pos             (8)
#define CRS_ISR_ERR                 (0x01U << CRS_ISR_ERR_Pos)              ///< SYNC error
#define CRS_ISR_MISS_Pos            (9)
#define CRS_ISR_MISS                (0x01U << CRS_ISR_MISS_Pos)             ///< SYNC missed
#define CRS_ISR_OVERFLOW_Pos        (10)
#define CRS_ISR_OVERFLOW            (0x01U << CRS_ISR_OVERFLOW_Pos)         ///< Trimming overflow or underflow
#define CRS_ISR_FEDIR_Pos           (15)
#define CRS_ISR_FEDIR               (0x01U << CRS_ISR_FEDIR_Pos)            ///< Frequency error direction
#define CRS_ISR_FECAP_Pos           (16)
#define CRS_ISR_FECAP               (0xFFFFU << CRS_ISR_FECAP_Pos)          ///< Frequency error capture

////////////////////////////////////////////////////////////////////////////////
/// @brief CRS_ICR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CRS_ICR_OK_Pos              (0)
#define CRS_ICR_OK                  (0x01U << CRS_ICR_OK_Pos)               ///< SYNC event OK clear flag
#define CRS_ICR_WARN_Pos            (1)
#define CRS_ICR_WARN                (0x01U << CRS_ICR_WARN_Pos)             ///< SYNC warning clear flag
#define CRS_ICR_ERR_Pos             (2)
#define CRS_ICR_ERR                 (0x01U << CRS_ICR_ERR_Pos)              ///< Error clear flag
#define CRS_ICR_EXPT_Pos            (3)
#define CRS_ICR_EXPT                (0x01U << CRS_ICR_EXPT_Pos)             ///< Expected SYNC clear flag





/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
