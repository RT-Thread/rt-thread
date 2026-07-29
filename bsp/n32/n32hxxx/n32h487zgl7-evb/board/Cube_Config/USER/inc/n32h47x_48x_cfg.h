/**
 * @file n32h47x_48x_cfg.h
 * @author N32cube
 */
#ifndef __N32H47X_48X_CFG_H__
#define __N32H47X_48X_CFG_H__

#ifdef __cplusplus
extern "C" {
#endif
/* NTFx CODE START INCLUDE*/
#include "n32h47x_48x.h"
#include "n32h47x_48x_conf.h"
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

#endif /* __N32H47X_48X_CFG_H__ */
/**
 * @}
 */
