/***********************************************************************************************//**
 * \file cy_serial_flash_qspi.c
 *
 * \brief
 * Provides APIs for interacting with an external flash connected to the SPI or
 * QSPI interface, uses SFDP to auto-discover memory properties if SFDP is
 * enabled in the configuration.
 *
 ***************************************************************************************************
 * \copyright
 * Copyright 2018-2022 Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **************************************************************************************************/

#include <stdbool.h>
#include "cy_serial_flash_qspi.h"
#include "cyhal_qspi.h"
#include "cy_trigmux.h"
#include "cy_dma.h"
#include "cy_utils.h"

#if defined(CY_SERIAL_FLASH_QSPI_THREAD_SAFE)
#include <stdlib.h>
#include "cyabs_rtos.h"
#endif /* #if defined(CY_SERIAL_FLASH_QSPI_THREAD_SAFE) */

#ifdef CY_IP_MXSMIF

#if defined(__cplusplus)
extern "C" {
#endif


/** \cond INTERNAL */

/** Timeout to apply while polling the memory for its ready status after quad
 *  enable command has been sent out. Quad enable is a non-volatile write.
 */
#define CY_SERIAL_FLASH_QUAD_ENABLE_TIMEOUT_US      (5000lu) // in microseconds

/** Number of loops to run while polling the SMIF for its busy status. */
#define SMIF_BUSY_CHECK_LOOP_COUNT                  (10lu)

/** Timeout to apply per loop while polling the SMIF for its busy status. */
#define SMIF_BUSY_CHECK_TIMEOUT_MS                  (1lu) // in milliseconds

// Number of memories supported by the driver
#define SMIF_MEM_DEVICES                            (1u)

// SMIF slot from which the memory configuration is picked up - fixed to 0 as
// the driver supports only one device
#define MEM_SLOT                                    (0u)

/* Maximum number of bytes that can be read by SMIF in one transfer */
#define SMIF_MAX_RX_COUNT                           (65536lu)

#define DMA_YCOUNT_ONE_LOOP                         (1lu)

#define MSB_SHIFT_EIGHT                             (0x08u)
#define LSB_MASK                                    (0xFFlu)

/* Masks used for checking the flag bits */
#define FLAG_QSPI_HAL_INIT_DONE                     (0x01lu << 0)
#define FLAG_DMA_INIT_DONE                          (0x01lu << 1)
#define FLAG_READ_IN_PROGRESS                       (0x01lu << 2)

#define IS_FLAG_SET(mask)                           (status_flags & (mask))
#define SET_FLAG(mask)                              (status_flags |= (mask))
#define CLEAR_FLAG(mask)                            (status_flags &= ~(mask))

#if defined(CY_DEVICE_PSOC6ABLE2)
/* You cannot simply change these values. The trigger mux connect code in
 * _init_dma() needs to be updated correspondingly.
 */
    #define RX_DMA_INSTANCE             DW1
    #define RX_DMA_CHANNEL_NUM          (15lu)
    #define RX_DMA_CH0_IRQn             (cpuss_interrupts_dw1_0_IRQn)
#elif defined(CY_DEVICE_PSOC6A2M) || defined(CY_DEVICE_PSOC6A512K) || defined(CY_DEVICE_PSOC6A256K)
/* In these devices, only 1to1 triggers are available between SMIF and a
 * specific combination of DW instances and channel numbers.
 * i.e. TX trigger request from SMIF can connect only to DW1 CH22 and
 * RX trigger request from SMIF can connect only to DW1 CH23.
 */
    #define RX_DMA_INSTANCE             DW1
    #define RX_DMA_CHANNEL_NUM          (23lu)
    #define RX_DMA_CH0_IRQn             (cpuss_interrupts_dw1_0_IRQn)

    #define DEVICE_GROUP_1TO1_TRIGGER
#elif defined(CY_DEVICE_CYW20829)
    #define RX_DMA_INSTANCE             DW0
    #define RX_DMA_CHANNEL_NUM          (0u)
    #define RX_DMA_CH0_IRQn             (cpuss_interrupts_dw0_0_IRQn)
#else // if defined(CY_DEVICE_PSOC6ABLE2)
    #define DMA_UNSUPPORTED
#endif // if defined(CY_DEVICE_PSOC6ABLE2)

#define DMA_CHANNEL_PRIORITY            (3lu)
#define DMA_INTR_PRIORITY               (7lu)

/** \endcond */

static cyhal_qspi_t qspi_obj;
static volatile uint32_t status_flags;
static cy_stc_smif_mem_config_t* qspi_mem_config[SMIF_MEM_DEVICES];

static cy_stc_smif_block_config_t qspi_block_config =
{
    // The number of SMIF memories defined.
    .memCount     = SMIF_MEM_DEVICES,
    // The pointer to the array of memory config structures of size memCount.
    .memConfig    = (cy_stc_smif_mem_config_t**)qspi_mem_config,
    // The version of the SMIF driver.
    .majorVersion = CY_SMIF_DRV_VERSION_MAJOR,
    // The version of the SMIF driver.
    .minorVersion = CY_SMIF_DRV_VERSION_MINOR
};

#if defined(CY_SERIAL_FLASH_QSPI_THREAD_SAFE)
static cy_mutex_t serial_flash_mutex;
#endif /* #if defined(CY_SERIAL_FLASH_QSPI_THREAD_SAFE) */

#ifndef DMA_UNSUPPORTED
typedef struct
{
    uint32_t addr;
    size_t length;
    uint8_t* buf;
    cy_serial_flash_qspi_read_complete_callback_t callback;
    void* callback_arg;
} read_txfr_info_t;

static read_txfr_info_t read_txfr_info;

/* DMA related variables */
static cy_stc_dma_descriptor_t dma_descr;

/* Default DW descriptor config */
static cy_stc_dma_descriptor_config_t dma_descr_config =
{
    .retrigger       = CY_DMA_RETRIG_4CYC,
    .interruptType   = CY_DMA_DESCR,
    .triggerOutType  = CY_DMA_DESCR_CHAIN,
    .channelState    = CY_DMA_CHANNEL_ENABLED,
    .triggerInType   = CY_DMA_DESCR,
    .dataSize        = CY_DMA_BYTE,
    .srcTransferSize = CY_DMA_TRANSFER_SIZE_WORD,
    .dstTransferSize = CY_DMA_TRANSFER_SIZE_DATA,
    .descriptorType  = CY_DMA_2D_TRANSFER,
    .srcAddress      = 0,
    .dstAddress      = 0,
    .srcXincrement   = 0U,
    .dstXincrement   = 1U,
    .xCount          = 1UL,
    .srcYincrement   = 0U,
    .dstYincrement   = CY_DMA_LOOP_COUNT_MAX,
    .yCount          = 1UL,
    .nextDescriptor  = &dma_descr,
};

/* Default DW channel config */
static cy_stc_dma_channel_config_t dma_channel_config =
{
    .descriptor  = &dma_descr,
    .preemptable = false,
    .priority    = DMA_CHANNEL_PRIORITY,
    .enable      = false,
    .bufferable  = false,
};

static const cyhal_resource_inst_t DW_obj =
{
    .type        = CYHAL_RSC_DW,
    .block_num   = ((uint32_t)RX_DMA_INSTANCE - DW0_BASE)/sizeof(DW_Type),
    .channel_num = RX_DMA_CHANNEL_NUM
};

static cy_rslt_t _init_dma(void);
static cy_rslt_t _deinit_dma(void);
static void _rx_dma_irq_handler(void);
static cy_en_smif_status_t _read_next_chunk(void);
#if !defined(CY_DEVICE_CYW20829)
static void _value_to_byte_array(uint32_t value, uint8_t* byte_array, uint32_t start_pos,
                                 uint32_t size);
#endif /* #if !defined(CY_DEVICE_CYW20829) */
#endif /* #ifndef DMA_UNSUPPORTED */

static inline cy_rslt_t _mutex_acquire(void);
static inline cy_rslt_t _mutex_release(void);

#if defined(CY_DEVICE_CYW20829)
static cy_stc_smif_context_t SMIFContext;
#endif /* defined(CY_DEVICE_CYW20829) */

//--------------------------------------------------------------------------------------------------
// cy_serial_flash_qspi_init
//
// The driver supports only one memory. When multiple memory configurations are generated by the
// SMIF configurator tool, provide only the configuration for memory that need to be supported by
// the driver.  Memory configuration can be changed by deinit followed by init with new
// configuration
//--------------------------------------------------------------------------------------------------
cy_rslt_t cy_serial_flash_qspi_init(
    const cy_stc_smif_mem_config_t* mem_config,
    cyhal_gpio_t io0,
    cyhal_gpio_t io1,
    cyhal_gpio_t io2,
    cyhal_gpio_t io3,
    cyhal_gpio_t io4,
    cyhal_gpio_t io5,
    cyhal_gpio_t io6,
    cyhal_gpio_t io7,
    cyhal_gpio_t sclk,
    cyhal_gpio_t ssel,
    uint32_t hz)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
    cy_en_smif_status_t smif_status = CY_SMIF_SUCCESS;

    #if (CYHAL_API_VERSION >= 2)
    // SMIF is already initialized for 20829 hence we can skip calling cyhal_qspi_init.
    // initializing only the SMIF base address and the context variables for 20829.
    #if defined(CY_DEVICE_CYW20829)
    qspi_obj.base = SMIF0;
    qspi_obj.context = SMIFContext;
    #else /* defined(CY_DEVICE_CYW20829) */
    cyhal_qspi_slave_pin_config_t memory_pin_set =
    {
        .io   = { io0, io1, io2, io3, io4, io5, io6, io7 },
        .ssel = ssel
    };
    result = cyhal_qspi_init(&qspi_obj, sclk, &memory_pin_set, hz, 0, NULL);
    #endif /* defined(CY_DEVICE_CYW20829) */

    #else /* HAL API version 1 */
    result = cyhal_qspi_init(&qspi_obj, io0, io1, io2, io3, io4, io5, io6, io7, sclk, ssel, hz, 0);
    #endif /* HAL API version 1 */

    qspi_mem_config[MEM_SLOT] = (cy_stc_smif_mem_config_t*)mem_config;

    if (CY_RSLT_SUCCESS == result)
    {
        SET_FLAG(FLAG_QSPI_HAL_INIT_DONE);

        // Perform SFDP detection and XIP register configuration depending on the memory
        // configuration.
        smif_status = Cy_SMIF_MemInit(qspi_obj.base, &qspi_block_config, &qspi_obj.context);
        if (CY_SMIF_SUCCESS == smif_status)
        {
            // Enable Quad mode (1-1-4 or 1-4-4 modes) to use all the four I/Os during
            // communication.

            if ((qspi_block_config.memConfig[MEM_SLOT]->deviceCfg->readCmd->dataWidth ==
                 CY_SMIF_WIDTH_QUAD) ||
                (qspi_block_config.memConfig[MEM_SLOT]->deviceCfg->programCmd->dataWidth ==
                 CY_SMIF_WIDTH_QUAD))
            {
                bool isQuadEnabled = false;
                smif_status =
                    Cy_SMIF_MemIsQuadEnabled(qspi_obj.base, qspi_block_config.memConfig[MEM_SLOT],
                                             &isQuadEnabled, &qspi_obj.context);
                if ((CY_SMIF_SUCCESS == smif_status) && !isQuadEnabled)
                {
                    smif_status =
                        Cy_SMIF_MemEnableQuadMode(qspi_obj.base,
                                                  qspi_block_config.memConfig[MEM_SLOT],
                                                  CY_SERIAL_FLASH_QUAD_ENABLE_TIMEOUT_US,
                                                  &qspi_obj.context);
                }
            }
            if (CY_SMIF_SUCCESS == smif_status)
            {
                #ifndef DMA_UNSUPPORTED
                result = _init_dma();

                if (CY_RSLT_SUCCESS == result)
                {
                    SET_FLAG(FLAG_DMA_INIT_DONE);
                #endif /* #ifndef DMA_UNSUPPORTED */

                #if defined(CY_SERIAL_FLASH_QSPI_THREAD_SAFE)
                /* Initialize the mutex */
                result = cy_rtos_init_mutex(&serial_flash_mutex);
                #endif /* #if defined(CY_SERIAL_FLASH_QSPI_THREAD_SAFE) */

                #ifndef DMA_UNSUPPORTED
            }
                #endif /* #ifndef DMA_UNSUPPORTED */
            }
        }
    }

    if ((CY_RSLT_SUCCESS != result) || (CY_SMIF_SUCCESS != smif_status))
    {
        cy_serial_flash_qspi_deinit();

        if (CY_SMIF_SUCCESS != smif_status)
        {
            result = (cy_rslt_t)smif_status;
        }
    }

    return result;
}


//--------------------------------------------------------------------------------------------------
// cy_serial_flash_qspi_deinit
//--------------------------------------------------------------------------------------------------
void cy_serial_flash_qspi_deinit(void)
{
    cy_rslt_t result;

    if (IS_FLAG_SET(FLAG_QSPI_HAL_INIT_DONE))
    {
        /* For CYW20829, BOOTROM enables XIP by default and user is not expected to
           disable memory while in XIP */
        #if !defined(CY_DEVICE_CYW20829)
        if (qspi_obj.base != NULL)
        {
            /* There is no harm in calling this even if Cy_SMIF_MemInit() did
             * not succeed since anyway we own the QSPI object.
             */
            Cy_SMIF_MemDeInit(qspi_obj.base);
        }

        cyhal_qspi_free(&qspi_obj);
        #endif /* !defined(CY_DEVICE_CYW20829) */
        CLEAR_FLAG(FLAG_QSPI_HAL_INIT_DONE);

        #ifndef DMA_UNSUPPORTED
        if (IS_FLAG_SET(FLAG_DMA_INIT_DONE))
        {
            result = _deinit_dma();
            CY_ASSERT(CY_RSLT_SUCCESS == result);

            CLEAR_FLAG(FLAG_DMA_INIT_DONE);
        #endif /* #ifndef DMA_UNSUPPORTED */

        #if defined(CY_SERIAL_FLASH_QSPI_THREAD_SAFE)
        result = cy_rtos_deinit_mutex(&serial_flash_mutex);
        CY_ASSERT(CY_RSLT_SUCCESS == result);
        #endif /* #if defined(CY_SERIAL_FLASH_QSPI_THREAD_SAFE) */

        #ifndef DMA_UNSUPPORTED
    }
        #endif /* #ifndef DMA_UNSUPPORTED */
    }

    CY_UNUSED_PARAMETER(result); /* To avoid compiler warning in Release mode. */
}


//--------------------------------------------------------------------------------------------------
// cy_serial_flash_qspi_get_size
//--------------------------------------------------------------------------------------------------
size_t cy_serial_flash_qspi_get_size(void)
{
    return (size_t)qspi_block_config.memConfig[MEM_SLOT]->deviceCfg->memSize;
}


//--------------------------------------------------------------------------------------------------
// cy_serial_flash_qspi_get_erase_size
//--------------------------------------------------------------------------------------------------
size_t cy_serial_flash_qspi_get_erase_size(uint32_t addr)
{
    size_t                            erase_sector_size;
    cy_stc_smif_hybrid_region_info_t* hybrid_info = NULL;

    cy_en_smif_status_t smif_status =
        Cy_SMIF_MemLocateHybridRegion(qspi_block_config.memConfig[MEM_SLOT], &hybrid_info, addr);

    if (CY_SMIF_SUCCESS != smif_status)
    {
        erase_sector_size = (size_t)qspi_block_config.memConfig[MEM_SLOT]->deviceCfg->eraseSize;
    }
    else
    {
        erase_sector_size = (size_t)hybrid_info->eraseSize;
    }

    return erase_sector_size;
}


//--------------------------------------------------------------------------------------------------
// cy_serial_flash_qspi_get_prog_size
//--------------------------------------------------------------------------------------------------
size_t cy_serial_flash_qspi_get_prog_size(uint32_t addr)
{
    CY_UNUSED_PARAMETER(addr);
    return (size_t)qspi_block_config.memConfig[MEM_SLOT]->deviceCfg->programSize;
}


//--------------------------------------------------------------------------------------------------
// cy_serial_flash_qspi_read
//--------------------------------------------------------------------------------------------------
cy_rslt_t cy_serial_flash_qspi_read(uint32_t addr, size_t length, uint8_t* buf)
{
    cy_rslt_t result_mutex_rel = CY_RSLT_SUCCESS;

    cy_rslt_t result = _mutex_acquire();

    if (CY_RSLT_SUCCESS == result)
    {
        // Cy_SMIF_MemRead() returns error if (addr + length) > total flash size.
        result = (cy_rslt_t)Cy_SMIF_MemRead(qspi_obj.base, qspi_block_config.memConfig[MEM_SLOT],
                                            addr,
                                            buf, length, &qspi_obj.context);
        result_mutex_rel = _mutex_release();
    }

    /* Give priority to the status of SMIF operation when both SMIF operation
     * and mutex release fail.
     */
    return ((CY_RSLT_SUCCESS == result) ? result_mutex_rel : result);
}


//--------------------------------------------------------------------------------------------------
// cy_serial_flash_qspi_abort_read
//--------------------------------------------------------------------------------------------------
cy_rslt_t cy_serial_flash_qspi_abort_read(void)
{
    #ifndef DMA_UNSUPPORTED
    cy_rslt_t result;

    /* Wait until SMIF finishes any pending transfer. */
    for (uint32_t loop = 0; loop < SMIF_BUSY_CHECK_LOOP_COUNT; loop++)
    {
        if (!Cy_SMIF_BusyCheck(qspi_obj.base))
        {
            break;
        }

        cyhal_system_delay_ms(SMIF_BUSY_CHECK_TIMEOUT_MS);
    }

    if (Cy_SMIF_BusyCheck(qspi_obj.base))
    {
        SET_FLAG(FLAG_READ_IN_PROGRESS);
        result = CY_RSLT_SERIAL_FLASH_ERR_QSPI_BUSY;
    }
    else
    {
        Cy_DMA_Channel_Disable(RX_DMA_INSTANCE, RX_DMA_CHANNEL_NUM);
        result = CY_RSLT_SUCCESS;
        CLEAR_FLAG(FLAG_READ_IN_PROGRESS);
    }

    return result;
    #else // ifndef DMA_UNSUPPORTED
    return CY_RSLT_SERIAL_FLASH_ERR_UNSUPPORTED;
    #endif /* #ifndef DMA_UNSUPPORTED */
}


//--------------------------------------------------------------------------------------------------
// cy_serial_flash_qspi_read_async
//--------------------------------------------------------------------------------------------------
cy_rslt_t cy_serial_flash_qspi_read_async(uint32_t addr, size_t length, uint8_t* buf,
                                          cy_serial_flash_qspi_read_complete_callback_t callback,
                                          void* callback_arg)
{
    #ifndef DMA_UNSUPPORTED
    cy_rslt_t result = CY_RSLT_SERIAL_FLASH_ERR_BAD_PARAM;
    cy_rslt_t result_mutex_rel = CY_RSLT_SUCCESS;

    CY_ASSERT(NULL != buf);

    if (IS_FLAG_SET(FLAG_READ_IN_PROGRESS))
    {
        result = CY_RSLT_SERIAL_FLASH_ERR_READ_BUSY; /* Previous read request is not yet complete.
                                                      */
    }
    else if ((addr + length) <= cy_serial_flash_qspi_get_size())
    {
        result = _mutex_acquire();

        if (CY_RSLT_SUCCESS == result)
        {
            read_txfr_info.addr = addr;
            read_txfr_info.length = length;
            read_txfr_info.buf = buf;
            read_txfr_info.callback = callback;
            read_txfr_info.callback_arg = callback_arg;

            /* Enable the DMA channel */
            Cy_DMA_Channel_Enable(RX_DMA_INSTANCE, RX_DMA_CHANNEL_NUM);

            SET_FLAG(FLAG_READ_IN_PROGRESS);
            result = (cy_rslt_t)_read_next_chunk();  /* Start the read transfer */

            if (CY_RSLT_SUCCESS != result)
            {
                CLEAR_FLAG(FLAG_READ_IN_PROGRESS);
            }

            result_mutex_rel = _mutex_release();
        }
    }

    /* Give priority to the status of SMIF operation when both SMIF operation
     * and mutex release fail.
     */
    return ((CY_RSLT_SUCCESS == result) ? result_mutex_rel : result);
    #else // ifndef DMA_UNSUPPORTED
    CY_UNUSED_PARAMETER(addr);
    CY_UNUSED_PARAMETER(length);
    CY_UNUSED_PARAMETER(buf);
    CY_UNUSED_PARAMETER(callback);
    CY_UNUSED_PARAMETER(callback_arg);

    return CY_RSLT_SERIAL_FLASH_ERR_UNSUPPORTED;
    #endif /* #ifndef DMA_UNSUPPORTED */
}


//--------------------------------------------------------------------------------------------------
// cy_serial_flash_qspi_write
//--------------------------------------------------------------------------------------------------
cy_rslt_t cy_serial_flash_qspi_write(uint32_t addr, size_t length, const uint8_t* buf)
{
    cy_rslt_t result_mutex_rel = CY_RSLT_SUCCESS;

    cy_rslt_t result = _mutex_acquire();

    if (CY_RSLT_SUCCESS == result)
    {
        // Cy_SMIF_MemWrite() returns error if (addr + length) > total flash size.
        result = (cy_rslt_t)Cy_SMIF_MemWrite(qspi_obj.base, qspi_block_config.memConfig[MEM_SLOT],
                                             addr,
                                             (uint8_t*)buf, length, &qspi_obj.context);
        result_mutex_rel = _mutex_release();
    }

    /* Give priority to the status of SMIF operation when both SMIF operation
     * and mutex release fail.
     */
    return ((CY_RSLT_SUCCESS == result) ? result_mutex_rel : result);
}


//--------------------------------------------------------------------------------------------------
// cy_serial_flash_qspi_erase
//--------------------------------------------------------------------------------------------------
cy_rslt_t cy_serial_flash_qspi_erase(uint32_t addr, size_t length)
{
    cy_rslt_t result_mutex_rel = CY_RSLT_SUCCESS;

    cy_rslt_t result = _mutex_acquire();

    if (CY_RSLT_SUCCESS == result)
    {
        // If the erase is for the entire chip, use chip erase command
        if ((addr == 0u) && (length == cy_serial_flash_qspi_get_size()))
        {
            result =
                (cy_rslt_t)Cy_SMIF_MemEraseChip(qspi_obj.base,
                                                qspi_block_config.memConfig[MEM_SLOT],
                                                &qspi_obj.context);
        }
        else
        {
            // Cy_SMIF_MemEraseSector() returns error if (addr + length) > total flash size or if
            // addr is not aligned to erase sector size or if (addr + length) is not aligned to
            // erase sector size.
            result =
                (cy_rslt_t)Cy_SMIF_MemEraseSector(qspi_obj.base,
                                                  qspi_block_config.memConfig[MEM_SLOT],
                                                  addr, length, &qspi_obj.context);
        }

        result_mutex_rel = _mutex_release();
    }

    /* Give priority to the status of SMIF operation when both SMIF operation
     * and mutex release fail.
     */
    return ((CY_RSLT_SUCCESS == result) ? result_mutex_rel : result);
}


//--------------------------------------------------------------------------------------------------
// cy_serial_flash_qspi_enable_xip
//
// This function enables or disables XIP on the MCU, does not send any command
// to the serial flash. XIP register configuration is already done as part of
// cy_serial_flash_qspi_init() if MMIO mode is enabled in the QSPI
// Configurator.
//--------------------------------------------------------------------------------------------------
cy_rslt_t cy_serial_flash_qspi_enable_xip(bool enable)
{
    if (enable)
    {
        Cy_SMIF_SetMode(qspi_obj.base, CY_SMIF_MEMORY);
    }
    else
    {
        Cy_SMIF_SetMode(qspi_obj.base, CY_SMIF_NORMAL);
    }

    return CY_RSLT_SUCCESS;
}


//--------------------------------------------------------------------------------------------------
// cy_serial_flash_qspi_set_interrupt_priority
//--------------------------------------------------------------------------------------------------
void cy_serial_flash_qspi_set_interrupt_priority(uint8_t priority)
{
    #if defined(CY_DEVICE_CYW20829)
    NVIC_SetPriority(smif_interrupt_normal_IRQn, priority);
    #else /* defined(CY_DEVICE_CYW20829) */
    NVIC_SetPriority(smif_interrupt_IRQn, priority);
    #endif /* defined(CY_DEVICE_CYW20829) */
}


//--------------------------------------------------------------------------------------------------
// cy_serial_flash_qspi_set_interrupt_priority
//--------------------------------------------------------------------------------------------------
void cy_serial_flash_qspi_set_dma_interrupt_priority(uint8_t priority)
{
    #ifndef DMA_UNSUPPORTED
    NVIC_SetPriority((IRQn_Type)(RX_DMA_CH0_IRQn + RX_DMA_CHANNEL_NUM), priority);
    #else
    CY_UNUSED_PARAMETER(priority);
    #endif /* #ifndef DMA_UNSUPPORTED */
}


#ifndef DMA_UNSUPPORTED
//--------------------------------------------------------------------------------------------------
// _read_next_chunk
//--------------------------------------------------------------------------------------------------
static cy_en_smif_status_t _read_next_chunk(void)
{
    cy_en_smif_status_t smif_status = CY_SMIF_SUCCESS;
    uint32_t chunk;
    #if !defined(CY_DEVICE_CYW20829)
    uint8_t addr_array[CY_SMIF_FOUR_BYTES_ADDR] = { 0U };
    #endif /* !defined(CY_DEVICE_CYW20829) */

    if (read_txfr_info.length > 0UL)
    {
        /* SMIF can read only up to 65536 bytes in one go. Split the larger read into multiple
           chunks */
        chunk =
            (read_txfr_info.length >
             SMIF_MAX_RX_COUNT) ? (SMIF_MAX_RX_COUNT) : read_txfr_info.length;

        /* In 2D transfer, (X_count x Y_count) should be a multiple of CY_DMA_LOOP_COUNT_MAX (256).
         */
        if (chunk > CY_DMA_LOOP_COUNT_MAX)
        {
            /* Make chunk divisible by CY_DMA_LOOP_COUNT_MAX (256) by masking out the LS bits */
            chunk &= ~(CY_DMA_LOOP_COUNT_MAX - 1);

            dma_descr_config.yCount = chunk/CY_DMA_LOOP_COUNT_MAX;
            dma_descr_config.xCount = CY_DMA_LOOP_COUNT_MAX;
        }
        else
        {
            dma_descr_config.yCount = DMA_YCOUNT_ONE_LOOP;
            dma_descr_config.xCount = chunk;
        }

        dma_descr_config.dstAddress = (void*)read_txfr_info.buf;
        #if defined(CY_DEVICE_CYW20829)
        dma_descr_config.dataSize = CY_DMA_BYTE;
        dma_descr_config.srcTransferSize = CY_DMA_TRANSFER_SIZE_DATA,
        dma_descr_config.srcXincrement = 1;
        dma_descr_config.srcAddress =
            (void*)(qspi_block_config.memConfig[MEM_SLOT]->baseAddress + read_txfr_info.addr);
        #endif /* defined(CY_DEVICE_CYW20829) */
        Cy_DMA_Descriptor_Init(&dma_descr, &dma_descr_config);

        #if defined(CY_DEVICE_CYW20829)
        Cy_TrigMux_SwTrigger(TRIG_OUT_MUX_0_PDMA0_TR_IN0, CY_TRIGGER_TWO_CYCLES);
        #else /* defined(CY_DEVICE_CYW20829) */
        /* Pass NULL for buffer (and callback) so that the function does not
         * set up FIFO interrupt. We don't need FIFO interrupt to be setup
         * since we will be using DMA.
         */
        _value_to_byte_array(read_txfr_info.addr, &addr_array[0], 0UL,
                             qspi_block_config.memConfig[MEM_SLOT]->deviceCfg->numOfAddrBytes);
        smif_status = Cy_SMIF_MemCmdRead(qspi_obj.base, qspi_block_config.memConfig[MEM_SLOT],
                                         addr_array, NULL, chunk, NULL, &qspi_obj.context);

        if (CY_SMIF_SUCCESS == smif_status)
        #endif /* defined(CY_DEVICE_CYW20829) */
        {
            /* Recalculate the next rxBuffer offset */
            read_txfr_info.length -= chunk;
            read_txfr_info.addr += chunk;
            read_txfr_info.buf += chunk;
        }
    }

    return smif_status;
}


//--------------------------------------------------------------------------------------------------
// _init_dma
//--------------------------------------------------------------------------------------------------
static cy_rslt_t _init_dma(void)
{
    cy_rslt_t result;

    /* Set the source address of the descriptor */
    dma_descr_config.srcAddress = (void*)&SMIF_RX_DATA_FIFO_RD1(qspi_obj.base);

    /* Configure the RX DMA */
    result =
        (cy_rslt_t)Cy_DMA_Channel_Init(RX_DMA_INSTANCE, RX_DMA_CHANNEL_NUM, &dma_channel_config);

    if (CY_RSLT_SUCCESS == result)
    {
        Cy_DMA_Channel_SetInterruptMask(RX_DMA_INSTANCE, RX_DMA_CHANNEL_NUM, CY_DMA_INTR_MASK);
        Cy_DMA_Enable(RX_DMA_INSTANCE);

        /* Configure interrupt for RX DMA */
        cy_stc_sysint_t dma_intr_config =
            { .intrSrc        = (IRQn_Type)(RX_DMA_CH0_IRQn + RX_DMA_CHANNEL_NUM),
              .intrPriority   = DMA_INTR_PRIORITY };

        result = (cy_rslt_t)Cy_SysInt_Init(&dma_intr_config, _rx_dma_irq_handler);

        if (CY_RSLT_SUCCESS == result)
        {
            NVIC_EnableIRQ(dma_intr_config.intrSrc);

            /* Configure the trigger mux */
            #if defined(DEVICE_GROUP_1TO1_TRIGGER)
            result = (cy_rslt_t)Cy_TrigMux_Select(TRIG_OUT_1TO1_3_SMIF_RX_TO_PDMA1_TR_IN23, false,
                                                  TRIGGER_TYPE_LEVEL);
            #else //defined(DEVICE_GROUP_1TO1_TRIGGER)
            #if !defined(CY_DEVICE_CYW20829)

            result = (cy_rslt_t)Cy_TrigMux_Connect(TRIG13_IN_SMIF_TR_RX_REQ,
                                                   TRIG13_OUT_TR_GROUP0_INPUT42, false,
                                                   TRIGGER_TYPE_LEVEL);

            if (CY_RSLT_SUCCESS == result)
            {
                result = (cy_rslt_t)Cy_TrigMux_Connect(TRIG1_IN_TR_GROUP13_OUTPUT15,
                                                       TRIG1_OUT_CPUSS_DW1_TR_IN15, false,
                                                       TRIGGER_TYPE_LEVEL);
            }
            #endif /*defined(CY_DEVICE_CYW20829)*/
            #endif /* #if defined(DEVICE_GROUP_1TO1_TRIGGER) */
        }
    }

    if (CY_RSLT_SUCCESS == result)
    {
        /* Reserve the DW instance so that HAL will not be able to use it later. */
        result = cyhal_hwmgr_reserve(&DW_obj);
    }

    return result;
}


//--------------------------------------------------------------------------------------------------
// _deinit_dma
//--------------------------------------------------------------------------------------------------
static cy_rslt_t _deinit_dma(void)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;

    NVIC_DisableIRQ((IRQn_Type)(RX_DMA_CH0_IRQn + RX_DMA_CHANNEL_NUM));

    /* Disable only the channel, not the DW instance as it may be used by other
     * part of the application.
     */
    Cy_DMA_Channel_Disable(RX_DMA_INSTANCE, RX_DMA_CHANNEL_NUM);

    /* Free the DMA resource so that HAL can use it now */
    cyhal_hwmgr_free(&DW_obj);

    #if defined(DEVICE_GROUP_1TO1_TRIGGER)
    result = (cy_rslt_t)Cy_TrigMux_Deselect(TRIG_OUT_1TO1_3_SMIF_RX_TO_PDMA1_TR_IN23);
    #else
    /* No PDL function is available for handling deinit for non-1to1 trigger muxes. */
    #endif /* #if defined(DEVICE_GROUP_1TO1_TRIGGER) */

    return result;
}


//--------------------------------------------------------------------------------------------------
// _rx_dma_irq_handler
//--------------------------------------------------------------------------------------------------
static void _rx_dma_irq_handler(void)
{
    cy_en_smif_status_t smif_status = CY_SMIF_SUCCESS;
    bool terminate_read_txfr = true;
    cy_en_dma_intr_cause_t cause = Cy_DMA_Channel_GetStatus(RX_DMA_INSTANCE, RX_DMA_CHANNEL_NUM);

    Cy_DMA_Channel_ClearInterrupt(RX_DMA_INSTANCE, RX_DMA_CHANNEL_NUM);

    if (CY_DMA_INTR_CAUSE_COMPLETION == cause)
    {
        if (read_txfr_info.length > 0UL)
        {
            smif_status = _read_next_chunk();

            if (CY_SMIF_SUCCESS == smif_status)
            {
                terminate_read_txfr = false;
            }
        }
    }
    else
    {
        smif_status = (cy_en_smif_status_t)CY_RSLT_SERIAL_FLASH_ERR_DMA;
    }

    if (terminate_read_txfr)
    {
        Cy_DMA_Channel_Disable(RX_DMA_INSTANCE, RX_DMA_CHANNEL_NUM);
        CLEAR_FLAG(FLAG_READ_IN_PROGRESS);

        /* Execute the callback */
        if (NULL != read_txfr_info.callback)
        {
            read_txfr_info.callback((cy_rslt_t)smif_status, read_txfr_info.callback_arg);
        }
    }
}


#if !defined(CY_DEVICE_CYW20829)
/*******************************************************************************
* Function Name: _value_to_byte_array
****************************************************************************//**
*
* Unpacks the specified number of bytes from a 32-bit value into the given byte
* array.
*
* \param value
* The 32-bit (4-byte) value to unpack.
*
* \param byte_array
* The byte array to fill.
*
* \param start_pos
* The start position of the byte array to begin filling from.
*
* \param size
* The number of bytes to unpack.
*
*******************************************************************************/
static void _value_to_byte_array(uint32_t value, uint8_t* byte_array, uint32_t start_pos,
                                 uint32_t size)
{
    CY_ASSERT((0lu < size) && (CY_SMIF_FOUR_BYTES_ADDR >= size));
    CY_ASSERT(NULL != byte_array);

    do
    {
        size--;
        byte_array[size + start_pos] = (uint8_t)(value & LSB_MASK);
        value >>= MSB_SHIFT_EIGHT; /* Shift to get the next byte */
    } while (size > 0U);
}


#endif /* #if !defined(CY_DEVICE_CYW20829)*/

#endif /* #ifndef DMA_UNSUPPORTED */

//--------------------------------------------------------------------------------------------------
// _mutex_acquire
//--------------------------------------------------------------------------------------------------
static inline cy_rslt_t _mutex_acquire(void)
{
    #if defined(CY_SERIAL_FLASH_QSPI_THREAD_SAFE)
    return cy_rtos_get_mutex(&serial_flash_mutex, CY_RTOS_NEVER_TIMEOUT);
    #else
    return CY_RSLT_SUCCESS;
    #endif /* #if defined(CY_SERIAL_FLASH_QSPI_THREAD_SAFE) */
}


//--------------------------------------------------------------------------------------------------
// _mutex_release
//--------------------------------------------------------------------------------------------------
static inline cy_rslt_t _mutex_release(void)
{
    #if defined(CY_SERIAL_FLASH_QSPI_THREAD_SAFE)
    return cy_rtos_set_mutex(&serial_flash_mutex);
    #else
    return CY_RSLT_SUCCESS;
    #endif /* #if defined(CY_SERIAL_FLASH_QSPI_THREAD_SAFE) */
}


#if defined(__cplusplus)
}
#endif

#endif // CY_IP_MXSMIF
