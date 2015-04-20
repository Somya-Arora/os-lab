/* Code for child process
As alarm() call has been made in the child process the child can resume by itself
or it can also be resumed by the parent
Value passed by the parent is used to determine normal or abnormal termination */

#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
int c;

void alarm_handler(int sig) //Used to handle SIGALRM
{
    if(sig==SIGALRM)
        {     
            int b=alarm(0);//resets the timer in case child alarm did not go off
            if(b==0)//Child alarm went off
                printf("\nChild %d says:I woke up myself after %d seconds \n",getpid(),4-b);
            else  //SIGALRM from parent caught
                printf("\nChild %d says:Woken up by parent after %d seconds\n ",getpid(),4-b);
        }
}
     
main(int argc,char *argv[])
{
    int n=atoi(argv[1]); //n contains the value passed by the parent
         
    printf("\nChild %d says:My parent is %d \n",getpid(),getppid());
    printf("\nChild %d says:I am going to sleep for 4 seconds\n",getpid());
         
    signal(SIGALRM,alarm_handler); //Catching SIGALRM
           
    alarm(4); //Setting the alarm
    pause(); //Self suspension
         
    if(n%2==0) //If even number passed by parent
        abort();//abnormal termination
    else  //Odd number passed by parent
        exit(0); //normal termination
}
