/* First Come First Served scheduling or FIFO
User can specify the number of child processes to be created
Arrival time must be entered in an ascending order or the program will go into an infinite sleep cycle
This can be fixed by sorting the processes based on arrival time which I have left out to reduce code length  */


#include<stdio.h>
#include<unistd.h>
#include<signal.h>

main()
{
      int n,i;
      printf("\nEnter the number of processes:");
      scanf("%d",&n);
      int at[n],bt[n],wt[n],pid[n],ft[n];// at=arrival time, bt=execution time
      char x[5],y[5],z[5],a[5],b[5];     //wt=waiting time, ft=finishing time
      wt[0]=0; // Waiting time of first process will always be 0
      
      for(i=0;i<n;i++)
        {
           printf("\nEnter arrival time of P%d:",i);
           scanf("%d",&at[i]);
        } 
       
      for(i=0;i<n;i++)
        {                             
           printf("\nEnter execution time of P%d:",i);
           scanf("%d",&bt[i]);
        }  
      
      at[n]=at[n-1]; //Needed later  to avoid infinite sleep cycle
      ft[0]=bt[0]+at[0]; //Finishing time of the first process depends only on its arrival and execution time
      
      for(i=1;i<n;i++)  //Calculating finishing time
        {
            if(at[i]<ft[i-1]) //If next process arrives before the previous one has finished
                 ft[i]=ft[i-1]+bt[i];
            else              //If process arrives when processor is idle
                 ft[i]=at[i]+bt[i]; 
        }
      
      for(i=1;i<n;i++)  //Calculating waiting time
        {      
            if(at[i]<ft[i-1]) //If next process arrives before the previous one has finished
                 wt[i]=ft[i-1]-at[i];    
            else              //If process arrives when processor is idle
                 wt[i]=0;     //hence waiting time is 0
        }
             
       for(i=0;i<n;i++)  //Creating child processes
        {
            pid[i]=fork();
            if(pid[i]==0) //Only the child created in each iteration can access this
                { 
                      sprintf(x,"%d",i);      // x has process number
                      sprintf(y,"%d",at[i]);  //y has arrival time
                      sprintf(z,"%d",bt[i]);  //z has execution time
                      sprintf(a,"%d",wt[i]);  //a has waiting time
                      sprintf(b,"%d",ft[i]);  //b has finishing time
                      execl("/cygdrive/c/users/pushpinder/desktop/job.exe","job.exe",x,y,z,a,b,NULL);
                      perror("Exec failed");
                      
                }
            sleep(at[i+1]-at[i]); //parent sleeps till next process arrives
                                  //so that processes are created based on arrival time
        }
                      
                  
}
