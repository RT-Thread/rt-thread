/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-25     LongfeiMa    transplantation driver of lan8742a
 */ 
#include <rtthread.h>
#include "lan8742a.h"


#include "etharp.h"
#include "ethernetif.h"
#include "stm32h7xx_hal.h"


#include "lwip/opt.h"
#include "lwip/ip4_frag.h"
#include "lwip/def.h"
#include "lwip/inet_chksum.h"
#include "lwip/netif.h"
#include "lwip/snmp.h"
#include "lwip/stats.h"
#include "lwip/pbuf.h"
#include "lwipopts.h"

/** @defgroup LAN8742 LAN8742
  * @{
  */   
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup LAN8742_Private_Defines LAN8742 Private Defines
  * @{
  */
#define LAN8742_SW_RESET_TO    ((uint32_t)500U)	//software reset timeout deadline
#define LAN8742_INIT_TO        ((uint32_t)2000U)//Wait for 2000ms to perform initialization
#define LAN8742_MAX_DEV_ADDR   ((uint32_t)31U)	//用于初始化时，搜索IC挂载的有效地址

#if defined ( __ICCARM__ ) /*!< IAR Compiler */

#pragma location=0x30040000
ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
#pragma location=0x30040060
ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */
#pragma location=0x30040200
uint8_t Rx_Buff[ETH_RX_DESC_CNT][ETH_MAX_PACKET_SIZE]; /* Ethernet Receive Buffers */

#elif defined ( __CC_ARM )  /* MDK ARM Compiler */

__attribute__((at(0x30040000))) ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
__attribute__((at(0x30040060))) ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */
__attribute__((at(0x30040200))) uint8_t Rx_Buff[ETH_RX_DESC_CNT][ETH_MAX_PACKET_SIZE]; /* Ethernet Receive Buffer */

#elif defined ( __GNUC__ ) /* GNU Compiler */ 

ETH_DMADescTypeDef DMARxDscrTab[ETH_RX_DESC_CNT] __attribute__((section(".RxDecripSection"))); /* Ethernet Rx DMA Descriptors */
ETH_DMADescTypeDef DMATxDscrTab[ETH_TX_DESC_CNT] __attribute__((section(".TxDecripSection")));   /* Ethernet Tx DMA Descriptors */
uint8_t Rx_Buff[ETH_RX_DESC_CNT][ETH_MAX_PACKET_SIZE] __attribute__((section(".RxArraySection"))); /* Ethernet Receive Buffers */

#endif

ETH_HandleTypeDef EthHandle;
ETH_TxPacketConfig TxConfig; 


#define MAX_ADDR_LEN	6
struct rt_lan8742_eth
{
    /* inherit from ethernet device */
    struct eth_device parent;

    /* interface address info. */
    rt_uint8_t  dev_addr[MAX_ADDR_LEN];		/* hw address	*/
};
static struct rt_lan8742_eth lan8742_device;

static struct rt_semaphore sem_lock;


/*******************************************************************************
                       PHI IO Functions
*******************************************************************************/
/**
  * @brief  Initializes the MDIO interface GPIO and clocks.
  * @param  None
  * @retval 0 if OK, -1 if ERROR
  */
int32_t ETH_PHY_IO_Init(void)
{  
  /* We assume that MDIO GPIO configuration is already done
     in the ETH_MspInit() else it should be done here 
  */
  
	/* Configure the MDIO Clock */
	HAL_ETH_SetMDIOClockRange(&EthHandle);

	return 0;
}

/**
  * @brief  De-Initializes the MDIO interface .
  * @param  None
  * @retval 0 if OK, -1 if ERROR
  */
int32_t ETH_PHY_IO_DeInit (void)
{
	return 0;
}

/**
  * @brief  Read a PHY register through the MDIO interface.
  * @param  DevAddr: PHY port address
  * @param  RegAddr: PHY register address
  * @param  pRegVal: pointer to hold the register value 
  * @retval 0 if OK -1 if Error
  */
int32_t ETH_PHY_IO_ReadReg(uint32_t DevAddr, uint32_t RegAddr, uint32_t *pRegVal)
{
	if(HAL_ETH_ReadPHYRegister(&EthHandle, DevAddr, RegAddr, pRegVal) != HAL_OK)
	{
		return -1;
	}

	return 0;
}

/**
  * @brief  Write a value to a PHY register through the MDIO interface.
  * @param  DevAddr: PHY port address
  * @param  RegAddr: PHY register address
  * @param  RegVal: Value to be written 
  * @retval 0 if OK -1 if Error
  */
int32_t ETH_PHY_IO_WriteReg(uint32_t DevAddr, uint32_t RegAddr, uint32_t RegVal)
{
	if(HAL_ETH_WritePHYRegister(&EthHandle, DevAddr, RegAddr, RegVal) != HAL_OK)
	{
		return -1;
	}

	return 0;
}

/**
  * @brief  Get the time in millisecons used for internal PHY driver process.
  * @retval Time value
  */
int32_t ETH_PHY_IO_GetTick(void)
{
	return HAL_GetTick();
}

//IC相关结构体
lan8742_Object_t LAN8742 = 
{
	0,	//LAN8742.DevAddr
	0,	//LAN8742.Is_Initialized
	{
		ETH_PHY_IO_Init,	//LAN8742.IO.Init
		ETH_PHY_IO_DeInit,	//LAN8742.IO.DeInit
		ETH_PHY_IO_WriteReg,//LAN8742.IO.WriteReg
		ETH_PHY_IO_ReadReg,	//LAN8742.IO.ReadReg
		ETH_PHY_IO_GetTick,	//LAN8742.IO.GetTick
	},
	NULL,
};


/*******************************************************************************
                       Ethernet MSP Routines
*******************************************************************************/
/**
  * @brief  Initializes the ETH MSP.
  * @param  heth: ETH handle
  * @retval None
*/
void HAL_ETH_MspInit(ETH_HandleTypeDef *heth)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Ethernett MSP init: RMII Mode */

	/* Enable GPIOs clocks */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

/* Ethernet pins configuration ************************************************/
	/*
		RMII_REF_CLK ----------------------> PA1
		RMII_MDIO -------------------------> PA2
		RMII_MDC --------------------------> PC1
		RMII_MII_CRS_DV -------------------> PA7
		RMII_MII_RXD0 ---------------------> PC4
		RMII_MII_RXD1 ---------------------> PC5
		RMII_MII_RXER ---------------------> PG2
		RMII_MII_TX_EN --------------------> PG11
		RMII_MII_TXD0 ---------------------> PG13
		RMII_MII_TXD1 ---------------------> PB13
	*/

	/* Configure PA1, PA2 and PA7 */
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL; 
	GPIO_InitStructure.Alternate = GPIO_AF11_ETH;
	GPIO_InitStructure.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_7;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure PB13 */
	GPIO_InitStructure.Pin = GPIO_PIN_13;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure PC1, PC4 and PC5 */
	GPIO_InitStructure.Pin = GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Configure PG2, PG11, PG13 and PG14 */
	GPIO_InitStructure.Pin =  GPIO_PIN_2 | GPIO_PIN_11 | GPIO_PIN_13;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);	

	/* Enable the Ethernet global Interrupt */
	HAL_NVIC_SetPriority(ETH_IRQn, 0x7, 0);
	HAL_NVIC_EnableIRQ(ETH_IRQn);

	/* Enable Ethernet clocks */
	__HAL_RCC_ETH1MAC_CLK_ENABLE();
	__HAL_RCC_ETH1TX_CLK_ENABLE();
	__HAL_RCC_ETH1RX_CLK_ENABLE();
}

/**
  * @brief  Initialize the lan8742 and configure the needed hardware resources
  * @param  void. 
  * @retval LAN8742_STATUS_OK  if OK
  *         LAN8742_STATUS_ADDRESS_ERROR if cannot find device address
  *         LAN8742_STATUS_READ_ERROR if connot read register
  *         LAN8742_STATUS_WRITE_ERROR if connot write to register
  *         LAN8742_STATUS_RESET_TIMEOUT if cannot perform a software reset
  */
static int32_t LAN8742_Init(lan8742_Object_t *pObj)
{
	uint32_t tickstart = 0, regvalue = 0, addr = 0;
	int32_t status = LAN8742_STATUS_OK;
	
	if(pObj->Is_Initialized == 0)
	{
		if(pObj->IO.Init != 0)
		{
			/* GPIO and Clocks initialization */
			pObj->IO.Init();
		}

		/* for later check */
		pObj->DevAddr = LAN8742_MAX_DEV_ADDR + 1;

		/* Get the device address from special mode register */  
		for(addr = 0; addr <= LAN8742_MAX_DEV_ADDR; addr ++)
		{
			if(pObj->IO.ReadReg(addr, LAN8742_REG_SMR, &regvalue) < 0)
			{ 
				status = LAN8742_STATUS_READ_ERROR;
				/* Can't read from this device address 
				continue with next address */
				continue;
			}

			if((regvalue & LAN8742_SMR_PHY_ADDR) == addr)
			{
				pObj->DevAddr = addr;
				status = LAN8742_STATUS_OK;
				break;
			}
		}

		if(pObj->DevAddr > LAN8742_MAX_DEV_ADDR)
		{
			status = LAN8742_STATUS_ADDRESS_ERROR;
		}

		/* if device address is matched */
		if(status == LAN8742_STATUS_OK)
		{
			/* set a software reset  */
			if(pObj->IO.WriteReg(pObj->DevAddr, LAN8742_REG_BCR, LAN8742_BCR_RESET) >= 0)
			{ 
				/* get software reset status */
				if(pObj->IO.ReadReg(pObj->DevAddr, LAN8742_REG_BCR, &regvalue) >= 0)
				{ 
					tickstart = pObj->IO.GetTick();

					/* wait until software reset is done or timeout occured  */
					while(regvalue & LAN8742_BCR_RESET)
					{
						if((pObj->IO.GetTick() - tickstart) <= LAN8742_SW_RESET_TO)
						{
							if(pObj->IO.ReadReg(pObj->DevAddr, LAN8742_REG_BCR, &regvalue) < 0)
							{ 
								status = LAN8742_STATUS_READ_ERROR;
								break;
							}
						}
						else
						{
							status = LAN8742_STATUS_RESET_TIMEOUT;
						}
					} 
				}
				else
				{
					status = LAN8742_STATUS_READ_ERROR;
				}
			}
			else
			{
				status = LAN8742_STATUS_WRITE_ERROR;
			}
		}
	}
	
	if(status == LAN8742_STATUS_OK)
	{
		tickstart =  pObj->IO.GetTick();

		/* Wait for 2s to perform initialization */
		while((pObj->IO.GetTick() - tickstart) <= LAN8742_INIT_TO)
		{
		}
		pObj->Is_Initialized = 1;
	}

	return status;
}

/**
  * @brief  De-Initialize the lan8742 and it's hardware resources
  * @param  void. 
  * @retval LAN8742_STATUS_ERROR / LAN8742_STATUS_OK
  */
static int32_t LAN8742_DeInit(lan8742_Object_t *pObj)
{
	if(pObj->Is_Initialized)
	{
		if(pObj->IO.DeInit != 0)
		{
			if(pObj->IO.DeInit() < 0)
			{
				return LAN8742_STATUS_ERROR;
			}
		}

		pObj->Is_Initialized = 0;  
	}

	return LAN8742_STATUS_OK;
}

/**
  * @brief  Disable the LAN8742 power down mode.
  * @param  pObj: device object LAN8742_Object_t.  
  * @retval LAN8742_STATUS_OK  if OK
  *         LAN8742_STATUS_READ_ERROR if connot read register
  *         LAN8742_STATUS_WRITE_ERROR if connot write to register
  */
static int32_t LAN8742_DisablePowerDownMode(lan8742_Object_t *pObj)
{
	uint32_t readval = 0;
	int32_t status = LAN8742_STATUS_OK;

	if(pObj->IO.ReadReg(pObj->DevAddr, LAN8742_REG_BCR, &readval) >= 0)
	{
		readval &= ~LAN8742_BCR_POWER_DOWN;

		/* Apply configuration */
		if(pObj->IO.WriteReg(pObj->DevAddr, LAN8742_REG_BCR, readval) < 0)
		{
			status =  LAN8742_STATUS_WRITE_ERROR;
		}
	}
	else
	{
		status = LAN8742_STATUS_READ_ERROR;
	}

	return status;
}

/**
  * @brief  Enable the LAN8742 power down mode.
  * @param  pObj: device object LAN8742_Object_t.  
  * @retval LAN8742_STATUS_OK  if OK
  *         LAN8742_STATUS_READ_ERROR if connot read register
  *         LAN8742_STATUS_WRITE_ERROR if connot write to register
  */
static int32_t LAN8742_EnablePowerDownMode(lan8742_Object_t *pObj)
{
	uint32_t readval = 0;
	int32_t status = LAN8742_STATUS_OK;

	if(pObj->IO.ReadReg(pObj->DevAddr, LAN8742_REG_BCR, &readval) >= 0)
	{
		readval |= LAN8742_BCR_POWER_DOWN;

		/* Apply configuration */
		if(pObj->IO.WriteReg(pObj->DevAddr, LAN8742_REG_BCR, readval) < 0)
		{
			status =  LAN8742_STATUS_WRITE_ERROR;
		}
	}
	else
	{
		status = LAN8742_STATUS_READ_ERROR;
	}

	return status;
}

/**
  * @brief  Start the auto negotiation process.
  * @param  pObj: device object LAN8742_Object_t.  
  * @retval LAN8742_STATUS_OK  if OK
  *         LAN8742_STATUS_READ_ERROR if connot read register
  *         LAN8742_STATUS_WRITE_ERROR if connot write to register
  */
static int32_t LAN8742_StartAutoNego(lan8742_Object_t *pObj)
{
  uint32_t readval = 0;
  int32_t status = LAN8742_STATUS_OK;
  
  if(pObj->IO.ReadReg(pObj->DevAddr, LAN8742_REG_BCR, &readval) >= 0)
  {
    readval |= LAN8742_BCR_ANEG_EN;
  
    /* Apply configuration */
    if(pObj->IO.WriteReg(pObj->DevAddr, LAN8742_REG_BCR, readval) < 0)
    {
      status =  LAN8742_STATUS_WRITE_ERROR;
    }
  }
  else
  {
    status = LAN8742_STATUS_READ_ERROR;
  }
   
  return status;
}

/**
  * @brief  Get the link state of LAN8742 device.
  * @param  pObj: Pointer to device object. 
  * @param  pLinkState: Pointer to link state
  * @retval LAN8742_STATUS_LINK_DOWN  if link is down
  *         LAN8742_STATUS_AUTONEGO_NOTDONE if Auto nego not completed 
  *         LAN8742_STATUS_100MBITS_FULLDUPLEX if 100Mb/s FD
  *         LAN8742_STATUS_100MBITS_HALFDUPLEX if 100Mb/s HD
  *         LAN8742_STATUS_10MBITS_FULLDUPLEX  if 10Mb/s FD
  *         LAN8742_STATUS_10MBITS_HALFDUPLEX  if 10Mb/s HD       
  *         LAN8742_STATUS_READ_ERROR if connot read register
  *         LAN8742_STATUS_WRITE_ERROR if connot write to register
  */
static int32_t LAN8742_GetLinkState(lan8742_Object_t *pObj)
{
	uint32_t readval = 0;
  
	/* Read Status register  */
	if(pObj->IO.ReadReg(pObj->DevAddr, LAN8742_REG_BSR, &readval) < 0)
	{
		return LAN8742_STATUS_READ_ERROR;
	}

	/* Read Status register again */
	if(pObj->IO.ReadReg(pObj->DevAddr, LAN8742_REG_BSR, &readval) < 0)
	{
		return LAN8742_STATUS_READ_ERROR;
	}

	if((readval & LAN8742_BSR_LINK_STAT) == 0)
	{
		/* Return Link Down status */
		return LAN8742_STATUS_LINK_DOWN;    
	}
  
	/* Check Auto negotiaition */
	if(pObj->IO.ReadReg(pObj->DevAddr, LAN8742_REG_BCR, &readval) < 0)
	{
		return LAN8742_STATUS_READ_ERROR;
	}
  
	if((readval & LAN8742_BCR_ANEG_EN) != LAN8742_BCR_ANEG_EN)
	{
		if(((readval & LAN8742_BCR_SPEED_SEL) == LAN8742_BCR_SPEED_SEL) && ((readval & LAN8742_BCR_DUPLEX) == LAN8742_BCR_DUPLEX)) 
		{
			return LAN8742_STATUS_100MBITS_FULLDUPLEX;
		}
		else if ((readval & LAN8742_BCR_SPEED_SEL) == LAN8742_BCR_SPEED_SEL)
		{
			return LAN8742_STATUS_100MBITS_HALFDUPLEX;
		}        
		else if ((readval & LAN8742_BCR_DUPLEX) == LAN8742_BCR_DUPLEX)
		{
			return LAN8742_STATUS_10MBITS_FULLDUPLEX;
		}
		else
		{
			return LAN8742_STATUS_10MBITS_HALFDUPLEX;
		}  		
	}
	else /* Auto Nego enabled */
	{
		if(pObj->IO.ReadReg(pObj->DevAddr, LAN8742_REG_PSCS, &readval) < 0)
		{
			return LAN8742_STATUS_READ_ERROR;
		}

		/* Check if auto nego not done */
		if((readval & LAN8742_PHYSCSR_AUTONEGO_DONE) == 0)
		{
			return LAN8742_STATUS_AUTONEGO_NOTDONE;
		}

		if((readval & LAN8742_PHYSCSR_HCDSPEEDMASK) == LAN8742_PHYSCSR_100BTX_FD)
		{
			return LAN8742_STATUS_100MBITS_FULLDUPLEX;
		}
		else if ((readval & LAN8742_PHYSCSR_HCDSPEEDMASK) == LAN8742_PHYSCSR_100BTX_HD)
		{
			return LAN8742_STATUS_100MBITS_HALFDUPLEX;
		}
		else if ((readval & LAN8742_PHYSCSR_HCDSPEEDMASK) == LAN8742_PHYSCSR_10BT_FD)
		{
			return LAN8742_STATUS_10MBITS_FULLDUPLEX;
		}
		else
		{
			return LAN8742_STATUS_10MBITS_HALFDUPLEX;
		}				
	}
}

/**
  * @brief  Set the link state of LAN8742 device.
  * @param  pObj: Pointer to device object. 
  * @param  pLinkState: link state can be one of the following
  *         LAN8742_STATUS_100MBITS_FULLDUPLEX if 100Mb/s FD
  *         LAN8742_STATUS_100MBITS_HALFDUPLEX if 100Mb/s HD
  *         LAN8742_STATUS_10MBITS_FULLDUPLEX  if 10Mb/s FD
  *         LAN8742_STATUS_10MBITS_HALFDUPLEX  if 10Mb/s HD   
  * @retval LAN8742_STATUS_OK  if OK
  *         LAN8742_STATUS_ERROR  if parameter error  
  *         LAN8742_STATUS_READ_ERROR if connot read register
  *         LAN8742_STATUS_WRITE_ERROR if connot write to register
  */
static int32_t LAN8742_SetLinkState(lan8742_Object_t *pObj, uint32_t LinkState)
{
	uint32_t bcrvalue = 0;
	int32_t status = LAN8742_STATUS_OK;

	if(pObj->IO.ReadReg(pObj->DevAddr, LAN8742_REG_BCR, &bcrvalue) >= 0)
	{
		/* Disable link config (Auto nego, speed and duplex) */
		bcrvalue &= ~(LAN8742_BCR_ANEG_EN | LAN8742_BCR_SPEED_SEL | LAN8742_BCR_DUPLEX);

		if(LinkState == LAN8742_STATUS_100MBITS_FULLDUPLEX)
		{
			bcrvalue |= (LAN8742_BCR_SPEED_SEL | LAN8742_BCR_DUPLEX);
		}
		else if (LinkState == LAN8742_STATUS_100MBITS_HALFDUPLEX)
		{
			bcrvalue |= LAN8742_BCR_SPEED_SEL;
		}
		else if (LinkState == LAN8742_STATUS_10MBITS_FULLDUPLEX)
		{
			bcrvalue |= LAN8742_BCR_DUPLEX;
		}
		else
		{
			/* Wrong link status parameter */
			status = LAN8742_STATUS_ERROR;
		}	
	}
	else
	{
		status = LAN8742_STATUS_READ_ERROR;
	}

	if(status == LAN8742_STATUS_OK)
	{
		/* Apply configuration */
		if(pObj->IO.WriteReg(pObj->DevAddr, LAN8742_REG_BCR, bcrvalue) < 0)
		{
			status = LAN8742_STATUS_WRITE_ERROR;
		}
	}

	return status;
}

/**
  * @brief  Enable loopback mode.
  * @param  pObj: Pointer to device object. 
  * @retval LAN8742_STATUS_OK  if OK
  *         LAN8742_STATUS_READ_ERROR if connot read register
  *         LAN8742_STATUS_WRITE_ERROR if connot write to register
  */
static int32_t LAN8742_EnableLoopbackMode(lan8742_Object_t *pObj)
{
	uint32_t readval = 0;
	int32_t status = LAN8742_STATUS_OK;

	if(pObj->IO.ReadReg(pObj->DevAddr, LAN8742_REG_BCR, &readval) >= 0)
	{
		readval |= LAN8742_BCR_LOOPBACK;

		/* Apply configuration */
		if(pObj->IO.WriteReg(pObj->DevAddr, LAN8742_REG_BCR, readval) < 0)
		{
			status = LAN8742_STATUS_WRITE_ERROR;
		}
	}
	else
	{
		status = LAN8742_STATUS_READ_ERROR;
	}

	return status;
}

/**
  * @brief  Disable loopback mode.
  * @param  pObj: Pointer to device object. 
  * @retval LAN8742_STATUS_OK  if OK
  *         LAN8742_STATUS_READ_ERROR if connot read register
  *         LAN8742_STATUS_WRITE_ERROR if connot write to register
  */
static int32_t LAN8742_DisableLoopbackMode(lan8742_Object_t *pObj)
{
	uint32_t readval = 0;
	int32_t status = LAN8742_STATUS_OK;

	if(pObj->IO.ReadReg(pObj->DevAddr, LAN8742_REG_BCR, &readval) >= 0)
	{
		readval &= ~LAN8742_BCR_LOOPBACK;

		/* Apply configuration */
		if(pObj->IO.WriteReg(pObj->DevAddr, LAN8742_REG_BCR, readval) < 0)
		{
			status =  LAN8742_STATUS_WRITE_ERROR;
		}
	}
	else
	{
		status = LAN8742_STATUS_READ_ERROR;
	}

	return status;
}

/**
  * @brief  Enable IT source.
  * @param  pObj: Pointer to device object. 
  * @param  Interrupt: IT source to be enabled
  *         should be a value or a combination of the following:
  *         LAN8742_WOL_IT                     
  *         LAN8742_ENERGYON_IT                
  *         LAN8742_AUTONEGO_COMPLETE_IT       
  *         LAN8742_REMOTE_FAULT_IT            
  *         LAN8742_LINK_DOWN_IT               
  *         LAN8742_AUTONEGO_LP_ACK_IT         
  *         LAN8742_PARALLEL_DETECTION_FAULT_IT
  *         LAN8742_AUTONEGO_PAGE_RECEIVED_IT
  * @retval LAN8742_STATUS_OK  if OK
  *         LAN8742_STATUS_READ_ERROR if connot read register
  *         LAN8742_STATUS_WRITE_ERROR if connot write to register
  */
static int32_t LAN8742_EnableIT(lan8742_Object_t *pObj, uint32_t Interrupt)
{
  uint32_t readval = 0;
  int32_t status = LAN8742_STATUS_OK;
  
  if(pObj->IO.ReadReg(pObj->DevAddr, LAN8742_REG_IM, &readval) >= 0)
  {
    readval |= Interrupt;
  
    /* Apply configuration */
    if(pObj->IO.WriteReg(pObj->DevAddr, LAN8742_REG_IM, readval) < 0)
    {
      status =  LAN8742_STATUS_WRITE_ERROR;
    }
  }
  else
  {
    status = LAN8742_STATUS_READ_ERROR;
  }
   
  return status;
}

/**
  * @brief  Disable IT source.
  * @param  pObj: Pointer to device object. 
  * @param  Interrupt: IT source to be disabled
  *         should be a value or a combination of the following:
  *         LAN8742_WOL_IT                     
  *         LAN8742_ENERGYON_IT                
  *         LAN8742_AUTONEGO_COMPLETE_IT       
  *         LAN8742_REMOTE_FAULT_IT            
  *         LAN8742_LINK_DOWN_IT               
  *         LAN8742_AUTONEGO_LP_ACK_IT         
  *         LAN8742_PARALLEL_DETECTION_FAULT_IT
  *         LAN8742_AUTONEGO_PAGE_RECEIVED_IT
  * @retval LAN8742_STATUS_OK  if OK
  *         LAN8742_STATUS_READ_ERROR if connot read register
  *         LAN8742_STATUS_WRITE_ERROR if connot write to register
  */
static int32_t LAN8742_DisableIT(lan8742_Object_t *pObj, uint32_t Interrupt)
{
  uint32_t readval = 0;
  int32_t status = LAN8742_STATUS_OK;
  
  if(pObj->IO.ReadReg(pObj->DevAddr, LAN8742_REG_IM, &readval) >= 0)
  {
    readval &= ~Interrupt;
  
    /* Apply configuration */
    if(pObj->IO.WriteReg(pObj->DevAddr, LAN8742_REG_IM, readval) < 0)
    {
      status = LAN8742_STATUS_WRITE_ERROR;
    }
  }
  else
  {
    status = LAN8742_STATUS_READ_ERROR;
  }
   
  return status;
}

/**
  * @brief  Clear IT flag.
  * @param  pObj: Pointer to device object. 
  * @param  Interrupt: IT flag to be cleared
  *         should be a value or a combination of the following:
  *         LAN8742_WOL_IT                     
  *         LAN8742_ENERGYON_IT                
  *         LAN8742_AUTONEGO_COMPLETE_IT       
  *         LAN8742_REMOTE_FAULT_IT            
  *         LAN8742_LINK_DOWN_IT               
  *         LAN8742_AUTONEGO_LP_ACK_IT         
  *         LAN8742_PARALLEL_DETECTION_FAULT_IT
  *         LAN8742_AUTONEGO_PAGE_RECEIVED_IT
  * @retval LAN8742_STATUS_OK  if OK
  *         LAN8742_STATUS_READ_ERROR if connot read register
  */
static int32_t  LAN8742_ClearIT(lan8742_Object_t *pObj, uint32_t Interrupt)
{
  uint32_t readval = 0;
  int32_t status = LAN8742_STATUS_OK;  
  
  if(pObj->IO.ReadReg(pObj->DevAddr, LAN8742_REG_ISF, &readval) < 0)
  {
    status =  LAN8742_STATUS_READ_ERROR;
  }
  
  return status;
}

/**
  * @brief  Get IT Flag status.
  * @param  pObj: Pointer to device object. 
  * @param  Interrupt: IT Flag to be checked, 
  *         should be a value or a combination of the following:
  *         LAN8742_WOL_IT                     
  *         LAN8742_ENERGYON_IT                
  *         LAN8742_AUTONEGO_COMPLETE_IT       
  *         LAN8742_REMOTE_FAULT_IT            
  *         LAN8742_LINK_DOWN_IT               
  *         LAN8742_AUTONEGO_LP_ACK_IT         
  *         LAN8742_PARALLEL_DETECTION_FAULT_IT
  *         LAN8742_AUTONEGO_PAGE_RECEIVED_IT  
  * @retval 1 IT flag is SET
  *         0 IT flag is RESET
  *         LAN8742_STATUS_READ_ERROR if connot read register
  */
static int32_t LAN8742_GetITStatus(lan8742_Object_t *pObj, uint32_t Interrupt)
{
  uint32_t readval = 0;
  int32_t status = 0;

  if(pObj->IO.ReadReg(pObj->DevAddr, LAN8742_REG_ISF, &readval) >= 0)
  {
    status = ((readval & Interrupt) == Interrupt);
  }
  else
  {
    status = LAN8742_STATUS_READ_ERROR;
  }
	
  return status;
}

static rt_err_t rt_lan8742_init(rt_device_t dev)
{
	return RT_EOK;
}

static rt_err_t rt_lan8742_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t rt_lan8742_close(rt_device_t dev)
{
	LAN8742_DeInit(&LAN8742);
	LAN8742_DisableIT(&LAN8742, LAN8742_INT_ALL);
	LAN8742_EnablePowerDownMode(&LAN8742);

    return RT_EOK;
}

static rt_size_t rt_lan8742_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_size_t rt_lan8742_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_lan8742_control(rt_device_t dev, int cmd, void *args)
{
	switch (cmd)
	{
		case NIOCTL_GADDR:
			/* get mac address */
			if (args)
				rt_memcpy(args, lan8742_device.dev_addr, 6);
			else
				return -RT_ERROR;
			break;
		default :
			break;
	}

	return RT_EOK;
}

/* ethernet device interface */
/* transmit packet. */
rt_err_t rt_lan8742_tx( rt_device_t dev, struct pbuf* p)
{
	uint32_t i=0, framelen = 0;
	struct pbuf *q;
	err_t errval = ERR_OK;
	ETH_BufferTypeDef Txbuffer[ETH_TX_DESC_CNT];
  
	/* lock LAN8742 device */
    rt_sem_take(&sem_lock, RT_WAITING_FOREVER);
	
	memset(Txbuffer, 0 , 4*sizeof(ETH_BufferTypeDef));

	for(q = p; q != NULL; q = q->next)
	{
		if(i >= ETH_TX_DESC_CNT)	
			return ERR_IF;

		Txbuffer[i].buffer = q->payload;
		Txbuffer[i].len = q->len;
		framelen += q->len;

		if(i>0)
		{
			Txbuffer[i-1].next = &Txbuffer[i];
		}

		i++;
	}

	TxConfig.Length = framelen;
	TxConfig.TxBuffer = Txbuffer;

	/* Clean and Invalidate data cache */
	SCB_CleanInvalidateDCache();  

	HAL_ETH_Transmit(&EthHandle, &TxConfig, 0);//Transmit an ETH frame in blocking mode

    /* unlock LAN8742 device */
    rt_sem_release(&sem_lock);

    return errval;
}

/* reception packet. */
struct pbuf *rt_lan8742_rx(rt_device_t dev)
{
	struct pbuf* p = RT_NULL;
	ETH_BufferTypeDef RxBuff;
	uint32_t framelength = 0;
	
    /* lock LAN8742 device */
    rt_sem_take(&sem_lock, RT_WAITING_FOREVER);
	
	/* Clean and Invalidate data cache */
	SCB_CleanInvalidateDCache();

	if(HAL_ETH_GetRxDataBuffer(&EthHandle, &RxBuff) == HAL_OK) 
	{
		HAL_ETH_GetRxDataLength(&EthHandle, &framelength);

		p = pbuf_alloc(PBUF_RAW, framelength, PBUF_RAM);

		if(p != NULL)
		{
			pbuf_take(p, (void *)RxBuff.buffer, framelength);
		}

	}
	HAL_ETH_BuildRxDescriptors(&EthHandle);
	
    /* unlock LAN8742 device */
    rt_sem_release(&sem_lock);

    return p;
}

/**
  * @brief  Custom Rx pbuf free callback
  * @param  pbuf: pbuf to be freed
  * @retval None
  */
static void pbuf_free_custom(struct pbuf *p)
{
	if(p != NULL)
	{
		p->flags = 0;
		p->next = NULL;
		p->len = p->tot_len = 0;
		p->ref = 0;
		p->payload = NULL;
	}
}


/** tell tcpip stack if link state is changed
 *  
 *  periodic call by timer or thread to check link states
 * 
 */
static void update_link_status(void* param)
{
	(void)param;

	int32_t curPhyStatus = LAN8742_GetLinkState(&LAN8742);
	int8_t isLinkUp = (curPhyStatus != LAN8742_STATUS_READ_ERROR && curPhyStatus != LAN8742_STATUS_LINK_DOWN) ? 1 : 0;

	if(isLinkUp != lan8742_device.parent.link_status)
	{
		eth_device_linkchange(&(lan8742_device.parent), isLinkUp);
	}
	
}

int rt_hw_lan8742a_init(void)
{
	uint32_t idx, duplex, speed = 0;
	int32_t PHYLinkState;
	ETH_MACConfigTypeDef MACConf;
	uint8_t macaddress[6]= {ETH_MAC_ADDR0, ETH_MAC_ADDR1, ETH_MAC_ADDR2, 
	                        ETH_MAC_ADDR3, ETH_MAC_ADDR4, ETH_MAC_ADDR5};

	EthHandle.Instance = ETH;  
	EthHandle.Init.MACAddr = macaddress;
	EthHandle.Init.MediaInterface = HAL_ETH_RMII_MODE;
	EthHandle.Init.RxDesc = DMARxDscrTab;
	EthHandle.Init.TxDesc = DMATxDscrTab;
	EthHandle.Init.RxBuffLen = ETH_MAX_PACKET_SIZE;

	/* configure ethernet peripheral (GPIOs, clocks, MAC, DMA) */
	HAL_ETH_Init(&EthHandle);
  
	for(idx = 0; idx < ETH_RX_DESC_CNT; idx ++)
	{
		HAL_ETH_DescAssignMemory(&EthHandle, idx, Rx_Buff[idx], NULL);
	}
	
	memset(&TxConfig, 0 , sizeof(ETH_TxPacketConfig));  
	TxConfig.Attributes = ETH_TX_PACKETS_FEATURES_CSUM | ETH_TX_PACKETS_FEATURES_CRCPAD;
	TxConfig.ChecksumCtrl = ETH_CHECKSUM_IPHDR_PAYLOAD_INSERT_PHDR_CALC;
	TxConfig.CRCPadCtrl = ETH_CRC_PAD_INSERT;
	
	/* Initialize the LAN8742 ETH PHY */
	LAN8742_Init(&LAN8742);
  
	/* Get link state */  
	PHYLinkState = LAN8742_GetLinkState(&LAN8742);

	/* Get link state */  
	if(PHYLinkState <= LAN8742_STATUS_LINK_DOWN)
	{
		//
	}
	else 
	{
		switch (PHYLinkState)
		{
			case LAN8742_STATUS_100MBITS_FULLDUPLEX:
				duplex = ETH_FULLDUPLEX_MODE;
				speed = ETH_SPEED_100M;
				break;
			case LAN8742_STATUS_100MBITS_HALFDUPLEX:
				duplex = ETH_HALFDUPLEX_MODE;
				speed = ETH_SPEED_100M;
				break;
			case LAN8742_STATUS_10MBITS_FULLDUPLEX:
				duplex = ETH_FULLDUPLEX_MODE;
				speed = ETH_SPEED_10M;
				break;
			case LAN8742_STATUS_10MBITS_HALFDUPLEX:
				duplex = ETH_HALFDUPLEX_MODE;
				speed = ETH_SPEED_10M;
				break;
			default:
				duplex = ETH_FULLDUPLEX_MODE;
				speed = ETH_SPEED_100M;
				break;      
		}

		/* Get MAC Config MAC */
		HAL_ETH_GetMACConfig(&EthHandle, &MACConf); 
		MACConf.DuplexMode = duplex;
		MACConf.Speed = speed;
		HAL_ETH_SetMACConfig(&EthHandle, &MACConf);
		HAL_ETH_Start_IT(&EthHandle);
	}
	
    rt_sem_init(&sem_lock, "eth_lock", 1, RT_IPC_FLAG_FIFO);
	
	rt_memcpy(lan8742_device.dev_addr, macaddress, 6);
	
    lan8742_device.parent.parent.init       = rt_lan8742_init;
    lan8742_device.parent.parent.open       = rt_lan8742_open;
    lan8742_device.parent.parent.close      = rt_lan8742_close;
    lan8742_device.parent.parent.read       = rt_lan8742_read;
    lan8742_device.parent.parent.write      = rt_lan8742_write;
    lan8742_device.parent.parent.control    = rt_lan8742_control;
    lan8742_device.parent.parent.user_data  = RT_NULL;

    lan8742_device.parent.eth_rx     = rt_lan8742_rx;
    lan8742_device.parent.eth_tx     = rt_lan8742_tx;

    eth_device_init(&(lan8742_device.parent), "e0");

	/* start link check timer */
	rt_uint8_t timerflag = RT_TIMER_FLAG_PERIODIC;

#ifdef RT_USING_TIMER_SOFT
		timerflag |= RT_TIMER_FLAG_SOFT_TIMER;
#endif

	rt_timer_t linkTimer = rt_timer_create("ethlink", 
											update_link_status, 
											RT_NULL, 
											RT_TICK_PER_SECOND, 
											   timerflag);
		
	if(RT_NULL == linkTimer)
	{
		rt_kprintf("ethernet: link check timer create failed.");
		return -RT_ERROR;
	}

	rt_timer_start(linkTimer);

	return 0;
}
INIT_DEVICE_EXPORT(rt_hw_lan8742a_init);


#ifdef  RT_USING_LWIP
/**
  * @brief  This function handles Ethernet interrupt request.
  * @param  None
  * @retval None
  */
void ETH_IRQHandler(void)
{
	HAL_ETH_IRQHandler(&EthHandle);
}
#endif /* RT_USING_LWIP */

/**
  * @brief  Ethernet Rx Transfer completed callback
  * @param  heth: ETH handle
  * @retval None
  */
void HAL_ETH_RxCpltCallback(ETH_HandleTypeDef *heth)
{
	/* a frame has been received */
	eth_device_ready(&(lan8742_device.parent));
}



