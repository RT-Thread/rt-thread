#include "xz.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static struct xz_dec *s;

int xz_uncompress_init(struct xz_buf *stream, uint8_t *sbuf, uint8_t *dbuf)
{
    xz_crc32_init();

    /*
     * Support up to 32 KiB dictionary. The actually needed memory
     * is allocated once the headers have been parsed.
     */
    s = xz_dec_init(XZ_DYNALLOC, 1 << 15);
    if (s == NULL) {
            return 1;
    }

    stream->in = sbuf;
    stream->in_pos = 0;
    stream->in_size = 0;
    stream->out = dbuf;
    stream->out_pos = 0;
    stream->out_size = 0;

	return 0;
}

int xz_uncompress_stream(struct xz_buf *stream, uint8_t *sbuf, uint32_t slen,
		uint8_t *dbuf, uint32_t dlen, uint32_t *decomp_len)
{
	int status;
	*decomp_len = 0;

	if (stream->in_pos == stream->in_size) {
		stream->in_size = slen;
	        stream->in_pos = 0;
	}

	if (stream->out_pos == stream->out_size) {
	        stream->out_size = dlen;
		stream->out_pos = 0;
	}

	status = xz_dec_run(s, stream);

	if ((status == XZ_STREAM_END) || (stream->out_pos == stream->out_size))
		*decomp_len = stream->out_pos;

	return status;
}

void xz_uncompress_end()
{
	xz_dec_end(s);
}
