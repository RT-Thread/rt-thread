

/**
 *  @Component:   CPSW
 *
 *  @Filename:    cpsw_sl_cred.h
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


#ifndef _HW_CPSW_SL_H_
#define _HW_CPSW_SL_H_

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

#define CPSW_SL_IDVER   (0x0)
#define CPSW_SL_MACCONTROL   (0x4)
#define CPSW_SL_MACSTATUS   (0x8)
#define CPSW_SL_SOFT_RESET   (0xc)
#define CPSW_SL_RX_MAXLEN  (0x10)
#define CPSW_SL_BOFFTEST  (0x14)
#define CPSW_SL_RX_PAUSE   (0x18)
#define CPSW_SL_TX_PAUSE   (0x1c)
#define CPSW_SL_EMCONTROL   (0x20)
#define CPSW_SL_RX_PRI_MAP   (0x24)
#define CPSW_SL_TX_GAP   (0x28)

/**************************************************************************\
 * Field Definition Macros
\**************************************************************************/

/* SL1_IDVER */
#define CPSW_SL_IDVER_IDENT   (0xFFFF0000u)
#define CPSW_SL_IDVER_IDENT_SHIFT   (0x00000010u)

#define CPSW_SL_IDVER_X   (0x00000700u)
#define CPSW_SL_IDVER_X_SHIFT   (0x00000008u)

#define CPSW_SL_IDVER_Y   (0x000000FFu)
#define CPSW_SL_IDVER_Y_SHIFT   (0x00000000u)

#define CPSW_SL_IDVER_Z   (0x0000F800u)
#define CPSW_SL_IDVER_Z_SHIFT   (0x0000000Bu)


/* SL1_MACCONTROL */
#define CPSW_SL_MACCONTROL_CMD_IDLE   (0x00000800u)
#define CPSW_SL_MACCONTROL_CMD_IDLE_SHIFT   (0x0000000Bu)

#define CPSW_SL_MACCONTROL_EXT_EN   (0x00040000u)
#define CPSW_SL_MACCONTROL_EXT_EN_SHIFT   (0x00000012u)

#define CPSW_SL_MACCONTROL_FULLDUPLEX   (0x00000001u)
#define CPSW_SL_MACCONTROL_FULLDUPLEX_SHIFT   (0x00000000u)

#define CPSW_SL_MACCONTROL_GIG   (0x00000080u)
#define CPSW_SL_MACCONTROL_GIG_SHIFT   (0x00000007u)

#define CPSW_SL_MACCONTROL_GIG_FORCE   (0x00020000u)
#define CPSW_SL_MACCONTROL_GIG_FORCE_SHIFT   (0x00000011u)

#define CPSW_SL_MACCONTROL_GMII_EN   (0x00000020u)
#define CPSW_SL_MACCONTROL_GMII_EN_SHIFT   (0x00000005u)

#define CPSW_SL_MACCONTROL_IFCTL_A   (0x00008000u)
#define CPSW_SL_MACCONTROL_IFCTL_A_SHIFT   (0x0000000Fu)

#define CPSW_SL_MACCONTROL_IFCTL_B   (0x00010000u)
#define CPSW_SL_MACCONTROL_IFCTL_B_SHIFT   (0x00000010u)

#define CPSW_SL_MACCONTROL_LOOPBACK   (0x00000002u)
#define CPSW_SL_MACCONTROL_LOOPBACK_SHIFT   (0x00000001u)

#define CPSW_SL_MACCONTROL_MTEST   (0x00000004u)
#define CPSW_SL_MACCONTROL_MTEST_SHIFT   (0x00000002u)

#define CPSW_SL_MACCONTROL_RX_CEF_EN   (0x00400000u)
#define CPSW_SL_MACCONTROL_RX_CEF_EN_SHIFT   (0x00000016u)

#define CPSW_SL_MACCONTROL_RX_CMF_EN   (0x01000000u)
#define CPSW_SL_MACCONTROL_RX_CMF_EN_SHIFT   (0x00000018u)

#define CPSW_SL_MACCONTROL_RX_CSF_EN   (0x00800000u)
#define CPSW_SL_MACCONTROL_RX_CSF_EN_SHIFT   (0x00000017u)

#define CPSW_SL_MACCONTROL_RX_FLOW_EN   (0x00000008u)
#define CPSW_SL_MACCONTROL_RX_FLOW_EN_SHIFT   (0x00000003u)

#define CPSW_SL_MACCONTROL_TX_FLOW_EN   (0x00000010u)
#define CPSW_SL_MACCONTROL_TX_FLOW_EN_SHIFT   (0x00000004u)

#define CPSW_SL_MACCONTROL_TX_PACE   (0x00000040u)
#define CPSW_SL_MACCONTROL_TX_PACE_SHIFT   (0x00000006u)

#define CPSW_SL_MACCONTROL_TX_SHORT_GAP_EN   (0x00000400u)
#define CPSW_SL_MACCONTROL_TX_SHORT_GAP_EN_SHIFT   (0x0000000Au)

#define CPSW_SL_MACCONTROL_TX_SHORT_GAP_LIM_EN   (0x00200000u)
#define CPSW_SL_MACCONTROL_TX_SHORT_GAP_LIM_EN_SHIFT   (0x00000015u)


/* SL1_MACSTATUS */
#define CPSW_SL_MACSTATUS_EXT_FULLDUPLEX   (0x00000008u)
#define CPSW_SL_MACSTATUS_EXT_FULLDUPLEX_SHIFT   (0x00000003u)

#define CPSW_SL_MACSTATUS_EXT_GIG   (0x00000010u)
#define CPSW_SL_MACSTATUS_EXT_GIG_SHIFT   (0x00000004u)

#define CPSW_SL_MACSTATUS_IDLE   (0x80000000u)
#define CPSW_SL_MACSTATUS_IDLE_SHIFT   (0x0000001Fu)

#define CPSW_SL_MACSTATUS_RX_FLOW_ACT   (0x00000002u)
#define CPSW_SL_MACSTATUS_RX_FLOW_ACT_SHIFT   (0x00000001u)

#define CPSW_SL_MACSTATUS_TX_FLOW_ACT   (0x00000001u)
#define CPSW_SL_MACSTATUS_TX_FLOW_ACT_SHIFT   (0x00000000u)


/* SL1_SOFT_RESET */
#define CPSW_SL_SOFT_RESET_SOFT_RESET   (0x00000001u)
#define CPSW_SL_SOFT_RESET_SOFT_RESET_SHIFT   (0x00000000u)


/* SL1_RX_MAXLEN */
#define CPSW_SL_RX_MAXLEN_RX_MAXLEN   (0x00003FFFu)
#define CPSW_SL_RX_MAXLEN_RX_MAXLEN_SHIFT   (0x00000000u)


/* SL1_BOFFTEST */
#define CPSW_SL_BOFFTEST_COLL_COUNT   (0x0000F000u)
#define CPSW_SL_BOFFTEST_COLL_COUNT_SHIFT   (0x0000000Cu)

#define CPSW_SL_BOFFTEST_PACEVAL   (0x7C000000u)
#define CPSW_SL_BOFFTEST_PACEVAL_SHIFT   (0x0000001Au)

#define CPSW_SL_BOFFTEST_RNDNUM   (0x03FF0000u)
#define CPSW_SL_BOFFTEST_RNDNUM_SHIFT   (0x00000010u)

#define CPSW_SL_BOFFTEST_TX_BACKOFF   (0x000003FFu)
#define CPSW_SL_BOFFTEST_TX_BACKOFF_SHIFT   (0x00000000u)


/* SL1_EMCONTROL */
#define CPSW_SL_EMCONTROL_FREE   (0x00000001u)
#define CPSW_SL_EMCONTROL_FREE_SHIFT   (0x00000000u)

#define CPSW_SL_EMCONTROL_SOFT   (0x00000002u)
#define CPSW_SL_EMCONTROL_SOFT_SHIFT   (0x00000001u)


/* SL1_RX_PRI_MAP */
#define CPSW_SL_RX_PRI_MAP_PRI0   (0x00000007u)
#define CPSW_SL_RX_PRI_MAP_PRI0_SHIFT   (0x00000000u)

#define CPSW_SL_RX_PRI_MAP_PRI1   (0x00000070u)
#define CPSW_SL_RX_PRI_MAP_PRI1_SHIFT   (0x00000004u)

#define CPSW_SL_RX_PRI_MAP_PRI2   (0x00000700u)
#define CPSW_SL_RX_PRI_MAP_PRI2_SHIFT   (0x00000008u)

#define CPSW_SL_RX_PRI_MAP_PRI3   (0x00007000u)
#define CPSW_SL_RX_PRI_MAP_PRI3_SHIFT   (0x0000000Cu)

#define CPSW_SL_RX_PRI_MAP_PRI4   (0x00070000u)
#define CPSW_SL_RX_PRI_MAP_PRI4_SHIFT   (0x00000010u)

#define CPSW_SL_RX_PRI_MAP_PRI5   (0x00700000u)
#define CPSW_SL_RX_PRI_MAP_PRI5_SHIFT   (0x00000014u)

#define CPSW_SL_RX_PRI_MAP_PRI6   (0x07000000u)
#define CPSW_SL_RX_PRI_MAP_PRI6_SHIFT   (0x00000018u)

#define CPSW_SL_RX_PRI_MAP_PRI7   (0x70000000u)
#define CPSW_SL_RX_PRI_MAP_PRI7_SHIFT   (0x0000001Cu)




#ifdef __cplusplus
}
#endif

#endif
