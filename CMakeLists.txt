cmake_minimum_required(VERSION 3.8)
project(Game)

set(CMAKE_CXX_STANDARD 11)

configure_file (
        "${PROJECT_SOURCE_DIR}/config.hpp.in"
        "${PROJECT_SOURCE_DIR}/config.hpp"
    )
include_directories(${PROJECT_SOURCE_DIR})

# Game
set (GAME_DIR ${PROJECT_SOURCE_DIR}/src/Game)
include_directories(${GAME_DIR}/include)
#file (GLOB GAME_CPPS ${GAME_DIR}/*.cpp)
set (GAME_CPPS
        ${GAME_DIR}/Game.cpp
        ${GAME_DIR}/GameObject.cpp
        ${GAME_DIR}/Loader.cpp
        ${GAME_DIR}/Logger.cpp
        ${GAME_DIR}/Main.cpp
        ${GAME_DIR}/MovementScript.cpp
        ${GAME_DIR}/ResourceManager.cpp
        ${GAME_DIR}/SFMLGame.cpp
        ${GAME_DIR}/Transform.cpp
        ${GAME_DIR}/WeakPtrStorage.cpp
    )

## Physics
set (PHYSICS_DIR ${PROJECT_SOURCE_DIR}/src/Physics)
include_directories(${PHYSICS_DIR}/include)
#file (GLOB PHYSICS_CPPS "${PHYSICS_DIR}/*.cpp")
set (PHYSICS_CPPS
        ${PHYSICS_DIR}/Box2DWorld.cpp
        ${PHYSICS_DIR}/BoxCollider.cpp
        ${PHYSICS_DIR}/PhysicsBody.cpp
        ${PHYSICS_DIR}/PhysicsSubsystem.cpp
    )

# Rendering
set (RENDERING_DIR ${PROJECT_SOURCE_DIR}/src/Rendering)
include_directories(${RENDERING_DIR}/include)
#file (GLOB RENDERING_CPPS ${RENDERING_DIR}/*.cpp)
set (RENDERING_CPPS
        ${RENDERING_DIR}/Camera.cpp
        ${RENDERING_DIR}/CircleRenderer.cpp
        ${RENDERING_DIR}/Renderer.cpp
        ${RENDERING_DIR}/SpriteRenderer.cpp
    )

## GUI
set (GUI_DIR ${PROJECT_SOURCE_DIR}/src/GUI)
include_directories(${GUI_DIR}/include)
#file (GLOB GUI_CPPS ${GUI_DIR}/*.cpp)
set (GUI_CPPS
        ${GUI_DIR}/Drawable.cpp
        ${GUI_DIR}/Label.cpp
        ${GUI_DIR}/LabelElement.cpp
        src/GUI/ScrollPanel.cpp
        src/GUI/InteractableGraphics.cpp
        src/GUI/include/ScrollPanelElement.hpp src/GUI/ScrollPanelElement.cpp
        src/GUI/include/IMouseListener.hpp src/GUI/GUIElement.cpp
        src/GUI/include/MouseListener.hpp src/GUI/MouseListener.cpp
        src/GUI/BoxLayout.cpp src/GUI/include/BoxLayout.hpp
        src/GUI/include/Image.hpp src/GUI/Image.cpp)

#Box2D
set (BOX2D_DIR ${PROJECT_SOURCE_DIR}/src/Box2D_v2.3.0/Box2D)
include_directories(${BOX2D_DIR})

add_definitions(-DENABLE_LOG)
#add_definitions(-DDEBUG_PRINT)
add_executable(Game ${GAME_CPPS} ${PHYSICS_CPPS} ${RENDERING_CPPS} ${GUI_CPPS})
target_link_libraries(Game ${BOX2D_DIR}/Box2D/libBox2D.a)
target_link_libraries(Game -lsfml-system -lsfml-graphics -lsfml-window)

