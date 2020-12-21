#include "internal/import.h"
#include "internal/resource.h"
#include <filesystem>
#include <fstream>
#include <string>
#include "log.h"

namespace fs = std::filesystem;
using ios = std::ifstream;



imp::SpriteData imp::parseSprite(std::string path) {
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

imp::SoundData imp::parseSound(std::string path) {
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
                flog::out << "importing resource at " << entry.path().string().substr(0, entry.path().string().length() - 5) << flog::endl;
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
    sfx::init();
    flog::out << "starting resource import" << flog::endl;
    std::string path = "./res";
    spr::init();
    recurseDir(path);
    flog::out << "finished resource import" << flog::endl;
}

void res::close() {

}