/* -----------------------------------------------------------------------------
 * Copyright (c) 2013-2014 ARM Ltd.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software. Permission is granted to anyone to use this
 * software for any purpose, including commercial applications, and to alter
 * it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 *
 * $Date:        31. Mar 2014
 * $Revision:    V2.00
 *
 * Project:      Flash Driver definitions
 * -------------------------------------------------------------------------- */

/* History:
 *  Version 2.00
 *    Renamed driver NOR -> Flash (more generic)
 *    Non-blocking operation
 *    Added Events, Status and Capabilities
 *    Linked Flash information (GetInfo)
 *  Version 1.11
 *    Changed prefix ARM_DRV -> ARM_DRIVER
 *  Version 1.10
 *    Namespace prefix ARM_ added
 *  Version 1.00
 *    Initial release
 */

#ifndef __DRIVER_FLASH_H
#define __DRIVER_FLASH_H

#include "Driver_Common.h"

#define ARM_FLASH_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(2,00)  /* API version */


#define _ARM_Driver_Flash_(n)      Driver_Flash##n
#define  ARM_Driver_Flash_(n) _ARM_Driver_Flash_(n)


#define ARM_FLASH_SECTOR_INFO(addr,size) { (addr), (addr)+(size)-1 }

/**
\brief Flash Sector information
*/
typedef struct _ARM_FLASH_SECTOR {
  uint32_t start;                       ///< Sector Start address
  uint32_t end;                         ///< Sector End address (start+size-1)
} const ARM_FLASH_SECTOR;

/**
\brief Flash information
*/
typedef struct _ARM_FLASH_INFO {
  ARM_FLASH_SECTOR *sector_info;        ///< Sector layout information (NULL=Uniform sectors)
  uint32_t          sector_count;       ///< Number of sectors
  uint32_t          sector_size;        ///< Uniform sector size in bytes (0=sector_info used) 
  uint32_t          page_size;          ///< Optimal programming page size in bytes
  uint32_t          program_unit;       ///< Smallest programmable unit in bytes
  uint8_t           erased_value;       ///< Contents of erased memory (usually 0xFF)
} const ARM_FLASH_INFO;


/**
\brief Flash Status
*/
typedef struct _ARM_FLASH_STATUS {
  uint32_t busy  : 1;                   ///< Flash busy flag
  uint32_t error : 1;                   ///< Read/Program/Erase error flag (cleared on start of next operation)
} ARM_FLASH_STATUS;


/****** Flash Event *****/
#define ARM_FLASH_EVENT_READY           (1UL << 0)  ///< Flash Ready
#define ARM_FLASH_EVENT_ERROR           (1UL << 1)  ///< Read/Program/Erase Error


// Function documentation
/**
  \fn          ARM_DRIVER_VERSION ARM_Flash_GetVersion (void)
  \brief       Get driver version.
  \return      \ref ARM_DRIVER_VERSION
*/
/**
  \fn          ARM_FLASH_CAPABILITIES ARM_Flash_GetCapabilities (void)
  \brief       Get driver capabilities.
  \return      \ref ARM_FLASH_CAPABILITIES
*/
/**
  \fn          int32_t ARM_Flash_Initialize (ARM_Flash_SignalEvent_t cb_event)
  \brief       Initialize the Flash Interface.
  \param[in]   cb_event  Pointer to \ref ARM_Flash_SignalEvent
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_Flash_Uninitialize (void)
  \brief       De-initialize the Flash Interface.
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_Flash_PowerControl (ARM_POWER_STATE state)
  \brief       Control the Flash interface power.
  \param[in]   state  Power state
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_Flash_ReadData (uint32_t addr, void *data, uint32_t cnt)
  \brief       Read data from Flash.
  \param[in]   addr  Data address.
  \param[out]  data  Pointer to a buffer storing the data read from Flash.
  \param[in]   cnt   Number of data items to read.
  \return      number of data items read or \ref execution_status
*/
/**
  \fn          int32_t ARM_Flash_ProgramData (uint32_t addr, const void *data, uint32_t cnt)
  \brief       Program data to Flash.
  \param[in]   addr  Data address.
  \param[in]   data  Pointer to a buffer containing the data to be programmed to Flash.
  \param[in]   cnt   Number of data items to program.
  \return      number of data items programmed or \ref execution_status
*/
/**
  \fn          int32_t ARM_Flash_EraseSector (uint32_t addr)
  \brief       Erase Flash Sector.
  \param[in]   addr  Sector address
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_Flash_EraseChip (void)
  \brief       Erase complete Flash.
               Optional function for faster full chip erase.
  \return      \ref execution_status
*/
/**
  \fn          ARM_FLASH_STATUS ARM_Flash_GetStatus (void)
  \brief       Get Flash status.
  \return      Flash status \ref ARM_FLASH_STATUS
*/
/**
  \fn          ARM_FLASH_INFO * ARM_Flash_GetInfo (void)
  \brief       Get Flash information.
  \return      Pointer to Flash information \ref ARM_FLASH_INFO
*/

/**
  \fn          void ARM_Flash_SignalEvent (uint32_t event)
  \brief       Signal Flash event.
  \param[in]   event  Event notification mask
  \return      none
*/

typedef void (*ARM_Flash_SignalEvent_t) (uint32_t event);    ///< Pointer to \ref ARM_Flash_SignalEvent : Signal Flash Event.


/**
\brief Flash Driver Capabilities.
*/
typedef struct _ARM_FLASH_CAPABILITIES {
  uint32_t event_ready  : 1;            ///< Signal Flash Ready event
  uint32_t data_width   : 2;            ///< Data width: 0=8-bit, 1=16-bit, 2=32-bit
  uint32_t erase_chip   : 1;            ///< Supports EraseChip operation
} ARM_FLASH_CAPABILITIES;


/**
\brief Access structure of the Flash Driver
*/
typedef struct _ARM_DRIVER_FLASH {
  ARM_DRIVER_VERSION     (*GetVersion)     (void);                                          ///< Pointer to \ref ARM_Flash_GetVersion : Get driver version.
  ARM_FLASH_CAPABILITIES (*GetCapabilities)(void);                                          ///< Pointer to \ref ARM_Flash_GetCapabilities : Get driver capabilities.
  int32_t                (*Initialize)     (ARM_Flash_SignalEvent_t cb_event);              ///< Pointer to \ref ARM_Flash_Initialize : Initialize Flash Interface.
  int32_t                (*Uninitialize)   (void);                                          ///< Pointer to \ref ARM_Flash_Uninitialize : De-initialize Flash Interface.
  int32_t                (*PowerControl)   (ARM_POWER_STATE state);                         ///< Pointer to \ref ARM_Flash_PowerControl : Control Flash Interface Power.
  int32_t                (*ReadData)       (uint32_t addr,       void *data, uint32_t cnt); ///< Pointer to \ref ARM_Flash_ReadData : Read data from Flash.
  int32_t                (*ProgramData)    (uint32_t addr, const void *data, uint32_t cnt); ///< Pointer to \ref ARM_Flash_ProgramData : Program data to Flash.
  int32_t                (*EraseSector)    (uint32_t addr);                                 ///< Pointer to \ref ARM_Flash_EraseSector : Erase Flash Sector.
  int32_t                (*EraseChip)      (void);                                          ///< Pointer to \ref ARM_Flash_EraseChip : Erase complete Flash.
  ARM_FLASH_STATUS       (*GetStatus)      (void);                                          ///< Pointer to \ref ARM_Flash_GetStatus : Get Flash status.
  ARM_FLASH_INFO *       (*GetInfo)        (void);                                          ///< Pointer to \ref ARM_Flash_GetInfo : Get Flash information.
} const ARM_DRIVER_FLASH;

#endif /* __DRIVER_FLASH_H */
