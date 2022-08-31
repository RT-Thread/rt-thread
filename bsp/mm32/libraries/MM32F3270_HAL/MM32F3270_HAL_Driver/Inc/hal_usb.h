/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_USB_H__
#define __HAL_USB_H__

#include "hal_common.h"
#include "hal_usb_bdt.h"

/*!
 * @addtogroup USB
 * @{
 */

/*!
 * @brief USB driver version number.
 */
#define USB_DRIVER_VERSION 0u /*!< USB_0. */


/*!
 * @addtogroup USB_INT
 * @brief USB_INT mask codes
 * @{
 */
#define USB_INT_RESET           USB_INTSTAT_USBRST_MASK         /*!< USB Interrupt: USB bus reset.  */
#define USB_INT_ERROR           USB_INTSTAT_ERROR_MASK          /*!< USB Interrupt: Error happend.  */
#define USB_INT_SOFTOK          USB_INTSTAT_SOFTOK_MASK         /*!< USB Interrupt: Recv a SOF_Tok. */
#define USB_INT_TOKENDONE       USB_INTSTAT_TOKDNE_MASK         /*!< USB Interrupt: Token done.     */
#define USB_INT_SLEEP           USB_INTSTAT_SLEEP_MASK          /*!< USB Interrupt: Sleep.          */
#define USB_INT_RESUME          USB_INTSTAT_RESUME_MASK         /*!< USB Interrupt: Resume.         */
#define USB_INT_ATTACH          USB_INTSTAT_ATTACH_MASK         /*!< USB Interrupt: Attach.         */
#define USB_INT_STALL           USB_INTSTAT_STALL_MASK          /*!< USB Interrupt: Stall.          */
/*!
 * @}
 */

/*!
 * @addtogroup USB_INT_ERR
 * @brief USB_INT_ERR mask codes
 * @{
 */
#define USB_INT_ERR_PID             USB_ERRSTAT_PIDERR_MASK         /*!< USB Error: PID check error.    */
#define USB_INT_ERR_CRC5            USB_ERRSTAT_CRC5EOF_MASK        /*!< USB Error: CRC5 check failed.  */
#define USB_INT_ERR_EOF             USB_ERRSTAT_CRC5EOF_MASK        /*!< USB Error: EOF Error.          */
#define USB_INT_ERR_CRC16           USB_ERRSTAT_CRC16_MASK          /*!< USB Error: CRC16 check failed. */
#define USB_INT_ERR_DFN8            USB_ERRSTAT_DFN8_MASK           /*!< USB Error: Data not 8bit.      */
#define USB_INT_ERR_BTO             USB_ERRSTAT_BTOERR_MASK         /*!< USB Error: BTO error.          */
#define USB_INT_ERR_DMA             USB_ERRSTAT_DMAERR_MASK         /*!< USB Error: DMA error.          */
#define USB_INT_ERR_BTS             USB_ERRSTAT_BTSERR_MASK         /*!< USB Error: Bit stuff error.    */
/*!
 * @}
 */

/*!
 * @addtogroup USB_EP
 * @brief USB_EP mask codes
 * @{
 */
#define USB_EP_0     (1u << 0u )                      /*!< EndPoint 0.  */
#define USB_EP_1     (1u << 1u )                      /*!< EndPoint 1.  */
#define USB_EP_2     (1u << 2u )                      /*!< EndPoint 2.  */
#define USB_EP_3     (1u << 3u )                      /*!< EndPoint 3.  */
#define USB_EP_4     (1u << 4u )                      /*!< EndPoint 4.  */
#define USB_EP_5     (1u << 5u )                      /*!< EndPoint 5.  */
#define USB_EP_6     (1u << 6u )                      /*!< EndPoint 6.  */
#define USB_EP_7     (1u << 7u )                      /*!< EndPoint 7.  */
#define USB_EP_8     (1u << 8u )                      /*!< EndPoint 8.  */
#define USB_EP_9     (1u << 9u )                      /*!< EndPoint 9.  */
#define USB_EP_10    (1u << 10u)                      /*!< EndPoint 10. */
#define USB_EP_11    (1u << 11u)                      /*!< EndPoint 11. */
#define USB_EP_12    (1u << 12u)                      /*!< EndPoint 12. */
#define USB_EP_13    (1u << 13u)                      /*!< EndPoint 13. */
#define USB_EP_14    (1u << 14u)                      /*!< EndPoint 14. */
#define USB_EP_15    (1u << 15u)                      /*!< EndPoint 15. */
/*!
 * @}
 */

/*!
 * @brief USB TokenPid type.
 */
typedef enum
{
    USB_TokenPid_OUT   = 0x1u, /*!< USB Token Pid: OUT.   */
    USB_TokenPid_IN    = 0x9u, /*!< USB Token Pid: IN.    */
    USB_TokenPid_SETUP = 0xDu, /*!< USB Token Pid: SETUP. */
} USB_TokenPid_Type;

/*!
 * @brief USB Direction type.
 */
typedef enum
{
    USB_Direction_OUT = 0x0u, /*!< USB Direstion: IN.   */
    USB_Direction_IN  = 0x1u, /*!< USB Direstion: OUT.  */
    USB_Direction_NULL,       /*!< USB Direstion: NULL. */
} USB_Direction_Type;

/*!
 * @brief USB BufDesp OddEven type.
 */
typedef enum
{
    USB_BufDesp_OddEven_Even = 0x0u, /*!< Buffer Descriptor OddEven: Even. */
    USB_BufDesp_OddEven_Odd  = 0x1u, /*!< Buffer Descriptor OddEven: Odd.  */
} USB_BufDesp_OddEven_Type;

/*!
 * @brief USB EndPoint Mode.
 */
typedef enum
{
    USB_EndPointMode_Control     = 1u, /*!< USB EndPoint Mode: Control xfer.   */
    USB_EndPointMode_Bulk        = 2u, /*!< USB EndPoint Mode: Bulk xfer.      */
    USB_EndPointMode_Interrupt   = 3u, /*!< USB EndPoint Mode: Interrupt xfer. */
    USB_EndPointMode_Isochronous = 4u, /*!< USB EndPoint Mode: isoch xfer.     */
    USB_EndPointMode_NULL,             /*!< USB EndPoint Mode: NULL.           */
} USB_EndPointMode_Type;

/*!
 * @brief This type of structure instance is used to keep the settings when calling the @ref USB_InitDevice() to initialize the USB module.
 */
typedef struct
{
    uint32_t BufDespTable_Addr; /*!< BufDespTable addr. */
} USB_Device_Init_Type;

/*!
 * @brief Initialize the USB module.
 *
 * @param USBx USB instance.
 * @param init Pointer to the initialization structure. See to @ref USB_Device_Init_Type.
 * @return None.
 */
void USB_InitDevice(USB_Type * USBx, USB_Device_Init_Type * init);

/*!
 * @brief Enable interrupts of the USB module.
 *
 * @param USBx USB instance.
 * @param interrupts Interrupt code masks. See to @ref USB_INT.
 * @param enable 'true' to enable the indicated interrupts, 'false' to disable the indicated interrupts.
 * @return None.
 */
void USB_EnableInterrupts(USB_Type * USBx, uint32_t interrupts, bool enable);

/*!
 * @brief Get the enabled interrupts status flags of the USB module.
 *
 * @param USBx USB instance.
 * @return Interrupt status flags. See to @ref USB_INT.
 */
uint32_t USB_GetEnabledInterrupts(USB_Type * USBx);

/*!
 * @brief Get the interrupts status flags of the USB module.
 *
 * @param USBx USB instance.
 * @return Interrupt status flags. See to @ref USB_INT.
 */
uint32_t USB_GetInterruptStatus(USB_Type * USBx);

/*!
 * @brief Clear the interrupts status flags of the USB module.

 * @param USBx USB instance.
 * @param interrupts Interrupt status flags. See to @ref USB_INT.
 * @return None.
 */
void USB_ClearInterruptStatus(USB_Type * USBx, uint32_t interrupts);

/*!
 * @brief Enable error interrupts of the USB module.
 *
 * @param USBx USB instance.
 * @param interrupts Error Interrupt code masks. See to @ref USB_INT_ERR.
 * @param enable 'true' to enable the indicated interrupts, 'false' to disable the indicated interrupts.
 * @return None.
 */
void USB_EnableErrInterrupts(USB_Type * USBx, uint32_t interrupts, bool enable);

/*!
 * @brief Get the enabled error interrupts status flags of the USB module.
 *
 * @param USBx USB instance.
 * @return Interrupt status flags. See to @ref USB_INT_ERR.
 */
uint32_t USB_GetEnabledErrInterrupts(USB_Type * USBx);

/*!
 * @brief Get the error interrupts status flags of the USB module.
 *
 * @param USBx USB instance.
 * @return Interrupt status flags. See to @ref USB_INT_ERR.
 */
uint32_t USB_GetErrInterruptStatus(USB_Type * USBx);

/*!
 * @brief Clear the error interrupts status flags of the USB module.

 * @param USBx USB instance.
 * @param interrupts Interrupt status flags. See to @ref USB_INT_ERR.
 * @return None.
 */
void USB_ClearErrInterruptStatus(USB_Type * USBx, uint32_t interrupts);

/*!
 * @brief Enable USB.
 *
 * @param USBx USB instance.
 * @param enable 'true' to enable the module, 'false' to disable the module.
 * @return None.
 */
void USB_Enable(USB_Type * USBx, bool enable);

/*!
 * @brief Enable USB BufDesp ODD_EVEN Reset, and make only even BufDesp can be used.
 *
 * @param USBx USB instance.
 * @param enable 'true' to enable the feature, 'false' to disable the feature.
 * @return None.
 */
void USB_EnableOddEvenReset(USB_Type * USBx, bool enable);

/*!
 * @brief Enable USB Resume signal.
 *
 * @param USBx USB instance.
 * @param enable 'true' to enable the resume signal, 'false' to disable the resume signal.
 * @return None.
 */
void USB_EnableResumeSignal(USB_Type * USBx, bool enable);

/*!
 * @brief Enable USB Suspend.
 *
 * @param USBx USB instance.
 * @param enable 'true' to enable suspend, 'false' to disable suspend.
 * @return None.
 */
void USB_EnableSuspend(USB_Type * USBx, bool enable);

/*!
 * @brief Set Device address. This address is distribute by host.
 *
 * @param USBx USB instance.
 * @param addr The Device address.
 * @return None.
 */
void USB_SetDeviceAddr(USB_Type * USBx, uint8_t addr);

/*!
 * @brief Get Device address.
 *
 * @param USBx USB instance.
 * @return The Device address.
 */
uint8_t USB_GetDeviceAddr(USB_Type * USBx);

/*!
 * @brief Get buffer descriptor table address.
 *
 * @param USBx USB instance.
 * @return The BufDespTable address.
 */
uint32_t USB_GetBufDespTableAddr(USB_Type * USBx);

/*!
 * @brief Get the USB Frame Number.
 *
 * @param USBx USB instance.
 * @return The USB Frame Number.
 */
uint32_t USB_GetFrameNumber(USB_Type * USBx);

/*!
 * @brief Get BufDesp after USB_INT_TOKENDONE interrupt happened and before clear USB_INT_TOKENDONE interrupt status.
 *
 * @param USBx USB instance.
 * @return BufDesp address.
 */
USB_BufDesp_Type * USB_GetBufDesp(USB_Type * USBx);

/*!
 * @brief Get Token Pid from BufDesp before the BufDesp Reset.
 *
 * @param bd BufDesp addr.
 * @return Token Pid.
 */
USB_TokenPid_Type USB_BufDesp_GetTokenPid(USB_BufDesp_Type * bd);

/*!
 * @brief Get packet addr from BufDesp before the BufDesp Reset.
 *
 * @param   bd BufDesp addr.
 * @return Packet addrress.
 */
uint32_t USB_BufDesp_GetPacketAddr(USB_BufDesp_Type * bd);

/*!
 * @brief Get packet size from BufDesp before the BufDesp Reset.
 *
 * @param bd BufDesp addr.
 * @return Packet size.
 */
uint32_t USB_BufDesp_GetPacketSize(USB_BufDesp_Type * bd);

/*!
 * @brief Reset BufDesp.
 *
 * @param bd BufDesp addr.
 * @return None.
 */
void USB_BufDesp_Reset(USB_BufDesp_Type * bd);

/*!
 * @brief Get EndPoint index after USB_INT_TOKENDONE interrupt happened and before clear USB_INT_TOKENDONE interrupt status.
 *
 * @param USBx USB instance.
 * @return EndPoint index.
 */
uint32_t USB_GetEndPointIndex(USB_Type * USBx);

/*!
 * @brief Get Xfer Direction after USB_INT_TOKENDONE interrupt happened and before clear USB_INT_TOKENDONE interrupt status.
 *
 * @param USBx USB instance.
 * @return Xfer Direction, See to @ref USB_Direction_Type.
 */
USB_Direction_Type USB_GetXferDirection(USB_Type * USBx);

/*!
 * @brief Get BufDesp OddEven after USB_INT_TOKENDONE interrupt happened and before clear USB_INT_TOKENDONE interrupt status.
 *
 * @param USBx USB instance.
 * @return BufDesp OddEven.
 */
USB_BufDesp_OddEven_Type USB_GetBufDespOddEven(USB_Type * USBx);

/*!
 * @brief Enable the end point.
 *
 * @param USBx USB instance.
 * @param index endpoint index.
 * @param mode End point mode, See to @ref USB_EndPointMode_Type.
 * @param enable 'true' to enable the EndPoint, 'false' to disable the EndPoint.
 * @return None.
 */
void USB_EnableEndPoint(USB_Type * USBx, uint32_t index, USB_EndPointMode_Type mode, bool enable);

/*!
 * @brief Stall EndPoint n.
 *
 * @param USBx USB instance.
 * @param ep_mask EndPoint mask, see to @ref USB_EP mask codes.
 * @param enable 'true' to enable the EndPoint stall, 'false' to disable the EndPoint stall.
 * @return None.
 */
void USB_EnableEndPointStall(USB_Type * USBx, uint32_t ep_mask, bool enable);

/*!
 * @brief Get Enabled EndPoint stall status.
 *
 * @param USBx USB instance.
 * @return stall status, see to @ref USB_EP mask codes.
 */
uint32_t USB_GetEnabledEndPointStall(USB_Type * USBx);

/*!
 * @brief Xfer data by usb.
 *
 * @param bd BufDesp.
 * @param data_n DATAn packet, n equal 0 or 1.
 * @param data the address of data.
 * @param len Data length.
 * @return 'true': BufDesp can be xfer data, 'false': BufDesp is busy.
 */
bool USB_BufDesp_Xfer(USB_BufDesp_Type * bd, uint32_t data_n, uint8_t * data, uint32_t len);

/*!
 * @brief Check whether BufDesp is busy.
 *
 * @param bd BufDesp addr.
 * @return 'true': BufDesp is busy, 'false': BufDesp is not busy.
 */
bool USB_BufDesp_IsBusy(USB_BufDesp_Type * bd);


/*!
 *@}
 */

#endif /* __HAL_USB_H__ */

