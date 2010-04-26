#include <reent.h>
#include <sys/errno.h>

int _fork_r (struct _reent *r)
{
	/* return "not supported" */
	r->_errno = ENOTSUP;
	return -1;
}

_ssize_t
_read_r (struct _reent *r, int fd, void *buf, size_t nbytes)
{
	_ssize_t rc;

	rc = -1;

	/* return "not supported" */
	r->_errno = ENOTSUP;
	return rc;
}

_ssize_t
_write_r (struct _reent *r, int fd, const void *buf, size_t nbytes)
{
	_ssize_t rc;

	rc = -1;

	/* return "not supported" */
	r->_errno = ENOTSUP;
	return rc;
}

int
_close_r (struct _reent *r, int fd)
{
	_ssize_t rc;

	rc = -1;

	/* return "not supported" */
	r->_errno = ENOTSUP;
	return rc;
}

_off_t
_lseek_r (struct _reent *r, int fd,  _off_t offset, int whence)
{
	_ssize_t rc;

	rc = -1;

	/* return "not supported" */
	r->_errno = ENOTSUP;
	return rc;
}
