

/**
 *  @Component:   PRM
 *
 *  @Filename:    ../../CredDataBase/prcmCRED/prm_cefuse_cred.h
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



#ifndef _HW_PRM_CEFUSE_H_
#define _HW_PRM_CEFUSE_H_


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

#define PRM_CEFUSE_PM_CEFUSE_PWRSTCTRL   (0x0)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST   (0x4)

/**************************************************************************\ 
 * Field Definition Macros
\**************************************************************************/

/* PM_CEFUSE_PWRSTCTRL */
#define PRM_CEFUSE_PM_CEFUSE_PWRSTCTRL_LOWPOWERSTATECHANGE   (0x00000010u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTCTRL_LOWPOWERSTATECHANGE_SHIFT   (0x00000004u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTCTRL_LOWPOWERSTATECHANGE_DIS   (0x0u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTCTRL_LOWPOWERSTATECHANGE_EN   (0x1u)

#define PRM_CEFUSE_PM_CEFUSE_PWRSTCTRL_POWERSTATE   (0x00000003u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTCTRL_POWERSTATE_SHIFT   (0x00000000u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTCTRL_POWERSTATE_INACT   (0x2u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTCTRL_POWERSTATE_OFF   (0x0u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTCTRL_POWERSTATE_ON   (0x3u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTCTRL_POWERSTATE_RESERVED   (0x1u)


/* PM_CEFUSE_PWRSTST */
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_INTRANSITION   (0x00100000u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_INTRANSITION_SHIFT   (0x00000014u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_INTRANSITION_NO   (0x0u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_INTRANSITION_ONGOING   (0x1u)

#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_LASTPOWERSTATEENTERED   (0x03000000u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_LASTPOWERSTATEENTERED_SHIFT   (0x00000018u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_LASTPOWERSTATEENTERED_OFF   (0x0u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_LASTPOWERSTATEENTERED_ON   (0x1u)

#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_LOGICSTATEST   (0x00000004u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_LOGICSTATEST_SHIFT   (0x00000002u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_LOGICSTATEST_OFF   (0x0u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_LOGICSTATEST_ON   (0x1u)

#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_POWERSTATEST   (0x00000003u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_POWERSTATEST_SHIFT   (0x00000000u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_POWERSTATEST_INACTIVE   (0x2u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_POWERSTATEST_OFF   (0x0u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_POWERSTATEST_ON   (0x3u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_POWERSTATEST_RET   (0x1u)



#endif
