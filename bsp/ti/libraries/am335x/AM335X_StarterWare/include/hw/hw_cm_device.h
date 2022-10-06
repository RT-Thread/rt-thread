

/**
 *  @Component:   CM
 *
 *  @Filename:    ../../CredDataBase/prcmCRED/cm_device_cred.h
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


#ifndef _HW_CM_DEVICE_H_
#define _HW_CM_DEVICE_H_


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

#define CM_DEVICE_CM_CLKOUT_CTRL   (0x0)

/**************************************************************************\ 
 * Field Definition Macros
\**************************************************************************/

/* CM_CLKOUT_CTRL */
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2DIV   (0x00000038u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2DIV_SHIFT   (0x00000003u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2DIV_DIV1   (0x0u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2DIV_DIV2   (0x1u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2DIV_DIV3   (0x2u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2DIV_DIV4   (0x3u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2DIV_DIV5   (0x4u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2DIV_DIV6   (0x5u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2DIV_DIV7   (0x6u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2DIV_DIV8   (0x7u)

#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2EN   (0x00000080u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2EN_SHIFT   (0x00000007u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2EN_DIS   (0x0u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2EN_EN   (0x1u)

#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2SOURCE   (0x00000007u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2SOURCE_SHIFT   (0x00000000u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2SOURCE_SEL0   (0x0u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2SOURCE_SEL1   (0x1u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2SOURCE_SEL2   (0x2u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2SOURCE_SEL4   (0x3u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2SOURCE_SEL5   (0x4u)



#endif
