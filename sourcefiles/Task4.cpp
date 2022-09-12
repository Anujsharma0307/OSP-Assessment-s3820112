#include <string>
#include <pthread.h>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fstream>
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
        error("Invalid usage: './Task4 infile.txt outfile.txt'"); 
        return EXIT_FAILURE; 
    }
    
    string input = string(argv[1]); 
    string output = "../outputfiles" + string(argv[2]); 

     
    if(!TaskFilter(input, output)) { error("Error occured while filtering"); return 0; }
    message("Filtering complete, file '" + output + "' created");
    ifstream infile; 
    infile.open(output); 
    
    for(string curLine; getline(infile, curLine);) {
        SHARED_STRING.push_back(curLine); 
    }

    infile.close(); 

    pthread_t mappingThread; 
    pthread_t reducingThread; 
    pthread_mutex_init(&r_mutex, NULL);
    pthread_cond_init(&r_cond, NULL);
    
    MAP_THREAD_ARGS m_params;
    m_params.type = 4;
    int thread_map_return = pthread_create(&mappingThread, NULL, map3, &m_params); 
    if (thread_map_return) { return EXIT_FAILURE; }

    REDUCE_THREAD_ARGS r_params; 
    r_params.output = output.replace(output.find(".txt"), output.length(), "_reduced.txt"); 
    r_params.type = 4;
    
    int thread_reduce_return = pthread_create(&reducingThread, NULL, reduce3, &r_params); 
    if (thread_reduce_return) { return EXIT_FAILURE; }

    pthread_join(reducingThread, NULL); 
    pthread_join(mappingThread, NULL); 

    pthread_mutex_destroy(&r_mutex);
    pthread_cond_destroy(&r_cond);

    message("Task 4 Finished, Outputs in outputfiles directory"); 
    return EXIT_SUCCESS;
}