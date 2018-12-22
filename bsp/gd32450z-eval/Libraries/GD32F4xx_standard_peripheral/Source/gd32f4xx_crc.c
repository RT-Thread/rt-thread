/*!
    \file  gd32f4xx_crc.c
    \brief CRC driver
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#include "gd32f4xx_crc.h"

/*!
    \brief      deinit CRC calculation unit
    \param[in]  none
    \param[out] none
    \retval     none
*/
void crc_deinit(void)
{
    CRC_DATA  = (uint32_t)0xFFFFFFFFU;
    CRC_FDATA = (uint32_t)0x00000000U;
    CRC_CTL   = CRC_CTL_RST;
}

/*!
    \brief      reset data register to the value of initializaiton data register
    \param[in]  none
    \param[out] none
    \retval     none
*/
void crc_data_register_reset(void)
{
    CRC_CTL |= (uint32_t)CRC_CTL_RST;
}

/*!
    \brief      read the data register 
    \param[in]  none
    \param[out] none
    \retval     32-bit value of the data register
*/
uint32_t crc_data_register_read(void)
{
    uint32_t data;
    data = CRC_DATA;
    return (data);
}

/*!
    \brief      read the free data register
    \param[in]  none
    \param[out] none
    \retval     8-bit value of the free data register
*/
uint8_t crc_free_data_register_read(void)
{
    uint8_t fdata;
    fdata = (uint8_t)CRC_FDATA;
    return (fdata);
}

/*!
    \brief      write the free data register
    \param[in]  free_data: specify 8-bit data
    \param[out] none
    \retval     none
*/
void crc_free_data_register_write(uint8_t free_data)
{
    CRC_FDATA = (uint32_t)free_data;
}

/*!
    \brief      CRC calculate a 32-bit data
    \param[in]  sdata: specify 32-bit data
    \param[out] none
    \retval     32-bit CRC calculate value
*/
uint32_t crc_single_data_calculate(uint32_t sdata)
{
    CRC_DATA = sdata;
    return (CRC_DATA);
}

/*!
    \brief      CRC calculate a 32-bit data array
    \param[in]  array: pointer to an array of 32 bit data words
    \param[in]  size: size of the array
    \param[out] none
    \retval     32-bit CRC calculate value
*/
uint32_t crc_block_data_calculate(uint32_t array[], uint32_t size)
{
    uint32_t index;
    for(index = 0U; index < size; index++){
        CRC_DATA = array[index];
    }
    return (CRC_DATA);
}
