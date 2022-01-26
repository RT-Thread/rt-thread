#include "sys.h"
#include "HAL_misc.h"

void  RemapVtorTable(void)
{
    int i;
    RCC->AHB1ENR |= 1<<13;//bkp clk,enable sram
    //关ROM区中断
    for(i = 0;i<90;i++)
    {
        NVIC_DisableIRQ((IRQn_Type)i);
    }
    SCB->VTOR = 0;
    SCB->VTOR |= 0x1<<29;
    for(i = 0;i < 512;i+=4)
    *(u32*)(T_SRAM_BASE + i) = *(u32*)(T_SDRAM_BASE+i);

}

void  AI_Responder_enable(void)
{
  AI_Responder->ADDR1= 0x70807040;
//  AI_Responder->ADDR0 = 0x70027080;
  AI_Responder->ADDR1 = 0;
  AI_Responder->CCR &= ~(0x3<<3);
  AI_Responder->CCR |= 1;
  while((AI_Responder->SR & 0x3) != 2);
}
void  AI_Responder_disable(void)
{
    AI_Responder->CCR &= ~1;
}


//外部中断配置函数
//只针对GPIOA~E
//参数:
//GPIOx:0~4,代表GPIOA~E
//BITx:需要使能的位，例如PB12，就填 12;
//TRIM:触发模式,1,下降沿;2,上升沿;3，任意电平触发
//该函数一次只能配置1个IO口,多个IO口,需多次调用
//该函数会自动开启对应中断,以及屏蔽线
void Ex_NVIC_Config(u8 GPIOx,u8 BITx,u8 TRIM)
{
    u8 EXTOFFSET=(BITx%4)*4;
    RCC->APB2ENR|=1<<14;                        //使能SYSCFG时钟
    SYSCFG->EXTICR[BITx/4]&=~(0x000F<<EXTOFFSET);//清除原来设置！！！
    SYSCFG->EXTICR[BITx/4]|=GPIOx<<EXTOFFSET;   //EXTI.BITx映射到GPIOx.BITx
    //自动设置
    EXTI->IMR|=1<<BITx;                 //开启line BITx上的中断(如果要禁止中断，则反操作即可)
    if(TRIM&0x01)EXTI->FTSR|=1<<BITx;   //line BITx事件下降沿触发
    if(TRIM&0x02)EXTI->RTSR|=1<<BITx;   //line BITx事件上升沿触发
}


//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI
void WFI_SET(void)
{
    __ASM volatile("wfi");
}
//关闭所有中断(但是不包括fault和NMI中断)
void INTX_DISABLE(void)
{
    __ASM volatile("cpsid i");
}
//开启所有中断
void INTX_ENABLE(void)
{
    __ASM volatile("cpsie i");
}
//设置栈顶地址  __set_MSP(0x70002000);

//进入待机模式
void Sys_Standby(void)
{
    SCB->SCR|=1<<2;     //使能SLEEPDEEP位 (SYS->CTRL)
    RCC->APB1ENR|=1<<28;//使能电源时钟
    PWR->CSR|=1<<8;     //设置WKUP用于唤醒
    PWR->CR|=1<<2;      //清除Wake-up 标志
    PWR->CR|=1<<1;      //PDDS置位
    WFI_SET();          //执行WFI指令,进入待机模式
}
//系统软复位
void Sys_Soft_Reset(void)
{
    SCB->AIRCR =0X05FA0000|(u32)0x04;
}

//      TK499_NVIC_Init(2,2,TK80_IRQn,2);
//设置NVIC
//NVIC_PreemptionPriority:抢占优先级
//NVIC_SubPriority       :响应优先级
//NVIC_Channel           :中断编号
//NVIC_Group             :中断分组 0~4
//注意优先级不能超过设定的组的范围!否则会有意想不到的错误
//组划分:
//组0:0位抢占优先级,4位响应优先级
//组1:1位抢占优先级,3位响应优先级
//组2:2位抢占优先级,2位响应优先级
//组3:3位抢占优先级,1位响应优先级
//组4:4位抢占优先级,0位响应优先级
//NVIC_SubPriority和NVIC_PreemptionPriority的原则是,数值越小,越优先
void TK499_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group)
{
    u32 temp;
    NVIC_SetPriorityGrouping(NVIC_Group);//设置分组
    temp=NVIC_PreemptionPriority<<(4-NVIC_Group);
    temp|=NVIC_SubPriority&(0x0f>>NVIC_Group);
    temp&=0xf;                              //取低四位
    NVIC->ISER[NVIC_Channel/32]|=1<<NVIC_Channel%32;//使能中断位(要清除的话,设置ICER对应位为1即可)
    NVIC->IP[NVIC_Channel]|=temp<<4;                //设置响应优先级和抢断优先级
}

void TK80_IRQHandler(void)
{
    if(TK80->SR & 0x1)
    {

    }
    if(TK80->SR & 0x2)
    {

    }
    if(TK80->SR & 0x4)
    {

    }
    if(TK80->SR & 0x8)
    {

    }
    TK80->SR |= 0;
}

//备用函数
//#define T_SRAM_FUN1 0x20000400
//copyAtoB((u32)LCD_PutPixel&0xFFFFFFFE,T_SRAM_FUN1,800);//加载函数到SRAM
//void copyAtoB(u32 srcAdd,u32 dstAdd,u16 len)
//{
//    len = (len + 3)/4;
//    while(len--)
//    {
//        *(u32*)dstAdd = *(u32*)srcAdd;
//        dstAdd += 4 ;
//        srcAdd +=4 ;
//    }
//}














