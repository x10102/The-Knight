cmake_minimum_required(VERSION 3.29)
project(untitled46)

# Použijeme C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Nepoužívat rozšíření kompilátoru

# Výstupní složka pro spustitelné soubory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Přidání SFML přes FetchContent
include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)
FetchContent_MakeAvailable(SFML)

# Přidání spustitelného souboru
add_executable(untitled46 main.cpp
        Managers/TextureManager.h
        Managers/TextureManager.cpp
        Managers/EntityManager.cpp
        Managers/EntityManager.h
        Managers/SpriteManager.cpp
        Managers/SpriteManager.h
        Insertors/InsertEntity.cpp
        Insertors/InsertEntity.h
        Entities/Entity.h
        Entities/Entity.cpp
        Entities/Player/Player.h
        Entities/Player/Player.cpp
        Entities/particle/BloodSplash.cpp
        Entities/particle/BloodSplash.h
        Managers/SpawnManager.h
        Managers/SpawnManager.cpp
        Managers/EnvironmenAndPhysicsManager.h
        Managers/EnvironmenAndPhysicsManager.cpp
        Managers/BackGroundManager.cpp
        Managers/BackGroundManager.h
        Entities/Enemies/HellHound.cpp
        Entities/Enemies/HellHound.h
        UIdirectory/UIManager.cpp
        UIdirectory/UIManager.h
        UIdirectory/UI/PlayerUIHP.cpp
        UIdirectory/UI/PlayerUIHP.h
        Managers/SpawnManager.h
        Managers/SpawnManager.cpp
        Managers/ParticalManager.cpp
        Managers/ParticalManager.h
        Entities/particle/HellHoundGore/HellHoundGore.cpp
        Entities/particle/HellHoundGore/HellHoundGore.h
        Entities/Envirament/platform.cpp
        Entities/Envirament/platform.h
        Managers/DrawManager.cpp
        Managers/DrawManager.h
        Entities/Envirament/PlatformEag.cpp
        Entities/Envirament/PlatformEag.cpp
        Managers/AudioAndMusicManager.cpp
        Managers/AudioAndMusicManager.h
        Managers/CameraManager.cpp
        Managers/CameraManager.h
        UIdirectory/UI/PlayerUIStamina.cpp
        UIdirectory/UI/PlayerUIStamina.h
)

# Linkování SFML
target_link_libraries(untitled46 PRIVATE sfml-graphics sfml-window sfml-system)
