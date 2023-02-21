/**************************************************************************//**
 * @file     hsusbd_reg.h
 * @brief    HSUSBD register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __HSUSBD_REG_H__
#define __HSUSBD_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif


/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/

/** @addtogroup REGISTER Control Register

  @{

*/


/*---------------------- High Speed USB 2.0 Device Controller -------------------------*/
/**
    @addtogroup HSUSBD High Speed USB 2.0 Device Controller(HSUSBD)
    Memory Mapped Structure for HSUSBD Controller
@{ */

/*----- IN Endpoint 1~8 -----*/
typedef struct
{

    /**
     * @var HSUSBD_T::DIEPCTLn
     * Offset: 0x00  Device Control IN Endpoint n Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |MPS       |Maximum Packet Size (MPS)
     * |        |          |The application must program this field with the maximum packet size for the current logical endpoint
     * |        |          |This value is in bytes.
     * |[15]    |USBActEP  |USB Active Endpoint (USBActEP)
     * |        |          |Indicates whether this endpoint is active in the current configuration and interface
     * |        |          |The core clears this bit for all endpoints (other than EP 0) after detecting a USB reset
     * |        |          |After receiving the SetConfiguration and SetInterface commands, the application must program endpoint registers accordingly and set this bit.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): Not Active
     * |        |          |0x1 (ENABLED): USB Active Endpoint
     * |[16]    |DPID      |Endpoint Data PID (DPID) (Read only)
     * |        |          |Applies to interrupt/bulk IN and OUT endpoints only.
     * |        |          |Contains the PID of the packet to be received or transmitted on this endpoint
     * |        |          |The application must program the PID of the first packet to be received or transmitted on this endpoint, after the endpoint is activated
     * |        |          |The applications use the SetD1PID and SetD0PID fields of this register to program either DATA0 or DATA1 PID.
     * |        |          |1'b0: DATA0
     * |        |          |1'b1: DATA1
     * |        |          |Values:
     * |        |          |0x0 (DATA0EVENFRM): DATA0 or Even Frame
     * |        |          |0x1 (DATA1ODDFRM): DATA1 or Odd Frame
     * |[17]    |NAKSts    |NAK Status (NAKSts) (Read only)
     * |        |          |Indicates the following:
     * |        |          |1'b0: The core is transmitting non-NAK handshakes based on the FIFO status.
     * |        |          |1'b1: The core is transmitting NAK handshakes on this endpoint.
     * |        |          |When either the application or the core sets this bit:
     * |        |          |The core stops receiving any data on an OUT endpoint, even if there is space in the RxFIFO to accommodate the incoming packet.
     * |        |          |For non-isochronous IN endpoints: The core stops transmitting any data on an IN endpoint, even if there data is available in the TxFIFO.
     * |        |          |For isochronous IN endpoints: The core sends out a zero-length data packet, even if there data is available in the TxFIFO.
     * |        |          |Irrespective of this bit's setting, the core always responds to SETUP data packets with an ACK handshake.
     * |        |          |Values:
     * |        |          |0x0 (NONNAK):
     * |        |          |The core is transmitting non-NAK handshakes based on the FIFO status
     * |        |          |0x1 (NAK):
     * |        |          |The core is transmitting NAK handshakes on this endpoint
     * |[19:18] |EPType    |Endpoint Type (EPType)
     * |        |          |This is the transfer type supported by this logical endpoint
     * |        |          |2'b00: Control
     * |        |          |2'b01: Isochronous
     * |        |          |2'b10: Bulk
     * |        |          |2'b11: Interrupt
     * |        |          |Values:
     * |        |          |0x0 (CONTROL): Control
     * |        |          |0x1 (ISOCHRONOUS): Isochronous
     * |        |          |0x2 (BULK): Bulk
     * |        |          |0x3 (INTERRUP): Interrupt
     * |[21]    |Stall     |STALL Handshake (Stall)
     * |        |          |Applies to non-control, non-isochronous IN and OUT endpoints only.
     * |        |          |The application sets this bit to stall all tokens from the USB host to this endpoint
     * |        |          |If a NAK bit, Global Non-periodic IN NAK, or Global OUT NAK is set along with this bit, the STALL bit takes priority
     * |        |          |Only the application can clear this bit, never the core.
     * |        |          |Applies to control endpoints only.
     * |        |          |The application can only set this bit, and the core clears it, when a SETUP token is received for this endpoint
     * |        |          |If a NAK bit, Global Non-periodic IN NAK, or Global OUT NAK is set along with this bit, the STALL bit takes priority
     * |        |          |Irrespective of this bit's setting, the core always responds to SETUP data packets with an ACK handshake.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): STALL All non-active tokens
     * |        |          |0x1 (ACTIVE): STALL All Active Tokens
     * |[25:22] |TxFNum    |TxFIFO Number (TxFNum)
     * |        |          |Dedicated FIFO Operation: These bits specify the FIFO number associated with this endpoint
     * |        |          |Each active IN endpoint must be programmed to a separate FIFO number
     * |        |          |This field is valid only for IN endpoints.
     * |        |          |Values:
     * |        |          |0x0 (TXFIFO0): Tx FIFO 0
     * |        |          |0x1 (TXFIFO1): Tx FIFO 1
     * |        |          |0x2 (TXFIFO2): Tx FIFO 2
     * |        |          |0x3 (TXFIFO3): Tx FIFO 3
     * |        |          |0x4 (TXFIFO4): Tx FIFO 4
     * |        |          |0x5 (TXFIFO5): Tx FIFO 5
     * |        |          |0x6 (TXFIFO6): Tx FIFO 6
     * |        |          |0x7 (TXFIFO7): Tx FIFO 7
     * |        |          |0x8 (TXFIFO8): Tx FIFO 8
     * |[26]    |CNAK      |Clear NAK (CNAK)
     * |        |          |A write to this bit clears the NAK bit for the endpoint.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Clear NAK
     * |        |          |0x1 (ACTIVE): Clear NAK
     * |[27]    |SNAK      |Set NAK (SNAK)
     * |        |          |A write to this bit sets the NAK bit for the endpoint.
     * |        |          |Using this bit, the application can control the transmission of NAK handshakes on an endpoint
     * |        |          |The core can also Set this bit for an endpoint after a SETUP packet is received on that endpoint.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Set NAK
     * |        |          |0x1 (ACTIVE): Set NAK
     * |[30]    |EPDis     |Endpoint Disable (EPDis)
     * |        |          |Applies to IN and OUT endpoints.
     * |        |          |The application sets this bit to stop transmitting/receiving data on an endpoint, even before the transfer for that endpoint is complete
     * |        |          |The application must wait for the Endpoint Disabled interrupt before treating the endpoint as disabled
     * |        |          |The core clears this bit before setting the Endpoint Disabled interrupt
     * |        |          |The application must set this bit only if Endpoint Enable is already set for this endpoint.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Action
     * |        |          |0x1 (ACTIVE): Disable Endpoint
     * |[31]    |EPEna     |Endpoint Enable (EPEna)
     * |        |          |Applies to IN and OUT endpoints.
     * |        |          |When Scatter/Gather DMA mode is enabled,
     * |        |          |For IN endpoints this bit indicates that the descriptor structure and data buffer with data ready to transmit is setup.
     * |        |          |For OUT endpoint it indicates that the descriptor structure and data buffer to receive data is setup.
     * |        |          |The core clears this bit before setting any of the following interrupts on this endpoint:
     * |        |          |SETUP Phase Done
     * |        |          |Endpoint Disabled
     * |        |          |Transfer Completed
     * |        |          |Note: For control endpoints in DMA mode, this bit must be set to be able to transfer SETUP data packets in memory.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Action
     * |        |          |0x1 (ACTIVE): Enable Endpoint
     * @var HSUSBD_T::DIEPINTn
     * Offset: 0x08  Device IN Endpoint n Interrupt Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |XferCompl |Transfer Completed Interrupt (XferCompl)
     * |        |          |Applies to IN and OUT endpoints.
     * |        |          |When Scatter/Gather DMA mode is enabled
     * |        |          |For IN endpoint this field indicates that the requested data from the descriptor is moved from external system memory to internal FIFO.
     * |        |          |For OUT endpoint this field indicates that the requested data from the internal FIFO is moved to external system memory
     * |        |          |This interrupt is generated only when the corresponding endpoint descriptor is closed, and the IOC bit for the corresponding descriptor is set.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Transfer Complete Interrupt
     * |        |          |0x1 (ACTIVE): Transfer Complete Interrupt
     * |[1]     |EPDisbld  |Endpoint Disabled Interrupt (EPDisbld)
     * |        |          |Applies to IN and OUT endpoints.
     * |        |          |This bit indicates that the endpoint is disabled per the application's request.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Endpoint Disabled Interrupt
     * |        |          |0x1 (ACTIVE): Endpoint Disabled Interrupt
     * |[2]     |AHBErr    |AHB Error (AHBErr)
     * |        |          |Applies to IN and OUT endpoints.
     * |        |          |When there is an AHB error during an AHB read/write
     * |        |          |The application can read the corresponding endpoint DMA address register to get the error address.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No AHB Error Interrupt
     * |        |          |0x1 (ACTIVE): AHB Error interrupt
     * |[4]     |INTknTXFEmp|IN Token Received When TxFIFO is Empty (INTknTXFEmp)
     * |        |          |Applies to non-periodic IN endpoints only.
     * |        |          |Indicates that an IN token was received when the associated TxFIFO (periodic/non-periodic) was empty
     * |        |          |This interrupt is asserted on the endpoint for which the IN token was received.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No IN Token Received interrupt
     * |        |          |0x1 (ACTIVE): IN Token Received Interrupt
     * |[5]     |INTknEPMis|IN Token Received with EP Mismatch (INTknEPMis)
     * |        |          |Applies to non-periodic IN endpoints only.
     * |        |          |Indicates that the data in the top of the non-periodic TxFIFO belongs to an endpoint other than the one for which the IN token was received
     * |        |          |This interrupt is asserted on the endpoint for which the IN token was received.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No IN Token Received with EP Mismatch interrupt
     * |        |          |0x1 (ACTIVE): IN Token Received with EP Mismatch interrupt
     * |[6]     |INEPNakEff|IN Endpoint NAK Effective (INEPNakEff)
     * |        |          |Applies to periodic IN endpoints only.
     * |        |          |This bit can be cleared when the application clears the IN endpoint NAK by writing to DIEPCTLn.CNAK.
     * |        |          |This interrupt indicates that the core has sampled the NAK bit
     * |        |          |Set (either by the application or by the core)
     * |        |          |The interrupt indicates that the IN endpoint NAK bit Set by the application has taken effect in the core.
     * |        |          |This interrupt does not guarantee that a NAK handshake is sent on the USB
     * |        |          |A STALL bit takes priority over a NAK bit.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Endpoint NAK Effective interrupt
     * |        |          |0x1 (ACTIVE): IN Endpoint NAK Effective interrupt
     * |[7]     |TxFEmp    |Transmit FIFO Empty (TxFEmp) (Read only)
     * |        |          |This bit is valid only for IN endpoints
     * |        |          |This interrupt is asserted when the TxFIFO for this endpoint is either half or completely empty
     * |        |          |The half or completely empty status is determined by the TxFIFO Empty Level bit in the Core AHB Configuration register (GAHBCFG.NPTxFEmpLvl)).
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Transmit FIFO Empty interrupt
     * |        |          |0x1 (ACTIVE): Transmit FIFO Empty interrupt
     * |[8]     |TxfifoUndrn|Fifo Underrun (TxfifoUndrn)
     * |        |          |Applies to IN endpoints Only
     * |        |          |This bit is valid only If thresholding is enabled
     * |        |          |The core generates this interrupt when it detects a transmit FIFO underrun condition for this endpoint.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Tx FIFO Underrun interrupt
     * |        |          |0x1 (ACTIVE): TxFIFO Underrun interrupt
     * |[9]     |BNAIntr   |BNA (Buffer Not Available) Interrupt (BNAIntr)
     * |        |          |The core generates this interrupt when the descriptor accessed is not ready for the Core to process, such as Host busy or DMA done.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No BNA interrupt
     * |        |          |0x1 (ACTIVE): BNA interrupt
     * |[12]    |BbleErr   |NAK Interrupt (BbleErr)
     * |        |          |The core generates this interrupt when babble is received for the endpoint.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No interrupt
     * |        |          |0x1 (ACTIVE): BbleErr interrupt
     * |[13]    |NAKIntrpt |NAK Interrupt (NAKInterrupt)
     * |        |          |The core generates this interrupt when a NAK is transmitted or received by the device
     * |        |          |In case of isochronous IN endpoints the interrupt gets generated when a zero length packet is transmitted due to un-availability of data in the TXFifo.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No NAK interrupt
     * |        |          |0x1 (ACTIVE): NAK Interrupt
     * |[14]    |NYETIntrpt|NYET Interrupt (NYETIntrpt)
     * |        |          |The core generates this interrupt when a NYET response is transmitted for a non isochronous OUT endpoint.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No NYET interrupt
     * |        |          |0x1 (ACTIVE): NYET Interrupt
     * @var HSUSBD_T::DIEPDMAn
     * Offset: 0x14  Device IN Endpoint n DMA Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DMAAddr   |Holds the start address of the external memory for storing or fetching endpoint data
     * |        |          |Note: For control endpoints, this field stores control OUT data packets as well as SETUP transaction data packets
     * |        |          |When more than three SETUP packets are received back-to-back, the SETUP data packet in the memory is overwritten.
     * |        |          |This register is incremented on every AHB transaction
     * |        |          |The application can give only a DWORD-aligned address.
     * |        |          |This field indicates the base pointer for the descriptor list.
     * @var HSUSBD_T::DTXFSTSn
     * Offset: 0x18  Device IN Endpoint Transmit FIFO Status Register n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |INEPTxFSpcAvail|IN Endpoint TxFIFO Space Avail (INEPTxFSpcAvail)
     * |        |          |Indicates the amount of free space available in the Endpoint TxFIFO.
     * |        |          |Values are in terms of 32-bit words.
     * |        |          |16'h0: Endpoint TxFIFO is full
     * |        |          |16'h1: 1 word available
     * |        |          |16'h2: 2 words available
     * |        |          |16'hn: n words available (where 0 n 32,768)
     * |        |          |16'h8000: 32,768 words available
     * |        |          |Others: Reserved
     * @var HSUSBD_T::DIEPDMABn
     * Offset: 0x1C  Device IN Endpoint n Buffer Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DMABufferAddr|Holds the current buffer address This register is updated as and when the data transfer for the corresponding end point is in progress
     */


    __IO uint32_t DIEPCTL;              /*!< [0x000] Device Control IN Endpoint n Control Register                    */
    __I  uint32_t RESERVE1[1];
    __IO uint32_t DIEPINT;              /*!< [0x008] Device IN Endpoint n Interrupt Register                          */
    __I  uint32_t RESERVE2[2];
    __IO uint32_t DIEPDMA;              /*!< [0x014] Device IN Endpoint n DMA Address Register                        */
    __I  uint32_t DTXFSTS;              /*!< [0x018] Device IN Endpoint Transmit FIFO Status Register n               */
    __I  uint32_t DIEPDMAB;             /*!< [0x01c] Device IN Endpoint n Buffer Address Register                     */

} HSUSBD_IEP_T;



/*----- OUT Endpoint 1~8 -----*/
typedef struct
{

    /**

     * @var HSUSBD_T::DOEPCTLn
     * Offset: 0x00  Device Control OUT Endpoint n Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |MPS       |Maximum Packet Size (MPS)Maximum Packet Size
     * |        |          |The application must program this field with the maximum packet size for the current logical endpoint
     * |        |          |This value is in bytes.
     * |[15]    |USBActEP  |USB Active Endpoint (USBActEP)USB Active Endpoint
     * |        |          |Indicates whether this endpoint is active in the current configuration and interface
     * |        |          |The core clears this bit for all endpoints (other than EP 0) after detecting a USB reset
     * |        |          |After receiving the SetConfiguration and SetInterface commands, the application must program endpoint registers accordingly and set this bit.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): Not Active
     * |        |          |0x1 (ENABLED): USB Active Endpoint
     * |[16]    |DPID      |Endpoint Data PID (DPID) (Read only)Endpoint Data PID (Read only)
     * |        |          |Applies to interrupt/bulk IN and OUT endpoints only.
     * |        |          |Contains the PID of the packet to be received or transmitted on this endpoint
     * |        |          |The application must program the PID of the first packet to be received or transmitted on this endpoint, after the endpoint is activated
     * |        |          |The applications use the SetD1PID and SetD0PID fields of this register to program either DATA0 or DATA1 PID.
     * |        |          |1'b0: DATA0
     * |        |          |1'b1: DATA1
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): Endpoint Data PID not active
     * |        |          |0x1 (ACTIVE): Endpoint Data PID active
     * |[17]    |NAKSts    |NAK Status (NAKSts) (Read only)NAK Status (Read only)
     * |        |          |Indicates the following:
     * |        |          |1'b0: The core is transmitting non-NAK handshakes based on the FIFO status.
     * |        |          |1'b1: The core is transmitting NAK handshakes on this endpoint.
     * |        |          |When either the application or the core sets this bit:
     * |        |          |The core stops receiving any data on an OUT endpoint, even if there is space in the RxFIFO to accommodate the incoming packet.
     * |        |          |For non-isochronous IN endpoints: The core stops transmitting any data on an IN endpoint, even if there data is available in the TxFIFO.
     * |        |          |For isochronous IN endpoints: The core sends out a zero-length data packet, even if there data is available in the TxFIFO.
     * |        |          |Irrespective of this bit's setting, the core always responds to SETUP data packets with an ACK handshake.
     * |        |          |Values:
     * |        |          |0x0 (NONNAK):
     * |        |          |The core is transmitting non-NAK handshakes based on the FIFO status
     * |        |          |0x1 (NAK):
     * |        |          |The core is transmitting NAK handshakes on this endpoint
     * |[19:18] |EPType    |Endpoint Type (EPType)Endpoint Type
     * |        |          |This is the transfer type supported by this logical endpoint.
     * |        |          |2'b00: Control
     * |        |          |2'b01: Isochronous
     * |        |          |2'b10: Bulk
     * |        |          |2'b11: Interrupt
     * |        |          |Values:
     * |        |          |0x0 (CONTROL): Control
     * |        |          |0x1 (ISOCHRONOUS): Isochronous
     * |        |          |0x2 (BULK): Bulk
     * |        |          |0x3 (INTERRUPT): Interrupt
     * |[20]    |Snp       |Reserved.
     * |[21]    |Stall     |STALL Handshake (Stall)STALL Handshake
     * |        |          |Applies to non-control, non-isochronous IN and OUT endpoints only.
     * |        |          |The application sets this bit to stall all tokens from the USB host to this endpoint
     * |        |          |If a NAK bit, Global Non-periodic IN NAK, or Global OUT NAK is set along with this bit, the STALL bit takes priority
     * |        |          |Only the application can clear this bit, never the core.
     * |        |          |Applies to control endpoints only.
     * |        |          |The application can only set this bit, and the core clears it, when a SETUP token is received for this endpoint
     * |        |          |If a NAK bit, Global Non-periodic IN NAK, or Global OUT NAK is set along with this bit, the STALL bit takes priority
     * |        |          |Irrespective of this bit's setting, the core always responds to SETUP data packets with an ACK handshake.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): STALL All non-active tokens
     * |        |          |0x1 (ACTIVE): STALL All Active Tokens
     * |[26]    |CNAK      |Clear NAK (CNAK)Clear NAK A write to this bit clears the NAK bit for the endpoint
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Clear NAK
     * |        |          |0x1 (ACTIVE): Clear NAK
     * |[27]    |SNAK      |Set NAK (SNAK)Set NAK
     * |        |          |A write to this bit sets the NAK bit for the endpoint.
     * |        |          |Using this bit, the application can control the transmission of NAK handshakes on an endpoint
     * |        |          |The core can also set this bit for an endpoint after a SETUP packet is received on that endpoint.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Set NAK
     * |        |          |0x1 (ACTIVE): Set NAK
     * |[28]    |SetD0PID  |Set DATA0 PID (SetD0PID)Set DATA0 PID
     * |        |          |Applies to interrupt/bulk IN and OUT endpoints only.
     * |        |          |Writing to this field sets the Endpoint Data PID (DPID) field in this register to DATA0.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): Disables Set DATA0 PID or Do not force Even Frame
     * |        |          |0x1 (ENABLED): Set Endpoint Data PID to DATA0 or Sets EO_FrNum field to odd (micro)Frame
     * |[29]    |SetD1PID  |Set DATA1 PID (SetD1PID)Set DATA1 PID
     * |        |          |Applies to interrupt and bulk IN and OUT endpoints only.
     * |        |          |Writing to this field sets the Endpoint Data PID (DPID) field in this register to DATA1.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): Disables Set DATA1 PID or Do not force Odd Frame
     * |        |          |0x1 (ENABLED): Set Endpoint Data PID to DATA1 or Sets EO_FrNum field to odd (micro)Frame
     * |[30]    |EPDis     |Endpoint Disable (EPDis)Endpoint Disable
     * |        |          |Applies to IN and OUT endpoints.
     * |        |          |The application sets this bit to stop transmitting/receiving data on an endpoint, even before the transfer for that endpoint is complete
     * |        |          |The application must wait for the Endpoint Disabled interrupt before treating the endpoint as disabled
     * |        |          |The core clears this bit before setting the Endpoint Disabled interrupt
     * |        |          |The application must set this bit only if Endpoint Enable is already set for this endpoint.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Action
     * |        |          |0x1 (ACTIVE): Disable Endpoint
     * |[31]    |EPEna     |Endpoint Enable (EPEna)Endpoint Enable
     * |        |          |Applies to IN and OUT endpoints.
     * |        |          |For IN endpoints this bit indicates that the descriptor structure and data buffer with data ready to transmit is setup.
     * |        |          |For OUT endpoint it indicates that the descriptor structure and data buffer to receive data is setup.
     * |        |          |The core clears this bit before setting any of the following interrupts on this endpoint:
     * |        |          |SETUP Phase Done
     * |        |          |Endpoint Disabled
     * |        |          |Transfer Completed
     * |        |          |Note: For control endpoints in DMA mode, this bit must be set for the controller to transfer SETUP data packets to the memory
     * |        |          |This bit will not be cleared on Transfer Completed interrupt of the SETUP packet.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Action
     * |        |          |0x1 (ACTIVE): Enable Endpoint
     * @var HSUSBD_T::DOEPINTn
     * Offset: 0x08  Device OUT Endpoint n Interrupt Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |XferCompl |Transfer Completed Interrupt (XferCompl) Transfer Completed Interrupt
     * |        |          |Applies to IN and OUT endpoints.
     * |        |          |When Scatter/Gather DMA mode is enabled
     * |        |          |For IN endpoint this field indicates that the requested data from the descriptor is moved from external system memory to internal FIFO.
     * |        |          |For OUT endpoint this field indicates that the requested data from the internal FIFO is moved to external system memory
     * |        |          |This interrupt is generated only when the corresponding endpoint descriptor is closed, and the IOC bit for the corresponding descriptor is Set.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Transfer Complete Interrupt
     * |        |          |0x1 (ACTIVE): Transfer Complete Interrupt
     * |[1]     |EPDisbld  |Endpoint Disabled Interrupt (EPDisbld)Endpoint Disabled Interrupt
     * |        |          |Applies to IN and OUT endpoints.
     * |        |          |This bit indicates that the endpoint is disabled per the application's request.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Endpoint Disabled Interrupt
     * |        |          |0x1 (ACTIVE): Endpoint Disabled Interrupt
     * |[2]     |AHBErr    |AHB Error (AHBErr)AHB Error
     * |        |          |Applies to IN and OUT endpoints.
     * |        |          |When there is an AHB error during an AHB read/write
     * |        |          |The application can read the corresponding endpoint DMA address register to get the error address.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No AHB Error Interrupt
     * |        |          |0x1 (ACTIVE): AHB Error interrupt
     * |[3]     |SetUp     |SETUP Phase Done (SetUp)SETUP Phase Done
     * |        |          |Applies to control OUT endpoints only.
     * |        |          |Indicates that the SETUP phase for the control endpoint is complete and no more back-to-back SETUP packets were received for the current control transfer
     * |        |          |On this interrupt, the application can decode the received SETUP data packet.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No SETUP Phase Done
     * |        |          |0x1 (ACTIVE): SETUP Phase Done
     * |[4]     |OUTTknEPdis|OUT Token Received When Endpoint Disabled (OUTTknEPdis)OUT Token Received When Endpoint Disabled
     * |        |          |Applies only to control OUT endpoints.
     * |        |          |Indicates that an OUT token was received when the endpoint was not yet enabled
     * |        |          |This interrupt is asserted on the endpoint for which the OUT token was received.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No OUT Token Received When Endpoint Disabled
     * |        |          |0x1 (ACTIVE): OUT Token Received When Endpoint Disabled
     * |[5]     |StsPhseRcvd|Status Phase Received for Control Write (StsPhseRcvd)Status Phase Received for Control Write
     * |        |          |This interrupt is valid only for Control OUT endpoints.
     * |        |          |This interrupt is generated only after the core has transferred all the data that the host has sent during the data phase of a control write transfer, to the system memory buffer.
     * |        |          |The interrupt indicates to the application that the host has switched from data phase to the status phase of a Control Write transfer
     * |        |          |The application can use this interrupt to ACK or STALL the Status phase, after it has decoded the data phase
     * |        |          |This is applicable only in Case of Scatter Gather DMA mode.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Status Phase Received for Control Write
     * |        |          |0x1 (ACTIVE): Status Phase Received for Control Write
     * |[6]     |Back2BackSETup|Back-to-Back SETUP Packets Received (Back2BackSETup)Back-to-Back SETUP Packets Received
     * |        |          |Applies to Control OUT endpoints only.
     * |        |          |This bit indicates that the core has received more than three back-to-back SETUP packets for this particular endpoint
     * |        |          |For information about handling this interrupt,
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Back-to-Back SETUP Packets Received
     * |        |          |0x1 (ACTIVE): Back-to-Back SETUP Packets Received
     * |[8]     |OutPktErr |OUT Packet Error (OutPktErr)OUT Packet Error
     * |        |          |Applies to OUT endpoints Only
     * |        |          |This interrupt is valid only when thresholding is enabled
     * |        |          |This interrupt is asserted when the core detects an overflow or a CRC error for non-Isochronous OUT packet.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No OUT Packet Error
     * |        |          |0x1 (ACTIVE): OUT Packet Error
     * |[9]     |BNAIntr   |BNA (Buffer Not Available) Interrupt (BNAIntr)Buffer Not Available Interrupt
     * |        |          |The core generates this interrupt when the descriptor accessed is not ready for the Core to process, such as Host busy or DMA done
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No BNA interrupt
     * |        |          |0x1 (ACTIVE): BNA interrupt
     * |[12]    |BbleErr   |NAK Interrupt (BbleErr)NAK Interrupt
     * |        |          |The core generates this interrupt when babble is received for the endpoint.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No BbleErr interrupt
     * |        |          |0x1 (ACTIVE): BbleErr interrupt
     * |[13]    |NAKIntrpt |NAK Interrupt (NAKInterrupt)NAK Interrupt
     * |        |          |The core generates this interrupt when a NAK is transmitted or received by the device.
     * |        |          |In case of isochronous IN endpoints the interrupt gets generated when a zero length packet is transmitted due to un-availability of data in the TXFifo.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No NAK interrupt
     * |        |          |0x1 (ACTIVE): NAK Interrupt
     * |[14]    |NYETIntrpt|NYET Interrupt (NYETIntrpt)NYET Interrupt
     * |        |          |The core generates this interrupt when a NYET response is transmitted for a non isochronous OUT endpoint.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No NYET interrupt
     * |        |          |0x1 (ACTIVE): NYET Interrupt
     * @var HSUSBD_T::DOEPDMAn
     * Offset: 0x14  Device OUT Endpoint n DMA Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DMAAddr   |Holds the start address of the external memory for storing or fetching endpoint data
     * |        |          |Note: For control endpoints, this field stores control OUT data packets as well as SETUP transaction data packets
     * |        |          |When more than three SETUP packets are received back-to-back, the SETUP data packet in the memory is overwritten.
     * |        |          |This register is incremented on every AHB transaction
     * |        |          |The application can give only a DWORD-aligned address
     * @var HSUSBD_T::DOEPDMABn
     * Offset: 0x1C  Device OUT Endpoint n Buffer Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DMABufferAddr|Holds the current buffer address This register is updated as and when the data transfer for the corresponding end point is in progress.
     */

    __IO uint32_t DOEPCTL;              /*!< [0x000] Device Control OUT Endpoint n Control Register                   */
    __I  uint32_t RESERVE1[1];
    __IO uint32_t DOEPINT;              /*!< [0x008] Device OUT Endpoint n Interrupt Register                         */
    __I  uint32_t RESERVE2[2];
    __IO uint32_t DOEPDMA;              /*!< [0x014] Device OUT Endpoint n DMA Address Register                       */
    __I  uint32_t RESERVE3[1];
    __I  uint32_t DOEPDMAB;             /*!< [0x01c] Device OUT Endpoint n Buffer Address Register                    */

} HSUSBD_OEP_T;


typedef struct
{


    /**
     * @var HSUSBD_T::GOTGCTL
     * Offset: 0x00  Control and Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[27]    |ChirpEn   |Mode: Device Only
     * |        |          |This bit when programmed to 1'b1 results in the core asserting chirp_on before sending an actual Chirp "K" signal on USB.
     * |        |          |0x0 (CHIRP_DISABLE): The controller does not assert chirp_on before sending an actual Chirp "K" signal on USB.
     * |        |          |0x1 (CHIRP_ENABLE): The controller asserts chirp_on before sending an actual Chirp "K" signal on USB.
     * |[31]    |Testmode_corr_eUSB2|UTMI IF correction for eUSB2 PHY during Test mode
     * |        |          |This bit is used to modify the behavior of UTMI 8-bit interface signals during test J and test K sequences when eUSB2 PHY is used.
     * |        |          |When this bit is set to 1'b1, the controller asserts utmi_txvalid and utmi_opmode in the same cycle during test J or test K sequence execution.
     * |        |          |Note: This bit is applicable only if eUSB2 PHY is used with 8-bit UTMI interface.
     * |        |          |0x0 (eUSB2_corr_disable): The controller asserts utmi_txvalid one cycle later than utmi_opmode.
     * |        |          |0x1 (eUSB2_corr_enable): The controller asserts utmi_txvalid and utmi_opmode in the same cycle.
     * @var HSUSBD_T::GAHBCFG
     * Offset: 0x08  AHB Configuration Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |GlblIntrMsk|Global Interrupt Mask (GlblIntrMsk)
     * |        |          |The application uses this bit to mask or unmask the interrupt line assertion to itself
     * |        |          |Irrespective of this bit's setting, the interrupt status registers are updated by the controller.
     * |        |          |1'b0: Mask the interrupt assertion to the application.
     * |        |          |1'b1: Unmask the interrupt assertion to the application.
     * |        |          |Values:
     * |        |          |0x0 (MASK): Mask the interrupt assertion to the application
     * |        |          |0x1 (NOMASK): Unmask the interrupt assertion to the application.
     * |[4:1]   |HBstLen   |Burst Length/Type (HBstLen)
     * |        |          |Internal DMA Mode AHB Master burst type:
     * |        |          |4'b0000 Single
     * |        |          |4'b0001 INCR
     * |        |          |4'b0011 INCR4
     * |        |          |4'b0101 INCR8
     * |        |          |4'b0111 INCR16
     * |        |          |Others: Reserved
     * |        |          |Values:
     * |        |          |0x0 (WORD1ORSINGLE): 1 word or single
     * |        |          |0x1 (WORD4ORINCR): 4 words or INCR
     * |        |          |0x3 (WORD16ORINCR4): 16 words or INCR4
     * |        |          |0x5 (WORD64ORINCR8): 64 words or INCR8
     * |        |          |0x7 (WORD256ORINCR16): 256 words or INCR16
     * |[5]     |DMAEn     |DMA Enable (DMAEn)
     * |        |          |Reset: 1'b0
     * |        |          |Values:
     * |        |          |0x1 (DMAMODE): Core operates in a DMA mode
     * |[23]    |AHBSingle |AHB Single Support (AHBSingle)
     * |        |          |This bit when programmed supports Single transfers for the remaining data in a transfer when the core is operating in DMA mode.
     * |        |          |1'b0: The remaining data in the transfer is sent using INCR burst size.
     * |        |          |1'b1: The remaining data in the transfer is sent using Single burst size.
     * |        |          |Note: If this feature is enabled, the AHB RETRY and SPLIT transfers still have INCR burst type
     * |        |          |Enable this feature when the AHB Slave connected to the core does not support INCR burst (and when Split, and Retry transactions are not being used in the bus).
     * |        |          |Values:
     * |        |          |0x0 (INCRBURST): The remaining data in the transfer is sent using INCR burst size
     * |        |          |0x1 (SINGLEBURST): The remaining data in the transfer is sent using Single burst size
     * |[24]    |InvDescEndianess|Invert Descriptor Endianess (InvDescEndianess)
     * |        |          |1'b0: Descriptor Endianness is same as AHB Master Endianness.
     * |        |          |1'b1:
     * |        |          |If the AHB Master endianness is Big Endian, the Descriptor Endianness is Little Endian.
     * |        |          |If the AHB Master endianness is Little Endian, the Descriptor Endianness is Big Endian.
     * |        |          |Values:
     * |        |          |0x0 (DISABLE): Descriptor Endianness is same as AHB Master Endianness
     * |        |          |0x1 (ENABLE): Descriptor Endianness is opposite to AHB Master Endianness
     * @var HSUSBD_T::GUSBCFG
     * Offset: 0x0C  USB Configuration Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |TOutCal   |HS/FS Timeout Calibration (TOutCal)
     * |        |          |The number of PHY clocks that the application programs in this field is added to the high-speed/full-speed interpacket timeout duration in the core to account for any additional delays introduced by the PHY
     * |        |          |This can be required, because the delay introduced by the PHY in generating the linestate condition can vary from one PHY to another.
     * |        |          |The USB standard timeout value for high-speed operation is 736 to 816 (inclusive) bit times
     * |        |          |The USB standard timeout value for full-speed operation is 16 to 18 (inclusive) bit times
     * |        |          |The application must program this field based on the speed of enumeration
     * |        |          |The number of bit times added per PHY clock are as follows:
     * |        |          |High-speed operation:
     * |        |          |One 60- MHz PHY clock = 8 bit times.
     * |        |          |Full-speed operation:
     * |        |          |One 60- MHz PHY clock = 0.2 bit times.
     * |[13:10] |USBTrdTim |USB Turnaround Time (USBTrdTim)
     * |        |          |Sets the turnaround time in PHY clocks
     * |        |          |Specifies the response time for a MAC request to the Packet FIFO Controller (PFC) to fetch data from the DFIFO (Interanl Storage)
     * |        |          |This must be programmed to
     * |        |          |4'h9: When the MAC interface is 8-bit UTMI+ .
     * |        |          |Values:
     * |        |          |0x9 (TURNTIME8BIT): MAC interface is 8-bit UTMI+.
     * |[28]    |TxEndDelay|Tx End Delay (TxEndDelay)
     * |        |          |Writing 1'b1 to this bit enables the controller to follow the TxEndDelay timings as per UTMI+ specification 1.05 section 4.1.5 for opmode signal during remote wakeup.
     * |        |          |1'b0 : Normal Mode.
     * |        |          |1'b1 : Tx End delay.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): Normal Mode
     * |        |          |0x1 (ENABLED): Tx End delay
     * @var HSUSBD_T::GRSTCTL
     * Offset: 0x10  Reset Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CSftRst   |Core Soft Reset (CSftRst)
     * |        |          |Resets the hclk and phy_clock domains as follows:
     * |        |          |Clears the interrupts and all the CSR registers except the following register bits:
     * |        |          |GUSBCFG.TxEndDelay
     * |        |          |DCFG.DevSpd
     * |        |          |DCTL.SftDiscon
     * |        |          |All module state machines
     * |        |          |All module state machines (except the AHB Slave Unit) are reset to the IDLE state, and all the transmit FIFOs and the receive FIFO are flushed.
     * |        |          |Any transactions on the AHB Master are terminated as soon as possible, after gracefully completing the last data phase of an AHB transfer
     * |        |          |Any transactions on the USB are terminated immediately.
     * |        |          |The application can write to this bit any time it wants to reset the core
     * |        |          |This is a self-clearing bit and the core clears this bit after all the necessary logic is reset in the core, which can take several clocks, depending on the current state of the core
     * |        |          |Once this bit is cleared software must wait at least 3 PHY clocks before doing any access to the PHY domain (synchronization delay)
     * |        |          |Software must also must check that bit 31 of this register is 1 (AHB Master is IDLE) before starting any operation.
     * |        |          |Typically software reset is used during software development and also when you dynamically change the PHY selection bits in the USB configuration registers listed above
     * |        |          |When you change the PHY, the corresponding clock for the PHY is selected and used in the PHY domain
     * |        |          |Once a new clock is selected, the PHY domain has to be reset for proper operation.
     * |        |          |Values:
     * |        |          |0x0 (NOTACTIVE): No reset
     * |        |          |0x1 (ACTIVE): Resets hclk and phy_clock domains
     * |[1]     |PIUFSSftRst|PIU FS Dedicated Controller Soft Reset (PIUFSSftRst)
     * |        |          |Resets the PIU FS Dedicated Controller
     * |        |          |All module state machines in FS Dedicated Controller of PIU are reset to the IDLE state
     * |        |          |Used to reset the FS Dedicated controller in PIU in case of any PHY Errors like Loss of activity or Babble Error resulting in the PHY remaining in RX state for more than one frame boundary.
     * |        |          |This is a self clearing bit and core clears this bit after all the necessary logic is reset in the core.
     * |        |          |Values:
     * |        |          |0x0 (RESET_INACTIVE): No Reset
     * |        |          |0x1 (RESET_ACTIVE): PIU FS Dedicated Controller Soft Reset
     * |[4]     |RxFFlsh   |RxFIFO Flush (RxFFlsh)
     * |        |          |The application can flush the entire RxFIFO using this bit, but must first ensure that the core is not in the middle of a transaction.
     * |        |          |The application must only write to this bit after checking that the controller is neither reading from the RxFIFO nor writing to the RxFIFO.
     * |        |          |The application must wait until the bit is cleared before performing any other operations
     * |        |          |This bit requires eight clocks (slowest of PHY or AHB clock) to clear.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): Does not flush the entire RxFIFO
     * |        |          |0x1 (ACTIVE): Flushes the entire RxFIFO
     * |[5]     |TxFFlsh   |TxFIFO Flush (TxFFlsh)
     * |        |          |This bit selectively flushes a single or all transmit FIFOs, but cannot do so If the core is in the midst of a transaction.
     * |        |          |The application must write this bit only after checking that the core is neither writing to the TxFIFO nor reading from the TxFIFO.
     * |        |          |Verify using these registers:
     * |        |          |ReadNAK Effective Interrupt ensures the core is not reading from the FIFO
     * |        |          |WriteGRSTCTL.AHBIdle ensures the core is not writing anything to the FIFO.
     * |        |          |Flushing is normally recommended when FIFOs are reconfigured
     * |        |          |FIFO flushing is also recommended during device endpoint disable
     * |        |          |The application must wait until the core clears this bit before performing any operations
     * |        |          |This bit takes eight clocks to clear, using the slower clock of phy_clk or hclk.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Flush
     * |        |          |0x1 (ACTIVE): Selectively flushes a single or all transmit FIFOs
     * |[10:6]  |TxFNum    |TxFIFO Number (TxFNum)
     * |        |          |This is the FIFO number that must be flushed using the TxFIFO Flush bit
     * |        |          |This field must not be changed until the core clears the TxFIFO Flush bit.
     * |        |          |5'h0:
     * |        |          |Tx FIFO 0 flush in device mode when in dedicated FIFO mode
     * |        |          |5'h1:
     * |        |          |TXFIFO 1 flush in device mode when in dedicated FIFO mode
     * |        |          |5'h2:
     * |        |          |TXFIFO 2 flush in device mode when in dedicated FIFO mode
     * |        |          |...
     * |        |          |5'h8
     * |        |          |TXFIFO 8 flush in device mode when in dedicated FIFO mode
     * |        |          |5'h10: Flush all the transmit FIFOs
     * |        |          |Values:
     * |        |          |0x0 (TXF0): TXFIFO 0 flush in device mode when in dedicated FIFO mode
     * |        |          |0x1 (TXF1): TXFIFO 1 flush in device mode when in dedicated FIFO mode
     * |        |          |0x2 (TXF2): TXFIFO 2 flush in device mode when in dedicated FIFO mode
     * |        |          |0x3 (TXF3): TXFIFO 3 flush in device mode when in dedicated FIFO mode
     * |        |          |0x4 (TXF4): TXFIFO 4 flush in device mode when in dedicated FIFO mode
     * |        |          |0x5 (TXF5): TXFIFO 5 flush in device mode when in dedicated FIFO mode
     * |        |          |0x6 (TXF6): TXFIFO 6 flush in device mode when in dedicated FIFO mode
     * |        |          |0x7 (TXF7): TXFIFO 7 flush in device mode when in dedicated FIFO mode
     * |        |          |0x8 (TXF8): TXFIFO 8 flush in device mode when in dedicated FIFO mode
     * |        |          |0x10 (TXF16): Flush all the transmit FIFOs
     * |[31]    |AHBIdle   |AHB Master Idle (AHBIdle)(Read only)
     * |        |          |Indicates that the AHB Master State Machine is in the IDLE condition.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): Not Idle
     * |        |          |0x1 (ACTIVE): AHB Master Idle
     * @var HSUSBD_T::GINTSTS
     * Offset: 0x14  Interrupt Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3]     |Sof       |Start of (micro)Frame (Sof)
     * |        |          |In Device mode, the controller sets this bit to indicate that an SOF token has been received on the USB
     * |        |          |The application can read the Device Status register to get the current (micro)Frame number
     * |        |          |This interrupt is seen only when the core is operating at either HS or FS
     * |        |          |This bit can be set only by the core and the application must write 1 to clear it.
     * |        |          |Note: This register may return 1'b1 if read immediately after power-on reset
     * |        |          |If the register bit reads 1'b1 immediately after power-on reset, it does not indicate that an SOF has been received
     * |        |          |The read value of this interrupt is valid only after a valid connection between host and device is established
     * |        |          |If the bit is set after power on reset the application can clear the bit.
     * |        |          |Values:
     * |        |          |0x0 (INTACTIVE): No Start of Frame
     * |        |          |0x1 (ACTIVE): Start of Frame
     * |[4]     |RxFLvl    |RxFIFO Non-Empty (RxFLvl)(Read only)
     * |        |          |Indicates that there is at least one packet pending to be read from the RxFIFO.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): Rx Fifo is empty
     * |        |          |0x1 (ACTIVE): Rx Fifo is not empty
     * |[6]     |GINNakEff |Global IN Non-periodic NAK Effective (GINNakEff)(Read only)
     * |        |          |Indicates that the Set Global Non-periodic IN NAK bit in the Device Control register (DCTL.SGNPInNak) set by the application, has taken effect in the core
     * |        |          |That is, the core has sampled the Global IN NAK bit Set by the application
     * |        |          |This bit can be cleared by clearing the Clear Global Non-periodic IN NAK bit in the Device Control register (DCTL.CGNPInNak)
     * |        |          |This interrupt does not necessarily mean that a NAK handshake is sent out on the USB
     * |        |          |The STALL bit takes precedence over the NAK bit.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): Global Non-periodic IN NAK not active
     * |        |          |0x1 (ACTIVE): Set Global Non-periodic IN NAK bit
     * |[7]     |GOUTNakEff|Global OUT NAK Effective (GOUTNakEff)(Read only)
     * |        |          |Indicates that the Set Global OUT NAK bit in the Device Control register (DCTL.SGOUTNak), Set by the application, has taken effect in the core
     * |        |          |This bit can be cleared by writing the Clear Global OUT NAK bit in the Device Control register (DCTL.CGOUTNak).
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): Not Active
     * |        |          |0x1 (ACTIVE): Global OUT NAK Effective
     * |[10]    |ErlySusp  |Early Suspend (ErlySusp)
     * |        |          |The controller sets this bit to indicate that an Idle state has been detected on the USB for 3 ms.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Idle state detected
     * |        |          |0x1 (ACTIVE): 3ms of Idle state detected
     * |[11]    |USBSusp   |USB Suspend (USBSusp)
     * |        |          |The controller sets this bit to indicate that a suspend was detected on the USB
     * |        |          |The controller enters the Suspended state when there is no activity on the linestate signal for an extended period of time.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): Not Active
     * |        |          |0x1 (ACTIVE): USB Suspend
     * |[12]    |USBRst    |USB Reset (USBRst)
     * |        |          |The controller sets this bit to indicate that a reset is detected on the USB.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): Not active
     * |        |          |0x1 (ACTIVE): USB Reset
     * |[13]    |EnumDone  |Enumeration Done (EnumDone)
     * |        |          |The core sets this bit to indicate that speed enumeration is complete
     * |        |          |The application must read the Device Status (DSTS) register to obtain the enumerated speed.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): Not active
     * |        |          |0x1 (ACTIVE): Enumeration Done
     * |[14]    |ISOOutDrop|Isochronous OUT Packet Dropped Interrupt (ISOOutDrop)
     * |        |          |The controller sets this bit when it fails to write an isochronous OUT packet into the RxFIFO because the RxFIFO does not have enough space to accommodate a maximum packet size packet for the isochronous OUT endpoint.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): Not active
     * |        |          |0x1 (ACTIVE): Isochronous OUT Packet Dropped Interrupt
     * |[15]    |EOPF      |End of Periodic Frame Interrupt (EOPF)
     * |        |          |Indicates that the period specified in the Periodic Frame Interval field of the Device Configuration register (DCFG.PerFrInt) has been reached in the current microframe
     * |        |          |In case of Non-Ignore Frame Number Scatter/Gather (Descriptor DMA) mode, the controller internally handles the following scenarios based on EOPF:
     * |        |          |Read Flush: At the EOPF, the controller checks if there are any pending packets in the FIFO corresponding to the current (micro)Frame.
     * |        |          |If there are any pending packets, then the controller initiates read flush, due to which the read pointer is updated to the starting location of the next micro-frame packet.
     * |        |          |If there are no pending packets corresponding to the current (micro)Frame, the controller does not take any action.
     * |        |          |Write Flush: At the EOPF, if the controller is still fetching the current micro-frame data, then the controller stops pushing data into the TXFIFO but keeps fetching the complete packet from the System Memory
     * |        |          |After completing the scheduled packet size fetch, the controller updates the Status Quadlet Fields (Transmit Status to BUFFLUSH) and closes the Descriptor
     * |        |          |During the descriptor close, the controller initiates write flush, due to which the write pointer is updated to the starting location of the next micro-frame packet
     * |        |          |Because the controller stops pushing the packet to the TxFIFO after EOPF, to bring the write pointer to the starting location of the next micro-frame, write flush is done.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): Not active
     * |        |          |0x1 (ACTIVE): End of Periodic Frame Interrupt
     * |[18]    |IEPInt    |IN Endpoints Interrupt (IEPInt)(Read only)
     * |        |          |The core sets this bit to indicate that an interrupt is pending on one of the IN endpoints of the core
     * |        |          |The application must read the Device All Endpoints Interrupt (DAINT) register to determine the exact number of the IN endpoint on Device IN Endpoint-n Interrupt (DIEPINTn) register to determine the exact cause of the interrupt
     * |        |          |The application must clear the appropriate status bit in the corresponding DIEPINTn register to clear this bit.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): Not active
     * |        |          |0x1 (ACTIVE): IN Endpoints Interrupt
     * |[19]    |OEPInt    |OUT Endpoints Interrupt (OEPInt)(Read only)
     * |        |          |The controller sets this bit to indicate that an interrupt is pending on one of the OUT endpoints of the core
     * |        |          |The application must read the Device All Endpoints Interrupt (DAINT) register to determine the exact number of the OUT endpoint on which the interrupt occurred, and then read the corresponding Device OUT Endpoint-n Interrupt (DOEPINTn) register to determine the exact cause of the interrupt
     * |        |          |The application must clear the appropriate status bit in the corresponding DOEPINTn register to clear this bit.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): Not active
     * |        |          |0x1 (ACTIVE): OUT Endpoints Interrupt
     * |[22]    |FetSusp   |Data Fetch Suspended (FetSusp)
     * |        |          |This interrupt indicates that the core has stopped fetching data
     * |        |          |For IN endpoints due to the unavailability of TxFIFO space or Request Queue space
     * |        |          |This interrupt is used by the application for an endpoint mismatch algorithm.
     * |        |          |For example, after detecting an endpoint mismatch, the application:
     * |        |          |Sets a Global non-periodic IN NAK handshake
     * |        |          |Disables IN endpoints
     * |        |          |Flushes the FIFO
     * |        |          |Determines the token sequence from the IN Token Sequence Learning Queue
     * |        |          |Re-enables the endpoints
     * |        |          |Clears the Global non-periodic IN NAK handshake
     * |        |          |If the Global non-periodic IN NAK is cleared, the core has not yet fetched data for the IN endpoint, and the IN token is received
     * |        |          |The core generates an 'IN token received when FIFO empty' interrupt
     * |        |          |It then sends the host a NAK response
     * |        |          |To avoid this scenario, the application can check the GINTSTS.FetSusp interrupt, which ensures that the FIFO is full before clearing a Global NAK handshake.
     * |        |          |Alternatively, the application can mask the IN token received when FIFO empty interrupt when clearing a Global IN NAK handshake.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): Not active
     * |        |          |0x1 (ACTIVE): Data Fetch Suspended
     * |[23]    |ResetDet  |Reset detected Interrupt (ResetDet)
     * |        |          |In Device mode, this interrupt is asserted when a reset is detected on the USB in partial power-down mode when the device is in Suspend.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): Not active
     * |        |          |0x1 (ACTIVE): Reset detected Interrupt
     * |[27]    |LPM_Int   |LPM Transaction Received Interrupt
     * |        |          |(LPM_Int) This interrupt is asserted when the device receives an LPM transaction and responds with a non-ERRORed response has completed LPM transactions for the programmed number of times (GLPMCFG.RetryCnt)
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): Not Active
     * |        |          |0x1 (ACTIVE): LPM Transaction Received Interrupt
     * |[31]    |WkUpInt   |Resume/Remote Wakeup Detected Interrupt (WkUpInt)
     * |        |          |Wakeup Interrupt during Suspend(L2) or LPM(L1) state.
     * |        |          |During Suspend(L2):
     * |        |          |This interrupt is asserted only when Host Initiated Resume is detected on USB.
     * |        |          |During LPM(L1):
     * |        |          |This interrupt is asserted for either Host Initiated Resume or Device Initiated Remote Wakeup on USB.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): Not active
     * |        |          |0x1 (ACTIVE): Resume or Remote Wakeup Detected Interrupt
     * @var HSUSBD_T::GINTMSK
     * Offset: 0x18  Interrupt Mask Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2]     |OTGIntMsk |OTG Interrupt Mask (OTGIntMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): OTG Interrupt Mask
     * |        |          |0x1 (NOMASK): No OTG Interrupt Mask
     * |[3]     |SofMsk    |Start of (micro) Frame Mask (SofMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Start of Frame Mask
     * |        |          |0x1 (NOMASK): No Start of Frame Mask
     * |[4]     |RxFLvlMsk |Receive FIFO Non-Empty Mask (RxFLvlMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Receive FIFO Non-Empty Mask
     * |        |          |0x1 (NOMASK): No Receive FIFO Non-Empty Mask
     * |[6]     |GINNakEffMsk|Global Non-periodic IN NAK Effective Mask (GINNakEffMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Global Non-periodic IN NAK Effective Mask
     * |        |          |0x1 (NOMASK): No Global Non-periodic IN NAK Effective Mask
     * |[7]     |GOUTNakEffMsk|Global OUT NAK Effective Mask (GOUTNakEffMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Global OUT NAK Effective Mask
     * |        |          |0x1 (NOMASK): No Global OUT NAK Effective Mask
     * |[10]    |ErlySuspMsk|Early Suspend Mask (ErlySuspMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Early Suspend Mask
     * |        |          |0x1 (NOMASK): No Early Suspend Mask
     * |[11]    |USBSuspMsk|USB Suspend Mask (USBSuspMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): USB Suspend Mask
     * |        |          |0x1 (NOMASK): No USB Suspend Mask
     * |[12]    |USBRstMsk |USB Reset Mask (USBRstMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): USB Reset Mask
     * |        |          |0x1 (NOMASK): No USB Reset Mask
     * |[13]    |EnumDoneMsk|Enumeration Done Mask (EnumDoneMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Enumeration Done Mask
     * |        |          |0x1 (NOMASK): No Enumeration Done Mask
     * |[14]    |ISOOutDropMsk|Isochronous OUT Packet Dropped Interrupt Mask (ISOOutDropMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Isochronous OUT Packet Dropped Interrupt Mask
     * |        |          |0x1 (NOMASK): No Isochronous OUT Packet Dropped Interrupt Mask
     * |[15]    |EOPFMsk   |End of Periodic Frame Interrupt Mask (EOPFMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): End of Periodic Frame Interrupt Mask
     * |        |          |0x1 (NOMASK): No End of Periodic Frame Interrupt Mask
     * |[17]    |EPMisMsk  |Endpoint Mismatch Interrupt Mask (EPMisMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Endpoint Mismatch Interrupt Mask
     * |        |          |0x1 (NOMASK): No Endpoint Mismatch Interrupt Mask
     * |[18]    |IEPIntMsk |IN Endpoints Interrupt Mask (IEPIntMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): IN Endpoints Interrupt Mask
     * |        |          |0x1 (NOMASK): No IN Endpoints Interrupt Mask
     * |[19]    |OEPIntMsk |OUT Endpoints Interrupt Mask (OEPIntMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): OUT Endpoints Interrupt Mask
     * |        |          |0x1 (NOMASK): No OUT Endpoints Interrupt Mask
     * |[22]    |FetSuspMsk|Data Fetch Suspended Mask (FetSuspMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Data Fetch Suspended Mask
     * |        |          |0x1 (NOMASK): No Data Fetch Suspended Mask
     * |[23]    |ResetDetMsk|Reset detected Interrupt Mask (ResetDetMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Reset detected Interrupt Mask
     * |        |          |0x1 (NOMASK): No Reset detected Interrupt Mask
     * |[27]    |LPM_IntMsk|LPM Transaction Received Interrupt (LPM_Int)
     * |        |          |LPM Transaction received interrupt Mask
     * |        |          |Values:
     * |        |          |0x0 (MASK): LPM Transaction received interrupt Mask
     * |        |          |0x1 (NOMASK): No LPM Transaction received interrupt Mask
     * |[31]    |WkUpIntMsk|Resume/Remote Wakeup Detected Interrupt Mask (WkUpIntMsk)
     * |        |          |The WakeUp bit is used for LPM state wake up in a way similar to that of wake up in suspend state.
     * |        |          |Values:
     * |        |          |0x0 (MASK): Resume or Remote Wakeup Detected Interrupt Mask
     * |        |          |0x1 (NOMASK): Unmask Resume Remote Wakeup Detected Interrupt
     * @var HSUSBD_T::GRXSTSR
     * Offset: 0x1C  Receive Status Debug Read Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |EPNum     |Endpoint Number (EPNum)
     * |        |          |Indicates the endpoint number to which the current received packet belongs.
     * |[14:4]  |BCnt      |Byte Count (BCnt)
     * |        |          |indicates the byte count of the received data packet.
     * |[16:15] |DPID      |Data PID
     * |        |          |I (DPID) indicates the Data PID of the received OUT data packet
     * |        |          |2'b00: DATA0
     * |        |          |2'b10: DATA1
     * |        |          |2'b01: DATA2
     * |        |          |2'b11: MDATA
     * |        |          |Reset: 2'h0
     * |        |          |Values:
     * |        |          |0x0 (DATA0): DATA0
     * |        |          |0x2 (DATA1): DATA1
     * |        |          |0x1 (DATA2): DATA2
     * |        |          |0x3 (MDATA): MDATA
     * |[20:17] |PktSts    |Packet Status
     * |        |          |I(PktSts) indicates the status of the received packet
     * |        |          |4'b0001: Global OUT NAK (triggers an interrupt)
     * |        |          |4'b0010: OUT data packet received
     * |        |          |4'b0011: OUT transfer completed (triggers an interrupt)
     * |        |          |4'b0100: SETUP transaction completed (triggers an interrupt)
     * |        |          |4'b0110: SETUP data packet received
     * |        |          |Others: Reserved
     * |        |          |Reset:4'h0
     * |        |          |Values:
     * |        |          |0x1 (OUTNAK): Global OUT NAK (triggers an interrupt)
     * |        |          |0x2 (INOUTDPRX): OUT data packet received
     * |        |          |0x3 (INOUTTRCOM): IN or OUT transfer completed (triggers an interrupt)
     * |        |          |0x4 (DSETUPCOM): SETUP transaction completed (triggers an interrupt)
     * |        |          |0x6 (DSETUPRX): SETUP data packet received
     * |[24:21] |FN        |Frame Number
     * |        |          |(FN)
     * |        |          |This is the least significant 4 bits of the (micro)Frame number in which the packet is received on the USB
     * |        |          |This field is supported only when isochronous OUT endpoints are supported.
     * @var HSUSBD_T::GRXSTSP
     * Offset: 0x20  Receive Status Read/Pop Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |EPNum     |Endpoint Number (EPNum)
     * |        |          |Indicates the endpoint number to which the current received packet belongs.
     * |        |          |Values:
     * |        |          |0x0 (CHEP0): Channel or EndPoint 0
     * |        |          |0x1 (CHEP1): Channel or EndPoint 1
     * |        |          |0x2 (CHEP2): Channel or EndPoint 2
     * |        |          |0x3 (CHEP3): Channel or EndPoint 3
     * |        |          |0x4 (CHEP4): Channel or EndPoint 4
     * |        |          |0x5 (CHEP5): Channel or EndPoint 5
     * |        |          |0x6 (CHEP6): Channel or EndPoint 6
     * |        |          |0x7 (CHEP7): Channel or EndPoint 7
     * |        |          |0x8 (CHEP8): Channel or EndPoint 8
     * |[14:4]  |BCnt      |Byte Count
     * |        |          |(BCnt)
     * |        |          |indicates the byte count of the received data packet.
     * |[16:15] |DPID      |Data PID (DPID)
     * |        |          |iIndicates the Data PID of the received OUT data packet
     * |        |          |2'b00: DATA0
     * |        |          |2'b10: DATA1
     * |        |          |2'b01: DATA2
     * |        |          |2'b11: MDATA
     * |        |          |Reset: 2'h0
     * |        |          |Values:
     * |        |          |0x0 (DATA0): DATA0
     * |        |          |0x2 (DATA1): DATA1
     * |        |          |0x1 (DATA2): DATA2
     * |        |          |0x3 (MDATA): MDATA
     * |[20:17] |PktSts    |Packet Status (PktSts)
     * |        |          |iIndicates the status of the received packet
     * |        |          |4'b0001: Global OUT NAK (triggers an interrupt)
     * |        |          |4'b0010: OUT data packet received
     * |        |          |4'b0011: OUT transfer completed (triggers an interrupt)
     * |        |          |4'b0100: SETUP transaction completed (triggers an interrupt)
     * |        |          |4'b0110: SETUP data packet received
     * |        |          |Others: Reserved
     * |        |          |Reset:4'h0
     * |        |          |Values:
     * |        |          |0x1 (OUTNAK): Global OUT NAK (triggers an interrupt)
     * |        |          |0x2 (INOUTDPRX): OUT data packet received
     * |        |          |0x3 (INOUTTRCOM): IN or OUT transfer completed (triggers an interrupt)
     * |        |          |0x4 (DSETUPCOM): SETUP transaction completed (triggers an interrupt)
     * |[24:21] |FN        |Frame Number (FN)
     * |        |          |This is the least significant 4 bits of the (micro)Frame number in which the packet is received on the USB
     * |        |          |This field is supported only when isochronous OUT endpoints are supported.
     * @var HSUSBD_T::GRXFSIZ
     * Offset: 0x24  Receive FIFO Size Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[8:0]   |RxFDep    |RxFIFO Depth (RxFDep)
     * |        |          |This value is in terms of 32-bit words.
     * |        |          |Minimum value is 16
     * |        |          |Maximum value is 32,768
     * |        |          |The power-on reset value of this register is specified as the Largest Rx Data FIFO Depth.
     * |        |          |You can write a new value in this field. Programmed values must not exceed the power-on value.
     * @var HSUSBD_T::GNPTXFSIZ
     * Offset: 0x28  Non-periodic Transmit FIFO Size Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[8:0]   |INEPTxF0StAddr|IN Endpoint FIFO0 Transmit RAM Start Address(INEPTxF0StAddr)
     * |        |          |This field contains the memory start address for IN Endpoint Transmit FIFO# 0.
     * |        |          |Programmed values must not exceed the power-on value.
     * |[21:16] |INEPTxF0Dep|IN Endpoint TxFIFO 0 Depth (INEPTxF0Dep)
     * |        |          |This value is in terms of 32-bit words.
     * |        |          |Minimum value is 16
     * |        |          |Maximum value is 32,768
     * |        |          |The application can write a new value in this field
     * |        |          |The power-on reset value of this field is specified as Largest IN Endpoint FIFO 0 Depth.
     * @var HSUSBD_T::GLPMCFG
     * Offset: 0x54  LPM Config Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |LPMCap    |LPM-Capable (LPMCap)
     * |        |          |The application uses this bit to control the controller LPM capabilities
     * |        |          |If the core operates as a non-LPM-capable device, it cannot respond to any LPM transactions
     * |        |          |If GLPMCFG.LPMCap is 1'b0, the software must not set any of the remaining fields in the GLPMCFG register and these fields should hold their Reset values.
     * |        |          |1'b0: LPM capability is not enabled.
     * |        |          |1'b1: LPM capability is enabled.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): LPM capability is not enabled
     * |        |          |0x1 (ENABLED): LPM capability is enabled
     * |[1]     |AppL1Res  |LPM response programmed by application (AppL1Res)
     * |        |          |Handshake response to LPM token pre-programmed by device application software
     * |        |          |The response depends on GLPMCFG.LPMCap
     * |        |          |If GLPMCFG.LPMCap is 1'b0, the core operates as a non-LPM-capable Device and does not respond to any LPM transactions
     * |        |          |If GLPMCFG.LPMCap is 1'b1, the core responds as follows:
     * |        |          |1: ACK
     * |        |          |Even though an ACK is pre-programmed, the core responds with an ACK only on a successful LPM transaction
     * |        |          |The LPM transaction is successful if:
     * |        |          |There are no PID/CRC5 errors in both the EXT token and the LPM token (else ERROR)
     * |        |          |A valid bLinkState = 0001B (L1) is received in the LPM transaction (else STALL).
     * |        |          |No data is pending in the Transmit queue (else NYET)
     * |        |          |0: NYET
     * |        |          |The pre-programmed software bit is overridden for response to LPM token when:
     * |        |          |The received bLinkState is not L1 (STALL response)
     * |        |          |An error is detected in either of the LPM token packets due to corruption (ERROR response).
     * |        |          |Values:
     * |        |          |0x0 (NYET_RESP): The core responds with a NYET when an error is detected in either of the LPM token packets due to corruption
     * |        |          |0x1 (ACK_RESP): The core responds with an ACK only on a successful LPM transaction
     * |[5:2]   |HIRD      |Host-Initiated Resume Duration (HIRD) (Read only)
     * |        |          |EnBESL = 1'b0.
     * |        |          |Host Initiated Resume Duration
     * |        |          |This field is read only and is updated with the Received LPM Token HIRD bmAttribute when an ACK/NYET/STALL response is sent to an LPM transaction
     * |        |          |If HIRD[3:0],
     * |        |          |4'b0000, THIRD(us) = 50.
     * |        |          |4'b0001, THIRD(us) = 125.
     * |        |          |4'b0010, THIRD(us) = 200.
     * |        |          |4'b0011, THIRD(us) = 275.
     * |        |          |4'b0100, THIRD(us) = 350.
     * |        |          |4'b0101, THIRD(us) = 425.
     * |        |          |4'b0110, THIRD(us) = 500.
     * |        |          |4'b0111, THIRD(us) = 575.
     * |        |          |4'b1000, THIRD(us) = 650.
     * |        |          |4'b1001, THIRD(us) = 725.
     * |        |          |4'b1010, THIRD(us) = 800.
     * |        |          |4'b1011, THIRD(us) = 875.
     * |        |          |4'b1100, THIRD(us) = 950.
     * |        |          |4'b1101, THIRD(us) = 1025.
     * |        |          |4'b1110, THIRD(us) = 1100.
     * |        |          |4'b1111, THIRD(us) = 1175.
     * |        |          |EnBESL = 1'b1.
     * |        |          |Best Effort Service Latency (BESL)
     * |        |          |This field is updated with the Received LPM Token BESL bmAttribute when an ACK/NYET/STALL response is sent to an LPM transaction
     * |        |          |If BESL[3:0],
     * |        |          |4'b0000, TBESL(us) = 125.
     * |        |          |4'b0001, TBESL(us) = 150.
     * |        |          |4'b0010, TBESL(us) = 200.
     * |        |          |4'b0011, TBESL(us) = 300.
     * |        |          |4'b0100, TBESL(us) = 400.
     * |        |          |4'b0101, TBESL(us) = 500.
     * |        |          |4'b0110, TBESL(us) = 1000.
     * |        |          |4'b0111, TBESL(us) = 2000.
     * |        |          |4'b1000, TBESL(us) = 3000.
     * |        |          |4'b1001, TBESL(us) = 4000.
     * |        |          |4'b1010, TBESL(us) = 5000.
     * |        |          |4'b1011, TBESL(us) = 6000.
     * |        |          |4'b1100, TBESL(us) = 7000.
     * |        |          |4'b1101, TBESL(us) = 8000.
     * |        |          |4'b1110, TBESL(us) = 9000.
     * |        |          |4'b1111, TBESL(us) = 10000.
     * |[6]     |bRemoteWake|RemoteWakeEnable (bRemoteWake)(Read only)
     * |        |          |This field is read only
     * |        |          |It is updated with the Received LPM Token bRemoteWake bmAttribute when an ACK/NYET/STALL response is sent to an LPM transaction.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): Remote Wakeup is disabled
     * |        |          |0x1 (ENABLED): In device mode, this field takes the value of remote wake up
     * |[7]     |EnblSlpM  |Enable utmi_sleep_n (EnblSlpM)
     * |        |          |The application uses this bit to control utmi_sleep_n assertion to the PHY in the L1 state.
     * |        |          |1'b0: utmi_sleep_n assertion from the core is not transferred to the external PHY.
     * |        |          |1'b1: utmi_sleep_n assertion from the core is transferred to the external PHY when utmi_l1_suspend_n cannot be asserted.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): utmi_sleep_n assertion from the core is not transferred to the external PHY
     * |        |          |0x1 (ENABLED): utmi_sleep_n assertion from the core is transferred to the external PHY when utmi_l1_suspend_n cannot be asserted
     * |[12:8]  |HIRD_Thres|BESL/HIRD Threshold (HIRD_Thres)
     * |        |          |EnBESL = 1'b0: The core puts the PHY into deep low power mode in L1 (by core asserting L1SuspendM) when HIRD value is greater than or equal to the value defined in this field HIRD_Thres[3:0] and HIRD_Thres[4] is set to 1b1.
     * |        |          |EnBESL = 1'b1: The core puts the PHY into deep low power mode in L1 (by core asserting L1SuspendM) when BESL value is greater than or equal to the value defined in this field BESL_Thres[3:0] and BESL_Thres [4] is set to 1'b1.
     * |        |          |DCTL.DeepSleepBESLReject = 1'b1: In device initiated resume, the core expects the Host to resume service to the device within the BESL value corresponding to L1 exit time specified in HIRD_Thres[3:0]
     * |        |          |The Device sends a NYET response when the received HIRD in LPM token is greater than HIRD threshold
     * |[14:13] |CoreL1Res |LPM Response (CoreL1Res) (Read only)
     * |        |          |The response of the core to LPM transaction received is reflected in these two bits.
     * |        |          |Values:
     * |        |          |0x0 (LPMRESP1): ERROR : No handshake response
     * |        |          |0x1 (LPMRESP2): STALL response
     * |        |          |0x2 (LPMRESP3): NYET response
     * |        |          |0x3 (LPMRESP4): ACK response
     * |[15]    |SlpSts    |Port Sleep Status (SlpSts) (Read only)
     * |        |          |This bit is set as long as a Sleep condition is present on the USB bus.
     * |        |          |The core enters the Sleep state when an ACK response is sent to an LPM transaction and the TL1TokenRetry timer has expired
     * |        |          |To stop the PHY clock, the application must set the Port Clock Stop bit, which asserts the PHY Suspend input signal
     * |        |          |The application must rely on SlpSts and not ACK in CoreL1Res to confirm transition into sleep.
     * |        |          |The core comes out of sleep:
     * |        |          |When there is any activity on the USB line_state
     * |        |          |When the application writes to the Remote Wakeup Signaling bit in the Device Control register (DCTL.RmtWkUpSig) or when the application resets or soft-disconnects the device.
     * |        |          |Values:
     * |        |          |0x0 (CORE_NOT_IN_L1): In Device mode, this bit indicates core is not in L1
     * |        |          |0x1 (CORE_IN_L1): In Device mode, the core enters the Sleep state when an ACK response is sent to an LPM transaction
     * |[16]    |L1ResumeOK|Sleep State Resume OK (L1ResumeOK)(Read only)
     * |        |          |Indicates that the application or host can start resume from Sleep state
     * |        |          |This bit is valid in LPM sleep (L1) state
     * |        |          |It is set in sleep mode after a delay of 50 micro sec (TL1Residency)
     * |        |          |The bit is reset when SlpSts is 0.
     * |        |          |1'b0: The application/core cannot start resume from Sleep state.
     * |        |          |1'b1: The application/core can start resume from Sleep state.
     * |        |          |Values:
     * |        |          |0x0 (NOTOK): The application/core cannot start Resume from Sleep state
     * |        |          |0x1 (OK): The application/core can start Resume from Sleep state
     * |[23:20] |LPM_Accept_Ctrl|Device Mode: LPM Accept Control (LPM_Accept_Ctrl)
     * |        |          |LPM_Accept_Ctrl[0]: The application can use this bit to accept an LPM token even if data is present in the Interrupt endpoint TxFIFO.
     * |        |          |1'b0: Reject (NYET) LPM token when data is present in the TxFIFO for Interrupt endpoints.
     * |        |          |1'b1: Accept(ACK) LPM token when data is present in the TxFIFO for Interrupt endpoints.
     * |        |          |Note: This bit is applicable only for Dedicated TxFIFO configurations (OTG_EN_DED_TX_FIFO=1).
     * |        |          |LPM_Accept_Ctrl[1]: The application can use this bit to reject an LPM token (NYET) between multiple stages of a single control transfer.
     * |        |          |1'b0: Accept(ACK) LPM token during Setup, Data, and Status stage of a control transfer.
     * |        |          |1'b1: Reject(NYET) LPM token during Setup, Data, and Status stage of a control transfer.
     * |        |          |LPM_Accept_Ctrl[2]: The application can use this bit to accept an LPM token even if data is present in the ISOC endpoint TxFIFO.
     * |        |          |1'b0: Reject (NYET) LPM token when data is present in the TxFIFO for ISOC endpoints.
     * |        |          |1'b1: Accept(ACK) LPM token when data is present in the TxFIFO for ISOC endpoints.
     * |        |          |Note: This bit is applicable only for Dedicated TxFIFO configurations (OTG_EN_DED_TX_FIFO=1).
     * |        |          |LPM_Accept_Ctrl[3]: The application can use this bit to accept an LPM token even if data is present in the BULK endpoint TxFIFO.
     * |        |          |1'b0: Reject (NYET) LPM token, when data is present in the TxFIFO for Bulk endpoints.
     * |        |          |1'b1: Accept(ACK) LPM token, when data is present in the TxFIFO for Bulk endpoints.
     * |        |          |Note: This bit is applicable only for Dedicated TxFIFO configurations (OTG_EN_DED_TX_FIFO=1).
     * |[28]    |LPM_EnBESL|LPM Enable BESL (LPM_EnBESL)
     * |        |          |This bit enables the BESL feature as defined in LPM Errata
     * |        |          |1'b0: The core works as per USB 2.0 Link Power Management Addendum Engineering Change Notice to the USB 2.0 specification as of July 16, 2007
     * |        |          |1'b1: The core works as per the LPM Errata
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): BESL is disabled
     * |        |          |0x1 (ENABLED): BESL is enabled as defined in LPM Errata
     * @var HSUSBD_T::GDFIFOCFG
     * Offset: 0x5C  Global DFIFO Configuration Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |GDFIFOCfg |GDFIFOCfg
     * |        |          |This field is for dynamic programming of the DFIFO Size
     * |        |          |This value takes effect only when the application programs a non zero value to this register
     * |        |          |The value programmed must conform to the guidelines described in 'FIFO RAM Allocation'
     * |        |          |The core does not have any corrective logic if the FIFO sizes are programmed incorrectly.
     * |        |          |Value After Reset: 0xc00
     * |[31:16] |EPInfoBaseAddr|EPInfoBaseAddr
     * |        |          |This field provides the start address of the EP info controller.
     * |        |          |Value After Reset: 0xbb8
     * @var HSUSBD_T::GREFCLK
     * Offset: 0x64  ref_clk Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |SOF_CNT_WKUP_ALERT|This bit indicates the number of SOF's after which the controller should generate an interrupt if the device had been in L1 state until that period
     * |        |          |The interrupt is used by software to initiate remote wakeup in the controller in order to sync to the uF number in the host
     * |[14]    |RefclkMode|This bit is used to enable or disable ref_clk mode of operation
     * |        |          |Note:
     * |        |          |The default value of this field is 'd0.
     * |        |          |When this field is disabled, DCTL.ServInt cannot be set to 1.
     * |        |          |Values:
     * |        |          |0x1 (ENABLE): Controller uses ref_clk to run internal micro-frame timers
     * |        |          |0x0 (DISABLE): Controller uses phy_clk to run internal micro-frame timers
     * |[31:15] |REFCLKPER |This bit indicates the period of ref_clk in terms of pico seconds
     * |        |          |Note:
     * |        |          |The default value of this field is 'd0.
     * |        |          |The period of ref_clk should be an integer multiple of 125us.
     * |        |          |The minimum frequency supported is 12 MHz.
     * |        |          |Other supported frequencies are 16, 17, 19.2, 20, 24, 30, and 40 MHz.
     * @var HSUSBD_T::GINTMSK2
     * Offset: 0x68  Interrupt Mask Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WkUpAlertIntMsk|Mode: Device
     * |        |          |Remote WakeUp Alert Interrupt Mask
     * |        |          |This interrupt is used to alert the application to initiate Remote WakeUp sequence.
     * |        |          |Values:
     * |        |          |0x0 (MASK): Mask Remote WakeUp Alert Interrupt
     * |        |          |0x1 (NOMASK): Unmask Remote WakeUp Alert Interrupt
     * @var HSUSBD_T::GINTSTS2
     * Offset: 0x6C  Interrupt Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WkUpAlertInt|Mode: Device
     * |        |          |Remote WakeUp Alert Interrupt Mask
     * |        |          |This interrupt is used to alert the application to initiate Remote WakeUp sequence.
     * |        |          |Values:
     * |        |          |&#8226; 0x0 (INACTIVE): Not Active
     * |        |          |&#8226; 0x1 (ACTIVE): Remote WakeUp Alert Interrupt detected
     * @var HSUSBD_T::DIEPTXF1
     * Offset: 0x104  Device IN Endpoint Transmit FIFO Size Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[8:0]   |INEPnTxFStAddr|IN Endpoint FIFOn Transmit RAM Start Address (INEPnTxFStAddr)
     * |        |          |This field contains the memory start address for IN endpoint Transmit FIFO
     * |        |          |The power-on reset value of this register is specified as the Largest Rx Data FIFO Depth
     * |[24:16] |INEPnTxFDep|IN Endpoint TxFIFO Depth (INEPnTxFDep)
     * |        |          |This value is in terms of 32-bit words.
     * |        |          |Minimum value is 16
     * |        |          |Maximum value is 32,768
     * |        |          |The power-on reset value of this register is specified as the Largest IN Endpoint FIFO number Depth.
     * |        |          |Programmed values must not exceed the power-on value.
     * @var HSUSBD_T::DIEPTXF2
     * Offset: 0x108  Device IN Endpoint Transmit FIFO Size Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |INEPnTxFStAddr|IN Endpoint FIFOn Transmit RAM Start Address (INEPnTxFStAddr)
     * |        |          |This field contains the memory start address for IN endpoint Transmit FIFO
     * |        |          |The power-on reset value of this register is specified as the Largest Rx Data FIFO Depth
     * |[24:16] |INEPnTxFDep|IN Endpoint TxFIFO Depth (INEPnTxFDep)
     * |        |          |This value is in terms of 32-bit words.
     * |        |          |Minimum value is 16
     * |        |          |Maximum value is 32,768
     * |        |          |The power-on reset value of this register is specified as the Largest IN Endpoint FIFO number Depth.
     * |        |          |Programmed values must not exceed the power-on value.
     * @var HSUSBD_T::DIEPTXF3
     * Offset: 0x10C  Device IN Endpoint Transmit FIFO Size Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |INEPnTxFStAddr|IN Endpoint FIFOn Transmit RAM Start Address (INEPnTxFStAddr)
     * |        |          |This field contains the memory start address for IN endpoint Transmit FIFO
     * |        |          |The power-on reset value of this register is specified as the Largest Rx Data FIFO Depth.
     * |        |          |Value After Reset: 0x320
     * |[15:10] |_         |Reserved.
     * |[24:16] |INEPnTxFDep|IN Endpoint TxFIFO Depth (INEPnTxFDep)
     * |        |          |This value is in terms of 32-bit words.
     * |        |          |Minimum value is 16
     * |        |          |Maximum value is 32,768
     * |        |          |The power-on reset value of this register is specified as the Largest IN Endpoint FIFO number Depth.
     * |        |          |Programmed values must not exceed the power-on value.
     * @var HSUSBD_T::DIEPTXF4
     * Offset: 0x110  Device IN Endpoint Transmit FIFO Size Register 4
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |INEPnTxFStAddr|IN Endpoint FIFOn Transmit RAM Start Address (INEPnTxFStAddr)
     * |        |          |This field contains the memory start address for IN endpoint Transmit FIFO
     * |        |          |The power-on reset value of this register is specified as the Largest Rx Data FIFO Depth
     * |[24:16] |INEPnTxFDep|IN Endpoint TxFIFO Depth (INEPnTxFDep)
     * |        |          |This value is in terms of 32-bit words.
     * |        |          |Minimum value is 16
     * |        |          |Maximum value is 32,768
     * |        |          |The power-on reset value of this register is specified as the Largest IN Endpoint FIFO number Depth.
     * |        |          |Programmed values must not exceed the power-on value
     * @var HSUSBD_T::DIEPTXF5
     * Offset: 0x114  Device IN Endpoint Transmit FIFO Size Register 5
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |INEPnTxFStAddr|IN Endpoint FIFOn Transmit RAM Start Address (INEPnTxFStAddr)
     * |        |          |This field contains the memory start address for IN endpoint Transmit FIFO
     * |        |          |The power-on reset value of this register is specified as the Largest Rx Data FIFO Depth
     * |[24:16] |INEPnTxFDep|IN Endpoint TxFIFO Depth (INEPnTxFDep)
     * |        |          |This value is in terms of 32-bit words.
     * |        |          |Minimum value is 16
     * |        |          |Maximum value is 32,768
     * |        |          |The power-on reset value of this register is specified as the Largest IN Endpoint FIFO number Depth.
     * |        |          |Programmed values must not exceed the power-on value.
     * @var HSUSBD_T::DIEPTXF6
     * Offset: 0x118  Device IN Endpoint Transmit FIFO Size Register 6
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |INEPnTxFStAddr|IN Endpoint FIFOn Transmit RAM Start Address (INEPnTxFStAddr)
     * |        |          |This field contains the memory start address for IN endpoint Transmit FIFO
     * |        |          |The power-on reset value of this register is specified as the Largest Rx Data FIFO Depth
     * |[24:16] |INEPnTxFDep|IN Endpoint TxFIFO Depth (INEPnTxFDep)
     * |        |          |This value is in terms of 32-bit words.
     * |        |          |Minimum value is 16
     * |        |          |Maximum value is 32,768
     * |        |          |The power-on reset value of this register is specified as the Largest IN Endpoint FIFO number Depth.
     * |        |          |Programmed values must not exceed the power-on value.
     * @var HSUSBD_T::DIEPTXF7
     * Offset: 0x11C  Device IN Endpoint Transmit FIFO Size Register 7
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |INEPnTxFStAddr|IN Endpoint FIFOn Transmit RAM Start Address (INEPnTxFStAddr)
     * |        |          |This field contains the memory start address for IN endpoint Transmit FIFO
     * |        |          |The power-on reset value of this register is specified as the Largest Rx Data FIFO Depth
     * |[24:16] |INEPnTxFDep|IN Endpoint TxFIFO Depth (INEPnTxFDep)
     * |        |          |This value is in terms of 32-bit words.
     * |        |          |Minimum value is 16
     * |        |          |Maximum value is 32,768
     * |        |          |The power-on reset value of this register is specified as the Largest IN Endpoint FIFO number Depth.
     * |        |          |Programmed values must not exceed the power-on value.
     * @var HSUSBD_T::DIEPTXF8
     * Offset: 0x120  Device IN Endpoint Transmit FIFO Size Register 8
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |INEPnTxFStAddr|IN Endpoint FIFOn Transmit RAM Start Address (INEPnTxFStAddr)
     * |        |          |This field contains the memory start address for IN endpoint Transmit FIFO
     * |        |          |The power-on reset value of this register is specified as the Largest Rx Data FIFO Depth
     * |[24:16] |INEPnTxFDep|IN Endpoint TxFIFO Depth (INEPnTxFDep)
     * |        |          |This value is in terms of 32-bit words.
     * |        |          |Minimum value is 16
     * |        |          |Maximum value is 32,768
     * |        |          |The power-on reset value of this register is specified as the Largest IN Endpoint FIFO number Depth.
     * |        |          |Programmed values must not exceed the power-on value.
     * @var HSUSBD_T::DCFG
     * Offset: 0x800  Device Configuration Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |DevSpd    |Device Speed (DevSpd)
     * |        |          |Indicates the speed at which the application requires the core to enumerate, or the maximum speed the application can support
     * |        |          |However, the actual bus speed is determined only after the connect sequence is completed, and is based on the speed of the USB host to which the core is connected.
     * |        |          |Values:
     * |        |          |0x0 (USBHS20): High speed USB 2.0
     * |        |          |0x1 (USBFS20): Full speed USB 2.0
     * |        |          |0x2 (Reserved0): Reserved
     * |        |          |0x3 (Reserved1): Reserved
     * |[2]     |NZStsOUTHShk|Non-Zero-Length Status OUT Handshake (NZStsOUTHShk)
     * |        |          |The application can use this field to select the handshake the core sends on receiving a nonzero-length data packet during the OUT transaction of a control transfer's Status stage.
     * |        |          |1'b1: Send a STALL handshake on a nonzero-length status OUT transaction and do not send the received OUT packet to the application.
     * |        |          |1'b0: Send the received OUT packet to the application (zerolength or nonzero-length) and send a handshake based on the NAK and STALL bits for the endpoint in the Device Endpoint Control register.
     * |        |          |Values:
     * |        |          |0x0 (SENDOUT):
     * |        |          |Send the received OUT packet to the application (zero-length or non-zero length) and send a handshake based on NAK and STALL bits for the endpoint in the Devce Endpoint Control Register
     * |        |          |0x1 (SENDSTALL):
     * |        |          |Send a STALL handshake on a nonzero-length status OUT transaction and do not send the received OUT packet to the application
     * |[10:4]  |DevAddr   |Device Address (DevAddr)
     * |        |          |The application must program this field after every SetAddress control command.
     * |[12:11] |PerFrInt  |Periodic Frame Interval (PerFrInt)
     * |        |          |Indicates the time within a (micro)Frame at which the application must be notified using the End Of Periodic Frame Interrupt
     * |        |          |This can be used to determine If all the isochronous traffic for that (micro)Frame is complete.
     * |        |          |2'b00: 80% of the (micro)Frame interval
     * |        |          |2'b01: 85% of the (micro)Frame interval
     * |        |          |2'b10: 90% of the (micro)Frame interval
     * |        |          |2'b11: 95% of the (micro)Frame interval
     * |        |          |Values:
     * |        |          |0x0 (EOPF80): 80% of the (micro)Frame interval
     * |        |          |0x1 (EOPF85): 85% of the (micro)Frame interval
     * |        |          |0x2 (EOPF90): 90% of the (micro)Frame interval
     * |        |          |0x3 (EOPF95): 95% of the (micro)Frame interval
     * |[13]    |EnDevOutNak|Enable Device OUT NAK (EnDevOutNak)
     * |        |          |This bit enables setting NAK for Bulk OUT endpoints after the transfer is completed for Device mode Descriptor DMA
     * |        |          |1'b0 : The core does not set NAK after Bulk OUT transfer complete
     * |        |          |1'b1 : The core sets NAK after Bulk OUT transfer complete
     * |        |          |This bit is one time programmable after reset like any other DCFG register bits.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED):
     * |        |          |The core does not set NAK after Bulk OUT transfer complete
     * |        |          |0x1 (ENABLED): The core sets NAK after Bulk OUT transfer complete
     * |[14]    |XCVRDLY   |XCVRDLY
     * |        |          |Enables or disables delay between xcvr_sel and txvalid during device chirp
     * |        |          |Values:
     * |        |          |0x0 (DISABLE): No delay between xcvr_sel and txvalid during Device chirp
     * |        |          |0x1 (ENABLE): Enable delay between xcvr_sel and txvalid during Device chirp
     * |[15]    |ErraticIntMsk|Erratic Error Interrupt Mask
     * |        |          |Values:
     * |        |          |0x0 (NOMASK): Early suspend interrupt is generated on erratic error
     * |        |          |0x1 (MASK): Mask early suspend interrupt on erratic error
     * |[17]    |ipgisocSupt|Worst-Case Inter-Packet Gap ISOC OUT Support (ipgisocSupt)
     * |        |          |This bit indicates that the controller supports the worst-case scenario of Rx followed by Rx Inter Packet Gap (IPG) (32 bit times) as per the UTMI Specification for any token following an ISOC OUT token
     * |        |          |Without this support, when any token follows an ISOC OUT token with the worst-case IPG, the controller will not detect the followed token
     * |        |          |The worst-case IPG of the controller without this support depends on the AHB and PHY Clock frequency.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): Worst-Case Inter-Packet Gap ISOC OUT Support is disabled
     * |        |          |0x1 (ENABLED): Worst-Case Inter-Packet Gap ISOC OUT Support is enabled
     * |[23]    |DescDMA   |Enable Scatter/gather DMA in device mode (DescDMA)
     * |        |          |The application can Set this bit during initialization to enable the Scatter/Gather DMA operation.
     * |        |          |Note: This bit must be modified only once after a reset
     * |        |          |The following combinations are available for programming:
     * |        |          |GAHBCFG.DMAEn=0,DCFG.DescDMA=0 => Invalid.
     * |        |          |GAHBCFG.DMAEn=0,DCFG.DescDMA=1 => Invalid.
     * |        |          |GAHBCFG.DMAEn=1,DCFG.DescDMA=0 => Invalid.
     * |        |          |GAHBCFG.DMAEn=1,DCFG.DescDMA=1 => Scatter/Gather DMA mode.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): Disable Scatter/Gather DMA
     * |        |          |0x1 (ENABLED): Enable Scatter/Gather DMA
     * |[25:24] |PerSchIntvl|Periodic Scheduling Interval (PerSchIntvl)
     * |        |          |PerSchIntvl must be programmed for Scatter/Gather DMA mode.
     * |        |          |This field specifies the amount of time the Internal DMA engine must allocate for fetching periodic IN endpoint data
     * |        |          |Based on the number of periodic endpoints, this value must be specified as 25,50 or 75% of (micro)Frame.
     * |        |          |When any periodic endpoints are active, the internal DMA engine allocates the specified amount of time in fetching periodic IN endpoint data .
     * |        |          |When no periodic endpoints are active, Then the internal DMA engine services non-periodic endpoints, ignoring this field.
     * |        |          |After the specified time within a (micro)Frame, the DMA switches to fetching for non-periodic endpoints.
     * |        |          |2'b00: 25% of (micro)Frame.
     * |        |          |2'b01: 50% of (micro)Frame.
     * |        |          |2'b10: 75% of (micro)Frame.
     * |        |          |2'b11: Reserved.
     * |        |          |Reset: 2'b00
     * |        |          |Values:
     * |        |          |0x0 (MF25): 25% of (micro)Frame
     * |        |          |0x1 (MF50): 50% of (micro)Frame
     * |        |          |0x2 (MF75): 75% of (micro)Frame
     * |        |          |0x3 (RESERVED): Reserved
     * |[31:26] |ResValid  |Resume Validation Period (ResValid)
     * |        |          |This field is effective only when DCFG.Ena32 kHzSusp is set
     * |        |          |It controls the resume period when the core resumes from suspend
     * |        |          |The core counts for ResValid number of clock cycles to detect a valid resume when this bit is set
     * @var HSUSBD_T::DCTL
     * Offset: 0x804  Device Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RmtWkUpSig|Remote Wakeup Signaling (RmtWkUpSig)
     * |        |          |When the application sets this bit, the core initiates remote signaling to wake up the USB host
     * |        |          |The application must Set this bit to instruct the core to exit the Suspend state
     * |        |          |As specified in the USB 2.0 specification, the application must clear this bit 1-15 ms after setting it.
     * |        |          |If LPM is enabled and the core is in the L1 (Sleep) state, when the application sets this bit, the core initiates L1 remote signaling to wake up the USB host
     * |        |          |The application must set this bit to instruct the core to exit the Sleep state
     * |        |          |As specified in the LPM specification, the hardware automatically clears this bit 50 microseconds (TL1DevDrvResume) after being set by the application
     * |        |          |The application must not set this bit when GLPMCFG bRemoteWake from the previous LPM transaction is zero.
     * |        |          |Values:
     * |        |          |0x0 (DISABLEDRMWKUP): Core does not send Remote Wakeup Signaling
     * |        |          |0x1 (ENABLERMWKUP): Core sends Remote Wakeup Signaling
     * |[1]     |SftDiscon |Soft Disconnect (SftDiscon)
     * |        |          |The application uses this bit to signal the controller to do a soft disconnect
     * |        |          |As long as this bit is set, the host does not see that the device is connected, and the device does not receive signals on the USB
     * |        |          |The core stays in the disconnected state until the application clears this bit.
     * |        |          |1'b0: Normal operation
     * |        |          |When this bit is cleared after a soft disconnect, the core drives the phy_opmode_o signal on the UTMI+ to 2'b00, which generates a device connect event to the USB host
     * |        |          |When the device is reconnected, the USB host restarts device enumeration.
     * |        |          |1'b1: The core drives the phy_opmode_o signal on the UTMI+ to 2'b01, which generates a device disconnect event to the USB host.
     * |        |          |Note:
     * |        |          |This bit can be also used for ULPI/FS Serial interfaces.
     * |        |          |This bit is not impacted by a soft reset.
     * |        |          |Values:
     * |        |          |0x0 (NODISCONNECT): The core drives the phy_opmode_o signal on the UTMI+ to 2'b00, which generates a device connect event to the USB host
     * |        |          |0x1 (DISCONNECT): The core drives the phy_opmode_o signal on the UTMI+ to 2'b01, which generates a device disconnect event to the USB host
     * |[2]     |GNPINNakSts|Global Non-periodic IN NAK Status (GNPINNakSts) (Read only)
     * |        |          |1'b0: A handshake is sent out based on the data availability in the transmit FIFO.
     * |        |          |1'b1: A NAK handshake is sent out on all non-periodic IN endpoints, irrespective of the data availability in the transmit FIFO.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): A handshake is sent out based on the data availability in the transmit FIFO
     * |        |          |0x1 (ACTIVE): A NAK handshake is sent out on all non-periodic IN endpoints, irrespective of the data availability in the transmit FIFO
     * |[3]     |GOUTNakSts|Global OUT NAK Status (GOUTNakSts) (Read only)
     * |        |          |1'b0: A handshake is sent based on the FIFO Status and the NAK and STALL bit settings.
     * |        |          |1'b1: No data is written to the RxFIFO, irrespective of space availability
     * |        |          |Sends a NAK handshake on all packets, except on SETUP transactions
     * |        |          |All isochronous OUT packets are dropped.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): A handshake is sent based on the FIFO Status and the NAK and STALL bit settings.
     * |        |          |0x1 (ACTIVE): No data is written to the RxFIFO, irrespective of space availability
     * |        |          |Sends a NAK handshake on all packets, except on SETUP transactions
     * |        |          |All isochronous OUT packets are dropped
     * |[6:4]   |TstCtl    |Test Control (TstCtl)
     * |        |          |3'b000: Test mode disabled
     * |        |          |3'b001: Test_J mode
     * |        |          |3'b010: Test_K mode
     * |        |          |3'b011: Test_SE0_NAK mode
     * |        |          |3'b100: Test_Packet mode
     * |        |          |3'b101: Test_Force_Enable
     * |        |          |Others: Reserved
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): Test mode disabled
     * |        |          |0x1 (TESTJ): Test_J mode
     * |        |          |0x2 (TESTK): Test_K mode
     * |        |          |0x3 (TESTSN): Test_SE0_NAK mode
     * |        |          |0x4 (TESTPM): Test_Packet mode
     * |        |          |0x5 (TESTFE): Test_force_Enable
     * |[7]     |SGNPInNak |Set Global Non-periodic IN NAK (SGNPInNak)
     * |        |          |A write to this field sets the Global Non-periodic IN NAK.The application uses this bit to send a NAK handshake on all non-periodic IN endpoints
     * |        |          |The application must Set this bit only after making sure that the Global IN NAK Effective bit in the Core Interrupt Register (GINTSTS.GINNakEff) is cleared
     * |        |          |Values:
     * |        |          |0x0 (DISABLE): Disable Global Non-periodic IN NAK
     * |        |          |0x1 (ENABLE): Set Global Non-periodic IN NAK
     * |[8]     |CGNPInNak |Clear Global Non-periodic IN NAK (CGNPInNak)
     * |        |          |A write to this field clears the Global Non-periodic IN NAK.
     * |        |          |Values:
     * |        |          |0x0 (DISABLE): Disable Global Non-periodic IN NAK
     * |        |          |0x1 (ENABLE): Clear Global Non-periodic IN NAK
     * |[9]     |SGOUTNak  |Set Global OUT NAK (SGOUTNak)
     * |        |          |A write to this field sets the Global OUT NAK
     * |        |          |The application uses this bit to send a NAK handshake on all OUT endpoints
     * |        |          |The application must set the this bit only after making sure that the Global OUT NAK Effective bit in the Core Interrupt Register (GINTSTS.GOUTNakEff) is cleared.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): Disable Global OUT NAK
     * |        |          |0x1 (ENABLED): Set Global OUT NAK
     * |[10]    |CGOUTNak  |Clear Global OUT NAK (CGOUTNak)
     * |        |          |A write to this field clears the Global OUT NAK.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): Disable Clear Global OUT NAK
     * |        |          |0x1 (ENABLED): Clear Global OUT NAK
     * |[11]    |PWROnPrgDone|Power-On Programming Done (PWROnPrgDone)
     * |        |          |The application uses this bit to indicate that register programming is completed after a wake-up from Power-down mode.
     * |        |          |Values:
     * |        |          |0x0 (NOTDONE): Power-On Programming not done
     * |        |          |0x1 (DONE): Power-On Programming Done
     * |[14:13] |GMC       |Global Multi Count (GMC)
     * |        |          |GMC must be programmed only once after initialization
     * |        |          |Applicable only for Scatter/Gather DMA mode
     * |        |          |This indicates the number of packets to be serviced for that end point before moving to the next end point
     * |        |          |It is only for non-periodic endpoints.
     * |        |          |2'b00: Invalid.
     * |        |          |2'b01: 1 packet.
     * |        |          |2'b10: 2 packets.
     * |        |          |2'b11: 3 packets.
     * |        |          |Values:
     * |        |          |0x0 (NOTVALID): Invalid
     * |        |          |0x1 (ONEPACKET): 1 packet
     * |        |          |0x2 (TWOPACKET): 2 packets
     * |        |          |0x3 (THREEPACKET): 3 packets
     * |[15]    |IgnrFrmNum|Ignore Frame Number Feature for Isochronous Endpoints (IgnrFrmNum)
     * |        |          |Note: Do not program IgnrFrmNum bit to 1'b1 when the core is operating in threshold mode.
     * |        |          |Note: When Scatter/Gather DMA mode is enabled this feature is not applicable to High Speed, High bandwidth transfers.
     * |        |          |When this bit is enabled, there must be only one packet per descriptor.
     * |        |          |0: The core transmits the packets only in the frame number in which they are intended to be transmitted.
     * |        |          |1: The core ignores the frame number, sending packets immediately as the packets are ready.
     * |        |          |In Scatter/Gather DMA mode, if this bit is enabled, the packets are not flushed when a ISOC IN token is received for an elapsed frame.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): The core transmits the packets only in the frame number in which they are intended to be transmitted.
     * |        |          |0x1 (ENABLED): The core ignores the frame number, sending packets immediately as the packets are ready
     * |[16]    |NakOnBble |NAK on Babble Error (NakOnBble)
     * |        |          |Set NAK automatically on babble (NakOnBble)
     * |        |          |The core sets NAK automatically for the endpoint on which babble is received.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): Disable NAK on Babble Error
     * |        |          |0x1 (ENABLED): NAK on Babble Error
     * |[17]    |EnContOnBNA|Enable Continue on BNA (EnContOnBNA)
     * |        |          |This bit enables the core to continue on BNA for Bulk OUT endpoints
     * |        |          |With this feature enabled, when a Bulk OUT or INTR OUT endpoint receives a BNA interrupt the core starts processing the descriptor that caused the BNA interrupt after the endpoint re-enables the endpoint.
     * |        |          |1'b0: After receiving BNA interrupt,the core disables the endpoint
     * |        |          |When the endpoint is re-enabled by the application, the core starts processing from the DOEPDMA descriptor.
     * |        |          |1'b1: After receiving BNA interrupt, the core disables the endpoint
     * |        |          |When the endpoint is re-enabled by the application, the core starts processing from the descriptor that received the BNA interrupt.
     * |        |          |It is a one-time programmable after reset bit like any other DCTL register bits.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): Core disables the endpoint after receiving BNA interrupt
     * |        |          |When application re-enables the endpoint, core starts processing from the DOEPDMA descriptor
     * |        |          |0x1 (ENABLED): Core disables the endpoint after receiving BNA interrupt
     * |        |          |When application re-enables the endpoint, core starts processing from the descriptor that received the BNA interrupt
     * |[18]    |DeepSleepBESLReject|DeepSleepBESLReject
     * |        |          |1: Deep Sleep BESL Reject feature is enabled
     * |        |          |0: Deep Sleep BESL Reject feature is disabled
     * |        |          |Core rejects LPM request with HIRD value greater than HIRD threshold programmed
     * |        |          |NYET response is sent for LPM tokens with HIRD value greater than HIRD threshold
     * |        |          |By default, the Deep Sleep BESL Reject feature is disabled.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): Deep Sleep BESL Reject feature is disabled
     * |        |          |0x1 (ENABLED): Deep Sleep BESL Reject feature is enabled
     * |[19]    |ServInt   |Service Interval based scheduling for Isochronous IN Endpoints
     * |        |          |Note: This bit is applicable only in device mode and when Scatter/Gather DMA mode is used
     * |        |          |This feature should not be enabled along with DCTL.IgnrFrmNum.
     * |        |          |When this bit is enabled, the frame number field in the ISOC IN descriptor structure is interpreted as the last frame of the service interval
     * |        |          |In Scatter/Gather DMA mode, if this bit is enabled, the pending packets are flushed by the controller at the last frame of the service interval.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): The controller behavior depends on DCTL.IgnrFrmNum field.
     * |        |          |0x1 (ENABLED): The controller can transmit the packets in any frame of the service interval.
     * @var HSUSBD_T::DSTS
     * Offset: 0x808  Device Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SuspSts   |Suspend Status (SuspSts)
     * |        |          |In Device mode, this bit is set as long as a Suspend condition is detected on the USB
     * |        |          |The core enters the Suspend state when there is no activity on the phy_line_state_i signal for an extended period of time
     * |        |          |The core comes out of the suspend under the following conditions :
     * |        |          |If there is any activity on the phy_line_state_i signal, or
     * |        |          |If the application writes to the Remote Wakeup Signaling bit in the Device Control register (DCTL.RmtWkUpSig).
     * |        |          |When the core comes out of the suspend, this bit is set to 1'b0.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No suspend state
     * |        |          |0x1 (ACTIVE): Suspend state
     * |[2:1]   |EnumSpd   |Enumerated Speed (EnumSpd)
     * |        |          |Indicates the speed at which the controller has come up after speed detection through a connect or reset sequence.
     * |        |          |2'b00: High speed
     * |        |          |2'b01: Full speed
     * |        |          |Values:
     * |        |          |0x0 (HS3060): High speed
     * |        |          |0x1 (FS3060): Full speed
     * |        |          |0x2 (Reserved0): Reserved
     * |        |          |0x3 (Reserved1): Reserved
     * |[3]     |ErrticErr |Erratic Error (ErrticErr)
     * |        |          |The core sets this bit to report any erratic errors (phy_rxvalid_i/phy_rxvldh_i or phy_rxactive_i is asserted for at least 2 ms, due to PHY error)
     * |        |          |Due to erratic errors, the core goes into Suspended state and an interrupt is generated to the application with Early Suspend bit of the Core Interrupt register (GINTSTS.ErlySusp)
     * |        |          |If the early suspend is asserted due to an erratic error, the application can only perform a soft disconnect recover.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Erratic Error
     * |        |          |0x1 (ACTIVE): Erratic Error
     * |[21:8]  |SOFFN     |Frame or Microframe Number of the Received SOF (SOFFN)
     * |        |          |When the core is operating at high speed, this field contains a microframe number
     * |        |          |When the core is operating at full or low speed, this field contains a Frame number.
     * |        |          |Note: This register may return a non-zero value if read immediately after power-on reset
     * |        |          |In case the register bit reads non-zero immediately after power-on reset, it does not indicate that SOF has been received from the host
     * |        |          |The read value of this interrupt is valid only after a valid connection between host and device is established.
     * |[23:22] |DevLnSts  |Device Line Status (DevLnSts)
     * |        |          |Indicates the current logic level USB data lines
     * |        |          |DevLnSts[1]: Logic level of D+
     * |        |          |DevLnSts[0]: Logic level of D-
     * @var HSUSBD_T::DIEPMSK
     * Offset: 0x810  Device IN Endpoint Common Interrupt Mask Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |XferComplMsk|Transfer Completed Interrupt Mask (XferComplMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Mask Transfer Completed Interrupt
     * |        |          |0x1 (NOMASK): No Transfer Completed Interrupt Mask
     * |[1]     |EPDisbldMsk|Endpoint Disabled Interrupt Mask (EPDisbldMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Mask Endpoint Disabled Interrupt
     * |        |          |0x1 (NOMASK): No Endpoint Disabled Interrupt Mask
     * |[2]     |AHBErrMsk |AHB Error Mask (AHBErrMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Mask AHB Error Interrupt
     * |        |          |0x1 (NOMASK): No AHB Error Interrupt Mask
     * |[3]     |TimeOUTMsk|Timeout Condition Mask (TimeOUTMsk) (Non-isochronous endpoints)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Mask Timeout Condition Interrupt
     * |        |          |0x1 (NOMASK): No Timeout Condition Interrupt Mask
     * |[4]     |INTknTXFEmpMsk|IN Token Received When TxFIFO Empty Mask (INTknTXFEmpMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Mask IN Token Received When TxFIFO Empty Interrupt
     * |        |          |0x1 (NOMASK):
     * |        |          |No IN Token Received When TxFIFO Empty Interrupt
     * |[5]     |INTknEPMisMsk|IN Token received with EP Mismatch Mask (INTknEPMisMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Mask IN Token received with EP Mismatch Interrupt
     * |        |          |0x1 (NOMASK):
     * |        |          |No Mask IN Token received with EP Mismatch Interrupt
     * |[6]     |INEPNakEffMsk|IN Endpoint NAK Effective Mask (INEPNakEffMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Mask IN Endpoint NAK Effective Interrupt
     * |        |          |0x1 (NOMASK): No IN Endpoint NAK Effective Interrupt Mask
     * |[8]     |TxfifoUndrnMsk|Fifo Underrun Mask (TxfifoUndrnMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Mask Fifo Underrun Interrupt
     * |        |          |0x1 (NOMASK): No Fifo Underrun Interrupt Mask
     * |[9]     |BNAInIntrMsk|BNA interrupt Mask (BNAInIntrMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Mask BNA Interrupt
     * |        |          |0x1 (NOMASK): No BNA Interrupt Mask
     * |[13]    |NAKMsk    |NAK interrupt Mask (NAKMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Mask NAK Interrupt
     * |        |          |0x1 (NOMASK): No Mask NAK Interrupt
     * @var HSUSBD_T::DOEPMSK
     * Offset: 0x814  Device OUT Endpoint Common Interrupt Mask Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |XferComplMsk|Transfer Completed Interrupt Mask (XferComplMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Mask Transfer Completed Interrupt
     * |        |          |0x1 (NOMASK): No Transfer Completed Interrupt Mask
     * |[1]     |EPDisbldMsk|Endpoint Disabled Interrupt Mask (EPDisbldMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Mask Endpoint Disabled Interrupt
     * |        |          |0x1 (NOMASK): No Endpoint Disabled Interrupt Mask
     * |[2]     |AHBErrMsk |AHB Error (AHBErrMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Mask AHB Error Interrupt
     * |        |          |0x1 (NOMASK): No AHB Error Interrupt Mask
     * |[3]     |SetUPMsk  |SETUP Phase Done Mask (SetUPMsk)
     * |        |          |Applies to control endpoints only.
     * |        |          |Values:
     * |        |          |0x0 (MASK): Mask SETUP Phase Done Interrupt
     * |        |          |0x1 (NOMASK): No SETUP Phase Done Interrupt Mask
     * |[4]     |OUTTknEPdisMsk|OUT Token Received when Endpoint Disabled Mask (OUTTknEPdisMsk)
     * |        |          |Applies to control OUT endpoints only.
     * |        |          |Values:
     * |        |          |0x0 (MASK):
     * |        |          |Mask OUT Token Received when Endpoint Disabled Interrupt
     * |        |          |0x1 (NOMASK):
     * |        |          |No OUT Token Received when Endpoint Disabled Interrupt Mask
     * |[5]     |StsPhseRcvdMsk|Status Phase Received Mask (StsPhseRcvdMsk)
     * |        |          |Applies to control OUT endpoints only.
     * |        |          |Values:
     * |        |          |0x0 (MASK): Status Phase Received Mask
     * |        |          |0x1 (NOMASK): No Status Phase Received Mask
     * |[6]     |Back2BackSETup|Back-to-Back SETUP Packets Received Mask (Back2BackSETup)
     * |        |          |Applies to control OUT endpoints only.
     * |        |          |Values:
     * |        |          |0x0 (MASK): Mask Back-to-Back SETUP Packets Received Interrupt
     * |        |          |0x1 (NOMASK):
     * |        |          |No Back-to-Back SETUP Packets Received Interrupt Mask
     * |[8]     |OutPktErrMsk|OUT Packet Error Mask (OutPktErrMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Mask OUT Packet Error Interrupt
     * |        |          |0x1 (NOMASK): No OUT Packet Error Interrupt Mask
     * |[9]     |BnaOutIntrMsk|BNA interrupt Mask (BnaOutIntrMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Mask BNA Interrupt
     * |        |          |0x1 (NOMASK): No BNA Interrupt Mask
     * |[12]    |BbleErrMsk|Babble Error interrupt Mask (BbleErrMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Mask Babble Error Interrupt
     * |        |          |0x1 (NOMASK): No Babble Error Interrupt Mask
     * |[13]    |NAKMsk    |NAK interrupt Mask (NAKMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Mask NAK Interrupt
     * |        |          |0x1 (NOMASK): No NAK Interrupt Mask
     * |[14]    |NYETMsk   |NYET interrupt Mask (NYETMsk)
     * |        |          |Values:
     * |        |          |0x0 (MASK): Mask NYET Interrupt
     * |        |          |0x1 (NOMASK): No NYET Interrupt Mask
     * @var HSUSBD_T::DAINT
     * Offset: 0x818  Device All Endpoints Interrupt Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |InEpInt0  |IN Endpoint 0 Interrupt Bit
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Interrupt
     * |        |          |0x1 (ACTIVE): IN Endpoint 0 Interrupt
     * |[1]     |InEpInt1  |IN Endpoint 1 Interrupt Bit
     * |[2]     |InEpInt2  |IN Endpoint 2 Interrupt Bit
     * |[3]     |InEpInt3  |IN Endpoint 3 Interrupt Bit
     * |[4]     |InEpInt4  |IN Endpoint 4 Interrupt Bit
     * |[5]     |InEpInt5  |IN Endpoint 5 Interrupt Bit
     * |[6]     |InEpInt6  |IN Endpoint 6 Interrupt Bit
     * |[7]     |InEpInt7  |IN Endpoint 7 Interrupt Bit
     * |[8]     |InEpInt8  |IN Endpoint 8 Interrupt Bit
     * |[16]    |OutEPInt0 |OUT Endpoint 0 Interrupt Bit
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Interrupt
     * |        |          |0x1 (ACTIVE): OUT Endpoint 0 Interrupt
     * |[17]    |OutEPInt1 |OUT Endpoint 1 Interrupt Bit
     * |[18]    |OutEPInt2 |OUT Endpoint 2 Interrupt Bit
     * |[19]    |OutEPInt3 |OUT Endpoint 3 Interrupt Bit
     * |[20]    |OutEPInt4 |OUT Endpoint 4 Interrupt Bit
     * |[21]    |OutEPInt5 |OUT Endpoint 5 Interrupt Bit
     * |[22]    |OutEPInt6 |OUT Endpoint 6 Interrupt Bit
     * |[23]    |OutEPInt7 |OUT Endpoint 7 Interrupt Bit
     * |[24]    |OutEPInt8 |OUT Endpoint 8 Interrupt Bit
     * @var HSUSBD_T::DAINTMSK
     * Offset: 0x81C  Device All Endpoints Interrupt Mask Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |InEpMsk0  |IN Endpoint 0 Interrupt mask Bit
     * |        |          |Values:
     * |        |          |0x0 (MASK): IN Endpoint 0 Interrupt mask
     * |        |          |0x1 (NOMASK): No Interrupt mask
     * |[1]     |InEpMsk1  |IN Endpoint 1 Interrupt mask Bit
     * |[2]     |InEpMsk2  |IN Endpoint 2 Interrupt mask Bit
     * |[3]     |InEpMsk3  |IN Endpoint 3 Interrupt mask Bit
     * |[4]     |InEpMsk4  |IN Endpoint 4 Interrupt mask Bit
     * |[5]     |InEpMsk5  |IN Endpoint 5 Interrupt mask Bit
     * |[6]     |InEpMsk6  |IN Endpoint 6 Interrupt mask Bit
     * |[7]     |InEpMsk7  |IN Endpoint 7 Interrupt mask Bit
     * |[8]     |InEpMsk8  |IN Endpoint 8 Interrupt mask Bit
     * |[16]    |OutEPMsk0 |OUT Endpoint 0 Interrupt mask Bit
     * |        |          |Values:
     * |        |          |0x0 (MASK): OUT Endpoint 0 Interrupt mask
     * |        |          |0x1 (NOMASK): No Interrupt mask
     * |[17]    |OutEPMsk1 |OUT Endpoint 1 Interrupt mask Bit
     * |[18]    |OutEPMsk2 |OUT Endpoint 2 Interrupt mask Bit
     * |[19]    |OutEPMsk3 |OUT Endpoint 3 Interrupt mask Bit
     * |[20]    |OutEPMsk4 |OUT Endpoint 4 Interrupt mask Bit
     * |[21]    |OutEPMsk5 |OUT Endpoint 5 Interrupt mask Bit
     * |[22]    |OutEPMsk6 |OUT Endpoint 6 Interrupt mask Bit
     * |[23]    |OutEPMsk7 |OUT Endpoint 7 Interrupt mask Bit
     * |[24]    |OutEPMsk8 |OUT Endpoint 8 Interrupt mask Bit
     * @var HSUSBD_T::DTHRCTL
     * Offset: 0x830  Device Threshold Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |NonISOThrEn|Non-ISO IN Endpoints Threshold Enable (NonISOThrEn)
     * |        |          |When this bit is Set, the core enables thresholding for Non Isochronous IN endpoints.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): No thresholding
     * |        |          |0x1 (ENABLED): Enable thresholding for non-isochronous IN endpoints
     * |[1]     |ISOThrEn  |ISO IN Endpoints Threshold Enable (ISOThrEn)
     * |        |          |When this bit is Set, the core enables thresholding for isochronous IN endpoints.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): No thresholding
     * |        |          |0x1 (ENABLED): Enables thresholding for isochronous IN endpoints
     * |[10:2]  |TxThrLen  |Transmit Threshold Length (TxThrLen)
     * |        |          |This field specifies Transmit thresholding size in DWORDS
     * |        |          |This also forms the MAC threshold and specifies the amount of data in bytes to be in the corresponding endpoint transmit FIFO, before the core can start transmit on the USB
     * |        |          |The threshold length has to be at least eight DWORDS when the value of AHBThrRatio is 2'h00
     * |        |          |In case the AHBThrRatio is non zero the application needs to ensure that the AHB Threshold value does not go below the recommended eight DWORD
     * |        |          |This field controls both isochronous and non-isochronous IN endpoint thresholds
     * |        |          |The recommended value for ThrLen is to be the same as the programmed AHB Burst Length (GAHBCFG.HBstLen).
     * |        |          |Note:
     * |        |          |When OTG_ARCHITECTURE=2, the reset value of this register field is 8.
     * |[12:11] |AHBThrRatio|AHB Threshold Ratio (AHBThrRatio)
     * |        |          |These bits define the ratio between the AHB threshold and the MAC threshold for the transmit path only
     * |        |          |The AHB threshold always remains less than or equal to the USB threshold, because this does not increase overhead
     * |        |          |Both the AHB and the MAC threshold must be DWORD-aligned
     * |        |          |The application needs to program TxThrLen and the AHBThrRatio to make the AHB Threshold value DWORD aligned
     * |        |          |If the AHB threshold value is not DWORD aligned, the core might not behave correctly
     * |        |          |When programming the TxThrLen and AHBThrRatio, the application must ensure that the minimum AHB threshold value does not go below 8 DWORDS to meet the USB turnaround time requirements.
     * |        |          |2'b00: AHB threshold = MAC threshold.
     * |        |          |2'b01: AHB threshold = MAC threshold / 2.
     * |        |          |2'b10: AHB threshold = MAC threshold / 4.
     * |        |          |2'b11: AHB threshold = MAC threshold / 8.
     * |        |          |Values:
     * |        |          |0x0 (THRESZERO): AHB threshold = MAC threshold.
     * |        |          |0x1 (THRESONE): AHB threshold = MAC threshold /2.
     * |        |          |0x2 (THRESTWO): AHB threshold = MAC threshold /4.
     * |        |          |0x3 (THRESTHREE): AHB threshold = MAC threshold /8.
     * |[16]    |RxThrEn   |Receive Threshold Enable (RxThrEn)
     * |        |          |When this bit is set, the core enables thresholding in the receive direction.
     * |        |          |Note: We recommends that you do not enable RxThrEn, because it may cause issues in the RxFIFO especially during error conditions such as RxError and Babble.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): Disable thresholding
     * |        |          |0x1 (ENABLED): Enable thresholding in the receive direction
     * |[25:17] |RxThrLen  |Receive Threshold Length (RxThrLen)
     * |        |          |This field specifies Receive thresholding size in DWORDS
     * |        |          |This field also specifies the amount of data received on the USB before the core can start transmitting on the AHB
     * |        |          |The threshold length has to be at least eight DWORDS
     * |        |          |The recommended value for ThrLen is to be the same as the programmed AHB Burst Length (GAHBCFG.HBstLen).
     * |[27]    |ArbPrkEn  |Arbiter Parking Enable (ArbPrkEn)
     * |        |          |This bit controls internal DMA arbiter parking for IN endpoints
     * |        |          |If thresholding is enabled and this bit is set to one, then the arbiter parks on the IN endpoint for which there is a token received on the USB
     * |        |          |This is done to avoid getting into underrun conditions
     * |        |          |By default, arbiter parking is enabled.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): Disable DMA arbiter parking
     * |        |          |0x1 (ENABLED): Enable DMA arbiter parking for IN endpoints
     * @var HSUSBD_T::DIEPEMPMSK
     * Offset: 0x834  Device IN Endpoint FIFO Empty Interrupt Mask Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |InEpTxfEmpMsk|IN EP Tx FIFO Empty Interrupt Mask Bits (InEpTxfEmpMsk)
     * |        |          |These bits acts as mask bits for DIEPINTn.TxFEmp interrupt, one bit per IN Endpoint:
     * |        |          |Bit 0 for IN EP 0, bit 8 for IN EP 8
     * |        |          |Values:
     * |        |          |0x1 (EP0_MASK): Mask IN EP0 Tx FIFO Empty Interrupt
     * |        |          |0x2 (EP1_MASK): Mask IN EP1 Tx FIFO Empty Interrupt
     * |        |          |0x4 (EP2_MASK): Mask IN EP2 Tx FIFO Empty Interrupt
     * |        |          |0x8 (EP3_MASK): Mask IN EP3 Tx FIFO Empty Interrupt
     * |        |          |0x10 (EP4_MASK): Mask IN EP4 Tx FIFO Empty Interrupt
     * |        |          |0x20 (EP5_MASK): Mask IN EP5 Tx FIFO Empty Interrupt
     * |        |          |0x40 (EP6_MASK): Mask IN EP6 Tx FIFO Empty Interrupt
     * |        |          |0x80 (EP7_MASK): Mask IN EP7 Tx FIFO Empty Interrupt
     * |        |          |0x100 (EP8_MASK): Mask IN EP8 Tx FIFO Empty Interrupt
     * @var HSUSBD_T::DIEPCTL0
     * Offset: 0x900  Device Control IN Endpoint 0 Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |MPS       |Maximum Packet Size (MPS)
     * |        |          |Applies to IN and OUT endpoints.
     * |        |          |The application must program this field with the maximum packet size for the current logical endpoint.
     * |        |          |2'b00: 64 bytes
     * |        |          |2'b01: 32 bytes
     * |        |          |2'b10: 16 bytes
     * |        |          |2'b11: 8 bytes
     * |        |          |Values:
     * |        |          |0x0 (BYTES64): 64 bytes
     * |        |          |0x1 (BYTES32): 32 bytes
     * |        |          |0x2 (BYTES16): 16 bytes
     * |        |          |0x3 (BYTES8): 8 bytes
     * |[15]    |USBActEP  |USB Active Endpoint (USBActEP) (Read only)
     * |        |          |This bit is always SET to 1, indicating that control endpoint 0 is always active in all configurations and interfaces.
     * |        |          |Values:
     * |        |          |0x1 (ACTIVE0): Control endpoint is always active
     * |[17]    |NAKSts    |NAK Status (NAKSts) (Read only)
     * |        |          |Indicates the following:
     * |        |          |1'b0: The core is transmitting non-NAK handshakes based on the FIFO status
     * |        |          |1'b1: The core is transmitting NAK handshakes on this endpoint.
     * |        |          |When this bit is set, either by the application or core, the core stops transmitting data, even If there is data available in the TxFIFO
     * |        |          |Irrespective of this bit's setting, the core always responds to SETUP data packets with an ACK handshake.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE):
     * |        |          |The core is transmitting non-NAK handshakes based on the FIFO status
     * |        |          |0x1 (ACTIVE):
     * |        |          |The core is transmitting NAK handshakes on this endpoint
     * |[19:18] |EPType    |Endpoint Type (EPType) (Read only)
     * |        |          |Hardcoded to 00 for control.
     * |        |          |Values:
     * |        |          |0x0 (ACTIVE): Endpoint Control 0
     * |[21]    |Stall     |STALL Handshake (Stall)
     * |        |          |The application can only set this bit, and the core clears it, when a SETUP token is received for this endpoint
     * |        |          |If a NAK bit, Global Nonperiodic IN NAK, or Global OUT NAK is set along with this bit, the STALL bit takes priority.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Stall
     * |        |          |0x1 (ACTIVE): Stall Handshake
     * |[25:22] |TxFNum    |TxFIFO Number (TxFNum)
     * |        |          |For Dedicated FIFO operation, this value is set to the FIFO number that is assigned to IN Endpoint.
     * |        |          |Values:
     * |        |          |0x0 (TXFIFO0): Tx FIFO 0
     * |        |          |0x1 (TXFIFO1): Tx FIFO 1
     * |        |          |0x2 (TXFIFO2): Tx FIFO 2
     * |        |          |0x3 (TXFIFO3): Tx FIFO 3
     * |        |          |0x4 (TXFIFO4): Tx FIFO 4
     * |        |          |0x5 (TXFIFO5): Tx FIFO 5
     * |        |          |0x6 (TXFIFO6): Tx FIFO 6
     * |        |          |0x7 (TXFIFO7): Tx FIFO 7
     * |        |          |0x8 (TXFIFO8): Tx FIFO 8
     * |[26]    |CNAK      |Clear NAK (CNAK)
     * |        |          |A write to this bit clears the NAK bit for the endpoint
     * |        |          |Values:
     * |        |          |0x0 (NOCLEAR): No action
     * |        |          |0x1 (CLEAR): Clear NAK
     * |[27]    |SNAK      |Set NAK (SNAK
     * |        |          |) A write to this bit sets the NAK bit for the endpoint Using this bit, the application can control the transmission of NAK handshakes on an endpoint The core can also set this bit for an endpoint after a SETUP packet is received on that endpoint
     * |        |          |Values:
     * |        |          |0x0 (NOSET): No action
     * |        |          |0x1 (SET): Set NAK
     * |[30]    |EPDis     |Endpoint Disable (EPDis)
     * |        |          |The application sets this bit to stop transmitting data on an endpoint, even before the transfer for that endpoint is complete
     * |        |          |The application must wait for the Endpoint Disabled interrupt before treating the endpoint as disabled
     * |        |          |The core clears this bit before setting the Endpoint Disabled Interrupt
     * |        |          |The application must Set this bit only if Endpoint Enable is already set for this endpoint.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No action
     * |        |          |0x1 (ACTIVE): Disabled Endpoint
     * |[31]    |EPEna     |Endpoint Enable (EPEna)
     * |        |          |When Scatter/Gather DMA mode is enabled for IN endpoints, this bit indicates that the descriptor structure and data buffer with data ready to transmit is setup.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No action
     * |        |          |0x1 (ACTIVE): Enable Endpoint
     * @var HSUSBD_T::DIEPINT0
     * Offset: 0x908  Device IN Endpoint 0 Interrupt Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |XferCompl |Transfer Completed Interrupt (XferCompl)
     * |        |          |Applies to IN and OUT endpoints.
     * |        |          |When Scatter/Gather DMA mode is enabled
     * |        |          |For IN endpoint this field indicates that the requested data from the descriptor is moved from external system memory to internal FIFO.
     * |        |          |For OUT endpoint this field indicates that the requested data from the internal FIFO is moved to external system memory
     * |        |          |This interrupt is generated only when the corresponding endpoint descriptor is closed, and the IOC bit for the corresponding descriptor is set.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Transfer Complete Interrupt
     * |        |          |0x1 (ACTIVE): Transfer Completed Interrupt
     * |[1]     |EPDisbld  |Endpoint Disabled Interrupt (EPDisbld)
     * |        |          |Applies to IN and OUT endpoints.
     * |        |          |This bit indicates that the endpoint is disabled per the application's request.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Endpoint Disabled Interrupt
     * |        |          |0x1 (ACTIVE): Endpoint Disabled Interrupt
     * |[2]     |AHBErr    |AHB Error (AHBErr)
     * |        |          |Applies to IN and OUT endpoints.
     * |        |          |When there is an AHB error during an AHB read/write
     * |        |          |The application can read the corresponding endpoint DMA address register to get the error address.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No AHB Error Interrupt
     * |        |          |0x1 (ACTIVE): AHB Error interrupt
     * |[4]     |INTknTXFEmp|IN Token Received When TxFIFO is Empty (INTknTXFEmp)
     * |        |          |Applies to non-periodic IN endpoints only.
     * |        |          |Indicates that an IN token was received when the associated TxFIFO (periodic/non-periodic) was empty
     * |        |          |This interrupt is asserted on the endpoint for which the IN token was received.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No IN Token Received when TxFIFO Empty interrupt
     * |        |          |0x1 (ACTIVE): IN Token Received when TxFIFO Empty Interrupt
     * |[5]     |INTknEPMis|IN Token Received with EP Mismatch (INTknEPMis)
     * |        |          |Applies to non-periodic IN endpoints only.
     * |        |          |Indicates that the data in the top of the non-periodic TxFIFO belongs to an endpoint other than the one for which the IN token was received
     * |        |          |This interrupt is asserted on the endpoint for which the IN token was received.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No IN Token Received with EP Mismatch interrupt
     * |        |          |0x1 (ACTIVE): IN Token Received with EP Mismatch interrupt
     * |[6]     |INEPNakEff|IN Endpoint NAK Effective (INEPNakEff)
     * |        |          |Applies to periodic IN endpoints only.
     * |        |          |This bit can be cleared when the application clears the IN endpoint NAK by writing to DIEPCTLn.CNAK.
     * |        |          |This interrupt indicates that the core has sampled the NAK bit
     * |        |          |Set (either by the application or by the core).
     * |        |          |The interrupt indicates that the IN endpoint NAK bit Set by the application has taken effect in the core.
     * |        |          |This interrupt does not guarantee that a NAK handshake is sent on the USB
     * |        |          |A STALL bit takes priority over a NAK bit.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No IN Endpoint NAK Effective interrupt
     * |        |          |0x1 (ACTIVE): IN Endpoint NAK Effective interrupt
     * |[7]     |TxFEmp    |Transmit FIFO Empty (TxFEmp) (Read only)
     * |        |          |This bit is valid only for IN Endpoints
     * |        |          |This interrupt is asserted when the TxFIFO for this endpoint is either half or completely empty
     * |        |          |The half or completely empty status is determined by the TxFIFO Empty Level bit in the Core AHB Configuration register (GAHBCFG.NPTxFEmpLvl)).
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Transmit FIFO Empty interrupt
     * |        |          |0x1 (ACTIVE): Transmit FIFO Empty interrupt
     * |[8]     |TxfifoUndrn|Fifo Underrun (TxfifoUndrn)
     * |        |          |Applies to IN endpoints only.
     * |        |          |The core generates this interrupt when it detects a transmit FIFO underrun condition in threshold mode for this endpoint.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Fifo Underrun interrupt
     * |        |          |0x1 (ACTIVE): Fifo Underrun interrupt
     * |[9]     |BNAIntr   |BNA (Buffer Not Available) Interrupt (BNAIntr)
     * |        |          |The core generates this interrupt when the descriptor accessed is not ready for the Core to process, such as DMA done.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No BNA interrupt
     * |        |          |0x1 (ACTIVE): BNA interrupt
     * |[12]    |BbleErr   |NAK Interrupt (BbleErr)
     * |        |          |The core generates this interrupt when babble is received for the endpoint.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No interrupt
     * |        |          |0x1 (ACTIVE): BbleErr interrupt
     * |[13]    |NAKIntrpt |NAK Interrupt (NAKInterrupt)
     * |        |          |The core generates this interrupt when a NAK is transmitted or received by the device
     * |        |          |<brIn case of isochronous IN endpoints the interrupt gets generated when a zero length packet is transmitted due to un-availability of data in the TXFifo.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No interrupt
     * |        |          |0x1 (ACTIVE): NAK Interrupt
     * |[14]    |NYETIntrpt|NYET Interrupt (NYETIntrpt)
     * |        |          |The core generates this interrupt when a NYET response is transmitted for a non isochronous OUT endpoint.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No interrupt
     * |        |          |0x1 (ACTIVE): NYET Interrupt
     * @var HSUSBD_T::DIEPDMA0
     * Offset: 0x914  Device IN Endpoint 0 DMA Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DMAAddr   |DMAAddr
     * |        |          |This field indicates the base pointer for the descriptor list.
     * @var HSUSBD_T::DTXFSTS0
     * Offset: 0x918  Device IN Endpoint Transmit FIFO Status Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |INEPTxFSpcAvail|IN Endpoint TxFIFO Space Avail (INEPTxFSpcAvail)
     * |        |          |Indicates the amount of free space available in the Endpoint TxFIFO.
     * |        |          |Values are in terms of 32-bit words.
     * |        |          |16'h0: Endpoint TxFIFO is full
     * |        |          |16'h1: 1 word available
     * |        |          |16'h2: 2 words available
     * |        |          |16'hn: n words available (where 0 n 32,768)
     * |        |          |16'h8000: 32,768 words available
     * |        |          |Others: Reserved
     * @var HSUSBD_T::DIEPDMAB0
     * Offset: 0x91C  Device IN Endpoint 16 Buffer Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DMABufferAddr|Holds the current buffer address This register is updated as and when the data transfer for the corresponding end point is in progress.
     * @var HSUSBD_T::DOEPCTL0
     * Offset: 0xB00  Device Control OUT Endpoint 0 Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |MPS       |Maximum Packet Size (MPS)Maximum Packet Size (Read only)
     * |        |          |The maximum packet size for control OUT endpoint 0 is the same as what is programmed in control IN Endpoint 0.
     * |        |          |2'b00: 64 bytes
     * |        |          |2'b01: 32 bytes
     * |        |          |2'b10: 16 bytes
     * |        |          |2'b11: 8 bytes
     * |        |          |Values:
     * |        |          |0x0 (BYTE64): 64 bytes
     * |        |          |0x1 (BYTE32): 32 bytes
     * |        |          |0x2 (BYTE16): 16 bytes
     * |        |          |0x3 (BYTE8): 8 bytes
     * |        |          |Value After Reset: 0x
     * |[15]    |USBActEP  |USB Active Endpoint (USBActEP)USB Active Endpoint (Read only)
     * |        |          |This bit is always set to 1, indicating that a control endpoint 0 is always active in all configurations and interfaces.
     * |        |          |Values:
     * |        |          |0x1 (ACTIVE): USB Active Endpoint 0
     * |[17]    |NAKSts    |NAK Status (NAKSts) (Read only)NAK Status (Read only)
     * |        |          |Indicates the following:
     * |        |          |1'b0: The core is transmitting non-NAK handshakes based on the FIFO status.
     * |        |          |1'b1: The core is transmitting NAK handshakes on this endpoint.
     * |        |          |When either the application or the core sets this bit, the core stops receiving data, even If there is space in the RxFIFO to accommodate the incoming packet
     * |        |          |Irrespective of this bit's setting, the core always responds to SETUP data packets with an ACK handshake.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE):
     * |        |          |The core is transmitting non-NAK handshakes based on the FIFO status
     * |        |          |0x1 (ACTIVE):
     * |        |          |The core is transmitting NAK handshakes on this endpoint
     * |[19:18] |EPType    |Endpoint Type (EPType) (Read only)Endpoint Type (Read only)
     * |        |          |Hardcoded to 2'b00 for control.
     * |        |          |Values:
     * |        |          |0x0 (ACTIVE): Endpoint Control 0
     * |[20]    |Snp       |Reserved.
     * |[21]    |Stall     |STALL Handshake (Stall)STALL Handshake
     * |        |          |The application can only set this bit, and the core clears it, when a SETUP token is received for this endpoint
     * |        |          |If a NAK bit or Global OUT NAK is Set along with this bit, the STALL bit takes priority
     * |        |          |Irrespective of this bit's setting, the core always responds to SETUP data packets with an ACK handshake.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Stall
     * |        |          |0x1 (ACTIVE): Stall Handshake
     * |[26]    |CNAK      |Clear NAK (CNAK)Clear NAK
     * |        |          |A write to this bit clears the NAK bit for the endpoint.
     * |        |          |Values:
     * |        |          |0x0 (NOCLEAR): No action
     * |        |          |0x1 (CLEAR): Clear NAK
     * |[27]    |SNAK      |Set NAK (SNAK)Set NAK
     * |        |          |A write to this bit sets the NAK bit for the endpoint
     * |        |          |Using this bit, the application can control the transmission of NAK handshakes on an endpoint
     * |        |          |The core can also set bit on a Transfer Completed interrupt, or after a SETUP is received on the endpoint.
     * |        |          |Values:
     * |        |          |0x0 (NOSET): No action
     * |        |          |0x1 (SET): Set NAK
     * |[30]    |EPDis     |Endpoint Disable (EPDis)Endpoint Disable (Read only)
     * |        |          |The application cannot disable control OUT endpoint 0.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Endpoint disable
     * |[31]    |EPEna     |Endpoint Enable (EPEna)Endpoint Enable
     * |        |          |When Scatter/Gather DMA mode is enabled, for OUT endpoints this bit indicates that the descriptor structure and data buffer to receive data is setup.
     * |        |          |The core clears this bit before setting any of the following interrupts on this endpoint:
     * |        |          |SETUP Phase Done
     * |        |          |Endpoint Disabled
     * |        |          |Transfer Completed
     * |        |          |Note: This bit must be set for the core to transfer SETUP data packets into memory.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No action
     * |        |          |0x1 (ACTIVE): Enable Endpoint
     * @var HSUSBD_T::DOEPINT0
     * Offset: 0xB08  Device OUT Endpoint 0 Interrupt Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |XferCompl |Transfer Completed Interrupt (XferCompl) Transfer Completed Interrupt
     * |        |          |Applies to IN and OUT endpoints.
     * |        |          |For IN endpoint this field indicates that the requested data from the descriptor is moved from external system memory to internal FIFO.
     * |        |          |For OUT endpoint this field indicates that the requested data from the internal FIFO is moved to external system memory
     * |        |          |This interrupt is generated only when the corresponding endpoint descriptor is closed, and the IOC bit for the corresponding descriptor is Set.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Transfer Complete Interrupt
     * |        |          |0x1 (ACTIVE): Transfer Complete Interrupt
     * |[1]     |EPDisbld  |Endpoint Disabled Interrupt (EPDisbld)Endpoint Disabled Interrupt
     * |        |          |Applies to IN and OUT endpoints.
     * |        |          |This bit indicates that the endpoint is disabled per the application's request.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Endpoint Disabled Interrupt
     * |        |          |0x1 (ACTIVE): Endpoint Disabled Interrupt
     * |[2]     |AHBErr    |AHB Error (AHBErr)AHB Error
     * |        |          |Applies to IN and OUT endpoints.
     * |        |          |This is generated when there is an AHB error during an AHB read/write
     * |        |          |The application can read the corresponding endpoint DMA address register to get the error address.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No AHB Error Interrupt
     * |        |          |0x1 (ACTIVE): AHB Error interrupt
     * |[3]     |SetUp     |SETUP Phase Done (SetUp)SETUP Phase Done
     * |        |          |Applies to control OUT endpoints only.
     * |        |          |Indicates that the SETUP phase for the control endpoint is complete and no more back-to-back SETUP packets were received for the current control transfer
     * |        |          |On this interrupt, the application can decode the received SETUP data packet.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No SETUP Phase Done
     * |        |          |0x1 (ACTIVE): SETUP Phase Done
     * |[4]     |OUTTknEPdis|OUT Token Received When Endpoint Disabled (OUTTknEPdis)OUT Token Received When Endpoint Disabled
     * |        |          |Applies only to control OUT endpoints.
     * |        |          |Indicates that an OUT token was received when the endpoint was not yet enabled
     * |        |          |This interrupt is asserted on the endpoint for which the OUT token was received.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No OUT Token Received When Endpoint Disabled
     * |        |          |0x1 (ACTIVE): OUT Token Received When Endpoint Disabled
     * |[5]     |StsPhseRcvd|Status Phase Received for Control Write (StsPhseRcvd)Status Phase Received for Control Write
     * |        |          |This interrupt is valid only for Control OUT endpoints.
     * |        |          |This interrupt is generated only after the core has transferred all the data that the host has sent during the data phase of a control write transfer, to the system memory buffer.
     * |        |          |The interrupt indicates to the application that the host has switched from data phase to the status phase of a Control Write transfer
     * |        |          |The application can use this interrupt to ACK or STALL the Status phase, after it has decoded the data phase.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Status Phase Received for Control Write
     * |        |          |0x1 (ACTIVE): Status Phase Received for Control Write
     * |[6]     |Back2BackSETup|Back-to-Back SETUP Packets Received (Back2BackSETup)Back-to-Back SETUP Packets Received
     * |        |          |Applies to Control OUT endpoints only.
     * |        |          |This bit indicates that the core has received more than three back-to-back SETUP packets for this particular endpoint
     * |        |          |For information about handling this interrupt,
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No Back-to-Back SETUP Packets Received
     * |        |          |0x1 (ACTIVE): Back-to-Back SETUP Packets Received
     * |[8]     |OutPktErr |OUT Packet Error (OutPktErr)OUT Packet Error
     * |        |          |Applies to OUT endpoints Only
     * |        |          |This interrupt is valid only when thresholding is enabled.
     * |        |          |This interrupt is asserted when the core detects an overflow or a CRC error for non-Isochronous OUT packet.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No OUT Packet Error
     * |        |          |0x1 (ACTIVE): OUT Packet Error
     * |[9]     |BNAIntr   |BNA (Buffer Not Available) Interrupt (BNAIntr)Buffer Not Available Interrupt
     * |        |          |The core generates this interrupt when the descriptor accessed is not ready for the core to process, such as Host busy or DMA done.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No BNA interrupt
     * |        |          |0x1 (ACTIVE): BNA interrupt
     * |[12]    |BbleErr   |NAK Interrupt (BbleErr)NAK Interrupt
     * |        |          |The core generates this interrupt when babble is received for the endpoint.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No BbleErr interrupt
     * |        |          |0x1 (ACTIVE): BbleErr interrupt
     * |[13]    |NAKIntrpt |NAK Interrupt (NAKInterrupt)NAK Interrupt
     * |        |          |The core generates this interrupt when a NAK is transmitted or received by the device
     * |        |          |In case of isochronous IN endpoints the interrupt gets generated when a zero length packet is transmitted due to un-availability of data in the TXFifo.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No NAK interrupt
     * |        |          |0x1 (ACTIVE): NAK Interrupt
     * |[14]    |NYETIntrpt|NYET Interrupt (NYETIntrpt)NYET Interrupt
     * |        |          |The core generates this interrupt when a NYET response is transmitted for a non isochronous OUT endpoint.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): No NYET interrupt
     * |        |          |0x1 (ACTIVE): NYET Interrupt
     * @var HSUSBD_T::DOEPDMA0
     * Offset: 0xB14  Device OUT Endpoint 0 DMA Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DMAAddr   |Holds the start address of the external memory for storing or fetching endpoint data
     * |        |          |Note: For control endpoints, this field stores control OUT data packets as well as SETUP transaction data packets
     * |        |          |When more than three SETUP packets are received back-to-back, the SETUP data packet in the memory is overwritten.
     * |        |          |This register is incremented on every AHB transaction
     * |        |          |The application can give only a DWORD-aligned address
     * @var HSUSBD_T::DOEPDMAB0
     * Offset: 0xB1C  Device OUT Endpoint 16 Buffer Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DMABufferAddr|Holds the current buffer address This register is updated as and when the data transfer for the corresponding end point is in progress
     * @var HSUSBD_T::PCGCCTL
     * Offset: 0xE00  Power and Clock Gating Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |StopPclk  |Stop Pclk (StopPclk)
     * |        |          |The application sets this bit to stop the PHY clock (phy_clk) when the USB is suspended, the session is not valid, or the device is disconnected.
     * |        |          |The application clears this bit when the USB is resumed or a new session starts.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): Disable Stop Pclk
     * |        |          |0x1 (ENABLED): Enable Stop Pclk
     * |[5]     |Enbl_L1Gating|Enable Sleep Clock Gating
     * |        |          |If this bit is set, core internal clock gating is enabled sleep state if utmi_l1_suspend_n cannot be asserted by the core.
     * |        |          |The PHY clock will not be gated in sleep state if Enbl_L1Gating is not set.
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): The PHY clock is not gated in Sleep state
     * |        |          |0x1 (ENABLED): The Core internal clock gating is enabled in Sleep state
     * |[6]     |PhySleep  |PHY In Sleep (Read only)
     * |        |          |Indicates that the PHY is in Sleep State.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): Phy not in Sleep state
     * |        |          |0x1 (ACTIVE): Phy in Sleep state
     * |[7]     |L1Suspended|L1 Deep Sleep (Read only)
     * |        |          |Indicates that the PHY is in deep sleep when in L1 state.
     * |        |          |Values:
     * |        |          |0x0 (INACTIVE): Non Deep Sleep
     * |        |          |0x1 (ACTIVE): Deep Sleep
     * @var HSUSBD_T::PCGCCTL1
     * Offset: 0xE04  Power and Clock Gating Control Register1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |GateEN    |Enable Active Clock Gating (GateEn)
     * |        |          |The application programs GateEn to enable Active Clock Gating feature for the PHY and AHB clocks.
     * |        |          |1b0: Disable Active Clock Gating (Default)
     * |        |          |1b1: Enable Active Clock Gating
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): ACG disable
     * |        |          |0x1 (ENABLED): ACG enable
     * |[2:1]   |counter   |Count to Gate Clock (CntGateClk)
     * |        |          |CntGateClk indicates to the Controller how many PHY Clock cycles and AHB Clock cycles of 'IDLE' (no activity) the Controller will wait for before Gating the respective PHY and AHB clocks internal to the Controller.
     * |        |          |2b00: 64 clocks (Default).
     * |        |          |2b01: 128 clocks
     * |        |          |Values:
     * |        |          |0x0 (CLOCKS64): CLOCKS64
     * |        |          |0x1 (CLOCKS128): CLOCKS128
     * |[3]     |RAMGateEN |RAM Clock Gating Enable (RAMGateEn)
     * |        |          |The application programs RAMGateEn to enable RAM Clock Gating.
     * |        |          |1b0: Disable RAM Clock Gating (Default)
     * |        |          |1b1: Enable RAM Clock Gating
     * |        |          |Values:
     * |        |          |0x0 (DISABLED): RAM Clock Gating disable
     * |        |          |0x1 (ENABLED): RAM Clock Gating enable
     */
    __IO uint32_t GOTGCTL;               /*!< [0x0000] Control and Status Register                                      */
    __I  uint32_t RESERVE0[1];
    __IO uint32_t GAHBCFG;               /*!< [0x0008] AHB Configuration Register                                       */
    __IO uint32_t GUSBCFG;               /*!< [0x000c] USB Configuration Register                                       */
    __IO uint32_t GRSTCTL;               /*!< [0x0010] Reset Register                                                   */
    __IO uint32_t GINTSTS;               /*!< [0x0014] Interrupt Register                                               */
    __IO uint32_t GINTMSK;               /*!< [0x0018] Interrupt Mask Register                                          */
    __I  uint32_t GRXSTSR;               /*!< [0x001c] Receive Status Debug Read Register                               */
    __I  uint32_t GRXSTSP;               /*!< [0x0020] Receive Status Read/Pop Register                                 */
    __IO uint32_t GRXFSIZ;               /*!< [0x0024] Receive FIFO Size Register                                       */
    __IO uint32_t GNPTXFSIZ;             /*!< [0x0028] Non-periodic Transmit FIFO Size Register                         */
    __I  uint32_t RESERVE1[10];
    __IO uint32_t GLPMCFG;               /*!< [0x0054] LPM Config Register                                              */
    __I  uint32_t RESERVE2[1];
    __IO uint32_t GDFIFOCFG;             /*!< [0x005c] Global DFIFO Configuration Register                              */
    __I  uint32_t RESERVE3[1];
    __IO uint32_t GREFCLK;               /*!< [0x0064] ref_clk Control Register                                         */
    __IO uint32_t GINTMSK2;              /*!< [0x0068] Interrupt Mask Register 2                                        */
    __IO uint32_t GINTSTS2;              /*!< [0x006c] Interrupt Register 2                                             */
    __I  uint32_t RESERVE4[37];
    __IO uint32_t DIEPTXF1;              /*!< [0x0104] Device IN Endpoint Transmit FIFO Size Register 1                 */
    __IO uint32_t DIEPTXF2;              /*!< [0x0108] Device IN Endpoint Transmit FIFO Size Register 2                 */
    __IO uint32_t DIEPTXF3;              /*!< [0x010c] Device IN Endpoint Transmit FIFO Size Register 3                 */
    __IO uint32_t DIEPTXF4;              /*!< [0x0110] Device IN Endpoint Transmit FIFO Size Register 4                 */
    __IO uint32_t DIEPTXF5;              /*!< [0x0114] Device IN Endpoint Transmit FIFO Size Register 5                 */
    __IO uint32_t DIEPTXF6;              /*!< [0x0118] Device IN Endpoint Transmit FIFO Size Register 6                 */
    __IO uint32_t DIEPTXF7;              /*!< [0x011c] Device IN Endpoint Transmit FIFO Size Register 7                 */
    __IO uint32_t DIEPTXF8;              /*!< [0x0120] Device IN Endpoint Transmit FIFO Size Register 8                 */
    __I  uint32_t RESERVE5[439];
    __IO uint32_t DCFG;                  /*!< [0x0800] Device Configuration Register                                    */
    __IO uint32_t DCTL;                  /*!< [0x0804] Device Control Register                                          */
    __I  uint32_t DSTS;                  /*!< [0x0808] Device Status Register                                           */
    __I  uint32_t RESERVE6[1];
    __IO uint32_t DIEPMSK;               /*!< [0x0810] Device IN Endpoint Common Interrupt Mask Register                */
    __IO uint32_t DOEPMSK;               /*!< [0x0814] Device OUT Endpoint Common Interrupt Mask Register               */
    __I  uint32_t DAINT;                 /*!< [0x0818] Device All Endpoints Interrupt Register                          */
    __IO uint32_t DAINTMSK;              /*!< [0x081c] Device All Endpoints Interrupt Mask Register                     */
    __I  uint32_t RESERVE7[4];
    __IO uint32_t DTHRCTL;               /*!< [0x0830] Device Threshold Control Register                                */
    __IO uint32_t DIEPEMPMSK;            /*!< [0x0834] Device IN Endpoint FIFO Empty Interrupt Mask Register            */
    __I  uint32_t RESERVE8[50];
    __IO uint32_t DIEPCTL0;              /*!< [0x0900] Device Control IN Endpoint 0 Control Register                    */
    __I  uint32_t RESERVE9[1];
    __IO uint32_t DIEPINT0;              /*!< [0x0908] Device IN Endpoint 0 Interrupt Register                          */
    __I  uint32_t RESERVE10[2];
    __IO uint32_t DIEPDMA0;              /*!< [0x0914] Device IN Endpoint 0 DMA Address Register                        */
    __I  uint32_t DTXFSTS0;              /*!< [0x0918] Device IN Endpoint Transmit FIFO Status Register 0               */
    __I  uint32_t DIEPDMAB0;             /*!< [0x091c] Device IN Endpoint 16 Buffer Address Register                    */

    HSUSBD_IEP_T  IEP[8];                /*!< [0x0920] ~ [0x0a1c]                                                       */

    __I  uint32_t RESERVE27[56];
    __IO uint32_t DOEPCTL0;              /*!< [0x0b00] Device Control OUT Endpoint 0 Control Register                   */
    __I  uint32_t RESERVE28[1];
    __IO uint32_t DOEPINT0;              /*!< [0x0b08] Device OUT Endpoint 0 Interrupt Register                         */
    __I  uint32_t RESERVE29[2];
    __IO uint32_t DOEPDMA0;              /*!< [0x0b14] Device OUT Endpoint 0 DMA Address Register                       */
    __I  uint32_t RESERVE30[1];
    __I  uint32_t DOEPDMAB0;             /*!< [0x0b1c] Device OUT Endpoint 16 Buffer Address Register                   */

    HSUSBD_OEP_T  IEP[8];                /*!< [0x0b20] ~ [0x0c1c]                                                       */

    __I  uint32_t RESERVE55[120];
    __IO uint32_t PCGCCTL;               /*!< [0x0e00] Power and Clock Gating Control Register                          */
    __IO uint32_t PCGCCTL1;              /*!< [0x0e04] Power and Clock Gating Control Register1                         */

} HSUSBD_T;

/**
    @addtogroup HSUSBD_CONST HSUSBD Bit Field Definition
    Constant Definitions for HSUSBD Controller
@{ */

#define HSUSBD_GOTGCTL_ChirpEn_Pos       (27)                                              /*!< HSUSBD_T::GOTGCTL: ChirpEn Position    */
#define HSUSBD_GOTGCTL_ChirpEn_Msk       (0x1ul << HSUSBD_GOTGCTL_ChirpEn_Pos)             /*!< HSUSBD_T::GOTGCTL: ChirpEn Mask        */

#define HSUSBD_GOTGCTL_Testmode_corr_eUSB2_Pos (31)                                        /*!< HSUSBD_T::GOTGCTL: Testmode_corr_eUSB2 Position*/
#define HSUSBD_GOTGCTL_Testmode_corr_eUSB2_Msk (0x1ul << HSUSBD_GOTGCTL_Testmode_corr_eUSB2_Pos) /*!< HSUSBD_T::GOTGCTL: Testmode_corr_eUSB2 Mask*/

#define HSUSBD_GAHBCFG_GlblIntrMsk_Pos   (0)                                               /*!< HSUSBD_T::GAHBCFG: GlblIntrMsk Position*/
#define HSUSBD_GAHBCFG_GlblIntrMsk_Msk   (0x1ul << HSUSBD_GAHBCFG_GlblIntrMsk_Pos)         /*!< HSUSBD_T::GAHBCFG: GlblIntrMsk Mask    */

#define HSUSBD_GAHBCFG_HBstLen_Pos       (1)                                               /*!< HSUSBD_T::GAHBCFG: HBstLen Position    */
#define HSUSBD_GAHBCFG_HBstLen_Msk       (0xful << HSUSBD_GAHBCFG_HBstLen_Pos)             /*!< HSUSBD_T::GAHBCFG: HBstLen Mask        */

#define HSUSBD_GAHBCFG_DMAEn_Pos         (5)                                               /*!< HSUSBD_T::GAHBCFG: DMAEn Position      */
#define HSUSBD_GAHBCFG_DMAEn_Msk         (0x1ul << HSUSBD_GAHBCFG_DMAEn_Pos)               /*!< HSUSBD_T::GAHBCFG: DMAEn Mask          */

#define HSUSBD_GAHBCFG_AHBSingle_Pos     (23)                                              /*!< HSUSBD_T::GAHBCFG: AHBSingle Position  */
#define HSUSBD_GAHBCFG_AHBSingle_Msk     (0x1ul << HSUSBD_GAHBCFG_AHBSingle_Pos)           /*!< HSUSBD_T::GAHBCFG: AHBSingle Mask      */

#define HSUSBD_GAHBCFG_InvDescEndianess_Pos (24)                                           /*!< HSUSBD_T::GAHBCFG: InvDescEndianess Position*/
#define HSUSBD_GAHBCFG_InvDescEndianess_Msk (0x1ul << HSUSBD_GAHBCFG_InvDescEndianess_Pos) /*!< HSUSBD_T::GAHBCFG: InvDescEndianess Mask*/

#define HSUSBD_GUSBCFG_TOutCal_Pos       (0)                                               /*!< HSUSBD_T::GUSBCFG: TOutCal Position    */
#define HSUSBD_GUSBCFG_TOutCal_Msk       (0x7ul << HSUSBD_GUSBCFG_TOutCal_Pos)             /*!< HSUSBD_T::GUSBCFG: TOutCal Mask        */

#define HSUSBD_GUSBCFG_USBTrdTim_Pos     (10)                                              /*!< HSUSBD_T::GUSBCFG: USBTrdTim Position  */
#define HSUSBD_GUSBCFG_USBTrdTim_Msk     (0xful << HSUSBD_GUSBCFG_USBTrdTim_Pos)           /*!< HSUSBD_T::GUSBCFG: USBTrdTim Mask      */

#define HSUSBD_GUSBCFG_TxEndDelay_Pos    (28)                                              /*!< HSUSBD_T::GUSBCFG: TxEndDelay Position */
#define HSUSBD_GUSBCFG_TxEndDelay_Msk    (0x1ul << HSUSBD_GUSBCFG_TxEndDelay_Pos)          /*!< HSUSBD_T::GUSBCFG: TxEndDelay Mask     */

#define HSUSBD_GRSTCTL_CSftRst_Pos       (0)                                               /*!< HSUSBD_T::GRSTCTL: CSftRst Position    */
#define HSUSBD_GRSTCTL_CSftRst_Msk       (0x1ul << HSUSBD_GRSTCTL_CSftRst_Pos)             /*!< HSUSBD_T::GRSTCTL: CSftRst Mask        */

#define HSUSBD_GRSTCTL_PIUFSSftRst_Pos   (1)                                               /*!< HSUSBD_T::GRSTCTL: PIUFSSftRst Position*/
#define HSUSBD_GRSTCTL_PIUFSSftRst_Msk   (0x1ul << HSUSBD_GRSTCTL_PIUFSSftRst_Pos)         /*!< HSUSBD_T::GRSTCTL: PIUFSSftRst Mask    */

#define HSUSBD_GRSTCTL_RxFFlsh_Pos       (4)                                               /*!< HSUSBD_T::GRSTCTL: RxFFlsh Position    */
#define HSUSBD_GRSTCTL_RxFFlsh_Msk       (0x1ul << HSUSBD_GRSTCTL_RxFFlsh_Pos)             /*!< HSUSBD_T::GRSTCTL: RxFFlsh Mask        */

#define HSUSBD_GRSTCTL_TxFFlsh_Pos       (5)                                               /*!< HSUSBD_T::GRSTCTL: TxFFlsh Position    */
#define HSUSBD_GRSTCTL_TxFFlsh_Msk       (0x1ul << HSUSBD_GRSTCTL_TxFFlsh_Pos)             /*!< HSUSBD_T::GRSTCTL: TxFFlsh Mask        */

#define HSUSBD_GRSTCTL_TxFNum_Pos        (6)                                               /*!< HSUSBD_T::GRSTCTL: TxFNum Position     */
#define HSUSBD_GRSTCTL_TxFNum_Msk        (0x1ful << HSUSBD_GRSTCTL_TxFNum_Pos)             /*!< HSUSBD_T::GRSTCTL: TxFNum Mask         */

#define HSUSBD_GRSTCTL_AHBIdle_Pos       (31)                                              /*!< HSUSBD_T::GRSTCTL: AHBIdle Position    */
#define HSUSBD_GRSTCTL_AHBIdle_Msk       (0x1ul << HSUSBD_GRSTCTL_AHBIdle_Pos)             /*!< HSUSBD_T::GRSTCTL: AHBIdle Mask        */

#define HSUSBD_GINTSTS_Sof_Pos           (3)                                               /*!< HSUSBD_T::GINTSTS: Sof Position        */
#define HSUSBD_GINTSTS_Sof_Msk           (0x1ul << HSUSBD_GINTSTS_Sof_Pos)                 /*!< HSUSBD_T::GINTSTS: Sof Mask            */

#define HSUSBD_GINTSTS_RxFLvl_Pos        (4)                                               /*!< HSUSBD_T::GINTSTS: RxFLvl Position     */
#define HSUSBD_GINTSTS_RxFLvl_Msk        (0x1ul << HSUSBD_GINTSTS_RxFLvl_Pos)              /*!< HSUSBD_T::GINTSTS: RxFLvl Mask         */

#define HSUSBD_GINTSTS_GINNakEff_Pos     (6)                                               /*!< HSUSBD_T::GINTSTS: GINNakEff Position  */
#define HSUSBD_GINTSTS_GINNakEff_Msk     (0x1ul << HSUSBD_GINTSTS_GINNakEff_Pos)           /*!< HSUSBD_T::GINTSTS: GINNakEff Mask      */

#define HSUSBD_GINTSTS_GOUTNakEff_Pos    (7)                                               /*!< HSUSBD_T::GINTSTS: GOUTNakEff Position */
#define HSUSBD_GINTSTS_GOUTNakEff_Msk    (0x1ul << HSUSBD_GINTSTS_GOUTNakEff_Pos)          /*!< HSUSBD_T::GINTSTS: GOUTNakEff Mask     */

#define HSUSBD_GINTSTS_ErlySusp_Pos      (10)                                              /*!< HSUSBD_T::GINTSTS: ErlySusp Position   */
#define HSUSBD_GINTSTS_ErlySusp_Msk      (0x1ul << HSUSBD_GINTSTS_ErlySusp_Pos)            /*!< HSUSBD_T::GINTSTS: ErlySusp Mask       */

#define HSUSBD_GINTSTS_USBSusp_Pos       (11)                                              /*!< HSUSBD_T::GINTSTS: USBSusp Position    */
#define HSUSBD_GINTSTS_USBSusp_Msk       (0x1ul << HSUSBD_GINTSTS_USBSusp_Pos)             /*!< HSUSBD_T::GINTSTS: USBSusp Mask        */

#define HSUSBD_GINTSTS_USBRst_Pos        (12)                                              /*!< HSUSBD_T::GINTSTS: USBRst Position     */
#define HSUSBD_GINTSTS_USBRst_Msk        (0x1ul << HSUSBD_GINTSTS_USBRst_Pos)              /*!< HSUSBD_T::GINTSTS: USBRst Mask         */

#define HSUSBD_GINTSTS_EnumDone_Pos      (13)                                              /*!< HSUSBD_T::GINTSTS: EnumDone Position   */
#define HSUSBD_GINTSTS_EnumDone_Msk      (0x1ul << HSUSBD_GINTSTS_EnumDone_Pos)            /*!< HSUSBD_T::GINTSTS: EnumDone Mask       */

#define HSUSBD_GINTSTS_ISOOutDrop_Pos    (14)                                              /*!< HSUSBD_T::GINTSTS: ISOOutDrop Position */
#define HSUSBD_GINTSTS_ISOOutDrop_Msk    (0x1ul << HSUSBD_GINTSTS_ISOOutDrop_Pos)          /*!< HSUSBD_T::GINTSTS: ISOOutDrop Mask     */

#define HSUSBD_GINTSTS_EOPF_Pos          (15)                                              /*!< HSUSBD_T::GINTSTS: EOPF Position       */
#define HSUSBD_GINTSTS_EOPF_Msk          (0x1ul << HSUSBD_GINTSTS_EOPF_Pos)                /*!< HSUSBD_T::GINTSTS: EOPF Mask           */

#define HSUSBD_GINTSTS_IEPInt_Pos        (18)                                              /*!< HSUSBD_T::GINTSTS: IEPInt Position     */
#define HSUSBD_GINTSTS_IEPInt_Msk        (0x1ul << HSUSBD_GINTSTS_IEPInt_Pos)              /*!< HSUSBD_T::GINTSTS: IEPInt Mask         */

#define HSUSBD_GINTSTS_OEPInt_Pos        (19)                                              /*!< HSUSBD_T::GINTSTS: OEPInt Position     */
#define HSUSBD_GINTSTS_OEPInt_Msk        (0x1ul << HSUSBD_GINTSTS_OEPInt_Pos)              /*!< HSUSBD_T::GINTSTS: OEPInt Mask         */

#define HSUSBD_GINTSTS_FetSusp_Pos       (22)                                              /*!< HSUSBD_T::GINTSTS: FetSusp Position    */
#define HSUSBD_GINTSTS_FetSusp_Msk       (0x1ul << HSUSBD_GINTSTS_FetSusp_Pos)             /*!< HSUSBD_T::GINTSTS: FetSusp Mask        */

#define HSUSBD_GINTSTS_ResetDet_Pos      (23)                                              /*!< HSUSBD_T::GINTSTS: ResetDet Position   */
#define HSUSBD_GINTSTS_ResetDet_Msk      (0x1ul << HSUSBD_GINTSTS_ResetDet_Pos)            /*!< HSUSBD_T::GINTSTS: ResetDet Mask       */

#define HSUSBD_GINTSTS_LPM_Int_Pos       (27)                                              /*!< HSUSBD_T::GINTSTS: LPM_Int Position    */
#define HSUSBD_GINTSTS_LPM_Int_Msk       (0x1ul << HSUSBD_GINTSTS_LPM_Int_Pos)             /*!< HSUSBD_T::GINTSTS: LPM_Int Mask        */

#define HSUSBD_GINTSTS_WkUpInt_Pos       (31)                                              /*!< HSUSBD_T::GINTSTS: WkUpInt Position    */
#define HSUSBD_GINTSTS_WkUpInt_Msk       (0x1ul << HSUSBD_GINTSTS_WkUpInt_Pos)             /*!< HSUSBD_T::GINTSTS: WkUpInt Mask        */

#define HSUSBD_GINTMSK_OTGIntMsk_Pos     (2)                                               /*!< HSUSBD_T::GINTMSK: OTGIntMsk Position  */
#define HSUSBD_GINTMSK_OTGIntMsk_Msk     (0x1ul << HSUSBD_GINTMSK_OTGIntMsk_Pos)           /*!< HSUSBD_T::GINTMSK: OTGIntMsk Mask      */

#define HSUSBD_GINTMSK_SofMsk_Pos        (3)                                               /*!< HSUSBD_T::GINTMSK: SofMsk Position     */
#define HSUSBD_GINTMSK_SofMsk_Msk        (0x1ul << HSUSBD_GINTMSK_SofMsk_Pos)              /*!< HSUSBD_T::GINTMSK: SofMsk Mask         */

#define HSUSBD_GINTMSK_RxFLvlMsk_Pos     (4)                                               /*!< HSUSBD_T::GINTMSK: RxFLvlMsk Position  */
#define HSUSBD_GINTMSK_RxFLvlMsk_Msk     (0x1ul << HSUSBD_GINTMSK_RxFLvlMsk_Pos)           /*!< HSUSBD_T::GINTMSK: RxFLvlMsk Mask      */

#define HSUSBD_GINTMSK_GINNakEffMsk_Pos  (6)                                               /*!< HSUSBD_T::GINTMSK: GINNakEffMsk Position*/
#define HSUSBD_GINTMSK_GINNakEffMsk_Msk  (0x1ul << HSUSBD_GINTMSK_GINNakEffMsk_Pos)        /*!< HSUSBD_T::GINTMSK: GINNakEffMsk Mask   */

#define HSUSBD_GINTMSK_GOUTNakEffMsk_Pos (7)                                               /*!< HSUSBD_T::GINTMSK: GOUTNakEffMsk Position*/
#define HSUSBD_GINTMSK_GOUTNakEffMsk_Msk (0x1ul << HSUSBD_GINTMSK_GOUTNakEffMsk_Pos)       /*!< HSUSBD_T::GINTMSK: GOUTNakEffMsk Mask  */

#define HSUSBD_GINTMSK_ErlySuspMsk_Pos   (10)                                              /*!< HSUSBD_T::GINTMSK: ErlySuspMsk Position*/
#define HSUSBD_GINTMSK_ErlySuspMsk_Msk   (0x1ul << HSUSBD_GINTMSK_ErlySuspMsk_Pos)         /*!< HSUSBD_T::GINTMSK: ErlySuspMsk Mask    */

#define HSUSBD_GINTMSK_USBSuspMsk_Pos    (11)                                              /*!< HSUSBD_T::GINTMSK: USBSuspMsk Position */
#define HSUSBD_GINTMSK_USBSuspMsk_Msk    (0x1ul << HSUSBD_GINTMSK_USBSuspMsk_Pos)          /*!< HSUSBD_T::GINTMSK: USBSuspMsk Mask     */

#define HSUSBD_GINTMSK_USBRstMsk_Pos     (12)                                              /*!< HSUSBD_T::GINTMSK: USBRstMsk Position  */
#define HSUSBD_GINTMSK_USBRstMsk_Msk     (0x1ul << HSUSBD_GINTMSK_USBRstMsk_Pos)           /*!< HSUSBD_T::GINTMSK: USBRstMsk Mask      */

#define HSUSBD_GINTMSK_EnumDoneMsk_Pos   (13)                                              /*!< HSUSBD_T::GINTMSK: EnumDoneMsk Position*/
#define HSUSBD_GINTMSK_EnumDoneMsk_Msk   (0x1ul << HSUSBD_GINTMSK_EnumDoneMsk_Pos)         /*!< HSUSBD_T::GINTMSK: EnumDoneMsk Mask    */

#define HSUSBD_GINTMSK_ISOOutDropMsk_Pos (14)                                              /*!< HSUSBD_T::GINTMSK: ISOOutDropMsk Position*/
#define HSUSBD_GINTMSK_ISOOutDropMsk_Msk (0x1ul << HSUSBD_GINTMSK_ISOOutDropMsk_Pos)       /*!< HSUSBD_T::GINTMSK: ISOOutDropMsk Mask  */

#define HSUSBD_GINTMSK_EOPFMsk_Pos       (15)                                              /*!< HSUSBD_T::GINTMSK: EOPFMsk Position    */
#define HSUSBD_GINTMSK_EOPFMsk_Msk       (0x1ul << HSUSBD_GINTMSK_EOPFMsk_Pos)             /*!< HSUSBD_T::GINTMSK: EOPFMsk Mask        */

#define HSUSBD_GINTMSK_EPMisMsk_Pos      (17)                                              /*!< HSUSBD_T::GINTMSK: EPMisMsk Position   */
#define HSUSBD_GINTMSK_EPMisMsk_Msk      (0x1ul << HSUSBD_GINTMSK_EPMisMsk_Pos)            /*!< HSUSBD_T::GINTMSK: EPMisMsk Mask       */

#define HSUSBD_GINTMSK_IEPIntMsk_Pos     (18)                                              /*!< HSUSBD_T::GINTMSK: IEPIntMsk Position  */
#define HSUSBD_GINTMSK_IEPIntMsk_Msk     (0x1ul << HSUSBD_GINTMSK_IEPIntMsk_Pos)           /*!< HSUSBD_T::GINTMSK: IEPIntMsk Mask      */

#define HSUSBD_GINTMSK_OEPIntMsk_Pos     (19)                                              /*!< HSUSBD_T::GINTMSK: OEPIntMsk Position  */
#define HSUSBD_GINTMSK_OEPIntMsk_Msk     (0x1ul << HSUSBD_GINTMSK_OEPIntMsk_Pos)           /*!< HSUSBD_T::GINTMSK: OEPIntMsk Mask      */

#define HSUSBD_GINTMSK_FetSuspMsk_Pos    (22)                                              /*!< HSUSBD_T::GINTMSK: FetSuspMsk Position */
#define HSUSBD_GINTMSK_FetSuspMsk_Msk    (0x1ul << HSUSBD_GINTMSK_FetSuspMsk_Pos)          /*!< HSUSBD_T::GINTMSK: FetSuspMsk Mask     */

#define HSUSBD_GINTMSK_ResetDetMsk_Pos   (23)                                              /*!< HSUSBD_T::GINTMSK: ResetDetMsk Position*/
#define HSUSBD_GINTMSK_ResetDetMsk_Msk   (0x1ul << HSUSBD_GINTMSK_ResetDetMsk_Pos)         /*!< HSUSBD_T::GINTMSK: ResetDetMsk Mask    */

#define HSUSBD_GINTMSK_LPM_IntMsk_Pos    (27)                                              /*!< HSUSBD_T::GINTMSK: LPM_IntMsk Position */
#define HSUSBD_GINTMSK_LPM_IntMsk_Msk    (0x1ul << HSUSBD_GINTMSK_LPM_IntMsk_Pos)          /*!< HSUSBD_T::GINTMSK: LPM_IntMsk Mask     */

#define HSUSBD_GINTMSK_WkUpIntMsk_Pos    (31)                                              /*!< HSUSBD_T::GINTMSK: WkUpIntMsk Position */
#define HSUSBD_GINTMSK_WkUpIntMsk_Msk    (0x1ul << HSUSBD_GINTMSK_WkUpIntMsk_Pos)          /*!< HSUSBD_T::GINTMSK: WkUpIntMsk Mask     */

#define HSUSBD_GRXSTSR_EPNum_Pos         (0)                                               /*!< HSUSBD_T::GRXSTSR: EPNum Position      */
#define HSUSBD_GRXSTSR_EPNum_Msk         (0xful << HSUSBD_GRXSTSR_EPNum_Pos)               /*!< HSUSBD_T::GRXSTSR: EPNum Mask          */

#define HSUSBD_GRXSTSR_BCnt_Pos          (4)                                               /*!< HSUSBD_T::GRXSTSR: BCnt Position       */
#define HSUSBD_GRXSTSR_BCnt_Msk          (0x7fful << HSUSBD_GRXSTSR_BCnt_Pos)              /*!< HSUSBD_T::GRXSTSR: BCnt Mask           */

#define HSUSBD_GRXSTSR_DPID_Pos          (15)                                              /*!< HSUSBD_T::GRXSTSR: DPID Position       */
#define HSUSBD_GRXSTSR_DPID_Msk          (0x3ul << HSUSBD_GRXSTSR_DPID_Pos)                /*!< HSUSBD_T::GRXSTSR: DPID Mask           */

#define HSUSBD_GRXSTSR_PktSts_Pos        (17)                                              /*!< HSUSBD_T::GRXSTSR: PktSts Position     */
#define HSUSBD_GRXSTSR_PktSts_Msk        (0xful << HSUSBD_GRXSTSR_PktSts_Pos)              /*!< HSUSBD_T::GRXSTSR: PktSts Mask         */

#define HSUSBD_GRXSTSR_FN_Pos            (21)                                              /*!< HSUSBD_T::GRXSTSR: FN Position         */
#define HSUSBD_GRXSTSR_FN_Msk            (0xful << HSUSBD_GRXSTSR_FN_Pos)                  /*!< HSUSBD_T::GRXSTSR: FN Mask             */

#define HSUSBD_GRXSTSP_EPNum_Pos         (0)                                               /*!< HSUSBD_T::GRXSTSP: EPNum Position      */
#define HSUSBD_GRXSTSP_EPNum_Msk         (0xful << HSUSBD_GRXSTSP_EPNum_Pos)               /*!< HSUSBD_T::GRXSTSP: EPNum Mask          */

#define HSUSBD_GRXSTSP_BCnt_Pos          (4)                                               /*!< HSUSBD_T::GRXSTSP: BCnt Position       */
#define HSUSBD_GRXSTSP_BCnt_Msk          (0x7fful << HSUSBD_GRXSTSP_BCnt_Pos)              /*!< HSUSBD_T::GRXSTSP: BCnt Mask           */

#define HSUSBD_GRXSTSP_DPID_Pos          (15)                                              /*!< HSUSBD_T::GRXSTSP: DPID Position       */
#define HSUSBD_GRXSTSP_DPID_Msk          (0x3ul << HSUSBD_GRXSTSP_DPID_Pos)                /*!< HSUSBD_T::GRXSTSP: DPID Mask           */

#define HSUSBD_GRXSTSP_PktSts_Pos        (17)                                              /*!< HSUSBD_T::GRXSTSP: PktSts Position     */
#define HSUSBD_GRXSTSP_PktSts_Msk        (0xful << HSUSBD_GRXSTSP_PktSts_Pos)              /*!< HSUSBD_T::GRXSTSP: PktSts Mask         */

#define HSUSBD_GRXSTSP_FN_Pos            (21)                                              /*!< HSUSBD_T::GRXSTSP: FN Position         */
#define HSUSBD_GRXSTSP_FN_Msk            (0xful << HSUSBD_GRXSTSP_FN_Pos)                  /*!< HSUSBD_T::GRXSTSP: FN Mask             */

#define HSUSBD_GRXFSIZ_RxFDep_Pos        (0)                                               /*!< HSUSBD_T::GRXFSIZ: RxFDep Position     */
#define HSUSBD_GRXFSIZ_RxFDep_Msk        (0x1fful << HSUSBD_GRXFSIZ_RxFDep_Pos)            /*!< HSUSBD_T::GRXFSIZ: RxFDep Mask         */

#define HSUSBD_GNPTXFSIZ_INEPTxF0StAddr_Pos (0)                                            /*!< HSUSBD_T::GNPTXFSIZ: INEPTxF0StAddr Position*/
#define HSUSBD_GNPTXFSIZ_INEPTxF0StAddr_Msk (0x1fful << HSUSBD_GNPTXFSIZ_INEPTxF0StAddr_Pos) /*!< HSUSBD_T::GNPTXFSIZ: INEPTxF0StAddr Mask*/

#define HSUSBD_GNPTXFSIZ_INEPTxF0Dep_Pos (16)                                              /*!< HSUSBD_T::GNPTXFSIZ: INEPTxF0Dep Position*/
#define HSUSBD_GNPTXFSIZ_INEPTxF0Dep_Msk (0x3ful << HSUSBD_GNPTXFSIZ_INEPTxF0Dep_Pos)      /*!< HSUSBD_T::GNPTXFSIZ: INEPTxF0Dep Mask  */

#define HSUSBD_GLPMCFG_LPMCap_Pos        (0)                                               /*!< HSUSBD_T::GLPMCFG: LPMCap Position     */
#define HSUSBD_GLPMCFG_LPMCap_Msk        (0x1ul << HSUSBD_GLPMCFG_LPMCap_Pos)              /*!< HSUSBD_T::GLPMCFG: LPMCap Mask         */

#define HSUSBD_GLPMCFG_AppL1Res_Pos      (1)                                               /*!< HSUSBD_T::GLPMCFG: AppL1Res Position   */
#define HSUSBD_GLPMCFG_AppL1Res_Msk      (0x1ul << HSUSBD_GLPMCFG_AppL1Res_Pos)            /*!< HSUSBD_T::GLPMCFG: AppL1Res Mask       */

#define HSUSBD_GLPMCFG_HIRD_Pos          (2)                                               /*!< HSUSBD_T::GLPMCFG: HIRD Position       */
#define HSUSBD_GLPMCFG_HIRD_Msk          (0xful << HSUSBD_GLPMCFG_HIRD_Pos)                /*!< HSUSBD_T::GLPMCFG: HIRD Mask           */

#define HSUSBD_GLPMCFG_bRemoteWake_Pos   (6)                                               /*!< HSUSBD_T::GLPMCFG: bRemoteWake Position*/
#define HSUSBD_GLPMCFG_bRemoteWake_Msk   (0x1ul << HSUSBD_GLPMCFG_bRemoteWake_Pos)         /*!< HSUSBD_T::GLPMCFG: bRemoteWake Mask    */

#define HSUSBD_GLPMCFG_EnblSlpM_Pos      (7)                                               /*!< HSUSBD_T::GLPMCFG: EnblSlpM Position   */
#define HSUSBD_GLPMCFG_EnblSlpM_Msk      (0x1ul << HSUSBD_GLPMCFG_EnblSlpM_Pos)            /*!< HSUSBD_T::GLPMCFG: EnblSlpM Mask       */

#define HSUSBD_GLPMCFG_HIRD_Thres_Pos    (8)                                               /*!< HSUSBD_T::GLPMCFG: HIRD_Thres Position */
#define HSUSBD_GLPMCFG_HIRD_Thres_Msk    (0x1ful << HSUSBD_GLPMCFG_HIRD_Thres_Pos)         /*!< HSUSBD_T::GLPMCFG: HIRD_Thres Mask     */

#define HSUSBD_GLPMCFG_CoreL1Res_Pos     (13)                                              /*!< HSUSBD_T::GLPMCFG: CoreL1Res Position  */
#define HSUSBD_GLPMCFG_CoreL1Res_Msk     (0x3ul << HSUSBD_GLPMCFG_CoreL1Res_Pos)           /*!< HSUSBD_T::GLPMCFG: CoreL1Res Mask      */

#define HSUSBD_GLPMCFG_SlpSts_Pos        (15)                                              /*!< HSUSBD_T::GLPMCFG: SlpSts Position     */
#define HSUSBD_GLPMCFG_SlpSts_Msk        (0x1ul << HSUSBD_GLPMCFG_SlpSts_Pos)              /*!< HSUSBD_T::GLPMCFG: SlpSts Mask         */

#define HSUSBD_GLPMCFG_L1ResumeOK_Pos    (16)                                              /*!< HSUSBD_T::GLPMCFG: L1ResumeOK Position */
#define HSUSBD_GLPMCFG_L1ResumeOK_Msk    (0x1ul << HSUSBD_GLPMCFG_L1ResumeOK_Pos)          /*!< HSUSBD_T::GLPMCFG: L1ResumeOK Mask     */

#define HSUSBD_GLPMCFG_LPM_Accept_Ctrl_Pos (20)                                            /*!< HSUSBD_T::GLPMCFG: LPM_Accept_Ctrl Position*/
#define HSUSBD_GLPMCFG_LPM_Accept_Ctrl_Msk (0xful << HSUSBD_GLPMCFG_LPM_Accept_Ctrl_Pos)   /*!< HSUSBD_T::GLPMCFG: LPM_Accept_Ctrl Mask*/

#define HSUSBD_GLPMCFG_LPM_EnBESL_Pos    (28)                                              /*!< HSUSBD_T::GLPMCFG: LPM_EnBESL Position */
#define HSUSBD_GLPMCFG_LPM_EnBESL_Msk    (0x1ul << HSUSBD_GLPMCFG_LPM_EnBESL_Pos)          /*!< HSUSBD_T::GLPMCFG: LPM_EnBESL Mask     */

#define HSUSBD_GDFIFOCFG_GDFIFOCfg_Pos   (0)                                               /*!< HSUSBD_T::GDFIFOCFG: GDFIFOCfg Position*/
#define HSUSBD_GDFIFOCFG_GDFIFOCfg_Msk   (0xfffful << HSUSBD_GDFIFOCFG_GDFIFOCfg_Pos)      /*!< HSUSBD_T::GDFIFOCFG: GDFIFOCfg Mask    */

#define HSUSBD_GDFIFOCFG_EPInfoBaseAddr_Pos (16)                                           /*!< HSUSBD_T::GDFIFOCFG: EPInfoBaseAddr Position*/
#define HSUSBD_GDFIFOCFG_EPInfoBaseAddr_Msk (0xfffful << HSUSBD_GDFIFOCFG_EPInfoBaseAddr_Pos) /*!< HSUSBD_T::GDFIFOCFG: EPInfoBaseAddr Mask*/

#define HSUSBD_GREFCLK_SOF_CNT_WKUP_ALERT_Pos (0)                                          /*!< HSUSBD_T::GREFCLK: SOF_CNT_WKUP_ALERT Position*/
#define HSUSBD_GREFCLK_SOF_CNT_WKUP_ALERT_Msk (0x3fful << HSUSBD_GREFCLK_SOF_CNT_WKUP_ALERT_Pos) /*!< HSUSBD_T::GREFCLK: SOF_CNT_WKUP_ALERT Mask*/

#define HSUSBD_GREFCLK_RefclkMode_Pos    (14)                                              /*!< HSUSBD_T::GREFCLK: RefclkMode Position */
#define HSUSBD_GREFCLK_RefclkMode_Msk    (0x1ul << HSUSBD_GREFCLK_RefclkMode_Pos)          /*!< HSUSBD_T::GREFCLK: RefclkMode Mask     */

#define HSUSBD_GREFCLK_REFCLKPER_Pos     (15)                                              /*!< HSUSBD_T::GREFCLK: REFCLKPER Position  */
#define HSUSBD_GREFCLK_REFCLKPER_Msk     (0x1fffful << HSUSBD_GREFCLK_REFCLKPER_Pos)       /*!< HSUSBD_T::GREFCLK: REFCLKPER Mask      */

#define HSUSBD_GINTMSK2_WkUpAlertIntMsk_Pos (0)                                            /*!< HSUSBD_T::GINTMSK2: WkUpAlertIntMsk Position*/
#define HSUSBD_GINTMSK2_WkUpAlertIntMsk_Msk (0x1ul << HSUSBD_GINTMSK2_WkUpAlertIntMsk_Pos) /*!< HSUSBD_T::GINTMSK2: WkUpAlertIntMsk Mask*/

#define HSUSBD_GINTSTS2_WkUpAlertInt_Pos (0)                                               /*!< HSUSBD_T::GINTSTS2: WkUpAlertInt Position*/
#define HSUSBD_GINTSTS2_WkUpAlertInt_Msk (0x1ul << HSUSBD_GINTSTS2_WkUpAlertInt_Pos)       /*!< HSUSBD_T::GINTSTS2: WkUpAlertInt Mask  */

#define HSUSBD_DIEPTXF1_INEPnTxFStAddr_Pos (0)                                             /*!< HSUSBD_T::DIEPTXF1: INEPnTxFStAddr Position*/
#define HSUSBD_DIEPTXF1_INEPnTxFStAddr_Msk (0x1fful << HSUSBD_DIEPTXF1_INEPnTxFStAddr_Pos) /*!< HSUSBD_T::DIEPTXF1: INEPnTxFStAddr Mask*/

#define HSUSBD_DIEPTXF1_INEPnTxFDep_Pos  (16)                                              /*!< HSUSBD_T::DIEPTXF1: INEPnTxFDep Position*/
#define HSUSBD_DIEPTXF1_INEPnTxFDep_Msk  (0x1fful << HSUSBD_DIEPTXF1_INEPnTxFDep_Pos)      /*!< HSUSBD_T::DIEPTXF1: INEPnTxFDep Mask   */

#define HSUSBD_DIEPTXF2_INEPnTxFStAddr_Pos (0)                                             /*!< HSUSBD_T::DIEPTXF2: INEPnTxFStAddr Position*/
#define HSUSBD_DIEPTXF2_INEPnTxFStAddr_Msk (0x3fful << HSUSBD_DIEPTXF2_INEPnTxFStAddr_Pos) /*!< HSUSBD_T::DIEPTXF2: INEPnTxFStAddr Mask*/

#define HSUSBD_DIEPTXF2_INEPnTxFDep_Pos  (16)                                              /*!< HSUSBD_T::DIEPTXF2: INEPnTxFDep Position*/
#define HSUSBD_DIEPTXF2_INEPnTxFDep_Msk  (0x1fful << HSUSBD_DIEPTXF2_INEPnTxFDep_Pos)      /*!< HSUSBD_T::DIEPTXF2: INEPnTxFDep Mask   */

#define HSUSBD_DIEPTXF3_INEPnTxFStAddr_Pos (0)                                             /*!< HSUSBD_T::DIEPTXF3: INEPnTxFStAddr Position*/
#define HSUSBD_DIEPTXF3_INEPnTxFStAddr_Msk (0x3fful << HSUSBD_DIEPTXF3_INEPnTxFStAddr_Pos) /*!< HSUSBD_T::DIEPTXF3: INEPnTxFStAddr Mask*/

#define HSUSBD_DIEPTXF3_INEPnTxFDep_Pos  (16)                                              /*!< HSUSBD_T::DIEPTXF3: INEPnTxFDep Position*/
#define HSUSBD_DIEPTXF3_INEPnTxFDep_Msk  (0x1fful << HSUSBD_DIEPTXF3_INEPnTxFDep_Pos)      /*!< HSUSBD_T::DIEPTXF3: INEPnTxFDep Mask   */

#define HSUSBD_DIEPTXF4_INEPnTxFStAddr_Pos (0)                                             /*!< HSUSBD_T::DIEPTXF4: INEPnTxFStAddr Position*/
#define HSUSBD_DIEPTXF4_INEPnTxFStAddr_Msk (0x7fful << HSUSBD_DIEPTXF4_INEPnTxFStAddr_Pos) /*!< HSUSBD_T::DIEPTXF4: INEPnTxFStAddr Mask*/

#define HSUSBD_DIEPTXF4_INEPnTxFDep_Pos  (16)                                              /*!< HSUSBD_T::DIEPTXF4: INEPnTxFDep Position*/
#define HSUSBD_DIEPTXF4_INEPnTxFDep_Msk  (0x1fful << HSUSBD_DIEPTXF4_INEPnTxFDep_Pos)      /*!< HSUSBD_T::DIEPTXF4: INEPnTxFDep Mask   */

#define HSUSBD_DIEPTXF5_INEPnTxFStAddr_Pos (0)                                             /*!< HSUSBD_T::DIEPTXF5: INEPnTxFStAddr Position*/
#define HSUSBD_DIEPTXF5_INEPnTxFStAddr_Msk (0x7fful << HSUSBD_DIEPTXF5_INEPnTxFStAddr_Pos) /*!< HSUSBD_T::DIEPTXF5: INEPnTxFStAddr Mask*/

#define HSUSBD_DIEPTXF5_INEPnTxFDep_Pos  (16)                                              /*!< HSUSBD_T::DIEPTXF5: INEPnTxFDep Position*/
#define HSUSBD_DIEPTXF5_INEPnTxFDep_Msk  (0x1fful << HSUSBD_DIEPTXF5_INEPnTxFDep_Pos)      /*!< HSUSBD_T::DIEPTXF5: INEPnTxFDep Mask   */

#define HSUSBD_DIEPTXF6_INEPnTxFStAddr_Pos (0)                                             /*!< HSUSBD_T::DIEPTXF6: INEPnTxFStAddr Position*/
#define HSUSBD_DIEPTXF6_INEPnTxFStAddr_Msk (0x7fful << HSUSBD_DIEPTXF6_INEPnTxFStAddr_Pos) /*!< HSUSBD_T::DIEPTXF6: INEPnTxFStAddr Mask*/

#define HSUSBD_DIEPTXF6_INEPnTxFDep_Pos  (16)                                              /*!< HSUSBD_T::DIEPTXF6: INEPnTxFDep Position*/
#define HSUSBD_DIEPTXF6_INEPnTxFDep_Msk  (0x1fful << HSUSBD_DIEPTXF6_INEPnTxFDep_Pos)      /*!< HSUSBD_T::DIEPTXF6: INEPnTxFDep Mask   */

#define HSUSBD_DIEPTXF7_INEPnTxFStAddr_Pos (0)                                             /*!< HSUSBD_T::DIEPTXF7: INEPnTxFStAddr Position*/
#define HSUSBD_DIEPTXF7_INEPnTxFStAddr_Msk (0x7fful << HSUSBD_DIEPTXF7_INEPnTxFStAddr_Pos) /*!< HSUSBD_T::DIEPTXF7: INEPnTxFStAddr Mask*/

#define HSUSBD_DIEPTXF7_INEPnTxFDep_Pos  (16)                                              /*!< HSUSBD_T::DIEPTXF7: INEPnTxFDep Position*/
#define HSUSBD_DIEPTXF7_INEPnTxFDep_Msk  (0x1fful << HSUSBD_DIEPTXF7_INEPnTxFDep_Pos)      /*!< HSUSBD_T::DIEPTXF7: INEPnTxFDep Mask   */

#define HSUSBD_DIEPTXF8_INEPnTxFStAddr_Pos (0)                                             /*!< HSUSBD_T::DIEPTXF8: INEPnTxFStAddr Position*/
#define HSUSBD_DIEPTXF8_INEPnTxFStAddr_Msk (0xffful << HSUSBD_DIEPTXF8_INEPnTxFStAddr_Pos) /*!< HSUSBD_T::DIEPTXF8: INEPnTxFStAddr Mask*/

#define HSUSBD_DIEPTXF8_INEPnTxFDep_Pos  (16)                                              /*!< HSUSBD_T::DIEPTXF8: INEPnTxFDep Position*/
#define HSUSBD_DIEPTXF8_INEPnTxFDep_Msk  (0x1fful << HSUSBD_DIEPTXF8_INEPnTxFDep_Pos)      /*!< HSUSBD_T::DIEPTXF8: INEPnTxFDep Mask   */

#define HSUSBD_DCFG_DevSpd_Pos           (0)                                               /*!< HSUSBD_T::DCFG: DevSpd Position        */
#define HSUSBD_DCFG_DevSpd_Msk           (0x3ul << HSUSBD_DCFG_DevSpd_Pos)                 /*!< HSUSBD_T::DCFG: DevSpd Mask            */

#define HSUSBD_DCFG_NZStsOUTHShk_Pos     (2)                                               /*!< HSUSBD_T::DCFG: NZStsOUTHShk Position  */
#define HSUSBD_DCFG_NZStsOUTHShk_Msk     (0x1ul << HSUSBD_DCFG_NZStsOUTHShk_Pos)           /*!< HSUSBD_T::DCFG: NZStsOUTHShk Mask      */

#define HSUSBD_DCFG_DevAddr_Pos          (4)                                               /*!< HSUSBD_T::DCFG: DevAddr Position       */
#define HSUSBD_DCFG_DevAddr_Msk          (0x7ful << HSUSBD_DCFG_DevAddr_Pos)               /*!< HSUSBD_T::DCFG: DevAddr Mask           */

#define HSUSBD_DCFG_PerFrInt_Pos         (11)                                              /*!< HSUSBD_T::DCFG: PerFrInt Position      */
#define HSUSBD_DCFG_PerFrInt_Msk         (0x3ul << HSUSBD_DCFG_PerFrInt_Pos)               /*!< HSUSBD_T::DCFG: PerFrInt Mask          */

#define HSUSBD_DCFG_EnDevOutNak_Pos      (13)                                              /*!< HSUSBD_T::DCFG: EnDevOutNak Position   */
#define HSUSBD_DCFG_EnDevOutNak_Msk      (0x1ul << HSUSBD_DCFG_EnDevOutNak_Pos)            /*!< HSUSBD_T::DCFG: EnDevOutNak Mask       */

#define HSUSBD_DCFG_XCVRDLY_Pos          (14)                                              /*!< HSUSBD_T::DCFG: XCVRDLY Position       */
#define HSUSBD_DCFG_XCVRDLY_Msk          (0x1ul << HSUSBD_DCFG_XCVRDLY_Pos)                /*!< HSUSBD_T::DCFG: XCVRDLY Mask           */

#define HSUSBD_DCFG_ErraticIntMsk_Pos    (15)                                              /*!< HSUSBD_T::DCFG: ErraticIntMsk Position */
#define HSUSBD_DCFG_ErraticIntMsk_Msk    (0x1ul << HSUSBD_DCFG_ErraticIntMsk_Pos)          /*!< HSUSBD_T::DCFG: ErraticIntMsk Mask     */

#define HSUSBD_DCFG_ipgisocSupt_Pos      (17)                                              /*!< HSUSBD_T::DCFG: ipgisocSupt Position   */
#define HSUSBD_DCFG_ipgisocSupt_Msk      (0x1ul << HSUSBD_DCFG_ipgisocSupt_Pos)            /*!< HSUSBD_T::DCFG: ipgisocSupt Mask       */

#define HSUSBD_DCFG_DescDMA_Pos          (23)                                              /*!< HSUSBD_T::DCFG: DescDMA Position       */
#define HSUSBD_DCFG_DescDMA_Msk          (0x1ul << HSUSBD_DCFG_DescDMA_Pos)                /*!< HSUSBD_T::DCFG: DescDMA Mask           */

#define HSUSBD_DCFG_PerSchIntvl_Pos      (24)                                              /*!< HSUSBD_T::DCFG: PerSchIntvl Position   */
#define HSUSBD_DCFG_PerSchIntvl_Msk      (0x3ul << HSUSBD_DCFG_PerSchIntvl_Pos)            /*!< HSUSBD_T::DCFG: PerSchIntvl Mask       */

#define HSUSBD_DCFG_ResValid_Pos         (26)                                              /*!< HSUSBD_T::DCFG: ResValid Position      */
#define HSUSBD_DCFG_ResValid_Msk         (0x3ful << HSUSBD_DCFG_ResValid_Pos)              /*!< HSUSBD_T::DCFG: ResValid Mask          */

#define HSUSBD_DCTL_RmtWkUpSig_Pos       (0)                                               /*!< HSUSBD_T::DCTL: RmtWkUpSig Position    */
#define HSUSBD_DCTL_RmtWkUpSig_Msk       (0x1ul << HSUSBD_DCTL_RmtWkUpSig_Pos)             /*!< HSUSBD_T::DCTL: RmtWkUpSig Mask        */

#define HSUSBD_DCTL_SftDiscon_Pos        (1)                                               /*!< HSUSBD_T::DCTL: SftDiscon Position     */
#define HSUSBD_DCTL_SftDiscon_Msk        (0x1ul << HSUSBD_DCTL_SftDiscon_Pos)              /*!< HSUSBD_T::DCTL: SftDiscon Mask         */

#define HSUSBD_DCTL_GNPINNakSts_Pos      (2)                                               /*!< HSUSBD_T::DCTL: GNPINNakSts Position   */
#define HSUSBD_DCTL_GNPINNakSts_Msk      (0x1ul << HSUSBD_DCTL_GNPINNakSts_Pos)            /*!< HSUSBD_T::DCTL: GNPINNakSts Mask       */

#define HSUSBD_DCTL_GOUTNakSts_Pos       (3)                                               /*!< HSUSBD_T::DCTL: GOUTNakSts Position    */
#define HSUSBD_DCTL_GOUTNakSts_Msk       (0x1ul << HSUSBD_DCTL_GOUTNakSts_Pos)             /*!< HSUSBD_T::DCTL: GOUTNakSts Mask        */

#define HSUSBD_DCTL_TstCtl_Pos           (4)                                               /*!< HSUSBD_T::DCTL: TstCtl Position        */
#define HSUSBD_DCTL_TstCtl_Msk           (0x7ul << HSUSBD_DCTL_TstCtl_Pos)                 /*!< HSUSBD_T::DCTL: TstCtl Mask            */

#define HSUSBD_DCTL_SGNPInNak_Pos        (7)                                               /*!< HSUSBD_T::DCTL: SGNPInNak Position     */
#define HSUSBD_DCTL_SGNPInNak_Msk        (0x1ul << HSUSBD_DCTL_SGNPInNak_Pos)              /*!< HSUSBD_T::DCTL: SGNPInNak Mask         */

#define HSUSBD_DCTL_CGNPInNak_Pos        (8)                                               /*!< HSUSBD_T::DCTL: CGNPInNak Position     */
#define HSUSBD_DCTL_CGNPInNak_Msk        (0x1ul << HSUSBD_DCTL_CGNPInNak_Pos)              /*!< HSUSBD_T::DCTL: CGNPInNak Mask         */

#define HSUSBD_DCTL_SGOUTNak_Pos         (9)                                               /*!< HSUSBD_T::DCTL: SGOUTNak Position      */
#define HSUSBD_DCTL_SGOUTNak_Msk         (0x1ul << HSUSBD_DCTL_SGOUTNak_Pos)               /*!< HSUSBD_T::DCTL: SGOUTNak Mask          */

#define HSUSBD_DCTL_CGOUTNak_Pos         (10)                                              /*!< HSUSBD_T::DCTL: CGOUTNak Position      */
#define HSUSBD_DCTL_CGOUTNak_Msk         (0x1ul << HSUSBD_DCTL_CGOUTNak_Pos)               /*!< HSUSBD_T::DCTL: CGOUTNak Mask          */

#define HSUSBD_DCTL_PWROnPrgDone_Pos     (11)                                              /*!< HSUSBD_T::DCTL: PWROnPrgDone Position  */
#define HSUSBD_DCTL_PWROnPrgDone_Msk     (0x1ul << HSUSBD_DCTL_PWROnPrgDone_Pos)           /*!< HSUSBD_T::DCTL: PWROnPrgDone Mask      */

#define HSUSBD_DCTL_GMC_Pos              (13)                                              /*!< HSUSBD_T::DCTL: GMC Position           */
#define HSUSBD_DCTL_GMC_Msk              (0x3ul << HSUSBD_DCTL_GMC_Pos)                    /*!< HSUSBD_T::DCTL: GMC Mask               */

#define HSUSBD_DCTL_IgnrFrmNum_Pos       (15)                                              /*!< HSUSBD_T::DCTL: IgnrFrmNum Position    */
#define HSUSBD_DCTL_IgnrFrmNum_Msk       (0x1ul << HSUSBD_DCTL_IgnrFrmNum_Pos)             /*!< HSUSBD_T::DCTL: IgnrFrmNum Mask        */

#define HSUSBD_DCTL_NakOnBble_Pos        (16)                                              /*!< HSUSBD_T::DCTL: NakOnBble Position     */
#define HSUSBD_DCTL_NakOnBble_Msk        (0x1ul << HSUSBD_DCTL_NakOnBble_Pos)              /*!< HSUSBD_T::DCTL: NakOnBble Mask         */

#define HSUSBD_DCTL_EnContOnBNA_Pos      (17)                                              /*!< HSUSBD_T::DCTL: EnContOnBNA Position   */
#define HSUSBD_DCTL_EnContOnBNA_Msk      (0x1ul << HSUSBD_DCTL_EnContOnBNA_Pos)            /*!< HSUSBD_T::DCTL: EnContOnBNA Mask       */

#define HSUSBD_DCTL_DeepSleepBESLReject_Pos (18)                                           /*!< HSUSBD_T::DCTL: DeepSleepBESLReject Position*/
#define HSUSBD_DCTL_DeepSleepBESLReject_Msk (0x1ul << HSUSBD_DCTL_DeepSleepBESLReject_Pos) /*!< HSUSBD_T::DCTL: DeepSleepBESLReject Mask*/

#define HSUSBD_DCTL_ServInt_Pos          (19)                                              /*!< HSUSBD_T::DCTL: ServInt Position       */
#define HSUSBD_DCTL_ServInt_Msk          (0x1ul << HSUSBD_DCTL_ServInt_Pos)                /*!< HSUSBD_T::DCTL: ServInt Mask           */

#define HSUSBD_DSTS_SuspSts_Pos          (0)                                               /*!< HSUSBD_T::DSTS: SuspSts Position       */
#define HSUSBD_DSTS_SuspSts_Msk          (0x1ul << HSUSBD_DSTS_SuspSts_Pos)                /*!< HSUSBD_T::DSTS: SuspSts Mask           */

#define HSUSBD_DSTS_EnumSpd_Pos          (1)                                               /*!< HSUSBD_T::DSTS: EnumSpd Position       */
#define HSUSBD_DSTS_EnumSpd_Msk          (0x3ul << HSUSBD_DSTS_EnumSpd_Pos)                /*!< HSUSBD_T::DSTS: EnumSpd Mask           */

#define HSUSBD_DSTS_ErrticErr_Pos        (3)                                               /*!< HSUSBD_T::DSTS: ErrticErr Position     */
#define HSUSBD_DSTS_ErrticErr_Msk        (0x1ul << HSUSBD_DSTS_ErrticErr_Pos)              /*!< HSUSBD_T::DSTS: ErrticErr Mask         */

#define HSUSBD_DSTS_SOFFN_Pos            (8)                                               /*!< HSUSBD_T::DSTS: SOFFN Position         */
#define HSUSBD_DSTS_SOFFN_Msk            (0x3ffful << HSUSBD_DSTS_SOFFN_Pos)               /*!< HSUSBD_T::DSTS: SOFFN Mask             */

#define HSUSBD_DSTS_DevLnSts_Pos         (22)                                              /*!< HSUSBD_T::DSTS: DevLnSts Position      */
#define HSUSBD_DSTS_DevLnSts_Msk         (0x3ul << HSUSBD_DSTS_DevLnSts_Pos)               /*!< HSUSBD_T::DSTS: DevLnSts Mask          */

#define HSUSBD_DIEPMSK_XferComplMsk_Pos  (0)                                               /*!< HSUSBD_T::DIEPMSK: XferComplMsk Position*/
#define HSUSBD_DIEPMSK_XferComplMsk_Msk  (0x1ul << HSUSBD_DIEPMSK_XferComplMsk_Pos)        /*!< HSUSBD_T::DIEPMSK: XferComplMsk Mask   */

#define HSUSBD_DIEPMSK_EPDisbldMsk_Pos   (1)                                               /*!< HSUSBD_T::DIEPMSK: EPDisbldMsk Position*/
#define HSUSBD_DIEPMSK_EPDisbldMsk_Msk   (0x1ul << HSUSBD_DIEPMSK_EPDisbldMsk_Pos)         /*!< HSUSBD_T::DIEPMSK: EPDisbldMsk Mask    */

#define HSUSBD_DIEPMSK_AHBErrMsk_Pos     (2)                                               /*!< HSUSBD_T::DIEPMSK: AHBErrMsk Position  */
#define HSUSBD_DIEPMSK_AHBErrMsk_Msk     (0x1ul << HSUSBD_DIEPMSK_AHBErrMsk_Pos)           /*!< HSUSBD_T::DIEPMSK: AHBErrMsk Mask      */

#define HSUSBD_DIEPMSK_TimeOUTMsk_Pos    (3)                                               /*!< HSUSBD_T::DIEPMSK: TimeOUTMsk Position */
#define HSUSBD_DIEPMSK_TimeOUTMsk_Msk    (0x1ul << HSUSBD_DIEPMSK_TimeOUTMsk_Pos)          /*!< HSUSBD_T::DIEPMSK: TimeOUTMsk Mask     */

#define HSUSBD_DIEPMSK_INTknTXFEmpMsk_Pos (4)                                              /*!< HSUSBD_T::DIEPMSK: INTknTXFEmpMsk Position*/
#define HSUSBD_DIEPMSK_INTknTXFEmpMsk_Msk (0x1ul << HSUSBD_DIEPMSK_INTknTXFEmpMsk_Pos)     /*!< HSUSBD_T::DIEPMSK: INTknTXFEmpMsk Mask */

#define HSUSBD_DIEPMSK_INTknEPMisMsk_Pos (5)                                               /*!< HSUSBD_T::DIEPMSK: INTknEPMisMsk Position*/
#define HSUSBD_DIEPMSK_INTknEPMisMsk_Msk (0x1ul << HSUSBD_DIEPMSK_INTknEPMisMsk_Pos)       /*!< HSUSBD_T::DIEPMSK: INTknEPMisMsk Mask  */

#define HSUSBD_DIEPMSK_INEPNakEffMsk_Pos (6)                                               /*!< HSUSBD_T::DIEPMSK: INEPNakEffMsk Position*/
#define HSUSBD_DIEPMSK_INEPNakEffMsk_Msk (0x1ul << HSUSBD_DIEPMSK_INEPNakEffMsk_Pos)       /*!< HSUSBD_T::DIEPMSK: INEPNakEffMsk Mask  */

#define HSUSBD_DIEPMSK_TxfifoUndrnMsk_Pos (8)                                              /*!< HSUSBD_T::DIEPMSK: TxfifoUndrnMsk Position*/
#define HSUSBD_DIEPMSK_TxfifoUndrnMsk_Msk (0x1ul << HSUSBD_DIEPMSK_TxfifoUndrnMsk_Pos)     /*!< HSUSBD_T::DIEPMSK: TxfifoUndrnMsk Mask */

#define HSUSBD_DIEPMSK_BNAInIntrMsk_Pos  (9)                                               /*!< HSUSBD_T::DIEPMSK: BNAInIntrMsk Position*/
#define HSUSBD_DIEPMSK_BNAInIntrMsk_Msk  (0x1ul << HSUSBD_DIEPMSK_BNAInIntrMsk_Pos)        /*!< HSUSBD_T::DIEPMSK: BNAInIntrMsk Mask   */

#define HSUSBD_DIEPMSK_NAKMsk_Pos        (13)                                              /*!< HSUSBD_T::DIEPMSK: NAKMsk Position     */
#define HSUSBD_DIEPMSK_NAKMsk_Msk        (0x1ul << HSUSBD_DIEPMSK_NAKMsk_Pos)              /*!< HSUSBD_T::DIEPMSK: NAKMsk Mask         */

#define HSUSBD_DOEPMSK_XferComplMsk_Pos  (0)                                               /*!< HSUSBD_T::DOEPMSK: XferComplMsk Position*/
#define HSUSBD_DOEPMSK_XferComplMsk_Msk  (0x1ul << HSUSBD_DOEPMSK_XferComplMsk_Pos)        /*!< HSUSBD_T::DOEPMSK: XferComplMsk Mask   */

#define HSUSBD_DOEPMSK_EPDisbldMsk_Pos   (1)                                               /*!< HSUSBD_T::DOEPMSK: EPDisbldMsk Position*/
#define HSUSBD_DOEPMSK_EPDisbldMsk_Msk   (0x1ul << HSUSBD_DOEPMSK_EPDisbldMsk_Pos)         /*!< HSUSBD_T::DOEPMSK: EPDisbldMsk Mask    */

#define HSUSBD_DOEPMSK_AHBErrMsk_Pos     (2)                                               /*!< HSUSBD_T::DOEPMSK: AHBErrMsk Position  */
#define HSUSBD_DOEPMSK_AHBErrMsk_Msk     (0x1ul << HSUSBD_DOEPMSK_AHBErrMsk_Pos)           /*!< HSUSBD_T::DOEPMSK: AHBErrMsk Mask      */

#define HSUSBD_DOEPMSK_SetUPMsk_Pos      (3)                                               /*!< HSUSBD_T::DOEPMSK: SetUPMsk Position   */
#define HSUSBD_DOEPMSK_SetUPMsk_Msk      (0x1ul << HSUSBD_DOEPMSK_SetUPMsk_Pos)            /*!< HSUSBD_T::DOEPMSK: SetUPMsk Mask       */

#define HSUSBD_DOEPMSK_OUTTknEPdisMsk_Pos (4)                                              /*!< HSUSBD_T::DOEPMSK: OUTTknEPdisMsk Position*/
#define HSUSBD_DOEPMSK_OUTTknEPdisMsk_Msk (0x1ul << HSUSBD_DOEPMSK_OUTTknEPdisMsk_Pos)     /*!< HSUSBD_T::DOEPMSK: OUTTknEPdisMsk Mask */

#define HSUSBD_DOEPMSK_StsPhseRcvdMsk_Pos (5)                                              /*!< HSUSBD_T::DOEPMSK: StsPhseRcvdMsk Position*/
#define HSUSBD_DOEPMSK_StsPhseRcvdMsk_Msk (0x1ul << HSUSBD_DOEPMSK_StsPhseRcvdMsk_Pos)     /*!< HSUSBD_T::DOEPMSK: StsPhseRcvdMsk Mask */

#define HSUSBD_DOEPMSK_Back2BackSETup_Pos (6)                                              /*!< HSUSBD_T::DOEPMSK: Back2BackSETup Position*/
#define HSUSBD_DOEPMSK_Back2BackSETup_Msk (0x1ul << HSUSBD_DOEPMSK_Back2BackSETup_Pos)     /*!< HSUSBD_T::DOEPMSK: Back2BackSETup Mask */

#define HSUSBD_DOEPMSK_OutPktErrMsk_Pos  (8)                                               /*!< HSUSBD_T::DOEPMSK: OutPktErrMsk Position*/
#define HSUSBD_DOEPMSK_OutPktErrMsk_Msk  (0x1ul << HSUSBD_DOEPMSK_OutPktErrMsk_Pos)        /*!< HSUSBD_T::DOEPMSK: OutPktErrMsk Mask   */

#define HSUSBD_DOEPMSK_BnaOutIntrMsk_Pos (9)                                               /*!< HSUSBD_T::DOEPMSK: BnaOutIntrMsk Position*/
#define HSUSBD_DOEPMSK_BnaOutIntrMsk_Msk (0x1ul << HSUSBD_DOEPMSK_BnaOutIntrMsk_Pos)       /*!< HSUSBD_T::DOEPMSK: BnaOutIntrMsk Mask  */

#define HSUSBD_DOEPMSK_BbleErrMsk_Pos    (12)                                              /*!< HSUSBD_T::DOEPMSK: BbleErrMsk Position */
#define HSUSBD_DOEPMSK_BbleErrMsk_Msk    (0x1ul << HSUSBD_DOEPMSK_BbleErrMsk_Pos)          /*!< HSUSBD_T::DOEPMSK: BbleErrMsk Mask     */

#define HSUSBD_DOEPMSK_NAKMsk_Pos        (13)                                              /*!< HSUSBD_T::DOEPMSK: NAKMsk Position     */
#define HSUSBD_DOEPMSK_NAKMsk_Msk        (0x1ul << HSUSBD_DOEPMSK_NAKMsk_Pos)              /*!< HSUSBD_T::DOEPMSK: NAKMsk Mask         */

#define HSUSBD_DOEPMSK_NYETMsk_Pos       (14)                                              /*!< HSUSBD_T::DOEPMSK: NYETMsk Position    */
#define HSUSBD_DOEPMSK_NYETMsk_Msk       (0x1ul << HSUSBD_DOEPMSK_NYETMsk_Pos)             /*!< HSUSBD_T::DOEPMSK: NYETMsk Mask        */

#define HSUSBD_DAINT_InEpInt0_Pos        (0)                                               /*!< HSUSBD_T::DAINT: InEpInt0 Position     */
#define HSUSBD_DAINT_InEpInt0_Msk        (0x1ul << HSUSBD_DAINT_InEpInt0_Pos)              /*!< HSUSBD_T::DAINT: InEpInt0 Mask         */

#define HSUSBD_DAINT_InEpInt1_Pos        (1)                                               /*!< HSUSBD_T::DAINT: InEpInt1 Position     */
#define HSUSBD_DAINT_InEpInt1_Msk        (0x1ul << HSUSBD_DAINT_InEpInt1_Pos)              /*!< HSUSBD_T::DAINT: InEpInt1 Mask         */

#define HSUSBD_DAINT_InEpInt2_Pos        (2)                                               /*!< HSUSBD_T::DAINT: InEpInt2 Position     */
#define HSUSBD_DAINT_InEpInt2_Msk        (0x1ul << HSUSBD_DAINT_InEpInt2_Pos)              /*!< HSUSBD_T::DAINT: InEpInt2 Mask         */

#define HSUSBD_DAINT_InEpInt3_Pos        (3)                                               /*!< HSUSBD_T::DAINT: InEpInt3 Position     */
#define HSUSBD_DAINT_InEpInt3_Msk        (0x1ul << HSUSBD_DAINT_InEpInt3_Pos)              /*!< HSUSBD_T::DAINT: InEpInt3 Mask         */

#define HSUSBD_DAINT_InEpInt4_Pos        (4)                                               /*!< HSUSBD_T::DAINT: InEpInt4 Position     */
#define HSUSBD_DAINT_InEpInt4_Msk        (0x1ul << HSUSBD_DAINT_InEpInt4_Pos)              /*!< HSUSBD_T::DAINT: InEpInt4 Mask         */

#define HSUSBD_DAINT_InEpInt5_Pos        (5)                                               /*!< HSUSBD_T::DAINT: InEpInt5 Position     */
#define HSUSBD_DAINT_InEpInt5_Msk        (0x1ul << HSUSBD_DAINT_InEpInt5_Pos)              /*!< HSUSBD_T::DAINT: InEpInt5 Mask         */

#define HSUSBD_DAINT_InEpInt6_Pos        (6)                                               /*!< HSUSBD_T::DAINT: InEpInt6 Position     */
#define HSUSBD_DAINT_InEpInt6_Msk        (0x1ul << HSUSBD_DAINT_InEpInt6_Pos)              /*!< HSUSBD_T::DAINT: InEpInt6 Mask         */

#define HSUSBD_DAINT_InEpInt7_Pos        (7)                                               /*!< HSUSBD_T::DAINT: InEpInt7 Position     */
#define HSUSBD_DAINT_InEpInt7_Msk        (0x1ul << HSUSBD_DAINT_InEpInt7_Pos)              /*!< HSUSBD_T::DAINT: InEpInt7 Mask         */

#define HSUSBD_DAINT_InEpInt8_Pos        (8)                                               /*!< HSUSBD_T::DAINT: InEpInt8 Position     */
#define HSUSBD_DAINT_InEpInt8_Msk        (0x1ul << HSUSBD_DAINT_InEpInt8_Pos)              /*!< HSUSBD_T::DAINT: InEpInt8 Mask         */

#define HSUSBD_DAINT_OutEPInt0_Pos       (16)                                              /*!< HSUSBD_T::DAINT: OutEPInt0 Position    */
#define HSUSBD_DAINT_OutEPInt0_Msk       (0x1ul << HSUSBD_DAINT_OutEPInt0_Pos)             /*!< HSUSBD_T::DAINT: OutEPInt0 Mask        */

#define HSUSBD_DAINT_OutEPInt1_Pos       (17)                                              /*!< HSUSBD_T::DAINT: OutEPInt1 Position    */
#define HSUSBD_DAINT_OutEPInt1_Msk       (0x1ul << HSUSBD_DAINT_OutEPInt1_Pos)             /*!< HSUSBD_T::DAINT: OutEPInt1 Mask        */

#define HSUSBD_DAINT_OutEPInt2_Pos       (18)                                              /*!< HSUSBD_T::DAINT: OutEPInt2 Position    */
#define HSUSBD_DAINT_OutEPInt2_Msk       (0x1ul << HSUSBD_DAINT_OutEPInt2_Pos)             /*!< HSUSBD_T::DAINT: OutEPInt2 Mask        */

#define HSUSBD_DAINT_OutEPInt3_Pos       (19)                                              /*!< HSUSBD_T::DAINT: OutEPInt3 Position    */
#define HSUSBD_DAINT_OutEPInt3_Msk       (0x1ul << HSUSBD_DAINT_OutEPInt3_Pos)             /*!< HSUSBD_T::DAINT: OutEPInt3 Mask        */

#define HSUSBD_DAINT_OutEPInt4_Pos       (20)                                              /*!< HSUSBD_T::DAINT: OutEPInt4 Position    */
#define HSUSBD_DAINT_OutEPInt4_Msk       (0x1ul << HSUSBD_DAINT_OutEPInt4_Pos)             /*!< HSUSBD_T::DAINT: OutEPInt4 Mask        */

#define HSUSBD_DAINT_OutEPInt5_Pos       (21)                                              /*!< HSUSBD_T::DAINT: OutEPInt5 Position    */
#define HSUSBD_DAINT_OutEPInt5_Msk       (0x1ul << HSUSBD_DAINT_OutEPInt5_Pos)             /*!< HSUSBD_T::DAINT: OutEPInt5 Mask        */

#define HSUSBD_DAINT_OutEPInt6_Pos       (22)                                              /*!< HSUSBD_T::DAINT: OutEPInt6 Position    */
#define HSUSBD_DAINT_OutEPInt6_Msk       (0x1ul << HSUSBD_DAINT_OutEPInt6_Pos)             /*!< HSUSBD_T::DAINT: OutEPInt6 Mask        */

#define HSUSBD_DAINT_OutEPInt7_Pos       (23)                                              /*!< HSUSBD_T::DAINT: OutEPInt7 Position    */
#define HSUSBD_DAINT_OutEPInt7_Msk       (0x1ul << HSUSBD_DAINT_OutEPInt7_Pos)             /*!< HSUSBD_T::DAINT: OutEPInt7 Mask        */

#define HSUSBD_DAINT_OutEPInt8_Pos       (24)                                              /*!< HSUSBD_T::DAINT: OutEPInt8 Position    */
#define HSUSBD_DAINT_OutEPInt8_Msk       (0x1ul << HSUSBD_DAINT_OutEPInt8_Pos)             /*!< HSUSBD_T::DAINT: OutEPInt8 Mask        */

#define HSUSBD_DAINTMSK_InEpMsk0_Pos     (0)                                               /*!< HSUSBD_T::DAINTMSK: InEpMsk0 Position  */
#define HSUSBD_DAINTMSK_InEpMsk0_Msk     (0x1ul << HSUSBD_DAINTMSK_InEpMsk0_Pos)           /*!< HSUSBD_T::DAINTMSK: InEpMsk0 Mask      */

#define HSUSBD_DAINTMSK_InEpMsk1_Pos     (1)                                               /*!< HSUSBD_T::DAINTMSK: InEpMsk1 Position  */
#define HSUSBD_DAINTMSK_InEpMsk1_Msk     (0x1ul << HSUSBD_DAINTMSK_InEpMsk1_Pos)           /*!< HSUSBD_T::DAINTMSK: InEpMsk1 Mask      */

#define HSUSBD_DAINTMSK_InEpMsk2_Pos     (2)                                               /*!< HSUSBD_T::DAINTMSK: InEpMsk2 Position  */
#define HSUSBD_DAINTMSK_InEpMsk2_Msk     (0x1ul << HSUSBD_DAINTMSK_InEpMsk2_Pos)           /*!< HSUSBD_T::DAINTMSK: InEpMsk2 Mask      */

#define HSUSBD_DAINTMSK_InEpMsk3_Pos     (3)                                               /*!< HSUSBD_T::DAINTMSK: InEpMsk3 Position  */
#define HSUSBD_DAINTMSK_InEpMsk3_Msk     (0x1ul << HSUSBD_DAINTMSK_InEpMsk3_Pos)           /*!< HSUSBD_T::DAINTMSK: InEpMsk3 Mask      */

#define HSUSBD_DAINTMSK_InEpMsk4_Pos     (4)                                               /*!< HSUSBD_T::DAINTMSK: InEpMsk4 Position  */
#define HSUSBD_DAINTMSK_InEpMsk4_Msk     (0x1ul << HSUSBD_DAINTMSK_InEpMsk4_Pos)           /*!< HSUSBD_T::DAINTMSK: InEpMsk4 Mask      */

#define HSUSBD_DAINTMSK_InEpMsk5_Pos     (5)                                               /*!< HSUSBD_T::DAINTMSK: InEpMsk5 Position  */
#define HSUSBD_DAINTMSK_InEpMsk5_Msk     (0x1ul << HSUSBD_DAINTMSK_InEpMsk5_Pos)           /*!< HSUSBD_T::DAINTMSK: InEpMsk5 Mask      */

#define HSUSBD_DAINTMSK_InEpMsk6_Pos     (6)                                               /*!< HSUSBD_T::DAINTMSK: InEpMsk6 Position  */
#define HSUSBD_DAINTMSK_InEpMsk6_Msk     (0x1ul << HSUSBD_DAINTMSK_InEpMsk6_Pos)           /*!< HSUSBD_T::DAINTMSK: InEpMsk6 Mask      */

#define HSUSBD_DAINTMSK_InEpMsk7_Pos     (7)                                               /*!< HSUSBD_T::DAINTMSK: InEpMsk7 Position  */
#define HSUSBD_DAINTMSK_InEpMsk7_Msk     (0x1ul << HSUSBD_DAINTMSK_InEpMsk7_Pos)           /*!< HSUSBD_T::DAINTMSK: InEpMsk7 Mask      */

#define HSUSBD_DAINTMSK_InEpMsk8_Pos     (8)                                               /*!< HSUSBD_T::DAINTMSK: InEpMsk8 Position  */
#define HSUSBD_DAINTMSK_InEpMsk8_Msk     (0x1ul << HSUSBD_DAINTMSK_InEpMsk8_Pos)           /*!< HSUSBD_T::DAINTMSK: InEpMsk8 Mask      */

#define HSUSBD_DAINTMSK_OutEPMsk0_Pos    (16)                                              /*!< HSUSBD_T::DAINTMSK: OutEPMsk0 Position */
#define HSUSBD_DAINTMSK_OutEPMsk0_Msk    (0x1ul << HSUSBD_DAINTMSK_OutEPMsk0_Pos)          /*!< HSUSBD_T::DAINTMSK: OutEPMsk0 Mask     */

#define HSUSBD_DAINTMSK_OutEPMsk1_Pos    (17)                                              /*!< HSUSBD_T::DAINTMSK: OutEPMsk1 Position */
#define HSUSBD_DAINTMSK_OutEPMsk1_Msk    (0x1ul << HSUSBD_DAINTMSK_OutEPMsk1_Pos)          /*!< HSUSBD_T::DAINTMSK: OutEPMsk1 Mask     */

#define HSUSBD_DAINTMSK_OutEPMsk2_Pos    (18)                                              /*!< HSUSBD_T::DAINTMSK: OutEPMsk2 Position */
#define HSUSBD_DAINTMSK_OutEPMsk2_Msk    (0x1ul << HSUSBD_DAINTMSK_OutEPMsk2_Pos)          /*!< HSUSBD_T::DAINTMSK: OutEPMsk2 Mask     */

#define HSUSBD_DAINTMSK_OutEPMsk3_Pos    (19)                                              /*!< HSUSBD_T::DAINTMSK: OutEPMsk3 Position */
#define HSUSBD_DAINTMSK_OutEPMsk3_Msk    (0x1ul << HSUSBD_DAINTMSK_OutEPMsk3_Pos)          /*!< HSUSBD_T::DAINTMSK: OutEPMsk3 Mask     */

#define HSUSBD_DAINTMSK_OutEPMsk4_Pos    (20)                                              /*!< HSUSBD_T::DAINTMSK: OutEPMsk4 Position */
#define HSUSBD_DAINTMSK_OutEPMsk4_Msk    (0x1ul << HSUSBD_DAINTMSK_OutEPMsk4_Pos)          /*!< HSUSBD_T::DAINTMSK: OutEPMsk4 Mask     */

#define HSUSBD_DAINTMSK_OutEPMsk5_Pos    (21)                                              /*!< HSUSBD_T::DAINTMSK: OutEPMsk5 Position */
#define HSUSBD_DAINTMSK_OutEPMsk5_Msk    (0x1ul << HSUSBD_DAINTMSK_OutEPMsk5_Pos)          /*!< HSUSBD_T::DAINTMSK: OutEPMsk5 Mask     */

#define HSUSBD_DAINTMSK_OutEPMsk6_Pos    (22)                                              /*!< HSUSBD_T::DAINTMSK: OutEPMsk6 Position */
#define HSUSBD_DAINTMSK_OutEPMsk6_Msk    (0x1ul << HSUSBD_DAINTMSK_OutEPMsk6_Pos)          /*!< HSUSBD_T::DAINTMSK: OutEPMsk6 Mask     */

#define HSUSBD_DAINTMSK_OutEPMsk7_Pos    (23)                                              /*!< HSUSBD_T::DAINTMSK: OutEPMsk7 Position */
#define HSUSBD_DAINTMSK_OutEPMsk7_Msk    (0x1ul << HSUSBD_DAINTMSK_OutEPMsk7_Pos)          /*!< HSUSBD_T::DAINTMSK: OutEPMsk7 Mask     */

#define HSUSBD_DAINTMSK_OutEPMsk8_Pos    (24)                                              /*!< HSUSBD_T::DAINTMSK: OutEPMsk8 Position */
#define HSUSBD_DAINTMSK_OutEPMsk8_Msk    (0x1ul << HSUSBD_DAINTMSK_OutEPMsk8_Pos)          /*!< HSUSBD_T::DAINTMSK: OutEPMsk8 Mask     */

#define HSUSBD_DTHRCTL_NonISOThrEn_Pos   (0)                                               /*!< HSUSBD_T::DTHRCTL: NonISOThrEn Position*/
#define HSUSBD_DTHRCTL_NonISOThrEn_Msk   (0x1ul << HSUSBD_DTHRCTL_NonISOThrEn_Pos)         /*!< HSUSBD_T::DTHRCTL: NonISOThrEn Mask    */

#define HSUSBD_DTHRCTL_ISOThrEn_Pos      (1)                                               /*!< HSUSBD_T::DTHRCTL: ISOThrEn Position   */
#define HSUSBD_DTHRCTL_ISOThrEn_Msk      (0x1ul << HSUSBD_DTHRCTL_ISOThrEn_Pos)            /*!< HSUSBD_T::DTHRCTL: ISOThrEn Mask       */

#define HSUSBD_DTHRCTL_TxThrLen_Pos      (2)                                               /*!< HSUSBD_T::DTHRCTL: TxThrLen Position   */
#define HSUSBD_DTHRCTL_TxThrLen_Msk      (0x1fful << HSUSBD_DTHRCTL_TxThrLen_Pos)          /*!< HSUSBD_T::DTHRCTL: TxThrLen Mask       */

#define HSUSBD_DTHRCTL_AHBThrRatio_Pos   (11)                                              /*!< HSUSBD_T::DTHRCTL: AHBThrRatio Position*/
#define HSUSBD_DTHRCTL_AHBThrRatio_Msk   (0x3ul << HSUSBD_DTHRCTL_AHBThrRatio_Pos)         /*!< HSUSBD_T::DTHRCTL: AHBThrRatio Mask    */

#define HSUSBD_DTHRCTL_RxThrEn_Pos       (16)                                              /*!< HSUSBD_T::DTHRCTL: RxThrEn Position    */
#define HSUSBD_DTHRCTL_RxThrEn_Msk       (0x1ul << HSUSBD_DTHRCTL_RxThrEn_Pos)             /*!< HSUSBD_T::DTHRCTL: RxThrEn Mask        */

#define HSUSBD_DTHRCTL_RxThrLen_Pos      (17)                                              /*!< HSUSBD_T::DTHRCTL: RxThrLen Position   */
#define HSUSBD_DTHRCTL_RxThrLen_Msk      (0x1fful << HSUSBD_DTHRCTL_RxThrLen_Pos)          /*!< HSUSBD_T::DTHRCTL: RxThrLen Mask       */

#define HSUSBD_DTHRCTL_ArbPrkEn_Pos      (27)                                              /*!< HSUSBD_T::DTHRCTL: ArbPrkEn Position   */
#define HSUSBD_DTHRCTL_ArbPrkEn_Msk      (0x1ul << HSUSBD_DTHRCTL_ArbPrkEn_Pos)            /*!< HSUSBD_T::DTHRCTL: ArbPrkEn Mask       */

#define HSUSBD_DIEPEMPMSK_InEpTxfEmpMsk_Pos (0)                                            /*!< HSUSBD_T::DIEPEMPMSK: InEpTxfEmpMsk Position*/
#define HSUSBD_DIEPEMPMSK_InEpTxfEmpMsk_Msk (0xfffful << HSUSBD_DIEPEMPMSK_InEpTxfEmpMsk_Pos) /*!< HSUSBD_T::DIEPEMPMSK: InEpTxfEmpMsk Mask*/

#define HSUSBD_DIEPCTL0_MPS_Pos          (0)                                               /*!< HSUSBD_T::DIEPCTL0: MPS Position       */
#define HSUSBD_DIEPCTL0_MPS_Msk          (0x3ul << HSUSBD_DIEPCTL0_MPS_Pos)                /*!< HSUSBD_T::DIEPCTL0: MPS Mask           */

#define HSUSBD_DIEPCTL_USBActEP_Pos      (15)                                              /*!< HSUSBD_T::DIEPCTL: USBActEP Position   */
#define HSUSBD_DIEPCTL_USBActEP_Msk      (0x1ul << HSUSBD_DIEPCTL_USBActEP_Pos)            /*!< HSUSBD_T::DIEPCTL: USBActEP Mask       */

#define HSUSBD_DIEPCTL_NAKSts_Pos        (17)                                              /*!< HSUSBD_T::DIEPCTL: NAKSts Position     */
#define HSUSBD_DIEPCTL_NAKSts_Msk        (0x1ul << HSUSBD_DIEPCTL_NAKSts_Pos)              /*!< HSUSBD_T::DIEPCTL: NAKSts Mask         */

#define HSUSBD_DIEPCTL_EPType_Pos        (18)                                              /*!< HSUSBD_T::DIEPCTL: EPType Position     */
#define HSUSBD_DIEPCTL_EPType_Msk        (0x3ul << HSUSBD_DIEPCTL_EPType_Pos)              /*!< HSUSBD_T::DIEPCTL: EPType Mask         */

#define HSUSBD_DIEPCTL_Stall_Pos         (21)                                              /*!< HSUSBD_T::DIEPCTL: Stall Position      */
#define HSUSBD_DIEPCTL_Stall_Msk         (0x1ul << HSUSBD_DIEPCTL_Stall_Pos)               /*!< HSUSBD_T::DIEPCTL: Stall Mask         */

#define HSUSBD_DIEPCTL_TxFNum_Pos        (22)                                              /*!< HSUSBD_T::DIEPCTL: TxFNum Position    */
#define HSUSBD_DIEPCTL_TxFNum_Msk        (0xful << HSUSBD_DIEPCTL_TxFNum_Pos)              /*!< HSUSBD_T::DIEPCTL: TxFNum Mask        */

#define HSUSBD_DIEPCTL_CNAK_Pos          (26)                                              /*!< HSUSBD_T::DIEPCTL: CNAK Position      */
#define HSUSBD_DIEPCTL_CNAK_Msk          (0x1ul << HSUSBD_DIEPCTL_CNAK_Pos)                /*!< HSUSBD_T::DIEPCTL: CNAK Mask          */

#define HSUSBD_DIEPCTL_SNAK_Pos          (27)                                              /*!< HSUSBD_T::DIEPCTL: SNAK Position      */
#define HSUSBD_DIEPCTL_SNAK_Msk          (0x1ul << HSUSBD_DIEPCTL_SNAK_Pos)                /*!< HSUSBD_T::DIEPCTL: SNAK Mask          */

#define HSUSBD_DIEPCTL_EPDis_Pos         (30)                                              /*!< HSUSBD_T::DIEPCTL: EPDis Position     */
#define HSUSBD_DIEPCTL_EPDis_Msk         (0x1ul << HSUSBD_DIEPCTL_EPDis_Pos)               /*!< HSUSBD_T::DIEPCTL: EPDis Mask         */

#define HSUSBD_DIEPCTL_EPEna_Pos         (31)                                              /*!< HSUSBD_T::DIEPCTL: EPEna Position     */
#define HSUSBD_DIEPCTL_EPEna_Msk         (0x1ul << HSUSBD_DIEPCTL_EPEna_Pos)               /*!< HSUSBD_T::DIEPCTL: EPEna Mask         */

#define HSUSBD_DIEPINT_XferCompl_Pos     (0)                                               /*!< HSUSBD_T::DIEPINT: XferCompl Position */
#define HSUSBD_DIEPINT_XferCompl_Msk     (0x1ul << HSUSBD_DIEPINT_XferCompl_Pos)           /*!< HSUSBD_T::DIEPINT: XferCompl Mask     */

#define HSUSBD_DIEPINT_EPDisbld_Pos      (1)                                               /*!< HSUSBD_T::DIEPINT: EPDisbld Position  */
#define HSUSBD_DIEPINT_EPDisbld_Msk      (0x1ul << HSUSBD_DIEPINT_EPDisbld_Pos)            /*!< HSUSBD_T::DIEPINT: EPDisbld Mask      */

#define HSUSBD_DIEPINT_AHBErr_Pos        (2)                                               /*!< HSUSBD_T::DIEPINT: AHBErr Position    */
#define HSUSBD_DIEPINT_AHBErr_Msk        (0x1ul << HSUSBD_DIEPINT_AHBErr_Pos)              /*!< HSUSBD_T::DIEPINT: AHBErr Mask        */

#define HSUSBD_DIEPINT_INTknTXFEmp_Pos   (4)                                               /*!< HSUSBD_T::DIEPINT: INTknTXFEmp Position*/
#define HSUSBD_DIEPINT_INTknTXFEmp_Msk   (0x1ul << HSUSBD_DIEPINT_INTknTXFEmp_Pos)         /*!< HSUSBD_T::DIEPINT: INTknTXFEmp Mask   */

#define HSUSBD_DIEPINT_INTknEPMis_Pos    (5)                                               /*!< HSUSBD_T::DIEPINT: INTknEPMis Position*/
#define HSUSBD_DIEPINT_INTknEPMis_Msk    (0x1ul << HSUSBD_DIEPINT_INTknEPMis_Pos)          /*!< HSUSBD_T::DIEPINT: INTknEPMis Mask    */

#define HSUSBD_DIEPINT_INEPNakEff_Pos    (6)                                               /*!< HSUSBD_T::DIEPINT: INEPNakEff Position*/
#define HSUSBD_DIEPINT_INEPNakEff_Msk    (0x1ul << HSUSBD_DIEPINT_INEPNakEff_Pos)          /*!< HSUSBD_T::DIEPINT: INEPNakEff Mask    */

#define HSUSBD_DIEPINT_TxFEmp_Pos        (7)                                               /*!< HSUSBD_T::DIEPINT: TxFEmp Position    */
#define HSUSBD_DIEPINT_TxFEmp_Msk        (0x1ul << HSUSBD_DIEPINT_TxFEmp_Pos)              /*!< HSUSBD_T::DIEPINT: TxFEmp Mask        */

#define HSUSBD_DIEPINT_TxfifoUndrn_Pos   (8)                                               /*!< HSUSBD_T::DIEPINT: TxfifoUndrn Position*/
#define HSUSBD_DIEPINT_TxfifoUndrn_Msk   (0x1ul << HSUSBD_DIEPINT_TxfifoUndrn_Pos)         /*!< HSUSBD_T::DIEPINT: TxfifoUndrn Mask   */

#define HSUSBD_DIEPINT_BNAIntr_Pos       (9)                                               /*!< HSUSBD_T::DIEPINT: BNAIntr Position   */
#define HSUSBD_DIEPINT_BNAIntr_Msk       (0x1ul << HSUSBD_DIEPINT_BNAIntr_Pos)             /*!< HSUSBD_T::DIEPINT: BNAIntr Mask       */

#define HSUSBD_DIEPINT_BbleErr_Pos       (12)                                              /*!< HSUSBD_T::DIEPINT: BbleErr Position   */
#define HSUSBD_DIEPINT_BbleErr_Msk       (0x1ul << HSUSBD_DIEPINT_BbleErr_Pos)             /*!< HSUSBD_T::DIEPINT: BbleErr Mask       */

#define HSUSBD_DIEPINT_NAKIntrpt_Pos     (13)                                              /*!< HSUSBD_T::DIEPINT: NAKIntrpt Position */
#define HSUSBD_DIEPINT_NAKIntrpt_Msk     (0x1ul << HSUSBD_DIEPINT_NAKIntrpt_Pos)           /*!< HSUSBD_T::DIEPINT: NAKIntrpt Mask     */

#define HSUSBD_DIEPINT_NYETIntrpt_Pos    (14)                                              /*!< HSUSBD_T::DIEPINT: NYETIntrpt Position*/
#define HSUSBD_DIEPINT_NYETIntrpt_Msk    (0x1ul << HSUSBD_DIEPINT_NYETIntrpt_Pos)          /*!< HSUSBD_T::DIEPINT: NYETIntrpt Mask    */

#define HSUSBD_DIEPDMA_DMAAddr_Pos       (0)                                               /*!< HSUSBD_T::DIEPDMA: DMAAddr Position   */
#define HSUSBD_DIEPDMA_DMAAddr_Msk       (0xfffffffful << HSUSBD_DIEPDMA_DMAAddr_Pos)      /*!< HSUSBD_T::DIEPDMA: DMAAddr Mask       */

#define HSUSBD_DTXFSTS_INEPTxFSpcAvail_Pos (0)                                             /*!< HSUSBD_T::DTXFSTS: INEPTxFSpcAvail Position*/
#define HSUSBD_DTXFSTS_INEPTxFSpcAvail_Msk (0xfffful << HSUSBD_DTXFSTS_INEPTxFSpcAvail_Pos) /*!< HSUSBD_T::DTXFSTS: INEPTxFSpcAvail Mask*/

#define HSUSBD_DIEPDMAB_DMABufferAddr_Pos (0)                                              /*!< HSUSBD_T::DIEPDMAB: DMABufferAddr Position*/
#define HSUSBD_DIEPDMAB_DMABufferAddr_Msk (0xfffffffful << HSUSBD_DIEPDMAB_DMABufferAddr_Pos) /*!< HSUSBD_T::DIEPDMAB: DMABufferAddr Mask*/

#define HSUSBD_DIEPCTL_MPS_Pos           (0)                                               /*!< HSUSBD_T::DIEPCTL: MPS Position       */
#define HSUSBD_DIEPCTL_MPS_Msk           (0x7fful << HSUSBD_DIEPCTL_MPS_Pos)               /*!< HSUSBD_T::DIEPCTL: MPS Mask           */

#define HSUSBD_DIEPCTL_DPID_Pos          (16)                                              /*!< HSUSBD_T::DIEPCTL: DPID Position      */
#define HSUSBD_DIEPCTL_DPID_Msk          (0x1ul << HSUSBD_DIEPCTL_DPID_Pos)                /*!< HSUSBD_T::DIEPCTL: DPID Mask          */

#define HSUSBD_DOEPCTL0_MPS_Pos          (0)                                               /*!< HSUSBD_T::DOEPCTL0: MPS Position       */
#define HSUSBD_DOEPCTL0_MPS_Msk          (0x3ul << HSUSBD_DOEPCTL0_MPS_Pos)                /*!< HSUSBD_T::DOEPCTL0: MPS Mask           */

#define HSUSBD_DOEPCTL_USBActEP_Pos      (15)                                              /*!< HSUSBD_T::DOEPCTL: USBActEP Position  */
#define HSUSBD_DOEPCTL_USBActEP_Msk      (0x1ul << HSUSBD_DOEPCTL_USBActEP_Pos)            /*!< HSUSBD_T::DOEPCTL: USBActEP Mask      */

#define HSUSBD_DOEPCTL_NAKSts_Pos        (17)                                              /*!< HSUSBD_T::DOEPCTL: NAKSts Position    */
#define HSUSBD_DOEPCTL_NAKSts_Msk        (0x1ul << HSUSBD_DOEPCTL_NAKSts_Pos)              /*!< HSUSBD_T::DOEPCTL: NAKSts Mask        */

#define HSUSBD_DOEPCTL_EPType_Pos        (18)                                              /*!< HSUSBD_T::DOEPCTL: EPType Position    */
#define HSUSBD_DOEPCTL_EPType_Msk        (0x3ul << HSUSBD_DOEPCTL_EPType_Pos)              /*!< HSUSBD_T::DOEPCTL: EPType Mask        */

#define HSUSBD_DOEPCTL_Snp_Pos           (20)                                              /*!< HSUSBD_T::DOEPCTL: Snp Position       */
#define HSUSBD_DOEPCTL_Snp_Msk           (0x1ul << HSUSBD_DOEPCTL_Snp_Pos)                 /*!< HSUSBD_T::DOEPCTL: Snp Mask           */

#define HSUSBD_DOEPCTL_Stall_Pos         (21)                                              /*!< HSUSBD_T::DOEPCTL: Stall Position     */
#define HSUSBD_DOEPCTL_Stall_Msk         (0x1ul << HSUSBD_DOEPCTL_Stall_Pos)               /*!< HSUSBD_T::DOEPCTL: Stall Mask         */

#define HSUSBD_DOEPCTL_CNAK_Pos          (26)                                              /*!< HSUSBD_T::DOEPCTL: CNAK Position      */
#define HSUSBD_DOEPCTL_CNAK_Msk          (0x1ul << HSUSBD_DOEPCTL_CNAK_Pos)                /*!< HSUSBD_T::DOEPCTL: CNAK Mask          */

#define HSUSBD_DOEPCTL_SNAK_Pos          (27)                                              /*!< HSUSBD_T::DOEPCTL: SNAK Position      */
#define HSUSBD_DOEPCTL_SNAK_Msk          (0x1ul << HSUSBD_DOEPCTL_SNAK_Pos)                /*!< HSUSBD_T::DOEPCTL: SNAK Mask          */

#define HSUSBD_DOEPCTL_EPDis_Pos         (30)                                              /*!< HSUSBD_T::DOEPCTL: EPDis Position     */
#define HSUSBD_DOEPCTL_EPDis_Msk         (0x1ul << HSUSBD_DOEPCTL_EPDis_Pos)               /*!< HSUSBD_T::DOEPCTL: EPDis Mask         */

#define HSUSBD_DOEPCTL_EPEna_Pos         (31)                                              /*!< HSUSBD_T::DOEPCTL: EPEna Position     */
#define HSUSBD_DOEPCTL_EPEna_Msk         (0x1ul << HSUSBD_DOEPCTL_EPEna_Pos)               /*!< HSUSBD_T::DOEPCTL: EPEna Mask         */

#define HSUSBD_DOEPINT_XferCompl_Pos     (0)                                               /*!< HSUSBD_T::DOEPINT: XferCompl Position */
#define HSUSBD_DOEPINT_XferCompl_Msk     (0x1ul << HSUSBD_DOEPINT_XferCompl_Pos)           /*!< HSUSBD_T::DOEPINT: XferCompl Mask     */

#define HSUSBD_DOEPINT_EPDisbld_Pos      (1)                                               /*!< HSUSBD_T::DOEPINT: EPDisbld Position  */
#define HSUSBD_DOEPINT_EPDisbld_Msk      (0x1ul << HSUSBD_DOEPINT_EPDisbld_Pos)            /*!< HSUSBD_T::DOEPINT: EPDisbld Mask      */

#define HSUSBD_DOEPINT_AHBErr_Pos        (2)                                               /*!< HSUSBD_T::DOEPINT: AHBErr Position    */
#define HSUSBD_DOEPINT_AHBErr_Msk        (0x1ul << HSUSBD_DOEPINT_AHBErr_Pos)              /*!< HSUSBD_T::DOEPINT: AHBErr Mask        */

#define HSUSBD_DOEPINT_SetUp_Pos         (3)                                               /*!< HSUSBD_T::DOEPINT: SetUp Position     */
#define HSUSBD_DOEPINT_SetUp_Msk         (0x1ul << HSUSBD_DOEPINT_SetUp_Pos)               /*!< HSUSBD_T::DOEPINT: SetUp Mask         */

#define HSUSBD_DOEPINT_OUTTknEPdis_Pos   (4)                                               /*!< HSUSBD_T::DOEPINT: OUTTknEPdis Position*/
#define HSUSBD_DOEPINT_OUTTknEPdis_Msk   (0x1ul << HSUSBD_DOEPINT_OUTTknEPdis_Pos)         /*!< HSUSBD_T::DOEPINT: OUTTknEPdis Mask   */

#define HSUSBD_DOEPINT_StsPhseRcvd_Pos   (5)                                               /*!< HSUSBD_T::DOEPINT: StsPhseRcvd Position*/
#define HSUSBD_DOEPINT_StsPhseRcvd_Msk   (0x1ul << HSUSBD_DOEPINT_StsPhseRcvd_Pos)         /*!< HSUSBD_T::DOEPINT: StsPhseRcvd Mask   */

#define HSUSBD_DOEPINT_Back2BackSETup_Pos (6)                                             /*!< HSUSBD_T::DOEPINT: Back2BackSETup Position*/
#define HSUSBD_DOEPINT_Back2BackSETup_Msk (0x1ul << HSUSBD_DOEPINT_Back2BackSETup_Pos)    /*!< HSUSBD_T::DOEPINT: Back2BackSETup Mask*/

#define HSUSBD_DOEPINT_OutPktErr_Pos     (8)                                               /*!< HSUSBD_T::DOEPINT: OutPktErr Position */
#define HSUSBD_DOEPINT_OutPktErr_Msk     (0x1ul << HSUSBD_DOEPINT_OutPktErr_Pos)           /*!< HSUSBD_T::DOEPINT: OutPktErr Mask     */

#define HSUSBD_DOEPINT_BNAIntr_Pos       (9)                                               /*!< HSUSBD_T::DOEPINT: BNAIntr Position   */
#define HSUSBD_DOEPINT_BNAIntr_Msk       (0x1ul << HSUSBD_DOEPINT_BNAIntr_Pos)             /*!< HSUSBD_T::DOEPINT: BNAIntr Mask       */

#define HSUSBD_DOEPINT_BbleErr_Pos       (12)                                              /*!< HSUSBD_T::DOEPINT: BbleErr Position   */
#define HSUSBD_DOEPINT_BbleErr_Msk       (0x1ul << HSUSBD_DOEPINT_BbleErr_Pos)             /*!< HSUSBD_T::DOEPINT: BbleErr Mask       */

#define HSUSBD_DOEPINT_NAKIntrpt_Pos     (13)                                              /*!< HSUSBD_T::DOEPINT: NAKIntrpt Position */
#define HSUSBD_DOEPINT_NAKIntrpt_Msk     (0x1ul << HSUSBD_DOEPINT_NAKIntrpt_Pos)           /*!< HSUSBD_T::DOEPINT: NAKIntrpt Mask     */

#define HSUSBD_DOEPINT_NYETIntrpt_Pos    (14)                                              /*!< HSUSBD_T::DOEPINT: NYETIntrpt Position*/
#define HSUSBD_DOEPINT_NYETIntrpt_Msk    (0x1ul << HSUSBD_DOEPINT_NYETIntrpt_Pos)          /*!< HSUSBD_T::DOEPINT: NYETIntrpt Mask    */

#define HSUSBD_DOEPDMA_DMAAddr_Pos       (0)                                               /*!< HSUSBD_T::DOEPDMA: DMAAddr Position   */
#define HSUSBD_DOEPDMA_DMAAddr_Msk       (0xfffffffful << HSUSBD_DOEPDMA_DMAAddr_Pos)      /*!< HSUSBD_T::DOEPDMA: DMAAddr Mask       */

#define HSUSBD_DOEPDMAB_DMABufferAddr_Pos (0)                                              /*!< HSUSBD_T::DOEPDMAB: DMABufferAddr Position*/
#define HSUSBD_DOEPDMAB_DMABufferAddr_Msk (0xfffffffful << HSUSBD_DOEPDMAB_DMABufferAddr_Pos) /*!< HSUSBD_T::DOEPDMAB: DMABufferAddr Mask*/

#define HSUSBD_DOEPCTL_MPS_Pos           (0)                                               /*!< HSUSBD_T::DOEPCTL: MPS Position       */
#define HSUSBD_DOEPCTL_MPS_Msk           (0x7fful << HSUSBD_DOEPCTL_MPS_Pos)               /*!< HSUSBD_T::DOEPCTL: MPS Mask           */

#define HSUSBD_DOEPCTL_DPID_Pos          (16)                                              /*!< HSUSBD_T::DOEPCTL: DPID Position      */
#define HSUSBD_DOEPCTL_DPID_Msk          (0x1ul << HSUSBD_DOEPCTL_DPID_Pos)                /*!< HSUSBD_T::DOEPCTL: DPID Mask          */

#define HSUSBD_PCGCCTL_StopPclk_Pos      (0)                                               /*!< HSUSBD_T::PCGCCTL: StopPclk Position   */
#define HSUSBD_PCGCCTL_StopPclk_Msk      (0x1ul << HSUSBD_PCGCCTL_StopPclk_Pos)            /*!< HSUSBD_T::PCGCCTL: StopPclk Mask       */

#define HSUSBD_PCGCCTL_Enbl_L1Gating_Pos (5)                                               /*!< HSUSBD_T::PCGCCTL: Enbl_L1Gating Position*/
#define HSUSBD_PCGCCTL_Enbl_L1Gating_Msk (0x1ul << HSUSBD_PCGCCTL_Enbl_L1Gating_Pos)       /*!< HSUSBD_T::PCGCCTL: Enbl_L1Gating Mask  */

#define HSUSBD_PCGCCTL_PhySleep_Pos      (6)                                               /*!< HSUSBD_T::PCGCCTL: PhySleep Position   */
#define HSUSBD_PCGCCTL_PhySleep_Msk      (0x1ul << HSUSBD_PCGCCTL_PhySleep_Pos)            /*!< HSUSBD_T::PCGCCTL: PhySleep Mask       */

#define HSUSBD_PCGCCTL_L1Suspended_Pos   (7)                                               /*!< HSUSBD_T::PCGCCTL: L1Suspended Position*/
#define HSUSBD_PCGCCTL_L1Suspended_Msk   (0x1ul << HSUSBD_PCGCCTL_L1Suspended_Pos)         /*!< HSUSBD_T::PCGCCTL: L1Suspended Mask    */

#define HSUSBD_PCGCCTL1_GateEN_Pos       (0)                                               /*!< HSUSBD_T::PCGCCTL1: GateEN Position    */
#define HSUSBD_PCGCCTL1_GateEN_Msk       (0x1ul << HSUSBD_PCGCCTL1_GateEN_Pos)             /*!< HSUSBD_T::PCGCCTL1: GateEN Mask        */

#define HSUSBD_PCGCCTL1_counter_Pos      (1)                                               /*!< HSUSBD_T::PCGCCTL1: counter Position   */
#define HSUSBD_PCGCCTL1_counter_Msk      (0x3ul << HSUSBD_PCGCCTL1_counter_Pos)            /*!< HSUSBD_T::PCGCCTL1: counter Mask       */

#define HSUSBD_PCGCCTL1_RAMGateEN_Pos    (3)                                               /*!< HSUSBD_T::PCGCCTL1: RAMGateEN Position */
#define HSUSBD_PCGCCTL1_RAMGateEN_Msk    (0x1ul << HSUSBD_PCGCCTL1_RAMGateEN_Pos)          /*!< HSUSBD_T::PCGCCTL1: RAMGateEN Mask     */

/**@}*/ /* HSUSBD_CONST */
/**@}*/ /* end of HSUSBD register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __HSUSBD_REG_H__ */
