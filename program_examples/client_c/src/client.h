#ifndef __CLIENT_H__
#define __CLIENT_H__
#define __SOCKET_SERVER_PRO  "./socket_server"
#define __TCP_POSITION_MOVING_LEFT 1
#define __TCP_POSITION_MOVING_RIGHT 2
#define __TCP_POSITION_LEFT 3
#define __TCP_POSITION_RIGHT 4
#include <stdlib.h>
#include "shmipc.h"

class Client
{
 private:
    shmipc shm;
    int dx;
    int pos;

 public:
    Client();
    ~Client();
    void start();
    void stop();
    void nope();
    void quit();
    void left(int speed);
    void right(int speed);
    void readstatus();	
    int getDx();
    int getPos();
    bool ifMovingRight();
    bool ifMovingLeft();
    bool ifPositionRight();	
    bool ifPositionLeft();

};
#endif
