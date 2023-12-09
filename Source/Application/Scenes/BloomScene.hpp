#pragma once

#include <vector>
#include <memory>

#include "../../Engine/Graphic/Base/BaseScene.hpp"

#include "Objects/Sphere.hpp"
#include "Objects/Box.hpp"

// -- Scene --
struct BloomScene : public BaseScene {
    BloomScene();

    void draw() override;

private:
    Sphere ball_model;
    Sphere light_model;
};
