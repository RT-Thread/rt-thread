/**
  ******************************************************************************
  * @brief   CRC header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F10X_CRC_H
#define __GD32F10X_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @addtogroup CRC
  * @{
  */

/** @defgroup CRC_Exported_Functions
  * @{
  */

void CRC_ResetDTR(void);
uint32_t CRC_CalcSingleData(uint32_t CRC_data);
uint32_t CRC_CalcDataFlow(uint32_t pbuffer[], uint32_t buffer_length);
uint32_t CRC_ReadDTR(void);
void CRC_WriteFDTR(uint8_t CRC_fdtr);
uint8_t CRC_ReadFDTR(void);

#ifdef __cplusplus
}
#endif

#endif /*__GD32F10X_CRC_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
