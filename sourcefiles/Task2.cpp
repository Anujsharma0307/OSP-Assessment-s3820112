#include <string>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "../Helperfiles/Helpers.h"
#include "../Helperfiles/Reduce.h"
#include "../Helperfiles/TaskFilter.h"
#include "../Helperfiles/Map.h"


bool THREADEXIT = false;
bool REDUCESIGNAL = false;
pthread_mutex_t r_mutex;
pthread_cond_t r_cond;
vector<string> SHARED_STRING; 
int main(int argc, char * argv[]) { 
    signal(SIGALRM, SIG_ALARM_HANDLER); 
    alarm(GRACEFUL_SECONDS); 

    
    if(argv[1] == nullptr || argv[2] == nullptr) {
        error("Invalid usage: './Task2 infile.txt outfile.txt'"); 
        return EXIT_FAILURE; 
    }
    
    string input = string(argv[1]); 
    string output = "../outputfiles/" + string(argv[2]); 

    if(!TaskFilter(input, output)) { error("Error occured while filtering"); return EXIT_FAILURE; }
    message("Filtering complete, file '" + output + "' created");
    
    if(!map2(input, output)) { error("Error occured while mapping "); return EXIT_FAILURE; }
    message("Mapping complete, filtered files in datafiles/FILTEREDFILES directory");

    string reducedOutput = output.replace(output.find(".txt"), output.length(), "_reduced.txt"); 
    if(!reduce2(reducedOutput)) { error("Error occured while reducing"); return EXIT_FAILURE; }
    message("Reducing complete, single reduced filter files in outputfiles directory");

    message("Task 2 Finished, Outputs in outputfiles directory"); 
    return EXIT_SUCCESS;
}