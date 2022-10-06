

/**
 *  @Component:   PRM
 *
 *  @Filename:    ../../CredDataBase/prcmCRED/prm_mpu_cred.h
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



#ifndef _HW_PRM_MPU_H_
#define _HW_PRM_MPU_H_


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

#define PRM_MPU_PM_MPU_PWRSTCTRL   (0x0)
#define PRM_MPU_PM_MPU_PWRSTST   (0x4)
#define PRM_MPU_RM_MPU_RSTST   (0x8)

/**************************************************************************\ 
 * Field Definition Macros
\**************************************************************************/

/* PM_MPU_PWRSTCTRL */
#define PRM_MPU_PM_MPU_PWRSTCTRL_LOGICRETSTATE   (0x00000004u)
#define PRM_MPU_PM_MPU_PWRSTCTRL_LOGICRETSTATE_SHIFT   (0x00000002u)
#define PRM_MPU_PM_MPU_PWRSTCTRL_LOGICRETSTATE_LOGIC_OFF   (0x0u)
#define PRM_MPU_PM_MPU_PWRSTCTRL_LOGICRETSTATE_LOGIC_RET   (0x1u)

#define PRM_MPU_PM_MPU_PWRSTCTRL_LOWPOWERSTATECHANGE   (0x00000010u)
#define PRM_MPU_PM_MPU_PWRSTCTRL_LOWPOWERSTATECHANGE_SHIFT   (0x00000004u)
#define PRM_MPU_PM_MPU_PWRSTCTRL_LOWPOWERSTATECHANGE_DIS   (0x0u)
#define PRM_MPU_PM_MPU_PWRSTCTRL_LOWPOWERSTATECHANGE_EN   (0x1u)

#define PRM_MPU_PM_MPU_PWRSTCTRL_MPU_L1_ONSTATE   (0x000C0000u)
#define PRM_MPU_PM_MPU_PWRSTCTRL_MPU_L1_ONSTATE_SHIFT   (0x00000012u)
#define PRM_MPU_PM_MPU_PWRSTCTRL_MPU_L1_ONSTATE_MEM_ON   (0x3u)

#define PRM_MPU_PM_MPU_PWRSTCTRL_MPU_L1_RETSTATE   (0x00400000u)
#define PRM_MPU_PM_MPU_PWRSTCTRL_MPU_L1_RETSTATE_SHIFT   (0x00000016u)

#define PRM_MPU_PM_MPU_PWRSTCTRL_MPU_L2_ONSTATE   (0x00300000u)
#define PRM_MPU_PM_MPU_PWRSTCTRL_MPU_L2_ONSTATE_SHIFT   (0x00000014u)
#define PRM_MPU_PM_MPU_PWRSTCTRL_MPU_L2_ONSTATE_MEM_ON   (0x3u)

#define PRM_MPU_PM_MPU_PWRSTCTRL_MPU_L2_RETSTATE   (0x00800000u)
#define PRM_MPU_PM_MPU_PWRSTCTRL_MPU_L2_RETSTATE_SHIFT   (0x00000017u)

#define PRM_MPU_PM_MPU_PWRSTCTRL_MPU_RAM_ONSTATE   (0x00030000u)
#define PRM_MPU_PM_MPU_PWRSTCTRL_MPU_RAM_ONSTATE_SHIFT   (0x00000010u)
#define PRM_MPU_PM_MPU_PWRSTCTRL_MPU_RAM_ONSTATE_MEM_OFF   (0x0u)
#define PRM_MPU_PM_MPU_PWRSTCTRL_MPU_RAM_ONSTATE_MEM_ON   (0x3u)
#define PRM_MPU_PM_MPU_PWRSTCTRL_MPU_RAM_ONSTATE_RESERVED   (0x2u)

#define PRM_MPU_PM_MPU_PWRSTCTRL_MPU_RAM_RETSTATE   (0x01000000u)
#define PRM_MPU_PM_MPU_PWRSTCTRL_MPU_RAM_RETSTATE_SHIFT   (0x00000018u)

#define PRM_MPU_PM_MPU_PWRSTCTRL_POWERSTATE   (0x00000003u)
#define PRM_MPU_PM_MPU_PWRSTCTRL_POWERSTATE_SHIFT   (0x00000000u)
#define PRM_MPU_PM_MPU_PWRSTCTRL_POWERSTATE_OFF   (0x0u)
#define PRM_MPU_PM_MPU_PWRSTCTRL_POWERSTATE_ON   (0x3u)
#define PRM_MPU_PM_MPU_PWRSTCTRL_POWERSTATE_RESERVED   (0x2u)
#define PRM_MPU_PM_MPU_PWRSTCTRL_POWERSTATE_RET   (0x1u)


/* PM_MPU_PWRSTST */
#define PRM_MPU_PM_MPU_PWRSTST_INTRANSITION   (0x00100000u)
#define PRM_MPU_PM_MPU_PWRSTST_INTRANSITION_SHIFT   (0x00000014u)
#define PRM_MPU_PM_MPU_PWRSTST_INTRANSITION_NO   (0x0u)
#define PRM_MPU_PM_MPU_PWRSTST_INTRANSITION_ONGOING   (0x1u)

#define PRM_MPU_PM_MPU_PWRSTST_LOGICSTATEST   (0x00000004u)
#define PRM_MPU_PM_MPU_PWRSTST_LOGICSTATEST_SHIFT   (0x00000002u)
#define PRM_MPU_PM_MPU_PWRSTST_LOGICSTATEST_OFF   (0x0u)
#define PRM_MPU_PM_MPU_PWRSTST_LOGICSTATEST_ON   (0x1u)

#define PRM_MPU_PM_MPU_PWRSTST_MPU_L1_STATEST   (0x000000C0u)
#define PRM_MPU_PM_MPU_PWRSTST_MPU_L1_STATEST_SHIFT   (0x00000006u)
#define PRM_MPU_PM_MPU_PWRSTST_MPU_L1_STATEST_MEM_OFF   (0x0u)
#define PRM_MPU_PM_MPU_PWRSTST_MPU_L1_STATEST_MEM_ON   (0x3u)
#define PRM_MPU_PM_MPU_PWRSTST_MPU_L1_STATEST_RESERVED   (0x2u)

#define PRM_MPU_PM_MPU_PWRSTST_MPU_L2_STATEST   (0x00000300u)
#define PRM_MPU_PM_MPU_PWRSTST_MPU_L2_STATEST_SHIFT   (0x00000008u)
#define PRM_MPU_PM_MPU_PWRSTST_MPU_L2_STATEST_MEM_OFF   (0x0u)
#define PRM_MPU_PM_MPU_PWRSTST_MPU_L2_STATEST_MEM_ON   (0x3u)
#define PRM_MPU_PM_MPU_PWRSTST_MPU_L2_STATEST_RESERVED   (0x2u)

#define PRM_MPU_PM_MPU_PWRSTST_MPU_RAM_STATEST   (0x00000030u)
#define PRM_MPU_PM_MPU_PWRSTST_MPU_RAM_STATEST_SHIFT   (0x00000004u)
#define PRM_MPU_PM_MPU_PWRSTST_MPU_RAM_STATEST_MEM_OFF   (0x0u)
#define PRM_MPU_PM_MPU_PWRSTST_MPU_RAM_STATEST_MEM_ON   (0x3u)
#define PRM_MPU_PM_MPU_PWRSTST_MPU_RAM_STATEST_RESERVED   (0x2u)

#define PRM_MPU_PM_MPU_PWRSTST_POWERSTATEST   (0x00000003u)
#define PRM_MPU_PM_MPU_PWRSTST_POWERSTATEST_SHIFT   (0x00000000u)
#define PRM_MPU_PM_MPU_PWRSTST_POWERSTATEST_OFF   (0x0u)
#define PRM_MPU_PM_MPU_PWRSTST_POWERSTATEST_ON   (0x3u)
#define PRM_MPU_PM_MPU_PWRSTST_POWERSTATEST_RET   (0x1u)


/* RM_MPU_RSTST */
#define PRM_MPU_RM_MPU_RSTST_EMULATION_MPU_RST   (0x00000020u)
#define PRM_MPU_RM_MPU_RSTST_EMULATION_MPU_RST_SHIFT   (0x00000005u)
#define PRM_MPU_RM_MPU_RSTST_EMULATION_MPU_RST_RESET_NO   (0x0u)
#define PRM_MPU_RM_MPU_RSTST_EMULATION_MPU_RST_RESET_YES   (0x1u)

#define PRM_MPU_RM_MPU_RSTST_ICECRUSHER_MPU_RST   (0x00000040u)
#define PRM_MPU_RM_MPU_RSTST_ICECRUSHER_MPU_RST_SHIFT   (0x00000006u)
#define PRM_MPU_RM_MPU_RSTST_ICECRUSHER_MPU_RST_RESET_NO   (0x0u)
#define PRM_MPU_RM_MPU_RSTST_ICECRUSHER_MPU_RST_RESET_YES   (0x1u)



#endif
