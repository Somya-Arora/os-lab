/* Code for child process
No alarm() call has been made in the child process but pause is used
So the child can only be woken up by the parent process
Value passed by the parent is used to determine normal or abnormal termination */

#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>


void alarm_handler(int sig) //Used to handle SIGALRM
{
                       
    printf("\nChild %d says:I was woken up by the parent\n ",getpid());
}
     
     
main(int argc,char *argv[])
{
    int n=atoi(argv[1]); //n contains the value passed by the parent
         
    printf("\nChild %d says:My parent is %d \n",getpid(),getppid());
    printf("\nChild %d says:I am going to sleep now\n",getpid());
         
    signal(SIGALRM,alarm_handler); //Catching SIGALRM
        
    pause(); //Self suspension
         
    if(n%2==0) //If even number passed by parent
        abort();//abnormal termination
    else  //Odd number passed by parent
        exit(0); //normal termination
}
