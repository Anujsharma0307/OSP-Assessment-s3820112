#include "Reduce.h"


queue<string> stringCache[TOTAL_FILES];
vector<string> sortingCache; 
ofstream OutputFile;


int reduce2(const string &output) {
    for (int i = 0; i < TOTAL_FILES && !THREADEXIT; i++)
    {
        ifstream inputStream;
        string infile = "../datafiles/FILTEREDFILES/" + to_string(i + OFFSET) + ".txt";
        inputStream.open(infile); 
        for(string line; getline(inputStream, line);){
            stringCache[i].push(line); 
        }

        inputStream.close();
        sortingCache.push_back(getNextLineFromFile(&stringCache[i])); 
    }

    OutputFile.open(output);
    while(!sortingCache.empty() && !THREADEXIT) {
        sort(sortingCache.begin(), sortingCache.end(), CustomSTRCMP);
        string line = sortingCache.front();
        OutputFile <<  line << "\n"; 
        pop_front(sortingCache); 

        string nextLine = getNextLineFromFile(&stringCache[line.length() - OFFSET]); 
        if(!nextLine.empty()) {
            sortingCache.push_back(nextLine);
        }
    }
    OutputFile.close();
    return 1;
}

void* reduce3(void* args) {
    
    struct REDUCE_THREAD_ARGS *reduce_args = (struct REDUCE_THREAD_ARGS *)args;
    if(reduce_args->type == 4)
    {
        nice(-20);
    }
    
    FIFO_THREAD_ARGS params[TOTAL_FILES];
    pthread_t fifoThread[TOTAL_FILES]; 
    
    
    message("Reduce Creating " + to_string(TOTAL_FILES) + " threads");
    for (int i = 0; i < TOTAL_FILES; i++)
    {
        params[i].index = i;
        params[i].stringCache = &stringCache[i]; 

        int thread_return = pthread_create(&fifoThread[i], NULL, readFIFO, &params[i]);
        if (thread_return) { return NULL; }
    }
    for (int i = 0; i < TOTAL_FILES; i++)
    {
        pthread_join(fifoThread[i], NULL);
    }
    pthread_mutex_lock(&r_mutex);
    while (!REDUCESIGNAL) {
        pthread_cond_wait(&r_cond, &r_mutex);
    }
    for (int i = 0; i < TOTAL_FILES && !THREADEXIT; i++)  {
        sortingCache.push_back(getNextLineFromFile(&stringCache[i])); 
    }

    OutputFile.open(reduce_args->output);
    while(!sortingCache.empty() && !THREADEXIT) {
        sort(sortingCache.begin(), sortingCache.end(), CustomSTRCMP);

        string line = sortingCache.front();
        OutputFile <<  line << "\n"; 
        pop_front(sortingCache); 

        string nextLine = getNextLineFromFile(&stringCache[line.length() - OFFSET]);
        if(!nextLine.empty()) {
            sortingCache.push_back(nextLine);
        }
    }
    OutputFile.close();
    message("Reducing complete, reduced filter files in outputfiles directory");
    return NULL; 
}
