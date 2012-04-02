/*
 * This is a APT test client example
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "uffs/uffs_fd.h"
#include "api_test.h"


int main(int argc, char *argv[])
{
	int interval = 1000;

	if (argc > 2) {
		interval = atoi(argv[2]);
	}

	printf("Host: %s, Interval: %d\n", argv[1], interval);

	if (api_client_init(argv[1]) == 0) {
		while(1) {
			uffs_flush_all("/");
			usleep(interval * 1000);
		}
	}
	else {
		printf("init failed.\n");
	}

	return 0;
}

