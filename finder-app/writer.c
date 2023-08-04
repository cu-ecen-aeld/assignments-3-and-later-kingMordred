#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

int main( int argc, char *argv[] )
{
    FILE *f;
    //puts(argv[1]);
    //puts(argv[2]);
    openlog(NULL, 0, LOG_USER);
    //printf("%d", argc);
    if(argc < 3){
        printf("one or more parameters were not specified");
        syslog(LOG_ERR, "Invalid number of arguments: %d", argc-1);
        exit(1);
    }

    syslog(LOG_DEBUG, "Writing %s to %s", argv[2], argv[1]);
    f = fopen (argv[1] , "w");
    for(int i=0; i<strlen(argv[2]); i++){
        fputc(argv[2][i], f);
    }
    syslog(LOG_DEBUG, "Successfully wrote %s to %s", argv[2], argv[1]);


    //printf("ok");
    return(0);
}