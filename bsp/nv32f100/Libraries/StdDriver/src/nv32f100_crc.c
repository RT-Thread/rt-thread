/**************************************************************************!     
 *     技术讨论：QQ群  123763203
 *     官网    ：www.navota.com
 *
 * @file       crc.c
 * @brief      冗余校验模块（CRC)函数库
 * @author     Navota
 * @date       2017-1-1
 ****************************************************************************/
#include "nv32f100.h"

/*****************************************************************************//*!
*
* @brief 初始化CRC
*        
* @param[in]  pConfig 指向CRC配置结构体. 
*
* @return none
*
*****************************************************************************/
void CRC_Init(CRC_ConfigType *pConfig)
{       
    uint32_t     u32Sc ;
    
    u32Sc      = 0;
    
    SIM->SCGC |= SIM_SCGC_CRC_MASK;   //使能CRC控制模块时钟
    
    u32Sc     |= ((pConfig->bWidth & 0x01)<<24);   //CRC模式选择
    u32Sc     |= CRC_CTRL_TOTR(pConfig->bTransposeReadType & 0x03);  //设置数据读取的转置类型
    u32Sc     |= CRC_CTRL_TOT(pConfig->bTransposeWriteType & 0x03);  //设置数据写入的转置类型
    
    if (pConfig->bFinalXOR)  
    {
        u32Sc |= CRC_CTRL_FXOR_MASK;  //对CRC数据寄存的读取值进行异或操作     
    }
    
    CRC0->CTRL  = u32Sc;

    if ( pConfig->bWidth )      
    {
        CRC0->GPOLY = pConfig->u32PolyData;  //写入32位多项式
    }
    else 
    {
        CRC0->GPOLY_ACCESS16BIT.GPOLYL = pConfig->u32PolyData;  /*!< 仅允许写16位多项式*/             
    }  
    
}     


/*****************************************************************************//*!
*
* @brief 16位模式下CRC计算函数.
*          
* @param[in]  seed  种子值
* @param[in]  msg   指向数据数组
* @param[in]  sizeBytes  数据大小
*
* @return data_out convertion result
*
*****************************************************************************/
uint32_t CRC_Cal16(uint32_t seed, uint8_t *msg, uint32_t sizeBytes)
{
  uint32_t ctrl_reg,data_out,data_in;
  uint8_t  *pCRCBytes;
  uint32_t sizeWords;
  uint32_t i,j;  
  
  /* 设置WaS=1，写入种子值 */
  ctrl_reg  = CRC0->CTRL;
  CRC0->CTRL  = ctrl_reg | CRC_CTRL_WAS_MASK;
  CRC0->ACCESS16BIT.DATAL = seed; 
  
  /* Set WaS=0，准备写入数据*/
  CRC0->CTRL  = ctrl_reg & 0xFD000000; 

  /*等待计算完成*/
  sizeWords = sizeBytes>>1;
  j = 0;
  for(i=0;i<sizeWords;i++){ 
      data_in = (msg[j] << 8) | (msg[j+1]);  /*将数据写入CRC数据寄存器，以16位方式写入*/
      j += 2;
      CRC0->ACCESS16BIT.DATAL =data_in; 
  }
  if (j<sizeBytes)
  { 
     pCRCBytes = (uint8_t*)&CRC0->ACCESS8BIT.DATALL; /*以8位的方式写入剩余的数据*/
     *pCRCBytes++ = msg[j];
  }
    data_out=CRC0->ACCESS16BIT.DATAL;  //读出16位计算结果
  
  return(data_out);
}


/*****************************************************************************//*!
*
* @brief  32位模式下CRC计算.
*        
* @param[in]  seed 
* @param[in]  msg  指向数据数组
* @param[in]  sizeBytes  数据大小
*
* @return data_out convertion result 
*
*****************************************************************************/
uint32_t CRC_Cal32(uint32_t seed, uint8_t *msg, uint32_t sizeBytes)
{  
  uint32_t ctrl_reg,data_out,data_in;
  uint32_t sizeDwords;
  uint8_t  *pCRCBytes;
  uint32_t i,j;
  
 /* 设置WaS=1，写入种子值 */
  ctrl_reg = CRC0->CTRL;
  CRC0->CTRL = ctrl_reg | 0x02000000;
  CRC0->DATA = seed;
 
 /* Set WaS=0，准备写入数据*/
  CRC0->CTRL = ctrl_reg & 0xFD000000;
  
  /*等待数据计算完成*/
  sizeDwords = sizeBytes>>2;
  j = 0;
  for(i=0;i<sizeDwords;i++)
  { 
      data_in = ((msg[j] << 24) | (msg[j+1] << 16) | (msg[j+2] << 8) | msg[j+3]); /*将数据写入CRC数据寄存器，以32方式写入*/
      j += 4;
      CRC0->DATA = data_in; 
  }
  if (j<sizeBytes)
  {
    pCRCBytes = (uint8_t*)&CRC0->ACCESS8BIT.DATALL;    /*以8位的方式写入剩余的数据*/

#if  defined(BYTE_ENABLES_1_2_4_8)    
    
    /*只写单个字节*/  
    for(;j<sizeBytes;j++)
    {     
       *pCRCBytes++ = msg[j];
    }
#elif  defined(BYTE_ENABLES_3_6_C)
    
    /*写入两个字节*/ 
    data_in = 0;
    i = 0;
    for(;j<sizeBytes;j++)
    {     
      data_in = (data_in <<8) | msg[j];
      i++;
      if (i==2)
      {
        i = 0;
        CRC0->ACCESS16BIT.DATAL = data_in;
      }
    }
    if (i==1)
    {
       CRC0->ACCESS8BIT.DATALL = data_in;                /*!< 写入最后一个字节 */
    }
#elif  defined(BYTE_ENABLES_7_E)                         
    /*!< 写入三个字节*/
    data_in = 0;
    i = 0;
    for(;j<sizeBytes;j++)
    {     
      data_in = (data_in <<8) | msg[j];
      i++;
      if (i==3)
      {
        i = 0;
        /*写入第一个字符*/
        CRC0->ACCESS8BIT.DATAHL  = (data_in>>16) & 0xff; /*!< 写入高字的低字节 */
        /*写入最后两个字节*/
        CRC0->ACCESS16BIT.DATAL = data_in & 0x00ffff;    /*!< 写入低字 */
       }
    }
    if ( i == 2)
    {
       CRC0->ACCESS16BIT.DATAL = (data_in);              /*!< 写最后两个字节 */
    }
    else if (i == 1)
    {
       CRC0->ACCESS8BIT.DATALL = data_in;                /*!< 写最后一个字节 */      
    }
#else                                                    /*!< 只写低字节 */
    for(;j<sizeBytes;j++)
    {     
       *pCRCBytes = msg[j];
    }
#endif            
  }
  data_out=CRC0->DATA;    

  return(data_out);   //读出32位计算结果
}


/*****************************************************************************//*!
*
* @brief 复位CRC模块
*        
* @param none 
*
* @return none 
*
*****************************************************************************/
void CRC_DeInit(void)
{  
   CRC0->CTRL  = 0x3000000; /*!<设置CRC位32位模式*/ 
   CRC0->DATA  = 0xFFFFFFFF;/*!< 写32位种子值到CRC数据寄存器*/ 
   while(!(CRC0->DATA == 0xFFFFFFFF));
   CRC0->GPOLY = 0x00001021; 
   CRC0->CTRL  = 0;         /*!<CRC控制寄存器清零*/  
   SIM->SCGC &= ~SIM_SCGC_CRC_MASK;
}



