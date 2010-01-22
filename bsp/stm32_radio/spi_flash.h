#ifndef SPI_FLASH_H_INCLUDED
#define SPI_FLASH_H_INCLUDED

/*
user for AT45DB161.
copy form : http://www.ourdev.cn/bbs/bbs_content.jsp?bbs_sn=737106
thanks to gxlujd.
*/

#define AT45DB_BUFFER_1_WRITE                 0x84	/* 写入第一缓冲区 */
#define AT45DB_BUFFER_2_WRITE                 0x87	/* 写入第二缓冲区 */
#define AT45DB_BUFFER_1_READ                  0xD4	/* 读取第一缓冲区 */
#define AT45DB_BUFFER_2_READ                  0xD6	/* 读取第二缓冲区 */
#define AT45DB_B1_TO_MM_PAGE_PROG_WITH_ERASE  0x83	/* 将第一缓冲区的数据写入主存储器（擦除模式）*/
#define AT45DB_B2_TO_MM_PAGE_PROG_WITH_ERASE  0x86	/* 将第二缓冲区的数据写入主存储器（擦除模式）*/
#define AT45DB_MM_PAGE_TO_B1_XFER             0x53	/* 将主存储器的指定页数据加载到第一缓冲区    */
#define AT45DB_MM_PAGE_TO_B2_XFER             0x55	/* 将主存储器的指定页数据加载到第二缓冲区    */
#define AT45DB_PAGE_ERASE                     0x81	/* 页删除（每页512/528字节） */
#define AT45DB_SECTOR_ERASE                   0x7C	/* 扇区擦除（每扇区128K字节）*/
#define AT45DB_READ_STATE_REGISTER            0xD7	/* 读取状态寄存器 */


extern void rt_hw_spi_flash_init(void);

#endif /* SPI_FLASH_H_INCLUDED */
