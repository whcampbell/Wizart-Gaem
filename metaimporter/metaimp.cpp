#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <cctype>

namespace fs = std::filesystem;



int VALID_EXTENTION_COUNT = 0;
struct Extention {
public:
    const int flag;
    const char* text;
    Extention(const char* str) : flag(VALID_EXTENTION_COUNT), text(str) {
        VALID_EXTENTION_COUNT++;
    }
    constexpr operator int() const {
        return flag;
    }
};

const Extention PNG(".png");
const Extention OGG(".ogg");
const Extention WAV(".wav");
const Extention VALID_EXTENTIONS[] =  {PNG, OGG, WAV};

bool flag_r = 0, flag_o = 0, flag_a = 0, flag_f =  0;


int extentionFlag(std::string ext) {
    for (int i = 0; i < VALID_EXTENTION_COUNT; i++)
        if (!ext.compare(VALID_EXTENTIONS[i].text))
            return VALID_EXTENTIONS[i].flag;
    return -1;
}

bool isValidExtention(std::string ext) {
    for (int i = 0; i < VALID_EXTENTION_COUNT; i++)
        if (!ext.compare(VALID_EXTENTIONS[i].text))
            return true;
    return false;
}

void logData(fs::path path, std::string ref, int frames) {
    if (fs::remove(path))
        std::cout << "Removed existing metafile: " << path.filename() << std::endl;
    std::ofstream file(path, std::ofstream::out | std::ofstream::binary);
    int ref_size = ref.size();
    file.write(reinterpret_cast<char*>(&frames), sizeof(int));
    file.write(reinterpret_cast<char*>(&ref_size), sizeof(int));
    file.write(ref.c_str(), ref.size());
    file.close();
    std::cout << "created new metafile: " << path.filename() << std::endl;
}

void logData(fs::path path, std::string ref, bool isMus) {
    if (fs::remove(path))
        std::cout << "Removed existing metafile: " << path.filename() << std::endl;
    std::ofstream file(path, std::ofstream::out | std::ofstream::binary);
    int ref_size = ref.size();
    file.write(reinterpret_cast<char*>(&isMus), sizeof(bool));
    file.write(reinterpret_cast<char*>(&ref_size), sizeof(int));
    file.write(ref.c_str(), ref.size());
    file.close();
    std::cout << "created new metafile: " << path.filename() << std::endl;
}

std::string getExtention(fs::directory_entry entry) {
    return entry.path().extension().string();
}


//TODO add cases for new filetypes
void parseFile(fs::directory_entry entry) {
    std::string ext = getExtention(entry);
    fs::path path = entry.path();
    path.concat(".meta");
    if (isValidExtention(ext) && (flag_a || !fs::exists(path))) {
        int extflag = extentionFlag(ext);
        std::cout << "Generating metafile for file " << entry.path().string() << std::endl;
        if (extflag == (int)PNG)
        {
            std::cout << "Enter the frame count" << std::endl;
            int frames;
            std::cin >> frames;
            std::cout << "Enter the name this animation will be referred to in code" << std::endl;
            std::string referenceName;
            std::cin >> referenceName;
            logData(path, referenceName, frames);
        } else if (extflag == (int)OGG) {

            std::string mus;
            std::cout << "Is this sound effect a musical track? (y/n)" << std::endl;
            std::cin >> mus;
            std::transform(mus.begin(), mus.end(), mus.begin(), [](unsigned char c){ return std::tolower(c); });
            bool isMus = mus.at(0) != 'n';
            std::cout << "Enter the name this animation will be referred to in code" << std::endl;
            std::string referenceName;
            std::cin >> referenceName;
            logData(path, referenceName, isMus);

        } else if (extflag == (int)WAV) {

            std::string mus;
            std::cout << "Is this sound effect a musical track? (y/n)" << std::endl;
            std::cin >> mus;
            std::transform(mus.begin(), mus.end(), mus.begin(), [](unsigned char c){ return std::tolower(c); });
            bool isMus = mus.at(0) != 'n';
            std::cout << "Enter the name this animation will be referred to in code" << std::endl;
            std::string referenceName;
            std::cin >> referenceName;
            logData(path, referenceName, isMus);

        } else {
            std::cout << "beanboy says: NO MORE BEANS :(";
        }


    }
}

void readfile(fs::directory_entry entry) {
    if (!entry.path().extension().string().compare(".meta")) {
        std::cout << entry.path().filename().string() << " metadata: ";
        
    }

}

void searchDir(std::string path) {
    for (const auto & entry : fs::directory_iterator(path))
        if (!entry.is_directory()) {
            if (flag_o)
                readfile(entry);
            else
                parseFile(entry);
        }
}

void recurseDir(std::string path) {
    for (const auto & entry : fs::directory_iterator(path)) {
        if (entry.is_directory()) {
            recurseDir(entry.path().string());
        } else {
            if (flag_o)
                readfile(entry);
            else
                parseFile(entry);
        }
    }
}

int main(int argc, char* argv[]) {
    std::string path = "./";
    std::vector<char*> params;
    char opt;
    for (int i = 0; i < argc; i++) {
        opt = *(argv[i] + 1);
        switch (opt) {
            case 'f':
                flag_f = 1;
                params.push_back(argv[i + 1]);
                break;
            case 'r':
                flag_r = 1;
                break;
            case 'a':
                flag_a = 1;
                break;
            case 'o':
                flag_o = 1;
                break;
        }
    }

    if (flag_f) {
        for (int i = 0; i < params.size(); i++)
        if (flag_r) {
            recurseDir(path + params[i]);
        } else {
            searchDir(path + params[i]);
        }
    } else {
        recurseDir("./res");
    }
    std::cout << "metafile generation complete" << std::endl;
}