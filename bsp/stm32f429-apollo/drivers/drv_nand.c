/*
 * File      : drv_nand.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author          Notes
 * 2017-04-10     lizhen9880      the first version
 */
#include "drv_nand.h"

#include <rtdevice.h>
#include <string.h>

#ifdef RT_USING_NFTL
#include <nftl.h>
#endif
#define NAND_DEBUG    rt_kprintf
/* nandflash confg */
#define PAGES_PER_BLOCK         64
#define PAGE_DATA_SIZE          2048
#define PAGE_OOB_SIZE           64
#define ECC_SIZE                4

#define SET_NAND_CMD(_c)    do{*(volatile rt_uint8_t*)(NAND_ADDRESS|NAND_CMD) = _c;}while(0)
#define SET_NAND_ADD(_a)    do{*(volatile rt_uint8_t*)(NAND_ADDRESS|NAND_ADDR) = _a;}while(0)    
#define SET_NAND_DAT(_d)    do{*(volatile rt_uint8_t*)NAND_ADDRESS = _d;}while(0) 
#define GET_NAND_DAT(_d)    do{_d = *(volatile rt_uint8_t*)NAND_ADDRESS;}while(0) 



static struct stm32f4_nand _device;
static rt_bool_t read_status(rt_uint8_t cmd);

NAND_HandleTypeDef NAND_Handler;    //NAND FLASH句柄

//NAND延时
void NAND_Delay(volatile rt_uint32_t i)
{
	while(i>0)i--;
}

//等待RB信号为某个电平
//rb:0,等待RB==0
//   1,等待RB==1
//返回值:0,成功
//       1,超时
rt_uint8_t NAND_WaitRB(volatile rt_uint8_t rb)
{
    volatile rt_uint16_t time=0;  
	while(time<10000)
	{
		time++;
		if(NAND_RB==rb)
        {
//            NAND_DEBUG("time:%d/%d  R/B:%d\n",time,10000,rb);
            return 0;
        }
	}
//    NAND_DEBUG("timeOUT\n");
	return 1;
}
//读NAND状态
//返回值:NAND状态值
//bit0:0,成功;1,错误(编程/擦除/READ)
//bit6:0,Busy;1,Ready
rt_uint8_t NAND_ReadStatus(void)
{
    volatile rt_uint8_t data=0; 
    SET_NAND_CMD(NAND_READSTA);//发送读状态命令
	data++;data++;data++;data++;data++;	//加延时,防止-O2优化,导致的错误.
 	data=*(volatile rt_uint8_t*)NAND_ADDRESS;			//读取状态值
    return data;
}
//等待NAND准备好
//返回值:NSTA_TIMEOUT 等待超时了
//      NSTA_READY    已经准备好
static rt_uint8_t wait_for_ready(void)
{
    rt_uint8_t status=0;
    volatile rt_uint32_t time=0; 
	while(1)						//等待ready
	{
		status=NAND_ReadStatus();	//获取状态值
		if(status&NSTA_READY)break;
		time++;
		if(time>=0X1FFFF)return NSTA_TIMEOUT;//超时
	}  
    return NSTA_READY;//准备好
}  

//复位NAND
//返回值:0,成功;
//    其他,失败
static rt_uint8_t nand_reset(void)
{ 
    SET_NAND_CMD(NAND_RESET);//复位NAND
    if(wait_for_ready()==NSTA_READY)return 0;//复位成功
    else return 1;								//复位失败
} 
//读取NAND FLASH的ID
//返回值:0,成功;
//    其他,失败
rt_uint8_t NAND_ModeSet(rt_uint8_t mode)
{   
    SET_NAND_CMD(NAND_FEATURE);
    SET_NAND_ADD(0X01);
    SET_NAND_DAT(mode);
    SET_NAND_DAT(0);
    SET_NAND_DAT(0);
    SET_NAND_DAT(0);
    if(wait_for_ready()==NSTA_READY)return 0;//成功
    else return 1;								//失败
}


//初始化NAND FLASH
void NAND_Init(void)
{
    FMC_NAND_PCC_TimingTypeDef ComSpaceTiming,AttSpaceTiming;
                                              
    NAND_Handler.Instance=FMC_NAND_DEVICE;
    NAND_Handler.Init.NandBank=FMC_NAND_BANK3;                          //NAND挂在BANK3上
    NAND_Handler.Init.Waitfeature=FMC_NAND_PCC_WAIT_FEATURE_DISABLE;    //关闭等待特性
    NAND_Handler.Init.MemoryDataWidth=FMC_NAND_PCC_MEM_BUS_WIDTH_8;     //8位数据宽度
    NAND_Handler.Init.EccComputation=FMC_NAND_ECC_DISABLE;              //不使用ECC
    NAND_Handler.Init.ECCPageSize=FMC_NAND_ECC_PAGE_SIZE_2048BYTE;      //ECC页大小为2k
    NAND_Handler.Init.TCLRSetupTime=0;                                  //设置TCLR(tCLR=CLE到RE的延时)=(TCLR+TSET+2)*THCLK,THCLK=1/180M=5.5ns
    NAND_Handler.Init.TARSetupTime=1;                                   //设置TAR(tAR=ALE到RE的延时)=(TAR+TSET+2)*THCLK,THCLK=1/180M=5.5n。   
   
    ComSpaceTiming.SetupTime=2;         //建立时间
    ComSpaceTiming.WaitSetupTime=3;     //等待时间
    ComSpaceTiming.HoldSetupTime=2;     //保持时间
    ComSpaceTiming.HiZSetupTime=1;      //高阻态时间
    
    AttSpaceTiming.SetupTime=2;         //建立时间
    AttSpaceTiming.WaitSetupTime=3;     //等待时间
    AttSpaceTiming.HoldSetupTime=2;     //保持时间
    AttSpaceTiming.HiZSetupTime=1;      //高阻态时间
    
    HAL_NAND_Init(&NAND_Handler,&ComSpaceTiming,&AttSpaceTiming); 
    nand_reset();       		        //复位NAND
//    delay_ms(100);
    wait_for_ready();
	NAND_ModeSet(4);			        //设置为MODE4,高速模式 

}

//NAND FALSH底层驱动,引脚配置，时钟使能
//此函数会被HAL_NAND_Init()调用
void HAL_NAND_MspInit(NAND_HandleTypeDef *hnand)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_FMC_CLK_ENABLE();             //使能FMC时钟
    __HAL_RCC_GPIOD_CLK_ENABLE();           //使能GPIOD时钟
    __HAL_RCC_GPIOE_CLK_ENABLE();           //使能GPIOE时钟
    __HAL_RCC_GPIOG_CLK_ENABLE();           //使能GPIOG时钟
    
	//初始化PD6 R/B引脚
	GPIO_Initure.Pin=GPIO_PIN_6;
    GPIO_Initure.Mode=GPIO_MODE_INPUT;          //输入
    GPIO_Initure.Pull=GPIO_PULLUP;    			//上拉          
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;         //高速
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);
	   
	//初始化PG9 NCE3引脚
    GPIO_Initure.Pin=GPIO_PIN_9;
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;          //输入
    GPIO_Initure.Pull=GPIO_NOPULL;    			//上拉          
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;         //高速
	GPIO_Initure.Alternate=GPIO_AF12_FMC;       //复用为FMC
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);  
	
    //初始化PD0,1,4,5,11,12,14,15
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5|\
                     GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_Initure.Pull=GPIO_NOPULL;              
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);

    //初始化PE7,8,9,10
    GPIO_Initure.Pin=GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10;
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);
}



//读NAND状态
//返回值:NAND状态值
//bit0:0,成功;1,错误(编程/擦除/READ)
//bit6:0,Busy;1,Ready
static rt_bool_t read_status(rt_uint8_t cmd)
{
    volatile rt_uint8_t value=0; 
    SET_NAND_CMD(NAND_READSTA);//发送读状态命令
	value++;value++;value++;value++;value++;	//加延时,防止-O2优化,导致的错误.
 	value=*(volatile rt_uint8_t*)NAND_ADDRESS;			//读取状态值
    switch (cmd)
    {
    case NAND_WRITE0:
    case NAND_ERASE1:
        if (value & 0x01)           /* Erase/Program failure(1) or pass(0) */
            return (RT_FALSE);
        else
            return (RT_TRUE);

    case NAND_AREA_TRUE1:            /* bit 5 and 6, Read busy(0) or ready(1) */
        return (RT_TRUE);

    default:
        break;
    }

    return (RT_FALSE);
}

static rt_err_t nand_MT29F4G08_readid(struct rt_mtd_nand_device *device)
{
    rt_uint32_t id;  
    SET_NAND_CMD(NAND_READID); //发送读取ID命令
    SET_NAND_ADD(0X00);
    GET_NAND_DAT(_device.id[0]);//ID一共有5个字节
    GET_NAND_DAT(_device.id[1]);
    GET_NAND_DAT(_device.id[2]);
    GET_NAND_DAT(_device.id[3]);
    GET_NAND_DAT(_device.id[4]);

    //镁光的NAND FLASH的ID一共5个字节，但是为了方便我们只取4个字节组成一个32位的ID值
    //根据NAND FLASH的数据手册，只要是镁光的NAND FLASH，那么一个字节ID的第一个字节都是0X2C
    //所以我们就可以抛弃这个0X2C，只取后面四字节的ID值。
    id=((rt_uint32_t)_device.id[1])<<24|((rt_uint32_t)_device.id[2])<<16|((rt_uint32_t)_device.id[3])<<8|_device.id[4];
    
    rt_kprintf("\nNAND ID: 0x%08X\n", id);
    return RT_EOK;
    
}
static rt_err_t nand_datacorrect(uint32_t generatedEcc, uint32_t readEcc, uint8_t *data)
{
#define ECC_MASK28    0x0FFFFFFF          /* 28 valid ECC parity bits. */
#define ECC_MASK      0x05555555          /* 14 ECC parity bits.       */

    rt_uint32_t count, bitNum, byteAddr;
    rt_uint32_t mask;
    rt_uint32_t syndrome;
    rt_uint32_t eccP;                            /* 14 even ECC parity bits. */
    rt_uint32_t eccPn;                           /* 14 odd ECC parity bits.  */

    syndrome = (generatedEcc ^ readEcc) & ECC_MASK28;

    if (syndrome == 0)
        return (RT_MTD_EOK);                  /* No errors in data. */

    eccPn = syndrome & ECC_MASK;              /* Get 14 odd parity bits.  */
    eccP  = (syndrome >> 1) & ECC_MASK;       /* Get 14 even parity bits. */

    if ((eccPn ^ eccP) == ECC_MASK)           /* 1-bit correctable error ? */
    {
        bitNum = (eccP & 0x01) |
                 ((eccP >> 1) & 0x02) |
                 ((eccP >> 2) & 0x04);
        NAND_DEBUG("ECC bit %d\n",bitNum);
        byteAddr = ((eccP >> 6) & 0x001) |
                   ((eccP >> 7) & 0x002) |
                   ((eccP >> 8) & 0x004) |
                   ((eccP >> 9) & 0x008) |
                   ((eccP >> 10) & 0x010) |
                   ((eccP >> 11) & 0x020) |
                   ((eccP >> 12) & 0x040) |
                   ((eccP >> 13) & 0x080) |
                   ((eccP >> 14) & 0x100) |
                   ((eccP >> 15) & 0x200) |
                   ((eccP >> 16) & 0x400) ;

        data[ byteAddr ] ^= 1 << bitNum;

        return RT_MTD_EOK;
    }

    /* Count number of one's in the syndrome. */
    count = 0;
    mask  = 0x00800000;
    while (mask)
    {
        if (syndrome & mask)
            count++;
        mask >>= 1;
    }

    if (count == 1)           /* Error in the ECC itself. */
        return RT_MTD_EECC;

    return -RT_MTD_EECC;       /* Unable to correct data. */

#undef ECC_MASK
#undef ECC_MASK24
}
static rt_err_t nand_MT29F4G08_readpage(struct rt_mtd_nand_device *device,
                                     rt_off_t                   page,
                                     rt_uint8_t                *data,
                                     rt_uint32_t                data_len,
                                     rt_uint8_t                *spare,
                                     rt_uint32_t                spare_len)
{
    rt_uint32_t index;
    rt_uint32_t gecc, recc;
    rt_uint8_t tmp[4];
    rt_err_t result;
    rt_uint32_t i;
    page = page + device->block_start * device->pages_per_block;
    if (page/device->pages_per_block > device->block_end)
    {
        return -RT_MTD_EIO;
    }

    result = RT_MTD_EOK;
    rt_mutex_take(&_device.lock, RT_WAITING_FOREVER);

    if (data && data_len)
    {
        SET_NAND_CMD(NAND_AREA_A); //发送地址
        SET_NAND_ADD((rt_uint8_t)(0&0xFF));
        SET_NAND_ADD((rt_uint8_t)(0>>8));
        SET_NAND_ADD((rt_uint8_t)(page & 0xFF));
        SET_NAND_ADD((rt_uint8_t)(page >> 8));
        SET_NAND_ADD((rt_uint8_t)(page >> 16));
        SET_NAND_CMD(NAND_AREA_TRUE1);
        //下面两行代码是等待R/B引脚变为低电平，其实主要起延时作用的，等待NAND操作R/B引脚。因为我们是通过
        //将STM32的NWAIT引脚(NAND的R/B引脚)配置为普通IO，代码中通过读取NWAIT引脚的电平来判断NAND是否准备
        //就绪的。这个也就是模拟的方法，所以在速度很快的时候有可能NAND还没来得及操作R/B引脚来表示NAND的忙
        //闲状态，就读取了R/B引脚,这个时候肯定会出错的，事实上确实是会出错!
        NAND_WaitRB(0);			//等待RB=0 
        //下面2行代码是真正判断NAND是否准备好的
        NAND_WaitRB(1);			//等待RB=1 
        FMC_NAND_ECC_Enable(NAND_Handler.Instance,FMC_NAND_BANK3);
        
        for (i = 0; i < data_len; i ++)
        {
            GET_NAND_DAT(data[i]);  
        }
        gecc = FMC_NAND_GetECC(NAND_Handler.Instance,(uint32_t*)&gecc,FMC_NAND_BANK3,10);

        if (data_len == PAGE_DATA_SIZE)
        {
            for (index = 0; index < ECC_SIZE; index ++)
            {
                GET_NAND_DAT(tmp[index]);
            }
                
            if (spare && spare_len)
            {
                for (i = ECC_SIZE; i < spare_len; i ++)
                {
                    GET_NAND_DAT(spare[i]);      
                }
                rt_memcpy(spare, tmp , ECC_SIZE);
            }

            recc   = (tmp[3] << 24) | (tmp[2] << 16) | (tmp[1] << 8) | tmp[0];

            if (recc != 0xFFFFFFFF && gecc != 0)
                result = nand_datacorrect(gecc, recc, data);

            if (result != RT_MTD_EOK)
                NAND_DEBUG("page: %d, gecc %X, recc %X>",page, gecc, recc);

            goto _exit;
        }
    }

    if (spare && spare_len)
    {
        SET_NAND_CMD(NAND_AREA_A); //发送地址
        SET_NAND_ADD((rt_uint8_t)(PAGE_DATA_SIZE&0xFF));
        SET_NAND_ADD((rt_uint8_t)(PAGE_DATA_SIZE>>8));
        SET_NAND_ADD((rt_uint8_t)(page & 0xFF));
        SET_NAND_ADD((rt_uint8_t)(page >> 8));
        SET_NAND_ADD((rt_uint8_t)(page >> 16));
        SET_NAND_CMD(NAND_AREA_TRUE1);
        
        //下面两行代码是等待R/B引脚变为低电平，其实主要起延时作用的，等待NAND操作R/B引脚。因为我们是通过
        //将STM32的NWAIT引脚(NAND的R/B引脚)配置为普通IO，代码中通过读取NWAIT引脚的电平来判断NAND是否准备
        //就绪的。这个也就是模拟的方法，所以在速度很快的时候有可能NAND还没来得及操作R/B引脚来表示NAND的忙
        //闲状态，就读取了R/B引脚,这个时候肯定会出错的，事实上确实是会出错!
        NAND_WaitRB(0);			//等待RB=0 
        //下面2行代码是真正判断NAND是否准备好的
        NAND_WaitRB(1);			//等待RB=1 

        for (i = 0; i < spare_len; i ++)
        {
            GET_NAND_DAT(spare[i]);
        }

    }
_exit:
    rt_mutex_release(&_device.lock);

    return (result);
}

static rt_err_t nand_MT29F4G08_writepage(struct rt_mtd_nand_device *device,
                                      rt_off_t                   page,
                                      const rt_uint8_t          *data,
                                      rt_uint32_t                data_len,
                                      const rt_uint8_t          *spare,
                                      rt_uint32_t                spare_len)
{
    rt_err_t result;
    rt_uint32_t gecc;
    rt_uint32_t i;
    
    page = page + device->block_start * device->pages_per_block;
    if (page/device->pages_per_block > device->block_end)
    {
        return -RT_MTD_EIO;
    }

    result = RT_MTD_EOK;
    rt_mutex_take(&_device.lock, RT_WAITING_FOREVER);

    if (data && data_len)
    {
        SET_NAND_CMD(NAND_WRITE0); //发送地址
        SET_NAND_ADD((rt_uint8_t)(0&0xFF));
        SET_NAND_ADD((rt_uint8_t)(0>>8));
        SET_NAND_ADD((rt_uint8_t)(page & 0xFF));
        SET_NAND_ADD((rt_uint8_t)(page >> 8));
        SET_NAND_ADD((rt_uint8_t)(page >> 16));
        
        FMC_NAND_ECC_Enable(NAND_Handler.Instance,FMC_NAND_BANK3);
        
        for (i = 0; i < data_len; i ++)
        {
            SET_NAND_DAT(data[i]);     
        }
        gecc = FMC_NAND_GetECC(NAND_Handler.Instance,(uint32_t*)&gecc,FMC_NAND_BANK3,10);
        
        FMC_NAND_ECC_Disable(NAND_Handler.Instance,FMC_NAND_BANK3);

        if (data_len == PAGE_DATA_SIZE)
        {
            SET_NAND_DAT((uint8_t)gecc);
            SET_NAND_DAT((uint8_t)(gecc >> 8));
            SET_NAND_DAT((uint8_t)(gecc >> 16));
            SET_NAND_DAT((uint8_t)(gecc >> 24));

            if (spare && spare_len)
            {
                for (i = ECC_SIZE; i < spare_len; i ++)
                {
                    SET_NAND_DAT(spare[i]);     
                }
            }
            
        }
        SET_NAND_CMD(NAND_WRITE_TURE1);
        if(wait_for_ready()!=NSTA_READY)
        {
            nand_reset();
            result = -RT_MTD_EIO;//失败
        }
        goto _exit;
    }

    if (spare && spare_len)
    {
        SET_NAND_CMD(NAND_WRITE0); //发送地址
        SET_NAND_ADD((rt_uint8_t)(PAGE_DATA_SIZE&0xFF));
        SET_NAND_ADD((rt_uint8_t)(PAGE_DATA_SIZE>>8));
        SET_NAND_ADD((rt_uint8_t)(page & 0xFF));
        SET_NAND_ADD((rt_uint8_t)(page >> 8));
        SET_NAND_ADD((rt_uint8_t)(page >> 16));
        
        if (spare && spare_len)
        for (i = ECC_SIZE; i < spare_len; i ++)
        {
            SET_NAND_DAT(spare[i]);
        }
        SET_NAND_CMD(NAND_WRITE_TURE1);
        if(wait_for_ready()!=NSTA_READY)
        {
            nand_reset();
            result = -RT_MTD_EIO;//失败
        }
    }

_exit:
    rt_mutex_release(&_device.lock);

    return (result);

}

static rt_err_t nand_MT29F4G08_eraseblock(struct rt_mtd_nand_device *device,
                                       rt_uint32_t block)
{
    unsigned int blockPage;
    rt_err_t result;
    /* add the start blocks */
    block = block + device->block_start;
    blockPage = (block << 6);
    result = RT_MTD_EOK;
    
    rt_mutex_take(&_device.lock, RT_WAITING_FOREVER);

    SET_NAND_CMD(NAND_ERASE0); //发送地址
    SET_NAND_ADD((rt_uint8_t)blockPage);
    SET_NAND_ADD((rt_uint8_t)(blockPage>>8));
    SET_NAND_ADD((rt_uint8_t)(blockPage>>16));
    SET_NAND_CMD(NAND_ERASE1);
	if(wait_for_ready()!=NSTA_READY)
    {
        nand_reset();
        result = -RT_MTD_EIO;//失败
    }
    rt_mutex_release(&_device.lock);
    return result;
}

static rt_err_t nand_MT29F4G08_pagecopy(struct rt_mtd_nand_device *device,
                                     rt_off_t                   src_page,
                                     rt_off_t                   dst_page)
{
    rt_err_t result = RT_MTD_EOK;
    rt_uint32_t source_block=0,dest_block=0; 
    src_page = src_page + device->block_start * device->pages_per_block;
    dst_page = dst_page + device->block_start * device->pages_per_block;
    //判断源页和目的页是否在同一个plane中
    source_block=src_page/device->pages_per_block;
    dest_block=dst_page/device->pages_per_block;
    if((source_block%2)!=(dest_block%2))return RT_MTD_ESRC;	//不在同一个plane内 
    
    SET_NAND_CMD(NAND_MOVEDATA_CMD0);//发送命令0X00
    SET_NAND_ADD((rt_uint8_t)(0&0xFF));    //发送源页地址
    SET_NAND_ADD((rt_uint8_t)(0>>8));
    SET_NAND_ADD((rt_uint8_t)(src_page & 0xFF));
    SET_NAND_ADD((rt_uint8_t)(src_page >> 8));
    SET_NAND_ADD((rt_uint8_t)(src_page >> 16));
    SET_NAND_CMD(NAND_MOVEDATA_CMD1);//发送命令0X35 

    //下面两行代码是等待R/B引脚变为低电平，其实主要起延时作用的，等待NAND操作R/B引脚。因为我们是通过
    //将STM32的NWAIT引脚(NAND的R/B引脚)配置为普通IO，代码中通过读取NWAIT引脚的电平来判断NAND是否准备
    //就绪的。这个也就是模拟的方法，所以在速度很快的时候有可能NAND还没来得及操作R/B引脚来表示NAND的忙
    //闲状态，结果我们就读取了R/B引脚,这个时候肯定会出错的，事实上确实是会出错!大家也可以将下面两行
    //代码换成延时函数,只不过这里我们为了效率所以没有用延时函数。
	result=NAND_WaitRB(0);			//等待RB=0 
	if(result)return -RT_MTD_EIO;	//超时退出
    //下面2行代码是真正判断NAND是否准备好的
	result=NAND_WaitRB(1);			//等待RB=1 
    if(result)return -RT_MTD_EIO;	//超时退出 
    
    SET_NAND_CMD(NAND_MOVEDATA_CMD2);//发送命令0X85
    SET_NAND_ADD((rt_uint8_t)(0&0xFF)); //发送目的页地址
    SET_NAND_ADD((rt_uint8_t)(0>>8));
    SET_NAND_ADD((rt_uint8_t)(dst_page & 0xFF));
    SET_NAND_ADD((rt_uint8_t)(dst_page >> 8));
    SET_NAND_ADD((rt_uint8_t)(dst_page >> 16));
    SET_NAND_CMD(NAND_MOVEDATA_CMD3);//发送命令0X10
 
    if(wait_for_ready()!=NSTA_READY)
    {
        nand_reset();
        return -RT_MTD_EIO;//失败
    }

    return RT_MTD_EOK;


}

static rt_err_t nand_MT29F4G08_checkblock(struct rt_mtd_nand_device* device, rt_uint32_t block)
{
    return (RT_MTD_EOK);
}

static rt_err_t nand_MT29F4G08_markbad(struct rt_mtd_nand_device* device, rt_uint32_t block)
{
    return (RT_MTD_EOK);
}

static const struct rt_mtd_nand_driver_ops ops =
{
    nand_MT29F4G08_readid,
    nand_MT29F4G08_readpage,
    nand_MT29F4G08_writepage,
    nand_MT29F4G08_pagecopy,
    nand_MT29F4G08_eraseblock,
    nand_MT29F4G08_checkblock,
    nand_MT29F4G08_markbad,
};
static struct rt_mtd_nand_device _partition[1];

int nand_MT29F4G08_hw_init(void)
{
   NAND_Init();
    rt_mutex_init(&_device.lock, "nand", RT_IPC_FLAG_FIFO);
    /* register nand0 */
    _partition[0].page_size       = PAGE_DATA_SIZE;
    _partition[0].pages_per_block = PAGES_PER_BLOCK;
    _partition[0].plane_num       = 2;
    _partition[0].oob_size        = PAGE_OOB_SIZE;
    _partition[0].oob_free        = PAGE_OOB_SIZE - ((PAGE_DATA_SIZE) * 3 / 256);
    _partition[0].block_start     = 0;
    _partition[0].block_end       = 4095;

    _partition[0].block_total     = _partition[0].block_end - _partition[0].block_start;
    _partition[0].ops             = &ops;

    rt_mtd_nand_register_device("nand0", &_partition[0]);
    nand_MT29F4G08_readid(&_partition[0]);

    return RT_EOK;
}
INIT_BOARD_EXPORT(nand_MT29F4G08_hw_init);
