/**************************************************************************//**
 * @file     config.h
 * @version  V1.00
 * @brief    This header file defines the configuration of USB Host library.
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#ifndef  _USBH_CONFIG_H_
#define  _USBH_CONFIG_H_


/// @cond HIDDEN_SYMBOLS

#include <rtthread.h>
#include "N9H30.h"
#include "nu_sys.h"
#include "drv_sys.h"


/*----------------------------------------------------------------------------------------*/
/*   Hardware settings                                                                    */
/*----------------------------------------------------------------------------------------*/
#define HCLK_MHZ               300          /* used for loop-delay. must be larger than
                                               true HCLK clock MHz                        */

#define NON_CACHE_MASK         (0x80000000)

#define ENABLE_OHCI_IRQ()      rt_hw_interrupt_umask(IRQ_OHCI)
#define DISABLE_OHCI_IRQ()     rt_hw_interrupt_mask(IRQ_OHCI)
#define IS_OHCI_IRQ_ENABLED()  ((inpw(REG_AIC_IMR)>>OHCI_IRQn) & 0x1)
#define ENABLE_EHCI_IRQ()      rt_hw_interrupt_umask(IRQ_EHCI)
#define DISABLE_EHCI_IRQ()     rt_hw_interrupt_mask(IRQ_EHCI)
#define IS_EHCI_IRQ_ENABLED()  ((inpw(REG_AIC_IMR)>>EHCI_IRQn) & 0x1)

#define ENABLE_OHCI                         /* Enable OHCI host controller                */
#define ENABLE_EHCI                         /* Enable EHCI host controller                */

#define EHCI_PORT_CNT          2            /* Number of EHCI roothub ports               */
#define OHCI_PORT_CNT          2            /* Number of OHCI roothub ports               */
//#define OHCI_PER_PORT_POWER               /* OHCI root hub per port powered             */

#define OHCI_ISO_DELAY         4            /* preserved number frames while scheduling
                                               OHCI isochronous transfer                  */

#define EHCI_ISO_DELAY         2            /* preserved number of frames while
                                               scheduling EHCI isochronous transfer       */

#define EHCI_ISO_RCLM_RANGE    32           /* When inspecting activated iTD/siTD,
                                               unconditionally reclaim iTD/isTD scheduled
                                               in just elapsed EHCI_ISO_RCLM_RANGE ms.    */

#define MAX_DESC_BUFF_SIZE     4096         /* To hold the configuration descriptor, USB
                                               core will allocate a buffer with this size
                                               for each connected device. USB core does
                                               not release it until device disconnected.  */

/*----------------------------------------------------------------------------------------*/
/*   Memory allocation settings                                                           */
/*----------------------------------------------------------------------------------------*/

#define STATIC_MEMORY_ALLOC    0       /* pre-allocate static memory blocks. No dynamic memory aloocation.
                                          But the maximum number of connected devices and transfers are
                                          limited.  */

#define MAX_UDEV_DRIVER        8       /*!< Maximum number of registered drivers                      */
#define MAX_ALT_PER_IFACE      12      /*!< maximum number of alternative interfaces per interface    */
#define MAX_EP_PER_IFACE       8       /*!< maximum number of endpoints per interface                 */
#define MAX_HUB_DEVICE         8       /*!< Maximum number of hub devices                             */

/* Host controller hardware transfer descriptors memory pool. ED/TD/ITD of OHCI and QH/QTD of EHCI
   are all allocated from this pool. Allocated unit size is determined by MEM_POOL_UNIT_SIZE.
   May allocate one or more units depend on hardware descriptor type.                                 */

#define MEM_POOL_UNIT_SIZE     128     /*!< A fixed hard coding setting. Do not change it!            */
#define MEM_POOL_UNIT_NUM      256     /*!< Increase this or heap size if memory allocate failed.     */

/*----------------------------------------------------------------------------------------*/
/*   Re-defined staff for various compiler                                                */
/*----------------------------------------------------------------------------------------*/
#ifdef __ICCARM__
    #define   __inline    inline
#endif


/*----------------------------------------------------------------------------------------*/
/*   Debug settings                                                                       */
/*----------------------------------------------------------------------------------------*/
#define ENABLE_ERROR_MSG                    /* enable debug messages                      */
#define ENABLE_DEBUG_MSG                    /* enable debug messages                      */
//#define ENABLE_VERBOSE_DEBUG              /* verbos debug messages                      */
//#define DUMP_DESCRIPTOR                   /* dump descriptors                           */

#ifdef ENABLE_ERROR_MSG
    #define USB_error            rt_kprintf
#else
    #define USB_error(...)
#endif

#ifdef ENABLE_DEBUG_MSG
    #define USB_debug            rt_kprintf
    #ifdef ENABLE_VERBOSE_DEBUG
        #define USB_vdebug          rt_kprintf
    #else
        #define USB_vdebug(...)
    #endif
#else
    #define USB_debug(...)
    #define USB_vdebug(...)
#endif


#define   __I     volatile const       /*!< Defines 'read only' permissions */
#define   __IO    volatile             /*!< Defines 'read / write' permissions */


//typedef unsigned int     uint32_t;
//typedef unsigned short   uint16_t;
//typedef unsigned char    uint8_t;



/*---------------------- USB Host Controller -------------------------*/
/**
    @addtogroup USBH USB Host Controller(USBH)
    Memory Mapped Structure for USBH Controller
@{ */

typedef struct
{

    /**
     * @var USBH_T::HcRevision
     * Offset: 0x00  Host Controller Revision Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |REV       |Revision Number
     * |        |          |Indicates the Open HCI Specification revision number implemented by the Hardware
     * |        |          |Host Controller supports 1.1 specification.
     * |        |          |(X.Y = XYh).
     * @var USBH_T::HcControl
     * Offset: 0x04  Host Controller Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |CBSR      |Control Bulk Service Ratio
     * |        |          |This specifies the service ratio between Control and Bulk EDs
     * |        |          |Before processing any of the non-periodic lists, HC must compare the ratio specified with its internal count on how many nonempty Control EDs have been processed, in determining whether to continue serving another Control ED or switching to Bulk EDs
     * |        |          |The internal count will be retained when crossing the frame boundary
     * |        |          |In case of reset, HCD is responsible for restoring this
     * |        |          |Value.
     * |        |          |00 = Number of Control EDs over Bulk EDs served is 1:1.
     * |        |          |01 = Number of Control EDs over Bulk EDs served is 2:1.
     * |        |          |10 = Number of Control EDs over Bulk EDs served is 3:1.
     * |        |          |11 = Number of Control EDs over Bulk EDs served is 4:1.
     * |[2]     |PLE       |Periodic List Enable Bit
     * |        |          |When set, this bit enables processing of the Periodic (interrupt and isochronous) list
     * |        |          |The Host Controller checks this bit prior to attempting any periodic transfers in a frame.
     * |        |          |0 = Processing of the Periodic (Interrupt and Isochronous) list after next SOF (Start-Of-Frame) Disabled.
     * |        |          |1 = Processing of the Periodic (Interrupt and Isochronous) list in the next frame Enabled.
     * |        |          |Note: To enable the processing of the Isochronous list, user has to set both PLE and IE (HcControl[3]) high.
     * |[3]     |IE        |Isochronous List Enable Bit
     * |        |          |Both ISOEn and PLE (HcControl[2]) high enables Host Controller to process the Isochronous list
     * |        |          |Either ISOEn or PLE (HcControl[2]) is low disables Host Controller to process the Isochronous list.
     * |        |          |0 = Processing of the Isochronous list after next SOF (Start-Of-Frame) Disabled.
     * |        |          |1 = Processing of the Isochronous list in the next frame Enabled, if the PLE (HcControl[2]) is high, too.
     * |[4]     |CLE       |Control List Enable Bit
     * |        |          |0 = Processing of the Control list after next SOF (Start-Of-Frame) Disabled.
     * |        |          |1 = Processing of the Control list in the next frame Enabled.
     * |[5]     |BLE       |Bulk List Enable Bit
     * |        |          |0 = Processing of the Bulk list after next SOF (Start-Of-Frame) Disabled.
     * |        |          |1 = Processing of the Bulk list in the next frame Enabled.
     * |[7:6]   |HCFS      |Host Controller Functional State
     * |        |          |This field sets the Host Controller state
     * |        |          |The Controller may force a state change from USBSUSPEND to USBRESUME after detecting resume signaling from a downstream port
     * |        |          |States are:
     * |        |          |00 = USBSUSPEND.
     * |        |          |01 = USBOPERATIONAL.
     * |        |          |10 = USBRESUME.
     * |        |          |11 = USBRESET.
     * @var USBH_T::HcCommandStatus
     * Offset: 0x08  Host Controller Command Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |HCR       |Host Controller Reset
     * |        |          |This bit is set to initiate the software reset of Host Controller
     * |        |          |This bit is cleared by the Host Controller, upon completed of the reset operation.
     * |        |          |This bit, when set, didn't reset the Root Hub and no subsequent reset signaling be asserted to its downstream ports.
     * |        |          |0 = Host Controller is not in software reset state.
     * |        |          |1 = Host Controller is in software reset state.
     * |[1]     |CLF       |Control List Filled
     * |        |          |Set high to indicate there is an active TD on the Control List
     * |        |          |It may be set by either software or the Host Controller and cleared by the Host Controller each time it begins processing the head of the Control List.
     * |        |          |0 = No active TD found or Host Controller begins to process the head of the Control list.
     * |        |          |1 = An active TD added or found on the Control list.
     * |[2]     |BLF       |Bulk List Filled
     * |        |          |Set high to indicate there is an active TD on the Bulk list
     * |        |          |This bit may be set by either software or the Host Controller and cleared by the Host Controller each time it begins processing the head of the Bulk list.
     * |        |          |0 = No active TD found or Host Controller begins to process the head of the Bulk list.
     * |        |          |1 = An active TD added or found on the Bulk list.
     * |[17:16] |SOC       |Schedule Overrun Count
     * |        |          |These bits are incremented on each scheduling overrun error
     * |        |          |It is initialized to 00b and wraps around at 11b
     * |        |          |This will be incremented when a scheduling overrun is detected even if SO (HcInterruptStatus[0]) has already been set.
     * @var USBH_T::HcInterruptStatus
     * Offset: 0x0C  Host Controller Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SO        |Scheduling Overrun
     * |        |          |Set when the List Processor determines a Schedule Overrun has occurred.
     * |        |          |0 = Schedule Overrun didn't occur.
     * |        |          |1 = Schedule Overrun has occurred.
     * |[1]     |WDH       |Write Back Done Head
     * |        |          |Set after the Host Controller has written HcDoneHead to HccaDoneHead
     * |        |          |Further updates of the HccaDoneHead will not occur until this bit has been cleared.
     * |        |          |0 =.Host Controller didn't update HccaDoneHead.
     * |        |          |1 =.Host Controller has written HcDoneHead to HccaDoneHead.
     * |[2]     |SF        |Start of Frame
     * |        |          |Set when the Frame Management functional block signals a 'Start of Frame' event
     * |        |          |Host Control generates a SOF token at the same time.
     * |        |          |0 =.Not the start of a frame.
     * |        |          |1 =.Indicate the start of a frame and Host Controller generates a SOF token.
     * |[3]     |RD        |Resume Detected
     * |        |          |Set when Host Controller detects resume signaling on a downstream port.
     * |        |          |0 = No resume signaling detected on a downstream port.
     * |        |          |1 = Resume signaling detected on a downstream port.
     * |[5]     |FNO       |Frame Number Overflow
     * |        |          |This bit is set when bit 15 of Frame Number changes from 1 to 0 or from 0 to 1.
     * |        |          |0 = The bit 15 of Frame Number didn't change.
     * |        |          |1 = The bit 15 of Frame Number changes from 1 to 0 or from 0 to 1.
     * |[6]     |RHSC      |Root Hub Status Change
     * |        |          |This bit is set when the content of HcRhStatus or the content of HcRhPortStatus register has changed.
     * |        |          |0 = The content of HcRhStatus and the content of HcRhPortStatus register didn't change.
     * |        |          |1 = The content of HcRhStatus or the content of HcRhPortStatus register has changed.
     * @var USBH_T::HcInterruptEnable
     * Offset: 0x10  Host Controller Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SO        |Scheduling Overrun Enable Bit
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Interrupt generation due to SO (HcInterruptStatus[0]) Enabled.
     * |        |          |Read Operation:
     * |        |          |0 = Interrupt generation due to SO (HcInterruptStatus[0]) Disabled.
     * |        |          |1 = Interrupt generation due to SO (HcInterruptStatus[0]) Enabled.
     * |[1]     |WDH       |Write Back Done Head Enable Bit
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Interrupt generation due to WDH (HcInterruptStatus[1]) Enabled.
     * |        |          |Read Operation:
     * |        |          |0 = Interrupt generation due to WDH (HcInterruptStatus[1]) Disabled.
     * |        |          |1 = Interrupt generation due to WDH (HcInterruptStatus[1]) Enabled.
     * |[2]     |SF        |Start of Frame Enable Bit
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Interrupt generation due to SF (HcInterruptStatus[2]) Enabled.
     * |        |          |Read Operation:
     * |        |          |0 = Interrupt generation due to SF (HcInterruptStatus[2]) Disabled.
     * |        |          |1 = Interrupt generation due to SF (HcInterruptStatus[2]) Enabled.
     * |[3]     |RD        |Resume Detected Enable Bit
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Interrupt generation due to RD (HcInterruptStatus[3]) Enabled.
     * |        |          |Read Operation:
     * |        |          |0 = Interrupt generation due to RD (HcInterruptStatus[3]) Disabled.
     * |        |          |1 = Interrupt generation due to RD (HcInterruptStatus[3]) Enabled.
     * |[5]     |FNO       |Frame Number Overflow Enable Bit
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Interrupt generation due to FNO (HcInterruptStatus[5]) Enabled.
     * |        |          |Read Operation:
     * |        |          |0 = Interrupt generation due to FNO (HcInterruptStatus[5]) Disabled.
     * |        |          |1 = Interrupt generation due to FNO (HcInterruptStatus[5]) Enabled.
     * |[6]     |RHSC      |Root Hub Status Change Enable Bit
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Interrupt generation due to RHSC (HcInterruptStatus[6]) Enabled.
     * |        |          |Read Operation:
     * |        |          |0 = Interrupt generation due to RHSC (HcInterruptStatus[6]) Disabled.
     * |        |          |1 = Interrupt generation due to RHSC (HcInterruptStatus[6]) Enabled.
     * |[31]    |MIE       |Master Interrupt Enable Bit
     * |        |          |This bit is a global interrupt enable
     * |        |          |A write of '1' allows interrupts to be enabled via the specific enable bits listed above.
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Interrupt generation due to RHSC (HcInterruptStatus[6]), FNO (HcInterruptStatus[5]), RD (HcInterruptStatus[3]), SF (HcInterruptStatus[2]), WDH (HcInterruptStatus[1]) or SO (HcInterruptStatus[0]) Enabled if the corresponding bit in HcInterruptEnable is high.
     * |        |          |Read Operation:
     * |        |          |0 = Interrupt generation due to RHSC (HcInterruptStatus[6]), FNO (HcInterruptStatus[5]), RD (HcInterruptStatus[3]), SF (HcInterruptStatus[2]), WDH (HcInterruptStatus[1]) or SO (HcInterruptStatus[0]) Disabled even if the corresponding bit in HcInterruptEnable is high.
     * |        |          |1 = Interrupt generation due to RHSC (HcInterruptStatus[6]), FNO (HcInterruptStatus[5]), RD (HcInterruptStatus[3]), SF (HcInterruptStatus[2]), WDH (HcInterruptStatus[1]) or SO (HcInterruptStatus[0]) Enabled if the corresponding bit in HcInterruptEnable is high.
     * @var USBH_T::HcInterruptDisable
     * Offset: 0x14  Host Controller Interrupt Disable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SO        |Scheduling Overrun Disable Bit
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Interrupt generation due to SO (HcInterruptStatus[0]) Disabled.
     * |        |          |Read Operation:
     * |        |          |0 = Interrupt generation due to SO (HcInterruptStatus[0]) Disabled.
     * |        |          |1 = Interrupt generation due to SO (HcInterruptStatus[0]) Enabled.
     * |[1]     |WDH       |Write Back Done Head Disable Bit
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Interrupt generation due to WDH (HcInterruptStatus[1]) Disabled.
     * |        |          |Read Operation:
     * |        |          |0 = Interrupt generation due to WDH (HcInterruptStatus[1]) Disabled.
     * |        |          |1 = Interrupt generation due to WDH (HcInterruptStatus[1]) Enabled.
     * |[2]     |SF        |Start of Frame Disable Bit
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Interrupt generation due to SF (HcInterruptStatus[2]) Disabled.
     * |        |          |Read Operation:
     * |        |          |0 = Interrupt generation due to SF (HcInterruptStatus[2]) Disabled.
     * |        |          |1 = Interrupt generation due to SF (HcInterruptStatus[2]) Enabled.
     * |[3]     |RD        |Resume Detected Disable Bit
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Interrupt generation due to RD (HcInterruptStatus[3]) Disabled.
     * |        |          |Read Operation:
     * |        |          |0 = Interrupt generation due to RD (HcInterruptStatus[3]) Disabled.
     * |        |          |1 = Interrupt generation due to RD (HcInterruptStatus[3]) Enabled.
     * |[5]     |FNO       |Frame Number Overflow Disable Bit
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Interrupt generation due to FNO (HcInterruptStatus[5]) Disabled.
     * |        |          |Read Operation:
     * |        |          |0 = Interrupt generation due to FNO (HcInterruptStatus[5]) Disabled.
     * |        |          |1 = Interrupt generation due to FNO (HcInterruptStatus[5]) Enabled.
     * |[6]     |RHSC      |Root Hub Status Change Disable Bit
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Interrupt generation due to RHSC (HcInterruptStatus[6]) Disabled.
     * |        |          |Read Operation:
     * |        |          |0 = Interrupt generation due to RHSC (HcInterruptStatus[6]) Disabled.
     * |        |          |1 = Interrupt generation due to RHSC (HcInterruptStatus[6]) Enabled.
     * |[31]    |MIE       |Master Interrupt Disable Bit
     * |        |          |Global interrupt disable. Writing '1' to disable all interrupts.
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Interrupt generation due to RHSC (HcInterruptStatus[6]), FNO (HcInterruptStatus[5]), RD (HcInterruptStatus[3]), SF (HcInterruptStatus[2]), WDH (HcInterruptStatus[1]) or SO (HcInterruptStatus[0]) Disabled if the corresponding bit in HcInterruptEnable is high.
     * |        |          |Read Operation:
     * |        |          |0 = Interrupt generation due to RHSC (HcInterruptStatus[6]), FNO (HcInterruptStatus[5]), RD (HcInterruptStatus[3]), SF (HcInterruptStatus[2]), WDH (HcInterruptStatus[1]) or SO (HcInterruptStatus[0]) Disabled even if the corresponding bit in HcInterruptEnable is high.
     * |        |          |1 = Interrupt generation due to RHSC (HcInterruptStatus[6]), FNO (HcInterruptStatus[5]), RD (HcInterruptStatus[3]), SF (HcInterruptStatus[2]), WDH (HcInterruptStatus[1]) or SO (HcInterruptStatus[0]) Enabled if the corresponding bit in HcInterruptEnable is high.
     * @var USBH_T::HcHCCA
     * Offset: 0x18  Host Controller Communication Area Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:8]  |HCCA      |Host Controller Communication Area
     * |        |          |Pointer to indicate base address of the Host Controller Communication Area (HCCA).
     * @var USBH_T::HcPeriodCurrentED
     * Offset: 0x1C  Host Controller Period Current ED Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:4]  |PCED      |Periodic Current ED
     * |        |          |Pointer to indicate physical address of the current Isochronous or Interrupt Endpoint Descriptor.
     * @var USBH_T::HcControlHeadED
     * Offset: 0x20  Host Controller Control Head ED Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:4]  |CHED      |Control Head ED
     * |        |          |Pointer to indicate physical address of the first Endpoint Descriptor of the Control list.
     * @var USBH_T::HcControlCurrentED
     * Offset: 0x24  Host Controller Control Current ED Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:4]  |CCED      |Control Current Head ED
     * |        |          |Pointer to indicate the physical address of the current Endpoint Descriptor of the Control list.
     * @var USBH_T::HcBulkHeadED
     * Offset: 0x28  Host Controller Bulk Head ED Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:4]  |BHED      |Bulk Head ED
     * |        |          |Pointer to indicate the physical address of the first Endpoint Descriptor of the Bulk list.
     * @var USBH_T::HcBulkCurrentED
     * Offset: 0x2C  Host Controller Bulk Current ED Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:4]  |BCED      |Bulk Current Head ED
     * |        |          |Pointer to indicate the physical address of the current endpoint of the Bulk list.
     * @var USBH_T::HcDoneHead
     * Offset: 0x30  Host Controller Done Head Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:4]  |DH        |Done Head
     * |        |          |Pointer to indicate the physical address of the last completed Transfer Descriptor that was added to the Done queue.
     * @var USBH_T::HcFmInterval
     * Offset: 0x34  Host Controller Frame Interval Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[13:0]  |FI        |Frame Interval
     * |        |          |This field specifies the length of a frame as (bit times - 1)
     * |        |          |For 12,000 bit times in a frame, a value of 11,999 is stored here.
     * |[30:16] |FSMPS     |FS Largest Data Packet
     * |        |          |This field specifies a value that is loaded into the Largest Data Packet Counter at the beginning of each frame.
     * |[31]    |FIT       |Frame Interval Toggle
     * |        |          |This bit is toggled by Host Controller Driver when it loads a new value into FI (HcFmInterval[13:0]).
     * |        |          |0 = Host Controller Driver didn't load new value into FI (HcFmInterval[13:0]).
     * |        |          |1 = Host Controller Driver loads a new value into FI (HcFmInterval[13:0]).
     * @var USBH_T::HcFmRemaining
     * Offset: 0x38  Host Controller Frame Remaining Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[13:0]  |FR        |Frame Remaining
     * |        |          |When the Host Controller is in the USBOPERATIONAL state, this 14-bit field decrements each 12 MHz clock period
     * |        |          |When the count reaches 0, (end of frame) the counter reloads with Frame Interval
     * |        |          |In addition, the counter loads when the Host Controller transitions into USBOPERATIONAL.
     * |[31]    |FRT       |Frame Remaining Toggle
     * |        |          |This bit is loaded from the FIT (HcFmInterval[31]) whenever FR (HcFmRemaining[13:0]) reaches 0.
     * @var USBH_T::HcFmNumber
     * Offset: 0x3C  Host Controller Frame Number Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |FN        |Frame Number
     * |        |          |This 16-bit incrementing counter field is incremented coincident with the re-load of FR (HcFmRemaining[13:0])
     * |        |          |The count rolls over from 'FFFFh' to '0h.'
     * @var USBH_T::HcPeriodicStart
     * Offset: 0x40  Host Controller Periodic Start Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[13:0]  |PS        |Periodic Start
     * |        |          |This field contains a value used by the List Processor to determine where in a frame the Periodic List processing must begin.
     * @var USBH_T::HcLSThreshold
     * Offset: 0x44  Host Controller Low-speed Threshold Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |LST       |Low-speed Threshold
     * |        |          |This field contains a value which is compared to the FR (HcFmRemaining[13:0]) field prior to initiating a Low-speed transaction
     * |        |          |The transaction is started only if FR (HcFmRemaining[13:0]) >= this field
     * |        |          |The value is calculated by Host Controller Driver with the consideration of transmission and setup overhead.
     * @var USBH_T::HcRhDescriptorA
     * Offset: 0x48  Host Controller Root Hub Descriptor A Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |NDP       |Number Downstream Ports
     * |        |          |USB host control supports two downstream ports and only one port is available in this series of chip.
     * |[8]     |PSM       |Power Switching Mode
     * |        |          |This bit is used to specify how the power switching of the Root Hub ports is controlled.
     * |        |          |0 = Global Switching.
     * |        |          |1 = Individual Switching.
     * |[11]    |OCPM      |over Current Protection Mode
     * |        |          |This bit describes how the over current status for the Root Hub ports reported
     * |        |          |This bit is only valid when NOCP (HcRhDescriptorA[12]) is cleared.
     * |        |          |0 = Global Over current.
     * |        |          |1 = Individual Over current.
     * |[12]    |NOCP      |No over Current Protection
     * |        |          |This bit describes how the over current status for the Root Hub ports reported.
     * |        |          |0 = Over current status is reported.
     * |        |          |1 = Over current status is not reported.
     * @var USBH_T::HcRhDescriptorB
     * Offset: 0x4C  Host Controller Root Hub Descriptor B Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:16] |PPCM      |Port Power Control Mask
     * |        |          |Global power switching
     * |        |          |This field is only valid if PowerSwitchingMode is set (individual port switching)
     * |        |          |When set, the port only responds to individual port power switching commands (Set/ClearPortPower)
     * |        |          |When cleared, the port only responds to global power switching commands (Set/ClearGlobalPower).
     * |        |          |0 = Port power controlled by global power switching.
     * |        |          |1 = Port power controlled by port power switching.
     * |        |          |Note: PPCM[15:2] and PPCM[0] are reserved.
     * @var USBH_T::HcRhStatus
     * Offset: 0x50  Host Controller Root Hub Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |LPS       |Clear Global Power
     * |        |          |In global power mode (PSM (HcRhDescriptorA[8]) = 0), this bit is written to one to clear all ports' power.
     * |        |          |This bit always read as zero.
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Clear global power.
     * |[1]     |OCI       |over Current Indicator
     * |        |          |This bit reflects the state of the over current status pin
     * |        |          |This field is only valid if NOCP (HcRhDesA[12]) and OCPM (HcRhDesA[11]) are cleared.
     * |        |          |0 = No over current condition.
     * |        |          |1 = Over current condition.
     * |[15]    |DRWE      |Device Remote Wakeup Enable Bit
     * |        |          |This bit controls if port's Connect Status Change as a remote wake-up event.
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Connect Status Change as a remote wake-up event Enabled.
     * |        |          |Read Operation:
     * |        |          |0 = Connect Status Change as a remote wake-up event Disabled.
     * |        |          |1 = Connect Status Change as a remote wake-up event Enabled.
     * |[16]    |LPSC      |Set Global Power
     * |        |          |In global power mode (PSM (HcRhDescriptorA[8]) = 0), this bit is written to one to enable power to all ports.
     * |        |          |This bit always read as zero.
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Set global power.
     * |[17]    |OCIC      |over Current Indicator Change
     * |        |          |This bit is set by hardware when a change has occurred in OCI (HcRhStatus[1]).
     * |        |          |Write 1 to clear this bit to zero.
     * |        |          |0 = OCI (HcRhStatus[1]) didn't change.
     * |        |          |1 = OCI (HcRhStatus[1]) change.
     * |[31]    |CRWE      |Clear Remote Wake-up Enable Bit
     * |        |          |This bit is use to clear DRWE (HcRhStatus[15]).
     * |        |          |This bit always read as zero.
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Clear DRWE (HcRhStatus[15]).
     * @var USBH_T::HcRhPortStatus[2]
     * Offset: 0x54  Host Controller Root Hub Port Status
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CCS       |CurrentConnectStatus (Read) or ClearPortEnable Bit (Write)
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Clear port enable.
     * |        |          |Read Operation:
     * |        |          |0 = No device connected.
     * |        |          |1 = Device connected.
     * |[1]     |PES       |Port Enable Status
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Set port enable.
     * |        |          |Read Operation:
     * |        |          |0 = Port Disabled.
     * |        |          |1 = Port Enabled.
     * |[2]     |PSS       |Port Suspend Status
     * |        |          |This bit indicates the port is suspended
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Set port suspend.
     * |        |          |Read Operation:
     * |        |          |0 = Port is not suspended.
     * |        |          |1 = Port is selectively suspended.
     * |[3]     |POCI      |Port over Current Indicator (Read) or Clear Port Suspend (Write)
     * |        |          |This bit reflects the state of the over current status pin dedicated to this port
     * |        |          |This field is only valid if NOCP (HcRhDescriptorA[12]) is cleared and OCPM (HcRhDescriptorA[11]) is set.
     * |        |          |This bit is also used to initiate the selective result sequence for the port.
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Clear port suspend.
     * |        |          |Read Operation:
     * |        |          |0 = No over current condition.
     * |        |          |1 = Over current condition.
     * |[4]     |PRS       |Port Reset Status
     * |        |          |This bit reflects the reset state of the port.
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Set port reset.
     * |        |          |Read Operation
     * |        |          |0 = Port reset signal is not active.
     * |        |          |1 = Port reset signal is active.
     * |[8]     |PPS       |Port Power Status
     * |        |          |This bit reflects the power state of the port regardless of the power switching mode.
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Port Power Enabled.
     * |        |          |Read Operation:
     * |        |          |0 = Port power is Disabled.
     * |        |          |1 = Port power is Enabled.
     * |[9]     |LSDA      |Low Speed Device Attached (Read) or Clear Port Power (Write)
     * |        |          |This bit defines the speed (and bud idle) of the attached device
     * |        |          |It is only valid when CCS (HcRhPortStatus1[0]) is set.
     * |        |          |This bit is also used to clear port power.
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Clear PPS (HcRhPortStatus1[8]).
     * |        |          |Read Operation:
     * |        |          |0 = Full Speed device.
     * |        |          |1 = Low-speed device.
     * |[16]    |CSC       |Connect Status Change
     * |        |          |This bit indicates connect or disconnect event has been detected (CCS (HcRhPortStatus1[0]) changed).
     * |        |          |Write 1 to clear this bit to zero.
     * |        |          |0 = No connect/disconnect event (CCS (HcRhPortStatus1[0]) didn't change).
     * |        |          |1 = Hardware detection of connect/disconnect event (CCS (HcRhPortStatus1[0]) changed).
     * |[17]    |PESC      |Port Enable Status Change
     * |        |          |This bit indicates that the port has been disabled (PES (HcRhPortStatus1[1]) cleared) due to a hardware event.
     * |        |          |Write 1 to clear this bit to zero.
     * |        |          |0 = PES (HcRhPortStatus1[1]) didn't change.
     * |        |          |1 = PES (HcRhPortStatus1[1]) changed.
     * |[18]    |PSSC      |Port Suspend Status Change
     * |        |          |This bit indicates the completion of the selective resume sequence for the port.
     * |        |          |Write 1 to clear this bit to zero.
     * |        |          |0 = Port resume is not completed.
     * |        |          |1 = Port resume completed.
     * |[19]    |OCIC      |Port over Current Indicator Change
     * |        |          |This bit is set when POCI (HcRhPortStatus1[3]) changes.
     * |        |          |Write 1 to clear this bit to zero.
     * |        |          |0 = POCI (HcRhPortStatus1[3]) didn't change.
     * |        |          |1 = POCI (HcRhPortStatus1[3]) changes.
     * |[20]    |PRSC      |Port Reset Status Change
     * |        |          |This bit indicates that the port reset signal has completed.
     * |        |          |Write 1 to clear this bit to zero.
     * |        |          |0 = Port reset is not complete.
     * |        |          |1 = Port reset is complete.
     * @var USBH_T::HcPhyControl
     * Offset: 0x200  Host Controller PHY Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[27]    |STBYEN    |USB Transceiver Standby Enable Bit
     * |        |          |This bit controls if USB transceiver could enter the standby mode to reduce power consumption.
     * |        |          |0 = The USB transceiver would never enter the standby mode.
     * |        |          |1 = The USB transceiver will enter standby mode while port is in power off state (port power is inactive).
     * @var USBH_T::HcMiscControl
     * Offset: 0x204  Host Controller Miscellaneous Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1]     |ABORT     |AHB Bus ERROR Response
     * |        |          |This bit indicates there is an ERROR response received in AHB bus.
     * |        |          |0 = No ERROR response received.
     * |        |          |1 = ERROR response received.
     * |[3]     |OCAL      |over Current Active Low
     * |        |          |This bit controls the polarity of over current flag from external power IC.
     * |        |          |0 = Over current flag is high active.
     * |        |          |1 = Over current flag is low active.
     * |[16]    |DPRT1     |Disable Port 1
     * |        |          |This bit controls if the connection between USB host controller and transceiver of port 1 is disabled
     * |        |          |If the connection is disabled, the USB host controller will not recognize any event of USB bus.
     * |        |          |Set this bit high, the transceiver of port 1 will also be forced into the standby mode no matter what USB host controller operation is.
     * |        |          |0 = The connection between USB host controller and transceiver of port 1 Enabled.
     * |        |          |1 = The connection between USB host controller and transceiver of port 1 Disabled and the transceiver of port 1 will also be forced into the standby mode.
     */
    __I  uint32_t HcRevision;            /*!< [0x0000] Host Controller Revision Register                                */
    __IO uint32_t HcControl;             /*!< [0x0004] Host Controller Control Register                                 */
    __IO uint32_t HcCommandStatus;       /*!< [0x0008] Host Controller Command Status Register                          */
    __IO uint32_t HcInterruptStatus;     /*!< [0x000c] Host Controller Interrupt Status Register                        */
    __IO uint32_t HcInterruptEnable;     /*!< [0x0010] Host Controller Interrupt Enable Register                        */
    __IO uint32_t HcInterruptDisable;    /*!< [0x0014] Host Controller Interrupt Disable Register                       */
    __IO uint32_t HcHCCA;                /*!< [0x0018] Host Controller Communication Area Register                      */
    __IO uint32_t HcPeriodCurrentED;     /*!< [0x001c] Host Controller Period Current ED Register                       */
    __IO uint32_t HcControlHeadED;       /*!< [0x0020] Host Controller Control Head ED Register                         */
    __IO uint32_t HcControlCurrentED;    /*!< [0x0024] Host Controller Control Current ED Register                      */
    __IO uint32_t HcBulkHeadED;          /*!< [0x0028] Host Controller Bulk Head ED Register                            */
    __IO uint32_t HcBulkCurrentED;       /*!< [0x002c] Host Controller Bulk Current ED Register                         */
    __IO uint32_t HcDoneHead;            /*!< [0x0030] Host Controller Done Head Register                               */
    __IO uint32_t HcFmInterval;          /*!< [0x0034] Host Controller Frame Interval Register                          */
    __I  uint32_t HcFmRemaining;         /*!< [0x0038] Host Controller Frame Remaining Register                         */
    __I  uint32_t HcFmNumber;            /*!< [0x003c] Host Controller Frame Number Register                            */
    __IO uint32_t HcPeriodicStart;       /*!< [0x0040] Host Controller Periodic Start Register                          */
    __IO uint32_t HcLSThreshold;         /*!< [0x0044] Host Controller Low-speed Threshold Register                     */
    __IO uint32_t HcRhDescriptorA;       /*!< [0x0048] Host Controller Root Hub Descriptor A Register                   */
    __IO uint32_t HcRhDescriptorB;       /*!< [0x004c] Host Controller Root Hub Descriptor B Register                   */
    __IO uint32_t HcRhStatus;            /*!< [0x0050] Host Controller Root Hub Status Register                         */
    __IO uint32_t HcRhPortStatus[2];     /*!< [0x0054] Host Controller Root Hub Port Status [1]                         */
    __I  uint32_t RESERVE0[105];
    __IO uint32_t HcPhyControl;          /*!< [0x0200] Host Controller PHY Control Register                             */
    __IO uint32_t HcMiscControl;         /*!< [0x0204] Host Controller Miscellaneous Control Register                   */

} USBH_T;

/**
    @addtogroup USBH_CONST USBH Bit Field Definition
    Constant Definitions for USBH Controller
@{ */

#define USBH_HcRevision_REV_Pos          (0)                                               /*!< USBH_T::HcRevision: REV Position       */
#define USBH_HcRevision_REV_Msk          (0xfful << USBH_HcRevision_REV_Pos)               /*!< USBH_T::HcRevision: REV Mask           */

#define USBH_HcControl_CBSR_Pos          (0)                                               /*!< USBH_T::HcControl: CBSR Position       */
#define USBH_HcControl_CBSR_Msk          (0x3ul << USBH_HcControl_CBSR_Pos)                /*!< USBH_T::HcControl: CBSR Mask           */

#define USBH_HcControl_PLE_Pos           (2)                                               /*!< USBH_T::HcControl: PLE Position        */
#define USBH_HcControl_PLE_Msk           (0x1ul << USBH_HcControl_PLE_Pos)                 /*!< USBH_T::HcControl: PLE Mask            */

#define USBH_HcControl_IE_Pos            (3)                                               /*!< USBH_T::HcControl: IE Position         */
#define USBH_HcControl_IE_Msk            (0x1ul << USBH_HcControl_IE_Pos)                  /*!< USBH_T::HcControl: IE Mask             */

#define USBH_HcControl_CLE_Pos           (4)                                               /*!< USBH_T::HcControl: CLE Position        */
#define USBH_HcControl_CLE_Msk           (0x1ul << USBH_HcControl_CLE_Pos)                 /*!< USBH_T::HcControl: CLE Mask            */

#define USBH_HcControl_BLE_Pos           (5)                                               /*!< USBH_T::HcControl: BLE Position        */
#define USBH_HcControl_BLE_Msk           (0x1ul << USBH_HcControl_BLE_Pos)                 /*!< USBH_T::HcControl: BLE Mask            */

#define USBH_HcControl_HCFS_Pos          (6)                                               /*!< USBH_T::HcControl: HCFS Position       */
#define USBH_HcControl_HCFS_Msk          (0x3ul << USBH_HcControl_HCFS_Pos)                /*!< USBH_T::HcControl: HCFS Mask           */

#define USBH_HcCommandStatus_HCR_Pos     (0)                                               /*!< USBH_T::HcCommandStatus: HCR Position  */
#define USBH_HcCommandStatus_HCR_Msk     (0x1ul << USBH_HcCommandStatus_HCR_Pos)           /*!< USBH_T::HcCommandStatus: HCR Mask      */

#define USBH_HcCommandStatus_CLF_Pos     (1)                                               /*!< USBH_T::HcCommandStatus: CLF Position  */
#define USBH_HcCommandStatus_CLF_Msk     (0x1ul << USBH_HcCommandStatus_CLF_Pos)           /*!< USBH_T::HcCommandStatus: CLF Mask      */

#define USBH_HcCommandStatus_BLF_Pos     (2)                                               /*!< USBH_T::HcCommandStatus: BLF Position  */
#define USBH_HcCommandStatus_BLF_Msk     (0x1ul << USBH_HcCommandStatus_BLF_Pos)           /*!< USBH_T::HcCommandStatus: BLF Mask      */

#define USBH_HcCommandStatus_SOC_Pos     (16)                                              /*!< USBH_T::HcCommandStatus: SOC Position  */
#define USBH_HcCommandStatus_SOC_Msk     (0x3ul << USBH_HcCommandStatus_SOC_Pos)           /*!< USBH_T::HcCommandStatus: SOC Mask      */

#define USBH_HcInterruptStatus_SO_Pos    (0)                                               /*!< USBH_T::HcInterruptStatus: SO Position */
#define USBH_HcInterruptStatus_SO_Msk    (0x1ul << USBH_HcInterruptStatus_SO_Pos)          /*!< USBH_T::HcInterruptStatus: SO Mask     */

#define USBH_HcInterruptStatus_WDH_Pos   (1)                                               /*!< USBH_T::HcInterruptStatus: WDH Position*/
#define USBH_HcInterruptStatus_WDH_Msk   (0x1ul << USBH_HcInterruptStatus_WDH_Pos)         /*!< USBH_T::HcInterruptStatus: WDH Mask    */

#define USBH_HcInterruptStatus_SF_Pos    (2)                                               /*!< USBH_T::HcInterruptStatus: SF Position */
#define USBH_HcInterruptStatus_SF_Msk    (0x1ul << USBH_HcInterruptStatus_SF_Pos)          /*!< USBH_T::HcInterruptStatus: SF Mask     */

#define USBH_HcInterruptStatus_RD_Pos    (3)                                               /*!< USBH_T::HcInterruptStatus: RD Position */
#define USBH_HcInterruptStatus_RD_Msk    (0x1ul << USBH_HcInterruptStatus_RD_Pos)          /*!< USBH_T::HcInterruptStatus: RD Mask     */

#define USBH_HcInterruptStatus_FNO_Pos   (5)                                               /*!< USBH_T::HcInterruptStatus: FNO Position*/
#define USBH_HcInterruptStatus_FNO_Msk   (0x1ul << USBH_HcInterruptStatus_FNO_Pos)         /*!< USBH_T::HcInterruptStatus: FNO Mask    */

#define USBH_HcInterruptStatus_RHSC_Pos  (6)                                               /*!< USBH_T::HcInterruptStatus: RHSC Position*/
#define USBH_HcInterruptStatus_RHSC_Msk  (0x1ul << USBH_HcInterruptStatus_RHSC_Pos)        /*!< USBH_T::HcInterruptStatus: RHSC Mask   */

#define USBH_HcInterruptEnable_SO_Pos    (0)                                               /*!< USBH_T::HcInterruptEnable: SO Position */
#define USBH_HcInterruptEnable_SO_Msk    (0x1ul << USBH_HcInterruptEnable_SO_Pos)          /*!< USBH_T::HcInterruptEnable: SO Mask     */

#define USBH_HcInterruptEnable_WDH_Pos   (1)                                               /*!< USBH_T::HcInterruptEnable: WDH Position*/
#define USBH_HcInterruptEnable_WDH_Msk   (0x1ul << USBH_HcInterruptEnable_WDH_Pos)         /*!< USBH_T::HcInterruptEnable: WDH Mask    */

#define USBH_HcInterruptEnable_SF_Pos    (2)                                               /*!< USBH_T::HcInterruptEnable: SF Position */
#define USBH_HcInterruptEnable_SF_Msk    (0x1ul << USBH_HcInterruptEnable_SF_Pos)          /*!< USBH_T::HcInterruptEnable: SF Mask     */

#define USBH_HcInterruptEnable_RD_Pos    (3)                                               /*!< USBH_T::HcInterruptEnable: RD Position */
#define USBH_HcInterruptEnable_RD_Msk    (0x1ul << USBH_HcInterruptEnable_RD_Pos)          /*!< USBH_T::HcInterruptEnable: RD Mask     */

#define USBH_HcInterruptEnable_FNO_Pos   (5)                                               /*!< USBH_T::HcInterruptEnable: FNO Position*/
#define USBH_HcInterruptEnable_FNO_Msk   (0x1ul << USBH_HcInterruptEnable_FNO_Pos)         /*!< USBH_T::HcInterruptEnable: FNO Mask    */

#define USBH_HcInterruptEnable_RHSC_Pos  (6)                                               /*!< USBH_T::HcInterruptEnable: RHSC Position*/
#define USBH_HcInterruptEnable_RHSC_Msk  (0x1ul << USBH_HcInterruptEnable_RHSC_Pos)        /*!< USBH_T::HcInterruptEnable: RHSC Mask   */

#define USBH_HcInterruptEnable_MIE_Pos   (31)                                              /*!< USBH_T::HcInterruptEnable: MIE Position*/
#define USBH_HcInterruptEnable_MIE_Msk   (0x1ul << USBH_HcInterruptEnable_MIE_Pos)         /*!< USBH_T::HcInterruptEnable: MIE Mask    */

#define USBH_HcInterruptDisable_SO_Pos   (0)                                               /*!< USBH_T::HcInterruptDisable: SO Position*/
#define USBH_HcInterruptDisable_SO_Msk   (0x1ul << USBH_HcInterruptDisable_SO_Pos)         /*!< USBH_T::HcInterruptDisable: SO Mask    */

#define USBH_HcInterruptDisable_WDH_Pos  (1)                                               /*!< USBH_T::HcInterruptDisable: WDH Position*/
#define USBH_HcInterruptDisable_WDH_Msk  (0x1ul << USBH_HcInterruptDisable_WDH_Pos)        /*!< USBH_T::HcInterruptDisable: WDH Mask   */

#define USBH_HcInterruptDisable_SF_Pos   (2)                                               /*!< USBH_T::HcInterruptDisable: SF Position*/
#define USBH_HcInterruptDisable_SF_Msk   (0x1ul << USBH_HcInterruptDisable_SF_Pos)         /*!< USBH_T::HcInterruptDisable: SF Mask    */

#define USBH_HcInterruptDisable_RD_Pos   (3)                                               /*!< USBH_T::HcInterruptDisable: RD Position*/
#define USBH_HcInterruptDisable_RD_Msk   (0x1ul << USBH_HcInterruptDisable_RD_Pos)         /*!< USBH_T::HcInterruptDisable: RD Mask    */

#define USBH_HcInterruptDisable_FNO_Pos  (5)                                               /*!< USBH_T::HcInterruptDisable: FNO Position*/
#define USBH_HcInterruptDisable_FNO_Msk  (0x1ul << USBH_HcInterruptDisable_FNO_Pos)        /*!< USBH_T::HcInterruptDisable: FNO Mask   */

#define USBH_HcInterruptDisable_RHSC_Pos (6)                                               /*!< USBH_T::HcInterruptDisable: RHSC Position*/
#define USBH_HcInterruptDisable_RHSC_Msk (0x1ul << USBH_HcInterruptDisable_RHSC_Pos)       /*!< USBH_T::HcInterruptDisable: RHSC Mask  */

#define USBH_HcInterruptDisable_MIE_Pos  (31)                                              /*!< USBH_T::HcInterruptDisable: MIE Position*/
#define USBH_HcInterruptDisable_MIE_Msk  (0x1ul << USBH_HcInterruptDisable_MIE_Pos)        /*!< USBH_T::HcInterruptDisable: MIE Mask   */

#define USBH_HcHCCA_HCCA_Pos             (8)                                               /*!< USBH_T::HcHCCA: HCCA Position          */
#define USBH_HcHCCA_HCCA_Msk             (0xfffffful << USBH_HcHCCA_HCCA_Pos)              /*!< USBH_T::HcHCCA: HCCA Mask              */

#define USBH_HcPeriodCurrentED_PCED_Pos  (4)                                               /*!< USBH_T::HcPeriodCurrentED: PCED Position*/
#define USBH_HcPeriodCurrentED_PCED_Msk  (0xffffffful << USBH_HcPeriodCurrentED_PCED_Pos)  /*!< USBH_T::HcPeriodCurrentED: PCED Mask   */

#define USBH_HcControlHeadED_CHED_Pos    (4)                                               /*!< USBH_T::HcControlHeadED: CHED Position */
#define USBH_HcControlHeadED_CHED_Msk    (0xffffffful << USBH_HcControlHeadED_CHED_Pos)    /*!< USBH_T::HcControlHeadED: CHED Mask     */

#define USBH_HcControlCurrentED_CCED_Pos (4)                                               /*!< USBH_T::HcControlCurrentED: CCED Position*/
#define USBH_HcControlCurrentED_CCED_Msk (0xffffffful << USBH_HcControlCurrentED_CCED_Pos) /*!< USBH_T::HcControlCurrentED: CCED Mask  */

#define USBH_HcBulkHeadED_BHED_Pos       (4)                                               /*!< USBH_T::HcBulkHeadED: BHED Position    */
#define USBH_HcBulkHeadED_BHED_Msk       (0xffffffful << USBH_HcBulkHeadED_BHED_Pos)       /*!< USBH_T::HcBulkHeadED: BHED Mask        */

#define USBH_HcBulkCurrentED_BCED_Pos    (4)                                               /*!< USBH_T::HcBulkCurrentED: BCED Position */
#define USBH_HcBulkCurrentED_BCED_Msk    (0xffffffful << USBH_HcBulkCurrentED_BCED_Pos)    /*!< USBH_T::HcBulkCurrentED: BCED Mask     */

#define USBH_HcDoneHead_DH_Pos           (4)                                               /*!< USBH_T::HcDoneHead: DH Position        */
#define USBH_HcDoneHead_DH_Msk           (0xffffffful << USBH_HcDoneHead_DH_Pos)           /*!< USBH_T::HcDoneHead: DH Mask            */

#define USBH_HcFmInterval_FI_Pos         (0)                                               /*!< USBH_T::HcFmInterval: FI Position      */
#define USBH_HcFmInterval_FI_Msk         (0x3ffful << USBH_HcFmInterval_FI_Pos)            /*!< USBH_T::HcFmInterval: FI Mask          */

#define USBH_HcFmInterval_FSMPS_Pos      (16)                                              /*!< USBH_T::HcFmInterval: FSMPS Position   */
#define USBH_HcFmInterval_FSMPS_Msk      (0x7ffful << USBH_HcFmInterval_FSMPS_Pos)         /*!< USBH_T::HcFmInterval: FSMPS Mask       */

#define USBH_HcFmInterval_FIT_Pos        (31)                                              /*!< USBH_T::HcFmInterval: FIT Position     */
#define USBH_HcFmInterval_FIT_Msk        (0x1ul << USBH_HcFmInterval_FIT_Pos)              /*!< USBH_T::HcFmInterval: FIT Mask         */

#define USBH_HcFmRemaining_FR_Pos        (0)                                               /*!< USBH_T::HcFmRemaining: FR Position     */
#define USBH_HcFmRemaining_FR_Msk        (0x3ffful << USBH_HcFmRemaining_FR_Pos)           /*!< USBH_T::HcFmRemaining: FR Mask         */

#define USBH_HcFmRemaining_FRT_Pos       (31)                                              /*!< USBH_T::HcFmRemaining: FRT Position    */
#define USBH_HcFmRemaining_FRT_Msk       (0x1ul << USBH_HcFmRemaining_FRT_Pos)             /*!< USBH_T::HcFmRemaining: FRT Mask        */

#define USBH_HcFmNumber_FN_Pos           (0)                                               /*!< USBH_T::HcFmNumber: FN Position        */
#define USBH_HcFmNumber_FN_Msk           (0xfffful << USBH_HcFmNumber_FN_Pos)              /*!< USBH_T::HcFmNumber: FN Mask            */

#define USBH_HcPeriodicStart_PS_Pos      (0)                                               /*!< USBH_T::HcPeriodicStart: PS Position   */
#define USBH_HcPeriodicStart_PS_Msk      (0x3ffful << USBH_HcPeriodicStart_PS_Pos)         /*!< USBH_T::HcPeriodicStart: PS Mask       */

#define USBH_HcLSThreshold_LST_Pos       (0)                                               /*!< USBH_T::HcLSThreshold: LST Position    */
#define USBH_HcLSThreshold_LST_Msk       (0xffful << USBH_HcLSThreshold_LST_Pos)           /*!< USBH_T::HcLSThreshold: LST Mask        */

#define USBH_HcRhDescriptorA_NDP_Pos     (0)                                               /*!< USBH_T::HcRhDescriptorA: NDP Position  */
#define USBH_HcRhDescriptorA_NDP_Msk     (0xfful << USBH_HcRhDescriptorA_NDP_Pos)          /*!< USBH_T::HcRhDescriptorA: NDP Mask      */

#define USBH_HcRhDescriptorA_PSM_Pos     (8)                                               /*!< USBH_T::HcRhDescriptorA: PSM Position  */
#define USBH_HcRhDescriptorA_PSM_Msk     (0x1ul << USBH_HcRhDescriptorA_PSM_Pos)           /*!< USBH_T::HcRhDescriptorA: PSM Mask      */

#define USBH_HcRhDescriptorA_OCPM_Pos    (11)                                              /*!< USBH_T::HcRhDescriptorA: OCPM Position */
#define USBH_HcRhDescriptorA_OCPM_Msk    (0x1ul << USBH_HcRhDescriptorA_OCPM_Pos)          /*!< USBH_T::HcRhDescriptorA: OCPM Mask     */

#define USBH_HcRhDescriptorA_NOCP_Pos    (12)                                              /*!< USBH_T::HcRhDescriptorA: NOCP Position */
#define USBH_HcRhDescriptorA_NOCP_Msk    (0x1ul << USBH_HcRhDescriptorA_NOCP_Pos)          /*!< USBH_T::HcRhDescriptorA: NOCP Mask     */

#define USBH_HcRhDescriptorB_PPCM_Pos    (16)                                              /*!< USBH_T::HcRhDescriptorB: PPCM Position */
#define USBH_HcRhDescriptorB_PPCM_Msk    (0xfffful << USBH_HcRhDescriptorB_PPCM_Pos)       /*!< USBH_T::HcRhDescriptorB: PPCM Mask     */

#define USBH_HcRhStatus_LPS_Pos          (0)                                               /*!< USBH_T::HcRhStatus: LPS Position       */
#define USBH_HcRhStatus_LPS_Msk          (0x1ul << USBH_HcRhStatus_LPS_Pos)                /*!< USBH_T::HcRhStatus: LPS Mask           */

#define USBH_HcRhStatus_OCI_Pos          (1)                                               /*!< USBH_T::HcRhStatus: OCI Position       */
#define USBH_HcRhStatus_OCI_Msk          (0x1ul << USBH_HcRhStatus_OCI_Pos)                /*!< USBH_T::HcRhStatus: OCI Mask           */

#define USBH_HcRhStatus_DRWE_Pos         (15)                                              /*!< USBH_T::HcRhStatus: DRWE Position      */
#define USBH_HcRhStatus_DRWE_Msk         (0x1ul << USBH_HcRhStatus_DRWE_Pos)               /*!< USBH_T::HcRhStatus: DRWE Mask          */

#define USBH_HcRhStatus_LPSC_Pos         (16)                                              /*!< USBH_T::HcRhStatus: LPSC Position      */
#define USBH_HcRhStatus_LPSC_Msk         (0x1ul << USBH_HcRhStatus_LPSC_Pos)               /*!< USBH_T::HcRhStatus: LPSC Mask          */

#define USBH_HcRhStatus_OCIC_Pos         (17)                                              /*!< USBH_T::HcRhStatus: OCIC Position      */
#define USBH_HcRhStatus_OCIC_Msk         (0x1ul << USBH_HcRhStatus_OCIC_Pos)               /*!< USBH_T::HcRhStatus: OCIC Mask          */

#define USBH_HcRhStatus_CRWE_Pos         (31)                                              /*!< USBH_T::HcRhStatus: CRWE Position      */
#define USBH_HcRhStatus_CRWE_Msk         (0x1ul << USBH_HcRhStatus_CRWE_Pos)               /*!< USBH_T::HcRhStatus: CRWE Mask          */

#define USBH_HcRhPortStatus_CCS_Pos      (0)                                               /*!< USBH_T::HcRhPortStatus1: CCS Position  */
#define USBH_HcRhPortStatus_CCS_Msk      (0x1ul << USBH_HcRhPortStatus_CCS_Pos)            /*!< USBH_T::HcRhPortStatus1: CCS Mask      */

#define USBH_HcRhPortStatus_PES_Pos      (1)                                               /*!< USBH_T::HcRhPortStatus1: PES Position  */
#define USBH_HcRhPortStatus_PES_Msk      (0x1ul << USBH_HcRhPortStatus_PES_Pos)            /*!< USBH_T::HcRhPortStatus1: PES Mask      */

#define USBH_HcRhPortStatus_PSS_Pos      (2)                                               /*!< USBH_T::HcRhPortStatus1: PSS Position  */
#define USBH_HcRhPortStatus_PSS_Msk      (0x1ul << USBH_HcRhPortStatus_PSS_Pos)            /*!< USBH_T::HcRhPortStatus1: PSS Mask      */

#define USBH_HcRhPortStatus_POCI_Pos     (3)                                               /*!< USBH_T::HcRhPortStatus1: POCI Position */
#define USBH_HcRhPortStatus_POCI_Msk     (0x1ul << USBH_HcRhPortStatus_POCI_Pos)           /*!< USBH_T::HcRhPortStatus1: POCI Mask     */

#define USBH_HcRhPortStatus_PRS_Pos      (4)                                               /*!< USBH_T::HcRhPortStatus1: PRS Position  */
#define USBH_HcRhPortStatus_PRS_Msk      (0x1ul << USBH_HcRhPortStatus_PRS_Pos)            /*!< USBH_T::HcRhPortStatus1: PRS Mask      */

#define USBH_HcRhPortStatus_PPS_Pos      (8)                                               /*!< USBH_T::HcRhPortStatus1: PPS Position  */
#define USBH_HcRhPortStatus_PPS_Msk      (0x1ul << USBH_HcRhPortStatus_PPS_Pos)            /*!< USBH_T::HcRhPortStatus1: PPS Mask      */

#define USBH_HcRhPortStatus_LSDA_Pos     (9)                                               /*!< USBH_T::HcRhPortStatus1: LSDA Position */
#define USBH_HcRhPortStatus_LSDA_Msk     (0x1ul << USBH_HcRhPortStatus_LSDA_Pos)           /*!< USBH_T::HcRhPortStatus1: LSDA Mask     */

#define USBH_HcRhPortStatus_CSC_Pos      (16)                                              /*!< USBH_T::HcRhPortStatus1: CSC Position  */
#define USBH_HcRhPortStatus_CSC_Msk      (0x1ul << USBH_HcRhPortStatus_CSC_Pos)            /*!< USBH_T::HcRhPortStatus1: CSC Mask      */

#define USBH_HcRhPortStatus_PESC_Pos     (17)                                              /*!< USBH_T::HcRhPortStatus1: PESC Position */
#define USBH_HcRhPortStatus_PESC_Msk     (0x1ul << USBH_HcRhPortStatus_PESC_Pos)           /*!< USBH_T::HcRhPortStatus1: PESC Mask     */

#define USBH_HcRhPortStatus_PSSC_Pos     (18)                                              /*!< USBH_T::HcRhPortStatus1: PSSC Position */
#define USBH_HcRhPortStatus_PSSC_Msk     (0x1ul << USBH_HcRhPortStatus_PSSC_Pos)           /*!< USBH_T::HcRhPortStatus1: PSSC Mask     */

#define USBH_HcRhPortStatus_OCIC_Pos     (19)                                              /*!< USBH_T::HcRhPortStatus1: OCIC Position */
#define USBH_HcRhPortStatus_OCIC_Msk     (0x1ul << USBH_HcRhPortStatus_OCIC_Pos)           /*!< USBH_T::HcRhPortStatus1: OCIC Mask     */

#define USBH_HcRhPortStatus_PRSC_Pos     (20)                                              /*!< USBH_T::HcRhPortStatus1: PRSC Position */
#define USBH_HcRhPortStatus_PRSC_Msk     (0x1ul << USBH_HcRhPortStatus_PRSC_Pos)           /*!< USBH_T::HcRhPortStatus1: PRSC Mask     */

#define USBH_HcPhyControl_STBYEN_Pos     (27)                                              /*!< USBH_T::HcPhyControl: STBYEN Position  */
#define USBH_HcPhyControl_STBYEN_Msk     (0x1ul << USBH_HcPhyControl_STBYEN_Pos)           /*!< USBH_T::HcPhyControl: STBYEN Mask      */

#define USBH_HcMiscControl_ABORT_Pos     (1)                                               /*!< USBH_T::HcMiscControl: ABORT Position  */
#define USBH_HcMiscControl_ABORT_Msk     (0x1ul << USBH_HcMiscControl_ABORT_Pos)           /*!< USBH_T::HcMiscControl: ABORT Mask      */

#define USBH_HcMiscControl_OCAL_Pos      (3)                                               /*!< USBH_T::HcMiscControl: OCAL Position   */
#define USBH_HcMiscControl_OCAL_Msk      (0x1ul << USBH_HcMiscControl_OCAL_Pos)            /*!< USBH_T::HcMiscControl: OCAL Mask       */

#define USBH_HcMiscControl_DPRT1_Pos     (16)                                              /*!< USBH_T::HcMiscControl: DPRT1 Position  */
#define USBH_HcMiscControl_DPRT1_Msk     (0x1ul << USBH_HcMiscControl_DPRT1_Pos)           /*!< USBH_T::HcMiscControl: DPRT1 Mask      */

/**@}*/ /* USBH_CONST */
/**@}*/ /* end of USBH register group */


/*---------------------- HSUSBH HSUSB Host Controller -------------------------*/
/**
    @addtogroup HSUSBH High Speed USB Host Controller (HSUSBH)
    Memory Mapped Structure for HSUSBH Controller
@{ */

typedef struct
{


    /**
     * @var HSUSBH_T::EHCVNR
     * Offset: 0x00  EHCI Version Number Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |CRLEN     |Capability Registers Length
     * |        |          |This register is used as an offset to add to register base to find the beginning of the Operational Register Space.
     * |[31:16] |VERSION   |Host Controller Interface Version Number
     * |        |          |This is a two-byte register containing a BCD encoding of the EHCI revision number supported by this host controller
     * |        |          |The most significant byte of this register represents a major revision and the least significant byte is the minor revision.
     * @var HSUSBH_T::EHCSPR
     * Offset: 0x04  EHCI Structural Parameters Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |N_PORTS   |Number of Physical Downstream Ports
     * |        |          |This field specifies the number of physical downstream ports implemented on this host controller
     * |        |          |The value of this field determines how many port registers are addressable in the Operational Register Space (see Table 2-8)
     * |        |          |Valid values are in the range of 1H to FH.
     * |        |          |A zero in this field is undefined.
     * |[4]     |PPC       |Port Power Control
     * |        |          |This field indicates whether the host controller implementation includes port power control
     * |        |          |A one in this bit indicates the ports have port power switches
     * |        |          |A zero in this bit indicates the port do not have port power stitches
     * |        |          |The value of this field affects the functionality of the Port Power field in each port status and control register.
     * |[11:8]  |N_PCC     |Number of Ports Per Companion Controller
     * |        |          |This field indicates the number of ports supported per companion host controller
     * |        |          |It is used to indicate the port routing configuration to system software.
     * |        |          |For example, if N_PORTS has a value of 6 and N_CC has a value of 2 then N_PCC could have a value of 3
     * |        |          |The convention is that the first N_PCC ports are assumed to be routed to companion controller 1, the next N_PCC ports to companion controller 2, etc
     * |        |          |In the previous example, the N_PCC could have been 4, where the first 4 are routed to companion controller 1 and the last two are routed to companion controller 2.
     * |        |          |The number in this field must be consistent with N_PORTS and N_CC.
     * |[15:12] |N_CC      |Number of Companion Controller
     * |        |          |This field indicates the number of companion controllers associated with this USB 2.0 host controller.
     * |        |          |A zero in this field indicates there are no companion host controllers
     * |        |          |Port-ownership hand-off is not supported
     * |        |          |Only high-speed devices are supported on the host controller root ports.
     * |        |          |A value larger than zero in this field indicates there are companion USB 1.1 host controller(s)
     * |        |          |Port-ownership hand-offs are supported
     * |        |          |High, Full- and Low-speed devices are supported on the host controller root ports.
     * @var HSUSBH_T::EHCCPR
     * Offset: 0x08  EHCI Capability Parameters Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |AC64      |64-bit Addressing Capability
     * |        |          |0 = Data structure using 32-bit address memory pointers.
     * |[1]     |PFLF      |Programmable Frame List Flag
     * |        |          |0 = System software must use a frame list length of 1024 elements with this EHCI host controller.
     * |[2]     |ASPC      |Asynchronous Schedule Park Capability
     * |        |          |0 = This EHCI host controller doesn't support park feature of high-speed queue heads in the Asynchronous Schedule.
     * |[7:4]   |IST       |Isochronous Scheduling Threshold
     * |        |          |This field indicates, relative to the current position of the executing host controller, where software can reliably update the isochronous schedule.
     * |        |          |When bit [7] is zero, the value of the least significant 3 bits indicates the number of micro-frames a host controller can hold a set of isochronous data structures (one or more) before flushing the state.
     * |[15:8]  |EECP      |EHCI Extended Capabilities Pointer (EECP)
     * |        |          |0 = No extended capabilities are implemented.
     * @var HSUSBH_T::UCMDR
     * Offset: 0x20  USB Command Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RUN       |Run/Stop (R/W)
     * |        |          |When set to a 1, the Host Controller proceeds with execution of the schedule
     * |        |          |The Host Controller continues execution as long as this bit is set to a 1
     * |        |          |When this bit is set to 0, the Host Controller completes the current and any actively pipelined transactions on the USB and then halts
     * |        |          |The Host Controller must halt within 16 micro-frames after software clears the Run bit
     * |        |          |The HC Halted bit in the status register indicates when the Host Controller has finished its pending pipelined transactions and has entered the stopped state
     * |        |          |Software must not write a one to this field unless the host controller is in the Halted state (i.e.
     * |        |          |HCHalted in the USBSTS register is a one)
     * |        |          |Doing so will yield undefined results.
     * |        |          |0 = Stop.
     * |        |          |1 = Run.
     * |[1]     |HCRST     |Host Controller Reset (HCRESET) (R/W)
     * |        |          |This control bit is used by software to reset the host controller
     * |        |          |The effects of this on Root Hub registers are similar to a Chip Hardware Reset.
     * |        |          |When software writes a one to this bit, the Host Controller resets its internal pipelines, timers, counters, state machines, etc
     * |        |          |to their initial value
     * |        |          |Any transaction currently in progress on USB is immediately terminated
     * |        |          |A USB reset is not driven on downstream ports.
     * |        |          |All operational registers, including port registers and port state machines are set to their initial values
     * |        |          |Port ownership reverts to the companion host controller(s), with the side effects
     * |        |          |Software must reinitialize the host controller in order to return the host controller to an operational state.
     * |        |          |This bit is set to zero by the Host Controller when the reset process is complete
     * |        |          |Software cannot terminate the reset process early by writing a zero to this register.
     * |        |          |Software should not set this bit to a one when the HCHalted bit in the USBSTS register is a zero
     * |        |          |Attempting to reset an actively running host controller will result in undefined behavior.
     * |[3:2]   |FLSZ      |Frame List Size (R/W or RO)
     * |        |          |This field is R/W only if Programmable Frame List Flag in the HCCPARAMS registers is set to a one
     * |        |          |This field specifies the size of the frame list
     * |        |          |The size the frame list controls which bits in the Frame Index Register should be used for the Frame List Current index
     * |        |          |Values mean:
     * |        |          |00 = 1024 elements (4096 bytes) Default value.
     * |        |          |01 = 512 elements (2048 bytes).
     * |        |          |10 = 256 elements (1024 bytes) u2013 for resource-constrained environment.
     * |        |          |11 = Reserved.
     * |[4]     |PSEN      |Periodic Schedule Enable (R/W)
     * |        |          |This bit controls whether the host controller skips processing the Periodic Schedule. Values mean:
     * |        |          |0 = Do not process the Periodic Schedule.
     * |        |          |1 = Use the PERIODICLISTBASE register to access the Periodic Schedule.
     * |[5]     |ASEN      |Asynchronous Schedule Enable (R/W)
     * |        |          |This bit controls whether the host controller skips processing the Asynchronous Schedule. Values mean:
     * |        |          |0 = Do not process the Asynchronous Schedule.
     * |        |          |1 = Use the ASYNCLISTADDR register to access the Asynchronous Schedule.
     * |[6]     |IAAD      |Interrupt on Asynchronous Advance Doorbell (R/W)
     * |        |          |This bit is used as a doorbell by software to tell the host controller to issue an interrupt the next time it advances asynchronous schedule
     * |        |          |Software must write a 1 to this bit to ring the doorbell.
     * |        |          |When the host controller has evicted all appropriate cached schedule state, it sets the Interrupt on Asynchronous Advance status bit in the USBSTS register
     * |        |          |If the Interrupt on Asynchronous Advance Enable bit in the USBINTR register is a one then the host controller will assert an interrupt at the next interrupt threshold.
     * |        |          |The host controller sets this bit to a zero after it has set the Interrupt on Asynchronous Advance status bit in the USBSTS register to a one.
     * |        |          |Software should not write a one to this bit when the asynchronous schedule is disabled
     * |        |          |Doing so will yield undefined results.
     * |[23:16] |ITC       |Interrupt Threshold Control (R/W)
     * |        |          |This field is used by system software to select the maximum rate at which the host controller will issue interrupts
     * |        |          |The only valid values are defined below
     * |        |          |If software writes an invalid value to this register, the results are undefined
     * |        |          |Value Maximum Interrupt Interval
     * |        |          |0x00 = Reserved.
     * |        |          |0x01 = 1 micro-frame.
     * |        |          |0x02 = 2 micro-frames.
     * |        |          |0x04 = 4 micro-frames.
     * |        |          |0x08 = 8 micro-frames (default, equates to 1 ms).
     * |        |          |0x10 = 16 micro-frames (2 ms).
     * |        |          |0x20 = 32 micro-frames (4 ms).
     * |        |          |0x40 = 64 micro-frames (8 ms).
     * |        |          |Any other value in this register yields undefined results.
     * |        |          |Software modifications to this bit while HCHalted bit is equal to zero results in undefined behavior.
     * @var HSUSBH_T::USTSR
     * Offset: 0x24  USB Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |USBINT    |USB Interrupt (USBINT) (R/WC)
     * |        |          |The Host Controller sets this bit to 1 on the completion of a USB transaction, which results in the retirement of a Transfer Descriptor that had its IOC bit set.
     * |        |          |The Host Controller also sets this bit to 1 when a short packet is detected (actual number of bytes received was less than the expected number of bytes).
     * |[1]     |UERRINT   |USB Error Interrupt (USBERRINT) (R/WC)
     * |        |          |The Host Controller sets this bit to 1 when completion of a USB transaction results in an error condition (e.g., error counter underflow)
     * |        |          |If the TD on which the error interrupt occurred also had its IOC bit set, both this bit and USBINT bit are set.
     * |[2]     |PCD       |Port Change Detect (R/WC)
     * |        |          |The Host Controller sets this bit to a one when any port for which the Port Owner bit is set to zero has a change bit transition from a zero to a one or a Force Port Resume bit transition from a zero to a one as a result of a J-K transition detected on a suspended port
     * |        |          |This bit will also be set as a result of the Connect Status Change being set to a one after system software has relinquished ownership of a connected port by writing a one to a port's Port Owner bit.
     * |        |          |This bit is allowed to be maintained in the Auxiliary power well
     * |        |          |Alternatively, it is also acceptable that on a D3 to D0 transition of the EHCI HC device, this bit is loaded with the OR of all of the PORTSC change bits (including: Force port resume, over-current change, enable/disable change and connect status change).
     * |[3]     |FLR       |Frame List Rollover (R/WC)
     * |        |          |The Host Controller sets this bit to a one when the Frame List Index rolls over from its maximum value to zero
     * |        |          |The exact value at which the rollover occurs depends on the frame list size
     * |        |          |For example, if the frame list size (as programmed in the Frame List Size field of the USBCMD register) is 1024, the Frame Index Register rolls over every time FRINDEX[13] toggles
     * |        |          |Similarly, if the size is 512, the Host Controller sets this bit to a one every time FRINDEX[12] toggles.
     * |[4]     |HSERR     |Host System Error (R/WC)
     * |        |          |The Host Controller sets this bit to 1 when a serious error occurs during a host system access involving the Host Controller module.
     * |[5]     |IAA       |Interrupt on Asynchronous Advance (R/WC)
     * |        |          |System software can force the host controller to issue an interrupt the next time the host controller advances the asynchronous schedule by writing a one to the Interrupt on Asynchronous Advance Doorbell bit in the USBCMD register
     * |        |          |This status bit indicates the assertion of that interrupt source.
     * |[12]    |HCHalted  |HCHalted (RO)
     * |        |          |This bit is a zero whenever the Run/Stop bit is a one
     * |        |          |The Host Controller sets this bit to one after it has stopped executing as a result of the Run/Stop bit being set to 0, either by software or by the Host Controller hardware (e.g.
     * |        |          |internal error).
     * |[13]    |RECLA     |Reclamation (RO)
     * |        |          |This is a read-only status bit, which is used to detect an empty asynchronous schedule.
     * |[14]    |PSS       |Periodic Schedule Status (RO)
     * |        |          |The bit reports the current real status of the Periodic Schedule
     * |        |          |If this bit is a zero then the status of the Periodic Schedule is disabled
     * |        |          |If this bit is a one then the status of the Periodic Schedule is enabled
     * |        |          |The Host Controller is not required to immediately disable or enable the Periodic Schedule when software transitions the Periodic Schedule Enable bit in the USBCMD register
     * |        |          |When this bit and the Periodic Schedule Enable bit are the same value, the Periodic Schedule is either enabled (1) or disabled (0).
     * |[15]    |ASS       |Asynchronous Schedule Status (RO)
     * |        |          |The bit reports the current real status of the Asynchronous Schedule
     * |        |          |If this bit is a zero then the status of them Asynchronous Schedule is disabled
     * |        |          |If this bit is a one then the status of the Asynchronous Schedule is enabled
     * |        |          |The Host Controller is not required to immediately disable or enable the Asynchronous Schedule when software transitions the Asynchronous Schedule Enable bit in the USBCMD register
     * |        |          |When this bit and the Asynchronous Schedule Enable bit are the same value, the Asynchronous Schedule is either enabled (1) or disabled (0).
     * @var HSUSBH_T::UIENR
     * Offset: 0x28  USB Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |USBIEN    |USB Interrupt Enable or Disable Bit
     * |        |          |When this bit is a one, and the USBINT bit in the USBSTS register is a one, the host controller will issue an interrupt at the next interrupt threshold
     * |        |          |The interrupt is acknowledged by software clearing the USBINT bit.
     * |        |          |0 = USB interrupt Disabled.
     * |        |          |1 = USB interrupt Enabled.
     * |[1]     |UERRIEN   |USB Error Interrupt Enable or Disable Bit
     * |        |          |When this bit is a one, and the USBERRINT bit in the USBSTS register is a one, the host t controller will issue an interrupt at the next interrupt threshold
     * |        |          |The interrupt is acknowledged by software clearing the USBERRINT bit.
     * |        |          |0 = USB Error interrupt Disabled.
     * |        |          |1 = USB Error interrupt Enabled.
     * |[2]     |PCIEN     |Port Change Interrupt Enable or Disable Bit
     * |        |          |When this bit is a one, and the Port Change Detect bit in the USBSTS register is a one, the host controller will issue an interrupt
     * |        |          |The interrupt is acknowledged by software clearing the Port Change Detect bit.
     * |        |          |0 = Port Change interrupt Disabled.
     * |        |          |1 = Port Change interrupt Enabled.
     * |[3]     |FLREN     |Frame List Rollover Enable or Disable Bit
     * |        |          |When this bit is a one, and the Frame List Rollover bit in the USBSTS register is a one, the host controller will issue an interrupt
     * |        |          |The interrupt is acknowledged by software clearing the Frame List Rollover bit.
     * |        |          |0 = Frame List Rollover interrupt Disabled.
     * |        |          |1 = Frame List Rollover interrupt Enabled.
     * |[4]     |HSERREN   |Host System Error Enable or Disable Bit
     * |        |          |When this bit is a one, and the Host System Error Status bit in the USBSTS register is a one, the host controller will issue an interrupt
     * |        |          |The interrupt is acknowledged by software clearing the Host System Error bit.
     * |        |          |0 = Host System Error interrupt Disabled.
     * |        |          |1 = Host System Error interrupt Enabled.
     * |[5]     |IAAEN     |Interrupt on Asynchronous Advance Enable or Disable Bit
     * |        |          |When this bit is a one, and the Interrupt on Asynchronous Advance bit in the USBSTS register is a one, the host controller will issue an interrupt at the next interrupt threshold
     * |        |          |The interrupt is acknowledged by software clearing the Interrupt on Asynchronous Advance bit.
     * |        |          |0 = Interrupt on Asynchronous Advance Disabled.
     * |        |          |1 = Interrupt on Asynchronous Advance Enabled.
     * @var HSUSBH_T::UFINDR
     * Offset: 0x2C  USB Frame Index Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[13:0]  |FI        |Frame Index
     * |        |          |The value in this register increment at the end of each time frame (e.g.
     * |        |          |micro-frame)
     * |        |          |Bits [N:3] are used for the Frame List current index
     * |        |          |This means that each location of the frame list is accessed 8 times (frames or micro-frames) before moving to the next index
     * |        |          |The following illustrates values of N based on the value of the Frame List Size field in the USBCMD register.
     * |        |          |FLSZ (UCMDR[3:2] Number Elements N
     * |        |          |0x0 1024 12
     * |        |          |0x1 512 11
     * |        |          |0x2 256 10
     * |        |          |0x3 Reserved
     * @var HSUSBH_T::UPFLBAR
     * Offset: 0x34  USB Periodic Frame List Base Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:12] |BADDR     |Base Address
     * |        |          |These bits correspond to memory address signals [31:12], respectively.
     * @var HSUSBH_T::UCALAR
     * Offset: 0x38  USB Current Asynchronous List Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:5]  |LPL       |Link Pointer Low (LPL)
     * |        |          |These bits correspond to memory address signals [31:5], respectively
     * |        |          |This field may only reference a Queue Head (QH).
     * @var HSUSBH_T::UASSTR
     * Offset: 0x3C  USB Asynchronous Schedule Sleep Timer Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |ASSTMR    |Asynchronous Schedule Sleep Timer
     * |        |          |This field defines the AsyncSchedSleepTime of EHCI spec.
     * |        |          |The asynchronous schedule sleep timer is used to control how often the host controller fetches asynchronous schedule list from system memory while the asynchronous schedule is empty.
     * |        |          |The default value of this timer is 12'hBD6
     * |        |          |Because this timer is implemented in UTMI clock (30MHz) domain, the default sleeping time will be about 100us.
     * @var HSUSBH_T::UCFGR
     * Offset: 0x60  USB Configure Flag Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CF        |Configure Flag (CF)
     * |        |          |Host software sets this bit as the last action in its process of configuring the Host Controller
     * |        |          |This bit controls the default port-routing control logic
     * |        |          |Bit values and side-effects are listed below.
     * |        |          |0 = Port routing control logic default-routes each port to an implementation dependent classic host controller.
     * |        |          |1 = Port routing control logic default-routes all ports to this host controller.
     * @var HSUSBH_T::UPSCR[2]
     * Offset: 0x64~0x68  USB Port 0~1 Status and Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CCS       |Current Connect Status (RO)
     * |        |          |This value reflects the current state of the port, and may not correspond directly to the event that caused the Connect Status Change bit (Bit 1) to be set.
     * |        |          |This field is zero if Port Power is zero.
     * |        |          |0 = No device is present.
     * |        |          |1 = Device is present on port.
     * |[1]     |CSC       |Connect Status Change (R/W)
     * |        |          |Indicates a change has occurred in the port's Current Connect Status
     * |        |          |The host controller sets this bit for all changes to the port device connect status, even if system software has not cleared an existing connect status change
     * |        |          |For example, the insertion status changes twice before system software has cleared the changed condition, hub hardware will be "setting" an already-set bit (i.e., the bit will remain set).Software sets this bit to 0 by writing a 1 to it.
     * |        |          |This field is zero if Port Power is zero.
     * |        |          |0 = No change.
     * |        |          |1 = Change in Current Connect Status.
     * |[2]     |PE        |Port Enabled/Disabled (R/W)
     * |        |          |Ports can only be enabled by the host controller as a part of the reset and enable
     * |        |          |Software cannot enable a port by writing a one to this field
     * |        |          |The host controller will only set this bit to a one when the reset sequence determines that the attached device is a high-speed device.
     * |        |          |Ports can be disabled by either a fault condition (disconnect event or other fault condition) or by host software
     * |        |          |Note that the bit status does not change until the port state actually changes
     * |        |          |There may be a delay in disabling or enabling a port due to other host controller and bus events.
     * |        |          |When the port is disabled (0b) downstream propagation of data is blocked on this port, except for reset.
     * |        |          |This field is zero if Port Power is zero.
     * |        |          |0 = Port Disabled.
     * |        |          |1 = Port Enabled.
     * |[3]     |PEC       |Port Enable/Disable Change (R/WC)
     * |        |          |For the root hub, this bit gets set to a one only when a port is disabled due to the appropriate conditions existing at the EOF2 point (See Chapter 11 of the USB Specification for the definition of a Port Error)
     * |        |          |Software clears this bit by writing a 1 to it.
     * |        |          |This field is zero if Port Power is zero.
     * |        |          |0 = No change.
     * |        |          |1 = Port enabled/disabled status has changed.
     * |[4]     |OCA       |Over-current Active (RO)
     * |        |          |This bit will automatically transition from a one to a zero when the over current condition is removed.
     * |        |          |0 = This port does not have an over-current condition.
     * |        |          |1 = This port currently has an over-current condition.
     * |[5]     |OCC       |Over-current Change (R/WC)
     * |        |          |1 = This bit gets set to a one when there is a change to Over-current Active
     * |        |          |Software clears this bit by writing a one to this bit position.
     * |[6]     |FPR       |Force Port Resume (R/W)
     * |        |          |This functionality defined for manipulating this bit depends on the value of the Suspend bit
     * |        |          |For example, if the port is not suspended (Suspend and Enabled bits are a one) and software transitions this bit to a one, then the effects on the bus are undefined.
     * |        |          |Software sets this bit to a 1 to drive resume signaling
     * |        |          |The Host Controller sets this bit to a 1 if a J-to-K transition is detected while the port is in the Suspend state
     * |        |          |When this bit transitions to a one because a J-to-K transition is detected, the Port Change Detect bit in the USBSTS register is also set to a one
     * |        |          |If software sets this bit to a one, the host controller must not set the Port Change Detect bit.
     * |        |          |Note that when the EHCI controller owns the port, the resume sequence follows the defined sequence documented in the USB Specification Revision 2.0
     * |        |          |The resume signaling (Full-speed 'K') is driven on the port as long as this bit remains a one
     * |        |          |Software must appropriately time the Resume and set this bit to a zero when the appropriate amount of time has elapsed
     * |        |          |Writing a zero (from one) causes the port to return to high-speed mode (forcing the bus below the port into a high-speed idle)
     * |        |          |This bit will remain a one until the port has switched to the high-speed idle
     * |        |          |The host controller must complete this transition within 2 milliseconds of software setting this bit to a zero.
     * |        |          |This field is zero if Port Power is zero.
     * |        |          |0 = No resume (K-state) detected/driven on port.
     * |        |          |1 = Resume detected/driven on port.
     * |[7]     |SUSPEND   |Suspend (R/W)
     * |        |          |Port Enabled Bit and Suspend bit of this register define the port states as follows:
     * |        |          |Port enable is 0 and suspend is 0 = Disable.
     * |        |          |Port enable is 0 and suspend is 1 = Disable.
     * |        |          |Port enable is 1 and suspend is 0 = Enable.
     * |        |          |Port enable is 1 and suspend is 1 = Suspend.
     * |        |          |When in suspend state, downstream propagation of data is blocked on this port, except for port reset
     * |        |          |The blocking occurs at the end of the current transaction, if a transaction was in progress when this bit was written to 1
     * |        |          |In the suspend state, the port is sensitive to resume detection
     * |        |          |Note that the bit status does not change until the port is suspended and that there may be a delay in suspending a port if there is a transaction currently in progress on the USB.
     * |        |          |A write of zero to this bit is ignored by the host controller
     * |        |          |The host controller will unconditionally set this bit to a zero when:
     * |        |          |Software sets the Force Port Resume bit to a zero (from a one).
     * |        |          |Software sets the Port Reset bit to a one (from a zero).
     * |        |          |If host software sets this bit to a one when the port is not enabled (i.e.
     * |        |          |Port enabled bit is a zero) the results are undefined.
     * |        |          |This field is zero if Port Power is zero.
     * |        |          |0 = Port not in suspend state.
     * |        |          |1 = Port in suspend state.
     * |[8]     |PRST      |Port Reset (R/W)
     * |        |          |When software writes a one to this bit (from a zero), the bus reset sequence as defined in the USB Specification Revision 2.0 is started
     * |        |          |Software writes a zero to this bit to terminate the bus reset sequence
     * |        |          |Software must keep this bit at a one long enough to ensure the reset sequence, as specified in the USB Specification Revision 2.0, completes
     * |        |          |Note: when software writes this bit to a one, it must also write a zero to the Port Enable bit.
     * |        |          |Note that when software writes a zero to this bit there may be a delay before the bit status changes to a zero
     * |        |          |The bit status will not read as a zero until after the reset has completed
     * |        |          |If the port is in high-speed mode after reset is complete, the host controller will automatically enable this port (e.g.
     * |        |          |set the Port Enable bit to a one)
     * |        |          |A host controller must terminate the reset and stabilize the state of the port within 2 milliseconds of software transitioning this bit from a one to a zero
     * |        |          |For example: if the port detects that the attached device is high-speed during reset, then the host controller must have the port in the enabled state within 2ms of software writing this bit to a zero.
     * |        |          |The HCHalted bit in the USBSTS register should be a zero before software attempts to use this bit
     * |        |          |The host controller may hold Port Reset asserted to a one when the HCHalted bit is a one.
     * |        |          |This field is zero if Port Power is zero.
     * |        |          |0 = Port is not in Reset.
     * |        |          |1 = Port is in Reset.
     * |[11:10] |LSTS      |Line Status (RO)
     * |        |          |These bits reflect the current logical levels of the D+ (bit 11) and D- (bit 10) signal lines
     * |        |          |These bits are used for detection of low-speed USB devices prior to the port reset and enable sequence
     * |        |          |This field is valid only when the port enable bit is zero and the current connect status bit is set to a one.
     * |        |          |The encoding of the bits are:
     * |        |          |Bits[11:10] USB State Interpretation
     * |        |          |00 = SE0 Not Low-speed device, perform EHCI reset.
     * |        |          |01 = K-state Low-speed device, release ownership of port.
     * |        |          |10 = J-state Not Low-speed device, perform EHCI reset.
     * |        |          |11 = Undefined Not Low-speed device, perform EHCI reset.
     * |        |          |This value of this field is undefined if Port Power is zero.
     * |[12]    |PP        |Port Power (PP)
     * |        |          |Host controller has port power control switches
     * |        |          |This bit represents the Current setting of the switch (0 = off, 1 = on)
     * |        |          |When power is not available on a port (i.e.
     * |        |          |PP equals a 0), the port is nonfunctional and will not report attaches, detaches, etc.
     * |        |          |When an over-current condition is detected on a powered port and PPC is a one, the PP bit in each affected port may be transitioned by the host controller from a 1 to 0 (removing power from the port).
     * |[13]    |PO        |Port Owner (R/W)
     * |        |          |This bit unconditionally goes to a 0b when the Configured bit in the CONFIGFLAG register makes a 0 to 1 transition
     * |        |          |This bit unconditionally goes to 1 whenever the Configured bit is zero.
     * |        |          |System software uses this field to release ownership of the port to a selected host controller (in the event that the attached device is not a high-speed device)
     * |        |          |Software writes a one to this bit when the attached device is not a high-speed device
     * |        |          |A one in this bit means that a companion host controller owns and controls the port.
     * |[19:16] |PTC       |Port Test Control (R/W)
     * |        |          |When this field is zero, the port is NOT operating in a test mode
     * |        |          |A non-zero value indicates that it is operating in test mode and the specific test mode is indicated by the specific value
     * |        |          |The encoding of the test mode bits are (0x6 ~ 0xF are reserved):
     * |        |          |Bits Test Mode
     * |        |          |0x0 = Test mode not enabled.
     * |        |          |0x1 = Test J_STATE.
     * |        |          |0x2 = Test K_STATE.
     * |        |          |0x3 = Test SE0_NAK.
     * |        |          |0x4 = Test Packet.
     * |        |          |0x5 = Test FORCE_ENABLE.
     * @var HSUSBH_T::USBPCR0
     * Offset: 0xC4  USB PHY 0 Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[8]     |SUSPEND   |Suspend Assertion
     * |        |          |This bit controls the suspend mode of USB PHY 0.
     * |        |          |While PHY was suspended, all circuits of PHY were powered down and outputs are tri-state.
     * |        |          |This bit is 1'b0 in default
     * |        |          |This means the USB PHY 0 is suspended in default
     * |        |          |It is necessary to set this bit 1'b1 to make USB PHY 0 leave suspend mode before doing configuration of USB host.
     * |        |          |0 = USB PHY 0 was suspended.
     * |        |          |1 = USB PHY 0 was not suspended.
     * |[11]    |CLKVALID  |UTMI Clock Valid
     * |        |          |This bit is a flag to indicate if the UTMI clock from USB 2.0 PHY is ready
     * |        |          |S/W program must prevent to write other control registers before this UTMI clock valid flag is active.
     * |        |          |0 = UTMI clock is not valid.
     * |        |          |1 = UTMI clock is valid.
     * @var HSUSBH_T::USBPCR1
     * Offset: 0xC8  USB PHY 1 Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[8]     |SUSPEND   |Suspend Assertion
     * |        |          |This bit controls the suspend mode of USB PHY 1.
     * |        |          |While PHY was suspended, all circuits of PHY were powered down and outputs are tri-state.
     * |        |          |This bit is 1'b0 in default
     * |        |          |This means the USB PHY 0 is suspended in default
     * |        |          |It is necessary to set this bit 1'b1 to make USB PHY 0 leave suspend mode before doing configuration of USB host.
     * |        |          |0 = USB PHY 1 was suspended.
     * |        |          |1 = USB PHY 1 was not suspended.
     */
    __I  uint32_t EHCVNR;                /*!< [0x0000] EHCI Version Number Register                                     */
    __I  uint32_t EHCSPR;                /*!< [0x0004] EHCI Structural Parameters Register                              */
    __I  uint32_t EHCCPR;                /*!< [0x0008] EHCI Capability Parameters Register                              */
    __I  uint32_t RESERVE0[5];
    __IO uint32_t UCMDR;                 /*!< [0x0020] USB Command Register                                             */
    __IO uint32_t USTSR;                 /*!< [0x0024] USB Status Register                                              */
    __IO uint32_t UIENR;                 /*!< [0x0028] USB Interrupt Enable Register                                    */
    __IO uint32_t UFINDR;                /*!< [0x002c] USB Frame Index Register                                         */
    __I  uint32_t RESERVE1[1];
    __IO uint32_t UPFLBAR;               /*!< [0x0034] USB Periodic Frame List Base Address Register                    */
    __IO uint32_t UCALAR;                /*!< [0x0038] USB Current Asynchronous List Address Register                   */
    __IO uint32_t UASSTR;                /*!< [0x003c] USB Asynchronous Schedule Sleep Timer Register                   */
    __I  uint32_t RESERVE2[8];
    __IO uint32_t UCFGR;                 /*!< [0x0060] USB Configure Flag Register                                      */
    __IO uint32_t UPSCR[2];              /*!< [0x0064] ~ [0x0068] USB Port 0 & 1 Status and Control Register            */
    __I  uint32_t RESERVE3[22];
    __IO uint32_t USBPCR0;               /*!< [0x00c4] USB PHY 0 Control Register                                       */
    __IO uint32_t USBPCR1;               /*!< [0x00c8] USB PHY 1 Control Register                                       */

} HSUSBH_T;

/**
    @addtogroup HSUSBH_CONST HSUSBH Bit Field Definition
    Constant Definitions for HSUSBH Controller
@{ */

#define HSUSBH_EHCVNR_CRLEN_Pos          (0)                                               /*!< HSUSBH_T::EHCVNR: CRLEN Position       */
#define HSUSBH_EHCVNR_CRLEN_Msk          (0xfful << HSUSBH_EHCVNR_CRLEN_Pos)               /*!< HSUSBH_T::EHCVNR: CRLEN Mask           */

#define HSUSBH_EHCVNR_VERSION_Pos        (16)                                              /*!< HSUSBH_T::EHCVNR: VERSION Position     */
#define HSUSBH_EHCVNR_VERSION_Msk        (0xfffful << HSUSBH_EHCVNR_VERSION_Pos)           /*!< HSUSBH_T::EHCVNR: VERSION Mask         */

#define HSUSBH_EHCSPR_N_PORTS_Pos        (0)                                               /*!< HSUSBH_T::EHCSPR: N_PORTS Position     */
#define HSUSBH_EHCSPR_N_PORTS_Msk        (0xful << HSUSBH_EHCSPR_N_PORTS_Pos)              /*!< HSUSBH_T::EHCSPR: N_PORTS Mask         */

#define HSUSBH_EHCSPR_PPC_Pos            (4)                                               /*!< HSUSBH_T::EHCSPR: PPC Position         */
#define HSUSBH_EHCSPR_PPC_Msk            (0x1ul << HSUSBH_EHCSPR_PPC_Pos)                  /*!< HSUSBH_T::EHCSPR: PPC Mask             */

#define HSUSBH_EHCSPR_N_PCC_Pos          (8)                                               /*!< HSUSBH_T::EHCSPR: N_PCC Position       */
#define HSUSBH_EHCSPR_N_PCC_Msk          (0xful << HSUSBH_EHCSPR_N_PCC_Pos)                /*!< HSUSBH_T::EHCSPR: N_PCC Mask           */

#define HSUSBH_EHCSPR_N_CC_Pos           (12)                                              /*!< HSUSBH_T::EHCSPR: N_CC Position        */
#define HSUSBH_EHCSPR_N_CC_Msk           (0xful << HSUSBH_EHCSPR_N_CC_Pos)                 /*!< HSUSBH_T::EHCSPR: N_CC Mask            */

#define HSUSBH_EHCCPR_AC64_Pos           (0)                                               /*!< HSUSBH_T::EHCCPR: AC64 Position        */
#define HSUSBH_EHCCPR_AC64_Msk           (0x1ul << HSUSBH_EHCCPR_AC64_Pos)                 /*!< HSUSBH_T::EHCCPR: AC64 Mask            */

#define HSUSBH_EHCCPR_PFLF_Pos           (1)                                               /*!< HSUSBH_T::EHCCPR: PFLF Position        */
#define HSUSBH_EHCCPR_PFLF_Msk           (0x1ul << HSUSBH_EHCCPR_PFLF_Pos)                 /*!< HSUSBH_T::EHCCPR: PFLF Mask            */

#define HSUSBH_EHCCPR_ASPC_Pos           (2)                                               /*!< HSUSBH_T::EHCCPR: ASPC Position        */
#define HSUSBH_EHCCPR_ASPC_Msk           (0x1ul << HSUSBH_EHCCPR_ASPC_Pos)                 /*!< HSUSBH_T::EHCCPR: ASPC Mask            */

#define HSUSBH_EHCCPR_IST_Pos            (4)                                               /*!< HSUSBH_T::EHCCPR: IST Position         */
#define HSUSBH_EHCCPR_IST_Msk            (0xful << HSUSBH_EHCCPR_IST_Pos)                  /*!< HSUSBH_T::EHCCPR: IST Mask             */

#define HSUSBH_EHCCPR_EECP_Pos           (8)                                               /*!< HSUSBH_T::EHCCPR: EECP Position        */
#define HSUSBH_EHCCPR_EECP_Msk           (0xfful << HSUSBH_EHCCPR_EECP_Pos)                /*!< HSUSBH_T::EHCCPR: EECP Mask            */

#define HSUSBH_UCMDR_RUN_Pos             (0)                                               /*!< HSUSBH_T::UCMDR: RUN Position          */
#define HSUSBH_UCMDR_RUN_Msk             (0x1ul << HSUSBH_UCMDR_RUN_Pos)                   /*!< HSUSBH_T::UCMDR: RUN Mask              */

#define HSUSBH_UCMDR_HCRST_Pos           (1)                                               /*!< HSUSBH_T::UCMDR: HCRST Position        */
#define HSUSBH_UCMDR_HCRST_Msk           (0x1ul << HSUSBH_UCMDR_HCRST_Pos)                 /*!< HSUSBH_T::UCMDR: HCRST Mask            */

#define HSUSBH_UCMDR_FLSZ_Pos            (2)                                               /*!< HSUSBH_T::UCMDR: FLSZ Position         */
#define HSUSBH_UCMDR_FLSZ_Msk            (0x3ul << HSUSBH_UCMDR_FLSZ_Pos)                  /*!< HSUSBH_T::UCMDR: FLSZ Mask             */

#define HSUSBH_UCMDR_PSEN_Pos            (4)                                               /*!< HSUSBH_T::UCMDR: PSEN Position         */
#define HSUSBH_UCMDR_PSEN_Msk            (0x1ul << HSUSBH_UCMDR_PSEN_Pos)                  /*!< HSUSBH_T::UCMDR: PSEN Mask             */

#define HSUSBH_UCMDR_ASEN_Pos            (5)                                               /*!< HSUSBH_T::UCMDR: ASEN Position         */
#define HSUSBH_UCMDR_ASEN_Msk            (0x1ul << HSUSBH_UCMDR_ASEN_Pos)                  /*!< HSUSBH_T::UCMDR: ASEN Mask             */

#define HSUSBH_UCMDR_IAAD_Pos            (6)                                               /*!< HSUSBH_T::UCMDR: IAAD Position         */
#define HSUSBH_UCMDR_IAAD_Msk            (0x1ul << HSUSBH_UCMDR_IAAD_Pos)                  /*!< HSUSBH_T::UCMDR: IAAD Mask             */

#define HSUSBH_UCMDR_ITC_Pos             (16)                                              /*!< HSUSBH_T::UCMDR: ITC Position          */
#define HSUSBH_UCMDR_ITC_Msk             (0xfful << HSUSBH_UCMDR_ITC_Pos)                  /*!< HSUSBH_T::UCMDR: ITC Mask              */

#define HSUSBH_USTSR_USBINT_Pos          (0)                                               /*!< HSUSBH_T::USTSR: USBINT Position       */
#define HSUSBH_USTSR_USBINT_Msk          (0x1ul << HSUSBH_USTSR_USBINT_Pos)                /*!< HSUSBH_T::USTSR: USBINT Mask           */

#define HSUSBH_USTSR_UERRINT_Pos         (1)                                               /*!< HSUSBH_T::USTSR: UERRINT Position      */
#define HSUSBH_USTSR_UERRINT_Msk         (0x1ul << HSUSBH_USTSR_UERRINT_Pos)               /*!< HSUSBH_T::USTSR: UERRINT Mask          */

#define HSUSBH_USTSR_PCD_Pos             (2)                                               /*!< HSUSBH_T::USTSR: PCD Position          */
#define HSUSBH_USTSR_PCD_Msk             (0x1ul << HSUSBH_USTSR_PCD_Pos)                   /*!< HSUSBH_T::USTSR: PCD Mask              */

#define HSUSBH_USTSR_FLR_Pos             (3)                                               /*!< HSUSBH_T::USTSR: FLR Position          */
#define HSUSBH_USTSR_FLR_Msk             (0x1ul << HSUSBH_USTSR_FLR_Pos)                   /*!< HSUSBH_T::USTSR: FLR Mask              */

#define HSUSBH_USTSR_HSERR_Pos           (4)                                               /*!< HSUSBH_T::USTSR: HSERR Position        */
#define HSUSBH_USTSR_HSERR_Msk           (0x1ul << HSUSBH_USTSR_HSERR_Pos)                 /*!< HSUSBH_T::USTSR: HSERR Mask            */

#define HSUSBH_USTSR_IAA_Pos             (5)                                               /*!< HSUSBH_T::USTSR: IAA Position          */
#define HSUSBH_USTSR_IAA_Msk             (0x1ul << HSUSBH_USTSR_IAA_Pos)                   /*!< HSUSBH_T::USTSR: IAA Mask              */

#define HSUSBH_USTSR_HCHalted_Pos        (12)                                              /*!< HSUSBH_T::USTSR: HCHalted Position     */
#define HSUSBH_USTSR_HCHalted_Msk        (0x1ul << HSUSBH_USTSR_HCHalted_Pos)              /*!< HSUSBH_T::USTSR: HCHalted Mask         */

#define HSUSBH_USTSR_RECLA_Pos           (13)                                              /*!< HSUSBH_T::USTSR: RECLA Position        */
#define HSUSBH_USTSR_RECLA_Msk           (0x1ul << HSUSBH_USTSR_RECLA_Pos)                 /*!< HSUSBH_T::USTSR: RECLA Mask            */

#define HSUSBH_USTSR_PSS_Pos             (14)                                              /*!< HSUSBH_T::USTSR: PSS Position          */
#define HSUSBH_USTSR_PSS_Msk             (0x1ul << HSUSBH_USTSR_PSS_Pos)                   /*!< HSUSBH_T::USTSR: PSS Mask              */

#define HSUSBH_USTSR_ASS_Pos             (15)                                              /*!< HSUSBH_T::USTSR: ASS Position          */
#define HSUSBH_USTSR_ASS_Msk             (0x1ul << HSUSBH_USTSR_ASS_Pos)                   /*!< HSUSBH_T::USTSR: ASS Mask              */

#define HSUSBH_UIENR_USBIEN_Pos          (0)                                               /*!< HSUSBH_T::UIENR: USBIEN Position       */
#define HSUSBH_UIENR_USBIEN_Msk          (0x1ul << HSUSBH_UIENR_USBIEN_Pos)                /*!< HSUSBH_T::UIENR: USBIEN Mask           */

#define HSUSBH_UIENR_UERRIEN_Pos         (1)                                               /*!< HSUSBH_T::UIENR: UERRIEN Position      */
#define HSUSBH_UIENR_UERRIEN_Msk         (0x1ul << HSUSBH_UIENR_UERRIEN_Pos)               /*!< HSUSBH_T::UIENR: UERRIEN Mask          */

#define HSUSBH_UIENR_PCIEN_Pos           (2)                                               /*!< HSUSBH_T::UIENR: PCIEN Position        */
#define HSUSBH_UIENR_PCIEN_Msk           (0x1ul << HSUSBH_UIENR_PCIEN_Pos)                 /*!< HSUSBH_T::UIENR: PCIEN Mask            */

#define HSUSBH_UIENR_FLREN_Pos           (3)                                               /*!< HSUSBH_T::UIENR: FLREN Position        */
#define HSUSBH_UIENR_FLREN_Msk           (0x1ul << HSUSBH_UIENR_FLREN_Pos)                 /*!< HSUSBH_T::UIENR: FLREN Mask            */

#define HSUSBH_UIENR_HSERREN_Pos         (4)                                               /*!< HSUSBH_T::UIENR: HSERREN Position      */
#define HSUSBH_UIENR_HSERREN_Msk         (0x1ul << HSUSBH_UIENR_HSERREN_Pos)               /*!< HSUSBH_T::UIENR: HSERREN Mask          */

#define HSUSBH_UIENR_IAAEN_Pos           (5)                                               /*!< HSUSBH_T::UIENR: IAAEN Position        */
#define HSUSBH_UIENR_IAAEN_Msk           (0x1ul << HSUSBH_UIENR_IAAEN_Pos)                 /*!< HSUSBH_T::UIENR: IAAEN Mask            */

#define HSUSBH_UFINDR_FI_Pos             (0)                                               /*!< HSUSBH_T::UFINDR: FI Position          */
#define HSUSBH_UFINDR_FI_Msk             (0x3ffful << HSUSBH_UFINDR_FI_Pos)                /*!< HSUSBH_T::UFINDR: FI Mask              */

#define HSUSBH_UPFLBAR_BADDR_Pos         (12)                                              /*!< HSUSBH_T::UPFLBAR: BADDR Position      */
#define HSUSBH_UPFLBAR_BADDR_Msk         (0xffffful << HSUSBH_UPFLBAR_BADDR_Pos)           /*!< HSUSBH_T::UPFLBAR: BADDR Mask          */

#define HSUSBH_UCALAR_LPL_Pos            (5)                                               /*!< HSUSBH_T::UCALAR: LPL Position         */
#define HSUSBH_UCALAR_LPL_Msk            (0x7fffffful << HSUSBH_UCALAR_LPL_Pos)            /*!< HSUSBH_T::UCALAR: LPL Mask             */

#define HSUSBH_UASSTR_ASSTMR_Pos         (0)                                               /*!< HSUSBH_T::UASSTR: ASSTMR Position      */
#define HSUSBH_UASSTR_ASSTMR_Msk         (0xffful << HSUSBH_UASSTR_ASSTMR_Pos)             /*!< HSUSBH_T::UASSTR: ASSTMR Mask          */

#define HSUSBH_UCFGR_CF_Pos              (0)                                               /*!< HSUSBH_T::UCFGR: CF Position           */
#define HSUSBH_UCFGR_CF_Msk              (0x1ul << HSUSBH_UCFGR_CF_Pos)                    /*!< HSUSBH_T::UCFGR: CF Mask               */

#define HSUSBH_UPSCR_CCS_Pos             (0)                                               /*!< HSUSBH_T::UPSCR[2]: CCS Position       */
#define HSUSBH_UPSCR_CCS_Msk             (0x1ul << HSUSBH_UPSCR_CCS_Pos)                   /*!< HSUSBH_T::UPSCR[2]: CCS Mask           */

#define HSUSBH_UPSCR_CSC_Pos             (1)                                               /*!< HSUSBH_T::UPSCR[2]: CSC Position       */
#define HSUSBH_UPSCR_CSC_Msk             (0x1ul << HSUSBH_UPSCR_CSC_Pos)                   /*!< HSUSBH_T::UPSCR[2]: CSC Mask           */

#define HSUSBH_UPSCR_PE_Pos              (2)                                               /*!< HSUSBH_T::UPSCR[2]: PE Position        */
#define HSUSBH_UPSCR_PE_Msk              (0x1ul << HSUSBH_UPSCR_PE_Pos)                    /*!< HSUSBH_T::UPSCR[2]: PE Mask            */

#define HSUSBH_UPSCR_PEC_Pos             (3)                                               /*!< HSUSBH_T::UPSCR[2]: PEC Position       */
#define HSUSBH_UPSCR_PEC_Msk             (0x1ul << HSUSBH_UPSCR_PEC_Pos)                   /*!< HSUSBH_T::UPSCR[2]: PEC Mask           */

#define HSUSBH_UPSCR_OCA_Pos             (4)                                               /*!< HSUSBH_T::UPSCR[2]: OCA Position       */
#define HSUSBH_UPSCR_OCA_Msk             (0x1ul << HSUSBH_UPSCR_OCA_Pos)                   /*!< HSUSBH_T::UPSCR[2]: OCA Mask           */

#define HSUSBH_UPSCR_OCC_Pos             (5)                                               /*!< HSUSBH_T::UPSCR[2]: OCC Position       */
#define HSUSBH_UPSCR_OCC_Msk             (0x1ul << HSUSBH_UPSCR_OCC_Pos)                   /*!< HSUSBH_T::UPSCR[2]: OCC Mask           */

#define HSUSBH_UPSCR_FPR_Pos             (6)                                               /*!< HSUSBH_T::UPSCR[2]: FPR Position       */
#define HSUSBH_UPSCR_FPR_Msk             (0x1ul << HSUSBH_UPSCR_FPR_Pos)                   /*!< HSUSBH_T::UPSCR[2]: FPR Mask           */

#define HSUSBH_UPSCR_SUSPEND_Pos         (7)                                               /*!< HSUSBH_T::UPSCR[2]: SUSPEND Position   */
#define HSUSBH_UPSCR_SUSPEND_Msk         (0x1ul << HSUSBH_UPSCR_SUSPEND_Pos)               /*!< HSUSBH_T::UPSCR[2]: SUSPEND Mask       */

#define HSUSBH_UPSCR_PRST_Pos            (8)                                               /*!< HSUSBH_T::UPSCR[2]: PRST Position      */
#define HSUSBH_UPSCR_PRST_Msk            (0x1ul << HSUSBH_UPSCR_PRST_Pos)                  /*!< HSUSBH_T::UPSCR[2]: PRST Mask          */

#define HSUSBH_UPSCR_LSTS_Pos            (10)                                              /*!< HSUSBH_T::UPSCR[2]: LSTS Position      */
#define HSUSBH_UPSCR_LSTS_Msk            (0x3ul << HSUSBH_UPSCR_LSTS_Pos)                  /*!< HSUSBH_T::UPSCR[2]: LSTS Mask          */

#define HSUSBH_UPSCR_PP_Pos              (12)                                              /*!< HSUSBH_T::UPSCR[2]: PP Position        */
#define HSUSBH_UPSCR_PP_Msk              (0x1ul << HSUSBH_UPSCR_PP_Pos)                    /*!< HSUSBH_T::UPSCR[2]: PP Mask            */

#define HSUSBH_UPSCR_PO_Pos              (13)                                              /*!< HSUSBH_T::UPSCR[2]: PO Position        */
#define HSUSBH_UPSCR_PO_Msk              (0x1ul << HSUSBH_UPSCR_PO_Pos)                    /*!< HSUSBH_T::UPSCR[2]: PO Mask            */

#define HSUSBH_UPSCR_PTC_Pos             (16)                                              /*!< HSUSBH_T::UPSCR[2]: PTC Position       */
#define HSUSBH_UPSCR_PTC_Msk             (0xful << HSUSBH_UPSCR_PTC_Pos)                   /*!< HSUSBH_T::UPSCR[2]: PTC Mask           */

#define HSUSBH_USBPCR0_SUSPEND_Pos       (8)                                               /*!< HSUSBH_T::USBPCR0: SUSPEND Position    */
#define HSUSBH_USBPCR0_SUSPEND_Msk       (0x1ul << HSUSBH_USBPCR0_SUSPEND_Pos)             /*!< HSUSBH_T::USBPCR0: SUSPEND Mask        */

#define HSUSBH_USBPCR0_CLKVALID_Pos      (11)                                              /*!< HSUSBH_T::USBPCR0: CLKVALID Position   */
#define HSUSBH_USBPCR0_CLKVALID_Msk      (0x1ul << HSUSBH_USBPCR0_CLKVALID_Pos)            /*!< HSUSBH_T::USBPCR0: CLKVALID Mask       */

#define HSUSBH_USBPCR1_SUSPEND_Pos       (8)                                               /*!< HSUSBH_T::USBPCR1: SUSPEND Position    */
#define HSUSBH_USBPCR1_SUSPEND_Msk       (0x1ul << HSUSBH_USBPCR1_SUSPEND_Pos)             /*!< HSUSBH_T::USBPCR1: SUSPEND Mask        */

/**@}*/ /* HSUSBH_CONST */
/**@}*/ /* end of HSUSBH register group */

#define USBH                 ((USBH_T *)0xB0007000)
#define HSUSBH               ((HSUSBH_T *)0xB0005000)


/// @endcond /*HIDDEN_SYMBOLS*/

#endif  /* _USBH_CONFIG_H_ */

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/

