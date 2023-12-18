#pragma once

#include <vector>
#include <memory>

#include "../../Engine/Graphic/Base/BaseScene.hpp"
#include "../../Engine/Graphic/Utils/Framebuffer.hpp"
#include "../../Engine/Graphic/Base/Shapes/Sphere.hpp"
#include "../../Engine/Graphic/Base/Shapes/Box.hpp"

// -- Scene --
struct LearnScene : public BaseScene {
    LearnScene();

    void draw() override;
    void _onResize() override;

private:

};
