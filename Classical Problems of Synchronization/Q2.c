//Header files

#include <stdlib.h>
//General purpose standard C programming language library. Memory allocation, process control, conversions are included.

#include <stdio.h>
//Program Input/output related functions.

#include <pthread.h>
//Function declarations and mappings. Used for threading interfaces.

#include <semaphore.h>
//Define the sem_t type. Semaphore operations performing uses.

#include <time.h>
//Declares structure tm which includes tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year.


int LOCAL_COUNTER = -1;
int FIB_COUNTER1,FIB_COUNTER2;
int zero = 0, one = 1, limit = 20;
pthread_t READ_THREAD;
pthread_t INCREMENT_THREAD;
sem_t GLOBAL_COUNTER;
sem_t GLOBAL_READ;


void *COUNTER_INC(int *FIB_COUNTER1)
{   

    int local_pointer = 0;
    do     
    {
	    sem_wait(&GLOBAL_READ); LOCAL_COUNTER++;
	    // sem_wait: Decreases the semaphore pointed to by sem. Decrement proceeds if semaphore's value is greater than 0. In this case function returns immediately. If semaphore value == 0 then call block until semaphore value becomes greater than 0 or interupted by signal handler.
	    printf("COUNT: %d THREAD ID (Incrementing thread): %ld\n",LOCAL_COUNTER,pthread_self());
	    sem_post(&GLOBAL_COUNTER);local_pointer++;
	    // sem_post: Increases the semaphore pointed to by sem. Another process or thread blocked in sem_wait call wakes up if semaphore value becomes greater than 0.
    }
    while(local_pointer <= limit); 

}


void *COUNTER_READ(int *FIB_COUNTER2)
{   
    
    int local_pointer = 0;
    do  
    {
	    sem_wait(&GLOBAL_COUNTER);
	    // sem_wait: Decreases the semaphore pointed to by sem. Decrement proceeds if semaphore's value is greater than 0. In this case function returns immediately. If semaphore value == 0 then call block until semaphore value becomes greater than 0 or interupted by signal handler.
	    printf("COUNT: %d THREAD ID (reading and printing): %ld\n\n",LOCAL_COUNTER,pthread_self());
	    sem_post(&GLOBAL_READ); local_pointer++;
	    // sem_post: Increases the semaphore pointed to by sem. Another process or thread blocked in sem_wait call wakes up if semaphore value becomes greater than 0.
    }
    while(local_pointer <= limit); 
}


void init(){sem_init(&GLOBAL_COUNTER,zero,zero); sem_init(&GLOBAL_READ,zero,one);}

void CREATE(){pthread_create(&INCREMENT_THREAD, NULL, (void *)COUNTER_INC, (int *)&FIB_COUNTER1);pthread_create(&READ_THREAD, NULL, (void *)COUNTER_READ, (int *)&FIB_COUNTER2);}

void JOIN(){pthread_join(INCREMENT_THREAD, NULL);pthread_join(READ_THREAD, NULL);}

void DESTROY(){sem_destroy(&GLOBAL_COUNTER);}


// main function
int main()
{   
   	init();	CREATE();	JOIN();	DESTROY();
	return 0; 
}
