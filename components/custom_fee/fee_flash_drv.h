#ifndef CUSTOM_FEE_FLASH_DRV_H
#define CUSTOM_FEE_FLASH_DRV_H

#include "fee_port.h"

/*
 * Board or driver-specific flash adapters may provide strong definitions for
 * these symbols. The default weak implementation lives in fee_port.c and uses
 * a RAM-backed mock flash for bring-up and QEMU testing.
 */
fee_ret_t fee_flash_driver_init(void);
fee_ret_t fee_flash_driver_get_caps(fee_flash_caps_t *caps);
fee_ret_t fee_flash_driver_read(uint32_t addr, uint8_t *dst, uint32_t len);
fee_ret_t fee_flash_driver_write(uint32_t addr, const uint8_t *src, uint32_t len);
fee_ret_t fee_flash_driver_erase(uint32_t addr, uint32_t len);
void fee_flash_driver_mainfunction(void);
fee_status_t fee_flash_driver_get_status(void);
fee_job_result_t fee_flash_driver_get_job_result(void);

#endif
