#ifndef	__K9F2G08_H__
#define __K9F2G08_H__

#include <rtdef.h>
#include <s3c24x0.h>
#include <nand.h>

void K9F2G08_Program(u32 blockIndex, u32 srcAddress, u32 fileSize);

//*************** H/W dependent functions ***************
void K9F2G08_ReadChipID(u8* buf, UBOOL all);
	
int K9F2G08_Check_badblk(u32 block);
int K9F2G08_EraseBlock	(u32 block);
int K9F2G08_Mark_badblk (u32 block);
int K9F2G08_ReadPage    (u32 block, u32 page, u8 *buffer, int len, u8 *ecc);
int K9F2G08_WritePage   (u32 block, u32 page, const u8 *buffer, int len, const u8 *ecc);
int K9F2G08_ReadTags	(u32 block, u32 page, u8 *spare, int ofs, int len);
int K9F2G08_WriteTags   (u32 block, u32 page, const u8 *spare, int ofs, int len);

void K9F2G08_Reset(void);

void K9F2G08_Init(void);


#endif


