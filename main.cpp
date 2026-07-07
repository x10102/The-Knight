#include "Game/GameManager.h"
#include "Game/Managers/EntityManager.h"
#include "Game/Managers/SpawnManager.h"

#include "Game/Managers/BackGroundManager.h"
#include "Game/Managers/CameraManager.h"
#include "Game/Managers/DrawManager.h"
#include "Game/Managers/EnvironmenAndPhysicsManager.h"


int main() {

    EnvironmenAndPhysicsManager &environmenAndPhysicsManager = EnvironmenAndPhysicsManager::getInstance();


    SpawnManager &spawnManager = SpawnManager::getInstance();

    EntityManager &entityManager = EntityManager::getInstance();

    DrawManager &drawManager = DrawManager::getInstance();

    spawnManager.spawnPlayer({835,520}, {0, 0});

    spawnManager.spawnHellHound({935,520}, {0, 0});

    environmenAndPhysicsManager.platformGeneretion({600,770}, "--");

    sf::RenderWindow window(sf::VideoMode(1600, 1200), "The Knight");


    while (window.isOpen()) {
        if (GameManager::getInstance().tickClock.getElapsedTime().asMilliseconds() >= GameManager::getInstance().timeInFrames) {
            GameManager::getInstance().addToTicksMade();
            GameManager::getInstance().resetColockForTicks();
            sf::Event event;

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();

            entityManager.update(window, environmenAndPhysicsManager);
            BackGroundManager::getInstance().logicOfBackground(window);
            CameraManager::getInstance().CameraUpdate(window);
            drawManager.getInstance().drawGame(window, environmenAndPhysicsManager);

            window.display();
        }
    }

    return 0;
}

