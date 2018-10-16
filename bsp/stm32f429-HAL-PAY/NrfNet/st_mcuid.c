#include <st_mcuid.h>

unsigned int idAddr[]={
	0x1FFFF7AC,  /*STM32F0唯一ID起始地址*/
	0x1FFFF7E8,  /*STM32F1唯一ID起始地址*/
	0x1FFF7A10,  /*STM32F2唯一ID起始地址*/
	0x1FFFF7AC,  /*STM32F3唯一ID起始地址*/
	0x1FFF7A10,  /*STM32F4唯一ID起始地址*/
	0x1FF0F420,  /*STM32F7唯一ID起始地址*/
	0x1FF80050,  /*STM32L0唯一ID起始地址*/
	0x1FF80050,  /*STM32L1唯一ID起始地址*/
	0x1FFF7590,  /*STM32L4唯一ID起始地址*/
	0x1FF0F420
}; /*STM32H7唯一ID起始地址*/

/*获取MCU的唯一ID*/
void GetSTM32MCUID(unsigned int *id,MCUTypedef type)
{
  if(id)
  {
    id[0]=*(unsigned int*)(idAddr[type]);
    id[1]=*(unsigned int*)(idAddr[type]+4);
    id[2]=*(unsigned int*)(idAddr[type]+8);
  }
}
