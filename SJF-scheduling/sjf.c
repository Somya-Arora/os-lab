/* Shortest Job first
No pre-emption, so arrival time of processes has not been considered
If some processes have the same execution time then the program works like FCFS */
#include<stdio.h>
#include<unistd.h>

main()
{
    int n,i,j,t1,t2;
    char x[100],y[100],z[100];
    printf("\nEnter the number of processes:");
    scanf("%d",&n);
    int bt[n],p[n],pid[n],ft[n];
      
    for(i=0;i<n;i++)
        {
            printf("\nEnter the execution time for P%d:",i);
            scanf("%d",&bt[i]);
            p[i]=i; //P[i] contains process ID's
        }
    for(i=0;i<n;i++) //To sort processes in ascending order of execution time
        {
            for(j=i+1;j<n;j++)
                {
                    if(bt[i]>bt[j])
                        {
                            t1=bt[i];
                            t2=p[i]; //Swapping process ID also
                            bt[i]=bt[j];
                            p[i]=p[j];
                            bt[j]=t1;
                            p[j]=t2;
                        }
                }
        }
    
	ft[0]=bt[0]; 
    for(i=1;i<n;i++) //For calculating finishing time
        {
            ft[i]=ft[i-1]+bt[i];
        }
                                     
    for(i=0;i<n;i++)
        {
            pid[i]=fork();
            if(pid[i]==0)
                {
                    sprintf(x,"%d",p[i]);
                    sprintf(y,"%d",bt[i]);
                    sprintf(z,"%d",ft[i]);
                    execl("/cygdrive/c/users/pushpinder/desktop/child.exe","child.exe",x,y,z,NULL);
                    perror("Exec failed");              
                }
            sleep(bt[i]); //So that the parent only creates a process after the previous one has executed 
        }               
                                     
}                        

