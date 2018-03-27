#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include "shmipc.h"
#include "client.h"

int main(int argc, char *argv[])
{
    Client control;
    int data;
    data=10;
    control.start();
    control.left(data);

    while(1)
    {

	control.readstatus();
	printf("dx: %d pos: %d\n",control.getDx(),control.getPos());
	if(control.ifPositionLeft())
         {
          control.right(data);
         }
        if(control.ifPositionRight())
         {
          control.left(data);      
         }
        usleep(100*1000);
     }
}
