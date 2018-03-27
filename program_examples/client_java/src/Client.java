import java.net.*;
import java.io.*;
import java.util.*;

class Client{
    private int TCP_POSITION_MOVING_LEFT=1;
    private int TCP_POSITION_MOVING_RIGHT=2;
    private int TCP_POSITION_LEFT=3;
    private int TCP_POSITION_RIGHT=4;
    private String SOCKET_SERVER_PRO="./socket_server";

    private shmipc shm;
    private Process execute;

    private long dx;
    private long pos;

    public void start() throws Exception{
        execute=new ProcessBuilder(SOCKET_SERVER_PRO).start();
//        System.out.println(SOCKET_SERVER_PRO);
        shm = new shmipc();
        shm.open();
    }

    public void left(int speed) throws Exception{
      shm.write((int)'L',speed);
    }
    public void right(int speed) throws Exception{
      shm.write((int)'R',speed);
    }
    public void stop() throws Exception{
      shm.write((int)'S',0);
    }
    public void quit() throws Exception{
      stop();
      Thread.sleep(1000);
      shm.write((int)'Q',0);
      Thread.sleep(1000);
      execute.destroy();
      shm.close();
    }

    public long getDx()
    {
     return dx;
    }

    public boolean ifMovingRight()
    {
     if(pos==TCP_POSITION_MOVING_RIGHT)
      return true;
     else
      return false;
    }

    public boolean ifMovingLeft()
    {
     if(pos==TCP_POSITION_MOVING_LEFT)
      return true;
     else
      return false;
    }

    public boolean ifPositionRight()
    {
     if(pos==TCP_POSITION_RIGHT)
      return true;
     else
      return false;
    }

    public boolean ifPositionLeft()
    {
     if(pos==TCP_POSITION_LEFT)
      return true;
     else
      return false;
    }

    public boolean readstatus()
     throws Exception{
      dx=shm.read_dx();
      pos=shm.read_pos();
      return true;
    }
}
