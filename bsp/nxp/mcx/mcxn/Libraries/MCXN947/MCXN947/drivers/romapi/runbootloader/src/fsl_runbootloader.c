/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_flash.h"
#include "fsl_flash_ffr.h"
#include "fsl_flexspi_nor_flash.h"
#include "fsl_runbootloader.h"

/*! @brief Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.runBootloader"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOOTLOADER_API_TREE_POINTER ((bootloader_tree_t *)0x1303fc00U)

/*!
 * @brief Root of the bootloader API tree.
 *
 * An instance of this struct resides in read-only memory in the bootloader. It
 * provides a user application access to APIs exported by the bootloader.
 *
 * @note The order of existing fields must not be changed.
 */
typedef struct BootloaderTree
{
    void (*runBootloader)(void *arg); /*!< Function to start the bootloader executing.*/
    const uint32_t version;           /*!< Bootloader version number.*/
    const char *copyright;            /*!< Copyright string.*/
    const uint32_t reserved0;         /*!< reserved*/
    const uint32_t flashDriver;       /*!< Internal Flash driver API.*/
    const uint32_t reserved1[5];      /*!< reserved*/
    const uint32_t nbootDriver;       /*!< Please refer to "fsl_nboot.h" */
    const uint32_t flexspiNorDriver;  /*!< FlexSPI NOR FLASH Driver API.*/
    const uint32_t reserved2;         /*!< reserved*/
    const uint32_t memoryInterface;   /*!< Please refer to "fsl_mem_interface.h" */
} bootloader_tree_t;

/*******************************************************************************
 * API
 ******************************************************************************/

void bootloader_user_entry(void *arg)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    BOOTLOADER_API_TREE_POINTER->runBootloader(arg);
}
