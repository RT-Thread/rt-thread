

/**
 *  @Component:   CM
 *
 *  @Filename:    ../../CredDataBase/prcmCRED/cm_cefuse_cred.h
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



#ifndef _HW_CM_CEFUSE_H_
#define _HW_CM_CEFUSE_H_


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

#define CM_CEFUSE_CLKSTCTRL   (0x0)
#define CM_CEFUSE_CEFUSE_CLKCTRL   (0x20)

/**************************************************************************\ 
 * Field Definition Macros
\**************************************************************************/

/* CLKSTCTRL */
#define CM_CEFUSE_CLKSTCTRL_CLKACTIVITY_CUST_EFUSE_SYS_CLK   (0x00000200u)
#define CM_CEFUSE_CLKSTCTRL_CLKACTIVITY_CUST_EFUSE_SYS_CLK_SHIFT   (0x00000009u)
#define CM_CEFUSE_CLKSTCTRL_CLKACTIVITY_CUST_EFUSE_SYS_CLK_ACT   (0x1u)
#define CM_CEFUSE_CLKSTCTRL_CLKACTIVITY_CUST_EFUSE_SYS_CLK_INACT   (0x0u)

#define CM_CEFUSE_CLKSTCTRL_CLKACTIVITY_L4_CEFUSE_GICLK   (0x00000100u)
#define CM_CEFUSE_CLKSTCTRL_CLKACTIVITY_L4_CEFUSE_GICLK_SHIFT   (0x00000008u)
#define CM_CEFUSE_CLKSTCTRL_CLKACTIVITY_L4_CEFUSE_GICLK_ACT   (0x1u)
#define CM_CEFUSE_CLKSTCTRL_CLKACTIVITY_L4_CEFUSE_GICLK_INACT   (0x0u)

#define CM_CEFUSE_CLKSTCTRL_CLKTRCTRL   (0x00000003u)
#define CM_CEFUSE_CLKSTCTRL_CLKTRCTRL_SHIFT   (0x00000000u)
#define CM_CEFUSE_CLKSTCTRL_CLKTRCTRL_HW_AUTO   (0x3u)
#define CM_CEFUSE_CLKSTCTRL_CLKTRCTRL_NO_SLEEP   (0x0u)
#define CM_CEFUSE_CLKSTCTRL_CLKTRCTRL_SW_SLEEP   (0x1u)
#define CM_CEFUSE_CLKSTCTRL_CLKTRCTRL_SW_WKUP   (0x2u)


/* CEFUSE_CLKCTRL */
#define CM_CEFUSE_CEFUSE_CLKCTRL_IDLEST   (0x00030000u)
#define CM_CEFUSE_CEFUSE_CLKCTRL_IDLEST_SHIFT   (0x00000010u)
#define CM_CEFUSE_CEFUSE_CLKCTRL_IDLEST_DISABLE   (0x3u)
#define CM_CEFUSE_CEFUSE_CLKCTRL_IDLEST_FUNC   (0x0u)
#define CM_CEFUSE_CEFUSE_CLKCTRL_IDLEST_IDLE   (0x2u)
#define CM_CEFUSE_CEFUSE_CLKCTRL_IDLEST_TRANS   (0x1u)

#define CM_CEFUSE_CEFUSE_CLKCTRL_MODULEMODE   (0x00000003u)
#define CM_CEFUSE_CEFUSE_CLKCTRL_MODULEMODE_SHIFT   (0x00000000u)
#define CM_CEFUSE_CEFUSE_CLKCTRL_MODULEMODE_DISABLED   (0x0u)
#define CM_CEFUSE_CEFUSE_CLKCTRL_MODULEMODE_ENABLE   (0x2u)
#define CM_CEFUSE_CEFUSE_CLKCTRL_MODULEMODE_RESERVED   (0x3u)
#define CM_CEFUSE_CEFUSE_CLKCTRL_MODULEMODE_RESERVED_1   (0x1u)



#endif
