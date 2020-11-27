#pragma once


#include <string>
struct EngineLogWarning {};
struct EngineLogError {};
struct EngineLogNewline {};
struct EngineLogEndlog {};
struct EngineLogAlert {};

struct EngineLog {
private:
    bool printing, normal;
    std::string file;
public:
    EngineLog();
    EngineLog(bool print);
    EngineLog operator<<(const char* s);
    EngineLog operator<<(std::string const& s);
    EngineLog operator<<(int const& s);
    EngineLog operator<<(char const& s);
    EngineLog operator<<(bool const& s);
    EngineLog operator<<(float const& s);
    EngineLog operator<<(double const& s);
    EngineLog operator<<(wchar_t const& s);

    EngineLog operator<<(short const& s);
    EngineLog operator<<(unsigned short const& s);
    EngineLog operator<<(unsigned int const& s);
    EngineLog operator<<(long const& s);
    EngineLog operator<<(unsigned long const& s);
    EngineLog operator<<(long long const& s);
    EngineLog operator<<(unsigned long long const& s);
    EngineLog operator<<(long double const& s);


    EngineLog operator<<(EngineLogWarning const& s);
    EngineLog operator<<(EngineLogError const& s);
    EngineLog operator<<(EngineLogNewline const& s);
    EngineLog operator<<(EngineLogEndlog const& s);
    EngineLog operator<<(EngineLogAlert const& s);
};



namespace log {
    extern EngineLog out;
    extern EngineLog fout;
    extern EngineLogWarning warn;
    extern EngineLogError err;
    extern EngineLogNewline newl;
    extern EngineLogEndlog endl;
    extern EngineLogAlert alert;
}
