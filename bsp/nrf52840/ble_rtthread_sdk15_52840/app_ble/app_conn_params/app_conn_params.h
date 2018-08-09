#ifndef APP_CONN_PARAMS_H__
#define APP_CONN_PARAMS_H__

#include <rtthread.h>
#include "nordic_common.h"
#include "nrf.h"
#include "ble_hci.h"
#include "ble_advdata.h"
#include "ble_advertising.h"
#include "ble_conn_params.h"
#include "nrf_sdh.h"
#include "nrf_sdh_soc.h"
#include "nrf_sdh_ble.h"
#include "nrf_ble_gatt.h"
#include "nrf_ble_qwr.h"
#ifdef __cplusplus
extern "C" {
#endif


#define CONN_PARAMS_FAST         0
#define CONN_PARAMS_SLOW         1

uint32_t app_conn_params_init(void);
void conn_params_event_treat(void * p_context);
#ifdef __cplusplus
}
#endif

#endif // BLE_CONN_PARAMS_H__

/** @} */
