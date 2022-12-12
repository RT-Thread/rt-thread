/**
 * \file
 *
 * \brief ADC related functionality declaration.
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

#ifndef _HPL_ADC_ADC_H_INCLUDED
#define _HPL_ADC_ADC_H_INCLUDED

#include <hpl_adc_sync.h>
#include <hpl_adc_async.h>

/**
 * \addtogroup HPL ADC
 *
 * \section hpl_adc_rev Revision History
 * - v1.0.0 Initial Release
 *
 *@{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name HPL functions
 */
//@{

/**
 * \brief Retrieve ADC helper functions
 *
 * \return A pointer to set of ADC helper functions
 */
void *_adc_get_adc_sync(void);
void *_adc_get_adc_async(void);

//@}

#ifdef __cplusplus
}
#endif
/**@}*/
#endif /* _HPL_USART_UART_H_INCLUDED */
