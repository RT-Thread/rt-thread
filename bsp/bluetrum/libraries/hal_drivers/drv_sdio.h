/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 * 
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-11-30     greedyhao         first version
 */

#ifndef DEV_SDIO_H__
#define DEV_SDIO_H__

#include "drv_common.h"
#include "board.h"
#include "drivers/mmcsd_core.h"
#include "drivers/sdio.h"

#define SDIO_BUFF_SIZE       1024
#define SDIO_ALIGN_LEN       32

#ifndef SDIO_MAX_FREQ
#define SDIO_MAX_FREQ        (1000000)
#endif

#ifndef SDIO_BASE_ADDRESS
#define SDIO_BASE_ADDRESS    (0x40012800U)
#endif

#ifndef SDIO_CLOCK_FREQ
#define SDIO_CLOCK_FREQ      (48U * 1000 * 1000)
#endif

#ifndef SDIO_BUFF_SIZE
#define SDIO_BUFF_SIZE       (4096)
#endif

#ifndef SDIO_ALIGN_LEN
#define SDIO_ALIGN_LEN       (32)
#endif

#ifndef SDIO_MAX_FREQ
#define SDIO_MAX_FREQ        (24 * 1000 * 1000)
#endif


#define HW_SDIO_CON_
#define HW_SDIO_CON_CFLAG                       (0x01u << 12)   /*!< 0:send command or received response not finish \
                                                                     1:send command or received response finish     */
#define HW_SDIO_CON_DFLAG                       (0x01u << 13)   /*!< 0:send or received data not finish             \
                                                                     1:send or received data finish                 */
#define HW_SDIO_CON_CCRCE                       (0x01u << 14)   /*!< 0:command crc no error                         \
                                                                     1:command crc error detected                   */
#define HW_SDIO_CON_NRPS                        (0x01u << 15)   /*!< 0:response received 1:no response received     */
#define HW_SDIO_CON_DCRCE                       (0x01u << 16)   /*!< 0:read data crc no error                       \
                                                                     1:read data crc error detected                 */
#define HW_SDIO_CON_CRCS                        (0x07u << 17)   /*!< 101:error transmission                         \
                                                                     010:non-erroneous transmission                 \
                                                                     111:flash error                                */
#define HW_SDIO_CON_BUSY                        (0x01u << 20)   /*!< 0:device busy 1:device not busy                */

#define HW_SDIO_ERRORS \
    (0)

#define HW_SDIO_POWER_OFF                      (0x00U)
#define HW_SDIO_POWER_UP                       (0x02U)
#define HW_SDIO_POWER_ON                       (0x03U)

#define HW_SDIO_FLOW_ENABLE                    (0x01U << 14)
#define HW_SDIO_BUSWIDE_1B                     (0x00U << 11)
#define HW_SDIO_BUSWIDE_4B                     (0x01U << 11)
#define HW_SDIO_BUSWIDE_8B                     (0x02U << 11)
#define HW_SDIO_BYPASS_ENABLE                  (0x01U << 10)
#define HW_SDIO_IDLE_ENABLE                    (0x01U << 9)
#define HW_SDIO_CLK_ENABLE                     (0x01U << 8)

#define HW_SDIO_SUSPEND_CMD                    (0x01U << 11)
#define HW_SDIO_CPSM_ENABLE                    (0x01U << 10)
#define HW_SDIO_WAIT_END                       (0x01U << 9)
#define HW_SDIO_WAIT_INT                       (0x01U << 8)
#define HW_SDIO_RESPONSE_NO                    (0x00U << 6)
#define HW_SDIO_RESPONSE_SHORT                 (0x01U << 6)
#define HW_SDIO_RESPONSE_LONG                  (0x03U << 6)

#define HW_SDIO_DATA_LEN_MASK                  (0x01FFFFFFU)

#define HW_SDIO_IO_ENABLE                      (0x01U << 11)
#define HW_SDIO_RWMOD_CK                       (0x01U << 10)
#define HW_SDIO_RWSTOP_ENABLE                  (0x01U << 9)
#define HW_SDIO_RWSTART_ENABLE                 (0x01U << 8)
#define HW_SDIO_DBLOCKSIZE_1                   (0x00U << 4)
#define HW_SDIO_DBLOCKSIZE_2                   (0x01U << 4)
#define HW_SDIO_DBLOCKSIZE_4                   (0x02U << 4)
#define HW_SDIO_DBLOCKSIZE_8                   (0x03U << 4)
#define HW_SDIO_DBLOCKSIZE_16                  (0x04U << 4)
#define HW_SDIO_DBLOCKSIZE_32                  (0x05U << 4)
#define HW_SDIO_DBLOCKSIZE_64                  (0x06U << 4)
#define HW_SDIO_DBLOCKSIZE_128                 (0x07U << 4)
#define HW_SDIO_DBLOCKSIZE_256                 (0x08U << 4)
#define HW_SDIO_DBLOCKSIZE_512                 (0x09U << 4)
#define HW_SDIO_DBLOCKSIZE_1024                (0x0AU << 4)
#define HW_SDIO_DBLOCKSIZE_2048                (0x0BU << 4)
#define HW_SDIO_DBLOCKSIZE_4096                (0x0CU << 4)
#define HW_SDIO_DBLOCKSIZE_8192                (0x0DU << 4)
#define HW_SDIO_DBLOCKSIZE_16384               (0x0EU << 4)
#define HW_SDIO_DMA_ENABLE                     (0x01U << 3)
#define HW_SDIO_STREAM_ENABLE                  (0x01U << 2)
#define HW_SDIO_TO_HOST                        (0x01U << 1)
#define HW_SDIO_DPSM_ENABLE                    (0x01U << 0)

#define HW_SDIO_DATATIMEOUT                    (0xF0000000U)

// struct ab32_sdio
// {};

typedef rt_err_t (*dma_txconfig)(rt_uint32_t *src, int size);
typedef rt_err_t (*dma_rxconfig)(rt_uint32_t *dst, int size);
typedef rt_uint32_t (*sdio_clk_get)(hal_sfr_t hw_sdio);

struct ab32_sdio_des
{
    hal_sfr_t    hw_sdio;
    dma_txconfig txconfig;
    dma_rxconfig rxconfig;
    sdio_clk_get clk_get;
};

struct ab32_sdio_config
{
    hal_sfr_t instance;
    // struct dma_config dma_rx, dma_tx;
};

struct ab32_sdio_class
{
    const struct ab32_sdio_config *cfg;
    struct rt_mmcsd_host host;
};

#endif
