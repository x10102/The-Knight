//
// Created by Oliver Šmítek on 30.05.2026.
//

#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <SFML/Graphics/RenderWindow.hpp>

class CameraManager {
  public:

  sf::View view;

  float idkOffSet = 735;
  float viewCornerX = 735;
  float viewCornerXsecand = 5000;

  int i = 0;

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
