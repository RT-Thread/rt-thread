#ifndef USB_H_
#define USB_H_

//*****************************************************************************
//
// These macros allow conversion between 0-based endpoint indices and the
// USB_EP_x values required when calling various USB APIs.
//
//*****************************************************************************
#define INDEX_TO_USB_EP(x)      ((x) << 4)
#define USB_EP_TO_INDEX(x)      ((x) >> 4)

//*****************************************************************************
//
// The following are values that can be passed to USBFIFOConfigSet() as the
// uFIFOSize parameter.
//
//*****************************************************************************
#define USB_FIFO_SZ_8           0x00000000  // 8 byte FIFO
#define USB_FIFO_SZ_16          0x00000001  // 16 byte FIFO
#define USB_FIFO_SZ_32          0x00000002  // 32 byte FIFO
#define USB_FIFO_SZ_64          0x00000003  // 64 byte FIFO
#define USB_FIFO_SZ_128         0x00000004  // 128 byte FIFO
#define USB_FIFO_SZ_256         0x00000005  // 256 byte FIFO
#define USB_FIFO_SZ_512         0x00000006  // 512 byte FIFO
#define USB_FIFO_SZ_1024        0x00000007  // 1024 byte FIFO


//*****************************************************************************
//
// This macro allow conversion from a FIFO size label as defined above to
// a number of bytes
//
//*****************************************************************************
#define USB_FIFO_SIZE_DB_FLAG  0x00000010
#define USB_FIFO_SZ_TO_BYTES(x) ((8 << ((x) & ~ USB_FIFO_SIZE_DB_FLAG)) * \
                                 (((x) & USB_FIFO_SIZE_DB_FLAG) ? 2 : 1))

								 
//*****************************************************************************
//
//! The maximum number of independent interfaces that any single device
//! implementation can support.  Independent interfaces means interface
//! descriptors with different bInterfaceNumber values - several interface
//! descriptors offering different alternative settings but the same interface
//! number count as a single interface.
//
//*****************************************************************************
#define USB_MAX_INTERFACES_PER_DEVICE 8


//*****************************************************************************
//
//! Following macro directives can be used for the configuring the USB device.
//! Note that these directives map directly to the hardware bit definitions and
//! cannot be modified to any other value.
//
//*****************************************************************************
#define USBD_PWR_BUS_PWR				(0x0000u) 	//Device is bus powered
#define USBD_PWR_SELF_PWR   			(0x0004u)	//Device is self powered
#define USBD_DATA_ENDIAN_LITTLE			(0x0000u)	//Little Endian Data (RM48x)
#define USBD_DATA_ENDIAN_BIG			(0x0080u)	//Bit Endian Data
#define USBD_DMA_ENDIAN_LITTLE			(0x0000u)	//DMA is Little Endian
#define USBD_DMA_ENDIAN_BIG				(0x0040u)	//DMA is Big Endian

//*****************************************************************************
//
//! Following macro directives can be used for the configuring the Endpoints
//! Note that these directives map directly to the hardware bit definitions and
//! cannot be modified to any other value.
//
//*****************************************************************************
#define USBD_EP_DIR_IN       			(0x0010u)		//IN Endpoint
#define USBD_EP_DIR_OUT       			(0x0000u)		//OUT Endpoint
#define USB_EP_DEV_IN					USBD_EP_DIR_IN	//IN Endpoint
#define USB_EP_DEV_OUT					USBD_EP_DIR_OUT	//OUT Endpoint
#define USB_TRANS_IN					USBD_EP_DIR_IN	//IN Endpoint
#define USB_TRANS_OUT					USBD_EP_DIR_OUT	//OUT Endpoint
#define USB_EP_DIR_IN					USBD_EP_DIR_IN
#define USB_EP_DIR_OUT					USBD_EP_DIR_OUT
#define USB_TRANS_IN_LAST				0				//Used to indicate the last transaction
														//(NOT USED in this port of USB)

#define USBD_TXRX_EP_VALID_VALID		(0x8000u)		//EP is valid & configured
#define USBD_TXRX_EP_VALID_NOTVALID		(0x0000u)		//EP is not valid & not configured
#define USBD_TXRX_EP_ISO_ISO			(0x0800u)		//EP is of ISO type
#define USBD_TXRX_EP_ISO_NONISO			(0x0000u)		//EP is either Bulk/Interrup/Control
#define USBD_TXRX_EP_DB_ENABLED			(0x4000u) 		//EP has double buffering enabled
														// For IN EPs DB should be enabled only in DMA mode */
#define USBD_TXRX_EP_DB_DISABLED		(0x0000u)		//EP has double buffering disabled

//*****************************************************************************
//
//! Following macro directives are to be used for enabling/disabling interrupts
//! Note that these directives map directly to the hardware bit definitions and
//! cannot be modified to any other value.
//
//*****************************************************************************
#define USBD_INT_EN_SOF_IE      				(0x0080u)	//Start-of-Frame Interrupt
#define USBD_INT_EN_EPN_RX_IE   				(0x0020u)	//Non-EP0 RX Interrupt
#define USBD_INT_EN_EPN_TX_IE   				(0x0010u)	//Non-EP0 TX Interrupt
#define USBD_INT_EN_DS_CHG_IE   				(0x0008u)	//Device State change interrupt
#define USBD_INT_EN_EP0_IE      				(0x0001u)	//EP0 Interrupt
#define USBD_INT_EN_ALL							(USBD_IRQ_EN_SOF_IE | \
												 USBD_IRQ_EN_EPN_RX_IE | \
												 USBD_IRQ_EN_EPN_TX_IE | \
												 USBD_IRQ_EN_DS_CHG_IE | \
												 USBD_IRQ_EN_EP0_IE)


//*****************************************************************************
//
//! Following macro directives are to be used for decoding the interrupt source
//! Note that these directives map directly to the hardware bit definitions and
//! cannot be modified to any other value.
//
//*****************************************************************************
#define USBD_INT_SRC_TXN_DONE   				(0x0400u)	//non-EP0 TX done interrupt
#define USBD_INT_SRC_RXN_CNT    				(0x0200u)	//non-EP0 RX Count
#define USBD_INT_SRC_RXN_EOT    				(0x0100u)	//non-EP0 RX end of transfer
#define USBD_INT_SRC_SOF        				(0x0080u)	//Start-of-frame interrupt
#define USBD_INT_SRC_EPN_RX     				(0x0020u)	//non-EP0 RX interrupt
#define USBD_INT_SRC_EPN_TX    					(0x0010u)	//non-EP0 TX interrupt
#define USBD_INT_SRC_DS_CHG     				(0x0008u)	//Device State change interrupt
#define USBD_INT_SRC_SETUP      				(0x0004u)	//Setup interrupt
#define USBD_INT_SRC_EP0_RX     				(0x0002u)	//EP0 RX Interrupt
#define USBD_INT_SRC_EP0_TX     				(0x0001u)	//EP0 TX Interrupt


//*****************************************************************************
//
// These values are used to indicate which endpoint to access.
//
//*****************************************************************************
#define USB_EP_0                0x00000000  // Endpoint 0
#define USB_EP_1                0x00000010  // Endpoint 1
#define USB_EP_2                0x00000020  // Endpoint 2
#define USB_EP_3                0x00000030  // Endpoint 3
#define USB_EP_4                0x00000040  // Endpoint 4
#define USB_EP_5                0x00000050  // Endpoint 5
#define USB_EP_6                0x00000060  // Endpoint 6
#define USB_EP_7                0x00000070  // Endpoint 7
#define USB_EP_8                0x00000080  // Endpoint 8
#define USB_EP_9                0x00000090  // Endpoint 9
#define USB_EP_10               0x000000A0  // Endpoint 10
#define USB_EP_11               0x000000B0  // Endpoint 11
#define USB_EP_12               0x000000C0  // Endpoint 12
#define USB_EP_13               0x000000D0  // Endpoint 13
#define USB_EP_14               0x000000E0  // Endpoint 14
#define USB_EP_15               0x000000F0  // Endpoint 15
#define NUM_USB_EP              16          // Number of supported endpoints


//*****************************************************************************
//
// The following are values that can be passed to USBHostEndpointConfig() and
// USBDevEndpointConfigSet() as the ulFlags parameter.
//
//*****************************************************************************
#define USB_EP_AUTO_SET         0x00000001u  // Auto set feature enabled
#define USB_EP_AUTO_REQUEST     0x00000002u  // Auto request feature enabled
#define USB_EP_AUTO_CLEAR       0x00000004u  // Auto clear feature enabled
#define USB_EP_DMA_MODE_0       0x00000008u  // Enable DMA access using mode 0
#define USB_EP_DMA_MODE_1       0x00000010u  // Enable DMA access using mode 1
#define USB_EP_MODE_ISOC        0x00000000u  // Isochronous endpoint
#define USB_EP_MODE_BULK        0x00000100u  // Bulk endpoint
#define USB_EP_MODE_INT         0x00000200u  // Interrupt endpoint
#define USB_EP_MODE_CTRL        0x00000300u  // Control endpoint
#define USB_EP_MODE_MASK        0x00000300u  // Mode Mask
#define USB_EP_SPEED_LOW        0x00000000u  // Low Speed
#define USB_EP_SPEED_FULL       0x00001000u  // Full Speed


//*****************************************************************************
//
// The following are values that are returned from USBEndpointStatus().  The
// USB_HOST_* values are used when the USB controller is in host mode and the
// USB_DEV_* values are used when the USB controller is in device mode.
//
//*****************************************************************************
#define USB_DEV_EP0_OUT_PKTRDY 0x00000001u  // Receive data packet ready
#define USB_DEV_RX_PKT_RDY    	0x00010000u  // Data packet ready
#define USB_DEV_TX_TXPKTRDY		0x00000001u
#define USB_DEV_TX_FIFO_NE		0x00000002u


//*****************************************************************************
//
// This value specifies the maximum size of transfers on endpoint 0 as 64
// bytes.  This value is fixed in hardware as the FIFO size for endpoint 0.
//
//*****************************************************************************
#define MAX_PACKET_SIZE_EP0     64


//*****************************************************************************
//
// Macros for hardware access, both direct and via the bit-band region.
//
//*****************************************************************************
#define HWREG(x) 				(*((volatile unsigned int *)(x)))




//*****************************************************************************
//
//! Initialize the USB Device
//!
//! \param ulBase specifies the USB module base address.
//! \param usFlags specifies the bus/self powered and endianness for data & dma.
//!			Should be a combination of the following flags
//! 			USBD_PWR_BUS_PWR or USBD_PWR_SELF_PWR
//!				USBD_DATA_ENDIAN_LITTLE or USBD_DATA_ENDIAN_BIG
//!				USBD_DMA_ENDIAN_LITTLE or USBD_DMA_ENDIAN_BIG
//! \param usFifoPtr specifies the start of the EP0 FIFO.
//!
//! This function will initialize the USB Device controller specified by the
//! \e ulBase parameter.
//!
//! \return None
//!
//! Note This function does not intiate a device connect (pull ups are
//! not enabled). Also the EP0 is intialized with FIFO size of 64Bytes.
//!
//
//*****************************************************************************
void USBDevInit(uint32 ulBase, uint16 usFlags, uint16 usFifoPtr);


//*****************************************************************************
//
//! Initialize the USB Device's EP0
//!
//! \param ulBase specifies the USB module base address.
//! \param usSize FIFO size. Supported values are USB_FIFO_SZ_8/USB_FIFO_SZ_16/
//!			USB_FIFO_SZ_32/USB_FIFO_SZ_64.
//! \param usFifoPtr specifies the start of the EP0 FIFO.
//!
//! This function will initialize the USB Device controller specified by the
//! \e ulBase parameter.  The \e uFlags parameter is not used by this
//! implementation.
//!
//! \return None
//!
//
//*****************************************************************************
void USBDevEp0Config(uint32 ulBase, uint16 usSize, uint16 usFifoPtr);


//*****************************************************************************
//
//! Disable control interrupts on a given USB device controller.
//!
//! \param ulBase specifies the USB module base address.
//! \param usFlags specifies which control interrupts to disable.
//!
//! This function will disable the interrupts for the USB device controller
//! specified by the \e ulBase parameter.  The \e usFlags parameter specifies
//! which control interrupts to disable.  The flags passed in the \e usFlags
//! parameters should be the definitions that start with \b USBD_INT_EN_*
//!
//! \return None.
//
//*****************************************************************************
void USBIntDisable(uint32 ulBase, uint16 usFlags);


//*****************************************************************************
//
//! Enable control interrupts on a given USB device controller.
//!
//! \param ulBase specifies the USB module base address.
//! \param usFlags specifies which control interrupts to enable.
//!
//! This function will enable the control interrupts for the USB device controller
//! specified by the \e ulBase parameter.  The \e usFlags parameter specifies
//! which control interrupts to enable.  The flags passed in the \e usFlags
//! parameters should be the definitions that start with \b USBD_INT_EN_* and
//! not any other \b USB_INT flags.
//!
//! \return None.
//
//*****************************************************************************
void USBIntEnable(uint32 ulBase, uint16 usFlags);


//*****************************************************************************
//
//! Returns the control interrupt status on a given USB device controller.
//!
//! \param ulBase specifies the USB module base address.
//!
//! This function will read interrupt status for a USB device controller.
//! The bit values returned should be compared against the \b USBD_INT_SRC_*
//! values.
//!
//! \return Returns the status of the control interrupts for a USB device controller.
//
//*****************************************************************************
uint16 USBIntStatus(uint32 ulBase);


//*****************************************************************************
//
//! Stalls the specified endpoint in device mode.
//!
//! \param ulBase specifies the USB module base address.
//! \param usEndpoint specifies the endpoint to stall.
//! \param usFlags specifies whether to stall the IN or OUT endpoint.
//!
//! This function will cause to endpoint number passed in to go into a stall
//! condition.  If the \e usFlags parameter is \b USB_EP_DEV_IN then the stall
//! will be issued on the IN portion of this endpoint.  If the \e usFlags
//! parameter is \b USB_EP_DEV_OUT then the stall will be issued on the OUT
//! portion of this endpoint.
//!
//! \note This function should only be called in device mode.
//!
//! \return None.
//
//*****************************************************************************
void USBDevEndpointStall(uint32 ulBase, uint16 usEndpoint, uint16 usFlags);


//*****************************************************************************
//
//! Clears the stall condition on the specified endpoint in device mode.
//!
//! \param ulBase specifies the USB module base address.
//! \param usEndpoint specifies which endpoint to remove the stall condition.
//! \param usFlags specifies whether to remove the stall condition from the IN
//! or the OUT portion of this endpoint.
//!
//! This function will cause the endpoint number passed in to exit the stall
//! condition.  If the \e usFlags parameter is \b USB_EP_DEV_IN then the stall
//! will be cleared on the IN portion of this endpoint.  If the \e usFlags
//! parameter is \b USB_EP_DEV_OUT then the stall will be cleared on the OUT
//! portion of this endpoint.
//!
//! \note This function should only be called in device mode.
//!
//! \return None.
//
//*****************************************************************************
void USBDevEndpointStallClear(uint32 ulBase, uint16 usEndpoint, uint16 usFlags);


//*****************************************************************************
//
//! Connects the USB device controller to the bus in device mode.
//!
//! \param ulBase specifies the USB module base address.
//!
//! This function will cause the soft connect feature of the USB device controller to
//! be enabled.  Call USBDisconnect() to remove the USB device from the bus.
//!
//!
//! \return None.
//
//*****************************************************************************
void USBDevConnect(uint32 ulBase);


//*****************************************************************************
//
//! Removes the USB device controller from the bus in device mode.
//!
//! \param ulBase specifies the USB module base address.
//!
//! This function will cause the soft disconnect feature of the USB device controller to
//! remove the device from the USB bus.  A call to USBDevConnect() is needed to
//! reconnect to the bus.
//!
//!
//! \return None.
//
//*****************************************************************************
void USBDevDisconnect(uint32 ulBase);


//*****************************************************************************
//
//! Sets the address in device mode.
//!
//! \param ulBase specifies the USB module base address.
//! \param ulAddress is the address to use for a device.
//!
//! This function will set the device address on the USB bus.  This address was
//! likely received via a SET ADDRESS command from the host controller.
//!
//! \note This function is not available on this controller. This is maintained
//! 		for compatibility.
//!
//! \return None.
//
//*****************************************************************************
void USBDevAddrSet(uint32 ulBase, uint32 ulAddress);


//*****************************************************************************
//
//! Determine the number of bytes of data available in a given endpoint's FIFO.
//!
//! \param ulBase specifies the USB module base address.
//! \param usEndpoint is the endpoint to access.
//!
//! This function will return the number of bytes of data currently available
//! in the FIFO for the given receive (OUT) endpoint.  It may be used prior to
//! calling USBEndpointDataGet() to determine the size of buffer required to
//! hold the newly-received packet.
//!
//! \return This call will return the number of bytes available in a given
//! endpoint FIFO.
//
//*****************************************************************************
uint16 USBEndpointDataAvail(uint32 ulBase, uint16 usEndpoint);


//*****************************************************************************
//
//! Retrieves data from the given endpoint's FIFO.
//!
//! \param ulBase specifies the USB module base address.
//! \param usEndpoint is the endpoint to access.
//! \param pucData is a pointer to the data area used to return the data from
//! the FIFO.
//! \param pulSize is initially the size of the buffer passed into this call
//! via the \e pucData parameter.  It will be set to the amount of data
//! returned in the buffer.
//!
//! This function will return the data from the FIFO for the given endpoint.
//! The \e pulSize parameter should indicate the size of the buffer passed in
//! the \e pulData parameter.  The data in the \e pulSize parameter will be
//! changed to match the amount of data returned in the \e pucData parameter.
//! If a zero byte packet was received this call will not return a error but
//! will instead just return a zero in the \e pulSize parameter.  The only
//! error case occurs when there is no data packet available.
//!
//! \return This call will return 0, or -1 if no packet was received.
//
//*****************************************************************************
uint32 USBEndpointDataGet(uint32 ulBase, uint16 usEndpoint, uint8 *pucData, uint32 *pulSize);


//*****************************************************************************
//
//! Retrieves the setup packet from EP0 Setup FIFO
//!
//! \param ulBase specifies the USB module base address.
//! \param sPkt Pointer to the data area for storing the setup packet.
//!			Atleast 8 bytes should be available.
//! \param pusPktSize On return this contains the size of the setup packet (8Bytes)
//!
//! This function will retrieves the 8Byte long setup packet from the EP0 setup
//! FIFO.
//!
//! \return None.
//
//*****************************************************************************
void USBDevGetSetupPacket (uint32 ulBase, uint8 * sPkt, uint16 * pusPktSize);


//*****************************************************************************
//
//! Acknowledge that data was read from the given endpoint's FIFO in device
//! mode.
//!
//! \param ulBase specifies the USB module base address.
//! \param usEndpoint is the endpoint to access.
//! \param bIsLastPacket This parameter is not used.
//!
//! This function acknowledges that the data was read from the endpoint's FIFO.
//! The \e bIsLastPacket parameter is set to a \b true value if this is the
//! last in a series of data packets on endpoint zero.  The \e bIsLastPacket
//! parameter is not used for endpoints other than endpoint zero.  This call
//! can be used if processing is required between reading the data and
//! acknowledging that the data has been read.
//!
//!
//! \return None.
//
//*****************************************************************************
void USBDevEndpointDataAck(uint32 ulBase, uint16 usEndpoint, uint8 bIsLastPacket);


//*****************************************************************************
//
//! Puts data into the given endpoint's FIFO.
//!
//! \param ulBase specifies the USB module base address.
//! \param usEndpoint is the endpoint to access.
//! \param pucData is a pointer to the data area used as the source for the
//! data to put into the FIFO.
//! \param ulSize is the amount of data to put into the FIFO.
//!
//! This function will put the data from the \e pucData parameter into the FIFO
//! for this endpoint.  If a packet is already pending for transmission then
//! this call will not put any of the data into the FIFO and will return -1.
//! Care should be taken to not write more data than can fit into the FIFO
//! allocated by the call to USBFIFOConfig().
//!
//! \return This call will return 0 on success, or -1 to indicate that the FIFO
//! is in use and cannot be written.
//
//*****************************************************************************
uint32 USBEndpointDataPut(uint32 ulBase, uint16 usEndpoint,uint8 *pucData, uint32 ulSize);


//*****************************************************************************
//
//! Starts the transfer of data from an endpoint's FIFO.
//!
//! \param ulBase specifies the USB module base address.
//! \param usEndpoint is the endpoint to access.
//! \param ulTransType Not used.
//!
//! This function will start the transfer of data from the FIFO for a given
//! endpoint.
//!
//! \return This call will return 0 on success, or -1 if a transmission is
//! already in progress.
//
//*****************************************************************************
uint32 USBEndpointDataSend(uint32 ulBase, uint16 usEndpoint, uint32 ulTransType);


//*****************************************************************************
//
//! Resets the USB Device Controller
//!
//! \param void
//!
//! \return None.
//
//! \note Since the USB Device reset is handled by the host, this is a dummy
//! function & maintained for compatibility purpose.
//
//*****************************************************************************
void USBReset(void);


//*****************************************************************************
//
//! Sets the FIFO configuration for an endpoint.
//!
//! \param ulBase specifies the USB module base address.
//! \param usEndpoint is the endpoint to access.
//! \param uFIFOAddress is the starting address for the FIFO.
//! \param uFIFOSize is the size of the FIFO in bytes.
//! \param uFlags specifies what information to set in the FIFO configuration.
//!
//! This function will set the starting FIFO RAM address and size of the FIFO
//! for a given endpoint.  Endpoint zero does not have a dynamically
//! configurable FIFO so this function should not be called for endpoint zero.
//! The \e uFIFOSize parameter should be one of the values in the
//! \b USB_FIFO_SZ_ values.  If the endpoint is going to use double buffering
//! it should use the values with the \b _DB at the end of the value.  For
//! example, use \b USB_FIFO_SZ_16_DB to configure an endpoint to have a 16
//! byte double buffered FIFO.  If a double buffered FIFO is used, then the
//! actual size of the FIFO will be twice the size indicated by the
//! \e uFIFOSize parameter.  This means that the \b USB_FIFO_SZ_16_DB value
//! will use 32 bytes of the USB controller's FIFO memory.
//!
//! The \e uFIFOAddress value should be a multiple of 8 bytes and directly
//! indicates the starting address in the USB controller's FIFO RAM.  For
//! example, a value of 64 indicates that the FIFO should start 64 bytes into
//! the USB controller's FIFO memory.  The \e uFlags value specifies whether
//! the endpoint's OUT or IN FIFO should be configured.  If in host mode, use
//! \b USB_EP_HOST_OUT or \b USB_EP_HOST_IN, and if in device mode use
//! \b USB_EP_DEV_OUT or \b USB_EP_DEV_IN.
//!
//! \return None.
//
//*****************************************************************************
void USBFIFOConfigSet(uint32 ulBase, uint32 usEndpoint, uint32 uFIFOAddress, uint32 uFIFOSize, uint16 uFlags);


//*****************************************************************************
//
//! Gets the current configuration for an endpoint.
//!
//! \param ulBase specifies the USB module base address.
//! \param usEndpoint is the endpoint to access.
//! \param pulMaxPacketSize is a pointer which will be written with the
//! maximum packet size for this endpoint.
//! \param puFlags is a pointer which will be written with the current
//! endpoint settings. On entry to the function, this pointer must contain
//! either \b USB_EP_DEV_IN or \b USB_EP_DEV_OUT to indicate whether the IN or
//! OUT endpoint is to be queried.
//!
//! This function will return the basic configuration for an endpoint in device
//! mode. The values returned in \e *pulMaxPacketSize and \e *puFlags are
//! equivalent to the \e ulMaxPacketSize and \e uFlags previously passed to
//! USBDevEndpointConfigSet() for this endpoint.
//!
//! \note This function should only be called in device mode.
//!
//! \return None.
//
//*****************************************************************************
void USBDevEndpointConfigGet(uint32 ulBase, uint16 usEndpoint, uint32*pulMaxPacketSize, uint32*puFlags);


//*****************************************************************************
//
//! Sets the configuration for an endpoint.
//!
//! \param ulBase specifies the USB module base address.
//! \param usEndpoint is the endpoint to access.
//! \param ulMaxPacketSize is the maximum packet size for this endpoint.
//! \param uFlags are used to configure other endpoint settings.
//!
//! This function will set the basic configuration for an endpoint in device
//! mode.  Endpoint zero does not have a dynamic configuration, so this
//! function should not be called for endpoint zero.  The \e uFlags parameter
//! determines some of the configuration while the other parameters provide the
//! rest.
//!
//! The \b USB_EP_MODE_ flags define what the type is for the given endpoint.
//!
//! - \b USB_EP_MODE_CTRL is a control endpoint.
//! - \b USB_EP_MODE_ISOC is an isochronous endpoint.
//! - \b USB_EP_MODE_BULK is a bulk endpoint.
//! - \b USB_EP_MODE_INT is an interrupt endpoint.
//!
//!
//! \note This function should only be called in device mode.
//!
//! \return None.
//
//*****************************************************************************
void USBDevEndpointConfigSet(uint32 ulBase, uint16 usEndpoint, uint32 ulMaxPacketSize, uint16 uFlags);

void USBDevSetDevCfg(uint32 ulBase);
void USBDevClearDevCfg(uint32 ulBase);
uint16 USBDevGetEPnStat(uint32 ulBase);
void USBDevPullEnableDisable(uint32 ulBase, uint32 ulSet);
void USBIntStatusClear (uint16 uFlag);
uint16 USBDevGetDevStat(uint32 ulBase);
void USBDevCfgUnlock(uint32 ulBase);
void USBDevCfgLock(uint32 ulBase);

#endif /*USB_H_*/
