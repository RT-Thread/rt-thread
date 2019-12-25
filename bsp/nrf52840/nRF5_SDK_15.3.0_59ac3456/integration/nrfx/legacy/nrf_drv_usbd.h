/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef NRF_DRV_USBD_H__
#define NRF_DRV_USBD_H__

#include "nrfx.h"
#include "nrfx_usbd.h"
#include "nrf_drv_usbd_errata.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_drv_usbd USBD driver - legacy layer
 * @{
 * @ingroup  nrf_usbd
 *
 * @brief    @tagAPI52 Layer providing compatibility with the former API.
 */

/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_DMASCHEDULER_PRIORITIZED	NRFX_USBD_DMASCHEDULER_PRIORITIZED
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_DMASCHEDULER_ROUNDROBIN  	NRFX_USBD_DMASCHEDULER_ROUNDROBIN
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EPSIZE 					NRFX_USBD_EPSIZE
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_ISOSIZE 					NRFX_USBD_ISOSIZE
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_FEEDER_BUFFER_SIZE 		NRFX_USBD_EPSIZE
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EPIN  						NRFX_USBD_EPIN
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EPOUT 						NRFX_USBD_EPOUT

/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_usbd_ep_t             nrf_drv_usbd_ep_t;
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EPOUT0			NRFX_USBD_EPOUT0
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EPOUT1			NRFX_USBD_EPOUT1
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EPOUT2			NRFX_USBD_EPOUT2
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EPOUT3			NRFX_USBD_EPOUT3
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EPOUT4			NRFX_USBD_EPOUT4
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EPOUT5			NRFX_USBD_EPOUT5
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EPOUT6			NRFX_USBD_EPOUT6
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EPOUT7			NRFX_USBD_EPOUT7
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EPOUT8			NRFX_USBD_EPOUT8
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EPIN0			NRFX_USBD_EPIN0
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EPIN1			NRFX_USBD_EPIN1
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EPIN2			NRFX_USBD_EPIN2
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EPIN3			NRFX_USBD_EPIN3
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EPIN4			NRFX_USBD_EPIN4
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EPIN5			NRFX_USBD_EPIN5
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EPIN6			NRFX_USBD_EPIN6
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EPIN7			NRFX_USBD_EPIN7
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EPIN8			NRFX_USBD_EPIN8

/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_usbd_event_type_t     nrf_drv_usbd_event_type_t;
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EVT_SOF			NRFX_USBD_EVT_SOF
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EVT_RESET			NRFX_USBD_EVT_RESET
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EVT_SUSPEND		NRFX_USBD_EVT_SUSPEND
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EVT_RESUME			NRFX_USBD_EVT_RESUME
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EVT_WUREQ			NRFX_USBD_EVT_WUREQ
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EVT_SETUP			NRFX_USBD_EVT_SETUP
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EVT_EPTRANSFER		NRFX_USBD_EVT_EPTRANSFER
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_EVT_CNT			NRFX_USBD_EVT_CNT

/** @brief Type definition for forwarding the new implementation. */
#define NRF_USBD_EP_OK		NRFX_USBD_EP_OK
/** @brief Type definition for forwarding the new implementation. */
#define NRF_USBD_EP_WAITING	NRFX_USBD_EP_WAITING
/** @brief Type definition for forwarding the new implementation. */
#define NRF_USBD_EP_OVERLOAD	NRFX_USBD_EP_OVERLOAD
/** @brief Type definition for forwarding the new implementation. */
#define NRF_USBD_EP_ABORTED	NRFX_USBD_EP_ABORTED

/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_usbd_ep_status_t      nrf_drv_usbd_ep_status_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_usbd_evt_t            nrf_drv_usbd_evt_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_usbd_event_handler_t  nrf_drv_usbd_event_handler_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_usbd_data_ptr_t       nrf_drv_usbd_data_ptr_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_usbd_ep_transfer_t    nrf_drv_usbd_ep_transfer_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_usbd_transfer_flags_t nrf_drv_usbd_transfer_flags_t;
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_TRANSFER_ZLP_FLAG	NRFX_USBD_TRANSFER_ZLP_FLAG

/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_usbd_transfer_t       nrf_drv_usbd_transfer_t;

/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_TRANSFER_IN_FLAGS(name, tx_buff, tx_size, tx_flags) \
		NRFX_USBD_TRANSFER_IN(name, tx_buff, tx_size, tx_flags)
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_TRANSFER_IN(name, tx_buff, tx_size) \
		NRFX_USBD_TRANSFER_IN(name, tx_buff, tx_size, 0)
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_TRANSFER_IN_ZLP(name, tx_buff, tx_size) \
		NRFX_USBD_TRANSFER_IN(name, tx_buff, tx_size, NRFX_USBD_TRANSFER_ZLP_FLAG)
/** @brief Type definition for forwarding the new implementation. */
#define NRF_DRV_USBD_TRANSFER_OUT 	NRFX_USBD_TRANSFER_OUT

/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_usbd_feeder_t nrf_drv_usbd_feeder_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_usbd_consumer_t nrf_drv_usbd_consumer_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_usbd_handler_t nrf_drv_usbd_handler_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_usbd_handler_desc_t nrf_drv_usbd_handler_desc_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_usbd_setup_t nrf_drv_usbd_setup_t;

/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_init					nrfx_usbd_init
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_enable					nrfx_usbd_enable
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_disable				nrfx_usbd_disable
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_start					nrfx_usbd_start
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_stop					nrfx_usbd_stop
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_is_initialized			nrfx_usbd_is_initialized
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_is_enabled				nrfx_usbd_is_enabled
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_is_started				nrfx_usbd_is_started
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_suspend				nrfx_usbd_suspend
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_wakeup_req				nrfx_usbd_wakeup_req
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_suspend_check			nrfx_usbd_suspend_check
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_suspend_irq_config		nrfx_usbd_suspend_irq_config
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_active_irq_config		nrfx_usbd_active_irq_config
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_force_bus_wakeup		nrfx_usbd_force_bus_wakeup
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_bus_suspend_check		nrfx_usbd_bus_suspend_check
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_ep_max_packet_size_set	nrfx_usbd_ep_max_packet_size_set
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_ep_max_packet_size_get	nrfx_usbd_ep_max_packet_size_get
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_ep_enable_check		nrfx_usbd_ep_enable_check
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_ep_enable				nrfx_usbd_ep_enable
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_ep_disable				nrfx_usbd_ep_disable
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_ep_default_config		nrfx_usbd_ep_default_config
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_ep_transfer			nrfx_usbd_ep_transfer
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_ep_handled_transfer	nrfx_usbd_ep_handled_transfer
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_feeder_buffer_get		nrfx_usbd_feeder_buffer_get
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_ep_status_get			nrfx_usbd_ep_status_get
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_epout_size_get			nrfx_usbd_epout_size_get
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_ep_is_busy				nrfx_usbd_ep_is_busy
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_ep_stall				nrfx_usbd_ep_stall
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_ep_stall_clear			nrfx_usbd_ep_stall_clear
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_ep_stall_check			nrfx_usbd_ep_stall_check
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_ep_dtoggle_clear		nrfx_usbd_ep_dtoggle_clear
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_setup_get				nrfx_usbd_setup_get
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_setup_data_clear		nrfx_usbd_setup_data_clear
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_setup_clear			nrfx_usbd_setup_clear
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_setup_stall			nrfx_usbd_setup_stall
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_ep_abort				nrfx_usbd_ep_abort
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_last_setup_dir_get		nrfx_usbd_last_setup_dir_get
/** @brief Type definition for forwarding the new implementation. */
#define nrf_drv_usbd_transfer_out_drop		nrfx_usbd_transfer_out_drop

/** @brief Type definition for forwarding the new implementation. */
static inline ret_code_t nrf_drv_usbd_uninit(void)
{
    nrfx_usbd_uninit();
    return NRF_SUCCESS;
}

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* NRF_DRV_USBD_H__ */
