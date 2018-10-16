#include <rtthread.h>
#include <nrf_bsp.h>
#include <md5.h>
#include <stdio.h>
#include <stdlib.h>
#include <st_mcuid.h>
#include <stmflash.h>

typedef char    BYTE;
typedef uint8_t BOOL;  

#define u8	uint8_t
#define u16 uint16_t
#define u32 uint32_t

static void NRF_CalcCols(u8 *col,u8 addr)
{
	u8 i;

	for(i = 5; i > 0; i--)
	{
		*col = (*col << 1) ^ addr;
		col++;
	}
}
static void NRF_InvMixColumn(u8 *column,u8 addr)
{
	u8 r[5];

	r[0] = column[1] ^ column[2] ^ column[3] ^ column[4];
	r[1] = column[0] ^ column[2] ^ column[3] ^ column[4];
	r[2] = column[0] ^ column[1] ^ column[3] ^ column[4];
	r[3] = column[0] ^ column[1] ^ column[2] ^ column[4];
	r[4] = column[0] ^ column[1] ^ column[2] ^ column[3];

	NRF_CalcCols(column,addr);

	r[0] ^= column[0] ^ column[1];
	r[1] ^= column[1] ^ column[2];
	r[2] ^= column[2] ^ column[3];
	r[3] ^= column[3] ^ column[4];
	r[4] ^= column[4] ^ column[0];

	NRF_CalcCols(column,addr);

	r[0] ^= column[0] ^ column[2];
	r[1] ^= column[1] ^ column[3];
	r[2] ^= column[2] ^ column[4];
	r[3] ^= column[3] ^ column[0];
	r[4] ^= column[4] ^ column[1];

	NRF_CalcCols(column,addr);

	column[0] ^= column[1] ^ column[2] ^ column[3] ^ column[4];
	r[0] ^= column[0];
	r[1] ^= column[0];
	r[2] ^= column[0];
	r[3] ^= column[0];
	r[4] ^= column[0];
	
	column[0] = r[0];
	column[1] = r[1];
	column[2] = r[2];
	column[3] = r[3];
	column[4] = r[4];
}
//软件CRC32 byte数据计算,将数据移到最高位,低位补上FF  
static u32 crc32_byte(u8 *ptr, u32 len)  
{  
    u32 CRC32=0xFFFFFFFF;//初值  
    u32 xbit,bits,data,i;  
    u8 buff[4];  
    u32 *p32 = (u32 *)buff;  
    const u32 dwPolynomial = 0x04c11db7;  
      
    buff[0] = buff[1] = buff[2] = buff[3] = 0XFF;  
    for(i = 0;i < len;i ++)  
    {   
		xbit = (u32)1 << 31;
        buff[3] = ptr[i];  
        data = *p32;  
        for(bits = 0; bits < 32; bits++)   
        {  
            if (CRC32 & 0x80000000) 
			{  
                CRC32 <<= 1;  
                CRC32 ^= dwPolynomial;  
            }  
            else  
                CRC32 <<= 1;  
            if (data & xbit)  
                CRC32 ^= dwPolynomial;  
  
            xbit >>= 1;  
        }  
    }  
    return CRC32;  
}
//crc单字节效验//方程式为X＾8＋X＾2＋X＋1
static u8 cal_crc8(u8 *ptr, u8 len) 
{
	u8 i,crc=0;
	
	while(len--!=0) 
	{
		for(i=0x80; i!=0; i/=2)
		{
			if((crc&0x80)!=0) 
			{
				crc*=2; 
				crc^=0x07;//余式CRC乘以2再求CRC
			}
			else 
				crc*=2;
			if((*ptr&i)!=0) 
				crc^=0x07;//再加上本位的CRC
		}
		ptr++;
	}
	return(crc);
}

u32 Get_RunTime(void)
{
	return rt_tick_get();
}
void NRF_GetMacAddr(u8 *mac,const u8 addr,u32 pwd)//传入NodeStatus.pwd
{
	u8 str[5]={0};
	u8 str1[10]={0};
	u8 i;
	
	rt_sprintf((char *)str1,"%d", pwd);
	if(addr>0&&addr<0xFF)
	{
		for(i=0;i<10;i++)//异或加密
		{
			 str1[i] ^= addr;
		}
		if(addr>0&&addr<128)
		{
			str[1]=(str1[0]+str1[1])<<2;
			str[2]=(str1[2]+str1[3])<<2;
			str[3]=(str1[4]+str1[5])<<2;
			str[4]=(str1[6]+str1[7])<<2;
			str[0]=(str1[8]+str1[9])<<2;
		}
		if(addr>=128&&addr<0xFF)
		{
			str[1]=str1[0]+str1[1];
			str[2]=str1[2]+str1[3];
			str[3]=str1[4]+str1[5];
			str[4]=str1[6]+str1[7];
			str[0]=str1[8]+str1[9];
		}
		NRF_InvMixColumn(str,addr);
	}
	else 
	{
		if(addr==0xFF)
		{
			str[0]=cal_crc8(str1, 10);
			str[1]=0xB9;
			str[2]=0x7F;
			str[3]=0x55;
			str[4]=0xB0;
		}
		if(addr==0)
		{
			for(i=0;i<5;i++)
			{
				 str[i] = 0xFF;
			}
		}
	}
	NRF_CopyMac(mac,str);
}

u32 Get_NetworkID(void)
{
//	u16 val1,val2;
	u8 ChipID[12]={0};//用以存贮96位ID号
	u8 key[16]={0};
//	u8 tmp[8]={0};
	u8 i;
	GetSTM32MCUID((u32*)ChipID, STM32F4_MCU);
	MD5_String(key,(char *)ChipID);
	for(i=0;i<16;i++)//异或加密
	{
		 key[i] ^= 0x22;
	}
//	for(i=0;i<8;i++)
//	{
//		tmp[i] = key[i];
//	}
//	MD5_String(key,(char *)tmp);
//	val1=cal_crc16(key, 16);
//	for(i=0;i<8;i++)
//	{
//		tmp[i] = key[i+8];
//	}
//	MD5_String(key,(char *)tmp);
//	val2=cal_crc16(key, 16);
//	rt_sprintf((char *)key,"%05d%05d}",val1,val2);
//	return strtol((char *)key,NULL,10);
//	return cal_crc32(key,16);
	return crc32_byte(key,16);
}
u8 Get_Nid(const u8 val)
{
	char up_id[3]={0};
	char up_id2[1]={0};
	u8 up_nid;
	
	rt_sprintf(up_id,"%d",val);
	if(val<100)//计算nid
	{
		up_id2[0]=up_id[1];//2位
		up_nid=atoi(up_id2);
	}
	else
	{
		up_id2[0]=up_id[2];//3位
		up_nid=atoi(up_id2);
	}
	return up_nid;
}
void NRF_CopyMac(u8 *dstMac,const u8 *srcMac)
{
	rt_memcpy(dstMac,srcMac,MAC_LEN);
}

#ifdef USING_NRF24L01_NODE
u8 NRF_StoreParam(NODESTATUS *NodeStatus)
{
	NRFSTOREDATA store_data;
	rt_memset((BYTE *)&store_data,0,sizeof(NRFSTOREDATA));
	store_data.tag = NRF_STORE_FLAG;
	store_data.addr=NodeStatus->addr;
	store_data.pwd=NodeStatus->pwd;
	STMFLASH_Write(NRF_STORE_ADDRESS,(uint32_t *)&store_data,FLASH_SIZE(sizeof(NRFSTOREDATA)));
	LPNRFSTOREDATA lp_store_data = (LPNRFSTOREDATA)NRF_STORE_ADDRESS;
	
	if(NRF_STORE_FLAG==lp_store_data->tag)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void NRF_ReadParam(NODESTATUS *NodeStatus)
{	
	LPNRFSTOREDATA lp_store_data = (LPNRFSTOREDATA)NRF_STORE_ADDRESS;
	if(NRF_STORE_FLAG==lp_store_data->tag)
	{
		NodeStatus->addr = lp_store_data->addr;
		NodeStatus->pwd = lp_store_data->pwd;
	}
	else
	{
		NodeStatus->addr = 0;
		NodeStatus->pwd = Get_NetworkID();
	}
}
void NRF_ClearStroreData(void)
{
	NRFSTOREDATA store_data;
	rt_memset((BYTE *)&store_data,0xff,sizeof(NRFSTOREDATA));
	STMFLASH_Write(NRF_STORE_ADDRESS,(uint32_t *)&store_data,FLASH_SIZE(sizeof(NRFSTOREDATA)));	
}
#else
u8 NRF_StoreParam(NODESTATUS *NodeStatus)
{
	NRFSTOREDATA store_data;
	rt_memset((BYTE *)&store_data,0,sizeof(NRFSTOREDATA));
	store_data.tag = NRF_STORE_FLAG;
	store_data.assign_addr=NodeStatus->assign_addr;
	STMFLASH_Write(NRF_STORE_ADDRESS,(uint32_t *)&store_data,FLASH_SIZE(sizeof(NRFSTOREDATA)));
	LPNRFSTOREDATA lp_store_data = (LPNRFSTOREDATA)NRF_STORE_ADDRESS;
	
	if(NRF_STORE_FLAG==lp_store_data->tag)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void NRF_ReadParam(NODESTATUS *NodeStatus)
{	
	LPNRFSTOREDATA lp_store_data = (LPNRFSTOREDATA)NRF_STORE_ADDRESS;
	if(NRF_STORE_FLAG==lp_store_data->tag)
	{		
		NodeStatus->assign_addr = lp_store_data->assign_addr;
		if(NodeStatus->assign_addr>=ASSIGN_ADDR_START || NodeStatus->assign_addr<ASSIGN_ADDR_END)
		{
			return;
		}
	}
	NodeStatus->assign_addr = ASSIGN_ADDR_START;
}
void NRF_ClearStroreData(void)
{
	NRFSTOREDATA store_data;
	rt_memset((BYTE *)&store_data,0xff,sizeof(NRFSTOREDATA));
	STMFLASH_Write(NRF_STORE_ADDRESS,(uint32_t *)&store_data,FLASH_SIZE(sizeof(NRFSTOREDATA)));	
}
#endif
