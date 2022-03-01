

int debugHexDump(const char * title, unsigned char * addr, int len);
void init_packet(char message[],int BUFSIZE);

enum command
{
	init_command = 0x01,
};


