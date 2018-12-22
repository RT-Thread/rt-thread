/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 ******************************************************************************
 *
 * THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
 * IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 **************************************************************************//*!
 *
 * @file audio_pwm_kinetis.c
 *
 * @author
 *
 * @version
 *
 * @date    
 *
 * @brief   This file configures Pulse Width Modulation (RTC) for Timer 
 *          Implementation
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <string.h>
#include "derivative.h"     /* include peripheral declarations */
#include "types.h"          /* Contains User Defined Data Types */
#include "audio_pwm.h"

void pwm_init(void);

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : TimerInit
* Returned Value   :
* Comments         : Initialize timer module
*    
*END*------------------------------------------------------------------------*/
void pwm_init(void) 
{
#ifdef MCU_MKL25Z4
	
	  /* TPM0 enable on PTE */
	  PORTE_PCR24 |= PORT_PCR_MUX(0x3);
	  
	  /* Enable TPM0 clock */ 
	  SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;
	  /* Set clock source */
	  SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);
	  
	  TPM0_SC = 0x00;
	  
	  /* Set TPM0 modular */
	  TPM0_MOD = 0xFF;	  
	  
	  TPM0_C0SC |= (TPM_CnSC_ELSB_MASK | TPM_CnSC_MSB_MASK);
	  
	  duty = 0x00;
	  
	  /* Enable TPM0 */ 
	   TPM0_SC |= TPM_SC_CMOD(1);
#else
  /* FTM0_CH0 enable on PTC1 ****/
  PORTC_PCR1 = PORT_PCR_MUX(0x4);
  
  /* Enable FTM0 clock */
  SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;
  
  /* Set FTM0 mode */
  FTM0_MODE = (FTM_MODE_WPDIS_MASK | FTM_MODE_FTMEN_MASK);
  FTM0_MODE &= ~FTM_MODE_FTMEN_MASK;
  FTM0_SC = 0;
  FTM0_CNTIN = 0x00;
  
  /* Set FTM0 modular */
  FTM0_MOD = 0xFF;
  FTM0_QDCTRL &= ~(FTM_QDCTRL_QUADEN_MASK);
  FTM0_COMBINE &= ~(FTM_COMBINE_DECAPEN0_MASK \
            |FTM_COMBINE_DECAPEN1_MASK \
            |FTM_COMBINE_DECAPEN2_MASK \
            |FTM_COMBINE_DECAPEN3_MASK \
            |FTM_COMBINE_COMBINE0_MASK \
            |FTM_COMBINE_COMBINE1_MASK \
            |FTM_COMBINE_COMBINE2_MASK \
            |FTM_COMBINE_COMBINE3_MASK);
  FTM0_C0SC = FTM_CnSC_ELSB_MASK | FTM_CnSC_MSB_MASK;
  duty = 0x00;   
  
  /* Enable FTM0 */
  FTM0_SC = FTM_SC_CLKS(1);
#endif
}
