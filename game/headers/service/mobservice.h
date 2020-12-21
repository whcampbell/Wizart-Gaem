#pragma once
#include <string>

struct Mob {
  std::string name;
  bool isHostile;
  bool isBoss;
  int baseHealth;
  int scaledHealth;
  int baseDamage;
  int scaledDamage;
  int baseSpeed;
  int scaledSpeed;
};

Mob getMob(int id);