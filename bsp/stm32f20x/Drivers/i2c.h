#ifndef I2C_H
#define I2C_H

#include "stm32f2xx.h"

/* Exported constants --------------------------------------------------------*/

#define	SR1_AF_Set				((uint16_t)0x0400)
#define	SR1_ARLO_Set			((uint16_t)0x0200)
#define	SR1_BERR_Set			((uint16_t)0x0100)
#define	SR1_ADDR_Set			((uint16_t)0x0002)
#define	SR1_SB_Set				((uint16_t)0x0001)


#define SR2_BUSY				((uint16_t)0x0002)
#define SR2_MSL					((uint16_t)0x0001)

#define CR1_SWRST_Set			((uint16_t)0x8000)
/* I2C SPE mask */
#define CR1_PE_Set              ((uint16_t)0x0001)
#define CR1_PE_Reset            ((uint16_t)0xFFFE)

/* I2C START mask */
#define CR1_START_Set           ((uint16_t)0x0100)
#define CR1_START_Reset         ((uint16_t)0xFEFF)

#define CR1_POS_Set           ((uint16_t)0x0800)
#define CR1_POS_Reset         ((uint16_t)0xF7FF)

/* I2C STOP mask */
#define CR1_STOP_Set            ((uint16_t)0x0200)
#define CR1_STOP_Reset          ((uint16_t)0xFDFF)

/* I2C ACK mask */
#define CR1_ACK_Set             ((uint16_t)0x0400)
#define CR1_ACK_Reset           ((uint16_t)0xFBFF)

/* I2C ENARP mask */
#define CR1_ENARP_Set           ((uint16_t)0x0010)
#define CR1_ENARP_Reset         ((uint16_t)0xFFEF)

/* I2C NOSTRETCH mask */
#define CR1_NOSTRETCH_Set       ((uint16_t)0x0080)
#define CR1_NOSTRETCH_Reset     ((uint16_t)0xFF7F)

/* I2C registers Masks */
#define CR1_CLEAR_Mask          ((uint16_t)0xFBF5)

/* I2C DMAEN mask */
#define CR2_DMAEN_Set           ((uint16_t)0x0800)
#define CR2_DMAEN_Reset         ((uint16_t)0xF7FF)

/* I2C LAST mask */
#define CR2_LAST_Set            ((uint16_t)0x1000)
#define CR2_LAST_Reset          ((uint16_t)0xEFFF)

/* I2C FREQ mask */
#define CR2_FREQ_Reset          ((uint16_t)0xFFC0)

/* I2C ADD0 mask */
#define OAR1_ADD0_Set           ((uint16_t)0x0001)
#define OAR1_ADD0_Reset         ((uint16_t)0xFFFE)

/* I2C ENDUAL mask */
#define OAR2_ENDUAL_Set         ((uint16_t)0x0001)
#define OAR2_ENDUAL_Reset       ((uint16_t)0xFFFE)

/* I2C ADD2 mask */
#define OAR2_ADD2_Reset         ((uint16_t)0xFF01)

/* I2C F/S mask */
#define CCR_FS_Set              ((uint16_t)0x8000)

/* I2C CCR mask */
#define CCR_CCR_Set             ((uint16_t)0x0FFF)

/* I2C FLAG mask */
#define FLAG_Mask               ((uint32_t)0x00FFFFFF)

/* I2C Interrupt Enable mask */
#define ITEN_Mask               ((uint32_t)0x07000000)


#define I2C_IT_BUF                      ((uint16_t)0x0400)
#define I2C_IT_EVT                      ((uint16_t)0x0200)
#define I2C_IT_ERR                      ((uint16_t)0x0100)


#define  ClockSpeed            400000

#define I2C_DIRECTION_TX 0
#define I2C_DIRECTION_RX 1

#define OwnAddress1 0x28
#define OwnAddress2 0x30


#define I2C1_DMA_CHANNEL_TX           DMA1_Stream6
#define I2C1_DMA_CHANNEL_RX           DMA1_Stream0
#define I2C1_DMA_TX_IRQn	          DMA1_Stream6_IRQn
#define I2C1_DMA_RX_IRQn              DMA1_Stream0_IRQn
								  
#define I2C2_DMA_CHANNEL_TX           DMA1_Stream2
#define I2C2_DMA_CHANNEL_RX           DMA1_Stream7
#define I2C2_DMA_TX_IRQn	          DMA1_Stream2_IRQn
#define I2C2_DMA_RX_IRQn              DMA1_Stream7_IRQn

#define I2C1_DR_Address              0x40005410
#define I2C2_DR_Address              0x40005810

#define I2C1_SDA_PIN                  GPIO_Pin_7
#define I2C1_SCL_PIN                  GPIO_Pin_6
#define I2C1_SDA_SOURCE               GPIO_PinSource7
#define I2C1_SCL_SOURCE               GPIO_PinSource6
#define I2C1_GPIO_PORT          	  GPIOB 
#define I2C1_GPIO_CLK          		  RCC_AHB1Periph_GPIOB
#define I2C1_CLK                      RCC_APB1Periph_I2C1

#define I2C2_SDA_PIN                  GPIO_Pin_11
#define I2C2_SCL_PIN                  GPIO_Pin_10
#define I2C2_SDA_SOURCE               GPIO_PinSource11
#define I2C2_SCL_SOURCE               GPIO_PinSource10
#define I2C2_GPIO_PORT          	  GPIOB 
#define I2C2_GPIO_CLK          		  RCC_AHB1Periph_GPIOB
#define I2C2_CLK                      RCC_APB1Periph_I2C1

#define I2C_MEM_1Byte			      1
#define I2C_MEM_2Bytes				  2

typedef enum
{
    Error = 0,
    Success = !Error
}Status;

typedef enum
{
    Polling = 0x00,
    Interrupt = 0x01,
    DMA = 0x02
} I2C_ProgrammingModel;

void I2C1_INIT();
Status I2C_AcknowledgePolling(I2C_TypeDef* I2Cx ,uint8_t Addr);
Status I2C_IORW(I2C_TypeDef* I2Cx, uint8_t* pBuffer, uint32_t NumByteToRead, uint16_t memAddr, uint8_t SlaveAddress , uint8_t MemType );

#endif