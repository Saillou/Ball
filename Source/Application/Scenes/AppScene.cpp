#include "AppScene.hpp"

#include <algorithm>
#include <ctime>
#include <random>

// -- Scene instance --
AppScene::AppScene() :
    BaseScene(),
    m_decors(0.25f)
{
    // Camera
    m_camera.position    = glm::vec3(0.0f, 2.0f, 0.0f);
    m_camera.direction   = glm::vec3(0.0f, 0.0, 0.0f);
    m_camera.fieldOfView = 45.0f;

    // - Generate batches
    // Random engine
    std::default_random_engine gen;
    std::uniform_real_distribution<float> dstr(-50.0f, +50.0f);

    // Draw decors
    m_decors.models.resize(2000);
    std::generate(m_decors.models.begin(), m_decors.models.end(), [&]() -> glm::mat4 {
        return 
            glm::scale(
                glm::translate(
                    glm::mat4(1.0f), 
                    glm::vec3(dstr(gen), dstr(gen), dstr(gen))
                ),
                0.05f * std::abs(dstr(gen)) * glm::vec3(1.0f, 1.0f, 1.0f)
            );
    });

    // Create batch
    m_decors.create();
}

void AppScene::resize(int width, int height) {
    // Update scene internal
    BaseScene::resize(width, height);

    // Camera
    _update_camera();
}

void AppScene::draw() {
    // Camera
    _update_camera();

    // Update particles
    if (m_anime_brownian) {
        for (size_t i = 0; i < m_decors.models.size(); i++)
        {
            glm::vec4& model_pos = m_decors.models[i][3];

            model_pos[0] = model_pos[0] * 0.95f + (0.5f) * 0.05f;
            model_pos[1] = model_pos[1] * 0.95f;
            model_pos[2] = model_pos[2] * 0.95f + (0.5f) * 0.05f;
        }
    }
    m_decors.update();

    // Draw universe
    m_decors.draw(m_camera, m_lights);
}

void AppScene::_update_camera() {
    float aspect = (float)m_width / m_height;

    m_camera.lookAt(glm::vec3(0, 0, 1));
    m_camera.usePerspective(aspect);
}
