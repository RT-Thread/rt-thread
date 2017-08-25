#include "../library/ndsvfs/include/ndsvfs.h"

struct dirent {

	int		d_cnt;
	int		d_ino;
	int		d_off;
	char		d_name[256];
};

struct dir {

	int		d_cnt;
	int		d_off;
	NDSVFS_FILE	*d_file;
	struct dirent	*d_dirent;
	NDSVFS_DENTRY	*vde_list;
	NDSVFS_DENTRY	*vde_head;
};

