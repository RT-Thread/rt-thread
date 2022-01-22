/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2010-11-13     weety     first version
 */

#include "dm36x.h"


/* ------------------------------------------------------------------------ *
 *  psc_change_state( id, state )                                           *
 *      id    = Domain #ID                                                  *
 *      state = ( ENABLE, DISABLE, SYNCRESET, RESET )                       *
 *              (   =3  ,   =2   ,    =1    ,   =0  )                       *
 * ------------------------------------------------------------------------ */
void psc_change_state(int id, int state)
{
    rt_uint32_t mdstat, mdctl;

    if (id > DAVINCI_DM365_LPSC_KALEIDO)
        return;

    mdstat = PSC_MDSTAT_BASE + (id * 4);
    mdctl = PSC_MDCTL_BASE + (id * 4);

    /*
     *  Step 0 - Ignore request if the state is already set as is
     */
    if ((readl(mdstat) & 0x1f) == state)
        return;

    /*
     *  Step 1 - Wait for PTSTAT.GOSTAT to clear
     */
    while (readl(PSC_PTSTAT) & 1) ;

    /*
     *  Step 2 - Set MDCTLx.NEXT to new state
     */
    writel(readl(mdctl) & (~0x1f), mdctl);
    writel(readl(mdctl) | state, mdctl);

    /*
     *  Step 3 - Start power transition ( set PTCMD.GO to 1 )
     */
    writel(readl(PSC_PTCMD) | 1, PSC_PTCMD);

    /*
     *  Step 4 - Wait for PTSTAT.GOSTAT to clear
     */
    while (readl(PSC_PTSTAT) & 1) ;
}

