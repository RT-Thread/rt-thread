/*
 * http client for RT-Thread
 */
#include <rtthread.h>
#include <dfs_posix.h>

#include <lwip/sockets.h>
#include <lwip/netdb.h>

const char _http_get[] = "GET ";
const char _http_host[] = "Host: ";
const char _http_getend[] = " HTTP/1.0\r\n";
const char _http_user_agent[] = "User-Agent: RT-Thread HTTP Agent\r\n";
const char _http_endheader[] = "\r\n";

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

		if ( (*ptr == '\n') ) break;

		// increment after check for cr.  Don't want to count the cr.
		count++;
		ptr++;
	}

	// Terminate string
	*ptr = '\0';

	// return how many bytes read.
	return count;
}

//
// Before we can connect we need to parse the server address and optional
// port from the url provided.  the format of "url" as passed to this function
// is "//192.168.0.1:8080/blah.elf" where "192.168.0.1" can be either an IP
// or a domain name and ":8080" is the optional port to connect to, default
// port is 80.
//
// This function will return a filename string for use in GET
// requests, and fill the structure pointed to by *server with the
// correct values.
//
const char *http_resolve_address( struct sockaddr_in *server, const char * url, char *host_addr)
{
	unsigned char w,x,y,z;
	const char *char_ptr;
	char addr[128];
	char port[6] = "80"; /* default port of 80(HTTP) */
	int i = 0, rv;
	int is_domain = 0;

	/* strip http: */
	char_ptr = strchr(url, ':');
	if (char_ptr != NULL)
	{
		url = char_ptr + 1;
	}

	// URL must start with double forward slashes.
	if((url[0] != '/') || (url[1] != '/' )) return(NULL);

	url += 2;
	for(i = 0; ((url[i] != '\0') && (url[i] != '/')) && (i < 127); i++)
	{
		if((((addr[i] = url[i]) < '0') || (url[i] > '9')) && (url[i] != '.'))
		{
			if(url[i] == ':')
			{// allow specification of port in URL like http://www.server.net:8080/
				for(w = 0; ((w + i + 1) < 127) && (w < 5) && (url[w + i + 1] != '/') && (url[w + i + 1] != '\0'); w++)
					port[w] = url[w + i + 1];
				port[w] = '\0';

				rt_kprintf("HTTP: using port %s for connection\n", port);
				break;
			}
			else // it's a domain name if a non-numeric char is contained in the "server" part of the URL.
				is_domain = 1;
		}
	}
	addr[i] = '\0'; // overwrite last char copied(should be '/', '\0' or ':') with a '\0'
	strcpy(host_addr, addr);

	if(is_domain)
	{
		// resolve the host name.
		rv = dns_gethostbyname(addr, &server->sin_addr, RT_NULL, RT_NULL);
		if(rv != 0)
		{
			rt_kprintf("HTTP: failed to resolve domain '%s'\n", addr);
			return RT_NULL;
		}
	}
	else
	{
		// turn '.' characters in ip string into null characters
		for(i = 0, w = 0; i < 16; i++)
		{
			if(addr[i] == '.')
			{
				addr[i] = '\0';
				w++;
			}
		}

		if(w < 4)
		{ // w is used as a simple error check here
			rt_kprintf("HTTP: invalid IP address '%s'\n", addr);
			return RT_NULL;
		}

		i = 0;

		// Extract individual ip number octets from string
		w = (int)strtol(&addr[i],NULL, 10);
		i += (strlen(&addr[i]) + 1);

		x = (int)strtol(&addr[i],NULL, 10);
		i += (strlen(&addr[i]) + 1);

		y = (int)strtol(&addr[i],NULL, 10);
		i += (strlen(&addr[i]) + 1);

		z = (int)strtol(&addr[i],NULL, 10);
		i += (strlen(&addr[i]) + 1);

		IP4_ADDR( (struct ip_addr *)&(server->sin_addr) ,w,x,y,z );
	}

	i = (int) strtol(port, NULL, 10); // set the port
	server->sin_port = htons(i);

	server->sin_family = AF_INET;

	char_ptr = url;
	while(*char_ptr != '/') char_ptr++;

	return char_ptr;
}

//
// This is the main HTTP client connect work.  Makes the connection
// and handles the protocol and reads the return headers.  Needs
// to leave the stream at the start of the real data.
//
static int http_connect(struct http_session* session,
    struct sockaddr_in * server, char *host_addr, const char * url)
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

	// Needs more error checking here.....
	rc = send( peer_handle, _http_get,  sizeof( _http_get ) - 1, 0 );
	rc = send( peer_handle, (void*) url, strlen( url ), 0 );
	rc = send( peer_handle, _http_getend, sizeof( _http_getend ) - 1, 0 );

	rc = send( peer_handle, _http_host,  sizeof( _http_host ) - 1, 0 );
	rc = send( peer_handle, host_addr, strlen( url ), 0 );
	rc = send( peer_handle, _http_endheader, sizeof( _http_endheader ) - 1, 0 ); // "\r\n"

	rc = send( peer_handle, _http_user_agent, sizeof( _http_user_agent ) - 1, 0 );
	rc = send( peer_handle, _http_endheader, sizeof( _http_endheader ) - 1, 0 );

	// We now need to read the header information
	while ( 1 )
	{
		int i;

		// read a line from the header information.
		rc = http_read_line( peer_handle, mimeBuffer, 100 );

		rt_kprintf(">> %s", mimeBuffer);

		if ( rc < 0 ) return rc;

		// End of headers is a blank line.  exit.
		if ( rc == 0 ) break;
		if ( (rc == 1) && (mimeBuffer[0] == '\r') ) break;

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
	const char *get_name;
	char host_addr[100];
	struct http_session* session;

    session = (struct http_session*) rt_malloc(sizeof(struct http_session*));
	if(session == RT_NULL) return RT_NULL;

	session->size = 0;
	session->position = 0;

	/* Check valid IP address and URL */
	if((get_name = http_resolve_address(&server, url, host_addr)) == NULL)
	{
		rt_free(session);
		return RT_NULL;
	}

	// Now we connect and initiate the transfer by sending a
	// request header to the server, and receiving the response header
	if((peer_handle = http_connect(session, &server, host_addr, get_name)) < 0)
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

#include <finsh.h>
void http_test(char* url)
{
	struct http_session* session;
	rt_uint8_t buffer[80];
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
		length = http_session_read(session, buffer, sizeof(buffer));

		rt_kprintf(buffer);
	} while (length > 0);

	http_session_close(session);
}
FINSH_FUNCTION_EXPORT(http_test, http client test);
