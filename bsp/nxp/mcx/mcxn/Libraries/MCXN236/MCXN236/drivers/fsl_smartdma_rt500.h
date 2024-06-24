/*
 * Copyright 2019-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_SMARTDMA_RT500_H_
#define FSL_SMARTDMA_RT500_H_

#include "fsl_common.h"

/*!
 * @addtogroup smartdma_rt500 RT500 SMARTDMA Firmware
 * @ingroup smartdma
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SMARTDMA_DISPLAY_MIPI_AND_FLEXIO 0
#define SMARTDMA_DISPLAY_MIPI_ONLY       1
#define SMARTDMA_DISPLAY_FLEXIO_ONLY     2

/* Select firmware for MIPI and FLEXIO by default. */
#ifndef SMARTDMA_DISPLAY_FIRMWARE_SELECT
#define SMARTDMA_DISPLAY_FIRMWARE_SELECT SMARTDMA_DISPLAY_MIPI_AND_FLEXIO
#endif

/*! @brief The firmware used for display. */
extern const uint8_t s_smartdmaDisplayFirmware[];

/*! @brief The s_smartdmaDisplayFirmware firmware memory address. */
#define SMARTDMA_DISPLAY_MEM_ADDR 0x24100000U

/*! @brief Size of s_smartdmaDisplayFirmware */
#define SMARTDMA_DISPLAY_FIRMWARE_SIZE (s_smartdmaDisplayFirmwareSize)

/*! @brief Size of s_smartdmaDisplayFirmware */
extern const uint32_t s_smartdmaDisplayFirmwareSize;

#if (SMARTDMA_DISPLAY_FIRMWARE_SELECT == SMARTDMA_DISPLAY_MIPI_AND_FLEXIO)
/*!
 * @brief The API index when using s_smartdmaDisplayFirmware.
 */
enum _smartdma_display_api
{
    kSMARTDMA_FlexIO_DMA_Endian_Swap = 0U,
    kSMARTDMA_FlexIO_DMA_Reverse32,
    kSMARTDMA_FlexIO_DMA,
    kSMARTDMA_FlexIO_DMA_Reverse,              /*!< Send data to FlexIO with reverse order. */
    kSMARTDMA_RGB565To888,                     /*!< Convert RGB565 to RGB888 and save to output memory, use parameter
                                                  smartdma_rgb565_rgb888_param_t. */
    kSMARTDMA_FlexIO_DMA_RGB565To888,          /*!< Convert RGB565 to RGB888 and send to FlexIO, use parameter
                                                  smartdma_flexio_mculcd_param_t. */
    kSMARTDMA_FlexIO_DMA_ARGB2RGB,             /*!< Convert ARGB to RGB and send to FlexIO, use parameter
                                                  smartdma_flexio_mculcd_param_t. */
    kSMARTDMA_FlexIO_DMA_ARGB2RGB_Endian_Swap, /*!< Convert ARGB to RGB, then swap endian, and send to
                                                 FlexIO, use         parameter smartdma_flexio_mculcd_param_t. */
    kSMARTDMA_FlexIO_DMA_ARGB2RGB_Endian_Swap_Reverse, /*!< Convert ARGB to RGB, then swap endian and reverse, and send
                                                 to FlexIO, use parameter smartdma_flexio_mculcd_param_t. */
    kSMARTDMA_MIPI_RGB565_DMA,               /*!< Send RGB565 data to MIPI DSI, use parameter smartdma_dsi_param_t. */
    kSMARTDMA_MIPI_RGB565_DMA2D,             /*!< Send RGB565 data to MIPI DSI, use parameter smartdma_dsi_2d_param_t.
                                              */
    kSMARTDMA_MIPI_RGB888_DMA,               /*!< Send RGB888 data to MIPI DSI, use parameter smartdma_dsi_param_t. */
    kSMARTDMA_MIPI_RGB888_DMA2D,             /*!< Send RGB565 data to MIPI DSI, use parameter smartdma_dsi_2d_param_t.
                                              */
    kSMARTDMA_MIPI_XRGB2RGB_DMA,             /*!< Send XRGB8888 data to MIPI DSI, use parameter smartdma_dsi_param_t */
    kSMARTDMA_MIPI_XRGB2RGB_DMA2D,           /*!< Send XRGB8888 data to MIPI DSI, use parameter
                                                smartdma_dsi_2d_param_t. */
    kSMARTDMA_MIPI_RGB565_R180_DMA,          /*!< Send RGB565 data to MIPI DSI, Rotate 180, use parameter
                                              * smartdma_dsi_param_t.
                                              */
    kSMARTDMA_MIPI_RGB888_R180_DMA,          /*!< Send RGB888 data to MIPI DSI, Rotate 180, use parameter
                                              * smartdma_dsi_param_t.
                                              */
    kSMARTDMA_MIPI_XRGB2RGB_R180_DMA,        /*!< Send XRGB8888 data to MIPI DSI, Rotate 180, use parameter
                                                smartdma_dsi_param_t */
    kSMARTDMA_MIPI_RGB5652RGB888_DMA,        /*!< Send RGB565 data to MIPI DSI, use parameter smartdma_dsi_param_t.
                                              */
    kSMARTDMA_MIPI_RGB888_CHECKER_BOARD_DMA, /*!< Send RGB888 data to MIPI DSI with checker board pattern,
                                                use parameter smartdma_dsi_checkerboard_param_t. */
    kSMARTDMA_MIPI_Enter_ULPS, /*!< Set MIPI-DSI to enter ultra low power state. */
    kSMARTDMA_MIPI_Exit_ULPS, /*!< Set MIPI-DSI to exit ultra low power state. */
    kSMARTDMA_FlexIO_DMA_ONELANE,            /*!< FlexIO DMA for one SHIFTBUF, Write Data to SHIFTBUF[OFFSET] */
    kSMARTDMA_FlexIO_FIFO2RAM, /*!< Read data from FlexIO FIFO to ram space. */
};

#elif (SMARTDMA_DISPLAY_FIRMWARE_SELECT == SMARTDMA_DISPLAY_MIPI_ONLY)

/*!
 * @brief The API index when using s_smartdmaDisplayFirmware.
 */
enum _smartdma_display_api
{
    kSMARTDMA_MIPI_RGB565_DMA,               /*!< Send RGB565 data to MIPI DSI, use parameter smartdma_dsi_param_t. */
    kSMARTDMA_MIPI_RGB565_DMA2D,             /*!< Send RGB565 data to MIPI DSI, use parameter smartdma_dsi_2d_param_t.
                                              */
    kSMARTDMA_MIPI_RGB888_DMA,               /*!< Send RGB888 data to MIPI DSI, use parameter smartdma_dsi_param_t. */
    kSMARTDMA_MIPI_RGB888_DMA2D,             /*!< Send RGB565 data to MIPI DSI, use parameter smartdma_dsi_2d_param_t.
                                              */
    kSMARTDMA_MIPI_XRGB2RGB_DMA,             /*!< Send XRGB8888 data to MIPI DSI, use parameter smartdma_dsi_param_t */
    kSMARTDMA_MIPI_XRGB2RGB_DMA2D,           /*!< Send XRGB8888 data to MIPI DSI, use parameter
                                                smartdma_dsi_2d_param_t. */
    kSMARTDMA_MIPI_RGB565_R180_DMA,          /*!< Send RGB565 data to MIPI DSI, Rotate 180, use parameter
                                              * smartdma_dsi_param_t.
                                              */
    kSMARTDMA_MIPI_RGB888_R180_DMA,          /*!< Send RGB888 data to MIPI DSI, Rotate 180, use parameter
                                              * smartdma_dsi_param_t.
                                              */
    kSMARTDMA_MIPI_XRGB2RGB_R180_DMA,        /*!< Send XRGB8888 data to MIPI DSI, Rotate 180, use parameter
                                                smartdma_dsi_param_t */
    kSMARTDMA_MIPI_RGB5652RGB888_DMA,        /*!< Send RGB565 data to MIPI DSI, use parameter smartdma_dsi_param_t.
                                              */
    kSMARTDMA_MIPI_RGB888_CHECKER_BOARD_DMA, /*!< Send RGB888 data to MIPI DSI with checker board pattern,
                                                use parameter smartdma_dsi_checkerboard_param_t. */
    kSMARTDMA_MIPI_Enter_ULPS, /*!< Set MIPI-DSI to enter ultra low power state. */
    kSMARTDMA_MIPI_Exit_ULPS, /*!< Set MIPI-DSI to exit ultra low power state. */
};

#elif (SMARTDMA_DISPLAY_FIRMWARE_SELECT == SMARTDMA_DISPLAY_FLEXIO_ONLY)

/*!
 * @brief The API index when using s_smartdmaDisplayFirmware.
 */
enum _smartdma_display_api
{
    kSMARTDMA_FlexIO_DMA_Endian_Swap = 0U,
    kSMARTDMA_FlexIO_DMA_Reverse32,
    kSMARTDMA_FlexIO_DMA,
    kSMARTDMA_FlexIO_DMA_Reverse,              /*!< Send data to FlexIO with reverse order. */
    kSMARTDMA_FlexIO_DMA_RGB565To888,          /*!< Convert RGB565 to RGB888 and send to FlexIO, use parameter
                                                  smartdma_flexio_mculcd_param_t. */
    kSMARTDMA_FlexIO_DMA_ARGB2RGB,             /*!< Convert ARGB to RGB and send to FlexIO, use parameter
                                                  smartdma_flexio_mculcd_param_t. */
    kSMARTDMA_FlexIO_DMA_ARGB2RGB_Endian_Swap, /*!< Convert ARGB to RGB, then swap endian, and send to FlexIO, use
                                                 parameter smartdma_flexio_mculcd_param_t. */
    kSMARTDMA_FlexIO_DMA_ARGB2RGB_Endian_Swap_Reverse, /*!< Convert ARGB to RGB, then swap endian and reverse, and send
                                                 to FlexIO, use parameter smartdma_flexio_mculcd_param_t. */
    kSMARTDMA_FlexIO_DMA_ONELANE, /*!< FlexIO DMA for one SHIFTBUF, Write Data to SHIFTBUF[OFFSET] */
    kSMARTDMA_FlexIO_FIFO2RAM, /*!< Read data from FlexIO FIFO to ram space. */
};
#endif

/*!
 * @brief Parameter for FlexIO MCULCD except kSMARTDMA_FlexIO_DMA_ONELANE
 */
typedef struct _smartdma_flexio_mculcd_param
{
    uint32_t *p_buffer;
    uint32_t buffersize;
    uint32_t *smartdma_stack;
} smartdma_flexio_mculcd_param_t;

/*!
 * @brief Parameter for kSMARTDMA_FlexIO_DMA_ONELANE
 */
typedef struct _smartdma_flexio_onelane_mculcd_param
{
    uint32_t *p_buffer;
    uint32_t buffersize;
    uint32_t offset;
    uint32_t *smartdma_stack;
} smartdma_flexio_onelane_mculcd_param_t;

/*!
 * @brief Parameter for MIPI DSI
 */
typedef struct _smartdma_dsi_param
{
    /*! Pointer to the buffer to send. */
    const uint8_t *p_buffer;
    /*! Buffer size in byte. */
    uint32_t buffersize;
    /*! Stack used by SMARTDMA. */
    uint32_t *smartdma_stack;
    /*!
     * If set to 1, the pixels are filled to MIPI DSI FIFO directly.
     * If set to 0, the pixel bytes are swapped then filled to
     * MIPI DSI FIFO. For example, when set to 0 and frame buffer pixel
     * format is RGB565:
     * LSB                                           MSB
     * B0 B1 B2 B3 B4 G0 G1 G2 | G3 G4 G5 R0 R1 R2 R3 R4
     * Then the pixel filled to DSI FIFO is:
     * LSB                                           MSB
     * G3 G4 G5 R0 R1 R2 R3 R4 | B0 B1 B2 B3 B4 G0 G1 G2
     */
    uint32_t disablePixelByteSwap;
} smartdma_dsi_param_t;

/*!
 * @brief Parameter for kSMARTDMA_MIPI_RGB565_DMA2D, kSMARTDMA_MIPI_RGB888_DMA2D
 * and kSMARTDMA_MIPI_XRGB2RGB_DMA2D.
 */
typedef struct _smartdma_dsi_2d_param
{
    /*! Pointer to the buffer to send. */
    const uint8_t *p_buffer;
    /*! SRC data transfer in a minor loop */
    uint32_t minorLoop;
    /*! SRC data offset added after a minor loop */
    uint32_t minorLoopOffset;
    /*! SRC data transfer in a major loop */
    uint32_t majorLoop;
    /*! Stack used by SMARTDMA. */
    uint32_t *smartdma_stack;
    /*!
     * If set to 1, the pixels are filled to MIPI DSI FIFO directly.
     * If set to 0, the pixel bytes are swapped then filled to
     * MIPI DSI FIFO. For example, when set to 0 and frame buffer pixel
     * format is RGB565:
     * LSB                                           MSB
     * B0 B1 B2 B3 B4 G0 G1 G2 | G3 G4 G5 R0 R1 R2 R3 R4
     * Then the pixel filled to DSI FIFO is:
     * LSB                                           MSB
     * G3 G4 G5 R0 R1 R2 R3 R4 | B0 B1 B2 B3 B4 G0 G1 G2
     */
    uint32_t disablePixelByteSwap;
} smartdma_dsi_2d_param_t;

/*!
 * @brief Parameter for kSMARTDMA_MIPI_RGB888_CHECKER_BOARD_DMA
 */
typedef struct _smartdma_dsi_checkerboard_param
{
    /*! Pointer to the buffer to send, pixel format is ARGB8888. */
    const uint8_t *p_buffer;
    uint32_t height; /*! Height resolution in pixel. */
    uint32_t width;  /*! Width resolution in pixel. */
    /*! Cube block type.
     * cbType=1 : 1/2 pixel mask cases
     * cbType=2 : 1/4 pixel mask cases
     */
    uint32_t cbType;
    /*! which pixel is turned off in each type
     *  cbType=2: indexOff= 1,2,3,4
     *  cbType=1: indexOff= 0,1
     */
    uint32_t indexOff;
    /*! Stack used by SMARTDMA. */
    uint32_t *smartdma_stack;
    /*!
     * If set to 1, the pixels are filled to MIPI DSI FIFO directly.
     * If set to 0, the pixel bytes are swapped then filled to
     * MIPI DSI FIFO. For example, when set to 0 and frame buffer pixel
     * for example
     * format is RGB888:
     * LSB                                           MSB
     * B0 B1 B2 B3 B4 B5 B6 B7 | G0 G1 G2 G3 G4 G5 G6 G7 | R0 R1 R2 R3 R4 R5 R6 R7
     * Then the pixel filled to DSI FIFO is:
     * LSB                                           MSB
     * R0 R1 R2 R3 R4 R5 R6 R7 | G0 G1 G2 G3 G4 G5 G6 G7 | B0 B1 B2 B3 B4 B5 B6 B7
     */
    uint32_t disablePixelByteSwap;
} smartdma_dsi_checkerboard_param_t;

/*!
 * @brief Parameter for RGB565To888
 */
typedef struct _smartdma_rgb565_rgb888_param
{
    uint32_t *inBuf;
    uint32_t *outBuf;
    uint32_t buffersize;
    uint32_t *smartdma_stack;
} smartdma_rgb565_rgb888_param_t;

/*!
 * @brief Parameter for all supported APIs.
 */
typedef union
{
    /*! Parameter for flexio MCULCD. */
    smartdma_flexio_mculcd_param_t flexioMcuLcdParam;
    /*! Parameter for flexio MCULCD with one shift buffer. */
    smartdma_flexio_onelane_mculcd_param_t flexioOneLineMcuLcdParam;
    /*! Parameter for MIPI DSI functions. */
    smartdma_dsi_param_t dsiParam;
    /*! Parameter for MIPI DSI 2D functions. */
    smartdma_dsi_2d_param_t dsi2DParam;
    /*! Parameter for MIPI DSI checker board functions. */
    smartdma_dsi_checkerboard_param_t dsiCheckerBoardParam;
    /*! Parameter for RGB565_RGB888 convertion. */
    smartdma_rgb565_rgb888_param_t rgb565_rgb888Param;
} smartdma_param_t;

typedef struct
{
    uint8_t RESERVED_0[32];
    __IO uint32_t BOOTADR;    /* 0x20 */
    __IO uint32_t CTRL;       /* 0x24 */
    __I uint32_t PC;          /* 0x28 */
    __I uint32_t SP;          /* 0x2C */
    __IO uint32_t BREAK_ADDR; /* 0x30 */
    __IO uint32_t BREAK_VECT; /* 0x34 */
    __IO uint32_t EMER_VECT;  /* 0x38 */
    __IO uint32_t EMER_SEL;   /* 0x3C */
    __IO uint32_t ARM2EZH;    /* 0x40 */
    __IO uint32_t EZH2ARM;    /* 0x44 */
    __IO uint32_t PENDTRAP;   /* 0x48 */
} SMARTDMA_Type;

#define SMARTDMA_BASE 0x40027000
#define SMARTDMA      ((volatile SMARTDMA_Type *)SMARTDMA_BASE)

/*******************************************************************************
 * APIs
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#if defined(__cplusplus)
}
#endif

/* @} */

#endif /* FSL_SMARTDMA_RT500_H_ */
