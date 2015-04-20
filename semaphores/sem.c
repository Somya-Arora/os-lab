/* Shared memory segment is allocates and then initialized with a binary semaphore
   As segment is not deallocated, on running the program again semget() will fail as segment already exists */
#include<stdio.h>
#include<sys/sem.h>
#include<sys/types.h>
#include <sys/ipc.h>

main()
{
    key_t key=ftok("/cygdrive/c/users/pushpinder/desktop/child.exe",'a'); //in case unrelated processes need to get a key
	
	if(key==-1) //ftok() failed
	perror("ftok");
    
      
    int semid=semget(key,1,IPC_CREAT|IPC_EXCL);//Allocating shared memory segment
    
	if(semid==-1) //Allocation failed because segment with same key already exists
        printf("\nSegment already exists with key=%d",key);
    else
	    printf("\nShared memory segment with  ID =%d successfully allocated",semid);
	
	int st=semctl(semid,0,SETALL); //Initializing segment ,4th argument not used
	
    if(st==-1) //initialization failed
	    {
           perror("semctl() failed");
	    }
	else   //initialization successful
        {
           printf("\nSegment successfully initialized");
		   
        }		   
      
}
      
