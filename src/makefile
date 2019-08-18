CC=gcc
CFLAGS=-I
ZAP=-pedantic -Wall -ansi

logger: logger.c ./keycodes/KeyCodeToASCII.c
	$(CC) $(ZAP) logger.c ./keycodes/KeyCodeToASCII.c -o logger

#LogListenner: LoggerListenner.c
#	$(CC) $(ZAP) LoggerListenner.c -o LogListenner
