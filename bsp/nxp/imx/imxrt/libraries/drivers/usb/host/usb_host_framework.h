/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _USB_HOST_CH9_H_
#define _USB_HOST_CH9_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @addtogroup usb_host_drv
 * @{
 */

/*! @}*/

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief standard control transfer common code.
 *
 * @param deviceInstance device instance handle.
 * @param transfer       transfer.
 * @param buffer         data buffer pointer.
 * @param bufferLen      data length.
 *
 * @return kStatus_USB_Success or error codes.
 */
usb_status_t USB_HostCh9RequestCommon(usb_host_device_instance_t *deviceInstance,
                                      usb_host_transfer_t *transfer,
                                      uint8_t *buffer,
                                      uint32_t bufferLen);

/*!
 * @brief standard get status implementation.
 *
 * @param deviceInstance device instance handle.
 * @param transfer       transfer.
 * @param param          parameter.
 *
 * @return kStatus_USB_Success or error codes.
 */
usb_status_t USB_HostStandardGetStatus(usb_host_device_instance_t *deviceInstance,
                                       usb_host_transfer_t *transfer,
                                       void *param);

/*!
 * @brief standard set/clear feature implementation.
 *
 * @param deviceInstance device instance handle.
 * @param transfer       transfer.
 * @param param          parameter.
 *
 * @return kStatus_USB_Success or error codes.
 */
usb_status_t USB_HostStandardSetClearFeature(usb_host_device_instance_t *deviceInstance,
                                             usb_host_transfer_t *transfer,
                                             void *param);

/*!
 * @brief standard set address implementation.
 *
 * @param deviceInstance device instance handle.
 * @param transfer       transfer.
 * @param param          parameter.
 *
 * @return kStatus_USB_Success or error codes.
 */
usb_status_t USB_HostStandardSetAddress(usb_host_device_instance_t *deviceInstance,
                                        usb_host_transfer_t *transfer,
                                        void *param);

/*!
 * @brief standard set/get descriptor implementation.
 *
 * @param deviceInstance device instance handle.
 * @param transfer       transfer.
 * @param param          parameter.
 *
 * @return kStatus_USB_Success or error codes.
 */
usb_status_t USB_HostStandardSetGetDescriptor(usb_host_device_instance_t *deviceInstance,
                                              usb_host_transfer_t *transfer,
                                              void *param);

/*!
 * @brief standard get interface implementation.
 *
 * @param deviceInstance device instance handle.
 * @param transfer       transfer.
 * @param param          parameter.
 *
 * @return kStatus_USB_Success or error codes.
 */
usb_status_t USB_HostStandardGetInterface(usb_host_device_instance_t *deviceInstance,
                                          usb_host_transfer_t *transfer,
                                          void *param);

/*!
 * @brief standard set interface implementation.
 *
 * @param deviceInstance device instance handle.
 * @param transfer       transfer.
 * @param param          parameter.
 *
 * @return kStatus_USB_Success or error codes.
 */
usb_status_t USB_HostStandardSetInterface(usb_host_device_instance_t *deviceInstance,
                                          usb_host_transfer_t *transfer,
                                          void *param);

/*!
 * @brief standard sync frame implementation.
 *
 * @param deviceInstance device instance handle.
 * @param transfer       transfer.
 * @param param          parameter.
 *
 * @return kStatus_USB_Success or error codes.
 */
usb_status_t USB_HostStandardSyncFrame(usb_host_device_instance_t *deviceInstance,
                                       usb_host_transfer_t *transfer,
                                       void *param);
#endif /* _USB_HOST_CH9_H_ */
