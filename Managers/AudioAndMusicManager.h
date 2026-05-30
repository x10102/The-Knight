//
// Created by Oliver Šmítek on 30.05.2026.
//

#ifndef AUDIOANDMUSICMANAGER_H
#define AUDIOANDMUSICMANAGER_H

#include <map>

#include "iostream"

#include "SpriteManager.h"
#include "SFML/Audio/Music.hpp"


class AudioAndMusicManager {

  std::map<std::string, sf::Music*> musicMap;


};



#endif //AUDIOANDMUSICMANAGER_H
