#ifndef __HTTP_H__
#define __HTTP_H__

#include <rtthread.h>

struct http_session
{
    char* host;
    int   port;

    char* user_agent;
	int   socket;

    /* size of http file */
    rt_size_t size;
    rt_off_t  position;
};

struct http_session* http_session_open(char* url);
rt_size_t http_session_read(struct http_session* session, rt_uint8_t *buffer, rt_size_t length);
rt_off_t http_session_seek(struct http_session* session, rt_off_t offset, int mode);
int http_session_close(struct http_session* session);

#endif
