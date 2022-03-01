

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"compare.h"

#define CLIENT_HEAD 0X01
#define SERVER_HEAD 0X02


int debugHexDump(const char * title, unsigned char * addr, int len)
{
#if 1
#if 0
	unsigned int i;
	printf("  [%s] %3d: ",title, len);
	for(i=0;i<len;i++) {
		printf("%02X ",addr[i]);
	}
	printf("\n");
#else	
	unsigned int i;
	unsigned char * s = addr;
	unsigned char * pp = addr;
	unsigned char * endPtr;
	unsigned char  remainder = len % 16;

	pp += len;
	endPtr = pp;

	printf("[%s] %d bytes\n", title, len);
	//printf("Offset      Hex Value                                        Ascii value\n");

	while (s + 16 <= endPtr) {
		printf("0x%04x  ", (unsigned short)(s - addr));
		for (i = 0; i < 16; i++) {
			printf("%02X ", s[i]);
		}
		printf(" ");
		for (i = 0; i < 16; i++) {
			if (s[i] >= 32 && s[i] <= 125) printf("%c", s[i]);
			else printf(".");
		}
		s += 16;
		printf("\n");
	}

	if (remainder) {
		printf("0x%04x  ", (short)(s - addr));

		for (i = 0; i < remainder; i++) {
			printf("%02X ", s[i]);
		}
		for (i = 0; i < (16 - remainder); i++) {
			printf("   ");
		}
		printf(" ");
		for (i = 0; i < remainder; i++) {
			if (s[i] >= 32 && s[i] <= 125) printf("%c", s[i]);
			else printf(".");
		}
		for (i = 0; i < (16 - remainder); i++) {
			printf(" ");
		}
		printf("\n");
	}
#endif	
#endif
	return 0;
}





//checksum 확인
int check_sum(char data[])
{
	int size;
	int check_sum,i;

	size=(data[2]<<8)+data[3]+6;

	
	i=0;
	check_sum=0;
	while(i<size-1){
		check_sum=check_sum^data[i];
		i+=1;     
	}
	if(check_sum!=data[size-1]){
		printf("check_sum=%d, data=%d\n",check_sum,data[size-1]);
		return -1;
	}

	return size;
}


void check_head(int sock, char data[])
{
	int size;
	
	//checksum 확인
	if((size=check_sum(data))==-1)
	{
		return;
	}


	if(data[0]==CLIENT_HEAD)
	{
		//init packet
		if(data[1]==init_command)
		{
			recv_init(sock, data, size);
		}
		
		else
		{
			printf("command error");
		}
		
	}

	else
	{
		printf("head error");
	}
}


void recv_init(int sock, char data[],int size)
{
	int a;
	
	printf("data size : %d\n",size);
	
	debugHexDump("recv_init", (unsigned char*)data, (int)size);
	send_init_respond(sock,data);
    
}

void send_init_respond(int sock, char data[])
{
	int index=0;
	write(sock, data, BUFSIZE);

	
}
