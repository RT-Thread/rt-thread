/*!
    \file    gd32e50x_libopt.h
    \brief   library optional for gd32e50x

    \version 2023-12-31, V1.4.0, firmware for GD32E50x
*/

/*
    Copyright (c) 2023, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#ifndef GD32E50X_LIBOPT_H
#define GD32E50X_LIBOPT_H

#ifndef GD32EPRT

#include "gd32e50x_adc.h"
#include "gd32e50x_bkp.h"
#include "gd32e50x_can.h"
#include "gd32e50x_crc.h"
#include "gd32e50x_ctc.h"
#include "gd32e50x_dac.h"
#include "gd32e50x_dbg.h"
#include "gd32e50x_dma.h"
#include "gd32e50x_exmc.h"
#include "gd32e50x_exti.h"
#include "gd32e50x_fmc.h"
#include "gd32e50x_fwdgt.h"
#include "gd32e50x_gpio.h"
#include "gd32e50x_shrtimer.h"
#include "gd32e50x_i2c.h"
#include "gd32e50x_misc.h"
#include "gd32e50x_pmu.h"
#include "gd32e50x_rcu.h"
#include "gd32e50x_rtc.h"
#include "gd32e50x_spi.h"
#include "gd32e50x_timer.h"
#include "gd32e50x_usart.h"
#include "gd32e50x_wwdgt.h"
#include "gd32e50x_sqpi.h"

#if defined (GD32E50X_CL) || defined (GD32E508)
#include "gd32e50x_enet.h"
#include "gd32e50x_tmu.h"
#include "gd32e50x_cmp.h"
#else /* GD32E50X_CL or GD32E508 */
#include "gd32e50x_sdio.h"
#endif /* GD32E50X_CL or GD32E508 */

#else /* GD32EPRT */
#include "gd32e50x_adc.h"
#include "gd32e50x_bkp.h"
#include "gd32e50x_crc.h"
#include "gd32e50x_ctc.h"
#include "gd32e50x_dac.h"
#include "gd32e50x_dbg.h"
#include "gd32e50x_dma.h"
#include "gd32e50x_enet.h"
#include "gd32e50x_exmc.h"
#include "gd32e50x_exti.h"
#include "gd32e50x_fmc.h"
#include "gd32e50x_fwdgt.h"
#include "gd32e50x_gpio.h"
#include "gd32e50x_i2c.h"
#include "gd32e50x_misc.h"
#include "gd32e50x_pmu.h"
#include "gd32e50x_rcu.h"
#include "gd32e50x_rtc.h"
#include "gd32e50x_spi.h"
#include "gd32e50x_timer.h"
#include "gd32e50x_usart.h"
#include "gd32e50x_wwdgt.h"
#include "gd32e50x_sqpi.h"

#endif /* GD32EPRT */

#endif /* GD32E50X_LIBOPT_H */
