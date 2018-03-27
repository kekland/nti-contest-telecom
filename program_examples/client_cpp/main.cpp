#include <iostream>
#include <thread>
#include <csignal>
#include <unistd.h>
#include <fcntl.h>
#include "shmipc.h"
#include "client.h"

//using namespace std;

//bool g_ExitDone;

int main(int argc, char *argv[])
{

    Client control;
    int curSpeed;
    int maxSpeed;
    int cmd;
    int position;
    int dx;

    double pid_kp = 1.0;
    double pid_ki = 0.0;
    double pid_kd = 0.0;
    int pid_integral = 0;
    int pid_integral_range = 30;
    int pid_prev_error;

    data = 10;
    control.start();
    control.left(data);

    printf("Client intialized");
    while (true)
    {
        control.readstatus();
        printf("dx: %d pos: %d\n", control.getDx(), control.getPos());

        if (curSpeed > 0 && !control.ifPositionRight())
        {
            control.right(curSpeed);
        }
        if (curSpeed < 0 && control.ifPositionLeft())
        {
            control.left(curSpeed);
        }

        curSpeed = dx * pid_kp + pid_integral * pid_ki + (dx - pid_prev_error) * pid_kd;

        if(abs(dx) < pid_integral_range) {
            pid_integral += dx;
        }
        else {
            pid_integral = 0;
        }

        usleep(1000);
    }
}
