#ifndef __LINUX_STAT_H__
#define __LINUX_STAT_H__


#include "port/sys/stat.h" //mod by prife

#define S_IRUGO (S_IRUSR|S_IRGRP|S_IROTH)
#define S_IWUGO (S_IWUSR|S_IWGRP|S_IWOTH)
#define S_IXUGO (S_IXUSR|S_IXGRP|S_IXOTH)
#define S_IRWXUGO (S_IRWXU|S_IRWXG|S_IRWXO)

#endif /* __LINUX_STAT_H__ */
