// Header files
#include <stdio.h>
#include <assert.h>
#include <complex.h>
#include <float.h>
#include <ctype.h>
#include <math.h>
#include <setjmp.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <time.h>
#include <stddef.h>
#include <time.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <tgmath.h>


int siz = 128;		// Maximum size of command
int Number_Of_Steps = 0;	// As an index to debug where we are 
char *Reductant[128], *Parameters_For[128],*token;  


// To erase whitespace from start and end 
void Erase_White_Space(char* adj){

	int end_line = 0, end_space = 0;  
	if(adj[strlen(adj)-1]=='\n')end_line = 1;	// if last character is line-break
	if(adj[strlen(adj)-1]==' ')end_space = 1;	// if last character is empty-character
	
	int begin_line = 0, begin_space = 0;
	if(adj[0]=='\n')begin_line = 1;		// if first character is line-break
	if(adj[0]==' ')begin_space = 1;		// if first character is empty-character
	
	
	if(end_line || end_space)adj[strlen(adj)-1]='\0';  			
	
	// Referenced from https://www.cplusplus.com/reference/cstring/memmove/
	if(begin_line || begin_space)memmove(adj, adj+1, strlen(adj));
	
}


// Tokenises the Reductant
void Token_maker(char** param,int *Number_Of_Steps,char *adj,const char *c){
	char *token;
	// strtok is referenced from https://www.cplusplus.com/reference/cstring/strtok/
	token=strtok(adj,c);  // Iniatlizing token
	int Program_Runner=-1;
	while(token){
		int sz = sizeof(token);   // Giving size so that malloc works properly
		sz++;Program_Runner++;	  // Incrementing sz and program runner
		// malloc is referenced from https://en.cppreference.com/w/c/memory/malloc
		param[Program_Runner]=malloc(sz);             
		param[Program_Runner] = token;
		Erase_White_Space(param[Program_Runner]);	//Erasing white space
		// strtok is referenced from https://www.cplusplus.com/reference/cstring/strtok/
		token=strtok(NULL,c);
	}
	Program_Runner++;		// Incrementing value
	param[Program_Runner]=NULL;	// Setting the default value
	*Number_Of_Steps=Program_Runner;  // Giving the count of program runner to address 
}


// Printing all parameters in one place
void Print_Parameters(char ** param){
	while(*param){ // while it reaches the last value
		printf("param=%s..\n",*param++);   // Printing all the parameters
	}
}


// Executes basic linux commands
void Basic_Command_Execution(char** argv){
	// Referenced fork from https://man7.org/linux/man-pages/man2/fork.2.html
	if(fork()>0){
		//Referenced from https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-wait-wait-child-process-end
		wait(NULL);		
	}
	else{
		execvp(argv[0],argv);
		perror(   "Not a valid command" "\n");    // Printing error
		// Referenced from https://en.cppreference.com/w/c/program/exit
		exit(1);
	}
}

// KMPAlgorithm for string matching taken from https://www.tutorialspoint.com/c-program-for-kmp-algorithm-for-pattern-searching
void prefixSuffixArray(char* pat, int M, int* pps) {
   int length = 0;
   pps[0] = 0;
   int i = 1;
   while (i < M) {
      if (pat[i] == pat[length]) {
         length++;
         pps[i] = length;
         i++;
      } else {
         if (length != 0)
         length = pps[length - 1];
         else {
            pps[i] = 0;
            i++;
         }
      }
   }
}
void KMPAlgorithm(char* text, char* pattern) {
   int M = strlen(pattern);
   int N = strlen(text);
   int pps[M];
   prefixSuffixArray(pattern, M, pps);
   int i = 0;
   int j = 0;
   while (i < N) {
      if (pattern[j] == text[i]) {
         j++;
         i++;
      }
      if (j == M) {
         j = pps[j - 1];
      }
      else if (i < N && pattern[j] != text[i]) {
         if (j != 0)
         j = pps[j - 1];
         else
         i = i + 1;
      }
   }
}


void prompt_line(){

// Prints the prompt line
	printf( "Pravin_Arjun_Shankhapal@12041130# ");

}

char adj[1024];
void command_input(){
	// https://www.cplusplus.com/reference/cstdio/fgets/
	fgets(adj, 1024, stdin);

}

void basic_function_caller(){

	Token_maker(Parameters_For,&Number_Of_Steps,adj," ");
	
	// strstr is referenced from https://www.cplusplus.com/reference/cstring/strstr/
	
	
	if(strstr(Parameters_For[0],"cd")){
	
		// chdir is referenced from https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-chdir-change-working-directory
		chdir(Parameters_For[1]);
	}
	
	else if(strstr(Parameters_For[0],"exit")){
		exit(0);
	}
	else Basic_Command_Execution(Parameters_For);
}

// Check which command user has typed
void command_check(){

	basic_function_caller();

}

// Main Function
int main(char** argv,int argc)
{
	
	Number_Of_Steps = 0;

	while(1){

		prompt_line();   
		command_input();
		command_check();
		
	}

	return 0;
}
