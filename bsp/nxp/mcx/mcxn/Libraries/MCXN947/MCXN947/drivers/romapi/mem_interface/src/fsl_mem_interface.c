/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_flash.h"
#include "fsl_flash_ffr.h"
#include "fsl_flexspi_nor_flash.h"
#include "fsl_mem_interface.h"

/*! @brief Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.memInterface"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOOTLOADER_API_TREE_POINTER ((bootloader_tree_t *)0x1303fc00U)

/*! @brief IAP API Interface structure */
typedef struct iap_api_interface_struct
{
    standard_version_t version; /*!< IAP API version number. */
    status_t (*api_init)(api_core_context_t *coreCtx, const kp_api_init_param_t *param);
    status_t (*api_deinit)(api_core_context_t *coreCtx);
    status_t (*mem_init)(api_core_context_t *ctx);
    status_t (*mem_read)(api_core_context_t *ctx, uint32_t addr, uint32_t len, uint8_t *buf, uint32_t memoryId);
    status_t (*mem_write)(api_core_context_t *ctx, uint32_t addr, uint32_t len, const uint8_t *buf, uint32_t memoryId);
    status_t (*mem_fill)(api_core_context_t *ctx, uint32_t addr, uint32_t len, uint32_t pattern, uint32_t memoryId);
    status_t (*mem_flush)(api_core_context_t *ctx);
    status_t (*mem_erase)(api_core_context_t *ctx, uint32_t addr, uint32_t len, uint32_t memoryId);
    status_t (*mem_config)(api_core_context_t *ctx, uint32_t *buf, uint32_t memoryId);
    status_t (*mem_erase_all)(api_core_context_t *ctx, uint32_t memoryId);
    status_t (*sbloader_init)(api_core_context_t *ctx);
    status_t (*sbloader_pump)(api_core_context_t *ctx, uint8_t *data, uint32_t length);
    status_t (*sbloader_finalize)(api_core_context_t *ctx);
} iap_api_interface_t;

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
    void (*runBootloader)(void *arg);        /*!< Function to start the bootloader executing.*/
    standard_version_t version;              /*!< Bootloader version number.*/
    const char *copyright;                   /*!< Copyright string.*/
    const uint32_t reserved0;                /*!< reserved*/
    const uint32_t flashDriver;              /*!< Internal Flash driver API.*/
    const uint32_t reserved1[5];             /*!< reserved*/
    const uint32_t nbootDriver;              /*!< Please refer to "fsl_nboot.h" */
    const uint32_t flexspiNorDriver;         /*!< FlexSPI NOR FLASH Driver API.*/
    const uint32_t efuseDriver;              /*!< eFuse driver API */
    const iap_api_interface_t *iapAPIDriver; /*!< IAP driver API */
} bootloader_tree_t;
/*******************************************************************************
 * API
 ******************************************************************************/

standard_version_t API_Version(void)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->iapAPIDriver->version;
}

/*! @brief Initialize the IAP API runtime environment */
status_t API_Init(api_core_context_t *coreCtx, const kp_api_init_param_t *param)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->iapAPIDriver->api_init(coreCtx, param);
}

/*! @brief Deinitialize the IAP API runtime environment */
status_t API_Deinit(api_core_context_t *coreCtx)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->iapAPIDriver->api_deinit(coreCtx);
}

/*! @brief Intialize the memory interface of the IAP API */
status_t MEM_Init(api_core_context_t *coreCtx)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->iapAPIDriver->mem_init(coreCtx);
}

/*! @brief Perform the memory write operation */
status_t MEM_Write(
    api_core_context_t *coreCtx, uint32_t start, uint32_t lengthInBytes, const uint8_t *buf, uint32_t memoryId)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->iapAPIDriver->mem_write(coreCtx, start, lengthInBytes, buf, memoryId);
}

/*! @brief Perform the Fill operation */
status_t MEM_Fill(
    api_core_context_t *coreCtx, uint32_t start, uint32_t lengthInBytes, uint32_t pattern, uint32_t memoryId)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->iapAPIDriver->mem_fill(coreCtx, start, lengthInBytes, pattern, memoryId);
}

/*! @brief Perform the Memory erase operation */
status_t MEM_Erase(api_core_context_t *coreCtx, uint32_t start, uint32_t lengthInBytes, uint32_t memoryId)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->iapAPIDriver->mem_erase(coreCtx, start, lengthInBytes, memoryId);
}
/*! @brief Perform the full Memory erase operation */
status_t MEM_EraseAll(api_core_context_t *coreCtx, uint32_t memoryId)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->iapAPIDriver->mem_erase_all(coreCtx, memoryId);
}

/*! @brief Perform the Memory configuration operation */
status_t MEM_Config(api_core_context_t *coreCtx, uint32_t *config, uint32_t memoryId)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->iapAPIDriver->mem_config(coreCtx, config, memoryId);
}

/*! @brief Perform the Memory Flush operation */
status_t MEM_Flush(api_core_context_t *coreCtx)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->iapAPIDriver->mem_flush(coreCtx);
}

/*! @brief Perform the Sbloader runtime environment initialization */
status_t Sbloader_Init(api_core_context_t *ctx)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->iapAPIDriver->sbloader_init(ctx);
}

/*! @brief Handle the SB data stream */
status_t Sbloader_Pump(api_core_context_t *ctx, uint8_t *data, uint32_t length)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->iapAPIDriver->sbloader_pump(ctx, data, length);
}
/*! @brief Finish the sbloader handling */
status_t Sbloader_Finalize(api_core_context_t *ctx)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->iapAPIDriver->sbloader_finalize(ctx);
}
