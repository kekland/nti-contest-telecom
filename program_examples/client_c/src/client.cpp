#include "client.h"

Client::Client()
 {
  return;
 }
Client::~Client()
 {
 }


  void Client::start()
   {
      system(__SOCKET_SERVER_PRO "&>/dev/null &");
//      shm=new shmipc();
//      this->shm.open();
   }
    
   void Client::stop()
    {
     shm.write_cs((int)'S',0);
    }
    void Client::nope()
    {
//     shm.nope();
    }

void Client::quit()
 {
     stop();
     sleep(1);
     shm.write_cs((int)('Q'),0);
     sleep(1);
  }

void Client::left(int speed)
     { shm.write_cs((int)'L',speed); }
void Client::right(int speed)
     { shm.write_cs((int)'R',speed); }

void Client::readstatus()
 {
     shm.read_dp(&dx,&pos);
     return;
  }
int Client::getDx()
{
     readstatus();
     return dx;
}
int Client::getPos()
{
     readstatus();
     return pos;
}    

bool Client::ifMovingRight()
{
    if (pos == __TCP_POSITION_MOVING_RIGHT)
      return true;
     else
      return false;
}
bool Client::ifMovingLeft()
{
    if (pos == __TCP_POSITION_MOVING_LEFT)
      return true;
     else
      return false;
}
bool Client::ifPositionRight()
{
    if (pos == __TCP_POSITION_RIGHT)
      return true;
     else
      return false;
}
bool Client::ifPositionLeft()
{
    if (pos == __TCP_POSITION_LEFT)
      return true;
     else
      return false;
}


