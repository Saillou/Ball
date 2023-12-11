#include "Quad.hpp"

// - Quad -
Quad::Quad()
{
    // Vertices
    using v3 = glm::vec3;

    int iA = _addPoint(v3(-1.0f, +1.0f, 0));
    int iB = _addPoint(v3(-1.0f, -1.0f, 0));
    int iC = _addPoint(v3(+1.0f, -1.0f, 0));
    int iD = _addPoint(v3(+1.0f, +1.0f, 0));

    _addAsTriangle(iA, iB, iC);
    _addAsTriangle(iA, iC, iD);

    _bindArray();

    // Shader
    addRecipe(CookType::Quad);
}

void Quad::draw() {
    get(CookType::Quad)->use();

    bind();
    glDrawElements(GL_TRIANGLES, (int)m_indices.size(), GL_UNSIGNED_INT, 0);
    unbind();
}