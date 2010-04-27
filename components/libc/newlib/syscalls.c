#include <reent.h>
#include <sys/errno.h>
#include <rtthread.h>

int
_fork_r (struct _reent *r)
{
	/* return "not supported" */
	r->_errno = ENOTSUP;
	return -1;
}

/*
 * I/O routine stub
 */
int
_isatty_r(struct _reent *r, int fd)
{
	_ssize_t rc;

	rc = -1;
	/* return "not supported" */
	r->_errno = ENOTSUP;

	return rc;
}

int
_open_r(struct _reent *r, const char *file, int flags, int mode)
{
	int rc;

	rc = open(file, flags, mode);
	return rc;
}

_ssize_t
_read_r (struct _reent *r, int fd, void *buf, size_t nbytes)
{
	_ssize_t rc;

	rc = read(fd, buf, nbytes);
	return rc;
}

_ssize_t
_write_r (struct _reent *r, int fd, const void *buf, size_t nbytes)
{
	_ssize_t rc;

	rc = write(fd, buf, nbytes);
	return rc;
}

int
_close_r (struct _reent *r, int fd)
{
	return close(fd);
}

_off_t
_lseek_r (struct _reent *r, int fd,  _off_t offset, int whence)
{
	_off_t rc;

	rc = lseek(fd, offset, whence);
	return rc;
}

int _fstat_r (struct _reent *r, int fd, struct stat *pstat)
{
	/* return "not supported" */
	r->_errno = ENOTSUP;
	return -1;
}

/*
 * memory routine stub
 */
void *
_malloc_r (struct _reent *ptr, size_t size)
{
	return (void*)rt_malloc (size);
}

void *
_realloc_r (struct _reent *ptr, void *old, size_t newlen)
{
	return (void*)rt_realloc (old, newlen);
}

void *_calloc_r (struct _reent *ptr, size_t size, size_t len)
{
  return (void*)rt_calloc (size, len);
}

void 
_free_r (struct _reent *ptr, void *addr)
{
	rt_free (addr);
}
