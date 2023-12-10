#include "BaseScene.hpp"

#include <glad/glad.h>

BaseScene::BaseScene() {
    _init_gl_config();
}

BaseScene::~BaseScene() {
}

void BaseScene::draw() {
    // to be overrided
}

void BaseScene::_onResize() {
    // to be overrided
}

void BaseScene::drawQuad(unsigned int texture_id) {
    glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.

    m_quad.setTexture(texture_id);
    m_quad.draw();

    glEnable(GL_DEPTH_TEST); // set back to original state.
}

void BaseScene::resize(int width, int height) {
    m_width = width;
    m_height = height;

    _update_camera();

    _onResize();
}

void BaseScene::_init_gl_config() {
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_MULTISAMPLE);
}

void BaseScene::_update_camera() {
    if (m_height == 0)
        return;

    float aspect = (float)m_width / m_height;

    m_camera.lookAt(glm::vec3(0, 0, 1));
    m_camera.usePerspective(aspect);
}

int BaseScene::width() const {
    return m_width;
}
int BaseScene::height() const {
    return m_height;
}
Camera& BaseScene::camera() {
    return m_camera;
}
std::vector<Light>& BaseScene::lights() {
    return m_lights;
}

// - Quad -
BaseScene::_Quad::_Quad() 
{
    // Vertices
    using v3 = glm::vec3;

    int iA = _addPoint(v3(-1.0f, +1.0f, 0));
    int iB = _addPoint(v3(-1.0f, -1.0f, 0));
    int iC = _addPoint(v3(+1.0f, -1.0f, 0));
    int iD = _addPoint(v3(+1.0f, +1.0f, 0));

    _addAsTriangle(iA, iB, iC);
    _addAsTriangle(iC, iD, iA);

    // Shader
    addRecipe(CookType::Quad);
}

void BaseScene::_Quad::setTexture(unsigned int texture_id) {
    glBindTexture(GL_TEXTURE_2D, texture_id);
}

void BaseScene::_Quad::draw() {
    //screenShader.use();
    //glBindVertexArray(quadVAO);

    //glDrawArrays(GL_TRIANGLES, 0, 6);
}
