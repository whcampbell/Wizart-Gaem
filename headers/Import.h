

namespace imp {

    void importSprite(const char* path);



    void importAudio(const char* path);
}

namespace imp_i {
    struct SpriteData {
        int frames;
        const char* path;
        const char* name;
    };

    struct SoundData {
        bool isMus;
        const char* path;
        const char* name;
    };

    SpriteData parseSprite(const char* path);

    SoundData parseSound(const char* path);
}