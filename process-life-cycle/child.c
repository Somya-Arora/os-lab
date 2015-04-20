/* Code for child process
The child processes will catch their own termination signals and display them
Value passed by the parent is used to determine normal or abnormal termination */

#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

void term() //Used to handle normal termination
    {
      printf("\nChild %d says:Normal Termination\n",getpid());
    }
     
void abort_handler(int sig) //Used to handle SIGABRT
    {
      printf("\nChild %d says:Abnormal Termination\n",getpid());
    }
     
void alarm_handler(int sig) //Used to handle SIGALRM
    {
      printf("\nChild %d says:I am waking up\n ",getpid());
    }
     
     
main(int argc,char *argv[])
{
         int n=atoi(argv[1]); //n contains the value passed by the parent
         
         printf("\nChild %d says:My parent is %d \n",getpid(),getppid());
         printf("\nChild %d says:I am going to sleep\n",getpid());
         
         atexit(term); //Catching normal exit and calling function term()
         signal(SIGALRM,alarm_handler); //Catching SIGALRM
         signal(SIGABRT,abort_handler); //Catching SIGABRT
         
         alarm(3); //Setting the alarm
         pause(); //Self suspension
         
         if(n%2==0) //If even number passed by parent
           abort();//abnormal termination
         else  //Odd number passed by parent
           exit(0); //normal termination
}
