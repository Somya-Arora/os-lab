/* Process life cycle,with self suspension but resumption by parent
although self resumption is possible if the parent is too late to wake up the child
You can specify the number of child processes to be created
Always half of the children will exit normally and the other half will exit abnormally
The parent process will wait until all the children have executed and will print their exit status   */
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
            sleep(2);//To make sure the children are suspended before SIGALRM is sent
            kill(pid[i],SIGALRM);//Sending SIGALRM to child                         
        }
                   
    for(i=0;i<n;i++)
        {
            while(waitpid(pid[i],&status,0)>0) //to make the parent keep waiting till the last child is executed
                {                             // not an optimal solution as waitpid() may return -1 for some unforeseen situations
	  		                                 // but in this simple program,it will return -1 only when all children have executed 
                    if(WIFEXITED(status)) //processes which exited normally
                        printf("\nParent says:Child %d exited normally",pid[i]);
                    else //aborted processes
                        printf("\nParent says:Child %d was aborted",pid[i]);
                }
        }
}
