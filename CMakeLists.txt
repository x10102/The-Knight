cmake_minimum_required(VERSION 3.29)
project(untitled46)

# Použijeme C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Nepoužívat rozšíření kompilátoru
set(CMAKE_BUILD_TYPE Debug) # Pridat debug symboly
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
        Game/Managers/TextureManager.h
        Game/Managers/TextureManager.cpp
        Game/Managers/EntityManager.cpp
        Game/Managers/EntityManager.h
        Game/Managers/SpriteManager.cpp
        Game/Managers/SpriteManager.h
        Game/Insertors/InsertEntity.cpp
        Game/Insertors/InsertEntity.h
        Game/Entities/Entity.h
        Game/Entities/Entity.cpp
        Game/Entities/Player/Player.h
        Game/Entities/Player/Player.cpp
        Game/Entities/particle/BloodSplash.cpp
        Game/Entities/particle/BloodSplash.h
        Game/Managers/SpawnManager.h
        Game/Managers/SpawnManager.cpp
        Game/Managers/EnvironmenAndPhysicsManager.h
        Game/Managers/EnvironmenAndPhysicsManager.cpp
        Game/Managers/BackGroundManager.cpp
        Game/Managers/BackGroundManager.h
        Game/Entities/Enemies/EnemyVariants/HellHound.cpp
        Game/Entities/Enemies/EnemyVariants/HellHound.h
        Game/UIdirectory/UIManager.cpp
        Game/UIdirectory/UIManager.h
        Game/UIdirectory/UI/PlayerUIHP.cpp
        Game/UIdirectory/UI/PlayerUIHP.h
        Game/Managers/SpawnManager.h
        Game/Managers/SpawnManager.cpp
        Game/Managers/ParticalManager.cpp
        Game/Managers/ParticalManager.h
        Game/Entities/particle/HellHoundGore/HellHoundGore.cpp
        Game/Entities/particle/HellHoundGore/HellHoundGore.h
        Game/Entities/Envirament/platform.cpp
        Game/Entities/Envirament/platform.h
        Game/Managers/DrawManager.cpp
        Game/Managers/DrawManager.h
        Game/Entities/Envirament/PlatformEag.cpp
        Game/Entities/Envirament/PlatformEag.cpp
        Game/Managers/AudioAndMusicManager.cpp
        Game/Managers/AudioAndMusicManager.h
        Game/Managers/CameraManager.cpp
        Game/Managers/CameraManager.h
        Game/UIdirectory/UI/PlayerUIStamina.cpp
        Game/UIdirectory/UI/PlayerUIStamina.h
        Game/Entities/souls/Soul.cpp
        Game/Entities/souls/Soul.h
        Game/Entities/souls/SoulsVariants/NarunSoul.cpp
        Game/Entities/souls/SoulsVariants/NarunSoul.h
        Game/Entities/Enemies/Enemy.cpp
        Game/Entities/Enemies/Enemy.h
        Game/GameManager.h
        Game/GameManager.cpp

)

# target_compile_options(untitled46 PRIVATE -fsanitize=address)
# target_link_options(untitled46 PRIVATE -fsanitize=address)

# Linkování SFML
target_link_libraries(untitled46 PRIVATE sfml-graphics sfml-window sfml-system)
