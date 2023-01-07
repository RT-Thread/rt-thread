/**
 * @file hal_spi.h
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */
#ifndef __HAL_SPI__H__
#define __HAL_SPI__H__

#include "hal_common.h"
#include "drv_device.h"
#include "bl808_config.h"

#define SPI_FIFO_LEN 32

#define DEVICE_CTRL_SPI_CONFIG_CLOCK 0x10

#define DEVICE_CTRL_SPI_GET_TX_FIFO   0x11
#define DEVICE_CTRL_SPI_GET_RX_FIFO   0x12
#define DEVICE_CTRL_SPI_CLEAR_TX_FIFO 0x13
#define DEVICE_CTRL_SPI_CLEAR_RX_FIFO 0x14

#define DEVICE_CTRL_SPI_GET_BUS_BUSY_STATUS 0x15
#define DEVICE_CTRL_SPI_SET_FRAME_SIZE 0x16

enum spi_index_type {
#ifdef BSP_USING_SPI0
    SPI0_INDEX,
#endif
#ifdef BSP_USING_SPI1
    SPI1_INDEX,
#endif
    SPI_MAX_INDEX
};

/** @defgroup SPI_Direction SPI Direction Mode (Only when the datasize==SPI_DATASIZE_32BIT)
  * @{
  */
typedef enum  {
    SPI_LSB_BYTE0_DIRECTION_FIRST = 0,
    SPI_LSB_BYTE3_DIRECTION_FIRST,
    SPI_MSB_BYTE0_DIRECTION_FIRST,
    SPI_MSB_BYTE3_DIRECTION_FIRST,
}spi_byte_order_type;

/** @defgroup SPI_Data_Size SPI Data Size
  * @{
  */
typedef enum  {
    SPI_DATASIZE_8BIT = 0,
    SPI_DATASIZE_16BIT,
    SPI_DATASIZE_24BIT,
    SPI_DATASIZE_32BIT,
}spi_data_size_type;

/** @defgroup SPI_Clock_Polarity SPI Clock Polarity
  * @{
  */
typedef enum  {
    SPI_POLARITY_LOW = 0,
    SPI_POLARITY_HIGH,
}spi_polarity_type;

/** @defgroup SPI_Clock_Phase SPI Clock Phase
  * @{
  */
 typedef enum  {
    SPI_PHASE_1EDGE = 0,
    SPI_PHASE_2EDGE,
}spi_phase_type;

/** @defgroup
  * @{
  */
typedef enum  {
    SPI_SLVAE_MODE = 0,
    SPI_MASTER_MODE,
}spi_mode_type;

typedef enum  {
    SPI_TRANSFER_TYPE_8BIT = 0,
    SPI_TRANSFER_TYPE_16BIT,
    SPI_TRANSFER_TPYE_24BIT,
    SPI_TRANSFER_TYPE_32BIT,
}spi_transfer_size_type;

typedef enum{
    SPI_EVENT_TX_FIFO =0,
    SPI_EVENT_RX_FIFO,
    SPI_EVENT_UNKNOWN,
}spi_event_type;

typedef struct spi_device {
    struct device parent;
    uint8_t id;
    uint32_t clk;
    spi_mode_type mode;
    spi_byte_order_type direction;
    spi_polarity_type clk_polaraity;
    spi_phase_type clk_phase;
    spi_data_size_type datasize;
    uint8_t fifo_threshold;
    uint8_t pin_swap_enable; /*swap mosi and miso*/
    uint8_t delitch_cnt;
    void *tx_dma;
    void *rx_dma;
} spi_device_t;

#define SPI_DEV(dev) ((spi_device_t *)dev)

int spi_register(enum spi_index_type index, const char *name);

#endif