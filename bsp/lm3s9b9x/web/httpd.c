#include "httpd.h"
/**************************************
*author: Jone.Chen  <yuhua8688@tom.com>
*License:LGPL
***************************************/


#ifdef RT_HTTP_USE_AUTH
volatile unsigned char http_user_auth;
#endif

#ifdef RT_HTTP_USE_CGI
extern void process_cgi(int sock,char cmd,char param,char *data,int len);
#endif

#ifdef RT_HTTP_USE_POST
extern void process_post(int sock,char *name,char * value);
#endif

#ifdef RT_HTTP_USE_UPLOAD
extern void process_upload(int sock,char *name,char * value,unsigned long offset,unsigned long length,unsigned long size);
#endif

#define  DefaultFile_Cnt 5
const char *g_default_file[] = {
  {".shtml" },
  {".ssi" },
  {".shtm"},
  {".html"},
  {".htm"}
};
#define  exe_file_cnt 4
const char *g_exe_file[] = {
  {".shtml" },
  {".ssi" },
  {".shtm"},
  {".cgi"}
};



rt_thread_t httpd_thread;
void init_httpd(void){
	httpd_thread = rt_thread_create("httpd",rt_httpd_entry, RT_NULL,4096, RT_LWIP_HTTP_PRIORITY, 20);
	rt_thread_startup(httpd_thread);
	#ifdef RT_HTTP_USE_AUTH
	http_user_auth=0;
	#endif
}


void rt_httpd_entry(void *parameter)
{
	int sock=0,sockClt=0,RecvLen=0;
	socklen_t cltLen=0;
	struct sockaddr_in srvAddr,clientAddr;
	char dbuf[2048];//*ptr;

	sock=socket(AF_INET,SOCK_STREAM,0);
	srvAddr.sin_family      = PF_INET;
	srvAddr.sin_port        = htons(80);
	srvAddr.sin_addr.s_addr	= INADDR_ANY;
	rt_thread_delay(500);
	bind(sock,(struct sockaddr*)&srvAddr,sizeof(srvAddr));
	listen(sock,30);
	rt_memset(dbuf,0,2048);
	while(1){
		sockClt=accept(sock,(struct sockaddr*)&clientAddr,&cltLen);
		RecvLen=recv(sockClt,dbuf,2048,0);	//
		dbuf[RecvLen]=0;
		if(RecvLen>0){
			/*if(RecvLen==512){
			   ptr=dbuf+4;
			   while(*ptr!=

			}*/
			resolv_http(sockClt,dbuf,RecvLen);
		}

		closesocket(sockClt);
		rt_memset(&clientAddr,0,sizeof(clientAddr));
		cltLen=0;
		rt_thread_delay(2);  
	}

}

#ifdef RT_HTTP_USE_AUTH
/*
HTTP/1.1 401 Unauthorized 
Server: Web Auth 
Content-Type: text/html; charset=GB2312
Accept-Ranges: bytes
Connection: close
Cache-Control: no-cache,no-store
WWW-Authenticate: Basic realm="Router Web Config System"

<HTML><HEAD><TITLE>401 Unauthorized</TITLE></HEAD><BODY><H2>401 Unauthorized</H2>Authorization failed.</BODY></HTML>
*/


unsigned char user_auth(int sock)
{
	if(http_user_auth!=1)
	{
		send(sock,"HTTP/1.1 401 Unauthorized\r\nServer: Web Auth\r\nContent-Type: text/html; charset=GB2312\r\nAccept-Ranges: bytes\r\nConnection: close\r\n",127,0);
		send(sock,"Cache-Control: no-cache,no-store\r\nWWW-Authenticate: Basic realm=\"",65,0);
		send(sock,USER_AUTH_TITLE,strlen(USER_AUTH_TITLE),0);
		send(sock,"\"\r\n\r\n<HTML><HEAD><TITLE>401 Unauthorized</TITLE></HEAD><BODY><H2>401 Unauthorized</H2>Authorization failed.</BODY></HTML>",121,0);
		return 1;
	}
	return 0;
}

unsigned char *decode_base_64(unsigned char*src)
{
	unsigned int tmp,i,len=strlen((char*)src);
	//unsigned int cnt=len/4;
	unsigned char j, *base=(unsigned char*)rt_malloc((len/4)*3+1);
	memset(base,0,(len/4)*3+1);
	for(i=0;i<len;i+=4)
	{
		tmp=0;
		for(j=0;j<4;j++)
		{
			if(src[i+j]>='A' && src[i+j]<='Z')
			{
				tmp=tmp<<6;
				tmp=tmp+(src[i+j]-'A');
			}
			else if(src[i+j]>='a' && src[i+j]<='z')
			{
				tmp=tmp<<6;
				tmp=tmp+(src[i+j]-'a'+26);
			}
			else if(src[i+j]>='0' && src[i+j]<='9')
			{
				tmp=tmp<<6;
				tmp=tmp+(src[i+j]-'0'+52);
			}
			else if(base[i+j]=='+')
			{
				tmp=tmp<<6;
				tmp=tmp+62;
			}
			else if(base[i+j]=='/')
			{
				tmp=tmp<<6;
				tmp=tmp+63;	
			}
			else //'='
			{
				tmp=tmp<<6;
			}
		}
		base[i/4*3+2]=tmp&0xFF;
		tmp=tmp>>8;
		base[i/4*3+1]=tmp&0xFF;
		tmp=tmp>>8;
		base[i/4*3]=tmp&0xFF;
	}
	return base;

}

#endif


void err_404(int sock){
 send(sock,"404 file not found",18,0);
}



#ifdef RT_HTTP_USE_CGI


void parse_file_cgi(int sock,int fd)	
{

 	int tfd;
	char data[1024];
	int size=0,len=0,tmp=0,cur_offset=0,offset=0;
	char *ptr=RT_NULL,*ptrTmp=RT_NULL,*pName=RT_NULL;
	char cmd=0,param=0;

	if(fd<0)
	{
		err_404(sock);
		return ;
	}
	send(sock,"HTTP/1.0 200 OK\r\nServer: lwIP\r\nContent-type: text/html\r\n\r\n",58,0);
	offset=lseek(fd,0,SEEK_END);
	cur_offset=lseek(fd,0,SEEK_SET);
	//EF BB BF 23
	while(cur_offset<offset){
		size=read(fd,data,1024);
		ptr=data;
		len=0;
		while(len<size)
		{	ptrTmp=strchr(ptr,'\n');
			if(ptrTmp==RT_NULL)
			{
			   break;
			}
			else
			{

				switch(*ptr){
				 case '#':
					ptrTmp++;
					tmp=ptrTmp-ptr;
					len+=tmp;
					ptr=ptrTmp;
				 	break;
				 case 'c':
				 	cmd=*(ptr+2);
					param=*(ptr+4);
					ptr+=6;
					ptrTmp++;
					tmp=ptrTmp-ptr;
					process_cgi(sock, cmd, param,ptr,tmp);
					tmp+=6;
					len+=tmp;	
					ptr=ptrTmp;
				 	break;
				 case 'i':
				 {
				 	char i_buff[1024];
					int  i_len,i_offset,i_cur_offset;
				 	ptr+=2;//file name
					tmp=ptrTmp-ptr;
					pName=rt_malloc(tmp+1);
					rt_memset(pName,0,tmp+1);//加一位存结束符
					if(*ptr=='/')
					{
						rt_memcpy(pName,ptr,tmp-1);
					}
					else
					{
						*pName='/';
						rt_memcpy(pName+1,ptr,tmp-1);
					}
					tmp+=1;
					len+=tmp;
					ptr=ptrTmp+1;
					tfd=open(pName,O_RDONLY,400);
					rt_free(pName);
					if(tfd<0)
					{
					   err_404(sock);
					   return;
					}
					i_offset=lseek(tfd,0,SEEK_END);
					i_cur_offset=lseek(tfd,0,SEEK_SET);
					while(i_cur_offset<i_offset)
					{
					  i_len=read(tfd,i_buff,1024);
					  send(sock,i_buff,i_len,0);
					  i_cur_offset=lseek(tfd,0,SEEK_CUR);
					}
					close(tfd);
				 }
				 break;
				 case 't':
				 	ptr+=2;//file name
					ptrTmp++;
					tmp=ptrTmp-ptr;
					len=len+tmp+2;
					send(sock,ptr,tmp,0);
					ptr=ptrTmp;
				 	break;
				case '.':
					return;
				 default:
				 	  ptr++;
					  len++;
					  break;
				}
			}
			cur_offset=lseek(fd,len,SEEK_CUR);
		}

	}
	//fs->data,fs->len
}
#endif
char open_url(int sock,char *url){

	int fd,len,offset,cur_offset;
	char param[1024];

	int i=0; 
	#ifdef RT_HTTP_USE_AUTH
	if(user_auth(sock))
	{
	 	return 0;
	}
	#endif
	if(url[0]=='/' &&url[1]==0){
	//param++;

		for(i=0;i<DefaultFile_Cnt;i++){
			sprintf(param,"/index%s\0",g_default_file[i]);

				fd=open(param,O_RDONLY,400);


			if(fd>=0)
			{
				break;
			}
		}
	}
	else{

	  fd=open(url,O_RDONLY,400);
	}


	if(fd>=0)
	{	
		for(i=0;i<exe_file_cnt;i++){			
			if(strstr(url,g_exe_file[i])!=RT_NULL){
				break;
			}
		}
		if(i<exe_file_cnt){
			if(strstr(url,".cgi")!=RT_NULL){ //cgi处理
			#ifdef RT_HTTP_USE_CGI
					parse_file_cgi( sock,fd);	
			#endif
			}
			else{//ssi处理
		
			}
		
		}
		else{

			//
			offset=lseek(fd,0,SEEK_END);
			cur_offset=lseek(fd,0,SEEK_SET);
			send(sock,"HTTP/1.0 200 OK\r\nServer: lwIP\r\nContent-type: ",45,0);//
			if(strstr(url,".ht")!=RT_NULL)
			{
			 	send(sock,"text/html",9,0);
			}
			else if(strstr(url,".sht")!=RT_NULL)
			{
			    send(sock,"text/html\r\nExpires: Fri, 10 Apr 2008 14:00:00 GMT\r\nPragma: no-cache",67,0);
			}
			else if(strstr(url,".css")!=RT_NULL)
			{
				 send(sock,"text/css",8,0);
			}
			else if(strstr(url,".js")!=RT_NULL)
			{
				 send(sock,"application/x-javascript",24,0);
			}
			else if(strstr(url,".jpg")!=RT_NULL)
			{
				 send(sock,"image/jpeg",10,0);
			}
			else if(strstr(url,".png")!=RT_NULL)
			{
				 send(sock,"image/png",9,0);
			}
			else if(strstr(url,".bmp")!=RT_NULL)
			{
				 send(sock,"image/bmp",9,0);
			}
			else if(strstr(url,".gif")!=RT_NULL)
			{
				 send(sock,"image/gif",9,0);
			}

			else if(strstr(url,".ico")!=RT_NULL)
			{
				 send(sock,"image/x-icon",12,0);
			}

			else if(strstr(url,".swf")!=RT_NULL)
			{
				 send(sock,"application/x-shockwave-flash",29,0);
			}
			else if(strstr(url,".xml")!=RT_NULL)
			{
				 send(sock,"text/xml\r\nExpires: Fri, 10 Apr 2008 14:00:00 GMT\r\nPragma: no-cache",66,0);
			}
			else if(strstr(url,".txt")!=RT_NULL)
			{
				 send(sock,"text/plain",10,0);
			}
			else if(strstr(url,".class")!=RT_NULL)
			{
				 send(sock,"application/octet-stream",24,0);
			}
			else if(strstr(url,".ram")!=RT_NULL)
			{
				 send(sock,"audio/x-pn-realaudio",20,0);
			}
			send(sock,"\r\n\r\n",4,0);
			while(cur_offset<offset)
			{
				len=read(fd,param,1024);
				send(sock,param,len,0);
				cur_offset=lseek(fd,0,SEEK_CUR);
			}
		}
		close(fd);
	}
	else{
		err_404(sock);
	}
	return 0;
}



void resolv_http(int sock,char *data,int len){
	//struct fs_file *fs=RT_NULL;
	char *pName=RT_NULL,*pValue=RT_NULL;
	char *param=RT_NULL,*url=RT_NULL;//i=0;
	#ifdef RT_HTTP_USE_UPLOAD	 
	char *pStart=RT_NULL;
	unsigned long offset,streamSize=0;
	unsigned char boundaryLen=0;
	#endif
	if(strncmp(data,"GET ",4)==0){
		url=data+4;
		param=strstr(data,"HTTP");
		param--;
		*param=0;
		#ifdef RT_HTTP_USE_AUTH
		if(http_user_auth!=1) //url[0]=='/' && url[1]==0
		{
			char *user_pwd;
			param++;
			param=strstr(param,"Authorization");
			if(param!=RT_NULL)
			{
			   param=param+21;
			   user_pwd=param;
			   param=strstr(param,"\r\n");
			   *param=0;
			   user_pwd=(char *)decode_base_64((unsigned char *)user_pwd);
			   param=strstr(user_pwd,":");
			   *param=0;
			   param++;//pwd
			   if(strcmp(user_pwd,USER_AUTH_NAME)==0 &&strcmp(param,USER_AUTH_PWD)==0)
			   {
			   	  http_user_auth=1;
			   }
			   else
			   {
			   	  http_user_auth=0;
			   } 
				rt_free(user_pwd);
			}

		}

		#endif
		open_url(sock,url);
	}
	else if(strncmp(data,"POST ",5)==0){
	
			
		param=strstr(data,"Content-Type");
		param+=14;//判断type
		if(*param=='a' || *param=='A')//type:application/x-www-form-urlencoded
		{
		#ifdef RT_HTTP_USE_POST		 
			param=strstr(param,"\r\n\r\n");//参数位置
			param+=4;
			while(param!=RT_NULL){
				pName=param;
				param=strchr(param,'=');
				if(param!=RT_NULL){
					*param=0;
					param++;
					pValue=param;
					param=strchr(param,'&');
					if(param!=RT_NULL){
						*param=0;
						param++;
					}
					
					if(pName!=RT_NULL&&pValue!=RT_NULL)
					{
						process_post( sock,pName,pValue);
					}
					
				}
			}
			url=data+5;
			param=strstr(data,"HTTP");
			param--;
			*param=0;
			open_url( sock, url);
			#endif

		}
		else if(*param=='m' || *param=='M')	//type:multipart/form-data
		{
		#ifdef RT_HTTP_USE_UPLOAD
			url=data+5;
			param=strstr(data,"HTTP");
			param--;
			*param=0;			
			param=param+1;
			open_url( sock, url);
			//Content-Length: 197
			
			param=strstr(param,"boundary");//边界长度=
			param=param+9;
			pStart=param;
			param=strstr(param,"\r\n");
			boundaryLen=param-pStart;

			param=strstr(param,"Length");//文件长度
			param=param+8;
			pStart=param;
			param=strstr(param,"\r\n\r\n");
			streamSize=0;
			while(pStart<param){
			  streamSize=streamSize*10+(*pStart-'0');
			  pStart++;
			}
			param=param+4;
			pStart=param;//开始计文件长度位置	
			param=strstr(param,"filename");//参数位置
			param+=10;
			pName=param;
			param=strchr(param,'"');
			*param=0;
			param+=1;
			param=strstr(param,"\r\n\r\n");//参数位置
			param+=4;
			pValue=param;
			
			streamSize=streamSize-(pValue-pStart);//计算剩余字节
			streamSize=streamSize-boundaryLen-8;//计算文件长度
			len=len-(pValue-data);//计算这个buff剩余长度
			pStart=param;

			len=len>streamSize?streamSize:len;
			//send(sock,pValue,len,0);
			pName=rt_strdup(pName);
			offset=0;
			process_upload(sock,pName,pValue,offset,len,streamSize-len);	
			offset=offset+len;
			streamSize=streamSize-len;
			if(streamSize){ 
				while(streamSize>=1)
				{	
					len=recv(sock,data,2048,0);	//
					data[len]=0;
					if(len>=streamSize)
					{
						//send(sock,data,streamSize,0);
						process_upload(sock,pName,data,offset,streamSize,0);
						offset=offset+streamSize;
						streamSize=0;
					}
					else
					{
						//send(sock,data,len,0);
						process_upload(sock,pName,data,offset,len,streamSize-len);
						offset=offset+len;
						streamSize=streamSize-len;
					}
				}
			}
			rt_free(pName);

			#endif

			//param=strstr(param,"------------------");
			//*param=0; 
		
			//processPost( sock,pName,pValue);  
		

		}


	}
	else{
	 return ;
	}

}

