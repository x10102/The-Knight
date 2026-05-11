#include <iostream>

#include "Entities/Player/Player.h"
#include "Managers/EntityManager.h"
#include "Managers/SpawnManager.h"

#include "Insertors/InsertEntity.h"
#include "Managers/BackGroundManager.h"
#include "Managers/EnvironmenAndPhysicsManager.h"
#include "SFML/Graphics.hpp"


int main() {
    EnvironmenAndPhysicsManager environmenAndPhysicsManager;

    SpawnManager &spawnManager = SpawnManager::getInstance();

    EntityManager &entityManager = EntityManager::getInstance();



    spawnManager.spawnPlayer({0,700}, {0, 0});

    environmenAndPhysicsManager.platformGeneretion({2000,720}, "--");



    BackGroundManager backGroundManager;

    sf::RenderWindow window(sf::VideoMode(1600, 1200), "The Knight");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        std::cout << "start"<<std::endl;

        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        backGroundManager.drawBackground(window);
        entityManager.update(window, environmenAndPhysicsManager);
        window.display();

        std::cout << "end"<<std::endl;

    }

    return 0;
}
