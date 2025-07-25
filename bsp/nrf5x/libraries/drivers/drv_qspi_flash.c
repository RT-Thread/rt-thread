/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-29     supperthomas first version
 *
 */
#include <stdint.h>
#include "board.h"
#include "nrfx_qspi.h"
#if defined(RT_USING_FAL)
#include <fal.h>

//log
#include <rtdbg.h>
#define LOG_TAG                "drv.qspiflash"

#define WAIT_FOR_PERIPH() do { \
        while (!m_finished) {} \
        m_finished = false;    \
    } while (0)

static volatile bool m_finished = false;
static void qspi_handler(nrfx_qspi_evt_t event, void *p_context)
{
    m_finished = true;
}

static void configure_memory()
{
#define QSPI_STD_CMD_WRSR   0x01
#define QSPI_STD_CMD_RSTEN  0x66
#define QSPI_STD_CMD_RST    0x99

    rt_uint8_t temporary = 0x40;
    rt_uint32_t err_code;
    nrf_qspi_cinstr_conf_t cinstr_cfg =
    {
        .opcode    = QSPI_STD_CMD_RSTEN,
        .length    = NRF_QSPI_CINSTR_LEN_1B,
        .io2_level = true,
        .io3_level = true,
        .wipwait   = true,
        .wren      = true
    };

    // Send reset enable
    err_code = nrfx_qspi_cinstr_xfer(&cinstr_cfg, NULL, NULL);
    if (NRFX_SUCCESS != err_code)
    {
        LOG_E("\r\n ERROR: QSPI_STD_CMD_RSTEN:0x%x\n", err_code);
        return ;
    }
    // Send reset command
    cinstr_cfg.opcode = QSPI_STD_CMD_RST;
    err_code = nrfx_qspi_cinstr_xfer(&cinstr_cfg, NULL, NULL);
    if (NRFX_SUCCESS != err_code)
    {
        LOG_E("\r\n ERROR: QSPI_STD_CMD_RST:0x%x\n", err_code);
        return ;
    }

    // Switch to qspi mode
    cinstr_cfg.opcode = QSPI_STD_CMD_WRSR;
    cinstr_cfg.length = NRF_QSPI_CINSTR_LEN_2B;
    err_code = nrfx_qspi_cinstr_xfer(&cinstr_cfg, &temporary, NULL);
    if (NRFX_SUCCESS != err_code)
    {
        LOG_E("\r\n ERROR: QSPI_STD_CMD_WRSR:0x%x\n", err_code);
        return;
    }
}
static int init(void)
{
    rt_uint32_t err_code;
    nrfx_qspi_config_t config = NRFX_QSPI_DEFAULT_CONFIG(BSP_QSPI_SCK_PIN, BSP_QSPI_CSN_PIN,
                                                         BSP_QSPI_IO0_PIN, BSP_QSPI_IO1_PIN, BSP_QSPI_IO2_PIN, BSP_QSPI_IO3_PIN);

    err_code = nrfx_qspi_init(&config, qspi_handler, NULL);
    if (NRFX_SUCCESS != err_code)
    {
        LOG_E("\r\n ERROR: QSPI_init:0x%x\n", err_code);
        return -1;
    }
    configure_memory();
    return 0;
}

static int read(long offset, rt_uint8_t *buf, rt_size_t size)
{
    rt_uint32_t err_code;
    m_finished = false;
    err_code = nrfx_qspi_read(buf, size, offset);
    WAIT_FOR_PERIPH();
    if (NRFX_SUCCESS == err_code)
    {
        return size;
    }
    else
    {
        LOG_E("\r\n ERROR: read:0x%x\n", err_code);
        return -1;
    }
}

static int write(long offset, const rt_uint8_t *buf, rt_size_t size)
{
    rt_uint32_t err_code;
    m_finished = false;
    err_code = nrfx_qspi_write(buf, size, offset);
    WAIT_FOR_PERIPH();
    if (NRFX_SUCCESS == err_code)
    {
        return size;
    }
    else
    {
        LOG_E("\r\n ERROR: write:0x%x\n", err_code);
        return -1;
    }
}

static int erase(long offset, rt_size_t size)
{
    rt_uint32_t err_code;
    m_finished = false;
    err_code = nrfx_qspi_erase(NRF_QSPI_ERASE_LEN_64KB, offset);
    WAIT_FOR_PERIPH();
    if (NRFX_SUCCESS == err_code)
    {
        return size;
    }
    else
    {
        LOG_E("\r\n ERROR: erase:0x%x\n", err_code);
        return -1;
    }
}

struct fal_flash_dev nor_flash0 =
{
    .name       = NOR_FLASH_DEV_NAME,
    .addr       = 0,
    .len        = QSPI_FLASH_SIZE_KB * 1024,
    .blk_size   = 4096,
    .ops        = {init, read, write, erase},
    .write_gran = 1
};

#endif
