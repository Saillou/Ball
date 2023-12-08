#pragma once

#include <vector>
#include <memory>

#include "../../Engine/Graphic/Base/BaseScene.hpp"

#include "Objects/Sphere.hpp"
#include "Objects/Box.hpp"

// -- Scene --
struct AppScene : public BaseScene {
    AppScene();

    void draw() override;

private:

    struct FireBall {
        std::unique_ptr<Sphere> object;
        glm::vec3 pos;

        struct Particles {
            std::unique_ptr<Box> object;
            std::vector<glm::mat4> models;
            std::vector<glm::vec4> colors;
            std::vector<glm::vec3> speeds;
        } particles;
    } m_fireBall;
};
