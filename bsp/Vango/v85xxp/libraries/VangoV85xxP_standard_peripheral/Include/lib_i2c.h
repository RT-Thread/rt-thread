/**
  ******************************************************************************
  * @file    lib_i2c.h 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
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

/**************  Bits definition for I2C_CTRL register       ******************/
#define I2C_CTRL_CR_0                 (0x0U << I2C_CTRL_CR0_Pos)                /*!< 0x0000000 */
#define I2C_CTRL_CR_1                 (0x1U << I2C_CTRL_CR0_Pos)                /*!< 0x0000001 */
#define I2C_CTRL_CR_2                 (0x2U << I2C_CTRL_CR0_Pos)                /*!< 0x0000002 */
#define I2C_CTRL_CR_3                 (0x3U << I2C_CTRL_CR0_Pos)                /*!< 0x0000003 */
#define I2C_CTRL_CR_4                 (0x80U << I2C_CTRL_CR0_Pos)               /*!< 0x0000080 */
#define I2C_CTRL_CR_5                 (0x81U << I2C_CTRL_CR0_Pos)               /*!< 0x0000081 */
#define I2C_CTRL_CR_6                 (0x82U << I2C_CTRL_CR0_Pos)               /*!< 0x0000082 */
#define I2C_CTRL_CR_7                 (0x83U << I2C_CTRL_CR0_Pos)               /*!< 0x0000083 */
                                  
/**************  Bits definition for I2C_STS register        ******************/
#define I2C_STS_STS_0x00              (0x0U << I2C_STS_STS_Pos)                /*!< 0x0000000 */
#define I2C_STS_STS_0x08              (0x1U << I2C_STS_STS_Pos)                /*!< 0x0000008 */
#define I2C_STS_STS_0x10              (0x2U << I2C_STS_STS_Pos)                /*!< 0x0000010 */
#define I2C_STS_STS_0x18              (0x3U << I2C_STS_STS_Pos)                /*!< 0x0000018 */
#define I2C_STS_STS_0x20              (0x4U << I2C_STS_STS_Pos)                /*!< 0x0000020 */
#define I2C_STS_STS_0x28              (0x5U << I2C_STS_STS_Pos)                /*!< 0x0000028 */
#define I2C_STS_STS_0x30              (0x6U << I2C_STS_STS_Pos)                /*!< 0x0000030 */
#define I2C_STS_STS_0x38              (0x7U << I2C_STS_STS_Pos)                /*!< 0x0000038 */
#define I2C_STS_STS_0x40              (0x8U << I2C_STS_STS_Pos)                /*!< 0x0000040 */
#define I2C_STS_STS_0x48              (0x9U << I2C_STS_STS_Pos)                /*!< 0x0000048 */
#define I2C_STS_STS_0x50              (0xAU << I2C_STS_STS_Pos)                /*!< 0x0000050 */
#define I2C_STS_STS_0x58              (0xBU << I2C_STS_STS_Pos)                /*!< 0x0000058 */
#define I2C_STS_STS_0x60              (0xCU << I2C_STS_STS_Pos)                /*!< 0x0000060 */
#define I2C_STS_STS_0x68              (0xDU << I2C_STS_STS_Pos)                /*!< 0x0000068 */
#define I2C_STS_STS_0x70              (0xEU << I2C_STS_STS_Pos)                /*!< 0x0000070 */
#define I2C_STS_STS_0x78              (0xFU << I2C_STS_STS_Pos)                /*!< 0x0000078 */
#define I2C_STS_STS_0x80              (0x10U << I2C_STS_STS_Pos)               /*!< 0x0000080 */
#define I2C_STS_STS_0x88              (0x11U << I2C_STS_STS_Pos)               /*!< 0x0000088 */
#define I2C_STS_STS_0x90              (0x12U << I2C_STS_STS_Pos)               /*!< 0x0000090 */
#define I2C_STS_STS_0x98              (0x13U << I2C_STS_STS_Pos)               /*!< 0x0000098 */
#define I2C_STS_STS_0xA0              (0x14U << I2C_STS_STS_Pos)               /*!< 0x00000A0 */
#define I2C_STS_STS_0xA8              (0x15U << I2C_STS_STS_Pos)               /*!< 0x00000A8 */
#define I2C_STS_STS_0xB0              (0x16U << I2C_STS_STS_Pos)               /*!< 0x00000B0 */
#define I2C_STS_STS_0xB8              (0x17U << I2C_STS_STS_Pos)               /*!< 0x00000B8 */
#define I2C_STS_STS_0xC0              (0x18U << I2C_STS_STS_Pos)               /*!< 0x00000C0 */
#define I2C_STS_STS_0xC8              (0x19U << I2C_STS_STS_Pos)               /*!< 0x00000C8 */
#define I2C_STS_STS_0xF8              (0x1FU << I2C_STS_STS_Pos)               /*!< 0x00000F8 */

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

#define I2C_CTRL_CR   (0x83)
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
#define I2C_SUBADDR_1BYTE   (1)
#define I2C_SUBADDR_2BYTE   (2)
#define I2C_SUBADDR_OTHER   (3)

//remap
#define I2C_REMAP_ENABLE    (1)
#define I2C_REMAP_DISABLE   (0)

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

/****************************** I2C Instances *********************************/
#define IS_I2C_ALL_INSTANCE(INSTANCE) ((INSTANCE) == I2C)


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
