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
* $FileName: usb_batt_chg.c$
* $Version : 1.0.0.0$
* $Date    : Apr-12-2011$
*END**************************************************************************/

/* Include files section *****************************************************/
#include "types.h"
#include "usb_devapi.h"
#include "usbevent.h"
#include "usb_batt_chg.h"
#include "derivative.h"

#include <stdlib.h>
#if (defined(__CWCC__)||defined(__IAR_SYSTEMS_ICC__) || defined(__CC_ARM))
	#include <cstring>
#elif defined(__GNUC__)
  #include <string.h>
#else
  #error Not supported compiler type
#endif

/* Private memory definition *************************************************/
static volatile USB_BATT_CHG_STRUCT*  usb_batt_chg_struct_ptr;

/* Private function declaration **********************************************/
static void _usb_batt_chg_dp_pullup_enable(boolean dp_pullup_enable);

/* Clock speed default (48MHz) */
#define USB_BATT_CHG_CLOCK_SPEED_DEFAULT 		(48)


/*FUNCTION*--------------------------------------------------------------------
* Function name:          _usb_batt_chg_init
* Parameters passed in:   init_struct       [IN]
* Returned value:
* Comment:
* 
*END*-------------------------------------------------------------------------*/
uint_32 _usb_batt_chg_init(USB_BATT_CHG_INIT_STRUCT* init_struct_ptr)
{     
  /* Debug info */
  #if(USB_BATT_CHG_DEBUG_ENABLE == TRUE)
    DEBUG_INFO_TRACE("_usb_batt_chg_init, Initialization phase.");      
  #endif 
    
  /* Check the members of the initialization structure */
  if((init_struct_ptr->ext_vbus_detect_circuit_use == FALSE)            ||    /* The external VBUS IC should be present */
     (init_struct_ptr->ext_vbus_detect_enable_disable_func == NULL)     ||    /* Valid function for enable/disable VBUS detection required */
     (init_struct_ptr->ext_vbus_detect_update_vbus_status_func == NULL) ||    /* Valid function required */
     (init_struct_ptr->ext_batt_chg_circuit_use == FALSE)               ||    /* The external Battery Charging IC should be present */
     (init_struct_ptr->ext_batt_chg_circuit_enable_disable_func == NULL))     /* Valid function to enable/disable Batt chg IC required */
  {
    return USBERR_INVALID_PARAMETER;
  }
  
  /* Check if the USB controller is in device mode */
  if(USB0_CTL & USB_CTL_HOSTMODEEN_MASK)
  {
    return USBERR_INIT_FAILED; 
  }
  
  /* Initialize the USB Battery charging interface */
  usb_batt_chg_struct_ptr = (USB_BATT_CHG_STRUCT*)malloc(sizeof(USB_BATT_CHG_STRUCT));   
  /* Check the pointer returned */
  if(usb_batt_chg_struct_ptr == NULL)
  {
    return USBERR_ALLOC;
  }
  memset((USB_BATT_CHG_STRUCT*)usb_batt_chg_struct_ptr, 0, sizeof(USB_BATT_CHG_STRUCT));
       
  /* Copy the initialization parameters related to the external ICs (VBUS detect and battery mngmt.) */
  usb_batt_chg_struct_ptr->usb_batt_chg_init.ext_vbus_detect_circuit_use              = init_struct_ptr->ext_vbus_detect_circuit_use;
  usb_batt_chg_struct_ptr->usb_batt_chg_init.ext_vbus_detect_enable_disable_func      = init_struct_ptr->ext_vbus_detect_enable_disable_func;
  usb_batt_chg_struct_ptr->usb_batt_chg_init.ext_vbus_detect_update_vbus_status_func  = init_struct_ptr->ext_vbus_detect_update_vbus_status_func; 
  usb_batt_chg_struct_ptr->usb_batt_chg_init.ext_batt_chg_circuit_use                 = init_struct_ptr->ext_batt_chg_circuit_use;
  usb_batt_chg_struct_ptr->usb_batt_chg_init.ext_batt_chg_circuit_enable_disable_func = init_struct_ptr->ext_batt_chg_circuit_enable_disable_func;
    
  /* Initialize the event used for application signaling */
  (void)_usb_event_init((USB_EVENT_STRUCT*)(&(usb_batt_chg_struct_ptr->usb_batt_chg_event)));
                                   
  /* Enable the external VBUS detect and battery charging circuits */
  usb_batt_chg_struct_ptr->usb_batt_chg_init.ext_vbus_detect_enable_disable_func(TRUE);
  usb_batt_chg_struct_ptr->usb_batt_chg_init.ext_batt_chg_circuit_enable_disable_func(TRUE);
   
  /* Initialize the USBDCD module */   
  /* Performs updates to the CLOCK register if there are none defaull values */
  if((USB_BATT_CHG_CLOCK_SPEED_DEFAULT != USB_BATT_CHG_CLOCK_SPEED) || (!USB_BATT_CHG_CLOCK_UNIT_MHZ)) 
  {
    USBDCD_CLOCK = USBDCD_CLOCK_CLOCK_SPEED(USB_BATT_CHG_CLOCK_SPEED) | USB_BATT_CHG_CLOCK_UNIT_MHZ; 
  }  
   
  /* Perform the timing registers updates */
  USBDCD_TIMER0 = USBDCD_TIMER0_TSEQ_INIT(init_struct_ptr->usb_batt_chg_timings_config.time_seq_init);
  if(init_struct_ptr->usb_batt_chg_timings_config.time_dcd_dbnc >= T_DCD_DBNC)
  {
    USBDCD_TIMER1 = USBDCD_TIMER1_TDCD_DBNC(init_struct_ptr->usb_batt_chg_timings_config.time_dcd_dbnc);   
  }
  else
  {
    /* Debug info */
    #if(USB_BATT_CHG_DEBUG_ENABLE == TRUE)
      DEBUG_INFO_TRACE("_usb_batt_chg_init, WARNING: T_DCD_DBNC less than 10msec!");  
    #endif  
  }
  if(init_struct_ptr->usb_batt_chg_timings_config.time_vdpsrc_on >= T_VDPSRC_ON)
  {
    USBDCD_TIMER1 |= USBDCD_TIMER1_TVDPSRC_ON(init_struct_ptr->usb_batt_chg_timings_config.time_vdpsrc_on); 
  }
  else
  {
    /* Debug info */
    #if(USB_BATT_CHG_DEBUG_ENABLE == TRUE)
      DEBUG_INFO_TRACE("_usb_batt_chg_init, WARNING: T_VDPSRC_ON less than 40msec!");  
    #endif      
  }
  if(init_struct_ptr->usb_batt_chg_timings_config.time_vdpsrc_con >= T_VDPSRC_CON)
  {
    USBDCD_TIMER2 = USBDCD_TIMER2_TVDPSRC_CON(init_struct_ptr->usb_batt_chg_timings_config.time_vdpsrc_con); 
  }
  else
  {
    /* Debug info */
    #if(USB_BATT_CHG_DEBUG_ENABLE == TRUE)
      DEBUG_INFO_TRACE("_usb_batt_chg_init, WARNING: T_VDPSRC_CON less than 40msec!");  
    #endif    
  }
  USBDCD_TIMER2 |= USBDCD_TIMER2_CHECK_DM(init_struct_ptr->usb_batt_chg_timings_config.time_check_d_minus); 
      
  /* Updates the rest of the battery charging structure members (timing related) */
  usb_batt_chg_struct_ptr->usb_batt_chg_init.usb_batt_chg_timings_config.time_seq_init      = (uint_16)((USBDCD_TIMER0 & USBDCD_TIMER0_TSEQ_INIT_MASK) >> USBDCD_TIMER0_TSEQ_INIT_SHIFT);
  usb_batt_chg_struct_ptr->usb_batt_chg_init.usb_batt_chg_timings_config.time_dcd_dbnc      = (uint_16)((USBDCD_TIMER1 & USBDCD_TIMER1_TDCD_DBNC_MASK) >> USBDCD_TIMER1_TDCD_DBNC_SHIFT);
  usb_batt_chg_struct_ptr->usb_batt_chg_init.usb_batt_chg_timings_config.time_vdpsrc_on     = (uint_16)((USBDCD_TIMER1 & USBDCD_TIMER1_TVDPSRC_ON_MASK));
  usb_batt_chg_struct_ptr->usb_batt_chg_init.usb_batt_chg_timings_config.time_vdpsrc_con    = (uint_16)((USBDCD_TIMER2 & USBDCD_TIMER2_TVDPSRC_CON_MASK) >> USBDCD_TIMER2_TVDPSRC_CON_SHIFT);
  usb_batt_chg_struct_ptr->usb_batt_chg_init.usb_batt_chg_timings_config.time_check_d_minus = (uint_8)(USBDCD_TIMER2 & USBDCD_TIMER2_CHECK_DM_MASK);
  
  /* Perform a software reset */
  USBDCD_CONTROL |= USBDCD_CONTROL_SR_MASK;
  /* Enable the interrupt */
  USBDCD_CONTROL |= USBDCD_CONTROL_IE_MASK;
  /* Note: the initialization of the charging detection is done as long as the 
     VBUS contact detection has been done */  
  
  return USB_OK;
}


/*FUNCTION*--------------------------------------------------------------------
* Function name:          _usb_batt_chg_uninit
* Parameters passed in:                                
* Returned value:
* Comment:                Function dealing with specific driver memory free
* 
*END*-------------------------------------------------------------------------*/
uint_32 _usb_batt_chg_uinit(void)
{  
  /* Debug info */
  #if(USB_BATT_CHG_DEBUG_ENABLE == TRUE)
    DEBUG_INFO_TRACE("_usb_batt_chg_uninit, Uninitialization phase.");  
  #endif   
  
  if(usb_batt_chg_struct_ptr == NULL)
  {
    /* Debug info */
    #if(USB_BATT_CHG_DEBUG_ENABLE == TRUE)
      DEBUG_INFO_TRACE("_usb_batt_chg_uninit, ERROR: Parameters wrong!");  
    #endif 
    return USBERR_INVALID_PARAMETER; 
  }
       
  /* Deallocate the memory */
  free((USB_BATT_CHG_STRUCT*)usb_batt_chg_struct_ptr);
  /* Reset the battery charging struct pointer */
  usb_batt_chg_struct_ptr = NULL;
  
  /* Debug info */
  #if(USB_BATT_CHG_DEBUG_ENABLE == TRUE)
    DEBUG_INFO_TRACE("_usb_batt_chg_uninit, SUCCESS!");  
  #endif  
     
  return USB_OK;  
}


/*FUNCTION*--------------------------------------------------------------------
* Function name:        _usb_batt_chg_register_callback
* Returned value:       None
* Comment:              Function used to register the application callback function
* 
*END*-------------------------------------------------------------------------*/ 
uint_32 _usb_batt_chg_register_callback(usb_batt_chg_callback callback)
{      
  if(NULL == usb_batt_chg_struct_ptr)
  {
    /* Debug info */
    #if(USB_BATT_CHG_DEBUG_ENABLE == TRUE)
      DEBUG_INFO_TRACE("_usb_batt_chg_register_callback, ERROR: Parameters wrong!");  
    #endif
  
    return USBERR_INVALID_PARAMETER;
  }     
  
  /* Save the provided callback */
  usb_batt_chg_struct_ptr->app_callback = callback;
  
  /* Debug info */
  #if(USB_BATT_CHG_DEBUG_ENABLE == TRUE)
    DEBUG_INFO_TRACE("_usb_batt_chg_register_callback, SUCCESS!");  
  #endif  
  
  return USB_OK;
}


/*FUNCTION*--------------------------------------------------------------------
* Function name:        _usb_batt_chg_ext_isr
* Returned value:       None
* Comment:              Function to enable the pending external interrupt from 
*                       the VBUS detection IC
* 
*END*-------------------------------------------------------------------------*/ 
void _usb_batt_chg_ext_isr(void)
{
  if(usb_batt_chg_struct_ptr != NULL)
  {
    usb_batt_chg_struct_ptr->pending_vbus_det_ext_isr = TRUE;
  }
}


/*FUNCTION*--------------------------------------------------------------------
* Function name:        _usb_batt_chg_task
* Returned value:       None
* Comment:              The battery charger driver task; the main purpose of the  
*                       task is to check if there is any battery charger event 
*                       pending; if it found one then the application callback 
*                       is launched; due to the fact that the callback's size is 
*                       application dependent, it cannot be launched from the 
*                       interrupt routine (the ISR is kept as tight as possible)
*END*-------------------------------------------------------------------------*/
void _usb_batt_chg_task(void)
{     
  USB_EVENT_STRUCT  event_pending;
    
  /* Debug info */
  #if(USB_BATT_CHG_DEBUG_ENABLE == TRUE)
    DEBUG_INFO_TRACE("_usb_batt_chg_task, Task occurence.");
  #endif
    
  if(NULL == usb_batt_chg_struct_ptr)
  {
    return;  
  }    
  
  /* Check if there is any pending VBUS detection interrupt */
  if(usb_batt_chg_struct_ptr->pending_vbus_det_ext_isr == TRUE)
  {
    /* Clear the pending external interrupt */
    usb_batt_chg_struct_ptr->pending_vbus_det_ext_isr = FALSE; 
           
    /* Update the VBUS valid voltage status */
    usb_batt_chg_struct_ptr->usb_batt_chg_status.vbus_valid = usb_batt_chg_struct_ptr->usb_batt_chg_init.ext_vbus_detect_update_vbus_status_func();
    /* Check the VBUS status */
    if(TRUE == usb_batt_chg_struct_ptr->usb_batt_chg_status.vbus_valid)
    {
      /* The VBUS contacts has been detected */      
      /* Update the sequence state */
      usb_batt_chg_struct_ptr->usb_batt_chg_status.dev_state = USB_BATT_CHG_STATE_VBUS_DETECT;
      /* Start the charger detection process */
      USBDCD_CONTROL |= USBDCD_CONTROL_START_MASK;
    }
    else
    {
      /* The PD has been unplugged from the USB bus */    	
      /* Apply a software reset */ 
      USBDCD_CONTROL |= USBDCD_CONTROL_SR_MASK;
      
      /* Update the status structure */
      usb_batt_chg_struct_ptr->usb_batt_chg_status.error_type = no_error;       
      /* Reset the charger port type information */
      usb_batt_chg_struct_ptr->usb_batt_chg_status.charger_type = USB_BATT_CHG_PORT_TYPE_NO_PORT;
       
      /* Call the application callback with unplug event */
      usb_batt_chg_struct_ptr->app_callback(USB_BATT_CHG_EVENT_UNPLUGGED, (USB_BATT_CHG_STATUS*)&(usb_batt_chg_struct_ptr->usb_batt_chg_status));
    }
    
    /* Initialize the sequence state information */
    usb_batt_chg_struct_ptr->usb_batt_chg_status.dev_state = USB_BATT_CHG_STATE_INIT; 
  }
  else
  { /* No external VBUS detection interrupt pending */
    /* Prepare the event pending */
    event_pending = usb_batt_chg_struct_ptr->usb_batt_chg_event;
    
    /* Check if there is any valid pending event */
    if((event_pending.VALID == USB_EVENT_VALID) && event_pending.VALUE)
    {
      /* Debug info */
      #if(USB_BATT_CHG_DEBUG_ENABLE == TRUE)
        DEBUG_INFO_TRACE("_usb_batt_chg_task, App. callback started.");  
      #endif    
      
      /* Call the application callback */
      usb_batt_chg_struct_ptr->app_callback((USB_BATT_CHG_EVENT)event_pending.VALUE, 
                                                                (USB_BATT_CHG_STATUS*)&(usb_batt_chg_struct_ptr->usb_batt_chg_status));
      /* Clear all events */
      _usb_event_clear((USB_EVENT_STRUCT*)&(usb_batt_chg_struct_ptr->usb_batt_chg_event), ~((uint_32)USB_BATT_CHG_EVENT_NO_EVENT));  
    }    
  }  
}


/*FUNCTION*--------------------------------------------------------------------
* Function name:        USBDCD_ISR
* Returned value:       None
* Comment:              Service interrupt for USBDCD; process the hardware 
*                       dependent actions; at the end it will send an event
*                       which is further processed by the task
*
* Note: The USBDCD_ISR() function should be also assigned in the vector table from 
*       the 'vectors.c' file (Vector: 90, IRQ: 74)
*END*-------------------------------------------------------------------------*/
#if (defined __MK_xxx_H__)
	void USBDCD_ISR(void)
#elif (defined MCU_mcf51jf128)
	void interrupt VectorNumber_Vusbdcd USBDCD_ISR(void)
#endif
{
  uint_32 status;
  uint_32 chg_type;
  
  /* Debug info */
  #if(USB_BATT_CHG_DEBUG_ENABLE == TRUE)
    DEBUG_INFO_TRACE("USBDCD_ISR, ISR occurence.");  
  #endif  
  
  /* Read the status register */
  status = USBDCD_STATUS;
  
  /* Clear the CONTROL.IF flag by writting a 1 to the CONTROL.IACK */
  USBDCD_CONTROL |= USBDCD_CONTROL_IACK_MASK;
  
  /* Determine the root cause of DCD interrupt */
  if(status & USBDCD_STATUS_ERR_MASK)
  {
    /* Error occurs */
    /* Check if the timeout has occured */
    if(status & USBDCD_STATUS_TO_MASK)
    {
      /* Timeout occurs */
      /* Reset the module; this will also disable the module */ 
      USBDCD_CONTROL |= USBDCD_CONTROL_SR_MASK;
      
      /* Update the status structure */
      usb_batt_chg_struct_ptr->usb_batt_chg_status.error_type = error_seq_timeout;
      
      /* Update the sequence state */
      usb_batt_chg_struct_ptr->usb_batt_chg_status.dev_state = USB_BATT_CHG_STATE_TIMEOUT;
      
      /* Send an event to the task */
      _usb_event_set((USB_EVENT_STRUCT*)&(usb_batt_chg_struct_ptr->usb_batt_chg_event), USB_BATT_CHG_EVENT_ERROR);
    }
    else
    {
      /* Error on the Charge Port Detection: D- line voltage above VLCG */
      /* Reset the module; this will also disable the module */ 
      USBDCD_CONTROL |= USBDCD_CONTROL_SR_MASK; 
      
      /* Update the status structure */
      usb_batt_chg_struct_ptr->usb_batt_chg_status.error_type = error_unknown_port_type;      
      
      /* Update the sequence state */
      usb_batt_chg_struct_ptr->usb_batt_chg_status.dev_state = USB_BATT_CHG_STATE_COMPLETE;      
      
      /* Send an event to the task */
      _usb_event_set((USB_EVENT_STRUCT*)&(usb_batt_chg_struct_ptr->usb_batt_chg_event), USB_BATT_CHG_EVENT_ERROR);      
    }
  }
  else
  {
    switch(status & USBDCD_STATUS_SEQ_STAT_MASK)
    {
      case USBDCD_STATUS_SEQ_STAT_CHARGER_DETECTED:
            /* The Charging Port Detection has been completed */            
            /* Check if the detected port is either a charging port or an standard Host Port */
            chg_type = status & USBDCD_STATUS_SEQ_RES_MASK; 
            if(chg_type == USBDCD_STATUS_SEQ_RES_STD_HOST)
            {
              /* The Portable Device (PD) is attached to a Standard Downstream Port (SDP) */
              /* Reset the module; this will also disable the module */ 
              USBDCD_CONTROL |= USBDCD_CONTROL_SR_MASK;
                          
              /* Update the device type */
              usb_batt_chg_struct_ptr->usb_batt_chg_status.charger_type = USB_BATT_CHG_PORT_TYPE_SDP; 
             
              /* Update the sequence state */
              usb_batt_chg_struct_ptr->usb_batt_chg_status.dev_state = USB_BATT_CHG_STATE_COMPLETE;
                             
              /* Send an event to the task */
              _usb_event_set((USB_EVENT_STRUCT*)&(usb_batt_chg_struct_ptr->usb_batt_chg_event), (uint_32)USB_BATT_CHG_EVENT_PHASE_COMPLETE);
            }
            else
            {
              if(chg_type == USBDCD_STATUS_SEQ_RES_CHG_PORT)
              {
                /* The Portable Device (PD) is attached to a Charging Port (CP), either a Dedicated Charging Port (DCP) 
                   or a Charging Downstream Port (CDP) */ 
                /* Move to the next phase: charging type detection: either a 
                    Dedicated Charging Port or a Charging downstream Port */                
                
                /* Update the sequence state to the next phase */
                usb_batt_chg_struct_ptr->usb_batt_chg_status.dev_state = USB_BATT_CHG_STATE_CHARGER_TYPE_DETECT;
                
                /* Connect the D+ pullup resistor */
                _usb_batt_chg_dp_pullup_enable(TRUE);
              }
            }            
   
            break;
            
      case USBDCD_STATUS_SEQ_STAT_CHARGER_TYPE_DETECTED:
            /* The Charging Type Detection has been completed */
            /* Reset the module; this will also disable the module */               
            USBDCD_CONTROL |= USBDCD_CONTROL_SR_MASK; 
            
            /* Update the sequence state */
            usb_batt_chg_struct_ptr->usb_batt_chg_status.dev_state = USB_BATT_CHG_STATE_COMPLETE; 
            
            /* Check the charging port type */ 
            chg_type = status & USBDCD_STATUS_SEQ_RES_MASK;
            if(chg_type == USBDCD_STATUS_SEQ_RES_CHG_HOST_PORT)
            {
              /* The Portable Device (PD) is attached to a Charging Downstream Port (CDP) */ 
              /* Update the charger port type */
              usb_batt_chg_struct_ptr->usb_batt_chg_status.charger_type = USB_BATT_CHG_PORT_TYPE_CDP;
            }
            else
            {
              if(chg_type == USBDCD_STATUS_SEQ_RES_DED_CHG_PORT)
              {
                /* The Portable Device (PD) is attached to a Dedicated Charging Port (DCP) */
                /* Disable the D+ pullup resistor */
                _usb_batt_chg_dp_pullup_enable(FALSE);
                
                /* Update the charger port type */
                usb_batt_chg_struct_ptr->usb_batt_chg_status.charger_type = USB_BATT_CHG_PORT_TYPE_DCP;                
              }
            }
            
            /* Send an event to the task */
            _usb_event_set((USB_EVENT_STRUCT*)&(usb_batt_chg_struct_ptr->usb_batt_chg_event), USB_BATT_CHG_EVENT_PHASE_COMPLETE);   
                      
            break;
    }
  }    
}


/*FUNCTION*--------------------------------------------------------------------
* Function name:          _usb_batt_chg_dp_pullup_enable
* Parameters passed in:   dp_pullup_enable
* Returned value:
* Comment:                Function to enable or disable the D+ pullup resistor
* 
*END*-------------------------------------------------------------------------*/
static void _usb_batt_chg_dp_pullup_enable(boolean dp_pullup_enable)
{ 
  /* Enable the OTG module if it was disabled */
  if(!(USB0_OTGCTL & USB_OTGCTL_OTGEN_MASK))
  {
    USB0_OTGCTL |= USB_OTGCTL_OTGEN_MASK;
  }
  
  if(TRUE == dp_pullup_enable)
  {	  
    /* Enable the D+ pullup resistor */
    USB0_OTGCTL |= USB_OTGCTL_DPHIGH_MASK;  
  }
  else
  {
	/* Disable the D+ pullup resistor */
    USB0_OTGCTL &= ~USB_OTGCTL_DPHIGH_MASK;  
  }
}
