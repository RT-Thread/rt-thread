/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016,2019 - 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <usb/include/usb_host_config.h>
#if ((defined USB_HOST_CONFIG_EHCI) && (USB_HOST_CONFIG_EHCI > 0U))
#include "usb_host.h"
#include "usb_host_hci.h"
#include "usb_host_devices.h"
#if ((defined USB_HOST_CONFIG_COMPLIANCE_TEST) && (USB_HOST_CONFIG_COMPLIANCE_TEST))
#include "usb_host_framework.h"
#endif
#include "fsl_device_registers.h"
#include "usb_host_ehci.h"
#if ((defined FSL_FEATURE_SOC_USBPHY_COUNT) && (FSL_FEATURE_SOC_USBPHY_COUNT))
#include <usb/phy/usb_phy.h>
#endif
#if ((defined USB_HOST_CONFIG_COMPLIANCE_TEST) && (USB_HOST_CONFIG_COMPLIANCE_TEST))
#include "usb_host.h"
#endif

//#define USB_GINSTANCE_SIZE (sizeof(usb_host_ehci_instance_t))
//#if defined(__ICCARM__) /* IAR Workbench */
//#pragma location = "usb_heap_section"
//static char ginstance_base[USB_GINSTANCE_SIZE];
//#endif
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if defined(USB_STACK_USE_DEDICATED_RAM) && (USB_STACK_USE_DEDICATED_RAM > 0U)

#error The SOC does not suppoort dedicated RAM case.

#endif

#define USB_HOST_EHCI_BANDWIDTH_DELAY             (3500U)
#define USB_HOST_EHCI_BANDWIDTH_HUB_LS_SETUP      (333U)
#define USB_HOST_EHCI_BANDWIDTH_FRAME_TOTOAL_TIME (900U)

#if ((defined USB_HOST_CONFIG_COMPLIANCE_TEST) && (USB_HOST_CONFIG_COMPLIANCE_TEST))
#define USB_HOST_EHCI_TEST_DESCRIPTOR_LENGTH     (18U)
#define USB_HOST_EHCI_PORTSC_PTC_J_STATE         (0x01U)
#define USB_HOST_EHCI_PORTSC_PTC_K_STATE         (0x02U)
#define USB_HOST_EHCI_PORTSC_PTC_SE0_NAK         (0x03U)
#define USB_HOST_EHCI_PORTSC_PTC_PACKET          (0x04U)
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
                                                      uint16_t frameBandwidths[8]);

/*!
 * @brief compute current allocated HS bandwidth when ehci work as hi-speed host.
 *
 * @param ehciInstance         ehci instance pointer.
 * @param frameIndex      frame index.
 * @param frameBandwidths return frame bandwidth data.
 */
static void USB_HostBandwidthHsHostComputeCurrentHsAll(usb_host_ehci_instance_t *ehciInstance,
                                                       uint16_t frameIndex,
                                                       uint16_t frameBandwidths[8]);

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

static uint8_t usbHostEhciFramListStatus[1] = {0};

USB_RAM_ADDRESS_ALIGNMENT(64) USB_CONTROLLER_DATA static usb_host_ehci_data_t s_UsbHostEhciData1;
#elif (USB_HOST_CONFIG_EHCI == 2U)
USB_RAM_ADDRESS_ALIGNMENT(4096)
USB_CONTROLLER_DATA static uint8_t s_UsbHostEhciFrameList1[USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE * 4];
USB_RAM_ADDRESS_ALIGNMENT(4096)
USB_CONTROLLER_DATA static uint8_t s_UsbHostEhciFrameList2[USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE * 4];
static uint8_t usbHostEhciFramListStatus[2] = {0, 0};

USB_RAM_ADDRESS_ALIGNMENT(64) USB_CONTROLLER_DATA static usb_host_ehci_data_t s_UsbHostEhciData1;
USB_RAM_ADDRESS_ALIGNMENT(64) USB_CONTROLLER_DATA static usb_host_ehci_data_t s_UsbHostEhciData2;
#else
#error "Please increase the instance count."
#endif
#define USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE (1024U)
#define USB_HOST_EHCI_MAX_MICRFRAME_VALUE    ((USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE << 3U) - 1U)

static uint8_t s_SlotMaxBandwidth[8]   = {125, 125, 125, 125, 125, 125, 50, 0};
static uint8_t s_SlotMaxBandwidthHs[8] = {100, 100, 100, 100, 100, 100, 100, 100};

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
static void *USB_EhciNCGetBase(uint8_t controllerId)
{
    void *usbNCBase = NULL;
#if ((defined FSL_FEATURE_SOC_USBNC_COUNT) && (FSL_FEATURE_SOC_USBNC_COUNT > 0U))
    uint32_t instance;
    uint32_t newinstance       = 0;
    uint32_t usbnc_base_temp[] = USBNC_BASE_ADDRS;
    uint32_t usbnc_base[]      = USBNC_BASE_ADDRS;

    if (controllerId < (uint8_t)kUSB_ControllerEhci0)
    {
        return NULL;
    }

    controllerId = controllerId - (uint8_t)kUSB_ControllerEhci0;

    for (instance = 0; instance < (sizeof(usbnc_base_temp) / sizeof(usbnc_base_temp[0])); instance++)
    {
        if (usbnc_base_temp[instance] != 0U)
        {
            usbnc_base[newinstance++] = usbnc_base_temp[instance];
        }
    }
    if (controllerId > newinstance)
    {
        return NULL;
    }

    usbNCBase = (void *)(uint8_t *)usbnc_base[controllerId];
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

    getDescriptorParam.descriptorLength  = sizeof(usb_descriptor_device_t);
    getDescriptorParam.descriptorLength  = 18;
    getDescriptorParam.descriptorBuffer  = (uint8_t *)&deviceInstance->deviceDescriptor;
    getDescriptorParam.descriptorType    = USB_DESCRIPTOR_TYPE_DEVICE;
    getDescriptorParam.descriptorIndex   = 0;
    getDescriptorParam.languageId        = 0;
    transfer->callbackFn                 = USB_HostEhciTestCallback;
    transfer->callbackParam              = ehciInstance->hostHandle;
    transfer->setupPacket->bmRequestType = USB_REQUEST_TYPE_DIR_IN;
    transfer->setupPacket->bRequest      = USB_REQUEST_STANDARD_GET_DESCRIPTOR;
    transfer->setupPacket->wIndex        = 0;
    transfer->setupPacket->wLength       = 0;
    transfer->setupPacket->wValue        = 0;
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
            qtdPointer                 = ehciInstance->ehciQtdHead;
            ehciInstance->ehciQtdHead  = (usb_host_ehci_qtd_t *)qtdPointer->nextQtdPointer;
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
        dataAddress                    = (uint32_t)(transfer->setupPacket);
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

            dataAddress                    = (uint32_t)(transfer->transferBuffer);
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
        transfer->next                 = NULL;
        vltQhPointer->ehciTransferHead = vltQhPointer->ehciTransferTail = transfer;
    }
    else
    {
        transfer->next                       = NULL;
        vltQhPointer->ehciTransferTail->next = transfer;
        vltQhPointer->ehciTransferTail       = transfer;
    }

    USB_HostEhciLock();
    /* link qtd to qh (link to end) */
    entryPointer = &(vltQhPointer->nextQtdPointer);
    dataAddress  = *entryPointer; /* dataAddress variable means entry value here */
    while ((dataAddress) && (!(dataAddress & EHCI_HOST_T_INVALID_VALUE)))
    {
        entryPointer = (volatile uint32_t *)dataAddress;
        dataAddress  = *entryPointer;
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
    transfer->callbackFn                 = USB_HostEhciTestCallback;
    transfer->callbackParam              = ehciInstance->hostHandle;
    transfer->setupPacket->bmRequestType = USB_REQUEST_TYPE_DIR_IN;
    transfer->setupPacket->bRequest      = USB_REQUEST_STANDARD_GET_DESCRIPTOR;
    transfer->setupPacket->wLength       = USB_SHORT_TO_LITTLE_ENDIAN(USB_HOST_EHCI_TEST_DESCRIPTOR_LENGTH);
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
    transfer->callbackFn     = USB_HostEhciTestCallback;
    transfer->callbackParam  = ehciInstance->hostHandle;
    transfer->transferBuffer = buffer;
    transfer->transferLength = USB_HOST_EHCI_TEST_DESCRIPTOR_LENGTH;
    USB_HostEhciSingleStepQtdListInit(ehciInstance, (usb_host_ehci_pipe_t *)(deviceInstance->controlPipe), transfer, 2);

    if (USB_HostMallocTransfer(ehciInstance->hostHandle, &transfer) != kStatus_USB_Success)
    {
        return;
    }
    transfer->callbackFn     = USB_HostEhciTestCallback;
    transfer->callbackParam  = ehciInstance->hostHandle;
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

static void USB_HostEhciTestModeInit(usb_device_handle deviceHandle)
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
            /*no action */
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
    uint32_t result = (3167U + ((1000U * dataLength) * 7U * 8U / 6U)) / 1000U;

    if (pipeType == USB_ENDPOINT_ISOCHRONOUS) /* iso */
    {
        if (speed == USB_SPEED_HIGH)
        {
            result = 38U * 8U * 2083U + 2083U * result + USB_HOST_EHCI_BANDWIDTH_DELAY;
        }
        else if (speed == USB_SPEED_FULL)
        {
            if (direction == USB_IN)
            {
                result = 7268000U + 83540U * result + USB_HOST_EHCI_BANDWIDTH_DELAY;
            }
            else
            {
                result = 6265000U + 83540U * result + USB_HOST_EHCI_BANDWIDTH_DELAY;
            }
        }
        else
        {
            /*no action*/
        }
    }
    else /* interrupt */
    {
        if (speed == USB_SPEED_HIGH)
        {
            result = 55U * 8U * 2083U + 2083U * result + USB_HOST_EHCI_BANDWIDTH_DELAY;
        }
        else if (speed == USB_SPEED_FULL)
        {
            result = 9107000U + 83540U * result + USB_HOST_EHCI_BANDWIDTH_DELAY;
        }
        else if (speed == USB_SPEED_LOW)
        {
            if (direction == USB_IN)
            {
                result = 64060000U + 2000U * USB_HOST_EHCI_BANDWIDTH_HUB_LS_SETUP + 676670U * result +
                         USB_HOST_EHCI_BANDWIDTH_DELAY;
            }
            else
            {
                result = 6265000U + 83540U * result + USB_HOST_EHCI_BANDWIDTH_DELAY;
            }
        }
        else
        {
            /*no action*/
        }
    }

    result /= 1000000U;
    if (result == 0U)
    {
        result = 1U;
    }

    return result;
}

static void USB_HostBandwidthFslsHostComputeCurrent(usb_host_ehci_instance_t *ehciInstance,
                                                    uint16_t frameIndex,
                                                    uint16_t *frameBandwidth)
{
    usb_host_ehci_pipe_t *ehciPipePointer;
    void *temp;
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
                (0U == ((uint32_t)((uint32_t)frameIndex - ehciPipePointer->startFrame) &
                        ((uint32_t)ehciPipePointer->pipeCommon.interval - 1U))))
            {
                *frameBandwidth += ehciPipePointer->dataTime;
            }
        }
        temp            = (void *)ehciPipePointer->pipeCommon.next;
        ehciPipePointer = (usb_host_ehci_pipe_t *)temp;
    }
}

static void USB_HostBandwidthHsHostComputeCurrentFsls(usb_host_ehci_instance_t *ehciInstance,
                                                      uint32_t hubNumber,
                                                      uint16_t frameIndex,
                                                      uint16_t frameBandwidths[8])
{
    usb_host_ehci_pipe_t *ehciPipePointer;
    uint8_t index;
    uint32_t deviceInfo = 0U;
    void *temp;

    for (index = 0; index < 8U; ++index)
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
            (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                         (uint32_t)kUSB_HostGetDeviceHSHubNumber, &deviceInfo);
            if (deviceInfo != hubNumber)
            {
                temp            = (void *)ehciPipePointer->pipeCommon.next;
                ehciPipePointer = (usb_host_ehci_pipe_t *)temp;
                continue;
            }
            (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                         (uint32_t)kUSB_HostGetDeviceSpeed, &deviceInfo);
            if (deviceInfo == USB_SPEED_HIGH)
            {
                temp            = (void *)ehciPipePointer->pipeCommon.next;
                ehciPipePointer = (usb_host_ehci_pipe_t *)temp;
                continue;
            }

            /* does pipe allocate bandwidth in frameIndex frame? note: interval is power of 2. */
            if ((frameIndex >= ehciPipePointer->startFrame) &&
                (0U == ((uint32_t)((uint32_t)frameIndex - ehciPipePointer->startFrame) &
                        ((uint32_t)ehciPipePointer->pipeCommon.interval - 1U))))
            {
                if (ehciPipePointer->pipeCommon.pipeType ==
                    USB_ENDPOINT_ISOCHRONOUS) /* iso bandwidth is allocated once */
                {
                    frameBandwidths[ehciPipePointer->startUframe + 1U] += ehciPipePointer->dataTime;
                }
                else /* iso bandwidth is allocated three times */
                {
                    frameBandwidths[ehciPipePointer->startUframe + 1U] += ehciPipePointer->dataTime;
                    frameBandwidths[ehciPipePointer->startUframe + 2U] += ehciPipePointer->dataTime;
                    frameBandwidths[ehciPipePointer->startUframe + 3U] += ehciPipePointer->dataTime;
                }
            }
        }
        temp            = (void *)ehciPipePointer->pipeCommon.next;
        ehciPipePointer = (usb_host_ehci_pipe_t *)temp;
    }

    for (index = 0; index < 7U; ++index) /*  */
    {
        if (frameBandwidths[index] > s_SlotMaxBandwidth[index])
        {
            frameBandwidths[index + 1U] += (frameBandwidths[index] - s_SlotMaxBandwidth[index]);
            frameBandwidths[index] = s_SlotMaxBandwidth[index];
        }
    }
}

static void USB_HostBandwidthHsHostComputeCurrentHsAll(usb_host_ehci_instance_t *ehciInstance,
                                                       uint16_t frameIndex,
                                                       uint16_t frameBandwidths[8])
{
    usb_host_ehci_pipe_t *ehciPipePointer;
    uint16_t index;
    uint32_t deviceInfo = 0U;
    uint16_t frameInterval;
    void *temp;
    for (index = 0; index < 8U; ++index)
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
            (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                         (uint32_t)kUSB_HostGetDeviceSpeed, &deviceInfo);
            if (deviceInfo == USB_SPEED_HIGH) /* high-speed data bandwidth */
            {
                /* frameInterval means micro-frame here */
                if (frameIndex >= ehciPipePointer->startFrame)
                {
                    if ((frameInterval > 8U) &&
                        (frameIndex * 8U - ehciPipePointer->startFrame * 8U >= ehciPipePointer->startUframe))
                    {
                        if (0U == ((((uint32_t)frameIndex) * 8U - ehciPipePointer->startFrame * 8U -
                                    ehciPipePointer->startUframe) &
                                   ((uint32_t)frameInterval - 1U)))
                        {
                            frameBandwidths[ehciPipePointer->startUframe] += ehciPipePointer->dataTime;
                        }
                    }
                    else
                    {
                        for (index = ehciPipePointer->startUframe; index < 8U; index += frameInterval)
                        {
                            frameBandwidths[index] += ehciPipePointer->dataTime;
                        }
                    }
                }
            }
            else /* full-speed split bandwidth */
            {
                if ((frameIndex >= ehciPipePointer->startFrame) &&
                    (0U == ((uint32_t)((uint32_t)frameIndex - ehciPipePointer->startFrame) &
                            (uint32_t)((uint32_t)frameInterval - 1U))))
                {
                    for (index = 0; index < 8U; ++index)
                    {
                        if (0U != ((uint32_t)(ehciPipePointer->uframeSmask) &
                                   (uint32_t)(0x01UL << index))) /* start-split micro-frames */
                        {
                            frameBandwidths[index] += ehciPipePointer->startSplitTime;
                        }
                        if (0U != ((uint32_t)(ehciPipePointer->uframeCmask) &
                                   (uint32_t)(0x01UL << index))) /* complete-split micro-frames */
                        {
                            frameBandwidths[index] += ehciPipePointer->completeSplitTime;
                        }
                    }
                }
            }
        }
        temp            = (void *)ehciPipePointer->pipeCommon.next;
        ehciPipePointer = (usb_host_ehci_pipe_t *)temp;
    }

#if 0
    for (index = 0; index < 7; ++index) /*  */
    {
        if (frameBandwidths[index] > s_SlotMaxBandwidthHs[index])
        {
            frameBandwidths[index + 1] += (frameBandwidths[index] - s_SlotMaxBandwidthHs[index]);
            frameBandwidths[index] = s_SlotMaxBandwidthHs[index];
        }
    }
#endif
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
    uint16_t frameTimes[8];

    frameIndex = 0;
    for (uint8_t i = 0; i < 8U; ++i)
    {
        frameTimes[i] = 0U;
    }
    USB_HostBandwidthHsHostComputeCurrentHsAll(
        ehciInstance, frameIndex, frameTimes); /* compute the allocated bandwidths in the frameIndex frame */
    for (uframeIntervalIndex = 0; (uframeIntervalIndex < uframeInterval); ++uframeIntervalIndex) /* start micro-frame */
    {
        /* for all the micro-frame in interval uframeInterval */
        for (uframeIndex = uframeIntervalIndex; uframeIndex < (USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE * 8U);
             uframeIndex += uframeInterval)
        {
            if (frameIndex != (uframeIndex >> 3))
            {
                frameIndex = (uframeIndex >> 3);
                USB_HostBandwidthHsHostComputeCurrentHsAll(
                    ehciInstance, frameIndex,
                    frameTimes); /* compute the allocated bandwidths in the new frameIndex frame */
            }
            if (frameTimes[uframeIndex & 0x0007U] + timeData >
                s_SlotMaxBandwidthHs[(uframeIndex & 0x0007U)]) /* micro-frame has enough idle bandwidth? */
            {
                break; /* fail */
            }
        }
        if (uframeIndex >= (USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE * 8U)) /* success? */
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
    uint32_t deviceInfo          = 0;
    uint32_t hubNumber           = 0;
    uint16_t uframeIntervalIndex = 0;
    uint16_t frameIntervalIndex  = 0;
    uint16_t frameIndex;
    uint16_t timeCompleteSplit;
    uint16_t timeStartSplit;
    uint32_t timeData;
    uint8_t SsCsNumber = 0;
    uint16_t frameInterval;
    uint16_t frameTimes[8];
    uint8_t allocateOk = 1;
    uint16_t index;

    for (uint8_t i = 0; i < 8U; ++i)
    {
        frameTimes[i] = 0U;
    }
    (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                 (uint32_t)kUSB_HostGetDeviceSpeed, &deviceInfo);

    timeData = USB_HostBandwidthComputeTime(
        (uint8_t)deviceInfo, USB_ENDPOINT_ISOCHRONOUS, ehciPipePointer->pipeCommon.direction,
        (((uint32_t)ehciPipePointer->pipeCommon.maxPacketSize) * ehciPipePointer->pipeCommon.numberPerUframe));
    /* pipe is high-speed */
    if (deviceInfo == USB_SPEED_HIGH)
    {
        uframeIntervalIndex = 0;
        status              = USB_HostBandwidthHsHostAllocateHsCommon(ehciInstance, ehciPipePointer->uframeInterval,
                                                         (uint16_t)timeData, &uframeIntervalIndex);
        if (status == kStatus_USB_Success)
        {
            ehciPipePointer->startFrame  = (uframeIntervalIndex / 8U);
            ehciPipePointer->startUframe = (uint8_t)(uframeIntervalIndex & 0x0007U);
            ehciPipePointer->dataTime    = (uint16_t)timeData;

            return kStatus_USB_Success;
        }
    }
    else /* pipe is full-speed or low-speed */
    {
        (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                     (uint32_t)kUSB_HostGetHubThinkTime,
                                                     &deviceInfo); /* deviceInfo variable means hub think time */
        timeData += (deviceInfo * 7U / (6U * 12U));
        (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                     (uint32_t)kUSB_HostGetDeviceHSHubNumber, &hubNumber);
        frameInterval = ehciPipePointer->pipeCommon.interval;

        /* compute start-split and complete-split bandwidth */
        if (ehciPipePointer->pipeCommon.direction == USB_OUT)
        {
            timeStartSplit = (uint16_t)USB_HostBandwidthComputeTime(USB_SPEED_HIGH, USB_ENDPOINT_ISOCHRONOUS, USB_OUT,
                                                                    ehciPipePointer->pipeCommon.maxPacketSize);
            timeCompleteSplit = 0;
        }
        else
        {
            timeStartSplit =
                (uint16_t)USB_HostBandwidthComputeTime(USB_SPEED_HIGH, USB_ENDPOINT_ISOCHRONOUS, USB_IN, 1);
            timeCompleteSplit = (uint16_t)USB_HostBandwidthComputeTime(USB_SPEED_HIGH, USB_ENDPOINT_ISOCHRONOUS, USB_IN,
                                                                       ehciPipePointer->pipeCommon.maxPacketSize);
        }
        /* note: bandwidth must put in one frame */
        for (uframeIntervalIndex = 0U; uframeIntervalIndex <= 5U; ++uframeIntervalIndex) /* uframe interval */
        {
            for (frameIntervalIndex = 0U; frameIntervalIndex < frameInterval; ++frameIntervalIndex) /* frame interval */
            {
                allocateOk = 1;
                for (frameIndex = frameIntervalIndex; frameIndex < USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE;
                     frameIndex += frameInterval) /* check all the frames */
                {
                    /* compute start-split and complete-split number */
                    SsCsNumber = (uint8_t)((ehciPipePointer->pipeCommon.maxPacketSize + 187U) /
                                           188U); /* ss number for iso out; cs number for iso in */
                    if (ehciPipePointer->pipeCommon.direction == USB_OUT) /* ISO OUT */
                    {
                        if (uframeIntervalIndex + SsCsNumber > 8U)
                        {
                            allocateOk = 0U;
                        }
                    }
                    else
                    {
                        if (uframeIntervalIndex + 2U + SsCsNumber >
                            8U) /* ISO IN: there are two micro-frame interval between start-split and complete-split */
                        {
                            allocateOk = 0U;
                        }
                    }
                    if (0U != allocateOk)
                    {
                        /* allocate start-split and complete-split bandwidth */
                        USB_HostBandwidthHsHostComputeCurrentHsAll(ehciInstance, frameIndex, frameTimes);
                        if (ehciPipePointer->pipeCommon.direction == USB_OUT) /* ISO OUT */
                        {
                            index = uframeIntervalIndex;
                            for (; index < (uframeIntervalIndex + SsCsNumber); ++index)
                            {
                                if (frameTimes[index] + timeStartSplit > s_SlotMaxBandwidthHs[index])
                                {
                                    allocateOk = 0U;
                                    break;
                                }
                            }
                        }
                        else /* ISO IN */
                        {
                            index = uframeIntervalIndex;
                            if (frameTimes[index] + timeStartSplit > s_SlotMaxBandwidthHs[index])
                            {
                                allocateOk = 0U;
                            }
                            if (0U != allocateOk)
                            {
                                index =
                                    uframeIntervalIndex +
                                    2U; /* there are two micro-frames interval between start-split and complete-split */
                                for (; index < (uframeIntervalIndex + 2U + SsCsNumber); ++index)
                                {
                                    if (frameTimes[index] + timeCompleteSplit > s_SlotMaxBandwidthHs[index])
                                    {
                                        allocateOk = 0U;
                                        break;
                                    }
                                }
                            }
                        }
                    }

                    /* allocate data bandwidth */
                    if (0U != allocateOk)
                    {
                        USB_HostBandwidthHsHostComputeCurrentFsls(ehciInstance, hubNumber, frameIndex, frameTimes);
                        index = uframeIntervalIndex + 1U; /* timeData bandwidth start position */
                        /* iso must occupy all the uframe bandwidth */
                        {
                            deviceInfo = timeData; /* note: deviceInfo variable means bandwidth here */
                            while ((index < 8U) && (deviceInfo > s_SlotMaxBandwidth[index]))
                            {
                                if (frameTimes[index] > 0U)
                                {
                                    allocateOk = 0U;
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
                    if (0U != allocateOk)
                    {
                        /* data bandwidth can be put in the frame? */
                        index = uframeIntervalIndex + 1U; /* timeData bandwidth start position */
                        frameTimes[index] += (uint16_t)timeData;
                        for (; index < 7U; ++index)
                        {
                            if (frameTimes[index] > s_SlotMaxBandwidth[index])
                            {
                                frameTimes[index + 1U] += (frameTimes[index] - s_SlotMaxBandwidth[index]);
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

                    if (0U != allocateOk)
                    {
                        break;
                    }
                }
                if (0U != allocateOk)
                {
                    break;
                }
            }
            if (0U != allocateOk)
            {
                break;
            }
        }

        if (0U != allocateOk)
        {
            ehciPipePointer->startFrame        = frameIntervalIndex;
            ehciPipePointer->startUframe       = (uint8_t)uframeIntervalIndex;
            ehciPipePointer->dataTime          = (uint16_t)timeData;
            ehciPipePointer->startSplitTime    = timeStartSplit;
            ehciPipePointer->completeSplitTime = timeCompleteSplit;
            if (ehciPipePointer->pipeCommon.direction == USB_OUT)
            {
                index = uframeIntervalIndex;
                for (; index < (uframeIntervalIndex + SsCsNumber); ++index)
                {
                    ehciPipePointer->uframeSmask = ehciPipePointer->uframeSmask | (uint8_t)(0x01UL << index);
                }
            }
            else
            {
                index                        = uframeIntervalIndex;
                ehciPipePointer->uframeSmask = ehciPipePointer->uframeSmask | (uint8_t)(0x01UL << index);
                index                        = uframeIntervalIndex + 2U;
                for (; index < (uframeIntervalIndex + 2U + SsCsNumber); ++index)
                {
                    ehciPipePointer->uframeCmask = ehciPipePointer->uframeCmask | (uint8_t)(0x01UL << index);
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
    uint32_t deviceInfo          = 0;
    uint32_t hubNumber           = 0;
    uint16_t uframeIntervalIndex = 0;
    uint16_t frameIntervalIndex  = 0;
    uint16_t frameIndex;
    uint16_t timeCompleteSplit;
    uint16_t timeStartSplit;
    uint32_t timeData;
    uint8_t SsCsNumber;
    uint16_t frameInterval;
    uint16_t frameTimes[8];
    uint8_t allocateOk = 1;
    uint8_t index;

    for (uint8_t i = 0; i < 8U; ++i)
    {
        frameTimes[i] = 0U;
    }
    (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                 (uint32_t)kUSB_HostGetDeviceSpeed, &deviceInfo);

    timeData = USB_HostBandwidthComputeTime(
        (uint8_t)deviceInfo, USB_ENDPOINT_INTERRUPT, ehciPipePointer->pipeCommon.direction,
        (uint32_t)ehciPipePointer->pipeCommon.maxPacketSize * ehciPipePointer->pipeCommon.numberPerUframe);
    /* pipe is high-speed */
    if (deviceInfo == USB_SPEED_HIGH)
    {
        uframeIntervalIndex = 0;
        status              = USB_HostBandwidthHsHostAllocateHsCommon(ehciInstance, ehciPipePointer->uframeInterval,
                                                         (uint16_t)timeData, &uframeIntervalIndex);
        if (status == kStatus_USB_Success)
        {
            ehciPipePointer->startFrame  = (uframeIntervalIndex / 8U);
            ehciPipePointer->startUframe = (uint8_t)(uframeIntervalIndex & 0x0007U);
            /* for HS interrupt start transaction position */
            if (ehciPipePointer->uframeInterval >= 8U)
            {
                ehciPipePointer->uframeSmask = (0x01U << ehciPipePointer->startUframe);
            }
            else
            {
                ehciPipePointer->uframeSmask = 0x00U;
                for (index = ehciPipePointer->startUframe; index < 8U;
                     index += (uint8_t)ehciPipePointer->uframeInterval)
                {
                    ehciPipePointer->uframeSmask |= (0x01U << index);
                }
            }
            ehciPipePointer->dataTime = (uint16_t)timeData;

            return kStatus_USB_Success;
        }
    }
    else /* pipe is full-speed or low-speed */
    {
        (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                     (uint32_t)kUSB_HostGetHubThinkTime, &deviceInfo);
        timeData += (deviceInfo * 7U / (6U * 12U));
        (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                     (uint32_t)kUSB_HostGetDeviceHSHubNumber, &hubNumber);
        frameInterval = ehciPipePointer->pipeCommon.interval;
        SsCsNumber    = 3U; /* complete split number */

        /* compute start-split and complete-split bandwidth */
        if (ehciPipePointer->pipeCommon.direction == USB_OUT)
        {
            timeStartSplit = (uint16_t)USB_HostBandwidthComputeTime(USB_SPEED_HIGH, USB_ENDPOINT_INTERRUPT, USB_OUT,
                                                                    ehciPipePointer->pipeCommon.maxPacketSize);
            timeStartSplit +=
                (uint16_t)USB_HostBandwidthComputeTime(USB_SPEED_HIGH, USB_ENDPOINT_INTERRUPT, USB_OUT, 1U);
            timeCompleteSplit =
                (uint16_t)USB_HostBandwidthComputeTime(USB_SPEED_HIGH, USB_ENDPOINT_INTERRUPT, USB_OUT, 0U);
        }
        else
        {
            timeStartSplit = (uint16_t)USB_HostBandwidthComputeTime(USB_SPEED_HIGH, USB_ENDPOINT_INTERRUPT, USB_IN, 1U);
            timeCompleteSplit = (uint16_t)USB_HostBandwidthComputeTime(USB_SPEED_HIGH, USB_ENDPOINT_INTERRUPT, USB_IN,
                                                                       ehciPipePointer->pipeCommon.maxPacketSize);
            timeCompleteSplit +=
                (uint16_t)USB_HostBandwidthComputeTime(USB_SPEED_HIGH, USB_ENDPOINT_INTERRUPT, USB_IN, 0U);
        }
        /* note: bandwidth must put in one frame */
        for (uframeIntervalIndex = 0U; uframeIntervalIndex <= 4U; ++uframeIntervalIndex) /* uframe interval */
        {
            for (frameIntervalIndex = 0U; frameIntervalIndex < frameInterval; ++frameIntervalIndex) /* frame interval */
            {
                allocateOk = 1U;
                for (frameIndex = frameIntervalIndex; frameIndex < USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE;
                     frameIndex += frameInterval) /* check all the frames */
                {
                    /* allocate data bandwidth */
                    USB_HostBandwidthHsHostComputeCurrentFsls(ehciInstance, hubNumber, frameIndex, frameTimes);
                    index = (uint8_t)(uframeIntervalIndex + 1U);
                    for (; index <= (uframeIntervalIndex + 3U); ++index) /* data bandwidth number is 3.
                                                                             uframeIntervalIndex don't exceed 4, so
                                                                             index cannot exceed 7 */
                    {
                        if (frameTimes[index] + timeData > s_SlotMaxBandwidth[index])
                        {
                            allocateOk = 0;
                            break;
                        }
                    }

                    if (0U != allocateOk)
                    {
                        USB_HostBandwidthHsHostComputeCurrentHsAll(ehciInstance, frameIndex, frameTimes);
                        /* allocate start_split bandwidth */
                        if (frameTimes[uframeIntervalIndex] + timeStartSplit >
                            s_SlotMaxBandwidthHs[uframeIntervalIndex])
                        {
                            allocateOk = 0U;
                        }
                        if (0U != allocateOk)
                        {
                            /* allocate complete_split bandwidth */
                            index = (uint8_t)uframeIntervalIndex + 2U;
                            /* complete-split number is normal 3. When uframeIntervalIndex is 4, complete-split number
                             * is 2. */
                            for (; (index <= (uframeIntervalIndex + 1U + SsCsNumber)) && (index < 8U); ++index)
                            {
                                if (frameTimes[index] + timeCompleteSplit > s_SlotMaxBandwidthHs[index])
                                {
                                    allocateOk = 0U;
                                    break;
                                }
                            }
                        }
                    }

                    if (0U == allocateOk)
                    {
                        break; /* allocate fail */
                    }
                }
                if (0U != allocateOk)
                {
                    break;
                }
            }
            if (0U != allocateOk)
            {
                break;
            }
        }

        if (0U != allocateOk)
        {
            ehciPipePointer->startFrame  = frameIntervalIndex;
            ehciPipePointer->startUframe = (uint8_t)uframeIntervalIndex;
            ehciPipePointer->uframeSmask = (0x01u << ehciPipePointer->startUframe);
            ehciPipePointer->uframeCmask = 0u;
            index                        = (uint8_t)uframeIntervalIndex + 2u;
            for (; (index <= (uframeIntervalIndex + 1u + SsCsNumber)) && (index < 8u); ++index)
            {
                ehciPipePointer->uframeCmask = ehciPipePointer->uframeCmask | (0x01U << index);
            }
            ehciPipePointer->dataTime          = (uint16_t)timeData;
            ehciPipePointer->startSplitTime    = timeStartSplit;
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
    uint32_t speed    = 0;
    uint16_t uframeIntervalIndex;
    uint16_t frameIndex;
    uint16_t frameInterval;
    uint16_t frameTime;

    (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                 (uint32_t)kUSB_HostGetHubThinkTime, &FslsTime);
    FslsTime += (FslsTime * 7U / (6U * 12U));
    (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                 (uint32_t)kUSB_HostGetDeviceSpeed, &speed);
    FslsTime = FslsTime + USB_HostBandwidthComputeTime((uint8_t)speed, ehciPipePointer->pipeCommon.pipeType,
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
        ehciPipePointer->startFrame  = (uframeIntervalIndex >> 3);
        ehciPipePointer->startUframe = (uint8_t)(uframeIntervalIndex & 0x0007U);
        ehciPipePointer->uframeSmask = 0; /* useless */
        ehciPipePointer->uframeCmask = 0;
        ehciPipePointer->dataTime    = (uint16_t)FslsTime;

        return kStatus_USB_Success;
    }

    return kStatus_USB_BandwidthFail;
}

static uint8_t USB_HostEhciGet2PowerValue(uint8_t value)
{
    if ((value == 0U) || (value == 1U))
    {
        return value;
    }
    if (0U != (value & 0xf0U))
    {
        if (0U != (value & 0x80U))
        {
            return 128U;
        }
        else if (0U != (value & 0x40U))
        {
            return 64U;
        }
        else if (0U != (value & 0x20U))
        {
            return 32U;
        }
        else
        {
            return 16U;
        }
    }
    else
    {
        if (0U != (value & 0x08U))
        {
            return 8U;
        }
        else if (0U != (value & 0x04U))
        {
            return 4U;
        }
        else if (0U != (value & 0x02U))
        {
            return 2U;
        }
        else
        {
            return 1U;
        }
    }
}

static void USB_HostEhciZeroMem(uint32_t *buffer, uint32_t length)
{
    /* note: the zero unit is uint32_t */
    while (0U != length)
    {
        length--;
        *buffer = 0;
        buffer++;
    }
}

static void USB_HostEhciDelay(USBHS_Type *ehciIpBase, uint32_t ms)
{
    /* note: the max delay time cannot exceed half of max value (0x4000) */
    uint32_t sofStart;
    uint32_t SofEnd;
    uint32_t distance;

    sofStart = (ehciIpBase->FRINDEX & EHCI_MAX_UFRAME_VALUE);

    do
    {
        SofEnd   = (ehciIpBase->FRINDEX & EHCI_MAX_UFRAME_VALUE);
        distance = (SofEnd + EHCI_MAX_UFRAME_VALUE + 1U - sofStart);
    } while ((distance & EHCI_MAX_UFRAME_VALUE) < (ms * 8U)); /* compute the distance between sofStart and SofEnd */
}

static void USB_HostEhciStartAsync(usb_host_ehci_instance_t *ehciInstance)
{
    uint32_t stateSync;

    if (0U == (ehciInstance->ehciIpBase->USBSTS & USBHS_USBSTS_AS_MASK))
    {
        /* the status must be same when change USBCMD->ASE */
        do
        {
            stateSync = ((ehciInstance->ehciIpBase->USBSTS & USBHS_USBSTS_AS_MASK) |
                         (ehciInstance->ehciIpBase->USBCMD & USBHS_USBCMD_ASE_MASK));
        } while ((stateSync == USBHS_USBSTS_AS_MASK) || (stateSync == USBHS_USBCMD_ASE_MASK));

        ehciInstance->ehciIpBase->ASYNCLISTADDR = (uint32_t)(ehciInstance->shedFirstQh);
        ehciInstance->ehciIpBase->USBCMD |= USBHS_USBCMD_ASE_MASK;
        while (0U == (ehciInstance->ehciIpBase->USBSTS & USBHS_USBSTS_AS_MASK))
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
    while (0U != (ehciInstance->ehciIpBase->USBSTS & USBHS_USBSTS_AS_MASK))
    {
    }
}

static void USB_HostEhciStartPeriodic(usb_host_ehci_instance_t *ehciInstance)
{
    uint32_t stateSync;

    if (0U == (ehciInstance->ehciIpBase->USBSTS & USBHS_USBSTS_PS_MASK))
    {
        /* the status must be same when change USBCMD->PSE */
        do
        {
            stateSync = ((ehciInstance->ehciIpBase->USBSTS & USBHS_USBSTS_PS_MASK) |
                         (ehciInstance->ehciIpBase->USBCMD & USBHS_USBCMD_PSE_MASK));
        } while ((stateSync == USBHS_USBSTS_PS_MASK) || (stateSync == USBHS_USBCMD_PSE_MASK));
        ehciInstance->ehciIpBase->PERIODICLISTBASE = (uint32_t)(ehciInstance->ehciFrameList);
        if (0U == (ehciInstance->ehciIpBase->USBCMD & USBHS_USBCMD_PSE_MASK))
        {
            ehciInstance->ehciIpBase->USBCMD |= USBHS_USBCMD_PSE_MASK; /* start periodic schedule */
        }
        while (0U == (ehciInstance->ehciIpBase->USBSTS & USBHS_USBSTS_PS_MASK))
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
    while (0U != (ehciInstance->ehciIpBase->USBSTS & USBHS_USBSTS_PS_MASK))
    {
    }
}

static usb_status_t USB_HostEhciQhQtdListInit(usb_host_ehci_instance_t *ehciInstance,
                                              usb_host_ehci_pipe_t *ehciPipePointer,
                                              usb_host_transfer_t *transfer)
{
    volatile usb_host_ehci_qh_t *vltQhPointer;
    usb_host_ehci_qtd_t *qtdPointer     = NULL;
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
        if (transfer->transferLength == 0U)
        {
            qtdNumber = 2U;
        }
        else
        {
            qtdNumber = 3U;
        }
    }
    else
    {
        qtdNumber = (((transfer->transferLength) & 0xFFFFC000U) >> 14U) +
                    (0U != ((transfer->transferLength) & 0x00003FFFU) ? 1U : 0U);
        if (0U == qtdNumber)
        {
            qtdNumber = 1U;
        }
    }

    vltQhPointer = (volatile usb_host_ehci_qh_t *)ehciPipePointer->ehciQh;
    /* get qtd list */
    USB_HostEhciLock();
    if (qtdNumber <= ehciInstance->ehciQtdNumber)
    {
        ehciInstance->ehciQtdNumber -= (uint8_t)qtdNumber;
        BaseQtdPointer = ehciInstance->ehciQtdHead;
        qtdPointer     = NULL;
        do
        {
            if (qtdPointer != NULL)
            {
                qtdPointer->nextQtdPointer = (uint32_t)ehciInstance->ehciQtdHead;
            }
            qtdPointer                 = ehciInstance->ehciQtdHead;
            ehciInstance->ehciQtdHead  = (usb_host_ehci_qtd_t *)qtdPointer->nextQtdPointer;
            qtdPointer->nextQtdPointer = 0;
            --qtdNumber;
        } while (0U != qtdNumber);
        if (ehciInstance->ehciQtdNumber == 0U)
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
        qtdPointer                          = BaseQtdPointer;
        qtdPointer->alternateNextQtdPointer = EHCI_HOST_T_INVALID_VALUE;
        /* dt: need set; ioc: 0; C_Page: 0; PID Code: SETUP; Status: Active */
        qtdPointer->transferResults[1] = 0U;
        qtdPointer->transferResults[0] =
            ((0x00000000UL << EHCI_HOST_QTD_DT_SHIFT) | (8UL << EHCI_HOST_QTD_TOTAL_BYTES_SHIFT) |
             (EHCI_HOST_PID_SETUP << EHCI_HOST_QTD_PID_CODE_SHIFT) | (EHCI_HOST_QTD_STATUS_ACTIVE_MASK));
        dataAddress                    = ((uint32_t)transfer->setupPacket);
        qtdPointer->transferResults[1] = dataAddress; /* current offset is set too */
        /* set buffer pointer no matter data length */
        for (index = 0; index < 4U; ++index)
        {
            qtdPointer->bufferPointers[index] = ((dataAddress + ((uint32_t)index + 1U) * 4U * 1024U) & 0xFFFFF000U);
        }

        /* data transaction qtd */
        dataLength = transfer->transferLength;
        if (dataLength != 0U)
        {
            qtdPointer = (usb_host_ehci_qtd_t *)(qtdPointer->nextQtdPointer);

            qtdPointer->alternateNextQtdPointer = EHCI_HOST_T_INVALID_VALUE;
            /* dt: need set; ioc: 0; C_Page: 0; PID Code: IN/OUT; Status: Active */
            qtdPointer->transferResults[1] = 0U;
            if (transfer->direction == USB_OUT)
            {
                qtdPointer->transferResults[0] =
                    ((0x00000001UL << EHCI_HOST_QTD_DT_SHIFT) | (dataLength << EHCI_HOST_QTD_TOTAL_BYTES_SHIFT) |
                     (EHCI_HOST_PID_OUT << EHCI_HOST_QTD_PID_CODE_SHIFT) | (EHCI_HOST_QTD_STATUS_ACTIVE_MASK));
            }
            else
            {
                qtdPointer->transferResults[0] =
                    ((0x00000001U << EHCI_HOST_QTD_DT_SHIFT) | (dataLength << EHCI_HOST_QTD_TOTAL_BYTES_SHIFT) |
                     (EHCI_HOST_PID_IN << EHCI_HOST_QTD_PID_CODE_SHIFT) | (EHCI_HOST_QTD_STATUS_ACTIVE_MASK));
            }

            dataAddress                    = (uint32_t)transfer->transferBuffer;
            qtdPointer->transferResults[1] = dataAddress; /* current offset is set too */
            /* set buffer pointer no matter data length */
            for (index = 0; index < 4U; ++index)
            {
                qtdPointer->bufferPointers[index] = ((dataAddress + ((uint32_t)index + 1U) * 4U * 1024U) & 0xFFFFF000U);
            }
        }

        /* status transaction qtd */
        qtdPointer                          = (usb_host_ehci_qtd_t *)(qtdPointer->nextQtdPointer);
        qtdPointer->alternateNextQtdPointer = EHCI_HOST_T_INVALID_VALUE;
        /* dt: dont care; ioc: 1; C_Page: 0; PID Code: IN/OUT; Status: Active */
        qtdPointer->transferResults[1] = 0;
        if ((dataLength == 0U) || (transfer->direction == USB_OUT))
        {
            qtdPointer->transferResults[0] =
                ((0x00000001UL << EHCI_HOST_QTD_DT_SHIFT) | (EHCI_HOST_PID_IN << EHCI_HOST_QTD_PID_CODE_SHIFT) |
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
        dataAddress = (uint32_t)transfer->transferBuffer;
        qtdPointer  = BaseQtdPointer;
        while (1U == 1U)
        {
            endAddress = dataAddress + (16U * 1024U);
            if (endAddress > (uint32_t)(transfer->transferBuffer + transfer->transferLength))
            {
                endAddress = (uint32_t)(transfer->transferBuffer + transfer->transferLength);
            }

            qtdPointer->alternateNextQtdPointer = EHCI_HOST_T_INVALID_VALUE;
            /* dt: set; ioc: 0; C_Page: 0; PID Code: IN/OUT; Status: Active */
            qtdPointer->transferResults[1] = 0U;
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
            for (index = 0; index < 4U; ++index)
            {
                qtdPointer->bufferPointers[index] = ((dataAddress + ((uint32_t)index + 1U) * 4U * 1024U) & 0xFFFFF000U);
            }
            dataAddress = endAddress; /* for next qtd */

            if (qtdPointer->nextQtdPointer == 0U)
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
        transfer->next                 = NULL;
        vltQhPointer->ehciTransferTail = transfer;
        vltQhPointer->ehciTransferHead = transfer;
    }
    else
    {
        transfer->next                       = NULL;
        vltQhPointer->ehciTransferTail->next = transfer;
        vltQhPointer->ehciTransferTail       = transfer;
    }

    USB_HostEhciLock();
    /* link qtd to qh (link to end) */
    entryPointer = &(vltQhPointer->nextQtdPointer);
    dataAddress  = *entryPointer; /* dataAddress variable means entry value here */
    while ((0U != dataAddress) && (0U == (dataAddress & EHCI_HOST_T_INVALID_VALUE)))
    {
        entryPointer = (volatile uint32_t *)dataAddress;
        dataAddress  = *entryPointer;
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

    ehciQtdEnd->nextQtdPointer = 0U;

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
    if (ehciInstance->ehciQtdNumber == 0U)
    {
        ehciInstance->ehciQtdHead = ehciQtdStart;
        ehciInstance->ehciQtdTail = ehciQtdEnd;
    }
    else
    {
        ehciInstance->ehciQtdTail->nextQtdPointer = (uint32_t)ehciQtdStart;
        ehciInstance->ehciQtdTail                 = ehciQtdEnd;
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
    uint32_t currentQtdPointer;
    uint8_t needStop = 0U;

    vltQhPointer = (volatile usb_host_ehci_qh_t *)ehciPipePointer->ehciQh;

    USB_HostEhciLock(); /* this API is called from APP, the host task may occupy to access the same resource */
    /* remove qtd from qh */
    /*for misra 13.5*/
    currentQtdPointer = vltQhPointer->currentQtdPointer;
    if ((0U == ((uint32_t)vltQhPointer->nextQtdPointer & EHCI_HOST_T_INVALID_VALUE)) ||
        (0U == ((uint32_t)currentQtdPointer & EHCI_HOST_T_INVALID_VALUE)))
    {
        /* need stop async schedule */
        if ((0U == (vltQhPointer->horizontalLinkPointer & EHCI_HOST_T_INVALID_VALUE)) &&
            (ehciPipePointer->pipeCommon.pipeType != USB_ENDPOINT_INTERRUPT))
        {
            needStop = 1U;
        }
        if (0U != needStop)
        {
            USB_HostEhciStopAsync(ehciInstance);
        }
        vltQhPointer->currentQtdPointer = EHCI_HOST_T_INVALID_VALUE;             /* invalid current qtd */
        vltQhPointer->nextQtdPointer    = EHCI_HOST_T_INVALID_VALUE;             /* invalid next qtd */
        vltQhPointer->transferOverlayResults[0] &= (~EHCI_HOST_QTD_STATUS_MASK); /* clear error status */
        if (0U != needStop)
        {
            USB_HostEhciStartAsync(ehciInstance);
        }
    }

    /* remove transfer from the QH transfer list */
    transfer                       = vltQhPointer->ehciTransferHead;
    vltQhPointer->ehciTransferTail = NULL;
    vltQhPointer->ehciTransferHead = NULL;
    USB_HostEhciUnlock();

    /* release qtd  and transfer callback*/
    while (transfer != NULL)
    {
        nextTransfer = transfer->next; /* the transfer is released when call back */
        transfer->transferSofar =
            USB_HostEhciQtdListRelease(ehciInstance, (usb_host_ehci_qtd_t *)(transfer->union1.unitHead),
                                       (usb_host_ehci_qtd_t *)(transfer->union2.unitTail));
        transfer->transferSofar = (transfer->transferLength < transfer->transferSofar) ?
                                      0U :
                                      (transfer->transferLength - transfer->transferSofar);
        /* callback function is different from the current condition */
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
    qhNextQtdValue  = (uint32_t)vltQhPointer->currentQtdPointer;
    qtdPointerEntry = *((uint32_t *)qhNextQtdValue + 2); /* note: qtdPointerEntry means qtd status */
    if ((0U != (qhNextQtdValue & EHCI_HOST_T_INVALID_VALUE)) ||
        (0U == (qtdPointerEntry & EHCI_HOST_QTD_STATUS_ACTIVE_MASK)))
    {
        qhNextQtdValue = (uint32_t)vltQhPointer->nextQtdPointer;
    }
    if (0U == (qhNextQtdValue & EHCI_HOST_T_INVALID_VALUE)) /* there is pending qtd in the qh */
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
        while (1U == 1U)
        {
            /* search qh's qtd list for qtdPointerEntry */
            searchQtdEntryPointer = &qhNextQtdValue;
            while (0U == ((*searchQtdEntryPointer) & EHCI_HOST_T_INVALID_VALUE))
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
    transfer->transferSofar = (transfer->transferLength < transfer->transferSofar) ?
                                  0U :
                                  (transfer->transferLength - transfer->transferSofar);
    /* callback function is different from the current condition */
    transfer->callbackFn(transfer->callbackParam, transfer, kStatus_USB_TransferCancel);

    /* start this qh schedule */
    vltQhPointer->transferOverlayResults[0] &= (~EHCI_HOST_QTD_STATUS_MASK); /* clear error status */
    if ((qhNextQtdValue != 0U) && (0U == (qhNextQtdValue & EHCI_HOST_T_INVALID_VALUE)))
    {
        vltQhPointer->nextQtdPointer = qhNextQtdValue;
    }

    return kStatus_USB_Success;
}

static usb_status_t USB_HostEhciQhInit(usb_host_ehci_instance_t *ehciInstance, usb_host_ehci_pipe_t *ehciPipePointer)
{
    usb_host_ehci_qh_t *qhPointer = NULL;
    uint32_t address              = 0;
    uint32_t speed                = 0;
    uint32_t portNumber           = 0;
    uint32_t hubNumber            = 0;
    ;
    uint32_t controlBits1 = 0U;
    uint32_t controlBits2 = 0U;

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
    USB_HostEhciZeroMem((void *)qhPointer, sizeof(usb_host_ehci_qh_t) / 4U);
    qhPointer->horizontalLinkPointer   = EHCI_HOST_T_INVALID_VALUE;
    qhPointer->currentQtdPointer       = EHCI_HOST_T_INVALID_VALUE;
    qhPointer->nextQtdPointer          = EHCI_HOST_T_INVALID_VALUE;
    qhPointer->alternateNextQtdPointer = EHCI_HOST_T_INVALID_VALUE;
    qhPointer->ehciPipePointer         = ehciPipePointer;
    qhPointer->timeOutLabel            = 0;
    qhPointer->timeOutValue            = USB_HOST_EHCI_CONTROL_BULK_TIME_OUT_VALUE;
    (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                 (uint32_t)kUSB_HostGetDeviceSpeed, &speed);
    /* initialize staticEndpointStates[0] */
    if (ehciPipePointer->pipeCommon.pipeType == USB_ENDPOINT_INTERRUPT)
    {
        /* Software should set the RL field to zero if the queue head is an interrupt endpoint. */
        controlBits1 |= ((0UL << EHCI_HOST_QH_RL_SHIFT) & EHCI_HOST_QH_RL_MASK);
    }
    else
    {
        if (ehciPipePointer->pipeCommon.nakCount >= 16U)
        {
            controlBits1 |= ((15UL << EHCI_HOST_QH_RL_SHIFT) & EHCI_HOST_QH_RL_MASK);
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
            controlBits1 |= (1UL << EHCI_HOST_QH_C_SHIFT);
        }
        controlBits1 |= (1UL << EHCI_HOST_QH_DTC_SHIFT);
    }
    controlBits1 |= ((uint32_t)ehciPipePointer->pipeCommon.maxPacketSize << EHCI_HOST_QH_MAX_PACKET_LENGTH_SHIFT);
    controlBits1 |= (speed << EHCI_HOST_QH_EPS_SHIFT);
    controlBits1 |= ((uint32_t)ehciPipePointer->pipeCommon.endpointAddress << EHCI_HOST_QH_ENDPT_SHIFT);
    (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                 (uint32_t)kUSB_HostGetDeviceAddress, &address);
    controlBits1 |= (address << EHCI_HOST_QH_DEVICE_ADDRESS_SHIFT);
    qhPointer->staticEndpointStates[0] = controlBits1;
    if (speed == USB_SPEED_HIGH)
    {
        controlBits2 |= ((uint32_t)ehciPipePointer->pipeCommon.numberPerUframe << EHCI_HOST_QH_MULT_SHIFT);
    }
    else
    {
        controlBits2 |= (0x00000001UL << EHCI_HOST_QH_MULT_SHIFT);
    }
    /*initialize staticEndpointStates[1] */
    if (speed != USB_SPEED_HIGH)
    {
        (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                     (uint32_t)kUSB_HostGetDeviceHSHubNumber, &hubNumber);
        (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                     (uint32_t)kUSB_HostGetDeviceHSHubPort, &portNumber);
    }
    else
    {
        (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                     (uint32_t)kUSB_HostGetDeviceHubNumber, &hubNumber);
        (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                     (uint32_t)kUSB_HostGetDevicePortNumber, &portNumber);
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
    (void)USB_HostEhciQhQtdListDeinit(ehciInstance, ehciPipePointer);

    /* release QH */
    USB_HostEhciLock();
    qhPointer->horizontalLinkPointer = (uint32_t)ehciInstance->ehciQhList;
    ehciInstance->ehciQhList         = qhPointer;
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
    void *temp;

    /* search for the inserting point by interval */
    temp              = (void *)ehciInstance->ehciFrameList;
    frameEntryPointer = (volatile uint32_t *)(&((uint32_t *)temp)[framePos]);
    while (NULL != frameEntryPointer)
    {
        frameEntryValue = *frameEntryPointer;
        if (0U != (frameEntryValue & EHCI_HOST_T_INVALID_VALUE))
        {
            /* insert into the end */
            *((uint32_t *)entryPointerValue) = EHCI_HOST_T_INVALID_VALUE;
            *frameEntryPointer               = (entryPointerValue | EHCI_HOST_POINTER_TYPE_QH);
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
            *frameEntryPointer               = (entryPointerValue | EHCI_HOST_POINTER_TYPE_QH);
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
    void *temp;
    /* search for the qh/itd/sitd entry */
    temp              = (void *)ehciInstance->ehciFrameList;
    frameEntryPointer = (volatile uint32_t *)(&((uint32_t *)temp)[framePos]);

    while (NULL != frameEntryPointer)
    {
        frameEntryValue = *frameEntryPointer;
        if (0U != (frameEntryValue & EHCI_HOST_T_INVALID_VALUE))
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
    uint32_t shouldLinkFrame;
    uint32_t currentFrame;
    void *temp;

    frameInterval = ((uint32_t)ehciPipePointer->uframeInterval >> 3U);

    if (isoPointer->lastLinkFrame == 0xFFFFU) /* first link */
    {
        currentFrame = ((ehciInstance->ehciIpBase->FRINDEX & USB_HOST_EHCI_MAX_MICRFRAME_VALUE) >> 3U);
        currentFrame = ((uint32_t)(currentFrame + USB_HOST_EHCI_ISO_BOUNCE_FRAME_NUMBER) &
                        (USB_HOST_EHCI_MAX_MICRFRAME_VALUE >> 3U)); /* add USB_HOST_EHCI_ISO_BOUNCE_FRAME_NUMBER */
        /* frame should align with interval */
        if (currentFrame <= ehciPipePointer->startFrame)
        {
            currentFrame = ehciPipePointer->startFrame;
        }
        else
        {
            currentFrame -= ehciPipePointer->startFrame;
            currentFrame = ((currentFrame + frameInterval - 1U) & (~(frameInterval - 1U)));
            currentFrame += ehciPipePointer->startFrame;
        }
    }
    else
    {
        shouldLinkFrame = isoPointer->lastLinkFrame + frameInterval; /* continuous next should link frame */
        if (shouldLinkFrame > USB_HOST_EHCI_MAX_MICRFRAME_VALUE >> 3U)
        {
            shouldLinkFrame = shouldLinkFrame - ((USB_HOST_EHCI_MAX_MICRFRAME_VALUE >> 3U) + 1U);
        }
        currentFrame = ((ehciInstance->ehciIpBase->FRINDEX & USB_HOST_EHCI_MAX_MICRFRAME_VALUE) >> 3U);
        distance =
            ((shouldLinkFrame + (USB_HOST_EHCI_MAX_MICRFRAME_VALUE >> 3U) + 1U - currentFrame) &
             (USB_HOST_EHCI_MAX_MICRFRAME_VALUE >> 3)); /* get the distance from shouldLinkFrame to currentFrame */
        /* shouldLinkFrame has add frameInterval, think about the align with interval, so here add (frameInterval *
         * 2) */
        if ((distance <=
             (USB_HOST_EHCI_ISO_BOUNCE_FRAME_NUMBER + frameInterval * USB_HOST_EHCI_ISO_MAX_CONTINUOUS_TRANSFER)) &&
            (distance > 0U))
        {
            currentFrame = shouldLinkFrame;
        }
        else /* re-link */
        {
            currentFrame =
                ((currentFrame + USB_HOST_EHCI_ISO_BOUNCE_FRAME_NUMBER) & (USB_HOST_EHCI_MAX_MICRFRAME_VALUE >> 3));

            /*if (currentFrame > (USB_HOST_EHCI_MAX_MICRFRAME_VALUE >> 3))
            {
                currentFrame = currentFrame - ((USB_HOST_EHCI_MAX_MICRFRAME_VALUE >> 3) + 1U);
            }*/
            /* frame should align with interval */
            if (currentFrame <= ehciPipePointer->startFrame)
            {
                currentFrame = ehciPipePointer->startFrame;
            }
            else
            {
                currentFrame -= ehciPipePointer->startFrame;
                currentFrame = ((currentFrame + frameInterval - 1U) & (~(frameInterval - 1U)));
                currentFrame += ehciPipePointer->startFrame;
            }
        }
    }
    if (currentFrame >= USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE) /* frame turn around */
    {
        shouldLinkFrame =
            (currentFrame - USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE); /* shouldLinkFrame means inserted frame position */
    }
    else
    {
        shouldLinkFrame = currentFrame; /* shouldLinkFrame means inserted frame position */
    }

    sitdPointer = (usb_host_ehci_sitd_t *)startEntryPointer;
    while (NULL != sitdPointer)
    {
        sitdPointer->frameEntryIndex = (uint16_t)shouldLinkFrame;
        /* add to frame list head */
        temp                                = (void *)ehciInstance->ehciFrameList;
        sitdPointer->nextLinkPointer        = ((uint32_t *)temp)[shouldLinkFrame];
        ((uint32_t *)temp)[shouldLinkFrame] = ((uint32_t)sitdPointer | EHCI_HOST_POINTER_TYPE_SITD);
        if (sitdPointer->nextSitdIndex == 0xFFU) /* 0xFF is invalid value */
        {
            break;
        }
        sitdPointer = &(ehciInstance->ehciSitdIndexBase[sitdPointer->nextSitdIndex]); /* next sitd */

        shouldLinkFrame += frameInterval;
        currentFrame += frameInterval;
        if (shouldLinkFrame >= USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE)
        {
            shouldLinkFrame = (shouldLinkFrame - USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE);
        }
    }

    if (currentFrame > (USB_HOST_EHCI_MAX_MICRFRAME_VALUE >> 3))
    {
        currentFrame = currentFrame - ((USB_HOST_EHCI_MAX_MICRFRAME_VALUE >> 3) + 1U);
    }
    isoPointer->lastLinkFrame = (uint16_t)currentFrame; /* save the last link frame value */
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
    uint32_t hubNumber  = 0U;
    uint32_t portNumber = 0U;
    uint32_t address    = 0U;
    uint32_t tmp;
    uint32_t *temp;
    uint32_t index;
    int32_t tempIndex;
    (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                 (uint32_t)kUSB_HostGetDeviceAddress, &address);

    sitdNumber = ((transfer->transferLength - 1U + (ehciPipePointer->pipeCommon.maxPacketSize)) /
                  (ehciPipePointer->pipeCommon.maxPacketSize));
    /* get sitd array */
    /* USB_HostEhciLock(); */
    if (ehciInstance->ehciSitdNumber >= sitdNumber)
    {
        sitdPointer               = ehciInstance->ehciSitdList;
        transfer->union1.unitHead = (uint32_t)sitdPointer;
        for (index = 1U; index < sitdNumber; ++index)
        {
            /*misra 10.8*/
            tempIndex                  = (((usb_host_ehci_sitd_t *)(sitdPointer->nextLinkPointer & 0xFFFFFFFEU)) -
                         ehciInstance->ehciSitdIndexBase);
            sitdPointer->nextSitdIndex = (uint8_t)tempIndex;
            sitdPointer                = (usb_host_ehci_sitd_t *)(sitdPointer->nextLinkPointer & 0xFFFFFFFEU);
        }
        sitdPointer->nextSitdIndex = 0xFF;
        ehciInstance->ehciSitdList = (usb_host_ehci_sitd_t *)(sitdPointer->nextLinkPointer & 0xFFFFFFFEU);
        ehciInstance->ehciSitdNumber -= (uint8_t)sitdNumber;
    }
    else
    {
        /* USB_HostEhciUnlock(); */
        return kStatus_USB_Error;
    }
    /* USB_HostEhciUnlock(); */
    transfer->union2.unitTail = (uint32_t)sitdPointer;
    /* initialize sitd array */
    (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                 (uint32_t)kUSB_HostGetDeviceHubNumber, &hubNumber);
    (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                 (uint32_t)kUSB_HostGetDevicePortNumber, &portNumber);
    sitdPointer = (usb_host_ehci_sitd_t *)transfer->union1.unitHead;
    dataLength  = transfer->transferLength;
    while (0U != sitdNumber)
    {
        sitdNumber--;
        USB_HostEhciZeroMem((void *)sitdPointer, 7);
        sitdLength = dataLength;
        if (sitdLength > ehciPipePointer->pipeCommon.maxPacketSize)
        {
            sitdLength = ehciPipePointer->pipeCommon.maxPacketSize;
        }
        dataBufferValue = (uint32_t)(transfer->transferBuffer + (transfer->transferLength - dataLength));
        dataLength -= sitdLength; /* update left data length */
        sitdPointer->transferResults[1] = dataBufferValue;
        sitdPointer->transferResults[2] = ((dataBufferValue + 4U * 1024U) & 0xFFFFF000U);
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

            tmp = (sitdLength + 187U) / 188U;
            if (tmp > 1U)
            {
                sitdPointer->transferResults[2] |= (0x01U << EHCI_HOST_SITD_TP_SHIFT); /* for iso split */
            }
            else
            {
                sitdPointer->transferResults[2] |= (0x00U << EHCI_HOST_SITD_TP_SHIFT); /* for iso split */
            }
            sitdPointer->transferResults[2] |= (tmp << EHCI_HOST_SITD_TCOUNT_SHIFT); /* for iso split */
        }

        sitdPointer->backPointer = EHCI_HOST_T_INVALID_VALUE;

        sitdPointer = (ehciInstance->ehciSitdIndexBase + sitdPointer->nextSitdIndex);
    }
    sitdPointer = (usb_host_ehci_sitd_t *)transfer->union2.unitTail;
    sitdPointer->transferResults[0] |= (1UL << EHCI_HOST_SITD_IOC_SHIFT); /* last set IOC */

    /* link transfer to usb_host_ehci_iso_t transfer list */
    isoPointer = (usb_host_ehci_iso_t *)ehciPipePointer->ehciQh;
    USB_HostEhciLock();
    if (isoPointer->ehciTransferHead == NULL)
    {
        transfer->next               = NULL;
        isoPointer->ehciTransferTail = transfer;
        isoPointer->ehciTransferHead = transfer;
    }
    else
    {
        transfer->next                     = NULL;
        isoPointer->ehciTransferTail->next = transfer;
        isoPointer->ehciTransferTail       = transfer;
    }
    USB_HostEhciUnlock();

    /* link itd to frame list (note: initialize frameEntryIndex)*/
    /*misra 11.6*/
    temp = (uint32_t *)(transfer->union1.unitHead);
    USB_HostEhciLinkSitd(ehciInstance, ehciPipePointer, (void *)temp);

    return kStatus_USB_Success;
}

static uint32_t USB_HostEhciSitdArrayRelease(usb_host_ehci_instance_t *ehciInstance,
                                             usb_host_ehci_sitd_t *startSitdPointer,
                                             usb_host_ehci_sitd_t *endSitdPointer)
{
    usb_host_ehci_sitd_t *sitdPointer = startSitdPointer;
    uint32_t leftLength               = 0;
    /* remove itd from frame list */
    while (1U == 1U)
    {
        /* record the transfer's result length */
        leftLength +=
            ((sitdPointer->transferResults[0] & EHCI_HOST_SITD_TOTAL_BYTES_MASK) >> EHCI_HOST_SITD_TOTAL_BYTES_SHIFT);
        USB_HostEhciRemoveFromFrame(ehciInstance, (uint32_t)sitdPointer,
                                    sitdPointer->frameEntryIndex); /* remove from the inserted frame list */

        /* release itd */
        /* USB_HostEhciLock(); */
        /*set next link pointer to invalid in case hardware access invalid sitd structure in special case*/
        sitdPointer->nextLinkPointer = (((uint32_t)ehciInstance->ehciSitdList) | EHCI_HOST_T_INVALID_VALUE);
        ehciInstance->ehciSitdList   = sitdPointer;
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
    transfer                     = isoPointer->ehciTransferHead;
    isoPointer->ehciTransferTail = NULL;
    isoPointer->ehciTransferHead = NULL;
    USB_HostEhciUnlock();

    while (transfer != NULL)
    {
        nextTransfer = transfer->next;
        /* remove sitd from frame list and release itd */
        transfer->transferSofar =
            transfer->transferLength - USB_HostEhciSitdArrayRelease(ehciInstance,
                                                                    (usb_host_ehci_sitd_t *)transfer->union1.unitHead,
                                                                    (usb_host_ehci_sitd_t *)transfer->union2.unitTail);
        /* callback function is different from the current condition */
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
    uint32_t shouldLinkUframe;
    uint32_t currentUframe;
    uint32_t distance;

    if (lastLinkUframe != 0xFFFFU)
    {
        shouldLinkUframe = lastLinkUframe + uframeInterval;
        if (shouldLinkUframe > USB_HOST_EHCI_MAX_MICRFRAME_VALUE)
        {
            shouldLinkUframe = shouldLinkUframe - (USB_HOST_EHCI_MAX_MICRFRAME_VALUE + 1U);
        }
        currentUframe = (ehciInstance->ehciIpBase->FRINDEX & USB_HOST_EHCI_MAX_MICRFRAME_VALUE);
        distance      = ((shouldLinkUframe + USB_HOST_EHCI_MAX_MICRFRAME_VALUE + 1U - currentUframe) &
                    USB_HOST_EHCI_MAX_MICRFRAME_VALUE); /* get the distance */
        /* shouldLinkUframe has add uframeInterval, think about the align with interval, so here add (uframeInterval
         * * 2) */
        if ((distance <= ((uint32_t)USB_HOST_EHCI_ISO_BOUNCE_UFRAME_NUMBER +
                          ((uint32_t)uframeInterval * USB_HOST_EHCI_ISO_MAX_CONTINUOUS_TRANSFER))) &&
            (distance > 2U))
        {
            currentUframe = shouldLinkUframe;
        }
        else /* re-link */
        {
            currentUframe =
                ((currentUframe + USB_HOST_EHCI_ISO_BOUNCE_UFRAME_NUMBER) & USB_HOST_EHCI_MAX_MICRFRAME_VALUE);
            /*if (currentUframe > USB_HOST_EHCI_MAX_MICRFRAME_VALUE)
            {
                currentUframe = currentUframe - (USB_HOST_EHCI_MAX_MICRFRAME_VALUE + 1U);
            }*/
            /* uframe should align with interval */
            if (currentUframe <= startUframe)
            {
                currentUframe = startUframe;
            }
            else
            {
                currentUframe -= startUframe;
                currentUframe = ((uint32_t)(currentUframe + uframeInterval) &
                                 (~((uint32_t)uframeInterval - 1U))); /* uframeInterval is power of 2 */
                currentUframe += startUframe;
            }
        }
    }
    else
    {
        currentUframe = (ehciInstance->ehciIpBase->FRINDEX & USB_HOST_EHCI_MAX_MICRFRAME_VALUE);
        currentUframe = ((currentUframe + USB_HOST_EHCI_ISO_BOUNCE_UFRAME_NUMBER) & USB_HOST_EHCI_MAX_MICRFRAME_VALUE);
        /* uframe should align with interval */
        if (currentUframe <= startUframe)
        {
            currentUframe = startUframe;
        }
        else
        {
            currentUframe -= startUframe;
            currentUframe =
                ((currentUframe + uframeInterval) & (~(uframeInterval - 1U))); /* uframeInterval is power of 2 */
            currentUframe += startUframe;
        }
    }

    return currentUframe;
}

static usb_status_t USB_HostEhciItdArrayInit(usb_host_ehci_instance_t *ehciInstance,
                                             usb_host_ehci_pipe_t *ehciPipePointer,
                                             usb_host_transfer_t *transfer)
{
    usb_host_ehci_iso_t *isoPointer;
    usb_host_ehci_itd_t *itdPointer = NULL;
    usb_host_ehci_itd_t *itdHead    = NULL;
    usb_host_ehci_itd_t *tmpItdPointer;
    uint32_t dataLength;        /* the remaining data for sending */
    uint32_t transactionLength; /* the initializing transaction descriptor data length */
    uint32_t itdBufferValue;
    uint32_t itdBufferBaseValue; /* for calculating PG value */
    uint32_t address = 0U;
    uint32_t lastShouldLinkUframe;
    uint32_t linkUframe;
    uint32_t minDataPerItd =
        (uint32_t)ehciPipePointer->pipeCommon.numberPerUframe * ehciPipePointer->pipeCommon.maxPacketSize;
    uint8_t maxItdNumber;
    uint16_t index = 0;

    isoPointer = (usb_host_ehci_iso_t *)ehciPipePointer->ehciQh;
    (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                 (uint32_t)kUSB_HostGetDeviceAddress, &address);

    /* max needed itd number, the actual needed number may be less because micro-frame interval may be less than 8 */
    maxItdNumber = (uint8_t)((transfer->transferLength - 1U + minDataPerItd) / minDataPerItd);
    if (ehciPipePointer->uframeInterval < 8U)
    {
        maxItdNumber = (uint8_t)((maxItdNumber * ehciPipePointer->uframeInterval + 7U) / 8U) + 1U;
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
        isoPointer->ehciTransferTail = transfer;
        isoPointer->ehciTransferHead = transfer;
    }
    else
    {
        isoPointer->ehciTransferTail->next = transfer;
        isoPointer->ehciTransferTail       = transfer;
    }
    /* USB_HostEhciUnlock(); */

    dataLength                = transfer->transferLength;
    transfer->union1.unitHead = 0U;
    /* get the link micro-frame */
    lastShouldLinkUframe = USB_HostEhciGetItdLinkFrame(
        ehciInstance, isoPointer->lastLinkFrame,
        (uint16_t)((ehciPipePointer->startFrame << 3) + ehciPipePointer->startUframe), ehciPipePointer->uframeInterval);
    if (lastShouldLinkUframe > USB_HOST_EHCI_MAX_MICRFRAME_VALUE)
    {
        linkUframe = lastShouldLinkUframe - (USB_HOST_EHCI_MAX_MICRFRAME_VALUE + 1U);
    }
    else
    {
        linkUframe = lastShouldLinkUframe;
    }
    itdHead = ehciInstance->ehciItdList;
    while (0U != dataLength)
    {
        /* get one idle itd */
        tmpItdPointer = ehciInstance->ehciItdList;
        if (tmpItdPointer == NULL)
        {
            return kStatus_USB_Error; /* this should not reach */
        }
        ehciInstance->ehciItdList = (usb_host_ehci_itd_t *)tmpItdPointer->nextItdPointer;
        ehciInstance->ehciItdNumber -= 1U;

        tmpItdPointer->nextItdPointer = NULL;

        /* use the itd */
        if (transfer->union1.unitHead == 0U) /* first itd */
        {
            transfer->union1.unitHead = (uint32_t)tmpItdPointer;
        }
        else /* link itd list */
        {
            itdPointer->nextItdPointer = tmpItdPointer;
        }
        itdPointer = tmpItdPointer;

        /* itd has been set to all zero when releasing */
        itdBufferValue     = (uint32_t)(transfer->transferBuffer + (transfer->transferLength - dataLength));
        itdBufferBaseValue = itdBufferValue;
        for (index = 0; index < 7U; ++index)
        {
            itdPointer->bufferPointers[index] = ((itdBufferBaseValue + ((uint32_t)index * 4U * 1024U)) & 0xFFFFF000U);
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
        for (index = (uint8_t)(linkUframe & 0x0007U); index < 8U; index += ehciPipePointer->uframeInterval)
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
            if (dataLength <= 0U)
            {
                break;
            }
        }
    }

    transfer->union2.unitTail = (uint32_t)itdPointer;
    itdPointer->transactions[index] |= (1UL << EHCI_HOST_ITD_IOC_SHIFT); /* last set IOC */

    itdPointer = itdHead;
    /* link itd to frame list (note: initialize frameEntryIndex)*/
    while (NULL != itdPointer)
    {
        void *temp                  = (void *)ehciInstance->ehciFrameList;
        uint32_t *linkPointer       = &((uint32_t *)temp)[linkUframe >> 3];
        uint32_t linkValue          = *linkPointer;
        itdPointer->frameEntryIndex = linkUframe >> 3;
        while ((0U == (linkValue & EHCI_HOST_T_INVALID_VALUE)) &&
               ((linkValue & EHCI_HOST_POINTER_TYPE_MASK) == EHCI_HOST_POINTER_TYPE_ITD))
        {
            linkPointer = (uint32_t *)(linkValue & EHCI_HOST_POINTER_ADDRESS_MASK);
            linkValue   = *linkPointer;
        }
        itdPointer->nextLinkPointer = *linkPointer;
        *linkPointer                = ((uint32_t)itdPointer | EHCI_HOST_POINTER_TYPE_ITD);
        itdPointer                  = itdPointer->nextItdPointer;
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

    if (lastShouldLinkUframe > USB_HOST_EHCI_MAX_MICRFRAME_VALUE)
    {
        lastShouldLinkUframe = lastShouldLinkUframe - (USB_HOST_EHCI_MAX_MICRFRAME_VALUE + 1U);
    }
    isoPointer->lastLinkFrame = (uint16_t)lastShouldLinkUframe;

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
    while (1U == 1U)
    {
        /* record the transfer's result length */
        for (index = 0U; index < 8U; ++index)
        {
            doneLength += ((itdPointer->transactions[index] & EHCI_HOST_ITD_TRANSACTION_LEN_MASK) >>
                           EHCI_HOST_ITD_TRANSACTION_LEN_SHIFT);
        }

        USB_HostEhciRemoveFromFrame(ehciInstance, (uint32_t)itdPointer,
                                    (uint16_t)itdPointer->frameEntryIndex); /* remove from the inserted frame list */

        /* release itd */
        /* USB_HostEhciLock(); */
        /*set next link pointer to invalid in case hardware access invalid itd structure in special case*/
        itdPointer->nextLinkPointer = EHCI_HOST_T_INVALID_VALUE;
        USB_HostEhciZeroMem((uint32_t *)(void *)itdPointer + 1, ((sizeof(usb_host_ehci_itd_t) >> 2) - 4U));
        itdPointer->nextItdPointer = (usb_host_ehci_itd_t *)ehciInstance->ehciItdList;
        ehciInstance->ehciItdList  = itdPointer;
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
    transfer                     = isoPointer->ehciTransferHead;
    isoPointer->ehciTransferTail = NULL;
    isoPointer->ehciTransferHead = NULL;
    USB_HostEhciUnlock();

    while (transfer != NULL)
    {
        nextTransfer = transfer->next;
        doneLength   = 0;
        /* remove itd from frame list and release itd */
        doneLength = USB_HostEhciItdArrayRelease(ehciInstance, (usb_host_ehci_itd_t *)transfer->union1.unitHead,
                                                 (usb_host_ehci_itd_t *)transfer->union2.unitTail);

        /* transfer callback */
        if (ehciPipePointer->pipeCommon.direction == USB_OUT)
        {
            doneLength = transfer->transferLength;
        }
        transfer->transferSofar = doneLength;
        /* callback function is different from the current condition */
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
    qhPointer->horizontalLinkPointer                 = ehciInstance->shedFirstQh->horizontalLinkPointer;
    ehciInstance->shedFirstQh->horizontalLinkPointer = ((uint32_t)qhPointer | EHCI_HOST_POINTER_TYPE_QH);

    return kStatus_USB_Success;
}

static usb_status_t USB_HostEhciCloseControlBulk(usb_host_ehci_instance_t *ehciInstance,
                                                 usb_host_ehci_pipe_t *ehciPipePointer)
{
    volatile usb_host_ehci_qh_t *vltPrevQhPointer;
    uint32_t horizontalLinkValue;
    uint32_t *temp;
    /* remove qh from async schedule */
    temp = (uint32_t *)ehciPipePointer->ehciQh;
    if ((ehciInstance->shedFirstQh->horizontalLinkPointer & EHCI_HOST_POINTER_ADDRESS_MASK) ==
        (uint32_t)temp) /* the removing qh is the first qh in the async list */
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
            if ((0U != (horizontalLinkValue & EHCI_HOST_T_INVALID_VALUE)) ||
                ((horizontalLinkValue & EHCI_HOST_POINTER_ADDRESS_MASK) == (uint32_t)temp) ||
                ((horizontalLinkValue & EHCI_HOST_POINTER_ADDRESS_MASK) == (uint32_t)ehciInstance->shedFirstQh))
            {
                break;
            }

            vltPrevQhPointer = (volatile usb_host_ehci_qh_t *)(horizontalLinkValue & EHCI_HOST_POINTER_ADDRESS_MASK);
        }

        /* remove the qh from async list */
        /*for misra 11.6*/
        temp = (uint32_t *)ehciPipePointer->ehciQh;
        if ((vltPrevQhPointer != NULL) && (0U == (horizontalLinkValue & EHCI_HOST_T_INVALID_VALUE)) &&
            ((horizontalLinkValue & EHCI_HOST_POINTER_ADDRESS_MASK) == (uint32_t)temp))
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
    uint32_t *temp;

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
         frameIndex += (((uint32_t)ehciPipePointer->uframeInterval + 7U) / 8U))
    {
        temp = (uint32_t *)ehciPipePointer->ehciQh;
        USB_HostEhciAddQhToFrame(ehciInstance, (uint32_t)temp, (uint16_t)frameIndex, ehciPipePointer->uframeInterval);
    }

    return kStatus_USB_Success;
}

static usb_status_t USB_HostEhciCloseInterrupt(usb_host_ehci_instance_t *ehciInstance,
                                               usb_host_ehci_pipe_t *ehciPipePointer)
{
    uint32_t frameIndex;
    uint32_t *temp;
    /* remove from frame list */
    for (frameIndex = ehciPipePointer->startFrame; frameIndex < USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE;
         frameIndex += (((uint32_t)ehciPipePointer->uframeInterval + 7U) / 8U))
    {
        temp = (uint32_t *)ehciPipePointer->ehciQh;
        USB_HostEhciRemoveFromFrame(ehciInstance, (uint32_t)temp, (uint16_t)frameIndex);
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
    isoPointer                = ehciInstance->ehciIsoList;
    ehciInstance->ehciIsoList = ehciInstance->ehciIsoList->next;
    USB_HostEhciUnlock();
    isoPointer->lastLinkFrame = 0xFFFF;
    ehciPipePointer->ehciQh   = isoPointer;

    return status;
}

static usb_status_t USB_HostEhciCloseIso(usb_host_ehci_instance_t *ehciInstance, usb_host_ehci_pipe_t *ehciPipePointer)
{
    usb_host_ehci_iso_t *isoPointer;
    uint32_t speed = 0U;

    isoPointer = (usb_host_ehci_iso_t *)ehciPipePointer->ehciQh;

    if (isoPointer->ehciTransferHead != NULL)
    {
        (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                     (uint32_t)kUSB_HostGetDeviceSpeed, &speed);
        if (speed == USB_SPEED_HIGH)
        {
#if ((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD))
            (void)USB_HostEhciItdArrayDeinit(ehciInstance, ehciPipePointer); /* de-initialize itd list and free them */
#endif
        }
        else
        {
#if ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD))
            (void)USB_HostEhciSitdArrayDeinit(ehciInstance,
                                              ehciPipePointer); /* de-initialize sitd list and free them */
#endif
        }
    }

    /* release usb_host_ehci_iso_t */
    USB_HostEhciLock();
    isoPointer->next          = ehciInstance->ehciIsoList;
    ehciInstance->ehciIsoList = isoPointer;
    USB_HostEhciUnlock();
    return kStatus_USB_Success;
}

#endif

static usb_status_t USB_HostEhciResetIP(usb_host_ehci_instance_t *ehciInstance)
{
    /* reset controller */
    ehciInstance->ehciIpBase->USBCMD = USBHS_USBCMD_RST_MASK;
    while (0U != (ehciInstance->ehciIpBase->USBCMD & USBHS_USBCMD_RST_MASK))
    {
    }
/* set host mode */
#if (ENDIANNESS == USB_LITTLE_ENDIAN)
    ehciInstance->ehciIpBase->USBMODE |= 0x03U;
#else
    ehciInstance->ehciIpBase->USBMODE |= (0x03U | (0x01U << USBHS_USBMODE_ES_SHIFT));
#endif
    /* check frame list size */
    if (0U == (ehciInstance->ehciIpBase->HCCPARAMS & USBHS_HCCPARAMS_PFL_MASK))
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

    if (0U != (ehciInstance->ehciIpBase->HCSPARAMS & USBHS_HCSPARAMS_PPC_MASK)) /* Ports have power port switches */
    {
        /* only has one port */
        tmp = ehciInstance->ehciIpBase->PORTSC1;
        tmp &= (~EHCI_PORTSC1_W1_BITS);
        ehciInstance->ehciIpBase->PORTSC1 = (tmp | USBHS_PORTSC1_PP_MASK); /* turn on port power */
    }

    /* set frame list size */
    if (0U != (ehciInstance->ehciIpBase->HCCPARAMS & USBHS_HCCPARAMS_PFL_MASK))
    {
#if (USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE <= 64)
        ehciInstance->ehciIpBase->USBCMD |= (USBHS_USBCMD_FS2_MASK);
#if (USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE == 64)
        ehciInstance->ehciIpBase->USBCMD |= (0x00U << USBHS_USBCMD_FS_SHIFT);
#elif (USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE == 32)
        ehciInstance->ehciIpBase->USBCMD |= (0x01U << USBHS_USBCMD_FS_SHIFT);
#elif (USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE == 16)
        ehciInstance->ehciIpBase->USBCMD |= (0x02U << USBHS_USBCMD_FS_SHIFT);
#elif (USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE == 8)
        ehciInstance->ehciIpBase->USBCMD |= (0x03U << USBHS_USBCMD_FS_SHIFT);
#endif
#else
#if (USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE == 1024)
        ehciInstance->ehciIpBase->USBCMD |= (0x00U << USBHS_USBCMD_FS_SHIFT);
#elif (USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE == 512)
        ehciInstance->ehciIpBase->USBCMD |= (0x01U << USBHS_USBCMD_FS_SHIFT);
#elif (USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE == 256)
        ehciInstance->ehciIpBase->USBCMD |= (0x02U << USBHS_USBCMD_FS_SHIFT);
#elif (USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE == 128)
        ehciInstance->ehciIpBase->USBCMD |= (0x03U << USBHS_USBCMD_FS_SHIFT);
#endif
#endif
    }
    /* no interrupt threshold */
    ehciInstance->ehciIpBase->USBCMD &= ~USBHS_USBCMD_ITC_MASK;
    /* start the controller */
    ehciInstance->ehciIpBase->USBCMD |= USBHS_USBCMD_RS_MASK;
    /* set timer0 */
    ehciInstance->ehciIpBase->GPTIMER0LD = (100U * 1000U - 1U); /* 100ms */

    /* enable interrupt (USB interrupt enable + USB error interrupt enable + port change detect enable + system error
     * enable + interrupt on async advance enable) + general purpos Timer 0 Interrupt enable */
    ehciInstance->ehciIpBase->USBINTR |= (0x1000037U);

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
    uint32_t speed = 0U;
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
                    cancelPipe = 1U;
                }
                else
                {
                    cancelPipe = 0U;
                }
            }
            else
            {
                cancelPipe = 1U;
            }
            if (cancelPipe == 1U) /* cancel all pipe */
            {
                (void)USB_HostEhciQhQtdListDeinit(ehciInstance, ehciPipePointer); /* release all the qtd */
            }
            else /* cancel one transfer */
            {
                (void)USB_HostEhciTransferQtdListDeinit(ehciInstance, ehciPipePointer, transfer);
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
            (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                         (uint32_t)kUSB_HostGetDeviceSpeed, &speed);
            if (speed == USB_SPEED_HIGH)
            {
#if ((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD))
                (void)USB_HostEhciItdArrayDeinit(ehciInstance, ehciPipePointer); /* de-initialize itd */
#endif
            }
            else
            {
#if ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD))
                (void)USB_HostEhciSitdArrayDeinit(ehciInstance, ehciPipePointer); /* de-initialize sitd */
#endif
            }
            break;
#endif

        default:
            /*no action*/
            break;
    }

    return kStatus_USB_Success;
}

static usb_status_t USB_HostEhciControlBus(usb_host_ehci_instance_t *ehciInstance, uint8_t busControl)
{
    usb_status_t status = kStatus_USB_Success;
    uint32_t portScRegister;
    usb_host_bus_control_t controlCode = (usb_host_bus_control_t)busControl;
    switch (controlCode)
    {
        case kUSB_HostBusReset:
            /* reset port */
            portScRegister = ehciInstance->ehciIpBase->PORTSC1;
            portScRegister &= (~EHCI_PORTSC1_W1_BITS);
            ehciInstance->ehciIpBase->PORTSC1 = (portScRegister | USBHS_PORTSC1_PR_MASK);
            while (0U != (ehciInstance->ehciIpBase->PORTSC1 & USBHS_PORTSC1_PR_MASK))
            {
            }
            break;

        case kUSB_HostBusRestart:
            ehciInstance->deviceAttached = (uint8_t)kEHCIDeviceDetached;
            ehciInstance->ehciIpBase->USBINTR |= (USBHS_USBINTR_PCE_MASK); /* enable ehci port change interrupt */
            break;

        case kUSB_HostBusEnableAttach: /* enable device attach */
            if (ehciInstance->deviceAttached == (uint8_t)kEHCIDeviceDetached)
            {
                ehciInstance->ehciIpBase->USBINTR |= (USBHS_USBINTR_PCE_MASK); /* enable ehci port change interrupt */
            }
            break;

        case kUSB_HostBusDisableAttach:                                     /* disable device attach */
            ehciInstance->ehciIpBase->USBINTR &= (~USBHS_USBINTR_PCE_MASK); /* disable ehci port change interrupt */
            break;
#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
        case kUSB_HostBusSuspend:
            if (0U != (ehciInstance->ehciIpBase->PORTSC1 & USBHS_PORTSC1_CCS_MASK))
            {
                /* set timer1 */
                ehciInstance->ehciIpBase->GPTIMER1LD = (1 * 1000); /* 1ms */
                ehciInstance->ehciIpBase->GPTIMER1CTL |=
                    (USBHS_GPTIMER0CTL_RUN_MASK | USBHS_GPTIMER0CTL_MODE_MASK | USBHS_GPTIMER0CTL_RST_MASK);

                USB_HostEhciStopAsync(ehciInstance);
                USB_HostEhciStopPeriodic(ehciInstance);
                while (0U != (ehciInstance->ehciIpBase->USBSTS & (USBHS_USBSTS_PS_MASK | USBHS_USBSTS_AS_MASK)))
                {
                    __NOP();
                }
                ehciInstance->ehciIpBase->PORTSC1 &= ~USBHS_PORTSC1_WKCN_MASK;
                ehciInstance->ehciIpBase->PORTSC1 |= USBHS_PORTSC1_WKDS_MASK;
                ehciInstance->ehciIpBase->PORTSC1 |= (USBHS_PORTSC1_SUSP_MASK); /* Suspend the device */
#if (defined(FSL_FEATURE_USB_ATLANTIC_EHCI_SUPPORT) && (FSL_FEATURE_USB_ATLANTIC_EHCI_SUPPORT > 0U))
                PMU->WAKEUP_PM2_MASK1 |= PMU_WAKEUP_PM2_MASK1_USB(1);
#endif
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
            if (ehciInstance->deviceAttached != (uint8_t)kEHCIDeviceDetached)
            {
                ehciInstance->busSuspendStatus = kBus_EhciStartResume;
#if (defined(FSL_FEATURE_SOC_USBNC_COUNT) && (FSL_FEATURE_SOC_USBNC_COUNT > 0U))
                ehciInstance->registerNcBase->USB_OTGn_CTRL &= ~USBNC_USB_OTGn_CTRL_WIE_MASK;
#else
#if (defined(FSL_FEATURE_USB_ATLANTIC_EHCI_SUPPORT) && (FSL_FEATURE_USB_ATLANTIC_EHCI_SUPPORT > 0U))
#else
                ehciInstance->ehciIpBase->USBGENCTRL &= ~USBHS_USBGENCTRL_WU_IE_MASK;
#endif
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
    uint32_t speed = 0U;
#endif
    void *temp;
    uint32_t transferResults;
    uint32_t transferOverlayResults;

    ehciPipePointer = ehciInstance->ehciRunningPipeList; /* check all the running pipes */
    while (ehciPipePointer != NULL)
    {
        switch (ehciPipePointer->pipeCommon.pipeType)
        {
            case USB_ENDPOINT_BULK:
            case USB_ENDPOINT_INTERRUPT:
            case USB_ENDPOINT_CONTROL:
                vltQhPointer = (volatile usb_host_ehci_qh_t *)ehciPipePointer->ehciQh; /* pipe's qh */
                transfer     = vltQhPointer->ehciTransferHead;                         /* qh's transfer */
                while (transfer != NULL)
                {
                    nextTransfer = transfer->next;
                    /* normal case */
                    vltQtdPointer          = (volatile usb_host_ehci_qtd_t *)transfer->union2.unitTail;
                    transferResults        = vltQtdPointer->transferResults[0];
                    transferOverlayResults = vltQhPointer->transferOverlayResults[0];
                    if ((0U != (transferResults & (EHCI_HOST_QTD_IOC_MASK))) &&
                        (0U == (transferResults & EHCI_HOST_QTD_STATUS_ACTIVE_MASK))) /* transfer is done */
                    {
                        qtdStatus = (transferResults & EHCI_HOST_QTD_STATUS_ERROR_MASK);
                        transfer->transferSofar =
                            USB_HostEhciQtdListRelease(ehciInstance, (usb_host_ehci_qtd_t *)(transfer->union1.unitHead),
                                                       (usb_host_ehci_qtd_t *)(transfer->union2.unitTail));
                        transfer->transferSofar = (transfer->transferLength < transfer->transferSofar) ?
                                                      0U :
                                                      (transfer->transferLength - transfer->transferSofar);

                        vltQhPointer->ehciTransferHead = transfer->next;
                        vltQhPointer->timeOutLabel     = 0U;
                        vltQhPointer->timeOutValue     = USB_HOST_EHCI_CONTROL_BULK_TIME_OUT_VALUE;
                        if (0U != qtdStatus) /* has errors */
                        {
                            if (0U == (transferOverlayResults & EHCI_HOST_QTD_STATUS_ACTIVE_MASK))
                            {
                                vltQhPointer->transferOverlayResults[0] &=
                                    (~EHCI_HOST_QTD_STATUS_MASK); /* clear error status */
                            }
                            if (0U != (qtdStatus & EHCI_HOST_QH_STATUS_NOSTALL_ERROR_MASK))
                            {
                                /* callback function is different from the current condition */
                                transfer->callbackFn(transfer->callbackParam, transfer,
                                                     kStatus_USB_TransferFailed); /* transfer fail */
                            }
                            else
                            {
                                /* callback function is different from the current condition */
                                transfer->callbackFn(transfer->callbackParam, transfer, kStatus_USB_TransferStall);
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
                                    temp                 = (void *)ehciClearPipePointer->pipeCommon.next;
                                    ehciClearPipePointer = (usb_host_ehci_pipe_t *)temp;
                                }

                                if ((ehciClearPipePointer != NULL) &&
                                    ((ehciClearPipePointer->pipeCommon.pipeType == USB_ENDPOINT_INTERRUPT) ||
                                     (ehciClearPipePointer->pipeCommon.pipeType == USB_ENDPOINT_BULK)))
                                {
                                    ((volatile usb_host_ehci_qh_t *)(ehciClearPipePointer->ehciQh))
                                        ->transferOverlayResults[0] &= (~EHCI_HOST_QTD_DT_MASK);
                                }
                            }
                            /* callback function is different from the current condition */
                            transfer->callbackFn(transfer->callbackParam, transfer,
                                                 kStatus_USB_Success); /* transfer success */
                        }
                    }
                    else if ((0U == (transferOverlayResults & EHCI_HOST_QTD_STATUS_ACTIVE_MASK)) &&
                             (0U != (transferOverlayResults &
                                     EHCI_HOST_QH_STATUS_ERROR_MASK))) /* there is error and transfer is done */
                    {
                        qtdStatus     = (vltQhPointer->transferOverlayResults[0] & EHCI_HOST_QH_STATUS_ERROR_MASK);
                        vltQtdPointer = (volatile usb_host_ehci_qtd_t *)(vltQhPointer->currentQtdPointer);

                        if ((0U != ((uint32_t)vltQtdPointer & EHCI_HOST_T_INVALID_VALUE)) ||
                            (vltQtdPointer == NULL)) /* the error status is unreasonable */
                        {
                            vltQhPointer->transferOverlayResults[0] &=
                                (~EHCI_HOST_QTD_STATUS_MASK); /* clear error status */
                        }
                        else
                        {
                            /* remove qtd from qh */
                            do
                            {
                                if (vltQtdPointer == NULL)
                                {
                                    break;
                                }
                                else if (0U != (vltQtdPointer->transferResults[0] & EHCI_HOST_QTD_IOC_MASK))
                                {
                                    break;
                                }
                                else
                                {
                                    /* no action */
                                }
                                vltQtdPointer = (volatile usb_host_ehci_qtd_t *)vltQtdPointer->nextQtdPointer;
                            } while (true);

                            vltQhPointer->nextQtdPointer    = EHCI_HOST_T_INVALID_VALUE;
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
                                                          0U :
                                                          (transfer->transferLength - transfer->transferSofar);
                            vltQhPointer->ehciTransferHead = transfer->next;
                            vltQhPointer->timeOutLabel     = 0U;
                            vltQhPointer->timeOutValue     = USB_HOST_EHCI_CONTROL_BULK_TIME_OUT_VALUE;
                            if (0U != (qtdStatus & EHCI_HOST_QH_STATUS_NOSTALL_ERROR_MASK))
                            {
                                /* callback function is different from the current condition */
                                transfer->callbackFn(transfer->callbackParam, transfer,
                                                     kStatus_USB_TransferFailed); /* transfer fail */
                            }
                            else
                            {
                                /* callback function is different from the current condition */
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
                qtdStatus  = 0; /* qtdStatus means break here, because there is only one break in while for misra */
                isoPointer = (usb_host_ehci_iso_t *)ehciPipePointer->ehciQh; /* pipe's usb_host_ehci_iso_t */
                transfer   = isoPointer->ehciTransferHead;                   /* usb_host_ehci_iso_t's transfer */
                while (transfer != NULL)
                {
                    nextTransfer = transfer->next;
                    (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                                 (uint32_t)kUSB_HostGetDeviceSpeed, &speed);
                    if (speed == USB_SPEED_HIGH)
                    {
#if ((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD))
                        vltItdPointer =
                            (volatile usb_host_ehci_itd_t *)(transfer->union2.unitTail); /* transfer's last itd */
                        for (index = 0; index < 8U; ++index)
                        {
                            if (0U != (vltItdPointer->transactions[index] & EHCI_HOST_ITD_STATUS_ACTIVE_MASK))
                            {
                                break;
                            }
                        }
                        if (index == 8U) /* transfer is done */
                        {
                            /* remove itd from frame list and release itd */
                            dataLength                   = USB_HostEhciItdArrayRelease(ehciInstance,
                                                                     (usb_host_ehci_itd_t *)transfer->union1.unitHead,
                                                                     (usb_host_ehci_itd_t *)transfer->union2.unitTail);
                            transfer->transferSofar      = dataLength;
                            isoPointer->ehciTransferHead = transfer->next;
                            /* callback function is different from the current condition */
                            transfer->callbackFn(transfer->callbackParam, transfer,
                                                 kStatus_USB_Success); /* transfer callback success */
                            /* TODO: iso callback error */
                        }
                        else
                        {
                            qtdStatus = 1U; /* break */
                        }
#endif
                    }
                    else
                    {
#if ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD))
                        vltSitdPointer =
                            (volatile usb_host_ehci_sitd_t *)(transfer->union2.unitTail); /* transfer's last sitd */
                        if (0U == (vltSitdPointer->transferResults[0] &
                                   EHCI_HOST_SITD_STATUS_ACTIVE_MASK)) /* transfer is done */
                        {
                            /* remove sitd from frame list and release itd */
                            dataLength = USB_HostEhciSitdArrayRelease(
                                ehciInstance, (usb_host_ehci_sitd_t *)transfer->union1.unitHead,
                                (usb_host_ehci_sitd_t *)transfer->union2.unitTail);
                            transfer->transferSofar      = transfer->transferLength - dataLength;
                            isoPointer->ehciTransferHead = transfer->next;
                            /* callback function is different from the current condition */
                            transfer->callbackFn(transfer->callbackParam, transfer,
                                                 kStatus_USB_Success); /* transfer callback success */
                            /* TODO: iso callback error */
                        }
                        else
                        {
                            qtdStatus = 1U; /* break */
                        }
#endif
                    }
                    if (qtdStatus == 1U)
                    {
                        break;
                    }
                    transfer = nextTransfer;
                }
                break;
#endif

            default:
                /*no action*/
                break;
        }
        temp            = (void *)ehciPipePointer->pipeCommon.next;
        ehciPipePointer = (usb_host_ehci_pipe_t *)temp;
    }
}

static void USB_HostEhciPortChange(usb_host_ehci_instance_t *ehciInstance)
{
    /* note: only has one port */
    uint32_t portScRegister = ehciInstance->ehciIpBase->PORTSC1;
    uint32_t sofStart       = 0;
    uint32_t sofCount       = 0;
    uint32_t index;

    if (0U != (portScRegister & USBHS_PORTSC1_CSC_MASK)) /* connection status change */
    {
        sofStart = (ehciInstance->ehciIpBase->FRINDEX & EHCI_MAX_UFRAME_VALUE);

        /* process CSC bit */
        while (1U == 1U)
        {
            portScRegister = ehciInstance->ehciIpBase->PORTSC1;
            if (0U != (portScRegister & USBHS_PORTSC1_CSC_MASK))
            {
                /* clear csc bit */
                portScRegister = ehciInstance->ehciIpBase->PORTSC1;
                portScRegister &= (~EHCI_PORTSC1_W1_BITS);
                ehciInstance->ehciIpBase->PORTSC1 = (portScRegister | USBHS_PORTSC1_CSC_MASK);
            }
            sofCount = (ehciInstance->ehciIpBase->FRINDEX & EHCI_MAX_UFRAME_VALUE);
            if (((sofCount + EHCI_MAX_UFRAME_VALUE + 1U - sofStart) & EHCI_MAX_UFRAME_VALUE) >
                (1U * 8U)) /* delay 1ms to clear CSC */
            {
                break;
            }
        }
    }

    /* process CCS bit */
    portScRegister = ehciInstance->ehciIpBase->PORTSC1;
    if (0U != (portScRegister & USBHS_PORTSC1_CCS_MASK)) /* process attach */
    {
        if ((ehciInstance->deviceAttached == (uint8_t)kEHCIDevicePhyAttached) ||
            (ehciInstance->deviceAttached == (uint8_t)kEHCIDeviceAttached))
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
            if (0U == (ehciInstance->ehciIpBase->PORTSC1 & USBHS_PORTSC1_CCS_MASK))
            {
                break;
            }
        }
        if (index < USB_HOST_EHCI_PORT_CONNECT_DEBOUNCE_DELAY) /* CCS is cleared */
        {
            ehciInstance->deviceAttached = (uint8_t)kEHCIDeviceDetached;
            return;
        }
        /* reset port */
        portScRegister = ehciInstance->ehciIpBase->PORTSC1;
        portScRegister &= (~EHCI_PORTSC1_W1_BITS);
        ehciInstance->ehciIpBase->PORTSC1 = (portScRegister | USBHS_PORTSC1_PR_MASK);
        while (0U != (ehciInstance->ehciIpBase->PORTSC1 & USBHS_PORTSC1_PR_MASK))
        {
        }
        ehciInstance->firstDeviceSpeed =
            (uint8_t)((ehciInstance->ehciIpBase->PORTSC1 & USBHS_PORTSC1_PSPD_MASK) >> USBHS_PORTSC1_PSPD_SHIFT);
        /* enable ehci phy disconnection */
#if ((defined FSL_FEATURE_SOC_USBPHY_COUNT) && (FSL_FEATURE_SOC_USBPHY_COUNT > 0U))
        if (ehciInstance->firstDeviceSpeed == USB_SPEED_HIGH)
        {
            USB_EhcihostPhyDisconnectDetectCmd(ehciInstance->controllerId, 1);
        }
#endif

        /* wait for reset */
        USB_HostEhciDelay(ehciInstance->ehciIpBase, USB_HOST_EHCI_PORT_RESET_DELAY);
        /* process attach */
        (void)OSA_EventSet(ehciInstance->taskEventHandle, EHCI_TASK_EVENT_DEVICE_ATTACH);
        /* gpt timer start */
        ehciInstance->ehciIpBase->GPTIMER0CTL |=
            (USBHS_GPTIMER0CTL_RUN_MASK | USBHS_GPTIMER0CTL_MODE_MASK | USBHS_GPTIMER0CTL_RST_MASK);
        ehciInstance->deviceAttached = (uint8_t)kEHCIDevicePhyAttached;
    }
    else
    {
        if ((ehciInstance->deviceAttached == (uint8_t)kEHCIDevicePhyAttached) ||
            (ehciInstance->deviceAttached == (uint8_t)kEHCIDeviceAttached))
        {
#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
            ehciInstance->busSuspendStatus = kBus_EhciIdle;
            ehciInstance->ehciIpBase->USBINTR &= ~(USBHS_USBINTR_TIE1_MASK);
#endif
            /* disable ehci phy disconnection */
#if ((defined FSL_FEATURE_SOC_USBPHY_COUNT) && (FSL_FEATURE_SOC_USBPHY_COUNT > 0U))
            USB_EhcihostPhyDisconnectDetectCmd(ehciInstance->controllerId, 0);
#endif
            /* disable async and periodic */
            USB_HostEhciStopAsync(ehciInstance);
            USB_HostEhciStopPeriodic(ehciInstance);
            (void)OSA_EventSet(ehciInstance->taskEventHandle, EHCI_TASK_EVENT_DEVICE_DETACH);
        }
    }
}

static void USB_HostEhciTimer0(usb_host_ehci_instance_t *ehciInstance)
{
    volatile usb_host_ehci_qh_t *vltQhPointer;
    usb_host_ehci_qtd_t *vltQtdPointer;
    usb_host_transfer_t *transfer;
    uint32_t backValue;
    volatile uint32_t *totalBytesAddress  = NULL;
    usb_host_ehci_pipe_t *ehciPipePointer = ehciInstance->ehciRunningPipeList;
    void *temp;
    uint8_t timeoutLabel;

    while (ehciPipePointer != NULL)
    {
        switch (ehciPipePointer->pipeCommon.pipeType)
        {
            case USB_ENDPOINT_BULK:
            case USB_ENDPOINT_CONTROL:
                vltQhPointer = (volatile usb_host_ehci_qh_t *)ehciPipePointer->ehciQh; /* pipe's qh */
                transfer     = vltQhPointer->ehciTransferHead;                         /* qh's transfer */
                if ((transfer != NULL))                                                /* there is transfering data */
                {
                    timeoutLabel = 0U;
                    if (ehciInstance->deviceAttached != (uint8_t)kEHCIDeviceAttached)
                    {
                        vltQtdPointer = (usb_host_ehci_qtd_t *)transfer->union2.unitTail;

                        vltQhPointer->nextQtdPointer = EHCI_HOST_T_INVALID_VALUE; /* invalid next qtd */
                        vltQhPointer->transferOverlayResults[0] &=
                            (~EHCI_HOST_QTD_STATUS_MASK); /* clear error status */
                        timeoutLabel = 1;
                    }
                    else
                    {
                        if (0U != (vltQhPointer->transferOverlayResults[0] & EHCI_HOST_QTD_STATUS_ACTIVE_MASK))
                        {
                            vltQtdPointer     = (usb_host_ehci_qtd_t *)vltQhPointer->currentQtdPointer;
                            totalBytesAddress = &(vltQhPointer->transferOverlayResults[0]);
                        }
                        else
                        {
                            vltQtdPointer     = (usb_host_ehci_qtd_t *)transfer->union2.unitTail;
                            totalBytesAddress = &(vltQtdPointer->transferResults[0]);
                        }

                        backValue =
                            (((*totalBytesAddress) & EHCI_HOST_QTD_TOTAL_BYTES_MASK) >>
                             EHCI_HOST_QTD_TOTAL_BYTES_SHIFT);       /* backValue is used for total bytes to transfer */
                        if (vltQhPointer->timeOutLabel != backValue) /* use total bytes to reflect the time out */
                        {
                            vltQhPointer->timeOutValue = USB_HOST_EHCI_CONTROL_BULK_TIME_OUT_VALUE;
                            vltQhPointer->timeOutLabel = (uint16_t)backValue;
                        }
                        else
                        {
                            /* time out when the total bytes don't change for the duration
                             * USB_HOST_EHCI_CONTROL_BULK_TIME_OUT_VALUE
                             */
                            (vltQhPointer->timeOutValue)--;
                            if (vltQhPointer->timeOutValue == 0U)
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
                                    timeoutLabel = 1U;
                                }
                            }
                        }
                    }

                    if (timeoutLabel == 1U)
                    {
                        /* remove qtd from qh */
                        temp = (void *)vltQhPointer->ehciTransferTail;
                        while ((vltQtdPointer != NULL) &&
                               (0U == (vltQtdPointer->transferResults[0] & EHCI_HOST_QTD_IOC_MASK)) &&
                               (vltQtdPointer != (usb_host_ehci_qtd_t *)temp))
                        {
                            vltQtdPointer = (usb_host_ehci_qtd_t *)vltQtdPointer->nextQtdPointer;
                        }
                        if ((vltQtdPointer != NULL) &&
                            (0U == (vltQtdPointer->nextQtdPointer & EHCI_HOST_T_INVALID_VALUE)))
                        {
                            vltQhPointer->nextQtdPointer =
                                vltQtdPointer->nextQtdPointer; /* start qh if there are other qtd that don't belong to
                                                                  the transfer */
                        }
                        transfer->transferSofar =
                            USB_HostEhciQtdListRelease(ehciInstance, (usb_host_ehci_qtd_t *)(transfer->union1.unitHead),
                                                       (usb_host_ehci_qtd_t *)(transfer->union2.unitTail));
                        transfer->transferSofar = (transfer->transferLength < transfer->transferSofar) ?
                                                      0U :
                                                      (transfer->transferLength - transfer->transferSofar);

                        vltQhPointer->ehciTransferHead = transfer->next;
                        vltQhPointer->timeOutValue     = USB_HOST_EHCI_CONTROL_BULK_TIME_OUT_VALUE;
                        /* callback function is different from the current condition */
                        transfer->callbackFn(transfer->callbackParam, transfer, kStatus_USB_TransferFailed);
                    }
                }
                break;
            default:
                /*no action*/
                break;
        }
        temp            = (void *)ehciPipePointer->pipeCommon.next;
        ehciPipePointer = (usb_host_ehci_pipe_t *)temp;
    }
}

#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
static void USB_HostEhciTimer1(usb_host_ehci_instance_t *ehciInstance)
{
    if (ehciInstance->deviceAttached != (uint8_t)kEHCIDeviceDetached)
    {
        if (kBus_EhciStartSuspend == ehciInstance->busSuspendStatus)
        {
            usb_host_instance_t *hostPointer = (usb_host_instance_t *)ehciInstance->hostHandle;

            if (0U == ehciInstance->matchTick)
            {
                ehciInstance->matchTick = hostPointer->hwTick;
            }
            else
            {
                if ((hostPointer->hwTick - ehciInstance->matchTick) >= 5U)
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
#if (defined(FSL_FEATURE_USBPHY_28FDSOI) && (FSL_FEATURE_USBPHY_28FDSOI > 0U))
                    ehciInstance->registerPhyBase->USB1_VBUS_DETECT_SET |=
                        USBPHY_USB1_VBUS_DETECT_VBUSVALID_TO_SESSVALID_MASK;
#endif
                    ehciInstance->ehciIpBase->PORTSC1 |= USBHS_PORTSC1_PHCD_MASK;
#if ((defined FSL_FEATURE_SOC_USBPHY_COUNT) && (FSL_FEATURE_SOC_USBPHY_COUNT > 0U))
                    ehciInstance->registerPhyBase->PWD = 0xFFFFFFFFU;

                    while (0U != (ehciInstance->registerPhyBase->CTRL & (USBPHY_CTRL_UTMI_SUSPENDM_MASK)))
                    {
                        __NOP();
                    }
#endif
#if (defined(FSL_FEATURE_SOC_USBNC_COUNT) && (FSL_FEATURE_SOC_USBNC_COUNT > 0U))
                    ehciInstance->registerNcBase->USB_OTGn_CTRL |= USBNC_USB_OTGn_CTRL_WKUP_ID_EN_MASK |
                                                                   USBNC_USB_OTGn_CTRL_WKUP_VBUS_EN_MASK |
                                                                   USBNC_USB_OTGn_CTRL_WKUP_DPDM_EN_MASK;
                    ehciInstance->registerNcBase->USB_OTGn_CTRL |= USBNC_USB_OTGn_CTRL_WIE_MASK;
#else
#if (defined(FSL_FEATURE_USB_ATLANTIC_EHCI_SUPPORT) && (FSL_FEATURE_USB_ATLANTIC_EHCI_SUPPORT > 0U))
#else
                    ehciInstance->ehciIpBase->USBGENCTRL = USBHS_USBGENCTRL_WU_IE_MASK;
#endif
#endif
#if ((defined FSL_FEATURE_SOC_USBPHY_COUNT) && (FSL_FEATURE_SOC_USBPHY_COUNT > 0U))
                    ehciInstance->registerPhyBase->CTRL |= USBPHY_CTRL_CLKGATE_MASK;
#endif
                    (void)hostPointer->deviceCallback(hostPointer->suspendedDevice, NULL,
                                                      kUSB_HostEventSuspended); /* call host callback function */
                    ehciInstance->busSuspendStatus = kBus_EhciSuspended;
                }
            }
        }
        else if (kBus_EhciStartResume == ehciInstance->busSuspendStatus)
        {
            usb_host_instance_t *hostPointer = (usb_host_instance_t *)ehciInstance->hostHandle;
            if (0U == (ehciInstance->ehciIpBase->PORTSC1 & USBHS_PORTSC1_FPR_MASK))
            {
                ehciInstance->ehciIpBase->PORTSC1 &= ~USBHS_PORTSC1_WKDS_MASK;
                if (0U != (ehciInstance->ehciIpBase->PORTSC1 & USBHS_PORTSC1_CCS_MASK))
                {
                    USB_HostEhciStartAsync(ehciInstance);
                    USB_HostEhciStartPeriodic(ehciInstance);
                }
                (void)hostPointer->deviceCallback(hostPointer->suspendedDevice, NULL,
                                                  kUSB_HostEventResumed); /* call host callback function */
                hostPointer->suspendedDevice   = NULL;
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
    osa_status_t osaStatus;
    usb_host_ehci_instance_t *ehciInstance;
    uint32_t usbhsBaseAddrs[] = USBHS_BASE_ADDRS;
    usb_host_ehci_data_t *usbHostEhciData[USB_HOST_CONFIG_EHCI];
    uint32_t *framePointer;
    void *temp;
    uint8_t instanceIndex = 0U;

    if ((controllerId - (uint8_t)kUSB_ControllerEhci0) >= (sizeof(usbhsBaseAddrs) / sizeof(usbhsBaseAddrs[0])))
    {
        return kStatus_USB_ControllerNotFound;
    }

    *controllerHandle = NULL;
    ehciInstance      = (usb_host_ehci_instance_t *)OSA_MemoryAllocate(
        sizeof(usb_host_ehci_instance_t)); /* malloc host ehci instance */
    if (ehciInstance == NULL)
    {
        return kStatus_USB_AllocFail;
    }
    ehciInstance->controllerId   = controllerId;
    ehciInstance->hostHandle     = upperLayerHandle;
    ehciInstance->deviceAttached = (uint8_t)kEHCIDeviceDetached;
    ehciInstance->ehciIpBase     = (USBHS_Type *)
        usbhsBaseAddrs[controllerId - (uint8_t)kUSB_ControllerEhci0]; /* operate ehci ip through the base address */
#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
    ehciInstance->busSuspendStatus = kBus_EhciIdle;

#if (defined(USB_HOST_CONFIG_LOW_POWER_MODE) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
#if ((defined FSL_FEATURE_SOC_USBPHY_COUNT) && (FSL_FEATURE_SOC_USBPHY_COUNT > 0U))
    ehciInstance->registerPhyBase = (USBPHY_Type *)USB_EhciPhyGetBase(controllerId);
#endif
#if (defined(FSL_FEATURE_SOC_USBNC_COUNT) && (FSL_FEATURE_SOC_USBNC_COUNT > 0U))
    ehciInstance->registerNcBase = (USBNC_Type *)USB_EhciNCGetBase(controllerId);
#endif

#endif

#endif

    if ((USB_HostEhciResetIP(ehciInstance) != kStatus_USB_Success) ||
        ((ehciInstance->controllerId < (uint8_t)kUSB_ControllerEhci0))) /* reset ehci ip */
    {
        OSA_MemoryFree(ehciInstance);
        return kStatus_USB_Error;
    }

#if (USB_HOST_CONFIG_EHCI == 1U)
    if (0U == usbHostEhciFramListStatus[0])
    {
        usbHostEhciFramListStatus[0] = 1U;
        instanceIndex                = 0U;
        ehciInstance->ehciFrameList  = &s_UsbHostEhciFrameList1[0];
    }
#elif (USB_HOST_CONFIG_EHCI == 2U)
    if (0U == usbHostEhciFramListStatus[0])
    {
        usbHostEhciFramListStatus[0] = 1U;
        instanceIndex                = 0U;
        ehciInstance->ehciFrameList  = &s_UsbHostEhciFrameList1[0];
    }
    else if (0U == usbHostEhciFramListStatus[1])
    {
        usbHostEhciFramListStatus[1] = 1U;
        instanceIndex                = 1U;
        ehciInstance->ehciFrameList  = &s_UsbHostEhciFrameList2[0];
    }
    else
    {
        /*no action*/
    }
#endif
    if (ehciInstance->ehciFrameList == NULL)
    {
        OSA_MemoryFree(ehciInstance);
        return kStatus_USB_Error;
    }

#if (USB_HOST_CONFIG_EHCI == 1U)
    usbHostEhciData[0] = &s_UsbHostEhciData1;
#elif (USB_HOST_CONFIG_EHCI == 2U)
    usbHostEhciData[0] = &s_UsbHostEhciData1;
    usbHostEhciData[1] = &s_UsbHostEhciData2;
#else
#error "Please increase the instance count."
#endif

    temp                       = (void *)usbHostEhciData[instanceIndex];
    ehciInstance->ehciUnitBase = (uint32_t *)(temp);
    /* initialize qh/qtd/itd/sitd/iso list */
    ehciInstance->ehciQhList  = (usb_host_ehci_qh_t *)((uint32_t)(ehciInstance->ehciUnitBase));
    ehciInstance->ehciQtdHead = (usb_host_ehci_qtd_t *)((uint32_t)ehciInstance->ehciQhList +
                                                        (sizeof(usb_host_ehci_qh_t) * USB_HOST_CONFIG_EHCI_MAX_QH));
    ehciInstance->ehciItdList = (usb_host_ehci_itd_t *)((uint32_t)ehciInstance->ehciQtdHead +
                                                        (sizeof(usb_host_ehci_qtd_t) * USB_HOST_CONFIG_EHCI_MAX_QTD));
#if ((defined(USB_HOST_CONFIG_EHCI_MAX_ITD)) && (USB_HOST_CONFIG_EHCI_MAX_ITD > 0U))
    /* If one ITD's first 32 bytes and next 32 bytes are in different 4K region,
     * the ITD need move 32 bytes because the ITD cannot cross over 4K boundary.
     */
    index = ((((((uint32_t)(ehciInstance->ehciItdList)) + 4095U) & 0xFFFFF000U) -
              ((uint32_t)(ehciInstance->ehciItdList))) >>
             5U);
    if (((index / 3U) < USB_HOST_CONFIG_EHCI_MAX_ITD) && ((index % 3U) == 1U))
    {
        ehciInstance->ehciItdList = (usb_host_ehci_itd_t *)(((uint32_t)(ehciInstance->ehciItdList)) + 32U);
    }
#endif
    ehciInstance->ehciSitdIndexBase =
        (usb_host_ehci_sitd_t *)((uint32_t)ehciInstance->ehciItdList +
                                 (sizeof(usb_host_ehci_itd_t) * USB_HOST_CONFIG_EHCI_MAX_ITD));
    ehciInstance->ehciSitdList = ehciInstance->ehciSitdIndexBase;
    ehciInstance->ehciIsoList  = (usb_host_ehci_iso_t *)((uint32_t)ehciInstance->ehciSitdList +
                                                        (sizeof(usb_host_ehci_sitd_t) * USB_HOST_CONFIG_EHCI_MAX_SITD));
    ehciInstance->ehciPipeIndexBase =
        (usb_host_ehci_pipe_t *)((uint32_t)ehciInstance->ehciIsoList +
                                 (sizeof(usb_host_ehci_iso_t) * USB_HOST_EHCI_ISO_NUMBER));
    for (index = 1U; index < USB_HOST_CONFIG_EHCI_MAX_QH; ++index)
    {
        ehciInstance->ehciQhList[index - 1U].horizontalLinkPointer = (uint32_t)(&ehciInstance->ehciQhList[index]);
    }
    ehciInstance->ehciQhList[USB_HOST_CONFIG_EHCI_MAX_QH - 1U].horizontalLinkPointer = 0U;
    for (index = 1; index < USB_HOST_CONFIG_EHCI_MAX_QTD; ++index)
    {
        ehciInstance->ehciQtdHead[index - 1U].nextQtdPointer = (uint32_t)(&ehciInstance->ehciQtdHead[index]);
    }
    ehciInstance->ehciQtdNumber                                                 = USB_HOST_CONFIG_EHCI_MAX_QTD;
    ehciInstance->ehciQtdHead[USB_HOST_CONFIG_EHCI_MAX_QTD - 1U].nextQtdPointer = 0U;
    ehciInstance->ehciQtdTail = &ehciInstance->ehciQtdHead[USB_HOST_CONFIG_EHCI_MAX_QTD - 1U];

#if ((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD))
    for (index = 1; index < USB_HOST_CONFIG_EHCI_MAX_ITD; ++index)
    {
        ehciInstance->ehciItdList[index - 1U].nextItdPointer =
            (usb_host_ehci_itd_t *)(&ehciInstance->ehciItdList[index]);
    }
    ehciInstance->ehciItdNumber                                                 = USB_HOST_CONFIG_EHCI_MAX_ITD;
    ehciInstance->ehciItdList[USB_HOST_CONFIG_EHCI_MAX_ITD - 1U].nextItdPointer = NULL;
#endif /* USB_HOST_CONFIG_EHCI_MAX_ITD */

#if ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD))
    for (index = 1; index < USB_HOST_CONFIG_EHCI_MAX_SITD; ++index)
    {
        ehciInstance->ehciSitdList[index - 1U].nextLinkPointer = (uint32_t)(&ehciInstance->ehciSitdList[index]);
    }
    ehciInstance->ehciSitdNumber                                                   = USB_HOST_CONFIG_EHCI_MAX_SITD;
    ehciInstance->ehciSitdList[USB_HOST_CONFIG_EHCI_MAX_SITD - 1U].nextLinkPointer = 0U;
#endif /* USB_HOST_CONFIG_EHCI_MAX_SITD */

#if ((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD))
    for (index = 1; index < USB_HOST_EHCI_ISO_NUMBER; ++index)
    {
        ehciInstance->ehciIsoList[index - 1U].next = &ehciInstance->ehciIsoList[index];
    }
    ehciInstance->ehciIsoList[USB_HOST_EHCI_ISO_NUMBER - 1U].next = NULL;
#endif

    /* initialize pipes */
    ehciInstance->ehciPipeList = ehciInstance->ehciPipeIndexBase;
    for (index = 1; index < USB_HOST_CONFIG_MAX_PIPES; ++index)
    {
        temp                                                   = (void *)&ehciInstance->ehciPipeList[index];
        ehciInstance->ehciPipeList[index - 1U].pipeCommon.next = (usb_host_pipe_t *)temp;
    }
    /* initialize mutext */
    ehciInstance->ehciMutex = (osa_mutex_handle_t)(&ehciInstance->mutexBuffer[0]);
    osaStatus               = OSA_MutexCreate(ehciInstance->ehciMutex);
    if (osaStatus != KOSA_StatusSuccess)
    {
#ifdef HOST_ECHO
        usb_echo("ehci mutex init fail\r\n");
#endif
        OSA_MemoryFree(ehciInstance);
        return kStatus_USB_Error;
    }
    /* initialize task event */
    ehciInstance->taskEventHandle = (osa_event_handle_t)&ehciInstance->taskEventHandleBuffer[0];
    osaStatus                     = OSA_EventCreate(ehciInstance->taskEventHandle, 1);
    if (osaStatus != KOSA_StatusSuccess)
    {
#ifdef HOST_ECHO
        usb_echo("ehci event init fail\r\n");
#endif
        (void)OSA_MutexDestroy(ehciInstance->ehciMutex);
        OSA_MemoryFree(ehciInstance);
        return kStatus_USB_Error;
    }

    /* initialize first qh */
    ehciInstance->shedFirstQh = ehciInstance->ehciQhList;
    ehciInstance->ehciQhList =
        (usb_host_ehci_qh_t *)(ehciInstance->ehciQhList->horizontalLinkPointer & EHCI_HOST_POINTER_ADDRESS_MASK);
    ehciInstance->shedFirstQh->staticEndpointStates[0] |= (1UL << EHCI_HOST_QH_H_SHIFT); /* first qh */
    ehciInstance->shedFirstQh->horizontalLinkPointer   = EHCI_HOST_T_INVALID_VALUE;
    ehciInstance->shedFirstQh->currentQtdPointer       = EHCI_HOST_T_INVALID_VALUE;
    ehciInstance->shedFirstQh->nextQtdPointer          = EHCI_HOST_T_INVALID_VALUE;
    ehciInstance->shedFirstQh->alternateNextQtdPointer = EHCI_HOST_T_INVALID_VALUE;
    ehciInstance->shedFirstQh->horizontalLinkPointer =
        (uint32_t)((uint32_t)(ehciInstance->shedFirstQh) | EHCI_HOST_POINTER_TYPE_QH);

    /* initialize periodic list */
    temp         = (void *)ehciInstance->ehciFrameList;
    framePointer = (uint32_t *)temp;
    for (index = 0; index < USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE; ++index)
    {
        framePointer[index] = EHCI_HOST_T_INVALID_VALUE;
    }

    (void)USB_HostEhciStartIP(ehciInstance); /* start ehci ip */

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
#if (USB_HOST_CONFIG_EHCI == 1U)
    if (ehciInstance->ehciFrameList == &s_UsbHostEhciFrameList1[0])
    {
        usbHostEhciFramListStatus[0] = 0;
    }
#elif (USB_HOST_CONFIG_EHCI == 2U)
    if (ehciInstance->ehciFrameList == &s_UsbHostEhciFrameList1[0])
    {
        usbHostEhciFramListStatus[0] = 0;
    }
    else if (ehciInstance->ehciFrameList == &s_UsbHostEhciFrameList2[0])
    {
        usbHostEhciFramListStatus[1] = 0;
    }
    else
    {
        /*no action*/
    }
#endif
    (void)OSA_MutexDestroy(ehciInstance->ehciMutex);
    (void)OSA_EventDestroy(ehciInstance->taskEventHandle);
    OSA_MemoryFree(ehciInstance);

    return kStatus_USB_Success;
}

usb_status_t USB_HostEhciOpenPipe(usb_host_controller_handle controllerHandle,
                                  usb_host_pipe_handle *pipeHandle,
                                  usb_host_pipe_init_t *pipeInit)
{
    usb_host_ehci_pipe_t *ehciPipePointer = NULL;
    usb_status_t status;
    uint32_t speed                         = 0;
    usb_host_ehci_instance_t *ehciInstance = (usb_host_ehci_instance_t *)controllerHandle;
    void *temp;
    /* get one pipe */
    USB_HostEhciLock();
    if (ehciInstance->ehciPipeList != NULL)
    {
        ehciPipePointer            = ehciInstance->ehciPipeList;
        temp                       = (void *)ehciPipePointer->pipeCommon.next;
        ehciInstance->ehciPipeList = (usb_host_ehci_pipe_t *)temp;
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
    USB_HostEhciZeroMem((void *)ehciPipePointer, sizeof(usb_host_ehci_pipe_t) / 4U);
    ehciPipePointer->pipeCommon.deviceHandle    = pipeInit->devInstance;
    ehciPipePointer->pipeCommon.endpointAddress = pipeInit->endpointAddress;
    ehciPipePointer->pipeCommon.direction       = pipeInit->direction;
    ehciPipePointer->pipeCommon.interval        = pipeInit->interval;
    ehciPipePointer->pipeCommon.maxPacketSize   = pipeInit->maxPacketSize;
    ehciPipePointer->pipeCommon.pipeType        = pipeInit->pipeType;
    ehciPipePointer->pipeCommon.numberPerUframe = pipeInit->numberPerUframe + 1U;
    if (ehciPipePointer->pipeCommon.numberPerUframe > 3U)
    {
        ehciPipePointer->pipeCommon.numberPerUframe = 3U;
    }
    ehciPipePointer->pipeCommon.nakCount   = pipeInit->nakCount;
    ehciPipePointer->pipeCommon.nextdata01 = 0U;
    ehciPipePointer->ehciQh                = NULL;
    (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                 (uint32_t)kUSB_HostGetDeviceSpeed, &speed);
    if ((ehciPipePointer->pipeCommon.pipeType == USB_ENDPOINT_ISOCHRONOUS) ||
        (ehciPipePointer->pipeCommon.pipeType == USB_ENDPOINT_INTERRUPT))
    {
        if (ehciPipePointer->pipeCommon.pipeType == USB_ENDPOINT_ISOCHRONOUS)
        {
            ehciPipePointer->pipeCommon.interval =
                (uint16_t)(1UL << (ehciPipePointer->pipeCommon.interval - 1U)); /* iso interval is the power of 2 */
        }
        else
        {
            if (speed == USB_SPEED_HIGH)
            {
                ehciPipePointer->pipeCommon.interval = (uint16_t)(
                    1UL << (ehciPipePointer->pipeCommon.interval - 1U)); /* HS interrupt interval is the power of 2 */
            }
            else
            {
                ehciPipePointer->pipeCommon.interval = USB_HostEhciGet2PowerValue(
                    (uint8_t)ehciPipePointer->pipeCommon.interval); /* FS/LS interrupt interval should be the power of
                                                              2, it is used for ehci bandwidth */
            }
        }
    }

    /* save the micro-frame interval, it is convenient for the interval process */
    if (speed == USB_SPEED_HIGH)
    {
        ehciPipePointer->uframeInterval = ehciPipePointer->pipeCommon.interval;
    }
    else
    {
        ehciPipePointer->uframeInterval = 8U * ehciPipePointer->pipeCommon.interval;
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
        temp                             = (void *)ehciInstance->ehciPipeList;
        ehciPipePointer->pipeCommon.next = (usb_host_pipe_t *)temp;
        ehciInstance->ehciPipeList       = ehciPipePointer;
        USB_HostEhciUnlock();
        return status;
    }

    /* add pipe to run pipe list */
    USB_HostEhciLock();
    temp                              = (void *)ehciInstance->ehciRunningPipeList;
    ehciPipePointer->pipeCommon.next  = (usb_host_pipe_t *)temp;
    ehciInstance->ehciRunningPipeList = ehciPipePointer;
    USB_HostEhciUnlock();

    *pipeHandle = ehciPipePointer;
    return status;
}

usb_status_t USB_HostEhciClosePipe(usb_host_controller_handle controllerHandle, usb_host_pipe_handle pipeHandle)
{
    usb_host_ehci_instance_t *ehciInstance = (usb_host_ehci_instance_t *)controllerHandle;
    usb_host_ehci_pipe_t *ehciPipePointer  = (usb_host_ehci_pipe_t *)pipeHandle;
    usb_host_pipe_t *prevPointer           = NULL;
    void *temp;
    void *tempCurrent;

    switch (ehciPipePointer->pipeCommon.pipeType)
    {
        case USB_ENDPOINT_BULK:
        case USB_ENDPOINT_CONTROL:
            (void)USB_HostEhciCloseControlBulk(ehciInstance, ehciPipePointer);
            break;

        case USB_ENDPOINT_INTERRUPT:
            (void)USB_HostEhciCloseInterrupt(ehciInstance, ehciPipePointer);
            break;

#if (((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD)) || \
     ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD)))
        case USB_ENDPOINT_ISOCHRONOUS:
            (void)USB_HostEhciCloseIso(ehciInstance, ehciPipePointer);
            break;
#endif

        default:
            /*no action*/
            break;
    }

    /* delete pipe from run pipe list */
    USB_HostEhciLock();
    temp        = (void *)ehciInstance->ehciRunningPipeList;
    prevPointer = (usb_host_pipe_t *)temp;
    tempCurrent = (void *)ehciPipePointer;
    if (prevPointer == (usb_host_pipe_t *)tempCurrent)
    {
        temp                              = (void *)prevPointer->next;
        ehciInstance->ehciRunningPipeList = (usb_host_ehci_pipe_t *)(temp);
    }
    else
    {
        while (prevPointer != NULL)
        {
            temp = (void *)ehciPipePointer;
            if (prevPointer->next == (usb_host_pipe_t *)temp)
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
    temp                             = (void *)ehciInstance->ehciPipeList;
    ehciPipePointer->pipeCommon.next = (usb_host_pipe_t *)temp;
    ehciInstance->ehciPipeList       = ehciPipePointer;
    USB_HostEhciUnlock();

    return kStatus_USB_Success;
}

usb_status_t USB_HostEhciWritePipe(usb_host_controller_handle controllerHandle,
                                   usb_host_pipe_handle pipeHandle,
                                   usb_host_transfer_t *transfer)
{
    usb_host_ehci_instance_t *ehciInstance = (usb_host_ehci_instance_t *)controllerHandle;
    usb_host_ehci_pipe_t *ehciPipePointer  = (usb_host_ehci_pipe_t *)pipeHandle;
    usb_status_t status                    = kStatus_USB_Success;
#if (((defined USB_HOST_CONFIG_EHCI_MAX_ITD) && (USB_HOST_CONFIG_EHCI_MAX_ITD)) || \
     ((defined USB_HOST_CONFIG_EHCI_MAX_SITD) && (USB_HOST_CONFIG_EHCI_MAX_SITD)))
    uint32_t speed = 0U;
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
            (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                         (uint32_t)kUSB_HostGetDeviceSpeed, &speed);
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
            /*no action*/
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
    usb_status_t status                    = kStatus_USB_Success;
    usb_host_ehci_instance_t *ehciInstance = (usb_host_ehci_instance_t *)controllerHandle;
    usb_host_cancel_param_t *param;
    usb_host_ehci_pipe_t *ehciPipePointer;
    volatile usb_host_ehci_qh_t *vltQhPointer;
    uint32_t deviceAddress                    = 0;
    usb_host_controller_control_t controlCode = (usb_host_controller_control_t)ioctlEvent;
    if (controllerHandle == NULL)
    {
        return kStatus_USB_InvalidHandle;
    }

    switch (controlCode)
    {
        case kUSB_HostCancelTransfer: /* cancel pipe or one transfer */
            param  = (usb_host_cancel_param_t *)ioctlParam;
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
            vltQhPointer    = (volatile usb_host_ehci_qh_t *)ehciPipePointer->ehciQh;
            /* update address */
            (void)USB_HostHelperGetPeripheralInformation(ehciPipePointer->pipeCommon.deviceHandle,
                                                         (uint32_t)kUSB_HostGetDeviceAddress, &deviceAddress);
            vltQhPointer->staticEndpointStates[0] |= deviceAddress;
            USB_HostEhciDelay(ehciInstance->ehciIpBase, 2U);
            break;

        case kUSB_HostUpdateControlPacketSize:
            ehciPipePointer = (usb_host_ehci_pipe_t *)ioctlParam;
            vltQhPointer    = (volatile usb_host_ehci_qh_t *)ehciPipePointer->ehciQh;
            USB_HostEhciLock();
            if (0U != (ehciInstance->ehciIpBase->USBSTS & USBHS_USBSTS_AS_MASK))
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
#if ((defined USB_HOST_CONFIG_COMPLIANCE_TEST) && (USB_HOST_CONFIG_COMPLIANCE_TEST))
        case kUSB_HostTestModeInit: /* test mode control */
            USB_HostEhciTestModeInit((usb_host_device_instance_t *)ioctlParam);
            break;
#endif
        default:
            status = kStatus_USB_NotSupported;
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

    if (OSA_EventWait(ehciInstance->taskEventHandle, 0xFF, 0, USB_OSA_WAIT_TIMEOUT, &bitSet) ==
        KOSA_StatusSuccess) /* wait all event */
    {
        if (0U != (bitSet & EHCI_TASK_EVENT_PORT_CHANGE)) /* port change */
        {
            USB_HostEhciPortChange(ehciInstance);
        }

        if (0U != (bitSet & EHCI_TASK_EVENT_TIMER0)) /* timer0 */
        {
            USB_HostEhciTimer0(ehciInstance);
        }

#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
        if (0U != (bitSet & EHCI_TASK_EVENT_TIMER1)) /* timer1 */
        {
            USB_HostEhciTimer1(ehciInstance);
        }
#endif

        if ((ehciInstance->deviceAttached == (uint8_t)kEHCIDeviceAttached))
        {
            if (0U != (bitSet & EHCI_TASK_EVENT_TRANSACTION_DONE)) /* transaction done */
            {
                USB_HostEhciTransactionDone(ehciInstance);
            }

            if (0U != (bitSet & EHCI_TASK_EVENT_DEVICE_DETACH)) /* device detach */
            {
                ehciInstance->ehciIpBase->USBINTR &=
                    (~USBHS_USBINTR_PCE_MASK); /* disable attach, enable when the detach process is done */
                ehciInstance->deviceAttached = (uint8_t)kEHCIDeviceDetached;
                (void)USB_HostDetachDevice(ehciInstance->hostHandle, 0, 0);
            }
        }
        else if (ehciInstance->deviceAttached != (uint8_t)kEHCIDeviceAttached)
        {
            if (0U != (bitSet & EHCI_TASK_EVENT_DEVICE_ATTACH)) /* device is attached */
            {
                USB_HostEhciStartAsync(ehciInstance);
                USB_HostEhciStartPeriodic(ehciInstance);

                if (USB_HostAttachDevice(ehciInstance->hostHandle, ehciInstance->firstDeviceSpeed, 0, 0, 1,
                                         &deviceHandle) == kStatus_USB_Success)
                {
                    ehciInstance->deviceAttached = (uint8_t)kEHCIDeviceAttached;
                }
            }
        }
        else
        {
            /*no action*/
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
    if (0U != (ehciInstance->registerNcBase->USB_OTGn_CTRL & USBNC_USB_OTGn_CTRL_WIE_MASK))
    {
        usb_host_instance_t *hostPointer = (usb_host_instance_t *)ehciInstance->hostHandle;
        ehciInstance->registerNcBase->USB_OTGn_CTRL &= ~USBNC_USB_OTGn_CTRL_WIE_MASK;
        (void)hostPointer->deviceCallback(hostPointer->suspendedDevice, NULL,
                                          kUSB_HostEventDetectResume); /* call host callback function */
#if (defined(USBNC_USB_OTGn_PHY_CTRL_0_UTMI_CLK_VLD_MASK))
        while (0U == (ehciInstance->registerNcBase->USB_OTGn_PHY_CTRL_0 & USBNC_USB_OTGn_PHY_CTRL_0_UTMI_CLK_VLD_MASK))
        {
        }
#endif
        if (0U != (ehciInstance->ehciIpBase->PORTSC1 & USBHS_PORTSC1_CCS_MASK))
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
            /*no action*/
        }
    }
    else
    {
        /*no action*/
    }
#else
#if (defined(FSL_FEATURE_USB_ATLANTIC_EHCI_SUPPORT) && (FSL_FEATURE_USB_ATLANTIC_EHCI_SUPPORT > 0U))
#else
    if (0U != (ehciInstance->ehciIpBase->USBGENCTRL & USBHS_USBGENCTRL_WU_IE_MASK))
    {
        usb_host_instance_t *hostPointer = (usb_host_instance_t *)ehciInstance->hostHandle;

        (void)hostPointer->deviceCallback(hostPointer->suspendedDevice, NULL,
                                          kUSB_HostEventDetectResume); /* call host callback function */

        while (0U == (USBPHY->PLL_SIC & USBPHY_PLL_SIC_PLL_LOCK_MASK))
        {
        }
        ehciInstance->ehciIpBase->USBGENCTRL |= USBHS_USBGENCTRL_WU_INT_CLR_MASK;
        ehciInstance->ehciIpBase->USBGENCTRL &= ~USBHS_USBGENCTRL_WU_IE_MASK;
        if (0U != (ehciInstance->ehciIpBase->PORTSC1 & USBHS_PORTSC1_CCS_MASK))
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
            /*no action*/
        }
    }
    else
    {
        /*no action*/
    }
#endif /* FSL_FEATURE_USB_ATLANTIC_EHCI_SUPPORT */
#endif /* FSL_FEATURE_SOC_USBNC_COUNT */
#endif /* USB_HOST_CONFIG_LOW_POWER_MODE */

    interruptStatus = ehciInstance->ehciIpBase->USBSTS;
    interruptStatus &= ehciInstance->ehciIpBase->USBINTR;
    while (0U != interruptStatus) /* there are usb interrupts */
    {
        ehciInstance->ehciIpBase->USBSTS = interruptStatus; /* clear interrupt */

        if (0U != (interruptStatus & USBHS_USBSTS_SRI_MASK)) /* SOF interrupt */
        {
        }

        if (0U != (interruptStatus & USBHS_USBSTS_SEI_MASK)) /* system error interrupt */
        {
        }

        if ((0U != (interruptStatus & USBHS_USBSTS_UI_MASK)) ||
            (0U != (interruptStatus & USBHS_USBSTS_UEI_MASK))) /* USB interrupt or USB error interrupt */
        {
            (void)OSA_EventSet(ehciInstance->taskEventHandle, EHCI_TASK_EVENT_TRANSACTION_DONE);
        }

        if (0U != (interruptStatus & USBHS_USBSTS_PCI_MASK)) /* port change detect interrupt */
        {
#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
            usb_host_instance_t *hostPointer = (usb_host_instance_t *)ehciInstance->hostHandle;
            if (0U != (ehciInstance->ehciIpBase->PORTSC1 & USBHS_PORTSC1_FPR_MASK))
            {
                if (kBus_EhciStartSuspend == ehciInstance->busSuspendStatus)
                {
                    if (0U != (ehciInstance->ehciIpBase->PORTSC1 & USBHS_PORTSC1_CCS_MASK))
                    {
                        USB_HostEhciStartAsync(ehciInstance);
                        USB_HostEhciStartPeriodic(ehciInstance);
                    }
                    (void)hostPointer->deviceCallback(hostPointer->suspendedDevice, NULL,
                                                      kUSB_HostEventNotSuspended); /* call host callback function */
                    hostPointer->suspendedDevice   = NULL;
                    ehciInstance->busSuspendStatus = kBus_EhciIdle;
                    ehciInstance->ehciIpBase->USBINTR &= ~(USBHS_USBINTR_TIE1_MASK);
                }
                else
                {
                    /*no action */
                }
            }
#if (defined(FSL_FEATURE_USB_ATLANTIC_EHCI_SUPPORT) && (FSL_FEATURE_USB_ATLANTIC_EHCI_SUPPORT > 0U))
            if ((kBus_EhciSuspended == ehciInstance->busSuspendStatus))
            {
                usb_host_instance_t *hostPointer = (usb_host_instance_t *)ehciInstance->hostHandle;

                (void)hostPointer->deviceCallback(hostPointer->suspendedDevice, NULL,
                                                  kUSB_HostEventDetectResume); /* call host callback function */

                uint32_t delay = 100000;
                while (delay-- && !(USBOTG->PLL_CONTROL_0 & USBC_PLL_CONTROL_0_PLL_READY_MASK))
                {
                }
                if (0U != (ehciInstance->ehciIpBase->PORTSC1 & USBHS_PORTSC1_CCS_MASK))
                {
                    USB_HostEhciStartAsync(ehciInstance);
                    USB_HostEhciStartPeriodic(ehciInstance);
                }
                ehciInstance->ehciIpBase->USBCMD |= (USBHS_USBCMD_RS_MASK);
                ehciInstance->busSuspendStatus = kBus_EhciStartResume;
            }
#endif
#endif
            (void)OSA_EventSet(ehciInstance->taskEventHandle, EHCI_TASK_EVENT_PORT_CHANGE);
        }

        if (0U != (interruptStatus & USBHS_USBSTS_TI0_MASK)) /* timer 0 interrupt */
        {
            (void)OSA_EventSet(ehciInstance->taskEventHandle, EHCI_TASK_EVENT_TIMER0);
        }

#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
        if (0U != (interruptStatus & USBHS_USBSTS_TI1_MASK)) /* timer 1 interrupt */
        {
            (void)OSA_EventSet(ehciInstance->taskEventHandle, EHCI_TASK_EVENT_TIMER1);
        }
#endif

        interruptStatus = ehciInstance->ehciIpBase->USBSTS;
        interruptStatus &= ehciInstance->ehciIpBase->USBINTR;
    }
}

#endif /* USB_HOST_CONFIG_EHCI */
