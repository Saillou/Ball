#include "LearnScene.hpp"

#include <iostream>

// -- Scene instance --
LearnScene::LearnScene() :
    BaseScene()
{
    // Camera
    m_camera.position    = glm::vec3(0.0f, -10.0f, 0.0f);
    m_camera.direction   = glm::vec3(0.0f, 0.0, 0.0f);
    m_camera.fieldOfView = 45.0f;

    // Lights
    m_lights = {  };

    // Objects

}

void LearnScene::draw() {
    BaseScene::clear();
}

void LearnScene::_onResize() {
    // . if you have framebuffer it may be the correct place to resize these.
}
