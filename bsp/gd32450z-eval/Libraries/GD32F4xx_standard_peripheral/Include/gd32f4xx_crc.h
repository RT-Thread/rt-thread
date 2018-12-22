/*!
    \file  gd32f4xx_crc.h
    \brief definitions for the CRC
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#ifndef GD32F4XX_CRC_H
#define GD32F4XX_CRC_H

#include "gd32f4xx.h"

/* CRC definitions */
#define CRC                            CRC_BASE

/* registers definitions */
#define CRC_DATA                       REG32(CRC + 0x00U)              /*!< CRC data register */
#define CRC_FDATA                      REG32(CRC + 0x04U)              /*!< CRC free data register */
#define CRC_CTL                        REG32(CRC + 0x08U)              /*!< CRC control register */

/* bits definitions */
/* CRC_DATA */
#define CRC_DATA_DATA                  BITS(0,31)                      /*!< CRC calculation result bits */

/* CRC_FDATA */
#define CRC_FDATA_FDATA                BITS(0,7)                       /*!< CRC free data bits */

/* CRC_CTL */
#define CRC_CTL_RST                    BIT(0)                          /*!< CRC reset CRC_DATA register bit */


/* function declarations */
/* deinit CRC calculation unit */
void crc_deinit(void);

/* reset data register to the value of initializaiton data register */
void crc_data_register_reset(void);
/* read the data register */
uint32_t crc_data_register_read(void);

/* read the free data register */
uint8_t crc_free_data_register_read(void);
/* write the free data register */
void crc_free_data_register_write(uint8_t free_data);

/* CRC calculate a 32-bit data */
uint32_t crc_single_data_calculate(uint32_t sdata);
/* CRC calculate a 32-bit data array */
uint32_t crc_block_data_calculate(uint32_t array[], uint32_t size);

#endif /* GD32F4XX_CRC_H */
