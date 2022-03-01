
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include"packet.h"

#define IP_ADDR "127.0.0.1"
#define PORT 5000
#define BUFSIZE 512

void error_handling(char *message);

int main(int argc,char**argv)
{
	int sock;
	int i;
	pid_t pid;
	char message[BUFSIZE];
	int str_len, recv_len, recv_num;
	struct sockaddr_in serv_addr;


	sock=socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(IP_ADDR);
	serv_addr.sin_port=htons(PORT);

	if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("connect() error!");
		
	
	while(1){
		fputs("send message input(q to quit): ", stdout);
		fgets(message, BUFSIZE, stdin);
		
		
		
		if(!strcmp(message,"q\n")){
			shutdown(sock, SHUT_WR);
			close(sock);
			exit(0);
		}

		init_packet(message,BUFSIZE);
		write(sock, message, BUFSIZE);


		//응답받기
		int str_len = read(sock,message,BUFSIZE);
		if(str_len ==0){
			exit(0);
		}
		//message[str_len]=0;
		//printf("recv message : %s\n",message);
		
	}
	

	close(sock);
	return 0;
}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}



