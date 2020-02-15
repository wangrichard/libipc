# This is a workable ipc implementation using socket interface.
It relies on json-c library.  

How to use:  
* On desktop Linux, install libjson-c  
  Download from https://github.com/json-c/json-c  
  cmake .  
  ./configure --prefix=/usr  
  make  
  sudo make install  
* Download libipc code and build it.  
  make  
  sudo make install  
  make example  
* Run the examples  
  ./example/x86_64-linux-gnu-release/server  
  ./example/x86_64-linux-gnu-release/client  
  You will see json message exchanged between client and server like below:  
Server side:  
server cb.  
status: 200  
operation: get  
param: 0  
param2: 1  
param3: bang  
  
Client side:  
client cb.  
status: 200  
operation: get  
param: 0  
param2: 1  
param3: bang  

