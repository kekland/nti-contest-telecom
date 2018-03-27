#include "shmipc.h"    
using namespace std;

shmipc::shmipc()
 {
    int len;
    int cmd;
    int mode = 0;
    char initcode[]="1234567890123456789012345678901234567890";
    mode = O_CREAT;
    cmd = SHM_CREATE;
    this->shm = shm_open(SHARED_MEMORY_OBJECT_NAME, mode|O_RDWR, 0777); 
    this->addr = (char*)mmap(0, SHARED_MEMORY_OBJECT_SIZE+1, PROT_WRITE|PROT_READ, MAP_SHARED, this->shm, 0);
    ftruncate(this->shm,SHARED_MEMORY_OBJECT_SIZE+1);
    memcpy(this->addr,initcode,40);

    munmap(this->addr, SHARED_MEMORY_OBJECT_SIZE);
    close(this->shm);
    this->shm = shm_open(SHARED_MEMORY_OBJECT_NAME, mode|O_RDWR, 0777); 
    this->addr = (char*)mmap(0, SHARED_MEMORY_OBJECT_SIZE+1, PROT_WRITE|PROT_READ, MAP_SHARED, this->shm, 0);
    return;
    
 }
shmipc::~shmipc()
 {
  munmap(this->addr, SHARED_MEMORY_OBJECT_SIZE);
  close(this->shm);
 }


void shmipc::read_cs(int* command,int* speed)
 {
  memcpy(command, this->addr+sizeof(int)*2, sizeof(int));
  memcpy(speed, this->addr+sizeof(int)*3,sizeof(int));
 }

void shmipc::read_dp(int* dx,int* pos)
 {
  memcpy(dx, this->addr, sizeof(int));
  memcpy(pos, this->addr+sizeof(int),sizeof(int));
 }



void shmipc::write_dp(int dx,int pos)
 {
  memcpy(this->addr, &dx, sizeof(dx));
  memcpy(this->addr+sizeof(dx), &pos, sizeof(pos));
 }

void shmipc::write_cs(int command,int speed)
 {
  memcpy(this->addr+sizeof(int)*2, &command, sizeof(int));
  memcpy(this->addr+sizeof(int)*3, &speed, sizeof(int));
 }
