#include <reent.h>

int _fork_r (struct _reent *ptr)
{
	/* return "not supported" */
	ptr->errno = ENOTSUP;
	return -1;
}
