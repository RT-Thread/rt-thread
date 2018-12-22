/******************************************************************************
* @brief    Cyclic redundancy check (CRC) source code. 
*
******************************************************************************/
#include "common.h"
#include "crc.h"

/******************************************************************************
* Global variables
******************************************************************************/

/******************************************************************************
* Constants and macros
******************************************************************************/

/******************************************************************************
* Local types
******************************************************************************/

/******************************************************************************
* Local function prototypes
******************************************************************************/

/******************************************************************************
* Local variables
******************************************************************************/

/******************************************************************************
* Local functions
******************************************************************************/

/******************************************************************************
* Global functions
******************************************************************************/

/******************************************************************************
* define CRC APIs
*
*//*! @addtogroup crc_api_list
* @{
*******************************************************************************/

/*****************************************************************************//*!
*
* @brief initialize CRC with poly per control parameters
*        
* @param[in]  pConfig point to configuration. 
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
void CRC_Init(CRC_ConfigType *pConfig)
{       
    uint32_t     u32Sc ;
    
    u32Sc      = 0;
    
    SIM->SCGC |= SIM_SCGC_CRC_MASK;  
    
    u32Sc     |= ((pConfig->bWidth & 0x01)<<24);    
    u32Sc     |= CRC_CTRL_TOTR(pConfig->bTransposeReadType & 0x03); 
    u32Sc     |= CRC_CTRL_TOT(pConfig->bTransposeWriteType & 0x03);
    
    if (pConfig->bFinalXOR)
    {
        u32Sc |= CRC_CTRL_FXOR_MASK;        
    }
    
    CRC0->CTRL  = u32Sc;

    if ( pConfig->bWidth )      
    {
        CRC0->GPOLY = pConfig->u32PolyData;
    }
    else 
    {
        CRC0->GPOLY_ACCESS16BIT.GPOLYL = pConfig->u32PolyData;  /*!< only 16-bit write allowed */             
    }  
    
}     


/*****************************************************************************//*!
*
* @brief crc module 16-bit mode calculation.
*        
* @param[in]  seed  
* @param[in]  msg  poiont to message buffer
* @param[in]  sizeBytes  size of message
*
* @return data_out convertion result
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
uint32_t CRC_Cal16(uint32_t seed, uint8_t *msg, uint32_t sizeBytes)
{
  uint32_t ctrl_reg,data_out,data_in;
  uint8_t  *pCRCBytes;
  uint32_t sizeWords;
  uint32_t i,j;  
  
  /* Input seed, Set WaS=1 */
  ctrl_reg  = CRC0->CTRL;
  CRC0->CTRL  = ctrl_reg | CRC_CTRL_WAS_MASK;
  CRC0->ACCESS16BIT.DATAL = seed;
  
  /*Input data, Set WaS=0*/
  CRC0->CTRL  = ctrl_reg & 0xFD000000;

  /*Wait for calculation completion*/
  sizeWords = sizeBytes>>1;
  j = 0;
  for(i=0;i<sizeWords;i++){ 
      data_in = (msg[j] << 8) | (msg[j+1]);
      j += 2;
      CRC0->ACCESS16BIT.DATAL =data_in; 
  }
  if (j<sizeBytes)
  { 
     pCRCBytes = (uint8_t*)&CRC0->ACCESS8BIT.DATALL;
     *pCRCBytes++ = msg[j];
  }
    data_out=CRC0->ACCESS16BIT.DATAL;
  
  return(data_out);
}


/*****************************************************************************//*!
*
* @brief crc module 32-bit mode calculation.
*        
* @param[in]  seed 
* @param[in]  msg  poiont to message buffer
* @param[in]  sizeBytes  size of message
*
* @return data_out convertion result 
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
uint32_t CRC_Cal32(uint32_t seed, uint8_t *msg, uint32_t sizeBytes)
{  
  uint32_t ctrl_reg,data_out,data_in;
  uint32_t sizeDwords;
  uint8_t  *pCRCBytes;
  uint32_t i,j;
  
  /*Input seed, Set WaS=1*/
  ctrl_reg = CRC0->CTRL;
  CRC0->CTRL = ctrl_reg | 0x02000000;
  CRC0->DATA = seed;
 
  /*Input data, Set WaS=0*/
  CRC0->CTRL = ctrl_reg & 0xFD000000;
  
  /*Wait for calculation completion*/
  sizeDwords = sizeBytes>>2;
  j = 0;
  for(i=0;i<sizeDwords;i++)
  { 
      data_in = ((msg[j] << 24) | (msg[j+1] << 16) | (msg[j+2] << 8) | msg[j+3]);
      j += 4;
      CRC0->DATA = data_in; 
  }
  if (j<sizeBytes)
  {
    pCRCBytes = (uint8_t*)&CRC0->ACCESS8BIT.DATALL;

#if  defined(BYTE_ENABLES_1_2_4_8)    
    
    /*write single byte*/  
    for(;j<sizeBytes;j++)
    {     
       *pCRCBytes++ = msg[j];
    }
#elif  defined(BYTE_ENABLES_3_6_C)
    
    /*write two bytes*/ 
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
       CRC0->ACCESS8BIT.DATALL = data_in;                /*!< write last byte */
    }
#elif  defined(BYTE_ENABLES_7_E)                         
    /*!< write three bytes */
    data_in = 0;
    i = 0;
    for(;j<sizeBytes;j++)
    {     
      data_in = (data_in <<8) | msg[j];
      i++;
      if (i==3)
      {
        i = 0;
        /*write first  char*/
        CRC0->ACCESS8BIT.DATAHL  = (data_in>>16) & 0xff; /*!< write low byte of high word */
        /*write last two chars*/
        CRC0->ACCESS16BIT.DATAL = data_in & 0x00ffff;    /*!< write low word */
       }
    }
    if ( i == 2)
    {
       CRC0->ACCESS16BIT.DATAL = (data_in);              /*!< write last 2 bytes */
    }
    else if (i == 1)
    {
       CRC0->ACCESS8BIT.DATALL = data_in;                /*!< write last byte */      
    }
#else                                                    /*!< write low byte only */
    for(;j<sizeBytes;j++)
    {     
       *pCRCBytes = msg[j];
    }
#endif            
  }
  data_out=CRC0->DATA;

  return(data_out);
}


/*****************************************************************************//*!
*
* @brief de-initialize crc module, reset crc register.
*        
* @param none 
*
* @return none 
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
void CRC_DeInit(void)
{  
   CRC0->CTRL  = 0x3000000; /*!< prepare for write 32-bit seed*/ 
   CRC0->DATA  = 0xFFFFFFFF;/*!< write 32-bit seed to data register*/ 
   while(!(CRC0->DATA == 0xFFFFFFFF));
   CRC0->GPOLY = 0x00001021; 
   CRC0->CTRL  = 0;         /*!< reset ctrl register*/  
   SIM->SCGC &= ~SIM_SCGC_CRC_MASK;
}

/*! @} End of crc_api_list                                                   */


