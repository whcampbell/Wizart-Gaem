#pragma once
#include "component.h"

struct Score : public Component {
    int dropLvl;
    int score;
    int scoreMax;
};