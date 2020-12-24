#ifndef __DRV_FLASH_H__
#define __DRV_FLASH_H__

#ifdef BSP_USING_ONCHIP_FLASH

#include <gd32f10x.h>
#include "gd32f10x_fmc.h"

int32_t gd32_flash_read(uint32_t addr, uint8_t *buf, size_t size);

int32_t gd32_flash_write(uint32_t addr, const uint8_t *buf, size_t size);

int32_t gd32_flash_erase(uint32_t addr, size_t size);

#endif

#endif
