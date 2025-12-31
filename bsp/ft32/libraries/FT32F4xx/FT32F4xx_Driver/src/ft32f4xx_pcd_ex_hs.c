/**
  ******************************************************************************
  * @file    			ft32f4xx_pcd_ex_hs.c
  * @author  			FMD XA
  * @brief   			This file provides firmware functions to manage the following 
  *          			functionalities of the USB Peripheral Controller:
  *           		+ Extended features functions
  * @version 			V1.0.0           
  * @data		 			2025-04-01
  */
/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"
#include "ft32f4xx_rcc.h"


/** @addtogroup FT32F4xx_DRIVER
  * @{
  */

#ifdef PCD_MODULE_ENABLED
#if defined (USB_OTG_HS)
/** @defgroup PCD_HS PCD
  * @brief PCD HS module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/


/* Exported functions --------------------------------------------------------*/
/** @defgroup PCDEx_HS_Exported_Functions PCDEx Exported Functions
  * @{
  */

/** @defgroup PCDEx_HS_Exported_Functions_Group1 Peripheral Control functions
  * @brief    PCDEx control functions
  *
@verbatim
 ===============================================================================
          ##### Extended features functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
          (+) Update FIFO configuration
@endverbatim
  * @{
  */
#if defined (USB_OTG_HS)
/**
  * @brief  Set Tx FIFO
  * @param  fifo The number of Tx fifo
  * @param  size Fifo size
  * @retval none
  */
void PCDEx_HS_SetTxFiFo(uint8_t fifo, uint16_t size)
{
  uint8_t i;
  uint32_t Tx_Offset;

  /*  TXn min size = 16 words. (n  : Transmit FIFO index)
      When a TxFIFO is not used, the Configuration should be as follows:
          case 1 :  n > m    and Txn is not used    (n,m  : Transmit FIFO indexes)
         --> Txm can use the space allocated for Txn.
         case2  :  n < m    and Txn is not used    (n,m  : Transmit FIFO indexes)
         --> Txn should be configured with the minimum space of 16 words
     The FIFO is used optimally when used TxFIFOs are allocated in the top
         of the FIFO.Ex: use EP1 and EP2 as IN instead of EP1 and EP3 as IN ones.
     When DMA is used 3n * FIFO locations should be reserved for internal DMA registers */

  Tx_Offset = USB_HS->GRXFSIZ;

  if (fifo == 0U)
  {
    USB_HS->DIEPTXF0_HNPTXFSIZ = ((uint32_t)size << 16) | Tx_Offset;
  }
  else
  {
    Tx_Offset += (USB_HS->DIEPTXF0_HNPTXFSIZ) >> 16;
    for (i = 0U; i < (fifo - 1U); i++)
    {
      Tx_Offset += (USB_HS->DIEPTXF[i] >> 16);
    }

    /* Multiply Tx_Size by 2 to get higher performance */
    USB_HS->DIEPTXF[fifo - 1U] = ((uint32_t)size << 16) | Tx_Offset;
  }

}

/**
  * @brief  Set Rx FIFO
  * @param  size Size of Rx fifo
  * @retval none
  */
void PCDEx_HS_SetRxFiFo(uint16_t size)
{
  USB_HS->GRXFSIZ = size;

}
#endif /* defined (USB_OTG_HS) */

/**
  * @}
  */


#endif /* defined (USB_OTG_HS) */
#endif /* PCD_MODULE_ENABLED */

