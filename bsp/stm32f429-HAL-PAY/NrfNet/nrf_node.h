#ifndef __NRF_NODE_H__
#include <nrf_bsp.h>

void nrf_get_nodestatus(NODESTATUS* nodestatus);
void nrf_reg_callback(on_connect_callback_t on_conn_cb, on_disconnect_callback_t on_disconn_cb,
	send_callback_t on_send_cb, recv_callback_t on_recv_cb);
void nrf_reset(void);
void nrf_send_data(rt_uint8_t addr, void *data);//data³¤¶ÈÎª£ºPAYLOAD_DATA_LEN

#endif
