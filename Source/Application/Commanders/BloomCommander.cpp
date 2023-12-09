#include "BloomCommander.hpp"
#include <glm/gtx/string_cast.hpp>

#include "../../Engine/Physx/Physx.hpp"

using namespace glm;


// Instance
BloomCommander::BloomCommander(std::shared_ptr<BaseScene> scene):
    BaseCommander(scene),
    m_scene(std::dynamic_pointer_cast<BloomScene>(scene))
{
    // ..
}

void BloomCommander::_on_state_update(const CommonEvents::StateUpdated& evt) {
    // ..
}

// Events
void BloomCommander::_on_key_pressed(const CommonEvents::KeyPressed& evt) {
    // ..
}

void BloomCommander::_on_mouse_moved(const CommonEvents::MouseMoved& evt) {
    // ..
}
