/*!
    \file    gd32h7xx_fac.c
    \brief   definitions for the FAC

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#ifndef GD32H7XX_FAC_H
#define GD32H7XX_FAC_H

#include "gd32h7xx.h"

/* FAC definitions */
#define FAC                              FAC_BASE                        /*!< FAC base address */

#define REG16_INT(addr)                  (*(volatile int16_t *)(uint32_t)(addr))
#define REG32_FLOAT(addr)                (*(volatile float *)(uint32_t)(addr))

/* registers definitions */
#define FAC_X0BCFG                       REG32((FAC) + 0x00000000U)      /*!< FAC X0 buffer configure register */
#define FAC_X1BCFG                       REG32((FAC) + 0x00000004U)      /*!< FAC X1 buffer configure register */
#define FAC_YBCFG                        REG32((FAC) + 0x00000008U)      /*!< FAC Y buffer configure register */
#define FAC_PARACFG                      REG32((FAC) + 0x0000000CU)      /*!< FAC Parameter configure register */
#define FAC_CTL                          REG32((FAC) + 0x00000010U)      /*!< FAC Control register */
#define FAC_STAT                         REG32((FAC) + 0x00000014U)      /*!< FAC Status register */
#define FAC_WDATA                        REG32((FAC) + 0x00000018U)      /*!< FAC write data register */
#define FAC_RDATA                        REG32((FAC) + 0x0000001CU)      /*!< FAC read data register */

#define FAC_WDATA_INT                    REG16_INT((FAC) + 0x00000018U)  /*!< FAC write data register */
#define FAC_WDATA_FLOAT                  REG32_FLOAT((FAC) + 0x00000018U)/*!< FAC write data register */

#define FAC_RDATA_INT                    REG16_INT((FAC) + 0x0000001CU)  /*!< FAC read data register */
#define FAC_RDATA_FLOAT                  REG32_FLOAT((FAC) + 0x0000001CU)/*!< FAC read data register */

/* bits definitions */
/* FAC_X0BCFG */
#define FAC_X0BCFG_X0B_ADDR              BITS(0,7)                       /*!< X0 buffer base address */
#define FAC_X0BCFG_X0B_SIZE              BITS(8,15)                      /*!< X0 buffer allocated size */
#define FAC_X0BCFG_X0_WBFF               BITS(24,25)                     /*!< watermark for buffer full flag */

/* FAC_X1BCFG */
#define FAC_X1BCFG_X1B_ADDR              BITS(0,7)                       /*!< X1 buffer base address */
#define FAC_X1BCFG_X1B_SIZE              BITS(8,15)                      /*!< X1 buffer allocated size */

/* FAC_YBCFG */
#define FAC_YBCFG_YB_ADDR                BITS(0,7)                       /*!< Y buffer base address */
#define FAC_YBCFG_YB_SIZE                BITS(8,15)                      /*!< Y buffer allocated size */
#define FAC_YBCFG_Y_WBEF                 BITS(24,25)                     /*!< watermark for buffer empty flag */

/* FAC_PARACFG */
#define FAC_PARACFG_IPP                  BITS(0,7)                       /*!< input parameter IPP */
#define FAC_PARACFG_IPQ                  BITS(8,15)                      /*!< input parameter IPQ */
#define FAC_PARACFG_IPR                  BITS(16,23)                     /*!< input parameter IPR */
#define FAC_PARACFG_FUN                  BITS(24,30)                     /*!< function */
#define FAC_PARACFG_EXE                  BIT(31)                         /*!< execution */

/* FAC_CTL */
#define FAC_CTL_RIE                      BIT(0)                          /*!< read interrupt enable */
#define FAC_CTL_WIE                      BIT(1)                          /*!< write interrupt enable */
#define FAC_CTL_OFEIE                    BIT(2)                          /*!< overflow error interrupt enable */
#define FAC_CTL_UFEIE                    BIT(3)                          /*!< underflow error interrupt enable */
#define FAC_CTL_STEIE                    BIT(4)                          /*!< saturation error interrupt enable */
#define FAC_CTL_GSTEIE                   BIT(5)                          /*!< gain saturation error interrupt enable */
#define FAC_CTL_DREN                     BIT(8)                          /*!< DMA read channel enable */
#define FAC_CTL_DWEN                     BIT(9)                          /*!< DMA write channel enable */
#define FAC_CTL_FLTEN                    BIT(14)                         /*!< floating point format enable */
#define FAC_CTL_CPEN                     BIT(15)                         /*!< clipping enable */
#define FAC_CTL_RST                      BIT(16)                         /*!< reset FAC unit */

/* FAC_STAT */
#define FAC_STAT_YBEF                    BIT(0)                          /*!< Y buffer empty flag */
#define FAC_STAT_X0BFF                   BIT(1)                          /*!< X0 buffer full flag */
#define FAC_STAT_OFEF                    BIT(8)                          /*!< overflow error flag */
#define FAC_STAT_UFEF                    BIT(9)                          /*!< underflow error flag */
#define FAC_STAT_STEF                    BIT(10)                         /*!< saturation error flag */
#define FAC_STAT_GSTEF                   BIT(11)                         /*!< gain saturation error flag */

/* FAC_WDATA */
#define FAC_WDATA_WDATA                  BITS(0,15)                      /*!< Write data */

/* FAC_RDATA */
#define FAC_RDATA_RDATA                  BITS(0,15)                      /*!< Read data */

/* constants definitions */
/* structure for fac filter parameters */
typedef struct
{
    uint8_t input_addr;                                                  /*!< base address of the input buffer (X0) */
    uint8_t input_size;                                                  /*!< size of input buffer */
    uint8_t coeff_addr;                                                  /*!< base address of the coefficient buffer (X1) */
    uint8_t coeff_size;                                                  /*!< size of coefficient buffer */
    uint8_t output_addr;                                                 /*!< base address of the output buffer (Y) */
    uint8_t output_size;                                                 /*!< size of output buffer */
    uint8_t ipp;                                                         /*!< value P (vector length, number of filter taps, etc.) */
    uint8_t ipq;                                                         /*!< value Q (vector length, etc.) */
    uint8_t ipr;                                                         /*!< value R (gain, etc.) */
    uint32_t input_threshold;                                            /*!< threshold of input buffer full */
    uint32_t output_threshold;                                           /*!< threshold of output buffer empty */
    uint32_t clip;                                                       /*!< enable or disable the clipping feature */
    uint32_t func;                                                       /*!< FAC functions select */
}fac_parameter_struct;

/* structure for fac fixed data preload parameters */
typedef struct
{
    uint8_t coeffa_size;                                                 /*!< size of the coefficient vector A */
    int16_t *coeffa_ctx;                                                 /*!< [IIR only] content of the coefficient vector A */
    uint8_t coeffb_size;                                                 /*!< size of the coefficient vector B */
    int16_t *coeffb_ctx;                                                 /*!< content of the coefficient vector B */
    uint8_t input_size;                                                  /*!< Size of the input data */
    int16_t *input_ctx;                                                  /*!< content of the input data */
    uint8_t output_size;                                                 /*!< size of the output data */
    int16_t *output_ctx;                                                 /*!< content of the output data */
}fac_fixed_data_preload_struct;

/* structure for fac float data preload parameters */
typedef struct
{
    uint8_t coeffa_size;                                                 /*!< size of the coefficient vector A */
    float *coeffa_ctx;                                                   /*!< [IIR only] content of the coefficient vector A */
    uint8_t coeffb_size;                                                 /*!< size of the coefficient vector B */
    float *coeffb_ctx;                                                   /*!< content of the coefficient vector B */
    uint8_t input_size;                                                  /*!< size of the input data */
    float *input_ctx;                                                    /*!< content of the input data */
    uint8_t  output_size;                                                /*!< size of the output data */
    float *output_ctx;                                                   /*!< content of the output data */
}fac_float_data_preload_struct;

/* FAC function select definitions */
#define PARACFG_FUN(regval)              (FAC_PARACFG_FUN & ((uint32_t)(regval) << 24))
#define FUNC_LOAD_X0                     PARACFG_FUN(1)                  /*!< load_X0_buffer */
#define FUNC_LOAD_X1                     PARACFG_FUN(2)                  /*!< load_X1_buffer */
#define FUNC_LOAD_Y                      PARACFG_FUN(3)                  /*!< load_Y_buffer */
#define FUNC_CONVO_FIR                   PARACFG_FUN(8)                  /*!< convolution (FIR filter) */
#define FUNC_IIR_DIRECT_FORM_1           PARACFG_FUN(9)                  /*!< IIR filter (direct form 1) */

/* FAC watermark setting definitions */
#define X0BCFG_X0_WBFF(regval)           (FAC_X0BCFG_X0_WBFF & ((uint32_t)(regval) << 24))
#define FAC_THRESHOLD_1                  X0BCFG_X0_WBFF(0)               /*!< full/empty flag when buffer less than 1 */
#define FAC_THRESHOLD_2                  X0BCFG_X0_WBFF(1)               /*!< full/empty flag when buffer less than 2 */
#define FAC_THRESHOLD_4                  X0BCFG_X0_WBFF(2)               /*!< full/empty flag when buffer less than 4 */
#define FAC_THRESHOLD_8                  X0BCFG_X0_WBFF(3)               /*!< full/empty flag when buffer less than 8 */

/* FAC clip function definitions */
#define FAC_CP_DISABLE                   ((uint8_t)0x00U)                /*!< clipping disabled */
#define FAC_CP_ENABLE                    ((uint8_t)0x01U)                /*!< clipping enabled */

/* FAC function execution definitions */
#define PARACFG_EXE(regval)              (FAC_PARACFG_EXE & ((uint32_t)(regval) << 31))
#define FAC_FUNC_START                   PARACFG_EXE(0)                  /*!< start execution function */
#define FAC_FUNC_STOP                    PARACFG_EXE(1)                  /*!< stop execution function */

/* FAC DMA mdoe definitions */
#define FAC_DMA_READ                     FAC_CTL_DREN                    /*!< enable dma read */
#define FAC_DMA_WRITE                    FAC_CTL_DWEN                    /*!< enable dma write */

/* FAC interrupt flag definitions */
#define FAC_INT_FLAG_YBEF                ((uint8_t)0x00U)                /*!< Y buffer empty interrupt flag */
#define FAC_INT_FLAG_X0BFF               ((uint8_t)0x01U)                /*!< X0 buffer full interrupt flag */
#define FAC_INT_FLAG_OFEF                ((uint8_t)0x02U)                /*!< Overflow error interrupt flag */
#define FAC_INT_FLAG_UFEF                ((uint8_t)0x03U)                /*!< underflow error interrupt flag */
#define FAC_INT_FLAG_STEF                ((uint8_t)0x04U)                /*!< saturation error interrupt flag */
#define FAC_INT_FLAG_GSTEF               ((uint8_t)0x05U)                /*!< gain saturation error interrupt flag */

/* FAC flag definitions */
#define FAC_FLAG_YBEF                    FAC_STAT_YBEF                   /*!< Y buffer empty flag */
#define FAC_FLAG_X0BFF                   FAC_STAT_X0BFF                  /*!< X0 buffer full flag */
#define FAC_FLAG_OFEF                    FAC_STAT_OFEF                   /*!< overflow error flag */
#define FAC_FLAG_UFEF                    FAC_STAT_UFEF                   /*!< underflow error flag */
#define FAC_FLAG_STEF                    FAC_STAT_STEF                   /*!< saturation error flag */
#define FAC_FLAG_GSTEF                   FAC_STAT_GSTEF                  /*!< gain saturation error flag */

/* FAC function declarations */
/* initialization functions */
/* reset the FAC peripheral */
void fac_deinit(void);
/* initialize the FAC filter parameter struct with the default values */
void fac_struct_para_init(fac_parameter_struct* fac_parameter);
/* initialize the FAC fixed data preload parameter struct with the default values */
void fac_fixed_data_preload_init(fac_fixed_data_preload_struct *init_struct);
/* initialize the FAC float data preload parameter struct with the default values */
void fac_float_data_preload_init(fac_float_data_preload_struct *init_struct);
/* initialize the FAC peripheral */
void fac_init(fac_parameter_struct* fac_parameter);
/* FAC preload X0 X1 Y fixed buffer */
void fac_fixed_buffer_preload(fac_fixed_data_preload_struct* init_struct);
/* FAC preload X0 X1 Y float buffer*/
void fac_float_buffer_preload(fac_float_data_preload_struct* init_struct);
/* FAC preload data */
void fac_fixed_data_preload(uint8_t size, int16_t array[]);
/* FAC preload float data */
void fac_float_data_preload(uint8_t size, float array[]);
/* configuration functions */
/* FAC reset write and read pointers */
void fac_reset(void);
/* config the FAC clip feature */
void fac_clip_config(uint8_t cpmod);
/* enable FAC float point format */
void fac_float_enable(void);
/* disable FAC float point format */
void fac_float_disable(void);
/* enable the FAC dma */
void fac_dma_enable(uint32_t dma_req);
/* disable the FAC dma */
void fac_dma_disable(uint32_t dma_req);
/* FAC config input buffer */
void fac_x0_config(uint32_t watermark, uint8_t baseaddr, uint8_t bufsize);
/* FAC config coefficient buffer */
void fac_x1_config(uint8_t baseaddr, uint8_t bufsize);
/* FAC config output buffer */
void fac_y_config(uint32_t watermark, uint8_t baseaddr, uint8_t bufsize);
/* FAC config function execute */
void fac_function_config(fac_parameter_struct* fac_parameter);
/* start the FAC */
void fac_start(void);
/* stop the FAC */
void fac_stop(void);
/* finish the filter calculate */
void fac_finish_calculate(void);

/* FAC data write and read */
/* FAC write data with fixed ponit format */
void fac_fixed_data_write(int16_t data);
/* FAC read data with fixed point format */
int16_t fac_fixed_data_read(void);
/* FAC write data with float ponit format */
void fac_float_data_write(float data);
/* FAC read data with fixed point format */
float fac_float_data_read(void);

/* interrupt & flag functions */
/* enable the FAC interrupt */
void fac_interrupt_enable(uint32_t interrupt);
/* disable the FAC interrupt */
void fac_interrupt_disable(uint32_t interrupt);
/* get the FAC interrupt flag status */
FlagStatus fac_interrupt_flag_get(uint8_t interrupt);
/* get the FAC flag status */
FlagStatus fac_flag_get(uint32_t flag);

#endif /* GD32H7XX_FAC_H */
