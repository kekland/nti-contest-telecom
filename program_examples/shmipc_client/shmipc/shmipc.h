#ifndef __SHMIPC_H__
#define __SHMIPC_H__
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define SHARED_MEMORY_OBJECT_NAME "my_shared_memory"
#define SHARED_MEMORY_OBJECT_SIZE 50
#define SHM_CREATE 1
#define SHM_PRINT  3
#define SHM_CLOSE  4

class shmipc
{
private:
    int shm;
    char* addr;

public:
     shmipc();
     ~shmipc();
     void read_dp(int* dx,int* pos);
     void read_cs(int* control,int* speed);
     void write_dp(int dx,int pos);
     void write_cs(int control,int speed);

};
#endif
