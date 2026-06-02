//
// Created by Oliver Šmítek on 02.06.2026.
//

#ifndef PLAYERUISTAMINA_H
#define PLAYERUISTAMINA_H

#include "../UIManager.h"



class PlayerUIStamina : public UIManager{

    PlayerUIStamina();

    sf::Vector2f scale;

public:
    static PlayerUIStamina& getInstance(){
        static PlayerUIStamina theInstance;
        return theInstance;
    }

    void updateStaminabar(int stamina,sf::Clock staminaNum, sf::RenderWindow &window);
};



#endif //PLAYERUISTAMINA_H
