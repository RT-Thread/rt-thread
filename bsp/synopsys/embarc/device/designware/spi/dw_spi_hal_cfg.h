/* ------------------------------------------
 * Copyright (c) 2017, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * \version 2017.03
 * \date 2015-09-09
 * \author Huaqi Fang(Huaqi.Fang@synopsys.com)
--------------------------------------------- */

/**
 * \file
 * \ingroup	DEVICE_DW_SPI
 * \brief	DesignWare SPI driver hardware description
 * 	related header file configuration file
 * \details	configuration file to enable or disable some function of spi
 */

#ifndef _DEVICE_DW_SPI_HAL_CFG_H_
#define _DEVICE_DW_SPI_HAL_CFG_H_

#ifndef DW_SPI_CALC_FIFO_LEN_ENABLE
#define DW_SPI_CALC_FIFO_LEN_ENABLE		(1)	/*!< Defaultly enable calculate fifo length */
#endif

#ifndef DW_SPI_MAX_FIFO_LENGTH
#define DW_SPI_MAX_FIFO_LENGTH			(256)	/*!< Max FIFO depth for designware SPI device */
#endif

#ifndef DW_SPI_MIN_FIFO_LENGTH
#define DW_SPI_MIN_FIFO_LENGTH			(2)	/*!< Min FIFO depth for designware SPI device */
#endif

#endif /* _DEVICE_DW_SPI_HAL_CFG_H_ */

