/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016,2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _USB_HOST_CONTROLLER_EHCI_H_
#define _USB_HOST_CONTROLLER_EHCI_H_

/*******************************************************************************
 * KHCI private public structures, enumerations, macros, functions
 ******************************************************************************/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* EHCI host macros */
#define EHCI_HOST_T_INVALID_VALUE      (1U)
#define EHCI_HOST_POINTER_TYPE_ITD     (0x00U)
#define EHCI_HOST_POINTER_TYPE_QH      (0x00000002U)
#define EHCI_HOST_POINTER_TYPE_SITD    (0x00000004U)
#define EHCI_HOST_POINTER_TYPE_FSTN    (0x00000006U)
#define EHCI_HOST_POINTER_TYPE_MASK    (0x00000006U)
#define EHCI_HOST_POINTER_ADDRESS_MASK (0xFFFFFFE0U)
#define EHCI_HOST_PID_OUT              (0UL)
#define EHCI_HOST_PID_IN               (1UL)
#define EHCI_HOST_PID_SETUP            (2UL)

#define EHCI_HOST_QH_RL_SHIFT                  (28U)
#define EHCI_HOST_QH_RL_MASK                   (0xF0000000U)
#define EHCI_HOST_QH_C_SHIFT                   (27U)
#define EHCI_HOST_QH_MAX_PACKET_LENGTH_SHIFT   (16U)
#define EHCI_HOST_QH_MAX_PACKET_LENGTH_MASK    (0x07FF0000U)
#define EHCI_HOST_QH_H_SHIFT                   (15U)
#define EHCI_HOST_QH_DTC_SHIFT                 (14U)
#define EHCI_HOST_QH_EPS_SHIFT                 (12U)
#define EHCI_HOST_QH_ENDPT_SHIFT               (8U)
#define EHCI_HOST_QH_I_SHIFT                   (7U)
#define EHCI_HOST_QH_DEVICE_ADDRESS_SHIFT      (0U)
#define EHCI_HOST_QH_MULT_SHIFT                (30U)
#define EHCI_HOST_QH_PORT_NUMBER_SHIFT         (23U)
#define EHCI_HOST_QH_HUB_ADDR_SHIFT            (16U)
#define EHCI_HOST_QH_UFRAME_CMASK_SHIFT        (8U)
#define EHCI_HOST_QH_UFRAME_SMASK_SHIFT        (0U)
#define EHCI_HOST_QH_STATUS_ERROR_MASK         (0x0000007EU)
#define EHCI_HOST_QH_STATUS_NOSTALL_ERROR_MASK (0x0000003EU)

#define EHCI_HOST_QTD_DT_SHIFT                (31U)
#define EHCI_HOST_QTD_DT_MASK                 (0x80000000U)
#define EHCI_HOST_QTD_TOTAL_BYTES_SHIFT       (16U)
#define EHCI_HOST_QTD_TOTAL_BYTES_MASK        (0x7FFF0000U)
#define EHCI_HOST_QTD_IOC_MASK                (0x00008000U)
#define EHCI_HOST_QTD_C_PAGE_SHIFT            (12U)
#define EHCI_HOST_QTD_CERR_SHIFT              (10U)
#define EHCI_HOST_QTD_CERR_MAX_VALUE          (0x00000003UL)
#define EHCI_HOST_QTD_PID_CODE_SHIFT          (8U)
#define EHCI_HOST_QTD_STATUS_SHIFT            (0U)
#define EHCI_HOST_QTD_CURRENT_OFFSET_MASK     (0x00000FFFU)
#define EHCI_HOST_QTD_BUFFER_POINTER_SHIFT    (12U)
#define EHCI_HOST_QTD_STATUS_ACTIVE_MASK      (0x00000080U)
#define EHCI_HOST_QTD_STATUS_MASK             (0x000000ffU)
#define EHCI_HOST_QTD_STATUS_ERROR_MASK       (0x0000007EU)
#define EHCI_HOST_QTD_STATUS_STALL_ERROR_MASK (0x00000040U)

#define EHCI_HOST_ITD_STATUS_ACTIVE_MASK       (0x80000000U)
#define EHCI_HOST_ITD_TRANSACTION_LEN_SHIFT    (16U)
#define EHCI_HOST_ITD_TRANSACTION_LEN_MASK     (0x0FFF0000U)
#define EHCI_HOST_ITD_IOC_SHIFT                (15U)
#define EHCI_HOST_ITD_PG_SHIFT                 (12U)
#define EHCI_HOST_ITD_TRANSACTION_OFFSET_SHIFT (0U)
#define EHCI_HOST_ITD_TRANSACTION_OFFSET_MASK  (0x00000FFFU)
#define EHCI_HOST_ITD_BUFFER_POINTER_SHIFT     (12U)
#define EHCI_HOST_ITD_ENDPT_SHIFT              (8U)
#define EHCI_HOST_ITD_DEVICE_ADDRESS_SHIFT     (0U)
#define EHCI_HOST_ITD_MAX_PACKET_SIZE_SHIFT    (0U)
#define EHCI_HOST_ITD_MULT_SHIFT               (0U)
#define EHCI_HOST_ITD_DIRECTION_SHIFT          (11U)

#define EHCI_HOST_SITD_STATUS_ACTIVE_MASK   (0x00000080U)
#define EHCI_HOST_SITD_DIRECTION_SHIFT      (31U)
#define EHCI_HOST_SITD_PORT_NUMBER_SHIFT    (24U)
#define EHCI_HOST_SITD_HUB_ADDR_SHIFT       (16U)
#define EHCI_HOST_SITD_ENDPT_SHIFT          (8U)
#define EHCI_HOST_SITD_DEVICE_ADDRESS_SHIFT (0U)
#define EHCI_HOST_SITD_CMASK_SHIFT          (8U)
#define EHCI_HOST_SITD_SMASK_SHIFT          (0U)
#define EHCI_HOST_SITD_TOTAL_BYTES_SHIFT    (16U)
#define EHCI_HOST_SITD_TOTAL_BYTES_MASK     (0x03FF0000U)
#define EHCI_HOST_SITD_TP_SHIFT             (3U)
#define EHCI_HOST_SITD_TCOUNT_SHIFT         (0U)
#define EHCI_HOST_SITD_IOC_SHIFT            (31U)

/* register related MACROs */
#define EHCI_PORTSC1_W1_BITS  (0x0000002AU)
#define EHCI_MAX_UFRAME_VALUE (0x00003FFFU)

/* task event */
#define EHCI_TASK_EVENT_DEVICE_ATTACH    (0x01U)
#define EHCI_TASK_EVENT_TRANSACTION_DONE (0x02U)
#define EHCI_TASK_EVENT_DEVICE_DETACH    (0x04U)
#define EHCI_TASK_EVENT_PORT_CHANGE      (0x08U)
#define EHCI_TASK_EVENT_TIMER0           (0x10U)
#define EHCI_TASK_EVENT_TIMER1           (0x20U)

#define USB_HostEhciLock()   (void)OSA_MutexLock(ehciInstance->ehciMutex, USB_OSA_WAIT_TIMEOUT)
#define USB_HostEhciUnlock() (void)OSA_MutexUnlock(ehciInstance->ehciMutex)

/*******************************************************************************
 * KHCI driver public structures, enumerations, macros, functions
 ******************************************************************************/

/*!
 * @addtogroup usb_host_controller_ehci
 * @{
 */

/*! @brief The maximum supported ISO pipe number */
#define USB_HOST_EHCI_ISO_NUMBER USB_HOST_CONFIG_EHCI_MAX_ITD
/*! @brief Check the port connect state delay if the state is unstable */
#define USB_HOST_EHCI_PORT_CONNECT_DEBOUNCE_DELAY (101U)
/*! @brief Delay for port reset */
#define USB_HOST_EHCI_PORT_RESET_DELAY (11U)
/*! @brief The MAX continuous transfers that application can send. */
#define USB_HOST_EHCI_ISO_MAX_CONTINUOUS_TRANSFER (8U)
/*! @brief The SITD inserts a frame interval for putting more SITD continuously.
 * There is an interval when an application sends two FS/LS ISO transfers.
 * When the interval is less than the macro, the two transfers are continuous in the frame list. Otherwise, the two
 * transfers
 * are not continuous.
 * For example:
 * - Use case 1: when inserting the SITD first, the inserted frame = the current frame value + this MACRO value.
 * - Use case 2: when inserting SITD is not first, choose between the last inserted frame value and the
 * current frame value according to the following criteria:
 *           If the interval is less than the MACRO value, the new SITD is continuous with the last SITD.
 *           If not, the new SITD inserting frame = the current frame value + this MACRO value.
 */
#define USB_HOST_EHCI_ISO_BOUNCE_FRAME_NUMBER (2U)
/*! @brief The ITD inserts a micro-frame interval for putting more ITD continuously.
 * There is an interval when an application sends two HS ISO transfers.
 * When the interval is less than the macro, the two transfers are continuous in the frame list. Otherwise, the two
 * transfers
 * are not continuous.
 * For example:
 * - Use case 1: when inserting ITD first, the inserted micro-frame = the current micro-frame value + this MACRO value.
 * - Use case 2: when inserting ITD is not first, choose between the last inserted micro-frame value and the
 * current micro-frame value according to the following criteria:
 *           If the interval is less than this MACRO value, the new ITD is continuous with the last ITD.
 *           If not, the new ITD inserting micro-frame = the current micro-frame value + this MACRO value.
 */
#define USB_HOST_EHCI_ISO_BOUNCE_UFRAME_NUMBER (16U)
/*! @brief Control or bulk transaction timeout value (unit: 100 ms) */
#define USB_HOST_EHCI_CONTROL_BULK_TIME_OUT_VALUE (50U)

#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
typedef enum _bus_ehci_suspend_request_state
{
    kBus_EhciIdle = 0U,
    kBus_EhciStartSuspend,
    kBus_EhciSuspended,
    kBus_EhciStartResume,
} bus_ehci_suspend_request_state_t;
#endif

/*! @brief EHCI state for device attachment/detachment. */
typedef enum _host_ehci_device_state_
{
    kEHCIDevicePhyAttached = 1, /*!< Device is physically attached */
    kEHCIDeviceAttached,        /*!< Device is attached and initialized */
    kEHCIDeviceDetached,        /*!< Device is detached and de-initialized */
} host_ehci_device_state_t;

/*! @brief EHCI pipe structure */
typedef struct _usb_host_ehci_pipe
{
    usb_host_pipe_t pipeCommon; /*!< Common pipe information */
    void *ehciQh;               /*!< Control/bulk/interrupt: QH; ISO: usb_host_ehci_iso_t*/

    /* bandwidth */
    uint16_t uframeInterval;    /*!< Micro-frame interval value */
    uint16_t startFrame;        /*!<
                                     Bandwidth start frame: its value is from 0 to frame_list.
                                 */
    uint16_t dataTime;          /*!<
                                     Bandwidth time value:
                                     - When the host works as HS: it's the data bandwidth value.
                                     - When the host works as FS/LS:
                                         - For FS/LS device, it's the data bandwidth value when transferring the data by FS/LS.
                                         - For HS device, it's the data bandwidth value when transferring the data by HS.
                                 */
    uint16_t startSplitTime;    /*!<
                                      Start splitting the bandwidth time value:
                                      - When the host works as HS, it is the start split bandwidth value.
                                  */
    uint16_t completeSplitTime; /*!<
                                      Complete splitting the bandwidth time value:
                                      - When host works as HS, it is the complete split bandwidth value.
                                  */
    uint8_t startUframe;        /*!<
                                     Bandwidth start micro-frame: its value is from 0 to 7.
                                 */
    uint8_t uframeSmask;        /*!<
                                     Start micro-frame.
                                     - When host works as an HS:
                                        - For FS/LS device, it's the interrupt or ISO transfer start-split mask.
                                         - For HS device, it's the interrupt transfer start micro-frame mask.
                                     - When host works as FS/LS, it's the interrupt and ISO start micro-frame mask
                                 */
    uint8_t uframeCmask;        /*!<
                                     Complete micro-frame
                                     - When host works as HS:
                                         - For FS/LS device, it's the interrupt or ISO transfer complete-split mask.
                                 */
} usb_host_ehci_pipe_t;

/*! @brief EHCI QH structure. See the USB EHCI specification */
typedef struct _usb_host_ehci_qh
{
    uint32_t horizontalLinkPointer; /*!< QH specification filed, queue head a horizontal link pointer */
    uint32_t
        staticEndpointStates[2]; /*!< QH specification filed, static endpoint state and configuration information */
    uint32_t currentQtdPointer;  /*!< QH specification filed, current qTD pointer */
    uint32_t nextQtdPointer;     /*!< QH specification filed, next qTD pointer */
    uint32_t alternateNextQtdPointer; /*!< QH specification filed, alternate next qTD pointer */
    uint32_t
        transferOverlayResults[6]; /*!< QH specification filed, transfer overlay configuration and transfer results */

    /* reserved space */
    usb_host_ehci_pipe_t *ehciPipePointer; /*!< EHCI pipe pointer */
    usb_host_transfer_t *ehciTransferHead; /*!< Transfer list head on this QH */
    usb_host_transfer_t *ehciTransferTail; /*!< Transfer list tail on this QH */
    uint16_t timeOutValue; /*!< Its maximum value is USB_HOST_EHCI_CONTROL_BULK_TIME_OUT_VALUE. When the value is
                                zero, the transfer times out. */
    uint16_t timeOutLabel; /*!< It's used to judge the transfer timeout. The EHCI driver maintain the value */
} usb_host_ehci_qh_t;

/*! @brief EHCI QTD structure. See the USB EHCI specification. */
typedef struct _usb_host_ehci_qtd
{
    uint32_t nextQtdPointer;          /*!< QTD specification filed, the next QTD pointer */
    uint32_t alternateNextQtdPointer; /*!< QTD specification filed, alternate next QTD pointer */
    uint32_t transferResults[2];      /*!< QTD specification filed, transfer results fields */
    uint32_t bufferPointers[4];       /*!< QTD specification filed, transfer buffer fields */
} usb_host_ehci_qtd_t;

/*! @brief EHCI ITD structure. See the USB EHCI specification. */
typedef struct _usb_host_ehci_itd
{
    uint32_t nextLinkPointer;   /*!< ITD specification filed, the next linker pointer */
    uint32_t transactions[8];   /*!< ITD specification filed, transactions information */
    uint32_t bufferPointers[7]; /*!< ITD specification filed, transfer buffer fields */

    /* add space */
    struct _usb_host_ehci_itd *nextItdPointer; /*!< Next ITD pointer */
    uint32_t frameEntryIndex;                  /*!< The ITD inserted frame value */
    uint32_t reserved[6];                      /*!< Reserved fields for 32 bytes align */
} usb_host_ehci_itd_t;

/*! @brief EHCI SITD structure. See the USB EHCI specification. */
typedef struct _usb_host_ehci_sitd
{
    uint32_t nextLinkPointer;    /*!< SITD specification filed, the next linker pointer */
    uint32_t endpointStates[2];  /*!< SITD specification filed, endpoint configuration information */
    uint32_t transferResults[3]; /*!< SITD specification filed, transfer result fields */
    uint32_t backPointer;        /*!< SITD specification filed, back pointer */

    /* reserved space */
    uint16_t frameEntryIndex; /*!< The SITD inserted frame value */
    uint8_t nextSitdIndex;    /*!< The next SITD index; Get the next SITD pointer through adding base address with the
                                 index. 0xFF means invalid. */
    uint8_t reserved;         /*!< Reserved fields for 32 bytes align */
} usb_host_ehci_sitd_t;

/*! @brief EHCI ISO structure; An ISO pipe has an instance of this structure to keep the ISO pipe-specific information.
 */
typedef struct _usb_host_ehci_iso
{
    struct _usb_host_ehci_iso *next;       /*!< Next instance pointer */
    usb_host_pipe_t *ehciPipePointer;      /*!< This ISO's EHCI pipe pointer */
    usb_host_transfer_t *ehciTransferHead; /*!< Transfer list head on this ISO pipe */
    usb_host_transfer_t *ehciTransferTail; /*!< Transfer list head on this ISO pipe */

    uint16_t lastLinkFrame; /*!< It means that the inserted frame for ISO ITD/SITD. 0xFFFF is invalid. For ITD, it is a
                               micro-frame value. For SITD, it is a frame value */
} usb_host_ehci_iso_t;

/*! @brief EHCI instance structure */
typedef struct _usb_host_ehci_instance
{
    usb_host_handle hostHandle;                /*!< Related host handle*/
    uint32_t *ehciUnitBase;                    /*!< Keep the QH/QTD/ITD/SITD buffer pointer for release*/
    uint8_t *ehciFrameList;                    /*!< The frame list of the current ehci instance*/
    usb_host_ehci_qh_t *ehciQhList;            /*!< Idle QH list pointer */
    usb_host_ehci_qtd_t *ehciQtdHead;          /*!< Idle QTD list pointer head */
    usb_host_ehci_qtd_t *ehciQtdTail;          /*!< Idle QTD list pointer tail (recently used qTD will be used)*/
    usb_host_ehci_itd_t *ehciItdList;          /*!< Idle ITD list pointer*/
    usb_host_ehci_sitd_t *ehciSitdIndexBase;   /*!< SITD buffer's start pointer*/
    usb_host_ehci_sitd_t *ehciSitdList;        /*!< Idle SITD list pointer*/
    usb_host_ehci_iso_t *ehciIsoList;          /*!< Idle ISO list pointer*/
    USBHS_Type *ehciIpBase;                    /*!< EHCI IP base address*/
    usb_host_ehci_qh_t *shedFirstQh;           /*!< First async QH*/
    usb_host_ehci_pipe_t *ehciPipeIndexBase;   /*!< Pipe buffer's start pointer*/
    usb_host_ehci_pipe_t *ehciPipeList;        /*!< Idle pipe list pointer*/
    usb_host_ehci_pipe_t *ehciRunningPipeList; /*!< Running pipe list pointer*/
    osa_mutex_handle_t ehciMutex;              /*!< EHCI mutex*/
    uint32_t mutexBuffer[(OSA_MUTEX_HANDLE_SIZE + 3) / 4];           /*!< The mutex buffer. */
    osa_event_handle_t taskEventHandle;                              /*!< EHCI task event*/
    uint32_t taskEventHandleBuffer[(OSA_EVENT_HANDLE_SIZE + 3) / 4]; /*!< EHCI task event handle buffer*/
#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
    uint64_t matchTick;
    USBPHY_Type *registerPhyBase; /*!< The base address of the PHY register */
#if (defined(FSL_FEATURE_SOC_USBNC_COUNT) && (FSL_FEATURE_SOC_USBNC_COUNT > 0U))
    USBNC_Type *registerNcBase; /*!< The base address of the USBNC register */
#endif

#endif
    uint8_t controllerId;     /*!< EHCI controller ID*/
    uint8_t deviceAttached;   /*!< Device attach/detach state, see #host_ehci_device_state_t */
    uint8_t firstDeviceSpeed; /*!< The first device's speed, the controller's work speed*/
    uint8_t ehciItdNumber;    /*!< Idle ITD number*/
    uint8_t ehciSitdNumber;   /*!< Idle SITD number*/
    uint8_t ehciQtdNumber;    /*!< Idle QTD number*/
#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
    bus_ehci_suspend_request_state_t busSuspendStatus; /*!< Bus Suspend Status*/
#endif
} usb_host_ehci_instance_t;

/*! @brief EHCI data structure */
typedef struct _usb_host_ehci_data
{
#if ((defined(USB_HOST_CONFIG_EHCI_MAX_QH)) && (USB_HOST_CONFIG_EHCI_MAX_QH > 0U))
    usb_host_ehci_qh_t ehciQh[USB_HOST_CONFIG_EHCI_MAX_QH]; /*!< Idle QH list array*/
#endif
#if ((defined(USB_HOST_CONFIG_EHCI_MAX_QTD)) && (USB_HOST_CONFIG_EHCI_MAX_QTD > 0U))
    usb_host_ehci_qtd_t ehciQtd[USB_HOST_CONFIG_EHCI_MAX_QTD]; /*!< Idle QTD list array*/
#endif
#if ((defined(USB_HOST_CONFIG_EHCI_MAX_ITD)) && (USB_HOST_CONFIG_EHCI_MAX_ITD > 0U))
    usb_host_ehci_itd_t ehciItd[USB_HOST_CONFIG_EHCI_MAX_ITD]; /*!< Idle ITD list array*/
    /* add additional 32bytes because the itd cannot cross over 4K boundary,
     * If one ITD cross over 4K boundary, the code will move 32 bytes for ITD.
     */
    uint32_t reserved[8];
#endif
#if ((defined(USB_HOST_CONFIG_EHCI_MAX_SITD)) && (USB_HOST_CONFIG_EHCI_MAX_SITD > 0U))
    usb_host_ehci_sitd_t ehciSitd[USB_HOST_CONFIG_EHCI_MAX_SITD]; /*!< Idle SITD list array*/
#endif
#if ((defined(USB_HOST_EHCI_ISO_NUMBER)) && (USB_HOST_EHCI_ISO_NUMBER > 0U))
    usb_host_ehci_iso_t ehciIso[USB_HOST_EHCI_ISO_NUMBER]; /*!< Idle ISO list array*/
#endif
#if ((defined(USB_HOST_CONFIG_MAX_PIPES)) && (USB_HOST_CONFIG_MAX_PIPES > 0U))
    usb_host_ehci_pipe_t ehciPipe[USB_HOST_CONFIG_MAX_PIPES]; /*!< Idle pipe list array*/
#endif
} usb_host_ehci_data_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif
/*!
 * @name USB host EHCI APIs
 * @{
 */

/*!
 * @brief Creates the USB host EHCI instance.
 *
 * This function initializes the USB host EHCI controller driver.
 *
 * @param[in] controllerId      The controller ID of the USB IP. Please refer to the enumeration usb_controller_index_t.
 * @param[in] upperLayerHandle  The host level handle.
 * @param[out] controllerHandle return the controller instance handle.
 *
 * @retval kStatus_USB_Success              The host is initialized successfully.
 * @retval kStatus_USB_AllocFail            Allocating memory failed.
 * @retval kStatus_USB_Error                Host mutex create fail, KHCI/EHCI mutex or KHCI/EHCI event create fail.
 *                                          Or, KHCI/EHCI IP initialize fail.
 */
extern usb_status_t USB_HostEhciCreate(uint8_t controllerId,
                                       usb_host_handle upperLayerHandle,
                                       usb_host_controller_handle *controllerHandle);

/*!
 * @brief Destroys the USB host EHCI instance.
 *
 * This function de-initializes The USB host EHCI controller driver.
 *
 * @param[in] controllerHandle  The controller handle.
 *
 * @retval kStatus_USB_Success              The host is initialized successfully.
 */
extern usb_status_t USB_HostEhciDestory(usb_host_controller_handle controllerHandle);

/*!
 * @brief Opens the USB host pipe.
 *
 * This function opens a pipe according to the pipe_init_ptr parameter.
 *
 * @param[in] controllerHandle The controller handle.
 * @param[out] pipeHandle      The pipe handle pointer, it is used to return the pipe handle.
 * @param[in] pipeInit         It is used to initialize the pipe.
 *
 * @retval kStatus_USB_Success              The host is initialized successfully.
 * @retval kStatus_USB_Error                There is no idle pipe.
 *                                          Or, there is no idle QH for EHCI.
 *                                          Or, bandwidth allocate fail for EHCI.
 */
extern usb_status_t USB_HostEhciOpenPipe(usb_host_controller_handle controllerHandle,
                                         usb_host_pipe_handle *pipeHandle,
                                         usb_host_pipe_init_t *pipeInit);

/*!
 * @brief Closes the USB host pipe.
 *
 * This function closes a pipe and releases related resources.
 *
 * @param[in] controllerHandle The controller handle.
 * @param[in] pipeHandle       The closing pipe handle.
 *
 * @retval kStatus_USB_Success              The host is initialized successfully.
 */
extern usb_status_t USB_HostEhciClosePipe(usb_host_controller_handle controllerHandle, usb_host_pipe_handle pipeHandle);

/*!
 * @brief Sends data to the pipe.
 *
 * This function requests to send the transfer to the specified pipe.
 *
 * @param[in] controllerHandle The controller handle.
 * @param[in] pipeHandle       The sending pipe handle.
 * @param[in] transfer          The transfer information.
 *
 * @retval kStatus_USB_Success              Sent successfully.
 * @retval kStatus_USB_LackSwapBuffer       There is no swap buffer for KHCI.
 * @retval kStatus_USB_Error                There is no idle QTD/ITD/SITD for EHCI.
 */
extern usb_status_t USB_HostEhciWritePipe(usb_host_controller_handle controllerHandle,
                                          usb_host_pipe_handle pipeHandle,
                                          usb_host_transfer_t *transfer);

/*!
 * @brief Receives data from the pipe.
 *
 * This function requests to receive the transfer from the specified pipe.
 *
 * @param[in] controllerHandle The controller handle.
 * @param[in] pipeHandle       The receiving pipe handle.
 * @param[in] transfer         The transfer information.

 * @retval kStatus_USB_Success              Send successfully.
 * @retval kStatus_USB_LackSwapBuffer       There is no swap buffer for KHCI.
 * @retval kStatus_USB_Error                There is no idle QTD/ITD/SITD for EHCI.
 */
extern usb_status_t USB_HostEhciReadpipe(usb_host_controller_handle controllerHandle,
                                         usb_host_pipe_handle pipeHandle,
                                         usb_host_transfer_t *transfer);

/*!
 * @brief Controls the EHCI.
 *
 * This function controls the EHCI.
 *
 * @param[in] controllerHandle The controller handle.
 * @param[in] ioctlEvent       See enumeration host_bus_control_t.
 * @param[in] ioctlParam       The control parameter.
 *
 * @retval kStatus_USB_Success              Cancel successfully.
 * @retval kStatus_USB_InvalidHandle        The controllerHandle is a NULL pointer.
 */
extern usb_status_t USB_HostEhciIoctl(usb_host_controller_handle controllerHandle,
                                      uint32_t ioctlEvent,
                                      void *ioctlParam);

/*! @}*/

#ifdef __cplusplus
}
#endif

/*! @}*/

#endif /* _USB_HOST_CONTROLLER_EHCI_H_ */
