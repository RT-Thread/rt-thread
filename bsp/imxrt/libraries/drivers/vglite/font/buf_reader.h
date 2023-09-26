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

/* Bufferred reader interface */
#ifndef _BUFFERRED_READER_
#define _BUFFERRED_READER_

typedef struct buffered_reader {
    char *data_buf;
    int size;
    int index;
    int is_valid;
} bufferred_reader_t;

#define E_BUF_IO_OUT_OF_MEMORY      -10
#define E_BUF_IO_READ_ERROR         -11
#define E_BUF_INVALID_HANDLE        -12
#define E_BUF_IO_INVALID_PARAMETERS -13

int is_buffered_handle_valid(bufferred_reader_t *fd);
int bufferred_fopen(bufferred_reader_t *fd, char *buf, int size);
int bufferred_ftell(bufferred_reader_t *fd);
int bufferred_fread(
    void *ptr,
    int size,
    int nmemb,
    bufferred_reader_t *fd
);
int bufferred_fseek(
    bufferred_reader_t *fd,
    int offset,
    int direction
);
int bufferred_fclose(bufferred_reader_t *fd);
char *bufferred_fgets(char* buff, int len, bufferred_reader_t *fd);

#endif //!_BUFFERRED_READER_
