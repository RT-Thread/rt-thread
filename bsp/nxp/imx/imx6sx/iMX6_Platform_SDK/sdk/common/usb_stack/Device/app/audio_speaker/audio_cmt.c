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
 * @file audio_cmt.c
 *
 * @author
 *
 * @version
 *
 * @date    
 *
 * @brief   This file configures CMT for Timer implementation
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
 * @name   cmt_init    
 *
 * @brief   Init timer   
 *
 * @param      None
 *
 * @return     None
 *
 *****************************************************************************
 * This function init the real-time counter
 *****************************************************************************/
void cmt_init(void)
{
  /* CMTMSC: EOCF=0,CMTDIV1=0,CMTDIV0=0,EXSPC=0,BASE=0,FSK=0,EOCIE=0,MCGEN=0 */
  CMTMSC = 0x00;                
  /* CMTOC: IROL=0,CMTPOL=0,IROPEN=0,??=0,??=0,??=0,??=0,??=0 */
  CMTOC = 0x00;                 
  /* CMTCG1: PH7=0,PH6=0,PH5=0,PH4=0,PH3=0,PH2=0,PH1=0,PH0=0,PL7=0,PL6=0,PL5=0,PL4=0,PL3=0,PL2=0,PL1=0,PL0=0 */
  CMTCG1 = 0x00;               
  /* CMTCG2: SH7=0,SH6=0,SH5=0,SH4=0,SH3=0,SH2=0,SH1=0,SH0=0,SL7=0,SL6=0,SL5=0,SL4=0,SL3=0,SL2=0,SL1=0,SL0=0 */
  CMTCG2 = 0x00;               
  /* CMTCMD12: MB15=0,MB14=0,MB13=0,MB12=0,MB11=0,MB10=0,MB9=0,MB8=1,MB7=0,MB6=1,MB5=1,MB4=1,MB3=0,MB2=1,MB1=1,MB0=0 */
  CMTCMD12 = 0x0176;           
  /* CMTCMD34: SB15=0,SB14=0,SB13=0,SB12=0,SB11=0,SB10=0,SB9=0,SB8=0,SB7=0,SB6=0,SB5=0,SB4=0,SB3=0,SB2=0,SB1=0,SB0=0 */
  CMTCMD34 = 0x00;             
  /* CMTMSC: EOCF=0,CMTDIV1=0,CMTDIV0=0,EXSPC=0,BASE=0,FSK=0,EOCIE=1,MCGEN=1 */
  CMTMSC = 0x03;  
}

/******************************************************************************
 * @name  cmt_isr     
 *
 * @brief  Interrupt service routine of timer 
 *
 * @param	 None
 *
 * @return   None
 *
 *****************************************************************************
 * This function responses to Interrupt service routine of real-time counter
 *****************************************************************************/
void interrupt VectorNumber_Vcmt cmt_isr(void)
{
  if (audio_event == USB_APP_DATA_RECEIVED){
    /* update duty */
    if(g_cur_mute[0] == 0)
    {
        duty = audio_data_recv[audio_sample];
    }
    else
    {
        duty = 0;
    }
    audio_sample+=1;
    if (7 < audio_sample){
      audio_sample = 0;
      audio_event = 0;
    }
  }
  (void)CMTMSC; 
  (void)CMTCMD2;
}

