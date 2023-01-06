#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <mutex>

#include "constants.h"

class Logger
{
public:
    Logger();
    Logger(const string& _filename);
    ~Logger();

    void write(const string& _message);
    void write(const string& _message, const string& _error);

private:
    string m_outfilename;
    ofstream m_outfile;
    mutex m_mutex;
};

#endif
