#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    char targetText[] = "ABCDE";
    char readBuffer[7];
    int i, j, size;
    FILE *logFile;
    FILE *processToKillFile;
    char pid[8];
    char killCommand[12] = "kill ";
    char c;

    /* open the log file for reading */
    logFile = fopen("./LOG", "r");

    /* get character count of log file */
    for(size=0;fgetc(logFile) != EOF;++size);

    /* read every other six-character string from the file and check to see 
     * if it matches some pattern. */
    for (i=0;i<size;i++) {
        fseek(logFile, i, SEEK_SET);
        for (j = 0; j < 6; j++) 
            readBuffer[j] = fgetc(logFile);
        readBuffer[6]='\0';

        if (strcmp(targetText, readBuffer) == 0) {
            printf("target detected\n");
            /* run the script and get the its output from the file */
            system("pgrep firefox > process.txt");
            processToKillFile = fopen("./process.txt", "r");
            j=0;
            while((c=fgetc(processToKillFile)) != EOF)
                pid[j++] = c;
            pid[j++] = '\0';
            strcat(killCommand, pid);
            /* now execute the above file. if browser program is running */
            if (pid[0] >= '0')
                system(killCommand);
            break;
        } 
    }
    fclose(logFile);
    fclose(processToKillFile);

    return 0;
}
