# import java.net.*;
# import java.io.*;
# import java.util.*;

import shlex,subprocess
import time
import os
import struct
import ctypes

class shmipc:
#    __f
#    __data
    def open(self):
     self.__f = open("/dev/shm/my_shared_memory","rb+")     
    def close(self):
     self.__f.close()

    def read_dx(self):
     self.__f.seek(0,0)
     self.__data = self.__f.read(8);
     return struct.unpack_from('h',self.__data,0)[0]

    def read_pos(self):
     self.__f.seek(0,0)
     self.__data = self.__f.read(8);
     return struct.unpack_from('h',self.__data,4)[0]

    def write(self,command,speed):
      self.__f.seek(8,0)
      buffer2=struct.pack("ii",command,speed);
      self.__f.write(buffer2)
#      self.__f.seek(16,0)
#      buffer2=struct.pack("ii",0,0);
#      self.__f.write(buffer2)

    def nope(self):
      self.__f.seek(16,0)
      buffer2=struct.pack("ii",0,0);
      self.__f.write(buffer2)
	