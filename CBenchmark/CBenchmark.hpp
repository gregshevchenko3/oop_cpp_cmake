#ifndef CBENCHMARK_HPP
#define CBENCHMARK_HPP

#ifdef _DEBUG


#include <string>
#include <vector>
#include <chrono>
#include <ratio>
#include <windows.h>
#include <fstream>

class Visualizer;

class TraceRecord {
    std::string m_name;
    int m_pid, m_tid;
    char m_ph;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_ts;
public:
    TraceRecord(std::string& name, std::chrono::time_point<std::chrono::high_resolution_clock> ts, char ph);
    std::string operator()() const;
};
class Timer
{
    std::string m_name;
    Visualizer& m_visualizer;
public:
    Timer(std::string name);
    ~Timer();
};
class Visualizer
{
    static Visualizer s_Visualizer;
    std::ofstream m_stream;

    std::vector<TraceRecord> m_tracerecords;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start_timepoint;
    Visualizer(std::string filename) : m_start_timepoint(std::chrono::high_resolution_clock::now()),
        m_stream(filename, std::ofstream::out | std::ofstream::trunc)
    {};
    ~Visualizer();
public:
    Visualizer(const Visualizer& other) = delete;
    static Visualizer& get();
    std::vector<TraceRecord>& get_tracerecords();
    std::chrono::time_point<std::chrono::high_resolution_clock>& get_start_timepoint();
};

#ifndef BENCHMARKING
#define BENCHMARKING(filename)   \
                Visualizer Visualizer::s_Visualizer(filename);
                //Visualizer Visualizer::s_stream(filename, std::ofstream::out | std::ofstream::trunc);
#ifndef __FUNCTION_NAME__
#if defined(WIN32) || defined(WIN64)   //WINDOWS
#define __FUNCTION_NAME__   __FUNCTION__
#else          //*NIX
#define __FUNCTION_NAME__   __func__
#endif
#endif
#define TRACE Timer __FUNCTION_NAME__##Timer(__FUNCTION_NAME__);
#endif
#else
#ifndef BENCHMARKING
#define BENCHMARKING(stream) ;
#define TRACE ;
#endif
#endif


#endif // CBENCHMARK_HPP
