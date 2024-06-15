#ifndef __usb_event_h__
#define __usb_event_h__ 
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
* $FileName: usbevent.h$
* $Version : 0.0.0.1$
* $Date    : Nov-18-2009$
*
* Comments:
*
*   
*
*END************************************************************************/
#include "types.h"


/*--------------------------------------------------------------------------*/
/*
**                            MACRO DEFINITIONS
*/

#define USB_EVENT_OK                       0x00
#define USB_EVENT_ERROR                    0x01
#define USB_EVENT_SET                      0x02
#define USB_EVENT_NOT_SET                  0x03
#define USB_EVENT_VALID                    0x04
#define USB_EVENT_INVALID                  0x05

/*--------------------------------------------------------------------------*/
/*
**                            DATATYPE DECLARATIONS
*/
#ifdef __CC_ARM
	#pragma push
	#pragma pack(1)
#endif
typedef struct usb_event 
{
	boolean VALID;
	uint_32 VALUE;
} USB_EVENT_STRUCT, _PTR_ USB_EVENT_STRUCT_PTR;
/*---------------------------------------------------------------------
**
** 
*/

/*--------------------------------------------------------------------------*/
/*
** FUNCTION PROTOTYPES
*/

#ifdef __cplusplus
extern "C" {
#endif

extern uint_16 _usb_event_init(USB_EVENT_STRUCT_PTR);
extern uint_16 _usb_event_clear(USB_EVENT_STRUCT_PTR, uint_32);
extern uint_16 _usb_event_set(USB_EVENT_STRUCT_PTR, uint_32);
extern uint_16 _usb_event_wait_ticks(USB_EVENT_STRUCT_PTR, uint_32, uint_8, uint_16);

#ifdef __cplusplus
}
#endif

#ifdef __CC_ARM
	#pragma pop
#endif
#endif
/* EOF */
