/*********************************************************
MD5加密常用字符
7a57a5a743894a0e admin(16位MD5小写加密)
972130B75066C825 ADMIN(16位MD5大写加密)
21232f297a57a5a743894a0e4a801fc3 admin(32位MD5小写加密)
73ACD9A5972130B75066C82595A1FAE3 ADMIN(32位MD5大写加密)
49ba59abbe56e057 123456(16位MD5小写加密)
e10adc3949ba59abbe56e057f20f883e 123456(32位MD5小写加密)
469e80d32c0559f8 admin888(16位MD5小写加密)
2299413865C28A35 ADMIN888(16位MD5大写加密)
7fef6171469e80d32c0559f88b377245 admin888(32位MD5小写加密)
A1F63A962299413865C28A3593D359B0 ADMIN888(32位MD5大写加密)
*********************************************************/

#ifndef _MD5_H_
#define _MD5_H_

typedef unsigned char * POINTER;  
typedef unsigned long int UINT4;  

typedef struct {  
    UINT4 state[4];				/* state (ABCD) */  
    UINT4 count[2];				/* number of bits, modulo 2^64 (lsb first) */  
    unsigned char buffer[64];	/* input buffer */  
} MD5_CTX;  
  
void MD5_Init(MD5_CTX *context);  
void MD5_Update(MD5_CTX *context, unsigned char *input, unsigned int inputLen);  
void MD5_Final(unsigned char digest[16], MD5_CTX *context);  
void MD5_String(unsigned char digest[16],char *string);  

#endif
