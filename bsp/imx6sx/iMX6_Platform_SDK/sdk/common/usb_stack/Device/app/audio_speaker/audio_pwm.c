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
 * @file audio_pwm.c
 *
 * @author
 *
 * @version
 *
 * @date    
 *
 * @brief   This file configures Pulse Width Modulation 
 *
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
* Function Name    : pwm_init
* Returned Value   :
* Comments         : Initialize timer module
*    
*END*------------------------------------------------------------------------*/
void pwm_init(void) 
{
#if (defined _MC9S08JS16_H)
  TPMSC = 0;
  TPMMOD = 0xFF;
  TPMC1SC = 0x24;

  duty = 0x00;
  
  TPMSC = 0x08;
#else
  TPM1SC = 0;
  TPM1MOD = 0xFF;
  TPM1C2SC = 0x24;

  duty = 0x00;
  
  TPM1SC = 0x08;
#endif
}
