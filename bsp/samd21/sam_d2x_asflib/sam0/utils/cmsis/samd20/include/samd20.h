/**
 * \file
 *
 * \brief Header file for SAMD20
 *
 * Copyright (c) 2013-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef _SAMD20_
#define _SAMD20_

/**
 * \defgroup SAMD20_definitions SAMD20 Device Definitions
 * \brief SAMD20 CMSIS Definitions.
 */

#if defined(__SAMD20E14__) || defined(__ATSAMD20E14__)
#include "samd20e14.h"
#elif defined(__SAMD20E15__) || defined(__ATSAMD20E15__)
#include "samd20e15.h"
#elif defined(__SAMD20E16__) || defined(__ATSAMD20E16__)
#include "samd20e16.h"
#elif defined(__SAMD20E17__) || defined(__ATSAMD20E17__)
#include "samd20e17.h"
#elif defined(__SAMD20E18__) || defined(__ATSAMD20E18__)
#include "samd20e18.h"
#elif defined(__SAMD20G14__) || defined(__ATSAMD20G14__)
#include "samd20g14.h"
#elif defined(__SAMD20G15__) || defined(__ATSAMD20G15__)
#include "samd20g15.h"
#elif defined(__SAMD20G16__) || defined(__ATSAMD20G16__)
#include "samd20g16.h"
#elif defined(__SAMD20G17__) || defined(__ATSAMD20G17__)
#include "samd20g17.h"
#elif defined(__SAMD20G17U__) || defined(__ATSAMD20G17U__)
#include "samd20g17u.h"
#elif defined(__SAMD20G18__) || defined(__ATSAMD20G18__)
#include "samd20g18.h"
#elif defined(__SAMD20G18U__) || defined(__ATSAMD20G18U__)
#include "samd20g18u.h"
#elif defined(__SAMD20J14__) || defined(__ATSAMD20J14__)
#include "samd20j14.h"
#elif defined(__SAMD20J15__) || defined(__ATSAMD20J15__)
#include "samd20j15.h"
#elif defined(__SAMD20J16__) || defined(__ATSAMD20J16__)
#include "samd20j16.h"
#elif defined(__SAMD20J17__) || defined(__ATSAMD20J17__)
#include "samd20j17.h"
#elif defined(__SAMD20J18__) || defined(__ATSAMD20J18__)
#include "samd20j18.h"
#else
  #error Library does not support the specified device.
#endif

#endif /* _SAMD20_ */
