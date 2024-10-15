/*
 * Copyright 2019-2021, 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_FBDEV_H_
#define _FSL_FBDEV_H_

#include "fsl_video_common.h"
#include "fsl_dc_fb.h"
#include "rtthread.h"

/*
 * Change Log:
 *
 * 1.0.3:
 *   - Bug Fixes:
 *     - Fixed the issue that frame buffer content changed when saved
 *       to free frame buffer list.
 *
 * 1.0.2:
 *   - Bug Fixes:
 *     - Fixed MISRA 2012 issues.
 *
 * 1.0.1:
 *   - Bug Fixes:
 *     - Fixed coverity warnings that return values unchedked.
 *
 * 1.0.0:
 *   - Initial version.
 */

/*!
 * @addtogroup fbdev
 * @{
 *
 * To use the fbdev, follow the workflow:
 *
   @code
   uint8_t layer = 0;
   fbdev_t fbdev;
   fbdev_fb_info_t fbInfo;
   extern const dc_fb_t dc;

   FBDEV_Open(&fbdev, &dc, layer);

   fbInfo.bufInfo.pixelFormat = DEMO_BUFFER_PIXEL_FORMAT;
   fbInfo.bufInfo.width       = DEMO_BUFFER_WIDTH;
   fbInfo.bufInfo.height      = DEMO_BUFFER_HEIGHT;
   fbInfo.bufInfo.strideBytes = DEMO_BUFFER_STRIDE_BYTE;
   fbInfo.buffers[0] = DEMO_BUFFER0_ADDR;
   fbInfo.buffers[1] = DEMO_BUFFER1_ADDR;

   FBDEV_SetFrameBufferInfo(&fbdev, &fbInfo);

   buffer = FBDEV_GetFrameBuffer(&fbdev, 0);

   fill the buffer here.

   FBDEV_SetFrameBuffer(&fbdev, buffer, 0);

   FBDEV_Enable(&fbdev);

   buffer = FBDEV_GetFrameBuffer(&fbdev, 0);

   fill the buffer here.

   FBDEV_SetFrameBuffer(&fbdev, buffer, 0);

   ...

   @endcode
 *
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief How many frame buffers used in each fbdev. */
#ifndef FBDEV_MAX_FRAME_BUFFER
#define FBDEV_MAX_FRAME_BUFFER 3
#endif

#define FBDEV_DEFAULT_FRAME_BUFFER 2

/*! @brief Frame buffer information. */
typedef struct _fbdev_fb_info
{
    uint8_t bufferCount;                   /*!< How many frame buffers used. */
    void *buffers[FBDEV_MAX_FRAME_BUFFER]; /*!< Address of the frame buffers */
    dc_fb_info_t bufInfo;                  /*!< Frame buffers information */
} fbdev_fb_info_t;

/*! @brief FBDEV handle, user should not touch the members directly. */
typedef struct _fbdev
{
    fbdev_fb_info_t fbInfo;                /*!< Frame buffer information. */
    video_stack_t fbManager;               /*!< Manage the framebuffers used by this device. */
    void *buffers[FBDEV_MAX_FRAME_BUFFER]; /*!< Memory used by @ref fbManager, to save the free frame buffers. */
    const dc_fb_t *dc;                     /*!< Display controller handle. */
    uint8_t layer;                         /*!< Layer in the display controller. */
    bool enabled;                          /*!< The fbdev is enabled or not by @ref FBDEV_Enable. */
    rt_sem_t semaFbManager;                /*!< Semaphore for the @ref fbManager. */
    rt_sem_t semaFramePending;             /*!< Semaphore for the @ref framePending. */
} fbdev_t;

/*! @brief Flags used for FBDEV operations. */
enum _fbdev_flag
{
    kFBDEV_NoWait = (1 << 0), /*!< Don't wait until available, but return directly. */
};

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Open the FBDEV.
 *
 * @param fbdev The FBDEV handle.
 * @param dc The display controller used.
 * @param layer The layer in the display controller.
 * @return Returns @ref kStatus_Success if success, otherwise returns
 * error code.
 */
status_t FBDEV_Open(fbdev_t *fbdev, const dc_fb_t *dc, uint8_t layer);

/*!
 * @brief Close the FBDEV.
 *
 * @param fbdev The FBDEV handle.
 * @return Returns @ref kStatus_Success if success, otherwise returns
 * error code.
 */
status_t FBDEV_Close(fbdev_t *fbdev);

/*!
 * @brief Enable the FBDEV.
 *
 * After enabled, the FBDEV will be shown in the panel. This function should be
 * called after @ref FBDEV_SetFrameBufferInfo.
 *
 * @param fbdev The FBDEV handle.
 * @return Returns @ref kStatus_Success if success, otherwise returns
 * error code.
 */
status_t FBDEV_Enable(fbdev_t *fbdev);

/*!
 * @brief Disable the FBDEV.
 *
 * After disabled, the FBDEV will not be shown in the panel. Don't call
 * @ref FBDEV_SetFrameBuffer when the FBDEV is disabled.
 *
 * @param fbdev The FBDEV handle.
 * @return Returns @ref kStatus_Success if success, otherwise returns
 * error code.
 */
status_t FBDEV_Disable(fbdev_t *fbdev);

/*!
 * @brief Get the frame buffer information of the FBDEV.
 *
 * @param fbdev The FBDEV handle.
 * @param info Pointer to the frame buffer information.
 */
void FBDEV_GetFrameBufferInfo(fbdev_t *fbdev, fbdev_fb_info_t *info);

/*!
 * @brief Set the frame buffer information of the FBDEV.
 *
 * This function could be used to configure the FRDEV, including set witdh, height,
 * pixel format, frame buffers, and so on. This function should only be called once
 * after @ref FBDEV_Open and before @ref FBDEV_Enable.
 *
 * @param fbdev The FBDEV handle.
 * @param info Pointer to the frame buffer information.
 * @return Returns @ref kStatus_Success if success, otherwise returns
 * error code.
 */
status_t FBDEV_SetFrameBufferInfo(fbdev_t *fbdev, fbdev_fb_info_t *info);

/*!
 * @brief Get available frame buffer from the FBDEV.
 *
 * Upper layer could call this function to get an available frame buffer from
 * the FBDEV, render send to show.
 *
 * @param fbdev The FBDEV handle.
 * @param flags OR'ed value of @ref _fbdev_flag. If @ref kFBDEV_NoWait is used,
 * the function returns NULL immediately if no available buffer. If @ref kFBDEV_NoWait
 * is not used, this function waits until available.
 *
 * @return Returns the address of the frame buffer. If no available, returns NULL.
 */
void *FBDEV_GetFrameBuffer(fbdev_t *fbdev, uint32_t flags);

/*!
 * @brief Send frame buffer to the FBDEV.
 *
 * Upper layer could call this function to send a frame buffer to the FBDEV. This
 * function should only be used when the FBDEV is enabled.
 *
 * @param fbdev The FBDEV handle.
 * @param flags OR'ed value of @ref _fbdev_flag. If @ref kFBDEV_NoWait is used,
 * the function returns NULL immediately if the previous frame buffer is pending.
 * If @ref kFBDEV_NoWait is not used, this function waits until previous frame
 * buffer not pending.
 *
 * @return Returns @ref kStatus_Success if success, otherwise returns
 * error code.
 */
status_t FBDEV_SetFrameBuffer(fbdev_t *fbdev, void *frameBuffer, uint32_t flags);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_FBDEV_H_ */
