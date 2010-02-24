/*
 * http client for RT-Thread
 */
#include "http.h"

#include <dfs_posix.h>

#include <lwip/sockets.h>
#include <lwip/netdb.h>

const char _http_get[] = "GET %s HTTP/1.0\r\nHost: %s:%d\r\nUser-Agent: RT-Thread HTTP Agent\r\n\r\n";
const char _shoutcast_get[] = "GET %s HTTP/1.0\r\nHost: %s:%d\r\nUser-Agent: RT-Thread HTTP Agent\r\nIcy-MetaData: 1\r\nConnection: close\r\n\r\n";

extern long int strtol(const char *nptr, char **endptr, int base);

//
// This function will parse the Content-Length header line and return the file size
//
int http_parse_content_length(char *mime_buf)
{
	char *line;

	line = strstr(mime_buf, "CONTENT-LENGTH:");
	line += strlen("CONTENT-LENGTH:");

	// Advance past any whitepace characters
	while((*line == ' ') || (*line == '\t')) line++;

	return (int)strtol(line, RT_NULL, 10);
}

//
// This function will parse the initial response header line and return 0 for a "200 OK",
// or return the error code in the event of an error (such as 404 - not found)
//
int http_is_error_header(char *mime_buf)
{
	char *line;
	int i;
	int code;

	line = strstr(mime_buf, "HTTP/1.");
	line += strlen("HTTP/1.");

	// Advance past minor protocol version number
	line++;

	// Advance past any whitespace characters
	while((*line == ' ') || (*line == '\t')) line++;

	// Terminate string after status code
	for(i = 0; ((line[i] != ' ') && (line[i] != '\t')); i++);
	line[i] = '\0';

	code = (int)strtol(line, RT_NULL, 10);
	if( code == 200 )
		return 0;
	else
		return code;
}

int shoutcast_is_error_header(char *mime_buf)
{
	char *line;
	int i;
	int code;

	line = strstr(mime_buf, "ICY");
	line += strlen("ICY");

	// Advance past minor protocol version number
	line++;

	// Advance past any whitespace characters
	while((*line == ' ') || (*line == '\t')) line++;

	// Terminate string after status code
	for(i = 0; ((line[i] != ' ') && (line[i] != '\t')); i++);
	line[i] = '\0';

	code = (int)strtol(line, RT_NULL, 10);
	if( code == 200 )
		return 0;
	else
		return code;
}

//
// When a request has been sent, we can expect mime headers to be
// before the data.  We need to read exactly to the end of the headers
// and no more data.  This readline reads a single char at a time.
//
int http_read_line( int socket, char * buffer, int size )
{
	char * ptr = buffer;
	int count = 0;
	int rc;

	// Keep reading until we fill the buffer.
	while ( count < size )
	{
		rc = recv( socket, ptr, 1, 0 );
		if ( rc <= 0 ) return rc;

		if ((*ptr == '\n'))
		{
			ptr ++;
			count++;
			break;
		}

		// increment after check for cr.  Don't want to count the cr.
		count++;
		ptr++;
	}

	// Terminate string
	*ptr = '\0';

	// return how many bytes read.
	return count;
}

/*
 * resolve server address
 * @param server the server sockaddress
 * @param url the input URL address, for example, http://www.rt-thread.org/index.html
 * @param host_addr the buffer pointer to save server host address
 * @param request the pointer to point the request url, for example, /index.html
 *
 * @return 0 on resolve server address OK, others failed
 */
int http_resolve_address(struct sockaddr_in *server, const char * url, char *host_addr, char** request)
{
	char *ptr;
	char port[6] = "80"; /* default port of 80(HTTP) */
	int i = 0, is_domain;
	struct hostent *hptr;

	/* strip http: */
	ptr = strchr(url, ':');
	if (ptr != NULL)
	{
		url = ptr + 1;
	}

	/* URL must start with double forward slashes. */
	if((url[0] != '/') || (url[1] != '/' )) return -1;

	url += 2; is_domain = 0;
	i = 0;
	/* allow specification of port in URL like http://www.server.net:8080/ */
	while (*url)
	{
		if (*url == '/') break;
		if (*url == ':')
		{
			unsigned char w;
			for (w = 0; w < 5 && url[w] != '/' && url[w] != '\0'; w ++)
				port[w] = url[w + 1];
			
			/* get port ok */
			port[w] = '\0';
			url += w + 1;
			break;
		}

		host_addr[i++] = *url;
		url ++;
	}
	*request = (char*)url;

	/* get host addr ok. */
	host_addr[i] = '\0';

	if (is_domain)
	{
		/* resolve the host name. */
		hptr = gethostbyname(host_addr);
		if(hptr == 0)
		{
			rt_kprintf("HTTP: failed to resolve domain '%s'\n", host_addr);
			return -1;
		}
		memcpy(&server->sin_addr, *hptr->h_addr_list, sizeof(server->sin_addr));
	}
	else
	{
		inet_aton(host_addr, (struct in_addr*)&(server->sin_addr));
	}
	/* set the port */
	server->sin_port = htons((int) strtol(port, NULL, 10));
	server->sin_family = AF_INET;

	return 0;
}

//
// This is the main HTTP client connect work.  Makes the connection
// and handles the protocol and reads the return headers.  Needs
// to leave the stream at the start of the real data.
//
static int http_connect(struct http_session* session,
    struct sockaddr_in * server, char *host_addr, const char *url)
{
	int socket_handle;
	int peer_handle;
	int rc;
	char mimeBuffer[100];

	if((socket_handle = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP )) < 0)
	{
		rt_kprintf( "HTTP: SOCKET FAILED\n" );
		return -1;
	}

	peer_handle = connect( socket_handle, (struct sockaddr *) server, sizeof(*server));
	if ( peer_handle < 0 )
	{
		rt_kprintf( "HTTP: CONNECT FAILED %i\n", peer_handle );
		return -1;
	}

	{
		char *buf;
		rt_uint32_t length;

		buf = rt_malloc (512);
		if (*url)
			length = rt_snprintf(buf, 512, _http_get, url, host_addr, server->sin_port);
		else
			length = rt_snprintf(buf, 512, _http_get, "/", host_addr, server->sin_port);
		
		rc = send(peer_handle, buf, length, 0);
		rt_kprintf("HTTP request:\n%s", buf);
		
		/* release buffer */
		rt_free(buf);
	}

	// We now need to read the header information
	while ( 1 )
	{
		int i;

		// read a line from the header information.
		rc = http_read_line( peer_handle, mimeBuffer, 100 );
		rt_kprintf(">> %s\n", mimeBuffer);

		if ( rc < 0 ) return rc;

		// End of headers is a blank line.  exit.
		if (rc == 0) break;
		if ((rc == 2) && (mimeBuffer[0] == '\r')) break;

		// Convert mimeBuffer to upper case, so we can do string comps
		for(i = 0; i < strlen(mimeBuffer); i++)
			mimeBuffer[i] = toupper(mimeBuffer[i]);

		if(strstr(mimeBuffer, "HTTP/1.")) // First line of header, contains status code. Check for an error code
		{
			rc = http_is_error_header(mimeBuffer);
			if(rc)
			{
				rt_kprintf("HTTP: status code = %d!\n", rc);
				return -rc;
			}
		}

		if(strstr(mimeBuffer, "CONTENT-LENGTH:"))
		{
			session->size = http_parse_content_length(mimeBuffer);
			rt_kprintf("size = %d\n", session->size);
		}
	}

	// We've sent the request, and read the headers.  SockHandle is
	// now at the start of the main data read for a file io read.
	return peer_handle;
}

struct http_session* http_session_open(char* url)
{
	int peer_handle = 0;
	struct sockaddr_in server;
	char *request, host_addr[32];
	struct http_session* session;

    session = (struct http_session*) rt_malloc(sizeof(struct http_session));
	if(session == RT_NULL) return RT_NULL;

	session->size = 0;
	session->position = 0;

	/* Check valid IP address and URL */
	if(http_resolve_address(&server, url, &host_addr[0], &request) != 0)
	{
		rt_free(session);
		return RT_NULL;
	}

	// Now we connect and initiate the transfer by sending a
	// request header to the server, and receiving the response header
	if((peer_handle = http_connect(session, &server, host_addr, request)) < 0)
	{
        rt_kprintf("HTTP: failed to connect to '%s'!\n", host_addr);
		rt_free(session);
		return RT_NULL;
	}

	// http connect returns valid socket.  Save in handle list.
	session->socket = peer_handle;

	/* open successfully */
	return session;
}

rt_size_t http_session_read(struct http_session* session, rt_uint8_t *buffer, rt_size_t length)
{
	int bytesRead = 0;
	int totalRead = 0;
	int left = length;

	// Read until: there is an error, we've read "size" bytes or the remote
	//             side has closed the connection.
	do
	{
		bytesRead = recv(session->socket, buffer + totalRead, left, 0);
		if(bytesRead <= 0) break;

		left -= bytesRead;
		totalRead += bytesRead;
	} while(left);

	return totalRead;
}

rt_off_t http_session_seek(struct http_session* session, rt_off_t offset, int mode)
{
	switch(mode)
	{
	case SEEK_SET:
		session->position = offset;
		break;

	case SEEK_CUR:
		session->position += offset;
		break;

	case SEEK_END:
		session->position = session->size + offset;
		break;
	}

	return session->position;
}

int http_session_close(struct http_session* session)
{
   	lwip_close(session->socket);
	rt_free(session);

	return 0;
}

//
// This is the main HTTP client connect work.  Makes the connection
// and handles the protocol and reads the return headers.  Needs
// to leave the stream at the start of the real data.
//
static int shoutcast_connect(struct shoutcast_session* session,
    struct sockaddr_in* server, char* host_addr, const char* url)
{
	int socket_handle;
	int peer_handle;
	int rc;
	char mimeBuffer[256];

	if((socket_handle = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP )) < 0)
	{
		rt_kprintf( "ICY: SOCKET FAILED\n" );
		return -1;
	}

	peer_handle = connect( socket_handle, (struct sockaddr *) server, sizeof(*server));
	if ( peer_handle < 0 )
	{
		rt_kprintf( "ICY: CONNECT FAILED %i\n", peer_handle );
		return -1;
	}

	{
		char *buf;
		rt_uint32_t length;

		buf = rt_malloc (512);
		if (*url)
			length = rt_snprintf(buf, 512, _shoutcast_get, url, host_addr, server->sin_port);
		else
			length = rt_snprintf(buf, 512, _shoutcast_get, "/", host_addr, server->sin_port);

		rc = send(peer_handle, buf, length, 0);
		rt_kprintf("SHOUTCAST request:\n%s", buf);
		
		/* release buffer */
		rt_free(buf);
	}

	/* read the header information */
	while ( 1 )
	{
		// read a line from the header information.
		rc = http_read_line(peer_handle, mimeBuffer, 100);
		rt_kprintf(">>%s", mimeBuffer);

		if ( rc < 0 ) return rc;

		// End of headers is a blank line.  exit.
		if (rc == 0) break;
		if ((rc == 2) && (mimeBuffer[0] == '\r')) break;

		if(strstr(mimeBuffer, "ICY")) // First line of header, contains status code. Check for an error code
		{
			rc = shoutcast_is_error_header(mimeBuffer);
			if(rc)
			{
				rt_kprintf("ICY: status code = %d!\n", rc);
				return -rc;
			}
		}
		
		if (strstr(mimeBuffer, "HTTP/1."))
		{
			rc = http_is_error_header(mimeBuffer);
			if(rc)
			{
				rt_kprintf("HTTP: status code = %d!\n", rc);
				return -rc;
			}
		}

		if (strstr(mimeBuffer, "icy-name:"))
		{
			/* get name */
			char* name;

			name = mimeBuffer + strlen("icy-name:");
			session->station_name = rt_strdup(name);
			rt_kprintf("station name: %s\n", session->station_name);
		}

		if (strstr(mimeBuffer, "icy-br:"))
		{
			/* get bitrate */
			session->bitrate = strtol(mimeBuffer + strlen("icy-br:"), RT_NULL, 10);
			rt_kprintf("bitrate: %d\n", session->bitrate);
		}

		if (strstr(mimeBuffer, "icy-metaint:"))
		{
			/* get metaint */
			session->metaint = strtol(mimeBuffer + strlen("icy-metaint:"), RT_NULL, 10);
			rt_kprintf("metaint: %d\n", session->metaint);
		}
		
		if (strstr(mimeBuffer, "content-type:"))
		{
			/* check content-type */
			if (strstr(mimeBuffer, "audio/mpeg") == RT_NULL)
			{
				rt_kprintf("ICY content is not audio/mpeg.\n");
				return -1;
			}
		}

		if (strstr(mimeBuffer, "Content-Type:"))
		{
			/* check content-type */
			if (strstr(mimeBuffer, "audio/mpeg") == RT_NULL)
			{
				rt_kprintf("ICY content is not audio/mpeg.\n");
				return -1;
			}
		}
	}

	// We've sent the request, and read the headers.  SockHandle is
	// now at the start of the main data read for a file io read.
	return peer_handle;
}

struct shoutcast_session* shoutcast_session_open(char* url)
{
	int peer_handle = 0;
	struct sockaddr_in server;
	char *request, host_addr[32];
	struct shoutcast_session* session;

    session = (struct shoutcast_session*) rt_malloc(sizeof(struct shoutcast_session));
	if(session == RT_NULL) return RT_NULL;

	session->metaint = 0;
	session->current_meta_chunk = 0;
	session->bitrate = 0;
	session->station_name = RT_NULL;

	/* Check valid IP address and URL */
	if(http_resolve_address(&server, url, &host_addr[0], &request) != 0)
	{
		rt_free(session);
		return RT_NULL;
	}

	// Now we connect and initiate the transfer by sending a
	// request header to the server, and receiving the response header
	if((peer_handle = shoutcast_connect(session, &server, host_addr, request)) < 0)
	{
        rt_kprintf("SHOUTCAST: failed to connect to '%s'!\n", host_addr);
		if (session->station_name != RT_NULL)
			rt_free(session->station_name);
		rt_free(session);
		return RT_NULL;
	}

	// http connect returns valid socket.  Save in handle list.
	session->socket = peer_handle;

	/* open successfully */
	return session;
}

rt_size_t shoutcast_session_read(struct shoutcast_session* session, rt_uint8_t *buffer, rt_size_t length)
{
	int bytesRead = 0;
	int totalRead = 0;
	int left = length;
	static rt_uint32_t first_meta_size = 0;

	// Read until: there is an error, we've read "size" bytes or the remote
	//             side has closed the connection.
	do
	{
		bytesRead = recv(session->socket, buffer + totalRead, left, 0);
		if(bytesRead <= 0) 
		{
			rt_kprintf("no data on recv, len %d,err %d\n", bytesRead, 
				lwip_get_error(session->socket));
			break;
		}

		left -= bytesRead;
		totalRead += bytesRead;
	} while(left);

	/* handle meta */
	if (first_meta_size > 0)
	{
		/* skip meta data */
		memmove(&buffer[0], &buffer[first_meta_size], totalRead - first_meta_size);

		// rt_kprintf("remove meta: len %d\n", first_meta_size);

		totalRead = totalRead - first_meta_size;
		first_meta_size = 0;
		session->current_meta_chunk = totalRead;
	}
	else
	{
		if (session->current_meta_chunk + totalRead == session->metaint)
		{
			rt_uint8_t meta_data;
			recv(session->socket, &meta_data, 1, 0);
		
			/* remove meta data in next packet */
			first_meta_size = meta_data * 16;
			session->current_meta_chunk = 0;

			// rt_kprintf("get meta: len %d\n", first_meta_size);
		}
		else if (session->current_meta_chunk + totalRead > session->metaint)
		{
			int meta_length, next_chunk_length;

			// rt_kprintf("c: %d, total: %d, m: %d\n", session->current_meta_chunk, totalRead, session->metaint);

			/* get the length of meta data */
			meta_length = buffer[session->metaint - session->current_meta_chunk] * 16;
			next_chunk_length = totalRead - (session->metaint - session->current_meta_chunk) - 
				(meta_length + 1);

			// rt_kprintf("l: %d, n: %d\n", meta_length, next_chunk_length);

			/* skip meta data */
			memmove(&buffer[session->metaint - session->current_meta_chunk], 
				&buffer[session->metaint - session->current_meta_chunk + meta_length + 1],
				next_chunk_length);

			/* set new current meta chunk */
			session->current_meta_chunk = next_chunk_length;
			totalRead = totalRead - (meta_length + 1);
		}
		else 
		{
			session->current_meta_chunk += totalRead;
		}
	}

	return totalRead;
}

rt_off_t shoutcast_session_seek(struct shoutcast_session* session, rt_off_t offset, int mode)
{
	/* not support seek yet */
	return 0;
}

int shoutcast_session_close(struct shoutcast_session* session)
{
   	lwip_close(session->socket);
	if (session->station_name != RT_NULL)
		rt_free(session->station_name);
	rt_free(session);

	return 0;
}

#include <finsh.h>
void http_test(char* url)
{
	struct http_session* session;
	char buffer[80];
	rt_size_t length;

	session = http_session_open(url);
	if (session == RT_NULL)
	{
		rt_kprintf("open http session failed\n");
		return;
	}

	do
	{
		rt_memset(buffer, 0, sizeof(buffer));
		length = http_session_read(session, (rt_uint8_t*)buffer, sizeof(buffer));

		rt_kprintf(buffer);rt_kprintf("\n");
	} while (length > 0);

	http_session_close(session);
}
FINSH_FUNCTION_EXPORT(http_test, http client test);

void shoutcast_test(char* url)
{
	struct shoutcast_session* session;

	session = shoutcast_session_open(url);
	if (session == RT_NULL)
	{
		rt_kprintf("open shoutcast session failed\n");
		return;
	}

	shoutcast_session_close(session);
}
FINSH_FUNCTION_EXPORT(shoutcast_test, shoutcast client test);

