/* read from UTMP file,
 * then show results
 */

#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define SHOWHOST

void show_info(struct utmp *utbufp);

int main(){
    struct utmp current_record;  //read info to this
    int utmpfd; //file descriptor
    int reclen = sizeof(current_record);    //record length

    if((utmpfd = open(UTMP_FILE, O_RDONLY))==-1){
        perror(UTMP_FILE);  //UTMP_FILE is in utmp.h
        exit(1);
    }

    while(read(utmpfd, &current_record, reclen) == reclen){
        show_info(&current_record);
    }
    close(utmpfd);
    return 0;
}

void show_time(long timeval){   //convert time to human readble form
    char *cp;
    cp = ctime(&timeval);
    printf("%12.12s", cp+4);    //no month
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