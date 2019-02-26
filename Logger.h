#ifndef MIOGIAPICCO_LOGGER_H
#define MIOGIAPICCO_LOGGER_H

#include "pthread.h"
#include "string"
#include "fstream"

using namespace std;

class Logger {
public:
    void init(string fname);
    void write(const string &s);
private:
    pthread_mutex_t mutex;
    string fname;
};


#endif //MIOGIAPICCO_LOGGER_H
