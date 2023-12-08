#include "AppScene.hpp"

#include <algorithm>
#include <ctime>
#include <random>

// -- Scene instance --
AppScene::AppScene() :
    BaseScene(),
    m_fireBall({
        std::make_unique<Sphere>(0.15f), 
        glm::vec3(0, 0, 0),
        { 
            std::make_unique<Box>(glm::vec3(0.05f, 0.05f, 0.05f)) 
        }
    })
{
    // Camera
    m_camera.position    = glm::vec3(0.0f, -10.0f, 0.0f);
    m_camera.direction   = glm::vec3(0.0f, 0.0, 0.0f);
    m_camera.fieldOfView = 45.0f;

    // - Generate batch parameters
    const size_t n_particles = 2'500;

    // Random engine
    std::default_random_engine gen;
    std::uniform_real_distribution<float> dstr_pi(-glm::pi<float>(), +glm::pi<float>());
    std::uniform_real_distribution<float> dstr_one(0.0f, 1.0f);
    std::uniform_real_distribution<float> dstr_half(-0.5f, +0.5f);

    // Define particles
    m_fireBall.particles.models.resize(n_particles);
    m_fireBall.particles.speeds.resize(n_particles);
    m_fireBall.particles.colors.resize(n_particles);

    std::generate(m_fireBall.particles.models.begin(), m_fireBall.particles.models.end(), [&, particules_id = 0]() mutable -> glm::mat4
    {
        // Create a grid (centered in 0)
        const int SIZE = (int)sqrt(n_particles);
        int x = particules_id % SIZE - SIZE / 2;
        int y = particules_id / SIZE - SIZE / 2;
        particules_id++;

        return glm::translate(
            glm::mat4(1.0f), 
            glm::vec3(x * 0.05f, 0.0f, y * 0.05f)
        );
    });

    std::generate(m_fireBall.particles.speeds.begin(), m_fireBall.particles.speeds.end(), [&]() -> glm::vec3
    {
        return glm::vec3(0.0f, 0.0f, 0.0f);
    });
    
    std::generate(m_fireBall.particles.colors.begin(), m_fireBall.particles.colors.end(), [&]() -> glm::vec4
    {
        return glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    });

    // Create batch
    m_fireBall.particles.object->shape()->createBatch(
        m_fireBall.particles.colors,
        m_fireBall.particles.models
    );

    // Cook
    m_fireBall.object->addRecipe(Cookable::CookType::Solid, glm::vec4(1.0f, 0.7f, 0.3f, 1.0f));
    m_fireBall.particles.object->addRecipe(Cookable::CookType::Batch);
}

void AppScene::draw() {
    static float t = 0.0f;
    const float dt = 0.016f;

    // Ball
    //m_fireBall.object->draw(m_camera, m_fireBall.pos, {}, m_lights);
    
    // Particles
    {
        // Move
        for (size_t i = 0; i < m_fireBall.particles.models.size(); i++)
        {
            glm::vec3& speed = m_fireBall.particles.speeds[i];
            glm::mat4& model = m_fireBall.particles.models[i];

            model = glm::translate(model, m_fireBall.pos + dt * speed);
        }

        // Update
        m_fireBall.particles.object->shape()->updateBatch(
            m_fireBall.particles.colors,
            m_fireBall.particles.models
        );

        // Draw
        m_fireBall.particles.object->drawBatch((int)m_fireBall.particles.models.size(), m_camera);
    }

    // Update
    t += dt;
}
