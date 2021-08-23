/*!
    \file  usbd_pwr.c
    \brief USB device power management driver

    \version 2014-12-26, V1.0.0, firmware for GD32F10x
    \version 2017-06-20, V2.0.0, firmware for GD32F10x
    \version 2018-07-31, V2.1.0, firmware for GD32F10x
*/

/*
    Copyright (c) 2018, GigaDevice Semiconductor Inc.

    All rights reserved.

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

#include "usbd_pwr.h"

#ifdef USBD_LOWPWR_MODE_ENABLE
static void  lowpower_mode_exit (void);
#endif /* USBD_LOWPWR_MODE_ENABLE */

__IO uint8_t g_ESOF_count = 0U;
__IO uint8_t g_suspend_enabled = 1U;
__IO uint8_t g_remote_wakeup_on = 0U;

#ifdef LPM_ENABLED
extern __IO uint32_t L1_resume;
#endif /* LPM_ENABLED */

/*!
    \brief      USB wakeup first operation is to wakeup mcu
    \param[in]  none
    \param[out] none
    \retval     none
*/
void  resume_mcu (void)
{
    /* clear low_power mode bit in USBD_CTL */
    USBD_REG_SET(USBD_CTL, USBD_REG_GET(USBD_CTL) & (~CTL_LOWM));

#ifdef USBD_LOWPWR_MODE_ENABLE

    /* restore normal operations */
    lowpower_mode_exit();

#endif /* USBD_LOWPWR_MODE_ENABLE */

    /* clear SETSPS bit */
    USBD_REG_SET(USBD_CTL, USBD_REG_GET(USBD_CTL) & (~CTL_SETSPS));
}

#ifdef USBD_LOWPWR_MODE_ENABLE

/*!
    \brief      restore system clocks and power while exiting suspend mode
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void  lowpower_mode_exit (void)
{
    /* restore system clock */

    /* enable HSE */
    rcu_osci_on(RCU_HXTAL);

    /* wait till HSE is ready */
    while(RESET == rcu_flag_get(RCU_FLAG_HXTALSTB));

    /* enable PLL */
    rcu_osci_on(RCU_PLL_CK);

    /* wait till PLL is ready */
    while(RESET == rcu_flag_get(RCU_FLAG_PLLSTB));

    /* select PLL as system clock source */
    rcu_system_clock_source_config(RCU_CKSYSSRC_PLL);

    /* wait till PLL is used as system clock source */
    while(0x08 != rcu_system_clock_source_get());

    /* low power sleep on exit disabled */
    system_lowpower_reset(SCB_LPM_DEEPSLEEP);
}

#endif /* USBD_LOWPWR_MODE_ENABLE */

/*!
    \brief      set USB device to suspend mode
    \param[in]  none
    \param[out] none
    \retval     none
*/
void  usbd_suspend (void)
{
    /* set usb module to suspend and low-power mode */
    USBD_REG_SET(USBD_CTL, USBD_REG_GET(USBD_CTL) | CTL_SETSPS | CTL_LOWM);

#ifdef USBD_LOWPWR_MODE_ENABLE

    /* check wakeup flag is set */
    if (0 == (USBD_REG_GET(USBD_INTF) & INTF_WKUPIF)) {
        /* enter DEEP_SLEEP mode with LDO in low power mode */
        pmu_to_deepsleepmode(PMU_LDO_LOWPOWER, WFI_CMD);
    } else {
        /* clear wakeup interrupt flag */
        USBD_REG_SET(USBD_INTF, CLR_WKUPIF);

        /* clear set_suspend flag */
        USBD_REG_SET(USBD_CTL, USBD_REG_GET(USBD_CTL) & ~CTL_SETSPS);
    }

#endif /* USBD_LOWPWR_MODE_ENABLE */
}

/*!
    \brief      start to remote wakeup
    \param[in]  none
    \param[out] none
    \retval     none
*/
void  usbd_remote_wakeup_active(void)
{
    resume_mcu();

#ifdef LPM_ENABLED
    USBD_REG_SET(USBD_CTL, USBD_REG_GET(USBD_CTL) | CTL_L1RSREQ);

    L1_resume = 1U;
#else
    g_remote_wakeup_on = 1U;

    g_ESOF_count = 15U;
    USBD_REG_SET(USBD_CTL, USBD_REG_GET(USBD_CTL) | CTL_RSREQ);
#endif /* LPM_ENABLED */
}
