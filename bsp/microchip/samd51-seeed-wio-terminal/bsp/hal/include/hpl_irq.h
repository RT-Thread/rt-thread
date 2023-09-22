/**
 * \file
 *
 * \brief IRQ related functionality declaration.
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _HPL_IRQ_H_INCLUDED
#define _HPL_IRQ_H_INCLUDED

/**
 * \addtogroup HPL IRQ
 *
 * \section hpl_irq_rev Revision History
 * - v1.0.0 Initial Release
 *
 *@{
 */

#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief IRQ descriptor
 */
struct _irq_descriptor {
	void (*handler)(void *parameter);
	void *parameter;
};

/**
 * \name HPL functions
 */
//@{
/**
 * \brief Retrieve current IRQ number
 *
 * \return The current IRQ number
 */
uint8_t _irq_get_current(void);

/**
 * \brief Disable the given IRQ
 *
 * \param[in] n The number of IRQ to disable
 */
void _irq_disable(uint8_t n);

/**
 * \brief Set the given IRQ
 *
 * \param[in] n The number of IRQ to set
 */
void _irq_set(uint8_t n);

/**
 * \brief Clear the given IRQ
 *
 * \param[in] n The number of IRQ to clear
 */
void _irq_clear(uint8_t n);

/**
 * \brief Enable the given IRQ
 *
 * \param[in] n The number of IRQ to enable
 */
void _irq_enable(uint8_t n);

/**
 * \brief Register IRQ handler
 *
 * \param[in] number The number registered IRQ
 * \param[in] irq The pointer to irq handler to register
 *
 * \return The status of IRQ handler registering
 * \retval -1 Passed parameters were invalid
 * \retval 0 The registering is completed successfully
 */
void _irq_register(const uint8_t number, struct _irq_descriptor *const irq);
//@}

#ifdef __cplusplus
}
#endif
/**@}*/
#endif /* _HPL_IRQ_H_INCLUDED */
