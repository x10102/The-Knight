//
// Created by Oliver Šmítek on 18.03.2026.
//

#include "PlayerUIHP.h"

#include "../UIManager.h"


PlayerUIHP::PlayerUIHP() : UIManager(100, {50,30}, {67,44}, {67,44}, "hpBar", "hpLine","hpDamageBar") {

    scale = sf::Vector2f(4.5, 4.5);
}

void PlayerUIHP::updateHPbar(int hp,sf::RenderWindow& window) {
    this->updateUIHPBar(window, hp, scale);
}


