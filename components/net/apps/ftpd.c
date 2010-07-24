#include <string.h>
#include <stdlib.h>

#include <rtthread.h>
#include <dfs_posix.h>
#include <lwip/sockets.h>
#include <time.h>

#define FTP_PORT			21
#define FTP_SRV_ROOT		"/"
#define FTP_MAX_CONNECTION	2
#define FTP_USER			"rtt"
#define FTP_PASSWORD		"demo"
#define FTP_WELCOME_MSG		"220-= welcome on RT-Thread FTP server =-\r\n220 \r\n"
#define FTP_BUFFER_SIZE		1024

struct ftp_session
{
	rt_bool_t is_anonymous;

	int sockfd;
	struct sockaddr_in remote;

	/* pasv data */
	char pasv_active;
	int  pasv_sockfd;

	unsigned short pasv_port;
	size_t offset;

	/* current directory */
	char currentdir[256];

	struct ftp_session* next;
};
static struct ftp_session* session_list = NULL;

int ftp_process_request(struct ftp_session* session, char * buf);
int ftp_get_filesize(char *filename);

struct ftp_session* ftp_new_session()
{
	struct ftp_session* session;

	session = (struct ftp_session*)rt_malloc(sizeof(struct ftp_session));

	session->next = session_list;
	session_list = session;

	return session;
}

void ftp_close_session(struct ftp_session* session)
{
	struct ftp_session* list;

	if (session_list == session)
	{
		session_list = session_list->next;
		session->next = NULL;
	}
	else
	{
		list = session_list;
		while (list->next != session) list = list->next;

		list->next = session->next;
		session->next = NULL;
	}

	rt_free(session);
}

int ftp_get_filesize(char * filename)
{
	int pos;
	int end;
	int fd;

	fd = open(filename, O_RDONLY, 0);
	if (fd < 0) return -1;

	pos = lseek(fd, 0, SEEK_CUR);
	end = lseek(fd, 0, SEEK_END);
	lseek (fd, pos, SEEK_SET);
	close(fd);

	return end;
}

rt_bool_t is_absolute_path(char* path)
{
#ifdef _WIN32
	if (path[0] == '\\' ||
		(path[1] == ':' && path[2] == '\\'))
		return RT_TRUE;
#else
	if (path[0] == '/') return RT_TRUE;
#endif

	return RT_FALSE;
}

int build_full_path(struct ftp_session* session, char* path, char* new_path, size_t size)
{
	if (is_absolute_path(path) == RT_TRUE)
		strcpy(new_path, path);
	else
	{
		rt_sprintf(new_path, "%s/%s", session->currentdir, path);
	}

	return 0;
}

void ftpd_thread_entry(void* parameter)
{
	int numbytes;
	int sockfd, maxfdp1;
	struct sockaddr_in local;
	fd_set readfds, tmpfds;
	struct ftp_session* session;
	rt_uint32_t addr_len = sizeof(struct sockaddr);
	char * buffer = (char *) rt_malloc(FTP_BUFFER_SIZE);

	local.sin_port=htons(FTP_PORT);
	local.sin_family=PF_INET;
	local.sin_addr.s_addr=INADDR_ANY;

	FD_ZERO(&readfds);
	FD_ZERO(&tmpfds);

	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		rt_kprintf("create socket failed\n");
		return ;
	}

	bind(sockfd, (struct sockaddr *)&local, addr_len);
	listen(sockfd, FTP_MAX_CONNECTION);

	FD_SET(sockfd, &readfds);
	for(;;)
	{
	    /* get maximum fd */
	    maxfdp1 = sockfd + 1;
        session = session_list;
	    while (session != RT_NULL)
	    {
	        if (maxfdp1 < session->sockfd + 1)
                maxfdp1 = session->sockfd + 1;

            FD_SET(session->sockfd, &readfds);
            session = session->next;
	    }

		tmpfds=readfds;
		if (select(maxfdp1, &tmpfds, 0, 0, 0) == 0) continue;

		if(FD_ISSET(sockfd, &tmpfds))
		{
			int com_socket;
			struct sockaddr_in remote;

			com_socket = accept(sockfd, (struct sockaddr*)&remote, &addr_len);
			if(com_socket == -1)
			{
				rt_kprintf("Error on accept()\nContinuing...\n");
				continue;
			}
			else
			{
				rt_kprintf("Got connection from %s\n", inet_ntoa(remote.sin_addr));
				send(com_socket, FTP_WELCOME_MSG, strlen(FTP_WELCOME_MSG), 0);
				FD_SET(com_socket, &readfds);

				/* new session */
				session = ftp_new_session();
				if (session != NULL)
				{
					strcpy(session->currentdir, FTP_SRV_ROOT);
					session->sockfd = com_socket;
					session->remote = remote;
				}
			}
		}

		{
			struct ftp_session* next;

			session = session_list;
			while (session != NULL)
			{
				next = session->next;
				if (FD_ISSET(session->sockfd, &tmpfds))
				{
					numbytes=recv(session->sockfd, buffer, FTP_BUFFER_SIZE, 0);
					if(numbytes==0 || numbytes==-1)
					{
						rt_kprintf("Client %s disconnected\n", inet_ntoa(session->remote.sin_addr));
						FD_CLR(session->sockfd, &readfds);
						closesocket(session->sockfd);
						ftp_close_session(session);
					}
					else
					{
						buffer[numbytes]=0;
						if(ftp_process_request(session, buffer)==-1)
						{
							rt_kprintf("Client %s disconnected\r\n", inet_ntoa(session->remote.sin_addr));
							closesocket(session->sockfd);
							ftp_close_session(session);
						}
					}
				}

				session = next;
			}
		}
	}

	// rt_free(buffer);
}

int do_list(char* directory, int sockfd)
{
	DIR* dirp;
	struct dirent* entry;
	char line_buffer[256], line_length;
#ifdef _WIN32
	struct _stat s;
#else
	struct stat s;
#endif

	dirp = opendir(directory);
	if (dirp == NULL)
	{
		line_length = rt_sprintf(line_buffer, "500 Internal Error\r\n");
		send(sockfd, line_buffer, line_length, 0);
		return -1;
	}

	while (1)
	{
		entry = readdir(dirp);
		if (entry == NULL) break;

		rt_sprintf(line_buffer, "%s/%s", directory, entry->d_name);
#ifdef _WIN32
		if (_stat(line_buffer, &s) ==0)
#else
		if (stat(line_buffer, &s) == 0)
#endif
		{
			if (s.st_mode & S_IFDIR)
				line_length = rt_sprintf(line_buffer, "drw-r--r-- 1 admin admin %d Jan 1 2000 %s\r\n", 0, entry->d_name);
			else
				line_length = rt_sprintf(line_buffer, "-rw-r--r-- 1 admin admin %d Jan 1 2000 %s\r\n", s.st_size, entry->d_name);

			send(sockfd, line_buffer, line_length, 0);
		}
		else
		{
			rt_kprintf("Get directory entry error\n");
			break;
		}
	}

	closedir(dirp);
	return 0;
}

int do_simple_list(char* directory, int sockfd)
{
	DIR* dirp;
	struct dirent* entry;
	char line_buffer[256], line_length;

	dirp = opendir(directory);
	if (dirp == NULL)
	{
		line_length = rt_sprintf(line_buffer, "500 Internal Error\r\n");
		send(sockfd, line_buffer, line_length, 0);
		return -1;
	}

	while (1)
	{
		entry = readdir(dirp);
		if (entry == NULL) break;

		line_length = rt_sprintf(line_buffer, "%s\r\n", entry->d_name);
		send(sockfd, line_buffer, line_length, 0);
	}

	closedir(dirp);
	return 0;
}

int str_begin_with(char* src, char* match)
{
	while (*match)
	{
		/* check source */
		if (*src == 0) return -1;

		if (*match != *src) return -1;
		match ++; src ++;
	}

	return 0;
}

int ftp_process_request(struct ftp_session* session, char *buf)
{
	int  fd;
	struct timeval tv;
	fd_set readfds;
	char filename[256];
	int  numbytes;
	char *sbuf;
	char *parameter_ptr, *ptr;
	rt_uint32_t addr_len = sizeof(struct sockaddr_in);
	struct sockaddr_in local, pasvremote;

	sbuf =(char *)rt_malloc(FTP_BUFFER_SIZE);

	tv.tv_sec=3, tv.tv_usec=0;
	local.sin_family=PF_INET;
	local.sin_addr.s_addr=INADDR_ANY;

	/* remove \r\n */
	ptr = buf;
	while (*ptr)
	{
		if (*ptr == '\r' || *ptr == '\n') *ptr = 0;
		ptr ++;
	}

	/* get request parameter */
	parameter_ptr = strchr(buf, ' '); if (parameter_ptr != NULL) parameter_ptr ++;

	// debug:
	rt_kprintf("%s requested: \"%s\"\n", inet_ntoa(session->remote.sin_addr), buf);

	//
	//-----------------------
	if(str_begin_with(buf, "USER")==0)
	{
		rt_kprintf("%s sent login \"%s\"\n", inet_ntoa(session->remote.sin_addr), parameter_ptr);
		// login correct
		if(strcmp(parameter_ptr, "anonymous") == 0)
		{
			session->is_anonymous = RT_TRUE;
			rt_sprintf(sbuf, "331 Anonymous login OK send e-mail address for password.\r\n", parameter_ptr);
			send(session->sockfd, sbuf, strlen(sbuf), 0);
		}
		else if (strcmp(parameter_ptr, FTP_USER) == 0)
		{
			session->is_anonymous = RT_FALSE;		
			rt_sprintf(sbuf, "331 Password required for %s\r\n", parameter_ptr);
			send(session->sockfd, sbuf, strlen(sbuf), 0);
		}
		else
		{
			// incorrect login
			rt_sprintf(sbuf, "530 Login incorrect. Bye.\r\n");
			send(session->sockfd, sbuf, strlen(sbuf), 0);
			rt_free(sbuf);
			return -1;
		}
		return 0;
	}
	else if(str_begin_with(buf, "PASS")==0)
	{
		rt_kprintf("%s sent password \"%s\"\n", inet_ntoa(session->remote.sin_addr), parameter_ptr);
		if (strcmp(parameter_ptr, FTP_PASSWORD)==0 ||
			session->is_anonymous == RT_TRUE)
		{
			// password correct
			rt_sprintf(sbuf, "230 User logged in\r\n");
			send(session->sockfd, sbuf, strlen(sbuf), 0);
			rt_free(sbuf);			
			return 0;
		}

		// incorrect password
		rt_sprintf(sbuf, "530 Login or Password incorrect. Bye!\r\n");
		send(session->sockfd, sbuf, strlen(sbuf), 0);
		rt_free(sbuf);		
		return -1;
	}
	else if(str_begin_with(buf, "LIST")==0  )
	{
		memset(sbuf,0,FTP_BUFFER_SIZE);
		rt_sprintf(sbuf, "150 Opening Binary mode connection for file list.\r\n");
		send(session->sockfd, sbuf, strlen(sbuf), 0);
		do_list(session->currentdir, session->pasv_sockfd);
		closesocket(session->pasv_sockfd);
		session->pasv_active = 0;
		rt_sprintf(sbuf, "226 Transfert Complete.\r\n");
		send(session->sockfd, sbuf, strlen(sbuf), 0);
	}
	else if(str_begin_with(buf, "NLST")==0 )
	{
		memset(sbuf, 0, FTP_BUFFER_SIZE);
		rt_sprintf(sbuf, "150 Opening Binary mode connection for file list.\r\n");
		send(session->sockfd, sbuf, strlen(sbuf), 0);
		do_simple_list(session->currentdir, session->pasv_sockfd);
		closesocket(session->pasv_sockfd);
		session->pasv_active = 0;
		rt_sprintf(sbuf, "226 Transfert Complete.\r\n");
		send(session->sockfd, sbuf, strlen(sbuf), 0);
	}
	else if(str_begin_with(buf, "PWD")==0 || str_begin_with(buf, "XPWD")==0)
	{
		rt_sprintf(sbuf, "257 \"%s\" is current directory.\r\n", session->currentdir);
		send(session->sockfd, sbuf, strlen(sbuf), 0);
	}
	else if(str_begin_with(buf, "TYPE")==0)
	{
		// Ignore it
		if(strcmp(parameter_ptr, "I")==0)
		{
			rt_sprintf(sbuf, "200 Type set to binary.\r\n");
			send(session->sockfd, sbuf, strlen(sbuf), 0);
		}
		else
		{
			rt_sprintf(sbuf, "200 Type set to ascii.\r\n");
			send(session->sockfd, sbuf, strlen(sbuf), 0);
		}
	}
	else if(str_begin_with(buf, "PASV")==0)
	{
		int dig1, dig2;
		int sockfd;
		char optval='1';

		session->pasv_port = 10000;
		session->pasv_active = 1;
		local.sin_port=htons(session->pasv_port);
		local.sin_addr.s_addr=INADDR_ANY;

		dig1 = (int)(session->pasv_port/256);
		dig2 = session->pasv_port % 256;

		FD_ZERO(&readfds);
		if((sockfd=socket(PF_INET, SOCK_STREAM, 0))==-1)
		{
			rt_sprintf(sbuf, "425 Can't open data connection.\r\n");
			send(session->sockfd, sbuf, strlen(sbuf), 0);
			goto err1;
		}
		if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))==-1)
		{
			rt_sprintf(sbuf, "425 Can't open data connection.\r\n");
			send(session->sockfd, sbuf, strlen(sbuf), 0);
			goto err1;
		}
		if(bind(sockfd, (struct sockaddr *)&local, addr_len)==-1)
		{
			rt_sprintf(sbuf, "425 Can't open data connection.\r\n");
			send(session->sockfd, sbuf, strlen(sbuf), 0);
			goto err1;
		}
		if(listen(sockfd, 1)==-1)
		{
			rt_sprintf(sbuf, "425 Can't open data connection.\r\n");
			send(session->sockfd, sbuf, strlen(sbuf), 0);
			goto err1;
		}
		rt_kprintf("Listening %d seconds @ port %d\n", tv.tv_sec, session->pasv_port);
		rt_sprintf(sbuf, "227 Entering passive mode (%d,%d,%d,%d,%d,%d)\r\n", 127, 0, 0, 1, dig1, dig2);
		send(session->sockfd, sbuf, strlen(sbuf), 0);
		FD_SET(sockfd, &readfds);
		select(0, &readfds, 0, 0, &tv);
		if(FD_ISSET(sockfd, &readfds))
		{
			if((session->pasv_sockfd = accept(sockfd, (struct sockaddr*)&pasvremote, &addr_len))==-1)
			{
				rt_sprintf(sbuf, "425 Can't open data connection.\r\n");
				send(session->sockfd, sbuf, strlen(sbuf), 0);
				goto err1;
			}
			else
			{
				rt_kprintf("Got Data(PASV) connection from %s\n", inet_ntoa(pasvremote.sin_addr));
				session->pasv_active = 1;
				closesocket(sockfd);
			}
		}
		else
		{
err1:
			closesocket(session->pasv_sockfd);
			session->pasv_active = 0;
			rt_free(sbuf);
			return 0;
		}
	}
	else if (str_begin_with(buf, "RETR")==0)
	{
		int file_size;

		strcpy(filename, buf + 5);

		build_full_path(session, parameter_ptr, filename, 256);
		file_size = ftp_get_filesize(filename);
		if (file_size == -1)
		{
			rt_sprintf(sbuf, "550 \"%s\" : not a regular file\r\n", filename);
			send(session->sockfd, sbuf, strlen(sbuf), 0);
			session->offset=0;
			rt_free(sbuf);			
			return 0;
		}

		fd = open(filename, O_RDONLY, 0);
		if (fd < 0)
		{
			rt_free(sbuf);
			return 0;
		}

		if(session->offset>0 && session->offset < file_size)
		{
			lseek(fd, session->offset, SEEK_SET);
			rt_sprintf(sbuf, "150 Opening binary mode data connection for partial \"%s\" (%d/%d bytes).\r\n",
				filename, file_size - session->offset, file_size);
		}
		else
		{
			rt_sprintf(sbuf, "150 Opening binary mode data connection for \"%s\" (%d bytes).\r\n", filename, file_size);
		}
		send(session->sockfd, sbuf, strlen(sbuf), 0);
		while((numbytes = read(fd, sbuf, FTP_BUFFER_SIZE))>0)
		{
			send(session->pasv_sockfd, sbuf, numbytes, 0);
		}
		rt_sprintf(sbuf, "226 Finished.\r\n");
		send(session->sockfd, sbuf, strlen(sbuf), 0);
		close(fd);
		closesocket(session->pasv_sockfd);
	}
	else if (str_begin_with(buf, "STOR")==0)
	{
		if(session->is_anonymous == RT_TRUE)
		{
			rt_sprintf(sbuf, "550 Permission denied.\r\n");
			send(session->sockfd, sbuf, strlen(sbuf), 0);
			rt_free(sbuf);
			return 0;
		}

		build_full_path(session, parameter_ptr, filename, 256);

		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0);
		if(fd < 0)
		{
			rt_sprintf(sbuf, "550 Cannot open \"%s\" for writing.\r\n", filename);
			send(session->sockfd, sbuf, strlen(sbuf), 0);
			rt_free(sbuf);
			return 0;
		}
		rt_sprintf(sbuf, "150 Opening binary mode data connection for \"%s\".\r\n", filename);
		send(session->sockfd, sbuf, strlen(sbuf), 0);
		FD_ZERO(&readfds);
		FD_SET(session->pasv_sockfd, &readfds);
		rt_kprintf("Waiting %d seconds for data...\n", tv.tv_sec);
		while(select(session->pasv_sockfd+1, &readfds, 0, 0, &tv)>0 )
		{
			if((numbytes=recv(session->pasv_sockfd, sbuf, FTP_BUFFER_SIZE, 0))>0)
			{
				write(fd, sbuf, numbytes);
			}
			else if(numbytes==0)
			{
				close(fd);
				closesocket(session->pasv_sockfd);
				rt_sprintf(sbuf, "226 Finished.\r\n");
				send(session->sockfd, sbuf, strlen(sbuf), 0);
				break;
			}
			else if(numbytes==-1)
			{
				close(fd);
				closesocket(session->pasv_sockfd);
				rt_free(sbuf);
				return -1;
			}
		}
		closesocket(session->pasv_sockfd);
	}
	else if(str_begin_with(buf, "SIZE")==0)
	{
		int file_size;

		build_full_path(session, parameter_ptr, filename, 256);

		file_size = ftp_get_filesize(filename);
		if( file_size == -1)
		{
			rt_sprintf(sbuf, "550 \"%s\" : not a regular file\r\n", filename);
			send(session->sockfd, sbuf, strlen(sbuf), 0);
		}
		else
		{
			rt_sprintf(sbuf, "213 %d\r\n", file_size);
			send(session->sockfd, sbuf, strlen(sbuf), 0);
		}
	}
	else if(str_begin_with(buf, "MDTM")==0)
	{
		rt_sprintf(sbuf, "550 \"/\" : not a regular file\r\n");
		send(session->sockfd, sbuf, strlen(sbuf), 0);
	}
	else if(str_begin_with(buf, "SYST")==0)
	{
		rt_sprintf(sbuf, "215 %s\r\n", "RT-Thread RTOS");
		send(session->sockfd, sbuf, strlen(sbuf), 0);
	}
	else if(str_begin_with(buf, "CWD")==0)
	{
		build_full_path(session, parameter_ptr, filename, 256);

		rt_sprintf(sbuf, "250 Changed to directory \"%s\"\r\n", filename);
		send(session->sockfd, sbuf, strlen(sbuf), 0);
		strcpy(session->currentdir, filename);
		rt_kprintf("Changed to directory %s", filename);
	}
	else if(str_begin_with(buf, "CDUP")==0)
	{
		rt_sprintf(filename, "%s/%s", session->currentdir, "..");

		rt_sprintf(sbuf, "250 Changed to directory \"%s\"\r\n", filename);
		send(session->sockfd, sbuf, strlen(sbuf), 0);
		strcpy(session->currentdir, filename);
		rt_kprintf("Changed to directory %s", filename);
	}
	else if(str_begin_with(buf, "PORT")==0)
	{
		int i;
		int portcom[6];
		char tmpip[100];

		i=0;
		portcom[i++]=atoi(strtok(parameter_ptr, ".,;()"));
		for(;i<6;i++)
			portcom[i]=atoi(strtok(0, ".,;()"));
		rt_sprintf(tmpip, "%d.%d.%d.%d", portcom[0], portcom[1], portcom[2], portcom[3]);

		FD_ZERO(&readfds);
		if((session->pasv_sockfd=socket(AF_INET, SOCK_STREAM, 0))==-1)
		{
			rt_sprintf(sbuf, "425 Can't open data connection.\r\n");
			send(session->sockfd, sbuf, strlen(sbuf), 0);
			closesocket(session->pasv_sockfd);
			session->pasv_active = 0;
			rt_free(sbuf);	
			return 0;
		}
		pasvremote.sin_addr.s_addr=inet_addr(tmpip);
		pasvremote.sin_port=htons(portcom[4] * 256 + portcom[5]);
		pasvremote.sin_family=PF_INET;
		if(connect(session->pasv_sockfd, (struct sockaddr *)&pasvremote, addr_len)==-1)
		{
			// is it only local address?try using gloal ip addr
			pasvremote.sin_addr=session->remote.sin_addr;
			if(connect(session->pasv_sockfd, (struct sockaddr *)&pasvremote, addr_len)==-1)
			{
				rt_sprintf(sbuf, "425 Can't open data connection.\r\n");
				send(session->sockfd, sbuf, strlen(sbuf), 0);
				closesocket(session->pasv_sockfd);
				rt_free(sbuf);				
				return 0;
			}
		}
		session->pasv_active=1;
		session->pasv_port = portcom[4] * 256 + portcom[5];
		rt_kprintf("Connected to Data(PORT) %s @ %d\n", tmpip, portcom[4] * 256 + portcom[5]);
		rt_sprintf(sbuf, "200 Port Command Successful.\r\n");
		send(session->sockfd, sbuf, strlen(sbuf), 0);
	}
	else if(str_begin_with(buf, "REST")==0)
	{
		if(atoi(parameter_ptr)>=0)
		{
			session->offset=atoi(parameter_ptr);
			rt_sprintf(sbuf, "350 Send RETR or STOR to start transfert.\r\n");
			send(session->sockfd, sbuf, strlen(sbuf), 0);
		}
	}
	else if(str_begin_with(buf, "MKD")==0)
	{
		if (session->is_anonymous == RT_TRUE)
		{
			rt_sprintf(sbuf, "550 Permission denied.\r\n");
			send(session->sockfd, sbuf, strlen(sbuf), 0);
			rt_free(sbuf);			
			return 0;
		}

		build_full_path(session, parameter_ptr, filename, 256);

		if(mkdir(filename, 0) == -1)
		{
			rt_sprintf(sbuf, "550 File \"%s\" exists.\r\n", filename);
			send(session->sockfd, sbuf, strlen(sbuf), 0);
		}
		else
		{
			rt_sprintf(sbuf, "257 directory \"%s\" successfully created.\r\n", filename);
			send(session->sockfd, sbuf, strlen(sbuf), 0);
		}
	}
	else if(str_begin_with(buf, "DELE")==0)
	{
		if (session->is_anonymous == RT_TRUE)
		{
			rt_sprintf(sbuf, "550 Permission denied.\r\n");
			send(session->sockfd, sbuf, strlen(sbuf), 0);
			rt_free(sbuf);
			return 0;
		}

		build_full_path(session, parameter_ptr, filename, 256);

		if(unlink(filename)==0)
			rt_sprintf(sbuf, "250 Successfully deleted file \"%s\".\r\n", filename);
		else
		{
			rt_sprintf(sbuf, "550 Not such file or directory: %s.\r\n", filename);
		}
		send(session->sockfd, sbuf, strlen(sbuf), 0);
	}
	else if(str_begin_with(buf, "RMD")==0)
	{
		if (session->is_anonymous == RT_TRUE)
		{
			rt_sprintf(sbuf, "550 Permission denied.\r\n");
			send(session->sockfd, sbuf, strlen(sbuf), 0);
			rt_free(sbuf);			
			return 0;
		}
		build_full_path(session, parameter_ptr, filename, 256);

		if(unlink(filename) == -1)
		{
			rt_sprintf(sbuf, "550 Directory \"%s\" doesn't exist.\r\n", filename);
			send(session->sockfd, sbuf, strlen(sbuf), 0);
		}
		else
		{
			rt_sprintf(sbuf, "257 directory \"%s\" successfully deleted.\r\n", filename);
			send(session->sockfd, sbuf, strlen(sbuf), 0);
		}
	}
	
	else if(str_begin_with(buf, "QUIT")==0)
	{
		rt_sprintf(sbuf, "221 Bye!\r\n");
		send(session->sockfd, sbuf, strlen(sbuf), 0);
		rt_free(sbuf);		
		return -1;
	}
	else
	{
		rt_sprintf(sbuf, "502 Not Implemented.\r\n");
		send(session->sockfd, sbuf, strlen(sbuf), 0);
	}
	rt_free(sbuf);	
	return 0;
}

void ftpd_start()
{
	rt_thread_t tid;

	tid = rt_thread_create("ftpd",
		ftpd_thread_entry, RT_NULL,
		4096, 30, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(ftpd_start, start ftp server)
#endif
