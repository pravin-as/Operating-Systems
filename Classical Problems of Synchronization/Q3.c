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

#include <unistd.h>
//Defines symbolic constants, types and declares miscellaneous functions.


//typedef pthread_mutex_t PMT;
//typedef pthread_mutex_lock PML;
//typedef pthread_mutex_unlock PMU;
//typedef sem_wait SW;
//typedef sem_post SP;



int GLOBAL_COUNTER = 0;
int SLEEP_TIME = 9;
int const_max = 1000;
int temp = 0;
int zero = 0, one = 1;
int LIMIT_MAXIMUM=5;
int GLOBAL_THREAD_ARRAY[9] = {1,2,3,4,5,6,7,8,9};
int iterator_ind_1;
int iterator_ind_2;
sem_t TYPER;
pthread_mutex_t LIME_MUTEX;

void initializ(){
	for(int i = 0; i < 9; i++){
		GLOBAL_THREAD_ARRAY[i] = i + 1;
	}
}

void *HELPER_THREAD_READ(void *GLOBAL_THREAD_ARRAY)
{   
	
   iterator_ind_1 = 1;
   do
   {
	pthread_mutex_lock(&LIME_MUTEX);temp=temp+1;
	if(temp == one) sem_wait(&TYPER);
	// sem_wait: Decreases the semaphore pointed to by sem. Decrement proceeds if semaphore's value is greater than 0. In this case function returns immediately. If semaphore value == 0 then call block until semaphore value becomes greater than 0 or interupted by signal handler.
	pthread_mutex_unlock(&LIME_MUTEX);
	printf("READER NUMBER:  %d: COUNTER VALUE %d\n",*((int *)GLOBAL_THREAD_ARRAY),GLOBAL_COUNTER);
	pthread_mutex_lock(&LIME_MUTEX);temp=temp-1;
	if(temp == zero) sem_post(&TYPER); 
	// sem_post: Increases the semaphore pointed to by sem. Another process or thread blocked in sem_wait call wakes up if semaphore value becomes greater than 0.
	pthread_mutex_unlock(&LIME_MUTEX);
	sleep(one);iterator_ind_1++;

    }
    while(iterator_ind_1 <= LIMIT_MAXIMUM);
}

int helper_fun_1(){
	int temp_count_x = const_max;
	for(int i = 0; i < 9; i++){
		if(temp_count_x < GLOBAL_THREAD_ARRAY[i]){
			temp_count_x = GLOBAL_THREAD_ARRAY[i];
		}
	}
	return temp_count_x;
}

int helper_fun_2(){
	int temp_count_y = 0;
	for(int i = 0; i < 9; i++){
		if(temp_count_y > GLOBAL_THREAD_ARRAY[i]){
			temp_count_y = GLOBAL_THREAD_ARRAY[i];
		}
	}
	return temp_count_y;
}

void init(){printf("STARTING GLOBAL COUNTER VALUE: \n");pthread_mutex_init(&LIME_MUTEX, NULL);sem_init(&TYPER,zero,one);}

void *HELPER_WRITER_READ(void *GLOBAL_THREAD_ARRAY)
{   

   iterator_ind_1 = 1;
   
   do{
	sem_wait(&TYPER);GLOBAL_COUNTER++;
	// sem_wait: Decreases the semaphore pointed to by sem. Decrement proceeds if semaphore's value is greater than 0. In this case function returns immediately. If semaphore value == 0 then call block until semaphore value becomes greater than 0 or interupted by signal handler.
	printf("WRITER NUMBER: %d: NEW COUNTER VALUE %d\n",(*((int *)GLOBAL_THREAD_ARRAY)),GLOBAL_COUNTER);
	sem_post(&TYPER);sleep(SLEEP_TIME);
	// sem_post: Increases the semaphore pointed to by sem. Another process or thread blocked in sem_wait call wakes up if semaphore value becomes greater than 0.
	iterator_ind_1 = iterator_ind_1 + 1;
   }
   while(iterator_ind_1 <= LIMIT_MAXIMUM);


}




int main()
{   


    init();    
    
    // sem_post: Increases the semaphore pointed to by sem. Another process or thread blocked in sem_wait call wakes up if semaphore value becomes greater than 0.
	// sem_wait: Decreases the semaphore pointed to by sem. Decrement proceeds if semaphore's value is greater than 0. In this case function returns immediately. If semaphore value == 0 then call block until semaphore value becomes greater than 0 or interupted by signal handler.
    
    pthread_t read_thread[9],write_thread[9];
    
    iterator_ind_1 = 0;
    
    do{
    
    	pthread_create(&write_thread[iterator_ind_1], NULL, (void *)HELPER_WRITER_READ, (void *)&GLOBAL_THREAD_ARRAY[iterator_ind_1]);
    	
    	iterator_ind_2 = 0;
    	
    	do{
    	
    		pthread_create(&read_thread[iterator_ind_2], NULL, (void *)HELPER_THREAD_READ, (void *)&GLOBAL_THREAD_ARRAY[iterator_ind_2]);
    		iterator_ind_2 = iterator_ind_2 + 1;
    	}
    	while(iterator_ind_2 < 9);
    	
    }
    while(iterator_ind_1 < 9);
    
    
    
    iterator_ind_1 = 0;
    
    do{
    	
    	pthread_join(read_thread[iterator_ind_1], NULL);
    	iterator_ind_1 = iterator_ind_1 + 1;
    
    }
    while(iterator_ind_1 < 9);
    
    
    iterator_ind_1 = 0;
    
    do{
    	
    	pthread_join(write_thread[iterator_ind_1], NULL);
    	iterator_ind_1 = iterator_ind_1 + 1;
    
    }
    while(iterator_ind_1 < 9);
  

    return 0;
    
}
