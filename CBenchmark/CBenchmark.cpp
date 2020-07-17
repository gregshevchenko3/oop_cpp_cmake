#include "CBenchmark.hpp"
#include <sstream>
#include <fstream>
#include <iostream>

#ifdef _DEBUG

Timer::Timer(std::string name) : m_visualizer(Visualizer::get()), m_name(name)
{
    m_visualizer.get_tracerecords().push_back(TraceRecord(m_name, std::chrono::high_resolution_clock::now(), 'B'));
}
Timer::~Timer()
{
    m_visualizer.get_tracerecords().push_back(TraceRecord(m_name, std::chrono::high_resolution_clock::now(), 'E'));
}
TraceRecord::TraceRecord(std::string& name, std::chrono::time_point<std::chrono::high_resolution_clock> ts, char ph):
    m_name(name), m_ts(ts), m_ph(ph)
{
#if defined(_WIN32) || defined(_WIN64)
    m_pid = GetCurrentProcessId();
    m_tid = GetCurrentThreadId();
#endif
}
std::string TraceRecord::operator()() const
{
    std::stringstream ss;
    ss << "{\n";
    ss << "\t\"name\":" << " \"" << m_name << "\"" << ",\n";
    ss << "\t\"cat\":" << " \"PERF\"" << ",\n";
    ss << "\t\"ph\":" << " \"" << m_ph << "\"" << ",\n";
    ss << "\t\"pid\":" << m_pid << ",\n";
    ss << "\t\"tid\":" <<  m_tid <<  ",\n";
    ss << "\t\"ts\":" <<  (m_ts - Visualizer::get().get_start_timepoint()).count() << "\n}";
    return ss.str();
}
Visualizer& Visualizer::get()
{
    return s_Visualizer;
}
std::vector<TraceRecord>& Visualizer::get_tracerecords()
{
    return m_tracerecords;
}
std::chrono::time_point<std::chrono::high_resolution_clock>& Visualizer::get_start_timepoint()
{
    return m_start_timepoint;
}
Visualizer::~Visualizer()
{
    m_stream << "{\n\"traceEvents\":\n\t[\n";

    auto it = m_tracerecords.begin(), end = m_tracerecords.end() - 1;
    while (it != end)
    {
        m_stream << "\t\t\t" << (*it)() << ",\n";
        it++;
    }
    m_stream << "\t\t\t" << (*it)() << "\n";
    m_stream << "\t],\n\t\"displayTimeUnit\": \"ns\",\n\t\"systemTraceEvents\": \"SystemTraceData\",\n\"controllerTraceDataKey\": \"traceEvents\"\n";
    m_stream << "}";
}
#endif
