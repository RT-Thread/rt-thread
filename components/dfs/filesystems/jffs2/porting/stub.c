#include <linux/kernel.h>
#include "nodelist.h"
#include <linux/pagemap.h>
#include <linux/crc32.h>
#include "compr.h"
//#include <errno.h>
#include <string.h>




extern struct cyg_fstab_entry jffs2_fste;

MTAB_ENTRY(jffs2_mte,
            "/",
            "jffs2",
            NULL,
            0);

#include "flash.h"
extern int file_handle;
extern int FLASH_SIZE;
extern int flash_file_init(void);

extern int jffs2_mount(cyg_fstab_entry * fste, cyg_mtab_entry * mte);


extern int jffs2_open(cyg_mtab_entry * mte, cyg_dir dir, const char *name,
		      int mode, cyg_file * file);
extern int jffs2_fo_read(struct CYG_FILE_TAG *fp, struct CYG_UIO_TAG *uio);

char buffer[1024];
int jffs2_main()
{
    int res;
    cyg_file file;
    struct CYG_UIO_TAG uio_s;
	struct CYG_IOVEC_TAG iovec;
//    res = flash_file_init();
    if (res != 0)
        goto out;

    //mount file system
    res = jffs2_mount(&jffs2_fste, &jffs2_mte);
    if (res < 0)
    {
        printf("jffs2_mount error!\n");
        goto out;
    }
    printf("jffs2 mount ok!\n");


    //read a file or dirs  "src/dfs.c"
    //res = jffs2_open(&jffs2_mte, 0, "dfs_uffs.c", O_RDWR, &file);
    //res = jffs2_open(&jffs2_mte, 0, "SConscript", O_RDWR, &file);
//    res = jffs2_open(&jffs2_mte, 0, "filesystems/devfs/console.c" , O_RDWR, &file);
    if (res != 0)
    {
        printf("jffs2_open file error: %d", res);
        goto out;
    }

    memset(buffer, 0, sizeof(buffer));
    uio_s.uio_iov = &iovec;
    uio_s.uio_iov->iov_base = buffer;
    uio_s.uio_iov->iov_len = 1024;
    uio_s.uio_iovcnt = 1; //must be 1
    //uio_s.uio_offset //not used...
    uio_s.uio_resid = uio_s.uio_iov->iov_len; //seem no use in ecos;
    //uio_s.uio_segflg = UIO_USERSPACE;
    //uio_s.uio_rw = ;

    res = jffs2_fo_read(&file, &uio_s);
    if (res != 0)
    {
        printf("jffs2_fo_read file error: %d", res);
        goto out;
    }
    printf("\n\n=====================================================================\n");
    printf("the uffs/dfs_uffs.c file content is:\n\n");
    printf("%s", buffer);

out:
#if defined  (MSVC)
	printf("\n\npress any key to colose this console...\n");
	getch();
#endif
    return 0;
}
