#include "httpd.h"
#include "fs.c"
/**************************************
*author: Jone.Chen  <yuhua8688@tom.com>
*License:LGPL
***************************************/

#ifdef RT_HTTP_USE_AUTH
volatile unsigned char http_user_auth;
#endif

#ifdef RT_HTTP_USE_CGI
extern void processCgi(int sock,char cmd,char param,char *data,int len);
#endif

#ifdef RT_HTTP_USE_POST
extern void processPost(int sock,char *name,char * value);
#endif

#ifdef RT_HTTP_USE_UPLOAD
extern void processUpload(int sock,char *name,char * value,unsigned long offset,unsigned long length,unsigned long size);
#endif

#define  DefaultFile_Cnt 5
const char *gDefaultFile[] = {
  {".shtml" },
  {".ssi" },
  {".shtm"},
  {".html"},
  {".htm"}
};
#define  ExeFile_Cnt 4
const char *gExeFile[] = {
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
			resolvHttp(sockClt,dbuf,RecvLen);
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

unsigned char *decodeBase64(unsigned char*src)
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
void parseFileCgi(int sock,struct fs_file *fs){
	struct fs_file *fstmp=RT_NULL;
	int len=0,tmp=0;
	char *ptr=RT_NULL,*ptrTmp=RT_NULL,*pName=RT_NULL,*pDat=RT_NULL;
	char cmd=0,param=0;

	if(fs==RT_NULL){
		err_404(sock);
		return ;
	}
	ptr=fs->data;
	ptrTmp=strstr(ptr,"\r\n\r\n");//参数位置
	tmp=ptrTmp-ptr;
	send(sock,ptr,tmp-5,0);
	send(sock,"html\r\n\r\n",8,0);
	ptr=ptrTmp+4;
	//EF BB BF 23
	while(len<fs->len){
		switch(*ptr){
		 case '#':
			ptrTmp=strchr(ptr,'\n');
			ptrTmp++;
			tmp=ptrTmp-ptr;
			len+=tmp;
			ptr=ptrTmp;
		 	break;
		 case 'c':
		 	
		 	cmd=*(ptr+2);
			param=*(ptr+4);
			ptr+=6;
			ptrTmp=strchr(ptr,'\n');
			
			ptrTmp++;
			//chr=*ptrTmp;
			//*ptrTmp=0;
			tmp=ptrTmp-ptr;
			//#ifdef RT_HTTP_USE_CGI
			processCgi(sock, cmd, param,ptr,tmp);
			//#endif
			tmp+=6;
			len+=tmp;
			//*ptrTmp=chr;	
			ptr=ptrTmp;
		 	break;
		 case 'i':
		 	ptr+=2;//file name
			ptrTmp=strchr(ptr,'\n');
			tmp=ptrTmp-ptr;
			pName=rt_malloc(tmp);
			rt_memset(pName,0,tmp+1);//加一位存结束符
			*pName='/';
			rt_memcpy(pName+1,ptr,tmp-1);
			tmp+=1;
			len+=tmp;
			ptr=ptrTmp+1;
			fstmp=fs_open(pName);
			rt_free(pName);
			if(fstmp==RT_NULL){
				err_404(sock);
				return;
			}
			pDat=fstmp->data;
			pName=strstr(pDat,"\r\n\r\n");
			tmp=pName-fstmp->data;//头长度
			//tmp+=2;
			tmp=fstmp->len-tmp;

			send(sock,pName,tmp,0);
			fs_close(fstmp);
		 	break;
		 case 't':
		 	ptr+=2;//file name
			ptrTmp=strchr(ptr,'\n');
			ptrTmp++;
			tmp=ptrTmp-ptr;
			send(sock,ptr,tmp,0);
			ptr=ptrTmp;
		 	break;
		case '.':
		 default:
		 	return;


		}

	}
	//fs->data,fs->len
}
#endif
char OpenUrl(int sock,char *url){
	struct fs_file *fs=RT_NULL;
	char param[256];
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
			sprintf(param,"/index%s\0",gDefaultFile[i]);
			fs=fs_open(param);
			if(fs!=RT_NULL){
				break;
			}
		}
	}
	else{
	  fs=fs_open(url);
	}
	if(fs!=RT_NULL){
	for(i=0;i<ExeFile_Cnt;i++){			
		if(strstr(url,gExeFile[i])!=RT_NULL){
			break;
		}
	}
	if(i<ExeFile_Cnt){
		if(strstr(url,".cgi")!=RT_NULL){ //cgi处理
		#ifdef RT_HTTP_USE_CGI
			parseFileCgi( sock,fs);
		#endif
		}
		else{//ssi处理
	
		}
	
	}
	else{
		send(sock,fs->data,fs->len,0);
	}
	fs_close(fs);
	}
	else{
	err_404(sock);
	}
	return 0;
}



void resolvHttp(int sock,char *data,int len){
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
			   user_pwd=(char *)decodeBase64((unsigned char *)user_pwd);
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
		OpenUrl(sock,url);
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
						processPost( sock,pName,pValue);
					}
					
				}
			}
			url=data+5;
			param=strstr(data,"HTTP");
			param--;
			*param=0;
			OpenUrl( sock, url);
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
			OpenUrl( sock, url);
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
			processUpload(sock,pName,pValue,offset,len,streamSize-len);	
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
						processUpload(sock,pName,data,offset,streamSize,0);
						offset=offset+streamSize;
						streamSize=0;
					}
					else
					{
						//send(sock,data,len,0);
						processUpload(sock,pName,data,offset,len,streamSize-len);
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

