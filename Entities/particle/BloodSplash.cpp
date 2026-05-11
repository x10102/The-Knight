//
// Created by Oliver Šmítek on 24.04.2026.
//

#include "BloodSplash.h"

#include <iostream>
#include <ostream>


BloodSplash::BloodSplash(sf::Vector2f position, sf::Vector2f velocity, std::string name,std::string direction, bool kill) : Entity(position, velocity, name) {
    float x = 2.4f;
    float y = 2.4f;


    if (kill == true) {
        nameOfTexture = "bloodSplash2";
    }
    else {
        nameOfTexture = "bloodSplash3";
    }

    setTexture(nameOfTexture);

    this->name = name;
    scale = sf::Vector2f(x,y);

    faceingDirection = direction;
}


void BloodSplash::update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) {
    transformationSprite(currentTexture);

    cooldowns_and_unIntraptebulActions();

    movmentSinchronaz();

    drawEntity( window);
}

void BloodSplash::cooldowns_and_unIntraptebulActions() {

    //attack finish animacion
        if (spriteManager->getInstance().getIndexOfAnimation(&sprite) >= spriteManager->getInstance().
        getMaxIndexOfAnimation(&sprite) - (sprite.getTexture()->getSize().x / textureManager->getInstance().numOfFramesTextures[nameOfTexture])){
            killParicul();
            }
}
void BloodSplash::killParicul() {
        entityManager->getInstance().killEntity(name, this);

}

