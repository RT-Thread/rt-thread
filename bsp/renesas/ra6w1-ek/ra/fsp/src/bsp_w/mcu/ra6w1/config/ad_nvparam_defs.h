/**
 ****************************************************************************************
 *
 * @file ad_nvparam_defs.h
 *
 * @brief NV-Parameters definitions
 *
 * Copyright (c) 2023-2024 Renesas Electronics. All rights reserved.
 *
 * This software ("Software") is owned by Renesas Electronics.
 *
 * By using this Software you agree that Renesas Electronics retains all
 * intellectual property and proprietary rights in and to this Software and any
 * use, reproduction, disclosure or distribution of the Software without express
 * written permission or a license agreement from Renesas Electronics is
 * strictly prohibited. This Software is solely for use on or in conjunction
 * with Renesas Electronics products.
 *
 * EXCEPT AS OTHERWISE PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, THE
 * SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. EXCEPT AS OTHERWISE
 * PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, IN NO EVENT SHALL
 * RENESAS ELECTRONICS BE LIABLE FOR ANY DIRECT, SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THE SOFTWARE.
 *
 ****************************************************************************************
 */

/*
 * DO NOT MODIFY THIS FILE!!!
 *
 * NV-Parameters configuration shall be done in platform_nvparam.h!!!
 *
 */

#ifndef AD_NVPARAM_DEFS_H_
#define AD_NVPARAM_DEFS_H_

#ifndef IN_AD_NVPARAM_C

/*
 * If this is included outside of ad_nvparam.c, we just define empty macros so nothing but tag
 * definitions are created from platform_nvparam.h
 */
#define NVPARAM_AREA(NAME, PARTITION)
#define NVPARAM_PARAM(TAGNAME, LENGTH)
#define NVPARAM_VARPARAM(TAGNAME, LENGTH)
#define NVPARAM_AREA_END()

#else

/*
 * If this is included inside of ad_nvparam.c, we will create proper configuration structure.
 */

/*
 * First we create configurations of each area - this will create "area_XXX" symbol for each defined
 * area in platform_nvparam.h. It contains all parameters defined for given area.
 */
#define NVPARAM_AREA(NAME, PARTITION) \
        static /*const*/ parameter_t area_ ## NAME[] = {
#define NVPARAM_PARAM(TAGNAME, LENGTH) \
                { \
                        .name = TAGNAME, \
                        .attr.flags = 0, \
                        .attr.length = LENGTH, \
                },
#define NVPARAM_VARPARAM(TAGNAME, LENGTH) \
                { \
                        .name = TAGNAME, \
                        .attr.flags = FLAG_VARIABLE_LEN, \
                        .attr.length = LENGTH, \
                },
#define NVPARAM_AREA_END() \
        };

#undef PLATFORM_NVPARAM_H_
#if (dg_configNVPARAM_APP_AREA == 2)
 #undef APP_NVPARAM_H_
 #if defined(dg_configADNVPARAM_PROJ_FILE)
 #include dg_configADNVPARAM_PROJ_FILE
 #else
 #error "dg_configADNVPARAM_PROJ_FILE is not exist !!"
 #endif
#else
 #include "platform_nvparam.h"
#endif


/*
 * Next, using the same platform_nvparam.h, we define list of areas. Each has proper attributes set
 * and pointer to corresponding area structure.
 */
#undef NVPARAM_AREA
#undef NVPARAM_PARAM
#undef NVPARAM_VARPARAM
#undef NVPARAM_AREA_END
#define NVPARAM_AREA(NAME, PARTITION) \
        { \
                .name = #NAME, \
                .parameters = area_ ## NAME, \
                .num_parameters = sizeof(area_ ## NAME) / sizeof(area_ ## NAME[0]), \
        },
#define NVPARAM_PARAM(TAGNAME, LENGTH)
#define NVPARAM_VARPARAM(TAGNAME, LENGTH)
#define NVPARAM_AREA_END()

static const area_t areas[] =
{
#undef PLATFORM_NVPARAM_H_
#if (dg_configNVPARAM_APP_AREA == 2)
 #undef APP_NVPARAM_H_
 #if defined(dg_configADNVPARAM_PROJ_FILE)
 #include dg_configADNVPARAM_PROJ_FILE
 #else
 #error "dg_configADNVPARAM_PROJ_FILE is not exist !!"
 #endif
#else
 #include "platform_nvparam.h"
#endif
};

#define num_areas (sizeof(areas) / sizeof(areas[0]))

#endif /* IN_AD_NVPARAM_C */

#endif /* AD_NVPARAM_DEFS_H_ */
