/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_JPEG_DRV_H
#define HPM_JPEG_DRV_H

#include "hpm_common.h"
#include "hpm_jpeg_regs.h"

/**
 * @brief Jpeg driver APIs
 * @defgroup Jpeg_interface JPEG driver APIs
 * @ingroup io_interfaces
 * @{
 */

/**
 * @brief Define events of the jpeg module
 */
#define JPEG_EVENT_BUSY             JPEG_STAT_BUSY_MASK
#define JPEG_EVENT_OUT_DMA_FINISH   JPEG_STAT_OUT_DMA_TRANSFER_DONE_MASK
#define JPEG_EVENT_IN_DMA_FINISH    JPEG_STAT_IN_DMA_TRANSFER_DONE_MASK
#define JPEG_EVENT_ERROR            (JPEG_STAT_RESTART_MARKER_ERROR_MASK | (0xF << 7))

/**
 * @brief byte order in a word
 */
#define JPEG_BYTE_ORDER_3210        (0U)      /**< no order change, {A3, A2, A1, A0} */
#define JPEG_BYTE_ORDER_2301        (1U)      /**< order change, {A2, A3, A0, A1} */
#define JPEG_BYTE_ORDER_1032        (2U)      /**< order change, {A1, A0, A2, A3} */
#define JPEG_BYTE_ORDER_0123        (3U)      /**< order change, {A0, A1, A2, A3} */

/**
 * @brief jpeg pixel conversion format
 */


/**
 * @brief jpeg data format definition
 */
#define JPEG_SUPPORTED_FORMAT_420   (0U)       /**< hy=2, vy=2, hc=1, vc=1 */
#define JPEG_SUPPORTED_FORMAT_422H  (1U)       /**< hy=2, vy=1, hc=1, vc=1 */
#define JPEG_SUPPORTED_FORMAT_422V  (2U)       /**< hy=1, vy=2, hc=1, vc=1 */
#define JPEG_SUPPORTED_FORMAT_444   (3U)       /**< hy=1, vy=1, hc=1, vc=1 */
#define JPEG_SUPPORTED_FORMAT_400   (4U)       /**< hy=2, vy=2, hc=0, vc=0 */

/**
 * @brief data format definition
 */
typedef struct {
    uint8_t hy:2;                   /**< bit:  1-0 --> horizontal y component */
    uint8_t vy:2;                   /**< bit:  3-2 --> Vertical y component */
    uint8_t hc:2;                   /**< bit:  bit:  5-4 --> horizontal c component */
    uint8_t vc:2;                   /**< bit:  7-6 --> Vertical c component */
} jpeg_sampling_t;

typedef struct {
    uint8_t pixel_width;
    uint8_t ipath;
    uint8_t opath;
    bool is_rgb;
} jpeg_pixel_t;

/**
 * @brief jpeg encoding and decoding configuration parameters
 *   @arg bit:  31-27 --> name
 *   @arg bit:  26-23 --> WIDTH IN BYTE
 *   @arg bit:  22-3 --> ELEMENT COUNT
 *   @arg bit:  2-0 --> TYPE
 */
typedef enum jpeg_table {
    jpeg_table_qmem =     0x201002,     /**< definition Decoder and Encoder Q. values */
    jpeg_table_huffenc =  0x201803,     /**< definition Huffman Encoder table */
    jpeg_table_huffmin =  0x400104,     /**< definition Huffman min values */
    jpeg_table_huffbase = 0x200405,     /**< definition Huffman BASE mem values */
    jpeg_table_huffsymb = 0x101506,     /**< definition Huffman SYMB mem values */
} jpeg_table_t;

typedef enum jpeg_pixel_format {
    jpeg_pixel_format_argb8888 = 0,
    jpeg_pixel_format_rgb565,
    jpeg_pixel_format_yuv422h1p,
    jpeg_pixel_format_yuv422h2p,
    jpeg_pixel_format_yuv420,
    jpeg_pixel_format_y8,
} jpeg_pixel_format_t;

/**
 * @brief jpeg encoding and decoding configuration parameters
 */
typedef struct {
    uint8_t jpeg_format;            /**< supported jpeg format */
    jpeg_pixel_format_t in_pixel_format;
    jpeg_pixel_format_t out_pixel_format;
    uint8_t in_byte_order;          /**< byte order */
    uint8_t out_byte_order;          /**< byte order */
    bool enable_ycbcr;              /**< enable YCbCr or YUV */
    uint16_t width_in_pixel;        /**< Image width register*/
    uint16_t height_in_pixel;       /**< Image height register*/
    uint32_t in_buffer;             /**< input buffer */
    uint32_t out_buffer;            /**< output buffer */
} jpeg_job_config_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief clear jpeg cfg Register
 *
 * @param [in] ptr JPEG base address, HPM_JPEG
 */
static inline void jpeg_clear_cfg(JPEG_Type *ptr)
{
    ptr->CFG = 0;
}

/**
 * @brief jpeg function disable
 *
 * @param [in] ptr JPEG base address, HPM_JPEG
 */
static inline void jpeg_disable(JPEG_Type *ptr)
{
    ptr->CFG &= ~JPEG_CFG_JPEG_EN_MASK;
}

/**
 * @brief jpeg function enable
 *
 * @param [in] ptr JPEG base address, HPM_JPEG
 */
static inline void jpeg_enable(JPEG_Type *ptr)
{
    ptr->CFG |= JPEG_CFG_JPEG_EN_MASK;
}

/**
 * @brief  stop a encoder/decoder conversion
 *
 * @param [in] ptr JPEG base address, HPM_JPEG
 */
static inline void jpeg_stop(JPEG_Type *ptr)
{
    ptr->CFG &= ~JPEG_CFG_START_MASK;
}

/**
 * @brief  start a new encoder/decoder conversion
 *
 * @param [in] ptr JPEG base address, HPM_JPEG
 */
static inline void jpeg_start(JPEG_Type *ptr)
{
    ptr->CFG |= JPEG_CFG_START_MASK;
}

/**
 * @brief  obtain jpeg Status Register
 *
 * @param [in] ptr JPEG base address, HPM_JPEG
 * @retval jpeg register's status
 */
static inline uint32_t jpeg_get_status(JPEG_Type *ptr)
{
    return ptr->STAT;
}

/**
 * @brief  clear jpeg Status Register
 *
 * @param [in] ptr JPEG base address, HPM_JPEG
 * @param [in] mask
 *  @arg JPEG_EVENT_BUSY:  the module is busy doing conversion and data transfer
 *  @arg JPEG_EVENT_OUT_DMA_FINISH: OutDMA process done
 *  @arg JPEG_EVENT_IN_DMA_FINISH: InDMA process done
 *  @arg JPEG_EVENT_ERROR: the axi err
 *
 */
static inline void jpeg_clear_status(JPEG_Type *ptr, uint32_t mask)
{
    ptr->STAT |= mask;
}

/**
 * @brief  Out DMA Bytes Counter
 *
 * @param [in] ptr JPEG base address, HPM_JPEG
 * @retval The out DMA counter
 */
static inline uint32_t jpeg_get_encoded_length(JPEG_Type *ptr)
{
    return JPEG_OUTDMACNT_VAL_GET(ptr->OUTDMACNT);
}

/**
 * @brief  jpeg Software Reset
 *
 * @param [in] ptr JPEG base address, HPM_JPEG
 */
static inline void jpeg_software_reset(JPEG_Type *ptr)
{
    ptr->CFG |= JPEG_CFG_JPEG_SFTRST_MASK;
    ptr->CFG &= ~JPEG_CFG_JPEG_SFTRST_MASK;
}

/**
 * @brief  stop a encoder/decoder conversion and Software Reset
 *
 * @param [in] ptr JPEG base address, HPM_JPEG
 */
void jpeg_reset(JPEG_Type *ptr);

/**
 * @brief  jpeg enable interrupt
 *
 * @param [in] ptr JPEG base address, HPM_JPEG
 * @param [in] mask
 *  @arg JPEG_EVENT_IN_DMA_FINISH:  In DMA Done enable
 *  @arg JPEG_EVENT_OUT_DMA_FINISH: interrupt enable for all interrupt sources of In DMA module
 *  @arg JPEG_EVENT_ERROR: The jpg endec restart error interrupt enable
 *
 */
void jpeg_enable_irq(JPEG_Type *ptr, uint32_t mask);

/**
 * @brief  jpeg disable interrupt
 *
 * @param [in] ptr JPEG base address, HPM_JPEG
 * @param [in] mask
 *  @arg JPEG_EVENT_IN_DMA_FINISH:  In DMA Done disable
 *  @arg JPEG_EVENT_OUT_DMA_FINISH: interrupt disable for all interrupt sources of In DMA module
 *  @arg JPEG_EVENT_ERROR: The jpg endec restart error interrupt disable
 *
 */
void jpeg_disable_irq(JPEG_Type *ptr, uint32_t mask);

/**
 * @brief  stop a encoder/decoder conversion and Software Reset
 *
 * @param [in] ptr JPEG base address, HPM_JPEG
 */
void jpeg_init(JPEG_Type *ptr);

/**
 * @brief  fill tables for jpeg controller
 *
 * @param [in] ptr JPEG base address, HPM_JPEG
 * @param [in] table
 *  @arg jpeg_table_qmem:  file describe for Decoder and Encoder Q. values
 *  @arg jpeg_table_huffenc: file describe for Huffman Encoder table
 *  @arg jpeg_table_huffmin: file describe for Huffman min values
 *  @arg jpeg_table_huffbase: file describe for Huffman BASE mem values
 *  @arg jpeg_table_huffsymb: file describe for Huffman SYMB mem values
 * @param [in] data
 *  @arg huffenc: data for Huffman Encoder table
 *  @arg huffmin: data for Huffman min values
 *  @arg huffbase: data for Huffman BASE mem values
 *  @arg huffsymb: data for Huffman SYMB mem values
 *  @arg qetable: data for Encoder Q. values
 *  @arg qdtable: data for Decoder Q. values
 * @param [in] count   data length
 * @retval  fill tables's status
 *
 */
hpm_stat_t jpeg_fill_table(JPEG_Type *ptr, jpeg_table_t table, uint8_t *data, uint32_t count);

/**
 * @brief   it will start decoding, and the process status needs to be checked by
 * querying JPEG_EVENT
 *
 * @param [in] ptr JPEG base address, HPM_JPEG
 * @param [in] config  config A pointer to the configuration struct of "jpeg_job_config_t"
 * @param [in] length  Decoded data length
 * @retval  jpeg decoding's status
 *
 */
hpm_stat_t jpeg_start_decode(JPEG_Type *ptr, jpeg_job_config_t *config, uint32_t length);

/**
 * @brief   * it will start encoding, and the process status needs to be checked by
 * querying JPEG_EVENT
 *
 * @param [in] ptr JPEG base address, HPM_JPEG
 * @param [in] config  config A pointer to the configuration struct of "jpeg_job_config_t"
 * @retval  jpeg encoding's status
 *
 */
hpm_stat_t jpeg_start_encode(JPEG_Type *ptr, jpeg_job_config_t *config);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif
#endif /* HPM_JPEG_DRV_H */
