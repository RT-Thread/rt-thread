/**
 * @file       spi.c
 * @brief      This file contains the function implementations for the
 *             Serial Peripheral Interface (SPIMSS) peripheral module.
 */

/* *****************************************************************************
 * Copyright (C) 2017 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2018-10-17 14:16:30 -0500 (Wed, 17 Oct 2018) $
 * $Revision: 38560 $
 *
 **************************************************************************** */

/* **** Includes **** */
#include "spi.h"
#include "mxc_sys.h"
#include "spimss.h"
#include "spi17y.h"

/**
 * @ingroup spi
 * @{
 */

/***** Definitions *****/


/***** Functions *****/


/* ************************************************************************ */
int SPI_Init(spi_type spi_name, unsigned mode, unsigned freq)
{
    sys_cfg_spimss_t spimss_cfg;
    sys_cfg_spi17y_t spi17y_cfg;
    int error = E_NO_ERROR;

    if (spi_name == SPI0A) {
        spi17y_cfg.map = MAP_A;
        error = SPI17Y_Init(MXC_SPI17Y, mode, freq, &spi17y_cfg);

    } else if(spi_name == SPI1A) {
        spimss_cfg.map = MAP_A;
        error = SPIMSS_Init(MXC_SPIMSS, mode, freq, &spimss_cfg);

    } else if(spi_name == SPI1B) {
        spimss_cfg.map = MAP_B;
        error = SPIMSS_Init(MXC_SPIMSS, mode, freq, &spimss_cfg);

    } else {
        return E_BAD_PARAM;
    }

 return error;
}

/* ************************************************************************ */
int SPI_MasterTransAsync(spi_type spi_name, spi_req_t *req)
{
    int error = E_NO_ERROR;

    if (spi_name == SPI0A) {
        error = SPI17Y_MasterTransAsync(MXC_SPI17Y,  (spi17y_req_t *) req);
    
    } else if((spi_name == SPI1A) || (spi_name == SPI1B)) {
        error = SPIMSS_MasterTransAsync(MXC_SPIMSS,  (spimss_req_t *) req);

    } else {
        return E_BAD_PARAM;
    }

 return error;
}


/* ************************************************************************ */
int SPI_MasterTrans(spi_type spi_name, spi_req_t *req)
{
    int error = E_NO_ERROR;

    if (spi_name == SPI0A) {
        error = SPI17Y_MasterTrans(MXC_SPI17Y, (spi17y_req_t *) req);

    } else if((spi_name == SPI1A) || (spi_name == SPI1B)) {
        error = SPIMSS_MasterTrans(MXC_SPIMSS, (spimss_req_t *) req);

    } else {
        return E_BAD_PARAM;
    }

 return error;
}

/* ************************************************************************ */
int SPI_SlaveTrans(spi_type spi_name, spi_req_t *req)
{
    int error = E_NO_ERROR;

    if (spi_name == SPI0A) {
        error = SPI17Y_SlaveTrans(MXC_SPI17Y, (spi17y_req_t *) req); 

    } else if ((spi_name == SPI1A) || (spi_name == SPI1B)) {
        error = SPIMSS_SlaveTrans(MXC_SPIMSS, (spimss_req_t *) req);

    } else {
        return E_BAD_PARAM;
    }

 return error;
}

/* ************************************************************************ */
int SPI_SlaveTransAsync(spi_type spi_name, spi_req_t *req)
{
    int error = E_NO_ERROR;

    if (spi_name == SPI0A) {
        error = SPI17Y_SlaveTransAsync(MXC_SPI17Y, (spi17y_req_t *) req);

    } else if ((spi_name == SPI1A) || (spi_name == SPI1B)) {
        error = SPIMSS_SlaveTransAsync(MXC_SPIMSS, (spimss_req_t *) req);
     
    } else {
        return E_BAD_PARAM;
    }

 return error;
}

/* ************************************************************************ */
int SPI_Shutdown(spi_type spi_name)
{
    int error = E_NO_ERROR;

    if (spi_name == SPI0A) {
        error = SPI17Y_Shutdown(MXC_SPI17Y);

    } else if ((spi_name == SPI1A) || (spi_name == SPI1B)) {
        error = SPIMSS_Shutdown(MXC_SPIMSS);

    } else {
        return E_BAD_PARAM;
    }

 return error;
}


/* ************************************************************************ */
int SPI_AbortAsync(spi_type spi_name, spi_req_t *req)
{
    int error = E_NO_ERROR;

    if (spi_name == SPI0A) {
        error = SPI17Y_AbortAsync((spi17y_req_t *) req);
     
    } else if ((spi_name == SPI1A) || (spi_name == SPI1B)) {
        error = SPIMSS_AbortAsync((spimss_req_t *) req);

    } else {
        return E_BAD_PARAM;
    }

 return error;
}

/* ************************************************************************ */
int SPI_Handler(spi_type spi_name)
{
    if (spi_name == SPI0A) {
        SPI17Y_Handler(MXC_SPI17Y);

    } else if ((spi_name == SPI1A) || (spi_name == SPI1B)) {
        SPIMSS_Handler(MXC_SPIMSS);

    } else {
         return E_BAD_PARAM;
    }

 return E_NO_ERROR;
}

// *****************************************************************************
int SPI_Enable(spi_type spi_name)
{
    if (spi_name == SPI0A) {
        SPI17Y_Enable(MXC_SPI17Y);
        
    } else if ((spi_name == SPI1A) || (spi_name == SPI1B)) {
        return E_NOT_SUPPORTED; 
    } else {
        return E_BAD_PARAM;
    }
    return E_NO_ERROR;
}

// *****************************************************************************
int SPI_Disable(spi_type spi_name)
{
    if (spi_name == SPI0A) {
        SPI17Y_Disable(MXC_SPI17Y);
        
    } else if ((spi_name == SPI1A) || (spi_name == SPI1B)) {
         return E_NOT_SUPPORTED;  
    } else {
        return E_BAD_PARAM;
    }
    return E_NO_ERROR;
}

// *****************************************************************************
int SPI_Clear_fifo(spi_type spi_name)
{
    if (spi_name == SPI0A) {
        SPI17Y_Clear_fifo(MXC_SPI17Y);
        
    } else if ((spi_name == SPI1A) || (spi_name == SPI1B)) {
         return E_NOT_SUPPORTED;  
    } else {
        return E_BAD_PARAM;
    }
    return E_NO_ERROR;
}

/**@} end of group spi */
