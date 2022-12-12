////////////////////////////////////////////////////////////////////////////////
/// @file     reg_wwdg.h
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

#ifndef __REG_WWDG_H
#define __REG_WWDG_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif











////////////////////////////////////////////////////////////////////////////////
/// @brief WWDG Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define WWDG_BASE                       (APB1PERIPH_BASE + 0x2C00)              ///< Base Address: 0x40002C00



////////////////////////////////////////////////////////////////////////////////
/// @brief WWDG Register Structure Definition
////////////////////////////////////////////////////////////////////////////////
#undef USENCOMBINEREGISTER
#undef USENNEWREGISTER
#undef USENOLDREGISTER
#define USENCOMBINEREGISTER
#ifdef USENCOMBINEREGISTER
typedef struct {
    __IO u32 CR;                                                                ///< Control register                               offset: 0x00
    union {
        __IO u32 CFGR;                                                          ///< Configuration register                         offset: 0x04
        __IO u32 CFR;
    };
    __IO u32 SR;                                                                ///< Status register                                offset: 0x08
} WWDG_TypeDef;
#endif
#ifdef USENNEWREGISTER
typedef struct {
    __IO u32 CR;                                                                ///< Control register                               offset: 0x00
    __IO u32 CFGR;                                                              ///< Configuration register                         offset: 0x04
    __IO u32 SR;                                                                ///< Status register                                offset: 0x08
} WWDG_TypeDef;
#endif
#ifdef USENOLDREGISTER
typedef struct {
    __IO u32 CR;
    __IO u32 CFR;
    __IO u32 SR;
} WWDG_TypeDef;
#endif


////////////////////////////////////////////////////////////////////////////////
/// @brief WWDG type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define WWDG                            ((WWDG_TypeDef*) WWDG_BASE)



////////////////////////////////////////////////////////////////////////////////
/// @brief WWDG_CR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define WWDG_CR_CNT_Pos                 (0)
#define WWDG_CR_CNT                     (0x7FU << WWDG_CR_CNT_Pos)              ///< T[6:0] bits (7-Bit counter (MSB to LSB))
#define WWDG_CR_WDGA_Pos                (7)
#define WWDG_CR_WDGA                    (0x01U << WWDG_CR_WDGA_Pos)             ///< Activation bit

////////////////////////////////////////////////////////////////////////////////
/// @brief WWDG_CFR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define WWDG_CFGR_WINDOW_Pos            (0)
#define WWDG_CFGR_WINDOW                (0x7FU << WWDG_CFGR_WINDOW_Pos)         ///< W[6:0] bits (7-bit window value)
#define WWDG_CFGR_WDGTB_Pos             (7)
#define WWDG_CFGR_WDGTB                 (0x03U << WWDG_CFGR_WDGTB_Pos)          ///< WDGTB[1:0] bits (Timer Base)
#define WWDG_CFGR_WDGTB_1               (0x00U << WWDG_CFGR_WDGTB_Pos)          ///< WDGTB[1:0] bits (Timer Base /1)
#define WWDG_CFGR_WDGTB_2               (0x01U << WWDG_CFGR_WDGTB_Pos)          ///< WDGTB[1:0] bits (Timer Base /2)
#define WWDG_CFGR_WDGTB_4               (0x02U << WWDG_CFGR_WDGTB_Pos)          ///< WDGTB[1:0] bits (Timer Base /4)
#define WWDG_CFGR_WDGTB_8               (0x03U << WWDG_CFGR_WDGTB_Pos)          ///< WDGTB[1:0] bits (Timer Base /8)
#define WWDG_CFGR_EWI_Pos               (9)
#define WWDG_CFGR_EWI                   (0x01U << WWDG_CFGR_EWI_Pos)            ///< Early Wakeup Interrupt

////////////////////////////////////////////////////////////////////////////////
/// @brief WWDG_SR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define WWDG_SR_EWIF_Pos                (0)
#define WWDG_SR_EWIF                    (0x01U << WWDG_SR_EWIF_Pos)             ///< Early Wakeup Interrupt Flag




/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
