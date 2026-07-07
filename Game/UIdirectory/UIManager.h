//
// Created by Oliver Šmítek on 12.03.2026.
//

#include "../Managers/SpriteManager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../Managers/TextureManager.h"


#ifndef UIMANAGER_H
#define UIMANAGER_H



class UIManager {
    //PlayerUI:
public:
    int sorceMAX;
    int pastSorce;
    int maxDashes;
    int offSetOfDashesUIs = 110;
    float dashScaleRemaber;

    sf::Vector2f posOutLine;
    sf::Vector2f posInLine;
    sf::Vector2f posBar;

    float posInLineDraw = 0.f;
    float posOutLineDraw = 0.f;
    float posBarDraw = 0.f;

    sf::Sprite BarOutline;
    sf::Sprite Bar;
    sf::Sprite DecreseSorceBar;

    sf::Clock cooldownOnHit;
public:

    UIManager(int sorce, sf::Vector2f posOutLine, sf::Vector2f posInLine,sf::Vector2f posLine, const std::string &nameOfTextureOutLine, const std::string &nameOfTextureInLine, const std::string &nameOfTextureLine);

    void updateUIHPBar(sf::RenderWindow &window, int hp, sf::Vector2f scale);
    void updateUIStaminaBar(int dashNumOfUse, sf::Clock timerStam, sf::RenderWindow &window);
};

#endif //UIMANAGER_H
