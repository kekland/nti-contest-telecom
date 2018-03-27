#include <iostream>
#include <thread>
#include <csignal>
#include <unistd.h>
#include <fcntl.h>
#include "ctcp.h"
#include "shmipc.h"

using namespace std;

bool g_ExitDone;

void signalHandler(int signal)
{
    g_ExitDone = true;
}

void clientThreadFunc(CClient &client)
{
    while(client.clientStart()==1)
     {
      if(g_ExitDone)
       break;
      sleep(1);
      
     }
    g_ExitDone = true;
    cout << "Exit client thread..." << endl;
}


int main(int argc, char *argv[])
{
    g_ExitDone = false;
    CClient tcp_client;
    shmipc control;
//    control = new shmipc();
//    control.open()
    
    cout << "Start, server address: " << tcp_client.SERVER_ADDR << ", server port: " << SERVER_PORT << ", exit - Ctrl-C" << endl;
//    exit(1);

// Set signal handler
    std::signal(SIGINT, signalHandler); // Ctrl+C - exit

    std::thread client_thread(clientThreadFunc, std::ref(tcp_client));
    
/*    usleep(100*1000);
    if(g_ExitDone)
     {
      printf("no server .");
//      tcp_client.ClientThreadDone = true;
      client_thread.join();      
      std::thread client_thread(clientThreadFunc, std::ref(tcp_client));
      usleep(100*1000);
//      exit(1);
     }
*/
char cmd[12];
int data;

    for(;;)
     {
       
//        fprintf(stderr,"data ready!\n");
	control.read_cs((int*)cmd,&data);
	
        if(cmd[0]=='Q')
         {
//          fprintf(stderr,"goto exit\n");
          goto EX;
         }
//printf("command: %c speed: %d\n",cmd[0],data);
	switch(cmd[0])
	{
	 case 'L':
    	    tcp_client.Control.command = CMD_MOVE_LEFT; break;
	 case 'R':
    	    tcp_client.Control.command = CMD_MOVE_RIGHT; break;
	 case 'S':
    	    tcp_client.Control.command = CMD_STOP; break;
//	 default: ;
	 
        }
	tcp_client.Control.data=data;
	tcp_client.sendCommand();
//        fprintf(stderr,"sent to server\n");
	control.write_dp(tcp_client.Status.dx,tcp_client.Status.position);
//	control.write_dp(rand()%1000,rand()%4);
       
        if(
/*        abs(tcp_client.Status.dx)<500 
        ||
*/        g_ExitDone
        )
	    break;

      usleep(100*1000);
//          fprintf(stderr,"wait done\n");

     }
goto EX;

    tcp_client.Control.command = CMD_STOP;
    tcp_client.Control.command = CMD_MOVE_RIGHT;
//    tcp_client.Control.command = CMD_MOVE_LEFT;
    tcp_client.Control.data = 1; // 50% speed
//goto SKIP;
    for(;;)
     {
      tcp_client.sendCommand();
/*
      if(tcp_client.Status.position==TCP_POSITION_LEFT)
       tcp_client.Control.command = CMD_MOVE_RIGHT;
      if(tcp_client.Status.position==TCP_POSITION_RIGHT)
*/
//       tcp_client.Control.command = CMD_MOVE_RIGHT;
	
	
	if( tcp_client.Status.position==TCP_POSITION_RIGHT)
	    {

	     tcp_client.Control.command = CMD_MOVE_LEFT;
//	     tcp_client.Control.command = CMD_MOVE_RIGHT;
	     tcp_client.Control.data = 1;
	    printf("found right: %d\n" ,tcp_client.Control.command);

	    }
	if( tcp_client.Status.position==TCP_POSITION_LEFT)
	    {
//	     tcp_client.Control.command = CMD_MOVE_LEFT;
	     tcp_client.Control.command = CMD_MOVE_RIGHT;
	     tcp_client.Control.data = 1;
	    printf("found left: %d\n" ,tcp_client.Control.command);
	    }
printf("move: %d %d\n",tcp_client.Control.command ,tcp_client.Status.dx);

//      tcp_client.Control.data = 1;
//       tcp_client.Control.command = CMD_MOVE_LEFT;
        if(abs(tcp_client.Status.dx)<50 )
         {
          tcp_client.Control.data = 0;
          break;
         }
        
        if(
/*        abs(tcp_client.Status.dx)<500 
        ||
*/        g_ExitDone
        )
	    break;

      usleep(100*1000);
      
     }
//goto EX;
SKIP:
    while(1) {
        tcp_client.sendCommand();
//        tcp_client.clientStart();
        if(abs(tcp_client.Status.dx)<500)
         {
//          tcp_client.Control.data = 0;
          cout << "position: " << tcp_client.Status.position << "dx :" << tcp_client.Status.dx <<"\n";
          fflush(stdout);
          tcp_client.Control.data = 1;

          if(abs(tcp_client.Status.dx)<150)
//          if(abs(tcp_client.Status.dx)<100)
            tcp_client.Control.data = 0;
        
          if(tcp_client.Status.dx<0/* && tcp_client.Status.dx>-500*/)
	    tcp_client.Control.command = CMD_MOVE_RIGHT;
//	else
          if(tcp_client.Status.dx>0/* && tcp_client.Status.dx<500*/)
	    tcp_client.Control.command = CMD_MOVE_LEFT;
          }
        else
         {
//          tcp_client.Control.command = CMD_STOP;
          tcp_client.Control.data = 0;
         }

	if( tcp_client.Status.position==TCP_POSITION_RIGHT)
	    {
	     tcp_client.Control.command = CMD_MOVE_LEFT;
	     tcp_client.Control.data = 1;
	    }
	if( tcp_client.Status.position==TCP_POSITION_LEFT)
	    {
	     tcp_client.Control.command = CMD_MOVE_RIGHT;
	     tcp_client.Control.data = 1;
	    }
	
	cout << "position: " << tcp_client.Status.position << "dx :" << tcp_client.Status.dx <<"\n";
         
//        tcp_client.Status.
	if(g_ExitDone)
	    break;
	usleep(100 * 1000);
//	usleep(1 * 1000);
    }
EX:
fprintf(stderr,"in exit\n");
    tcp_client.ClientThreadDone = true;
fprintf(stderr,"in exit2\n");
    std::terminate();
    client_thread.join();
fprintf(stderr,"in exit3\n");

    cout << "Bye!" << endl;
    return 0;
}
