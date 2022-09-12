#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "../Helperfiles/Helpers.h"
#include "../Helperfiles/TaskFilter.h"



bool THREADEXIT = false;
bool REDUCESIGNAL = false;
pthread_mutex_t r_mutex;
pthread_cond_t r_cond;
vector<string> SHARED_STRING; 



int main(int argc, char * argv[]) { 
    signal(SIGALRM, SIG_ALARM_HANDLER); 
    alarm(GRACEFUL_SECONDS); 
    
    if(argv[1] == nullptr || argv[2] == nullptr) {
        error("Invalid usage: './Task1 infile.txt outfile.txt'"); 
        return EXIT_FAILURE; 
    }
    
    string input = string(argv[1]); 
    string output = "../outputfiles/" + string(argv[2]); 
    if(!TaskFilter(input, output)) { error("Error occured while filtering");  return EXIT_FAILURE; }
    message("Filtering complete, file '" + output + "' created in 'outputs'");

    return EXIT_SUCCESS;
}