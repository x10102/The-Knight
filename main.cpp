#include "Managers/EntityManager.h"
#include "Managers/SpawnManager.h"

#include "Managers/BackGroundManager.h"
#include "Managers/CameraManager.h"
#include "Managers/DrawManager.h"
#include "Managers/EnvironmenAndPhysicsManager.h"


int main() {

    EnvironmenAndPhysicsManager &environmenAndPhysicsManager = EnvironmenAndPhysicsManager::getInstance();


    SpawnManager &spawnManager = SpawnManager::getInstance();

    EntityManager &entityManager = EntityManager::getInstance();

    DrawManager &drawManager = DrawManager::getInstance();

    spawnManager.spawnPlayer({835,520}, {0, 0});

    spawnManager.spawnHellHound({935,520}, {0, 0});

    environmenAndPhysicsManager.platformGeneretion({600,770}, "--");

    sf::RenderWindow window(sf::VideoMode(1600, 1200), "The Knight");

    window.setFramerateLimit(60);

    while (window.isOpen()) {

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

    return 0;
}
