import java.net.*;
import java.io.*;
import java.math.*;

class example {

public static void main(String args[]) 

throws Exception{

Client client=new Client();
int speed=1;
int dir=1;

client.start();
client.left(1);

Thread.sleep(1000);


client.right(speed);


for(int i=0;i<10000;i=0/*i++*/)
{
    while(!client.readstatus())
     {
      System.out.println("not rady");
      Thread.sleep(1000);
      client.readstatus();
     }


 if(client.ifPositionRight())
  {
   speed=1;
   client.left(speed);
  }
 if(client.ifPositionLeft())
  {
   speed=1;
   client.right(speed);
  }
 Thread.sleep(10);

}

 client.quit();
 client.stop();
}



}
