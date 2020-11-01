#pragma once

enum EaseType {
    LINEAR, QUADRATIC_IN, QUADRATIC_OUT, QUADRATIC, CUBIC_IN, CUBIC_OUT, CUBIC, CIRCULAR
};

enum LoopType {
    YOYO, REPEAT, NONE
};

struct Tween {
private:

public:
    Tween* wait(int t);
    Tween* ease(EaseType type);
    Tween* time(int t);
    Tween* loop(int loops, LoopType type);

    void update();
    void render();
};


namespace tween {
    Tween transform(int* source, int* target);

    Tween transform(int* source, int target);

    Tween transform(int* source, float* target);

    Tween transform(int* source, float target);

    Tween transform(float* source, int* target);

    Tween transform(float* source, int target);

    Tween transform(float* source, float* target);

    Tween transform(float* source, float target);

    Tween run(void (*func)());
};