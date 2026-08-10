/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>

#ifdef BSP_USING_QSPI_PSRAM
#include <stdint.h>
#include "hal_data.h"
#include "r_qspi_w.h"

#define RA6W1_QSPI_PSRAM_SZ_1K             (1024U)
#define RA6W1_QSPI_PSRAM_SZ_1M             (RA6W1_QSPI_PSRAM_SZ_1K * RA6W1_QSPI_PSRAM_SZ_1K)

#define QSPI_RAM_COMMAND_ENTER_QPI_MODE    (0x35U)
#define QSPI_RAM_COMMAND_EXIT_QPI_MODE     (0xF5U)
#define QSPI_RAM_COMMAND_READ_ID           (0x9FU)
#define QSPI_RAM_COMMAND_RESET_ENABLE      (0x66U)
#define QSPI_RAM_COMMAND_RESET             (0x99U)
#define RA6W1_QSPI_PSRAM_ID_LENGTH         (9U)

#define RA6W1_QSPI_PSRAM_DEFAULT_SIZE      (8U * RA6W1_QSPI_PSRAM_SZ_1M)
#define RA6W1_QSPI_PSRAM_MEMHEAP_NAME      "psram"

struct ra6w1_qspi_psram_density
{
    rt_uint32_t mbits;
    rt_size_t bytes;
    const char *name;
};

static const struct ra6w1_qspi_psram_density s_qspi_psram_density[] =
{
    {16U,  2U  * RA6W1_QSPI_PSRAM_SZ_1M, "16Mbit/2MiB"},
    {32U,  4U  * RA6W1_QSPI_PSRAM_SZ_1M, "32Mbit/4MiB"},
    {64U,  8U  * RA6W1_QSPI_PSRAM_SZ_1M, "64Mbit/8MiB"},
};

static rt_bool_t s_qspi_psram_opened = RT_FALSE;
static rt_bool_t s_qspi_psram_initialized = RT_FALSE;
static rt_size_t s_qspi_psram_size = RA6W1_QSPI_PSRAM_DEFAULT_SIZE;

#ifdef RT_USING_MEMHEAP
static struct rt_memheap s_qspi_psram_memheap;
static rt_bool_t s_qspi_psram_memheap_initialized = RT_FALSE;
#endif

static rt_err_t ra6w1_fsp_to_rt_err(fsp_err_t err)
{
    if ((FSP_SUCCESS == err) || (FSP_ERR_ALREADY_OPEN == err))
        return RT_EOK;
    return -RT_ERROR;
}

static rt_err_t ra6w1_qspi_psram_open(void)
{
    fsp_err_t err;
    if (s_qspi_psram_opened) return RT_EOK;
    err = R_QSPI_W_Open(&g_qspi_ram0_ctrl, &g_qspi_ram0_cfg);
    if ((FSP_SUCCESS != err) && (FSP_ERR_ALREADY_OPEN != err))
    {
        rt_kprintf("[qspi] open failed: %d\n", (int)err);
        return ra6w1_fsp_to_rt_err(err);
    }
    s_qspi_psram_opened = RT_TRUE;
    return RT_EOK;
}

static rt_err_t ra6w1_qspi_psram_set_protocol(spi_flash_protocol_t protocol)
{
    fsp_err_t err;

    err = R_QSPI_W_SpiProtocolSet(&g_qspi_ram0_ctrl, protocol);
    if (FSP_SUCCESS != err)
    {
        rt_kprintf("[qspi] protocol set failed: %d\n", (int)err);
        return ra6w1_fsp_to_rt_err(err);
    }

    return RT_EOK;
}

static rt_err_t ra6w1_qspi_psram_exit_qpi_mode(void)
{
    fsp_err_t err;
    uint8_t cmd = QSPI_RAM_COMMAND_EXIT_QPI_MODE;

    if (RT_EOK != ra6w1_qspi_psram_set_protocol(SPI_FLASH_PROTOCOL_QPI))
        return -RT_ERROR;

    err = R_QSPI_W_DirectWrite(&g_qspi_ram0_ctrl, &cmd, 1, false);
    if (FSP_SUCCESS != err) return ra6w1_fsp_to_rt_err(err);

    return ra6w1_qspi_psram_set_protocol(SPI_FLASH_PROTOCOL_EXTENDED_SPI);
}

static rt_err_t ra6w1_qspi_psram_reset(void)
{
    fsp_err_t err;
    uint8_t cmd = QSPI_RAM_COMMAND_RESET_ENABLE;

    /* A CPU-only reset can leave the external PSRAM in QPI mode. Exit QPI first so SPI reset/read-ID work. */
    (void)ra6w1_qspi_psram_exit_qpi_mode();

    if (RT_EOK != ra6w1_qspi_psram_set_protocol(SPI_FLASH_PROTOCOL_EXTENDED_SPI))
        return -RT_ERROR;

    err = R_QSPI_W_DirectWrite(&g_qspi_ram0_ctrl, &cmd, 1, false);
    if (FSP_SUCCESS != err) return ra6w1_fsp_to_rt_err(err);

    cmd = QSPI_RAM_COMMAND_RESET;
    err = R_QSPI_W_DirectWrite(&g_qspi_ram0_ctrl, &cmd, 1, false);
    if (FSP_SUCCESS != err) return ra6w1_fsp_to_rt_err(err);

    s_qspi_psram_initialized = RT_FALSE;
    return RT_EOK;
}

static rt_err_t ra6w1_qspi_psram_read_id(rt_uint8_t id[RA6W1_QSPI_PSRAM_ID_LENGTH])
{
    fsp_err_t err;
    rt_uint8_t cmd[4] = {QSPI_RAM_COMMAND_READ_ID, 0, 0, 0};

    err = R_QSPI_W_DirectWrite(&g_qspi_ram0_ctrl, cmd, sizeof(cmd), true);
    if (FSP_SUCCESS != err) return ra6w1_fsp_to_rt_err(err);

    err = R_QSPI_W_DirectRead(&g_qspi_ram0_ctrl, id, RA6W1_QSPI_PSRAM_ID_LENGTH);
    if (FSP_SUCCESS != err) return ra6w1_fsp_to_rt_err(err);

    return RT_EOK;
}

static void ra6w1_qspi_psram_update_size_from_id(const rt_uint8_t id[RA6W1_QSPI_PSRAM_ID_LENGTH])
{
    rt_uint8_t density = id[2] >> 5;

    rt_kprintf("[qspi] id:");
    for (rt_uint32_t i = 0; i < RA6W1_QSPI_PSRAM_ID_LENGTH; i++)
    {
        rt_kprintf(" %02x", id[i]);
    }
    rt_kprintf("\n");

    if (0x5DU != id[1])
    {
        rt_kprintf("[qspi] warning: KGD=0x%02x, keep default size %lu bytes\n",
                   id[1],
                   (unsigned long)s_qspi_psram_size);
        return;
    }

    if (density < (sizeof(s_qspi_psram_density) / sizeof(s_qspi_psram_density[0])))
    {
        s_qspi_psram_size = s_qspi_psram_density[density].bytes;
        rt_kprintf("[qspi] density=%s\n", s_qspi_psram_density[density].name);
    }
    else
    {
        rt_kprintf("[qspi] warning: unknown density index %u, keep default size %lu bytes\n",
                   density,
                   (unsigned long)s_qspi_psram_size);
    }
}

static rt_err_t ra6w1_qspi_psram_enter_qpi(void)
{
    fsp_err_t err;
    uint8_t cmd = QSPI_RAM_COMMAND_ENTER_QPI_MODE;

    err = R_QSPI_W_DirectWrite(&g_qspi_ram0_ctrl, &cmd, 1, false);
    if (FSP_SUCCESS != err) return ra6w1_fsp_to_rt_err(err);

    return ra6w1_qspi_psram_set_protocol(SPI_FLASH_PROTOCOL_QPI);
}

rt_err_t ra6w1_qspi_psram_init(void)
{
    rt_err_t ret;
    rt_uint8_t id[RA6W1_QSPI_PSRAM_ID_LENGTH];

    if (s_qspi_psram_initialized) return RT_EOK;

    ret = ra6w1_qspi_psram_open();
    if (RT_EOK != ret) return ret;

    ret = ra6w1_qspi_psram_reset();
    if (RT_EOK != ret) return ret;

    if (RT_EOK == ra6w1_qspi_psram_read_id(id))
    {
        ra6w1_qspi_psram_update_size_from_id(id);
    }
    else
    {
        rt_kprintf("[qspi] warning: read id failed, keep default size %lu bytes\n",
                   (unsigned long)s_qspi_psram_size);
    }

    ret = ra6w1_qspi_psram_enter_qpi();
    if (RT_EOK != ret)
    {
        rt_kprintf("[qspi] enter QPI failed: %d\n", (int)ret);
        return ret;
    }

    s_qspi_psram_initialized = RT_TRUE;
    rt_kprintf("[qspi] PSRAM ready, QPI 4-4-4 mode, size=%lu base=0x%08x\n",
               (unsigned long)s_qspi_psram_size,
               (unsigned)(uintptr_t)QSPI_W_DEVICE_START_ADDRESS);
    return RT_EOK;
}

void *ra6w1_qspi_psram_base(void)
{
    return (void *)QSPI_W_DEVICE_START_ADDRESS;
}

rt_size_t ra6w1_qspi_psram_size(void)
{
    return s_qspi_psram_size;
}

#ifdef RT_USING_MEMHEAP
rt_err_t ra6w1_qspi_psram_memheap_init(void)
{
    rt_err_t ret;

    if (s_qspi_psram_memheap_initialized) return RT_EOK;

    ret = ra6w1_qspi_psram_init();
    if (RT_EOK != ret) return ret;

    ret = rt_memheap_init(&s_qspi_psram_memheap,
                          RA6W1_QSPI_PSRAM_MEMHEAP_NAME,
                          (void *)QSPI_W_DEVICE_START_ADDRESS,
                          s_qspi_psram_size);
    if (RT_EOK != ret)
    {
        rt_kprintf("[qspi] PSRAM memheap init failed: %d\n", (int)ret);
        return ret;
    }

    s_qspi_psram_memheap_initialized = RT_TRUE;
    rt_kprintf("[qspi] PSRAM memheap ready, name=%s total=%lu available=%lu\n",
               RA6W1_QSPI_PSRAM_MEMHEAP_NAME,
               (unsigned long)s_qspi_psram_memheap.pool_size,
               (unsigned long)s_qspi_psram_memheap.available_size);

    return RT_EOK;
}

static int ra6w1_qspi_psram_memheap_auto_init(void)
{
    return (int)ra6w1_qspi_psram_memheap_init();
}
INIT_COMPONENT_EXPORT(ra6w1_qspi_psram_memheap_auto_init);

struct rt_memheap *ra6w1_qspi_psram_memheap(void)
{
    if (RT_EOK != ra6w1_qspi_psram_memheap_init()) return RT_NULL;

    return &s_qspi_psram_memheap;
}
#endif

#endif /* BSP_USING_QSPI_PSRAM */
