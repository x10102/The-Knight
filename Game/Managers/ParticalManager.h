//
// Created by Oliver Šmítek on 14.04.2026.
//

#ifndef PARTICALMANAGER_H
#define PARTICALMANAGER_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../common.hpp"


class ParticalManager {

    ParticalManager() {};

public:

    static ParticalManager& getInstance(){
        static ParticalManager theInstance;
        return theInstance;
    }


    void spawnBloodSplash(sf::Vector2f spawnPos, Direction direction, bool kill);
    void spawnHellHoundGore(sf::Vector2f spawnPos, sf::Vector2f spanwVel, Direction direction, std::string nameOfTexture);


};

#endif //PARTICALMANAGER_H
