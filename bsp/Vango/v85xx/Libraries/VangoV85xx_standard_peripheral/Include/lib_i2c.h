/**
  ******************************************************************************
  * @file    lib_i2c.h 
  * @author  Application Team
  * @version V4.5.0
  * @date    2019-05-14
  * @brief   IIC library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_I2C_H
#define __LIB_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"
   
typedef struct
{
  uint32_t SlaveAddr;
  uint32_t GeneralCallAck;
  uint32_t AssertAcknowledge;
  uint32_t ClockSource;
} I2C_InitType;
//GeneralCallAck
#define I2C_GENERALCALLACK_ENABLE   I2C_ADDR_GC
#define I2C_GENERALCALLACK_DISABLE  0
//AssertAcknowledge
#define I2C_ASSERTACKNOWLEDGE_ENABLE    I2C_CTRL_AA
#define I2C_ASSERTACKNOWLEDGE_DISABLE   0
//ClockSource
#define I2C_CLOCKSOURCE_APBD256     I2C_CTRL_CR_0
#define I2C_CLOCKSOURCE_APBD224     I2C_CTRL_CR_1
#define I2C_CLOCKSOURCE_APBD192     I2C_CTRL_CR_2
#define I2C_CLOCKSOURCE_APBD160     I2C_CTRL_CR_3
#define I2C_CLOCKSOURCE_APBD960     I2C_CTRL_CR_4
#define I2C_CLOCKSOURCE_APBD120     I2C_CTRL_CR_5
#define I2C_CLOCKSOURCE_APBD60      I2C_CTRL_CR_6
#define I2C_CLOCKSOURCE_TIM3OFD8    I2C_CTRL_CR_7

typedef struct
{
  uint16_t SlaveAddr;
  uint8_t SubAddrType;
  uint32_t PageRange;
  uint32_t SubAddress;
  uint8_t *pBuffer;
  uint32_t Length;
} I2C_WRType;
//SubAddrType
#define I2C_SUBADDR_1BYTE   1
#define I2C_SUBADDR_2BYTE   2
#define I2C_SUBADDR_OTHER   3

//remap
#define I2C_REMAP_ENABLE    1
#define I2C_REMAP_DISABLE   0

/* Private macros ------------------------------------------------------------*/

#define IS_I2C_GC(__GC__)  (((__GC__) == I2C_GENERALCALLACK_ENABLE) ||\
                            ((__GC__) == I2C_GENERALCALLACK_DISABLE))

#define IS_I2C_AA(__AA__)  (((__AA__) == I2C_ASSERTACKNOWLEDGE_ENABLE) ||\
                            ((__AA__) == I2C_ASSERTACKNOWLEDGE_DISABLE))

#define IS_I2C_CLKSRC(__CLKSRC__)  (((__CLKSRC__) == I2C_CLOCKSOURCE_APBD256) ||\
                                    ((__CLKSRC__) == I2C_CLOCKSOURCE_APBD224) ||\
                                    ((__CLKSRC__) == I2C_CLOCKSOURCE_APBD192) ||\
                                    ((__CLKSRC__) == I2C_CLOCKSOURCE_APBD160) ||\
                                    ((__CLKSRC__) == I2C_CLOCKSOURCE_APBD960) ||\
                                    ((__CLKSRC__) == I2C_CLOCKSOURCE_APBD120) ||\
                                    ((__CLKSRC__) == I2C_CLOCKSOURCE_APBD60)  ||\
                                    ((__CLKSRC__) == I2C_CLOCKSOURCE_TIM3OFD8))

#define I2C_SUBADDR_TYPE(__TYPE__)  (((__TYPE__) == I2C_SUBADDR_1BYTE) ||\
                                     ((__TYPE__) == I2C_SUBADDR_2BYTE) ||\
                                     ((__TYPE__) == I2C_SUBADDR_OTHER))

/* Exported Functions ------------------------------------------------------- */
/* I2C Exported Functions Group1: 
                                   (De)Initialization ------------------------*/
void I2C_DeInit(uint32_t remap);
void I2C_StructInit(I2C_InitType *InitStruct);
void I2C_Init(I2C_InitType *InitStruct);
/* I2C Exported Functions Group2: 
                                   Interrupt ---------------------------------*/
void I2C_INTConfig(uint32_t NewState);
uint8_t I2C_GetINTStatus(void);
void I2C_ClearINTStatus(void);
/* I2C Exported Functions Group3: 
                                   Transfer datas ----------------------------*/
uint16_t I2C_MasterReadBytes(I2C_WRType *InitStruct);
uint16_t I2C_MasterWriteBytes(I2C_WRType *InitStruct);
/* I2C Exported Functions Group4: 
                                   MISC Configuration ------------------------*/
void I2C_Cmd(uint32_t NewState);

/* I2C Exported Functions Group5: 
                                   Others ------------------------------------*/
void I2C_AssertAcknowledgeConfig(uint32_t NewState);
uint8_t I2C_ReceiveData(void);
void I2C_SendData(uint8_t Dat);
void I2C_GenerateSTART(uint32_t NewState);
void I2C_GenerateSTOP(uint32_t NewState);
uint8_t I2C_GetStatusCode(void);


#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_I2C_H */

/*********************************** END OF FILE ******************************/
