/***************************************************************************//**
* \file cy_crypto_core_trng_config.h
* \version 2.70
*
* \brief
*  This file provides internal (not public) constants and parameters
*  for the Crypto TRNG driver.
*
********************************************************************************
* \copyright
* Copyright (c) (2020-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/


#if !defined (CY_CRYPTO_CORE_TRNG_CONFIG_H)
#define CY_CRYPTO_CORE_TRNG_CONFIG_H

#include "cy_crypto_core_trng.h"

#if defined (CY_IP_MXCRYPTO)

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_TR == 1)


/** TRNG Configuration default values */
/**
* Specifies the clock divider that is used to sample oscillator data.
* "0": sample clock is "clk_sys".
* "1": sample clock is "clk_sys"/2.
* ...
* "255": sample clock is "clk_sys"/256.
*/
#define CY_CRYPTO_DEF_TR_SAMPLE_CLOCK_DIV          (0UL)

/**
* Specifies the clock divider used to produce reduced bits.
* "0": 1 reduced bit is produced for each sample.
* "1": 1 reduced bit is produced for each 2 samples.
* ...
* "255": 1 reduced bit is produced for each 256 samples.
*
* The reduced bits are considered random bits and shifted into TR_RESULT0.DATA32.
*/
#define CY_CRYPTO_DEF_TR_RED_CLOCK_DIV                  (0UL)

/**
* Specifies an initialization delay: a number of removed/dropped samples before
* reduced bits are generated. This field should be programmed in the range [1, 255].
* After starting the oscillators, at least the first 2 samples should be
* removed/dropped to clear the state of internal synchronizers. In addition,
* it is advised to drop at least the second 2 samples from the oscillators
* (to circumvent the semi-predictable oscillator start-up behavior). This results
* in the default field value of "3". the field encoding is as follows:
* "0": 1 sample is dropped.
* "1": 2 samples are dropped.
* ...
* "255": 256 samples are dropped.
*
* The TR_INITIALIZED interrupt cause is set to '1', when the initialization delay is passed.
*/
#define CY_CRYPTO_DEF_TR_INIT_DELAY                        (3UL)

/**
* Specifies if the "von Neumann corrector" is disabled or enabled:
* '0': disabled.
* '1': enabled.
* The "von Neumann corrector" post-processes the reduced bits to remove a '0' or '1' bias.
* The corrector operates on reduced bit pairs ("oldest bit, newest bit"):
* "00": no bit is produced.
* "01": '0' bit is produced (oldest bit).
* "10": '1' bit is produced (oldest bit).
* "11": no bit is produced.
* NOTE: The corrector produces bits at a random pace and at a frequency that
* is 1/4 of the reduced bit frequency (reduced bits are processed in pairs,
* and half of the pairs do NOT produce a bit).
*/
#define CY_CRYPTO_DEF_TR_VON_NEUMANN_CORR            (1UL)

/**
* Specifies if the TRNG functionality is stopped on an adaptive proportion test
* detection (when HW sets INTR.TR_AP_DETECT to '1'):
* '0': Functionality is stopped (TR_CTL1 fields are set to '0' by HW).
* '1': Functionality is NOT stopped.
*/
#define CY_CRYPTO_DEF_TR_STOP_ON_AP_DETECT          (1UL)

/**
* Specifies if the TRNG functionality is stopped on a repetition count test detection
* (when HW sets INTR.TR_RC_DETECT to '1'):
* '0': Functionality is stopped (TR_CTL1 fields are set to '0' by HW).
* '1': Functionality is NOT stopped.
*/
#define CY_CRYPTO_DEF_TR_STOP_ON_RC_DETECT          (1UL)

/** FW sets this field to '1' to enable the ring oscillator with 11 inverters. */
#define CY_CRYPTO_DEF_TR_RO11_EN                              (1UL)

/** FW sets this field to '1' to enable the ring oscillator with 15 inverters. */
#define CY_CRYPTO_DEF_TR_RO15_EN                              (1UL)

/**
* FW sets this field to '1' to enable the fixed Galois ring oscillator
* with 15 inverters.
*/
#define CY_CRYPTO_DEF_TR_GARO15_EN                          (1UL)

/**
* FW sets this field to '1' to enable the programmable Galois ring oscillator with up
* to 31 inverters. The TR_GARO_CTL register specifies the programmable polynomial.
*/
#define CY_CRYPTO_DEF_TR_GARO31_EN             (1UL)

/** FW sets this field to '1' to enable the fixed Fibonacci ring oscillator with 15 inverters. */
#define CY_CRYPTO_DEF_TR_FIRO15_EN                          (1UL)

/**
* FW sets this field to '1' to enable the programmable Fibonacci ring oscillator
* with up to 31 inverters. The TR_FIRO_CTL register specifies the programmable polynomial.
*/
#define CY_CRYPTO_DEF_TR_FIRO31_EN                          (1UL)

/**
* The polynomial for programmable Galois ring oscillator. The polynomial is represented
* WITHOUT the high order bit (this bit is always assumed '1'). The polynomial should be aligned
* so that the more significant bits (bit 30 and down) contain the polynomial and the less
* significant bits (bit 0 and up) contain padding '0's.
*/
#define CY_CRYPTO_DEF_TR_GARO                                    (0x04c11db7)

/**
* The polynomial for the programmable Fibonacci ring oscillator. The polynomial is represented
* WITHOUT the high order bit (this bit is always assumed '1'). The polynomial should
* be aligned so that the more significant bits (bit 30 and down) contain the polynomial
* and the less significant bits (bit 0 and up) contain padding '0's.
*/
#define CY_CRYPTO_DEF_TR_FIRO                                    (0x04c11db7)

/**
* Selection of the bit stream:
* "0": DAS bit stream.
* "1": RED bit stream.
* "2": TR bit stream.
* "3": Undefined.
*/
#define CY_CRYPTO_DEF_TR_BITSTREAM_SEL                  (CY_CRYPTO_TRMON_BS_TR)

/**
* Adaptive proportion (AP) test enable:
* '0': Stopped.
* '1': Started.
*
* On AP detection, HW sets this field to '0' and sets INTR.TR_AP_DETECT to '1.
*/
#define CY_CRYPTO_DEF_TR_START_AP                            (0UL)

/**
* Repetition count (RC) test enable:
* '0': Disabled.
* '1': Enabled.
*
* On RC detection, HW sets this field to '0' and sets INTR.TR_RC_DETECT to '1.
*/
#define CY_CRYPTO_DEF_TR_START_RC                            (0UL)

/**
* Cut-off count (legal range is [1, 255]):
* "0": Illegal.
* "1": 1 repetition.
* ...
* "255": 255 repetitions.
*/
#define CY_CRYPTO_DEF_TR_CUTOFF_COUNT8                  (255UL)

/**
* Cut-off count (legal range is [1, 65535]).
* "0": Illegal.
* "1": 1 occurrence.
* ...
* "65535": 65535 occurrences.
*/
#define CY_CRYPTO_DEF_TR_CUTOFF_COUNT16                (65535UL)

/**
* The window size (minus 1) :
* "0": 1 bit.
* ...
* "65535": 65536 bits.
*/

#define CY_CRYPTO_DEF_TR_WINDOW_SIZE           (65535UL)


#endif /* #if (CPUSS_CRYPTO_TR == 1) */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXCRYPTO */

#endif /* #if !defined (CY_CRYPTO_CORE_TRNG_CONFIG_H) */


/* [] END OF FILE */
