/**
  ******************************************************************************
  * @file    stm32f2x7_eth_conf.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    13-June-2011
  * @brief   Configuration file for the STM32F2x7 Ethernet driver.  
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F2x7_ETH_CONF_H
#define __STM32F2x7_ETH_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Uncomment the line below when using time stamping and/or IPv4 checksum offload */
#define USE_ENHANCED_DMA_DESCRIPTORS

/* Uncomment the line below if you want to use user defined Delay function
   (for precise timing), otherwise default _eth_delay_ function defined within
   the Ethernet driver is used (less precise timing) */
//#define USE_Delay

#ifdef USE_Delay
  #include "main.h"                /* Header file where the Delay function prototype is exported */  
  #define _eth_delay_    Delay     /* User can provide more timing precise _eth_delay_ function */
#else
  #define _eth_delay_    ETH_Delay /* Default _eth_delay_ function with less precise timing */
#endif


/* Uncomment the line below to allow custom configuration of the Ethernet driver buffers */    
#define CUSTOM_DRIVER_BUFFERS_CONFIG   

#ifdef  CUSTOM_DRIVER_BUFFERS_CONFIG
/* Redefinition of the Ethernet driver buffers size and count */   
 #define ETH_RX_BUF_SIZE    ETH_MAX_PACKET_SIZE  /* buffer size for receive */
 #define ETH_TX_BUF_SIZE    ETH_MAX_PACKET_SIZE  /* buffer size for transmit */
 #define ETH_RXBUFNB        4                    /* 4 Rx buffers of size ETH_RX_BUF_SIZE */
 #define ETH_TXBUFNB        2                    /* 2  Tx buffers of size ETH_TX_BUF_SIZE */
#endif


/* PHY configuration section **************************************************/
/* PHY Reset delay */ 
#define PHY_RESET_DELAY    ((uint32_t)0x000FFFFF) 
/* PHY Configuration delay */ 
#define PHY_CONFIG_DELAY   ((uint32_t)0x00FFFFFF)

/* The PHY status register value change from a PHY to another, so the user have 
   to update this value depending on the used external PHY */
#define PHY_SR    	((uint16_t)16) /* Value for DP83848 PHY */
#define PHY_MICR	((uint16_t)0x11)
#define PHY_MISR	((uint16_t)0x12)
#define PHY_LEDCR	((uint16_t)0x18)
#define PHY_CR		((uint16_t)0x19)
#define PHY_CDCTRL1	((uint16_t)0x1B)
#define PHY_FCSCR	((uint16_t)0x14)

#define MDIX_EN		((uint16_t)1<<15)
#define BIST_START	((uint16_t)1<<8)
#define BIST_STATUS	((uint16_t)1<<9)
#define BIST_CONT_MODE	((uint16_t)1<<5)
#define BIST_ERROR_COUNT(n) (n&0xFF00)>>8

/* The Speed and Duplex mask values change from a PHY to another, so the user
   have to update this value depending on the used external PHY */
#define PHY_SPEED_STATUS            ((uint16_t)0x0002) /* Value for DP83848 PHY */
#define PHY_DUPLEX_STATUS           ((uint16_t)0x0004) /* Value for DP83848 PHY */

   
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */  

#ifdef __cplusplus
}
#endif

#endif /* __STM32F2x7_ETH_CONF_H */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

