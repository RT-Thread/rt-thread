/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
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
 */
 
#include "fsl_edma_driver.h"
#if FSL_FEATURE_SOC_EDMA_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*! @brief Edma Handler*/
#if (FSL_RTOS_MQX)
#if  (FSL_FEATURE_EDMA_MODULE_CHANNEL == 4)

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA0_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(0);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA1_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(1);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA2_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(2);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA3_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(3);
}

#elif (FSL_FEATURE_EDMA_MODULE_CHANNEL == 8)

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA0_DMA4_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(0);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA1_DMA5_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(1);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA2_DMA6_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(2);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA3_DMA7_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(3);
}

#elif (FSL_FEATURE_EDMA_MODULE_CHANNEL <= 16)
/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA0_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(0);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA1_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(1);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA2_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(2);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA3_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(3);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA4_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(4);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA5_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(5);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA6_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(6);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA7_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(7);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA8_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(8);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA9_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(9);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA10_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(10);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA11_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(11);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA12_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(12);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA13_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(13);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA14_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(14);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA15_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(15);
}

#else
void MQX_DMA0_DMA16_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(0);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA1_DMA17_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(1);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA2_DMA18_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(2);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA3_DMA19_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(3);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA4_DMA20_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(4);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA5_DMA21_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(5);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA6_DMA22_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(6);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA7_DMA23_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(7);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA8_DMA24_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(8);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA9_DMA25_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(9);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA10_DMA26_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(10);
}


/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA11_DMA27_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(11);
}


/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA12_DMA28_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(12);
}


/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA13_DMA29_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(13);
}


/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA14_DMA30_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(14);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void MQX_DMA15_DMA31_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(15);
}
#endif

#if FSL_FEATURE_EDMA_HAS_ERROR_IRQ
/*! @brief EDMA ERROR IRQ handler with the same name in the startup code*/
void MQX_DMA_Error_IRQHandler(void)
{
    EDMA_DRV_ErrorIRQHandler(0);
}
#endif
#else
#if  (FSL_FEATURE_EDMA_MODULE_CHANNEL == 4)

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA0_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(0);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA1_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(1);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA2_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(2);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA3_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(3);
}

#elif (FSL_FEATURE_EDMA_MODULE_CHANNEL == 8)

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA0_DMA4_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(0);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA1_DMA5_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(1);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA2_DMA6_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(2);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA3_DMA7_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(3);
}

#elif (FSL_FEATURE_EDMA_MODULE_CHANNEL <= 16)
/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA0_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(0);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA1_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(1);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA2_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(2);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA3_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(3);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA4_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(4);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA5_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(5);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA6_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(6);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA7_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(7);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA8_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(8);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA9_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(9);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA10_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(10);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA11_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(11);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA12_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(12);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA13_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(13);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA14_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(14);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA15_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(15);
}

#else
void DMA0_DMA16_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(0);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA1_DMA17_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(1);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA2_DMA18_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(2);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA3_DMA19_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(3);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA4_DMA20_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(4);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA5_DMA21_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(5);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA6_DMA22_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(6);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA7_DMA23_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(7);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA8_DMA24_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(8);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA9_DMA25_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(9);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA10_DMA26_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(10);
}


/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA11_DMA27_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(11);
}


/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA12_DMA28_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(12);
}


/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA13_DMA29_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(13);
}


/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA14_DMA30_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(14);
}

/*! @brief EDMA IRQ handler with the same name in the startup code*/
void DMA15_DMA31_IRQHandler(void)
{
    EDMA_DRV_IRQHandler(15);
}
#endif

#if FSL_FEATURE_EDMA_HAS_ERROR_IRQ
/*! @brief EDMA ERROR IRQ handler with the same name in the startup code*/
void DMA_Error_IRQHandler(void)
{
    EDMA_DRV_ErrorIRQHandler(0);
}
#endif
#endif
#endif
/*******************************************************************************
 * EOF
 ******************************************************************************/

