#include "import.h"
#include "resource.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>

namespace fs = std::filesystem;
using ios = std::ifstream;



imp_i::SpriteData imp_i::parseSprite(std::string path) {
    SpriteData data;
    std::ifstream stream(path, ios::in|ios::binary);
    stream.read(reinterpret_cast<char*>(&(data.frames)), sizeof(int));
    int name;
    stream.read(reinterpret_cast<char*>(&name), sizeof(int));
    char* str_name = new char[name + 1];
    stream.read(str_name, name);
    str_name[name + 1] = (char)NULL;
    std::string str_name_val(str_name);
    str_name_val = str_name_val.substr(0, name);
    data.name = str_name_val.c_str();
    data.path = path.substr(0, path.length() - 5).c_str();
    stream.close();
    return data;
}

imp_i::SoundData imp_i::parseSound(std::string path) {
    SoundData data;
    std::ifstream stream(path, ios::in|ios::binary);
    stream.read(reinterpret_cast<char*>(&data.isMus), sizeof(bool));
    int name;
    stream.read(reinterpret_cast<char*>(&name), sizeof(int));
    char* str_name = new char[name + 1];
    stream.read(str_name, name);
    str_name[name + 1] = (char)NULL;
    std::string str_name_val(str_name);
    str_name_val = str_name_val.substr(0, name);
    data.name = str_name_val.c_str();
    data.path = path.substr(0, path.length() - 5).c_str();
    stream.close();
    return data;
}

void recurseDir(std::string path) {
    for (const auto & entry : fs::directory_iterator(path)) {
        if ( entry.is_directory()) {
            recurseDir(entry.path().string());
        } else {
            if (!entry.path().extension().string().compare(".meta")) {
                std::cout << "importing resource at " << entry.path().string().substr(0, entry.path().string().length() - 5) << std::endl;
                if (entry.path().filename().string().find(".png") != std::string::npos) {
                    imp::importSprite(entry.path().string().c_str());
                } else {
                    imp::importAudio(entry.path().string().c_str());
                }
            }
        }
    }
}

void res::init() {
    sfx_i::init();
    std::cout << "starting resource import" << std::endl;
    std::string path = "./res";
    spr_i::init();
    recurseDir(path);
    std::cout << "finished resource import" << std::endl;
}

void res::close() {

}