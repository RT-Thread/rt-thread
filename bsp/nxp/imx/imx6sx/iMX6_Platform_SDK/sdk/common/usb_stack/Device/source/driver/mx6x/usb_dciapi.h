/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
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
 * @file usb_dciapi.h
 *
 * @author 
 *
 * @version 
 *
 * @date Jun-05-2009
 *
 * @brief The file contains DCI api function definetions .
 *
 *****************************************************************************/

#ifndef _USB_DCIAPI_H
#define _USB_DCIAPI_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "types.h"
#include "usb_devapi.h"

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define MAX_SUPPORTED_ENDPOINTS (USB_SERVICE_MAX_EP + 1)
                                           /* Maximum endpoints supported */
#define MIN_SUPPORTED_ENDPOINTS (1)        /* Minimum endpoints supported */
#define DOUBLE_BUFFERED_ENPOINT_NUMBER (0) /* First double buffered endpoint */

#if defined(CHIP_MX6DQ) || defined(CHIP_MX6SDL)
	#define NUM_USB_CONTROLLERS	(4)
#else
	#define NUM_USB_CONTROLLERS	(3)
#endif

/******************************************************************************
 * Types
 *****************************************************************************/
typedef enum USB_Controllers_t
{
	USB_CORE_1,
	USB_CORE_2,
	USB_CORE_3,
	USB_CORE_4,
}USB_Controllers_t;

#if HIGH_SPEED_DEVICE
// typedef struct dqh_setup_t {
//     unsigned int dqh_word0;
//     unsigned int dqh_word1;
//     unsigned int dqh_word2;
//     unsigned int dqh_word3;
//     unsigned int dqh_word4;
//     unsigned int dqh_word5;
//     unsigned int dqh_word6;
//     unsigned int dqh_word7;
//     unsigned int dqh_word8;
//     unsigned int dqh_word9;
//     unsigned int dqh_word10;
//     unsigned int dqh_word11;
// } dqh_setup_t;
// 
// typedef struct dtd_setup_t {
//     unsigned int dtd_word0;
//     unsigned int dtd_word1;
//     unsigned int dtd_word2;
//     unsigned int dtd_word3;
//     unsigned int dtd_word4;
//     unsigned int dtd_word5;
//     unsigned int dtd_word6;
//     unsigned int dtd_word7;
// } dtd_setup_t;
// 
// typedef struct dqh_t {
//     unsigned int dqh_base;
//     unsigned int next_link_ptr;
//     unsigned int buffer_ptr0;
//     unsigned int buffer_ptr1;
//     unsigned int buffer_ptr2;
//     unsigned int buffer_ptr3;
//     unsigned int buffer_ptr4;
//     unsigned short total_bytes;
//     unsigned short mps;
//     unsigned short current_offset;
//     unsigned char zlt;
//     unsigned char ios;
//     unsigned char terminate;
//     unsigned char ioc;
//     unsigned char status;
// 	unsigned char mult;
// } dqh_t;
// 
// typedef struct dtd_t {
//     unsigned int dtd_base;
//     unsigned int next_link_ptr;
//     unsigned int buffer_ptr0;
//     unsigned int buffer_ptr1;
//     unsigned int buffer_ptr2;
//     unsigned int buffer_ptr3;
//     unsigned int buffer_ptr4;
//     unsigned short total_bytes;
//     unsigned short current_offset;
//     unsigned char terminate;
//     unsigned char ioc;
//     unsigned char status;
// } dtd_t;
// 
// typedef struct {
//     unsigned int ep_dqh_base_addrs; /* Base Address of Queue Header */
//     unsigned int ep_dtd_base_addrs; /* Base Address of Transfer Descriptor */
//     unsigned int ep0_buffer_addrs;  /* Buffer Addres for EP0 IN  */
//     unsigned int buffer1_address;   /* Buffer1 address for bulk transfer */
//     unsigned int buffer1_status;    /* Status of Buffer1 */
//     unsigned int buffer2_address;   /* Buffer2 address for bulk transfer */
//     unsigned int buffer2_status;    /* Status of Buffer2 */
// } buffer_map_t;

/* USB standard device request*/ 
typedef struct usb_standrd_device_request  {
    unsigned char bmRequestType;
    unsigned char bRequest;
    unsigned short wValue;
    unsigned short wIndex;
    unsigned short wLength;
} usb_standard_device_request_t;

#endif // HIGH_SPEED_DEVICE

 /*****************************************************************************
 * Global Functions
 *****************************************************************************/
extern uint_8 USB_DCI_Init(
    uint_8    controller_ID,
    uint_8    bVregEn
);


extern uint_8 USB_DCI_Init_EndPoint(
    uint_8              controller_ID, 
    USB_EP_STRUCT_PTR   ep_ptr,        
    boolean             double_buffered
);

// extern uint_8 USB_DCI_Init_EndPoint(
//     uint_8               controller_ID,            
//     USB_EP_STRUCT_PTR    ep_ptr,       
//     boolean              flag          
// );

extern uint_8 USB_DCI_Cancel_Transfer(
    uint_8    controller_ID,   
    uint_8    ep_num,          
    uint_8    direction        
);
   
extern uint_8 USB_DCI_Deinit_EndPoint(
    uint_8    controller_ID,  
    uint_8    ep_num,         
    uint_8    direction       
);

extern void USB_DCI_Stall_EndPoint(
    uint_8    controller_ID, 
    uint_8    ep_num,        
    uint_8    direction      
);

extern void USB_DCI_Unstall_EndPoint(
    uint_8    controller_ID, 
    uint_8    ep_num,        
    uint_8    direction      
);

extern void USB_DCI_Get_Setup_Data( 
    uint_8       controller_ID, 
    uint_8       ep_num,        
    uchar_ptr    buff_ptr       
);

extern uint_8 USB_DCI_Get_Transfer_Status(
    uint_8    controller_ID, 
    uint_8    ep_num,        
    uint_8    direction      
);

extern uint_8 USB_DCI_Recv_Data(
    uint_8           controller_ID, 
    uint_8           ep_num,        
    uchar_ptr        buff_ptr,      
    USB_PACKET_SIZE  size           
);

extern uint_8 USB_DCI_Send_Data(
    uint_8           controller_ID, 
    uint_8           ep_num,        
    uchar_ptr        buff_ptr,      
    USB_PACKET_SIZE  size           
);

extern void  USB_DCI_Set_Address(
    uint_8    controller_ID,
    uint_8    address       
);

extern void USB_DCI_Shutdown(
    uint_8    controller_ID 
);

extern void USB_DCI_Assert_Resume(
    uint_8    controller_ID 
);

extern void Clear_Mem(uint_8* start_addr,uint_32 count, uint_8 val);

#define USB_DCI_Cancel_Transfer _usb_device_cancel_transfer  

#define USB_DCI_Recv_Data _usb_device_recv_data  

#define USB_DCI_Send_Data _usb_device_send_data    

#define USB_DCI_Shutdown _usb_device_shutdown  

#define USB_DCI_Stall_EndPoint _usb_device_stall_endpoint  

#define USB_DCI_Unstall_EndPoint _usb_device_unstall_endpoint  

#define USB_DCI_Get_Transfer_Status _usb_device_get_transfer_status

#define USB_DCI_Get_Setup_Data _usb_device_read_setup_data 

#define USB_DCI_Set_Address _usb_device_set_address  

#define USB_DCI_Assert_Resume _usb_device_assert_resume

// #define USB_DCI_Cancel_Transfer USB_Device_Cancel_Transfer  
// 
// #define USB_DCI_Recv_Data USB_Device_Recv_Data  
// 
// #define USB_DCI_Send_Data USB_Device_Send_Data    
// 
// #define USB_DCI_Shutdown USB_Device_Shutdown  
// 
// #define USB_DCI_Stall_EndPoint USB_Device_Stall_EndPoint  
// 
// #define USB_DCI_Unstall_EndPoint USB_Device_Unstall_EndPoint  
// 
// #define USB_DCI_Get_Transfer_Status USB_Device_Get_Transfer_Status
// 
// #define USB_DCI_Get_Setup_Data USB_Device_Read_Setup_Data 
// 
// #define USB_DCI_Set_Address USB_Device_Set_Address  
// 
// #define USB_DCI_Assert_Resume USB_Device_Assert_Resume  

#endif


