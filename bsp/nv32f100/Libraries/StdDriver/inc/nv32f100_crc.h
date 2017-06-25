/******************************************************************************
*
* @brief  CRC 驱动头文件.  
*
******************************************************************************/
#ifndef CRC_H_
#define CRC_H_
#ifdef __cplusplus
extern "C" {
#endif
	
#include "common.h"
/**********************************************************************!
 * @brief CRC控制寄存器位定义
 *
 *******************************************************************/

#define CRC_WIDTH_16BIT                 0	/*!< 选择16位CRC协议 */   
#define CRC_WIDTH_32BIT                 1	/*!< 选择32位CRC协议 */ 
#define CRC_DATA_SEED                   1	/*!< 写入CRC数据寄存器的值为种子值 */  
#define CRC_DATA_DATA                   0	/*!< 写入CRC数据寄存器的值为数据值 */ 
#define CRC_READ_COMPLETE               1	/*!< 反转或补充CRC数据寄存器的读取值 */ 
#define CRC_READ_NONE                   0	/*!< 读取数据寄存器时不执行异或运算*/ 
#define CRC_READ_TRANSPOSE_NONE         0	/*!< 读取数据寄存器的值无转置 */ 
#define CRC_READ_TRANSPOSE_BIT          1	/*!< 读取数据寄存器的值，字节中的位转置，字不转置*/
#define CRC_READ_TRANSPOSE_ALL          2	/*!< 读取数据寄存器的值，字节中的位和字节均转置 */
#define CRC_READ_TRANSPOSE_BYTE         3	/*!< 读取数据寄存器的值，仅字节转置，字节中的位不转置 */
#define CRC_WRITE_TRANSPOSE_NONE        0	/*!< 写数据时无转置 */
#define CRC_WRITE_TRANSPOSE_BIT         1	/*!< 写数据时，字节中的位转置，字节不转置 */ 
#define CRC_WRITE_TRANSPOSE_ALL         2	/*!< 写数据时，字节中的位和字节均转置 */
#define CRC_WRITE_TRANSPOSE_BYTE        3	/*!< 写数据时，仅字节转置，字节中的位不转置 */

 
/******************************************************************************
*
* CRC 配置结构体类型.
*
*******************************************************************************/ 

typedef struct
{          
    uint8_t bWidth                  : 1;    /*!< 1: 32位CRC协议  0: 16位CRC协议 */
    uint8_t bDataType               : 1;    /*!< 1: 写入种子值 , 0: 写入数据 */
    uint8_t bFinalXOR               : 1;    /*!< 1: 读数据是反转或补充 , 0: 读数据时不执行异或*/
    uint8_t bRESERVED               : 1;    /*!< 保留位 */  
    uint8_t bTransposeReadType      : 2;    /*!< 读取数据时的转置类型, 参阅参考手册 */
    uint8_t bTransposeWriteType     : 2;    /*!< 写数据时的转置类型, 参阅参考手册 */      
    uint32_t u32PolyData               ;    /*!< 32位或16位多项式*/           
} CRC_ConfigType, *CRC_ConfigPtr  ; 


/******************************************************************************/

void        CRC_Init(CRC_ConfigType *pConfig);
uint32_t    CRC_Cal16(uint32_t u32Seed, uint8_t *msg, uint32_t u32SizeBytes);
uint32_t    CRC_Cal32(uint32_t u32Seed, uint8_t *msg, uint32_t u32SizeBytes);
void        CRC_DeInit(void);


#ifdef __cplusplus
}
#endif
#endif 



