#ifndef GAMESTAT_H_INCLUDED
#define GAMESTAT_H_INCLUDED

#include "Component.h"

class GameStat : public Component {
public:
    int health = 100;
    int maxHealth = 100;
    int attackDamage = 10;

    GameStat() {}
    GameStat(int hp, int dmg) : health(hp), maxHealth(hp), attackDamage(dmg) {}

    void takeDamage(int amount) {
        health -= amount;
        if (health < 0) health = 0;
    }

    bool isDead() const {
        return health <= 0;
    }

    void heal(int amount) {
        health += amount;
        if (health > maxHealth) health = maxHealth;
    }

    void init() override {

    }

    void update() override {

    }
};

#endif // GAMESTAT_H_INCLUDED
