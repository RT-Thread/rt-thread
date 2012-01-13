#include <stdio.h>
//#include <io.h>
//#include <fcntl.h>
//#include <sys/stat.h>
#include "flash.h"
int file_handle;
int FLASH_SIZE;
int flash_file_init(void)
{
//	file_handle = open(FILE_NAME, O_RDWR |O_BINARY| O_CREAT, S_IREAD | S_IWRITE);
//	if(file_handle >= 0) {
//		printf("read file ok\n");
//	} else {
//		printf("read file error\n");
//        return -1;
//	}
//    FLASH_SIZE = lseek(file_handle, 0, SEEK_END) ;// / BLOCK_SIZE * BLOCK_SIZE; /*È¡ÕûÊý*/
//    printf("the size of jffs bin file is %d", FLASH_SIZE);
    return 0;
}
