#ifndef __HELPERS__
#define __HELPERS__
#include <vector>
#include <string>
#include <queue>
#include <cassert>
#include <iostream>
using namespace std;

#define GRACEFUL_SECONDS 10
#define TOTAL_FILES 13
#define OFFSET 3

extern bool THREADEXIT;
extern vector<string> SHARED_STRING;
extern bool REDUCESIGNAL;
extern pthread_mutex_t r_mutex;
extern pthread_cond_t r_cond;


struct MAP_THREAD_ARGS {
    int index;
    vector<int> stringIndex;
    int type;
};

struct REDUCE_THREAD_ARGS {
    string output;
    int type;
};
struct FIFO_THREAD_ARGS {
    int index;
    queue<string>* stringCache; 
    int type;
};

//Functions Declarations
bool CustomSTRCMP(string s1, string s2);
bool CustomSTRCMP_TASK3(int i1, int i2);
void message(string print);
void error(string print);
void pop_front(vector<string> &vec);
string getNextLineFromFile(queue<string>* stringCache);
int createOpenFIFO(int index, int flag);
void *writeFIFO(void *args);
void *readFIFO(void *args);
void SIG_ALARM_HANDLER(int seconds);


#endif