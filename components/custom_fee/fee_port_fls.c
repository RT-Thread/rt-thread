#include "fee_port.h"

fee_ret_t fee_port_init(void)
{
    return FEE_E_NOT_OK;
}

fee_ret_t fee_port_get_caps(fee_flash_caps_t *caps)
{
    (void)caps;
    return FEE_E_NOT_OK;
}

fee_ret_t fee_port_read(uint32_t addr, uint8_t *dst, uint32_t len)
{
    (void)addr;
    (void)dst;
    (void)len;
    return FEE_E_NOT_OK;
}

fee_ret_t fee_port_write(uint32_t addr, const uint8_t *src, uint32_t len)
{
    (void)addr;
    (void)src;
    (void)len;
    return FEE_E_NOT_OK;
}

fee_ret_t fee_port_erase(uint32_t addr, uint32_t len)
{
    (void)addr;
    (void)len;
    return FEE_E_NOT_OK;
}

void fee_port_mainfunction(void)
{
}

fee_status_t fee_port_get_status(void)
{
    return FEE_STATUS_UNINIT;
}

fee_job_result_t fee_port_get_job_result(void)
{
    return FEE_JOB_FAILED;
}
