/* 
 * nand flash read
 */

#define NFCONF				(*(volatile unsigned int  *)0x4e000000)
#define rNFCONT				(*(volatile unsigned int  *)0x4E000004)
#define NFCMD				(*(volatile unsigned int  *)0x4e000008)
#define NFADDR				(*(volatile unsigned char *)0x4e00000C)
#define NFDATA				(*(volatile unsigned char *)0x4e000010)
#define NFSTAT				(*(volatile unsigned char *)0x4e000020)

#define BUSY				1

#define NAND_SECTOR_SIZE	512
#define NAND_BLOCK_MASK		(NAND_SECTOR_SIZE - 1)

void wait_idle(void) {
	int i;

	while (!(NFSTAT & BUSY)) {
		for(i=0; i<10; i++) {
			;
		}
	}
}

/* low level nand read function */
int nand_read_ll(unsigned char *buf, unsigned long start_addr, int size)
{
	int i, j;

	/*
	 * K9F5608UOC asks for 512B per page, and read/write operation must
	 * do with page. Therefore, first judge whether start_addr and size
	 * are valid.
	 */ 
	if ((start_addr & NAND_BLOCK_MASK) || (size & NAND_BLOCK_MASK)) {
		return -1;	/* invalid alignment */
	}

	/* chip Enable */
	NFCONF &= ~0x800;
	for (i=0; i<10; i++) {
		;
	}

	for (i=start_addr; i < (start_addr + size); i+=NAND_SECTOR_SIZE) {
		NFCMD = 0;

		/* Write Address */
		NFADDR = i & 0xff;
		NFADDR = (i >> 9) & 0xff;
		NFADDR = (i >> 17) & 0xff;
		NFADDR = (i >> 25) & 0xff;

		wait_idle();

 		for(j=0; j < NAND_SECTOR_SIZE; j++) {
			*buf++ = (NFDATA & 0xff);
		}
	}

	/* chip Disable */
	NFCONF |= 0x800;	/* chip disable */

	return 0;
}
