/***************************************************************************//**
* \file cyhal_wdt_impl.h
*
* \brief
* CAT1 specific implementation for WDT API.
*
********************************************************************************
* \copyright
* Copyright 2019-2021 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#pragma once

/**
* \addtogroup group_hal_impl_wdt WDT (Watchdog Timer)
* \ingroup group_hal_impl
* \{
* The CAT1 WDT is only capable of supporting certain timeout ranges below its maximum timeout.
* As a result, any unsupported timeouts given to the HAL WDT are rounded up to the nearest supported value.
* The following table describes the unsupported ranges and the timeout values they are rounded to.
*
* <table class="doxtable">
*   <tr><th>Range (ms)</th><th>Rounded Timeout (ms)</th></tr>
*   <tr>
*     <td>3001 - 3999</td>
*     <td>4000</td>
*   </tr>
*   <tr>
*     <td>1501 - 1999</td>
*     <td>2000</td>
*   </tr>
*   <tr>
*     <td>751 - 999</td>
*     <td>1000</td>
*   </tr>
*   <tr>
*     <td>376 - 499</td>
*     <td>500</td>
*   </tr>
*   <tr>
*     <td>188 - 249</td>
*     <td>250</td>
*   </tr>
*   <tr>
*     <td>94 - 124</td>
*     <td>125</td>
*   </tr>
*   <tr>
*     <td>47 - 62</td>
*     <td>63</td>
*   </tr>
*   <tr>
*     <td>24 - 31</td>
*     <td>32</td>
*   </tr>
*   <tr>
*     <td>12 - 15</td>
*     <td>16</td>
*   </tr>
*   <tr>
*     <td>6 - 7</td>
*     <td>8</td>
*   </tr>
*   <tr>
*     <td>3 - 3</td>
*     <td>4</td>
*   </tr>
* </table>
* \} group_hal_impl_wdt
*/

#include "cyhal_wdt_impl_common.h"

#if (defined(CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) || defined(CY_IP_MXS40SSRSS)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/**
* \cond INTERNAL
*/

// (2^16 * 3) * .030518 ms
/** Maximum WDT timeout in milliseconds */
#define _CYHAL_WDT_MAX_TIMEOUT_MS 6000

/** Maximum number of ignore bits */
#define _CYHAL_WDT_MAX_IGNORE_BITS 12

/** \endcond */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif // defined(CY_IP_MXS40SRSS) || defined(CY_IP_MXS40SSRSS)
