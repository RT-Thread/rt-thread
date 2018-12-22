#include "flash.h"
#include "eeprom.h"
#include <string.h>

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
*
* EEPROM 擦除命令，擦掉eeprom
*输入参数：地址，函数将会擦除adr所在的512bytes eeprom
*
******************************************************************************/
uint16_t Adress_Js(uint32_t adr)
{
    uint16_t err = EEPROM_ERR_SUCCESS;

  
    if(adr & 0x03)
    {
        err = EEPROM_ERR_INVALID_PARAM;
	return (err);
	}
  
    if(adr >1024)
    {
        err=EEPROM_ADR_OverFlow;
      return(err);
    }
    return(err);
}

/******************************************************************************
*
* EEPROM 擦除命令，擦掉eeprom
*输入参数：地址，函数将会擦除adr所在的512bytes eeprom
*
******************************************************************************/


uint16_t EEPROM_Erase(uint32_t adr)
{
    uint16_t err = EEPROM_ERR_SUCCESS;
    uint32_t e_adr;

     if(adr & 0x03)
    {
        err = EEPROM_ERR_INVALID_PARAM;
	return (err);
	}
  
    if(adr >1024)
    {
        err=EEPROM_ADR_OverFlow;
    
      return(err);
    }
    
    e_adr=adr+EEPROM_START_ADR;
    err = Flash_EraseSector(e_adr);  
    return(err);
}

/******************************************************************************
*
* EEPROM 读取函数，读取地址所在的eeprom
*输入参数：地址
*
******************************************************************************/
uint32_t EEPROM_Read(uint32_t adr)
{
    uint16_t err = EEPROM_ERR_SUCCESS;
    uint32_t e_adr;
    uint32_t data;
    
    if(adr & 0x03)
    {
        err = EEPROM_ERR_INVALID_PARAM;
	return (err);
	}
  
    if(adr >1024)
    {
        err=EEPROM_ADR_OverFlow;
      return(err);
    }
    
    e_adr=adr+EEPROM_START_ADR;
    data = M32(e_adr);
    return(data);
    
}
/******************************************************************************
*
* EEPROM 写函数，写地址所在的eeprom
*写之前读取出来，判断eeprom是否为空，如果为空，则直接写
*如果非空，则先把整个512bytes sector读取到sram，修改要写的位置
*然后再写入到flash，模拟一个eeprom的写过程
*输入参数：地址
*
******************************************************************************/
uint16_t EEPROM_Write(uint32_t adr, uint32_t Data)
{
  
    uint32_t err = EEPROM_ERR_SUCCESS;
    uint32_t e_adr;
    uint32_t r_data;
    uint16_t i;
    uint32_t start_adr;
 //   uint32_t modify_adr;
    uint32_t EEPROM_DATA[128];

    if(adr & 0x03)
    {
        err = EEPROM_ERR_INVALID_PARAM;
	return (err);
	}
  
    if(adr >1024)
    {
        err=EEPROM_ADR_OverFlow;
      return(err);
    }

    
    r_data = EEPROM_Read(adr);
    
    e_adr=adr+EEPROM_START_ADR;

    if(r_data== EEPROM_BLANK) //如果要写的位置是空的，则直接写
    {
      err= Flash_Program1LongWord(e_adr,Data);
    }
   else if((r_data&Data) == Data)//如果要写的位置对应的bit，和要写的数据一致，或者是1，也是可以直接写
     {
      err= Flash_Program1LongWord(e_adr,Data);
    }
    else if(r_data == Data) //如果要写的数据和现有的数据一致，就不进行任何操作，直接返回
    {
      return(err);
    }
    else
    {
        start_adr = e_adr & EEPROM_SECTOR_MASK; //计算出sector的头地址    
        
        for( i=0;i<128;i++ ) //如果要写的位置不为空，则先把flash内容读取出来，放在sram中，修改
        {
          EEPROM_DATA[i] = M32(start_adr + 4*i);
        }
            
        EEPROM_DATA[(adr&EEPROM_ARRAY_ADR_MASK)>>2] = Data; //修改SRAM 中的数据
        
        err=EEPROM_Erase(adr);
     
        err=Flash_Program(start_adr,(uint8_t*)EEPROM_DATA,512);//然后写入flash
    }
    return(err);
    
}

/******************************************************************************
*
*Byte 写函数
*
******************************************************************************/
uint16_t EEPROM_WriteByte(uint32_t adr, uint8_t Data)
{
    uint32_t err = EEPROM_ERR_SUCCESS;
    uint32_t data_mask;
    uint32_t r_data;
    uint32_t data_m0;
    uint32_t data_m1;
    uint32_t word_adr = adr &0x3fc;
    uint32_t  b_sit= adr & 0x3;
    

 //先让高位为FF
    data_m0 = Data << b_sit*8;   
    data_mask = 0xFFFFFFFF<<(b_sit+1)*8;    
//   printf("datam0:=0x%x \n",data_m0);    
//然后让低位为FF    
     data_m1 = 0xFFFFFFFF >> (32-b_sit*8);
     data_m1 = data_m1 | data_m0 | data_mask ;
     
//    printf("datam1:=0x%x \n",data_m1);  
    
    r_data = EEPROM_Read(word_adr);
//    printf("r_data:=0x%x \n",r_data);        
//或上原来的数据    
    data_m1 = data_m1 & r_data;
		
    
//    printf("data_m1:=0x%x \n",data_m1);     ;           
    err = EEPROM_Write(word_adr , data_m1);
    
    return(err);

}

/******************************************************************************
*
*Byte 读函数
*
******************************************************************************/
uint8_t EEPROM_ReadByte(uint32_t adr)
{
   uint32_t r_data;
   uint32_t word_adr = adr &0x3fc;
   uint32_t b_sit= adr & 0x3;
   uint8_t  data;
   
    r_data = EEPROM_Read(word_adr);
    data = (r_data>>b_sit*8)& 0xff;
    return(data);
   
   
}


/******************************************************************************
*
*写函数，写一个长度为bytesize，到eeprom
*先把1k的eeprom读取放入sram，然后修改要写的位置，
*这个函数是还可以再优化的
*这样更改后，没有考虑2K eeprom 。超过2K 也是完全可以的。
******************************************************************************/
uint16_t EERPOM_Writeup4byte(uint32_t adr,uint8_t *pData,uint32_t length)
{
	uint8_t buf[512];
	uint8_t *pbuf;
	uint32_t e_adr;
	uint32_t e_sec;
	uint32_t e_offset;
	uint32_t a;
	uint32_t err = EEPROM_ERR_SUCCESS;
	
   #ifdef IAR
    if(adr & 0x03)
    {
        err = EEPROM_ERR_INVALID_PARAM;
	      return (err);
	   }
    #endif
  
    if((adr + length )>1024)
    {
        err=EEPROM_ADR_OverFlow;
      return(err);
    }
    
	e_adr=adr+EEPROM_START_ADR;
	e_sec=e_adr & EEPROM_SECTOR_MASK;
	e_offset=e_adr & 0x1ff;

	
	while (length>0){
          //如果起始地址不等于0，或者长度小于512 都进入这个循环
		if (e_offset||(length<512)){
			pbuf=buf;
			a=512-e_offset;
			a=(length>a?a:length);
			
			memcpy(buf,(uint8_t*)e_sec,512);
			memcpy(&buf[e_offset],pData,a);
			pData+=a;
			length-=a;
			e_offset=0;

		}else{ //如果起始地址等于0且长度大于512 则简单了
			pbuf=pData;
			pData+=512;
			length-=512;
		}
		err=Flash_EraseSector(e_sec);
		err=Flash_Program(e_sec,(uint8_t*)pbuf,512);//然后写入flash
		e_sec+=0x200;
	}
	return err;
}


/*
uint16_t EERPOM_Writeup4byte(uint32_t adr,uint8_t *pData,uint32_t bytesize)
{
    uint32_t err = EEPROM_ERR_SUCCESS;
    uint32_t e_adr;
    uint16_t i;
    uint32_t start_adr;
    uint32_t EEPROM_DATA[256];
    uint32_t longword = bytesize >>2;
    uint32_t *pwData = (uint32_t*)pData ;
    
    err=Adress_Js(adr);
    
    if(adr+bytesize >1024) //如果写入的地址,加上要写的数据的个数大于1024，则报错
    {
      err = EEPROM_ADR_OverFlow;
      return(err);
    }
    
    e_adr=adr+EEPROM_START_ADR;
    
    start_adr = e_adr & EEPROM_SECTOR_MASK; //计算出sector 头地址

    for( i=0;i<256;i++ ) //先把数据读取到sram
      {
        EEPROM_DATA[i] = M32(start_adr + 4*i);
        }
    for( i=0 ;i<longword ;i++) //然后修改要写的地址
      {
        EEPROM_DATA[(adr>>2)+i] = *pwData++;
      }
     //先erase掉2个eeprom secoter     
     err=EEPROM_Erase(0x000);
     err=EEPROM_Erase(0x200);   
      
    err=Flash_Program(start_adr,(uint8_t*)EEPROM_DATA,1024);//然后写入flash
    
    return(err);
}
*/

