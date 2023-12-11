#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "../Light.hpp"
#include "../BaseShape.hpp"
#include "../Cookable.hpp"
#include "../../Camera.hpp"

// Objects
struct Sphere : public Cookable
{
    // Instance
    Sphere(float radius);
    virtual ~Sphere() = default;

    void draw(const Camera& camera, const glm::vec3& position = {}, const glm::vec3& orientation = {}, const std::vector<Light>& lights = {});
    void drawBatch(size_t amount, const Camera& camera);

    std::shared_ptr<BaseShape> shape();

private:
    void bind();
    void unbind();

    // Members
    std::shared_ptr<BaseShape> m_shape;
};