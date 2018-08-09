#include "app_conn_params.h"

#include "app_event.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

const ble_gap_conn_params_t slow_params =
{
    .min_conn_interval = MSEC_TO_UNITS(100, UNIT_1_25_MS),
    .max_conn_interval = MSEC_TO_UNITS(200, UNIT_1_25_MS),
    .slave_latency     = 0,
    .conn_sup_timeout  = MSEC_TO_UNITS(4000, UNIT_10_MS),
};

const ble_gap_conn_params_t fast_params =
{
    .min_conn_interval = MSEC_TO_UNITS(7.5, UNIT_1_25_MS),
    .max_conn_interval = MSEC_TO_UNITS(15, UNIT_1_25_MS),
    .slave_latency     = 0,
    .conn_sup_timeout  = MSEC_TO_UNITS(2000, UNIT_10_MS),
};

static uint8_t  current_params_mode;
static uint16_t m_conn_handle;
static uint8_t is_fast_params;

static uint8_t is_conn_params_fast(ble_gap_conn_params_t *p_new_params)
{
    NRF_LOG_INFO("is_conn_params_fast ? new:%d,%d  slow:%d,%d\r\n", \
                 p_new_params->min_conn_interval, p_new_params->max_conn_interval, \
                 slow_params.min_conn_interval, slow_params.max_conn_interval);

    if (p_new_params->max_conn_interval <= slow_params.min_conn_interval)
    {
        return CONN_PARAMS_FAST;
    }
    else
    {
        return CONN_PARAMS_SLOW;
    }
}

static void app_ble_set_conn_params(uint8_t falst_slow)
{
    uint32_t err_code;
    if(m_conn_handle == BLE_CONN_HANDLE_INVALID)
    {
        return;
    }
    switch(falst_slow) 
    {
      case CONN_PARAMS_SLOW:
      {
          NRF_LOG_INFO("conn_params set slow %d %d ssssssssssss\r\n", slow_params.min_conn_interval, slow_params.max_conn_interval);
          err_code = sd_ble_gap_ppcp_set(&slow_params);
          //APP_ERROR_CHECK(err_code);
          if(err_code)
          {
              NRF_LOG_INFO("sd_ble_gap_ppcp_set fail %d\r\n", err_code);
          }
          current_params_mode = CONN_PARAMS_SLOW;
          err_code = sd_ble_gap_conn_param_update(m_conn_handle, &slow_params);
          //APP_ERROR_CHECK(err_code);
          if(err_code)
          {
              NRF_LOG_INFO("sd_ble_gap_conn_param_update fail 0x%x\r\n", err_code);
          }
      }
        break;
      
      case CONN_PARAMS_FAST:
      {
          //APP_EVENT_REMOVE_DELAY(conn_params_event_treat);
          //APP_EVENT_PUSH_DELAY(conn_params_event_treat, (void*)CONN_PARAMS_SLOW, 30000);
          NRF_LOG_INFO("conn_params set fast %d %d ffffffffffff\r\n", fast_params.min_conn_interval, fast_params.max_conn_interval);
          err_code = sd_ble_gap_ppcp_set(&fast_params);
          //APP_ERROR_CHECK(err_code);
          if(err_code)
          {
              NRF_LOG_INFO("sd_ble_gap_ppcp_set fail\r\n");
          }
          current_params_mode = CONN_PARAMS_FAST;
          err_code = sd_ble_gap_conn_param_update(m_conn_handle, &fast_params);
          //APP_ERROR_CHECK(err_code);
          if(err_code)
          {
              NRF_LOG_INFO("sd_ble_gap_conn_param_update fail\r\n");
          }
      }
        break;
      
      default:
        break;
    }
}

static void on_conn_params_update_event(ble_evt_t const * p_ble_evt)
{
    ble_gap_conn_params_t  conn_params;
  
    NRF_LOG_INFO("on_conn_params_update_event want updata to %s \r\n",((current_params_mode - 1)? "FAST": "SLOW" ));
    conn_params = p_ble_evt->evt.gap_evt.params.conn_param_update.conn_params;
    is_fast_params = is_conn_params_fast(&conn_params);
    if(is_fast_params != current_params_mode)
    {
        NRF_LOG_INFO("conn_params update %s fail xxxxxxxxxxx\r\n", ((current_params_mode - 1)? "FAST": "SLOW" ));
        // change again 
        if(current_params_mode == CONN_PARAMS_SLOW)
        {
          APP_EVENT_PUSH_DELAY(conn_params_event_treat, (void*)CONN_PARAMS_SLOW,4000);   //4s change slow 
        }
        else
        {
          APP_EVENT_PUSH_DELAY(conn_params_event_treat, (void*)CONN_PARAMS_FAST,2000);   //2s change falst           
        }
    }
    else
    {
      NRF_LOG_INFO("conn_params update %s ok *********\r\n",((current_params_mode - 1)? "FAST": "SLOW") );
    }
}

static void ble_conn_params_ble_evt_handle(ble_evt_t const * p_ble_evt, void * p_context)
{
    switch (p_ble_evt->header.evt_id)
    {
     case BLE_GAP_EVT_CONNECTED:
       {
          m_conn_handle         = p_ble_evt->evt.gap_evt.conn_handle;
          ble_gap_conn_params_t new_params = p_ble_evt->evt.gap_evt.params.connected.conn_params;
          current_params_mode   = is_conn_params_fast(&new_params);
         
          NRF_LOG_INFO("connect parame %d,%d is %s\r\n", \
                       p_ble_evt->evt.gap_evt.params.connected.conn_params.min_conn_interval, \
                       p_ble_evt->evt.gap_evt.params.connected.conn_params.max_conn_interval, \
                       (current_params_mode? "SLOW":"FAST"));
              
          if(current_params_mode == CONN_PARAMS_FAST)
          {
              APP_EVENT_REMOVE_DELAY(conn_params_event_treat);
              APP_EVENT_PUSH_DELAY(conn_params_event_treat, (void*)CONN_PARAMS_SLOW,30000);
          }
        }
        break;

     case BLE_GAP_EVT_DISCONNECTED:
        m_conn_handle = BLE_CONN_HANDLE_INVALID;
        APP_EVENT_REMOVE_DELAY(conn_params_event_treat);
        break;

     case BLE_GAP_EVT_CONN_PARAM_UPDATE:
        on_conn_params_update_event(p_ble_evt);
        break;

     default:
        break;
    }
}


uint32_t app_conn_params_init(void)
{
    uint32_t err_code;
    err_code = sd_ble_gap_ppcp_set(&fast_params);
    if(err_code)
    {
        NRF_LOG_INFO("ble_conn_params_init fast\r\n");
    }
    return NRF_SUCCESS;
}

void conn_params_event_treat(void * p_context)
{

   NRF_LOG_INFO("%s\r\n",(uint32_t)p_context ? "CONN_PARAMS_SLOW" :"CONN_PARAMS_FAST");
   app_ble_set_conn_params((uint8_t)p_context);
}

NRF_SDH_BLE_OBSERVER(m_ble_observer, BLE_CONN_PARAMS_BLE_OBSERVER_PRIO, ble_conn_params_ble_evt_handle, NULL);







