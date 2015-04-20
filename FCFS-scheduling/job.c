/*Code for child processes , job.c  */
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>

int i;
char x[100],y[100],z[100],a[100],b[100];

void alarm_handler() //Used to handle SIGALRM
    {
      write(1,b,strlen(b));//Print finishing message of process
    }

main(int argc,char *argv[])

   {
         i=atoi(argv[1]);      //Stores process number
         int at=atoi(argv[2]); //Stores arrival time
         int bt=atoi(argv[3]); //Stores execution time
         int wt=atoi(argv[4]); //Stores waiting time
         int ft=atoi(argv[5]); //Stores finishing time
         
         sprintf(x,"\nProcess %d says:I have arrived, current time is t=%d",i,at);
         sprintf(y,"\nProcess %d says:But the processor is busy at t=%d",i,at);
         sprintf(z,"\nProcess %d says:I will execute now for %d seconds",i,bt);
         sprintf(a,"\nProcess %d says:And the processor is idle at t=%d",i,at);
         sprintf(b,"\nProcess %d says:I have finished,my total waiting time was=%d,current time is t=%d\n ",i,wt,ft);
         
         write(1,x,strlen(x)); //Prints arrival message of process
         signal(SIGALRM,alarm_handler); //catches SIGALRM and calls alarm_handler
        
         if(wt>0) //Means processor has to wait
           {
              write(1,y,strlen(y));
              sleep(wt+1);// 1 is added to get more readable output
           }
         else //Means processor is idle
              write(1,a,strlen(a)); //Prints processor idle message
         
         write(1,z,strlen(z));// Prints execution message of process
         sleep(0.5); //For more readable output
         alarm(bt); //process suspends itself for the duration of its execution time
         pause();
         exit(0);
   }
