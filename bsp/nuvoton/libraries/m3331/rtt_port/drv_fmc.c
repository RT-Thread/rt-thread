/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Includes ------------------------------------------------------------------*/
#include "rtconfig.h"
#if defined(BSP_USING_FMC)

#include "NuMicro.h"
#include "drv_fmc.h"
#include "rtdevice.h"

/* Defines / Macros ----------------------------------------------------------*/
#undef LOG_TAG
#define LOG_TAG "drv.fmc"
#define DBG_TAG LOG_TAG
#include "drv_log.h"

#define NU_SUPPORT_NONALIGN

/* Get byte offset within a word (0, 8, 16, 24) */
#define NU_GETBYTE_OFST(addr)         (((addr) & 0x3) * 8)
/* Get word-aligned address (4-byte aligned) */
#define NU_GET_WALIGN(addr)           ((addr) & ~0x3)
/* Get double-word-aligned address (8-byte aligned) */
#define NU_GET_DWALIGN(addr)          ((addr) & ~0x7)
/* Get lowest 2 bits (for word alignment checks) */
#define NU_GET_LSB2BIT(addr)          ((addr) & 0x3)
/* Get lowest 3 bits (for double-word alignment checks) */
#define NU_GET_LSB3BIT(addr)          ((addr) & 0x7)

/* Types / Structures ---------------------------------------------------------*/

/* Static Function Prototypes ------------------------------------------------*/
#if defined(RT_USING_FAL)
    static int aprom_read(long offset, uint8_t *buf, size_t size);
    static int aprom_write(long offset, const uint8_t *buf, size_t size);
    static int aprom_erase(long offset, size_t size);

    static int ldrom_read(long offset, uint8_t *buf, size_t size);
    static int ldrom_write(long offset, const uint8_t *buf, size_t size);
    static int ldrom_erase(long offset, size_t size);

    static int dataflash_read(long offset, uint8_t *buf, size_t size);
    static int dataflash_write(long offset, const uint8_t *buf, size_t size);
    static int dataflash_erase(long offset, size_t size);
#endif  /* RT_USING_FAL */
static int nu_fmc_init(void);

/* Static Variables ----------------------------------------------------------*/
static rt_mutex_t g_mutex_fmc = RT_NULL;

#if defined(RT_USING_FAL)
const struct fal_flash_dev g_falFMC_AP =
{
    "FMC_AP",
    FMC_APROM_BASE,
    FMC_APROM_SIZE,
    FMC_FLASH_PAGE_SIZE,
    {
        NULL,
        aprom_read,
        aprom_write,
        aprom_erase
    }
};

const struct fal_flash_dev g_falFMC_LD =
{
    "FMC_LD",
    FMC_LDROM_BASE,
    FMC_LDROM_SIZE,
    FMC_FLASH_PAGE_SIZE,
    {
        NULL,
        ldrom_read,
        ldrom_write,
        ldrom_erase
    }
};

const struct fal_flash_dev g_falFMC_DF =
{
    "FMC_DF",
    FMC_DATA_FLASH_BASE,
    FMC_DATA_FLASH_SIZE,
    FMC_FLASH_PAGE_SIZE,
    {
        NULL,
        dataflash_read,
        dataflash_write,
        dataflash_erase
    }
};
#endif  /* RT_USING_FAL */

/* Functions Implementation --------------------------------------------------*/

/**
 * @brief  Read data from FMC flash memory.
 * @param  addr: Start address to read from
 * @param  buf:  Buffer to store read data
 * @param  size: Number of bytes to read
 * @return Number of bytes actually read
 */
int nu_fmc_read(long addr, uint8_t *buf, size_t size)
{
    size_t read_size = 0;
    uint32_t addr_end = addr + size;
    uint32_t isp_rdata = 0;
    rt_mutex_take(g_mutex_fmc, RT_WAITING_FOREVER);

    // If address is not word-aligned, read the aligned word first
    if (NU_GET_LSB2BIT(addr))
        isp_rdata = FMC_Read(NU_GET_WALIGN(addr));

    for (; addr < addr_end;)
    {
        if (NU_GET_LSB2BIT(addr) == 0)
        {
            isp_rdata = FMC_Read(addr);
            if (addr_end - addr >= 4)
            {
                *(uint32_t *)buf = isp_rdata;
                addr += 4;
                buf += 4;
                read_size += 4;
                continue;
            }
        }
        *buf = (uint8_t)(isp_rdata >> NU_GETBYTE_OFST(addr));
        addr++;
        buf++;
        read_size++;
    }

    rt_mutex_release(g_mutex_fmc);
    return read_size;
}

/**
 * @brief  Write data to FMC flash memory.
 * @param  addr: Start address to write to
 * @param  buf:  Buffer containing data to write
 * @param  size: Number of bytes to write
 * @return Number of bytes actually written
 */
int nu_fmc_write(long addr, const uint8_t *buf, size_t size)
{
    size_t write_size = 0;
    uint32_t addr_end = addr + size;
    uint64_t isp_rdata = 0;

    rt_mutex_take(g_mutex_fmc, RT_WAITING_FOREVER);

    // Enable APROM, LDROM or DATAFLASH update depending on address
    if (addr < FMC_APROM_END)
        FMC_ENABLE_AP_UPDATE();
    else if ((addr < FMC_LDROM_END) && addr >= FMC_LDROM_BASE)
        FMC_ENABLE_LD_UPDATE();
    else if ((addr < FMC_DATA_FLASH_END) && addr >= FMC_DATA_FLASH_BASE)
        FMC_ENABLE_DF_UPDATE();
    else
        goto Exit2;

    // If address is not dword-aligned, read the aligned dword first
    if (NU_GET_LSB3BIT(addr))
    {
        FMC_Read64(NU_GET_DWALIGN(addr), &isp_rdata);
    }

    for (; addr < addr_end;)
    {
        if ((addr_end - addr >= 8) && (NU_GET_LSB3BIT(addr) == 0))
        {
            FMC_Write64(addr, *((uint64_t *)buf));
            addr += 8;
            buf += 8;
            write_size += 8;
            continue;
        }

        if (NU_GET_LSB3BIT(addr) == 0)
        {
            FMC_Read64(NU_GET_DWALIGN(addr), &isp_rdata);
        }

        int byte_ofs = addr & 0x7;
        isp_rdata = (isp_rdata & ~((uint64_t)0xFF << (byte_ofs * 8))) |
                    ((uint64_t)(*buf) << (byte_ofs * 8));

        if (NU_GET_LSB3BIT(addr) == 0x7)
        {
            FMC_Write64(NU_GET_DWALIGN(addr), isp_rdata);
        }

        addr ++;
        buf++;
        write_size++;
    }
    if (NU_GET_LSB3BIT(addr))
        FMC_Write64(NU_GET_DWALIGN(addr), isp_rdata);

    FMC_DISABLE_AP_UPDATE();
    FMC_DISABLE_LD_UPDATE();
    FMC_DISABLE_DF_UPDATE();

Exit2:

    rt_mutex_release(g_mutex_fmc);
    return write_size;
}

/**
 * @brief  Erase flash memory region.
 * @param  addr: Start address to erase
 * @param  size: Number of bytes to erase
 * @return Number of bytes actually erased
 */
int nu_fmc_erase(long addr, size_t size)
{
    size_t erased_size = 0;
    uint32_t addrptr;
    uint32_t addr_end = addr + size;
#if defined(NU_SUPPORT_NONALIGN)
    uint8_t *page_sdtemp = RT_NULL;
    uint8_t *page_edtemp = RT_NULL;

    // Save data before the first page boundary if not aligned
    addrptr = addr & (FMC_FLASH_PAGE_SIZE - 1);
    if (addrptr)
    {
        page_sdtemp = rt_malloc(addrptr);
        if (page_sdtemp == RT_NULL)
        {
            erased_size = 0;
            goto Exit3;
        }
        if (nu_fmc_read(addr & ~(FMC_FLASH_PAGE_SIZE - 1), page_sdtemp, addrptr) != addrptr)
        {
            erased_size = 0;
            goto Exit3;
        }
    }
    addrptr = addr_end & (FMC_FLASH_PAGE_SIZE - 1);
    if (addrptr)
    {
        page_edtemp = rt_malloc(FMC_FLASH_PAGE_SIZE - addrptr);
        if (page_edtemp == RT_NULL)
        {
            erased_size = 0;
            goto Exit3;
        }
        if (nu_fmc_read(addr_end, page_edtemp, FMC_FLASH_PAGE_SIZE - addrptr) != FMC_FLASH_PAGE_SIZE - addrptr)
        {
            erased_size = 0;
            goto Exit3;
        }
    }
#endif

    rt_mutex_take(g_mutex_fmc, RT_WAITING_FOREVER);

    // Enable APROM, LDROM or DATAFLASH update depending on address
    if (addr <= FMC_APROM_END)
        FMC_ENABLE_AP_UPDATE();
    else if ((addr < FMC_LDROM_END) && addr >= FMC_LDROM_BASE)
        FMC_ENABLE_LD_UPDATE();
    else if ((addr < FMC_DATA_FLASH_END) && addr >= FMC_DATA_FLASH_BASE)
        FMC_ENABLE_DF_UPDATE();
    else
        goto Exit2;

    // Erase each page in the region
    addrptr = (addr & ~(FMC_FLASH_PAGE_SIZE - 1));
    while (addrptr < addr_end)
    {
        if (FMC_Erase(addrptr) != RT_EOK)
            goto Exit1;
        erased_size += FMC_FLASH_PAGE_SIZE;
        addrptr += FMC_FLASH_PAGE_SIZE;
    }

Exit1:

    FMC_DISABLE_AP_UPDATE();
    FMC_DISABLE_LD_UPDATE();

Exit2:

    rt_mutex_release(g_mutex_fmc);
#if defined(NU_SUPPORT_NONALIGN)
    // Restore saved data if needed
    if (erased_size >= size)
    {
        addrptr = addr & (FMC_FLASH_PAGE_SIZE - 1);
        if (addrptr)
        {
            if (nu_fmc_write(addr & ~(FMC_FLASH_PAGE_SIZE - 1), page_sdtemp, addrptr) != addrptr)
                goto Exit3;
            erased_size += addrptr;
        }
        addrptr = addr_end & (FMC_FLASH_PAGE_SIZE - 1);
        if (addrptr)
        {
            if (nu_fmc_write(addr_end, page_edtemp, FMC_FLASH_PAGE_SIZE - addrptr) != FMC_FLASH_PAGE_SIZE - addrptr)
                goto Exit3;
            erased_size += FMC_FLASH_PAGE_SIZE - addrptr;
        }
    }
    else
        erased_size = 0;

Exit3:
    if (page_sdtemp != RT_NULL)
        rt_free(page_sdtemp);
    if (page_edtemp != RT_NULL)
        rt_free(page_edtemp);
#endif
    return erased_size;
}
#if defined(RT_USING_FAL)

static int aprom_read(long offset, uint8_t *buf, size_t size)
{
    return nu_fmc_read(g_falFMC_AP.addr + offset, buf, size);
}

static int aprom_write(long offset, const uint8_t *buf, size_t size)
{
    return nu_fmc_write(g_falFMC_AP.addr + offset, buf, size);
}

static int aprom_erase(long offset, size_t size)
{
    return nu_fmc_erase(g_falFMC_AP.addr + offset, size);
}

static int ldrom_read(long offset, uint8_t *buf, size_t size)
{
    return nu_fmc_read(g_falFMC_LD.addr + offset, buf, size);
}

static int ldrom_write(long offset, const uint8_t *buf, size_t size)
{
    return nu_fmc_write(g_falFMC_LD.addr + offset, buf, size);
}

static int ldrom_erase(long offset, size_t size)
{
    return nu_fmc_erase(g_falFMC_LD.addr + offset, size);
}

static int dataflash_read(long offset, uint8_t *buf, size_t size)
{
    return nu_fmc_read(g_falFMC_DF.addr + offset, buf, size);
}

static int dataflash_write(long offset, const uint8_t *buf, size_t size)
{
    return nu_fmc_write(g_falFMC_DF.addr + offset, buf, size);
}

static int dataflash_erase(long offset, size_t size)
{
    return nu_fmc_erase(g_falFMC_DF.addr + offset, size);
}
#endif /* RT_USING_FAL */

static int nu_fmc_init(void)
{
    FMC_ENABLE_ISP();

    g_mutex_fmc = rt_mutex_create("nu_fmc_lock", RT_IPC_FLAG_PRIO);
    RT_ASSERT(g_mutex_fmc);

#if defined(RT_USING_FAL)
    /* RT_USING_FAL */
    extern int fal_init_check(void);
    if (!fal_init_check())
        fal_init();
#endif

    return (int)RT_EOK;
}

INIT_APP_EXPORT(nu_fmc_init);

#endif //#if defined(BSP_USING_FMC)
