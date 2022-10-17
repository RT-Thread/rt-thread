#ifndef __SWM341_QEI_H__
#define __SWM341_QEI_H__

typedef struct {
    uint8_t  mode;                  //QEI_MODE_X2、QEI_MODE_X4
    uint16_t maxcnt;                //最大计数值
    uint8_t  swapAB;                //1 交换A、B引脚
    uint8_t  intINDEXEn;            //检测到Index脉冲中断使能
    uint8_t  intMATCHEn;            //POSCNT递增到与MAXCNT相等，或POSCNT从MAXCNT递减到0中断使能
    uint8_t  intCNTOVEn;            //Counter Overrun，计数器溢出中断使能
    uint8_t  intERROREn;            //计数器错误中断使能
} QEI_InitStructure;


#define QEI_MODE_X2         0
#define QEI_MODE_X4         1

#define QEI_INT_INDEX       (1 << 0)
#define QEI_INT_MATCH       (1 << 1)
#define QEI_INT_CNTOV       (1 << 2)
#define QEI_INT_ERROR       (1 << 3)


void QEI_Init(QEI_TypeDef * QEIx, QEI_InitStructure * initStruct);      //QEI初始化
void QEI_Start(QEI_TypeDef * QEIx);                     //启动QEI
void QEI_Stop(QEI_TypeDef * QEIx);                      //关闭QEI

uint32_t QEI_IndexLvl(QEI_TypeDef * QEIx);              //QEI Index引脚电平
uint32_t QEI_CountDir(QEI_TypeDef * QEIx);              //QEI计数方向，0 反向计数    1 正向计数

void QEI_IntEn(QEI_TypeDef * QEIx, uint32_t it);        //QEI中断使能
void QEI_IntDis(QEI_TypeDef * QEIx, uint32_t it);       //QEI中断关闭
void QEI_IntClr(QEI_TypeDef * QEIx, uint32_t it);       //QEI中断标志清除
uint32_t QEI_IntStat(QEI_TypeDef * QEIx, uint32_t it);  //QEI中断状态查询


#endif //__SWM341_QEI_H__
