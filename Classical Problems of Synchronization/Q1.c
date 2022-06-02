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


int MAX_BUFFER_SIZE = 2048, const_max = 2048 * 8;
int SECONDARY[2048];
int BUFFER[2048];
int GLOBAL_COUNTER;
int GLOBAL_COUNTER2 = 0, zero = 0, one = 1;
pthread_mutex_t MUTEX_THREAD, MUTEX_THREAD2_;
sem_t IS_IT_EMPTY;
sem_t HALF_FILL;
sem_t TEMP;
sem_t IS_IT_COMPLETE;

//Producer function
void *PRODUCER()
{
	
	 sem_wait(&IS_IT_EMPTY);
	 // sem_wait: Decreases the semaphore pointed to by sem. Decrement proceeds if semaphore's value is greater than 0. In this case function returns immediately. If semaphore value == 0 then call block until semaphore value becomes greater than 0 or interupted by signal handler.
        pthread_mutex_lock(&MUTEX_THREAD);
	int INPUT_SIZE=MAX_BUFFER_SIZE;
	
    	printf("\n");
    	
    	int new_size = GLOBAL_COUNTER;
    	new_size += INPUT_SIZE;
    	
    	int temp_flag = 0;
    	if(new_size > MAX_BUFFER_SIZE){
    		temp_flag = 1;    		
    	}
    	
    	if (temp_flag){
    		printf("OVERFLOW!!!\n");
    		
        	
    	}
    	else{
    		
		printf("PRODUCER THREAD:");
		printf("\n");
		
		int ITERATOR = 0;
		
		while(ITERATOR < INPUT_SIZE){
			
			BUFFER[ITERATOR] = ITERATOR + 1;
			ITERATOR = ITERATOR + 1;
			
		}
		
		ITERATOR = 0;;
		
		while(ITERATOR < INPUT_SIZE){
			
			printf("%d ", BUFFER[ITERATOR]);
			ITERATOR = ITERATOR + 1;
		
		}
		
		GLOBAL_COUNTER+=INPUT_SIZE; printf("\n");
		
		sleep(0.01);			
	}
	

	pthread_mutex_unlock(&MUTEX_THREAD);sem_post(&IS_IT_COMPLETE);
        // sem_post: Increases the semaphore pointed to by sem. Another process or thread blocked in sem_wait call wakes up if semaphore value becomes greater than 0.
	
	return NULL;
}

int helper_fun_1(){
	int temp_count_x = const_max;
	for(int i = 0; i < MAX_BUFFER_SIZE; i++){
		if(temp_count_x < BUFFER[i]){
			temp_count_x = BUFFER[i];
		}
	}
	return temp_count_x;
}

int helper_fun_2(){
	int temp_count_y = 0;
	for(int i = 0; i < MAX_BUFFER_SIZE; i++){
		if(temp_count_y > BUFFER[i]){
			temp_count_y = BUFFER[i];
		}
	}
	return temp_count_y;
}


//Counsumer function
void *CONSUMER()
{
	sem_wait(&IS_IT_COMPLETE);
	// sem_wait: Decreases the semaphore pointed to by sem. Decrement proceeds if semaphore's value is greater than 0. In this case function returns immediately. If semaphore value == 0 then call block until semaphore value becomes greater than 0 or interupted by signal handler.
        pthread_mutex_lock(&MUTEX_THREAD);
        int ITERATOR=0;
	printf("\nCONSUMER THREAD:");
	printf("\n");
	
	do{
	
		printf("%d ", BUFFER[ITERATOR]);
		ITERATOR = ITERATOR + 1;
	
	}
	while(ITERATOR < GLOBAL_COUNTER);

	pthread_mutex_unlock(&MUTEX_THREAD);sem_post(&IS_IT_EMPTY);
        // sem_post: Increases the semaphore pointed to by sem. Another process or thread blocked in sem_wait call wakes up if semaphore value becomes greater than 0.
	GLOBAL_COUNTER=0;
	printf("\n");printf("\n");
	sleep(0.01);
	return NULL;
}


int main()
{
	
	pthread_t CONSUMING_HERE, PRODUCING_HERE;
	pthread_mutex_init(&MUTEX_THREAD, NULL);sem_init(&IS_IT_EMPTY,zero,MAX_BUFFER_SIZE);sem_init(&IS_IT_COMPLETE,zero,zero);
	
	while(1 == 1) {

		pthread_create(&PRODUCING_HERE, NULL, PRODUCER, NULL); pthread_create(&CONSUMING_HERE, NULL, CONSUMER, NULL);
		pthread_join(PRODUCING_HERE, NULL); pthread_join(CONSUMING_HERE,NULL);
	
	}
}
				


