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
	switch(cmd){
	case 't':
		{
			switch(param)
			{
			 case '2':
			 add_cgi=add_cgi_1+add_cgi_2;
			 sprintf(data,data,add_cgi);
			 break;
	
			}
		}
		break;	
	 }
  len=strlen(data);
  len=send(sock,data,len,0);
}

