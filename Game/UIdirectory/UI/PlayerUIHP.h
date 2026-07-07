//
// Created by Oliver Šmítek on 18.03.2026.
//

#ifndef PLAYERUIHP_H
#define PLAYERUIHP_H
#include "../UIManager.h"


class PlayerUIHP : public UIManager {

    PlayerUIHP();

    sf::Vector2f scale;

public:
    static PlayerUIHP& getInstance(){
        static PlayerUIHP theInstance;
        return theInstance;
    }

    void updateHPbar(int hp, sf::RenderWindow &window);
};


#endif //PLAYERUIHP_H
