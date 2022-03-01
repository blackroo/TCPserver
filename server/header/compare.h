
#define BUFSIZE 512

int debugHexDump(const char * title, unsigned char * addr, int len);
int check_sum(char data[]);
void check_head(int sock, char data[]);
void recv_init(int sock, char data[], int size);
void send_init_respond(int sock, char data[]);


enum command
{
	init_command = 0x01,
};

