# import java.net.*;
# import java.io.*;
# import java.util.*;

import shlex,subprocess
import time
import os
from shmipc import shmipc 

class Client:
    __SOCKET_SERVER_PRO = "./socket_server";

    __TCP_POSITION_MOVING_LEFT=1;
    __TCP_POSITION_MOVING_RIGHT=2;
    __TCP_POSITION_LEFT=3;
    __TCP_POSITION_RIGHT=4;

    __dx=0
    __pos=0

#    __execute;
    def start(self):
#      self.__execute= subprocess.Popen([self.__SOCKET_SERVER_PRO],shell=True)
#      subprocess.call([self.__SOCKET_SERVER_PRO],shell=True)
#     try:
#      pid=os.fork()
#     except OSError.e:
#      sys.exit(1)
#     if pid==0:
#      self.__execute=subprocess.call(self.__SOCKET_SERVER_PRO+" &",shell=True)
#      self.__execute=subprocess.Popen([self.__SOCKET_SERVER_PRO,'-c'])
      subprocess.Popen([self.__SOCKET_SERVER_PRO,'-c'],stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
#     else:
      self.__shm=shmipc()
      self.__shm.open()
#	print "started"
    def stop(self):
     self.__shm.write(ord('S'),0);

    def nope(self):
     self.__shm.nope();
     self.__shm.close()
     self.__shm.open()

    def quit(self):
     self.stop();
     time.sleep(1)
     self.__shm.write(ord('Q'),0);
#     self.__shm.close()
#     self.__shm.open()
     time.sleep(1)
     self.__execute.kill()

    def left(self, speed):
     self.__shm.write(ord('L'),speed);
#     self.__shm.close()
#     self.__shm.open()
    def right(self, speed):
     self.__shm.write(ord('R'),speed);
#     self.__shm.close()
#     self.__shm.open()


    def readstatus(self):
     self.__dx=self.__shm.read_dx()
     self.__pos=self.__shm.read_pos()
     return 1

    def getDx(self):
#     return self.__dx;
     return self.__shm.read_dx()
    def getPos(self):
#     return self.__pos;
     return self.__shm.read_pos()
    
    def ifMovingRight(self):
     if self.__pos == self.__TCP_POSITION_MOVING_RIGHT :
      return 1
     else:
      return ''

    def ifMovingLeft(self):
     if self.__pos == self.__TCP_POSITION_MOVING_LEFT :
      return 1
     else:
      return ''

    def ifPositionRight(self):
     if self.__pos == self.__TCP_POSITION_RIGHT :
      return 1
     else:
      return ''

    def ifPositionLeft(self):
     if self.__pos == self.__TCP_POSITION_LEFT :
      return 1
     else:
      return ''
