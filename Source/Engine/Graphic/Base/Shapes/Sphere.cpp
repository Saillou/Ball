#include "Sphere.hpp"

Sphere::Sphere(float radius)
{
    const unsigned int X_SEGMENTS = 32;
    const unsigned int Y_SEGMENTS = 32;

    for (unsigned int x = 0; x <= X_SEGMENTS; ++x) {
        for (unsigned int y = 0; y <= Y_SEGMENTS; ++y) {
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;

            _addPoint(
                radius * std::cos(xSegment * 2.0f * glm::pi<float>()) * std::sin(ySegment * glm::pi<float>()),
                radius * std::cos(ySegment * 1.0f * glm::pi<float>()),
                radius * std::sin(xSegment * 2.0f * glm::pi<float>()) * std::sin(ySegment * glm::pi<float>()),

                radius * std::cos(xSegment * 2.0f * glm::pi<float>()) * std::sin(ySegment * glm::pi<float>()),
                radius * std::cos(ySegment * 1.0f * glm::pi<float>()),
                radius * std::sin(xSegment * 2.0f * glm::pi<float>()) * std::sin(ySegment * glm::pi<float>())
            );
        }
    }

    for (unsigned int y = 0; y < Y_SEGMENTS; ++y) {
        if (y % 2 == 0) {
            for (unsigned int x = 0; x <= X_SEGMENTS; ++x) {
                m_indices.push_back(y * (X_SEGMENTS + 1) + x);
                m_indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
            }
        }
        else {
            for (int x = X_SEGMENTS; x >= 0; --x) {
                m_indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                m_indices.push_back(y * (X_SEGMENTS + 1) + x);
            }
        }
    }

    // Bind
    _bindArray();
}

void Sphere::draw(const Camera& camera, const glm::vec3& position, const glm::vec3& orientation, const std::vector<Light>& lights) {
    glm::mat4 model(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, orientation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, orientation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, orientation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    for (auto& recipe: m_shaders) {
        // Setup uniforms
        recipe.second->
            use().
            set("Model",        model).
            set("View",         camera.modelview).
            set("Projection",   camera.projection).
            set("CameraPos",    camera.position).
            set("LightPos",     glm::vec3(0, 0, 0)).
            set("LightColor",   glm::vec4(0, 0, 0, 0));

        if(!lights.empty()) {
            recipe.second->
                set("LightPos",   lights[0].position).
                set("LightColor", lights[0].color);
        }

        // Draw
        bind();
        glDrawElements(GL_TRIANGLE_STRIP, (int)m_indices.size(), GL_UNSIGNED_INT, 0);
        unbind();
    }
}

void Sphere::drawBatch(size_t amount, const Camera& camera) {
    for (auto& recipe : m_shaders) {
        // Setup uniforms
        recipe.second->
            use().
            set("View",         camera.modelview).
            set("Projection",   camera.projection).
            set("CameraPos",    camera.position);

        // Draw
        bind();
        glDrawElementsInstanced(GL_TRIANGLE_STRIP, (int)m_indices.size(), GL_UNSIGNED_INT, 0, (GLsizei)amount);
        unbind();
    }
}
