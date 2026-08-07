/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DRV_XSPI_H__
#define __DRV_XSPI_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <ipc/completion.h>
#include "drv_common.h"

#include "n32h7xx_xspi_v2.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mdma_config
{
    MDMA_ChNumType  mdma_channel;
    IRQn_Type       dma_irq;
    uint32_t        dmamux_channel;
    uint32_t        dmamux_request;
    uint32_t        hs_interface;
};

#define XSPI_USING_RX_DMA_FLAG   (1<<0)
#define XSPI_USING_TX_DMA_FLAG   (1<<1)

typedef enum
{
    XSPI_Tx_Rx = 0U,
    XSPI_Tx,
    XSPI_Rx,
    XSPI_Idle,

} XSPI_Work_Direct_t;

struct n32_xspi
{

    XSPI_Module                 *xSPIx;
    char                        *bus_name;
    XSPI_InitType                InitStructure;
    XSPI_EnhancedInitType        EnhInitStructure;
    XSPI_XIPInitType             XIPInitStructure;

    struct rt_qspi_configuration *qspi_cfg;
    struct rt_spi_configuration  *cfg;
    XSPI_Work_Direct_t           Direct;
    rt_uint8_t                   xspi_dma_flag;

    struct
    {
        rt_bool_t         DMA_Tx_Init;
        MDMA_ChInitType   TX_DMA_ChInitStr;
        rt_bool_t         DMA_Rx_Init;
        MDMA_ChInitType   RX_DMA_ChInitStr;
    } dma;

    rt_uint8_t                   slave_sel;
    rt_uint8_t                   xip_enabled;

    struct rt_completion         cpt;
};

struct n32_xspi_config
{
    uint32_t scph;
    uint32_t scpol;
    uint32_t role;
    uint32_t frame_format;
    uint32_t data_frame_size;
    uint32_t transfer_mode;
    uint32_t baudr;
    uint32_t rxd_sampling_edge;
    uint32_t rxd_sample_delay;
    uint32_t nss_toggle;

    uint8_t slave_sel;

    uint32_t Enhance_clock_strech;
    uint32_t Enhance_TransferType;
    uint32_t Enhance_AddrLen;
    uint32_t Enhance_InstructLen;
    uint32_t Enhance_WaitCycles;
    uint32_t Enhance_DDR;

};

struct xspi_xip_config
{
    uint32_t XipInstructLen;
    uint32_t XipInstrctEnable;
    uint32_t XipDFSHC;
    uint32_t XipPrefetch;

    uint32_t XipModeBit;
    uint32_t XipModeBitLen;
    uint16_t XipModeBit_Data;

    uint32_t XipContinousTransfer;
    uint32_t XipWatchDogTimeout;

    uint16_t XipIncrOpcode;
    uint16_t XipWrapOpcode;
};

/* XSPI control commands */
#define XSPI_CTRL_ENTER_XIP      0x01
#define XSPI_CTRL_EXIT_XIP       0x02
#define XSPI_CTRL_GET_XIP_ADDR   0x03

rt_err_t rt_hw_xspi_device_attach(const char *bus_name, const char *device_name,
                                  rt_uint8_t data_line_width,
                                  void (*enter_qspi_mode)(struct rt_qspi_device *),
                                  void (*exit_qspi_mode)(struct rt_qspi_device *),
                                  struct n32_xspi_config *cfg);

#ifdef __cplusplus
}
#endif

#endif /*__DRV_XSPI_H__ */
