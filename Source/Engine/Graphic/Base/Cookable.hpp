#pragma once

#include <glm/glm.hpp>

#include "../Shaders/Shader.hpp"
#include "../../../Utils/Caster.hpp"

// Objects
struct Cookable : public Object {
    // Basic possibilities
    enum class CookType {
        Solid, Batch
    };

    // Instance
    virtual ~Cookable() = default;

    virtual Cookable* addRecipe(const CookType& type);
    virtual Cookable* addRecipe(const CookType& type, const glm::vec4& color);

protected:
    virtual void _set_shader_batch(UShader& shader);
    virtual void _set_shader_single(UShader& shader);

    // Members
    std::vector<UShader> m_shaders;
};

typedef std::unordered_map<std::string, std::shared_ptr<Cookable>> CookableCollection;
