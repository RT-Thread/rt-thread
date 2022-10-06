

/**
 *  @Component:   CM
 *
 *  @Filename:    ../../CredDataBase/prcmCRED/cm_dpll_cred.h
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



#ifndef _HW_CM_DPLL_H_
#define _HW_CM_DPLL_H_


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

#define CM_DPLL_CLKSEL_TIMER7_CLK   (0x4)
#define CM_DPLL_CLKSEL_TIMER2_CLK   (0x8)
#define CM_DPLL_CLKSEL_TIMER3_CLK   (0xc)
#define CM_DPLL_CLKSEL_TIMER4_CLK   (0x10)
#define CM_DPLL_CM_MAC_CLKSEL   (0x14)
#define CM_DPLL_CLKSEL_TIMER5_CLK   (0x18)
#define CM_DPLL_CLKSEL_TIMER6_CLK   (0x1c)
#define CM_DPLL_CM_CPTS_RFT_CLKSEL   (0x20)
#define CM_DPLL_CLKSEL_TIMER1MS_CLK   (0x28)
#define CM_DPLL_CLKSEL_GFX_FCLK   (0x2c)
#define CM_DPLL_CLKSEL_ICSS_OCP_CLK   (0x30)
#define CM_DPLL_CLKSEL_LCDC_PIXEL_CLK   (0x34)
#define CM_DPLL_CLKSEL_WDT1_CLK   (0x38)
#define CM_DPLL_CLKSEL_GPIO0_DBCLK   (0x3c)

/**************************************************************************\ 
 * Field Definition Macros
\**************************************************************************/

/* CLKSEL_TIMER7_CLK */
#define CM_DPLL_CLKSEL_TIMER7_CLK_CLKSEL   (0x00000003u)
#define CM_DPLL_CLKSEL_TIMER7_CLK_CLKSEL_SHIFT   (0x00000000u)
#define CM_DPLL_CLKSEL_TIMER7_CLK_CLKSEL_SEL1   (0x0u)
#define CM_DPLL_CLKSEL_TIMER7_CLK_CLKSEL_CLK_M_OSC   (0x1u)
#define CM_DPLL_CLKSEL_TIMER7_CLK_CLKSEL_SEL3   (0x2u)
#define CM_DPLL_CLKSEL_TIMER7_CLK_CLKSEL_SEL4   (0x3u)


/* CLKSEL_TIMER2_CLK */
#define CM_DPLL_CLKSEL_TIMER2_CLK_CLKSEL   (0x00000003u)
#define CM_DPLL_CLKSEL_TIMER2_CLK_CLKSEL_SHIFT   (0x00000000u)
#define CM_DPLL_CLKSEL_TIMER2_CLK_CLKSEL_SEL1   (0x0u)
#define CM_DPLL_CLKSEL_TIMER2_CLK_CLKSEL_CLK_M_OSC   (0x1u)
#define CM_DPLL_CLKSEL_TIMER2_CLK_CLKSEL_SEL3   (0x2u)
#define CM_DPLL_CLKSEL_TIMER2_CLK_CLKSEL_SEL4   (0x3u)


/* CLKSEL_TIMER3_CLK */
#define CM_DPLL_CLKSEL_TIMER3_CLK_CLKSEL   (0x00000003u)
#define CM_DPLL_CLKSEL_TIMER3_CLK_CLKSEL_SHIFT   (0x00000000u)
#define CM_DPLL_CLKSEL_TIMER3_CLK_CLKSEL_SEL1   (0x0u)
#define CM_DPLL_CLKSEL_TIMER3_CLK_CLKSEL_CLK_M_OSC   (0x1u)
#define CM_DPLL_CLKSEL_TIMER3_CLK_CLKSEL_SEL3   (0x2u)
#define CM_DPLL_CLKSEL_TIMER3_CLK_CLKSEL_SEL4   (0x3u)


/* CLKSEL_TIMER4_CLK */
#define CM_DPLL_CLKSEL_TIMER4_CLK_CLKSEL   (0x00000003u)
#define CM_DPLL_CLKSEL_TIMER4_CLK_CLKSEL_SHIFT   (0x00000000u)
#define CM_DPLL_CLKSEL_TIMER4_CLK_CLKSEL_SEL1   (0x0u)
#define CM_DPLL_CLKSEL_TIMER4_CLK_CLKSEL_CLK_M_OSC   (0x1u)
#define CM_DPLL_CLKSEL_TIMER4_CLK_CLKSEL_SEL3   (0x2u)
#define CM_DPLL_CLKSEL_TIMER4_CLK_CLKSEL_SEL4   (0x3u)


/* CM_MAC_CLKSEL */
#define CM_DPLL_CM_MAC_CLKSEL_MII_CLK_SEL   (0x00000004u)
#define CM_DPLL_CM_MAC_CLKSEL_MII_CLK_SEL_SHIFT   (0x00000002u)
#define CM_DPLL_CM_MAC_CLKSEL_MII_CLK_SEL_SEL0   (0x0u)
#define CM_DPLL_CM_MAC_CLKSEL_MII_CLK_SEL_SEL1   (0x1u)


/* CLKSEL_TIMER5_CLK */
#define CM_DPLL_CLKSEL_TIMER5_CLK_CLKSEL   (0x00000003u)
#define CM_DPLL_CLKSEL_TIMER5_CLK_CLKSEL_SHIFT   (0x00000000u)
#define CM_DPLL_CLKSEL_TIMER5_CLK_CLKSEL_SEL1   (0x0u)
#define CM_DPLL_CLKSEL_TIMER5_CLK_CLKSEL_SEL2   (0x1u)
#define CM_DPLL_CLKSEL_TIMER5_CLK_CLKSEL_SEL3   (0x2u)
#define CM_DPLL_CLKSEL_TIMER5_CLK_CLKSEL_SEL4   (0x3u)


/* CLKSEL_TIMER6_CLK */
#define CM_DPLL_CLKSEL_TIMER6_CLK_CLKSEL   (0x00000003u)
#define CM_DPLL_CLKSEL_TIMER6_CLK_CLKSEL_SHIFT   (0x00000000u)
#define CM_DPLL_CLKSEL_TIMER6_CLK_CLKSEL_SEL1   (0x0u)
#define CM_DPLL_CLKSEL_TIMER6_CLK_CLKSEL_SEL2   (0x1u)
#define CM_DPLL_CLKSEL_TIMER6_CLK_CLKSEL_SEL3   (0x2u)
#define CM_DPLL_CLKSEL_TIMER6_CLK_CLKSEL_SEL4   (0x3u)


/* CM_CPTS_RFT_CLKSEL */
#define CM_DPLL_CM_CPTS_RFT_CLKSEL_CLKSEL   (0x00000001u)
#define CM_DPLL_CM_CPTS_RFT_CLKSEL_CLKSEL_SHIFT   (0x00000000u)
#define CM_DPLL_CM_CPTS_RFT_CLKSEL_CLKSEL_SEL1   (0x0u)
#define CM_DPLL_CM_CPTS_RFT_CLKSEL_CLKSEL_SEL2   (0x1u)


/* CLKSEL_TIMER1MS_CLK */
#define CM_DPLL_CLKSEL_TIMER1MS_CLK_CLKSEL   (0x00000007u)
#define CM_DPLL_CLKSEL_TIMER1MS_CLK_CLKSEL_SHIFT   (0x00000000u)
#define CM_DPLL_CLKSEL_TIMER1MS_CLK_CLKSEL_SEL1   (0x0u)
#define CM_DPLL_CLKSEL_TIMER1MS_CLK_CLKSEL_SEL2   (0x1u)
#define CM_DPLL_CLKSEL_TIMER1MS_CLK_CLKSEL_SEL3   (0x2u)
#define CM_DPLL_CLKSEL_TIMER1MS_CLK_CLKSEL_SEL4   (0x3u)
#define CM_DPLL_CLKSEL_TIMER1MS_CLK_CLKSEL_SEL5   (0x4u)


/* CLKSEL_GFX_FCLK */
#define CM_DPLL_CLKSEL_GFX_FCLK_CLKDIV_SEL_GFX_FCLK   (0x00000001u)
#define CM_DPLL_CLKSEL_GFX_FCLK_CLKDIV_SEL_GFX_FCLK_SHIFT   (0x00000000u)
#define CM_DPLL_CLKSEL_GFX_FCLK_CLKDIV_SEL_GFX_FCLK_DIV1   (0x0u)
#define CM_DPLL_CLKSEL_GFX_FCLK_CLKDIV_SEL_GFX_FCLK_DIV2   (0x1u)

#define CM_DPLL_CLKSEL_GFX_FCLK_CLKSEL_GFX_FCLK   (0x00000002u)
#define CM_DPLL_CLKSEL_GFX_FCLK_CLKSEL_GFX_FCLK_SHIFT   (0x00000001u)
#define CM_DPLL_CLKSEL_GFX_FCLK_CLKSEL_GFX_FCLK_SEL0   (0x0u)
#define CM_DPLL_CLKSEL_GFX_FCLK_CLKSEL_GFX_FCLK_SEL1   (0x1u)


/* CLKSEL_ICSS_OCP_CLK */
#define CM_DPLL_CLKSEL_ICSS_OCP_CLK_CLKSEL   (0x00000001u)
#define CM_DPLL_CLKSEL_ICSS_OCP_CLK_CLKSEL_SHIFT   (0x00000000u)
#define CM_DPLL_CLKSEL_ICSS_OCP_CLK_CLKSEL_SEL1   (0x0u)
#define CM_DPLL_CLKSEL_ICSS_OCP_CLK_CLKSEL_SEL2   (0x1u)


/* CLKSEL_LCDC_PIXEL_CLK */
#define CM_DPLL_CLKSEL_LCDC_PIXEL_CLK_CLKSEL   (0x00000003u)
#define CM_DPLL_CLKSEL_LCDC_PIXEL_CLK_CLKSEL_SHIFT   (0x00000000u)
#define CM_DPLL_CLKSEL_LCDC_PIXEL_CLK_CLKSEL_SEL1   (0x0u)
#define CM_DPLL_CLKSEL_LCDC_PIXEL_CLK_CLKSEL_SEL2   (0x1u)
#define CM_DPLL_CLKSEL_LCDC_PIXEL_CLK_CLKSEL_SEL3   (0x2u)
#define CM_DPLL_CLKSEL_LCDC_PIXEL_CLK_CLKSEL_SEL4   (0x3u)


/* CLKSEL_WDT1_CLK */
#define CM_DPLL_CLKSEL_WDT1_CLK_CLKSEL   (0x00000001u)
#define CM_DPLL_CLKSEL_WDT1_CLK_CLKSEL_SHIFT   (0x00000000u)
#define CM_DPLL_CLKSEL_WDT1_CLK_CLKSEL_SEL1   (0x0u)
#define CM_DPLL_CLKSEL_WDT1_CLK_CLKSEL_SEL2   (0x1u)


/* CLKSEL_GPIO0_DBCLK */
#define CM_DPLL_CLKSEL_GPIO0_DBCLK_CLKSEL   (0x00000003u)
#define CM_DPLL_CLKSEL_GPIO0_DBCLK_CLKSEL_SHIFT   (0x00000000u)
#define CM_DPLL_CLKSEL_GPIO0_DBCLK_CLKSEL_SEL1   (0x0u)
#define CM_DPLL_CLKSEL_GPIO0_DBCLK_CLKSEL_SEL2   (0x1u)
#define CM_DPLL_CLKSEL_GPIO0_DBCLK_CLKSEL_SEL3   (0x2u)



#endif
