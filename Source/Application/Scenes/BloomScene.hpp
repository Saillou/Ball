#pragma once

#include <vector>
#include <memory>

#include "../../Engine/Graphic/Base/BaseScene.hpp"
#include "../../Engine/Graphic/Utils/Framebuffer.hpp"

#include "Objects/Sphere.hpp"
#include "Objects/Box.hpp"

// -- Scene --
struct BloomScene : public BaseScene {
    BloomScene();

    void draw() override;
    void _onResize() override;

private:
    Sphere ball_model;
    Sphere light_model;
    Framebuffer framebuffer;
};
