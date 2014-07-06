#include <board.h>
#include <rtthread.h>

#ifdef  RT_USING_COMPONENTS_INIT
#include <components.h>
#endif  /* RT_USING_COMPONENTS_INIT */

#ifdef RT_USING_DFS
/* dfs filesystem:ELM filesystem init */
#include <dfs_elm.h>
/* dfs Filesystem APIs */
#include <dfs_posix.h>
#endif

rt_err_t File_systeminit(void);

int Readline(int fd,char * buff,int maxlen)
{

	int num=maxlen;
	char temp;
	while(maxlen--)
	{
	if(read(fd,&temp,1)==0)break;
	if(temp=='\n'|temp=='\r')
	{
		if(temp=='\r')
		{
		read(fd,&temp,1);
			if(temp!='\n')
				lseek(fd,SEEK_CUR,-1);
		}
	  else if(temp=='\n')
		{
		read(fd,&temp,1);
			if(temp!='\r')
				lseek(fd,SEEK_CUR,-1);
		}
		
		*buff=0;
		return num-maxlen;
	}
	*buff=temp;
	buff++;
	}
	return num;
}

rt_err_t sys_inf(void)
{
	int fd,x=0,y=4,i,eer=0;
	char read_buf[50];
	{
		int size,cmd_size=0;
		int run_type=0;
		char * so_path=rt_malloc(40);
		char * bin_path=rt_malloc(40);
		
		fd=open("/sys/sys.inf",DFS_O_WRONLY,0);
		if(fd>=0)
		{
		for(i=0;i<3;i++)
		{
		size=Readline(fd,read_buf,50);
		if(rt_memcmp(read_buf,"init_file=",10)==0)
		{
		rt_memcpy(so_path,read_buf+10,size-10);
		run_type|=0x8000;
		}
		else if(rt_memcmp(read_buf,"data_file=",10)==0)
		{
		rt_memcpy(bin_path,read_buf+10,size-10);
		cmd_size=size-10;
		}
		else if(rt_memcmp(read_buf,"init_type=",10)==0)
		{
		 
			if(rt_memcmp(read_buf+10,"updata",6)==0)run_type|=1;
			else if(rt_memcmp(read_buf+10,"run",3)==0)run_type|=0;	
			else run_type=0;
		}
		
		}
		close(fd);
		if(run_type&0x8000)
		{
			fd=open(so_path,DFS_O_WRONLY,0);
		if((run_type&0x01)&&fd>=0)
		{
			close(fd);
			fd=open(bin_path,DFS_O_WRONLY,0);
			if(fd>=0)
			{
			close(fd);
			if(dfs_file_unlink("/sys/sys.inf")<0)
			{
				fd=open("/sys/sys.inf",DFS_O_WRONLY,0);
			//lseek(fd,0,SEEK_SET);
			write(fd,"Delete file failed\n",18);
			write(fd,"Delete file failed\n",18);
			write(fd,"Delete file failed\n",18);
				close(fd);
			}
				rt_module_exec_cmd(so_path,bin_path,cmd_size);
				//LCDClear();
				rt_thread_delay(6000);
			}
		}
		else 
		rt_module_exec_cmd(so_path,0,0);
		rt_free(so_path);
		}
		
	}
		
	rt_thread_delay(100);
	if(eer)return RT_ERROR;
	return RT_EOK;
}
}

void myinit()
{

rt_hw_usb_init();
File_systeminit();
 sys_inf();	
			{
			rt_device_t usb = rt_device_find("usb");
				if(usb)
			rt_device_open(usb,1);		
			} 
}


#define SPIFLASH
//#define nandflash
#ifdef SPIFLASH
	
#include "stm32_spi.h"  		
#include "spi_flash_w25qxx.h"
void rt_hw_spi1_init(void);
struct stm32_spi_bus SPI1_bus;
struct rt_spi_device SPI_FLASH;
struct stm32_spi_cs  SPI_FLASH_CS={GPIOA,GPIO_Pin_3};	
#endif




void rt_hw_spi1_init(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA 
                               , ENABLE);
	      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	      GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	      GPIO_Init(GPIOA,&GPIO_InitStructure);
		    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	      GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
				GPIO_Init(GPIOA,&GPIO_InitStructure);
}

rt_err_t File_systeminit(void)
{
#ifdef RT_USING_DFS
 dfs_init();
#endif

	
#ifdef SPIFLASH
 elm_init();
  rt_hw_spi1_init();
	//rt_hw_spi3_init();
 stm32_spi_register(SPI1,&SPI1_bus,"SPI1");
 rt_spi_bus_attach_device(&SPI_FLASH,"SPI_FLASH_DEV","SPI1",(void*)&SPI_FLASH_CS);	
 w25qxx_init("w25","SPI_FLASH_DEV");
 rt_device_init_all();		
		if (dfs_mount("w25", "/", "elm", 0, 0) == 0)
		{
			rt_kprintf("SPI File System initialized!\n");
		}
		else
		{
		 extern int dfs_mkfs(const char *fs_name, const char *device_name);
    	
      if(dfs_mkfs("elm","w25") == 0)
      {
        if (dfs_mount("w25", "/", "elm", 0, 0) == 0)
        {
          rt_kprintf("File System initialized ok!\n");
        }
      }
      else
      {
        rt_kprintf("File System initialzation failed!\n");
				return RT_ERROR;
      }	
		}
		
	#endif		

#ifdef SD_FLASH
 elm_init();
		if (dfs_mount("SD_FLASH", "/", "elm", 0, 0) == 0)
		{
			rt_kprintf("SPI File System initialized!\n");

		}
		else
		{
		 extern int dfs_mkfs(const char *fs_name, const char *device_name);
    	
      if(dfs_mkfs("elm","SD_FLASH") == 0)
      {
        if (dfs_mount("SD_FLASH", "/", "elm", 0, 0) == 0)
        {
          rt_kprintf("File System initialized ok!\n");
	
        }
      }
      else
      {
        rt_kprintf("File System initialzation failed!\n");
				return RT_ERROR;
      }	
		}
		
#endif	
#ifdef nandflash
#ifdef RT_USING_DFS_UFFS
dfs_uffs_init();
	/* mount nand flash partition 0 as root directory */
	if (dfs_mount("nand0", "/", "uffs", 0, 0) == 0)
	{rt_kprintf("uffs initialized!\n");
}
	else
 	{ 
		rt_kprintf("uffs failed!\n");
		return RT_ERROR;
	}
#endif /* RT_USING_DFS_UFFS */
#endif
	
  return RT_EOK;
}