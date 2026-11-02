# AF_UNIX local sockets

The AF_UNIX component provides pathname-based local IPC through the existing
SAL and POSIX socket APIs. It supports `SOCK_DGRAM`, `SOCK_STREAM`, and
`socketpair()` for both socket types.

## Configuration

Enable `RT_USING_AF_UNIX`. The component requires `RT_USING_SAL`,
`SAL_USING_POSIX`, and `RT_USING_DFS_V2`.

- `AF_UNIX_DGRAM_MAX_SIZE` bounds one datagram.
- `AF_UNIX_DGRAM_QUEUE_LEN` bounds queued datagrams per socket.
- `AF_UNIX_STREAM_BUFFER_SIZE` bounds each stream receive buffer.
- `AF_UNIX_LISTEN_BACKLOG_MAX` caps the stream accept queue.
- `AF_UNIX_RIGHTS_MAX` bounds the file descriptors in one `SCM_RIGHTS` send.
- `RT_AF_UNIX_USING_TESTCASES` builds the component utest suite.

## Pathname behavior

`bind()` creates an `S_IFSOCK` node through DFSv2. The mounted filesystem must
support special nodes through `create_vnode()`; tmpfs and devtmpfs support
socket nodes directly. Closing a bound socket leaves its pathname in the
filesystem. Applications should call `unlink()` before rebinding, which
matches common Unix daemon behavior.

Removing a pathname prevents new lookups. Existing stream connections and
connected datagram endpoints continue to reference their established peers.

## Descriptor passing

`sendmsg()` and `recvmsg()` support one or more file descriptors in
`SOL_SOCKET`/`SCM_RIGHTS` control messages. The queued reference remains valid
after the sender closes its descriptor. On receive, each reference is installed
as a new descriptor in the receiving process and retains the same open file
description, including its shared file position. Passing an AF_UNIX socket
descriptor is not supported and returns `EOPNOTSUPP`.

For datagram sockets, the control message is atomic with its datagram. For
stream sockets, it is associated with the first byte written by `sendmsg()` and
is delivered when a receive consumes that byte. A receive without a control
buffer discards associated descriptors and reports `MSG_CTRUNC`; `MSG_PEEK`
does not install or consume descriptors. At least one payload byte is required
when sending `SCM_RIGHTS`.

Only `SCM_RIGHTS` ancillary data is supported. Credentials and other control
message types return `EOPNOTSUPP`.

## Supported operations

The component implements bind, connect, listen, accept, send/receive,
sendto/recvfrom, sendmsg/recvmsg with descriptor passing, shutdown, socket
options, nonblocking I/O, timeouts, poll/select readiness, address queries, and
socketpair.

Linux abstract namespace addresses and credential ancillary data are not
supported. The component requires DFSv2.
