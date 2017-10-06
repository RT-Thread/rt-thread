/******************************************************************************
*
* @brief    Cyclic redundancy check (CRC) header file. 
*
******************************************************************************/
#ifndef CRC_H_
#define CRC_H_
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
* Includes
******************************************************************************/

/******************************************************************************
* Constants
******************************************************************************/

/******************************************************************************
* Macros
******************************************************************************/


/******************************************************************************
* CRC control bit definition
*
*//*! @addtogroup crc_controlbit
* @{
*******************************************************************************/

/*!
 * @brief CRC control register bit definition.
 *
 */

#define CRC_WIDTH_16BIT                 0	/*!< select CRC16 protocol */   
#define CRC_WIDTH_32BIT                 1	/*!< select CRC32 protocol */ 
#define CRC_DATA_SEED                   1	/*!< Write CRC Data Register are seed */  
#define CRC_DATA_DATA                   0	/*!< Write CRC Data Register are data */ 
#define CRC_READ_COMPLETE               1	/*!< Invert or complement read CRC Data register */ 
#define CRC_READ_NONE                   0	/*!< No XOR on reading */ 
#define CRC_READ_TRANSPOSE_NONE         0	/*!< No transposition in read */ 
#define CRC_READ_TRANSPOSE_BIT          1	/*!< only bits in bytes are transposed in read */
#define CRC_READ_TRANSPOSE_ALL          2	/*!< both bits in bytes and bytes are transposed in read */
#define CRC_READ_TRANSPOSE_BYTE         3	/*!< only bytes are transposed in read */
#define CRC_WRITE_TRANSPOSE_NONE        0	/*!< No transposition write */
#define CRC_WRITE_TRANSPOSE_BIT         1	/*!< only bits in bytes are transposed in write */ 
#define CRC_WRITE_TRANSPOSE_ALL         2	/*!< both bits in bytes and bytes are transposed in write */
#define CRC_WRITE_TRANSPOSE_BYTE        3	/*!< only bytes are transposed in write */

/*! @} End of crc_controlbit                                                */

     
/******************************************************************************
* Types
******************************************************************************/
/* CRC configuration structure 
 */  
/******************************************************************************
* CRC Configuration Structure type.
*
*//*! @addtogroup crc_config_type
* @{
*******************************************************************************/ 
/*!
 * @brief CRC Configuration Structure.
 *
 */

typedef struct
{          
    uint8_t bWidth                  : 1;    /*!< 1: 32-bit CRC protocol , 0: 16-bit CRC protocol */
    uint8_t bDataType               : 1;    /*!< 1: write seed , 0: write data */
    uint8_t bFinalXOR               : 1;    /*!< 1: Invert or complement read , 0: No XOR on reading */
    uint8_t bRESERVED               : 1;    /*!< reserved bit */  
    uint8_t bTransposeReadType      : 2;    /*!< type of transpose For read, see reference manual */
    uint8_t bTransposeWriteType     : 2;    /*!< type of transpose For write, see reference manual */      
    uint32_t u32PolyData               ;    /*!< 32bit or 16-biy poly data */           
} CRC_ConfigType, *CRC_ConfigPtr  ; 
/*! @} End of crc_config_type                                                */

           
/******************************************************************************
* Global variables
******************************************************************************/

/******************************************************************************
* CRC API list
*
*//*! @addtogroup crc_api_list
* @{
*******************************************************************************/

/******************************************************************************
* Global functions
******************************************************************************/
void        CRC_Init(CRC_ConfigType *pConfig);
uint32_t    CRC_Cal16(uint32_t u32Seed, uint8_t *msg, uint32_t u32SizeBytes);
uint32_t    CRC_Cal32(uint32_t u32Seed, uint8_t *msg, uint32_t u32SizeBytes);
void        CRC_DeInit(void);
/*! @} End of crc_api_list                                                   */

#ifdef __cplusplus
}
#endif
#endif /* CRC_H_ */



