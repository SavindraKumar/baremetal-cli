# Cli baremethdal
Often we require command line interface to configure or debug our baremetal
embedded system. This is the application where we can debug and control embedded system
application over difference physical interface (RS232,RS485,UDP,TCP/IP) to our main application.
Drivers for physical interface must be included with the application/

## How to use the project

There are two files in the Command line interface:
1. cli.c(Implements the functions for cli)
2. cli.h(Prototypes for cli )

Note: Echo on terminal should be enable to see the commands because this code do not send
the character typed back to terminal.

Application for demo is written in app.c and main.c intialise the cli and application.
Application may be splitted into multiple files(depending upon requirements) and 
header files for applications file has to be included in cli.c and application function name 
for particular commands must be included in CommandList[] array 

The project is tested on Linux Environment. In actual case any baremetal environment can be taken 
with RS232 ,RS485 etc. physical interface. Main application can be modified as per requirements.

## How to build the project
Project can be build using eclipse with MINGW compiler.

## License

MIT

**Free Software, Hell Yeah!**
