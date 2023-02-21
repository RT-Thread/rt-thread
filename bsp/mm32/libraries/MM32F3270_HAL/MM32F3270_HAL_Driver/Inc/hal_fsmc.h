/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_FSMC_H__
#define __HAL_FSMC_H__

#include "hal_common.h"

/*
* There are still some configurations in SYSCFG_CFGR1:
* - switch between 8080 mode and NOR FLASH mode.
* - disable the reuse of data pins as address pins.
* - enable the fsmc sync.
*/

/*!
 * @addtogroup FSMC
 * @{
 */

/*!
 * @brief FSMC driver version number.
 */
#define FSMC_DRIVER_VERSION 0u /*!< fsmc_0. */

/*!
 * @brief FSMC memory type.
 */
typedef enum
{
    FSMC_MemType_SRAM     = 1u, /*!< Mem type: SRAM. */
    FSMC_MemType_NorFlash = 2u, /*!< Mem type: NorFlash. */
    FSMC_MemType_PSRAM    = 3u, /*!< Mem type: PSRAM. */
} FSMC_MemType_Type;

/*!
 * @brief FSMC memory size type.
 */
typedef enum
{
    FSMC_MemSize_NoDevice = 0u,  /*!< Mem Size type: NoDevice. */
    FSMC_MemSize_64KB     = 1u,  /*!< Mem Size type: 64KB. */
    FSMC_MemSize_128KB    = 2u,  /*!< Mem Size type: 128KB. */
    FSMC_MemSize_256KB    = 3u,  /*!< Mem Size type: 256KB. */
    FSMC_MemSize_512KB    = 4u,  /*!< Mem Size type: 512KB. */
    FSMC_MemSize_1MB      = 5u,  /*!< Mem Size type: 1MB. */
    FSMC_MemSize_2MB      = 6u,  /*!< Mem Size type: 2MB. */
    FSMC_MemSize_4MB      = 7u,  /*!< Mem Size type: 4MB. */
    FSMC_MemSize_8MB      = 8u,  /*!< Mem Size type: 8MB. */
    FSMC_MemSize_16MB     = 9u,  /*!< Mem Size type: 16MB. */
    FSMC_MemSize_32MB     = 10u, /*!< Mem Size type: 32MB. */
    FSMC_MemSize_64MB     = 11u, /*!< Mem Size type: 64MB. */
    FSMC_MemSize_128MB    = 12u, /*!< Mem Size type: 128MB. */
    FSMC_MemSize_256MB    = 13u, /*!< Mem Size type: 256MB. */
    FSMC_MemSize_512MB    = 14u, /*!< Mem Size type: 512MB. */
    FSMC_MemSize_1GB      = 15u, /*!< Mem Size type: 1GB. */
    FSMC_MemSize_2GB      = 16u, /*!< Mem Size type: 2GB. */
    FSMC_MemSize_4GB      = 17u, /*!< Mem Size type: 4GB. */
} FSMC_MemSize_Type;

/*!
 * @brief FSMC ready signal type.
 */
typedef enum
{
    FSMC_ReadySignal_Internal = 0u, /*!< The ready signal is inside the FSMC, do not need the external ready signal. */
    FSMC_ReadySignal_External = 1u, /*!< The ready signal is from external device. */
} FSMC_ReadySignal_Type;

/*!
 * @brief FSMC bus width type.
 */
typedef enum
{
    FSMC_BusWidth_8b  = 4u, /*!< Bus width: 8bit.  */
    FSMC_BusWidth_16b = 0u, /*!< Bus width: 16bit. */
    FSMC_BusWidth_32b = 1u, /*!< Bus width: 32bit. */
} FSMC_BusWidth_Type;

/*!
 * @brief This type of structure instance is used to keep the settings when calling the @ref FSMC_Init() to initialize the FSMC module.
 */
typedef struct
{
    FSMC_MemType_Type MemType;  /*!< Specify the memory type. */
    FSMC_MemSize_Type MemSize;  /*!< Specify the memory size. */
} FSMC_Init_Type;

/*!
 * @brief This type of structure instance is used to keep the settings when calling the @ref FSMC_SetConf() to initialize the FSMC config.
 */
typedef struct
{
    uint32_t                ReadPeriod;     /*!< the cycles for 'reading data', NOE available period.  */
    uint32_t                AddrSetTime;    /*!< the cycles for 'setup' when writing. */
    uint32_t                WriteHoldTime;  /*!< the cycles between the master write action and slave capture done. */
    uint32_t                WritePeriod;    /*!< the cycles for 'keep data' in writing operation, NWE available period.  */
    FSMC_ReadySignal_Type   ReadySignal;    /*!< select if capture the external ready signal. */
    uint32_t                SMReadPipe;     /*!< the cycles between the read action and release the bus.*/
    FSMC_BusWidth_Type      BusWidth;       /*!< Specify the bus width. */
} FSMC_Conf_Type;

/*!
 * @brief Initialize the FSMC module.
 *
 * @param FSMCx FSMC instance.
 * @param init Pointer to the initialization structure. See to @ref FSMC_Init_Type.
 * @return None.
 */
void FSMC_Init(FSMC_Type * FSMCx, FSMC_Init_Type * init);

/*!
 * @brief Set the FSMC config.
 *
 * @param FSMCx FSMC instance.
 * @param index Config index.
 * @param conf Pointer to the config structure. See to @ref FSMC_Conf_Type.
 * @return None.
 */
void FSMC_SetConf(FSMC_Type * FSMCx, uint32_t index, FSMC_Conf_Type * conf);

/*!
 * @brief Enable the FSMC config.
 *
 * Only last enabled config is available.
 *
 * @param FSMCx FSMC instance.
 * @param index Config index.
 * @return None.
 */
void FSMC_EnableConf(FSMC_Type * FSMCx, uint32_t index);

/*!
 * @brief Get the Xfer data reg addr.
 *
 * @param FSMCx FSMC instance.
 * @param bankn FSMC bank number.
 * @param offset offset of data in FSMC bank.
 * @return The addr value of Xfer data reg.
 */
uint32_t FSMC_GetXferDataRegAddr(FSMC_Type *FSMCx, uint32_t bankn, uint32_t offset);

/*!
 * @brief Put the 32bit data by FSMC module.
 *
 * @param FSMCx FSMC instance.
 * @param bankn FSMC bank number.
 * @param offset offset of data in FSMC bank.
 * @param data Data value to be send through the transmiter.
 * @return None.
 */
void FSMC_PutData32(FSMC_Type * FSMCx, uint32_t bankn, uint32_t offset, uint32_t data);

/*!
 * @brief Get the 32bit data by FSMC module.
 *
 * @param FSMCx FSMC instance.
 * @param bankn FSMC bank number.
 * @param offset offset of data in FSMC bank.
 * @return The data value received from FSMC.
 */
uint32_t FSMC_GetData32(FSMC_Type * FSMCx, uint32_t bankn, uint32_t offset);

/*!
 * @brief Put the 16bit data by FSMC module.
 *
 * @param FSMCx FSMC instance.
 * @param bankn FSMC bank number.
 * @param offset offset of data in FSMC bank.
 * @param data Data value to be send through the transmiter.
 * @return None.
 */
void FSMC_PutData16(FSMC_Type * FSMCx, uint32_t bankn, uint32_t offset, uint16_t data);

/*!
 * @brief Get the 16bit data by FSMC module.
 *
 * @param FSMCx FSMC instance.
 * @param bankn FSMC bank number.
 * @param offset offset of data in FSMC bank.
 * @return The data value received from FSMC.
 */
uint16_t FSMC_GetData16(FSMC_Type * FSMCx, uint32_t bankn, uint32_t offset);

/*!
 * @brief Put the 8bit data by FSMC module.
 *
 * @param FSMCx FSMC instance.
 * @param bankn FSMC bank number.
 * @param offset offset of data in FSMC bank.
 * @param data Data value to be send through the transmiter.
 * @return None.
 */
void FSMC_PutData8(FSMC_Type * FSMCx, uint32_t bankn, uint32_t offset, uint8_t data);

/*!
 * @brief Get the 8bit data by FSMC module.
 *
 * @param FSMCx FSMC instance.
 * @param bankn FSMC bank number.
 * @param offset offset of data in FSMC bank.
 * @return The data value received from FSMC.
 */
uint8_t FSMC_GetData8(FSMC_Type * FSMCx, uint32_t bankn, uint32_t offset);

/*!
 *@}
 */

#endif /* __HAL_FSMC_H__ */

