/**
 * @file n32h49x_cfg.h
 * @author N32cube
 */
#ifndef __N32H49X_CFG_H__
#define __N32H49X_CFG_H__

#ifdef __cplusplus
extern "C" {
#endif
/* NTFx CODE START INCLUDE*/
#include "n32h49x.h"
#include "n32h49x_dbg.h"
#include "n32h49x_vrefbuf.h"
#include "n32h49x_flash.h"
#include "n32h49x_rcc.h"
#include "misc.h"
#include "n32h49x_dma.h"
#include "n32h49x_gpio.h"
#include "n32h49x_usart.h"
/* NTFx CODE END INCLUDE*/

/* NTFx CODE START Extern*/
extern void SysTick_Delayms(uint32_t Delayms);
extern void DMA_SetPerMemAddr(DMA_ChannelType* DMAChx, uint32_t periphAddr, uint32_t memAddr, uint32_t bufSize);
extern bool RCC_Configuration(void);
extern bool GPIO_Configuration(void);
extern bool NVIC_Configuration(void);
extern bool DMA_Configuration(void);
extern bool USART_Configuration(void);
/* NTFx CODE END Extern*/

#ifdef __cplusplus
}
#endif

#endif /* __N32H49X_CFG_H__ */
/**
 * @}
 */
