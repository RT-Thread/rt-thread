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
 * @file audio_rtc.c
 *
 * @author
 *
 * @version
 *
 * @date    
 *
 * @brief   This file configures Timer 
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <string.h>
#include "derivative.h"     /* include peripheral declarations */
#include "types.h"          /* Contains User Defined Data Types */
#include "audio_pwm.h"
#include "usb_class.h"
#include "usb_descriptor.h"

extern uint_8 audio_sample;
extern uint_8 audio_event;
extern uint_8 audio_data_recv[8];
extern uint_8 g_cur_mute[USB_MAX_SUPPORTED_INTERFACES];

/******************************************************************************
 * @name   rtc_init    
 *
 * @brief   Init real-time counter   
 *
 * @param       None
 *
 * @return     None
 *
 *****************************************************************************
 * This function init the real-time counter
 *****************************************************************************/
void rtc_init(void)
{
  RTCMOD = 3;
  RTCSC = 0x58;
}

/******************************************************************************
 * @name  rtc_isr     
 *
 * @brief  Interrupt service routine of real-time counter 
 *
 * @param       None
 *
 * @return     None
 *
 *****************************************************************************
 * This function responses to Interrupt service routine of real-time counter
 *****************************************************************************/
void interrupt VectorNumber_Vrtc cmt_isr(void)
{
  if (audio_event == USB_APP_DATA_RECEIVED){
    /* update duty */
    if (g_cur_mute[0] == 0)
      duty = audio_data_recv[audio_sample];
    else
      duty = 0;
    audio_sample+=1;
    if (7 < audio_sample){
      audio_sample = 0;
      audio_event = 0;
    }
  }
  RTCSC_RTIF = 1; 
}

