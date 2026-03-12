
/**
 * @file n32h76x_78x_cfg.h
 * @author N32cube
 */
#ifndef __N32H76X_78X_CFG_H__
#define __N32H76X_78X_CFG_H__

#ifdef __cplusplus
extern "C" {
#endif
/* NTFx CODE START INCLUDE*/
#include "n32h76x_78x.h"
#include "n32h76x_78x_rcc.h"
#include "misc.h"
#include "n32h76x_78x_dma.h"
#include "n32h76x_78x_gpio.h"
#include "n32h76x_78x_usart.h"
#include "n32h76x_78x_pwr.h"
#include "n32h76x_78x_dmamux.h"
#include "n32h76x_78x_mdma.h"
/* NTFx CODE END INCLUDE*/
/* NTFx CODE START Extern*/
extern void SysTick_Delayms(uint32_t Delayms);
extern void DMA_SetPerMemAddr(DMA_ChannelType* DMAChx, uint32_t periphAddr,uint32_t memAddr,uint32_t bufSize );
extern bool RCC_Configuration(void);
extern bool NVIC_Configuration(void);
extern bool DMA_Configuration(void);
extern bool GPIO_Configuration(void);
extern bool USART_Configuration(void);
/* NTFx CODE END Extern*/

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */
/**
 * @}
 */
