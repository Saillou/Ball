#include "Quad.hpp"

// - Quad -
Quad::Quad()
{
    // Shape
    _createQuad(
        glm::vec3(-1.0f, +1.0f, 0),
        glm::vec3(-1.0f, -1.0f, 0),
        glm::vec3(+1.0f, -1.0f, 0),
        glm::vec3(+1.0f, +1.0f, 0)
    );
    _bindArray();

    // Cook
    addRecipe(CookType::Quad);
}

void Quad::draw() {
    get(CookType::Quad)->use();

    bind();
    glDrawElements(GL_TRIANGLES, (int)m_indices.size(), GL_UNSIGNED_INT, 0);
    unbind();
}