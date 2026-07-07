//
// Created by Oliver Šmítek on 25.11.2025.
//

#include "SpriteManager.h"

#include "../GameManager.h"


void SpriteManager::drawSprite(sf::Sprite *sprite, float x, float y, sf::RenderWindow& window) {
    sprite->setPosition(x,y);
    window.draw(*sprite);
}

void SpriteManager::setTextureToSprite(sf::String nameOfTexture,sf::Sprite *sprite) {

    const sf::Texture* current = sprite->getTexture();
    const sf::Texture* wanted  = &textureManager->getInstance().textures.at(nameOfTexture);

    if (current != wanted) {
        textureManager->getInstance().setTexture(nameOfTexture, sprite);
        sf::IntRect rect =  sprite->getTextureRect();
        int sizeOftexture = sprite->getTexture()->getSize().x;
        int oneFrame = sizeOftexture / textureManager->getInstance().numOfFramesTextures.at(nameOfTexture);
        sprite->setTextureRect({0,rect.top,oneFrame,rect.height});
    }
}

void SpriteManager::setTextureToBackGroundSprite(std::string nameOfTexture, sf::Sprite *sprite) {
    textureManager->getInstance().setTexture(nameOfTexture, sprite);
}


void SpriteManager::switchSides(std::string direction, sf::Sprite *sprite) {
    sf::Vector2f scale = sprite->getScale();

    if (direction == "left")
        sprite->setScale(-std::abs(scale.x), scale.y);
    else if (direction == "right")
        sprite->setScale(std::abs(scale.x), scale.y);
}


void SpriteManager::transfomration(sf::Sprite *sprite, sf::Vector2f scale, std::string direction, std::string currentTexture) {
    animationUpdate(sprite, currentTexture);
    sprite->setOrigin(sprite->getLocalBounds().width/2, sprite->getLocalBounds().height);
    sprite->setScale(scale.x, scale.y);
    switchSides(direction, sprite);
}

void SpriteManager::hitBoxTransformation(sf::Sprite *sprite, sf::Vector2f scale, sf::String direction) {
    sprite->setOrigin(sprite->getLocalBounds().width/2, sprite->getLocalBounds().height);
    sprite->setColor(sf::Color(255,255,255,100));
    sprite->setScale(scale.x, scale.y);
    switchSides(direction, sprite);
}

void SpriteManager::shadowTransform(sf::Sprite *sprite, sf::Vector2f scale) {
    sprite->setOrigin(sprite->getLocalBounds().width/2, sprite->getLocalBounds().height);
    sprite->setScale(scale.x, scale.y);
    sprite->setColor(sf::Color(255,255,255,80));
}


void SpriteManager::transformSpriteHPBar(sf::Sprite *sprite, sf::Vector2f scale, int hp) {
    sf::IntRect rect =  sprite->getTextureRect();
    sprite->setScale(scale.x, scale.y);
    int left = std::round((100 - hp)* 0.47) + 3;
    sprite->setTextureRect({left ,rect.top,50,rect.height});

}
void SpriteManager::transformDamageBar(sf::Sprite *sprite, sf::Vector2f scale, int pastHP, int hp, sf::Vector2f *locationDmgBar) {

    sf::IntRect rect = sprite->getTextureRect();
    sprite->setScale(scale.x, scale.y);

    int damage = pastHP - hp;
    int width = damage * 47 / 100;
    locationDmgBar->x = 67 + (hp * 213) / 100;
    sprite->setTextureRect({3, rect.top, width, rect.height});
}


void SpriteManager::markTextureAsHit(sf::Sprite *sprite) {
    sprite->setColor(sf::Color::Red);
}
void SpriteManager::markTextureAsNormal(sf::Sprite *sprite) {
    sprite->setColor(sf::Color(255,255,255,255));
}


void SpriteManager::sinchorizeIntervalBtwAnim() {
}


void SpriteManager::animationUpdate(sf::Sprite *sprite, std::string currentTexture) {
    if (timer.getElapsedTime().asMilliseconds() < intervalBetwenAnimations) return;


    int sizeOftexture = sprite->getTexture()->getSize().x;
    int oneFrame = sizeOftexture / textureManager->getInstance().numOfFramesTextures.at(currentTexture);
    sf::IntRect rect =  sprite->getTextureRect();
    if (rect.left < sizeOftexture - oneFrame) {
        sprite->setTextureRect({rect.left + oneFrame,rect.top,oneFrame,rect.height});
    }
    else {
        sprite->setTextureRect({0,rect.top,oneFrame,rect.height});
    }
}

void SpriteManager::transformCircle(sf::CircleShape *circule) {
    circule->setOrigin(circule->getLocalBounds().width/2, circule->getLocalBounds().height);
    circule->setFillColor(sf::Color(100, 250, 50));
}


void SpriteManager::resetAnimationTimer() {
    if (timer.getElapsedTime().asMilliseconds() >= intervalBetwenAnimations) {
    timer.restart();
    }
}

int SpriteManager::getIndexOfAnimation(sf::Sprite *sprite) {
    int indexOfAnimation =  sprite->getTextureRect().left;
    return indexOfAnimation;
}

int SpriteManager::getMaxIndexOfAnimation(sf::Sprite *sprite) {
    int sizeOftexture = sprite->getTexture()->getSize().x;
    return sizeOftexture;
}
void SpriteManager::rotateSprite(sf::Sprite *sprite, int angle) {
    sprite->setRotation(angle);
}

void SpriteManager::trimStaminaBarToFitInOutLines(sf::Sprite *sprite, bool redy) {

    sf::IntRect rect =  sprite->getTextureRect();
    if (redy) {
        sprite->setTextureRect({12 ,rect.top,19,rect.height});
    }
    else {
        sprite->setTextureRect({30 ,rect.top,19,rect.height});
    }

}
void SpriteManager::sorceBarTransformation(sf::Sprite *sprite, float sorce) {
    sprite->setScale(sorce * 0.385, sprite->getScale().y);
}


void SpriteManager::speedBlurer(sf::Sprite *sprite, sf::RenderWindow &window, float numOfBlure, std::string direction, float velocityX, bool dashIsActiveBool) {

    if (dashIsActiveBool && clockOfBlure.getElapsedTime().asMilliseconds() >= numOfBlure) {
        sf::Sprite spriteToBlur = *sprite;
        spriteToBlur.setPosition(sprite->getPosition().x, sprite->getPosition().y);
        oldPositionsOfPlayer.push_back({spriteToBlur,blureShadow});
        clockOfBlure.restart();
    }

    for (auto &[spriteBlur, alpha] : oldPositionsOfPlayer) {
        spriteBlur.setColor(sf::Color(255, 255, 255, alpha));
        alpha -= 30;
        drawSprite(&spriteBlur,spriteBlur.getPosition().x, spriteBlur.getPosition().y, window );        
    }

    // Remove all shadows with zero or negative alpha
    // Schizo C++20 stuff used here, so:
    // `condition` is a lambda function that can be applied to an element of oldPositions
    // will return true if alpha is <= 0
    // remove_if moves all elements of oldPositions which match the condition to the end of the vector
    // and gives us an iterator to the first one
    // Then we erase everything from toErase to the actual end, meaning all the expired elements
    auto condition = [](auto &x){return x.second <= 0;};
    auto toErase = std::remove_if(oldPositionsOfPlayer.begin(), oldPositionsOfPlayer.end(), condition);
    oldPositionsOfPlayer.erase(toErase, oldPositionsOfPlayer.end());
}


