/******************************************************************************
 * Includes
 *****************************************************************************/
#include "sdk_types.h"
#include "core/interrupt.h"
#include <string.h>
#include "usb_dciapi.h" /* USB DCI API Header File */
#include "usb_devapi.h" /* USB Device API Header File */
#include "usb_mx6.h"
#include "irq_numbers.h"
#include "registers/regsusbcore.h"
#include "registers/regsusbnoncore.h"
#include "registers/regsusbanalog.h"
#include "registers/regsusbphy.h"
#include "registers/regsccm.h"
#include "registers/regsccmanalog.h"
#include "buffers.h"

/*****************************************************************************
 * Forward function declarations
 *****************************************************************************/
static usb_status_t usbd_mx6_dev_init(uint_8 controller_ID);
static void usb_clk_init(uint_8 controller_ID);
static void usb_phy_init(uint_8 controller_ID);
static usb_status_t usb_set_device_mode(uint_8 controller_ID);
static void usbd_ep_qh_init(uint_8 controller_ID,
                            unsigned char endpt_number, unsigned char direction,
		unsigned int max_pkt_len,
		unsigned int zlt, unsigned char mult);
static void usbd_ep_setup(uint_8 controller_ID, unsigned char endpt_number, unsigned char direction, unsigned char ep_type);
static void usbd_setup_qhead(struct dqh_t *qhead);
static void usbd_ep0_init(uint_8 controller_ID);
static usb_status_t usbd_usb_run(uint_8 controller_ID);
static unsigned int usbd_get_dqh(uint_8 controller_ID, unsigned char endpt_number, unsigned char direction);
static unsigned int usbd_get_dtd(uint_8 controller_ID, unsigned char endpt_number, unsigned char direction, unsigned int sz);

static void usb0_isr(void);// *data);
// static void usb1_isr(void *data);

static void USB_Bus_Reset_Handler(uint_8 controller_ID);
static void usbd_setup_packet_handler(USB_DEV_EVENT_STRUCT* event);
static void usbd_ep_complete_handler(USB_DEV_EVENT_STRUCT* event);
static void usbd_ep0_complete(USB_DEV_EVENT_STRUCT* event);
static void usbd_dtd_complete(USB_DEV_EVENT_STRUCT* event);
static void usbd_read_setup_packet(uint_8 controller_ID, unsigned char *setup_packet);
static usb_status_t usbd_send_data_ep0in(uint_8 controller_ID,
                                         unsigned int ep0_data_buffer, unsigned int sz,
                                         unsigned char zlt_enable);
static usb_status_t usbd_receive_data_ep0out(uint_8 controller_ID, unsigned int ep0_data_buffer, unsigned int sz);
static usb_status_t usbd_send_data_epxin(uint_8 controller_ID, unsigned int epx_data_buffer, uint_8 ep_num, unsigned int sz);
static usb_status_t usbd_receive_data_epxout(uint_8 controller_ID, unsigned int epx_data_buffer, uint_8 ep_num, unsigned int sz);
static void usbd_setup_td(struct dtd_t *td);

static inline void writel(unsigned int val, volatile unsigned int *addr);
static inline unsigned int readl(volatile unsigned int * addr);

/*****************************************************************************
 * Definitions
 *****************************************************************************/

#define PRINT_USB_INFO 0
#define PRINT_USB_ERRORS 1

// To activate info printf's, define printf_info as printf
#if PRINT_USB_INFO
    #define printf_info(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
    #define printf_info(fmt, ...)
#endif

// To activate error printf's, define printf_error as printf
#if PRINT_USB_ERRORS
#define printf_error(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
    #define printf_error(fmt, ...) 
#endif

#define MAX_DTDS_PER_EP     5
#define DTD_FREE            0
#define DTD_BUSY            1
#define MAX_ENDPOINT_NUMBER 4

// QH structures are 64-byte aligned
#define TOTAL_QHD_SIZE (SIZE_OF_QHD * (MAX_ENDPOINT_NUMBER * 2))
// TD structures are 64-byte aligned
#define TOTAL_QTD_SIZE ((SIZE_OF_DTD0) * (MAX_ENDPOINT_NUMBER * 2) * MAX_DTDS_PER_EP)

#define NO_ERRORS                       (0)   /* Init value for error */

/* control endpoint transfer types */
#define USB_TRF_UNKNOWN      			(0xFF)

#if CHIP_MX6DQ || CHIP_MX6SDL    
#define BM_USBC_(x) BM_USBC_UOG_##x
#elif CHIP_MX6SL
#define BM_USBC_(x) BM_USBC_UOG1_##x
#endif

#if CHIP_MX6DQ || CHIP_MX6SDL    
#define BP_USBC_(x) BP_USBC_UOG_##x
#elif CHIP_MX6SL
#define BP_USBC_(x) BP_USBC_UOG1_##x
#endif

#if CHIP_MX6DQ || CHIP_MX6SDL    
#define BF_USBC_(x, v) BF_USBC_UOG_##x(v)
#elif CHIP_MX6SL
#define BF_USBC_(x, v) BF_USBC_UOG1_##x(v)
#endif

/*****************************************************************************
 * Variables
 *****************************************************************************/
usb_mx6_hardware_t *usbotg[MAX_USB_STACKS] = {(usb_mx6_hardware_t *) REGS_USBC_BASE}; //,
                                                //(usb_mx6_hardware_t *) REGS_USBCTRL1_BASE};

// #pragma data_alignment=(0x1000)
// unsigned char g_usbd0_qh_buf[TOTAL_QHD_SIZE];
// #pragma data_alignment=(0x1000)
// unsigned char g_usbd1_qh_buf[TOTAL_QHD_SIZE];
// #pragma data_alignment=(0x800)
// unsigned char g_usbd0_td_buf[TOTAL_QTD_SIZE];
// #pragma data_alignment=(0x800)
// unsigned char g_usbd1_td_buf[TOTAL_QTD_SIZE];

unsigned char * g_usbd_qh_bufs[MAX_USB_STACKS] = {0};
unsigned char * g_usbd_td_bufs[MAX_USB_STACKS] = {0};

static uint_8 g_dci_address_state[MAX_USB_STACKS] = {0};
static uint_8 g_dci_controller_Id[MAX_USB_STACKS] = {0};

/* flag status for td */
static struct _td_status
{
    uint_8  status;                  // DTD_BUSY or DTD_FREE
    unsigned int total_bytes;       // Original total bytes to transfer (not used by EP0)
    volatile struct dtd_setup_t *phys_td;   // Pointer to physical TD (not used by EP0)
} g_usbd_td_flag[MAX_USB_STACKS][MAX_ENDPOINT_NUMBER * 2][MAX_DTDS_PER_EP];

// Queue info
static struct _queue_info
{
    uint_8 enq_idx;                 // Enqueue index
    uint_8 deq_idx;                 // Dequeue index
    dtd_setup_t *tail;              // Pointer to dTD at tail
} g_usbd_queue_info[MAX_USB_STACKS][MAX_ENDPOINT_NUMBER * 2];

/*****************************************************************************
 * Global Functions
 *****************************************************************************/

/**************************************************************************//*!
 *
 * @name  USB_DCI_Init
 *
 * @brief The function initializes the Controller layer
 *
 * @param controller_ID : Controller ID
 *
 * @return status
 *         USBERR_INIT_FAILED : could not install interrupt handler
 *         USB_OK    : Success
 ******************************************************************************
 * Initializes the USB controller
 *****************************************************************************/
uint_8 USB_DCI_Init(
    uint_8    controller_ID,   /* [IN] Controller ID */
    uint_8    bVregEn
)
{
    usb_status_t status;
    
    g_usbd_qh_bufs[controller_ID] = (unsigned char *)(QH_BUFFER + TOTAL_QHD_SIZE * controller_ID);
    g_usbd_td_bufs[controller_ID] = (unsigned char *)(TD_BUFFER + TOTAL_QTD_SIZE * controller_ID);
    
    // Clear qh and td bufs.
    memset(g_usbd_qh_bufs[controller_ID], 0, TOTAL_QHD_SIZE);
    memset(g_usbd_td_bufs[controller_ID], 0, TOTAL_QTD_SIZE);
    
//     unsigned char *qh_buf = controller_ID ? g_usbd1_qh_buf : g_usbd0_qh_buf;
    unsigned char *qh_buf = g_usbd_qh_bufs[controller_ID];

    printf_info("%s\n", __func__);

    g_dci_controller_Id[controller_ID] = controller_ID;
    memset(qh_buf, 0x0, sizeof(qh_buf));

    // Initialize hardware
    status = usbd_mx6_dev_init(controller_ID);
    if (status != USB_OK)
    {
        return status;
    }

	usbd_ep0_init(controller_ID);

    status = usbd_usb_run(controller_ID);

    return status;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_DeInit
 *
 * @brief The function de-initializes the Controller layer
 *
 * @param controller_ID : Controller ID
 *
 * @return status
 *         USB_OK    : Always
 ******************************************************************************
 * Un-initializes the USB controller
 *****************************************************************************/
uint_8 USB_DCI_DeInit(
)
{
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Init_EndPoint
 *
 * @brief The function initializes an endpoint
 *
 * @param controller_ID : Controller ID
 * @param ep_ptr        : Pointer to EndPoint Structures
 * @param flag          : Zero Termination
 *
 * @return status
 *         USB_OK                    : When Successfull
 *         USBERR_EP_INIT_FAILED     : When Error
 ******************************************************************************
 *
 * This function initializes an endpoint and the QH
 * entry associated with it. Incase the input parameters are invalid it will
 * return USBERR_EP_INIT_FAILED error.
 *
 *****************************************************************************/
uint_8 USB_DCI_Init_EndPoint(
    uint_8               controller_ID,/* [IN] Controller ID */
    USB_EP_STRUCT_PTR    ep_ptr,       /* [IN] Pointer to Endpoint structure,
                                               (endpoint number,
                                                endpoint type,
                                                endpoint direction,
                                                max packet size) */
    bool_8               flag          /* [IN] Zero Termination */
)
{
	printf_info("%s, ep_num is %d, dir is %d, type is %d\n", __func__, ep_ptr->ep_num, ep_ptr->direction, ep_ptr->type);

	unsigned char mult;

	// Initialize endpoint 0
    if (ep_ptr->ep_num == 0)
    {
        usbd_ep0_init(controller_ID);
        return USB_OK;
    }
	
	switch (ep_ptr->type & 0x3) {
		case EP_TRANSFER_TYPE_CONTROL:
		case EP_TRANSFER_TYPE_BULK:
		case EP_TRANSFER_TYPE_INTERRUPT:
			mult = 0;
            break;
		case EP_TRANSFER_TYPE_ISOCHRONOUS:
			/* Calculate the ISO transfer High-Bandwidth Pipe Multiplier
			  * The ISO endpoints, must set Mult 1, 2, 3.
			 */
			mult = (unsigned char)(1 + (((ep_ptr->size) >> 11) & 0x03));
	}

	usbd_ep_qh_init(controller_ID, ep_ptr->ep_num, ep_ptr->direction, ep_ptr->size, flag, mult);
		
	usbd_ep_setup(controller_ID, ep_ptr->ep_num, ep_ptr->direction, ep_ptr->type);
	
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Cancel_Transfer
 *
 * @brief The function cancels any pending Transfers which ahve not been sent
 *
 * @param controller_ID : Controller ID
 * @param ep_num        : Endpoint number
 * @param direction     : Endpoint direction
 *
 * @return status
 *         USBERR_NOT_SUPPORTED : Always
 ******************************************************************************
 * This function just returns Error Code not supported
 *****************************************************************************/
uint_8 USB_DCI_Cancel_Transfer (
//     uint_8    controller_ID,   /* [IN] Controller ID */
    _usb_device_handle    handle,             /* [IN] USB Device handle */
    uint_8    ep_num,          /* [IN] Endpoint number */
    uint_8    direction        /* [IN] Endpoint direction */
)
{
	printf_info("%s\n", __func__);
    return USBERR_NOT_SUPPORTED;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Deinit_EndPoint
 *
 * @brief The function de initializes an endpoint
 *
 * @param controller_ID : Controller ID
 * @param ep_num        : Endpoint number
 * @param direction     : Endpoint direction
 *
 * @return status
 *         USB_OK                   : When successfull
 *         USBERR_EP_DEINIT_FAILED  : When unsuccessfull
 ******************************************************************************
 *
 * This function un-intializes the endpoint by clearing the corresponding
 * endpoint control register and then clearing the QH.
 *
 *****************************************************************************/
uint_8 USB_DCI_Deinit_EndPoint (
    uint_8    controller_ID,   /* [IN] Controller ID */
    uint_8    ep_num,          /* [IN] Endpoint number */
    uint_8    direction        /* [IN] Endpoint direction */
)
{
	printf_info("%s\n", __func__);
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Stall_EndPoint
 *
 * @brief The function stalls an endpoint
 *
 * @param controller_ID : Controller ID
 * @param ep_num        : Endpoint number
 * @param direction     : Endpoint direction
 *
 * @return None
 *
 ******************************************************************************
 * This function stalls the endpoint by setting Endpoint QH
 *****************************************************************************/
void USB_DCI_Stall_EndPoint (
//     uint_8    controller_ID,   /* [IN] Controller ID */
    _usb_device_handle    handle,             /* [IN] USB Device handle */
    uint_8    ep_num,          /* [IN] Endpoint number */
    uint_8    direction        /* [IN] Endpoint direction */
)
{
    uint_8 controller_ID = *(uint_8 *)handle;
	printf_info("%s, ep_num is %d, dir is %d\n", __func__, ep_num, direction);
	
	// check if it is control endpoint
	if(ep_num == 0){
		// stall both directions
#if CHIP_MX6DQ || CHIP_MX6SDL
		HW_USBC_UOG_ENDPTCTRL0_SET(BM_USBC_(ENDPTCTRL0_TXS)|BM_USBC_(ENDPTCTRL0_RXS));
#elif CHIP_MX6SL
		HW_USBC_UOG1_ENDPTCTRL0_SET(BM_USBC_(ENDPTCTRL0_TXS)|BM_USBC_(ENDPTCTRL0_RXS));
#endif
		
	}else{
		
// 		USBHS_EPCR(endpoint_number-1) |= direction?USBHS_EPCR0_TXS_MASK:USBHS_EPCR0_RXS_MASK;

		writel(readl(&usbotg[controller_ID]->endptctrl[ep_num]) | (direction?BM_USBC_(ENDPTCTRL0_TXS):BM_USBC_(ENDPTCTRL0_RXS)), &usbotg[controller_ID]->endptctrl[ep_num]);
	}
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Unstall_EndPoint
 *
 * @brief The function unstalls an endpoint
 *
 * @param controller_ID : Controller ID
 * @param ep_num        : Endpoint number
 * @param direction     : Endpoint direction
 *
 * @return None
 *
 ******************************************************************************
 * This function unstalls the endpoint by clearing Endpoint Control Register
 * and QH
 *****************************************************************************/
void USB_DCI_Unstall_EndPoint (
//     uint_8    controller_ID,   /* [IN] Controller ID */
    _usb_device_handle     handle,             /* [IN] USB Device handle */
    uint_8    ep_num,          /* [IN] Endpoint number */
    uint_8    direction        /* [IN] Endpoint direction */
)
{
    uint_8 controller_ID = *(uint_8 *)handle;
	printf_info("%s\n", __func__);
	// todo:
	// This function unstalls the endpoint by clearing Endpoint Control Register
	// and QH
	if(ep_num == 0){
			// unstall both directions
#if CHIP_MX6DQ || CHIP_MX6SDL
			HW_USBC_UOG_ENDPTCTRL0_CLR(BM_USBC_(ENDPTCTRL0_TXS)|BM_USBC_(ENDPTCTRL0_RXS));
#elif CHIP_MX6SL
			HW_USBC_UOG1_ENDPTCTRL0_CLR(BM_USBC_(ENDPTCTRL0_TXS)|BM_USBC_(ENDPTCTRL0_RXS));
#endif
		}else{
// 			USBHS_EPCR(endpoint_number-1) &= ~(direction?USBHS_EPCR_TXS_MASK:USBHS_EPCR_RXS_MASK);
            writel(readl(&usbotg[controller_ID]->endptctrl[ep_num]) &  ~(direction?BM_USBC_(ENDPTCTRL0_TXS):BM_USBC_(ENDPTCTRL0_RXS)), &usbotg[controller_ID]->endptctrl[ep_num]);
		}
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Get_Setup_Data
 *
 * @brief The function copies Setup Packet from USB RAM to application buffer
 *
 * @param controller_ID : Controller ID
 * @param ep_num        : Endpoint number
 * @param buff_ptr      : Application buffer pointer
 *
 * @return None
 *
 ******************************************************************************
 * Copies setup packet from USB RAM to Application Buffer
 *****************************************************************************/
void USB_DCI_Get_Setup_Data (
//     uint_8      controller_ID,  /* [IN] Controller ID */
    _usb_device_handle    handle,             /* [IN] USB Device handle */
    uint_8      ep_num,         /* [IN] Endpoint number */
    uint_8_ptr  buff_ptr        /* [IN] Application buffer pointer */
)
{
	printf_info("%s\n", __func__);
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Get_Transfer_Status
 *
 * @brief The function retrieves the Transfer status of an endpoint
 *
 * @param controller_ID : Controller ID
 * @param ep_num        : Endpoint number
 * @param direction     : Endpoint direction
 *
 * @return status
 *         USBERR_TR_FAILED                : When unsuccessfull
 *         USB_STATUS_IDLE                 : No transfer on endpoint
 *         USB_STATUS_DISABLED             : endpoint is disabled
 *         USB_STATUS_STALLED              : endpoint is stalled
 *         USB_STATUS_TRANSFER_IN_PROGRESS : When SIE has control of BDT
 ******************************************************************************
 *
 * This function retrieves the transfer status of the endpoint by checking the
 * QH as well as the endpoint control register
 *
 *****************************************************************************/
uint_8 USB_DCI_Get_Transfer_Status (
//     uint_8    controller_ID,   /* [IN] Controller ID */
    _usb_device_handle    handle,             /* [IN] USB Device handle */
    uint_8    ep_num,          /* [IN] Endpoint number */
    uint_8    direction        /* [IN] Endpoint direction */
)
{
	printf_info("%s, ep_num is %d\n", __func__, ep_num);
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Recv_Data
 *
 * @brief The function retrieves data recieved on an RECV endpoint
 *
 * @param controller_ID : Controller ID
 * @param ep_num        : Endpoint number
 * @param buff_ptr      : Application buffer pointer
 * @param size          : Size of the buffer
 *
 * @return status
 *         USB_OK                          : When successfull
 *         USBERR_RX_FAILED                : When unsuccessfull
 ******************************************************************************
 * This function retrieves data received data on a RECV endpoint by copying it
 * from USB RAM to application buffer
 *****************************************************************************/
uint_8 USB_DCI_Recv_Data (
//     uint_8          controller_ID,  /* [IN] Controller ID */
    _usb_device_handle    handle,             /* [IN] USB Device handle */
    uint_8          ep_num,         /* [IN] Endpoint number */
    uchar_ptr       buff_ptr,       /* [OUT] Application buffer pointer */
//     USB_PACKET_SIZE size            /* [IN] Size of the buffer */
		uint_32                 size
)
{
    uint_8 controller_ID = *(uint_8 *)handle;
    usb_status_t status;
//    printf_info("%s, ep_num is %d\n", __func__, ep_num);

    if (ep_num != 0) {
    	status = usbd_receive_data_epxout(controller_ID, (unsigned int)buff_ptr, ep_num, size);
	}
    else
    	status = usbd_receive_data_ep0out(controller_ID, (unsigned int)buff_ptr, size);

    if (status != USB_SUCCESS)
    {
        return USBERR_RX_FAILED;
    }
    else
    {
        return USB_OK;
    }
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Send_Data
 *
 * @brief The function configures Controller to send data on an SEND endpoint
 *
 * @param controller_ID : Controller ID
 * @param ep_num        : Endpoint number
 * @param buff_ptr      : Application buffer pointer
 * @param size          : Size of the buffer
 *
 * @return status
 *         USB_OK           : When successfull
 *         USBERR_TX_FAILED : When unsuccessfull
 ******************************************************************************
 * This function configures Controller to send data on an SEND endpoint by
 * setting the QH to send data.
 *****************************************************************************/
uint_8 USB_DCI_Send_Data (
//     uint_8          controller_ID,  /* [IN] Controller ID */
    _usb_device_handle    handle,             /* [IN] USB Device handle */
    uint_8          ep_num,         /* [IN] Endpoint number */
    uchar_ptr       buff_ptr,       /* [IN] Application buffer pointer */
//     USB_PACKET_SIZE size            /* [IN] Size of the buffer */
		uint_32                 size
)
{
    usb_status_t status;
    uint_8 controller_ID = *(uint_8 *)handle;
 //   printf_info("%s, ep_num is %d\n", __func__, ep_num);

	if (ep_num != 0) {
    	status = usbd_send_data_epxin(controller_ID, (unsigned int)buff_ptr, ep_num, size);
	}

    /* Send descriptor - Data Phase */
    //zlt is false=>not zero length packet, send dev descriptor to host.
    else
    	status = usbd_send_data_ep0in(controller_ID, (unsigned int)buff_ptr, size, 0);

    if (status != USB_SUCCESS)
        return USBERR_TX_FAILED;

    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Set_Address
 *
 * @brief The function configures Controller to send data on an SEND endpoint
 *
 * @param controller_ID : Controller ID
 * @param address       : Controller Address
 *
 * @return None
 *
 ******************************************************************************
 * Assigns the Address to the Controller
 *****************************************************************************/
void  USB_DCI_Set_Address (
//     uint_8    controller_ID,    /* [IN] Controller ID */
    _usb_device_handle    handle,    /* [IN] USB Device handle */
    uint_8    address           /* [IN] Controller Address */
)
{
    uint_8 controller_ID = *(uint_8 *)handle;

    /* set the address */
//    printf_info("%s, address is %d\n", __func__, address);
    writel(BF_USBC_(DEVICEADDR_USBADR, address), &usbotg[controller_ID]->deviceaddr);

//     USB_Device_Set_Status(g_dci_controller_Id[controller_ID], USB_STATUS_DEVICE_STATE,
//         USB_STATE_ADDRESS);
    _usb_device_set_status(&g_dci_controller_Id[controller_ID], USB_STATUS_DEVICE_STATE,
        USB_STATE_ADDRESS);
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Shutdown
 *
 * @brief The function shuts down the controller
 *
 * @param controller_ID : Controller ID
 *
 * @return None
 *
 ******************************************************************************
 * Resets USB Device Controller
 *****************************************************************************/
void USB_DCI_Shutdown (
//     uint_8    controller_ID     /* [IN] Controller ID */
    _usb_device_handle    handle    /* [IN] USB Device handle */
)
{
	printf_info("%s\n", __func__);
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Assert_Resume
 *
 * @brief The function makes the Controller start USB RESUME signaling
 *
 * @param controller_ID: Controller ID
 *
 * @return None
 *
 ******************************************************************************
 *
 * This function starts RESUME signalling and then stops it after some delay.
 *
 *****************************************************************************/
void USB_DCI_Assert_Resume (
//     uint_8    controller_ID     /* [IN] Controller ID */
    _usb_device_handle    handle    /* [IN] USB Device handle */
)
{
	printf_info("%s\n", __func__);
}

/**************************************************************************//*!
 *
 * @name  Clear_Mem
 *
 * @brief The function clears memory starting from start_addr till count bytes
 *
 * @param start_addr : Buffer Start address
 * @param count      : Count of Bytes
 * @param val        : Value to be set
 *
 * @return None
 ******************************************************************************
 * This function is an implementation of memset
 *****************************************************************************/
void Clear_Mem (
    uint_8_ptr start_addr,  /* [OUT] Buffer Start address */
    uint_32 count,          /* [IN] Count of Bytes */
    uint_8 val              /* [IN] Value to be set */
)
{
    (void)memset(start_addr, val, count);
    return;
}


/*****************************************************************************
 * Local Functions
 *****************************************************************************/

static inline unsigned int readl(volatile unsigned int * addr)
{
    return *addr;
}

// Write register
static inline void writel(unsigned int val, volatile unsigned int *addr)
{
//	readl(addr);
//     __SWP((unsigned long)val, (unsigned long *)addr);
    *addr = val;
}

//Let the controller run
static usb_status_t usbd_usb_run(uint_8 controller_ID)
{
	unsigned reg, int_enable;

    printf_info("%s %d\n", __FUNCTION__, controller_ID);
    if(controller_ID == 0){
        // Register interrupt handler
#if CHIP_MX6DQ || CHIP_MX6SDL
        uint32_t irqId = IMX_INT_USBOH3_UOTG;
#elif CHIP_MX6SL
        uint32_t irqId = IMX_INT_USB_OTG1;
#endif

        register_interrupt_routine(irqId, usb0_isr);
        enable_interrupt(irqId, CPU_0, 0);
    }else{
        printf("Wrong USB controller ID! (%d)\n", controller_ID);
        return USBERR_INIT_FAILED;
    }

    // Enable usb deivce interrupts
    int_enable = BM_USBC_(USBINTR_UE) |        // USB interrupt
        BM_USBC_(USBINTR_UEE) |                // USB error
        BM_USBC_(USBINTR_PCE) |                // Port chanage
        BM_USBC_(USBINTR_URE) |                // Reset enable
        // SOF not currently used
        BM_USBC_(USBINTR_SRE) |                 // SOF received
        BM_USBC_(USBINTR_SLE) |                // suspend received
        BM_USBC_(USBINTR_SEE);                 // System error
    writel(int_enable, &usbotg[controller_ID]->usbintr);

    // USB start to run
    reg = readl(&usbotg[controller_ID]->usbcmd);
    reg |= (0x1 << 0);
    writel(reg, &usbotg[controller_ID]->usbcmd);

    return USB_OK;
}

/*!
 * MX6 USB device HW initialization
 */
static usb_status_t usbd_mx6_dev_init(uint_8 controller_ID)
{
    usb_status_t status;

    usb_clk_init(controller_ID);
    usb_phy_init(controller_ID);

    status = usb_set_device_mode(controller_ID);

    if (status == USB_OK)
    {
        printf_info("usb%d device mode initialized.\n", controller_ID);
    }
    else
    {
        printf_error("error: could not set usb%d device mode\n", controller_ID);
    }

    return status;
}

/*!
 * Clock init for USB
 */
static void usb_clk_init(uint_8 controller_ID)
{
//     *(unsigned int *)DIGCTRL_CTRL_CLR |= (0x1 << 2);
// 
//     if (controller_ID == 0) {
//         *(unsigned int *)HW_CLKCTRL_PLL0CTRL0_SET |= (0x1 << 18);
//         *(unsigned int *)HW_CLKCTRL_PLL0CTRL0_SET |= (0x1 << 17);
//     } else {
//         *(unsigned int *)HW_CLKCTRL_PLL1CTRL0_SET |= (0x1 << 18);
//         *(unsigned int *)HW_CLKCTRL_PLL1CTRL0_SET |= (0x1 << 17);
//     }
// 		        		
//     *(unsigned int *)HW_POWER_5VCTRL_SET |= (0x1 << 1);
    
//     usb_module_t usbModule = {
//             .moduleName = "OTG",
//             .controllerID = OTG,
//             .phyType = Utmi
//         };
// 
//     usbEnableClocks(&usbModule);
//     usbEnableTransceiver(&usbModule);

    /*!
     * Enable the USB clock for the controller
     */

    HW_CCM_CCGR6.B.CG0 = 3;

    /*!
     * Enable the PLL\n
     * OTG, Host2 and Host3 controllers use USB_PLL0
     * Host1 controller uses USB_PLL1
     */

    HW_CCM_ANALOG_PLL_USB1_SET(BM_CCM_ANALOG_PLL_USB1_POWER);	//! - Turn PLL power on.
    HW_CCM_ANALOG_PLL_USB1_SET(BM_CCM_ANALOG_PLL_USB1_EN_USB_CLKS); //!Powers the 9-phase PLL outputs for USBPHY0
    while(!(HW_CCM_ANALOG_PLL_USB1_RD() & BM_CCM_ANALOG_PLL_USB1_LOCK));//! - Wait for PLL to lock
    HW_CCM_ANALOG_PLL_USB1_CLR(BM_CCM_ANALOG_PLL_USB1_BYPASS);	//! - Clear bypass
    HW_CCM_ANALOG_PLL_USB1_SET(BM_CCM_ANALOG_PLL_USB1_ENABLE); 	//! - Enable PLL clock output for the PHY
}

/*!
 * Initialize the USB PHY
 */
static void usb_phy_init(uint_8 controller_ID)
{
//     HW_USBPHY_CTRL(controller_ID).B.SFTRST = 0;
//     HW_USBPHY_CTRL(controller_ID).B.CLKGATE = 0;
// 
//     HW_USBPHY_PWD(controller_ID).B.TXPWDFS = 0;
//     HW_USBPHY_PWD(controller_ID).B.TXPWDIBIAS = 0;
//     HW_USBPHY_PWD(controller_ID).B.TXPWDV2I = 0;
//     HW_USBPHY_PWD(controller_ID).B.RXPWDENV = 0;
//     HW_USBPHY_PWD(controller_ID).B.RXPWD1PT1 = 0;
//     HW_USBPHY_PWD(controller_ID).B.RXPWDDIFF = 0;
//     HW_USBPHY_PWD(controller_ID).B.RXPWDRX = 0;
// 
//     HW_USBPHY_CTRL(controller_ID).B.ENUTMILEVEL2 = 1;   //enable low speed
//     HW_USBPHY_CTRL(controller_ID).B.ENUTMILEVEL3 = 1;   //enable low speed on full speed
//     HW_USBPHY_CTRL(controller_ID).B.FSDLL_RST_EN = 1;   //enable added logic for full speed dll reset


    //! NOTE !! CLKGATE must be cleared before clearing power down
    HW_USBPHY_CTRL_CLR(HW_USBPHY1, BM_USBPHY_CTRL_SFTRST);	//! - clear SFTRST
    HW_USBPHY_CTRL_CLR(HW_USBPHY1, BM_USBPHY_CTRL_CLKGATE);	//! - clear CLKGATE
    HW_USBPHY_PWD_WR(HW_USBPHY1, 0);	//! - clear all power down bits
    HW_USBPHY_CTRL_SET(HW_USBPHY1, BM_USBPHY_CTRL_ENUTMILEVEL2 | BM_USBPHY_CTRL_ENUTMILEVEL3 | BM_USBPHY_CTRL_ENHOSTDISCONDETECT);    

    //! disable the charger detector. This must be off during normal operation
    {
        // this register is not documented. Will be updated in the next release
        uint32_t *ChargerDetectControl;
        ChargerDetectControl = (uint32_t *) 0x020c81b0;
        *ChargerDetectControl |= 1 << 20;   // disable detector
    }

    //! Check if all power down bits are clear
//     if (HW_USBPHY_PWD_RD(instance) != 0)
//         return -1;              // Phy still in power-down mode. Check if all clocks are running.
//     else
//         return 0;
}

/*!
 * Set the OTG to device mode
 *
 * @return    On success returns 0, otherwise 1
 */
static usb_status_t usb_set_device_mode(uint_8 controller_ID)
{
    unsigned int count = 10000;
    unsigned int reg;
//     unsigned char *qh_buf = controller_ID ? g_usbd1_qh_buf : g_usbd0_qh_buf;
    unsigned char *qh_buf = g_usbd_qh_bufs[controller_ID];

    printf_info("set usb%d as device\n", controller_ID);

    /*reset usb controller */
    reg = readl(&usbotg[controller_ID]->usbcmd);
    reg |= (0x1 << 1);
    writel(reg, &usbotg[controller_ID]->usbcmd);
    while (readl(&usbotg[controller_ID]->usbcmd) & (0x1 << 1)) ;   //check if reset done, port is enabled

    //enable USB work in device mode
    reg = readl(&usbotg[controller_ID]->usbmode);
    reg &= ~0x3;
    reg |= 2; //BV_USBC_UOG_USBMODE_CM__DEVICE;
    // Disable Setup Lockout by writing '1' to SLOM in USBMODE
    reg |= (0x1 << 3);
    reg &= ~(0x1 << 4);  //disable stream mode
    // note this register can only be written once after reset
    writel(reg, &usbotg[controller_ID]->usbmode);

    //todo change to processor speed independent wait
    while (((readl(&usbotg[controller_ID]->usbmode) & 0x3) != 2 /*BV_USBC_UOG_USBMODE_CM__DEVICE*/) && (--count)) ;

    if (count == 0)
        return USBERR_INIT_FAILED;               //timeout

#if FORCE_FULLSPEED
	reg = readl(&usbotg[controller_ID]->portsc1);
    reg |= BM_USBC_(PORTSC1_PFSC);
	writel(reg, &usbotg[controller_ID]->portsc1); /* force full speed */
#endif

    // Configure ENDPOINTLISTADDR Pointer
    writel((unsigned int)qh_buf & 0xfffff800, &usbotg[controller_ID]->endpointlistaddr);

    // Set OTG termination, controls the pulldown on DM
    reg = readl(&usbotg[controller_ID]->otgsc);
    reg |= (0x1 << 3);
    writel(reg, &usbotg[controller_ID]->otgsc);

    // clear the usb intr status
    writel(0xffffffff, &usbotg[controller_ID]->usbsts);

    // USB0 start to run
    reg = readl(&usbotg[controller_ID]->usbcmd);
    reg |= (0x1 << 0);
    writel(reg, &usbotg[controller_ID]->usbcmd);

    return USB_OK;
}

static void usbd_ep_setup(uint_8 controller_ID, unsigned char endpt_number, unsigned char direction, unsigned char ep_type)
{
	unsigned int temp = 0;

//	temp = readl(usbotg->endptctrl[endpt_number]);
//	printf("endpctrl is ep[%d]=0x%x, tempj is 0x%x\n", endpt_number, readl(&usbotg->endptctrl[endpt_number]), temp);
	
	if (direction) {
		if (endpt_number)
			temp |= BM_USBC_(ENDPTCTRL1_TXR);
		temp |= BM_USBC_(ENDPTCTRL1_TXE);
		temp |= ((unsigned int)(ep_type)
				<< BP_USBC_(ENDPTCTRL1_TXT));
	} else {
		if (endpt_number)
			temp |= BM_USBC_(ENDPTCTRL1_RXR);
		temp |= BM_USBC_(ENDPTCTRL1_RXE);
		temp |= ((unsigned int)(ep_type)
				<< BP_USBC_(ENDPTCTRL1_RXT));
	}
	
	writel(temp, &usbotg[controller_ID]->endptctrl[endpt_number]);
	printf_info("endpctrl is ep[%d]=0x%x, temp is 0x%x\n", endpt_number, readl(&usbotg[controller_ID]->endptctrl[endpt_number]), temp);
}

static void usbd_ep0_init(uint_8 controller_ID)
{
	usbd_ep_qh_init(controller_ID, EP0, IN, 64, 0, 0);
	usbd_ep_qh_init(controller_ID, EP0, OUT, 64, 0, 0);
		
	usbd_ep_setup(controller_ID, 0, USB_RECV, EP_TRANSFER_TYPE_CONTROL);
	usbd_ep_setup(controller_ID, 0, USB_SEND, EP_TRANSFER_TYPE_CONTROL);
	
	return;
}

/*!
 * Initialize the USB device endpoint queue head structure
 */
static void usbd_ep_qh_init(uint_8 controller_ID,
                            unsigned char endpt_number, unsigned char direction,
		unsigned int max_pkt_len,
		unsigned int zlt, unsigned char mult)
{
    struct dqh_t qhead;
    unsigned int total_bytes;

    // Initialize device queue head in system memory

    total_bytes = 0x8;  // 8 bytes for the 1st setup packet
    qhead.dqh_base = usbd_get_dqh(controller_ID, endpt_number, direction);
    qhead.zlt = zlt;
    qhead.mps = max_pkt_len;
    qhead.ios = IOS_SET;
    qhead.terminate = NOT_TERMINATE;
    qhead.total_bytes = total_bytes;
    qhead.ioc = IOC_SET;
    qhead.status = NO_STATUS;
	qhead.mult = mult;
    qhead.buffer_ptr0 = 0;
    qhead.current_offset = 0;
    qhead.buffer_ptr1 = 0;
    qhead.buffer_ptr2 = 0;
    qhead.buffer_ptr3 = 0;
    qhead.buffer_ptr4 = 0;

    /* Set Device Queue Head */
    usbd_setup_qhead(&qhead);
    
    // Initialize the TD queue info
    int td_index = (endpt_number * 2) + direction;
    g_usbd_queue_info[controller_ID][td_index].enq_idx = 0;
    g_usbd_queue_info[controller_ID][td_index].deq_idx = 0;
    g_usbd_queue_info[controller_ID][td_index].tail = NULL;

    // Initialize TD flags
    for (int i = 0; i < MAX_DTDS_PER_EP; i++)
    {
        g_usbd_td_flag[controller_ID][td_index][i].status = DTD_FREE;
        g_usbd_td_flag[controller_ID][td_index][i].total_bytes = 0;
        g_usbd_td_flag[controller_ID][td_index][i].phys_td = NULL;
   }
}

/*!
 * Setup the queue head for the USB device
 *
 * @param    qhead    The queue head data sturcture that contains the necessary configuration data
 */
static void usbd_setup_qhead(struct dqh_t *qhead)
{
    volatile struct dqh_setup_t *dqh_word = (volatile struct dqh_setup_t *)qhead->dqh_base;

    /*======
    0x0
    ======
    Bit31:30 Mult; Bit29 zlt; Bit26:16 mps; Bit15 ios */
    dqh_word->dqh_word0 =
        (((unsigned int)((qhead->zlt) << 29)) | ((unsigned int)((qhead->mps) << 16)) | (((unsigned int)
                                           (qhead->ios) <<15)) | (unsigned int)((qhead->mult) << 30));
    /*======
    0x4
    ======
    Current dTD Pointer => for hw use, not modified by DCD software */
    dqh_word->dqh_word1 = 0x0;

    /*======
    0x8
    ======
    Next dTD Pointer */
    dqh_word->dqh_word2 = (((qhead->next_link_ptr) & 0xFFFFFFE0) | qhead->terminate);

    /*======
    0xC
    ======
    Bit30:16 total_bytes; Bit15 ioc; Bit11:10 MultO; Bit7:0 status */
    dqh_word->dqh_word3 =
        ((((unsigned int)(qhead->total_bytes) & 0x7FFF) << 16) | ((unsigned int)(qhead->ioc) << 15)
         | (qhead->status));

    /*======
    0x10
    ======
    Bit31:12 Buffer Pointer (Page 0) */
    dqh_word->dqh_word4 = ((qhead->buffer_ptr0 & 0xFFFFF000) | (qhead->current_offset & 0xFFF));

    /*======
    0x14
    ======
    Bit31:12 Buffer Pointer (Page 1) */
    dqh_word->dqh_word5 = (qhead->buffer_ptr1 & 0xFFFFF000);

    /*======
    0x18
    ======
    Bit31:12 Buffer Pointer (Page 2) */
    dqh_word->dqh_word6 = (qhead->buffer_ptr2 & 0xFFFFF000);

    /*======
    0x1C
    ======
    Bit31:12 Buffer Pointer (Page 3) */
    dqh_word->dqh_word7 = (qhead->buffer_ptr3 & 0xFFFFF000);

    /*======
    0x20
    ======
    Bit31:12 Buffer Pointer (Page 4) */
    dqh_word->dqh_word8 = (qhead->buffer_ptr4 & 0xFFFFF000);

    /*======
    0x24
    ======
    Reserved */
    dqh_word->dqh_word9 = 0;

    /*======
    0x28
    ======
    Setup Buffer 0 */
    dqh_word->dqh_word10 = 0;

    /*======
    0x2C
    ======
    Setup Buffer 1 */
    dqh_word->dqh_word11 = 0;
}

/*!
 * Setup the transfer descriptor
 *
 * @param    td    The TD data sturcture that contains the necessary configuration data
 */
static void usbd_setup_td(struct dtd_t *td)
{
    volatile struct dtd_setup_t *dtd_word = (volatile struct dtd_setup_t *)td->dtd_base;

    /* Bit31:5 Next Link Pointer ; Bit0 terminate */
    dtd_word->dtd_word0 = ((td->next_link_ptr & 0xFFFFFFE0) | td->terminate);

    /* Bit30:16 total_bytes, Bit15 ioc, Bit7:0 status */
    dtd_word->dtd_word1 = ((unsigned int)td->total_bytes & 0x7FFF) << 16;
    dtd_word->dtd_word1 |= ((unsigned int)td->ioc << 15) | (td->status);

    /* Bit31:12 Buffer Pointer Page 0 ; Bit11:0 Current Offset */
    dtd_word->dtd_word2 = ((td->buffer_ptr0 & 0xFFFFF000) | (td->current_offset & 0xFFF));

    /* Bit31:12 Buffer Pointer Page 1 ; Bit10:0 Frame Number */
    dtd_word->dtd_word3 = (td->buffer_ptr1 & 0xFFFFF000);

    /* Bit31:12 Buffer Pointer Page 2 ; */
    dtd_word->dtd_word4 = (td->buffer_ptr2 & 0xFFFFF000);

    /* Bit31:12 Buffer Pointer Page 3 ; */
    dtd_word->dtd_word5 = (td->buffer_ptr3 & 0xFFFFF000);

    /* Bit31:12 Buffer Pointer Page 4 ; */
    dtd_word->dtd_word6 = (td->buffer_ptr4 & 0xFFFFF000);

    /* Store app buffer address */
    dtd_word->dtd_word7 = td->buffer_ptr0;

}
/*!
 * Get the offset of DQH from the QH buffer base
 *
 * @param    endpt_number    The end point number, start from 0
 * @param    direction       The In or Out endpoint
 *
 * @return   The relative offset of DQH
 * @return   0 if can't find a free DTD
 */
static unsigned int usbd_get_dqh(uint_8 controller_ID, unsigned char endpt_number, unsigned char direction)
{
//     unsigned char *qh_buf = controller_ID ? g_usbd1_qh_buf : g_usbd0_qh_buf;
    unsigned char *qh_buf = g_usbd_qh_bufs[controller_ID];

    /* direction OUT = 0 and IN = 1 */
    return (unsigned int)(qh_buf + (SIZE_OF_QHD * (endpt_number * 2 + direction)));
}

/*!
 * Get the offset of DTD from the TD buffer base
 *
 * @param    endpt_number    The end point number, start from 0
 * @param    direction       The In or Out endpoint
 *
 * @return   The relative offset of DTD
 */
static unsigned int usbd_get_dtd(uint_8 controller_ID, unsigned char endpt_number, unsigned char direction, unsigned int sz)
{
//     unsigned char *td_buf = controller_ID ? g_usbd1_td_buf : g_usbd0_td_buf;
    unsigned char *td_buf = g_usbd_td_bufs[controller_ID];
    int td_index = (endpt_number * 2) + direction;
    uint_8 *enq_idx = &g_usbd_queue_info[controller_ID][td_index].enq_idx;
    unsigned int phys_td;
    
    // Check if we are out of free TDs
    if (g_usbd_td_flag[controller_ID][td_index][*enq_idx].status == DTD_BUSY)
    {
        printf_error("Cannot get dTD!\n");
        return 0;
    }

    //printf("id%d ep%d direction%d alloc = %d\n", controller_ID, endpt_number, direction, *enq_idx);
    
    // We have found an available TD. Mark it as busy
    g_usbd_td_flag[controller_ID][td_index][*enq_idx].status = DTD_BUSY;
    g_usbd_td_flag[controller_ID][td_index][*enq_idx].phys_td = (volatile struct dtd_setup_t *)
        ((unsigned int) td_buf +
        (SIZE_OF_DTD0) *(td_index) * MAX_DTDS_PER_EP +
        (*enq_idx) * (SIZE_OF_DTD0));
    g_usbd_td_flag[controller_ID][td_index][*enq_idx].total_bytes = sz;
    phys_td = (unsigned int)g_usbd_td_flag[controller_ID][td_index][*enq_idx].phys_td;
    
    // Increment the enqueue TD index with wrapping
    if (++(*enq_idx) >= MAX_DTDS_PER_EP)
    {
        *enq_idx = 0;
    }

    return phys_td;
}

uint_32 sof_counter[MAX_USB_STACKS] = {0, 0};
#if !FORCE_FULLSPEED
static uint_32 temp_sof0_counter = 0;
#endif
/**************************************************************************//*!
 *
 * @name  USB_ISR
 *
 * @brief The function handles USB interrupts on the bus.
 *
 * @param None
 *
 * @return None
 *
 ******************************************************************************
 * This function handles the USB interrupts.
 * After handling the interrupt it calls the Device Layer to notify it about
 * the event.
 *****************************************************************************/
static void usb0_isr(void)// *data)
{
    uint_32 intr_stat;
    USB_DEV_EVENT_STRUCT event;

    intr_stat = readl(&usbotg[0]->usbsts);
    // Only process the interrupts that are enabled
    intr_stat &= readl(&usbotg[0]->usbintr);
    
//     printf("usb0_isr %x\n", intr_stat);

    /* initialize event structure */
    event.controller_ID = g_dci_controller_Id[0];
    event.setup = FALSE;
    event.buffer_ptr = NULL;
    event.len = 0;
    event.direction = USB_RECV;
    event.errors = NO_ERRORS;
    event.ep_num = (uint_8)UNINITIALISED_VAL;

    // Handle SOF interrupt
	if (intr_stat & BM_USBC_(USBSTS_SRI))
	{
        /* Clear Interrupt */
        writel(BM_USBC_(USBSTS_SRI), &usbotg[0]->usbsts);
#if FORCE_FULLSPEED
		sof_counter[0]++;
#else
		if (++temp_sof0_counter == 8)
		{
			sof_counter[0]++;
			temp_sof0_counter = 0;
		}
#endif
    }

    // Handle suspend
    if (intr_stat & BM_USBC_(USBSTS_SLI))
	{
		printf_info("received suspend irq on device 0\n");
		writel(BM_USBC_(USBSTS_SLI), &usbotg[0]->usbsts);
		return;
	}

    // Handle bus reset
    if (intr_stat & BM_USBC_(USBSTS_URI))
    {
		printf_info("received bus reset irq on device 0\n");
        /* Clear Interrupt */
		writel(BM_USBC_(USBSTS_URI), &usbotg[0]->usbsts);

        /* Handle RESET Interrupt */
        USB_Bus_Reset_Handler(0);

        /* Notify Device Layer of RESET Event */
        (void)USB_Device_Call_Service(USB_SERVICE_BUS_RESET, &event);

        // No need to handle other interrupts
        return;
    }

    // Handle Transaction complete
    if (intr_stat & BM_USBC_(USBSTS_UI))
    {
        /* Clear Interrupt */
		writel(BM_USBC_(USBSTS_UI), &usbotg[0]->usbsts);

        // todo This does happen, what else triggers this interrupt?
//        if (!(readl(&usbotg->endptsetupstat) && !(readl(&usbotg->endptcomplete))))
//        {
//            printf("Warning: unexpected UI interrupt\n");
//        }

        // Handle dTD complete interrupt.
        // Must process EP complete events first, because setup complete events
        // trigger stack to re-prime endpoints.
        if (readl(&usbotg[0]->endptcomplete))
        {
			usbd_ep_complete_handler(&event);
        }
        // Handle setup compete packet interrupt
		if (readl(&usbotg[0]->endptsetupstat) & BF_USBC_(ENDPTSETUPSTAT_ENDPTSETUPSTAT, 1))
        {
        	usbd_setup_packet_handler(&event);
        }
    }

    // Handle port change interrupt
    if (intr_stat & BM_USBC_(USBSTS_PCI))
    {
		printf_info("received port change irq on device 0\n");
        /* Clear Interrupt */
		writel(BM_USBC_(USBSTS_PCI), &usbotg[0]->usbsts);
    }

    // Handle USB error
    if (intr_stat & BM_USBC_(USBSTS_UEI))
    {
		printf_info("received usb error irq on device 0\n");
        /* Clear Interrupt */
		writel(BM_USBC_(USBSTS_UEI), &usbotg[0]->usbsts);

        event.errors = (uint_8)BM_USBC_(USBSTS_UEI);

        /* Notify Device Layer of ERROR Event to error service */
       (void)USB_Device_Call_Service(USB_SERVICE_ERROR, &event);
    }

    // Handle System error (this bit will always 0 on mx28 controller)
    if (intr_stat & BM_USBC_(USBSTS_SEI))
    {
		printf_info("received usb system error irq on device 0\n");
        /* Clear Interrupt */
		writel(BM_USBC_(USBSTS_SEI), &usbotg[0]->usbsts);

        event.errors = (uint_8)BM_USBC_(USBSTS_SEI);

        /* Notify Device Layer of ERROR Event to error service */
       (void)USB_Device_Call_Service(USB_SERVICE_ERROR, &event);
    }
}

#if !FORCE_FULLSPEED
static uint_32 temp_sof1_counter = 0;
#endif
#if 0
/**************************************************************************//*!
 *
 * @name  USB_ISR
 *
 * @brief The function handles USB interrupts on the bus.
 *
 * @param None
 *
 * @return None
 *
 ******************************************************************************
 * This function handles the USB interrupts.
 * After handling the interrupt it calls the Device Layer to notify it about
 * the event.
 *****************************************************************************/
static void usb1_isr(void *data)
{
    uint_32 intr_stat;
    USB_DEV_EVENT_STRUCT event;

    intr_stat = readl(&usbotg[1]->usbsts);

    // Only process the interrupts that are enabled
    intr_stat &= readl(&usbotg[1]->usbintr);

    /* initialize event structure */
    event.controller_ID = g_dci_controller_Id[1];
    event.setup = FALSE;
    event.buffer_ptr = NULL;
    event.len = 0;
    event.direction = USB_RECV;
    event.errors = NO_ERRORS;
    event.ep_num = (uint_8)UNINITIALISED_VAL;

    // Handle SOF interrupt
	if (intr_stat & BM_USBC_(USBSTS_SRI))
	{
        /* Clear Interrupt */
        writel(BM_USBC_(USBSTS_SRI), &usbotg[1]->usbsts);
#if FORCE_FULLSPEED
		sof_counter[1]++;
#else
		if (++temp_sof1_counter == 8)
		{
			sof_counter[1]++;
			temp_sof1_counter = 0;
		}
#endif
    }
	
    // Handle suspend
    if (intr_stat & BM_USBC_(USBSTS_SLI))
	{
		printf_info("receive suspend irq on device 1\n");
		writel(BM_USBC_(USBSTS_SLI), &usbotg[1]->usbsts);
		return;
	}

    // Handle bus reset
    if (intr_stat & BM_USBC_(USBSTS_URI))
    {
        /* Clear Interrupt */
		writel(BM_USBC_(USBSTS_URI), &usbotg[1]->usbsts);

        /* Handle RESET Interrupt */
        USB_Bus_Reset_Handler(1);

        /* Notify Device Layer of RESET Event */
        (void)USB_Device_Call_Service(USB_SERVICE_BUS_RESET, &event);

        // No need to handle other interrupts
        return;
    }

    // Handle Transaction complete
    if (intr_stat & BM_USBC_(USBSTS_UI))
    {
        /* Clear Interrupt */
		writel(BM_USBC_(USBSTS_UI), &usbotg[1]->usbsts);

        // todo This does happen, what else triggers this interrupt?
//        if (!(readl(&usbotg[1]->endptsetupstat) && !(readl(&usbotg[1]->endptcomplete))))
//        {
//            printf("Warning: unexpected UI interrupt\n");
//        }

        // Handle dTD complete interrupt.
        // Must process EP complete events first, because setup complete events
        // trigger stack to re-prime endpoints.
        if (readl(&usbotg[1]->endptcomplete))
        {
			usbd_ep_complete_handler(&event);
        }
        // Handle setup compete packet interrupt
		if (readl(&usbotg[1]->endptsetupstat) & BF_USBC_(ENDPTSETUPSTAT_ENDPTSETUPSTAT, 1))
        {
        	usbd_setup_packet_handler(&event);
        }
    }

    // Handle port change interrupt
    if (intr_stat & BM_USBC_(USBSTS_PCI))
    {
        /* Clear Interrupt */
		writel(BM_USBC_(USBSTS_PCI), &usbotg[1]->usbsts);
    }

    // Handle USB error
    if (intr_stat & BM_USBC_(USBSTS_UEI))
    {
        /* Clear Interrupt */
		writel(BM_USBC_(USBSTS_UEI), &usbotg[1]->usbsts);

        //todo how to get error num
        //event.errors = (uint_8)(USB0_ERRSTAT & USB0_ERREN);

        /* Notify Device Layer of ERROR Event to error service */
       (void)USB_Device_Call_Service(USB_SERVICE_ERROR, &event);
    }

    // Handle System error
    if (intr_stat & BM_USBC_(USBSTS_SEI))
    {
        /* Clear Interrupt */
		writel(BM_USBC_(USBSTS_SEI), &usbotg[1]->usbsts);

        //todo how to get error num
        //event.errors = (uint_8)(USB0_ERRSTAT & USB0_ERREN);

        /* Notify Device Layer of ERROR Event to error service */
       (void)USB_Device_Call_Service(USB_SERVICE_ERROR, &event);
    }
}
#endif // 0

/**************************************************************************//*!
 *
 * @name  USB_Bus_Reset_Handler
 *
 * @brief The function handles Bus Reset Interrupt
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************
 * This functions is called when USB Bus Reset event is received on USB Bus.
 * This function clears all the errors conditions and reinit Global data
 * structures. Also resets USB device controller.
 *****************************************************************************/
static void USB_Bus_Reset_Handler(uint_8 controller_ID)
{
    unsigned int temp;

    //printf_info("usb0 device get bus reset\n");

	//Clear the device address
	writel(~USBD_ADDR_MASK, &usbotg[controller_ID]->deviceaddr);

    /*1. Reading and writing back the ENDPTSETUPSTAT register
       clears the setup token semaphores */
    temp = readl(&usbotg[controller_ID]->endptsetupstat);
    writel(temp, &usbotg[controller_ID]->endptsetupstat);

    /*2. Reading and writing back the ENDPTCOMPLETE register
       clears the endpoint complete status bits */
    temp = readl(&usbotg[controller_ID]->endptcomplete);
    writel(temp, &usbotg[controller_ID]->endptcomplete);

	//Write 1s to the flush register
	writel(0xffffffff, &usbotg[controller_ID]->endptflush);
}

/**************************************************************************//*!
 *
 * @name  usbd_setup_packet_handler
 *
 * @brief The function handles Token Complete USB interrupts on the bus.
 *
 * @param event : Pointer to USB EVENT Structure
 *
 * @return None
 ******************************************************************************
 * This function handles Token Complete USB interrupts on the bus.
 *****************************************************************************/
static void usbd_setup_packet_handler(
    USB_DEV_EVENT_STRUCT* event /* [IN] Pointer to USB EVENT Structure */
)
{
    unsigned char setup_packet[8];
    unsigned int setup_complete;

    // Clear setup complete register
    setup_complete = readl(&usbotg[event->controller_ID]->endptsetupstat);
    writel(setup_complete, &usbotg[event->controller_ID]->endptsetupstat);

    // Read setup packet
    usbd_read_setup_packet(event->controller_ID, setup_packet);

    // Assume EP0
    event->ep_num = CONTROL_ENDPOINT;
    // Direction of setup complete is always Receive
    event->direction = USB_RECV;
    event->buffer_ptr = setup_packet;
    event->len = sizeof(setup_packet);
    event->setup = TRUE;

    /* Notify Device Layer of Data Recieved or Sent Event */
    (void)USB_Device_Call_Service(event->ep_num, event);
}

// Read in setup packet. Assumes EP0.
static void usbd_read_setup_packet(uint_8 controller_ID, unsigned char *setup_packet)
{
    dqh_setup_t *dqh_word;
    unsigned int dqh_address;
    unsigned int temp;
    unsigned int count = 10000;
    int i;
    usb_standard_device_request_t *setup_struct;

    /* Get the Device Queue Head Address for EP0 OUT   */
    dqh_address = usbd_get_dqh(controller_ID, EP0, OUT);
    dqh_word = (dqh_setup_t *) dqh_address;

    do {
        /* write '1' to Setup Tripwire (SUTW) in USBCMD register */
        temp = readl(&usbotg[controller_ID]->usbcmd);
        temp |= (0x1 << 13);
        writel(temp, &usbotg[controller_ID]->usbcmd);

        /* Copy the SetupBuffer into local software byte array */
        temp = (dqh_word->dqh_word10);

        /* This is due to the simulator bug for word variant access on EMI but actually design has word invariant access */
        for (i = 0; i < 4; i++) {
            setup_packet[i] = (unsigned int)((temp >> (8 * i)) & 0xFF);
        }
        temp = (dqh_word->dqh_word11);
        for (i = 0; i < 4; i++) {
            setup_packet[i + 4] = (unsigned int)((temp >> (8 * i)) & 0xFF);
        }

        //todo change to processor speed independent count
    } while (!(readl(&usbotg[controller_ID]->usbcmd) & BIT13) && (--count));

    if (!count)
    {
        printf_error("error getting setup buffer\n");
    }

    /* Write '0' to clear SUTW in USBCMD register */
    temp = readl(&usbotg[controller_ID]->usbcmd);
    temp &= ~(0x1 << 13);
    writel(temp, &usbotg[controller_ID]->usbcmd);
    setup_struct = (usb_standard_device_request_t *)setup_packet;
   	if (setup_struct->bRequest == SET_ADDRESS) {
		g_dci_address_state[controller_ID] = 1;
	}
	if (setup_struct->bRequest == SET_INTERFACE) {
		printf_info("it is set interface\n");
	}
//                printf_info("received setup packet\n");
}

/**************************************************************************//*!
 *
 * @name  usbd_dtd_handler
 *
 * @brief The function handles Token Complete USB interrupts on the bus.
 *
 * @param event : Pointer to USB EVENT Structure
 *
 * @return None
 ******************************************************************************
 * This function handles Token Complete USB interrupts on the bus.
 *****************************************************************************/
static void usbd_ep_complete_handler(
    USB_DEV_EVENT_STRUCT* event /* [IN] Pointer to USB EVENT Structure */
)
{
    int i;
    unsigned int ep_complete;

    // Get and clear endpoint complete register
    ep_complete = readl(&usbotg[event->controller_ID]->endptcomplete);
    writel(ep_complete, &usbotg[event->controller_ID]->endptcomplete);

    // Handle all ep bits set in ep complete register
    for (i = 0; i < 16; i++)
    {
        // Determine bit position in ep complete register
        // (skip over the reserved bits)
        unsigned int ep_bit = (i < 8) ? i : (i + 8);

        if (ep_complete & (1 << ep_bit))
        {
            if (ep_bit < 8)
            {
                // Endpoint Receive Complete Event
                event->direction = USB_RECV;
                event->ep_num = i;
            }
            else
            {
                // Endpoint Transmit Complete Event
                event->direction = USB_SEND;
                event->ep_num = ep_bit - 16;
            }

            if (event->ep_num == CONTROL_ENDPOINT)
            {
                // Control endpoint handling
                usbd_ep0_complete(event);
            }
            else
            {
                // Non-control endpoint handling
                usbd_dtd_complete(event);
            }
        }
    }
}

// Control endpoint complete handling
static void usbd_ep0_complete(USB_DEV_EVENT_STRUCT* event)
{
    volatile struct dtd_setup_t *dtd_word;
    unsigned int endpt_number = event->ep_num;
    unsigned int direction = event->direction;
    unsigned int td_index = (endpt_number * 2) + direction;
    uint_8 *deq_idx = &g_usbd_queue_info[event->controller_ID][td_index].deq_idx;
    
    // Complete all retired TDs. TDs are retired in the order they were enqueued, in other words
    // starting at the current dequeue index.
    while (1)
    {
        // Get dTD associated with this endpoint and direction
        dtd_word = g_usbd_td_flag[event->controller_ID][td_index][*deq_idx].phys_td;

        // Determine if dTD is busy (not free) and completed (not active)
        if ((g_usbd_td_flag[event->controller_ID][td_index][*deq_idx].status == DTD_BUSY) && ((dtd_word->dtd_word1 & 0x80) != 0x80))
        {
            //printf("id%d ep%d direction%d free = %d\n", event->controller_ID, endpt_number, direction, *deq_idx);
            
            // Get original number of bytes to transfer
            unsigned int total_bytes = g_usbd_td_flag[event->controller_ID][td_index][*deq_idx].total_bytes;
            // Subtract number of remaining bytes not transferred
            event->len = total_bytes - (dtd_word->dtd_word1 >> 16) & 0x7FFF;
            event->buffer_ptr = (uint_8 *)dtd_word->dtd_word7;

            // Mark dTD as free
            g_usbd_td_flag[event->controller_ID][td_index][*deq_idx].status = DTD_FREE;
			
            if (g_dci_address_state[event->controller_ID] == 1)
            {
                event->ep_num = CONTROL_ENDPOINT;
                event->buffer_ptr = 0;
                event->len = 0;
                g_dci_address_state[event->controller_ID] = 0;
            }
            
            // If this was the tail, mark list as empty
            if (dtd_word == g_usbd_queue_info[event->controller_ID][td_index].tail)
            {
                g_usbd_queue_info[event->controller_ID][td_index].tail = NULL;
            }
            
            // Increment the dequeue TD index with wrapping
            if (++(*deq_idx) >= MAX_DTDS_PER_EP)
            {
                *deq_idx = 0;
            }
			
            /* Notify Device Layer of Data Recieved or Sent Event */
            (void)USB_Device_Call_Service(event->ep_num, event);
        }
        else
        {
            // Since TDs will always be completed in order, once we have found a TD that is not completed we are done.
            break;
        }
    }
}

// Handle endpoint dTD complete
static void usbd_dtd_complete(USB_DEV_EVENT_STRUCT* event)
{
    volatile struct dtd_setup_t *dtd_word;
    unsigned int endpt_number = event->ep_num;
    unsigned int direction = event->direction;
    unsigned int td_index = (endpt_number * 2) + direction;
    uint_8 *deq_idx = &g_usbd_queue_info[event->controller_ID][td_index].deq_idx;
    
    // Complete all retired TDs. TDs are retired in the order they were enqueued, in other words
    // starting at the current dequeue index.
    while (1)
    {
        // Get dTD associated with this endpoint and direction
        dtd_word = g_usbd_td_flag[event->controller_ID][td_index][*deq_idx].phys_td;

        // Determine if dTD is busy (not free) and completed (not active)
        if ((g_usbd_td_flag[event->controller_ID][td_index][*deq_idx].status == DTD_BUSY) && ((dtd_word->dtd_word1 & 0x80) != 0x80))
        {
            //printf("id%d ep%d direction%d free = %d\n", event->controller_ID, endpt_number, direction, *deq_idx);
            
            // Get original number of bytes to transfer
            unsigned int total_bytes = g_usbd_td_flag[event->controller_ID][td_index][*deq_idx].total_bytes;
            // Subtract number of remaining bytes not transferred
            event->len = total_bytes - (dtd_word->dtd_word1 >> 16) & 0x7FFF;
            event->buffer_ptr = (uint_8 *)dtd_word->dtd_word7;

            // Mark dTD as free
            g_usbd_td_flag[event->controller_ID][td_index][*deq_idx].status = DTD_FREE;
			
            // If this was the tail, mark list as empty
            if (dtd_word == g_usbd_queue_info[event->controller_ID][td_index].tail)
            {
                g_usbd_queue_info[event->controller_ID][td_index].tail = NULL;
            }
            
            // Increment the dequeue TD index with wrapping
            if (++(*deq_idx) >= MAX_DTDS_PER_EP)
            {
                *deq_idx = 0;
            }
			
            /* Notify Device Layer of Data Recieved or Sent Event */
            (void)USB_Device_Call_Service(event->ep_num, event);
        }
        else
        {
            // Since TDs will always be completed in order, once we have found a TD that is not completed we are done.
            break;
        }
    }
}

// Prime endpoint
static void usbd_prime_ep(uint_8 controller_ID, unsigned char ep_num, unsigned char direction, struct dtd_t *td)
{
    unsigned int temp;
    unsigned int ep_mask = (direction == OUT ? EPOUT_PRIME : EPIN_PRIME);

    // Get Device Device Queue Head of the requested endpoint
    unsigned int dqh_address = usbd_get_dqh(controller_ID, ep_num, direction);

    /* Enable ZLT when data size is in multiple of Maximum Packet Size  */
    /* set ZLT enable */
    if (direction == IN)
    {
        (*(volatile unsigned int *)(dqh_address)) &= ~0x20000000;
    }

    /* 1. write dQH next ptr and dQH terminate bit to 0 */
    *(volatile unsigned int *)(dqh_address + 0x8) = td->dtd_base;

    /* 2. clear active & halt bit in dQH */
    *(volatile unsigned int *)(dqh_address + 0xC) &= ~0xFF;

    /* 3. prime endpoint by writing '1' in ENDPTPRIME */
    temp = readl(&usbotg[controller_ID]->endptprime);
    temp |= ep_mask << ep_num;
    writel(temp, &usbotg[controller_ID]->endptprime);
}

// Add TD to TD list and prime endpoint based on this algorithm:
// Appendix
// 5.5.3 Executing A Transfer Descriptor
// To safely add a dTD, the DCD must be follow this procedure which will handle the event where the device
// controller reaches the end of the dTD list at the same time a new dTD is being added to the end of the list.
// Determine whether the link list is empty:
// Check DCD driver to see if pipe is empty (internal representation of linked-list should indicate if any packets
// are outstanding).
// Case 1: Link list is empty
// 1. Write dQH next pointer AND dQH terminate bit to 0 as a single DWord operation.
// 2. Clear active & halt bit in dQH (in case set from a previous error).
// 3. Prime endpoint by writing '1' to correct bit position in ENDPTPRIME.
// Case 2: Link list is not empty
// 1. Add dTD to end of linked list.
// 2. Read correct prime bit in ENDPTPRIME - if '1' DONE.
// 3. Set ATDTW bit in USBCMD register to '1'.
// 4. Read correct status bit in ENDPTPRIME. (store in tmp. variable for later) [[this should be ENDPTSTATUS, not ENDPTPRIME]}
// 5. Read ATDTW bit in USBCMD register.
// If '0' goto 3.
// If '1' continue to 6.
// 6. Write ATDTW bit in USBCMD register to '0'.
// 7. If status bit read in (4) is '1' DONE.
// 8. If status bit read in (4) is '0' then Goto Case 1: Step 1.
//
static void usbd_add_td(uint_8 controller_ID, unsigned char ep_num, unsigned char direction, struct dtd_t *td)
{
    // Get the index into the TD list for this endpoint + direction
    int td_index = (ep_num * 2) + direction;

    if (g_usbd_queue_info[controller_ID][td_index].tail == NULL)
    {
        // Case 1: Link list is empty

        usbd_prime_ep(controller_ID, ep_num, direction, td);
    }
    else
    {
        // Case 2: Link list is not empty

        unsigned int ep_mask = (direction == OUT ? EPOUT_PRIME : EPIN_PRIME);

        // Add TD to tail next_link_ptr
        // Clear Terminate bit to indicate pointer is valid
        g_usbd_queue_info[controller_ID][td_index].tail->dtd_word0 = td->dtd_base & 0xFFFFFFE0;

        // If EP is already primed, we are done
        if (!(readl(&usbotg[controller_ID]->endptprime) & (ep_mask << ep_num)))
        {
            // EP not primed, check if it is active
            unsigned int ep_status = 0;
            unsigned int temp;

            // Use Add dTD Tripwire to properly read endpoint status register
            do
            {
                /* write '1' to Add Tripwire (ATDTW) in USBCMD register */
                temp = readl(&usbotg[controller_ID]->usbcmd);
                temp |= (0x1 << BP_USBC_(USBCMD_ATDTW));
                writel(temp, &usbotg[controller_ID]->usbcmd);

                // Read endpoint status
                ep_status = readl(&usbotg[controller_ID]->endptstat) & (ep_mask << ep_num);

            } while (!readl(&usbotg[controller_ID]->usbcmd) & (0x1 << BP_USBC_(USBCMD_ATDTW)));

            /* write '0' to Add Tripwire (ATDTW) in USBCMD register */
            temp = readl(&usbotg[controller_ID]->usbcmd);
            temp &= ~(0x1 << BP_USBC_(USBCMD_ATDTW));
            writel(temp, &usbotg[controller_ID]->usbcmd);

            if (!ep_status)
            {
                // Status is inactive, so need to prime EP
                usbd_prime_ep(controller_ID, ep_num, direction, td);
            }
        }
    }

    // Make this TD the tail
    g_usbd_queue_info[controller_ID][td_index].tail = (struct dtd_setup_t *)td->dtd_base;
}

/*!
 * Receive data through EPx
 *
 * @param    epx_data_buffer    EPx receive buffer
 * @param    sz                 Number of bytes to receive
 *
 * @return   SUCCESS on success, otherwise FAIL when timeout
 */
static usb_status_t usbd_receive_data_epxout(uint_8 controller_ID, unsigned int epx_data_buffer, uint_8 ep_num, unsigned int sz)
{
    struct dtd_t td;
    unsigned int total_bytes;
    unsigned int dtd_address;
    unsigned int direction = OUT;

    //printf_info("%s, size is %d\n", __func__, sz);
	
    /* Get Device Transfer Descriptor of the requested endpoint */
	dtd_address = usbd_get_dtd(controller_ID, ep_num, direction, sz);
    if (!dtd_address)
    {
        return USB_FAILURE;
    }

    /* Get the total bytes to be received   */
    total_bytes = sz;

	if (total_bytes > 20 * 1024)
	    printf_error("Error!!! %s, size is %d\n", __func__, sz);
		
    td.dtd_base = dtd_address;
   	td.next_link_ptr = 0;
    td.terminate = TERMINATE;
    td.total_bytes = total_bytes;
    td.ioc = IOC_SET;
    td.status = ACTIVE;
    td.buffer_ptr0 = epx_data_buffer;
    td.current_offset = (epx_data_buffer & 0xFFF);
    td.buffer_ptr1 = (epx_data_buffer & 0xFFFFF000) + 0x1000;
    td.buffer_ptr2 = (epx_data_buffer & 0xFFFFF000) + 0x2000;
    td.buffer_ptr3 = (epx_data_buffer & 0xFFFFF000) + 0x3000;
    td.buffer_ptr4 = (epx_data_buffer & 0xFFFFF000) + 0x4000;

    /* Set the Transfer Descriptor  */
    usbd_setup_td(&td);

    // Add TD to TD list for this endpoint + direction
    usbd_add_td(controller_ID, ep_num, direction, &td);

    return USB_SUCCESS;
}

/*!
 * Receive data through EP0
 *
 * @param    ep0_data_buffer    EP0 receive buffer
 * @param    sz                 Number of bytes to receive
 *
 * @return   SUCCESS on success, otherwise FAIL when timeout
 */
static usb_status_t usbd_receive_data_ep0out(uint_8 controller_ID, unsigned int ep0_data_buffer, unsigned int sz)
{
    struct dtd_t td;
    unsigned int total_bytes;
    unsigned int dtd_address;
    unsigned int dqh_address;
    unsigned int temp;

//    printf_info("%s, size is %d\n", __func__, sz);

    // Yi if (ep0_data_buffer != NULL)
    //  memset((void *)ep0_data_buffer, 0x0, 256);  //todo hard-coded size

    /* Get Device Device Queue Head of the requested endpoint */
    dqh_address = usbd_get_dqh(controller_ID, EP0, OUT);

    /* Get Device Transfer Descriptor of the requested endpoint */
	dtd_address = usbd_get_dtd(controller_ID, EP0, OUT, sz);
    if (!dtd_address)
    {
        return USB_FAILURE;
    }

    /* Get the total bytes to be received   */
    total_bytes = sz;

    td.dtd_base = dtd_address;
   	td.next_link_ptr = dtd_address + 0x20;
    td.terminate = TERMINATE;
    td.total_bytes = total_bytes;
    td.ioc = IOC_SET;
    td.status = ACTIVE;
    td.buffer_ptr0 = ep0_data_buffer;
    td.current_offset = (ep0_data_buffer & 0xFFF);
    td.buffer_ptr1 = (ep0_data_buffer & 0xFFFFF000) + 0x1000;
    td.buffer_ptr2 = (ep0_data_buffer & 0xFFFFF000) + 0x2000;
    td.buffer_ptr3 = (ep0_data_buffer & 0xFFFFF000) + 0x3000;
    td.buffer_ptr4 = (ep0_data_buffer & 0xFFFFF000) + 0x4000;

    /* Set the Transfer Descriptor  */
    usbd_setup_td(&td);

	//Yi
    //(*(volatile unsigned int *)(dqh_address)) &= ~0x20000000;

    /* 1. write dQH next ptr and dQH terminate bit to 0 */
    *(volatile unsigned int *)(dqh_address + 0x8) = dtd_address;

    /* 2. clear active & halt bit in dQH */
    *(volatile unsigned int *)(dqh_address + 0xC) &= ~0xFF;

    /* 3. prime endpoint by writing '1' in ENDPTPRIME */
    temp = readl(&usbotg[controller_ID]->endptprime);
    temp |= EPOUT_PRIME;
    writel(temp, &usbotg[controller_ID]->endptprime);
    while (readl(&usbotg[controller_ID]->endptprime) & EPOUT_PRIME) ;  //wait prime end

    return USB_SUCCESS;
}

/*!
 * Send data through endpoint x
 *
 * @param    epx_data_buffer    EPx send buffer
 * @param    sz                 Number of bytes to send
 *
 * @return   SUCCESS on success, otherwise FAIL when timeout
 */
static usb_status_t usbd_send_data_epxin(uint_8 controller_ID, unsigned int epx_data_buffer, uint_8 ep_num, unsigned int sz)
{
    struct dtd_t td;
    unsigned int total_bytes;
    unsigned int dtd_address;
    unsigned int direction = IN;

	printf_info("%s, size is %d\n", __func__, sz);

    /* varify Endpoint Number and address */
    /* Get Device Transfer Descriptor of the requested endpoint */
    dtd_address = usbd_get_dtd(controller_ID, ep_num, direction, sz);
    if (!dtd_address)
    {
        return USB_FAILURE;
    }

    /* Get Total Bytes to Be recieved */
    total_bytes = sz;

    td.dtd_base = dtd_address;
    td.next_link_ptr = 0;
    td.terminate = TERMINATE;
    td.total_bytes = total_bytes;
    td.ioc = IOC_SET;
    td.status = ACTIVE;
    td.buffer_ptr0 = epx_data_buffer;
    td.current_offset = (epx_data_buffer & 0xFFF);
    td.buffer_ptr1 = (epx_data_buffer & 0xFFFFF000) + 0x1000;
    td.buffer_ptr2 = (epx_data_buffer & 0xFFFFF000) + 0x2000;
    td.buffer_ptr3 = (epx_data_buffer & 0xFFFFF000) + 0x3000;
    td.buffer_ptr4 = (epx_data_buffer & 0xFFFFF000) + 0x4000;

    /* Set the transfer descriptor */
    usbd_setup_td(&td);

    // Add TD to TD list for this endpoint + direction
    usbd_add_td(controller_ID, ep_num, direction, &td);

    return USB_SUCCESS;
}

/*!
 * Send data through endpoint 0
 *
 * @param    ep0_data_buffer    EP0 send buffer
 * @param    sz                 Number of bytes to send
 * @param    zlt_enable         If ZLT is enabled
 *
 * @return   SUCCESS on success, otherwise FAIL when timeout
 */
static usb_status_t usbd_send_data_ep0in(uint_8 controller_ID,
                                         unsigned int ep0_data_buffer, unsigned int sz,
                                         unsigned char zlt_enable)
{
    struct dtd_t td;
    unsigned int total_bytes;
    unsigned int dtd_address, dqh_address;
    unsigned int temp;

	//printf_info("%s, size is %d\n", __func__, sz);

    /* varify Endpoint Number and address */
    /* Get Device Transfer Descriptor of the requested endpoint */
    dtd_address = usbd_get_dtd(controller_ID, EP0, IN, sz);
    if (!dtd_address)
    {
        return USB_FAILURE;
    }

    /* Get Device Queue head of the requested endpoint */
    dqh_address = usbd_get_dqh(controller_ID, EP0, IN);

    /* Get Total Bytes to Be recieved */
    total_bytes = sz;

    td.dtd_base = dtd_address;
    td.next_link_ptr = 0;
    td.terminate = TERMINATE;
    td.total_bytes = total_bytes;
    td.ioc = IOC_SET;
    td.status = ACTIVE;
    td.buffer_ptr0 = ep0_data_buffer;
    td.current_offset = (ep0_data_buffer & 0xFFF);
    td.buffer_ptr1 = (ep0_data_buffer & 0xFFFFF000) + 0x1000;
    td.buffer_ptr2 = (ep0_data_buffer & 0xFFFFF000) + 0x2000;
    td.buffer_ptr3 = (ep0_data_buffer & 0xFFFFF000) + 0x3000;
    td.buffer_ptr4 = (ep0_data_buffer & 0xFFFFF000) + 0x4000;

    /* Set the transfer descriptor */
    usbd_setup_td(&td);

    /* Enable ZLT when data size is in multiple of Maximum Packet Size  */
    /* set ZLT enable, already done at usbd_ep0_init*/
//    (*(volatile unsigned int *)(dqh_address)) &= ~0x20000000;

    /* 1. write dQH next ptr and dQH terminate bit to 0  */
    *(volatile unsigned int *)(dqh_address + 0x8) = (dtd_address);

    /* 2. clear active & halt bit in dQH */
    *(volatile unsigned int *)(dqh_address + 0xC) &= ~0xFF;

    temp = readl(&usbotg[controller_ID]->endptprime);
    temp |= EPIN_PRIME;
    writel(temp, &usbotg[controller_ID]->endptprime);

    /* 4. wait for prime complete */
    while (readl(&usbotg[controller_ID]->endptprime) & EPIN_PRIME) ;

    return USB_SUCCESS;
}
