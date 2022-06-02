#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/types.h>

int mx = 1000007;
int ARRAY[1000007];
int counter = 0;





int MAX_DATA;
int find_max(int var1, int var2){

	if(var1 > var2){
		return var1;
	}else{
		return var2;
	}
	
}


pid_t THREAD_ID_2;
void *Thread_two(void *vargp)
{

    THREAD_ID_2 = syscall(SYS_gettid);

    int max = 0;
    for (int j = 0 ; j < counter; j++){
    	max = find_max(max, ARRAY[j]);
    } 
    
    MAX_DATA = max;     

    printf("Maximum value is %d The thread id is: %d\n",MAX_DATA , THREAD_ID_2);
}




int MIN_DATA;
int find_min(int var1, int var2){

	if(var1 < var2){
		return var1;
	}else{
		return var2;
	}
	
}


pid_t THREAD_ID_3; 
void *Thread_three(void *vargp )
{
  
     THREAD_ID_3 = syscall(SYS_gettid);
     
     int min = ARRAY[0];
     
     for (int j = 0 ; j < counter ; j++){
     	min = find_min(min, ARRAY[j]);
     } 
     
    MIN_DATA = min;
	
    printf("Minimum value is %d The thread id is: %d\n",MIN_DATA , THREAD_ID_3);
}




pid_t THREAD_ID_1;
float AVERAGE;
void *Thread_one(void *vargp  )
{
    float sm=0;
    for (int j = 0 ; j < counter; j++){
        sm += ARRAY[j] + 0.0;
    }
     AVERAGE = sm / counter;
     THREAD_ID_1 = syscall(SYS_gettid);

    printf("Average value is %f The thread id is: %d\n", AVERAGE  , THREAD_ID_1);
  
}
 

int main()
{
       
    
    printf("Enter the elements of the array:\n"); 
    do {
        scanf("%d", &ARRAY[counter++]);
    } while (getchar() != '\n' && counter < mx);
 
    ARRAY[counter];
    
    pthread_t tidd1;pthread_t tidd2;pthread_t tidd3;
    
    pthread_create(&tidd1, NULL, Thread_one, NULL); pthread_join(tidd1, NULL);
    pthread_create(&tidd2, NULL, Thread_two, NULL); pthread_join(tidd2, NULL);
    pthread_create(&tidd3, NULL, Thread_three,NULL);pthread_join(tidd3, NULL);
    
    printf("AVG: %f MIN:%d MAX:%d and Process ID:%ld\n",AVERAGE,MIN_DATA,MAX_DATA,syscall(SYS_gettid));

 
    return 0;
}
