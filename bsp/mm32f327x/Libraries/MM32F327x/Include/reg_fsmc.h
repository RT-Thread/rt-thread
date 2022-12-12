////////////////////////////////////////////////////////////////////////////////
/// @file     reg_fsmc.h
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

#ifndef __REG_FSMC_H
#define __REG_FSMC_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif



////////////////////////////////////////////////////////////////////////////////
/// @brief FLASH Base Address Definition
////////////////////////////////////////////////////////////////////////////////

#define FSMC_BANK1_ADDR       (0x60000000UL )
#define FSMC_BANK2_ADDR       (0x60000000UL + 0x4000000 )
#define FSMC_BANK3_ADDR       (0x60000000UL + 0x8000000 )
#define FSMC_BANK4_ADDR       (0x60000000UL + 0xc000000 )
#define FSMC_BASE             (0x60000000UL + 0x40000000)                      ///< Base Address: 0xA0000000

////////////////////////////////////////////////////////////////////////////////
/// @brief FSMC Registers Structure Definition
////////////////////////////////////////////////////////////////////////////////

typedef struct {
    __IO u32 Reservedoffset0x00;                                                ///< Reserved Register                              offset: 0x00
    __IO u32 Reservedoffset0x04;                                                ///< Reserved Register                              offset: 0x04
    __IO u32 Reservedoffset0x08;                                                ///< Reserved Register                              offset: 0x08
    __IO u32 Reservedoffset0x0c;                                                ///< Reserved Register                              offset: 0x0c
    __IO u32 Reservedoffset0x10;                                                ///< Reserved Register                              offset: 0x10
    __IO u32 Reservedoffset0x14;                                                ///< Reserved Register                              offset: 0x14
    __IO u32 Reservedoffset0x18;                                                ///< Reserved Register                              offset: 0x18
    __IO u32 Reservedoffset0x1c;                                                ///< Reserved Register                              offset: 0x1c
    __IO u32 Reservedoffset0x20;                                                ///< Reserved Register                              offset: 0x20
    __IO u32 Reservedoffset0x24;                                                ///< Reserved Register                              offset: 0x24
    __IO u32 Reservedoffset0x28;                                                ///< Reserved Register                              offset: 0x28
    __IO u32 Reservedoffset0x2c;                                                ///< Reserved Register                              offset: 0x2c
    __IO u32 Reservedoffset0x30;                                                ///< Reserved Register                              offset: 0x30
    __IO u32 Reservedoffset0x34;                                                ///< Reserved Register                              offset: 0x34
    __IO u32 Reservedoffset0x38;                                                ///< Reserved Register                              offset: 0x38
    __IO u32 Reservedoffset0x3c;                                                ///< Reserved Register                              offset: 0x3c
    __IO u32 Reservedoffset0x40;                                                ///< Reserved Register                              offset: 0x40
    __IO u32 Reservedoffset0x44;                                                ///< Reserved Register                              offset: 0x44
    __IO u32 Reservedoffset0x48;                                                ///< Reserved Register                              offset: 0x48
    __IO u32 Reservedoffset0x4c;                                                ///< Reserved Register                              offset: 0x4c
    __IO u32 Reservedoffset0x50;                                                ///< Reserved Register                              offset: 0x50
    __IO u32 SMSKR;                                                             ///< SMSKR control Register                         offset: 0x54
    __IO u32 Reservedoffset0x58;                                                ///< Reserved Register                              offset: 0x58
    __IO u32 Reservedoffset0x5c;                                                ///< Reserved Register                              offset: 0x5c
    __IO u32 Reservedoffset0x60;                                                ///< Reserved Register                              offset: 0x60
    __IO u32 Reservedoffset0x64;                                                ///< Reserved Register                              offset: 0x64
    __IO u32 Reservedoffset0x68;                                                ///< Reserved Register                              offset: 0x68
    __IO u32 Reservedoffset0x6c;                                                ///< Reserved Register                              offset: 0x6c
    __IO u32 Reservedoffset0x70;                                                ///< Reserved Register                              offset: 0x70
    __IO u32 Reservedoffset0x74;                                                ///< Reserved Register                              offset: 0x74
    __IO u32 Reservedoffset0x78;                                                ///< Reserved Register                              offset: 0x78
    __IO u32 Reservedoffset0x7c;                                                ///< Reserved Register                              offset: 0x7c
    __IO u32 Reservedoffset0x80;                                                ///< Reserved Register                              offset: 0x80
    __IO u32 Reservedoffset0x84;                                                ///< Reserved Register                              offset: 0x84
    __IO u32 Reservedoffset0x88;                                                ///< Reserved Register                              offset: 0x88
    __IO u32 Reservedoffset0x8c;                                                ///< Reserved Register                              offset: 0x8c
    __IO u32 Reservedoffset0x90;                                                ///< Reserved Register                              offset: 0x90
    __IO u32 SMTMGR_SET0;                                                       ///< SMTMGR_SET Register 0                          offset: 0x94
    __IO u32 SMTMGR_SET1;                                                       ///< SMTMGR_SET Register 1                          offset: 0x98
    __IO u32 SMTMGR_SET2;                                                       ///< SMTMGR_SET Register 2                          offset: 0x9c
    __IO u32 Reservedoffset0xA0;                                                ///< Reserved Register                              offset: 0xa0
    __IO u32 SMCTLR;                                                            ///< Reserved Register                              offset: 0xa4
    __IO u32 Reservedoffset0xA8;                                                ///< Reserved Register                              offset: 0xa8
    __IO u32 Reservedoffset0xAC;                                                ///< Reserved Register                              offset: 0xac
} FSMC_TypeDef;




////////////////////////////////////////////////////////////////////////////////
/// @brief FSMC  type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define FSMC                            ((FSMC_TypeDef*) FSMC_BASE)

////////////////////////////////////////////////////////////////////////////////
/// @brief FSMC_SMSKR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define FSMC_SMSKR_REG_SELECT_Pos          (8)
#define FSMC_SMSKR_REG_SELECT0             (0x00U << FSMC_SMSKR_REG_SELECT_Pos)        ///< timing parameter configures the register group 0
#define FSMC_SMSKR_REG_SELECT1             (0x01U << FSMC_SMSKR_REG_SELECT_Pos)        ///< timing parameter configures the register group 1
#define FSMC_SMSKR_REG_SELECT2             (0x02U << FSMC_SMSKR_REG_SELECT_Pos)        ///< timing parameter configures the register group 2
#define FSMC_SMSKR_MEM_TYPE_Pos            (5)
#define FSMC_SMSKR_MEM_TYPE0               (0x00U << FSMC_SMSKR_MEM_TYPE_Pos)        ///< SDRAM
#define FSMC_SMSKR_MEM_TYPE1               (0x01U << FSMC_SMSKR_MEM_TYPE_Pos)        ///< SRAM
#define FSMC_SMSKR_MEM_TYPE2               (0x02U << FSMC_SMSKR_MEM_TYPE_Pos)        ///< FLASH
#define FSMC_SMSKR_MEM_SIZE_Pos            (0)
#define FSMC_SMSKR_MEM_SIZE_64K            (0x01U << FSMC_SMSKR_MEM_SIZE_Pos)         ///< external DEVICE size 64KB
#define FSMC_SMSKR_MEM_SIZE_128K           (0x02U << FSMC_SMSKR_MEM_SIZE_Pos)         ///< external DEVICE size 128KB
#define FSMC_SMSKR_MEM_SIZE_256K           (0x03U << FSMC_SMSKR_MEM_SIZE_Pos)         ///< external DEVICE size 256KB
#define FSMC_SMSKR_MEM_SIZE_512K           (0x04U << FSMC_SMSKR_MEM_SIZE_Pos)         ///< external DEVICE size 512KB
#define FSMC_SMSKR_MEM_SIZE_1M             (0x05U << FSMC_SMSKR_MEM_SIZE_Pos)         ///< external DEVICE size 1MB
#define FSMC_SMSKR_MEM_SIZE_2M             (0x06U << FSMC_SMSKR_MEM_SIZE_Pos)         ///< external DEVICE size 2MB
#define FSMC_SMSKR_MEM_SIZE_4M             (0x07U << FSMC_SMSKR_MEM_SIZE_Pos)         ///< external DEVICE size 4MB
#define FSMC_SMSKR_MEM_SIZE_8M             (0x08U << FSMC_SMSKR_MEM_SIZE_Pos)         ///< external DEVICE size 8MB
#define FSMC_SMSKR_MEM_SIZE_16M            (0x09U << FSMC_SMSKR_MEM_SIZE_Pos)         ///< external DEVICE size 16MB
#define FSMC_SMSKR_MEM_SIZE_32M            (0x10U << FSMC_SMSKR_MEM_SIZE_Pos)        ///< external DEVICE size 32MB
#define FSMC_SMSKR_MEM_SIZE_64M            (0x11U << FSMC_SMSKR_MEM_SIZE_Pos)        ///< external DEVICE size 64MB
#define FSMC_SMSKR_MEM_SIZE_128M           (0x12U << FSMC_SMSKR_MEM_SIZE_Pos)        ///< external DEVICE size 128MB
#define FSMC_SMSKR_MEM_SIZE_256M           (0x13U << FSMC_SMSKR_MEM_SIZE_Pos)        ///< external DEVICE size 256MB
#define FSMC_SMSKR_MEM_SIZE_512M           (0x14U << FSMC_SMSKR_MEM_SIZE_Pos)        ///< external DEVICE size 512MB
#define FSMC_SMSKR_MEM_SIZE_1G             (0x15U << FSMC_SMSKR_MEM_SIZE_Pos)        ///< external DEVICE size 1GB
#define FSMC_SMSKR_MEM_SIZE_2G             (0x16U << FSMC_SMSKR_MEM_SIZE_Pos)        ///< external DEVICE size 2GB
#define FSMC_SMSKR_MEM_SIZE_4G             (0x17U << FSMC_SMSKR_MEM_SIZE_Pos)        ///< external DEVICE size 4GB

////////////////////////////////////////////////////////////////////////////////
/// @brief FSMC_SMTMGR_SET0/1/2 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define FSMC_SMTMGR_SET_SM_READ_PIPE_Pos          (28)
#define FSMC_SMTMGR_SET_SM_READ_PIPE              (0x03U << FSMC_SMTMGR_SET_SM_READ_PIPE_Pos)          ///< The period of the latched read data 
#define FSMC_SMTMGR_SET_LOW_FREG_SYNC_DEVICE_Pos  (27)
#define FSMC_SMTMGR_SET_LOW_FREG_SYNC_DEVICE      (0x01U << FSMC_SMTMGR_SET_LOW_FREG_SYNC_DEVICE_Pos)  ///< Access low frequency synchronization devices
#define FSMC_SMTMGR_SET_READ_MODE_Pos             (26)
#define FSMC_SMTMGR_SET_READ_MODE                 (0x01U << FSMC_SMTMGR_SET_READ_MODE_Pos)             ///< The Hready_RESP signal is from an external DEVICE
#define FSMC_SMTMGR_SET_T_WP_Pos                  (10)
#define FSMC_SMTMGR_SET_T_WP                      (0x3FU << FSMC_SMTMGR_SET_T_WP_Pos)                  ///< Write pulse width 64 clock cycles
#define FSMC_SMTMGR_SET_T_WR_Pos                  (8)
#define FSMC_SMTMGR_SET_T_WR                      (0x03U << FSMC_SMTMGR_SET_T_WR_Pos)                  ///< Address/data retention time for write operations is 3 clock cycles
#define FSMC_SMTMGR_SET_T_AS_Pos                  (6)
#define FSMC_SMTMGR_SET_T_AS                      (0x03U << FSMC_SMTMGR_SET_T_AS_Pos)                  ///< The address establishment time of write operation is 3 clock cycles
#define FSMC_SMTMGR_SET_T_RC_Pos                  (0)
#define FSMC_SMTMGR_SET_T_RC                      (0x3FU << FSMC_SMTMGR_SET_T_RC_Pos)                  ///< Read operation cycle 64 clock cycles

////////////////////////////////////////////////////////////////////////////////
/// @brief FSMC_SMCTLR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define FSMC_SMCTLR_SM_DATA_WIDTH_SET2_Pos          (13)
#define FSMC_SMCTLR_SM_DATA_WIDTH_SET2              (0x07U << FSMC_SMCTLR_SM_DATA_WIDTH_SET2_Pos)
#define FSMC_SMCTLR_SM_DATA_WIDTH_SET2_16           (0x00U << FSMC_SMCTLR_SM_DATA_WIDTH_SET2_Pos)          ///< Memory data bus bit width 16  bits
#define FSMC_SMCTLR_SM_DATA_WIDTH_SET2_32           (0x01U << FSMC_SMCTLR_SM_DATA_WIDTH_SET2_Pos)          ///< Memory data bus bit width 32  bits
#define FSMC_SMCTLR_SM_DATA_WIDTH_SET2_64           (0x02U << FSMC_SMCTLR_SM_DATA_WIDTH_SET2_Pos)          ///< Memory data bus bit width 64  bits
#define FSMC_SMCTLR_SM_DATA_WIDTH_SET2_128          (0x03U << FSMC_SMCTLR_SM_DATA_WIDTH_SET2_Pos)          ///< Memory data bus bit width 128 bits
#define FSMC_SMCTLR_SM_DATA_WIDTH_SET2_8            (0x04U << FSMC_SMCTLR_SM_DATA_WIDTH_SET2_Pos)          ///< Memory data bus bit width 8   bits
#define FSMC_SMCTLR_SM_DATA_WIDTH_SET1_Pos          (10)
#define FSMC_SMCTLR_SM_DATA_WIDTH_SET1              (0x07U << FSMC_SMCTLR_SM_DATA_WIDTH_SET1_Pos)
#define FSMC_SMCTLR_SM_DATA_WIDTH_SET1_16           (0x00U << FSMC_SMCTLR_SM_DATA_WIDTH_SET1_Pos)          ///< Memory data bus bit width 16  bits
#define FSMC_SMCTLR_SM_DATA_WIDTH_SET1_32           (0x01U << FSMC_SMCTLR_SM_DATA_WIDTH_SET1_Pos)          ///< Memory data bus bit width 32  bits
#define FSMC_SMCTLR_SM_DATA_WIDTH_SET1_64           (0x02U << FSMC_SMCTLR_SM_DATA_WIDTH_SET1_Pos)          ///< Memory data bus bit width 64  bits
#define FSMC_SMCTLR_SM_DATA_WIDTH_SET1_128          (0x03U << FSMC_SMCTLR_SM_DATA_WIDTH_SET1_Pos)          ///< Memory data bus bit width 128 bits
#define FSMC_SMCTLR_SM_DATA_WIDTH_SET1_8            (0x04U << FSMC_SMCTLR_SM_DATA_WIDTH_SET1_Pos)          ///< Memory data bus bit width 8   bits
#define FSMC_SMCTLR_SM_DATA_WIDTH_SET0_Pos          (7)
#define FSMC_SMCTLR_SM_DATA_WIDTH_SET0              (0x07U << FSMC_SMCTLR_SM_DATA_WIDTH_SET0_Pos)
#define FSMC_SMCTLR_SM_DATA_WIDTH_SET0_16           (0x00U << FSMC_SMCTLR_SM_DATA_WIDTH_SET0_Pos)          ///< Memory data bus bit width 16  bits
#define FSMC_SMCTLR_SM_DATA_WIDTH_SET0_32           (0x01U << FSMC_SMCTLR_SM_DATA_WIDTH_SET0_Pos)          ///< Memory data bus bit width 32  bits
#define FSMC_SMCTLR_SM_DATA_WIDTH_SET0_64           (0x02U << FSMC_SMCTLR_SM_DATA_WIDTH_SET0_Pos)          ///< Memory data bus bit width 64  bits
#define FSMC_SMCTLR_SM_DATA_WIDTH_SET0_128          (0x03U << FSMC_SMCTLR_SM_DATA_WIDTH_SET0_Pos)          ///< Memory data bus bit width 128 bits
#define FSMC_SMCTLR_SM_DATA_WIDTH_SET0_8            (0x04U << FSMC_SMCTLR_SM_DATA_WIDTH_SET0_Pos)          ///< Memory data bus bit width 8   bits






/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif //__REG_FSMC_H
////////////////////////////////////////////////////////////////////////////////
