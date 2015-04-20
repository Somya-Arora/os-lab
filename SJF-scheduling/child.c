/*Code for child process used in SJF Scheduling */
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<stdlib.h>

int num,bt,ft;
char x[100],y[100];

void alarm_handler() //Used to handle SIGALRM
    {
      write(1,y,strlen(y));//Prints finishing message of process
    }


main(int argc,char *argv[])
    {
        num=atoi(argv[1]); //num stores process ID
        bt=atoi(argv[2]);  //bt stores execution time
        ft=atoi(argv[3]);  //ft stores finishing time
         
        sprintf(x,"\nProcess %d says:I will execute now for %d seconds",num,bt);
        sprintf(y,"\nProcess %d says:I have finished execution at t=%d",num,ft);
         
        write(1,x,strlen(x)); //Prints at starting of process execution
        signal(SIGALRM,alarm_handler); //Catches SIGALRM
         
        alarm(bt); //Self suspension till process is executed
        pause();
		
		exit(0);
         
    }
