
#include <rtthread.h>

#if defined(RT_USING_FINSH) && defined(DFS_USING_POSIX)

#include <finsh.h>
#include "msh.h"
#include <dfs_file.h>
#include <unistd.h>
#include <fcntl.h>
#ifdef RT_USING_DFS_V2
#include <dfs_mnt.h>
#endif

#ifdef RT_USING_SMART
#include "lwp.h"
#endif /* RT_USING_SMART */

void cp_big_file(int argc, char **argv)
{
    void copy(const char *src, const char *dst);

    copy("test_file.txt", "test_dir");

    return 0;
}
MSH_CMD_EXPORT(cp_big_file, cp_big_file);
#endif