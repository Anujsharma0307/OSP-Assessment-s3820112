#include "Map.h"


int map2(const string &input, const string &output)
{
    vector<string> inputStreams[TOTAL_FILES];
    ifstream infile;
    infile.open(output);

    for (string curLine; getline(infile, curLine);)
    {
        inputStreams[curLine.length() - OFFSET].push_back(curLine);
    }

    infile.close();
    for (int i = 0; i < TOTAL_FILES && !THREADEXIT; i++)
    {
        if (fork() == 0)
        {
            sort(inputStreams[i].begin(), inputStreams[i].end(), CustomSTRCMP);
            ofstream OutputFile;
            string outputFile = "../datafiles/FILTEREDFILES/" + to_string(i + OFFSET) + ".txt";
            OutputFile.open(outputFile, ofstream::trunc);
            for (string str : inputStreams[i])
            {
                OutputFile << str << "\n";
            }
            OutputFile.close();
            exit(0);
        }
    }
    while (wait(NULL) != -1 || errno != ECHILD);
    return 1;
}


void *map3(void *args)
{
    struct MAP_THREAD_ARGS *map_args = (struct MAP_THREAD_ARGS *)args;
    if(map_args->type == 4)
    {
        nice(-17);
    }
    vector<vector<int>> indexArray(13, vector<int>());
    MAP_THREAD_ARGS params[TOTAL_FILES];
    pthread_t fifoThread[TOTAL_FILES];

    int counter = 0;
    for (string string : SHARED_STRING)  {
        int length = string.length();
        indexArray.at(length - OFFSET).push_back(counter);
        counter++;
    }
    for(int i = 0; i < TOTAL_FILES; i++) {
        sort(indexArray.at(i).begin(), indexArray.at(i).end(), CustomSTRCMP_TASK3); 
    }
    
    message("Creating " + to_string(TOTAL_FILES) + " threads");
    for (int i = 0; i < TOTAL_FILES; i++)
    {
        params[i].index = i; 
        params[i].stringIndex = indexArray.at(i);
        int thread_return = pthread_create(&fifoThread[i], NULL, writeFIFO, &params[i]);
        if (thread_return) { return NULL; }
    }
    for (int i = 0; i < TOTAL_FILES; i++)
    {
        pthread_join(fifoThread[i], NULL);
    }
    
    pthread_mutex_lock(&r_mutex);
    REDUCESIGNAL = true;
    pthread_mutex_unlock(&r_mutex);
    pthread_cond_signal(&r_cond);
    message("Mapping complete, FIFO's created in 'datafiles/FIFO");
    return NULL;
}
