#pragma once

#include "../../Engine/Graphic/Base/BaseScene.hpp"

#include <vector>
#include <memory>
#include "Objects/SphereBatch.hpp"

// -- Scene --
struct AppScene : public BaseScene {
    AppScene();

    void draw() override;
    void resize(int width, int height) override;

    void startBrownian() {
        m_anime_brownian = true;
    }

private:
    void _update_camera();

    SphereBatch m_decors;
    bool m_anime_brownian = false;
};
