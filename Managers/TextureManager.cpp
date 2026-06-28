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
    {"../../textures/_Idle.png", "idleKnight", 10},
    {"../../textures/_Run.png", "runKnight", 10},
    {"../../textures/_Attack.png", "attackKnight", 4},
    {"../../textures/_Attack2NoMovement.png", "SaccendAttackKnight", 6},
    {"../../textures/_Jump.png", "JumpKnight", 3},
    {"../../textures/_JumpFallInbetween.png", "JumpFallInbetweenKnight", 2},
    {"../../textures/_Fall.png", "FallKnight", 3},
    {"../../textures/_SlideTransitionStart.png", "SlideTransitionStartKnight", 2},
    {"../../textures/_Slide.png", "SlideKnight", 2},
    {"../../textures/_SlideTransitionEnd.png", "SlideTransitionEndKnight", 2},
    {"../../textures/_Hit.png", "HitKnight", 1},
    {"../../textures/_Dash.png", "dashKnight", 2},

    // ===== Hellhound =====
    {"../../textures/hell-hound-idle.png", "HellHoundIdle", 11},
    {"../../textures/hell-hound-jump.png", "HellHoundJump", 6},
    {"../../textures/hell-hound-run.png", "HellHoundRun", 5},
    {"../../textures/hell-hound-walk.png", "HellHoundWalk", 12},
    {"../../textures/hell-hound-hit.png", "HellHoundHit", 1},

    // ===== Pozadí =====
    {"../../textures/backGroundTexture/clouds.png", "CloudsBackground", 0},
    {"../../textures/backGroundTexture/town.png", "TownBackground", 0},
    {"../../textures/backGroundTexture/tiles.png", "TilesBackground", 0},

    // ===== UI =====
    {"../../textures/hpBar.png", "hpBar", 0},
    {"../../textures/hpLine.png", "hpLine", 0},
    {"../../textures/damageBAR.png", "hpDamageBar", 0},
    {"../../textures/staminaBar.png", "staminaBar", 1},
    {"../../textures/staminaLine.png", "staminaLine", 1},

    // ===== Particles =====
    {"../../textures/Gore/blood-3.png", "bloodSplash0", 5},
    {"../../textures/Gore/blood.png", "bloodSplash1", 8},
    {"../../textures/Gore/blood-2.png", "bloodSplash2", 6},
    {"../../textures/Gore/blood-small.png", "bloodSplash3", 5},
    {"../../textures/Gore/HellHoundGore/goreHellHound1.png", "GoreHellHound1", 1},
    {"../../textures/Gore/HellHoundGore/goreHellHound2.png", "GoreHellHound2", 1},
    {"../../textures/Gore/HellHoundGore/goreHellHound3.png", "GoreHellHound3", 1},
    {"../../textures/Gore/HellHoundGore/goreHellHound4.png", "GoreHellHound4", 1},
    {"../../textures/Gore/HellHoundGore/goreHellHound5.png", "GoreHellHound5", 1},

    // ===== Platformy =====
    {"../../textures/frontGround/platform1.png", "Plarform1", 1},
    {"../../textures/frontGround/Platform2.png", "Plarform2", 1},
    {"../../textures/frontGround/Plarform3.png", "Plarform3", 1},
    {"../../textures/frontGround/PlatformEag.png", "platformEagLeft", 1},
    {"../../textures/frontGround/PlatformEagRight.png", "platformEagRight", 1},

    // ===== Dalsi =====
    {"../../textures/hitbox.png", "hitbox", 1},
    {"../../textures/shedow/oleophob_silhouette.png", "shedowOfEntity", 1},
    
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
