A very naive keylogger written in C.
Main file is logger.c and it needs to be compiled by running makefile.
The output program then needs to be run using sudo command such as 

            sudo ./logger

This is because logger.c opens the keyboard file for reading and it requires 
super user priviliges to so do. 
