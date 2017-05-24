#!/usr/bin/python           # This is server.py file

import socket               # Import socket module
from Phone_cmd_Pub import CMD


s = socket.socket()         # Create a socket object
host = ""                   # Get local machine name
port = 2004                # Reserve a port for your service.
s.bind((host, port))        # Bind to the port

s.listen(5)                 # Now wait for client connection.
while True:
   c, addr = s.accept()     # Establish connection with client.
   print 'Got connection from', addr
   data = c.recv(1024)
   print(data)
   CMD(data)
   c.send('Thank you for connecting')
   c.close()     
