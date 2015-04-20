/* Process life cycle, no self resumption
You can specify the number of child processes to be created
Always half of the children will exit normally and the other half will exit abnormally
The parent will wake up the children by sending SIGALRM directly to children
The parent process will wait until all the children have executed and then print their exit status   */
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
main()
{
    int n,i,status;
    char x[10];
    printf("\nHow many child processes do you want to create?:");
    scanf("%d",&n);
    int pid[n]; //To store process ID's of all children created
      
    for(i=0;i<n;i++)
        {
            pid[i]=fork();
            if(pid[i]==0) //Only the child created in each iteration can access this
                { 
                    sprintf(x,"%d",i); //x[i] now contains i so that each child is passed a different value
                    execl("/cygdrive/c/users/pushpinder/desktop/child.exe","child.exe",x,NULL);
                         
                } 
            
        }
              
     
    for(i=0;i<n;i++)
	    {
            sleep(i);//makes sure the last created process is woken up last
            kill(pid[i],SIGALRM);//sending SIGALRM to child processes
                                 
        }
                   
    for(i=0;i<n;i++)
        {
            while(waitpid(pid[i],&status,0)>0) //to make the parent keep waiting till the last child is executed
                {                             // not an optimal solution as waitpid() may return -1 for some unforeseen situations
					                         // but in this simple program,it will return -1 only when all children have executed 
                    if(WIFEXITED(status))//processes which exited normally
                        printf("\nParent says:Child %d exited normally",pid[i]);
                    else //aborted processes
                        printf("\nParent says:Child %d was aborted",pid[i]);
                }
        }
}
