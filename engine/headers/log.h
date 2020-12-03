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


/**
 * contains a number of values for outputting runtime logs to console and file
 */ 
namespace flog {
    
    /**
     * use log::out to output to just the console. Format is log::out << data << data << ...;
     */ 
    extern EngineLog out;

    /**
     * use log::fout to output to console and a file. Format is log::fout << data << data << ...;
     */ 
    extern EngineLog fout;

     /**
     * use << log::warn to trigger a warning output to the console. end the warning with log::endl
     */ 
    extern EngineLogWarning warn;

     /**
     * use << log::err to trigger a error output to the console. end the error with log::endl
     */ 
    extern EngineLogError err;

    /**
     * use << log::newl to create a new line without ending the current alert/warning/error
     */ 
    extern EngineLogNewline newl;

    /**
     * use << log::endl to create a new line and end the current alert/warning/error
     */ 
    extern EngineLogEndlog endl;

     /**
     * use << log::alert to trigger an alert output to the console. end the alert with log::endl
     */ 
    extern EngineLogAlert alert;

}
