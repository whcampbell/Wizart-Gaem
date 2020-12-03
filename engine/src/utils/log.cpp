    #include <iostream>
    #include <fstream>
    #include <filesystem>
    #include "log.h"

namespace flog {
    EngineLog out;
    EngineLog fout(true);
    EngineLogWarning warn;
    EngineLogError err;
    EngineLogNewline newl;
    EngineLogEndlog endl;
    EngineLogAlert alert;
}

    static std::ofstream output;

    EngineLog::EngineLog() {printing = false; normal = true;}
    EngineLog::EngineLog(bool print) {
        normal = true;
        printing = print;
        std::filesystem::create_directory("./logs");
        file = "./logs/log";
        int i = 0;
        while (std::filesystem::exists(file.append(std::to_string(i)).append(".txt"))) {
            file = "./logs/log";
            i++;
        }
    }

    EngineLog EngineLog::operator<<(const char* s) {
        if (normal)
            std::cout << s;
        else
            std::cout << "\x1b[37;1m" << s << "\x1b[0m"; 
        if (printing) {
            output.open(file, std::ofstream::out | std::ofstream::app);
            output << s;
            output.close();
        }
        return *this;
    }
    EngineLog EngineLog::operator<<(std::string const& s) {
        if (normal)
            std::cout << s;
        else
            std::cout << "\x1b[37;1m" << s << "\x1b[0m"; 
        if (printing) {
            output.open(file, std::ofstream::out | std::ofstream::app);
            output << s;
            output.close();
        }
        return *this;
    }
    EngineLog EngineLog::operator<<(int const& s) {
        if (normal)
            std::cout << s;
        else
            std::cout << "\x1b[37;1m" << s << "\x1b[0m"; 
        if (printing) {
            output.open(file, std::ofstream::out | std::ofstream::app);
            output << s;
            output.close();
        }
        return *this;
    }
    EngineLog EngineLog::operator<<(char const& s) {
        if (normal)
            std::cout << s;
        else
            std::cout << "\x1b[37;1m" << s << "\x1b[0m"; 
        if (printing) {
            output.open(file, std::ofstream::out | std::ofstream::app);
            output << s;
            output.close();
        }
        return *this;
    }
    EngineLog EngineLog::operator<<(bool const& s) {
        if (normal)
            std::cout << s;
        else
            std::cout << "\x1b[37;1m" << s << "\x1b[0m"; 
        if (printing) {
            output.open(file, std::ofstream::out | std::ofstream::app);
            output << s;
            output.close();
        }
        return *this;
    }
    EngineLog EngineLog::operator<<(float const& s) {
        if (normal)
            std::cout << s;
        else
            std::cout << "\x1b[37;1m" << s << "\x1b[0m"; 
        if (printing) {
            output.open(file, std::ofstream::out | std::ofstream::app);
            output << s;
            output.close();
        }
        return *this;
    }
    EngineLog EngineLog::operator<<(double const& s) {
        if (normal)
            std::cout << s;
        else
            std::cout << "\x1b[37;1m" << s << "\x1b[0m"; 
        if (printing) {
            output.open(file, std::ofstream::out | std::ofstream::app);
            output << s;
            output.close();
        }
        return *this;
    }
    EngineLog EngineLog::operator<<(wchar_t const& s) {
        if (normal)
            std::wcout << s;
        else
            std::wcout << "\x1b[37;1m" << s << "\x1b[0m"; 
        if (printing) {
            output.open(file, std::ofstream::out | std::ofstream::app);
            output << s;
            output.close();
        }
        return *this;
    }
    EngineLog EngineLog::operator<<(short const& s) {
        if (normal)
            std::cout << s;
        else
            std::cout << "\x1b[37;1m" << s << "\x1b[0m"; 
        if (printing) {
            output.open(file, std::ofstream::out | std::ofstream::app);
            output << s;
            output.close();
        }
        return *this;
    }
    EngineLog EngineLog::operator<<(unsigned short const& s) {
        if (normal)
            std::cout << s;
        else
            std::cout << "\x1b[37;1m" << s << "\x1b[0m"; 
        if (printing) {
            output.open(file, std::ofstream::out | std::ofstream::app);
            output << s;
            output.close();
        }
        return *this;
    }
    EngineLog EngineLog::operator<<(unsigned int const& s) {
        if (normal)
            std::cout << s;
        else
            std::cout << "\x1b[37;1m" << s << "\x1b[0m"; 
        if (printing) {
            output.open(file, std::ofstream::out | std::ofstream::app);
            output << s;
            output.close();
        }
        return *this;
    }
    EngineLog EngineLog::operator<<(long const& s) {
        if (normal)
            std::cout << s;
        else
            std::cout << "\x1b[37;1m" << s << "\x1b[0m"; 
        if (printing) {
            output.open(file, std::ofstream::out | std::ofstream::app);
            output << s;
            output.close();
        }
        return *this;
    }
    EngineLog EngineLog::operator<<(unsigned long const& s) {
        if (normal)
            std::cout << s;
        else
            std::cout << "\x1b[37;1m" << s << "\x1b[0m"; 
        if (printing) {
            output.open(file, std::ofstream::out | std::ofstream::app);
            output << s;
            output.close();
        }
        return *this;
    }
    EngineLog EngineLog::operator<<(long long const& s) {
        if (normal)
            std::cout << s;
        else
            std::cout << "\x1b[37;1m" << s << "\x1b[0m"; 
        if (printing) {
            output.open(file, std::ofstream::out | std::ofstream::app);
            output << s;
            output.close();
        }
        return *this;
    }
    EngineLog EngineLog::operator<<(unsigned long long const& s) {
        if (normal)
            std::cout << s;
        else
            std::cout << "\x1b[37;1m" << s << "\x1b[0m"; 
        if (printing) {
            output.open(file, std::ofstream::out | std::ofstream::app);
            output << s;
            output.close();
        }
        return *this;
    }
    EngineLog EngineLog::operator<<(long double const& s) {
        if (normal)
            std::cout << s;
        else
            std::cout << "\x1b[37;1m" << s << "\x1b[0m";   
        if (printing) {
            output.open(file, std::ofstream::out | std::ofstream::app);
            output << s;
            output.close();
        }
        return *this;
    }

    EngineLog EngineLog::operator<<(EngineLogWarning const& s) {
        std::cout << "\x1b[0m[\x1b[33;1mWARNING\x1b[0m]: ";
        if (printing){
            output.open(file, std::ofstream::out | std::ofstream::app);
            output << "[WARNING]: ";
            output.close();
            flog::fout.normal = false;
            this->normal = false;
            return *this;
        }
        flog::out.normal = false;
        this->normal = false;
        return *this;
    }
    EngineLog EngineLog::operator<<(EngineLogError const& s) {
        std::cout << "\x1b[0m[\x1b[31mERROR\x1b[0m]: ";
        if (printing) {
            output.open(file, std::ofstream::out | std::ofstream::app);
            output << "[ERROR]: ";
            output.close();
            flog::fout.normal = false;
            this->normal = false;
            return *this;
        }
        flog::out.normal = false;
        this->normal = false;
        return *this;
    }
    EngineLog EngineLog::operator<<(EngineLogAlert const& s) {
        std::cout << "\x1b[0m[\x1b[34;1mALERT\x1b[0m]: ";
        if (printing) {
            output.open(file, std::ofstream::out | std::ofstream::app);
            output << "[ALERT]: ";
            output.close();
            flog::fout.normal = false;
            this->normal = false;
            return *this;
        }
        flog::out.normal = false;
        this->normal = false;
        return *this;
    }
    EngineLog EngineLog::operator<<(EngineLogNewline const& s) {
        std::cout << std::endl;
        if (printing) {
            output.open(file, std::ofstream::out | std::ofstream::app);
            output << "\n";
            output.close();
        }
            
        return *this;
    }
    EngineLog EngineLog::operator<<(EngineLogEndlog const& s) {
        std::cout << std::endl << "\x1b[0m";
        if (printing) {
            output.open(file, std::ofstream::out | std::ofstream::app);
            output << "\n";
            output.close();
            flog::fout.normal = true;
            this->normal = true;
            return *this;
        }
        flog::out.normal = true;
        this->normal = true;
        return *this;
    }