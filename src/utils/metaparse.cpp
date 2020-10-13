#include "Import.h"



imp_i::SpriteData imp_i::parseSprite(const char* path) {
    SpriteData data;
    data.path = path;
    return data;
}

imp_i::SoundData imp_i::parseSound(const char* path) {
    SoundData data;
    data.path = path;
    return data;
}