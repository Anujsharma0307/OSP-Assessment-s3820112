

#include "TaskFilter.h"
bool valid_length(const string param) {
    if(param.length() < 3 || param.length() > 15)
        return false;
    return true;
}
bool has_lowercase_only(const string param) {
    string criteria("abcdefghijklmnopqrstuvwxyz");
    return (string::npos == param.find_first_not_of(criteria));
}
bool more_than_two_consecs(string param) {
    for(int i = 0; i < (int)param.length() - 2; i++)
        if(param[i] == param[i+1] && param[i] == param[i+2])
            return true;
    return false;
}
int TaskFilter(const string& input, const string& output) {
    ifstream infile(input); 
    ofstream outfile(output);
    set<string> readLines; 
    for(string curLine; getline(infile, curLine) &&!THREADEXIT;) {
        if(!valid_length(curLine)) { continue; }
        if(!has_lowercase_only(curLine)) { continue; }
        if(more_than_two_consecs(curLine)) { continue; }
        readLines.insert(curLine);
    }

    for(string string: readLines) {
        outfile << string << "\n";
    }
    infile.close();
    outfile.close();
    return 1;
}