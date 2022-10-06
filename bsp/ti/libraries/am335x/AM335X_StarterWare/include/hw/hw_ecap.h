/**
 * \file  hw_ecap.h
 *
 * \brief ECAP register definitions
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


#ifndef _HW_ECAP_H_
#define _HW_ECAP_H_

#ifdef __cplusplus
extern "C" {
#endif

#define ECAP_TSCTR	(0x0)
#define ECAP_CTRPHS	(0x4)
#define ECAP_CAP1	(0x8)
#define ECAP_CAP2	(0xC)
#define ECAP_CAP3	(0x10)
#define ECAP_CAP4	(0x14)
#define ECAP_ECCTL1	(0x28)
#define ECAP_ECCTL2	(0x2A)
#define ECAP_ECEINT	(0x2C)
#define ECAP_ECFLG	(0x2E)
#define ECAP_ECCLR	(0x30)
#define ECAP_ECFRC	(0x32)
#define ECAP_REVID	(0x5C)

/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

/* TSCTR */

#define ECAP_TSCTR_TSCTR (0xFFFFFFFFu)
#define ECAP_TSCTR_TSCTR_SHIFT (0x00000000u)


/* CTRPHS */

#define ECAP_CTRPHS_CTRPHS (0xFFFFFFFFu)
#define ECAP_CTRPHS_CTRPHS_SHIFT (0x00000000u)


/* CAP1 */

#define ECAP_CAP1_CAP1 (0xFFFFFFFFu)
#define ECAP_CAP1_CAP1_SHIFT (0x00000000u)


/* CAP2 */

#define ECAP_CAP2_CAP2 (0xFFFFFFFFu)
#define ECAP_CAP2_CAP2_SHIFT (0x00000000u)


/* CAP3 */

#define ECAP_CAP3_CAP3 (0xFFFFFFFFu)
#define ECAP_CAP3_CAP3_SHIFT (0x00000000u)


/* CAP4 */

#define ECAP_CAP4_CAP4 (0xFFFFFFFFu)
#define ECAP_CAP4_CAP4_SHIFT (0x00000000u)


/* ECCTL1 */

#define ECAP_ECCTL1_FREE_SOFT (0xC000u)
#define ECAP_ECCTL1_FREE_SOFT_SHIFT (0x000Eu)
#define ECAP_ECCTL1_FREE_SOFT_STOP (0x0000u)
#define ECAP_ECCTL1_FREE_SOFT_RUNUNTIL0 (0x0001u)

#define ECAP_ECCTL1_PRESCALE (0x3E00u)
#define ECAP_ECCTL1_PRESCALE_SHIFT (0x0009u)

#define ECAP_ECCTL1_CAPLDEN (0x0100u)
#define ECAP_ECCTL1_CAPLDEN_SHIFT (0x0008u)

#define ECAP_ECCTL1_CTRRST4 (0x0080u)
#define ECAP_ECCTL1_CTRRST4_SHIFT (0x0007u)
#define ECAP_ECCTL1_CTRRST4_NORESET (0x0000u)
#define ECAP_ECCTL1_CTRRST4_RESET (0x0001u)

#define ECAP_ECCTL1_CAP4POL (0x0040u)
#define ECAP_ECCTL1_CAP4POL_SHIFT (0x0006u)

#define ECAP_ECCTL1_CTRRST3 (0x0020u)
#define ECAP_ECCTL1_CTRRST3_SHIFT (0x0005u)

#define ECAP_ECCTL1_CAP3POL (0x0010u)
#define ECAP_ECCTL1_CAP3POL_SHIFT (0x0004u)

#define ECAP_ECCTL1_CTRRST2 (0x0008u)
#define ECAP_ECCTL1_CTRRST2_SHIFT (0x0003u)

#define ECAP_ECCTL1_CAP2POL (0x0004u)
#define ECAP_ECCTL1_CAP2POL_SHIFT (0x0002u)

#define ECAP_ECCTL1_CTRRST1 (0x0002u)
#define ECAP_ECCTL1_CTRRST1_SHIFT (0x0001u)

#define ECAP_ECCTL1_CAP1POL (0x0001u)
#define ECAP_ECCTL1_CAP1POL_SHIFT (0x0000u)


/* ECCTL2 */


#define ECAP_ECCTL2_APWMPOL (0x0400u)
#define ECAP_ECCTL2_APWMPOL_SHIFT (0x000Au)

#define ECAP_ECCTL2_CAP_APWM (0x0200u)
#define ECAP_ECCTL2_CAP_APWM_SHIFT (0x0009u)

#define ECAP_ECCTL2_SWSYNC (0x0100u)
#define ECAP_ECCTL2_SWSYNC_SHIFT (0x0008u)

#define ECAP_ECCTL2_SYNCO_SEL (0x00C0u)
#define ECAP_ECCTL2_SYNCO_SEL_SHIFT (0x0006u)

#define ECAP_ECCTL2_SYNCI_EN (0x0020u)
#define ECAP_ECCTL2_SYNCI_EN_SHIFT (0x0005u)

#define ECAP_ECCTL2_TSCTRSTOP (0x0010u)
#define ECAP_ECCTL2_TSCTRSTOP_SHIFT (0x0004u)

#define ECAP_ECCTL2_RE_ARM (0x0008u)
#define ECAP_ECCTL2_RE_ARM_SHIFT (0x0003u)

#define ECAP_ECCTL2_STOP_WRAP (0x0006u)
#define ECAP_ECCTL2_STOP_WRAP_SHIFT (0x0001u)
#define ECAP_ECCTL2_STOP_WRAP_CAP1 (0x0000u)
#define ECAP_ECCTL2_STOP_WRAP_CAP2 (0x0001u)
#define ECAP_ECCTL2_STOP_WRAP_CAP3 (0x0002u)
#define ECAP_ECCTL2_STOP_WRAP_CAP4 (0x0003u)

#define ECAP_ECCTL2_CONT_ONESHT (0x0001u)
#define ECAP_ECCTL2_CONT_ONESHT_SHIFT (0x0000u)


/* ECEINT */


#define ECAP_ECEINT_CTR_CMP (0x0080u)
#define ECAP_ECEINT_CTR_CMP_SHIFT (0x0007u)

#define ECAP_ECEINT_CTR_PRD (0x0040u)
#define ECAP_ECEINT_CTR_PRD_SHIFT (0x0006u)

#define ECAP_ECEINT_CTROVF (0x0020u)
#define ECAP_ECEINT_CTROVF_SHIFT (0x0005u)

#define ECAP_ECEINT_CEVT4 (0x0010u)
#define ECAP_ECEINT_CEVT4_SHIFT (0x0004u)

#define ECAP_ECEINT_CEVT3 (0x0008u)
#define ECAP_ECEINT_CEVT3_SHIFT (0x0003u)

#define ECAP_ECEINT_CEVT2 (0x0004u)
#define ECAP_ECEINT_CEVT2_SHIFT (0x0002u)

#define ECAP_ECEINT_CEVT1 (0x0002u)
#define ECAP_ECEINT_CEVT1_SHIFT (0x0001u)



/* ECFLG */


#define ECAP_ECFLG_CTR_CMP (0x0080u)
#define ECAP_ECFLG_CTR_CMP_SHIFT (0x0007u)

#define ECAP_ECFLG_CTR_PRD (0x0040u)
#define ECAP_ECFLG_CTR_PRD_SHIFT (0x0006u)

#define ECAP_ECFLG_CTROVF (0x0020u)
#define ECAP_ECFLG_CTROVF_SHIFT (0x0005u)

#define ECAP_ECFLG_CEVT4 (0x0010u)
#define ECAP_ECFLG_CEVT4_SHIFT (0x0004u)

#define ECAP_ECFLG_CEVT3 (0x0008u)
#define ECAP_ECFLG_CEVT3_SHIFT (0x0003u)

#define ECAP_ECFLG_CEVT2 (0x0004u)
#define ECAP_ECFLG_CEVT2_SHIFT (0x0002u)

#define ECAP_ECFLG_CEVT1 (0x0002u)
#define ECAP_ECFLG_CEVT1_SHIFT (0x0001u)

#define ECAP_ECFLG_INT (0x0001u)
#define ECAP_ECFLG_INT_SHIFT (0x0000u)


/* ECCLR */


#define ECAP_ECCLR_CTR_CMP (0x0080u)
#define ECAP_ECCLR_CTR_CMP_SHIFT (0x0007u)

#define ECAP_ECCLR_CTR_PRD (0x0040u)
#define ECAP_ECCLR_CTR_PRD_SHIFT (0x0006u)

#define ECAP_ECCLR_CTROVF (0x0020u)
#define ECAP_ECCLR_CTROVF_SHIFT (0x0005u)

#define ECAP_ECCLR_CEVT4 (0x0010u)
#define ECAP_ECCLR_CEVT4_SHIFT (0x0004u)

#define ECAP_ECCLR_CEVT3 (0x0008u)
#define ECAP_ECCLR_CEVT3_SHIFT (0x0003u)

#define ECAP_ECCLR_CEVT2 (0x0004u)
#define ECAP_ECCLR_CEVT2_SHIFT (0x0002u)

#define ECAP_ECCLR_CEVT1 (0x0002u)
#define ECAP_ECCLR_CEVT1_SHIFT (0x0001u)

#define ECAP_ECCLR_INT (0x0001u)
#define ECAP_ECCLR_INT_SHIFT (0x0000u)


/* ECFRC */


#define ECAP_ECFRC_CTR_CMP (0x0080u)
#define ECAP_ECFRC_CTR_CMP_SHIFT (0x0007u)

#define ECAP_ECFRC_CTR_PRD (0x0040u)
#define ECAP_ECFRC_CTR_PRD_SHIFT (0x0006u)

#define ECAP_ECFRC_CTROVF (0x0020u)
#define ECAP_ECFRC_CTROVF_SHIFT (0x0005u)

#define ECAP_ECFRC_CEVT4 (0x0010u)
#define ECAP_ECFRC_CEVT4_SHIFT (0x0004u)

#define ECAP_ECFRC_CEVT3 (0x0008u)
#define ECAP_ECFRC_CEVT3_SHIFT (0x0003u)

#define ECAP_ECFRC_CEVT2 (0x0004u)
#define ECAP_ECFRC_CEVT2_SHIFT (0x0002u)

#define ECAP_ECFRC_CEVT1 (0x0002u)
#define ECAP_ECFRC_CEVT1_SHIFT (0x0001u)



/* REVID */

#define ECAP_REVID_REV          (0xFFFFFFFFu)
#define ECAP_REVID_REV_SHIFT         (0x00000000u)

#ifdef __cplusplus
}
#endif

#endif
