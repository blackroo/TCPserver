
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"packet.h"

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




void init_packet(char message[],int BUFSIZE)
{
	int index=0;
	int check_sum=0;
	int i=0;
	memset(message,0,BUFSIZE);


	message[index++]=CLIENT_HEAD;
	message[index++]=init_command;

	//size
	message[index++]=0x00;	
	message[index++]=0x00;


	//data
	message[index++]=0x04;
	message[index++]=',';


	//size-setting
	message[2]=(index-4)>>8;
	message[3]=(index-4);

	//etc
	message[index++]=0x03;

	//checksum
	while(i<index){
		check_sum=check_sum^message[i];
		i+=1;     
	}

	message[index++]=check_sum;
	

	debugHexDump("init_packet", (unsigned char*)message, (int)index); //20201016
	
}

