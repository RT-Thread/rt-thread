////////////////////////////////////////////////////////////////////////////////
/// @file     reg_crc.h
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

#ifndef __REG_CRC_H
#define __REG_CRC_H

// Files includes
#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif







////////////////////////////////////////////////////////////////////////////////
/// @brief CRC Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define CRC_BASE                        (AHBPERIPH_BASE + 0x3000)               ///< Base Address: 0x40023000




////////////////////////////////////////////////////////////////////////////////
/// @brief CRC Register Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32   DR;                                                              ///< CRC data register,                             offset: 0x00
    __IO u32   IDR;                                                             ///< CRC independent data register,                 offset: 0x04
    __IO u32   CR;                                                              ///< CRC control register,                          offset: 0x08
    __IO u32   MIR;                                                              ///< Middle data register,                          offset: 0x08
} CRC_TypeDef;



////////////////////////////////////////////////////////////////////////////////
/// @brief CRC type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define CRC                             ((CRC_TypeDef*) CRC_BASE)



////////////////////////////////////////////////////////////////////////////////
/// @brief CRC_DR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CRC_DR_DATA_Pos                 (0)
#define CRC_DR_DATA                     (0xFFFFFFFFU << CRC_DR_DATA_Pos)        ///< Data register bits
////////////////////////////////////////////////////////////////////////////////
/// @brief CRC_IDR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CRC_IDR_DATA_Pos                (0)
#define CRC_IDR_DATA                    (0xFFU << CRC_IDR_DATA_Pos)             ///< General-purpose 8-bit data register bits

////////////////////////////////////////////////////////////////////////////////
/// @brief CRC_CTRL Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CRC_CR_RESET_Pos                (0)
#define CRC_CR_RESET                    (0x01U << CRC_CR_RESET_Pos)             ///< RESET bit
////////////////////////////////////////////////////////////////////////////////
/// @brief CRC_MIR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CRC_MIR_Pos                 (0)
#define CRC_MIR                     (0xFFFFFFFFU << CRC_MIR_Pos)        ///< Middle data register




/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
