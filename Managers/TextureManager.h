//
// Created by Oliver Šmítek on 16.12.2025.
//

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <unordered_map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "SFML/Graphics/Sprite.hpp"

class TextureManager {

    TextureManager();



public:
    static TextureManager& getInstance(){
        static TextureManager theInstance;
        return theInstance;
    }

    std::unordered_map<std::string, sf::Texture> textures; //obsahuje všechny textury hry
    std::unordered_map<std::string, int> numOfFramesTextures; //obsahuje všechny textury hry

    void setTexture(std::string nameOfTexture, sf::Sprite* spriteToInsertTo);

    sf::Texture getTextureFromEntity(std::string nameOfTexture);
};



#endif //TEXTUREMANAGER_H
