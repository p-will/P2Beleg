 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <fcntl.h>   
#include <sys/stat.h>  

union semun {
int              val;    /* Value for SETVAL */
struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
unsigned short  *array;  /* Array for GETALL, SETALL */
struct seminfo  *__buf;  /* Buffer for IPC_INFO
			   (Linux-specific) */
};

void* create_shared_memory(size_t size) {
  // Our memory buffer will be readable and writable:
  int protection = PROT_READ | PROT_WRITE;

  // The buffer will be shared (meaning other processes can access it), but
  // anonymous (meaning third-party processes cannot obtain an address for it),
  // so only this process and its children will be able to use it:
  int visibility = MAP_ANONYMOUS | MAP_SHARED;

  // The remaining parameters to `mmap()` are not important for this use case,
  // but the manpage for `mmap` explains their purpose.
  return mmap(NULL, size, protection, visibility, 0, 0);
}

int main(int argc, char** argv)
{
    if(argc!=2)
    {
        perror("Too few arguments");
        EXIT_FAILURE;
    }
    long int processCount = strtol(argv[1],NULL,10);

    int child_pid[processCount];

    sem_t *mutex, *w;

    w = sem_open("/sem_w", O_CREAT,0777,1);
    mutex = sem_open("/sem_mutex",O_CREAT,0777,1); 
    int rc=0;

    void* sharedMem = create_shared_memory(sizeof(int));

    memcpy(sharedMem,&rc,sizeof(int));

    FILE* fp = fopen("test.dat","w");
    if(fp==NULL)
    {
        perror("Fileopening error");
        EXIT_FAILURE;
    }
    fprintf(fp,"%d",processCount);
    fclose(fp);

    for(int i=0; i < processCount; i++)
    {
        child_pid[i] = fork();
        if(child_pid[i]==-1)
        {
            perror("Fork error");
            EXIT_FAILURE;
        }
        else if(child_pid[i] == 0) // Kind
        {
            if(i%2 == 0) //Gerade -> Leser-Prozess
            {
               sem_wait(mutex);
               memcpy(&rc,sharedMem,sizeof(int)); 
               rc++;
               memcpy(sharedMem,&rc,sizeof(int));
               if(rc==1)
               {
		   int val;
		   sem_getvalue(w,&val);
		   printf("Value :%d\n",val);
                   sem_wait(w);
		   puts("w blockieren");
               }
               sem_post(mutex);
	       puts("lesen");
               FILE* read_fp = fopen("test.dat","r");
               int read_val = 0;
               if(fscanf(read_fp,"%d",&read_val)==-1)
               {
                   perror("Read error");
                   EXIT_FAILURE;
               }
               rewind(read_fp);
               fclose(read_fp);
               sem_wait(mutex);
	       puts("rc --");
               memcpy(&rc,sharedMem,sizeof(int)); 
               rc--;
               memcpy(sharedMem,&rc,sizeof(int));
               if(rc==0)
	       {
	     	  puts("w öffnen");
                  sem_post(w);
		  //int val;
		  //sem_getvalue(w,&val);
		  //printf("Value :%d\n",val);
	       }
                sem_post(mutex);
		exit(0);
	    }
            else //ungerade -> Schreibprozess
            {
               sem_wait(w);
	       puts("schreiben");
               FILE* write_fp = fopen("test.dat","r+");
               int write_val = 0;
               if(fscanf(write_fp,"%d",&write_val)==-1)
               {
                   perror("Read error");
                   EXIT_FAILURE;
               }
	       printf("Read :%d\n",write_val);
               write_val--;
	       printf("Written: %d\n",write_val);
               rewind(write_fp);
               if(fprintf(write_fp,"%d",write_val)==-1)
               {
                   perror("Write error");
                   EXIT_FAILURE;
               }
               fclose(write_fp);
	       puts("w öffnen");
               sem_post(w);
	       exit(0);
            }
            
        }
        else
        {
            ;
        }
        
    }
    int n= processCount;
    while(n>0)
    {
        int tmpid= wait(NULL);
        n--;
    }
    if(sem_unlink("/sem_w")==-1)
    {
        perror("Error on closing semaphore wait");
    }
    if(sem_unlink("/sem_mutex")==-1)
    {
        perror("Error on closing semaphore mutex");
    }

    munmap(sharedMem,sizeof(int));
    return 0;
}
