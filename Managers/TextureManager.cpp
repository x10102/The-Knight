//
// Created by Oliver Šmítek on 16.12.2025.
//

#include "TextureManager.h"


TextureManager::TextureManager() {
    sf::Texture texture;
    if (!texture.loadFromFile("../../textures/_Idle.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["idleKnight"] = texture;
    numOfFramesTextures["idleKnight"] = 10;

    if (!texture.loadFromFile("../../textures/_Run.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["runKnight"] = texture;
    numOfFramesTextures["runKnight"] = 10;


    if (!texture.loadFromFile("../../textures/_Attack.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["attackKnight"] = texture;
    numOfFramesTextures["attackKnight"] = 4;


    if (!texture.loadFromFile("../../textures/_Attack2NoMovement.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["SaccendAttackKnight"] = texture;
    numOfFramesTextures["SaccendAttackKnight"] = 6;


    if (!texture.loadFromFile("../../textures/_Jump.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["JumpKnight"] = texture;
    numOfFramesTextures["JumpKnight"] = 3;


    if (!texture.loadFromFile("../../textures/_JumpFallInbetween.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["JumpFallInbetweenKnight"] = texture;
    numOfFramesTextures["JumpFallInbetweenKnight"] = 2;


    if (!texture.loadFromFile("../../textures/_Fall.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["FallKnight"] = texture;
    numOfFramesTextures["FallKnight"] = 3;


    if (!texture.loadFromFile("../../textures/_SlideTransitionStart.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["SlideTransitionStartKnight"] = texture;
    numOfFramesTextures["SlideTransitionStartKnight"] = 2;


    if (!texture.loadFromFile("../../textures/_Slide.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["SlideKnight"] = texture;
    numOfFramesTextures["SlideKnight"] = 2;


    if (!texture.loadFromFile("../../textures/_SlideTransitionEnd.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["SlideTransitionEndKnight"] = texture;
    numOfFramesTextures["SlideTransitionEndKnight"] = 2;


    if (!texture.loadFromFile("../../textures/_Hit.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["HitKnight"] = texture;
    numOfFramesTextures["HitKnight"] = 1;


    //HellHound:


    if (!texture.loadFromFile("../../textures/hell-hound-idle.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["HellHoundIdle"] = texture;
    numOfFramesTextures["HellHoundIdle"] = 11;


    if (!texture.loadFromFile("../../textures/hell-hound-jump.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["HellHoundJump"] = texture;
    numOfFramesTextures["HellHoundJump"] = 6;


    if (!texture.loadFromFile("../../textures/hell-hound-run.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["HellHoundRun"] = texture;
    numOfFramesTextures["HellHoundRun"] = 5;


    if (!texture.loadFromFile("../../textures/hell-hound-walk.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["HellHoundWalk"] = texture;
    numOfFramesTextures["HellHoundWalk"] = 12;


    if (!texture.loadFromFile("../../textures/hell-hound-hit.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["HellHoundHit"] = texture;
    numOfFramesTextures["HellHoundHit"] = 1;


    //Pozadí:

    if (!texture.loadFromFile("../../textures/backGroundTexture/clouds.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["CloudsBackground"] = texture;


    if (!texture.loadFromFile("../../textures/backGroundTexture/town.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["TownBackground"] = texture;


    if (!texture.loadFromFile("../../textures/backGroundTexture/tiles.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["TilesBackground"] = texture;


    if (!texture.loadFromFile("../../textures/hpBar.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["hpBar"] = texture;

    if (!texture.loadFromFile("../../textures/hpLine.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["hpLine"] = texture;

    if (!texture.loadFromFile("../../textures/damageBAR.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["hpDamageBar"] = texture;

    if (!texture.loadFromFile("../../textures/Gore/blood-3.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["bloodSplash0"] = texture;
    numOfFramesTextures["bloodSplash0"] = 5;

    if (!texture.loadFromFile("../../textures/Gore/blood.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["bloodSplash1"] = texture;
    numOfFramesTextures["bloodSplash1"] = 8;

    if (!texture.loadFromFile("../../textures/Gore/blood-2.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["bloodSplash2"] = texture;
    numOfFramesTextures["bloodSplash2"] = 6;

    if (!texture.loadFromFile("../../textures/Gore/blood-small.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["bloodSplash3"] = texture;
    numOfFramesTextures["bloodSplash3"] = 5;


    if (!texture.loadFromFile("../../textures/Gore/HellHoundGore/goreHellHound1.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["GoreHellHound1"] = texture;
    numOfFramesTextures["GoreHellHound1"] = 1;

    if (!texture.loadFromFile("../../textures/Gore/HellHoundGore/goreHellHound2.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["GoreHellHound2"] = texture;
    numOfFramesTextures["GoreHellHound2"] = 1;

    if (!texture.loadFromFile("../../textures/Gore/HellHoundGore/goreHellHound3.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["GoreHellHound3"] = texture;
    numOfFramesTextures["GoreHellHound3"] = 1;

    if (!texture.loadFromFile("../../textures/Gore/HellHoundGore/goreHellHound4.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["GoreHellHound4"] = texture;
    numOfFramesTextures["GoreHellHound4"] = 1;

    if (!texture.loadFromFile("../../textures/Gore/HellHoundGore/goreHellHound5.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["GoreHellHound5"] = texture;
    numOfFramesTextures["GoreHellHound5"] = 1;




    if (!texture.loadFromFile("../../textures/forntGround/Plarform3.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["Plarform3"] = texture;
    numOfFramesTextures["Plarform3"] = 1;

    if (!texture.loadFromFile("../../textures/forntGround/Platform2.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["Plarform2"] = texture;
    numOfFramesTextures["Plarform2"] = 1;

    if (!texture.loadFromFile("../../textures/forntGround/platform1.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["Plarform1"] = texture;
    numOfFramesTextures["Plarform1"] = 1;

    if (!texture.loadFromFile("../../textures/hitbox.png"))  {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["hitbox"] = texture;
    numOfFramesTextures["hitbox"] = 1;
}


void TextureManager::setTexture(std::string nameOfTexture, sf::Sprite *spriteToInsertTo) {
    spriteToInsertTo->setTexture(textures.at(nameOfTexture));
}

sf::Texture TextureManager::getTextureFromEntity(std::string nameOfTexture) {
    return  textures.at(nameOfTexture);
}
