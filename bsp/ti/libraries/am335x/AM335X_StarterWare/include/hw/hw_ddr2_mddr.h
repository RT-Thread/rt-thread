/** ============================================================================
 *   \file  hw_ddr2_mddr.h
 *
 *   \brief This file contains the Register Descriptions for DDR2/MDDR
 *
 *  ============================================================================
 */

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



#ifndef _HW_DDR2_MDDR_H_
#define _HW_DDR2_MDDR_H_

#ifdef __cplusplus
extern "C" {
#endif

#define DDR2_MDDR_REVID		(0x0)
#define DDR2_MDDR_SDRSTAT	(0x4)
#define DDR2_MDDR_SDCR		(0x8)
#define DDR2_MDDR_SDRCR		(0xC)
#define DDR2_MDDR_SDTIMR1	(0x10)
#define DDR2_MDDR_SDTIMR2	(0x14)
#define DDR2_MDDR_SDCR2		(0x1C)
#define DDR2_MDDR_PBBPR		(0x20)
#define DDR2_MDDR_PC1		(0x40)
#define DDR2_MDDR_PC2		(0x44)
#define DDR2_MDDR_PCC		(0x48)
#define DDR2_MDDR_PCMRS		(0x4C)
#define DDR2_MDDR_PCT		(0x50)
#define DDR2_MDDR_IRR		(0xC0)
#define DDR2_MDDR_IMR		(0xC4)
#define DDR2_MDDR_IMSR		(0xC8)
#define DDR2_MDDR_IMCR		(0xCC)
#define DDR2_MDDR_DRPYC1R	(0xE4)


/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

/* REVID */

#define DDR2_MDDR_REVID_ID         (0xFFFFFFFFu)
#define DDR2_MDDR_REVID_ID_SHIFT        (0x00000000u)

/* SDRSTAT */
#define DDR2_MDDR_SDRSTAT_DUALCLK  (0x40000000u)
#define DDR2_MDDR_SDRSTAT_DUALCLK_SHIFT (0x0000001Eu)
#define DDR2_MDDR_SDRSTAT_PHYRDY   (0x00000004u)
#define DDR2_MDDR_SDRSTAT_PHYRDY_SHIFT  (0x00000002u)

/* SDCR */
#define DDR2_MDDR_SDCR_DDR2TERM1   (0x08000000u)
#define DDR2_MDDR_SDCR_DDR2TERM1_SHIFT  (0x0000001Bu)
/*----DDR2TERM1 Tokens----*/
/* Tokens shown below should be used in conjunction with tokens for DDR2TERM0 to
 * generate the required temination resistor settings.                          
 * For example: 
 * To disable termination the required value is 00 (binary), which would
 * require DDR2TERM0 to be 0 and DDR2TERM1 to be 0. This could be generated as
 * shown below:
 * ((DDR2_MDDR_SDCR_DDR2TERM0_CLEAR | DDR2_MDDR_SDCR_DDR2TERM0_SHIFT) |
 *  (DDR2_MDDR_SDCR_DDR2TERM1_CLEAR | DDR2_MDDR_SDCR_DDR2TERM1_SHIFT))
 */
#define DDR2_MDDR_SDCR_DDR2TERM1_SET     (0x00000001u)
#define DDR2_MDDR_SDCR_DDR2TERM1_CLEAR   (0x00000000u)
#define DDR2_MDDR_SDCR_IBANK_POS   (0x04000000u)
#define DDR2_MDDR_SDCR_IBANK_POS_SHIFT  (0x0000001Au)
#define DDR2_MDDR_SDCR_MSDRAMEN    (0x02000000u)
#define DDR2_MDDR_SDCR_MSDRAMEN_SHIFT   (0x00000019u)
#define DDR2_MDDR_SDCR_DDRDRIVE1   (0x01000000u)
#define DDR2_MDDR_SDCR_DDRDRIVE1_SHIFT  (0x00000018u)
/*----DDRDRIVE1 Tokens----*/
/* Tokens shown below should be used in conjunction with tokens for DDRDRIVE1 to
 * generate the required temination resistor settings.                          
 * For example: 
 * For the case of weak driver streangth for DDR2 or 1/2 driver strength for mDDR
 * setting the required value is 01 (binary), which would require DDRDRIVE0 to 
 * be 1 and DDRDRIVE1 to be 0. This could be generated as shown below:
 * ((DDR2_MDDR_SDCR_DDRDRIVE0_SET | DDR2_MDDR_SDCR_DDRDRIVE0_SHIFT) |
 *  (DDR2_MDDR_SDCR_DDRDRIVE1_CLEAR | DDR2_MDDR_SDCR_DDRDRIVE1_SHIFT))
 */
#define DDR2_MDDR_SDCR_DDRDRIVE1_SET     (0x00000001u)
#define DDR2_MDDR_SDCR_DDRDRIVE1_CLEAR   (0x00000000u)
#define DDR2_MDDR_SDCR_BOOTUNLOCK  (0x00800000u)
#define DDR2_MDDR_SDCR_BOOTUNLOCK_SHIFT (0x00000017u)
#define DDR2_MDDR_SDCR_DDR2DDQS    (0x00400000u)
#define DDR2_MDDR_SDCR_DDR2DDQS_SHIFT   (0x00000016u)
#define DDR2_MDDR_SDCR_DDR2TERM0   (0x00200000u)
#define DDR2_MDDR_SDCR_DDR2TERM0_SHIFT  (0x00000015u)
/*----DDR2TERM0 Tokens----*/
/* Tokens shown below should be used in conjunction with tokens for DDR2TERM1 to
 * generate the required temination resistor settings.                          
 * For example: 
 * For disable termination the required value is 00 (binary), which would
 * require DDR2TERM0 to be 0 and DDR2TERM1 to be 0. This could be generated as
 * shown below:
 * ((DDR2_MDDR_SDCR_DDR2TERM0_CLEAR | DDR2_MDDR_SDCR_DDR2TERM0_SHIFT) |
 *  (DDR2_MDDR_SDCR_DDR2TERM1_CLEAR | DDR2_MDDR_SDCR_DDR2TERM1_SHIFT))
 */
#define DDR2_MDDR_SDCR_DDR2TERM0_SET     (0x00000001u)
#define DDR2_MDDR_SDCR_DDR2TERM0_CLEAR   (0x00000000u)

#define DDR2_MDDR_SDCR_DDR2EN      (0x00100000u)
#define DDR2_MDDR_SDCR_DDR2EN_SHIFT     (0x00000014u)
#define DDR2_MDDR_SDCR_DDRDLL_DIS  (0x00080000u)
#define DDR2_MDDR_SDCR_DDRDLL_DIS_SHIFT (0x00000013u)
#define DDR2_MDDR_SDCR_DDRDRIVE0   (0x00040000u)
#define DDR2_MDDR_SDCR_DDRDRIVE0_SHIFT  (0x00000012u)
/*----DDRDRIVE0 Tokens----*/
/* Tokens shown below should be used in conjunction with tokens for DDRDRIVE0 to
 * generate the required temination resistor settings.                          
 * For example: 
 * For the case of weak driver streangth for DDR2 or 1/2 driver strength for mDDR
 * setting the required value is 01 (binary), which would require DDRDRIVE0 to 
 * be 1 and DDRDRIVE1 to be 0. This could be generated as shown below:
 * ((DDR2_MDDR_SDCR_DDRDRIVE0_SET | DDR2_MDDR_SDCR_DDRDRIVE0_SHIFT) |
 *  (DDR2_MDDR_SDCR_DDRDRIVE1_CLEAR | DDR2_MDDR_SDCR_DDRDRIVE1_SHIFT))
 */
#define DDR2_MDDR_SDCR_DDRDRIVE0_SET     (0x00000001u)
#define DDR2_MDDR_SDCR_DDRDRIVE0_CLEAR   (0x00000000u)

#define DDR2_MDDR_SDCR_DDREN       (0x00020000u)
#define DDR2_MDDR_SDCR_DDREN_SHIFT      (0x00000011u)
#define DDR2_MDDR_SDCR_SDRAMEN     (0x00010000u)
#define DDR2_MDDR_SDCR_SDRAMEN_SHIFT    (0x00000010u)
#define DDR2_MDDR_SDCR_TIMUNLOCK   (0x00008000u)
#define DDR2_MDDR_SDCR_TIMUNLOCK_SHIFT  (0x0000000Fu)
#define DDR2_MDDR_SDCR_NM          (0x00004000u)
#define DDR2_MDDR_SDCR_NM_SHIFT         (0x0000000Eu)
#define DDR2_MDDR_SDCR_CL          (0x00000E00u)
#define DDR2_MDDR_SDCR_CL_SHIFT         (0x00000009u)
/*----CL Tokens----*/
#define DDR2_MDDR_SDCR_CL_TWO           (0x00000002u)
#define DDR2_MDDR_SDCR_CL_THREE         (0x00000003u)
#define DDR2_MDDR_SDCR_CL_FOUR          (0x00000004u)
#define DDR2_MDDR_SDCR_CL_FIVE          (0x00000005u)


#define DDR2_MDDR_SDCR_IBANK       (0x00000070u)
#define DDR2_MDDR_SDCR_IBANK_SHIFT      (0x00000004u)
/*----IBANK Tokens----*/
#define DDR2_MDDR_SDCR_IBANK_ONE        (0x00000000u)
#define DDR2_MDDR_SDCR_IBANK_TWO        (0x00000001u)
#define DDR2_MDDR_SDCR_IBANK_FOUR       (0x00000002u)
#define DDR2_MDDR_SDCR_IBANK_EIGHT      (0x00000003u)

#define DDR2_MDDR_SDCR_PAGESIZE    (0x00000007u)
#define DDR2_MDDR_SDCR_PAGESIZE_SHIFT   (0x00000000u)
/*----PAGESIZE Tokens----*/
#define DDR2_MDDR_SDCR_PAGESIZE_256WORD (0x00000000u)
#define DDR2_MDDR_SDCR_PAGESIZE_512WORD (0x00000001u)
#define DDR2_MDDR_SDCR_PAGESIZE_1024WORD (0x00000002u)
#define DDR2_MDDR_SDCR_PAGESIZE_2048WORD (0x00000003u)

/* SDRCR */
#define DDR2_MDDR_SDRCR_LPMODEN    (0x80000000u)
#define DDR2_MDDR_SDRCR_LPMODEN_SHIFT   (0x0000001Fu)
#define DDR2_MDDR_SDRCR_MCLKSTOPEN (0x40000000u)
#define DDR2_MDDR_SDRCR_MCLKSTOPEN_SHIFT (0x0000001Eu)
#define DDR2_MDDR_SDRCR_SR_PD      (0x00800000u)
#define DDR2_MDDR_SDRCR_SR_PD_SHIFT     (0x00000017u)
#define DDR2_MDDR_SDRCR_RR         (0x0000FFFFu)
#define DDR2_MDDR_SDRCR_RR_SHIFT        (0x00000000u)

/* SDTIMR1 */
#define DDR2_MDDR_SDTIMR1_T_RFC    (0xFE000000u)
#define DDR2_MDDR_SDTIMR1_T_RFC_SHIFT   (0x00000019u)
#define DDR2_MDDR_SDTIMR1_T_RP     (0x01C00000u)
#define DDR2_MDDR_SDTIMR1_T_RP_SHIFT    (0x00000016u)
#define DDR2_MDDR_SDTIMR1_T_RCD    (0x00380000u)
#define DDR2_MDDR_SDTIMR1_T_RCD_SHIFT   (0x00000013u)
#define DDR2_MDDR_SDTIMR1_T_WR     (0x00070000u)
#define DDR2_MDDR_SDTIMR1_T_WR_SHIFT    (0x00000010u)
#define DDR2_MDDR_SDTIMR1_T_RAS    (0x0000F800u)
#define DDR2_MDDR_SDTIMR1_T_RAS_SHIFT   (0x0000000Bu)
#define DDR2_MDDR_SDTIMR1_T_RC     (0x000007C0u)
#define DDR2_MDDR_SDTIMR1_T_RC_SHIFT    (0x00000006u)
#define DDR2_MDDR_SDTIMR1_T_RRD    (0x00000038u)
#define DDR2_MDDR_SDTIMR1_T_RRD_SHIFT   (0x00000003u)
#define DDR2_MDDR_SDTIMR1_T_WTR    (0x00000003u)
#define DDR2_MDDR_SDTIMR1_T_WTR_SHIFT   (0x00000000u)

/* SDTIMR2 */
#define DDR2_MDDR_SDTIMR2_T_RAS_MAX (0x78000000u)
#define DDR2_MDDR_SDTIMR2_T_RAS_MAX_SHIFT (0x0000001Bu)
#define DDR2_MDDR_SDTIMR2_T_XP     (0x06000000u)
#define DDR2_MDDR_SDTIMR2_T_XP_SHIFT    (0x00000019u)
#define DDR2_MDDR_SDTIMR2_T_XSNR   (0x007F0000u)
#define DDR2_MDDR_SDTIMR2_T_XSNR_SHIFT  (0x00000010u)
#define DDR2_MDDR_SDTIMR2_T_XSRD   (0x0000FF00u)
#define DDR2_MDDR_SDTIMR2_T_XSRD_SHIFT  (0x00000008u)
#define DDR2_MDDR_SDTIMR2_T_RTP    (0x000000E0u)
#define DDR2_MDDR_SDTIMR2_T_RTP_SHIFT   (0x00000005u)
#define DDR2_MDDR_SDTIMR2_T_CKE    (0x0000001Fu)
#define DDR2_MDDR_SDTIMR2_T_CKE_SHIFT   (0x00000000u)

/* SDCR2 */
#define DDR2_MDDR_SDCR2_PASR       (0x00070000u)
#define DDR2_MDDR_SDCR2_PASR_SHIFT      (0x00000010u)
/*----PASR Tokens----*/
#define DDR2_MDDR_SDCR2_PASR_4BNK       (0x00000000u)
#define DDR2_MDDR_SDCR2_PASR_2BNK       (0x00000001u)
#define DDR2_MDDR_SDCR2_PASR_1BNK       (0x00000002u)
#define DDR2_MDDR_SDCR2_PASR_HALFBNK    (0x00000005u)
#define DDR2_MDDR_SDCR2_PASR_QRTRBNK    (0x00000006u)


#define DDR2_MDDR_SDCR2_ROWSIZE    (0x00000007u)
#define DDR2_MDDR_SDCR2_ROWSIZE_SHIFT   (0x00000000u)
/*----ROWSIZE Tokens----*/
#define DDR2_MDDR_SDCR2_ROWSIZE_9ROW    (0x00000000u)
#define DDR2_MDDR_SDCR2_ROWSIZE_10ROW   (0x00000001u)
#define DDR2_MDDR_SDCR2_ROWSIZE_11ROW   (0x00000002u)
#define DDR2_MDDR_SDCR2_ROWSIZE_12ROW   (0x00000003u)
#define DDR2_MDDR_SDCR2_ROWSIZE_13ROW   (0x00000004u)
#define DDR2_MDDR_SDCR2_ROWSIZE_14ROW   (0x00000005u)
#define DDR2_MDDR_SDCR2_ROWSIZE_15ROW   (0x00000006u)
#define DDR2_MDDR_SDCR2_ROWSIZE_16ROW   (0x00000007u)

/* PBBPR */
#define DDR2_MDDR_PBBPR_PR_OLD_COUNT (0x000000FFu)
#define DDR2_MDDR_PBBPR_PR_OLD_COUNT_SHIFT (0x00000000u)

/* PC1 */
#define DDR2_MDDR_PC1_COUNTER1     (0xFFFFFFFFu)
#define DDR2_MDDR_PC1_COUNTER1_SHIFT    (0x00000000u)

/* PC2 */
#define DDR2_MDDR_PC2_COUNTER2     (0xFFFFFFFFu)
#define DDR2_MDDR_PC2_COUNTER2_SHIFT    (0x00000000u)

/* PCC */
#define DDR2_MDDR_PCC_CNTR2_MSTID_EN (0x80000000u)
#define DDR2_MDDR_PCC_CNTR2_MSTID_EN_SHIFT (0x0000001Fu)
#define DDR2_MDDR_PCC_CNTR2_REGION_EN (0x40000000u)
#define DDR2_MDDR_PCC_CNTR2_REGION_EN_SHIFT (0x0000001Eu)
#define DDR2_MDDR_PCC_CNTR2_CFG    (0x000F0000u)
#define DDR2_MDDR_PCC_CNTR2_CFG_SHIFT   (0x00000010u)
#define DDR2_MDDR_PCC_CNTR1_MSTID_EN (0x00008000u)
#define DDR2_MDDR_PCC_CNTR1_MSTID_EN_SHIFT (0x0000000Fu)
#define DDR2_MDDR_PCC_CNTR1_REGION_EN (0x00004000u)
#define DDR2_MDDR_PCC_CNTR1_REGION_EN_SHIFT (0x0000000Eu)
#define DDR2_MDDR_PCC_CNTR1_CFG    (0x0000000Fu)
#define DDR2_MDDR_PCC_CNTR1_CFG_SHIFT   (0x00000000u)

/* PCMRS */
#define DDR2_MDDR_PCMRS_MST_ID2    (0xFF000000u)
#define DDR2_MDDR_PCMRS_MST_ID2_SHIFT   (0x00000018u)
#define DDR2_MDDR_PCMRS_REGION_SEL2 (0x000F0000u)
#define DDR2_MDDR_PCMRS_REGION_SEL2_SHIFT (0x00000010u)
/*----REGION_SEL2 Tokens----*/
#define DDR2_MDDR_PCMRS_REGION_SEL2_DDRACCESS (0x00000000u)
#define DDR2_MDDR_PCMRS_REGION_SEL2_MMRACCESS (0x00000007u)

#define DDR2_MDDR_PCMRS_MST_ID1    (0x0000FF00u)
#define DDR2_MDDR_PCMRS_MST_ID1_SHIFT   (0x00000008u)
#define DDR2_MDDR_PCMRS_REGION_SEL1 (0x0000000Fu)
#define DDR2_MDDR_PCMRS_REGION_SEL1_SHIFT (0x00000000u)
/*----REGION_SEL1 Tokens----*/
#define DDR2_MDDR_PCMRS_REGION_SEL1_DDRACCESS (0x00000000u)
#define DDR2_MDDR_PCMRS_REGION_SEL1_MMRACCESS (0x00000007u)

/* PCT */
#define DDR2_MDDR_PCT_TOTAL_TIME   (0xFFFFFFFFu)
#define DDR2_MDDR_PCT_TOTAL_TIME_SHIFT  (0x00000000u)

/* IRR */
#define DDR2_MDDR_IRR_LT           (0x00000004u)
#define DDR2_MDDR_IRR_LT_SHIFT          (0x00000002u)

/* IMR */
#define DDR2_MDDR_IMR_LTM          (0x00000004u)
#define DDR2_MDDR_IMR_LTM_SHIFT         (0x00000002u)

/* IMSR */
#define DDR2_MDDR_IMSR_LTMSET      (0x00000004u)
#define DDR2_MDDR_IMSR_LTMSET_SHIFT     (0x00000002u)
/*----LTMSET Tokens----*/
#define DDR2_MDDR_IMSR_LTMSET_SET       (0x00000001u)

/* IMCR */
#define DDR2_MDDR_IMCR_LTMCLR      (0x00000004u)
#define DDR2_MDDR_IMCR_LTMCLR_SHIFT     (0x00000002u)

/* DRPYC1R */
#define DDR2_MDDR_DRPYC1R_LBCKSEL  (0x00800000u)
#define DDR2_MDDR_DRPYC1R_LBCKSEL_SHIFT (0x00000017u)
#define DDR2_MDDR_DRPYC1R_VTP_DYN_UPDT (0x00008000u)
#define DDR2_MDDR_DRPYC1R_VTP_DYN_UPDT_SHIFT (0x0000000Fu)
#define DDR2_MDDR_DRPYC1R_DLLMODE  (0x00007000u)
#define DDR2_MDDR_DRPYC1R_DLLMODE_SHIFT (0x0000000Cu)
#define DDR2_MDDR_DRPYC1R_EXT_STRBEN (0x00000080u)
#define DDR2_MDDR_DRPYC1R_EXT_STRBEN_SHIFT (0x00000007u)
#define DDR2_MDDR_DRPYC1R_PWRDNEN  (0x00000040u)
#define DDR2_MDDR_DRPYC1R_PWRDNEN_SHIFT (0x00000006u)
#define DDR2_MDDR_DRPYC1R_RL       (0x00000007u)
#define DDR2_MDDR_DRPYC1R_RL_SHIFT      (0x00000000u)

#ifdef __cplusplus
}
#endif

#endif
