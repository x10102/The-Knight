//
// Created by Oliver Šmítek on 02.06.2026.
//

#include "PlayerUIStamina.h"

PlayerUIStamina::PlayerUIStamina() : UIManager(100, {50,80}, {67,94}, {67,94}, "staminaBar", "staminaLine","staminaReSorce") {
    scale = sf::Vector2f(4.5, 4.5);
    maxDashes = 2;
}

void PlayerUIStamina::updateStaminabar(int stamina, sf::Clock staminaNum, sf::RenderWindow &window) {
    this->updateUIStaminaBar(stamina, staminaNum, window);

}

