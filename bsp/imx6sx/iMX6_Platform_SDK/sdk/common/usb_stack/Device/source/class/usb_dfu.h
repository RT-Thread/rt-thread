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
 * @file usb_dfu.h
 *
 * @author
 *
 * @version
 *
 * @date 
 *
 * @brief The file contains USB stack DFU class layer API header function.
 *
 *****************************************************************************/

#ifndef _USB_DFU_H
#define _USB_DFU_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "types.h"
#include "usb_descriptor.h"
#include "usb_class.h"

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define MAX_QUEUE_ELEMS     (4)

 /* class specific requests */
#define USB_DFU_DETACH      (0)
#define USB_DFU_DNLOAD      (1)
#define USB_DFU_UPLOAD      (2)
#define USB_DFU_GETSTATUS   (3)
#define USB_DFU_CLRSTATUS   (4)
#define USB_DFU_GETSTATE    (5)
#define USB_DFU_ABORT       (6)
#define DFU_ENDPOINT        (0x00)

/* for class specific requests */
#define HIGH_BYTE_SHIFT                 (8)
#define MSB_MASK                        (0xFF00)
#define USB_DFU_REQUEST_DIR_MASK        (0x08)
#define USB_DFU_REQUEST_TYPE_MASK       (0x01)
#define REPORT_SIZE                     (4)
#define CLASS_REQ_DATA_SIZE             (0x01)

/* define status for request */
#define USB_OK                  (0x00)
#define USB_ERR_TARGET          (0x01)
#define USB_ERR_FILE            (0x02)
#define USB_ERR_WRITE           (0x03)
#define USB_ERR_ERASE           (0x04)
#define USB_ERR_CHECK_ERASE     (0x05)
#define USB_ERR_PROG            (0x06)
#define USB_ERR_VERIFY          (0x07)
#define USB_ERR_ADDRESS         (0x08)
#define USB_ERR_NOTDONE         (0x09)
#define USB_ERR_FIRMWARE        (0x0A)
#define USB_ERR_VENDOR          (0x0B)
#define USB_ERR_USBR            (0x0C)
#define USB_ERR_POR             (0x0D)
#define USB_ERR_UNKNOWN         (0x0E)
#define USB_ERR_STALLEDPKT      (0x0F)

/* define state for request */
#define USB_APP_IDLE                (0x00)
#define USB_APP_DETACH              (0x01)
#define USB_DFU_IDLE                (0x02)
#define USB_DFU_DNLOAD_SYNC         (0x03)
#define USB_DFU_DNBUSY              (0x04)
#define USB_DFU_DNLOAD_IDLE         (0x05)
#define USB_DFU_MANIFEST_SYNC       (0x06)
#define USB_DFU_MANIFEST            (0x07)
#define USB_DFU_MANIFEST_WAIT_RESET (0x08)
#define USB_DFU_UPLOAD_IDLE         (0x09)
#define USB_DFU_ERROR               (0x0a)
/* define index of fields in Status  */
#define BSTATUS                (0x00)
#define BWPOLLTIMEOUT          (0x01)
#define BSTATE                 (0x04)
#define ISTRING                 (0x05)
/* define index of fields in Status  */
#define POLLTIMEOUT                (0x64)
/******************************************************************************
 * Types
 *****************************************************************************/
 
 /* structure to hold a request in the endpoint queue */
typedef struct _usb_class_dfu_queue
{
    uint_8 controller_ID;   /* Controller ID*/
    uint_8 channel;         /* Endpoint number */
    uint_8_ptr app_buff;    /* Buffer to send */
    USB_PACKET_SIZE size;   /* Size of the transfer */
}USB_CLASS_DFU_QUEUE, *PTR_USB_CLASS_DFU_QUEUE;

/******************************************************************************
 * Global Functions
 *****************************************************************************/
extern uint_8 USB_Class_DFU_Init (
    uint_8                          controller_ID,
    USB_CLASS_CALLBACK              dfu_class_callback,
    USB_REQ_FUNC                    vendor_req_callback,
    USB_CLASS_SPECIFIC_HANDLER_FUNC param_callback
);

extern uint_8 USB_Class_DFU_DeInit (uint_8 controller_ID); 
/*****************************************************************************/
extern void USB_Class_DFU_App_SetIdle(void);
extern void USB_Class_DFU_App_SetDetach(void);
extern void USB_Class_DFU_App_Set_Usbreset(void);
extern uint_8 USB_Class_DFU_App_Getstate(void);
extern void USB_Class_DFU_App_Set_Flag_Manifest(void);
extern uint_8 USB_Class_DFU_App_Get_Flag_Manifest(void);
extern void USB_Class_DFU_App_Reset_Flag_Manifest(void);
extern void USB_Class_DFU_Flashing(void);
#endif
