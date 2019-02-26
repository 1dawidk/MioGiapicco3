#include "Logger.h"

void Logger::init(string fname) {
    mutex= PTHREAD_MUTEX_INITIALIZER;
    this->fname= fname;

}

void Logger::write(const string &s) {
    pthread_mutex_lock(&mutex);

    ofstream f;
    f.open(fname);
    f << s;
    f.close();

    pthread_mutex_unlock(&mutex);
}
