#include "FireCommander.hpp"
#include <glm/gtx/string_cast.hpp>

#include "../../Engine/Physx/Physx.hpp"

using namespace glm;


// Instance
FireCommander::FireCommander(std::shared_ptr<BaseScene> scene):
    BaseCommander(scene),
    m_scene(std::dynamic_pointer_cast<FireScene>(scene))
{
    // ..
}

void FireCommander::_on_state_update(const CommonEvents::StateUpdated& evt) {
    // ..
}

// Events
void FireCommander::_on_key_pressed(const CommonEvents::KeyPressed& evt) {
    // ..
    if (evt.key == Key::Space)
        m_scene->start = true;
}

void FireCommander::_on_mouse_moved(const CommonEvents::MouseMoved& evt) {
    // ..
}
