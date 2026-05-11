//
// Created by Oliver Šmítek on 12.03.2026.
//

#include "../Managers/SpriteManager.h"
#include "../cmake-build-debug/_deps/sfml-src/include/SFML/Graphics/Sprite.hpp"
#include "../cmake-build-debug/_deps/sfml-src/include/SFML/Graphics/RenderWindow.hpp"
#include "../Managers/TextureManager.h"


#ifndef UIMANAGER_H
#define UIMANAGER_H



class UIManager {
    //PlayerUI:

    TextureManager* textureManager{};
    SpriteManager* spriteManager{};

    int hpMAX;
    int pastHP;

    sf::Vector2f posOutLine;
    sf::Vector2f posInLine;
    sf::Vector2f posDamageBar;



    sf::Sprite HPBarOutline;
    sf::Sprite HPBar;
    sf::Sprite DamageBar;

    sf::Clock cooldownOnHit;
public:

    UIManager(int hp, sf::Vector2f posOutLine, sf::Vector2f posInLine,sf::Vector2f posDamageLine, std::string nameOfTextureOutLine, std::string nameOfSpriteOutLine, std::string nameOfDamageBar);


    void updateUIHPBar(sf::RenderWindow &window, int hp, sf::Vector2f scale);
};

#endif //UIMANAGER_H
