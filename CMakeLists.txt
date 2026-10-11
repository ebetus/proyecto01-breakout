cmake_minimum_required(VERSION 3.16)
project(proyecto01-breakout LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Detección de SDL3
find_package(SDL3 QUIET)
if(NOT SDL3_FOUND)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED IMPORTED_TARGET sdl3)
set(SDL3_TARGET PkgConfig::SDL3)
else()
set(SDL3_TARGET SDL3::SDL3)
endif()



add_executable(${PROJECT_NAME}
src/main.cpp
src/Engine/Component.cpp
src/Engine/GameObject.cpp
src/Engine/RectRenderComponent.cpp
src/Engine/Scene.cpp
src/Engine/SceneManager.cpp
src/Engine/TransformComponent.cpp
src/Game/BallComponent.cpp
src/Game/GameOverScene.cpp
src/Game/GameScene.cpp
src/Game/PauseScene.cpp
src/Game/PlayerControllerComponent.cpp
src/Game/TitleScene.cpp
src/Game/DesactivatorComponent.cpp
src/Game/LifeRenderComponent.cpp
src/Game/WinScene.cpp
src/Math/Vector2.cpp
src/Physics/ColliderComponent.cpp
src/Physics/CollisionManager.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
include
src
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL3_TARGET})
