#ifndef STM32_SPI_H_INCLUDED
#define STM32_SPI_H_INCLUDED

#include <rtdevice.h>

#include "stm32f10x.h"
#include "stm32f10x_spi.h"

#include "board.h"

#if defined(SPI1_USING_DMA) || defined(SPI2_USING_DMA) ||  defined(SPI3_USING_DMA)
#define SPI_USE_DMA
#endif /*defined(SPI1_USING_DMA) || defined(SPI2_USING_DMA) ||  defined(SPI3_USING_DMA)*/

#ifdef SPI_USE_DMA

#define SPI_DMA_RX_DONE    0x01
#define SPI_DMA_TX_DONE    0x02
#define SPI_DMA_COMPLETE   (SPI_DMA_RX_DONE | SPI_DMA_TX_DONE)

struct stm32_spi_dma_private
{
    DMA_Channel_TypeDef * DMA_Channel_TX;
    DMA_Channel_TypeDef * DMA_Channel_RX;
    uint32_t DMA_Channel_TX_FLAG_TC;
    uint32_t DMA_Channel_TX_FLAG_TE;
    uint32_t DMA_Channel_RX_FLAG_TC;
    uint32_t DMA_Channel_RX_FLAG_TE;
    uint8_t tx_irq_ch;
    uint8_t rx_irq_ch;
    uint32_t tx_gl_flag;
    uint32_t rx_gl_flag;
};
struct stm32_spi_dma
{
    const struct stm32_spi_dma_private *priv_data;
    struct rt_event event;
};
#endif /*SPI_USE_DMA*/
struct stm32_spi_bus
{
    struct rt_spi_bus parent;
    SPI_TypeDef * SPI;
#ifdef SPI_USE_DMA
    struct stm32_spi_dma *dma;
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
