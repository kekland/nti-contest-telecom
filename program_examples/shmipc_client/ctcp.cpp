#include "ctcp.h"

using namespace std;


int CClient::hostname_to_ip(const char * hostname , char* ip)
{
	struct hostent *he;
	struct in_addr **addr_list;
	int i;
	if ( (he = gethostbyname( hostname ) ) == NULL) 
	{
		// get the host info
		herror("gethostbyname");
		return 1;
	}
//fprintf(stderr,"here \n");

	addr_list = (struct in_addr **) he->h_addr_list;
	
	for(i = 0; addr_list[i] != NULL; i++) 
	{
		//Return the first one;
		strcpy(ip , inet_ntoa(*addr_list[i]) );
		return 0;
	}
	return 1;
}


CClient::CClient()
{
    ClientThreadDone = false;
    flConnected = false;
//berng
    hostname_to_ip(SERVER_NAME,SERVER_ADDR);
    
    init_crc32_table();
}

CClient::~CClient()
{
}

void CClient::init_crc32_table(void)
{
    unsigned int crc;
    int i, j;

    for(i=0; i<256; i++) {
        crc = i;
        for(j=0; j<8; j++)
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
        crc_table[i] = crc;
    }
}

// CRC32
unsigned int CClient::crc_32(unsigned char *buf, unsigned int size)
{
    unsigned int crc;

    crc = 0xFFFFFFFFUL;
    while(size--)
        crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);

    return crc ^ 0xFFFFFFFFUL;
}

int CClient::in_data(unsigned char *data, unsigned int len)
{
    unsigned int sz = len-CRC_SIZE;
    unsigned int crc;
    if(len <= CRC_SIZE || sz != sizeof(PacketIn))
        return -1;
    crc = *(unsigned int*)(data+len-CRC_SIZE);
    if(crc_32(data, sz) != crc)
        return -2;
    packetIn.deserialize(data, len);
    return 0;
}
unsigned int CClient::out_data(unsigned char *data, unsigned int sz)
{
    unsigned int len;
    if(sz < sizeof(PacketOut)+CRC_SIZE)
	return -1;
    len = packetOut.serialize(data);
    
    *(unsigned int*)(data+len) = crc_32(data, len);
    return len+CRC_SIZE;
}


int CClient::sendCommand()
{
    unsigned char buff[MAX_BUFF_SIZE];
    unsigned int len = MAX_BUFF_SIZE;
    int ret;
    
//berng    printf("send command\n");
    if(flConnected) {
	packetOut.control = Control;
	ret = out_data(buff, len);
	if(ret > 0)
//	    sendto(connFd, buff, ret, 0, (struct sockaddr *)&clientAddr, clientLen);
	    sendto(sockFd, buff, ret, 0, (struct sockaddr *)&servAddr, sizeof(servAddr));
	else {
	    printf("Some error!\n");
	}

    }
    return 0;
}

int CClient::Close()
{
    if(flConnected) {
	close(sockFd);
	flConnected = false;
    }
    return 0;
}

int CClient::clientStart()
{
    int ret, optval, num;
    struct timeval read_timeout;
    unsigned char buff[MAX_BUFF_SIZE];
    unsigned char speed, dir;
    
    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockFd < 0) {
        cout << "ERROR! socket()" << endl;
    	return 1;
    }
    optval = 1;
    ret = setsockopt(sockFd, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval));

    read_timeout.tv_sec = 0;
    read_timeout.tv_usec = 100;
    setsockopt(sockFd, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof read_timeout);
    
    std::memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    
    servAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    servAddr.sin_port = htons(SERVER_PORT);
    
    
    ret = connect(sockFd, (struct sockaddr *)&servAddr, sizeof(servAddr));
    if(ret != 0) {
        cout << "ERROR! connect() [code=" << errno << "]" << endl;
        return 1;
    }
    cout << "Connected" << endl;
    
    flConnected = true;
    while(1) {
	if(ClientThreadDone) {
    	    Close();
	    return 0;
    	}
        num = recvfrom(sockFd, buff, MAX_BUFF_SIZE, 0, NULL, NULL);
        if(num < 0 ) {
    	    if(errno != EAGAIN) {
        	Close();
            	cout << "ERROR! recvfrom()=" << errno << endl;
            	break;
            }
        }
        if(num == 0) {
    	    Close();
            cout << "Client connection closed" << endl;
            break;
        }
        if(num > 0) {
//berng    	    cout << "received data=" << num << endl;
    	    ret = in_data(buff, num);
    	    if(ret == 0) {
    		Status = packetIn.status;
//berng        	cout << "State=" << (int)Status.state;
        	switch(Status.state) {
        	    case TCP_STATE_UNKNOWN:
//berng        		cout << " TCP_STATE_UNKNOWN";
        		break;
        	    case TCP_STATE_DISABLED:
//berng        		cout << " TCP_STATE_DISABLED";
        		break;
        	    case TCP_STATE_STOPPED:
//berng        		cout << " CMD_TCP_STATE_STOPPED";
        		break;
        	    case TCP_STATE_MOVE:
//berng        		cout << " CMD_TCP_STATE_MOVE";
        		break;
        	    default:
        		cout << " Unknown";
        		break;
        	}
//berng        	cout << endl;
//berng        	cout << "Position=" << (int)Status.position;
        	switch(Status.position) {
        	    case TCP_POSITION_UNKNOWN:
//berng        		cout << " TCP_POSITION_UNKNOWN";
        		break;
        	    case TCP_POSITION_MOVING_LEFT:
//berng        		cout << " TCP_POSITION_MOVING_LEFT";
        		break;
        	    case TCP_POSITION_MOVING_RIGHT:
//berng        		cout << " TCP_POSITION_MOVING_RIGHT";
        		break;
        	    case TCP_POSITION_LEFT:
//berng        		cout << " TCP_POSITION_LEFT";
        		break;
        	    case TCP_POSITION_RIGHT:
//berng        	        cout << " TCP_POSITION_RIGHT";
        	        break;
        	    default:
        		cout << " Unknown";
        		break;
        	}
//berng        	cout << endl;
//berng        	cout << "Speed=" << (int)Status.speed << endl;;
//berng        	cout << "dx=" << (int)Status.dx << endl;;
    	    }
    	    else {
        	if(ret == -1)
        	    cout << "ERROR! Data length problem, received: " << num << " bytes, need: " << sizeof(PacketIn) << " data + " << CRC_SIZE << " crc" << endl;
        	if(ret == -2)
        	    cout << "ERROR! CRC mismatch" << endl;
    	    }
        }
    }
    
    return 0;
}
