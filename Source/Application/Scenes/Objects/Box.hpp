#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "../../../Engine/Graphic/Base/Light.hpp"
#include "../../../Engine/Graphic/Camera.hpp"
#include "../../../Engine/Graphic/Base/BaseShape.hpp"
#include "../../../Engine/Graphic/Base/Cookable.hpp"

// Objects
struct Box : public Cookable
{
    // Instance
    Box(const glm::vec3& dims);
    virtual ~Box() = default;

    void draw(const Camera& camera, const glm::vec3& position = {}, const glm::vec3& orientation = {}, const std::vector<Light>& lights = {});
    void drawBatch(size_t amount, const Camera& camera);

    std::shared_ptr<BaseShape> shape();

private:
    void bind();
    void unbind();

    // Members
    std::shared_ptr<BaseShape> m_shape;
};