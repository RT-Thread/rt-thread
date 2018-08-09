#ifndef APP_BLE_INIT_H__
#define APP_BLE_INIT_H__
#include "app_common.h"

extern uint16_t curren_mtu;
uint16_t current_conn_handle(void);
void app_ble_ant_init(void);
void power_manage(void);
extern const ble_advertising_t * p_m_advertising;
void advertising_start(bool erase_bonds);
#endif










