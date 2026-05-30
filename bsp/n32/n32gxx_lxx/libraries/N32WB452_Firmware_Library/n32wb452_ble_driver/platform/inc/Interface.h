#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "ble_arch.h"
#include "Eif_debug.h"
#include <stdbool.h>

#define BLEINFO_ADDR        0X801C800
///Base address of Flash on system bus
#define FLASH_BASE_ADDR         (BLEINFO_ADDR)
#define FLASH_BLE_SIZE          (0x0400)


const struct rwip_eif_api *rwip_eif_get(uint8_t );
void        eif_delay_us(uint32_t);
void        eif_delay_ms(uint32_t);


void        ble_system_Init(void);
bool        wait_for_status_enable(void);


enum read_state
{
    READ_STATE_RX_START,
    READ_STATE_RX_HDR,
    READ_STATE_RX_PAYL,
    READ_STATE_RX_OUT_OF_SYNC
};

extern uint8_t read_state_flag;

struct interface_sys_tag
{
    //timer
    void        (*set_timesout)(uint32_t to);
    uint32_t    (*get_time)(void);
    void        (*enable_timer)(bool enable);

   ///flash
    void        (*flash_init)(void);
    uint8_t     (*flash_erase)( uint32_t offset, uint32_t size);
    uint8_t     (*flash_write)(uint32_t offset, uint32_t length, uint8_t *buffer);
    uint8_t     (*falsh_read)( uint32_t offset, uint32_t length, uint8_t *buffer);

   ///feature init
    void        (*user_feature_init)(void);
};
extern struct interface_sys_tag interface_sys;



void SetIPR(uint8_t num,uint8_t pri);

int32_t ble_interface_init(void);
int32_t ble_hardware_init(void);

int32_t ble_initdata_down(void);
int32_t ble_host_init(void);
int32_t ble_hardware_reinit(void);

#endif // _INTERFACE_H_

