#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "Helpers.h"

int map2(const string &input, const string &output);
void *map3(void *args);

