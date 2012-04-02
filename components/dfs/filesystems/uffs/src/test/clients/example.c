/*
 * This is a APT test client example
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uffs/uffs_fd.h"
#include "api_test.h"


int main(int argc, char *argv[])
{
	int version;
	int fd;
	char buf[128];

	api_client_init("192.168.0.103");

	version = uffs_version();
	printf("Version: %08X\n", version);

	fd = uffs_open("/test.txt", UO_RDWR|UO_CREATE);
	if (fd < 0) {
		printf("Can't create /test.txt\n");
		return -1;
	}
	
	sprintf(buf, "Hello, this is test\n");
	if (uffs_write(fd, buf, strlen(buf)) < 0) {
		printf("call uffs_write failed\n");
	}
	else {
		if (uffs_seek(fd, 7, USEEK_SET) != 7) {
			printf("call uffs_seek failed\n");
		}
		else {
			if (uffs_read(fd, buf, 4) != 4) {
				printf("call uffs_read failed\n");
			}
			else {
				if (memcmp(buf, "this", 4) != 0) {
					printf("uffs_read content not matched\n");
				}
				else {
					printf("everything is ok.\n");
				}
			}
		}
	}

	if (uffs_close(fd) < 0) {
		printf("uffs_close failed.\n");
	}

	return 0;
}

