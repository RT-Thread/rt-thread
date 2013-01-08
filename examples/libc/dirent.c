/*
 * dirent.c
 *
 *  Created on: 2010-11-17
 *      Author: bernard
 */
#include <stdio.h>
#include <stdlib.h>
#include <finsh.h>

#include <dirent.h>
int libc_dirent()
{
	DIR * dirp;
	long int save3 = 0;
	long int cur;
	int i = 0;
	int result = 0;
	struct dirent *dp;

	dirp = opendir("/");
	for (dp = readdir(dirp); dp != NULL; dp = readdir(dirp))
	{
		/* save position 3 (after fourth entry) */
		if (i++ == 3)
			save3 = telldir(dirp);

		printf("%s\n", dp->d_name);

		/* stop at 400 (just to make sure dirp->__offset and dirp->__size are
		 scrambled */
		if (i == 400)
			break;
	}

	printf("going back past 4-th entry...\n");

	/* go back to saved entry */
	seekdir(dirp, save3);

	/* Check whether telldir equals to save3 now.  */
	cur = telldir(dirp);
	if (cur != save3)
	{
		printf("seekdir (d, %ld); telldir (d) == %ld\n", save3, cur);
		result = 1;
	}

	/* print remaining files (3-last) */
	for (dp = readdir(dirp); dp != NULL; dp = readdir(dirp))
		printf("%s\n", dp->d_name);

	closedir(dirp);
	return result;
}
FINSH_FUNCTION_EXPORT(libc_dirent, dirent test for libc);
