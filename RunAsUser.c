#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 2048

char *fmt = "bash --login -c \"%s\"";
char cmd[MAX + 128] = "";
char buf[MAX];

int main( int argc, char *argv[] )
{
    int i, sum = 0, res = 0;
    uid_t uid , euid;
    uid = getuid();
    euid= geteuid();
    if(setreuid(euid,uid)) perror("setreuid");
    for ( i = 1; i < argc; i++ ) sum += strlen(argv[i]);
    if ( sum + argc > MAX ) {
        puts("Command too long!");
        return -1;
    }
    buf[0] = 0;
    for ( i = 1; i < argc; i++ ) {
        if ( i != 1 ) strcat(buf, " ");
        strcat(buf, argv[i]);
    }
    sprintf(cmd, fmt, buf);
    res = system(cmd);
    //puts(cmd);
    return res;
}
