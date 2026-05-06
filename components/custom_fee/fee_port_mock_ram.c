#include "fee_port.h"
#include <string.h>

#ifndef CUSTOM_FEE_MOCK_FLASH_SIZE
#define CUSTOM_FEE_MOCK_FLASH_SIZE 0x60000U
#endif

static uint8_t g_fee_mock_flash[CUSTOM_FEE_MOCK_FLASH_SIZE];
static fee_flash_caps_t g_fee_mock_caps =
{
    CUSTOM_FEE_MOCK_FLASH_SIZE,
    1U,
    8U,
    0xE000U,
    512U,
    0U,
    0U
};
static fee_status_t g_fee_port_status = FEE_STATUS_UNINIT;
static fee_job_result_t g_fee_port_job_result = FEE_JOB_NONE;
static uint8_t g_fee_mock_initialized = 0U;

static fee_ret_t fee_port_check_range(uint32_t addr, uint32_t len)
{
    if ((addr + len) > (uint32_t)sizeof(g_fee_mock_flash))
    {
        return FEE_E_PARAM;
    }

    return FEE_E_OK;
}

static fee_ret_t fee_port_check_alignment(uint32_t addr, uint32_t len, uint32_t align)
{
    if ((align == 0U) || ((addr % align) != 0U) || ((len % align) != 0U))
    {
        return FEE_E_PARAM;
    }

    return FEE_E_OK;
}

fee_ret_t fee_port_init(void)
{
    if (g_fee_mock_initialized == 0U)
    {
        (void)memset(g_fee_mock_flash, 0xFF, sizeof(g_fee_mock_flash));
        g_fee_mock_initialized = 1U;
    }

    g_fee_port_status = FEE_STATUS_IDLE;
    g_fee_port_job_result = FEE_JOB_OK;
    return FEE_E_OK;
}

fee_ret_t fee_port_get_caps(fee_flash_caps_t *caps)
{
    if (caps == RT_NULL)
    {
        return FEE_E_PARAM;
    }

    *caps = g_fee_mock_caps;
    return FEE_E_OK;
}

fee_ret_t fee_port_read(uint32_t addr, uint8_t *dst, uint32_t len)
{
    fee_ret_t ret;

    if ((dst == RT_NULL) || (len == 0U))
    {
        return FEE_E_PARAM;
    }

    ret = fee_port_check_range(addr, len);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    ret = fee_port_check_alignment(addr, len, g_fee_mock_caps.read_unit);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    g_fee_port_status = FEE_STATUS_BUSY;
    (void)memcpy(dst, &g_fee_mock_flash[addr], len);
    g_fee_port_status = FEE_STATUS_IDLE;
    g_fee_port_job_result = FEE_JOB_OK;

    return FEE_E_OK;
}

fee_ret_t fee_port_write(uint32_t addr, const uint8_t *src, uint32_t len)
{
    fee_ret_t ret;

    if ((src == RT_NULL) || (len == 0U))
    {
        return FEE_E_PARAM;
    }

    ret = fee_port_check_range(addr, len);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    ret = fee_port_check_alignment(addr, len, g_fee_mock_caps.program_unit);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    g_fee_port_status = FEE_STATUS_BUSY;
    {
        uint32_t idx;

        for (idx = 0U; idx < len; ++idx)
        {
            g_fee_mock_flash[addr + idx] &= src[idx];
        }
    }
    g_fee_port_status = FEE_STATUS_IDLE;
    g_fee_port_job_result = FEE_JOB_OK;

    return FEE_E_OK;
}

fee_ret_t fee_port_erase(uint32_t addr, uint32_t len)
{
    fee_ret_t ret;

    if (len == 0U)
    {
        return FEE_E_PARAM;
    }

    ret = fee_port_check_range(addr, len);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    ret = fee_port_check_alignment(addr, len, g_fee_mock_caps.erase_unit);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    g_fee_port_status = FEE_STATUS_BUSY;
    (void)memset(&g_fee_mock_flash[addr], 0xFF, len);
    g_fee_port_status = FEE_STATUS_IDLE;
    g_fee_port_job_result = FEE_JOB_OK;

    return FEE_E_OK;
}

void fee_port_mainfunction(void)
{
}

fee_status_t fee_port_get_status(void)
{
    return g_fee_port_status;
}

fee_job_result_t fee_port_get_job_result(void)
{
    return g_fee_port_job_result;
}
