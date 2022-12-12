
/**
 * \file
 *
 * \brief SAM Serial Communication Interface
 *
 * Copyright (c) 2016-2019 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#include <compiler.h>
#include <hpl_usart_async.h>
#include <hpl_usart_config.h>
#include <hpl_usart_sync.h>
#include <peripheral_clk_config.h>
#include <utils.h>
#include <utils_assert.h>

#ifndef US_MR_SYNC_Pos
#define US_MR_SYNC_Pos 8
#endif
#ifndef US_MR_MSBF_Pos
#define US_MR_MSBF_Pos 16
#endif
#ifndef US_MR_MODE9_Pos
#define US_MR_MODE9_Pos 17
#endif
#ifndef US_MR_CLKO_Pos
#define US_MR_CLKO_Pos 18
#endif
#ifndef US_MR_OVER_Pos
#define US_MR_OVER_Pos 19
#endif
#ifndef US_MR_INACK_Pos
#define US_MR_INACK_Pos 20
#endif
#ifndef US_MR_DSNACK_Pos
#define US_MR_DSNACK_Pos 21
#endif
#ifndef US_MR_VAR_SYNC_Pos
#define US_MR_VAR_SYNC_Pos 22
#endif
#ifndef US_MR_INVDATA_Pos
#define US_MR_INVDATA_Pos 23
#endif
#ifndef US_MR_FILTER_Pos
#define US_MR_FILTER_Pos 28
#endif
#ifndef US_MR_MAN_Pos
#define US_MR_MAN_Pos 29
#endif
#ifndef US_MR_MODSYNC_Pos
#define US_MR_MODSYNC_Pos 30
#endif
#ifndef US_MR_ONEBIT_Pos
#define US_MR_ONEBIT_Pos 31
#endif

#ifndef CONF_USART_0_ENABLE
#define CONF_USART_0_ENABLE 0
#endif
#ifndef CONF_USART_1_ENABLE
#define CONF_USART_1_ENABLE 0
#endif
#ifndef CONF_USART_2_ENABLE
#define CONF_USART_2_ENABLE 0
#endif

/** Amount of USART. */
#define USART_AMOUNT (CONF_USART_0_ENABLE + CONF_USART_1_ENABLE + CONF_USART_2_ENABLE)

/**
 * \brief Macro is used to fill usart configuration structure based on
 * its number
 *
 * \param[in] n The number of structures
 */

#define USART_CONFIGURATION(n)                                                                                         \
	{                                                                                                                  \
		n,                                                                                                             \
		    US_MR_USART_MODE(0x0) | US_MR_USCLKS(CONF_USART##n##_CK_SRC) | US_MR_CHRL(CONF_USART_##n##_CHSIZE)         \
		        | (CONF_USART_##n##_MODE << US_MR_USART_SYNC_Pos) | US_MR_USART_PAR(CONF_USART_##n##_PARITY)           \
		        | US_MR_USART_NBSTOP(CONF_USART_##n##_SBMODE) | US_MR_USART_CHMODE(CONF_USART_##n##_CHMODE)            \
		        | (CONF_USART_##n##_MSBF << US_MR_USART_MSBF_Pos) | (CONF_USART_##n##_MODE9 << US_MR_USART_MODE9_Pos)  \
		        | (CONF_USART_##n##_CLKO << US_MR_CLKO_Pos) | (CONF_USART_##n##_OVER << US_MR_USART_OVER_Pos)          \
		        | (CONF_USART_##n##_INACK << US_MR_USART_INACK_Pos)                                                    \
		        | (CONF_USART_##n##_DSNACK << US_MR_USART_DSNACK_Pos)                                                  \
		        | (CONF_USART_##n##_VAR_SYNC << US_MR_USART_VAR_SYNC_Pos)                                              \
		        | (CONF_USART_##n##_INVDATA << US_MR_USART_INVDATA_Pos)                                                \
		        | US_MR_USART_MAX_ITERATION(CONF_USART_##n##_MAX_ITERATION)                                            \
		        | (CONF_USART_##n##_FILTER << US_MR_USART_FILTER_Pos) | (CONF_USART_##n##_MAN << US_MR_USART_MAN_Pos)  \
		        | (CONF_USART_##n##_MODSYNC << US_MR_USART_MODSYNC_Pos)                                                \
		        | (CONF_USART_##n##_ONEBIT << US_MR_USART_ONEBIT_Pos),                                                 \
		    US_BRGR_CD(CONF_USART_##n##_BAUD_CD) | US_BRGR_FP(CONF_USART_##n##_BAUD_FP)                                \
	}
/**
 * \brief USART configuration type
 */
struct usart_configuration {
	uint8_t                 number;
	hri_usart_us_mr_reg_t   us_mr;
	hri_usart_us_brgr_reg_t us_brgr;
};

#if USART_AMOUNT < 1
/** Dummy array to pass compiling. */
static struct usart_configuration _usarts[1] = {{0}};
#else
/**
 * \brief Array of USART configurations
 */
static struct usart_configuration _usarts[] = {
#if CONF_USART_0_ENABLE == 1
    USART_CONFIGURATION(0),
#endif
#if CONF_USART_1_ENABLE == 1
    USART_CONFIGURATION(1),
#endif
#if CONF_USART_2_ENABLE == 1
    USART_CONFIGURATION(2),
#endif
};
#endif

static struct _usart_async_device *_usart1_dev = NULL;

static uint8_t _usart_get_irq_num(const void *const hw);
static uint8_t _get_usart_index(const void *const hw);
static uint8_t _usart_get_hardware_index(const void *const hw);

static int32_t     _usart_init(void *const hw);
static inline void _usart_enable(void *const hw);
static inline void _usart_disable(void *const hw);
static inline void _usart_deinit(void *const hw);
static uint16_t    _usart_calculate_baud_rate(const uint32_t baud, const uint32_t clock_rate, const uint8_t samples,
                                              const enum usart_baud_rate_mode mode, const uint8_t fraction);
static void        _usart_set_baud_rate(void *const hw, const uint32_t baud_rate);
static void        _usart_set_data_order(void *const hw, const enum usart_data_order order);
static void        _usart_set_mode(void *const hw, const enum usart_mode mode);
static void        _usart_set_parity(void *const hw, const enum usart_parity parity);
static void        _usart_set_stop_bits(void *const hw, const enum usart_stop_bits stop_bits);
static void        _usart_set_character_size(void *const hw, const enum usart_character_size size);

/**
 * \brief Retrieve IRQ number for the given hardware instance
 */
static uint8_t _usart_get_irq_num(const void *const hw)
{
	ASSERT(hw);

	return USART0_IRQn + _usart_get_hardware_index(hw);
}

/**
 * \brief Init irq param with the given usart hardware instance
 */
static void _usart_init_irq_param(const void *const hw, struct _usart_async_device *dev)
{
	if (hw == USART1) {
		_usart1_dev = dev;
	}
}

/**
 * \brief Initialize synchronous USART
 */
int32_t _usart_usart_sync_init(struct _usart_sync_device *const device, void *const hw)
{
	ASSERT(device);
	ASSERT(hw);

	device->hw = hw;

	return _usart_init(hw);
}

/**
 * \brief Initialize asynchronous USART
 */
int32_t _usart_async_init(struct _usart_async_device *const device, void *const hw)
{
	int32_t init_status;

	ASSERT(device);

	init_status = _usart_init(hw);
	if (init_status) {
		return init_status;
	}
	device->hw = hw;

	_usart_init_irq_param(hw, device);
	NVIC_DisableIRQ((IRQn_Type)_usart_get_irq_num(hw));
	NVIC_ClearPendingIRQ((IRQn_Type)_usart_get_irq_num(hw));
	NVIC_EnableIRQ((IRQn_Type)_usart_get_irq_num(hw));

	return ERR_NONE;
}

/**
 * \brief De-initialize USART
 */
void _usart_usart_sync_deinit(struct _usart_sync_device *const device)
{
	ASSERT(device);
	_usart_deinit(device->hw);
}

/**
 * \brief De-initialize USART
 */
void _usart_async_deinit(struct _usart_async_device *const device)
{
	ASSERT(device);
	NVIC_DisableIRQ((IRQn_Type)_usart_get_irq_num(device->hw));
	_usart_deinit(device->hw);
}

/**
 * \brief Calculate baud rate register value
 */
uint16_t _usart_usart_sync_calculate_baud_rate(const uint32_t baud, const uint32_t clock_rate, const uint8_t samples,
                                               const enum usart_baud_rate_mode mode, const uint8_t fraction)
{
	return _usart_calculate_baud_rate(baud, clock_rate, samples, mode, fraction);
}

/**
 * \brief Calculate baud rate register value
 */
uint16_t _usart_async_calculate_baud_rate(const uint32_t baud, const uint32_t clock_rate, const uint8_t samples,
                                          const enum usart_baud_rate_mode mode, const uint8_t fraction)
{
	return _usart_calculate_baud_rate(baud, clock_rate, samples, mode, fraction);
}
/**
 * \brief Enable USART sync module
 */
void _usart_usart_sync_enable(struct _usart_sync_device *const device)
{
	ASSERT(device);
	_usart_enable(device->hw);
}

/**
 * \brief Enable USART async module
 */
void _usart_async_enable(struct _usart_async_device *const device)
{
	ASSERT(device);
	_usart_enable(device->hw);
}

/**
 * \brief Disable USART sync module
 */
void _usart_usart_sync_disable(struct _usart_sync_device *const device)
{
	ASSERT(device);
	_usart_disable(device->hw);
}

/**
 * \brief Disable USART async module
 */
void _usart_async_disable(struct _usart_async_device *const device)
{
	ASSERT(device);
	_usart_disable(device->hw);
}

/**
 * \brief Set baud rate
 */
void _usart_usart_sync_set_baud_rate(struct _usart_sync_device *const device, const uint32_t baud_rate)
{
	ASSERT(device);
	_usart_set_baud_rate(device->hw, baud_rate);
}

/**
 * \brief Set baud rate
 */
void _usart_async_set_baud_rate(struct _usart_async_device *const device, const uint32_t baud_rate)
{
	ASSERT(device);
	_usart_set_baud_rate(device->hw, baud_rate);
}

/**
 * \brief Set data order
 */
void _usart_usart_sync_set_data_order(struct _usart_sync_device *const device, const enum usart_data_order order)
{
	ASSERT(device);
	_usart_set_data_order(device->hw, order);
}

/**
 * \brief Set data order
 */
void _usart_async_set_data_order(struct _usart_async_device *const device, const enum usart_data_order order)
{
	ASSERT(device);
	_usart_set_data_order(device->hw, order);
}

/**
 * \brief Set mode
 */
void _usart_usart_sync_set_mode(struct _usart_sync_device *const device, const enum usart_mode mode)
{
	ASSERT(device);
	_usart_set_mode(device->hw, mode);
}

/**
 * \brief Set mode
 */
void _usart_async_set_mode(struct _usart_async_device *const device, const enum usart_mode mode)
{
	ASSERT(device);
	_usart_set_mode(device->hw, mode);
}

/**
 * \brief Set parity
 */
void _usart_usart_sync_set_parity(struct _usart_sync_device *const device, const enum usart_parity parity)
{
	ASSERT(device);
	_usart_set_parity(device->hw, parity);
}

/**
 * \brief Set parity
 */
void _usart_async_set_parity(struct _usart_async_device *const device, const enum usart_parity parity)
{
	ASSERT(device);
	_usart_set_parity(device->hw, parity);
}

/**
 * \brief Set stop bits mode
 */
void _usart_usart_sync_set_stop_bits(struct _usart_sync_device *const device, const enum usart_stop_bits stop_bits)
{
	ASSERT(device);
	_usart_set_stop_bits(device->hw, stop_bits);
}

/**
 * \brief Set stop bits mode
 */
void _usart_async_set_stop_bits(struct _usart_async_device *const device, const enum usart_stop_bits stop_bits)
{
	ASSERT(device);
	_usart_set_stop_bits(device->hw, stop_bits);
}

/**
 * \brief Set character size
 */
void _usart_usart_sync_set_character_size(struct _usart_sync_device *const device, const enum usart_character_size size)
{
	ASSERT(device);
	_usart_set_character_size(device->hw, size);
}

/**
 * \brief Set character size
 */
void _usart_async_set_character_size(struct _usart_async_device *const device, const enum usart_character_size size)
{
	ASSERT(device);
	_usart_set_character_size(device->hw, size);
}

/**
 * \brief Retrieve usart status
 */
uint32_t _usart_usart_sync_get_status(const struct _usart_sync_device *const device)
{
	ASSERT(device);
	return (uint32_t)hri_usart_read_US_CSR_reg(device->hw);
}

/**
 * \brief Retrieve usart status
 */
uint32_t _usart_async_get_status(const struct _usart_async_device *const device)
{
	ASSERT(device);
	return (uint32_t)hri_usart_read_US_CSR_reg(device->hw);
}

/**
 * \brief Write a byte to the given USART instance
 */
void _usart_usart_sync_write_byte(struct _usart_sync_device *const device, uint8_t data)
{
	ASSERT(device);
	hri_usart_write_US_THR_reg(device->hw, (hri_usart_us_thr_reg_t)data);
}

/**
 * \brief Write a byte to the given USART instance
 */
void _usart_async_write_byte(struct _usart_async_device *const device, uint8_t data)
{
	ASSERT(device);
	hri_usart_write_US_THR_reg(device->hw, (hri_usart_us_thr_reg_t)data);
}

/**
 * \brief Read a byte from the given USART instance
 */
uint8_t _usart_usart_sync_read_byte(const struct _usart_sync_device *const device)
{
	ASSERT(device);
	return (uint8_t)(hri_usart_read_US_RHR_reg(device->hw) & 0xff);
}

/**
 * \brief Check if USART is ready to send next byte
 */
bool _usart_usart_sync_is_ready_to_send(const struct _usart_sync_device *const device)
{
	ASSERT(device);
	return hri_usart_get_US_CSR_TXRDY_bit(device->hw);
}

/**
 * \brief Check if USART transmission complete
 */
bool _usart_usart_sync_is_transmit_done(const struct _usart_sync_device *const device)
{
	ASSERT(device);
	return hri_usart_get_US_CSR_TXEMPTY_bit(device->hw);
}

/**
 * \brief Check if USART is ready to send next byte
 */
bool _usart_async_is_byte_sent(const struct _usart_async_device *const device)
{
	ASSERT(device);
	return hri_usart_get_US_CSR_TXRDY_bit(device->hw);
}

/**
 * \brief Check if there is data received by USART
 */
bool _usart_usart_sync_is_byte_received(const struct _usart_sync_device *const device)
{
	ASSERT(device);
	return hri_usart_get_US_CSR_RXRDY_bit(device->hw);
}

/**
 * \brief Set the state of flow control pins
 */
void _usart_usart_sync_set_flow_control_state(struct _usart_sync_device *const     device,
                                              const union usart_flow_control_state state)
{
	ASSERT(device);
	(void)device;
	(void)state;
}

/**
 * \brief Set the state of flow control pins
 */
void _usart_async_set_flow_control_state(struct _usart_async_device *const    device,
                                         const union usart_flow_control_state state)
{
	ASSERT(device);
	(void)device;
	(void)state;
}

/**
 * \brief Retrieve the state of flow control pins
 */
union usart_flow_control_state _usart_usart_sync_get_flow_control_state(const struct _usart_sync_device *const device)
{
	ASSERT(device);
	(void)device;
	union usart_flow_control_state state;

	state.value           = 0;
	state.bit.unavailable = 1;
	return state;
}

/**
 * \brief Retrieve the state of flow control pins
 */
union usart_flow_control_state _usart_async_get_flow_control_state(const struct _usart_async_device *const device)
{
	ASSERT(device);
	(void)device;
	union usart_flow_control_state state;

	state.value           = 0;
	state.bit.unavailable = 1;
	return state;
}

/**
 * \brief Enable data register empty interrupt
 */
void _usart_async_enable_byte_sent_irq(struct _usart_async_device *const device)
{
	ASSERT(device);
	hri_usart_set_US_IMR_TXRDY_bit(device->hw);
}

/**
 * \brief Enable transmission complete interrupt
 */
void _usart_async_enable_tx_done_irq(struct _usart_async_device *const device)
{
	ASSERT(device);
	hri_usart_set_US_IMR_TXEMPTY_bit(device->hw);
}

/**
 * \brief Retrieve ordinal number of the given usart hardware instance
 */
static uint8_t _usart_get_hardware_index(const void *const hw)
{
	ASSERT(hw);

#ifdef _UNIT_TEST_
	return ((uint32_t)hw - (uint32_t)USART0) / sizeof(Usart);
#endif

	return ((uint32_t)hw - (uint32_t)USART0) >> 14;
}

/**
 * \brief Retrieve ordinal number of the given USART hardware instance
 */
uint8_t _usart_usart_sync_get_hardware_index(const struct _usart_sync_device *const device)
{
	ASSERT(device);
	return _usart_get_hardware_index(device->hw);
}

/**
 * \brief Retrieve ordinal number of the given USART hardware instance
 */
uint8_t _usart_async_get_hardware_index(const struct _usart_async_device *const device)
{
	ASSERT(device);
	return _usart_get_hardware_index(device->hw);
}

/**
 * \brief Enable/disable USART interrupt
 */
void _usart_async_set_irq_state(struct _usart_async_device *const device, const enum _usart_async_callback_type type,
                                const bool state)
{
	ASSERT(device);
	if (state) {
		if (USART_ASYNC_BYTE_SENT == type || USART_ASYNC_TX_DONE == type) {
			hri_usart_set_US_IMR_TXRDY_bit(device->hw);
			hri_usart_set_US_IMR_TXEMPTY_bit(device->hw);
		} else if (USART_ASYNC_RX_DONE == type) {
			hri_usart_set_US_IMR_RXRDY_bit(device->hw);
		} else if (USART_ASYNC_ERROR == type) {

			hri_usart_set_US_IMR_reg(
			    device->hw, US_CSR_OVRE | US_CSR_USART_LIN_FRAME | US_CSR_USART_LIN_PARE | US_CSR_USART_MANERR);
		}
	} else {
		if (USART_ASYNC_BYTE_SENT == type || USART_ASYNC_TX_DONE == type) {
			hri_usart_clear_US_IMR_TXRDY_bit(device->hw);
			hri_usart_clear_US_IMR_TXEMPTY_bit(device->hw);
		} else if (USART_ASYNC_RX_DONE == type) {
			hri_usart_clear_US_IMR_RXRDY_bit(device->hw);
		} else if (USART_ASYNC_ERROR == type) {

			hri_usart_clear_US_IMR_reg(
			    device->hw, US_CSR_OVRE | US_CSR_USART_LIN_FRAME | US_CSR_USART_LIN_PARE | US_CSR_USART_MANERR);
		}
	}
}

/**
 * \brief Retrieve usart sync helper functions
 */
void *_usart_get_usart_sync(void)
{
	return (void *)NULL;
}

/**
 * \brief Retrieve usart async helper functions
 */
void *_usart_get_usart_async(void)
{
	return (void *)NULL;
}

/**
 * \brief Retrieve usart dma helper functions
 */
void *_usart_get_usart_dma(void)
{
	return (void *)NULL;
}

/**
 * \internal Usart interrupt handler
 *
 * \param[in] p The pointer to interrupt parameter
 */
static void _usart_interrupt_handler(struct _usart_async_device *device)
{
	ASSERT(device);
	void *hw = device->hw;

	if (hri_usart_get_US_CSR_TXRDY_bit(hw) && hri_usart_get_US_IMR_TXRDY_bit(hw)) {
		hri_usart_clear_US_IMR_TXRDY_bit(hw);
		device->usart_cb.tx_byte_sent(device);
	} else if (hri_usart_get_US_CSR_TXEMPTY_bit(hw) && hri_usart_get_US_IMR_TXEMPTY_bit(hw)) {
		hri_usart_clear_US_IMR_TXEMPTY_bit(hw);
		device->usart_cb.tx_done_cb(device);
	} else if (hri_usart_get_US_CSR_RXRDY_bit(hw) && hri_usart_get_US_IMR_RXRDY_bit(hw)) {
		if (hri_usart_read_US_CSR_reg(hw) &

		    (US_CSR_OVRE | US_CSR_USART_LIN_FRAME | US_CSR_USART_LIN_PARE | US_CSR_USART_MANERR)) {
			hri_usart_read_US_RHR_reg(hw);
			hri_usart_write_US_CR_reg(hw, US_CR_RSTSTA);
			return;
		}
		device->usart_cb.rx_done_cb(device, (uint8_t)hri_usart_read_US_RHR_reg(hw));
	} else if (hri_usart_read_US_CSR_reg(hw) &

	           (US_CSR_OVRE | US_CSR_USART_LIN_FRAME | US_CSR_USART_LIN_PARE | US_CSR_USART_MANERR)) {
		hri_usart_write_US_CR_reg(hw, US_CR_RSTSTA);
		device->usart_cb.error_cb(device);
	}
}

/**
 * \internal USART interrupt handler
 */
void USART1_Handler(void)
{
	_usart_interrupt_handler(_usart1_dev);
}

/**
 * \internal Retrieve ordinal number of the given usart hardware instance
 *
 * \param[in] hw The pointer to hardware instance

 * \return The ordinal number of the given usart hardware instance
 */
static uint8_t _get_usart_index(const void *const hw)
{
	ASSERT(hw);
	uint8_t usart_offset = _usart_get_hardware_index(hw);
	uint8_t i;

	for (i = 0; i < ARRAY_SIZE(_usarts); i++) {
		if (_usarts[i].number == usart_offset) {
			return i;
		}
	}

	ASSERT(false);
	return 0;
}

/**
 * \internal Initialize USART
 *
 * \param[in] hw The pointer to hardware instance
 *
 * \return The status of initialization
 */
static int32_t _usart_init(void *const hw)
{
	ASSERT(hw);
	uint8_t i = _get_usart_index(hw);
	/* Disable the Write Protect. */
	hri_usart_write_US_WPMR_reg(hw, US_WPMR_WPKEY_PASSWD);

	/* Reset registers that could cause unpredictable behavior after reset. */
	hri_usart_write_US_MR_reg(hw, 0x0);
	hri_usart_write_US_RTOR_reg(hw, 0x0);
	hri_usart_write_US_TTGR_reg(hw, 0x0);

	/* Disable and reset TX and RX. */
	hri_usart_write_US_CR_reg(hw, US_CR_RSTRX | US_CR_RXDIS | US_CR_RSTTX | US_CR_TXDIS);
	/* Reset status bits. */
	hri_usart_write_US_CR_reg(hw, US_CR_RSTSTA);
	/* Turn off RTS and DTR if exist. */
	hri_usart_write_US_CR_reg(hw, US_CR_USART_RTSDIS);

	hri_usart_write_US_MR_reg(hw, _usarts[i].us_mr);
	hri_usart_write_US_BRGR_reg(hw, _usarts[i].us_brgr);

	return ERR_NONE;
}

/**
 * \internal De-initialize USART
 *
 * \param[in] hw The pointer to hardware instance
 */
static inline void _usart_deinit(void *const hw)
{
	ASSERT(hw);
	hri_usart_write_US_CR_reg(hw, US_CR_RSTRX | US_CR_RSTTX | US_CR_RSTSTA);
}

/**
 * \internal Enable USART
 *
 * \param[in] hw The pointer to hardware instance
 */
static inline void _usart_enable(void *const hw)
{
	ASSERT(hw);
	hri_usart_write_US_CR_reg(hw, US_CR_RXEN | US_CR_TXEN);
}

/**
 * \internal Disable USART
 *
 * \param[in] hw The pointer to hardware instance
 */
static inline void _usart_disable(void *const hw)
{
	ASSERT(hw);
	hri_usart_write_US_CR_reg(hw, US_CR_RXDIS | US_CR_TXDIS);
}

/**
 * \internal Calculate baud rate register value
 *
 * \param[in] baud Required baud rate
 * \param[in] clock_rate USART clock frequency
 * \param[in] samples The number of samples
 * \param[in] mode USART mode
 * \param[in] fraction A fraction value
 *
 * \return Calculated baud rate register value
 */
static uint16_t _usart_calculate_baud_rate(const uint32_t baud, const uint32_t clock_rate, const uint8_t samples,
                                           const enum usart_baud_rate_mode mode, const uint8_t fraction)
{
	if (USART_BAUDRATE_ASYNCH_ARITHMETIC == mode) {
		return clock_rate / baud / samples;
	}

	if (USART_BAUDRATE_ASYNCH_FRACTIONAL == mode) {
		return clock_rate / baud / samples + US_BRGR_FP(fraction);
	}

	if (USART_BAUDRATE_SYNCH == mode) {
		return clock_rate / baud;
	}

	return 0;
}

/**
 * \internal Set baud rate
 *
 * \param[in] device The pointer to USART device instance
 * \param[in] baud_rate A baud rate to set
 */
static void _usart_set_baud_rate(void *const hw, const uint32_t baud_rate)
{
	ASSERT(hw);
	uint32_t usart_freq, cd = 0, fp = 0, clock_select;
	bool     over;
	uint8_t  i = _usarts[_get_usart_index(hw)].number;
	switch (i) {
	case 0:

#ifdef CONF_USART0_FREQUENCY
		usart_freq = CONF_USART0_FREQUENCY;
#endif
		break;

	case 1:
#ifdef CONF_USART1_FREQUENCY
		usart_freq = CONF_USART1_FREQUENCY;
#endif
		break;

	case 2:
#ifdef CONF_USART2_FREQUENCY
		usart_freq = CONF_USART2_FREQUENCY;
#endif
		break;

	default:
		ASSERT(false);
	}

	clock_select = hri_usart_read_US_MR_USCLKS_bf(hw);
	if (hri_usart_get_US_MR_USART_SYNC_bit(hw)) {
		switch (clock_select) {
		case 0x0:
		case 0x1:
		case 0x2:
			cd = usart_freq / baud_rate;
			fp = usart_freq * 8 / baud_rate - 8 * cd;
			break;

		case 0x3:
			break;

		default:
			ASSERT(false);
		}
	} else {
		over = hri_usart_get_US_MR_USART_OVER_bit(hw);
		switch (clock_select) {
		case 0x0:
		case 0x1:
		case 0x2:
			cd = usart_freq / baud_rate / 8 / (2 - over);
			fp = usart_freq / baud_rate / (2 - over) - 8 * cd;
			break;

		case 0x3:
			break;

		default:
			ASSERT(false);
		}
	}
	hri_usart_write_US_WPMR_reg(hw, US_WPMR_WPKEY_PASSWD);
	hri_usart_write_US_BRGR_reg(hw, US_BRGR_CD(cd) | US_BRGR_FP(fp));
}

/**
 * \internal Set data order
 *
 * \param[in] device The pointer to USART device instance
 * \param[in] order A data order to set
 */
static void _usart_set_data_order(void *const hw, const enum usart_data_order order)
{
	ASSERT(hw);

	hri_usart_write_US_WPMR_reg(hw, US_WPMR_WPKEY_PASSWD);
	if (order == USART_DATA_ORDER_MSB) {
		hri_usart_set_US_MR_USART_MSBF_bit(hw);
	} else {
		hri_usart_clear_US_MR_USART_MSBF_bit(hw);
	}
}

/**
 * \internal Set mode
 *
 * \param[in] device The pointer to USART device instance
 * \param[in] mode A mode to set
 */
static void _usart_set_mode(void *const hw, const enum usart_mode mode)
{
	ASSERT(hw);
	hri_usart_write_US_WPMR_reg(hw, US_WPMR_WPKEY_PASSWD);
	if (mode == USART_MODE_SYNCHRONOUS) {
		hri_usart_set_US_MR_USART_SYNC_bit(hw);
	} else {
		hri_usart_clear_US_MR_USART_SYNC_bit(hw);
	}
}

/**
 * \internal Set parity
 *
 * \param[in] device The pointer to USART device instance
 * \param[in] parity A parity to set
 */
static void _usart_set_parity(void *const hw, const enum usart_parity parity)
{
	ASSERT(hw);
	hri_usart_write_US_WPMR_reg(hw, US_WPMR_WPKEY_PASSWD);
	switch (parity) {
	case USART_PARITY_EVEN:
		hri_usart_write_US_MR_USART_PAR_bf(hw, (hri_usart_us_mr_reg_t)0x0u);
		break;

	case USART_PARITY_ODD:
		hri_usart_write_US_MR_USART_PAR_bf(hw, (hri_usart_us_mr_reg_t)0x1u);
		break;

	case USART_PARITY_SPACE:
		hri_usart_write_US_MR_USART_PAR_bf(hw, (hri_usart_us_mr_reg_t)0x2u);
		break;

	case USART_PARITY_MARK:
		hri_usart_write_US_MR_USART_PAR_bf(hw, (hri_usart_us_mr_reg_t)0x3u);
		break;

	case USART_PARITY_NONE:
		hri_usart_write_US_MR_USART_PAR_bf(hw, (hri_usart_us_mr_reg_t)0x4u);
		break;

	default:
		ASSERT(false);
	}
}

/**
 * \internal Set stop bits mode
 *
 * \param[in] device The pointer to USART device instance
 * \param[in] stop_bits A stop bits mode to set
 */
static void _usart_set_stop_bits(void *const hw, const enum usart_stop_bits stop_bits)
{
	ASSERT(hw);
	hri_usart_write_US_WPMR_reg(hw, US_WPMR_WPKEY_PASSWD);
	switch (stop_bits) {
	case USART_STOP_BITS_ONE:
		hri_usart_write_US_MR_USART_NBSTOP_bf(hw, (hri_usart_us_mr_reg_t)0x0u);
		break;

	case USART_STOP_BITS_TWO:
		hri_usart_write_US_MR_USART_NBSTOP_bf(hw, (hri_usart_us_mr_reg_t)0x2u);
		break;

	case USART_STOP_BITS_ONE_P_FIVE:
		hri_usart_write_US_MR_USART_NBSTOP_bf(hw, (hri_usart_us_mr_reg_t)0x1u);
		break;

	default:
		ASSERT(false);
	}
}

/**
 * \internal Set character size
 *
 * \param[in] device The pointer to USART device instance
 * \param[in] size A character size to set
 */
static void _usart_set_character_size(void *const hw, const enum usart_character_size size)
{
	ASSERT(hw);
	hri_usart_write_US_WPMR_reg(hw, US_WPMR_WPKEY_PASSWD);
	if (size == USART_CHARACTER_SIZE_9BITS) {
		hri_usart_set_US_MR_USART_MODE9_bit(hw);
	} else {
		hri_usart_clear_US_MR_USART_MODE9_bit(hw);
		switch (size) {
		case USART_CHARACTER_SIZE_5BITS:
			hri_usart_write_US_MR_CHRL_bf(hw, (hri_usart_us_mr_reg_t)0x0u);
			break;

		case USART_CHARACTER_SIZE_6BITS:
			hri_usart_write_US_MR_CHRL_bf(hw, (hri_usart_us_mr_reg_t)0x1u);
			break;

		case USART_CHARACTER_SIZE_7BITS:
			hri_usart_write_US_MR_CHRL_bf(hw, (hri_usart_us_mr_reg_t)0x2u);
			break;

		case USART_CHARACTER_SIZE_8BITS:
			hri_usart_write_US_MR_CHRL_bf(hw, (hri_usart_us_mr_reg_t)0x3u);
			break;

		default:
			ASSERT(false);
		}
	}
}
