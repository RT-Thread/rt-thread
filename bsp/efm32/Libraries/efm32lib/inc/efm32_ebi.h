/***************************************************************************//**
 * @file
 * @brief External Bus Iterface (EBI) peripheral API for EFM32
 * @author Energy Micro AS
 * @version 1.3.0
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2010 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * This source code is the property of Energy Micro AS. The source and compiled
 * code may only be used on Energy Micro "EFM32" microcontrollers.
 *
 * This copyright notice may not be removed from the source code nor changed.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/
#ifndef __EFM32_EBI_H
#define __EFM32_EBI_H

#include "efm32.h"

#if defined(EBI_COUNT) && (EBI_COUNT > 0)
#include "efm32_bitband.h"

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup EFM32_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup EBI
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @verbatim
 *
 * ---------               ---------
 * |  EBI  |  /|       |\  | Ext.  |
 * |       | / --------- \ | Async |
 * |(EFM32)| \ --------- / | Device|
 * |       |  \|       |/  |       |
 * ---------               ---------
 *         Parallel interface
 *
 * @endverbatim
 ******************************************************************************/

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#define EBI_BANK0    (1 << 1) /**< EBI address bank 0 */
#define EBI_BANK1    (1 << 2) /**< EBI address bank 1 */
#define EBI_BANK2    (1 << 3) /**< EBI address bank 2 */
#define EBI_BANK3    (1 << 4) /**< EBI address bank 3 */

#define EBI_CS0      (1 << 1) /**< EBI chip select line 0 */
#define EBI_CS1      (1 << 2) /**< EBI chip select line 1 */
#define EBI_CS2      (1 << 3) /**< EBI chip select line 2 */
#define EBI_CS3      (1 << 4) /**< EBI chip select line 3 */

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** EBI Mode of operation */
typedef enum
{
  /** 8 data bits, 8 address bits */
  ebiModeD8A8      = EBI_CTRL_MODE_D8A8,
  /** 16 data bits, 16 address bits, using address latch enable */
  ebiModeD16A16ALE = EBI_CTRL_MODE_D16A16ALE,
  /** 8 data bits, 24 address bits, using address latch enable */
  ebiModeD8A24ALE  = EBI_CTRL_MODE_D8A24ALE
} EBI_Mode_TypeDef;

/** EBI Polarity configuration */
typedef enum
{
  /** Active Low */
  ebiActiveLow  = 0,
  /** Active High */
  ebiActiveHigh = 1
} EBI_Polarity_TypeDef;

/** EBI Pin Line types */
typedef enum
{
  /** Address Ready polarity */
  ebiLineARDY,
  /** Address Latch Enable polarity */
  ebiLineALE,
  /** Write Enable polarity */
  ebiLineWE,
  /** Read Enable polarity */
  ebiLineRE,
  /** Chip Select polarity */
  ebiLineCS
} EBI_Line_TypeDef;

/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

/** EBI Initialization structure */
typedef struct
{
  /** EBI operation mode, data and address limits */
  EBI_Mode_TypeDef     mode;
  /** Address Ready pin polarity, active high or low */
  EBI_Polarity_TypeDef ardyPolarity;
  /** Address Latch Enable pin polarity, active high or low */
  EBI_Polarity_TypeDef alePolarity;
  /** Write Enable pin polarity, active high or low */
  EBI_Polarity_TypeDef wePolarity;
  /** Read Enable pin polarity, active high or low */
  EBI_Polarity_TypeDef rePolarity;
  /** Chip Select pin polarity, active high or low */
  EBI_Polarity_TypeDef csPolarity;
  /** Flag to enable or disable Address Ready support */
  bool                 ardyEnable;
  /** Set to turn off 32 cycle timeout ability */
  bool                 ardyDisableTimeout;
  /** Mask of flags which selects address banks to configure EBI_BANK<0-3> */
  uint32_t             banks;
  /** Mask of flags which selects chip select lines t configure EBI_CS<0-3> */
  uint32_t             csLines;
  /** Number of cycles address is held after Adress Latch Enable is asserted */
  int                  addrSetupCycles;
  /** Number of cycles address is driven onto the ADDRDAT bus before ALE is asserted */
  int                  addrHoldCycles;
  /** Number of cycles for address setup before REn is asserted */
  int                  readSetupCycles;
  /** Number of cycles REn is held active */
  int                  readStrobeCycles;
  /** Number of cycles CSn is held active after REn is deasserted */
  int                  readHoldCycles;
  /** Number of cycles for address setup before WEn is asserted */
  int                  writeSetupCycles;
  /** Number of cycles WEn is held active */
  int                  writeStrobeCycles;
  /** Number of cycles CSn is held active after WEn is deasserted */
  int                  writeHoldCycles;
  /** Flag, if EBI should be enabled after configuration */
  bool                 enable;
} EBI_Init_TypeDef;

/** Default config for EBI init structures */
#define EBI_INIT_DEFAULT                                 \
  {   ebiModeD8A8,      /* 8 bit address, 8 bit data */  \
      ebiActiveLow,     /* ARDY polarity */              \
      ebiActiveLow,     /* ALE polarity */               \
      ebiActiveLow,     /* WE polarity */                \
      ebiActiveLow,     /* RE polarity */                \
      ebiActiveLow,     /* CS polarity */                \
      false,            /* enable ARDY */                \
      false,            /* don't disable ARDY timeout */ \
      EBI_BANK0,        /* enable bank 0 */              \
      EBI_CS0,          /* enable chip select 0 */       \
      0,                /* addr setup cycles */          \
      1,                /* addr hold cycles */           \
      0,                /* read setup cycles */          \
      0,                /* read strobe cycles */         \
      0,                /* read hold cycles */           \
      0,                /* write setup cycles */         \
      0,                /* write strobe cycles */        \
      1,                /* write hold cycles */          \
      true,             /* enable EBI */                 \
  }

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

void EBI_Init(const EBI_Init_TypeDef *ebiInit);
void EBI_Disable(void);
uint32_t EBI_BankAddress(uint32_t bank);
void EBI_BankEnable(uint32_t banks, bool enable);
void EBI_ChipSelectEnable(uint32_t banks, bool enable);
void EBI_ReadTimingSet(int setupCycles, int strobeCycles, int holdCycles);
void EBI_WriteTimingSet(int setupCycles, int strobeCycles, int holdCycles);
void EBI_AddressTimingSet(int setupCycles, int holdCycles);
void EBI_PolaritySet(EBI_Line_TypeDef line, EBI_Polarity_TypeDef polarity);

/** @} (end addtogroup EBI) */
/** @} (end addtogroup EFM32_Library) */

#ifdef __cplusplus
}
#endif

#endif /* defined(EBI_COUNT) && (EBI_COUNT > 0) */

#endif /* __EFM32_EBI_H */
