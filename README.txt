/**

@mainpage Cli for Baremetal embedded System
@author Savindra Kumar(savindran1989@gmail.com)


Often we require command line interface to configure or debug our baremetal
embedded system. This is the application where we can debug and control embedded system
application over difference physical interface (RS232,RS485,UDP,TCP/IP) to our main application.
Drivers for physical interface must be included with the applicatin/

There are two files in the Command line interface:
1. cli.c(Implements the functions for cli)
2. cli.h(Prototypes for cli )

Application for demo is written in app.c and main.c intialise the cli and application.
Application may be splitted into multiple files(depending upon requirements) and 
header files for applications file has to be included in cli.c and application function name 
for particular commands must be included in CommandList[] array 

The project is tested on Linux Environment
*/