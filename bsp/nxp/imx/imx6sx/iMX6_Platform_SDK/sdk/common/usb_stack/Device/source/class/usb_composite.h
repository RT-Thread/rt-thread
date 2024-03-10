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
 * @file usb_composite.h
 *
 * @author
 *
 * @version
 *
 * @date
 *
 * @brief The file contains USB stack Video class layer API header function.
 *
 *****************************************************************************/

#ifndef _USB_COMPOSITE_H
#define _USB_COMPOSITE_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "types.h"
#include "usb_class.h"
#include "usb_descriptor.h"

/******************************************************************************
 * Macro's
 *****************************************************************************/
/* Audio class type */ 
#define AUDIO_COMP_CC                           (0x01)
/* CDC class type */
#define CDC_COMP_CC                             (0x02)
/* HID class type */
#define HID_COMP_CC                             (0x03)
/* MSD class type */
#define MSD_COMP_CC                             (0x08)
/* Video class type */
#define VIDEO_COMP_CC                           (0x0e)
/* PHDC class type */
#define PHDC_COMP_CC                            (0x0f)
/* DFU class type */
#define DFU_COMP_CC                             (0xfe)

/******************************************************************************
 * Types
 *****************************************************************************/
/* application callback struct */ 
typedef struct _CLASS_APP_CALLBACK_STRUCT
{
    USB_CLASS_CALLBACK composite_class_callback;
    USB_REQ_FUNC       vendor_req_callback; 
    USB_CLASS_CALLBACK param_callback;                              
    USB_CLASS_SPECIFIC_HANDLER_FUNC param_specific_callback;
}CLASS_APP_CALLBACK_STRUCT, _PTR_ CLASS_APP_CALLBACK_STRUCT_PTR;

/* composite callback struct */
typedef struct _COMPOSITE_CALLBACK_STRUCT
{
    /* Number of class support */
    uint_8 count;
    /* Array of Endpoints Structures */
    CLASS_APP_CALLBACK_STRUCT_PTR class_app_callback[COMP_CLASS_UNIT_COUNT];
}COMPOSITE_CALLBACK_STRUCT;

/* Class architecture struct */
typedef struct _CLASS_ARC_STRUCT
{
    uint_8 class_type;
    uint_8 value[1];
}CLASS_ARC_STRUCT, _PTR_ CLASS_ARC_STRUCT_PTR;

/* Endpoint architecture struct */
typedef struct _ENDPOINT_ARC_STRUCT
{
    uint_8 ep_count;
    uint_8 value[1];
}ENDPOINT_ARC_STRUCT, _PTR_ ENDPOINT_ARC_STRUCT_PTR;

/* Interface architecture struct */
typedef struct _INTERFACE_ARC_STRUCT
{
    uint_8 interface_count;
    uint_8 value[1];
}INTERFACE_ARC_STRUCT, _PTR_ INTERFACE_ARC_STRUCT_PTR;

/******************************************************************************
 * Global function prototypes
 *****************************************************************************/
extern uint_8 USB_Composite_Init (
    uint_8    controller_ID,                /* [IN] Controller ID */
    COMPOSITE_CALLBACK_STRUCT *composite_callback_ptr  /* [IN] Poiter to class info */
);

extern uint_8 USB_Composite_DeInit(
    uint_8    controller_ID                            /* [IN] Controller ID */
);
#endif
/* EOF */