/*!
    \file  exmc_nandflash.h
    \brief the header file of sdram(MICRON 48LC16M16A2) driver
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-10-19, V1.0.0, demo for GD32F4xx
*/

#ifndef EXMC_SDRAM_H
#define EXMC_SDRAM_H

#include "gd32f4xx.h"

/* sdram peripheral initialize */
void exmc_synchronous_dynamic_ram_init(uint32_t sdram_device);

/* fill the buffer with specified value */
void fill_buffer(uint8_t *pbuffer, uint16_t buffer_lengh, uint16_t offset);

/* write a byte buffer(data is 8 bits) to the EXMC SDRAM memory */
void sdram_writebuffer_8(uint32_t sdram_device,uint8_t* pbuffer, uint32_t writeaddr, uint32_t numbytetowrite);

/* read a block of 8-bit data from the EXMC SDRAM memory */
void sdram_readbuffer_8(uint32_t sdram_device,uint8_t* pbuffer, uint32_t readaddr, uint32_t numbytetoread);

#define SDRAM_DEVICE0_ADDR                         ((uint32_t)0xC0000000)
#define SDRAM_DEVICE1_ADDR                         ((uint32_t)0xD0000000)

#endif /* EXMC_SDRAM_H */
