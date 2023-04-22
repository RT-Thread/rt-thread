/***************************************************************************//**
* \file cy_device_headers.h
*
* \brief
* Common header file to be included by the drivers.
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

#ifndef _CY_DEVICE_HEADERS_H_
#define _CY_DEVICE_HEADERS_H_

#if defined (XMC7100_F100K1088)
    #include "xmc7100_f100k1088.h"
#elif defined (XMC7100_F100K2112)
    #include "xmc7100_f100k2112.h"
#elif defined (XMC7100_F100K4160)
    #include "xmc7100_f100k4160.h"
#elif defined (XMC7100D_F100K2112)
    #include "xmc7100d_f100k2112.h"
#elif defined (XMC7100D_F100K4160)
    #include "xmc7100d_f100k4160.h"
#elif defined (XMC7100_F144K2112)
    #include "xmc7100_f144k2112.h"
#elif defined (XMC7100_F144K4160)
    #include "xmc7100_f144k4160.h"
#elif defined (XMC7100D_F144K2112)
    #include "xmc7100d_f144k2112.h"
#elif defined (XMC7100D_F144K4160)
    #include "xmc7100d_f144k4160.h"
#elif defined (XMC7100_F176K4160)
    #include "xmc7100_f176k4160.h"
#elif defined (XMC7100D_F176K4160)
    #include "xmc7100d_f176k4160.h"
#elif defined (XMC7100_E272K4160)
    #include "xmc7100_e272k4160.h"
#elif defined (XMC7100D_E272K4160)
    #include "xmc7100d_e272k4160.h"
#elif defined (XMC7200_F176K8384)
    #include "xmc7200_f176k8384.h"
#elif defined (XMC7200D_F176K8384)
    #include "xmc7200d_f176k8384.h"
#elif defined (XMC7200_E272K8384)
    #include "xmc7200_e272k8384.h"
#elif defined (XMC7200D_E272K8384)
    #include "xmc7200d_e272k8384.h"
#elif defined (CYT3BB5CES)
    #include "cyt3bb5ces.h"
#elif defined (CYT3BB5CEE)
    #include "cyt3bb5cee.h"
#elif defined (CYT3BB7CES)
    #include "cyt3bb7ces.h"
#elif defined (CYT3BB7CEE)
    #include "cyt3bb7cee.h"
#elif defined (CYT3BB8CES)
    #include "cyt3bb8ces.h"
#elif defined (CYT3BB8CEE)
    #include "cyt3bb8cee.h"
#elif defined (CYT3BBBCES)
    #include "cyt3bbbces.h"
#elif defined (CYT3BBBCEE)
    #include "cyt3bbbcee.h"
#elif defined (CYT4BB5CES)
    #include "cyt4bb5ces.h"
#elif defined (CYT4BB5CEE)
    #include "cyt4bb5cee.h"
#elif defined (CYT4BB7CES)
    #include "cyt4bb7ces.h"
#elif defined (CYT4BB7CEE)
    #include "cyt4bb7cee.h"
#elif defined (CYT4BB8CES)
    #include "cyt4bb8ces.h"
#elif defined (CYT4BB8CEE)
    #include "cyt4bb8cee.h"
#elif defined (CYT4BBBCES)
    #include "cyt4bbbces.h"
#elif defined (CYT4BBBCEE)
    #include "cyt4bbbcee.h"
#elif defined (CYT4BF8CES)
    #include "cyt4bf8ces.h"
#elif defined (CYT4BF8CEE)
    #include "cyt4bf8cee.h"
#elif defined (CYT4BF8CDS)
    #include "cyt4bf8cds.h"
#elif defined (CYT4BF8CDE)
    #include "cyt4bf8cde.h"
#elif defined (CYT4BFBCJS)
    #include "cyt4bfbcjs.h"
#elif defined (CYT4BFBCJE)
    #include "cyt4bfbcje.h"
#elif defined (CYT4BFBCHS)
    #include "cyt4bfbchs.h"
#elif defined (CYT4BFBCHE)
    #include "cyt4bfbche.h"
#elif defined (CYT4BFCCJS)
    #include "cyt4bfccjs.h"
#elif defined (CYT4BFCCJE)
    #include "cyt4bfccje.h"
#elif defined (CYT4BFCCHS)
    #include "cyt4bfcchs.h"
#elif defined (CYT4BFCCHE)
    #include "cyt4bfcche.h"
#else
    #error Undefined part number
#endif

#endif /* _CY_DEVICE_HEADERS_H_ */


/* [] END OF FILE */
