#include "Screen.h"
#include <iostream>
#include "Engine.h"

void engine::start() {
    if (!initWindow()) {
        std::cout << "Window initialization failed" << std::endl;
    }
}



