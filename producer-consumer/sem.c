/* Shared memory segment is allocates and then initialized with a binary semaphore
   As segment is not deallocated, on running the program again semget() will fail as segment already exists */
#include<stdio.h>
#include<sys/sem.h>
#include<sys/types.h>
#include <sys/ipc.h>
#include<unistd.h>
#include<string.h>
#include <sys/shm.h>

int pid;
int c=0;
main()
{
char str1[100],str2[100],str3[100],arg1[100],arg2[100];
   
    key_t key=ftok("/cygdrive/c/users/pushpinder/Desktop/prog/mtp.c",'A');
	

	key_t key2=ftok("/cygdrive/c/users/pushpinder/Desktop/prog/mtpc.c",'B');
	int segid;
	segid=shmget(key2,1024,IPC_CREAT|0666);
	if(segid==-1)
	{
	perror("Shmget()");
	}
	int *buffer;
	buffer=shmat(segid,NULL,0);
	
	buffer[0]=0;
	sprintf(arg2,"%d",segid);
	
	union semun{
	    int val;
		unsigned short int *array;
		};
    
    union semun argument;
    unsigned short values[1];
    values[0] =0;
    argument.val = 0;
    int i;
   
	
	
    
    int semid=semget(key,1,IPC_CREAT|IPC_EXCL|0666);
    
	if(semid==-1) //Allocation failed because segment with same key already exists
      {  
		sprintf(str1,"\nParent says:Segment already exists with key=%d",key);
		write(1,str1,strlen(str1));
	  }
    else
	  {
	   	   sprintf(str1,"\nParent says:Semaphore with key= %d, ID =%d successfully allocated\n",key,semid);
		   write(1,str1,strlen(str1));
	  }
	int st=semctl(semid,0,SETVAL,argument);	//Initializing semaphore
	if(st==-1)
	{
	perror("\nSetval");
	}
    sprintf(arg1,"%d",semid);
	int value=semctl(semid,0,GETVAL,0);
	//printf("\nInitial Value of semaphore is %d",value);
	
	struct sembuf acquire[1];
	struct sembuf release[1];
	struct sembuf wait[1];
	acquire[0].sem_num=0;
	release[0].sem_num=0;
	wait[0].sem_num=0;
	wait[0].sem_op=0;
	acquire[0].sem_op=1;
	release[0].sem_op=-1;
	acquire[0].sem_flg=0;
    release[0].sem_flg=0;
	wait[0].sem_flg=0;
    pid=fork();
	
	if(pid==0)
	{
	printf("\nCreating child");
	execl("/cygdrive/c/users/pushpinder/Desktop/prog/semchild.exe","semchild.exe",arg1,arg2,NULL);
	perror("Exec");
	
	}
	
	
	for(i=0;i<5;i++)
	{
	semop(semid,wait,1);
	semop(semid,acquire,1);
	if(buffer[0]==5)
	{
	sprintf(str3,"\nProducer says: Buffer full\n");
	write(1,str3,strlen(str3));
	semop(semid,release,1);
	}
	else{
	
	sprintf(str1,"\nProducer says:Items in buffer=%d",buffer[0]);
	write(1,str1,strlen(str1));
	sprintf(str1,"\nProducer says:Producing item");
	write(1,str1,strlen(str1));
	buffer[0]=buffer[0]+1;
	sprintf(str1,"\nProducer says:now buffer=%d\n",buffer[0]);
    write(1,str1,strlen(str1));
	
	sleep(1);
	
	semop(semid,release,1);
	}
	}
	//wait();
	semctl(semid,0,IPC_RMID,0);
	shmctl(segid,IPC_RMID,0);
	
	//printf("\nValue of semaphore after releasing is=%d",value);
	
}
	

	
	

      
