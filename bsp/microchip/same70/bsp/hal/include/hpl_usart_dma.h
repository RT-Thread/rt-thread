/**
 * \file
 *
 * \brief USART related functionality declaration.
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _HPL_USART_DMA_H_INCLUDED
#define _HPL_USART_DMA_H_INCLUDED

/**
 * \addtogroup HPL USART
 *
 * \section hpl_usart_rev Revision History
 * - v1.0.0 Initial Release
 *
 *@{
 */

#include "hpl_usart.h"
#include "hpl_irq.h"
#include <hpl_dma.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief USART callback types
 */
enum usart_dma_callback_type { USART_DMA_RX_DONE, USART_DMA_TX_DONE, USART_DMA_ERROR };

/**
 * \brief USART device structure
 *
 * The USART device structure forward declaration.
 */
struct _usart_dma_device;

/**
 *  \brief The prototype for callback on USART DMA.
 */
typedef void (*usart_dma_cb_t)(struct _dma_resource *resource);

/**
 * \brief USART interrupt callbacks
 */
struct _usart_dma_callbacks {
	usart_dma_cb_t tx_done_cb;
	usart_dma_cb_t rx_done_cb;
	usart_dma_cb_t error_cb;
};

/**
 * \brief USART descriptor device structure
 */
struct _usart_dma_device {
	struct _usart_dma_callbacks usart_cb;
	void *                      hw;
	struct _dma_resource *      resource;
};
/**
 * \name HPL functions
 */
//@{
/**
 * \brief Initialize dmahronous USART
 *
 * This function does low level USART configuration.
 *
 * \param[in] device The pointer to USART device instance
 * \param[in] hw The pointer to hardware instance
 *
 * \return Initialization status
 */
int32_t _usart_dma_init(struct _usart_dma_device *const device, void *const hw);

/**
 * \brief Deinitialize USART
 *
 * This function closes the given USART by disabling its clock.
 *
 * \param[in] device The pointer to USART device instance
 */
void _usart_dma_deinit(struct _usart_dma_device *const device);

/**
 * \brief Enable usart module
 *
 * This function will enable the usart module
 *
 * \param[in] device The pointer to USART device instance
 */
void _usart_dma_enable(struct _usart_dma_device *const device);

/**
 * \brief Disable usart module
 *
 * This function will disable the usart module
 *
 * \param[in] device The pointer to USART device instance
 */
void _usart_dma_disable(struct _usart_dma_device *const device);

/**
 * \brief Calculate baud rate register value
 *
 * \param[in] baud Required baud rate
 * \param[in] clock_rate clock frequency
 * \param[in] samples The number of samples
 * \param[in] mode USART mode
 * \param[in] fraction A fraction value
 *
 * \return Calculated baud rate register value
 */
uint16_t _usart_dma_calculate_baud_rate(const uint32_t baud, const uint32_t clock_rate, const uint8_t samples,
                                        const enum usart_baud_rate_mode mode, const uint8_t fraction);

/**
 * \brief Set baud rate
 *
 * \param[in] device The pointer to USART device instance
 * \param[in] baud_rate A baud rate to set
 */
void _usart_dma_set_baud_rate(struct _usart_dma_device *const device, const uint32_t baud_rate);

/**
 * \brief Set data order
 *
 * \param[in] device The pointer to USART device instance
 * \param[in] order A data order to set
 */
void _usart_dma_set_data_order(struct _usart_dma_device *const device, const enum usart_data_order order);

/**
 * \brief Set mode
 *
 * \param[in] device The pointer to USART device instance
 * \param[in] mode A mode to set
 */
void _usart_dma_set_mode(struct _usart_dma_device *const device, const enum usart_mode mode);

/**
 * \brief Set parity
 *
 * \param[in] device The pointer to USART device instance
 * \param[in] parity A parity to set
 */
void _usart_dma_set_parity(struct _usart_dma_device *const device, const enum usart_parity parity);

/**
 * \brief Set stop bits mode
 *
 * \param[in] device The pointer to USART device instance
 * \param[in] stop_bits A stop bits mode to set
 */
void _usart_dma_set_stop_bits(struct _usart_dma_device *const device, const enum usart_stop_bits stop_bits);

/**
 * \brief Set character size
 *
 * \param[in] device The pointer to USART device instance
 * \param[in] size A character size to set
 */
void _usart_dma_set_character_size(struct _usart_dma_device *const device, const enum usart_character_size size);

/**
 * \brief Set the state of flow control pins
 *
 * \param[in] device The pointer to USART device instance
 * \param[in] state - A state of flow control pins to set
 */
void _usart_dma_set_flow_control_state(struct _usart_dma_device *const      device,
                                       const union usart_flow_control_state state);

/**
 * \brief Eanble dma write
 *
 * \param[in] device The pointer to USART device instance
 * \param[in] txbuf Pointer to the transfer information
 * \param[in] length spi transfer data length
 *
 *  \return Operation status
 *  \retval ERR_NONE Success
 *  \retval ERR_INVALID_DATA Invalid data
 */
int32_t _usart_dma_write(struct _usart_dma_device *const device, uint8_t const *txbuf, const uint16_t length);

/**
 * \brief Eanble dma read
 *
 * \param[in] device The pointer to USART device instance
 * \param[out] rxbuf Pointer to the receiver information
 * \param[in] length spi receiver data length
 *
 *  \return Operation status
 *  \retval ERR_NONE Success
 *  \retval ERR_INVALID_DATA Invalid data
 */
int32_t _usart_dma_read(struct _usart_dma_device *const device, uint8_t *const rxbuf, const uint16_t length);

/**
 * \brief Enable/disable USART interrupt
 *
 * param[in] device The pointer to USART device instance
 * param[in] type The type of interrupt to disable/enable if applicable
 * param[in] state Enable or disable
 */
void _usart_dma_register_callback(struct _usart_dma_device *const device, const enum usart_dma_callback_type type,
                                  usart_dma_cb_t cb);
//@}

#ifdef __cplusplus
}
#endif
/**@}*/
#endif /* _HPL_USART_DMA_H_INCLUDED */
