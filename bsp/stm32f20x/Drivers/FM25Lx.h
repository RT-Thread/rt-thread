#ifndef FM25LX_H
#define FM25LX_H

#define FM25_WREN	0x06
#define FM25_WRDI	0x04
#define FM25_RDSR	0x05
#define FM25_WRSR	0x01
#define FM25_READ	0x03
#define FM25_WRITE	0x02
#define FM25_WEL	0x02
#define FM25_WPEN	0x80

#define FM25CL64B
//#define FM25LC256

#ifdef FM25CL64B
#define FM25_MAXSIZE 8192
#elif defined(FM25LC256)
#define FM25_MAXSIZE 32768
#endif

#define FM25_SPI             	SPI3
#define FM25_SPI_GPIO        	GPIOB
#define FM25_SPI_MOSI        	GPIO_Pin_5
#define FM25_SPI_MISO        	GPIO_Pin_4
#define FM25_SPI_SCK        	GPIO_Pin_3
#define FM25_SPI_NSS_GPIO		GPIOD
#define FM25_SPI_NSS_PIN       	GPIO_Pin_10
#define FM25_SPI_CLK         	RCC_APB1Periph_SPI3
#define FM25_SPI_GPIO_CLK    	RCC_AHB1Periph_GPIOB
#define FM25_SPI_NSS_GPIO_CLK  	RCC_AHB1Periph_GPIOD

#define FM25_SPI_DMA_CLK     	RCC_AHB1Periph_DMA1
#define FM25_SPI_DMA_Channel	DMA_Channel_0
#define FM25_SPI_RX_DMA_Stream	DMA1_Stream0
#define FM25_SPI_RX_DMA_IRQ  	DMA1_Stream0_IRQn
#define FM25_SPI_RX_DMA_FLAG    DMA_IT_TCIF0
#define FM25_SPI_TX_DMA_Stream	DMA1_Stream5
#define FM25_SPI_TX_DMA_IRQ  	DMA1_Stream5_IRQn
#define FM25_SPI_TX_DMA_FLAG    DMA_IT_TCIF5
#define FM25_SPI_DR_Base     	0x4003C00C

#endif