/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-3-03       FYChou       First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_FMC)
#include <rtdevice.h>
#include "NuMicro.h"

#if defined(PKG_USING_FAL)
    #include <fal.h>
#endif

/* Private define ---------------------------------------------------------------*/
#define NU_GETBYTE_OFST(addr)         (((addr)&0x3)*8)
#define NU_GET_WALIGN(addr)           ((addr)&~0x3)
#define NU_GET_LSB2BIT(addr)          ((addr)&0x3)
/* Private typedef --------------------------------------------------------------*/

/* Private functions ------------------------------------------------------------*/
static int nu_fmc_init(void);
#if defined(PKG_USING_FAL)
    static int aprom_read(long offset, uint8_t *buf, size_t size);
    static int aprom_write(long offset, const uint8_t *buf, size_t size);
    static int aprom_erase(long offset, size_t size);

    static int ldrom_read(long offset, uint8_t *buf, size_t size);
    static int ldrom_write(long offset, const uint8_t *buf, size_t size);
    static int ldrom_erase(long offset, size_t size);
#endif  /* PKG_USING_FAL */

/* Public functions -------------------------------------------------------------*/
int nu_fmc_read(long offset, uint8_t *buf, size_t size);
int nu_fmc_write(long offset, const uint8_t *buf, size_t size);
int nu_fmc_erase(long offset, size_t size);

/* Private variables ------------------------------------------------------------*/
static rt_mutex_t g_mutex_fmc = RT_NULL;

/* Public variables -------------------------------------------------------------*/
#if defined(PKG_USING_FAL)
const struct fal_flash_dev Onchip_aprom_flash = { "OnChip_APROM", FMC_APROM_BASE, FMC_APROM_END, FMC_FLASH_PAGE_SIZE, {NULL, aprom_read, aprom_write, aprom_erase} };
const struct fal_flash_dev Onchip_ldrom_flash = { "OnChip_LDROM", FMC_LDROM_BASE, FMC_LDROM_END, FMC_FLASH_PAGE_SIZE, {NULL, ldrom_read, ldrom_write, ldrom_erase} };
#endif  /* PKG_USING_FAL */

int nu_fmc_read(long addr, uint8_t *buf, size_t size)
{
    rt_err_t result;

    size_t read_size = 0;
    uint32_t addr_end = addr + size;
    uint32_t isp_rdata = 0;

    result = rt_mutex_take(g_mutex_fmc, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    SYS_UnlockReg();

    if (NU_GET_LSB2BIT(addr))
        isp_rdata = FMC_Read(NU_GET_WALIGN(addr));


    for (; addr < addr_end ;)
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

        *buf = isp_rdata >> NU_GETBYTE_OFST(addr);
        addr++;
        buf++;
        read_size++;

    }

    SYS_LockReg();

    result = rt_mutex_release(g_mutex_fmc);
    RT_ASSERT(result == RT_EOK);

    return read_size;
}

int nu_fmc_write(long addr, const uint8_t *buf, size_t size)
{
    size_t write_size = 0;
    uint32_t addr_end = addr + size;
    uint32_t isp_rdata = 0;
    rt_err_t result;

    result = rt_mutex_take(g_mutex_fmc, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    SYS_UnlockReg();

    if (addr < FMC_APROM_END)
        FMC_ENABLE_AP_UPDATE();
    else if ((addr < FMC_LDROM_END) && addr >= FMC_LDROM_BASE)
        FMC_ENABLE_LD_UPDATE();
    else
    {
        goto Exit2;
    }

    if (NU_GET_LSB2BIT(addr))
        isp_rdata = FMC_Read(NU_GET_WALIGN(addr));

    for (; addr < addr_end ;)
    {

        if (addr_end - addr >= 4 && NU_GET_LSB2BIT(addr) == 0)
        {
            FMC_Write(addr, *((uint32_t *)buf));
            addr += 4;
            buf += 4;
            write_size += 4;
            continue;
        }

        if ((NU_GET_LSB2BIT(addr)) == 0x0)
            isp_rdata = FMC_Read(NU_GET_WALIGN(addr));

        isp_rdata = (isp_rdata & ~(0xFF << NU_GETBYTE_OFST(addr))) | ((*buf) << NU_GETBYTE_OFST(addr));

        if ((NU_GET_LSB2BIT(addr)) == 0x3)
            FMC_Write(NU_GET_WALIGN(addr), isp_rdata);

        addr++;
        buf++;
        write_size++;

    }

    if (NU_GET_LSB2BIT(addr))
        FMC_Write(NU_GET_WALIGN(addr), isp_rdata);

    FMC_DISABLE_AP_UPDATE();
    FMC_DISABLE_LD_UPDATE();

Exit2:
    SYS_LockReg();

    result = rt_mutex_release(g_mutex_fmc);
    RT_ASSERT(result == RT_EOK);

    return write_size;

}

int nu_fmc_erase(long addr, size_t size)
{
    size_t erased_size = 0;
    uint32_t addrptr;
    uint32_t addr_end = addr + size;
    rt_err_t result;

#if defined(NU_SUPPORT_NONALIGN)
    uint8_t *page_sdtemp = RT_NULL;
    uint8_t *page_edtemp = RT_NULL;

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

    result = rt_mutex_take(g_mutex_fmc, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    SYS_UnlockReg();

    if (addr <= FMC_APROM_END)
        FMC_ENABLE_AP_UPDATE();
    else if ((addr < FMC_LDROM_END) && addr >= FMC_LDROM_BASE)
        FMC_ENABLE_LD_UPDATE();
    else
    {
        goto Exit2;
    }

    addrptr = (addr & ~(FMC_FLASH_PAGE_SIZE - 1));
    while (addrptr < addr_end)
    {
        if (FMC_Erase(addrptr) != RT_EOK)
        {
            goto Exit1;
        }
        erased_size += FMC_FLASH_PAGE_SIZE;
        addrptr += FMC_FLASH_PAGE_SIZE;
    }

Exit1:
    FMC_DISABLE_AP_UPDATE();
    FMC_DISABLE_LD_UPDATE();
Exit2:
    SYS_LockReg();

    result = rt_mutex_release(g_mutex_fmc);
    RT_ASSERT(result == RT_EOK);

#if defined(NU_SUPPORT_NONALIGN)

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

#if defined(PKG_USING_FAL)

static int aprom_read(long offset, uint8_t *buf, size_t size)
{
    return nu_fmc_read(Onchip_aprom_flash.addr + offset, buf, size);
}

static int aprom_write(long offset, const uint8_t *buf, size_t size)
{
    return nu_fmc_write(Onchip_aprom_flash.addr + offset, buf, size);
}

static int aprom_erase(long offset, size_t size)
{
    return nu_fmc_erase(Onchip_aprom_flash.addr + offset, size);
}

static int ldrom_read(long offset, uint8_t *buf, size_t size)
{
    return nu_fmc_read(Onchip_ldrom_flash.addr + offset, buf, size);
}

static int ldrom_write(long offset, const uint8_t *buf, size_t size)
{
    return nu_fmc_write(Onchip_ldrom_flash.addr + offset, buf, size);
}

static int ldrom_erase(long offset, size_t size)
{
    return nu_fmc_erase(Onchip_ldrom_flash.addr + offset, size);
}

#endif /* PKG_USING_FAL */

static int nu_fmc_init(void)
{
    SYS_UnlockReg();
    FMC_ENABLE_ISP();
    SYS_LockReg();

    g_mutex_fmc = rt_mutex_create("nu_fmc_lock", RT_IPC_FLAG_FIFO);
    RT_ASSERT(g_mutex_fmc != RT_NULL);

    /* PKG_USING_FAL */
#if defined(PKG_USING_FAL)
    fal_init();
#endif

    return (int)RT_EOK;
}
INIT_APP_EXPORT(nu_fmc_init);

#endif /* BSP_USING_FMC */
