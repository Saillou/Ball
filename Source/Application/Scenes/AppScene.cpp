#include "AppScene.hpp"

#include <algorithm>
#include <ctime>
#include <random>

// Random engine
static std::default_random_engine gen;

static std::uniform_real_distribution<float> dstr_pi(-glm::pi<float>(), +glm::pi<float>());
static std::uniform_real_distribution<float> dstr_one(0.0f, 1.0f);
static std::uniform_real_distribution<float> dstr_half(-0.5f, +0.5f);

// -- Scene instance --
AppScene::AppScene() :
    BaseScene(),
    m_fireBall({
        std::make_unique<Sphere>(0.15f), 
        glm::vec3(0, 0, 0),
        { 
            size_t(2500),
            std::make_unique<Box>(0.015f * glm::vec3(1.0f, 1.0f, 1.0f))
        }
    })
{
    // Camera
    m_camera.position    = glm::vec3(0.0f, -10.0f, 0.0f);
    m_camera.direction   = glm::vec3(0.0f, 0.0, 0.0f);
    m_camera.fieldOfView = 45.0f;

    // - Generate batch parameters
    const glm::vec3 color(1.0f, 0.7f, 0.3f);

    // Define particles
    m_fireBall.particles.models.resize(m_fireBall.particles.amount);
    m_fireBall.particles.speeds.resize(m_fireBall.particles.amount);
    m_fireBall.particles.colors.resize(m_fireBall.particles.amount);

    std::generate(m_fireBall.particles.models.begin(), m_fireBall.particles.models.end(), [&, particules_id = 0]() mutable -> glm::mat4
    {
        const int SIZE = (int)sqrt(m_fireBall.particles.amount);
        int x = particules_id % SIZE - SIZE / 2;
        int y = particules_id / SIZE - SIZE / 2;
        particules_id++;

        return glm::translate(
            glm::mat4(1.0f), 
            glm::vec3(x * 0.05f, 0.0f, y * 0.05f)
        );
    });

    std::generate(m_fireBall.particles.colors.begin(), m_fireBall.particles.colors.end(), [&, particules_id = 0]() mutable -> glm::vec4
    {
        particules_id++;
        float ratio = particules_id / float(m_fireBall.particles.amount);

        return glm::min(glm::vec4(1.5f * ratio * color, 0.0f) + glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    });

    std::generate(m_fireBall.particles.speeds.begin(), m_fireBall.particles.speeds.end(), [&]() -> glm::vec4
    {
        return glm::vec4(dstr_half(gen) / 2.0f, 0.0f, dstr_one(gen), 1.0f - dstr_one(gen) / 10.0f - 1e-2f);
    });

    // Create batch
    m_fireBall.particles.object->shape()->createBatch(
        m_fireBall.particles.colors,
        m_fireBall.particles.models
    );

    // Cook
    m_fireBall.object->addRecipe(Cookable::CookType::Solid, glm::vec4(color, 1.0f));
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
        for (int particules_id = 0; particules_id < m_fireBall.particles.amount; particules_id++)
        {
            glm::vec4& speed = m_fireBall.particles.speeds[particules_id];
            glm::mat4& model = m_fireBall.particles.models[particules_id];

            if (model[0][0] < 1e-2f || model[1][1] < 1e-2f || model[2][2] < 1e-2f || redraw)
            {
                const int SIZE = (int)sqrt(m_fireBall.particles.amount);
                int x = particules_id % SIZE - SIZE / 2;
                int y = particules_id / SIZE - SIZE / 2;

                model = glm::translate(
                    glm::mat4(1.0f),
                    glm::vec3(x * 0.05f, 0.0f, y * 0.05f)
                );

                speed = glm::vec4(dstr_half(gen) / 2.0f, 0.0f, dstr_one(gen), 1.0f - dstr_one(gen) / 10.0f - 1e-2f);
            }
            else {
                model = glm::scale(
                    glm::translate(
                        model, 
                        m_fireBall.pos + dt * glm::vec3(speed)), speed.a * glm::vec3(1, 1, 1)
                );
            }
        }

        // Update
        m_fireBall.particles.object->shape()->updateBatch(
            m_fireBall.particles.colors,
            m_fireBall.particles.models
        );

        // Draw
        m_fireBall.particles.object->drawBatch(m_fireBall.particles.amount, m_camera);
    }

    // Update
    t += dt;
    redraw = false;
}
