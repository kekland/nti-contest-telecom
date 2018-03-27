# import java.net.*;
# import java.io.*;
# import java.util.*;

import time
from Client import Client


client = Client()
client.start()
#client.readstatus()
client.right(10)
# client.stop()
# exit()
client.nope()
client.readstatus()
time.sleep(0.1)

# while not client.readstatus():
# print ("!");

# exit


dx=2
status = 1
rl=1

while (1):
    dx=client.getDx()
    print ("dx:")
    print (dx)

#    client.right(10)
    if rl == 1:
     client.right(10)
    else:
     client.left(10)

    if client.ifPositionLeft():
     print ("to right")
     client.right(10)
     rl=1
    if client.ifPositionRight() :
     print ("to left")
     client.left(10)
     rl = -1


    client.nope()

#    time.sleep(1)
#    client.stop()


#    client.nope()
    client.readstatus()
    time.sleep(0.01)


time.sleep(1)
client.stop()
client.quit()

