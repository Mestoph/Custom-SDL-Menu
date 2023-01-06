#include "logger.h"

Logger::Logger() : 
    Logger(DEBUG_FILENAME)
{
}

Logger::Logger(const string& _filename)
{
    this->m_outfilename = _filename;
    this->m_outfile.open(_filename, ios::out | ios::app);
}

Logger::~Logger()
{
    this->m_outfile.close();
}

void Logger::write(const string& _message)
{
    if (!this->m_outfile)
        this->m_outfile.open(this->m_outfilename, ios::out | ios::app);

    lock_guard<mutex> lock(this->m_mutex);
    cerr << _message << endl;
    this->m_outfile << _message << endl;
}

void Logger::write(const string& _message, const string& _error)
{
    string msg = _message + " " + _error;
    this->write(msg);
}
