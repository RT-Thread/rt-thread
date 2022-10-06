

/**
 *  @Component:   WDT
 *
 *  @Filename:    ../../CredDataBase/WDT_cred.h
 *
 ============================================================================ */
/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/



#ifndef _HW_WDT_H_
#define _HW_WDT_H_

#ifdef __cplusplus
extern "C" {
#endif


/***********************************************************************\
 * Register arrays Definition
\***********************************************************************/


/***********************************************************************\
 * Bundle arrays Definition
\***********************************************************************/


/***********************************************************************\
 * Bundles Definition
\***********************************************************************/



/*************************************************************************\
 * Registers Definition
\*************************************************************************/

#define WDT_WIDR   (0x0)
#define WDT_WDSC   (0x10)
#define WDT_WDST   (0x14)
#define WDT_WISR   (0x18)
#define WDT_WIER   (0x1C)
#define WDT_WWER   (0x20)
#define WDT_WCLR   (0x24)
#define WDT_WCRR   (0x28)
#define WDT_WLDR   (0x2C)
#define WDT_WTGR   (0x30)
#define WDT_WWPS   (0x34)
#define WDT_WDLY   (0x44)
#define WDT_WSPR   (0x48)
#define WDT_WIRQSTATRAW   (0x54)
#define WDT_WIRQSTAT   (0x58)
#define WDT_WIRQENSET   (0x5C)
#define WDT_WIRQENCLR   (0x60)

/**************************************************************************\ 
 * Field Definition Macros
\**************************************************************************/

/* WIDR */
#define WDT_WIDR_CUSTOM   (0x000000C0u)
#define WDT_WIDR_CUSTOM_SHIFT   (0x00000006u)

#define WDT_WIDR_FUNC   (0x0FFF0000u)
#define WDT_WIDR_FUNC_SHIFT   (0x00000010u)

#define WDT_WIDR_MAJOR   (0x00000700u)
#define WDT_WIDR_MAJOR_SHIFT   (0x00000008u)

#define WDT_WIDR_MINOR   (0x0000003Fu)
#define WDT_WIDR_MINOR_SHIFT   (0x00000000u)

#define WDT_WIDR_RTL   (0x0000F800u)
#define WDT_WIDR_RTL_SHIFT   (0x0000000Bu)

#define WDT_WIDR_SCHEME   (0xC0000000u)
#define WDT_WIDR_SCHEME_SHIFT   (0x0000001Eu)


/* WDSC */
#define WDT_WDSC_EMUFREE   (0x00000020u)
#define WDT_WDSC_EMUFREE_SHIFT   (0x00000005u)
#define WDT_WDSC_EMUFREE_TIMER_FREE   (0x1u)
#define WDT_WDSC_EMUFREE_TIMER_FROZEN   (0x0u)

#define WDT_WDSC_IDLEMODE   (0x00000018u)
#define WDT_WDSC_IDLEMODE_SHIFT   (0x00000003u)
#define WDT_WDSC_IDLEMODE_FORCEIDLE   (0x0u)
#define WDT_WDSC_IDLEMODE_NOIDLE   (0x1u)
#define WDT_WDSC_IDLEMODE_SMARTIDLE   (0x2u)
#define WDT_WDSC_IDLEMODE_SMARTIDLEWAKEUP   (0x3u)

#define WDT_WDSC_SOFTRESET   (0x00000002u)
#define WDT_WDSC_SOFTRESET_SHIFT   (0x00000001u)
#define WDT_WDSC_SOFTRESET_DONE   (0x0u)
#define WDT_WDSC_SOFTRESET_INITIATE   (0x1u)
#define WDT_WDSC_SOFTRESET_ONGOING   (0x1u)


/* WDST */
#define WDT_WDST_RESETDONE   (0x00000001u)
#define WDT_WDST_RESETDONE_SHIFT   (0x00000000u)
#define WDT_WDST_RESETDONE_COMPLETED   (0x1u)
#define WDT_WDST_RESETDONE_ONGOING   (0x0u)


/* WISR */
#define WDT_WISR_DLY_IT_FLAG   (0x00000002u)
#define WDT_WISR_DLY_IT_FLAG_SHIFT   (0x00000001u)
#define WDT_WISR_DLY_IT_FLAG_CLEAR   (0x1u)
#define WDT_WISR_DLY_IT_FLAG_NONE   (0x0u)
#define WDT_WISR_DLY_IT_FLAG_PENDING   (0x1u)

#define WDT_WISR_OVF_IT_FLAG   (0x00000001u)
#define WDT_WISR_OVF_IT_FLAG_SHIFT   (0x00000000u)
#define WDT_WISR_OVF_IT_FLAG_CLEAR   (0x1u)
#define WDT_WISR_OVF_IT_FLAG_NONE   (0x0u)
#define WDT_WISR_OVF_IT_FLAG_PENDING   (0x1u)


/* WIER */
#define WDT_WIER_DLY_IT_ENA   (0x00000002u)
#define WDT_WIER_DLY_IT_ENA_SHIFT   (0x00000001u)
#define WDT_WIER_DLY_IT_ENA_DISABLED   (0x0u)
#define WDT_WIER_DLY_IT_ENA_ENABLED   (0x1u)

#define WDT_WIER_OVF_IT_ENA   (0x00000001u)
#define WDT_WIER_OVF_IT_ENA_SHIFT   (0x00000000u)
#define WDT_WIER_OVF_IT_ENA_DISABLED   (0x0u)
#define WDT_WIER_OVF_IT_ENA_ENABLED   (0x1u)


/* WWER */
#define WDT_WWER_DLY_WK_ENA   (0x00000002u)
#define WDT_WWER_DLY_WK_ENA_SHIFT   (0x00000001u)
#define WDT_WWER_DLY_WK_ENA_DISABLED   (0x0u)
#define WDT_WWER_DLY_WK_ENA_ENABLED   (0x1u)

#define WDT_WWER_OVF_WK_ENA   (0x00000001u)
#define WDT_WWER_OVF_WK_ENA_SHIFT   (0x00000000u)
#define WDT_WWER_OVF_WK_ENA_DISABLED   (0x0u)
#define WDT_WWER_OVF_WK_ENA_ENABLED   (0x1u)


/* WCLR */
#define WDT_WCLR_PRE   (0x00000020u)
#define WDT_WCLR_PRE_SHIFT   (0x00000005u)
#define WDT_WCLR_PRE_DISABLED   (0x0u)
#define WDT_WCLR_PRE_ENABLED   (0x1u)

#define WDT_WCLR_PTV   (0x0000001Cu)
#define WDT_WCLR_PTV_SHIFT   (0x00000002u)


/* WCRR */
#define WDT_WCRR_TIMER_COUNTER   (0xFFFFFFFFu)
#define WDT_WCRR_TIMER_COUNTER_SHIFT   (0x00000000u)


/* WLDR */
#define WDT_WLDR_TIMER_LOAD   (0xFFFFFFFFu)
#define WDT_WLDR_TIMER_LOAD_SHIFT   (0x00000000u)


/* WTGR */
#define WDT_WTGR_TTGR_VALUE   (0xFFFFFFFFu)
#define WDT_WTGR_TTGR_VALUE_SHIFT   (0x00000000u)


/* WWPS */
#define WDT_WWPS_W_PEND_WCLR   (0x00000001u)
#define WDT_WWPS_W_PEND_WCLR_SHIFT   (0x00000000u)
#define WDT_WWPS_W_PEND_WCLR_PENDING   (0x1u)
#define WDT_WWPS_W_PEND_WCLR_READY   (0x0u)

#define WDT_WWPS_W_PEND_WCRR   (0x00000002u)
#define WDT_WWPS_W_PEND_WCRR_SHIFT   (0x00000001u)
#define WDT_WWPS_W_PEND_WCRR_PENDING   (0x1u)
#define WDT_WWPS_W_PEND_WCRR_READY   (0x0u)

#define WDT_WWPS_W_PEND_WDLY   (0x00000020u)
#define WDT_WWPS_W_PEND_WDLY_SHIFT   (0x00000005u)
#define WDT_WWPS_W_PEND_WDLY_PENDING   (0x1u)
#define WDT_WWPS_W_PEND_WDLY_READY   (0x0u)

#define WDT_WWPS_W_PEND_WLDR   (0x00000004u)
#define WDT_WWPS_W_PEND_WLDR_SHIFT   (0x00000002u)
#define WDT_WWPS_W_PEND_WLDR_PENDING   (0x1u)
#define WDT_WWPS_W_PEND_WLDR_READY   (0x0u)

#define WDT_WWPS_W_PEND_WSPR   (0x00000010u)
#define WDT_WWPS_W_PEND_WSPR_SHIFT   (0x00000004u)
#define WDT_WWPS_W_PEND_WSPR_PENDING   (0x1u)
#define WDT_WWPS_W_PEND_WSPR_READY   (0x0u)

#define WDT_WWPS_W_PEND_WTGR   (0x00000008u)
#define WDT_WWPS_W_PEND_WTGR_SHIFT   (0x00000003u)
#define WDT_WWPS_W_PEND_WTGR_PENDING   (0x1u)
#define WDT_WWPS_W_PEND_WTGR_READY   (0x0u)


/* WDLY */
#define WDT_WDLY_WDLY_VALUE   (0xFFFFFFFFu)
#define WDT_WDLY_WDLY_VALUE_SHIFT   (0x00000000u)


/* WSPR */
#define WDT_WSPR_WSPR_VALUE   (0xFFFFFFFFu)
#define WDT_WSPR_WSPR_VALUE_SHIFT   (0x00000000u)


/* WIRQSTATRAW */
#define WDT_WIRQSTATRAW_EVENT_DLY   (0x00000002u)
#define WDT_WIRQSTATRAW_EVENT_DLY_SHIFT   (0x00000001u)
#define WDT_WIRQSTATRAW_EVENT_DLY_NONE   (0x0u)
#define WDT_WIRQSTATRAW_EVENT_DLY_PENDING   (0x1u)
#define WDT_WIRQSTATRAW_EVENT_DLY_SET   (0x1u)

#define WDT_WIRQSTATRAW_EVENT_OVF   (0x00000001u)
#define WDT_WIRQSTATRAW_EVENT_OVF_SHIFT   (0x00000000u)
#define WDT_WIRQSTATRAW_EVENT_OVF_NONE   (0x0u)
#define WDT_WIRQSTATRAW_EVENT_OVF_PENDING   (0x1u)
#define WDT_WIRQSTATRAW_EVENT_OVF_SET   (0x1u)


/* WIRQSTAT */
#define WDT_WIRQSTAT_EVENT_DLY   (0x00000002u)
#define WDT_WIRQSTAT_EVENT_DLY_SHIFT   (0x00000001u)
#define WDT_WIRQSTAT_EVENT_DLY_CLEAR   (0x1u)
#define WDT_WIRQSTAT_EVENT_DLY_NONE   (0x0u)
#define WDT_WIRQSTAT_EVENT_DLY_PENDING   (0x1u)

#define WDT_WIRQSTAT_EVENT_OVF   (0x00000001u)
#define WDT_WIRQSTAT_EVENT_OVF_SHIFT   (0x00000000u)
#define WDT_WIRQSTAT_EVENT_OVF_CLEAR   (0x1u)
#define WDT_WIRQSTAT_EVENT_OVF_NONE   (0x0u)
#define WDT_WIRQSTAT_EVENT_OVF_PENDING   (0x1u)


/* WIRQENSET */
#define WDT_WIRQENSET_ENABLE_DLY   (0x00000002u)
#define WDT_WIRQENSET_ENABLE_DLY_SHIFT   (0x00000001u)
#define WDT_WIRQENSET_ENABLE_DLY_DISABLED   (0x0u)
#define WDT_WIRQENSET_ENABLE_DLY_ENABLE   (0x1u)
#define WDT_WIRQENSET_ENABLE_DLY_ENABLED   (0x1u)

#define WDT_WIRQENSET_ENABLE_OVF   (0x00000001u)
#define WDT_WIRQENSET_ENABLE_OVF_SHIFT   (0x00000000u)
#define WDT_WIRQENSET_ENABLE_OVF_DISABLED   (0x0u)
#define WDT_WIRQENSET_ENABLE_OVF_ENABLE   (0x1u)
#define WDT_WIRQENSET_ENABLE_OVF_ENABLED   (0x1u)


/* WIRQENCLR */
#define WDT_WIRQENCLR_ENABLE_DLY   (0x00000002u)
#define WDT_WIRQENCLR_ENABLE_DLY_SHIFT   (0x00000001u)
#define WDT_WIRQENCLR_ENABLE_DLY_DISABLE   (0x1u)
#define WDT_WIRQENCLR_ENABLE_DLY_DISABLED   (0x0u)
#define WDT_WIRQENCLR_ENABLE_DLY_ENABLED   (0x1u)

#define WDT_WIRQENCLR_ENABLE_OVF   (0x00000001u)
#define WDT_WIRQENCLR_ENABLE_OVF_SHIFT   (0x00000000u)
#define WDT_WIRQENCLR_ENABLE_OVF_DISABLE   (0x1u)
#define WDT_WIRQENCLR_ENABLE_OVF_DISABLED   (0x0u)
#define WDT_WIRQENCLR_ENABLE_OVF_ENABLED   (0x1u)



#ifdef __cplusplus
}
#endif

#endif
