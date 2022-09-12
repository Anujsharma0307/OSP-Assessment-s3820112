#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include "Helpers.h"



int reduce2(const string &output);
void* reduce3(void* args);