//
// Created by Oliver Šmítek on 02.06.2026.
//

#include "PlayerUIStamina.h"

PlayerUIStamina::PlayerUIStamina() : UIManager(100, {50,30}, {67,44}, {67,44}, "none", "staminaLine","staminaBar") {

    scale = sf::Vector2f(4.5, 4.5);
}

void PlayerUIStamina::updateStaminabar(int stamina, sf::Clock staminaNum, sf::RenderWindow &window) {

}

