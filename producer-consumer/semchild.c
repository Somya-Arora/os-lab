#include<stdio.h>
#include<sys/sem.h>
#include<sys/types.h>
#include <sys/ipc.h>
#include<string.h>
#include <sys/shm.h>

int main(int argc,char* argv[])
{
    int semid,segid;
    semid=atoi(argv[1]);
    segid=atoi(argv[2]);
   
    char str1[100],str2[100],str3[100];
       
    int *buffer;
    buffer=shmat(segid,NULL,0);
	if(buffer==(void *)-1)
	{
    perror("\nChild shmat()");
	}
    
   
    int i;
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
	sleep(1);
for(i=0;i<5;i++)
{
    semop(semid,wait,1);
	semop(semid,acquire,1);
	if(buffer[0]==0)
	{
	sprintf(str1,"\nConsumer says:Buffer empty\n");
	write(1,str1,strlen(str1));
	semop(semid,release,1);
	}
	else
	{
	sprintf(str1,"\nConsumer says: Current items in buffer =%d",buffer[0]);
	write(1,str1,strlen(str1));
	sprintf(str1,"\nConsumer says:Consuming item");
	write(1,str1,strlen(str1));
	buffer[0]=buffer[0]-1;
	sprintf(str1,"\nConsumer says:now items in buffer= %d\n",buffer[0]);
	write(1,str1,strlen(str1));
	sleep(1);
	semop(semid,release,1);
	}
	}
	//exit();
	
	}