////////////////////////////////////////////////////////////////////////////////
/// @file     reg_flash.h
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

#ifndef __REG_FLASH_H
#define __REG_FLASH_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif


////////////////////////////////////////////////////////////////////////////////
/// @brief  MM32 MCU Memory/Peripherals mapping
////////////////////////////////////////////////////////////////////////////////
#define FLASH_BASE                      (0x08000000U)                           ///< FLASH base address in the alias region
#define SRAM_BASE                       (0x20000000U)                           ///< SRAM base address in the alias region

#define CACHE_BASE                      (APB2PERIPH_BASE + 0x6000)              ///< Base Address: 0x40016000       

////////////////////////////////////////////////////////////////////////////////
/// @brief FLASH Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define FLASH_REG_BASE                  (AHBPERIPH_BASE + 0x2000)               ///< Base Address: 0x40022000
////////////////////////////////////////////////////////////////////////////////
/// @brief OPTB Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define OB_BASE                         (0x1FFFF800U)                           ///< Flash Option Bytes base address
#define PROTECT_BASE                    (0x1FFE0000U)                           ///< Flash Protect Bytes base address



////////////////////////////////////////////////////////////////////////////////
/// @brief FLASH Registers Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 ACR;                                                               ///< Access control Register                        offset: 0x00
    __IO u32 KEYR;                                                              ///< Key Register                                   offset: 0x04
    __IO u32 OPTKEYR;                                                           ///< Option byte key Register                       offset: 0x08
    __IO u32 SR;                                                                ///< State Register                                 offset: 0x0C
    __IO u32 CR;                                                                ///< Control Register                               offset: 0x10
    __IO u32 AR;                                                                ///< Address Register                               offset: 0x14
    __IO u32 RESERVED;
    __IO u32 OBR;                                                               ///< Option bytes Register                          offset: 0x1C
    __IO u32 WRPR;                                                              ///< Write protect Register                         offset: 0x20
} FLASH_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  OPT Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u16 RDP;                                                               ///< Read Protect,                                  offset: 0x00
    __IO u16 USER;                                                              ///< User option byte,                              offset: 0x02
    __IO u16 Data0;                                                             ///< User data 0,                                   offset: 0x04
    __IO u16 Data1;                                                             ///< User data 1,                                   offset: 0x06
    __IO u16 WRP0;                                                              ///< Flash write protection option byte 0,          offset: 0x08
    __IO u16 WRP1;                                                              ///< Flash write protection option byte 1,          offset: 0x0A
    __IO u16 WRP2;                                                              ///< Flash write protection option byte 2,          offset: 0x0C
    __IO u16 WRP3;                                                              ///< Flash write protection option byte 3,          offset: 0x0E
} OB_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  PROTECT BYTES Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u16 PROTECT_LEN0;                                                      ///< The length of Protect byte 0,                  offset: 0x00
    __IO u16 PROTECT_ADDR0;                                                     ///< Data of Protect byte 0,                        offset: 0x02
    __IO u16 PROTECT_LEN1;                                                      ///< The length of Protect byte 1,                  offset: 0x04
    __IO u16 PROTECT_ADDR1;                                                     ///< Data of Protect byte 1,                        offset: 0x06
    __IO u16 PROTECT_LEN2;                                                      ///< The length of Protect byte 2,                  offset: 0x08
    __IO u16 PROTECT_ADDR2;                                                     ///< Data of Protect byte 2,                        offset: 0x0A
    __IO u16 PROTECT_LEN3;                                                      ///< The length of Protect byte 3,                  offset: 0x0C
    __IO u16 PROTECT_ADDR3;                                                     ///< Data of Protect byte 3,                        offset: 0x0E
} PROTECT_TypeDef;
////////////////////////////////////////////////////////////////////////////////
/// @brief  CACHE BYTES Structure Definition
////////////////////////////////////////////////////////////////////////////////

typedef struct {
    __IO u32 CCR;                                                               ///< Configuration and control register              offset: 0x00
    __IO u32 SR;                                                                ///< Status register                                 offset: 0x04
    __IO u32 IMR;                                                               ///< Interrupt mask register                         offset: 0x08
    __IO u32 ISR;                                                               ///< Interrupt status register                       offset: 0x0C
    __IO u32 RESERVED0;                                                         ///<                                                 offset: 0x10
    __IO u32 CSHR;                                                              ///< Hit Statistics Register                         offset: 0x14
    __IO u32 CSMR;                                                              ///< Lost Statistics Register                        offset: 0x18
} CACHE_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief FLASH type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define FLASH                           ((FLASH_TypeDef*) FLASH_REG_BASE)
////////////////////////////////////////////////////////////////////////////////
/// @brief OPTB type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define OB                              ((OB_TypeDef*) OB_BASE)
#define PROTECT                         ((PROTECT_TypeDef*) PROTECT_BASE)
////////////////////////////////////////////////////////////////////////////////
/// @brief CACHE pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define CACHE                           ((CACHE_TypeDef*) CACHE_BASE)
////////////////////////////////////////////////////////////////////////////////
/// @brief FLASH_ACR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define FLASH_ACR_LATENCY_Pos           (0)
#define FLASH_ACR_LATENCY               (0x07U << FLASH_ACR_LATENCY_Pos)        ///< LATENCY[2:0] bits (Latency)
#define FLASH_ACR_LATENCY_0             (0x00U << FLASH_ACR_LATENCY_Pos)        ///< 0 waiting state
#define FLASH_ACR_LATENCY_1             (0x01U << FLASH_ACR_LATENCY_Pos)        ///< 1 waiting state   
#define FLASH_ACR_LATENCY_2             (0x02U << FLASH_ACR_LATENCY_Pos)        ///< 2 waiting state
#define FLASH_ACR_LATENCY_3             (0x03U << FLASH_ACR_LATENCY_Pos)        ///< 3 waiting state
#define FLASH_ACR_HLFCYA_Pos            (3)
#define FLASH_ACR_HLFCYA                (0x01U << FLASH_ACR_HLFCYA_Pos)         ///< Flash Half Cycle Access Enable
#define FLASH_ACR_PRFTBE_Pos            (4)
#define FLASH_ACR_PRFTBE                (0x01U << FLASH_ACR_PRFTBE_Pos)         ///< Prefetch Buffer Enable
#define FLASH_ACR_PRFTBS_Pos            (5)
#define FLASH_ACR_PRFTBS                (0x01U << FLASH_ACR_PRFTBS_Pos)         ///< Prefetch Buffer Status
////////////////////////////////////////////////////////////////////////////////
/// @brief FLASH_KEYR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define FLASH_KEYR_FKEY_Pos             (0)
#define FLASH_KEYR_FKEY                 (0xFFFFFFFFU << FLASH_KEYR_FKEY_Pos)    ///< FLASH Key

////////////////////////////////////////////////////////////////////////////////
/// @brief FLASH_OPTKEYR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define FLASH_OPTKEYR_OPTKEY_Pos        (0)
#define FLASH_OPTKEYR_OPTKEY            (0xFFFFFFFFU << FLASH_OPTKEYR_OPTKEY_Pos)   ///< Option Byte Key

////////////////////////////////////////////////////////////////////////////////
/// @brief FLASH_SR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define FLASH_SR_BUSY_Pos               (0)
#define FLASH_SR_BUSY                   (0x01U << FLASH_SR_BUSY_Pos)            ///< Busy
#define FLASH_SR_PGERR_Pos              (2)
#define FLASH_SR_PGERR                  (0x01U << FLASH_SR_PGERR_Pos)           ///< Programming Error
#define FLASH_SR_WRPRTERR_Pos           (4)
#define FLASH_SR_WRPRTERR               (0x01U << FLASH_SR_WRPRTERR_Pos)        ///< Write Protection Error
#define FLASH_SR_EOP_Pos                (5)
#define FLASH_SR_EOP                    (0x01U << FLASH_SR_EOP_Pos)             ///< End of operation

////////////////////////////////////////////////////////////////////////////////
/// @brief FLASH_CR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define FLASH_CR_PG_Pos                 (0)
#define FLASH_CR_PG                     (0x01U << FLASH_CR_PG_Pos)              ///< Programming
#define FLASH_CR_PER_Pos                (1)
#define FLASH_CR_PER                    (0x01U << FLASH_CR_PER_Pos)             ///< Page Erase
#define FLASH_CR_MER_Pos                (2)
#define FLASH_CR_MER                    (0x01U << FLASH_CR_MER_Pos)             ///< Mass Erase
#define FLASH_CR_OPTPG_Pos              (4)
#define FLASH_CR_OPTPG                  (0x01U << FLASH_CR_OPTPG_Pos)           ///< Option Byte Programming
#define FLASH_CR_OPTER_Pos              (5)
#define FLASH_CR_OPTER                  (0x01U << FLASH_CR_OPTER_Pos)           ///< Option Byte Erase
#define FLASH_CR_STRT_Pos               (6)
#define FLASH_CR_STRT                   (0x01U << FLASH_CR_STRT_Pos)            ///< Start
#define FLASH_CR_LOCK_Pos               (7)
#define FLASH_CR_LOCK                   (0x01U << FLASH_CR_LOCK_Pos)            ///< Lock
#define FLASH_CR_OPTWRE_Pos             (9)
#define FLASH_CR_OPTWRE                 (0x01U << FLASH_CR_OPTWRE_Pos)          ///< Option Bytes Write Enable
#define FLASH_CR_ERRIE_Pos              (10)
#define FLASH_CR_ERRIE                  (0x01U << FLASH_CR_ERRIE_Pos)           ///< Error Interrupt Enable
#define FLASH_CR_EOPIE_Pos              (12)
#define FLASH_CR_EOPIE                  (0x01U << FLASH_CR_EOPIE_Pos)           ///< End of operation interrupt enable

////////////////////////////////////////////////////////////////////////////////
/// @brief FLASH_AR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define FLASH_AR_FAR_Pos                (0)
#define FLASH_AR_FAR                    (0xFFFFFFFFU << FLASH_AR_FAR_Pos)       ///< Flash Address

////////////////////////////////////////////////////////////////////////////////
/// @brief FLASH_OBR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define FLASH_OBR_OPTERR_Pos            (0)
#define FLASH_OBR_OPTERR                (0x01U << FLASH_OBR_OPTERR_Pos)         ///< Option Byte Error
#define FLASH_OBR_RDPRT_Pos             (1)
#define FLASH_OBR_RDPRT                 (0x01U << FLASH_OBR_RDPRT_Pos)         ///< Read protection level status
#define FLASH_OBR_USER_Pos              (2)
#define FLASH_OBR_USER                  (0xFFU << FLASH_OBR_USER_Pos)           ///< User Option Bytes

#define FLASH_OBR_WDG_SW                (0x01U << FLASH_OBR_USER_Pos)           ///< WDG_SW
#define FLASH_OBR_RST_STOP              (0x02U << FLASH_OBR_USER_Pos)           ///< nRST_STOP
#define FLASH_OBR_RST_STDBY             (0x04U << FLASH_OBR_USER_Pos)           ///< nRST_STDBY


#define FLASH_OBR_Data0_Pos             (10)
#define FLASH_OBR_Data0                 (0xFFU << FLASH_OBR_Data0_Pos)          ///< User data storage option byte
#define FLASH_OBR_Data1_Pos             (18)
#define FLASH_OBR_Data1                 (0xFFU << FLASH_OBR_Data1_Pos)          ///< User data storage option byte

////////////////////////////////////////////////////////////////////////////////
/// @brief FLASH_WRPR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define FLASH_WRPR_WRP_Pos              (0)
#define FLASH_WRPR_WRP                  (0xFFFFFFFFU << FLASH_WRPR_WRP_Pos)     ///< Write Protect



////////////////////////////////////////////////////////////////////////////////
/// @brief CACHE_CCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CACHE_CCR_EN_Pos               (0)
#define CACHE_CCR_EN                   (0x01U << CACHE_CCR_EN_Pos)              ///< Cache Enable
#define CACHE_CCR_INV_Pos              (1)
#define CACHE_CCR_INV                  (0x01U << CACHE_CCR_INV_REQ_Pos)         ///< Manually invalidate the request
#define CACHE_CCR_POW_Pos              (2)
#define CACHE_CCR_POW                  (0x01U << CACHE_CCR_POW_REQ_Pos)         ///< Manual SRAM power request
#define CACHE_CCR_MAN_POW_Pos          (3)
#define CACHE_CCR_MAN_POW              (0x01U << CACHE_CCR_MAN_POW_Pos)         ///< Set manual or automatic SRAM power request
#define CACHE_CCR_MAN_INV_Pos          (4)
#define CACHE_CCR_MAN_INV              (0x01U << CACHE_CCR_MAN_INV_Pos)         ///< Manually or automatically disable it
#define CACHE_CCR_PREFETCH_Pos         (5)
#define CACHE_CCR_PREFETCH             (0x01U << CACHE_CCR_PREFETCH_Pos)        ///< Prefetch function
#define CACHE_CCR_STATISTIC_Pos        (6)
#define CACHE_CCR_STATISTIC            (0x01U << CACHE_CCR_STATISTIC_Pos)       ///< Statistics enable
////////////////////////////////////////////////////////////////////////////////
/// @brief CACHE_SR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CACHE_SR_CS_Pos               (0)
#define CACHE_SR_CS0                  (0x00U << CACHE_CCR_CS_Pos)              ///< Cache is disabled
#define CACHE_SR_CS1                  (0x01U << CACHE_CCR_CS_Pos)              ///< Cache is being enabled
#define CACHE_SR_CS2                  (0x02U << CACHE_CCR_CS_Pos)              ///< Cache is enabled
#define CACHE_SR_CS3                  (0x03U << CACHE_CCR_CS_Pos)              ///< Cache is being disabled
#define CACHE_SR_INV_Pos              (2)
#define CACHE_SR_INV                  (0x01U << CACHE_CCR_INV_REQ_Pos)         ///< Invalidation status
#define CACHE_SR_POW_Pos              (4)
#define CACHE_SR_POW                  (0x01U << CACHE_CCR_POW_REQ_Pos)         ///< SRAM power response
////////////////////////////////////////////////////////////////////////////////
/// @brief CACHE_IMR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CACHE_IMR_MAN_INV_Pos          (0)
#define CACHE_IMR_MAN_INV              (0x01U << CACHE_IMR_MAN_INV_Pos)        ///< Mask the interrupt request of manual invalidation error
#define CACHE_IMR_POW_Pos              (1)
#define CACHE_IMR_POW                  (0x01U << CACHE_IMR_POW_Pos)            ///< Mask the interrupt request of power supply error 
////////////////////////////////////////////////////////////////////////////////
/// @brief CACHE_ISR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CACHE_ISR_MAN_INV_Pos          (0)
#define CACHE_ISR_MAN_INV              (0x01U << CACHE_ISR_MAN_INV_Pos)        ///< Manual invalidation of error flags
#define CACHE_ISR_POW_Pos              (1)
#define CACHE_ISR_POW                  (0x01U << CACHE_ISR_POW_Pos)            ///< SRAM power error flags 
////////////////////////////////////////////////////////////////////////////////
/// @brief CACHE_CSHR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CACHE_CSHR                     (0xFFFFU )                              ///< Cache  Hits
////////////////////////////////////////////////////////////////////////////////
/// @brief CACHE_CSHR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CACHE_CSMR                     (0xFFFFU )                              ///< Cache  Lost times







/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
