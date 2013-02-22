#ifndef STM32_SPI_H_INCLUDED
#define STM32_SPI_H_INCLUDED

#include <rtdevice.h>

#include "stm32f10x.h"
#include "stm32f10x_spi.h"

#include "board.h"

//#define SPI_USE_DMA

struct stm32_spi_bus
{
    struct rt_spi_bus parent;
    SPI_TypeDef * SPI;
#ifdef SPI_USE_DMA
    DMA_Channel_TypeDef * DMA_Channel_TX;
    DMA_Channel_TypeDef * DMA_Channel_RX;
    uint32_t DMA_Channel_TX_FLAG_TC;
    uint32_t DMA_Channel_TX_FLAG_TE;
    uint32_t DMA_Channel_RX_FLAG_TC;
    uint32_t DMA_Channel_RX_FLAG_TE;
#endif /* SPI_USE_DMA */
};

struct stm32_spi_cs
{
    GPIO_TypeDef * GPIOx;
    uint16_t GPIO_Pin;
};

/* public function list */
rt_err_t stm32_spi_register(SPI_TypeDef * SPI,
                            struct stm32_spi_bus * stm32_spi,
                            const char * spi_bus_name);

#endif // STM32_SPI_H_INCLUDED
