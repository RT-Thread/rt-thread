#include "../httpd.h"
/**************************************
*author: Jone.Chen  <yuhua8688@tom.com>
*License:LGPL
***************************************/

/*
#cgi example
i file.inc
c d 1 <TD><INPUT TYPE=TEXT NAME=pw SIZE=10 MAXLENGTH=10 VALUE="%s"></TD></TR>
.
*/


int add_cgi_1=0,add_cgi_2=0,add_cgi;

void process_cgi(int sock,char cmd,char param,char *data,int len){
	char *tmpbuff;
	tmpbuff=rt_malloc(len+10);
	rt_memset(tmpbuff,0,len+10);
	rt_memcpy(tmpbuff,data,len);
	switch(cmd){
	case 't':
		{
			switch(param)
			{
			 case '2':
			 add_cgi=add_cgi_1+add_cgi_2;
			 sprintf(tmpbuff,tmpbuff,add_cgi);
			 break;
	
			}
		}
		break;	
	 }
  len=strlen(tmpbuff);
  len=send(sock,tmpbuff,len,0);
  rt_free(tmpbuff);
  if(len<0)
  {
   	len=len+100;
  }
}

