/*!
    \file    gd32h7xx_tmu.h
    \brief   definitions for the TMU

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

#ifndef GD32H7XX_TMU_H
#define GD32H7XX_TMU_H

#include "gd32h7xx.h"

/* TMU definitions */
#define TMU                         TMU_BASE

/* registers definitions */
#define TMU_CS                      REG32(TMU + 0x00000000U)    /*!< TMU control and status register */
#define TMU_IDATA                   REG32(TMU + 0x00000004U)    /*!< TMU input data register */
#define TMU_ODATA                   REG32(TMU + 0x00000008U)    /*!< TMU output data register */

/* bits definitions */
/* TMU_CS */
#define TMU_CS_MODE                 BITS(0,3)                   /*!< TMU operation mode selection */
#define TMU_CS_ITRTNUM              BITS(4,7)                   /*!< number of iterations selection */
#define TMU_CS_FACTOR               BITS(8,10)                  /*!< scaling factor */
#define TMU_CS_RIE                  BIT(16)                     /*!< read TMU_ODATA interrupt enable */
#define TMU_CS_RDEN                 BIT(17)                     /*!< read TMU_ODATA DMA request enable */
#define TMU_CS_WDEN                 BIT(18)                     /*!< write TMU_IDATA DMA request enable */
#define TMU_CS_ONUM                 BIT(19)                     /*!< times the TMU_ODATA needs to be read */
#define TMU_CS_INUM                 BIT(20)                     /*!< times the TMU_IDATA needs to be write */
#define TMU_CS_OWIDTH               BIT(21)                     /*!< width of output data */
#define TMU_CS_IWIDTH               BIT(22)                     /*!< width of input data */
#define TMU_CS_ENDF                 BIT(31)                     /*!< end of TMU operation flag */

/* TMU_IDATA */
#define TMU_IDATA_IDATA             BITS(0,31)                  /*!< the input data of TMU operation */

/* TMU_ODATA */
#define TMU_ODATA_ODATA             BITS(0,31)                  /*!< the output data of TMU operation */

/* constants definitions */
/* TMU init parameter struct definitions */
typedef struct
{
    uint32_t mode;                                              /*!< mode of TMU operation */
    uint32_t iterations_number;                                 /*!< number of iterations selection */
    uint32_t scale;                                             /*!< scaling factor */
    uint32_t dma_read;                                          /*!< DMA request to read TMU_ODATA */
    uint32_t dma_write;                                         /*!< DMA request to write TMU_IDATA */
    uint32_t read_times;                                        /*!< times the TMU_ODATA needs to be read */
    uint32_t write_times;                                       /*!< times the TMU_IDATA needs to be write */
    uint32_t output_width;                                      /*!< width of output data */
    uint32_t input_width;                                       /*!< width of input data */
}tmu_parameter_struct;

/* TMU mode definitions */
#define TMU_MODE(regval)            (BITS(0,3) & ((uint32_t)(regval) << 0))
#define TMU_MODE_COS                TMU_MODE(0)                 /*!< mode0: m*cos(��) */
#define TMU_MODE_SIN                TMU_MODE(1)                 /*!< mode1: m*sin(��) */
#define TMU_MODE_ATAN2              TMU_MODE(2)                 /*!< mode2: atan2(y,x) */
#define TMU_MODE_MODULUS            TMU_MODE(3)                 /*!< mode3: sqrt(x^2+y^2) */
#define TMU_MODE_ATAN               TMU_MODE(4)                 /*!< mode4: atan(x) */
#define TMU_MODE_COSH               TMU_MODE(5)                 /*!< mode5: cosh(x) */
#define TMU_MODE_SINH               TMU_MODE(6)                 /*!< mode6: sinh(x) */
#define TMU_MODE_ATANH              TMU_MODE(7)                 /*!< mode7: atanh(x) */
#define TMU_MODE_LN                 TMU_MODE(8)                 /*!< mode8: ln(x) */
#define TMU_MODE_SQRT               TMU_MODE(9)                 /*!< mode9: sqrt(x) */

/* TMU number of iterations definitions */
#define ITERATIONS(regval)          (BITS(4,7) & ((uint32_t)(regval) << 4))
#define TMU_ITERATION_STEPS_4       ITERATIONS(1)               /*!< 4 iteration steps */
#define TMU_ITERATION_STEPS_8       ITERATIONS(2)               /*!< 8 iteration steps */
#define TMU_ITERATION_STEPS_12      ITERATIONS(3)               /*!< 12 iteration steps */
#define TMU_ITERATION_STEPS_16      ITERATIONS(4)               /*!< 16 iteration steps */
#define TMU_ITERATION_STEPS_20      ITERATIONS(5)               /*!< 20 iteration steps */
#define TMU_ITERATION_STEPS_24      ITERATIONS(6)               /*!< 24 iteration steps */

/* TMU scaling factor definitions */
#define SCALE(regval)               (BITS(8,10) & ((uint32_t)(regval) << 8))
#define TMU_SCALING_FACTOR_1        SCALE(0)                    /*!< scaling factor = 1 */
#define TMU_SCALING_FACTOR_2        SCALE(1)                    /*!< scaling factor = 2 */
#define TMU_SCALING_FACTOR_4        SCALE(2)                    /*!< scaling factor = 4 */
#define TMU_SCALING_FACTOR_8        SCALE(3)                    /*!< scaling factor = 8 */
#define TMU_SCALING_FACTOR_16       SCALE(4)                    /*!< scaling factor = 16 */
#define TMU_SCALING_FACTOR_32       SCALE(5)                    /*!< scaling factor = 32 */
#define TMU_SCALING_FACTOR_64       SCALE(6)                    /*!< scaling factor = 64 */
#define TMU_SCALING_FACTOR_128      SCALE(7)                    /*!< scaling factor = 128 */

/* TMU DMA read enable definitions */
#define TMU_READ_DMA_DISABLE        ((uint32_t)0x00000000U)     /*!< disable DMA request to read TMU_ODATA */
#define TMU_READ_DMA_ENABLE         TMU_CS_RDEN                 /*!< enable DMA request to read TMU_ODATA */

/* TMU DMA write enable definitions */
#define TMU_WRITE_DMA_DISABLE       ((uint32_t)0x00000000U)     /*!< disable DMA request to write TMU_IDATA */
#define TMU_WRITE_DMA_ENABLE        TMU_CS_WDEN                 /*!< enable DMA request to write TMU_IDATA */

/* TMU_ODATA read times definitions */
#define TMU_READ_TIMES_1            ((uint32_t)0x00000000U)     /*!< one 32-bit read operation */
#define TMU_READ_TIMES_2            TMU_CS_ONUM                 /*!< two 32-bit read operation */

/* TMU_IDATA write times definitions */
#define TMU_WRITE_TIMES_1           ((uint32_t)0x00000000U)     /*!< one 32-bit write operation */
#define TMU_WRITE_TIMES_2           TMU_CS_INUM                 /*!< two 32-bit write operation */

/* TMU output data width definitions */
#define TMU_OUTPUT_WIDTH_32         ((uint32_t)0x00000000U)     /*!< TMU_ODATA contains the output data in q1.31 format */
#define TMU_OUTPUT_WIDTH_16         TMU_CS_OWIDTH               /*!< TMU_ODATA contains the output data in q1.15 format */

/* TMU input data width definitions */
#define TMU_INPUT_WIDTH_32          ((uint32_t)0x00000000U)     /*!< TMU_IDATA contains the input data in q1.31 format */
#define TMU_INPUT_WIDTH_16          TMU_CS_IWIDTH               /*!< TMU_IDATA contains the input data in q1.15 format */

/* function declarations */
/* initialization functions */
/* reset the TMU registers */
void tmu_deinit(void);
/* initialize the parameters of TMU struct with the default values */
void tmu_struct_para_init(tmu_parameter_struct* init_struct);
/* initialize TMU */
void tmu_init(tmu_parameter_struct* init_struct);

/* interrupt and dma configuration */
/* enable TMU read interrupt */
void tmu_read_interrupt_enable(void);
/* disable TMU read interrupt */
void tmu_read_interrupt_disable(void);
/* enable TMU DMA read request */
void tmu_dma_read_enable(void);
/* disable TMU DMA read request */
void tmu_dma_read_disable(void);
/* enable TMU DMA write request */
void tmu_dma_write_enable(void);
/* disable TMU DMA write request */
void tmu_dma_write_disable(void);

/* TMU data write and read */
/* write one data in q1.31 format */
void tmu_one_q31_write(uint32_t data);
/* write two data in q1.31 format */
void tmu_two_q31_write(uint32_t data1, uint32_t data2);
/* write two data in q1.15 format */
void tmu_two_q15_write(uint16_t data1, uint16_t data2);
/* read one data in q1.31 format */
void tmu_one_q31_read(uint32_t* p);
/* read two data in q1.31 format */
void tmu_two_q31_read(uint32_t* p1, uint32_t* p2);
/* read two data in q1.15 format */
void tmu_two_q15_read(uint16_t* p1, uint16_t* p2);

#endif /* GD32H7XX_TMU_H */
