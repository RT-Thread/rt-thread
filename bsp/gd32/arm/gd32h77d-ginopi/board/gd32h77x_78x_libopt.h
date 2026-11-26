/*!
    \file    gd32h77x_78x_libopt.h
    \brief   library optional for gd32h77x_78x

    \version 2026-06-18, V0.4.0, demo for GD32H77x_78x
*/

/*
    Copyright (c) 2026, GigaDevice Semiconductor Inc.

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

#ifndef GD32H77X_78X_LIBOPT_H
#define GD32H77X_78X_LIBOPT_H

#include "gd32h77x_78x_adc.h"
#include "gd32h77x_78x_axiim.h"
#include "gd32h77x_78x_can.h"
#include "gd32h77x_78x_cau.h"
#include "gd32h77x_78x_cmp.h"
#include "gd32h77x_78x_cpdm.h"
#include "gd32h77x_78x_crc.h"
#include "gd32h77x_78x_ctc.h"
#include "gd32h77x_78x_dac.h"
#include "gd32h77x_78x_dbg.h"
#include "gd32h77x_78x_dci.h"
#include "gd32h77x_78x_dma.h"
#if (defined(GD32H77X_78X_SUPPORT_DSI))
#include "gd32h77x_78x_dsi.h"
#endif /* (defined(GD32H77X_78X_SUPPORT_DSI)) */
#include "gd32h77x_78x_edim.h"
#include "gd32h77x_78x_edim_biss.h"
#include "gd32h77x_78x_edim_endat.h"
#include "gd32h77x_78x_edim_afmt.h"
#include "gd32h77x_78x_edim_tfmt.h"
#include "gd32h77x_78x_edim_hdsl.h"
#include "gd32h77x_78x_edout.h"
#include "gd32h77x_78x_enet.h"
#if (defined(GD32H77X_78X_SUPPORT_ESC))
#include "gd32h77x_78x_esc.h"
#endif /* (defined(GD32H77X_78X_SUPPORT_ESC)) */
#include "gd32h77x_78x_exmc.h"
#include "gd32h77x_78x_exti.h"
#include "gd32h77x_78x_fac.h"
#include "gd32h77x_78x_fft.h"
#include "gd32h77x_78x_fwdgt.h"
#include "gd32h77x_78x_gpio.h"
#include "gd32h77x_78x_gpsi.h"
#include "gd32h77x_78x_hau.h"
#include "gd32h77x_78x_hpdf.h"
#include "gd32h77x_78x_hwsem.h"
#include "gd32h77x_78x_i2c.h"
#include "gd32h77x_78x_ipa.h"
#include "gd32h77x_78x_lpdts.h"
#include "gd32h77x_78x_mdio.h"
#include "gd32h77x_78x_mdma.h"
#include "gd32h77x_78x_misc.h"
#include "gd32h77x_78x_nvmc.h"
#include "gd32h77x_78x_ospi.h"
#include "gd32h77x_78x_ospim.h"
#include "gd32h77x_78x_pkcau.h"
#include "gd32h77x_78x_pmu.h"
#include "gd32h77x_78x_rameccmu.h"
#include "gd32h77x_78x_rcu.h"
#include "gd32h77x_78x_rdcm.h"
#include "gd32h77x_78x_rspdif.h"
#include "gd32h77x_78x_rtc.h"
#include "gd32h77x_78x_rtdec.h"
#include "gd32h77x_78x_sai.h"
#include "gd32h77x_78x_sdio.h"
#include "gd32h77x_78x_spi.h"
#include "gd32h77x_78x_syscfg.h"
#include "gd32h77x_78x_timer.h"
#include "gd32h77x_78x_tli.h"
#include "gd32h77x_78x_tmu.h"
#include "gd32h77x_78x_trigsel.h"
#include "gd32h77x_78x_trng.h"
#include "gd32h77x_78x_usart.h"
#include "gd32h77x_78x_vref.h"
#include "gd32h77x_78x_wwdgt.h"

#endif /* GD32H77X_78X_LIBOPT_H */
