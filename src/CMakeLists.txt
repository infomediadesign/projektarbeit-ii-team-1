cmake_minimum_required(VERSION 3.11)

include(../cmake/raylib.cmake)

# nlohmann
include(../cmake/nlohmann_json.cmake)

project(game VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cpp Scenes/Scenes.cpp Scenes/Scenes.h Scenes/MenuScenes.cpp Scenes/MenuScenes.h Scenes/LevelScene.cpp Scenes/LevelScene.h Scenes/PauseScene.cpp Scenes/PauseScene.h Scenes/InventoryScene.cpp Scenes/InventoryScene.h Scenes/SkillTreeScene.cpp Scenes/SkillTreeScene.h Scenes/MainMenuScene.cpp Scenes/MainMenuScene.h Scenes/BattleScene.cpp Scenes/BattleScene.h Scenes/GameOverScene.cpp Scenes/GameOverScene.h "Actors/Prop.cpp" "Actors/Actor.h" "Actors/Actor.cpp" "Actors/Player.h" "Actors/Player.cpp" "Actors/Enemies/Enemy.h" "Actors/Enemies/Enemy.cpp" "Actors/enums.h" "Systems/DialogueManager.h" "Systems/DialogueManager.cpp" Actors/Enemies/GangsterFemale.cpp Actors/Enemies/GangsterFemale.h Actors/Enemies/GangsterMale.cpp Actors/Enemies/GangsterMale.h Actors/Enemies/Bouncer1.cpp Actors/Enemies/Bouncer1.h Actors/Enemies/Bouncer2.cpp Actors/Enemies/Bouncer2.h Systems/SceneManager.cpp Systems/SceneManager.h Scenes/Button.h Scenes/Button.cpp)

# Add config.h.in file
configure_file(config.h.in config.h)
target_include_directories(${PROJECT_NAME} PUBLIC
        "${PROJECT_BINARY_DIR}"
        )

#  Link to Raylib
#target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} raylib nlohmann_json::nlohmann_json)

# Copy assets to assets path
add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_LIST_DIR}/../cmake/copy-assets.cmake"
        )
add_dependencies(${PROJECT_NAME} copy_assets)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif ()

# CPack instructions
# call e.g. cpack -G ZIP -C Debug to create a binary distribution
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "${PROJECT_NAME}_Bundle")
install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/assets" DESTINATION "${PROJECT_NAME}_Bundle")