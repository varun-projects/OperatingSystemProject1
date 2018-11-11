
/*
Author Varum Garg     : varun_garg@student.uml.edu   
Date              : 02/11/2018
Course            : Operating Systems (Spring 2018)
Project Name      : OS_program1.c
Code Version      : 5.50
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>



void printCredits(void){  // ---- function that prints authors info
system("clear");
printf("\n\t ============================================================== \n");
printf("\t                         OS Program 1 \n");
printf("\t ---------------------------------------------------------------\n");
printf("\t |  Name      |  Last Name   |              e-mail              |\n");
printf("\t --------------------------------------------------------------- \n");
printf("\t |  Varum     |   Garg       |     varun_garg@student.uml.edu   |\n");
printf("\t ---------------------------------------------------------------\n\n");

}



// ----  search in a given array for the index of the requested content
int searchPID(pid_t PID, int * PID_Array, int ChildsNum) {
 
   int PID_index=-2;
   int k;
  
   for(k=0; k<ChildsNum+1; k++) {
        
     if(PID == PID_Array[k]) {
        PID_index=k;  // requested PID found in the array 
        break;  
      }else {
        PID_index = -2;  // error - PID not found in the given array
      }  
    }
  return PID_index;
}





// ---- MAIN LOOP -------------------
int main(int argc, char *argv[]){


  int CHILDS_SIZE = atoi(argv[1]); // number of children wanted

  if (CHILDS_SIZE >25){            // inserted childs check
    puts("ERROR: Use less than 25 childs");
    printf("You entered child number = %d  !!!\n", CHILDS_SIZE); 
    return 0;
  }

  int PID_array[CHILDS_SIZE+1];             // array to store children's PIDs if needed
  int childID,i,j;                          // variables for counters and PID numbers
  int Children_Left= CHILDS_SIZE;
  pid_t newPID,trackPID;
  char progARG[8];
  char command[8];

  printCredits();                             // print authors info
  printf("Create %d childs\n\n",CHILDS_SIZE); // print user defined children number 
  printf("Parent pid is %d\n", getpid());     // print parent Process ID


   for(i=1; i<=CHILDS_SIZE; i++){
         
         PID_array[i] = fork();
         

            if(PID_array[i]==0){  // Child Process
                sprintf(command, "./test%d",i%5);
                sprintf(progARG, "test%d",i%5);
                execlp(command,progARG,NULL);
                exit(0);

            }else if (PID_array[i]<0) {   // error case : fork fails to create a child process 
                printf("FORK ERROR !!!\n");

            }else{
                // Parent process
                printf("Started Child %d with pid %d\n",i,PID_array[i]);   
            }
    
    }


while(Children_Left>0){
	    trackPID = wait(NULL);
    childID = searchPID(trackPID,&PID_array[0],CHILDS_SIZE);  // for a given PID it returns the Child Numner
		printf("Child %d (PID %d) finished\n",childID,trackPID);
    Children_Left--;		
}

return 0;
}
