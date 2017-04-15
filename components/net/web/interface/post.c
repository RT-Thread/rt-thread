#include "../httpd.h"
/**************************************
*author: Jone.Chen  <yuhua8688@tom.com>
*License:LGPL
***************************************/
extern  int add_cgi_1,add_cgi_2;

void processPost(int sock,char *name,char * value){
	//comset.html
	//unsigned char tmp=0;
	if(strncmp(name,"ck",2)==0){
		if(strncmp(value,"on",2)==0)
		{ 
			send(sock,"<p>check box on</p>",19,0);
		}
	}
	else if(strncmp(name,"text",4)==0){
			send(sock,"<p>",3,0);
			send(sock,value,rt_strlen(value),0);
			send(sock,"</p>",4,0);
	}
	else if(strncmp(name,"txt1",4)==0){
			add_cgi_1=atoi(value);
	}
	else if(strncmp(name,"txt2",4)==0){
			add_cgi_2=atoi(value);
	}		
	
					 
}

