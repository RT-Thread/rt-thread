/**HEADER**********************************************************************
*
* Copyright (c) Freescale Semiconductor
* All rights reserved 
*
*******************************************************************************
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
*******************************************************************************
*
* $FileName: usb_batt_chg_app.h$
* $Version : 1.0.0.0$
* $Date    : Jun-01-2011$
*END**************************************************************************/

#ifndef _USB_BATT_CHG_APP_H_
  #define _USB_BATT_CHG_APP_H_

  #if (defined MCU_mcf51jf128)
	/* Vector number source */
	#define VectorNumber_Virq  			64 
    #define VectorNumber_Vusbdcd        111
    /* PTC4 shift position */
	#define PCTL_PTC4_MASK 				(1<<4) 
  #endif

#endif /* _USB_BATT_CHG_APP_H_ */
