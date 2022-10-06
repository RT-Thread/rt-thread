

/**
 *  @Component:   PRM
 *
 *  @Filename:    ../../CredDataBase/prcmCRED/prm_wkup_cred.h
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



#ifndef _HW_PRM_WKUP_H_
#define _HW_PRM_WKUP_H_


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

#define PRM_WKUP_RM_WKUP_RSTCTRL   (0x0)
#define PRM_WKUP_PM_WKUP_PWRSTCTRL   (0x4)
#define PRM_WKUP_PM_WKUP_PWRSTST   (0x8)
#define PRM_WKUP_RM_WKUP_RSTST   (0xc)

/**************************************************************************\ 
 * Field Definition Macros
\**************************************************************************/

/* RM_WKUP_RSTCTRL */
#define PRM_WKUP_RM_WKUP_RSTCTRL_WKUP_M3_LRST   (0x00000008u)
#define PRM_WKUP_RM_WKUP_RSTCTRL_WKUP_M3_LRST_SHIFT   (0x00000003u)
#define PRM_WKUP_RM_WKUP_RSTCTRL_WKUP_M3_LRST_ASSERT   (0x1u)
#define PRM_WKUP_RM_WKUP_RSTCTRL_WKUP_M3_LRST_CLEAR   (0x0u)


/* PM_WKUP_PWRSTCTRL */
#define PRM_WKUP_PM_WKUP_PWRSTCTRL_LOGICRETSTATE   (0x00000008u)
#define PRM_WKUP_PM_WKUP_PWRSTCTRL_LOGICRETSTATE_SHIFT   (0x00000003u)
#define PRM_WKUP_PM_WKUP_PWRSTCTRL_LOGICRETSTATE_LOGIC_OFF   (0x0u)
#define PRM_WKUP_PM_WKUP_PWRSTCTRL_LOGICRETSTATE_LOGIC_RET   (0x1u)

#define PRM_WKUP_PM_WKUP_PWRSTCTRL_LOWPOWERSTATECHANGE   (0x00000010u)
#define PRM_WKUP_PM_WKUP_PWRSTCTRL_LOWPOWERSTATECHANGE_SHIFT   (0x00000004u)
#define PRM_WKUP_PM_WKUP_PWRSTCTRL_LOWPOWERSTATECHANGE_DIS   (0x0u)
#define PRM_WKUP_PM_WKUP_PWRSTCTRL_LOWPOWERSTATECHANGE_EN   (0x1u)


/* PM_WKUP_PWRSTST */
#define PRM_WKUP_PM_WKUP_PWRSTST_DEBUGSS_MEM_STATEST   (0x00060000u)
#define PRM_WKUP_PM_WKUP_PWRSTST_DEBUGSS_MEM_STATEST_SHIFT   (0x00000011u)
#define PRM_WKUP_PM_WKUP_PWRSTST_DEBUGSS_MEM_STATEST_MEM_OFF   (0x0u)
#define PRM_WKUP_PM_WKUP_PWRSTST_DEBUGSS_MEM_STATEST_MEM_ON   (0x3u)
#define PRM_WKUP_PM_WKUP_PWRSTST_DEBUGSS_MEM_STATEST_RESERVED   (0x2u)

#define PRM_WKUP_PM_WKUP_PWRSTST_INTRANSITION   (0x00100000u)
#define PRM_WKUP_PM_WKUP_PWRSTST_INTRANSITION_SHIFT   (0x00000014u)
#define PRM_WKUP_PM_WKUP_PWRSTST_INTRANSITION_NO   (0x0u)
#define PRM_WKUP_PM_WKUP_PWRSTST_INTRANSITION_ONGOING   (0x1u)

#define PRM_WKUP_PM_WKUP_PWRSTST_LOGICSTATEST   (0x00000004u)
#define PRM_WKUP_PM_WKUP_PWRSTST_LOGICSTATEST_SHIFT   (0x00000002u)
#define PRM_WKUP_PM_WKUP_PWRSTST_LOGICSTATEST_OFF   (0x0u)
#define PRM_WKUP_PM_WKUP_PWRSTST_LOGICSTATEST_ON   (0x1u)


/* RM_WKUP_RSTST */
#define PRM_WKUP_RM_WKUP_RSTST_EMULATION_M3_RST   (0x00000040u)
#define PRM_WKUP_RM_WKUP_RSTST_EMULATION_M3_RST_SHIFT   (0x00000006u)
#define PRM_WKUP_RM_WKUP_RSTST_EMULATION_M3_RST_RESET_NO   (0x0u)
#define PRM_WKUP_RM_WKUP_RSTST_EMULATION_M3_RST_RESET_YES   (0x1u)

#define PRM_WKUP_RM_WKUP_RSTST_ICECRUSHER_M3_RST   (0x00000080u)
#define PRM_WKUP_RM_WKUP_RSTST_ICECRUSHER_M3_RST_SHIFT   (0x00000007u)
#define PRM_WKUP_RM_WKUP_RSTST_ICECRUSHER_M3_RST_RESET_NO   (0x0u)
#define PRM_WKUP_RM_WKUP_RSTST_ICECRUSHER_M3_RST_RESET_YES   (0x1u)

#define PRM_WKUP_RM_WKUP_RSTST_WKUP_M3_LRST   (0x00000020u)
#define PRM_WKUP_RM_WKUP_RSTST_WKUP_M3_LRST_SHIFT   (0x00000005u)
#define PRM_WKUP_RM_WKUP_RSTST_WKUP_M3_LRST_RESET_NO   (0x0u)
#define PRM_WKUP_RM_WKUP_RSTST_WKUP_M3_LRST_RESET_YES   (0x1u)



#endif
