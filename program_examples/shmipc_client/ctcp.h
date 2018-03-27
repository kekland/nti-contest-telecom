#ifndef __TCP_H__
#define __TCP_H__

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include "tcp_proto.h"

//#define SERVER_ADDR     "10.12.12.5"
#define SERVER_NAME     "rad"

class CClient
{
private:
    struct PacketIn {
	TCP_STATUS_STRUCT status;
	void deserialize(unsigned char *data, unsigned int len) {
	    memcpy(this, data, len-CRC_SIZE);
	}
    };
    struct PacketOut {
	TCP_CONTROL_STRUCT control;
	unsigned int serialize(unsigned char *data) {
	    unsigned int len = sizeof(PacketOut);
	    memcpy(data, this, len);
	    return len;
	}
    };
    
    PacketIn packetIn;
    PacketOut packetOut;
    unsigned char Buffer[MAX_BUFF_SIZE];
    bool flConnected;
    int sockFd;
    socklen_t clientLen;
    struct sockaddr_in servAddr;
    unsigned int crc_table[256];
    void init_crc32_table();
    unsigned int crc_32(unsigned char *buf, unsigned int size);
    int in_data(unsigned char *data, unsigned int len);
    unsigned int out_data(unsigned char *data, unsigned int len);
    int hostname_to_ip(const char* host,char* ip);
public:
    char SERVER_ADDR[255];
    bool ClientThreadDone;
    TCP_CONTROL_STRUCT Control;
    TCP_STATUS_STRUCT Status;
    
    CClient();
    ~CClient();
    int clientStart();
    int sendCommand();
    int Close();
};

#endif
