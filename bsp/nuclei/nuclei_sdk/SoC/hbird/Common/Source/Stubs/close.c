#include <errno.h>
#include "stub.h"

int _close(int fd)
{
    return _stub(EBADF);
}
