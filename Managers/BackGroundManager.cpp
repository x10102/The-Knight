//
// Created by Oliver Šmítek on 03.02.2026.
//

#include "BackGroundManager.h"

#include "CameraManager.h"

BackGroundManager::BackGroundManager(){

    spriteManager->getInstance().setTextureToBackGroundSprite("CloudsBackground",&backgroundClouds);
    backgroundClouds.scale(scaleOfMapBackGround);
    spriteManager->getInstance().setTextureToBackGroundSprite("TownBackground",&backgroundTown);
    backgroundTown.scale(scaleOfMapBackGround);


    spriteManager->getInstance().setTextureToBackGroundSprite("TilesBackground",&backgroundHouse1);

    backgroundHouse1.scale(scaleOfMap);


    sf::IntRect rect =  backgroundHouse1.getTextureRect();
    backgroundHouse1.setTextureRect({450,rect.top,320,rect.height});


    spriteManager->getInstance().setTextureToBackGroundSprite("TilesBackground",&backgroundHouse2);

    backgroundHouse2.scale(scaleOfMap);


    sf::IntRect rect2 =  backgroundHouse2.getTextureRect();
    backgroundHouse2.setTextureRect({780,rect2.top,330,rect2.height});

    spriteManager->getInstance().setTextureToBackGroundSprite("TilesBackground",&floor);
    floor.setTextureRect({175,50,40,100});

    floor.scale(scaleOfMap);

    spriteManager->getInstance().setTextureToBackGroundSprite("TilesBackground",&floor2);
    floor2.scale(scaleOfMap);
    floor2.setTextureRect({31,50,17,30});


    backGroundFull = (735 / 1.08f) - 735;
    backGround = (735 / 1.1f) - 735;
    midGround = (735 / 1.5f) - 735;
}

void BackGroundManager::logicOfBackground(sf::RenderWindow& window) {

    positionXOfPlayer = entityManager->getInstance().getPositionOfEntity("Player").x;
    float posOfPlayerX = EntityManager::getInstance().uMOfEntitys.at("Player")->position.x - window.getSize().x / 2;

    if (posOfPlayerX > CameraManager::getInstance().viewCornerX - CameraManager::getInstance().idkOffSet  && posOfPlayerX < CameraManager::getInstance().viewCornerXsecand- CameraManager::getInstance().idkOffSet) {
        backGroundFull = (positionXOfPlayer / 1.08f) - (float)window.getSize().x/2;
        backGround = (positionXOfPlayer / 1.1f) - (float)window.getSize().x/2;
        midGround = (positionXOfPlayer / 1.5f) - (float)window.getSize().x/2;
    }

}

void BackGroundManager::drawBackground(sf::RenderWindow &window) {


    spriteManager->getInstance().drawSprite(&backgroundClouds, backGroundFull, 0, window);

    spriteManager->getInstance().drawSprite(&backgroundClouds, backGroundFull + 1152, 0, window);

    spriteManager->getInstance().drawSprite(&backgroundClouds, backGroundFull + 2048, 0, window);


    spriteManager->getInstance().drawSprite(&backgroundTown, backGround, 0, window);
    spriteManager->getInstance().drawSprite(&backgroundTown, backGround + 1152,0, window);
    spriteManager->getInstance().drawSprite(&backgroundTown, backGround + 2048, 0, window);


    for (int i = 0; i < 400; i++) {
        sf::IntRect rect3 =  floor.getTextureRect();
        if (crackedBrickIsPlased) {
            xOfFloor = rect3.width * i* 2;
            crackedBrickIsPlased = false;
        }
        else {
            xOfFloor = rect3.width * i;
        }

        if (!(i % 12 == 0) && !(i % 15 == 0) && !(i % 20 == 0)) {
            spriteManager->getInstance().drawSprite(&floor2, floorDist + xOfFloor, 757.5, window);
        }
        else {
            spriteManager->getInstance().drawSprite(&floor,floorDist + xOfFloor, 757.5, window);
            crackedBrickIsPlased = true;
        }
    }

    spriteManager->getInstance().drawSprite(&backgroundHouse2,  midGround + 720, 352, window);

    spriteManager->getInstance().drawSprite(&backgroundHouse2,  midGround + 1800, 352, window);

    spriteManager->getInstance().drawSprite(&backgroundHouse1,  frontGround, 352, window);

}
