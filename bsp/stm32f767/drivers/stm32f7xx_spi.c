/*
 * File      : stm32f7xx_spi.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-10-27     ZYH      first implementation
 */
#include "stm32f7xx_spi.h"
#include <rtdevice.h>
#include <board.h>
struct stm32_hw_spi_cs
{
    rt_uint32_t pin;
};

struct stm32_spi
{
    SPI_TypeDef *Instance;
    struct rt_spi_configuration *cfg;
};


static rt_err_t stm32_spi_init(SPI_TypeDef *spix, struct rt_spi_configuration *cfg)
{
    SPI_HandleTypeDef hspi;
    hspi.Instance = spix;

    if (cfg->mode & RT_SPI_SLAVE)
    {
        hspi.Init.Mode = SPI_MODE_SLAVE;
    }
    else
    {
        hspi.Init.Mode = SPI_MODE_MASTER;
    }
    if (cfg->mode & RT_SPI_3WIRE)
    {
        hspi.Init.Direction = SPI_DIRECTION_1LINE;
    }
    else
    {
        hspi.Init.Direction = SPI_DIRECTION_2LINES;
    }
    if (cfg->data_width == 8)
    {
        hspi.Init.DataSize = SPI_DATASIZE_8BIT;
    }
    else if (cfg->data_width == 16)
    {
        hspi.Init.DataSize = SPI_DATASIZE_16BIT;
    }
    else
    {
        return RT_EIO;
    }
    if (cfg->mode & RT_SPI_CPHA)
    {
        hspi.Init.CLKPhase = SPI_PHASE_2EDGE;
    }
    else
    {
        hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
    }
    if (cfg->mode & RT_SPI_CPOL)
    {
        hspi.Init.CLKPolarity = SPI_POLARITY_HIGH;
    }
    else
    {
        hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
    }
    if (cfg->mode & RT_SPI_NO_CS)
    {
        hspi.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
        hspi.Init.NSS = SPI_NSS_SOFT;
    }
    else
    {
			hspi.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
            hspi.Init.NSS = SPI_NSS_SOFT;
    }
    if(cfg->max_hz >= HAL_RCC_GetPCLK2Freq()/2)
    {
            hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    }
    else if(cfg->max_hz >= HAL_RCC_GetPCLK2Freq()/4)
    {
            hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
    }
    else if(cfg->max_hz >= HAL_RCC_GetPCLK2Freq()/8)
    {
            hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
    }
    else if(cfg->max_hz >= HAL_RCC_GetPCLK2Freq()/16)
    {
            hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
    }
    else if(cfg->max_hz >= HAL_RCC_GetPCLK2Freq()/32)
    {
            hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
    }
    else if(cfg->max_hz >= HAL_RCC_GetPCLK2Freq()/64)
    {
            hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
    }
    else if(cfg->max_hz >= HAL_RCC_GetPCLK2Freq()/128)
    {
            hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
    }
    else
    {
            /*  min prescaler 256 */
            hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
    }
    if (cfg->mode & RT_SPI_MSB)
    {
        hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    }
    else
    {
        hspi.Init.FirstBit = SPI_FIRSTBIT_LSB;
    }
    hspi.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi.Init.CRCPolynomial = 7;
    hspi.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	hspi.State = HAL_SPI_STATE_RESET;
    if (HAL_SPI_Init(&hspi) != HAL_OK)
    {
        return RT_EIO;
    }
    __HAL_SPI_ENABLE(&hspi);
    return RT_EOK;
}
#define SPISTEP(datalen) (((datalen) == 8) ? 1 : 2)
#define SPISEND_1(reg, ptr, datalen)       \
    do                                     \
    {                                      \
        if (datalen == 8)                  \
        {                                  \
            (reg) = *(rt_uint8_t *)(ptr);  \
        }                                  \
        else                               \
        {                                  \
            (reg) = *(rt_uint16_t *)(ptr); \
        }                                  \
    } while (0)
#define SPIRECV_1(reg, ptr, datalen)      \
    do                                    \
    {                                     \
        if (datalen == 8)                 \
        {                                 \
            *(rt_uint8_t *)(ptr) = (reg); \
        }                                 \
        else                              \
        {                                 \
            *(rt_uint16_t *)(ptr) = reg;  \
        }                                 \
    } while (0)


static rt_err_t spitxrx1b(struct stm32_spi *hspi, void *rcvb, const void *sndb)
{
    rt_uint32_t padrcv = 0;
    rt_uint32_t padsnd = 0xFF;
    if (!rcvb && !sndb)
    {
        return RT_ERROR;
    }
    if (!rcvb)
    {
        rcvb = &padrcv;
    }
    if (!sndb)
    {
        sndb = &padsnd;
    }
    while (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE) == RESET)
        ;
    SPISEND_1(hspi->Instance->DR, sndb, hspi->cfg->data_width);
    while (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_RXNE) == RESET)
        ;
    SPIRECV_1(hspi->Instance->DR, rcvb, hspi->cfg->data_width);
    return RT_EOK;
}

static rt_uint32_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    rt_err_t res;
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);
    struct stm32_spi * hspi = (struct stm32_spi *)device->bus->parent.user_data;
    struct stm32_hw_spi_cs *cs = device->parent.user_data;

    if (message->cs_take)
    {
        rt_pin_write(cs->pin, 0);
    }
    const rt_uint8_t *sndb = message->send_buf;
    rt_uint8_t *rcvb = message->recv_buf;
    rt_int32_t length = message->length;
    while (length)
    {
        res = spitxrx1b(hspi, rcvb, sndb);
        if (rcvb)
        {
            rcvb += SPISTEP(hspi->cfg->data_width);
        }
        if (sndb)
        {
            sndb += SPISTEP(hspi->cfg->data_width);
        }
        if (res != RT_EOK)
        {
            break;
        }
        length--;
    }
    /* Wait until Busy flag is reset before disabling SPI */
    while (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_BSY) == SET)
        ;
    if (message->cs_release)
    {
        rt_pin_write(cs->pin, 1);
    }
    return message->length - length;
}


static rt_err_t spi_configure(struct rt_spi_device *device,
    struct rt_spi_configuration *configuration)
{
    struct stm32_spi * hspi = (struct stm32_spi *)device->bus->parent.user_data;
    hspi->cfg = configuration;
    return stm32_spi_init(hspi->Instance, configuration);
}

const struct rt_spi_ops stm_spi_ops =
{
        .configure = spi_configure,
        .xfer = spixfer,
};

int stm32_spi_register_bus(SPI_TypeDef * SPIx,const char * name)
{
    struct rt_spi_bus * spi_bus = (struct rt_spi_bus *)malloc(sizeof(struct rt_spi_bus));
    RT_ASSERT(spi_bus != RT_NULL);
    struct stm32_spi * spi = (struct stm32_spi *)malloc(sizeof(struct stm32_spi));
    RT_ASSERT(spi != RT_NULL);
    spi->Instance = SPIx;
    spi_bus->parent.user_data = spi;
    return rt_spi_bus_register(spi_bus, name, &stm_spi_ops);
}

rt_err_t stm32_spi_bus_attach_device(rt_uint32_t pin,const char * bus_name,const char * device_name)
{
    struct rt_spi_device * spi_device = (struct rt_spi_device *)malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
    struct stm32_hw_spi_cs * cs_pin = (struct stm32_hw_spi_cs *)malloc(sizeof(struct stm32_hw_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);
    cs_pin->pin = pin;
    rt_pin_mode(pin,PIN_MODE_OUTPUT);
    rt_pin_write(pin, 1);
    return rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);
}
//please check heap is enough
int stm32_hw_spi_init(void)
{
		stm32_spi_register_bus(SPI1,"spi1");
		stm32_spi_register_bus(SPI2,"spi2");
		stm32_spi_register_bus(SPI3,"spi3");
		stm32_spi_register_bus(SPI4,"spi4");
		stm32_spi_register_bus(SPI5,"spi5");
    stm32_spi_register_bus(SPI6,"spi6");
//    stm32_spi_bus_attach_device(56,"spi5","cs_g1");
    return 0;
}
INIT_BOARD_EXPORT(stm32_hw_spi_init);


//int w25qxx_register(void)
//{
//	w25qxx_init("flash0","cs_g1");
//	return 0;
//}

//INIT_DEVICE_EXPORT(w25qxx_register);











void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */

  /* USER CODE END SPI1_MspInit 0 */
    /* SPI1 clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**SPI1 GPIO Configuration    
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }
  else if(spiHandle->Instance==SPI2)
  {
  /* USER CODE BEGIN SPI2_MspInit 0 */

  /* USER CODE END SPI2_MspInit 0 */
    /* SPI2 clock enable */
    __HAL_RCC_SPI2_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**SPI2 GPIO Configuration    
    PC1     ------> SPI2_MOSI
    PC2     ------> SPI2_MISO
    PB10     ------> SPI2_SCK 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI2_MspInit 1 */

  /* USER CODE END SPI2_MspInit 1 */
  }
  else if(spiHandle->Instance==SPI3)
  {
  /* USER CODE BEGIN SPI3_MspInit 0 */

  /* USER CODE END SPI3_MspInit 0 */
    /* SPI3 clock enable */
    __HAL_RCC_SPI3_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**SPI3 GPIO Configuration    
    PB2     ------> SPI3_MOSI
    PC10     ------> SPI3_SCK
    PC11     ------> SPI3_MISO 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_SPI3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI3_MspInit 1 */

  /* USER CODE END SPI3_MspInit 1 */
  }
  else if(spiHandle->Instance==SPI4)
  {
  /* USER CODE BEGIN SPI4_MspInit 0 */

  /* USER CODE END SPI4_MspInit 0 */
    /* SPI4 clock enable */
    __HAL_RCC_SPI4_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    /**SPI4 GPIO Configuration    
    PE5     ------> SPI4_MISO
    PE6     ------> SPI4_MOSI
    PE12     ------> SPI4_SCK 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI4;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI4_MspInit 1 */

  /* USER CODE END SPI4_MspInit 1 */
  }
  else if(spiHandle->Instance==SPI5)
  {
  /* USER CODE BEGIN SPI5_MspInit 0 */

  /* USER CODE END SPI5_MspInit 0 */
    /* SPI5 clock enable */
    __HAL_RCC_SPI5_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    /**SPI5 GPIO Configuration    
    PF7     ------> SPI5_SCK
    PF8     ------> SPI5_MISO
    PF9     ------> SPI5_MOSI 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI5;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI5_MspInit 1 */

  /* USER CODE END SPI5_MspInit 1 */
  }
  else if(spiHandle->Instance==SPI6)
  {
  /* USER CODE BEGIN SPI6_MspInit 0 */

  /* USER CODE END SPI6_MspInit 0 */
    /* SPI6 clock enable */
    __HAL_RCC_SPI6_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    /**SPI6 GPIO Configuration    
    PG12     ------> SPI6_MISO
    PG13     ------> SPI6_SCK
    PG14     ------> SPI6_MOSI 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI6;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI6_MspInit 1 */

  /* USER CODE END SPI6_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspDeInit 0 */

  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();
  
    /**SPI1 GPIO Configuration    
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

  /* USER CODE BEGIN SPI1_MspDeInit 1 */

  /* USER CODE END SPI1_MspDeInit 1 */
  }
  else if(spiHandle->Instance==SPI2)
  {
  /* USER CODE BEGIN SPI2_MspDeInit 0 */

  /* USER CODE END SPI2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI2_CLK_DISABLE();
  
    /**SPI2 GPIO Configuration    
    PC1     ------> SPI2_MOSI
    PC2     ------> SPI2_MISO
    PB10     ------> SPI2_SCK 
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_1|GPIO_PIN_2);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10);

  /* USER CODE BEGIN SPI2_MspDeInit 1 */

  /* USER CODE END SPI2_MspDeInit 1 */
  }
  else if(spiHandle->Instance==SPI3)
  {
  /* USER CODE BEGIN SPI3_MspDeInit 0 */

  /* USER CODE END SPI3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI3_CLK_DISABLE();
  
    /**SPI3 GPIO Configuration    
    PB2     ------> SPI3_MOSI
    PC10     ------> SPI3_SCK
    PC11     ------> SPI3_MISO 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_2);

    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_10|GPIO_PIN_11);

  /* USER CODE BEGIN SPI3_MspDeInit 1 */

  /* USER CODE END SPI3_MspDeInit 1 */
  }
  else if(spiHandle->Instance==SPI4)
  {
  /* USER CODE BEGIN SPI4_MspDeInit 0 */

  /* USER CODE END SPI4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI4_CLK_DISABLE();
  
    /**SPI4 GPIO Configuration    
    PE5     ------> SPI4_MISO
    PE6     ------> SPI4_MOSI
    PE12     ------> SPI4_SCK 
    */
    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_12);

  /* USER CODE BEGIN SPI4_MspDeInit 1 */

  /* USER CODE END SPI4_MspDeInit 1 */
  }
  else if(spiHandle->Instance==SPI5)
  {
  /* USER CODE BEGIN SPI5_MspDeInit 0 */

  /* USER CODE END SPI5_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI5_CLK_DISABLE();
  
    /**SPI5 GPIO Configuration    
    PF7     ------> SPI5_SCK
    PF8     ------> SPI5_MISO
    PF9     ------> SPI5_MOSI 
    */
    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9);

  /* USER CODE BEGIN SPI5_MspDeInit 1 */

  /* USER CODE END SPI5_MspDeInit 1 */
  }
  else if(spiHandle->Instance==SPI6)
  {
  /* USER CODE BEGIN SPI6_MspDeInit 0 */

  /* USER CODE END SPI6_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI6_CLK_DISABLE();
  
    /**SPI6 GPIO Configuration    
    PG12     ------> SPI6_MISO
    PG13     ------> SPI6_SCK
    PG14     ------> SPI6_MOSI 
    */
    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14);

  /* USER CODE BEGIN SPI6_MspDeInit 1 */

  /* USER CODE END SPI6_MspDeInit 1 */
  }
} 










