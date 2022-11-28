#ifndef SUNXI_HAL_SPINOR_H
#define SUNXI_HAL_SPINOR_H

#include <stdint.h>
#include <sunxi_hal_common.h>
#include <sunxi_hal_spi.h>
#include <hal_sem.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SUNXI_HAL_SPINOR_API_VERSION 1
#define SUNXI_HAL_SPINOR_DRV_VERSION 0

typedef enum sunxi_hal_spinor_signal_event
{
    ARM_FLASH_EVENT_READY = (1UL << 0),
    ARM_FLASH_EVENT_ERROR = (1UL << 1),
} sunxi_hal_spinor_signal_event_t;

typedef struct sunxi_hal_spinor_status
{
    uint32_t busy:  1;
    uint32_t error: 1;
    uint32_t reserved: 30;
} sunxi_hal_spinor_status_t;

typedef struct _sunxi_hal_spinor_sector_info
{
    uint32_t start;
    uint32_t end;
} sunxi_hal_spinor_sector_info;

typedef struct _sunxi_hal_spinor_info
{
    sunxi_hal_spinor_sector_info *sector_info;
    uint32_t sector_count;
    uint32_t sector_size;
    uint32_t page_size;
    uint32_t program_unit;
    uint8_t  erased_value;
    uint8_t  reserved[3];
} sunxi_hal_spinor_info;

typedef struct sunxi_hal_spinor_capabilities
{
    uint32_t event_ready: 1;
    uint32_t data_width: 2;
    uint32_t erase_chip: 1;
    uint32_t reserved: 28;
} sunxi_hal_spinor_capabilities_t;

int32_t hal_spinor_init(sunxi_hal_spinor_signal_event_t cb_event);
int32_t hal_spinor_deinit(void);
sunxi_hal_version_t hal_spinor_get_version(int32_t dev);
sunxi_hal_spinor_capabilities_t hal_spinor_get_capabilities(void);
sunxi_hal_spinor_status_t hal_spinor_get_status(void);
int32_t hal_spinor_power_control(sunxi_hal_power_state_e state);
int32_t hal_spinor_read_data(uint32_t addr, void *buf, uint32_t cnt);
int32_t hal_spinor_program_data(uint32_t addr, const void *buf, uint32_t cnt);
int32_t hal_spinor_erase_sector(uint32_t addr, uint32_t size);
int32_t hal_spinor_erase_chip(void);
int32_t hal_spinor_sync(void);
sunxi_hal_spinor_info *hal_spinor_get_info(void);
void hal_spinor_signal_event(uint32_t event);
int32_t hal_spinor_control(int32_t dev, uint32_t command, uint32_t arg);

#ifdef __cplusplus
}
#endif

#endif  /*SUNXI_HAL_SPINOR_H*/
