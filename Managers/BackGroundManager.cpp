//
// Created by Oliver Šmítek on 03.02.2026.
//

#include "BackGroundManager.h"

#include <iostream>
#include <ostream>

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

    positionXOfPlayer = entityManager->getInstance().getPositionOfEntity("Player").x;
    positionYOfPlayer = entityManager->getInstance().getPositionOfEntity("Player").y;


}

void BackGroundManager::drawBackground(sf::RenderWindow& window) {
    sf::Vector2f playerVelocity = entityManager->getInstance().getVelocityOfEntity("Player");
    std::cout << playerVelocity.x << std::endl;

    if (!entityManager->getInstance().getFreezEntity("Player")) {
        positionXOfPlayer += playerVelocity.x;
    }

    if (positionXOfPlayer >= 5500.f) {
        entityManager->getInstance().cornerBoolSetFalsePlayer();
        backgroundCloudsDist = 0.f - 5500.f / 20.f;
        backgroundTownDist = 0.f - 5500.f / 13.f;
        backgroundHouse2ADist = 0.f - 5500.f / 2.f;
        backgroundHouse2BDist = 0.f - 5500.f / 1.8f;
        backgroundHouse1Dist = 0.f - 5500.f;
        floorDist = 0.f - 5500.f;
    }

    else if (positionXOfPlayer >= 0)  {
        entityManager->getInstance().cornerBoolSetTruePlayer();
        backgroundCloudsDist = -positionXOfPlayer / 20.f;
        backgroundTownDist = -positionXOfPlayer / 13.f;
        backgroundHouse2ADist = -positionXOfPlayer / 2.f;
        backgroundHouse2BDist = -positionXOfPlayer / 1.8f;
        backgroundHouse1Dist = -positionXOfPlayer;
        floorDist = -positionXOfPlayer;
    }

    else {
        entityManager->getInstance().cornerBoolSetFalsePlayer();
        backgroundCloudsDist = 0.f;
        backgroundTownDist = 0.f;
        backgroundHouse2ADist = 0.f;
        backgroundHouse2BDist = 0.f;
        backgroundHouse1Dist = 0.f;
        floorDist = 0.f;

    }


    spriteManager->getInstance().drawSprite(&backgroundClouds, backgroundCloudsDist, 0, window);

    spriteManager->getInstance().drawSprite(&backgroundClouds, backgroundCloudsDist + 1152, 0, window);

    spriteManager->getInstance().drawSprite(&backgroundClouds, backgroundCloudsDist + 2048, 0, window);





    spriteManager->getInstance().drawSprite(&backgroundTown, backgroundTownDist, 0, window);
    spriteManager->getInstance().drawSprite(&backgroundTown, backgroundTownDist + 1152,0, window);
    spriteManager->getInstance().drawSprite(&backgroundTown, backgroundTownDist + 2048, 0, window);


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

    spriteManager->getInstance().drawSprite(&backgroundHouse2,  backgroundHouse2ADist + 720, 352, window);

    spriteManager->getInstance().drawSprite(&backgroundHouse2,  backgroundHouse2BDist + 1800, 352, window);

    spriteManager->getInstance().drawSprite(&backgroundHouse1,  backgroundHouse1Dist, 352, window);

}
