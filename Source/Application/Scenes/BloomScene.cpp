#include "BloomScene.hpp"

// -- Scene instance --
BloomScene::BloomScene() :
    BaseScene(),
    ball_model(0.25f),
    light_model(0.07f)
{
    // Camera
    m_camera.position    = glm::vec3(0.0f, -10.0f, 0.0f);
    m_camera.direction   = glm::vec3(0.0f, 0.0, 0.0f);
    m_camera.fieldOfView = 45.0f;

    // Lights
    m_lights = { 
        Light(glm::vec3{ 0,0,1 }, glm::vec4{ 1,1,1,1 }),
        Light(glm::vec3{ 1,0,1 }, glm::vec4{ 1,0,0,1 }),
        Light(glm::vec3{ 0,1,1 }, glm::vec4{ 0,1,0,1 }),
        Light(glm::vec3{ 1,1,1 }, glm::vec4{ 0,0,1,1 }),
    };

    // Objects
    ball_model.addRecipe(Cookable::CookType::Solid, glm::vec4(1, 1, 1, 1));
    light_model.addRecipe(Cookable::CookType::Solid);
}

void BloomScene::draw() {
    // Objects
    ball_model.draw(m_camera, {}, {}, m_lights);

    // Lights
    for (auto& light : m_lights) {
        light_model.get(Cookable::CookType::Solid)->set("color", light.color);
        light_model.draw(m_camera, light.position);
    }
}
