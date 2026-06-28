//
// Created by Oliver Šmítek on 30.05.2026.
//

#ifndef AUDIOANDMUSICMANAGER_H
#define AUDIOANDMUSICMANAGER_H

#include <map>

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>


class AudioAndMusicManager {
  AudioAndMusicManager();

  static AudioAndMusicManager& getInstance(){
    static AudioAndMusicManager theInstance;
    return theInstance;
  }

  std::map<std::string, sf::Music*> musicMap;
  std::map<std::string, sf::Sound*> soundMap;

};



#endif //AUDIOANDMUSICMANAGER_H
