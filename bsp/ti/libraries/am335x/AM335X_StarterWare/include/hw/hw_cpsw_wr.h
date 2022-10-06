

/**
 *  @Component:   CPSW
 *
 *  @Filename:    cpsw_wr_cred.h
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



#ifndef _HW_CPSW_WR_H_
#define _HW_CPSW_WR_H_

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

#define CPSW_WR_IDVER   (0x0)
#define CPSW_WR_SOFT_RESET   (0x04)
#define CPSW_WR_CONTROL   (0x08)
#define CPSW_WR_INT_CONTROL   (0x0c)
#define CPSW_WR_C_RX_THRESH_EN(n)   (0x10 + (n * 16))
#define CPSW_WR_C_RX_EN(n)   (0x14 + (n * 16))
#define CPSW_WR_C_TX_EN(n)   (0x18 + (n * 16))
#define CPSW_WR_C_MISC_EN(n)   (0x1c + (n * 16))
#define CPSW_WR_C_RX_THRESH_STAT(n)   (0x40 + (n * 16))
#define CPSW_WR_C_RX_STAT(n)   (0x44 + (n * 16))
#define CPSW_WR_C_TX_STAT(n)   (0x48 + (n * 16))
#define CPSW_WR_C_MISC_STAT(n)   (0x4c + (n * 16))
#define CPSW_WR_C_RX_IMAX(n)   (0x70 + (n * 8))
#define CPSW_WR_C_TX_IMAX(n)   (0x74 + (n * 8))
#define CPSW_WR_RGMII_CTL   (0x88)

/**************************************************************************\
 * Field Definition Macros
\**************************************************************************/

/* IDVER */
#define CPSW_WR_IDVER_CUSTOM   (0x000000C0u)
#define CPSW_WR_IDVER_CUSTOM_SHIFT   (0x00000006u)

#define CPSW_WR_IDVER_FUNCTION   (0x0FFF0000u)
#define CPSW_WR_IDVER_FUNCTION_SHIFT   (0x00000010u)

#define CPSW_WR_IDVER_MAJOR   (0x00000700u)
#define CPSW_WR_IDVER_MAJOR_SHIFT   (0x00000008u)

#define CPSW_WR_IDVER_MINOR   (0x0000003Fu)
#define CPSW_WR_IDVER_MINOR_SHIFT   (0x00000000u)

#define CPSW_WR_IDVER_RTL   (0x0000F800u)
#define CPSW_WR_IDVER_RTL_SHIFT   (0x0000000Bu)

#define CPSW_WR_IDVER_SCHEME   (0xFFF00000u)
#define CPSW_WR_IDVER_SCHEME_SHIFT   (0x00000014u)


/* SOFT_RESET */
#define CPSW_WR_SOFT_RESET_SOFT_RESET   (0x00000001u)
#define CPSW_WR_SOFT_RESET_SOFT_RESET_SHIFT   (0x00000000u)


/* CONTROL */
#define CPSW_WR_CONTROL_MMR_RESET      (0x0000000Au)
#define CPSW_WR_CONTROL_MMR_IDLEMODE   (0x00000003u)
#define CPSW_WR_CONTROL_MMR_IDLEMODE_SHIFT   (0x00000000u)

#define CPSW_WR_CONTROL_MMR_STDBYMODE   (0x0000000Cu)
#define CPSW_WR_CONTROL_MMR_STDBYMODE_SHIFT   (0x00000002u)


/* INT_CONTROL */
#define CPSW_WR_INT_CONTROL_INT_PACE_EN   (0x003F0000u)
#define CPSW_WR_INT_CONTROL_INT_PACE_EN_SHIFT   (0x00000010u)

#define CPSW_WR_INT_CONTROL_INT_PRESCALE   (0x00000FFFu)
#define CPSW_WR_INT_CONTROL_INT_PRESCALE_SHIFT   (0x00000000u)

#define CPSW_WR_INT_CONTROL_INT_TEST   (0x80000000u)
#define CPSW_WR_INT_CONTROL_INT_TEST_SHIFT   (0x0000001Fu)


/* C0_RX_THRESH_EN */
#define CPSW_WR_C0_RX_THRESH_EN_C0_RX_THRESH_EN   (0x000000FFu)
#define CPSW_WR_C0_RX_THRESH_EN_C0_RX_THRESH_EN_SHIFT   (0x00000000u)


/* C0_RX_EN */
#define CPSW_WR_C0_RX_EN_C0_RX_EN   (0x000000FFu)
#define CPSW_WR_C0_RX_EN_C0_RX_EN_SHIFT   (0x00000000u)


/* C0_TX_EN */
#define CPSW_WR_C0_TX_EN_C0_TX_EN   (0x000000FFu)
#define CPSW_WR_C0_TX_EN_C0_TX_EN_SHIFT   (0x00000000u)


/* C0_MISC_EN */
#define CPSW_WR_C0_MISC_EN_C0_MISC_EN   (0x0000001Fu)
#define CPSW_WR_C0_MISC_EN_C0_MISC_EN_SHIFT   (0x00000000u)


/* C1_RX_THRESH_EN */
#define CPSW_WR_C1_RX_THRESH_EN_C1_RX_THRESH_EN   (0x000000FFu)
#define CPSW_WR_C1_RX_THRESH_EN_C1_RX_THRESH_EN_SHIFT   (0x00000000u)


/* C1_RX_EN */
#define CPSW_WR_C1_RX_EN_C1_RX_EN   (0x000000FFu)
#define CPSW_WR_C1_RX_EN_C1_RX_EN_SHIFT   (0x00000000u)


/* C1_TX_EN */
#define CPSW_WR_C1_TX_EN_C1_TX_EN   (0x000000FFu)
#define CPSW_WR_C1_TX_EN_C1_TX_EN_SHIFT   (0x00000000u)


/* C1_MISC_EN */
#define CPSW_WR_C1_MISC_EN_C1_MISC_EN   (0x0000001Fu)
#define CPSW_WR_C1_MISC_EN_C1_MISC_EN_SHIFT   (0x00000000u)


/* C2_RX_THRESH_EN */
#define CPSW_WR_C2_RX_THRESH_EN_C2_RX_THRESH_EN   (0x000000FFu)
#define CPSW_WR_C2_RX_THRESH_EN_C2_RX_THRESH_EN_SHIFT   (0x00000000u)


/* C2_RX_EN */
#define CPSW_WR_C2_RX_EN_C2_RX_EN   (0x000000FFu)
#define CPSW_WR_C2_RX_EN_C2_RX_EN_SHIFT   (0x00000000u)


/* C2_TX_EN */
#define CPSW_WR_C2_TX_EN_C2_TX_EN   (0x000000FFu)
#define CPSW_WR_C2_TX_EN_C2_TX_EN_SHIFT   (0x00000000u)


/* C2_MISC_EN */
#define CPSW_WR_C2_MISC_EN_C2_MISC_EN   (0x0000001Fu)
#define CPSW_WR_C2_MISC_EN_C2_MISC_EN_SHIFT   (0x00000000u)


/* C0_RX_THRESH_STAT */
#define CPSW_WR_C0_RX_THRESH_STAT_C0_RX_THRESH_STAT   (0x000000FFu)
#define CPSW_WR_C0_RX_THRESH_STAT_C0_RX_THRESH_STAT_SHIFT   (0x00000000u)


/* C0_RX_STAT */
#define CPSW_WR_C0_RX_STAT_C0_RX_STAT   (0x000000FFu)
#define CPSW_WR_C0_RX_STAT_C0_RX_STAT_SHIFT   (0x00000000u)


/* C0_TX_STAT */
#define CPSW_WR_C0_TX_STAT_C0_TX_STAT   (0x000000FFu)
#define CPSW_WR_C0_TX_STAT_C0_TX_STAT_SHIFT   (0x00000000u)


/* C0_MISC_STAT */
#define CPSW_WR_C0_MISC_STAT_C0_MISC_STAT   (0x0000001Fu)
#define CPSW_WR_C0_MISC_STAT_C0_MISC_STAT_SHIFT   (0x00000000u)


/* C1_RX_THRESH_STAT */
#define CPSW_WR_C1_RX_THRESH_STAT_C1_RX_THRESH_STAT   (0x000000FFu)
#define CPSW_WR_C1_RX_THRESH_STAT_C1_RX_THRESH_STAT_SHIFT   (0x00000000u)


/* C1_RX_STAT */
#define CPSW_WR_C1_RX_STAT_C1_RX_STAT   (0x000000FFu)
#define CPSW_WR_C1_RX_STAT_C1_RX_STAT_SHIFT   (0x00000000u)


/* C1_TX_STAT */
#define CPSW_WR_C1_TX_STAT_C1_TX_STAT   (0x000000FFu)
#define CPSW_WR_C1_TX_STAT_C1_TX_STAT_SHIFT   (0x00000000u)


/* C1_MISC_STAT */
#define CPSW_WR_C1_MISC_STAT_C1_MISC_STAT   (0x0000001Fu)
#define CPSW_WR_C1_MISC_STAT_C1_MISC_STAT_SHIFT   (0x00000000u)


/* C2_RX_THRESH_STAT */
#define CPSW_WR_C2_RX_THRESH_STAT_C2_RX_THRESH_STAT   (0x000000FFu)
#define CPSW_WR_C2_RX_THRESH_STAT_C2_RX_THRESH_STAT_SHIFT   (0x00000000u)


/* C2_RX_STAT */
#define CPSW_WR_C2_RX_STAT_C2_RX_STAT   (0x000000FFu)
#define CPSW_WR_C2_RX_STAT_C2_RX_STAT_SHIFT   (0x00000000u)


/* C2_TX_STAT */
#define CPSW_WR_C2_TX_STAT_C2_TX_STAT   (0x000000FFu)
#define CPSW_WR_C2_TX_STAT_C2_TX_STAT_SHIFT   (0x00000000u)


/* C2_MISC_STAT */
#define CPSW_WR_C2_MISC_STAT_C2_MISC_STAT   (0x0000001Fu)
#define CPSW_WR_C2_MISC_STAT_C2_MISC_STAT_SHIFT   (0x00000000u)


/* C0_RX_IMAX */
#define CPSW_WR_C0_RX_IMAX_C0_RX_IMAX   (0x0000003Fu)
#define CPSW_WR_C0_RX_IMAX_C0_RX_IMAX_SHIFT   (0x00000000u)


/* C0_TX_IMAX */
#define CPSW_WR_C0_TX_IMAX_C0_TX_IMAX   (0x0000003Fu)
#define CPSW_WR_C0_TX_IMAX_C0_TX_IMAX_SHIFT   (0x00000000u)


/* C1_RX_IMAX */
#define CPSW_WR_C1_RX_IMAX_C1_RX_IMAX   (0x0000003Fu)
#define CPSW_WR_C1_RX_IMAX_C1_RX_IMAX_SHIFT   (0x00000000u)


/* C1_TX_IMAX */
#define CPSW_WR_C1_TX_IMAX_C1_TX_IMAX   (0x0000003Fu)
#define CPSW_WR_C1_TX_IMAX_C1_TX_IMAX_SHIFT   (0x00000000u)


/* C2_RX_IMAX */
#define CPSW_WR_C2_RX_IMAX_C2_RX_IMAX   (0x0000003Fu)
#define CPSW_WR_C2_RX_IMAX_C2_RX_IMAX_SHIFT   (0x00000000u)


/* C2_TX_IMAX */
#define CPSW_WR_C2_TX_IMAX_C2_TX_IMAX   (0x0000003Fu)
#define CPSW_WR_C2_TX_IMAX_C2_TX_IMAX_SHIFT   (0x00000000u)


/* RGMII_CTL */
#define CPSW_WR_RGMII_CTL_RGMII1_FULLDUPLEX   (0x00000008u)
#define CPSW_WR_RGMII_CTL_RGMII1_FULLDUPLEX_SHIFT   (0x00000003u)

#define CPSW_WR_RGMII_CTL_RGMII1_LINK   (0x00000001u)
#define CPSW_WR_RGMII_CTL_RGMII1_LINK_SHIFT   (0x00000000u)

#define CPSW_WR_RGMII_CTL_RGMII1_SPEED   (0x00000006u)
#define CPSW_WR_RGMII_CTL_RGMII1_SPEED_SHIFT   (0x00000001u)

#define CPSW_WR_RGMII_CTL_RGMII2_FULLDUPLEX   (0x00000080u)
#define CPSW_WR_RGMII_CTL_RGMII2_FULLDUPLEX_SHIFT   (0x00000007u)

#define CPSW_WR_RGMII_CTL_RGMII2_LINK   (0x00000010u)
#define CPSW_WR_RGMII_CTL_RGMII2_LINK_SHIFT   (0x00000004u)

#define CPSW_WR_RGMII_CTL_RGMII2_SPEED   (0x00000060u)
#define CPSW_WR_RGMII_CTL_RGMII2_SPEED_SHIFT   (0x00000005u)



#ifdef __cplusplus
}
#endif

#endif
