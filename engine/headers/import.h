#pragma once
#include <string>

namespace imp {

    void importSprite(std::string path);



    void importAudio(std::string path);
}

namespace imp_i {
    struct SpriteData {
        int frames;
        std::string path;
        std::string name;
    };

    struct SoundData {
        bool isMus;
        std::string path;
        std::string name;
    };

    SpriteData parseSprite(std::string path);

    SoundData parseSound(std::string path);
}