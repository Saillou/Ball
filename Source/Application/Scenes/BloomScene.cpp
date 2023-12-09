#include "BloomScene.hpp"

#include <algorithm>
#include <ctime>
#include <random>
#include <array>

// -- Scene instance --
BloomScene::BloomScene() :
    BaseScene()
{
    // Camera
    m_camera.position    = glm::vec3(0.0f, -10.0f, 0.0f);
    m_camera.direction   = glm::vec3(0.0f, 0.0, 0.0f);
    m_camera.fieldOfView = 45.0f;
}

void BloomScene::draw() {

}
