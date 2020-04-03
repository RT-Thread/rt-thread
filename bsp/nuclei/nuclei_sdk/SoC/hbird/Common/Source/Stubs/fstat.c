#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include "stub.h"

int _fstat(int fd, struct stat* st)
{
  return _stub(EBADF);
}
