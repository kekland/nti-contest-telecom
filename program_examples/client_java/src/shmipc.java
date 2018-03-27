import java.net.*;
import java.io.*;
import java.math.*;
import java.nio.*;
import java.nio.channels.*;
import java.nio.charset.*;

class shmipc {
    private RandomAccessFile f;
    private MappedByteBuffer buffer;

    public boolean open() throws Exception
    {
       this.f = new RandomAccessFile("/dev/shm/my_shared_memory", "rw");
       this.buffer = f.getChannel().map(FileChannel.MapMode.READ_WRITE, 0, f.length());
       this.buffer.order(ByteOrder.LITTLE_ENDIAN);
       return true;
    }

    public boolean close() throws Exception
    {
     this.f.close();
     return true;
    }
    
    public void write(int command, int speed)
     {
      this.buffer.position(8);
      this.buffer.putInt(command);
      this.buffer.position(12);
      this.buffer.putInt(speed);
     }

    public int read_dx()
     {
      this.buffer.position(0);
      return this.buffer.getInt();
     }

    public int read_pos()
     {
      this.buffer.position(4);
      return this.buffer.getInt();
     }


}
