#include "../httpd.h"
/**************************************
*author: Jone.Chen  <yuhua8688@tom.com>
*License:LGPL
***************************************/
/*
  name--文件名，offset--偏移量,length--当前数据流长度，size--剩余数据流长度。
  offset=0:文件开始
  size=0:文件结束
*/
//#ifdef RT_HTTP_USE_UPLOAD
void process_upload(int sock,char *name,char * value,unsigned long offset,unsigned long length,unsigned long size)
{
	 if(offset==0)
	 {
	 	send(sock,"<p>Filename:",12,0);
		send(sock,name,rt_strlen(name),0);
		send(sock,"</p> <p>Data</p> <p>",20,0);
	 }
	 send(sock,value,length,0);
	 if(size==0)
	 {
	   send(sock,"</p>",4,0);
	 }
}
//#endif

