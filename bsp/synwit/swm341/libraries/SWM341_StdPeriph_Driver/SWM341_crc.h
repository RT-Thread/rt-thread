#ifndef __SWM341_CRC_H__
#define __SWM341_CRC_H__


typedef struct {
    uint32_t init_crc;          // 初始值
    uint8_t  Poly;              // CRC多项式，可取值CRC_POLY_11021、CRC_POLY_107、CRC_POLY_18005、CRC_POLY_104C11DB7
    uint8_t  in_width;          // 输入数据宽度，可取值CRC_WIDTH_32、CRC_WIDTH_16、CRC_WIDTH_8
    uint8_t  in_rev;            // 输入数据翻转，可取值CRC_REV_NOT、CRC_REV_ALL、CRC_REV_IN_BYTE、CRC_REV_BYTE
    bool     in_not;            // 输入数据取反
    uint8_t  out_rev;           // 输出结果翻转，可取值CRC_REV_NOT、CRC_REV_ALL、CRC_REV_IN_BYTE、CRC_REV_BYTE
    bool     out_not;           // 输出结果取反
} CRC_InitStructure;


#define CRC_POLY_11021      0   // x^16+x^12+x^5+1
#define CRC_POLY_107        1   // x^8+x^2+x+1
#define CRC_POLY_18005      2   // x^16+x^15+x^2+1
#define CRC_POLY_104C11DB7  3   // x^32+x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x+1

#define CRC_WIDTH_32        0
#define CRC_WIDTH_16        1
#define CRC_WIDTH_8         2

#define CRC_REV_NOT         0   // bit顺序不变
#define CRC_REV_ALL         1   // bit顺序完全翻转
#define CRC_REV_IN_BYTE     2   // bit顺序字节内翻转
#define CRC_REV_BYTE        3   // 仅字节顺序翻转


void CRC_Init(CRC_TypeDef * CRCx, CRC_InitStructure * initStruct);
void CRC_SetInitVal(CRC_TypeDef * CRCx, uint32_t init_crc);


/******************************************************************************************************************************************
* 函数名称: CRC_Write()
* 功能说明: CRC写入数据
* 输    入: uint32_t data     要写入的数据
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
static __INLINE void CRC_Write(uint32_t data)
{
    CRC->DATAIN = data;
}

/******************************************************************************************************************************************
* 函数名称: CRC_Result()
* 功能说明: 获取CRC计算结果
* 输    入: 无
* 输    出: uint32_t          CRC 计算结果
* 注意事项: 无
******************************************************************************************************************************************/
static __INLINE uint32_t CRC_Result(void)
{
    return CRC->RESULT;
}

#endif //__SWM341_CRC_H__
