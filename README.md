# Riot-OS UDP Echo Server


This is a simple UDP Echo Server.
There are two server instances and a client instance one of the echo server instances being delaying the received message by 1 second. 

## Getting Started

Riot-OS is required to run this.

### Prerequisites

A C compiler is required to compile the program.

To install Riot-OS

```
git clone git://github.com/RIOT-OS/RIOT.git # assumption: git is pre-installed
git checkout <LATEST_RELEASE>
cd RIOT
./dist/tools/tapsetup/tapsetup              # create virtual Ethernet
                                            # interfaces to connect multiple
                                            # RIOT instances
```

### Installation
Go into examples

```
cd examples
```

Clone this repo 

```
git clone https://github.com/harunzengin/riot_udp_echo_server.git
```
Cd into the project folder
```
cd riot_udp_echo_server 
```
Build the project

```
make
```

## Running
You need to run the following on two different terminal windows:

### Server 

Run the riot process
```
./bin/native/udp.elf tap0
```
After successfully running the riot process, run the simple echo server with 
```
udps
```
Or to run the server with 1s delay,

```
udpd

```
### Client

Run the riot process
```
./bin/native/udp.elf tap1
```
Run the client with 
```
client <messageToBeSent>
```
This will continously send your message and wait for the reply for 2 seconds, if the reply is not present, it will throw a timeout error and continue sending messages. 
Else, will print the reply message. 

## References

* [RIOT_OS Tutorials](https://github.com/RIOT-OS/Tutorials/tree/master/task-06) - Riot Tutorials on Github
* [RIOT API Reference](https://riot-os.org/api/group__net__sock__udp.html) - Riot API Reference 
