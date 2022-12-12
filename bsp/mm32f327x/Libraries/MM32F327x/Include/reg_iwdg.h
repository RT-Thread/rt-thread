////////////////////////////////////////////////////////////////////////////////
/// @file     reg_iwdg.h
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

#ifndef __REG_IWDG_H
#define __REG_IWDG_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif



////////////////////////////////////////////////////////////////////////////////
/// @brief IWDG Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define IWDG_BASE                       (APB1PERIPH_BASE + 0x3000)              ///< Base Address: 0x40003000

////////////////////////////////////////////////////////////////////////////////
/// @brief IWDG Register Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 KR;                                                                ///< Key Register                                   offset: 0x00
    __IO u32 PR;                                                                ///< Prescaler Register                             offset: 0x04
    __IO u32 RLR;                                                               ///< Reload Register                                offset: 0x08
    __IO u32 SR;                                                                ///< Status Register                                offset: 0x0C
    __IO u32 CR;                                                                ///< Control Register                               offset: 0x10
    __IO u32  IGEN;                                                              ///< Interrupt Generator Register                   offset: 0x14
    __IO u32  CNT;                                                              ///< Interrupt Generator count Register              offset: 0x18
    __IO u32  PS;                                                              ///< Prescaler count Register              offset: 0x1C
} IWDG_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief IWDG type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define IWDG                            ((IWDG_TypeDef*) IWDG_BASE)

////////////////////////////////////////////////////////////////////////////////
/// @brief IWDG_KR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define IWDG_KEYR_KEY_Pos               (0)
#define IWDG_KEYR_KEY                   (0xFFFFU << IWDG_KEYR_KEY_Pos)          ///< Key Value

////////////////////////////////////////////////////////////////////////////////
/// @brief IWDG_PR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define IWDG_PR_PRE_Pos                 (0)
#define IWDG_PR_PRE                     (0x07U << IWDG_PR_PRE_Pos)              ///< Prescaler divided by 4
#define IWDG_PR_PRE_DIV4                (0x00U << IWDG_PR_PRE_Pos)              ///< Prescaler divided by 4
#define IWDG_PR_PRE_DIV8                (0x01U << IWDG_PR_PRE_Pos)              ///< Prescaler divided by 8
#define IWDG_PR_PRE_DIV16               (0x02U << IWDG_PR_PRE_Pos)              ///< Prescaler divided by 16
#define IWDG_PR_PRE_DIV32               (0x03U << IWDG_PR_PRE_Pos)              ///< Prescaler divided by 32
#define IWDG_PR_PRE_DIV64               (0x04U << IWDG_PR_PRE_Pos)              ///< Prescaler divided by 64
#define IWDG_PR_PRE_DIV128              (0x05U << IWDG_PR_PRE_Pos)              ///< Prescaler divided by 128
#define IWDG_PR_PRE_DIV256              (0x06U << IWDG_PR_PRE_Pos)              ///< Prescaler divided by 256

////////////////////////////////////////////////////////////////////////////////
/// @brief IWDG_RLR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define IWDG_RLR_RL_Pos                 (0)
#define IWDG_RLR_RL                     (0x0FFFU << IWDG_RLR_RL_Pos)            ///< Watchdog counter reload value

////////////////////////////////////////////////////////////////////////////////
/// @brief IWDG_SR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define IWDG_SR_PVU_Pos                 (0)
#define IWDG_SR_PVU                     (0x01U << IWDG_SR_PVU_Pos)              ///< Watchdog prescaler value update
#define IWDG_SR_RVU_Pos                 (1)
#define IWDG_SR_RVU                     (0x01U << IWDG_SR_RVU_Pos)              ///< Watchdog counter reload value update

#define IWDG_SR_IVU_Pos                 (2)
#define IWDG_SR_IVU                     (0x01U << IWDG_SR_IVU_Pos)

#define IWDG_SR_UPDATE_Pos                 (3)
#define IWDG_SR_UPDATE                     (0x01U << IWDG_SR_UPDATE_Pos)

////////////////////////////////////////////////////////////////////////////////
/// @brief IWDG_CR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define IWDG_CR_IRQSEL_Pos          (0)
#define IWDG_CR_IRQSEL              (0x01U << IWDG_CR_IRQSEL_Pos)           ///< IWDG overflow operation selection
#define IWDG_CR_IRQCLR_Pos          (1)
#define IWDG_CR_IRQCLR              (0x01U << IWDG_CR_IRQCLR_Pos)           ///< IWDG interrupt clear

////////////////////////////////////////////////////////////////////////////////
/// @brief IWDG_IGRN Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define IWDG_IGEN_IGEN_Pos          (0)
#define IWDG_IGEN_IGEN              (0xFFFU << IWDG_CR_IRQSEL_Pos)          ///< IWDG Interrupt Generate value


/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
