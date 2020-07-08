// using utmplib.c as buffering

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
#include <utmp.h>
#include <unistd.h>

#define SHOWHOST

void show_info(struct utmp *);

int main()
{
    struct utmp * utbufp, * utmp_next();
    
    if (utmp_open(UTMP_FILE)==-1){
        perror(UTMP_FILE);
        exit(1);
    }
    while((utbufp = utmp_next())!=((struct utmp *)NULL))
        show_info(utbufp);
    utmp_close();
    return 0;
}

/* show_info(), display contents of utmp stru
*/
void show_info(struct utmp *utbufp){
    if(utbufp->ut_type != USER_PROCESS) return; //skip non-user
    printf("% -8.8s", utbufp->ut_name);
    printf(" ");
    printf("% -8.8s", utbufp->ut_line);
    printf(" ");
    show_time(utbufp->ut_time);
    #ifdef SHOWHOST
    if (utbufp->ut_host[0] != '\0')
        printf("(%s)", utbufp->ut_host);
    #endif
    printf("\n");
}