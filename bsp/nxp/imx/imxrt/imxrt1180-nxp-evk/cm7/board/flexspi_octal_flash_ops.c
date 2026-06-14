/*
 * Copyright 2019-2022, 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_flexspi.h"
#include "flexspi_port.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*******************************************************************************
 * Variables
 ******************************************************************************/

extern flexspi_device_config_t deviceconfig;
extern const uint32_t customLUTOctalMode[CUSTOM_LUT_LENGTH];
#if defined(EXAMPLE_FLASH_RESET_CONFIG) || defined(FLASH_ADESTO)
extern const uint32_t FastReadSDRLUTCommandSeq[4];
extern const uint32_t OctalReadDDRLUTCommandSeq[4];
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
void flexspi_nor_disable_cache(flexspi_cache_status_t *cacheStatus)
{
    (void)memset(cacheStatus, 0, sizeof(flexspi_cache_status_t));

#if (defined __CORTEX_M) && (__CORTEX_M == 7U)
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
    /* Disable D cache. */
    if (SCB_CCR_DC_Msk == (SCB_CCR_DC_Msk & SCB->CCR))
    {
        SCB_DisableDCache();
        cacheStatus->DCacheEnableFlag = true;
    }
#endif /* __DCACHE_PRESENT */

#if defined(__ICACHE_PRESENT) && (__ICACHE_PRESENT == 1U)
    /* Disable I cache. */
    if (SCB_CCR_IC_Msk == (SCB_CCR_IC_Msk & SCB->CCR))
    {
        SCB_DisableICache();
        cacheStatus->ICacheEnableFlag = true;
    }
#endif /* __ICACHE_PRESENT */

#elif (defined FSL_FEATURE_SOC_LMEM_COUNT) && (FSL_FEATURE_SOC_LMEM_COUNT != 0U)
    /* Disable code bus cache and system bus cache */
    if (LMEM_PCCCR_ENCACHE_MASK == (LMEM_PCCCR_ENCACHE_MASK & LMEM->PCCCR))
    {
        L1CACHE_DisableCodeCache();
        cacheStatus->codeCacheEnableFlag = true;
    }
    if (LMEM_PSCCR_ENCACHE_MASK == (LMEM_PSCCR_ENCACHE_MASK & LMEM->PSCCR))
    {
        L1CACHE_DisableSystemCache();
        cacheStatus->systemCacheEnableFlag = true;
    }

#elif (defined FSL_FEATURE_SOC_CACHE64_CTRL_COUNT) && (FSL_FEATURE_SOC_CACHE64_CTRL_COUNT != 0U)
    /* Disable cache */
    CACHE64_DisableCache(EXAMPLE_CACHE);
    cacheStatus->CacheEnableFlag = true;
#endif
}

void flexspi_nor_enable_cache(flexspi_cache_status_t cacheStatus)
{
#if (defined __CORTEX_M) && (__CORTEX_M == 7U)
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
    if (cacheStatus.DCacheEnableFlag)
    {
        /* Enable D cache. */
        SCB_EnableDCache();
    }
#endif /* __DCACHE_PRESENT */

#if defined(__ICACHE_PRESENT) && (__ICACHE_PRESENT == 1U)
    if (cacheStatus.ICacheEnableFlag)
    {
        /* Enable I cache. */
        SCB_EnableICache();
    }
#endif /* __ICACHE_PRESENT */

#elif (defined FSL_FEATURE_SOC_LMEM_COUNT) && (FSL_FEATURE_SOC_LMEM_COUNT != 0U)
    if (cacheStatus.codeCacheEnableFlag)
    {
        /* Enable code cache. */
        L1CACHE_EnableCodeCache();
    }

    if (cacheStatus.systemCacheEnableFlag)
    {
        /* Enable system cache. */
        L1CACHE_EnableSystemCache();
    }
#elif (defined FSL_FEATURE_SOC_CACHE64_CTRL_COUNT) && (FSL_FEATURE_SOC_CACHE64_CTRL_COUNT != 0U)
    if (cacheStatus.CacheEnableFlag)
    {
        /* Enable cache. */
        CACHE64_EnableCache(EXAMPLE_CACHE);
    }
#endif
}

status_t flexspi_nor_write_enable(FLEXSPI_Type *base, uint32_t baseAddr, bool enableOctal)
{
    flexspi_transfer_t flashXfer;
    status_t status;

    /* Write enable */
    flashXfer.deviceAddress = baseAddr;
    flashXfer.port          = FLASH_PORT;
    flashXfer.cmdType       = kFLEXSPI_Command;
    flashXfer.SeqNumber     = 1;
    if (enableOctal)
    {
        flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_WRITEENABLE_OPI;
    }
    else
    {
        flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_WRITEENABLE;
    }

    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    return status;
}

status_t flexspi_nor_wait_bus_busy(FLEXSPI_Type *base, bool enableOctal)
{
    /* Wait status ready. */
    bool isBusy;
    uint32_t readValue;
    status_t status;
    flexspi_transfer_t flashXfer;

    flashXfer.deviceAddress = 0;
    flashXfer.port          = FLASH_PORT;
    flashXfer.cmdType       = kFLEXSPI_Read;
    flashXfer.SeqNumber     = 1;
    if (enableOctal)
    {
        flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_READSTATUS_OPI;
    }
    else
    {
        flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_READSTATUS;
    }

    flashXfer.data     = &readValue;
    flashXfer.dataSize = 1;

    do
    {
        readValue = 0;
        status = FLEXSPI_TransferBlocking(base, &flashXfer);

        if (status != kStatus_Success)
        {
            return status;
        }
        if (FLASH_BUSY_STATUS_POL)
        {
            if (readValue & (1U << FLASH_BUSY_STATUS_OFFSET))
            {
                isBusy = true;
            }
            else
            {
                isBusy = false;
            }
        }
        else
        {
            if (readValue & (1U << FLASH_BUSY_STATUS_OFFSET))
            {
                isBusy = false;
            }
            else
            {
                isBusy = true;
            }
        }

    } while (isBusy);

    return status;
}

#if defined(FLASH_ENABLE_OCTAL_CMD)
status_t flexspi_nor_enable_octal_mode(FLEXSPI_Type *base)
{
    flexspi_transfer_t flashXfer;
    status_t status;

    /* Copy LUT information from flash region into RAM region, because flash boot mode maybe not same with application's
       required mode.
       If yes, doesn't need to memory copy operation; if no, need to memory opeation before flash access failure due to
       mismatch LUT read command sequence. */
#if defined(EXAMPLE_FLASH_RESET_CONFIG)
    uint32_t TempOctalReadDDRLUTCommandSeq[4];

    memcpy(TempOctalReadDDRLUTCommandSeq, OctalReadDDRLUTCommandSeq, sizeof(OctalReadDDRLUTCommandSeq));
#endif
#if defined(CACHE_MAINTAIN) && CACHE_MAINTAIN
    flexspi_cache_status_t cacheStatus;
    flexspi_nor_disable_cache(&cacheStatus);
#endif

#if defined(FLASH_ADESTO) && FLASH_ADESTO
    uint32_t tempLUT[4] = {0};
    uint32_t readValue;

    /* Update LUT table for octal mode. */
    FLEXSPI_UpdateLUT(base, 4 * NOR_CMD_LUT_SEQ_IDX_READ, OctalReadDDRLUTCommandSeq, 4);

    /* Set the command instruction of read status register for LUT in octal sdr mode. */
    tempLUT[0] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_8PAD, 0x05, kFLEXSPI_Command_DUMMY_SDR, kFLEXSPI_8PAD, 0x04);
    tempLUT[1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_SDR, kFLEXSPI_8PAD, 0x04, kFLEXSPI_Command_STOP, kFLEXSPI_8PAD, 0x0);
    /* Update LUT table. */
    FLEXSPI_UpdateLUT(base, 4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS_OPI, tempLUT, 4);

    /* Write enable */
    status = flexspi_nor_write_enable(base, 0, false);

    /* Enable quad mode. */
    flashXfer.deviceAddress = 0;
    flashXfer.port          = FLASH_PORT;
    flashXfer.cmdType       = kFLEXSPI_Command;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_ENTEROPI;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);
    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_nor_wait_bus_busy(base, true);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Check global protect or ont. */
    flashXfer.deviceAddress = 0;
    flashXfer.port          = FLASH_PORT;
    flashXfer.cmdType       = kFLEXSPI_Read;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_READSTATUS_OPI;

    flashXfer.data     = &readValue;
    flashXfer.dataSize = 1;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Global protected. */
    if ((readValue & 0x0CU) == 0x0CU)
    {
        /* Global unprotect entire memory region if it was protected by default, such as Adesto's octal flash. */
        tempLUT[0] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_8PAD, 0x01, kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_8PAD, 0x04);
        tempLUT[1] = 0x00U;

        /* Update LUT table. */
        FLEXSPI_UpdateLUT(base, 4 * NOR_CMD_LUT_SEQ_IDX_CONFIG, tempLUT, 4);

        uint32_t globalUnprotect = FLASH_UNPROTECTVALUE;

        /* Write enable */
        status = flexspi_nor_write_enable(base, 0, true);

        if (status != kStatus_Success)
        {
            return status;
        }

        flashXfer.deviceAddress = 0;
        flashXfer.port          = FLASH_PORT;
        flashXfer.cmdType       = kFLEXSPI_Write;
        flashXfer.SeqNumber     = 1;
        flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_CONFIG;
        flashXfer.data          = &globalUnprotect;
        flashXfer.dataSize      = 1;

        status = FLEXSPI_TransferBlocking(base, &flashXfer);
        if (status != kStatus_Success)
        {
            return status;
        }

        status = flexspi_nor_wait_bus_busy(base, true);

        if (status != kStatus_Success)
        {
            return status;
        }

        /* Check unprotect successfully or not. */
        flashXfer.deviceAddress = 0;
        flashXfer.port          = FLASH_PORT;
        flashXfer.cmdType       = kFLEXSPI_Read;
        flashXfer.SeqNumber     = 1;
        flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_READSTATUS_OPI;

        flashXfer.data     = &readValue;
        flashXfer.dataSize = 1;

        status = FLEXSPI_TransferBlocking(base, &flashXfer);
        if (status != kStatus_Success)
        {
            return status;
        }

        status = flexspi_nor_wait_bus_busy(base, true);
        if (status != kStatus_Success)
        {
            return status;
        }

        if ((readValue & 0x0CU) != 0x00U)
        {
            return -1;
        }
    }

    /* Enable DDR mode. */
    /* Update LUT table for configure status register2.*/
    tempLUT[0] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_8PAD, 0x31, kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_8PAD, 0x01);
    /* Update LUT table. */
    FLEXSPI_UpdateLUT(base, 4 * NOR_CMD_LUT_SEQ_IDX_CONFIG, tempLUT, 4);

    /* Set the command instruction of read status register for LUT in octal ddr mode. */
    tempLUT[0] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_8PAD, 0x05, kFLEXSPI_Command_DUMMY_DDR, kFLEXSPI_8PAD, 0x04);
    tempLUT[1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_DDR, kFLEXSPI_8PAD, 0x04, kFLEXSPI_Command_STOP, kFLEXSPI_8PAD, 0x0);
    /* Update LUT table. */
    FLEXSPI_UpdateLUT(base, 4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS_OPI, tempLUT, 4);

    /* Adesto enable octal mode needs to configures status register2. */
    uint32_t enableDdrMode = FLASH_ENABLE_OCTAL_DDRMODE;

    /* Write enable */
    status = flexspi_nor_write_enable(base, 0, true);
    if (status != kStatus_Success)
    {
        return status;
    }

    flashXfer.deviceAddress = 0;
    flashXfer.port          = FLASH_PORT;
    flashXfer.cmdType       = kFLEXSPI_Write;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_CONFIG;
    flashXfer.data          = &enableDdrMode;
    flashXfer.dataSize      = 1;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);
    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_nor_wait_bus_busy(base, true);

#else /* MXIC's octal flash. */

    uint32_t writeValue = FLASH_ENABLE_OCTAL_CMD;

    /* Write enable */
    status = flexspi_nor_write_enable(base, 0, false);

    if (status != kStatus_Success)
    {
        return status;
    }

    /* Enable quad mode. */
    flashXfer.deviceAddress = 0;
    flashXfer.port          = FLASH_PORT;
    flashXfer.cmdType       = kFLEXSPI_Write;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_ENTEROPI;
    flashXfer.data          = &writeValue;
    flashXfer.dataSize      = 1;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);
    if (status != kStatus_Success)
    {
        return status;
    }

    status             = flexspi_nor_wait_bus_busy(base, true);
#endif

#if defined(EXAMPLE_FLASH_RESET_CONFIG)
    /* 8DTRD: enter octal DDR and update read LUT entry into 8DTRD. */
    FLEXSPI_UpdateLUT(base, 4 * NOR_CMD_LUT_SEQ_IDX_READ, TempOctalReadDDRLUTCommandSeq, 4);
#endif

    /* Do software reset. */
    FLEXSPI_SoftwareReset(base);

#if defined(CACHE_MAINTAIN) && CACHE_MAINTAIN
    flexspi_nor_enable_cache(cacheStatus);
#endif

    return status;
}
#endif

status_t flexspi_nor_flash_erase_sector(FLEXSPI_Type *base, uint32_t address)
{
    status_t status;
    flexspi_transfer_t flashXfer;

#if defined(CACHE_MAINTAIN) && CACHE_MAINTAIN
    flexspi_cache_status_t cacheStatus;
    flexspi_nor_disable_cache(&cacheStatus);
#endif

    /* Write enable */
    status = flexspi_nor_write_enable(base, 0, true);

    if (status != kStatus_Success)
    {
        return status;
    }

    flashXfer.deviceAddress = address;
    flashXfer.port          = FLASH_PORT;
    flashXfer.cmdType       = kFLEXSPI_Command;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_ERASESECTOR;
    status                  = FLEXSPI_TransferBlocking(base, &flashXfer);

    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_nor_wait_bus_busy(base, true);

    /* Do software reset. */
    FLEXSPI_SoftwareReset(base);

#if defined(CACHE_MAINTAIN) && CACHE_MAINTAIN
    flexspi_nor_enable_cache(cacheStatus);
#endif

    return status;
}

status_t flexspi_nor_flash_page_program(FLEXSPI_Type *base, uint32_t dstAddr, const uint32_t *src)
{
#if defined(FLASH_ENABLE_OCTAL_CMD)
    assert(((uint32_t)dstAddr & (0x1UL)) == 0UL);
#endif
  
    status_t status;
    flexspi_transfer_t flashXfer;

#if defined(CACHE_MAINTAIN) && CACHE_MAINTAIN
    flexspi_cache_status_t cacheStatus;
    flexspi_nor_disable_cache(&cacheStatus);
#endif

    /* Write neable */
    status = flexspi_nor_write_enable(base, dstAddr, true);

    if (status != kStatus_Success)
    {
        return status;
    }

    /* Prepare page program command */
    flashXfer.deviceAddress = dstAddr;
    flashXfer.port          = FLASH_PORT;
    flashXfer.cmdType       = kFLEXSPI_Write;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM;
    flashXfer.data          = (uint32_t *)src;
    flashXfer.dataSize      = FLASH_PAGE_SIZE;
    status                  = FLEXSPI_TransferBlocking(base, &flashXfer);

    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_nor_wait_bus_busy(base, true);

    /* Do software reset. */
    FLEXSPI_SoftwareReset(base);

#if defined(CACHE_MAINTAIN) && CACHE_MAINTAIN
    flexspi_nor_enable_cache(cacheStatus);
#endif

    return status;
}

status_t flexspi_nor_read_data(FLEXSPI_Type *base, uint32_t startAddress, uint32_t *buffer, uint32_t length)
{
    status_t status;
    flexspi_transfer_t flashXfer;
    uint32_t readAddress = startAddress;

    /* Read page. */
    flashXfer.deviceAddress = readAddress;
    flashXfer.port          = FLASH_PORT;
    flashXfer.cmdType       = kFLEXSPI_Read;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_READ;
    flashXfer.data          = buffer;
    flashXfer.dataSize      = length;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    return status;
}

#if defined(__ICCARM__)
#pragma optimize = none
#endif
status_t flexspi_nor_get_vendor_id(FLEXSPI_Type *base, uint8_t *vendorId)
{
    /* Read manufacturer ID based on JEP106V spec, max continuation code table is 9, max manufacturer ID starts from
     * 9 + 1. */
    uint8_t id[10] = {0x00U};
    flexspi_transfer_t flashXfer;
    flashXfer.deviceAddress = 0;
    flashXfer.port          = FLASH_PORT;
    flashXfer.cmdType       = kFLEXSPI_Read;
    flashXfer.SeqNumber     = 1;
#if defined(FLASH_ADESTO) && FLASH_ADESTO
    flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_READID_SPI;
#else
    flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_READID_OPI;
#endif
    flashXfer.data     = (uint32_t *)id;
    flashXfer.dataSize = 10U;

    status_t status = FLEXSPI_TransferBlocking(base, &flashXfer);

    for (uint8_t i = 0x00U; i < 10U; i++)
    {
        if (0x7FU != id[i])
        {
            *vendorId = (uint32_t)id[i];
            break;
        }
    }

    return status;
}

void flexspi_nor_flash_init(FLEXSPI_Type *base)
{
    flexspi_config_t config;
    /* To store custom's LUT table in local. */
    uint32_t tempCustomLUT[CUSTOM_LUT_LENGTH] = {0U};

#if defined(CACHE_MAINTAIN) && CACHE_MAINTAIN
    flexspi_cache_status_t cacheStatus;
    flexspi_nor_disable_cache(&cacheStatus);
#endif

    /* Copy LUT information from flash region into RAM region, because LUT update maybe corrupt read sequence(LUT[0])
     * and load wrong LUT table from FLASH region. */
    memcpy(tempCustomLUT, customLUTOctalMode, sizeof(tempCustomLUT));

    /*Get FLEXSPI default settings and configure the flexspi. */
    FLEXSPI_GetDefaultConfig(&config);

    /*Set AHB buffer size for reading data through AHB bus. */
    config.ahbConfig.enableAHBPrefetch = true;
    config.rxSampleClock               = FLEXSPI_RX_SAMPLE_CLOCK;
#if !(defined(FSL_FEATURE_FLEXSPI_HAS_NO_MCR0_COMBINATIONEN) && FSL_FEATURE_FLEXSPI_HAS_NO_MCR0_COMBINATIONEN)
    config.enableCombination = true;
#endif
    config.ahbConfig.enableAHBBufferable = true;
    config.ahbConfig.enableAHBCachable   = true;
    FLEXSPI_Init(base, &config);

    /* Configure flash settings according to serial flash feature. */
    FLEXSPI_SetFlashConfig(base, &deviceconfig, FLASH_PORT);

    /* Copy LUT information from flash region into RAM region, because flash will be reset and back to single mode;
       In lately time, LUT table assignment maybe failed after flash reset due to LUT read entry is application's
       required mode(such as octal DDR mode) and flash is being in single SDR mode, they don't matched. */
#if defined(EXAMPLE_FLASH_RESET_CONFIG)
    uint32_t TempFastReadSDRLUTCommandSeq[4];

    memcpy(TempFastReadSDRLUTCommandSeq, FastReadSDRLUTCommandSeq, sizeof(FastReadSDRLUTCommandSeq));
#endif

#if (defined(XIP_EXTERNAL_FLASH) && XIP_EXTERNAL_FLASH == 1) && (FLASH_ADESTO == 1)
    uint32_t tempLUT[4] = {0};
    uint32_t tmpFastReadSDRLUTCommandSeq[4];
    /* Exit octal mode command. */
    tempLUT[0] = FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_8PAD, 0xFF, kFLEXSPI_Command_STOP, kFLEXSPI_8PAD, 0x0);
    memcpy(tmpFastReadSDRLUTCommandSeq, FastReadSDRLUTCommandSeq, sizeof(FastReadSDRLUTCommandSeq));
#endif

    /* Update LUT table into a specific mode, such as octal SDR mode or octal DDR mode based on application's
     * requirement. */
    FLEXSPI_UpdateLUT(base, 0, tempCustomLUT, CUSTOM_LUT_LENGTH);

    /* Do software reset. */
    FLEXSPI_SoftwareReset(base);

#if (defined(XIP_EXTERNAL_FLASH) && XIP_EXTERNAL_FLASH == 1) && (FLASH_ADESTO == 1)
    status_t status;
    flexspi_transfer_t flashXfer;

    /* Update for standard mode. */
    FLEXSPI_UpdateLUT(base, 4 * NOR_CMD_LUT_SEQ_IDX_READ, tmpFastReadSDRLUTCommandSeq, 4);
    /* Update for exit octal mode. */
    FLEXSPI_UpdateLUT(base, 4 * NOR_CMD_LUT_SEQ_IDX_CONFIG, tempLUT, 4);

    /* Write enable */
    status = flexspi_nor_write_enable(base, 0, true);

    /* Back to standard SPI mode. */
    flashXfer.deviceAddress = 0;
    flashXfer.port          = FLASH_PORT;
    flashXfer.cmdType       = kFLEXSPI_Command;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_CONFIG;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    if (status == kStatus_Success)
    {
        status = flexspi_nor_wait_bus_busy(base, false);
    }
#endif

#if defined(EXAMPLE_FLASH_RESET_CONFIG)
    EXAMPLE_FLASH_RESET_CONFIG();
    /* FAST_READ4B: back to single mode and update read LUT entry into FAST_READ4B after flash reset,
           to make sure fetch code/data from flash is right. */
    FLEXSPI_UpdateLUT(base, 4 * NOR_CMD_LUT_SEQ_IDX_READ, TempFastReadSDRLUTCommandSeq, 4);
#endif

#if defined(EXAMPLE_INVALIDATE_FLEXSPI_CACHE)
    EXAMPLE_INVALIDATE_FLEXSPI_CACHE();
#endif

#if defined(CACHE_MAINTAIN) && CACHE_MAINTAIN
    flexspi_nor_enable_cache(cacheStatus);
#endif
}
