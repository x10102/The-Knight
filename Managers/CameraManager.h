//
// Created by Oliver Šmítek on 30.05.2026.
//

#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "SFML/Graphics/RenderWindow.hpp"

class CameraManager {

  sf::View view;

  CameraManager();


  public:
    static CameraManager& getInstance(){
      static CameraManager theInstance;
      return theInstance;
    }

    public:
      void CameraUpdate(sf::RenderWindow& window);

};



#endif //CAMERAMANAGER_H
