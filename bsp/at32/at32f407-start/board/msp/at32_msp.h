/**
  ******************************************************************************
  * @file    at32_msp.h
  * @author  Artery Technology
  * @version V1.0.0
  * @date    2020-01-10
  * @brief   Msp header file
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, ARTERYTEK SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2018 ArteryTek</center></h2>
  ******************************************************************************
  */

#ifndef __AT32_MSP_H__
#define __AT32_MSP_H__

void at32_msp_usart_init(void *Instance);
void at32_msp_spi_init(void *Instance);
void at32_msp_tmr_init(void *Instance);
void at32_msp_i2c_init(void *Instance);
void at32_msp_sdio_init(void *Instance);
void at32_msp_adc_init(void *Instance);
void at32_msp_hwtmr_init(void *Instance);

#endif /* __AT32_MSP_H__ */
