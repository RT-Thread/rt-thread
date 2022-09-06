/**
 * \file
 *
 * \brief External IRQ related functionality declaration.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _HPL_EXT_IRQ_H_INCLUDED
#define _HPL_EXT_IRQ_H_INCLUDED

/**
 * \addtogroup HPL EXT IRQ
 *
 * \section hpl_ext_irq_rev Revision History
 * - v1.0.0 Initial Release
 *
 *@{
 */

#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name HPL functions
 */
//@{
/**
 * \brief Initialize external interrupt module
 *
 * This function does low level external interrupt configuration.
 *
 * \param[in] cb The pointer to callback function from external interrupt
 *
 * \return Initialization status.
 * \retval -1 External irq module is already initialized
 * \retval 0 The initialization is completed successfully
 */
int32_t _ext_irq_init(void (*cb)(const uint32_t pin));

/**
 * \brief Deinitialize external interrupt module
 *
 * \return Initialization status.
 * \retval -1 External irq module is already deinitialized
 * \retval 0 The de-initialization is completed successfully
 */
int32_t _ext_irq_deinit(void);

/**
 * \brief Enable / disable external irq
 *
 * \param[in] pin Pin to enable external irq on
 * \param[in] enable True to enable, false to disable
 *
 * \return Status of external irq enabling / disabling
 * \retval -1 External irq module can't be enabled / disabled
 * \retval 0 External irq module is enabled / disabled successfully
 */
int32_t _ext_irq_enable(const uint32_t pin, const bool enable);
//@}

#ifdef __cplusplus
}
#endif
/**@}*/
#endif /* _HPL_EXT_IRQ_H_INCLUDED */
