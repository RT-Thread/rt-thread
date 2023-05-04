/***************************************************************************//**
* \file cyip_headers.h
*
* \brief
* Common header file to be included by all IP definition headers
*
********************************************************************************
* \copyright
* (c) (2016-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
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

#ifndef _CYIP_HEADERS_H_
#define _CYIP_HEADERS_H_

#include <stdint.h>

/* These are CMSIS-CORE defines used for structure members definitions */
#ifndef     __IM
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#endif
#ifndef     __OM
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#endif
#ifndef     __IOM
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */
#endif

#endif /* _CYIP_HEADERS_H_ */


/* [] END OF FILE */
