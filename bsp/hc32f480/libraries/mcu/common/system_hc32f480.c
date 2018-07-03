/*******************************************************************************
* Copyright (C) 2016, Huada Semiconductor Co., Ltd. All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co., Ltd. ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/
/******************************************************************************/
/** \file system_hc32f480.c
 **
 ** System clock initialization.
 **
 **   - 2018-1-15  1.0  Zhangxl First version
 **   - 2018-5-29  1.1  Jason   Add config system clock function
 **
 ******************************************************************************/

/******************************************************************************/
/* Global pre-processor symbols/macros ('define')                             */
/******************************************************************************/
#define STABLE_TIME                 0x1000
/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "hc32f480.h"
#include "system_hc32f480.h"

/**
 ******************************************************************************
 ** System Clock Frequency (Core Clock) Variable according CMSIS
 ******************************************************************************/
uint32_t SystemCoreClock = XTAL_VALUE;

static void SetSysClock(void)
{
    __IO uint32_t timeout = STABLE_TIME;

    /* Enable clock register write. */
    M4_SYSREG->FPRC = 0xa501;

    /* XTAL config. */
    M4_SYSREG->CMU_XTALCFGR_f.SUPDRV = 1u;
    M4_SYSREG->CMU_XTALCFGR_f.XTALDRV = 2u;
    /* Enable XTAL. */
    M4_SYSREG->CMU_XTALCR_f.XTALSTP = 0u;
    /* Wait until XTAL ready. */
    while(0u == M4_SYSREG->CMU_OSCSTBSR_f.XTALSTBF);

    /* PLL config. */
    M4_SYSREG->CMU_PLLCFGR_f.PLLSRC = 0u;
    M4_SYSREG->CMU_PLLCFGR_f.MPLLN = 49u;
    M4_SYSREG->CMU_PLLCFGR_f.MPLLP = 1u;
    M4_SYSREG->CMU_PLLCFGR_f.MPLLM = 0u;
    /* Flash read wait cycle config. */
    M4_EFM->FAPRT = 0x0123;
    M4_EFM->FAPRT = 0x3210;
    M4_EFM->FRMC_f.FLWT = 4;

    /* Enable PLL. */
    M4_SYSREG->CMU_PLLCR_f.MPLLOFF = 0u;
    /* Wait until PLL ready. */
    while(0u == M4_SYSREG->CMU_OSCSTBSR_f.MPLLSTBF);

    /* Config all of the peripheral clock to default. */
    M4_MSTP->FCG0 = 0xFFFFFAEE;
    M4_MSTP->FCG1 = 0xFFFFFFFF;
    M4_MSTP->FCG2 = 0xFFFFFFFF;
    M4_MSTP->FCG3 = 0xFFFF;
    /* Wait stable. */
    timeout = STABLE_TIME;
    do
    {
        timeout--;
    }while(timeout);

    /* Config system clock division factor. */
    M4_SYSREG->CMU_SCFGR_f.EXCKS = 3u;      //Max 25MHZ.
    M4_SYSREG->CMU_SCFGR_f.PCLK4S = 1u;     //Max 100MHZ.
    M4_SYSREG->CMU_SCFGR_f.PCLK3S = 2u;     //Max 50MHZ.
    M4_SYSREG->CMU_SCFGR_f.PCLK2S = 2u;     //Max 50MHZ.
    M4_SYSREG->CMU_SCFGR_f.PCLK1S = 1u;     //Max 100MHZ.
    M4_SYSREG->CMU_SCFGR_f.PCLK0S = 0u;     //Max 200MHZ.
    M4_SYSREG->CMU_SCFGR_f.HCLKS = 0u;      //Max 200MHZ.
    /* Wait stable. */
    timeout = STABLE_TIME;
    do
    {
        timeout--;
    }while(timeout);

    /* Config pll as system clock source. */
    M4_SYSREG->CMU_CKSWR_f.CKSW = 5u;
    /* Wait stable. */
    timeout = STABLE_TIME;
    do
    {
        timeout--;
    }while(timeout);

    /* Disable clock register write. */
    M4_SYSREG->FPRC = 0xa500;

    /* Config sram read write wait cycle 3. */
    M4_SRAMC->WTPR = (0x3b << 2) | 1;

    M4_SRAMC->WTCR_f.SRAMSYSRWT = 2;
    M4_SRAMC->WTCR_f.SRAMSYSWWT = 2;

    M4_SRAMC->WTCR_f.SRAMECCRWT = 2;
    M4_SRAMC->WTCR_f.SRAMECCWWT = 2;

    M4_SRAMC->WTCR_f.SRAMBKRWT = 2;
    M4_SRAMC->WTCR_f.SRAMBKWWT = 2;

    M4_SRAMC->WTPR = (0x3b << 2) | 0;
}

/**
 ******************************************************************************
 ** \brief  Setup the microcontroller system. Initialize the System and update
 ** the SystemCoreClock variable.
 **
 ** \param  none
 ** \return none
 ******************************************************************************/
void SystemInit(void)
{
    SetSysClock();
}

void SystemCoreClockUpdate (void) // Update SystemCoreClock variable
{
    uint8_t tmp=0, plln = 19, pllp = 1, pllm = 0, pllsource = 0;
    tmp = M4_SYSREG->CMU_CKSWR_f.CKSW;
    switch (tmp)
    {
        case 0x00:  /* use internal high speed RC */
            SystemCoreClock = HRC_VALUE;
        break;

        case 0x01:  /* use internal middle speed RC */
            SystemCoreClock = MRC_VALUE;
        break;

        case 0x02:  /* use internal low speed RC */
            SystemCoreClock = LRC_VALUE;
        break;

        case 0x03:  /* use external high speed RC */
            SystemCoreClock = XTAL_VALUE;
        break;

        case 0x04:  /* use external low speed RC */
            SystemCoreClock = XTAL32_VALUE;
        break;

        case 0x05:  /* use MPLL */
            /* PLLCLK = ((pllsrc / pllm) * plln) / pllp */
            pllsource = M4_SYSREG->CMU_PLLCFGR_f.PLLSRC;
            plln = M4_SYSREG->CMU_PLLCFGR_f.MPLLN;
            pllp = M4_SYSREG->CMU_PLLCFGR_f.MPLLP;
            pllm = M4_SYSREG->CMU_PLLCFGR_f.MPLLM;
            /* use exteranl high speed OSC as PLL source */
            if (0 == pllsource)
            {
                SystemCoreClock = (XTAL_VALUE)/(pllm+1)*(plln+1)/(pllp<<1);
            }
            /* use interanl high RC as PLL source */
            else if (1 == pllsource)
            {
                SystemCoreClock = (HRC_VALUE)/(pllm+1)*(plln+1)/(pllp<<1);
            }
        break;

    }
}
