#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <fcntl.h>
#include <chrono>
#include <algorithm>
#include "Helpers.h"


bool CustomSTRCMP(string s1, string s2)
{
    if (s1.length() == 0)
    {
        return false;
    }
    if (s2.length() == 0)
    {
        return true;
    }

    return s1.substr(2, string::npos) < s2.substr(2, string::npos);
}

bool CustomSTRCMP_TASK3(int i1, int i2)
{
    string s1 = SHARED_STRING.at(i1);
    string s2 = SHARED_STRING.at(i2);
    if (s1.length() == 0)
    {
        return false;
    }
    if (s2.length() == 0)
    {
        return true;
    }

    return s1.substr(2, string::npos) < s2.substr(2, string::npos);
}


void message(string print)
{
    cout << to_string(getpid()) + " | " + print + "\n";
    cout.flush();
}
void error(string print)
{
    cerr << to_string(getpid()) + " | " + print + "\n";
    cerr.flush();
}

void pop_front(vector<string> &vec)
{
    // https://stackoverflow.com/questions/9445327/fast-way-to-implement-pop-front-to-a-stdvector
    assert(!vec.empty());
    vec.erase(vec.begin());
}


string getNextLineFromFile(queue<string>* stringCache) {
    string line; 

    if(stringCache->size() == 0) {
        return "";
    }
    line = stringCache->front();
    stringCache->pop(); 
    return line; 
}

int createOpenFIFO(int index, int flag) {
    if(mkfifo(("../datafiles/FIFO/" + to_string(index + OFFSET)).c_str(), 0777) == -1) {
            if(errno != EEXIST) {
                error("Creating FIFO Failed");
                return -1; 
            }
        }
        
    int handle = open(("../datafiles/FIFO/" + to_string(index + OFFSET)).c_str(), flag);
    if(handle == -1) { return -1; }

    return handle; 
}

void *writeFIFO(void *args) 
{
    struct MAP_THREAD_ARGS *__args__ = (struct MAP_THREAD_ARGS *)args;
    if(__args__->type == 4)
    {
        nice(-18);
    }
    
    int fifoHandle = createOpenFIFO(__args__->index, O_WRONLY); 
    if(fifoHandle == -1) { return NULL; }
    for(int index = 0; index < (int)__args__->stringIndex.size() && !THREADEXIT; index++) {
        if (write(fifoHandle, &__args__->stringIndex.at(index), sizeof(int)) == -1) {
            error("Error writing FIFO file");
            return NULL;
        };
    };
    close(fifoHandle); 
    return NULL;
}


  
void *readFIFO(void *args)  
{
    struct FIFO_THREAD_ARGS *__args__ = (struct FIFO_THREAD_ARGS *)args;
    if(__args__->type == 4)
    {
        nice(-19);
    }
    
    int fifoHandle = createOpenFIFO(__args__->index, O_RDONLY); 
    if(fifoHandle == -1) { return NULL; }

    int index; 
    while(read(fifoHandle, &index, sizeof(int)) > 0 && !THREADEXIT) {
        __args__->stringCache->push(SHARED_STRING.at(index)); 
    }
    close(fifoHandle); 
    return NULL;
}






void SIG_ALARM_HANDLER(int seconds) {
    cerr << "Program running to long, " << GRACEFUL_SECONDS ;
    cerr << "is the limit" <<endl;
    THREADEXIT = true; 
}