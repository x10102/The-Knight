//
// Created by Oliver Šmítek on 16.12.2025.
//

#include "TextureManager.h"
#include <SFML/Graphics/Texture.hpp>
#include <initializer_list>
#include <stdexcept>
#include <format>
#include <string>

TextureManager::TextureManager() {
    this->loadTextures({
    // ===== Player =====
    {"../../Game/textures/PlayerTextures/_Idle.png", "idleKnight", 10},
    {"../../Game/textures/PlayerTextures/_Run.png", "runKnight", 10},
    {"../../Game/textures/PlayerTextures/_Attack.png", "attackKnight", 4},
    {"../../Game/textures/PlayerTextures/_Attack2NoMovement.png", "SaccendAttackKnight", 6},
    {"../../Game/textures/PlayerTextures/_Jump.png", "JumpKnight", 3},
    {"../../Game/textures/PlayerTextures/_JumpFallInbetween.png", "JumpFallInbetweenKnight", 2},
    {"../../Game/textures/PlayerTextures/_Fall.png", "FallKnight", 3},
    {"../../Game/textures/PlayerTextures/_SlideTransitionStart.png", "SlideTransitionStartKnight", 2},
    {"../../Game/textures/PlayerTextures/_Slide.png", "SlideKnight", 2},
    {"../../Game/textures/PlayerTextures/_SlideTransitionEnd.png", "SlideTransitionEndKnight", 2},
    {"../../Game/textures/PlayerTextures/_Hit.png", "HitKnight", 1},
    {"../../Game/textures/PlayerTextures/_Dash.png", "dashKnight", 2},

    // ===== Hellhound =====
    {"../../Game/textures/HellHoundTextures/hell-hound-idle.png", "HellHoundIdle", 11},
    {"../../Game/textures/HellHoundTextures/hell-hound-jump.png", "HellHoundJump", 6},
    {"../../Game/textures/HellHoundTextures/hell-hound-run.png", "HellHoundRun", 5},
    {"../../Game/textures/HellHoundTextures/hell-hound-walk.png", "HellHoundWalk", 12},
    {"../../Game/textures/HellHoundTextures/hell-hound-hit.png", "HellHoundHit", 1},

    // ===== Pozadí =====
    {"../../Game/textures/backGroundTexture/clouds.png", "CloudsBackground", 0},
    {"../../Game/textures/backGroundTexture/town.png", "TownBackground", 0},
    {"../../Game/textures/backGroundTexture/tiles.png", "TilesBackground", 0},

    // ===== UI =====
    {"../../Game/textures/UI/PlayerUI/HPbar/hpBar.png", "hpBar", 0},
    {"../../Game/textures/UI/PlayerUI/HPbar/hpLine.png", "hpLine", 0},
    {"../../Game/textures/UI/PlayerUI/HPbar/damageBAR.png", "hpDamageBar", 0},
    {"../../Game/textures/UI/PlayerUI/StaminaBar/staminaBar.png", "staminaBar", 0},
    {"../../Game/textures/UI/PlayerUI/StaminaBar/staminaLine.png", "staminaLine", 0},
    {"../../Game/textures/UI/PlayerUI/StaminaBar/resorceLine.png", "staminaReSorce", 0},

    // ===== Particles =====
    {"../../Game/textures/Gore/blood-3.png", "bloodSplash0", 5},
    {"../../Game/textures/Gore/blood.png", "bloodSplash1", 8},
    {"../../Game/textures/Gore/blood-2.png", "bloodSplash2", 6},
    {"../../Game/textures/Gore/blood-small.png", "bloodSplash3", 5},
    {"../../Game/textures/Gore/HellHoundGore/goreHellHound1.png", "GoreHellHound1", 1},
    {"../../Game/textures/Gore/HellHoundGore/goreHellHound2.png", "GoreHellHound2", 1},
    {"../../Game/textures/Gore/HellHoundGore/goreHellHound3.png", "GoreHellHound3", 1},
    {"../../Game/textures/Gore/HellHoundGore/goreHellHound4.png", "GoreHellHound4", 1},
    {"../../Game/textures/Gore/HellHoundGore/goreHellHound5.png", "GoreHellHound5", 1},

    // ===== Platformy =====
    {"../../Game/textures/frontGround/platform1.png", "Plarform1", 1},
    {"../../Game/textures/frontGround/Platform2.png", "Plarform2", 1},
    {"../../Game/textures/frontGround/Plarform3.png", "Plarform3", 1},
    {"../../Game/textures/frontGround/PlatformEag.png", "platformEagLeft", 1},
    {"../../Game/textures/frontGround/PlatformEagRight.png", "platformEagRight", 1},

    // ===== Dalsi =====
    {"../../Game/textures/hitbox.png", "hitbox", 1},
    {"../../Game/textures/shedow/oleophob_silhouette.png", "shedowOfEntity", 1},
    
    });
}

void TextureManager::loadTextures(const std::initializer_list<TextureMapItem> init) {
    sf::Texture temp;

    for(const auto &tex : init) {
        if(!temp.loadFromFile(tex.path)) {
            const std::string errorStr = std::format("Nelze načíst texturu {} ze souboru {}", tex.name, tex.path);
            throw std::runtime_error(errorStr);
        }
        textures[tex.name] = temp;

        if(tex.frameCount != 0)
            numOfFramesTextures[tex.name] = tex.frameCount;
    }
}

void TextureManager::setTexture(std::string nameOfTexture, sf::Sprite *spriteToInsertTo) {
    spriteToInsertTo->setTexture(textures.at(nameOfTexture));
}

sf::Texture TextureManager::getTextureFromEntity(std::string nameOfTexture) {
    return  textures.at(nameOfTexture);
}
