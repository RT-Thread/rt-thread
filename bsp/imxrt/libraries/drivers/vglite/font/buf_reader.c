/****************************************************************************
*
*    The MIT License (MIT)
*
*    Copyright 2020 NXP
*    All Rights Reserved.
*
*    Permission is hereby granted, free of charge, to any person obtaining
*    a copy of this software and associated documentation files (the
*    'Software'), to deal in the Software without restriction, including
*    without limitation the rights to use, copy, modify, merge, publish,
*    distribute, sub license, and/or sell copies of the Software, and to
*    permit persons to whom the Software is furnished to do so, subject
*    to the following conditions:
*
*    The above copyright notice and this permission notice (including the
*    next paragraph) shall be included in all copies or substantial
*    portions of the Software.
*
*    THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
*    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
*    IN NO EVENT SHALL VIVANTE AND/OR ITS SUPPLIERS BE LIABLE FOR ANY
*    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
*    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
*    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
*****************************************************************************/
#include "buf_reader.h"
#include "stdio.h"
#include "string.h"

#define DBG_TRACE(x) printf x

static int _is_buffered_handle_valid(bufferred_reader_t *fd)
{
    if (fd == NULL)
        return E_BUF_INVALID_HANDLE;
    if ( fd->data_buf == NULL )
        return E_BUF_INVALID_HANDLE;
    if ( fd->size < 0 )
        return E_BUF_INVALID_HANDLE;
    if ( fd->index > fd->size )
        return E_BUF_INVALID_HANDLE;

    return 0;
}

/* Write buffered IO operations */
int bufferred_fopen(bufferred_reader_t *fd, char *buf, int size)
{
    if (fd == NULL)
        return E_BUF_INVALID_HANDLE;

    fd->data_buf = buf;
    fd->size = size;
    fd->index = 0;

    if ( _is_buffered_handle_valid(fd)) {
        return E_BUF_INVALID_HANDLE;
    }

    fd->is_valid = 1;

    return 0;
}

int bufferred_ftell(bufferred_reader_t *fd)
{
    if ( _is_buffered_handle_valid(fd)) {
        return E_BUF_INVALID_HANDLE;
    }

    return fd->index;
}

int bufferred_fread(
    void *ptr,
    int size,
    int nmemb,
    bufferred_reader_t *fd
)
{
    int to_copy = 0;
    char *data_ptr = NULL;
    char *buff = (char *)ptr;
    int byte_to_read = size * nmemb;

    if ( _is_buffered_handle_valid(fd)) {
        return E_BUF_INVALID_HANDLE;
    }

    if ( buff == NULL ) {
        return E_BUF_IO_INVALID_PARAMETERS;
    }

    if ( byte_to_read < 0 ) {
        return E_BUF_IO_INVALID_PARAMETERS;
    }

    to_copy = (fd->size - fd->index);
    data_ptr = fd->data_buf + fd->index;

    if ( to_copy > byte_to_read )
        to_copy = byte_to_read;

    if (to_copy <= 0)
        return -1; //EOF

    memcpy(buff, data_ptr, to_copy);

    fd->index += to_copy;

    return 0;
}

int bufferred_fseek(
    bufferred_reader_t *fd,
    int offset,
    int direction
)
{
    if ( _is_buffered_handle_valid(fd)) {
        return E_BUF_INVALID_HANDLE;
    }

    switch(direction)
    {
        case SEEK_SET:
            fd->index = offset;
            break;
        case SEEK_CUR:
            fd->index += offset;
            break;
        case SEEK_END:
            fd->index = fd->size - offset;
            break;
    }

    /* Clamp current offset */
    if ( fd->index > fd->size ) {
        DBG_TRACE(("WARNING: seeking beyond buffer size\n"));
        fd->index = fd->size;
    }
    if ( fd->index < 0 ) {
        DBG_TRACE(("WARNING: seeking beyond buffer size\n"));
        fd->index = 0;
    }

    return 0;
}

int bufferred_fclose(bufferred_reader_t *fd)
{
    if ( _is_buffered_handle_valid(fd)) {
        return E_BUF_INVALID_HANDLE;
    }

    fd->size = -1;
    fd->is_valid = 0;

    return 0;
}

char *bufferred_fgets(char* buff, int len, bufferred_reader_t *fd)
{
    char *ptr;
    int i, j, valid_bytes;

    if ( buff == NULL ) {
        return NULL;
    }

    if ( len <= 0 ) {
        return NULL;
    }

    if ( _is_buffered_handle_valid(fd)) {
        return NULL;
    }

    /* Check how many bytes are available to read */
    valid_bytes = fd->size - fd->index;
    if ( len > 0 )
        len -=1; /* fgets read one character less than buffer length */
    if ( len > valid_bytes )
        len = valid_bytes;

     if ( valid_bytes <= 0 )
      return NULL;

    ptr = fd->data_buf + fd->index;
    for(i=0; ptr[i] != '\0' && i < len; i++)
    {
        if ( ptr[i] == '\n' )
            break;
        if ( ptr[i] == '\r' )
            break;
        buff[i] = ptr[i];
    }
    buff[i] = '\0';
    j = i;
    /* skip trailing newline from file buffer */
    if ( ptr[i] == '\r' )
        i++;
    if ( ptr[i] == '\n' )
        i++;
    fd->index += i;

    /* Trim trailing spaces from output buffer */
    for (i = j-1 ; i>0; i--) {
        if (buff[i] == ' ')
            buff[i] = '\0';
        else
            break;
    }


    return ptr;

}
