/**HEADER********************************************************************
* 
* Copyright (c) 2010 Freescale Semiconductor;
* All Rights Reserved
*
*************************************************************************** 
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
**************************************************************************
*
* $FileName: usbevent.c$
* $Version : 0.0.0.1$
* $Date    : Nov-18-2009$
*
* Comments:
*
*   
*
*
*END************************************************************************/

#include "usbevent.h"
#include "usb_devapi.h"

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _usb_event_init
* Returned Value   :
* Comments         :
*    
*
*END*----------------------------------------------------------------------*/
uint_16 _usb_event_init
(
USB_EVENT_STRUCT_PTR event
)
{
  event->VALID = USB_EVENT_VALID;
  event->VALUE = 0;
  return  USB_OK;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _usb_event_set
* Returned Value   : 
* Comments         :
*    
*
*END*----------------------------------------------------------------------*/
uint_16 _usb_event_set
(
  USB_EVENT_STRUCT_PTR event ,
  uint_32 value
)
{
    if(event->VALID == USB_EVENT_VALID) {
      event->VALUE |= value;
      return USB_EVENT_VALID;
    }
    return USB_EVENT_INVALID;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _usb_event_clear
* Returned Value   : 
* Comments         :
*    
*
*END*----------------------------------------------------------------------*/
uint_16 _usb_event_clear
(
  USB_EVENT_STRUCT_PTR event ,
  uint_32 bitmask
)
{
   if(event->VALID == USB_EVENT_VALID) {
      event->VALUE &= ~bitmask;
      return USB_EVENT_VALID;
    }
    return USB_EVENT_INVALID;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _usb_event_wait_ticks
* Returned Value   : 
* Comments         :
*    
*
*END*----------------------------------------------------------------------*/
uint_16 _usb_event_wait_ticks
(
  USB_EVENT_STRUCT_PTR event ,
  uint_32 bitmask,
  uint_8  all,
  uint_16 ticks
)
{
	UNUSED(all)
	UNUSED(ticks)
	
     if(event->VALID == USB_EVENT_VALID) {
      if(0x00 != (event->VALUE & bitmask)){
        return USB_EVENT_SET;
      } else {
        return USB_EVENT_NOT_SET;
      }
    }
    return USB_EVENT_INVALID;
    
}
