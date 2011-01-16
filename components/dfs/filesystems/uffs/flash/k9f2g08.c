/**
 * 用户要自己实现这个文件中的接口函数,不一样的芯片会有不同的访问命令
 * 这个例程文件是关于Samsung k9f2g08芯片的,属于大页nandflash
 */
#include <nand.h>
#include "s3c24x0.h" 

#include <k9f2g08.h>

#define nand_write_cmd(cmd)		(NFCMD  = (cmd))
#define nand_write_addr(addr)	(NFADDR = (addr))	
#define nand_cs_en()			(NFCONT &= ~(1<<1))
#define nand_cs_ds()			(NFCONT |=  (1<<1))
#define nand_Init_ECC()			(NFCONT |=  (1<<4))
#define nand_read() 			(NFDATA8)
#define nand_write(data) 		(NFDATA8 = (data))

#define nand_wait()    	{while(!(NFSTAT&(1<<0)));} //wait tWB and check F_RNB pin. 

//NAND Flash Command.support K9F2G08
#define K9F2G08_CMD_READ0			0x00	//  Read0
//#define K9F2G08_CMD_READ1			1		//  Read1,K9F2G08 don't support the command.
#define K9F2G08_CMD_RANDOM_DATA_OUT	0x05	//  Random data output
#define K9F2G08_CMD_PAGEPROG		0x10	//  Write phase 2
#define K9F2G08_CMD_READ30			0x30	//  Read30
#define K9F2G08_CMD_READ35			0x35	//  Read35
//#define K9F2G08_CMD_READOOB			0x50	//  Read oob
#define K9F2G08_CMD_ERASE1			0x60	//  Erase phase 1
#define K9F2G08_CMD_STATUS			0x70	//  Status read
#define K9F2G08_CMD_READ_EDC		0x7b	//  Read EDC Status
#define K9F2G08_CMD_SEQIN			0x80	//  Write phase 1
#define K9F2G08_CMD_RANDOM_DATA_IN	0x85	//  Random data input Copy-Back Program(0x85,0x10)
#define K9F2G08_CMD_READID			0x90	//  ReadID,all-purpose command
#define K9F2G08_CMD_ERASE2			0xd0	//  Erase phase 2
#define K9F2G08_CMD_RESET			0xff	//  Reset

#define BAD_CHECK	(0)
#define ECC_CHECK	(0)


//*************************************************
//**           H/W dependent functions           **
//************************************************* 

// HCLK=100Mhz
#define TACLS		1  //1clk(0ns) 
#define TWRPH0		4  //3clk(25ns)
#define TWRPH1		0  //1clk(10ns)  //TACLS+TWRPH0+TWRPH1>=50ns

int read_nand_stats(void)	// R/B 未接好?
{
	u8 stat;

	nand_write_cmd(K9F2G08_CMD_STATUS);//0x70

	stat = nand_read();//读出返回的数据

	if(stat&1) return 1; // I/O0=1失败
	else return 0; 		 // I/O0=0成功
}

//擦除一个块
//返回0,successful
//返回1,error
int K9F2G08_EraseBlock(u32 block)
{
	int stat;
	u32 _page = block*PAGES_PER_BLOCK;
    
    nand_cs_en();
    
    nand_write_cmd(K9F2G08_CMD_ERASE1);   // Erase one block 1st command

    nand_write_addr(_page&0xff);	    // Page number=0
    nand_write_addr((_page>>8)&0xff);   
    nand_write_addr((_page>>16)&0xff);

    nand_write_cmd(K9F2G08_CMD_ERASE2);   // Erase one blcok 2nd command
    
	nand_wait();    // Wait tBERS max 3ms.

    stat = read_nand_stats();
	nand_cs_ds();
	return stat;
}

//return 1 if it's a bad block, 0 if it's good.
int K9F2G08_Check_badblk(u32 block)	//0:bad,1:good
{
    u8 data;
    u32 _page;//块的首页地址
    
    _page = block*PAGES_PER_BLOCK;	// For 2'nd cycle I/O[7:5] 
    
    nand_cs_en();
	    
    nand_write_cmd(K9F2G08_CMD_READ0);		// Spare array read command
    nand_write_addr(PAGE_DATA_SIZE&0xff);		// Read the mark of bad block in spare array(M addr=5)
	nand_write_addr((PAGE_DATA_SIZE>>8)&0xff); 
    nand_write_addr(_page&0xff);	// The mark of bad block is in 0 page
    nand_write_addr((_page>>8)&0xff);   // For block number A[24:17]
    nand_write_addr((_page>>16)&0xff);  // For block number A[25]
	nand_write_cmd(K9F2G08_CMD_READ30);

    nand_wait();	// Wait tR(max 12us)
    
    data=nand_read();
    nand_cs_ds();    
    if(data==0x00)
    	return 1;//坏块
    else
    	return 0;//好块
}

//return 0 if ok, 1:fail
int K9F2G08_Mark_badblk(u32 block)
{
	u8 stat;
    u32 _page = block*PAGES_PER_BLOCK; 
    
    nand_cs_en(); 

    nand_write_cmd(K9F2G08_CMD_SEQIN);   	// Write 1st command
    
    nand_write_addr(PAGE_DATA_SIZE & 0xff);		    // The mark of bad block
	nand_write_addr((PAGE_DATA_SIZE>>8)&0xff);
    nand_write_addr(_page&0xff);	    // marked 5th spare array 
    nand_write_addr((_page>>8)&0xff);   // in the 1st page.
    nand_write_addr((_page>>16)&0xff);  //
    
    nand_write(0x00);	//坏块标记

    nand_write_cmd(K9F2G08_CMD_PAGEPROG);   // Write 2nd command

    nand_wait();      // Wait tPROG(200~500us)
    stat = read_nand_stats();//查询是否成功
	nand_cs_ds();

    return stat;
}


int K9F2G08_ReadPage(u32 block, u32 page, u8 *buffer, int len, u8 *ecc)
{
    int i;
    u32 _page = block*PAGES_PER_BLOCK + page;
    
//    NF_RSTECC();    // Initialize ECC
    
    nand_cs_en(); 
	   
    nand_write_cmd(K9F2G08_CMD_READ0);   // Read command
    nand_write_addr(0x00);	// Column = 0
	nand_write_addr(0x00);
    nand_write_addr(_page&0xff);	    //
    nand_write_addr((_page>>8)&0xff);   // Block & Page num.
    nand_write_addr((_page>>16)&0xff);  //

	nand_write_cmd(K9F2G08_CMD_READ30);
    
    nand_wait();    // Wait tR(max 12us)
    for(i=0;i<len;i++)
    {
    	buffer[i] = nand_read();	// Read one page
    }

    nand_cs_ds();    
   	
	return 1;
}

int K9F2G08_ReadTags(u32 block, u32 page, u8 *spare, int ofs, int len)
{
    int i;

	u32 _page = block*PAGES_PER_BLOCK + page;

//    NF_RSTECC();    // Initialize ECC
    
    nand_cs_en(); 
	   
    nand_write_cmd(K9F2G08_CMD_READ0);   // Read command
    nand_write_addr((PAGE_DATA_SIZE+ofs)&0xff);	// Column = 0
	nand_write_addr(((PAGE_DATA_SIZE+ofs)>>8)&0xff);
    nand_write_addr(_page&0xff);	    //
    nand_write_addr((_page>>8)&0xff);   // Block & Page num.
    nand_write_addr((_page>>16)&0xff);  //

	nand_write_cmd(K9F2G08_CMD_READ30);
    
    nand_wait();    // Wait tR(max 12us)
    for(i=0;i<len;i++)
    {
    	spare[i] = nand_read();	// Read one page
    }

    nand_cs_ds();    
   	
	return 1;
}

//写一页数据
//返回0,successful
//返回1,error
int K9F2G08_WritePage(u32 block, u32 page, const u8 *buffer, int len, const u8 *ecc)
{
    int i,stat;

	u32 _page = block*PAGES_PER_BLOCK + page;

    //nand_Init_ECC();    // Initialize ECC
    
    nand_cs_en(); 

    nand_write_cmd(K9F2G08_CMD_SEQIN);   //0x80 Write 1st command
	for(i=0;i<10;i++); 
    nand_write_addr(0x00);			    // Column 0
	nand_write_addr(0x00);
    nand_write_addr(_page&0xff);	    //
    nand_write_addr((_page>>8)&0xff);   // Block & page num.
    nand_write_addr((_page>>16)&0xff);  //

    for(i=0;i<len;i++)
    {
		nand_write(*buffer++);	// Write one page to NFM from buffer
    }  
    nand_write_cmd(K9F2G08_CMD_PAGEPROG);   //0x10 Write 2nd command

    nand_wait();    //wait tPROG 200~500us;
 
	stat = read_nand_stats();
    nand_cs_ds();

	return stat;
}

int K9F2G08_WriteTags(u32 block, u32 page, const u8 *spare, int ofs, int len)
{
    int i,stat;
	u32 _page = block*PAGES_PER_BLOCK + page;

    //nand_Init_ECC();    // Initialize ECC
    
    nand_cs_en(); 

    nand_write_cmd(K9F2G08_CMD_SEQIN);   //0x80 Write 1st command
	for(i=0;i<10;i++); 
    nand_write_addr((PAGE_DATA_SIZE+ofs)&0xff);			    // Column 0
	nand_write_addr(((PAGE_DATA_SIZE+ofs)>>8)&0xff);
    nand_write_addr(_page&0xff);	    //
    nand_write_addr((_page>>8)&0xff);   // Block & page num.
    nand_write_addr((_page>>16)&0xff);  //

    for(i=0;i<len;i++)
    {
		nand_write(*spare++);	// Write one page to NFM from buffer
    }   

    nand_write_cmd(K9F2G08_CMD_PAGEPROG);   //0x10 Write 2nd command

    nand_wait();    //wait tPROG 200~500us;
 
	stat = read_nand_stats();
    if(!stat) // Page write error
    {	
    	nand_cs_ds();
		return 0;
    }
    else 
    {
    	nand_cs_ds();
		return 1;
    }
}

//find frist shift bit
//rt_inline int generic_ffs(int x)
//{
//	int r = 1;
//
//	if(!x)
//		return 0;
//
//	if(!(x & 0xffff)) {x >>= 16;r += 16;}
//	if(!(x & 0xff))   {x >>= 8;r += 8;}
//	if(!(x & 0xf))    {x >>= 4;r += 4;}
//	if(!(x & 3))      {x >>= 2;r += 2;}
//	if(!(x & 1))      {x >>= 1;r += 1;}
//
//	return r;
//}

/* when all is true,read all byte */
void K9F2G08_ReadChipID(u8* buf, UBOOL all)
{
	nand_cs_en();    

	nand_write_cmd(K9F2G08_CMD_READID);	//0x90
	nand_write_addr(K9F2G08_CMD_READ0);

	buf[0] = nand_read();//制造商ID
	buf[1] = nand_read();//芯片ID
	if(all)
	{
		buf[2] = nand_read();
		buf[3] = nand_read();
		//buf[4] = nand_read();	//有的芯片没有第5个字节
	}

	nand_cs_ds();
}

void K9F2G08_Init(void)
{
    NFCONF = (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4)|(0<<0);
	NFCONT = (0<<13)|(0<<12)|(0<<10)|(0<<9)|(0<<8)|(1<<6)|(1<<5)|(1<<4)|(1<<1)|(1<<0);
	NFSTAT = 0;	
    // 1  1    1     1,   1      xxx,  r xxx,   r xxx        
    // En 512B 4step ECCR nFCE=H tACLS   tWRPH0   tWRPH1
}

void K9F2G08_Reset(void)
{
    nand_cs_en();

    nand_write_cmd(0xFF);	//reset command

    nand_wait();      //wait 200~500us;
    nand_cs_ds();

	K9F2G08_Init();
}

#if (0)
int K9F2G08_ReadChunk(u32 chunk, u8 *data, u8 *tags)
{
    int i;

    nand_cs_en(); 
	   
    nand_write_cmd(K9F2G08_CMD_READ0);   // Read command
	nand_write_addr(0x00);
	nand_write_addr(0x00);
    nand_write_addr(chunk & 0xff);	    //
    nand_write_addr((chunk >> 8) & 0xff);   // Block & Page num.
    nand_write_addr((chunk >> 16) & 0xff);  //
	//nand_Init_ECC();
	nand_write_cmd(K9F2G08_CMD_READ30);   // Read command

    nand_wait();    // Wait tR(max 12us)

    for(i = 0; i < PAGE_DATA_SIZE; i++)
	{	
    	data[i] = nand_read();	// Read one page
	}
    for(i = 0; i < PAGE_SPARE_SIZE; i++)
	{	
    	tags[i] = nand_read();	// Read spare array
    }

    nand_cs_ds();    

	return 1;
}
#endif

