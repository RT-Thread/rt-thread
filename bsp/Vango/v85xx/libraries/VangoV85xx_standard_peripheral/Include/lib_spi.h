/**
  ******************************************************************************
  * @file    lib_spi.h 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
  * @brief   SPI library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_SPI_H
#define __LIB_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"
   
typedef struct
{
  uint32_t Mode;
  uint32_t SPH;
  uint32_t SPO;
  uint32_t ClockDivision;
  uint32_t CSNSoft;
  uint32_t SWAP;
} SPI_InitType;
//Mode
#define SPI_MODE_MASTER         0
#define SPI_MODE_SLAVE          SPI_CTRL_MOD
//SPH
#define SPI_SPH_0               0
#define SPI_SPH_1               SPI_CTRL_SCKPHA
//SPO
#define SPI_SPO_0               0
#define SPI_SPO_1               SPI_CTRL_SCKPOL
//ClockDivision
#define SPI_CLKDIV_2            (0)  
#define SPI_CLKDIV_4            (SPI_CTRL_SCKSEL_0)  
#define SPI_CLKDIV_8            (SPI_CTRL_SCKSEL_1)  
#define SPI_CLKDIV_16           (SPI_CTRL_SCKSEL_0 | SPI_CTRL_SCKSEL_1) 
#define SPI_CLKDIV_32           (SPI_CTRL_SCKSEL_2) 
#define SPI_CLKDIV_64           (SPI_CTRL_SCKSEL_0 | SPI_CTRL_SCKSEL_2) 
#define SPI_CLKDIV_128          (SPI_CTRL_SCKSEL_1 | SPI_CTRL_SCKSEL_2)
//CSNSoft
#define SPI_CSNSOFT_ENABLE      SPI_CTRL_CSGPIO
#define SPI_CSNSOFT_DISABLE     0
//SWAP
#define SPI_SWAP_ENABLE         SPI_CTRL_SWAP
#define SPI_SWAP_DISABLE        0  

//INT
#define SPI_INT_TX          (0x80000000|SPI_TXSTS_TXIEN)
#define SPI_INT_RX          (0x40000000|SPI_RXSTS_RXIEN)

//status
#define SPI_STS_TXIF     (0x80000000|SPI_TXSTS_TXIF)
#define SPI_STS_TXEMPTY  (0x80000000|SPI_TXSTS_TXEMPTY)
#define SPI_STS_TXFUR    (0x80000000|SPI_TXSTS_TXFUR)
#define SPI_STS_RXIF     (0x40000000|SPI_RXSTS_RXIF)
#define SPI_STS_RXFULL   (0x40000000|SPI_RXSTS_RXFULL)
#define SPI_STS_RXFOV    (0x40000000|SPI_RXSTS_RXFOV)
#define SPI_STS_BSY      (0x20000000|SPI_MISC_BSY)
#define SPI_STS_RFF      (0x20000000|SPI_MISC_RFF)
#define SPI_STS_RNE      (0x20000000|SPI_MISC_RNE)
#define SPI_STS_TNF      (0x20000000|SPI_MISC_TNF)
#define SPI_STS_TFE      (0x20000000|SPI_MISC_TFE)

//TXFLEV
#define SPI_TXFLEV_0       (0)
#define SPI_TXFLEV_1       (SPI_TXSTS_TXFLEV_0)
#define SPI_TXFLEV_2       (SPI_TXSTS_TXFLEV_1)
#define SPI_TXFLEV_3       (SPI_TXSTS_TXFLEV_0 | SPI_TXSTS_TXFLEV_1)
#define SPI_TXFLEV_4       (SPI_TXSTS_TXFLEV_2)
#define SPI_TXFLEV_5       (SPI_TXSTS_TXFLEV_0 | SPI_TXSTS_TXFLEV_2)
#define SPI_TXFLEV_6       (SPI_TXSTS_TXFLEV_1 | SPI_TXSTS_TXFLEV_2)
#define SPI_TXFLEV_7       (SPI_TXSTS_TXFLEV_0 | SPI_TXSTS_TXFLEV_1 | SPI_TXSTS_TXFLEV_2)

//RXFLEV
#define SPI_RXFLEV_0       (0)
#define SPI_RXFLEV_1       (SPI_RXSTS_RXFLEV_0)
#define SPI_RXFLEV_2       (SPI_RXSTS_RXFLEV_1)
#define SPI_RXFLEV_3       (SPI_RXSTS_RXFLEV_0 | SPI_RXSTS_RXFLEV_1)
#define SPI_RXFLEV_4       (SPI_RXSTS_RXFLEV_2)
#define SPI_RXFLEV_5       (SPI_RXSTS_RXFLEV_2 | SPI_RXSTS_RXFLEV_0)
#define SPI_RXFLEV_6       (SPI_RXSTS_RXFLEV_2 | SPI_RXSTS_RXFLEV_1)
#define SPI_RXFLEV_7       (SPI_RXSTS_RXFLEV_2 | SPI_RXSTS_RXFLEV_1 | SPI_RXSTS_RXFLEV_0)

                   
/* Private macros ------------------------------------------------------------*/
#define IS_SPI_MODE(__MODE__)  (((__MODE__) == SPI_MODE_MASTER) || ((__MODE__) == SPI_MODE_SLAVE))

#define IS_SPI_SPH(__SPH__)  (((__SPH__) == SPI_SPH_0) || ((__SPH__) == SPI_SPH_1))

#define IS_SPI_SPO(__SPO__)  (((__SPO__) == SPI_SPO_0) || ((__SPO__) == SPI_SPO_1)) 

#define IS_SPI_CLKDIV(__CLKDIV__)  (((__CLKDIV__) == SPI_CLKDIV_2) ||\
                                    ((__CLKDIV__) == SPI_CLKDIV_4) ||\
                                    ((__CLKDIV__) == SPI_CLKDIV_8) ||\
                                    ((__CLKDIV__) == SPI_CLKDIV_16) ||\
                                    ((__CLKDIV__) == SPI_CLKDIV_32) ||\
                                    ((__CLKDIV__) == SPI_CLKDIV_64) ||\
                                    ((__CLKDIV__) == SPI_CLKDIV_128))

#define IS_SPI_CSN(__CSN__)  (((__CSN__) == SPI_CSNSOFT_ENABLE) || ((__CSN__) == SPI_CSNSOFT_DISABLE))

#define IS_SPI_SWAP(__SWAP__)  (((__SWAP__) == SPI_SWAP_ENABLE) || ((__SWAP__) == SPI_SWAP_DISABLE))

#define IS_SPI_INT(__INT__)  ((((__INT__) & (SPI_INT_TX | SPI_INT_RX)) != 0U) &&\
                              (((__INT__) & ~(SPI_INT_TX | SPI_INT_RX)) == 0U))

#define IS_SPI_STSR(__STSR__)  (((__STSR__) == SPI_STS_TXIF)    ||\
                                ((__STSR__) == SPI_STS_TXEMPTY) ||\
                                ((__STSR__) == SPI_STS_TXFUR)   ||\
                                ((__STSR__) == SPI_STS_RXFULL)  ||\
                                ((__STSR__) == SPI_STS_RXFOV)   ||\
                                ((__STSR__) == SPI_STS_BSY)     ||\
                                ((__STSR__) == SPI_STS_RFF)     ||\
                                ((__STSR__) == SPI_STS_RNE)     ||\
                                ((__STSR__) == SPI_STS_TNF)     ||\
                                ((__STSR__) == SPI_STS_TFE)     ||\
                                ((__STSR__) == SPI_STS_RXIF))

#define IS_SPI_STSC(__STSC__)  ((((__STSC__) & (SPI_STS_TXIF | SPI_STS_RXIF)) != 0U) &&\
                                (((__STSC__) & ~(SPI_STS_TXIF | SPI_STS_RXIF)) == 0U))

#define IS_SPI_TXFLEV(__TXFLEV__)  (((__TXFLEV__) == SPI_TXFLEV_0) ||\
                                    ((__TXFLEV__) == SPI_TXFLEV_1) ||\
                                    ((__TXFLEV__) == SPI_TXFLEV_2) ||\
                                    ((__TXFLEV__) == SPI_TXFLEV_3) ||\
                                    ((__TXFLEV__) == SPI_TXFLEV_4) ||\
                                    ((__TXFLEV__) == SPI_TXFLEV_5) ||\
                                    ((__TXFLEV__) == SPI_TXFLEV_6) ||\
                                    ((__TXFLEV__) == SPI_TXFLEV_7))

#define IS_SPI_RXFLEV(__RXFLEV__)  (((__RXFLEV__) == SPI_RXFLEV_0) ||\
                                    ((__RXFLEV__) == SPI_RXFLEV_1) ||\
                                    ((__RXFLEV__) == SPI_RXFLEV_2) ||\
                                    ((__RXFLEV__) == SPI_RXFLEV_3) ||\
                                    ((__RXFLEV__) == SPI_RXFLEV_4) ||\
                                    ((__RXFLEV__) == SPI_RXFLEV_5) ||\
                                    ((__RXFLEV__) == SPI_RXFLEV_6) ||\
                                    ((__RXFLEV__) == SPI_RXFLEV_7))

/* Exported Functions ------------------------------------------------------- */
/* SPI Exported Functions Group1: 
                                  (De)Initialization -------------------------*/
void SPI_DeviceInit(SPI_TypeDef *SPIx);
void SPI_Init(SPI_TypeDef *SPIx, SPI_InitType *InitStruct);
void SPI_StructInit(SPI_InitType *InitStruct);
/* SPI Exported Functions Group2: 
                                  Interrupt (flag) ---------------------------*/
void SPI_INTConfig(SPI_TypeDef *SPIx, uint32_t INTMask, uint32_t NewState);
uint8_t SPI_GetStatus(SPI_TypeDef *SPIx, uint32_t Status);
void SPI_ClearStatus(SPI_TypeDef *SPIx, uint32_t Status);
/* SPI Exported Functions Group3: 
                                  Transfer datas -----------------------------*/
void SPI_SendData(SPI_TypeDef *SPIx, uint8_t ch);
uint8_t SPI_ReceiveData(SPI_TypeDef *SPIx);
/* SPI Exported Functions Group4: 
                                  MISC Configuration -------------------------*/
void SPI_Cmd(SPI_TypeDef *SPIx, uint32_t NewState);
void SPI_TransmitFIFOLevelConfig(SPI_TypeDef *SPIx, uint32_t FIFOLevel);
void SPI_ReceiveFIFOLevelConfig(SPI_TypeDef *SPIx, uint32_t FIFOLevel);
uint8_t SPI_GetTransmitFIFOLevel(SPI_TypeDef *SPIx);
uint8_t SPI_GetReceiveFIFOLevel(SPI_TypeDef *SPIx);
void SPI_SmartModeCmd(SPI_TypeDef *SPIx, uint32_t NewState);
void SPI_OverWriteModeCmd(SPI_TypeDef *SPIx, uint32_t NewState);


#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_SPI_H */

/*********************************** END OF FILE ******************************/
