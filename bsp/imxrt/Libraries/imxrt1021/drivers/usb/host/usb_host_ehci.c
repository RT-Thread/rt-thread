/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <usb/include/usb_device_config.h>
#if ((defined USB_HOST_CONFIG_EHCI) && (USB_HOST_CONFIG_EHCI > 0U))
#include "usb_host.h"
#include "usb_host_hci.h"
#include "usb_host_devices.h"
#include "fsl_device_registers.h"
#include "usb_host_ehci.h"
#include "usb_phy.h"
#if ((defined USB_HOST_CONFIG_COMPLIANCE_TEST) && (USB_HOST_CONFIG_COMPLIANCE_TEST))
#include "usb_host.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if defined(USB_STACK_USE_DEDICATED_RAM) && (USB_STACK_USE_DEDICATED_RAM > 0U)

#error The SOC does not suppoort dedicated RAM case.

#endif

#define USB_HOST_EHCI_BANDWIDTH_DELAY (3500U)
#define USB_HOST_EHCI_BANDWIDTH_HUB_LS_SETUP (333U)
#define USB_HOST_EHCI_BANDWIDTH_FRAME_TOTOAL_TIME (900U)

#if ((defined USB_HOST_CONFIG_COMPLIANCE_TEST) && (USB_HOST_CONFIG_COMPLIANCE_TEST))
#define USB_HOST_EHCI_TEST_DESCRIPTOR_LENGTH (18U)
#define USB_HOST_EHCI_PORTSC_PTC_J_STATE (0x01U)
#define USB_HOST_EHCI_PORTSC_PTC_K_STATE (0x02U)
#define USB_HOST_EHCI_PORTSC_PTC_SE0_NAK (0x03U)
#define USB_HOST_EHCI_PORTSC_PTC_PACKET (0x04U)
#define USB_HOST_EHCI_PORTSC_PTC_FORCE_ENABLE_HS (0x05U)
#define USB_HOST_EHCI_PORTSC_PTC_FORCE_ENABLE_FS (0x06U)
#define USB_HOST_EHCI_PORTSC_PTC_FORCE_ENABLE_LS (0x07U)
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief compute data bandwidth time.
 *
 * @param speed       data speed.
 * @param pipeType    data type.
 * @param direction   data direction.
 * @param dataLength  data length.
 *
 *@return time value.
 */
static uint32_t USB_HostBandwidthComputeTime(uint8_t speed, uint8_t pipeType, uint8_t direction, uint32_t dataLength);

/*!
 * @brief compute current allocated bandwidth when ehci work as full-speed or low-speed host.
 *
 * @param ehciInstance    ehci instance pointer.
 * @param frameIndex      frame index.
 * @param frameBandwidths return frame bandwidth data.
 */
static void USB_HostBandwidthFslsHostComputeCurrent(usb_host_ehci_instance_t *ehciInstance,
                                                    uint16_t frameIndex,
                                                    uint16_t *frameBandwidth);

/*!
 * @brief compute current hub's allocated FS/LS bandwidth when ehci work as hi-speed host.
 *
 * @param ehciInstance    ehci instance pointer.
 * @param hubNumber       hub address.
 * @param frameIndex      frame index.
 * @param frameBandwidths return frame bandwidth data.
 */
static void USB_HostBandwidthHsHostComputeCurrentFsls(usb_host_ehci_instance_t *ehciInstance,
                                                      uint32_t hubNumber,
                                                      uint16_t frameIndex,
                                                      uint8_t frameBandwidths[8]);

/*!
 * @brief compute current allocated HS bandwidth when ehci work as hi-speed host.
 *
 * @param ehciInstance         ehci instance pointer.
 * @param frameIndex      frame index.
 * @param frameBandwidths return frame bandwidth data.
 */
static void USB_HostBandwidthHsHostComputeCurrentHsAll(usb_host_ehci_instance_t *ehciInstance,
                                                       uint16_t frameIndex,
                                                       uint8_t frameBandwidths[8]);

/*!
 * @brief allocate HS bandwidth when host work as high-speed host.
 *
 * @param ehciInstance         ehci instance pointer.
 * @param uframeInterval  micro-frame interval.
 * @param timeData        time for allocating.
 * @param uframe_index_out return start uframe index.
 *
 * @return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostBandwidthHsHostAllocateHsCommon(usb_host_ehci_instance_t *ehciInstance,
                                                            uint16_t uframeInterval,
                                                            uint16_t timeData,
                                                            uint16_t *uframeIndexOut);

/*!
 * @brief allocate HS interrupt bandwidth when host work as high-speed host.
 *
 * @param ehciInstance         ehci instance pointer.
 * @param ehciPipePointer    ehci pipe pointer.
 *
 * @return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostBandwidthHsHostAllocateInterrupt(usb_host_ehci_instance_t *ehciInstance,
                                                             usb_host_ehci_pipe_t *ehciPipePointer);

/*!
 * @brief allocate bandwidth when host work as full-speed or low-speed host.
 *
 * @param ehciInstance         ehci instance pointer.
 * @param ehciPipePointer    ehci pipe pointer.
 *
 * @return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostBandwidthFslsHostAllocate(usb_host_ehci_instance_t *ehciInstance,
                                                      usb_host_ehci_pipe_t *ehciPipePointer);

/*!
 * @brief get the 2 power value of uint8_t.
 *
 * @param value     input uint8_t value.
 */
static uint8_t USB_HostEhciGet2PowerValue(uint8_t value);

/*!
 * @brief memory zero.
 *
 * @param buffer     buffer pointer.
 * @param length     buffer length.
 */
static void USB_HostEhciZeroMem(uint32_t *buffer, uint32_t length);

/*!
 * @brief host ehci delay.
 *
 * @param ehciIpBase     ehci ip base address.
 * @param ms          millisecond.
 */
static void USB_HostEhciDelay(USBHS_Type *ehciIpBase, uint32_t ms);

/*!
 * @brief host ehci start async schedule.
 *
 * @param ehciInstance    ehci instance pointer.
 */
static void USB_HostEhciStartAsync(usb_host_ehci_instance_t *ehciInstance);

/*!
 * @brief host ehci stop async schedule.
 *
 * @param ehciInstance    ehci instance pointer.
 */
static void USB_HostEhciStopAsync(usb_host_ehci_instance_t *ehciInstance);

/*!
 * @brief host ehci start periodic schedule.
 *
 * @param ehciInstance    ehci instance pointer.
 */
static void USB_HostEhciStartPeriodic(usb_host_ehci_instance_t *ehciInstance);

/*!
 * @brief host ehci stop periodic schedule.
 *
 * @param ehciInstance    ehci instance pointer.
 */
static void USB_HostEhciStopPeriodic(usb_host_ehci_instance_t *ehciInstance);

/*!
 * @brief initialize the qtd for one transfer.
 *
 * @param ehciInstance      ehci instance pointer.
 * @param ehciPipePointer ehci pipe pointer.
 * @param transfer      transfer information.
 *
 *@return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostEhciQhQtdListInit(usb_host_ehci_instance_t *ehciInstance,
                                              usb_host_ehci_pipe_t *ehciPipePointer,
                                              usb_host_transfer_t *transfer);

/*!
 * @brief release the qtd list.
 *
 * @param ehciInstance   ehci instance pointer.
 * @param ehciQtdStart   qtd list start pointer.
 * @param ehciQtdEnd     qtd list end pointer.
 *
 *@return the transfer's length.
 */
static uint32_t USB_HostEhciQtdListRelease(usb_host_ehci_instance_t *ehciInstance,
                                           usb_host_ehci_qtd_t *ehciQtdStart,
                                           usb_host_ehci_qtd_t *ehciQtdEnd);

/*!
 * @brief de-initialize qh's linking qtd list.
 * 1. remove qtd from qh; 2. remove transfer from qh; 3. release qtd; 4. transfer callback.
 *
 * @param ehciInstance    ehci instance pointer.
 * @param ehciPipePointer ehci pipe.
 *
 *@return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostEhciQhQtdListDeinit(usb_host_ehci_instance_t *ehciInstance,
                                                usb_host_ehci_pipe_t *ehciPipePointer);

/*!
 * @brief de-initialize transfer's linking qtd list.
 * 1. stop this qh schedule; 2. remove qtd from qh; 3. remove transfer from qh; 4. release qtd; 5. transfer callback; 6.
 *start this qh schedule.
 *
 * @param ehciInstance    ehci instance pointer.
 * @param ehciPipePointer ehci pipe pointer.
 * @param transfer        transfer information.
 *
 *@return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostEhciTransferQtdListDeinit(usb_host_ehci_instance_t *ehciInstance,
                                                      usb_host_ehci_pipe_t *ehciPipePointer,
                                                      usb_host_transfer_t *transfer);

/*!
 * @brief initialize QH when opening one control, bulk or interrupt pipe.
 *
 * @param ehciInstance       ehci instance pointer.
 * @param ehciPipePointer    ehci pipe pointer.
 *
 * @return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostEhciQhInit(usb_host_ehci_instance_t *ehciInstance, usb_host_ehci_pipe_t *ehciPipePointer);

/*!
 * @brief de-initialize QH when closing one control, bulk or interrupt pipe.
 *
 * @param ehciInstance       ehci instance pointer.
 * @param ehciPipePointer    ehci pipe pointer.
 *
 * @return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostEhciQhDeinit(usb_host_ehci_instance_t *ehciInstance, usb_host_ehci_pipe_t *ehciPipePointer);

/*!
 * @brief add qh to one frame entry.
 *
 * @param ehciInstance      ehci instance pointer.
 * @param entryPointerValue entry pointer value.
 * @param framePos          frame index.
 * @param uframeInterval    micro-frame interval.
 */
static void USB_HostEhciAddQhToFrame(usb_host_ehci_instance_t *ehciInstance,
                                     uint32_t entryPointerValue,
                                     uint16_t framePos,
                                     uint16_t uframeInterval);

/*!
 * @brief remove entry from frame list.
 *
 * @param ehciInstance      ehci instance pointer.
 * @param entryPointerValue entry pointer value.
 * @param framePos          frame index.
 */
static void USB_HostEhciRemoveFromFrame(usb_host_ehci_instance_t *ehciInstance,
                                        uint32_t entryPointerValue,
                                        uint16_t framePos);

#if ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD))
/*!
 * @brief add sitd array to the frame list.
 *
 * @param ehciInstance      ehci instance pointer.
 * @param entryPointerValue entry pointer value.
 * @param startEntryPointer sitd entry pointer.
 */
static void USB_HostEhciLinkSitd(usb_host_ehci_instance_t *ehciInstance,
                                 usb_host_ehci_pipe_t *ehciPipePointer,
                                 void *startEntryPointer);

/*!
 * @brief initialize sitd array for one transfer.
 *
 * @param ehciInstance      ehci instance pointer.
 * @param ehciPipePointer   ehci pipe pointer.
 * @param transfer          transfer information.
 */
static usb_status_t USB_HostEhciSitdArrayInit(usb_host_ehci_instance_t *ehciInstance,
                                              usb_host_ehci_pipe_t *ehciPipePointer,
                                              usb_host_transfer_t *transfer);

/*!
 * @brief release sitd list.
 *
 * @param ehciInstance     ehci instance pointer.
 * @param startSitdPointer start sitd pointer.
 * @param endSitdPointer   end sitd pointer.
 *
 * @return transfer's result length.
 */
static uint32_t USB_HostEhciSitdArrayRelease(usb_host_ehci_instance_t *ehciInstance,
                                             usb_host_ehci_sitd_t *startSitdPointer,
                                             usb_host_ehci_sitd_t *endSitdPointer);

/*!
 * @brief de-initialize sitd list.
 * 1. remove transfer; 2. remove sitd from frame list and release sitd; 3. transfer callback
 *
 * @param ehciInstance    ehci instance pointer.
 * @param ehciPipePointer ehci pipe pointer.
 *
 * @return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostEhciSitdArrayDeinit(usb_host_ehci_instance_t *ehciInstance,
                                                usb_host_ehci_pipe_t *ehciPipePointer);
#endif /* USB_HOST_CONFIG_EHCI_MAX_SITD */

#if ((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD))
/*!
 * @brief compute the frame index when inserting itd.
 *
 * @param ehciInstance    ehci instance pointer.
 * @param lastLinkUframe  last inserted micro-frame.
 * @param startUframe     start micro-frame.
 * @param uframeInterval  micro-frame interval.
 *
 * @return frame index
 */
static uint32_t USB_HostEhciGetItdLinkFrame(usb_host_ehci_instance_t *ehciInstance,
                                            uint32_t lastLinkUframe,
                                            uint16_t startUframe,
                                            uint16_t uframeInterval);

/*!
 * @brief initialize itd list for one transfer.
 * 1. initialize itd list; 2. insert itd to frame list.
 *
 * @param ehciInstance    ehci instance pointer.
 * @param ehciPipePointer ehci pipe pointer.
 * @param transfer        transfer information.
 *
 * @return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostEhciItdArrayInit(usb_host_ehci_instance_t *ehciInstance,
                                             usb_host_ehci_pipe_t *ehciPipePointer,
                                             usb_host_transfer_t *transfer);

/*!
 * @brief release itd list.
 *
 * @param ehciInstance    ehci instance pointer.
 * @param startItdPointer start itd pointer.
 * @param endItdPointer   end itd pointer.
 *
 * @return transfer's result length.
 */
static uint32_t USB_HostEhciItdArrayRelease(usb_host_ehci_instance_t *ehciInstance,
                                            usb_host_ehci_itd_t *startItdPointer,
                                            usb_host_ehci_itd_t *endItdPointer);

/*!
 * @brief de-initialize itd list.
 * 1. remove transfer; 2. remove itd from frame list and release itd; 3. transfer callback
 *
 * @param ehciInstance    ehci instance pointer.
 * @param ehciPipePointer ehci pipe pointer.
 *
 * @return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostEhciItdArrayDeinit(usb_host_ehci_instance_t *ehciInstance,
                                               usb_host_ehci_pipe_t *ehciPipePointer);
#endif /* USB_HOST_CONFIG_EHCI_MAX_ITD */

/*!
 * @brief open control or bulk pipe.
 *
 * @param ehciInstance    ehci instance pointer.
 * @param ehciPipePointer ehci pipe pointer.
 *
 * @return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostEhciOpenControlBulk(usb_host_ehci_instance_t *ehciInstance,
                                                usb_host_ehci_pipe_t *ehciPipePointer);

/*!
 * @brief close control or bulk pipe.
 *
 * @param ehciInstance    ehci instance pointer.
 * @param ehciPipePointer ehci pipe pointer.
 *
 * @return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostEhciCloseControlBulk(usb_host_ehci_instance_t *ehciInstance,
                                                 usb_host_ehci_pipe_t *ehciPipePointer);

/*!
 * @brief open interrupt pipe.
 *
 * @param ehciInstance    ehci instance pointer.
 * @param ehciPipePointer ehci pipe pointer.
 *
 * @return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostEhciOpenInterrupt(usb_host_ehci_instance_t *ehciInstance,
                                              usb_host_ehci_pipe_t *ehciPipePointer);

/*!
 * @brief close interrupt pipe.
 *
 * @param ehciInstance    ehci instance pointer.
 * @param ehciPipePointer ehci pipe pointer.
 *
 * @return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostEhciCloseInterrupt(usb_host_ehci_instance_t *ehciInstance,
                                               usb_host_ehci_pipe_t *ehciPipePointer);

#if (((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD)) || \
     ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD)))
/*!
 * @brief open iso pipe.
 *
 * @param ehciInstance    ehci instance pointer.
 * @param ehciPipePointer ehci pipe pointer.
 *
 * @return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostEhciOpenIso(usb_host_ehci_instance_t *ehciInstance, usb_host_ehci_pipe_t *ehciPipePointer);

/*!
 * @brief close iso pipe.
 *
 * @param ehciInstance    ehci instance pointer.
 * @param ehciPipePointer ehci pipe pointer.
 *
 * @return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostEhciCloseIso(usb_host_ehci_instance_t *ehciInstance, usb_host_ehci_pipe_t *ehciPipePointer);

/*!
 * @brief allocate HS iso bandwidth when host work as high-speed host.
 *
 * @param ehciInstance         ehci instance pointer.
 * @param ehciPipePointer    ehci pipe pointer.
 *
 * @return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostBandwidthHsHostAllocateIso(usb_host_ehci_instance_t *ehciInstance,
                                                       usb_host_ehci_pipe_t *ehciPipePointer);

#endif

/*!
 * @brief reset ehci ip.
 *
 * @param ehciInstance      ehci instance pointer.
 *
 * @return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostEhciResetIP(usb_host_ehci_instance_t *ehciInstance);

/*!
 * @brief start ehci ip.
 *
 * @param ehciInstance      ehci instance pointer.
 *
 * @return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostEhciStartIP(usb_host_ehci_instance_t *ehciInstance);

/*!
 * @brief cancel pipe's transfers.
 *
 * @param ehciInstance    ehci instance pointer.
 * @param ehciPipePointer ehci pipe pointer.
 * @param transfer        the canceling transfer.
 *
 * @return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostEhciCancelPipe(usb_host_ehci_instance_t *ehciInstance,
                                           usb_host_ehci_pipe_t *ehciPipePointer,
                                           usb_host_transfer_t *transfer);

/*!
 * @brief control ehci bus.
 *
 * @param ehciInstance  ehci instance pointer.
 * @param bus_control   control code.
 *
 * @return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostEhciControlBus(usb_host_ehci_instance_t *ehciInstance, uint8_t busControl);

/*!
 * @brief ehci transaction done process function.
 *
 * @param ehciInstance      ehci instance pointer.
 */
void USB_HostEhciTransactionDone(usb_host_ehci_instance_t *ehciInstance);

/*!
 * @brief ehci port change interrupt process function.
 *
 * @param ehciInstance      ehci instance pointer.
 */
static void USB_HostEhciPortChange(usb_host_ehci_instance_t *ehciInstance);

/*!
 * @brief ehci timer0 interrupt process function.
 * cancel control/bulk transfer that time out.
 *
 * @param ehciInstance      ehci instance pointer.
 */
static void USB_HostEhciTimer0(usb_host_ehci_instance_t *ehciInstance);

#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
/*!
 * @brief ehci timer1 interrupt process function.
 * cancel control/bulk transfer that time out.
 *
 * @param ehciInstance      ehci instance pointer.
 */
static void USB_HostEhciTimer1(usb_host_ehci_instance_t *ehciInstance);
#endif

#if ((defined USB_HOST_CONFIG_COMPLIANCE_TEST) && (USB_HOST_CONFIG_COMPLIANCE_TEST))
/*!
 * @brief suspend bus.
 *
 * @param ehciInstance      ehci instance pointer.
 */
static void USB_HostEhciSuspendBus(usb_host_ehci_instance_t *ehciInstance);

/*!
 * @brief resume bus.
 *
 * @param ehciInstance      ehci instance pointer.
 */
static void USB_HostEhciResumeBus(usb_host_ehci_instance_t *ehciInstance);

extern usb_status_t USB_HostStandardSetGetDescriptor(usb_host_device_instance_t *deviceInstance,
                                                     usb_host_transfer_t *transfer,
                                                     void *param);
#endif /* USB_HOST_CONFIG_COMPLIANCE_TEST */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* EHCI controller driver instances. */
#if (USB_HOST_CONFIG_EHCI == 1U)
USB_RAM_ADDRESS_ALIGNMENT(4096)
USB_CONTROLLER_DATA static uint8_t s_UsbHostEhciFrameList1[USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE * 4];

#define USB_HOST_EHCI_FRAME_LIST_ARRAY \
    {                                  \
        &s_UsbHostEhciFrameList1[0]    \
    }

USB_RAM_ADDRESS_ALIGNMENT(64) USB_CONTROLLER_DATA static usb_host_ehci_data_t s_UsbHostEhciData1;
#define USB_HOST_EHCI_DATA_ARRAY \
    {                            \
        &s_UsbHostEhciData1      \
    }
#elif(USB_HOST_CONFIG_EHCI == 2U)
USB_RAM_ADDRESS_ALIGNMENT(4096)
USB_CONTROLLER_DATA static uint8_t s_UsbHostEhciFrameList1[USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE * 4];
USB_RAM_ADDRESS_ALIGNMENT(4096)
USB_CONTROLLER_DATA static uint8_t s_UsbHostEhciFrameList2[USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE * 4];
#define USB_HOST_EHCI_FRAME_LIST_ARRAY                           \
    {                                                            \
        &s_UsbHostEhciFrameList1[0], &s_UsbHostEhciFrameList2[0] \
    }

USB_RAM_ADDRESS_ALIGNMENT(64) USB_CONTROLLER_DATA static usb_host_ehci_data_t s_UsbHostEhciData1;
USB_RAM_ADDRESS_ALIGNMENT(64) USB_CONTROLLER_DATA static usb_host_ehci_data_t s_UsbHostEhciData2;
#define USB_HOST_EHCI_DATA_ARRAY                 \
    {                                            \
        &s_UsbHostEhciData1, &s_UsbHostEhciData2 \
    }
#else
#error "Please increase the instance count."
#endif

static uint8_t s_SlotMaxBandwidth[8] = {125, 125, 125, 125, 125, 125, 50, 0};

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
* @brief EHCI NC get USB NC bass address.
*
* This function is used to get USB NC bass address.
*
* @param[in] controllerId    EHCI controller ID; See the #usb_controller_index_t.
*
* @retval USB NC bass address.
*/
#if (defined(USB_HOST_CONFIG_LOW_POWER_MODE) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
#if (defined(FSL_FEATURE_SOC_USBNC_COUNT) && (FSL_FEATURE_SOC_USBNC_COUNT > 0U))
void *USB_EhciNCGetBase(uint8_t controllerId)
{
    void *usbNCBase = NULL;
#if ((defined FSL_FEATURE_SOC_USBNC_COUNT) && (FSL_FEATURE_SOC_USBNC_COUNT > 0U))
    uint32_t instance;
    uint32_t newinstance = 0;
    uint32_t usbnc_base_temp[] = USBNC_BASE_ADDRS;
    uint32_t usbnc_base[] = USBNC_BASE_ADDRS;

    if (controllerId < kUSB_ControllerEhci0)
    {
        return NULL;
    }

    controllerId = controllerId - kUSB_ControllerEhci0;

    for (instance = 0; instance < (sizeof(usbnc_base_temp) / sizeof(usbnc_base_temp[0])); instance++)
    {
        if (usbnc_base_temp[instance])
        {
            usbnc_base[newinstance++] = usbnc_base_temp[instance];
        }
    }
    if (controllerId > newinstance)
    {
        return NULL;
    }

    usbNCBase = (void *)usbnc_base[controllerId];
#endif
    return usbNCBase;
}
#endif
#endif

#if ((defined USB_HOST_CONFIG_COMPLIANCE_TEST) && (USB_HOST_CONFIG_COMPLIANCE_TEST))

usb_status_t USB_HostEhciTestSetMode(usb_host_ehci_instance_t *ehciInstance, uint32_t testMode)
{
    uint32_t ehciPortSC;

    ehciPortSC = ehciInstance->ehciIpBase->PORTSC1;
    ehciPortSC &= ~((uint32_t)USBHS_PORTSC1_PTC_MASK);   /* clear test mode bits */
    ehciPortSC |= (testMode << USBHS_PORTSC1_PTC_SHIFT); /* set test mode bits */
    ehciInstance->ehciIpBase->PORTSC1 = ehciPortSC;
    return kStatus_USB_Success;
}

static void USB_HostEhciTestSuspendResume(usb_host_ehci_instance_t *ehciInstance)
{
    uint8_t timeCount;
    timeCount = 15; /* 15s */
    while (timeCount--)
    {
        USB_HostEhciDelay(ehciInstance->ehciIpBase, 1000U);
    }
    USB_HostEhciSuspendBus(ehciInstance);
    timeCount = 15; /* 15s */
    while (timeCount--)
    {
        USB_HostEhciDelay(ehciInstance->ehciIpBase, 1000U);
    }

    USB_HostEhciResumeBus(ehciInstance);
}

static void USB_HostEhciTestCallback(void *param, usb_host_transfer_t *transfer, usb_status_t status)
{
    USB_HostFreeTransfer(param, transfer);
}

static void USB_HostEhciTestSingleStepGetDeviceDesc(usb_host_ehci_instance_t *ehciInstance,
                                                    usb_device_handle deviceHandle)
{
    usb_host_process_descriptor_param_t getDescriptorParam;
    usb_host_device_instance_t *deviceInstance = (usb_host_device_instance_t *)deviceHandle;
    usb_host_transfer_t *transfer;
    uint8_t timeCount;

    /* disable periodic shedule */
    USB_HostEhciStopPeriodic(ehciInstance);

    timeCount = 15; /* 15s */
    while (timeCount--)
    {
        USB_HostEhciDelay(ehciInstance->ehciIpBase, 1000U);
    }

    /* malloc one transfer */
    if (USB_HostMallocTransfer(ehciInstance->hostHandle, &transfer) != kStatus_USB_Success)
    {
#ifdef HOST_ECHO
        usb_echo("allocate transfer error\r\n");
#endif
        return;
    }

    getDescriptorParam.descriptorLength = sizeof(usb_descriptor_device_t);
    getDescriptorParam.descriptorLength = 18;
    getDescriptorParam.descriptorBuffer = (uint8_t *)&deviceInstance->deviceDescriptor;
    getDescriptorParam.descriptorType = USB_DESCRIPTOR_TYPE_DEVICE;
    getDescriptorParam.descriptorIndex = 0;
    getDescriptorParam.languageId = 0;
    transfer->callbackFn = USB_HostEhciTestCallback;
    transfer->callbackParam = ehciInstance->hostHandle;
    transfer->setupPacket->bmRequestType = USB_REQUEST_TYPE_DIR_IN;
    transfer->setupPacket->bRequest = USB_REQUEST_STANDARD_GET_DESCRIPTOR;
    transfer->setupPacket->wIndex = 0;
    transfer->setupPacket->wLength = 0;
    transfer->setupPacket->wValue = 0;
    USB_HostStandardSetGetDescriptor(deviceInstance, transfer, &getDescriptorParam);
}

static usb_status_t USB_HostEhciSingleStepQtdListInit(usb_host_ehci_instance_t *ehciInstance,
                                                      usb_host_ehci_pipe_t *ehciPipePointer,
                                                      usb_host_transfer_t *transfer,
                                                      uint8_t setupPhase)
{
    volatile usb_host_ehci_qh_t *vltQhPointer;
    usb_host_ehci_qtd_t *qtdPointer = NULL;
    volatile uint32_t *entryPointer;
    uint32_t qtdNumber;
    uint32_t dataLength;
    uint32_t dataAddress;
    uint8_t index;

    /* compute the qtd number */
    qtdNumber = 1;

    vltQhPointer = (volatile usb_host_ehci_qh_t *)ehciPipePointer->ehciQh;
    /* get qtd list */
    USB_HostEhciLock();
    if (qtdNumber <= ehciInstance->ehciQtdNumber)
    {
        ehciInstance->ehciQtdNumber -= qtdNumber;
        qtdPointer = NULL;
        do
        {
            if (qtdPointer != NULL)
            {
                qtdPointer->nextQtdPointer = (uint32_t)ehciInstance->ehciQtdHead;
            }
            qtdPointer = ehciInstance->ehciQtdHead;
            ehciInstance->ehciQtdHead = (usb_host_ehci_qtd_t *)qtdPointer->nextQtdPointer;
            qtdPointer->nextQtdPointer = 0;
        } while (--qtdNumber);
    }
    else
    {
        USB_HostEhciUnlock();
        return kStatus_USB_Error;
    }
    USB_HostEhciUnlock();

    /* int qTD */
    if (setupPhase == 1) /* setup transaction qtd init */
    {
        qtdPointer->alternateNextQtdPointer = EHCI_HOST_T_INVALID_VALUE;
        /* dt: need set; ioc: 0; C_Page: 0; PID Code: SETUP; Status: Active */
        qtdPointer->transferResults[0] = qtdPointer->transferResults[1] = 0;
        qtdPointer->transferResults[0] =
            ((0x00000000 << EHCI_HOST_QTD_DT_SHIFT) | (8 << EHCI_HOST_QTD_TOTAL_BYTES_SHIFT) |
             (EHCI_HOST_PID_SETUP << EHCI_HOST_QTD_PID_CODE_SHIFT) | (EHCI_HOST_QTD_STATUS_ACTIVE_MASK));
        dataAddress = (uint32_t)(transfer->setupPacket);
        qtdPointer->transferResults[1] = dataAddress; /* current offset is set too */
        /* set buffer pointer no matter data length */
        for (index = 0; index < 4; ++index)
        {
            qtdPointer->bufferPointers[index] = ((dataAddress + (index + 1) * 4 * 1024) & 0xFFFFF000);
        }
    }
    else if (setupPhase == 2) /* data transaction qtd */
    {
        dataLength = transfer->transferLength;
        if (dataLength != 0)
        {
            qtdPointer->alternateNextQtdPointer = EHCI_HOST_T_INVALID_VALUE;
            /* dt: need set; ioc: 0; C_Page: 0; PID Code: IN/OUT; Status: Active */
            qtdPointer->transferResults[0] = qtdPointer->transferResults[1] = 0;

            qtdPointer->transferResults[0] =
                ((0x00000001U << EHCI_HOST_QTD_DT_SHIFT) | (dataLength << EHCI_HOST_QTD_TOTAL_BYTES_SHIFT) |
                 (EHCI_HOST_PID_IN << EHCI_HOST_QTD_PID_CODE_SHIFT) | (EHCI_HOST_QTD_STATUS_ACTIVE_MASK));

            dataAddress = (uint32_t)(transfer->transferBuffer);
            qtdPointer->transferResults[1] = dataAddress; /* current offset is set too */
            /* set buffer pointer no matter data length */
            for (index = 0; index < 4; ++index)
            {
                qtdPointer->bufferPointers[index] = ((dataAddress + (index + 1) * 4 * 1024) & 0xFFFFF000);
            }
        }
    }
    else if (setupPhase == 3)
    {
        /* status transaction qtd */
        qtdPointer->alternateNextQtdPointer = EHCI_HOST_T_INVALID_VALUE;
        /* dt: dont care; ioc: 1; C_Page: 0; PID Code: IN/OUT; Status: Active */
        qtdPointer->transferResults[0] = qtdPointer->transferResults[1] = 0;

        qtdPointer->transferResults[0] =
            ((0x00000001U << EHCI_HOST_QTD_DT_SHIFT) | (EHCI_HOST_PID_OUT << EHCI_HOST_QTD_PID_CODE_SHIFT) |
             (EHCI_HOST_QTD_IOC_MASK) | (EHCI_HOST_QTD_STATUS_ACTIVE_MASK));

        qtdPointer->nextQtdPointer |= EHCI_HOST_T_INVALID_VALUE;
    }
    qtdPointer->nextQtdPointer |= EHCI_HOST_T_INVALID_VALUE;
    qtdPointer->transferResults[0] |= EHCI_HOST_QTD_IOC_MASK; /* set IOC */

    /* save qtd to transfer */
    transfer->union1.unitHead = (uint32_t)qtdPointer;
    transfer->union2.unitTail = (uint32_t)qtdPointer;
    /* link transfer to qh */
    transfer->next = NULL;
    if (vltQhPointer->ehciTransferHead == NULL)
    {
        transfer->next = NULL;
        vltQhPointer->ehciTransferHead = vltQhPointer->ehciTransferTail = transfer;
    }
    else
    {
        transfer->next = NULL;
        vltQhPointer->ehciTransferTail->next = transfer;
        vltQhPointer->ehciTransferTail = transfer;
    }

    USB_HostEhciLock();
    /* link qtd to qh (link to end) */
    entryPointer = &(vltQhPointer->nextQtdPointer);
    dataAddress = *entryPointer; /* dataAddress variable means entry value here */
    while ((dataAddress) && (!(dataAddress & EHCI_HOST_T_INVALID_VALUE)))
    {
        entryPointer = (volatile uint32_t *)dataAddress;
        dataAddress = *entryPointer;
    }
    *entryPointer = (uint32_t)qtdPointer;
    USB_HostEhciUnlock();
    USB_HostEhciStartAsync(ehciInstance);

    return kStatus_USB_Success;
}

static void USB_HostEhciTestSingleStepGetDeviceDescData(usb_host_ehci_instance_t *ehciInstance,
                                                        usb_device_handle deviceHandle)
{
    static uint8_t buffer[USB_HOST_EHCI_TEST_DESCRIPTOR_LENGTH];
    usb_host_device_instance_t *deviceInstance = (usb_host_device_instance_t *)deviceHandle;
    usb_host_transfer_t *transfer;
    uint8_t timeCount;

    USB_HostEhciStopPeriodic(ehciInstance);

    if (USB_HostMallocTransfer(ehciInstance->hostHandle, &transfer) != kStatus_USB_Success)
    {
        return;
    }
    transfer->callbackFn = USB_HostEhciTestCallback;
    transfer->callbackParam = ehciInstance->hostHandle;
    transfer->setupPacket->bmRequestType = USB_REQUEST_TYPE_DIR_IN;
    transfer->setupPacket->bRequest = USB_REQUEST_STANDARD_GET_DESCRIPTOR;
    transfer->setupPacket->wLength = USB_SHORT_TO_LITTLE_ENDIAN(USB_HOST_EHCI_TEST_DESCRIPTOR_LENGTH);
    transfer->setupPacket->wValue = USB_SHORT_TO_LITTLE_ENDIAN((uint16_t)((uint16_t)USB_DESCRIPTOR_TYPE_DEVICE << 8));
    transfer->setupPacket->wIndex = 0;
    USB_HostEhciSingleStepQtdListInit(ehciInstance, (usb_host_ehci_pipe_t *)(deviceInstance->controlPipe), transfer, 1);

    timeCount = 15; /* 15s */
    while (timeCount--)
    {
        USB_HostEhciDelay(ehciInstance->ehciIpBase, 1000U);
    }

    if (USB_HostMallocTransfer(ehciInstance->hostHandle, &transfer) != kStatus_USB_Success)
    {
        return;
    }
    transfer->callbackFn = USB_HostEhciTestCallback;
    transfer->callbackParam = ehciInstance->hostHandle;
    transfer->transferBuffer = buffer;
    transfer->transferLength = USB_HOST_EHCI_TEST_DESCRIPTOR_LENGTH;
    USB_HostEhciSingleStepQtdListInit(ehciInstance, (usb_host_ehci_pipe_t *)(deviceInstance->controlPipe), transfer, 2);

    if (USB_HostMallocTransfer(ehciInstance->hostHandle, &transfer) != kStatus_USB_Success)
    {
        return;
    }
    transfer->callbackFn = USB_HostEhciTestCallback;
    transfer->callbackParam = ehciInstance->hostHandle;
    transfer->transferBuffer = NULL;
    transfer->transferLength = 0;
    USB_HostEhciSingleStepQtdListInit(ehciInstance, (usb_host_ehci_pipe_t *)(deviceInstance->controlPipe), transfer, 3);

    timeCount = 15; /* 15s */
    while (timeCount--)
    {
        USB_HostEhciDelay(ehciInstance->ehciIpBase, 1000U);
    }

    usb_echo("test_single_step_get_dev_desc_data finished\r\n");

    return;
}

void USB_HostEhciTestModeInit(usb_device_handle deviceHandle)
{
    uint32_t productId;
    usb_host_device_instance_t *deviceInstance = (usb_host_device_instance_t *)deviceHandle;
    usb_host_ehci_instance_t *ehciInstance =
        (usb_host_ehci_instance_t *)(((usb_host_instance_t *)(deviceInstance->hostHandle))->controllerHandle);

    USB_HostHelperGetPeripheralInformation(deviceHandle, kUSB_HostGetDevicePID, &productId);

    usb_echo("usb host ehci test mode init  product id:0x%x\r\n", productId);

    switch (productId)
    {
        case 0x0101U:
            USB_HostEhciTestSetMode(ehciInstance, USB_HOST_EHCI_PORTSC_PTC_SE0_NAK);
            break;
        case 0x0102U:
            USB_HostEhciTestSetMode(ehciInstance, USB_HOST_EHCI_PORTSC_PTC_J_STATE);
            break;
        case 0x0103U:
            USB_HostEhciTestSetMode(ehciInstance, USB_HOST_EHCI_PORTSC_PTC_K_STATE);
            break;
        case 0x0104U:
            USB_HostEhciTestSetMode(ehciInstance, USB_HOST_EHCI_PORTSC_PTC_PACKET);
            break;
        case 0x0105U:
            usb_echo("set test mode FORCE_ENALBE_HS\r\n");
            USB_HostEhciTestSetMode(ehciInstance, USB_HOST_EHCI_PORTSC_PTC_FORCE_ENABLE_HS);
            break;
        case 0x0106U:
            USB_HostEhciTestSuspendResume(ehciInstance);
            break;
        case 0x0107U:
            usb_echo("start test SINGLE_STEP_GET_DEV_DESC\r\n");
            USB_HostEhciTestSingleStepGetDeviceDesc(ehciInstance, deviceHandle);
            break;
        case 0x0108U:
            usb_echo("start test SINGLE_STEP_GET_DEV_DESC_DATA\r\n");
            USB_HostEhciTestSingleStepGetDeviceDescData(ehciInstance, deviceHandle);
            break;
        default:
            break;
    }

    return;
}

static void USB_HostEhciSuspendBus(usb_host_ehci_instance_t *ehciInstance)
{
    uint32_t ehciPortSC;

    USB_HostEhciLock();
    ehciPortSC = ehciInstance->ehciIpBase->PORTSC1;
    if (ehciPortSC & USBHS_PORTSC1_PE_MASK)
    {
        ehciPortSC = ehciInstance->ehciIpBase->PORTSC1;
        ehciPortSC &= (uint32_t)(~EHCI_PORTSC1_W1_BITS);
        ehciInstance->ehciIpBase->PORTSC1 = (ehciPortSC | USBHS_PORTSC1_SUSP_MASK);
    }
    USB_HostEhciUnlock();
}

static void USB_HostEhciResumeBus(usb_host_ehci_instance_t *ehciInstance)
{
    uint32_t ehciPortSC;

    USB_HostEhciLock();
    /* Resume port */
    ehciPortSC = ehciInstance->ehciIpBase->PORTSC1;
    if (ehciPortSC & USBHS_PORTSC1_PE_MASK)
    {
        ehciPortSC &= (uint32_t)(~EHCI_PORTSC1_W1_BITS);
        ehciInstance->ehciIpBase->PORTSC1 = (ehciPortSC | USBHS_PORTSC1_FPR_MASK);
    }
    USB_HostEhciUnlock();
}
#endif

static uint32_t USB_HostBandwidthComputeTime(uint8_t speed, uint8_t pipeType, uint8_t direction, uint32_t dataLength)
{
    uint32_t result = (3167 + ((1000 * dataLength) * 7U * 8U / 6U)) / 1000;

    if (pipeType == USB_ENDPOINT_ISOCHRONOUS) /* iso */
    {
        if (speed == USB_SPEED_HIGH)
        {
            result = 38 * 8 * 2083 + 2083 * result + USB_HOST_EHCI_BANDWIDTH_DELAY;
        }
        else if (speed == USB_SPEED_FULL)
        {
            if (direction == USB_IN)
            {
                result = 7268000 + 83540 * result + USB_HOST_EHCI_BANDWIDTH_DELAY;
            }
            else
            {
                result = 6265000 + 83540 * result + USB_HOST_EHCI_BANDWIDTH_DELAY;
            }
        }
        else
        {
        }
    }
    else /* interrupt */
    {
        if (speed == USB_SPEED_HIGH)
        {
            result = 55 * 8 * 2083 + 2083 * result + USB_HOST_EHCI_BANDWIDTH_DELAY;
        }
        else if (speed == USB_SPEED_FULL)
        {
            result = 9107000 + 83540 * result + USB_HOST_EHCI_BANDWIDTH_DELAY;
        }
        else if (speed == USB_SPEED_LOW)
        {
            if (direction == USB_IN)
            {
                result = 64060000 + 2000 * USB_HOST_EHCI_BANDWIDTH_HUB_LS_SETUP + 676670 * result +
                         USB_HOST_EHCI_BANDWIDTH_DELAY;
            }
            else
            {
                result = 6265000 + 83540 * result + USB_HOST_EHCI_BANDWIDTH_DELAY;
            }
        }
        else
        {
        }
    }

    result /= 1000000;
    if (result == 0)
    {
        result = 1;
    }

    return result;
}

static void USB_HostBandwidthFslsHostComputeCurrent(usb_host_ehci_instance_t *ehciInstance,
                                                    uint16_t frameIndex,
                                                    uint16_t *frameBandwidth)
{
    usb_host_ehci_pipe_t *ehciPipePointer;

    /* clear the bandwidth */
    *frameBandwidth = 0;

    ehciPipePointer = ehciInstance->ehciRunningPipeList;
    while (ehciPipePointer != NULL)
    {
        /* only compute iso and interrupt pipe */
        if ((ehciPipePointer->pipeCommon.pipeType == USB_ENDPOINT_ISOCHRONOUS) ||
            (ehciPipePointer->pipeCommon.pipeType == USB_ENDPOINT_INTERRUPT))
        {
            /* does pipe allocate bandwidth in frameIndex frame? note: interval is power of 2. */
            if ((frameIndex >= ehciPipePointer->startFrame) &&
                (!((uint32_t)(frameIndex - ehciPipePointer->startFrame) &
                   (uint32_t)(ehciPipePointer->pipeCommon.interval - 1))))
            {
                *frameBandwidth += ehciPipePointer->dataTime;
            }
        }
        ehciPipePointer = (usb_host_ehci_pipe_t *)ehciPipePointer->pipeCommon.next;
    }
}

static void USB_HostBandwidthHsHostComputeCurrentFsls(usb_host_ehci_instance_t *ehciInstance,
                                                      uint32_t hubNumber,
                                                      uint16_t frameIndex,
                                                      uint8_t frameBandwidths[8])
{
    usb_host_ehci_pipe_t *ehciPipePointer;
    uint8_t index;
    uint32_t deviceInfo;

    for (index = 0; index < 8; ++index)
    {
        frameBandwidths[index] = 0;
    }

    ehciPipePointer = ehciInstance->ehciRunningPipeList;
    while (ehciPipePointer != NULL)
    {
        /* only compute iso and interrupt pipe */
        if ((ehciPipePointer->pipeCommon.pipeType == USB_ENDPOINT_ISOCHRONOUS) ||
            (ehciPipePointer->pipeCommon.pipeType == USB_ENDPOINT_INTERRUPT))
        {
            /* compute FS/LS bandwidth that blong to same high-speed hub, because FS/LS bandwidth is allocated from
             * first parent high-speed hub */
            USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                   kUSB_HostGetDeviceHSHubNumber, &deviceInfo);
            if (deviceInfo != hubNumber)
            {
                ehciPipePointer = (usb_host_ehci_pipe_t *)ehciPipePointer->pipeCommon.next;
                continue;
            }
            USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetDeviceSpeed,
                                                   &deviceInfo);
            if (deviceInfo == USB_SPEED_HIGH)
            {
                ehciPipePointer = (usb_host_ehci_pipe_t *)ehciPipePointer->pipeCommon.next;
                continue;
            }

            /* does pipe allocate bandwidth in frameIndex frame? note: interval is power of 2. */
            if ((frameIndex >= ehciPipePointer->startFrame) &&
                (!((uint32_t)(frameIndex - ehciPipePointer->startFrame) &
                   (uint32_t)(ehciPipePointer->pipeCommon.interval - 1))))
            {
                if (ehciPipePointer->pipeCommon.pipeType ==
                    USB_ENDPOINT_ISOCHRONOUS) /* iso bandwidth is allocated once */
                {
                    frameBandwidths[ehciPipePointer->startUframe + 1] += ehciPipePointer->dataTime;
                }
                else /* iso bandwidth is allocated three times */
                {
                    frameBandwidths[ehciPipePointer->startUframe + 1] += ehciPipePointer->dataTime;
                    frameBandwidths[ehciPipePointer->startUframe + 2] += ehciPipePointer->dataTime;
                    frameBandwidths[ehciPipePointer->startUframe + 3] += ehciPipePointer->dataTime;
                }
            }
        }
        ehciPipePointer = (usb_host_ehci_pipe_t *)ehciPipePointer->pipeCommon.next;
    }

    for (index = 0; index < 7; ++index) /*  */
    {
        if (frameBandwidths[index] > s_SlotMaxBandwidth[index])
        {
            frameBandwidths[index + 1] += (frameBandwidths[index] - s_SlotMaxBandwidth[index]);
            frameBandwidths[index] = s_SlotMaxBandwidth[index];
        }
    }
}

static void USB_HostBandwidthHsHostComputeCurrentHsAll(usb_host_ehci_instance_t *ehciInstance,
                                                       uint16_t frameIndex,
                                                       uint8_t frameBandwidths[8])
{
    usb_host_ehci_pipe_t *ehciPipePointer;
    uint8_t index;
    uint32_t deviceInfo;
    uint16_t frameInterval;

    for (index = 0; index < 8; ++index)
    {
        frameBandwidths[index] = 0;
    }

    ehciPipePointer = ehciInstance->ehciRunningPipeList;
    while (ehciPipePointer != NULL)
    {
        /* only compute iso and interrupt pipe */
        if ((ehciPipePointer->pipeCommon.pipeType == USB_ENDPOINT_ISOCHRONOUS) ||
            (ehciPipePointer->pipeCommon.pipeType == USB_ENDPOINT_INTERRUPT))
        {
            frameInterval = ehciPipePointer->pipeCommon.interval;
            USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetDeviceSpeed,
                                                   &deviceInfo);
            if (deviceInfo == USB_SPEED_HIGH) /* high-speed data bandwidth */
            {
                /* frameInterval means micro-frame here */
                if (frameIndex >= ehciPipePointer->startFrame)
                {
                    if ((frameInterval > 8) &&
                        (frameIndex * 8 - ehciPipePointer->startFrame * 8 >= ehciPipePointer->startUframe))
                    {
                        if (!((uint32_t)(frameIndex * 8 - ehciPipePointer->startFrame * 8 -
                                         ehciPipePointer->startUframe) &
                              (uint32_t)(frameInterval - 1)))
                        {
                            frameBandwidths[ehciPipePointer->startUframe] += ehciPipePointer->dataTime;
                        }
                    }
                    else
                    {
                        for (index = ehciPipePointer->startUframe; index < 8; index += frameInterval)
                        {
                            frameBandwidths[index] += ehciPipePointer->dataTime;
                        }
                    }
                }
            }
            else /* full-speed split bandwidth */
            {
                if ((frameIndex >= ehciPipePointer->startFrame) &&
                    (!((uint32_t)(frameIndex - ehciPipePointer->startFrame) & (uint32_t)(frameInterval - 1))))
                {
                    for (index = 0; index < 8; ++index)
                    {
                        if ((uint32_t)(ehciPipePointer->uframeSmask) &
                            (uint32_t)(0x01 << index)) /* start-split micro-frames */
                        {
                            frameBandwidths[index] += ehciPipePointer->startSplitTime;
                        }
                        if ((uint32_t)(ehciPipePointer->uframeCmask) &
                            (uint32_t)(0x01 << index)) /* complete-split micro-frames */
                        {
                            frameBandwidths[index] += ehciPipePointer->completeSplitTime;
                        }
                    }
                }
            }
        }
        ehciPipePointer = (usb_host_ehci_pipe_t *)ehciPipePointer->pipeCommon.next;
    }

    for (index = 0; index < 7; ++index) /*  */
    {
        if (frameBandwidths[index] > s_SlotMaxBandwidth[index])
        {
            frameBandwidths[index + 1] += (frameBandwidths[index] - s_SlotMaxBandwidth[index]);
            frameBandwidths[index] = s_SlotMaxBandwidth[index];
        }
    }
}

/*!
 * @brief allocate HS bandwidth when host work as high-speed host.
 *
 * @param ehciInstance         ehci instance pointer.
 * @param uframeInterval  micro-frame interval.
 * @param timeData        time for allocating.
 * @param uframeIndexOut return start uframe index.
 *
 * @return kStatus_USB_Success or error codes.
 */
static usb_status_t USB_HostBandwidthHsHostAllocateHsCommon(usb_host_ehci_instance_t *ehciInstance,
                                                            uint16_t uframeInterval,
                                                            uint16_t timeData,
                                                            uint16_t *uframeIndexOut)
{
    uint16_t uframeIntervalIndex;
    uint16_t uframeIndex;
    uint16_t frameIndex;
    uint8_t frameTimes[8];

    frameIndex = 0;
    USB_HostBandwidthHsHostComputeCurrentHsAll(
        ehciInstance, frameIndex, frameTimes); /* compute the allocated bandwidths in the frameIndex frame */
    for (uframeIntervalIndex = 0; (uframeIntervalIndex < uframeInterval); ++uframeIntervalIndex) /* start micro-frame */
    {
        /* for all the micro-frame in interval uframeInterval */
        for (uframeIndex = uframeIntervalIndex; uframeIndex < (USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE * 8);
             uframeIndex += uframeInterval)
        {
            if (frameIndex != (uframeIndex >> 3))
            {
                frameIndex = (uframeIndex >> 3);
                USB_HostBandwidthHsHostComputeCurrentHsAll(
                    ehciInstance, frameIndex,
                    frameTimes); /* compute the allocated bandwidths in the new frameIndex frame */
            }
            if (frameTimes[uframeIndex & 0x0007] + timeData >
                s_SlotMaxBandwidth[(uframeIndex & 0x0007)]) /* micro-frame has enough idle bandwidth? */
            {
                break; /* fail */
            }
        }
        if (uframeIndex >= (USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE * 8)) /* success? */
        {
            break;
        }
    }

    if (uframeIntervalIndex < uframeInterval)
    {
        *uframeIndexOut = (uframeIntervalIndex);
        return kStatus_USB_Success;
    }
    else
    {
        return kStatus_USB_Error;
    }
}

#if (((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD)) || \
     ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD)))

static usb_status_t USB_HostBandwidthHsHostAllocateIso(usb_host_ehci_instance_t *ehciInstance,
                                                       usb_host_ehci_pipe_t *ehciPipePointer)
{
    usb_status_t status;
    uint32_t deviceInfo;
    uint32_t hubNumber;
    uint16_t uframeIntervalIndex = 0;
    uint16_t frameIntervalIndex = 0;
    uint16_t frameIndex;
    uint16_t timeCompleteSplit;
    uint16_t timeStartSplit;
    uint32_t timeData;
    uint8_t SsCsNumber = 0;
    uint16_t frameInterval;
    uint8_t frameTimes[8];
    uint8_t allocateOk = 1;
    uint8_t index;

    USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetDeviceSpeed,
                                           &deviceInfo);

    timeData = USB_HostBandwidthComputeTime(
        deviceInfo, USB_ENDPOINT_ISOCHRONOUS, ehciPipePointer->pipeCommon.direction,
        ehciPipePointer->pipeCommon.maxPacketSize * ehciPipePointer->pipeCommon.numberPerUframe);
    /* pipe is high-speed */
    if (deviceInfo == USB_SPEED_HIGH)
    {
        uframeIntervalIndex = 0;
        status = USB_HostBandwidthHsHostAllocateHsCommon(ehciInstance, ehciPipePointer->uframeInterval, timeData,
                                                         &uframeIntervalIndex);
        if (status == kStatus_USB_Success)
        {
            ehciPipePointer->startFrame = (uframeIntervalIndex / 8);
            ehciPipePointer->startUframe = (uframeIntervalIndex & 0x0007);
            ehciPipePointer->dataTime = timeData;

            return kStatus_USB_Success;
        }
    }
    else /* pipe is full-speed or low-speed */
    {
        USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetHubThinkTime,
                                               &deviceInfo); /* deviceInfo variable means hub think time */
        timeData += (deviceInfo * 7 / (6 * 12));
        USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetDeviceHSHubNumber,
                                               &hubNumber);
        frameInterval = ehciPipePointer->pipeCommon.interval;

        /* compute start-split and complete-split bandwidth */
        if (ehciPipePointer->pipeCommon.direction == USB_OUT)
        {
            timeStartSplit = USB_HostBandwidthComputeTime(USB_SPEED_HIGH, USB_ENDPOINT_ISOCHRONOUS, USB_OUT,
                                                          ehciPipePointer->pipeCommon.maxPacketSize);
            timeCompleteSplit = 0;
        }
        else
        {
            timeStartSplit = USB_HostBandwidthComputeTime(USB_SPEED_HIGH, USB_ENDPOINT_ISOCHRONOUS, USB_IN, 1);
            timeCompleteSplit = USB_HostBandwidthComputeTime(USB_SPEED_HIGH, USB_ENDPOINT_ISOCHRONOUS, USB_IN,
                                                             ehciPipePointer->pipeCommon.maxPacketSize);
        }
        /* note: bandwidth must put in one frame */
        for (uframeIntervalIndex = 0; uframeIntervalIndex <= 5; ++uframeIntervalIndex) /* uframe interval */
        {
            for (frameIntervalIndex = 0; frameIntervalIndex < frameInterval; ++frameIntervalIndex) /* frame interval */
            {
                allocateOk = 1;
                for (frameIndex = frameIntervalIndex; frameIndex < USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE;
                     frameIndex += frameInterval) /* check all the frames */
                {
                    /* compute start-split and complete-split number */
                    SsCsNumber = (ehciPipePointer->pipeCommon.maxPacketSize + 187) /
                                 188; /* ss number for iso out; cs number for iso in */
                    if (ehciPipePointer->pipeCommon.direction == USB_OUT) /* ISO OUT */
                    {
                        if (uframeIntervalIndex + SsCsNumber > 8)
                        {
                            allocateOk = 0;
                        }
                    }
                    else
                    {
                        if (uframeIntervalIndex + 2 + SsCsNumber >
                            8) /* ISO IN: there are two micro-frame interval between start-split and complete-split */
                        {
                            allocateOk = 0;
                        }
                    }
                    if (allocateOk)
                    {
                        /* allocate start-split and complete-split bandwidth */
                        USB_HostBandwidthHsHostComputeCurrentHsAll(ehciInstance, frameIndex, frameTimes);
                        if (ehciPipePointer->pipeCommon.direction == USB_OUT) /* ISO OUT */
                        {
                            index = uframeIntervalIndex;
                            for (; index < (uframeIntervalIndex + SsCsNumber); ++index)
                            {
                                if (frameTimes[index] + timeStartSplit > s_SlotMaxBandwidth[index])
                                {
                                    allocateOk = 0;
                                    break;
                                }
                            }
                        }
                        else /* ISO IN */
                        {
                            index = uframeIntervalIndex;
                            if (frameTimes[index] + timeStartSplit > s_SlotMaxBandwidth[index])
                            {
                                allocateOk = 0;
                            }
                            if (allocateOk)
                            {
                                index =
                                    uframeIntervalIndex +
                                    2; /* there are two micro-frames interval between start-split and complete-split */
                                for (; index < (uframeIntervalIndex + 2 + SsCsNumber); ++index)
                                {
                                    if (frameTimes[index] + timeCompleteSplit > s_SlotMaxBandwidth[index])
                                    {
                                        allocateOk = 0;
                                        break;
                                    }
                                }
                            }
                        }
                    }

                    /* allocate data bandwidth */
                    if (allocateOk)
                    {
                        USB_HostBandwidthHsHostComputeCurrentFsls(ehciInstance, hubNumber, frameIndex, frameTimes);
                        index = uframeIntervalIndex + 1; /* timeData bandwidth start position */
                        /* iso must occupy all the uframe bandwidth */
                        {
                            deviceInfo = timeData; /* note: deviceInfo variable means bandwidth here */
                            while ((index < 8) && (deviceInfo > s_SlotMaxBandwidth[index]))
                            {
                                if (frameTimes[index] > 0)
                                {
                                    allocateOk = 0;
                                    break;
                                }
                                else
                                {
                                    deviceInfo -= s_SlotMaxBandwidth[index];
                                }
                                ++index;
                            }
                        }
                    }
                    if (allocateOk)
                    {
                        /* data bandwidth can be put in the frame? */
                        index = uframeIntervalIndex + 1; /* timeData bandwidth start position */
                        frameTimes[index] += timeData;
                        for (; index < 7; ++index)
                        {
                            if (frameTimes[index] > s_SlotMaxBandwidth[index])
                            {
                                frameTimes[index + 1] += (frameTimes[index] - s_SlotMaxBandwidth[index]);
                                frameTimes[index] = s_SlotMaxBandwidth[index];
                            }
                            else
                            {
                                break;
                            }
                        }
                        if (frameTimes[index] > s_SlotMaxBandwidth[index])
                        {
                            allocateOk = 0;
                        }
                    }

                    if (allocateOk)
                    {
                        break;
                    }
                }
                if (allocateOk)
                {
                    break;
                }
            }
            if (allocateOk)
            {
                break;
            }
        }

        if (allocateOk)
        {
            ehciPipePointer->startFrame = frameIntervalIndex;
            ehciPipePointer->startUframe = uframeIntervalIndex;
            ehciPipePointer->dataTime = timeData;
            ehciPipePointer->startSplitTime = timeStartSplit;
            ehciPipePointer->completeSplitTime = timeCompleteSplit;
            if (ehciPipePointer->pipeCommon.direction == USB_OUT)
            {
                index = uframeIntervalIndex;
                for (; index < (uframeIntervalIndex + SsCsNumber); ++index)
                {
                    ehciPipePointer->uframeSmask = (uint32_t)ehciPipePointer->uframeSmask | (uint32_t)(0x01 << index);
                }
            }
            else
            {
                index = uframeIntervalIndex;
                ehciPipePointer->uframeSmask = (uint32_t)ehciPipePointer->uframeSmask | (uint32_t)(0x01 << index);
                index = uframeIntervalIndex + 2;
                for (; index < (uframeIntervalIndex + 2 + SsCsNumber); ++index)
                {
                    ehciPipePointer->uframeCmask = (uint32_t)ehciPipePointer->uframeCmask | (uint32_t)(0x01 << index);
                }
            }

            return kStatus_USB_Success;
        }
    }

    return kStatus_USB_Error;
}

#endif

static usb_status_t USB_HostBandwidthHsHostAllocateInterrupt(usb_host_ehci_instance_t *ehciInstance,
                                                             usb_host_ehci_pipe_t *ehciPipePointer)
{
    usb_status_t status;
    uint32_t deviceInfo;
    uint32_t hubNumber;
    uint16_t uframeIntervalIndex = 0;
    uint16_t frameIntervalIndex = 0;
    uint16_t frameIndex;
    uint16_t timeCompleteSplit;
    uint16_t timeStartSplit;
    uint32_t timeData;
    uint8_t SsCsNumber;
    uint16_t frameInterval;
    uint8_t frameTimes[8];
    uint8_t allocateOk = 1;
    uint8_t index;

    USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetDeviceSpeed,
                                           &deviceInfo);

    timeData = USB_HostBandwidthComputeTime(
        deviceInfo, USB_ENDPOINT_INTERRUPT, ehciPipePointer->pipeCommon.direction,
        ehciPipePointer->pipeCommon.maxPacketSize * ehciPipePointer->pipeCommon.numberPerUframe);
    /* pipe is high-speed */
    if (deviceInfo == USB_SPEED_HIGH)
    {
        uframeIntervalIndex = 0;
        status = USB_HostBandwidthHsHostAllocateHsCommon(ehciInstance, ehciPipePointer->uframeInterval, timeData,
                                                         &uframeIntervalIndex);
        if (status == kStatus_USB_Success)
        {
            ehciPipePointer->startFrame = (uframeIntervalIndex / 8);
            ehciPipePointer->startUframe = (uframeIntervalIndex & 0x0007);
            /* for HS interrupt start transaction position */
            if (ehciPipePointer->uframeInterval >= 8)
            {
                ehciPipePointer->uframeSmask = (0x01 << ehciPipePointer->startUframe);
            }
            else
            {
                ehciPipePointer->uframeSmask = 0x00u;
                for (index = ehciPipePointer->startUframe; index < 8; index += ehciPipePointer->uframeInterval)
                {
                    ehciPipePointer->uframeSmask |= (0x01U << index);
                }
            }
            ehciPipePointer->dataTime = timeData;

            return kStatus_USB_Success;
        }
    }
    else /* pipe is full-speed or low-speed */
    {
        USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetHubThinkTime,
                                               &deviceInfo);
        timeData += (deviceInfo * 7 / (6 * 12));
        USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetDeviceHSHubNumber,
                                               &hubNumber);
        frameInterval = ehciPipePointer->pipeCommon.interval;
        SsCsNumber = 3; /* complete split number */

        /* compute start-split and complete-split bandwidth */
        if (ehciPipePointer->pipeCommon.direction == USB_OUT)
        {
            timeStartSplit = USB_HostBandwidthComputeTime(USB_SPEED_HIGH, USB_ENDPOINT_INTERRUPT, USB_OUT,
                                                          ehciPipePointer->pipeCommon.maxPacketSize) +
                             USB_HostBandwidthComputeTime(USB_SPEED_HIGH, USB_ENDPOINT_INTERRUPT, USB_OUT, 1);
            timeCompleteSplit = USB_HostBandwidthComputeTime(USB_SPEED_HIGH, USB_ENDPOINT_INTERRUPT, USB_OUT, 0);
        }
        else
        {
            timeStartSplit = USB_HostBandwidthComputeTime(USB_SPEED_HIGH, USB_ENDPOINT_INTERRUPT, USB_IN, 1);
            timeCompleteSplit = USB_HostBandwidthComputeTime(USB_SPEED_HIGH, USB_ENDPOINT_INTERRUPT, USB_IN,
                                                             ehciPipePointer->pipeCommon.maxPacketSize) +
                                USB_HostBandwidthComputeTime(USB_SPEED_HIGH, USB_ENDPOINT_INTERRUPT, USB_IN, 0);
        }
        /* note: bandwidth must put in one frame */
        for (uframeIntervalIndex = 0; uframeIntervalIndex <= 4; ++uframeIntervalIndex) /* uframe interval */
        {
            for (frameIntervalIndex = 0; frameIntervalIndex < frameInterval; ++frameIntervalIndex) /* frame interval */
            {
                allocateOk = 1;
                for (frameIndex = frameIntervalIndex; frameIndex < USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE;
                     frameIndex += frameInterval) /* check all the frames */
                {
                    /* allocate data bandwidth */
                    USB_HostBandwidthHsHostComputeCurrentFsls(ehciInstance, hubNumber, frameIndex, frameTimes);
                    index = uframeIntervalIndex + 1;
                    for (; index <= (uframeIntervalIndex + 3); ++index) /* data bandwidth number is 3.
                                                                             uframeIntervalIndex don't exceed 4, so
                                                                             index cannot exceed 7 */
                    {
                        if (frameTimes[index] + timeData > s_SlotMaxBandwidth[index])
                        {
                            allocateOk = 0;
                            break;
                        }
                    }

                    if (allocateOk)
                    {
                        USB_HostBandwidthHsHostComputeCurrentHsAll(ehciInstance, frameIndex, frameTimes);
                        /* allocate start_split bandwidth */
                        if (frameTimes[uframeIntervalIndex] + timeStartSplit > s_SlotMaxBandwidth[uframeIntervalIndex])
                        {
                            allocateOk = 0;
                        }
                        if (allocateOk)
                        {
                            /* allocate complete_split bandwidth */
                            index = uframeIntervalIndex + 2;
                            /* complete-split number is normal 3. When uframeIntervalIndex is 4, complete-split number
                             * is 2. */
                            for (; (index <= (uframeIntervalIndex + 1 + SsCsNumber)) && (index < 8); ++index)
                            {
                                if (frameTimes[index] + timeCompleteSplit > s_SlotMaxBandwidth[index])
                                {
                                    allocateOk = 0;
                                    break;
                                }
                            }
                        }
                    }

                    if (!allocateOk)
                    {
                        break; /* allocate fail */
                    }
                }
                if (allocateOk)
                {
                    break;
                }
            }
            if (allocateOk)
            {
                break;
            }
        }

        if (allocateOk)
        {
            ehciPipePointer->startFrame = frameIntervalIndex;
            ehciPipePointer->startUframe = uframeIntervalIndex;
            ehciPipePointer->uframeSmask = (0x01 << ehciPipePointer->startUframe);
            ehciPipePointer->uframeCmask = 0;
            index = uframeIntervalIndex + 2;
            for (; (index <= (uframeIntervalIndex + 1 + SsCsNumber)) && (index < 8); ++index)
            {
                ehciPipePointer->uframeCmask = (uint32_t)ehciPipePointer->uframeCmask | (uint32_t)(0x01 << index);
            }
            ehciPipePointer->dataTime = timeData;
            ehciPipePointer->startSplitTime = timeStartSplit;
            ehciPipePointer->completeSplitTime = timeCompleteSplit;

            return kStatus_USB_Success;
        }
    }

    return kStatus_USB_BandwidthFail;
}

static usb_status_t USB_HostBandwidthFslsHostAllocate(usb_host_ehci_instance_t *ehciInstance,
                                                      usb_host_ehci_pipe_t *ehciPipePointer)
{
    uint32_t FslsTime = 0;
    uint32_t speed = 0;
    uint16_t uframeIntervalIndex;
    uint16_t frameIndex;
    uint16_t frameInterval;
    uint16_t frameTime;

    USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetHubThinkTime,
                                           &FslsTime);
    FslsTime += (FslsTime * 7 / (6 * 12));
    USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetDeviceSpeed, &speed);
    FslsTime = FslsTime + USB_HostBandwidthComputeTime(speed, ehciPipePointer->pipeCommon.pipeType,
                                                       ehciPipePointer->pipeCommon.direction,
                                                       ehciPipePointer->pipeCommon.maxPacketSize);

    frameInterval = ehciPipePointer->pipeCommon.interval;
    for (uframeIntervalIndex = 0; uframeIntervalIndex < ehciPipePointer->uframeInterval;
         ++uframeIntervalIndex) /* uframeIntervalIndex can exceed 8 */
    {
        for (frameIndex = (uframeIntervalIndex >> 3); frameIndex < USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE;
             frameIndex += frameInterval)
        {
            USB_HostBandwidthFslsHostComputeCurrent(ehciInstance, frameIndex, &frameTime);
            if (frameTime + FslsTime > USB_HOST_EHCI_BANDWIDTH_FRAME_TOTOAL_TIME)
            {
                break;
            }
        }
        if (frameIndex >= USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE)
        {
            break;
        }
    }
    if (uframeIntervalIndex < ehciPipePointer->uframeInterval)
    {
        ehciPipePointer->startFrame = (uframeIntervalIndex >> 3);
        ehciPipePointer->startUframe = (uframeIntervalIndex & 0x0007);
        ehciPipePointer->uframeSmask = 0; /* useless */
        ehciPipePointer->uframeCmask = 0;
        ehciPipePointer->dataTime = FslsTime;

        return kStatus_USB_Success;
    }

    return kStatus_USB_BandwidthFail;
}

static uint8_t USB_HostEhciGet2PowerValue(uint8_t value)
{
    if ((value == 0) || (value == 1))
    {
        return value;
    }
    if (value & 0xf0)
    {
        if (value & 0x80)
        {
            return 128;
        }
        else if (value & 0x40)
        {
            return 64;
        }
        else if (value & 0x20)
        {
            return 32;
        }
        else
        {
            return 16;
        }
    }
    else
    {
        if (value & 0x08)
        {
            return 8;
        }
        else if (value & 0x04)
        {
            return 4;
        }
        else if (value & 0x02)
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }
}

static void USB_HostEhciZeroMem(uint32_t *buffer, uint32_t length)
{
    /* note: the zero unit is uint32_t */
    while (length--)
    {
        *buffer = 0;
        buffer++;
    }
}

static void USB_HostEhciDelay(USBHS_Type *ehciIpBase, uint32_t ms)
{
    /* note: the max delay time cannot exceed half of max value (0x4000) */
    int32_t sofStart;
    int32_t SofEnd;
    uint32_t distance;

    sofStart = (int32_t)(ehciIpBase->FRINDEX & EHCI_MAX_UFRAME_VALUE);

    do
    {
        SofEnd = (int32_t)(ehciIpBase->FRINDEX & EHCI_MAX_UFRAME_VALUE);
        distance = (uint32_t)(SofEnd - sofStart + EHCI_MAX_UFRAME_VALUE + 1);
    } while ((distance & EHCI_MAX_UFRAME_VALUE) < (ms * 8)); /* compute the distance between sofStart and SofEnd */
}

static void USB_HostEhciStartAsync(usb_host_ehci_instance_t *ehciInstance)
{
    uint32_t stateSync;

    if (!(ehciInstance->ehciIpBase->USBSTS & USBHS_USBSTS_AS_MASK))
    {
        /* the status must be same when change USBCMD->ASE */
        do
        {
            stateSync = ((ehciInstance->ehciIpBase->USBSTS & USBHS_USBSTS_AS_MASK) |
                         (ehciInstance->ehciIpBase->USBCMD & USBHS_USBCMD_ASE_MASK));
        } while ((stateSync == USBHS_USBSTS_AS_MASK) || (stateSync == USBHS_USBCMD_ASE_MASK));

        ehciInstance->ehciIpBase->ASYNCLISTADDR = (uint32_t)(ehciInstance->shedFirstQh);
        ehciInstance->ehciIpBase->USBCMD |= USBHS_USBCMD_ASE_MASK;
        while (!(ehciInstance->ehciIpBase->USBSTS & USBHS_USBSTS_AS_MASK))
        {
        }
    }
}

static void USB_HostEhciStopAsync(usb_host_ehci_instance_t *ehciInstance)
{
    uint32_t stateSync;

    /* the status must be same when change USBCMD->ASE */
    do
    {
        stateSync = ((ehciInstance->ehciIpBase->USBSTS & USBHS_USBSTS_AS_MASK) |
                     (ehciInstance->ehciIpBase->USBCMD & USBHS_USBCMD_ASE_MASK));
    } while ((stateSync == USBHS_USBSTS_AS_MASK) || (stateSync == USBHS_USBCMD_ASE_MASK));

    ehciInstance->ehciIpBase->USBCMD &= (uint32_t)(~(uint32_t)USBHS_USBCMD_ASE_MASK); /* disable async schedule */
    while (ehciInstance->ehciIpBase->USBSTS & USBHS_USBSTS_AS_MASK)
    {
    }
}

static void USB_HostEhciStartPeriodic(usb_host_ehci_instance_t *ehciInstance)
{
    uint32_t stateSync;

    if (!(ehciInstance->ehciIpBase->USBSTS & USBHS_USBSTS_PS_MASK))
    {
        /* the status must be same when change USBCMD->PSE */
        do
        {
            stateSync = ((ehciInstance->ehciIpBase->USBSTS & USBHS_USBSTS_PS_MASK) |
                         (ehciInstance->ehciIpBase->USBCMD & USBHS_USBCMD_PSE_MASK));
        } while ((stateSync == USBHS_USBSTS_PS_MASK) || (stateSync == USBHS_USBCMD_PSE_MASK));
        ehciInstance->ehciIpBase->PERIODICLISTBASE = (uint32_t)(ehciInstance->ehciFrameList);
        if (!(ehciInstance->ehciIpBase->USBCMD & USBHS_USBCMD_PSE_MASK))
        {
            ehciInstance->ehciIpBase->USBCMD |= USBHS_USBCMD_PSE_MASK; /* start periodic schedule */
        }
        while (!(ehciInstance->ehciIpBase->USBSTS & USBHS_USBSTS_PS_MASK))
        {
        }
    }
    return;
}

static void USB_HostEhciStopPeriodic(usb_host_ehci_instance_t *ehciInstance)
{
    uint32_t stateSync;

    /* the status must be same when change USBCMD->PSE */
    do
    {
        stateSync = ((ehciInstance->ehciIpBase->USBSTS & USBHS_USBSTS_PS_MASK) |
                     (ehciInstance->ehciIpBase->USBCMD & USBHS_USBCMD_PSE_MASK));
    } while ((stateSync == USBHS_USBSTS_PS_MASK) || (stateSync == USBHS_USBCMD_PSE_MASK));

    ehciInstance->ehciIpBase->USBCMD &= (~USBHS_USBCMD_PSE_MASK); /* stop periodic schedule */
    while (ehciInstance->ehciIpBase->USBSTS & USBHS_USBSTS_PS_MASK)
    {
    }
}

static usb_status_t USB_HostEhciQhQtdListInit(usb_host_ehci_instance_t *ehciInstance,
                                              usb_host_ehci_pipe_t *ehciPipePointer,
                                              usb_host_transfer_t *transfer)
{
    volatile usb_host_ehci_qh_t *vltQhPointer;
    usb_host_ehci_qtd_t *qtdPointer = NULL;
    usb_host_ehci_qtd_t *BaseQtdPointer = NULL;
    volatile uint32_t *entryPointer;
    uint32_t qtdNumber;
    uint32_t dataLength;
    uint32_t dataAddress;
    uint32_t endAddress;
    uint8_t index;

    /* compute the qtd number */
    if (ehciPipePointer->pipeCommon.pipeType == USB_ENDPOINT_CONTROL)
    {
        /* assume setup data don't exceed one qtd data size, one qtd can transfer least 16k data */
        if (transfer->transferLength == 0)
        {
            qtdNumber = 2;
        }
        else
        {
            qtdNumber = 3;
        }
    }
    else
    {
        qtdNumber =
            (((transfer->transferLength) & 0xFFFFC000U) >> 14) + (((transfer->transferLength) & 0x00003FFF) ? 1 : 0);
    }

    vltQhPointer = (volatile usb_host_ehci_qh_t *)ehciPipePointer->ehciQh;
    /* get qtd list */
    USB_HostEhciLock();
    if (qtdNumber <= ehciInstance->ehciQtdNumber)
    {
        ehciInstance->ehciQtdNumber -= qtdNumber;
        BaseQtdPointer = ehciInstance->ehciQtdHead;
        qtdPointer = NULL;
        do
        {
            if (qtdPointer != NULL)
            {
                qtdPointer->nextQtdPointer = (uint32_t)ehciInstance->ehciQtdHead;
            }
            qtdPointer = ehciInstance->ehciQtdHead;
            ehciInstance->ehciQtdHead = (usb_host_ehci_qtd_t *)qtdPointer->nextQtdPointer;
            qtdPointer->nextQtdPointer = 0;
        } while (--qtdNumber);
        if (ehciInstance->ehciQtdNumber == 0)
        {
            ehciInstance->ehciQtdTail = NULL;
        }
    }
    else
    {
        USB_HostEhciUnlock();
        return kStatus_USB_Error;
    }
    USB_HostEhciUnlock();

    /* int qTD list */
    if (ehciPipePointer->pipeCommon.pipeType == USB_ENDPOINT_CONTROL)
    {
        /* setup transaction qtd */
        qtdPointer = BaseQtdPointer;
        qtdPointer->alternateNextQtdPointer = EHCI_HOST_T_INVALID_VALUE;
        /* dt: need set; ioc: 0; C_Page: 0; PID Code: SETUP; Status: Active */
        qtdPointer->transferResults[0] = qtdPointer->transferResults[1] = 0;
        qtdPointer->transferResults[0] =
            ((0x00000000 << EHCI_HOST_QTD_DT_SHIFT) | (8 << EHCI_HOST_QTD_TOTAL_BYTES_SHIFT) |
             (EHCI_HOST_PID_SETUP << EHCI_HOST_QTD_PID_CODE_SHIFT) | (EHCI_HOST_QTD_STATUS_ACTIVE_MASK));
        dataAddress = ((uint32_t)transfer->setupPacket);
        qtdPointer->transferResults[1] = dataAddress; /* current offset is set too */
        /* set buffer pointer no matter data length */
        for (index = 0; index < 4; ++index)
        {
            qtdPointer->bufferPointers[index] = ((dataAddress + (index + 1) * 4 * 1024) & 0xFFFFF000U);
        }

        /* data transaction qtd */
        dataLength = transfer->transferLength;
        if (dataLength != 0)
        {
            qtdPointer = (usb_host_ehci_qtd_t *)(qtdPointer->nextQtdPointer);

            qtdPointer->alternateNextQtdPointer = EHCI_HOST_T_INVALID_VALUE;
            /* dt: need set; ioc: 0; C_Page: 0; PID Code: IN/OUT; Status: Active */
            qtdPointer->transferResults[0] = qtdPointer->transferResults[1] = 0;
            if (transfer->direction == USB_OUT)
            {
                qtdPointer->transferResults[0] =
                    ((0x00000001U << EHCI_HOST_QTD_DT_SHIFT) | (dataLength << EHCI_HOST_QTD_TOTAL_BYTES_SHIFT) |
                     (EHCI_HOST_PID_OUT << EHCI_HOST_QTD_PID_CODE_SHIFT) | (EHCI_HOST_QTD_STATUS_ACTIVE_MASK));
            }
            else
            {
                qtdPointer->transferResults[0] =
                    ((0x00000001U << EHCI_HOST_QTD_DT_SHIFT) | (dataLength << EHCI_HOST_QTD_TOTAL_BYTES_SHIFT) |
                     (EHCI_HOST_PID_IN << EHCI_HOST_QTD_PID_CODE_SHIFT) | (EHCI_HOST_QTD_STATUS_ACTIVE_MASK));
            }

            dataAddress = (uint32_t)transfer->transferBuffer;
            qtdPointer->transferResults[1] = dataAddress; /* current offset is set too */
            /* set buffer pointer no matter data length */
            for (index = 0; index < 4; ++index)
            {
                qtdPointer->bufferPointers[index] = ((dataAddress + (index + 1) * 4 * 1024) & 0xFFFFF000U);
            }
        }

        /* status transaction qtd */
        qtdPointer = (usb_host_ehci_qtd_t *)(qtdPointer->nextQtdPointer);
        qtdPointer->alternateNextQtdPointer = EHCI_HOST_T_INVALID_VALUE;
        /* dt: dont care; ioc: 1; C_Page: 0; PID Code: IN/OUT; Status: Active */
        qtdPointer->transferResults[0] = qtdPointer->transferResults[1] = 0;
        if ((dataLength == 0) || (transfer->direction == USB_OUT))
        {
            qtdPointer->transferResults[0] =
                ((0x00000001U << EHCI_HOST_QTD_DT_SHIFT) | (EHCI_HOST_PID_IN << EHCI_HOST_QTD_PID_CODE_SHIFT) |
                 (EHCI_HOST_QTD_IOC_MASK) | (EHCI_HOST_QTD_STATUS_ACTIVE_MASK));
        }
        else
        {
            qtdPointer->transferResults[0] =
                ((0x00000001U << EHCI_HOST_QTD_DT_SHIFT) | (EHCI_HOST_PID_OUT << EHCI_HOST_QTD_PID_CODE_SHIFT) |
                 (EHCI_HOST_QTD_IOC_MASK) | (EHCI_HOST_QTD_STATUS_ACTIVE_MASK));
        }
        qtdPointer->nextQtdPointer |= EHCI_HOST_T_INVALID_VALUE;
    }
    else
    {
        dataLength = transfer->transferLength;
        dataAddress = (uint32_t)transfer->transferBuffer;
        qtdPointer = BaseQtdPointer;
        while (1)
        {
            endAddress = dataAddress + (16 * 1024);
            if (endAddress > (uint32_t)(transfer->transferBuffer + transfer->transferLength))
            {
                endAddress = (uint32_t)(transfer->transferBuffer + transfer->transferLength);
            }

            qtdPointer->alternateNextQtdPointer = EHCI_HOST_T_INVALID_VALUE;
            /* dt: set; ioc: 0; C_Page: 0; PID Code: IN/OUT; Status: Active */
            qtdPointer->transferResults[0] = qtdPointer->transferResults[1] = 0;
            if (transfer->direction == USB_OUT)
            {
                qtdPointer->transferResults[0] =
                    (((endAddress - dataAddress) << EHCI_HOST_QTD_TOTAL_BYTES_SHIFT) |
                     ((uint32_t)ehciPipePointer->pipeCommon.nextdata01 << EHCI_HOST_QTD_DT_SHIFT) |
                     (EHCI_HOST_QTD_CERR_MAX_VALUE << EHCI_HOST_QTD_CERR_SHIFT) |
                     (EHCI_HOST_PID_OUT << EHCI_HOST_QTD_PID_CODE_SHIFT) | (EHCI_HOST_QTD_STATUS_ACTIVE_MASK));
            }
            else
            {
                qtdPointer->transferResults[0] =
                    (((endAddress - dataAddress) << EHCI_HOST_QTD_TOTAL_BYTES_SHIFT) |
                     ((uint32_t)ehciPipePointer->pipeCommon.nextdata01 << EHCI_HOST_QTD_DT_SHIFT) |
                     (EHCI_HOST_QTD_CERR_MAX_VALUE << EHCI_HOST_QTD_CERR_SHIFT) |
                     (EHCI_HOST_PID_IN << EHCI_HOST_QTD_PID_CODE_SHIFT) | (EHCI_HOST_QTD_STATUS_ACTIVE_MASK));
            }
            qtdPointer->transferResults[1] = dataAddress; /* current offset is set too */
            /* set buffer pointer no matter data length */
            for (index = 0; index < 4; ++index)
            {
                qtdPointer->bufferPointers[index] = ((dataAddress + (index + 1) * 4 * 1024) & 0xFFFFF000U);
            }
            dataAddress = endAddress; /* for next qtd */

            if (qtdPointer->nextQtdPointer == 0)
            {
                break;
            }
            qtdPointer = (usb_host_ehci_qtd_t *)(qtdPointer->nextQtdPointer);
        }

        qtdPointer->nextQtdPointer |= EHCI_HOST_T_INVALID_VALUE;
        qtdPointer->transferResults[0] |= EHCI_HOST_QTD_IOC_MASK; /* last one set IOC */
    }

    /* save qtd to transfer */
    transfer->union1.unitHead = (uint32_t)BaseQtdPointer;
    transfer->union2.unitTail = (uint32_t)qtdPointer;
    /* link transfer to qh */
    transfer->next = NULL;
    if (vltQhPointer->ehciTransferHead == NULL)
    {
        transfer->next = NULL;
        vltQhPointer->ehciTransferHead = vltQhPointer->ehciTransferTail = transfer;
    }
    else
    {
        transfer->next = NULL;
        vltQhPointer->ehciTransferTail->next = transfer;
        vltQhPointer->ehciTransferTail = transfer;
    }

    USB_HostEhciLock();
    /* link qtd to qh (link to end) */
    entryPointer = &(vltQhPointer->nextQtdPointer);
    dataAddress = *entryPointer; /* dataAddress variable means entry value here */
    while ((dataAddress) && (!(dataAddress & EHCI_HOST_T_INVALID_VALUE)))
    {
        entryPointer = (volatile uint32_t *)dataAddress;
        dataAddress = *entryPointer;
    }
    *entryPointer = (uint32_t)BaseQtdPointer;
    USB_HostEhciUnlock();
    USB_HostEhciStartAsync(ehciInstance);

    return kStatus_USB_Success;
}

static uint32_t USB_HostEhciQtdListRelease(usb_host_ehci_instance_t *ehciInstance,
                                           usb_host_ehci_qtd_t *ehciQtdStart,
                                           usb_host_ehci_qtd_t *ehciQtdEnd)
{
    uint32_t length = 0;
    usb_host_ehci_qtd_t *qtdPointer;

    ehciQtdEnd->nextQtdPointer = 0;

    /* compute remaining length */
    qtdPointer = ehciQtdStart;
    while (qtdPointer != ehciQtdEnd)
    {
        length +=
            ((qtdPointer->transferResults[0] & EHCI_HOST_QTD_TOTAL_BYTES_MASK) >> EHCI_HOST_QTD_TOTAL_BYTES_SHIFT);
        qtdPointer = (usb_host_ehci_qtd_t *)qtdPointer->nextQtdPointer;
    }
    qtdPointer = ehciQtdEnd;
    length += ((qtdPointer->transferResults[0] & EHCI_HOST_QTD_TOTAL_BYTES_MASK) >> EHCI_HOST_QTD_TOTAL_BYTES_SHIFT);

    /* put releasing qtd to idle qtd list */
    USB_HostEhciLock();
    if (ehciInstance->ehciQtdNumber == 0)
    {
        ehciInstance->ehciQtdHead = ehciQtdStart;
        ehciInstance->ehciQtdTail = ehciQtdEnd;
    }
    else
    {
        ehciInstance->ehciQtdTail->nextQtdPointer = (uint32_t)ehciQtdStart;
        ehciInstance->ehciQtdTail = ehciQtdEnd;
    }

    while (ehciQtdStart != ehciQtdEnd)
    {
        ehciInstance->ehciQtdNumber++;
        ehciQtdStart = (usb_host_ehci_qtd_t *)ehciQtdStart->nextQtdPointer;
    }
    ehciInstance->ehciQtdNumber++;
    USB_HostEhciUnlock();

    return length;
}

static usb_status_t USB_HostEhciQhQtdListDeinit(usb_host_ehci_instance_t *ehciInstance,
                                                usb_host_ehci_pipe_t *ehciPipePointer)
{
    volatile usb_host_ehci_qh_t *vltQhPointer;
    usb_host_transfer_t *transfer;
    usb_host_transfer_t *nextTransfer;
    uint8_t needStop = 0;

    vltQhPointer = (volatile usb_host_ehci_qh_t *)ehciPipePointer->ehciQh;

    USB_HostEhciLock(); /* this API is called from APP, the host task may occupy to access the same resource */
    /* remove qtd from qh */
    if ((!((uint32_t)vltQhPointer->nextQtdPointer & EHCI_HOST_T_INVALID_VALUE)) ||
        (!((uint32_t)vltQhPointer->currentQtdPointer & EHCI_HOST_T_INVALID_VALUE)))
    {
        /* need stop async schedule */
        if ((!(vltQhPointer->horizontalLinkPointer & EHCI_HOST_T_INVALID_VALUE)) &&
            (ehciPipePointer->pipeCommon.pipeType != USB_ENDPOINT_INTERRUPT))
        {
            needStop = 1;
        }
        if (needStop)
        {
            USB_HostEhciStopAsync(ehciInstance);
        }
        vltQhPointer->currentQtdPointer = EHCI_HOST_T_INVALID_VALUE;             /* invalid current qtd */
        vltQhPointer->nextQtdPointer = EHCI_HOST_T_INVALID_VALUE;                /* invalid next qtd */
        vltQhPointer->transferOverlayResults[0] &= (~EHCI_HOST_QTD_STATUS_MASK); /* clear error status */
        if (needStop)
        {
            USB_HostEhciStartAsync(ehciInstance);
        }
    }

    /* remove transfer from the QH transfer list */
    transfer = vltQhPointer->ehciTransferHead;
    vltQhPointer->ehciTransferHead = vltQhPointer->ehciTransferTail = NULL;
    USB_HostEhciUnlock();

    /* release qtd  and transfer callback*/
    while (transfer != NULL)
    {
        nextTransfer = transfer->next; /* the transfer is released when call back */
        transfer->transferSofar =
            USB_HostEhciQtdListRelease(ehciInstance, (usb_host_ehci_qtd_t *)(transfer->union1.unitHead),
                                       (usb_host_ehci_qtd_t *)(transfer->union2.unitTail));
        transfer->transferSofar = (transfer->transferLength < transfer->transferSofar) ?
                                      0 :
                                      (transfer->transferLength - transfer->transferSofar);
        transfer->callbackFn(transfer->callbackParam, transfer, kStatus_USB_TransferCancel);
        transfer = nextTransfer;
    }

    return kStatus_USB_Success;
}

static usb_status_t USB_HostEhciTransferQtdListDeinit(usb_host_ehci_instance_t *ehciInstance,
                                                      usb_host_ehci_pipe_t *ehciPipePointer,
                                                      usb_host_transfer_t *transfer)
{
    volatile usb_host_ehci_qh_t *vltQhPointer;
    usb_host_transfer_t *preSearchTransfer;
    uint32_t qhNextQtdValue;
    uint32_t qtdPointerEntry;
    uint32_t *searchQtdEntryPointer;

    vltQhPointer = (volatile usb_host_ehci_qh_t *)ehciPipePointer->ehciQh;

    USB_HostEhciLock(); /* this API is called from APP, the host task may occupy to access the same resource */
    /* remove qtd from qh */
    qhNextQtdValue = (uint32_t)vltQhPointer->currentQtdPointer;
    qtdPointerEntry = *((uint32_t *)qhNextQtdValue + 2); /* note: qtdPointerEntry means qtd status */
    if ((qhNextQtdValue & EHCI_HOST_T_INVALID_VALUE) || (!(qtdPointerEntry & EHCI_HOST_QTD_STATUS_ACTIVE_MASK)))
    {
        qhNextQtdValue = (uint32_t)vltQhPointer->nextQtdPointer;
    }
    if (!(qhNextQtdValue & EHCI_HOST_T_INVALID_VALUE)) /* there is pending qtd in the qh */
    {
        /* this qh don't schedule temporarily */
        if (ehciPipePointer->pipeCommon.pipeType != USB_ENDPOINT_INTERRUPT)
        {
            USB_HostEhciStopAsync(ehciInstance);
        }
        vltQhPointer->currentQtdPointer |= EHCI_HOST_T_INVALID_VALUE; /* invalid current qtd */
        vltQhPointer->nextQtdPointer |= EHCI_HOST_T_INVALID_VALUE;    /* invalid next qtd */
        if (ehciPipePointer->pipeCommon.pipeType != USB_ENDPOINT_INTERRUPT)
        {
            USB_HostEhciStartAsync(ehciInstance);
        }

        /* remove qtd from qh one by one */
        qtdPointerEntry = transfer->union1.unitHead;
        while (1)
        {
            /* search qh's qtd list for qtdPointerEntry */
            searchQtdEntryPointer = &qhNextQtdValue;
            while (!((*searchQtdEntryPointer) & EHCI_HOST_T_INVALID_VALUE))
            {
                if ((*searchQtdEntryPointer) == qtdPointerEntry)
                {
                    *searchQtdEntryPointer = *((uint32_t *)qtdPointerEntry); /* remove the qtd from qh */
                    break;
                }
                else
                {
                    searchQtdEntryPointer = (uint32_t *)(*searchQtdEntryPointer);
                }
            }
            if (qtdPointerEntry == transfer->union2.unitTail)
            {
                break;
            }
            qtdPointerEntry = *((uint32_t *)qtdPointerEntry);
        }
    }

    /* remove transfer from the QH transfer list */
    preSearchTransfer = vltQhPointer->ehciTransferHead;
    if (preSearchTransfer == transfer)
    {
        vltQhPointer->ehciTransferHead = preSearchTransfer->next;
    }
    else
    {
        while (preSearchTransfer != NULL)
        {
            if (preSearchTransfer->next == transfer)
            {
                preSearchTransfer->next = transfer->next;
                break;
            }
            else
            {
                preSearchTransfer = preSearchTransfer->next;
            }
        }
    }
    USB_HostEhciUnlock();

    /* release qtd and callback */
    transfer->transferSofar =
        USB_HostEhciQtdListRelease(ehciInstance, (usb_host_ehci_qtd_t *)(transfer->union1.unitHead),
                                   (usb_host_ehci_qtd_t *)(transfer->union2.unitTail));
    transfer->transferSofar =
        (transfer->transferLength < transfer->transferSofar) ? 0 : (transfer->transferLength - transfer->transferSofar);
    transfer->callbackFn(transfer->callbackParam, transfer, kStatus_USB_TransferCancel);

    /* start this qh schedule */
    vltQhPointer->transferOverlayResults[0] &= (~EHCI_HOST_QTD_STATUS_MASK); /* clear error status */
    if ((qhNextQtdValue != 0) && (!(qhNextQtdValue & EHCI_HOST_T_INVALID_VALUE)))
    {
        vltQhPointer->nextQtdPointer = qhNextQtdValue;
    }

    return kStatus_USB_Success;
}

static usb_status_t USB_HostEhciQhInit(usb_host_ehci_instance_t *ehciInstance, usb_host_ehci_pipe_t *ehciPipePointer)
{
    usb_host_ehci_qh_t *qhPointer = NULL;
    uint32_t address, speed, portNumber, hubNumber;
    uint32_t controlBits1 = 0;
    uint32_t controlBits2 = 0;
    /* get qh */
    USB_HostEhciLock();
    if (ehciInstance->ehciQhList != NULL)
    {
        qhPointer = (usb_host_ehci_qh_t *)ehciInstance->ehciQhList;
        ehciInstance->ehciQhList =
            (usb_host_ehci_qh_t *)(ehciInstance->ehciQhList->horizontalLinkPointer & EHCI_HOST_POINTER_ADDRESS_MASK);
    }
    USB_HostEhciUnlock();
    if (qhPointer == NULL)
    {
#ifdef HOST_EHCO
        usb_echo("get qh error\r\n");
#endif
        return kStatus_USB_Error;
    }
    ehciPipePointer->ehciQh = (void *)qhPointer;

    /* initialize qh */
    USB_HostEhciZeroMem((uint32_t *)qhPointer, sizeof(usb_host_ehci_qh_t) / 4);
    qhPointer->horizontalLinkPointer = EHCI_HOST_T_INVALID_VALUE;
    qhPointer->currentQtdPointer = EHCI_HOST_T_INVALID_VALUE;
    qhPointer->nextQtdPointer = EHCI_HOST_T_INVALID_VALUE;
    qhPointer->alternateNextQtdPointer = EHCI_HOST_T_INVALID_VALUE;
    qhPointer->ehciPipePointer = ehciPipePointer;
    qhPointer->timeOutLabel = 0;
    qhPointer->timeOutValue = USB_HOST_EHCI_CONTROL_BULK_TIME_OUT_VALUE;
    USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetDeviceSpeed, &speed);
    /* initialize staticEndpointStates[0] */
    if (ehciPipePointer->pipeCommon.pipeType == USB_ENDPOINT_INTERRUPT)
    {
        /* Software should set the RL field to zero if the queue head is an interrupt endpoint. */
        controlBits1 |= ((0U << EHCI_HOST_QH_RL_SHIFT) & EHCI_HOST_QH_RL_MASK);
    }
    else
    {
        if (ehciPipePointer->pipeCommon.nakCount >= 16)
        {
            controlBits1 |= ((15U << EHCI_HOST_QH_RL_SHIFT) & EHCI_HOST_QH_RL_MASK);
        }
        else
        {
            controlBits1 |=
                (((uint32_t)ehciPipePointer->pipeCommon.nakCount << EHCI_HOST_QH_RL_SHIFT) & EHCI_HOST_QH_RL_MASK);
        }
    }
    if (ehciPipePointer->pipeCommon.pipeType == USB_ENDPOINT_CONTROL)
    {
        if (speed != USB_SPEED_HIGH)
        {
            controlBits1 |= (1 << EHCI_HOST_QH_C_SHIFT);
        }
        controlBits1 |= (1 << EHCI_HOST_QH_DTC_SHIFT);
    }
    controlBits1 |= ((uint32_t)ehciPipePointer->pipeCommon.maxPacketSize << EHCI_HOST_QH_MAX_PACKET_LENGTH_SHIFT);
    controlBits1 |= (speed << EHCI_HOST_QH_EPS_SHIFT);
    controlBits1 |= ((uint32_t)ehciPipePointer->pipeCommon.endpointAddress << EHCI_HOST_QH_ENDPT_SHIFT);
    USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetDeviceAddress,
                                           &address);
    controlBits1 |= (address << EHCI_HOST_QH_DEVICE_ADDRESS_SHIFT);
    qhPointer->staticEndpointStates[0] = controlBits1;
    if (speed == USB_SPEED_HIGH)
    {
        controlBits2 |= ((uint32_t)ehciPipePointer->pipeCommon.numberPerUframe << EHCI_HOST_QH_MULT_SHIFT);
    }
    else
    {
        controlBits2 |= (0x00000001U << EHCI_HOST_QH_MULT_SHIFT);
    }
    /*initialize staticEndpointStates[1] */
    if (speed != USB_SPEED_HIGH)
    {
        USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetDeviceHSHubNumber,
                                               &hubNumber);
        USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetDeviceHSHubPort,
                                               &portNumber);
    }
    else
    {
        USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetDeviceHubNumber,
                                               &hubNumber);
        USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetDevicePortNumber,
                                               &portNumber);
    }
    controlBits2 |= (portNumber << EHCI_HOST_QH_PORT_NUMBER_SHIFT);
    controlBits2 |= (hubNumber << EHCI_HOST_QH_HUB_ADDR_SHIFT);
    controlBits2 |= ((uint32_t)ehciPipePointer->uframeCmask << EHCI_HOST_QH_UFRAME_CMASK_SHIFT);
    controlBits2 |= ((uint32_t)ehciPipePointer->uframeSmask << EHCI_HOST_QH_UFRAME_SMASK_SHIFT);
    qhPointer->staticEndpointStates[1] = controlBits2;

    return kStatus_USB_Success;
}

static usb_status_t USB_HostEhciQhDeinit(usb_host_ehci_instance_t *ehciInstance, usb_host_ehci_pipe_t *ehciPipePointer)
{
    usb_host_ehci_qh_t *qhPointer;

    qhPointer = (usb_host_ehci_qh_t *)ehciPipePointer->ehciQh;
    /* de-initialize qtd from qh */
    USB_HostEhciQhQtdListDeinit(ehciInstance, ehciPipePointer);

    /* release QH */
    USB_HostEhciLock();
    qhPointer->horizontalLinkPointer = (uint32_t)ehciInstance->ehciQhList;
    ehciInstance->ehciQhList = qhPointer;
    USB_HostEhciUnlock();

    return kStatus_USB_Success;
}

static void USB_HostEhciAddQhToFrame(usb_host_ehci_instance_t *ehciInstance,
                                     uint32_t entryPointerValue,
                                     uint16_t framePos,
                                     uint16_t uframeInterval)
{
    volatile uint32_t *frameEntryPointer;
    uint32_t frameEntryValue;

    /* search for the inserting point by interval */
    frameEntryPointer = (volatile uint32_t *)(&((uint32_t *)ehciInstance->ehciFrameList)[framePos]);
    while (frameEntryPointer)
    {
        frameEntryValue = *frameEntryPointer;
        if (frameEntryValue & EHCI_HOST_T_INVALID_VALUE)
        {
            /* insert into the end */
            *((uint32_t *)entryPointerValue) = EHCI_HOST_T_INVALID_VALUE;
            *frameEntryPointer = (entryPointerValue | EHCI_HOST_POINTER_TYPE_QH);
            break;
        }

        if ((frameEntryValue & EHCI_HOST_POINTER_ADDRESS_MASK) == entryPointerValue)
        {
            return; /* has inserted */
        }
        if (((frameEntryValue & EHCI_HOST_POINTER_TYPE_MASK) == EHCI_HOST_POINTER_TYPE_QH) &&
            (((usb_host_ehci_qh_t *)(frameEntryValue & EHCI_HOST_POINTER_ADDRESS_MASK))
                 ->ehciPipePointer->uframeInterval <= uframeInterval))
        {
            /* insert into this point */
            *((uint32_t *)entryPointerValue) = frameEntryValue;
            *frameEntryPointer = (entryPointerValue | EHCI_HOST_POINTER_TYPE_QH);
            return;
        }
        else
        {
            frameEntryPointer = (volatile uint32_t *)(frameEntryValue & EHCI_HOST_POINTER_ADDRESS_MASK);
        }
    }
}

static void USB_HostEhciRemoveFromFrame(usb_host_ehci_instance_t *ehciInstance,
                                        uint32_t entryPointerValue,
                                        uint16_t framePos)
{
    volatile uint32_t *frameEntryPointer;
    uint32_t frameEntryValue;

    /* search for the qh/itd/sitd entry */
    frameEntryPointer = (volatile uint32_t *)(&((uint32_t *)ehciInstance->ehciFrameList)[framePos]);

    while (frameEntryPointer)
    {
        frameEntryValue = *frameEntryPointer;
        if (frameEntryValue & EHCI_HOST_T_INVALID_VALUE)
        {
            return;
        }

        if ((frameEntryValue & EHCI_HOST_POINTER_ADDRESS_MASK) == entryPointerValue)
        {
            /* remove the entry */
            *frameEntryPointer = *((uint32_t *)entryPointerValue);
            break;
        }
        else
        {
            frameEntryPointer = (volatile uint32_t *)(frameEntryValue & EHCI_HOST_POINTER_ADDRESS_MASK);
        }
    }
}

#if ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD))
static void USB_HostEhciLinkSitd(usb_host_ehci_instance_t *ehciInstance,
                                 usb_host_ehci_pipe_t *ehciPipePointer,
                                 void *startEntryPointer)
{
    usb_host_ehci_iso_t *isoPointer = (usb_host_ehci_iso_t *)ehciPipePointer->ehciQh;
    usb_host_ehci_sitd_t *sitdPointer;
    uint32_t distance;
    uint32_t frameInterval;
    int32_t shouldLinkFrame;
    int32_t currentFrame;

    frameInterval = (ehciPipePointer->uframeInterval >> 3);

    if (isoPointer->lastLinkFrame == 0xFFFF) /* first link */
    {
        currentFrame = ((ehciInstance->ehciIpBase->FRINDEX & EHCI_MAX_UFRAME_VALUE) >> 3);
        currentFrame = ((uint32_t)(currentFrame + USB_HOST_EHCI_ISO_BOUNCE_FRAME_NUMBER) &
                        (EHCI_MAX_UFRAME_VALUE >> 3)); /* add USB_HOST_EHCI_ISO_BOUNCE_FRAME_NUMBER */
        /* frame should align with interval */
        currentFrame -= ehciPipePointer->startFrame;
        currentFrame =
            ((uint32_t)(currentFrame + frameInterval - 1) & (~(frameInterval - 1))); /* frameInterval is power of 2 */
        currentFrame += ehciPipePointer->startFrame;
    }
    else
    {
        shouldLinkFrame = isoPointer->lastLinkFrame + frameInterval; /* continuous next should link frame */
        if (shouldLinkFrame > (int32_t)(EHCI_MAX_UFRAME_VALUE >> 3))
        {
            shouldLinkFrame = shouldLinkFrame - ((EHCI_MAX_UFRAME_VALUE >> 3) + 1);
        }
        currentFrame = ((ehciInstance->ehciIpBase->FRINDEX & EHCI_MAX_UFRAME_VALUE) >> 3);
        distance = ((shouldLinkFrame - currentFrame + (EHCI_MAX_UFRAME_VALUE >> 3) + 1) &
                    (EHCI_MAX_UFRAME_VALUE >> 3)); /* get the distance from shouldLinkFrame to currentFrame */
        /* shouldLinkFrame has add frameInterval, think about the align with interval, so here add (frameInterval *
         * 2) */
        if ((distance <= (USB_HOST_EHCI_ISO_BOUNCE_FRAME_NUMBER + frameInterval * 2)) && (distance > 0))
        {
            currentFrame = shouldLinkFrame;
        }
        else /* re-link */
        {
            currentFrame =
                ((uint32_t)(currentFrame + USB_HOST_EHCI_ISO_BOUNCE_FRAME_NUMBER) & (EHCI_MAX_UFRAME_VALUE >> 3));
            if (currentFrame > (int32_t)(EHCI_MAX_UFRAME_VALUE >> 3))
            {
                currentFrame = currentFrame - ((EHCI_MAX_UFRAME_VALUE >> 3) + 1);
            }
            /* frame should align with interval */
            currentFrame -= ehciPipePointer->startFrame;
            currentFrame = ((uint32_t)(currentFrame + frameInterval - 1) & (~(frameInterval - 1)));
            currentFrame += ehciPipePointer->startFrame;
        }
    }
    if (currentFrame >= (int32_t)USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE) /* frame turn around */
    {
        shouldLinkFrame =
            (currentFrame - USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE); /* shouldLinkFrame means inserted frame position */
    }
    else
    {
        shouldLinkFrame = currentFrame; /* shouldLinkFrame means inserted frame position */
    }

    sitdPointer = (usb_host_ehci_sitd_t *)startEntryPointer;
    while (sitdPointer)
    {
        sitdPointer->frameEntryIndex = shouldLinkFrame;
        /* add to frame list head */
        sitdPointer->nextLinkPointer = ((uint32_t *)ehciInstance->ehciFrameList)[shouldLinkFrame];
        ((uint32_t *)ehciInstance->ehciFrameList)[shouldLinkFrame] =
            ((uint32_t)sitdPointer | EHCI_HOST_POINTER_TYPE_SITD);
        if (sitdPointer->nextSitdIndex == 0xFF) /* 0xFF is invalid value */
        {
            break;
        }
        sitdPointer = &(ehciInstance->ehciSitdIndexBase[sitdPointer->nextSitdIndex]); /* next sitd */

        shouldLinkFrame += frameInterval;
        currentFrame += frameInterval;
        if (shouldLinkFrame >= (int32_t)USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE)
        {
            shouldLinkFrame = (shouldLinkFrame - USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE);
        }
    }

    if (currentFrame > (int32_t)(EHCI_MAX_UFRAME_VALUE >> 3))
    {
        currentFrame = currentFrame - ((EHCI_MAX_UFRAME_VALUE >> 3) + 1);
    }
    isoPointer->lastLinkFrame = currentFrame; /* save the last link frame value */
}

static usb_status_t USB_HostEhciSitdArrayInit(usb_host_ehci_instance_t *ehciInstance,
                                              usb_host_ehci_pipe_t *ehciPipePointer,
                                              usb_host_transfer_t *transfer)
{
    usb_host_ehci_iso_t *isoPointer;
    uint32_t sitdNumber = 0;
    usb_host_ehci_sitd_t *sitdPointer;
    uint32_t dataLength = 0;
    uint32_t sitdLength = 0;
    uint32_t dataBufferValue;
    uint32_t hubNumber;
    uint32_t portNumber;
    uint32_t address;
    uint32_t tmp;
    uint8_t index;

    USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetDeviceAddress,
                                           &address);

    sitdNumber = ((transfer->transferLength - 1 + (ehciPipePointer->pipeCommon.maxPacketSize)) /
                  (ehciPipePointer->pipeCommon.maxPacketSize));
    /* get sitd array */
    tmp = ehciPipePointer - ehciInstance->ehciPipeIndexBase; /* pipe index */
    /* USB_HostEhciLock(); */
    if (ehciInstance->ehciSitdNumber >= sitdNumber)
    {
        sitdPointer = ehciInstance->ehciSitdList;
        transfer->union1.unitHead = (uint32_t)sitdPointer;
        for (index = 1; index < sitdNumber; ++index)
        {
            sitdPointer->nextSitdIndex =
                (((usb_host_ehci_sitd_t *)sitdPointer->nextLinkPointer) - ehciInstance->ehciSitdIndexBase);
            sitdPointer = (usb_host_ehci_sitd_t *)sitdPointer->nextLinkPointer;
        }
        sitdPointer->nextSitdIndex = 0xFF;
        ehciInstance->ehciSitdList = (usb_host_ehci_sitd_t *)sitdPointer->nextLinkPointer;
        ehciInstance->ehciSitdNumber -= sitdNumber;
    }
    else
    {
        /* USB_HostEhciUnlock(); */
        return kStatus_USB_Error;
    }
    /* USB_HostEhciUnlock(); */
    transfer->union2.unitTail = (uint32_t)sitdPointer;
    /* initialize sitd array */
    USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetDeviceHubNumber,
                                           &hubNumber);
    USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetDevicePortNumber,
                                           &portNumber);
    sitdPointer = (usb_host_ehci_sitd_t *)transfer->union1.unitHead;
    dataLength = transfer->transferLength;
    while (sitdNumber--)
    {
        USB_HostEhciZeroMem((uint32_t *)sitdPointer, 7);
        sitdLength = dataLength;
        if (sitdLength > ehciPipePointer->pipeCommon.maxPacketSize)
        {
            sitdLength = ehciPipePointer->pipeCommon.maxPacketSize;
        }
        dataBufferValue = (uint32_t)(transfer->transferBuffer + (transfer->transferLength - dataLength));
        dataLength -= sitdLength; /* update left data length */
        sitdPointer->transferResults[1] = dataBufferValue;
        sitdPointer->transferResults[2] = ((dataBufferValue + 4 * 1024) & 0xFFFFF000U);
        sitdPointer->endpointStates[0] =
            (((uint32_t)ehciPipePointer->pipeCommon.direction << EHCI_HOST_SITD_DIRECTION_SHIFT) |
             (portNumber << EHCI_HOST_SITD_PORT_NUMBER_SHIFT) | (hubNumber << EHCI_HOST_SITD_HUB_ADDR_SHIFT) |
             ((uint32_t)ehciPipePointer->pipeCommon.endpointAddress << EHCI_HOST_SITD_ENDPT_SHIFT) |
             (address << EHCI_HOST_SITD_DEVICE_ADDRESS_SHIFT));
        sitdPointer->transferResults[0] =
            ((sitdLength << EHCI_HOST_SITD_TOTAL_BYTES_SHIFT) | (EHCI_HOST_SITD_STATUS_ACTIVE_MASK));

        if (ehciInstance->firstDeviceSpeed == USB_SPEED_HIGH)
        {
            sitdPointer->endpointStates[1] = (((uint32_t)ehciPipePointer->uframeCmask << EHCI_HOST_SITD_CMASK_SHIFT) |
                                              ((uint32_t)ehciPipePointer->uframeSmask << EHCI_HOST_SITD_SMASK_SHIFT));

            tmp = (sitdLength + 187) / 188;
            if (tmp > 1)
            {
                sitdPointer->transferResults[2] |= (0x01 << EHCI_HOST_SITD_TP_SHIFT); /* for iso split */
            }
            else
            {
                sitdPointer->transferResults[2] |= (0x00 << EHCI_HOST_SITD_TP_SHIFT); /* for iso split */
            }
            sitdPointer->transferResults[2] |= (tmp << EHCI_HOST_SITD_TCOUNT_SHIFT); /* for iso split */
        }

        sitdPointer->backPointer = EHCI_HOST_T_INVALID_VALUE;

        sitdPointer = (ehciInstance->ehciSitdIndexBase + sitdPointer->nextSitdIndex);
    }
    sitdPointer = (usb_host_ehci_sitd_t *)transfer->union2.unitTail;
    sitdPointer->transferResults[0] |= (1U << EHCI_HOST_SITD_IOC_SHIFT); /* last set IOC */

    /* link transfer to usb_host_ehci_iso_t transfer list */
    isoPointer = (usb_host_ehci_iso_t *)ehciPipePointer->ehciQh;
    USB_HostEhciLock();
    if (isoPointer->ehciTransferHead == NULL)
    {
        transfer->next = NULL;
        isoPointer->ehciTransferHead = isoPointer->ehciTransferTail = transfer;
    }
    else
    {
        transfer->next = NULL;
        isoPointer->ehciTransferTail->next = transfer;
        isoPointer->ehciTransferTail = transfer;
    }
    USB_HostEhciUnlock();

    /* link itd to frame list (note: initialize frameEntryIndex)*/
    USB_HostEhciLinkSitd(ehciInstance, ehciPipePointer, (void *)transfer->union1.unitHead);

    return kStatus_USB_Success;
}

static uint32_t USB_HostEhciSitdArrayRelease(usb_host_ehci_instance_t *ehciInstance,
                                             usb_host_ehci_sitd_t *startSitdPointer,
                                             usb_host_ehci_sitd_t *endSitdPointer)
{
    usb_host_ehci_sitd_t *sitdPointer = startSitdPointer;
    uint32_t leftLength = 0;
    /* remove itd from frame list */
    while (1)
    {
        /* record the transfer's result length */
        leftLength +=
            ((sitdPointer->transferResults[0] & EHCI_HOST_SITD_TOTAL_BYTES_MASK) >> EHCI_HOST_SITD_TOTAL_BYTES_SHIFT);
        USB_HostEhciRemoveFromFrame(ehciInstance, (uint32_t)sitdPointer,
                                    sitdPointer->frameEntryIndex); /* remove from the inserted frame list */

        /* release itd */
        /* USB_HostEhciLock(); */
        sitdPointer->nextLinkPointer = (uint32_t)ehciInstance->ehciSitdList;
        ehciInstance->ehciSitdList = sitdPointer;
        ehciInstance->ehciSitdNumber++;
        /* USB_HostEhciUnlock(); */

        if (sitdPointer == endSitdPointer)
        {
            break;
        }

        sitdPointer = &(ehciInstance->ehciSitdIndexBase[sitdPointer->nextSitdIndex]);
    }

    return leftLength;
}

static usb_status_t USB_HostEhciSitdArrayDeinit(usb_host_ehci_instance_t *ehciInstance,
                                                usb_host_ehci_pipe_t *ehciPipePointer)
{
    usb_host_ehci_iso_t *isoPointer = (usb_host_ehci_iso_t *)ehciPipePointer->ehciQh;
    usb_host_transfer_t *transfer;
    usb_host_transfer_t *nextTransfer;

    /* firstly remove the transfer (because host task may occupy to access the resource) */
    USB_HostEhciLock();
    transfer = isoPointer->ehciTransferHead;
    isoPointer->ehciTransferHead = isoPointer->ehciTransferTail = NULL;
    USB_HostEhciUnlock();

    while (transfer != NULL)
    {
        nextTransfer = transfer->next;
        /* remove sitd from frame list and release itd */
        transfer->transferSofar =
            transfer->transferLength - USB_HostEhciSitdArrayRelease(ehciInstance,
                                                                    (usb_host_ehci_sitd_t *)transfer->union1.unitHead,
                                                                    (usb_host_ehci_sitd_t *)transfer->union2.unitTail);
        /* transfer callback */
        transfer->callbackFn(transfer->callbackParam, transfer, kStatus_USB_TransferCancel);
        /* next transfer */
        transfer = nextTransfer;
    }

    return kStatus_USB_Success;
}
#endif /* USB_HOST_CONFIG_EHCI_MAX_SITD */

#if ((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD))
static uint32_t USB_HostEhciGetItdLinkFrame(usb_host_ehci_instance_t *ehciInstance,
                                            uint32_t lastLinkUframe,
                                            uint16_t startUframe,
                                            uint16_t uframeInterval)
{
    int32_t shouldLinkUframe;
    int32_t currentUframe;
    int32_t distance;

    if (lastLinkUframe != 0xFFFF)
    {
        shouldLinkUframe = lastLinkUframe + uframeInterval;
        if (shouldLinkUframe > (int32_t)EHCI_MAX_UFRAME_VALUE)
        {
            shouldLinkUframe = shouldLinkUframe - (EHCI_MAX_UFRAME_VALUE + 1);
        }
        currentUframe = (ehciInstance->ehciIpBase->FRINDEX & EHCI_MAX_UFRAME_VALUE);
        distance = ((shouldLinkUframe - currentUframe + EHCI_MAX_UFRAME_VALUE + 1) &
                    EHCI_MAX_UFRAME_VALUE); /* get the distance */
        /* shouldLinkUframe has add uframeInterval, think about the align with interval, so here add (uframeInterval
         * * 2) */
        if ((distance <= (int32_t)(USB_HOST_EHCI_ISO_BOUNCE_UFRAME_NUMBER + (uframeInterval * 2))) && (distance > 2))
        {
            currentUframe = shouldLinkUframe;
        }
        else /* re-link */
        {
            currentUframe =
                ((uint32_t)(currentUframe + USB_HOST_EHCI_ISO_BOUNCE_UFRAME_NUMBER) & EHCI_MAX_UFRAME_VALUE);
            if (currentUframe > (int32_t)EHCI_MAX_UFRAME_VALUE)
            {
                currentUframe = currentUframe - (EHCI_MAX_UFRAME_VALUE + 1);
            }
            /* uframe should align with interval */
            currentUframe -= startUframe;
            currentUframe = ((uint32_t)(currentUframe + uframeInterval - 1) &
                             (~((uint32_t)uframeInterval - 1))); /* uframeInterval is power of 2 */
            currentUframe += startUframe;
        }
    }
    else
    {
        currentUframe = (ehciInstance->ehciIpBase->FRINDEX & EHCI_MAX_UFRAME_VALUE);
        currentUframe = ((uint32_t)(currentUframe + USB_HOST_EHCI_ISO_BOUNCE_UFRAME_NUMBER) & EHCI_MAX_UFRAME_VALUE);
        /* uframe should align with interval */
        currentUframe -= startUframe;
        currentUframe = ((uint32_t)(currentUframe + uframeInterval - 1) &
                         (~((uint32_t)uframeInterval - 1))); /* uframeInterval is power of 2 */
        currentUframe += startUframe;
    }

    return currentUframe;
}

static usb_status_t USB_HostEhciItdArrayInit(usb_host_ehci_instance_t *ehciInstance,
                                             usb_host_ehci_pipe_t *ehciPipePointer,
                                             usb_host_transfer_t *transfer)
{
    usb_host_ehci_iso_t *isoPointer;
    usb_host_ehci_itd_t *itdPointer = NULL;
    usb_host_ehci_itd_t *tmpItdPointer;
    uint32_t dataLength;        /* the remaining data for sending */
    uint32_t transactionLength; /* the initializing transaction descriptor data length */
    uint32_t itdBufferValue;
    uint32_t itdBufferBaseValue; /* for calculating PG value */
    uint32_t address;
    uint32_t lastShouldLinkUframe;
    uint32_t linkUframe;
    uint32_t minDataPerItd = ehciPipePointer->pipeCommon.numberPerUframe * ehciPipePointer->pipeCommon.maxPacketSize;
    uint8_t maxItdNumber;
    uint8_t index = 0;

    isoPointer = (usb_host_ehci_iso_t *)ehciPipePointer->ehciQh;
    USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetDeviceAddress,
                                           &address);

    /* max needed itd number, the actual needed number may be less because micro-frame interval may be less than 8 */
    maxItdNumber = ((transfer->transferLength - 1 + minDataPerItd) / minDataPerItd);
    if (ehciPipePointer->uframeInterval < 8)
    {
        maxItdNumber = ((maxItdNumber * ehciPipePointer->uframeInterval + 7) / 8) + 1;
    }
    if (maxItdNumber > ehciInstance->ehciItdNumber)
    {
        return kStatus_USB_Error;
    }

    /* link transfer to usb_host_ehci_iso_t transfer list */
    transfer->next = NULL;
    /* USB_HostEhciLock(); */
    if (isoPointer->ehciTransferHead == NULL)
    {
        isoPointer->ehciTransferHead = isoPointer->ehciTransferTail = transfer;
    }
    else
    {
        isoPointer->ehciTransferTail->next = transfer;
        isoPointer->ehciTransferTail = transfer;
    }
    /* USB_HostEhciUnlock(); */

    dataLength = transfer->transferLength;
    transfer->union1.unitHead = (uint32_t)NULL;
    /* get the link micro-frame */
    lastShouldLinkUframe = USB_HostEhciGetItdLinkFrame(
        ehciInstance, isoPointer->lastLinkFrame,
        (uint16_t)((ehciPipePointer->startFrame << 3) + ehciPipePointer->startUframe), ehciPipePointer->uframeInterval);
    if (lastShouldLinkUframe > EHCI_MAX_UFRAME_VALUE)
    {
        linkUframe = lastShouldLinkUframe - (EHCI_MAX_UFRAME_VALUE + 1);
    }
    else
    {
        linkUframe = lastShouldLinkUframe;
    }
    while (dataLength)
    {
        /* get one idle itd */
        tmpItdPointer = ehciInstance->ehciItdList;
        ehciInstance->ehciItdList = (usb_host_ehci_itd_t *)tmpItdPointer->nextLinkPointer;
        ehciInstance->ehciItdNumber -= 1;
        if (tmpItdPointer == NULL)
        {
            return kStatus_USB_Error; /* this should not reach */
        }
        tmpItdPointer->nextItdPointer = NULL;

        /* use the itd */
        if (transfer->union1.unitHead == (uint32_t)NULL) /* first itd */
        {
            transfer->union1.unitHead = (uint32_t)tmpItdPointer;
        }
        else /* link itd list */
        {
            itdPointer->nextItdPointer = tmpItdPointer;
        }
        itdPointer = tmpItdPointer;

        /* itd has been set to all zero when releasing */
        itdBufferBaseValue = itdBufferValue =
            (uint32_t)(transfer->transferBuffer + (transfer->transferLength - dataLength));
        for (index = 0; index < 7; ++index)
        {
            itdPointer->bufferPointers[index] = ((itdBufferBaseValue + (index * 4 * 1024)) & 0xFFFFF000U);
        }
        /* initialize iTD common fields */
        itdPointer->bufferPointers[0] |=
            (((uint32_t)ehciPipePointer->pipeCommon.endpointAddress << EHCI_HOST_ITD_ENDPT_SHIFT) |
             (address << EHCI_HOST_ITD_DEVICE_ADDRESS_SHIFT));
        itdPointer->bufferPointers[1] |=
            (((uint32_t)ehciPipePointer->pipeCommon.direction << EHCI_HOST_ITD_DIRECTION_SHIFT) |
             ((uint32_t)ehciPipePointer->pipeCommon.maxPacketSize << EHCI_HOST_ITD_MAX_PACKET_SIZE_SHIFT));
        itdPointer->bufferPointers[2] |= (ehciPipePointer->pipeCommon.numberPerUframe);
        /* initialize transaction descriptors */
        for (index = (linkUframe & 0x0007); index < 8; index += ehciPipePointer->uframeInterval)
        {
            transactionLength = ((dataLength > minDataPerItd) ? minDataPerItd : dataLength);
            /* initialize the uframeIndex's transaction descriptor in itd */
            itdPointer->transactions[index] =
                ((EHCI_HOST_ITD_STATUS_ACTIVE_MASK) | (transactionLength << EHCI_HOST_ITD_TRANSACTION_LEN_SHIFT) |
                 ((((itdBufferValue & 0xFFFFF000U) - (itdBufferBaseValue & 0xFFFFF000U)) >>
                   EHCI_HOST_ITD_BUFFER_POINTER_SHIFT)
                  << EHCI_HOST_ITD_PG_SHIFT) |
                 (itdBufferValue & EHCI_HOST_ITD_TRANSACTION_OFFSET_MASK));
            dataLength -= transactionLength;
            itdBufferValue += transactionLength;
            if (dataLength <= 0)
            {
                break;
            }
        }
    }

    transfer->union2.unitTail = (uint32_t)itdPointer;
    itdPointer->transactions[index] |= (1 << EHCI_HOST_ITD_IOC_SHIFT); /* last set IOC */

    /* link itd to frame list (note: initialize frameEntryIndex)*/
    while (itdPointer)
    {
        itdPointer->frameEntryIndex = linkUframe;
        /* add to frame head */
        itdPointer->nextLinkPointer = ((uint32_t *)ehciInstance->ehciFrameList)[linkUframe >> 3];
        *(uint32_t *)((uint32_t *)ehciInstance->ehciFrameList)[linkUframe >> 3] =
            ((uint32_t)itdPointer | EHCI_HOST_POINTER_TYPE_ITD);
        itdPointer = itdPointer->nextItdPointer;
        if (itdPointer == NULL)
        {
            break;
        }

        linkUframe += ehciPipePointer->uframeInterval;
        lastShouldLinkUframe += ehciPipePointer->uframeInterval;
        if (linkUframe >= (USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE << 3))
        {
            linkUframe = (linkUframe - (USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE << 3));
        }
    }

    if (lastShouldLinkUframe > EHCI_MAX_UFRAME_VALUE)
    {
        lastShouldLinkUframe = lastShouldLinkUframe - (EHCI_MAX_UFRAME_VALUE + 1);
    }
    isoPointer->lastLinkFrame = lastShouldLinkUframe;

    return kStatus_USB_Success;
}

static uint32_t USB_HostEhciItdArrayRelease(usb_host_ehci_instance_t *ehciInstance,
                                            usb_host_ehci_itd_t *startItdPointer,
                                            usb_host_ehci_itd_t *endItdPointer)
{
    usb_host_ehci_itd_t *itdPointer = startItdPointer;
    uint8_t index;
    uint32_t doneLength = 0;

    /* remove itd from frame list */
    while (1)
    {
        /* record the transfer's result length */
        for (index = 0; index < 8; ++index)
        {
            doneLength += ((itdPointer->transactions[index] & EHCI_HOST_ITD_TRANSACTION_LEN_MASK) >>
                           EHCI_HOST_ITD_TRANSACTION_LEN_SHIFT);
        }

        USB_HostEhciRemoveFromFrame(ehciInstance, (uint32_t)itdPointer,
                                    itdPointer->frameEntryIndex); /* remove from the inserted frame list */

        /* release itd */
        /* USB_HostEhciLock(); */
        USB_HostEhciZeroMem((uint32_t *)itdPointer, sizeof(usb_host_ehci_itd_t) >> 2);
        itdPointer->nextLinkPointer = (uint32_t)ehciInstance->ehciItdList;
        ehciInstance->ehciItdList = itdPointer;
        ehciInstance->ehciItdNumber++;
        /* USB_HostEhciUnlock(); */

        if (itdPointer == endItdPointer)
        {
            break;
        }
        itdPointer = itdPointer->nextItdPointer;
    }

    return doneLength;
}

static usb_status_t USB_HostEhciItdArrayDeinit(usb_host_ehci_instance_t *ehciInstance,
                                               usb_host_ehci_pipe_t *ehciPipePointer)
{
    usb_host_ehci_iso_t *isoPointer = (usb_host_ehci_iso_t *)ehciPipePointer->ehciQh;
    usb_host_transfer_t *transfer;
    usb_host_transfer_t *nextTransfer;
    uint32_t doneLength = 0;

    /* firstly remove the transfer (because host task may occupy to access the resource) */
    USB_HostEhciLock();
    transfer = isoPointer->ehciTransferHead;
    isoPointer->ehciTransferHead = isoPointer->ehciTransferTail = NULL;
    USB_HostEhciUnlock();

    while (transfer != NULL)
    {
        nextTransfer = transfer->next;
        doneLength = 0;
        /* remove itd from frame list and release itd */
        doneLength = USB_HostEhciItdArrayRelease(ehciInstance, (usb_host_ehci_itd_t *)transfer->union1.unitHead,
                                                 (usb_host_ehci_itd_t *)transfer->union2.unitTail);

        /* transfer callback */
        if (ehciPipePointer->pipeCommon.direction == USB_OUT)
        {
            doneLength = transfer->transferLength;
        }
        transfer->transferSofar = doneLength;
        transfer->callbackFn(transfer->callbackParam, transfer, kStatus_USB_TransferCancel);

        /* next transfer */
        transfer = nextTransfer;
    }

    return kStatus_USB_Success;
}
#endif /* USB_HOST_CONFIG_EHCI_MAX_ITD */

static usb_status_t USB_HostEhciOpenControlBulk(usb_host_ehci_instance_t *ehciInstance,
                                                usb_host_ehci_pipe_t *ehciPipePointer)
{
    usb_host_ehci_qh_t *qhPointer;

    if (USB_HostEhciQhInit(ehciInstance, ehciPipePointer) != kStatus_USB_Success) /* initialize control/bulk qh */
    {
        return kStatus_USB_Error;
    }

    qhPointer = (usb_host_ehci_qh_t *)ehciPipePointer->ehciQh;

    /* add qh to async */
    qhPointer->horizontalLinkPointer = ehciInstance->shedFirstQh->horizontalLinkPointer;
    ehciInstance->shedFirstQh->horizontalLinkPointer = ((uint32_t)qhPointer | EHCI_HOST_POINTER_TYPE_QH);

    return kStatus_USB_Success;
}

static usb_status_t USB_HostEhciCloseControlBulk(usb_host_ehci_instance_t *ehciInstance,
                                                 usb_host_ehci_pipe_t *ehciPipePointer)
{
    volatile usb_host_ehci_qh_t *vltPrevQhPointer;
    uint32_t horizontalLinkValue;

    /* remove qh from async schedule */
    if ((ehciInstance->shedFirstQh->horizontalLinkPointer & EHCI_HOST_POINTER_ADDRESS_MASK) ==
        (uint32_t)ehciPipePointer->ehciQh) /* the removing qh is the first qh in the async list */
    {
        USB_HostEhciStopAsync(ehciInstance);
        ehciInstance->shedFirstQh->horizontalLinkPointer =
            ((usb_host_ehci_qh_t *)ehciPipePointer->ehciQh)->horizontalLinkPointer;
        USB_HostEhciStartAsync(ehciInstance);
    }
    else
    {
        /* search for the removing qh from the async list */
        vltPrevQhPointer = ehciInstance->shedFirstQh;
        while (vltPrevQhPointer != NULL)
        {
            horizontalLinkValue = vltPrevQhPointer->horizontalLinkPointer;
            if ((horizontalLinkValue & EHCI_HOST_T_INVALID_VALUE) ||
                ((horizontalLinkValue & EHCI_HOST_POINTER_ADDRESS_MASK) == (uint32_t)ehciPipePointer->ehciQh) ||
                ((horizontalLinkValue & EHCI_HOST_POINTER_ADDRESS_MASK) == (uint32_t)ehciInstance->shedFirstQh))
            {
                break;
            }

            vltPrevQhPointer = (volatile usb_host_ehci_qh_t *)(horizontalLinkValue & EHCI_HOST_POINTER_ADDRESS_MASK);
        }

        /* remove the qh from async list */
        if ((vltPrevQhPointer != NULL) && (!(horizontalLinkValue & EHCI_HOST_T_INVALID_VALUE)) &&
            ((horizontalLinkValue & EHCI_HOST_POINTER_ADDRESS_MASK) == (uint32_t)ehciPipePointer->ehciQh))
        {
            USB_HostEhciStopAsync(ehciInstance);
            vltPrevQhPointer->horizontalLinkPointer =
                ((usb_host_ehci_qh_t *)ehciPipePointer->ehciQh)->horizontalLinkPointer;
            USB_HostEhciStartAsync(ehciInstance);
        }
    }
    ((usb_host_ehci_qh_t *)ehciPipePointer->ehciQh)->horizontalLinkPointer =
        EHCI_HOST_T_INVALID_VALUE;                              /* invalid next qh link */
    return USB_HostEhciQhDeinit(ehciInstance, ehciPipePointer); /* de-initialize qh and release qh */
}

static usb_status_t USB_HostEhciOpenInterrupt(usb_host_ehci_instance_t *ehciInstance,
                                              usb_host_ehci_pipe_t *ehciPipePointer)
{
    usb_status_t status = kStatus_USB_Success;
    uint32_t frameIndex;

    /* allocate bandwidth */
    if (ehciInstance->firstDeviceSpeed == USB_SPEED_HIGH)
    {
        status = USB_HostBandwidthHsHostAllocateInterrupt(ehciInstance, ehciPipePointer); /* host works as high-speed */
    }
    else
    {
        status = USB_HostBandwidthFslsHostAllocate(ehciInstance,
                                                   ehciPipePointer); /* host works as full-speed or low-speed */
    }

    if (status != kStatus_USB_Success)
    {
        return status;
    }
    if (USB_HostEhciQhInit(ehciInstance, ehciPipePointer) != kStatus_USB_Success)
    {
        return kStatus_USB_Error;
    }

    /* insert QH to frame list */
    for (frameIndex = ehciPipePointer->startFrame; frameIndex < USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE;
         frameIndex += (ehciPipePointer->uframeInterval / 8))
    {
        USB_HostEhciAddQhToFrame(ehciInstance, (uint32_t)ehciPipePointer->ehciQh, frameIndex,
                                 ehciPipePointer->uframeInterval);
    }

    return kStatus_USB_Success;
}

static usb_status_t USB_HostEhciCloseInterrupt(usb_host_ehci_instance_t *ehciInstance,
                                               usb_host_ehci_pipe_t *ehciPipePointer)
{
    uint32_t frameIndex;

    /* remove from frame list */
    for (frameIndex = ehciPipePointer->startFrame; frameIndex < USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE;
         frameIndex += (ehciPipePointer->uframeInterval / 8))
    {
        USB_HostEhciRemoveFromFrame(ehciInstance, (uint32_t)ehciPipePointer->ehciQh, frameIndex);
    }
    ((usb_host_ehci_qh_t *)ehciPipePointer->ehciQh)->horizontalLinkPointer |=
        EHCI_HOST_T_INVALID_VALUE; /* invalid next qh link */

    return USB_HostEhciQhDeinit(ehciInstance, ehciPipePointer); /* de-initilaze qh and release qh */
}

#if (((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD)) || \
     ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD)))

static usb_status_t USB_HostEhciOpenIso(usb_host_ehci_instance_t *ehciInstance, usb_host_ehci_pipe_t *ehciPipePointer)
{
    usb_host_ehci_iso_t *isoPointer;
    usb_status_t status = kStatus_USB_Success;

    if (ehciInstance->firstDeviceSpeed == USB_SPEED_HIGH)
    {
        status = USB_HostBandwidthHsHostAllocateIso(
            ehciInstance, ehciPipePointer); /* allocate iso bandwidth when host works as high-speed */
    }
    else
    {
        status = USB_HostBandwidthFslsHostAllocate(
            ehciInstance, ehciPipePointer); /* allocate iso bandwidth when host works as full-speed or low-speed */
    }

    if (status != kStatus_USB_Success)
    {
        return status;
    }

    /* get usb_host_ehci_iso_t */
    if (ehciInstance->ehciIsoList == NULL)
    {
        return kStatus_USB_Error;
    }
    USB_HostEhciLock();
    isoPointer = ehciInstance->ehciIsoList;
    ehciInstance->ehciIsoList = ehciInstance->ehciIsoList->next;
    USB_HostEhciUnlock();
    isoPointer->lastLinkFrame = 0xFFFF;
    ehciPipePointer->ehciQh = isoPointer;

    return status;
}

static usb_status_t USB_HostEhciCloseIso(usb_host_ehci_instance_t *ehciInstance, usb_host_ehci_pipe_t *ehciPipePointer)
{
    usb_host_ehci_iso_t *isoPointer;
    uint32_t speed;

    isoPointer = (usb_host_ehci_iso_t *)ehciPipePointer->ehciQh;

    if (isoPointer->ehciTransferHead != NULL)
    {
        USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetDeviceSpeed,
                                               &speed);
        if (speed == USB_SPEED_HIGH)
        {
#if ((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD))
            USB_HostEhciItdArrayDeinit(ehciInstance, ehciPipePointer); /* de-initialize itd list and free them */
#endif
        }
        else
        {
#if ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD))
            USB_HostEhciSitdArrayDeinit(ehciInstance, ehciPipePointer); /* de-initialize sitd list and free them */
#endif
        }
    }

    /* release usb_host_ehci_iso_t */
    USB_HostEhciLock();
    isoPointer->next = ehciInstance->ehciIsoList;
    ehciInstance->ehciIsoList = isoPointer;
    USB_HostEhciUnlock();
    return kStatus_USB_Success;
}

#endif

static usb_status_t USB_HostEhciResetIP(usb_host_ehci_instance_t *ehciInstance)
{
    /* reset controller */
    ehciInstance->ehciIpBase->USBCMD = USBHS_USBCMD_RST_MASK;
    while (ehciInstance->ehciIpBase->USBCMD & USBHS_USBCMD_RST_MASK)
    {
    }
/* set host mode */
#if (ENDIANNESS == USB_LITTLE_ENDIAN)
    ehciInstance->ehciIpBase->USBMODE |= 0x03;
#else
    ehciInstance->ehciIpBase->USBMODE |= (0x03 | (0x01 << USBHS_USBMODE_ES_SHIFT));
#endif
    /* check frame list size */
    if (!(ehciInstance->ehciIpBase->HCCPARAMS & USBHS_HCCPARAMS_PFL_MASK))
    {
#if ((USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE < 8) || (USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE > 1024))
        return kStatus_USB_Error;
#endif
#if (USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE & (USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE - 1))
        return kStatus_USB_Error; /* frame size must be 1024/512/256/128/64/32/16/8 */
#endif
    }
    return kStatus_USB_Success;
}

static usb_status_t USB_HostEhciStartIP(usb_host_ehci_instance_t *ehciInstance)
{
    uint32_t tmp = 0;

    if (ehciInstance->ehciIpBase->HCSPARAMS & USBHS_HCSPARAMS_PPC_MASK) /* Ports have power port switches */
    {
        /* only has one port */
        tmp = ehciInstance->ehciIpBase->PORTSC1;
        tmp &= (~EHCI_PORTSC1_W1_BITS);
        ehciInstance->ehciIpBase->PORTSC1 = (tmp | USBHS_PORTSC1_PP_MASK); /* turn on port power */
    }

    /* set frame list size */
    if (ehciInstance->ehciIpBase->HCCPARAMS & USBHS_HCCPARAMS_PFL_MASK)
    {
#if (USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE <= 64)
        ehciInstance->ehciIpBase->USBCMD |= (USBHS_USBCMD_FS2_MASK);
#if (USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE == 64)
        ehciInstance->ehciIpBase->USBCMD |= (0x00 << USBHS_USBCMD_FS_SHIFT);
#elif(USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE == 32)
        ehciInstance->ehciIpBase->USBCMD |= (0x01 << USBHS_USBCMD_FS_SHIFT);
#elif(USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE == 16)
        ehciInstance->ehciIpBase->USBCMD |= (0x02 << USBHS_USBCMD_FS_SHIFT);
#elif(USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE == 8)
        ehciInstance->ehciIpBase->USBCMD |= (0x03 << USBHS_USBCMD_FS_SHIFT);
#endif
#else
#if (USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE == 1024)
        ehciInstance->ehciIpBase->USBCMD |= (0x00 << USBHS_USBCMD_FS_SHIFT);
#elif(USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE == 512)
        ehciInstance->ehciIpBase->USBCMD |= (0x01 << USBHS_USBCMD_FS_SHIFT);
#elif(USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE == 256)
        ehciInstance->ehciIpBase->USBCMD |= (0x02 << USBHS_USBCMD_FS_SHIFT);
#elif(USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE == 128)
        ehciInstance->ehciIpBase->USBCMD |= (0x03 << USBHS_USBCMD_FS_SHIFT);
#endif
#endif
    }

    /* start the controller */
    ehciInstance->ehciIpBase->USBCMD = USBHS_USBCMD_RS_MASK;

    /* set timer0 */
    ehciInstance->ehciIpBase->GPTIMER0LD = (300 * 1000 - 1); /* 100ms */

    /* enable interrupt (USB interrupt enable + USB error interrupt enable + port change detect enable + system error
     * enable + interrupt on async advance enable) + general purpos Timer 0 Interrupt enable */
    ehciInstance->ehciIpBase->USBINTR |= (0x1000037);

    return kStatus_USB_Success;
}

static usb_status_t USB_HostEhciCancelPipe(usb_host_ehci_instance_t *ehciInstance,
                                           usb_host_ehci_pipe_t *ehciPipePointer,
                                           usb_host_transfer_t *transfer)
{
    usb_host_ehci_qh_t *qhPointer;
#if (((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD)) || \
     ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD)))
    usb_host_ehci_iso_t *isoPointer;
    uint32_t speed;
#endif
    uint8_t cancelPipe = 0;

    switch (ehciPipePointer->pipeCommon.pipeType)
    {
        case USB_ENDPOINT_BULK:
        case USB_ENDPOINT_CONTROL:
        case USB_ENDPOINT_INTERRUPT:
            qhPointer = (usb_host_ehci_qh_t *)ehciPipePointer->ehciQh;
            if (qhPointer->ehciTransferHead == NULL) /* there is no transfer to cancel */
            {
                return kStatus_USB_Success;
            }
            if (transfer != NULL)
            {
                if ((qhPointer->ehciTransferHead == transfer) &&
                    (qhPointer->ehciTransferHead == qhPointer->ehciTransferTail)) /* only has this one transfer */
                {
                    cancelPipe = 1;
                }
                else
                {
                    cancelPipe = 0;
                }
            }
            else
            {
                cancelPipe = 1;
            }
            if (cancelPipe == 1) /* cancel all pipe */
            {
                USB_HostEhciQhQtdListDeinit(ehciInstance, ehciPipePointer); /* release all the qtd */
            }
            else /* cancel one transfer */
            {
                USB_HostEhciTransferQtdListDeinit(ehciInstance, ehciPipePointer, transfer);
            }
            break;

#if (((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD)) || \
     ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD)))
        case USB_ENDPOINT_ISOCHRONOUS:
            isoPointer = (usb_host_ehci_iso_t *)ehciPipePointer->ehciQh;
            if (isoPointer->ehciTransferHead == NULL) /* there is no transfer to cancel */
            {
                return kStatus_USB_Success;
            }
            /* cancel all pipe, don't implement canceling transfer for iso */
            USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetDeviceSpeed,
                                                   &speed);
            if (speed == USB_SPEED_HIGH)
            {
#if ((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD))
                USB_HostEhciItdArrayDeinit(ehciInstance, ehciPipePointer); /* de-initialize itd */
#endif
            }
            else
            {
#if ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD))
                USB_HostEhciSitdArrayDeinit(ehciInstance, ehciPipePointer); /* de-initialize sitd */
#endif
            }
            break;
#endif

        default:
            break;
    }

    return kStatus_USB_Success;
}

static usb_status_t USB_HostEhciControlBus(usb_host_ehci_instance_t *ehciInstance, uint8_t busControl)
{
    usb_status_t status = kStatus_USB_Success;
    uint32_t portScRegister;

    switch (busControl)
    {
        case kUSB_HostBusReset:
            /* reset port */
            portScRegister = ehciInstance->ehciIpBase->PORTSC1;
            portScRegister &= (~EHCI_PORTSC1_W1_BITS);
            ehciInstance->ehciIpBase->PORTSC1 = (portScRegister | USBHS_PORTSC1_PR_MASK);
            while (ehciInstance->ehciIpBase->PORTSC1 & USBHS_PORTSC1_PR_MASK)
            {
            }
            break;

        case kUSB_HostBusRestart:
            ehciInstance->deviceAttached = kEHCIDeviceDetached;
            ehciInstance->ehciIpBase->USBINTR |= (USBHS_USBINTR_PCE_MASK); /* enable ehci port change interrupt */
            break;

        case kUSB_HostBusEnableAttach: /* enable device attach */
            if (ehciInstance->deviceAttached == kEHCIDeviceDetached)
            {
                ehciInstance->ehciIpBase->USBINTR |= (USBHS_USBINTR_PCE_MASK); /* enable ehci port change interrupt */
            }
            break;

        case kUSB_HostBusDisableAttach:                                     /* disable device attach */
            ehciInstance->ehciIpBase->USBINTR &= (~USBHS_USBINTR_PCE_MASK); /* disable ehci port change interrupt */
            break;
#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
        case kUSB_HostBusSuspend:
            if (ehciInstance->ehciIpBase->PORTSC1 && USBHS_PORTSC1_CCS_MASK)
            {
                /* set timer1 */
                ehciInstance->ehciIpBase->GPTIMER1LD = (1 * 1000); /* 1ms */
                ehciInstance->ehciIpBase->GPTIMER1CTL |=
                    (USBHS_GPTIMER0CTL_RUN_MASK | USBHS_GPTIMER0CTL_MODE_MASK | USBHS_GPTIMER0CTL_RST_MASK);

                USB_HostEhciStopAsync(ehciInstance);
                USB_HostEhciStopPeriodic(ehciInstance);
                while (ehciInstance->ehciIpBase->USBSTS & (USBHS_USBSTS_PS_MASK | USBHS_USBSTS_AS_MASK))
                {
                    __ASM("nop");
                }
                ehciInstance->ehciIpBase->PORTSC1 &= ~USBHS_PORTSC1_WKCN_MASK;
                ehciInstance->ehciIpBase->PORTSC1 |= USBHS_PORTSC1_WKDS_MASK;
                ehciInstance->ehciIpBase->PORTSC1 |= (USBHS_PORTSC1_SUSP_MASK); /* Suspend the device */

                ehciInstance->matchTick = 0U;
                ehciInstance->ehciIpBase->USBINTR |= (USBHS_USBINTR_TIE1_MASK);
                ehciInstance->busSuspendStatus = kBus_EhciStartSuspend;
            }
            else
            {
                status = kStatus_USB_Error;
            }
            break;
        case kUSB_HostBusResume:
            ehciInstance->ehciIpBase->PORTSC1 &= ~(USBHS_PORTSC1_SUSP_MASK); /* Clear Suspend bit */
            ehciInstance->ehciIpBase->PORTSC1 &= ~USBHS_PORTSC1_PHCD_MASK;
            if (ehciInstance->deviceAttached != kEHCIDeviceDetached)
            {
                ehciInstance->busSuspendStatus = kBus_EhciStartResume;
#if (defined(FSL_FEATURE_SOC_USBNC_COUNT) && (FSL_FEATURE_SOC_USBNC_COUNT > 0U))
                ehciInstance->registerNcBase->USB_OTGn_CTRL &= ~USBNC_USB_OTGn_CTRL_WIE_MASK;
#else
                ehciInstance->ehciIpBase->USBGENCTRL &= ~USBHS_USBGENCTRL_WU_IE_MASK;
#endif
                ehciInstance->ehciIpBase->USBCMD |= (USBHS_USBCMD_RS_MASK);
                ehciInstance->ehciIpBase->PORTSC1 |= (USBHS_PORTSC1_FPR_MASK); /* Resume the device */
            }
            else
            {
                status = kStatus_USB_Error;
            }
            break;
#endif
        default:
            status = kStatus_USB_Error;
            break;
    }
    return status;
}

void USB_HostEhciTransactionDone(usb_host_ehci_instance_t *ehciInstance)
{
    /* process async QH */
    usb_host_ehci_pipe_t *ehciPipePointer;
    usb_host_ehci_pipe_t *ehciClearPipePointer = NULL;
    volatile usb_host_ehci_qh_t *vltQhPointer;
    volatile usb_host_ehci_qtd_t *vltQtdPointer;
    usb_host_transfer_t *transfer;
    usb_host_transfer_t *nextTransfer;
    uint32_t qtdStatus = 0;
#if ((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD))
    volatile usb_host_ehci_itd_t *vltItdPointer;
    uint8_t index = 0;
#endif
#if ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD))
    volatile usb_host_ehci_sitd_t *vltSitdPointer;
#endif
#if (((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD)) || \
     ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD)))
    usb_host_ehci_iso_t *isoPointer;
    uint32_t dataLength;
    uint32_t speed;
#endif

    ehciPipePointer = ehciInstance->ehciRunningPipeList; /* check all the running pipes */
    while (ehciPipePointer != NULL)
    {
        switch (ehciPipePointer->pipeCommon.pipeType)
        {
            case USB_ENDPOINT_BULK:
            case USB_ENDPOINT_INTERRUPT:
            case USB_ENDPOINT_CONTROL:
                vltQhPointer = (volatile usb_host_ehci_qh_t *)ehciPipePointer->ehciQh; /* pipe's qh */
                transfer = vltQhPointer->ehciTransferHead;                             /* qh's transfer */
                while (transfer != NULL)
                {
                    nextTransfer = transfer->next;
                    /* normal case */
                    vltQtdPointer = (volatile usb_host_ehci_qtd_t *)transfer->union2.unitTail;
                    if ((vltQtdPointer->transferResults[0] & (EHCI_HOST_QTD_IOC_MASK)) &&
                        (!(vltQtdPointer->transferResults[0] &
                           EHCI_HOST_QTD_STATUS_ACTIVE_MASK))) /* transfer is done */
                    {
                        qtdStatus = (vltQtdPointer->transferResults[0] & EHCI_HOST_QTD_STATUS_ERROR_MASK);
                        transfer->transferSofar =
                            USB_HostEhciQtdListRelease(ehciInstance, (usb_host_ehci_qtd_t *)(transfer->union1.unitHead),
                                                       (usb_host_ehci_qtd_t *)(transfer->union2.unitTail));
                        transfer->transferSofar = (transfer->transferLength < transfer->transferSofar) ?
                                                      0 :
                                                      (transfer->transferLength - transfer->transferSofar);

                        vltQhPointer->ehciTransferHead = transfer->next;
                        vltQhPointer->timeOutLabel = 0;
                        vltQhPointer->timeOutValue = USB_HOST_EHCI_CONTROL_BULK_TIME_OUT_VALUE;
                        if (qtdStatus) /* has errors */
                        {
                            if (!(vltQhPointer->transferOverlayResults[0] & EHCI_HOST_QTD_STATUS_ACTIVE_MASK))
                            {
                                vltQhPointer->transferOverlayResults[0] &=
                                    (~EHCI_HOST_QTD_STATUS_MASK); /* clear error status */
                            }
                            if (qtdStatus & EHCI_HOST_QH_STATUS_NOSTALL_ERROR_MASK)
                            {
                                transfer->callbackFn(transfer->callbackParam, transfer,
                                                     kStatus_USB_TransferFailed); /* transfer fail */
                            }
                            else
                            {
                                transfer->callbackFn(transfer->callbackParam, transfer,
                                                     kStatus_USB_TransferStall); /* transfer stall */
                            }
                        }
                        else
                        {
                            if ((ehciPipePointer->pipeCommon.pipeType == USB_ENDPOINT_CONTROL) &&
                                (transfer->setupPacket->bRequest == USB_REQUEST_STANDARD_CLEAR_FEATURE) &&
                                (transfer->setupPacket->bmRequestType == USB_REQUEST_TYPE_RECIPIENT_ENDPOINT) &&
                                ((USB_SHORT_FROM_LITTLE_ENDIAN(transfer->setupPacket->wValue) & 0x00FFu) ==
                                 USB_REQUEST_STANDARD_FEATURE_SELECTOR_ENDPOINT_HALT))
                            {
                                ehciClearPipePointer = ehciInstance->ehciRunningPipeList;
                                while (ehciClearPipePointer != NULL)
                                {
                                    /* only compute bulk and interrupt pipe */
                                    if (((ehciClearPipePointer->pipeCommon.endpointAddress |
                                          (ehciClearPipePointer->pipeCommon.direction
                                           << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT)) ==
                                         (uint8_t)(USB_SHORT_FROM_LITTLE_ENDIAN(transfer->setupPacket->wIndex))) &&
                                        (ehciClearPipePointer->pipeCommon.deviceHandle ==
                                         ehciPipePointer->pipeCommon.deviceHandle))
                                    {
                                        break;
                                    }
                                    ehciClearPipePointer =
                                        (usb_host_ehci_pipe_t *)ehciClearPipePointer->pipeCommon.next;
                                }

                                if ((ehciClearPipePointer != NULL) &&
                                    ((ehciClearPipePointer->pipeCommon.pipeType == USB_ENDPOINT_INTERRUPT) ||
                                     (ehciClearPipePointer->pipeCommon.pipeType == USB_ENDPOINT_BULK)))
                                {
                                    ((volatile usb_host_ehci_qh_t *)(ehciClearPipePointer->ehciQh))
                                        ->transferOverlayResults[0] &= (~EHCI_HOST_QTD_DT_MASK);
                                }
                            }
                            transfer->callbackFn(transfer->callbackParam, transfer,
                                                 kStatus_USB_Success); /* transfer success */
                        }
                    }
                    else if ((!(vltQhPointer->transferOverlayResults[0] & EHCI_HOST_QTD_STATUS_ACTIVE_MASK)) &&
                             (vltQhPointer->transferOverlayResults[0] &
                              EHCI_HOST_QH_STATUS_ERROR_MASK)) /* there is error and transfer is done */
                    {
                        qtdStatus = (vltQhPointer->transferOverlayResults[0] & EHCI_HOST_QH_STATUS_ERROR_MASK);
                        vltQtdPointer = (volatile usb_host_ehci_qtd_t *)(vltQhPointer->currentQtdPointer);

                        if (((uint32_t)vltQtdPointer & EHCI_HOST_T_INVALID_VALUE) ||
                            (vltQtdPointer == NULL)) /* the error status is unreasonable */
                        {
                            vltQhPointer->transferOverlayResults[0] &=
                                (~EHCI_HOST_QTD_STATUS_MASK); /* clear error status */
                        }
                        else
                        {
                            /* remove qtd from qh */
                            while ((vltQtdPointer != NULL) && (!(vltQtdPointer->transferResults[0] &
                                                                 EHCI_HOST_QTD_IOC_MASK))) /* find the IOC qtd */
                            {
                                vltQtdPointer = (volatile usb_host_ehci_qtd_t *)vltQtdPointer->nextQtdPointer;
                            }

                            vltQhPointer->nextQtdPointer = EHCI_HOST_T_INVALID_VALUE;
                            vltQhPointer->currentQtdPointer = EHCI_HOST_T_INVALID_VALUE;
                            vltQhPointer->transferOverlayResults[0] &=
                                (~EHCI_HOST_QTD_STATUS_MASK); /* clear error status */
                            if (vltQtdPointer != NULL)
                            {
                                vltQhPointer->nextQtdPointer = vltQtdPointer->nextQtdPointer;
                            }

                            transfer->transferSofar = USB_HostEhciQtdListRelease(
                                ehciInstance, (usb_host_ehci_qtd_t *)(transfer->union1.unitHead),
                                (usb_host_ehci_qtd_t *)(transfer->union2.unitTail));
                            transfer->transferSofar = (transfer->transferLength < transfer->transferSofar) ?
                                                          0 :
                                                          (transfer->transferLength - transfer->transferSofar);
                            vltQhPointer->ehciTransferHead = transfer->next;
                            vltQhPointer->timeOutLabel = 0;
                            vltQhPointer->timeOutValue = USB_HOST_EHCI_CONTROL_BULK_TIME_OUT_VALUE;
                            if (qtdStatus & EHCI_HOST_QH_STATUS_NOSTALL_ERROR_MASK)
                            {
                                transfer->callbackFn(transfer->callbackParam, transfer,
                                                     kStatus_USB_TransferFailed); /* transfer fail */
                            }
                            else
                            {
                                transfer->callbackFn(transfer->callbackParam, transfer,
                                                     kStatus_USB_TransferStall); /* transfer stall */
                            }
                        }
                    }
                    else
                    {
                        break;
                    }
                    transfer = nextTransfer;
                }
                break;
#if (((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD)) || \
     ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD)))
            case USB_ENDPOINT_ISOCHRONOUS:
                qtdStatus = 0; /* qtdStatus means break here, because there is only one break in while for misra */
                isoPointer = (usb_host_ehci_iso_t *)ehciPipePointer->ehciQh; /* pipe's usb_host_ehci_iso_t */
                transfer = isoPointer->ehciTransferHead;                     /* usb_host_ehci_iso_t's transfer */
                while (transfer != NULL)
                {
                    nextTransfer = transfer->next;
                    USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                           kUSB_HostGetDeviceSpeed, &speed);
                    if (speed == USB_SPEED_HIGH)
                    {
#if ((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD))
                        vltItdPointer =
                            (volatile usb_host_ehci_itd_t *)(transfer->union2.unitTail); /* transfer's last itd */
                        for (index = 0; index < 8; ++index)
                        {
                            if (vltItdPointer->transactions[index] & EHCI_HOST_ITD_STATUS_ACTIVE_MASK)
                            {
                                break;
                            }
                        }
                        if (index == 8) /* transfer is done */
                        {
                            /* remove itd from frame list and release itd */
                            dataLength = USB_HostEhciItdArrayRelease(ehciInstance,
                                                                     (usb_host_ehci_itd_t *)transfer->union1.unitHead,
                                                                     (usb_host_ehci_itd_t *)transfer->union2.unitTail);
                            transfer->transferSofar = dataLength;
                            isoPointer->ehciTransferHead = transfer->next;
                            transfer->callbackFn(transfer->callbackParam, transfer,
                                                 kStatus_USB_Success); /* transfer callback success */
                            /* TODO: iso callback error */
                        }
                        else
                        {
                            qtdStatus = 1; /* break */
                        }
#endif
                    }
                    else
                    {
#if ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD))
                        vltSitdPointer =
                            (volatile usb_host_ehci_sitd_t *)(transfer->union2.unitTail); /* transfer's last sitd */
                        if (!(vltSitdPointer->transferResults[0] &
                              EHCI_HOST_SITD_STATUS_ACTIVE_MASK)) /* transfer is done */
                        {
                            /* remove sitd from frame list and release itd */
                            dataLength = USB_HostEhciSitdArrayRelease(
                                ehciInstance, (usb_host_ehci_sitd_t *)transfer->union1.unitHead,
                                (usb_host_ehci_sitd_t *)transfer->union2.unitTail);
                            transfer->transferSofar = dataLength;
                            isoPointer->ehciTransferHead = transfer->next;
                            transfer->callbackFn(transfer->callbackParam, transfer,
                                                 kStatus_USB_Success); /* transfer callback success */
                            /* TODO: iso callback error */
                        }
                        else
                        {
                            qtdStatus = 1; /* break */
                        }
#endif
                    }
                    if (qtdStatus == 1)
                    {
                        break;
                    }
                    transfer = nextTransfer;
                }
                break;
#endif

            default:
                break;
        }
        ehciPipePointer = (usb_host_ehci_pipe_t *)ehciPipePointer->pipeCommon.next;
    }
}

static void USB_HostEhciPortChange(usb_host_ehci_instance_t *ehciInstance)
{
    /* note: only has one port */
    uint32_t portScRegister = ehciInstance->ehciIpBase->PORTSC1;
    int32_t sofStart = 0;
    int32_t sofCount = 0;
    uint32_t index;

    if (portScRegister & USBHS_PORTSC1_CSC_MASK) /* connection status change */
    {
        sofStart = (int32_t)(ehciInstance->ehciIpBase->FRINDEX & EHCI_MAX_UFRAME_VALUE);

        /* process CSC bit */
        while (1)
        {
            portScRegister = ehciInstance->ehciIpBase->PORTSC1;
            if (portScRegister & USBHS_PORTSC1_CSC_MASK)
            {
                /* clear csc bit */
                portScRegister = ehciInstance->ehciIpBase->PORTSC1;
                portScRegister &= (~EHCI_PORTSC1_W1_BITS);
                ehciInstance->ehciIpBase->PORTSC1 = (portScRegister | USBHS_PORTSC1_CSC_MASK);
            }
            sofCount = (int32_t)(ehciInstance->ehciIpBase->FRINDEX & EHCI_MAX_UFRAME_VALUE);
            if (((sofCount - sofStart + EHCI_MAX_UFRAME_VALUE + 1) & EHCI_MAX_UFRAME_VALUE) >
                (1 * 8)) /* delay 1ms to clear CSC */
            {
                break;
            }
        }
    }

    /* process CCS bit */
    portScRegister = ehciInstance->ehciIpBase->PORTSC1;
    if (portScRegister & USBHS_PORTSC1_CCS_MASK) /* process attach */
    {
        if ((ehciInstance->deviceAttached == kEHCIDevicePhyAttached) ||
            (ehciInstance->deviceAttached == kEHCIDeviceAttached))
        {
            return;
        }
#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
        ehciInstance->busSuspendStatus = kBus_EhciIdle;
        ehciInstance->ehciIpBase->USBINTR &= ~(USBHS_USBINTR_TIE1_MASK);
#endif
        for (index = 0; index < USB_HOST_EHCI_PORT_CONNECT_DEBOUNCE_DELAY; ++index)
        {
            USB_HostEhciDelay(ehciInstance->ehciIpBase, 1);
            if (!(ehciInstance->ehciIpBase->PORTSC1 & USBHS_PORTSC1_CCS_MASK))
            {
                break;
            }
        }
        if (index < USB_HOST_EHCI_PORT_CONNECT_DEBOUNCE_DELAY) /* CCS is cleared */
        {
            ehciInstance->deviceAttached = kEHCIDeviceDetached;
            return;
        }
        /* reset port */
        portScRegister = ehciInstance->ehciIpBase->PORTSC1;
        portScRegister &= (~EHCI_PORTSC1_W1_BITS);
        ehciInstance->ehciIpBase->PORTSC1 = (portScRegister | USBHS_PORTSC1_PR_MASK);
        while (ehciInstance->ehciIpBase->PORTSC1 & USBHS_PORTSC1_PR_MASK)
        {
        }
        ehciInstance->firstDeviceSpeed =
            ((ehciInstance->ehciIpBase->PORTSC1 & USBHS_PORTSC1_PSPD_MASK) >> USBHS_PORTSC1_PSPD_SHIFT);
        /* enable ehci phy disconnection */
        if (ehciInstance->firstDeviceSpeed == USB_SPEED_HIGH)
        {
            USB_EhcihostPhyDisconnectDetectCmd(ehciInstance->controllerId, 1);
        }

        /* wait for reset */
        USB_HostEhciDelay(ehciInstance->ehciIpBase, USB_HOST_EHCI_PORT_RESET_DELAY);
        /* process attach */
        USB_OsaEventSet(ehciInstance->taskEventHandle, EHCI_TASK_EVENT_DEVICE_ATTACH);
        /* gpt timer start */
        ehciInstance->ehciIpBase->GPTIMER0CTL |=
            (USBHS_GPTIMER0CTL_RUN_MASK | USBHS_GPTIMER0CTL_MODE_MASK | USBHS_GPTIMER0CTL_RST_MASK);
        ehciInstance->deviceAttached = kEHCIDevicePhyAttached;
    }
    else
    {
        if ((ehciInstance->deviceAttached == kEHCIDevicePhyAttached) ||
            (ehciInstance->deviceAttached == kEHCIDeviceAttached))
        {
#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
            ehciInstance->busSuspendStatus = kBus_EhciIdle;
            ehciInstance->ehciIpBase->USBINTR &= ~(USBHS_USBINTR_TIE1_MASK);
#endif
            /* disable ehci phy disconnection */
            USB_EhcihostPhyDisconnectDetectCmd(ehciInstance->controllerId, 0);
            /* disable async and periodic */
            USB_HostEhciStopAsync(ehciInstance);
            USB_HostEhciStopPeriodic(ehciInstance);
            USB_OsaEventSet(ehciInstance->taskEventHandle, EHCI_TASK_EVENT_DEVICE_DETACH);
        }
    }
}

static void USB_HostEhciTimer0(usb_host_ehci_instance_t *ehciInstance)
{
    volatile usb_host_ehci_qh_t *vltQhPointer;
    volatile usb_host_ehci_qtd_t *vltQtdPointer;
    usb_host_transfer_t *transfer;
    uint32_t backValue;
    volatile uint32_t *totalBytesAddress = NULL;
    usb_host_ehci_pipe_t *ehciPipePointer = ehciInstance->ehciRunningPipeList;
    uint8_t timeoutLabel;

    while (ehciPipePointer != NULL)
    {
        switch (ehciPipePointer->pipeCommon.pipeType)
        {
            case USB_ENDPOINT_BULK:
            case USB_ENDPOINT_CONTROL:
                vltQhPointer = (volatile usb_host_ehci_qh_t *)ehciPipePointer->ehciQh; /* pipe's qh */
                transfer = vltQhPointer->ehciTransferHead;                             /* qh's transfer */
                if ((transfer != NULL))                                                /* there is transfering data */
                {
                    timeoutLabel = 0;
                    if (ehciInstance->deviceAttached != kEHCIDeviceAttached)
                    {
                        vltQtdPointer = (volatile usb_host_ehci_qtd_t *)transfer->union2.unitTail;

                        vltQhPointer->nextQtdPointer = EHCI_HOST_T_INVALID_VALUE; /* invalid next qtd */
                        vltQhPointer->transferOverlayResults[0] &=
                            (~EHCI_HOST_QTD_STATUS_MASK); /* clear error status */
                        timeoutLabel = 1;
                    }
                    else
                    {
                        if (vltQhPointer->transferOverlayResults[0] & EHCI_HOST_QTD_STATUS_ACTIVE_MASK)
                        {
                            vltQtdPointer = (volatile usb_host_ehci_qtd_t *)vltQhPointer->currentQtdPointer;
                            totalBytesAddress = &(vltQhPointer->transferOverlayResults[0]);
                        }
                        else
                        {
                            vltQtdPointer = (volatile usb_host_ehci_qtd_t *)transfer->union2.unitTail;
                            totalBytesAddress = ((uint32_t *)vltQtdPointer + 2);
                        }

                        backValue =
                            (((*totalBytesAddress) & EHCI_HOST_QTD_TOTAL_BYTES_MASK) >>
                             EHCI_HOST_QTD_TOTAL_BYTES_SHIFT);       /* backValue is used for total bytes to transfer */
                        if (vltQhPointer->timeOutLabel != backValue) /* use total bytes to reflect the time out */
                        {
                            vltQhPointer->timeOutValue = USB_HOST_EHCI_CONTROL_BULK_TIME_OUT_VALUE;
                            vltQhPointer->timeOutLabel = backValue;
                        }
                        else
                        {
                            /* time out when the total bytes don't change for the duration
                             * USB_HOST_EHCI_CONTROL_BULK_TIME_OUT_VALUE
                             */
                            (vltQhPointer->timeOutValue)--;
                            if (vltQhPointer->timeOutValue == 0)
                            {
                                /* stop the qh schedule */
                                USB_HostEhciStopAsync(ehciInstance);
                                if (backValue != (((*totalBytesAddress) & EHCI_HOST_QTD_TOTAL_BYTES_MASK) >>
                                                  EHCI_HOST_QTD_TOTAL_BYTES_SHIFT))
                                {
                                    USB_HostEhciStartAsync(ehciInstance);
                                }
                                else
                                {
                                    vltQhPointer->nextQtdPointer = EHCI_HOST_T_INVALID_VALUE; /* invalid next qtd */
                                    vltQhPointer->transferOverlayResults[0] &=
                                        (~EHCI_HOST_QTD_STATUS_MASK); /* clear error status */
                                    USB_HostEhciStartAsync(ehciInstance);
                                    timeoutLabel = 1;
                                }
                            }
                        }
                    }

                    if (timeoutLabel == 1)
                    {
                        /* remove qtd from qh */
                        while ((vltQtdPointer != NULL) &&
                               (!(vltQtdPointer->transferResults[0] & EHCI_HOST_QTD_IOC_MASK)) &&
                               (vltQtdPointer != (usb_host_ehci_qtd_t *)vltQhPointer->ehciTransferTail))
                        {
                            vltQtdPointer = (volatile usb_host_ehci_qtd_t *)vltQtdPointer->nextQtdPointer;
                        }
                        if ((vltQtdPointer != NULL) && (!(vltQtdPointer->nextQtdPointer & EHCI_HOST_T_INVALID_VALUE)))
                        {
                            vltQhPointer->nextQtdPointer =
                                vltQtdPointer->nextQtdPointer; /* start qh if there are other qtd that don't belong to
                                                                  the transfer */
                        }
                        transfer->transferSofar =
                            USB_HostEhciQtdListRelease(ehciInstance, (usb_host_ehci_qtd_t *)(transfer->union1.unitHead),
                                                       (usb_host_ehci_qtd_t *)(transfer->union2.unitTail));
                        transfer->transferSofar = (transfer->transferLength < transfer->transferSofar) ?
                                                      0 :
                                                      (transfer->transferLength - transfer->transferSofar);

                        vltQhPointer->ehciTransferHead = transfer->next;
                        vltQhPointer->timeOutValue = USB_HOST_EHCI_CONTROL_BULK_TIME_OUT_VALUE;
                        transfer->callbackFn(transfer->callbackParam, transfer, kStatus_USB_TransferFailed);
                    }
                }
                break;
            default:
                break;
        }
        ehciPipePointer = (usb_host_ehci_pipe_t *)ehciPipePointer->pipeCommon.next;
    }
}

#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
static void USB_HostEhciTimer1(usb_host_ehci_instance_t *ehciInstance)
{
    if (ehciInstance->deviceAttached != kEHCIDeviceDetached)
    {
        if (kBus_EhciStartSuspend == ehciInstance->busSuspendStatus)
        {
            usb_host_instance_t *hostPointer = (usb_host_instance_t *)ehciInstance->hostHandle;

            if (0 == ehciInstance->matchTick)
            {
                ehciInstance->matchTick = hostPointer->hwTick;
            }
            else
            {
                if ((hostPointer->hwTick - ehciInstance->matchTick) >= 5)
                {
                    ehciInstance->ehciIpBase->USBCMD &= ~USBHS_USBCMD_RS_MASK;
                    ehciInstance->ehciIpBase->USBSTS |= USBHS_USBSTS_SRI_MASK;
#if (defined(FSL_FEATURE_SOC_USBNC_COUNT) && (FSL_FEATURE_SOC_USBNC_COUNT > 0U))
#if 0
                    ehciInstance->registerPhyBase->CTRL |= USBPHY_CTRL_ENVBUSCHG_WKUP_MASK
                                                      | USBPHY_CTRL_ENIDCHG_WKUP_MASK
                                                      | USBPHY_CTRL_ENDPDMCHG_WKUP_MASK
                                                      | USBPHY_CTRL_ENIRQRESUMEDETECT_MASK
                                                      ;
#endif
#endif
                    ehciInstance->ehciIpBase->PORTSC1 |= USBHS_PORTSC1_PHCD_MASK;

                    ehciInstance->registerPhyBase->PWD = 0xFFFFFFFFU;

                    while (ehciInstance->registerPhyBase->CTRL & (USBPHY_CTRL_UTMI_SUSPENDM_MASK))
                    {
                        __ASM("nop");
                    }

#if (defined(FSL_FEATURE_SOC_USBNC_COUNT) && (FSL_FEATURE_SOC_USBNC_COUNT > 0U))
                    ehciInstance->registerNcBase->USB_OTGn_CTRL |= USBNC_USB_OTGn_CTRL_WKUP_ID_EN_MASK |
                                                                   USBNC_USB_OTGn_CTRL_WKUP_VBUS_EN_MASK |
                                                                   USBNC_USB_OTGn_CTRL_WKUP_DPDM_EN_MASK;
                    ehciInstance->registerNcBase->USB_OTGn_CTRL |= USBNC_USB_OTGn_CTRL_WIE_MASK;
#else
                    ehciInstance->ehciIpBase->USBGENCTRL = USBHS_USBGENCTRL_WU_IE_MASK;
#endif
                    ehciInstance->registerPhyBase->CTRL |= USBPHY_CTRL_CLKGATE_MASK;
                    hostPointer->deviceCallback(hostPointer->suspendedDevice, NULL,
                                                kUSB_HostEventSuspended); /* call host callback function */
                    ehciInstance->busSuspendStatus = kBus_EhciSuspended;
                }
            }
        }
        else if (kBus_EhciStartResume == ehciInstance->busSuspendStatus)
        {
            usb_host_instance_t *hostPointer = (usb_host_instance_t *)ehciInstance->hostHandle;
            if (!(ehciInstance->ehciIpBase->PORTSC1 & USBHS_PORTSC1_FPR_MASK))
            {
                ehciInstance->ehciIpBase->PORTSC1 &= ~USBHS_PORTSC1_WKDS_MASK;
                if (ehciInstance->ehciIpBase->PORTSC1 & USBHS_PORTSC1_CCS_MASK)
                {
                    USB_HostEhciStartAsync(ehciInstance);
                    USB_HostEhciStartPeriodic(ehciInstance);
                }
                hostPointer->deviceCallback(hostPointer->suspendedDevice, NULL,
                                            kUSB_HostEventResumed); /* call host callback function */
                hostPointer->suspendedDevice = NULL;
                ehciInstance->busSuspendStatus = kBus_EhciIdle;
                ehciInstance->ehciIpBase->USBINTR &= ~(USBHS_USBINTR_TIE1_MASK);
            }
        }
        else
        {
        }
    }
    else
    {
        ehciInstance->busSuspendStatus = kBus_EhciIdle;
        ehciInstance->ehciIpBase->USBINTR &= ~(USBHS_USBINTR_TIE1_MASK);
    }
}
#endif

usb_status_t USB_HostEhciCreate(uint8_t controllerId,
                                usb_host_handle upperLayerHandle,
                                usb_host_controller_handle *controllerHandle)
{
    uint32_t index = 0;
    usb_osa_status_t osaStatus;
    usb_host_ehci_instance_t *ehciInstance;
    uint32_t usbhsBaseAddrs[] = USBHS_BASE_ADDRS;
    usb_host_ehci_data_t *usbHostEhciData[] = USB_HOST_EHCI_DATA_ARRAY;
    uint8_t *usbHostEhciFrameList[] = USB_HOST_EHCI_FRAME_LIST_ARRAY;
    uint32_t *framePointer;

    if ((uint32_t)(controllerId - kUSB_ControllerEhci0) >= (sizeof(usbhsBaseAddrs) / sizeof(usbhsBaseAddrs[0])))
    {
        return kStatus_USB_ControllerNotFound;
    }

    *controllerHandle = NULL;
    ehciInstance = (usb_host_ehci_instance_t *)USB_OsaMemoryAllocate(
        sizeof(usb_host_ehci_instance_t)); /* malloc host ehci instance */
    if (ehciInstance == NULL)
    {
        return kStatus_USB_AllocFail;
    }
    ehciInstance->controllerId = controllerId;
    ehciInstance->hostHandle = upperLayerHandle;
    ehciInstance->deviceAttached = kEHCIDeviceDetached;
    ehciInstance->ehciIpBase = (USBHS_Type *)
        usbhsBaseAddrs[controllerId - kUSB_ControllerEhci0]; /* operate ehci ip through the base address */
#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
    ehciInstance->busSuspendStatus = kBus_EhciIdle;

#if (defined(USB_HOST_CONFIG_LOW_POWER_MODE) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
    ehciInstance->registerPhyBase = (USBPHY_Type *)USB_EhciPhyGetBase(controllerId);

#if (defined(FSL_FEATURE_SOC_USBNC_COUNT) && (FSL_FEATURE_SOC_USBNC_COUNT > 0U))
    ehciInstance->registerNcBase = (USBNC_Type *)USB_EhciNCGetBase(controllerId);
#endif

#endif

#endif

    if (USB_HostEhciResetIP(ehciInstance) != kStatus_USB_Success) /* reset ehci ip */
    {
        USB_OsaMemoryFree(ehciInstance);
        return kStatus_USB_Error;
    }

    /* initialize ehci frame list */
    ehciInstance->ehciFrameList = usbHostEhciFrameList[ehciInstance->controllerId - kUSB_ControllerEhci0];

    /* initialize ehci units */
    ehciInstance->ehciUnitBase = (uint32_t *)(usbHostEhciData[ehciInstance->controllerId - kUSB_ControllerEhci0]);
    /* initialize qh/qtd/itd/sitd/iso list */
    ehciInstance->ehciQhList = (usb_host_ehci_qh_t *)((uint32_t)(ehciInstance->ehciUnitBase));
    ehciInstance->ehciQtdHead = (usb_host_ehci_qtd_t *)((uint32_t)ehciInstance->ehciQhList +
                                                        (sizeof(usb_host_ehci_qh_t) * USB_HOST_CONFIG_EHCI_MAX_QH));
    ehciInstance->ehciItdList = (usb_host_ehci_itd_t *)((uint32_t)ehciInstance->ehciQtdHead +
                                                        (sizeof(usb_host_ehci_qtd_t) * USB_HOST_CONFIG_EHCI_MAX_QTD));
    ehciInstance->ehciSitdList = ehciInstance->ehciSitdIndexBase =
        (usb_host_ehci_sitd_t *)((uint32_t)ehciInstance->ehciItdList +
                                 (sizeof(usb_host_ehci_itd_t) * USB_HOST_CONFIG_EHCI_MAX_ITD));
    ehciInstance->ehciIsoList = (usb_host_ehci_iso_t *)((uint32_t)ehciInstance->ehciSitdList +
                                                        (sizeof(usb_host_ehci_sitd_t) * USB_HOST_CONFIG_EHCI_MAX_SITD));
    ehciInstance->ehciPipeIndexBase =
        (usb_host_ehci_pipe_t *)((uint32_t)ehciInstance->ehciIsoList +
                                 (sizeof(usb_host_ehci_iso_t) * USB_HOST_EHCI_ISO_NUMBER));
    for (index = 1; index < USB_HOST_CONFIG_EHCI_MAX_QH; ++index)
    {
        ehciInstance->ehciQhList[index - 1].horizontalLinkPointer = (uint32_t)(&ehciInstance->ehciQhList[index]);
    }
    ehciInstance->ehciQhList[USB_HOST_CONFIG_EHCI_MAX_QH - 1].horizontalLinkPointer = (uint32_t)NULL;
    for (index = 1; index < USB_HOST_CONFIG_EHCI_MAX_QTD; ++index)
    {
        ehciInstance->ehciQtdHead[index - 1].nextQtdPointer = (uint32_t)(&ehciInstance->ehciQtdHead[index]);
    }
    ehciInstance->ehciQtdNumber = USB_HOST_CONFIG_EHCI_MAX_QTD;
    ehciInstance->ehciQtdHead[USB_HOST_CONFIG_EHCI_MAX_QTD - 1].nextQtdPointer = (uint32_t)NULL;
    ehciInstance->ehciQtdTail = &ehciInstance->ehciQtdHead[USB_HOST_CONFIG_EHCI_MAX_QTD - 1];

#if ((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD))
    for (index = 1; index < USB_HOST_CONFIG_EHCI_MAX_ITD; ++index)
    {
        ehciInstance->ehciItdList[index - 1].nextLinkPointer = (uint32_t)(&ehciInstance->ehciItdList[index]);
    }
    ehciInstance->ehciItdNumber = USB_HOST_CONFIG_EHCI_MAX_ITD;
    ehciInstance->ehciItdList[USB_HOST_CONFIG_EHCI_MAX_ITD - 1].nextLinkPointer = (uint32_t)NULL;
#endif /* USB_HOST_CONFIG_EHCI_MAX_ITD */

#if ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD))
    for (index = 1; index < USB_HOST_CONFIG_EHCI_MAX_SITD; ++index)
    {
        ehciInstance->ehciSitdList[index - 1].nextLinkPointer = (uint32_t)(&ehciInstance->ehciSitdList[index]);
    }
    ehciInstance->ehciSitdNumber = USB_HOST_CONFIG_EHCI_MAX_SITD;
    ehciInstance->ehciSitdList[USB_HOST_CONFIG_EHCI_MAX_SITD - 1].nextLinkPointer = (uint32_t)NULL;
#endif /* USB_HOST_CONFIG_EHCI_MAX_SITD */

#if ((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD))
    for (index = 1; index < USB_HOST_EHCI_ISO_NUMBER; ++index)
    {
        ehciInstance->ehciIsoList[index - 1].next = &ehciInstance->ehciIsoList[index];
    }
    ehciInstance->ehciIsoList[USB_HOST_EHCI_ISO_NUMBER - 1].next = NULL;
#endif

    /* initialize pipes */
    ehciInstance->ehciPipeList = ehciInstance->ehciPipeIndexBase;
    for (index = 1; index < USB_HOST_CONFIG_MAX_PIPES; ++index)
    {
        ehciInstance->ehciPipeList[index - 1].pipeCommon.next = (usb_host_pipe_t *)&ehciInstance->ehciPipeList[index];
    }
    /* initialize mutext */
    osaStatus = USB_OsaMutexCreate(&ehciInstance->ehciMutex);
    if (osaStatus != kStatus_USB_OSA_Success)
    {
#ifdef HOST_ECHO
        usb_echo("ehci mutex init fail\r\n");
#endif
        USB_OsaMemoryFree(ehciInstance);
        return kStatus_USB_Error;
    }
    /* initialize task event */
    osaStatus = USB_OsaEventCreate(&ehciInstance->taskEventHandle, 1);
    if (osaStatus != kStatus_USB_OSA_Success)
    {
#ifdef HOST_ECHO
        usb_echo("ehci event init fail\r\n");
#endif
        USB_OsaMutexDestroy(ehciInstance->ehciMutex);
        USB_OsaMemoryFree(ehciInstance);
        return kStatus_USB_Error;
    }

    /* initialize first qh */
    ehciInstance->shedFirstQh = ehciInstance->ehciQhList;
    ehciInstance->ehciQhList =
        (usb_host_ehci_qh_t *)(ehciInstance->ehciQhList->horizontalLinkPointer & EHCI_HOST_POINTER_ADDRESS_MASK);
    ehciInstance->shedFirstQh->staticEndpointStates[0] |= (1 << EHCI_HOST_QH_H_SHIFT); /* first qh */
    ehciInstance->shedFirstQh->horizontalLinkPointer = EHCI_HOST_T_INVALID_VALUE;
    ehciInstance->shedFirstQh->currentQtdPointer = EHCI_HOST_T_INVALID_VALUE;
    ehciInstance->shedFirstQh->nextQtdPointer = EHCI_HOST_T_INVALID_VALUE;
    ehciInstance->shedFirstQh->alternateNextQtdPointer = EHCI_HOST_T_INVALID_VALUE;
    ehciInstance->shedFirstQh->horizontalLinkPointer =
        (uint32_t)((uint32_t)(ehciInstance->shedFirstQh) | EHCI_HOST_POINTER_TYPE_QH);

    /* initialize periodic list */
    framePointer = (uint32_t *)ehciInstance->ehciFrameList;
    for (index = 0; index < USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE; ++index)
    {
        framePointer[index] = EHCI_HOST_T_INVALID_VALUE;
    }

    USB_HostEhciStartIP(ehciInstance); /* start ehci ip */

    *controllerHandle = ehciInstance;

    return kStatus_USB_Success;
}

usb_status_t USB_HostEhciDestory(usb_host_controller_handle controllerHandle)
{
    usb_host_ehci_instance_t *ehciInstance = (usb_host_ehci_instance_t *)controllerHandle;

    /* disable all interrupts */
    ehciInstance->ehciIpBase->USBINTR = 0;
    /* stop the controller */
    ehciInstance->ehciIpBase->USBCMD = 0;
    /* free memory */
    USB_OsaMutexDestroy(ehciInstance->ehciMutex);
    USB_OsaEventDestroy(ehciInstance->taskEventHandle);
    USB_OsaMemoryFree(ehciInstance);

    return kStatus_USB_Success;
}

usb_status_t USB_HostEhciOpenPipe(usb_host_controller_handle controllerHandle,
                                  usb_host_pipe_handle *pipeHandle,
                                  usb_host_pipe_init_t *pipeInit)
{
    usb_host_ehci_pipe_t *ehciPipePointer = NULL;
    usb_status_t status;
    uint32_t speed;
    usb_host_ehci_instance_t *ehciInstance = (usb_host_ehci_instance_t *)controllerHandle;

    /* get one pipe */
    USB_HostEhciLock();
    if (ehciInstance->ehciPipeList != NULL)
    {
        ehciPipePointer = ehciInstance->ehciPipeList;
        ehciInstance->ehciPipeList = (usb_host_ehci_pipe_t *)ehciPipePointer->pipeCommon.next;
    }
    USB_HostEhciUnlock();
    if (ehciPipePointer == NULL)
    {
#ifdef HOST_ECHO
        usb_echo("ehci open pipe failed\r\n");
#endif
        return kStatus_USB_Busy;
    }

    /* initialize pipe informations */
    USB_HostEhciZeroMem((uint32_t *)ehciPipePointer, sizeof(usb_host_ehci_pipe_t) / 4);
    ehciPipePointer->pipeCommon.deviceHandle = pipeInit->devInstance;
    ehciPipePointer->pipeCommon.endpointAddress = pipeInit->endpointAddress;
    ehciPipePointer->pipeCommon.direction = pipeInit->direction;
    ehciPipePointer->pipeCommon.interval = pipeInit->interval;
    ehciPipePointer->pipeCommon.maxPacketSize = pipeInit->maxPacketSize;
    ehciPipePointer->pipeCommon.pipeType = pipeInit->pipeType;
    ehciPipePointer->pipeCommon.numberPerUframe = pipeInit->numberPerUframe;
    if (ehciPipePointer->pipeCommon.numberPerUframe == 0)
    {
        ehciPipePointer->pipeCommon.numberPerUframe = 1;
    }
    ehciPipePointer->pipeCommon.nakCount = pipeInit->nakCount;
    ehciPipePointer->pipeCommon.nextdata01 = 0;
    ehciPipePointer->ehciQh = NULL;
    USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetDeviceSpeed, &speed);
    if (ehciPipePointer->pipeCommon.pipeType == USB_ENDPOINT_ISOCHRONOUS)
    {
        ehciPipePointer->pipeCommon.interval =
            (1 << (ehciPipePointer->pipeCommon.interval - 1)); /* iso interval is the power of 2 */
    }
    else if (ehciPipePointer->pipeCommon.pipeType == USB_ENDPOINT_INTERRUPT)
    {
        if (speed == USB_SPEED_HIGH)
        {
            ehciPipePointer->pipeCommon.interval =
                (1 << (ehciPipePointer->pipeCommon.interval - 1)); /* HS interrupt interval is the power of 2 */
        }
        else
        {
            ehciPipePointer->pipeCommon.interval = USB_HostEhciGet2PowerValue(
                ehciPipePointer->pipeCommon
                    .interval); /* FS/LS interrupt interval should be the power of 2, it is used for ehci bandwidth */
        }
    }
    else
    {
    }

    /* save the micro-frame interval, it is convenient for the interval process */
    if (speed == USB_SPEED_HIGH)
    {
        ehciPipePointer->uframeInterval = ehciPipePointer->pipeCommon.interval;
    }
    else
    {
        ehciPipePointer->uframeInterval = 8 * ehciPipePointer->pipeCommon.interval;
    }

    /* open pipe */
    switch (ehciPipePointer->pipeCommon.pipeType)
    {
        case USB_ENDPOINT_CONTROL:
        case USB_ENDPOINT_BULK:
            status = USB_HostEhciOpenControlBulk(ehciInstance, ehciPipePointer);
            break;

#if (((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD)) || \
     ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD)))
        case USB_ENDPOINT_ISOCHRONOUS:
            status = USB_HostEhciOpenIso(ehciInstance, ehciPipePointer);
            break;
#endif

        case USB_ENDPOINT_INTERRUPT:
            status = USB_HostEhciOpenInterrupt(ehciInstance, ehciPipePointer);
            break;

        default:
            status = kStatus_USB_Error;
            break;
    }

    if (status != kStatus_USB_Success)
    {
        /* release pipe */
        USB_HostEhciLock();
        ehciPipePointer->pipeCommon.next = (usb_host_pipe_t *)ehciInstance->ehciPipeList;
        ehciInstance->ehciPipeList = ehciPipePointer;
        USB_HostEhciUnlock();
        return status;
    }

    /* add pipe to run pipe list */
    USB_HostEhciLock();
    ehciPipePointer->pipeCommon.next = (usb_host_pipe_t *)ehciInstance->ehciRunningPipeList;
    ehciInstance->ehciRunningPipeList = ehciPipePointer;
    USB_HostEhciUnlock();

    *pipeHandle = ehciPipePointer;
    return status;
}

usb_status_t USB_HostEhciClosePipe(usb_host_controller_handle controllerHandle, usb_host_pipe_handle pipeHandle)
{
    usb_host_ehci_instance_t *ehciInstance = (usb_host_ehci_instance_t *)controllerHandle;
    usb_host_ehci_pipe_t *ehciPipePointer = (usb_host_ehci_pipe_t *)pipeHandle;
    usb_host_pipe_t *prevPointer = NULL;

    switch (ehciPipePointer->pipeCommon.pipeType)
    {
        case USB_ENDPOINT_BULK:
        case USB_ENDPOINT_CONTROL:
            USB_HostEhciCloseControlBulk(ehciInstance, ehciPipePointer);
            break;

        case USB_ENDPOINT_INTERRUPT:
            USB_HostEhciCloseInterrupt(ehciInstance, ehciPipePointer);
            break;

#if (((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD)) || \
     ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD)))
        case USB_ENDPOINT_ISOCHRONOUS:
            USB_HostEhciCloseIso(ehciInstance, ehciPipePointer);
            break;
#endif

        default:
            break;
    }

    /* delete pipe from run pipe list */
    USB_HostEhciLock();
    prevPointer = (usb_host_pipe_t *)ehciInstance->ehciRunningPipeList;
    if (prevPointer == (usb_host_pipe_t *)ehciPipePointer)
    {
        ehciInstance->ehciRunningPipeList = (usb_host_ehci_pipe_t *)(prevPointer->next);
    }
    else
    {
        while (prevPointer != NULL)
        {
            if (prevPointer->next == (usb_host_pipe_t *)ehciPipePointer)
            {
                prevPointer->next = ehciPipePointer->pipeCommon.next;
                break;
            }
            else
            {
                prevPointer = prevPointer->next;
            }
        }
    }
    USB_HostEhciUnlock();

    /* release pipe */
    USB_HostEhciLock();
    ehciPipePointer->pipeCommon.next = (usb_host_pipe_t *)ehciInstance->ehciPipeList;
    ehciInstance->ehciPipeList = ehciPipePointer;
    USB_HostEhciUnlock();

    return kStatus_USB_Success;
}

usb_status_t USB_HostEhciWritePipe(usb_host_controller_handle controllerHandle,
                                   usb_host_pipe_handle pipeHandle,
                                   usb_host_transfer_t *transfer)
{
    usb_host_ehci_instance_t *ehciInstance = (usb_host_ehci_instance_t *)controllerHandle;
    usb_host_ehci_pipe_t *ehciPipePointer = (usb_host_ehci_pipe_t *)pipeHandle;
    usb_status_t status = kStatus_USB_Success;
#if (((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD)) || \
     ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD)))
    uint32_t speed;
#endif

    switch (ehciPipePointer->pipeCommon.pipeType)
    {
        case USB_ENDPOINT_BULK:
        case USB_ENDPOINT_CONTROL:
        case USB_ENDPOINT_INTERRUPT:
            status = USB_HostEhciQhQtdListInit(ehciInstance, ehciPipePointer,
                                               transfer); /* initialize qtd for control/bulk transfer */
            break;

#if (((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD)) || \
     ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD)))
        case USB_ENDPOINT_ISOCHRONOUS:
            USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetDeviceSpeed,
                                                   &speed);
            if (speed == USB_SPEED_HIGH)
            {
#if ((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD))
                status = USB_HostEhciItdArrayInit(ehciInstance, ehciPipePointer,
                                                  transfer); /* initialize itd for iso transfer */
#endif
            }
            else
            {
#if ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD))
                status = USB_HostEhciSitdArrayInit(ehciInstance, ehciPipePointer,
                                                   transfer); /* initialize sitd for iso transfer */
#endif
            }
            break;
#endif

        default:
            break;
    }
    return status;
}

usb_status_t USB_HostEhciReadpipe(usb_host_controller_handle controllerHandle,
                                  usb_host_pipe_handle pipeHandle,
                                  usb_host_transfer_t *transfer)
{
    return USB_HostEhciWritePipe(controllerHandle, pipeHandle, transfer); /* same as write */
}

usb_status_t USB_HostEhciIoctl(usb_host_controller_handle controllerHandle, uint32_t ioctlEvent, void *ioctlParam)
{
    usb_status_t status = kStatus_USB_Success;
    usb_host_ehci_instance_t *ehciInstance = (usb_host_ehci_instance_t *)controllerHandle;
    usb_host_cancel_param_t *param;
    usb_host_ehci_pipe_t *ehciPipePointer;
    volatile usb_host_ehci_qh_t *vltQhPointer;
    uint32_t deviceAddress;

    if (controllerHandle == NULL)
    {
        return kStatus_USB_InvalidHandle;
    }

    switch (ioctlEvent)
    {
        case kUSB_HostCancelTransfer: /* cancel pipe or one transfer */
            param = (usb_host_cancel_param_t *)ioctlParam;
            status = USB_HostEhciCancelPipe(ehciInstance, (usb_host_ehci_pipe_t *)param->pipeHandle, param->transfer);
            break;

        case kUSB_HostBusControl: /* bus control */
            status = USB_HostEhciControlBus(ehciInstance, *((uint8_t *)ioctlParam));
            break;

        case kUSB_HostGetFrameNumber: /* get frame number */
            *((uint32_t *)ioctlParam) = ((ehciInstance->ehciIpBase->FRINDEX & EHCI_MAX_UFRAME_VALUE) >> 3);
            break;

        case kUSB_HostUpdateControlEndpointAddress:
            ehciPipePointer = (usb_host_ehci_pipe_t *)ioctlParam;
            vltQhPointer = (volatile usb_host_ehci_qh_t *)ehciPipePointer->ehciQh;
            /* update address */
            USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle, kUSB_HostGetDeviceAddress,
                                                   &deviceAddress);
            vltQhPointer->staticEndpointStates[0] |= deviceAddress;
            break;

        case kUSB_HostUpdateControlPacketSize:
            ehciPipePointer = (usb_host_ehci_pipe_t *)ioctlParam;
            vltQhPointer = (volatile usb_host_ehci_qh_t *)ehciPipePointer->ehciQh;
            USB_HostEhciLock();
            if (ehciInstance->ehciIpBase->USBSTS & USBHS_USBSTS_AS_MASK)
            {
                USB_HostEhciStopAsync(ehciInstance);
                /* update max packet size */
                vltQhPointer->staticEndpointStates[0] =
                    (((vltQhPointer->staticEndpointStates[0]) & (~EHCI_HOST_QH_MAX_PACKET_LENGTH_MASK)) |
                     ((uint32_t)ehciPipePointer->pipeCommon.maxPacketSize << EHCI_HOST_QH_MAX_PACKET_LENGTH_SHIFT));
                USB_HostEhciStartAsync(ehciInstance);
            }
            else
            {
                /* update max packet size */
                vltQhPointer->staticEndpointStates[0] =
                    (((vltQhPointer->staticEndpointStates[0]) & (~EHCI_HOST_QH_MAX_PACKET_LENGTH_MASK)) |
                     ((uint32_t)ehciPipePointer->pipeCommon.maxPacketSize << EHCI_HOST_QH_MAX_PACKET_LENGTH_SHIFT));
            }
            USB_HostEhciUnlock();
            break;

        default:
            break;
    }
    return status;
}

void USB_HostEhciTaskFunction(void *hostHandle)
{
    usb_host_ehci_instance_t *ehciInstance;
    uint32_t bitSet;
    usb_device_handle deviceHandle;

    if (hostHandle == NULL)
    {
        return;
    }
    ehciInstance = (usb_host_ehci_instance_t *)((usb_host_instance_t *)hostHandle)->controllerHandle;

    if (USB_OsaEventWait(ehciInstance->taskEventHandle, 0xFF, 0, 0, &bitSet) ==
        kStatus_USB_OSA_Success) /* wait all event */
    {
        if (bitSet & EHCI_TASK_EVENT_PORT_CHANGE) /* port change */
        {
            USB_HostEhciPortChange(ehciInstance);
        }

        if (bitSet & EHCI_TASK_EVENT_TIMER0) /* timer0 */
        {
            USB_HostEhciTimer0(ehciInstance);
        }

#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
        if (bitSet & EHCI_TASK_EVENT_TIMER1) /* timer1 */
        {
            USB_HostEhciTimer1(ehciInstance);
        }
#endif

        if (ehciInstance->deviceAttached == kEHCIDeviceAttached)
        {
            if (bitSet & EHCI_TASK_EVENT_TRANSACTION_DONE) /* transaction done */
            {
                USB_HostEhciTransactionDone(ehciInstance);
            }

            if (bitSet & EHCI_TASK_EVENT_DEVICE_DETACH) /* device detach */
            {
                ehciInstance->ehciIpBase->USBINTR &=
                    (~USBHS_USBINTR_PCE_MASK); /* disable attach, enable when the detach process is done */
                ehciInstance->deviceAttached = kEHCIDeviceDetached;
                USB_HostDetachDevice(ehciInstance->hostHandle, 0, 0);
            }
        }
        else if (ehciInstance->deviceAttached != kEHCIDeviceAttached)
        {
            if (bitSet & EHCI_TASK_EVENT_DEVICE_ATTACH) /* device is attached */
            {
                USB_HostEhciStartAsync(ehciInstance);
                USB_HostEhciStartPeriodic(ehciInstance);

                if (USB_HostAttachDevice(ehciInstance->hostHandle, ehciInstance->firstDeviceSpeed, 0, 0, 1,
                                         &deviceHandle) == kStatus_USB_Success)
                {
                    ehciInstance->deviceAttached = kEHCIDeviceAttached;
                }
            }
        }
        else
        {
        }
    }
}

void USB_HostEhciIsrFunction(void *hostHandle)
{
    usb_host_ehci_instance_t *ehciInstance;
    static uint32_t interruptStatus = 0;

    if (hostHandle == NULL)
    {
        return;
    }

    ehciInstance = (usb_host_ehci_instance_t *)((usb_host_instance_t *)hostHandle)->controllerHandle;

#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))

#if (defined(FSL_FEATURE_SOC_USBNC_COUNT) && (FSL_FEATURE_SOC_USBNC_COUNT > 0U))
    if (ehciInstance->registerNcBase->USB_OTGn_CTRL & USBNC_USB_OTGn_CTRL_WIE_MASK)
    {
        usb_host_instance_t *hostPointer = (usb_host_instance_t *)ehciInstance->hostHandle;
        ehciInstance->registerNcBase->USB_OTGn_CTRL &= ~USBNC_USB_OTGn_CTRL_WIE_MASK;
        hostPointer->deviceCallback(hostPointer->suspendedDevice, NULL,
                                    kUSB_HostEventDetectResume); /* call host callback function */

        while (!(ehciInstance->registerNcBase->USB_OTGn_PHY_CTRL_0 & USBNC_USB_OTGn_PHY_CTRL_0_UTMI_CLK_VLD_MASK))
        {
        }

        if (ehciInstance->ehciIpBase->PORTSC1 & USBHS_PORTSC1_CCS_MASK)
        {
            USB_HostEhciStartAsync(ehciInstance);
            USB_HostEhciStartPeriodic(ehciInstance);
        }
        ehciInstance->ehciIpBase->USBCMD |= (USBHS_USBCMD_RS_MASK);
        if ((kBus_EhciSuspended == ehciInstance->busSuspendStatus))
        {
            /* ehciInstance->ehciIpBase->PORTSC1 |= USBHS_PORTSC1_FPR_MASK; */
            ehciInstance->busSuspendStatus = kBus_EhciStartResume;
        }
        else
        {
        }
    }
    else
    {
    }
#else
    if (ehciInstance->ehciIpBase->USBGENCTRL & USBHS_USBGENCTRL_WU_IE_MASK)
    {
        usb_host_instance_t *hostPointer = (usb_host_instance_t *)ehciInstance->hostHandle;

        hostPointer->deviceCallback(hostPointer->suspendedDevice, NULL,
                                    kUSB_HostEventDetectResume); /* call host callback function */

        while (!(USBPHY->PLL_SIC & USBPHY_PLL_SIC_PLL_LOCK_MASK))
        {
        }
        ehciInstance->ehciIpBase->USBGENCTRL |= USBHS_USBGENCTRL_WU_INT_CLR_MASK;
        ehciInstance->ehciIpBase->USBGENCTRL &= ~USBHS_USBGENCTRL_WU_IE_MASK;
        if (ehciInstance->ehciIpBase->PORTSC1 & USBHS_PORTSC1_CCS_MASK)
        {
            USB_HostEhciStartAsync(ehciInstance);
            USB_HostEhciStartPeriodic(ehciInstance);
        }
        ehciInstance->ehciIpBase->USBCMD |= (USBHS_USBCMD_RS_MASK);
        if ((kBus_EhciSuspended == ehciInstance->busSuspendStatus))
        {
            ehciInstance->busSuspendStatus = kBus_EhciStartResume;
            /*ehciInstance->ehciIpBase->PORTSC1 |= USBHS_PORTSC1_FPR_MASK; */
        }
        else
        {
        }
    }
    else
    {
    }
#endif /* FSL_FEATURE_SOC_USBNC_COUNT */

#endif /* USB_HOST_CONFIG_LOW_POWER_MODE */

    interruptStatus = ehciInstance->ehciIpBase->USBSTS;
    interruptStatus &= ehciInstance->ehciIpBase->USBINTR;
    while (interruptStatus) /* there are usb interrupts */
    {
        ehciInstance->ehciIpBase->USBSTS = interruptStatus; /* clear interrupt */

        if (interruptStatus & USBHS_USBSTS_SRI_MASK) /* SOF interrupt */
        {
        }

        if (interruptStatus & USBHS_USBSTS_SEI_MASK) /* system error interrupt */
        {
        }

        if ((interruptStatus & USBHS_USBSTS_UI_MASK) ||
            (interruptStatus & USBHS_USBSTS_UEI_MASK)) /* USB interrupt or USB error interrupt */
        {
            USB_OsaEventSet(ehciInstance->taskEventHandle, EHCI_TASK_EVENT_TRANSACTION_DONE);
        }

        if (interruptStatus & USBHS_USBSTS_PCI_MASK) /* port change detect interrupt */
        {
#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
            usb_host_instance_t *hostPointer = (usb_host_instance_t *)ehciInstance->hostHandle;
            if (ehciInstance->ehciIpBase->PORTSC1 & USBHS_PORTSC1_FPR_MASK)
            {
                if (kBus_EhciStartSuspend == ehciInstance->busSuspendStatus)
                {
                    if (ehciInstance->ehciIpBase->PORTSC1 & USBHS_PORTSC1_CCS_MASK)
                    {
                        USB_HostEhciStartAsync(ehciInstance);
                        USB_HostEhciStartPeriodic(ehciInstance);
                    }
                    hostPointer->deviceCallback(hostPointer->suspendedDevice, NULL,
                                                kUSB_HostEventNotSuspended); /* call host callback function */
                    hostPointer->suspendedDevice = NULL;
                    ehciInstance->busSuspendStatus = kBus_EhciIdle;
                    ehciInstance->ehciIpBase->USBINTR &= ~(USBHS_USBINTR_TIE1_MASK);
                }
                else
                {
                }
            }
#endif
            USB_OsaEventSet(ehciInstance->taskEventHandle, EHCI_TASK_EVENT_PORT_CHANGE);
        }

        if (interruptStatus & USBHS_USBSTS_TI0_MASK) /* timer 0 interrupt */
        {
            USB_OsaEventSet(ehciInstance->taskEventHandle, EHCI_TASK_EVENT_TIMER0);
        }

#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
        if (interruptStatus & USBHS_USBSTS_TI1_MASK) /* timer 1 interrupt */
        {
            USB_OsaEventSet(ehciInstance->taskEventHandle, EHCI_TASK_EVENT_TIMER1);
        }
#endif

        interruptStatus = ehciInstance->ehciIpBase->USBSTS;
        interruptStatus &= ehciInstance->ehciIpBase->USBINTR;
    }
}

#endif /* USB_HOST_CONFIG_EHCI */
